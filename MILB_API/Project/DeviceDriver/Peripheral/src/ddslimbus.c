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

#include <string.h>
#include "_slimbus.h"
#include "ddslimbus.h"
#include "ddim_user_custom.h"
#include "dd_top.h"
#include "dd_hdmac1.h"

#include "ddslimbus.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSlimbus, dd_slimbus);
#define DD_SLIMBUS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdSlimbusPrivate, DD_TYPE_SLIMBUS))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define D_DD_SLIMBUS_CH_MAX_NUM					        (4)
#define D_DD_SLIMBUS_MC_FIFO_MSG_MAX_SIZE		    (64)
#define D_DD_SLIMBUS_P0_FIFO_DATA_MAX_NUM		(64)

#define D_DD_SLIMBUS_DMACA_IS_BASE				            (D_DD_HDMAC1_IS_IDREQ_25)

//#define D_DEBUG_PRINT_INFO_ON
#ifndef D_DEBUG_PRINT_INFO_ON
#define DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(arg)
#else
#define DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(arg)		{DDIM_User_Printf arg;}
#endif	// D_DEBUG_PRINT_INFO_ON

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
typedef volatile struct io_slimbus	T_DD_SLIMBUS_REG;

struct _DdSlimbusPrivate
{
	volatile kuchar		            gDdSlimbusDmaChInfo[D_DD_SLIMBUS_CH_MAX_NUM];
	volatile TDdSlimbusCtrl		gDdSlimbusCtrl[D_DD_SLIMBUS_CH_MAX_NUM];
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static volatile VpSlimbusCallback	S_GDD_SLIMBUS_MANAGER_INT_CB[D_DD_SLIMBUS_CH_MAX_NUM]
                                 	                             = {NULL, NULL, NULL, NULL};
static volatile VpSlimbusCallback	S_GDD_SLIMBUS_DATA_PORT_INT_CB[D_DD_SLIMBUS_CH_MAX_NUM]
                                 	                             = {NULL, NULL, NULL, NULL};
static volatile VpSlimbusCallback	S_GDD_SLIMBUS_DMA_INT_CB[D_DD_SLIMBUS_CH_MAX_NUM] = {NULL, NULL, NULL, NULL};
static volatile kuchar					    S_GDD_SLIMBUS_CH_INFO[D_DD_HDMAC1_CH_NUM_MAX] = {0, 0, 0, 0, 0, 0, 0, 0};
static volatile kuchar					    S_GDD_SLIMBUS_DMA_WAIT[D_DD_SLIMBUS_CH_MAX_NUM] = {0, 0, 0, 0};

/*
 * DECLS
 */
//---------------------------- driver section ----------------------------
static T_DD_SLIMBUS_REG*  ddSlimbusGetRegister(EDdSlimbusCh ch);
static kint32                             ddSlimbusStartDma(DdSlimbus* self, kuchar dmaCh,
		                                                T_DD_HDMAC1_CTRL* const hdmac1Ctrl);
static void                               ddSlimbusDmaInt_cb(kuchar dmaCh, kushort* const status);

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
static kint32                              ddSlimbusChkRegPar(DdSlimbus* self, kushort offset);
#endif

static void dd_slimbus_constructor(DdSlimbus *self)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);

	kint i, j;
	for(i = 0; i < D_DD_SLIMBUS_CH_MAX_NUM; i++)
	{
		 priv->gDdSlimbusDmaChInfo[i] = 0;
	}

	for(j = 0; j < D_DD_SLIMBUS_CH_MAX_NUM; j++)
	{
		priv->gDdSlimbusCtrl[j].ch = 0;
		priv->gDdSlimbusCtrl[j].frEn = 0;
		priv->gDdSlimbusCtrl[j].managerMode = 0;
		priv->gDdSlimbusCtrl[i].sinkThr = 0;
		priv->gDdSlimbusCtrl[j].srcThr = 0;
		priv->gDdSlimbusCtrl[j].dataPortIntCb = NULL;
		priv->gDdSlimbusCtrl[j].managerIntCb = NULL;
	}
}

