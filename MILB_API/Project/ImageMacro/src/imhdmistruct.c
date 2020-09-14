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
#include "imhdmistruct.h"


G_DEFINE_TYPE(ImHdmiStruct, im_hdmi_struct, G_TYPE_OBJECT);
#define IM_HDMI_STRUCT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_HDMI_STRUCT, ImHdmiStructPrivate));


struct _ImHdmiStructPrivate
{
	gint a;
};
/*----------------------------------------------------------------------	*/
/* Global Data																*/
/*----------------------------------------------------------------------	*/
static volatile VP_HDMI_CALLBACK gIM_HDMI_INT_Callback = NULL;
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 * IMPL
 */
static void 		im_hdmi_struct_class_init(ImHdmiStructClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImHdmiStructPrivate));
}

static void 		im_hdmi_struct_init(ImHdmiStruct *self)
{
	ImHdmiStructPrivate *priv = IM_HDMI_STRUCT_GET_PRIVATE(self);
	self->imHdmi = im_hdmi_new();
}

static void 		dispose_od(GObject *object)
{
	ImHdmiStructPrivate *priv = IM_HDMI_STRUCT_GET_PRIVATE(object);
	ImHdmiStruct *self = im_hdmi_struct_new();
	if(self->imHdmi){
		g_object_unref(self->imHdmi);
		self->imHdmi = NULL;
	}
	G_OBJECT_CLASS(im_hdmi_struct_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImHdmiStructPrivate *priv = IM_HDMI_STRUCT_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_hdmi_struct_parent_class) -> dispose(object);
}
/**
 * PUBLIC
 */
/**
 * @brief	Set Color Space Converter.
 */
