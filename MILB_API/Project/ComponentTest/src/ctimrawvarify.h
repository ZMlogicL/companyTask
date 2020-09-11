/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈元
*@brief : CtImRawVarify
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_RAW_VARIFY_H__
#define __CT_IM_RAW_VARIFY_H__


#include <klib.h>


#define CT_TYPE_IM_RAW_VARIFY                  (ct_im_raw_varify_get_type())
#define CT_IM_RAW_VARIFY(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRawVarify))
#define CT_IS_IM_RAW_VARIFY(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RAW_VARIFY))


typedef struct _CtImRawVarify CtImRawVarify;
typedef struct _CtImRawVarifyPrivate CtImRawVarifyPrivate;


typedef struct {
	kint32 retval;
	kuint32 cond;
	kuint32 byte;
	kuint16 width;
	kuint16 lines;
	kuint16 bitMode;
} EncResult;

typedef struct {
	kuint16* addr1;
	kuint16* addr2;
	kuint32 byte;
	kuchar bitsel;
}RawData;

struct _CtImRawVarify
{
	KObject parent;
};


KConstType 			ct_im_raw_varify_get_type(void);
CtImRawVarify* 	ct_im_raw_varify_new(void);

kint32 					ct_im_raw_varify_check_retval(CtImRawVarify* self, kint32 retval, kint32 correct);
void 					ct_im_raw_varify_ret_print(CtImRawVarify* self, kint32 retVal);

#if 0
#ifndef CO_DEBUG_ON_PC
void 					ct_im_raw_config_clear(CtImRawVarify* self);
#endif	// CO_DEBUG_ON_PC
#endif

void 					ct_im_raw_varify_dump_reg(CtImRawVarify* self);
void 					ct_im_raw_varify_enc_result(CtImRawVarify* self, EncResult encResult);
kint32 					ct_im_raw_varify_raw(CtImRawVarify* self, RawData rawData);
kint32 					ct_im_raw_varify_raw_12bit_pack(CtImRawVarify* self, kuint16* addr1, kuchar* addr2, kuint32 byte);
kint32 					ct_im_raw_varify_data(CtImRawVarify* self, kuchar* addr1, kuchar* addr2, kuint32 byte);
kint32 					ct_im_raw_varify_test_init(CtImRawVarify* self);

#endif /* __CT_IM_RAW_VARIFY_H__ */
