/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-10
* @author    : 肖泽友
* @brief        :uart driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、branch
*
*@version   :1.0.0
*
*/

#include "dd_arm.h"
#include "uart_csio.h"

#include "dduartbranch.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUartBranch, dd_uart_branch);
#define DD_UART_BRANCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		DdUartBranchPrivate, DD_TYPE_UART_BRANCH))

struct _DdUartBranchPrivate
{
    kint a;
};

static DdUartSpinLock S_GDD_UART_BRANCH_SPIN_LOCK[DdUart_CH_NUM_MAX]
                                                  __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_uart_branch_constructor(DdUartBranch *self)
{
	DdUartBranchPrivate *priv = DD_UART_BRANCH_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_uart_branch_destructor(DdUartBranch *self)
{

}

/*
 * PUBLIC
 */
/*
 * @brief  UART is exclusively controlled.
 * @param  kuchar  ch
 * @return	kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 * / DdUart_SEM_TIMEOUT / DdUart_SEM_NG
 */
kint32 dd_uart_branch_open(DdUartBranch *self, kuchar ch, kint32 timeOut)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if (timeOut < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("UART: input param error. timeOut = %x\n", timeOut));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(timeOut == D_DDIM_USER_SEM_WAIT_POL) {
		ercd = DDIM_User_Pol_Sem(SID_DD_USIO(ch));
	}
	else{
		ercd = DDIM_User_Twai_Sem(SID_DD_USIO(ch), (DDIM_USER_TMO)timeOut);
	}

	if(ercd != D_DDIM_USER_E_OK) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdUart_SEM_TIMEOUT;
		}
		return DdUart_SEM_NG;
	}

	dd_uart_set_usio_state(dd_uart_get(), ch, DdUart_EXC_UART);

	return D_DDIM_OK;
}

kint32 dd_uart_branch_set_baudrate(DdUartBranch *self, kuchar ch, kushort baudRate)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	IO_USIO.UART[ch].BGR.hword = baudRate;
	return D_DDIM_OK;
}

