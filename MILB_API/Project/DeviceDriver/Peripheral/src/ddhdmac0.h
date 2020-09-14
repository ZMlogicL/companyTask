/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月4日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#ifndef _DD_HDMAC0_H_
#define _DD_HDMAC0_H_

#include "klib.h"
#include "driver_common.h"
#include "ddhdmac0utility.h"


#define DD_TYPE_HDMAC0				(dd_hdmac0_get_type())
#define DD_HDMAC0(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdHdmac0))
#define DD_IS_HDMAC0(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_HDMAC0))

// Interrupt flag
#define	DdHdmac0_FLG_CH0				(0x00000001)								/**< Event flag of channel 0 */
#define	DdHdmac0_FLG_CH1				(0x00000002)								/**< Event flag of channel 1 */
#define	DdHdmac0_FLG_CH2				(0x00000004)								/**< Event flag of channel 2 */
#define	DdHdmac0_FLG_CH3				(0x00000008)								/**< Event flag of channel 3 */
#define	DdHdmac0_FLG_CH4				(0x00000010)								/**< Event flag of channel 4 */
#define	DdHdmac0_FLG_CH5				(0x00000020)								/**< Event flag of channel 5 */
#define	DdHdmac0_FLG_CH6				(0x00000040)								/**< Event flag of channel 6 */
#define	DdHdmac0_FLG_CH7				(0x00000080)								/**< Event flag of channel 7 */

#define	DdHdmac0_MOTOR_FINISHED_DMA_TRANS_CH4		(0x00000004)						/**< Event flag of channel 4 */
#define	DdHdmac0_MOTOR_FINISHED_DMA_TRANS_CH8		(0x00000008)						/**< Event flag of channel 8 */

// Num of channel
#define DdHdmac0_CH_NUM_MAX			(8)											/**< The maximum values of number of channels */

// Return value of HDMAC0 processing result
#define	DdHdmac0_SYSTEM_ERR			(D_DD_HDMAC0 | D_DDIM_SYSTEM_ERROR)			/**< System Error */
#define	DdHdmac0_INPUT_PARAM_ERR	(D_DD_HDMAC0 | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */
#define	DdHdmac0_TIMEOUT_ERR		(D_DD_HDMAC0 | D_DDIM_TIMEOUT)				/**< Time Out */
#define	DdHdmac0_EXC_LOCK_NG		(D_DD_HDMAC0 | D_DDIM_EXT_LOCK_NG)			/**< Exclusive control NG */
#define	DdHdmac0_BUSY_ERR			(D_DD_HDMAC0 | D_DDIM_MACRO_BUSY_NG)		/**< HDMAC0 Busy */
#define	DdHdmac0_SEM_NG				(D_DD_HDMAC0 | D_DDIM_SEM_NG)				/**< HDMAC0 Semaphore acquisition NG */
#define	DdHdmac0_SEM_TIMEOUT		(D_DD_HDMAC0 | D_DDIM_SEM_TIMEOUT)			/**< HDMAC0 Semaphore acquisition Time Out */

// wait mode
#define	DdHdmac0_WAITMODE_CPU		(0)										/**< CPU observes register mode  (interrupt no use) */
#define	DdHdmac0_WAITMODE_EVENT		(1)										/**< event flg wait mode         (interrupt use) */

// HDMAC0 exclusion mode
#define DdHdmac0_EXC_OFF			(0)										/**< Exclusive control release */
#define DdHdmac0_EXC_ON				(1)										/**< Exclusive control setting */

