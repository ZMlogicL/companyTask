/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImHdmi1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_HDMI1_H__
#define __CT_IM_HDMI1_H__


#include <klib.h>


#define CT_TYPE_IM_HDMI1                  (ct_im_hdmi1_get_type())
#define CT_IM_HDMI1(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImHdmi1)) 
#define CT_IS_IM_HDMI1(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_HDMI1)) 


typedef struct _CtImHdmi1 CtImHdmi1;
typedef struct _CtImHdmi1Private CtImHdmi1Private;

struct _CtImHdmi1 
{
	KObject parent;
};


KConstType ct_im_hdmi1_get_type(void);
CtImHdmi1* ct_im_hdmi1_new(void);
CtImHdmi1* ct_im_hdmi1_get(void);


VOID ct_im_hdmi1_printf1();
VOID ct_im_hdmi1_printf2();
VOID ct_im_hdmi1_printf3();
VOID ct_im_hdmi1_printf4();
VOID ct_im_hdmi1_printf5();
VOID ct_im_hdmi1_printf6();
VOID ct_im_hdmi1_printf7();
VOID ct_im_hdmi1_printf8();
VOID ct_im_hdmi1_printf9();
VOID ct_im_hdmi1_printf10();
VOID ct_im_hdmi1_printf11();
VOID ct_im_hdmi1_printf12();
VOID ct_im_hdmi1_printf13();
VOID ct_im_hdmi1_printf14();
VOID ct_im_hdmi1_pcsim_test(VOID);


#endif /* __CT_IM_HDMI1_H__ */
