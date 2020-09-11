/*
*@Copyright (C) 2010-2020贵阳高新网用软件有限公司
*@date                :2020-9-2
*@author           :sunhongyu
*@brief                :imltmmapevent类
*@rely                  :
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __IM_LTM_MAP_EVENT_H__
#define __IM_LTM_MAP_EVENT_H__

#include <klib.h>

#define IM_TYPE_LTM_MAP_EVENT				(im_ltm_map_event_get_type())
#define IM_LTM_MAP_EVENT(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtmMapEvent))
#define IM_IS_LTM_MAP_EVENT(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_LTM_MAP_EVENT))

typedef struct 													_ImLtmMapEvent ImLtmMapEvent;
typedef struct 													_ImLtmMapEventPrivate ImLtmMapEventPrivate;

struct _ImLtmMapEvent {
	KObject parent;
};

KConstType 		    												im_ltm_map_event_get_type(void);
ImLtmMapEvent*		       									im_ltm_map_event_get(void);

INT32 																		Im_LTM_MAP_Init( UCHAR pipe_no );
INT32																	    Im_LTM_MAP_SW_Reset( UCHAR pipe_no );
INT32 																		Im_LTM_MAP_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_AXI* const ctrl_axi );
INT32																		Im_LTM_MAP_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_RCH_STAT* const axi_read_stat );
INT32 																		Im_LTM_MAP_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_WCH_STAT* const axi_write_stat );
INT32 																		Im_LTM_MAP_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm );
INT32 																		Im_LTM_MAP_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_COMMON* const map_ctrl );
INT32 																		Im_LTM_MAP_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_SDRAM_INPUT* const map_ctrl_sdram_input );
INT32 																		Im_LTM_MAP_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_INDATA_INFO* const in_data_info );
INT32 																		Im_LTM_MAP_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_OUTDATA_INFO* const out_data_info );
INT32 																		Im_LTM_MAP_Ctrl_ModeRBKDirect( UCHAR pipe_no );
INT32 																		Im_LTM_MAP_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );

#endif /* __IM_LTM_MAP_EVENT_H__ */
