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

#ifndef __DD_SPI_CALCULATE_H__
#define __DD_SPI_CALCULATE_H__

#include <klib.h>
#include "ddspi.h"

#define DD_TYPE_SPI_CALCULATE                    (dd_spi_calculate_get_type())
#define DD_SPI_CALCULATE(obj)                      K_TYPE_CHECK_INSTANCE_CAST(obj, DdSpiCalculate)
#define DD_IS_SPI_CALCULATE(obj)                 K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SPI_CALCULATE)

typedef struct _DdSpiCalculate                         DdSpiCalculate;
typedef struct _DdSpiCalculatePrivate            DdSpiCalculatePrivate;

struct _DdSpiCalculate
{
	KObject parent;
};

KConstType                        dd_spi_calculate_get_type(void);
DdSpiCalculate*                dd_spi_calculate_get(void);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
*@{*/

/*
*Calculate the clock divisor from the specified baudrate.
*@param [in]		baudrate	baudrate (bps).
*@param [out]	clkDiv		clock divisor (result of calculate).
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                                  dd_spi_calculate_clock_divisor(DdSpiCalculate* self,
		                                            kulong baudrate, kuchar* const clkDiv);

/*
*Set SPI clock divisor.
*@param [in]		ch		Channel number(0 to 2)
*@param [in]		clkDiv	Serial Clock Divisor.<br>
*						SCLK = extSclkM(SPICLK) / (2 * (divisor + 1))
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                                  dd_spi_calculate_set_clock_divisor(DdSpiCalculate* self,
		                                             kuchar ch, kuchar clkDiv);

/*
*Get SPI clock divisor.
*@param [in]		ch		Channel number(0 to 2)
*@param [out]	clkDiv	Serial Clock Divisor.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                                  dd_spi_calculate_get_clock_divisor(DdSpiCalculate* self,
		                                             kuchar ch, kuchar* const clkDiv);

#endif

#endif /* __DD_SPI_CALCULATE_H__ */
