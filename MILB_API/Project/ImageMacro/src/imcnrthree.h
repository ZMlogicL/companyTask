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


#ifndef  __IM_CNRTHREE_H__
#define __IM_CNRTHREE_H__


#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_CNRTHREE							(im_cnrthree_get_type ())
#define IM_CNRTHREE(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRTHREE, ImCnrthree))
#define IM_CNRTHREE_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRTHREE, ImCnrthreeClass))
#define IM_IS_CNRTHREE(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRTHREE))
#define IM_IS_CNRTHREE_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRTHREE))
#define IM_CNRTHREE_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRTHREE, ImCnrthreeClass))


typedef struct _ImCnrthree 							ImCnrthree;
typedef struct _ImCnrthreeClass 					ImCnrthreeClass;
typedef struct _ImCnrthreePrivate 				ImCnrthreePrivate;

struct _ImCnrthree{
	GObject parent;
};

struct _ImCnrthreeClass{
	GObjectClass parentclass;
};


#ifdef __cplusplus
	extern "c1" {
#endif


GType 						im_cnrthree_get_type(void) G_GNUC_CONST;
ImCnrthree* 			im_cnrthree_new(void);

#ifdef CO_CNR_DEBUG
VOID im_cnrthree_print_clockstatus( ImCnrthree *self );
#endif

/**
SPR Get Latest Address information for On The Fly
@param [in]		ch				channel[0 - 1]
@param [out]	latestAddr		latest CbCr image address
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_otf_get_latest_outaddr(ImCnrthree *self, UCHAR ch, ULONG* const latestAddr );

#ifdef CO_DDIM_UTILITY_USE
/**
Get SPR setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnrCtrlC		Top address of the address array of C suppre parameter
@param[out]	size			Size of the address array of C suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_ctrl_c(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCtrlC** const cnrCtrlC, ULONG* const size );

/**
Get SPR setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	cnrCtrlC		Top address of the address array of C suppre parameter
@param[out]	size			Size of the address array of C suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_ctrl_c(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCtrlC** const cnrCtrlC, ULONG* const size );

/**
Get SPR setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnrCtrlY		Top address of the address array of Y suppre parameter
@param[out]	size			Size of the address array of Y suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_ctrl_y(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrOflCtrlY** const cnrCtrlY, ULONG* const size );

/**
Set SPR setting parameter information for Y for Off Line
@param[in]	sprCtrlY		Y suppre parameter
@param[out]	rdmaCtrlY		Y suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_set_rdmavalue_ofl_ctrl_y(ImCnrthree *self, const ImCnrOflCtrlY* const sprCtrlY,
		ImCnrRdmaDataOflCtrlY* const rdmaCtrlY );


/**
Get SPR table setting address information for Y for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	cnrYsprTbl	Top address of the address array of Y suppre table parameter
@param[out]	size			Size of the address array of Y suppre table parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_yspr_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrOflYsprTbl** const cnrYsprTbl, ULONG* const size );

/**
Set SPR table setting parameter information for Y for Off Line
@param[in]	ysprTable		Y suppre table parameter
@param[out]	rdmaYsprTable	Y suppre table parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_set_rdmavalue_ofl_yspr_table(ImCnrthree *self, const ImCnrTable* const ysprTable,
		ImCnrRdmaDataOflYsprTbl* const rdmaYsprTable );

/**
Get CSPR Mid-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	csprMidYTbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidYTbl** const csprMidYTbl, ULONG* const size );

/**
Get CSPR Mid-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	csprMidYTbl	Top address of the address array of C suppre Middle-Y parameter
@param[out]	size			Size of the address array of C suppre Middle-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidYTbl** const csprMidYTbl, ULONG* const size );


/**
Get CSPR Mid-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprMidCcYTbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcYTbl** const csprMidCcYTbl, ULONG* const size );

/**
Get CSPR Mid-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprMidCcYTbl	Top address of the address array of C suppre Middle-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcYTbl** const csprMidCcYTbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprMidCcCTbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_mid_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcCTbl** const csprMidCcCTbl, ULONG* const size );

/**
Get CSPR Mid-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprMidCcCTbl	Top address of the address array of C suppre Middle-CC-C parameter
@param[out]	size				Size of the address array of C suppre Middle-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_mid_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprMidCcCTbl** const csprMidCcCTbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for Off Line
@param[in]	ch				channel[0 - 2]
@param[out]	csprLowYTbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowYTbl** const csprLowYTbl, ULONG* const size );

/**
Get CSPR Low-Y setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	csprLowYTbl	Top address of the address array of C suppre Low-Y parameter
@param[out]	size			Size of the address array of C suppre Low-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowYTbl** const csprLowYTbl, ULONG* const size );

/**
Get CSPR Low-CC-Y setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprLowCcYTbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowCcYTbl** const csprLowCcYTbl, ULONG* const size );


/**
Get CSPR Low-CC-Y setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprLowCcYTbl	Top address of the address array of C suppre Low-CC-Y parameter
@param[out]	size				Size of the address array of C suppre Low-CC-Y parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_y_table(ImCnrthree *self, UCHAR ch,
		const ImCnrRdmaAddrCsprLowCcYTbl** const csprLowCcYTbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprLowCcCTbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_low_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprLowCcCTbl** const csprLowCcCTbl, ULONG* const size );

/**
Get CSPR Low-CC-C setting address information for C for On The Fly
@param[in]	ch					channel[0 - 2]
@param[out]	csprLowCcCTbl	Top address of the address array of C suppre Low-CC-C parameter
@param[out]	size				Size of the address array of C suppre Low-CC-C parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_low_cc_c_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprLowCcCTbl** const csprLowCcCTbl, ULONG* const size );

/**
Get CSPR Edge setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprEdgeTbl		Top address of the address array of C suppre Edge parameter
@param[out]	size				Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_edge_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprEdgeTbl** const csprEdgeTbl, ULONG* const size );


/**
Get CSPR Edge setting address information for C for On The Fly
@param[in]	ch				channel[0 - 2]
@param[out]	csprEdgeTbl	Top address of the address array of C suppre Edge parameter
@param[out]	size			Size of the address array of C suppre Edge parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_otf_cspr_edge_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprEdgeTbl** const csprEdgeTbl, ULONG* const size );


/**
Get CSPR Hue Specified setting address information for C for Off Line
@param[in]	ch					channel[0 - 2]
@param[out]	csprHueTbl		Top address of the address array of C suppre Hue Specified parameter
@param[out]	size				Size of the address array of C suppre Hue Specified parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrthree_get_rdmaaddr_ofl_cspr_hue_spec_table(ImCnrthree *self, UCHAR ch,
		const ImCnroneRdmaAddrCsprHueTbl** const csprHueTbl, ULONG* const size );


#endif


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNRTHREE_H__ */
