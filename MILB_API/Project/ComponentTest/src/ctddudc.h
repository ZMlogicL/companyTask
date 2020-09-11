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

#ifndef __CT_DD_UDC_H__
#define __CT_DD_UDC_H__

#include <klib.h>
#include "ddtop.h"

#define CT_TYPE_DD_UDC                  (ct_dd_udc_get_type())
#define CT_DD_UDC(obj)                  (K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUdc)) 
#define CT_IS_DD_UDC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UDC)) 

typedef struct                          _CtDdUdc CtDdUdc;
typedef struct                          _CtDdUdcPrivate CtDdUdcPrivate;

#define CtDdUdc_D_CT_DD_UDC_CH0_AIN		(DdTop_GPIO_PF2)
#define CtDdUdc_D_CT_DD_UDC_CH0_BIN		(DdTop_GPIO_PF0)
#define CtDdUdc_D_CT_DD_UDC_CH0_ZIN		(DdTop_GPIO_PE1)
#define CtDdUdc_D_CT_DD_UDC_CH1_AIN		(DdTop_GPIO_PF1)
#define CtDdUdc_D_CT_DD_UDC_CH1_BIN		(DdTop_GPIO_P87)
#define CtDdUdc_D_CT_DD_UDC_CH1_ZIN		(DdTop_GPIO_PE3)
#define CtDdUdc_D_CT_DD_UDC_CH2_AIN		(DdTop_GPIO_PE0)
#define CtDdUdc_D_CT_DD_UDC_CH2_BIN		(DdTop_GPIO_PE1)
#define CtDdUdc_D_CT_DD_UDC_CH3_AIN		(DdTop_GPIO_PE2)
#define CtDdUdc_D_CT_DD_UDC_CH3_BIN		(DdTop_GPIO_PE3)
#define CtDdUdc_D_CT_DD_UDC_CH4_AIN		(DdTop_GPIO_PE4)
#define CtDdUdc_D_CT_DD_UDC_CH4_BIN		(DdTop_GPIO_PE5)
#define CtDdUdc_D_CT_DD_UDC_CH5_AIN		(DdTop_GPIO_PM0)
#define CtDdUdc_D_CT_DD_UDC_CH5_BIN		(DdTop_GPIO_PP3)

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Input port kind of UDC
typedef enum {
	CtDdUdc_E_CT_DD_UDC_TRG_KIND_AIN = 0,	// AIN
	CtDdUdc_E_CT_DD_UDC_TRG_KIND_BIN,		// BIN
	CtDdUdc_E_CT_DD_UDC_TRG_KIND_ZIN,		// ZIN
	CtDdUdc_E_CT_DD_UDC_TRG_KIND_END		// End of enum
} CtDdUdcTrgKind;

// Kind of general-purpose port register
typedef enum {
	CtDdUdc_E_CT_DD_UDC_PORT_KIND_PDR = 0,	// PDR
	CtDdUdc_E_CT_DD_UDC_PORT_KIND_DDR,		// DDR
	CtDdUdc_E_CT_DD_UDC_PORT_KIND_EPCR,		// EPCR
	CtDdUdc_E_CT_DD_UDC_PORT_KIND_END		// End of enum
} CtDdUdcPortKind;

struct _CtDdUdc {
    KObject parent;
    kuchar ch;
    kint32 i;
    kuchar tmrCh;
    kuchar tmrChA;
    kuchar tmrChB;
    // Control data of virtual AIN input.
    kuchar	gctDdUdcAinCh;		// Target UDC channel number
    // Control data of virtual BIN input.
    kuchar	gctDdUdcBinCh;		// Target UDC channel number
};

KConstType  ct_dd_udc_get_type(void);

kint32      ct_dd_udc_set_port(CtDdUdc *self, CtDdUdcTrgKind trg, CtDdUdcPortKind port, kuchar writeVal);
void        ct_dd_udc_callback(kuchar ch, kint32 factor);//
void        ct_dd_udc_callback_sub(kuchar ch, kint32 factor);//
void        ct_dd_udc_utility_callback(kuchar ch);//
void        ct_dd_udc_observe_udcr(void);//
kint32      ct_dd_udc_start_timer32(CtDdUdc *self, kulong interval, VP_CALLBACK cbFunc);
void        ct_dd_udc_stop_timer32(CtDdUdc *self);
kint32      ct_dd_udc_start_virtual_ain(CtDdUdc *self, kuchar udcCh, kulong tmrInterval);
void        ct_dd_udc_stop_virtual_ain(CtDdUdc *self);
kint32      ct_dd_udc_start_virtual_bin(CtDdUdc *self, kuchar udcCh, kulong tmrInterval);
void        ct_dd_udc_stop_virtual_bin(CtDdUdc *self);
void        ct_dd_udc_print_crl_common(CtDdUdc *self, T_DD_UDC_CTRL_CMN const* const udcCrl);
void        ct_dd_udc_print_clk_info(CtDdUdc *self);
void        ct_dd_udc_print_trg_info(CtDdUdc *self);
void        ct_dd_udc_print_reg_info(CtDdUdc *self);
kuchar      ct_dd_udc_get_ain_ch(CtDdUdc *self);
kuchar      ct_dd_udc_get_bin_ch(CtDdUdc *self);

CtDdUdc*    ct_dd_udc_new(void);

#endif /* __CT_DD_UDC_H__ */
