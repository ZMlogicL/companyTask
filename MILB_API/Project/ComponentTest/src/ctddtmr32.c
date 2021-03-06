/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTmr32类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_tmr32.c
 * @brief		This is ct code for dd_tmr32
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "ddtmr32.h"
#include "peripheral.h"
#include "ddtop.h"
#include "chiptop.h"
#include <stdlib.h>
#include <string.h>
#include "ddgic.h"
#include "ctddtmr32.h"
#include "ddimusercustom.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTmr32, ct_dd_tmr32);
#define CT_DD_TMR32_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTmr32Private,CT_TYPE_DD_TMR32))

struct _CtDdTmr32Private {
    
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CO_CT_DD_TMR32_USTIME		// Enable;get time(us). Disenable:get time(ms)

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kulonglong	S_GDD_TIMER32_TIM1;
static kulonglong	S_GDD_TIMER32_TIM2;

#if 0
static kulong gDD_Timer32_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));
#endif
/*
 *DECLS
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef	CO_CT_DD_TMR32_USTIME
static kulong       ctDdTmr32GetTimeUs(void);
#endif
static void  		ctTimer32Cb(void);

static void ct_dd_tmr32_constructor(CtDdTmr32 *self) 
{
// CtDdTmr32Private *priv = CT_DD_TMR32_GET_PRIVATE(self);
}

static void ct_dd_tmr32_destructor(CtDdTmr32 *self)
{
// CtDdTmr32Private *priv = CT_DD_TMR32_GET_PRIVATE(self);
}
/*
 *IMPL
 */
/*-------------*/
/* 32bit Timer */
/*-------------*/
static void ctTimer32Cb(void)
{
	DdimUserCustom *ddimUserCus = ddim_user_custom_new();
#ifdef	CO_CT_DD_TMR32_USTIME
#else	// CO_CT_DD_TMR32_USTIME
	kint32	er;
#endif	// CO_CT_DD_TMR32_USTIME

#if 0	// for Debug code
	//for Oscilloscope///////////////	//This is not needed for PT.
	// DSR_C and DSR_C are not used.
//	if (IO_CHIPTOP.PDR.bit.P41 == 0){
	if (*(volatile unsigned long*)0x1DFFB004 == 0x00400000){
		//IO_CHIPTOP.PDR_S.bit.P41=1;		// DSR_S is not defined. ok???
		//IO_CHIPTOP.PDR.bit.P41=1;
		*(volatile unsigned long*)0x1DFFB004 = 0x00400040;
	}else{
		//IO_CHIPTOP.PDR_C.bit.P41=1;		// DSR_C is not defined. ok???
		//IO_CHIPTOP.PDR.bit.P41=0;
		*(volatile unsigned long*)0x1DFFB004 = 0x00400000;
	}
//	IO_CHIPTOP.PDR_S.bit.P41=1;	//oscilloscope
#endif	// for Debug code

#ifdef	CO_CT_DD_TMR32_USTIME
	S_GDD_TIMER32_TIM2 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
	er = ddim_user_custom_get_tim(ddimUserCus, &S_GDD_TIMER32_TIM2);
	if(er != DdimUserCustom_E_OK){
		Ddim_Print(("get_tim() er=%d\n",er));
	}
#endif	// CO_CT_DD_TMR32_USTIME
	Ddim_Print(("TMR32 INT. %lu\n", (kulong)(S_GDD_TIMER32_TIM2 - S_GDD_TIMER32_TIM1)));
	S_GDD_TIMER32_TIM1 = S_GDD_TIMER32_TIM2 ;
	k_object_unref(ddimUserCus);
	ddimUserCus = NULL;
}

#ifdef	CO_CT_DD_TMR32_USTIME
//Get_Time_us
static kulong ctDdTmr32GetTimeUs(void)
{
	kulong hCount;
	kulong 		sCount;
	kulonglong 	hCountLong;
	static kuint32 S_GET_TIME_CH =2;
	dd_tmr32_get_counter(S_GET_TIME_CH, &hCount, &sCount);
	hCount = 0xFFFFFFFF - hCount;
	hCountLong = (kulonglong)hCount;
	hCountLong = hCountLong * 32;
	
	return (kulong)(hCountLong / 54);
}
#endif	// CO_CT_DD_TMR32_USTIME
/*
 *PUBLIC
 */
