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
	DdimUserCustom_ER ercd;
	kuchar loopCnt;
	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);

	DD_ARM_CRITICAL_SECTION_START( gddIpcuSpinLock );

	/* Get Mail Box Number */
	if (16 > intCh) {
		unit = 0;
		mbNum = (ioIpcu0.mbadr[intCh].bit.mba - 0x100) >> 7;
	} else {
		unit = 1;
		intCh -= 16;
		mbNum = ((ioIpcu1.mbadr[intCh].bit.mba - 0x100) >> 7) + 8;
	}

	if (unit == 0) {
		/* Get Data */
		id = mbNum;
		for (loopCnt = 0; loopCnt <= C_IPCU_MB_DATA_MAX; loopCnt++) {
			priv->gddIpcuReqData[mbNum].mbData[loopCnt] = ioIpcu0.mailbox[id].data[loopCnt];
		}
		/* clear Destination Register */
		if (ioIpcu0.mbadr[intCh].bit.req != 0) {
			ioIpcu0.mailbox[id].dstclr.word = (1U << (intCh));
		}
	} else { /* unit 1 */
		/* Get Data */
		id = mbNum - 8;
		for (loopCnt = 0; loopCnt <= C_IPCU_MB_DATA_MAX; loopCnt++) {
			priv->gddIpcuReqData[mbNum].mbData[loopCnt] = ioIpcu1.mailbox[id].data[loopCnt];
		}
		/* clear Destination Register */
		if (ioIpcu1.mbadr[intCh].bit.req != 0) {
			ioIpcu1.mailbox[id].dstclr.word = (1U << (intCh));
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
		ercd = ddim_user_custom_set_flg(NULL, FID_DD_IPCU_REQ, (1 << mbNum));

		if (ercd == DdimUserCustom_E_TMOUT) {
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
	DdimUserCustom_FLGPTN waiptn, flgptn;
	DdimUserCustom_ER ercd;
	DdIpcuMbPrivate *priv = DD_IPCU_MB_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_wait_req() - IPCU ID No. exceeds the maximum. : ID = %lu\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	waiptn = ( 1 << id );
	ercd = ddim_user_custom_twai_flg(NULL, FID_DD_IPCU_REQ, waiptn, DdimUserCustom_TWF_ORW, &flgptn,
			D_DDIM_WAIT_END_TIME);
	ddim_user_custom_clr_flg(NULL,  FID_DD_IPCU_REQ, ~waiptn);
	if (ercd == DdimUserCustom_E_TMOUT) {
		Ddim_Print(("dd_ipcu_wait_req() : time out. ercd = %d\n", ercd));
		return C_IPCU_WAIT_TIMEOUT;
	}

	/* Level1 & Level2 D-Cache Clean by Addressing & size */
	ddim_user_custom_l1l2cache_clean_flush_addr(NULL, ( kuint32 )(priv->gddIpcuReqData[id].mbData ),
			C_IPCU_DATA_LENGTH );

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
//	DdimUserCustom_FLGPTN waiptn, flgptn;
//	DdimUserCustom_ER ercd;

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
 * @param	kulong dstCh 	Request transmit destination ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_dst_unit(DdIpcuMb *self, kuchar id, kulong dstCh )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_dst_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dstCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_dst_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if(( 1 & (ioIpcu0.mailbox[mbIdx].dststat.word >> dstCh)) == 0 ) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		ioIpcu0.mailbox[mbIdx].dstclr.word = (1U << (dstCh));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if(( 1 & (ioIpcu1.mailbox[mbIdx].dststat.word >> dstCh)) == 0 ) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		ioIpcu1.mailbox[mbIdx].dstclr.word = (1U << (dstCh));
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
		*dst = ioIpcu0.mailbox[mbIdx].dststat.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*dst = ioIpcu1.mailbox[mbIdx].dststat.word;
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
kint32 dd_ipcu_mb_get_mb_dst_stat_unit(DdIpcuMb *self, kuchar id, kulong dstCh, kulong *dst )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dstCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dst == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_dst_stat_unit() - Dst address is NULL. : ID = %d Ch = %lu\n", id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*dst = (1 & (ioIpcu0.mailbox[mbIdx].dststat.word >> (dstCh)));
	} else { /* unit 1 */
		mbIdx = id - 8;
		*dst = (1 & (ioIpcu1.mailbox[mbIdx].dststat.word >> (dstCh)));
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
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].maskset.word = msk;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu1.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].maskset.word = msk;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Mask request indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong mskCh 	Request mask ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_msk_unit(DdIpcuMb *self, kuchar id, kulong mskCh )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n",
				id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mskCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].maskset.word = (1U << (mskCh));
	} else { /* unit 2 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu1.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_msk_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].maskset.word = (1U << (mskCh));
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
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Msk = %lu\n", id, msk ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].maskclr.word = msk;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Msk = %lu\n", id, msk ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].maskclr.word = msk;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Clear Mask request
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong mskCh 	Request mask ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_msk_unit(DdIpcuMb *self, kuchar id, kulong mskCh )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Mailbox number exceeds the maximum. : ID = %d Ch = %lu\n", id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mskCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n", id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n", id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].maskclr.word = (1U << (mskCh));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_msk_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n", id, mskCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].maskclr.word = (1U << (mskCh));
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
		*msk = ioIpcu0.mailbox[mbIdx].maskstat.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*msk = ioIpcu1.mailbox[mbIdx].maskstat.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Mask request indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kuchar mskCh	Interrupt ch of IPCU(0-15)
 * @param	kulong *msk	 	Mask request
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_msk_stat_unit(DdIpcuMb *self, kuchar id, kulong mskCh, kulong *msk )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n", id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mskCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n", id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (msk == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Msk address is NULL. : ID = %d, Ch = %lu\n", id, mskCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*msk = (1 & (ioIpcu0.mailbox[mbIdx].maskstat.word >> (mskCh)));
	} else { /* unit 1 */
		mbIdx = id - 8;
		*msk = (1 & (ioIpcu1.mailbox[mbIdx].maskstat.word >> (mskCh)));
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
		if ( ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2 ) {
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
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
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
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if ((ioIpcu0.mailbox[mbIdx].ackset.word & ack) != 0) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - ACK is sending. : ID = %d\n", id ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		ioIpcu0.mailbox[mbIdx].ackset.word = ack;
	} else {
		/* Check Sourece register */
		if ( ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if ( ioIpcu1.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if ( ioIpcu1.mailbox[mbIdx].mode.bit.mode > DdIpcu_IPCU_MB_MODE_MANUAL_2 ) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		/* Check status with mode 2 */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if ((ioIpcu1.mailbox[mbIdx].ackset.word & ack) != 0) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack() - ACK is sending. : ID = %d\n", id ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		ioIpcu1.mailbox[mbIdx].ackset.word = ack;
	}

	DD_ARM_DSB_POU();

	return D_DDIM_OK;
}

/**
 * @brief	Set Acknowledge indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ackCh 	Acknowledge ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_ack_unit(DdIpcuMb *self, kuchar id, kulong ackCh )
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

	if (ackCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}

#endif // CO_PARAM_CHECK

	if (unit == 0) {
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if (1 & (ioIpcu0.mailbox[mbIdx].ackset.word >> (ackCh))) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - ACK is sending. : ID = %d Ch = %lu\n", id, ackCh ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		ioIpcu0.mailbox[mbIdx].ackset.word = (1U << (ackCh));
	} else {
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Request transmit source is not set. : ID = %d, Ack = %lu\n",
					id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu1.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode > DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check status with mode 2 */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_MANUAL_2) {
			if (1 & (ioIpcu1.mailbox[mbIdx].ackset.word >> (ackCh))) {
				Ddim_Print(( "dd_ipcu_mb_set_mb_ack_unit() - ACK is sending. : ID = %d Ch = %lu\n", id, ackCh ));
				return C_IPCU_INPUT_PARAM_ERR;
			}
		}

		ioIpcu1.mailbox[mbIdx].ackset.word = (1U << (ackCh));
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
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Clr = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Mode = %d\n",
					id, DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].ackclr.word = ack;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Clr = %lu\n",
					id, ack ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( ioIpcu1.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Mode = %d\n",
					id, DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].ackclr.word = ack;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Clear Acknowledge indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong ackCh 	Acknowledge by bit data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_clr_mb_ack_unit(DdIpcuMb *self,kuchar id, kulong ackCh )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if( id > C_IPCU_ID_MAX ){
		Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if( ackCh > C_IPCU_INT_MAX ){
		Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if( id < 8 ) {				/* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if( ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( ioIpcu0.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d, Ch = %lu\n", id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if( ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Ch = %lu\n", id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].ackclr.word = (1U << (ackCh));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if( ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Request transmit source is not set. : ID = %d, Ch = %lu\n",
					id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if( ioIpcu1.mailbox[mbIdx].send.bit.send == 0) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Send trigger is not set. : ID = %d, Ch = %lu\n", id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check mode type */
		if( ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_clr_mb_ack() - Mode is Auto clear mode. : ID = %d, Ch = %lu\n", id, ackCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].ackclr.word = (1U << (ackCh));
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
		if( ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR ) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = ioIpcu0.mailbox[mbIdx].ackstat.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = ioIpcu1.mailbox[mbIdx].ackstat.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Acknowledge indicated by IPCU ch
 * @param	kuchar id		IPCU ID(0 to 17)
 * @param	kuchar ackCh	Interrupt ch of IPCU(0-15)
 * @param	kulong *ack	 	Acknowledge
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_stat_unit(DdIpcuMb *self, kuchar id, kulong ackCh, kulong *ack )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ackCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Ack address is NULL. : ID = %d, Ch = %lu\n", id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		if (ioIpcu0.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (ioIpcu0.mailbox[mbIdx].ackstat.word >> ( ackCh )));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		if (ioIpcu1.mailbox[mbIdx].mode.bit.mode == DdIpcu_IPCU_MB_MODE_AUTO_CLEAR) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_stat_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (ioIpcu1.mailbox[mbIdx].ackstat.word >> ( ackCh )));
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
		mode = ioIpcu0.mailbox[mbIdx].mode.bit.mode;
		if(( mode != DdIpcu_IPCU_MB_MODE_MANUAL_2 ) && ( mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2 )) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = ioIpcu0.mailbox[mbIdx].acksrc.word;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		mode = ioIpcu1.mailbox[mbIdx].mode.bit.mode;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = ioIpcu1.mailbox[mbIdx].acksrc.word;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get Source information indicated by IPCU ch
 * @param	kuchar id		IPCU ID(0 to 17)
 * @param	kuchar ackCh	Interrupt ch of IPCU(0-15)
 * @param	kulong *ack  	Acknowledge source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_ack_src_unit(DdIpcuMb *self, kuchar id, kulong ackCh, kulong *ack )
{
	kulong mode;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_MB_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ackCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mailbox address is NULL. : ID = %d, Ch = %lu\n", id, ackCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check mode type */
		mode = ioIpcu0.mailbox[mbIdx].mode.bit.mode;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (ioIpcu0.mailbox[mbIdx].acksrc.word >> ( ackCh )));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check mode type */
		mode = ioIpcu1.mailbox[mbIdx].mode.bit.mode;
		if ((mode != DdIpcu_IPCU_MB_MODE_MANUAL_2) && (mode != DdIpcu_IPCU_MB_MODE_AUTO_ACK_2)) {
			Ddim_Print(( "dd_ipcu_mb_get_mb_ack_src_unit() - Mode is not correct. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		*ack = (1 & (ioIpcu1.mailbox[mbIdx].acksrc.word >> ( ackCh )));
	}

	return D_DDIM_OK;
}

/*##################################
  ##         Data Register        ##
  ##################################*/
/**
 * @brief	Get Transfer data
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kuchar datNum	Transfer data No.
 * @param	kulong *data 	Transfer data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_data(DdIpcuMb *self, kuchar id, kuchar datNum, kulong *data )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Mailbox number exceeds the maximum. : ID = %d, Data No = %d\n",
				id, datNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (datNum > C_IPCU_MB_DATA_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Transfer data No. exceeds the maximum. : ID = %d, Data No = %d\n",
				id, datNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (data == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_data() - Data address is NULL. : ID = %d, Data No = %d\n", id, datNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*data = ioIpcu0.mailbox[mbIdx].data[datNum];
	} else { /* unit 1 */
		mbIdx = id - 8;
		*data = ioIpcu1.mailbox[mbIdx].data[datNum];
	}

	return D_DDIM_OK;
}

DdIpcuMb* dd_ipcu_mb_new(void)
{
	DdIpcuMb* self = k_object_new_with_private(DD_TYPE_IPCU_MB, sizeof(DdIpcuMbPrivate));

	return self;
}

