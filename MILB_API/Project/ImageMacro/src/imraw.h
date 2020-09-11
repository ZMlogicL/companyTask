/*
 * imraw.h
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#ifndef __IM_RAW_H__
#define __IM_RAW_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_RAW          (im_raw_get_type())
#define IM_RAW(obj)            (K_TYPE_CHECK_INSTANCE_CAST(obj, imRaw))
#define IM_IS_RAW(obj)      (K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_RAW))

#define D_IM_RAW_NUM_CATEGORY	(15)	/**< The number of category */
/**
	@name Returned value
	@{
*/
//	D_DDIM_OK is defined with driver_common.h
#define	D_IM_RAW_RETVAL_OK				(D_DDIM_OK)								/**< OK */
#define	D_IM_RAW_RETVAL_PARAM_ERROR		(D_IM_RAW | D_DDIM_INPUT_PARAM_ERROR)	/**< Parameter error	*/
#define	D_IM_RAW_RETVAL_SYSTEM_ERROR	(D_IM_RAW | D_DDIM_SYSTEM_ERROR)		/**< System call error	*/
#define	D_IM_RAW_RETVAL_MACRO_BUSY		(D_IM_RAW | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy error	*/
#define	D_IM_RAW_RETVAL_FORCE_STOP		(D_IM_RAW | 0x0000FFFF)					/**< Force stop			*/
#define	D_IM_RAW_RETVAL_R_AXI_ERR		(D_IM_RAW | D_DDIM_R_AXI_ERROR)			/**< Read AXI error		*/
#define	D_IM_RAW_RETVAL_W_AXI_ERR		(D_IM_RAW | D_DDIM_W_AXI_ERROR)			/**< Write AXI error	*/
#define	D_IM_RAW_RETVAL_TIME_OUT		(D_IM_RAW | D_DDIM_TIMEOUT)				/**< Time Out			*/
/*@}*/	// name

#define D_IM_RAW_OFF					(0)		/**< OFF */
#define D_IM_RAW_ON						(1)		/**< ON */

#define D_IM_RAW_RFMT_14_OR_16_BIT		(0)		/**< 14 or 16bits (RAW data) If select 16bit, necessarily set bit_select. */
#define D_IM_RAW_RFMT_12_BIT_PACK		(1)		/**< 12bit pack */
#define D_IM_RAW_RFMT_8_BIT				(2)		/**< 8bits */

#define D_IM_RAW_BITSEL_EXCEPT_16_BIT	(0)		/**< 14/12/8 bits (RAW data) */
#define D_IM_RAW_BITSEL_16_BIT			(1)		/**< 16bits (RAW data) */

#define D_IM_RAW_DEFFC_MCU_2x2			(0)		/**< MCU is 2x2. */
#define D_IM_RAW_DEFFC_MCU_2x1			(1)		/**< MCU is 2x1. */

#define D_IM_RAW_DEFOP_DIFF_PREV_VALUE	(0)		/**< Target pixel value - previous pixel value  [RCTL1.DEFOP = 0b] */
#define D_IM_RAW_DEFOP_DIFF_FIXED_VALUE	(1)		/**< Target pixel value - fixed value (DEFINIT) [RCTL1.DEFOP = 1b] */

#define D_IM_RAW_COND_OK				(0)		/**< Encode/Decode OK. */
#define D_IM_RAW_COND_ENC_LIMIT_OVER	(1)		/**< Encode Error: Over code limitation. */
#define D_IM_RAW_COND_DEC_UNDEF_CODE	(2)		/**< Decode Error: Detect undefined code. */
#define D_IM_RAW_COND_DEC_ERROR			(3)		/**< Decode Error: General error. */

#define D_IM_RAW_TBLAEN_OFF				(1)		/**< Raw macro OFF */
#define D_IM_RAW_TBLAEN_ON				(0)		/**< Raw macro ON */

#define D_IM_RAW_R_AXI_ERROR			(4)		/**< Read AXI Error.(Callback return value) */
#define D_IM_RAW_W_AXI_ERROR			(5)		/**< Write AXI Error.(Callback return value) */

