/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicutlis.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_UTLIS_H__ 
#define __MXIC_UTLIS_H__ 

#include <klib.h>
#include <string.h>
#include "driver_common.h"
#include "jdsmxic.h"
#include "dd_top.h"
// #include "../Project/PalladiumTest/src/ddimusercustom.h"
#include "ddim_user_custom.h"

#define MXIC_TYPE_UTLIS    (mxic_utlis_get_type())
#define MXIC_UTLIS(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicUtlis))
#define MXIC_IS_UTLIS(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_UTLIS))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return value of processing result
#define MxicUtlis_INPUT_PARAM_ERROR			(D_IM_MXIC | D_DDIM_INPUT_PARAM_ERROR)	/**< Processing result code.<br> Input parameter error. */

// General-purpose definition of register value (Effectiveness selection)
#define MxicUtlis_OFF						(0)			/**< Effectiveness selection of processing.<br> Invalidity	*/
#define MxicUtlis_ON						(1)			/**< Effectiveness selection of processing.<br> Effective	*/

// Monitor start trigger
#define MxicUtlis_MONITOR_START_OFF			(0x00)		/**< Monitor start trigger.<br> Monitor is not executed */
#define MxicUtlis_MONITOR_START_ON			(0x01)		/**< Monitor start trigger.<br> Monitor is started by configuration starting. */
#define MxicUtlis_MONITOR_START_ASSERT		(0x02)		/**< Monitor start trigger.<br> Monitor is started by asserting of a monitor start terminal. */
#define MxicUtlis_MONITOR_START_TRG			(0x03)		/**< Monitor start trigger.<br> Monitor is started by "1" writing to TMONTRG.TONTRG. */

// Monitor end trigger
#define MxicUtlis_MONITOR_ENDLESS			(0x00)		/**< Monitor end trigger.<br> Monitor operation is continued. */
#define MxicUtlis_MONITOR_END_ASSERT		(0x02)		/**< Monitor end trigger.<br> Monitor is ended by asserting of the end terminal of a monitor. */
#define MxicUtlis_MONITOR_END_LIMIT			(0x03)		/**< Monitor end trigger.<br> Monitor is ended by the amount limit judging of transmission. */

// Monitor update trigger interval
#define MxicUtlis_MONITOR_UPDATE_1			(0x00)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal */
#define MxicUtlis_MONITOR_UPDATE_8			(0x01)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 8 times */
#define MxicUtlis_MONITOR_UPDATE_16			(0x02)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 16 times */
#define MxicUtlis_MONITOR_UPDATE_32			(0x03)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 32 times */
#define MxicUtlis_MONITOR_UPDATE_64			(0x04)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 64 times */
#define MxicUtlis_MONITOR_UPDATE_128		(0x05)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 128 times */
#define MxicUtlis_MONITOR_UPDATE_256		(0x06)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 256 times */
#define MxicUtlis_MONITOR_UPDATE_512		(0x07)		/**< Monitor update trigger interval.<br> Assert of monitor update terminal 512 times */

// Monitor processing state
#define MxicUtlis_MONITOR_OPERATION_PROCESS	(0x00)		/**< Monitor processing state.<br> The monitor is not ended. */
#define MxicUtlis_MONITOR_OPERATION_END		(0x01)		/**< Monitor processing state.<br> The monitor is ended. */

// Monitor reading value
#define MxicUtlis_VALUE_WHEN_UPDATE_TRG		(0)			/**< Monitor reading value.<br> Amount of transfer data when update trigger generated */
#define MxicUtlis_TRANS_COUNT_VALUE			(1)			/**< Monitor reading value.<br> Amount of transfer data count value */

// Monitor type
#define MxicUtlis_MONITOR_TRANSFER			(0)			/**< Monitor type.<br> Amount of transfer data */
#define MxicUtlis_MONITOR_ACCESS			(1)			/**< Monitor type.<br> Access count */

// Master priority level
#define MxicUtlis_MASTER_MOVE_LAST			(0x00)		/**< Master priority level.<br> Master moves to the last of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_1				(0x01)		/**< Master priority level.<br> Master moves to the 1st of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_2				(0x02)		/**< Master priority level.<br> Master moves to the 2nd of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_3				(0x03)		/**< Master priority level.<br> Master moves to the 3rd of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_4				(0x04)		/**< Master priority level.<br> Master moves to the 4th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_5				(0x05)		/**< Master priority level.<br> Master moves to the 5th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_6				(0x06)		/**< Master priority level.<br> Master moves to the 6th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_7				(0x07)		/**< Master priority level.<br> Master moves to the 7th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_8				(0x08)		/**< Master priority level.<br> Master moves to the 8th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_9				(0x09)		/**< Master priority level.<br> Master moves to the 9th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_10			(0x0A)		/**< Master priority level.<br> Master moves to the 10th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_11			(0x0B)		/**< Master priority level.<br> Master moves to the 11th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_12			(0x0C)		/**< Master priority level.<br> Master moves to the 12th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_13			(0x0D)		/**< Master priority level.<br> Master moves to the 13th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_14			(0x0E)		/**< Master priority level.<br> Master moves to the 14th of a slot, after receiving service. */
#define MxicUtlis_MASTER_MOVE_15			(0x0F)		/**< Master priority level.<br> Master moves to the 15th of a slot, after receiving service. */

// Slot priority level
#define MxicUtlis_SLOT_PRIORITY_UPPER		(0)			/**< Slot priority level.<br> The priority is on upper level slot */
#define MxicUtlis_SLOT_PRIORITY_LOWWER		(1)			/**< Slot priority level.<br> The priority is on lower level slot */
#define MxicUtlis_SLOT_PRIORITY_UPPER_ONLY	(2)			/**< Slot priority level.<br> The priority is fixed upper level slot */
#define MxicUtlis_SLOT_PRIORITY_LOWWER_ONLY	(3)			/**< Slot priority level.<br> The priority is fixed lower level slot */

// Master mask setting
#define MxicUtlis_MASTER_MASK_OFF			(0x00)		/**< Master mask setting.<br> Transfer request mask OFF */
#define MxicUtlis_MASTER_MASK_ON			(0x01)		/**< Master mask setting.<br> Transfer request mask ON */
#define MxicUtlis_MASTER_MASK_PERIOD_ON		(0x02)		/**< Master mask setting.<br> Transfer request mask ON during specified period. */

// Number of monitor target
#define MxicUtlis_MAX_MONITOR_TARGET_NUM	(4)			/**< The number of monitor target */

// Number of service history
#define MxicUtlis_MAX_MONITOR_HISTORY_NUM	(16)		/**< The number of service history monitor */

// Number of master
#define MxicUtlis_MAX_W_MASTER_NUM			(127 + 1)	/**< The number of slave write master */
#define MxicUtlis_MAX_R_MASTER_NUM			(127 + 1)	/**< The number of slave read master */

// Number of slot on each port
#define MxicUtlis_MAX_W_SLOT_NUM			(4)			/**< The number of slot in write arbiter */
#define MxicUtlis_MAX_R_SLOT_NUM			(4)			/**< The number of slot in read arbiter */

// Slot size
#define MxicUtlis_SLOT_SIZE_8				(8)			/**< Slot size.<br> 8 columns in slot */
#define MxicUtlis_SLOT_SIZE_16				(16)		/**< Slot size.<br> 16 columns in slot */

// MXIC common master number (slave)
#define MxicUtlis_W_RESERVE					(0x00)		/**< Write master number.<br> Reserve.			(W00). */
#define MxicUtlis_R_RESERVE					(0x80)		/**< Read master number.<br> Reserve.			(R00). */

// MXIC0 Write master number (slave)
#define MxicUtlis_0_W_SEN_0					(0x01)		/**< Write master number.<br> SEN0				(W01). */
#define MxicUtlis_0_W_SEN_1					(0x02)		/**< Write master number.<br> SEN1				(W02). */
#define MxicUtlis_0_W_SEN_2					(0x03)		/**< Write master number.<br> SEN2				(W03). */
#define MxicUtlis_0_W_SEN_3					(0x04)		/**< Write master number.<br> SEN3				(W04). */

// MXIC1 Write master number (slave)
#define MxicUtlis_1_W_SRO					(0x01)		/**< Write master number.<br> SRO				(W01). */
#define MxicUtlis_1_W_B2B					(0x02)		/**< Write master number.<br> B2B				(W02). */
#define MxicUtlis_1_W_B2R_A					(0x03)		/**< Write master number.<br> B2RA				(W03). */
#define MxicUtlis_1_W_B2R_B					(0x04)		/**< Write master number.<br> B2RB				(W04). */
#define MxicUtlis_1_W_B2R_C					(0x05)		/**< Write master number.<br> B2RC				(W05). */
#define MxicUtlis_1_W_LTMDT					(0x06)		/**< Write master number.<br> LTMDT				(W06). */
#define MxicUtlis_1_W_NONE_7				(0x07)		/**< Write master number.<br> none				(W07). */
#define MxicUtlis_1_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define MxicUtlis_1_W_NONE_9				(0x09)		/**< Write master number.<br> none				(W09). */
#define MxicUtlis_1_W_R2Y_A					(0x0A)		/**< Write master number.<br> R2YA				(W10). */
#define MxicUtlis_1_W_R2Y_B					(0x0B)		/**< Write master number.<br> R2YB				(W11). */
#define MxicUtlis_1_W_R2Y_C					(0x0C)		/**< Write master number.<br> R2YC				(W12). */
#define MxicUtlis_1_W_R2Y_D					(0x0D)		/**< Write master number.<br> R2YD				(W13). */
#define MxicUtlis_1_W_CNR_A					(0x0E)		/**< Write master number.<br> CNRA				(W14). */
#define MxicUtlis_1_W_CNR_B					(0x0F)		/**< Write master number.<br> CNRB				(W15). */

