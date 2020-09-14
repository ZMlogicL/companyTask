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


#include <stdio.h>
#include <glib-object.h>
#include "imjpegcommon.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_JPEG_SHARE							(im_jpeg_share_struct_get_type ())
#define IM_JPEG_SHARE(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_JPEG_SHARE, ImJpegShare))
#define IM_JPEG_SHARE_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_JPEG_SHARE, ImJpegShareClass))
#define IM_IS_JPEG_SHARE(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_JPEG_SHARE))
#define IM_IS_JPEG_SHARE_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_JPEG_SHARE))
#define IM_JPEG_SHARE_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_JPEG_SHARE, ImJpegShareClass))


typedef struct _ImJpegShare							ImJpegShare;
typedef struct _ImJpegShareClass					ImJpegShareClass;
typedef struct _ImJpegSharePrivate 				ImJpegSharePrivate;


struct _ImJpegShare
{
	GObject parent;
	DdimUserCustom *ddimUserCustom;
};

struct _ImJpegShareClass
{
	GObjectClass parentClass;
};

GType									im_jpeg_share_struct_get_type(void)	G_GNUC_CONST;
ImJpegShare*					im_jpeg_share_struct_new(void);

/**
  This function set Jpeg encode frame management table data.
  @param [in]	pJpgEncFrmMng		: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
  @remarks		Please call this function after you have made the setting in im_jpeg_ctrl_enc().<br>
				It can set during the encoding process, If the same base configuration to encode.<br>
				If you want to set in during Jpeg encoding process, please set after PBUF and JBUF is running.<br>
*/
extern	gint32	im_jpeg_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function get the base settings for Jpeg encode.
  @param [out]	pJpgEncMng			: Pointer to Jpeg encode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	gint32	im_jpeg_get_ctrl_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng );

/**
  This function get the frame settings for Jpeg encode.
  @param [out]	pJpgEncFrmMng		: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	gint32	im_jpeg_get_ctrl_enc_frame(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function starts as asynchronous processing Jpeg encoded.
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: Systemcall error.
  @remarks		This API uses DDIM_User_Clr_Flg().<br><br>
  				If you want to synchronize, please call im_jpeg_wait_end_enc().
*/
extern	gint32	im_jpeg_start_enc( ImJpegShare*self );

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
extern	gint32	im_jpeg_wait_end_enc(ImJpegShare*self, TimgEncMng* pJpgEncMng, gint32 timeOut );

/**
  This function is restarted from the paused state of Jpeg macro.
  @param [in]	pJpgEncFrmMng			: Pointer to Jpeg encode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG		: Macro running error.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: System call error.
  @remarks		This API uses DDIM_User_Clr_Flg().
*/
extern	gint32	im_jpeg_restart_enc(ImJpegShare*self, TimgEncFrameMng* pJpgEncFrmMng );

/**
  This function set Jpeg decode for skip marker mode.
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG	: Macro is running error.
  @remarks		Please use the skip marker mode after decoding normally once.<br>
  				It can be used to decode the compressed file from the skip marker mode.<br>
*/
extern	gint32	im_jpeg_set_skip_marker_dec( ImJpegShare*self );

/**
  This function set Jpeg decode base management table data before decode process start.
  @param [in]	pJpgDecMng			: pointer to Jpeg decode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	gint32	im_jpeg_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng );

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
extern	gint32	im_jpeg_ctrl_dec_frame(ImJpegShare*self, TimgDecFrameMng* pJpgDecFrmMng );

/**
  This function get the base settings for Jpeg decode.
  @param [out]	pJpgDecMng			: pointer to Jpeg decode base management table
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Success.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	gint32	im_jpeg_get_ctrl_dec(ImJpegShare*self, TimgDecMng* pJpgDecMng );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_JPEG_SHARE_H__ */
