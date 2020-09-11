/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro27Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IMPRO_2_7_PRINT_H__
#define __IMPRO_2_7_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IMPRO_TYPE_2_7_PRINT                  (impro_2_7_print_get_type())
#define IMPRO_2_7_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, Impro27Print)) 
#define IMPRO_IS_2_7_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_2_7_PRINT)) 


typedef struct _Impro27Print Impro27Print;
typedef struct _Impro27PrintPrivate Impro27PrintPrivate;

struct _Impro27Print 
{
	AbsImProPrint parent;
};


KConstType impro_2_7_print_get_type(void);
Impro27Print* impro_2_7_print_new(void);
Impro27Print* impro_2_7_print_get(void);

#ifndef CO_CT_IM_PRO_DISABL

void 			im_pro_2_7_print_0(Impro27Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
									E_IM_PRO_SDC_GAIN_TABLE_SEL sdcCtrl);
void 			im_pro_2_7_print_1(Impro27Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
									T_IM_PRO_SDC_CTRL_AFPB* sdcCtrl);
void 			im_pro_2_7_print_2(Impro27Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
									E_IM_PRO_SDC_GAIN_TABLE_SEL tblSel, kint32 ercd, T_IM_PRO_SDC_GAIN_TABLE* sdcCtrl, kint32 cmpErcd);
void 			im_pro_2_7_print_3(Impro27Print *self,E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, kuchar paenTrg);
void 			im_pro_2_7_print_4(Impro27Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
									const T_IM_PRO_RDMA_SDC_ADDR** sdcCtrl);
void 			im_pro_2_7_print_5(Impro27Print *self,const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
									E_IM_PRO_SDC_GAIN_TABLE_SEL tblSel, kint32 ercd, const T_IM_PRO_RDMA_SDC_GAIN_TBL_ADDR** sdcCtrl);
#endif /*CO_CT_IM_PRO_DISABL*/


#endif /* __IMPRO_2_7_PRINT_H__ */
