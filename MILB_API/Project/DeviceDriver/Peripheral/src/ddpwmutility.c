/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :PWM driver(utility  section)
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

#include "dd_top.h"
#include "ddpwmutility.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdPwmUtility, dd_pwm_utility);
#define DD_PWM_UTILITY_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdPwmUtilityPrivate, DD_TYPE_PWM_UTILITY))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
#define D_DD_PWM_MAX_CYC			(8)
#endif	/* CO_DDIM_UTILITY_USE */

struct _DdPwmUtilityPrivate
{
    kint a;
};

static void dd_pwm_utility_constructor(DdPwmUtility *self)
{
	DdPwmUtilityPrivate *priv = DD_PWM_UTILITY_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_pwm_utility_destructor(DdPwmUtility *self)
{

}

/*
 * PUBLIC
 */
#ifdef CO_DDIM_UTILITY_USE
/*
 * @brief  Cycle parameters are calculated according
 *		   to the designated time (u sec).
 *		   If it doesn't calculate, Input Parameter Error is returned.
 * @param  kulong usec, kuchar* clk, kushort* cycle
 * @return kint32 D_DDIM_OK / DdPwmBranch_OVERFLOW_OK / DdPwmBranch_OVERFLOW_ERROR
 */
kint32 dd_pwm_utility_calculate(DdPwmUtility* self, kulong usec, kuchar* const clk, kushort* const cycle)
{
	kuint32 findFlag;
	kulong periClock;
	kulong totalCount;
	kulong totalCountWk;
	kulong divTmp;
	kuchar divWk, divWk2, divWk3;
	kulong countBase;
	kulong clockDiv, clockMargin;
	kulong usecByUsecDiv;
	kulong periClockByClockDiv;
	kulong usecDivWk, usecDiv, usecMargin;
	// clock	CKS	2^	divWk
	// 1		0	0	1
	// 4		1	2	2
	// 16		2	4	3
	// 64		3	6	4

#ifdef CO_PARAM_CHECK
	if (usec == 0) {
		Ddim_Assertion(("PWM input param error. [usec] = %ld\n", usec));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (clk == NULL) {
		Ddim_Assertion(("PWM input param error. [clk] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (cycle == NULL) {
		Ddim_Assertion(("PWM input param error. [cycle] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	clockDiv = 1;
	clockMargin = 1;
	usecDiv = 0;
	usecMargin = 0;

	// The number of clocks is set to the variable
	periClock = Dd_Top_Get_RCLK();
//	printf("periClock = %ld \n", periClock);

	// total count(Overflow is a disregarded number of counts)
	countBase = periClock * usec;

	// The correspondence dividing frequency is retrieved
	for (divWk = 4; divWk > 0; divWk--) {
		// flag initialize
		findFlag = 0;
		// clock
		divTmp = 1 << (kuchar)((divWk - 1) * 2);

		// divTmp(clock) = usecDiv * clockDiv

		/* "The number of specified time" * "periClock" judges to be divided
		because of a specified dividing frequency regardless of overflow*/
		if ((countBase & (divTmp - 1)) == 0) {
			/*Dividing frequency that usec can be divided is retrieved.
			 * It adds for the condition judgment of the kulong type 1*/
			for (usecDivWk = 1; usecDivWk <= divTmp; usecDivWk *= 2) {
				// clock
				usecDiv = divTmp / usecDivWk;

				/* Time is divided in order of 64, 32, 16, 8, 4, and 2 at the time of 64 dividing frequency
				*Time is divided in order of 16, 8, 4, and 2 at the time of 16 dividing frequency
				*Time is divided in order of 4 and 2 at the time of four dividing frequency
				*Time is divided by one at the time of one dividing frequency */

				if ((usec % usecDiv) == 0) {
					// (usec/usecDiv)However, the multiple of ten that can be practical is obtained
					usecByUsecDiv = usec / usecDiv;
					clockDiv = (divTmp / usecDiv);
					periClockByClockDiv = periClock / clockDiv;
					for (usecMargin = 1000000; usecMargin > 0; usecMargin /= 10) {
						if ((usecByUsecDiv % usecMargin) == 0) {
							clockMargin = (1000000 / usecMargin);
							// Whether {periClock/(divTmp/usecDiv)} can divide by (1000000/usecMargin) is judged
							if ((periClockByClockDiv % clockMargin) == 0) {

								// It is judged not to overflow even if the number of total counts is requested by
								// using obtained "usecDiv", "usecMargin", "clockDiv", and "clockMargin"
								if ((usec / (usecDiv * usecMargin))
										<= (0xffffffff / (periClock / (clockDiv * clockMargin)))) {
									findFlag = 1;
									break;
								}
							}
						}
					}
					if (findFlag == 1) {
						// Dividing frequency (usecDiv&clockDiv) and margin that doesn't do overflow exist.
						if(((usec / usecDiv) % usecMargin) != 0) {
							// Because time cannot be divided, it continues the retrieval
							findFlag = 0;
							continue;
						}
						if ((periClockByClockDiv % clockMargin) != 0) {
							// Because time cannot be divided, it continues the retrieval
							findFlag = 0;
							continue;
						}
						if ((usec / usecDiv) > (0xffffffff / (periClockByClockDiv / clockMargin))) {
							findFlag = 0;
							continue;
						}
						break;
					}
				}
			}
		}

		if (findFlag == 1) {
			// totalCount
			totalCount = (usec / (usecDiv * usecMargin)) * (periClock / (clockDiv * clockMargin));

			*clk = (kuchar)(divWk - 1);
			if (totalCount <= 0xffff) {
				*cycle	= (kushort)totalCount;
			}
			else {
				for (divWk2 = 1; divWk2 <= 4; divWk2++) {

					if ((divWk + divWk2) > 4) {
						break;
					}

					divWk3 = (kuchar)(4 << (kuchar)((divWk2 - 1) * 2));

					totalCountWk	= totalCount / divWk3;

					if (totalCountWk <= 0xffff) {
						*cycle	= (kushort)totalCountWk;
						*clk	= (kuchar)(*clk + divWk2);
						return DdPwmBranch_OVERFLOW_OK;
					}
				}
				return DdPwmBranch_OVERFLOW_ERROR;
			}
			break;
		}
	}
	return D_DDIM_OK;
}

/*
 * * @brief  Cycle parameters are calculated according
 *		   to the designated time (u sec).
 *		   If it doesn't calculate, Input Parameter Error is returned.
 * @param  kulong usec, kuchar clk, kushort* cycle
 * @return kint32 D_DDIM_OK / DdPwmBranch_OVERFLOW_ERROR
 */
kint32 dd_pwm_utility_calculate_cycle(DdPwmUtility* self,
		kulong usec, kuchar const clk, kushort* const cycle)
{
	kulong periClock2;
	kulong totalCount;

#ifdef CO_PARAM_CHECK
	if (usec == 0) {
		Ddim_Assertion(("PWM input param error. [usec] = %ld\n", usec));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (clk > DdPwmBranch_PCNHL_CKS_DIV_64) {
		Ddim_Assertion(("PWM input param error. [clk] = %d\n", clk));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (cycle == NULL) {
		Ddim_Assertion(("PWM input param error. [cycle] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	periClock2 = Dd_Top_Get_RCLK();

	if(0 == clk) {
		totalCount = ((periClock2 / 1000000) * usec);
	}
	else {
		totalCount = ((periClock2 / 1000000) * usec) / (1 << (clk << 1));
	}

	if(0 == totalCount) {
		// minimum count
		*cycle = 1;
//        return DdPwmBranch_OVERFLOW_ERROR;
		return D_DDIM_OK;
	}
	else if(0xFFFF < totalCount) {
		// maximum count
		*cycle = 0xFFFF;
//		return DdPwmBranch_OVERFLOW_ERROR;
		return D_DDIM_OK;
	}
	else {
		*cycle = (kushort)totalCount;
		return D_DDIM_OK;
	}
}

/*
 * @brief  The PWM output control channel wave form is set (change).
 * @param  kuint32 ch, kuchar cycle, kuchar duty(0-100%)
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_cycle_duty(DdPwmUtility* self, kuint32 ch,
		kushort cycle, kuchar duty, kuchar clkSel)
{
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;
	kushort dutyValue = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (cycle == 0) {
		Ddim_Assertion(("PWM input param error. [cycle] = %d\n", cycle));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (duty == 0) {
		Ddim_Assertion(("PWM input param error. [duty] = %d\n", duty));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (clkSel > DdPwmBranch_PCNHL_CKS_DIV_64) {
		Ddim_Assertion(("PWM input param error. [clkSel] = %d\n", clkSel));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(dd_pwm_get_branch_ctrl_memo(dd_pwm_get(), ch).clkSel != clkSel) {
		pcnAddr = dd_pwm_get_branch_func_pcn_addr(dd_pwm_get(), ch);
		pcnTmp.word = pcnAddr->word;
		pcnTmp.bit.__CKS = clkSel;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF = 1;
		pcnAddr->word = pcnTmp.word;
	}

	dutyValue = (kushort)(cycle * duty / 100);
	dd_pwm_set_branch_cyc_num(dd_pwm_get(), ch, cycle);
	dd_pwm_set_branch_duty_num(dd_pwm_get(), ch, dutyValue);

	switch (ch & 0x03) {
		case 0:
			IO_PERI.PWM[ch >> 2].PCSRA = cycle;
			IO_PERI.PWM[ch >> 2].PDUTA = dutyValue;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].PCSRB = cycle;
			IO_PERI.PWM[ch >> 2].PDUTB = dutyValue;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].PCSRC = cycle;
			IO_PERI.PWM[ch >> 2].PDUTC = dutyValue;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].PCSRD = cycle;
			IO_PERI.PWM[ch >> 2].PDUTD = dutyValue;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM output control channel wave form is set for reverse(change).
 * @param  kuint32 ch, kushort cycle, kuchar duty(0-100%)
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_cycle_duty_reverse(DdPwmUtility* self,
		kuint32 ch, kushort cycle, kuchar duty, kuchar clkSel)
{
	kuchar CNTE;
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;
	kushort dutyValue = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (cycle == 0) {
		Ddim_Assertion(("PWM input param error. [cycle] = %d\n", cycle));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (duty == 0) {
		Ddim_Assertion(("PWM input param error. [duty] = %d\n", duty));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (clkSel > DdPwmBranch_PCNHL_CKS_DIV_64) {
		Ddim_Assertion(("PWM input param error. [clkSel] = %d\n", clkSel));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	pcnAddr = dd_pwm_get_branch_func_pcn_addr(dd_pwm_get(), ch);

	CNTE = pcnAddr->bit.__CNTE;
	pcnTmp.word = pcnAddr->word;
	/* timer count enable	@PCNH	*/
	pcnTmp.bit.__CNTE	= 0;
	/* interrupt flag (not change)	*/
	pcnTmp.bit.__IRQF	= 1;
	if(dd_pwm_get_branch_ctrl_memo(dd_pwm_get(), ch).clkSel != clkSel) {
		pcnTmp.bit.__CKS = clkSel;
	}
	pcnAddr->word = pcnTmp.word;

	dutyValue = (kushort)(cycle * duty / 100);

	switch (ch & 0x03) {
		case 0:
			IO_PERI.PWM[ch >> 2].PCSRRA = cycle;
			IO_PERI.PWM[ch >> 2].PDUTRA = dutyValue;
			IO_PERI.PWM[ch >> 2].PREV.bit.PREVE0 = 1;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].PCSRRB = cycle;
			IO_PERI.PWM[ch >> 2].PDUTRB = dutyValue;
			IO_PERI.PWM[ch >> 2].PREV.bit.PREVE1 = 1;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].PCSRRC = cycle;
			IO_PERI.PWM[ch >> 2].PDUTRC = dutyValue;
			IO_PERI.PWM[ch >> 2].PREV.bit.PREVE2 = 1;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].PCSRRD = cycle;
			IO_PERI.PWM[ch >> 2].PDUTRD = dutyValue;
			IO_PERI.PWM[ch >> 2].PREV.bit.PREVE3 = 1;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	/* timer count restore			*/
	pcnTmp.bit.__CNTE	= CNTE;
	pcnAddr->word = pcnTmp.word;

	return D_DDIM_OK;
}

/*
 * @brief  The PWM output control channel wave form is set for queue(change).
 * @param  kuint32 ch, kushort cycle, kuchar duty(0-100%)
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_cycle_duty_queue(DdPwmUtility* self,
		kuint32 ch, kushort cycle, kuchar duty, kuchar clkSel)
{
	volatile union io_pwm_pcn* pcnAddr;
	union io_pwm_pcn pcnTmp;
	kushort dutyValue = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (cycle == 0) {
		Ddim_Assertion(("PWM input param error. [cycle] = %d\n", cycle));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (duty == 0) {
		Ddim_Assertion(("PWM input param error. [duty] = %d\n", duty));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (clkSel > DdPwmBranch_PCNHL_CKS_DIV_64) {
		Ddim_Assertion(("PWM input param error. [clkSel] = %d\n", clkSel));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	if(dd_pwm_get_branch_ctrl_memo(dd_pwm_get(), ch).clkSel != clkSel) {
		pcnAddr = dd_pwm_get_branch_func_pcn_addr(dd_pwm_get(), ch);
		pcnTmp.word = pcnAddr->word;
		pcnTmp.bit.__CKS = clkSel;
		/* interrupt flag (not change)	*/
		pcnTmp.bit.__IRQF = 1;
		pcnAddr->word = pcnTmp.word;
		dd_pwm_set_branch_clk_sel(dd_pwm_get(), ch, clkSel);
	}

	dutyValue = (kushort)(cycle * duty / 100);

	switch (ch & 0x03) {
		case 0:
			IO_PERI.PWM[ch >> 2].PCSRQA = cycle;
			IO_PERI.PWM[ch >> 2].PDUTQA = dutyValue;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].PCSRQB = cycle;
			IO_PERI.PWM[ch >> 2].PDUTQB = dutyValue;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].PCSRQC = cycle;
			IO_PERI.PWM[ch >> 2].PDUTQC = dutyValue;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].PCSRQD = cycle;
			IO_PERI.PWM[ch >> 2].PDUTQD = dutyValue;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM input trigger is set.
 * @param  kuint32 ch, kuchar gcnTsel
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_input_trg(DdPwmUtility* self, kuint32 ch, kuchar gcnTsel)
{
	const kuint32 chInBlk = (DdPwmBranch_CH_NUM_IN_BLOCK - 1) & ch;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch (chInBlk) {
		case 0:
			IO_PERI.PWM[ch >> 2].GCN1.bit.TSEL0 = gcnTsel;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].GCN1.bit.TSEL1 = gcnTsel;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].GCN1.bit.TSEL2 = gcnTsel;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].GCN1.bit.TSEL3 = gcnTsel;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM switch factor of cycle and duty is selected.
 * @param  kuint32 ch, kuchar tsel
 * @return kint32  D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_cycle_duty_switch(DdPwmUtility* self, kuint32 ch, kuchar tsel)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch (ch & 0x03) {
		case 0:
			IO_PERI.PWM[ch >> 2].TSEL.bit.SEL0 = tsel;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].TSEL.bit.SEL1 = tsel;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].TSEL.bit.SEL2 = tsel;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].TSEL.bit.SEL3 = tsel;
			break;

		default:
			return DdPwmBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/*
 * @brief  The PWM controle and status is set.
 * @param  kuint32 ch, kushort pcn
 * @return kint32 D_DDIM_OK/DdPwmBranch_INPUT_PARAM_ERROR
 */
kint32 dd_pwm_utility_write_pcn(DdPwmUtility* self, kuint32 ch, kushort pcn)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	switch (ch & 0x03) {
		case 0:
			IO_PERI.PWM[ch >> 2].PCNA.word = pcn;
			break;

		case 1:
			IO_PERI.PWM[ch >> 2].PCNB.word = pcn;
			break;

		case 2:
			IO_PERI.PWM[ch >> 2].PCNC.word = pcn;
			break;

		case 3:
			IO_PERI.PWM[ch >> 2].PCND.word = pcn;
			break;

		default:
			break;
	}

	return D_DDIM_OK;
}

/*
 * The PWM Timer Onshot is set.
 */
kint32 dd_pwm_utility_write_onshot(DdPwmUtility* self, kuint32 ch, kushort dutyTime,
						 DdPwmCtrlCmn* const pwmCtrlCmn,
						 DdpwmCtrlTimerAbcd* const pwmCtrlTimerAbcd)
{
	kint32 ret;
	kuchar clk;
	kushort cycNum = 0;
	kushort dutyNum = 0;

#ifdef CO_PARAM_CHECK
	if (ch >= DdPwmBranch_CH_NUM_MAX) {
		Ddim_Assertion(("PWM input param error. [ch] = %d\n", ch));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlCmn) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlCmn] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
	if (0 == pwmCtrlTimerAbcd) {
		Ddim_Assertion(("PWM input param error. [pwmCtrlTimerAbcd] = NULL\n"));
		return DdPwmBranch_INPUT_PARAM_ERROR;
	}
#endif

	// Dividing frequency set
	clk = pwmCtrlCmn->clkSel;

	// cycle time(usec) convert
	ret = dd_pwm_utility_calculate(self, pwmCtrlTimerAbcd->cycTime, &clk, &cycNum);
	if ((ret != D_DDIM_OK) && (ret != DdPwmBranch_OVERFLOW_OK)){
		Ddim_Print(("PWM: calculate error. ret = 0x%x\n", ret))
		return ret;
	}

	dutyNum =	(kushort)(cycNum * dutyTime / pwmCtrlTimerAbcd->cycTime);

	if (dutyNum > cycNum) {
		dutyNum = (kushort)(cycNum - 1);
	}
	/* Oneshot */
	pwmCtrlCmn->drvMode = 1;
	pwmCtrlCmn->clkSel = clk;
	pwmCtrlTimerAbcd->cycNum = cycNum;
	pwmCtrlTimerAbcd->dutyNum = dutyNum;
	pwmCtrlCmn->intEnable = DdPwmBranch_PCNHL_IREN_ON;

	ret = dd_pwm_ctrl_common(dd_pwm_get(), ch, pwmCtrlCmn);
	if (ret != D_DDIM_OK){
		Ddim_Print(("PWM: common setting error. ret = 0x%x\n", ret))
		return ret;
	}

	ret = dd_pwm_ctrl_timer_abcd(dd_pwm_get(), ch, pwmCtrlTimerAbcd);
	if (ret != D_DDIM_OK){
		Ddim_Print(("PWM: abcd setting error. ret = 0x%x\n", ret))
		return ret;
	}

	return D_DDIM_OK;
}

#endif	/* CO_DDIM_UTILITY_USE */

DdPwmUtility* dd_pwm_utility_get(void)
{
	DdPwmUtility *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_PWM_UTILITY, sizeof(DdPwmUtilityPrivate));
	}

	return self;
}
