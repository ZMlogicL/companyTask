/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-08
* @author    : 肖泽友
* @brief        :UpDown Counter driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、The interruption flag is cleared, and the CallBack function for UpDown Counter called.
*
*@version   :1.0.0
*
*/

#include "peripheral.h"
#include "dd_arm.h"

#include "ddudcinterruption.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdUdcInterruption, dd_udc_interruption);
#define DD_UDC_INTERRUPTION_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), \
		DdUdcInterruptionPrivate, DD_TYPE_UDC_INTERRUPTION))

struct _DdUdcInterruptionPrivate
{
    kint a;
};

static void dd_udc_interruption_constructor(DdUdcInterruption *self)
{
	DdUdcInterruptionPrivate *priv = DD_UDC_INTERRUPTION_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_udc_interruption_destructor(DdUdcInterruption *self)
{

}

/*
 * PUBLIC
 */
/*
*The interruption flag is cleared, and the CallBack function for UpDown Counter called.
*@param [in] ch	Channel number.<br>
*/
void dd_udc_interruption_int_handler(kuchar ch)
{
	kint32	result;
	kulong	 reg;

#ifdef CO_PARAM_CHECK
	// channel number range check
	if(dd_udc_get_chk_ch_number(dd_udc_get(), ch) != D_DDIM_OK){
		// Error of channel number
		Ddim_Assertion(("E:Dd_UDC_Int_Handler parameter error. ch=%d\n", ch));
		return;
	}
#endif	// CO_PARAM_CHECK

	if((IO_PERI.UDC[ch].CSR.bit.__CITE == 1) && (IO_PERI.UDC[ch].CSR.bit.__CMPF == 1)){
		// The comparison agreement was detected.
		if(dd_udc_get_p_callback(dd_udc_get(), ch) != NULL){
			// Call callback function
			result = DdUdc_CMPF_OK;
			(*dd_udc_get_p_callback(dd_udc_get(), ch))(ch, result);
		}
		// Clear interrupt flag
		reg = IO_PERI.UDC[ch].CSR.word;
		// Clear CMPF
		reg &= ~DdUdc_CSR_BIT_CMPF;
		// Not change OVFF, UDFF
		reg |= (DdUdc_CSR_BIT_OVFF | DdUdc_CSR_BIT_UDFF);
		IO_PERI.UDC[ch].CSR.word = reg;
		Dd_ARM_Dsb_Pou();
	}

	if((IO_PERI.UDC[ch].CSR.bit.__UDIE == 1) && (IO_PERI.UDC[ch].CSR.bit.__OVFF == 1)){
		// The overflow was detected.
		if(dd_udc_get_p_callback(dd_udc_get(), ch) != NULL){
			// Call callback function
			result = DdUdc_OVER_FLOW;
			(*dd_udc_get_p_callback(dd_udc_get(), ch))(ch, result);
		}
		// Clear interrupt flag
		reg = IO_PERI.UDC[ch].CSR.word;
		// Clear OVFF
		reg &= ~DdUdc_CSR_BIT_OVFF;
		// Not change CMPF, UDFF
		reg |= (DdUdc_CSR_BIT_CMPF | DdUdc_CSR_BIT_UDFF);
		IO_PERI.UDC[ch].CSR.word = reg;
		Dd_ARM_Dsb_Pou();
	}

	if((IO_PERI.UDC[ch].CSR.bit.__UDIE == 1) && (IO_PERI.UDC[ch].CSR.bit.__UDFF == 1)){
		// The underflow was detected.
		if(dd_udc_get_p_callback(dd_udc_get(), ch) != NULL){
			// Call callback function
			result = DdUdc_UNDER_FLOW;
			(*dd_udc_get_p_callback(dd_udc_get(), ch))(ch, result);
		}
		// Clear interrupt flag
		reg = IO_PERI.UDC[ch].CSR.word;
		// Clear UDFF
		reg &= ~DdUdc_CSR_BIT_UDFF;
		// Not change CMPF, OVFF
		reg |= (DdUdc_CSR_BIT_CMPF | DdUdc_CSR_BIT_OVFF);
		IO_PERI.UDC[ch].CSR.word = reg;
		Dd_ARM_Dsb_Pou();
	}

	if((IO_PERI.UDC[ch].CCR.bit.__CFIE == 1) && (IO_PERI.UDC[ch].CCR.bit.__CDCF == 1)){
		// Count direction change was detected.
		if(dd_udc_get_p_callback(dd_udc_get(), ch) != NULL){
			// Call callback function
			result = DdUdc_COUNT_DIRECTION;
			(*dd_udc_get_p_callback(dd_udc_get(), ch))(ch, result);
		}
		// Clear interrupt flag
		// Clear CDCF
		IO_PERI.UDC[ch].CCR.word &= ~DdUdc_CCR_BIT_CDCF;
		Dd_ARM_Dsb_Pou();
	}
	return;
}

DdUdcInterruption* dd_udc_interruption_new(void)
{
	DdUdcInterruption* self = k_object_new_with_private(DD_TYPE_UDC_INTERRUPTION,
			sizeof(DdUdcInterruptionPrivate));
	return self;
}
