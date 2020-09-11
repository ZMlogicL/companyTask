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

#include "dd_tmr32.h"
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
    kulong hCount;
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
static DdimUserCustom_SYSTIM	S_GDD_TIMER32_TIM1;
static DdimUserCustom_SYSTIM	S_GDD_TIMER32_TIM2;

#if 0
static kulong gDD_Timer32_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));
#endif

/*DECLS*/

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef	CO_CT_DD_TMR32_USTIME
static kulong       ctDdTmr32GetTimeUs(void);
#endif
static void  ctTimer32Cb(void);

static void ct_dd_tmr32_constructor(CtDdTmr32 *self) 
{
// CtDdTmr32Private *priv = CT_DD_TMR32_GET_PRIVATE(self);
}

static void ct_dd_tmr32_destructor(CtDdTmr32 *self)
{
// CtDdTmr32Private *priv = CT_DD_TMR32_GET_PRIVATE(self);
}

/*IMPL*/

/*-------------*/
/* 32bit Timer */
/*-------------*/
static void ctTimer32Cb(void)
{
#ifdef	CO_CT_DD_TMR32_USTIME
#else	// CO_CT_DD_TMR32_USTIME
	DdimUserCustom_ER	er;
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
	er = ddim_user_custom_get_tim(&S_GDD_TIMER32_TIM2);
	if(er != DdimUserCustom_E_OK){
		Ddim_Print(("get_tim() er=%d\n",er));
	}
#endif	// CO_CT_DD_TMR32_USTIME
	Ddim_Print(("TMR32 INT. %lu\n", (kulong)(S_GDD_TIMER32_TIM2 - S_GDD_TIMER32_TIM1)));
	S_GDD_TIMER32_TIM1 = S_GDD_TIMER32_TIM2 ;
}

#ifdef	CO_CT_DD_TMR32_USTIME
//Get_Time_us
static kulong ctDdTmr32GetTimeUs(void)
{
	CtDdTmr32Private *priv = CT_DD_TMR32_GET_PRIVATE(self);
	kulong 		sCount;
	kulonglong 	hCountLong;
	static kuint32 S_GET_TIME_CH =2;
	Dd_TMR32_Get_Counter(S_GET_TIME_CH, &priv->hCount, &sCount);
	priv->hCount = 0xFFFFFFFF - priv->hCount;
	hCountLong = (kulonglong)priv->hCount;
	hCountLong = hCountLong * 32;
	
	return (kulong)(hCountLong / 54);
}
#endif	// CO_CT_DD_TMR32_USTIME

/*PUBLIC*/

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
	T_DD_TMR32_CTRL		tmr32Ctrl = {{0}};
