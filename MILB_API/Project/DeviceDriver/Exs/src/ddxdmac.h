/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、XDMA driver
*2、将dd_xdmac.h更名为ddxdmac.h类
*@version
*1.0.0 2020年06月开始开发
*/

/**
@addtogroup dd_xdmac
@{
	- @ref DMA_Sync_Sample
	- @ref DMA_Async_Sample
*/

#ifndef __DD_XDMAC_H__
#define __DD_XDMAC_H__

#include <klib.h>
#include "ddimusercustom.h"
#include "driver_common.h"

#define DD_TYPE_XDMAC     (dd_xdmac_get_type())
#define DD_XDMAC(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdXdmac))
#define DD_IS_XDMAC(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_XDMAC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Interrupt flag
#define	DdXdmac_FLG_CH0					(0x00000001)					/**< Event flag of channel 0 */
#define	DdXdmac_FLG_CH1					(0x00000002)					/**< Event flag of channel 1 */
#define	DdXdmac_FLG_CH2					(0x00000004)					/**< Event flag of channel 2 */
#define	DdXdmac_FLG_CH3					(0x00000008)					/**< Event flag of channel 3 */

// Num of channel
#define DdXdmac_CH_NUM_MAX		(4)								/**< The maximum values of number of channels */

// Return value of DMA processing result
#define	DdXdmac_CH_SYSTEM_ERR			(D_DD_XDMAC | D_DDIM_SYSTEM_ERROR)			/**< System Error */
#define	DdXdmac_INPUT_PARAM_ERR		(D_DD_XDMAC | D_DDIM_INPUT_PARAM_ERROR)		/**< Input Parameter Error */
#define	DdXdmac_TIMEOUT_ERR				(D_DD_XDMAC | D_DDIM_TIMEOUT)				/**< Time Out */
#define	DdXdmac_EXC_LOCK_NG				(D_DD_XDMAC | D_DDIM_EXT_LOCK_NG)			/**< Exclusive control NG */
#define	DdXdmac_BUSY_ERR						(D_DD_XDMAC | D_DDIM_MACRO_BUSY_NG)			/**< DMA Busy */
#define	DdXdmac_SEM_NG							(D_DD_XDMAC | D_DDIM_SEM_NG)				/**< XDMAC Semaphore acquisition NG */
#define	DdXdmac_SEM_TIMEOUT				(D_DD_XDMAC | D_DDIM_SEM_TIMEOUT)			/**< XDMAC Semaphore acquisition Time Out */

// wait mode
#define	DdXdmac_WAITMODE_CPU			(0)								/**< CPU observes register mode  (interrupt no use) */
#define	DdXdmac_WAITMODE_EVENT		(1)								/**< event flg wait mode         (interrupt use) */

// DMA exclusion mode
#define DdXdmac_EXC_OFF							(0)								/**< Exclusive control release */
#define DdXdmac_EXC_ON							(1)								/**< Exclusive control setting */

/*** Value of setting XDACS register ***/
// XE(XDMAC Enable)
#define DdXdmac_XDACS_XE_DISABLE		(0x00)							/**< XDMAC (All channels) is disabled. */
#define DdXdmac_XDACS_XE_ENABLE		(0x01)							/**< XDMAC (All channels) is enabled. */

// CP(Channel Priority)
#define DdXdmac_XDACS_CP_FIXED			(0x00)							/**< Fixed (Ch0>Ch1>Ch2>Ch3>Ch4>Ch5>Ch6>Ch7) */
#define DdXdmac_XDACS_CP_ROTATED		(0x01)							/**< Rotated (Round-robin mode) */

// LP(Low Power)
#define DdXdmac_XDACS_LP_DISABLE		(0x00)							/**< Low Power interface is disabled. */
#define DdXdmac_XDACS_LP_ENABLE		(0x01)							/**< Low Power interface is enabled. */

// XS(XDMAC Status)
#define DdXdmac_XDACS_XS_NOTACTIVE		(0x00)							/**< The XDMAC is not active. */
#define DdXdmac_XDACS_XS_ACTIVE				(0x01)							/**< The XDMAC is active. */

/*** Value of setting XDSAC register ***/
// SBS(Source Access Burst Size)
#define DdXdmac_XDSAC_SBS_BYTE							(0x00)							/**< Burst Size is 1 / Transfer size is Byte */
#define DdXdmac_XDSAC_SBS_HALFWORD				(0x01)							/**< Burst Size is 2 / Transfer size is Half word */
#define DdXdmac_XDSAC_SBS_WORD						(0x02)							/**< Burst Size is 4 / Transfer size is Word */
#define DdXdmac_XDSAC_SBS_DOUBLEWORD		(0x03)							/**< Burst Size is 8 / Transfer size is Double word */

