/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :王睿
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/
#ifndef __INTERRUPT_DEFINE_H__
#define __INTERRUPT_DEFINE_H__

#include "jdspro.h"
#include "im_pro.h"
#include "dd_top.h"

#define	InterruptDefine_D_IM_PRO_INTFLG_CLEAR	(1)				// Clear the PRO interrupt flag

typedef struct {
	ULONG				flgBitmask;		// Bitmask of
	ULONG				enaBitmask;		// Bitmask of
	ULONG				intFact;			// Interrupt factor bitmask.
} TimproIntflgTbl;

typedef struct {
	ULONG	slvsCommonIntf;
	ULONG	slvsIntf[D_IM_PRO_SEN_SLVS_CH_NUM];
	ULONG	slvsLeintf[D_IM_PRO_SEN_SLVS_CH_NUM];
	ULONG	slvsMeintf0[D_IM_PRO_SEN_SLVS_CH_NUM];
	ULONG	slvsMeintf1[D_IM_PRO_SEN_SLVS_CH_NUM];
	ULONG	lvdsIntf0;
	ULONG	lvdsIntf1;
	ULONG	lvdsIntf2;
	ULONG	cmipiIntf1;
	ULONG	cmipiIntf2;
	ULONG	dmipiIntf;
	ULONG	moniIntf;
} TimproSencoreIntFactor;

typedef struct {
	E_IM_PRO_UNIT_NUM			unitNo;
	E_IM_PRO_BLOCK_TYPE			blockType;
	volatile struct io_prch*	regPtr;
} TimproPichIntInfo;           //等着

typedef struct {
	E_IM_PRO_UNIT_NUM			unitNo;
	E_IM_PRO_BLOCK_TYPE			blockType;
	volatile struct io_pwch*	regPtr;
} TimproPwchIntInfo;


/**
from  im_pro_common.h
*/
typedef struct {
	T_CALLBACK_LONG				pCallback;
	ULONG						userParam;
} TimproCallbackInfo;

#endif //__INTERRUPTDEFINE_H__
