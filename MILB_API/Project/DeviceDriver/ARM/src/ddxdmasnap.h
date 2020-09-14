/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :刘应春
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、AXI DMA driver
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_XDMASNAP_H__
#define __DD_XDMASNAP_H__

#include "driver_common.h"
#include <klib.h>

#define DD_TYPE_XDMASNAP			(dd_xdmasnap_get_type())
#define DD_XDMASNAP(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, DdXdmasnap))
#define DD_IS_XDMASNAP(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_XDMASNAP))

// Interrupt flag
// Event flag of channel 0
#define	DdXdmasnap_D_DD_XDMASNAP_FLG_CH0				(0x00000001)
// Event flag of channel 1
#define	DdXdmasnap_D_DD_XDMASNAP_FLG_CH1				(0x00000002)
// Event flag of channel 2
#define	DdXdmasnap_D_DD_XDMASNAP_FLG_CH2				(0x00000004)
// Event flag of channel 3
#define	DdXdmasnap_D_DD_XDMASNAP_FLG_CH3				(0x00000008)

// Num of channel
// The maximum values of number of channels
#define DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX				(4)

// Return value of DMA processing result
// System Error
#define	DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR				(D_DD_XDMASNAP | D_DDIM_SYSTEM_ERROR)
// Input Parameter Error
#define	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR		(D_DD_XDMASNAP | D_DDIM_INPUT_PARAM_ERROR)
// Time Out
#define	DdXdmasnap_D_DD_XDMASNAP_TIMEOUT_ERR			(D_DD_XDMASNAP | D_DDIM_TIMEOUT)
// Exclusive control NG
#define	DdXdmasnap_D_DD_XDMASNAP_EXC_LOCK_NG			(D_DD_XDMASNAP | D_DDIM_EXT_LOCK_NG)
// DMA Busy
#define	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR				(D_DD_XDMASNAP | D_DDIM_MACRO_BUSY_NG)
// XDMASNAP Semaphore acquisition NG
#define	DdXdmasnap_D_DD_XDMASNAP_SEM_NG					(D_DD_XDMASNAP | D_DDIM_SEM_NG)
// XDMASNAP Semaphore acquisition Time Out
#define	DdXdmasnap_D_DD_XDMASNAP_SEM_TIMEOUT			(D_DD_XDMASNAP | D_DDIM_SEM_TIMEOUT)

// wait mode
// CPU observes register mode  (interrupt no use)
#define	DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU					(0)
// event flg wait mode         (interrupt use)
#define	DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT					(1)

// DMA exclusion mode
// Exclusive control release
#define DdXdmasnap_D_DD_XDMASNAP_EXC_OFF						(0)
// Exclusive control setting
#define DdXdmasnap_D_DD_XDMASNAP_EXC_ON							(1)

/*** Value of setting XDACS register ***/
// xE(XDMAC Enable)
// XDMAC (All channels) is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_DISABLE				(0x00)
// XDMAC (All channels) is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE				(0x01)

// cP(Channel Priority)
// Fixed (Ch0>Ch1>Ch2>Ch3>Ch4>Ch5>Ch6>Ch7)
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED					(0x00)
// Rotated (Round-robin mode)
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_ROTATED				(0x01)

// LP(Low Power)
// Low Power interface is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_DISABLE				(0x00)
// Low Power interface is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_ENABLE				(0x01)

// XS(XDMAC Status )
// The XDMAC is not active.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_XS_NOTACTIVE				(0x00)
// The XDMAC is active.
#define DdXdmasnap_D_DD_XDMASNAP_XDACS_XS_ACTIVE				(0x01)

/*** Value of setting XDSAC register ***/
// sBS( Source Access Burst Size)
// Burst Size is 1 / Transfer size is Byte
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_BYTE					(0x00)
// Burst Size is 2 / Transfer size is Half word
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD				(0x01)
// Burst Size is 4 / Transfer size is Word
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD					(0x02)
// Burst Size is 8 / Transfer size is Double word
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD			(0x03)

// sBL(Source Access Burst Length)
// Burst Length is 1
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_01			(0x00)
// Burst Length is 2
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_02			(0x01)
// Burst Length is 3
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_03			(0x02)
// Burst Length is 4
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_04			(0x03)
// Burst Length is 5
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_05			(0x04)
// Burst Length is 6
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_06			(0x05)
// Burst Length is 7
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_07			(0x06)
// Burst Length is 8
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_08			(0x07)
// Burst Length is 9
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_09			(0x08)
// Burst Length is 10
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_10			(0x09)
// Burst Length is 11
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_11			(0x0a)
// Burst Length is 12
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_12			(0x0b)
// Burst Length is 13
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_13			(0x0c)
// Burst Length is 14
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_14			(0x0d)
// Burst Length is 15
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_15			(0x0e)
// Burst Length is 16
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16			(0x0f)

