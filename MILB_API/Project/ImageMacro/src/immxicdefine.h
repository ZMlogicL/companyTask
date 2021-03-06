/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file immxicdefine.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: MXIC driver
 * @version: 1.0.0
***********************************************************************/

#ifndef __IM_MXIC_DEFINE_H__ 
#define __IM_MXIC_DEFINE_H__ 

#include <klib.h>
#include <string.h>
#include "driver_common.h"
#include "jdsmxic.h"
#include "dd_top.h"
#include "ddim_user_custom.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return value of processing result
#define D_IM_MXIC_INPUT_PARAM_ERROR			(D_IM_MXIC | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code.<br> Input parameter error. */

// General-purpose definition of register value (Effectiveness selection)
#define D_IM_MXIC_OFF						(0)			/**< Effectiveness selection of processing.<br> Invalidity	*/
#define D_IM_MXIC_ON						(1)			/**< Effectiveness selection of processing.<br> Effective	*/

// Monitor start trigger
#define D_IM_MXIC_MONITOR_START_OFF			(0x00)		/**< Monitor start trigger.<br> Monitor is not executed */
#define D_IM_MXIC_MONITOR_START_ON			(0x01)		/**< Monitor start trigger.<br> Monitor is started by configuration starting. */
#define D_IM_MXIC_MONITOR_START_ASSERT		(0x02)		/**< Monitor start trigger.<br> Monitor is started by asserting of a monitor start terminal. */
#define D_IM_MXIC_MONITOR_START_TRG			(0x03)		/**< Monitor start trigger.<br> Monitor is started by "1" writing to TMONTRG.TONTRG. */

// Monitor end trigger
#define D_IM_MXIC_MONITOR_ENDLESS			(0x00)		/**< Monitor end trigger.<br> Monitor operation is continued. */
#define D_IM_MXIC_MONITOR_END_ASSERT		(0x02)		/**< Monitor end trigger.<br> Monitor is ended by asserting of the end terminal of a monitor. */
#define D_IM_MXIC_MONITOR_END_LIMIT			(0x03)		/**< Monitor end trigger.<br> Monitor is ended by the amount limit judging of transmission. */

// Monitor update trigger interval
#define D_IM_MXIC_MONITOR_UPDATE_1			(0x00)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal */
#define D_IM_MXIC_MONITOR_UPDATE_8			(0x01)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 8 times */
#define D_IM_MXIC_MONITOR_UPDATE_16			(0x02)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 16 times */
#define D_IM_MXIC_MONITOR_UPDATE_32			(0x03)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 32 times */
#define D_IM_MXIC_MONITOR_UPDATE_64			(0x04)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 64 times */
#define D_IM_MXIC_MONITOR_UPDATE_128		(0x05)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 128 times */
#define D_IM_MXIC_MONITOR_UPDATE_256		(0x06)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 256 times */
#define D_IM_MXIC_MONITOR_UPDATE_512		(0x07)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 512 times */

// Monitor processing state
#define D_IM_MXIC_MONITOR_OPERATION_PROCESS	(0x00)		/**< Monitor processing state.<br> The monitor is not ended. */
#define D_IM_MXIC_MONITOR_OPERATION_END		(0x01)		/**< Monitor processing state.<br> The monitor is ended. */

// Monitor reading value
#define D_IM_MXIC_VALUE_WHEN_UPDATE_TRG		(0)			/**< Monitor reading value.<br> Amount of transfer data when update trigger generated */
#define D_IM_MXIC_TRANS_COUNT_VALUE			(1)			/**< Monitor reading value.<br> Amount of transfer data count value */

// Monitor type
#define D_IM_MXIC_MONITOR_TRANSFER			(0)			/**< Monitor type.<br> Amount of transfer data */
#define D_IM_MXIC_MONITOR_ACCESS			(1)			/**< Monitor type.<br> Access count */

// Master priority level
#define D_IM_MXIC_MASTER_MOVE_LAST			(0x00)		/**< Master priority level.<br> Master moves to the last of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_1				(0x01)		/**< Master priority level.<br> Master moves to the 1st of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_2				(0x02)		/**< Master priority level.<br> Master moves to the 2nd of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_3				(0x03)		/**< Master priority level.<br> Master moves to the 3rd of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_4				(0x04)		/**< Master priority level.<br> Master moves to the 4th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_5				(0x05)		/**< Master priority level.<br> Master moves to the 5th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_6				(0x06)		/**< Master priority level.<br> Master moves to the 6th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_7				(0x07)		/**< Master priority level.<br> Master moves to the 7th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_8				(0x08)		/**< Master priority level.<br> Master moves to the 8th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_9				(0x09)		/**< Master priority level.<br> Master moves to the 9th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_10			(0x0A)		/**< Master priority level.<br> Master moves to the 10th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_11			(0x0B)		/**< Master priority level.<br> Master moves to the 11th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_12			(0x0C)		/**< Master priority level.<br> Master moves to the 12th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_13			(0x0D)		/**< Master priority level.<br> Master moves to the 13th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_14			(0x0E)		/**< Master priority level.<br> Master moves to the 14th of a slot, after receiving service. */
#define D_IM_MXIC_MASTER_MOVE_15			(0x0F)		/**< Master priority level.<br> Master moves to the 15th of a slot, after receiving service. */

// Slot priority level
#define D_IM_MXIC_SLOT_PRIORITY_UPPER		(0)			/**< Slot priority level.<br> The priority is on upper level slot */
#define D_IM_MXIC_SLOT_PRIORITY_LOWWER		(1)			/**< Slot priority level.<br> The priority is on lower level slot */
#define D_IM_MXIC_SLOT_PRIORITY_UPPER_ONLY	(2)			/**< Slot priority level.<br> The priority is fixed upper level slot */
#define D_IM_MXIC_SLOT_PRIORITY_LOWWER_ONLY	(3)			/**< Slot priority level.<br> The priority is fixed lower level slot */

// Master mask setting
#define D_IM_MXIC_MASTER_MASK_OFF			(0x00)		/**< Master mask setting.<br> Transfer request mask OFF */
#define D_IM_MXIC_MASTER_MASK_ON			(0x01)		/**< Master mask setting.<br> Transfer request mask ON */
#define D_IM_MXIC_MASTER_MASK_PERIOD_ON		(0x02)		/**< Master mask setting.<br> Transfer request mask ON during specified period. */

// Number of monitor target
#define D_IM_MXIC_MAX_MONITOR_TARGET_NUM	(4)			/**< The number of monitor target */

// Number of service history
#define D_IM_MXIC_MAX_MONITOR_HISTORY_NUM	(16)		/**< The number of service history monitor */

// Number of master
#define D_IM_MXIC_MAX_W_MASTER_NUM			(127 + 1)	/**< The number of slave write master */
#define D_IM_MXIC_MAX_R_MASTER_NUM			(127 + 1)	/**< The number of slave read master */

// Number of slot on each port
#define D_IM_MXIC_MAX_W_SLOT_NUM			(4)			/**< The number of slot in write arbiter */
#define D_IM_MXIC_MAX_R_SLOT_NUM			(4)			/**< The number of slot in read arbiter */

// Slot size
#define D_IM_MXIC_SLOT_SIZE_8				(8)			/**< Slot size.<br> 8 columns in slot */
#define D_IM_MXIC_SLOT_SIZE_16				(16)		/**< Slot size.<br> 16 columns in slot */

// MXIC common master number (slave)
#define D_IM_MXIC_W_RESERVE					(0x00)		/**< Write master number.<br> Reserve.			(W00). */
#define D_IM_MXIC_R_RESERVE					(0x80)		/**< Read master number.<br> Reserve.			(R00). */

// MXIC0 Write master number (slave)
#define D_IM_MXIC_0_W_SEN_0					(0x01)		/**< Write master number.<br> SEN0				(W01). */
#define D_IM_MXIC_0_W_SEN_1					(0x02)		/**< Write master number.<br> SEN1				(W02). */
#define D_IM_MXIC_0_W_SEN_2					(0x03)		/**< Write master number.<br> SEN2				(W03). */
#define D_IM_MXIC_0_W_SEN_3					(0x04)		/**< Write master number.<br> SEN3				(W04). */

