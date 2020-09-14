/*
 *ctimdisp2.c
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

#include "ctimdisp4.h"//variable macro

#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"

#include "imdisp2group.h"
#include "ctimdisp2.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2, ct_im_disp2, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2, CtImDisp2Private))

#define CtImDisp2_M_LCD_DISP_TBL_GET_IGTAEN(TBLASET)	((TBLASET) & 0x1)
#define CtImDisp2_M_LCD_DISP_TBL_GET_DGTAEN(TBLASET)	(((TBLASET)>>8) & 0x1)

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2Private
{
	T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_END];
	T_IM_DISP_CTRL_MAIN_LAYER gLcdDispTblMainCtrl[CtImDisp4_LCD_DISP_SEL_END];
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
static void disp2DoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/
static void initDisp2TblMainCtrl(CtImDisp2 *self);

/*
 * IMPL
 * */
static void ct_im_disp2_class_init(CtImDisp2Class *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2Private));
}

static void ct_im_disp2_init(CtImDisp2 *self)
{
	CtImDisp2Private *priv = CT_IM_DISP2_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2DoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/

	self->privCtImDisp2 = priv;

	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_HDMI].lrpgctl = (E_IM_DISP_RPGTMG)DISP_HDMI_LRPGCTL;
	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_HDMI].ltblaset_igtaen = (E_IM_DISP_TABLE_ACCESS)
			CtImDisp2_M_LCD_DISP_TBL_GET_IGTAEN( DISP_HDMI_LTBLASET );
	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_HDMI].ltblaset_gtaen = (E_IM_DISP_TABLE_ACCESS)
			CtImDisp2_M_LCD_DISP_TBL_GET_DGTAEN( DISP_HDMI_LTBLASET );

	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_LCD].lrpgctl = (E_IM_DISP_RPGTMG)DISP_LCD_LRPGCTL;
	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_LCD].ltblaset_igtaen = (E_IM_DISP_TABLE_ACCESS)
				CtImDisp2_M_LCD_DISP_TBL_GET_IGTAEN( DISP_LCD_LTBLASET );
	priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_LCD].ltblaset_gtaen = (E_IM_DISP_TABLE_ACCESS)
				CtImDisp2_M_LCD_DISP_TBL_GET_DGTAEN( DISP_LCD_LTBLASET );

	initDisp2TblMainCtrl(self);
}

