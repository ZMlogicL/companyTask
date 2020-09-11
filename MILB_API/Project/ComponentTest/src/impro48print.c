/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro48Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro48print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro48Print, impro_4_8_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_8_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro48PrintPrivate, IMPRO_TYPE_4_8_PRINT))


struct _Impro48PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_8_print_constructor(Impro48Print *self)
{
	Impro48PrintPrivate *priv = IMPRO_4_8_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_8_print_destructor(Impro48Print *self)
{
	Impro48PrintPrivate *priv = IMPRO_4_8_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_4_8_print_0(Impro48Print *self,const char *string, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_MATRIX_LV_GATE *flckCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.bit.flmlucy != flckCtrl->flmlucy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmlucy  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.bit.flmlucy, flckCtrl->flmlucy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.bit.flmllcy != flckCtrl->flmllcy)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmllcy  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcy.bit.flmllcy, flckCtrl->flmllcy));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.bit.flmlucb != flckCtrl->flmlucb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmlucb  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.bit.flmlucb, flckCtrl->flmlucb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.bit.flmllcb != flckCtrl->flmllcb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmllcb  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcb.bit.flmllcb, flckCtrl->flmllcb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.bit.flmlucr != flckCtrl->flmlucr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmlucr  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.bit.flmlucr, flckCtrl->flmlucr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.bit.flmllcr != flckCtrl->flmllcr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmllcr  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmlcr.bit.flmllcr, flckCtrl->flmllcr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.bit.flmc00 != flckCtrl->flmc[0][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc00   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.bit.flmc00, flckCtrl->flmc[0][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.bit.flmc01 != flckCtrl->flmc[0][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc01   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc1.bit.flmc01, flckCtrl->flmc[0][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.bit.flmc02 != flckCtrl->flmc[0][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc02   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.bit.flmc02, flckCtrl->flmc[0][2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.bit.flmc10 != flckCtrl->flmc[1][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc10   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc2.bit.flmc10, flckCtrl->flmc[1][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.bit.flmc11 != flckCtrl->flmc[1][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc11   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.bit.flmc11, flckCtrl->flmc[1][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.bit.flmc12 != flckCtrl->flmc[1][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc12   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc3.bit.flmc12, flckCtrl->flmc[1][2]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.bit.flmc20 != flckCtrl->flmc[2][0])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc20   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.bit.flmc20, flckCtrl->flmc[2][0]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.bit.flmc21 != flckCtrl->flmc[2][1])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc21   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc4.bit.flmc21, flckCtrl->flmc[2][1]));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc5.bit.flmc22 != flckCtrl->flmc[2][2])
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_Matrix_Lv_Gate(%u) %s result:flmc22   0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc5.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flmc.flmc5.bit.flmc22, flckCtrl->flmc[2][2]));
    }
}

void im_pro_4_8_print_1(Impro48Print *self,const char *string, E_IM_PRO_AF_CH ch, T_IM_PRO_STAT_YK *histCtrl)
{
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykrr.bit.flykrr != histCtrl->ykr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_FLYK(%u) %s result:HFLCKWBGR  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykrr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykrr.bit.flykrr, histCtrl->ykr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgr.bit.flykgr != histCtrl->ykgr)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_FLYK(%u) %s result:HFLCKWBGG  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgr.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgr.bit.flykgr, histCtrl->ykgr));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgb.bit.flykgb != histCtrl->ykgb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_FLYK(%u) %s result:HFLCKWBGB  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykgb.bit.flykgb, histCtrl->ykgb));
    }
    
    if (((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykbb.bit.flykbb != histCtrl->ykb)
    {
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Set_FLYK(%u) %s result:HFLCKWBGB  0x%08lx(%d) in(%d)\n", 
        ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykbb.word, 
        ((AbsImProPrint*)self)->ioPro->stat.flck[ch].flykbb.bit.flykbb, histCtrl->ykb));
    }
}

void im_pro_4_8_print_2(Impro48Print *self,E_IM_PRO_FLCK_CH ch, kulong flckCtrl)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Get_FLCKData(%u) result:FLCKData  0x%08lx\n", ch, flckCtrl));
}

void im_pro_4_8_print_3(Impro48Print *self,E_IM_PRO_FLCK_CH ch, kulong flckCtrl)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_FLCK_Get_LastFLCKData(%u) result:FLCKData  0x%08lx\n", ch, flckCtrl));
}
#endif //CO_CT_IM_PRO_DISABLE

Impro48Print* impro_4_8_print_new(void)
{
	Impro48Print* self = k_object_new_with_private(IMPRO_TYPE_4_8_PRINT, sizeof(Impro48PrintPrivate));

	return self;
}

Impro48Print* impro_4_8_print_get(void)
{
	static Impro48Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_8_PRINT, sizeof(Impro48PrintPrivate));
	}

	return self;
}
