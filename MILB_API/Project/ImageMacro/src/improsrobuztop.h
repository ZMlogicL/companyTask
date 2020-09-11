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


#ifndef __IMPRO_SROBUZTOP_H__
#define __IMPRO_SROBUZTOP_H__


#include <klib.h>
#include "jdspro.h"
#include "im_pro_common.h"
#include "dd_top.h"


#define IMPRO_TYPE_SROBUZTOP        (impro_srobuztop_get_type())
#define IMPRO_SROBUZTOP(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrobuztop))
#define IMPRO_IS_SROBUZTOP(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROBUZTOP))


/*宏定义区域*/
// --- REMOVE_BUZ BEGIN
// @cond
/** @addtogroup im_pro_sro_buztop BUZTOP*/
	/**< Minimum setting of BUZV		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZV_MIN			(0)
/**< Maximum setting of BUZV		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZV_MAX			(16382)
/**< Minimum setting of BUZH		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZH_MIN			(0)
/**< Maximum setting of BUZH		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZH_MAX			(4095)
	/**< Minimum setting of BUZVW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZVW_MIN			(2)
/**< Maximum setting of BUZVW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZVW_MAX			(4094)
/**< Minimum setting of BUZHW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZHW_MIN			(1)
	/**< Maximum setting of BUZHW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZHW_MAX			(4095)
	/**< Minimum setting of BUZOHW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZOHW_MIN			(1)
/**< Maximum setting of BUZOHW		*/
#define	ImproSrobuztop_D_IM_PRO_BUZ_BUZOHW_MAX			(4095)
// im_pro_sro_buztop

/*其他结构体或类型定义区域*/
/** PRO Bayer resize select.
*/
typedef enum {
	/**< Using HRB/VRB resizer	*/
	ImproSrobuztop_E_IM_PRO_BUZTOP_SEL_HRB_VRB = 0,
	/**< Using BUZTOP(Buzzard) resizer	*/
	ImproSrobuztop_E_IM_PRO_BUZTOP_SEL_BUZTOP,
	/**< MAX value	*/
	ImproSrobuztop_E_IM_PRO_BUZTOP_SEL_MAX,
} EimproBuztopSel;

/** BUZTOP Information
*/
typedef struct {
	/**< Start position of BUZTOP window from a valid VD edge. Set the interlace coordinates after
	 *  2-line division which is input to BUZTOP0/1 core respectively. If the value of this register is
	 *  doubled, it becomes the progressive image coordinates.
	 *   value range :[0 - 4095] target registor :@@BUZH	*/
	USHORT			inPosX;
	/**< Start position of BUZTOP window from a valid HD edge. value range :[0 - 16382] target registor :@@BUZV	*/
	USHORT			inPosY;
	/**< BUZTOP Horizon INC value range :[1 - 4095] target registor :@@BUZHW */
	USHORT			inWidth;
	/**< BUZTOP Vertical INC value range :[2 - 4094] target registor :@@BUZVW */
	USHORT			inLines;
	/**< BUZTOP Output Horizon INC value range :[1 - 4095] target registor :@@BUZOHW */
	USHORT			outWidth;
} TimproBuztopCtrl;

/*类型定义区域*/
typedef struct _ImproSrobuztop							ImproSrobuztop;
typedef struct _ImproSrobuztopPrivate				ImproSrobuztopPrivate;


/*对象结构体区域*/
struct _ImproSrobuztop
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srobuztop_get_type(void);
ImproSrobuztop*	impro_srobuztop_new();
/**
Software reset of BUZTOP macro.
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_srobuztop_sr( E_IM_PRO_UNIT_NUM unitNo );
/**
Software reset release of BUZTOP.
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
extern	INT32			impro_srobuztop_sr_rlease( E_IM_PRO_UNIT_NUM unitNo );
/**
BUZTOP control data setting
@param[in]	unitNo : Unit number.
@param[in]	buzCtrl : BUZTOP control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srobuztop_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproBuztopCtrl* buzCtrl );
/**
A setup of enable access to the built-in RAM of BUZTOP.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srobuztop_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );
/**
A setup of Resizer select.
@param[in]	unitNo : Unit number.
@param[in]	sel     : Raw resizer select.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srobuztop_set_resizer_sel( E_IM_PRO_UNIT_NUM unitNo, EimproBuztopSel sel );






#endif /* __IMPRO_SROBUZTOP_H__ */

