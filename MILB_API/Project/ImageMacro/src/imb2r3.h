/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __IM_B2R3_H__
#define __IM_B2R3_H__

#include <klib.h>

#define IM_TYPE_B2R3		(im_b2r3_get_type())
#define IM_B2R3(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImB2r3))
#define IM_IS_B2R3(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_B2R3))

typedef struct 				_ImB2r3 ImB2r3;
typedef struct 				_ImB2r3Private ImB2r3Private;

struct _ImB2r3 {
	KObject parent;
};

KConstType 		    im_b2r3_get_type(void);
ImB2r3*		        im_b2r3_get(void);

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
extern	INT32 Im_B2R_Get_RdmaAddr_Deknee_Table( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_Knee_Table( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_Offset_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_OFST_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_WB_Slope_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_WB_SLOPE_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_WB_Clip_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_WB_CLIP_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_Sensitivity_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_SENSITIVITY_ADDR** addr );
extern	INT32 Im_B2R_Get_RdmaAddr_HPF_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_HPF_ADDR** addr );
extern INT32 Im_B2R_Set_Deknee_Table( UCHAR pipe_no, const USHORT* const src_tbl );
extern INT32 Im_B2R_Set_Knee_Table( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const UCHAR* const src_tbl );
extern INT32 Im_B2R_Set_Offset( UCHAR pipe_no, const T_IM_B2R_OFS* const ofs );
extern INT32 Im_B2R_Set_WB_Slope_Gain( UCHAR pipe_no, UCHAR slope_gain_enable, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color );
extern INT32 Im_B2R_Set_WB_Clip_Level( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color );
extern INT32 Im_B2R_Ctrl_Sensitivity( UCHAR pipe_no, const T_IM_B2R_CTRL_ADIP* const b2r_ctrl_adip );


//为了平衡代码量，把调用他的公有函数放到别的文件，这个私有函数需要转为公有
#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_B2R_RDMA_ON
VOID im_b2r_set_rdma_val_hpf_ctrl( UCHAR pipe_no, const T_IM_B2R_CTRL_HPF* const b2r_ctrl_hpf );
#endif	// CO_B2R_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE


#endif /* __IM_B2R3_H__ */
