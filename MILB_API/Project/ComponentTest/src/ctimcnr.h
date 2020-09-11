/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-00
*@author              :王印斌
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

#ifndef __CT_IM_CNR_H__
#define __CT_IM_CNR_H__

#include "im_cnr.h"
#include "ctimcnr1.h"
#include "driver_common.h"
#include <glib-object.h>

G_BEGIN_DECLS

#define CT_TYPE_IM_CNR         		 (ct_im_cnr_get_type())
#define CT_IM_CNR(obj)         		 (G_TYPE_CHECK_INSTANCE_CAST(obj,CtImCnr))
#define CT_IM_CNR_CLASS(kclass) 	 (G_TYPE_CHECK_CLASS_CAST((klass), CT_TYPE_IM_CNR, CtImCnrClass))
#define CT_IS_IM_CNR(obj)      		 (G_TYPE_CHECK_INSTANCE_TYPE(obj,CT_TYPE_IM_CNR))
#define CT_IS_IM_CNR_CLASS(obj)		 (G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_CNR))
#define CT_IM_CNR_HGET_CLASS(kclass) (G_TYPE_INSTANCE_GET_CLASS((obj), CT_TYPE_IM_CNR, CtImCnrClass))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImMe_D_IM_CNR_R2Y_MACRO_ENABLE	// R2Y macro process selector

#define CtImCnr_D_IM_CNR_TEST_H_PIXS	(640)
#define CtImCnr_D_IM_CNR_TEST_V_PIXS	(480)

#define CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR	(0x7D000000)

// Src address(YCC422 Planar format)
#define CtImCnr_D_IM_CNR_TEST_IMG_SRC_Y_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR)						// 0x7D000000
#define CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_SRC_ADDR + \
	CtImCnr_D_IM_CNR_TEST_H_PIXS * \
	CtImCnr_D_IM_CNR_TEST_V_PIXS)								// 0x7D04B000
#define CtImCnr_D_IM_CNR_TEST_IMG_SRC_CR_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_SRC_CB_ADDR + \
	CtImCnr_D_IM_CNR_TEST_H_PIXS * \
	CtImCnr_D_IM_CNR_TEST_V_PIXS / 2)							// 0x7D070800
#define CtImCnr_D_IM_CNR_TEST_IMG_SRC_BYTES\
	(CtImCnr_D_IM_CNR_TEST_H_PIXS * \
	CtImCnr_D_IM_CNR_TEST_V_PIXS * 2)							// 0x96000

// Dst address(YCC422 Planar format)
#define CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR		(0x7E000000)																		// 0x7E000000

#define CtImCnr_D_IM_CNR_TEST_IMG_DST_Y_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR)						// 0x7E000000
#define CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_DST_ADDR + \
	CtImCnr_D_IM_CNR_TEST_H_PIXS * \
	CtImCnr_D_IM_CNR_TEST_V_PIXS)								// 0x7E04B000
#define CtImCnr_D_IM_CNR_TEST_IMG_DST_CR_ADDR\
	(CtImCnr_D_IM_CNR_TEST_IMG_DST_CB_ADDR + \
	CtImCnr_D_IM_CNR_TEST_H_PIXS * \
	CtImCnr_D_IM_CNR_TEST_V_PIXS / 2)							// 0x7E070800
#define CtImCnr_D_IM_CNR_TEST_IMG_DST_BYTES\
		(CtImCnr_D_IM_CNR_TEST_H_PIXS *\
		 CtImCnr_D_IM_CNR_TEST_V_PIXS * 2)						// 0x96000

// Temporary address(for CNR macro use)
#define CtImCnr_D_IM_CNR_TEST_IMG_TMP_ADDR		(0x7F000000)																		// 0x7F000000
#define CtImCnr_D_IM_CNR_TEST_IMG_TMP_BYTES		(CtImCnr_D_IM_CNR_TEST_V_PIXS * 576)														// 0x43800

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define io_cnr(ch)	\
	((D_IM_CNR_CH_0 == ((ch))) ? &IO_CNR1 : (D_IM_CNR_CH_1 == ((ch))) ? &IO_CNR2 : &IO_CNR3)

typedef struct _CtImCnr 		CtImCnr;
typedef struct _CtImCnrPrivate	CtImCnrPrivate;
typedef struct _CtImCnrClass 	CtImCnrClass;

struct _CtImCnr {
	GObject parent;
	UINT32 ctId;
};

struct _CtImCnrClass {
	GObjectClass parentclass;
}

GType 		ct_im_cnr_get_type(void) G_GNUC_CONST;
CtImCnr* 	ct_im_cnr_new(void);

void ct_im_cnr_run(CtImCnr* self, 
				const UINT32 ct_idx_2nd, 
				const UINT32 ct_idx_3rd);
void ct_im_cnr_main(INT32 argc, CHAR** argv);

void ct_im_cnr_get_loop_cnt(UCHAR ch, UCHAR* sta, UCHAR* end);

G_END_DECLS
#endif /* __CT_IM_CNR_H__ */
