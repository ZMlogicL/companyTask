/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :王睿
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "imimg.h"

#include "jdsimg.h"
#include "dd_top.h"
#include "ddim_user_custom.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImImg, im_img);
#define IM_IMG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImImgPrivate, IM_TYPE_IMG))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// wait usec
#define ImImg_WAIT_USEC( usec )			Dd_ARM_Wait_ns( (usec) * 1000 )

#define ImImg_JPEG_ACCESS_WAIT_USEC		(1)

struct _ImImgPrivate
{
	int a;
};


static void im_img_constructor(ImImg *self)
{
	ImImgPrivate *priv = IM_IMG_GET_PRIVATE(self);
	priv->a = 0;
}

static void im_img_destructor(ImImg *self)
{
	ImImgPrivate *priv = IM_IMG_GET_PRIVATE(self);
	priv->a = 0;
}

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/

/**
 * @brief	IMG initialize.
 * @param	None.
 * @return	None.
 */
VOID im_img_init( ImImg*self )
{
	// IMGPIPEPSW
	IO_IMG.IMGPIPEPSW.word		= 0;
	// MXICMON
	IO_IMG.MXICMON.word			= 0;
	// SRAMPD
	IO_IMG.SRAMPD.bit.JPEGPD	= 0x0F;

	return;
}

/**
 * @brief		The setting of IMGPIPEPSW register is acquired.
 * @param [in]	imgpipesw_typ : IMGPIPEPSW type.
 * @return		IMGPIPEPSW register value.
 */
USHORT im_img_get_imgpipepsw( ImImg*self, ImImgImgpipepswTyp imgpipeswTyp )
{
	USHORT rtnVal = 0;

#ifdef CO_PARAM_CHECK
	if ( imgpipeswTyp > ImImg_IMGPIPEPSW_B2RCNC ) {	// imgpipeswTyp parameter range check
		Ddim_Assertion( ("E:im_img_get_imgpipepsw imgpipeswTyp parameter error=%d\n", imgpipeswTyp) );
		return 0;
	}
#endif // CO_PARAM_CHECK

	switch ( imgpipeswTyp ) {						// IMGPIPEPSW type
		case ImImg_IMGPIPEPSW_R2YSEL :				// R2Y input select
			rtnVal = IO_IMG.IMGPIPEPSW.bit.R2YSEL;
			break;
		case ImImg_IMGPIPEPSW_B2RCNC :				// B2R connection select
			rtnVal = IO_IMG.IMGPIPEPSW.bit.B2RCNC;
			break;
		default :
			/* Nothing special */
			break;
	}

	return rtnVal ;
}

/**
 * @brief		The IMGPIPEPSW register is set.
 * @param [in]	imgpipeswTyp : IMGPIPEPSW type.
 * @param [in]	imgpipeswSel : R2Y input select / B2R connection select.
 * @return		None.
 * @attention	If you select imgpipeswTyp = "ImImg_IMGPIPEPSW_R2YSEL" and imgpipeswSel = "ImImg_IMGPIPEPSW_B2R",<br>
				you must not select imgpipeswTyp = "ImImg_IMGPIPEPSW_B2RCNC" and imgpipeswSel = "ImImg_IMGPIPEPSW_LTM".
 */
VOID im_img_set_imgpipepsw( ImImg*self, ImImgImgpipepswTyp imgpipeswTyp, ImImgImgpipeswSel imgpipeswSel )
{
#ifdef CO_PARAM_CHECK
	if ( imgpipeswTyp > ImImg_IMGPIPEPSW_B2RCNC ) {	// imgpipeswTyp parameter range check
		Ddim_Assertion( ("E:im_img_set_imgpipepsw imgpipeswTyp parameter error=%d\n", imgpipeswTyp) );
		return;
	}

	if ( imgpipeswSel > ImImg_IMGPIPEPSW_NONE ) {	// imgpipeswSel parameter range check
		Ddim_Assertion( ("E:im_img_set_imgpipepsw imgpipeswSel parameter error=%d\n", imgpipeswSel) );
		return;
	}
#endif // CO_PARAM_CHECK

	switch ( imgpipeswTyp ) {						// IMGPIPEPSW type
		case ImImg_IMGPIPEPSW_R2YSEL :				// R2Y input select
			IO_IMG.IMGPIPEPSW.bit.R2YSEL	= (USHORT)imgpipeswSel;
			break;
		case ImImg_IMGPIPEPSW_B2RCNC :				// B2R connection select
			IO_IMG.IMGPIPEPSW.bit.B2RCNC	= (USHORT)imgpipeswSel;
			break;
		default :
			/* Nothing special */
			break;
	}
	return ;
}

