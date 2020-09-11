/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : ImPro7Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_7_PRINT_H__
#define __IM_PRO_7_PRINT_H__


#include <klib.h>
#include "absimproprint.h"


#define IM_TYPE_PRO_7_PRINT                  (im_pro_7_print_getType())
#define IM_PRO_7_PRINT(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImPro7Print)) 
#define IM_IS_PRO_7_PRINT(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_7_PRINT)) 


typedef struct _ImPro7Print ImPro7Print;
typedef struct _ImPro7PrintPrivate ImPro7PrintPrivate;

struct _ImPro7Print 
{
	AbsImProPrint parent;
};


KConstType im_pro_7_print_getType(void);
ImPro7Print* im_pro_7_print_new(void);
ImPro7Print* im_pro_7_print_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_7_15_Print(ImPro7Print *self, kint32 ercd, TImProIntSentopCtrl* intCtrl, kuchar permissionFlg );
void im_pro_7_16_Print(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_SG_CTRL* intCtrl, kuchar permissionFlg, kuchar vhdeg );
void im_pro_7_17_Print(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_GYRO_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_18_Print(ImPro7Print *self, const char* string, kuchar blockNum, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_19_Print(ImPro7Print *self, const char* string, kuchar blockNum, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_20_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_21_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_22_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_30_Print(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_31_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_32_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_33_Print(ImPro7Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_34_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_LVDS_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_35_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_36_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_37_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_38_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CMIPI_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_39_Print(ImPro7Print *self, const char* string, kuchar ch, kuchar cate, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_40_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_41_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_42_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_43_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_44_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_45_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_46_Print(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_47_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_48_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_SROTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_49_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_50_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_51_Print(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_52_Print(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_59_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_60_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
							TImProCallbackCfg* intCtrl );
void im_pro_7_61_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_B2BTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_62_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_64_Print(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_65_Print(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_72_Print(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_STATTOP_CTRL* intCtrl );
void im_pro_7_74_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_75_Print(ImPro7Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_76_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_AF_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_77_Print(ImPro7Print *self, const char* string, E_IM_PRO_AF_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_78_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_HIST_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_79_Print(ImPro7Print *self, const char* string, E_IM_PRO_HIST_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_80_Print(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_PASTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_81_Print(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_83_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_84_Print(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_88_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_89_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_90_Print(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_91_Print(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );

#endif

#endif /* __IM_PRO_7_PRINT_H__ */