static void dispose_od(GObject *object)
{
//	CtImDisp2 *self = CT_IM_DISP2(object);
//	CtImDisp2Private *priv = CT_IM_DISP2_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2 *self = CT_IM_DISP2(object);
//	CtImDisp2Private *priv = CT_IM_DISP2_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2_parent_class)->finalize(object);
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2DoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	gint32 error = D_DDIM_OK;
	CtImDisp2 *self = (CtImDisp2 *)parent;
	CtImDisp2Private *priv = self->privCtImDisp2;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	Ddim_Print(("*.. DISP CT command execute.\n"));
	if (strcmp((gchar *) argv[1], "Init") == 0)
	{
		//Im_DISP_Init
		if (argc == 2)
		{
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_reset(disp3);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Init();

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_dump_reg_reset(disp3);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 1\n"));
		}

	}
	else if (strcmp((gchar *) argv[1], "CtrlMs") == 0)
	{
		//Im_DISP_Ctrl_Main_Layer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "CtrlMs"
		// argv[2] Parameter assign(0:NO para/1:only first para/2:only second para/3:both para)
		// argv[3] block
		// argv[4] setting

		if (argc == 5)
		{
			E_IM_DISP_SEL block = E_IM_DISP_HDMI;
			T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT* pMain_ctrl_trg_limit = NULL;
			T_IM_DISP_CTRL_MAIN_LAYER* pMain_ctrl = NULL;
			T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT mainCtrlTrgLimit;
			T_IM_DISP_CTRL_MAIN_LAYER mainCtrl;
			switch (argv[3][0])
			{
			case CtImDisp3_D_CT_IM_DISP_BLOCK_0:
				block = E_IM_DISP_HDMI;
				memcpy((void *) &mainCtrlTrgLimit,
						(void *) &priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_HDMI],
						sizeof(T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT));
				memcpy((void *) &mainCtrl,
						(void *) &priv->gLcdDispTblMainCtrl[CtImDisp4_LCD_DISP_SEL_HDMI],
						sizeof(T_IM_DISP_CTRL_MAIN_LAYER));
				break;
			case CtImDisp3_D_CT_IM_DISP_BLOCK_1:
				block = E_IM_DISP_LCD_MIPI;
				memcpy((void *) &mainCtrlTrgLimit,
						(void *) &priv->gLcdDispTblMainCtrlTrgLimit[CtImDisp4_LCD_DISP_SEL_LCD],
						sizeof(T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT));
				memcpy((void *) &mainCtrl,
						(void *) &priv->gLcdDispTblMainCtrl[CtImDisp4_LCD_DISP_SEL_LCD],
						sizeof(T_IM_DISP_CTRL_MAIN_LAYER));
				break;
			default:
				Ddim_Print(("Parameter(block num.) error\n"));
				break;
			}
			Ddim_Print(("Block Number = %d\n", block));
			ct_im_disp3a_clear_reg_lch(disp3a, block);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_HDMI);
			ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_LCD_MIPI);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			switch (argv[2][0])
			{
			case CtImDisp3_D_CT_IM_DISP_NO_PARA:
				break;
			case CtImDisp3_D_CT_IM_DISP_FIRST_PARA_ONLY:
				pMain_ctrl_trg_limit = (void *) &mainCtrlTrgLimit;
				break;
			case CtImDisp3_D_CT_IM_DISP_SECOND_PARA_ONLY:
				pMain_ctrl = (void *) &mainCtrl;
				break;
			case CtImDisp3_D_CT_IM_DISP_BOTH_PARA:
				pMain_ctrl_trg_limit = (void *) &mainCtrlTrgLimit;
				pMain_ctrl = (void *) &mainCtrl;
				break;
			default:
				Ddim_Print(("Command parameter error\n"));
				break;
			}

			// parameter check
			if (strcmp((gchar *) argv[4], "1") == 0)
			{	// subnormality
				mainCtrl.ltblaset_igen = 0;
			}
			else if (strcmp((gchar *) argv[4], "2") == 0)
			{	// subnormality
				mainCtrl.ltblaset_gmen = (E_IM_DISP_CORRECT_PROC) 0;
			}
			else if (strcmp((gchar *) argv[4], "3") == 0)
			{	// OK
				mainCtrl.lidt.word[0] = 0x00013300;
			}
			else if (strcmp((gchar *) argv[4], "4") == 0)
			{	//Block:1 is NG/Block:0 isOK
				mainCtrl.lidt.word[0] = 0x00013301;
			}
			else if (strcmp((gchar *) argv[4], "5") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x00013302;
			}
			else if (strcmp((gchar *) argv[4], "6") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x00013303;
			}
			else if (strcmp((gchar *) argv[4], "7") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x00013307;
			}
			else if (strcmp((gchar *) argv[4], "8") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x00013308;
			}
			else if (strcmp((gchar *) argv[4], "9") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x0001330A;
			}
			else if (strcmp((gchar *) argv[4], "10") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x0001330B;
			}
			else if (strcmp((gchar *) argv[4], "11") == 0)
			{	// NG
				mainCtrl.lidt.word[0] = 0x0001331B;
			}
			else if (strcmp((gchar *) argv[4], "12") == 0)
			{	// NG
			    //						 0x00013304
				mainCtrl.lidt.word[0] = 0x0001331C;
			}
			else if (strcmp((gchar *) argv[4], "13") == 0)
			{	//NG
				mainCtrl.lisize.word = 0x0010007E;		// width:126 lines:16
			}
			else if (strcmp((gchar *) argv[4], "14") == 0)
			{	//NG
				mainCtrl.lisize.word = 0x00100081;		// width:129 lines:16
			}
			else if (strcmp((gchar *) argv[4], "15") == 0)
			{	//NG
				mainCtrl.lisize.word = 0x000E0080;		// width:128 lines:14
			}
			else if (strcmp((gchar *) argv[4], "16") == 0)
			{	//NG
				mainCtrl.lisize.word = 0x00110080;		// width:128 lines:17
			}
			else if (strcmp((gchar *) argv[4], "17") == 0)
			{	//NG
				mainCtrl.ldsta.word = 0x00000001;
			}
			else if (strcmp((gchar *) argv[4], "18") == 0)
			{	//NG
				mainCtrl.ldsta.word = 0x00010000;
			}
			else if (strcmp((gchar *) argv[4], "19") == 0)
			{	//NG
				mainCtrl.y_hga = 0;
				mainCtrl.c_hga = 256;
			}
			else if (strcmp((gchar *) argv[4], "20") == 0)
			{	//NG
				mainCtrl.y_hga = 1;
				mainCtrl.c_hga = 0;
			}
			else if (strcmp((gchar *) argv[4], "21") == 0)
			{	//NG
				mainCtrl.y_hga = 0;
				mainCtrl.c_hga = 0;
			}
			else if (strcmp((gchar *) argv[4], "22") == 0)
			{	//NG
				mainCtrl.y_hga = 0;
				mainCtrl.c_hga = 1;
			}
			else if (strcmp((gchar *) argv[4], "23") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_BILINEAR;
				mainCtrl.lrsz1.word = 0x00001F0F;
				mainCtrl.lrsz2.word = 0x00001F0F;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "24") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_BILINEAR;
				mainCtrl.lrsz1.word = 0x00000319;
				mainCtrl.lrsz2.word = 0x00001F0F;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "25") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_PADDING_THINNING;
				mainCtrl.lrsz1.word = 0x04001F10;
				mainCtrl.lrsz2.word = 0x00001F0F;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "26") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_BILINEAR;
				mainCtrl.lrsz1.word = 0x04000808;
				mainCtrl.lrsz2.word = 0x00001F0F;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "27") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_BILINEAR;
				mainCtrl.lrsz1.word = 0x04000804;
				mainCtrl.lrsz2.word = 0x00001F0F;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "28") == 0)
			{	//NG
				mainCtrl.lrsz0 = E_IM_DISP_RSZSL_PADDING_THINNING;
				mainCtrl.lrsz1.word = 0x00000804;
				mainCtrl.lrsz2.word = 0x00000301;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "29") == 0)
			{	//NG
				mainCtrl.lrsz1.word = 0x00000804;
				mainCtrl.lrsz2.word = 0x00000401;
				mainCtrl.lrsz3.word = 0x00003F3F;
			}
			else if (strcmp((gchar *) argv[4], "30") == 0)
			{	//NG
				mainCtrl.warning.lyw0th.word = 0x00010000;
			}
			else if (strcmp((gchar *) argv[4], "31") == 0)
			{	//NG
				mainCtrl.warning.lyw1th.word = 0x00010000;
			}
			else if (strcmp((gchar *) argv[4], "32") == 0)
			{	//NG
				mainCtrl.warning.lywctl.word = 0xFFFF00FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_G;
			}
			else if (strcmp((gchar *) argv[4], "33") == 0)
			{	//NG
				mainCtrl.warning.lywctl.word = 0xFFFF01FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_B;
			}
			else if (strcmp((gchar *) argv[4], "34") == 0)
			{	//NG
				mainCtrl.warning.lywctl.word = 0xFFFF01FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_BR_RGB;
				mainCtrl.warning.lyw1st = E_IM_DISP_YWMD_G;
			}
			else if (strcmp((gchar *) argv[4], "35") == 0)
			{	//NG
				mainCtrl.warning.lywctl.word = 0xFFFF00FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_BW_R;
				mainCtrl.warning.lyw1st = E_IM_DISP_YWMD_B;
			}
			else if (strcmp((gchar *) argv[4], "36") == 0)
			{	//NG
				mainCtrl.warning.lbost = 0x00000002;
			}
			else if (strcmp((gchar *) argv[4], "37") == 0)
			{	//OK
				mainCtrl.warning.lbost = 0x00000000;
			}
			else if (strcmp((gchar *) argv[4], "38") == 0)
			{	//OK
				mainCtrl.warning.lywctl.word = 0xFFFF02FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_BR_RGB;
			}
			else if (strcmp((gchar *) argv[4], "39") == 0)
			{	//OK
				mainCtrl.warning.lywctl.word = 0xFFFF03FF;
				mainCtrl.warning.lyw0st = E_IM_DISP_YWMD_BW_R;
			}
			// route check.
