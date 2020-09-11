#include "jdsme.h"
#include "im_me.h"
#include <string.h>
#include <stdlib.h>

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif //CO_ACT_CLOCK | CO_ACT_HCLOCK | CO_ACT_PCLOCK

#include "ddim_user_custom.h"
#include "ctimme.h"

G_DEFINE_TYPE(CtImMe, ct_im_me, G_TYPE_OBJECT); 
#define CT_IM_ME_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CT_TYPE_IM_ME, CtImMePrivate))

#define CtImMe_PC_DEBUG

struct _CtImMePrivate 
{
};

typedef struct {
	T_IM_ME_CTRL	ctrl;
	T_IM_ME_START	start;
} T_IM_ME_PARAM;

static void ctCmMeCallback(void);
static void ctImMeCtrl(void);
static void ctImMeStart(void);
static void ctImMeErrCtrl(void);
static void ctImMeErrStart(void);
static void ctImMeTest(T_IM_ME_PARAM* meParam);
static void ctImMeTest2(void);

static void ct_im_me_constructor(CtImMe *self)
{
}

static void ct_im_me_destructor(CtImMe  *self)
{
}

static void ctCmMeCallback(void)
{
	Ddim_Print(("ctCmMeCallback\n"));
}

static void ctImMeCtrl(void)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_ME_CTRL	ctrl[] = {
		[ 0 ] = {	// Max.
			.apbbrg = {
				.pp_enable[ 0 ]			= 0,
				.pp_enable[ 1 ]			= 0,
				.pp_enable[ 2 ]			= 0,
				.int_mode				= 0,
				.interval				= 0,
			},
			.pme[ 0 ] = {
				.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
				.ref_txb				= D_IM_ME_REFTXB_TOP,
				.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
				.bank_num				= D_IM_ME_BANKNUM_1,
				.m1org_mode[ 0 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 1 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 2 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 3 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1correct = {
					.front_ky			= 0,
					.back_ky			= 0,
					.front_kx			= 0,
					.back_kx			= 0,
					.mode				= 1,
					.front_h			= 0,
					.front_v			= 0,
					.back_h				= 0,
					.back_v				= 0,
				},
				.m1mc = {
					.p_pic				= 0,
					.b_pic				= 0,
				},
				.m1splt = {
					.mode				= D_IM_ME_SPLITMODE_NORMAL,
					.th_h				= 0,
					.th_v				= 0,
				},
				.m1skip					= D_IM_ME_OFF,
				.m1sad = {
					.upper				= 0,
					.lower				= 0,
				},
				.m1adjust = {
					.wait_cycle			= 0,
					.wait_onoff			= D_IM_ME_OFF,
				},
				.m1pause = {
					.pause_line			= 0,
					.pause_onoff		= D_IM_ME_OFF,
				},
				.m1limit = {
					.v_plus				= 0,
					.v_minus			= 0,
					.h_plus				= 0,
					.h_minus			= 0,
				},
			},
			.pme[ 1 ] = {
				.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
				.ref_txb				= D_IM_ME_REFTXB_TOP,
				.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
				.bank_num				= D_IM_ME_BANKNUM_1,
				.m1org_mode[ 0 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 1 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 2 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 3 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1correct = {
					.front_ky			= 0,
					.back_ky			= 0,
					.front_kx			= 0,
					.back_kx			= 0,
					.mode				= 1,
					.front_h			= 0,
					.front_v			= 0,
					.back_h				= 0,
					.back_v				= 0,
				},
				.m1mc = {
					.p_pic				= 0,
					.b_pic				= 0,
				},
				.m1splt = {
					.mode				= D_IM_ME_SPLITMODE_NORMAL,
					.th_h				= 0,
					.th_v				= 0,
				},
				.m1skip					= D_IM_ME_OFF,
				.m1sad = {
					.upper				= 0,
					.lower				= 0,
				},
				.m1adjust = {
					.wait_cycle			= 0,
					.wait_onoff			= D_IM_ME_OFF,
				},
				.m1pause = {
					.pause_line			= 0,
					.pause_onoff		= D_IM_ME_OFF,
				},
				.m1limit = {
					.v_plus				= 0,
					.v_minus			= 0,
					.h_plus				= 0,
					.h_minus			= 0,
				},
			},
			.pme[ 2 ] = {
				.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
				.ref_txb				= D_IM_ME_REFTXB_TOP,
				.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
				.bank_num				= D_IM_ME_BANKNUM_1,
				.m1org_mode[ 0 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 1 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 2 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1org_mode[ 3 ] = {
					.direction			= D_IM_ME_M1ORG_DIR_FWD,
					.parity				= D_IM_ME_M1ORG_PARI_TOP,
					.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
					.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
					.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
					.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
					.pic_type			= D_IM_ME_M1ORG_PICT_P,
				},
				.m1correct = {
					.front_ky			= 0,
					.back_ky			= 0,
					.front_kx			= 0,
					.back_kx			= 0,
					.mode				= 1,
					.front_h			= 0,
					.front_v			= 0,
					.back_h				= 0,
					.back_v				= 0,
				},
				.m1mc = {
					.p_pic				= 0,
					.b_pic				= 0,
				},
				.m1splt = {
					.mode				= D_IM_ME_SPLITMODE_NORMAL,
					.th_h				= 0,
					.th_v				= 0,
				},
				.m1skip					= D_IM_ME_OFF,
				.m1sad = {
					.upper				= 0,
					.lower				= 0,
				},
				.m1adjust = {
					.wait_cycle			= 0,
					.wait_onoff			= D_IM_ME_OFF,
				},
				.m1pause = {
					.pause_line			= 0,
					.pause_onoff		= D_IM_ME_OFF,
				},
				.m1limit = {
					.v_plus				= 0,
					.v_minus			= 0,
					.h_plus				= 0,
					.h_minus			= 0,
				},
			},
			.rmcif = {
				.pme_num				= 0,
				.abt_type				= D_IM_ME_ABT_ROUND,
				.bank_tbl = {
					.fwd_pvec			= 0,
					.top				= 0,
					.fwd_8pel			= 0,
				},
				.axi_if = {
					.r_cache_type		= 0,
					.r_protect_type		= 0,
					.w_cache_type		= 0,
					.w_protect_type		= 0,
				},
			},
			.pCallBack					= (T_IM_ME_CALLBACK)ctCmMeCallback,
		},
#if 0
		[ 1 ] = {	// Min.
			.pCallBack					= (T_IM_ME_CALLBACK)ctCmMeCallback,
		},
#endif
	};

	for(loopcnt = 0; loopcnt < (sizeof(ctrl) / sizeof(ctrl[0])); loopcnt++) {
		ret = Im_ME_Ctrl(&ctrl[ loopcnt ]);
		Ddim_Print(("ct_im_me_set_ctrl(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

static void ctImMeStart(void)
{
	UINT32			loopcnt;
	INT32			ret;
	T_IM_ME_START	start[] = {
		[ 0 ] = {	// Max.
			.pme[ 0 ] = {
				.mbnum_h				= 0,
				.mbnum_v				= 0,
				.cancel_mode			= 0,
				.cancel_threshold_hi	= 0,
				.cancel_threshold_lo	= 0,
				.vec_hsize				= 0,
			},
			.pme[ 1 ] = {
				.mbnum_h				= 0,
				.mbnum_v				= 0,
				.cancel_mode			= 0,
				.cancel_threshold_hi	= 0,
				.cancel_threshold_lo	= 0,
				.vec_hsize				= 0,
			},
			.pme[ 2 ] = {
				.mbnum_h				= 0,
				.mbnum_v				= 0,
				.cancel_mode			= 0,
				.cancel_threshold_hi	= 0,
				.cancel_threshold_lo	= 0,
				.vec_hsize				= 0,
			},
			.rmcif = {
				.pre_shift_x			= 0,
				.pre_shift_y			= 0,
				.pre_r_addr_hi			= 0,
				.pre_r_addr_lo			= 0,
				.cur_r_addr_hi			= 0,
				.cur_r_addr_lo			= 0,
				.vec_w_addr_hi			= 0,
				.vec_w_addr_hi			= 0,
				.pre_gwidth				= 0,
				.pre_width				= 0,
				.pre_height				= 0,
				.cur_gwidth				= 0,
				.cur_margin_width		= 0,
				.cur_margin_height		= 0,
				.prefetch_width			= 0,
				.prefetch_height		= 0,
				.search_width			= 0,
				.search_height			= 0,
			},
		},
#if 0
		[ 1 ] = {	// Min.

		},
#endif
	};

	for(loopcnt = 0; loopcnt < (sizeof(start) / sizeof(start[0])); loopcnt++) {
		ret = Im_ME_Start(&start[ loopcnt ]);
		Ddim_Print(("ct_im_me_set_start(%d)[ret=0x%08x]\n", loopcnt, ret));
	}
}

static void ctImMeErrCtrl(void)
{
	INT32			ret;
	T_IM_ME_CTRL	ctrl = {
		.apbbrg = {
			.pp_enable[ 0 ]			= 0,
			.pp_enable[ 1 ]			= 0,
			.pp_enable[ 2 ]			= 0,
			.int_mode				= 0,
			.interval				= 0,
		},
		.pme[ 0 ] = {
			.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
			.ref_txb				= D_IM_ME_REFTXB_TOP,
			.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
			.bank_num				= D_IM_ME_BANKNUM_1,
			.m1org_mode[ 0 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 1 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 2 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 3 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1correct = {
				.front_ky			= 0,
				.back_ky			= 0,
				.front_kx			= 0,
				.back_kx			= 0,
				.mode				= 1,
				.front_h			= 0,
				.front_v			= 0,
				.back_h				= 0,
				.back_v				= 0,
			},
			.m1mc = {
				.p_pic				= 0,
				.b_pic				= 0,
			},
			.m1splt = {
				.mode				= D_IM_ME_SPLITMODE_NORMAL,
				.th_h				= 0,
				.th_v				= 0,
			},
			.m1skip					= D_IM_ME_OFF,
			.m1sad = {
				.upper				= 0,
				.lower				= 0,
			},
			.m1adjust = {
				.wait_cycle			= 0,
				.wait_onoff			= D_IM_ME_OFF,
			},
			.m1pause = {
				.pause_line			= 0,
				.pause_onoff		= D_IM_ME_OFF,
			},
			.m1limit = {
				.v_plus				= 0,
				.v_minus			= 0,
				.h_plus				= 0,
				.h_minus			= 0,
			},
		},
		.pme[ 1 ] = {
			.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
			.ref_txb				= D_IM_ME_REFTXB_TOP,
			.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
			.bank_num				= D_IM_ME_BANKNUM_1,
			.m1org_mode[ 0 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 1 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 2 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 3 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1correct = {
				.front_ky			= 0,
				.back_ky			= 0,
				.front_kx			= 0,
				.back_kx			= 0,
				.mode				= 1,
				.front_h			= 0,
				.front_v			= 0,
				.back_h				= 0,
				.back_v				= 0,
			},
			.m1mc = {
				.p_pic				= 0,
				.b_pic				= 0,
			},
			.m1splt = {
				.mode				= D_IM_ME_SPLITMODE_NORMAL,
				.th_h				= 0,
				.th_v				= 0,
			},
			.m1skip					= D_IM_ME_OFF,
			.m1sad = {
				.upper				= 0,
				.lower				= 0,
			},
			.m1adjust = {
				.wait_cycle			= 0,
				.wait_onoff			= D_IM_ME_OFF,
			},
			.m1pause = {
				.pause_line			= 0,
				.pause_onoff		= D_IM_ME_OFF,
			},
			.m1limit = {
				.v_plus				= 0,
				.v_minus			= 0,
				.h_plus				= 0,
				.h_minus			= 0,
			},
		},
		.pme[ 2 ] = {
			.input_mode				= D_IM_ME_INPUTMODE_INTERLACE,
			.ref_txb				= D_IM_ME_REFTXB_TOP,
			.out_limit				= D_IM_ME_OUTLIMIT_NOLIMIT0,
			.bank_num				= D_IM_ME_BANKNUM_1,
			.m1org_mode[ 0 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 1 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 2 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1org_mode[ 3 ] = {
				.direction			= D_IM_ME_M1ORG_DIR_FWD,
				.parity				= D_IM_ME_M1ORG_PARI_TOP,
				.read_mode			= D_IM_ME_M1ORG_READ_FIXED,
				.sad0_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.sad1_mode			= D_IM_ME_M1ORG_SAD_SAVE,
				.vec_mode			= D_IM_ME_M1ORG_VECM_WRITE0,
				.vec_select			= D_IM_ME_M1ORG_VECS_SAVE,
				.pic_type			= D_IM_ME_M1ORG_PICT_P,
			},
			.m1correct = {
				.front_ky			= 0,
				.back_ky			= 0,
				.front_kx			= 0,
				.back_kx			= 0,
				.mode				= 1,
				.front_h			= 0,
				.front_v			= 0,
				.back_h				= 0,
				.back_v				= 0,
			},
			.m1mc = {
				.p_pic				= 0,
				.b_pic				= 0,
			},
			.m1splt = {
				.mode				= D_IM_ME_SPLITMODE_NORMAL,
				.th_h				= 0,
				.th_v				= 0,
			},
			.m1skip					= D_IM_ME_OFF,
			.m1sad = {
				.upper				= 0,
				.lower				= 0,
			},
			.m1adjust = {
				.wait_cycle			= 0,
				.wait_onoff			= D_IM_ME_OFF,
			},
			.m1pause = {
				.pause_line			= 0,
				.pause_onoff		= D_IM_ME_OFF,
			},
			.m1limit = {
				.v_plus				= 0,
				.v_minus			= 0,
				.h_plus				= 0,
				.h_minus			= 0,
			},
		},
		.rmcif = {
			.pme_num				= 0,
			.abt_type				= D_IM_ME_ABT_ROUND,
			.bank_tbl = {
				.fwd_pvec			= 0,
				.top				= 0,
				.fwd_8pel			= 0,
			},
			.axi_if = {
				.r_cache_type		= 0,
				.r_protect_type		= 0,
				.w_cache_type		= 0,
				.w_protect_type		= 0,
			},
		},
		.pCallBack					= (T_IM_ME_CALLBACK)ctCmMeCallback,
	};

	ret = Im_ME_Ctrl(NULL);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.rmcif.abt_type = D_IM_ME_ABT_ROUND + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.rmcif.pme_num = E_IM_ME_PPNUM_MAX;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].core_mode.line_interval = D_IM_ME_LINEINTV_3QMB + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1limit.h_minus = D_IM_ME_VEC_LIMITH_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1limit.h_plus = D_IM_ME_VEC_LIMITH_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1limit.v_minus = D_IM_ME_VEC_LIMITV_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1limit.v_plus = D_IM_ME_VEC_LIMITV_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1pause.pause_onoff = D_IM_ME_ON + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1adjust.wait_onoff = D_IM_ME_ON + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1skip = D_IM_ME_ON + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1splt.mode = D_IM_ME_SPLITMODE_VERTICAL + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1correct.back_kx = D_IM_ME_M1CRCT_KX_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1correct.front_kx = D_IM_ME_M1CRCT_KX_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1correct.back_ky = D_IM_ME_M1CRCT_KY_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1correct.front_ky = D_IM_ME_M1CRCT_KY_MAX + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].pic_type = D_IM_ME_M1ORG_PICT_I + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].vec_select = 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].vec_mode = D_IM_ME_M1ORG_VECM_WRITE1 + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].sad1_mode = D_IM_ME_M1ORG_SAD_MIN1 + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].sad0_mode = D_IM_ME_M1ORG_SAD_MIN1 + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].read_mode = D_IM_ME_M1ORG_READ_SDRAM + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].parity = D_IM_ME_M1ORG_PARI_BOTTOM + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].m1org_mode[ 0 ].direction = D_IM_ME_M1ORG_DIR_BWD + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].bank_num = D_IM_ME_BANKNUM_4 + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].out_limit = D_IM_ME_OUTLIMIT_TOP + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].ref_txb = D_IM_ME_REFTXB_BOTTOM + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.pme[ 0 ].input_mode = D_IM_ME_INPUTMODE_PROGRESSIVE + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.apbbrg.pp_enable[ 0 ] = D_IM_ME_ENABLE + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));

	ctrl.apbbrg.int_mode = D_IM_ME_INTMODE_LOGICAL_OR + 1;
	ret = Im_ME_Ctrl(&ctrl);
	Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));
}

