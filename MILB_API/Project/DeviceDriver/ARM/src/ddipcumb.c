/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdIpcuMb
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ddipcu.h"
#include "ddipcumb.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdIpcuMb, dd_ipcu_mb);

#define DD_IPCU_MB_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdIpcuMbPrivate, DD_TYPE_IPCU_MB))


typedef struct _DdIpcuMbData DdIpcuMbData;

/* IPCU Request data */
struct _DdIpcuMbData
{
	kulong	mbData[C_IPCU_MB_DATA_TOTAL_NUM];	/* Mailbox data */
};

/* IPCU Callback function for Request */
typedef void (*T_DD_IPCU_REQ_FUNC)( kuchar );

//将S_GDD_IPCU_REQ_DATA放入私有结构
struct _DdIpcuMbPrivate
{
	volatile DdIpcuMbData gddIpcuReqData[C_IPCU_MB_TOTAL_NUM];
};


kulong gddIpcuSpinLock __attribute__((section(".LOCK_SECTION"), aligned(64)));
//static volatile DdIpcuMbData	S_GDD_IPCU_REQ_DATA[C_IPCU_MB_TOTAL_NUM] = {{{0}}};
static volatile T_DD_IPCU_REQ_FUNC	S_GDD_IPCU_REQ_FUNC[C_IPCU_UNIT_TOTAL_NUM][C_IPCU_INT_TOTAL_NUM] = {{0}};

/**
DECLS
*/

/**
IMPL
*/
static void dd_ipcu_mb_constructor(DdIpcuMb *self)
{
	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);
	int i, j;
	for (i = 0; i < C_IPCU_MB_TOTAL_NUM; i++) {
		for (j = 0; j < C_IPCU_MB_DATA_TOTAL_NUM; j++) {
			priv->gddIpcuReqData[i].mbData[j] = (kulong) 0;
		}
	}
}

static void dd_ipcu_mb_destructor(DdIpcuMb *self)
{
//	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Request Interrupt Handler of IPCU request or acknowledge.
 * @param	kuint32 intCh	Interrupt ch of IPCU(0-15)
 */
void dd_ipcu_int_handler_req(DdIpcuMb *self, kuint32 intCh )
{
	kulong unit;
	kulong mbNum;
	kulong id;
	DDIM_USER_ER ercd;
	kuchar loopCnt;
	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);

	DD_ARM_CRITICAL_SECTION_START( gddIpcuSpinLock );

	/* Get Mail Box Number */
	if (16 > intCh) {
		unit = 0;
		mbNum = (IO_IPCU0.MBADR[intCh].bit.MBA - 0x100) >> 7;
	} else {
		unit = 1;
		intCh -= 16;
		mbNum = ((IO_IPCU1.MBADR[intCh].bit.MBA - 0x100) >> 7) + 8;
	}

	if (unit == 0) {
		/* Get Data */
		id = mbNum;
		for (loopCnt = 0; loopCnt <= C_IPCU_MB_DATA_MAX; loopCnt++) {
			priv->gddIpcuReqData[mbNum].mbData[loopCnt] = IO_IPCU0.MAILBOX[id].DATA[loopCnt];
		}
		/* clear Destination Register */
		if (IO_IPCU0.MBADR[intCh].bit.REQ != 0) {
			IO_IPCU0.MAILBOX[id].DSTCLR.word = (1U << (intCh));
		}
	} else { /* unit 1 */
		/* Get Data */
		id = mbNum - 8;
		for (loopCnt = 0; loopCnt <= C_IPCU_MB_DATA_MAX; loopCnt++) {
			priv->gddIpcuReqData[mbNum].mbData[loopCnt] = IO_IPCU1.MAILBOX[id].DATA[loopCnt];
		}
		/* clear Destination Register */
		if (IO_IPCU1.MBADR[intCh].bit.REQ != 0) {
			IO_IPCU1.MAILBOX[id].DSTCLR.word = (1U << (intCh));
		}
	}

	DD_ARM_DSB_POU();

	/* Check Sync or Async */
	if (S_GDD_IPCU_REQ_FUNC[unit][intCh]) {
		/* Async process */
		/* Callback function */
		(*S_GDD_IPCU_REQ_FUNC[unit][intCh])(( kuchar ) mbNum);
	} else {
		/* Sync process */
		ercd = DDIM_User_Set_Flg( FID_DD_IPCU_REQ, (1 << mbNum));

		if (ercd == D_DDIM_USER_E_TMOUT) {
			Ddim_Print(("dd_ipcu_int_handler_req() : Set flag is timeout. ercd = %d\n", ercd));
		}
	}

	DD_ARM_CRITICAL_SECTION_END( gddIpcuSpinLock );
}

