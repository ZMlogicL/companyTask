/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :徐廷军
*@brief               :sns 索喜rtos
*@redd                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include <string.h>
#include "ddrelc.h"
#include "_relc.h"
#include "ddarm.h"
#include "ddexs.h"
#include "ddgpv.h"
#include "ddimusercustom.h"
#include "driver_common.h"
#include "ddrelccommon.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdRelcCommon, dd_relc_common);
#define DD_RELC_COMMON_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdRelcCommonPrivate, DD_TYPE_RELC_COMMON))


struct _DdRelcCommonPrivate
{
	kint a;
};

/*----------------------------------------------------------------------	*/
/* Enumeration																*/
/*----------------------------------------------------------------------	*/
/* Nothing Special */

/*----------------------------------------------------------------------	*/
/* Structure																		*/
/*----------------------------------------------------------------------	*/
/* Nothing Special */

/*----------------------------------------------------------------------	*/
/* Global Data																*/
/*----------------------------------------------------------------------	*/
static volatile TDdRelcDecInfo S_GRELC_DEC_INFO;
/**
 *IMPL
 */
static void dd_relc_common_constructor(DdRelcCommon *self)
{
//	DdRelcCommonPrivate *priv = DD_RELC_COMMON_GET_PRIVATE(self);
}

static void dd_relc_common_destructor(DdRelcCommon *self)
{
//	DdRelcCommonPrivate *priv = DD_RELC_COMMON_GET_PRIVATE(self);
}

/**
 * PUBLIC
 */
/**
 * @preif	RELC decode status is get.
 * @return	RELC decode status
 */
kint32 dd_relc_get_status(DdRelc*self)
{
	kint32 ret;

	/* 000b = IDLE, 001b = RUN, 010b = SLEEP, 100b = FINISH  */
	ret = (ioRelc.relcStatus.word & 0x00000007);

	return ret;
}

/**
 * @preif	RELC sleep reason is get.
 * @return	RELC sleep reason
 */
kint32 dd_relc_get_sleep_reason(DdRelc*self)
{
	kint32 ret;

	/* 100b = User instruction,*/
	/* 001b = To reach the end address input,	*/
	/* 010b = To reach the end address output	*/
	ret = ioRelc.relcStatus.bit.sres;
	return ret;
}

/**
 * @preif	RELC error status is get.
 * @return	RELC error status
 */
kint32 dd_relc_get_error_status(DdRelc*self )
{
	kint32 ret;

	ret = ioRelc.relcStatus.bit.eflg;

	return ret;
}

/**
 * @preif	RELC error number is get.
 * @return DdRelc_D_DD_RELC_OK							OK
 * @return D_DD_RELC_ERR_INPUT_DATA_x			Input data error
 * @return D_DD_RELC_ERR_BUS_INPUT				Bus error(input)
 * @return D_DD_RELC_ERR_BUS_OUTPUT				Bus error(output)
 * @return DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_INPUT	Address mismatch error(input)
 * @return DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_OUTPUT	Address mismatch error(output)
*/
kint32 dd_relc_get_error(DdRelc*self)
{
	kint32 ret;

	ret = (ioRelc.relcErrorNum.word & 0x0000ffff);

	return ret;
}

/**
 * @preif	RELC status is get.
 * @param[out] decInfo	RELC processing status
 */
kint32 dd_relc_get_process_status(DdRelc*self, TDdRelcDecInfo* decInfo )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (decInfo == NULL) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*decInfo] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

#if 0
	/* Number of bytes read*/
	decInfo->readByte = (kushort)ioRelc.RELC_READ_BYTE.bit.DRNM;
	/* Number of bytes written*/
	decInfo->writeByte = (kushort)ioRelc.RELC_WRITE_BYTE.bit.DWNM;
	/* Number of processing blocks*/
	decInfo->procBlock = (kushort)ioRelc.RELC_BLOCK.bit.BLKN;
	/* Decode the total number of bytes to read*/
	decInfo->decTotalReadBytes = ioRelc.RELC_INPUT_BYTE;
	/* Decode the total number of bytes to write	*/
	decInfo->decTotalWriteBytes = ioRelc.RELC_OUTPUT_BYTE;
	/* Sequential run counter	*/
	decInfo->seqCnt = ioRelc.RELC_SEQ_CNT;
#else
	/* Number of bytes read */
	decInfo->readByte = S_GRELC_DEC_INFO.readByte;
	/* Number of bytes written	*/
	decInfo->writeByte = S_GRELC_DEC_INFO.writeByte;
	/* Number of processing blocks	*/
	decInfo->procBlock = S_GRELC_DEC_INFO.procBlock;
	/* Decode the total number of bytes to read	*/
	decInfo->decTotalReadBytes = S_GRELC_DEC_INFO.decTotalReadBytes;
	/* Decode the total number of bytes to write	*/
	decInfo->decTotalWriteBytes = S_GRELC_DEC_INFO.decTotalWriteBytes;
	/* Sequential run counter	*/
	decInfo->seqCnt = S_GRELC_DEC_INFO.seqCnt;
