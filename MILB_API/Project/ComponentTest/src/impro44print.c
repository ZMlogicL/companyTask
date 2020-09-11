/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro44Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro44print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro44Print, impro_4_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_4_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro44PrintPrivate, IMPRO_TYPE_4_4_PRINT))


struct _Impro44PrintPrivate
{


};


/**
 *IMPL 
 */
static void impro_4_4_print_constructor(Impro44Print *self)
{
	Impro44PrintPrivate *priv = IMPRO_4_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_4_4_print_destructor(Impro44Print *self)
{
	Impro44PrintPrivate *priv = IMPRO_4_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC 
 */
#ifndef CO_CT_IM_PRO_DISABLE
Impro44Print* impro_4_4_print_new(void)
{
	Impro44Print* self = k_object_new_with_private(IMPRO_TYPE_4_4_PRINT, sizeof(Impro44PrintPrivate));

	return self;
}

void im_pro_4_4_print_0(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Eval_Calc_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_1(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Eval_Calc_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_2(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Max_Assess_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_3(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Min_Assess_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_4(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal0_Line_Accum_Max_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_5(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal1_Line_Accum_Max_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_6(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Horizontal2_Line_Accum_Max_Value(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_7(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Eval_Calc_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_8(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Bright_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}

void im_pro_4_4_print_9(Impro44Print *self,const char *string, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO winNo, kulong *calcData)
{
        DriverCommon_DDIM_PRINT(("Im_PRO_AF_Get_Dark_LastData(%u %u) %s result:last_addr(%lu)\n", 
        ch, winNo, string, *calcData));
}
#endif

Impro44Print* impro_4_4_print_get(void)
{
	static Impro44Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_4_4_PRINT, sizeof(Impro44PrintPrivate));
	}

	return self;
}