// MXIC1 Write master number (slave)
#define D_IM_MXIC_1_W_SRO					(0x01)		/**< Write master number.<br> SRO				(W01). */
#define D_IM_MXIC_1_W_B2B					(0x02)		/**< Write master number.<br> B2B				(W02). */
#define D_IM_MXIC_1_W_B2R_A					(0x03)		/**< Write master number.<br> B2RA				(W03). */
#define D_IM_MXIC_1_W_B2R_B					(0x04)		/**< Write master number.<br> B2RB				(W04). */
#define D_IM_MXIC_1_W_B2R_C					(0x05)		/**< Write master number.<br> B2RC				(W05). */
#define D_IM_MXIC_1_W_LTMDT					(0x06)		/**< Write master number.<br> LTMDT				(W06). */
#define D_IM_MXIC_1_W_NONE_7				(0x07)		/**< Write master number.<br> none				(W07). */
#define D_IM_MXIC_1_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define D_IM_MXIC_1_W_NONE_9				(0x09)		/**< Write master number.<br> none				(W09). */
#define D_IM_MXIC_1_W_R2Y_A					(0x0A)		/**< Write master number.<br> R2YA				(W10). */
#define D_IM_MXIC_1_W_R2Y_B					(0x0B)		/**< Write master number.<br> R2YB				(W11). */
#define D_IM_MXIC_1_W_R2Y_C					(0x0C)		/**< Write master number.<br> R2YC				(W12). */
#define D_IM_MXIC_1_W_R2Y_D					(0x0D)		/**< Write master number.<br> R2YD				(W13). */
#define D_IM_MXIC_1_W_CNR_A					(0x0E)		/**< Write master number.<br> CNRA				(W14). */
#define D_IM_MXIC_1_W_CNR_B					(0x0F)		/**< Write master number.<br> CNRB				(W15). */

// MXIC1 Read master number (slave)
#define D_IM_MXIC_1_R_SRO					(0x81)		/**< Read master number.<br> SRO				(R01). */
#define D_IM_MXIC_1_R_B2B					(0x82)		/**< Read master number.<br> B2B				(R02). */
#define D_IM_MXIC_1_R_B2R_A					(0x83)		/**< Read master number.<br> B2RA				(R03). */
#define D_IM_MXIC_1_R_NONE_4				(0x84)		/**< Read master number.<br> none				(R04). */
#define D_IM_MXIC_1_R_NONE_5				(0x85)		/**< Read master number.<br> none				(R05). */
#define D_IM_MXIC_1_R_LTMDT					(0x86)		/**< Read master number.<br> LTMDT				(R06). */
#define D_IM_MXIC_1_R_LTM_R					(0x87)		/**< Read master number.<br> LTMR				(R07). */
#define D_IM_MXIC_1_R_LTM_G					(0x88)		/**< Read master number.<br> LTMG				(R08). */
#define D_IM_MXIC_1_R_LTM_B					(0x89)		/**< Read master number.<br> LTMB				(R09). */
#define D_IM_MXIC_1_R_R2Y_A					(0x8A)		/**< Read master number.<br> R2YA				(R10). */
#define D_IM_MXIC_1_R_R2Y_B					(0x8B)		/**< Read master number.<br> R2YB				(R11). */
#define D_IM_MXIC_1_R_R2Y_C					(0x8C)		/**< Read master number.<br> R2YC				(R12). */
#define D_IM_MXIC_1_R_NONE_13				(0x8D)		/**< Read master number.<br> none				(R13). */
#define D_IM_MXIC_1_R_CNR_B					(0x8E)		/**< Read master number.<br> CNRB				(R14). */
#define D_IM_MXIC_1_R_NONE_15				(0x8F)		/**< Read master number.<br> none				(R15). */

// MXIC2 Write master number (slave)
#define D_IM_MXIC_2_W_SRO					(0x01)		/**< Write master number.<br> SRO				(W01). */
#define D_IM_MXIC_2_W_B2B					(0x02)		/**< Write master number.<br> B2B				(W02). */
#define D_IM_MXIC_2_W_B2R_A					(0x03)		/**< Write master number.<br> B2RA				(W03). */
#define D_IM_MXIC_2_W_B2R_B					(0x04)		/**< Write master number.<br> B2RB				(W04). */
#define D_IM_MXIC_2_W_B2R_C					(0x05)		/**< Write master number.<br> B2RC				(W05). */
#define D_IM_MXIC_2_W_LTMDT					(0x06)		/**< Write master number.<br> LTMDT				(W06). */
#define D_IM_MXIC_2_W_NONE_7				(0x07)		/**< Write master number.<br> none				(W07). */
#define D_IM_MXIC_2_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define D_IM_MXIC_2_W_NONE_9				(0x09)		/**< Write master number.<br> none				(W09). */
#define D_IM_MXIC_2_W_R2Y_A					(0x0A)		/**< Write master number.<br> R2YA				(W10). */
#define D_IM_MXIC_2_W_R2Y_B					(0x0B)		/**< Write master number.<br> R2YB				(W11). */
#define D_IM_MXIC_2_W_R2Y_C					(0x0C)		/**< Write master number.<br> R2YC				(W12). */
#define D_IM_MXIC_2_W_R2Y_D					(0x0D)		/**< Write master number.<br> R2YD				(W13). */
#define D_IM_MXIC_2_W_CNR_A					(0x0E)		/**< Write master number.<br> CNRA				(W14). */
#define D_IM_MXIC_2_W_CNR_B					(0x0F)		/**< Write master number.<br> CNRB				(W15). */

// MXIC2 Read master number (slave)
#define D_IM_MXIC_2_R_SRO					(0x81)		/**< Read master number.<br> SRO				(R01). */
#define D_IM_MXIC_2_R_B2B					(0x82)		/**< Read master number.<br> B2B				(R02). */
#define D_IM_MXIC_2_R_B2R_A					(0x83)		/**< Read master number.<br> B2RA				(R03). */
#define D_IM_MXIC_2_R_NONE_4				(0x84)		/**< Read master number.<br> none				(R04). */
#define D_IM_MXIC_2_R_NONE_5				(0x85)		/**< Read master number.<br> none				(R05). */
#define D_IM_MXIC_2_R_LTMDT					(0x86)		/**< Read master number.<br> LTMDT				(R06). */
#define D_IM_MXIC_2_R_LTM_R					(0x87)		/**< Read master number.<br> LTMR				(R07). */
#define D_IM_MXIC_2_R_LTM_G					(0x88)		/**< Read master number.<br> LTMG				(R08). */
#define D_IM_MXIC_2_R_LTM_B					(0x89)		/**< Read master number.<br> LTMB				(R09). */
#define D_IM_MXIC_2_R_R2Y_A					(0x8A)		/**< Read master number.<br> R2YA				(R10). */
#define D_IM_MXIC_2_R_R2Y_B					(0x8B)		/**< Read master number.<br> R2YB				(R11). */
#define D_IM_MXIC_2_R_R2Y_C					(0x8C)		/**< Read master number.<br> R2YC				(R12). */
#define D_IM_MXIC_2_R_NONE_13				(0x8D)		/**< Read master number.<br> none				(R13). */
#define D_IM_MXIC_2_R_CNR_B					(0x8E)		/**< Read master number.<br> CNRB				(R14). */
#define D_IM_MXIC_2_R_NONE_15				(0x8F)		/**< Read master number.<br> none				(R15). */