// SBL(Source Access Burst Length)
#define DdXdmac_XDSAC_SBL_LENGTH_01				(0x00)							/**< Burst Length is 1 */
#define DdXdmac_XDSAC_SBL_LENGTH_02				(0x01)							/**< Burst Length is 2 */
#define DdXdmac_XDSAC_SBL_LENGTH_03				(0x02)							/**< Burst Length is 3 */
#define DdXdmac_XDSAC_SBL_LENGTH_04				(0x03)							/**< Burst Length is 4 */
#define DdXdmac_XDSAC_SBL_LENGTH_05				(0x04)							/**< Burst Length is 5 */
#define DdXdmac_XDSAC_SBL_LENGTH_06				(0x05)							/**< Burst Length is 6 */
#define DdXdmac_XDSAC_SBL_LENGTH_07				(0x06)							/**< Burst Length is 7 */
#define DdXdmac_XDSAC_SBL_LENGTH_08				(0x07)							/**< Burst Length is 8 */
#define DdXdmac_XDSAC_SBL_LENGTH_09				(0x08)							/**< Burst Length is 9 */
#define DdXdmac_XDSAC_SBL_LENGTH_10				(0x09)							/**< Burst Length is 10 */
#define DdXdmac_XDSAC_SBL_LENGTH_11				(0x0a)							/**< Burst Length is 11 */
#define DdXdmac_XDSAC_SBL_LENGTH_12				(0x0b)							/**< Burst Length is 12 */
#define DdXdmac_XDSAC_SBL_LENGTH_13				(0x0c)							/**< Burst Length is 13 */
#define DdXdmac_XDSAC_SBL_LENGTH_14				(0x0d)							/**< Burst Length is 14 */
#define DdXdmac_XDSAC_SBL_LENGTH_15				(0x0e)							/**< Burst Length is 15 */
#define DdXdmac_XDSAC_SBL_LENGTH_16				(0x0f)							/**< Burst Length is 16 */

// SAF (Source Address Fix)
#define DdXdmac_XDSAC_SAF_NOTFIX						(0x00)							/**< Source Address is not fixed. */
#define DdXdmac_XDSAC_SAF_FIX								(0x01)							/**< Source Address is fixed. */

// SRL(Source Address Reload)
#define DdXdmac_XDSAC_SRL_DISABLE					(0x00)							/**< Source address reload is disabled. */
#define DdXdmac_XDSAC_SRL_ENABLE						(0x01)							/**< Source address reload is enabled. */

/*** Value of setting XDDAC register ***/
// DBS(Destination Access Burst Size)
#define DdXdmac_XDDAC_DBS_BYTE							(0x00)							/**< Burst Size is 1 / Transfer size is Byte */
#define DdXdmac_XDDAC_DBS_HALFWORD				(0x01)							/**< Burst Size is 2 / Transfer size is Half word */
#define DdXdmac_XDDAC_DBS_WORD						(0x02)							/**< Burst Size is 4 / Transfer size is Word */
#define DdXdmac_XDDAC_DBS_DOUBLEWORD		(0x03)							/**< Burst Size is 8 / Transfer size is Double word */

// DBL(Destination Access Burst Length)
#define DdXdmac_XDDAC_DBL_LENGTH_01				(0x00)							/**< Burst Length is 1 */
#define DdXdmac_XDDAC_DBL_LENGTH_02				(0x01)							/**< Burst Length is 2 */
#define DdXdmac_XDDAC_DBL_LENGTH_03				(0x02)							/**< Burst Length is 3 */
#define DdXdmac_XDDAC_DBL_LENGTH_04				(0x03)							/**< Burst Length is 4 */
#define DdXdmac_XDDAC_DBL_LENGTH_05				(0x04)							/**< Burst Length is 5 */
#define DdXdmac_XDDAC_DBL_LENGTH_06				(0x05)							/**< Burst Length is 6 */
#define DdXdmac_XDDAC_DBL_LENGTH_07				(0x06)							/**< Burst Length is 7 */
#define DdXdmac_XDDAC_DBL_LENGTH_08				(0x07)							/**< Burst Length is 8 */
#define DdXdmac_XDDAC_DBL_LENGTH_09				(0x08)							/**< Burst Length is 9 */
#define DdXdmac_XDDAC_DBL_LENGTH_10				(0x09)							/**< Burst Length is 10 */
#define DdXdmac_XDDAC_DBL_LENGTH_11				(0x0a)							/**< Burst Length is 11 */
#define DdXdmac_XDDAC_DBL_LENGTH_12				(0x0b)							/**< Burst Length is 12 */
#define DdXdmac_XDDAC_DBL_LENGTH_13				(0x0c)							/**< Burst Length is 13 */
#define DdXdmac_XDDAC_DBL_LENGTH_14				(0x0d)							/**< Burst Length is 14 */
#define DdXdmac_XDDAC_DBL_LENGTH_15				(0x0e)							/**< Burst Length is 15 */
#define DdXdmac_XDDAC_DBL_LENGTH_16				(0x0f)							/**< Burst Length is 16 */

// DAF(Destination Address Fix)
#define DdXdmac_XDDAC_DAF_NOTFIX				(0x00)							/**< Destination Address is not fixed. */
#define DdXdmac_XDDAC_DAF_FIX						(0x01)							/**< Destination Address is fixed. */

// DRL(Destination Address Reload)
#define DdXdmac_XDDAC_DRL_DISABLE				(0x00)							/**< Destination address reload is disabled. */
#define DdXdmac_XDDAC_DRL_ENABLE				(0x01)							/**< Destination address reload is enabled. */

