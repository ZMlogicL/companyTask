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


#ifndef __IMPRO_SENOBD_H__
#define __IMPRO_SENOBD_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENOBD        (impro_senobd_get_type())
#define IMPRO_SENOBD(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSenobd))
#define IMPRO_IS_SENOBD(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENOBD))


/*宏定义区域*/
/** @addtogroup im_pro_sen_obd OBD*/
/**< Minimum setting of OBDV	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDV_MIN			(0)
/**< Maximum setting of OBDV	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDV_MAX			(8191)
/**< Minimum setting of OBDH	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDH_MIN			(0)
/**< Maximum setting of OBDH	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDH_MAX			(12287)
/**< Minimum setting of OBDVW	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDVW_MIN			(2)
/**< Maximum setting of OBDVW	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDVW_MAX			(8192)
/**< Minimum setting of OBDHW	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDHW_MIN			(2)
/**< Maximum setting of OBDHW	*/
#define	ImproSenobd_D_IM_PRO_OBD_OBDHW_MAX			(12288)


/*其他结构体或类型定义区域*/
/** PRO OB Control information*/
typedef struct {
	/**< OB Input upper threshold value value range		:[0 - 16383] target registor	:@@OBDHTHBIT */
	USHORT				obMaxValue;
	/**< OB Input lower threshold value value range		:[0 - 16383] target registor	:@@OBDLTHBIT */
	USHORT				obMinValue;
} TimproObdCtrl;

/** PRO Get RGB ULONG data*/
typedef struct {
	/**< rr		*/
	ULONG				rr;
	/**< gr		*/
	ULONG				gr;
	/**< gb		*/
	ULONG				gb;
	/**< bb		*/
	ULONG				bb;
} TimproRgb4;
/*类型定义区域*/
typedef struct _ImproSenobd							ImproSenobd;
typedef struct _ImproSenobdPrivate				ImproSenobdPrivate;


/*对象结构体区域*/
struct _ImproSenobd
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_senobd_get_type(void);
ImproSenobd*		impro_senobd_new();
/**
Start OBD
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobd_start( E_IM_PRO_OBD_CH ch );
/**
Stop OBD
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobd_stop( E_IM_PRO_OBD_CH ch, UCHAR force );
/**
The control parameter of OBD compensation is set.
@param[in]	ch : Channel No.
@param[in]	obCtrl	:	OBD Control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_senobd_ctrl( E_IM_PRO_OBD_CH ch, TimproObdCtrl* obCtrl );
/**
The area for OBD detection is set up.
@param[in]	ch : Channel No.
@param[in]	obArea	:The area for OB detection<br>
					value range :posX[0 - 12287]<br>
					target registor :@@OBDH<br>
					value range :posY[0 - 8191]<br>
					target registor :@@OBDV<br>
					value range :width[2 - 12288] 2pixel boundary<br>
					target registor :@@OBDHW<br>
					value range :lines[2 - 8192] 2pixel boundary<br>
					target registor :@@OBDVW<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_senobd_set_area( E_IM_PRO_OBD_CH ch, T_IM_PRO_AREA_INFO* obArea );
/**
Get OBD count
@param[in]	ch : Channel No.
@param[out]	obcnt :	OBCNT<br>
			each colors count value range :0 - 0xFFFFF<br>
@retval		D_DDIM_OK					: Getting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
extern	INT32			impro_senobd_get_ob_cnt( E_IM_PRO_OBD_CH ch, TimproRgb4* obcnt );
/**
Get OBD data
@param[in]	ch : Channel No.
@param[out]	obdata : OBD Data
@retval		D_DDIM_OK					: Getting OK
@retval		D_IM_PRO_NG					: Getting NG
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
extern	INT32			impro_senobd_get_ob_data( E_IM_PRO_OBD_CH ch, TimproRgb4* obdata );


#endif /* __IMPRO_SENOBD_H__ */

