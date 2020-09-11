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


#ifndef __IMPRO_SROHRB_H__
#define __IMPRO_SROHRB_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROHRB        (impro_srohrb_get_type())
#define IMPRO_SROHRB(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrohrb))
#define IMPRO_IS_SROHRB(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROHRB))


/*宏定义区域*/
/** @addtogroup im_pro_sro_hrb HRB*/
/**< Minimum setting of HRBV		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBV_MIN			(0)
/**< Maximum setting of HRBV		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBV_MAX			(8190)
/**< Minimum setting of HRBH		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBH_MIN			(0)
/**< Maximum setting of HRBH		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBH_MAX			(16382)
/**< Minimum setting of HRBVW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBVW_MIN			(1)
/**< Maximum setting of HRBVW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBVW_MAX			(8191)
/**< Minimum setting of HRBHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBHW_MIN			(2)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of HRBHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBHW_MAX			(2496)
	/**< Maximum setting of HRBOHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBOHW_MAX			(2496)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of HRBHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBHW_MAX			(2900)
/**< Maximum setting of HRBOHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBOHW_MAX			(2900)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of HRBOHW		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBOHW_MIN			(2)
/**< Minimum setting of HRBSCYC		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MIN		(1)
/**< Maximum setting of HRBSCYC		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MAX		(20)
	/**< Minimum setting of HRBOSM		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MIN			(0)
/**< Maximum setting of HRBOSM		*/
#define	ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MAX			(8191)
/*	@}*/	// im_pro_sro_hrb

/*其他结构体或类型定义区域*/
/** HRB Information
*/
typedef struct {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	/**< Start position of HRB window from a valid VD edge.<br>
	Set the interlace coordinates after 2-line division which is input to HRB/1 core respectively.<br>
	If the value of this register is doubled, it becomes the progressive image coordinates.<br>
	value range :[0 - 16382]<br>
	target registor :@@HRBH	*/
	USHORT			inPosX;
	/**< Start position of HRB window from a valid HD edge.<br>
	value range :[0 - 8190]target registor :@@HRBV	*/
	USHORT			inPosY;
	/**< HRB Horizon INC value range :[2 - 2496] target registor :@@HRBHW */
	USHORT			inWidth;
	/**< HRB Vertical INC value range :[1 - 8191] target registor :@@HRBVW */
	USHORT			inLines;
	/**< HRB Output Horizon INC value range :[2 - 2496] target registor :@@HRBOHW */
	USHORT			outWidth;
	/**< HRB input cycle value range :[0 - 14] target registor :@@HRBSCYC */
	UCHAR				cycle;
	/**< HRB Output Timing value range :[0 - 8191] target registor :@@HRBOSM */
	USHORT			outTiming;
	/**< HRB Offset value range :[0 - 65535(1.999969482)] target registor :@@HRBK_0_0-@@HRBK_19_4		*/
	USHORT			coefficient[20][5];
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/**< Start position of HRB window from a valid VD edge.<br>
	Set the interlace coordinates after 2-line division which is input to HRB/1 core respectively.<br>
	If the value of this register is doubled, it becomes the progressive image coordinates.<br>
	value range :[0 - 16382]<br>
	target registor :@@HRBH	*/
	USHORT			inPosX;
	/**< Start position of HRB window from a valid HD edge.<br>
	value range :[0 - 8190] target registor :@@HRBV	*/
	USHORT			inPosY;
	/**< HRB Horizon INC value range :[2 - 2900] target registor :@@HRBHW */
	USHORT			inWidth;
	/**< HRB Vertical INC value range :[1 - 8191] target registor :@@HRBVW */
	USHORT			inLines;
	/**< HRB Output Horizon INC value range :[2 - 2900] target registor :@@HRBOHW */
	USHORT			outWidth;
	/**< HRB input cycle value range :[0 - 14] target registor :@@HRBSCYC */
	UCHAR				cycle;
	/**< HRB Output Timing value range :[0 - 8191] target registor :@@HRBOSM */
	USHORT			outTiming;
	/**< HRB Offset value range :[0 - 65535(1.999969482)] target registor :@@HRBK_0_0-@@HRBK_19_4		*/
	USHORT			coefficient[20][5];
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
} TimproHrbCtrl;

/*类型定义区域*/
typedef struct _ImproSrohrb					ImproSrohrb;
typedef struct _ImproSrohrbPrivate				ImproSrohrbPrivate;


/*对象结构体区域*/
struct _ImproSrohrb
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srohrb_get_type(void);
ImproSrohrb*			impro_srohrb_new();
/**
Start HRB
@param[in]	unitNo : Unit number.
*/
extern	VOID			impro_srohrb_start( E_IM_PRO_UNIT_NUM unitNo );
/**
Stop HRB
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
extern	VOID			impro_srohrb_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force );
/**
HRB control data setting
@param[in]	unitNo : Unit number.
@param[in]	hrbCtrl : HRB control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srohrbCtrl( E_IM_PRO_UNIT_NUM unitNo, TimproHrbCtrl* hrbCtrl );
/**
A setup of enable access to the built-in RAM of hrb.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srohrb_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );




#endif /* __IMPRO_SROHRB_H__ */