/**
 * @brief		The setting of MXICMON register is acquired.
 * @param [in]	mxicmonTyp : MXICMON type.
 * @return		MXICMON register value.
*/
USHORT im_img_get_mxicmon( ImImg*self, ImImgMxicmonTyp mxicmonTyp )
{
	USHORT mxicmonSts = 0;

#ifdef CO_PARAM_CHECK
	if ( mxicmonTyp > ImImg_MXICMON_DEN ) {	// mxicmonTyp parameter range check
		Ddim_Assertion( ("E:im_img_get_mxicmon mxicmonTyp parameter error=%d\n", mxicmonTyp) );
		return 0;
	}
#endif // CO_PARAM_CHECK

	switch ( mxicmonTyp ) {					// MXICMON Type
		case ImImg_MXICMON_VDEN :				// VD enable
			mxicmonSts = IO_IMG.MXICMON.bit.VDEN;
			break;
		case ImImg_MXICMON_HDEN :				// HD enable
			mxicmonSts = IO_IMG.MXICMON.bit.HDEN;
			break;
		case ImImg_MXICMON_SENEN :				// SEN ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.SENEN;
			break;
		case ImImg_MXICMON_SRO1EN :				// SRO1 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.SRO1EN;
			break;
		case ImImg_MXICMON_SRO2EN :				// SRO2 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.SRO2EN;
			break;
		case ImImg_MXICMON_B2B1EN :				// B2B1 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.B2B1EN;
			break;
		case ImImg_MXICMON_B2B2EN :				// B2B2 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.B2B2EN;
			break;
		case ImImg_MXICMON_YO1EN :				// R2Y1 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.YO1EN;
			break;
		case ImImg_MXICMON_YO2EN :				// R2Y2 ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.YO2EN;
			break;
		case ImImg_MXICMON_STATEN :				// STAT ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.STATEN;
			break;
		case ImImg_MXICMON_PASEN :				// PAS ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.PASEN;
			break;
		case ImImg_MXICMON_DEN :					// DISP ERROR enable
			mxicmonSts = IO_IMG.MXICMON.bit.DEN;
			break;
		default :
			/* Nothing special */
			break;
	}
	return mxicmonSts ;
}

/**
 * @brief		The MXICMON register is set.
 * @param [in]	mxicmonTyp : MXICMON type.
 * @param [in]	mxicmonSts : Enable/Disable.
 * @return		None.
*/
VOID im_img_set_mxicmon( ImImg*self, ImImgMxicmonTyp mxicmonTyp, ImImgMxicmonSts  mxicmonSts )
{
#ifdef CO_PARAM_CHECK
	if ( mxicmonTyp > ImImg_MXICMON_DEN ) {		// mxicmonTyp parameter range check
		Ddim_Assertion( ("E:im_img_set_mxicmon mxicmonTyp parameter error=%d\n", mxicmonTyp) );
		return;
	}
	if ( mxicmonSts > ImImg_MXICMON_ENABLE ) {	// mxicmonSts parameter range check
		Ddim_Assertion( ("E:im_img_set_mxicmon mxicmonSts parameter error=%d\n", mxicmonSts) );
		return;
	}
#endif // CO_PARAM_CHECK

	switch ( mxicmonTyp ) {					// MXICMON type
		case ImImg_MXICMON_VDEN :				// VD enable
			IO_IMG.MXICMON.bit.VDEN		= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_HDEN :				// HD enable
			IO_IMG.MXICMON.bit.HDEN		= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_SENEN :				// SEN ERROR enable
			IO_IMG.MXICMON.bit.SENEN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_SRO1EN :				// SRO1 ERROR enable
			IO_IMG.MXICMON.bit.SRO1EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_SRO2EN :				// SRO2 ERROR enable
			IO_IMG.MXICMON.bit.SRO2EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_B2B1EN :				// B2B1 ERROR enable
			IO_IMG.MXICMON.bit.B2B1EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_B2B2EN :				// B2B2 ERROR enable
			IO_IMG.MXICMON.bit.B2B2EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_YO1EN :				// R2Y1 ERROR enable
			IO_IMG.MXICMON.bit.YO1EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_YO2EN :				// R2Y2 ERROR enable
			IO_IMG.MXICMON.bit.YO2EN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_STATEN :				// STAT ERROR enable
			IO_IMG.MXICMON.bit.STATEN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_PASEN :				// PAS ERROR enable
			IO_IMG.MXICMON.bit.PASEN	= (USHORT)mxicmonSts;
			break;
		case ImImg_MXICMON_DEN :					// DISP ERROR enable
			IO_IMG.MXICMON.bit.DEN		= (USHORT)mxicmonSts;
			break;
		default :
			/* Nothing special */
			break;
	}
	return ;
}

