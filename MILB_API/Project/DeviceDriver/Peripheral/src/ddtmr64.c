/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :peripheral 64 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "peripheral.h"
#include "dd_hdmac1.h"
#include "dd_arm.h"

#include "ddtmr64.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdTmr64, dd_tmr64);
#define DD_TMR64_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdTmr64Private, DD_TYPE_TMR64))

struct _DdTmr64Private
{
    kint a;
};

static void dd_tmr64_constructor(DdTmr64 *self)
{
	DdTmr64Private *priv = DD_TMR64_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_tmr64_destructor(DdTmr64 *self)
{

}

/*
 * @brief  The 64bit Timer is exclusively controlled.
 * @param  kint32 timeOut
 * @return kint32 D_DDIM_OK/DdTmr64_D_DD_TMR64_SEM_NG/DdTmr64_INPUT_PARAM_ERR/DdTmr64_D_DD_TMR64_SEM_TIMEOUT
 */
kint32 dd_tmr64_open(DdTmr64* self, kint32 timeOut)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (timeOut < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("Dd_TMR64_Open: input param error. timeOut = %x\n", timeOut));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	if(D_DDIM_USER_SEM_WAIT_POL == timeOut) {
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(SID_DD_TMR64);
	}
	else{
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(SID_DD_TMR64, (DDIM_USER_TMO)timeOut);
	}

	if(D_DDIM_USER_E_OK != ercd) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdTmr64_SEM_TIMEOUT;
		}
		return DdTmr64_SEM_NG;
	}
	return D_DDIM_OK;

}

/*
 * @brief  The exclusive control of control it is released.
 * @return kuint32 D_DDIM_OK/DdTmr64_D_DD_TMR64_SEM_NG
 */
kint32 dd_tmr64_close(DdTmr64* self)
{
	DDIM_USER_ER	ercd;

	// sig_sem()
	ercd = DDIM_User_Sig_Sem(SID_DD_TMR64);

	if(D_DDIM_USER_E_OK != ercd) {
		return DdTmr64_SEM_NG;
	}
	return D_DDIM_OK;

}

/*
 * @brief  The operation condition of Timer is set.
 * @param  TDdTmr64Ctrl* tmr64Ctrl
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_ctrl(DdTmr64* self, TDdTmr64Ctrl const* const tmr64Ctrl)
{
#ifdef CO_PARAM_CHECK
	if (tmr64Ctrl == NULL) {
		Ddim_Assertion(("Dd_TMR64_Ctrl: input param error. [*tmr64Ctrl] NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif
	// It sets it to the register
	IO_PERI.TMR64.TMCSR64_1.word = tmr64Ctrl->csr1.word;
	IO_PERI.TMR64.TMCSR64_1.word &= 0xFFFFFFFC;
	IO_PERI.TMR64.TMCSR64_2.word = tmr64Ctrl->csr2.word;

	return D_DDIM_OK;
}

/*
 * @brief  All the register values of 64bit reload timer are acquired.
 * @param  TDdTmr64Ctrl* tmr64Ctrl
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_get_ctrl(DdTmr64* self, TDdTmr64Ctrl* const tmr64Ctrl)
{
#ifdef CO_PARAM_CHECK
	if (tmr64Ctrl == NULL) {
		Ddim_Assertion(("Dd_TMR64_Get_Ctrl: input param error. [*tmr64Ctrl] NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	// Register value acquisition
	tmr64Ctrl->csr1.word = IO_PERI.TMR64.TMCSR64_1.word;
	tmr64Ctrl->csr2.word = IO_PERI.TMR64.TMCSR64_2.word;

	return D_DDIM_OK;
}

/*
 * @brief  64bit Timer is started.
 * @param  kboolean timeStampEnable
 * @return kint32 D_DDIM_OK
 */