kint32 dd_uart_branch_get_baudrate(DdUartBranch *self, kuchar ch, kushort* baudRate)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(baudRate == NULL){
		Ddim_Assertion(("UART input param error. [baudRate] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	*baudRate = IO_USIO.UART[ch].BGR.hword;
	return D_DDIM_OK;
}

kint32 dd_uart_branch_save_send_fifo_pointer(DdUartBranch *self, kuchar ch, kuchar lostDetect)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if((lostDetect != 0) && (lostDetect != 1)){
		Ddim_Assertion(("UART input param error. [lostDetect] = %d\n", lostDetect));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	// Check exist data in send fifo
	if(IO_USIO.UART[ch].FBYTE.byte[IO_USIO.UART[ch].FCR.bit.FSEL] != 0){
		return DdUart_DATA_EXIST_ERROR;
	}

	// Save Read Pointer
	IO_USIO.UART[ch].FCR.bit.FSET = 1;

	// Enable/Disable data lost detection (FLST)
	IO_USIO.UART[ch].FCR.bit.FLSTE = lostDetect;

	return D_DDIM_OK;
}

kint32 dd_uart_branch_get_reload_status(DdUartBranch *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	return IO_USIO.UART[ch].FCR.bit.FLD;
}

kint32 dd_uart_branch_reset_fifo(DdUartBranch *self, kuchar ch, kuchar fifoNum)
{
	kuchar txe;
	kuchar rxe;
	kuchar ftie;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if((fifoNum != 1) && (fifoNum != 2) && (fifoNum != 3)){
		Ddim_Assertion(("UART input param error. [fifoNum] = %d\n", fifoNum));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	// Keep to temporary
	txe = IO_USIO.UART[ch].SCR.bit.TXE;
	rxe = IO_USIO.UART[ch].SCR.bit.RXE;
	ftie = IO_USIO.UART[ch].FCR.bit.FTIE;

	// Disable send/receive
	IO_USIO.UART[ch].SCR.bit.TXE = 0;
	IO_USIO.UART[ch].SCR.bit.RXE = 0;
	IO_USIO.UART[ch].FCR.bit.FTIE = 0;

	// Reset FIFO
	// D_DD_UART_SELECT_FIFO_1		(1)
	// D_DD_UART_SELECT_FIFO_2		(2)
	// D_DD_UART_SELECT_FIFO_BOTH	(3)
	IO_USIO.UART[ch].FCR.hword |= fifoNum << 2;

	DdUart_DSB();

	// Set keep value
	IO_USIO.UART[ch].SCR.bit.TXE = txe;
	IO_USIO.UART[ch].SCR.bit.RXE = rxe;
	IO_USIO.UART[ch].FCR.bit.FTIE = ftie;

	DdUart_DSB();

	return D_DDIM_OK;
}

kint32 dd_uart_branch_reset_baudrate(DdUartBranch *self, kuchar ch)
{
	kint32 baudRate;
	kint32 count;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	baudRate = dd_uart_get_uart_mng(dd_uart_get(), ch).baudRate;
	count = (Dd_Top_Get_HCLK() /  baudRate) - 1;
	IO_USIO.UART[ch].BGR.hword = (unsigned short)count;
	return D_DDIM_OK;
}

kint32 dd_uart_branch_reload_send_fifo_pointer(DdUartBranch *self, kuchar ch)
{
	kuchar fe1;
	kuchar fe2;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_USIO.UART[ch].FCR.bit.FLST == 1){
		// Reload data lost
		return DdUart_OVERWRITE_ERROR;
	}

	// Keep to temporary
	fe1 = IO_USIO.UART[ch].FCR.bit.FE1;
	fe2 = IO_USIO.UART[ch].FCR.bit.FE2;

	// Disable send/receive
	IO_USIO.UART[ch].FCR.bit.FE1 = 0;
	IO_USIO.UART[ch].FCR.bit.FE2 = 0;
	IO_USIO.UART[ch].SCR.bit.TIE	= 0;
	IO_USIO.UART[ch].SCR.bit.TBIE = 0;
	IO_USIO.UART[ch].FCR.bit.FTIE = 0;

	// Reload Send FIFO
	IO_USIO.UART[ch].FCR.bit.FLD = 1;

	// Enable send permission
	IO_USIO.UART[ch].SMR.bit.SOE	= 1;
	IO_USIO.UART[ch].SCR.bit.TXE = 1;

	// Set keep value
	IO_USIO.UART[ch].FCR.bit.FE1 = fe1;
	IO_USIO.UART[ch].FCR.bit.FE2 = fe2;

	// Subtract the number of resend   ???
//	if(IO_USIO.UART[ch].FBYTE.byte[IO_USIO.UART[ch].FCR.bit.FSEL] >= gDD_UART_Info[ch].send_pos){
//		gDD_UART_Info[ch].send_pos -= IO_USIO.UART[ch].FBYTE.byte[IO_USIO.UART[ch].FCR.bit.FSEL];
//	}
	// Interrupt enable?
	if(dd_uart_get_uart_mng(dd_uart_get(), ch).psendCallback){
		IO_USIO.UART[ch].FCR.bit.FDRQ = 0;
		IO_USIO.UART[ch].FCR.bit.FTIE = 1;
	}

	DdUart_DSB();

	return D_DDIM_OK;
}

/*
 * @brief  The UART sending and receiving processing begins.
 * @param  kuchar  ch
 * @return kint32  D_DDIM_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_branch_start(DdUartBranch *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	IO_USIO.UART[ch].SCR.byte |= 0x03;

	DdUart_DSB();

	dd_uart_set_info_force_stop_flg(dd_uart_get(), ch, 0);

	return D_DDIM_OK;
}

/*
 * @brief  The data that wants to transmit to the transmission buffer is stored.
 * 		   When the transmission buffer overflows, the overflow error is sent back.
 * @param  kuchar  ch
 * @param  kchar   str
 * @return kint32  D_DDIM_OK/DdUart_D_DD_UART_OVERFLOW_ERROR
 */
kint32 dd_uart_branch_set_str(DdUartBranch *self, kuchar ch, kchar str)
{
	kint32 result;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	// SpinLock.
	Dd_ARM_Critical_Section_Start(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

	if((dd_uart_get_uart_buff_info(dd_uart_get(), ch).sReadPos
			<= dd_uart_get_uart_buff_info(dd_uart_get(), ch).sWritePos)
			&& (dd_uart_get_uart_buff_info(dd_uart_get(), ch).sFlag == 1)){
		result = DdUart_OVERFLOW_ERROR;
	}
	else{

		dd_uart_set_mng_send_buff_addr(dd_uart_get(), ch, str);
		dd_uart_set_buff_info_write_pos(dd_uart_get(), ch);
		dd_uart_set_buff_info_size_add(dd_uart_get(), ch);

		if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).sWritePos
				>= dd_uart_get_uart_mng(dd_uart_get(), ch).sendBuffSize){
			dd_uart_set_buff_info_s_write_pos(dd_uart_get(), ch);
			// The flag is hoisted
//         gDD_Uart_Buff_Info[ch].sFlag++;
			// The flag is hoisted
			dd_uart_set_buff_info_flag(dd_uart_get(), ch, 1);
			dd_uart_set_buff_info_overlap(dd_uart_get(), ch);
		}

		result = D_DDIM_OK;
	}

	// SpinUnLock.
	Dd_ARM_Critical_Section_End(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

	return result;
}

/*
 * @brief  All the data that exists in the transmission buffer is transmitted.
*		   The error is sent back when there is no data in the transmission buffer.
 * @param  kuchar  ch
 * @return kint32  D_DDIM_OK/DdUart_D_DD_UART_NO_SEND_DATA
 */
kint32 dd_uart_branch_put_str(DdUartBranch *self, kuchar ch)
{
	kchar	buffData;
	kint32	sendSize;
	kint32	result;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	if(IO_USIO.UART[ch].SCR.bit.TXE == 0){
		return DdUart_STOPPED;
	}

	if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).sSize == 0){
		result = DdUart_NO_SEND_DATA;
	}
	else{
		// All the data that exists in the transmission buffer is transmitted
		for(sendSize = dd_uart_get_uart_buff_info(dd_uart_get(), ch).sSize; sendSize > 0; sendSize--){
			buffData = *(dd_uart_get_uart_mng(dd_uart_get(), ch).sendBuffAddr
					+ dd_uart_get_uart_buff_info(dd_uart_get(), ch).sReadPos);
			result = dd_uart_put_char(dd_uart_get(), ch, buffData);
			if(result != D_DDIM_OK){
				return result;
			}

			// SpinLock.
			Dd_ARM_Critical_Section_Start(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

			dd_uart_set_buff_info_read_pos(dd_uart_get(), ch);
			dd_uart_set_buff_info_size_subtract(dd_uart_get(), ch);

			if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).sReadPos
					>= dd_uart_get_uart_mng(dd_uart_get(), ch).sendBuffSize){
				dd_uart_set_buff_info_s_read_pos(dd_uart_get(), ch);
				// The flag is dropped
//				gDD_Uart_Buff_Info[ch].sFlag--;
				// The flag is dropped
				dd_uart_set_buff_info_flag(dd_uart_get(), ch, 0);
			}

			// SpinUnLock.
			Dd_ARM_Critical_Section_End(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);
		}
		result = D_DDIM_OK;
	}
	return result;
}

