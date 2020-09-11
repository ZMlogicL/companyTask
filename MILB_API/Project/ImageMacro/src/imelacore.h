/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李昕
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

#ifndef _IM_ELA_CORE_H_
#define _IM_ELA_CORE_H_

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_ELA_CORE		(im_ela_core_get_type())
#define IM_ELA_CORE(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImElaCore))
#define IM_IS_ELA_CORE(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_ELA_CORE))

typedef struct 				_ImElaCore ImElaCore;
typedef struct 				_ImElaCorePrivate ImElaCorePrivate;

struct _ImElaCore {
	KObject parent;
};

KConstType 		    im_ela_core_get_type(void);
ImElaCore*		        im_ela_core_new(void);

/*----------------------------------------------------------------------*/
/* Function  															*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
//---------------------------- driver section ----------------------------

INT32 im_ela_core_start_core(ImElaCore*self, UINT32 sync );
VOID im_ela_core_on_pclk(ImElaCore*self);
VOID im_ela_core_off_pclk(ImElaCore*self);

/**
The register is set for the ELA macro processing since the second times. <br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks Please specify "1" for "ela_last_flg" at the last ELA macro start. <br>
*/
UINT32 im_ela_core_ctrl_next(ImElaCore*self );

/**
ELA initialize.<br>
@remarks Reset release is done by this function.<br>
*/
VOID im_ela_core_init(ImElaCore*self );

/**
The processing of ELA stop. <br>
@remarks	This API uses DDIM_User_Clr_Flg().
*/
VOID  im_ela_core_stop(ImElaCore*self );

/**
Interruption handler of ELA that starts when the processing of ELA ends. <br>
@remarks This API uses DDIM_User_Set_Flg().
*/
VOID im_ela_core_int_handler(VOID);

#endif	// _IM_ELA_CORE_H_
