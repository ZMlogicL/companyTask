/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : ImPro5Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_5_PRINT_H__
#define __IM_PRO_5_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_5_PRINT                  (im_pro_5_print_get_type())
#define IM_PRO_5_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro5Print)) 
#define IM_IS_PRO_5_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_5_PRINT)) 


typedef struct _ImPro5Print ImPro5Print;
typedef struct _ImPro5PrintPrivate ImPro5PrintPrivate;

struct _ImPro5Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_5_print_get_type(void);
ImPro5Print* im_pro_5_print_new(void);
ImPro5Print* im_pro_5_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_5_print_4(ImPro5Print *self,const char* string, kint32 ercd );
void im_pro_5_print_5(ImPro5Print *self,kint32 ercd );
void im_pro_5_print_6(ImPro5Print *self,kint32 ercd, kuchar force );
void im_pro_5_print_7(ImPro5Print *self,const char* string, kint32 ercd, TimproSptCtrl* ctrl );
void im_pro_5_print_8(ImPro5Print *self,kint32 ercd, kuchar paenTrg );
void im_pro_5_print_9(ImPro5Print *self,const char* string, kint32 ercd, kint32 cmpErcd );
void im_pro_5_10_Print(ImPro5Print *self,EImProSptTblSel tblSel, kint32 ercd, const TimproRdmaSptShdTblAddr** addr );
#endif //CO_CT_IM_PRO_DISABLE

#endif /* __IM_PRO_5_PRINT_H__ */
