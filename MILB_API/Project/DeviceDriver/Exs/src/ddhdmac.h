/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、HDMAC driver
*2、将dd_hdmac.c更名为ddhdmac.c类
*@version
*1.0.0 2020年06月开始开发
*/

/**
@addtogroup dd_hdmac
@{
- @ref HDMAC_DREQ
- @ref HDMAC_IDREQ
- @ref HDMAC_Sync
- @ref HDMAC_Async
- @ref HDMAC_Sync_Sample_Dd_HDMAC_Ctrl_Common
- @ref HDMAC_Sync_Sample_Dd_HDMAC_Ctrl_Trns
- @ref HDMAC_Async_Sample

@section HDMAC_DREQ	Connection of DREQ
<table>
<tr>
	<th>DREQ(HDMAC ch)</th>
	<th>HDMAC Start factor</th>
</tr>
<tr>
	<td>0</td>
	<td>USB2.0 ch1</td>
</tr>
<tr>
	<td>1</td>
	<td>USB2.0 ch2</td>
</tr>
<tr>
	<td>2</td>
	<td>none</td>
</tr>
<tr>
	<td>3</td>
	<td>none</td>
</tr>
</table>

@section HDMAC_IDREQ	Connection of IDREQ
<table>
<tr>
	<th>IDREQ</th>
	<th>HDMAC Start factor</th>
</tr>
<tr>
	<td>0</td>
	<td>none</td>
</tr>
<tr>
	<td>1</td>
	<td>none</td>
</tr>
<tr>
	<td>2</td>
	<td>none</td>
</tr>
<tr>
	<td>3</td>
	<td>none</td>
</tr>
<tr>
	<td>4</td>
	<td>none</td>
</tr>
<tr>
	<td>5</td>
	<td>none</td>
</tr>
<tr>
	<td>6</td>
	<td>none</td>
</tr>
<tr>
	<td>7</td>
	<td>none</td>
</tr>
<tr>
	<td>8</td>
	<td>none</td>
</tr>
<tr>
	<td>9</td>
	<td>none</td>
</tr>
<tr>
	<td>10</td>
	<td>none</td>
</tr>
<tr>
	<td>11</td>
	<td>none</td>
</tr>
<tr>
	<td>12</td>
	<td>none</td>
</tr>
<tr>
	<td>13</td>
	<td>none</td>
</tr>
<tr>
	<td>14</td>
	<td>none</td>
</tr>
<tr>
	<td>15</td>
	<td>none</td>
</tr>
</table>

@section HDMAC_Sync	Sequence of HDMAC forwarding sequence (Waiting of HDMAC forwarding)
@image html 01_HDMAC_Sync.PNG

@section HDMAC_Async	Sequence of HDMAC forwarding sequence (The interrupt handler is used)
@image html 02_HDMAC_Async.PNG
*/

#ifndef __DD_HDMAC_H__
#define __DD_HDMAC_H__

#include <klib.h>
#include "driver_common.h"
#include "ddimtypedef.h"//我自己添加的为了让kuchar不报错

#define DD_TYPE_HDMAC     (dd_hdmac_get_type())
#define DD_HDMAC(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, DdHdmac))
#define DD_IS_HDMAC(obj)  (K_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_HDMAC))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
// Interrupt flag
#define	DdHdmac_FLG_CH0				(0x00000001)								/**< Event flag of channel 0 */
#define	DdHdmac_FLG_CH1				(0x00000002)								/**< Event flag of channel 1 */
#define	DdHdmac_FLG_CH2				(0x00000004)								/**< Event flag of channel 2 */
#define	DdHdmac_FLG_CH3				(0x00000008)								/**< Event flag of channel 3 */

// Num of channel
#define DdHdmac_CH_NUM_MAX				(4)											/**< The maximum values of number of channels */