/*** Value of setting DMACA register ***/
// Input Select(IS)
#define DdHdmac0_IS_SOFT			(0x00)										/**< Software */
#define DdHdmac0_IS_DREQ_H			(0x01)										/**< DREQ High level or Positive edge */
#define DdHdmac0_IS_DREQ_L			(0x02)										/**< DREQ Low level or Negative edge */
#define DdHdmac0_IS_IDREQ_0			(0x03)										/**< IDREQ[0] High level or Positive edge (for Audio IF In 0 (ch0)) */
#define DdHdmac0_IS_IDREQ_1			(0x04)										/**< IDREQ[1] High level or Positive edge (for Audio IF Out 0 (ch0)) */
#define DdHdmac0_IS_IDREQ_2			(0x05)										/**< IDREQ[2] High level or Positive edge (for Audio IF In 0 (ch1)) */
#define DdHdmac0_IS_IDREQ_3			(0x06)										/**< IDREQ[3] High level or Positive edge (for Audio IF Out 0 (ch1)) */
#define DdHdmac0_IS_IDREQ_4			(0x07)										/**< IDREQ[4] High level or Positive edge (for Audio IF In 0 (ch2)) */
#define DdHdmac0_IS_IDREQ_5			(0x08)										/**< IDREQ[5] High level or Positive edge (for Audio IF Out 0 (ch2)) */
#define DdHdmac0_IS_IDREQ_6			(0x09)										/**< IDREQ[6] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_7			(0x0A)										/**< IDREQ[7] High level or Positive edge (for Audio IF Out 0 (ch3)) */
#define DdHdmac0_IS_IDREQ_8			(0x0B)										/**< IDREQ[8] High level or Positive edge (for Audio IF In 0 (ch4)) */
#define DdHdmac0_IS_IDREQ_9			(0x0C)										/**< IDREQ[9] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_10		(0x0D)										/**< IDREQ[10] High level or Positive edge (for Audio IF In 0 (ch5)) */
#define DdHdmac0_IS_IDREQ_11		(0x0E)										/**< IDREQ[11] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_12		(0x0F)										/**< IDREQ[12] High level or Positive edge (for Audio IF In 1 (ch0)) */
#define DdHdmac0_IS_IDREQ_13		(0x10)										/**< IDREQ[13] High level or Positive edge (for Audio IF Out 1 (ch0)) */
#define DdHdmac0_IS_IDREQ_14		(0x11)										/**< IDREQ[14] High level or Positive edge (for Audio IF In 1 (ch1)) */
#define DdHdmac0_IS_IDREQ_15		(0x12)										/**< IDREQ[15] High level or Positive edge (for Audio IF Out 1 (ch1)) */
#define DdHdmac0_IS_IDREQ_16		(0x13)										/**< IDREQ[16] High level or Positive edge (for Audio IF In 1 (ch2)) */
#define DdHdmac0_IS_IDREQ_17		(0x14)										/**< IDREQ[17] High level or Positive edge (for Audio IF Out 1 (ch2)) */
#define DdHdmac0_IS_IDREQ_18		(0x15)										/**< IDREQ[18] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_19		(0x16)										/**< IDREQ[19] High level or Positive edge (for Audio IF Out 1 (ch3)) */
#define DdHdmac0_IS_IDREQ_20		(0x17)										/**< IDREQ[20] High level or Positive edge (for Audio IF In 1 (ch4)) */
#define DdHdmac0_IS_IDREQ_21		(0x18)										/**< IDREQ[21] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_22		(0x19)										/**< IDREQ[22] High level or Positive edge (for Audio IF In 1 (ch5)) */
#define DdHdmac0_IS_IDREQ_23		(0x1A)										/**< IDREQ[23] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_24		(0x1B)										/**< IDREQ[24] High level or Positive edge (reserved) */
#define DdHdmac0_IS_IDREQ_25		(0x1C)										/**< IDREQ[25] High level or Positive edge (for PWM ch0-3 DMA Request) */
#define DdHdmac0_IS_IDREQ_26		(0x1D)										/**< IDREQ[26] High level or Positive edge (for PWM ch4-7 DMA Request) */
#define DdHdmac0_IS_IDREQ_27		(0x1E)										/**< IDREQ[27] High level or Positive edge (for PWM ch8-11 DMA Request) */
#define DdHdmac0_IS_IDREQ_28		(0x1F)										/**< IDREQ[28] High level or Positive edge (for PWM ch12-15 DMA Request) */