/*
 * @brief  Receive data is acquired from the UART receive data storage area.
 * @param  kuchar  ch
 * @param  kchar*  getChar
 * @return kint32  D_DDIM_OK/DdUart_D_DD_UART_NO_RECEIVE/DdUart_D_DD_UART_OVERFLOW_ERROR
 */
kint32 dd_uart_branch_get_char(DdUartBranch *self, kuchar ch, kchar* const getChar)
{
	kuchar buffData;
	kint32 result;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(getChar == NULL){
		Ddim_Assertion(("UART input param error. [getChar] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).rSize == 0){
		result = DdUart_NO_RECEIVE;
	}
	else if((dd_uart_get_uart_buff_info(dd_uart_get(), ch).rReadPos
			<= dd_uart_get_uart_buff_info(dd_uart_get(), ch).rWritePos)
			&& (dd_uart_get_uart_buff_info(dd_uart_get(), ch).rFlag == 1)){
		result = DdUart_OVERFLOW_ERROR;
	}
	else{
		if(dd_uart_get_uart_flag(dd_uart_get(), ch) == 1){
			// SpinLock.
			Dd_ARM_Critical_Section_Start(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

			buffData = *(dd_uart_get_uart_mng(dd_uart_get(), ch).receiveBuffAddr
					+ dd_uart_get_uart_buff_info(dd_uart_get(), ch).rReadPos);

			*getChar = buffData;
			dd_uart_set_buff_info_r_read_pos_add(dd_uart_get(), ch);
			dd_uart_set_buff_info_r_size_subtract(dd_uart_get(), ch);

			if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).rReadPos
					>= dd_uart_get_uart_mng(dd_uart_get(), ch).receiveBuffSize){
				dd_uart_set_buff_info_r_read_pos(dd_uart_get(), ch);
				// The flag is dropped
				dd_uart_set_buff_info_flag_subtract(dd_uart_get(), ch);
			}

			// SpinUnLock.
			Dd_ARM_Critical_Section_End(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

			result = D_DDIM_OK;
		}
		else{
			result = DdUart_NO_RECEIVE;
		}
	}
	return result;
}

/*
 * @brief  Clear the uart buffer information for overwrite.
 * @param  kuchar  ch
 * @return kint32  write pointer
 * @return kint32  D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_branch_clear_overwrite(DdUartBranch *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	dd_uart_set_buff_info_flag(dd_uart_get(), ch, 0);
	dd_uart_set_buff_info_size(dd_uart_get(), ch, 0);

	return D_DDIM_OK;
}

/*
 * @brief  Get the write pointer of send buffer.
 * @param  kuchar  ch
 * @return kint32  write pointer
 */
kulong dd_uart_branch_get_send_write_pointer_addr(DdUartBranch *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return 0;
	}
#endif

	return (kulong)dd_uart_get_uart_buff_info(dd_uart_get(), ch).sWritePos;
}

kulong dd_uart_branch_get_send_overlap_count(DdUartBranch *self, kuchar ch)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return 0;
	}
