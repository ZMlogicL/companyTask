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
	Ddim_Print(( "yyw.EE1CTL.bit.EE1EN          = 0x%x\n", ioR2yP1.yyw.EE1CTL.bit.EE1EN ));
	Ddim_Print(( "yyw.EE1CTL.bit.EE1TC          = 0x%x\n", ioR2yP1.yyw.EE1CTL.bit.EE1TC ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK0      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK0 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK1      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK1 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK2      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK2 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK3      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK3 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK4      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK4 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK5      = 0x%x\n", ioR2yP1.yyw.EE1HPFK.bit.EE1HPFK5 ));
	Ddim_Print(( "yyw.EE1NRLV.bit.EE1NRLV       = 0x%x\n", ioR2yP1.yyw.EE1NRLV.bit.EE1NRLV ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_0 = 0x%x\n", ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_0 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_1 = 0x%x\n", ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_1 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_2 = 0x%x\n", ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_2 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_3 = 0x%x\n", ioR2yP1.yyw.EE1CORPOF.bit.EE1CORPOF_3 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_0 = 0x%x\n", ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_0 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_1 = 0x%x\n", ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_1 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_2 = 0x%x\n", ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_2 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_3 = 0x%x\n", ioR2yP1.yyw.EE1CORPGA.bit.EE1CORPGA_3 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_1 = 0x%x\n", ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_1 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_2 = 0x%x\n", ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_2 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_3 = 0x%x\n", ioR2yP1.yyw.EE1CORPBD.bit.EE1CORPBD_3 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_0 = 0x%x\n", ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_0 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_1 = 0x%x\n", ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_1 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_2 = 0x%x\n", ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_2 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_3 = 0x%x\n", ioR2yP1.yyw.EE1CORMOF.bit.EE1CORMOF_3 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_0 = 0x%x\n", ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_0 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_1 = 0x%x\n", ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_1 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_2 = 0x%x\n", ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_2 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_3 = 0x%x\n", ioR2yP1.yyw.EE1CORMGA.bit.EE1CORMGA_3 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_1 = 0x%x\n", ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_1 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_2 = 0x%x\n", ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_2 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_3 = 0x%x\n", ioR2yP1.yyw.EE1CORMBD.bit.EE1CORMBD_3 ));
	Ddim_Print(( "yyw.EE1SCLSUP.bit.EE1SCLSUP   = 0x%x\n", ioR2yP1.yyw.EE1SCLSUP.bit.EE1SCLSUP ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_0 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_0 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_1 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_2 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_3 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_4 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_5 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_6 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_7 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_8 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLPOF.bit.EE1SCLPOF_9 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_0 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_0 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_1 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_2 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_3 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_4 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_5 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_6 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_7 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_8 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLPGA.bit.EE1SCLPGA_9 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_1 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_2 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_3 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_4 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_5 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_6 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_7 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_8 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLPBD.bit.EE1SCLPBD_9 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_0 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_0 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_1 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_2 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_3 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_4 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_5 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_6 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_7 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_8 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLMOF.bit.EE1SCLMOF_9 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_0 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_0 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_1 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_2 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_3 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_4 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_5 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_6 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_7 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_8 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLMGA.bit.EE1SCLMGA_9 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_1 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_1 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_2 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_2 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_3 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_3 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_4 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_4 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_5 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_5 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_6 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_6 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_7 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_7 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_8 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_8 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_9 = 0x%x\n", ioR2yP1.yyw.EE1SCLMBD.bit.EE1SCLMBD_9 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_0 = 0x%x\n", ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_0 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_1 = 0x%x\n", ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_1 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_2 = 0x%x\n", ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_2 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_3 = 0x%x\n", ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_3 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_4 = 0x%x\n", ioR2yP1.yyw.EE1TONPOF.bit.EE1TONPOF_4 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_0 = 0x%x\n", ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_0 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_1 = 0x%x\n", ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_1 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_2 = 0x%x\n", ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_2 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_3 = 0x%x\n", ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_3 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_4 = 0x%x\n", ioR2yP1.yyw.EE1TONPGA.bit.EE1TONPGA_4 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_1 = 0x%x\n", ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_1 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_2 = 0x%x\n", ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_2 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_3 = 0x%x\n", ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_3 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_4 = 0x%x\n", ioR2yP1.yyw.EE1TONPBD.bit.EE1TONPBD_4 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_0 = 0x%x\n", ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_0 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_1 = 0x%x\n", ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_1 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_2 = 0x%x\n", ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_2 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_3 = 0x%x\n", ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_3 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_4 = 0x%x\n", ioR2yP1.yyw.EE1TONMOF.bit.EE1TONMOF_4 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_0 = 0x%x\n", ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_0 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_1 = 0x%x\n", ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_1 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_2 = 0x%x\n", ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_2 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_3 = 0x%x\n", ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_3 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_4 = 0x%x\n", ioR2yP1.yyw.EE1TONMGA.bit.EE1TONMGA_4 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_1 = 0x%x\n", ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_1 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_2 = 0x%x\n", ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_2 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_3 = 0x%x\n", ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_3 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_4 = 0x%x\n", ioR2yP1.yyw.EE1TONMBD.bit.EE1TONMBD_4 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_0 = 0x%x\n", ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_0 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_1 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPPOF.bit.EE1CLPPOF_2 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_0 = 0x%x\n", ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_0 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_1 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPPGA.bit.EE1CLPPGA_2 ));
	Ddim_Print(( "yyw.EE1CLPPBD.bit.EE1CLPPBD_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPPBD.bit.EE1CLPPBD_1 ));
	Ddim_Print(( "yyw.EE1CLPPBD.bit.EE1CLPPBD_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPPBD.bit.EE1CLPPBD_2 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_0 = 0x%x\n", ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_0 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_1 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPMOF.bit.EE1CLPMOF_2 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_0 = 0x%x\n", ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_0 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_1 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPMGA.bit.EE1CLPMGA_2 ));
	Ddim_Print(( "yyw.EE1CLPMBD.bit.EE1CLPMBD_1 = 0x%x\n", ioR2yP1.yyw.EE1CLPMBD.bit.EE1CLPMBD_1 ));
	Ddim_Print(( "yyw.EE1CLPMBD.bit.EE1CLPMBD_2 = 0x%x\n", ioR2yP1.yyw.EE1CLPMBD.bit.EE1CLPMBD_2 ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "yyw.EE1CTL.bit.EE1EN          = 0x%x\n", ioR2yP2.yyw.EE1CTL.bit.EE1EN ));
	Ddim_Print(( "yyw.EE1CTL.bit.EE1TC          = 0x%x\n", ioR2yP2.yyw.EE1CTL.bit.EE1TC ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK0      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK0 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK1      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK1 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK2      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK2 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK3      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK3 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK4      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK4 ));
	Ddim_Print(( "yyw.EE1HPFK.bit.EE1HPFK5      = 0x%x\n", ioR2yP2.yyw.EE1HPFK.bit.EE1HPFK5 ));
	Ddim_Print(( "yyw.EE1NRLV.bit.EE1NRLV       = 0x%x\n", ioR2yP2.yyw.EE1NRLV.bit.EE1NRLV ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_0 = 0x%x\n", ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_0 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_1 = 0x%x\n", ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_1 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_2 = 0x%x\n", ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_2 ));
	Ddim_Print(( "yyw.EE1CORPOF.bit.EE1CORPOF_3 = 0x%x\n", ioR2yP2.yyw.EE1CORPOF.bit.EE1CORPOF_3 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_0 = 0x%x\n", ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_0 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_1 = 0x%x\n", ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_1 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_2 = 0x%x\n", ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_2 ));
	Ddim_Print(( "yyw.EE1CORPGA.bit.EE1CORPGA_3 = 0x%x\n", ioR2yP2.yyw.EE1CORPGA.bit.EE1CORPGA_3 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_1 = 0x%x\n", ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_1 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_2 = 0x%x\n", ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_2 ));
	Ddim_Print(( "yyw.EE1CORPBD.bit.EE1CORPBD_3 = 0x%x\n", ioR2yP2.yyw.EE1CORPBD.bit.EE1CORPBD_3 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_0 = 0x%x\n", ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_0 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_1 = 0x%x\n", ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_1 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_2 = 0x%x\n", ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_2 ));
	Ddim_Print(( "yyw.EE1CORMOF.bit.EE1CORMOF_3 = 0x%x\n", ioR2yP2.yyw.EE1CORMOF.bit.EE1CORMOF_3 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_0 = 0x%x\n", ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_0 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_1 = 0x%x\n", ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_1 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_2 = 0x%x\n", ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_2 ));
	Ddim_Print(( "yyw.EE1CORMGA.bit.EE1CORMGA_3 = 0x%x\n", ioR2yP2.yyw.EE1CORMGA.bit.EE1CORMGA_3 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_1 = 0x%x\n", ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_1 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_2 = 0x%x\n", ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_2 ));
	Ddim_Print(( "yyw.EE1CORMBD.bit.EE1CORMBD_3 = 0x%x\n", ioR2yP2.yyw.EE1CORMBD.bit.EE1CORMBD_3 ));
	Ddim_Print(( "yyw.EE1SCLSUP.bit.EE1SCLSUP   = 0x%x\n", ioR2yP2.yyw.EE1SCLSUP.bit.EE1SCLSUP ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_0 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_0 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_1 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_2 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_3 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_4 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_5 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_6 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_7 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_8 ));
	Ddim_Print(( "yyw.EE1SCLPOF.bit.EE1SCLPOF_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLPOF.bit.EE1SCLPOF_9 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_0 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_0 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_1 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_2 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_3 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_4 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_5 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_6 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_7 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_8 ));
	Ddim_Print(( "yyw.EE1SCLPGA.bit.EE1SCLPGA_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLPGA.bit.EE1SCLPGA_9 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_1 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_2 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_3 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_4 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_5 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_6 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_7 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_8 ));
	Ddim_Print(( "yyw.EE1SCLPBD.bit.EE1SCLPBD_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLPBD.bit.EE1SCLPBD_9 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_0 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_0 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_1 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_2 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_3 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_4 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_5 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_6 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_7 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_8 ));
	Ddim_Print(( "yyw.EE1SCLMOF.bit.EE1SCLMOF_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLMOF.bit.EE1SCLMOF_9 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_0 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_0 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_1 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_2 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_3 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_4 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_5 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_6 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_7 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_8 ));
	Ddim_Print(( "yyw.EE1SCLMGA.bit.EE1SCLMGA_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLMGA.bit.EE1SCLMGA_9 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_1 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_1 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_2 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_2 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_3 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_3 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_4 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_4 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_5 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_5 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_6 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_6 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_7 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_7 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_8 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_8 ));
	Ddim_Print(( "yyw.EE1SCLMBD.bit.EE1SCLMBD_9 = 0x%x\n", ioR2yP2.yyw.EE1SCLMBD.bit.EE1SCLMBD_9 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_0 = 0x%x\n", ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_0 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_1 = 0x%x\n", ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_1 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_2 = 0x%x\n", ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_2 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_3 = 0x%x\n", ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_3 ));
	Ddim_Print(( "yyw.EE1TONPOF.bit.EE1TONPOF_4 = 0x%x\n", ioR2yP2.yyw.EE1TONPOF.bit.EE1TONPOF_4 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_0 = 0x%x\n", ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_0 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_1 = 0x%x\n", ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_1 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_2 = 0x%x\n", ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_2 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_3 = 0x%x\n", ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_3 ));
	Ddim_Print(( "yyw.EE1TONPGA.bit.EE1TONPGA_4 = 0x%x\n", ioR2yP2.yyw.EE1TONPGA.bit.EE1TONPGA_4 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_1 = 0x%x\n", ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_1 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_2 = 0x%x\n", ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_2 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_3 = 0x%x\n", ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_3 ));
	Ddim_Print(( "yyw.EE1TONPBD.bit.EE1TONPBD_4 = 0x%x\n", ioR2yP2.yyw.EE1TONPBD.bit.EE1TONPBD_4 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_0 = 0x%x\n", ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_0 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_1 = 0x%x\n", ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_1 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_2 = 0x%x\n", ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_2 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_3 = 0x%x\n", ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_3 ));
	Ddim_Print(( "yyw.EE1TONMOF.bit.EE1TONMOF_4 = 0x%x\n", ioR2yP2.yyw.EE1TONMOF.bit.EE1TONMOF_4 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_0 = 0x%x\n", ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_0 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_1 = 0x%x\n", ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_1 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_2 = 0x%x\n", ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_2 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_3 = 0x%x\n", ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_3 ));
	Ddim_Print(( "yyw.EE1TONMGA.bit.EE1TONMGA_4 = 0x%x\n", ioR2yP2.yyw.EE1TONMGA.bit.EE1TONMGA_4 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_1 = 0x%x\n", ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_1 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_2 = 0x%x\n", ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_2 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_3 = 0x%x\n", ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_3 ));
	Ddim_Print(( "yyw.EE1TONMBD.bit.EE1TONMBD_4 = 0x%x\n", ioR2yP2.yyw.EE1TONMBD.bit.EE1TONMBD_4 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_0 = 0x%x\n", ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_0 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_1 ));
	Ddim_Print(( "yyw.EE1CLPPOF.bit.EE1CLPPOF_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPPOF.bit.EE1CLPPOF_2 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_0 = 0x%x\n", ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_0 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_1 ));
	Ddim_Print(( "yyw.EE1CLPPGA.bit.EE1CLPPGA_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPPGA.bit.EE1CLPPGA_2 ));
	Ddim_Print(( "yyw.EE1CLPPBD.bit.EE1CLPPBD_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPPBD.bit.EE1CLPPBD_1 ));
	Ddim_Print(( "yyw.EE1CLPPBD.bit.EE1CLPPBD_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPPBD.bit.EE1CLPPBD_2 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_0 = 0x%x\n", ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_0 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_1 ));
	Ddim_Print(( "yyw.EE1CLPMOF.bit.EE1CLPMOF_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPMOF.bit.EE1CLPMOF_2 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_0 = 0x%x\n", ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_0 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_1 ));
	Ddim_Print(( "yyw.EE1CLPMGA.bit.EE1CLPMGA_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPMGA.bit.EE1CLPMGA_2 ));
	Ddim_Print(( "yyw.EE1CLPMBD.bit.EE1CLPMBD_1 = 0x%x\n", ioR2yP2.yyw.EE1CLPMBD.bit.EE1CLPMBD_1 ));
	Ddim_Print(( "yyw.EE1CLPMBD.bit.EE1CLPMBD_2 = 0x%x\n", ioR2yP2.yyw.EE1CLPMBD.bit.EE1CLPMBD_2 ));
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
	Ddim_Print(( "(F_R2Y)\n" ));
	Ddim_Print(( "PIPE1\n" ));
	Ddim_Print(( "F_R2Y.CNTL.CNTL.bit.TRG = %u\n",    ioR2yP1.F_R2Y.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "F_R2Y.CNTL.R2YFLAG      = 0x%lx\n", ioR2yP1.F_R2Y.CNTL.R2YFLAG.word ));
	Ddim_Print(( "F_R2Y.CNTL.R2YINTE      = 0x%lx\n", ioR2yP1.F_R2Y.CNTL.R2YINTE.word ));
	Ddim_Print(( "F_R2Y.CNTL.R2YINTF      = 0x%lx\n", ioR2yP1.F_R2Y.CNTL.R2YINTF.word ));
	Ddim_Print(( "PIPE2\n" ));
	Ddim_Print(( "F_R2Y.CNTL.CNTL.bit.TRG = %u\n",    ioR2yP2.F_R2Y.CNTL.CNTL.bit.TRG ));
	Ddim_Print(( "F_R2Y.CNTL.R2YFLAG      = 0x%lx\n", ioR2yP2.F_R2Y.CNTL.R2YFLAG.word ));
	Ddim_Print(( "F_R2Y.CNTL.R2YINTE      = 0x%lx\n", ioR2yP2.F_R2Y.CNTL.R2YINTE.word ));
	Ddim_Print(( "F_R2Y.CNTL.R2YINTF      = 0x%lx\n", ioR2yP2.F_R2Y.CNTL.R2YINTF.word ));
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