/**
 * @brief		The setting of SRAMPD register is acquired.
 * @param [in]	srampdTyp : SRAMPD type.
 * @return		TRUE:Power down ON / FALSE:Power down OFF.
*/
BOOL im_img_get_srampd( ImImg*self, ImImgSrampdTyp srampdTyp )
{
	UCHAR	jpegpd		= 0x00;
	BOOL	powerDown	= FALSE;

#ifdef CO_PARAM_CHECK
	if ( srampdTyp > ImImg_SRAMPD_C ) {	// srampdTyp parameter range check
		Ddim_Assertion( ("E:im_img_get_srampd srampdTyp parameter error=%d\n", srampdTyp) );
		return powerDown;
	}
#endif // CO_PARAM_CHECK

	jpegpd = IO_IMG.SRAMPD.bit.JPEGPD;

	switch ( srampdTyp ) {					// SRAMPD type
		case ImImg_SRAMPD_Y01 :				// Data placement conversion PBUF for Y0-1
			if ( ( jpegpd & 0x08 ) != 0x00 ) {
				powerDown = TRUE;
			}
			break;
		case ImImg_SRAMPD_Y23 :				// Data placement conversion PBUF for Y2-3
			if ( ( jpegpd & 0x04 ) != 0x00 ) {
				powerDown = TRUE;
			}
			break;
		case ImImg_SRAMPD_C :				// Data placement conversion PBUF for C
			if ( ( jpegpd & 0x02 ) != 0x00 ) {
				powerDown = TRUE;
			}
			break;
		default :
			/* Nothing special */
			break;
	}

	return powerDown;
}

/**
 * @brief		The SRAMPD register is set.
 * @param [in]	srampdTyp : SRAMPD type.
 * @param [in]	powerDown : TRUE:Power down ON / FALSE:Power down OFF.
 * @return		None.
 * @attention	If you select powerDown = "FALSE:Power down OFF", wait 1us until jpeg access.
*/
VOID im_img_set_srampd( ImImg*self, ImImgSrampdTyp srampdTyp, BOOL powerDown )
{
	UCHAR jpegpd = 0x00;

#ifdef CO_PARAM_CHECK
	if ( srampdTyp > ImImg_SRAMPD_C ) {	// srampdTyp parameter range check
		Ddim_Assertion( ("E:im_img_set_srampd srampdTyp parameter error=%d\n", srampdTyp) );
		return;
	}

	if ( powerDown > TRUE ) {	// powerDown parameter range check
		Ddim_Assertion( ("E:im_img_set_srampd powerDown parameter error=%d\n", powerDown) );
		return;
	}
#endif // CO_PARAM_CHECK

	jpegpd = IO_IMG.SRAMPD.bit.JPEGPD;

	switch ( srampdTyp ) {					// SRAMPD type
		case ImImg_SRAMPD_Y01 :				// Data placement conversion PBUF for Y0-1
			if ( powerDown ) {
				jpegpd |= 0x08;
			}
			else {
				jpegpd &= 0x07;
			}
			break;
		case ImImg_SRAMPD_Y23 :				// Data placement conversion PBUF for Y2-3
			if ( powerDown ) {
				jpegpd |= 0x04;
			}
			else {
				jpegpd &= 0x0B;
			}
			break;
		case ImImg_SRAMPD_C :				// Data placement conversion PBUF for C
			if ( powerDown ) {
				jpegpd |= 0x02;
			}
			else {
				jpegpd &= 0x0D;
			}
			break;
		default :
			/* Nothing special */
			break;
	}

	IO_IMG.SRAMPD.bit.JPEGPD = jpegpd;

	if ( !powerDown ) {
		ImImg_WAIT_USEC( ImImg_JPEG_ACCESS_WAIT_USEC );
	}

	return;
}

ImImg *im_img_new(void)
{
	ImImg* self = k_object_new_with_private(IM_TYPE_IMG,sizeof(ImImgPrivate));
	return self;
}
