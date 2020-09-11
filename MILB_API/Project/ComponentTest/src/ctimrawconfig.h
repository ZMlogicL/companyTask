/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRawConfig
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_RAW_CONFIG_H__
#define __CT_IM_RAW_CONFIG_H__


#include <klib.h>
#include <stdlib.h>
#include <string.h>

#include "jdsraw.h"
#include "im_raw.h"
#include "ctimraw.h"
#include "driver_common.h"


#define CT_TYPE_IM_RAW_CONFIG                  (ct_im_raw_config_get_type())
#define CT_IM_RAW_CONFIG(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRawConfig))
#define CT_IS_IM_RAW_CONFIG(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RAW_CONFIG))

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

// #define D_CT_IM_RAW_PT_TEST
#define CtImRawConfig_OK		(0)
#define CtImRawConfig_NG		(1)

#define CtImRawConfig_WIDTH	(1536)
#define CtImRawConfig_LINES		(1152)

#define CtImRawConfig_8_WIDTH	(640)
#define CtImRawConfig_8_LINES		(480)


typedef struct _CtImRawConfig CtImRawConfig;
typedef struct _CtImRawConfigPrivate CtImRawConfigPrivate;


struct _CtImRawConfig
{
	KObject parent;
};


KConstType 			ct_im_raw_config_get_type(void);
CtImRawConfig* 	ct_im_raw_config_new(void);

T_IM_RAW_CTRL_CODE_TBL ct_im_raw_config_get_code_tbl(CtImRawConfig *self);
T_IM_RAW_CTRL_PARAM		ct_im_raw_config_get_raw_param(CtImRawConfig *self);
kuchar					ct_im_raw_config_get_user_lut(CtImRawConfig *self);
kuint32 				ct_im_raw_config_get_enc_byte(CtImRawConfig *self);
void 					ct_im_raw_config_set_huff_tbl(CtImRawConfig* self);
void 					ct_im_raw_config_init_param(CtImRawConfig* self);
void 					ct_im_raw_config_invalid_code(CtImRawConfig* self);
void 					ct_im_raw_config_8bit_code_table(CtImRawConfig* self);
void 					ct_im_raw_config_setup_user_lut0(CtImRawConfig* self);
void 					ct_im_raw_config_setup_user_lut1(CtImRawConfig* self);
kint32 					ct_im_raw_config_verify_data_lut(CtImRawConfig* self,
		kuchar* addr1, kuchar* addr2, kuint32 byte);


#endif /* __CT_IM_RAW_CONFIG_H__ */
