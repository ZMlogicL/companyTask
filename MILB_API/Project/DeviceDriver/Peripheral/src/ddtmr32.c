/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :peripheral 32 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "ddtmr32.h"
#include "peripheral.h"
#include "dd_top.h"
#include "dd_arm.h"

#include "ddtmr32.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdTmr32, dd_tmr32);
#define DD_TMR32_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdTmr32Private, DD_TYPE_TMR32))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//Dd_Top_Get_RCLK()[Hz] * 1[sec] / 32[div]
#define DdTmr32_1SEC_COUNT	            (1687500)

struct _DdTmr32Private
{
	// Soft-Counter : 1 - 0xFFFFFFFF
	volatile kulong		gDdTmr32SoftCounter[DdTmr32_CH_NUM_MAX];
	// Initial value of Soft-Counter : 1 - 0xFFFFFFFF
	volatile kulong		gDdTmr32SoftCounterIni[DdTmr32_CH_NUM_MAX];
	// Reload Flag : Reload = 1 / One-Shot = 0
	volatile kuchar	gDdTmr32SetReloadFlg[DdTmr32_CH_NUM_MAX];
	// Pointer of Callback Function
	volatile VP_CALLBACK	gDdTmr32Callback[DdTmr32_CH_NUM_MAX];
	// OUT Level
	volatile kuint32	gDdTmr32OutLevel;
};

/*
 * DECLS
 */
static kint32     ddTmr32CheckOverflow(DdTmr32* self, kulong param1, kulong param2, kulong margin);
static kint32     ddTmr32GetSoftCounter(DdTmr32* self, kulong clk, kulong time,
		                         kulong dividing, kulong* softCounter);

#if 0
static kuchar    ddTmr32CalDigit(DdTmr32* self, kulong value);
#endif

static void dd_tmr32_constructor(DdTmr32 *self)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
    priv->gDdTmr32OutLevel = 0;

    kint i;
    for(i = 0; i < DdTmr32_CH_NUM_MAX; i++){
    	priv->gDdTmr32SetReloadFlg[i] = 0;
    	priv->gDdTmr32SoftCounter[i] = 0;
    	priv->gDdTmr32SoftCounterIni[i] = 0;
    	priv->gDdTmr32Callback[i] = NULL;
    }
}

static void dd_tmr32_destructor(DdTmr32 *self)
{

}

/*
 * IMPL
 */
static kint32 ddTmr32CheckOverflow(DdTmr32* self, kulong param1, kulong param2, kulong margin)
{
	kint32 ret;
	kulonglong total;

	total = param1 * param2 / margin;

	if ((total & 0xFFFFFFFF00000000) == 0) {
		ret = 0;
	}
	else {
		ret = 1;
	}
	return ret;
}

static kint32 ddTmr32GetSoftCounter(DdTmr32* self, kulong clk, kulong time,
		kulong dividing, kulong* softCounter)
{
	kulong cnt;
	klonglong clockCount;

	cnt = *softCounter;

	clockCount = (klonglong)time * clk / dividing / 1000000;

	if(clockCount < 1){
		return -1;
	}
	else if(clockCount <= 0x100000000){
		return 0;
	}
	else{
		cnt = clockCount >> 32;
		if(clockCount & 0xFFFFFFFF){
			cnt += 1;
		}

		for(; ;) {

			if ((clk % cnt) == 0)  {
				break;
			}
			else{
				if (clk <= cnt) {
					*softCounter = 0;
					Ddim_Print(("ddTmr32GetSoftCounter: check overflow error.\n"));
					return -1;
				}
				cnt++;
			}
		}

		*softCounter = cnt;
	}
	return 0;
}

#if 0
static kuchar ddTmr32CalDigit(DdTmr32* self, kulong value)
{
	kulong digitValue;
	kint8  digitNum;
	kuchar digit = 0;

	for (digitNum = 31; digitNum >= 0; digitNum--) {
		digitValue = (1 << digitNum);
		if (value >= digitValue) {
			digit = (digitNum + 1);
			break;
		}
	}
	return digit;
}
#endif

/*
 * PUBLIC
 */
/*
 * @brief  The 32bit Reload Timer channel is exclusively controlled.
 * @param  kuchar ch
 * @param  kint32 timeOut
 * @return kint32 D_DDIM_OK/D_TIMER32_SEM_NG/DdTmr32_INPUT_PARAM_ERR/DdTmr32_D_DD_TMR32_SEM_TIMEOUT
 */
