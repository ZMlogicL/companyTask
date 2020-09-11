/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-9-2
*@author           :sunhongyu
*@brief                :imltmmaplist类
*@rely                  :
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __IM_LTM_LTM_WIN_H__
#define __IM_LTM_LTM_WIN_H__

#include <klib.h>

#define IM_TYPE_LTM_LTM_WIN							(im_ltm_ltm_win_get_type())
#define IM_LTM_LTM_WIN(obj)							(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtmLtmWin))
#define IM_IS_LTM_LTM_WIN(obj)						(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_LTM_LTM_WIN))

typedef struct 															_ImLtmLtmWin ImLtmLtmWin;
typedef struct 															_ImLtmLtmWinPrivate ImLtmLtmWinPrivate;

struct _ImLtmLtmWin {
	KObject parent;
};

INT32 																				Im_LTM_LTM_Init( UCHAR pipe_no );
INT32 																				Im_LTM_LTM_SW_Reset( UCHAR pipe_no );
INT32 																				Im_LTM_LTM_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_AXI* const ctrl_axi );
INT32 																				Im_LTM_LTM_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_RCH_STAT* const axi_read_stat );
INT32 																				Im_LTM_LTM_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_WCH_STAT* const axi_write_stat );
INT32																				Im_LTM_LTM_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm );
INT32 																				Im_LTM_LTM_Set_AxiCtrlParam( UCHAR pipe_no, const T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm );
INT32 																				Im_LTM_LTM_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_COMMON* const ltm_ctrl );
INT32 																				Im_LTM_LTM_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_SDRAM_INPUT* const ltm_ctrl_sdram_input );
INT32 																				Im_LTM_LTM_Set_InAddr_Info_Rgb( UCHAR pipe_no, const T_IM_LTM_INADDR_INFO* const in_addr );
INT32 																				Im_LTM_LTM_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_INDATA_INFO* const in_data_info );
INT32 																				Im_LTM_LTM_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_OUTDATA_INFO* const out_data_info );
INT32 																				Im_LTM_LTM_Ctrl_ModeB2RDirect( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_B2R_DIRECT* const ltm_ctrl_b2r_direct );
INT32 																				Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto( UCHAR pipe_no );

KConstType 		    														 im_ltm_ltm_win_get_type(void);
ImLtmLtmWin*		       													 im_ltm_ltm_win_get(void);

#endif /* __IM_LTM_LTM_WIN_H__ */
