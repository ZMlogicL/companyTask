/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-04
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、Calculate the clock divisor from the specified baudrate
*
*@version   :1.0.0
*
*/

#include "spi.h"
#include "dd_top.h"

#include "ddspicalculate.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdSpiCalculate, dd_spi_calculate);
#define DD_SPI_CALCULATE_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdSpiCalculatePrivate, DD_TYPE_SPI_CALCULATE))

struct _DdSpiCalculatePrivate
{
	kulong divisor;
};

static void dd_spi_calculate_constructor(DdSpiCalculate *self)
{
	DdSpiCalculatePrivate *priv = DD_SPI_CALCULATE_GET_PRIVATE(self);
    priv->divisor = 0;
}

static void dd_spi_calculate_destructor(DdSpiCalculate *self)
{

}

/*
 * PUBLIC
 */
#ifdef CO_DDIM_UTILITY_USE
/*
 * Calculate the clock divisor from the specified baudrate
 */
kint32 dd_spi_calculate_clock_divisor(DdSpiCalculate* self, kulong baudrate, kuchar* const clkDiv)
{
	DdSpiCalculatePrivate *priv = DD_SPI_CALCULATE_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if(baudrate < 1){
		Ddim_Assertion(("SPI input param error. [baudrate] = %lu\n", baudrate));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(clkDiv == NULL){
		Ddim_Assertion(("SPI input param error. [clkDiv] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	priv->divisor = (Dd_Top_Get_SPICLK() / baudrate / 2);

	if((priv->divisor >= 1) && (priv->divisor <= 256)){
		*clkDiv = priv->divisor - 1;
//		Ddim_Print(("SPICLK=%d , baudrate=%d, divisor=%d, clkDiv=%d\n", Dd_Top_Get_SPICLK(),
//				baudrate, priv->divisor, *clkDiv));
	}
	else {
		*clkDiv = 0;
		Ddim_Print(("Dd_SPI_Calculate() error. baudrate=%lu , divisor=%lu\n", baudrate, priv->divisor));

		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

#endif

/*
 * Set SPI clock divisor
 */
kint32 dd_spi_calculate_set_clock_divisor(DdSpiCalculate* self, kuchar ch, kuchar clkDiv)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	IO_SPI[ch].DIV.bit.DIVISOR = clkDiv;

	return D_DDIM_OK;
}

/*
 * Get SPI clock divisor
 */
kint32 dd_spi_calculate_get_clock_divisor(DdSpiCalculate* self, kuchar ch, kuchar* const clkDiv)
{
#ifdef CO_PARAM_CHECK
	if(ch >= DdSpiDriveBranch_CH_MAX){
		Ddim_Assertion(("SPI input param error. [ch] = %d\n", ch));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
	if(clkDiv == NULL){
		Ddim_Assertion(("SPI input param error. [clkDiv] = NULL\n"));
		return DdSpiDriveBranch_INPUT_PARAM_ERROR;
	}
#endif

	*clkDiv = IO_SPI[ch].DIV.bit.DIVISOR;

	return D_DDIM_OK;
}

DdSpiCalculate* dd_spi_calculate_get(void)
{
	DdSpiCalculate *self = NULL;
	if(!self){
		self = k_object_new_with_private(DD_TYPE_SPI_CALCULATE, sizeof(DdSpiCalculatePrivate));
	}

	return self;
}