// MXIC1 Read master number (slave)
#define MxicUtlis_1_R_SRO					(0x81)		/**< Read master number.<br> SRO				(R01). */
#define MxicUtlis_1_R_B2B					(0x82)		/**< Read master number.<br> B2B				(R02). */
#define MxicUtlis_1_R_B2R_A					(0x83)		/**< Read master number.<br> B2RA				(R03). */
#define MxicUtlis_1_R_NONE_4				(0x84)		/**< Read master number.<br> none				(R04). */
#define MxicUtlis_1_R_NONE_5				(0x85)		/**< Read master number.<br> none				(R05). */
#define MxicUtlis_1_R_LTMDT					(0x86)		/**< Read master number.<br> LTMDT				(R06). */
#define MxicUtlis_1_R_LTM_R					(0x87)		/**< Read master number.<br> LTMR				(R07). */
#define MxicUtlis_1_R_LTM_G					(0x88)		/**< Read master number.<br> LTMG				(R08). */
#define MxicUtlis_1_R_LTM_B					(0x89)		/**< Read master number.<br> LTMB				(R09). */
#define MxicUtlis_1_R_R2Y_A					(0x8A)		/**< Read master number.<br> R2YA				(R10). */
#define MxicUtlis_1_R_R2Y_B					(0x8B)		/**< Read master number.<br> R2YB				(R11). */
#define MxicUtlis_1_R_R2Y_C					(0x8C)		/**< Read master number.<br> R2YC				(R12). */
#define MxicUtlis_1_R_NONE_13				(0x8D)		/**< Read master number.<br> none				(R13). */
#define MxicUtlis_1_R_CNR_B					(0x8E)		/**< Read master number.<br> CNRB				(R14). */
#define MxicUtlis_1_R_NONE_15				(0x8F)		/**< Read master number.<br> none				(R15). */

// MXIC2 Write master number (slave)
#define MxicUtlis_2_W_SRO					(0x01)		/**< Write master number.<br> SRO				(W01). */
#define MxicUtlis_2_W_B2B					(0x02)		/**< Write master number.<br> B2B				(W02). */
#define MxicUtlis_2_W_B2R_A					(0x03)		/**< Write master number.<br> B2RA				(W03). */
#define MxicUtlis_2_W_B2R_B					(0x04)		/**< Write master number.<br> B2RB				(W04). */
#define MxicUtlis_2_W_B2R_C					(0x05)		/**< Write master number.<br> B2RC				(W05). */
#define MxicUtlis_2_W_LTMDT					(0x06)		/**< Write master number.<br> LTMDT				(W06). */
#define MxicUtlis_2_W_NONE_7				(0x07)		/**< Write master number.<br> none				(W07). */
#define MxicUtlis_2_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define MxicUtlis_2_W_NONE_9				(0x09)		/**< Write master number.<br> none				(W09). */
#define MxicUtlis_2_W_R2Y_A					(0x0A)		/**< Write master number.<br> R2YA				(W10). */
#define MxicUtlis_2_W_R2Y_B					(0x0B)		/**< Write master number.<br> R2YB				(W11). */
#define MxicUtlis_2_W_R2Y_C					(0x0C)		/**< Write master number.<br> R2YC				(W12). */
#define MxicUtlis_2_W_R2Y_D					(0x0D)		/**< Write master number.<br> R2YD				(W13). */
#define MxicUtlis_2_W_CNR_A					(0x0E)		/**< Write master number.<br> CNRA				(W14). */
#define MxicUtlis_2_W_CNR_B					(0x0F)		/**< Write master number.<br> CNRB				(W15). */

// MXIC2 Read master number (slave)
#define MxicUtlis_2_R_SRO					(0x81)		/**< Read master number.<br> SRO				(R01). */
#define MxicUtlis_2_R_B2B					(0x82)		/**< Read master number.<br> B2B				(R02). */
#define MxicUtlis_2_R_B2R_A					(0x83)		/**< Read master number.<br> B2RA				(R03). */
#define MxicUtlis_2_R_NONE_4				(0x84)		/**< Read master number.<br> none				(R04). */
#define MxicUtlis_2_R_NONE_5				(0x85)		/**< Read master number.<br> none				(R05). */
#define MxicUtlis_2_R_LTMDT					(0x86)		/**< Read master number.<br> LTMDT				(R06). */
#define MxicUtlis_2_R_LTM_R					(0x87)		/**< Read master number.<br> LTMR				(R07). */
#define MxicUtlis_2_R_LTM_G					(0x88)		/**< Read master number.<br> LTMG				(R08). */
#define MxicUtlis_2_R_LTM_B					(0x89)		/**< Read master number.<br> LTMB				(R09). */
#define MxicUtlis_2_R_R2Y_A					(0x8A)		/**< Read master number.<br> R2YA				(R10). */
#define MxicUtlis_2_R_R2Y_B					(0x8B)		/**< Read master number.<br> R2YB				(R11). */
#define MxicUtlis_2_R_R2Y_C					(0x8C)		/**< Read master number.<br> R2YC				(R12). */
#define MxicUtlis_2_R_NONE_13				(0x8D)		/**< Read master number.<br> none				(R13). */
#define MxicUtlis_2_R_CNR_B					(0x8E)		/**< Read master number.<br> CNRB				(R14). */
#define MxicUtlis_2_R_NONE_15				(0x8F)		/**< Read master number.<br> none				(R15). */

// MXIC3 Write master number (slave)
#define MxicUtlis_3_W_STAT					(0x01)		/**< Write master number.<br> STAT				(W01). */
#define MxicUtlis_3_W_IIP_A					(0x02)		/**< Write master number.<br> IIPA				(W02). */
#define MxicUtlis_3_W_IIP_B					(0x03)		/**< Write master number.<br> IIPB				(W03). */
#define MxicUtlis_3_W_IIP_C					(0x04)		/**< Write master number.<br> IIPC				(W04). */
#define MxicUtlis_3_W_SHDR_A				(0x05)		/**< Write master number.<br> SHDRA				(W05). */
#define MxicUtlis_3_W_SHDR_B				(0x06)		/**< Write master number.<br> SHDRB				(W06). */
#define MxicUtlis_3_W_SHDR_C				(0x07)		/**< Write master number.<br> SHDRC				(W07). */
#define MxicUtlis_3_W_NONE_8				(0x08)		/**< Write master number.<br> none				(W08). */
#define MxicUtlis_3_W_ME					(0x09)		/**< Write master number.<br> ME				(W09). */
#define MxicUtlis_3_W_IPU_A					(0x0A)		/**< Write master number.<br> IPU_A				(W10). */
#define MxicUtlis_3_W_NONE_11				(0x0B)		/**< Write master number.<br> none				(W11). */
#define MxicUtlis_3_W_IPU_C					(0x0C)		/**< Write master number.<br> IPU_C				(W12). */
#define MxicUtlis_3_W_IPU_D					(0x0D)		/**< Write master number.<br> IPU_D				(W13). */
#define MxicUtlis_3_W_IPU_E					(0x0E)		/**< Write master number.<br> IPU_E				(W14). */
#define MxicUtlis_3_W_DSP_A					(0x0F)		/**< Write master number.<br> DSP_A				(W15). */
#define MxicUtlis_3_W_DSP_B					(0x10)		/**< Write master number.<br> DSP_B				(W16). */
#define MxicUtlis_3_W_GPU					(0x11)		/**< Write master number.<br> GPU				(W17). */
#define MxicUtlis_3_W_DW					(0x12)		/**< Write master number.<br> DW				(W18). */
#define MxicUtlis_3_W_JPEG					(0x13)		/**< Write master number.<br> JPEG				(W19). */
#define MxicUtlis_3_W_RAW					(0x14)		/**< Write master number.<br> RAW				(W20). */
#define MxicUtlis_3_W_NONE_21				(0x15)		/**< Write master number.<br> none				(W21). */
#define MxicUtlis_3_W_GROUP0_M0				(0x30)		/**< Write master number.<br> Group0 Master0	(W48). */
#define MxicUtlis_3_W_GROUP0_M1				(0x31)		/**< Write master number.<br> Group0 Master1	(W49). */

