/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIipTool
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_TOOL_H__
#define __CT_IM_IIP_TOOL_H__


#include <klib.h>

// C Standard header
#include <string.h>
#include <stdlib.h>

#ifndef CO_CT_IM_IIP_DISABLE
#if 1
#include <stdio.h>
#endif
#endif //CO_CT_IM_IIP_DISABLE

// CT header
#include "ct_im_iip.h"
#include "ct_im_iip_b2y_frect_afn.h"
#include "ct_im_iip_afn.h"
#include "ct_im_iip_frect.h"
#include "ct_im_iip_lut.h"
#include "ct_im_iip_blend.h"
#include "ct_im_iip_csc.h"
#include "ct_im_iip_ld.h"
#include "ct_im_iip_flt.h"
#include "ct_im_iip_sl.h"
#include "ct_im_iip_mon.h"
#include "ct_im_iip_cfl.h"
#include "ct_im_iip_gpc.h"
#include "ct_im_iip_utility.h"
#include "ct_im_iip_mft.h"
// im_iip header
#include "im_iip.h"

// ### REMOVE_RELEASE BEGIN
#ifdef CO_PT_ENABLE
#include "palladium_test.h"
#include "palladium_test_common.h"
#endif
// ### REMOVE_RELEASE END

// Driver common header
#include "driver_common.h"
#include "ddim_user_custom.h"

// Clock Control
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif

// Memory barrier
#include "dd_arm.h"
// MILB register header
#include "jdsiip.h"


#define CT_TYPE_IM_IIP_TOOL                  (ct_im_iip_tool_get_type())
#define CT_IM_IIP_TOOL(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipTool)) 
#define CT_IS_IM_IIP_TOOL(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_TOOL)) 

#ifndef CO_CT_IM_IIP_DISABLE

#if 1
#undef Ddim_Print
#define Ddim_Print(arg)		{DDIM_User_Printf arg;}		/**< printf function inside DDIM */
#endif

//#define CO_CT_IM_IIP_2_5_3_DISABLE_FRECT_TBL
//#define CO_CT_IM_IIP_2_5_4_DISABLE_FRECT_TBL
//#define CO_CT_IM_IIP_5_1_1_DISABLE_LUT
//#define CO_CT_IM_IIP_5_1_2_DISABLE_LUT
//#define CO_CT_IM_IIP_14_3_1_DISABLE_LUT
//#define CO_CT_IM_IIP_14_3_2_DISABLE_LUT
//#define CO_CT_IM_IIP_3_1_1_FILL_TEST
//#define CO_CT_IM_IIP_2_7_1_DISABLE_HIST
//#define CO_CT_IM_IIP_11_1_2_DISABLE_HIST
#define CO_CT_IM_IIP_DCACHE_CLEAN_ENABLE

// Enable CT test number 1-1-26
//#define CO_CT_IM_IIP_ENABLE_1_1_26
// Enable CT test number 1-1-34
//#define CO_CT_IM_IIP_ENABLE_1_1_34
// Enable Image SRAM by B2Y-IIP link and/or IIP-IIP link
#define CO_CT_IM_IIP_USE_SRAM


#define D_CT_IM_IIP_UNIT_ARRAY_MAX		(sizeof(g_ct_im_iip_unitid_array) / sizeof(g_ct_im_iip_unitid_array[0]))



/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef struct {
	UINT64							pldunit;
	E_IM_IIP_UNIT_ID				unitid;
	CHAR*							unitname;
	volatile struct io_iip_uinftbl* pUNITINFTBL;
	VOID (*unit_param_dump)( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
	UCHAR							is_sl;
} T_CT_IM_IIP_UNITID_TBL;

typedef struct {
	CHAR*			axiname;
	volatile ULONG*	reg_addr0;
	volatile ULONG*	reg_addr1;
} T_CT_IM_IIP_AXI_PRINT_TBL;


/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
#define ct_im_iip_conv_afntbl_float(regval)		((DOUBLE)(regval) / D_IM_IIP_PARAM_AFN_VAL_1_0)

#endif //CO_CT_IM_IIP_DISABLE

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef CO_MSG_PRINT_ON
#define D_IM_IIP_RESULT(statement)		result = statement
#else
#define D_IM_IIP_RESULT
#endif

#ifdef CO_DEBUG_ON_PC
#define ct_im_iip_print_hwen( unit_name, unitinftbl_reg )		Ddim_Print(( "%s HWEN = %u\n", (unit_name), (unitinftbl_reg).UNITINFTBL0.bit.HWEN ))
#endif // CO_DEBUG_ON_PC



#ifndef CO_CT_IM_IIP_DISABLE

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_2: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_3: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_4: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_5: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_6: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_7: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_8: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_9: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_10: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_11: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_12: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_13: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_14: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_15: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_16: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_17: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_18: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_19: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_20: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_21: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_22: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_23: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_24: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_25: "

#ifdef CO_CT_IM_IIP_ENABLE_1_1_26
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_26: "
#endif //CO_CT_IM_IIP_ENABLE_1_1_26

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_27: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_28: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_29: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_30: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_31: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_32: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_33: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_CT_IM_IIP_ENABLE_1_1_34
#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_34: "
#endif //CO_DEBUG_ON_PC
#endif // CO_CT_IM_IIP_ENABLE_1_1_34

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_35: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_36: "

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_37: "
#endif //CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_38: "
#endif //CO_DEBUG_ON_PC

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_39: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_40: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_41: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_42: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_43: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_44: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_1_1_45: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_1_1: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_1_2: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_1_3: "

typedef struct {
	E_IM_IIP_UNIT_ID				unit_id;
	volatile struct io_iip_uinftbl*	uinftbl;
} T_CT_IM_IIP_2_1_3;


#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_2_1: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_2_2: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_4_1: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_6_1: "

#undef D_IM_IIP_FUNC_NAME
#define D_IM_IIP_FUNC_NAME "CT_Im_IIP_2_7_1: "

#endif //CO_CT_IM_IIP_DISABLE



typedef struct _CtImIipTool CtImIipTool;
typedef struct _CtImIipToolPrivate CtImIipToolPrivate;

struct _CtImIipTool 
{
	KObject parent;
};


KConstType 		ct_im_iip_tool_get_type(void);
CtImIipTool*		ct_im_iip_tool_get(void);

#endif /* __CT_IM_IIP_TOOL_H__ */
