/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdSpiJudge类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_JUDGE_H__
#define __CT_DD_SPI_JUDGE_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_JUDGE					(ct_dd_spi_judge_get_type())
#define CT_DD_SPI_JUDGE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiJudge)) 
#define CT_IS_DD_SPI_JUDGE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_JUDGE))

#define CtDdSpiJudge_SPI_CH_MAX			(3)

typedef struct 												_CtDdSpiJudge CtDdSpiJudge;
typedef struct 												_CtDdSpiJudgePrivate CtDdSpiJudgePrivate;

typedef enum {
	CtDdSpiJudge_SPI_TRNAS_TYPE_SEND = 0,
	CtDdSpiJudge_SPI_TRNAS_TYPE_RECV,
	CtDdSpiJudge_SPI_TRNAS_TYPE_FULL,
} CtDdSpiJudgeSpiTransType;

struct _CtDdSpiJudge
{
	KObject parent;
	kint32 ret;
	kuint32 val;
	kuint32 index;
	kint32 tmout;
	kuchar ch;
	kuchar dmaCh[2];
	kuchar clkDiv;
	kchar* endstr;
	kulong baudrate;
	TDdSpiCtrl spiCtrl;
	DdSpiSsInfo	ssInfo;
	DdSpiEnableSig enableSig;
	kboolean enable;
	CtDdSpiJudgePrivate *priv;
};

KConstType 							ct_dd_spi_judge_get_type(void);
CtDdSpiJudge*	 					ct_dd_spi_judge_new(void);

CtDdSpiJudgeSpiTransType 	ct_dd_spi_judge_get_trans_type(void);
void 										ct_dd_spi_judge_set_trans_type(CtDdSpiJudgeSpiTransType newtype);
void 										ct_dd_spi_judge_main( CtDdSpiJudge *self, CtDdSpiTest * test,kint argc, kchar** argv );

#endif /* __CT_DD_SPI_JUDGE_H__ */
