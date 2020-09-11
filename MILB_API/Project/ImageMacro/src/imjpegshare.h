/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_JPEG_SHARE_H__
#define __IM_JPEG_SHARE_H__


#include <klib.h>
#include "imjpegcommon.h"


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_JPEG_SHARE				(im_jpeg_share_get_type())
#define IM_JPEG_SHARE	(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImJpegShare))
#define IM_IS_JPEG_SHARE(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_JPEG_SHARE))


typedef struct _ImJpegShare 				ImJpegShare;
typedef struct _ImJpegSharePrivate 	ImJpegSharePrivate;


struct _ImJpegShare
{
	KObject parent;
};


KConstType 		    		im_jpeg_share_get_type(void);
ImJpegShare*		        im_jpeg_share_new(void);
/**
  This function set Jpeg encode frame management table data.
  @param [in]	pJpgEncFrmMng		: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
  @remarks		Please call this function after you have made the setting in im_jpeg_ctrl_enc().<br>
				It can set during the encoding process, If the same base configuration to encode.<br>
				If you want to set in during Jpeg encoding process, please set after PBUF and JBUF is running.<br>
*/
extern	kint32	im_jpeg_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function get the base settings for Jpeg encode.
  @param [out]	pJpgEncMng			: Pointer to Jpeg encode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	kint32	im_jpeg_get_ctrl_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng );

/**
  This function get the frame settings for Jpeg encode.
  @param [out]	pJpgEncFrmMng		: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	kint32	im_jpeg_get_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function starts as asynchronous processing Jpeg encoded.
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: Systemcall error.
  @remarks		This API uses DDIM_User_Clr_Flg().<br><br>
  				If you want to synchronize, please call im_jpeg_wait_end_enc().
*/
extern	kint32	im_jpeg_start_enc( ImJpegShare*self );

/**
  This function wait end of Jpeg encode process.
  @param [out]	pJpgEncMng				: Pointer to Jpeg encode result table
  @param [in]	timeOut					: Time-out period
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_ENCODE_PAUSE		: Pause end (or limit size over end)
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		D_IM_JPEG_AXI_ERROR			: AXI bus error.
  @retval		ImJpegCommon_D_IM_JPEG_TIMEOUT			: Encode timeout.
  @retval		ImJpegCommon_D_IM_JPEG_ENCODE_ERR		: Encode error.
  @remarks		This API uses DDIM_User_Twai_Flg().
*/
extern	kint32	im_jpeg_wait_end_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng, kint32 timeOut );

/**
  This function is restarted from the paused state of Jpeg macro.
  @param [in]	pJpgEncFrmMng			: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG		: Macro running error.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: System call error.
  @remarks		This API uses DDIM_User_Clr_Flg().
*/
extern	kint32	im_jpeg_restart_enc(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function set Jpeg decode for skip marker mode.
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG	: Macro is running error.
  @remarks		Please use the skip marker mode after decoding normally once.<br>
  				It can be used to decode the compressed file from the skip marker mode.<br>
*/
extern	kint32	im_jpeg_set_skip_marker_dec( ImJpegShare*self );

/**
  This function set Jpeg decode base management table data before decode process start.
  @param [in]	pJpgDecMng			: pointer to Jpeg decode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	kint32	im_jpeg_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng );

/**
  This function set Jpeg decode frame management table data.
  @param [in]	pJpgDecFrmMng		: pointer to Jpeg decode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
  @remarks		Please call this function after you have made the setting in im_jpeg_ctrl_dec()<br>
				It can also set during the decoding process, If the same base configuration to decode in a row<br>
				If you want to set in during Jpeg encoding process, please set after PBUF and JBUF is running.<br>
  @attention	Cutout function is only supported the following format.<br>
				:: YCC444(RGB) planer format<br>
				:: YCC422 planer format<br>
				:: YCC422 planer Y and dot sequential CbCr format<br>
				:: YCC422 tile format<br>
				:: YCC400 planer format
*/
extern	kint32	im_jpeg_ctrl_dec_frame(ImJpegShare*self, TimgDecFrameMng* pJpgDecFrmMng );

/**
  This function get the base settings for Jpeg decode.
  @param [out]	pJpgDecMng			: pointer to Jpeg decode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	kint32	im_jpeg_get_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng );


#ifdef __cplusplus
}
#endif


#endif /* __IM_JPEG_SHARE_H__ */
