/*
 * imsdramc.h
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#ifndef __IM_SDRAMC_H__
#define __IM_SDRAMC_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_SDRAMC		(im_sdramc_get_type())
#define IM_SDRAMC(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImSdramc))
#define IM_IS_SDRAMC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImSdramc))
#define	D_IM_SDRAMC_INPUT_PARAM_ERROR		(D_IM_SDRAMC | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code<br> Input parameter error			(0x11000001) */
#define	D_IM_SDRAMC_MACRO_BUSY					(D_IM_SDRAMC | D_DDIM_MACRO_BUSY_NG)		/**< Processing result code<br> Macro busy 						(0x11000005) */
#define D_IM_SDRAMC_SEM_NG								(D_IM_SDRAMC | D_DDIM_SEM_NG)				/**< Processing result code<br> Semaphore acquisition NG		(0x11000010) */
#define	D_IM_SDRAMC_SEM_TIMEOUT_ERR			(D_IM_SDRAMC | D_DDIM_SEM_TIMEOUT)			/**< Processing result code<br> Semaphore acquisition Time Out	(0x11000011) */
#define	D_IM_SDRAMC_TIMEOUT					(D_IM_SDRAMC | D_DDIM_TIMEOUT)				/**< Processing result code<br> Time Out 						(0x11000013) */
#define	D_IM_SDRAMC_AXI_ERROR				(D_IM_SDRAMC | D_DDIM_AXI_ERROR)			/**< Processing result code<br> AXI BUS error					(0x1100001A) */
#define	D_IM_SDRAMC_NG								(D_IM_SDRAMC | D_DDIM_SYSTEM_ERROR)			/**< Processing result code<br> Processing NG					(0x11000099) */
#define	D_IM_SDRAMC_PROCESS_END			(D_IM_SDRAMC | 0x000000FF)					/**< Processing result code<br> Process End 					(0x110000FF) */
#define im_sdramc_dsb()							Dd_ARM_Dsb_Pou()
#define im_sdramc_wait_ns( nsec )			Dd_ARM_Wait_ns( nsec )
#define im_sdramc_wait_us( usec )			Dd_ARM_Wait_ns( usec * 1000 )
#ifdef CO_SDRAMC_REG_TYPE_CHECK
#define im_sdramc_check_reg_type( dst, src )	( dst ) = ( src );
#else
#define im_sdramc_check_reg_type( dst, src )
#endif
#define im_sdramc_set_reg_signed( reg, type, member, val )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = (val); \
			(reg).bit.member = work.bit.member; \
			im_sdramc_check_reg_type( work, (reg) ); \
		}
