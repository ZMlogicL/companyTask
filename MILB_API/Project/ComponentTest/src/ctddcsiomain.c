/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :杨升柄
*@brief               :CtDdCsioMain类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include "stdlib.h"
#include "string.h"
#include "dd_csio.h"
#include "dd_uart.h"
#include "dd_top.h"
#include "dd_hdmac1.h"
#include "dd_gic.h"
#include "dd_tmr32.h"
#include "uart_csio.h"
#include "ct_dd_csio.h"
#include "ctddcsio.h"
#include "ctddcsioprocess.h"
#include "ctddcsiomain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdCsioMain, ct_dd_csio_main);
#define CT_DD_CSIO_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdCsioMainPrivate,CT_TYPE_DD_CSIO_MAIN))

struct _CtDdCsioMainPrivate
{
	CtDdCsio *cdCsio;
};

static void ct_dd_csio_main_constructor(CtDdCsioMain *self) 
{
	CtDdCsioMainPrivate *priv = CT_DD_CSIO_MAIN_GET_PRIVATE(self);

	priv->cdCsio = ct_dd_csio_new();
	self->priv = priv;
}

static void ct_dd_csio_main_destructor(CtDdCsioMain *self) 
{
	CtDdCsioMainPrivate *priv = CT_DD_CSIO_MAIN_GET_PRIVATE(self);

	if(priv->cdCsio)
	{
		k_object_unref(priv->cdCsio);
	}
	priv->cdCsio = NULL;
}

/*
 * PUBLIC
 *
 * @brief  Command main function for CSIO test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 *
 *	The meaning of parameters
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| P1             | P2       |  P3         | P4          | P5        | P6     | P7  | P8     | Meaning                            |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| open           | ch       | tmout       |             |           |        |     |        | Dd_CSIO_Open()                     |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| close          | ch       |             |             |           |        |     |        | Dd_CSIO_Close()                    |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_type       | ch       | type        |             |           |        |     |        | Set Master or Slave                |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| cal            | cal_freq |             |             |           |        |     |        | Dd_CSIO_Calculate()                |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_test       | ch       | num         |             |           |        |     |        | Continuous execution               |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| ctrl           | Refer to the following tables.       |           |        |     |        | Dd_CSIO_Ctrl()                     |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_send       | ch       | data num    | sdram       |           |        |     |        | Dd_CSIO_Set_Send_Data()            | sdram:for send to SDRAM test
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_recv       | ch       | data num    | sdram       |           |        |     |        | Dd_CSIO_Set_Recv_Data()            | sdram:for recv to SDRAM test
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_send     | ch       |             |             |           |        |     |        | Dd_CSIO_Start_Send()               |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_send_dma | ch       | dmaCh      | dma_mode    |           |        |     |        | Dd_CSIO_Start_Send_DMA()           |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_recv_dma | ch       | dmaCh      | dma_mode    |           |        |     |        | Dd_CSIO_Start_Recv_DMA()           |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_recv     | ch       |             |             |           |        |     |        | Dd_CSIO_Start_Recv()               |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_full     | ch       |             |             |           |        |     |        | Dd_CSIO_Start_Full_Duplex()        |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_full_dma | ch       | dma_ch_send | dma_ch_recv |           |        |     |        | Dd_CSIO_Start_Full_Duplex_DMA()    |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| stop           | ch       |             |             |           |        |     |        | Dd_CSIO_Stop()                     |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| ut_send        | ch       | mode        | baudrate    | direction | length | dma | dmaCh | Dd_CSIO_Send()                     |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| get_ctrl       |          |             |             |           |        |     |        | Dd_CSIO_Get_Ctrl()                 |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_brate      | ch       | baudrate    |             |           |        |     |        | Dd_CSIO_Set_Baudrate()             |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| get_brate      | ch       |             |             |           |        |     |        | Dd_CSIO_Get_Baudrate()             |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_fset       | ch       | lost_detect |             |           |        |     |        | Dd_CSIO_Save_Send_FIFO_Pointer()   |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| set_fld        | ch       |             |             |           |        |     |        | Dd_CSIO_Reload_Send_FIFO_Pointer() |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| get_fld        | ch       |             |             |           |        |     |        | Dd_CSIO_Get_Reload_Status()        |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| reset_fifo     | ch       | fifo_num    |             |           |        |     |        | Dd_CSIO_Reset_FIFO()               |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| err            |          |             |             |           |        |     |        | Parameter error test               |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *	| start_stop     |          |             |             |           |        |     |        | Stop test during transfer(Sync)    |
 *	+----------------+----------+-------------+-------------+-----------+--------+-----+--------+------------------------------------+
 *
 *			ch			:	Chanel Number (0-5)
 *			in_freq		:	Input frequency
 *			cal_freq	:	Output frequency
 *			num			:	Test ID
 *			mode		:	Trasmit mode (0-3)
 *			baudrate	:	Baudrate
 *			direction	:	Bit direction (0=LSB first, 1=MSB first)
 *			length		:	Data bit length (5-9)
 *			data		:	Send data
 *			type		:	Type (0=Master, 1=Slave)
 *			data_num	:	Number of data
 *
 *
 *	The meaning of "ctrl" command parameters
 *	+----+---- +----+--------+---+--------+----+----------+-----+----+---------+-----+------+---+----------------+
 *	| P1 | P2  | P3 | P4     | P5| P6     | P7 | P8       | P9  | P10| P11     | P12 | P13  |P14| Meaning        |
 *	+----+-----+----+--------+---+--------+----+----------+-----+----+---------+-----+------+---+----------------+
 *	|ctrl| ch  |send|normal_h|lsb|[length]|sop0|[Baudrate]|fsel0|fe00|[fbyte_r]|fset0|flste0|cb0| Dd_CSIO_Ctrl() |
 *  |    |(0-5)|recv|normal_l|msb| (5-9)  |sop1|(bps)     |fsel1|fe12|(num)    |fset1|flste1|cb1|                |
 *  |    |     |    |spi_h   |   |        |    |          |     |fe10|         |     |      |   |                |
 *  |    |     |    |spi_l   |   |        |    |          |     |fe02|         |     |      |   |                |
 *	+----+-----+----+--------+---+--------+----+----------+-----+----+---------+-----+------+---+----------------+
 *
 * @return void
 */