#endif

	return dd_uart_get_uart_buff_info(dd_uart_get(), ch).sOverlapCnt;
}

kint32 dd_uart_branch_set_slave_addr(DdUartBranch *self, kuchar ch, kuchar slaveAddr)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif
	dd_uart_set_info_slave_addr(dd_uart_get(), ch, slaveAddr);
	return D_DDIM_OK;
}

/*
 * @brief  It is a function started when the UART reception is completed.
 * @param  kuchar  ch
 * @return void
 */
void dd_uart_branch_int_handler_rx(DdUartBranch *self, kuchar ch)
{
	kchar	rData;
	kushort	rAddr;
	kint32	rRslt;
	kint32	result;

	if(dd_uart_get_uart_info(dd_uart_get(), ch).dmaWait == 1){
		IO_USIO.UART[ch].FCR.bit.FRIIE = 0;
		IO_USIO.UART[ch].SCR.bit.RIE = 0;
		DdUart_DSB();
		return;
	}

	// It annuls it because dd_uart_ctrl() is not called, except when gDD_Uart_Flag is 1.
	if(dd_uart_get_uart_flag(dd_uart_get(), ch) == 1){
		// The reception result is acquired.
		rRslt = (IO_USIO.UART[ch].SSR.byte & 0x38);
		switch(rRslt){
			case 0:
				// Reception OK
				if(IO_USIO.UART[ch].SMR.bit.MD == 1){
					// Multi Processor mode
					rAddr = IO_USIO.UART[ch].DR.hword;
					if(rAddr & DdUart_DR_D8_BIT){
						// address
						if((rAddr & 0x00FF) == (kushort)dd_uart_get_uart_info(dd_uart_get(), ch).multiSlaveAddr){
							result = DdUart_INT_STATUS_RECV_SLAVE_ADDR;
							dd_uart_set_info_multi_active_flg(dd_uart_get(), ch, DdUart_MODE_MULTI_SLAVE);
							if (dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback != NULL){
								(*dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback)(&result);
							}
							// Communication start
							return;
						}
						else{
							if(dd_uart_get_uart_info(dd_uart_get(), ch).multiActiveFlg
									== DdUart_MODE_MULTI_SLAVE){
								// Slave address unmatch
								dd_uart_set_info_multi_active_flg(dd_uart_get(), ch,
										DdUart_MODE_MULTI_DIS);
//								Ddim_Print(("Slave address unmatch addr=0x%x\n", rAddr));
							}
							return;
						}
					}
					else{
						if(dd_uart_get_uart_info(dd_uart_get(), ch).multiActiveFlg
								== DdUart_MODE_MULTI_DIS){
//							Ddim_Print(("Data to other data=%s\n", rAddr));
							// Data to other
							return;
						}
					}
				}

				result = DdUart_INT_STATUS_RECV_CHAR;
				// Receive data acquisition
				rData = (kchar)IO_USIO.UART[ch].DR.byte[0];

				if(dd_uart_get_uart_mng(dd_uart_get(), ch).autoEcho
						== DdUart_AUTO_ECHO_ON){
					if (rData == '\r' || rData == '\n') {
						dd_uart_branch_set_str(self, ch, '\r');
						dd_uart_branch_set_str(self, ch, '\n');
						result = DdUart_INT_STATUS_RECV_ENTER;
					}
					else{
						// echo
						dd_uart_branch_set_str(self, ch, rData);
					}
				}
				else{
					result = (kint32)rData;
				}
				if(dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback != NULL){
					// Reception result is passed to the user here
					(*dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback)(&result);
				}

				if(dd_uart_get_uart_mng(dd_uart_get(), ch).saveBuff == DdUart_SAVE2BUFFER_EN){
					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);

					dd_uart_set_mng_receive_buff_addr(dd_uart_get(), ch, rData);
					dd_uart_set_buff_info_r_write_pos_add(dd_uart_get(), ch);
					dd_uart_set_buff_info_r_size_add(dd_uart_get(), ch);

					if(dd_uart_get_uart_buff_info(dd_uart_get(), ch).rWritePos
							>= dd_uart_get_uart_mng(dd_uart_get(), ch).receiveBuffSize){
						dd_uart_set_buff_info_r_write_pos(dd_uart_get(), ch);
						// The flag is hoisted
						dd_uart_set_buff_info_flag_add(dd_uart_get(), ch);
					}

					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GDD_UART_BRANCH_SPIN_LOCK[ch].lock);
				}
				break;

			case 0x20:
				// Parity error
				result = DdUart_INT_STATUS_PARITY_ERROR;
				// The error factor register is clear
				IO_USIO.UART[ch].SSR.byte |= DdUart_SSR_REC_BIT;
				DdUart_DSB();
				if (dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback != NULL){
					// Reception result is passed to the user here
					(*dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback)(&result);
				}
				break;

			case 0x08:
				// Over-run error
				result = DdUart_INT_STATUS_OVERRUN_ERROR;
				// The error factor register is clear
				IO_USIO.UART[ch].SSR.byte |= DdUart_SSR_REC_BIT;
				DdUart_DSB();
				if (dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback != NULL){
					// Reception result is passed to the user here
					(*dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback)(&result);
				}
				break;

			case 0x10:
				// Framing error
				result = DdUart_INT_STATUS_FRAMING_ERROR;
				// The error factor register is clear
				IO_USIO.UART[ch].SSR.byte |= DdUart_SSR_REC_BIT;
				DdUart_DSB();
				if (dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback != NULL){
					// Reception result is passed to the user here
					(*dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback)(&result);
				}
				break;

			default:
				// Route that doesn't pass
				break;
		}
	}
}

