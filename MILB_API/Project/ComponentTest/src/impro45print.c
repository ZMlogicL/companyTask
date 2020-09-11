/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro45Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro45print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro45Print, impro_4_5_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_5_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro45PrintPrivate, IMPRO_TYPE_4_5_PRINT))


struct _Impro45PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_4_5_print_constructor(Impro45Print *self)
{
	Impro45PrintPrivate *priv = IMPRO_4_5_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_5_print_destructor(Impro45Print *self)
{
	Impro45PrintPrivate *priv = IMPRO_4_5_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_4_5_print_0(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void ct_im_pro_4_5_print_1(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_2(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_3(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Vertical_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_4(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Eval_Calc_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_5(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Eval_Calc_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_6(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Assess_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_7(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Assess_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_8(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_5_print_9(Impro45Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}
#endif

Impro45Print* impro_4_5_print_new(void)
{
	Impro45Print* self = k_object_new_with_private(IMPRO_TYPE_4_5_PRINT, sizeof(Impro45PrintPrivate));

	return self;
}

Impro45Print* impro_4_5_print_get(void)
{
	static Impro45Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_5_PRINT, sizeof(Impro45PrintPrivate));
	}

	return self;
}
