/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdIpcu
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		dd_ipcu.c
 * @brief		IPCU (Inter-Processor Communications Unit) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddipcu.h"	


K_TYPE_DEFINE_WITH_PRIVATE(DdIpcu, dd_ipcu);

#define DD_IPCU_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdIpcuPrivate, DD_TYPE_IPCU))

#define C_IPCU_MB_NOT_USE				(0xFF) /* IPCU Mailbox not used*/
#define C_IPCU_MAGIC_NUMBER		(0xBEEFCAFEul)


typedef struct _DdIpcuSendInfo DdIpcuSendInfo;

/* IPCU Send information table */
struct _DdIpcuSendInfo
{
	kuchar 	state;				/* State of IPCU process*/
	kuchar 	async;				/* Async*/
};

/* IPCU Callback function for Acknowledge */
typedef void (*DdIpcuAckFunc)( kuchar );

struct _DdIpcuPrivate
{

};


static volatile DdIpcuSendInfo	S_GDD_IPCU_SEND_INFO_TBL[C_IPCU_MB_TOTAL_NUM] = {{0}};
static volatile DdIpcuAckFunc		S_GDD_IPCU_ACK_FUNC[C_IPCU_MB_TOTAL_NUM] = {0};

/**
DECLS
*/

/**
IMPL
*/
static void dd_ipcu_constructor(DdIpcu *self)
{
//	DdIpcuPrivate *priv = DD_IPCU_GET_PRIVATE(self);
}

