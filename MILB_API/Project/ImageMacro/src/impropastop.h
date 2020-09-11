/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __IMPRO_PASTOP_H__
#define __IMPRO_PASTOP_H__


#include <klib.h>
#include "jdspro.h"
#include "im_pro_common.h"
#include "dd_top.h"


#define IMPRO_TYPE_PASTOP        (impro_pastop_get_type())
#define IMPRO_PASTOP(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproPastop))
#define IMPRO_IS_PASTOP(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_PASTOP))


/**宏定义区域*/


/**其他结构体或类型定义区域*/
/** PASTOP Clock Type*/
typedef enum {
	/**< PASCLK		*/
	ImproPastop_E_IM_PRO_PASTOP_CLK_TYPE_PASCLK = 0,
} EimproPastopClkType;

/** Select L or rr pixel side of PD in frame.*/
typedef enum {
	/**< PDAF-L pixel	*/
	ImproPastop_E_IM_PRO_PASTOP_ORG_L_PDAF = 0,
	/**< PDAF-L pixel	*/
	ImproPastop_E_IM_PRO_PASTOP_ORG_R_PDAF,
} EimproPastopOrg;

/** PASTOP Macro Control Information*/
typedef struct {
	/**< Select L or rr pixel side of PD in frame. PASTOPCTL1@@ORG */
	EimproPastopOrg				org;
} TimproPastopCtrl;
// clock control status
static	volatile	ULONG	gIM_PAS_START_Status[1] = {0x00000000};


/*类型定义区域*/
typedef struct _ImproPastop                 							ImproPastop;
typedef struct _ImproPastopPrivate             				ImproPastopPrivate;




/*对象结构体区域*/
struct _ImproPastop
{
	KObject    parent;
};



/*
方法定义区域（公有放在new后面）
*/
KConstType				impro_pastop_get_type(void);
ImproPastop*			impro_pastop_new();
/**
PASTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
extern	VOID			impro_pastop_init( VOID );
/**
PASTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
extern	INT32			impro_pastop_sw_reset( VOID );
/**
PASTOP Macro clock control
@param[in]	clkType	: PASTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_pastop_control_clock(EimproPastopClkType clkType, UCHAR onOff, UCHAR waitSkip );
/**
PASTOP macro control data setting
@param[in]	ctrl : PASTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_pastop_ctrl( TimproPastopCtrl* ctrl );





#endif /* __IMPRO_PASTOP_H__ */