gint32 im_hdmi_struct_csc(ImHdmiStruct *self, ThdmiCscConfig const *const config, const ThdmiCscCoef
										matrix[ImHdmiStruct_D_IM_HDMI_CSC_CONF_COLUMN_NUM][ImHdmiStruct_D_IM_HDMI_CSC_CONF_ROW_NUM])
{
	gint32 loop1, loop2;

#ifdef CO_PARAM_CHECK
	if ((config == NULL) || (matrix == NULL)) {
		Ddim_Assertion(("im_hdmi_struct_csc Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Set cscCfg/cscScale.
	ioDisp.hdmiTx.cscCfg.byte[0] = config->cscCfg.byte;
	ioDisp.hdmiTx.cscScale.byte[0] = config->cscScale.byte;

	// Set csc_coef_a1_msb~csc_coef_c4_lsb.
	for (loop1 = 0; loop1 < ImHdmiStruct_D_IM_HDMI_CSC_CONF_COLUMN_NUM; loop1++) {
		for (loop2 = 0; loop2 < ImHdmiStruct_D_IM_HDMI_CSC_CONF_ROW_NUM; loop2++) {
			ioDisp.hdmiTx.cscCoef[loop1][loop2].msb = matrix[loop1][loop2].msb;
			ioDisp.hdmiTx.cscCoef[loop1][loop2].lsb = matrix[loop1][loop2].lsb;
		}
	}

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Video Sampler.
 */
void im_hdmi_struct_set_video_sampler(ImHdmiStruct *self, UhdmiTxInvid0 txInvid0)
{
	im_hdmi_pclk_on(self->imHdmi);

	// Set txInvid0.
	ioDisp.hdmiTx.txInvid0.byte[0]	= txInvid0.byte;

	im_hdmi_pclk_off(self->imHdmi);
}

/**
 * @brief	Get Video Sampler.
 */
gint32 im_hdmi_struct_get_video_sampler(ImHdmiStruct *self, UhdmiTxInvid0* txInvid0)
{
#ifdef CO_PARAM_CHECK
	if (txInvid0 == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_video_sampler Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get txInvid0.
	txInvid0->byte = ioDisp.hdmiTx.txInvid0.byte[0];

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Video Packetizer.
 */
gint32 im_hdmi_struct_set_video_packetizer(ImHdmiStruct *self, ThdmiVideoPacketizer const *const videoPacketizer)
{
#ifdef CO_PARAM_CHECK
	if (videoPacketizer == NULL) {
		Ddim_Assertion(("im_hdmi_struct_set_video_packetizer Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Set vpPrCd/vpRemap/vpConf.
	ioDisp.hdmiTx.vpPrCd.byte[0] = videoPacketizer->vpPrCd.byte;
	ioDisp.hdmiTx.vpRemap.byte[0] = videoPacketizer->vpRemap;
	ioDisp.hdmiTx.vpConf.byte[0] = videoPacketizer->vpConf.byte;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Video Packetizer.
 */
gint32 im_hdmi_struct_get_video_packetizer(ImHdmiStruct *self, ThdmiVideoPacketizer *const videoPacketizer)
{
#ifdef CO_PARAM_CHECK
	if (videoPacketizer == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_video_packetizer Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get vpPrCd/vpRemap/vpConf.
	videoPacketizer->vpPrCd.byte = ioDisp.hdmiTx.vpPrCd.byte[0];
	videoPacketizer->vpRemap = (EhdmiVpRemap) ioDisp.hdmiTx.vpRemap.byte[0];
	videoPacketizer->vpConf.byte = ioDisp.hdmiTx.vpConf.byte[0];

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Frame Composer.
 */
gint32 im_hdmi_struct_set_frame_composer(ImHdmiStruct *self, ThdmiFrameComposer const *const frameComposer)
{
	unsigned char writeWork = 0;

#ifdef CO_PARAM_CHECK
	if (frameComposer == NULL) {
		Ddim_Assertion(("im_hdmi_struct_set_frame_composer Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Set fcInvidconf.
	ioDisp.hdmiTx.fcInvidconf.byte[0] = frameComposer->fcInvidconf.byte;

	// Set fc_inhactiv0/1.
	writeWork = frameComposer->fcInhactiv;
	ioDisp.hdmiTx.fcInhactiv0.byte[0] = writeWork;
	writeWork = frameComposer->fcInhactiv >> 8;
	ioDisp.hdmiTx.fcInhactiv1.byte[0] = writeWork;

	// Set fc_inhblank0/1.
	writeWork = frameComposer->fcInhblank;
	ioDisp.hdmiTx.fcInhblank0.byte[0] = writeWork;
	writeWork = frameComposer->fcInhblank >> 8;
	ioDisp.hdmiTx.fcInhblank1.byte[0] = writeWork;

	// Set fc_invactiv0/1.
	writeWork = frameComposer->fcInvactiv;
	ioDisp.hdmiTx.fcInvactiv0.byte[0] = writeWork;
	writeWork = frameComposer->fcInvactiv >> 8;
	ioDisp.hdmiTx.fcInvactiv1.byte[0] = writeWork;

	// Set fcInvblank.
	ioDisp.hdmiTx.fcInvblank = frameComposer->fcInvblank;

	// Set fc_hsyncindelay0/1.
	ioDisp.hdmiTx.fcHsyncindelay0.byte[0] = (frameComposer->fcHsyncindelay & 0x00FF);
	ioDisp.hdmiTx.fcHsyncindelay1.byte[0] = (frameComposer->fcHsyncindelay >> 8);
	// Set fc_hsyncinwidth0/1.
	ioDisp.hdmiTx.fcHsyncinwidth0.byte[0] = (frameComposer->fcHsyncinwidth & 0x00FF);
	ioDisp.hdmiTx.fcHsyncinwidth1.byte[0] = (frameComposer->fcHsyncinwidth >> 8);
	// Set fcVsyncindelay/fcVsyncinwidth.
	ioDisp.hdmiTx.fcVsyncindelay = frameComposer->fcVsyncindelay;
	ioDisp.hdmiTx.fcVsyncinwidth.byte[0] = frameComposer->fcVsyncinwidth;

	// Set fcAviconf3/fcAviconf0/fcAviconf1/fcAviconf2.
	ioDisp.hdmiTx.fcAviconf3.byte[0] = frameComposer->fcAviconf3.byte;
	ioDisp.hdmiTx.fcAviconf0.byte[0] = frameComposer->fcAviconf0.byte;
	ioDisp.hdmiTx.fcAviconf1.byte[0] = frameComposer->fcAviconf1.byte;
	ioDisp.hdmiTx.fcAviconf2.byte[0] = frameComposer->fcAviconf2.byte;
	// Set fcAvivid.
	ioDisp.hdmiTx.fcAvivid.byte[0] = frameComposer->fcAvivid;
	// Set fcPrconf.
	ioDisp.hdmiTx.fcPrconf.byte[0] = frameComposer->fcPrconf.byte;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Frame Composer.
 */
gint32 im_hdmi_struct_get_frame_composer(ImHdmiStruct *self, ThdmiFrameComposer *const frameComposer)
{
#ifdef CO_PARAM_CHECK
	if (frameComposer == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_frame_composer Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get fcInvidconf.
	frameComposer->fcInvidconf.byte = ioDisp.hdmiTx.fcInvidconf.byte[0];
	// Get fc_inhactiv0/1.
	frameComposer->fcInhactiv = ioDisp.hdmiTx.fcInhactiv1.byte[0];
	frameComposer->fcInhactiv = ((frameComposer->fcInhactiv << 8) | ioDisp.hdmiTx.fcInhactiv0.byte[0]);

	// Get fc_inhblank0/1.
	frameComposer->fcInhblank = ioDisp.hdmiTx.fcInhblank1.byte[0];
	frameComposer->fcInhblank = ((frameComposer->fcInhblank << 8) | ioDisp.hdmiTx.fcInhblank0.byte[0]);

	// Get fc_invactiv0/1.
	frameComposer->fcInvactiv = ioDisp.hdmiTx.fcInvactiv1.byte[0];
	frameComposer->fcInvactiv = ((frameComposer->fcInvactiv << 8) | ioDisp.hdmiTx.fcInvactiv0.byte[0]);
	// Get fcInvblank.
	frameComposer->fcInvblank = ioDisp.hdmiTx.fcInvblank;

	// Get fc_hsyncindelay0/1.
	frameComposer->fcHsyncindelay = ioDisp.hdmiTx.fcHsyncindelay1.byte[0];
	frameComposer->fcHsyncindelay = ((frameComposer->fcHsyncindelay << 8) | ioDisp.hdmiTx.fcHsyncindelay0.byte[0]);
	// Get fc_hsyncinwidth0/1.
	frameComposer->fcHsyncinwidth = ioDisp.hdmiTx.fcHsyncinwidth1.byte[0];
	frameComposer->fcHsyncinwidth = ((frameComposer->fcHsyncinwidth << 8) | ioDisp.hdmiTx.fcHsyncinwidth0.byte[0]);

	// Get fcVsyncindelay/fcVsyncinwidth.
	frameComposer->fcVsyncindelay = ioDisp.hdmiTx.fcVsyncindelay;
	frameComposer->fcVsyncinwidth = ioDisp.hdmiTx.fcVsyncinwidth.byte[0];

	// Get fcAviconf3/fcAviconf0/fcAviconf1/fcAviconf2.
	frameComposer->fcAviconf3.byte = ioDisp.hdmiTx.fcAviconf3.byte[0];
	frameComposer->fcAviconf0.byte = ioDisp.hdmiTx.fcAviconf0.byte[0];
	frameComposer->fcAviconf1.byte = ioDisp.hdmiTx.fcAviconf1.byte[0];
	frameComposer->fcAviconf2.byte = ioDisp.hdmiTx.fcAviconf2.byte[0];
	// Get fcAvivid.
	frameComposer->fcAvivid = ioDisp.hdmiTx.fcAvivid.byte[0];
	// Get fcPrconf.
	frameComposer->fcPrconf.byte = ioDisp.hdmiTx.fcPrconf.byte[0];

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Frame Composer (SPD Packet Data).
 */
gint32 im_hdmi_struct_set_frame_composer_spd(ImHdmiStruct *self, ThdmiFcSpd const *const fcSpd)
{
	gint32 loop;
#ifdef CO_PARAM_CHECK
	if (fcSpd == NULL) {
		Ddim_Assertion(("im_hdmi_struct_set_frame_composer_spd Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Vendor Name.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_SPD_VENDER_NAME_NUM; loop++) {
		ioDisp.hdmiTx.fcSpdvendorname[loop].byte[0] = fcSpd->fcSpdvendorname[loop];
	}
	// Product Name.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_SPD_PRO_NAME_NUM; loop++) {
		ioDisp.hdmiTx.fcSpdproductname[loop].byte[0] = fcSpd->fcSpdproductname[loop];
	}
	// Source Product Descriptor.
	ioDisp.hdmiTx.fcSpddeviceinf = fcSpd->fcSpddeviceinf;
	// Enables SPD automatic packet scheduling
	ioDisp.hdmiTx.fcDatauto0.bit.spdAuto = 1;
	// auto_frame_packets
	ioDisp.hdmiTx.fcDatauto2.bit.autoFramePackets = 1;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Frame Composer (SPD Packet Data).
 */
gint32 im_hdmi_struct_get_frame_composer_spd(ImHdmiStruct *self, ThdmiFcSpd *const fcSpd)
{
	gint32 loop;
#ifdef CO_PARAM_CHECK
	if (fcSpd == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_frame_composer_spd Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Vendor Name.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_SPD_VENDER_NAME_NUM; loop++) {
		fcSpd->fcSpdvendorname[loop] = ioDisp.hdmiTx.fcSpdvendorname[loop].byte[0];
	}
	// Product Name.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_SPD_PRO_NAME_NUM; loop++) {
		fcSpd->fcSpdproductname[loop] = ioDisp.hdmiTx.fcSpdproductname[loop].byte[0];
	}
	// Source Product Descriptor.
	fcSpd->fcSpddeviceinf = ioDisp.hdmiTx.fcSpddeviceinf;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Frame Composer (Vendor Specific).
 */
gint32 im_hdmi_struct_set_frame_composer_vsd(ImHdmiStruct *self, ThdmiFcVsd const *const fcVsd)
{
	gint32 loop;
#ifdef CO_PARAM_CHECK
	if (fcVsd == NULL) {
		Ddim_Assertion(("im_hdmi_struct_set_frame_composer_vsd Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// IEEE registration identifier.
	ioDisp.hdmiTx.fcVsdieeeid0 = fcVsd->fcVsdieeeid[0];
	ioDisp.hdmiTx.fcVsdieeeid1 = fcVsd->fcVsdieeeid[1];
	ioDisp.hdmiTx.fcVsdieeeid2 = fcVsd->fcVsdieeeid[2];

	// VSI Packet Data Size.
	ioDisp.hdmiTx.fcVsdsize.bit.vsdsize = fcVsd->fcVsdsize;

	// Payload Register Array.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_VSD_PAYLOAD_NUM; loop++) {
		ioDisp.hdmiTx.fcVsdpayload[loop].byte[0] = fcVsd->fcVsdpayload[loop];
	}
	// Enables VSD automatic packet scheduling
	ioDisp.hdmiTx.fcDatauto0.bit.vsdAuto = 1;
	// auto_frame_packets
	ioDisp.hdmiTx.fcDatauto2.bit.autoFramePackets = 1;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Frame Composer (Vendor Specific).
 */
gint32 im_hdmi_struct_get_frame_composer_vsd(ImHdmiStruct *self, ThdmiFcVsd *const fcVsd)
{
	gint32 loop;
#ifdef CO_PARAM_CHECK
	if (fcVsd == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_frame_composer_vsd Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// IEEE registration identifier.
	fcVsd->fcVsdieeeid[0] = ioDisp.hdmiTx.fcVsdieeeid0;
	fcVsd->fcVsdieeeid[1] = ioDisp.hdmiTx.fcVsdieeeid1;
	fcVsd->fcVsdieeeid[2] = ioDisp.hdmiTx.fcVsdieeeid2;

	// VSI Packet Data Size.
	fcVsd->fcVsdsize = ioDisp.hdmiTx.fcVsdsize.byte[0];

	// Payload Register Array.
	for (loop = 0; loop < ImHdmi_D_IM_HDMI_FC_VSD_PAYLOAD_NUM; loop++) {
		fcVsd->fcVsdpayload[loop] = ioDisp.hdmiTx.fcVsdpayload[loop].byte[0];
	}

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Main Controller.
 */
gint32 im_hdmi_struct_set_main_controller(ImHdmiStruct *self, guchar mcFlowctrl)
{
#ifdef CO_PARAM_CHECK
	if ((mcFlowctrl != ImHdmi_D_IM_HDMI_ENABLE_OFF) && (mcFlowctrl != ImHdmi_D_IM_HDMI_ENABLE_ON)) {
		Ddim_Assertion(("im_hdmi_struct_set_main_controller Input_Param_Err\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Set mcFlowctrl.
	ioDisp.hdmiTx.mcFlowctrl.byte[0] = mcFlowctrl;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Main Controller.
 */
gint32 im_hdmi_struct_get_main_controller(ImHdmiStruct *self, guchar* mcFlowctrl)
{
#ifdef CO_PARAM_CHECK
	if (mcFlowctrl == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_main_controller Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get mcFlowctrl.
	*mcFlowctrl = ioDisp.hdmiTx.mcFlowctrl.byte[0];

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Audio data.
 */
gint32 im_hdmi_struct_set_audio(ImHdmiStruct *self, ThdmiAudio const *const audio)
{
#ifdef CO_PARAM_CHECK
	if (audio == NULL) {
		Ddim_Assertion(("im_hdmi_struct_set_audio Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Clock Domain Disable.
	ioDisp.hdmiTx.mcClkdis.bit.audclkDisable = 1;

	// Set audInputclkfs.
	ioDisp.hdmiTx.audInputclkfs.byte[0] = audio->audInputclkfs;

	// Set audConf0/audConf1/audConf2.
	ioDisp.hdmiTx.audConf0.byte[0] = audio->audConf0.byte;
	ioDisp.hdmiTx.audConf1.byte[0] = audio->audConf1.byte;
	ioDisp.hdmiTx.audConf2.byte[0] = audio->audConf2.byte;

	// Set fcAudsconf.
	ioDisp.hdmiTx.fcAudsconf.byte[0] = audio->fcAudsconf.byte;

	// Set audSpdif1.
	ioDisp.hdmiTx.audSpdif1.byte[0] = audio->audSpdif1.byte;

	// Audio Infoframe.
	ioDisp.hdmiTx.fcAudiconf0.byte[0] = audio->fcAudiconf0.byte;
	ioDisp.hdmiTx.fcAudiconf1.byte[0] = audio->fcAudiconf1.byte;
	ioDisp.hdmiTx.fcAudiconf2 = audio->fcAudiconf2;
	ioDisp.hdmiTx.fcAudiconf3.byte[0] = audio->fcAudiconf3.byte;

	// Frame Composer Audio Sample Channel Status Configuration Register 7(Sampling frequency)
	ioDisp.hdmiTx.fcAudschnl7.bit.oiecSampfreq = audio->sampfreq;
	// Frame Composer Audio Sample Channel Status Configuration Register 8(Word length configuration)
	ioDisp.hdmiTx.fcAudschnl8.bit.oiecWordlength = audio->oiecWordlength;

	// Clock Domain Disable.
	ioDisp.hdmiTx.mcClkdis.bit.audclkDisable = 0;

	// CTS Automatic/Manual select.
	if (audio->ctsManual == ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_MANUAL) {
		// N3 ncts_atomic_write
		ioDisp.hdmiTx.audN3.bit.nctsAtomicWrite = audio->audNctsAtomicWrite;
		// CTS Manual.
		ioDisp.hdmiTx.audCts3.bit.ctsManual = ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_MANUAL;
		//Set Audio fixed N factor.
		ioDisp.hdmiTx.audCts3.bit.audcts = audio->audCts3Audcts;
		ioDisp.hdmiTx.audCts2 = audio->audCts2;
		ioDisp.hdmiTx.audCts1 = audio->audCts1;
		// N3 ncts_atomic_write
		ioDisp.hdmiTx.audN3.bit.nctsAtomicWrite = audio->audNctsAtomicWrite;
		//Set Audio fixed N factor.
		ioDisp.hdmiTx.audN3.bit.audn = audio->audN3Audn;
		ioDisp.hdmiTx.audN2 = audio->audN2;
		ioDisp.hdmiTx.audN1 = audio->audN1;
	}
	else {
		// CTS Automatic.
		ioDisp.hdmiTx.audCts3.bit.ctsManual = ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_AUTO;
		// N3 ncts_atomic_write
		ioDisp.hdmiTx.audN3.bit.nctsAtomicWrite = audio->audNctsAtomicWrite;
		//Set Audio fixed N factor.
		ioDisp.hdmiTx.audN3.bit.audn = audio->audN3Audn;
		ioDisp.hdmiTx.audN2 = audio->audN2;
		ioDisp.hdmiTx.audN1 = audio->audN1;
	}

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get Audio data.
 */
gint32 im_hdmi_struct_get_audio(ImHdmiStruct *self, ThdmiAudio *const audio)
{
#ifdef CO_PARAM_CHECK
	if (audio == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_audio Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get audInputclkfs.
	audio->audInputclkfs = ioDisp.hdmiTx.audInputclkfs.byte[0];

	// Get audConf0/audConf1/audConf2.
	audio->audConf0.byte = ioDisp.hdmiTx.audConf0.byte[0];
	audio->audConf1.byte = ioDisp.hdmiTx.audConf1.byte[0];
	audio->audConf2.byte = ioDisp.hdmiTx.audConf2.byte[0];

	// Get fcAudsconf.
	audio->fcAudsconf.byte = ioDisp.hdmiTx.fcAudsconf.byte[0];

	// Get audSpdif1.
	audio->audSpdif1.byte = ioDisp.hdmiTx.audSpdif1.byte[0];

	// Get N3 ncts_atomic_write
	audio->audNctsAtomicWrite = ioDisp.hdmiTx.audN3.bit.nctsAtomicWrite;
	// Get CTS Manual.
	audio->ctsManual = ioDisp.hdmiTx.audCts3.bit.ctsManual;
	// Get Audio fixed N factor.
	audio->audCts3Audcts = ioDisp.hdmiTx.audCts3.bit.audcts;
	audio->audCts2 = ioDisp.hdmiTx.audCts2;
	audio->audCts1 = ioDisp.hdmiTx.audCts1;
	// Get Audio fixed N factor.
	audio->audN3Audn = ioDisp.hdmiTx.audN3.bit.audn;
	audio->audN2 = ioDisp.hdmiTx.audN2;
	audio->audN1 = ioDisp.hdmiTx.audN1;

	// Get Audio Infoframe.
	audio->fcAudiconf0.byte = ioDisp.hdmiTx.fcAudiconf0.byte[0];
	audio->fcAudiconf1.byte = ioDisp.hdmiTx.fcAudiconf1.byte[0];
	audio->fcAudiconf2 = ioDisp.hdmiTx.fcAudiconf2;
	audio->fcAudiconf3.byte = ioDisp.hdmiTx.fcAudiconf3.byte[0];

	// Get Frame Composer Audio Sample Channel Status Configuration Register 7(Sampling frequency)
	audio->sampfreq = ioDisp.hdmiTx.fcAudschnl7.bit.oiecSampfreq;
	// Get Frame Composer Audio Sample Channel Status Configuration Register 8(Word length configuration)
	audio->oiecWordlength = ioDisp.hdmiTx.fcAudschnl8.bit.oiecWordlength;

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Set Interrupt callback function.
 */
void im_hdmi_struct_set_int_callback(ImHdmiStruct *self, VP_HDMI_CALLBACK vpCallback)
{
	// Set interrupt callback.
	gIM_HDMI_INT_Callback = vpCallback;
}

/**
 * @brief	Set Interrupt Mute.
 */
void im_hdmi_struct_set_int_mute(ImHdmiStruct *self, EhdmiIntReg interruptRegister, guchar mute)
{
	im_hdmi_pclk_on(self->imHdmi);

	// Check Interrupt type.
	switch (interruptRegister) {
		// ih_mute_fc_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0:
			ioDisp.hdmiTx.ihMuteFcStat0.byte[0] = mute;
			break;
		// ih_mute_fc_stat1 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1:
			ioDisp.hdmiTx.ihMuteFcStat1.byte[0] = mute;
			break;
		// ih_mute_fc_stat2 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2:
			ioDisp.hdmiTx.ihMuteFcStat2.byte[0] = mute;
			break;
		// ih_mute_as_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0:
			ioDisp.hdmiTx.ihMuteAsStat0.byte[0] = mute;
			break;
		// ih_mute_phy_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0:
			ioDisp.hdmiTx.ihMutePhyStat0.byte[0] = mute;
			break;
		// ih_mute_i2cm_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0:
			ioDisp.hdmiTx.ihMuteI2cmStat0.byte[0] = mute;
			break;
		// ih_mute_cec_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0:
			ioDisp.hdmiTx.ihMuteCecStat0.byte[0] = mute;
			break;
		// ih_mute_vp_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0:
			ioDisp.hdmiTx.ihMuteVpStat0.byte[0] = mute;
			break;
		// default (ih_mute_i2cmphy_stat0).
		default:
			ioDisp.hdmiTx.ihI2cmphyStat0.byte[0] = mute;
			break;
	}

	im_hdmi_pclk_off(self->imHdmi);
}

/**
 * @brief	Get Interrupt Mute.
 */
gint32 im_hdmi_struct_get_int_mute(ImHdmiStruct *self, EhdmiIntReg interruptRegister, guchar* mute)
{
#ifdef CO_PARAM_CHECK
	if (mute == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_int_mute Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Check Interrupt type.
	switch (interruptRegister) {
		// ih_mute_fc_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0:
			*mute = ioDisp.hdmiTx.ihMuteFcStat0.byte[0];
			break;
		// ih_mute_fc_stat1 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1:
			*mute = ioDisp.hdmiTx.ihMuteFcStat1.byte[0];
			break;
		// ih_mute_fc_stat2 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2:
			*mute = ioDisp.hdmiTx.ihMuteFcStat2.byte[0];
			break;
		// ih_mute_as_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0:
			*mute = ioDisp.hdmiTx.ihMuteAsStat0.byte[0];
			break;
		// ih_mute_phy_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0:
			*mute = ioDisp.hdmiTx.ihMutePhyStat0.byte[0];
			break;
		// ih_mute_i2cm_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0:
			*mute = ioDisp.hdmiTx.ihMuteI2cmStat0.byte[0];
			break;
		// ih_mute_cec_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0:
			*mute = ioDisp.hdmiTx.ihMuteCecStat0.byte[0];
			break;
		// ih_mute_vp_stat0 Register.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0:
			*mute = ioDisp.hdmiTx.ihMuteVpStat0.byte[0];
			break;
		// default (ih_mute_i2cmphy_stat0).
		default:
			*mute = ioDisp.hdmiTx.ihI2cmphyStat0.byte[0];
			break;
	}

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}

/**
 * @brief	Get PHY status.
 */
gint32 im_hdmi_struct_get_phy_status(ImHdmiStruct *self, UhdmiPhyStat0 *status)
{
#ifdef CO_PARAM_CHECK
	if (status == NULL) {
		Ddim_Assertion(("im_hdmi_struct_get_phy_status Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on(self->imHdmi);

	// Get phy_stat0 Register.
	status->byte = ioDisp.hdmiTx.phyStat0.byte[0];

	im_hdmi_pclk_off(self->imHdmi);

	return D_DDIM_OK;
}
/**
 * @brief	HDMI Interrupt Handler.
 */
void im_hdmi_struct_int_handler(ImHdmiStruct *self)
{
	im_hdmi_pclk_on(self->imHdmi);

	// check ih_fc_stat0/ih_fc_stat1/ih_fc_stat2.
	im_hdmi_check_interrupt_fc(self->imHdmi);
	// check as_stat0.
	im_hdmi_check_interrupt_as(self->imHdmi);
	// check ih_phy_stat0.
	im_hdmi_check_interrupt_phy(self->imHdmi);
	// check ih_i2cm_stat0.
	im_hdmi_check_interrupt_i2cm(self->imHdmi);
	// check ih_cec_stat0.
	im_hdmi_check_interrupt_cec(self->imHdmi);
	// check ih_vp_stat0.
	im_hdmi_check_interrupt_vp(self->imHdmi);
	// check ih_i2cmphy_stat0.
	im_hdmi_check_interrupt_i2cmphy(self->imHdmi);

	im_hdmi_pclk_off(self->imHdmi);
}

ImHdmiStruct* 		im_hdmi_struct_new(void)
{
	ImHdmiStruct *self = g_object_new(IM_TYPE_HDMI_STRUCT, NULL);
	return self;
}