// Return value of HDMAC processing result
#define	DdHdmac_SYSTEM_ERR					(D_DD_HDMAC | D_DDIM_SYSTEM_ERROR)			/**< System Error */
#define	DdHdmac_INPUT_PARAM_ERR		(D_DD_HDMAC | D_DDIM_INPUT_PARAM_ERROR)		/**< Input Parameter Error */
#define	DdHdmac_TIMEOUT_ERR				(D_DD_HDMAC | D_DDIM_TIMEOUT)				/**< Time Out */
#define	DdHdmac_EXC_LOCK_NG				(D_DD_HDMAC | D_DDIM_EXT_LOCK_NG)			/**< Exclusive control NG */
#define	DdHdmac_BUSY_ERR						(D_DD_HDMAC | D_DDIM_MACRO_BUSY_NG)			/**< HDMAC Busy */
#define	DdHdmac_SEM_NG							(D_DD_HDMAC | D_DDIM_SEM_NG)				/**< HDMAC Semaphore acquisition NG */
#define	DdHdmac_SEM_TIMEOUT				(D_DD_HDMAC | D_DDIM_SEM_TIMEOUT)			/**< HDMAC Semaphore acquisition Time Out */

// wait mode
#define	DdHdmac_WAITMODE_CPU			(0)											/**< CPU observes register mode  (interrupt no use) */
#define	DdHdmac_WAITMODE_EVENT		(1)											/**< event flg wait mode         (interrupt use) */

// HDMAC exclusion mode
#define DdHdmac_EXC_OFF				(0)											/**< Exclusive control release */
#define DdHdmac_EXC_ON				(1)											/**< Exclusive control setting */

/*** Value of setting dmaca register ***/
// Input Select(IS)
#define DdHdmac_IS_SOFT					(0x00)										/**< Software */
#define DdHdmac_IS_DREQ_H			(0x01)										/**< DREQ High level or Positive edge */
#define DdHdmac_IS_DREQ_L				(0x02)										/**< DREQ Low level or Negative edge */
#define DdHdmac_IS_IDREQ_0			(0x03)										/**< IDREQ[0] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_1			(0x04)										/**< IDREQ[1] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_2			(0x05)										/**< IDREQ[2] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_3			(0x06)										/**< IDREQ[3] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_4			(0x07)										/**< IDREQ[4] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_5			(0x08)										/**< IDREQ[5] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_6			(0x09)										/**< IDREQ[6] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_7			(0x0A)										/**< IDREQ[7] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_8			(0x0B)										/**< IDREQ[8] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_9			(0x0C)										/**< IDREQ[9] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_10			(0x0D)										/**< IDREQ[10] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_11			(0x0E)										/**< IDREQ[11] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_12			(0x0F)										/**< IDREQ[12] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_13			(0x10)										/**< IDREQ[13] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_14			(0x11)										/**< IDREQ[14] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_15			(0x12)										/**< IDREQ[15] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_16			(0x13)										/**< IDREQ[16] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_17			(0x14)										/**< IDREQ[17] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_18			(0x15)										/**< IDREQ[18] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_19			(0x16)										/**< IDREQ[19] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_20			(0x17)										/**< IDREQ[20] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_21			(0x18)										/**< IDREQ[21] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_22			(0x19)										/**< IDREQ[22] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_23			(0x1A)										/**< IDREQ[23] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_24			(0x1B)										/**< IDREQ[24] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_25			(0x1C)										/**< IDREQ[25] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_26			(0x1D)										/**< IDREQ[26] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_27			(0x1E)										/**< IDREQ[27] High level or Positive edge (reserved) */
#define DdHdmac_IS_IDREQ_28			(0x1F)										/**< IDREQ[28] High level or Positive edge (reserved) */

// Beat Type(BT)
#define DdHdmac_BT_NORMAL			(0x00)										/**< NORMAL (same as SINGLE) */
#define DdHdmac_BT_SINGLE				(0x08)										/**< SINGLE (same as NORMAL) */
#define DdHdmac_BT_INCR					(0x09)										/**< INCR */
#define DdHdmac_BT_WRAP4				(0x0A)										/**< WRAP4 */
#define DdHdmac_BT_INCR4				(0x0B)										/**< INCR4 */
#define DdHdmac_BT_WRAP8				(0x0C)										/**< WRAP8 */
#define DdHdmac_BT_INCR8				(0x0D)										/**< INCR8 */
#define DdHdmac_BT_WRAP16			(0x0E)										/**< WRAP16 */
#define DdHdmac_BT_INCR16				(0x0F)										/**< INCR16 */

