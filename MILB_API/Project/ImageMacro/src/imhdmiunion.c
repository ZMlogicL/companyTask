/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#include "jdsdisp3a.h"
#include "imhdmi.h"
#include "ddarm.h"
#include "imdisp.h"
#include "imhdmiunion.h"


G_DEFINE_TYPE(ImHdmiUnion, im_hdmi_union, G_TYPE_OBJECT);
#define IM_HDMI_UNION_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_HDMI_UNION, ImHdmiUnionPrivate));

struct _ImHdmiUnionPrivate
{
	gint a;
};


const static guchar S_GIM_HDMI_PHY_REGISTER_ADDRESS[ImHdmi_D_IM_HDMI_PHY_REG_NUM] = {
	ImHdmi_D_IM_HDMI_INT_FLG_I2CM,
	ImHdmi_D_IM_HDMI_PHY_ADR_OPMODE_PLLCFG,
	ImHdmi_D_IM_HDMI_PHY_ADR_CKSYMTXCTRL,
	ImHdmi_D_IM_HDMI_PHY_ADR_VLEVCTRL,
	ImHdmi_D_IM_HDMI_PHY_ADR_PLLCURRCTRL,
	ImHdmi_D_IM_HDMI_PHY_ADR_PLLCTRL,
	ImHdmi_D_IM_HDMI_PHY_ADR_PLLGMPCTRL,
	ImHdmi_D_IM_HDMI_PHY_ADR_TXTERM
};
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 * IMPL
 */
static void 		im_hdmi_union_class_init(ImHdmiUnionClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImHdmiUnionPrivate));
}

static void 		im_hdmi_union_init(ImHdmiUnion *self)
{
	ImHdmiUnionPrivate *priv = IM_HDMI_UNION_GET_PRIVATE(self);
	self->imhdmi = im_hdmi_new();
	self->imHdmiStruct = im_hdmi_struct_new();
}

