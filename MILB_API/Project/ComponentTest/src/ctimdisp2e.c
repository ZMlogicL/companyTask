/*
 *ctimdisp2e.c
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

#include "ctimdisp4.h"//variable
#include "ctimdisp3.h"//static func
#include "ctimdisp3a.h"

#include "imdisp2group.h"
#include "ctimdisp2e.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2e, ct_im_disp2e, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2E_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2E, CtImDisp2ePrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2ePrivate
{
	gpointer qwertyu;
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
static void disp2eDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * IMPL
 * */
static void ct_im_disp2e_class_init(CtImDisp2eClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2ePrivate));
}

static void ct_im_disp2e_init(CtImDisp2e *self)
{
	//CtImDisp2ePrivate *priv = CT_IM_DISP2E_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2eDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
}

static void dispose_od(GObject *object)
{
//	CtImDisp2e *self = CT_IM_DISP2E(object);
//	CtImDisp2ePrivate *priv = CT_IM_DISP2E_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2e_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2e *self = CT_IM_DISP2E(object);
//	CtImDisp2ePrivate *priv = CT_IM_DISP2E_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2e_parent_class)->finalize(object);
}

#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2eDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	gint32 error = D_DDIM_OK;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	guchar *pImDispPclkCounter = im_disp2_group_get_pclk_counter(imDisp2Group);
	CtImDisp3 *disp3 = (CtImDisp3 *)im_disp2_group_get_disp3(imDisp2Group);

	if (strcmp((gchar *) argv[1], "SetRefTiming") == 0)
	{
		//Im_DISP_Set_Parameter_Reflect_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetRefTiming"
		// argv[2] block(0/1)
		// argv[3] timming(0:FRAME_TOP/1:VSYNC)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_RPGTMG timing = (E_IM_DISP_RPGTMG) strtoul(argv[3], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRPGCTL = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LRPGCTL.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Parameter_Reflect_Timing(block, timing); /* pgr0539 */
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LRPGCTL = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LRPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetRefTiming") == 0)
	{
		//Im_DISP_Get_Parameter_Reflect_Timing

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetRefTiming"
		// argv[2] Command select(0:NULL pointer/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_RPGTMG timing;
			timing = E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP;

			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Parameter_Reflect_Timing(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Parameter_Reflect_Timing(block, &timing); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Parameter_Reflect_Timing error=%08X\n", error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[0].LCH.LRPGCTL = %08X\n",
						(guint32)IO_DISP.MAIN[0].LCH.LRPGCTL.word));
				Ddim_Print(("IO_DISP.MAIN[1].LCH.LRPGCTL = %08X\n",
						(guint32)IO_DISP.MAIN[1].LCH.LRPGCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
				Ddim_Print(("Reflect timing = %d\n", timing));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetITrans") == 0)
	{
		//Im_DISP_Set_Input_Data_Transfer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetITrans"
		// argv[2] block(0/1)
		// argv[3] lidt[0]
		// argv[4] lidt[1]

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT0 = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LIDT0.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT1 = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LIDT1.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			U_IM_DISP_LIDT lidt;
			lidt.word[0] = strtoul(argv[3], NULL, 0);
			lidt.word[1] = strtoul(argv[4], NULL, 0);

			error = Im_DISP_Set_Input_Data_Transfer(block, lidt);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Input_Data_Transfer error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT0 = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIDT0.word));
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT1 = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIDT1.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetITrans") == 0)
	{
		//Im_DISP_Get_Input_Data_Transfer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetITrans"
		// argv[2] Command select(0:NULL pointer/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			U_IM_DISP_LIDT lidt;
			memset(&lidt, 0, sizeof(U_IM_DISP_LIDT));
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Input_Data_Transfer(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Input_Data_Transfer(block, &lidt); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Input_Data_Transfer error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT0 = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIDT0.word));
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIDT1 = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIDT1.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_LIDT]\n"));
				Ddim_Print(("IFMT  :%d\n", lidt.bit.IFMT));
				Ddim_Print(("NBT   :%d\n", lidt.bit.NBT));
				Ddim_Print(("IFEW  :%d\n", lidt.bit.IFEW));
				Ddim_Print(("LVFM  :%d\n", lidt.bit.LVFM));
				Ddim_Print(("PKGDV :%d\n", lidt.bit.PKGDV));
				Ddim_Print(("CACHE :%d\n", lidt.bit.CACHE));
				Ddim_Print(("PROT  :%d\n", lidt.bit.PROT));
				Ddim_Print(("YSLVSL:%d\n", lidt.bit.YSLVSL));
				Ddim_Print(("CSLVSL:%d\n", lidt.bit.CSLVSL));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetISize") == 0)
	{
		//Im_DISP_Set_Input_Size

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "SetISize"
		// argv[2] block(0/1)
		// argv[3] size

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LISIZE = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LISIZE.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING

			U_IM_DISP_SIZE inputSize;
			inputSize.word = strtoul(argv[3], NULL, 0);
			error = Im_DISP_Set_Input_Size(block, inputSize);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Input_Size error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LISIZE = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LISIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetISize") == 0)
	{
		//Im_DISP_Get_Input_Size

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetISize"
		// argv[2] Command select(0:NULL pointer/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			U_IM_DISP_SIZE inputSize;
			memset(&inputSize, 0, sizeof(U_IM_DISP_SIZE));
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Input_Size(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Input_Size(block, &inputSize); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Input_Size error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP[%d].MAIN.LCH.LISIZE = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LISIZE.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("[U_IM_DISP_SIZE]\n"));
				Ddim_Print(("width=0x%04X, lines=0x%04X\n",inputSize.size.width,inputSize.size.lines));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetAdd") == 0)
	{
		//Im_DISP_Set_Addr

		// argc=7
		// argv[0] "imdisp"
		// argv[1] "SetAdd"
		// argv[2] Command select(0:NULL pointer/1:Normal)
		// argv[3] block(0/1)
		// argv[4] bank(0~3)
		// argv[5] y_addr.(0~3)
		// argv[6] c_addr.(0~3)

		if (argc == 7)
		{

			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_BANK bank_no = (E_IM_DISP_BANK) strtoul(argv[4], NULL, 0);
			T_IM_DISP_IMAGE_ADDR add;
			add.y_addr = strtoul((gchar *) argv[5], NULL, 16);
			add.c_addr = strtoul((gchar *) argv[6], NULL, 16);

			Ddim_Print(("[input] bank=%d y_addr=%08x c_addr=%08x\n",
					(guint32)bank_no, (guint32)add.y_addr, (guint32)add.c_addr)); /* pgr0539 */
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_addr(disp3);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Set_Addr(block, bank_no, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Set_Addr(block, bank_no, &add); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Addr error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_addr(disp3);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 7\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetAdd") == 0)
	{
		//Im_DISP_Get_Addr

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "GetAdd"
		// argv[2] Command select(0:NULL pointer/1:Normal)
		// argv[3] block(0/1)
		// argv[4] bank(0~3)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_BANK bank_no = (E_IM_DISP_BANK) strtoul(argv[4], NULL, 0);
			T_IM_DISP_IMAGE_ADDR add;
			memset(&add, 0, sizeof(T_IM_DISP_IMAGE_ADDR));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Addr(block, bank_no, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Addr(block, bank_no, &add); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Addr error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_addr(disp3);

				Ddim_Print(("Y data address = %08X, CbCr data address = %08X\n",
						(guint32)add.y_addr,(guint32)add.c_addr));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetLfd") == 0)
	{
		//Im_DISP_Set_Lfd

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "SetLfd"
		// argv[2] block(0/1)
		// argv[3] y_hga
		// argv[4] c_hga

		if (argc == 5)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);

			ULONG y_hga = strtoul(argv[3], NULL, 0);
			ULONG c_hga = strtoul(argv[4], NULL, 0);

			Ddim_Print(("[input] y_hga = %08x, c_hga = %08x\n", (guint32)y_hga, (guint32)c_hga)); /* pgr0539 */
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHGA = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LYHGA.word)); /* pgr0539 */
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCHGA = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LCHGA.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			error = Im_DISP_Set_Lfd(block, y_hga, c_hga);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Lfd error=%08X\n", error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHGA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LYHGA.word));
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCHGA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LCHGA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetLfd") == 0)
	{
		//Im_DISP_Get_Lfd

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetLfd"
		// argv[2] Command select(0:both NULL/1:y_hga NULL/2:c_hga NULL/3:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			ULONG y_hga = 0, c_hga = 0;

			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Lfd(block, NULL, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Lfd(block, NULL, &c_hga); /* pgr0539 */
				break;
			case '2':
				error = Im_DISP_Get_Lfd(block, &y_hga, NULL); /* pgr0539 */
				break;
			case '3':
				error = Im_DISP_Get_Lfd(block, &y_hga, &c_hga); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Lfd error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LYHGA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LYHGA.word));
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LCHGA = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LCHGA.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("y_hga = %08X, c_hga = %08X\n", (guint32)y_hga, (guint32)c_hga));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetMBank") == 0)
	{
		//Im_DISP_Set_Main_Bank

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetLfd"
		// argv[2] block(0/1)
		// argv[3] bank_no(0~3)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[2], NULL, 0);
			E_IM_DISP_BANK bank_no = (E_IM_DISP_BANK) strtoul(argv[3], NULL, 0);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIBCTL = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LIBCTL.word)); /* pgr0539 */
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Im_DISP_Set_Main_Bank(block, bank_no); /* pgr0539 */

			Ddim_Print(("------- After Setting -------\n"));
			ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
			Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIBCTL = %08X\n",
					block, (guint32)IO_DISP.MAIN[block].LCH.LIBCTL.word));
			ct_im_disp3_pclk_counter_off(pImDispPclkCounter);
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetMBank") == 0)
	{
		//Im_DISP_Get_Main_Bank

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetMBank"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_BANK bank_no = E_IM_DISP_BANK_00;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Main_Bank(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Main_Bank(block, &bank_no); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Main_Bank error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIBCTL = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIBCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("bank_no:%d\n",bank_no));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetMBkMon") == 0)
	{
		//Im_DISP_Get_Main_Bank_Monitor

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetMBkMon"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			E_IM_DISP_BANK bank_no = E_IM_DISP_BANK_00;

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Main_Bank_Monitor(block, NULL); /* pgr0539 */
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Get_Main_Bank_Monitor(block, &bank_no); /* pgr0539 */
			}
			else
			{
				Ddim_Print(("Parameter command error.\n"));
				return;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Main_Bank_Monitor error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_pclk_counter_on(pImDispPclkCounter);
				Ddim_Print(("IO_DISP.MAIN[%d].LCH.LIBCTL = %08X\n",
						block, (guint32)IO_DISP.MAIN[block].LCH.LIBCTL.word));
				ct_im_disp3_pclk_counter_off(pImDispPclkCounter);

				Ddim_Print(("bank_no:%d\n",bank_no));
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetRes") == 0)
	{
		//Im_DISP_Set_Resize

		// argc=8
		// argv[0] "imdisp"
		// argv[1] "SetRes"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] lrsz0
		// argv[5] lrsz1
		// argv[6] lrsz2
		// argv[7] lrsz3

		if (argc == 8)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_RESIZE resize;
			resize.rsz0 = (E_IM_DISP_RSZSL) strtoul(argv[4], NULL, 0);
			resize.rsz1.word = strtoul(argv[5], NULL, 0);
			resize.rsz2.word = strtoul(argv[6], NULL, 0);
			resize.rsz3.word = strtoul(argv[7], NULL, 0);
#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_resize(disp3);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Set_Resize(block, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Set_Resize(block, &resize); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Resize error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_resize(disp3);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 8\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetRes") == 0)
	{
		//Im_DISP_Get_Resize

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetRes"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_RESIZE resize;
			resize.rsz0 = E_IM_DISP_RSZSL_PADDING_THINNING;
			resize.rsz1.word = 0;
			resize.rsz2.word = 0;
			resize.rsz3.word = 0;
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Resize(block, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Resize(block, &resize); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Resize error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_resize(disp3);

				ct_im_disp3_print_param_resize(resize);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 4\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "SetYhlp") == 0)
	{
		//Im_DISP_Set_Yhlp

		// argc=9
		// argv[0] "imdisp"
		// argv[1] "SetYhlp"
		// argv[2] Command select(0:NULL/1:Normal)
		// argv[3] block(0/1)
		// argv[4] lyhlpcl
		// argv[5] lyhlpk0
		// argv[6] lyhlpk1
		// argv[7] lyhlpol
		// argv[8] lyhlpclr(DWORD)

		if (argc == 9)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_YHLP yhelp;
			yhelp.lyhlpcl.word = strtoul(argv[4], NULL, 0);
			yhelp.lyhlpk.word[0] = strtoul(argv[5], NULL, 0);
			yhelp.lyhlpk.word[1] = strtoul(argv[6], NULL, 0);
			yhelp.lyhlpol.word = strtoul(argv[7], NULL, 0);
			yhelp.lyhlpclr.dword = (ULLONG) strtoull(argv[8], NULL, 0);

			Ddim_Print(("------- Input Value -------\n"));
			Ddim_Print(("lyhlpcl        = 0x%08X\n", (guint32)yhelp.lyhlpcl.word)); /* pgr0539 */
			Ddim_Print(("lyhlpk.word[0] = 0x%08X\n", (guint32)yhelp.lyhlpk.word[0]));
			Ddim_Print(("lyhlpk.word[1] = 0x%08X\n", (guint32)yhelp.lyhlpk.word[1]));
			Ddim_Print(("lyhlpol        = 0x%08X\n", (guint32)yhelp.lyhlpol.word)); /* pgr0539 */
			Ddim_Print(("lyhlpclr       = 0x%llX\n", yhelp.lyhlpclr.dword)); /* pgr0539 */

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3_dump_reg_yhelp(disp3, block); /* pgr0539 */
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Set_Yhlp(block, NULL);
				break;
			case '1':
				error = Im_DISP_Set_Yhlp(block, &yhelp);
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Set_Yhlp error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3_dump_reg_yhelp(disp3, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 5\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "GetYhlp") == 0)
	{
		//Im_DISP_Get_Yhlp

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "GetYhlp"
		// argv[2] Command select(0:Normal/1:NULL)
		// argv[3] block(0/1)

		if (argc == 4)
		{
			E_IM_DISP_SEL block = (E_IM_DISP_SEL) strtoul(argv[3], NULL, 0);
			T_IM_DISP_YHLP Yhlp;
			memset(&Yhlp, 0, sizeof(T_IM_DISP_YHLP));
			switch (argv[2][0])
			{
			case '0':
				error = Im_DISP_Get_Yhlp(block, NULL); /* pgr0539 */
				break;
			case '1':
				error = Im_DISP_Get_Yhlp(block, &Yhlp); /* pgr0539 */
				break;
			default:
				Ddim_Print(("Parameter command error.\n"));
				return;
				break;
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Yhlp error=%08X\n",error));
			}
			else
			{
				ct_im_disp3_dump_reg_yhelp(disp3, block);

				ct_im_disp3_print_param_yhelp(Yhlp);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}

}
#endif /*CtImDisp_CO_DEBUG_DISP*/

/*
 * PUBLIC
 * */

CtImDisp2e *ct_im_disp2e_new(void)
{
	CtImDisp2e *self = (CtImDisp2e *) g_object_new(CT_TYPE_IM_DISP2E, NULL);
	return self;
}
