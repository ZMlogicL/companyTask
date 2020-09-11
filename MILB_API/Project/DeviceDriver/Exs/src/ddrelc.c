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
*1.0.0 2020年09月开始开发
*/

#include <string.h>
#include "_relc.h"
#include "ddarm.h"
#include "ddexs.h"
#include "ddgpv.h"
#include "ddimusercustom.h"
#include "driver_common.h"
#include "ddrelc.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdRelc, dd_relc);
#define DD_RELC_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdRelcPrivate, DD_TYPE_RELC))


struct _DdRelcPrivate
{
	kint a;
};


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
#endif	/* CO_DDIM_UTILITY_USE */

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
/**< Callback function pointer */
static VpCallback S_GRELC_CALLBACK = NULL;
static volatile TDdRelcDecInfo S_GRELC_DEC_INFO;
/**
 *IMPL
 */
static void dd_relc_constructor(DdRelc *self)
{
//	DdRelcPrivate *priv = DD_RELC_GET_PRIVATE(self);
}

static void dd_relc_destructor(DdRelc *self)
{
//	DdRelcPrivate *priv = DD_RELC_GET_PRIVATE(self);
}

/**
 * PUBLIC
 */
/*----------------------------------------------------------------------	*/
/* Local Method Definition											*/
/*----------------------------------------------------------------------	*/
/* Nothing Special */

/*----------------------------------------------------------------------	*/
/* Function																		*/
/*----------------------------------------------------------------------	*/
/**
 *RELC initialize.
 *@param[in] writeHprot			RELC data write side HPROT (default:0x0B)
 *@param[in] readHprot			RELC data read side HPROT (default:0x0B)
 *@remarks This function performs interrupt permission and soft reset.
 */
extern	void dd_relc_init(DdRelc*self, kuchar writeHprot, kuchar readHprot )
{
	dd_exs_set_ram_pd_ctrl_relc(NULL, 1);
	dd_exs_set_relc_soft_reset(NULL, 1);
	Dd_GPV_Set_ARC_Remap(DdGpv_REMAP_SD_RELC_HDMAC_USB2, 1);

#ifdef CO_ACT_CLOCK
	Dd_Exs_Set_RELC_BUS_CLOCK_Stop_Ctrl(0);
#endif //CO_ACT_CLOCK

	/* Set the RELC expanded data write side HPROT setting */
	Dd_Exs_Set_RELC_HPROT_Write(writeHprot);
	/* Set the RELC expanded data read side HPROT setting */
	Dd_Exs_Set_RELC_HPROT_Read(readHprot);

	/* SRST:soft reset on */
	ioRelc.relcReset.bit.srst = 0x00000001;
	Dd_ARM_Dsb_Pou();
	S_GRELC_CALLBACK = NULL;

	while (1) {
		if (ioRelc.relcReset.bit.srst == 0) {
			break;
		}
	}

	/* Interrupt permission */
	ioRelc.relcIntEn.word = 0x0000000F;
	Dd_ARM_Dsb_Pou();

	/* Number of bytes read*/
	S_GRELC_DEC_INFO.readByte = 0;
	/* Number of bytes written*/
	S_GRELC_DEC_INFO.writeByte = 0;
	/* Number of processing blocks*/
	S_GRELC_DEC_INFO.procBlock = 0;
	/* Decode the total number of bytes to read*/
	S_GRELC_DEC_INFO.decTotalReadBytes = 0;
	/* Decode the total number of bytes to write	*/
	S_GRELC_DEC_INFO.decTotalWriteBytes = 0;
	/* Sequential run counter	*/
	S_GRELC_DEC_INFO.seqCnt = 0;

#ifdef CO_ACT_CLOCK
	Dd_Exs_Set_RELC_BUS_CLOCK_Stop_Ctrl(1);
#endif //CO_ACT_CLOCK
}
/**
 * @brief  RELC is exclusively controlled.
 * @return DdRelc_D_DD_RELC_OK					OK
 * @return DdRelc_D_DD_RELC_EXT_LOCK_NG		Lock Error (System Using RELC)
*/
kint32 dd_relc_open(DdRelc*self)
{
	kint32 ret = DdRelc_D_DD_RELC_OK;

	if (DDIM_User_Twai_Sem(SID_DD_RELC, D_DDIM_USER_SEM_WAIT_POL) != D_DDIM_USER_E_OK) {
		ret = DdRelc_D_DD_RELC_EXT_LOCK_NG;
	}

	dd_exs_set_ram_pd_ctrl_relc(NULL, 0);

#ifdef CO_ACT_CLOCK
	Dd_Exs_Set_RELC_BUS_CLOCK_Stop_Ctrl(0);
#endif //CO_ACT_CLOCK

	return ret;
}


