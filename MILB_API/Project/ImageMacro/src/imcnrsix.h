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


#ifndef  __IM_CNRSIX_H__
#define __IM_CNRSIX_H__


#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_CNRSIX								(im_cnrsix_get_type ())
#define IM_CNRSIX(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRSIX, ImCnrsix))
#define IM_CNRSIX_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRSIX, ImCnrsixClass))
#define IM_IS_CNRSIX(obj)							(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRSIX))
#define IM_IS_CNRSIX_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRSIX))
#define IM_CNRSIX_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRSIX, ImCnrsixClass))


struct 				   _ImCnrsix;
typedef struct _ImCnrsix 							ImCnrsix;
typedef struct _ImCnrsixClass 					ImCnrsixClass;
typedef struct _ImCnrsixPrivate 				ImCnrsixPrivate;

struct _ImCnrsix{
	GObject parent;
};

struct _ImCnrsixClass{
	GObjectClass parentclass;
};


#ifdef __cplusplus
	extern "c1" {
#endif


GType 						im_cnrsix_get_type(void) G_GNUC_CONST;
ImCnrsix* 				im_cnrsix_new(void);
/**
Set CbCr setting of source for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	sprsCtrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
extern	INT32 im_cnrsix_ofl_ctrl_sprs_cc(ImCnrsix *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl );


/**
Set CbCr setting of source for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	sprsCtrl	Source CbCr adjustment parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the source CbCr Adjustment is set.
*/
extern	INT32 im_cnrsix_otf_ctrl_sprs_cc(ImCnrsix *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl );


/**
SPR Wait End for Off Line
@param [in]	ch				channel[0 - 1]
@param[out]	pWaitFactor	: Pointer of factor bitfield parameter which release wait process.<br>
								  <ul>
										 <li>@ref ImCnr_FLG_0_OFL_SPR_END
										 <li>@ref ImCnr_FLG_1_OFL_SPR_AXI_ERR
								  </ul>
@param[in]	waitTime			Wait time [msec]. The valid range is -1, 0, ... .
							If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval		D_DDIM_OK						Success.
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		ImCnr_AXI_ERR				Fail - AXI bus error.
@retval		D_IM_CNR_TIMEOUT				Fail - Processing NG.(Time outed)
@retval		ImCnr_SEM_NG					Fail - Process NG. (Event flag error)
@remarks	Wait for SPR function is ended.
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
extern	INT32 im_cnrfive_ofl_wait_end(ImCnrsix *self, UCHAR ch, UINT32* const pWaitFactor,
		const INT32 waitTime );

/**
SPR Wait End for On The Fly
@param [in]	ch				channel[0 - 1]
@param[out]	pWaitFactor	: Pointer of factor bitfield parameter which release wait process.<br>
								  <ul>
										 <li>@ref ImCnr_FLG_0_OTF_SPR_END
										 <li>@ref ImCnr_FLG_1_OTF_SPR_AXI_ERR
								  </ul>
@param[in]	waitTime			Wait time [msec]. The valid range is -1, 0, ... .
							If this parameter is set to -1, driver waits permanently unless system-call sets event-flag.
@retval		D_DDIM_OK						Success.
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		ImCnr_AXI_ERR				Fail - AXI bus error.
@retval		D_IM_CNR_TIMEOUT				Fail - Processing NG.(Time outed)
@retval		ImCnr_SEM_NG					Fail - Process NG. (Event flag error)
@remarks	Wait for SPR function is ended.
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
extern	INT32 im_cnrfive_otf_wait_end(ImCnrsix *self, UCHAR ch, UINT32* const pWaitFactor,
		const INT32 waitTime );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_CNRSIX_H__ */
