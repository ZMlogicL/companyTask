/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-08
* @author    : 肖泽友
* @brief        :UpDown Counter driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、utility section
*
*@version   :1.0.0
*
*/

#ifndef __DD_UDC_UTILITY_H__
#define __DD_UDC_UTILITY_H__

#include <klib.h>
#include "ddudc.h"

#define DD_TYPE_UDC_UTILITY                    (dd_udc_utility_get_type())
#define DD_UDC_UTILITY(obj)                      K_TYPE_CHECK_INSTANCE_CAST(obj, DdUdcUtility)
#define DD_IS_UDC_UTILITY(obj)                 K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UDC_UTILITY)

typedef struct _DdUdcUtility                         DdUdcUtility;
typedef struct _DdUdcUtilityPrivate             DdUdcUtilityPrivate;

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Typedefs
@{*/

/*< Type is defined to Callback function pointer
*for timer utility function.<br>The meaning of
* the argument is as follows.<br>
* - kuchar ch    : Channel number.<br>
*<ul><li>@ref D_DD_UDC_CH0
*<li>@ref D_DD_UDC_CH1
* <li>@ref D_DD_UDC_CH2
*<li>@ref D_DD_UDC_CH3
*<li>@ref D_DD_UDC_CH4
*<li>@ref D_DD_UDC_CH5</ul>
*/
typedef void (*DdUdcTimerCallback)(kuchar ch);

/*@}*/
#endif

struct _DdUdcUtility
{
	KObject parent;
};

KConstType               dd_udc_utility_get_type(void);
DdUdcUtility*            dd_udc_utility_get(void);

#ifdef CO_DDIM_UTILITY_USE
/* @name Utility Functions
@{*/

/*
*Set parameter for timer utility function.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*@param [in] usec	Setting time.(usec order, range of 0..4294967295)<br>
*@param [in] timerCallback	Callback function for timer utility function.<br>
*@retval D_DDIM_OK					OK
*@retval D_DD_UDC_ERROR_BUSY			Macro Busy Error
*@retval D_DD_UDC_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32                          dd_udc_utility_write_timer_mode(DdUdcUtility* self, kuchar ch,
		                                   kulong usec, DdUdcTimerCallback timerCallback);

/*@}*/
/*@}*/

/*
@weakgroup dd_udc
@{
<hr>
Utility Functions <br>
	- @ref UDC_timer_utility
	- @ref dd_udc_sample_section5

	@section UDC_timer_utility	Sequence of UDC timer utility function
*/
/*@}*/

#endif

#endif /* __DD_UDC_UTILITY_H__ */