#define D_IM_RAW_NON_CACHE_NON_BUF				(0)		/**< Cache Support: Non Cacheable & Non Bufferable */
#define D_IM_RAW_ON_BUF							(1)		/**< Cache Support: Bufferable */
#define D_IM_RAW_ON_CACHE_NO_ALLOCATE			(2)		/**< Cache Support: Cacheable & No Allocate */
#define D_IM_RAW_ON_CACHE_ON_BUF_NO_ALLOCATE	(3)		/**< Cache Support: Cacheable & Bufferable & No Allocate */
#define D_IM_RAW_ON_CACHE_R_WRITE_THROUGH		(6)		/**< Cache Support: Cacheable & Write Through(Allocate Read only) */
#define D_IM_RAW_ON_CACHE_R_WRITE_BACK			(7)		/**< Cache Support: Cacheable & Write Back(Allocate Read only) */
#define D_IM_RAW_ON_CACHE_W_WRITE_THROUGH		(10)	/**< Cache Support: Cacheable & Write Through(Allocate Write only) */
#define D_IM_RAW_ON_CACHE_W_WRITE_BACK			(11)	/**< Cache Support: Cacheable & Write Back(Allocate Write only) */
#define D_IM_RAW_ON_CACHE_RW_WRITE_THROUGH		(14)	/**< Cache Support: Cacheable & Write Through(Allocate Read & Write) */
#define D_IM_RAW_ON_CACHE_RW_WRITE_BACK			(15)	/**< Cache Support: Cacheable & Write Back(Allocate Read & Write) */

#define D_IM_RAW_D_SEC_NORMAL_ACCESS			(0)		/**< Cache Protect: Data       /Secure    /Normal     Access */
#define D_IM_RAW_D_SEC_PRIVILEGED_ACCESS		(1)		/**< Cache Protect: Data       /Secure    /Privileged Access */
#define D_IM_RAW_D_NSEC_NORMAL_ACCESS			(2)		/**< Cache Protect: Data       /Non-Secure/Normal     Access */
#define D_IM_RAW_D_NSEC_PRIVILEGED_ACCESS		(3)		/**< Cache Protect: Data       /Non-Secure/Privileged Access */
#define D_IM_RAW_I_SEC_NORMAL_ACCESS			(4)		/**< Cache Protect: Instruction/Secure    /Normal     Access */
#define D_IM_RAW_I_SEC_PRIVILEGED_ACCESS		(5)		/**< Cache Protect: Instruction/Secure    /Privileged Access */
#define D_IM_RAW_I_NSEC_NORMAL_ACCESS			(6)		/**< Cache Protect: Instruction/Non-Secure/Normal     Access */
#define D_IM_RAW_I_NSEC_PRIVILEGED_ACCESS		(7)		/**< Cache Protect: Instruction/Non-Secure/Privileged Access */

/** Code Table */
typedef struct {
	USHORT	code[D_IM_RAW_NUM_CATEGORY];			/**< CODEx (x = 0x0, 0x1, ... 0xE) */
	UCHAR	code_length[D_IM_RAW_NUM_CATEGORY];		/**< LENx  (x = 0x0, 0x1, ... 0xE) */
} T_IM_RAW_CTRL_CODE_TBL;


