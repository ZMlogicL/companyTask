/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-07
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_HDMI_H__
#define __IM_HDMI_H__


#include <stdio.h>
#include <glib-object.h>
#include "driver_common.h"
#include "imhdmistruct.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_HDMI			(im_hdmi_get_type ())
#define IM_HDMI(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_HDMI, ImHdmi))
#define IM_HDMI_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_HDMI, ImHdmiClass))
#define IM_IS_HDMI(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_HDMI))
#define IM_IS_HDMI_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_HDMI))
#define IM_HDMI_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_HDMI, ImHdmiClass))

/*----------------------------------------------------------------------	*/
/* Definition																	*/
/*----------------------------------------------------------------------	*/
// Interrupt flag.
// i2cm.
#define ImHdmi_D_IM_HDMI_INT_FLG_I2CM							(0x00000001)
// i2cmphy.
#define ImHdmi_D_IM_HDMI_INT_FLG_I2CM							(0x00000002)
// phy_lock.
#define ImHdmi_D_IM_HDMI_INT_FLG_I2CM							(0x00000004)

// PHY Register Address (Offset).
// PWRCTRL.
#define ImHdmi_D_IM_HDMI_INT_FLG_I2CM							(0x00)
// OPMODE_PLLCFG.
#define ImHdmi_D_IM_HDMI_PHY_ADR_OPMODE_PLLCFG		(0x06)
// CKSYMTXCTRL.
#define ImHdmi_D_IM_HDMI_PHY_ADR_CKSYMTXCTRL			(0x09)
// VLEVCTRL.
#define ImHdmi_D_IM_HDMI_PHY_ADR_VLEVCTRL					(0x0E)
// PLLCURRCTRL.
#define ImHdmi_D_IM_HDMI_PHY_ADR_PLLCURRCTRL			(0x10)
// PLLCTRL.
#define ImHdmi_D_IM_HDMI_PHY_ADR_PLLCTRL						(0x14)
// PLLGMPCTRL.
#define ImHdmi_D_IM_HDMI_PHY_ADR_PLLGMPCTRL				(0x15)
// TXTERM.
#define ImHdmi_D_IM_HDMI_PHY_ADR_TXTERM						(0x19)

/*----------------------------------------------------------------------	*/
/* Definition																	*/
/*----------------------------------------------------------------------	*/
//---------------------- driver  section -------------------------------
// Return value of ARM watchdog timer processing result.
/**< Input Parameter Error */
#define ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR				(D_IM_HDMI | D_DDIM_INPUT_PARAM_ERROR)
/**< No receive */
#define ImHdmi_D_IM_HDMI_NO_RECEIVE								(D_IM_HDMI | D_DDIM_NO_RECEIVE)
/**< Time out */
#define ImHdmi_D_IM_HDMI_TIMEOUT									(D_IM_HDMI | D_DDIM_TIMEOUT)
/**< System error */
#define ImHdmi_D_IM_HDMI_NG												(D_IM_HDMI | D_DDIM_SYSTEM_ERROR)


// Frame Composer SPD packet Data number.
/**< Vendor Name:8.		*/
#define ImHdmi_D_IM_HDMI_FC_SPD_VENDER_NAME_NUM	(8)
/**< Product Name:16.	*/
#define ImHdmi_D_IM_HDMI_FC_SPD_PRO_NAME_NUM			(16)

// Frame Composer VSD packet Data number.
/**< IEEE:3.		*/
#define ImHdmi_D_IM_HDMI_FC_VSD_IEEE_DATA_NUM			(3)
/**< Payload:24.	*/
#define ImHdmi_D_IM_HDMI_FC_VSD_PAYLOAD_NUM				(24)

// General-purpose definition of register value (Effectiveness selection)
/**< OFF	*/
#define ImHdmi_D_IM_HDMI_ENABLE_OFF								(0)
/**< ON		*/
#define ImHdmi_D_IM_HDMI_ENABLE_ON								(1)

