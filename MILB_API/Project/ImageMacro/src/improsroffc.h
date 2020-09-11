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


#ifndef __IMPRO_SROFFC_H__
#define __IMPRO_SROFFC_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROFFC        (impro_sroffc_get_type())
#define IMPRO_SROFFC(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSroffc))
#define IMPRO_IS_SROFFC(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROFFC))


/*宏定义区域*/
/** @addtogroup im_pro_sro_ffc FFC*/
/**< Minimum setting of FCV			*/
#define	ImproSroffc_D_IM_PRO_FFC_FCV_MIN			(2)
/**< Maximum setting of FCV			*/
#define	ImproSroffc_D_IM_PRO_FFC_FCV_MAX			(8960)
/**< Minimum setting of FCH			*/
#define	ImproSroffc_D_IM_PRO_FFC_FCH_MIN			(0)
/**< Maximum setting of FCH			*/
#define	ImproSroffc_D_IM_PRO_FFC_FCH_MAX			(4095)
/**< Minimum setting of FCVW		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCVW_MIN			(4)
	/**< Maximum setting of FCVW		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCVW_MAX			(8960)
/**< Minimum setting of FCHW		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCHW_MIN			(4)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FCHW		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCHW_MAX			(2496)
/**< Maximum setting of FCSUBPRH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBPRH_MAX		(314)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FCHW		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCHW_MAX			(2900)
/**< Maximum setting of FCSUBPRH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBPRH_MAX		(366)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of FCSUBPRH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBPRH_MIN		(4)
	/**< Minimum setting of FCSUBPRV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBPRV_MIN		(4)
/**< Maximum setting of FCSUBPRV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBPRV_MAX		(1122)
/**< Minimum setting of FCSUBSPH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSPH_MIN		(16)
/**< Maximum setting of FCSUBSPH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSPH_MAX		(724)
	/**< Minimum setting of FCSUBSPV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSPV_MIN		(16)
	/**< Maximum setting of FCSUBSPV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSPV_MAX		(724)
/**< Minimum setting of FCSUBSTH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSTH_MIN		(0)
/**< Maximum setting of FCSUBSTH	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSTH_MAX		(722)
/**< Minimum setting of FCSUBSTV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSTV_MIN		(0)
/**< Maximum setting of FCSUBSTV	*/
#define	ImproSroffc_D_IM_PRO_FFC_FCSUBSTV_MAX		(722)
/**< Minimum setting of FCWRIC		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCWRIC_MIN			(4)
/**< Maximum setting of FCWRIC		*/
#define	ImproSroffc_D_IM_PRO_FFC_FCWRIC_MAX			(1023)
/*	@}*/	// im_pro_sro_ffc

/*其他结构体或类型定义区域*/
/** PRO FFC Control information
*/
typedef struct {
	/**< Frame correction coefficient horizontal size<br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
															value range		:[4 - 314] 2pixel boundary<br>
	// --- REMOVE_ES1_HARDWARE END ---
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES1_HARDWARE
	#ifdef CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES3_HARDWARE BEGIN ---
															value range		:[4 - 366] 2pixel boundary<br>
	// --- REMOVE_ES3_HARDWARE END --
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif	// CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	target registor	:@@FCSUBPRH	*/
	USHORT					coefHorizontalSize;
	/**< Frame correction coefficient vertical size value range
	 * :[4 - 1122] 2pixel boundary target registor	:@@FCSUBPRV	*/
	USHORT					coefVorizontalSize;
	/**< Frame correction interpolation horizontal pixels unit value range
:[16 - 724] 2pixel boundary target registor	:@@FCSUBSPH */
	USHORT					horizontalPixel;
	/**< Frame correction interpolation vertical pixels unit value range
	 * 	:[16 - 724] 2pixel boundary target registor	:@@FCSUBSPV */
	USHORT					verticalPixel;
	/**< Inverse coefficient correction interpolation (base unit) value range
	 * 	:[0 - 65535]  target registor	:@@FCSUBDRM */
	USHORT					inverseBase;
	/**< Inverse coefficient correction interpolation (Exponent part)
value range		:[0 - 11]  target registor	:@@FCSUBDRE */
	USHORT					inverseExponent;
	/**< Frame correction coefficient horizontal start position value range
	 * 		:[0 - 722] 2pixel boundary target registor	:@@FCSUBSTH	*/
	USHORT					coefPosX;
	/**< Frame correction coefficient vertical start position value range
	 * 	:[0 - 722] 2pixel boundary target registor	:@@FCSUBSTV	*/
	USHORT					coefPosY;
} TimproFfcCtrl;

