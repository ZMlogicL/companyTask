/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : maoguangkun
*@brief : CtImIipParam
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_IIP_PARAM_H__
#define __CT_IM_IIP_PARAM_H__


#include <klib.h>

#include "ctimiip1.h"


#define CT_TYPE_IM_IIP_PARAM                  (ct_im_iip_param_get_type())
#define CT_IM_IIP_PARAM(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImIipParam)) 
#define CT_IS_IM_IIP_PARAM(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_IIP_PARAM)) 


typedef struct _CtImIipParam CtImIipParam;
typedef struct _CtImIipParamPrivate CtImIipParamPrivate;


struct _CtImIipParam 
{
	KObject parent;
};


KConstType				ct_im_iip_param_get_type(void);
CtImIipParam* 		ct_im_iip_param_get(void);

#ifndef CO_CT_IM_IIP_DISABLE
VOID 						ct_im_iip_print_afn_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_frect_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_sl_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_csc_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_1d_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_lut_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_blend_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_mft_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_flt_unit_param( volatile struct io_iip_uinftbl* const pUNITINFTBL, const E_IM_IIP_UNIT_ID unitid );
VOID 						ct_im_iip_print_lutram( const E_IM_IIP_LUTRAM_TYPE lutram_type );
#endif //CO_CT_IM_IIP_DISABLE

#endif /* __CT_IM_IIP_PARAM_H__ */