static void dd_slimbus_destructor(DdSlimbus *self)
{

}

/*
 * IMPL
 */
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// Get SLIMBus Register Address
static T_DD_SLIMBUS_REG* ddSlimbusGetRegister(EDdSlimbusCh ch)
{
	T_DD_SLIMBUS_REG*	slimbusReg;

	switch (ch) {
		case DdSlimbus_CH0:
			// for Audio.
			slimbusReg = &IO_SLIMBUS0;
			break;
		case DdSlimbus_CH1:
			// for Audio.
			slimbusReg = &IO_SLIMBUS1;
			break;
		case DdSlimbus_CH2:
			// for Peripheral.
			slimbusReg = &IO_SLIMBUS2;
			break;
		case DdSlimbus_CH3:
			// for Peripheral.
			slimbusReg = &IO_SLIMBUS3;
			break;
		default:
			slimbusReg = NULL;
	}
	return slimbusReg;
}

// Start DMA
static kint32 ddSlimbusStartDma(DdSlimbus* self, kuchar dmaCh, T_DD_HDMAC1_CTRL* const hdmac1Ctrl)
{
	kint32	ret;

	ret = Dd_HDMAC1_Ctrl_Common(dmaCh, hdmac1Ctrl);
	if(ret == D_DDIM_OK){
		ret = Dd_HDMAC1_Start_Async(dmaCh);
		if(ret != D_DDIM_OK){
			DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("Dd_HDMAC1_Start_Async() error. ret=0x%x\n", ret));
		}
	}
	else{
		DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("Dd_HDMAC1_Ctrl_Common() error. ret=0x%x\n", ret));
	}

	return ret;
}

