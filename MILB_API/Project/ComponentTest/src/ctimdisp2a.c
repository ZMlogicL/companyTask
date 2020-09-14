/*
 *ctimdisp2a.c
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date:                2020-09-11
 *@author:            杨永济
 *@brief:                m10v-isp
 *@rely:                 klib
 *@function:
 *设计的主要功能:
 *@version: 
 */

/*
 * 以下开始include语句
 * */

#include <stdlib.h>
#include <string.h>
#include "im_disp.h"
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "jdsdisp3a.h"

#include "ctimdisp.h"//already define CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
#include "ct_im_disptbl_define.h"
#include "ct_im_disp_define.h"//CO_IO_DISP_DEFINE

#include "ctimdisp4.h"//variable
#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"

#include "imdisp2group.h"
#include "ctimdisp2a.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2a, ct_im_disp2a, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2A_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2A, CtImDisp2aPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2aPrivate
{
	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT gLcdDispTblOutCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_END];
};

/*
 * 文件级全局变量定义
 * */

/*
 * DECLS
 * */
static void dispose_od(GObject *object);
static void finalize_od(GObject *object);
#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2aDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/
static void getCtrlOutLayer(BYTE getDataType, BYTE block);
static void initHdmiDataTgkmd(CtImDisp2a *self);

/*
 * IMPL
 * */
static void ct_im_disp2a_class_init(CtImDisp2aClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2aPrivate));
}

static void ct_im_disp2a_init(CtImDisp2a *self)
{
	CtImDisp2aPrivate *priv = CT_IM_DISP2A_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2aDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->privCtImDisp2a = priv;
	initHdmiDataTgkmd(self);
}

static void dispose_od(GObject *object)
{
//	CtImDisp2a *self = CT_IM_DISP2A(object);
//	CtImDisp2aPrivate *priv = CT_IM_DISP2A_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2a_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2a *self = CT_IM_DISP2A(object);
//	CtImDisp2aPrivate *priv = CT_IM_DISP2A_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2a_parent_class)->finalize(object);
}


#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2aDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	CtImDisp2a *self = (CtImDisp2a *)parent;
	CtImDisp2aPrivate *priv = self->privCtImDisp2a;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((gchar *) argv[1], "CtrlOUTs") == 0)
	{
		//Im_DISP_Ctrl_Output

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "CtrlOUTs"
		// argv[2] Parameter assign(0:NO para/1:only first para/2:only second para/3:both para)
		// argv[3] block
		// argv[4] error Setting

		if (argc == 5)
		{
			ImDisp2Group *disp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
			// CtImDisp4 *ctImDisp4 = (CtImDisp4 *)im_disp2_group_get_disp4(disp2Group);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			E_IM_DISP_SEL block = strtoul(argv[3], NULL, 0);
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_DCORE, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT outCtrlTrgLimit;
			T_IM_DISP_CTRL_OUTPUT outCtrl;
			T_IM_DISP_CTRL_OUTPUT *pOutputCtl = im_disp2_group_get_output_ctl(disp2Group);
			switch (argv[3][0])
			{
			case '0':
				// HDMI
				memcpy(&outCtrlTrgLimit,
						(void *) &priv->gLcdDispTblOutCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_HDMI],
						sizeof(T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT));
				memcpy(&outCtrl, (void *) &pOutputCtl[CtImDisp4_LCD_DISP_SEL_HDMI],
						sizeof(T_IM_DISP_CTRL_OUTPUT));
				break;
			default:
				// LCD
				memcpy(&outCtrlTrgLimit,
						(void *) &priv->gLcdDispTblOutCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_LCD],
						sizeof(T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT));
				memcpy(&outCtrl, (void *) &pOutputCtl[CtImDisp4_LCD_DISP_SEL_LCD],
						sizeof(T_IM_DISP_CTRL_OUTPUT));
				break;
			}

			// "CP:im_disp_param_check_ctrl_output() 5"
			if (strcmp((gchar *) argv[4], "1") == 0)
			{
				// domd.mode error
				outCtrlTrgLimit.domd.bit.MODE = 0xFF;
			}
