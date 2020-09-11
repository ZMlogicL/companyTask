/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-02
*@author              	:杨升柄
*@brief               	:CtDdCsioProcess类
*@rely                		:klib
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

K_TYPE_DEFINE_WITH_PRIVATE(CtDdCsioProcess, ct_dd_csio_process);
#define CT_DD_CSIO_PROCESS_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdCsioProcessPrivate,CT_TYPE_DD_CSIO_PROCESS))

struct _CtDdCsioProcessPrivate
{
	CtDdCsio *cdCsio;
};

static void ct_dd_csio_process_constructor(CtDdCsioProcess *self) 
{
	CtDdCsioProcessPrivate *priv = CT_DD_CSIO_PROCESS_GET_PRIVATE(self);

	priv->cdCsio = NULL;
	self->priv = priv;
}

static void ct_dd_csio_process_destructor(CtDdCsioProcess *self) 
{
}

/*
 * PUBLIC
 */
kint32 ct_dd_csio_process_test(CtDdCsioProcess* self, kuchar ch, kuchar num)
{
	CtDdCsioProcessPrivate* 	 priv;
	kint										 intData;
	kuchar* 								 sendP;
	kuchar* 								 recvP;

	priv = self->priv;
	intData = (kint)(num - '0');
	priv->cdCsio->csioCtrl.fifo_ctrl = &priv->cdCsio->fifoCtrl;
	priv->cdCsio->gBuf2Used = 0;
	priv->cdCsio->gNonChacheAreaUsed = 0;

	if(intData>0 && intData< 6)
	{
		priv->cdCsio->ret = ct_dd_csio_from_process(priv->cdCsio, ch, num);
		return priv->cdCsio->ret;
	}

	switch (num) {
		// PROCESS1 + FIFO
		case 6:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 0;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// PROCESS1 + FIFO + enable
		case 7:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_send_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// PROCESS1 + FIFO + DMA + 8bit
		case 8:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO2,Receive=FIFO1
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 1;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_send_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// PROCESS3 + DMA
		case 9:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf16, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		// Receive
		case 10:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_receive_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 11:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 0;

			priv->cdCsio->gSendSize = 3;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 12:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			// Transmit mode              :Nomal II
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_L;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :5 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_5;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_receive_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 13:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :1 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 1;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 0;

			priv->cdCsio->gSendSize = 3;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf16, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 14:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI II
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO2,Receive=FIFO1
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 1;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :1 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 1;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_receive_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// // #4 < none callback >
		case 15:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI II
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];

			// FIFO selection             :Send=FIFO2,Receive=FIFO1
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 1;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 1 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 0;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 0;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// #4 < fsel=0 FIFO1:send FIFO2:recieve >
		case 16:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			// Transmit mode              :SPI II
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_L;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :LSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_LSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :0 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_send_callback;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 3;

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf8, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 20:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			if( priv->cdCsio->gType[ch] == E_DD_CSIO_TYPE_MASTER ){
				sendP  = priv->cdCsio->gBuf8;
				recvP  = priv->cdCsio->gRcvBuf8;
			}else
			{
				sendP  = priv->cdCsio->gBuf8Slave;
				recvP  = priv->cdCsio->gRcvBuf8Slave;
			}
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :1 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 1;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_callback_full_duplex;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 8;

			memset(priv->cdCsio->gRcvBuf8, 0, sizeof(priv->cdCsio->gRcvBuf8));
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));
			memset(priv->cdCsio->gRcvBuf8Slave, 0, sizeof(priv->cdCsio->gRcvBuf8Slave));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, sendP, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, recvP, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 21:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :Nomal I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_NORMAL_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :1 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 1;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_callback_full_duplex;
			priv->cdCsio->gAsync = 1;
			priv->cdCsio->gSendSize = 3;
			memset(priv->cdCsio->gRcvBuf16, 0, sizeof(priv->cdCsio->gRcvBuf16));

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, priv->cdCsio->gBuf16, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, priv->cdCsio->gRcvBuf16, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		case 23:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :1 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 1;

			priv->cdCsio->csioCtrl.pcallback = 0;
			priv->cdCsio->gAsync = 0;
			priv->cdCsio->gSendSize = 3;
			priv->cdCsio->gNonChacheAreaUsed = 1;
			memset((void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, 0, 6);

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, (void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// Full Duplex + DMA(8bit)
		case 24:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :8 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_8;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 1 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe1 = 1;
			// FIFO receive data size     :128 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0x80;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_callback_full_duplex_dma;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 0x003FFFFF;

			memset((void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, 0, 0x00400000);

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch,
					(void *)CtDdCsio_HDMAC_DATA_ADDR_SEND, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, (void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;
		// Full Duplex + DMA(9bit)
		case 25:
			priv->cdCsio->calTbl.in_freq = 100000;
			priv->cdCsio->calTbl.cal_freq = 0;
			priv->cdCsio->ret = Dd_CSIO_Calculate(&priv->cdCsio->calTbl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Cal ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}

			// Transmit mode              :SPI I
			priv->cdCsio->csioCtrl.mode = E_DD_CSIO_MODE_SPI_SC_H;
			// Baudrate
			priv->cdCsio->csioCtrl.baudrate = priv->cdCsio->calTbl.cal_freq;
			// Serial output              :Output
			priv->cdCsio->csioCtrl.sop = 0;
			// Bit direction              :MSB First
			priv->cdCsio->csioCtrl.bit_direction = E_DD_CSIO_BIT_DIR_MSB_FIRST;
			// Data length                :9 bit
			priv->cdCsio->csioCtrl.data_length = E_DD_CSIO_DATA_LENGTH_9;
			// Type                       :Master/Slave
			priv->cdCsio->csioCtrl.type = priv->cdCsio->gType[ch];
			// FIFO selection             :Send=FIFO1,Receive=FIFO2
			priv->cdCsio->csioCtrl.fifo_ctrl->fsel = 0;
			// FIFO Data-lost check       :Disable
			priv->cdCsio->csioCtrl.fifo_ctrl->flste = 0;
			// FIFO pointer               :Not save
			priv->cdCsio->csioCtrl.fifo_ctrl->fset = 0;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO 2 enable              :Enable
			priv->cdCsio->csioCtrl.fifo_ctrl->fe2 = 1;
			// FIFO receive data size     :128 byte
			priv->cdCsio->csioCtrl.fifo_ctrl->fbyte_recv = 0x80;

			priv->cdCsio->csioCtrl.pcallback = ct_dd_csio_callback_full_duplex_dma;
			priv->cdCsio->gAsync = 1;

			priv->cdCsio->gSendSize = 0x00200000;
			priv->cdCsio->gDataLength = E_DD_CSIO_DATA_LENGTH_9;

			memset((void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, 0, 0x00400000);

			priv->cdCsio->ret = Dd_CSIO_Open(ch, priv->cdCsio->tmout);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Open ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Ctrl(ch, &priv->cdCsio->csioCtrl);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Ctrl ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Send_Data(ch, (void *)CtDdCsio_HDMAC_DATA_ADDR_SEND, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Send Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			priv->cdCsio->ret = Dd_CSIO_Set_Recv_Data(ch, (void *)CtDdCsio_HDMAC_DATA_ADDR_RECV, priv->cdCsio->gSendSize);
			if (priv->cdCsio->ret !=D_DDIM_OK) {
				Ddim_Print(("CSIO Set Receive Data ERR. priv->cdCsio->ret=0x%x\n", priv->cdCsio->ret));
			}
			break;

		default:
			break;
	}
	return priv->cdCsio->ret;
}

void ct_dd_csio_process_set_csio(CtDdCsioProcess* self, CtDdCsio *cdCsio)
{
	CtDdCsioProcessPrivate* priv = self->priv;
	priv->cdCsio = cdCsio;
}

CtDdCsioProcess* ct_dd_csio_process_new(void) 
{
    CtDdCsioProcess *self = k_object_new_with_private(CT_TYPE_DD_CSIO_PROCESS, sizeof(CtDdCsioProcessPrivate));
    return self;
}
