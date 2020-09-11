/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#ifndef  __IM_CNRFOUR_H__
#define __IM_CNRFOUR_H__


#include <glib-object.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"


G_BEGIN_DECLS


#define IM_TYPE_CNRFOUR							(im_cnrfour_get_type ())
#define IM_CNRFOUR(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRFOUR, ImCnrfour))
#define IM_CNRFOUR_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRFOUR, ImCnrfourClass))
#define IM_IS_CNRFOUR(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRFOUR))
#define IM_IS_CNRFOUR_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRFOUR))
#define IM_CNRFOUR_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRFOUR, ImCnrfourClass))


typedef struct _ImCnrfour 							ImCnrfour;
typedef struct _ImCnrfourClass 					ImCnrfourClass;
typedef struct _ImCnrfourPrivate 				ImCnrfourPrivate;

struct _ImCnrfour{
	GObject parent;
};

struct _ImCnrfourClass{
	GObjectClass parentclass;
};


#ifdef __cplusplus
	extern "c1" {
#endif


GType 						im_cnrfour_get_type(void) G_GNUC_CONST;
ImCnrfour* 			im_cnrfour_new(void);

/**
SPR Start Sync for On The Fly
@param [in]	ch				channel[0 - 1]
@param[in]	waitTime			Wait time [msec]. The valid range is -1, 0, ... .
							If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval		D_DDIM_OK : success.
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		D_IM_CNR_AXI_ERR				Fail - AXI bus error.
@retval		D_IM_CNR_TIMEOUT				Fail - Processing NG. (Time outed)
@retval		D_IM_CNR_NG						Fail - Process NG. (system error)
@remarks	SPR function is started(enable) Sync.
@remarks	This API uses DDIM_User_Clr_Flg().
*/
extern	INT32 im_cnrfour_otf_start_sync(ImCnrfour *self, UCHAR ch, const INT32 waitTime );

/**
SPR Start Async for On The Fly
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@remarks	SPR function is started(enable) Async.
@remarks	This API uses DDIM_User_Clr_Flg().
*/
extern	INT32 im_cnrfour_otf_start_async(ImCnrfour *self, UCHAR ch );


/**
SPR Start Sync for Off Line
@param [in]	ch				channel[0 - 1]
@param[in]	waitTime			Wait time [msec]. The valid range is -1, 0, ... .
							If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval		D_DDIM_OK : success.
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		D_IM_CNR_AXI_ERR				Fail - AXI bus error.
@retval		D_IM_CNR_TIMEOUT				Fail - Processing NG. (Time outed)
@retval		D_IM_CNR_NG						Fail - Process NG. (system error)
@remarks	SPR function is started(enable) Sync.
@remarks	This API uses DDIM_User_Clr_Flg().
*/
extern	INT32 im_cnrfour_ofl_start_sync(ImCnrfour *self, UCHAR ch, const INT32 waitTime );

/**
SPR Start Async for Off Line
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@remarks	SPR function is started(enable) Async.
@remarks	This API uses DDIM_User_Clr_Flg().
*/
extern	INT32 im_cnrfour_ofl_start_async(ImCnrfour *self, UCHAR ch );

#ifdef CO_DDIM_UTILITY_USE
/**
Get CSPR Hue Specified setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	csprHueTbl	Top address of the address array of C suppre Hue Specified parameter
@param[out]	size			Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_get_rdmaaddr_otf_cspr_hue_spec_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprHueTbl** const csprHueTbl, ULONG* const size );


/**
Get CSPR SPRS setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprSprsCcTbl	Top address of the address array of C suppre SPRS CC parameter
@param[out]	size				Size of the address array of C suppre SPRS CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_get_rdmaaddr_ofl_cspr_sprs_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprsCcTbl** const csprSprsCcTbl, ULONG* const size );

/**
Get CSPR SPRS setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprSprsCcTbl	Top address of the address array of C suppre SPRS CC parameter
@param[out]	size				Size of the address array of C suppre SPRS CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_get_rdmaaddr_otf_cspr_sprs_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprsCcTbl** const csprSprsCcTbl, ULONG* const size );

/**
Get CSPR SPRD setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprSprdCcTbl	Top address of the address array of C suppre SPRD CC parameter
@param[out]	size				Size of the address array of C suppre SPRD CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_get_rdmaaddr_ofl_cspr_sprd_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprdCcTbl** const csprSprdCcTbl, ULONG* const size );

/**
Get CSPR SPRD setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprSprdCcTbl	Top address of the address array of C suppre SPRD CC parameter
@param[out]	size				Size of the address array of C suppre SPRD CC parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_get_rdmaaddr_otf_cspr_sprd_cc_table(ImCnrfour *self, UCHAR ch,
		const ImCnroneRdmaAddrSprdCcTbl** const csprSprdCcTbl, ULONG* const size );

/**
Set SPR setting parameter information for C for Off Line
@param[in]	sprCtrlC		C suppre parameter
@param[out]	rdmaCtrlC		C suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_ofl_ctrl_c(ImCnrfour *self, const ImCnrCtrlC* const sprCtrlC,
		ImCnrRdmaDataCtrlC* const rdmaCtrlC );

/**
Set SPR setting parameter information for C for On The Fly
@param[in]	sprCtrlC		C suppre parameter
@param[out]	rdmaCtrlC		C suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_otf_ctrl_c(ImCnrfour *self, const ImCnrCtrlC* const sprCtrlC,
		ImCnrRdmaDataCtrlC* const rdmaCtrlC );


/**
Set CSPR Mid-Y setting parameter information for C for Off Line
@param[in]	sprCsprMidY			C suppre Middle-Y parameter
@param[out]	rdmaCsprMidYTable	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* const rdmaCsprMidYTable );

/**
Set CSPR Mid-Y setting parameter information for C for On The Fly
@param[in]	sprCsprMidY			C suppre Middle-Y parameter
@param[out]	rdmaCsprMidYTable	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidY,
		ImCnrRdmaDataCsprMidYTbl* const rdmaCsprMidYTable );


/**
Set CSPR Mid-CC-Y setting parameter information for C for Off Line
@param[in]	sprCsprMidCcY			C suppre Middle-CC-Y parameter
@param[out]	rdmaCsprMidCcYTable	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* const rdmaCsprMidCcYTable );

/**
Set CSPR Mid-CC-Y setting parameter information for C for On The Fly
@param[in]	sprCsprMidCcY			C suppre Middle-CC-Y parameter
@param[out]	rdmaCsprMidCcYTable	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_y_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcY,
		ImCnrRdmaDataCsprMidCcYTbl* const rdmaCsprMidCcYTable );

/**
Set CSPR Mid-CC-C setting parameter information for C for Off Line
@param[in]	sprCsprMidCcC			C suppre Middle-CC-C parameter
@param[out]	rdmaCsprMidCcCTable	C suppre Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_ofl_cspr_mid_cc_c_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* const rdmaCsprMidCcCTable );

/**
Set CSPR Mid-CC-C setting parameter information for C for On The Fly
@param[in]	sprCsprMidCcC			C suppre Middle-CC-C Middle-CC-C parameter
@param[out]	rdmaCsprMidCcCTable	C suppre Middle-CC-C Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrfour_set_rdmavalue_otf_cspr_mid_cc_c_table(ImCnrfour *self, const ImCnrTable* const sprCsprMidCcC,
		ImCnrRdmaDataCsprMidCcCTbl* const rdmaCsprMidCcCTable );

#endif


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNRFOUR_H__ */








