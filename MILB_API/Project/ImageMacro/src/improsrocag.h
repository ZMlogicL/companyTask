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


#ifndef __IMPRO_SROCAG_H__
#define __IMPRO_SROCAG_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"


#define IMPRO_TYPE_SROCAG        (impro_srocag_get_type())
#define IMPRO_SROCAG(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSrocag))
#define IMPRO_IS_SROCAG(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROCAG))


/*宏定义区域*/
	/**< Minimum setting of CAGGV	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGV_MIN			(0)
/**< Maximum setting of CAGGV	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGV_MAX			(8960)
	/**< Minimum setting of CAGGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGH_MIN			(0)
/**< Minimum setting of CAGGVW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGVW_MIN			(10)
/**< Maximum setting of CAGGVW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGVW_MAX			(8960)
/**< Minimum setting of CAGGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGHW_MIN			(18)
	/**< Minimum setting of CAGV	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGV_MIN			(4)
/**< Maximum setting of CAGV	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGV_MAX			(8954)
	/**< Minimum setting of CAGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGH_MIN			(8)
/**< Minimum setting of CAGVW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGVW_MIN			(2)
	/**< Maximum setting of CAGVW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGVW_MAX			(8952)
	/**< Minimum setting of CAGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGHW_MIN			(1)

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
/**< Maximum setting of CAGGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGH_MAX			(2496)
/**< Maximum setting of CAGGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGHW_MAX			(2496)
/**< Maximum setting of CAGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGH_MAX			(2487)
/**< Maximum setting of CAGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGHW_MAX			(2480)
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
/**< Maximum setting of CAGGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGH_MAX			(2900)
/**< Maximum setting of CAGGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGGHW_MAX			(2900)
/**< Maximum setting of CAGH	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGH_MAX			(2891)
	/**< Maximum setting of CAGHW	*/
#define	ImproSrocag_D_IM_PRO_CAG_CAGHW_MAX			(2884)
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE


/*其他结构体或类型定义区域*/
/** Clip select after correction
*/
typedef enum {
	/**< Data is clipped to 14bit.	*/
	ImproSrocag_E_IM_PRO_CAG_CLIP_MODE_14BIT = 0,
	/**< Data is clipped to 12bit.	*/
	ImproSrocag_E_IM_PRO_CAG_CLIP_MODE_14BIT_MAX
} EimproCagClipMode;

/** CAG gr/gb gap correction
*/
typedef enum {
	/**< GrGb use	*/
	ImproSrocag_E_IM_PRO_CAG_COR_MODE_GBGB = 0,
	/**< G use		*/
	ImproSrocag_E_IM_PRO_CAG_COR_MODE_G
} EimproCagCorMode;

/** CAG Processing pixel padding Enable/Disable
*/
typedef enum {
	/**< Disable	*/
	ImproSrocag_E_IM_PRO_CAG_PAD_MODE_DIS = 0,
	/**< Enable		*/
	ImproSrocag_E_IM_PRO_CAG_PAD_MODE_EN
} EimproCagPadMode;

/** CAG gap correction mode
*/
typedef enum {
	/**< Optical center distance only  */
	ImproSrocag_E_IM_PRO_CAG_MODE_OPT_CENTER_ONLY = 0,
	/**< Surface correction only */
	ImproSrocag_E_IM_PRO_CAG_MODE_SURFACE_ONLY,
	/**< Additional value of Optical center distance and Surface correction */
	ImproSrocag_E_IM_PRO_CAG_MODE_OPT_CENTER_SURFACE_ADD
} EimproCagMode;


