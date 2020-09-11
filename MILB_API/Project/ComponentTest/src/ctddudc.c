/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdUdc类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
#include "ddimusercustom.h"
#include "peripheral.h"
#include "dd_udc.h"
#include "ddtop.h"
#include "dd_tmr32.h"
#include "stdlib.h"
#include "string.h"

#include "ddgic.h"
#include "ctddudc1.h"
#include "ctddudc.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdUdc, ct_dd_udc);
#define CT_DD_UDC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUdcPrivate,CT_TYPE_DD_UDC))

struct _CtDdUdcPrivate {
	CtDdUdc *cdUdc;
};

// /*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Control data of virtual AIN input
static DdimUserCustom_SYSTIM	S_GCT_DD_UDC_TIM_A_STA;
static DdimUserCustom_SYSTIM	S_GCT_DD_UDC_TIM_A_END;

// Control data of virtual BIN input.
static DdimUserCustom_SYSTIM	S_GCT_DD_UDC_TIM_B_STA;
static DdimUserCustom_SYSTIM	S_GCT_DD_UDC_TIM_B_END;

//Save system time for UDC utility function
static DdimUserCustom_SYSTIM	S_GCT_DD_UDC_TIM_UTIL_END;

/*DECLS*/

static kint32 	ctDdUdcGetPdr(kuchar ch, CtDdUdcTrgKind trg, kuchar* val);
static void 	ctDdUdcSinHandler(void);
static void 	ctDdUdcBinHandler(void);

static void ct_dd_udc_constructor(CtDdUdc *self) 
{
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);
	priv->cdUdc = ct_dd_udc_new();
}

static void ct_dd_udc_destructor(CtDdUdc *self)
{
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);
	if(priv->cdUdc){
		k_object_unref(priv->cdUdc);
	}
	priv->cdUdc = NULL;
}

/*IMPL*/

/*
Get value of PDR register value.
*/
static kint32 ctDdUdcGetPdr(kuchar ch, CtDdUdcTrgKind trg, kuchar* val)
{
	DdTopfour *ddTop4 = dd_topfour_new();
	switch (ch) {
		case D_DD_UDC_CH0:
			// UDC ch0
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_BIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_ZIN:
					// ZIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_ZIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH1:
			// UDC ch1
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_BIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_ZIN:
					// ZIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_ZIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH2:
			// UDC ch2
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH2_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_BIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH3:
			// UDC ch3
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_BIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH4:
			// UDC ch4
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_BIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH5:
			// UDC ch5
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_AIN, val);
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					dd_topfour_get_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_BIN, val);
					break;

				default:
					// Parameter error.
					Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		default:
			// Parameter error.
			Ddim_Print(("ct_dd_udc_get_pdr(): Parameter error. ch=%d, trg=%d\n", ch, trg));
			return D_DD_UDC_INPUT_PARAM_ERROR;
	}
	k_object_unref(ddTop4);
	ddTop4 = NULL;
	return D_DDIM_OK;
}

/**
Callback function for virtual AIN control.
*/
static void ctDdUdcSinHandler(void)
{
	DdimUserCustom_ER	ercd;
	kuchar 				pdr;
	CtDdUdc *			cdUdc = ct_dd_udc_new();

	ercd = DDIM_User_Get_Tim(&S_GCT_DD_UDC_TIM_A_END);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_ain_handler(): get_tim NG. ercd=%d\n", ercd));
		return;
	}

	ercd = (DdimUserCustom_ER)ctDdUdcGetPdr(cdUdc->gctDdUdcAinCh, CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN, &pdr);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_ain_handler(): ct_dd_udc_get_pdr NG. ercd=%d\n", ercd));
		return;
	}

	if (pdr == 0) {
		// AIN -> High
		pdr = 1;
	}
	else {
		// AIN -> Low
		pdr = 0;
	}
	cdUdc->ch = cdUdc->gctDdUdcAinCh;
	ercd = (DdimUserCustom_ER)ct_dd_udc_set_port(cdUdc, CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN, 
			CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR, pdr);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_ain_handler(): ct_dd_udc_set_port NG. ercd=%d\n", ercd));
		return;
	}

	Ddim_Print((
		"[AIN] (Ch=%d) (TIM=%lu) (UDCR=%d) (PDR=%d)\n",
		cdUdc->gctDdUdcAinCh,
		(kulong)(S_GCT_DD_UDC_TIM_A_END - S_GCT_DD_UDC_TIM_A_STA), 
		Dd_UDC_Get_UDCR_Counter(cdUdc->gctDdUdcAinCh), 
		pdr
	));
	S_GCT_DD_UDC_TIM_A_STA = S_GCT_DD_UDC_TIM_A_END;
	k_object_unref(cdUdc);
	cdUdc = NULL;
}