// definition of register value (Active Low/High)
/**< Acvtice Low	*/
#define ImHdmi_D_IM_HDMI_ACTIVE_LOW								(0)
/**< Acvtice High	*/
#define ImHdmi_D_IM_HDMI_ACTIVE_HIGH								(1)

// definition of register value (Video Mode)
/**< HDMI Video Mode	*/
#define ImHdmi_D_IM_HDMI_VIDEO_MODE_HDMI					(0x20)
/**< 3D Video Mode		*/
#define ImHdmi_D_IM_HDMI_VIDEO_MODE_3D						(0x40)

// fcInvidconf Register - inIP (Input video mode)
/**< Progressive	*/
#define ImHdmi_D_IM_HDMI_IN_I_P_PROGRESSIVE					(0)
/**< Interlaced		*/
#define ImHdmi_D_IM_HDMI_IN_I_P_INTERLACED					(1)

// fcInvidconf Register - dviModez (DVI mode setected)
/**< DVI mode selected	*/
#define ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI						(0)
/**< HDMI mode selected	*/
#define ImHdmi_D_IM_HDMI_DVI_MODEZ_HDMI						(1)

// mc_phyrstz Register - phyrstz (HDMI Source PHY active high reset control)
/**< Reset cancel.	*/
#define ImHdmi_D_IM_HDMI_PHYRSTZ_CANCEL						(0)
/**< Reset.			*/
#define ImHdmi_D_IM_HDMI_PHYRSTZ_RESET							(1)

/**< PHY Register number	*/
#define ImHdmi_D_IM_HDMI_PHY_REG_NUM							(8)

/* HDMI Video Output format */
/**< RGB */
#define ImHdmi_D_IM_HDMI_OUT_RGB									(0x00)
/**< YCbCr420 */
#define ImHdmi_D_IM_HDMI_OUT_YCC420								(0x10)
/**< YCbCr422 */
#define ImHdmi_D_IM_HDMI_OUT_YCC422								(0x20)
/**< YCbCr444 */
#define ImHdmi_D_IM_HDMI_OUT_YCC444								(0x40)


/**< Type is defined to Callback function pointer */
typedef void	(*VP_HDMI_CALLBACK)(guchar);


typedef struct _ImHdmi					ImHdmi;
typedef struct _ImHdmiClass			ImHdmiClass;
typedef struct _ImHdmiPrivate 		ImHdmiPrivate;


struct _ImHdmi
{
	GObject parent;
	DdimUserCustomTest *ddimUserCustomTest;
	ImHdmiEnum *imHdmiEnum;
};

struct _ImHdmiClass
{
	GObjectClass parentClass;
};


/*----------------------------------------------------------------------	*/
/* Grobal Data																*/
/*----------------------------------------------------------------------	*/
// Nothing Special

/*----------------------------------------------------------------------	*/
/* Macro																			*/
/*----------------------------------------------------------------------	*/
// Nothing Special

/*----------------------------------------------------------------------	*/
/* Function																		*/
/*----------------------------------------------------------------------	*/
GType						im_hdmi_get_type(void)	G_GNUC_CONST;
ImHdmi*				im_hdmi_new(void);
void 						im_hdmi_pclk_on(ImHdmi *self);
void 						im_hdmi_pclk_off(ImHdmi *self);
gint32 					im_hdmi_configure_pll(ImHdmi *self, ThdmiPllConfig const *const config);
gint32 					im_hdmi_configure_infoframes(ImHdmi *self, ThdmiInfoFrames const *const config);
void 						im_hdmi_check_interrupt_fc(ImHdmi *self);
void 						im_hdmi_check_interrupt_as(ImHdmi *self);
void 						im_hdmi_check_interrupt_phy(ImHdmi *self);
void 						im_hdmi_check_interrupt_i2cm(ImHdmi *self);
void 						im_hdmi_check_interrupt_cec(ImHdmi *self);
void 						im_hdmi_check_interrupt_vp(ImHdmi *self);
void 						im_hdmi_check_interrupt_i2cmphy(ImHdmi *self);
gint32 					im_hdmi_phy_read(ImHdmi *self, guchar address, gushort *data);


