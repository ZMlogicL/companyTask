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


K_TYPE_DEFINE_WITH_PRIVATE(ImHdmiUnion, im_hdmi_union);
#define IM_HDMI_UNION_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImHdmiUnionPrivate, IM_TYPE_HDMI_UNION	))

struct _ImHdmiUnionPrivate
{
	kint a;
};


const static kuchar S_GIM_HDMI_PHY_REGISTER_ADDRESS[ImHdmi_D_IM_HDMI_PHY_REG_NUM] = {
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
 * IMPL
 */
static void im_hdmi_union_constructor(ImHdmiUnion *self)
{
//	ImHdmiUnionPrivate *priv = IM_HDMI_UNION	_GET_PRIVATE(self);
}

static void im_hdmi_union_destructor(ImHdmiUnion *self)
{
//	ImHdmiUnionPrivate *priv = IM_HDMI_UNION	_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/**
 * @brief	Get control data of HDMI Transmitter.
 * @param[out]	ctrl	Control data.
 * @retval				D_DDIM_OK					success.
 * @retval				ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error
 */
kint32 im_hdmi_get_ctrl(ThdmiCtrl *const ctrl)
{
	kint32 index;
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL) {
		Ddim_Assertion(("im_hdmi_get_ctrl Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on();

	// Get Video Mapping input mode.
	ctrl->videoInputMapping = ioDisp.hdmiTx.txInvid0.bit.videoMapping;

	// Get fcInvidconf.
	ctrl->hdcpKeepout = ioDisp.hdmiTx.fcInvidconf.bit.hdcpKeepout;
	ctrl->vsyncInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.vsyncInPolarity;
	ctrl->hsyncInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.hsyncInPolarity;
	ctrl->deInPolarity = ioDisp.hdmiTx.fcInvidconf.bit.deInPolarity;
	ctrl->rVBlankInOsc = ioDisp.hdmiTx.fcInvidconf.bit.rVBlankInOsc;
	ctrl->inIP = ioDisp.hdmiTx.fcInvidconf.bit.inIP;
	// Get fcInvactiv.
	ctrl->hInActiv = ioDisp.hdmiTx.fcInhactiv1.byte[0];
	ctrl->hInActiv = ((ctrl->hInActiv << 8) | ioDisp.hdmiTx.fcInhactiv0.byte[0]);

	ctrl->vInActiv = ioDisp.hdmiTx.fcInvactiv1.byte[0];
	ctrl->vInActiv = ((ctrl->vInActiv << 8) | ioDisp.hdmiTx.fcInvactiv0.byte[0]);

	// Get fc_invact_2d_0/1, fcActspcHdlrCfg.
	ctrl->fcInvact2d = ioDisp.hdmiTx.fcInvact2d1.byte[0];
	ctrl->fcInvact2d = ((ctrl->fcInvact2d << 8) | ioDisp.hdmiTx.fcInvact2d0.byte[0]);

	ctrl->fcActspcHdlrCfg.byte = ioDisp.hdmiTx.fcActspcHdlrCfg.byte[0];
	// Get H blanking pixels / V blanking pixels.
	ctrl->fcInhblank = ioDisp.hdmiTx.fcInhblank1.byte[0];
	ctrl->fcInhblank = ((ctrl->fcInhblank << 8) | ioDisp.hdmiTx.fcInhblank0.byte[0]);

	ctrl->fcInvblank = ioDisp.hdmiTx.fcInvblank;
	// Get HSync offset / VSync offset.
	ctrl->fcHsyncindelay = ioDisp.hdmiTx.fcHsyncindelay1.byte[0];
	ctrl->fcHsyncindelay = ((ctrl->fcHsyncindelay << 8) | ioDisp.hdmiTx.fcHsyncindelay0.byte[0]);
	ctrl->fcVsyncindelay = ioDisp.hdmiTx.fcVsyncindelay;
	// Get HSync pulse width / VSync pulse width
	ctrl->fcHsyncinwidth = ioDisp.hdmiTx.fcHsyncinwidth1.byte[0];
	ctrl->fcHsyncinwidth = ((ctrl->fcHsyncinwidth << 8) | ioDisp.hdmiTx.fcHsyncinwidth0.byte[0]);

	ctrl->fcVsyncinwidth = ioDisp.hdmiTx.fcVsyncinwidth.byte[0];

	// DVI mode
	ctrl->dviModez = ioDisp.hdmiTx.fcInvidconf.bit.dviModez;

	// Get PLL.
	ctrl->pllConfig.vpPrCd.byte = ioDisp.hdmiTx.vpPrCd.byte[0];
	// PHY Register.
	ctrl->pllConfig.phyRegNum = ImHdmi_D_IM_HDMI_PHY_REG_NUM;
	for (index = 0; index < ImHdmi_D_IM_HDMI_PHY_REG_NUM; index++) {
		// Address.
		ctrl->pllConfig.phyRegAddr[index] = S_GIM_HDMI_PHY_REGISTER_ADDRESS[index];
		// Value.
		if (im_hdmi_phy_read(S_GIM_HDMI_PHY_REGISTER_ADDRESS[index], &(ctrl->pllConfig.phyRegData[index])) != D_DDIM_OK) {
			ctrl->pllConfig.phyRegNum = index;
			Ddim_Print(("im_hdmi_get_ctrl PHY Register data read NG!!\n"));
			break;
		}
	}

	// Get Audio mode.
	ctrl->audioConfig.i2sSelect = (EhdmiI2sSelect) ioDisp.hdmiTx.audConf0.bit.i2sSelect;
	ctrl->audioConfig.audConf1.byte = ioDisp.hdmiTx.audConf1.byte[0];
	ctrl->audioConfig.audConf2.byte = ioDisp.hdmiTx.audConf2.byte[0];
	ctrl->audioConfig.audSpdif1.byte = ioDisp.hdmiTx.audSpdif1.byte[0];
	ctrl->audioConfig.audInputclkfs = ioDisp.hdmiTx.audInputclkfs.byte[0];
	ctrl->audioConfig.audN1 = ioDisp.hdmiTx.audN1;
	ctrl->audioConfig.audN2 = ioDisp.hdmiTx.audN2;
	ctrl->audioConfig.audN3Audn = ioDisp.hdmiTx.audN3.bit.audn;
	ctrl->audioConfig.ctsManual = (EhdmiCtsManual) ioDisp.hdmiTx.audCts3.bit.ctsManual;
	ctrl->audioConfig.audCts1 = ioDisp.hdmiTx.audCts1;
	ctrl->audioConfig.audCts2 = ioDisp.hdmiTx.audCts2;
	ctrl->audioConfig.audCts3Audcts = ioDisp.hdmiTx.audCts3.bit.audcts;

	// Infoframes.
	ctrl->infoFrames.fcAviconf0.byte = ioDisp.hdmiTx.fcAviconf0.byte[0];
	ctrl->infoFrames.fcAviconf1.byte = ioDisp.hdmiTx.fcAviconf1.byte[0];
	ctrl->infoFrames.fcAviconf2.byte = ioDisp.hdmiTx.fcAviconf2.byte[0];
	ctrl->infoFrames.fcAviconf3.byte = ioDisp.hdmiTx.fcAviconf3.byte[0];
	ctrl->infoFrames.fcAvivid = ioDisp.hdmiTx.fcAvivid.byte[0];
	ctrl->infoFrames.fcPrconf.byte = ioDisp.hdmiTx.fcPrconf.byte[0];
	ctrl->infoFrames.fcAudiconf0.byte = ioDisp.hdmiTx.fcAudiconf0.byte[0];
	ctrl->infoFrames.fcAudiconf1.byte = ioDisp.hdmiTx.fcAudiconf1.byte[0];
	ctrl->infoFrames.fcAudiconf2 = ioDisp.hdmiTx.fcAudiconf2;
	ctrl->infoFrames.fcAudiconf3.byte = ioDisp.hdmiTx.fcAudiconf3.byte[0];
	ctrl->infoFrames.fcVsdieeeid[0] = ioDisp.hdmiTx.fcVsdieeeid0;
	ctrl->infoFrames.fcVsdieeeid[1] = ioDisp.hdmiTx.fcVsdieeeid1;
	ctrl->infoFrames.fcVsdieeeid[2] = ioDisp.hdmiTx.fcVsdieeeid2;
	ctrl->infoFrames.scramblerOn = ioDisp.hdmiTx.fcScramblerCtrl.bit.scramblerOn;
	ctrl->infoFrames.videoMode = (ioDisp.hdmiTx.fcVsdpayload[0].byte[0] & 0xE0);
	if (ctrl->infoFrames.videoMode == ImHdmi_D_IM_HDMI_VIDEO_MODE_HDMI) {
		// HDMI Video Mode.
		ctrl->infoFrames.videoFormat = ioDisp.hdmiTx.fcVsdpayload[1].byte[0];
	}
	else {
		// 3D Video Mode.
		ctrl->infoFrames.videoFormat = (ioDisp.hdmiTx.fcVsdpayload[1].byte[0] & 0xF0) >> 4;
		ctrl->infoFrames.metaPresent = (ioDisp.hdmiTx.fcVsdpayload[1].byte[0] & 0x80) >> 3;
		ctrl->infoFrames.additionalVideoFormat = (ioDisp.hdmiTx.fcVsdpayload[2].byte[0] & 0xF0) >> 4;
		ctrl->infoFrames.metaType = (ioDisp.hdmiTx.fcVsdpayload[3].byte[0] & 0xE0) >> 5;
		ctrl->infoFrames.metaLength = (ioDisp.hdmiTx.fcVsdpayload[3].byte[0] & 0x1F);
		for (index = 0; index < 8; index++) {
			ctrl->infoFrames.metaData[index] = ioDisp.hdmiTx.fcVsdpayload[4 + index].byte[0];
		}
	}

	im_hdmi_pclk_off();

	return D_DDIM_OK;
}

ImHdmiUnion* im_hdmi_union_new(void)
{
	ImHdmiUnion *self = k_object_new_with_private(IM_TYPE_HDMI_UNION, sizeof(ImHdmiUnionPrivate));
	return self;
}