/*
 * @brief  The value specified by the argument is get from the register of UART.
 * @param  DdUartMng* uartMng
 * @return kint32  D_DDIM_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_branch_get_ctrl(DdUartBranch *self, kuchar ch, DdUartMng* const uartMng)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(uartMng == NULL){
		Ddim_Assertion(("UART input param error. [uartMng] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	uartMng->baudRate = dd_uart_get_uart_mng(dd_uart_get(), ch).baudRate;
	uartMng->psendCallback = dd_uart_get_uart_mng(dd_uart_get(), ch).psendCallback;
	uartMng->preceiveCallback = dd_uart_get_uart_mng(dd_uart_get(), ch).preceiveCallback;
	uartMng->receiveBuffAddr = dd_uart_get_uart_mng(dd_uart_get(), ch).receiveBuffAddr;
	uartMng->receiveBuffSize = dd_uart_get_uart_mng(dd_uart_get(), ch).receiveBuffSize;
	uartMng->sendBuffAddr = dd_uart_get_uart_mng(dd_uart_get(), ch).sendBuffAddr;
	uartMng->sendBuffSize = dd_uart_get_uart_mng(dd_uart_get(), ch).sendBuffSize;
	uartMng->autoEcho = dd_uart_get_uart_mng(dd_uart_get(), ch).autoEcho;
	uartMng->saveBuff = dd_uart_get_uart_mng(dd_uart_get(), ch).saveBuff;
	uartMng->sendDmaCallback = dd_uart_get_uart_mng(dd_uart_get(), ch).sendDmaCallback;
	uartMng->recvDmaCallback = dd_uart_get_uart_mng(dd_uart_get(), ch).recvDmaCallback;

	uartMng->mode = (EDdUartMode)IO_USIO.UART[ch].SMR.bit.MD;
	uartMng->bitDirection = (DdUartBitDir)IO_USIO.UART[ch].SMR.bit.BDS;
	uartMng->stopBitLength = (DdUartStopBit)IO_USIO.UART[ch].SMR.bit.SBL;
	uartMng->dataLength = (DdUartDataLength)IO_USIO.UART[ch].ESCR.bit.L;
	if(IO_USIO.UART[ch].ESCR.bit.PEN == 1){
		if(IO_USIO.UART[ch].ESCR.bit.P == 1){
			uartMng->parityBit = DdUart_PARITY_BIT_ODD;
		}
		else{
			uartMng->parityBit = DdUart_PARITY_BIT_EVEN;
		}
	}
	else{
		uartMng->parityBit = DdUart_PARITY_BIT_NONE;
	}

	if(uartMng->fifoCtrl == NULL){
		return D_DDIM_OK;
	}

	uartMng->invNrz = IO_USIO.UART[ch].ESCR.bit.INV;
	uartMng->flowEnable = IO_USIO.UART[ch].ESCR.bit.FLWEN;
	uartMng->extClk = IO_USIO.UART[ch].BGR.bit.EXT;

	uartMng->fifoCtrl->fsel = IO_USIO.UART[ch].FCR.bit.FSEL;
	uartMng->fifoCtrl->flste = IO_USIO.UART[ch].FCR.bit.FLSTE;
	uartMng->fifoCtrl->fset = IO_USIO.UART[ch].FCR.bit.FSET;
	uartMng->fifoCtrl->fe2 = IO_USIO.UART[ch].FCR.bit.FE2;
	uartMng->fifoCtrl->fe1 = IO_USIO.UART[ch].FCR.bit.FE1;
	if(uartMng->fifoCtrl->fsel == 0){
		uartMng->fifoCtrl->fbyteRecv = IO_USIO.UART[ch].FBYTE.bit.__FIFO2;
	}
	else{
		uartMng->fifoCtrl->fbyteRecv = IO_USIO.UART[ch].FBYTE.bit.__FIFO1;
	}

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief  The value specified by the argument is set to the register of UART.
 * @param  DdUartMngSimple* uartMngSimple
 * @return kint32  D_DD_OK/DdUart_INPUT_PARAM_ERROR
 */