//				else if(strcmp((gchar *)argv[4], "2")==0) {
//					// domd.mode error
//					outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_YCC422_20BIT;
//				}
//				else if(strcmp((gchar *)argv[4], "3")==0) {
//					// domd.mode error
//					outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_YCC422_24BIT;
//				}
			// "CP:im_disp_param_check_ctrl_output() 12"
			else if (strcmp((gchar *) argv[4], "4") == 0)
			{
				// hblk error
				outCtrlTrgLimit.hblk = 7;
			}
			// "CP:im_disp_param_check_ctrl_output() 13"
			else if (strcmp((gchar *) argv[4], "5") == 0)
			{
				// vdly error
				outCtrlTrgLimit.vdly = 10;
				outCtrlTrgLimit.hcyc = 20;
			}
			// "CP:im_disp_param_check_ctrl_output() 14"
			else if (strcmp((gchar *) argv[4], "6") == 0)
			{
				// hdly error
				outCtrlTrgLimit.hdly = 16;
				outCtrlTrgLimit.hblk = 16;
			}
			// "CP:im_disp_param_check_ctrl_output() 15
			else if (strcmp((gchar *) argv[4], "7") == 0)
			{
				// tsl & ovsize error
				outCtrlTrgLimit.tsl = D_IM_DISP_TSL_INTERLACE;
				outCtrlTrgLimit.ovsize = 0x00001001;
			}
			// "CP:im_disp_param_check_ctrl_output() 16
			else if (strcmp((gchar *) argv[4], "8") == 0)
			{
				// ohsize error
				outCtrlTrgLimit.ohsize = 0x000000F8;
			}
			// "CP:im_disp_param_check_ctrl_output() 17
			else if (strcmp((gchar *) argv[4], "9") == 0)
			{
				// ovsize error
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_YCC420_24BIT;
				outCtrlTrgLimit.tsl = D_IM_DISP_TSL_PROGRESSIVE;
				outCtrlTrgLimit.ovsize = 0x00000FFF;
			}
			// "CP:im_disp_param_check_ctrl_output() 18
			else if (strcmp((gchar *) argv[4], "10") == 0)
			{
				// ohsize error
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_YCC420_30BIT;
				outCtrlTrgLimit.ohsize = 0x00001001;
			}

			// "CP:im_disp_param_check_ctrl_output() 19
			else if (strcmp((gchar *) argv[4], "11") == 0)
			{
				// clbhsize error
				outCtrl.clbhsize = 10;
				outCtrlTrgLimit.ohsize = 0x176;
			}
			// "CP:im_disp_param_check_ctrl_output() 20
			else if (strcmp((gchar *) argv[4], "12") == 0)
			{
				// "CP:im_disp_param_check_blend() 1
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 1;
				outCtrl.bldctl.bit.BLD2 = 1;
				outCtrl.bldctl.bit.BLD3 = 0;
				outCtrl.bldctl.bit.BLD4 = 0;
			}
			else if (strcmp((gchar *) argv[4], "13") == 0)
			{
				// "CP:im_disp_param_check_blend() 2
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 1;
				outCtrl.bldctl.bit.BLD2 = 0;
				outCtrl.bldctl.bit.BLD3 = 1;
				outCtrl.bldctl.bit.BLD4 = 0;
			}
			else if (strcmp((gchar *) argv[4], "14") == 0)
			{
				// "CP:im_disp_param_check_blend() 3
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 1;
				outCtrl.bldctl.bit.BLD2 = 0;
				outCtrl.bldctl.bit.BLD3 = 0;
				outCtrl.bldctl.bit.BLD4 = 1;
			}
			else if (strcmp((gchar *) argv[4], "15") == 0)
			{
				// "CP:im_disp_param_check_blend() 4
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 0;
				outCtrl.bldctl.bit.BLD2 = 1;
				outCtrl.bldctl.bit.BLD3 = 1;
				outCtrl.bldctl.bit.BLD4 = 2;
			}
			else if (strcmp((gchar *) argv[4], "16") == 0)
			{
				// "CP:im_disp_param_check_blend() 5
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 0;
				outCtrl.bldctl.bit.BLD2 = 1;
				outCtrl.bldctl.bit.BLD3 = 3;
				outCtrl.bldctl.bit.BLD4 = 1;
			}
			else if (strcmp((gchar *) argv[4], "17") == 0)
			{
				// "CP:im_disp_param_check_blend() 6
				// im_disp_param_check_blend() error
				outCtrl.bldctl.bit.BLD1 = 0;
				outCtrl.bldctl.bit.BLD2 = 3;
				outCtrl.bldctl.bit.BLD3 = 1;
				outCtrl.bldctl.bit.BLD4 = 1;
			}

			// "CP:im_disp_param_check_ctrl_output() 21
			else if (strcmp((gchar *) argv[4], "18") == 0)
			{
				// doctl1.bit.ODO1 error
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
				outCtrl.doctl1.bit.ODO1 = D_IM_DISP_ENABLE_ON;
			}
			// "CP:im_disp_param_check_ctrl_output() 22
			else if (strcmp((gchar *) argv[4], "19") == 0)
			{
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
				outCtrl.doctl1.bit.ODO2 = D_IM_DISP_ENABLE_ON;
			}
			// "CP:im_disp_param_check_ctrl_output() 23
			else if (strcmp((gchar *) argv[4], "20") == 0)
			{
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
				outCtrl.doctl1.bit.ODE1 = D_IM_DISP_ENABLE_ON;
			}
			// "CP:im_disp_param_check_ctrl_output() 24
			else if (strcmp((gchar *) argv[4], "21") == 0)
			{
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
				outCtrl.doctl1.bit.ODE2 = D_IM_DISP_ENABLE_ON;
			}

			// "CP:im_disp_param_check_ctrl_output() 25
			else if (strcmp((gchar *) argv[4], "22") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
			}
			else if (strcmp((gchar *) argv[4], "23") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_30BIT;
			}
			else if (strcmp((gchar *) argv[4], "24") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_36BIT;
			}
			else if (strcmp((gchar *) argv[4], "25") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "26") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
			}
			else if (strcmp((gchar *) argv[4], "27") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_3;
			}
			else if (strcmp((gchar *) argv[4], "28") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "29") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_2;
			}
			else if (strcmp((gchar *) argv[4], "30") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB565_8BIT;
			}
			else if (strcmp((gchar *) argv[4], "31") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB565_16BIT;
			}
			else if (strcmp((gchar *) argv[4], "32") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB666_18BIT;
			}
			else if (strcmp((gchar *) argv[4], "33") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_8BIT;
			}
			else if (strcmp((gchar *) argv[4], "34") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_16BIT;
			}
			else if (strcmp((gchar *) argv[4], "35") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "36") == 0)
			{
				// clvs error
				outCtrl.doctl2.bit.CLVS = D_IM_DISP_CLVS_SIGNED;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_2;
			}

			// "CP:im_disp_param_check_ctrl_output() 26
			else if (strcmp((gchar *) argv[4], "37") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_RIGHT;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_24BIT;
			}
			else if (strcmp((gchar *) argv[4], "38") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_AVERAGE;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_30BIT;
			}
			else if (strcmp((gchar *) argv[4], "39") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_36BIT;
			}
			else if (strcmp((gchar *) argv[4], "40") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "41") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_AVERAGE;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_2;
			}
			else if (strcmp((gchar *) argv[4], "42") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_RIGHT;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_8BIT_3;
			}
			else if (strcmp((gchar *) argv[4], "43") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_RIGHT;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "44") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_AVERAGE;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB888_16BIT_2;
			}
			else if (strcmp((gchar *) argv[4], "45") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB565_8BIT;
			}
			else if (strcmp((gchar *) argv[4], "46") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB565_16BIT;
			}
			else if (strcmp((gchar *) argv[4], "47") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_RGB666_18BIT;
			}
			else if (strcmp((gchar *) argv[4], "48") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_YCC444_24BIT;
			}
			else if (strcmp((gchar *) argv[4], "49") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_30BIT;
			}
			else if (strcmp((gchar *) argv[4], "50") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_DEEP_YCC444_36BIT;
			}
			else if (strcmp((gchar *) argv[4], "51") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_DUAL_YCC444_12BIT;
			}
			else if (strcmp((gchar *) argv[4], "52") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_8BIT;
			}
			else if (strcmp((gchar *) argv[4], "53") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_16BIT;
			}
			else if (strcmp((gchar *) argv[4], "54") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_1;
			}
			else if (strcmp((gchar *) argv[4], "55") == 0)
			{
				// ctoh error
				outCtrl.doctl2.bit.CTOH = D_IM_DISP_CTOH_FILTER;
				outCtrlTrgLimit.domd.bit.MODE = D_IM_DISP_MODE_GENERAL_10BIT_2;
			}

			// "CP:im_disp_param_check_ctrl_output() 27
			else if (strcmp((gchar *) argv[4], "56") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 1
				// dsh error
				outCtrl.face.param[0].ffdsta.bit.DSH = 0x0001;
			}
			else if (strcmp((gchar *) argv[4], "57") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 2
				// dsv error
				outCtrl.face.param[0].ffdsta.bit.DSV = 0x0001;
			}
			else if (strcmp((gchar *) argv[4], "58") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 3
				// ffhsz error
				outCtrl.face.param[0].ffsize.bit.FFHSZ = 0x0FF1;
			}
			else if (strcmp((gchar *) argv[4], "59") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 3
				// ffhsz error
				outCtrl.face.param[0].ffsize.bit.FFHSZ = 0x0006;
			}
			else if (strcmp((gchar *) argv[4], "60") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 4
				// ffvsz error
				outCtrl.face.param[0].ffsize.bit.FFVSZ = 0x0FF1;
			}
			else if (strcmp((gchar *) argv[4], "61") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 4
				// ffvsz error
				outCtrl.face.param[0].ffsize.bit.FFVSZ = 0x0006;
			}
			else if (strcmp((gchar *) argv[4], "62") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 5
				// ffhwid error
				outCtrl.face.param[0].ffwidth.bit.FFHWID = 0x3F;
			}
			else if (strcmp((gchar *) argv[4], "63") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 5
				// ffhwid error
				outCtrl.face.param[0].ffwidth.bit.FFHWID = 0x00;
			}
			else if (strcmp((gchar *) argv[4], "64") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 6
				// ffvwid error
				outCtrl.face.param[0].ffwidth.bit.FFVWID = 0x3F;
			}
			else if (strcmp((gchar *) argv[4], "65") == 0)
			{
				// "CP:im_disp_param_check_face_frame() 6
				// ffvwid error
				outCtrl.face.param[0].ffwidth.bit.FFVWID = 0x00;
			}

			// "CP:im_disp_param_check_ctrl_output() 28
			else if (strcmp((gchar *) argv[4], "66") == 0)
			{
				// "CP:im_disp_param_check_top_face() 1
				// msff error
				outCtrl.face.msff = 43;
			}


			Disp2bNewParams mParams = {(gpointer)&outCtrlTrgLimit, (gpointer)&outCtrl};
			ImDisp2Parent *imDisp2Parent = im_disp2_group_create_im_disp(disp2Group,
					ImDisp2Group_DO_IM_DISP_TEST_B, (GData)&mParams);
			if(imDisp2Parent){
				im_disp2_parent_do_main(imDisp2Parent, argc, argv);
				g_object_unref(imDisp2Parent);
				imDisp2Parent = NULL;
			}