/**
Callback function for virtual BIN control.
*/
static void ctDdUdcBinHandler(void)
{
	DdimUserCustom_ER	ercd;
	kuchar 				pdr;
	CtDdUdc *			cdUdc = ct_dd_udc_new();

	ercd = DDIM_User_Get_Tim(&S_GCT_DD_UDC_TIM_B_END);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_bin_handler(): get_tim NG. ercd=%d\n", ercd));
		return;
	}

	ercd = (DdimUserCustom_ER)ctDdUdcGetPdr(cdUdc->gctDdUdcBinCh, CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN, &pdr);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_bin_handler(): ct_dd_udc_get_pdr NG. ercd=%d\n", ercd));
		return;
	}

	if (pdr == 0) {
		// BIN -> High z
		pdr = 1;
	}
	else {
		// BIN -> Low
		pdr = 0;
	}
	cdUdc->ch = cdUdc->gctDdUdcBinCh;
	ercd = (DdimUserCustom_ER)ct_dd_udc_set_port(cdUdc, CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN, 
			CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR, pdr);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_bin_handler(): ct_dd_udc_set_port NG. ercd=%d\n", ercd));
		return;
	}

	Ddim_Print((
		"[BIN] (Ch=%d) (TIM=%lu) (UDCR=%d) (PDR=%d)\n",
		cdUdc->gctDdUdcBinCh,
		(kulong)(S_GCT_DD_UDC_TIM_B_END - S_GCT_DD_UDC_TIM_B_STA), 
		Dd_UDC_Get_UDCR_Counter(cdUdc->gctDdUdcBinCh), 
		pdr
	));
	S_GCT_DD_UDC_TIM_B_STA = S_GCT_DD_UDC_TIM_B_END;
	k_object_unref(cdUdc);
	cdUdc = NULL;
}

/*PUBLIC*/

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
/*
Set value of general-purpose port control register.
*/
kint32 ct_dd_udc_set_port(CtDdUdc *self, CtDdUdcTrgKind trg, CtDdUdcPortKind port, kuchar writeVal)
{
	DdTopthree 	*ddTop3 = dd_topthree_new();
	DdTopfour 	*ddTop4 = dd_topfour_new();
	switch (self->ch) {
		case D_DD_UDC_CH0:
			// UDC ch0
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH0_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH0_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_BIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_ZIN:
					// ZIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_ZIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH0_ZIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//★						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH0_ZIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				default:
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH1:
			// UDC ch1
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH1_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
/*★*/					dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH1_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_BIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_ZIN:
					// ZIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_ZIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH1_ZIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH1_ZIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				default: 
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH2:
			// UDC ch2
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH2_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH2_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH2_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH2_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH2_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//★						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH2_BIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				default:
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH3:
			// UDC ch3
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH3_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH3_BIN, writeVal);
					}
					else {
						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH3_BIN, writeVal);
					}
					break;

				default:
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH4:
			// UDC ch4
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH4_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH4_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH4_BIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				default:
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		case D_DD_UDC_CH5:
			// UDC ch5
			switch (trg) {
				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN:
					// AIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						//IO_CHIPTOP.PDR.bit.PR2 = writeVal;
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						//IO_CHIPTOP.DDR.bit.PR2 = writeVal;
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH5_AIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
//						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_AIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				case CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN:
					// BIN
					if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR) {
						//IO_CHIPTOP.PDR.bit.PR3 = writeVal;
						dd_toptwo_set_gpio_status(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR) {
						//IO_CHIPTOP.DDR.bit.PR3 = writeVal;
						dd_topthree_set_gpio_direction(ddTop3, CtDdUdc_D_CT_DD_UDC_CH5_BIN, writeVal);
					}
					else if (port == CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR) {
						//IO_CHIPTOP.EPCR.bit.PR3 = writeVal;
						dd_topfour_set_gpio_function(ddTop4, CtDdUdc_D_CT_DD_UDC_CH5_BIN, writeVal);
					}
					else {
						;	// DO NOTHING
					}
					break;

				default:
					// Parameter error.
					Ddim_Print((
						"ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
					return D_DD_UDC_INPUT_PARAM_ERROR;
			}
			break;

		default:
			// Parameter error.
			Ddim_Print(("ct_dd_udc_set_port(): Parameter error. ch=%d, trg=%d\n", self->ch, trg));
			return D_DD_UDC_INPUT_PARAM_ERROR;
	}
	k_object_unref(ddTop3);
	k_object_unref(ddTop4);
	ddTop3 = NULL;
	ddTop4 = NULL;
	return D_DDIM_OK;
}

