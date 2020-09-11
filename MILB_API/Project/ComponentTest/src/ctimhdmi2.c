/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImHdmi2
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimhdmi.h"


typedef struct _NEW
{
	T_IM_HDMI_VIDEO_PACKETIZER *videoPacketizer;
	T_IM_HDMI_AUDIO *audio;
	T_IM_HDMI_CSC_CONFIG *cscConfig;
	T_IM_HDMI_I2CM_CONFIG *i2cmConfig;
} NEW;
NEW new;


K_TYPE_DEFINE_WITH_PRIVATE(CtImHdmi2, ct_im_hdmi2)
#define CT_IM_HDMI2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), CtImHdmi2Private, CT_TYPE_IM_HDMI2))


struct _CtImHdmi2Private
{
	int a;
};


/**
 * IMPL
 */
static void ct_im_hdmi2_constructor(CtImHdmi2 *self)
{
	CtImHdmi2Private *priv = CT_IM_HDMI2_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_hdmi2_destructor(CtImHdmi2 *self)
{
	CtImHdmi2Private *priv = CT_IM_HDMI2_GET_PRIVATE(self);

	priv->a = 0;
}


/**
 * PUBLIC
 */
VOID ct_im_hdmi2_printf1()
{
	// set parameter.
	new.videoPacketizer->vp_pr_cd.bit.desired_pr_factor = 0;									// No pixel repetition (pixel sent only once)
	new.videoPacketizer->vp_pr_cd.bit.color_depth = E_IM_HDMI_COLOR_DEPTH_8BIT;					// Color depth
	new.videoPacketizer->vp_remap = E_IM_HDMI_VP_REMAP_16BIT;									// Video Packetizer YCC422 Remapping
	new.videoPacketizer->vp_conf.bit.output_selector = E_IM_HDMI_OUTPUT_SELECTOR_PIXEL_PACKING; // Video Packetizer output selection
	new.videoPacketizer->vp_conf.bit.bypass_select = E_IM_HDMI_BYPASS_SELECT_PIXEL_REPEATER;	// bypass select
	new.videoPacketizer->vp_conf.bit.ycc422_en = D_IM_HDMI_ENABLE_OFF;							// YCC422 select disable
	new.videoPacketizer->vp_conf.bit.pr_en = D_IM_HDMI_ENABLE_OFF;								// Pixel repeater disable
	new.videoPacketizer->vp_conf.bit.pp_en = D_IM_HDMI_ENABLE_OFF;								// Pixel packing disable
	new.videoPacketizer->vp_conf.bit.bypass_en = D_IM_HDMI_ENABLE_OFF;							// Bypass disable
}

VOID ct_im_hdmi2_printf2()
{
	// set parameter.
	new.videoPacketizer->vp_pr_cd.bit.desired_pr_factor = 9;								   // Pixel sent 10 times
	new.videoPacketizer->vp_pr_cd.bit.color_depth = E_IM_HDMI_COLOR_DEPTH_16BIT;			   // Color depth
	new.videoPacketizer->vp_remap = E_IM_HDMI_VP_REMAP_24BIT;								   // Video Packetizer YCC422 Remapping
	new.videoPacketizer->vp_conf.bit.output_selector = E_IM_HDMI_OUTPUT_SELECTOR_8BIT_BYPASS;  // Video Packetizer output selection
	new.videoPacketizer->vp_conf.bit.bypass_select = E_IM_HDMI_BYPASS_SELECT_VIDEO_PACKETIZER; // bypass select
	new.videoPacketizer->vp_conf.bit.ycc422_en = D_IM_HDMI_ENABLE_ON;						   // YCC422 select enable
	new.videoPacketizer->vp_conf.bit.pr_en = D_IM_HDMI_ENABLE_ON;							   // Pixel repeater enable
	new.videoPacketizer->vp_conf.bit.pp_en = D_IM_HDMI_ENABLE_ON;							   // Pixel packing enable
	new.videoPacketizer->vp_conf.bit.bypass_en = D_IM_HDMI_ENABLE_ON;						   // Bypass enable
}

VOID ct_im_hdmi2_printf3()
{
	// check get data
	Ddim_Print(("----------\n"));
	Ddim_Print(("result:\n"));
	Ddim_Print(("vp_pr_cd : 0x%x\n", new.videoPacketizer->vp_pr_cd.byte));
	Ddim_Print(("vp_remap : 0x%x\n", new.videoPacketizer->vp_remap));
	Ddim_Print(("vp_conf  : 0x%x\n", new.videoPacketizer->vp_conf.byte));
	Ddim_Print(("register:\n"));
	Ddim_Print(("vp_pr_cd = %p\n", IO_DISP.HDMI_TX.vp_pr_cd.byte));
	Ddim_Print(("vp_remap = %p\n", IO_DISP.HDMI_TX.vp_remap.byte));
	Ddim_Print(("vp_conf  = %p\n", IO_DISP.HDMI_TX.vp_conf.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf4()
{
	// set parameter.
	new.audio->aud_conf0.bit.I2S_in_en = 0x00; // I2Sdata[0]~I2Sdata[3] disable
	new.audio->aud_conf0.bit.i2s_select = E_IM_HDMI_I2S_SELECT_S_PDIF;
	new.audio->aud_conf0.bit.sw_audio_fifo_rst = 0; //  no action taken
	new.audio->aud_conf1.bit.I2S_width = 16;		   // I2S input data width
	new.audio->aud_conf1.bit.I2S_mode = E_IM_HDMI_I2S_MODE_STANDARD;
	new.audio->aud_conf2.bit.HBR = D_IM_HDMI_ENABLE_OFF;	  // I2S HBR Mode Disable
	new.audio->aud_conf2.bit.NLPCM = D_IM_HDMI_ENABLE_OFF; // I2S NLPCM Mode Disable
	new.audio->aud_spdif1.bit.spdif_width = 16;			  // SPDIF input data width=16
	new.audio->aud_spdif1.bit.spdif_hbr_mode = 0;		  // Transmitted in the HDMI HBR packets
	new.audio->aud_spdif1.bit.setnlpcm = 0;				  // Non-Linear PCM mode
	new.audio->aud_inputclkfs = E_IM_HDMI_AUD_IFSFACTOR_128XFS;
	new.audio->fc_audiconf1.bit.SF = 0;				  // Sampling frequency=0.
	new.audio->fc_audiconf1.bit.SS = 0;				  // Sampling size=0.
	new.audio->fc_audsconf.bit.aud_packet_layout = 0;  // layout 0.
	new.audio->fc_audsconf.bit.aud_packet_sampflt = 0; // audio packet sample flat value=0.
}

VOID ct_im_hdmi2_printf5()
{
	// set parameter.
	new.audio->aud_conf0.bit.I2S_in_en = 0x0F; // I2Sdata[0]~I2Sdata[3] enable
	new.audio->aud_conf0.bit.i2s_select = E_IM_HDMI_I2S_SELECT_I2S;
	new.audio->aud_conf0.bit.sw_audio_fifo_rst = 1; // Resets all audio FIFOs
	new.audio->aud_conf1.bit.I2S_width = 24;		   // I2S input data width
	new.audio->aud_conf1.bit.I2S_mode = E_IM_HDMI_I2S_MODE_LEFT_JUSTIFIED;
	new.audio->aud_conf2.bit.HBR = D_IM_HDMI_ENABLE_ON;	 // I2S HBR Mode Enable
	new.audio->aud_conf2.bit.NLPCM = D_IM_HDMI_ENABLE_ON; // I2S NLPCM Mode Enable
	new.audio->aud_spdif1.bit.spdif_width = 24;			 // SPDIF input data width=24
	new.audio->aud_spdif1.bit.spdif_hbr_mode = 1;		 // Transmitted in the HDMI AUDS packets
	new.audio->aud_spdif1.bit.setnlpcm = 1;				 // Linear PCM mode
	new.audio->aud_inputclkfs = E_IM_HDMI_AUD_IFSFACTOR_64XFS;
	new.audio->fc_audiconf1.bit.SF = 7;				   // Sampling frequency=7.
	new.audio->fc_audiconf1.bit.SS = 3;				   // Sampling size=3.
	new.audio->fc_audsconf.bit.aud_packet_layout = 1;   // layout 1.
	new.audio->fc_audsconf.bit.aud_packet_sampflt = 15; // audio packet sample flat value=15.
}

VOID ct_im_hdmi2_printf6()
{
	// check get data
	Ddim_Print(("----------\n"));
	Ddim_Print(("result:\n"));
	Ddim_Print(("aud_conf0      : 0x%x\n", new.audio->aud_conf0.byte));
	Ddim_Print(("aud_conf1      : 0x%x\n", new.audio->aud_conf1.byte));
	Ddim_Print(("aud_conf2      : 0x%x\n", new.audio->aud_conf2.byte));
	Ddim_Print(("aud_spdif1     : 0x%x\n", new.audio->aud_spdif1.byte));
	Ddim_Print(("aud_inputclkfs : %d\n", new.audio->aud_inputclkfs));
	Ddim_Print(("fc_audiconf1   : 0x%x\n", new.audio->fc_audiconf1.byte));
	Ddim_Print(("fc_audsconf    : 0x%x\n", new.audio->fc_audsconf.byte));
	Ddim_Print(("register:\n"));
	Ddim_Print(("aud_conf0      = %p\n", IO_DISP.HDMI_TX.aud_conf0.byte));
	Ddim_Print(("aud_conf1      = %p\n", IO_DISP.HDMI_TX.aud_conf1.byte));
	Ddim_Print(("aud_conf2      = %p\n", IO_DISP.HDMI_TX.aud_conf2.byte));
	Ddim_Print(("aud_spdif1     = %p\n", IO_DISP.HDMI_TX.aud_spdif1.byte));
	Ddim_Print(("aud_inputclkfs = %p\n", IO_DISP.HDMI_TX.aud_inputclkfs.byte));
	Ddim_Print(("fc_audiconf1   = %p\n", IO_DISP.HDMI_TX.fc_audiconf1.byte));
	Ddim_Print(("fc_audsconf    = %p\n", IO_DISP.HDMI_TX.fc_audsconf.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf7()
{
	Ddim_Print(("register:\n"));
	Ddim_Print(("ih_mute_fc_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat0.byte));
	Ddim_Print(("ih_mute_fc_stat1   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat1.byte));
	Ddim_Print(("ih_mute_fc_stat2   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat2.byte));
	Ddim_Print(("ih_mute_as_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_as_stat0.byte));
	Ddim_Print(("ih_mute_phy_stat0  = %p\n", IO_DISP.HDMI_TX.ih_mute_phy_stat0.byte));
	Ddim_Print(("ih_mute_i2cm_stat0 = %p\n", IO_DISP.HDMI_TX.ih_mute_i2cm_stat0.byte));
	Ddim_Print(("ih_mute_cec_stat0  = %p\n", IO_DISP.HDMI_TX.ih_mute_cec_stat0.byte));
	Ddim_Print(("ih_mute_vp_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_vp_stat0.byte));
	Ddim_Print(("ih_i2cmphy_stat0   = %p\n", IO_DISP.HDMI_TX.ih_i2cmphy_stat0.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf8()
{
	Ddim_Print(("register:\n"));
	Ddim_Print(("ih_mute_fc_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat0.byte));
	Ddim_Print(("ih_mute_fc_stat1   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat1.byte));
	Ddim_Print(("ih_mute_fc_stat2   = %p\n", IO_DISP.HDMI_TX.ih_mute_fc_stat2.byte));
	Ddim_Print(("ih_mute_as_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_as_stat0.byte));
	Ddim_Print(("ih_mute_phy_stat0  = %p\n", IO_DISP.HDMI_TX.ih_mute_phy_stat0.byte));
	Ddim_Print(("ih_mute_i2cm_stat0 = %p\n", IO_DISP.HDMI_TX.ih_mute_i2cm_stat0.byte));
	Ddim_Print(("ih_mute_cec_stat0  = %p\n", IO_DISP.HDMI_TX.ih_mute_cec_stat0.byte));
	Ddim_Print(("ih_mute_vp_stat0   = %p\n", IO_DISP.HDMI_TX.ih_mute_vp_stat0.byte));
	Ddim_Print(("ih_i2cmphy_stat0   = %p\n", IO_DISP.HDMI_TX.ih_i2cmphy_stat0.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf9()
{
	// set parameter.
	new.cscConfig->csc_cfg.bit.decmode = 0;									  // Chroma decimation configuration
	new.cscConfig->csc_cfg.bit.intmode = 0;									  // Chroma interpolation configuration.
	new.cscConfig->csc_cfg.bit.csc_limit = D_IM_HDMI_ENABLE_OFF;				  // CSC limit setting disable.
	new.cscConfig->csc_scale.bit.cscscale = 0;								  // Scale factor.
	new.cscConfig->csc_scale.bit.csc_color_depth = E_IM_HDMI_COLOR_DEPTH_8BIT; // csc_color_depth.
}

VOID ct_im_hdmi2_printf10()
{
	// set parameter.
	new.cscConfig->csc_cfg.bit.decmode = 3;									   // Chroma decimation configuration
	new.cscConfig->csc_cfg.bit.intmode = 3;									   // Chroma interpolation configuration.
	new.cscConfig->csc_cfg.bit.csc_limit = D_IM_HDMI_ENABLE_ON;				   // CSC limit setting enable.
	new.cscConfig->csc_scale.bit.cscscale = 2;								   // Scale factor.
	new.cscConfig->csc_scale.bit.csc_color_depth = E_IM_HDMI_COLOR_DEPTH_16BIT; // csc_color_depth.
}

VOID ct_im_hdmi2_printf11()
{
	// check register
	Ddim_Print(("----------\n"));
	Ddim_Print(("register:\n"));
	Ddim_Print(("PLLCTRL       = 0x%x\n", IO_DISP.HDMI_TX.PLLCTRL.hword));
	Ddim_Print(("PLLGMPCTRL    = 0x%x\n", IO_DISP.HDMI_TX.PLLGMPCTRL.hword));
	Ddim_Print(("PLLCURRCTRL   = 0x%x\n", IO_DISP.HDMI_TX.PLLCURRCTRL.hword));
	Ddim_Print(("OPMODE_PLLCFG = 0x%x\n", IO_DISP.HDMI_TX.OPMODE_PLLCFG.hword));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf12()
{
	Ddim_Print(("register:\n"));
	Ddim_Print(("PLLCTRL       = 0x%x\n", IO_DISP.HDMI_TX.PLLCTRL.hword));
	Ddim_Print(("PLLGMPCTRL    = 0x%x\n", IO_DISP.HDMI_TX.PLLGMPCTRL.hword));
	Ddim_Print(("PLLCURRCTRL   = 0x%x\n", IO_DISP.HDMI_TX.PLLCURRCTRL.hword));
	Ddim_Print(("OPMODE_PLLCFG = 0x%x\n", IO_DISP.HDMI_TX.OPMODE_PLLCFG.hword));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf13()
{
	// check get data
	Ddim_Print(("----------\n"));
	Ddim_Print(("register:\n"));
	Ddim_Print(("vp_pr_cd = %p\n", IO_DISP.HDMI_TX.vp_pr_cd.byte));
	Ddim_Print(("vp_remap = %p\n", IO_DISP.HDMI_TX.vp_remap.byte));
	Ddim_Print(("vp_conf  = %p\n", IO_DISP.HDMI_TX.vp_conf.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi2_printf14()
{
	// i2cm Config.
	new.i2cmConfig->i2cm_address = 0x00;
	new.i2cmConfig->i2cm_segaddr = 0x00;
	new.i2cmConfig->i2cm_segptr = 0x00;
	new.i2cmConfig->i2cm_operation = E_IM_HDMI_I2CM_OPERATION_RD;
}

VOID ct_im_hdmi2_printf15()
{
	// i2cm Config.
	new.i2cmConfig->i2cm_address = 0xFF;
	new.i2cmConfig->i2cm_segaddr = 0xFF;
	new.i2cmConfig->i2cm_segptr = 0xFF;
	new.i2cmConfig->i2cm_operation = E_IM_HDMI_I2CM_OPERATION_WR;
}

CtImHdmi2 *ct_im_hdmi2_new(void)
{
	CtImHdmi2 *self = k_object_new_with_private(CT_TYPE_IM_HDMI2, sizeof(CtImHdmi2Private));

	return self;
}

CtImHdmi2 *ct_im_hdmi2_get(void)
{
	static CtImHdmi2 *self = NULL;

	if (!self)
	{
		self = k_object_new_with_private(CT_TYPE_IM_HDMI2, sizeof(CtImHdmi2Private));
	}

	return self;
}
