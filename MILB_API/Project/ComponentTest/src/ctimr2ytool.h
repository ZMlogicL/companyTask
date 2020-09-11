/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yTool
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_R2Y_TOOL_H__
#define __CT_IM_R2Y_TOOL_H__


#include <klib.h>
#include "ctimr2y.h"
#include "ct_im_r2y.h"
#include "ct_im_b2r.h"
#include "ct_im_ltm.h"

#include "im_r2y.h"
#include "im_b2r.h"

#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

#include "jdsr2y.h"
#include "jdsimg.h"

#include <stdlib.h>
#include <string.h>



#define CT_TYPE_IM_R2Y_TOOL                  (ct_im_r2y_tool_get_type())
#define CT_IM_R2Y_TOOL(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImR2yTool)) 
#define CT_IS_IM_R2Y_TOOL(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_R2Y_TOOL)) 

#ifdef CO_MSG_PRINT_ON
#define D_IM_R2Y_RESULT(statement)		result = statement
#else
#define D_IM_R2Y_RESULT
#endif



/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define CtImR2yTool_CHECK_TARGET_PIPE_NO_1(a)		(((a)+1) & (D_IM_R2Y_PIPE1+1))
#define CtImR2yTool_CHECK_TARGET_PIPE_NO_2(a)		(((a)+1) & (D_IM_R2Y_PIPE2+1))





typedef struct _CtImR2yTool CtImR2yTool;
typedef struct _CtImR2yToolPrivate CtImR2yToolPrivate;

struct _CtImR2yTool 
{
	KObject parent;
};



#ifdef D_IM_R2Y_DEBUG_ON_PC
extern volatile UCHAR gimR2yMacroFakeFinish[2];
#endif

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef IM_R2Y_STATUS_PRINT
extern VOID im_r2y_stat_print_status(self->imR2yStat VOID );
extern VOID im_r2y_stat_print_clock_status(self->imR2yStat VOID );
extern VOID im_r2y_stat_print_acc_en_status(self->imR2yStat VOID );
#endif

extern ULONG gctImR2yInAddr;
extern ULONG gctImR2yOutAddr[2];
extern TImR2yCtrl gctImR2yCtrl[];
extern TImR2yCtrlSdramInput gctImR2yCtrlSdramIn[];
extern TImR2yCtrl gctImR2yCtrlBase;
extern TImR2yCtrlSdramInput gctImR2yCtrlSdramInBase;
extern TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb8bit;
extern TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb12bit;
extern TImR2yCtrlSdramInput gctImR2yCtrlSdramInRgb16bit;
extern TImR2yResizeRect gctImR2yResizeRectParamOutYcc444;
extern TImR2yResizeRect gctImR2yResizeRectParamOutYcc422;
extern TImR2yResizeRect gctImR2yResizeRectParamOutYcc420;
extern TImR2yInaddrInfo gctImR2yInAddrRgb8bit;
extern TImR2yInaddrInfo gctImR2yInAddrRgb12bit;
extern TImR2yInaddrInfo gctImR2yInAddrRgb16bit;
extern TImR2yCtrlDirect gctImR2yCtrlDirect;
extern TImR2yOutbankInfo gctImR2yOutAddrYcc444;
extern TImR2yOutbankInfo gctImR2yOutAddrYcc422;
extern TImR2yOutbankInfo gctImR2yOutAddrYcc420;
extern const USHORT gctImR2yRgbDekneeTbl[D_IM_R2Y_TABLE_MAX_RGB_DEKNEE];
extern const USHORT gctImLtmYlogTbl[D_IM_LTM_TABLE_MAX_YLOG];











KConstType ct_im_r2y_tool_get_type(void);
CtImR2yTool* ct_im_r2y_tool_new(void);
CtImR2yTool* ct_im_r2y_tool_get(void);


#endif /* __CT_IM_R2Y_TOOL_H__ */
