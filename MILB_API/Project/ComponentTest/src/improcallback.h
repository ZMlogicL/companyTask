/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImProCallback
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_CALLBACK_H__
#define __IM_PRO_CALLBACK_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_CALLBACK                  (im_pro_callback_get_type())
#define IM_PRO_CALLBACK(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImProCallback)) 
#define IM_IS_PRO_CALLBACK(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_CALLBACK)) 


typedef struct _ImProCallback ImProCallback;
typedef struct _ImProCallbackPrivate ImProCallbackPrivate;

struct _ImProCallback 
{
	KObject parent;
};


KConstType im_pro_callback_get_type(void);
ImProCallback* im_pro_callback_new(void);
ImProCallback* im_pro_callback_get(void);
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_callback_sen_vd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_hd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_slvs_common_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_slvs_intn_o_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_slvs_link_err_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_slvs_mac_err1_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_slvs_mac_err2_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_lvds_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_dmipi_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_cmipi_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_moni_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_ldiv_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_obd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_obt_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sen_pwch_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_prch_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sro_vd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sro_hd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_sro_sdc_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_b2b_vd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_b2b_hd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_stat_aeawb_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_stat_af_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_stat_hist_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_pas_vd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
void im_pro_callback_pas_hd_int_cb( T_CALLBACK_ID* cbId, kulong result, kulong userParam );
#endif

#endif /* __IM_PRO_CALLBACK_H__ */