// DMA interrupt callback
static void ddSlimbusDmaInt_cb(kuchar dmaCh, kushort* const status)
{
	kint32 result;
	kuchar ch;

	ch = S_GDD_SLIMBUS_CH_INFO[dmaCh];
	if(*status == D_DD_HDMAC1_SS_NORMAL_END){
		result = D_DDIM_OK;
	}
	else{
		DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("ddSlimbusDmaInt_cb status=0x%x\n.", *status));
		result = DdSlimbus_DMA_SS_ERROR;
	}

	Dd_HDMAC1_Close(dmaCh);
	S_GDD_SLIMBUS_DMA_WAIT[ch] = 0;

	if(S_GDD_SLIMBUS_DMA_INT_CB[ch]){
		(*S_GDD_SLIMBUS_DMA_INT_CB[ch])(ch, result);
	}
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Check SLIMBus register parameter.
static kint32 ddSlimbusChkRegPar(DdSlimbus* self, kushort offset)
{
	// Word boundary check.
	if((offset % 4) != 0){
		return DdSlimbus_INPUT_PARAM_ERROR;
	}

	// Check on reserved address.
	if((offset >= 0x0014 && offset <= 0x0017) ||
	   (offset >= 0x0030 && offset <= 0x0037) ||
	   (offset >= 0x0084 && offset <= 0x00BF) ||
	   (offset >= 0x00C4 && offset <= 0x00FF) ||
	   (offset >= 0x0108 && offset <= 0x0FFF) ||
	   (offset >= 0x1040)){
		return DdSlimbus_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}
#endif

/*
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
// Open SLIMBus Channel
kint32 dd_slimbus_open(DdSlimbus* self, EDdSlimbusCh ch, kint32 tmout)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("SLIMBus input param error. [tmout] = %x\n", tmout));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if(tmout == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_SLIMBUS(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_SLIMBUS(ch), (DDIM_USER_TMO)tmout);
	}

	if(ercd != D_DDIM_USER_E_OK) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdSlimbus_SEM_TIMEOUT;
		}
		else {
			return DdSlimbus_SEM_NG;
		}
	}
	return D_DDIM_OK;
}

// Close SLIMBus Channel
kint32 dd_slimbus_close(DdSlimbus* self, EDdSlimbusCh ch)
{
	DDIM_USER_ER	ercd;

	// sig_sem()
	ercd = DDIM_User_Sig_Sem(SID_DD_SLIMBUS(ch));

	if(D_DDIM_USER_E_OK != ercd) {
		return DdSlimbus_SEM_NG;
	}
	return D_DDIM_OK;
}

// Set SLIMBus Control
kint32 dd_slimbus_ctrl(DdSlimbus* self, TDdSlimbusCtrl const* const slimbusCtrl)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);
	T_DD_SLIMBUS_REG*	slimbusReg;

#ifdef CO_PARAM_CHECK
	if(slimbusCtrl == NULL){
		Ddim_Assertion(("SLIMBus input param error. [slimbusCtrl] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(slimbusCtrl->managerIntCb == NULL){
		Ddim_Assertion(("SLIMBus input param error. [manager_int_cb] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(slimbusCtrl->dataPortIntCb == NULL){
		Ddim_Assertion(("SLIMBus input param error. [data_port_int_cb] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	slimbusReg = ddSlimbusGetRegister(slimbusCtrl->ch);

	switch(slimbusCtrl->ch){
		case DdSlimbus_CH0:
		case DdSlimbus_CH1:
			if(slimbusCtrl->ch == DdSlimbus_CH0){
				Dd_Top_Set_CLKSTOP2_SLIMB00CK(2);
			}
			else{
				Dd_Top_Set_CLKSTOP2_SLIMB01CK(2);
			}

			/*Configuration – Generic device
			 *  [26:24]TP_SUPP
			 *  [23:0]PR_SUPP : 24.576MHz*/
			slimbusReg->CONFIG_PR_TP.word = 0x07FF00FE;
			/*// Configuration – Framer device
			 * [17:16]QUALITY=3
			 * [15:0]RF_SUPP=1(24.576MHz)*/
			slimbusReg->CONFIG_FR.word = 0x00030001;
			break;
		case DdSlimbus_CH2:
		case DdSlimbus_CH3:
			if(slimbusCtrl->ch == DdSlimbus_CH2){
				Dd_Top_Set_CLKSTOP2_SLIMB10CK(2);
			}
			else{
				Dd_Top_Set_CLKSTOP2_SLIMB11CK(2);
			}

			/*Configuration – Generic device
			 * [26:24]TP_SUPP
			 * [23:0]PR_SUPP : 28.8MHz*/
			slimbusReg->CONFIG_PR_TP.word = 0x073F007E;
			/*Configuration – Framer device
			 * [17:16]QUALITY=3
			 * [15:0]RF_SUPP=0(28.8MHz Not Indicated)*/
			slimbusReg->CONFIG_FR.word = 0x00030000;
			break;
		default:
			return DdSlimbus_INPUT_PARAM_ERROR;
	}

	priv->gDdSlimbusCtrl[slimbusCtrl->ch] = *slimbusCtrl;

	/*Configuration – Mode
	 * [11:8]RETRY_LMT=8
	 * [4]DEV_EN=1
	 * [0]ENABLE=1*/
	slimbusReg->CONFIG_MODE.word = 0x00000811;

	slimbusReg->CONFIG_MODE.bit.MANAGER_MODE = slimbusCtrl->managerMode;

	slimbusReg->CONFIG_MODE.bit.FR_EN = slimbusCtrl->frEn;

	if(slimbusReg->CONFIG_MODE.bit.MANAGER_MODE == DdSlimbus_MANAGER_MODE_ENABLE){
		slimbusReg->CONFIG_EA.bit.INSTANCE_VAL = 0;
	}
	else{
		slimbusReg->CONFIG_EA.bit.INSTANCE_VAL = 1;
	}

	// Reset value
	slimbusReg->CONFIG_DPORT.word = 0x00000600;

	// source threshold
	slimbusReg->CONFIG_THR.bit.SRC_THR  = slimbusCtrl->srcThr;
	// sink threshold
	slimbusReg->CONFIG_THR.bit.SINK_THR = slimbusCtrl->sinkThr;

	// Interrupt Clear
	slimbusReg->INT.word = 0x0000007E;

	/*Interrupt Enable
	 * [4]SYNC_LOST_EN=1
	 * [3]TX_ERR_EN=1
	 * [2]TX_INT_EN=1
	 * [1]RX_INT_EN=1
	 * [0]IN_EN=1*/
	slimbusReg->INT_EN.word = 0x0000001F;

	// Interrupt Clear
	slimbusReg->P0_INT.word = 0x0000003F;

	// Only DMA_INT_EN is 0.
	slimbusReg->P0_INT_EN.word = 0x000000F7;

	S_GDD_SLIMBUS_MANAGER_INT_CB[slimbusCtrl->ch] = slimbusCtrl->managerIntCb;
	S_GDD_SLIMBUS_DATA_PORT_INT_CB[slimbusCtrl->ch] = slimbusCtrl->dataPortIntCb;

	return D_DDIM_OK;
}

