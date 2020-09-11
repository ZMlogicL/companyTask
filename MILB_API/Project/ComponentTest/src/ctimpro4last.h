/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro4Last
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO4_LAST_H__
#define __CT_IM_PRO4_LAST_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro4print.h"


#define CT_TYPE_IM_PRO4_LAST                  (ct_im_pro4_last_get_type())
#define CT_IM_PRO4_LAST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro4Last)) 
#define CT_IS_IM_PRO4_LAST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO4_LAST)) 


typedef struct _CtImPro4Last CtImPro4Last;
typedef struct _CtImPro4LastPrivate CtImPro4LastPrivate;

struct _CtImPro4Last 
{
	KObject parent;
};


KConstType 		ct_im_pro4_last_get_type(void);
CtImPro4Last* ct_im_pro4_last_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 				ct_im_pro4_last_58(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_59(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_60(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_61(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_62(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_63(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_64(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_65(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_66(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_67(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_68(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_69(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_70(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_71(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_72(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_73(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_74(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_75(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_76(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_77(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_78(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_79(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_80(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_81(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_82(CtImPro4Last* self, const kuint32 idx);
void 				ct_im_pro4_last_83(CtImPro4Last* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO4_LAST_H__ */