void ct_dd_csio_main_test(CtDdCsioMain* self, kint argc, kchar** argv )
{
	CtDdCsioMainPrivate *priv = self->priv;
	kint32 ret;
	kuchar ch;
	kulong intid[2];
	kuchar dmaCh[2];
	kulong dmaIntid[2];
	kuchar num;
	kint32 index;
	kint32 tmout = D_DDIM_USER_SEM_WAIT_POL;
	kushort baudrate;
	T_DD_CSIO_CAL calTbl;
	T_DD_CSIO_CTRL csioCtrl;
	T_DD_CSIO_FIFO_CTRL fifoCtrl;

	csioCtrl.fifo_ctrl = &fifoCtrl;

	if( strcmp(argv[1], "open") == 0 ){
		// ch number
		ch = atoi( argv[2] );
		tmout = atoi(argv[3]);

		ret = Dd_CSIO_Open( ch, tmout );
		if (ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_CSIO_Open ERR. ret=0x%x\n", ret) );
		}
	}else if( strcmp(argv[1], "close") == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Close( ch );
		if (ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_CSIO_Close ERR. ret=0x%x\n", ret) );
		}
	}else if( strcmp(argv[1], "set_type") == 0 ){
		// ch number
		ch = atoi( argv[2] );

		// type
		priv->cdCsio->gType[ch] = (E_DD_CSIO_TYPE)atoi( argv[3] );
		Ddim_Print(("Master/Slave Type:\n"));
		for (index = 0; index < D_DD_USIO_CH_NUM_MAX; index++ ){
			Ddim_Print(("  CH[%d] =%d\n", index, priv->cdCsio->gType[index]));
		}

		ct_dd_csio_set_port(priv->cdCsio);
	}else if( strcmp(argv[1], "cal") == 0 ){
		calTbl.in_freq = atoi( argv[2] );

		ret = Dd_CSIO_Calculate( &calTbl );
		if (ret != D_DDIM_OK) {
			Ddim_Print( ("Dd_CSIO_Calculate ERR. ret=0x%x\n", ret) );
		}
	// Set CTRL data
	}else if( strcmp(argv[1], "ctrl") == 0 ){
		// ch number
		ch = atoi( argv[2] );

		// Type
		csioCtrl.type = priv->cdCsio->gType[ch];

		// Trasmit mode
		if( strcmp(argv[4], "normal_h") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
		}else if( strcmp(argv[4], "normal_l") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_L;
		}else if( strcmp(argv[4], "spi_h") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
		}else if( strcmp(argv[4], "spi_l") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
		}else
		{
			Ddim_Print(("please check 4th parameter!!\n"));
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[5], "lsb") == 0 ){
			csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
		}else if( strcmp(argv[5], "msb") == 0 ){
			csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
		}else
		{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		// Data bit length
		if( atoi(argv[6]) == 8 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
		}else if( atoi(argv[6]) == 5 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_5;
		}else if( atoi(argv[6]) == 6 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_6;
		}else if( atoi(argv[6]) == 7 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_7;
		}else if( atoi(argv[6]) == 9 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
		}else
		{
			Ddim_Print( ("please check 6th parameter!!\n" ) );
			return;
		}

		priv->cdCsio->gDataLength = csioCtrl.data_length;

		// Serial output port setting (0:uninfluential, 1:High )
		if( strcmp(argv[7], "sop0") == 0 ){
			csioCtrl.sop = 0;
		}else if( strcmp(argv[7], "sop1") == 0 ){
			csioCtrl.sop = 1;
		}else
		{
			Ddim_Print( ("please check 7th parameter!!\n" ) );
			return;
		}

		// Baudrate (bps)
		calTbl.in_freq  = atol(argv[8]);
		calTbl.cal_freq = 0;
		ret = Dd_CSIO_Calculate(&calTbl);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", ret));
			return;
		}
		csioCtrl.baudrate = calTbl.cal_freq;

		csioCtrl.sop = 0;

		// FIFO selection
		if( strcmp(argv[9], "fsel0") == 0 ){
			csioCtrl.fifo_ctrl->fsel = 0;
		}else if( strcmp(argv[9], "fsel1") == 0 ){
			csioCtrl.fifo_ctrl->fsel = 1;
		}else
		{
			Ddim_Print( ("please check 9th parameter!!\n" ) );
			return;
		}

		// FIFO 1/2 enable
		if( strcmp(argv[10], "fe00") == 0 ){
			// FIFO 1 enable              :Disable
			csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO 2 enable              :Disable
			csioCtrl.fifo_ctrl->fe2 = 0;
		}else if( strcmp(argv[10], "fe12") == 0 ){
			// FIFO 1 enable              :Enable
			csioCtrl.fifo_ctrl->fe1 = 1;
					// FIFO 2 enable              :Enable
		csioCtrl.fifo_ctrl->fe2 = 1;
		}else if( strcmp(argv[10], "fe10") == 0 ){
			// FIFO 1 enable              :Enable
			csioCtrl.fifo_ctrl->fe1 = 1;
			// FIFO 2 enable              :Disable
			csioCtrl.fifo_ctrl->fe2 = 0;
		}else if( strcmp(argv[10], "fe02") == 0 ){
			// FIFO 1 enable              :Disable
			csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO 2 enable              :Enable
			csioCtrl.fifo_ctrl->fe2 = 1;
		}else
		{
			Ddim_Print( ("please check 10th parameter!!\n" ) );
			return;
		}

		// FIFO receive data size
		csioCtrl.fifo_ctrl->fbyte_recv = atoi(argv[11]);

		// FIFO reload pointer
		if( strcmp(argv[12], "fset0") == 0 ){
			csioCtrl.fifo_ctrl->fset = 0;
		}else if( strcmp(argv[12], "fset1") == 0 ){
			csioCtrl.fifo_ctrl->fset = 1;
		}else
		{
			Ddim_Print( ("please check 12th parameter!!\n" ) );
			return;
		}

		// FIFO Data-lost check
		if( strcmp(argv[13], "flste0") == 0 ){
			csioCtrl.fifo_ctrl->flste = 0;
		}else if( strcmp(argv[13], "flste1") == 0 ){
			csioCtrl.fifo_ctrl->flste = 1;
		}else
		{
			Ddim_Print( ("please check 13th parameter!!\n" ) );
			return;
		}

		// Callback function
		if( strcmp(argv[14], "cb0") == 0 ){
			csioCtrl.pcallback = NULL;
		}else if( strcmp(argv[14], "cb1") == 0 ){
			csioCtrl.pcallback = ct_dd_csio_callback;
			priv->cdCsio->gAsync = 1;
		}else
		{
			Ddim_Print( ("please check 14th parameter!!\n" ) );
			return;
		}

		// Call API
		ret = Dd_CSIO_Ctrl(ch, &csioCtrl);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", ret));
		}
	// Set CTRL data(for Test)
	}else if( strcmp(argv[1], "ctrl_test") == 0 ){
		// ch number
		ch = atoi( argv[2] );

		// Type
		csioCtrl.type = priv->cdCsio->gType[ch];

		// Trasmit mode
		if( strcmp(argv[3], "normal_h") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
		}else if( strcmp(argv[3], "normal_l") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_L;
		}else if( strcmp(argv[3], "spi_h") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
		}else if( strcmp(argv[3], "spi_l") == 0 ){
			csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
		}else
		{
			Ddim_Print(("please check 3th parameter!!\n"));
			return;
		}

		// LSB first or MSB first
		if( strcmp(argv[4], "lsb") == 0 ){
			csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
		}else if( strcmp(argv[4], "msb") == 0 ){
			csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
		}else
		{
			Ddim_Print( ("please check 4th parameter!!\n" ) );
			return;
		}

		// Data bit length
		if( atoi(argv[5]) == 8 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
		}else if( atoi(argv[5]) == 5 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_5;
		}else if( atoi(argv[5]) == 6 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_6;
		}else if( atoi(argv[5]) == 7 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_7;
		}else if( atoi(argv[5]) == 9 ){
			csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
		}else
		{
			Ddim_Print( ("please check 5th parameter!!\n" ) );
			return;
		}

		priv->cdCsio->gDataLength = csioCtrl.data_length;

		// Serial output port setting (0:uninfluential, 1:High )
		csioCtrl.sop = 0;

		// Baudrate (bps)
		calTbl.in_freq  = atol(argv[6]);
		calTbl.cal_freq = 0;
		ret = Dd_CSIO_Calculate(&calTbl);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Cal ERR. ret=0x%x\n", ret));
			return;
		}
		csioCtrl.baudrate = calTbl.cal_freq;

		csioCtrl.sop = 0;

		// FIFO selection
		csioCtrl.fifo_ctrl->fsel = 0;

		// FIFO 1/2 enable
		// FIFO 1 enable              :Enable
		csioCtrl.fifo_ctrl->fe1 = 1;
		// FIFO 2 enable              :Enable
		csioCtrl.fifo_ctrl->fe2 = 1;

		// FIFO receive data size
		csioCtrl.fifo_ctrl->fbyte_recv = 1;

		// FIFO reload pointer
		csioCtrl.fifo_ctrl->fset = 0;

		// FIFO Data-lost check
		csioCtrl.fifo_ctrl->flste = 0;

		// Callback function
		if( strcmp(argv[7], "cb0") == 0 ){
			csioCtrl.pcallback = NULL;
			priv->cdCsio->gAsync = 0;
		}else if( strcmp(argv[7], "cb1") == 0 ){
			csioCtrl.pcallback = ct_dd_csio_callback;
			priv->cdCsio->gAsync = 1;
		}else
		{
			Ddim_Print( ("please check 7th parameter!!\n" ) );
			return;
		}

		// Call API
		ret = Dd_CSIO_Ctrl(ch, &csioCtrl);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Ctrl ERR. ret=0x%x\n", ret));
		}
	// Set send data
	}else if( strcmp(argv[1], "set_send") == 0 ){
		kuint32 idx;
		kuint32 idx2 = 0;

		// ch number
		ch = atoi( argv[2] );

		// Data size
		priv->cdCsio->gSendSize = atoi(argv[3]);

		if(strcmp(argv[4], "sdram") != 0){
			if (priv->cdCsio->gDataLength == E_DD_CSIO_DATA_LENGTH_9){
				for( idx = 0; idx < priv->cdCsio->gSendSize; idx += idx2 ){
					// 101010101
					priv->cdCsio->gBuf162[idx] = 0x155;
					// 9bit max
					for( idx2 = 1; idx2 < 512; idx2++ ){
						if( idx+idx2 >= priv->cdCsio->gSendSize ){
							break;
						}
						else{
							priv->cdCsio->gBuf162[idx+idx2] = idx2;
						}
					}
				}
				ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf162, priv->cdCsio->gSendSize);
			}else
			{
				for( idx = 0; idx < priv->cdCsio->gSendSize; idx += idx2 ){
					// 10101010
					priv->cdCsio->gBuf82[idx] = 0xAA;
					// 8bit max
					for( idx2 = 1; idx2 < 256; idx2++ ){
						if( idx+idx2 >= priv->cdCsio->gSendSize ){
							break;
						}
						else{
							priv->cdCsio->gBuf82[idx+idx2] = idx2;
						}
					}
				}
				ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf82, priv->cdCsio->gSendSize);
			}
		}else
		{
			ret = Dd_CSIO_Set_Send_Data(ch, (void*)CtDdCsio_HDMAC_DATA_ADDR_SEND, priv->cdCsio->gSendSize);
		}

		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Set Send Data ERR. ret=0x%x\n", ret));
		}
	// Set revceive data
	}else if( strcmp(argv[1], "set_recv") == 0 ){
		// ch number
		ch = atoi( argv[2] );

		// Data size
		priv->cdCsio->gSendSize = atoi(argv[3]);

		// Recv Buffer2 used
		priv->cdCsio->gBuf2Used = 1;

		if(strcmp(argv[4], "sdram") != 0){
			if (priv->cdCsio->gDataLength == E_DD_CSIO_DATA_LENGTH_9){
				memset(priv->cdCsio->gRcvBuf162, 0, sizeof(priv->cdCsio->gRcvBuf162));
				ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf162, priv->cdCsio->gSendSize);
			}else
			{
				memset(priv->cdCsio->gRcvBuf82, 0, sizeof(priv->cdCsio->gRcvBuf82));
				ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf82, priv->cdCsio->gSendSize);
			}
		}else
		{
			// Clear 4MB
			memset((void*)CtDdCsio_HDMAC_DATA_ADDR_RECV, 0, 4 * 1024 * 1024);
			ret = Dd_CSIO_Set_Recv_Data(ch, (void*)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
		}

		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Set Receive Data ERR. ret=0x%x\n", ret));
		}
	}else if( strcmp(argv[1], "set_test") == 0 ){
		//ch number
		ch = atoi( argv[2] );

		// Test number
		num = atoi( argv[3] );
		CtDdCsioProcess* csioProcess = ct_dd_csio_process_new();
		ct_dd_csio_process_set_csio(csioProcess, priv->cdCsio);
		ret = ct_dd_csio_process_test(csioProcess, ch, num );
		k_object_unref(csioProcess);
		csioProcess = NULL;
		if (ret != D_DDIM_OK) {
			Ddim_Print( ("ct_csio_process ERR. ret=0x%x\n", ret) );
		}
	}else if ( strcmp(argv[1], "get_ctrl") == 0 ){
		// ch number
		ch = atoi( argv[2] );
		ct_dd_csio_from_main_with_ctrl(priv->cdCsio, ch);
	}else if ( strcmp( argv[1], "start_send" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Start_Send(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Start Send ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "start_send_dma" ) == 0 ){
		kuchar dma_mode;

		// ch number
		ch = atoi( argv[2] );
		dmaCh[0] = atoi( argv[3] );
		dma_mode = atoi( argv[4] );

		intid[0] = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + ch;
		dmaIntid[0] = E_DD_GIC_INTID_HDMAC1_CH0_INT + dmaCh[0];

		// CSIO interrupt disable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 0, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt enable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 1, D_DD_GIC_PRI30, 0x1);

		if(priv->cdCsio->gDataLength == E_DD_CSIO_DATA_LENGTH_9){
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gBuf162, sizeof(priv->cdCsio->gBuf162));
		}else
		{
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gBuf82, sizeof(priv->cdCsio->gBuf82));
		}

		ret = Dd_CSIO_Start_Send_DMA(ch, dmaCh[0], dma_mode);

		// CSIO interrupt enable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 1, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt disable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 0, D_DD_GIC_PRI30, 0x1);

		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Start Send ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "start_recv" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Start_Recv(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Start Receive ERR. ret=0x%x\n", ret));
		}

		if((priv->cdCsio->gSendSize <= 300) && (!priv->cdCsio->gAsync)){
			if ( priv->cdCsio->gBuf2Used ) {
				for (index = 0; index < priv->cdCsio->gSendSize; index++ ){
					Ddim_Print(("Rcv_buf8_2[%d]=0x%X    Rcv_buf16_2[%d]=0x%X\n", index,
							priv->cdCsio->gRcvBuf82[index], index, priv->cdCsio->gRcvBuf162[index]));
				}
			}else
			{
				for (index = 0; index < priv->cdCsio->gSendSize; index++ ){
					Ddim_Print(("Rcv_buf8[%d]=0x%X    Rcv_buf16[%d]=0x%X\n", index,
							priv->cdCsio->gRcvBuf8[index], index, priv->cdCsio->gRcvBuf16[index]));
				}
			}
		}
	}else if ( strcmp( argv[1], "start_recv_dma" ) == 0 ){
		kuchar dma_mode;

		// ch number
		ch = atoi( argv[2] );
		dmaCh[0] = atoi( argv[3] );
		dma_mode = atoi( argv[4] );

		intid[0] = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + ch;
		dmaIntid[0] = E_DD_GIC_INTID_HDMAC1_CH0_INT + dmaCh[0];

		// CSIO interrupt disable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 0, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt enable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 1, D_DD_GIC_PRI30, 0x1);

		if(priv->cdCsio->gDataLength == E_DD_CSIO_DATA_LENGTH_9){
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gRcvBuf162, sizeof(priv->cdCsio->gRcvBuf162));
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gRcvBuf16, sizeof(priv->cdCsio->gRcvBuf16));
		}else
		{
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gRcvBuf82, sizeof(priv->cdCsio->gRcvBuf82));
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
			DDIM_User_L1l2cache_Clean_Flush_Addr((kulong)priv->cdCsio->gRcvBuf8, sizeof(priv->cdCsio->gRcvBuf8));
		}

		ret = Dd_CSIO_Start_Recv_DMA(ch, dmaCh[0], dma_mode);

		// CSIO interrupt enable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 1, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt disable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 0, D_DD_GIC_PRI30, 0x1);

		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Start Recv ERR. ret=0x%x\n", ret));
		}

		if((priv->cdCsio->gSendSize <= 300) && (!priv->cdCsio->gAsync)){
			if ( priv->cdCsio->gBuf2Used ) {
				for (index = 0; index < priv->cdCsio->gSendSize; index++ ){
					Ddim_Print(("priv->cdCsio->gRcvBuf82[%d]=0x%X    priv->cdCsio->gRcvBuf162[%d]=0x%X\n",
							index, priv->cdCsio->gRcvBuf82[index], index, priv->cdCsio->gRcvBuf162[index]));
				}
			}else if ( priv->cdCsio->gNonChacheAreaUsed ) {
				for (index = 0; index < priv->cdCsio->gSendSize; index++ ){
					Ddim_Print(("Rcv_Data8[%d]=0x%X    Rcv_Data16[%d]=0x%X\n", index,
							((kuchar*)CtDdCsio_HDMAC_DATA_ADDR_RECV)[index], index,
							((kushort*)CtDdCsio_HDMAC_DATA_ADDR_RECV)[index]));
				}
			}else
			{
				for (index = 0; index < priv->cdCsio->gSendSize; index++ ){
					Ddim_Print(("Rcv_buf8[%d]=0x%X    Rcv_buf16[%d]=0x%X\n",
							index, priv->cdCsio->gRcvBuf8[index], index, priv->cdCsio->gRcvBuf16[index]));
				}
			}
		}
	}else if ( strcmp( argv[1], "start_full" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Start_Full_Duplex(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Full Duplex Start ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "start_full_dma" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );
		dmaCh[0] = atoi( argv[3] );
		dmaCh[1] = atoi( argv[4] );

		intid[0] = E_DD_GIC_INTID_UART_CH0_RECEPTION_INT + ch;
		intid[1] = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + ch;
		dmaIntid[0] = E_DD_GIC_INTID_HDMAC1_CH0_INT + dmaCh[0];
		dmaIntid[1] = E_DD_GIC_INTID_HDMAC1_CH0_INT + dmaCh[1];

		// CSIO interrupt disable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 0, D_DD_GIC_PRI30, 0x1);
		// CSIO interrupt disable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[1], 0, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt enable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 1, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt enable
		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[1], 1, D_DD_GIC_PRI30, 0x1);

		if(priv->cdCsio->gDataLength == E_DD_CSIO_DATA_LENGTH_9){
			DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdCsio_HDMAC_DATA_ADDR_SEND, 0x00400000);
			DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdCsio_HDMAC_DATA_ADDR_RECV, 0x00400000);
		}else
		{
			DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdCsio_HDMAC_DATA_ADDR_SEND, 0x00400000);
			DDIM_User_L1l2cache_Clean_Flush_Addr(CtDdCsio_HDMAC_DATA_ADDR_RECV, 0x00400000);
		}

		ret = Dd_CSIO_Start_Full_Duplex_DMA(ch, dmaCh[0], dmaCh[1]);

		// CSIO interrupt enable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 1, D_DD_GIC_PRI30, 0x1);
		// CSIO interrupt enable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[1], 1, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt disable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 0, D_DD_GIC_PRI30, 0x1);
		// HDMAC1 interrupt disable
