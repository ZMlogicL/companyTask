/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro47Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro47print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro47Print, impro_4_7_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_7_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro47PrintPrivate, IMPRO_TYPE_4_7_PRINT))


struct _Impro47PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_7_print_constructor(Impro47Print *self)
{
	Impro47PrintPrivate *priv = IMPRO_4_7_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_7_print_destructor(Impro47Print *self)
{
	Impro47PrintPrivate *priv = IMPRO_4_7_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_7_print_0(Impro47Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_HIST_RAM_DATA *histCtrl)
{
    kulong loopCnt = 0;
    for (loopCnt = 0; loopCnt < 256; loopCnt++)
    {
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Ram(%u %lu) %s result:histrdata (%lu)\n", 
        ch, loopCnt, string, histCtrl->r[loopCnt]));
        }
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Ram(%u %lu) %s result:histgdata (%lu)\n", 
        ch, loopCnt, string, histCtrl->g[loopCnt]));
        }
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Ram(%u %lu) %s result:histbdata (%lu)\n", 
        ch, loopCnt, string, histCtrl->b[loopCnt]));
        }
        {
            DriverCommon_DDIM_PRINT(("Im_PRO_HIST_Get_HIST_Ram(%u %lu) %s result:histydata (%lu)\n", 
        ch, loopCnt, string, histCtrl->y[loopCnt]));
        }
    }
}

void im_pro_4_7_print_1(Impro47Print *self,E_IM_PRO_FLCK_CH ch)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Start(%u) result:fltrg    0x%08lx(%u)\n", 
        ch, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltrg.bit.fltrg));
}

void im_pro_4_7_print_2(Impro47Print *self,E_IM_PRO_FLCK_CH ch, kuchar force)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Stop(%u %u) result:fltrg  0x%08lx(%u)\n", 
        ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltrg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltrg.bit.fltrg));
}

void im_pro_4_7_print_3(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_CTRL *flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwpmd != flckCtrl->flckType)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Ctrl(%u) %s result:flwpmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwpmd, flckCtrl->flckType));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwlmd != flckCtrl->flckMode)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Ctrl(%u) %s result:flwlmd 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwlmd, flckCtrl->flckMode));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flcvw != flckCtrl->flcvw)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Ctrl(%u) %s result:flcvw  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flcvw, flckCtrl->flcvw));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.bit.flbc != flckCtrl->bcNum)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Ctrl(%u) %s result:flbc   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.bit.flbc, flckCtrl->bcNum));
    }
}

void im_pro_4_7_print_4(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_TYPE flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwpmd != flckCtrl)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_FLCKDataFormat(%u) %s result:flwpmd   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwpmd, flckCtrl));
    }
}

void im_pro_4_7_print_5(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_TYPE flckCtrl)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_WD_Mode(%u) %s result:flwlmd  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flckctl.bit.flwlmd, flckCtrl));
}

void im_pro_4_7_print_6(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_AREA *flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flh.bit.flh != flckCtrl->posX)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Area(%u) %s result:flh    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flh.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flh.bit.flh, flckCtrl->posX));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flv.bit.flv != flckCtrl->posY)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Area(%u) %s result:flv    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flv.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flv.bit.flv, flckCtrl->posY));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flhw.bit.flhw != flckCtrl->width)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Area(%u) %s result:flhw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flhw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flhw.bit.flhw, flckCtrl->width));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flvw != flckCtrl->lines)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Area(%u) %s result:flvw   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flvw, flckCtrl->lines));
    }
}

void im_pro_4_7_print_7(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, USHORT flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.bit.flbc != flckCtrl)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Blocks(%u) %s result:flbc 0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flbc.bit.flbc, flckCtrl));
    }
}

void im_pro_4_7_print_8(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, USHORT flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flcvw != flckCtrl)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_CW(%u) %s result:flcvw    0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flvw.bit.flcvw, flckCtrl));
    }
}

void im_pro_4_7_print_9(Impro47Print *self,const char *string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_LV_GATE *flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.bit.fltduy != flckCtrl->fltduy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltduy  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.bit.fltduy, flckCtrl->fltduy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.bit.fltdur != flckCtrl->fltdur)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdur  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.bit.fltdur, flckCtrl->fltdur));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.bit.fltdug != flckCtrl->fltdug)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdug  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.bit.fltdug, flckCtrl->fltdug));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.bit.fltdub != flckCtrl->fltdub)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdub  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.bit.fltdub, flckCtrl->fltdub));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.bit.fltdly != flckCtrl->fltdly)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdly  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdy.bit.fltdly, flckCtrl->fltdly));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.bit.fltdlr != flckCtrl->fltdlr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdlr  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdr.bit.fltdlr, flckCtrl->fltdlr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.bit.fltdlg != flckCtrl->fltdlg)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdlg  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdg.bit.fltdlg, flckCtrl->fltdlg));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.bit.fltdlb != flckCtrl->fltdlb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Lv_Gate(%u) %s result:fltdlb  0x%08lx(%u) in(%lu)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].fltdb.bit.fltdlb, flckCtrl->fltdlb));
    }
}
#endif

Impro47Print* impro_4_7_print_new(void)
{
	Impro47Print* self = k_object_new_with_private(IMPRO_TYPE_4_7_PRINT, sizeof(Impro47PrintPrivate));

	return self;
}

Impro47Print* impro_4_7_print_get(void)
{
	static Impro47Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_7_PRINT, sizeof(Impro47PrintPrivate));
	}

	return self;
}