/** Im_RAW_Ctrl_Axi() parameter structure */
typedef struct {
	UINT32	r_cache_type;			/**< Read ch cache type<br>
											<ul>
												<li>@ref D_IM_RAW_NON_CACHE_NON_BUF
												<li>@ref D_IM_RAW_ON_BUF
												<li>@ref D_IM_RAW_ON_CACHE_NO_ALLOCATE
												<li>@ref D_IM_RAW_ON_CACHE_ON_BUF_NO_ALLOCATE
												<li>@ref D_IM_RAW_ON_CACHE_R_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_R_WRITE_BACK
												<li>@ref D_IM_RAW_ON_CACHE_W_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_W_WRITE_BACK
												<li>@ref D_IM_RAW_ON_CACHE_RW_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_RW_WRITE_BACK
											</ul>
									 */
	UINT32	r_protection_type;		/**< Read ch protect type <br>
											<ul>
												<li>@ref D_IM_RAW_D_SEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_D_SEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_D_NSEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_D_NSEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_I_SEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_I_SEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_I_NSEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_I_NSEC_PRIVILEGED_ACCESS
											</ul>
									 */
	UINT32	w_cache_type;			/**< Write ch cache type<br>
											<ul>
												<li>@ref D_IM_RAW_NON_CACHE_NON_BUF
												<li>@ref D_IM_RAW_ON_BUF
												<li>@ref D_IM_RAW_ON_CACHE_NO_ALLOCATE
												<li>@ref D_IM_RAW_ON_CACHE_ON_BUF_NO_ALLOCATE
												<li>@ref D_IM_RAW_ON_CACHE_R_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_R_WRITE_BACK
												<li>@ref D_IM_RAW_ON_CACHE_W_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_W_WRITE_BACK
												<li>@ref D_IM_RAW_ON_CACHE_RW_WRITE_THROUGH
												<li>@ref D_IM_RAW_ON_CACHE_RW_WRITE_BACK
											</ul>
									 */
	UINT32	w_protection_type;		/**< Write ch protect type <br>
											<ul>
												<li>@ref D_IM_RAW_D_SEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_D_SEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_D_NSEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_D_NSEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_I_SEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_I_SEC_PRIVILEGED_ACCESS
												<li>@ref D_IM_RAW_I_NSEC_NORMAL_ACCESS
												<li>@ref D_IM_RAW_I_NSEC_PRIVILEGED_ACCESS
											</ul>
									 */
} T_IM_RAW_AXI;

/** Im_RAW_Get_AXI_Status() parameter structure */
typedef struct {
	UCHAR	r_ch_resp;		/**< Read Channel Response */
	UCHAR	w_ch_resp;		/**< Write Channel Response */
} T_IM_RAW_AXI_STATUS;

