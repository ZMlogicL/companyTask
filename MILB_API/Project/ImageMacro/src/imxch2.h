/*
 * imxch2.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version:        1.0.0
*/

#ifndef __IM_XCH2_H__
#define __IM_XCH2_H__

#include <klib.h>
#include "imxch.h"


#define IM_TYPE_XCH2          (im_xch2_get_type())
#define IM_XCH2(obj)            (K_TYPE_CHECK_INSTANCE_CAST(obj, ImXch2))
#define IM_IS_XCH2(obj)      (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_XCH2))



typedef struct _ImXch2  ImXch2;
typedef struct _ImXch2Private ImXch2Private;

struct _ImXch2 {
KObject parent;
};


KConstType  im_xch2_get_type(void);
ImXch2* im_xch2_new(void);

#ifdef CO_DDIM_UTILITY_USE

INT32 im_xch2_conv_copy_param( ImXch2*self,ImXchCopyEx* copy_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlThin* xch_ctrl_thin, ImXchCtrlCopy* xch_ctrl_copy );
VOID im_xch2_conv_fill_param( ImXch2*self,ImXchFillEx* fill_param, ImXchCtrlCmn* xch_ctrl_cmn );
VOID im_xch2_conv_hist_param( ImXch2*self,ImXchExamineHist* hist_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlHist* xch_ctrl_hist );
INT32 im_xch2_conv_thin_param( ImXch2*self,ImXchConvThin* thin_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlThin* xch_ctrl_thin );
INT32 im_xch2_copy_dual_channel( ImXch2*self,VOID* dst_addr, VOID* src_addr, INT32 size );
INT32 im_xch2_copy( ImXch2*self,ImXchChSel xch, UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines );
INT32 im_xch2_copy_ex_sync( ImXch2*self,ImXchCopyEx* copy_param );
INT32 im_xch2_copy_ex_async( ImXch2*self,ImXchCopyEx* copy_param, VP_CALLBACK pCallBack );
INT32 im_xch2_examine_histogram_sync( ImXch2*self,ImXchExamineHist* hist_param, ULONG* hist_buffer, UCHAR* hist_max );
INT32 im_xch2_examine_histogram_async( ImXch2*self,ImXchExamineHist* hist_param, VP_CALLBACK pCallBack );
INT32 im_xch2_convert_thinning_sync( ImXch2*self,ImXchConvThin* thin_param );
INT32 im_xch2_convert_thinning_async( ImXch2*self,ImXchConvThin* thin_param, VP_CALLBACK pCallBack );

#endif	// CO_DDIM_UTILITY_USE

#endif /* __IM_XCH2_H__ */