//			ct_im_disp2b_do_main(argc, argv, &outCtrlTrgLimit, &outCtrl);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "CtrlOUTg") == 0)
	{
		//Im_DISP_Get_Ctrl_Output
		if (argc == 4)
		{
			getCtrlOutLayer(argv[2][0], argv[3][0]);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

static void getCtrlOutLayer(BYTE getDataType, BYTE block)
{
	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT ctrlTrgLimit;
	T_IM_DISP_CTRL_OUTPUT ctrl;
	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT* pCtrlTrgLimit = NULL;
	T_IM_DISP_CTRL_OUTPUT* pCtrl = NULL;
	memset(&ctrlTrgLimit, 0, sizeof(T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT));
	memset(&ctrl, 0, sizeof(T_IM_DISP_CTRL_OUTPUT));
	gint32 loop = 0;
	switch(getDataType){
		case CtImDisp3_D_CT_IM_DISP_NO_PARA:
			break;
		case CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY:
			pCtrlTrgLimit =&ctrlTrgLimit;
			break;
		case CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY:
			pCtrl = &ctrl;
			break;
		case CtImDisp3_D_CT_IM_DISP_BOTH_PARA:
			pCtrlTrgLimit =&ctrlTrgLimit;
			pCtrl = &ctrl;
			break;
		default:
			Ddim_Print(("Command parameter error\n"));
			return;
	}

	E_IM_DISP_SEL blockNum;
	switch(block){
		case CtImDisp3_D_CT_IM_DISP_BLOCK_0:
			blockNum = E_IM_DISP_HDMI;
			break;
		case CtImDisp3_D_CT_IM_DISP_BLOCK_1:
			blockNum = E_IM_DISP_LCD_MIPI;
			break;
		default:
			Ddim_Print(("Command parameter(block num.) error\n"));
			return;
	}

	gint32 error = Im_DISP_Get_Ctrl_Output(blockNum, pCtrlTrgLimit, pCtrl);
	if(error != D_DDIM_OK){
		Ddim_Print(("Im_DISP_Get_Ctrl_Output error=%08X\n",error));
		return;
	}

	if(pCtrlTrgLimit){
		Ddim_Print(("[T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT]\n"));
		// Get TRG.TGKMD/TGKST/TOCTL
		Ddim_Print(("tgkmd          = %08X\n",ctrlTrgLimit.tgkmd));
		Ddim_Print(("tgkst          = %08X\n",(guint32)ctrlTrgLimit.tgkst));
		Ddim_Print(("toctl          = %08X\n",(guint32)ctrlTrgLimit.toctl.word));
		// Get RPGCTL/POLSEL/TSL
		Ddim_Print(("rpgctl         = %08X\n",ctrlTrgLimit.rpgctl));
		Ddim_Print(("polsel         = %08X\n",(guint32)ctrlTrgLimit.polsel.word));
		Ddim_Print(("tsl            = %08X\n",(guint32)ctrlTrgLimit.tsl));
		// Get VCYC/HCYC/VPW/HPW/VBLK/HBLK/VDLY/HDLY/OVSIZE/OHSIZE
		Ddim_Print(("vcyc           = %08X\n",(guint32)ctrlTrgLimit.vcyc.word));
		Ddim_Print(("hcyc           = %08X\n",(guint32)ctrlTrgLimit.hcyc));
		Ddim_Print(("ovpw           = %08X\n",(guint32)ctrlTrgLimit.ovpw.word));
		Ddim_Print(("hpw            = %08X\n",(guint32)ctrlTrgLimit.hpw));
		Ddim_Print(("vblk           = %08X\n",(guint32)ctrlTrgLimit.vblk.word));
		Ddim_Print(("hblk           = %08X\n",(guint32)ctrlTrgLimit.hblk));
		Ddim_Print(("vdly           = %08X\n",(guint32)ctrlTrgLimit.vdly));
		Ddim_Print(("hdly           = %08X\n",(guint32)ctrlTrgLimit.hdly));
		Ddim_Print(("ovsize         = %08X\n",(guint32)ctrlTrgLimit.ovsize));
		Ddim_Print(("ohsize         = %08X\n",(guint32)ctrlTrgLimit.ohsize));
		// Get VRFCTL/HRFCTL
		Ddim_Print(("vrfctl         = %08X\n",(guint32)ctrlTrgLimit.vrfctl));
		Ddim_Print(("hrfctl         = %08X\n",(guint32)ctrlTrgLimit.hrfctl));
		// Get DOMD
		Ddim_Print(("toctl          = %08X\n",(guint32)ctrlTrgLimit.domd.word));
		// Get TBLASET.GMTAEN/TBLASET.YSATTA
		Ddim_Print(("tblaset_gmtaen = %08X\n",ctrlTrgLimit.tblaset_gmtaen));
		Ddim_Print(("tblaset_ysatta = %08X\n",ctrlTrgLimit.tblaset_ysatta));

	}
	if(pCtrl){
		Ddim_Print(("[T_IM_DISP_CTRL_OUTPUT]\n"));
		Ddim_Print(("--- intc/inte ---\n"));
		Ddim_Print(("intc      = %02X\n", (guint32)ctrl.intc));
		Ddim_Print(("inte      = %08X\n", (guint32)ctrl.inte.word));

		Ddim_Print(("--- hablk ---\n"));
		Ddim_Print(("hablk     = %04X\n", (guint32)ctrl.hablk));

		Ddim_Print(("--- fdoen/fodata/blankdt/clbhsize ---\n"));
		Ddim_Print(("fdoen     = %02X\n", (guint32)ctrl.fdoen));
		Ddim_Print(("fodata    = %08X\n", (guint32)ctrl.fodata.word));
		Ddim_Print(("blankdt (RGB/YCbCr) = %04X %04X %04X\n",
				ctrl.blankdt.rgb.r, ctrl.blankdt.rgb.g, ctrl.blankdt.rgb.b));
		Ddim_Print(("clbhsize  = %08X\n", (guint32)ctrl.clbhsize));

		Ddim_Print(("--- clbdt ---\n"));
		ct_im_disp3a_output_word_table((guint32*)ctrl.clbdt, D_IM_DISP_COLOR_BAR_COUNT);

		Ddim_Print(("--- bldctl ---\n"));
		Ddim_Print(("bldctl  = %08X\n",(guint32)ctrl.bldctl.word));

		Ddim_Print(("--- r2y0/1/2 ---\n"));
		ct_im_disp3a_output_byte_9_table(ctrl.r2y);

		Ddim_Print(("--- ycal/yclip/cbcal/cbclip/crcal/crclip ---\n"));
		Ddim_Print(("clip_cal.y_cal.ygain  = %08X\n", (guint32)ctrl.clip_cal.y_cal.ygain));
		Ddim_Print(("clip_cal.y_cal.yofs   = %d\n", (guint32)ctrl.clip_cal.y_cal.yofs));
		Ddim_Print(("clip_cal.y_clip.cph   = %04X\n", (guint32)ctrl.clip_cal.y_clip.cph));
		Ddim_Print(("clip_cal.y_clip.cpl   = %04X\n", (guint32)ctrl.clip_cal.y_clip.cpl));
		Ddim_Print(("clip_cal.cb_cal.cgain = %04X\n", (guint32)ctrl.clip_cal.cb_cal.cgain));
		Ddim_Print(("clip_cal.cb_cal.cofs  = %d\n", ctrl.clip_cal.cb_cal.cofs));
		Ddim_Print(("clip_cal.cb_clip.cph  = %04X\n", (guint32)ctrl.clip_cal.cb_clip.cph));
		Ddim_Print(("clip_cal.cb_clip.cpl  = %04X\n", (guint32)ctrl.clip_cal.cb_clip.cpl));
		Ddim_Print(("clip_cal.cr_cal.cgain = %04X\n", ctrl.clip_cal.cr_cal.cgain));
		Ddim_Print(("clip_cal.cr_cal.cofs  = %d\n", ctrl.clip_cal.cr_cal.cofs));
		Ddim_Print(("clip_cal.cr_clip.cph  = %04X\n", (guint32)ctrl.clip_cal.cr_clip.cph));
		Ddim_Print(("clip_cal.cr_clip.cpl  = %04X\n", (guint32)ctrl.clip_cal.cr_clip.cpl));

		Ddim_Print(("--- doctl0~doctl2 ---\n"));
		Ddim_Print(("doctl0      = %08X\n", (guint32)ctrl.doctl0.word));
		Ddim_Print(("doctl1      = %08X\n", (guint32)ctrl.doctl1.word));
		Ddim_Print(("doctl2      = %08X\n", (guint32)ctrl.doctl2.word));

		Ddim_Print(("--- trscode0/trscode1 ---\n"));
		Ddim_Print(("trscode[0]  = %02X\n", (guint32)ctrl.trscode[0].word));
		Ddim_Print(("trscode[1]  = %02X\n", (guint32)ctrl.trscode[1].word));

		Ddim_Print(("--- y2r0/1/2 ---\n"));
		ct_im_disp3a_output_byte_9_table(ctrl.y2r);

		Ddim_Print(("--- tblaset ---\n"));
		Ddim_Print(("tblaset_gmen    = %02X\n", ctrl.tblaset_gmen));
		Ddim_Print(("tblaset_gmtsl   = %02X\n", (guint32)ctrl.tblaset_gmtsl));
		Ddim_Print(("tblaset_ysaten  = %02X\n", ctrl.tblaset_ysaten));
		Ddim_Print(("tblaset_ysatsl  = %02X\n", (guint32)ctrl.tblaset_ysatsl));

		Ddim_Print(("--- ffdsta ---\n"));
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			Ddim_Print(("%02d : %08X\n", loop, (guint32)ctrl.face.param[loop].ffdsta.word));
		}

		Ddim_Print(("--- ffsize ---\n"));
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			Ddim_Print(("%02d : %08X\n", loop, (guint32)ctrl.face.param[loop].ffsize.word));
		}

		Ddim_Print(("--- ffwidth ---\n"));
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			Ddim_Print(("%02d : %08X\n", loop, (guint32)ctrl.face.param[loop].ffwidth.word));
		}

		Ddim_Print(("--- ffclr ---\n"));
		for(loop = D_IM_DISP_FACE_FRAME_COUNT - 1; loop >= 0 ; loop--) {
			Ddim_Print(("%02d : %08X\n", loop, (guint32)ctrl.face.param[loop].ffclr.word));
		}

		Ddim_Print(("--- ffdispen ---\n"));
		Ddim_Print(("face.ffden  = %llX\n", ctrl.face.ffden));

		Ddim_Print(("--- ffdispen ---\n"));
		Ddim_Print(("face.msff   = %02X\n", (guint32)ctrl.face.msff));

		Ddim_Print(("--- VP_CALLBACK[0~8] ---\n"));
		ct_im_disp3a_output_word_table((guint32*)ctrl.int_callback, E_IM_DISP_INT_CB_MAX);	/* pgr0672 */
	}
}