//				else if(strcmp((gchar *)argv[3], "29")==0) {
//					mainCtrl.warning.lbost = 0x00000002;
//				}
			error = Im_DISP_Ctrl_Main_Layer(block, pMain_ctrl_trg_limit, pMain_ctrl);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Ctrl_Main_Layer error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_HDMI);
				ct_im_disp3a_dump_regiser(disp3a, E_IM_DISP_SEL_LAYER_MAIN, E_IM_DISP_LCD_MIPI);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}

	}
	else if (strcmp((gchar *) argv[1], "CtrlMg") == 0)
	{
		//Im_DISP_Get_Ctrl_Main_Layer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "CtrlMg"
		// argv[2] Parameter assign(0:NO para/1:only first para/2:only second para/3:both para)
		// argv[3] block

		if (argc == 4)
		{
			E_IM_DISP_SEL block = E_IM_DISP_HDMI;

			switch (argv[3][0])
			{
			case CtImDisp3_D_CT_IM_DISP_BLOCK_0:
				block = E_IM_DISP_HDMI;
				break;
			case CtImDisp3_D_CT_IM_DISP_BLOCK_1:
				block = E_IM_DISP_LCD_MIPI;
				break;
			default:
				Ddim_Print(("Parameter(block num.) error\n"));
				break;
			}

			ct_im_disp3a_get_ctrl_main_layer(argv[2][0], block);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

static void initDisp2TblMainCtrl(CtImDisp2 *self)
{
	CtImDisp2Private *priv = self->privCtImDisp2;

	T_IM_DISP_CTRL_MAIN_LAYER tblMainCtrl[CtImDisp4_LCD_DISP_SEL_END] = {
		{
			{ 												// lidt
				{ DISP_HDMI_LIDT0, DISP_HDMI_LIDT1 },		// D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
			},
			{ DISP_HDMI_LISIZE },							// lisize
			{												// laddr[D_IM_DISP_MAIN_ADDR_BANK_SIZE]
				{
					DISP_HDMI_LYSA0,
					DISP_HDMI_LCSA0
				},
				{
					DISP_HDMI_LYSA1,
					DISP_HDMI_LCSA1
				},
				{
					DISP_HDMI_LYSA2,
					DISP_HDMI_LCSA2
				},
				{
					DISP_HDMI_LYSA3,
					DISP_HDMI_LCSA3
				}
			},
			DISP_HDMI_LYHGA,								// y_hga
			DISP_HDMI_LCHGA,								// c_hga
			( DISP_HDMI_LIBCTL & 0xFFFFFFFE ),				// libctl_iben
			(E_IM_DISP_BANK)( (DISP_HDMI_LIBCTL & 0x00000300) >> 8 ),			// libctl_ibset
			(E_IM_DISP_RSZSL)DISP_HDMI_LHRSZ0,				// lrsz0
			{ DISP_HDMI_LHRSZ1 },							// lrsz1
			{ DISP_HDMI_LHRSZ2 },							// lrsz2
			{ DISP_HDMI_LHRSZ3 },							// lrsz3

			{												// yhlp
				{ DISP_HDMI_LYHLPCTL },						// lyhlpcl
				{											// lyhlpk
					{ DISP_HDMI_LYHLPK0, DISP_HDMI_LYHLPK1 },
				},
				{ DISP_HDMI_LYHLPOL },						// lyhlpol
				{ DISP_HDMI_LYHLPCLR },						// lyhlpclr
			},
			{												// warning
				{ (ULONG)DISP_HDMI_LYWCTL },				// lywctl
				{ (ULONG)DISP_HDMI_LYW0TH },				// lyw0th
				{ (ULONG)DISP_HDMI_LYW1TH} ,				// lyw1th
				(E_IM_DISP_YWMD)DISP_HDMI_LYW0ST,			// lyw0st
				{ (ULLONG)DISP_HDMI_LYW0CA },				// lyw0ca
				{ (ULLONG)DISP_HDMI_LYW0CB },				// lyw0cb
				(E_IM_DISP_YWMD)DISP_HDMI_LYW1ST,			// lyw1st
				{ (ULLONG)DISP_HDMI_LYW1CA },				// lyw1ca
				{ (ULLONG)DISP_HDMI_LYW1CB },				// lyw1cb
				(ULONG)DISP_HDMI_LBOST,						// lbost
			},
			{ DISP_HDMI_LBLTMR },							// lbltmr
			{												// zebra
				{ DISP_HDMI_LZBWID },						// lzbwid
				{ DISP_HDMI_LZBV },							// lzbv
				{ DISP_HDMI_LZBPT },						// lzbpt
			},
			{												// ly2r[3]
				{ (LLONG)DISP_HDMI_LY2R0_0 },
				{ (LLONG)DISP_HDMI_LY2R1_0 },
				{ (LLONG)DISP_HDMI_LY2R2_0 }
			},
			(E_IM_DISP_CORRECT_PROC)DISP_HDMI_IGEN,			// ltblaset_igen
			(BYTE)DISP_HDMI_IGTSL,							// ltblaset_igtsl
			(E_IM_DISP_CORRECT_PROC)DISP_HDMI_GMEN,			// ltblaset_gmen
			(BYTE)DISP_HDMI_GMTSL,							// ltblaset_gmtsl
			{												// lcc[3]
				{ (LLONG)DISP_HDMI_LCC0_0 },
				{ (LLONG)DISP_HDMI_LCC1_0 },
				{ (LLONG)DISP_HDMI_LCC2_0 },
			},
			{ DISP_HDMI_LGMMD },							// lgmmd
			{ DISP_HDMI_LALP },								// lalp
			{ DISP_HDMI_LDSTA },							// ldsta
			{ DISP_HDMI_LREVDISP },							// lrevdisp
		},
		{
			{ 												// lidt
				{ DISP_LCD_LIDT0, DISP_LCD_LIDT1 }			// D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT
			},
			{ DISP_LCD_LISIZE },							// lisize
			{												// laddr[D_IM_DISP_MAIN_ADDR_BANK_SIZE]
				{
					DISP_LCD_LYSA0,
					DISP_LCD_LCSA0
				},
				{
					DISP_LCD_LYSA1,
					DISP_LCD_LCSA1
				},
				{
					DISP_LCD_LYSA2,
					DISP_LCD_LCSA2
				},
				{
					DISP_LCD_LYSA3,
					DISP_LCD_LCSA3
				}
			},
			DISP_LCD_LYHGA,									// y_hga
			DISP_LCD_LCHGA,									// c_hga
			( DISP_LCD_LIBCTL & 0xFFFFFFFE ),				// libctl_iben
			(E_IM_DISP_BANK)( (DISP_LCD_LIBCTL & 0x00000300) >> 8 ),			// libctl_ibset
			(E_IM_DISP_RSZSL)DISP_LCD_LHRSZ0,				// lrsz0
			{ DISP_LCD_LHRSZ1 },							// lrsz1
			{ DISP_LCD_LHRSZ2 },							// lrsz2
			{ DISP_LCD_LHRSZ3 },							// lrsz3

			{												// yhlp
				{ DISP_LCD_LYHLPCTL },						// lyhlpcl
				{											// lyhlpk
					{ (ULONG)DISP_LCD_LYHLPK0, (ULONG)DISP_LCD_LYHLPK1 }
				},
				{ DISP_LCD_LYHLPOL },						// lyhlpol
				{ DISP_LCD_LYHLPCLR }						// lyhlpclr
			},
			{												// warning
				{ (ULONG)DISP_LCD_LYWCTL },					// lywctl
				{ (ULONG)DISP_LCD_LYW0TH },					// lyw0th
				{ (ULONG)DISP_LCD_LYW1TH },					// lyw1th
				(E_IM_DISP_YWMD)DISP_LCD_LYW0ST,			// lyw0st
				{ (ULLONG)DISP_LCD_LYW0CA },				// lyw0ca
				{ (ULLONG)DISP_LCD_LYW0CB },				// lyw0cb
				(E_IM_DISP_YWMD)DISP_LCD_LYW1ST,			// lyw1st
				{ (ULLONG)DISP_LCD_LYW1CA },				// lyw1ca
				{ (ULLONG)DISP_LCD_LYW1CB },				// lyw1cb
				(ULONG)DISP_LCD_LBOST						// lbost
			},
			{ DISP_LCD_LBLTMR },							// lbltmr
			{												// zebra
				{ DISP_LCD_LZBWID },						// lzbwid
				{ DISP_LCD_LZBV },							// lzbv
				{ DISP_LCD_LZBPT },							// lzbpt
			},
			{												// ly2r[3]
				{ (LLONG)DISP_LCD_LY2R0_0 },
				{ (LLONG)DISP_LCD_LY2R1_0 },
				{ (LLONG)DISP_LCD_LY2R2_0 }
			},
			(E_IM_DISP_CORRECT_PROC)DISP_LCD_IGEN,			// ltblaset_igen
			(BYTE)DISP_LCD_IGTSL,							// ltblaset_igtsl
			(E_IM_DISP_CORRECT_PROC)DISP_LCD_GMEN,			// ltblaset_gmen
			(BYTE)DISP_LCD_GMTSL,							// ltblaset_gmtsl
			{												// lcc[3]
				{ (LLONG)DISP_LCD_LCC0_0 },
				{ (LLONG)DISP_LCD_LCC1_0 },
				{ (LLONG)DISP_LCD_LCC2_0 },
			},
			{ DISP_LCD_LGMMD },								// lgmmd
			{ DISP_LCD_LALP },								// lalp
			{ DISP_LCD_LDSTA },								// ldsta
			{ DISP_LCD_LREVDISP },							// lrevdisp
		}
	};

	memcpy(&priv->gLcdDispTblMainCtrl, &tblMainCtrl, sizeof(tblMainCtrl));
}

/*
 * PUBLIC
 * */

CtImDisp2 *ct_im_disp2_new(void)
{
	CtImDisp2 *self = (CtImDisp2 *) g_object_new(CT_TYPE_IM_DISP2, NULL);
	return self;
}