/** PRO CAG Area information
*/
typedef struct {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	/**< global Compensation horizontal direction start position value range :[0 - 2496] target registor :@@CAGGH */
	USHORT	gPosX;
	/**< global Compensation vertical direction start position value range
	 * :[0 - 8960] 2pixel boundary target registor	:@@CAGGV */
	USHORT	gPosY;
	/**< global horizontal size value range	:[18 - 2496] 2pixel boundary target registor	:@@CAGGHW */
	USHORT	gWidth;
	/**< global vertical size value range		:[10 - 8960] 2pixel boundary target registor	:@@CAGGVW */
	USHORT	gLines;
	/**< Compensation horizontal direction start position value range
	 * 	:[8 - 2487] target registor	:@@CAGH */
	USHORT	posX;
	/**< Compensation vertical direction start position value range
	 * 	:[4 - 8954] 2pixel boundary target registor	:@@CAGV */
	USHORT	posY;
	/**< horizontal size value range		:[1 - 2480] target registor	:@@CAGHW */
	USHORT	width;
	/**< vertical size value range		:[2 - 8952] 2pixel boundary target registor	:@@CAGVW */
	USHORT	lines;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	/**< global Compensation horizontal direction start position value
	 *  range		:[0 - 2900] target registor	:@@CAGGH */
	USHORT	gPosX;
	/**< global Compensation vertical direction start position value range
	 * :[0 - 8960] 2pixel boundary target registor	:@@CAGGV */
	USHORT	gPosY;
	/**< global horizontal size value range		:[18 - 2900] 2pixel
	 *  boundary target registor	:@@CAGGHW */
	USHORT	gWidth;
	/**< global vertical size value range		:[10 - 8960]
	 *  2pixel boundary target registor	:@@CAGGVW */
	USHORT	gLines;
	/**< Compensation horizontal direction start position
	 *  value range		:[8 - 2891] target registor	:@@CAGH */
	USHORT	posX;
	/**< Compensation vertical direction start position value range
	 * 	:[4 - 8954] 2pixel boundary target registor	:@@CAGV */
	USHORT	posY;
	/**< horizontal size value range		:[1 - 2884] target registor	:@@CAGHW */
	USHORT	width;
	/**< vertical size value range		:[2 - 8952] 2pixel boundary target registor	:@@CAGVW */
	USHORT	lines;
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
} TimproCagArea;

/** CAG gr/gb gap correction control
*/
typedef struct {
	/**< Clip select after correction target registor	:@@CLPSEL */
	EimproCagClipMode	clipMode;
	/**< gr/gb gap correction mode register target registor	:@@GCAMD */
	EimproCagCorMode	gGapCorMode;
	/**< Processing pixel padding ring register target registor	:@@CAGPDD */
	EimproCagPadMode	gGapPadMode;
	/**< Gap correction mode register target registor	:@@CAMD */
	EimproCagMode		gGapMode;
	/**< upper limit to calculate the limit value of GrGb gradient correction
	 * amount. value range		:[0 - 16383] This value must be set to maintain
	 *  the relationship: BFGLMTL<=BFGLMTH. target registor	:@@BFGLMTH	*/
	USHORT	gradientULimit;
	/**< lower limit to calculate the limit value of GrGb gradient correction
	 * amount. value range		:[0 - 16383] This value must be set to maintain
	 * the relationship: BFGLMTL<=BFGLMTH. target registor	:@@BFGLMTL	*/
	USHORT	gradientLLimit;
	/**< threshold to calculate the limit value of GrGb gradient correction
	 *  amount. value range		:[0 - 16383] target registor	:@@BFGTHA	*/
	USHORT	gradientThreshold;
	/**< gain value to calculate the limit value of GrGb gradient correction
	 * amount. value range		:[0x00 - 0xFF(=3.984375)] target registor	:@@BFGTHK	*/
	UCHAR	gradientThresholdGain;
} TimproCagCtrlGlevelDiff;