/**
 * @brief  Command main function for timer32 test.
 * @param  int argc		:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 */
void ct_dd_tmr32_main(CtDdTmr32 *self, kint argc, KType* argv)
{
	kint32				ret;
	kuint32				ch;
	TDdTmr32Ctrl		tmr32Ctrl = {{0}};
	DdTmr32 *			ddTmr32 = dd_tmr32_get();
	DdimUserCustom *	ddimUserCus = ddim_user_custom_new();
#ifndef	CO_CT_DD_TMR32_USTIME
	kint32				er;
#endif	// CO_CT_DD_TMR32_USTIME

	/*-------*/
	/* Open  */
	/*-------*/
	if(strcmp(argv[1], "open") == 0){
		/* ch number */
		ch = atoi(argv[2]);
		DdGic *ddGic = dd_gic_new();
#if 0	// for Debug code
		// DSR_C is not used.
		//IO_CHIPTOP.PDR_C.bit.P41  = 1;	//for Oscilloscope	//This is not needed for PT.
		//IO_CHIPTOP.PDR.bit.P41  = 0; //?????
		*(volatile unsigned long*)0x1DFFB004 = 0x00400000;
#endif	// for Debug code
		// Set for gic(For the channel that it's not set).
		switch(ch){
			case 6:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH6_INT,1,C_PRI30,1);
				break;
			case 7:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH7_INT,1,C_PRI30,1);
				break;
			case 8:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH8_INT,1,C_PRI30,1);
				break;
			case 9:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH9_INT,1,C_PRI30,1);
				break;
			case 10:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH10_INT,1,C_PRI30,1);
				break;
			case 11:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH11_INT,1,C_PRI30,1);
				break;
			case 12:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH12_INT,1,C_PRI30,1);
				break;
			case 13:
				dd_gic_ctrl(ddGic, DdGic_INTID_TIMER_CH13_INT,1,C_PRI30,1);
				break;
			default:
				break;
		}
		k_object_unref(ddGic);
		ddGic = NULL;
		/* Open */
		ret = dd_tmr32_open(ddTmr32, ch, (kint32)atoi(argv[3]));
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_open[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_open[%d] ERR=%d\n", ch, ret));
		}
#if 0	// for Debug code
		S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
		DDIM_User_Dly_Tsk(10);
		S_GDD_TIMER32_TIM2 = ctDdTmr32GetTimeUs();
		Ddim_Print(("TMR32_Dly test. %d\n", (kulong)(S_GDD_TIMER32_TIM2 - S_GDD_TIMER32_TIM1)));
		S_GDD_TIMER32_TIM1=S_GDD_TIMER32_TIM2;
		DDIM_User_Dly_Tsk(10);
		S_GDD_TIMER32_TIM2 = ctDdTmr32GetTimeUs();
		Ddim_Print(("TMR32_Dly test. %d\n", (kulong)(S_GDD_TIMER32_TIM2 - S_GDD_TIMER32_TIM1)));
