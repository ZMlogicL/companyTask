/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImHdmi2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_HDMI2_H__
#define __CT_IM_HDMI2_H__


#include <klib.h>


#define CT_TYPE_IM_HDMI2                  (ct_im_hdmi2_get_type())
#define CT_IM_HDMI2(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImHdmi2)) 
#define CT_IS_IM_HDMI2(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_HDMI2)) 


typedef struct _CtImHdmi2 CtImHdmi2;
typedef struct _CtImHdmi2Private CtImHdmi2Private;

struct _CtImHdmi2 
{
	KObject parent;
};


KConstType ct_im_hdmi2_get_type(void);
CtImHdmi2* ct_im_hdmi2_new(void);
CtImHdmi2* ct_im_hdmi2_get(void);


VOID ct_im_hdmi2_printf1();
VOID ct_im_hdmi2_printf2();
VOID ct_im_hdmi2_printf3();
VOID ct_im_hdmi2_printf4();
VOID ct_im_hdmi2_printf5();
VOID ct_im_hdmi2_printf6();
VOID ct_im_hdmi2_printf7();
VOID ct_im_hdmi2_printf8();
VOID ct_im_hdmi2_printf9();
VOID ct_im_hdmi2_printf10();
VOID ct_im_hdmi2_printf11();
VOID ct_im_hdmi2_printf12();
VOID ct_im_hdmi2_printf13();
VOID ct_im_hdmi2_printf14();
VOID ct_im_hdmi2_printf15();


#endif /* __CT_IM_HDMI2_H__ */