/*** Value of setting dmacb register ***/
// Mode Select(MS)
#define DdHdmac_MS_BLK					(0x00)										/**< Block Transfer mode */
#define DdHdmac_MS_BURST				(0x01)										/**< Burst Transfer mode */
#define DdHdmac_MS_DEMAND			(0x02)										/**< Demand Transfer mode */

// Transfer Width(TW)
#define DdHdmac_TW_BYTE				(0x00)										/**< Byte */
#define DdHdmac_TW_HWORD			(0x01)										/**< Half-Word */
#define DdHdmac_TW_WORD				(0x02)										/**< Word */

// Fixed Source(FS)
#define DdHdmac_FS_INCR					(0x00)										/**< Source address is incremented */
#define DdHdmac_FS_FIX						(0x01)										/**< Source address is fixed */

// Fixed Destination(FD)
#define DdHdmac_FD_INCR					(0x00)										/**< Destination address is incremented */
#define DdHdmac_FD_FIX					(0x01)										/**< Destination address is fixed */

// Reload Count(RC)
#define DdHdmac_RC_DISABLE			(0x00)										/**< Reload function of the transfer count is disabled */
#define DdHdmac_RC_ENABLE			(0x01)										/**< Reload function of the transfer count is enabled */

// Reload Source(RS)
#define DdHdmac_RS_DISABLE			(0x00)										/**< Reload function of the source address is disabled */
#define DdHdmac_RS_ENABLE			(0x01)										/**< Reload function of the source address is enabled */

// Reload Destination(RD)
#define DdHdmac_RD_DISABLE			(0x00)										/**< Reload function of the destination address is disabled */
#define DdHdmac_RD_ENABLE			(0x01)										/**< Reload function of the destination address is enabled */

// Stop Status(SS)
#define DdHdmac_SS_NONE					(0x00)										/**< Initial value */
#define DdHdmac_SS_ADDR_OVER			(0x01)										/**< Address overflow (Error) */
#define DdHdmac_SS_STOP_REQ			(0x02)										/**< Transfer stop request (Error) */
#define DdHdmac_SS_SRC_ERR				(0x03)										/**< Source access error (Error) */
#define DdHdmac_SS_DST_ERR				(0x04)										/**< Destination access error (Error) */
#define DdHdmac_SS_NORMAL_END		(0x05)										/**< Normal end */
#define DdHdmac_SS_PAUSE					(0x07)										/**< HDMAC pause */

// Arbitration mode
#define DdHdmac_ARB_FIX						(0x00)										/**< priority fixed */
#define DdHdmac_ARB_ROTATE				(0x01)										/**< priority rotated */

typedef union _UDdHdmacDmaca 			UDdHdmacDmaca;
typedef struct _DmacaBit 							DmacaBit;					/*U_DD_HDMAC_DMACA中的bit*/
typedef union _UDdHdmacDmacb 			UDdHdmacDmacb;
typedef struct _DmacbBit 							DmacbBit;					/*U_DD_HDMAC_DMACB中的bit*/
typedef struct _TDdHdmacCtrl 					TDdHdmacCtrl;
typedef struct _TDdHdmacTrnsMode 		TDdHdmacTrnsMode;
typedef struct _TDdHdmacTrnsSize 			TDdHdmacTrnsSize;
typedef struct _TDdHdmacCtrlTrns 			TDdHdmacCtrlTrns;
typedef struct _TDdHdmacReloadMode 	TDdHdmacReloadMode;

typedef struct _DdHdmac                			DdHdmac;
typedef struct _DdHdmacPrivate 				DdHdmacPrivate;

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/** HDMAC Control dmaca */
union _UDdHdmacDmaca
{
	kulong		word;						/**< for kulong access */
	DmacaBit   bit;
};
struct _DmacaBit
{
	kulong	tC				:16;			/**< Transfer Count (16'h0000 to 16'hFFFF) */
	kulong	bC			:4;			/**< Block Count (4'b0000 to 4'bFFFF)<br>
											 	 	 In the demand transfer mode, BC must be set to 4'b0000. */
	kulong	bT				:4;			/**< Beat Type (4'b0000, 4'b1000 to 4'b1111)<br>
											 In the demand transfer mode, incrementing/wrapping burst (INCR*, WRAP*) is not supported. */
	kulong	iS				:5;			/**< Input Select (5'b00000, 5'b01110 to 5'b11111) */
	kulong					:3;			/**< Reserved */
};											/**< for bit access */