// SAF ( Source Address Fix )
// Source Address is not fixed.
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX				(0x00)
// Source Address is fixed.
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_FIX					(0x01)

// SRL(Source Address Reload )
// Source address reload is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE				(0x00)
// Source address reload is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_ENABLE				(0x01)

/*** Value of setting XDDAC register ***/
// dBS(Destination Access Burst Size )
// Burst Size is 1 / Transfer size is Byte
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_BYTE					(0x00)
// Burst Size is 2 / Transfer size is Half word
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD				(0x01)
// Burst Size is 4 / Transfer size is Word
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD					(0x02)
// Burst Size is 8 / Transfer size is Double word
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD			(0x03)

// dBL(Destination Access Burst Length)
// Burst Length is 1
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_01			(0x00)
// Burst Length is 2
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_02			(0x01)
// Burst Length is 3
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_03			(0x02)
// Burst Length is 4
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_04			(0x03)
// Burst Length is 5
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_05			(0x04)
// Burst Length is 6
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_06			(0x05)
// Burst Length is 7
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_07			(0x06)
// Burst Length is 8
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_08			(0x07)
// Burst Length is 9
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_09			(0x08)
// Burst Length is 10
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_10			(0x09)
// Burst Length is 11
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_11			(0x0a)
// Burst Length is 12
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_12			(0x0b)
// Burst Length is 13
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_13			(0x0c)
// Burst Length is 14
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_14			(0x0d)
// Burst Length is 15
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_15			(0x0e)
// Burst Length is 16
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16			(0x0f)

// dAF(Destination Address Fix)
// Destination Address is not fixed.
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX				(0x00)
// Destination Address is fixed.
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_FIX					(0x01)

// dRL(Destination Address Reload )
// Destination address reload is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE				(0x00)
// Destination address reload is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_ENABLE				(0x01)

/*** Value of setting XDDCC register ***/
// dCN (Descriptor Chain Next Valid  )
// Next Descriptor Chain is invalid.
#define DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID				(0x00)
// Next Descriptor Chain is valid.
#define DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_VALID				(0x01)

/*** Value of setting XDDES register ***/
// CE(Channel Enable.)
// Channel is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_DISABLE				(0x00)
// Channel is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_CE_ENABLE				(0x01)

// sE(Software Enable )
// Software DMA is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_DISABLE				(0x00)
// Software DMA is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE				(0x01)

// tF(Transfer Factor )
// Factor is None. Detection is -
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_NONE					(0x00)
// Factor is Software. Detection is Register write (to sE bit)
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT					(0x01)
// Factor is DREQ[0].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_0				(0x02)
// Factor is DREQ[1].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_1				(0x03)
// Factor is DREQ[2].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_2				(0x04)
// Factor is DREQ[3].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_3				(0x05)
// Factor is DREQ[4].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_4				(0x06)
// Factor is DREQ[5].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_5				(0x07)
// Factor is DREQ[6].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_6				(0x08)
// Factor is DREQ[7].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_7				(0x09)
// Factor is DREQ[8].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_8				(0x0a)
// Factor is DREQ[9].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_9				(0x0b)
// Factor is DREQ[10].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_10				(0x0c)
// Factor is DREQ[11].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_11				(0x0d)
// Factor is DREQ[12].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_12				(0x0e)
// Factor is DREQ[13].Detection is High level
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_13				(0x0f)

// sA(Serial Access)
// Serial Access is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE				(0x00)
// Serial Access is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_ENABLE				(0x01)

// bT(Block transfer )
// Block transfer is disabled. (Burst transfer is enabled.)
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_DISABLE				(0x00)
// Block transfer is enabled. (Burst transfer is disabled.)
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE				(0x01)

// bR(Transfer Byte Count Reload)
// The transfer byte count reload is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE				(0x00)
// The transfer byte count reload is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_ENABLE				(0x01)

// aT(DACK Assert Timing)
// DACK is asserted while the channel accesses the source slave.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE				(0x00)
// DACK is asserted while the channel accesses the destination slave.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_DESTINATION			(0x01)