// Get SLIMBus Control
kint32 dd_slimbus_get_ctrl(DdSlimbus* self, EDdSlimbusCh ch, TDdSlimbusCtrl* const slimbusCtrl)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);
	if(slimbusCtrl == NULL){
		return DdSlimbus_INPUT_PARAM_ERROR;
	}

	*slimbusCtrl = priv->gDdSlimbusCtrl[ch];

	return D_DDIM_OK;
}

// Start SLIMBus Macro
kint32 dd_slimbus_start(DdSlimbus* self, EDdSlimbusCh ch)
{
	T_DD_SLIMBUS_REG* slimbusReg;

	slimbusReg = ddSlimbusGetRegister(ch);

	if(slimbusReg->COMMAND.bit.CFG_STROBE == 0){
		slimbusReg->COMMAND.bit.CFG_STROBE = 1;
	}
	else{
		// previous reconfiguration
		return DdSlimbus_STATUS_ABNORMAL;
	}

	return D_DDIM_OK;
}

// Stop SLIMBus Macro
kint32 dd_slimbus_stop(DdSlimbus* self, EDdSlimbusCh ch)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);
	T_DD_SLIMBUS_REG* slimbusReg;

	slimbusReg = ddSlimbusGetRegister(ch);

	if(slimbusReg->COMMAND.bit.CFG_STROBE == 1){
		slimbusReg->COMMAND.bit.CFG_STROBE_CLR = 1;
	}

    // Disable all interrupts
	slimbusReg->P0_INT_EN.word = 0x00000040;
	slimbusReg->INT_EN.bit.IN_EN = 0;

    // Disable component
	slimbusReg->CONFIG_MODE.bit.ENABLE = 0;
	slimbusReg->COMMAND.bit.CFG_STROBE = 1;

	if(S_GDD_SLIMBUS_DMA_WAIT[ch] == 1){
		Dd_HDMAC1_Close(priv->gDdSlimbusDmaChInfo[ch]);
		S_GDD_SLIMBUS_DMA_WAIT[ch] = 0;
	}

	return D_DDIM_OK;
}

// Interrupt Handler of SLIMBus.
void dd_slimbus_int_handler(EDdSlimbusCh ch)
{
	T_DD_SLIMBUS_REG* slimbusReg;
	kuint32	intReg;
	kuint32	p0IntReg;
	VpSlimbusCallback	intCb;
	VpSlimbusCallback	portIntCb;

	intCb = S_GDD_SLIMBUS_MANAGER_INT_CB[ch];
	portIntCb = S_GDD_SLIMBUS_DATA_PORT_INT_CB[ch];

	slimbusReg = ddSlimbusGetRegister(ch);

	intReg = slimbusReg->INT.word;
	if(intCb != NULL){
		(*intCb)((kuchar)ch, intReg);
	}

	// Interrupt Clear
	slimbusReg->INT.word = intReg;

	if(intReg & 0x00000080){
		// PORT_INT Hight ?
		p0IntReg = slimbusReg->P0_INT.word;
		if(portIntCb != NULL){
			(*portIntCb)((kuchar)ch, p0IntReg);
		}
		// Interrupt Clear
		slimbusReg->P0_INT.word = p0IntReg;
	}
}

