/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :杨升柄
*@brief               :CtDdCsio类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_CSIO_H__
#define __CT_DD_CSIO_H__

#include <klib.h>

#define CT_TYPE_DD_CSIO									(ct_dd_csio_get_type())
#define CT_DD_CSIO(obj)									(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdCsio))
#define CT_IS_DD_CSIO(obj)								(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_CSIO))

// DMA TRANSFER BUFFER START ADDRESS
#define CtDdCsio_HDMAC_DATA_ADDR_SEND	(0x7A000000)
// DMA RECEIVE BUFFER START ADDRESS
#define CtDdCsio_HDMAC_DATA_ADDR_RECV	(0x7A400000)
#define CtDdCsio_TIMER_CH								(7)

#ifdef CO_DEBUG_ON_PC
#define CtDdCsio_TEST_CMD_LEN		20
#endif /*CO_DEBUG_ON_PC */

typedef struct 			_CtDdCsio CtDdCsio;
typedef struct 			_CtDdCsioPrivate CtDdCsioPrivate;

struct _CtDdCsio
{
	KObject 									parent;

	/*
	 * 全是静态变量，修改的
	 */
	#if 0
	kuchar 									gBuf8[255]	;
	#endif

	#if 1
	kuchar 									gBuf82[32768];
	kuchar 									gRcvBuf82[32768];

	kushort 									gBuf162[16384];
	kushort 									gRcvBuf162[16384];

	#else
	kuchar 									gBuf82[512]	;

	kushort 									gBuf162[512]	;
	kuchar 									gRcvBuf82[512];
	kushort 									gRcvBuf162[512];
	#endif

	kuchar 									gBuf8[8];
	kuchar 									gBuf8Slave[8];
	kushort 									gBuf16[8];

	kuchar 									gRcvBuf8[8];
	kuchar 									gRcvBuf8Slave[8];
	kushort 									gRcvBuf16[8];

	E_DD_CSIO_TYPE 					gType[D_DD_USIO_CH_NUM_MAX];
	kuint32 									gSendSize;
	E_DD_CSIO_DATA_LENGTH 	gDataLength;
	kuchar 									gAsync;
	kuchar 									gBuf2Used;
	kuchar 									gNonChacheAreaUsed;
	kuchar 									gSendFlg;
	kuchar 									gSendingChNumber;

	/*
	 * 函数process提出了的属性
	 */
	kint32										ret;
	T_DD_CSIO_CAL						calTbl;
	T_DD_CSIO_CTRL					csioCtrl;
	T_DD_CSIO_FIFO_CTRL			fifoCtrl;
	kint32										tmout;
};

KConstType ct_dd_csio_get_type(void);
CtDdCsio* ct_dd_csio_new(void);

/*
 * 静态方法转公有
 */
void 	ct_dd_csio_callback( kint32 result );
void 	ct_dd_csio_send_callback( kint32 result );
void 	ct_dd_csio_receive_callback( kint32 result );
void 	ct_dd_csio_callback_full_duplex( kint32 result );
void 	ct_dd_csio_callback_full_duplex_dma( kint32 result );
void 	ct_dd_csio_timer_handler_callback(void);
void 	ct_dd_csio_set_port(CtDdCsio *self);

/*
 * main函数拆分出来的
 */
void 	ct_dd_csio_from_main_with_ctrl(CtDdCsio *self, kuchar ch );
void 	ct_dd_csio_from_main_with_err(CtDdCsio *self, kint32 tmout, kushort baudrate);

void 	ct_dd_csio_pcsim_test(CtDdCsio *self);

//从process函数拆分出来
kint32 	ct_dd_csio_from_process(CtDdCsio *self, kuchar ch, kuchar num);

#endif /* __CT_DD_CSIO_H__ */
