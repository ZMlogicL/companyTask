/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmLtm类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <stdlib.h>
#include <string.h>
#include "ct_im_b2r.h"
#include "ct_im_ltm.h"
#include "im_b2r.h"
#include "im_ltm.h"
#include "im_r2y.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsimg.h"
#include "jdsltm.h"

#include "ctimltmltm1.h"
#include "ctimltmltm2.h"
#include "ctimltmltm3.h"
#include "ctimltmltm4.h"
#include "ctimltmltm5.h"
#include "ctimltmltm.h"

G_DEFINE_TYPE(CtImLtmLtm, ct_im_ltm_ltm, G_TYPE_OBJECT);

#define CT_IM_LTM_LTM_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_LTM, CtImLtmLtmPrivate))

#ifdef CO_MSG_PRINT_ON
#define CtImLtmLtm_D_IM_LTM_RESULT(statement)		result = statement
#else
#define CtImLtmLtm_D_IM_LTM_RESULT
#endif

struct _CtImLtmLtmPrivate
{
	CtImLtmLtm1 *ltm1;
	CtImLtmLtm2 *ltm2;
	CtImLtmLtm3 *ltm3;
	CtImLtmLtm4 *ltm4;
	CtImLtmLtm5 *ltm5;
};
/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static gint32 	ctImLtmLtmRun1(CtImLtmLtm *self, const guint32 ctNo2nd);
static gint32 	ctImLtmLtmRun2(CtImLtmLtm *self, const guint32 ctNo2nd);
static gint32 	ctImLtmLtmRun3(CtImLtmLtm *self, const guint32 ctNo2nd);

static void ct_im_ltm_ltm_class_init(CtImLtmLtmClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmLtmPrivate));
}

static void ct_im_ltm_ltm_init(CtImLtmLtm *self)
{
	CtImLtmLtmPrivate *priv = CT_IM_LTM_LTM_GET_PRIVATE(self);
	priv->ltm1=ct_im_ltm_ltm1_new();
	priv->ltm2=ct_im_ltm_ltm2_new();
	priv->ltm3=ct_im_ltm_ltm3_new();
	priv->ltm4=ct_im_ltm_ltm4_new();
	priv->ltm5=ct_im_ltm_ltm5_new();
}
/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
	CtImLtmLtm *self = (CtImLtmLtm*)object;
	CtImLtmLtmPrivate *priv = CT_IM_LTM_LTM_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm_parent_class)->dispose(object);

	if(priv->ltm1){
	g_object_unref(priv->ltm1);
	priv->ltm1=NULL;
	}

	if(priv->ltm2){
		g_object_unref(priv->ltm2);
		priv->ltm2=NULL;
		}

	if(priv->ltm3){
		g_object_unref(priv->ltm3);
		priv->ltm3=NULL;
		}

	if(priv->ltm4){
		g_object_unref(priv->ltm4);
		priv->ltm4=NULL;
		}

	if(priv->ltm5){
		g_object_unref(priv->ltm5);
		priv->ltm5=NULL;
		}
}

static void finalize_od(GObject *object)
{
//	CtImLtmLtm *self = (CtImLtmLtm*)object;
//	CtImLtmLtmPrivate *priv = CT_IM_LTM_LTM_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_ltm_parent_class)->finalize(object);
}