/** PRO FFC Control information
*/
typedef struct {
	/**< Frame correction expansion blend ratio 0 value range		:[-512 - +511] target registor	:@@FCBC0	*/
	SHORT	blendRatio0;
	/**< Frame correction expansion blend ratio 1 value range		:[-512 - +511] target registor	:@@FCBC1	*/
	SHORT	blendRatio1;
} TimproFfcBlendCtrl;

/** PRO FFC Area information
*/
typedef struct {
	/**< Frame correction expansion horizontal start position value range		:[0 - 4095] target registor	:@@FCH */
	USHORT	posX;
	/**< Frame correction expansion vertical start position value range
	 * :[2 - 8960] 2line boundary target registor	:@@FCV */
	USHORT	posY;
	/**< horizontal size<br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
								value range		:[4 - 2496] 4pixel boundary<br>
	// --- REMOVE_ES1_HARDWARE END ---
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES1_HARDWARE
	#ifdef CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES3_HARDWARE BEGIN ---
								value range		:[4 - 2900] 4pixel boundary<br>
	// --- REMOVE_ES3_HARDWARE END --
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif	// CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	target registor	:@@FCHW */
	USHORT	width;
	/**< vertical size value range		:[4 - 8960] 4pixel boundary< target registor	:@@FCVW */
	USHORT	lines;
} TimproFfcArea;

/** RDMA I/F FFC register address information
*/
typedef struct {
	/**< 2840_(971C - 971Fh) */
	ULONG	fcbc;
	/**< 2840_(9734 - 9737h) */
	ULONG	fcsubpr;
	/**< 2840_(9738 - 973Bh) */
	ULONG	fcsubsp;
	/**< 2840_(973C - 973Fh) */
	ULONG	fcsubdr;
	/**< 2840_(9740 - 9743h) */
	ULONG	fcsubst;
} TimproRdmaFfcAddr;

/*类型定义区域*/
typedef struct _ImproSroffc							ImproSroffc;
typedef struct _ImproSroffcPrivate				ImproSroffcPrivate;


/*对象结构体区域*/
struct _ImproSroffc
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sroffc_get_type(void);
ImproSroffc*			impro_sroffc_new();
/**
Start FFC
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH/M2P not running NG
*/
extern	INT32			impro_sroffc_start( E_IM_PRO_UNIT_NUM unitNo );
/**
Stop FFC
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH/M2P not stopped NG
*/
extern	INT32			impro_sroffc_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force );
/**
Set FFC control information
@param[in]	unitNo : Unit number.
@param[in]	ffcCtrl	: FFC control Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffc_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproFfcCtrl* ffcCtrl );
/**
Set FFC blend control information
@param[in]	unitNo : Unit number.
@param[in]	blendCtrl	: FFC blend control Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffc_set_blend( E_IM_PRO_UNIT_NUM unitNo, TimproFfcBlendCtrl* blendCtrl );
/**
A setup of enable access to the built-in RAM of FFC.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_sroffc_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );
/**
Set FFC area
@param[in]	unitNo : Unit number.
@param[in]	ffcArea	: FFC area.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffc_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproFfcArea* ffcArea );
/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
			Always set this register to maintain the following relationship:<br>
			(FCWRIC < ((Input horizontal size - (4* FCSUBPRH)) - 10)/3) <br>
			target registor	:@@FCWRIC
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffc_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, USHORT reqIntervalClk );
/**
Get the top address of the address array of FFC control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of FFC control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_sroffc_get_rdma_addr_ffc_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaFfcAddr** addr );







#endif /* __IMPRO_SROFFC_H__ */