/**
Callback function for interrupt of UDC.
*/
void ct_dd_udc_callback(kuchar ch, kint32 factor)
{
	kushort udcr;

	// Get UDCR
	udcr = Dd_UDC_Get_UDCR_Counter(ch);

	switch (factor) {
		case D_DD_UDC_CMPF_OK:
			// Compare
			Ddim_Print(("[UDC#%d INT] D_DD_UDC_CMPF_OK. UDCR=%d\n", ch, udcr));
			break;

		case D_DD_UDC_OVER_FLOW:
			// Overflow
			Ddim_Print(("[UDC#%d INT] D_DD_UDC_OVER_FLOW. UDCR=%d\n", ch, udcr));
			break;

		case D_DD_UDC_UNDER_FLOW:
			// Underflow
			Ddim_Print(("[UDC#%d INT] D_DD_UDC_UNDER_FLOW. UDCR=%d\n", ch, udcr));
			break;

		case D_DD_UDC_COUNT_DIRECTION:
			// Count direction change
			Ddim_Print(("[UDC#%d INT] D_DD_UDC_COUNT_DIRECTION. UDCR=%d DIR=%d\n", ch, 
					udcr, Dd_UDC_Get_Up_Down_Flg(ch)));
			break;

		default:
			// Unknown factor
			Ddim_Print(("[UDC#%d INT] Unknown factor. factor=%d UDCR=%d\n", ch, factor, udcr));
			break;
	}
}

/**
Callback sub function for interrupt of UDC.
*/
void ct_dd_udc_callback_sub(kuchar ch, kint32 factor)
{
	Ddim_Print(("[UDC#%d INT] ct_dd_udc_callback_sub() Start!!\n", ch));
	ct_dd_udc_callback(ch, factor);
	Ddim_Print(("[UDC#%d INT] ct_dd_udc_callback_sub() End!!\n", ch));
}

/**
Callback function for interrupt of UDC utility function
*/
void ct_dd_udc_utility_callback(kuchar ch)
{
	DdimUserCustom_ER	ercd;
	CtDdUdc1 			*cdUdc1 = ct_dd_udc1_new();

	ercd = DDIM_User_Get_Tim(&S_GCT_DD_UDC_TIM_UTIL_END);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("UDC utility function: get end time NG. ercd=%d\n", ercd));
		return;
	}

	Ddim_Print(("Stop utility function\n"));
	Ddim_Print(("Measuring Time(msec) = %lu\n",
		(kulong)(S_GCT_DD_UDC_TIM_UTIL_END - ct_dd_udc1_get_tim_util_sta(cdUdc1))))

	return;
	k_object_unref(cdUdc1);
	cdUdc1 = NULL;
}

/**
Callback function for UDCR observer.
*/
void ct_dd_udc_observe_udcr(void)
{
	CtDdUdc1 *cdUdc1 = ct_dd_udc1_new();
	Ddim_Print((
		"[Observer] (Ch=%d) (UDCR=%d)\n", 
		ct_dd_udc1_get_obs_ch(cdUdc1), 
		Dd_UDC_Get_UDCR_Counter(ct_dd_udc1_get_obs_ch(cdUdc1))
	));
	k_object_unref(cdUdc1);
	cdUdc1 = NULL;
}

