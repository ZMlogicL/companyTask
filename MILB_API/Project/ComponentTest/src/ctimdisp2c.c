/*
 *ctimdisp2c.c
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
#include "ctimdisp2c.h"

/*
 * G_DEFINE_语句
 * */
G_DEFINE_TYPE (CtImDisp2c, ct_im_disp2c, IM_TYPE_DISP2_PARENT);

/*
 * 以下开始宏定义
 * */
#define CT_IM_DISP2C_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), CT_TYPE_IM_DISP2C, CtImDisp2cPrivate))

/*
 * 内部结构体或类型定义
 * */
struct _CtImDisp2cPrivate
{
	gpointer qwertyu;
	T_IM_DISP_CTRL_GRID_LAYER gLcdDispTblGridCtrl[CtImDisp4_LCD_DISP_SEL_END];
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
static void disp2cDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv);
#endif /*CtImDisp_CO_DEBUG_DISP*/
static void initTblGridCtrl(CtImDisp2c *self);

/*
 * IMPL
 * */
static void ct_im_disp2c_class_init(CtImDisp2cClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImDisp2cPrivate));
}

static void ct_im_disp2c_init(CtImDisp2c *self)
{
	CtImDisp2cPrivate *priv = CT_IM_DISP2C_GET_PRIVATE(self);
#ifdef CtImDisp_CO_DEBUG_DISP
	ImDisp2Parent *parent = (ImDisp2Parent *)self;
	parent->doMainFunc = disp2cDoMain_od;
#endif /*CtImDisp_CO_DEBUG_DISP*/
	self->privCtImDisp2c = priv;

	initTblGridCtrl(self);
}

static void dispose_od(GObject *object)
{
//	CtImDisp2c *self = CT_IM_DISP2C(object);
//	CtImDisp2cPrivate *priv = CT_IM_DISP2C_GET_PRIVATE(self);
	/*释放创建的对象1*/
//	if (priv->objectMine) {
//		g_object_unref(priv->objectMine);
//		priv->objectMine = NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2c_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtImDisp2c *self = CT_IM_DISP2C(object);
//	CtImDisp2cPrivate *priv = CT_IM_DISP2C_GET_PRIVATE(self);
	/*释放创建的内存2*/
//	if(self->name)
//	{
//		free(self->name);
//		self->name =NULL;
//	}
	G_OBJECT_CLASS (ct_im_disp2c_parent_class)->finalize(object);
}


