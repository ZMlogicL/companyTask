/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 王顺
*@brief : DdExiu
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/
/**
 * @file		ddexiu.h
 * @brief		EXIU (External Interrupt Unit) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
@addtogroup dd_exiu
@{
	- @ref operation_procedure_sequence_exiu
	- @ref dd_exiu_sample_section
*/


#ifndef __DD_EXIU_H__
#define __DD_EXIU_H__


#include <klib.h>
#include "driver_common.h"
#include "ddarm.h"
#include "arm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_EXIU                  (dd_exiu_get_type())
#define DD_EXIU(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdExiu))
#define DD_IS_EXIU(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DD_TYPE_EXIU))

#define	C_INPUT_PARAM_ERR		(D_DD_EXIU | D_DDIM_INPUT_PARAM_ERROR) /**< Input Parameter Error */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define C_CH_MAX				(31)						/**< Channel Max Number */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define C_CH_MAX				(32)						/**< Channel Max Number */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define C_CH_MIN				(16)						/**< Channel Min Number */
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
#define C_VAL_MAX				(0x0000FFFF)		/**< Value Max Number */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
#define C_VAL_MAX				(0x0001FFFF)		/**< Value Max Number */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
#define C_VAL_MIN				(0x00000000)		/**< Value Min Number */


typedef struct _DdExiu DdExiu;
typedef struct _DdExiuPrivate DdExiuPrivate;

struct _DdExiu
{
	KObject parent;
};


KConstType		dd_exiu_get_type(void);
DdExiu* 			dd_exiu_new(void);
/**
Get Interrupt Mask.
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Interrupt Mask Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 				dd_exiu_get_eimask(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get Interrupt Source Select.
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Interrupt Source Select Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eisrcsel(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get Internal Interrupt Request Status
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Internal Interrupt Request Status Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eireqsta(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get Raw Interrupt Request Status
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Raw Interrupt Request Status Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eirawreqsta(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get External Interrupt Level Setting
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: External Interrupt Level Setting Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eilvl(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get Interrupt Detection Method Setting
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Interrupt Detection Method Setting Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eiedg(DdExiu *self, kuint32 ch, kuint32* val);

/**
Get Software Interrupt
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@param [out] *val						: Software Interrupt Value
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_get_eisir(DdExiu *self, kuint32 ch, kuint32* val);

/**
Set Interrupt Mask Release Select
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eimask_release(DdExiu *self, kuint32 ch);

/**
Set Interrupt Mask Select
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_dd_exiu_set_eimask_mask(DdExiu *self, kuint32 ch);

/**
Set Interrupt is Mask or Release
@param [in]	val							: Interrupt Mask or Release Value ( @ref C_VAL_MIN to @ref C_VAL_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eimask_val(DdExiu *self, kuint32 val);

/**
Set Interrupt External Source Select
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eisrcsel_ext(DdExiu *self, kuint32 ch);

/**
Set Interrupt Sofware Source Select
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eisrcsel_soft(DdExiu *self, kuint32 ch);

/**
Set Interrupt Cleared Channel
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32 				dd_exiu_set_eireqclr_ch(DdExiu *self, kuint32 ch);

/**
Set Interrupt Cleared Value
@param [in]	val							: Interrupt Cleared Value ( @ref C_VAL_MIN to @ref C_VAL_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eireqclr_val(DdExiu *self, kuint32 val);

/**
Set External Interrupt Low level or Falling edge
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eilvl_lo(DdExiu *self, kuint32 ch);

/**
Set External Interrupt High level or Rising edge
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eilvl_hi(DdExiu *self, kuint32 ch);

/**
Set Interrupt Level Detection Setting
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eiedg_level(DdExiu *self, kuint32 ch);

/**
Set Interrupt Edge Detection Setting
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eiedg_edge(DdExiu *self, kuint32 ch);

/**
Set Software Interrupt Generate
@param [in]	ch							: EXIU Channel Number ( @ref C_CH_MIN to @ref C_CH_MAX )
@retval	D_DDIM_OK						: Normal end
@retval	C_INPUT_PARAM_ERR		: Input Parameter Error
*/
kint32				dd_exiu_set_eisir_generate(DdExiu *self, kuint32 ch);