/** HDMAC Control dmacb */
union _UDdHdmacDmacb
{
	kulong		word;						/**< for kulong access */
	DmacbBit	bit;
};

struct _DmacbBit
{
	kulong					:8;			/**< Reserved */
	kulong	dP			:4;			/**< Destination Protection (4'b0000 to 4'b1111) */
	kulong	sP			:4;			/**< Source Protection (4'b0000 to 4'b1111) */
	kulong	sS				:3;			/**< Stop Status (3'b000 to 3'b111) */
	kulong	cI				:1;			/**< Completion Interrupt (0 or 1) */
	kulong	eI				:1;			/**< Error Interrupt (0 or 1) */
	kulong	rD			:1;			/**< Reload Destination (0 or 1) */
	kulong	rS				:1;			/**< Reload Source (0 or 1) */
	kulong	rC				:1;			/**< Reload Count (0 or 1) */
	kulong	fD				:1;			/**< Fixed Destination (0 or 1) */
	kulong	fS				:1;			/**< Fixed Source (0 or 1) */
	kulong	tW			:2;			/**< Transfer Width (2'b00 to 2'b10) */
	kulong	mS			:2;			/**< Mode Select (2'b00 to 2'b10) */
	kulong	tT				:2;			/**< Transfer Type (2'b00) */
};									/**< for bit access */

/** HDMAC Control Common */
struct _TDdHdmacCtrl
{
	UDdHdmacDmaca		configA;		/**< Configuration A */
	UDdHdmacDmacb		configB;		/**< Configuration B */
	kulong							srcAddr;		/**< Source Address */
	kulong							dstAddr;		/**< Destination Address */
	VpCallback						intHandler;	/**< Interrupt Handler */
};//有3处用
//TODO:VpCallback定义在ddim_typedef.h中
//原型为typedef void	(*VP_CALLBACK)();	/**< Type is defined to Callback function pointer */

/** HDMAC Transfer mode */
struct _TDdHdmacTrnsMode
{
	kuchar		inputSel;		/**< Input Select (5'b00000, 5'b01110 to 5'b11111) */
	kuchar		modeSel;		/**< Mode Select (2'b00 to 2'b10) */
	kuchar		srcFix;		/**< Source Address fixed (0 or 1) */
	kuchar		dstFix;		/**< Destination Address fixed (0 or 1) */
	kuchar		beatType;		/**< Beat Type (4'b0000, 4'b1000 to 4'b1111)<br>
												 In the demand transfer mode, incrementing/wrapping burst (INCR*, WRAP*) is not supported. */
};

/** HDMAC Transfer size */
struct _TDdHdmacTrnsSize
{
	kuchar					trnsWidth;		/**< Transfer Width (2'b00 to 2'b10) */
	kulong					trnsSize;		/**< Transfer Size */
	kulong					srcAddr;		/**< Source Address */
	kulong					dstAddr;		/**< Destination Address */
};

/** HDMAC Transfer Control */
struct _TDdHdmacCtrlTrns
{
	TDdHdmacTrnsMode	mode;			/**< Transfer mode set */
	TDdHdmacTrnsSize		size;			/**< Transfer size set */
	VpCallback				intHandler;	/**< Interrupt Handler */
};

/** HDMAC Reload mode set */
struct _TDdHdmacReloadMode
{
	kuchar					reloadCnt;		/**< Reload Count mode (0 or 1) */
	kuchar					reloadSrc;		/**< Reload Source mode (0 or 1) */
	kuchar					reloadDst;		/**< Reload Destination mode (0 or 1) */
};

struct _DdHdmac
{
	KObject	parent;
	kulong 	srcAddr;
	kulong 	dstAddr;
};

KConstType 		dd_hdmac_get_type(void);
DdHdmac* 		dd_hdmac_get(void);

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