// MXIC3 Write master number (group)
#define MxicUtlis_3_W_ELA					(0x40)		/**< Write master number.<br> ELA				(W64). */
#define MxicUtlis_3_W_XCH					(0x41)		/**< Write master number.<br> XCH				(W65). */
#define MxicUtlis_3_W_FPT_0					(0x42)		/**< Write master number.<br> FPT0				(W66). */
#define MxicUtlis_3_W_FPT_1					(0x43)		/**< Write master number.<br> FPT1				(W67). */

// MXIC3 Read master number (slave)
#define MxicUtlis_3_R_STAT					(0x81)		/**< Read master number.<br> STAT				(R01). */
#define MxicUtlis_3_R_IIP_A					(0x82)		/**< Read master number.<br> IIPA				(R02). */
#define MxicUtlis_3_R_IIP_B					(0x83)		/**< Read master number.<br> IIPB				(R03). */
#define MxicUtlis_3_R_IIP_C					(0x84)		/**< Read master number.<br> IIPC				(R04). */
#define MxicUtlis_3_R_SHDR_A				(0x85)		/**< Read master number.<br> SHDRA				(R05). */
#define MxicUtlis_3_R_SHDR_B				(0x86)		/**< Read master number.<br> SHDRB				(R06). */
#define MxicUtlis_3_R_SHDR_C				(0x87)		/**< Read master number.<br> SHDRC				(R07). */
#define MxicUtlis_3_R_SHDR_D				(0x88)		/**< Read master number.<br> SHDRD				(R08). */
#define MxicUtlis_3_R_ME					(0x89)		/**< Read master number.<br> ME					(R09). */
#define MxicUtlis_3_R_IPU_A					(0x8A)		/**< Read master number.<br> IPU_A				(R10). */
#define MxicUtlis_3_R_IPU_B					(0x8B)		/**< Read master number.<br> IPU_B				(R11). */
#define MxicUtlis_3_R_IPU_C					(0x8C)		/**< Read master number.<br> IPU_C				(R12). */
#define MxicUtlis_3_R_IPU_D					(0x8D)		/**< Read master number.<br> IPU_D				(R13). */
#define MxicUtlis_3_R_NONE_14				(0x8E)		/**< Read master number.<br> none				(R14). */
#define MxicUtlis_3_R_DSP_A					(0x8F)		/**< Read master number.<br> DSP_A				(R15). */
#define MxicUtlis_3_R_DSP_B					(0x90)		/**< Read master number.<br> DSP_B				(R16). */
#define MxicUtlis_3_R_GPU					(0x91)		/**< Read master number.<br> GPU				(R17). */
#define MxicUtlis_3_R_NONE_18				(0x92)		/**< Read master number.<br> none				(R18). */
#define MxicUtlis_3_R_JPEG					(0x93)		/**< Read master number.<br> JPEG				(R19). */
#define MxicUtlis_3_R_RAW					(0x94)		/**< Read master number.<br> RAW				(R20). */
#define MxicUtlis_3_R_RDMA					(0x95)		/**< Read master number.<br> RDMA				(R21). */
#define MxicUtlis_3_R_GROUP0_M0				(0xB0)		/**< Read master number.<br> Group0 Master0		(R48). */
#define MxicUtlis_3_R_GROUP0_M1				(0xB1)		/**< Read master number.<br> Group0 Master1		(R49). */

// MXIC3 Read master number (group0)
#define MxicUtlis_3_R_ELA					(0xC0)		/**< Write master number.<br> ELA				(R64). */
#define MxicUtlis_3_R_XCH					(0xC1)		/**< Write master number.<br> XCH				(R65). */
#define MxicUtlis_3_R_FPT_0					(0xC2)		/**< Write master number.<br> FPT0				(R66). */
#define MxicUtlis_3_R_FPT_1					(0xC3)		/**< Write master number.<br> FPT1				(R67). */

// MXIC4 Read master number (slave)
#define MxicUtlis_4_R_DISP_A				(0x81)		/**< Write master number.<br> DISPA				(R01). */
#define MxicUtlis_4_R_DISP_B				(0x82)		/**< Write master number.<br> DISPB				(R02). */

// MXIC5 Write master number (slave)
#define MxicUtlis_5_W_EXS_0					(0x01)		/**< Write master number.<br> EXS0				(W01). */
#define MxicUtlis_5_W_EXS_1					(0x02)		/**< Write master number.<br> EXS1				(W02). */
#define MxicUtlis_5_W_NIC					(0x03)		/**< Write master number.<br> NIC				(W03). */
#define MxicUtlis_5_W_BMH_0					(0x04)		/**< Write master number.<br> BMH0				(W04). */
#define MxicUtlis_5_W_BMH_1					(0x05)		/**< Write master number.<br> BMH1				(W05). */

// MXIC5 Read master number (slave)
#define MxicUtlis_5_R_EXS_0					(0x81)		/**< Write master number.<br> EXS0				(R01). */
#define MxicUtlis_5_R_EXS_1					(0x82)		/**< Write master number.<br> EXS1				(R02). */
#define MxicUtlis_5_R_NIC					(0x83)		/**< Write master number.<br> NIC				(R03). */
#define MxicUtlis_5_R_BMH_0					(0x84)		/**< Write master number.<br> BMH0				(R04). */
#define MxicUtlis_5_R_BMH_1					(0x85)		/**< Write master number.<br> BMH1				(R05). */

// MXIC6 Write master number (slave)
#define MxicUtlis_6_W_CA7					(0x01)		/**< Write master number.<br> CA7				(W01). */

// MXIC6 Read master number (slave)
#define MxicUtlis_6_R_CA7					(0x81)		/**< Write master number.<br> CA7				(R01). */

// Monitor target slave write channel
#define MxicUtlis_SLAVE_W1_PORT0			(0x104)		/**< Monitor target slave write channel.<br> W1-Port0 */
#define MxicUtlis_SLAVE_W1_PORT1			(0x105)		/**< Monitor target slave write channel.<br> W1-Port1 */
#define MxicUtlis_SLAVE_W1_PORT2			(0x106)		/**< Monitor target slave write channel.<br> W1-Port2 */
#define MxicUtlis_SLAVE_W1_PORT3			(0x107)		/**< Monitor target slave write channel.<br> W1-Port3 */
#define MxicUtlis_SLAVE_W2_PORT0			(0x108)		/**< Monitor target slave write channel.<br> W2-Port0 */
#define MxicUtlis_SLAVE_W2_PORT1			(0x109)		/**< Monitor target slave write channel.<br> W2-Port1 */
#define MxicUtlis_SLAVE_W2_PORT2			(0x10A)		/**< Monitor target slave write channel.<br> W2-Port2 */
#define MxicUtlis_SLAVE_W2_PORT3			(0x10B)		/**< Monitor target slave write channel.<br> W2-Port3 */
#define MxicUtlis_SLAVE_W3_PORT0			(0x10C)		/**< Monitor target slave write channel.<br> W3-Port0 */
#define MxicUtlis_SLAVE_W3_PORT1			(0x10D)		/**< Monitor target slave write channel.<br> W3-Port1 */
#define MxicUtlis_SLAVE_W3_PORT2			(0x10E)		/**< Monitor target slave write channel.<br> W3-Port2 */
#define MxicUtlis_SLAVE_W3_PORT3			(0x10F)		/**< Monitor target slave write channel.<br> W3-Port3 */
#define MxicUtlis_SLAVE_W4_PORT0			(0x110)		/**< Monitor target slave write channel.<br> W4-Port0 */
#define MxicUtlis_SLAVE_W4_PORT1			(0x111)		/**< Monitor target slave write channel.<br> W4-Port1 */
#define MxicUtlis_SLAVE_W4_PORT2			(0x112)		/**< Monitor target slave write channel.<br> W4-Port2 */
#define MxicUtlis_SLAVE_W4_PORT3			(0x113)		/**< Monitor target slave write channel.<br> W4-Port3 */

// Monitor target slave read channel
#define MxicUtlis_SLAVE_R1_PORT0			(0x184)		/**< Monitor target slave read channel.<br> R1-Port0 */
#define MxicUtlis_SLAVE_R1_PORT1			(0x185)		/**< Monitor target slave read channel.<br> R1-Port1 */
#define MxicUtlis_SLAVE_R1_PORT2			(0x186)		/**< Monitor target slave read channel.<br> R1-Port2 */
#define MxicUtlis_SLAVE_R1_PORT3			(0x187)		/**< Monitor target slave read channel.<br> R1-Port3 */
#define MxicUtlis_SLAVE_R2_PORT0			(0x188)		/**< Monitor target slave read channel.<br> R2-Port0 */
#define MxicUtlis_SLAVE_R2_PORT1			(0x189)		/**< Monitor target slave read channel.<br> R2-Port1 */
#define MxicUtlis_SLAVE_R2_PORT2			(0x18A)		/**< Monitor target slave read channel.<br> R2-Port2 */
#define MxicUtlis_SLAVE_R2_PORT3			(0x18B)		/**< Monitor target slave read channel.<br> R2-Port3 */
#define MxicUtlis_SLAVE_R3_PORT0			(0x18C)		/**< Monitor target slave read channel.<br> R3-Port0 */
#define MxicUtlis_SLAVE_R3_PORT1			(0x18D)		/**< Monitor target slave read channel.<br> R3-Port1 */
#define MxicUtlis_SLAVE_R3_PORT2			(0x18E)		/**< Monitor target slave read channel.<br> R3-Port2 */
#define MxicUtlis_SLAVE_R3_PORT3			(0x18F)		/**< Monitor target slave read channel.<br> R3-Port3 */
#define MxicUtlis_SLAVE_R4_PORT0			(0x190)		/**< Monitor target slave read channel.<br> R4-Port0 */
#define MxicUtlis_SLAVE_R4_PORT1			(0x191)		/**< Monitor target slave read channel.<br> R4-Port1 */
#define MxicUtlis_SLAVE_R4_PORT2			(0x192)		/**< Monitor target slave read channel.<br> R4-Port2 */
#define MxicUtlis_SLAVE_R4_PORT3			(0x193)		/**< Monitor target slave read channel.<br> R4-Port3 */
 