// Write message to TX_FIFO.
kint32 dd_slimbus_write_msg(DdSlimbus* self, EDdSlimbusCh ch, kuint32* msg, kuint32 size)
{
	T_DD_SLIMBUS_REG* slimbusReg;
	kuint32 i, sendRegNum;

#ifdef CO_PARAM_CHECK
	if(msg == NULL){
		Ddim_Assertion(("SLIMBus input param error. [msg] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(size > D_DD_SLIMBUS_MC_FIFO_MSG_MAX_SIZE){
		Ddim_Assertion(("SLIMBus input param error. [size] = %d\n", size));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	slimbusReg = ddSlimbusGetRegister(ch);

	if(slimbusReg->STATE.bit.TX_PUSH || slimbusReg->STATE.bit.TX_FULL){
		return DdSlimbus_PROCESSING;
	}

	sendRegNum = (size >> 2);
	if(size & 0x3){
		sendRegNum++;
	}

	for (i = 0; i < sendRegNum; i++, msg++) {
		slimbusReg->MC_FIFO[i] = *msg;
	}

	// Send MC_FIFO
	slimbusReg->COMMAND.bit.TX_PUSH = 1;

	return D_DDIM_OK;
}

// Read message from RX_FIFO.
kint32 dd_slimbus_read_msg(DdSlimbus* self, EDdSlimbusCh ch, kuint32* msg, kuint32* size)
{
	T_DD_SLIMBUS_REG* slimbusReg;
	kuint32 i, readRegNum;

#ifdef CO_PARAM_CHECK
	if(msg == NULL){
		Ddim_Assertion(("SLIMBus input param error. [msg] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(size == NULL){
		Ddim_Assertion(("SLIMBus input param error. [size] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	slimbusReg = ddSlimbusGetRegister(ch);

	// RX_OVERFLOW
	if(slimbusReg->MC_FIFO[15] & 0x00000100){
		return DdSlimbus_OVERFLOW_ERR;
	}

	// The size is acquired from RX_FIFO_FLAG.
	*size = slimbusReg->MC_FIFO[15] & 0x0000003F;

	readRegNum = (*size >> 2);
	if(*size & 0x3){
		readRegNum++;
	}

	for (i = 0; i < readRegNum; i++, msg++) {
		*msg = slimbusReg->MC_FIFO[i];
	}

	// Read MC_FIFO
	slimbusReg->COMMAND.bit.RX_PULL = 1;

	return D_DDIM_OK;
}

// Write data to P0_FIFO.
kint32 dd_slimbus_write_data(DdSlimbus* self, WriteDataParam writeDataParam)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);
	kint32	ret;
	T_DD_HDMAC1_CTRL	hdmac1Ctrl;
	T_DD_SLIMBUS_REG* 	slimbusReg;

	EDdSlimbusCh ch = writeDataParam.ch;
	kuchar dmaCh = writeDataParam.dmaCh;
	kuint32* data = writeDataParam.data;
	kuint32 count = writeDataParam.count;
	VpSlimbusCallback pCallback = writeDataParam.pCallback;

#ifdef CO_PARAM_CHECK
	if(dmaCh >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SLIMBus input param error. [dmaCh] = %d\n", dmaCh));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(data == NULL){
		Ddim_Assertion(("SLIMBus input param error. [data] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(count == 0 || count > D_DD_SLIMBUS_P0_FIFO_DATA_MAX_NUM){
		Ddim_Assertion(("SLIMBus input param error. [count] = %d\n", count));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(pCallback == NULL) {
		Ddim_Assertion(("SLIMBus input param error. [pCallback] = %p\n", pCallback));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return DdSlimbus_STATUS_ABNORMAL;
	}

	memset(&hdmac1Ctrl, 0, sizeof(hdmac1Ctrl));
	hdmac1Ctrl.config_a.bit.is = D_DD_SLIMBUS_DMACA_IS_BASE + ch;
	hdmac1Ctrl.config_a.bit.tc = count - 1;
	hdmac1Ctrl.config_a.bit.bt = D_DD_HDMAC1_BT_NORMAL;
	hdmac1Ctrl.config_b.bit.tw	= D_DD_HDMAC1_TW_WORD;
	hdmac1Ctrl.config_b.bit.ms = D_DD_HDMAC1_MS_DEMAND;
	hdmac1Ctrl.config_b.bit.fd	= D_DD_HDMAC1_FD_FIX;

	hdmac1Ctrl.src_addr = (ULONG)data;
	slimbusReg = ddSlimbusGetRegister(ch);
	hdmac1Ctrl.dst_addr = (ULONG)(slimbusReg->P0_FIFO);
	if(pCallback){
		hdmac1Ctrl.int_handler = (VP_CALLBACK)ddSlimbusDmaInt_cb;
		S_GDD_SLIMBUS_DMA_INT_CB[ch] = pCallback;
		S_GDD_SLIMBUS_DMA_WAIT[ch] = 1;
	}
	else{
		hdmac1Ctrl.int_handler = NULL;
		S_GDD_SLIMBUS_DMA_INT_CB[ch] = NULL;
	}
	S_GDD_SLIMBUS_CH_INFO[dmaCh] = (kuchar)ch;
	priv->gDdSlimbusDmaChInfo[ch] = dmaCh;

	ret = ddSlimbusStartDma(self, dmaCh, &hdmac1Ctrl);
	if(ret != D_DDIM_OK){
		Dd_HDMAC1_Close(dmaCh);
		S_GDD_SLIMBUS_DMA_WAIT[ch] = 0;
		return ret;
	}

	return D_DDIM_OK;
}

// Read data from P0_FIFO.
kint32 dd_slimbus_read_data(DdSlimbus* self, ReadDataParam readDataParam)
{
	DdSlimbusPrivate *priv = DD_SLIMBUS_GET_PRIVATE(self);
	kint32	ret;
	T_DD_HDMAC1_CTRL	hdmac1Ctrl;
	T_DD_SLIMBUS_REG* 	slimbusReg;

	EDdSlimbusCh ch = readDataParam.ch;
	kuchar  dmaCh = readDataParam.dmaCh;
	kuint32*  data = readDataParam.data;
	kuint32  count = readDataParam.count;
	VpSlimbusCallback pCallback = readDataParam.pCallback;

#ifdef CO_PARAM_CHECK
	if(dmaCh >= D_DD_HDMAC1_CH_NUM_MAX){
		Ddim_Assertion(("SLIMBus input param error. [dmaCh] = %d\n", dmaCh));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(data == NULL){
		Ddim_Assertion(("SLIMBus input param error. [data] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(count == 0 || count > D_DD_SLIMBUS_P0_FIFO_DATA_MAX_NUM){
		Ddim_Assertion(("SLIMBus input param error. [count] = %d\n", count));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
	if(pCallback == NULL) {
		Ddim_Assertion(("SLIMBus input param error. [pCallback] = %p\n", pCallback));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	// Open DMA.
	ret = Dd_HDMAC1_Open(dmaCh, D_DDIM_WAIT_END_TIME);
	if(ret != D_DDIM_OK){
		DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("Dd_HDMAC1_Open() error. ret=0x%x\n", ret));
		return DdSlimbus_STATUS_ABNORMAL;
	}

	memset(&hdmac1Ctrl, 0, sizeof(hdmac1Ctrl));
	hdmac1Ctrl.config_a.bit.is	= D_DD_SLIMBUS_DMACA_IS_BASE + ch;
	hdmac1Ctrl.config_a.bit.tc	= count - 1;
	hdmac1Ctrl.config_a.bit.bt	= D_DD_HDMAC1_BT_NORMAL;
	hdmac1Ctrl.config_b.bit.tw	= D_DD_HDMAC1_TW_WORD;
	hdmac1Ctrl.config_b.bit.ms	= D_DD_HDMAC1_MS_DEMAND;
	hdmac1Ctrl.config_b.bit.fs	= D_DD_HDMAC1_FS_FIX;
	// HPROT of destination protection (8:cacheable)
	hdmac1Ctrl.config_b.bit.dp	= 8;

	slimbusReg = ddSlimbusGetRegister(ch);
	hdmac1Ctrl.src_addr = (ULONG)(slimbusReg->P0_FIFO);
	hdmac1Ctrl.dst_addr = (ULONG)data;
	if(pCallback){
		hdmac1Ctrl.int_handler = (VP_CALLBACK)ddSlimbusDmaInt_cb;
		S_GDD_SLIMBUS_DMA_INT_CB[ch] = pCallback;
		S_GDD_SLIMBUS_DMA_WAIT[ch] = 1;
	}
	else{
		hdmac1Ctrl.int_handler = NULL;
		S_GDD_SLIMBUS_DMA_INT_CB[ch] = NULL;
	}
	S_GDD_SLIMBUS_CH_INFO[dmaCh] = (kuchar)ch;
	priv->gDdSlimbusDmaChInfo[ch] = dmaCh;

	ret = ddSlimbusStartDma(self, dmaCh, &hdmac1Ctrl);
	if(ret != D_DDIM_OK){
		Dd_HDMAC1_Close(dmaCh);
		S_GDD_SLIMBUS_DMA_WAIT[ch] = 0;
		return ret;
	}

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Get SLIMBus Register value.
kint32 dd_slimbus_get_reg(DdSlimbus* self, EDdSlimbusCh ch, kushort offset, kuint32* data)
{
	kint32	ret = D_DDIM_OK;
	kuint32*	 addr;
	T_DD_SLIMBUS_REG*	slimbusReg;

#ifdef CO_PARAM_CHECK
	if(data == NULL){
		Ddim_Assertion(("SLIMBus input param error. [data] = NULL\n"));
		return DdSlimbus_INPUT_PARAM_ERROR;
	}
#endif

	ret = ddSlimbusChkRegPar(self, offset);
	if(ret != D_DDIM_OK){
		return ret;
	}

	slimbusReg = ddSlimbusGetRegister(ch);
	addr = (kuint32*)((kuchar*)slimbusReg + offset);

	DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("[DD_SLIMBUS] addr  = 0x%08X\n", addr));
	DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("[DD_SLIMBUS] *addr = 0x%08X\n", *addr));

	*data = *addr;

	return ret;
}

// Set SLIMBus Register value.
kint32 dd_slimbus_set_reg(DdSlimbus* self, EDdSlimbusCh ch, kushort offset, kuint32 data)
{
	kint32	ret = D_DDIM_OK;
	kuint32*	 addr;
	T_DD_SLIMBUS_REG*	slimbusReg;

	ret = ddSlimbusChkRegPar(self, offset);
	if(ret != D_DDIM_OK){
		return ret;
	}

	slimbusReg = ddSlimbusGetRegister(ch);
	addr = (kuint32*)((kuchar*)slimbusReg + offset);

	DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("[DD_SLIMBUS] addr  = 0x%08X\n", addr));
	DdSlimbus_DD_SLIMBUS_DEBUG_PRINT(("[DD_SLIMBUS] *addr = 0x%08X\n", *addr));

	*addr = data;

	return ret;
}

#endif

DdSlimbus* dd_slimbus_get(void)
{
	DdSlimbus *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_SLIMBUS, sizeof(DdSlimbusPrivate));
	}

	return self;
}