/**
 * @brief	Wait IPCU Request.
 * @param	kulong id		IPCU ID(0-15)
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_WAIT_TIMEOUT
 */
kint32 dd_ipcu_wait_req(DdIpcuMb *self, kulong id )
{
	DDIM_USER_FLGPTN waiptn, flgptn;
	DDIM_USER_ER ercd;
	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_wait_req() - IPCU ID No. exceeds the maximum. : ID = %lu\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	waiptn = ( 1 << id );

	ercd = DDIM_User_Twai_Flg( FID_DD_IPCU_REQ, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME);
	DDIM_User_Clr_Flg( FID_DD_IPCU_REQ, ~waiptn);
	if (ercd == D_DDIM_USER_E_TMOUT) {
		Ddim_Print(("dd_ipcu_wait_req() : time out. ercd = %d\n", ercd));
		return C_IPCU_WAIT_TIMEOUT;
	}

	/* Level1 & Level2 D-Cache Clean by Addressing & size */
	DDIM_User_L1l2cache_Clean_Flush_Addr(( kuint32 )(priv->gddIpcuReqData[id].mbData ), C_IPCU_DATA_LENGTH );

	return D_DDIM_OK;
}

/**
 * @brief	Get Request data.
 * @param	kulong id		IPCU ID(0-15)
 * @param	kulong* data		Top address of request data.
 * @param	kuchar  length	Size of data.
 * @return	D_DDIM_OK/C_IPCU_WAIT_TIMEOUT
 */
kint32 dd_ipcu_get_req_data(DdIpcuMb *self, kulong id, kulong *data, kuchar length)
{
//	DDIM_USER_FLGPTN waiptn, flgptn;
//	DDIM_USER_ER ercd;

	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_req_data() - IPCU ID No. exceeds the maximum. : ID = %lu\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (length > C_IPCU_SEND_DATA_MAX) {
		Ddim_Assertion(( "dd_ipcu_get_req_data() - IPCU data length exceeds the maximum size. : ID = %lu, "
				"data = 0x%p, length = %d\n", id, data, length ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	dd_ipcu_memcpy_ulong(NULL, data, ( kulong* )&(priv->gddIpcuReqData[id].mbData ), length );

	return D_DDIM_OK;
}

/**
 * @brief	Set Request callback function.
 * @param	kulong unit	IPCU unit(0-1)
 * @param	kulong ch	IPCU interrupt ch(0-15)
 * @param	T_DD_IPCU_REQ_FUNC	p_callreq_fn_ptrback	Callback function of Request
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_STATUS_ABNORMAL
 */
kint32 dd_ipcu_set_req_cb(DdIpcuMb *self, kulong unit, kulong ch, void (*reqFnPtr)( kuchar))
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_set_req_cb() - Unit No. exceeds the maximum. :  Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_set_req_cb() - INT Ch No. exceeds the maximum. :  Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	S_GDD_IPCU_REQ_FUNC[unit][ch] = *reqFnPtr;
	return D_DDIM_OK;
}

/**
 * @brief	Clear Destination information indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong dst_ch 	Request transmit destination ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_dst_unit(DdIpcuMb *self, kuchar id, kulong dst_ch )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_dst_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dst_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dst_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_dst_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dst_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dst_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if(( 1 & (IO_IPCU0.MAILBOX[mbIdx].DSTSTAT.word >> dst_ch)) == 0 ) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d Ch = %lu\n",
					id, dst_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		IO_IPCU0.MAILBOX[mbIdx].DSTCLR.word = (1U << (dst_ch));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dst_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if(( 1 & (IO_IPCU1.MAILBOX[mbIdx].DSTSTAT.word >> dst_ch)) == 0 ) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d Ch = %lu\n",
					id, dst_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		IO_IPCU1.MAILBOX[mbIdx].DSTCLR.word = (1U << (dst_ch));
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##  Destination Status Register ##
  ##################################*/
/**
 * @brief	Get Destination information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *dst 	Request transmit destination
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_dst_stat(DdIpcuMb *self, kuchar id, kulong *dst )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dst == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat() - Dst address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*dst = IO_IPCU0.MAILBOX[mbIdx].DSTSTAT.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*dst = IO_IPCU1.MAILBOX[mbIdx].DSTSTAT.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Destination information indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *dst 	Request transmit destination
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_dst_stat_unit(DdIpcuMb *self, kuchar id, kulong dst_ch, kulong *dst )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dst_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dst_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dst_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dst == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - Dst address is NULL. : ID = %d Ch = %lu\n", id, dst_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*dst = (1 & (IO_IPCU0.MAILBOX[mbIdx].DSTSTAT.word >> (dst_ch)));
	} else { /* unit 1 */
		mbIdx = id - 8;
		*dst = (1 & (IO_IPCU1.MAILBOX[mbIdx].DSTSTAT.word >> (dst_ch)));
	}

	return D_DDIM_OK;
}