//---------------------- driver  section -------------------------------
/**
Execute exclusive control for designated HDMAC channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "DriverCommon_DDIM_OK",<br>
if the channel state is in-use (lock), return "DdHdmac_EXC_LOCK_NG".

@param [in] ch	Channel number (0 to 3)
@param [in]	tmout	semaphore timeout value(milli seconds)/DdimUserCustom_SEM_WAIT_POL(polling semaphore)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_EXC_LOCK_NG		Lock Error (System Using designated channel number)
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@remarks This API uses ddim_user_custom_pol_sem(priv->ddimUserCustom,) when waitTime is set to 0. <br>
		 This API uses ddim_user_custom_twai_sem(priv->ddimUserCustom,) when waitTime is set to the value except for 0.
*/
kint32	dd_hdmac_open(DdHdmac *self, kuchar ch, kint32 tmout);//z1179

/**
The member who exists in the structure of "TDdHdmacCtrl" is set.<br>
他是存在于"TDdHdmacCtrl"结构中的成员
@param [in] ch				Channel number (0 to 3)
@param [in] hdmac_ctrl		HDMAC control data. See @ref TDdHdmacCtrl
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_BUSY_ERR		HDMAC is being forwarded.
@remarks In the case of synchronous mode, please don't setting "IntHandlerFunc". (It ignores, even if it has setting)<br>
         In the case of the asynchronous mode, an end can be supervised by calling "Dd_HDMAC_Wait_End()" or setting up "intHandler".<br>
         When you don't call "Dd_HDMAC_Wait_End()", please be sure to set up "IntHandlerFunc".
*/
kint32	dd_hdmac_ctrl_common(DdHdmac *self, kuchar ch, TDdHdmacCtrl const *const hdmacCtrl);//z

/**
The member who exists in the structure of "TDdHdmacCtrlTrns" is set.<br>

@param [in] ch					Channel number (0 to 3)
@param [in] hdmac_ctrl_trans	HDMAC control data. See @ref TDdHdmacCtrlTrns
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_BUSY_ERR			HDMAC is being forwarded.
@remarks In the case of synchronous mode, please don't setting "IntHandlerFunc". (It ignores, even if it has setting)<br>
         In the case of the asynchronous mode, an end can be supervised by calling "Dd_HDMAC_Wait_End()" or setting up "intHandler".<br>
         When you don't call "Dd_HDMAC_Wait_End()", please be sure to set up "IntHandlerFunc".<br>
         <br>
         Transfer MAX size of this API as following.<br>
          - Block Transfer mode and Burst Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
          - Demand Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 128KByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 64KByte.<br>
*/
kint32	dd_hdmac_ctrl_trns(DdHdmac *self, kuchar ch, TDdHdmacCtrlTrns const *const hdmacCtrlTrans);

/**
The member who exists in the structure of "TDdHdmacTrnsSize" is set.<br>

@param [in] ch					Channel number (0 to 3)
@param [in] hdmac_trns_size	HDMAC transfer size data. See @ref TDdHdmacTrnsSize
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_BUSY_ERR			HDMAC is being forwarded.
@remarks
         Please call the Dd_HDMAC_Ctrl_Common or Dd_HDMAC_Ctrl_Trns before this API.<br>
         Transfer MAX size of this API as following.<br>
          - Block Transfer mode and Burst Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
          - Demand Transfer mode<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 256KByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 128KByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 64KByte.<br>
*/
kint32	dd_hdmac_set_trns_size(DdHdmac *self, kuchar ch, TDdHdmacTrnsSize const *const hdmacTrnsSize);