/** Parameters of Im_RAW_Ctrl_Enc() and Im_RAW_Ctrl_Dec() */
typedef struct {

	// Common (16/14/12/8 bit)
	UINT32		src_addr;				/**< MSA.<br>
											 Source address.<br>
											 Should be aligned on 16.
										 */
	UINT32		dst_addr;				/**< MDA.<br>
											 Destination address.<br>
											 Should be aligned on 16.
										 */
	UINT32		diff_fixed_value;		/**< DEFINIT.<br>
										   	 Fixed value of subtraction. [0~16383].
										 */
	UCHAR		byte_stuffing;			/**< RCTL1.BYTS<br>
											 Byte stuffing.<br>
											 <ul>
												<li>@ref D_IM_RAW_OFF		Byte stuffing OFF [RCTL1.BYTS = 0b]
												<li>@ref D_IM_RAW_ON		Byte stuffing ON  [RCTL1.BYTS = 1b]
											 </ul>
										 */
	UCHAR		data_format;			/**< RCTL1.RFMT<br>
											 Data format<br>
											 <ul>
												<li>@ref D_IM_RAW_RFMT_14_OR_16_BIT	14/16 bit   [RCTL1.RFMT = 00b]
												<li>@ref D_IM_RAW_RFMT_12_BIT_PACK	12 bit pack [RCTL1.RFMT = 01b]
												<li>@ref D_IM_RAW_RFMT_8_BIT		8 bit       [RCTL1.RFMT = 10b]
											 </ul>
										 */
	T_IM_RAW_AXI	axi_param;			/**< RAW AXI parameter. */
	VOID		(*callback)(UINT32);	/**< The pointer of callback function. The callback function can be called in Im_RAW_Int_Handler.
											 If this parameter is set to NULL, Im_RAW_Int_Handler does not call callback function. <br><br>
											 Sample of callback function.<br>
											 @code
											 VOID RAW_User_Callback( UINT32 condition )
											 {
												switch ( condition ) {
													case D_IM_RAW_COND_OK:
														// User process when COND = 000b.
														break;
													case D_IM_RAW_COND_ENC_LIMIT_OVER:
														// User process when COND = 001b.
														break;
													case D_IM_RAW_COND_DEC_UNDEF_CODE:
														// User process when COND = 010b.
														break;
													case D_IM_RAW_COND_DEC_ERROR:
														// User process when COND = 011b.
														break;
													case D_IM_RAW_R_AXI_ERROR:
														// User process when 100b.
														break;
													case D_IM_RAW_W_AXI_ERROR:
														// User process when 101b.
														break;
													default:
														break;
												}
											 }
											 @endcode
										   */
	// Only 12/14/16 bits
	UCHAR		mcu_size;			/**< RCTL1.DEFFC<br>
										 MCU size.<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_14_or_16_BIT.<br>
											 <ul>
												<li>@ref D_IM_RAW_DEFFC_MCU_2x2		MCU 2x2 [RCTL1.DEFFC = 0b]
												<li>@ref D_IM_RAW_DEFFC_MCU_2x1		MCU 2x1 [RCTL1.DEFFC = 1b]
											 </ul>
										 */
	UCHAR		bit_select;			/**< RCTL1.BITSEL<br>
										 Select whether 16 bits or except 16 bits RAW data.<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_14_or_16_BIT.<br>
											 <ul>
												<li>@ref D_IM_RAW_BITSEL_EXCEPT_16_BIT	Except 16 bit RAW [RCTL1.BITSEL = 0b]
												<li>@ref D_IM_RAW_BITSEL_16_BIT			16 bit RAW [RCTL1.BITSEL = 1b]
											 </ul>
									 */
	USHORT		width;				/**< HSIZE<br>
										 Width (pixels) [0~16383]. Should be aligned on 32.<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_14_or_16_BIT.<br>
									 */
	USHORT		lines;				/**< VSIZE<br>
										 Lines (pixels) [0~16383]. Should be aligned on 2.<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_14_or_16_BIT.<br>
									 */

	// Only 8bit data.
	UCHAR		diff_mode;			/**< RCTL1.DEFOP<br>
										 The mode of subtraction.<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_8_BIT.<br>
											 <ul>
												<li>@ref D_IM_RAW_DEFOP_DIFF_PREV_VALUE		[RCTL1.DEFOP = 0b]
												<li>@ref D_IM_RAW_DEFOP_DIFF_FIXED_VALUE	[RCTL1.DEFOP = 1b]
											 </ul>
									 */
	UCHAR		*lut;				/**< RCTL1.LUTEN<br>
										 LUTx (x = 0, 1, ..., 255)<br>
										 If it is set to NULL, LUT is not used. [RCTL1.LUTEN = 0b]<br>
										 If it is set to the address of LUT table (UCHAR user_lut_table[256]), LUT is used. [RCTL1.LUTEN = 1b]<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_8_BIT.<br>
									 */
	UINT32		data_size;			/**< DSIZE<br>
										 Data size (bytes)<br>
										 This parameter is valid only when T_IM_RAW_CTRL_PARAM::data_format is set to D_IM_RAW_RFMT_8_BIT.<br>
									 */
} T_IM_RAW_CTRL_PARAM;

typedef struct _imRaw  imRaw;
typedef struct _imRawPrivate imRawPrivate;

struct _imRaw {
KObject parent;
};


KConstType  im_raw_get_type(void);
imRaw* im_raw_new(void);

VOID Im_RAW_On_Pclk( VOID );
VOID Im_RAW_Off_Pclk( VOID );
INT32 Im_RAW_Init( VOID );
INT32 Im_RAW_Open( INT32 wait_time );
INT32 Im_RAW_Close( VOID );
INT32 Im_RAW_Ctrl_CodeTbl( const T_IM_RAW_CTRL_CODE_TBL* const tbl, UCHAR data_format );
INT32 Im_RAW_Ctrl_Enc( const T_IM_RAW_CTRL_PARAM* const cfg, UINT32 code_limit );
INT32 Im_RAW_Ctrl_Dec( const T_IM_RAW_CTRL_PARAM* const cfg );
INT32 Im_RAW_Start( VOID );
INT32 Im_RAW_Wait_End_Enc( UINT32* const condition, UINT32* const byte, INT32 wait_time );
INT32 Im_RAW_Wait_End_Dec( UINT32* const condition, INT32 wait_time );
INT32 Im_RAW_Stop( VOID );
INT32 Im_RAW_Get_AXI_Status( T_IM_RAW_AXI_STATUS* const sts );
VOID Im_RAW_Int_Handler( VOID );


#endif /* __IM_RAW_H__ */
