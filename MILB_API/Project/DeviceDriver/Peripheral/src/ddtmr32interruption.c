/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-08
* @author    : 肖泽友
* @brief        :peripheral 32 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、The interruption flag is cleared, and the CallBack function for 32bit Reload Timer is called.
*
*@version   :1.0.0
*
*/

#include "peripheral.h"
#include "dd_arm.h"

#include "ddtmr32interruption.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdTmr32Interruption, dd_tmr32_interruption);
#define DD_TMR32_INTERRUPTION_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		DdTmr32InterruptionPrivate, DD_TYPE_TMR32_INTERRUPTION))

struct _DdTmr32InterruptionPrivate
{
    kint a;
};

static void dd_tmr32_interruption_constructor(DdTmr32Interruption *self)
{
	DdTmr32InterruptionPrivate *priv = DD_TMR32_INTERRUPTION_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_tmr32_interruption_destructor(DdTmr32Interruption *self)
{

}

/*
 * PUBLIC
 */
/*
 * @brief  The interruption flag is cleared, and the CallBack function for 32bit Reload Timer is called.
 * @param  kuint32 ch
 * @return VOID
 */
void dd_tmr32_interruption_int_handler(kuint32 ch)
{
	union	io_tmr_tmcsr	tmcsr;

	tmcsr.word = IO_PERI.TMR[ch].TMCSR.word;

//	printf("Dd_TMR32_Int_Handler = %d \n", ch);

	// The channel of the generated interruption is checked.
	if ((tmcsr.word & 0x00000006) != 0x00000006) {
		return;
	}
	// UF bit clear
	IO_PERI.TMR[ch].TMCSR.word &= 0xFFFFFFBB;
	Dd_ARM_Dsb_Pou();

	// Soft-Counter check
	if (dd_tmr32_get_soft_counter(dd_tmr32_get(), ch) > 1) {
		dd_tmr32_set_soft_counter_reduce(dd_tmr32_get(), ch);
	}
	else {
		// Reload check
		if ((tmcsr.bit.__RELD == 1) && (dd_tmr32_get_reload_flg(dd_tmr32_get(), ch) == 1)) {
			/* pgr0872 */
			dd_tmr32_set_soft_counter(dd_tmr32_get(), ch);
		}
		else {
			dd_tmr32_stop(dd_tmr32_get(), ch);
		}

		// Callback check
		if (dd_tmr32_get_callback(dd_tmr32_get(), ch)) {
			// Call Back function
			(*dd_tmr32_get_callback(dd_tmr32_get(), ch))();
		}
	}
}

DdTmr32Interruption* dd_tmr32_interruption_new(void)
{
	DdTmr32Interruption* self = k_object_new_with_private(DD_TYPE_TMR32_INTERRUPTION,
			sizeof(DdTmr32InterruptionPrivate));
	return self;
}