#endif
	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preifThe input and reference data buffer size for RELC is get.
 * @param[out] inBufSize			input buffer size
 * @param[out] refBufSize			reference buffer size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_get_buf_size(DdRelc*self, kushort* inBufSize, kushort* refBufSize )
{
	kuint32 bufSizeType;

#ifdef DriverCommon_CO_PARAM_CHECK
	if (inBufSize == NULL) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inBufSize] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
	if (refBufSize == NULL) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*refBufSize] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	bufSizeType = ioRelc.relcBufSize.bit.ibfs;

	switch (bufSizeType) {
		case 2:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_64;
			break;
		case 3:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_128;
			break;
		case 4:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_256;
			break;
		case 5:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_512;
			break;
		case 6:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_1024;
			break;
		case 7:
			*inBufSize = DdRelc_D_DD_RELC_IN_BUF_2048;
			break;
		default:
			*inBufSize = 0;
	}

	bufSizeType = ioRelc.relcBufSize.bit.rbfs;

	if (bufSizeType == 0) {
		*refBufSize = DdRelc_D_DD_RELC_REF_NO_BUF;
	}
	else {
		*refBufSize = DdRelc_D_DD_RELC_REF_BUF_8K;
	}

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Set the data to the input data buffer(mirror erea).
 * @param[in]	inDataAddr		input data address
 * @param[in]	inDataSize		input data size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_in_buf_data_mirror(DdRelc*self, kulong inDataAddr, kuint32 inDataSize )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (inDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) &ioRelc.relcInputBufDataMirror, (void*) inDataAddr, inDataSize);
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Get the data to the input data buffer(mirror erea).
 * @param[out]	inDataAddr			input data address
 * @param[out]	inDataSize			input data size
 * @return DdRelc_D_DD_RELC_OK					OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
kint32 dd_relc_get_in_buf_data_mirror(DdRelc*self, kulong outDataAddr, kuint32 outDataSize )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (outDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*outDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) outDataAddr, (void*) &ioRelc.relcInputBufDataMirror, outDataSize);

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Set the data to the input data buffer.
 * @param[in] inDataAddr			input data address
 * @param[in] inDataSize			input data size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
kint32 dd_relc_set_in_buf_data(DdRelc*self, kulong inDataAddr, kuint32 inDataSize )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (inDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) &ioRelc.relcInputBufData, (void*) inDataAddr, inDataSize);
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Get the data to the input data buffer.
 * @param[out]	inDataAddr		input data address
 * @param[out]	inDataSize		input data size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_get_in_buf_data(DdRelc*self, kulong outDataAddr, kuint32 outDataSize)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (outDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*outDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) outDataAddr, (void*) &ioRelc.relcInputBufData, outDataSize);

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Set the data to the reference data buffer.
 * @param[in]	outDataAddr		output data address
 * @param[in]	outDataSize		output data size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_ref_buf_data(DdRelc*self, kulong inDataAddr, kuint32 inDataSize )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (inDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) &ioRelc.relcRefBufData, (void*) inDataAddr, inDataSize);
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	Get the data to the reference data buffer.
 * @param[out]	outDataAddr		output data address
 * @param[out]	outDataSize		output data size
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_get_ref_buf_data(DdRelc*self, kulong outDataAddr, kuint32 outDataSize )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if (outDataAddr == 0) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*outDataAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	memcpy((void*) outDataAddr, (void*) &ioRelc.relcRefBufData, outDataSize);

	return DdRelc_D_DD_RELC_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/** @name Utility Functions
@{*/
/**
 * @preif	Set and Start RELC normal mode
 * @param[in] relcSetModNormal		RELC setting for normal mode
 * @return DdRelc_D_DD_RELC_OK					OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR				Parameter error
 */