kint32 dd_tmr32_open(DdTmr32* self, kuint32 ch, kint32 timeOut)
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_Timer32_Open: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if (timeOut < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("Dd_Timer32_Open: input param error. timeOut = %x\n", timeOut));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	if(D_DDIM_USER_SEM_WAIT_POL == timeOut) {
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(SID_DD_TMR32(ch));
	}
	else{
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(SID_DD_TMR32(ch), (DDIM_USER_TMO)timeOut);
	}

	if(D_DDIM_USER_E_OK != ercd) {
		if(D_DDIM_USER_E_TMOUT == ercd) {
			return DdTmr32_SEM_TIMEOUT;
		}
		return DdTmr32_SEM_NG;
	}
	return D_DDIM_OK;

}

/*
 * @brief  The exclusive control of control Channel it is released.
 * @param  kuint32 ch
 * @return kuint32 D_DDIM_OK/DdTmr32_D_DD_TMR32_SEM_NG/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_close(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Close: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	// Global variable is clear
	priv->gDdTmr32SoftCounter[ch] = 0;
	priv->gDdTmr32SoftCounterIni[ch] = 0;
	priv->gDdTmr32SetReloadFlg[ch] = 0;
	priv->gDdTmr32Callback[ch] = NULL;

	// sig_sem()
	ercd = DDIM_User_Sig_Sem(SID_DD_TMR32(ch));

	if(D_DDIM_USER_E_OK != ercd) {
		return DdTmr32_SEM_NG;
	}
	return D_DDIM_OK;
}

/*
 * @brief  The operation condition of Reload Timer (Channel) is set.
 * @param  kuchar ch, TDdTmr32Ctrl* tmr32Ctrl
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_ctrl(DdTmr32* self, kuint32 ch , TDdTmr32Ctrl const* const tmr32Ctrl)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_Timer32_Ctrl: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if (tmr32Ctrl == NULL) {
		Ddim_Assertion(("Dd_Timer32_Ctrl: input param error. [*tmr32Ctrl] NULL\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	// It sets it to the register
	IO_PERI.TMR[ch].TMCSR.word = tmr32Ctrl->csr.word;
	IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFF8;
	IO_PERI.TMR[ch].TMRLR0 = tmr32Ctrl->rlr1;
	IO_PERI.TMR[ch].TMRLR1 = tmr32Ctrl->rlr2;

	// The reload counter is set
	priv->gDdTmr32SoftCounter[ch] = tmr32Ctrl->softCounter;
	priv->gDdTmr32SoftCounterIni[ch] = tmr32Ctrl->softCounter;

	// Reload check
	if (tmr32Ctrl->csr.bit.reld == 1) {
		// Reload
		priv->gDdTmr32SetReloadFlg[ch] = 1;
	}
	else {
		// One shot
		priv->gDdTmr32SetReloadFlg[ch] = 0;
	}

	// The callback function is registered
	priv->gDdTmr32Callback[ch] = tmr32Ctrl->pCallback;

	return D_DDIM_OK;
}

/*
 * @brief  Hard Counter, Soft Counter, and other parameters are calculated according
 *          to the designated time (usec).
 *           If it doesn't calculate, Input Parameter Error is returned.
 * @param  kulong usec, TDdTmr32Ctrl* tmr32Ctrl, kulong softCounter
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_calculate(DdTmr32* self, kulong usec, TDdTmr32Ctrl* const tmr32Ctrl)
{
	kulong  totalCount;
	kulong  dividing[3];
	kulonglong  countBase, countBaseWk;
	kulong  periClk, periClkWk;
	kulong  softCounter = 1;
	kulong  softCnt;
	kulong  dividingWk1, dividingWk2, dividingWk3;
	kulong  periCnt1 = 0;
	kulong  periCnt2 = 0;
	kulong  periCnt3 = 0;
	kulong  margin1, margin2, margin3;
//	kulong  repeatBase;
//	kulong  repeat;
	kint32  ret;
	kint8   divWk;
	kuchar  findFlag = 0;

	dividing[0] = 2;
	dividing[1] = 8;
	dividing[2] = 32;

#ifdef CO_PARAM_CHECK
	if (usec == 0) {
		Ddim_Assertion(("dd_tmr32_calculate: input param error. [usec] = 0\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if (tmr32Ctrl == NULL) {
		Ddim_Assertion(("dd_tmr32_calculate: input param error. [*tmr32Ctrl] NULL\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	periClk = Dd_Top_Get_RCLK();

	// Number of total counts(Overflow is a disregarded number of counts)
	countBase = (kulonglong)periClk * usec;

	periClkWk = periClk;
	countBaseWk = countBase;

	for (divWk = 2; divWk >= 0; divWk--) {
		countBase = (kulonglong)(periClk / 1000000) * usec;
		if ((countBase / dividing[divWk]) < 1) {
			continue;
		}
		if ((countBase % dividing[divWk]) != 0) {
			continue;
		}
		for (;;) {
			if ((countBaseWk & (dividing[divWk] - 1)) == 0) {
				softCnt = softCounter;

				// Check overflow
				ret = ddTmr32GetSoftCounter(self, periClkWk, usec, dividing[divWk], &softCounter);
				if (ret == 0) {
					if (softCnt == softCounter) {
						findFlag = 1;
						break;
					}
					periClkWk = periClk / softCounter;
					countBaseWk = (kulonglong)periClkWk * usec;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		if (findFlag == 1) {
			if ((periClk % softCounter) != 0) {
				Ddim_Print(("dd_tmr32_calculate:It cannot be divided.\n"));
			}
			break;
		}
	}
	while (1) {
		if (findFlag == 1) {
			for (dividingWk1 = dividing[divWk]; dividingWk1 >= 1; dividingWk1 /= 2) {
				if ((periClkWk % dividingWk1) == 0) {
					periCnt1 = (periClkWk / dividingWk1);
					break;
				}
			}
			dividingWk2 = dividing[divWk] / dividingWk1;
			dividingWk3 = dividingWk2;

			for (; dividingWk2 >= 1; dividingWk2 /= 2) {
				if ((usec % dividingWk2) == 0) {
					periCnt2 = (usec / dividingWk2);
					break;
				}
			}
			dividingWk3 = (dividing[divWk] / dividingWk1) / dividingWk2;

			for (margin1 = 1000000; margin1 > 0; margin1 /= 10) {
				if ((periCnt1 % margin1) == 0) {
					periCnt1 = (periCnt1 / margin1);
					break;
				}
			}
			// Division in multiples of 10
			if ((1000000 / margin1) > 1) {
				for (margin2 = (1000000 / margin1); margin2 > 0; margin2 /= 10) {
					if ((periCnt2 % margin2) == 0) {
						periCnt2 = (periCnt2 / margin2);
						break;
					}
				}
				margin3 = (1000000 / margin1) / margin2;
				periCnt3 = margin3;
			}
			else {
				margin2 = 1;
				margin3 = 1;
				periCnt3 = margin3;
			}
			// Check overflow
			ret = ddTmr32CheckOverflow(self, periCnt1, periCnt2, margin3);
			if (ret != 0) {
				// Division in multiples of 2
				switch (margin3) {
					case 1000000:
						margin1 = 64;
						margin2 = 64;
						break;
					case 100000:
						margin1 = 32;
						margin2 = 32;
						break;
					case 10000:
						margin1 = 16;
						margin2 = 16;
						break;
					case 1000:
						margin1 = 8;
						margin2 = 8;
						break;
					case 100:
						margin1 = 4;
						margin2 = 4;
						break;
					case 10:
						margin1 = 2;
						margin2 = 2;
						break;
					default:
						findFlag = 0;
						Ddim_Print(("dd_tmr32_calculate:It was not possible to "
								"request it though it calculated.\n"));
						break;
				}
				for (; margin1 > 0; margin1 /= 2) {
					if ((periCnt1 % margin1) == 0) {
						periCnt1 = (periCnt1 / margin1);
						break;
					}
				}
				if ((margin3 / margin1) > 1) {
					for (margin2 = (margin2 / margin1); margin2 > 0; margin2 /= 2) {
						if ((periCnt2 % margin2) == 0) {
							periCnt2 = (periCnt2 / margin2);
							break;
						}
					}
					margin3 = (margin3 / margin1) / margin2;
					periCnt3 = margin3;
				}
				else {
					margin2 = 1;
					margin3 = 1;
					periCnt3 = margin3;
				}
				ret = ddTmr32CheckOverflow(self, periCnt1, periCnt2, margin3);
				if (ret != 0) {
					findFlag = 0;
					Ddim_Print(("dd_tmr32_calculate:It was not possible to "
							"request it though it calculated.\n"));
					break;
				}
			}
			totalCount = (((kulonglong)periCnt1 * periCnt2) / dividingWk3) / periCnt3;

			// 32bit counter
			tmr32Ctrl->rlr1 = totalCount - 1;
			tmr32Ctrl->rlr2 = totalCount - 1;
			tmr32Ctrl->softCounter = softCounter;
			// Periodic mode, Interrupt Enable, Reload
			tmr32Ctrl->csr.word = 0x00000018;
			tmr32Ctrl->csr.bit.csl = divWk;
		}
		break;
	}
	if (findFlag == 1) {
		return D_DDIM_OK;
	}
	else {
		return DdTmr32_INPUT_PARAM_ERR;
	}
}

/*
 * @brief  If it doesn't calculate, Input Parameter Error is returned.
 * @param  kuint32 pwmCh, kuchar mode, TDdTmr32Ctrl* tmr32Ctrl
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_calculate_pwm_sync(DdTmr32* self, kuint32 pwmCh,
		kuchar mode, TDdTmr32Ctrl* const tmr32Ctrl)
{
	kulong  totalCount;
	kulong  softCounter = 0;
	kint8   divWk;

#ifdef CO_PARAM_CHECK
	if ((pwmCh != 4)&&(pwmCh != 8)) {
		Ddim_Assertion(("dd_tmr32_calculate_pwm_sync: input param error. [ch] = %d\n", pwmCh));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if (tmr32Ctrl == NULL) {
		Ddim_Assertion(("dd_tmr32_calculate: input param error. [*tmr32Ctrl] NULL\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if ((mode != 0)&&(mode != 1)) {
		Ddim_Assertion(("dd_tmr32_calculate_pwm_sync: input param error. [mode] = %d\n", mode));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	// pwm			reload
	// 0 : φ		φ/2
	// 1 : φ/4		φ/8
	// 2 : φ/16	φ/32
	// 3 : φ/64
	// 60fps
	if(mode==0){
		switch(IO_PERI.PWM[pwmCh>>2].PCNE.bit.__CKS){
			case 0:
				divWk = 0;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + IO_PERI.PWM[pwmCh>>2].PCSRE2 + 2) >> 1;
				break;
			case 1:
				divWk = 1;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + IO_PERI.PWM[pwmCh>>2].PCSRE2 + 2) >> 1;
				break;
			case 2:
				divWk = 2;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + IO_PERI.PWM[pwmCh>>2].PCSRE2 + 2) >> 1;
				break;
			case 3:
				divWk = 2;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + IO_PERI.PWM[pwmCh>>2].PCSRE2 + 2) << 1;
				break;
			default:
				break;
		}
	}
	// 240fps
	else if(mode==1){
		switch(IO_PERI.PWM[pwmCh>>2].PCNE.bit.__CKS){
			case 0:
				divWk = 0;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + 1) >> 2;
				break;
			case 1:
				divWk = 1;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + 1) >> 2;
				break;
			case 2:
				divWk = 2;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + 1) >> 2;
				break;
			case 3:
				divWk = 2;
				totalCount = (IO_PERI.PWM[pwmCh>>2].PCSRE1 + 1) >> 1;
				break;
			default:
				break;
		}
	}
	else{
		; //nothing
	}

	// 32bit counter
	tmr32Ctrl->rlr1 = totalCount - 1;
	tmr32Ctrl->rlr2 = totalCount - 1;
	tmr32Ctrl->softCounter = softCounter;
	// Periodic mode, Interrupt Enable, Reload
	tmr32Ctrl->csr.word	 = 0x00000018;
	tmr32Ctrl->csr.bit.csl = divWk;

	return D_DDIM_OK;
}

/*
 * @brief  32bit Reload Timer(Channel) is started.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_start(DdTmr32* self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Start: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	IO_PERI.TMR[ch].TMCSR.word |= 0x0000000B;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
 * @brief  32bit Reload Timer(Channel) wait for external trigger.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_external_start(DdTmr32* self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_EXT_TRG_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_External_Start: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	IO_PERI.TMR[ch].TMCSR.word |= 0x0000000A;

	return D_DDIM_OK;
}

/*
 * @brief  32bit Reload Timer(Channel) is Stopped.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_stop(DdTmr32* self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Stop: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	// UF=0,CNTE=0,CNTE=0
	IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFB8;

	// If the interrupt request flag set timing and the clear
	// timing clash, the flag set has priority and the clearing
	// operation is disabled.
	IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFB8;
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
 * @brief  32bit Reload Timer(Channel) is paused.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_pause(DdTmr32* self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Pause: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFBD;
	Dd_ARM_Dsb_Pou();
	return D_DDIM_OK;
}

/*
 * @brief  Get designated 32bit Reload Timer counter value.
 * @param  kuint32 ch, kulong* hCount, kulong* sCount
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_get_counter(DdTmr32* self, kuint32 ch, kulong* const hCount, kulong* const sCount)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Get_Counter: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if ((hCount == NULL) || (sCount == NULL)) {
		Ddim_Assertion(("Dd_TMR32_Get_Counter: input param error. [*hCount] or [*sCount] is NULL\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	*hCount = IO_PERI.TMR[ch].TMR;
	*sCount = priv->gDdTmr32SoftCounter[ch];

	return D_DDIM_OK;
}

/*
 * @brief  All the register values of 32bit reload timer are acquired.
 * @param  kuint32 ch, TDdTmr32Ctrl* tmr32Ctrl
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_get_ctrl(DdTmr32* self, kuint32 ch, TDdTmr32Ctrl* const tmr32Ctrl)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Get_Ctrl: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
	if (tmr32Ctrl == NULL) {
		Ddim_Assertion(("Dd_TMR32_Get_Ctrl: input param error. [*tmr32Ctrl] NULL\n"));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	// Register value acquisition
	tmr32Ctrl->csr.word = IO_PERI.TMR[ch].TMCSR.word;
	tmr32Ctrl->softCounter = priv->gDdTmr32SoftCounter[ch];
	tmr32Ctrl->pCallback = priv->gDdTmr32Callback[ch];

	return D_DDIM_OK;
}

/*
 * @brief  Only the soft count value that wants to repeat in the reload mode is set.
 * @param  kuint32 ch, kulong softCounter
 * @return void
 */
