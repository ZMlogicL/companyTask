/*
 * imxch1.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#ifndef __IM_XCH1_H__
#define __IM_XCH1_H__

#include <klib.h>
#include "imxch.h"


#define IM_TYPE_XCH1      (im_xch1_get_type())
#define IM_XCH1(obj)        (K_TYPE_CHECK_INSTANCE_CAST(obj, ImXch1))
#define IM_IS_XCH1(obj)  (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_XCH1))

typedef struct _ImXch1  ImXch1;
typedef struct _ImXch1Private ImXch1Private;



struct _ImXch1 {
KObject parent;
};


KConstType  im_xch1_get_type(void);
ImXch1* im_xch1_new(void);

INT32 Im_Xch_Ctrl_Common( E_IM_XCH_CH_SEL xch, ImXchCtrlCmn* xch_ctrl_cmn );
INT32 Im_Xch_Ctrl_Thin( E_IM_XCH_CH_SEL xch, ImXchCtrlThin* xch_ctrl_thin );
INT32 Im_Xch_Ctrl_Hist( E_IM_XCH_CH_SEL xch, ImXchCtrlHist* xch_ctrl_hist );
INT32 Im_Xch_Ctrl_Half_Thin( E_IM_XCH_CH_SEL xch, ImXchCtrlHalfThin* xch_ctrl_half_thin );
INT32 Im_Xch_Ctrl_Copy( E_IM_XCH_CH_SEL xch, ImXchCtrlCopy* xch_ctrl_copy );
INT32 Im_Xch_Ctrl_Fill( E_IM_XCH_CH_SEL xch, UCHAR fill_data );
UCHAR Im_Xch_Get_Histogram_Max( VOID );
INT32 Im_Xch_Get_Ctrl_Common( E_IM_XCH_CH_SEL xch, ImXchCtrlCmn* xch_ctrl_cmn );
INT32 Im_Xch_Get_Ctrl_Thin( E_IM_XCH_CH_SEL xch, ImXchCtrlThin* xch_ctrl_thin );
INT32 Im_Xch_Get_Ctrl_Hist( E_IM_XCH_CH_SEL xch, ImXchCtrlHist* xch_ctrl_hist );
INT32 Im_Xch_Get_Ctrl_Half_Thin( E_IM_XCH_CH_SEL xch, ImXchCtrlHalfThin* xch_ctrl_half_thin );
INT32 Im_Xch_Get_Ctrl_Copy( E_IM_XCH_CH_SEL xch, ImXchCtrlCopy* xch_ctrl_copy );
INT32 Im_Xch_Get_Ctrl_Fill( E_IM_XCH_CH_SEL xch, UCHAR* fill_data );
INT32 Im_Xch_Get_Xtrg( E_IM_XCH_CH_SEL xch, E_IM_XCH_ST* status );;

#endif /* __IM_XCH1_H__ */