static void dd_ipcu_destructor(DdIpcu *self)
{
//	DdIpcuPrivate *priv = DD_IPCU_GET_PRIVATE(self);
}
/**
PUBLIC
*/
//---------------------------- driver section ----------------------------
void dd_ipcu_memcpy_ulong(DdIpcu *self, kulong* const dst, kulong* const src, kuint32 cpSize)
{
	kuint32 i;
	kulong words;

	words = (cpSize + sizeof(kulong) - 1) / sizeof(kulong);

	for (i = 0; i < words; i++) {
		dst[i] = src[i];
	}
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief	Execute exclusive control for designated IPCU unit and Mailbox.
 * @param	kuchar 	mbNum	Mailbox No.(0-15)
 * @param	kint32	tmout
 * @param	kuchar* 	id		IPCU ID(0-15)
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_MB_BUSY
 */
kint32 dd_ipcu_open(DdIpcu *self, kuchar mbNum, kint32 tmout, kuchar *id )
{
	DdimUserCustom_ER ercd;

#ifdef CO_PARAM_CHECK
	if (mbNum > C_IPCU_MB_MAX) {
		Ddim_Assertion(( "dd_ipcu_open() - IPCU Mailbox No. exceeds the maximum. : MB No. = %d\n", mbNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if ( NULL == id) {
		Ddim_Assertion(( "dd_ipcu_open() - IPCU ID address is NULL.\n" ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (tmout == DdimUserCustom_SEM_WAIT_POL) {
		ercd = ddim_user_custom_pol_sem(NULL, SID_DD_IPCU(mbNum));
	} else {
		ercd = ddim_user_custom_twai_sem(NULL, SID_DD_IPCU(mbNum), (DdimUserCustom_TMO) tmout);
	}

	if ( DdimUserCustom_E_OK != ercd) {
		if ( DdimUserCustom_E_TMOUT == ercd) {
			return C_IPCU_SEM_TIMEOUT;
		}
		return C_IPCU_SEM_NG;
	}

	/* Get Mailbox */
	if (S_GDD_IPCU_SEND_INFO_TBL[mbNum].state == C_IPCU_STATE_NONE) {
		*id = mbNum;
	} else {
		Ddim_Assertion(( "dd_ipcu_open(%d) - Selected Mailbox is busy.\n", mbNum ));
		return C_IPCU_MB_BUSY;
	}
	
	/* Set Send info table */
	S_GDD_IPCU_SEND_INFO_TBL[mbNum].state = C_IPCU_STATE_KEEP;
	
	return D_DDIM_OK;
}

/**
 * @brief	Cancel exclusive control for designated IPCU unit and Mailbox.
 * @param	kuchar id	IPCU ID(0-15)
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_STATUS_ABNORMAL
 */
kint32 dd_ipcu_close(DdIpcu *self, kuchar id )
{
	kuchar mbIdx;
	DdimUserCustom_ER ercd;
	
#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Assertion(( "dd_ipcu_close(NULL, ) - IPCU ID No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	ercd = ddim_user_custom_sig_sem(NULL,  SID_DD_IPCU( id ));

	if ( DdimUserCustom_E_OK != ercd) {
		return C_IPCU_SEM_NG;
	}

	if (S_GDD_IPCU_SEND_INFO_TBL[id].state != C_IPCU_STATE_KEEP) {
		Ddim_Assertion(( "dd_ipcu_close() - IPCU state Error! : ID = %d, Status = %d\n", id,
				S_GDD_IPCU_SEND_INFO_TBL[id].state ));
		return C_IPCU_STATUS_ABNORMAL;
	}
	
	/* Release Malibox */
	if (id < 8) {
		mbIdx = id;
		ioIpcu0.mailbox[mbIdx].src.word = 0; /* unit 0 */
	} else {
		mbIdx = id - 8;
		ioIpcu1.mailbox[mbIdx].src.word = 0; /* unit 1 */
	}
	
	/* Clear Send info table */
	S_GDD_IPCU_SEND_INFO_TBL[id].state = C_IPCU_STATE_NONE;
	
	/* Clear callback function */
	S_GDD_IPCU_ACK_FUNC[id] = NULL;
	
	return D_DDIM_OK;
}

/**
 * @brief	Set IPCU operation condition and callback function for designated IPCU unit and Mailbox.
 * @param	kuchar id	IPCU ID(0-15)
 * @param	DdIpcu self
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_ctrl(kuchar id, DdIpcu const* const self)
{
	kulong srcNum;
	kulong dstChBit;
	kulong maskChBit;
	kuchar mbIdx;

	srcNum = self->srcChNum;
	dstChBit = self->dstChBit;
	maskChBit = self->maskChBit;
	
#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Assertion(( "dd_ipcu_ctrl() - IPCU ID No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (self == NULL) {
		Ddim_Assertion(( "dd_ipcu_ctrl() - IPCU MNG Tbl address is NULL. ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (self->dataSize > C_IPCU_SEND_DATA_MAX) {
		Ddim_Assertion(( "dd_ipcu_ctrl() - IPCU data size exceeds the maximum. : ID = %d, size = %lu\n",
				id, self -> dataSize ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Level1 & Level2 D-Cache Clean by Addressing & size */
	ddim_user_custom_l1l2cache_clean_flush_addr(NULL,  ( kuint32 )( self->sendData ), self->dataSize );
	
	/* Clear local data */
	memset((void*)&S_GDD_IPCU_ACK_FUNC[id], 0, sizeof(DdIpcuSendInfo));

	if (id < 8) {
		mbIdx = id;
		/* Set source */
		ioIpcu0.mailbox[mbIdx].src.word = (1 << srcNum);

		if (ioIpcu0.mailbox[mbIdx].src.word != (1 << srcNum)) {
			return C_IPCU_MB_BUSY;
		}
		/* Set destination */
		ioIpcu0.mailbox[mbIdx].dstset.word = dstChBit;
		/* Set mask */
		ioIpcu0.mailbox[mbIdx].maskset.word = maskChBit;
		/* Set mode */
		ioIpcu0.mailbox[mbIdx].mode.bit.mode = self->mode;
		/* Set data */
		dd_ipcu_memcpy_ulong(NULL, (kulong*) &(ioIpcu0.mailbox[mbIdx].data), (kulong*) &(self->sendData),
				self->dataSize);
	} else {
		mbIdx = id - 8;
		/* Set Mailbox */
		ioIpcu1.mailbox[mbIdx].src.word = (1 << srcNum);

		if (ioIpcu1.mailbox[mbIdx].src.word != (1 << srcNum)) {
			return C_IPCU_MB_BUSY;
		}
		/* Set destination */
		ioIpcu1.mailbox[mbIdx].dstset.word = dstChBit;
		/* Set mask */
		ioIpcu1.mailbox[mbIdx].maskset.word = maskChBit;
		/* Set Mode */
		ioIpcu1.mailbox[mbIdx].mode.bit.mode = self->mode;
		/* Set data */
		dd_ipcu_memcpy_ulong(NULL, (kulong*)&( ioIpcu1.mailbox[mbIdx].data ), (kulong*)&( self -> sendData ),
				self -> dataSize );
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Get IPCU operation condition and callback function for designated IPCU unit and Mailbox.
 * @param	kuchar id	IPCU ID(0-15)
 * @param	DdIpcu *self
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_ctrl(kuchar id, DdIpcu * const self)
{
	kuchar srcCnt;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Assertion(( "dd_ipcu_get_ctrl() - IPCU ID No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (self == NULL) {
		Ddim_Assertion(( "dd_ipcu_get_ctrl() - IPCU MNG Tbl address is NULL. ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	if (id < 8) {
		mbIdx = id;
		/* Get source */
		for (srcCnt = 0; srcCnt < C_IPCU_ID_MAX; srcCnt++) {
			if (1 & (ioIpcu0.mailbox[mbIdx].src.word >> (srcCnt))) {
				self->srcChNum = srcCnt;
			}
		}
		/* Get destination */
		self->dstChBit = ioIpcu0.mailbox[mbIdx].dststat.word;
		/* Get mask */
		self->maskChBit = ioIpcu0.mailbox[mbIdx].maskstat.word;
		/* Get mode */
		self->mode = ioIpcu0.mailbox[mbIdx].mode.bit.mode;
		/* Get data */
		dd_ipcu_memcpy_ulong(NULL, (kulong*) &(self->sendData), (kulong*) &(ioIpcu0.mailbox[mbIdx].data),
				self->dataSize);
	} else {
		mbIdx = id - 8;
		/* Get source */
		for (srcCnt = 0; srcCnt < C_IPCU_ID_MAX; srcCnt++) {
			if (1 & (ioIpcu1.mailbox[mbIdx].src.word >> (srcCnt))) {
				self->srcChNum = srcCnt;
			}
		}
		/* Get destination */
		self->dstChBit = ioIpcu1.mailbox[mbIdx].dststat.word;
		/* Get mask */
		self->maskChBit = ioIpcu1.mailbox[mbIdx].maskstat.word;
		/* Get mode */
		self->mode = ioIpcu1.mailbox[mbIdx].mode.bit.mode;
		/* Get data */
		dd_ipcu_memcpy_ulong(NULL, (kulong*) &(self->sendData), (kulong*) &(ioIpcu1.mailbox[mbIdx].data),
				self->dataSize);
	}
	
	return D_DDIM_OK;
}
/**
 * @brief	Start sending data.
 * @param	kuchar id	IPCU ID(0-15)
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_WAIT_TIMEOUT
 */
kint32 dd_ipcu_start(DdIpcu *self, kuchar id )
{
	DdimUserCustom_FLGPTN flgptn;
	DdimUserCustom_ER ercd;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Assertion(( "dd_ipcu_start() - IPCU ID No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	if (id < 8) {
		mbIdx = id;
		/* Set source register */
		ioIpcu0.mailbox[mbIdx].send.bit.send = 1; /* unit 0 */
	} else {
		mbIdx = id - 8;
		/* Set source register */
		ioIpcu1.mailbox[mbIdx].send.bit.send = 1;	/* unit 1 */
	}
	/* Check Sync or Async */
	if( S_GDD_IPCU_SEND_INFO_TBL[id].async == 0 ) {
		/* Sync process */
		ercd = ddim_user_custom_twai_flg(NULL, FID_DD_IPCU_ACK, (1 << id), DdimUserCustom_TWF_ORW, &flgptn,
				D_DDIM_WAIT_END_TIME);
		ddim_user_custom_clr_flg(NULL,  FID_DD_IPCU_ACK, ~(1 << id));
		if (ercd == DdimUserCustom_E_TMOUT) {
			Ddim_Print(("dd_ipcu_start() : time out. ercd = %d\n", ercd));
			return C_IPCU_WAIT_TIMEOUT;
		}
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Acknowledge Interrupt Handler of IPCU request or acknowledge.
 * @param	kuint32 intCh	Interrupt ch of IPCU(0-15)
 * @param	kulong  *unit	IPCU unit(0-1)
 * @param	kulong  *mbIdx	Mailbox number(0-15)
 */
void dd_ipcu_int_handler_ack(DdIpcu *self,  kuint32 intCh, kulong *mbNum )
{
	kulong unit;
	kulong mbIdx;
	kulong ackReg;

	/* Get Mail Box Number */
	if (16 > intCh) {
		unit = 0;
		mbIdx = (ioIpcu0.mbadr[intCh].bit.mba - 0x100) >> 7;
		*mbNum = mbIdx;
	} else {
		unit = 1;
		intCh -= 16;
		mbIdx = (ioIpcu1.mbadr[intCh].bit.mba - 0x100) >> 7;
		*mbNum = mbIdx + 8;
	}

	if (unit == 0) {
		/* Read acknowlegde status */
		ackReg = ioIpcu0.mailbox[mbIdx].ackstat.word;
		/* Clear acknowlegde */
		ioIpcu0.mailbox[mbIdx].ackclr.word = ackReg;
		/* Clear source register */
		ioIpcu0.mailbox[mbIdx].src.word = 0;
	} else {
		/* Read acknowlegde status */
		ackReg = ioIpcu1.mailbox[mbIdx].ackstat.word;
		/* Clear acknowlegde */
		ioIpcu1.mailbox[mbIdx].ackclr.word = ackReg;
		/* Clear source register */
		ioIpcu1.mailbox[mbIdx].src.word = 0;
	}
	
	DD_ARM_DSB_POU();
	
#if 0
	/* Check Sync or Async */
	if( S_GDD_IPCU_SEND_INFO_TBL[mbIdx].async == 0 ) {
		/* Sync process */
		ercd = ddim_user_custom_set_flg(NULL, FID_DD_IPCU_ACK, (1 << mbIdx));

		if( ercd == DdimUserCustom_E_TMOUT ) {
			Ddim_Print(("Dd_IPCU_Int_Handler(ACK) : Set flag is timeout. ercd = %d\n", ercd));
		}
	} else {
		/* Async process */
		/* Callback check */
		if( S_GDD_IPCU_ACK_FUNC[mbNum] ) {
			/* Callback function */
			( *S_GDD_IPCU_ACK_FUNC[mbNum] )( (kulong)intCh );
		}
	}
#endif
}

/**
 * @brief	Start Ack process.
 * @param	kulong  mbNum	Mailbox index(0-7)
 * @param	kuint32 intCh	Interrupt ch of IPCU(0-15)
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_start_ack_proc(DdIpcu *self, kulong mbNum, kulong intCh )
{
	DdimUserCustom_ER ercd;
	kulong id;
	
#ifdef CO_PARAM_CHECK
	if (mbNum > C_IPCU_MB_MAX) {
		Ddim_Assertion(( "Dd_IPCU_Receive_Ack() - IPCU Mailbox No. exceeds the maximum. : MB No. = %lu\n", mbNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	id = mbNum;

	/* Check Sync or Async */
	if (S_GDD_IPCU_SEND_INFO_TBL[id].async == 0) {
		/* Sync process */
		ercd = ddim_user_custom_set_flg(NULL, FID_DD_IPCU_ACK, (1 << id));

		if (ercd == DdimUserCustom_E_TMOUT) {
			Ddim_Print(("Dd_IPCU_Int_Handler(ACK) : Set flag is timeout. ercd = %d\n", ercd));
		}
	} else {
		/* Async process */
		/* Callback check */
		if (S_GDD_IPCU_ACK_FUNC[id]) {
			/* Callback function */
			(*S_GDD_IPCU_ACK_FUNC[id])((kulong) intCh);
		}
	}
	return D_DDIM_OK;
}

/**
 * @brief	Set Acknowledge callback function.
 * @param	kuchar id		IPCU ID(0-15)
 * @param	DdIpcuAckFunc	ackFnPtr Callback function of Acknowledge
 * @return	D_DDIM_OK/C_IPCU_INPUT_PARAM_ERR/C_IPCU_STATUS_ABNORMAL
 */
kint32 dd_ipcu_set_ack_cb(DdIpcu *self, kuchar id, void (* ackFnPtr )( kuchar ))
{
#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_set_ack_cb() - IPCU ID No. exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ackFnPtr == NULL) {
		Ddim_Print(( "dd_ipcu_set_ack_cb() - Callback function is nothing. : ID = %d\n", id ));
		S_GDD_IPCU_SEND_INFO_TBL[id].async = 0;
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	if (S_GDD_IPCU_SEND_INFO_TBL[id].state != C_IPCU_STATE_KEEP) {
		Ddim_Print(( "dd_ipcu_set_ack_cb() - state Error! : id=%d\n", id ));
		return C_IPCU_STATUS_ABNORMAL;
	}
	
	S_GDD_IPCU_ACK_FUNC[id] = *ackFnPtr;
	S_GDD_IPCU_SEND_INFO_TBL[id].async = 1;
	
	return D_DDIM_OK;
}

/*##################################
  ##   Interrupt Status Register  ##
  ##################################*/

/**
 * @brief	Get Interrupt Status
 * @param	kulong unit		IPCU Unit(0-1)
 * @param	kulong ch		Interrupt ch of IPCU(0-15)
 * @param	kulong *state	Interrupt Status of IPCU
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_int_stat(DdIpcu *self, kulong unit, kulong ch, kulong *state)
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_get_int_stat() - Unit No. exceeds the maximum. :  Unit = %lu, Ch = %lu\n",
				unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_int_stat() - INT Ch No. exceeds the maximum. :  Unit = %lu, Ch = %lu\n",
				unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (state == NULL) {
		Ddim_Print(( "dd_ipcu_get_int_stat() - State address is NULL. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		*state = ioIpcu0.isr[ch].word; /* unit 0 */
	} else {
		*state = ioIpcu1.isr[ch].word; /* unit 1 */
	}
	return D_DDIM_OK;
}

/**
 * @brief	Get Interrupt Status indicated by Mailbox number
 * @param	kulong unit		IPCU Unit(0-1)
 * @param	kulong ch		Interrupt ch of IPCU(0-15)
 * @param	kuchar mbNum 	Mailbox number
 * @param	kulong *state	Interrupt Status of IPCU
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_int_stat_mb(DdIpcu *self, kulong unit, kulong ch, kuchar mbNum, kulong *state)
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_get_int_stat_mb() - Unit No. exceeds the maximum. : Unit = %lu, Ch = %lu\n",
				unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_int_stat_mb() - INT Ch No. exceeds the maximum. : Unit = %lu, Ch = %lu\n",
				unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mbNum > C_IPCU_MB_MAX) {
		Ddim_Print(( "dd_ipcu_get_int_stat_mb() - IPCU Mailbox No. exceeds the maximum. : Unit = %lu, Ch = %lu "
				"Bit = %u\n", unit, ch, mbNum));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (state == NULL) {
		Ddim_Print(( "dd_ipcu_get_int_stat_mb() - State address is NULL.\n" ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		*state = (1 & (ioIpcu0.isr[ch].word >> (mbNum))); /* unit 0 */
	} else {
		*state = (1 & (ioIpcu1.isr[ch].word >> (mbNum))); /* unit 1 */
	}
	return D_DDIM_OK;
}

/*##################################
  ##   Mailbox Address Register   ##
  ##################################*/
/**
 * @brief	Get Acknowledge status
 * @param	kulong unit	IPCU Unit(0-1)
 * @param	kulong ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *ack  Acknowledge(0:not Ack, 1:Ack)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_ack(DdIpcu *self, kulong unit, kulong ch, kulong *ack )
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_ack() - Unit No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_ack() - INT Ch No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ack == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_ack() - Ack address is NULL. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	if (unit == 0) {
		*ack = ioIpcu0.mbadr[ch].bit.ack; /* unit 0 */
	} else {
		*ack = ioIpcu1.mbadr[ch].bit.ack; /* unit 1 */
	}
	return D_DDIM_OK;
}

/**
 * @brief	Get Request status
 * @param	kulong unit	IPCU Unit(0-1)
 * @param	kulong ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *req  Request(0:not Req, 1:Req)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_req(DdIpcu *self, kulong unit, kulong ch, kulong *req)
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_req() - Unit No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_req() - INT Ch No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (req == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_req() - Req address is NULL. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	if (unit == 0) {
		*req = ioIpcu0.mbadr[ch].bit.req; /* unit 0 */
	} else {
		*req = ioIpcu1.mbadr[ch].bit.req; /* unit 1 */
	}
	return D_DDIM_OK;
}

/**
 * @brief	Get Mailbox Address
 * @param	kulong unit	IPCU Unit(0-1)
 * @param	kulong ch	Interrupt ch of IPCU(0-15)
 * @param	kulong *mba  Mailbox Address
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_adr(DdIpcu *self, kulong unit, kulong ch, kulong *mba)
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_adr() - Unit No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (ch > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_adr() - INT Ch No. exceeds the maximum. : Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mba == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_adr() - Mailbox address is NULL. Unit = %lu, Ch = %lu\n", unit, ch ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		*mba = ioIpcu0.mbadr[ch].bit.mba; /* unit 0 */
	} else {
		*mba = ioIpcu1.mbadr[ch].bit.mba; /* unit 1 */
	}
	return D_DDIM_OK;
}

/*##################################
  ##   	    Source Register       ##
  ##################################*/
/**
 * @brief	Get Source information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *src  Request transmit source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_src(DdIpcu *self, kuchar id, kulong *src )
{
		kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src() - Mailbox number exceeds the maximum. : ID = %u\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (src == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_src() - Mailbox address is NULL. : ID = %u\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) {
		mbIdx = id;
		*src = ioIpcu0.mailbox[mbIdx].src.word; /* unit 0 */
	} else {
		mbIdx = id - 8;
		*src = ioIpcu1.mailbox[mbIdx].src.word; /* unit 1 */
	}
	
	return D_DDIM_OK;
}

/**
 * @brief	Get Source information indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong srcCh	Interrupt ch of IPCU(0-15)
 * @param	kulong *src  	Request transmit source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_src_unit(DdIpcu *self, kuchar id, kulong srcCh, kulong *src)
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Mailbox number exceeds the maximum. : ID = %d, Ch = %lu\n",
				id, srcCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (srcCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, srcCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (src == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_src_unit() - Mailbox address is NULL. : ID = %d, Ch = %lu\n", id, srcCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*src = (1 & (ioIpcu0.mailbox[mbIdx].src.word >> (srcCh)));
	} else { /* unit 2 */
		mbIdx = id - 8;
		*src = (1 & (ioIpcu1.mailbox[mbIdx].src.word >> (srcCh)));
	}
	
	return D_DDIM_OK;
}