#define im_sdramc_get_reg_signed( val, reg, type, member )		\
		{ \
			type work = { .word = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_sdramc_check_reg_type( (reg), work );	/* The structure type matching check. */ \
		}

#define D_IM_SDRAMC_SHIFT_REMAPADDR		(26)
#define im_sdramc_lock()				Dd_ARM_Critical_Section_Start( gIM_SDRAMC_Spin_Lock )
#define im_sdramc_unlock()				Dd_ARM_Critical_Section_End( gIM_SDRAMC_Spin_Lock )

#ifdef CO_ACT_ICLOCK
#define	CO_ACT_SDRAMC_ICLOCK
#endif

#ifdef CO_ACT_PCLOCK
#define	CO_ACT_SDRMAC_PCLOCK
#endif

#ifdef CO_ACT_SDRAMC_PCLOCK
static volatile UCHAR					gIM_SDRAMC_PCLK_Counter[ E_IM_SDRAMC_CH_MAX ] = { 0, 0 };
#endif

typedef struct _ImSdramc ImSdramc;
typedef enum {
	E_IM_SDRAMC_CH_0 = 0,					/**< Channel 0.				*/
	E_IM_SDRAMC_CH_1,						/**< Channel 1.				*/
	E_IM_SDRAMC_CH_MAX						/**< Channel MAX.			*/
} E_IM_SDRAMC_CH;

typedef enum {
	E_IM_SDRAMC_PORT_MX10 = 0,				/**< MXIC1(MX10).			*/
	E_IM_SDRAMC_PORT_MX11,					/**< MXIC1(MX11).			*/
	E_IM_SDRAMC_PORT_MX12,					/**< MXIC1(MX12).			*/
	E_IM_SDRAMC_PORT_MX13,					/**< MXIC1(MX13).			*/
	E_IM_SDRAMC_PORT_MX20,					/**< MXIC2(MX20).			*/
	E_IM_SDRAMC_PORT_MX21,					/**< MXIC2(MX21).			*/
	E_IM_SDRAMC_PORT_MX22,					/**< MXIC2(MX22).			*/
	E_IM_SDRAMC_PORT_MX23,					/**< MXIC2(MX23).			*/
	E_IM_SDRAMC_PORT_MX30,					/**< MXIC3(MX30).			*/
	E_IM_SDRAMC_PORT_MX31,					/**< MXIC3(MX31).			*/
	E_IM_SDRAMC_PORT_MX32,					/**< MXIC3(MX32).			*/
	E_IM_SDRAMC_PORT_MX33,					/**< MXIC3(MX33).			*/
	E_IM_SDRAMC_PORT_MX40,					/**< MXIC4(MX40).			*/
	E_IM_SDRAMC_PORT_MX50,					/**< MXIC5(MX50).			*/
	E_IM_SDRAMC_PORT_MX51,					/**< MXIC5(MX51).			*/
	E_IM_SDRAMC_PORT_MX00,					/**< MXIC0(MX00).			*/
	E_IM_SDRAMC_PORT_MX01,					/**< MXIC0(MX01).			*/
	E_IM_SDRAMC_PORT_MX60,					/**< MXIC6(MX60).			*/
	E_IM_SDRAMC_PORT_RB0,					/**< H.264(RB0).			*/
	E_IM_SDRAMC_PORT_RB1,					/**< H.264(RB1).			*/
	E_IM_SDRAMC_PORT_RB2,					/**< H.264(RB2).			*/
	E_IM_SDRAMC_PORT_DS0,					/**< H.265 Common(DS0).		*/
	E_IM_SDRAMC_PORT_DS1,					/**< H.265 Common(DS1).		*/
	E_IM_SDRAMC_PORT_SDM,					/**< H.265 Common(SDM).		*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	E_IM_SDRAMC_PORT_VE0,					/**< H.265 Encode(VE0).		*/
	E_IM_SDRAMC_PORT_VE1,					/**< H.265 Encode(VE1).		*/
	E_IM_SDRAMC_PORT_VE2,					/**< H.265 Encode(VE2).		*/
	E_IM_SDRAMC_PORT_VD0,					/**< H.265 Decode(VD0).		*/
	E_IM_SDRAMC_PORT_VD1,					/**< H.265 Decode(VD1).		*/
	E_IM_SDRAMC_PORT_VD2,					/**< H.265 Decode(VD2).		*/
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	E_IM_SDRAMC_PORT_VCOREW,				/**< H.265 Encode(VCOREW).	*/
	E_IM_SDRAMC_PORT_VCORER0,				/**< H.265 Encode(VCORER0).	*/
	E_IM_SDRAMC_PORT_VCORER1,				/**< H.265 Encode(VCORER1).	*/
	E_IM_SDRAMC_PORT_VD0,					/**< H.265 Decode(VD0).		*/
	E_IM_SDRAMC_PORT_VD1,					/**< H.265 Decode(VD1).		*/
	E_IM_SDRAMC_PORT_VD2,					/**< H.265 Decode(VD2).		*/
	E_IM_SDRAMC_PORT_VCPU,					/**< H.265 Encode(VCPU).	*/
	E_IM_SDRAMC_PORT_VCOREM,				/**< H.265 Encode(VCOREM).	*/
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	E_IM_SDRAMC_PORT_MAX					/**< Port MAX.				*/
} E_IM_SDRAMC_PORT;

typedef enum {
	E_IM_SDRAMC_SUBID_MXIC1_1 = 0,			/**< MXIC1(W1/R1).			*/
	E_IM_SDRAMC_SUBID_MXIC1_2,				/**< MXIC1(W2/R2).			*/
	E_IM_SDRAMC_SUBID_MXIC1_3,				/**< MXIC1(W3/R3).			*/
	E_IM_SDRAMC_SUBID_MXIC1_4,				/**< MXIC1(W4).				*/
	E_IM_SDRAMC_SUBID_MXIC1_5,				/**< MXIC1(W5).				*/
	E_IM_SDRAMC_SUBID_MXIC1_6,				/**< MXIC1(W6/R6).			*/
	E_IM_SDRAMC_SUBID_MXIC1_7,				/**< MXIC1(R7).				*/
	E_IM_SDRAMC_SUBID_MXIC1_8,				/**< MXIC1(W8/R8).			*/
	E_IM_SDRAMC_SUBID_MXIC1_9,				/**< MXIC1(W9/R9).			*/
	E_IM_SDRAMC_SUBID_MXIC1_10,				/**< MXIC1(W10/R10).		*/
	E_IM_SDRAMC_SUBID_MXIC1_11,				/**< MXIC1(W11/R11).		*/
	E_IM_SDRAMC_SUBID_MXIC1_12,				/**< MXIC1(W12/R12).		*/
	E_IM_SDRAMC_SUBID_MXIC1_13,				/**< MXIC1(W13).			*/
	E_IM_SDRAMC_SUBID_MXIC1_14,				/**< MXIC1(W14/R14).		*/
	E_IM_SDRAMC_SUBID_MXIC1_15,				/**< MXIC1(W15).			*/
	E_IM_SDRAMC_SUBID_MXIC2_1,				/**< MXIC2(W1/R1).			*/
	E_IM_SDRAMC_SUBID_MXIC2_2,				/**< MXIC2(W2/R2).			*/
	E_IM_SDRAMC_SUBID_MXIC2_3,				/**< MXIC2(W3/R3).			*/
	E_IM_SDRAMC_SUBID_MXIC2_4,				/**< MXIC2(W4).				*/
	E_IM_SDRAMC_SUBID_MXIC2_5,				/**< MXIC2(W5).				*/
	E_IM_SDRAMC_SUBID_MXIC2_6,				/**< MXIC2(W6/R6).			*/
	E_IM_SDRAMC_SUBID_MXIC2_7,				/**< MXIC2(W7/R7).			*/
	E_IM_SDRAMC_SUBID_MXIC2_8,				/**< MXIC2(W8/R8).			*/
	E_IM_SDRAMC_SUBID_MXIC2_9,				/**< MXIC2(W9/R9).			*/
	E_IM_SDRAMC_SUBID_MXIC2_10,				/**< MXIC2(W10/R10).		*/
	E_IM_SDRAMC_SUBID_MXIC2_11,				/**< MXIC2(W11/R11).		*/
	E_IM_SDRAMC_SUBID_MXIC2_12,				/**< MXIC2(W12/R12).		*/
	E_IM_SDRAMC_SUBID_MXIC2_13,				/**< MXIC2(W13).			*/
	E_IM_SDRAMC_SUBID_MXIC2_14,				/**< MXIC2(W14/R14).		*/
	E_IM_SDRAMC_SUBID_MXIC2_15,				/**< MXIC2(W15).			*/
	E_IM_SDRAMC_SUBID_MXIC3_1,				/**< MXIC3(W1/R1).			*/
	E_IM_SDRAMC_SUBID_MXIC3_2,				/**< MXIC3(W2/R2).			*/
	E_IM_SDRAMC_SUBID_MXIC3_3,				/**< MXIC3(W3/R3).			*/
	E_IM_SDRAMC_SUBID_MXIC3_4,				/**< MXIC3(W4/R4).			*/
	E_IM_SDRAMC_SUBID_MXIC3_5,				/**< MXIC3(W5/R5).			*/
	E_IM_SDRAMC_SUBID_MXIC3_6,				/**< MXIC3(W6/R6).			*/
	E_IM_SDRAMC_SUBID_MXIC3_7,				/**< MXIC3(W7/R7).			*/
	E_IM_SDRAMC_SUBID_MXIC3_8,				/**< MXIC3(R8).				*/
	E_IM_SDRAMC_SUBID_MXIC3_9,				/**< MXIC3(W9/R9).			*/
	E_IM_SDRAMC_SUBID_MXIC3_10,				/**< MXIC3(W10/R10).		*/
	E_IM_SDRAMC_SUBID_MXIC3_11,				/**< MXIC3(R11).			*/
	E_IM_SDRAMC_SUBID_MXIC3_12,				/**< MXIC3(W12/R12).		*/
	E_IM_SDRAMC_SUBID_MXIC3_13,				/**< MXIC3(W13/R13).		*/
	E_IM_SDRAMC_SUBID_MXIC3_14,				/**< MXIC3(W14).			*/
	E_IM_SDRAMC_SUBID_MXIC3_15,				/**< MXIC3(W15/R15).		*/
	E_IM_SDRAMC_SUBID_MXIC3_16,				/**< MXIC3(W16/R16).		*/
	E_IM_SDRAMC_SUBID_MXIC3_17,				/**< MXIC3(W17/R17).		*/
	E_IM_SDRAMC_SUBID_MXIC3_18,				/**< MXIC3(R18).			*/
	E_IM_SDRAMC_SUBID_MXIC3_64,				/**< MXIC3(W64/R64).		*/
	E_IM_SDRAMC_SUBID_MXIC3_65,				/**< MXIC3(W65/R65).		*/
	E_IM_SDRAMC_SUBID_MXIC3_66,				/**< MXIC3(W66/R66).		*/
	E_IM_SDRAMC_SUBID_MXIC3_67,				/**< MXIC3(W67/R67).		*/
	E_IM_SDRAMC_SUBID_MXIC5_1,				/**< MXIC5(W1/R1).			*/
	E_IM_SDRAMC_SUBID_MXIC5_2,				/**< MXIC5(W2/R2).			*/
	E_IM_SDRAMC_SUBID_MXIC5_3,				/**< MXIC5(W3/R3).			*/
	E_IM_SDRAMC_SUBID_MXIC5_4,				/**< MXIC5(W4/R4).			*/
	E_IM_SDRAMC_SUBID_MXIC5_5,				/**< MXIC5(W5/R5).			*/
	E_IM_SDRAMC_SUBID_MXIC6_0,				/**< MXIC6(CA7-Core0).		*/
	E_IM_SDRAMC_SUBID_MXIC6_1,				/**< MXIC6(CA7-Core1).		*/
	E_IM_SDRAMC_SUBID_MXIC6_2,				/**< MXIC6(CA7-Core2).		*/
	E_IM_SDRAMC_SUBID_MXIC6_3,				/**< MXIC6(CA7-Core3).		*/
	E_IM_SDRAMC_SUBID_MXIC6_ETC,			/**< MXIC6(CA7-Etc).		*/
	E_IM_SDRAMC_SUBID_MAX					/**< Port MAX.				*/
} E_IM_SDRAMC_SUBID;

typedef enum {
	E_IM_SDRAMC_DATABUF_0 = 0,				/**< Data buffer  0(MX10/MX11).		*/
	E_IM_SDRAMC_DATABUF_1,					/**< Data buffer  1(MX12/MX13).		*/
	E_IM_SDRAMC_DATABUF_2,					/**< Data buffer  2(MX20/MX21).		*/
	E_IM_SDRAMC_DATABUF_3,					/**< Data buffer  3(MX22/MX23).		*/
	E_IM_SDRAMC_DATABUF_4,					/**< Data buffer  4(MX30/MX31).		*/
	E_IM_SDRAMC_DATABUF_5,					/**< Data buffer  5(MX32/MX33).		*/
	E_IM_SDRAMC_DATABUF_6,					/**< Data buffer  6(MX50/MX51).		*/
	E_IM_SDRAMC_DATABUF_7,					/**< Data buffer  7(MX40).			*/
	E_IM_SDRAMC_DATABUF_8,					/**< Data buffer  8(MX00/MX01).		*/
	E_IM_SDRAMC_DATABUF_9,					/**< Data buffer  9(MX60).			*/
	E_IM_SDRAMC_DATABUF_10,					/**< Data buffer 10(RB0).			*/
	E_IM_SDRAMC_DATABUF_11,					/**< Data buffer 11(RB1).			*/
	E_IM_SDRAMC_DATABUF_12,					/**< Data buffer 12(RB2).			*/
	E_IM_SDRAMC_DATABUF_13,					/**< Data buffer 13(DS0/DS1).		*/
	E_IM_SDRAMC_DATABUF_14,					/**< Data buffer 14(SDM).			*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	E_IM_SDRAMC_DATABUF_15,					/**< Data buffer 15(VE0/VE1/VE2).	*/
	E_IM_SDRAMC_DATABUF_16,					/**< Data buffer 16(VD0/VD1).		*/
	E_IM_SDRAMC_DATABUF_17,					/**< Data buffer 17(VD2).			*/
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	E_IM_SDRAMC_DATABUF_16,					/**< Data buffer 16(VD0/VD1).		*/
	E_IM_SDRAMC_DATABUF_18,					/**< Data buffer 18(VCPU).			*/
	E_IM_SDRAMC_DATABUF_19,					/**< Data buffer 19(VCOREW/VCORER0).*/
	E_IM_SDRAMC_DATABUF_20,					/**< Data buffer 20(VCORER1).		*/
	E_IM_SDRAMC_DATABUF_21,					/**< Data buffer 21(VCOREM).		*/
	E_IM_SDRAMC_DATABUF_22,					/**< Data buffer 22(VD2).			*/
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	E_IM_SDRAMC_DATABUF_MAX					/**< Data buffer number MAX.		*/
} E_IM_SDRAMC_DATABUF;

typedef enum {
	E_IM_SDRAMC_EN_DISABLE = 0,				/**< disable.				*/
	E_IM_SDRAMC_EN_ENABLE					/**< enable.				*/
} E_IM_SDRAMC_EN;

typedef enum {
	E_IM_SDRAMC_ACCESS_READ = 0,			/**< Read acsess.			*/
	E_IM_SDRAMC_ACCESS_WRITE				/**< Write access.			*/
} E_IM_SDRAMC_ACCESS;

typedef enum {
	E_IM_SDRAMC_MONMODE_SIZE = 0,			/**< Transfer data size.	*/
	E_IM_SDRAMC_MONMODE_COUNT				/**< Access recieve count.	*/
} E_IM_SDRAMC_MONMODE;

typedef enum {
	E_IM_SDRAMC_RANK_0 = 1,					/**< MR command for Rank0.	*/
	E_IM_SDRAMC_RANK_1						/**< MR command for Rank1.	*/
} E_IM_SDRAMC_RANK;

typedef enum {
	E_IM_SDRAMC_AREA_A = 0,					/**< Area A.				*/
	E_IM_SDRAMC_AREA_B						/**< Area B.				*/
} E_IM_SDRAMC_AREA;

typedef enum {
	E_IM_SDRAMC_TRAINING_MODE_WRITE = 0,	/**< Write leveling.					*/
	E_IM_SDRAMC_TRAINING_MODE_GATE,			/**< Gate training.						*/
	E_IM_SDRAMC_TRAINING_MODE_RDATA_SYNC,	/**< Read Data Synchronizer training.	*/
	E_IM_SDRAMC_TRAINING_MODE_RDATA_EYE,	/**< Read Data Eye training.			*/
	E_IM_SDRAMC_TRAINING_MODE_WDATA_EYE,	/**< Write Data Eye training.			*/
	E_IM_SDRAMC_TRAINING_MODE_RW_TEST,		/**< Read & Write test mode.			*/
	E_IM_SDRAMC_TRAINING_MODE_CA,			/**< CA training.						*/
	E_IM_SDRAMC_TRAINING_MODE_RESERVED		/**< Reserved.							*/
} E_IM_SDRAMC_TRAINING_MODE;

typedef enum {
	E_IM_SDRAMC_BURST_LIMIT_256BYTE = 4,	/**< 256 byte */
	E_IM_SDRAMC_BURST_LIMIT_512BYTE = 5,	/**< 512 byte */
} E_IM_SDRAMC_BURST_LIMIT;

typedef struct {
	USHORT							throughput[ E_IM_SDRAMC_PORT_MAX ];		/**< Throughput of arbitration permission (average interval) (12bits).	*/
	USHORT							latency[ E_IM_SDRAMC_PORT_MAX ];		/**< Initial latency until arbitration permission (12bits).				*/
	E_IM_SDRAMC_EN					enable[ E_IM_SDRAMC_PORT_MAX ];			/**< Rate control enable.												*/
} T_IM_SDRAMC_CMD_ARB_RATE;

typedef struct {
	UCHAR							priority[ E_IM_SDRAMC_PORT_MAX ];		/**< Priority between ports (5bits).
																				 [remarks1]A priority is high so as to be small.
																				 [remarks2]It is forbidden setting the same value between ports.	*/
	E_IM_SDRAMC_EN					enable[ E_IM_SDRAMC_PORT_MAX ];			/**< Priority control enable.											*/
} T_IM_SDRAMC_CMD_ARB_PRI;

typedef struct {
	ULONG							data[ E_IM_SDRAMC_PORT_MAX ];			/**< Access monitor data (32bits).
																				 [remarks]The unit of transfer data size to SDRAM is 8 byte.		*/
} T_IM_SDRAMC_MONITOR;

typedef struct {
	ULONG							data[ E_IM_SDRAMC_SUBID_MAX ];			/**< Access monitor data for MXIC (32bits).
																				 [remarks]The unit of transfer data size to SDRAM is 8 byte.		*/
} T_IM_SDRAMC_MONITOR_MXIC;

typedef VOID (*T_IM_SDRAMC_CALLBACK)( ULONG int_cause );

typedef struct {
	ULONG							s_addr;									/**< Access detection start address (32bits, 4KByte unit).				*/
	ULONG							e_addr;									/**< Access detection end address (32bits, 4KByte unit).				*/
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	ULONG							w_port;									/**< Write access detection port (bit array. bit[0]=0x1:MX10).			*/
	ULONG							r_port;									/**< Read access detection port (bit array. bit[0]=0x1:MX10).			*/
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	ULONG							w_port_l;								/**< Write access detection port (bit array. bit[0]=0x1:MX10).			*/
	ULONG							r_port_l;								/**< Read access detection port (bit array. bit[0]=0x1:MX10).			*/
	ULONG							w_port_u;								/**< Write access detection port (bit array. bit[0]=0x1:VCPU).			*/
	ULONG							r_port_u;								/**< Read access detection port (bit array. bit[0]=0x1:VCPU).			*/
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	T_IM_SDRAMC_CALLBACK			pCallBack;								/**< User callback function.											*/
} T_IM_SDRAMC_ACCESS_DETECTION;

struct _ImSdramc {
	KObject parent;
};

KConstType 		    	im_sdramc_get_type(void);
ImSdramc*		            im_sdramc_new(void);

extern INT32 im_sdramc_set_clock_enable_databuf( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_DATABUF dbno, E_IM_SDRAMC_EN enable );
extern INT32 im_sdramc_strat_selfrefresh( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_stop_selfrefresh( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_start_manualmode( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_stop_manualmode( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_relock_dll( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_start_training( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_TRAINING_MODE mode );
extern INT32 im_sdramc_start_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA area, const T_IM_SDRAMC_ACCESS_DETECTION* const acs_det );
extern INT32 im_sdramc_stop_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA area );
extern INT32 im_sdramc_get_access_detection( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_AREA *area, E_IM_SDRAMC_PORT* port, ULONG* const addr );
extern INT32 im_sdramc_start_monitor( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_MONMODE mode, BOOL write_access, BOOL read_access, BOOL auto_clear );
extern INT32 im_sdramc_stop_monitor( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_get_monitor( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_MONITOR* const mon );
extern INT32 im_sdramc_start_monitor_mxic( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_MONMODE mode, BOOL write_access, BOOL read_access, BOOL auto_clear );
extern INT32 im_sdramc_stop_monitor_mxic( E_IM_SDRAMC_CH ch );
extern INT32 im_sdramc_get_monitor_mxic( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_MONITOR_MXIC* const mon );
extern VOID im_sdramc_int_handler( E_IM_SDRAMC_CH ch );

#endif /* __IM_SDRAMC_H__ */


