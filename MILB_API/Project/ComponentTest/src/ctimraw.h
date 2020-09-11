/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈元
*@brief : CtImRaw
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_RAW_H__
#define __CT_IM_RAW_H__


#include <klib.h>
#include "driver_common.h"


#define CT_TYPE_IM_RAW                  (ct_im_raw_get_type())
#define CT_IM_RAW(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImRaw))
#define CT_IS_IM_RAW(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_RAW))

#define CtImRaw_ORG_ADDR	(0x60000000)
#define CtImRaw_ENC_ADDR	(0x62000000)
#define CtImRaw_DEC_ADDR	(0x64000000)

// 4680(+24)
#define CtImRaw_INPUT_BAYER_0_WIDTH		(4704)
#define CtImRaw_INPUT_BAYER_0_LINES		(3500)
// 1536
#define CtImRaw_INPUT_BAYER_1_WIDTH		(1536)
#define CtImRaw_INPUT_BAYER_1_LINES		(1152)
// 2304
#define CtImRaw_INPUT_BAYER_2_WIDTH		(2304)
#define CtImRaw_INPUT_BAYER_2_LINES		(1296)
// 640
#define CtImRaw_INPUT_Y_0_WIDTH				(640)
#define CtImRaw_INPUT_Y_0_LINES					(480)

// 12bit-Pack
#define CtImRaw_INPUT_BAYER_0_SIZ		(CtImRaw_INPUT_BAYER_0_WIDTH * CtImRaw_INPUT_BAYER_0_LINES * 3 / 2)
// 16bit-NonPack
#define CtImRaw_INPUT_BAYER_1_SIZ		(CtImRaw_INPUT_BAYER_1_WIDTH * CtImRaw_INPUT_BAYER_1_WIDTH * 2)
// 16bit-NonPack
#define CtImRaw_INPUT_BAYER_2_SIZ		(CtImRaw_INPUT_BAYER_2_WIDTH * CtImRaw_INPUT_BAYER_2_LINES * 2)
// Y
#define CtImRaw_INPUT_Y_0_SIZ					(CtImRaw_INPUT_Y_0_WIDTH * CtImRaw_INPUT_Y_0_LINES)


typedef struct _CtImRaw CtImRaw;
typedef struct _CtImRawPrivate CtImRawPrivate;


struct _CtImRaw
{
	KObject parent;
};


KConstType 	ct_im_raw_get_type(void);
CtImRaw* 	ct_im_raw_new(void);

kuint32		ct_im_raw_get_enc_size(CtImRaw* self);
void 			ct_im_raw_main(CtImRaw* self, int argc, char** argv);

#ifdef CO_DEBUG_ON_PC
void			ct_im_raw_main_pc(CtImRaw* self, int argc, char** argv);
#endif // CO_DEBUG_ON_PC


#endif /* __CT_IM_RAW_H__ */