// Beat Type(BT)
#define DdHdmac0_BT_NORMAL			(0x00)										/**< NORMAL (same as SINGLE) */
#define DdHdmac0_BT_SINGLE			(0x08)										/**< SINGLE (same as NORMAL) */
#define DdHdmac0_BT_INCR			(0x09)										/**< INCR */
#define DdHdmac0_BT_WRAP4			(0x0A)										/**< WRAP4 */
#define DdHdmac0_BT_INCR4			(0x0B)										/**< INCR4 */
#define DdHdmac0_BT_WRAP8			(0x0C)										/**< WRAP8 */
#define DdHdmac0_BT_INCR8			(0x0D)										/**< INCR8 */
#define DdHdmac0_BT_WRAP16			(0x0E)										/**< WRAP16 */
#define DdHdmac0_BT_INCR16			(0x0F)										/**< INCR16 */

/*** Value of setting DMACB register ***/
// Mode Select(MS)
#define DdHdmac0_MS_BLK				(0x00)										/**< Block Transfer mode */
#define DdHdmac0_MS_BURST			(0x01)										/**< Burst Transfer mode */
#define DdHdmac0_MS_DEMAND			(0x02)										/**< Demand Transfer mode */

// Transfer Width(TW)
#define DdHdmac0_TW_BYTE			(0x00)										/**< Byte */
#define DdHdmac0_TW_HWORD			(0x01)										/**< Half-Word */
#define DdHdmac0_TW_WORD			(0x02)										/**< Word */

// Fixed Source(FS)
#define DdHdmac0_FS_INCR			(0x00)										/**< Source address is incremented */
#define DdHdmac0_FS_FIX				(0x01)										/**< Source address is fixed */

// Fixed Destination(FD)
#define DdHdmac0_FD_INCR			(0x00)										/**< Destination address is incremented */
#define DdHdmac0_FD_FIX				(0x01)										/**< Destination address is fixed */

// Reload Count(RC)
#define DdHdmac0_RC_DISABLE			(0x00)										/**< Reload function of the transfer count is disabled */
#define DdHdmac0_RC_ENABLE			(0x01)										/**< Reload function of the transfer count is enabled */

// Reload Source(RS)
#define DdHdmac0_RS_DISABLE			(0x00)										/**< Reload function of the source address is disabled */
#define DdHdmac0_RS_ENABLE			(0x01)										/**< Reload function of the source address is enabled */

// Reload Destination(RD)
#define DdHdmac0_RD_DISABLE			(0x00)										/**< Reload function of the destination address is disabled */
#define DdHdmac0_RD_ENABLE			(0x01)										/**< Reload function of the destination address is enabled */

// Stop Status(SS)
#define DdHdmac0_SS_NONE			(0x00)										/**< Initial value */
#define DdHdmac0_SS_ADDR_OVER		(0x01)										/**< Address overflow (Error) */
#define DdHdmac0_SS_STOP_REQ		(0x02)										/**< Transfer stop request (Error) */
#define DdHdmac0_SS_SRC_ERR			(0x03)										/**< Source access error (Error) */
#define DdHdmac0_SS_DST_ERR			(0x04)										/**< Destination access error (Error) */
#define DdHdmac0_SS_NORMAL_END		(0x05)										/**< Normal end */
#define DdHdmac0_SS_PAUSE			(0x07)										/**< HDMAC0 pause */

// Arbitration mode
#define DdHdmac0_ARB_FIX			(0x00)										/**< priority fixed */
#define DdHdmac0_ARB_ROTATE			(0x01)										/**< priority rotated */


typedef union _Hdmac0Dmaca Hdmac0Dmaca;
typedef union _Hdmac0Dmacb Hdmac0Dmacb;
typedef struct _Hdmac0Ctrl Hdmac0Ctrl;
typedef struct _Hdmac0TrnsMode Hdmac0TrnsMode;
typedef struct _Hdmac0TrnsSize Hdmac0TrnsSize;
typedef struct _Hdmac0CtrlTrns Hdmac0CtrlTrns;
typedef struct _Hdmac0ReloadMode Hdmac0ReloadMode;

