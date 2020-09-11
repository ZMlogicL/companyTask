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

#ifndef __IM_B2R2_H__
#define __IM_B2R2_H__

#include <klib.h>

#define	D_IM_B2R_PIPE_MAX					(3)						/**< Max value						*/

#define IM_TYPE_B2R2		(im_b2r2_get_type())
#define IM_B2R2(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImB2r2))
#define IM_IS_B2R2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_B2R2))

typedef struct 				_ImB2r2 ImB2r2;
typedef struct 				_ImB2r2Private ImB2r2Private;

// Ring pixel information
typedef struct {
	UCHAR	padEnable;
	UCHAR	ringPixs;
	UCHAR	padPixs;
	UCHAR	refPixs;
} TImB2rRingPixs;


// control information
typedef struct {
	UCHAR					wasStarted;					// 1st call Im_B2R_Start() after Im_B2R_Stop() or Im_B2R_Init()
	UCHAR					videoPhotoMode;				// Now operation mode(Photo/Video)
	UCHAR					busyState;						// Starting state for YBR/YBW/F_B2R
	UCHAR					ciaBypass;						// CIA bypass mode
	UCHAR					ciaPadding;					// CIA padding mode
	UINT32					intStatus;						// Interrupt status
	VOID					(*b2rUserHandler)(UINT32* int_status, UINT32 user_param);	// Interrupt Handler
	UINT32					userParam;						// return to callback argument value when interrupt occurs
	UCHAR					inputDtype;					// input dtype
	UCHAR					bayerTopPixel;				// Color of Bayer top pixel
	ULONG					inAddr;						// input image address
	USHORT					inputGlobal;					// bayer global width(16bytes align)
	UCHAR					topOffset;						// Bayer Top area bit offset
	TImB2rRingPixs		ringPixsInfo;					// Ring pixel information
	T_IM_B2R_IN_RECT		inputSize;						// YBR input size
	T_IM_B2R_CTRL_TRIMMING	trim;							// YBW trimming
} TImB2rStateMng;

struct _ImB2r2 {
	KObject parent;
	volatile struct io_b2r* gImIoB2rRegPtr[D_IM_B2R_PIPE_MAX];
	TImB2rStateMng gImB2rState[ImB2r1_D_IM_B2R_PIPE_COUNT];
};

//gIM_Io_B2r_Reg_Ptr
#define im_b2r2_get_g_im_io_b2r_reg_ptr(self,i)         (self->gImIoB2rRegPtr[i])
//gIM_B2R_State
#define im_b2r2_get_g_im_b2r_state(self,i)         (self->gImB2rState[i])


KConstType 		    im_b2r2_get_type(void);
ImB2r2*		        im_b2r2_get(void);

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
INT32 Im_B2R_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_B2R_CTRL_SDRAM_INPUT* const b2r_ctrl_sdram_input );
INT32 Im_B2R_Ctrl_ModeB2BDirect( UCHAR pipe_no, const T_IM_B2R_CTRL_B2B_DIRECT* const b2r_ctrl_b2b_direct );
INT32 Im_B2R_Get_HRingPixs( UCHAR pipe_no, USHORT* const ring_pixs );
INT32 Im_B2R_ContStart( UCHAR pipe_no );
INT32 Im_B2R_Start( UCHAR pipe_no, UCHAR start_type );
INT32 Im_B2R_Stop( UCHAR pipe_no );


//为了平衡代码量，私有转公有
VOID im_b2r_calc_in_rect_sdram_input( UCHAR pipe_no );
VOID im_b2r_calc_top_color_sdram_input( UCHAR pipe_no );
VOID im_b2r_calc_in_rect_b2b_direct( UCHAR pipe_no );

#endif /* __IM_B2R2_H__ */
