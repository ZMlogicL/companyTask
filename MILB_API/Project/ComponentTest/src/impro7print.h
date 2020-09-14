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
void im_pro_7_print_15(ImPro7Print *self, kint32 ercd, TImProIntSentopCtrl* intCtrl, kuchar permissionFlg );
void im_pro_7_print_16(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_SG_CTRL* intCtrl, kuchar permissionFlg, kuchar vhdeg );
void im_pro_7_print_17(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_GYRO_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_18(ImPro7Print *self, const char* string, kuchar blockNum, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_print_19(ImPro7Print *self, const char* string, kuchar blockNum, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_print_20(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_21(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_22(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_30(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_31(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_32(ImPro7Print *self, kint32 ercd, E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_33(ImPro7Print *self, const char* string, E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_34(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_LVDS_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_35(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_36(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_37(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_38(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CMIPI_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_39(ImPro7Print *self, const char* string, kuchar ch, kuchar cate, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_40(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_41(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_42(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_43(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_44(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_45(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_46(ImPro7Print *self, kint32 ercd, kuchar ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_47(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_48(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_SROTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_49(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_print_50(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_51(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_print_52(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_print_59(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_60(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kint32 ercd, 
							TImProCallbackCfg* intCtrl );
void im_pro_7_print_61(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_INT_B2BTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_62(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, kuchar ch, kint32 ercd, 
							T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_print_64(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_print_65(ImPro7Print *self, const char* string, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, TImProCallbackCfg* intCtrl );
void im_pro_7_print_72(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_STATTOP_CTRL* intCtrl );
void im_pro_7_print_74(ImPro7Print *self, kint32 ercd, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_75(ImPro7Print *self, const char* string, E_IM_PRO_AEAWB_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_76(ImPro7Print *self, kint32 ercd, E_IM_PRO_AF_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_77(ImPro7Print *self, const char* string, E_IM_PRO_AF_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_78(ImPro7Print *self, kint32 ercd, E_IM_PRO_HIST_CH ch, T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_79(ImPro7Print *self, const char* string, E_IM_PRO_HIST_CH ch, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_80(ImPro7Print *self, kint32 ercd, T_IM_PRO_INT_PASTOP_CTRL* intCtrl, kuchar permissionFlg );
void im_pro_7_print_81(ImPro7Print *self, const char* string, kuchar ch, kint32 ercd, T_IM_PRO_INT_VHD_DELAY_CTRL* intCtrl );
void im_pro_7_print_83(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_84(ImPro7Print *self, const char* string, kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_88(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_89(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );
void im_pro_7_print_90(ImPro7Print *self, kint32 ercd, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							T_IM_PRO_INT_CFG* intCtrl, kuchar permissionFlg );
void im_pro_7_print_91(ImPro7Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_BLOCK_TYPE blockType, kuchar ch, 
							kint32 ercd, TImProCallbackCfg* intCtrl );

#endif

#endif /* __IM_PRO_7_PRINT_H__ */
