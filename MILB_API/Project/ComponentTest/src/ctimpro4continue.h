/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈元
*@brief : CtImPro4Continue
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_PRO4_CONTINUE_H__
#define __CT_IM_PRO4_CONTINUE_H__


#include <klib.h>
#include "ctimprofile.h"
#include "impro4print.h"


#define CT_TYPE_IM_PRO4_CONTINUE                  (ct_im_pro4_continue_get_type())
#define CT_IM_PRO4_CONTINUE(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImPro4Continue)) 
#define CT_IS_IM_PRO4_CONTINUE(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_PRO4_CONTINUE)) 


typedef struct _CtImPro4Continue CtImPro4Continue;
typedef struct _CtImPro4ContinuePrivate CtImPro4ContinuePrivate;

struct _CtImPro4Continue 
{
	KObject parent;
};


KConstType 				ct_im_pro4_continue_get_type(void);
CtImPro4Continue* 	ct_im_pro4_continue_new(void);

#ifndef CO_CT_IM_PRO_DISABLE
void 						ct_im_pro4_continue_29(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_30(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_31(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_32(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_33(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_34(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_35(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_36(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_37(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_38(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_39(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_40(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_41(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_42(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_43(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_44(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_45(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_46(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_47(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_48(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_49(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_50(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_51(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_52(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_53(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_54(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_55(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_56(CtImPro4Continue* self, const kuint32 idx);
void 						ct_im_pro4_continue_57(CtImPro4Continue* self, const kuint32 idx);
#endif //CO_CT_IM_PRO_DISABLE


#endif /* __CT_IM_PRO4_CONTINUE_H__ */
