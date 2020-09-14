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

#ifndef __IM_BMH1_H__
#define __IM_BMH1_H__

#include <klib.h>

#define IM_TYPE_BMH1		(im_bmh1_get_type())
#define IM_BMH1(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImBmh1))
#define IM_IS_BMH1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_BMH1))

typedef struct 				_ImBmh1 ImBmh1;
typedef struct 				_ImBmh1Private ImBmh1Private;

struct _ImBmh1 {
	KObject parent;
};

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/* Nothing Special */
// SLimbus channel_no
typedef enum {
	ImBmh1_E_IM_BMH_CHANNEL_00 = 0,			// Channel 0
	ImBmh1_E_IM_BMH_CHANNEL_01,				// Channel 1
	ImBmh1_E_IM_BMH_CHANNEL_END				// End flag
} ImBmh1EImBmhChannel;


KConstType 		    im_bmh1_get_type(void);
ImBmh1*		        im_bmh1_get(void);

extern	INT32 Im_BMH_Set_Interrupt( BYTE channel_no, USHORT interrupt_bit, UCHAR permission_flg );
extern	INT32 Im_BMH_Set_Cur( BYTE channel_no, const ImBmhCurBlock* const cur_write_data );
extern	INT32 Im_BMH_Set_Ref( BYTE channel_no, const ImBmhRefBlock* const ref_write_data );
extern	INT32 Im_BMH_Get_Sadr_000( BYTE channel_no, ImBmhSadr000* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_001( BYTE channel_no, ImBmhSadr001* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_010( BYTE channel_no, ImBmhSadr010* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_011( BYTE channel_no, ImBmhSadr011* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_100( BYTE channel_no, ImBmhSadr100* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_101( BYTE channel_no, ImBmhSadr101* const sadr_read_data );
extern	INT32 Im_BMH_Get_Sadr_110( BYTE channel_no, ImBmhSadr110* const sadr_read_data );
extern	INT32 Im_BMH_Get_Ctrl_Dma( BYTE channel_no, ImBmhCtrlDma* const bmh_ctrl_dma );
extern	INT32 Im_BMH_Get_Bmhsad_wr( BYTE channel_no, ImBmhBmhsadWr* const sadWr );
extern	INT32 Im_BMH_Get_Bmhhcnt( BYTE channel_no, ImBmhBmhhcnt* const cnt );
extern	INT32 Im_BMH_Get_Bmhaxierr( BYTE channel_no, ImBmhAxiStatus* const sts );
extern	INT32 Im_BMH_Open( BYTE channel_no, const INT32 tmout );





#endif /* __IM_BMH1_H__ */