/*** Value of setting XDDCC register ***/
// DCN (Descriptor Chain Next Valid)
#define DdXdmac_XDDCC_DCN_INVALID				(0x00)							/**< Next Descriptor Chain is invalid. */
#define DdXdmac_XDDCC_DCN_VALID					(0x01)							/**< Next Descriptor Chain is valid. */

/*** Value of setting XDDES register ***/
// CE(Channel Enable.)
#define DdXdmac_XDDES_CE_DISABLE					(0x00)							/**< Channel is disabled. */
#define DdXdmac_XDDES_CE_ENABLE					(0x01)							/**< Channel is enabled. */

// SE(Software Enable)
#define DdXdmac_XDDES_SE_DISABLE					(0x00)							/**< Software DMA is disabled. */
#define DdXdmac_XDDES_SE_ENABLE					(0x01)							/**< Software DMA is enabled. */

// TF(Transfer Factor)
#define DdXdmac_XDDES_TF_NONE						(0x00)							/**< Factor is None. Detection is - */
#define DdXdmac_XDDES_TF_SOFT							(0x01)							/**< Factor is Software. Detection is Register write (to SE bit) */
#define DdXdmac_XDDES_TF_IDREQ_0					(0x02)							/**< Factor is DREQ[0].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_1					(0x03)							/**< Factor is DREQ[1].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_2					(0x04)							/**< Factor is DREQ[2].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_3					(0x05)							/**< Factor is DREQ[3].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_4					(0x06)							/**< Factor is DREQ[4].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_5					(0x07)							/**< Factor is DREQ[5].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_6					(0x08)							/**< Factor is DREQ[6].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_7					(0x09)							/**< Factor is DREQ[7].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_8					(0x0a)							/**< Factor is DREQ[8].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_9					(0x0b)							/**< Factor is DREQ[9].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_10				(0x0c)							/**< Factor is DREQ[10].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_11				(0x0d)							/**< Factor is DREQ[11].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_12				(0x0e)							/**< Factor is DREQ[12].Detection is High level */
#define DdXdmac_XDDES_TF_IDREQ_13				(0x0f)							/**< Factor is DREQ[13].Detection is High level */

// SA(Serial Access)
#define DdXdmac_XDDES_SA_DISABLE					(0x00)							/**< Serial Access is disabled. */
#define DdXdmac_XDDES_SA_ENABLE					(0x01)							/**< Serial Access is enabled. */

// BT(Block transfer)
#define DdXdmac_XDDES_BT_DISABLE					(0x00)							/**< Block transfer is disabled. (Burst transfer is enabled.) */
#define DdXdmac_XDDES_BT_ENABLE					(0x01)							/**< Block transfer is enabled. (Burst transfer is disabled.) */

// BR(Transfer Byte Count Reload)
#define DdXdmac_XDDES_BR_DISABLE					(0x00)							/**< The transfer byte count reload is disabled. */
#define DdXdmac_XDDES_BR_ENABLE					(0x01)							/**< The transfer byte count reload is enabled. */

// AT(DACK Assert Timing)
#define DdXdmac_XDDES_AT_SOURCE					(0x00)							/**< DACK is asserted while the channel accesses the source slave. */
#define DdXdmac_XDDES_AT_DESTINATION		(0x01)							/**< DACK is asserted while the channel accesses the destination slave. */

// EI(Error Interrupt)
#define DdXdmac_XDDES_EI_DISABLE					(0x00)							/**< The error interrupt is disabled. */
#define DdXdmac_XDDES_EI_ENABLE					(0x01)							/**< The error interrupt is enabled. */

// TI(Termination Interupt)
#define DdXdmac_XDDES_TI_DISABLE					(0x00)							/**< The termination interrupt is disabled. */
#define DdXdmac_XDDES_TI_ENABLE					(0x01)							/**< The termination interrupt is enabled. */

/*** Value of setting XDDPC register ***/
// SP(Source Access Protection Level)
#define DdXdmac_XDDPC_SP_NORMAL_NONSECURE			(0x00)							/**< Normal access and Non-secure access */
#define DdXdmac_XDDPC_SP_PRIVILEGED_NONSECURE		(0x01)							/**< Privileged access and Non-secure access */
#define DdXdmac_XDDPC_SP_NORMAL_SECURE						(0x02)							/**< Normal access and Secure access */
#define DdXdmac_XDDPC_SP_PRIVILEGED_SECURE				(0x03)							/**< Privileged access and Secure access */

// DP(Destination Access Protection Level)
#define DdXdmac_XDDPC_DP_NORMAL_NONSECURE			(0x00)							/**< Normal access and Non-secure access */
#define DdXdmac_XDDPC_DP_PRIVILEGED_NONSECURE		(0x01)							/**< Privileged access and Non-secure access */
#define DdXdmac_XDDPC_DP_NORMAL_SECURE					(0x02)							/**< Normal access and Secure access */
#define DdXdmac_XDDPC_DP_PRIVILEGED_SECURE				(0x03)							/**< Privileged access and Secure access */

