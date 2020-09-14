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


#ifndef __IM_JPEG_SKIP_H__
#define __IM_JPEG_SKIP_H__


#include <stdio.h>
#include <glib-object.h>
#include "imjpegcommon.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_JPEG_SKIP							(im_jpeg_skip_struct_get_type ())
#define IM_JPEG_SKIP(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_JPEG_SKIP, ImJpegSkip))
#define IM_JPEG_SKIP_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_JPEG_SKIP, ImJpegSkipClass))
#define IM_IS_JPEG_SKIP(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_JPEG_SKIP))
#define IM_IS_JPEG_SKIP_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_JPEG_SKIP))
#define IM_JPEG_SKIP_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_JPEG_SKIP, ImJpegSkipClass))


typedef struct _ImJpegSkip			ImJpegSkip;
typedef struct _ImJpegSkipClass		ImJpegSkipClass;
typedef struct _ImJpegSkipPrivate 		ImJpegSkipPrivate;


struct _ImJpegSkip
{
	GObject parent;
	DdimUserCustom *ddimUserCustom;
};

struct _ImJpegSkipClass
{
	GObjectClass parentClass;
};


GType								im_jpeg_skip_struct_get_type(void)	G_GNUC_CONST;
ImJpegSkip*					im_jpeg_skip_struct_new(void);

/**
 This function starts as asynchronous processing Jpeg decoded for Marker Skip.
 @retval		ImJpegCommon_D_IM_JPEG_OK									: Normal end.
 @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG							: Macro is running error.
 @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR						: System call error.
 @remarks		Please use the skip marker mode after decoding normally once.<br>
 It can be used to decode the compressed file from the skip marker mode.<br>
 If you want to synchronize, please call im_jpeg_wait_end_dec().<br>
 This API uses DDIM_User_Clr_Flg().
 */
extern	gint32 im_jpeg_start_skip_marker_dec( ImJpegSkip*self );

/**
  This function wait end of Jpeg decode process.
  @param [out]	pJpgDecMng				: pointer to Jpeg decode result table
  @param [in]	timeOut					: Time-out period
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_DECODE_PAUSE		: Pause end (or limit size over end)
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		D_IM_JPEG_AXI_ERROR			: AXI bus error
  @retval		ImJpegCommon_D_IM_JPEG_TIMEOUT			: Decode timeout.
  @retval		ImJpegCommon_D_IM_JPEG_DECODE_ERR		: Decode error
  @remarks		This API uses DDIM_User_Twai_Flg().
*/
extern	gint32	im_jpeg_wait_end_dec(ImJpegSkip*self, TimgDecMng* pJpgDecMng, gint32 timeOut );

/**
  This function is restarted from the paused state of Jpeg macro.
  @param [in]	pJpgDecFrmMng			: Pointer to Jpeg decode frame management table
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_RUNNING_NG		: Macro running error.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: System call error.
  @remarks		This API uses DDIM_User_Clr_Flg().
*/
extern	gint32	im_jpeg_restart_dec(ImJpegSkip*self,  TimgDecFrameMng* pJpgDecFrmMng );

/**
  This function forcibly stop Jpeg encode process.
  @remarks		Please call to process error. In addition, please call im_jpeg_close() after call this function.
*/
extern	void	im_jpeg_stop( ImJpegSkip*self );

/**
  This function is an interrupt handler.
  @remarks		This API uses DDIM_User_Set_Flg().
*/
extern	void	im_jpeg_int_handler( ImJpegSkip*self );

/**
  This function get AXI (PBUF and JBUF) status of frame processing.
  @param [out]	pJpAxiState			: pointer to AXI (JBUF and PBUF) state
  @retval		ImJpegCommon_D_IM_JPEG_OK			: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR	: Parameter error.
*/
extern	gint32	im_jpeg_get_axi_state(ImJpegSkip*self,  EimgAxiSt* pJpAxiState );

/**
  This function get processed image size (number of lines).
  @retval		gushort 	: processed vertical image lines
*/
extern	gushort	im_jpeg_get_line_cnt( ImJpegSkip*self );

/**
  This function get processed image size (number of sector).
  @retval		gulong 	: processed sector size (512 byte unit)
*/
extern	gulong	im_jpeg_get_sect_cnt( ImJpegSkip*self );

#ifdef CO_DDIM_UTILITY_USE
/** @name Utility Functions
@{*/

//---------------------- utility section -------------------------------

/**
  This function performs a Jpeg decoding process.
  @param [in]	inputParam 				: pointer to Jpeg decode input parameters
  @param [out]	outputParam				: pointer to Jpeg decode output parameters
  @retval		ImJpegCommon_D_IM_JPEG_OK				: Normal end.
  @retval		ImJpegCommon_D_IM_JPEG_PARAM_ERROR		: Parameter error.
  @retval		ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR	: System call error.
  @retval		ImJpegCommon_D_IM_JPEG_DECODE_PAUSE		: limit size over.
  @retval		D_IM_JPEG_AXI_ERROR			: AXI bus error
  @retval		ImJpegCommon_D_IM_JPEG_DECODE_ERR		: Decode error
  @retval		ImJpegCommon_D_IM_JPEG_TIMEOUT			: Decode time out
*/
extern	gint32 im_jpeg_decode_sync(ImJpegSkip*self,  TimgDecInput* inputParam, TimgDecOutput* outputParam );

//---------------------- colabo  section -------------------------------

/*  @}*/
#endif	// CO_DDIM_UTILITY_USE


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_JPEG_SKIP_H__ */
