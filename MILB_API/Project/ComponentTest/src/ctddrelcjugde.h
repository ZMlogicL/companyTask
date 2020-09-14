/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdRelcJugde类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_RELC_JUGDE_H__
#define __CT_DD_RELC_JUGDE_H__

#include <klib.h>

#define CT_TYPE_DD_RELC_JUGDE					(ct_dd_relc_jugde_get_type())
#define CT_DD_RELC_JUGDE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdRelcJugde)) 
#define CT_IS_DD_RELC_JUGDE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_RELC_JUGDE))

typedef struct 													_CtDdRelcJugde CtDdRelcJugde;
typedef struct 													_CtDdRelcJugdePrivate CtDdRelcJugdePrivate;

struct _CtDdRelcJugde
{
	KObject parent;
	kint32 ret;
	TDdRelcCtrlCmn ctrlCom;
	TDdRelcCtrlReg ctrlReg;
	TDdRelcCtrlDesc ctrlDesc;
	TDdRelcSetModNormal setModNorm;
	TDdRelcSetModDesc setModDesc;
	TDdRelcDecInfo decInfo;
	kulong setAddr;
	kuint32 setSize;
	kushort inBufSize;
	kushort	refBufSize;
	kuchar testNum;
	kchar* endstr;
	kchar* hprot;
	kulong writeHprot;
	kulong readHprot;
#ifdef PC_DEBUG
	kulong testPat;
#endif
	CtDdRelcJugdePrivate *priv;
};

KConstType 			ct_dd_relc_jugde_get_type(void);
CtDdRelcJugde* 		ct_dd_relc_jugde_new(void);

void 						ct_dd_relc_buffer_dump( void );
void 						ct_dd_relc_judge(CtDdRelcJugde *self,kint argc, kchar** argv );
DdRelc* 				ct_dd_relc_judge_get_ddrelc(CtDdRelcJugde* self);
#endif /* __CT_DD_RELC_JUGDE_H__ */