// MXIC3 Write master number (slave)
#define D_IM_MXIC_3_W_STAT					(0x01)		/**< Write master number.<br> STAT				(W01). */
#define D_IM_MXIC_3_W_IIP_A					(0x02)		/**< Write master number.<br> IIPA				(W02). */
#define D_IM_MXIC_3_W_IIP_B					(0x03)		/**< Write master number.<br> IIPB				(W03). */
#define D_IM_MXIC_3_W_IIP_C					(0x04)		/**< Write master number.<br> IIPC				(W04). */
#define D_IM_MXIC_3_W_SHDR_A				(0x05)		/**< Write master number.<br> SHDRA				(W05). */
#define D_IM_MXIC_3_W_SHDR_B				(0x06)		/**< Write master number.<br> SHDRB				(W06). */
#define D_IM_MXIC_3_W_SHDR_C				(0x07)		/**< Write master number.<br> SHDRC				(W07). */
#define D_IM_MXIC_3_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define D_IM_MXIC_3_W_ME					(0x09)		/**< Write master number.<br> ME				(W09). */
#define D_IM_MXIC_3_W_IPU_A					(0x0A)		/**< Write master number.<br> IPU_A				(W10). */
#define D_IM_MXIC_3_W_NONE_11				(0x0B)		/**< Write master number.<br> none				(W11). */
#define D_IM_MXIC_3_W_IPU_C					(0x0C)		/**< Write master number.<br> IPU_C				(W12). */
#define D_IM_MXIC_3_W_IPU_D					(0x0D)		/**< Write master number.<br> IPU_D				(W13). */
#define D_IM_MXIC_3_W_IPU_E					(0x0E)		/**< Write master number.<br> IPU_E				(W14). */
#define D_IM_MXIC_3_W_DSP_A					(0x0F)		/**< Write master number.<br> DSP_A				(W15). */
#define D_IM_MXIC_3_W_DSP_B					(0x10)		/**< Write master number.<br> DSP_B				(W16). */
#define D_IM_MXIC_3_W_GPU					(0x11)		/**< Write master number.<br> GPU				(W17). */
#define D_IM_MXIC_3_W_DW					(0x12)		/**< Write master number.<br> DW				(W18). */
#define D_IM_MXIC_3_W_JPEG					(0x13)		/**< Write master number.<br> JPEG				(W19). */
#define D_IM_MXIC_3_W_RAW					(0x14)		/**< Write master number.<br> RAW				(W20). */
#define D_IM_MXIC_3_W_NONE_21				(0x15)		/**< Write master number.<br> none				(W21). */
#define D_IM_MXIC_3_W_GROUP0_M0				(0x30)		/**< Write master number.<br> Group0 Master0	(W48). */
#define D_IM_MXIC_3_W_GROUP0_M1				(0x31)		/**< Write master number.<br> Group0 Master1	(W49). */

// MXIC3 Write master number (group)
#define D_IM_MXIC_3_W_ELA					(0x40)		/**< Write master number.<br> ELA				(W64). */
#define D_IM_MXIC_3_W_XCH					(0x41)		/**< Write master number.<br> XCH				(W65). */
#define D_IM_MXIC_3_W_FPT_0					(0x42)		/**< Write master number.<br> FPT0				(W66). */
#define D_IM_MXIC_3_W_FPT_1					(0x43)		/**< Write master number.<br> FPT1				(W67). */

// MXIC3 Read master number (slave)
#define D_IM_MXIC_3_R_STAT					(0x81)		/**< Read master number.<br> STAT				(R01). */
#define D_IM_MXIC_3_R_IIP_A					(0x82)		/**< Read master number.<br> IIPA				(R02). */
#define D_IM_MXIC_3_R_IIP_B					(0x83)		/**< Read master number.<br> IIPB				(R03). */
#define D_IM_MXIC_3_R_IIP_C					(0x84)		/**< Read master number.<br> IIPC				(R04). */
#define D_IM_MXIC_3_R_SHDR_A				(0x85)		/**< Read master number.<br> SHDRA				(R05). */
#define D_IM_MXIC_3_R_SHDR_B				(0x86)		/**< Read master number.<br> SHDRB				(R06). */
#define D_IM_MXIC_3_R_SHDR_C				(0x87)		/**< Read master number.<br> SHDRC				(R07). */
#define D_IM_MXIC_3_R_SHDR_D				(0x88)		/**< Read master number.<br> SHDRD				(R08). */
#define D_IM_MXIC_3_R_ME					(0x89)		/**< Read master number.<br> ME					(R09). */
#define D_IM_MXIC_3_R_IPU_A					(0x8A)		/**< Read master number.<br> IPU_A				(R10). */
#define D_IM_MXIC_3_R_IPU_B					(0x8B)		/**< Read master number.<br> IPU_B				(R11). */
#define D_IM_MXIC_3_R_IPU_C					(0x8C)		/**< Read master number.<br> IPU_C				(R12). */
#define D_IM_MXIC_3_R_IPU_D					(0x8D)		/**< Read master number.<br> IPU_D				(R13). */
#define D_IM_MXIC_3_R_NONE_14				(0x8E)		/**< Read master number.<br> none				(R14). */
#define D_IM_MXIC_3_R_DSP_A					(0x8F)		/**< Read master number.<br> DSP_A				(R15). */
#define D_IM_MXIC_3_R_DSP_B					(0x90)		/**< Read master number.<br> DSP_B				(R16). */
#define D_IM_MXIC_3_R_GPU					(0x91)		/**< Read master number.<br> GPU				(R17). */
#define D_IM_MXIC_3_R_NONE_18				(0x92)		/**< Read master number.<br> none				(R18). */
#define D_IM_MXIC_3_R_JPEG					(0x93)		/**< Read master number.<br> JPEG				(R19). */
#define D_IM_MXIC_3_R_RAW					(0x94)		/**< Read master number.<br> RAW				(R20). */
#define D_IM_MXIC_3_R_RDMA					(0x95)		/**< Read master number.<br> RDMA				(R21). */
#define D_IM_MXIC_3_R_GROUP0_M0				(0xB0)		/**< Read master number.<br> Group0 Master0		(R48). */
#define D_IM_MXIC_3_R_GROUP0_M1				(0xB1)		/**< Read master number.<br> Group0 Master1		(R49). */

// MXIC3 Read master number (group0)
#define D_IM_MXIC_3_R_ELA					(0xC0)		/**< Write master number.<br> ELA				(R64). */
#define D_IM_MXIC_3_R_XCH					(0xC1)		/**< Write master number.<br> XCH				(R65). */
#define D_IM_MXIC_3_R_FPT_0					(0xC2)		/**< Write master number.<br> FPT0				(R66). */
#define D_IM_MXIC_3_R_FPT_1					(0xC3)		/**< Write master number.<br> FPT1				(R67). */

// MXIC4 Read master number (slave)
#define D_IM_MXIC_4_R_DISP_A				(0x81)		/**< Write master number.<br> DISPA				(R01). */
#define D_IM_MXIC_4_R_DISP_B				(0x82)		/**< Write master number.<br> DISPB				(R02). */

// MXIC5 Write master number (slave)
#define D_IM_MXIC_5_W_EXS_0					(0x01)		/**< Write master number.<br> EXS0				(W01). */
#define D_IM_MXIC_5_W_EXS_1					(0x02)		/**< Write master number.<br> EXS1				(W02). */
#define D_IM_MXIC_5_W_NIC					(0x03)		/**< Write master number.<br> NIC				(W03). */
#define D_IM_MXIC_5_W_BMH_0					(0x04)		/**< Write master number.<br> BMH0				(W04). */
#define D_IM_MXIC_5_W_BMH_1					(0x05)		/**< Write master number.<br> BMH1				(W05). */

// MXIC5 Read master number (slave)
#define D_IM_MXIC_5_R_EXS_0					(0x81)		/**< Write master number.<br> EXS0				(R01). */
#define D_IM_MXIC_5_R_EXS_1					(0x82)		/**< Write master number.<br> EXS1				(R02). */
#define D_IM_MXIC_5_R_NIC					(0x83)		/**< Write master number.<br> NIC				(R03). */
#define D_IM_MXIC_5_R_BMH_0					(0x84)		/**< Write master number.<br> BMH0				(R04). */
#define D_IM_MXIC_5_R_BMH_1					(0x85)		/**< Write master number.<br> BMH1				(R05). */

// MXIC6 Write master number (slave)
#define D_IM_MXIC_6_W_CA7					(0x01)		/**< Write master number.<br> CA7				(W01). */

// MXIC6 Read master number (slave)
#define D_IM_MXIC_6_R_CA7					(0x81)		/**< Write master number.<br> CA7				(R01). */