/**
Start 32bit timer
*/
kint32 ct_dd_udc_start_timer32(CtDdUdc *self, kulong interval, VP_CALLBACK cbFunc)
{
	kint32 ercd;

	// Timer32 GIC.
	dd_gic_ctrl(DdGic_INTID_TIMER_CH5_INT,1,C_PRI30,2);
	dd_gic_ctrl(DdGic_INTID_TIMER_CH6_INT,1,C_PRI30,2);
	dd_gic_ctrl(DdGic_INTID_TIMER_CH7_INT,1,C_PRI30,2);
	
	// Timer32 open
	ercd = Dd_TMR32_Open((kuint32)self->tmrCh, DdimUserCustom_SEM_WAIT_FEVR);
	if(ercd != D_DDIM_OK) {
		Ddim_Print(("ct_dd_udc_start_timer32(): Dd_TMR32_Open(%d) NG. ercd=%d\n", self->tmrCh, ercd));
		return ercd;
	}

	// Timer32 setting
	ercd = Dd_TMR32_SetTimer(self->tmrCh, interval, cbFunc);
	if(ercd != D_DDIM_OK) {
		Ddim_Print((
			"ct_dd_udc_start_timer32(): Dd_TMR32_SetTimer(%d) NG. ercd=%d\n", self->tmrCh, ercd));
		return ercd;
	}

	// Start timer
	ercd = Dd_TMR32_StartReload(self->tmrCh);
	if(ercd != D_DDIM_OK) {
		Ddim_Print((
			"ct_dd_udc_start_timer32(): Dd_TMR32_StartReload(%d) NG. ercd=%d\n", self->tmrCh, ercd));
		return ercd;
	}
	return D_DDIM_OK;
}

/**
Stop 32bit timer
*/
void ct_dd_udc_stop_timer32(CtDdUdc *self)
{
	Dd_TMR32_Stop(self->tmrCh);
	Dd_TMR32_Close(self->tmrCh);
}

/**
Start virtual AIN input timer.
*/
kint32 ct_dd_udc_start_virtual_ain(CtDdUdc *self, kuchar udcCh, kulong tmrInterval)
{
	DdimUserCustom_ER	ercd;

	self->gctDdUdcAinCh = udcCh; // UDC channel number
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);

	// Start timer
	priv->cdUdc->tmrCh = self->tmrChA;
	ercd = (DdimUserCustom_ER)ct_dd_udc_start_timer32(
		priv->cdUdc, 
		tmrInterval, 
		ctDdUdcSinHandler
	);
	if (ercd != DdimUserCustom_E_OK) {
		// Timer execution error.
		Ddim_Print(("ct_dd_udc_start_virtual_ain(): ct_dd_udc_start_timer32 NG. ercd=%d\n", ercd));
		return((kint32)ercd);
	}
	// Save start time
	ercd = DDIM_User_Get_Tim(&S_GCT_DD_UDC_TIM_A_STA);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_start_virtual_ain(): get_tim NG. ercd=%d\n", ercd));
		return((kint32)ercd);
	}
	return D_DDIM_OK;
}

/**
Stop virtual AIN input timer.
*/
void ct_dd_udc_stop_virtual_ain(CtDdUdc *self)
{
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);
	priv->cdUdc->tmrCh = self->tmrChA;
	ct_dd_udc_stop_timer32(priv->cdUdc);
}

/**
Start virtual BIN input timer.
*/
kint32 ct_dd_udc_start_virtual_bin(CtDdUdc *self, kuchar udcCh, kulong tmrInterval)
{
	DdimUserCustom_ER	ercd;
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);

	// Check UDCTRG setting
	if ((DdTopothree_GET_PERSEL2_UDCTRG() == 1) && ((udcCh == 2) || (udcCh == 3))) {
		Ddim_Print((
			"ct_dd_udc_start_virtual_bin(): UDCTRG setting error. BIN can't use in ch2~3.\n"));
		return D_DD_UDC_INPUT_PARAM_ERROR;
	}

	self->gctDdUdcBinCh = udcCh; // UDC channel number

	// Start timer
	priv->cdUdc->tmrCh = self->tmrChB;
	ercd = (DdimUserCustom_ER)ct_dd_udc_start_timer32(
		priv->cdUdc, 
		tmrInterval, 
		ctDdUdcBinHandler
	);
	if (ercd !=DdimUserCustom_E_OK) {
		// Timer execution error.
		Ddim_Print(("ct_dd_udc_start_virtual_bin(): ct_dd_udc_start_timer32 NG. ercd=%d\n", ercd));
		return((kint32)ercd);
	}
	// Save start time
	ercd = DDIM_User_Get_Tim(&S_GCT_DD_UDC_TIM_B_STA);
	if (ercd != DdimUserCustom_E_OK) {
		Ddim_Print(("ct_dd_udc_start_virtual_bin(): get_tim NG. ercd=%d\n", ercd));
		return((kint32)ercd);
	}
	return D_DDIM_OK;
}