kint32 dd_tmr32_set_soft_counter_value(DdTmr32* self, kuint32 ch, kulong softCounter)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Set_Softcounter: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	priv->gDdTmr32SoftCounter[ch] = softCounter;
	return D_DDIM_OK;
}

/*
 * @brief  The soft count value is returned.
 * @param  kuint32 ch, kulong softCounter
 * @return kulong soft counter
 */
kulong dd_tmr32_get_soft_counter_vlaue(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("dd_tmr32_set_reload_flg_value: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif

	return priv->gDdTmr32SoftCounter[ch];
}

/*
 * @brief  The reload_flg is set.
 * @param  kuint32 ch, kuchar softCounter
 * @return kint32 D_DDIM_OK / DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_set_reload_flg_value(DdTmr32* self, kuint32 ch, kuchar flg)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("dd_tmr32_set_reload_flg_value: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	priv->gDdTmr32SetReloadFlg[ch] = flg;

	return D_DDIM_OK;
}

/*
 * @brief  The reload_flg value is returned.
 * @param  kuint32 ch, kulong softCounter
 * @return void
 */
kint32 dd_tmr32_get_reload_flg_value(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_Get_Reload_Flg: input param error. [ch] = %x\n", ch));
		return 0;
	}
#endif
	return priv->gDdTmr32SetReloadFlg[ch];
}

