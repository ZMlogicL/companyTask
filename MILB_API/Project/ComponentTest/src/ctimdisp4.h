/*
 *ctimdisp4.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP4_H__
#define __CT_IM_DISP4_H__

#include <glib-object.h>

G_BEGIN_DECLS
/*
 * 以下开始宏声明
 * */
#define CT_TYPE_IM_DISP4						(ct_im_disp4_get_type ())
#define CT_IM_DISP4(widget)					(G_TYPE_CHECK_INSTANCE_CAST ((widget), \
					CT_TYPE_IM_DISP4, CtImDisp4))
#define CT_IM_DISP4_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_DISP4, CtImDisp4Class))
#define CT_IS_IM_DISP4(widget)				(G_TYPE_CHECK_INSTANCE_TYPE ((widget), CT_TYPE_IM_DISP4))
#define CT_IS_IM_DISP4_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_DISP4))
#define CT_IM_DISP4_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_DISP4, CtImDisp4Class))

/*
 * 以下开始类结构体声明
 * */
typedef struct _CtImDisp4 		CtImDisp4;
typedef struct _CtImDisp4Class 	CtImDisp4Class;
typedef struct _CtImDisp4Private 	CtImDisp4Private;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
typedef enum {
	CtImDisp4_LCD_DISP_SEL_HDMI = 0,	/**< Output to HDMI.	*/
	CtImDisp4_LCD_DISP_SEL_LCD,			/**< Output to LCD.		*/
	CtImDisp4_LCD_DISP_SEL_END
} CtImDisp4ELcdDispSel;

struct _CtImDisp4
{
	GObject parent;
	/*public*/
	CtImDisp4Private *privCtImDisp4;
};

struct _CtImDisp4Class
{
	GObjectClass parentclass;
};

/*
 * 如下开始public方法声明
 * */
GType 				ct_im_disp4_get_type(void) G_GNUC_CONST;
CtImDisp4 *		ct_im_disp4_new(void);

guint32 *			ct_im_disp4_get_r_anti_tbla(CtImDisp4 *self);
guint32 *			ct_im_disp4_get_g_anti_tbla(CtImDisp4 *self);
guint32 *			ct_im_disp4_get_b_anti_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_r_gamma_out_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_g_gamma_out_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_b_gamma_out_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_r_gamma_out_tblb(CtImDisp4 *self);
gushort *			ct_im_disp4_get_g_gamma_out_tblb(CtImDisp4 *self);
gushort *			ct_im_disp4_get_b_gamma_out_tblb(CtImDisp4 *self);
guint32 *			ct_im_disp4_get_r_full_tbl(CtImDisp4 *self);
guint32 *			ct_im_disp4_get_g_full_tbl(CtImDisp4 *self);
guint32 *			ct_im_disp4_get_b_full_tbl(CtImDisp4 *self);
gushort *			ct_im_disp4_get_luminance_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_luminance_tblb(CtImDisp4 *self);
gushort *			ct_im_disp4_get_gain_tbla(CtImDisp4 *self);
gushort *			ct_im_disp4_get_gain_tblb(CtImDisp4 *self);

G_END_DECLS

#endif /* __CT_IM_DISP4_H__ */
