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

#ifndef __IM_IMG_H__
#define __IM_IMG_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_IMG		(im_img_get_type())
#define IM_IMG(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImImg))
#define IM_IS_IMG(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_IMG))
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/

typedef struct 				_ImImg ImImg;
typedef struct 				_ImImgPrivate ImImgPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** IMGPIPEPSW type */
typedef enum {
	ImImg_IMGPIPEPSW_R2YSEL = 0,		/**< IMGPIPEPSW.R2YSEL : R2Y input select */
	ImImg_IMGPIPEPSW_B2RCNC			/**< IMGPIPEPSW.B2RCNC : B2R connection select */
} ImImgImgpipepswTyp;

/** IMGPIPEPSW select */
typedef enum {
	ImImg_IMGPIPEPSW_B2R = 0,		/**< [R2Y input]B2R  / [B2R connection]NONE */
	ImImg_IMGPIPEPSW_LTM,			/**< [R2Y input]LTM  / [B2R connection]LTM  */
	ImImg_IMGPIPEPSW_NONE			/**< [R2Y input]NONE / [B2R connection]NONE */
} ImImgImgpipeswSel;

/** MXICMON type */
typedef enum {
	ImImg_MXICMON_VDEN = 0,			/**< MXICMON.VDEN   : MXIC VD enable */
	ImImg_MXICMON_HDEN,				/**< MXICMON.HDEN   : MXIC HD enable */
	ImImg_MXICMON_SENEN,				/**< MXICMON.SENEN  : MXIC SEN  ERROR enable */
	ImImg_MXICMON_SRO1EN,			/**< MXICMON.SRO1EN : MXIC SRO1 ERROR enable */
	ImImg_MXICMON_SRO2EN,			/**< MXICMON.SRO2EN : MXIC SRO2 ERROR enable */
	ImImg_MXICMON_B2B1EN,			/**< MXICMON.B2B1EN : MXIC B2B1 ERROR enable */
	ImImg_MXICMON_B2B2EN,			/**< MXICMON.B2B2EN : MXIC B2B2 ERROR enable */
	ImImg_MXICMON_YO1EN,				/**< MXICMON.YO1EN  : MXIC R2Y1 ERROR enable */
	ImImg_MXICMON_YO2EN,				/**< MXICMON.YO2EN  : MXIC R2Y2 ERROR enable */
	ImImg_MXICMON_STATEN,			/**< MXICMON.STATEN : MXIC STAT ERROR enable */
	ImImg_MXICMON_PASEN,				/**< MXICMON.PASEN  : MXIC PAS  ERROR enable */
	ImImg_MXICMON_DEN				/**< MXICMON.DEN    : MXIC DISP ERROR enable */
} ImImgMxicmonTyp;

/** MXICMON status */
typedef enum {
	ImImg_MXICMON_DISABLE = 0,		/**< Disable */
	ImImg_MXICMON_ENABLE				/**< Enable  */
} ImImgMxicmonSts;

/** SRAMPD type */
typedef enum {
	ImImg_SRAMPD_Y01 = 0,			/**< Data placement conversion PBUF for Y0-1 */
	ImImg_SRAMPD_Y23,				/**< Data placement conversion PBUF for Y2-3 */
	ImImg_SRAMPD_C					/**< Data placement conversion PBUF for C    */
} ImImgSrampdTyp;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Nothing Special

struct _ImImg {
	KObject parent;
};

KConstType 		    im_img_get_type(void);
ImImg*		        im_img_new(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief	IMG initialize.
 * @return	None.
 */
VOID	im_img_init( ImImg*self );

/**
 * @brief		The setting of IMGPIPEPSW register is acquired.
 * @param [in]	imgpipeswTyp : IMGPIPEPSW type.
 * @return		IMGPIPEPSW register value.
*/
USHORT	im_img_get_imgpipepsw( ImImg*self, ImImgImgpipepswTyp imgpipeswTyp );

/**
 * @brief		The IMGPIPEPSW register is set.
 * @param [in]	imgpipeswTyp : IMGPIPEPSW type.
 * @param [in]	imgpipeswSel : R2Y input select / B2R connection select.
 * @return		None.
 * @attention	If you select imgpipeswTyp = "ImImg_IMGPIPEPSW_R2YSEL" and imgpipeswSel = "ImImg_IMGPIPEPSW_B2R",<br>
				you must not select imgpipeswTyp = "ImImg_IMGPIPEPSW_B2RCNC" and imgpipeswSel = "ImImg_IMGPIPEPSW_LTM".
 */
VOID	im_img_set_imgpipepsw( ImImg*self, ImImgImgpipepswTyp imgpipeswTyp, ImImgImgpipeswSel imgpipeswSel );

/**
 * @brief		The setting of MXICMON register is acquired.
 * @param [in]	mxicmonTyp : MXICMON type.
 * @return		MXICMON register value.
*/
USHORT	im_img_get_mxicmon( ImImg*self, ImImgMxicmonTyp mxicmonTyp );

/**
 * @brief		The MXICMON register is set.
 * @param [in]	mxicmonTyp : MXICMON type.
 * @param [in]	mxicmonSts : Enable/Disable.
 * @return		None.
*/
VOID	im_img_set_mxicmon( ImImg*self, ImImgMxicmonTyp mxicmonTyp, ImImgMxicmonSts mxicmonSts );

/**
 * @brief		The setting of SRAMPD register is acquired.
 * @param [in]	srampdTyp : SRAMPD type.
 * @return		TRUE:Power down ON / FALSE:Power down OFF.
*/
BOOL im_img_get_srampd( ImImg*self, ImImgSrampdTyp srampdTyp );

/**
 * @brief		The SRAMPD register is set.
 * @param [in]	srampdTyp : SRAMPD type.
 * @param [in]	powerDown : TRUE:Power down ON / FALSE:Power down OFF.
 * @return		None.
 * @attention	If you select powerDown = "FALSE:Power down OFF", wait 1us until jpeg access.
*/
VOID im_img_set_srampd( ImImg*self, ImImgSrampdTyp srampdTyp, BOOL powerDown );

#endif /* __IM_IMG_H__ */
/*	@}*/
/*@}*/
