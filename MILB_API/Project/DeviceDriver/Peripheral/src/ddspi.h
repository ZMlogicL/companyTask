/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_spi
@{

	- @ref SPI_Channel_Specification
	- @ref SPI_Sample_Send_Recv
	- @ref SPI_Sample_Full_Duplex
	- @ref SPI_Sample_DMA_Util_Send_Recv
	- @ref SPI_Sample_DMA_Util_Full_Duplex

*/

#ifndef __DD_SPI_H__
#define __DD_SPI_H__

#include <klib.h>
#include "ddspidrive.h"

#define DD_TYPE_SPI                     (dd_spi_get_type())
#define DD_SPI(obj)                       K_TYPE_CHECK_INSTANCE_CAST(obj, DdSpi)
#define DD_IS_SPI(obj)                  K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SPI)

typedef struct _DdSpi                    DdSpi;
typedef struct _DdSpiPrivate        DdSpiPrivate;

struct _DdSpi
{
	KObject parent;
};

KConstType                         dd_spi_get_type(void);
DdSpi*                                 dd_spi_new(void);

#ifdef __cplusplus
extern "C" {
#endif

/*
*Interrupt handler for SPI macro.<br>
*@param [in]	ch
*Channel number(0 to 2)
*/
void                                     dd_spi_int_handler(kuchar ch);       //TODO  中断汇编调用

#ifdef __cplusplus
}
#endif
/*@}*/

/*
@weakgroup dd_spi
@{
	<hr>
	@section SPI_Channel_Specification SPI Channel Specification
		<table><tr>			<th>SPI ch</th>					<th>SSOUT max</th>	<th>Baudrate</th>	<th>FIFO size</th>	<th>Connect Gyro</th></tr>
		<tr align=right>	<td><b>0</b> (HW ch:1)</td>		<td>4</td>			<td>108MHz</td>		<td>128</td></tr>	<td>x</td></tr>
		<tr align=right>	<td><b>1</b> (HW ch:2)</td>		<td>4</td>			<td>50MHz</td>		<td>64</td></tr>	<td>x</td></tr>
		<tr align=right>	<td><b>2</b> (HW ch:3)</td>		<td>1</td>			<td>50MHz</td>		<td>16</td></tr>	<td>o</td></tr></table>
		Note:Channel number specify to the APIs, please from 0 to 2.<br>
	<br>
	<br>
	<hr>


	@section SPI_Sample_Send_Recv Sample of Send and Receive communication
	@code

	INT32			ret = D_DDIM_OK;
	kuchar			ch = 1;					// SPI ch:1
	kuchar			send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar			receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32			send_size = 10;
	kuint32			receive_size = 10;
	ULONG			baudrate = 100000000;	// 100 Mbps;
	kuchar			clk_div;
	INT32			index;
	T_DD_SPI_CTRL	spi_ctrl;

	ret = Dd_SPI_Calculate(baudrate, &clk_div);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("SPI Open ERR. ret=0x%x\n", ret));
		return ;
	}

	spi_ctrl.type				= E_DD_SPI_TYPE_MASTER;				// Master
	spi_ctrl.mode				= E_DD_SPI_MODE_2_CPOL1_CPHA0;		// Mode2:Clock Polarity=1, Clock Phase=0
	spi_ctrl.enable_sig			= E_DD_SPI_ENABLE_SIG_CPU;			// CPU. (software)
	spi_ctrl.bit_direction		= E_DD_SPI_BIT_DIR_MSB_FIRST;		// MSB first
	spi_ctrl.bit_length			= E_DD_SPI_BIT_LEN_8;				// 8 bit length
	spi_ctrl.clk_div			= clk_div;							// 100 Mbps
	spi_ctrl.delay_en			= 0;								// Disable delay (full speed)
	spi_ctrl.delay_val			= 0;								// Don't care
	spi_ctrl.rx_inhibit_en		= 0;								// Not inhibit
	spi_ctrl.fifo_wmark_tx		= 64;								// Half of TX FIFO
	spi_ctrl.fifo_wmark_rx		= 64;								// Half of RX FIFO
	spi_ctrl.dma_en				= 0;								// DMA disable
	spi_ctrl.dma_recv_to		= 0;								// Don't care
	spi_ctrl.ss_info.cont_trans	= E_DD_SPI_CONT_TRANS_INACT_BETWEEN;// ssOut goes inactive between successive transfers
	spi_ctrl.ss_info.sspol[0]	= 1;								// Select Slave for TX/RX
	spi_ctrl.ss_info.sspol[1]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[2]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[3]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.ssout[0]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[1]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[2]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[3]	= 0;								// SSOUT is an active Low
	spi_ctrl.pcallback			= 0;								// Synchronization
	spi_ctrl.pcallback_ss		= 0;								// Disable callback

	ret = Dd_SPI_Open(ch, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		// error correction code here.
		return ;
	}
	ret = Dd_SPI_Ctrl(ch, &spi_ctrl);

	// Transfer process
	ret = Dd_SPI_Set_Send_Data(ch, send_buf, send_size);
	ret = Dd_SPI_Start_Send(ch);

	Ddim_Print(("SPI Send Complete. ret=0x%x\n", ret));

	// Receive process
	ret = Dd_SPI_Set_Recv_Data(ch, receive_buf, receive_size);
	ret = Dd_SPI_Start_Recv(ch);

	Ddim_Print(("SPI Receive Complete. ret=0x%x\n", ret));

	for(index = 0; index < receive_size; index++){
		Ddim_Print(("receive_buf[%d]=0x%02X\n", index, receive_buf[index]));
	}

	ret = Dd_SPI_Close(ch);

	@endcode
	<br>
	<br>


	@section SPI_Sample_Full_Duplex Sample of Full-duplex communication
	@code

	// Sample Global Data
	static kuchar	g_send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	static kuchar	g_receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	static kuint32	g_fullduplex_size = 10;

	// Sample Callback Function
	static void sample_callback_function(kuchar ch, kuint32 result)
	{
		INT32 index;

		Ddim_Print(("SPI Callback\n"));
		for(index = 0; index < g_fullduplex_size; index++){
			Ddim_Print(("g_receive_buf[%d]=0x%02X\n", index, g_receive_buf[index]));
		}
	}

	@endcode
	<br>


	@code

	INT32			ret = D_DDIM_OK;
	kuchar			ch = 1;					// SPI ch:1
	kuchar			send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar			receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32			send_size = 10;
	kuint32			receive_size = 10;
	ULONG			baudrate = 100000000;	// 100 Mbps;
	kuchar			clk_div;
	T_DD_SPI_CTRL	spi_ctrl;

	ret = Dd_SPI_Calculate(baudrate, &clk_div);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("SPI Open ERR. ret=0x%x\n", ret));
		return ;
	}

	spi_ctrl.type				= E_DD_SPI_TYPE_MASTER;				// Master
	spi_ctrl.mode				= E_DD_SPI_MODE_2_CPOL1_CPHA0;		// Mode2:Clock Polarity=1, Clock Phase=0
	spi_ctrl.enable_sig			= E_DD_SPI_ENABLE_SIG_CPU;			// CPU. (software)
	spi_ctrl.bit_direction		= E_DD_SPI_BIT_DIR_MSB_FIRST;		// MSB first
	spi_ctrl.bit_length			= E_DD_SPI_BIT_LEN_8;				// 8 bit length
	spi_ctrl.clk_div			= clk_div;							// 100 Mbps
	spi_ctrl.delay_en			= 0;								// Disable delay (full speed)
	spi_ctrl.delay_val			= 0;								// Don't care
	spi_ctrl.rx_inhibit_en		= 0;								// Not inhibit
	spi_ctrl.fifo_wmark_tx		= 64;								// Half of TX FIFO
	spi_ctrl.fifo_wmark_rx		= 64;								// Half of RX FIFO
	spi_ctrl.dma_en				= 0;								// DMA disable
	spi_ctrl.dma_recv_to		= 0;								// Don't care
	spi_ctrl.ss_info.cont_trans	= E_DD_SPI_CONT_TRANS_INACT_BETWEEN;// ssOut goes inactive between successive transfers
	spi_ctrl.ss_info.sspol[0]	= 1;								// Select Slave for TX/RX
	spi_ctrl.ss_info.sspol[1]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[2]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[3]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.ssout[0]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[1]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[2]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[3]	= 0;								// SSOUT is an active Low
	spi_ctrl.pcallback			= sample_callback_function;			// Asynchronization
	spi_ctrl.pcallback_ss		= 0;								// Disable callback

	ret = Dd_SPI_Open(ch, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		// error correction code here.
		return ;
	}
	ret = Dd_SPI_Ctrl(ch, &spi_ctrl);

	// Transfer set
	ret = Dd_SPI_Set_Send_Data(ch, g_send_buf, g_fullduplex_size);

	// Receive set
	ret = Dd_SPI_Set_Recv_Data(ch, g_receive_buf, g_fullduplex_size);

	//
	// Demand the preparation to the slave side device according to the handshaking signal.
	// And the waited for preparation completion.
	//

	// Start communication
	ret = Dd_SPI_Start_Full_Duplex(ch);

	//
	// Communication completion is notified to the callback function.
	//

	@endcode
	<br>
	<br>


	@section SPI_Sample_DMA_Util_Send_Recv Sample of Send and Receive by DMA utility
	@code

	INT32			ret = D_DDIM_OK;
	kuchar			ch = 1;					// SPI ch:1
	kuchar			dma_ch = 5;				// HDMAC1 ch:5
	kuchar			send_buf[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x00,0x11};
	kuchar			receive_buf[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	kuint32			send_size = 10;
	kuint32			receive_size = 10;
	ULONG			baudrate = 100000000;	// 100 Mbps;
	kuchar			clk_div;
	INT32			index;
	T_DD_SPI_CTRL	spi_ctrl;

	ret = Dd_SPI_Calculate(baudrate, &clk_div);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("SPI Open ERR. ret=0x%x\n", ret));
		return ;
	}

	spi_ctrl.type				= E_DD_SPI_TYPE_MASTER;				// Master
	spi_ctrl.mode				= E_DD_SPI_MODE_2_CPOL1_CPHA0;		// Mode2:Clock Polarity=1, Clock Phase=0
	spi_ctrl.enable_sig			= E_DD_SPI_ENABLE_SIG_CPU;			// CPU. (software)
	spi_ctrl.bit_direction		= E_DD_SPI_BIT_DIR_MSB_FIRST;		// MSB first
	spi_ctrl.bit_length			= E_DD_SPI_BIT_LEN_8;				// 8 bit length
	spi_ctrl.clk_div			= clk_div;							// 100 Mbps
	spi_ctrl.delay_en			= 0;								// Disable delay (full speed)
	spi_ctrl.delay_val			= 0;								// Don't care
	spi_ctrl.rx_inhibit_en		= 0;								// Not inhibit
	spi_ctrl.fifo_wmark_tx		= 64;								// Half of TX FIFO
	spi_ctrl.fifo_wmark_rx		= 64;								// Half of RX FIFO
	spi_ctrl.dma_en				= 1;								// DMA disable
	spi_ctrl.dma_recv_to		= 0x00800000;						// 8388609 clock count
	spi_ctrl.ss_info.cont_trans	= E_DD_SPI_CONT_TRANS_INACT_BETWEEN;// ssOut goes inactive between successive transfers
	spi_ctrl.ss_info.sspol[0]	= 1;								// Select Slave for TX/RX
	spi_ctrl.ss_info.sspol[1]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[2]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[3]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.ssout[0]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[1]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[2]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[3]	= 0;								// SSOUT is an active Low
	spi_ctrl.pcallback			= 0;								// Synchronization
	spi_ctrl.pcallback_ss		= 0;								// Disable callback

	ret = Dd_SPI_Open(ch, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		// error correction code here.
		return ;
	}
	ret = Dd_SPI_Ctrl(ch, &spi_ctrl);

	// Transfer process
	ret = Dd_SPI_Set_Send_Data(ch, send_buf, send_size);
	ret = Dd_SPI_Start_Send_DMA(ch, dma_ch);

	Ddim_Print(("SPI Send Complete. ret=0x%x\n", ret));

	// Receive process
	ret = Dd_SPI_Set_Recv_Data(ch, receive_buf, receive_size);
	ret = Dd_SPI_Start_Recv_DMA(ch, dma_ch);

	for(index = 0; index < receive_size; index++){
		Ddim_Print(("receive_buf[%d]=0x%02X\n", index, receive_buf[index]));
	}

	Ddim_Print(("SPI Receive Complete. ret=0x%x\n", ret));

	ret = Dd_SPI_Close(ch);

	@endcode
	<br>
	<br>


	@section SPI_Sample_DMA_Util_Full_Duplex Sample of Full-duplex by DMA utility
	@code

	INT32			ret = D_DDIM_OK;
	kuchar			ch = 1;					// SPI ch:1
	kuchar			dma_ch_send = 5;		// HDMAC1 ch for send:5
	kuchar			dma_ch_recv = 6;		// HDMAC1 ch for recv:6
	ULONG			baudrate = 100000000; 	// 100 Mbps;
	kuchar			clk_div;
	T_DD_SPI_CTRL	spi_ctrl;

	ret = Dd_SPI_Calculate(baudrate, &clk_div);
	if(ret != D_DDIM_OK) {
		Ddim_Print(("SPI Open ERR. ret=0x%x\n", ret));
		return ;
	}

	spi_ctrl.type				= E_DD_SPI_TYPE_MASTER;				// Master
	spi_ctrl.mode				= E_DD_SPI_MODE_2_CPOL1_CPHA0;		// Mode2:Clock Polarity=1, Clock Phase=0
	spi_ctrl.enable_sig			= E_DD_SPI_ENABLE_SIG_CPU;			// CPU. (software)
	spi_ctrl.bit_direction		= E_DD_SPI_BIT_DIR_MSB_FIRST;		// MSB first
	spi_ctrl.bit_length			= E_DD_SPI_BIT_LEN_8;				// 8 bit length
	spi_ctrl.clk_div			= clk_div;							// 100 Mbps
	spi_ctrl.delay_en			= 0;								// Disable delay (full speed)
	spi_ctrl.delay_val			= 0;								// Don't care
	spi_ctrl.rx_inhibit_en		= 0;								// Not inhibit
	spi_ctrl.fifo_wmark_tx		= 64;								// Half of TX FIFO
	spi_ctrl.fifo_wmark_rx		= 64;								// Half of RX FIFO
	spi_ctrl.dma_en				= 1;								// DMA disable
	spi_ctrl.dma_recv_to		= 0x00800000;						// 8388609 clock count
	spi_ctrl.ss_info.cont_trans	= E_DD_SPI_CONT_TRANS_INACT_BETWEEN;// ssOut goes inactive between successive transfers
	spi_ctrl.ss_info.sspol[0]	= 1;								// Select Slave for TX/RX
	spi_ctrl.ss_info.sspol[1]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[2]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.sspol[3]	= 0;								// Do not select slave for TX/RX
	spi_ctrl.ss_info.ssout[0]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[1]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[2]	= 0;								// SSOUT is an active Low
	spi_ctrl.ss_info.ssout[3]	= 0;								// SSOUT is an active Low
	spi_ctrl.pcallback			= sample_callback_function;			// Asynchronization
	spi_ctrl.pcallback_ss		= 0;								// Disable callback

	ret = Dd_SPI_Open(ch, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		// error correction code here.
		return ;
	}
	ret = Dd_SPI_Ctrl(ch, &spi_ctrl);

	// Transfer set
	ret = Dd_SPI_Set_Send_Data(ch, g_send_buf, g_fullduplex_size);

	// Receive set
	ret = Dd_SPI_Set_Recv_Data(ch, g_receive_buf, g_fullduplex_size);

	//
	// Demand the preparation to the slave side device according to the handshaking signal.
	// And the waited for preparation completion.
	//

	// Start communication
	ret = Dd_SPI_Start_Full_Duplex_DMA(ch, dma_ch_send, dma_ch_recv);

	//
	// Communication completion is notified to the callback function.
	//

	@endcode
*/

/*@}*/

#endif /* __DD_SPI_H__ */
