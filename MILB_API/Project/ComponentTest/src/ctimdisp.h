/*
 *ctimdisp.h
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-02
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

#ifndef __CT_IM_DISP_H__
#define __CT_IM_DISP_H__

#include <klib.h>

#include "driver_common.h"

#define CT_TYPE_IM_DISP	(ct_im_disp_get_type())
#define CT_IM_DISP(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, CtImDisp))
#define CT_IS_IM_DISP(obj)			K_TYPE_CHECK_INSTANCE_TYPE(obj, CT_TYPE_IM_DISP)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtImDisp_CO_DEBUG_DISP
#define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

typedef struct _CtImDisp CtImDisp;
typedef struct _CtImDispPrivate		CtImDispPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
typedef enum {
	CtImDisp_SET_GAMMA_R_FULL =					0x001,	/**< Set r_full Gamma*/
	CtImDisp_SET_GAMMA_G_FULL =					0x002,	/**< Set g_full Gamma*/
	CtImDisp_SET_GAMMA_B_FULL =					0x004,	/**< Set b_full Gamma*/
	CtImDisp_SET_GAMMA_ALL_FULL =				0x007,	/**< Set all full Gamma*/
	CtImDisp_SET_GAMMA_R_DELTA_FULL =			0x008,	/**< Set r_delta Gamma*/
	CtImDisp_SET_GAMMA_G_DELTA_FULL =			0x010,	/**< Set g_delta Gamma*/
	CtImDisp_SET_GAMMA_B_DELTA_FULL =			0x020,	/**< Set b_delta Gamma*/
	CtImDisp_SET_GAMMA_ALL_DELTA_FULL =			0x038,	/**< Set all delta Gamma*/

	CtImDisp_SET_GAMMA_REVERSE_R_FULL =			0x040,	/**< Set reverse r_full Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_G_FULL =			0x080,	/**< Set reverse g_full Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_B_FULL =			0x100,	/**< Set reverse b_full Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_ALL_FULL =		0x1C0,	/**< Set reverse all full Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_R_DELTA_FULL =	0x200,	/**< Set reverse r_delta Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_G_DELTA_FULL =	0x400,	/**< Set reverse g_delta Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_B_DELTA_FULL =	0x800,	/**< Set reverse b_delta Gamma*/
	CtImDisp_SET_GAMMA_REVERSE_ALL_DELTA_FULL =	0xE00,	/**< Set reverse all delta Gamma*/
	CtImDisp_SET_GAMMA_ALL =					0xFFF,	/**< Set all */
}CtImDispSetGamma;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

struct _CtImDisp{
	KObject parent;
	CtImDispPrivate *privCtImDisp;
};

KConstType 		ct_im_disp_get_type(void);
CtImDisp *		ct_im_disp_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
void 				ct_im_disp_pctest_main(CtImDisp *self);
void 				ct_im_disp_main_cb(CtImDisp *self, kint32 argc, char **argv);
kuchar *			ct_im_disp_get_pclk_counter(CtImDisp *self);
kuchar *			ct_im_disp_get_hclk_counter(CtImDisp *self);

#endif /* __CT_IM_DISP_H__ */