#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief  The operation condition of Reload Timer (Channel) is set.
 *          Timer value unit:[ms]
 * @param  kuint32 ch, kulong usec, kulong softCounter, VP_CALLBACK pCallback
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_set_timer(DdTmr32* self, kuint32 ch, kulong usec, VP_CALLBACK pCallback)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	kint32 result;
	TDdTmr32Ctrl tmr32Ctrl;

#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_SetTimer: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	// A reload counter and the final, set value are cleared
	priv->gDdTmr32SoftCounter[ch] = 0;
	priv->gDdTmr32SoftCounterIni[ch] = 0;

	// The register count value and the number of repetitions are requested.
	result = dd_tmr32_calculate(self, usec, &tmr32Ctrl);
	if (result != D_DDIM_OK) {
		Ddim_Print(("Dd_TMR32_SetTimer: Calculate error. ret=0x%x\n", result));
		return result;
	}
	tmr32Ctrl.pCallback = pCallback;

	if(ch == 3) {
		//OUTL resetting
		tmr32Ctrl.csr.bit.outl = priv->gDdTmr32OutLevel;
	}
	result = dd_tmr32_ctrl(self, ch, &tmr32Ctrl);
	if (result != D_DDIM_OK) {
		Ddim_Print(("Dd_TMR32_SetTimer: ctrl error. ret=0x%x\n", result));
	}
	return result;
}