/**
 * @brief	Set Source information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong src   Request transmit source
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_set_mb_src(DdIpcu *self, kuchar id, kulong src )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_src() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (src == 0) {
		Ddim_Print(( "dd_ipcu_set_mb_src() - It's not registered. : ID = %d, SRC = %lu\n", id, src));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		ioIpcu0.mailbox[mbIdx].src.word = src;
	} else { /* unit 1 */
		mbIdx = id - 8;
		ioIpcu1.mailbox[mbIdx].src.word = src;
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##        Mode Register         ##
  ##################################*/
/**
 * @brief	Get Mode information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *mode Operation mode
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_mode(DdIpcu *self, kuchar id, kulong *mode )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_mode() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mode == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_mode() - Mode address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*mode = ioIpcu0.mailbox[mbIdx].mode.bit.mode;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*mode = ioIpcu1.mailbox[mbIdx].mode.bit.mode;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief	Set Mode information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	DdIpcuMbMode mode  Operation mode
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_set_mb_mode(DdIpcu *self, kuchar id, DdIpcuMbMode mode)
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_mode() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mode >= DdIpcu_IPCU_MB_MODE_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_mode() - Mode address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		ioIpcu0.mailbox[mbIdx].mode.bit.mode = mode;
	} else { /* unit 1 */
		mbIdx = id - 8;
		ioIpcu1.mailbox[mbIdx].mode.bit.mode = mode;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##        Send Register         ##
  ##################################*/