/*** Value of setting XDDSD register ***/
// TS(DMA transfer status)
#define DdXdmac_XDDSD_TS_NOTRUNNING			(0x00)							/**< The DMA transfer is not running. */
#define DdXdmac_XDDSD_TS_RUNNING					(0x01)							/**< The DMA transfer is running. */

// IS(Interrupt Status)
#define DdXdmac_XDDSD_IS_NONE									(0x00)							/**< Initial or Clear the interrupt / Status attribute is none. */
#define DdXdmac_XDDSD_IS_DMA_STOP_DSTP				(0x01)							/**< DMA stop by DSTP / Status attribute is ERROR. */
#define DdXdmac_XDDSD_IS_DMA_STOP_DISABLING	(0x02)							/**< DMA stop by disabling CE bit of XDDES reg. or XE bit of XDACS reg / Status attribute is ERROR. */
#define DdXdmac_XDDSD_IS_SOURCE_ERR						(0x04)							/**< Source access error / Status attribute is ERROR. */
#define DdXdmac_XDDSD_IS_DESTINATION_ERR			(0x05)							/**< Destination access error / Status attribute is ERROR. */
#define DdXdmac_XDDSD_IS_MEMORY_ERR					(0x06)							/**< Memory Access error for Descriptor Chain DMA / Status attribute is ERROR. */
#define DdXdmac_XDDSD_IS_NORMAL_END					(0x08)							/**< Normal End / Status attribute is END. */

/*** Value of setting XDMAC LowPower Control register ***/
// CACTIV
#define DdXdmac_LOWPOWER_CACTIV_NOTEQUESTING		(0x00)							/**< The bus clock is not requesting. */
#define DdXdmac_LOWPOWER_CACTIV_EQUESTING				(0x01)							/**< The bus clock is requesting. */

// CSYSAC
#define DdXdmac_LOWPOWER_CSYSAC_NOTACCEPTED		(0x00)							/**< Start request is not accepted bus clock. */
#define DdXdmac_LOWPOWER_CSYSAC_ACCEPTED				(0x01)							/**< Start request is accepted bus clock. */

// CSYSRE
#define DdXdmac_LOWPOWER_CSYSRE_STOP				(0x00)							/**< Bus clock stop request. */
#define DdXdmac_LOWPOWER_CSYSRE_START			(0x01)							/**< Bus clock start request. */

typedef union _UDdXdmacCommon UDdXdmacCommon;
typedef struct _CommonBit CommonBit;					/*  bit*/
typedef struct _TDdXdmacCommon TDdXdmacCommon;
typedef union _UDdXdmacCtrlOne UDdXdmacCtrlOne;
typedef struct _CtrlOneBit CtrlOneBit;
typedef union _UDdXdmacCtrlTwo UDdXdmacCtrlTwo;
typedef struct _CtrlTwoBit CtrlTwoBit;
typedef struct _TDdXdmacCtrl TDdXdmacCtrl;
typedef struct _TDdXdmacTrnsSize TDdXdmacTrnsSize;

typedef struct _DdXdmac                DdXdmac;
typedef struct _DdXdmacPrivate DdXdmacPrivate;


/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
/** DMA Control Common */
union _UDdXdmacCommon
{
	kulong			word;						/**< for kulong access */
	CommonBit  	bit;
};
struct _CommonBit
{
	kulong					:30;		/**< Reserved */
	kulong	cP			:1;			/**< Channel Priority (0 or 1) */
	kulong	xE			:1;			/**< XDMAC Enable (0 or 1) */
};									/**< for bit access */

/** DMA Control Trns */
struct _TDdXdmacCommon
{
	UDdXdmacCommon	commonConfig;				/**< Configuration */
};

/** DMA Control xdsac and xddac and xddes */
union _UDdXdmacCtrlOne
{
	kulong		word;						/**< for kulong access */
	CtrlOneBit		bit;
};

struct _CtrlOneBit
{
	kulong	sRL			:1;			/**< Source Address Reload (0 or 1) */
	kulong	sAF			:1;			/**< Source Address Fix (0 or 1) */
	kulong	sBL			:4;			/**< Source Access Burst Length (0 to 15) */
	kulong	sBS			:2;			/**< Source Access Burst Size (0 or 3) */
	kulong	dRL			:1;			/**< Destination Address Reload (0 or 1) */
	kulong	dAF			:1;			/**< Destination Address Fix (0 or 1) */
	kulong	dBL			:4;			/**< Destination Access Burst Length (0 to 15) */
	kulong	dBS			:2;			/**< Destination Access Burst Size (0 or 3) */
	kulong	tI				:1;			/**< Termination Interupt (0 or 1) */
	kulong	eI				:1;			/**< Error Interrupt (0 or 1) */
	kulong	aT			:1;			/**< DACK Assert Timing (0 or 1) */
	kulong	bR			:1;			/**< Transfer Byte Count Reload (0 or 1) */
	kulong	bT			:1;			/**< Block transfer (0 or 1) */
	kulong	sA			:1;			/**< Serial Access (0 or 1) */
	kulong	tF				:4;			/**< Transfer Factor (0 to 15) */
	kulong	sE			:1;			/**< Software Enable (0 or 1) */
	kulong					:5;			/**< Reserved */
};									/**< for bit access */

