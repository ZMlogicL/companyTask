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


#ifndef __IMPRO_SROFFSH_H__
#define __IMPRO_SROFFSH_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROFFSH        (impro_sroffsh_get_type())
#define IMPRO_SROFFSH(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSroffsh))
#define IMPRO_IS_SROFFSH(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROFFSH))


/*宏定义区域*/
	/**< Number of SRO FFSH		*/
#define ImproSroffsh_D_IM_PRO_SRO_FFSH_CH_NUM		(ImproSroffsh_E_IM_PRO_FFSH_CH1 + 1)

/** @addtogroup im_pro_sro_ffsh FFSH*/
/**< Minimum setting of FFSHV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MIN			(2)
	/**< Maximum setting of FFSHV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHV_MAX			(8960)
/**< Minimum setting of FFSHH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MIN			(0)
/**< Maximum setting of FFSHH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHH_MAX			(4095)
/**< Minimum setting of FFSHVW	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MIN		(4)
	/**< Maximum setting of FFSHVW	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHVW_MAX		(8960)
	/**< Minimum setting of FFSHHW	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MIN		(4)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FFSHHW	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MAX		(2496)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FFSHHW	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHHW_MAX		(2900)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	/**< Minimum setting of FFSHSUBPRH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MIN	(4)
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MAX	(314)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of FFSHSUBPRH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRH_MAX	(366)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
/**< Minimum setting of FFSHSUBPRV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MIN	(4)
/**< Maximum setting of FFSHSUBPRV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBPRV_MAX	(1122)
/**< Minimum setting of FFSHSUBSPH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MIN	(16)
/**< Maximum setting of FFSHSUBSPH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPH_MAX	(724)
/**< Minimum setting of FFSHSUBSPV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MIN	(16)
/**< Maximum setting of FFSHSUBSPV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSPV_MAX	(724)
/**< Minimum setting of FFSHSUBSTH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MIN	(0)
/**< Maximum setting of FFSHSUBSTH	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTH_MAX	(722)
	/**< Minimum setting of FFSHSUBSTV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MIN	(0)
/**< Maximum setting of FFSHSUBSTV	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHSUBSTV_MAX	(722)
/**< Minimum setting of FFSHWRIC	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHWRIC_MIN		(4)
/**< Maximum setting of FFSHWRIC	*/
#define	ImproSroffsh_D_IM_PRO_FFSH_FFSHWRIC_MAX		(1023)
/*	@}*/	// im_pro_sro_ffsh

/*其他结构体或类型定义区域*/
/** FFSH channel number.
*/
typedef enum {
	/**< FFSH0 */
	ImproSroffsh_E_IM_PRO_FFSH_CH0 = 0,
	/**< FFSH1 */
	ImproSroffsh_E_IM_PRO_FFSH_CH1
} EimproFfshCh;

/** FFSH Blend Control information
*/
typedef struct {
	/**< Frame correction expansion blend ratio 0 value range		:[-512 - +511]  target registor	:@@FFSHBC0 */
	SHORT							frameCorrectionBlend0;
	/**< Frame correction expansion blend ratio 1 value range		:[-512 - +511]  target registor	:@@FFSHBC1 */
	SHORT							frameCorrectionBlend1;
} TimproFfshBlendCtrl;

/** FFSH Control information
*/
typedef struct {
	/**< horizontal data size of the correction coefficient of the frame correction expansion
	 * processing in units of 2 pixels.<br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
																				value range		:[4 - 314]<br>
	// --- REMOVE_ES1_HARDWARE END ---
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES1_HARDWARE
	#ifdef CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES3_HARDWARE BEGIN ---
																				value range		:[4 - 366]<br>
	// --- REMOVE_ES3_HARDWARE END --
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#endif // CO_ES3_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	target registor	:@@FFSHSUBPRH */
	USHORT							hSizeCorrectionCoeff;
	/**< vertical data size of the correction coefficient of the frame correction expansion processing in
	 * units of 2 pixels. value range		:[4 - 1122] target registor	:@@FFSHSUBPRV */
	USHORT							vSizeCorrectionCoeff;
	/**< horizontal pixel unit in units of 2 pixels when performing bilinear interpolation for the correction
	 *  coefficient data in the frame correction expansion processing. value range
	 *  	:[16 - 724] target registor	:@@FFSHSUBSPH */
	USHORT							hPixelUnitInterpolation;
	/**< vertical pixel unit in units of 2 pixels when performing bilinear interpolation for the correction
	 * coefficient data in the frame correction expansion processing. value range
	 * :[16 - 724 target registor	:@@FFSHSUBSPV */
	USHORT							vPixelUnitInterpolation;
	/**< radix part of the reciprocal number of the divisor which is used in the bilinear interpolation for
	 *  the correction coefficient data in the frame correction expansion processing. value range
	 *  	:[0(=1.0) - 65535(=1.9999847412109375)] target registor	:@@FFSHSUBDRM */
	USHORT							radInverseCoeffInterpolation;
	/**< exponential part of the reciprocal number of the divisor which is used in the bilinear interpolation
	 *  for the correction coefficient data in the frame correction expansion processing. value range
	 *  	:[0 - 11] target registor	:@@FFSHSUBDRE */
	UCHAR							expRadInverseCoeffInterpolation;
	/**< horizontal start position of the expanded upper left grid in units of 2 pixels in the frame correction
	 *  expansion processing.value range		:[0 - 722] target registor	:@@FFSHSUBSTH */
	USHORT							hStartPosCoeff;
	/**< vertical start position of the expanded upper left grid in units of 2 pixels in the frame correction
	 *  expansion processing. value range		:[0 - 722] target registor	:@@FFSHSUBSTV */
	USHORT							vStartPosCoeff;
} TimproFfshCtrl;

