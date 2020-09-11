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


#ifndef __IMPRO_SROVRB_H__
#define __IMPRO_SROVRB_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROVRB        (impro_srovrb_get_type())
#define IMPRO_SROVRB(obj)       	(K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrovrb))
#define IMPRO_IS_SROVRB(obj)    	(K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROVRB))


/*宏定义区域*/
/** @addtogroup im_pro_sro_vrb VRB*/
	/**< Minimum setting of VRBV		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBV_MIN					(0)
/**< Maximum setting of VRBV		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBV_MAX					(8190)
/**< Minimum setting of VRBH		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBH_MIN					(0)
/**< Maximum setting of VRBH		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBH_MAX					(16382)
	/**< Minimum setting of VRBVW		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBVW_MIN					(1)
/**< Maximum setting of VRBVW		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBVW_MAX					(8191)
/**< Minimum setting of VRBHW		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBHW_MIN					(2)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of VRBHW		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBHW_MAX				(2496)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of VRBHW		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBHW_MAX				(2900)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of VRBSCYC		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MIN				(1)
/**< Maximum setting of VRBSCYC		*/
#define	ImproSrovrb_D_IM_PRO_VRB_VRBSCYC_MAX				(10)
/*	@}*/	// im_pro_sro_vrb

/*其他结构体或类型定义区域*/
/** VRB Information
*/
typedef struct {
	/**< Start position of VRB window from a valid VD edge.<br>
	Set the interlace coordinates after 2-line division which is input to VRB0/1 core respectively.<br>
	If the value of this register is doubled, it becomes the progressive image coordinates.<br>
	value range :[0 - 16382] target registor :@@VRBH	*/
	USHORT			inPosX;
	/**< Start position of VRB window from a valid HD edge.<br>
	value range :[0 - 8190] 2pixel boundary. target registor :@@VRBV	*/
	USHORT			inPosY;
	/**< VRB Horizon INC<br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
											value range :[2 - 2496]<br>
	// --- REMOVE_ES1_HARDWARE END ---
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES1_HARDWARE
	#ifdef CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES3_HARDWARE BEGIN ---
											value range :[2 - 2900]<br>
	// --- REMOVE_ES3_HARDWARE END --
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif	// CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	target registor :@@VRBHW */
	USHORT			inWidth;
	/**< VRB Vertical INC value range :[1 - 8191] target registor :@@VRBVW */
	USHORT			inLines;
	/**< VRB input cycle value range :[1 - 10] target registor :@@VRBSCYC */
	UCHAR				cycle;
	/**< VRB0 Input Offset value range :[0 - 65535(1.999969482)] target registor :@@VRB0K_0_0-@@VRB0K_9_2		*/
	USHORT			coefficient0[10][3];
	/**< VRB1 Input Offset value range :[0 - 65535(1.999969482)] target registor :@@VRB1K_0_0-@@VRB1K_9_2		*/
	USHORT			coefficient1[10][3];
} TimproVrbCtrl;

/*类型定义区域*/
typedef struct _ImproSrovrb							ImproSrovrb;
typedef struct _ImproSrovrbPrivate				ImproSrovrbPrivate;


/*对象结构体区域*/
struct _ImproSrovrb
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srovrb_get_type(void);
ImproSrovrb*			impro_srovrb_new();
/**
Start VRB
@param[in]	unitNo : Unit number.
*/
extern	VOID			impro_srovrb_start( E_IM_PRO_UNIT_NUM unitNo );
/**
Stop VRB
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
extern	VOID			impro_srovrb_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force );
/**
VRB control data setting
@param[in]	unitNo : Unit number.
@param[in]	vrb_ctrl : VRB control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srovrb_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproVrbCtrl* vrb_ctrl );
/**
A setup of enable access to the built-in RAM of vrb.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srovrb_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );





#endif /* __IMPRO_SROVRB_H__ */