kint32 dd_tmr64_start(DdTmr64* self, kboolean timeStampEnable)
{
	if (timeStampEnable) {
		// TSEN=1
		IO_PERI.TMR64.TMCSR64_2.word |= 0x00010000;
	}
	else {
		// TSEN=0
		IO_PERI.TMR64.TMCSR64_2.word &= 0xFFFEFFFF;
	}

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	// CNTE=1,TRG=1
	IO_PERI.TMR64.TMCSR64_1.word |= 0x00000003;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	// Z-EVAL - QA #4772
	// CNTE=1,TRG=1, bit4=1
	IO_PERI.TMR64.TMCSR64_1.word |= 0x00000013;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
 * @brief  64bit Timer is Stopped.
 * @return kint32 D_DDIM_OK
 */
kint32 dd_tmr64_stop(DdTmr64* self)
{
	// TSEN=0
	IO_PERI.TMR64.TMCSR64_2.word &= 0xFFFEFFFF;
	// CNTE=0,TRG=0
	IO_PERI.TMR64.TMCSR64_1.word &= 0xFFFFFFFC;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
 * @brief  Get 64bit Timer Gyro Time Stamp value.
 * @param  kulong* timeStamp
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_get_gyro_time_stamp(DdTmr64* self, kulong* const timeStamp)
{
#ifdef CO_PARAM_CHECK
	if (timeStamp == NULL) {
		Ddim_Assertion(("Dd_TMR64_Get_Gyro_TimeStamp: input param error. [*timeStamp] is NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	*timeStamp = IO_PERI.TMR64.GSTMP;

	return D_DDIM_OK;
}

/*
 * @brief  Get 64bit Timer Frame Start Time Stamp value.
 * @param  kuint32 sensorNo
 * @param  kuint32 lotationCount
 * @param  kulonglong* timeStamp
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_get_frame_start_time_stamp(DdTmr64* self, kuint32 sensorNo,
		kuint32 lotationCount, kulonglong* const timeStamp)
{
	kulong lCount = 0;
	kulong hCount = 0;

#ifdef CO_PARAM_CHECK
	if (sensorNo >= 4 || lotationCount >= 3) {
		Ddim_Assertion(("Dd_TMR64_Get_FrameStart_TimeStamp:"
				" input param error. sensorNo or lotationCount is Over\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
	else if (timeStamp == NULL) {
		Ddim_Assertion(("Dd_TMR64_Get_FrameStart_TimeStamp: input param error. [*timeStamp] is NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	if (sensorNo == 0) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FSSTMP00L;
				hCount = IO_PERI.TMR64.FSSTMP00H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FSSTMP01L;
				hCount = IO_PERI.TMR64.FSSTMP01H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FSSTMP02L;
				hCount = IO_PERI.TMR64.FSSTMP02H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameStart_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 1) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FSSTMP10L;
				hCount = IO_PERI.TMR64.FSSTMP10H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FSSTMP11L;
				hCount = IO_PERI.TMR64.FSSTMP11H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FSSTMP12L;
				hCount = IO_PERI.TMR64.FSSTMP12H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameStart_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 2) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FSSTMP20L;
				hCount = IO_PERI.TMR64.FSSTMP20H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FSSTMP21L;
				hCount = IO_PERI.TMR64.FSSTMP21H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FSSTMP22L;
				hCount = IO_PERI.TMR64.FSSTMP22H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameStart_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 3) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FSSTMP30L;
				hCount = IO_PERI.TMR64.FSSTMP30H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FSSTMP31L;
				hCount = IO_PERI.TMR64.FSSTMP31H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FSSTMP32L;
				hCount = IO_PERI.TMR64.FSSTMP32H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameStart_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else{
		Ddim_Print(("Dd_TMR64_Get_FrameStart_TimeStamp : sensorNo is over.\n"));
	}

	*timeStamp = ((kulonglong)hCount << 32) + lCount;

	return D_DDIM_OK;
}

/*
 * @brief  Get 64bit Timer Frame End Time Stamp  value.
 * @param  kuint32 sensorNo
 * @param  kuint32 lotationCount
 * @param  kulonglong* timeStamp
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_get_frame_end_time_stamp(DdTmr64* self, kuint32 sensorNo,
		kuint32 lotationCount, kulonglong* const timeStamp)
{
	kulong lCount = 0;
	kulong hCount = 0;

#ifdef CO_PARAM_CHECK
	if (sensorNo >= 4 || lotationCount >= 3) {
		Ddim_Assertion(("Dd_TMR64_Get_FrameEnd_TimeStamp: "
				"input param error. sensorNo or lotationCount is Over\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
	else if (timeStamp == NULL) {
		Ddim_Assertion(("Dd_TMR64_Get_FrameEnd_TimeStamp: input param error. [*timeStamp] is NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	if (sensorNo == 0) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FESTMP00L;
				hCount = IO_PERI.TMR64.FESTMP00H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FESTMP01L;
				hCount = IO_PERI.TMR64.FESTMP01H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FESTMP02L;
				hCount = IO_PERI.TMR64.FESTMP02H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameEnd_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 1) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FESTMP10L;
				hCount = IO_PERI.TMR64.FESTMP10H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FESTMP11L;
				hCount = IO_PERI.TMR64.FESTMP11H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FESTMP12L;
				hCount = IO_PERI.TMR64.FESTMP12H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameEnd_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 2) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FESTMP20L;
				hCount = IO_PERI.TMR64.FESTMP20H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FESTMP21L;
				hCount = IO_PERI.TMR64.FESTMP21H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FESTMP22L;
				hCount = IO_PERI.TMR64.FESTMP22H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameEnd_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else if (sensorNo == 3) {
		switch (lotationCount) {
			case 0:
				lCount = IO_PERI.TMR64.FESTMP30L;
				hCount = IO_PERI.TMR64.FESTMP30H;
				break;
			case 1:
				lCount = IO_PERI.TMR64.FESTMP31L;
				hCount = IO_PERI.TMR64.FESTMP31H;
				break;
			case 2:
				lCount = IO_PERI.TMR64.FESTMP32L;
				hCount = IO_PERI.TMR64.FESTMP32H;
				break;
			default:
				Ddim_Print(("Dd_TMR64_Get_FrameEnd_TimeStamp : lotationCount is over.\n"));
				break;
		}
	}
	else{
		Ddim_Print(("Dd_TMR64_Get_FrameEnd_TimeStamp : sensorNo is over.\n"));
	}

	*timeStamp = ((kulonglong)hCount << 32) + lCount;

	return D_DDIM_OK;
}

/*
 * @brief  Get 64bit Timer counter value.
 * @param  kulonglong* counter
 * @return kint32 D_DDIM_OK/DdTmr64_INPUT_PARAM_ERR
 */
kint32 dd_tmr64_get_counter(DdTmr64* self, kulonglong* const counter)
{
#ifdef CO_PARAM_CHECK
	if (counter == NULL) {
		Ddim_Assertion(("Dd_TMR64_Get_Counter: input param error. [*counter] is NULL\n"));
		return DdTmr64_INPUT_PARAM_ERR;
	}
#endif

	// Counter load trigger ON
	// CVT
	IO_PERI.TMR64.TMCSR64_2.word |= 0x00000001;

	// Get Counter
	*counter = ((kulonglong)IO_PERI.TMR64.TMR64_H << 32) + IO_PERI.TMR64.TMR64_L;

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief  Enable/Disable 64bit Time Stamp.
 * @param  kboolean timeStampEnable
 * @return kint32 D_DDIM_OK
 */
kint32 dd_tmr64_time_stamp_enable(DdTmr64* self, kboolean timeStampEnable)
{
	if (timeStampEnable) {
		// TSEN=1
		IO_PERI.TMR64.TMCSR64_2.word |= 0x00010000;
	}
	else {
		// TSEN=0
		IO_PERI.TMR64.TMCSR64_2.word &= 0xFFFEFFFF;
	}

	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

#endif

DdTmr64* dd_tmr64_get(void)
{
	DdTmr64 *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_TMR64, sizeof(DdTmr64Private));
	}

	return self;
}