/*
 * @brief  The operation condition of Reload Timer (Channel) is set.
 *           Timer value unit:[ms]
 * @param  kuint32 reloadCh, kuint32 pwmCh,  kuchar mode, VP_CALLBACK pCallback
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_set_timer_pwm(DdTmr32* self, kuint32 reloadCh, kuint32 pwmCh,
		kuchar mode, VP_CALLBACK pCallback)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	kint32 result;
	TDdTmr32Ctrl tmr32Ctrl;

#ifdef CO_PARAM_CHECK
	if (reloadCh >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_SetTimer: input param error. [ch] = %x\n", reloadCh));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	// A reload counter and the final, set value are cleared
	priv->gDdTmr32SoftCounter[reloadCh] = 0;
	priv->gDdTmr32SoftCounterIni[reloadCh] = 0;

	// The register count value and the number of repetitions are requested.
	result = dd_tmr32_calculate_pwm_sync(self, pwmCh, mode, &tmr32Ctrl);
	if (result != D_DDIM_OK) {
		Ddim_Print(("Dd_TMR32_SetTimer: dd_tmr32_calculate_pwm_sync error. ret=0x%x\n", result));
		return result;
	}
	tmr32Ctrl.pCallback = pCallback;

	result = dd_tmr32_ctrl(self, reloadCh, &tmr32Ctrl);
	if (result != D_DDIM_OK) {
		Ddim_Print(("Dd_TMR32_SetTimer: ctrl error. ret=0x%x\n", result));
	}
	return result;
}

/*
 * @brief  32bit Reload Timer(Channel) is started for reload.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_start_reload(DdTmr32* self, kuint32 ch)
{
	kint32 result = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_StartReload: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	// Reload
	dd_tmr32_set_reload_flg_value(self, ch, 1);

	IO_PERI.TMR[ch].TMCSR.word |= 0x0000001B;
	Dd_ARM_Dsb_Pou();

	return result;
}

/*
 * @brief  Designated Channel of 32bit Reload Timer is started for oneshot.
 * @param  kuint32 ch
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_start_one_shot(DdTmr32* self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdTmr32_CH_NUM_MAX) {
		Ddim_Assertion(("Dd_TMR32_StartOneshot: input param error. [ch] = %x\n", ch));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif
	// One shot
	dd_tmr32_set_reload_flg_value(self, ch, 0);

	// Reload check
	if (dd_tmr32_get_soft_counter_vlaue(self, ch) >= 2) {
		IO_PERI.TMR[ch].TMCSR.word |= 0x0000001B;
	}
	else {
		// RELD bit clear
		IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFEF;
		IO_PERI.TMR[ch].TMCSR.word |= 0x0000000B;
	}
	Dd_ARM_Dsb_Pou();

	return D_DDIM_OK;
}

/*
 * @brief  The outLevel(OUTL) is set.
 * @param  kuint32 outLevel
 * @return kint32 D_DDIM_OK/DdTmr32_INPUT_PARAM_ERR
 */