/**
 * @brief  RELC is exclusively closed.
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_EXT_LOCK_NG	Lock Error (System Using RELC
*/
kint32 dd_relc_close(DdRelc*self)
{
	kint32 ret = DdRelc_D_DD_RELC_OK;

	if (DDIM_User_Sig_Sem(SID_DD_RELC) != D_DDIM_USER_E_OK) {
		ret = DdRelc_D_DD_RELC_EXT_LOCK_NG;
	}

	dd_exs_set_ram_pd_ctrl_relc(NULL, 1);

#ifdef CO_ACT_CLOCK
	Dd_Exs_Set_RELC_BUS_CLOCK_Stop_Ctrl(1);
#endif //CO_ACT_CLOCK

	return ret;
}

/**
 * @brief  RELC decode is started.(Sync)
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_FLG_CLR_NG		Clear flag is NG
 * @return DdRelc_D_DD_RELC_TIMEOUT		twai_flg is time out
*/
kint32 dd_relc_start_sync(DdRelc*self)
{
	DdimUserCustom_FLGPTN flgptn;
	DdimUserCustom_FLGPTN waiptn;
	kint ercd = 0;

	waiptn = ( DdRelc_D_DD_RELC_INT_END_FLG | DdRelc_D_DD_RELC_INT_ERR_FLG | DdRelc_D_DD_RELC_INT_SLP_FLG );

	ercd = DDIM_User_Clr_Flg( FID_DD_RELC, ~waiptn );
	if( ercd != D_DDIM_USER_E_OK ) {
		Ddim_Print(("I:RELC_Start_Sync() clr_flg error\n"));
		return DdRelc_D_DD_RELC_FLG_CLR_NG;
	}

	/* RELC start */
	ioRelc.relcMode1.bit.prun = 0x00000001;
	Dd_ARM_Dsb_Pou();

	ercd = DDIM_User_Twai_Flg( FID_DD_RELC, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME );
	if ( ercd == D_DDIM_USER_E_TMOUT ) {
		Ddim_Print(("I:RELC_Start_Sync() RELC twai_flg timeout\n"));
		return DdRelc_D_DD_RELC_TIMEOUT;
	}

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @brief  RELC decode is started.(Async)
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_FLG_CLR_NG		Clear flag is NG
*/
kint32 dd_relc_start_async(DdRelc*self)
{
	DdimUserCustom_FLGPTN waiptn;
	kint ercd = 0;
	waiptn = (DdRelc_D_DD_RELC_INT_END_FLG | DdRelc_D_DD_RELC_INT_ERR_FLG | DdRelc_D_DD_RELC_INT_SLP_FLG );

	ercd = DDIM_User_Clr_Flg( FID_DD_RELC, ~waiptn );
	if(ercd != D_DDIM_USER_E_OK){
		Ddim_Print(("I:RELC_Start_ASync() clr_flg error\n"));
		return DdRelc_D_DD_RELC_FLG_CLR_NG;
	}

	/* RELC start */
	ioRelc.relcMode1.bit.prun = 0x00000001;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @brief  Wait for the completion of the RELC decode.
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_TIMEOUT		twai_flg is time out
*/
kint32 dd_relc_wait_end(DdRelc*self)
{
	DdimUserCustom_FLGPTN flgptn;
	DdimUserCustom_FLGPTN waiptn;
	kint ercd = 0;

	waiptn = ( DdRelc_D_DD_RELC_INT_END_FLG | DdRelc_D_DD_RELC_INT_ERR_FLG | DdRelc_D_DD_RELC_INT_SLP_FLG );

	ercd = DDIM_User_Twai_Flg( FID_DD_RELC, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME );
	if ( ercd == D_DDIM_USER_E_TMOUT ) {
		Ddim_Print(("I:RELC_Wait_End() twai_flg timeout\n"));
		return DdRelc_D_DD_RELC_TIMEOUT;
	}

	 /* Number of bytes read	*/
	S_GRELC_DEC_INFO.readByte = (kushort) ioRelc.relcReadByte.bit.drnm;
	/* Number of bytes written	*/
	S_GRELC_DEC_INFO.writeByte = (kushort) ioRelc.relcWriteByte.bit.dwnm;
	/* Number of processing blocks	*/
	S_GRELC_DEC_INFO.procBlock = (kushort) ioRelc.relcBlock.bit.blkn;
	/* Decode the total number of bytes to read	*/
	S_GRELC_DEC_INFO.decTotalReadBytes = ioRelc.relcInputByte;
	/* Decode the total number of bytes to write	*/
	S_GRELC_DEC_INFO.decTotalWriteBytes = ioRelc.relcOutputByte;
	/* Sequential run counter	*/
	S_GRELC_DEC_INFO.seqCnt = ioRelc.relcSeqCnt;

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @brief  RELC decode is stopped.(both Sync and Async)
*/
void dd_relc_stop(DdRelc*self)
{
	/* RELC stop */
	ioRelc.relcMode1.bit.prun	&= 0x00000000;
	Dd_ARM_Dsb_Pou();
}

/**
 * @brief  The common control setting for RELC is set.
 * @param[in] relcCtrlCmn			RELC common control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_ctrl_common(DdRelc*self, TDdRelcCtrlCmn const* const relcCtrlCmn )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlCmn == NULL ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlCmn] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	if ( relcCtrlCmn->descMode > 0 ) {
		ioRelc.relcMode1.word |= (relcCtrlCmn->descMode << 2);
	}

	/* Descriptor Mode	*/
	ioRelc.relcMode1.bit.dsmd = relcCtrlCmn->descMode;
	/* Continuous Run Mode	*/
	ioRelc.relcMode1.bit.crmd = relcCtrlCmn->contRunMode;
	/* Sequential Run Number of Times	*/
	ioRelc.relcSeqNum = relcCtrlCmn->seqNum;
	Dd_ARM_Dsb_Pou();
	/* Callback function pointer	*/
	S_GRELC_CALLBACK = relcCtrlCmn->callback;

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @brief  The register control setting for RELC is set.
 * @param[in] relcCtrlCmn			RELC register control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_ctrl_register(DdRelc*self, TDdRelcCtrlReg const* const relcCtrlReg )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlReg == NULL ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlReg] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Input End Address Enable	*/
	ioRelc.relcMode2.bit.imax = relcCtrlReg->inEndAddrEn;
	/* Output End Address Enable	*/
	ioRelc.relcMode2.bit.omax = relcCtrlReg->outEndAddrEn;
	/* Input Address Auto Increment	*/
	ioRelc.relcMode2.bit.iaai = relcCtrlReg->inAddrAutoInc;
	/* Output Address Auto Increment	*/
	ioRelc.relcMode2.bit.oaai = relcCtrlReg->outAddrAutoInc;

	/* Input start address		*/
	ioRelc.relcInStartAddr = relcCtrlReg->inStartAddr;
	/* Input end address	*/
	ioRelc.relcInEndAddr = relcCtrlReg->inEndAddr;
	/* Output start address	*/
	ioRelc.relcOutStartAddr = relcCtrlReg->outStartAddr;
	/* Output end address	*/
	ioRelc.relcOutEndAddr = relcCtrlReg->outEndAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @brief  The descriptor control setting for RELC is set.
 * @param[in] relcCtrlCmn			RELC descriptor control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_ctrl_descriptor(DdRelc*self, TDdRelcCtrlDesc const* const relcCtrlDesc )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlDesc == NULL ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlDesc] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* descriptor address */
	ioRelc.relcDescriptorAddr = relcCtrlDesc->descriptorAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The input start address for RELC is set.
 * @param[in] inStartAddr			Input start address
 * @return DdRelc_D_DD_RELC_OK				OK
 * @retval DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_in_start_addr(DdRelc*self, kulong inStartAddr )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( inStartAddr == 0 ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inStartAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Input start address */
	ioRelc.relcInStartAddr = inStartAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The input end address for RELC is set.
 * @param[in] inEndAddr			Input end address
 * @return DdRelc_D_DD_RELC_OK				OK
 * @retval DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_in_end_addr(DdRelc*self, kulong inEndAddr )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( inEndAddr == 0 ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*inEndAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Input end address */
	ioRelc.relcInEndAddr = inEndAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The output start address for RELC is set.
 * @param[in] outStartAddr		Output start address
 * @return DdRelc_D_DD_RELC_OK				OK
 * @retval DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_out_start_addr(DdRelc*self, kulong outStartAddr )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( outStartAddr == 0 ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*outStartAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Output start address */
	ioRelc.relcOutStartAddr = outStartAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The output end address for RELC is set.
 * @param[in] outEndAddr			Output end address
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_set_out_end_addr(DdRelc*self, kulong outEndAddr)
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( outEndAddr == 0 ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*outEndAddr] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Output end address */
	ioRelc.relcOutEndAddr = outEndAddr;
	Dd_ARM_Dsb_Pou();

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The common control setting for RELC is get.
 * @param[out] relcCtrlCmn		RELC common control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
kint32 dd_relc_get_ctrl_common(DdRelc*self, TDdRelcCtrlCmn* const relcCtrlCmn )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlCmn == NULL ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlCmn] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Descriptor Mode	*/
	relcCtrlCmn->descMode = (kuchar) ioRelc.relcMode1.bit.dsmd;
	/* Continuous Run Mode	*/
	relcCtrlCmn->contRunMode = (kuchar) ioRelc.relcMode1.bit.crmd;
	/* Sequential Run Number of Times	*/
	relcCtrlCmn->seqNum = ioRelc.relcSeqNum;
	/* Callback function pointer	*/
	relcCtrlCmn->callback = S_GRELC_CALLBACK;

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The register control setting for RELC is get.
 * @param[out] relcCtrlReg		RELC register control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_get_ctrl_register(DdRelc*self, TDdRelcCtrlReg* const relcCtrlReg )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlReg == NULL ) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlReg] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* Input End Address Enable	*/
	relcCtrlReg->inEndAddrEn = (kuchar) ioRelc.relcMode2.bit.imax;
	/* Output End Address Enable	*/
	relcCtrlReg->outEndAddrEn = (kuchar) ioRelc.relcMode2.bit.omax;
	/* Input Address Auto Increment	*/
	relcCtrlReg->inAddrAutoInc = (kuchar) ioRelc.relcMode2.bit.iaai;
	/* Output Address Auto Increment */
	relcCtrlReg->outAddrAutoInc = (kuchar) ioRelc.relcMode2.bit.oaai;

	/* Input start address	 */
	relcCtrlReg->inStartAddr = ioRelc.relcInStartAddr;
	/* Input end address	*/
	relcCtrlReg->inEndAddr = ioRelc.relcInEndAddr;
	/* Output start address	*/
	relcCtrlReg->outStartAddr = ioRelc.relcOutStartAddr;
	/* Output end address	*/
	relcCtrlReg->outEndAddr = ioRelc.relcOutEndAddr;

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	The descriptor control setting for RELC is get.
 * @param[out] relcCtrlDesc		RELC descriptor control parameter
 * @return DdRelc_D_DD_RELC_OK				OK
 * @return DdRelc_D_DD_RELC_PARAM_ERR		Parameter error
*/
kint32 dd_relc_get_ctrl_descriptor(DdRelc*self, TDdRelcCtrlDesc* const relcCtrlDesc )
{
#ifdef DriverCommon_CO_PARAM_CHECK
	if ( relcCtrlDesc == NULL) {
		DriverCommon_DDIM_ASSERTION(("RELC: input param error. [*relcCtrlDesc] NULL\n"));
		return DdRelc_D_DD_RELC_PARAM_ERR;
	}
#endif

	/* descriptor address */
	relcCtrlDesc->descriptorAddr = ioRelc.relcDescriptorAddr;

	return DdRelc_D_DD_RELC_OK;
}

/**
 * @preif	It is Interrupt Handler of RELC.
 *			The interruption flag is cleared, and the CallBack function is called.
 */
void dd_relc_int_handler(DdRelc*self)
{
	DdimUserCustom_FLGPTN waiptn;
	kuchar int_type = 0;
	DDIM_USER_ER ret = D_DDIM_USER_E_OK;

	waiptn = 0;

	/* ERROR INT */
	if ( ( ioRelc.relcIntEn.bit.eint == 1 ) && ( ioRelc.relcIntSt.bit.__eins == 1 ) ) {
		waiptn |= DdRelc_D_DD_RELC_INT_ERR_FLG;
		int_type = DdRelc_D_DD_RELC_ERR;
	}

	/* SLEEP INT */
	if ( ( ioRelc.relcIntEn.bit.sint == 1) && ( ioRelc.relcIntSt.bit.__sins == 1 ) ) {
		if ( int_type == 0 ) {
	 		waiptn |= DdRelc_D_DD_RELC_INT_SLP_FLG;
			int_type = DdRelc_D_DD_RELC_ERR;
		}
	}

	/* FINISH INT */
	if ( ( ioRelc.relcIntEn.bit.fint == 1 ) && ( ioRelc.relcIntSt.bit.__fins == 1 ) ) {
		if ( int_type == 0 ) {
	 		waiptn |= DdRelc_D_DD_RELC_INT_END_FLG;
 			int_type = DdRelc_D_DD_RELC_FINISH;
		}
	}

	/* CONTINUOUS RUN FINISH */
	if ( (ioRelc.relcIntEn.bit.cint == 1 ) && ( ioRelc.relcIntSt.bit.__cins == 1 ) ) {
		if ( int_type == 0 ) {
			waiptn |= DdRelc_D_DD_RELC_INT_END_FLG;
			int_type = DdRelc_D_DD_RELC_CR_FINISH;
		}
	}

	if ( int_type == DdRelc_D_DD_RELC_FINISH ) {
		if ( ioRelc.relcSeqNum == 1 ) {
			ret = DDIM_User_Set_Flg( FID_DD_RELC, waiptn );
			if ( ret != D_DDIM_USER_E_OK ) {
				Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
			}
		}
	}
	else {
		ret = DDIM_User_Set_Flg( FID_DD_RELC, waiptn );
		if ( ret != D_DDIM_USER_E_OK ) {
			Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
		}
	}

	if ( S_GRELC_CALLBACK ) {
		/* Call Back function */
		(*S_GRELC_CALLBACK)( int_type );
	}

	if ( int_type == DdRelc_D_DD_RELC_ERR ) {
		/* EINS */
		ioRelc.relcIntSt.word = 0x0000FFFB;
	}

	if ( int_type == DdRelc_D_DD_RELC_ERR ) {
		/* SINS */
		ioRelc.relcIntSt.word = 0x0000FFFE;
	}

	if ( int_type == DdRelc_D_DD_RELC_FINISH ) {
		/* FINS */
		ioRelc.relcIntSt.word = 0x0000FFFD;
	}

	if ( int_type == DdRelc_D_DD_RELC_CR_FINISH ) {
		/* CINS, FINS */
		ioRelc.relcIntSt.word = 0x0000FFF5;
	}

	Dd_ARM_Dsb_Pou();
}

DdRelc* 		dd_relc_new(kuchar writeHprot, kuchar readHprot)
{
	DdRelc *self = k_object_new_with_private(DD_TYPE_RELC	, sizeof(DdRelcPrivate));
	return self;
}