static void initHdmiDataTgkmd(CtImDisp2a *self)
{
	CtImDisp2aPrivate *priv = self->privCtImDisp2a;

	T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT gLcdDispTblOutCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_END] = {
		{
			(E_IM_DISP_TGKMD)DISP_HDMI_DATA_TGKMD,			// tgkmd
			(ULONG)DISP_HDMI_DATA_TGKST,					// tgkst
			{ DISP_HDMI_DATA_TOCTL },						// toctl
			(E_IM_DISP_RPGTMG)DISP_HDMI_DATA_RPGCTL,		// rpgctl
			{ DISP_HDMI_DATA_POLSEL },						// polsel
			DISP_HDMI_DATA_TSL,								// tsl
			{ DISP_HDMI_DATA_VCYC },						// vcyc
			DISP_HDMI_DATA_HCYC,							// hcyc
			{ DISP_HDMI_DATA_OVPW },						// ovpw
			DISP_HDMI_DATA_HPW,								// hpw
			{ DISP_HDMI_DATA_VBLK },						// vblk
			DISP_HDMI_DATA_HBLK,							// hblk
			DISP_HDMI_DATA_VDLY,							// vdly
			DISP_HDMI_DATA_HDLY,							// hdly
			DISP_HDMI_DATA_OVSIZE,							// ovsize
			DISP_HDMI_DATA_OHSIZE,							// ohsize
			DISP_HDMI_DATA_VRFCTL,							// vrfctl
			DISP_HDMI_DATA_HRFCTL,							// hrfctl
			{ DISP_HDMI_DATA_DOMD },						// domd
			(E_IM_DISP_TABLE_ACCESS)DISP_HDMI_DATA_GMTAEN,	// tblaset_gmtaen
			(E_IM_DISP_TABLE_ACCESS)DISP_HDMI_DATA_YSATTA,	// tblaset_ysatta
		},
		{
			(E_IM_DISP_TGKMD)DISP_LCD_DATA_TGKMD,			// tgkmd
			(ULONG)DISP_LCD_DATA_TGKST,						// tgkst
			{ DISP_LCD_DATA_TOCTL },						// toctl
			(E_IM_DISP_RPGTMG)DISP_LCD_DATA_RPGCTL,			// rpgctl
			{ DISP_LCD_DATA_POLSEL },						// polsel
			DISP_LCD_DATA_TSL,								// tsl
			{ DISP_LCD_DATA_VCYC },							// vcyc
			DISP_LCD_DATA_HCYC,								// hcyc
			{ DISP_LCD_DATA_OVPW },							// ovpw
			DISP_LCD_DATA_HPW,								// hpw
			{ DISP_LCD_DATA_VBLK },							// vblk
			DISP_LCD_DATA_HBLK,								// hblk
			DISP_LCD_DATA_VDLY,								// vdly
			DISP_LCD_DATA_HDLY,								// hdly
			DISP_LCD_DATA_OVSIZE,							// ovsize
			DISP_LCD_DATA_OHSIZE,							// ohsize
			DISP_LCD_DATA_VRFCTL,							// vrfctl
			DISP_LCD_DATA_HRFCTL,							// hrfctl
			{ DISP_LCD_DATA_DOMD },							// domd
			(E_IM_DISP_TABLE_ACCESS)DISP_LCD_DATA_GMTAEN,	// tblaset_gmtaen
			(E_IM_DISP_TABLE_ACCESS)DISP_LCD_DATA_YSATTA,	// tblaset_ysatta
		}
	};

	memcpy(priv->gLcdDispTblOutCtrlTrgLimit, gLcdDispTblOutCtrlTrgLimit,
			sizeof(priv->gLcdDispTblOutCtrlTrgLimit));
}

/*
 * PUBLIC
 * */

CtImDisp2a *ct_im_disp2a_new(void)
{
	CtImDisp2a *self = (CtImDisp2a *) g_object_new(CT_TYPE_IM_DISP2A, NULL);
	return self;
}