/** HDMAC0 Control DMACA */
union _Hdmac0Dmaca {
	kulong		word;						/**< for kulong access */
	struct {
		kulong	tc				:16;		/**< Transfer Count (16'h0000 to 16'hFFFF) */
		kulong	bc				:4;			/**< Block Count (4'b0000 to 4'bFFFF)<br>
												 In the demand transfer mode, BC must be set to 4'b0000. */
		kulong	bt				:4;			/**< Beat Type (4'b0000, 4'b1000 to 4'b1111)<br>
												 In the demand transfer mode, incrementing/wrapping burst (INCR*, WRAP*) is not supported. */
		kulong	is				:5;			/**< Input Select (5'b00000, 5'b01110 to 5'b11111) */
		kulong					:3;			/**< Reserved */
	} bit;									/**< for bit access */
};

/** HDMAC0 Control DMACB */
union _Hdmac0Dmacb {
	kulong		word;						/**< for kulong access */
	struct {
		kulong					:8;			/**< Reserved */
		kulong	dp				:4;			/**< Destination Protection (4'b0000 to 4'b1111) */
		kulong	sp				:4;			/**< Source Protection (4'b0000 to 4'b1111) */
		kulong	ss				:3;			/**< Stop Status (3'b000 to 3'b111) */
		kulong	ci				:1;			/**< Completion Interrupt (0 or 1) */
		kulong	ei				:1;			/**< Error Interrupt (0 or 1) */
		kulong	rd				:1;			/**< Reload Destination (0 or 1) */
		kulong	rs				:1;			/**< Reload Source (0 or 1) */
		kulong	rc				:1;			/**< Reload Count (0 or 1) */
		kulong	fd				:1;			/**< Fixed Destination (0 or 1) */
		kulong	fs				:1;			/**< Fixed Source (0 or 1) */
		kulong	tw				:2;			/**< Transfer Width (2'b00 to 2'b10) */
		kulong	ms				:2;			/**< Mode Select (2'b00 to 2'b10) */
		kulong	tt				:2;			/**< Transfer Type (2'b00) */
	} bit;									/**< for bit access */
};

/** HDMAC0 Control Common */
struct _Hdmac0Ctrl {
	Hdmac0Dmaca		configA;		/**< Configuration A */
	Hdmac0Dmacb		configB;		/**< Configuration B */
	kulong			srcAddr;		/**< Source Address */
	kulong			dstAddr;		/**< Destination Address */
	VpCallbackFunc		intHandler;	/**< Interrupt Handler */
};

/** HDMAC0 Transfer mode */
struct _Hdmac0TrnsMode {
	kuchar	inputSel;		/**< Input Select (5'b00000, 5'b01110 to 5'b11111) */
	kuchar	modeSel;		/**< Mode Select (2'b00 to 2'b10) */
	kuchar	srcFix;		/**< Source Address fixed (0 or 1) */
	kuchar	dstFix;		/**< Destination Address fixed (0 or 1) */
	kuchar	beatType;		/**< Beat Type (4'b0000, 4'b1000 to 4'b1111)<br>
												 In the demand transfer mode, incrementing/wrapping burst (INCR*, WRAP*) is not supported. */
};

/** HDMAC0 Transfer size */
struct _Hdmac0TrnsSize {
	kuchar	trnsWidth;		/**< Transfer Width (2'b00 to 2'b10) */
	kulong	trnsSize;		/**< Transfer Size */
	kulong	srcAddr;		/**< Source Address */
	kulong	dstAddr;		/**< Destination Address */
};

/** HDMAC0 Transfer Control */
struct _Hdmac0CtrlTrns {
	Hdmac0TrnsMode	mode;			/**< Transfer mode set */
	Hdmac0TrnsSize	size;			/**< Transfer size set */
	VpCallbackFunc		intHandler;	/**< Interrupt Handler */
};

/** HDMAC0 Reload mode set */
struct _Hdmac0ReloadMode {
	kuchar	reloadCnt;		/**< Reload Count mode (0 or 1) */
	kuchar	reloadSrc;		/**< Reload Source mode (0 or 1) */
	kuchar	reloadDst;		/**< Reload Destination mode (0 or 1) */
};


typedef struct _DdHdmac0 		DdHdmac0;
typedef struct _DdHdmac0Private DdHdmac0Private;

struct  _DdHdmac0 {
	KObject parent;
};

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