// eI(Error Interrupt)
// The error interrupt is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE				(0x00)
// The error interrupt is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE				(0x01)

// tI(Termination Interupt )
// The termination interrupt is disabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE				(0x00)
// The termination interrupt is enabled.
#define DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE				(0x01)

/*** Value of setting XDDPC register ***/
// SP(Source Access Protection Level )
// Normal access and Non-secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_NONSECURE		(0x00)
// Privileged access and Non-secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_NONSECURE	(0x01)
// Normal access and Secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_SECURE			(0x02)
// Privileged access and Secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE		(0x03)

// DP( Destination Access Protection Level)
// Normal access and Non-secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_NORMAL_NONSECURE		(0x00)
// Privileged access and Non-secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_NONSECURE	(0x01)
// Normal access and Secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_NORMAL_SECURE			(0x02)
// Privileged access and Secure access
#define DdXdmasnap_D_DD_XDMASNAP_XDDPC_DP_PRIVILEGED_SECURE		(0x03)

/*** Value of setting XDDSD register ***/
// TS(DMA transfer status )
// The DMA transfer is not running.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_TS_NOTRUNNING			(0x00)
// The DMA transfer is running.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_TS_RUNNING				(0x01)

// IS(Interrupt Status )
// Initial or Clear the interrupt / Status attribute is none.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NONE					(0x00)
// DMA stop by DSTP / Status attribute is ERROR.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_DMA_STOP_DSTP			(0x01)
// DMA stop by disabling CE bit of XDDES reg. or xE bit of XDACS reg / Status attribute is ERROR.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_DMA_STOP_DISABLING	(0x02)
// Source access error / Status attribute is ERROR.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_SOURCE_ERR			(0x04)
// Destination access error / Status attribute is ERROR.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_DESTINATION_ERR		(0x05)
// Memory Access error for Descriptor Chain DMA / Status attribute is ERROR.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_MEMORY_ERR			(0x06)
// Normal End / Status attribute is END.
#define DdXdmasnap_D_DD_XDMASNAP_XDDSD_IS_NORMAL_END			(0x08)

/*** Value of setting XDMAC LowPower Control register ***/
// CACTIV
// The bus clock is not requesting.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CACTIV_NOTEQUESTING	(0x00)
// The bus clock is requesting.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CACTIV_EQUESTING		(0x01)

// CSYSAC
// Start request is not accepted bus clock.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CSYSAC_NOTACCEPTED	(0x00)
// Start request is accepted bus clock.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CSYSAC_ACCEPTED		(0x01)

// CSYSRE
// Bus clock stop request.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CSYSRE_STOP			(0x00)
// Bus clock start request.
#define DdXdmasnap_D_DD_XDMASNAP_LOWPOWER_CSYSRE_START			(0x01)

typedef struct 		_XdmasnapCommonBit 		XdmasnapCommonBit;
typedef union 		_UDdXdmasnapCommon 		UDdXdmasnapCommon;
typedef struct 		_TDdXdmasnapCommon 		TDdXdmasnapCommon;
typedef struct 		_XdmasnapCommonCtrl1Bit	XdmasnapCommonCtrl1Bit;
typedef union 		_UDdXdmasnapCrtl1 		UDdXdmasnapCrtl1;
typedef union 		_XdmasnapCrtl2Bit 		XdmasnapCrtl2Bit;
typedef union 		_UDdXdmasnapCtrl2		UDdXdmasnapCtrl2;
typedef struct 		_TDdXdmasnapCtrl		TDdXdmasnapCtrl;
typedef struct		_DdXdmasnapTrnsSize 	DdXdmasnapTrnsSize;
typedef struct 		_DdXdmasnap 			DdXdmasnap;
typedef struct 		_DdXdmasnapPrivate 		DdXdmasnapPrivate;

struct _XdmasnapCommonBit{
	// Reserved
	kulong					:30;
	// Channel Priority ( 0 or 1 )
	kulong	cP				:1;
	// XDMAC Enable ( 0 or 1 )
	kulong	xE				:1;
};

/** DMA Control Common */
union _UDdXdmasnapCommon{
	// for kulong access
	kulong		word;
	// for bit access
	XdmasnapCommonBit bit;
};

/** DMA Control Trns */
struct _TDdXdmasnapCommon{
	// Configuration
	UDdXdmasnapCommon	commonConfig;
};