/**
 * @brief	Get Send trigger
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong *send Send trigger
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_get_mb_send(DdIpcu *self, kuchar id, kulong *send)
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_send() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (send == NULL) {
		Ddim_Print(( "dd_ipcu_get_mb_send() - Send address is NULL. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		*send = ioIpcu0.mailbox[mbIdx].send.bit.send;
	} else { /* unit 1 */
		mbIdx = id - 8;
		*send = ioIpcu1.mailbox[mbIdx].send.bit.send;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief	Set Send trigger
 * @param	kuchar id	IPCU ID(0 to 17)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_set_mb_send(DdIpcu *self, kuchar id)
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_send() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_send() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].send.bit.send = 1;
	} else { /* unit 1 */
		mbIdx = id - 8;
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_send() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].send.bit.send = 1;
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##  Destination Set Register    ##
  ##################################*/
/**
 * @brief	Set Destination information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong dst 	Request transmit destination
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_set_mb_dst(DdIpcu *self, kuchar id, kulong dst)
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_get_mb_src() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu0.mailbox[mbIdx].dstset.word = dst;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu1.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Send trigger is set. : ID = %d\n", id ));
			return C_IPCU_STATUS_ABNORMAL;
		}

		ioIpcu1.mailbox[mbIdx].dstset.word = dst;
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Destination information indicated by IPCU ch
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong dstCh 	Request transmit destination ch(0-15)
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_set_mb_dst_unit(DdIpcu *self, kuchar id, kulong dstCh )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - Mailbox number exceeds the maximum. : ID = %d\n", id ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (dstCh > C_IPCU_INT_MAX) {
		Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - INT Ch No. exceeds the maximum. : ID = %d Ch = %lu\n",
				id, dstCh ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if( id < 8 ) {				/* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu0.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		
		ioIpcu0.mailbox[mbIdx].dstset.word = (1U << (dstCh));
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - Request transmit source is not set. : ID = %d Ch = %lu\n",
					id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Send register */
		if (ioIpcu1.mailbox[mbIdx].send.bit.send != 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst_unit() - Send trigger is set. : ID = %d Ch = %lu\n", id, dstCh ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		
		ioIpcu1.mailbox[mbIdx].dstset.word = (1U << (dstCh));
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##  Destination Clear Register  ##
  ##################################*/
/**
 * @brief	Clear Destination information
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kulong dst 	Request transmit destination by bit data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_clr_mb_dst(DdIpcu *self, kuchar id, kulong dst)
{
	kuchar loopCnt;
	kuchar bitCnt = 0;
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_clr_mb_dst() - Mailbox number exceeds the maximum. : ID = %d, Dst = %lu\n",
				id, dst ));
		return C_IPCU_INPUT_PARAM_ERR;
	}

	for (loopCnt = 0; loopCnt <= C_IPCU_INT_MAX; loopCnt++) {
		if (1 & (dst >> loopCnt)) {
			bitCnt++;
		}
	}
	if (bitCnt > 1) {
		Ddim_Print(( "dd_ipcu_clr_mb_dst() - Too many setting bits. : ID = %d, Dst = %lu\n", id, dst ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	
#endif // CO_PARAM_CHECK
	
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		/* Check Sourece register */
		if (ioIpcu0.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Dst = %lu\n",
					id, dst ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if (dst != (ioIpcu0.mailbox[mbIdx].dststat.word & dst)) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d, Dst = %lu\n",
					id, dst ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		
		ioIpcu0.mailbox[mbIdx].dstclr.word = dst;
	} else { /* unit 1 */
		mbIdx = id - 8;
		/* Check Sourece register */
		if (ioIpcu1.mailbox[mbIdx].src.word == 0) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request transmit source is not set. : ID = %d, Dst = %lu\n", id, dst ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		/* Check Destination Status register */
		if (dst != (ioIpcu1.mailbox[mbIdx].dststat.word & dst)) {
			Ddim_Print(( "dd_ipcu_set_mb_dst() - Request for designated ch is nothing. : ID = %d, Dst = %lu\n", id, dst ));
			return C_IPCU_STATUS_ABNORMAL;
		}
		
		ioIpcu1.mailbox[mbIdx].dstclr.word = dst;
	}
	
	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Set Transfer data
 * @param	kuchar id	IPCU ID(0 to 17)
 * @param	kuchar datNum	Transfer data No.
 * @param	kulong data 		Transfer data
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_set_mb_data(DdIpcu *self, kuchar id, kuchar datNum, kulong data )
{
	kuchar mbIdx;

#ifdef CO_PARAM_CHECK
	if (id > C_IPCU_ID_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_data() - Mailbox number exceeds the maximum. : ID = %d, Data No = %d\n",
				id, datNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (datNum > C_IPCU_MB_DATA_MAX) {
		Ddim_Print(( "dd_ipcu_mb_set_mb_data() - Transfer data No. exceeds the maximum. : ID = %d, Data No = %d\n",
				id, datNum ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK
	/* Get unit No. */
	if (id < 8) { /* unit 0 */
		mbIdx = id;
		ioIpcu0.mailbox[mbIdx].data[datNum] = data;
	} else { /* unit 1 */
		mbIdx = id - 8;
		ioIpcu1.mailbox[mbIdx].data[datNum] = data;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/*##################################
  ##    MailBox Status Register   ##
  ##################################*/
/**
 * @brief	Get MailBox status
 * @param	kuchar unit		IPCU Unit(0-1)
 * @param	kulong *mb_stat 	MailBox status
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_stat(DdIpcu *self,  kuchar unit, kulong *mb_stat )
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_stat() - Unit No. exceeds the maximum. : Unit = %d\n", unit ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (mb_stat == NULL) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_stat() - MB status address is NULL. : Unit = %d\n", unit ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		*mb_stat = ioIpcu0.mbstat.word;
	} else {
		*mb_stat = ioIpcu1.mbstat.word;
	}

	DD_ARM_DSB_POU();
	return D_DDIM_OK;
}

/**
 * @brief	Get MailBox status
 * @param	kuchar unit		IPCU Unit(0-1)
 * @param	kulong num		Mailbox number(0-7)
 * @param	kulong *mb_stat 	MailBox status
 * @return  D_DDIM_OK / C_IPCU_INPUT_PARAM_ERR
 */
kint32 dd_ipcu_mb_get_mb_stat_mb(DdIpcu *self, kuchar unit, kulong num, kulong *mb_stat )
{
#ifdef CO_PARAM_CHECK
	if (unit > C_IPCU_UNIT_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_stat_mb() - Unit No. exceeds the maximum. : Unit = %d, Num = %lu\n",
				unit, num ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
	if (num > C_IPCU_MB_MAX) {
		Ddim_Print(( "dd_ipcu_mb_get_mb_stat_mb() - Mailbox number exceeds the maximum. : Unit = %d, Num = %lu\n",
				unit, num ));
		return C_IPCU_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	if (unit == 0) {
		*mb_stat = (1 & (ioIpcu0.mbstat.word >> (num)));
	} else {
		*mb_stat = (1 & (ioIpcu1.mbstat.word >> (num)));
	}

	return D_DDIM_OK;
}

DdIpcu* dd_ipcu_new(void)
{
	DdIpcu* self = k_object_new_with_private(DD_TYPE_IPCU, sizeof(DdIpcuPrivate));

	return self;
}