KConstType 	dd_hdmac0_get_type(void);
DdHdmac0* 	dd_hdmac0_get(void);

//---------------------- driver  section -------------------------------
/**
Execute exclusive control for designated HDMAC0 channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
if the channel state is in-use (lock), return "DdHdmac0_EXC_LOCK_NG".

@param [in] ch	Channel number (0 to 7)
@param [in]	tmout	semaphore timeout value(milli seconds)/DdimUserCustom_SEM_WAIT_POL(polling semaphore)
@retval D_DDIM_OK					OK
@retval DdHdmac0_EXC_LOCK_NG		Lock Error (System Using designated channel number)
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@remarks This API uses DDIM_User_Pol_Sem() when waitTime is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when waitTime is set to the value except for 0.
*/
kint32		dd_hdmac0_open(DdHdmac0 *self, kuchar ch, kint32 tmout);

/**
The member who exists in the structure of "Hdmac0Ctrl" is set.<br>

@param [in] ch				Channel number (0 to 7)
@param [in] hdmac0Ctrl		HDMAC0 control data. See @ref Hdmac0Ctrl
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac0_BUSY_ERR		HDMAC0 is being forwarded. 
@remarks In the case of synchronous mode, please don't setting "intHandler". (It ignores, even if it has setting)<br>
         In the case of the asynchronous mode, an end can be supervised by calling "dd_hdmac0_wait_end()" or setting up "intHandler".<br>
         When you don't call "dd_hdmac0_wait_end()", please be sure to set up "intHandler".
*/
kint32		dd_hdmac0_ctrl_common(DdHdmac0 *self, kuchar ch, Hdmac0Ctrl const *const hdmac0Ctrl);

/**
The member who exists in the structure of "Hdmac0CtrlTrns" is set.<br>

@param [in] ch					Channel number (0 to 7)
@param [in] hdmac0CtrlTrans	HDMAC0 control data. See @ref Hdmac0CtrlTrns
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac0_BUSY_ERR			HDMAC0 is being forwarded. 
@remarks In the case of synchronous mode, please don't setting "intHandler". (It ignores, even if it has setting)<br>
         In the case of the asynchronous mode, an end can be supervised by calling "dd_hdmac0_wait_end()" or setting up "intHandler".<br>
         When you don't call "dd_hdmac0_wait_end()", please be sure to set up "intHandler".<br>
         <br>
         Transfer MAX size of this API as following.<br>
          - Block Transfer mode and Burst Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
          - Demand Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 128KByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 64KByte.<br>
*/
kint32		dd_hdmac0_ctrl_trns(DdHdmac0 *self, kuchar ch, Hdmac0CtrlTrns const *const hdmac0CtrlTrans);

/**
The member who exists in the structure of "Hdmac0TrnsSize" is set.<br>

@param [in] ch					Channel number (0 to 7)
@param [in] hdmac0TrnsSize	HDMAC0 transfer size data. See @ref Hdmac0TrnsSize
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac0_BUSY_ERR			HDMAC0 is being forwarded. 
@remarks 
         Please call the Dd_HDMAC0_Ctrl_Common or Dd_HDMAC0_Ctrl_Trns before this API.<br>
         Transfer MAX size of this API as following.<br>
          - Block Transfer mode and Burst Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
          - Demand Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 128KByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 64KByte.<br>
*/
kint32		dd_hdmac0_set_trns_size(DdHdmac0 *self, kuchar ch, Hdmac0TrnsSize const *const hdmac0TrnsSize);