/** Optical Color aberration control
*/
typedef struct {
	/**< Reciprocal number of the binning ratio of the vertical direction.
	 * value range		:[0 - 4095] target registor	:@@RBRV	*/
	USHORT	vBinningRatioReciprocalNum;
	/**< eciprocal number of the binning ratio of the horizontal direction.
	 *  value range		:[0 - 4095] target registor	:@@RBRH	*/
	USHORT	hBinningRatioReciprocalNum;
	/**< Optical center position and offset(horizontal) value range		:[0 - 65535(-16384.0 - +16383.5)]
	 *  target registor	:@@ABOARH/@@ABOAGH/@@ABOABH	*/
	SHORT	optCenterPosH[3];
	/**< Optical center position and offset(vertical) value range		:[0 - 65535(-16384.0 - +16383.5)]
	 * target registor	:@@ABOARV/@@ABOAGV/@@ABOABV	*/
	SHORT	optCenterPosV[3];
	/**< Gain value range		:[0 - 8191(-0.00000190 - +0.00000190)]
	 * target registor	:@@ABGAR/@@ABGAG/@@ABGAB	*/
	SHORT	gain[3];
	/**< horizontal Transfer upper limit value range		:[0x1800(=-8.0) - 0x0800(=+8)]
	 * target registor	:@@ABLRHU/@@ABLGHU/@@ABLBHU	*/
	SHORT	transferULimitH[3];
	/**< horizontal Transfer lower limit value range		:[0x1800(=-8.0) - 0x0800(=+8)]
	 *  target registor	:@@ABLRHL/@@ABLGHL/@@ABLBHL	*/
	SHORT	transferLLimitH[3];
	/**< vertical Transfer upper limit value range		:[0x0C00(=-4.0) - 0x0400(=+4.0)]
	 *  target registor	:@@ABLRVU/@@ABLGVU/@@ABLBVU	*/
	SHORT	transferULimitV[3];
	/**< vertical Transfer lower limit value range		:[0x0C00(=-4.0) - 0x0400(=+4.0)]
	 *  target registor	:@@ABLRVL/@@ABLGVL/@@ABLBVL	*/
	SHORT	transferLLimitV[3];
	/**< horizontal Transfer offset value range		:[0 - 4095(-8.0 - +7.99609375)]
	 *  target registor	:@@ABOFSRH/@@ABOFSGH/@@ABOFSBH	*/
	SHORT	transferOffsetH[3];
	/**< vertical Transfer offset value range		:[0 - 2047(-4.0 - +3.99609375)]
	 *  target registor	:@@ABOFSRV/@@ABOFSGV/@@ABOFSBV	*/
	SHORT	transferOffsetV[3];
	/**< corner threshold 1 value range		:[0 - 0xFFFF(15-bit integer part,1-bit fractional part)]
	 * target registor	:@@ABNLTHR1/@@ABNLTHG1/@@ABNLTHB1	*/
	USHORT	cornerThresh1[3];
	/**< corner gain 1 value range		:[0 - 32767(-0.99993896484375 - +0.99993896484375)]
	 * target registor	:@@ABNLGAR1/@@ABNLGAG1/@@ABNLGAB1	*/
	SHORT	cornerGain1[3];
	/**< corner threshold 2 value range		:[0 - 0xFFFF(15-bit integer part,1-bit fractional part)]
	 * target registor	:@@ABNLTHR2/@@ABNLTHG2/@@ABNLTHB2	*/
	USHORT	cornerThresh2[3];
	/**< corner gain 2 value range		:[0 - 32767(-0.99993896484375 - +0.99993896484375)]
	 * target registor	:@@ABNLGAR2/@@ABNLGAG2/@@ABNLGAB2	*/
	SHORT	cornerGain2[3];
	/**< corner threshold 3 value range		:[0 - 0xFFFF(15-bit integer part,1-bit fractional part)]
	 *  target registor	:@@ABNLTHR3/@@ABNLTHG3/@@ABNLTHB3	*/
	USHORT	cornerThresh3[3];
	/**< corner gain 3 value range		:[0 - 32767(-0.99993896484375 - +0.99993896484375)]
	 *  target registor	:@@ABNLGAR3/@@ABNLGAG3/@@ABNLGAB3	*/
	SHORT	cornerGain3[3];
	/**< corner threshold 4 value range		:[0 - 0xFFFF(15-bit integer part,1-bit fractional part)]
	 *  target registor	:@@ABNLTHR4/@@ABNLTHG4/@@ABNLTHB4	*/
	USHORT	cornerThresh4[3];
	/**< corner gain 4 value range		:[0 - 32767(-0.99993896484375 - +0.99993896484375)]
	 *  target registor	:@@ABNLGAR4/@@ABNLGAG4/@@ABNLGAB4	*/
	SHORT	cornerGain4[3];
} TimproCagCtrl;

