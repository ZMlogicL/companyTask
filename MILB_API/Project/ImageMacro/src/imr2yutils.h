/*
 * imr2yutils.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __IM_R2Y_UTILS_H__
#define __IM_R2Y_UTILS_H__

#include <klib.h>
#include "ddim_user_custom.h"
#include "imr2yclk.h"
#include "imr2y.h"
#include "dd_arm.h"

#define IM_TYPE_R2Y_UTILS		(im_r2y_utils_get_type())
#define IM_R2Y_UTILS(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtils))
#define IM_IS_R2Y_UTILS(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILS))

#ifdef CO_ASSERT_ON
#define M_IM_R2Y_ASSETION_MSG( msg )		(msg)
#else
#define M_IM_R2Y_ASSETION_MSG( msg )		("")
#endif

//#define IM_R2Y_REG_TYPE_CHECK



// The structure type matching check.
#ifdef IM_R2Y_REG_TYPE_CHECK
#define im_r2y_check_reg_type( dst, src )	(dst) = (src);
#else
#define im_r2y_check_reg_type( dst, src )
#endif

#define D_IM_R2Y_SRAM_WAIT_USEC			(1)

// PIPE count
#define D_IM_R2Y_PIPE_COUNT				(2)


// R2Y Photo/Video mode(DINCTL.B2RDIN)
#define D_IM_R2Y_MODE_SDRAM_INPUT		(0)
#define D_IM_R2Y_MODE_DIRECT			(1)



#define	D_IM_R2Y_PARAM_ERROR					(D_IM_R2Y | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error		*/
#define	D_IM_R2Y_MACRO_BUSY						(D_IM_R2Y | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy error		*/


//dd_arm.h
#define Im_R2Y_Dsb()	Dd_ARM_Dsb_Pou()


#define im_r2y_max( a, b )						(((a) > (b)) ? (a) : (b))
#define im_r2y_min( a, b )						(((a) < (b)) ? (a) : (b))

// Check R2Y activate

#define im_r2y_set_reg_signed_a( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_r2y_check_reg_type( work, (reg) );	/* The structure type matching check. */ \
		}

// Signed register access macros.
#define im_r2y_set_reg_signed( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_r2y_check_reg_type( work, (reg) );	/* The structure type matching check. */ \
		}



typedef struct 				_ImR2yUtils ImR2yUtils;
typedef struct 				_ImR2yUtilsPrivate ImR2yUtilsPrivate;


// Access enable register management
typedef struct {
	UCHAR					ctrl_cnt[D_IM_R2Y_PIPE_COUNT];
	VOID						(*reg_set_func)( UCHAR pipe_no, UCHAR enable );
} T_IM_R2Y_ACCESS_ENABLE_MANAGE;

typedef struct {
	USHORT					ofs_x_pixs;
	USHORT					ofs_y_pixs;
	ULONG					ofs_bytes;
} T_IM_R2Y_YYRA_OFS_INFO;

// Ring pixel information
typedef struct {
	UCHAR					pad_enable;
	UCHAR					ring_pixs;
	UCHAR					pad_pixs;
	UCHAR					ref_pixs;
} T_IM_R2Y_RING_PIXS;


// control information
typedef struct {
	UCHAR					was_started;									// 1st call im_r2y_proc_start(im_r2y_proc_new(), ) after im_r2y_proc_stop(im_r2y_proc_new(), ) or Im_r2y_init()
	UCHAR					video_photo_mode;								// Now operation mode(Photo/Video)
	UCHAR					busy_state;										// Starting state for YYR/YYW/F_R2Y
	UCHAR					ycf_bypass;										// YCF bypass mode
	UCHAR					ycf_padding;									// YCF padding mode
	UCHAR					mcc_select;										// MCC process select
	UCHAR					mcc_bit_shift;									// MCC bit shift mode
	UCHAR					resize_mode[D_IM_R2Y_YYW_CH_MAX - 1];			// Resize mode
	UCHAR					pix_avg_reduct_mode[D_IM_R2Y_YYW_CH_MAX - 1];	// Pixel average reduction mode
	UCHAR					pix_avg_reduct_en[D_IM_R2Y_YYW_CH_MAX - 1];		// Pixel average reduction enable
	UCHAR					output_mode_0a;									// Output channel 0a mode
	UINT32					int_status;										// Interrupt status
	VOID					(*r2y_user_handler)(UINT32* int_status, UINT32 user_param);					// Interrupt Handler
	UINT32					user_param;										// return to callback argument value when interrupt occurs
	UCHAR					input_dtype;									// input dtype
	ULONG					in_addr[D_IM_R2Y_PORT_MAX];						// input image address
	USHORT					input_global;									// RGB global width(16bytes align)
	UCHAR					top_offset[D_IM_R2Y_PORT_MAX];					// RGB Top area bit offset
	UCHAR					yyw_enable[D_IM_R2Y_YYW_CH_MAX - 1];			// YYW0(&0a)/1/2 enable
	UCHAR					yyw_rect_valid;									// validation of yyw_width and yyw_lines
	USHORT					yyw_width[D_IM_R2Y_YYW_CH_MAX];					// output image width for YYW0/1/2
	USHORT					yyw_lines[D_IM_R2Y_YYW_CH_MAX];					// output image lines for YYW0/1/2
	T_IM_R2Y_RING_PIXS		ring_pixs_info;									// Ring pixel information
	T_IM_R2Y_RECT			input_size;										// YYR input size
	T_IM_R2Y_CTRL_TRIMMING	trim[D_IM_R2Y_YYW_CH_MAX - 1];					// trim macro setting
	T_IM_R2Y_CTRL_TRIMMING_EXT	trim_ext;									// trim macro setting(external)
} T_IM_R2Y_STATE_MNG;

struct _ImR2yUtils {
	KObject parent;
	volatile T_IM_R2Y_STATE_MNG gIM_R2Y_State[D_IM_R2Y_PIPE_COUNT];
	volatile struct io_r2y*			gIM_Io_R2y_Reg_Ptr[D_IM_R2Y_PIPE_MAX];
	volatile T_IM_R2Y_YYRA_OFS_INFO gIM_R2Y_yyra_ofs_info[D_IM_R2Y_PIPE_COUNT];
	volatile struct io_r2y_sram*		gIM_Io_R2y_Tbl_Ptr[D_IM_R2Y_PIPE_MAX];

};

KConstType 		    	im_r2y_utils_get_type(void);
ImR2yUtils*		        im_r2y_utils_get(void);

volatile T_IM_R2Y_STATE_MNG* im_r2y_utils_get_state_mng(ImR2yUtils* self);
volatile struct io_r2y** im_r2y_utils_get_io_reg(ImR2yUtils* self);
volatile T_IM_R2Y_YYRA_OFS_INFO* im_r2y_utils_get_yyra_ofs_info(ImR2yUtils* self);
volatile struct io_r2y_sram** im_r2y_utils_get_io_tbl(ImR2yUtils* self);

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
//TODO 私转公
VOID im_r2y_utils_start_rdma(ImR2yUtils *self, T_IM_RDMA_CTRL* ctrl );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE
VOID im_r2y_utils_get_loop_val(ImR2yUtils *self, UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end );

#endif /* __IM_R2Y_UTILS_H__ */