/**
HDMAC0 start of "Synchronous" mode.<br>
The operation of HDMAC0 of specified ch begins.<br>

@param [in] ch				Channel number (0 to 7)
@param [out] *status		Channel Status Register pointer
@param [in] waitMode		HDMAC0 end wait mode (DdHdmac0_WAITMODE_CPU or DdHdmac0_WAITMODE_EVENT)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac0_TIMEOUT_ERR		time out
@retval DdHdmac0_SYSTEM_ERR		system error
@remarks This API uses DDIM_User_Clr_Flg().
@remarks This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_hdmac0_start_sync(DdHdmac0 *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
HDMAC0 start of "Asynchronous" mode.<br>
The operation of HDMAC0 of specified ch begins.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@remarks When this mode is used, the CALLBACK function is registered or dd_hdmac0_wait_end() API please call,
         so check the HDMAC0 forwarding completion.
@remarks This API uses DDIM_User_Clr_Flg().
@remarks This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_hdmac0_start_async(DdHdmac0 *self, kuchar ch);

/**
The operation of HDMAC0 of specified ch is stopped.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_stop(DdHdmac0 *self, kuchar ch);

/**
The operation of HDMAC0 of specified ch is paused.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_pause(DdHdmac0 *self, kuchar ch);

/**
The operation of HDMAC0 of specified ch is resumed.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@remarks This API uses DDIM_User_Clr_Flg().
*/
kint32		dd_hdmac0_resume(DdHdmac0 *self, kuchar ch);