#ifdef CtImDisp_CO_DEBUG_DISP
static void disp2cDoMain_od(ImDisp2Parent *parent, gint32 argc, char **argv)
{
	guint32 layer = 0;
	gint32 error = D_DDIM_OK;
	CtImDisp2c *self =(CtImDisp2c *)parent;
	CtImDisp2cPrivate *priv = self->privCtImDisp2c;
	ImDisp2Group *imDisp2Group = (ImDisp2Group *)im_disp2_parent_get_group(parent);
	CtImDisp3a *disp3a = (CtImDisp3a *)im_disp2_group_get_disp3a(imDisp2Group);

	if (strcmp((gchar *) argv[1], "CtrlGRIDs") == 0)
	{
		//Im_DISP_Ctrl_Grid_Layer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "CtrlGRIDs"
		// argv[2] Parameter assign
		// argv[3] block
		// argv[4] parameter Setting Num.

		// Normal:check ALL Settings(argv[2] == '0')
		// Illegal:NULL pointer(argv[2] == '1')
		// Illegal:IFMT Illegal(argv[2] != '2')

		if (argc == 5)
		{
			E_IM_DISP_SEL block = strtoul(argv[3], NULL, 0);
			Ddim_Print(("Block Number = %d\n", block)); /* pgr0539 */

			T_IM_DISP_CTRL_GRID_LAYER ctrl;
			T_IM_DISP_CTRL_GRID_LAYER* pGrid_ctrl = (void *) &ctrl;
			memcpy(pGrid_ctrl, (void *) &(priv->gLcdDispTblGridCtrl[block]), sizeof(T_IM_DISP_CTRL_GRID_LAYER));

			if (strcmp((gchar *) argv[4], "1") == 0)
			{
				pGrid_ctrl->grid.ghdsta.bit.DSH = 3;
			}
			else if (strcmp((gchar *) argv[4], "2") == 0)
			{
				pGrid_ctrl->grid.ghdsta.bit.DSV = 3;
			}
			else if (strcmp((gchar *) argv[4], "3") == 0)
			{
				pGrid_ctrl->grid.gvdsta.bit.DSH = 3;
			}
			else if (strcmp((gchar *) argv[4], "4") == 0)
			{
				pGrid_ctrl->grid.gvdsta.bit.DSV = 3;
			}
			else if (strcmp((gchar *) argv[4], "5") == 0)
			{
				pGrid_ctrl->grid.glength.bit.GHLEN = 9;
			}
			else if (strcmp((gchar *) argv[4], "6") == 0)
			{
				pGrid_ctrl->grid.glength.bit.GHLEN = 6;
			}
			else if (strcmp((gchar *) argv[4], "7") == 0)
			{
				pGrid_ctrl->grid.glength.bit.GVLEN = 9;
			}
			else if (strcmp((gchar *) argv[4], "8") == 0)
			{
				pGrid_ctrl->grid.glength.bit.GVLEN = 6;
			}
			else if (strcmp((gchar *) argv[4], "9") == 0)
			{
				pGrid_ctrl->grid.gwidth.bit.GHWID = 3;
			}
			else if (strcmp((gchar *) argv[4], "10") == 0)
			{
				pGrid_ctrl->grid.gwidth.bit.GHWID = 0;
			}
			else if (strcmp((gchar *) argv[4], "11") == 0)
			{
				pGrid_ctrl->grid.gwidth.bit.GVWID = 3;
			}
			else if (strcmp((gchar *) argv[4], "12") == 0)
			{
				pGrid_ctrl->grid.gwidth.bit.GVWID = 0;
			}
			else if (strcmp((gchar *) argv[4], "13") == 0)
			{
				pGrid_ctrl->grid.gitvl.bit.GHITV = 5;
			}
			else if (strcmp((gchar *) argv[4], "14") == 0)
			{
				pGrid_ctrl->grid.gitvl.bit.GHITV = 2;
			}
			else if (strcmp((gchar *) argv[4], "15") == 0)
			{
				pGrid_ctrl->grid.gitvl.bit.GVITV = 5;
			}
			else if (strcmp((gchar *) argv[4], "16") == 0)
			{
				pGrid_ctrl->grid.gitvl.bit.GVITV = 2;
			}
			/*				else if(strcmp((gchar *)argv[4], "17")==0) {
			 pGrid_ctrl->grid.gnum.bit.GHNUM = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "18")==0) {
			 pGrid_ctrl->grid.gnum.bit.GHNUM = 7;
			 }
			 else if(strcmp((gchar *)argv[4], "19")==0) {
			 pGrid_ctrl->grid.gnum.bit.GVNUM = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "20")==0) {
			 pGrid_ctrl->grid.gnum.bit.GVNUM = 7;
			 }
			 else if(strcmp((gchar *)argv[4], "21")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRR = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "22")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRR = 0xFF;
			 }
			 else if(strcmp((gchar *)argv[4], "23")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRG = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "24")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRG = 0xFF;
			 }
			 else if(strcmp((gchar *)argv[4], "25")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRG = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "26")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GCLRB = 0xFF;
			 }
			 else if(strcmp((gchar *)argv[4], "27")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GALP = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "28")==0) {
			 pGrid_ctrl->grid.gdctl.bit.GALP = 3;
			 }*/
			/*				else if(strcmp((gchar *)argv[4], "29")==0) {
			 pGrid_ctrl->gdispen = 1;
			 }
			 else if(strcmp((gchar *)argv[4], "30")==0) {
			 pGrid_ctrl->gdispen = 0;
			 }*/

#ifdef CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			Ddim_Print(("------- Before Setting -------\n"));
			ct_im_disp3a_dump_reg_grid(disp3a, block);
			ct_im_disp3a_print_param_ctrl_grid(ctrl);
#endif	// CtImDisp_CO_DEBUG_PRINT_BEFORE_SETTING
			if (argv[2][0] == '0')
			{
				error = Im_DISP_Ctrl_Grid_Layer(block, NULL);
			}
			else if (argv[2][0] == '1')
			{
				error = Im_DISP_Ctrl_Grid_Layer(block, pGrid_ctrl);
			}
//				else if (argv[2][0] == '2') {
//					//IFMT Setting
//					pGrid_ctrl->grid.bit.IFMT = 5;
//					error = Im_DISP_Ctrl_Grid_Layer(block, pGrid_ctrl);
//				}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Ctrl_Grid_Layer error=%08X\n",error));
			}
			else
			{
				Ddim_Print(("------- After Setting -------\n"));
				ct_im_disp3a_dump_reg_grid(disp3a, block);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "CtrlGRIDg") == 0)
	{
		//Im_DISP_Get_Ctrl_Grid_Layer

		// argc=4
		// argv[0] "imdisp"
		// argv[1] "CtrlGRIDg"
		// argv[2] parameter assign
		// argv[3] block

		// Normal:check ALL settings(argv[2] == '0')
		// Illegal:NULL pointer(argv[2] == '1')

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
			Ddim_Print(("Block Number = %d\n", block));

			T_IM_DISP_CTRL_GRID_LAYER ctrl;

			memset(&ctrl, 0, sizeof(T_IM_DISP_CTRL_GRID_LAYER));

			if (argv[2][0] == '0')
			{
				error = Im_DISP_Get_Ctrl_Grid_Layer(block, NULL);
			}
			else
			{
				error = Im_DISP_Get_Ctrl_Grid_Layer(block, &ctrl);
			}
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Ctrl_Grid_Layer error=%08X\n",error));
			}
			else
			{
				ct_im_disp3a_dump_reg_grid(disp3a, block);
				ct_im_disp3a_print_param_ctrl_grid(ctrl);
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 2\n"));
		}
	}
	else if (strcmp((gchar *) argv[1], "Ctrl_OSDg") == 0)
	{
		//Im_DISP_Get_Ctrl_OSD_Layer

		// argc=5
		// argv[0] "imdisp"
		// argv[1] "Ctrl_OSDg"
		// argv[2] Command select(0:both NULL, 1:first NULL, 2:second NULL, 3:Normal)
		// argv[3] block
		// argv[4] layer(0x0004/0x0008)

		if (argc == 5)
		{
			E_IM_DISP_SEL block = strtoul(argv[3], NULL, 0);
			layer = strtoul(argv[4], NULL, 0);
			E_IM_DISP_RPGTMG grrpgctl = 0;
			E_IM_DISP_RPGTMG *pGrrpgctl = 0;
			T_IM_DISP_CTRL_OSD_LAYER ctrl;
			memset(&ctrl, 0, sizeof(T_IM_DISP_CTRL_OSD_LAYER));
			T_IM_DISP_CTRL_OSD_LAYER *pCtrl = 0;

			if (argv[2][0] == '0')
			{
			}
			else if (argv[2][0] == '1')
			{
				pCtrl = &ctrl;
			}
			else if (argv[2][0] == '2')
			{
				pGrrpgctl = &grrpgctl;
			}
			else if (argv[2][0] == '3')
			{
				pGrrpgctl = &grrpgctl;
				pCtrl = &ctrl;
			}
			Ddim_Print(("Block:%d, Layer:%d\n",block, layer)); /* pgr0539 */

			error = Im_DISP_Get_Ctrl_OSD_Layer(block, (E_IM_DISP_SEL_LAYER) layer, pGrrpgctl, pCtrl);
			if (error != D_DDIM_OK)
			{
				Ddim_Print(("Im_DISP_Get_Ctrl_OSD_Layer error=%08X\n",error));
			}
			else
			{
				if (pGrrpgctl != NULL)
				{

					Ddim_Print(("[E_IM_DISP_RPGTMG]\n"));
					Ddim_Print(("grrpgctl = %08X\n",grrpgctl));
				}
				if (pCtrl != NULL)
				{
					ct_im_disp3a_dump_regiser(disp3a, layer, block);
					ct_im_disp3a_print_param_grch(ctrl);
				}
			}
		}
		else
		{
			Ddim_Print(("Parameter num shold be 3\n"));
		}
	}
}
#endif /*CtImDisp_CO_DEBUG_DISP*/