#ifndef	CO_CT_DD_TMR32_USTIME
	DdimUserCustom_ER	er;
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
		ret = Dd_TMR32_Open(ch, (kint32)atoi(argv[3]));
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Open[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Open[%d] ERR=%d\n", ch, ret));
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
		ret = Dd_TMR32_Close(ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Close[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Close[%d] ERR=%d\n", ch, ret));
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
		tmr32Ctrl.soft_counter = (kuchar)atoi(argv[7]);
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


		Ddim_Print(("Dd_TMR32_Ctrl Arg(T_DD_TMR32_CTRL)///\n"));
		Ddim_Print(("csr.trg_fixed0 = %d\n", tmr32Ctrl.csr.bit.trg_fixed0));/* pgr0872 */
		Ddim_Print(("csr.cnte       = %d\n", tmr32Ctrl.csr.bit.cnte));		/* pgr0872 */
		Ddim_Print(("csr.uf_fixed1  = %d\n", tmr32Ctrl.csr.bit.uf_fixed1));	/* pgr0872 */
		Ddim_Print(("csr.inte       = %d\n", tmr32Ctrl.csr.bit.inte));		/* pgr0872 */
		Ddim_Print(("csr.reld       = %d\n", tmr32Ctrl.csr.bit.reld));
		Ddim_Print(("csr.outl       = %d\n", tmr32Ctrl.csr.bit.outl));		/* pgr0872 */
		Ddim_Print(("csr.mod        = %d\n", tmr32Ctrl.csr.bit.mod));		/* pgr0872 */
		Ddim_Print(("csr.csl        = %d\n", tmr32Ctrl.csr.bit.csl));
		Ddim_Print(("csr.rels       = %d\n", tmr32Ctrl.csr.bit.rels));		/* pgr0872 */
		Ddim_Print(("rlr1           = %lu\n", tmr32Ctrl.rlr1));
		Ddim_Print(("rlr2           = %lu\n", tmr32Ctrl.rlr2));
		Ddim_Print(("soft_counter   = %lu\n", tmr32Ctrl.soft_counter));
		Ddim_Print(("pcallback      = %p\n", tmr32Ctrl.pcallback));
		Ddim_Print(("///////////////////////////////////////\n"));

		/* Ctrl */
		ret = Dd_TMR32_Ctrl(ch, &tmr32Ctrl);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Ctrl[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("timer Dd_TMR32_Ctrl[%d] error=%d\n", ch, ret));
		}
		Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
	}
	/*-----------*/
	/* Calculate */
	/*-----------*/
	else if(strcmp(argv[1], "cal") == 0){
		self->usec = (kulong)atoi(argv[2]);

		ret = Dd_TMR32_Calculate(self->usec, &tmr32Ctrl);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Calculate OK\n"));
			Ddim_Print(("rels         = %d\n", tmr32Ctrl.csr.bit.rels));
			Ddim_Print(("csl          = %d\n", tmr32Ctrl.csr.bit.csl));
			Ddim_Print(("mod          = %d\n", tmr32Ctrl.csr.bit.mod));
			Ddim_Print(("outl         = %d\n", tmr32Ctrl.csr.bit.outl));
			Ddim_Print(("reld         = %d\n", tmr32Ctrl.csr.bit.reld));
			Ddim_Print(("inte         = %d\n", tmr32Ctrl.csr.bit.inte));
			Ddim_Print(("uf_fixed1    = %d\n", tmr32Ctrl.csr.bit.uf_fixed1));
			Ddim_Print(("cnte         = %d\n", tmr32Ctrl.csr.bit.cnte));
			Ddim_Print(("trg_fixed0   = %d\n", tmr32Ctrl.csr.bit.trg_fixed0));
			Ddim_Print(("rlr1         = %lu\n", tmr32Ctrl.rlr1));
			Ddim_Print(("rlr2         = %lu\n", tmr32Ctrl.rlr2));
			Ddim_Print(("soft_counter = %lu\n", tmr32Ctrl.soft_counter));
			Ddim_Print(("pcallback    = %p\n", tmr32Ctrl.pcallback));
		}
		else {
			Ddim_Print(("Dd_TMR32_Calculate ERR=%d\n", ret));
		}
	}
	/*----------------*/
	/* Start / Resume */
	/*----------------*/
	else if(strcmp(argv[1], "start") == 0){
		/* ch number */
		ch = atoi(argv[2]);
		
		/* Start */
		ret = Dd_TMR32_Start(ch);
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
			er = ddim_user_custom_get_tim(&S_GDD_TIMER32_TIM1);
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
			Ddim_Print(("Dd_TMR32_Start[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Start[%d] ERR=%d\n", ch, ret));
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
		ret = Dd_TMR32_External_Start(ch);
			/* Debug: Time(msec) */
#ifdef	CO_CT_DD_TMR32_USTIME
			S_GDD_TIMER32_TIM1 = ctDdTmr32GetTimeUs();
#else	// CO_CT_DD_TMR32_USTIME
			er = ddim_user_custom_get_tim(&S_GDD_TIMER32_TIM1);
			if(er != DdimUserCustom_E_OK){
				Ddim_Print(("get_tim() er=%d\n",er));
			}
#endif	// CO_CT_DD_TMR32_USTIME
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_External_Start[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_External_Start[%d] ERR=%d\n", ch, ret));
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
		ret = Dd_TMR32_Stop(ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Stop[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Stop[%d] ERR=%d\n", ch, ret));
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
		ret = Dd_TMR32_Pause(ch);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Pause[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Pause[%d] ERR=%d\n", ch, ret));
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
		ret = Dd_TMR32_Get_Counter(ch, &hwCount, &swCount);
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Get_Counter[%d] OK\n", ch));
			Ddim_Print(("H/W counter = 0x%lx, S/W Counter=%lu\n", hwCount, swCount));
		}
		else {
			Ddim_Print(("Dd_TMR32_Get_Counter[%d] ERR=%d\n", ch, ret));
		}
	}
	/*------------------------*/
	/* Get Timer's Ctrl table */
	/*------------------------*/
	else if(strcmp(argv[1], "get_table") == 0){
		/* ch number */
		ch = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		ret = Dd_TMR32_Get_Ctrl(ch, &tmr32Ctrl) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Get_Ctrl[%d] OK\n", ch));
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", ch, ioPeri.tmr[ch].tmcsr.word));
			Ddim_Print(("csr         =0x%lx\n", tmr32Ctrl.csr.word));
			Ddim_Print(("rlr1        =%lu\n", tmr32Ctrl.rlr1));
			Ddim_Print(("rlr2        =%lu\n", tmr32Ctrl.rlr2));
			Ddim_Print(("soft_counter=%lu\n", tmr32Ctrl.soft_counter));
			Ddim_Print(("pcallback   =%p\n", tmr32Ctrl.pcallback));
		}
		else {
			Ddim_Print(("Dd_TMR32_Get_Ctrl ERR=%d\n", ret));
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
		ret = Dd_TMR32_Set_Softcounter(ch, self->num) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Set_Softcounter[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Set_Softcounter[%d] ERR=%d\n", ch, ret));
		}
	}
	/*------------------*/
	/* Get Soft Counter */
	/*------------------*/
	else if(strcmp(argv[1], "get_softcounter") == 0){
		/* ch number */
		ch  = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		self->num = Dd_TMR32_Get_Softcounter(ch) ;
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
		ret = Dd_TMR32_Set_Reload_Flg(ch, self->num) ;
		if(ret == D_DDIM_OK){
			Ddim_Print(("Dd_TMR32_Set_Reload_Flg[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_Set_Reload_Flg[%d] ERR=%d\n", ch, ret));
		}
	}
	/*-----------------*/
	/* Get Reload Flag */
	/*-----------------*/
	else if(strcmp(argv[1], "get_reload") == 0){
		/* ch number */
		ch  = atoi(argv[2]);

		/* Get H/W & S/W Counter */
		self->num = Dd_TMR32_Get_Reload_Flg(ch) ;
		Ddim_Print(("Reload Flag[%d]=%lu\n", ch, self->num));
	}
	/*---------------------*/
	/* Utility : Set_Timer */
	/*---------------------*/
	else if(strcmp(argv[1], "u_set") == 0){
		ch   = atoi(argv[2]);
		self->usec = (kulong)atoi(argv[3]);
		
		Ddim_Print(("Peri CLK=%lu\n", dd_topone_get_rclk()));
		
		ret = Dd_TMR32_SetTimer(ch, self->usec, ctTimer32Cb);
		if (ret == 0) {
			Ddim_Print(("Dd_TMR32_SetTimer[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_SetTimer[%d] ERR. ret=0x%x\n", ch, ret));
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
		er = ddim_user_custom_get_tim(&S_GDD_TIMER32_TIM1);
		if(er != DdimUserCustom_E_OK){
			Ddim_Print(("get_tim() er=%d\n",er));
		}
#endif	// CO_CT_DD_TMR32_USTIME
		ret = Dd_TMR32_StartReload(ch);
		if (ret == 0) {
			Ddim_Print(("Dd_TMR32_StartReload[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_StartReload[%d] ERR. ret=0x%x\n", ch, ret));
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
		er = ddim_user_custom_get_tim(&S_GDD_TIMER32_TIM1);
		if(er != DdimUserCustom_E_OK){
			Ddim_Print(("get_tim() er=%d\n",er));
		}
#endif	// CO_CT_DD_TMR32_USTIME
		ret = Dd_TMR32_StartOneshot(ch);
		if (ret == 0) {
			Ddim_Print(("Dd_TMR32_StartOneshot[%d] OK\n", ch));
		}
		else {
			Ddim_Print(("Dd_TMR32_StartOneshot[%d] ERR. ret=0x%x\n", ch, ret));
		}
	}
	/*---------------*/
	/* Set Out Level */
	/*---------------*/
	else if(strcmp(argv[1], "set_outlevel") == 0){

		ch   = atoi(argv[2]);

		ret = Dd_TMR32_Set_Outlevel(atoi(argv[3]));
		if (ret == 0) {
			Ddim_Print(("Dd_TMR32_Set_Outlevel[%d] OK\n", ch));
			Ddim_Print(("OUTL = [0x%lx] \n", ioPeri.tmr[3].tmcsr.word));
		}
		else {
			Ddim_Print(("Dd_TMR32_Set_Outlevel[%d] ERR. ret=0x%x\n", ch, ret));
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
		for(chRoop=0; chRoop<D_DD_TMR32_CH_NUM_MAX; chRoop++){
			Ddim_Print(("test_1_all : %d /////////////////////////\n", chRoop));
			/* Open */
			ret = Dd_TMR32_Open(chRoop, 0);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Open[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Open[%d] ERR=%d\n", chRoop, ret));
			}

			/* Calculate */
			Dd_TMR32_Calculate(3000, &tmr32Ctrl);
			/* Ctrl */
			ret = Dd_TMR32_Ctrl(chRoop, &tmr32Ctrl);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Ctrl[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("timer Dd_TMR32_Ctrl[%d] error=%d\n", chRoop, ret));
			}

			/* Start */
			ret = Dd_TMR32_Start(chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Start[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Start[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* Pause */
			ret = Dd_TMR32_Pause(chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Pause[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Pause[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* ReStart */
			ret = Dd_TMR32_Start(chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Start[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Start[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

#ifdef CO_DEBUG_ON_PC
			ioPeri.tmr[chRoop].tmr	= 0x11111111 * (chRoop+1);
#endif	// CO_DEBUG_ON_PC

			/* Get H/W & S/W Counter */
			ret = Dd_TMR32_Get_Counter(chRoop, &hwCount, &swCount);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Get_Counter[%d] OK\n", chRoop));
				Ddim_Print(("H/W counter = 0x%lx, S/W Counter=%lu\n", hwCount, swCount));
			}
			else {
				Ddim_Print(("Dd_TMR32_Get_Counter[%d] ERR=%d\n", chRoop, ret));
			}

			/* Get H/W & S/W Counter */
			ret = Dd_TMR32_Get_Ctrl(chRoop, &tmr32Ctrl) ;
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Get_Ctrl[%d] OK\n", chRoop));
				Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
					chRoop, ioPeri.tmr[chRoop].tmcsr.word));
				Ddim_Print(("csr         =0x%lx\n", tmr32Ctrl.csr.word));
				Ddim_Print(("rlr1        =%lu\n", tmr32Ctrl.rlr1));
				Ddim_Print(("rlr2        =%lu\n", tmr32Ctrl.rlr2));
				Ddim_Print(("soft_counter=%lu\n", tmr32Ctrl.soft_counter));
				Ddim_Print(("pcallback   =%p\n", tmr32Ctrl.pcallback));
			}
			else {
				Ddim_Print(("Dd_TMR32_Get_Ctrl ERR=%d\n", ret));
			}

			/* Stop */
			ret = Dd_TMR32_Stop(chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Stop[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Stop[%d] ERR=%d\n", chRoop, ret));
			}
			Ddim_Print(("Timer32 IO_PERI.TMR[%d].TMCSR.word =[%lx].\n", 
				chRoop, ioPeri.tmr[chRoop].tmcsr.word));

			/* Close */
			ret = Dd_TMR32_Close(chRoop);
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Close[%d] OK\n", chRoop));
			}
			else {
				Ddim_Print(("Dd_TMR32_Close[%d] ERR=%d\n", chRoop, ret));
			}

			/* Check SoftCounter */
			ret = Dd_TMR32_Set_Softcounter(chRoop, (0x11111111*(chRoop+1)));
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Set_Softcounter[%d] OK\n", chRoop));
				Ddim_Print(("Dd_TMR32_Get_Softcounter[%d] %lx\n", 
					chRoop, Dd_TMR32_Get_Softcounter(chRoop)));
			}
			else {
				Ddim_Print(("Dd_TMR32_Set_Softcounter[%d] ERR=%d\n", chRoop, ret));
			}

			/* Check Reload_Flg */
			ret = Dd_TMR32_Set_Reload_Flg(chRoop, (0x11*(chRoop+1))) ;
			if(ret == D_DDIM_OK){
				Ddim_Print(("Dd_TMR32_Set_Reload_Flg[%d] OK\n", chRoop));
				Ddim_Print(("Dd_TMR32_Get_Reload_Flg[%d] %x\n", 
					chRoop, Dd_TMR32_Get_Reload_Flg(chRoop)));
			}
			else {
				Ddim_Print(("Dd_TMR32_Set_Reload_Flg[%d] ERR=%d\n", chRoop, ret));
			}
		}
	}
	else{
		Ddim_Print(("please check 2nd parameter!!\n"));
	}
}

CtDdTmr32 *ct_dd_tmr32_new(void)
{
    CtDdTmr32 *self = k_object_new_with_private(CT_TYPE_DD_TMR32, sizeof(CtDdTmr32Private));
    return self;
}