static gint32 ctImLtmLtmRun1(CtImLtmLtm *self, const guint32 ctNo2nd)
{
	CtImLtmLtmPrivate *priv=CT_IM_LTM_LTM_GET_PRIVATE(self);

	switch(ctNo2nd) {
		// Test-1-1-1
		case 1:
			return ct_im_ltm_ltm3_1_1(priv->ltm3);

		// Test-1-1-2
		case 2:
			return ct_im_ltm_ltm3_1_2(priv->ltm3);

		// Test-1-1-3
		case 3:
			return ct_im_ltm_ltm3_1_3(priv->ltm3);

		// Test-1-1-4
		case 4:
			return ct_im_ltm_ltm3_1_4(priv->ltm3);

		// Test-1-1-5
		case 5:
			return ct_im_ltm_ltm3_1_5(priv->ltm3);

		// Test-1-1-6
		case 6:
			return ct_im_ltm_ltm3_1_6(priv->ltm3);

		// Test-1-1-7
		case 7:
			return ct_im_ltm_ltm1_1_7(priv->ltm1);

		// Test-1-1-8
		case 8:
			return ct_im_ltm_ltm1_1_8(priv->ltm1);

		// Test-1-1-9
		case 9:
			return ct_im_ltm_ltm1_1_9(priv->ltm1);

		// Test-1-1-10
		case 10:
			return ct_im_ltm_ltm1_1_10(priv->ltm1);

		// Test-1-1-11
		case 11:
			return ct_im_ltm_ltm3_1_11(priv->ltm3);

		// Test-1-1-12
		case 12:
			return ct_im_ltm_ltm1_1_12(priv->ltm1);

		// Test-1-1-13
		case 13:
			return ct_im_ltm_ltm1_1_13(priv->ltm1);

		// Test-1-1-14
		case 14:
			return ct_im_ltm_ltm3_1_14(priv->ltm3);

		// Test-1-1-15
		case 15:
			return ct_im_ltm_ltm3_1_15(priv->ltm3);

		// Test-1-1-16
		case 16:
			return ct_im_ltm_ltm3_1_16(priv->ltm3);

		// Test-1-1-17
		case 17:
			return ct_im_ltm_ltm3_1_17(priv->ltm3);

		// Test-1-1-18
		case 18:
			return ct_im_ltm_ltm3_1_18(priv->ltm3);

		// Test-1-1-19
		case 19:
			return ct_im_ltm_ltm3_1_19(priv->ltm3);

		// Test-1-1-20
		case 20:
			return ct_im_ltm_ltm3_1_20(priv->ltm3);

		// Test-1-1-21
		case 21:
			return ct_im_ltm_ltm3_1_21(priv->ltm3);

		// Test-1-1-22
		case 22:
			return ct_im_ltm_ltm3_1_22(priv->ltm3);

		// Test-1-1-23
		case 23:
			return ct_im_ltm_ltm5_1_23(priv->ltm5);

		// Test-1-1-24
		case 24:
			return ct_im_ltm_ltm5_1_24(priv->ltm5);

		// Test-1-1-25
		case 25:
			return ct_im_ltm_ltm5_1_25(priv->ltm5);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

static gint32 ctImLtmLtmRun2(CtImLtmLtm *self, const guint32 ctNo2nd)
{
	CtImLtmLtmPrivate *priv=CT_IM_LTM_LTM_GET_PRIVATE(self);

	switch(ctNo2nd) {
		// Test-1-2-1
		case 1:
			return ct_im_ltm_ltm5_2_1(priv->ltm5);

		// Test-1-2-2
		case 2:
			return ct_im_ltm_ltm5_2_2(priv->ltm5);

		// Test-1-2-3
		case 3:
			return ct_im_ltm_ltm5_2_3(priv->ltm5);

		// Test-1-2-4
		case 4:
			return ct_im_ltm_ltm5_2_4(priv->ltm5);

		// Test-1-2-5
		case 5:
			return ct_im_ltm_ltm5_2_5(priv->ltm5);

		// Test-1-2-6
		case 6:
			return ct_im_ltm_ltm5_2_6(priv->ltm5);

		// Test-1-2-7
		case 7:
			return ct_im_ltm_ltm5_2_7(priv->ltm5);

		// Test-1-2-8
		case 8:
			return ct_im_ltm_ltm5_2_8(priv->ltm5);

		// Test-1-2-9
		case 9:
			return ct_im_ltm_ltm5_2_9(priv->ltm5);

		// Test-1-2-10
		case 10:
			return ct_im_ltm_ltm5_2_10(priv->ltm5);

		// Test-1-2-11
		case 11:
			return ct_im_ltm_ltm5_2_11(priv->ltm5);

		// Test-1-2-12
		case 12:
			return ct_im_ltm_ltm5_2_12(priv->ltm5);

		// Test-1-2-13
		case 13:
			return ct_im_ltm_ltm5_2_13(priv->ltm5);

		// Test-1-2-14
		case 14:
			return ct_im_ltm_ltm5_2_14(priv->ltm5);

		// Test-1-2-15
		case 15:
			return ct_im_ltm_ltm5_2_15(priv->ltm5);

		// Test-1-2-16
		case 16:
			return ct_im_ltm_ltm5_2_16(priv->ltm5);

		// Test-1-2-17
		case 17:
			return ct_im_ltm_ltm5_2_17(priv->ltm5);

		// Test-1-2-18
		case 18:
			return ct_im_ltm_ltm5_2_18(priv->ltm5);

		// Test-1-2-19
		case 19:
			return ct_im_ltm_ltm5_2_19(priv->ltm5);

		// Test-1-2-20
		case 20:
			return ct_im_ltm_ltm5_2_20(priv->ltm5);

		// Test-1-2-21
		case 21:
			return ct_im_ltm_ltm5_2_21(priv->ltm5);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

static gint32 ctImLtmLtmRun3(CtImLtmLtm *self, const guint32 ctNo2nd)
{
	CtImLtmLtmPrivate *priv=CT_IM_LTM_LTM_GET_PRIVATE(self);

	Im_LTM_LTM_Ctrl_Blend(ct_im_ltm_ltm1_get_self1(priv->ltm1), &priv->ltm2->gctImLtmLtmCtrlBlend);

	switch(ctNo2nd) {
		// Test-1-3-1
		case 1:
			return ct_im_ltm_ltm4_3_1(priv->ltm4);

		// Test-1-3-2
		case 2:
			return ct_im_ltm_ltm4_3_2(priv->ltm4);

		// Test-1-3-3
		case 3:
			return ct_im_ltm_ltm4_3_3(priv->ltm4);

		// Test-1-3-4
		case 4:
			return ct_im_ltm_ltm4_3_4(priv->ltm4);

		// Test-1-3-5
		case 5:
			return ct_im_ltm_ltm4_3_5(priv->ltm4);

		// Test-1-3-6
		case 6:
			return ct_im_ltm_ltm4_3_6(priv->ltm4);

		// Test-1-3-7
		case 7:
			return ct_im_ltm_ltm1_3_7(priv->ltm1);

		// Test-1-3-8
		case 8:
			return ct_im_ltm_ltm1_3_8(priv->ltm1);

		// Test-1-3-9
		case 9:
			return ct_im_ltm_ltm1_3_9(priv->ltm1);

		// Test-1-3-10
		case 10:
			return ct_im_ltm_ltm1_3_10(priv->ltm1);

		// Test-1-3-11
		case 11:
			return ct_im_ltm_ltm1_3_11(priv->ltm1);

		// Test-1-3-12
		case 12:
			return ct_im_ltm_ltm2_3_12(priv->ltm2);

		// Test-1-3-13
		case 13:
			return ct_im_ltm_ltm2_3_13(priv->ltm2);

		// Test-1-3-14
		case 14:
			return ct_im_ltm_ltm2_3_14(priv->ltm2);

		// Test-1-3-15
		case 15:
			return ct_im_ltm_ltm2_3_15(priv->ltm2);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}
/*
 *PUBLIC
 * */
void ct_im_ltm_ltm_run(CtImLtmLtm *self,const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd)
{
	CtImLtmLtmPrivate *priv=CT_IM_LTM_LTM_GET_PRIVATE(self);
#ifdef CO_MSG_PRINT_ON
	gint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static gboolean S_IS_INIT = 0;
	guchar loopCnt;

	ct_im_ltm_ltm3_set_ltm4(priv->ltm3,priv->ltm4);
	ct_im_ltm_ltm2_set_ltm4(priv->ltm2,priv->ltm4);
	ct_im_ltm_ltm1_set_ltm4(priv->ltm1, priv->ltm4);
	ct_im_ltm_ltm5_set_ltm4(priv->ltm5,priv->ltm4);

	Ddim_Print(("ct_im_ltm_ltm_run(%u, %u, %u) Begin\n", ctIdx1st, ctIdx2nd, ctIdx3rd));

	if(S_IS_INIT == 0) {
#ifdef CO_DEBUG_ON_PC
		memset((kpointer)&IO_LTM_P1.LTM, '\0', sizeof(IO_LTM_P1.LTM));
		memset((kpointer)&IO_LTM_P2.LTM, '\0', sizeof(IO_LTM_P2.LTM));
		IO_LTM_P1.LTM.LTRG.word = 2;
		IO_LTM_P2.LTM.LTRG.word = 2;
#endif // CO_DEBUG_ON_PC
		if(!((ctIdx1st == 1) && (ctIdx2nd == 1))) {
			Ddim_Print(("Im_LTM_LTM_Init() Begin\n"));
			Im_LTM_LTM_Init(D_IM_LTM_PIPE12);
			Ddim_Print(("Im_LTM_LTM_Init() End\n"));
			S_IS_INIT = 1;
		}
	}

	if(ctIdx1st != 3){
		for(loopCnt = 0; loopCnt <= 1; loopCnt++){
			priv->ltm4->pipeNo = loopCnt;
			switch(ctIdx1st) {
				case 1:
					CtImLtmLtm_D_IM_LTM_RESULT(ctImLtmLtmRun1(self,ctIdx2nd));
					break;

				case 2:
					CtImLtmLtm_D_IM_LTM_RESULT(ctImLtmLtmRun2(self, ctIdx2nd));
					break;

				default:
					Ddim_Print(("Error: Unknown command.\n"));
					break;
			}

#ifdef CO_MSG_PRINT_ON
			Ddim_Print(("result = 0x%x\n", result));
#endif
			Ddim_Print(("ct_im_ltm_ltm_run(%u, %u, %u) End\n", ctIdx1st, ctIdx2nd, loopCnt));
		}
	}else{
		priv->ltm4->pipeNo = ctIdx3rd;
		CtImLtmLtm_D_IM_LTM_RESULT(ctImLtmLtmRun3(self,ctIdx2nd));
#ifdef CO_MSG_PRINT_ON
		Ddim_Print(("result = 0x%x\n", result));
#endif
		Ddim_Print(("ct_im_ltm_ltm_run(%u, %u, %u) End\n", ctIdx1st, ctIdx2nd, ctIdx3rd));
	}

	return;
}

// for Debug console interface
void ct_im_ltm_ltm_main(CtImLtmLtm *self,gint32 argc, gchar** argv)
{
	if(argc < 3) {
		Ddim_Print(("ct_im_ltm_ltm_main: parameter error.\n"));
		return;
	}

	ct_im_ltm_ltm_run(self,(guint32)atoi((const char*)argv[1]),
					   (guint32)atoi((const char*)argv[2]),
					   (guint32)atoi((const char*)argv[3]));
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmLtm类的一个实例
 */
CtImLtmLtm* ct_im_ltm_ltm_new()
{
	CtImLtmLtm *self = g_object_new(CT_TYPE_IM_LTM_LTM,NULL);
	return self;
}