kint32 dd_tmr32_set_out_level(DdTmr32* self, kuint32 outLevel)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (outLevel >= 2) {
		Ddim_Assertion(("Dd_TMR32_Set_Outlevel: input param error. [outLevel] = %x\n", outLevel));
		return DdTmr32_INPUT_PARAM_ERR;
	}
#endif

	if (outLevel == 0) {
		// OUTL bit clear
		IO_PERI.TMR[3].TMCSR.word &= 0xFFFFFFDF;
	}
	else {
		// OUTL bit set
		IO_PERI.TMR[3].TMCSR.word |= 0x00000020;
	}
	priv->gDdTmr32OutLevel = outLevel;

	return D_DDIM_OK;
}
#endif

kulong dd_tmr32_get_soft_counter(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	return priv->gDdTmr32SoftCounter[ch];
}

kulong dd_tmr32_get_soft_counter_ini(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	return priv->gDdTmr32SoftCounterIni[ch];
}

kuchar dd_tmr32_get_reload_flg(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	return priv->gDdTmr32SetReloadFlg[ch];
}

VP_CALLBACK dd_tmr32_get_callback(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	return priv->gDdTmr32Callback[ch];
}

void dd_tmr32_set_soft_counter_reduce(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	priv->gDdTmr32SoftCounter[ch]--;
}

void dd_tmr32_set_soft_counter(DdTmr32* self, kuint32 ch)
{
	DdTmr32Private *priv = DD_TMR32_GET_PRIVATE(self);
	priv->gDdTmr32SoftCounter[ch] = priv->gDdTmr32SoftCounterIni[ch];
}

DdTmr32* dd_tmr32_get(void)
{
	DdTmr32 *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_TMR32, sizeof(DdTmr32Private));
	}

	return self;
}