kint32 dd_relc_utility_register(DdRelc*self, TDdRelcSetModNormal const* const relcSetModNormal )
{
	kint32 retCode = 0;
	TDdRelcCtrlCmn ctrlCmn;
	TDdRelcCtrlReg ctrl_reg;

	memset(&ctrlCmn, 0, sizeof(TDdRelcCtrlCmn));
	memset(&ctrl_reg, 0, sizeof(TDdRelcCtrlReg));

	ctrlCmn.writeHprot = relcSetModNormal->writeHprot;
	ctrlCmn.readHprot = relcSetModNormal->readHprot;

	/* After power on and the reset, this is executed only once. */
	dd_relc_new(ctrlCmn.writeHprot, ctrlCmn.readHprot);

	retCode = dd_relc_open();
	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error RELC Open !!\n" ));
		return retCode;
	}

	ctrlCmn.descMode = DdRelc_D_DD_RELC_RUN_MODE_NORMAL;
	ctrlCmn.callback = relcSetModNormal->callback;

	/* Continuous run mode */
	if ((relcSetModNormal->seqNum) > 1) {
		ctrlCmn.contRunMode = DdRelc_D_DD_RELC_CONT_MODE_CONT;
		ctrlCmn.seqNum = relcSetModNormal->seqNum;
		ctrl_reg.inEndAddrEn = DdRelc_D_DD_RELC_ADDR_DISABLE;
		ctrl_reg.outEndAddrEn = DdRelc_D_DD_RELC_ADDR_DISABLE;
		ctrl_reg.inAddrAutoInc = DdRelc_D_DD_RELC_ADDR_INCRE_ON;
		ctrl_reg.outAddrAutoInc = DdRelc_D_DD_RELC_ADDR_INCRE_ON;
	}
	/* Normal mode */
	else {
		ctrlCmn.contRunMode = DdRelc_D_DD_RELC_CONT_MODE_NORMAL;
		ctrlCmn.seqNum = 1;
		ctrl_reg.inEndAddrEn = DdRelc_D_DD_RELC_ADDR_DISABLE;
		ctrl_reg.outEndAddrEn = DdRelc_D_DD_RELC_ADDR_DISABLE;
		ctrl_reg.inAddrAutoInc = DdRelc_D_DD_RELC_ADDR_INCRE_OFF;
		ctrl_reg.outAddrAutoInc = DdRelc_D_DD_RELC_ADDR_INCRE_OFF;
	}

	ctrl_reg.inStartAddr = relcSetModNormal->inStartAddr;
	ctrl_reg.inEndAddr = 0;
	ctrl_reg.outStartAddr = relcSetModNormal->outStartAddr;
	ctrl_reg.outEndAddr = 0;

	retCode = dd_relc_ctrl_common(NULL, &ctrlCmn);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_ctrl_common() !!\n" ));
	}

	retCode = dd_relc_ctrl_register(NULL, &ctrl_reg);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_ctrl_register() !!\n" ));
	}

	retCode = dd_relc_start_sync(NULL);

	if (retCode != 0) {
		Ddim_Print(("dd_relc_start_sync() clr_flg error. retCode=0x%x\n", retCode));
	}

	retCode = dd_relc_close(NULL);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_close() !!\n" ));
	}

	return retCode;
}

/**
 * @preif	Set and Start RELC descriptor mode
 * @param[in] relcSetModDesc		RELC setting for descriptor mode
 * @retval DdRelc_D_DD_RELC_OK				OK
 * @retval DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
 */
kint32 dd_relc_utility_descriptor(DdRelc*self, TDdRelcSetModDesc const* const relcSetModDesc )
{
	kint32 retCode = 0;
	TDdRelcCtrlCmn ctrlCmn;
	TDdRelcCtrlDesc ctrlDesc;

	memset(&ctrlCmn, 0, sizeof(TDdRelcCtrlCmn));
	memset(&ctrlDesc, 0, sizeof(TDdRelcCtrlDesc));

	ctrlCmn.writeHprot = relcSetModDesc->writeHprot;
	ctrlCmn.readHprot = relcSetModDesc->readHprot;

	/* After power on and the reset, this is executed only once. */
	dd_relc_new(ctrlCmn.writeHprot, ctrlCmn.readHprot);

	retCode = dd_relc_open();

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error RELC Open !!\n" ));
		return retCode;
	}

	ctrlCmn.descMode = DdRelc_D_DD_RELC_RUN_MODE_DESC;
	ctrlCmn.callback = relcSetModDesc->callback;

	/* Continuous run mode */
	if (relcSetModDesc->seqNum > 1) {
		ctrlCmn.contRunMode = DdRelc_D_DD_RELC_CONT_MODE_CONT;
		ctrlCmn.seqNum = relcSetModDesc->seqNum;
	}
	/* Normal mode */
	else {
		ctrlCmn.contRunMode = DdRelc_D_DD_RELC_CONT_MODE_NORMAL;
		ctrlCmn.seqNum = 1;
	}

	ctrlDesc.descriptorAddr = relcSetModDesc->relcDescriptorAddr;

	retCode = dd_relc_ctrl_common(NULL, &ctrlCmn);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_ctrl_common() !!\n" ));
	}

	retCode = dd_relc_ctrl_descriptor(NULL, &ctrlDesc);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_ctrl_descriptor() !!\n" ));
	}

	retCode = dd_relc_start_sync(NULL);

	if (retCode != 0) {
		Ddim_Print(("dd_relc_start_sync() clr_flg error. retCode=0x%x\n", retCode));
	}

	retCode = dd_relc_close(NULL);

	if (retCode != DdRelc_D_DD_RELC_OK) {
		Ddim_Print(("Error dd_relc_close() !!\n" ));
	}

	return retCode;
}

#endif	/* CO_DDIM_UTILITY_USE */

DdRelcCommon* dd_relc_common_new(void)
{
	DdRelcCommon *self = k_object_new_with_private(DD_TYPE_RELC_COMMON	, sizeof(DdRelcCommonPrivate));
	return self;
}
