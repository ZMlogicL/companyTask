/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李昕
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

#ifndef _IM_ELA_REG_H_
#define _IM_ELA_REG_H_

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_ELA_REG		(im_ela_reg_get_type())
#define IM_ELA_REG(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImElaReg))
#define IM_IS_ELA_REG(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_ELA_REG))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#define ImElaReg_D_IM_ELA_STAGE_MAX				(5)				/**< ELA macro stage cnt max	*/
#define ImElaReg_D_IM_ELA_STEP_MAX				(16)			/**< ELA macro step cnt max	*/

//#define CO_ELA_REG_TYPE_CHECK
//#define CO_ELA_DEBUG_PRINT		// Debug
#define ImElaReg_CO_ELA_OPTIMUM_MEM			// Memory consumption optimization

#define ImElaReg_D_IM_ELA_SYNC				(0)				/* Sync Processing  			*/
#define ImElaReg_D_IM_ELA_ASYNC				(1)				/* Async Processing 			*/

// interrupt flag
#define ImElaReg_D_IM_ELA_FLG_ELA			(0x00000001)	/**< Interrupt flag */

#define ImElaReg_D_IM_ELA_STEP_S				(0xFF)			/**< Step = Synthesis */

#define ImElaReg_D_IM_ELA_ELAINTF_AXWERF		(0x0020)		// __AXWERF
#define ImElaReg_D_IM_ELA_ELAINTF_AXRERF		(0x0010)		// __AXRERF
#define ImElaReg_D_IM_ELA_ELAINTF_ENWF		(0x0002)		// __ENWF

#define ImElaReg_D_IM_ELA_EXECUTE_MIN		(1)				/* ELA macro execute cnt min	*/

/** Operation mode
*/
#define	ImElaReg_D_IM_ELA_ELAACT_EXTRACT		(0x00)			/**< Operation mode : Extraction mode 		*/
#define	ImElaReg_D_IM_ELA_ELAACT_COMBINE		(0x01)			/**< Operation mode : Combine mode 			*/

#define ImElaReg_D_IM_ELA_SRAM_WAIT_USEC		(1)

//#define ImElaReg_D_IM_ELA_WAIT_END_TIME		(D_DDIM_WAIT_END_TIME)
#define ImElaReg_D_IM_ELA_WAIT_END_TIME		(1000)

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define ImElaReg_IM_ELA_DSB()	Dd_ARM_Dsb_Pou()

#define ImElaReg_IM_ELA_CONV_STAGE_TO_LEVEL(stage)	(stage + 1)

#define ImElaReg_IM_ELA_WAIT_USEC1( usec )	Dd_ARM_Wait_ns( (usec * 1000) )
#ifdef CO_ELA_REG_TYPE_CHECK
#define ImElaReg_IM_ELA_CHECK_REG_TYPE( dst, src )	(dst) = (src);
#else
#define ImElaReg_IM_ELA_CHECK_REG_TYPE( dst, src )
#endif

#define ImElaReg_IM_ELA_SET_REG_SIGNED( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			ImElaReg_IM_ELA_CHECK_REG_TYPE( work, (reg) ); \
		}

#define ImElaReg_IM_ELA_GET_REG_SIGNED( val, reg, type, member )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member + 1); \
			} \
			ImElaReg_IM_ELA_CHECK_REG_TYPE( (reg), work ); \
		}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**  ELA curtail bayer data table */
typedef struct {
	UINT32	bayerAddr[ImElaReg_D_IM_ELA_STEP_MAX];		/**< Output bayer data top address									*/
	USHORT	glHbyte;							/**< Number of curtail bayer data total horizontal size (byte unit)	*/
	USHORT	hSize;								/**< Number of curtail bayer data horizontal pixels					*/
	USHORT	vLine;								/**< Number of curtail bayer data vertical pixels					*/
} TImElaCurtailBayerData;

/** ELA extraction noise data table */
typedef struct {
	UINT32	noiseDataAddr[ImElaReg_D_IM_ELA_STEP_MAX];	/**< Output noise data top address									*/
	USHORT	glHbyte;							/**< Number of curtail bayer data total horizontal size (byte unit)	*/
	USHORT	hSize;								/**< Number of curtail bayer data horizontal pixels					*/
	USHORT	vLine;								/**< Number of curtail bayer data vertical pixels					*/
} TImElaExtractNoiseData;

typedef struct 				_ImElaReg ImElaReg;
typedef struct 				_ImElaRegPrivate ImElaRegPrivate;