/**
Wait end time of transfer process of designated channel.

@param [in] ch					Channel number (0 to 7)
@param [in] waitTime			Wait end time of transfer process (>= -1)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_set_wait_time(DdHdmac0 *self, kuchar ch, kint32 waitTime);

/**
Wait end of transfer process of designated channel.<br>
The value of the CSTR register is passed by the out parameter.

@param [in] ch				Channel number (0 to 7)
@param [out] *status		Channel Status Register pointer
@param [in] waitMode		HDMAC0 end wait mode (DdHdmac0_WAITMODE_CPU or DdHdmac0_WAITMODE_EVENT)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac0_TIMEOUT_ERR		time out
@retval DdHdmac0_SYSTEM_ERR		system error
@remarks This API is used only in the asynchronous mode. (It doesn't use it in the synchronous mode.)<br>
         The HDMAC0 forwarding is observed to be completed in this API.<br>
         When the HDMAC0 forwarding is completed, the CALLBACK function is called when CALLBACK function (user interrupt handler) is registered.
@remarks This API uses DDIM_User_Clr_Flg().
@remarks This API uses DDIM_User_Twai_Flg().
*/
kint32		dd_hdmac0_wait_end(DdHdmac0 *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
The status bit of the DMACB register is cleared.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_clear_status(DdHdmac0 *self, kuchar ch);

/**
Cancel exclusive control for designated HDMAC0 channel.<br>
When the designated channel is under transferring, stop transfer immediately and cancel lock.

@param [in] ch				Channel number (0 to 7)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@remarks This API forced cancel exclusive control if process is under executing.
@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32		dd_hdmac0_close(DdHdmac0 *self, kuchar ch);

/**
The content of the DMACB register is acquired.

@param [in] ch				Channel number (0 to 7)
@param [out] *status		Channel Status Register pointer
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_get_status(DdHdmac0 *self, kuchar ch, kushort *const status);

/**
The value of the transferd size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong		dd_hdmac0_get_trns_size(DdHdmac0 *self, kuchar ch);

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong		dd_hdmac0_get_remain_trns_size(DdHdmac0 *self, kuchar ch);

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval size						total transfer size of the specified channel
*/
kulong		dd_hdmac0_get_total_trns_size(DdHdmac0 *self, kuchar ch);

/**
The value of the source address (DMACSA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval srcAddr					source address of the specified channel
*/
kulong		dd_hdmac0_get_src_addr(DdHdmac0 *self, kuchar ch);

/**
The value of the destination address (DMACDA) of the specified channel is acquired.

@param [in] ch				Channel number (0 to 7)
@retval dstAddr					Destination address of the specified channel
*/
kulong		dd_hdmac0_get_dst_addr(DdHdmac0 *self, kuchar ch);

/**
Source Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protectCode		Source Protection Code (4'b0000 to 4'b1111)<br>
								AHB HPROT[3:0] value.<br>
								[0] = 0:Opcode fetch, 1:Data access (Not effect)<br>
								[1] = 0:User mode access, 1:Supervisor mode access (Not effect)<br>
								[2] = 0:Nonbufferable access, 1:Bufferable access (Not effect)<br>
								[3] = 0:Noncachable access, 1:Cachable access<br>
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_set_source_protect(DdHdmac0 *self, kuchar ch, kuchar protectCode);

/**
Destination Protection code is set.

@param [in] ch					Channel number (0 to 7)
@param [in] protectCode		Destination Protection Code (4'b0000 to 4'b1111)<br>
								AHB HPROT[3:0] value.<br>
								[0] = 0:Opcode fetch, 1:Data access (Not effect)<br>
								[1] = 0:User mode access, 1:Supervisor mode access (Not effect)<br>
								[2] = 0:Nonbufferable access, 1:Bufferable access (Not effect)<br>
								[3] = 0:Noncachable access, 1:Cachable access<br>
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_set_destination_protect(DdHdmac0 *self, kuchar ch, kuchar protectCode);

/**
Arbitration mode is set.

@param [in] arbitration		Arbitration mode. (0 or 1)
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
@remarks There is an influence in all channels when setting it because it is a common register to all channels.
*/
kint32		dd_hdmac0_set_arbitration(DdHdmac0 *self, kuchar arbitration);

/**
Arbitration mode is read.

@param [out] *arbitration		Arbitration mode.
@retval D_DDIM_OK					OK
@retval DdHdmac0_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32		dd_hdmac0_get_arbitration(DdHdmac0 *self, kuchar *const arbitration);

/**
Arbitration mode is returned to an initial value.

@remarks There is an influence in all channels when setting it because it is a common register to all channels.
*/
void		dd_hdmac0_clear_arbitration(DdHdmac0 *self);

/**
The operation of All HDMAC0 channel is stopped.
*/
void		dd_hdmac0_stop_all_ch(DdHdmac0 *self);

/**
The operation of All HDMAC0 channel is resumed.
*/
void		dd_hdmac0_resume_all_ch(DdHdmac0 *self);

/**
It is API that returns the value set to the register of TW. 

@param [in] srcAddr			soruce address
@param [in] dstAddr			destination address
@param [in] totalSize			total size
@retval TW value set to register of TW
@remarks Total MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	BYTE transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
kuchar		dd_hdmac0_get_trns_width(DdHdmac0 *self, kulong srcAddr, kulong dstAddr, kulong totalSize);

/**
Set Interrupt handler address.

@param [in] ch				Channel number (0 to 7)
@param [in] *intHandler	callback function pointer
*/
void		dd_hdmac0_set_int_handler(DdHdmac0 *self, kuchar ch, void (*intHandler)(void));

/**
Interrupt handler of HDMAC0 for transfer process is finished.<br>
The register value of CSTR is set to the argument of the callback function of the user registration.<br>
The type of the argument is "kushort*" type.

@param [in] ch				Channel number (0 to 7)
@remarks	This API uses DDIM_User_Set_Flg().
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
void		dd_hdmac0_int_handler(DdHdmac0 *self, kuchar ch);

/**
Interrupt handler of HDMAC0 for transfer process is finished.<br>
The register value of CSTR is set to the argument of the callback function of the user registration.<br>
The type of the argument is "kushort*" type.

@param [in] ch				Channel number (5 or 6)
@remarks	This API uses DDIM_User_Set_Flg().
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
void		dd_hdmac0_int_handler_2(DdHdmac0 *self, kuchar ch);

#ifdef CO_DDIM_UTILITY_USE

kint32		dd_hdmac0_copy_sdram_sync(DdHdmac0 *self, kuchar ch, kulong srcAddr, kulong dstAddr,
				kulong size, kuint32 waitMode);
kint32		dd_hdmac0_copy_sdram_async(DdHdmac0 *self, kuchar ch, kulong srcAddr, kulong dstAddr,
				kulong size, VpCallbackFunc intHandler);
kint32		dd_hdmac0_input_audio_async(DdHdmac0 *self, kuchar ch, kuchar inputSel, kulong srcAddr,
				kulong dstAddr, kulong size, VpCallbackFunc intHandler);
kint32		dd_hdmac0_output_audio_async(DdHdmac0 *self, kuchar ch, kuchar inputSel, kulong srcAddr,
				kulong dstAddr, kulong size, VpCallbackFunc intHandler);

#endif

#ifdef __cplusplus
}
#endif


#endif	// _DD_HDMAC0_H_