static void initTblGridCtrl(CtImDisp2c *self)
{
	CtImDisp2cPrivate *priv = self->privCtImDisp2c;
	T_IM_DISP_CTRL_GRID_LAYER tblGridCtrl[CtImDisp4_LCD_DISP_SEL_END] = {
		{
			{
				{ DISP_HDMI_DATA_GHDSTA },
				{ DISP_HDMI_DATA_GVDSTA },
				{ DISP_HDMI_DATA_GLENGTH },
				{ DISP_HDMI_DATA_GWIDTH },
				{ DISP_HDMI_DATA_GITVL },
				{ DISP_HDMI_DATA_GNUM },
				{ DISP_HDMI_DATA_GDCTL }
			},
			(E_IM_DISP_GDISPEN)DISP_HDMI_DATA_GDISPEN
		},
		{
			{
				{ DISP_LCD_DATA_GHDSTA },
				{ DISP_LCD_DATA_GVDSTA },
				{ DISP_LCD_DATA_GLENGTH },
				{ DISP_LCD_DATA_GWIDTH },
				{ DISP_LCD_DATA_GITVL },
				{ DISP_LCD_DATA_GNUM },
				{ DISP_LCD_DATA_GDCTL }
			},
			(E_IM_DISP_GDISPEN)DISP_LCD_DATA_GDISPEN
		}
	};
	memcpy(&priv->gLcdDispTblGridCtrl, &tblGridCtrl, sizeof(tblGridCtrl));
}

/*
 * PUBLIC
 * */

CtImDisp2c *ct_im_disp2c_new(void)
{
	CtImDisp2c *self = (CtImDisp2c *) g_object_new(CT_TYPE_IM_DISP2C, NULL);
	return self;
}
