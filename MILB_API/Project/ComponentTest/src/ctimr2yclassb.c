/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassb
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassb.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassb, ct_im_r2y_classb)
#define CT_IM_R2Y_CLASSB_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClassbPrivate, CT_TYPE_IM_R2Y_CLASSB))


struct _CtImR2yClassbPrivate
{

};


static void ct_im_r2y_classb_constructor(CtImR2yClassb *self)
{
	CtImR2yClassbPrivate *priv = CT_IM_R2Y_CLASSB_GET_PRIVATE(self);
	self->ctImR2yClassb=ct_im_r2y_classb_new();
	self->ctImR2yClassa=ct_im_r2y_classa_new();
	self->imR2yCtrl2=im_r2y_ctrl2_new();
	self->imR2yClk=im_r2y_clk_new();
	self->imR2yStat=im_r2y_stat_new();
	self->imR2y=im_r2y_new();
}

static void ct_im_r2y_classb_destructor(CtImR2yClassb *self)
{
	CtImR2yClassbPrivate *priv = CT_IM_R2Y_CLASSB_GET_PRIVATE(self);

	if(self->ctImR2yClassb){
				k_object_unref(self->ctImR2yClassb);
				self->ctImR2yClassb=NULL;
			}

	if(self->ctImR2yClassa){
			k_object_unref(self->ctImR2yClassa);
			self->ctImR2yClassa=NULL;
		}


	if(self->imR2yCtrl2){
		k_object_unref(self->imR2yCtrl2);
		self->imR2yCtrl2=NULL;
	}

	if(self->imR2yClk){
			k_object_unref(self->imR2yClk);
			self->imR2yClk=NULL;
		}
	if(self->imR2yStat){
				k_object_unref(self->imR2yStat);
				self->imR2yStat=NULL;
			}
	if(self->imR2y){
				k_object_unref(self->imR2y);
				self->imR2y=NULL;
			}
}