struct _XdmasnapCommonCtrl1Bit{
	// Source Address Reload ( 0 or 1 )
	kulong	sRL				:1;
	// Source Address Fix ( 0 or 1 )
	kulong	sAF				:1;
	// Source Access Burst Length ( 0 to 15 )
	kulong	sBL				:4;
	// Source Access Burst Size ( 0 or 3 )
	kulong	sBS				:2;
	// Destination Address Reload ( 0 or 1 )
	kulong	dRL				:1;
	// Destination Address Fix ( 0 or 1 )
	kulong	dAF				:1;
	// Destination Access Burst Length ( 0 to 15 )
	kulong	dBL				:4;
	// Destination Access Burst Size ( 0 or 3 )
	kulong	dBS				:2;
	// Termination Interupt ( 0 or 1 )
	kulong	tI				:1;
	// Error Interrupt ( 0 or 1 )
	kulong	eI				:1;
	// DACK Assert Timing ( 0 or 1 )
	kulong	aT				:1;
	// Transfer Byte Count Reload ( 0 or 1 )
	kulong	bR				:1;
	// Block transfer ( 0 or 1 )
	kulong	bT				:1;
	// Serial Access ( 0 or 1 )
	kulong	sA				:1;
	// Transfer Factor ( 0 to 15 )
	kulong	tF				:4;
	// Software Enable ( 0 or 1 )
	kulong	sE				:1;
	// Reserved
	kulong					:5;
	// for bit access
};

/** DMA Control xdsac and xddac and xddes */
union _UDdXdmasnapCrtl1{
	// for kulong access
	kulong		word;
	XdmasnapCommonCtrl1Bit bit;
};

struct _XdmasnapCrtl2Bit{
	// Descriptor Chain Next Valid ( 0 or 1 )
	kulong	dCN				:1;
	// Reserved
	kulong					:3;
	// Descriptor Chain Address
	kulong	dCA				:28;
};

/** DMA Control xddcc */
union _UDdXdmasnapCtrl2{
	// for kulong access
	kulong		word;
	// for bit access
	XdmasnapCrtl2Bit bit;
};

/** DMA Control Trns */
struct _TDdXdmasnapCtrl{
	// Configuration 1
	UDdXdmasnapCrtl1	config1;
	// Configuration 2
	UDdXdmasnapCtrl2	config2;
	// Source Address
	kulong			srcAddr;
	// Destination Address
	kulong			dstAddr;
	// Transfer Size (Please specify one or more)
	kulong			trnsSize;
	// Interrupt Handler
	VpCallbackFunc		intHandler;
};

/** DMA Transfer size */
struct _DdXdmasnapTrnsSize{
	// Source Address
	kulong			srcAddr;
	// Destination Address
	kulong			dstAddr;
	// Transfer Size (Please specify one or more)
	kulong			trnsSize;
};

struct _DdXdmasnap {
	KObject parent;
};

KConstType	dd_xdmasnap_get_type(void);
DdXdmasnap*	dd_xdmasnap_new(void);