kint32	dd_uart_branch_initialize_simple(DdUartBranch *self, kuchar ch,
		DdUartMngSimple const *const uartMngSimple)
{
	kint32			ret;
	DdUartMng	uartMng;

#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(uartMngSimple == NULL){
		Ddim_Assertion(("UART input param error. [uartMngSimple] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	// The value gotten by the argument is set to a management table.
	// Baud rate
	uartMng.baudRate = uartMngSimple->baudRate;
	// Send callback function pointer
	uartMng.psendCallback = NULL;
	// Receive callback function pointer
	uartMng.preceiveCallback = uartMngSimple->preceiveCallback;
	// Receive buffer address
	uartMng.receiveBuffAddr = uartMngSimple->receiveBuffAddr;
	// Receive buffer size
	uartMng.receiveBuffSize = uartMngSimple->receiveBuffSize;
	// Send_buff_addr
	uartMng.sendBuffAddr = uartMngSimple->sendBuffAddr;
	// Send buffer size
	uartMng.sendBuffSize = uartMngSimple->sendBuffSize;
	// Auto Echo
	uartMng.autoEcho = uartMngSimple->autoEcho;
	// Save to the buffer
	uartMng.saveBuff = uartMngSimple->saveBuff;
	// UART Normal Mode
	uartMng.mode = DdUart_MODE_NORMAL;
	// Transferring Direction, LSB first or MSB first
	uartMng.bitDirection = DdUart_BIT_DIR_LSB_FIRST;
	// Stop bit length
	uartMng.stopBitLength = uartMngSimple->stopBitLength;
	// Data Length
	uartMng.dataLength = uartMngSimple->dataLength;
	// Parity bit type
	uartMng.parityBit = uartMngSimple->parityBit;
	// Internal clock
	uartMng.extClk = 0;
	// NRZ
	uartMng.invNrz = 0;
	// Hardware flow control disable
	uartMng.flowEnable = 0;
	// FIFO Setting
	uartMng.fifoCtrl = NULL;
	// Send DMA callback function pointer
	uartMng.sendDmaCallback = NULL;
	// Receive DMA callback function pointer
	uartMng.recvDmaCallback	= NULL;

	ret = dd_uart_ctrl(dd_uart_get(), ch, &uartMng);

	return ret;
}

/*
 * @brief	Set data information to send by UART (DMA).
 * @param	kuchar	ch
 *			void*	sendAddr
 *			kuint32	num
 * @return	kint32	D_DDIM_OK / DdUart_INPUT_PARAM_ERROR
 */
kint32 dd_uart_branch_set_send_data_dma(DdUartBranch *self, kuchar ch,
		void const* const sendAddr, kuint32 num)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdUart_CH_NUM_MAX){
		Ddim_Assertion(("UART input param error. [ch] = %d\n", ch));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(sendAddr == NULL){
		Ddim_Assertion(("UART input param error. [sendAddr] = NULL\n"));
		return DdUart_INPUT_PARAM_ERROR;
	}
	if(num == 0){
		Ddim_Assertion(("UART input param error. [num] = %d\n", num));
		return DdUart_INPUT_PARAM_ERROR;
	}
#endif

	dd_uart_set_info_send_addr(dd_uart_get(), ch, sendAddr);
	dd_uart_set_info_num(dd_uart_get(), ch, num);
	dd_uart_set_info_dma_wait(dd_uart_get(), ch, 0);

	return D_DDIM_OK;
}

#endif

DdUartBranch* dd_uart_branch_get(void)
{
	DdUartBranch *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_UART_BRANCH, sizeof(DdUartBranchPrivate));
	}

	return self;
}