static void ctImMeErrStart(void)
{
	INT32			ret;

	ret = Im_ME_Start(NULL);
	Ddim_Print(("Im_ME_Start[ret=0x%08x]\n", ret));
}

static void ctImMeTest(T_IM_ME_PARAM* meParam)
{
	INT32	ret;
	UINT32	waitFactor;

	Ddim_Print(("porocess 1\n"));
	ret = Im_ME_Open(0);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Open[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 2\n"));
	ret = Im_ME_Init();
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Init[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 3\n"));
	ret = Im_ME_Ctrl(&meParam->ctrl);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Ctrl[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 4\n"));
	ret = Im_ME_Start(&meParam->start);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Start[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 5\n"));
	ret = Im_ME_Wait_End(&waitFactor, 1000);
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Wait_End[ret=0x%08x]\n", ret));
	}

	Ddim_Print(("porocess 6\n"));
	ret = Im_ME_Close();
	if (ret != D_DDIM_OK) {
		Ddim_Print(("Im_ME_Close[ret=0x%08x]\n", ret));
	}
}

static void ctImMeTest2(void)
{
	T_IM_ME_PARAM	meParam = {
		.ctrl = {
			.pCallBack	= (T_IM_ME_CALLBACK)ctCmMeCallback,
		},
		.start = {
		},
	};

	ctImMeTest(&meParam);
}

void ct_im_me_main(INT32 argc, char** argv)
{
	INT32	ret;
	UINT32	waitFactor;

	if (strcmp(argv[1], "init") == 0) {
		ret = Im_ME_Init();
		Ddim_Print(("Im_ME_Init() ret = %d\n", ret));
	}
	else if (strcmp(argv[1], "open") == 0) {
		ret = Im_ME_Open(D_DDIM_USER_SEM_WAIT_FEVR);
		Ddim_Print(("Im_ME_Open() ret = %d\n", ret));
	}
	else if (strcmp(argv[1], "close") == 0) {
		ret = Im_ME_Close();
		Ddim_Print(("Im_ME_Close() ret = %d\n", ret));
	}
	else if (strcmp(argv[1], "ctrl") == 0) {
		ctImMeCtrl();
	}
	else if (strcmp(argv[1], "start") == 0) {
		ctImMeStart();
	}
	else if (strcmp(argv[1], "wait") == 0) {
#ifdef CtImMe_PC_DEBUG
		(void)DDIM_User_Set_Flg(FID_IM_ME, 1);
#endif
		ret = Im_ME_Wait_End(&waitFactor, 0);
		Ddim_Print(("Im_ME_Wait_End() End ret = %d\n", ret));
	}
	else if (strcmp(argv[1], "err") == 0) {
		if (strcmp(argv[2], "init") == 0) {
			ret = Im_ME_Init();
			Ddim_Print(("Im_ME_Init() ret = %d\n", ret));
		}
		else if (strcmp(argv[2], "open") == 0) {
			ret = Im_ME_Open(-2);
			Ddim_Print(("Im_ME_Open() ret = %d\n", ret));
		}
		else if (strcmp(argv[2], "close") == 0) {
			ret = Im_ME_Close();
			Ddim_Print(("Im_ME_Close() ret = %d\n", ret));
		}
		else if (strcmp(argv[2], "ctrl") == 0) {
			ctImMeErrCtrl();
		}
		else if (strcmp(argv[2], "start") == 0) {
			ctImMeErrStart();
		}
		else if (strcmp(argv[2], "wait") == 0) {
#ifdef CtImMe_PC_DEBUG
			(void)DDIM_User_Clr_Flg(FID_IM_ME, ~1);
#endif
			ret = Im_ME_Wait_End(&waitFactor, 100);
			Ddim_Print(("Im_ME_Wait_End() ret = %d\n", ret));

#ifdef CtImMe_PC_DEBUG
			(void)DDIM_User_Set_Flg(FID_IM_ME, 1);
#endif
			ret = Im_ME_Wait_End(NULL, 0);
			Ddim_Print(("Im_ME_Wait_End() ret = %d\n", ret));

			ret = Im_ME_Wait_End(&waitFactor, -2);
			Ddim_Print(("Im_ME_Wait_End() ret = %d\n", ret));
		}
		else {
			Ddim_Print(("please check 2nd parameter!\n"));
			return;
		}
	}
	else if (strcmp(argv[1], "2") == 0) {
#ifdef CtImMe_PC_DEBUG
		(void)DDIM_User_Set_Flg(FID_IM_ME, 1);
#endif
		if (strcmp(argv[2], "1") == 0) {
			Ddim_Print(("me test2_1 Start []\n"));
			ctImMeTest2();
			Ddim_Print(("me test2_1 End\n"));
		}
		else {
			Ddim_Print(("please check 2nd parameter!\n"));
			return;
		}
	}
	else {
		Ddim_Print(("please check 1st parameter!\n"));
	}

	return ;
}

CtImMe* ct_im_me_new(void)
{
	CtImMe* self = g_object_new(CT_TYPE_IM_ME,NULL);
	return self;
}