/*##################################
  ##       Mask Set Register      ##
  ##################################*/
/**
 * @brief	Set Mask request
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong msk 	Mask request
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_msk(DdIpcuMb *self, kuchar id, kulong msk )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].MASKSET.word = msk;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].MASKSET.word = msk;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Mask request indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong msk_ch 	Request mask ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_msk_unit(DdIpcuMb *self, kuchar id, kulong msk_ch )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].MASKSET.word = (1U << (msk_ch));
	} else { /* unit 2 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].MASKSET.word = (1U << (msk_ch));
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##      Mask Clear Register     ##
  ##################################*/
/**
 * @brief	Clear Mask request indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong msk 	Mask request by bit data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_msk(DdIpcuMb *self, kuchar id, kulong msk )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_clr_mb_dst() - Mailbox number exceeds the maximum. : ID = %d, Msk = %lu\n", id, msk ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Msk = %lu\n", id, msk ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].MASKCLR.word = msk;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Msk = %lu\n", id, msk ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].MASKCLR.word = msk;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Clear Mask request
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong msk_ch 	Request mask ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_msk_unit(DdIpcuMb *self, kuchar id, kulong msk_ch )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n", id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n", id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n", id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].MASKCLR.word = (1U << (msk_ch));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n", id, msk_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].MASKCLR.word = (1U << (msk_ch));
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##     Mask Status Register     ##
  ##################################*/
/**
 * @brief	Get Mask request status
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *msk 	Mask request
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_msk_stat(DdIpcuMb *self, kuchar id, kulong *msk )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_msk_stat() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_msk_stat() - Msk address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*msk = IO_IPCU0.MAILBOX[mbIdx].MASKSTAT.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*msk = IO_IPCU1.MAILBOX[mbIdx].MASKSTAT.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Mask request indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kuchar msk_ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *msk	 	Mask request
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_msk_stat_unit(DdIpcuMb *self, kuchar id, kulong msk_ch, kulong *msk )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n", id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n", id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Msk address is NULL. : ID = %d, Ch = %lu\n", id, msk_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*msk = (1 & (IO_IPCU0.MAILBOX[mbIdx].MASKSTAT.word >> (msk_ch)));
	} else { /* unit 1 */
		mbIdx = id - 8;
		*msk = (1 & (IO_IPCU1.MAILBOX[mbIdx].MASKSTAT.word >> (msk_ch)));
	}

	return D_DDIM_OK;
}

/*##################################
  ##    Acknowledge Set Register  ##
  ##################################*/