struct _ImElaReg {
	KObject parent;
};

KConstType 		    im_ela_reg_get_type(void);
ImElaReg*		        im_ela_reg_new(void);

/*----------------------------------------------------------------------*/
/* Function  															*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
//---------------------------- driver section ----------------------------

VOID im_ela_reg_ctrl_next_register(ImElaReg*self);
VOID im_ela_reg_ctrl_eiwch_register(ImElaReg*self);
VOID im_ela_reg_ctrl_enwch_register(ImElaReg*self);
VOID im_ela_reg_enrach_enwmch_register(ImElaReg*self);
VOID im_ela_reg_calc_curtail_bayer_data(ImElaReg*self, UINT32 outBayerAddr );
VOID im_ela_reg_calc_extract_noise_data(ImElaReg*self, UINT32 extractNoiseAddr, UINT32 noiseSuppressAddr );

/**
Execute exclusive control for ELA macro.<br>
@param [in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref D_DDIM_USER_SEM_WAIT_POL
							<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval D_DDIM_OK						OK
@retval ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Input Parameter Error
@retval ImEla_D_IM_ELA_SEM_NG					Semaphore acquisition NG
@retval ImEla_D_IM_ELA_SEM_TIMEOUT_ERR		Semaphore acquisition Time Out
@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
INT32 im_ela_reg_open(ImElaReg*self, INT32 tmout );

/**
Cancel exclusive control for ELA macro.<br>
@retval D_DDIM_OK						OK
@retval ImEla_D_IM_ELA_SEM_NG					Semaphore release NG
@retval ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Input Parameter Error
@remarks This API uses DDIM_User_Sig_Sem().
*/
INT32 im_ela_reg_close(ImElaReg*self);

/**
Get ELA executing count. <br>
@retval ELA executing count.(0~4)
@retval Parameter error(0xFF)
*/
UCHAR im_ela_reg_get_exe_cnt(ImElaReg*self);

/**
Get Optical zero level shift parameter. <br>
@retval Optical zero level shift parameter.(Two's complement)
@retval Parameter error(0xFF)
*/
USHORT im_ela_reg_get_optical_zero_level_shift(ImElaReg*self);

/**
ELA is executed by synchronous processing.<br>
@retval	D_DDIM_OK			Success
@retval ImEla_D_IM_ELA_TIMEOUT	Fail - Time-out
@retval	ImEla_D_IM_ELA_MACRO_BUSY	Fail - Macro busy
@retval	ImEla_D_IM_ELA_NG			Fail - Processing NG (system error)
@remarks	This API uses DDIM_User_Dly_Tsk().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
INT32 im_ela_reg_start_sync(ImElaReg*self);

/**
ELA is executed by asynchronization processing.<br>
@retval	D_DDIM_OK				Success
@retval	ImEla_D_IM_ELA_MACRO_BUSY		Fail - Macro busy
@remarks When the processing of ELA is completed, the callback function is started.<br>
         Please wait for the completion of processing with @ref im_ela_reg_wait_end(NULL) when you do not use the callback function.
@remarks	This API uses DDIM_User_Dly_Tsk().
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
INT32  im_ela_reg_start_async(ImElaReg*self);

/**
Wait the end of the asynchronization processing started with im_ela_reg_start_async(NULL).
@retval	D_DDIM_OK			Success
@retval ImEla_D_IM_ELA_TIMEOUT	Fail - Time-out
@retval	ImEla_D_IM_ELA_NG			Fail - Processing NG (system error)
@remarks Please receive the end of the asynchronization processing by the callback function when you do not wait for the end of the asynchronization processing by this function.
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
INT32 im_ela_reg_wait_end(ImElaReg*self);

/**
Cancel the LUT sleep for Deknee.
@param [in]		dekneeEnable	: Setting the LUT sleep release for Deknee
						<ul><li>@ref ImEla_D_IM_ELA_DISABLE
							<li>@ref ImEla_D_IM_ELA_ENABLE</ul>
@remarks		When setting the LUT for the Deknee from the CPU, and when the process is performed Deknee, please set to "ImEla_D_IM_ELA_ENABLE".<br>
				If no processing is performed Deknee, you will be able to reduce power consumption by the LUT for Deknee in that you will be set to "ImEla_D_IM_ELA_DISABLE".
*/
VOID im_ela_reg_set_deknee_lut_sleep(ImElaReg*self, UCHAR dekneeEnable );

