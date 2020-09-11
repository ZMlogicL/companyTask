/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImPro81Slvs
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_8_1_SLVS_H__
#define __IM_PRO_8_1_SLVS_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_8_1_SLVS                  (im_pro_8_1_slvs_get_type())
#define IM_PRO_8_1_SLVS(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro81Slvs)) 
#define IM_IS_PRO_8_1_SLVS(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_8_1_SLVS)) 


typedef struct _ImPro81Slvs ImPro81Slvs;
typedef struct _ImPro81SlvsPrivate ImPro81SlvsPrivate;

struct _ImPro81Slvs 
{
	AbsImProPrint parent;
};


KConstType im_pro_8_1_slvs_get_type(void);
ImPro81Slvs* im_pro_8_1_slvs_new(void);
ImPro81Slvs* im_pro_8_1_slvs_get(void);


#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_8_1_slvs_common_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_normal_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_link_err_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_mac_err1_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_mac_err2_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_sen_vd_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);
void im_pro_8_1_slvs_pwch_cb(T_CALLBACK_ID* id, kulong result, kulong userParam);

void im_pro_8_1_slvs_init_combo_phy(ImPro81Slvs* self);
void im_pro_8_1_slvs_mode_change(ImPro81Slvs* self);
void im_pro_8_1_slvs_init(ImPro81Slvs* self);
void im_pro_8_1_slvs_raw_output(ImPro81Slvs* self);


#endif

#endif /* __IM_PRO_8_1_SLVS_H__ */
