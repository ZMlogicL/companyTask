/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :SLIMbus Driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_slimbus
@{
	- @ref dd_slimbus_manager_start_sample
	- @ref dd_slimbus_configration_sample
	- @ref dd_slimbus_data_write_sample
	- @ref dd_slimbus_data_read_sample
	- @ref dd_slimbus_disconnet_sample
	- @ref dd_slimbus_manager_stop_sample
*/

#ifndef __DD_SLIMBUS_H__
#define __DD_SLIMBUS_H__

#include <klib.h>
#include "driver_common.h"

#define DD_TYPE_SLIMBUS                            (dd_slimbus_get_type())
#define DD_SLIMBUS(obj)                              K_TYPE_CHECK_INSTANCE_CAST(obj, DdSlimbus)
#define DD_IS_SLIMBUS(obj)                         K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SLIMBUS)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return values
/*< Input parameter error			*/
#define DdSlimbus_INPUT_PARAM_ERROR		(D_DD_SLIMBUS | D_DDIM_INPUT_PARAM_ERROR)
/*< Overflow */
#define DdSlimbus_OVERFLOW_ERR			        (D_DD_SLIMBUS | D_DDIM_OVERFLOW_ERR)
/*< Job Processing  */
#define DdSlimbus_PROCESSING				        (D_DD_SLIMBUS | D_DDIM_PROCESSING)
/*< Semaphore acquisition NG		*/
#define DdSlimbus_SEM_NG					            (D_DD_SLIMBUS | D_DDIM_SEM_NG)
/*< Semaphore acquisition Time Out	*/
#define	DdSlimbus_SEM_TIMEOUT			            (D_DD_SLIMBUS | D_DDIM_SEM_TIMEOUT)
/*< Abnormal Status				*/
#define	DdSlimbus_STATUS_ABNORMAL		    (D_DD_SLIMBUS | D_DDIM_STATUS_ABNORMAL)
/*< DMA stop status error. */
#define DdSlimbus_DMA_SS_ERROR			        (D_DD_SLIMBUS | D_DDIM_BUS_ERROR)

typedef struct _TDdSlimbusCtrl           TDdSlimbusCtrl;

typedef struct _WriteDataParam        WriteDataParam;
typedef struct _ReadDataParam         ReadDataParam;

typedef struct _DdSlimbus                   DdSlimbus;
typedef struct _DdSlimbusPrivate       DdSlimbusPrivate;

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/* SLIMBus channel */
typedef enum {
	/*< Channel 0	*/
	DdSlimbus_CH0 = 0,
	/*< Channel 1	*/
	DdSlimbus_CH1,
	/*< Channel 2	*/
	DdSlimbus_CH2,
	/*< Channel 3	*/
	DdSlimbus_CH3,
}EDdSlimbusCh;

/* Manager mode */
typedef enum {
	/*< Manager mode disable	*/
	DdSlimbus_MANAGER_MODE_DISABLE = 0,
	/*< Manager mode enable	*/
	DdSlimbus_MANAGER_MODE_ENABLE
}DdSlimbusManagerMode;

/* Framer enable */
typedef enum {
	/*< Framer disable	*/
	DdSlimbus_FR_DISABLE = 0,
	/*< Framer enable	*/
	DdSlimbus_FR_ENABLE
}DdSlimbusFrEn;

/*
*Type is defined to Callback function pointer when complete communication.<br>
*@param [in]	ch			Channel number(0 to 3)
*@param [in] status		Interrupt status.
*/
typedef void (*VpSlimbusCallback)(kuchar ch, kint32 status);

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* SLIMBus control data. */
struct _TDdSlimbusCtrl
{
	/*< SLIMBus channel		*/
	EDdSlimbusCh				ch;
	/*< Manager mode	*/
	DdSlimbusManagerMode	managerMode;
	/*< framer enable			*/
	DdSlimbusFrEn			frEn;
	/*< source threshold (0 to 63)	*/
	kuchar						srcThr;
	/*< sink threshold (0 to 63)	*/
	kuchar						sinkThr;
	/*< Callback function pointer when manager interrupt is generated.<br>
	*The following are set to argument status of callback.<br>
	*bit1: RX_INT(Set HIGH when enabled and RX_FIFO is not empty.)<br>
	*bit2: TX_INT(Set HIGH when enabled and TX_FIFO becomes empty (after transmitting all messages).)<br>
	*bit3: TX_ERR(Set HIGH when enabled and when message from TX_FIFO is not transmitted successfully.)<br>
	*bit4: SYNC_LOST(Set HIGH when enabled and when any of main synchronization bits (F_SYNC, SF_SYNC,M_SYNC)
	*toggles into LOW, and the IP is not detached due to REPORT_ABSENT message.)<br>
	*bit7: PORT_INT(HIGH when bit of PINT register is HIGH.) */
	VpSlimbusCallback			managerIntCb;
	/*< Callback function pointer when data port interrupt is generated.<br>
	*The following are set to argument status of callback.<br>
	*bit0: ACT_INT(Channel activation)<br>
	*bit1: CON_INT(Channel content definition)<br>
	*bit2: CHAN_INT(Channel definition)<br>
	*bit4: OVF_ERR(Data Port FIFO overflow)<br>
	*bit5: UND_INT(Data port FIFO underrun) */
	VpSlimbusCallback			dataPortIntCb;
};

struct _WriteDataParam
{
	EDdSlimbusCh ch;
	kuchar              dmaCh;
	kuint32*           data;
	kuint32             count;
	VpSlimbusCallback pCallback;
};

struct _ReadDataParam
{
	EDdSlimbusCh ch;
	kuchar              dmaCh;
	kuint32*           data;
	kuint32             count;
	VpSlimbusCallback pCallback;
};

struct _DdSlimbus
{
	KObject parent;
};

KConstType                   dd_slimbus_get_type(void);
DdSlimbus*                   dd_slimbus_get(void);

/*----------------------------------------------------------------------*/
/* Function 															*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
//---------------------------- driver section ----------------------------
/*
*Execute exclusive control for designated SLIMBus channel.<br>
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@param[in]	tmout	Time of timeout<br>
*					<ul><li>Positive Value(Time of timeout)
*						<li>@ref D_DDIM_USER_SEM_WAIT_POL
*						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SLIMBUS_SEM_TIMEOUT		: Semaphore acquisition Time Out
*@retval		D_DD_SLIMBUS_SEM_NG				: Semaphore acquisition NG
*@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32                             dd_slimbus_open(DdSlimbus* self, EDdSlimbusCh ch, kint32 tmout);

/*
*Cancel exclusive control for designated SLIMBus channel.<br>
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@retval		D_DDIM_OK			: OK
*@remarks	This API uses DDIM_User_Sig_Sem().
*/
kint32                             dd_slimbus_close(DdSlimbus* self, EDdSlimbusCh ch);

/*
*Set SLIMBus operation condition and callback function for the specified channel.
*@param [in]	slimbusCtrl	SLIMBus Control data. See @ref TDdSlimbusCtrl.
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                             dd_slimbus_ctrl(DdSlimbus* self, TDdSlimbusCtrl const* const slimbusCtrl);

/*
*Get SLIMBus operation condition and callback function for the specified channel.
*@param[in]		ch				Channel number.	See @ref EDdSlimbusCh.
*@param [out]	slimbusCtrl	SLIMBus Control data. See @ref TDdSlimbusCtrl.
*@retval			D_DDIM_OK						: OK
*@retval			DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                             dd_slimbus_get_ctrl(DdSlimbus* self, EDdSlimbusCh ch,
		                                       TDdSlimbusCtrl* const slimbusCtrl);

/*
*Start SLIMBus Manager.<br>
*@param[in]	ch	Channel number.	See @ref EDdSlimbusCh.
*@retval		D_DDIM_OK	: OK
*/
kint32                             dd_slimbus_start(DdSlimbus* self, EDdSlimbusCh ch);

/*
*Stop SLIMBus Manager.<br>
*@param[in]	ch	Channel number.	See @ref EDdSlimbusCh.
*@retval		D_DDIM_OK	: OK
*/
kint32                             dd_slimbus_stop(DdSlimbus* self, EDdSlimbusCh ch);

/*
*Interrupt handler for SLIMBus macro.<br>
*@param [in]	ch	Channel number.	See @ref EDdSlimbusCh.
*/
void                               dd_slimbus_int_handler(EDdSlimbusCh ch);   //TODO 中断汇编调用

/*
*Write message to MC_FIFO(TX_FIFO).<br>
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@param[in]	msg		Message address.
*@param[in]	size	Message size(1 to 64).
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error.
*@retval		D_DD_SLIMBUS_PROCESSING			: Transmission is being processed.
*/
kint32                             dd_slimbus_write_msg(DdSlimbus* self, EDdSlimbusCh ch,
		                                     kuint32* msg, kuint32 size);

/*
*Read message from MC_FIFO(RX_FIFO).<br>
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@param[out]	msg		Message address.
*@param[out]	size	Message size.
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error.
*@retval		D_DD_SLIMBUS_OVERFLOW_ERR		:
*Overflow indication – at least 1 message has been lost due to overflow in RX_FIFO.
*/
kint32                             dd_slimbus_read_msg(DdSlimbus* self, EDdSlimbusCh ch,
		                                     kuint32* msg, kuint32* size);

/*
*Write data to P0_FIFO.<br>
*@param[in]	ch			Channel number.	See @ref EDdSlimbusCh.
*@param[in]	dmaCh		DMA channel number(0 to 7)
*@param[in]	data		Write Data address.
*@param[in]	count		Write count(1 to 64). Writing one word is executed by one count.
*@param[in]	pCallback	Callback function pointer when writing is completed.
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error.
*@retval		D_DD_SLIMBUS_STATUS_ABNORMAL	: Abnormal Status.
*/
kint32                             dd_slimbus_write_data(DdSlimbus* self, WriteDataParam writeDataParam);

/*
*Read data from P0_FIFO.<br>
*@param[in]	ch			Channel number.	See @ref EDdSlimbusCh.
*@param[in]	dmaCh		DMA channel number(0 to 7)
*@param[out]	data		Read Data address.
*@param[in]	count		Read count(1 to 64). Reading one word is executed by one count.
*@param[in]	pCallback	Callback function pointer when reading is completed.
*@retval		D_DDIM_OK						: OK
*@retval		DdSlimbus_D_DD_SLIMBUS_INPUT_PARAM_ERROR	: Input parameter error.
*@retval		D_DD_SLIMBUS_STATUS_ABNORMAL	: Abnormal Status.
*/
kint32                             dd_slimbus_read_data(DdSlimbus* self, ReadDataParam readDataParam);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
@{*/
/*
*Get SLIMBus register value.
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@param[in]	offset	Offset of SLIMBus register.
*@param[out]	data	Get data.
*@retval D_DDIM_OK					OK
*@retval DdSlimbusManagerMode	Violation of word boundary or reservation register.
*/
kint32                             dd_slimbus_get_reg(DdSlimbus* self, EDdSlimbusCh ch,
		                                     kushort offset, kuint32* data);

/*
*Set SLIMBus register value.
*@param[in]	ch		Channel number.	See @ref EDdSlimbusCh.
*@param[in]	offset	Offset of SLIMBus register.
*@param[in]	data	Set data.
*@retval D_DDIM_OK					OK
*@retval DdSlimbusManagerMode	Violation of word boundary or reservation register.
*/
kint32                             dd_slimbus_set_reg(DdSlimbus* self, EDdSlimbusCh ch,
		                                     kushort offset, kuint32 data);

/*  @}*/
#endif

#ifdef __cplusplus
}
#endif

/*@}*/

/*
@weakgroup dd_slimbus
@{
	<br>
	<br>
	The example of SLIMBus is as follows.<br>
	Sample code, use the PCIE to the opposing device. (SLIMBus ch0 -> ch1 transfer)
	<hr>

	@section dd_slimbus_manager_start_sample	Sample of SLIMBus Manager Start.
	@code
	static kint32 slimbus_read_msg(EDdSlimbusCh ch)
	{
		kint32	ret;
		kuint32	size;
		kuint32	rx_msg[16];
		kuchar	loop, i;

		memset(rx_msg, 0, sizeof(rx_msg));
		ret =Dd_Slimbus_Read_Msg(ch, rx_msg, &size);
		if(ret != D_DDIM_OK){
			Ddim_Print(("Dd_Slimbus_Read_Msg(%d) Error. Return Value=0x%08X\n", ch, ret));
			return ret;
		}

		loop = (size >> 2);
		if(size & 0x3){
			loop++;
		}
		Ddim_Print(("-- Read Message size:%d(byte) --\n", size));
		for(i=0;i<loop;i++){
			Ddim_Print(("MC_FIFO[%d]=0x%08X\n", i, rx_msg[i]));
		}

		return D_DDIM_OK;
	}

	static void slimbus_manager_int_cb(kuchar ch, kint32 status)
	{
		kint32	ret;

		// status
		// bit1: RX_INT
		// bit2: TX_INT
		// bit3: TX_ERR
		// bit4: SYNC_LOST
		// bit7: PORT_INT
		Ddim_Print(("ch=%d, Status=0x%08X\n", ch, status));

		if(status & 0x00000002){	// RX_INT
			ret = slimbus_read_msg(ch);
			if(ret != D_DDIM_OK){
				Ddim_Print(("slimbus_read_msg Error. ret=0x%08x\n", ret));
			}
		}

		if(status & 0x00000004){	// TX_INT
			g_Tx_Int_Flag[ch] = 1;
		}
	}

	static void slimbus_data_port_int_cb(kuchar ch, kint32 status)
	{
		// status
		// bit0: ACT_INT
		// bit1: CON_INT
		// bit2: CHAN_INT
		// bit4: OVF_ERR
		// bit5: UND_INT
		Ddim_Print(("ch=%d, Status=0x%08X\n", ch, status));
	}

	void SLIMBus_Manager_Start(EDdSlimbusCh ch)
	{
		kint32				ret;
		TDdSlimbusCtrl	slimbusCtrl;

		ret = Dd_Slimbus_Open(ch, D_DDIM_USER_SEM_WAIT_POL);
		if(ret != D_DDIM_OK){
			Ddim_Print(("Dd_Slimbus_Open Error. ret=0x%08x\n", ret));
			return;
		}

		slimbusCtrl.ch					= ch;
		slimbusCtrl.manager_mode		= E_DD_SLIMBUS_MANAGER_MODE_ENABLE;
		slimbusCtrl.fr_en				= E_DD_SLIMBUS_FR_ENABLE;
		slimbusCtrl.src_thr			= 16;
		slimbusCtrl.sink_thr			= 0;
		slimbusCtrl.manager_int_cb		= (VpSlimbusCallback)slimbus_manager_int_cb;
		slimbusCtrl.data_port_int_cb	= (VpSlimbusCallback)slimbus_data_port_int_cb;
		ret = Dd_Slimbus_Ctrl(&slimbusCtrl);
		if(ret != D_DDIM_OK){
			Ddim_Print(("Dd_Slimbus_Open Error. ret=0x%08x\n", ret));
			return;
		}
	}
	@endcode

	<br>
	<br>
	@section dd_slimbus_configration_sample	Sample of SLIMBus Configration.
	@code
	#define	CONFIG_MSG_NUM	(16)

	// ch0(manager) -> ch1(peri device) transfer slimbus message table
	static T_MC_FIFO_MSG	g_MC_FIFO_Tx_Msg[] = {
	// ASSIGN_LOGICAL_ADDRESS
		// ch1 Interface Device (LA=0x40)
		{0x10, {0x020AFFF3, 0x008C0311, 0x40010000, 0x00000050}},	// 0
		// ch1 Generic Device (LA=0x42)
		{0x10, {0x020AFFF3, 0x008C0311, 0x42010200, 0x00000050}},	// 1
		// ch0 Interface Device (LA=0x30)
		{0x10, {0x020AFFF3, 0x008C0311, 0x30000000, 0x000000D0}},	// 2
		// ch0 Generic Device (LA=0x32)
		{0x10, {0x020AFFF3, 0x008C0311, 0x32000200, 0x00000070}},	// 3
		// ch0 Framer Device (LA=0x31)
		{0x10, {0x020AFFF3, 0x008C0311, 0x31000100, 0x00000080}},	// 4
	// REQUEST_SELF_ANNOUNCEMENT
		{0x8,  {0x0C03FFF3, 0x00000035, 0x00000000, 0x00000000}},	// 5
	// BEGIN_RECONFIGURATION
		{0x8,  {0x4003FFF3, 0x00000035, 0x00000000, 0x00000000}},	// 6
	// NEXT_ROOT_FREQUENCY
		{0x8,  {0x4704FFF3, 0x00300133, 0x00000000, 0x00000000}},	// 7
	// NEXT_CLOCK_GEAR
		{0x8,  {0x4604FFF3, 0x00B00936, 0x00000000, 0x00000000}},	// 8
	// NEXT_SUBFRAME_MODE
		{0x8,  {0x4504FFF3, 0x00C01339, 0x00000000, 0x00000000}},	// 9
	// CONNECT_SOURCE
		{0xc,  {0x1006FFF3, 0x1B00320C, 0x000000A0, 0x00000000}},	// 10
	// CONNECT_SINK
		{0xc,  {0x1106FFF3, 0x1B004209, 0x000000F0, 0x00000000}},	// 11
	// NEXT_DEFINE_CHANNEL
		{0xc,  {0x5007FFF3, 0x1C461B39, 0x00009009, 0x00000000}},	// 12
	// NEXT_DEFINE_CONTENT
		{0xc,  {0x5107FFF3, 0x01111B37, 0x00005008, 0x00000000}},	// 13
	// ACTIVATE_CHANNEL
		{0x8,  {0x5404FFF3, 0x00B01B33, 0x00000000, 0x00000000}},	// 14
	// RECONFIGURE_NOW
		{0x8,  {0x5F03FFF3, 0x0000003C, 0x00000000, 0x00000000}},	// 15
	// DISCONNECT_PORT(SOURCE)
		{0xc,  {0x1405FFF3, 0xA000420D, 0x00000000, 0x00000000}},	// 16
	// DISCONNECT_PORT(SINK)
		{0xc,  {0x1405FFF3, 0xB000320D, 0x00000000, 0x00000000}},	// 17
	};

	void SLIMBus_Configration(EDdSlimbusCh ch)
	{
		kint32			ret;
		kuchar			index;
		DDIM_USER_ER	ercd;

		for(index=0 ; index<CONFIG_MSG_NUM ; index++){
			g_Tx_Int_Flag[ch] = 0;
			ret = Dd_Slimbus_Write_Msg(ch, &g_MC_FIFO_Tx_Msg[index].msg[0], g_MC_FIFO_Tx_Msg[index].size);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Dd_Slimbus_Write_Msg_Tx_Fifo Error. ret=0x%08x\n", ret));
			}

			while(1){
				ercd = DDIM_User_Dly_Tsk(1);	// 1ms wait
				if (ercd != D_DDIM_USER_E_OK){
					Ddim_Print(("DDIM_User_Dly_Tsk Error. ercd = %d\n", ercd));
				}
				if(g_Tx_Int_Flag[ch] == 1){
					break;
				}
			}
		}
	}
	@endcode

	<br>
	<br>
	@section dd_slimbus_data_write_sample	Sample of SLIMBus Data Write.
	@code
	static void slimbus_dma_int_write_cb(kuchar dmaCh, kint32 status)
	{
		// status
		// 0x00000000:Normal End
		// else      :Error
		Ddim_Print(("dmaCh=%d, Status=0x%08X\n", dmaCh, status));
	}

	void SLIMBus_Data_Write(EDdSlimbusCh ch)
	{
		kint32	ret;

		ret = Dd_Slimbus_Write_Data(ch, 4, (kuint32*)g_Write_Data, 0x10, (VpSlimbusCallback)slimbus_dma_int_write_cb);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Dd_Slimbus_Write_Data Error. ret=0x%08x\n", ret));
			}
	}
	@endcode

	<br>
	<br>
	@section dd_slimbus_data_read_sample	Sample of SLIMBus Data Read.
	@code
	static void slimbus_dma_int_read_cb(kuchar dmaCh, kint32 status)
	{
		// status
		// 0x00000000:Normal End
		// else      :Error
		Ddim_Print(("dmaCh=%d, Status=0x%08X\n", dmaCh, status));
	}

	void SLIMBus_Data_Read(EDdSlimbusCh ch)
	{
		kint32	ret;
		kuint32	read_data[16];

		ret = Dd_Slimbus_Read_Data(ch, 3, &read_data, 0x10, (VpSlimbusCallback)slimbus_dma_int_read_cb);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Dd_Slimbus_Read_Data Error. ret=0x%08x\n", ret));
			}
	}
	@endcode

	<br>
	<br>
	@section dd_slimbus_disconnet_sample	Sample of SLIMBus Port Disconnect.
	@code
	void SLIMBus_Port_Disconnect(EDdSlimbusCh ch)
	{
		kint32			ret;
		kuchar			index;
		DDIM_USER_ER	ercd;

		for(index=CONFIG_MSG_NUM ; index<CONFIG_MSG_NUM+2 ; index++){
			g_Tx_Int_Flag[ch] = 0;
			ret = Dd_Slimbus_Write_Msg(ch, &g_MC_FIFO_Tx_Msg[index].msg[0], g_MC_FIFO_Tx_Msg[index].size);
			if(ret != D_DDIM_OK){
				Ddim_Print(("Dd_Slimbus_Write_Msg Error. ret=0x%08x\n", ret));
			}

			while(1){
				ercd = DDIM_User_Dly_Tsk(1);	// 1ms wait
				if (ercd != D_DDIM_USER_E_OK){
					Ddim_Print(("DDIM_User_Dly_Tsk Error. ercd = %d\n", ercd));
				}
				if(g_Tx_Int_Flag[ch] == 1){
					break;
				}
			}
		}
	}
	@endcode

	<br>
	<br>
	@section dd_slimbus_manager_stop_sample	Sample of SLIMBus Manager Stop.
	@code
	void SLIMBus_Manager_Stop(EDdSlimbusCh ch)
	{
		kint32	ret;

		ret = Dd_Slimbus_Stop(ch);
		if(ret != D_DDIM_OK){
			Ddim_Print(("Dd_Slimbus_Stop Error. ret=0x%08x\n", ret));
		}
	}
	@endcode
@}*/

#endif /* __DD_SLIMBUS_H__ */