static void 		dispose_od(GObject *object)
{
	ImHdmiUnionPrivate *priv = IM_HDMI_UNION_GET_PRIVATE(object);
	ImHdmiUnion *self = im_hdmi_union_new();
	if(self->imhdmi){
		g_object_unref(self->imhdmi);
		self->imhdmi = NULL;
	}
	if(self->imHdmiStruct){
		g_object_unref(self->imHdmiStruct);
		self->imHdmiStruct = NULL;
	}
	G_OBJECT_CLASS(im_hdmi_union_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImHdmiUnionPrivate *priv = IM_HDMI_UNION_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_hdmi_union_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
/**
 * @brief	Get control data of HDMI Transmitter.
 * @param[out]	self	Control data.
 * @retval				D_DDIM_OK					success.
 * @retval				ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error
 */
gint32 im_hdmi_get_ctrl(ImHdmiUnion *self)
{
	gint32 index;
#ifdef CO_PARAM_CHECK
	if (self == NULL) {
		Ddim_Assertion(("im_hdmi_get_self Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imhdmi);

	// Get Video Mapping input mode.
	self->imHdmiStruct->videoInputMapping = ioDisp.hdmiTx.txInvid0.bit.videoMapping;

	// Get fcInvidconf.
	self->imHdmiStruct->hdcpKeepout = ioDisp.hdmiTx.fcInvidconf.bit.hdcpKeepout;
	self->imHdmiStruct->vsyncInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.vsyncInPolarity;
	self->imHdmiStruct->hsyncInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.hsyncInPolarity;
	self->imHdmiStruct->deInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.deInPolarity;
	self->imHdmiStruct->rVBlankInOsc = ioDisp.hdmiTx.fcInvidconf.bit.rVBlankInOsc;
	self->imHdmiStruct->inIP = ioDisp.hdmiTx.fcInvidconf.bit.inIP;
	// Get fcInvactiv.
	self->imHdmiStruct->hInActiv = ioDisp.hdmiTx.fcInhactiv1.byte[0];
	self->imHdmiStruct->hInActiv = ((self->imHdmiStruct->hInActiv << 8) | ioDisp.hdmiTx.fcInhactiv0.byte[0]);

	self->imHdmiStruct->vInActiv = ioDisp.hdmiTx.fcInvactiv1.byte[0];
	self->imHdmiStruct->vInActiv = ((self->imHdmiStruct->vInActiv << 8) | ioDisp.hdmiTx.fcInvactiv0.byte[0]);

	// Get fc_invact_2d_0/1, fcActspcHdlrCfg.
	self->imHdmiStruct->fcInvact2d = ioDisp.hdmiTx.fcInvact2d1.byte[0];
	self->imHdmiStruct->fcInvact2d = ((self->imHdmiStruct->fcInvact2d << 8) | ioDisp.hdmiTx.fcInvact2d0.byte[0]);

	self->imHdmiStruct->fcActspcHdlrCfg.byte = ioDisp.hdmiTx.fcActspcHdlrCfg.byte[0];
	// Get H blanking pixels / V blanking pixels.
	self->imHdmiStruct->fcInhblank = ioDisp.hdmiTx.fcInhblank1.byte[0];
	self->imHdmiStruct->fcInhblank = ((self->imHdmiStruct->fcInhblank << 8) | ioDisp.hdmiTx.fcInhblank0.byte[0]);

	self->imHdmiStruct->fcInvblank = ioDisp.hdmiTx.fcInvblank;
	// Get HSync offset / VSync offset.
	self->imHdmiStruct->fcHsyncindelay = ioDisp.hdmiTx.fcHsyncindelay1.byte[0];
	self->imHdmiStruct->fcHsyncindelay = ((self->imHdmiStruct->fcHsyncindelay << 8) | ioDisp.hdmiTx.fcHsyncindelay0.byte[0]);
	self->imHdmiStruct->fcVsyncindelay = ioDisp.hdmiTx.fcVsyncindelay;
	// Get HSync pulse width / VSync pulse width
	self->imHdmiStruct->fcHsyncinwidth = ioDisp.hdmiTx.fcHsyncinwidth1.byte[0];
	self->imHdmiStruct->fcHsyncinwidth = ((self->imHdmiStruct->fcHsyncinwidth << 8) | ioDisp.hdmiTx.fcHsyncinwidth0.byte[0]);

	self->imHdmiStruct->fcVsyncinwidth = ioDisp.hdmiTx.fcVsyncinwidth.byte[0];

	// DVI mode
	self->imHdmiStruct->dviModez = ioDisp.hdmiTx.fcInvidconf.bit.dviModez;

	// Get PLL.
	self->imHdmiStruct->pllConfig.vpPrCd.byte = ioDisp.hdmiTx.vpPrCd.byte[0];
	// PHY Register.
	self->imHdmiStruct->pllConfig.phyRegNum = ImHdmi_D_IM_HDMI_PHY_REG_NUM;
	for (index = 0; index < ImHdmi_D_IM_HDMI_PHY_REG_NUM; index++) {
		// Address.
		self->imHdmiStruct->pllConfig.phyRegAddr[index] = S_GIM_HDMI_PHY_REGISTER_ADDRESS[index];
		// Value.
		if (im_hdmi_phy_read(self->imhdmi, S_GIM_HDMI_PHY_REGISTER_ADDRESS[index], &(self->imHdmiStruct->pllConfig.phyRegData[index])) != D_DDIM_OK) {
			self->imHdmiStruct->pllConfig.phyRegNum = index;
			Ddim_Print(("im_hdmi_get_self PHY Register data read NG!!\n"));
			break;
		}
	}

	// Get Audio mode.
	self->imHdmiStruct->audioConfig.i2sSelect = (EhdmiI2sSelect) ioDisp.hdmiTx.audConf0.bit.i2sSelect;
	self->imHdmiStruct->audioConfig.audConf1.byte = ioDisp.hdmiTx.audConf1.byte[0];
	self->imHdmiStruct->audioConfig.audConf2.byte = ioDisp.hdmiTx.audConf2.byte[0];
	self->imHdmiStruct->audioConfig.audSpdif1.byte = ioDisp.hdmiTx.audSpdif1.byte[0];
	self->imHdmiStruct->audioConfig.audInputclkfs = ioDisp.hdmiTx.audInputclkfs.byte[0];
	self->imHdmiStruct->audioConfig.audN1 = ioDisp.hdmiTx.audN1;
	self->imHdmiStruct->audioConfig.audN2 = ioDisp.hdmiTx.audN2;
	self->imHdmiStruct->audioConfig.audN3Audn = ioDisp.hdmiTx.audN3.bit.audn;
	self->imHdmiStruct->audioConfig.ctsManual = (EhdmiCtsManual) ioDisp.hdmiTx.audCts3.bit.ctsManual;
	self->imHdmiStruct->audioConfig.audCts1 = ioDisp.hdmiTx.audCts1;
	self->imHdmiStruct->audioConfig.audCts2 = ioDisp.hdmiTx.audCts2;
	self->imHdmiStruct->audioConfig.audCts3Audcts = ioDisp.hdmiTx.audCts3.bit.audcts;

	// Infoframes.
	self->imHdmiStruct->infoFrames.fcAviconf0.byte = ioDisp.hdmiTx.fcAviconf0.byte[0];
	self->imHdmiStruct->infoFrames.fcAviconf1.byte = ioDisp.hdmiTx.fcAviconf1.byte[0];
	self->imHdmiStruct->infoFrames.fcAviconf2.byte = ioDisp.hdmiTx.fcAviconf2.byte[0];
	self->imHdmiStruct->infoFrames.fcAviconf3.byte = ioDisp.hdmiTx.fcAviconf3.byte[0];
	self->imHdmiStruct->infoFrames.fcAvivid = ioDisp.hdmiTx.fcAvivid.byte[0];
	self->imHdmiStruct->infoFrames.fcPrconf.byte = ioDisp.hdmiTx.fcPrconf.byte[0];
	self->imHdmiStruct->infoFrames.fcAudiconf0.byte = ioDisp.hdmiTx.fcAudiconf0.byte[0];
	self->imHdmiStruct->infoFrames.fcAudiconf1.byte = ioDisp.hdmiTx.fcAudiconf1.byte[0];
	self->imHdmiStruct->infoFrames.fcAudiconf2 = ioDisp.hdmiTx.fcAudiconf2;
	self->imHdmiStruct->infoFrames.fcAudiconf3.byte = ioDisp.hdmiTx.fcAudiconf3.byte[0];
	self->imHdmiStruct->infoFrames.fcVsdieeeid[0] = ioDisp.hdmiTx.fcVsdieeeid0;
	self->imHdmiStruct->infoFrames.fcVsdieeeid[1] = ioDisp.hdmiTx.fcVsdieeeid1;
	self->imHdmiStruct->infoFrames.fcVsdieeeid[2] = ioDisp.hdmiTx.fcVsdieeeid2;
	self->imHdmiStruct->infoFrames.scramblerOn = ioDisp.hdmiTx.fcScramblerCtrl.bit.scramblerOn;
	self->imHdmiStruct->infoFrames.videoMode = (ioDisp.hdmiTx.fcVsdpayload[0].byte[0] & 0xE0);
	if (self->imHdmiStruct->infoFrames.videoMode == ImHdmi_D_IM_HDMI_VIDEO_MODE_HDMI) {
		// HDMI Video Mode.
		self->imHdmiStruct->infoFrames.videoFormat = ioDisp.hdmiTx.fcVsdpayload[1].byte[0];
	}
	else {
		// 3D Video Mode.
		self->imHdmiStruct->infoFrames.videoFormat = (ioDisp.hdmiTx.fcVsdpayload[1].byte[0] & 0xF0) >> 4;
		self->imHdmiStruct->infoFrames.metaPresent = (ioDisp.hdmiTx.fcVsdpayload[1].byte[0] & 0x80) >> 3;
		self->imHdmiStruct->infoFrames.additionalVideoFormat = (ioDisp.hdmiTx.fcVsdpayload[2].byte[0] & 0xF0) >> 4;
		self->imHdmiStruct->infoFrames.metaType = (ioDisp.hdmiTx.fcVsdpayload[3].byte[0] & 0xE0) >> 5;
		self->imHdmiStruct->infoFrames.metaLength = (ioDisp.hdmiTx.fcVsdpayload[3].byte[0] & 0x1F);
		for (index = 0; index < 8; index++) {
			self->imHdmiStruct->infoFrames.metaData[index] = ioDisp.hdmiTx.fcVsdpayload[4 + index].byte[0];
		}
	}

	im_hdmi_pclk_off(self->imhdmi);

	return D_DDIM_OK;
}

ImHdmiUnion* 		im_hdmi_union_new(void)
{
	ImHdmiUnion *self = g_object_new(IM_TYPE_HDMI_UNION, NULL);
	return self;
}