/** RDMA I/F FFSH register address information
*/
typedef struct {
	/**< 2840_(821C - 821Fh) */
	ULONG	ffshbc;
	/**< 2840_(8230 - 8233h) */
	ULONG	ffshsubpr;
	/**< 2840_(8234 - 8237h) */
	ULONG	ffshsubsp;
	/**< 2840_(8238 - 823Bh) */
	ULONG	ffshsubdr;
	/**< 2840_(823C - 824Fh) */
	ULONG	ffshsubst;
} TimproRdmaFfshAddr;

/** FFSH Area Control information
*/
typedef struct {
	/**< FFSH Window information<br>
													value range  :posX[0 - 4095]<br>
													target registor  :@@FFSHH<br><br>
													value range  :posY[2 - 8960]<br>
													target registor  :@@FFSHV<br><br>
	// --- REMOVE_ES_COMPILE_OPT BEGIN ---
	#ifdef CO_ES1_HARDWARE
	// --- REMOVE_ES_COMPILE_OPT END ---
	// --- REMOVE_ES1_HARDWARE BEGIN ---
													value range  :width[4 - 2496] 2pixel boundary<br>
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
													target registor  :@@FFSHHW<br><br>
													value range  :lines[4 - 8960] 2pixel boundary<br>
													target registor  :@@FFSHVW */
	T_IM_PRO_AREA_INFO		ffshArea;
} TimproFfshArea;

/*类型定义区域*/
typedef struct _ImproSroffsh					ImproSroffsh;
typedef struct _ImproSroffshPrivate				ImproSroffshPrivate;


/*对象结构体区域*/
struct _ImproSroffsh
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sroffsh_get_type(void);
ImproSroffsh*		impro_sroffsh_new();
/**
FFSH start
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not running NG
*/
extern	INT32			impro_sroffsh_start( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch );
/**
FFSH stop
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Processing OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: PRCH not stopped NG
*/
extern	INT32			impro_sroffsh_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, UCHAR force );
/**
FFSH control setup
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffshCtrl : FFSH control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffsh_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshCtrl* ffshCtrl );
/**
A setup of FFSH blend ratio.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	blendCtrl : FFSH blend control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffsh_set_blend( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshBlendCtrl* blendCtrl );
/**
A setup of FFSH effective area
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffshArea : FFSH area information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffsh_set_area( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, TimproFfshArea* ffshArea );
/**
A setup of enable access to the built-in RAM of FFSH.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_sroffsh_set_paen( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, UCHAR paenTrg );
/**
set the request issue interval when reading the coefficients from PRCH/M2P macro.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	reqIntervalClk : RAM access control<br>
			value range :[4~1023]<br>
			Always set this register to maintain the following relationship:<br>
			(FFSHWRIC < ((Input horizontal size - (4* FFSHSUBPRH)) - 10)/3)<br>
			target registor	:@@FFSHWRIC
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroffsh_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, USHORT reqIntervalClk );
/**
Get the top address of the address array of FFSH control.
@param[in]		unitNo : Unit number.
@param[in]		ch : Channel No
@param[out]		addr					: Top address of the address array of FFSH control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_sroffsh_get_rdma_addr_ffsh_cntl( E_IM_PRO_UNIT_NUM unitNo, EimproFfshCh ch, const TimproRdmaFfshAddr** addr );



#endif /* __IMPRO_SROFFSH_H__ */