/**
Stop virtual BIN input timer.
*/
void ct_dd_udc_stop_virtual_bin(CtDdUdc *self)
{
	CtDdUdcPrivate *priv = CT_DD_UDC_GET_PRIVATE(self);
	priv->cdUdc->tmrCh = self->tmrChB;
	ct_dd_udc_stop_timer32(priv->cdUdc);
}

/**
Print T_DD_UDC_CTRL_CMN data.
*/
void ct_dd_udc_print_crl_common(CtDdUdc *self, T_DD_UDC_CTRL_CMN const* const udcCrl)
{
	Ddim_Print(("---- T_DD_UDC_CTRL_CMN(Ch%d) ----\n", self->ch));
	Ddim_Print(("UDCR     = 0x%x\n", udcCrl->udcr		));
	Ddim_Print(("RCR      = 0x%x\n", udcCrl->rcr		));
	Ddim_Print(("CCR.CMS  = 0x%x\n", udcCrl->count_mode	));
	Ddim_Print(("CCR.UCRE = 0x%x\n", udcCrl->comp_clear	));
	Ddim_Print(("CCR.RLDE = 0x%x\n", udcCrl->reload		));
	Ddim_Print(("CCR.CGSC = 0x%x\n", udcCrl->zin_mode	));
	Ddim_Print(("CCR.CGE  = 0x%x\n", udcCrl->zin_edge	));
	Ddim_Print(("CSR.CITE = 0x%x\n", udcCrl->cmp_int	));
	Ddim_Print(("CSR.UDIE = 0x%x\n", udcCrl->under_over	));
	Ddim_Print(("CCR.CFIE = 0x%x\n", udcCrl->cnt_dir_int));
	Ddim_Print(("udcCrl.pCallBack = %p\n", udcCrl->pCallBack));
	Ddim_Print(("---------------------------------\n"));
}

/**
Print RCLK status.
*/
void ct_dd_udc_print_clk_info(CtDdUdc *self)
{
	Ddim_Print(("==== Clock info ====\n"));
	Ddim_Print(("RCLK=%d\n", DdTopone_Get_CLKSEL1_RCLK()));
//	Ddim_Print(("RCK=%d\n", Dd_Top_Get_CLKSTOP_RCK()));
	Ddim_Print(("====================\n"));
}

/**
Print triger status of all channels.
*/
void ct_dd_udc_print_trg_info(CtDdUdc *self)
{
	Ddim_Print(("==== Trigger info ====\n"));
	for (self->i = 0; self->i < 6; self->i++) {
		Ddim_Print(("IO_PERI.UDC[%d].CSR.bit.__CSTR=%d\n", 
			self->i, ioPeri.udc[self->i].csr.bit.__cstr));
	}
	Ddim_Print(("======================\n"));
}

void ct_dd_udc_print_reg_info(CtDdUdc *self)
{
	Ddim_Print(("==== UDC reg info ====\n"));
	for (self->i = 0; self->i < 6; self->i++) {
		Ddim_Print(("IO_PERI.UDC[%d].CCR.word=%lu\n", self->i, ioPeri.udc[self->i].ccr.word));
		Ddim_Print(("IO_PERI.UDC[%d].CSR.word=%lu\n", self->i, ioPeri.udc[self->i].csr.word));
		Ddim_Print(("IO_PERI.UDC[%d].UDCR=%lu\n", self->i, ioPeri.udc[self->i].udcr.word));
	}
	Ddim_Print(("======================\n"));
}

kuchar ct_dd_udc_get_ain_ch(CtDdUdc *self)
{
	return self->gctDdUdcAinCh;
}

kuchar ct_dd_udc_get_bin_ch(CtDdUdc *self)
{
	return self->gctDdUdcBinCh;
}

CtDdUdc *ct_dd_udc_new(void)
{
    CtDdUdc *self = k_object_new_with_private(CT_TYPE_DD_UDC, sizeof(CtDdUdcPrivate));
    return self;
}
