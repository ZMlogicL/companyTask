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
#include "ddimusercustom.h"
#include "imr2yclk.h"
#include "imr2y.h"
#include "ddarm.h"

#define IM_TYPE_R2Y_UTILS		(im_r2y_utils_get_type())
#define IM_R2Y_UTILS(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImR2yUtils))
#define IM_IS_R2Y_UTILS(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_R2Y_UTILS))

#ifdef CO_ASSERT_ON
#define ImR2yUtils_ASSETION_MSG( msg )		(msg)
#else
#define ImR2yUtils_ASSETION_MSG( msg )		("")
#endif

//#define IM_R2Y_REG_TYPE_CHECK



// The structure type matching check.
#ifdef IM_R2Y_REG_TYPE_CHECK
#define ImR2yUtils_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else
#define ImR2yUtils_CHECK_REG_TYPE( dst, src )
#endif

#define ImR2yUtils_SRAM_WAIT_USEC			(1)

// PIPE count
#define ImR2yUtils_PIPE_COUNT				(2)


// R2Y Photo/Video mode(DINCTL.B2RDIN)
#define ImR2yUtils_MODE_SDRAM_INPUT		(0)
#define ImR2yUtils_MODE_DIRECT			(1)



#define	ImR2yUtils_PARAM_ERROR					(D_IM_R2Y | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error		*/
#define	ImR2yUtils_MACRO_BUSY						(D_IM_R2Y | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy error		*/


//dd_arm.h
#define Im_R2Y_Dsb()	Dd_ARM_Dsb_Pou()


#define ImR2yUtils_MAX( a, b )						(((a) > (b)) ? (a) : (b))
#define ImR2yUtils_MIN( a, b )						(((a) < (b)) ? (a) : (b))

// Check R2Y activate

#define imR2yUtils_SET_REG_SIGNED_A( reg, type, member, val )		\
		{ \
			type work = { .word[0] = 0xFFFFFFFFUL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImR2yUtils_CHECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}

// Signed register access macros.
#define imR2yUtils_SET_REG_SIGNED( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImR2yUtils_CHECK_REG_TYPE( work, (reg) );	/* The structure type matching check. */ \
		}



typedef struct 				_ImR2yUtils ImR2yUtils;
typedef struct 				_ImR2yUtilsPrivate ImR2yUtilsPrivate;


// Access enable register management
typedef struct {
	kuint16					ctrlCnt[ImR2yUtils_PIPE_COUNT];
	void						(*reg_set_func)( kuint16 pipeNo, kuint16 enable );
} R2yAccessEnableManage;

typedef struct {
	kuint16					ofsXPixs;
	kuint16					ofsYPixs;
	kulong					ofsBytes;
} R2yYyraOfsInfo;

// Ring pixel information
typedef struct {
	kuint16					padEnable;
	kuint16					ringPixs;
	kuint16					padPixs;
	kuint16					refPixs;
} R2yRingPixs;


// control information
typedef struct {
	kuint16					wasStarted;									// 1st call im_r2y_proc_start(im_r2y_proc_new(), ) after im_r2y_proc_stop(im_r2y_proc_new(), ) or Im_r2y_init()
	kuint16					videoPhotoMode;								// Now operation mode(Photo/Video)
	kuint16					busyState;										// Starting state for YYR/YYW/F_R2Y
	kuint16					ycfBypass;										// YCF bypass mode
	kuint16					ycfPadding;									// YCF padding mode
	kuint16					mccSelect;										// MCC process select
	kuint16					mccBitShift;									// MCC bit shift mode
	kuint16					resizeMode[ImR2yCtrl_YYW_CH_MAX - 1];			// Resize mode
	kuint16					pixAvgReductMode[ImR2yCtrl_YYW_CH_MAX - 1];	// Pixel average reduction mode
	kuint16					pixAvgReductEn[ImR2yCtrl_YYW_CH_MAX - 1];		// Pixel average reduction enable
	kuint16					outputMode0a;									// Output channel 0a mode
	UINT32					intStatus;										// Interrupt status
	void					(*r2yUserHandler)(UINT32* intStatus, UINT32 userParam);					// Interrupt Handler
	UINT32					userParam;										// return to callback argument value when interrupt occurs
	kuint16					inputDtype;									// input dtype
	kulong					inAddr[ImR2yCtrl_PORT_MAX];						// input image address
	kuint16					inputGlobal;									// RGB global width(16bytes align)
	kuint16					topOffset[ImR2yCtrl_PORT_MAX];					// RGB Top area bit offset
	kuint16					yywEnable[ImR2yCtrl_YYW_CH_MAX - 1];			// YYW0(&0a)/1/2 enable
	kuint16					yywRectValid;									// validation of yywWidth and yywLines
	kuint16					yywWidth[ImR2yCtrl_YYW_CH_MAX];					// output image width for YYW0/1/2
	kuint16					yywLines[ImR2yCtrl_YYW_CH_MAX];					// output image lines for YYW0/1/2
	R2yRingPixs		ringPixsInfo;									// Ring pixel information
	TImR2yRect			inputSize;										// YYR input size
	R2yCtrlTrimming	trim[ImR2yCtrl_YYW_CH_MAX - 1];					// trim macro setting
	CtrlTrimmingExt	trimExt;									// trim macro setting(external)
} R2yStateMng;

struct _ImR2yUtils {
	KObject parent;
	volatile R2yStateMng gImR2yState[ImR2yUtils_PIPE_COUNT];
	volatile struct io_r2y*			gImIoR2yRegPtr[ImR2yCtrl_PIPE_MAX];
	volatile R2yYyraOfsInfo gImR2yYyraOfsInfo[ImR2yUtils_PIPE_COUNT];
	volatile struct io_r2y_sram*		gImIoR2yTblPtr[ImR2yCtrl_PIPE_MAX];

};

KConstType 		    	im_r2y_utils_get_type(void);
ImR2yUtils*		        im_r2y_utils_get(void);

volatile R2yStateMng* im_r2y_utils_get_state_mng(ImR2yUtils* self);
volatile struct io_r2y** im_r2y_utils_get_io_reg(ImR2yUtils* self);
volatile R2yYyraOfsInfo* im_r2y_utils_get_yyra_ofs_info(ImR2yUtils* self);
volatile struct io_r2y_sram** im_r2y_utils_get_io_tbl(ImR2yUtils* self);

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
//TODO 私转公
void im_r2y_utils_start_rdma(ImR2yUtils *self, T_IM_RDMA_CTRL* ctrl );
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE
void im_r2y_utils_get_loop_val(ImR2yUtils *self, kuint16 pipeNo, kuint16* loop_sta, kuint16* loop_end );

#endif /* __IM_R2Y_UTILS_H__ */