/**
 * @brief	Set Acknowledge
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ack 	Acknowledge
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_ack(DdIpcuMb *self, kuchar id, kulong ack )
{
	kuchar loopCnt;
	kuchar bitCnt = 0;
	kuchar unit;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Unit No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) {
		mbIdx = id;
		unit = 0;
	} else if (id < 16) {
		mbIdx = id - 8;
		unit = 1;
	} else {
		mbIdx = id - 16;
		unit = 2;
	}

#ifdef CO_PARAM_CHECK
	if (unit == 0) {
		if ( IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2 ) {
			/* Check too many setting */
			for (loopCnt = 0; loopCnt <= C_IPCU_INT_MAX; loopCnt++) {
				if (1 & (ack >> loopCnt)) {
					bitCnt++;
				}
			}
			if (bitCnt > 1) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Too many setting bits. : ID = %d, Ack = %lu\n", id, ack ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}
	} else {
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			/* Check too many setting */
			for (loopCnt = 0; loopCnt <= C_IPCU_INT_MAX; loopCnt++) {
				if (1 & (ack >> loopCnt)) {
					bitCnt++;
				}
			}
			if (bitCnt > 1) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Too many setting bits. : ID = %d, Ack = %lu\n", id, ack ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if ((IO_IPCU0.MAILBOX[mbIdx].ACKSET.word & ack) != 0) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - ACK is sending. : ID = %d\n", id ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		IO_IPCU0.MAILBOX[mbIdx].ACKSET.word = ack;
	} else {
		/* Check Sourece register */
		if ( IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if ( IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if ( IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE > DdIpcu_IPCU_MB_MODE_MANUAL_2 ) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		/* Check status with mode 2 */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if ((IO_IPCU1.MAILBOX[mbIdx].ACKSET.word & ack) != 0) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - ACK is sending. : ID = %d\n", id ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		IO_IPCU1.MAILBOX[mbIdx].ACKSET.word = ack;
	}

	DD_ARM_DSB_POU();

	return D_DDIM_OK;
}

/**
 * @brief	Set Acknowledge indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ack_ch 	Acknowledge ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_ack_unit(DdIpcuMb *self, kuchar id, kulong ack_ch )
{
	kuchar unit;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	/* Get unit No. */
	if (id < 8) {
		mbIdx = id;
		unit = 0;
	} else if (id < 16) {
		mbIdx = id - 8;
		unit = 1;
	} else {
		mbIdx = id - 16;
		unit = 2;
	}

	if (ack_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}

#endif // CO_PARAM_CHECK

	if (unit == 0) {
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if (1 & (IO_IPCU0.MAILBOX[mbIdx].ACKSET.word >> (ack_ch))) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - ACK is sending. : ID = %d Ch = %lu\n", id, ack_ch ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		IO_IPCU0.MAILBOX[mbIdx].ACKSET.word = (1U << (ack_ch));
	} else {
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if (1 & (IO_IPCU1.MAILBOX[mbIdx].ACKSET.word >> (ack_ch))) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - ACK is sending. : ID = %d Ch = %lu\n", id, ack_ch ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		IO_IPCU1.MAILBOX[mbIdx].ACKSET.word = (1U << (ack_ch));
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##  Acknowledge Clear Register  ##
  ##################################*/
/**
 * @brief	Clear Acknowledge indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong msk 	Acknowledge by bit data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_ack(DdIpcuMb *self, kuchar id, kulong ack )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mailbox number exceeds the maximum. : ID = %d, Ack = %lu\n",
				id, ack ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Clr = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Mode = %d\n",
					id, DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].ACKCLR.word = ack;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Clr = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Mode = %d\n",
					id, DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].ACKCLR.word = ack;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Clear Acknowledge indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ack_ch 	Acknowledge by bit data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_ack_unit(DdIpcuMb *self,kuchar id, kulong ack_ch )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if( id > C_IPCU_ID_MAX ){
		Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if( ack_ch > C_IPCU_INT_MAX ){
		Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if( id < 8 ) {				/* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if( IO_IPCU0.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( IO_IPCU0.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d, Ch = %lu\n", id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if( IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Ch = %lu\n", id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU0.MAILBOX[mbIdx].ACKCLR.word = (1U << (ack_ch));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if( IO_IPCU1.MAILBOX[mbIdx].SRC.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( IO_IPCU1.MAILBOX[mbIdx].SEND.bit.SEND == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d, Ch = %lu\n", id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if( IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Ch = %lu\n", id, ack_ch ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		IO_IPCU1.MAILBOX[mbIdx].ACKCLR.word = (1U << (ack_ch));
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##  Acknowledge Status Register ##
  ##################################*/
/**
 * @brief	Get Acknowledge status
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *ack 	Acknowledge status
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_stat(DdIpcuMb *self, kuchar id, kulong *ack )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Ack address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		if( IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = IO_IPCU0.MAILBOX[mbIdx].ACKSTAT.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = IO_IPCU1.MAILBOX[mbIdx].ACKSTAT.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Acknowledge indicated by IPCU ch
 * @param	kuchar id		IPCU ID(0 to 17)
 * @param	kuchar ack_ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *ack	 	Acknowledge
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_stat_unit(DdIpcuMb *self, kuchar id, kulong ack_ch, kulong *ack )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Ack address is NULL. : ID = %d, Ch = %lu\n", id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		if (IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (IO_IPCU0.MAILBOX[mbIdx].ACKSTAT.word >> ( ack_ch )));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		if (IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (IO_IPCU1.MAILBOX[mbIdx].ACKSTAT.word >> ( ack_ch )));
	}

	return D_DDIM_OK;
}

/*##################################
  ##  Acknowledge Source Register ##
  ##################################*/
/**
 * @brief	Get Acknowledge source information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *ack 	Acknowledge source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_src(DdIpcuMb *self,  kuchar id, kulong *ack )
{
	kulong mode;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Ack address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		mode = IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE;
		if(( mode != DdIpcu_IPCU_MB_MODE_MANUAL_2 ) && ( mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2 )) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = IO_IPCU0.MAILBOX[mbIdx].ACKSRC.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		mode = IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = IO_IPCU1.MAILBOX[mbIdx].ACKSRC.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Source information indicated by IPCU ch
 * @param	kuchar id		IPCU ID(0 to 17)
 * @param	kuchar ack_ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *ack  	Acknowledge source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_src_unit(DdIpcuMb *self, kuchar id, kulong ack_ch, kulong *ack )
{
	kulong mode;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_MB_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack_ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mailbox address is NULL. : ID = %d, Ch = %lu\n", id, ack_ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		mode = IO_IPCU0.MAILBOX[mbIdx].MODE.bit.MODE;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (IO_IPCU0.MAILBOX[mbIdx].ACKSRC.word >> ( ack_ch )));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		mode = IO_IPCU1.MAILBOX[mbIdx].MODE.bit.MODE;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (IO_IPCU1.MAILBOX[mbIdx].ACKSRC.word >> ( ack_ch )));
	}

	return D_DDIM_OK;
}

/*##################################
  ##         Data Register        ##
  ##################################*/
/**
 * @brief	Get Transfer data
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kuchar dat_num	Transfer data No.
 * @param	kulong *data 	Transfer data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_data(DdIpcuMb *self, kuchar id, kuchar dat_num, kulong *data )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Mailbox number exceeds the maximum. : ID = %d, Data No = %d\n",
				id, dat_num ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dat_num > C_IPCU_MB_DATA_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Transfer data No. exceeds the maximum. : ID = %d, Data No = %d\n",
				id, dat_num ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (data == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Data address is NULL. : ID = %d, Data No = %d\n", id, dat_num ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*data = IO_IPCU0.MAILBOX[mbIdx].DATA[dat_num];
	} else { /* unit 1 */
		mbIdx = id - 8;
		*data = IO_IPCU1.MAILBOX[mbIdx].DATA[dat_num];
	}

	return D_DDIM_OK;
}

DdIpcuMb* dd_ipcu_mb_new(void)
{
	DdIpcuMb* self = k_object_new_with_private(DD_TYPE_IPCU_MB, sizeof(DdIpcuMbPrivate));

	return self;
}