#ifdef __cplusplus
extern "C" {
#endif

/**
Execute exclusive control for designated XDMA channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
if the channel state is in-use (lock), return "DdXdmasnap_D_DD_XDMASNAP_EXC_LOCK_NG".
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	tmout						: Time of timeout
										<ul>
										<li>Positive Value
										<li>@ref D_DDIM_USER_SEM_WAIT_POL
										<li>@ref D_DDIM_USER_SEM_WAIT_FEVR
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_EXC_LOCK_NG		: Lock Error (System Using designated channel number)
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_SEM_TIMEOUT		: Semaphore acquisition Time out
@retval	DdXdmasnap_D_DD_XDMASNAP_SEM_NG			: Semaphore acquisition NG
@remarks	This API uses DDIM_User_Pol_Sem() when waitTime is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when waitTime is set to the value except for 0.
*/
kint32		dd_xdmasnap_open(DdXdmasnap *self, kuchar ch, kint32 tmout);

/**
The member who exists in the structure of "TDdXdmasnapCommon" is set.
@param [in]	dmaCtrl					: DMA control data. See @ref TDdXdmasnapCtrl
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR			: DMA is being forwarded
@remarks	In the case of synchronous mode, please don't setting "intHandler". (It ignores, even if it has setting.)<br>
			In the case of the asynchronous mode, an end can be supervised by calling "Dd_XDMASNAP_Wait_End()" or setting up "intHandler".<br>
			When you don't call "Dd_XDMASNAP_Wait_End()", please be sure to set up "intHandler".
*/
kint32		dd_xdmasnap_ctrl_common(DdXdmasnap *self, TDdXdmasnapCommon const *const dmaCtrl);

/**
The member who exists in the structure of "TDdXdmasnapCtrl" is set.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	dmaCtrlTrans				: DMA control data. See @ref TDdXdmasnapCtrl
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR			: DMA is being forwarded
@remarks	In the case of synchronous mode, please don't setting "intHandler". (It ignores, even if it has setting.)<br>
			In the case of the asynchronous mode, an end can be supervised by calling "Dd_XDMASNAP_Wait_End()" or setting up "intHandler".<br>
			When you don't call "Dd_XDMASNAP_Wait_End()", please be sure to set up "intHandler".
*/
kint32		dd_xdmasnap_ctrl_trns(DdXdmasnap *self, kuchar ch, TDdXdmasnapCtrl const *const dmaCtrlTrans);

/**
The member who exists in the structure of "DdXdmasnapTrnsSize" is set.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	dmaTrnsSize				: DMA transfer size data. See @ref DdXdmasnapTrnsSize
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR			: DMA is being forwarded
@remarks	Transfer MAX size of this API as following.
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.
			<li>BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.
			</ul>
*/
kint32		dd_xdmasnap_set_trns_size(DdXdmasnap *self, kuchar ch, DdXdmasnapTrnsSize const *const dmaTrnsSize);

/**
DMA start of "Synchronous" mode.<br>
The operation of DMA of specified ch begins.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	status						: Channel Status Register pointer
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_TIMEOUT_ERR		: Time out
@retval	DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR		: System Error
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_xdmasnap_start_sync(DdXdmasnap *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
DMA start of "Asynchronous" mode.<br>
The operation of DMA of specified ch begins.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	When this mode is used, the CALLBACK function is registered or Dd_XDMASNAP_Wait_End() API please call, so check the DMA forwarding completion.
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_xdmasnap_start_async(DdXdmasnap *self, kuchar ch);

/**
The operation of DMA of specified ch is stopped.

@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32		dd_xdmasnap_stop(DdXdmasnap *self, kuchar ch);

/**
Wait end time of transfer process of designated channel.

@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	waitTime					: Wait end time of transfer process
										<ul>
										<li>Positive Value
										<li>@ref D_DDIM_USER_SEM_WAIT_POL
										<li>@ref D_DDIM_USER_SEM_WAIT_FEVR
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32		dd_xdmasnap_set_wait_time(DdXdmasnap *self, kuchar ch, kint32 waitTime);

/**
Wait end of transfer process of designated channel.<br>
The value of the CSTR register is passed by the out parameter.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [out]	status					: Channel Status Register pointer
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_TIMEOUT_ERR		: Time out
@retval	DdXdmasnap_D_DD_XDMASNAP_SYSTEM_ERR		: System Error
@remarks	This API is used only in the asynchronous mode. (It doesn't use it in the synchronous mode.)<br>
			The DMA forwarding is observed to be completed in this API.<br>
			When the DMA forwarding is completed, the CALLBACK function is called when CALLBACK function (user interrupt handler) is registered.
@remarks	This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_xdmasnap_wait_end(DdXdmasnap *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
The status bit of the DMACB register is cleared.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32		dd_xdmasnap_clear_status(DdXdmasnap *self, kuchar ch);

/**
Cancel exclusive control for designated DMA channel.<br>
When the designated channel is under transferring, stop transfer immediately and cancel lock.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_SEM_NG			: Semaphore acquisition NG
@remarks	This API forced cancel exclusive control if process is under executing.
@remarks	This API uses DDIM_User_Sig_Sem().
*/
kint32		dd_xdmasnap_close(DdXdmasnap *self, kuchar ch);

/**
The content of the DMACB register is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [out]	xdmacStatus			: XDMAC Status Register pointer
@param [out]	transferStatus			: Channel Transfer Status Register pointer
@param [out]	interruptStatus		: Channel Interrupt Status Register pointer
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32		dd_xdmasnap_get_status(DdXdmasnap *self, kuchar ch, kushort *const xdmacStatus, kushort *const transferStatus, kushort *const interruptStatus);

/**
The value of the transferd size of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	size							: Transferd size of the specified channel
@remarks	This API forced cancel exclusive control if process is under executing.
*/
kulong		dd_xdmasnap_get_trns_size(DdXdmasnap *self, kuchar ch);

/**
The value of the source address (DMACSA) of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	srcAddr						: Source address of the specified channel
*/
kulong		dd_xdmasnap_get_src_addr(DdXdmasnap *self, kuchar ch);

/**
The value of the destination address (DMACDA) of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@retval	dstAddr						: Destination address of the specified channel
*/
kulong		dd_xdmasnap_get_dst_addr(DdXdmasnap *self, kuchar ch);

/**
Low Power is set.
@param [in]	lowPower					: Low Power
										<ul>
										<li>0:DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_DISABLE
										<li>1:DdXdmasnap_D_DD_XDMASNAP_XDACS_LP_ENABLE
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32		dd_xdmasnap_set_low_power(DdXdmasnap *self, kuchar lowPower);

/**
Source Protection code is set. # Current vesion, DO NOT support this API.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	protectCode				: Protection Code
										<ul>
										<li>0:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_NONSECURE
										<li>1:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_NONSECURE
										<li>2:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_SECURE
										<li>3:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	It is allowed for a master who is not in the privileged (secure) mode to read this register.
*/
kint32		dd_xdmasnap_set_source_protect(DdXdmasnap *self, kuchar ch, kuchar protectCode);

/**
Destination Protection code is set. # Current vesion, DO NOT support this API.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	protectCode				: Protection Code
										<ul>
										<li>0:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_NONSECURE
										<li>1:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_NONSECURE
										<li>2:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_NORMAL_SECURE
										<li>3:DdXdmasnap_D_DD_XDMASNAP_XDDPC_SP_PRIVILEGED_SECURE
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	It is allowed for a master who is not in the privileged (secure) mode to read this register.
*/
kint32		dd_xdmasnap_set_destination_protect(DdXdmasnap *self, kuchar ch, kuchar protectCode);

/**
The operation of All DMA channel is stopped.
*/
void		dd_xdmasnap_stop_all_ch(DdXdmasnap *self);

/**
Set Interrupt handler address.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	intHandler					: Callback function pointer
*/
void		dd_xdmasnap_set_int_handler(DdXdmasnap *self, kuchar ch, void (*intHandler)(void));

/**
Interrupt handler of DMA for transfer process is finished.<br>
The register value of CSTR is set to the argument of the callback function of the user registration.<br>
The type of the argument is "kushort*" type.
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@remarks	This API uses DDIM_User_Set_Flg().
*/
void		dd_xdmasnap_int_handler(DdXdmasnap *self, kuchar ch);

#ifdef CO_DDIM_UTILITY_USE
/** @name Utility Functions
@{*/
/**
DMA forwarding between SDRAM-SDRAM.<br>
It waits until forwarding ends. (synchronization)
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	srcAddr					: Source address
@param [in]	dstAddr					: Destination address
@param [in]	size						: Transfer size
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU
										<li>@ref DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT
										</ul>
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_EXC_LOCK_NG		: Lock Error (System Using designated channel number)
@retval	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR			: DMA is being forwarded.
@remarks	The unit of forwarding makes a large size give priority.<br>
			Transfer MAX size of this API as following.
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.
			<li>BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.
			</ul>
*/
kint32		dd_xdmasnap_copy_sdram_sync(DdXdmasnap *self, kuchar ch, kulong srcAddr, kulong dstAddr, kulong size, kuint32 waitMode);

/**
DMA forwarding between SDRAM-SDRAM.<br>
It doesn't wait until the forwarding completion is done. (Asynchronization)
@param [in]	ch							: Channel number (0 to @ref DdXdmasnap_D_DD_XDMASNAP_CH_NUM_MAX - 1)
@param [in]	srcAddr					: Source address
@param [in]	dstAddr					: Destination address
@param [in]	size						: Transfer size
@param [in]	intHandler					: Pointer of callback function
@retval	D_DDIM_OK						: Normal end
@retval	DdXdmasnap_D_DD_XDMASNAP_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmasnap_D_DD_XDMASNAP_BUSY_ERR			: DMA is being forwarded
@remarks	The unit of forwarding makes a large size give priority.<br>
			Please call Dd_XDMASNAP_Open() before calling this function.<br>
			Please call Dd_XDMASNAP_Close() when the DMA forwarding ends.<br>
			Transfer MAX size of this API as following.<br>
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
			<li>BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
			</ul>
*/
kint32		dd_xdmasnap_copy_sdram_async(DdXdmasnap *self, kuchar ch, kulong srcAddr, kulong dstAddr, kulong size, VpCallbackFunc intHandler);
/*@}*/
#endif

#ifdef __cplusplus
}
#endif

// __DD_XDMASNAP_H__
#endif