/**
HDMAC start of "Synchronous" mode.<br>
The operation of HDMAC of specified ch begins.<br>

@param [in] ch				Channel number (0 to 3)
@param [out] *status		Channel Status Register pointer
@param [in] waitMode		HDMAC end wait mode (DdHdmac_WAITMODE_CPU or DdHdmac_WAITMODE_EVENT)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_TIMEOUT_ERR		time out
@retval DdHdmac_SYSTEM_ERR		system error
@remarks This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_hdmac_start_sync(DdHdmac *self, kuchar ch, kushort *const status, kuint32 waitMode);//z

/**
HDMAC start of "Asynchronous" mode.<br>
The operation of HDMAC of specified ch begins.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@remarks When this mode is used, the CALLBACK function is registered or Dd_HDMAC_Wait_End() API please call,
         so check the HDMAC forwarding completion.
@remarks This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_hdmac_start_async(DdHdmac *self, kuchar ch);//1270zy

/**
Wait end time of transfer process of designated channel.

@param [in] ch					Channel number (0 to 3)
@param [in] waitTime			Wait end time of transfer process (>= -1)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	dd_hdmac_set_wait_time(DdHdmac *self, kuchar ch, kint32 waitTime);

/**
Wait end of transfer process of designated channel.<br>
The value of the CSTR register is passed by the out parameter.

@param [in] ch				Channel number (0 to 3)
@param [out] *status		Channel Status Register pointer
@param [in] waitMode		HDMAC end wait mode (DdHdmac_WAITMODE_CPU or DdHdmac_WAITMODE_EVENT)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_TIMEOUT_ERR		time out
@retval DdHdmac_SYSTEM_ERR		system error
@remarks This API is used only in the asynchronous mode. (It doesn't use it in the synchronous mode.)<br>
         The HDMAC forwarding is observed to be completed in this API.<br>
         When the HDMAC forwarding is completed, the CALLBACK function is called when CALLBACK function (user interrupt handler) is registered.
@remarks	This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks	This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
kint32	dd_hdmac_wait_end(DdHdmac *self, kuchar ch, kushort *const status, kuint32 waitMode);

/**
Cancel exclusive control for designated HDMAC channel.<br>
When the designated channel is under transferring, stop transfer immediately and cancel lock.

@param [in] ch				Channel number (0 to 3)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@remarks This API forced cancel exclusive control if process is under executing.
@remarks This API uses ddim_user_custom_sig_sem(priv->ddimUserCustom,).
*/
kint32	dd_hdmac_close(DdHdmac *self, kuchar ch);//z

/**
The value of the transferd size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval size						transferd size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong	dd_hdmac_get_trns_size(DdHdmac *self, kuchar ch);

/**
The value of the remainder transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval size						remainder transfer size of the specified channel
@remarks This API forced cancel exclusive control if process is under executing.
*/
kulong	dd_hdmac_get_remain_trns_size(DdHdmac *self, kuchar ch);

/**
The value of the total transfer size of the specified channel is acquired.

@param [in] ch				Channel number (0 to 3)
@retval size						total transfer size of the specified channel
*/
kulong	dd_hdmac_get_total_trns_size(DdHdmac *self, kuchar ch);

/**
Set Interrupt handler address.

@param [in] ch				Channel number (0 to 3)
@param [in] *IntHandlerFunc	callback function pointer
*/
void	dd_hdmac_set_int_handler(DdHdmac *self, kuchar ch, void (*IntHandlerFunc)(void));

/**
Interrupt handler of HDMAC for transfer process is finished.<br>
The register value of CSTR is set to the argument of the callback function of the user registration.<br>
The type of the argument is "kushort*" type.

@param [in] ch				Channel number (0 to 3)
@remarks	This API uses ddim_user_custom_set_flg(priv->ddimUserCustom,).
@remarks	This API uses ddim_user_custom_clr_flg(priv->ddimUserCustom,).
@remarks	This API uses ddim_user_custom_twai_flg(priv->ddimUserCustom,).
*/
void	dd_hdmac_int_handler(DdHdmac *self, kuchar ch);

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/** @name Utility Functions
@{*/
/**
HDMAC forwarding between SDRAM-SDRAM.<br>
It waits until forwarding ends. (synchronization)

@param [in] ch			Channel number (0 to 3)
@param [in] src_addr	source address
@param [in] dst_addr	destination address
@param [in] size		transfer size
@param [in] waitMode	HDMAC end wait mode (DdHdmac_WAITMODE_CPU or DdHdmac_WAITMODE_EVENT)
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_EXC_LOCK_NG		Lock Error (System Using designated channel number)
@retval DdHdmac_BUSY_ERR			HDMAC is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
//这个方法的参数放到了类的self里满足传参少于5个
kint32	dd_hdmac_copy_sdram_sync(DdHdmac *self, kuchar ch, kulong size, kuint32 waitMode);

/**
HDMAC forwarding between SDRAM-SDRAM.<br>
It doesn't wait until the forwarding completion is done. (Asynchronization)

@param [in] ch			Channel number (0 to 3)
@param [in] src_addr	source address
@param [in] dst_addr	destination address
@param [in] size		transfer size
@param [in] *intHandler	Pointer of callback function
@retval DriverCommon_DDIM_OK					OK
@retval DdHdmac_INPUT_PARAM_ERR	Input Parameter Error
@retval DdHdmac_BUSY_ERR			HDMAC is being forwarded.
@remarks The unit of forwarding makes a large size give priority.<br>
         Please call Dd_HDMAC_Open() before calling this function.<br>
         Please call Dd_HDMAC_Close() when the HDMAC forwarding ends. <br>
         <br>
         Transfer MAX size of this API as following.<br>
         	WORD transfer (source address and destination address are 4byte alignment) : MAX size is 4MByte.<br>
         	HALF WORD transfer (source address and destination address are 2byte alignment) : MAX size is 2MByte.<br>
         	kuchar transfer (source address and destination address are 1byte alignment) : MAX size is 1MByte.<br>
*/
//这个方法的参数放到了类的self里满足传参少于5个
kint32	dd_hdmac_copy_sdram_async(DdHdmac *self, kuchar ch, kulong size, VpCallback intHandler);