#ifdef __cplusplus
}
#endif

G_END_DECLS


#endif /* __IM_HDMI_H__ */
/*@}*/
/*@}*/

/************************************************************************/
/* Sample Code															*/
/************************************************************************/
/** @weakgroup im_hdmi
@{
<hr>
@section Hdmi_Sample_Basic		Sample of HDMI(Basic sequence)
@code
// SAMPLE CODE //
void im_hdmi_sample_initialize(void)
{
	gint32 ret = D_DDIM_OK;
	ThdmiPllConfig	pllConfig;
	ThdmiI2cmConfig	i2cmConfig;
	guchar					read_sinks_e_edid[8];
	ImHdmiStruct			ctrl;

	// PLL Configuration.
	pllConfig.vpPrCd.desiredPrFactor	= 0;
	pllConfig.vpPrCd.colorDepth			= ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT;
	pllConfig.phyI2cmAddress				= 0x00;
	pllConfig.phyI2cmDatao[0]			= 0x00;
	pllConfig.phyI2cmDatao[0]			= 0x00;

	// Init.
	ret = im_hdmi_enum_init();
	if (ret != D_DDIM_OK){
		// NG.
		return;
	}

	// i2cm paramter.
	i2cmConfig.i2cmAddress	= 0x00;
	i2cmConfig.i2cmSegaddr	= 0x00;
	i2cmConfig.i2cmSegptr		= 0x00;
	i2cmConfig.i2cmOperation	= ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD;

	// Read Sink’s E-EDID.
	ret = im_hdmi_enum_read_sinks_e_edid(&i2cmConfig, read_sinks_e_edid);
	if (ret != D_DDIM_OK){
		// NG.
		return;
	}

	// Read data check.

	// Configuration.
	ctrl.videoInputMapping						= ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT;
	ctrl.vsyncInPolarity							= ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ctrl.hsyncInPolarity							= ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ctrl.deInPolarity								= ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ctrl.dviModez									= ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI;
	ctrl.rVBlankInOsc							= ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ctrl.inIP										= ImHdmi_D_IM_HDMI_IN_I_P_PROGRESSIVE;
	ctrl.hInActiv									= 0x280;
	ctrl.vInActiv									= 0x1E0;
	ctrl.fcInvact2d;								= 0x1E0;
	ctrl.fcActspcHdlrCfg.actspcHdlrEn			= ImHdmi_D_IM_HDMI_ENABLE_OFF;
	ctrl.fcActspcHdlrCfg.actspcHdlrTgl			= ImHdmi_D_IM_HDMI_ENABLE_OFF;
	ctrl.fcInhblank								= 0xA0;
	ctrl.fcInvblank								= 0x2D;
	ctrl.fcHsyncindelay							= 0x10;
	ctrl.fcHsyncinwidth							= 0x60;
	ctrl.fcVsyncindelay							= 0x02;
	ctrl.fcVsyncinwidth							= 0x02;
	// PLL
	ctrl.pllConfig.vpPrCd.desiredPrFactor		= 0;
	ctrl.pllConfig.vpPrCd.colorDepth			= ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT;
	ctrl.pllConfig.phyI2cmAddress				= 0;
	ctrl.pllConfig.phyI2cmDatao[0]				= 0;
	ctrl.pllConfig.phyI2cmDatao[0]				= 0;

	// When DVI mode (ctrl.dviModez=ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI),
	// Audio config and Infoframes setting is omitted.

	ret = im_hdmi_enum_ctrl(&ctrl);
	if (ret != D_DDIM_OK){
		// NG.
		return;
	}
}
@endcode
@}*//* end of im_hdmi*/
