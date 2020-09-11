/*
 *ctimdisp4.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP4_H__
#define __CT_IM_DISP4_H__

#include <klib.h>

#define CT_TYPE_IM_DISP4	(ct_im_disp4_get_type())
#define CT_IM_DISP4(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp4))
#define CT_IS_IM_DISP4(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP4)

typedef struct _CtImDisp4 					CtImDisp4;
typedef struct _CtImDisp4Private		CtImDisp4Private;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
typedef enum {
	CtImDisp4_LCD_DISP_SEL_HDMI = 0,	/**< Output to HDMI.	*/
	CtImDisp4_LCD_DISP_SEL_LCD,			/**< Output to LCD.		*/
	CtImDisp4_LCD_DISP_SEL_END
} CtImDisp4ELcdDispSel;

struct _CtImDisp4{
	KObject parent;
	CtImDisp4Private *privCtImDisp4;
};

KConstType 		ct_im_disp4_get_type(void);
CtImDisp4 *		ct_im_disp4_new(void);

kuint32 *			ct_im_disp4_get_r_anti_tbla(CtImDisp4 *self);
kuint32 *			ct_im_disp4_get_g_anti_tbla(CtImDisp4 *self);
kuint32 *			ct_im_disp4_get_b_anti_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_r_gamma_out_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_g_gamma_out_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_b_gamma_out_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_r_gamma_out_tblb(CtImDisp4 *self);
kushort *			ct_im_disp4_get_g_gamma_out_tblb(CtImDisp4 *self);
kushort *			ct_im_disp4_get_b_gamma_out_tblb(CtImDisp4 *self);
kuint32 *			ct_im_disp4_get_r_full_tbl(CtImDisp4 *self);
kuint32 *			ct_im_disp4_get_g_full_tbl(CtImDisp4 *self);
kuint32 *			ct_im_disp4_get_b_full_tbl(CtImDisp4 *self);
kushort *			ct_im_disp4_get_luminance_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_luminance_tblb(CtImDisp4 *self);
kushort *			ct_im_disp4_get_gain_tbla(CtImDisp4 *self);
kushort *			ct_im_disp4_get_gain_tblb(CtImDisp4 *self);

#endif /* __CT_IM_DISP4_H__ */
