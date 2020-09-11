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


#ifndef __IMPRO_SROFSHDL_H__
#define __IMPRO_SROFSHDL_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROFSHDL        (impro_srofshdl_get_type())
#define IMPRO_SROFSHDL(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrofshdl))
#define IMPRO_IS_SROFSHDL(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROFSHDL))


/*宏定义区域*/

	/**< Number of SRO FSHDL	*/
#define ImproSrofshdl_D_IM_PRO_SRO_FSHDL_CH_NUM		(ImproSrofshdl_E_IM_PRO_FSHDL_CH_1 + 1)
//

/** @addtogroup im_pro_sro_fshdl FSHDL
@{
*/
/**< Minimum setting of FFSHV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHV_MIN		(2)
/**< Maximum setting of FFSHV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHV_MAX		(8960)
/**< Minimum setting of FFSHH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHH_MIN		(0)
/**< Maximum setting of FFSHH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHH_MAX		(4095)
/**< Minimum setting of FFSHVW	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHVW_MIN		(4)
/**< Maximum setting of FFSHVW	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHVW_MAX		(8960)
/**< Minimum setting of FFSHHW	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHW_MIN		(4)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FFSHHW	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHW_MAX		(2496)

/**< Maximum setting of FFSHHWPH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MAX		(2496)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FFSHHW	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHW_MAX		(2900)
/**< Maximum setting of FFSHHWPH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MAX		(2900)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE

#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX	(314)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX	(366)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE

#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX	(314)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE

#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MAX	(366)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE

// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of FFSHSUBPRV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MIN	(4)
/**< Maximum setting of FFSHSUBPRV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRV_MAX	(1122)
/**< Minimum setting of FFSHSUBSPH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MIN	(16)
/**< Maximum setting of FFSHSUBSPH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPH_MAX	(724)
/**< Minimum setting of FFSHSUBSPV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MIN	(16)
/**< Maximum setting of FFSHSUBSPV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSPV_MAX	(724)
/**< Minimum setting of FFSHSUBSTH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MIN	(0)
/**< Maximum setting of FFSHSUBSTH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTH_MAX	(722)
/**< Minimum setting of FFSHSUBSTV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MIN	(0)
/**< Maximum setting of FFSHSUBSTV	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBSTV_MAX	(722)
/**< Minimum setting of FFSHWRIC	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHWRIC_MIN		(4)
/**< Maximum setting of FFSHWRIC	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHWRIC_MAX		(1023)
/*	@}*/	// im_pro_sro_fshdl

// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of FFSHULRR	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULRR_MIN		(0)
/**< Maximum setting of FFSHULRR	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULRR_MAX		(16383)
	/**< Minimum setting of FFSHULGR	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGR_MIN		(0)
/**< Maximum setting of FFSHULGR	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGR_MAX		(16383)
/**< Minimum setting of FFSHULGB	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGB_MIN		(0)
/**< Maximum setting of FFSHULGB	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULGB_MAX		(16383)
/**< Minimum setting of FFSHULBB	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULBB_MIN		(0)
	/**< Maximum setting of FFSHULBB	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHULBB_MAX		(16383)
/**< Minimum setting of FFSHSUBPRH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHSUBPRH_MIN	(4)
/**< Minimum setting of FFSHHWPH	*/
#define	ImproSrofshdl_D_IM_PRO_FSHDL_FFSHHWPH_MIN		(4)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
/*其他结构体或类型定义区域*/
/** FSHDL channel number
*/
typedef enum {
	/**< ch 0	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CH_0 = 0,
	/**< ch 1	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CH_1,
} EimproFshdlCh;

/** Formatting correction factor concentric
*/
typedef enum {
	/**<   XXXX.XXXX_XXXX_XXXX		*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_0 = 0,
	/**< 1+XXXX.XXXX_XXXX_XXXX		*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_1,
	/**<    XXX.XXXX_XXXX_XXXX_X	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_2,
	/**< 1+ XXX.XXXX_XXXX_XXXX_X	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_3,
	/**<     XX.XXXX_XXXX_XXXX_XX	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_4,
	/**< 1+  XX.XXXX_XXXX_XXXX_XX	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_5,
	/**<      X.XXXX_XXXX_XXXX_XXX	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_6,
	/**< 1+   X.XXXX_XXXX_XXXX_XXX	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_CORRECTION_FORMAT_7,
} EimproFshdlCorrectionFormat;

/** Saturation correction Enable/Disable
*/
typedef enum {
	/**< Disable	*/
	ImproSrofshdl_E_IM_PRO_FSHDL_SAT_CORRECTION_DIS = 0,
	/**< Enable		*/
	ImproSrofshdl_E_IM_PRO_FSHDL_SAT_CORRECTION_EN
} EimproFshdlSatCorrection;

/** Frame shading montage image processing mode.
*/
typedef enum {
	/**< Montage image processing mode is OFF.	*/
	ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_OFF = 0,
	/**< Montage image processing mode is ON.	*/
	ImproSrofshdl_E_IM_PRO_FSHD_MONTAGE_MODE_ON,
} EimproFshdMontageMode;

/** Light-Frame Correction common control information
*/
typedef struct {
	/**< Montage mode target registor	:@@FFSHPTMD */
	EimproFshdMontageMode			montageMode;
	/**< Clip surface shading correction value after (rr) value range
	 * 	:[0 - 16383]  target registor	:@@FFSHULRR */
	USHORT								clipR;
	/**< Clip surface shading correction value after (GR) value range
	 * 	:[0 - 16383]  target registor	:@@FFSHULGR */
	USHORT								clipGr;
	/**< Clip surface shading correction value after (GB) value range
	 * 	:[0 - 16383]  target registor	:@@FFSHULGB */
	USHORT								clipGb;
	/**< Clip surface shading correction value after (bb) value range
	 * 	:[0 - 16383]  target registor	:@@FFSHULBB */
	USHORT								clipB;
} TimproFshdlCommonCtrl;

/** Light-Frame Correction blend ratio information
*/
typedef struct {
	/**< Frame shading blend ratio 0 value range		:[-512 - +511]  target registor	:@@FSHDBC0 */
	SHORT							shadingBlend0;
	/**< Frame shading blend ratio 1 value range		:[-512 - +511]  target registor	:@@FSHDBC1 */
	SHORT							shadingBlend1;
} TimproFshdlBlendCtrl;

/** RDMA I/F FSHDL register address information
*/
typedef struct {
	/**< 2840_(931C - 931Fh) */
	ULONG	ffshbc;
	/**< 2840_(9320 - 9323h) */
	ULONG	ffshul1;
	/**< 2840_(9324 - 9327h) */
	ULONG	ffshul2;
	/**< 2840_(9328 - 932Bh) */
	ULONG	ffshgfmt;
	/**< 2840_(9330 - 9333h) */
	ULONG	ffshsubpr;
	/**< 2840_(9334 - 9337h) */
	ULONG	ffshsubsp;
	/**< 2840_(9338 - 933Bh) */
	ULONG	ffshsubdr;
	/**< 2840_(933C - 933Fh) */
	ULONG	ffshsubst;
	/**< 2840_(9340 - 9343h) */
	ULONG	ffshctl;
	/**< 2840_(9344 - 9347h) */
	ULONG	ffshhwph;
	/**< 2840_(9350 - 9353h) */
	ULONG	ffshcctl;
	/**< 2840_(9354 - 9357h) */
	ULONG	ffshlp1;
	/**< 2840_(9358 - 935Bh) */
	ULONG	ffshlp2;
} TimproRdmaFshdlAddr;

/** Light-Frame Correction common control information
*/
typedef struct {
	/**< Formatting correction factor concentric target registor	:@@FFSHGFMT */
	EimproFshdlCorrectionFormat	selectFormat;
	/**< Frame horizontal size correction factor<br>
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
		target registor	:@@FFSHSUBPRH */
	USHORT								frameHorizontalSize;
	/**< Frame vertical size correction factor value range
	 * 	:[4 - 1122] 2pixel boundary target registor	:@@FFSHSUBPRV */
	USHORT								frameVorizontalSize;
	/**< Correction of horizontal pixels per frame interpolation value range
	 * 	:[16 - 724] 2pixel boundary target registor	:@@FFSHSUBSPH */
	USHORT								horizontalPixel;
	/**< Correction of vertical pixels per frame interpolation value range
	 * 	:[16 - 724] 2pixel boundary target registor	:@@FFSHSUBSPV */
	USHORT								verticalPixel;
	/**< Inverse coefficient correction interpolation frame (base unit) value range
	 * \	:[0 - 65535]  target registor	:@@FFSHSUBDRM */
	USHORT								InverseBase;
	/**< Inverse coefficient correction interpolation frame (Exponent part) value range
	 * :[0 - 11]  target registor	:@@FFSHSUBDRE */
	USHORT								InverseExponent;
	/**< Horizontal start position correction factor frame value range
	 * 	:[0 - 722] 2pixel boundary target registor	:@@FFSHSUBSTH */
	USHORT								startPosH;
	/**< Vertical start position correction factor frame value range
	 * 	:[0 - 722] 2pixel boundary target registor	:@@FFSHSUBSTV */
	USHORT								startPosV;
	/**< horizontal montage position of the montage image in units of 2 pixels<br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
																	value range		:[4 - 2496] 2pixel boundary<br>
	// --- REMOVE_ES1_HARDWARE END ---
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES1_HARDWARE
	#ifdef CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES3_HARDWARE BEGIN ---
																	value range		:[4 - 2900] 2pixel boundary<br>
		// --- REMOVE_ES3_HARDWARE END --
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif	// CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	Set the value with reference to the left side of the setting processing window<br>
	and inside the setting value range of FSHDHW and satisfy the relationship shown below.<br>
	Moreover, make sure to set FSHDPTMD=1 to use this setting. <br>
	FSSUBSTH + FSHDHWPH = n * FSSUBSPH + 2<br>
	※n: integer<br>
	target registor	:@@FFSHHWPH */
	USHORT								montagePosH;
	/**< Saturation correction Enable/Disable target registor	:@@FFSHCEN */
	EimproFshdlSatCorrection		satCorrectionEnabled;
	/**< SLOPE gain for Saturation correction. value range		:[0 - 4095(=255.9375)] target registor
	 * 	:[0]@@FFSHLPRR, [1]@@FFSHLPGR, [2]@@FFSHLPGB, [3]@@FFSHLPBB */
	USHORT								satSlopeGain[4];
} TimproFshdlFrameCtrl;

/*类型定义区域*/
typedef struct _ImproSrofshdl					ImproSrofshdl;
typedef struct _ImproSrofshdlPrivate				ImproSrofshdlPrivate;


/*对象结构体区域*/
struct _ImproSrofshdl
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_srofshdl_get_type(void);
ImproSrofshdl*		impro_srofshdl_new();
extern	VOID			impro_srofshdl_comm_get_fshdl_reg_info( E_IM_PRO_UNIT_NUM unitNo,
									EimproFshdlCh ch, const T_IM_PRO_SRO_FSHDL_INFO** fshdlInfo );
/**
Flat Shading Start
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PRCH/M2P not running NG
@remarks	Flat Shading Compensation function is started(enable).
*/
extern	INT32			impro_srofshdl_start( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch );
/**
Flat Shading Stop
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK				: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PRCH/M2P not stopped NG
@remarks	Flat Shading Compensation function is stopped(disable).
*/
extern	INT32			impro_srofshdl_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, UCHAR force );
/**
Flat Shading Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlCtrl : Shading Control information
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_srofshdl_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproFshdlCommonCtrl* fshdlCtrl );
/**
Flat Shading Blend ratio Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	blendCtrl : Shading Blend Control information
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_srofshdl_set_blend( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, TimproFshdlBlendCtrl* blendCtrl );
/**
A setup of enable access to the built-in RAM of FSHDL.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srofshdl_set_paen( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch, UCHAR paenTrg );
/**
A Setup is Flat Shading Area
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlArea : Area for Shading compensation See @ref T_IM_PRO_AREA_INFO<br>
 												value range  :posX[0 - 4095]<br>
 												target registor  :@@FFSHH<br>
 												value range  :posY[2 - 8960] 2line boundary<br>
 												target registor  :@@FFSHV<br>
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
 												value range  :width[4 - 2496] 4pixel boundary<br>
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
												value range  :width[4 - 2900] 2pixel boundary<br>
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
 												target registor  :@@FFSHHW<br>
 												value range  :lines[4 - 8960] 4pixel boundary<br>
 												target registor  :@@FFSHVW
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_srofshdl_set_area( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
									T_IM_PRO_AREA_INFO* fshdlArea );
/**
Flat Shading (Frame Correction) Control
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	fshdlCtrl : Frame Correction Control information
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_srofshdl_set_frame( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
									TimproFshdlFrameCtrl* fshdlCtrl );
/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
			Always set this parameter to maintain the following relationship:<br>
			(FFSHWRIC < ((Input horizontal size - (4* FFSHSUBPRH)) - 10)/3)<br>
			target registor	:@@FFSHWRIC
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srofshdl_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
									USHORT reqIntervalClk );
/**
Get the top address of the address array of FSHDL control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of FSHDL control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_srofshdl_get_rdma_addr_fshdl_cntl( E_IM_PRO_UNIT_NUM unitNo, EimproFshdlCh ch,
									const TimproRdmaFshdlAddr** addr );





#endif /* __IMPRO_SROFSHDL_H__ */

