/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-02
*@author              	:杨升柄
*@brief               	:CtDdCsioProcess类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_CSIO_PROCESS_H__
#define __CT_DD_CSIO_PROCESS_H__

#include <klib.h>

#define CT_TYPE_DD_CSIO_PROCESS					(ct_dd_csio_process_get_type())
#define CT_DD_CSIO_PROCESS(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCsioProcess)) 
#define CT_IS_DD_CSIO_PROCESS(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_CSIO_PROCESS))

typedef struct 			_CtDdCsioProcess CtDdCsioProcess;
typedef struct 			_CtDdCsioProcessPrivate CtDdCsioProcessPrivate;

struct _CtDdCsioProcess
{
	KObject parent;
	CtDdCsioProcessPrivate *priv;

};

KConstType 			ct_dd_csio_process_get_type(void);
CtDdCsioProcess* 	ct_dd_csio_process_new(void);

//静态方法转公有
kint32 						ct_dd_csio_process_test(CtDdCsioProcess* self, kuchar ch, kuchar num);
void 						ct_dd_csio_process_set_csio(CtDdCsioProcess* self, CtDdCsio *cdCsio);

#endif /* __CT_DD_CSIO_PROCESS_H__ */