/** RDMA I/F CAG register address information
*/
typedef struct {
	/**< 2840_(9818 - 981Bh) */
	ULONG	cagmd;
	/**< 2840_(981C - 981Fh) */
	ULONG	rbr;
	/**< 2840_(9820 - 9823h) */
	ULONG	aboarv;
	/**< 2840_(9824 - 9827h) */
	ULONG	aboarh;
	/**< 2840_(9828 - 982Bh) */
	ULONG	aboagv;
	/**< 2840_(982C - 982Fh) */
	ULONG	aboagh;
	/**< 2840_(9830 - 9833h) */
	ULONG	aboabv;
	/**< 2840_(9834 - 9837h) */
	ULONG	aboabh;
	/**< 2840_(9838 - 983Bh) */
	ULONG	abgar;
	/**< 2840_(983C - 983Fh) */
	ULONG	abgag;
	/**< 2840_(9840 - 9843h) */
	ULONG	abgab;
	/**< 2840_(9844 - 9847h) */
	ULONG	ablrv;
	/**< 2840_(9848 - 984Bh) */
	ULONG	ablrh;
	/**< 2840_(984C - 984Fh) */
	ULONG	ablgv;
	/**< 2840_(9850 - 9853h) */
	ULONG	ablgh;
	/**< 2840_(9854 - 9857h) */
	ULONG	ablbv;
	/**< 2840_(9858 - 985Bh) */
	ULONG	ablbh;
	/**< 2840_(985C - 985Fh) */
	ULONG	abofsrv;
	/**< 2840_(9860 - 9863h) */
	ULONG	abofsrh;
	/**< 2840_(9864 - 9867h) */
	ULONG	abofsgv;
	/**< 2840_(9868 - 986Bh) */
	ULONG	abofsgh;
	/**< 2840_(986C - 986Fh) */
	ULONG	abofsbv;
	/**< 2840_(9870 - 9873h) */
	ULONG	abofsbh;
	/**< 2840_(9874 - 9877h) */
	ULONG	abnlthr1;
	/**< 2840_(9878 - 987Bh) */
	ULONG	abnlthg1;
	/**< 2840_(987C - 987Fh) */
	ULONG	abnlthb1;
	/**< 2840_(9880 - 9883h) */
	ULONG	abnlgar1;
	/**< 2840_(9884 - 9887h) */
	ULONG	abnlgag1;
	/**< 2840_(9888 - 988Bh) */
	ULONG	abnlgab1;
	/**< 2840_(988C - 988Fh) */
	ULONG	abnlthr2;
	/**< 2840_(9890 - 9893h) */
	ULONG	abnlthg2;
	/**< 2840_(9894 - 9897h) */
	ULONG	abnlthb2;
	/**< 2840_(9898 - 989Bh) */
	ULONG	abnlgar2;
	/**< 2840_(989C - 989Fh) */
	ULONG	abnlgag2;
	/**< 2840_(98A0 - 98A3h) */
	ULONG	abnlgab2;
	/**< 2840_(98A4 - 98A7h) */
	ULONG	abnlthr3;
	/**< 2840_(98A8 - 98ABh) */
	ULONG	abnlthg3;
	/**< 2840_(98AC - 98AFh) */
	ULONG	abnlthb3;
	/**< 2840_(98B0 - 98B3h) */
	ULONG	abnlgar3;
	/**< 2840_(98B4 - 98B7h) */
	ULONG	abnlgag3;
	/**< 2840_(98B8 - 98BBh) */
	ULONG	abnlgab3;
	/**< 2840_(98BC - 98BFh) */
	ULONG	abnlthr4;
	/**< 2840_(98C0 - 98C3h) */
	ULONG	abnlthg4;
	/**< 2840_(98C4 - 98C7h) */
	ULONG	abnlthb4;
	/**< 2840_(98C8 - 98CBh) */
	ULONG	abnlgar4;
	/**< 2840_(98CC - 98CFh) */
	ULONG	abnlgag4;
	/**< 2840_(98D0 - 98D3h) */
	ULONG	abnlgab4;
	/**< 2840_(98D4 - 98D7h) */
	ULONG	bfglmt;
	/**< 2840_(98D8 - 98DBh) */
	ULONG	bfgth;
} TimproRdmaCagAddr;


/*类型定义区域*/
typedef struct _ImproSrocag							ImproSrocag;
typedef struct _ImproSrocagPrivate				ImproSrocagPrivate;


/*对象结构体区域*/
struct _ImproSrocag
{
	KObject    parent;
};




/*方法定义区域（公有放在new后面）*/
KConstType				impro_srocag_get_type(void);
ImproSrocag*			impro_srocag_new();
/**
Start CAG
@param[in]	unitNo : Unit number.
*/
extern	VOID			impro_srocag_start( E_IM_PRO_UNIT_NUM unitNo );
/**
Stop CAG
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
extern	VOID			impro_srocag_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force );
/**
Set CAG control information
@param[in]	unitNo : Unit number.
@param[in]	cagCtrl	: CAG control Information.
*/
extern	INT32			impro_srocag_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproCagCtrl* cagCtrl );
/**
A setup of enable access to the built-in RAM of CAG.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg :  control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_srocag_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg );
/**
Set CAG area
@param[in]	unitNo : Unit number.
@param[in]	cagArea	: CAG area.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srocag_set_area( E_IM_PRO_UNIT_NUM unitNo, TimproCagArea* cagArea );
/**
Set CAG optCenterPosH  control
@param[in]	unitNo : Unit number.
@param[in]	optCenterPosH	: CAG control Information.
*/
extern INT32			impro_srocag_opt_center_pos_h_ctrl( E_IM_PRO_UNIT_NUM unitNo, SHORT optCenterPosH [3] );
/**
Set CAG G level difference information
@param[in]	unitNo : Unit number.
@param[in]	cagCtrlGlevelDiff	: CAG G level difference Information.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_srocag_ctrl_glv_diff( E_IM_PRO_UNIT_NUM unitNo, TimproCagCtrlGlevelDiff* cagCtrlGlevelDiff );
/**
Get the top address of the address array of CAG control.
@param[in]		unitNo : Unit number.
@param[out]		addr					: Top address of the address array of CAG control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_srocag_get_rdma_addr_cag_cntl( E_IM_PRO_UNIT_NUM unitNo, const TimproRdmaCagAddr** addr );







#endif /* __IMPRO_SROCAG_H__ */