//		Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[1], 0, D_DD_GIC_PRI30, 0x1);

		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Full Duplex DMA ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "stop" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Stop(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Stop ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "ut_send" ) == 0 ){
		T_DD_CSIO_SEND_CTRL csioUtilCtrl;

		// ch number
		ch = atoi( argv[2] );

		csioUtilCtrl.mode 		 = (E_DD_CSIO_MODE) (atoi( argv[3] ));
		csioUtilCtrl.baudrate 	 = atol( argv[4] );
		csioUtilCtrl.bit_direction = (E_DD_CSIO_BIT_DIR) (atoi( argv[5] ));
		csioUtilCtrl.data_length	 = (E_DD_CSIO_DATA_LENGTH) (atoi( argv[6] ));

		if( atoi( argv[7] ) == 1 ){
			dmaCh[0] = atoi( argv[8] );

			csioUtilCtrl.fifo_dma_enable	 = 1;
			csioUtilCtrl.dma_ch			 = dmaCh[0];

			intid[0] = E_DD_GIC_INTID_UART_CH0_TRANSMISSION_INT + ch;
			dmaIntid[0] = E_DD_GIC_INTID_HDMAC1_CH0_INT + dmaCh[0];
			// CSIO interrupt disable
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 0, D_DD_GIC_PRI30, 0x1);
			// HDMAC1 interrupt enable
			Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 1, D_DD_GIC_PRI30, 0x1);

			ret = Dd_CSIO_Send( ch, &csioUtilCtrl, priv->cdCsio->gBuf8, 3 );
			// CSIO interrupt enable
			Dd_GIC_Ctrl((E_DD_GIC_INTID)intid[0], 1, D_DD_GIC_PRI30, 0x1);
			// HDMAC1 interrupt disable
			Dd_GIC_Ctrl((E_DD_GIC_INTID)dmaIntid[0], 0, D_DD_GIC_PRI30, 0x1);

			if (ret != D_DDIM_OK) {
				Ddim_Print( ("Dd_CSIO_Send ERR. ret=0x%x\n", ret) );
			}

		}else
		{
			csioUtilCtrl.fifo_dma_enable	 = 0;
			csioUtilCtrl.dma_ch			 = 0;

			ret = Dd_CSIO_Send( ch, &csioUtilCtrl, priv->cdCsio->gBuf8, 3 );
			if (ret != D_DDIM_OK) {
				Ddim_Print( ("Dd_CSIO_Send ERR. ret=0x%x\n", ret) );
			}
		}
	}else if ( strcmp( argv[1], "set_brate" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );
		// baudrate
		baudrate = atoi( argv[3] );

		ret = Dd_CSIO_Set_Baudrate(ch, baudrate);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Set_Baudrate ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "get_brate" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Get_Baudrate(ch, &baudrate);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Get_Baudrate ERR. ret=0x%x\n", ret));
		}else
		{
			Ddim_Print(("Dd_CSIO_Get_Baudrate: Baudrate=%d\n", baudrate));
		}
	}else if ( strcmp( argv[1], "set_fset" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );
		// lost_detect
		num = atoi( argv[3] );

		ret = Dd_CSIO_Save_Send_FIFO_Pointer(ch, num);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Save_Send_FIFO_Pointer ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "set_fld" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Reload_Send_FIFO_Pointer(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Reload_Send_FIFO_Pointer ERR. ret=0x%x\n", ret));
		}
	}else if ( strcmp( argv[1], "get_fld" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );

		ret = Dd_CSIO_Get_Reload_Status(ch);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Get_Reload_Status ERR. ret=0x%x\n", ret));
		}else
		{
			Ddim_Print(("Dd_CSIO_Get_Reload_Status: FLD = %d\n", ret));
		}
	}else if ( strcmp( argv[1], "reset_fifo" ) == 0 ){
		// ch number
		ch = atoi( argv[2] );
		// fifo_num
		num = atoi( argv[3] );

		ret = Dd_CSIO_Reset_FIFO(ch, num);
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("Dd_CSIO_Reset_FIFO ERR. ret=0x%x\n", ret));
		}
	}else if (strcmp(argv[1], "err") == 0){
		ct_dd_csio_from_main_with_err(priv->cdCsio, tmout, baudrate);
	}else if ( strcmp( argv[1], "start_stop" ) == 0 ){
		// ch number
		priv->cdCsio->gSendingChNumber = atoi( argv[2] );

		ret = Dd_TMR32_Open( CtDdCsio_TIMER_CH, D_DDIM_USER_SEM_WAIT_POL );
		if (ret != D_DDIM_OK) {
			Ddim_Print(("timer open error : ret=%d \n", ret));
			return;
		}

		ret = Dd_TMR32_SetTimer( CtDdCsio_TIMER_CH, 150*1000, ct_dd_csio_timer_handler_callback );
		if(ret != D_DDIM_OK) {
			Dd_TMR32_Stop(CtDdCsio_TIMER_CH);
			Dd_TMR32_Close(CtDdCsio_TIMER_CH);
			Ddim_Print(("timer set error : ret=%d \n", ret));
			return;
		}

		priv->cdCsio->gSendFlg = 1;
		ret = Dd_TMR32_Start(CtDdCsio_TIMER_CH);
		if(ret != D_DDIM_OK) {
			priv->cdCsio->gSendFlg = 0;
			Ddim_Print(("timer start error : ret=%d \n", ret));
			return;
		}

		ret = Dd_CSIO_Start_Send(priv->cdCsio->gSendingChNumber);
		Dd_TMR32_Stop(CtDdCsio_TIMER_CH);
		Dd_TMR32_Close(CtDdCsio_TIMER_CH);
		priv->cdCsio->gSendFlg = 0;
		priv->cdCsio->gSendingChNumber = 0;
		if (ret !=D_DDIM_OK) {
			Ddim_Print(("CSIO Start Send ERR. ret=0x%x\n", ret));
		}
	}else
	{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	return ;
}

CtDdCsioMain* ct_dd_csio_main_new(void) 
{
    CtDdCsioMain *self = k_object_new_with_private(CT_TYPE_DD_CSIO_MAIN, sizeof(CtDdCsioMainPrivate));
    return self;
}
