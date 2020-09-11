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


#ifndef __IMPRO_SENSLDIV_H__
#define __IMPRO_SENSLDIV_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENSLDIV        (impro_sensldiv_get_type())
#define IMPRO_SENSLDIV(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSensldiv))
#define IMPRO_IS_SENSLDIV(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENSLDIV))


/*宏定义区域*/


/*其他结构体或类型定义区域*/
/** Line division processing input point mode setting.
*/
typedef enum {
	/**< 2-point input		*/
	ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_2POINT_INPUT = 0,
	/**< 4-point input		*/
	ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_4POINT_INPUT,
	/**< 8-point input	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_8POINT_INPUT,
} EimproLdivLdipmd;

typedef enum {
	/**< Division processing is started from the first line of a frame.	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDSTMD_LINE = 0,
	/**< Division processing is started by skipping the first line of a frame.	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDSTMD_LINESKIP
} EimproLdivLdstmd;

/** Line division processing VD subsampling mode setting.set the VD subsampling mode of the output side.*/
typedef enum {
	/**< No VD subsampling	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_NO_SUBSAMPLING = 0,
	/**< 1/2 VD subsampling	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_HARF_SUBSAMPLING,
	/**< 1/3 VD subsampling	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_ONE_THIRD_SUBSAMPLING,
	/**< 1/4 VD subsampling	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_QUARTER_SUBSAMPLING,
} EimproLdivLdvdmd;

/** Line division processing HD insertion mode setting.set the HD signal insertion mode right after VD.*/
typedef enum {
	/**< Disable	*/
	ImproSensldiv_E_IM_PRO_LDIV_HD_INSERTION_ENABLE_DIS = 0,
	/**< Enable		*/
	ImproSensldiv_E_IM_PRO_LDIV_HD_INSERTION_ENABLE_EN,
} EimproLdivHdInsertionEnable;

/** Line division processing multi-CH combination mode setting.set the
 *  multi-CH combination mode of the line division processing.*/
typedef enum {
	/**< No combination	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDMCH_NO_COMBI = 0,
	/**< 2 combination	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDMCH_2_COMBI,
	/**< 4 combination	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDMCH_4_COMBI,
} EimproLdivLdmch;

/** Line division processing rectangle output mode setting. set the rectangle
 *  output mode ofthe output side of the line division processing.*/
typedef enum {
	/**< Single output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_SINGLE_OUTPUT = 0,
	/**< 2-rectangle output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_2RECT_OUTPUT,
	/**< 3-rectangle output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_3RECT_OUTPUT,
	/**< 4-rectangle output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_4RECT_OUTPUT,
} EimproLdivLddivmd;

/** Line division processing output point mode setting.*/
typedef enum {
	/**< 2-line 1-point output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDOPMD_2LINE_1OUT = 0,
	/**< 2-line 2-point output	*/
	ImproSensldiv_E_IM_PRO_LDIV_LDOPMD_2LINE_2OUT,
} EimproLdivLdopmd;


/** PRO LDIV Macro Control information*/
typedef struct {
	/**< Line division processing first line mode setting. target registor	:LDIVCTL@@LDSTMD */
	EimproLdivLdstmd					mode;
	/**< Line division processing input point mode setting. target registor	:LDIVCTL@@LDIPMD */
	EimproLdivLdipmd				ldipmd;
	/**< Line division processing VD subsampling mode setting. target registor	:LDIVCTL@@LDVDMD */
	EimproLdivLdvdmd				ldvdmd;
	/**< Line division processing HD insertion mode setting. target registor	:LDIVCTL@@LDHDMD */
	EimproLdivHdInsertionEnable	hdInsertionEn;
	/**< Line division processing multi-CH combination mode setting. target registor	:LDIVCTL@@LDMCH */
	EimproLdivLdmch					ldmch;
	/**< Line division processing rectangle output mode setting. target registor	:LDIVCTL@@LDDIVMD */
	EimproLdivLddivmd				lddivmd;
	/**< Line division processing output point mode setting. target registor	:LDIVCTL@@LDOPMD */
	EimproLdivLdopmd				ldopmd;
} TimproLdivCtrl;

/** LDIV Area information*/
typedef struct {
	/**< Line division processing input horizontal pixel count. value range[2~***] Maximum setting
	 * value depends on the horizontal maximum size of @ref impro_sentop_ctrl() argument of @ref
	 * EimproSentopLdivMaxHsizeCtrl. target registor	:LDIVIHW@@LDIVIHW */
	USHORT				inWidth;
	/**< Line Division Processing Output Horizontal Start Position.
	 *  value range[2~16382] target registor	:LDIVOH@@LDIVOH[x] */
	USHORT				outPosX[4];
	/**< Line Division Processing Output Horizontal Pixel Count Register. value range[2~***] Maximum
	 *  setting value depends on the horizontal maximum size of @ref impro_sentop_ctrl() argument of
	 *   @ref  EimproSentopLdivMaxHsizeCtrl. target registor	:LDIVOHW@@LDIVOHW[x] */
	USHORT				outWidth[4];
} TimproLdivArea;

/*类型定义区域*/
typedef struct _ImproSensldiv					ImproSensldiv;
typedef struct _ImproSensldivPrivate				ImproSensldivPrivate;


/*对象结构体区域*/
struct _ImproSensldiv
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sensldiv_get_type(void);
ImproSensldiv*		impro_sensldiv_new();
/**
LDIV macro start.
@param[in]	ch : Channel No.
*/
extern	INT32			impro_sensldiv_start( E_IM_PRO_LDIV_CH ch );
/**
Stop LDIV information
@param[in]	ch : Channel No.
@param[in]	force : force stop option
*/
extern	INT32			impro_sensldiv_stop( E_IM_PRO_LDIV_CH ch, UCHAR force );
/**
LDIV macro control parameter is set.
@param[in]	ch : Channel No.
@param[in]	ldivCtrl : LDIV control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sensldiv_ctrl( E_IM_PRO_LDIV_CH ch, TimproLdivCtrl* ldivCtrl );
/**
The area for Top OB detection is set up.
@param[in]	ch : Channel No.
@param[in]	ldivArea	:The area of LDIV processing. See @ref TimproLdivArea.
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
extern	INT32			impro_sensldiv_set_area( E_IM_PRO_LDIV_CH ch, TimproLdivArea* ldivArea );
/**
A setup of enable access to the built-in RAM of LDIV.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_sensldiv_set_paen( E_IM_PRO_LDIV_CH ch, UCHAR paenTrg );






#endif /* __IMPRO_SENSLDIV_H__ */