VOID ct_im_r2y_classb_print_post_resize_edge1_reg( CtImR2yClassb * self )
{
	im_r2y_clk_on_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( "yyw.ee1ctl.bit.ee1en          = 0x%x\n", ioR2yP1.yyw.ee1ctl.bit.ee1en ));
	Ddim_Print(( "yyw.ee1ctl.bit.ee1tc          = 0x%x\n", ioR2yP1.yyw.ee1ctl.bit.ee1tc ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk0      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk0 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk1      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk1 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk2      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk2 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk3      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk3 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk4      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk4 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk5      = 0x%x\n", ioR2yP1.yyw.ee1hpfk.bit.ee1hpfk5 ));
	Ddim_Print(( "yyw.ee1nrlv.bit.ee1nrlv       = 0x%x\n", ioR2yP1.yyw.ee1nrlv.bit.ee1nrlv ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof0 = 0x%x\n", ioR2yP1.yyw.ee1corpof.bit.ee1corpof0 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof1 = 0x%x\n", ioR2yP1.yyw.ee1corpof.bit.ee1corpof1 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof2 = 0x%x\n", ioR2yP1.yyw.ee1corpof.bit.ee1corpof2 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof3 = 0x%x\n", ioR2yP1.yyw.ee1corpof.bit.ee1corpof3 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga0 = 0x%x\n", ioR2yP1.yyw.ee1corpga.bit.ee1corpga0 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga1 = 0x%x\n", ioR2yP1.yyw.ee1corpga.bit.ee1corpga1 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga2 = 0x%x\n", ioR2yP1.yyw.ee1corpga.bit.ee1corpga2 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga3 = 0x%x\n", ioR2yP1.yyw.ee1corpga.bit.ee1corpga3 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd1 = 0x%x\n", ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd1 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd2 = 0x%x\n", ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd2 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd3 = 0x%x\n", ioR2yP1.yyw.ee1corpbd.bit.ee1corpbd3 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof0 = 0x%x\n", ioR2yP1.yyw.ee1cormof.bit.ee1cormof0 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof1 = 0x%x\n", ioR2yP1.yyw.ee1cormof.bit.ee1cormof1 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof2 = 0x%x\n", ioR2yP1.yyw.ee1cormof.bit.ee1cormof2 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof3 = 0x%x\n", ioR2yP1.yyw.ee1cormof.bit.ee1cormof3 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga0 = 0x%x\n", ioR2yP1.yyw.ee1cormga.bit.ee1cormga0 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga1 = 0x%x\n", ioR2yP1.yyw.ee1cormga.bit.ee1cormga1 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga2 = 0x%x\n", ioR2yP1.yyw.ee1cormga.bit.ee1cormga2 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga3 = 0x%x\n", ioR2yP1.yyw.ee1cormga.bit.ee1cormga3 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd1 = 0x%x\n", ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd1 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd2 = 0x%x\n", ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd2 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd3 = 0x%x\n", ioR2yP1.yyw.ee1cormbd.bit.ee1cormbd3 ));
	Ddim_Print(( "yyw.ee1sclsup.bit.ee1sclsup   = 0x%x\n", ioR2yP1.yyw.ee1sclsup.bit.ee1sclsup ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof0 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof0 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof1 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof1 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof2 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof2 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof3 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof3 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof4 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof4 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof5 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof5 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof6 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof6 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof7 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof7 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof8 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof8 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof9 = 0x%x\n", ioR2yP1.yyw.ee1sclpof.bit.ee1sclpof9 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga0 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga0 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga1 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga1 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga2 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga2 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga3 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga3 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga4 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga4 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga5 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga5 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga6 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga6 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga7 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga7 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga8 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga8 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga9 = 0x%x\n", ioR2yP1.yyw.ee1sclpga.bit.ee1sclpga9 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd1 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd1 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd2 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd2 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd3 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd3 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd4 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd4 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd5 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd5 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd6 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd6 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd7 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd7 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd8 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd8 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd9 = 0x%x\n", ioR2yP1.yyw.ee1sclpbd.bit.ee1sclpbd9 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof0 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof0 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof1 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof1 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof2 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof2 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof3 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof3 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof4 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof4 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof5 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof5 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof6 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof6 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof7 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof7 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof8 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof8 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof9 = 0x%x\n", ioR2yP1.yyw.ee1sclmof.bit.ee1sclmof9 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga0 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga0 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga1 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga1 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga2 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga2 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga3 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga3 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga4 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga4 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga5 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga5 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga6 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga6 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga7 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga7 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga8 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga8 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga9 = 0x%x\n", ioR2yP1.yyw.ee1sclmga.bit.ee1sclmga9 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd1 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd1 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd2 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd2 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd3 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd3 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd4 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd4 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd5 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd5 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd6 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd6 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd7 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd7 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd8 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd8 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd9 = 0x%x\n", ioR2yP1.yyw.ee1sclmbd.bit.ee1sclmbd9 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof0 = 0x%x\n", ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof0 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof1 = 0x%x\n", ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof1 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof2 = 0x%x\n", ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof2 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof3 = 0x%x\n", ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof3 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof4 = 0x%x\n", ioR2yP1.yyw.ee1tonpof.bit.ee1tonpof4 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga0 = 0x%x\n", ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga0 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga1 = 0x%x\n", ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga1 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga2 = 0x%x\n", ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga2 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga3 = 0x%x\n", ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga3 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga4 = 0x%x\n", ioR2yP1.yyw.ee1tonpga.bit.ee1tonpga4 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd1 = 0x%x\n", ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd1 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd2 = 0x%x\n", ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd2 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd3 = 0x%x\n", ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd3 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd4 = 0x%x\n", ioR2yP1.yyw.ee1tonpbd.bit.ee1tonpbd4 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof0 = 0x%x\n", ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof0 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof1 = 0x%x\n", ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof1 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof2 = 0x%x\n", ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof2 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof3 = 0x%x\n", ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof3 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof4 = 0x%x\n", ioR2yP1.yyw.ee1tonmof.bit.ee1tonmof4 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga0 = 0x%x\n", ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga0 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga1 = 0x%x\n", ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga1 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga2 = 0x%x\n", ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga2 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga3 = 0x%x\n", ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga3 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga4 = 0x%x\n", ioR2yP1.yyw.ee1tonmga.bit.ee1tonmga4 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd1 = 0x%x\n", ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd1 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd2 = 0x%x\n", ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd2 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd3 = 0x%x\n", ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd3 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd4 = 0x%x\n", ioR2yP1.yyw.ee1tonmbd.bit.ee1tonmbd4 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof0 = 0x%x\n", ioR2yP1.yyw.ee1clppof.bit.ee1clppof0 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof1 = 0x%x\n", ioR2yP1.yyw.ee1clppof.bit.ee1clppof1 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof2 = 0x%x\n", ioR2yP1.yyw.ee1clppof.bit.ee1clppof2 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga0 = 0x%x\n", ioR2yP1.yyw.ee1clppga.bit.ee1clppga0 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga1 = 0x%x\n", ioR2yP1.yyw.ee1clppga.bit.ee1clppga1 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga2 = 0x%x\n", ioR2yP1.yyw.ee1clppga.bit.ee1clppga2 ));
	Ddim_Print(( "yyw.ee1clppbd.bit.ee1clppbd1 = 0x%x\n", ioR2yP1.yyw.ee1clppbd.bit.ee1clppbd1 ));
	Ddim_Print(( "yyw.ee1clppbd.bit.ee1clppbd2 = 0x%x\n", ioR2yP1.yyw.ee1clppbd.bit.ee1clppbd2 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof0 = 0x%x\n", ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof0 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof1 = 0x%x\n", ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof1 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof2 = 0x%x\n", ioR2yP1.yyw.ee1clpmof.bit.ee1clpmof2 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga0 = 0x%x\n", ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga0 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga1 = 0x%x\n", ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga1 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga2 = 0x%x\n", ioR2yP1.yyw.ee1clpmga.bit.ee1clpmga2 ));
	Ddim_Print(( "yyw.ee1clpmbd.bit.ee1clpmbd1 = 0x%x\n", ioR2yP1.yyw.ee1clpmbd.bit.ee1clpmbd1 ));
	Ddim_Print(( "yyw.ee1clpmbd.bit.ee1clpmbd2 = 0x%x\n", ioR2yP1.yyw.ee1clpmbd.bit.ee1clpmbd2 ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "yyw.ee1ctl.bit.ee1en          = 0x%x\n", ioR2yP2.yyw.ee1ctl.bit.ee1en ));
	Ddim_Print(( "yyw.ee1ctl.bit.ee1tc          = 0x%x\n", ioR2yP2.yyw.ee1ctl.bit.ee1tc ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk0      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk0 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk1      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk1 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk2      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk2 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk3      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk3 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk4      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk4 ));
	Ddim_Print(( "yyw.ee1hpfk.bit.ee1hpfk5      = 0x%x\n", ioR2yP2.yyw.ee1hpfk.bit.ee1hpfk5 ));
	Ddim_Print(( "yyw.ee1nrlv.bit.ee1nrlv       = 0x%x\n", ioR2yP2.yyw.ee1nrlv.bit.ee1nrlv ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof0 = 0x%x\n", ioR2yP2.yyw.ee1corpof.bit.ee1corpof0 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof1 = 0x%x\n", ioR2yP2.yyw.ee1corpof.bit.ee1corpof1 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof2 = 0x%x\n", ioR2yP2.yyw.ee1corpof.bit.ee1corpof2 ));
	Ddim_Print(( "yyw.ee1corpof.bit.ee1corpof3 = 0x%x\n", ioR2yP2.yyw.ee1corpof.bit.ee1corpof3 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga0 = 0x%x\n", ioR2yP2.yyw.ee1corpga.bit.ee1corpga0 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga1 = 0x%x\n", ioR2yP2.yyw.ee1corpga.bit.ee1corpga1 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga2 = 0x%x\n", ioR2yP2.yyw.ee1corpga.bit.ee1corpga2 ));
	Ddim_Print(( "yyw.ee1corpga.bit.ee1corpga3 = 0x%x\n", ioR2yP2.yyw.ee1corpga.bit.ee1corpga3 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd1 = 0x%x\n", ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd1 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd2 = 0x%x\n", ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd2 ));
	Ddim_Print(( "yyw.ee1corpbd.bit.ee1corpbd3 = 0x%x\n", ioR2yP2.yyw.ee1corpbd.bit.ee1corpbd3 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof0 = 0x%x\n", ioR2yP2.yyw.ee1cormof.bit.ee1cormof0 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof1 = 0x%x\n", ioR2yP2.yyw.ee1cormof.bit.ee1cormof1 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof2 = 0x%x\n", ioR2yP2.yyw.ee1cormof.bit.ee1cormof2 ));
	Ddim_Print(( "yyw.ee1cormof.bit.ee1cormof3 = 0x%x\n", ioR2yP2.yyw.ee1cormof.bit.ee1cormof3 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga0 = 0x%x\n", ioR2yP2.yyw.ee1cormga.bit.ee1cormga0 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga1 = 0x%x\n", ioR2yP2.yyw.ee1cormga.bit.ee1cormga1 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga2 = 0x%x\n", ioR2yP2.yyw.ee1cormga.bit.ee1cormga2 ));
	Ddim_Print(( "yyw.ee1cormga.bit.ee1cormga3 = 0x%x\n", ioR2yP2.yyw.ee1cormga.bit.ee1cormga3 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd1 = 0x%x\n", ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd1 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd2 = 0x%x\n", ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd2 ));
	Ddim_Print(( "yyw.ee1cormbd.bit.ee1cormbd3 = 0x%x\n", ioR2yP2.yyw.ee1cormbd.bit.ee1cormbd3 ));
	Ddim_Print(( "yyw.ee1sclsup.bit.ee1sclsup   = 0x%x\n", ioR2yP2.yyw.ee1sclsup.bit.ee1sclsup ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof0 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof0 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof1 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof1 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof2 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof2 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof3 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof3 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof4 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof4 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof5 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof5 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof6 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof6 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof7 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof7 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof8 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof8 ));
	Ddim_Print(( "yyw.ee1sclpof.bit.ee1sclpof9 = 0x%x\n", ioR2yP2.yyw.ee1sclpof.bit.ee1sclpof9 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga0 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga0 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga1 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga1 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga2 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga2 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga3 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga3 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga4 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga4 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga5 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga5 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga6 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga6 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga7 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga7 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga8 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga8 ));
	Ddim_Print(( "yyw.ee1sclpga.bit.ee1sclpga9 = 0x%x\n", ioR2yP2.yyw.ee1sclpga.bit.ee1sclpga9 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd1 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd1 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd2 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd2 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd3 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd3 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd4 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd4 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd5 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd5 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd6 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd6 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd7 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd7 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd8 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd8 ));
	Ddim_Print(( "yyw.ee1sclpbd.bit.ee1sclpbd9 = 0x%x\n", ioR2yP2.yyw.ee1sclpbd.bit.ee1sclpbd9 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof0 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof0 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof1 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof1 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof2 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof2 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof3 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof3 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof4 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof4 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof5 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof5 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof6 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof6 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof7 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof7 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof8 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof8 ));
	Ddim_Print(( "yyw.ee1sclmof.bit.ee1sclmof9 = 0x%x\n", ioR2yP2.yyw.ee1sclmof.bit.ee1sclmof9 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga0 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga0 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga1 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga1 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga2 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga2 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga3 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga3 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga4 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga4 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga5 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga5 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga6 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga6 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga7 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga7 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga8 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga8 ));
	Ddim_Print(( "yyw.ee1sclmga.bit.ee1sclmga9 = 0x%x\n", ioR2yP2.yyw.ee1sclmga.bit.ee1sclmga9 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd1 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd1 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd2 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd2 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd3 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd3 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd4 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd4 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd5 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd5 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd6 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd6 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd7 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd7 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd8 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd8 ));
	Ddim_Print(( "yyw.ee1sclmbd.bit.ee1sclmbd9 = 0x%x\n", ioR2yP2.yyw.ee1sclmbd.bit.ee1sclmbd9 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof0 = 0x%x\n", ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof0 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof1 = 0x%x\n", ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof1 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof2 = 0x%x\n", ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof2 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof3 = 0x%x\n", ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof3 ));
	Ddim_Print(( "yyw.ee1tonpof.bit.ee1tonpof4 = 0x%x\n", ioR2yP2.yyw.ee1tonpof.bit.ee1tonpof4 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga0 = 0x%x\n", ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga0 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga1 = 0x%x\n", ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga1 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga2 = 0x%x\n", ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga2 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga3 = 0x%x\n", ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga3 ));
	Ddim_Print(( "yyw.ee1tonpga.bit.ee1tonpga4 = 0x%x\n", ioR2yP2.yyw.ee1tonpga.bit.ee1tonpga4 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd1 = 0x%x\n", ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd1 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd2 = 0x%x\n", ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd2 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd3 = 0x%x\n", ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd3 ));
	Ddim_Print(( "yyw.ee1tonpbd.bit.ee1tonpbd4 = 0x%x\n", ioR2yP2.yyw.ee1tonpbd.bit.ee1tonpbd4 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof0 = 0x%x\n", ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof0 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof1 = 0x%x\n", ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof1 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof2 = 0x%x\n", ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof2 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof3 = 0x%x\n", ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof3 ));
	Ddim_Print(( "yyw.ee1tonmof.bit.ee1tonmof4 = 0x%x\n", ioR2yP2.yyw.ee1tonmof.bit.ee1tonmof4 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga0 = 0x%x\n", ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga0 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga1 = 0x%x\n", ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga1 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga2 = 0x%x\n", ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga2 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga3 = 0x%x\n", ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga3 ));
	Ddim_Print(( "yyw.ee1tonmga.bit.ee1tonmga4 = 0x%x\n", ioR2yP2.yyw.ee1tonmga.bit.ee1tonmga4 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd1 = 0x%x\n", ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd1 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd2 = 0x%x\n", ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd2 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd3 = 0x%x\n", ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd3 ));
	Ddim_Print(( "yyw.ee1tonmbd.bit.ee1tonmbd4 = 0x%x\n", ioR2yP2.yyw.ee1tonmbd.bit.ee1tonmbd4 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof0 = 0x%x\n", ioR2yP2.yyw.ee1clppof.bit.ee1clppof0 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof1 = 0x%x\n", ioR2yP2.yyw.ee1clppof.bit.ee1clppof1 ));
	Ddim_Print(( "yyw.ee1clppof.bit.ee1clppof2 = 0x%x\n", ioR2yP2.yyw.ee1clppof.bit.ee1clppof2 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga0 = 0x%x\n", ioR2yP2.yyw.ee1clppga.bit.ee1clppga0 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga1 = 0x%x\n", ioR2yP2.yyw.ee1clppga.bit.ee1clppga1 ));
	Ddim_Print(( "yyw.ee1clppga.bit.ee1clppga2 = 0x%x\n", ioR2yP2.yyw.ee1clppga.bit.ee1clppga2 ));
	Ddim_Print(( "yyw.ee1clppbd.bit.ee1clppbd1 = 0x%x\n", ioR2yP2.yyw.ee1clppbd.bit.ee1clppbd1 ));
	Ddim_Print(( "yyw.ee1clppbd.bit.ee1clppbd2 = 0x%x\n", ioR2yP2.yyw.ee1clppbd.bit.ee1clppbd2 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof0 = 0x%x\n", ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof0 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof1 = 0x%x\n", ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof1 ));
	Ddim_Print(( "yyw.ee1clpmof.bit.ee1clpmof2 = 0x%x\n", ioR2yP2.yyw.ee1clpmof.bit.ee1clpmof2 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga0 = 0x%x\n", ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga0 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga1 = 0x%x\n", ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga1 ));
	Ddim_Print(( "yyw.ee1clpmga.bit.ee1clpmga2 = 0x%x\n", ioR2yP2.yyw.ee1clpmga.bit.ee1clpmga2 ));
	Ddim_Print(( "yyw.ee1clpmbd.bit.ee1clpmbd1 = 0x%x\n", ioR2yP2.yyw.ee1clpmbd.bit.ee1clpmbd1 ));
	Ddim_Print(( "yyw.ee1clpmbd.bit.ee1clpmbd2 = 0x%x\n", ioR2yP2.yyw.ee1clpmbd.bit.ee1clpmbd2 ));
	im_r2y_clk_off_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
}

VOID ct_im_classb_r2y_print_other_reg( CtImR2yClassb * self )
{
	im_r2y_clk_on_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
	Ddim_Print(( "\n" ));
	// Other
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( "yyw.yywctl.bit.usebank0  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank0 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a00  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a00 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a10  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a10 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a20  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a20 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a01  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a01 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a11  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a11 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a21  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a21 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a02  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a02 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a12  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a12 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a22  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a22 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a03  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a03 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a13  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a13 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a23  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a23 ));
	Ddim_Print(( "yyw.yywctl.bit.usebank1  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank1 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a00  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a00 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a10  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a10 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a20  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a20 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a01  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a01 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a11  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a11 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a21  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a21 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a02  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a02 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a12  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a12 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a22  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a22 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a03  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a03 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a13  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a13 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a23  = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a23 ));
	Ddim_Print(( "yyw.yywctl.bit.usebank2  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank2 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a0    = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a0 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a1    = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a1 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a2    = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a2 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a3    = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a3 ));
	Ddim_Print(( "yyw.yywctl.bit.usebanka  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebanka ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa00  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa00 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa10  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa10 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa01  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa01 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa11  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa11 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa02  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa02 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa12  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa12 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa03  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa03 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa13  = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa13 ));
	Ddim_Print(( "yyw.yywbank.bit.bankst   = %u\n",   ioR2yP1.yyw.yywbank.bit.bankst ));
	Ddim_Print(( "yyw.yywbank.bit.bank0ps  = %u\n",   ioR2yP1.yyw.yywbank.bit.bank0ps ));
	Ddim_Print(( "yyw.yywbank.bit.bank1ps  = %u\n",   ioR2yP1.yyw.yywbank.bit.bank1ps ));
	Ddim_Print(( "yyw.yywbank.bit.bank2ps  = %u\n",   ioR2yP1.yyw.yywbank.bit.bank2ps ));
	Ddim_Print(( "yyw.yywbank.bit.bankaps  = %u\n",   ioR2yP1.yyw.yywbank.bit.bankaps ));
	Ddim_Print(( "yyw.yywbank.bit.bank0sts = %u\n",   ioR2yP1.yyw.yywbank.bit.bank0sts ));
	Ddim_Print(( "yyw.yywbank.bit.bank1sts = %u\n",   ioR2yP1.yyw.yywbank.bit.bank1sts ));
	Ddim_Print(( "yyw.yywbank.bit.bank2sts = %u\n",   ioR2yP1.yyw.yywbank.bit.bank2sts ));
	Ddim_Print(( "yyw.yywbank.bit.bankasts = %u\n",   ioR2yP1.yyw.yywbank.bit.bankasts ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "yyw.yywctl.bit.usebank0  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank0 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a00  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a00 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a10  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a10 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a20  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a20 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a01  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a01 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a11  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a11 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a21  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a21 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a02  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a02 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a12  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a12 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a22  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a22 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a03  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a03 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a13  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a13 ));
	Ddim_Print(( "yyw.yyw0a.bit.yyw0a23  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a23 ));
	Ddim_Print(( "yyw.yywctl.bit.usebank1  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank1 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a00  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a00 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a10  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a10 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a20  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a20 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a01  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a01 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a11  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a11 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a21  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a21 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a02  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a02 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a12  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a12 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a22  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a22 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a03  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a03 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a13  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a13 ));
	Ddim_Print(( "yyw.yyw1a.bit.yyw1a23  = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a23 ));
	Ddim_Print(( "yyw.yywctl.bit.usebank2  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank2 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a0    = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a0 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a1    = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a1 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a2    = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a2 ));
	Ddim_Print(( "yyw.yyw2a.bit.yyw2a3    = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a3 ));
	Ddim_Print(( "yyw.yywctl.bit.usebanka  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebanka ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa00  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa00 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa10  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa10 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa01  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa01 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa11  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa11 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa02  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa02 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa12  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa12 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa03  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa03 ));
	Ddim_Print(( "yyw.yywaa.bit.yywaa13  = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa13 ));
	Ddim_Print(( "yyw.yywbank.bit.bankst   = %u\n",   ioR2yP2.yyw.yywbank.bit.bankst ));
	Ddim_Print(( "yyw.yywbank.bit.bank0ps  = %u\n",   ioR2yP2.yyw.yywbank.bit.bank0ps ));
	Ddim_Print(( "yyw.yywbank.bit.bank1ps  = %u\n",   ioR2yP2.yyw.yywbank.bit.bank1ps ));
	Ddim_Print(( "yyw.yywbank.bit.bank2ps  = %u\n",   ioR2yP2.yyw.yywbank.bit.bank2ps ));
	Ddim_Print(( "yyw.yywbank.bit.bankaps  = %u\n",   ioR2yP2.yyw.yywbank.bit.bankaps ));
	Ddim_Print(( "yyw.yywbank.bit.bank0sts = %u\n",   ioR2yP2.yyw.yywbank.bit.bank0sts ));
	Ddim_Print(( "yyw.yywbank.bit.bank1sts = %u\n",   ioR2yP2.yyw.yywbank.bit.bank1sts ));
	Ddim_Print(( "yyw.yywbank.bit.bank2sts = %u\n",   ioR2yP2.yyw.yywbank.bit.bank2sts ));
	Ddim_Print(( "yyw.yywbank.bit.bankasts = %u\n",   ioR2yP2.yyw.yywbank.bit.bankasts ));
	im_r2y_clk_off_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
}

VOID ct_im_r2y_classb_print_fr2y_ctrl_reg( CtImR2yClassb * self )
{
	im_r2y_clk_on_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "(fR2y)\n" ));
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( "fR2y.CNTL.CNTL.bit.TRG = %u\n",    ioR2yP1.fR2y.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "fR2y.CNTL.R2YFLAG      = 0x%lx\n", ioR2yP1.fR2y.CNTL.R2YFLAG.word ));
	Ddim_Print(( "fR2y.CNTL.R2YINTE      = 0x%lx\n", ioR2yP1.fR2y.CNTL.R2YINTE.word ));
	Ddim_Print(( "fR2y.CNTL.R2YINTF      = 0x%lx\n", ioR2yP1.fR2y.CNTL.R2YINTF.word ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "fR2y.CNTL.CNTL.bit.TRG = %u\n",    ioR2yP2.fR2y.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "fR2y.CNTL.R2YFLAG      = 0x%lx\n", ioR2yP2.fR2y.CNTL.R2YFLAG.word ));
	Ddim_Print(( "fR2y.CNTL.R2YINTE      = 0x%lx\n", ioR2yP2.fR2y.CNTL.R2YINTE.word ));
	Ddim_Print(( "fR2y.CNTL.R2YINTF      = 0x%lx\n", ioR2yP2.fR2y.CNTL.R2YINTF.word ));
	im_r2y_clk_off_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
}


VOID ct_im_r2y_classb_print_axi_reg( CtImR2yClassb * self )
{
	im_r2y_clk_on_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
	Ddim_Print(( "\n" ));
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_0   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_0 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_0    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_0 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_1   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_1 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_1    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_1 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_2   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_2 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_2    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_2 ));

	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_0 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_0 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_0  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_0 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_1 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_1 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_1  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_1 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_2 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_2 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_2  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_2 ));

	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWACACHE_0 = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWACACHE_0 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWAPROT_0  = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWAPROT_0 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWACACHE_1 = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWACACHE_1 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWAPROT_1  = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWAPROT_1 ));

	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_0 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_0 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_0  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_0 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_1 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_1 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_1  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_1 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_2 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_2 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_2  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_2 ));

	Ddim_Print(( "yych.YYW2AXCTL.bit.YYW2CACHE   = %u\n", ioR2yP1.yych.YYW2AXCTL.bit.YYW2CACHE ));
	Ddim_Print(( "yych.YYW2AXCTL.bit.YYW2PROT    = %u\n", ioR2yP1.yych.YYW2AXCTL.bit.YYW2PROT ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_0   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_0 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_0    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_0 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_1   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_1 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_1    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_1 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRCACHE_2   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_2 ));
	Ddim_Print(( "yych.YYRAXCTL.bit.YYRPROT_2    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_2 ));

	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_0 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_0 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_0  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_0 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_1 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_1 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_1  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_1 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0CACHE_2 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_2 ));
	Ddim_Print(( "yych.YYW0AXCTL.bit.YYW0PROT_2  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_2 ));

	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWACACHE_0 = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWACACHE_0 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWAPROT_0  = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWAPROT_0 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWACACHE_1 = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWACACHE_1 ));
	Ddim_Print(( "yych.YYWAAXCTL.bit.YYWAPROT_1  = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWAPROT_1 ));

	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_0 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_0 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_0  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_0 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_1 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_1 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_1  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_1 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1CACHE_2 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_2 ));
	Ddim_Print(( "yych.YYW1AXCTL.bit.YYW1PROT_2  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_2 ));

	Ddim_Print(( "yych.YYW2AXCTL.bit.YYW2CACHE   = %u\n", ioR2yP2.yych.YYW2AXCTL.bit.YYW2CACHE ));
	Ddim_Print(( "yych.YYW2AXCTL.bit.YYW2PROT    = %u\n", ioR2yP2.yych.YYW2AXCTL.bit.YYW2PROT ));
	im_r2y_clk_off_pclk(self->imR2yClk, D_IM_R2Y_PIPE12 );
}

VOID ct_im_r2y_classb_printreg( CtImR2yClassb * self )
{
	ct_im_r2y_classa_print_r2y_common_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyr_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_yyw_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassaself->ctImR2yClassa);
	ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassaself->ctImR2yClassa);
	ct_im_r2y_classa_print_resize_rect_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_trimming_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_color_extract_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_chroma_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_hue_scale_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_hist_reg(self->ctImR2yClassa);
	ct_im_r2y_classa_print_post_resize_edge0_reg(self->ctImR2yClassa);
	ct_im_r2y_classb_print_post_resize_edge1_reg(self->ctImR2yClassb);
	ct_im_classb_r2y_print_other_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_fr2y_ctrl_reg(self->ctImR2yClassb);
	ct_im_r2y_classb_print_axi_reg(self->ctImR2yClassb);

#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print(( "R2Y End Status\n" ));
	im_r2y_stat_print_status(self->imR2yStat);
	im_r2y_stat_print_clock_status(self->imR2yStat);
	im_r2y_stat_print_acc_en_status(self->imR2yStat);
#endif
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_1: "
INT32 ct_im_r2y_classb_1_1( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	return im_r2y_init(self->imR2y, pipeNo );
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_2: "
INT32 ct_im_r2y_classb_1_2( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_3: "
INT32 ct_im_r2y_classb_1_3( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_4: "
INT32 ct_im_r2y_classb_1_4(CtImR2yClassb * self, UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Force_Off_Pclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_5: "
INT32 ct_im_r2y_classb_1_5(CtImR2yClassb * self, UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_On_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Off_Hclk( pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_6: "
INT32 ct_im_r2y_classb_1_6( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	Im_R2Y_On_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Off_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_7: "
INT32 ct_im_r2y_classb_1_7(CtImR2yClassb * self, UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_On_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_On_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_On_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Force_Off_Hclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_8: "
INT32 ct_im_r2y_classb_1_8(CtImR2yClassb * self, UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_off_iclk(self->imR2yClk, pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_9: "
INT32 ct_im_r2y_classb_1_9( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	im_r2y_clk_on_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif


	im_r2y_clk_off_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_10: "
INT32 ct_im_r2y_classb_1_10( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_iclk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Force_Off_Iclk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_11: "
INT32 ct_im_r2y_classb_1_11( CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_off_clk(self->imR2yClk, pipeNo );

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_12: "
INT32 ct_im_r2y_classb_1_12(CtImR2yClassb * self, UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	im_r2y_clk_on_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_off_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_13: "
INT32 ct_im_r2y_classb_1_13(CtImR2yClassb * self,UCHAR pipeNo )
{
	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	im_r2y_clk_on_clk(self->imR2yClk, pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	Im_R2Y_Force_Off_Clk( pipeNo );
#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_clock_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classb_1_14: "
INT32 ct_im_r2y_classb_1_14(CtImR2yClassb * self, UCHAR pipeNo )
{
	UINT32				loopcnt;
	TImR2yCtrlAxi	r2yCtrlAxi[] = {
		[0] = {	// max
			.yyr[0].cacheType = 0xF,
			.yyr[0].protectType = 7,
			.yyr[1].cacheType = 0xF,
			.yyr[1].protectType = 7,
			.yyr[2].cacheType = 0xF,
			.yyr[2].protectType = 7,
			.yyw[0][0].cacheType = 0xF,
			.yyw[0][0].protectType = 7,
			.yyw[0][1].cacheType = 0xF,
			.yyw[0][1].protectType = 7,
			.yyw[0][2].cacheType = 0xF,
			.yyw[0][2].protectType = 7,
			.yyw[1][0].cacheType = 0xF,
			.yyw[1][0].protectType = 7,
			.yyw[1][1].cacheType = 0xF,
			.yyw[1][1].protectType = 7,
			.yyw[1][2].cacheType = 0xF,
			.yyw[1][2].protectType = 7,
			.yyw[2][0].cacheType = 0xF,
			.yyw[2][0].protectType = 7,
			.yyw[3][0].cacheType = 0xF,
			.yyw[3][0].protectType = 7,
			.yyw[3][1].cacheType = 0xF,
			.yyw[3][1].protectType = 7,
		},
		[1] = {	// min
			.yyr[0].cacheType = 0,
			.yyr[0].protectType = 0,
			.yyr[1].cacheType = 0,
			.yyr[1].protectType = 0,
			.yyr[2].cacheType = 0,
			.yyr[2].protectType = 0,
			.yyw[0][0].cacheType = 0,
			.yyw[0][0].protectType = 0,
			.yyw[0][1].cacheType = 0,
			.yyw[0][1].protectType = 0,
			.yyw[0][2].cacheType = 0,
			.yyw[0][2].protectType = 0,
			.yyw[1][0].cacheType = 0,
			.yyw[1][0].protectType = 0,
			.yyw[1][1].cacheType = 0,
			.yyw[1][1].protectType = 0,
			.yyw[1][2].cacheType = 0,
			.yyw[1][2].protectType = 0,
			.yyw[2][0].cacheType = 0,
			.yyw[2][0].protectType = 0,
			.yyw[3][0].cacheType = 0,
			.yyw[3][0].protectType = 0,
			.yyw[3][1].cacheType = 0,
			.yyw[3][1].protectType = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlAxi) / sizeof(r2yCtrlAxi[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl_axi(self->imR2y, pipeNo, &r2yCtrlAxi[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_ctrl_axi(self->imR2y, pipeNo, &r2yCtrlAxi[loopcnt] );
#endif

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_0   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_0 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_0    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_0 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_1   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_1 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_1    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_1 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_2   = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRCACHE_2 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_2    = %u\n", ioR2yP1.yych.YYRAXCTL.bit.YYRPROT_2 ));

		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_0 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_0 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_0  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_0 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_1 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_1 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_1  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_1 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_2 = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0CACHE_2 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_2  = %u\n", ioR2yP1.yych.YYW0AXCTL.bit.YYW0PROT_2 ));

		Ddim_Print(( "YYWAAXCTL.bit.YYWACACHE_0 = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWACACHE_0 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWAPROT_0  = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWAPROT_0 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWACACHE_1 = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWACACHE_1 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWAPROT_1  = %u\n", ioR2yP1.yych.YYWAAXCTL.bit.YYWAPROT_1 ));

		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_0 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_0 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_0  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_0 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_1 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_1 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_1  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_1 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_2 = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1CACHE_2 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_2  = %u\n", ioR2yP1.yych.YYW1AXCTL.bit.YYW1PROT_2 ));

		Ddim_Print(( "YYW2AXCTL.bit.YYW2CACHE_0 = %u\n", ioR2yP1.yych.YYW2AXCTL.bit.YYW2CACHE ));
		Ddim_Print(( "YYW2AXCTL.bit.YYW2PROT_0  = %u\n", ioR2yP1.yych.YYW2AXCTL.bit.YYW2PROT ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_0   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_0 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_0    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_0 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_1   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_1 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_1    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_1 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRCACHE_2   = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRCACHE_2 ));
		Ddim_Print(( "YYRAXCTL.bit.YYRPROT_2    = %u\n", ioR2yP2.yych.YYRAXCTL.bit.YYRPROT_2 ));

		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_0 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_0 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_0  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_0 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_1 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_1 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_1  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_1 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0CACHE_2 = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0CACHE_2 ));
		Ddim_Print(( "YYW0AXCTL.bit.YYW0PROT_2  = %u\n", ioR2yP2.yych.YYW0AXCTL.bit.YYW0PROT_2 ));

		Ddim_Print(( "YYWAAXCTL.bit.YYWACACHE_0 = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWACACHE_0 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWAPROT_0  = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWAPROT_0 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWACACHE_1 = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWACACHE_1 ));
		Ddim_Print(( "YYWAAXCTL.bit.YYWAPROT_1  = %u\n", ioR2yP2.yych.YYWAAXCTL.bit.YYWAPROT_1 ));

		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_0 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_0 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_0  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_0 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_1 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_1 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_1  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_1 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1CACHE_2 = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1CACHE_2 ));
		Ddim_Print(( "YYW1AXCTL.bit.YYW1PROT_2  = %u\n", ioR2yP2.yych.YYW1AXCTL.bit.YYW1PROT_2 ));

		Ddim_Print(( "YYW2AXCTL.bit.YYW2CACHE_0 = %u\n", ioR2yP2.yych.YYW2AXCTL.bit.YYW2CACHE ));
		Ddim_Print(( "YYW2AXCTL.bit.YYW2PROT_0  = %u\n", ioR2yP2.yych.YYW2AXCTL.bit.YYW2PROT ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );
	}

	return D_DDIM_OK;
}


CtImR2yClassb* ct_im_r2y_classb_new(void)
{
	CtImR2yClassb* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSB, sizeof(CtImR2yClassbPrivate));

	return self;
}

CtImR2yClassb* ct_im_r2y_classb_get(void)
{
	static CtImR2yClassb* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSB, sizeof(CtImR2yClassbPrivate));
	}

	return self;
}