/** DMA Control xddcc */
union _UDdXdmacCtrlTwo
{
	kulong			word;						/**< for kulong access */
	CtrlTwoBit 		bit;
};

struct _CtrlTwoBit
{
	kulong	dCN		:1;			/**< Descriptor Chain Next Valid (0 or 1) */
	kulong				:3;			/**< Reserved */
	kulong	dCA		:28;		/**< Descriptor Chain Address */
};									/**< for bit access */

/** DMA Control Trns */
struct _TDdXdmacCtrl
{
	UDdXdmacCtrlOne	configOne;			/**< Configuration 1 */
	UDdXdmacCtrlTwo	configTwo;			/**< Configuration 2 */
	kulong						srcAddr;			/**< Source Address */
	kulong						dstAddr;			/**< Destination Address */
	kulong						trnsSize;			/**< Transfer Size (Please specify one or more) */
	VpCallback					intHandler;		/**< Interrupt Handler */
};

/** DMA Transfer size */
struct _TDdXdmacTrnsSize
{
	kulong		srcAddr;			/**< Source Address */
	kulong		dstAddr;			/**< Destination Address */
	kulong		trnsSize;			/**< Transfer Size (Please specify one or more) */
};

struct _DdXdmac
{
	KObject 		parent;
};

KConstType 	dd_xdmac_get_type(void);
DdXdmac* 	dd_xdmac_get(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

//---------------------- driver  section -------------------------------
/**
Execute exclusive control for designated XDMA channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "DriverCommon_DDIM_OK",<br>
if the channel state is in-use (lock), return "DdXdmac_EXC_LOCK_NG".
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	tmout						: Time of timeout
										<ul>
										<li>Positive Value
										<li>@ref DdimUserCustom_SEM_WAIT_POL
										<li>@ref D_DDIM_USER_SEM_WAIT_FEVR
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_EXC_LOCK_NG			: Lock Error (System Using designated channel number)
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_SEM_TIMEOUT			: Semaphore acquisition Time out
@retval	DdXdmac_SEM_NG				: Semaphore acquisition NG
@remarks	This API uses ddim_user_custom_pol_sem(priv->ddimUserCustom,) when waitTime is set to 0. <br>
			This API uses ddim_user_custom_twai_sem(priv->ddimUserCustom,) when waitTime is set to the value except for 0.
*/
kint32	dd_xdmac_open(DdXdmac *self, kuchar ch, kint32 tmout);

/**
The member who exists in the structure of "TDdXdmacCommon" is set.
@param [in]	dma_ctrl					: DMA control data. See @ref TDdXdmacCtrl
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_BUSY_ERR				: DMA is being forwarded
@remarks	In the case of synchronous mode, please don't setting "IntHandlerFunc". (It ignores, even if it has setting.)<br>
			In the case of the asynchronous mode, an end can be supervised by calling "dd_xdmac_wait_end()" or setting up "intHandler".<br>
			When you don't call "dd_xdmac_wait_end()", please be sure to set up "IntHandlerFunc".
*/
kint32	dd_xdmac_ctrl_common(DdXdmac *self, TDdXdmacCommon const *const dma_ctrl);

/**
The member who exists in the structure of "TDdXdmacCtrl" is set.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	dma_ctrl_trans				: DMA control data. See @ref TDdXdmacCtrl
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_BUSY_ERR				: DMA is being forwarded
@remarks	In the case of synchronous mode, please don't setting "IntHandlerFunc". (It ignores, even if it has setting.)<br>
			In the case of the asynchronous mode, an end can be supervised by calling "dd_xdmac_wait_end()" or setting up "intHandler".<br>
			When you don't call "dd_xdmac_wait_end()", please be sure to set up "IntHandlerFunc".
*/
kint32	dd_xdmac_ctrl_trns(DdXdmac *self, kuchar ch, TDdXdmacCtrl const *const dma_ctrl_trans);

/**
The member who exists in the structure of "TDdXdmacTrnsSize" is set.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	dma_trns_size				: DMA transfer size data. See @ref TDdXdmacTrnsSize
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_BUSY_ERR				: DMA is being forwarded
@remarks	Transfer MAX size of this API as following.
			<ul>
			<li>WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.
			<li>HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.
			<li>kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.
			</ul>
*/
kint32	dd_xdmac_set_trns_size(DdXdmac *self, kuchar ch, TDdXdmacTrnsSize const *const dma_trns_size);

/**
DMA start of "Synchronous" mode.<br>
The operation of DMA of specified ch begins.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	status						: Channel Status Register pointer
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmac_WAITMODE_CPU
										<li>@ref DdXdmac_WAITMODE_EVENT
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR	: Input Parameter Error
@retval	DdXdmac_TIMEOUT_ERR		: Time out
@retval	DdXdmac_CH_SYSTEM_ERR		: System Error
@remarks	This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks	This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_xdmac_start_sync(DdXdmac *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
DMA start of "Asynchronous" mode.<br>
The operation of DMA of specified ch begins.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@remarks	When this mode is used, the CALLBACK function is registered or dd_xdmac_wait_end() API please call, so check the DMA forwarding completion.
@remarks	This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks	This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_xdmac_start_async(DdXdmac *self, kuchar ch);

/**
The operation of DMA of specified ch is stopped.

@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32	dd_xdmac_stop(DdXdmac *self, kuchar ch);

/**
Wait end time of transfer process of designated channel.

@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	waitTime					: Wait end time of transfer process
										<ul>
										<li>Positive Value
										<li>@ref DdimUserCustom_SEM_WAIT_POL
										<li>@ref D_DDIM_USER_SEM_WAIT_FEVR
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32	dd_xdmac_set_wait_time(DdXdmac *self, kuchar ch, kint32 waitTime);

/**
Wait end of transfer process of designated channel.<br>
The value of the CSTR register is passed by the out parameter.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [out]	status					: Channel Status Register pointer
@param [in]	waitMode					: DMA end wait mode
										<ul>
										<li>@ref DdXdmac_WAITMODE_CPU
										<li>@ref DdXdmac_WAITMODE_EVENT
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_TIMEOUT_ERR			: Time out
@retval	DdXdmac_CH_SYSTEM_ERR			: System Error
@remarks	This API is used only in the asynchronous mode. (It doesn't use it in the synchronous mode.)<br>
			The DMA forwarding is observed to be completed in this API.<br>
			When the DMA forwarding is completed, the CALLBACK function is called when CALLBACK function (user interrupt handler) is registered.
@remarks	This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_xdmac_wait_end(DdXdmac *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
The status bit of the dmacb register is cleared.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32	dd_xdmac_clear_status(DdXdmac *self, kuchar ch);

/**
Cancel exclusive control for designated DMA channel.<br>
When the designated channel is under transferring, stop transfer immediately and cancel lock.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
@retval	DdXdmac_SEM_NG				: Semaphore acquisition NG
@remarks	This API forced cancel exclusive control if process is under executing.
@remarks	This API uses ddim_user_custom_sig_sem(priv->ddimUserCustom,).
*/
kint32	dd_xdmac_close(DdXdmac *self, kuchar ch);

/**
The content of the dmacb register is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [out]	xdmacStatus			: XDMAC Status Register pointer
@param [out]	transferStatus			: Channel Transfer Status Register pointer
@param [out]	interruptStatus		: Channel Interrupt Status Register pointer
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32	dd_xdmac_get_status(DdXdmac *self, kuchar ch, kushort *const xdmacStatus,\
		kushort *const transferStatus, kushort *const interruptStatus);

/**
The value of the transferd size of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	size							: Transferd size of the specified channel
@remarks	This API forced cancel exclusive control if process is under executing.
*/
kulong	dd_xdmac_get_trns_size(DdXdmac *self, kuchar ch);

/**
The value of the source address (dmacsa) of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	src_addr						: Source address of the specified channel
*/
kulong	dd_xdmac_get_src_addr(DdXdmac *self, kuchar ch);

/**
The value of the destination address (dmacda) of the specified channel is acquired.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@retval	dst_addr						: Destination address of the specified channel
*/
kulong	dd_xdmac_get_dst_addr(DdXdmac *self, kuchar ch);

/**
Low Power is set.
@param [in]	lowpower					: Low Power
										<ul>
										<li>0:DdXdmac_XDACS_LP_DISABLE
										<li>1:DdXdmac_XDACS_LP_ENABLE
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR	: Input Parameter Error
*/
kint32	dd_xdmac_set_low_power(DdXdmac *self, kuchar lowpower);

/**
Source Protection code is set. # Current vesion, DO NOT support this API.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	protect_code				: Protection Code
										<ul>
										<li>0:DdXdmac_XDDPC_SP_NORMAL_NONSECURE
										<li>1:DdXdmac_XDDPC_SP_PRIVILEGED_NONSECURE
										<li>2:DdXdmac_XDDPC_SP_NORMAL_SECURE
										<li>3:DdXdmac_XDDPC_SP_PRIVILEGED_SECURE
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	It is allowed for a master who is not in the privileged (secure) mode to read this register.
*/
kint32	dd_xdmac_set_source_protect(DdXdmac *self, kuchar ch, kuchar protect_code);

/**
Destination Protection code is set. # Current vesion, DO NOT support this API.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	protect_code				: Protection Code
										<ul>
										<li>0:DdXdmac_XDDPC_SP_NORMAL_NONSECURE
										<li>1:DdXdmac_XDDPC_SP_PRIVILEGED_NONSECURE
										<li>2:DdXdmac_XDDPC_SP_NORMAL_SECURE
										<li>3:DdXdmac_XDDPC_SP_PRIVILEGED_SECURE
										</ul>
@retval	DriverCommon_DDIM_OK						: Normal end
@retval	DdXdmac_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	It is allowed for a master who is not in the privileged (secure) mode to read this register.
*/
kint32	dd_xdmac_set_destination_protect(DdXdmac *self, kuchar ch, kuchar protect_code);

/**
The operation of All DMA channel is stopped.
*/
void	dd_xdmac_stop_all_ch(DdXdmac *self);

/**
Set Interrupt handler address.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@param [in]	IntHandlerFunc					: Callback function pointer
*/
void	dd_xdmac_set_int_handler(DdXdmac *self, kuchar ch, void (*IntHandlerFunc)(void));

/**
Interrupt handler of DMA for transfer process is finished.<br>
The register value of CSTR is set to the argument of the callback function of the user registration.<br>
The type of the argument is "kushort*" type.
@param [in]	ch							: Channel number (0 to @ref DdXdmac_CH_NUM_MAX - 1)
@remarks	This API uses ddim_user_custom_set_flg(priv->ddimUserCustom,).
*/
void	dd_xdmac_int_handler(DdXdmac *self, kuchar ch);

#endif /* __DD_XDMAC_H__ */

/*@}*/
/** @weakgroup dd_xdmac
@{
	@section DMA_Sync_Sample		Sample of DMA (Sync)
	The example of executing synchronous processing is as follows.
	<br>
	@code
	kint32 ret;
	kushort status = 0;
	TDdXdmacCtrl dmaCtrlTrns;
	TDdXdmacCommon dmaCommon;
	kuchar ch;
	kuint32 waitMode;

	waitMode = DdXdmac_WAITMODE_CPU;
	ch = 0;

	// Check transfer size
	if (((SRC_TOP_ADDR & 0x07) == 0) && ((DST_TOP_ADDR & 0x07) == 0) && ((TRANS_SIZE & 0x07) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_DOUBLEWORD;
	}
	else if (((SRC_TOP_ADDR & 0x03) == 0) && ((DST_TOP_ADDR & 0x03) == 0) && ((TRANS_SIZE & 0x03) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_WORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_WORD;
	}
	else if (((SRC_TOP_ADDR & 0x01) == 0) && ((DST_TOP_ADDR & 0x01) == 0) && ((TRANS_SIZE & 0x01) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_HALFWORD;
	}
	else {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_BYTE;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_BYTE;
	}

	dmaCtrlTrns.trns_size = TRANS_SIZE;
	dmaCtrlTrns.src_addr = SRC_TOP_ADDR;
	dmaCtrlTrns.dst_addr = DST_TOP_ADDR;
	dmaCtrlTrns.IntHandlerFunc = 0;

	dmaCtrlTrns.config_1.bit.SRL = DdXdmac_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.config_1.bit.saf = DdXdmac_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.config_1.bit.sbl = D_DD_XDMAC_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.config_1.bit.drl = DdXdmac_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.config_1.bit.daf = DdXdmac_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.config_1.bit.dbl = D_DD_XDMAC_XDDAC_DBL_LENGTH_16;

	if (waitMode == DdXdmac_WAITMODE_EVENT) {
		dmaCtrlTrns.config_1.bit.ti = DdXdmac_XDDES_TI_ENABLE;
		dmaCtrlTrns.config_1.bit.ei = DdXdmac_XDDES_EI_ENABLE;
	}
	else {
		dmaCtrlTrns.config_1.bit.ti = DdXdmac_XDDES_TI_DISABLE;
		dmaCtrlTrns.config_1.bit.ei = DdXdmac_XDDES_EI_DISABLE;
	}

	dmaCtrlTrns.config_1.bit.at = DdXdmac_XDDES_AT_SOURCE;
	dmaCtrlTrns.config_1.bit.br = DdXdmac_XDDES_BR_DISABLE;
	dmaCtrlTrns.config_1.bit.bt = DdXdmac_XDDES_BT_DISABLE;
	dmaCtrlTrns.config_1.bit.sa = DdXdmac_XDDES_SA_DISABLE;
	dmaCtrlTrns.config_1.bit.tf = DdXdmac_XDDES_TF_NONE;
	dmaCtrlTrns.config_1.bit.se = DdXdmac_XDDES_SE_DISABLE;
	dmaCtrlTrns.config_2.bit.DCN = DdXdmac_XDDCC_DCN_INVALID;
	dmaCtrlTrns.config_2.bit.DCA = 0;

	dmaCommon.common_config.bit.XE = DdXdmac_XDACS_XE_ENABLE;
	dmaCommon.common_config.bit.cp = DdXdmac_XDACS_CP_FIXED;

	ret = Dd_XDMAC_Open(ch,DriverCommon_DDIM_WAIT_END_TIME);
	if (ret != DriverCommon_DDIM_OK) {
		return ret;
	}

	ret = dd_xdmac_ctrl_common(&dmaCommon);
	if (ret != DriverCommon_DDIM_OK) {
		return ret;// ERROR
	}

	while (1) {
		ret = dd_xdmac_ctrl_trns(ch, &dmaCtrlTrns);
		if (ret != DriverCommon_DDIM_OK) {
			break;// ERROR
		}
		ret = dd_xdmac_start_sync(ch, &status, waitMode);
		if (ret != DriverCommon_DDIM_OK) {
			;// ERROR
		}
		break;
	}

	ret = dd_xdmac_close(ch);
	if (ret != DriverCommon_DDIM_OK) {
		;// ERROR
	}
	@endcode
	<br>
	@section DMA_Async_Sample		Sample of DMA (Async)
	The example of executing Asynchronous processing is as follows.
	@code
	kint32              ret;
	kushort             status = 0;
	TDdXdmacCtrl dmaCtrlTrns;
	TDdXdmacCommon dmaCommon;
	kuchar                ch;
	kuint32               waitMode;
	waitMode = DdXdmac_WAITMODE_EVENT;
	ch = 0;

	// Check transfer size
	if (((SRC_TOP_ADDR & 0x07) == 0) && ((DST_TOP_ADDR & 0x07) == 0) && ((TRANS_SIZE & 0x07) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_DOUBLEWORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_DOUBLEWORD;
	}
	else if (((SRC_TOP_ADDR & 0x03) == 0) && ((DST_TOP_ADDR & 0x03) == 0) && ((TRANS_SIZE & 0x03) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_WORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_WORD;
	}
	else if (((SRC_TOP_ADDR & 0x01) == 0) && ((DST_TOP_ADDR & 0x01) == 0) && ((TRANS_SIZE & 0x01) == 0)) {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_HALFWORD;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_HALFWORD;
	}
	else {
		dmaCtrlTrns.config_1.bit.sbs = DdXdmac_XDSAC_SBS_BYTE;
		dmaCtrlTrns.config_1.bit.dbs = DdXdmac_XDDAC_DBS_BYTE;
	}

	dmaCtrlTrns.trns_size = TRANS_SIZE;
	dmaCtrlTrns.src_addr = SRC_TOP_ADDR;
	dmaCtrlTrns.dst_addr = DST_TOP_ADDR;
	dmaCtrlTrns.IntHandlerFunc = 0;

	dmaCtrlTrns.config_1.bit.SRL = DdXdmac_XDSAC_SRL_DISABLE;
	dmaCtrlTrns.config_1.bit.saf = DdXdmac_XDSAC_SAF_NOTFIX;
	dmaCtrlTrns.config_1.bit.sbl = D_DD_XDMAC_XDSAC_SBL_LENGTH_16;
	dmaCtrlTrns.config_1.bit.drl = DdXdmac_XDDAC_DRL_DISABLE;
	dmaCtrlTrns.config_1.bit.daf = DdXdmac_XDDAC_DAF_NOTFIX;
	dmaCtrlTrns.config_1.bit.dbl = D_DD_XDMAC_XDDAC_DBL_LENGTH_16;

	if (waitMode == DdXdmac_WAITMODE_EVENT) {
		dmaCtrlTrns.config_1.bit.ti = DdXdmac_XDDES_TI_ENABLE;
		dmaCtrlTrns.config_1.bit.ei = DdXdmac_XDDES_EI_ENABLE;
	}
	else {
		dmaCtrlTrns.config_1.bit.ti = DdXdmac_XDDES_TI_DISABLE;
		dmaCtrlTrns.config_1.bit.ei = DdXdmac_XDDES_EI_DISABLE;
	}

	dmaCtrlTrns.config_1.bit.at = DdXdmac_XDDES_AT_SOURCE;
	dmaCtrlTrns.config_1.bit.br = DdXdmac_XDDES_BR_DISABLE;
	dmaCtrlTrns.config_1.bit.bt = DdXdmac_XDDES_BT_DISABLE;
	dmaCtrlTrns.config_1.bit.sa = DdXdmac_XDDES_SA_DISABLE;
	dmaCtrlTrns.config_1.bit.tf = DdXdmac_XDDES_TF_NONE;
	dmaCtrlTrns.config_1.bit.se = DdXdmac_XDDES_SE_DISABLE;
	dmaCtrlTrns.config_2.bit.DCN = DdXdmac_XDDCC_DCN_INVALID;
	dmaCtrlTrns.config_2.bit.DCA = 0;

	dmaCommon.common_config.bit.XE = DdXdmac_XDACS_XE_ENABLE;
	dmaCommon.common_config.bit.cp = DdXdmac_XDACS_CP_FIXED;

	ret = Dd_XDMAC_Open(ch,DriverCommon_DDIM_WAIT_END_TIME);
	if (ret != DriverCommon_DDIM_OK) {
		return ret;
	}

	ret = dd_xdmac_ctrl_common(&dmaCommon);
	if (ret != DriverCommon_DDIM_OK) {
		return ret;// ERROR
	}

	while (1) {
		ret = dd_xdmac_ctrl_trns(ch, &dmaCtrlTrns);
		if (ret != DriverCommon_DDIM_OK) {
			break;// ERROR
		}
		ret = dd_xdmac_start_async(ch);
		if (ret != DriverCommon_DDIM_OK) {
			;// ERROR
		}
		ret = dd_xdmac_wait_end(ch, &status, waitMode);
		if (ret != 0) {
			// ERROR
			break;
		}
		break;
	}

	ret = dd_xdmac_close(ch);
	if (ret != DriverCommon_DDIM_OK) {
		;// ERROR
	}
	@endcode
@}*/
