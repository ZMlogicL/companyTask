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

#ifndef __DD_UDC_INTERRUPTION_H__
#define __DD_UDC_INTERRUPTION_H__

#include <klib.h>
#include "ddudc.h"

#define DD_TYPE_UDC_INTERRUPTION               (dd_udc_interruption_get_type())
#define DD_UDC_INTERRUPTION(obj)                 K_TYPE_CHECK_INSTANCE_CAST(obj, DdUdcInterruption)
#define DD_IS_UDC_INTERRUPTION(obj)            K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_UDC_INTERRUPTION)

typedef struct _DdUdcInterruption                       DdUdcInterruption;
typedef struct _DdUdcInterruptionPrivate          DdUdcInterruptionPrivate;

struct _DdUdcInterruption
{
	KObject parent;
};

KConstType                   dd_udc_interruption_get_type(void);
DdUdcInterruption*    dd_udc_interruption_new(void);

/*
*The interruption flag is cleared, and the CallBack function for UpDown Counter called.
*@param [in] ch	Channel number.<br>
*				Please specify either the following.<br>
*				- @ref D_DD_UDC_CH0
*				- @ref D_DD_UDC_CH1
*				- @ref D_DD_UDC_CH2
*				- @ref D_DD_UDC_CH3
*				- @ref D_DD_UDC_CH4
*				- @ref D_DD_UDC_CH5
*/
void                               dd_udc_interruption_int_handler(kuchar ch);    // TODO 中断汇编调用

#endif /* __DD_UDC_INTERRUPTION_H__ */