/*@}*/

/**
@weakgroup dd_exiu
@{
	@section operation_procedure_sequence_exiu		Example of Operating Procedure for External Interrupt.
	@image html Operating_Procedure_for_External_Interrupt.png
	<br>
	@section dd_exiu_sample_section					Sample of "Operating Procedure for External Interrupt" using Dd_EXIU_xxx functions.
    @code
	// interrupt parameter
	#define EXTERNAL_INTERRUPT	(0)
	#define SOFTWARE_INTERRUPT	(1)
	
	// trigger parameter
	#define LOW_LEVEL			(0)
	#define HIGH_LEVEL			(1)
	#define FALLING_EDGE		(2)
	#define RISING_EDGE			(3)
	
	// detection type
	#define LEVEL_DETECTION		(0)
	#define EDGE_DETECTION		(1)
	
	void Init_External_Interrupt_Unit(kuchar ch_num, kuchar interrupt_prm, kuchar trigger_prm)
	{
		// ch_num		 : C_CH_MIN - C_CH_MAX
		// interrupt_prm : 0 - 1
		// trigger_prm	 : 0 - 3
		
		if( ch_num < C_CH_MIN || ch_num > C_CH_MAX ) {
			Ddim_Print(("Error Channel Prameter !!\n"));
			return;
		}
		
		// Set the interrupt mask in the "Interrupt Masking Register (EIMASK)".
		dd_exiu_dd_exiu_set_eimask_mask(NULL, ch_num);
		
		// Set the interrupt source in the "Interrupt Source Select Register (EISRCSEL)".
		if( interrupt_prm == EXTERNAL_INTERRUPT ) {
			dd_exiu_set_eisrcsel_ext(NULL, ch_num);
		}
		else if( interrupt_prm == SOFTWARE_INTERRUPT ) {
			dd_exiu_set_eisrcsel_soft(NULL, ch_num);
		}
		else {
			Ddim_Print(("Error Interrupt Source Select Prameter !!\n"));
			return;
		}
		
		// Set the external interrupt request signal in the "External Interrupt Level Setting Register (EILVL)".
		if( trigger_prm == LOW_LEVEL || trigger_prm == FALLING_EDGE ) {
			dd_exiu_set_eilvl_lo(NULL, ch_num);
		}
		else if( trigger_prm == HIGH_LEVEL || trigger_prm == RISING_EDGE ) {
			dd_exiu_set_eilvl_hi(NULL, ch_num);
		}
		else {
			Ddim_Print(("Error Trigger Prameter !!\n"));
			return;
		}
		
		// Set the external interrupt request signal in the "Interrupt Detection Method Setting Register (EIEDG)".
		if( trigger_prm == LOW_LEVEL || trigger_prm == HIGH_LEVEL ) {
			dd_exiu_set_eiedg_level(NULL, ch_num);
		}
		else if( trigger_prm == FALLING_EDGE || trigger_prm == RISING_EDGE ) {
			dd_exiu_set_eiedg_edge(NULL, ch_num);
		}
		else {
			Ddim_Print(("Error Trigger Prameter !!\n"));
			return;
		}
		
		// Clear all the interrupts requests by writing to the "Interrupt Clear Register (EIREQCLR)".
		dd_exiu_set_eireqclr_ch(NULL, ch_num);
		
		// In order to release the mask on the interrupt ports, set the "Interrupt Masking Register (EIMASK)".
		dd_exiu_set_eimask_release(NULL, ch_num);
	}
    @endcode
@}*/

#ifdef __cplusplus
}
#endif

#endif /* __DD_EXIU_H__ */