// Monitor target slave write channel
#define D_IM_MXIC_SLAVE_W1_PORT0			(0x104)		/**< Monitor target slave write channel.<br> W1-Port0 */
#define D_IM_MXIC_SLAVE_W1_PORT1			(0x105)		/**< Monitor target slave write channel.<br> W1-Port1 */
#define D_IM_MXIC_SLAVE_W1_PORT2			(0x106)		/**< Monitor target slave write channel.<br> W1-Port2 */
#define D_IM_MXIC_SLAVE_W1_PORT3			(0x107)		/**< Monitor target slave write channel.<br> W1-Port3 */
#define D_IM_MXIC_SLAVE_W2_PORT0			(0x108)		/**< Monitor target slave write channel.<br> W2-Port0 */
#define D_IM_MXIC_SLAVE_W2_PORT1			(0x109)		/**< Monitor target slave write channel.<br> W2-Port1 */
#define D_IM_MXIC_SLAVE_W2_PORT2			(0x10A)		/**< Monitor target slave write channel.<br> W2-Port2 */
#define D_IM_MXIC_SLAVE_W2_PORT3			(0x10B)		/**< Monitor target slave write channel.<br> W2-Port3 */
#define D_IM_MXIC_SLAVE_W3_PORT0			(0x10C)		/**< Monitor target slave write channel.<br> W3-Port0 */
#define D_IM_MXIC_SLAVE_W3_PORT1			(0x10D)		/**< Monitor target slave write channel.<br> W3-Port1 */
#define D_IM_MXIC_SLAVE_W3_PORT2			(0x10E)		/**< Monitor target slave write channel.<br> W3-Port2 */
#define D_IM_MXIC_SLAVE_W3_PORT3			(0x10F)		/**< Monitor target slave write channel.<br> W3-Port3 */
#define D_IM_MXIC_SLAVE_W4_PORT0			(0x110)		/**< Monitor target slave write channel.<br> W4-Port0 */
#define D_IM_MXIC_SLAVE_W4_PORT1			(0x111)		/**< Monitor target slave write channel.<br> W4-Port1 */
#define D_IM_MXIC_SLAVE_W4_PORT2			(0x112)		/**< Monitor target slave write channel.<br> W4-Port2 */
#define D_IM_MXIC_SLAVE_W4_PORT3			(0x113)		/**< Monitor target slave write channel.<br> W4-Port3 */

// Monitor target slave read channel
#define D_IM_MXIC_SLAVE_R1_PORT0			(0x184)		/**< Monitor target slave read channel.<br> R1-Port0 */
#define D_IM_MXIC_SLAVE_R1_PORT1			(0x185)		/**< Monitor target slave read channel.<br> R1-Port1 */
#define D_IM_MXIC_SLAVE_R1_PORT2			(0x186)		/**< Monitor target slave read channel.<br> R1-Port2 */
#define D_IM_MXIC_SLAVE_R1_PORT3			(0x187)		/**< Monitor target slave read channel.<br> R1-Port3 */
#define D_IM_MXIC_SLAVE_R2_PORT0			(0x188)		/**< Monitor target slave read channel.<br> R2-Port0 */
#define D_IM_MXIC_SLAVE_R2_PORT1			(0x189)		/**< Monitor target slave read channel.<br> R2-Port1 */
#define D_IM_MXIC_SLAVE_R2_PORT2			(0x18A)		/**< Monitor target slave read channel.<br> R2-Port2 */
#define D_IM_MXIC_SLAVE_R2_PORT3			(0x18B)		/**< Monitor target slave read channel.<br> R2-Port3 */
#define D_IM_MXIC_SLAVE_R3_PORT0			(0x18C)		/**< Monitor target slave read channel.<br> R3-Port0 */
#define D_IM_MXIC_SLAVE_R3_PORT1			(0x18D)		/**< Monitor target slave read channel.<br> R3-Port1 */
#define D_IM_MXIC_SLAVE_R3_PORT2			(0x18E)		/**< Monitor target slave read channel.<br> R3-Port2 */
#define D_IM_MXIC_SLAVE_R3_PORT3			(0x18F)		/**< Monitor target slave read channel.<br> R3-Port3 */
#define D_IM_MXIC_SLAVE_R4_PORT0			(0x190)		/**< Monitor target slave read channel.<br> R4-Port0 */
#define D_IM_MXIC_SLAVE_R4_PORT1			(0x191)		/**< Monitor target slave read channel.<br> R4-Port1 */
#define D_IM_MXIC_SLAVE_R4_PORT2			(0x192)		/**< Monitor target slave read channel.<br> R4-Port2 */
#define D_IM_MXIC_SLAVE_R4_PORT3			(0x193)		/**< Monitor target slave read channel.<br> R4-Port3 */
 
// Monitor target nothing
#define D_IM_MXIC_TARGET_NOTHING			(0x00)		/**< Monitor target nothing */

// Master number max.
#define D_IM_MXIC_MASTER_NUMBER_MAX			(0x40)		/**< Max master number.		*/