#endif	// for Debug code
	}
	/*-------*/
	/* close */
	/*-------*/
	else if(strcmp(argv[1], "close") == 0){
		/* ch number */
		ch = atoi(argv[2]);

		/* Close */
		ret = dd_tmr32_close(ddTmr32, ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_close[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_close[%d] ERR=%d\n", ch, ret));
		}
	}
	/*------*/
	/* Ctrl */
	/*------*/
	else if(strcmp(argv[1], "ctrl") == 0){
		// CH
		ch = atoi(argv[2]);
		
		tmr32Ctrl.csr.word = 0x00000008;
		
		// DIV
		if(strcmp(argv[3], "32") == 0){
			tmr32Ctrl.csr.bit.csl = 2;
		}
		else if(strcmp(argv[3], "8") == 0){
			tmr32Ctrl.csr.bit.csl = 1;
		}
		else if(strcmp(argv[3], "2") == 0){
			tmr32Ctrl.csr.bit.csl = 0;
		}
		else if(strcmp(argv[3], "ext") == 0){
			tmr32Ctrl.csr.bit.csl = 3;
		}
		else {
			tmr32Ctrl.csr.bit.csl = 0;
		}
		// MODE
		if(strcmp(argv[4], "one") == 0){
			tmr32Ctrl.csr.bit.reld = 0;
		}
		else if(strcmp(argv[4], "reload") == 0){
			tmr32Ctrl.csr.bit.reld = 1;
		}
		else {
			tmr32Ctrl.csr.bit.reld = 0;
		}
		
		tmr32Ctrl.rlr1 = (kulong)atoi(argv[5]);
		tmr32Ctrl.rlr2 = (kulong)atoi(argv[6]);
		tmr32Ctrl.softCounter = (kuchar)atoi(argv[7]);
		tmr32Ctrl.pcallback = ctTimer32Cb;
		
		// Edge hunt MODE
		if(strcmp(argv[8], "u") == 0){
			// Upper
			tmr32Ctrl.csr.bit.mod = 1;
		}
		else if(strcmp(argv[8], "d") == 0){
			// Down
			tmr32Ctrl.csr.bit.mod = 2;
		}
		else if(strcmp(argv[8], "b") == 0){
			// Both
			tmr32Ctrl.csr.bit.mod = 3;
		}
		else {
			tmr32Ctrl.csr.bit.mod = 0;
		}


		Ddim_Print(("dd_tmr32_ctrl Arg(TDdTmr32Ctrl)///\n"));
		Ddim_Print(("csr.trg_fixed0 = %d\n", tmr32Ctrl.csr.bit.trgFixed0));/* pgr0872 */
		Ddim_Print(("csr.cnte       = %d\n", tmr32Ctrl.csr.bit.cnte));		/* pgr0872 */
		Ddim_Print(("csr.uf_fixed1  = %d\n", tmr32Ctrl.csr.bit.ufFixed1));	/* pgr0872 */
		Ddim_Print(("csr.inte       = %d\n", tmr32Ctrl.csr.bit.inte));		/* pgr0872 */
		Ddim_Print(("csr.reld       = %d\n", tmr32Ctrl.csr.bit.reld));
		Ddim_Print(("csr.outl       = %d\n", tmr32Ctrl.csr.bit.outl));		/* pgr0872 */
		Ddim_Print(("csr.mod        = %d\n", tmr32Ctrl.csr.bit.mod));		/* pgr0872 */
		Ddim_Print(("csr.csl        = %d\n", tmr32Ctrl.csr.bit.csl));
		Ddim_Print(("csr.rels       = %d\n", tmr32Ctrl.csr.bit.rels));		/* pgr0872 */
		Ddim_Print(("rlr1           = %lu\n", tmr32Ctrl.rlr1));
		Ddim_Print(("rlr2           = %lu\n", tmr32Ctrl.rlr2));
		Ddim_Print(("soft_counter   = %lu\n", tmr32Ctrl.softCounter));
		Ddim_Print(("pcallback      = %p\n", tmr32Ctrl.pcallback));
		Ddim_Print(("///////////////////////////////////////\n"));

		/* Ctrl */
		ret = dd_tmr32_ctrl(ddTmr32, ch, &tmr32Ctrl);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_ctrl[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("timer dd_tmr32_ctrl[%d] error=%d\n", ch, ret));
		}
		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*-----------*/
	/* Calculate */
	/*-----------*/
	else if(strcmp(argv[1], "cal") == 0){
		self->usec = (kulong)atoi(argv[2]);

		ret = dd_tmr32_calculate(ddTmr32, self->usec, &tmr32Ctrl);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_calculate OK\n"));
			Ddim_Print(("rels         = %d\n", tmr32Ctrl.csr.bit.rels));
			Ddim_Print(("csl          = %d\n", tmr32Ctrl.csr.bit.csl));
			Ddim_Print(("mod          = %d\n", tmr32Ctrl.csr.bit.mod));
			Ddim_Print(("outl         = %d\n", tmr32Ctrl.csr.bit.outl));
			Ddim_Print(("reld         = %d\n", tmr32Ctrl.csr.bit.reld));
			Ddim_Print(("inte         = %d\n", tmr32Ctrl.csr.bit.inte));
			Ddim_Print(("uf_fixed1    = %d\n", tmr32Ctrl.csr.bit.ufFixed1));
			Ddim_Print(("cnte         = %d\n", tmr32Ctrl.csr.bit.cnte));
			Ddim_Print(("trg_fixed0   = %d\n", tmr32Ctrl.csr.bit.trgFixed0));
			Ddim_Print(("rlr1         = %lu\n", tmr32Ctrl.rlr1));
			Ddim_Print(("rlr2         = %lu\n", tmr32Ctrl.rlr2));
			Ddim_Print(("soft_counter = %lu\n", tmr32Ctrl.softCounter));
			Ddim_Print(("pcallback    = %p\n", tmr32Ctrl.pcallback));
		}
		else {
			Ddim_Print(("dd_tmr32_calculate ERR=%d\n", ret));
		}
	}
	/*----------------*/
	/* Start / Resume */
	/*----------------*/
	else if(strcmp(argv[1], "start") == 0){
		/* ch number */
		ch = atoi(argv[2]);
		
		/* Start */
		ret = dd_tmr32_start(ddTmr32, ch);
			/* Debug: Time(msec) */
#if 0	// for Debug code
			// DSR_S is not used.
			//IO_CHIPTOP.PDR_S.bit.P41 = 1;	//for Oscilloscope	//This is not needed for PT.
			//IO_CHIPTOP.PDR.bit.P41 = 1;//?????
			*(volatile unsigned long*)0x1DFFB004 = 0x00400040;
#endif	// for Debug code

#ifdef	CO_CT_DD_TMR32_USTIME
			S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
			er = ddim_user_custom_get_tim(ddimUserCus, &S_GDD_TIMER32_TIM1);
			if(er != DdimUserCustom_E_OK){
				Ddim_Print(("get_tim() er=%d\n",er));
			}
#endif	// CO_CT_DD_TMR32_USTIME

#if 0	// for Debug code
	S_GDD_TIMER32_TIM2 = 0;
	gDd_timer32_tim3 = 0;
	gDd_timer32_tim4 = 0;
	Dd_ARM_Critical_Section_Start(gDD_Timer32_Spin_Lock);
	ioPeri.tmr[ch].tmcsr.word |= 0x0000000B;
	S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
	// UF clear 
	ioPeri.tmr[ch].tmcsr.word &= 0xFFFFFFFA;
	
	// UF 
	while(1){
		if(ioPeri.tmr[ch].tmcsr.bit.__UF == 1){
			if (S_GDD_TIMER32_TIM2 == 0){
				S_GDD_TIMER32_TIM2 = ctDdTmr32GetTimeUs();
				ioPeri.tmr[ch].tmcsr.word &= 0xFFFFFFFA;
			}
			else if (gDd_timer32_tim3 == 0){
				gDd_timer32_tim3 = ctDdTmr32GetTimeUs();
				ioPeri.tmr[ch].tmcsr.word &= 0xFFFFFFFA;
			}
			else if (gDd_timer32_tim4 == 0){
				gDd_timer32_tim4 = ctDdTmr32GetTimeUs();
				ioPeri.tmr[ch].tmcsr.word &= 0xFFFFFFFA;
				break;
			}
		}
	}
	Ddim_Print(("\n___%d(us)\n", (kulong)(S_GDD_TIMER32_TIM2 - S_GDD_TIMER32_TIM1)));
	Ddim_Print(("\n___%d(us)\n", (kulong)(gDd_timer32_tim3 - S_GDD_TIMER32_TIM2)));
	Ddim_Print(("\n___%d(us)\n", (kulong)(gDd_timer32_tim4 - gDd_timer32_tim3)));
	S_GDD_TIMER32_TIM1 = gDd_timer32_tim4;
	Dd_ARM_Critical_Section_End(gDD_Timer32_Spin_Lock);
#endif	// for Debug code
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_start[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_start[%d] ERR=%d\n", ch, ret));
		}
		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*------------------------*/
	/* External trigger Start */
	/*------------------------*/
	else if(strcmp(argv[1], "ext_start") == 0){
		/* ch number */
		ch = atoi(argv[2]);
		
		/* Start */
		ret = dd_tmr32_external_start(ddTmr32, ch);
			/* Debug: Time(msec) */
#ifdef	CO_CT_DD_TMR32_USTIME
			S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
			er = ddim_user_custom_get_tim(ddimUserCus, &S_GDD_TIMER32_TIM1);
			if(er != DdimUserCustom_E_OK){
				Ddim_Print(("get_tim() er=%d\n",er));
			}
#endif	// CO_CT_DD_TMR32_USTIME
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_external_start[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_external_start[%d] ERR=%d\n", ch, ret));
		}
//		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*------*/
	/* stop */
	/*------*/
	else if(strcmp(argv[1], "stop") == 0){  		// Timer32 stop
		/* ch number */
		ch = atoi(argv[2]);

		/* Stop */
		ret = dd_tmr32_stop(ddTmr32, ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_stop[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_stop[%d] ERR=%d\n", ch, ret));
		}
		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*-------*/
	/* Pause */
	/*-------*/
	else if(strcmp(argv[1], "pause") == 0){
		/* ch number */
		ch = atoi(argv[2]);

		/* Pause */
		ret = dd_tmr32_pause(ddTmr32, ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_pause[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_pause[%d] ERR=%d\n", ch, ret));
		}
		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*-----------------------------------*/
	/* Get TMR Register and Soft Counter */
	/*-----------------------------------*/
	else if(strcmp(argv[1], "get_counter") == 0){
		kulong	hwCount ;
		kulong	swCount ;

		/* ch number */
		ch = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		ret = dd_tmr32_get_counter(ddTmr32, ch, &hwCount, &swCount);
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_get_counter[%d] OK\n", ch));
			Ddim_Print(("H/W counter = 0x%lx, S/W Counter=%lu\n", hwCount, swCount));
		}
		else {
			Ddim_Print(("dd_tmr32_get_counter[%d] ERR=%d\n", ch, ret));
		}
	}
	/*------------------------*/
	/* Get Timer's Ctrl table */
	/*------------------------*/
	else if(strcmp(argv[1], "get_table") == 0){
		/* ch number */
		ch = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		ret = dd_tmr32_get_ctrl(ddTmr32, ch, &tmr32Ctrl) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_get_ctrl[%d] OK\n", ch));
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
			Ddim_Print(("csr         =0x%lx\n", tmr32Ctrl.csr.word));
			Ddim_Print(("rlr1        =%lu\n", tmr32Ctrl.rlr1));
			Ddim_Print(("rlr2        =%lu\n", tmr32Ctrl.rlr2));
			Ddim_Print(("soft_counter=%lu\n", tmr32Ctrl.softCounter));
			Ddim_Print(("pcallback   =%p\n", tmr32Ctrl.pcallback));
		}
		else {
			Ddim_Print(("dd_tmr32_get_ctrl ERR=%d\n", ret));
		}
	}
	/*------------------*/
	/* Set Soft Counter */
	/*------------------*/
	else if(strcmp(argv[1], "set_softcounter") == 0){
		/* ch number */
		ch  = atoi(argv[2]);
		self->num = atoi(argv[3]);

		/* Set H/W & S/W Counter */
		ret = dd_tmr32_set_soft_counter_value(ddTmr32, ch, self->num) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_set_soft_counter_value[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_set_soft_counter_value[%d] ERR=%d\n", ch, ret));
		}
	}
	/*------------------*/
	/* Get Soft Counter */
	/*------------------*/
	else if(strcmp(argv[1], "get_softcounter") == 0){
		/* ch number */
		ch  = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		self->num = dd_tmr32_get_soft_counter_vlaue(ddTmr32, ch) ;
		Ddim_Print(("Soft counter[%d]=%lu\n", ch, self->num));
	}
	/*-----------------*/
	/* Set Reload Flag */
	/*-----------------*/
	else if(strcmp(argv[1], "set_reload") == 0){
		/* ch number */
		ch  = atoi(argv[2]);
		self->num = atoi(argv[3]);

		/* Get H/W & S/W Counter */
		ret = dd_tmr32_set_reload_flg_value(ddTmr32, ch, self->num) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr32_set_reload_flg_value[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_set_reload_flg_value[%d] ERR=%d\n", ch, ret));
		}
	}
	/*-----------------*/
	/* Get Reload Flag */
	/*-----------------*/
	else if(strcmp(argv[1], "get_reload") == 0){
		/* ch number */
		ch  = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		self->num = dd_tmr32_get_reload_flg_value(ddTmr32, ch) ;
		Ddim_Print(("Reload Flag[%d]=%lu\n", ch, self->num));
	}
	/*---------------------*/
	/* Utility : Set_Timer */
	/*---------------------*/
	else if(strcmp(argv[1], "u_set") == 0){
		ch   = atoi(argv[2]);
		self->usec = (kulong)atoi(argv[3]);
		
		Ddim_Print(("Peri CLK=%lu\n", dd_topone_get_rclk()));
		
		ret = dd_tmr32_set_timer(ddTmr32, ch, self->usec, ctTimer32Cb);
		if (ret == 0) {
			Ddim_Print(("dd_tmr32_set_timer[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_set_timer[%d] ERR. ret=0x%x\n", ch, ret));
		}
	}
	/*------------------------*/
	/* Utility : Start Reload */
	/*------------------------*/
	else if(strcmp(argv[1], "u_start_reload") == 0){
		ch   = atoi(argv[2]);
		
		/* Debug: Time(msec) */
#ifdef	CO_CT_DD_TMR32_USTIME
		S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
		er = ddim_user_custom_get_tim(ddimUserCus, &S_GDD_TIMER32_TIM1);
		if(er != DdimUserCustom_E_OK){
			Ddim_Print(("get_tim() er=%d\n",er));
		}
#endif	// CO_CT_DD_TMR32_USTIME
		ret = dd_tmr32_start_reload(ddTmr32, ch);
		if (ret == 0) {
			Ddim_Print(("dd_tmr32_start_reload[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_start_reload[%d] ERR. ret=0x%x\n", ch, ret));
		}
	}
	/*--------------------------*/
	/* Utility : Start OneShot  */
	/*--------------------------*/
	else if(strcmp(argv[1], "u_start_one") == 0){
		ch   = atoi(argv[2]);
		
		/* Debug: Time(msec) */
#ifdef	CO_CT_DD_TMR32_USTIME
		S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
		er = ddim_user_custom_get_tim(ddimUserCus, &S_GDD_TIMER32_TIM1);
		if(er != DdimUserCustom_E_OK){
			Ddim_Print(("get_tim() er=%d\n",er));
		}
#endif	// CO_CT_DD_TMR32_USTIME
		ret = dd_tmr32_start_one_shot(ddTmr32, ch);
		if (ret == 0) {
			Ddim_Print(("dd_tmr32_start_one_shot[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("dd_tmr32_start_one_shot[%d] ERR. ret=0x%x\n", ch, ret));
		}
	}
	/*---------------*/
	/* Set Out Level */
	/*---------------*/
	else if(strcmp(argv[1], "set_outlevel") == 0){

		ch   = atoi(argv[2]);

		ret = dd_tmr32_set_out_level(ddTmr32, atoi(argv[3]));
		if (ret == 0) {
			Ddim_Print(("dd_tmr32_set_out_level[%d] OK\n", ch));
			Ddim_Print(("OUTL = [0x%lx] \n", ioPeri.tmr[3].tmcsr.word));
		}
		else {
			Ddim_Print(("dd_tmr32_set_out_level[%d] ERR. ret=0x%x\n", ch, ret));
		}
	}
	/*------------*/
	/* Test 1-all */
	/*------------*/
	else if(strcmp(argv[1], "test_1_all") == 0){
		kint32	chRoop;
		kulong	hwCount ;
		kulong	swCount ;

		// Open/Close check
		for(chRoop=0; chRoop < DdTmr32_CH_NUM_MAX; chRoop++){
			Ddim_Print(("test_1_all : %d /////////////////////////\n", chRoop));
			/* Open */
			ret = dd_tmr32_open(ddTmr32, chRoop, 0);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_open[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_open[%d] ERR=%d\n", chRoop, ret));
			}

			/* Calculate */
			dd_tmr32_calculate(ddTmr32, 3000, &tmr32Ctrl);
			/* Ctrl */
			ret = dd_tmr32_ctrl(ddTmr32, chRoop, &tmr32Ctrl);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_ctrl[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("timer dd_tmr32_ctrl[%d] error=%d\n", chRoop, ret));
			}

			/* Start */
			ret = dd_tmr32_start(ddTmr32, chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_start[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_start[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* Pause */
			ret = dd_tmr32_pause(ddTmr32, chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_pause[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_pause[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* ReStart */
			ret = dd_tmr32_start(ddTmr32, chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_start[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_start[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

#ifdef CO_DEBUG_ON_PC
			ioPeri.tmr[chRoop].tmr	= 0x11111111 * (chRoop+1);
#endif	// CO_DEBUG_ON_PC

			/* Get H/W & S/W Counter */
			ret = dd_tmr32_get_counter(ddTmr32, chRoop, &hwCount, &swCount);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_get_counter[%d] OK\n", chRoop));
				Ddim_Print(("H/W counter = 0x%lx, S/W Counter=%lu\n", hwCount, swCount));
			}
			else {
				Ddim_Print(("dd_tmr32_get_counter[%d] ERR=%d\n", chRoop, ret));
			}

			/* Get H/W & S/W Counter */
			ret = dd_tmr32_get_ctrl(ddTmr32, chRoop, &tmr32Ctrl) ;
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_get_ctrl[%d] OK\n", chRoop));
				Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
					chRoop, ioPeri.tmr[chRoop].tmcsr.word));
				Ddim_Print(("csr         =0x%lx\n", tmr32Ctrl.csr.word));
				Ddim_Print(("rlr1        =%lu\n", tmr32Ctrl.rlr1));
				Ddim_Print(("rlr2        =%lu\n", tmr32Ctrl.rlr2));
				Ddim_Print(("soft_counter=%lu\n", tmr32Ctrl.softCounter));
				Ddim_Print(("pcallback   =%p\n", tmr32Ctrl.pcallback));
			}
			else {
				Ddim_Print(("dd_tmr32_get_ctrl ERR=%d\n", ret));
			}

			/* Stop */
			ret = dd_tmr32_stop(ddTmr32, chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_stop[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_stop[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* Close */
			ret = dd_tmr32_close(ddTmr32, chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_close[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("dd_tmr32_close[%d] ERR=%d\n", chRoop, ret));
			}

			/* Check SoftCounter */
			ret = dd_tmr32_set_soft_counter_value(ddTmr32, chRoop, (0x11111111*(chRoop+1)));
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_set_soft_counter_value[%d] OK\n", chRoop));
				Ddim_Print(("dd_tmr32_get_soft_counter_vlaue[%d] %lx\n", 
					chRoop, dd_tmr32_get_soft_counter_vlaue(ddTmr32, chRoop)));
			}
			else {
				Ddim_Print(("dd_tmr32_set_soft_counter_value[%d] ERR=%d\n", chRoop, ret));
			}

			/* Check Reload_Flg */
			ret = dd_tmr32_set_reload_flg_value(ddTmr32, chRoop, (0x11*(chRoop+1))) ;
			if(ret == D_DDIM_OK){
				Ddim_Print(("dd_tmr32_set_reload_flg_value[%d] OK\n", chRoop));
				Ddim_Print(("dd_tmr32_get_reload_flg_value[%d] %x\n", 
					chRoop, dd_tmr32_get_reload_flg_value(ddTmr32, chRoop)));
			}
			else {
				Ddim_Print(("dd_tmr32_set_reload_flg_value[%d] ERR=%d\n", chRoop, ret));
			}
		}
	}
	else{
		Ddim_Print(("please check 2nd parameter!!\n"));
	}
	k_object_unref(ddTmr32);
	ddTmr32 = NULL; 
	k_object_unref(ddimUserCus);
	ddimUserCus = NULL;
}

CtDdTmr32 *ct_dd_tmr32_new(void)
{
    CtDdTmr32 *self = k_object_new_with_private(CT_TYPE_DD_TMR32, sizeof(CtDdTmr32Private));
    return self;
}
