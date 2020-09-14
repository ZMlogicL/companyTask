/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdTmr64类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
/**
 * @file		ct_dd_tmr64.c
 * @brief		This is ct code for dd_tmr64
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "ddtmr64.h"
#include "ddhdmac1.h"
#include "peripheral.h"
#include "chiptop.h"
#include <stdlib.h>
#include <string.h>
#include "ctddtmr64.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdTmr64, ct_dd_tmr64);
#define CT_DD_TMR64_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTmr64Private,CT_TYPE_DD_TMR64))

struct _CtDdTmr64Private {
    kint i;
};

static void ct_dd_tmr64_constructor(CtDdTmr64 *self) 
{
    // CtDdTmr64Private *priv = CT_DD_TMR64_GET_PRIVATE(self);
}

static void ct_dd_tmr64_destructor(CtDdTmr64 *self)
{
    // CtDdTmr64Private *priv = CT_DD_TMR64_GET_PRIVATE(self);
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CO_DEBUG_ON_PC

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for timer64 test.
 * @param  int argc		:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 */
void ct_dd_tmr64_main(CtDdTmr64 *self, kint argc, KType* argv)
{
	TDdTmr64Ctrl		tmr64Ctrl = {{0}};
	DdTmr64 *			ddTmr64 = dd_tmr64_get();
	DdimUserCustom *	ddimUserCus = ddim_user_custom_new();

	/*-------*/
	/* Open  */
	/*-------*/
	// ddtmr64 open [tmout]
	if(strcmp(argv[1], "open") == 0){
		/* Open */
		self->ret = dd_tmr64_open(ddTmr64, (kint32)atoi(argv[2]));
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_open OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_open ERR=%d\n", self->ret));
		}
	}
	/*-------*/
	/* close */
	/*-------*/
	// ddtmr64 close
	else if(strcmp(argv[1], "close") == 0){
		/* Stop */
		self->ret = dd_tmr64_close(ddTmr64);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_close OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_close ERR=%d\n", self->ret));
		}
	}
	/*------*/
	/* Ctrl */
	/*------*/
	// ddtmr64 ctrl [trg] [cnte] [csl] [cvt] [tsen]
	else if(strcmp(argv[1], "ctrl") == 0){
		// trg
		if(strcmp(argv[2], "1") == 0){
			tmr64Ctrl.csr1.bit.trg = 1;
		}
		else {
			tmr64Ctrl.csr1.bit.trg = 0;
		}

		// cnte
		if(strcmp(argv[3], "1") == 0){
			tmr64Ctrl.csr1.bit.cnte = 1;
		}
		else {
			tmr64Ctrl.csr1.bit.cnte = 0;
		}

		// csl
		if(strcmp(argv[4], "32") == 0){
			tmr64Ctrl.csr1.bit.csl = 2;
		}
		else if(strcmp(argv[4], "8") == 0){
			tmr64Ctrl.csr1.bit.csl = 1;
		}
		else if(strcmp(argv[4], "2") == 0){
			tmr64Ctrl.csr1.bit.csl = 0;
		}
		else {
			tmr64Ctrl.csr1.bit.csl = 0;
		}

		// cvt
		if(strcmp(argv[5], "1") == 0){
			tmr64Ctrl.csr2.bit.cvt = 1;
		}
		else {
			tmr64Ctrl.csr2.bit.cvt = 0;
		}

		// tsen
		if(strcmp(argv[6], "1") == 0){
			tmr64Ctrl.csr2.bit.tsen = 1;
		}
		else {
			tmr64Ctrl.csr2.bit.tsen = 0;
		}

		Ddim_Print(("--dd_tmr64_ctrl()--\n"));
		Ddim_Print(("tmr64Ctrl.csr1.bit.trg  = %d\n", tmr64Ctrl.csr1.bit.trg));
		Ddim_Print(("tmr64Ctrl.csr1.bit.cnte = %d\n", tmr64Ctrl.csr1.bit.cnte));
		Ddim_Print(("tmr64Ctrl.csr1.bit.csl  = %d\n", tmr64Ctrl.csr1.bit.csl));
		Ddim_Print(("tmr64Ctrl.csr2.bit.cvt  = %d\n", tmr64Ctrl.csr2.bit.cvt));
		Ddim_Print(("tmr64Ctrl.csr2.bit.tsen = %d\n", tmr64Ctrl.csr2.bit.tsen));
		Ddim_Print(("-------------------\n"));

		/* Ctrl */
		self->ret = dd_tmr64_ctrl(ddTmr64, &tmr64Ctrl);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_ctrl OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_ctrl ERR=%d\n", self->ret));
		}
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_1.word = [0x%08lx]\n", ioPeri.tmr64.tmcsr641.word));
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_2.word = [0x%08lx]\n", ioPeri.tmr64.tmcsr642.word));
	}
	else if(strcmp(argv[1], "get_ctrl") == 0){
#ifdef CO_DEBUG_ON_PC
		ioPeri.tmr64.tmcsr641.word	= 0x00000800;
		ioPeri.tmr64.tmcsr642.word	= 0x00010001;
#endif	// CO_DEBUG_ON_PC

		/* Get H/W & S/W Counter */
		self->ret = dd_tmr64_get_ctrl(ddTmr64, &tmr64Ctrl) ;
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_ctrl OK\n"));
			Ddim_Print(("IO_PERI.TMR64.TMCSR64_1.word = [0x%08lx]\n", ioPeri.tmr64.tmcsr641.word));
			Ddim_Print(("IO_PERI.TMR64.TMCSR64_2.word = [0x%08lx]\n", ioPeri.tmr64.tmcsr642.word));
			Ddim_Print(("tmr64Ctrl.csr1.word        = [0x%08lx]\n", tmr64Ctrl.csr1.word));
			Ddim_Print(("tmr64Ctrl.csr2.word        = [0x%08lx]\n", tmr64Ctrl.csr2.word));
		}
		else {
			Ddim_Print(("dd_tmr64_get_ctrl ERR=%d\n", self->ret));
		}
	}
	/*----------------*/
	/* Start / Resume */
	/*----------------*/
	else if(strcmp(argv[1], "start") == 0){
		/* Start */
		self->ret = dd_tmr64_start(ddTmr64, atoi(argv[2]));

		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_start OK\n"));

			self->ret = ddim_user_custom_get_tim(ddimUserCus, &self->systim);
			if (self->ret != DdimUserCustom_E_OK) {
				Ddim_Print(("ddim_user_custom_get_tim ERR=%d\n", self->ret));
			}
			else {
				Ddim_Print(("System time = %llu ms.\n", self->systim));
			}
		}
		else {
			Ddim_Print(("dd_tmr64_start ERR=%d\n", self->ret));
		}
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_1.word =[0x%08lx].\n", ioPeri.tmr64.tmcsr641.word));
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_2.word =[0x%08lx].\n", ioPeri.tmr64.tmcsr641.word));
	}
	/*------*/
	/* Stop */
	/*------*/
	else if(strcmp(argv[1], "stop") == 0){
#ifdef CO_DEBUG_ON_PC
		dd_tmr64_start(ddTmr64, TRUE);
#endif	// CO_DEBUG_ON_PC

		/* Stop */
		self->ret = dd_tmr64_stop(ddTmr64);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_stop OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_stop ERR=%d\n", self->ret));
		}
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_1.word =[0x%08lx].\n", ioPeri.tmr64.tmcsr641.word));
		Ddim_Print(("IO_PERI.TMR64.TMCSR64_2.word =[0x%08lx].\n", ioPeri.tmr64.tmcsr641.word));
	}
	/*-------------------------*/
	/* Get TMR64 Counter value */
	/*-------------------------*/
	else if(strcmp(argv[1], "get_counter") == 0){
		kulonglong	counter;

#ifdef CO_DEBUG_ON_PC
		ioPeri.tmr64.tmr64L	= 0x13572468;
		ioPeri.tmr64.tmr64H	= 0x24681357;
#endif	// CO_DEBUG_ON_PC

		/* Get H/W & S/W Counter */
		self->ret = dd_tmr64_get_counter(ddTmr64, &counter);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_counter OK\n"));
			Ddim_Print(("Counter = 0x%llX\n", counter));
			self->ret = ddim_user_custom_get_tim(ddimUserCus, &self->systim);
			if (self->ret != DdimUserCustom_E_OK) {
				Ddim_Print(("ddim_user_custom_get_tim ERR=%d\n", self->ret));
			}
			else {
				Ddim_Print(("System time = %llu ms.\n", self->systim));
			}
		}
		else {
			Ddim_Print(("dd_tmr64_get_counter ERR=%d\n", self->ret));
		}
	}
	/*--------------------------------------*/
	/* Get TMR Register and Gryo Time Stamp */
	/*--------------------------------------*/
	else if(strcmp(argv[1], "get_gyro") == 0){
		kulong	timeStamp ;

#ifdef CO_DEBUG_ON_PC
		ioPeri.tmr64.GSTMP = 0xAAAAAAAA;
#endif	// CO_DEBUG_ON_PC

		/* Get Time Stamp */
		self->ret = dd_tmr64_get_gyro_time_stamp(ddTmr64, &timeStamp);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_gyro_time_stamp OK\n"));
			Ddim_Print(("timeStamp = 0x%lX\n", timeStamp));
		}
		else {
			Ddim_Print(("dd_tmr64_get_gyro_time_stamp ERR=%d\n", self->ret));
		}
	}
	/*---------------------------------------------*/
	/* Get TMR Register and Frame Start Time Stamp */
	/*---------------------------------------------*/
	else if(strcmp(argv[1], "get_start") == 0){
		kuint32		sensorNo;
		kuint32		lotationCount;
		kulonglong	timeStamp;

// ToDo: Set data for PC Debug

		Ddim_Print(("--dd_tmr64_get_frame_start_time_stamp()--\n"));
		for (sensorNo = 0; sensorNo < 4; sensorNo ++) {
			for (lotationCount = 0; lotationCount < 3; lotationCount ++) {   // Strange???? Change?????
				/* Get Counter */
				self->ret = dd_tmr64_get_frame_start_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
				if(self->ret == D_DDIM_OK){
					Ddim_Print(("TimeStamp[%d][%d] = 0x%llX\n", 
						sensorNo, lotationCount, timeStamp));
				}
				else {
					Ddim_Print(("TimeStamp[%d][%d] = ERR\n", sensorNo, lotationCount));
				}
			}
		}
		Ddim_Print(("---------------------------------------\n"));
	}
	/*-------------------------------------------*/
	/* Get TMR Register and Frame End Time Stamp */
	/*-------------------------------------------*/
	else if(strcmp(argv[1], "get_end") == 0){
		kuint32		sensorNo;
		kuint32		lotationCount;
		kulonglong	timeStamp;

// ToDo: Set data for PC Debug

		Ddim_Print(("--dd_tmr64_get_frame_end_time_stamp()--\n"));
		for (sensorNo = 0; sensorNo < 4; sensorNo ++) {
			for (lotationCount = 0; lotationCount < 3; lotationCount ++) {
				/* Get Counter */
				self->ret = dd_tmr64_get_frame_end_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
				if(self->ret == D_DDIM_OK){
					Ddim_Print(("TimeStamp[%d][%d] = 0x%llX\n", 
						sensorNo, lotationCount, timeStamp));
				}
				else {
					Ddim_Print(("TimeStamp[%d][%d] = ERR\n", sensorNo, lotationCount));
				}
			}
		}
		Ddim_Print(("-------------------------------------\n"));
	}
	/*-------------------*/
	/* Init Gyro trigger */
	/*-------------------*/
	else if(strcmp(argv[1], "gyro_init") == 0){
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
		ioChiptop.eprc.bit.PB4 = 0;	// SPIRLTRG
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
		ioChiptop.eprc.bit.TRGEN = 0;	// SPIRLTRG
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
		ioChiptop.ddr.bit.pb4 = 0;		// SPIRLTRG

//		ioChiptop.EPCR.bit.PF3 = 0;
		ioChiptop.ddr.bit.pf3 = 1;
		ioChiptop.pdr.bit.pf3 = 0;
	}
	/*----------------------*/
	/* Set Gyro trigger ON  */
	/*----------------------*/
	else if(strcmp(argv[1], "gyro_trg_on") == 0){
		ioChiptop.pdr.bit.pf3 = 1;		// ToDo

		self->ret = ddim_user_custom_get_tim(ddimUserCus, &self->systim);
		if (self->ret != DdimUserCustom_E_OK) {
			Ddim_Print(("ddim_user_custom_get_tim ERR=%d\n", self->ret));
		}
		else {
			Ddim_Print(("System time = %llu ms.\n", self->systim));
		}
	}
	/*----------------------*/
	/* Set Gyro trigger OFF  */
	/*----------------------*/
	else if(strcmp(argv[1], "gyro_trg_off") == 0){
		ioChiptop.pdr.bit.pf3 = 0;
	}
	/*----------*/
	/* test 2-1 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_1") == 0){
		self->ret = dd_tmr64_open(ddTmr64, 0);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_open OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_open ERR=0x%08x\n", self->ret));
		}

		self->ret = dd_tmr64_open(ddTmr64, 0);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_open OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_open ERR=0x%08x\n", self->ret));
		}

		self->ret = dd_tmr64_close(ddTmr64);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_close OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_close ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-2 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_2") == 0){
		self->ret = dd_tmr64_open(ddTmr64, -2);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_open OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_open ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-3 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_3") == 0){
		kint32 sidBack;

		sidBack = SID_DD_TMR64;
		SID_DD_TMR64 = 0xfff;

		self->ret = dd_tmr64_open(ddTmr64, 0);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_open OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_open ERR=0x%08x\n", self->ret));
		}

		SID_DD_TMR64 = sidBack;
	}
	/*----------*/
	/* test 2-4 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_4") == 0){
		kint32 sidBack;

		sidBack = SID_DD_TMR64;
		SID_DD_TMR64 = 0xfff;

		self->ret = dd_tmr64_close(ddTmr64);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_close OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_close ERR=0x%08x\n", self->ret));
		}

		SID_DD_TMR64 = sidBack;
	}
	/*----------*/
	/* test 2-5 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_5") == 0){
		self->ret = dd_tmr64_ctrl(ddTmr64, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_ctrl OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_ctrl ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-6 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_6") == 0){
		self->ret = dd_tmr64_get_gyro_time_stamp(ddTmr64, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_gyro_time_stamp OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_gyro_time_stamp ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-7 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_7") == 0){
		kuint32		sensorNo		= 0;
		kuint32		lotationCount	= 0;
		kulonglong	timeStamp;

		// timeStamp is null
		self->ret = dd_tmr64_get_frame_start_time_stamp(ddTmr64, sensorNo, lotationCount, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp ERR=0x%08x\n", self->ret));
		}

		// sensorNo is over
		sensorNo		= 4;
		lotationCount	= 0;
		self->ret = dd_tmr64_get_frame_start_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp ERR=0x%08x\n", self->ret));
		}

		// lotationCount is over
		sensorNo		= 0;
		lotationCount	= 4;
		self->ret = dd_tmr64_get_frame_start_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_start_time_stamp ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-8 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_8") == 0){
		kuint32		sensorNo		= 0;
		kuint32		lotationCount	= 0;
		kulonglong	timeStamp;

		// timeStamp is null
		self->ret = dd_tmr64_get_frame_end_time_stamp(ddTmr64, sensorNo, lotationCount, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp ERR=0x%08x\n", self->ret));
		}

		// sensorNo is over
		sensorNo		= 4;
		lotationCount	= 0;
		self->ret = dd_tmr64_get_frame_end_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp ERR=0x%08x\n", self->ret));
		}

		// lotationCount is over
		sensorNo		= 0;
		lotationCount	= 4;
		self->ret = dd_tmr64_get_frame_end_time_stamp(ddTmr64, sensorNo, lotationCount, &timeStamp);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp OK"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_frame_end_time_stamp ERR=0x%08x\n", self->ret));
		}
	}
	/*----------*/
	/* test 2-9 */
	/*----------*/
	else if(strcmp(argv[1], "test_2_9") == 0){
		// counter is null
		self->ret = dd_tmr64_get_counter(ddTmr64, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_counterOK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_counter ERR=0x%08x\n", self->ret));
		}
	}
	/*-----------*/
	/* test 2-10 */
	/*-----------*/
	else if(strcmp(argv[1], "test_2_10") == 0){
		self->ret = dd_tmr64_get_ctrl(ddTmr64, NULL);
		if(self->ret == D_DDIM_OK){
			Ddim_Print(("dd_tmr64_get_ctrl OK\n"));
		}
		else {
			Ddim_Print(("dd_tmr64_get_ctrl ERR=0x%08x\n", self->ret));
		}
	}
	else{
		Ddim_Print(("please check 2nd parameter!!\n"));
	}
	k_object_unref(ddTmr64);
	ddTmr64 = NULL;
	k_object_unref(ddimUserCus);
	ddimUserCus = NULL;
}

CtDdTmr64 *ct_dd_tmr64_new(void)
{
    CtDdTmr64 *self = k_object_new_with_private(CT_TYPE_DD_TMR64, sizeof(CtDdTmr64Private));
    return self;
}