// The kind of channel which the error generated
#define D_IM_MXIC_DEC_ERR_CH_W				(0x01)		/**< The decoding error occurred by the write channel.<br> */
#define D_IM_MXIC_DEC_ERR_CH_R				(0x02)		/**< The decoding error occurred by the read channel.<br> */
#define D_IM_MXIC_DEC_ERR_CH_RW				(0x04)		/**< The decoding error occurred by the read channel and write channel.<br> */


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define Im_MXIC_Get_TMIF0		(IO_MXIC0.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW0		(IO_MXIC0.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW0		(IO_MXIC0.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR0		(IO_MXIC0.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR0		(IO_MXIC0.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF1		(IO_MXIC1.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW1		(IO_MXIC1.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW1		(IO_MXIC1.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR1		(IO_MXIC1.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR1		(IO_MXIC1.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF2		(IO_MXIC2.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW2		(IO_MXIC2.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW2		(IO_MXIC2.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR2		(IO_MXIC2.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR2		(IO_MXIC2.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF3		(IO_MXIC3.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW3		(IO_MXIC3.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW3		(IO_MXIC3.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR3		(IO_MXIC3.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR3		(IO_MXIC3.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF4		(IO_MXIC4.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW4		(IO_MXIC4.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW4		(IO_MXIC4.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR4		(IO_MXIC4.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR4		(IO_MXIC4.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF5		(IO_MXIC5.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW5		(IO_MXIC5.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW5		(IO_MXIC5.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR5		(IO_MXIC5.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR5		(IO_MXIC5.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define Im_MXIC_Get_TMIF6		(IO_MXIC6.TMIF.word)				/**< Get Interrupt flag register */
#define Im_MXIC_Get_TDEADW6		(IO_MXIC6.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define Im_MXIC_Get_TDEMNW6		(IO_MXIC6.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define Im_MXIC_Get_TDEADR6		(IO_MXIC6.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define Im_MXIC_Get_TDEMNR6		(IO_MXIC6.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */


typedef VOID (*ImMxicDecErrFunc)(UCHAR chType);	/**< Type is defined to callback function pointer for decode error.<br>
															 Decode error information is initialized after the end of processing of a Callback function.<br>
															 For this reason, please be sure to use an @ref mxic_master_slave_get_decode_error function from a Callback function and to refer to error information. <br>
															 The meaning of the argument is as follows.<br>
															 - UCHAR chType: The kind of channel which the error generated.<br>
																<ul><li>@ref D_IM_MXIC_DEC_ERR_CH_W
																	<li>@ref D_IM_MXIC_DEC_ERR_CH_R
																	<li>@ref D_IM_MXIC_DEC_ERR_CH_RW</ul> */


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/**	Slave write or read Arbiter selection. */
typedef enum {
	E_IM_MXIC_UNIT_0 = 0,						/**< MXIC0				*/
	E_IM_MXIC_UNIT_1,							/**< MXIC1				*/
	E_IM_MXIC_UNIT_2,							/**< MXIC2				*/
	E_IM_MXIC_UNIT_3,							/**< MXIC3				*/
	E_IM_MXIC_UNIT_4,							/**< MXIC4				*/
	E_IM_MXIC_UNIT_5,							/**< MXIC5				*/
	E_IM_MXIC_UNIT_6,							/**< MXIC6				*/
	E_IM_MXIC_UNIT_MAX							/**< Enumeration stopper */
} EImMxicUnit;

/**	Slave write or read Arbiter selection. */
typedef enum {
	E_IM_MXIC_WR_ARBITER_W = 0,					/**< Write arbiter */
	E_IM_MXIC_WR_ARBITER_R,						/**< Read arbiter */
	E_IM_MXIC_WR_ARBITER_MAX					/**< Enumeration stopper */
} EImMxicWrArbiter;

/**	Slave Spec Arbiter selection. (slave) */
typedef enum {
	E_IM_MXIC_SPEC_ARBITER_1 = 0,				/**< slave1 arbiter */
	E_IM_MXIC_SPEC_ARBITER_2,					/**< slave2 Read arbiter */
	E_IM_MXIC_SPEC_ARBITER_3,					/**< slave3 Read arbiter */
	E_IM_MXIC_SPEC_ARBITER_4,					/**< slave4 Read arbiter */
	E_IM_MXIC_SPEC_ARBITER_MAX					/**< Enumeration stopper */
} EImMxicSpecArbiter;

/**	Slave write arbiter selection. (slave) */
typedef enum {
	E_IM_MXIC_W_ARBITER_W1 = 0,					/**< W1 arbiter */
	E_IM_MXIC_W_ARBITER_W2,						/**< W2 arbiter */
	E_IM_MXIC_W_ARBITER_W3,						/**< W3 arbiter */
	E_IM_MXIC_W_ARBITER_W4,						/**< W4 arbiter */
	E_IM_MXIC_W_ARBITER_MAX						/**< Enumeration stopper */
} EImMxicWArbiter;

/**	Slave read arbiter selection. (slave) */
typedef enum {
	E_IM_MXIC_R_ARBITER_R1 = 0,					/**< R1 arbiter */
	E_IM_MXIC_R_ARBITER_R2,						/**< R2 arbiter */
	E_IM_MXIC_R_ARBITER_R3,						/**< R3 arbiter */
	E_IM_MXIC_R_ARBITER_R4,						/**< R4 arbiter */
	E_IM_MXIC_R_ARBITER_MAX						/**< Enumeration stopper */
} EImMxicRArbiter;

/**	Slave Spec Arbiter selection. (group) */
typedef enum {
	E_IM_MXIC_SPEC_ARBITER_GR_0 = 0,			/**< group0 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_1,				/**< group1 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_2,				/**< group2 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_3,				/**< group3 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_4,				/**< group4 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_5,				/**< group5 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_6,				/**< group6 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_7,				/**< group7 arbiter */
	E_IM_MXIC_SPEC_ARBITER_GR_MAX				/**< Enumeration stopper */
} EImMxicSpecArbiterGr;

/**	Slave write arbiter selection. (group) */
typedef enum {
	E_IM_MXIC_W_ARBITER_GR_W0 = 0,				/**< W0 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W1,					/**< W1 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W2,					/**< W2 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W3,					/**< W3 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W4,					/**< W4 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W5,					/**< W5 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W6,					/**< W6 arbiter */
	E_IM_MXIC_W_ARBITER_GR_W7,					/**< W7 arbiter */
	E_IM_MXIC_W_ARBITER_GR_MAX					/**< Enumeration stopper */
} EImMxicWArbiterGr;

/**	Slave read arbiter selection. (group) */
typedef enum {
	E_IM_MXIC_R_ARBITER_GR_R0 = 0,				/**< R0 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R1,					/**< R1 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R2,					/**< R2 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R3,					/**< R3 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R4,					/**< R4 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R5,					/**< R5 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R6,					/**< R6 arbiter */
	E_IM_MXIC_R_ARBITER_GR_R7,					/**< R7 arbiter */
	E_IM_MXIC_R_ARBITER_GR_MAX					/**< Enumeration stopper */
} EImMxicRArbiterGr;

/**	Slot selection. */
typedef enum {
	E_IM_MXIC_SLOT_0 = 0,						/**< Slot0 */
	E_IM_MXIC_SLOT_1,							/**< Slot1 */
	E_IM_MXIC_SLOT_2,							/**< Slot2 */
	E_IM_MXIC_SLOT_3,							/**< Slot3 */
	E_IM_MXIC_SLOT_MAX							/**< Enumeration stopper */
} EImMxicSlot;

/**	Slot level control selection. */
typedef enum {
	E_IM_MXIC_SLOT_LEVEL_CTRL_0 = 0,			/**< Slot level control block 0 */
	E_IM_MXIC_SLOT_LEVEL_CTRL_1,				/**< Slot level control block 1 */
	E_IM_MXIC_SLOT_LEVEL_CTRL_2,				/**< Slot level control block 2 */
	E_IM_MXIC_SLOT_LEVEL_CTRL_MAX				/**< Enumeration stopper */
} EImMxicSlotLevelCtrl;

/**	Port selection. */
typedef enum {
	E_IM_MXIC_PORT_0 = 0,						/**< Port-0	*/
	E_IM_MXIC_PORT_1,							/**< Port-1	*/
	E_IM_MXIC_PORT_2,							/**< Port-2	*/
	E_IM_MXIC_PORT_3,							/**< Port-3	*/
	E_IM_MXIC_PORT_MAX							/**< Enumeration stopper */
} EImMxicPort;

/**	Port selection.  (group) */
typedef enum {
	E_IM_MXIC_PORT_GR_0 = 0,					/**< Port-0	*/
	E_IM_MXIC_PORT_GR_1,						/**< Port-1	*/
	E_IM_MXIC_PORT_GR_MAX						/**< Enumeration stopper */
} EImMxicPortGr;

/** Slave number. */
typedef enum {
	E_IM_MXIC_SLAVE_NUMBER_1 = 0,				/**< Slave number-1 */
	E_IM_MXIC_SLAVE_NUMBER_2,					/**< Slave number-2 */
	E_IM_MXIC_SLAVE_NUMBER_3,					/**< Slave number-3 */
	E_IM_MXIC_SLAVE_NUMBER_4,					/**< Slave number-4 */
	E_IM_MXIC_SLAVE_NUMBER_MAX					/**< Enumeration stopper */
} EImMxicSlaveNumber;

/**	Slot assigned to a port. */
typedef enum {
	E_IM_MXIC_PORT_ASSIGN_SLOT_0     = 0,		/**< Slot-0 is assigned to Port-0.		*/
	E_IM_MXIC_PORT_ASSIGN_SLOT_0_1   = 1,		/**< Slot-0~1 is assigned to Port-0.	*/
	E_IM_MXIC_PORT_ASSIGN_SLOT_0_1_2 = 2,		/**< Slot-0~2 is assigned to Port-0.	*/
	E_IM_MXIC_PORT_ASSIGN_SLOT_ALL   = 3,		/**< Slot-0~3 is assigned to Port-0.	*/
	E_IM_MXIC_PORT_ASSIGN_MAX					/**< Enumeration stopper */
} EImMxicPortAssign;

/** Mask group selection. */
typedef enum{
	E_IM_MXIC_MASK_GROUP_A = 0,					/**< Mask group A */
	E_IM_MXIC_MASK_GROUP_B,						/**< Mask group B */
	E_IM_MXIC_MASK_GROUP_MAX					/**< Enumeration stopper */
} EImMxicMaskGroup;

/**	Level selection. */
typedef enum {
	E_IM_MXIC_LEVEL_0 = 0,						/**< Level-0	*/
	E_IM_MXIC_LEVEL_1,							/**< Level-1	*/
	E_IM_MXIC_LEVEL_2,							/**< Level-2	*/
	E_IM_MXIC_LEVEL_3,							/**< Level-3	*/
	E_IM_MXIC_LEVEL_MAX							/**< Enumeration stopper */
} EImMxicLevel;


/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
/** Master assignment into all the slave slots of W arbiter. */
typedef struct{
	UCHAR		slot0[D_IM_MXIC_SLOT_SIZE_8];	/**< Write master assignment in slot0 */
	UCHAR		slot1[D_IM_MXIC_SLOT_SIZE_8];	/**< Write master assignment in slot1 */
	UCHAR		slot2[D_IM_MXIC_SLOT_SIZE_8];	/**< Write master assignment in slot2 */
	UCHAR		slot3[D_IM_MXIC_SLOT_SIZE_8];	/**< Write master assignment in slot3 */
} TImMxicWArbiterAssign;

/** Master assignment into all the slave slots of R arbiter. */
typedef struct{
	UCHAR		slot0[D_IM_MXIC_SLOT_SIZE_8];	/**< Read master assignment in slot0 */
	UCHAR		slot1[D_IM_MXIC_SLOT_SIZE_8];	/**< Read master assignment in slot1 */
	UCHAR		slot2[D_IM_MXIC_SLOT_SIZE_8];	/**< Read master assignment in slot2 */
	UCHAR		slot3[D_IM_MXIC_SLOT_SIZE_8];	/**< Read master assignment in slot3 */
} TImMxicRArbiterAssign;

/** Master assignment into all the slave slots of each port of W arbiter. */
typedef struct{
	TImMxicWArbiterAssign		port[E_IM_MXIC_PORT_MAX];	/**< Write master assignment in port */
} TImMxicWArbiterAssignPort;

/** Master assignment into all the slave slots of each port of R arbiter. */
typedef struct{
	TImMxicRArbiterAssign		port[E_IM_MXIC_PORT_MAX];	/**< Read master assignment in port */
} TImMxicRArbiterAssignPort;

/** Master assignment into all the slave slots of W(group) arbiter. */
typedef struct{
	UCHAR		slot[D_IM_MXIC_SLOT_SIZE_8];	/**< Write master assignment in slot0 */
} TImMxicWArbiterAssignGr;

/** Master assignment into all the slave slots of R(group) arbiter. */
typedef struct{
	UCHAR		slot[D_IM_MXIC_SLOT_SIZE_8];	/**< Read master assignment in slot0 */
} TImMxicRArbiterAssignGr;

/** Master assignment into all the slots of all arbiter. */
typedef struct{
	TImMxicWArbiterAssignPort	wArbiter[E_IM_MXIC_W_ARBITER_MAX];	/**< Slave Write master assignment in W arbiter */
	TImMxicRArbiterAssignPort	rArbiter[E_IM_MXIC_R_ARBITER_MAX];	/**< Slave Read master assignment in R arbiter */
} TImMxicAllArbiterAssign;

/** Setting of configration start enable */
typedef struct{
	UCHAR		slW1ConfigOnFlg;			/**< TCFMD.bit.TENW_1: Configration start enable flag in slave W1 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slW2ConfigOnFlg;			/**< TCFMD.bit.TENW_2: Configration start enable flag in slave W2 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slW3ConfigOnFlg;			/**< TCFMD.bit.TENW_3: Configration start enable flag in slave W3 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slW4ConfigOnFlg;			/**< TCFMD.bit.TENW_4: Configration start enable flag in slave W4 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slR1ConfigOnFlg;			/**< TCFMD.bit.TENR_1: Configration start enable flag in slave R1 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slR2ConfigOnFlg;			/**< TCFMD.bit.TENR_2: Configration start enable flag in slave R2 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slR3ConfigOnFlg;			/**< TCFMD.bit.TENR_3: Configration start enable flag in slave R3 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		slR4ConfigOnFlg;			/**< TCFMD.bit.TENR_4: Configration start enable flag in slave R4 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW0ConfigOnFlg;			/**< TGCFMD.bit.TEGW_0: Configration start enable flag in group W0 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW1ConfigOnFlg;			/**< TGCFMD.bit.TEGW_1: Configration start enable flag in group W1 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW2ConfigOnFlg;			/**< TGCFMD.bit.TEGW_2: Configration start enable flag in group W2 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW3ConfigOnFlg;			/**< TGCFMD.bit.TEGW_3: Configration start enable flag in group W3 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW4ConfigOnFlg;			/**< TGCFMD.bit.TEGW_4: Configration start enable flag in group W4 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW5ConfigOnFlg;			/**< TGCFMD.bit.TEGW_5: Configration start enable flag in group W5 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW6ConfigOnFlg;			/**< TGCFMD.bit.TEGW_6: Configration start enable flag in group W6 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grW7ConfigOnFlg;			/**< TGCFMD.bit.TEGW_7: Configration start enable flag in group W7 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR0ConfigOnFlg;			/**< TGCFMD.bit.TEGR_0: Configration start enable flag in group R0 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR1ConfigOnFlg;			/**< TGCFMD.bit.TEGR_1: Configration start enable flag in group R1 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR2ConfigOnFlg;			/**< TGCFMD.bit.TEGR_2: Configration start enable flag in group R2 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR3ConfigOnFlg;			/**< TGCFMD.bit.TEGR_3: Configration start enable flag in group R3 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR4ConfigOnFlg;			/**< TGCFMD.bit.TEGR_4: Configration start enable flag in group R4 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR5ConfigOnFlg;			/**< TGCFMD.bit.TEGR_5: Configration start enable flag in group R5 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR6ConfigOnFlg;			/**< TGCFMD.bit.TEGR_6: Configration start enable flag in group R6 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		grR7ConfigOnFlg;			/**< TGCFMD.bit.TEGR_7: Configration start enable flag in group R7 arbiter<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
} TImMxicConfigArbiter;

/** Setting of clock enable */
typedef struct {
	UCHAR		clkEnSlave10;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-0 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave11;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-1 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave12;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-2 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave13;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-3 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave20;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-0 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave21;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-1 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave22;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-2 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave23;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-3 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave30;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-0 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave31;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-1 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave32;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-2 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave33;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-3 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave40;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-0 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave41;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-1 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave42;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-2 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnSlave43;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-3 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup0;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-0 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup1;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-1 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup2;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-2 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup3;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-3 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup4;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-4 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup5;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-5 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup6;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-6 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnGroup7;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-7 arbiter.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnDecErr;					/**< TCKEN.bit.TCKSEN: Clock enable of decode error block.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR		clkEnMonitor;					/**< TCKEN.bit.TCKMEN: Clock enable of monitor and memory access function block.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
} TImMxicClock;

/** Setting of acceptance capability */
typedef struct {
	UCHAR		wCapability[E_IM_MXIC_W_ARBITER_MAX][E_IM_MXIC_PORT_MAX];				/**< TACPTCW.bit.TACPTCW*: Acceptance capability of write port. (1~8)<br> */
	UCHAR		rCapability[E_IM_MXIC_R_ARBITER_MAX][E_IM_MXIC_PORT_MAX];				/**< TACPTCR.bit.TACPTCR*: Acceptance capability of read port. (1~8)<br> */
	UCHAR		wCapabilityGr[E_IM_MXIC_W_ARBITER_GR_MAX][E_IM_MXIC_PORT_GR_MAX];		/**< TGACPTCW.bit.TGACPTCW*: Acceptance capability of write port.(group) (1~8)<br> */
	UCHAR		rCapabilityGr[E_IM_MXIC_R_ARBITER_GR_MAX][E_IM_MXIC_PORT_GR_MAX];		/**< TGACPTCR.bit.TGACPTCR*: Acceptance capability of read port.(group) (1~8)<br> */
} TImMxicAllAcceptanceCapability;

/** Setting of slave area */
typedef struct {
	UINT32		size;							/**< TREGION.bit.TSIZE: Size of slave area.<br> */
	UINT32		address;						/**< TREGION.bit.TSTAD: Start address of slave area.<br> */
} TImMxicSlaveArea;

/** Setting of all slave area */
typedef struct {
	TImMxicSlaveArea		slaveArea[E_IM_MXIC_SLAVE_NUMBER_MAX];	/**< Setting of all slave area.<br> */
} TImMxicAllSlaveArea;

/** Setting of decoding error interruption */
typedef struct {
	UCHAR					wErrIntEn;		/**< TMIE.bit.TDEWE: Enable setting of interruption by the decode error of write channel.<br>
													 <ul><li>@ref D_IM_MXIC_ON
														 <li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR					rErrIntEn;		/**< TMIE.bit.TDERE: Enable setting of interruption by the decode error of read channel.<br>
													 <ul><li>@ref D_IM_MXIC_ON
														 <li>@ref D_IM_MXIC_OFF</ul>  */
	ImMxicDecErrFunc	pCallBack;			/**< Call Back function pointer	for decode error.	*/
} TImMxicDecErrInt;

/** Decode error status */
typedef struct {
	UINT32			wReqAddr;					/**< TDESTW.bit.TDEADW: Decode error demand address of write channel. */
	UINT32			rReqAddr;					/**< TDESTR.bit.TDEADR: Decode error demand address of read channel. */
	UCHAR			wReqMaster;				/**< TDESTW.bit.TDEMNW: Decode error demand master of write channel. */
	UCHAR			rReqMaster;				/**< TDESTR.bit.TDEMNR: Decode error demand master of read channel. */
} TImMxicDecErr;

/** Setting of slot assigned to all ports */
typedef struct {
	EImMxicPortAssign	wAssign[E_IM_MXIC_W_ARBITER_MAX];	/**< TPORTBW.bit.TPORTBW*: Setting of slot assigned to W ports. */
	EImMxicPortAssign	rAssign[E_IM_MXIC_R_ARBITER_MAX];	/**< TPORTBR.bit.TPORTBR*: Setting of slot assigned to R ports. */
} TImMxicAllPortAssign;

/** Slot priority level */
typedef struct{
	UCHAR			priorityLevelType;		/**< TLVL*.bit.LPL*: Priority level type<br>
													<ul><li>@ref D_IM_MXIC_SLOT_PRIORITY_UPPER
														<li>@ref D_IM_MXIC_SLOT_PRIORITY_LOWWER
														<li>@ref D_IM_MXIC_SLOT_PRIORITY_UPPER_ONLY
														<li>@ref D_IM_MXIC_SLOT_PRIORITY_LOWWER_ONLY</ul> */
	UCHAR			upperPriorityLevel;		/**< TLVL*.bit.LPCCL*: Upper priority ratio<br>
													 The setting priority ranges are from 1 to 64("0" value stands for 64) */
	UCHAR			lowerPriorityLevel;		/**< TLVL*.bit.LPCSL*: Lower priority ratio<br>
													 The setting priority ranges are from 1 to 64("0" value stands for 64) */
} TImMxicSlotPriorityLevel;

/** Slot priority level for each port */
typedef struct{
	// W1 arbiter
	TImMxicSlotPriorityLevel level0[E_IM_MXIC_PORT_MAX];				/**< Setting of level 0 control block for each port */
	TImMxicSlotPriorityLevel level1[E_IM_MXIC_PORT_MAX];				/**< Setting of level 1 control block for each port */
	TImMxicSlotPriorityLevel level2[E_IM_MXIC_PORT_MAX];				/**< Setting of level 2 control block for each port */
} TImMxicSlotPriorityLevelPort;

/** Slot priority level in all arbiter */
typedef struct{
	// W arbiter
	TImMxicSlotPriorityLevelPort wLevel[E_IM_MXIC_W_ARBITER_MAX];	/**< Setting of Write arbiter in all arbiter */
	// R arbiter
	TImMxicSlotPriorityLevelPort rLevel[E_IM_MXIC_R_ARBITER_MAX];	/**< Setting of Read arbiter in all arbiter */
} TImMxicAllSlotPriorityLevel;

/** Setting of master transfer mask */
typedef struct{
	USHORT		maskPeriod;					/**< TRMC*.bit.TRMCVP*: Mask period.<br>
													 The setting mask ranges are from 4 to 4096("0" value stands for 4096) */
	UCHAR		maskType;						/**< TRMC*.bit.TRM*: Mask type.<br>
													<ul><li>@ref D_IM_MXIC_MASTER_MASK_OFF
														<li>@ref D_IM_MXIC_MASTER_MASK_ON
														<li>@ref D_IM_MXIC_MASTER_MASK_PERIOD_ON</ul> */
} TImMxicMasterMask;

/** Service history monitor result of port */
typedef struct {
	UCHAR		history[D_IM_MXIC_MAX_MONITOR_HISTORY_NUM];	/**< THST*.bit.THST*: Service history monitor result. */
} TImMxicHistoryMonitor;

/** Service history monitor result of all port */
typedef struct {
	TImMxicHistoryMonitor	wArbiter[E_IM_MXIC_W_ARBITER_MAX][E_IM_MXIC_PORT_MAX];	/**< Service history monitor result of W ports. */
	TImMxicHistoryMonitor	rArbiter[E_IM_MXIC_R_ARBITER_MAX][E_IM_MXIC_PORT_MAX];	/**< Service history monitor result of R ports. */
} TImMxicAllHistoryMonitor;

/** Slot status monitor result of all arbiter */
typedef struct {
	TImMxicWArbiterAssignPort	wArbiter[E_IM_MXIC_W_ARBITER_MAX];					/**< TSLSW.bit.SLOTSW*: Slot status monitor result of W(slave) arbiter. */
	TImMxicRArbiterAssignPort	rArbiter[E_IM_MXIC_R_ARBITER_MAX];					/**< TSLSR.bit.SLOTSR*: Slot status monitor result of R(slave) arbiter. */
	TImMxicWArbiterAssignGr	wArbiterGr[E_IM_MXIC_W_ARBITER_GR_MAX];			/**< TGSLSW.bit.GSLOTSW_*: Slot status monitor result of W(group) arbiter. */
	TImMxicRArbiterAssignGr	rArbiterGr[E_IM_MXIC_R_ARBITER_GR_MAX];			/**< TGSLSR.bit.GSLOTSR_*: Slot status monitor result of R(group) arbiter. */
} TImMxicAllSlotStatusMonitor;

/** All master status monitor result */
typedef struct {
	UCHAR		wMaster[D_IM_MXIC_MAX_W_MASTER_NUM];	/**< TMSTW.bit.TMSTW_*: write master request status.	*/
	UCHAR		rMaster[D_IM_MXIC_MAX_R_MASTER_NUM];	/**< TMSTR.bit.TMSTR_*: read master request status.	*/
} TImMxicMasterStatusMonitor;

/** Selection monitor target */
typedef struct {
	UCHAR		monitorSel;					/**< TMSEL.bit.TMAS*: Selection monitor function.<br>
													<ul><li>@ref D_IM_MXIC_MONITOR_TRANSFER
														<li>@ref D_IM_MXIC_MONITOR_ACCESS</ul> */
	UINT32		monitorTarget;					/**< TMSEL.bit.TMSEL*: Selection monitor target from all arbiter or all master.	*/
} TImMxicMonitorTarget;

/** Access count or transfer amount monitor parameter */
typedef struct{
	UCHAR					startCondition;							/**< TMMD.bit.TMON: Selection monitor start condition.<br>
																			<ul><li>@ref D_IM_MXIC_MONITOR_START_OFF
																				<li>@ref D_IM_MXIC_MONITOR_START_ON
																				<li>@ref D_IM_MXIC_MONITOR_START_ASSERT
																				<li>@ref D_IM_MXIC_MONITOR_START_TRG</ul> */
	UCHAR					endCondition;								/**< TMMD.bit.TMOFF: Selection monitor end condition.<br>
																			<ul><li>@ref D_IM_MXIC_MONITOR_ENDLESS
																				<li>@ref D_IM_MXIC_MONITOR_END_ASSERT
																				<li>@ref D_IM_MXIC_MONITOR_END_LIMIT</ul> */
	UCHAR					updateEnable;								/**< TMMD.bit.TMUP: Monitor update terminal enable.<br>
																			<ul><li>@ref D_IM_MXIC_ON
																				<li>@ref D_IM_MXIC_OFF</ul> */
	UCHAR					updateTriggerInterval;					/**< TMMD.bit.TMUPC: Update trigger generation interval.<br>
																			<ul><li>@ref D_IM_MXIC_MONITOR_UPDATE_1
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_8
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_16
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_32
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_64
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_128
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_256
																				<li>@ref D_IM_MXIC_MONITOR_UPDATE_512</ul> */
	UCHAR					updateClearEn;							/**< TMMD.bit.TMCLR: Selection monitor clear by update trigger.<br>
																			<ul><li>@ref D_IM_MXIC_ON
																				<li>@ref D_IM_MXIC_OFF</ul> */
	UCHAR					startClearEn;								/**< TMMD.bit.TMCLRC: Selection monitor clear by asserting of a monitor start terminal.<br>
																			<ul><li>@ref D_IM_MXIC_ON
																				<li>@ref D_IM_MXIC_OFF</ul> */
	UCHAR					cntVal;									/**< TMMD.bit.TMRSEL: Selection switch of reading value.<br>
																			<ul><li>@ref D_IM_MXIC_VALUE_WHEN_UPDATE_TRG
																				<li>@ref D_IM_MXIC_TRANS_COUNT_VALUE</ul> */
	UCHAR					limitAccessTrans;							/**< TMLIMSEL.bit.TMALMS: Selection limit judgment<br>
																			<ul><li>@ref D_IM_MXIC_MONITOR_TRANSFER
																				<li>@ref D_IM_MXIC_MONITOR_ACCESS</ul> */
	UINT32					limitDetectionTarget;						/**< TMLIMSEL.bit.TLIMSEL: Selection limit target from all arbiter or all master.<br>
																		<ul><li>@ref D_IM_MXIC_3_W_STAT
																			<li>@ref D_IM_MXIC_3_W_IIP_A
																			<li>@ref D_IM_MXIC_3_W_IIP_B
																			<li>@ref D_IM_MXIC_3_W_IIP_C
																			<li>@ref D_IM_MXIC_3_W_SHDR_A
																			<li>@ref D_IM_MXIC_3_W_SHDR_B
																			<li>@ref D_IM_MXIC_3_W_SHDR_C
																			<li>@ref D_IM_MXIC_3_W_ME
																			<li>@ref D_IM_MXIC_3_W_IPU_A
																			<li>@ref D_IM_MXIC_3_W_IPU_C
																			<li>@ref D_IM_MXIC_3_W_IPU_D
																			<li>@ref D_IM_MXIC_3_W_IPU_E
																			<li>@ref D_IM_MXIC_3_W_DSP_A
																			<li>@ref D_IM_MXIC_3_W_DSP_B
																			<li>@ref D_IM_MXIC_3_W_GPU
																			<li>@ref D_IM_MXIC_3_W_DW
																			<li>@ref D_IM_MXIC_3_W_JPEG
																			<li>@ref D_IM_MXIC_3_W_RAW
																			<li>@ref D_IM_MXIC_3_W_GROUP0_M0
																			<li>@ref D_IM_MXIC_3_W_GROUP0_M1
																			<li>@ref D_IM_MXIC_3_W_ELA
																			<li>@ref D_IM_MXIC_3_W_XCH
																			<li>@ref D_IM_MXIC_3_W_FPT_0
																			<li>@ref D_IM_MXIC_3_W_FPT_1
																			<li>@ref D_IM_MXIC_3_R_STAT
																			<li>@ref D_IM_MXIC_3_R_IIP_A
																			<li>@ref D_IM_MXIC_3_R_IIP_B
																			<li>@ref D_IM_MXIC_3_R_IIP_C
																			<li>@ref D_IM_MXIC_3_R_SHDR_A
																			<li>@ref D_IM_MXIC_3_R_SHDR_B
																			<li>@ref D_IM_MXIC_3_R_SHDR_C
																			<li>@ref D_IM_MXIC_3_R_SHDR_D
																			<li>@ref D_IM_MXIC_3_R_ME
																			<li>@ref D_IM_MXIC_3_R_IPU_A
																			<li>@ref D_IM_MXIC_3_R_IPU_B
																			<li>@ref D_IM_MXIC_3_R_IPU_C
																			<li>@ref D_IM_MXIC_3_R_IPU_D
																			<li>@ref D_IM_MXIC_3_R_DSP_A
																			<li>@ref D_IM_MXIC_3_R_DSP_B
																			<li>@ref D_IM_MXIC_3_R_GPU
																			<li>@ref D_IM_MXIC_3_R_JPEG
																			<li>@ref D_IM_MXIC_3_R_RAW
																			<li>@ref D_IM_MXIC_3_R_RDMA
																			<li>@ref D_IM_MXIC_3_R_GROUP0_M0
																			<li>@ref D_IM_MXIC_3_R_GROUP0_M1
																			<li>@ref D_IM_MXIC_3_R_ELA
																			<li>@ref D_IM_MXIC_3_R_XCH
																			<li>@ref D_IM_MXIC_3_R_FPT_0
																			<li>@ref D_IM_MXIC_3_R_FPT_1
																			<li>@ref D_IM_MXIC_SLAVE_W1_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_W1_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_W1_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_W1_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_W2_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_W2_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_W2_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_W2_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_W3_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_W3_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_W3_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_W3_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_W4_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_W4_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_W4_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_W4_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_R1_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_R1_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_R1_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_R1_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_R2_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_R2_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_R2_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_R2_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_R3_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_R3_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_R3_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_R3_PORT3
																			<li>@ref D_IM_MXIC_SLAVE_R4_PORT0
																			<li>@ref D_IM_MXIC_SLAVE_R4_PORT1
																			<li>@ref D_IM_MXIC_SLAVE_R4_PORT2
																			<li>@ref D_IM_MXIC_SLAVE_R4_PORT3
																			<li>@ref D_IM_MXIC_TARGET_NOTHING</ul> */
	UINT32					limit;										/**< TMLIMIT.bit.TMLIMT: Limiting value of amount of transfer data.<br>
																			 Setting values are from 0 to 256*256*256*256-1(bit). "0" value stands for no limit.<br>
																			 When limitAccessTrans is D_IM_MXIC_MONITOR_TRANSFER, please set the value by the unit of 256 bytes.  */
	TImMxicMonitorTarget	target[D_IM_MXIC_MAX_MONITOR_TARGET_NUM];	/**< Selection monitor target. */
	// CallBack function
	VP_CALLBACK				pCallBack;									/**< Call Back function pointer.<br>
																		     When the monitor end flag(TMIF.TMF) becomes "1", this callback function is called. */
} TImMxicMonitorParameter;

/** All access count or transfer amount monitor */
typedef struct {
	UINT32					count[D_IM_MXIC_MAX_MONITOR_TARGET_NUM];		/**< TMCNT.bit.TMCNT: Monitor result of access count or transfer amount monitor */
} TImMxicAllAccessOrTransMonitor;

/** Write master output port */
typedef struct {
	EImMxicPortGr	ela;				/**< Setting the output port of the JDSELA Master I/F.	*/
	EImMxicPortGr	xch;				/**< Setting the output port of the JDSXH Master I/F.	*/
	EImMxicPortGr	fpt0;				/**< Setting the output port of the FPT Master I/F-0.	*/
	EImMxicPortGr	fpt1;				/**< Setting the output port of the FPT Master I/F-1.	*/
}TImMxicWOutputPort;

/** Read master output port */
typedef struct {
	EImMxicPortGr	ela;				/**< Setting the output port of the JDSELA Master I/F.	*/
	EImMxicPortGr	xch;				/**< Setting the output port of the JDSXH Master I/F.	*/
	EImMxicPortGr	fpt0;				/**< Setting the output port of the FPT Master I/F-0.	*/
	EImMxicPortGr	fpt1;				/**< Setting the output port of the FPT Master I/F-1.	*/
}TImMxicROutputPort;

/** Output port setting */
typedef struct {
	TImMxicWOutputPort	wOutPort;		/**< TPORTMW.bit.TPORTMW_127_64: Write output port setting master channel.	*/
	TImMxicROutputPort	rOutPort;		/**< TPORTMR.bit.TPORTMR_127_64: Read output port setting master channel.	*/
} TImMxicOutputPort;

/** LevelPort all setting. */
typedef struct{
	EImMxicPort					port[D_IM_MXIC_MASTER_NUMBER_MAX-1];		/**< Target port.	*/
	EImMxicLevel				level[D_IM_MXIC_MASTER_NUMBER_MAX-1];		/**< Target level.	*/
} TImMxicArbiterLevelport;

/** LevelPort all setting. */
typedef struct{
	TImMxicArbiterLevelport		wArbiter[E_IM_MXIC_W_ARBITER_MAX];		/**< LevelPort in W arbiter.	*/
	TImMxicArbiterLevelport		rArbiter[E_IM_MXIC_R_ARBITER_MAX];		/**< LevelPort in R arbiter.	*/
} TImMxicAllLevelport;

/** Detection parameters of memory access */
typedef struct {
	UCHAR				startTrigger;			/**< TSASETW.bit.TSATRGW: Start trigger of memory access.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UINT64				master47M1;				/**< TSASETW.bit.TSAMASW47_1: Master of memory access.	*/
	UINT64				master127M64;			/**< TSASETW.bit.TSAMASW127_64: Master of memory access.	*/
	UINT32				startAddress;			/**< TSASETW.bit.TSASADW: Start address of memory access.	*/
	UINT32				endAddress;			/**< TSASETW.bit.TSAEADW: End address of memory access.	*/
	UCHAR				mode;					/**< TSASETW.bit.TSARW: Mode of memory access.<br>
													<ul><li>@ref D_IM_MXIC_ON
														<li>@ref D_IM_MXIC_OFF</ul>  */
	UCHAR				detectMaster;			/**< TSASETW.bit.TSAMNSTW: Detection master of memory access.	*/
	UCHAR				detectAddress;			/**< TSASETW.bit.TSAADSTW: Detection address of memory access.	*/
} TImMxicMemoryAccessParameter;

/** Detection parameters of slave each memory access */
typedef struct {
	TImMxicMemoryAccessParameter	slave[E_IM_MXIC_W_ARBITER_MAX];		/**< TPORTMW.bit.TPORTMW_127_64: Write output port setting master channel.	*/
	VP_CALLBACK						pCallBack;							/**< Call Back function pointer.<br> */
} TImMxicMemoryAccessSlave;

#endif	// __IM_MXIC_DEFINE_H__