/*@}*/
/*@}*/

/** @weakgroup dd_hdmac
@{
	<hr>
	Utility Functions
	- @ref HDMAC_Utility_SDRAM_Copy_Sync
	- @ref HDMAC_Utility_SDRAM_Copy_Async

	@section HDMAC_Utility_SDRAM_Copy_Sync		Sequence to use Dd_HDMAC_Copy_SDRAM_Sync()
	@image html 11_HDMAC_Utility_SDRAM_Copy_Sync.PNG

	@section HDMAC_Utility_SDRAM_Copy_Async		Sequence to use Dd_HDMAC_Copy_SDRAM_Async()
	@image html 12_HDMAC_Utility_SDRAM_Copy_Async.PNG
@}*/
//---------------------- colabo  section -------------------------------
#endif

#ifdef __cplusplus
}
#endif

/************************************************************************/
/* Sample Code															*/
/************************************************************************/
/** @weakgroup dd_hdmac
@{
	<hr>
	@section HDMAC_Sync_Sample_Dd_HDMAC_Ctrl_Common		Sample of HDMAC (Sync) (use Dd_HDMAC_Ctrl_Common)
	The example of executing synchronous processing is as follows.
	@code
	kint32                ret;
	kuint32               waitMode;
	kushort               status = 0;
	kuchar                ch;
	TDdHdmacCtrl      hdmac_ctrl;

	ch = 0;

	hdmac_ctrl.config_a.word = 0;
	hdmac_ctrl.config_a.bit.iS = DdHdmac_IS_SOFT;
	hdmac_ctrl.config_a.bit.bT = DdHdmac_BT_NORMAL;
	hdmac_ctrl.config_a.bit.bC = 0;
	hdmac_ctrl.config_a.bit.tC = (TRANS_SIZE / 4) -1;

	hdmac_ctrl.config_b.word = 0;
	hdmac_ctrl.config_b.bit.mS = DdHdmac_MS_BLK;
	hdmac_ctrl.config_b.bit.tW = DdHdmac_TW_WORD;
	hdmac_ctrl.config_b.bit.fS = DdHdmac_FS_INCR;
	hdmac_ctrl.config_b.bit.fD = DdHdmac_FD_INCR;
	hdmac_ctrl.config_b.bit.rc = DdHdmac_RC_DISABLE;
	hdmac_ctrl.config_b.bit.rs = DdHdmac_RS_DISABLE;
	hdmac_ctrl.config_b.bit.rd = DdHdmac_RD_DISABLE;

	hdmac_ctrl.src_addr = SRC_TOP_ADDR;
	hdmac_ctrl.dst_addr = DST_TOP_ADDR;
	hdmac_ctrl.IntHandlerFunc = 0;

	waitMode = DdHdmac_WAITMODE_CPU;

	ret = Dd_HDMAC_Open(ch, SEM_WAIT_TIME);
	if (ret != 0) {
		// ERROR
		return ;
	}
	while (1) {
		ret = Dd_HDMAC_Ctrl_Common(ch, &hdmac_ctrl);
		if (ret != 0) {
			// ERROR
			break;
		}
		ret = Dd_HDMAC_Start_Sync(ch, &status, waitMode);
		if (ret != 0) {
			// ERROR
			break;
		}
		break;
	}
	ret = Dd_HDMAC_Close(ch);
	if (ret != 0) {
		// ERROR
	}
	@endcode

	@section HDMAC_Sync_Sample_Dd_HDMAC_Ctrl_Trns		Sample of HDMAC (Sync) (use Dd_HDMAC_Ctrl_Trns)
	The example of executing synchronous processing is as follows.
	@code
	kint32                 ret;
	kuint32                waitMode;
	kushort                status = 0;
	kuchar                 ch;
	TDdHdmacCtrlTrns hdmac_ctrl_trns;

	ch = 0;

	hdmac_ctrl_trns.mode.input_sel = DdHdmac_IS_SOFT;
	hdmac_ctrl_trns.mode.mode_sel = DdHdmac_MS_BLK;
	hdmac_ctrl_trns.mode.src_fix = DdHdmac_FS_INCR;
	hdmac_ctrl_trns.mode.dst_fix = DdHdmac_FD_INCR;
	hdmac_ctrl_trns.mode.beat_type = DdHdmac_BT_NORMAL;

	hdmac_ctrl_trns.size.trns_width = DdHdmac_TW_WORD;
	hdmac_ctrl_trns.size.trns_size = TRANS_SIZE;
	hdmac_ctrl_trns.size.src_addr = SRC_TOP_ADDR;
	hdmac_ctrl_trns.size.dst_addr = DST_TOP_ADDR;

	hdmac_ctrl_trns.IntHandlerFunc = 0;

	waitMode = DdHdmac_WAITMODE_CPU;

	ret = Dd_HDMAC_Open(ch, SEM_WAIT_TIME);
	if (ret != 0) {
		// ERROR
		return ;
	}
	while (1) {
		ret = Dd_HDMAC_Ctrl_Trns(ch, &hdmac_ctrl_trns);
		if (ret != 0) {
			// ERROR
			break;
		}
		ret = Dd_HDMAC_Start_Sync(ch, &status, waitMode);
		if (ret != 0) {
			// ERROR
			break;
		}
		break;
	}
	ret = Dd_HDMAC_Close(ch);
	if (ret != 0) {
		// ERROR
	}
	@endcode

	@section HDMAC_Async_Sample		Sample of HDMAC (Async)
	The example of executing Asynchronous processing is as follows.
	@code
	kint32                 ret;
	kuint32                waitMode;
	kushort                status = 0;
	kuchar                 ch;
	TDdHdmacCtrlTrns hdmac_ctrl_trns;

	ch = 0;

	hdmac_ctrl_trns.mode.input_sel = DdHdmac_IS_SOFT;
	hdmac_ctrl_trns.mode.mode_sel = DdHdmac_MS_BLK;
	hdmac_ctrl_trns.mode.src_fix = DdHdmac_FS_INCR;
	hdmac_ctrl_trns.mode.dst_fix = DdHdmac_FD_INCR;
	hdmac_ctrl_trns.mode.beat_type = DdHdmac_BT_NORMAL;

	hdmac_ctrl_trns.size.trns_width = DdHdmac_TW_WORD;
	hdmac_ctrl_trns.size.trns_size = TRANS_SIZE;
	hdmac_ctrl_trns.size.src_addr = SRC_TOP_ADDR;
	hdmac_ctrl_trns.size.dst_addr = DST_TOP_ADDR;

	hdmac_ctrl_trns.IntHandlerFunc = sample_hdmac_callback;

	waitMode = DdHdmac_WAITMODE_EVENT;

	ret = Dd_HDMAC_Open(ch, SEM_WAIT_TIME);
	if (ret != 0) {
		// ERROR
		return ;
	}
	while (1) {
		ret = Dd_HDMAC_Ctrl_Trns(ch, &hdmac_ctrl_trns);
		if (ret != 0) {
			// ERROR
			break;
		}
		ret = Dd_HDMAC_Start_Async(ch);
		if (ret != 0) {
			// ERROR
			break;
		}
		ret = Dd_HDMAC_Wait_End(ch, &status, waitMode);
		if (ret != 0) {
			// ERROR
			break;
		}
		break;
	}
	ret = Dd_HDMAC_Close(ch);
	if (ret != 0) {
		// ERROR
	}
	@endcode
@}*/

#endif /* __DD_HDMAC_H__ */