/**
Set Deknee table
@param [in]	src_tbl			Pointer of Table data (Maximum array number is ImEla_D_IM_ELA_DEKNEE_TBL_MAX)
@param [in]	write_ofs_num	write offset number of table constituent(data number, must set multiple of 2).<br>
							value range: [write_ofs_num + array_num <= ImEla_D_IM_ELA_DEKNEE_TBL_MAX ]
@param [in]	array_num		num of table constituent(data number, must set multiple of 2).<br>
							value range: [write_ofs_num + array_num <= ImEla_D_IM_ELA_DEKNEE_TBL_MAX ]
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_MACRO_BUSY				Fail - Macro busy
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
*/
UINT32 im_ela_reg_set_deknee_tbl(ImElaReg*self, const USHORT* const src_tbl, USHORT write_ofs_num, USHORT array_num );

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/**
Set curtail bayer data table
@param [in]	curtail_bayerl	Pointer of Table data<br> See @ref TImElaCurtailBayerData.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks
sample code<br>
@code
	UINT32 i, j;
	TImElaCurtailBayerData curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX];

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			curtail_bayer[i].bayerAddr[j] = 0x10000000 + (0x100 * i) + j;
		}
		curtail_bayer[i].glHbyte = i + 100;
		curtail_bayer[i].hSize    = i + 200;
		curtail_bayer[i].vLine    = i + 300;
	}

	im_ela_reg_set_curtail_bayer_data_tbl(NULL,0, curtail_bayer );
@endcode
*/
UINT32 im_ela_reg_set_curtail_bayer_data_tbl(ImElaReg*self, const TImElaCurtailBayerData curtail_bayerl[ImElaReg_D_IM_ELA_STAGE_MAX] );

/**
Get curtail bayer data table
@param [out]	curtail_bayerl	Pointer of Table data<br> See @ref TImElaCurtailBayerData.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks
sample code<br>
@code
	UINT32 i, j;
	TImElaCurtailBayerData curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX];

	im_ela_reg_get_curtail_bayer_data_tbl(NULL,0, curtail_bayer);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		printf("(((Stage%d)))\n", i + 1);
		printf("glHbyte = %d\n",	curtail_bayer[i].glHbyte);
		printf("hSize = %d\n",	curtail_bayer[i].hSize);
		printf("vLine = %d\n",	curtail_bayer[i].vLine);
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			printf("(Sterp%02d)bayerAddr = 0x%08X\n", j, curtail_bayer[i].bayerAddr[j]);
		}
	}
@endcode
*/
UINT32 im_ela_reg_get_curtail_bayer_data_tbl(ImElaReg*self, TImElaCurtailBayerData curtail_bayerl[ImElaReg_D_IM_ELA_STAGE_MAX] );

/**
Set extraction noise data table
@param [in]	extract_noise	Pointer of Table data<br> See @ref TImElaExtractNoiseData.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks
sample code<br>
@code
	UINT32 i, j;
	UINT32 result;
	TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX];

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			extract_noise[i].noiseDataAddr[j] = 0x20000000 + (0x100 * i) + j;
		}
		extract_noise[i].glHbyte = i + 100;
		extract_noise[i].hSize    = i + 200;
		extract_noise[i].vLine    = i + 300;
	}

	im_ela_reg_set_extract_noise_data_tbl(NULL,0, extract_noise );
@endcode
*/
UINT32 im_ela_reg_set_extract_noise_data_tbl(ImElaReg*self, const TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX]);

/**
Get extraction noise data table
@param [out]	extract_noise	Pointer of Table data<br> See @ref TImElaExtractNoiseData.<br>
@retval	D_DDIM_OK						Success
@retval	ImEla_D_IM_ELA_INPUT_PARAM_ERROR		Fail - Parameter error
@remarks
sample code<br>
@code
	UINT32 i, j;
	TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX];

	im_ela_reg_get_extract_noise_data_tbl(NULL,extract_noise);

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		printf("(((Stage%d)))\n", i + 1);
		printf("glHbyte = %d\n",	extract_noise[i].glHbyte);
		printf("hSize = %d\n",	extract_noise[i].hSize);
		printf("vLine = %d\n",	extract_noise[i].vLine);
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			printf("(Sterp%02d)noiseDataAddr = 0x%08X\n", j, extract_noise[i].noiseDataAddr[j]);
		}
	}
@endcode
*/
UINT32 im_ela_reg_get_extract_noise_data_tbl(ImElaReg*self, TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX]);

//---------------------------- colabo section ----------------------------
// Nothing Special
#endif

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// _IM_ELA_REG_H_
