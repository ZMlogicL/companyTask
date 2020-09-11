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

#ifndef __IM_B2R4_H__
#define __IM_B2R4_H__

#include <klib.h>

#define IM_TYPE_B2R4		(im_b2r4_get_type())
#define IM_B2R4(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImB2r4))
#define IM_IS_B2R4(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_B2R4))

typedef struct 				_ImB2r4 ImB2r4;
typedef struct 				_ImB2r4Private ImB2r4Private;

struct _ImB2r4 {
	KObject parent;
};

KConstType 		    im_b2r4_get_type(void);
ImB2r4*		        im_b2r4_get(void);

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
INT32 Im_B2R_Ctrl_Left_Shift( UCHAR pipe_no, UCHAR bayer_left_shift, UCHAR saturation_mode );
INT32 Im_B2R_Set_WB_Gain( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const bay_color );
INT32 Im_B2R_Ctrl_Axi( UCHAR pipe_no, const T_IM_B2R_CTRL_AXI* const b2r_ctrl_axi );
INT32 Im_B2R_Get_AxiReadStat( UCHAR pipe_no, T_IM_B2R_AXI_YBR_STAT* const b2r_axi_read_stat );
INT32 Im_B2R_Get_AxiWriteStat( UCHAR pipe_no, T_IM_B2R_AXI_YBW_STAT* const b2r_axi_write_stat );
INT32 Im_B2R_Get_AxiWriteMode( UCHAR pipe_no, T_IM_B2R_AXI_YBW_MODE* const b2r_axi_write_mode );
INT32 Im_B2R_Set_AxiWriteMode( UCHAR pipe_no, const T_IM_B2R_AXI_YBW_MODE* const b2r_axi_write_mode );
INT32 Im_B2R_Set_OutBankIndex( UCHAR pipe_no, UCHAR bank_index );
INT32 Im_B2R_Inc_OutBankIndex( UCHAR pipe_no );
INT32 Im_B2R_Set_ExternalIfOutput( UCHAR pipe_no, const UCHAR ext_out_en, const UCHAR ext_out_alarm );
INT32 Im_B2R_Get_ExternalIfOutput( UCHAR pipe_no, UCHAR* const ext_out_en, UCHAR* const ext_out_alarm );
INT32 Im_B2R_Set_FrameStop( UCHAR pipe_no, UCHAR onoff );
INT32 Im_B2R_Get_YbrBusy( UCHAR pipe_no, BOOL* const busy_status );
INT32 Im_B2R_Get_YBR_Error_Factor( UCHAR pipe_no, UINT32* const err_factor );
INT32 Im_B2R_Ctrl_Trimming( UCHAR pipe_no, const T_IM_B2R_CTRL_TRIMMING* const b2r_ctrl_trimming );
INT32 Im_B2R_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );
INT32 Im_B2R_Ctrl_HighPassFilter( UCHAR pipe_no, const T_IM_B2R_CTRL_HPF* const b2r_ctrl_hpf );

//私有转公有
VOID im_b2r_get_loop_val( UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end );

#endif /* __IM_B2R4_H__ */