// Monitor target nothing
#define MxicUtlis_TARGET_NOTHING			(0x00)		/**< Monitor target nothing */

// Master number max.
#define MxicUtlis_MASTER_NUMBER_MAX			(0x40)		/**< Max master number.		*/

// The kind of channel which the error generated
#define MxicUtlis_DEC_ERR_CH_W				(0x01)		/**< The decoding error occurred by the write channel.<br> */
#define MxicUtlis_DEC_ERR_CH_R				(0x02)		/**< The decoding error occurred by the read channel.<br> */
#define MxicUtlis_DEC_ERR_CH_RW				(0x04)		/**< The decoding error occurred by the read channel and write channel.<br> */


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define MxicUtlis_GET_TMIF0		(IO_MXIC0.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW0		(IO_MXIC0.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW0		(IO_MXIC0.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR0		(IO_MXIC0.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR0		(IO_MXIC0.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF1		(IO_MXIC1.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW1		(IO_MXIC1.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW1		(IO_MXIC1.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR1		(IO_MXIC1.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR1		(IO_MXIC1.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF2		(IO_MXIC2.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW2		(IO_MXIC2.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW2		(IO_MXIC2.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR2		(IO_MXIC2.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR2		(IO_MXIC2.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF3		(IO_MXIC3.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW3		(IO_MXIC3.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW3		(IO_MXIC3.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR3		(IO_MXIC3.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR3		(IO_MXIC3.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF4		(IO_MXIC4.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW4		(IO_MXIC4.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW4		(IO_MXIC4.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR4		(IO_MXIC4.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR4		(IO_MXIC4.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF5		(IO_MXIC5.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW5		(IO_MXIC5.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW5		(IO_MXIC5.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR5		(IO_MXIC5.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR5		(IO_MXIC5.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */
#define MxicUtlis_GET_TMIF6		(IO_MXIC6.TMIF.word)				/**< Get Interrupt flag register */
#define MxicUtlis_GET_TDEADW6		(IO_MXIC6.TDESTW.bit.TDEADW)		/**< Get Write channel decode error required address */
#define MxicUtlis_GET_TDEMNW6		(IO_MXIC6.TDESTW.bit.TDEMNW)		/**< Get Write channel decode error required master */
#define MxicUtlis_GET_TDEADR6		(IO_MXIC6.TDESTR.bit.TDEADR)		/**< Get Read channel decode error required address */
#define MxicUtlis_GET_TDEMNR6		(IO_MXIC6.TDESTR.bit.TDEMNR)		/**< Get Read channel decode error required master */

//在原.c文件中定义的宏
#define MxicUtlis_DSB()	Dd_ARM_Dsb_Pou()

#ifdef CO_ACT_HCLOCK
#define MxicUtlis_CO_ACT_MXIC_HCLOCK
#endif //CO_ACT_HCLOCK

#ifdef CO_ACT_PCLOCK
#define MxicUtlis_CO_ACT_MXIC_PCLOCK
#endif //CO_ACT_PCLOCK

// Mask bit to identify kind of master.
#define MxicUtlis_MASTER_TYPE_CHECK_MASK	(0x80)
// Write channel identification value.
#define MxicUtlis_MASTER_TYPE_WRITE			(MxicUtlis_W_RESERVE)
// Read channel identification value.
#define MxicUtlis_MASTER_TYPE_READ			(MxicUtlis_R_RESERVE)
// Mask bit to erase bit flag of read channel.
#define MxicUtlis_READ_MASTER_FLG_MASK		(0x7F)


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/**	Slave write or read Arbiter selection. */
typedef enum {
	MxicUtlis_UNIT_0 = 0,						/**< MXIC0				*/
	MxicUtlis_UNIT_1,							/**< MXIC1				*/
	MxicUtlis_UNIT_2,							/**< MXIC2				*/
	MxicUtlis_UNIT_3,							/**< MXIC3				*/
	MxicUtlis_UNIT_4,							/**< MXIC4				*/
	MxicUtlis_UNIT_5,							/**< MXIC5				*/
	MxicUtlis_UNIT_6,							/**< MXIC6				*/
	MxicUtlis_UNIT_MAX							/**< Enumeration stopper */
} ImMxicUnit;

/**	Slave write or read Arbiter selection. */
typedef enum {
	MxicUtlis_WR_ARBITER_W = 0,					/**< Write arbiter */
	MxicUtlis_WR_ARBITER_R,						/**< Read arbiter */
	MxicUtlis_WR_ARBITER_MAX					/**< Enumeration stopper */
} ImMxicWrArbiter;

/**	Slave Spec Arbiter selection. (slave) */
typedef enum {
	MxicUtlis_SPEC_ARBITER_1 = 0,				/**< slave1 arbiter */
	MxicUtlis_SPEC_ARBITER_2,					/**< slave2 Read arbiter */
	MxicUtlis_SPEC_ARBITER_3,					/**< slave3 Read arbiter */
	MxicUtlis_SPEC_ARBITER_4,					/**< slave4 Read arbiter */
	MxicUtlis_SPEC_ARBITER_MAX					/**< Enumeration stopper */
} ImMxicSpecArbiter;

/**	Slave write arbiter selection. (slave) */
typedef enum {
	MxicUtlis_W_ARBITER_W1 = 0,					/**< W1 arbiter */
	MxicUtlis_W_ARBITER_W2,						/**< W2 arbiter */
	MxicUtlis_W_ARBITER_W3,						/**< W3 arbiter */
	MxicUtlis_W_ARBITER_W4,						/**< W4 arbiter */
	MxicUtlis_W_ARBITER_MAX						/**< Enumeration stopper */
} ImMxicWArbiter;

/**	Slave read arbiter selection. (slave) */
typedef enum {
	MxicUtlis_R_ARBITER_R1 = 0,					/**< R1 arbiter */
	MxicUtlis_R_ARBITER_R2,						/**< R2 arbiter */
	MxicUtlis_R_ARBITER_R3,						/**< R3 arbiter */
	MxicUtlis_R_ARBITER_R4,						/**< R4 arbiter */
	MxicUtlis_R_ARBITER_MAX						/**< Enumeration stopper */
} ImMxicRArbiter;

/**	Slave Spec Arbiter selection. (group) */
typedef enum {
	MxicUtlis_SPEC_ARBITER_GR_0 = 0,			/**< group0 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_1,				/**< group1 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_2,				/**< group2 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_3,				/**< group3 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_4,				/**< group4 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_5,				/**< group5 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_6,				/**< group6 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_7,				/**< group7 arbiter */
	MxicUtlis_SPEC_ARBITER_GR_MAX				/**< Enumeration stopper */
} ImMxicSpecArbiterGr;

/**	Slave write arbiter selection. (group) */
typedef enum {
	MxicUtlis_W_ARBITER_GR_W0 = 0,				/**< W0 arbiter */
	MxicUtlis_W_ARBITER_GR_W1,					/**< W1 arbiter */
	MxicUtlis_W_ARBITER_GR_W2,					/**< W2 arbiter */
	MxicUtlis_W_ARBITER_GR_W3,					/**< W3 arbiter */
	MxicUtlis_W_ARBITER_GR_W4,					/**< W4 arbiter */
	MxicUtlis_W_ARBITER_GR_W5,					/**< W5 arbiter */
	MxicUtlis_W_ARBITER_GR_W6,					/**< W6 arbiter */
	MxicUtlis_W_ARBITER_GR_W7,					/**< W7 arbiter */
	MxicUtlis_W_ARBITER_GR_MAX					/**< Enumeration stopper */
} MxicWArbiterGr;

/**	Slave read arbiter selection. (group) */
typedef enum {
	MxicUtlis_R_ARBITER_GR_R0 = 0,				/**< R0 arbiter */
	MxicUtlis_R_ARBITER_GR_R1,					/**< R1 arbiter */
	MxicUtlis_R_ARBITER_GR_R2,					/**< R2 arbiter */
	MxicUtlis_R_ARBITER_GR_R3,					/**< R3 arbiter */
	MxicUtlis_R_ARBITER_GR_R4,					/**< R4 arbiter */
	MxicUtlis_R_ARBITER_GR_R5,					/**< R5 arbiter */
	MxicUtlis_R_ARBITER_GR_R6,					/**< R6 arbiter */
	MxicUtlis_R_ARBITER_GR_R7,					/**< R7 arbiter */
	MxicUtlis_R_ARBITER_GR_MAX					/**< Enumeration stopper */
} MxicRArbiterGr;

/**	Slot selection. */
typedef enum {
	MxicUtlis_SLOT_0 = 0,						/**< Slot0 */
	MxicUtlis_SLOT_1,							/**< Slot1 */
	MxicUtlis_SLOT_2,							/**< Slot2 */
	MxicUtlis_SLOT_3,							/**< Slot3 */
	MxicUtlis_SLOT_MAX							/**< Enumeration stopper */
} ImMxicSlot;

/**	Slot level control selection. */
typedef enum {
	MxicUtlis_SLOT_LEVEL_CTRL_0 = 0,			/**< Slot level control block 0 */
	MxicUtlis_SLOT_LEVEL_CTRL_1,				/**< Slot level control block 1 */
	MxicUtlis_SLOT_LEVEL_CTRL_2,				/**< Slot level control block 2 */
	MxicUtlis_SLOT_LEVEL_CTRL_MAX				/**< Enumeration stopper */
} MxicSlotLevelCtrl;

/**	Port selection. */
typedef enum {
	MxicUtlis_PORT_0 = 0,						/**< Port-0	*/
	MxicUtlis_PORT_1,							/**< Port-1	*/
	MxicUtlis_PORT_2,							/**< Port-2	*/
	MxicUtlis_PORT_3,							/**< Port-3	*/
	MxicUtlis_PORT_MAX							/**< Enumeration stopper */
} ImMxicPort;

/**	Port selection.  (group) */
typedef enum {
	MxicUtlis_PORT_GR_0 = 0,					/**< Port-0	*/
	MxicUtlis_PORT_GR_1,						/**< Port-1	*/
	MxicUtlis_PORT_GR_MAX						/**< Enumeration stopper */
} ImMxicPortGr;

/** Slave number. */
typedef enum {
	MxicUtlis_SLAVE_NUMBER_1 = 0,				/**< Slave number-1 */
	MxicUtlis_SLAVE_NUMBER_2,					/**< Slave number-2 */
	MxicUtlis_SLAVE_NUMBER_3,					/**< Slave number-3 */
	MxicUtlis_SLAVE_NUMBER_4,					/**< Slave number-4 */
	MxicUtlis_SLAVE_NUMBER_MAX					/**< Enumeration stopper */
} ImMxicSlaveNumber;

/**	Slot assigned to a port. */
typedef enum {
	MxicUtlis_PORT_ASSIGN_SLOT_0     = 0,		/**< Slot-0 is assigned to Port-0.		*/
	MxicUtlis_PORT_ASSIGN_SLOT_0_1   = 1,		/**< Slot-0~1 is assigned to Port-0.	*/
	MxicUtlis_PORT_ASSIGN_SLOT_0_1_2 = 2,		/**< Slot-0~2 is assigned to Port-0.	*/
	MxicUtlis_PORT_ASSIGN_SLOT_ALL   = 3,		/**< Slot-0~3 is assigned to Port-0.	*/
	MxicUtlis_PORT_ASSIGN_MAX					/**< Enumeration stopper */
} ImMxicPortAssign;

/** Mask group selection. */
typedef enum{
	MxicUtlis_MASK_GROUP_A = 0,					/**< Mask group A */
	MxicUtlis_MASK_GROUP_B,						/**< Mask group B */
	MxicUtlis_MASK_GROUP_MAX					/**< Enumeration stopper */
} ImMxicMaskGroup;

/**	Level selection. */
typedef enum {
	MxicUtlis_LEVEL_0 = 0,						/**< Level-0	*/
	MxicUtlis_LEVEL_1,							/**< Level-1	*/
	MxicUtlis_LEVEL_2,							/**< Level-2	*/
	MxicUtlis_LEVEL_3,							/**< Level-3	*/
	MxicUtlis_LEVEL_MAX							/**< Enumeration stopper */
} ImMxicLevel;


typedef void (*ImMxicDecErrFunc)(kuchar chType);	/**< Type is defined to callback function pointer for decode error.<br>
															 Decode error information is initialized after the end of processing of a Callback function.<br>
															 For this reason, please be sure to use an @ref mxic_master_slave_get_decode_error function from a Callback function and to refer to error information. <br>
															 The meaning of the argument is as follows.<br>
															 - kuchar chType: The kind of channel which the error generated.<br>
																<ul><li>@ref MxicUtlis_DEC_ERR_CH_W
																	<li>@ref MxicUtlis_DEC_ERR_CH_R
																	<li>@ref MxicUtlis_DEC_ERR_CH_RW</ul> */


/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
/** Master assignment into all the slave slots of W arbiter. */
typedef struct{
	kuchar		slot0[MxicUtlis_SLOT_SIZE_8];	/**< Write master assignment in slot0 */
	kuchar		slot1[MxicUtlis_SLOT_SIZE_8];	/**< Write master assignment in slot1 */
	kuchar		slot2[MxicUtlis_SLOT_SIZE_8];	/**< Write master assignment in slot2 */
	kuchar		slot3[MxicUtlis_SLOT_SIZE_8];	/**< Write master assignment in slot3 */
} MxicWArbiterAssign;

/** Master assignment into all the slave slots of R arbiter. */
typedef struct{
	kuchar		slot0[MxicUtlis_SLOT_SIZE_8];	/**< Read master assignment in slot0 */
	kuchar		slot1[MxicUtlis_SLOT_SIZE_8];	/**< Read master assignment in slot1 */
	kuchar		slot2[MxicUtlis_SLOT_SIZE_8];	/**< Read master assignment in slot2 */
	kuchar		slot3[MxicUtlis_SLOT_SIZE_8];	/**< Read master assignment in slot3 */
} MxicRArbiterAssign;

/** Master assignment into all the slave slots of each port of W arbiter. */
typedef struct{
	MxicWArbiterAssign		port[MxicUtlis_PORT_MAX];	/**< Write master assignment in port */
} MxicWarbiterAssignPort;

/** Master assignment into all the slave slots of each port of R arbiter. */
typedef struct{
	MxicRArbiterAssign		port[MxicUtlis_PORT_MAX];	/**< Read master assignment in port */
} MxicRarbiterAssignPort;

/** Master assignment into all the slave slots of W(group) arbiter. */
typedef struct{
	kuchar		slot[MxicUtlis_SLOT_SIZE_8];	/**< Write master assignment in slot0 */
} MxicWarbiterAssignGr;

/** Master assignment into all the slave slots of R(group) arbiter. */
typedef struct{
	kuchar		slot[MxicUtlis_SLOT_SIZE_8];	/**< Read master assignment in slot0 */
} MxicRarbiterAssignGr;

/** Master assignment into all the slots of all arbiter. */
typedef struct{
	MxicWarbiterAssignPort	wArbiter[MxicUtlis_W_ARBITER_MAX];	/**< Slave Write master assignment in W arbiter */
	MxicRarbiterAssignPort	rArbiter[MxicUtlis_R_ARBITER_MAX];	/**< Slave Read master assignment in R arbiter */
} MxicAllArbiterAssign;

/** Setting of configration start enable */
typedef struct{
	kuchar		slW1ConfigOnFlg;			/**< TCFMD.bit.TENW_1: Configration start enable flag in slave W1 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slW2ConfigOnFlg;			/**< TCFMD.bit.TENW_2: Configration start enable flag in slave W2 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slW3ConfigOnFlg;			/**< TCFMD.bit.TENW_3: Configration start enable flag in slave W3 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slW4ConfigOnFlg;			/**< TCFMD.bit.TENW_4: Configration start enable flag in slave W4 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slR1ConfigOnFlg;			/**< TCFMD.bit.TENR_1: Configration start enable flag in slave R1 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slR2ConfigOnFlg;			/**< TCFMD.bit.TENR_2: Configration start enable flag in slave R2 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slR3ConfigOnFlg;			/**< TCFMD.bit.TENR_3: Configration start enable flag in slave R3 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		slR4ConfigOnFlg;			/**< TCFMD.bit.TENR_4: Configration start enable flag in slave R4 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW0ConfigOnFlg;			/**< TGCFMD.bit.TEGW_0: Configration start enable flag in group W0 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW1ConfigOnFlg;			/**< TGCFMD.bit.TEGW_1: Configration start enable flag in group W1 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW2ConfigOnFlg;			/**< TGCFMD.bit.TEGW_2: Configration start enable flag in group W2 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW3ConfigOnFlg;			/**< TGCFMD.bit.TEGW_3: Configration start enable flag in group W3 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW4ConfigOnFlg;			/**< TGCFMD.bit.TEGW_4: Configration start enable flag in group W4 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW5ConfigOnFlg;			/**< TGCFMD.bit.TEGW_5: Configration start enable flag in group W5 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW6ConfigOnFlg;			/**< TGCFMD.bit.TEGW_6: Configration start enable flag in group W6 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grW7ConfigOnFlg;			/**< TGCFMD.bit.TEGW_7: Configration start enable flag in group W7 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR0ConfigOnFlg;			/**< TGCFMD.bit.TEGR_0: Configration start enable flag in group R0 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR1ConfigOnFlg;			/**< TGCFMD.bit.TEGR_1: Configration start enable flag in group R1 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR2ConfigOnFlg;			/**< TGCFMD.bit.TEGR_2: Configration start enable flag in group R2 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR3ConfigOnFlg;			/**< TGCFMD.bit.TEGR_3: Configration start enable flag in group R3 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR4ConfigOnFlg;			/**< TGCFMD.bit.TEGR_4: Configration start enable flag in group R4 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR5ConfigOnFlg;			/**< TGCFMD.bit.TEGR_5: Configration start enable flag in group R5 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR6ConfigOnFlg;			/**< TGCFMD.bit.TEGR_6: Configration start enable flag in group R6 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		grR7ConfigOnFlg;			/**< TGCFMD.bit.TEGR_7: Configration start enable flag in group R7 arbiter<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
} ImMxicConfigArbiter;

/** Setting of clock enable */
typedef struct {
	kuchar		clkEnSlave10;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-0 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave11;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-1 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave12;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-2 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave13;				/**< TCKENP.bit.TCKENP_1: Clock enable of slave-1 port-3 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave20;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-0 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave21;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-1 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave22;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-2 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave23;				/**< TCKENP.bit.TCKENP_2: Clock enable of slave-2 port-3 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave30;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-0 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave31;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-1 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave32;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-2 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave33;				/**< TCKENP.bit.TCKENP_3: Clock enable of slave-3 port-3 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave40;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-0 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave41;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-1 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave42;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-2 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnSlave43;				/**< TCKENP.bit.TCKENP_4: Clock enable of slave-4 port-3 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup0;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-0 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup1;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-1 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup2;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-2 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup3;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-3 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup4;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-4 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup5;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-5 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup6;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-6 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnGroup7;					/**< TGCKEN.bit.TGCKSEN: Clock enable of group-7 arbiter.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnDecErr;					/**< TCKEN.bit.TCKSEN: Clock enable of decode error block.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar		clkEnMonitor;					/**< TCKEN.bit.TCKMEN: Clock enable of monitor and memory access function block.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
} ImMxicClock;

/** Setting of acceptance capability */
typedef struct {
	kuchar		wCapability[MxicUtlis_W_ARBITER_MAX][MxicUtlis_PORT_MAX];				/**< TACPTCW.bit.TACPTCW*: Acceptance capability of write port. (1~8)<br> */
	kuchar		rCapability[MxicUtlis_R_ARBITER_MAX][MxicUtlis_PORT_MAX];				/**< TACPTCR.bit.TACPTCR*: Acceptance capability of read port. (1~8)<br> */
	kuchar		wCapabilityGr[MxicUtlis_W_ARBITER_GR_MAX][MxicUtlis_PORT_GR_MAX];		/**< TGACPTCW.bit.TGACPTCW*: Acceptance capability of write port.(group) (1~8)<br> */
	kuchar		rCapabilityGr[MxicUtlis_R_ARBITER_GR_MAX][MxicUtlis_PORT_GR_MAX];		/**< TGACPTCR.bit.TGACPTCR*: Acceptance capability of read port.(group) (1~8)<br> */
} MxicAllAcceptanceCapability;

/** Setting of slave area */
typedef struct {
	kuint32		size;							/**< TREGION.bit.TSIZE: Size of slave area.<br> */
	kuint32		address;						/**< TREGION.bit.TSTAD: Start address of slave area.<br> */
} ImMxicSlaveArea;

/** Setting of all slave area */
typedef struct {
	ImMxicSlaveArea		slaveArea[MxicUtlis_SLAVE_NUMBER_MAX];	/**< Setting of all slave area.<br> */
} MxicAllSlaveArea;

/** Setting of decoding error interruption */
typedef struct {
	kuchar					wErrIntEn;		/**< TMIE.bit.TDEWE: Enable setting of interruption by the decode error of write channel.<br>
													 <ul><li>@ref MxicUtlis_ON
														 <li>@ref MxicUtlis_OFF</ul>  */
	kuchar					rErrIntEn;		/**< TMIE.bit.TDERE: Enable setting of interruption by the decode error of read channel.<br>
													 <ul><li>@ref MxicUtlis_ON
														 <li>@ref MxicUtlis_OFF</ul>  */
	ImMxicDecErrFunc	pCallBack;			/**< Call Back function pointer	for decode error.	*/
} MxicDecErrInt;

/** Decode error status */
typedef struct {
	kuint32			wReqAddr;					/**< TDESTW.bit.TDEADW: Decode error demand address of write channel. */
	kuint32			rReqAddr;					/**< TDESTR.bit.TDEADR: Decode error demand address of read channel. */
	kuchar			wReqMaster;				/**< TDESTW.bit.TDEMNW: Decode error demand master of write channel. */
	kuchar			rReqMaster;				/**< TDESTR.bit.TDEMNR: Decode error demand master of read channel. */
} ImMxicDecErr;

/** Setting of slot assigned to all ports */
typedef struct {
	ImMxicPortAssign	wAssign[MxicUtlis_W_ARBITER_MAX];	/**< TPORTBW.bit.TPORTBW*: Setting of slot assigned to W ports. */
	ImMxicPortAssign	rAssign[MxicUtlis_R_ARBITER_MAX];	/**< TPORTBR.bit.TPORTBR*: Setting of slot assigned to R ports. */
} MxicAllPortAssign;

/** Slot priority level */
typedef struct{
	kuchar			priorityLevelType;		/**< TLVL*.bit.LPL*: Priority level type<br>
													<ul><li>@ref MxicUtlis_SLOT_PRIORITY_UPPER
														<li>@ref MxicUtlis_SLOT_PRIORITY_LOWWER
														<li>@ref MxicUtlis_SLOT_PRIORITY_UPPER_ONLY
														<li>@ref MxicUtlis_SLOT_PRIORITY_LOWWER_ONLY</ul> */
	kuchar			upperPriorityLevel;		/**< TLVL*.bit.LPCCL*: Upper priority ratio<br>
													 The setting priority ranges are from 1 to 64("0" value stands for 64) */
	kuchar			lowerPriorityLevel;		/**< TLVL*.bit.LPCSL*: Lower priority ratio<br>
													 The setting priority ranges are from 1 to 64("0" value stands for 64) */
} MxicSlotPriorityLevel;

/** Slot priority level for each port */
typedef struct{
	// W1 arbiter
	MxicSlotPriorityLevel level0[MxicUtlis_PORT_MAX];				/**< Setting of level 0 control block for each port */
	MxicSlotPriorityLevel level1[MxicUtlis_PORT_MAX];				/**< Setting of level 1 control block for each port */
	MxicSlotPriorityLevel level2[MxicUtlis_PORT_MAX];				/**< Setting of level 2 control block for each port */
} MxicSlotPriorityLevelport;

/** Slot priority level in all arbiter */
typedef struct{
	// W arbiter
	MxicSlotPriorityLevelport wLevel[MxicUtlis_W_ARBITER_MAX];	/**< Setting of Write arbiter in all arbiter */
	// R arbiter
	MxicSlotPriorityLevelport rLevel[MxicUtlis_R_ARBITER_MAX];	/**< Setting of Read arbiter in all arbiter */
} MxicAllSlotPriority;

/** Setting of master transfer mask */
typedef struct{
	kushort		maskPeriod;					/**< TRMC*.bit.TRMCVP*: Mask period.<br>
													 The setting mask ranges are from 4 to 4096("0" value stands for 4096) */
	kuchar		maskType;						/**< TRMC*.bit.TRM*: Mask type.<br>
													<ul><li>@ref MxicUtlis_MASTER_MASK_OFF
														<li>@ref MxicUtlis_MASTER_MASK_ON
														<li>@ref MxicUtlis_MASTER_MASK_PERIOD_ON</ul> */
} ImMxicMasterMask;

/** Service history monitor result of port */
typedef struct {
	kuchar		history[MxicUtlis_MAX_MONITOR_HISTORY_NUM];	/**< THST*.bit.THST*: Service history monitor result. */
} ImMxicHistoryMonitor;

/** Service history monitor result of all port */
typedef struct {
	ImMxicHistoryMonitor	wArbiter[MxicUtlis_W_ARBITER_MAX][MxicUtlis_PORT_MAX];	/**< Service history monitor result of W ports. */
	ImMxicHistoryMonitor	rArbiter[MxicUtlis_R_ARBITER_MAX][MxicUtlis_PORT_MAX];	/**< Service history monitor result of R ports. */
} MxicAllHistoryMonitor;

/** Slot status monitor result of all arbiter */
typedef struct {
	MxicWarbiterAssignPort	wArbiter[MxicUtlis_W_ARBITER_MAX];					/**< TSLSW.bit.SLOTSW*: Slot status monitor result of W(slave) arbiter. */
	MxicRarbiterAssignPort	rArbiter[MxicUtlis_R_ARBITER_MAX];					/**< TSLSR.bit.SLOTSR*: Slot status monitor result of R(slave) arbiter. */
	MxicWarbiterAssignGr	wArbiterGr[MxicUtlis_W_ARBITER_GR_MAX];			/**< TGSLSW.bit.GSLOTSW_*: Slot status monitor result of W(group) arbiter. */
	MxicRarbiterAssignGr	rArbiterGr[MxicUtlis_R_ARBITER_GR_MAX];			/**< TGSLSR.bit.GSLOTSR_*: Slot status monitor result of R(group) arbiter. */
} MxicAllSlotMonitor;

/** All master status monitor result */
typedef struct {
	kuchar		wMaster[MxicUtlis_MAX_W_MASTER_NUM];	/**< TMSTW.bit.TMSTW_*: write master request status.	*/
	kuchar		rMaster[MxicUtlis_MAX_R_MASTER_NUM];	/**< TMSTR.bit.TMSTR_*: read master request status.	*/
} MxicMasterStatusMonitor;

/** Selection monitor target */
typedef struct {
	kuchar		monitorSel;					/**< TMSEL.bit.TMAS*: Selection monitor function.<br>
													<ul><li>@ref MxicUtlis_MONITOR_TRANSFER
														<li>@ref MxicUtlis_MONITOR_ACCESS</ul> */
	kuint32		monitorTarget;					/**< TMSEL.bit.TMSEL*: Selection monitor target from all arbiter or all master.	*/
} ImMxicMonitorTarget;

/** Access count or transfer amount monitor parameter */
typedef struct{
	kuchar					startCondition;							/**< TMMD.bit.TMON: Selection monitor start condition.<br>
																			<ul><li>@ref MxicUtlis_MONITOR_START_OFF
																				<li>@ref MxicUtlis_MONITOR_START_ON
																				<li>@ref MxicUtlis_MONITOR_START_ASSERT
																				<li>@ref MxicUtlis_MONITOR_START_TRG</ul> */
	kuchar					endCondition;								/**< TMMD.bit.TMOFF: Selection monitor end condition.<br>
																			<ul><li>@ref MxicUtlis_MONITOR_ENDLESS
																				<li>@ref MxicUtlis_MONITOR_END_ASSERT
																				<li>@ref MxicUtlis_MONITOR_END_LIMIT</ul> */
	kuchar					updateEnable;								/**< TMMD.bit.TMUP: Monitor update terminal enable.<br>
																			<ul><li>@ref MxicUtlis_ON
																				<li>@ref MxicUtlis_OFF</ul> */
	kuchar					updateTriggerInterval;					/**< TMMD.bit.TMUPC: Update trigger generation interval.<br>
																			<ul><li>@ref MxicUtlis_MONITOR_UPDATE_1
																				<li>@ref MxicUtlis_MONITOR_UPDATE_8
																				<li>@ref MxicUtlis_MONITOR_UPDATE_16
																				<li>@ref MxicUtlis_MONITOR_UPDATE_32
																				<li>@ref MxicUtlis_MONITOR_UPDATE_64
																				<li>@ref MxicUtlis_MONITOR_UPDATE_128
																				<li>@ref MxicUtlis_MONITOR_UPDATE_256
																				<li>@ref MxicUtlis_MONITOR_UPDATE_512</ul> */
	kuchar					updateClearEn;							/**< TMMD.bit.TMCLR: Selection monitor clear by update trigger.<br>
																			<ul><li>@ref MxicUtlis_ON
																				<li>@ref MxicUtlis_OFF</ul> */
	kuchar					startClearEn;								/**< TMMD.bit.TMCLRC: Selection monitor clear by asserting of a monitor start terminal.<br>
																			<ul><li>@ref MxicUtlis_ON
																				<li>@ref MxicUtlis_OFF</ul> */
	kuchar					cntVal;									/**< TMMD.bit.TMRSEL: Selection switch of reading value.<br>
																			<ul><li>@ref MxicUtlis_VALUE_WHEN_UPDATE_TRG
																				<li>@ref MxicUtlis_TRANS_COUNT_VALUE</ul> */
	kuchar					limitAccessTrans;							/**< TMLIMSEL.bit.TMALMS: Selection limit judgment<br>
																			<ul><li>@ref MxicUtlis_MONITOR_TRANSFER
																				<li>@ref MxicUtlis_MONITOR_ACCESS</ul> */
	kuint32					limitDetectionTarget;						/**< TMLIMSEL.bit.TLIMSEL: Selection limit target from all arbiter or all master.<br>
																		<ul><li>@ref MxicUtlis_3_W_STAT
																			<li>@ref MxicUtlis_3_W_IIP_A
																			<li>@ref MxicUtlis_3_W_IIP_B
																			<li>@ref MxicUtlis_3_W_IIP_C
																			<li>@ref MxicUtlis_3_W_SHDR_A
																			<li>@ref MxicUtlis_3_W_SHDR_B
																			<li>@ref MxicUtlis_3_W_SHDR_C
																			<li>@ref MxicUtlis_3_W_ME
																			<li>@ref MxicUtlis_3_W_IPU_A
																			<li>@ref MxicUtlis_3_W_IPU_C
																			<li>@ref MxicUtlis_3_W_IPU_D
																			<li>@ref MxicUtlis_3_W_IPU_E
																			<li>@ref MxicUtlis_3_W_DSP_A
																			<li>@ref MxicUtlis_3_W_DSP_B
																			<li>@ref MxicUtlis_3_W_GPU
																			<li>@ref MxicUtlis_3_W_DW
																			<li>@ref MxicUtlis_3_W_JPEG
																			<li>@ref MxicUtlis_3_W_RAW
																			<li>@ref MxicUtlis_3_W_GROUP0_M0
																			<li>@ref MxicUtlis_3_W_GROUP0_M1
																			<li>@ref MxicUtlis_3_W_ELA
																			<li>@ref MxicUtlis_3_W_XCH
																			<li>@ref MxicUtlis_3_W_FPT_0
																			<li>@ref MxicUtlis_3_W_FPT_1
																			<li>@ref MxicUtlis_3_R_STAT
																			<li>@ref MxicUtlis_3_R_IIP_A
																			<li>@ref MxicUtlis_3_R_IIP_B
																			<li>@ref MxicUtlis_3_R_IIP_C
																			<li>@ref MxicUtlis_3_R_SHDR_A
																			<li>@ref MxicUtlis_3_R_SHDR_B
																			<li>@ref MxicUtlis_3_R_SHDR_C
																			<li>@ref MxicUtlis_3_R_SHDR_D
																			<li>@ref MxicUtlis_3_R_ME
																			<li>@ref MxicUtlis_3_R_IPU_A
																			<li>@ref MxicUtlis_3_R_IPU_B
																			<li>@ref MxicUtlis_3_R_IPU_C
																			<li>@ref MxicUtlis_3_R_IPU_D
																			<li>@ref MxicUtlis_3_R_DSP_A
																			<li>@ref MxicUtlis_3_R_DSP_B
																			<li>@ref MxicUtlis_3_R_GPU
																			<li>@ref MxicUtlis_3_R_JPEG
																			<li>@ref MxicUtlis_3_R_RAW
																			<li>@ref MxicUtlis_3_R_RDMA
																			<li>@ref MxicUtlis_3_R_GROUP0_M0
																			<li>@ref MxicUtlis_3_R_GROUP0_M1
																			<li>@ref MxicUtlis_3_R_ELA
																			<li>@ref MxicUtlis_3_R_XCH
																			<li>@ref MxicUtlis_3_R_FPT_0
																			<li>@ref MxicUtlis_3_R_FPT_1
																			<li>@ref MxicUtlis_SLAVE_W1_PORT0
																			<li>@ref MxicUtlis_SLAVE_W1_PORT1
																			<li>@ref MxicUtlis_SLAVE_W1_PORT2
																			<li>@ref MxicUtlis_SLAVE_W1_PORT3
																			<li>@ref MxicUtlis_SLAVE_W2_PORT0
																			<li>@ref MxicUtlis_SLAVE_W2_PORT1
																			<li>@ref MxicUtlis_SLAVE_W2_PORT2
																			<li>@ref MxicUtlis_SLAVE_W2_PORT3
																			<li>@ref MxicUtlis_SLAVE_W3_PORT0
																			<li>@ref MxicUtlis_SLAVE_W3_PORT1
																			<li>@ref MxicUtlis_SLAVE_W3_PORT2
																			<li>@ref MxicUtlis_SLAVE_W3_PORT3
																			<li>@ref MxicUtlis_SLAVE_W4_PORT0
																			<li>@ref MxicUtlis_SLAVE_W4_PORT1
																			<li>@ref MxicUtlis_SLAVE_W4_PORT2
																			<li>@ref MxicUtlis_SLAVE_W4_PORT3
																			<li>@ref MxicUtlis_SLAVE_R1_PORT0
																			<li>@ref MxicUtlis_SLAVE_R1_PORT1
																			<li>@ref MxicUtlis_SLAVE_R1_PORT2
																			<li>@ref MxicUtlis_SLAVE_R1_PORT3
																			<li>@ref MxicUtlis_SLAVE_R2_PORT0
																			<li>@ref MxicUtlis_SLAVE_R2_PORT1
																			<li>@ref MxicUtlis_SLAVE_R2_PORT2
																			<li>@ref MxicUtlis_SLAVE_R2_PORT3
																			<li>@ref MxicUtlis_SLAVE_R3_PORT0
																			<li>@ref MxicUtlis_SLAVE_R3_PORT1
																			<li>@ref MxicUtlis_SLAVE_R3_PORT2
																			<li>@ref MxicUtlis_SLAVE_R3_PORT3
																			<li>@ref MxicUtlis_SLAVE_R4_PORT0
																			<li>@ref MxicUtlis_SLAVE_R4_PORT1
																			<li>@ref MxicUtlis_SLAVE_R4_PORT2
																			<li>@ref MxicUtlis_SLAVE_R4_PORT3
																			<li>@ref MxicUtlis_TARGET_NOTHING</ul> */
	kuint32					limit;										/**< TMLIMIT.bit.TMLIMT: Limiting value of amount of transfer data.<br>
																			 Setting values are from 0 to 256*256*256*256-1(bit). "0" value stands for no limit.<br>
																			 When limitAccessTrans is MxicUtlis_MONITOR_TRANSFER, please set the value by the unit of 256 bytes.  */
	ImMxicMonitorTarget	target[MxicUtlis_MAX_MONITOR_TARGET_NUM];	/**< Selection monitor target. */
	// CallBack function
	VP_CALLBACK				pCallBack;									/**< Call Back function pointer.<br>
																		     When the monitor end flag(TMIF.TMF) becomes "1", this callback function is called. */
} ImMxicMonitorParameter;

/** All access count or transfer amount monitor */
typedef struct {
	kuint32					count[MxicUtlis_MAX_MONITOR_TARGET_NUM];		/**< TMCNT.bit.TMCNT: Monitor result of access count or transfer amount monitor */
} AllAccessTransMonitor;

/** Write master output port */
typedef struct {
	ImMxicPortGr	ela;				/**< Setting the output port of the JDSELA Master I/F.	*/
	ImMxicPortGr	xch;				/**< Setting the output port of the JDSXH Master I/F.	*/
	ImMxicPortGr	fpt0;				/**< Setting the output port of the FPT Master I/F-0.	*/
	ImMxicPortGr	fpt1;				/**< Setting the output port of the FPT Master I/F-1.	*/
}MxicWOutputPort;

/** Read master output port */
typedef struct {
	ImMxicPortGr	ela;				/**< Setting the output port of the JDSELA Master I/F.	*/
	ImMxicPortGr	xch;				/**< Setting the output port of the JDSXH Master I/F.	*/
	ImMxicPortGr	fpt0;				/**< Setting the output port of the FPT Master I/F-0.	*/
	ImMxicPortGr	fpt1;				/**< Setting the output port of the FPT Master I/F-1.	*/
}MxicROutputPort;

/** Output port setting */
typedef struct {
	MxicWOutputPort	wOutPort;		/**< TPORTMW.bit.TPORTMW_127_64: Write output port setting master channel.	*/
	MxicROutputPort	rOutPort;		/**< TPORTMR.bit.TPORTMR_127_64: Read output port setting master channel.	*/
} ImMxicOutputPort;

/** LevelPort all setting. */
typedef struct{
	ImMxicPort					port[MxicUtlis_MASTER_NUMBER_MAX-1];		/**< Target port.	*/
	ImMxicLevel				level[MxicUtlis_MASTER_NUMBER_MAX-1];		/**< Target level.	*/
} MxicArbiterLevelport;

/** LevelPort all setting. */
typedef struct{
	MxicArbiterLevelport		wArbiter[MxicUtlis_W_ARBITER_MAX];		/**< LevelPort in W arbiter.	*/
	MxicArbiterLevelport		rArbiter[MxicUtlis_R_ARBITER_MAX];		/**< LevelPort in R arbiter.	*/
} ImMxicAllLevelport;

/** Detection parameters of memory access */
typedef struct {
	kuchar				startTrigger;			/**< TSASETW.bit.TSATRGW: Start trigger of memory access.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	unsigned long long				master47M1;				/**< TSASETW.bit.TSAMASW47_1: Master of memory access.	*/
	unsigned long long				master127M64;			/**< TSASETW.bit.TSAMASW127_64: Master of memory access.	*/
	kuint32				startAddress;			/**< TSASETW.bit.TSASADW: Start address of memory access.	*/
	kuint32				endAddress;			/**< TSASETW.bit.TSAEADW: End address of memory access.	*/
	kuchar				mode;					/**< TSASETW.bit.TSARW: Mode of memory access.<br>
													<ul><li>@ref MxicUtlis_ON
														<li>@ref MxicUtlis_OFF</ul>  */
	kuchar				detectMaster;			/**< TSASETW.bit.TSAMNSTW: Detection master of memory access.	*/
	kuchar				detectAddress;			/**< TSASETW.bit.TSAADSTW: Detection address of memory access.	*/
} MxicMemoryAccessParameter;

/** Detection parameters of slave each memory access */
typedef struct {
	MxicMemoryAccessParameter	slave[MxicUtlis_W_ARBITER_MAX];		/**< TPORTMW.bit.TPORTMW_127_64: Write output port setting master channel.	*/
	VP_CALLBACK					pCallBack;							/**< Call Back function pointer.<br> */
} MxicMemoryAccessSlave;

typedef struct _MxicUtlis MxicUtlis;
typedef struct _MxicUtlisPrivate MxicUtlisPrivate;

struct _MxicUtlis {
    KObject parent;
};


KConstType     mxic_utlis_get_type(void);
// MxicUtlis*     mxic_utlis_get(void);
MxicUtlis*     mxic_utlis_new(void);

#ifdef CO_PARAM_CHECK
/**
Check port specifies parameter.
@param[in]		wrArbiter				Write or Read Arbiter.<br>
@param[in]		arbiter					Arbiter.<br>
@param[in]		port					Port.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 mxic_utlis_check_port( MxicUtlis *self, ImMxicWrArbiter wrArbiter, 
							ImMxicSpecArbiter arbiter, ImMxicPort port );
#endif // CO_PARAM_CHECK

/**
Get unit table address.
@param[in]		unit						MXIC unit number.<br>
@param[out]		ioMxicTbl					MXIC table address.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
kint32 mxic_utlis_get_unit_tbl_address( MxicUtlis *self, ImMxicUnit unit, 
									   volatile struct io_jdsmxic_tbl** ioMxicTbl );

/**
Set TAEN register for power saving.
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
@param[in]		enable					TRUE : Enable  TSL* access.<br>
										FALSE: Disable TSL* access.<br>
*/
void mxic_utlis_set_taen( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic, kboolean enable );

/**
Init arbiter assign setting.<br>
@param[in]		unit						Target unit number.<br>
											Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allAssign					Arbiter assign.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
kint32 mxic_utlis_init_arbiter_assign( MxicUtlis *self, ImMxicUnit unit, MxicAllArbiterAssign* allAssign );

/* MXIC PCLK change to ON.
 */
void mxic_utlis_on_pclk( MxicUtlis *self, ImMxicUnit unit );

/* MXIC PCLK change to OFF.
 */
void mxic_utlis_off_pclk( MxicUtlis *self, ImMxicUnit unit );

/* MXIC HCLK change to ON.
 */
void mxic_utlis_on_hclk( MxicUtlis *self, ImMxicUnit unit );

/* MXIC HCLK change to OFF.
 */
void mxic_utlis_off_hclk( MxicUtlis *self, ImMxicUnit unit );

/**
Get unit address.
@param[in]		unit							MXIC unit number.<br>
@param[out]		ioMxic							MXIC address.<br>
@retval			D_DDIM_OK						Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR		Fail - Parameter error.
*/
kint32 mxic_utlis_get_unit_address( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic** ioMxic );

/**
Waits until the command becomes executable. 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		ioMxic					MXIC address.<br>
*/
void mxic_utlis_wait_command_enable( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic );

/**
Configuration start and wait complete.
@param[in]		ioMxic					MXIC address.<br>
*/
void mxic_utlis_process_configuration( MxicUtlis *self, ImMxicUnit unit, volatile struct io_jdsmxic* ioMxic );

/**
This function get acceptance capability of the specified port.<br> 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[out]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_utlis_get_acceptance_capability( MxicUtlis *self, ImMxicUnit unit, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiter arbiter, ImMxicPort port, kuchar* capability);

#endif	// __MXIC_UTLIS_H__