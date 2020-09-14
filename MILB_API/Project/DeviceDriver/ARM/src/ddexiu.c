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
 * @file		dd_exiu.c
 * @brief		EXIU (External Interrupt Unit) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include "ddexiu.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdExiu, dd_exiu);

#define DD_EXIU_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdExiuPrivate, DD_TYPE_EXIU))


struct _DdExiuPrivate
{

};


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
kulong gDDExiuSpinLock __attribute__((section(".LOCK_SECTION"), aligned(64)));

/**
DECLS
*/
/**
IMPL
*/
static void dd_exiu_constructor(DdExiu *self)
{
//	DdExiuPrivate *priv = DD_EXIU_GET_PRIVATE(self);
}

static void dd_exiu_destructor(DdExiu *self)
{
//	DdExiuPrivate *priv = DD_EXIU_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Get Interrupt Mask
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eimask(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	*val = (1 & (ioExiu.eimask.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get Interrupt Source Select
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eisrcsel(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	*val = (1 & (ioExiu.eisrcsel.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get Internal Interrupt Request Status
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eireqsta(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif

	*val = (1 & (ioExiu.eireqsta.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get Raw Interrupt Request Status
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eirawreqsta(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	*val = (1 & (ioExiu.eirawreqsta.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get External Interrupt Level Setting
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eilvl(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif

	*val = (1 & (ioExiu.eilvl.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get Interrupt Detection Method Setting
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eiedg(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	*val = (1 & (ioExiu.eiedg.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Get Software Interrupt
 * @param	kuint32 ch, kuint32* val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_get_eisir(DdExiu *self, kuint32 ch, kuint32* val)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
	if (val == NULL) {
		Ddim_Assertion(("EXIU: input param error. [val] = NULL\n"));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	*val = (1 & (ioExiu.eisir.word >> (ch - C_CH_MIN)));
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Mask Release Select
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eimask_release(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eimask.word &= ~(1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Mask Select
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_dd_exiu_set_eimask_mask(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eimask.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt is Mask or Release
 * @param	kuint32 val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eimask_val(DdExiu *self, kuint32 val)
{
#ifdef CO_PARAM_CHECK
	if (val > C_VAL_MAX) {
		Ddim_Assertion(("EXIU: input param error. [val] = %08x\n", val));
		return C_INPUT_PARAM_ERR;
	}
#endif

	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eimask.word = (val);
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt External Source Select
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eisrcsel_ext(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eisrcsel.word &= ~(1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Sofware Source Select
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eisrcsel_soft(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eisrcsel.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Cleared Channel
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eireqclr_ch(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif

	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eireqclr.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Cleared Value
 * @param	kuint32 val
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eireqclr_val(DdExiu *self, kuint32 val)
{
#ifdef CO_PARAM_CHECK
	if (val > C_VAL_MAX) {
		Ddim_Assertion(("EXIU: input param error. [val] = %08x\n", val));
		return C_INPUT_PARAM_ERR;
	}
#endif

	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eireqclr.word = (val);
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	External Interrupt Low level or Falling edge
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eilvl_lo(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eilvl.word &= ~(1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	External Interrupt High level or Rising edge
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eilvl_hi(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eilvl.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Level Detection Setting
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eiedg_level(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif

	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eiedg.word &= ~(1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt Edge Detection Setting
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eiedg_edge(DdExiu * self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eiedg.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

/**
 * @brief	Set Software Interrupt Generate
 * @param	kuint32 ch
 * @return	D_DDIM_OK/C_INPUT_PARAM_ERR
 */
kint32 dd_exiu_set_eisir_generate(DdExiu *self, kuint32 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch < C_CH_MIN || ch > C_CH_MAX) {
		Ddim_Assertion(("EXIU: input param error. [ch] = %d\n", ch));
		return C_INPUT_PARAM_ERR;
	}
#endif
	
	DD_ARM_CRITICAL_SECTION_START(gDDExiuSpinLock);
	ioExiu.eisir.word |= (1U << (ch - C_CH_MIN));
	DD_ARM_CRITICAL_SECTION_END(gDDExiuSpinLock);
	return D_DDIM_OK;
}

DdExiu* dd_exiu_new(void)
{
	DdExiu* self = k_object_new_with_private(DD_TYPE_EXIU, sizeof(DdExiuPrivate));

	return self;
}
