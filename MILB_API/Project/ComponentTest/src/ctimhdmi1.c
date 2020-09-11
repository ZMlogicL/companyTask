/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 杨文
*@brief : CtImHdmi1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimhdmi.h"


typedef struct _DATA
{
	T_IM_HDMI_CTRL *ctrl;
	T_IM_HDMI_FRAME_COMPOSER *frameComposer;

} DATA;
DATA data;


K_TYPE_DEFINE_WITH_PRIVATE(CtImHdmi1, ct_im_hdmi1)
#define CT_IM_HDMI1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImHdmi1Private, CT_TYPE_IM_HDMI1))


struct _CtImHdmi1Private
{
	int a;
};

/**
 * DECLS
 */
#ifdef CO_DEBUG_ON_PC
static void ctImHdmiSetCmd( int cmdArgc, char* cmdArgv );
#endif	// CO_DEBUG_ON_PC


/**
 * IMPL
 */
static void ct_im_hdmi1_constructor(CtImHdmi1 *self)
{
	CtImHdmi1Private *priv = CT_IM_HDMI1_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_hdmi1_destructor(CtImHdmi1 *self)
{
	CtImHdmi1Private *priv = CT_IM_HDMI1_GET_PRIVATE(self);

	priv->a = 0;
}

#ifdef CO_DEBUG_ON_PC
static void ctImHdmiSetCmd( int cmdArgc, char* cmdArgv ) 
{ 
	INT32 j;
	INT32 cmd_pos = 0;

	for( j = 0; j < cmdArgc; j++ ) { 
		gCmdArgv[ j ] = ( cmdArgv + ( cmd_pos * CtImHdmi_D_HDMI_TEST_CMD_LEN ) ); 
		cmd_pos++;
	}
}
#endif	// CO_DEBUG_ON_PC


/**
 * PUBLIC
 */
VOID ct_im_hdmi1_printf1()
{
	Ddim_Print(("----------\n"));
	Ddim_Print(("tx_invid0        = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte));
	Ddim_Print(("fc_invidconf     = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0     = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1     = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_invactiv0     = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1     = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_inhblank0     = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1     = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invblank      = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_vsyncindelay  = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_hsyncinwidth0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth1.byte));
	Ddim_Print(("fc_vsyncinwidth  = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("fc_ctrldur       = 0x%x\n", IO_DISP.HDMI_TX.fc_ctrldur));
	Ddim_Print(("fc_exctrldur     = 0x%x\n", IO_DISP.HDMI_TX.fc_exctrldur));
	Ddim_Print(("fc_exctrlspac    = 0x%x\n", IO_DISP.HDMI_TX.fc_exctrlspac));
	Ddim_Print(("fc_ch0pream      = 0x%x\n", IO_DISP.HDMI_TX.fc_ch0pream));
	Ddim_Print(("fc_ch1pream      = %p\n", IO_DISP.HDMI_TX.fc_ch1pream.byte));
	Ddim_Print(("fc_ch2pream      = %p\n", IO_DISP.HDMI_TX.fc_ch2pream.byte));
	Ddim_Print(("mc_clkdis        = %p\n", IO_DISP.HDMI_TX.mc_clkdis.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi1_printf2()
{
	Ddim_Print(("----------\n"));
	Ddim_Print(("tx_invid0        = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte));
	Ddim_Print(("fc_invidconf     = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0     = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1     = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_invactiv0     = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1     = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_inhblank0     = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1     = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invblank      = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_vsyncindelay  = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_hsyncinwidth0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth1.byte));
	Ddim_Print(("fc_vsyncinwidth  = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("fc_ctrldur       = 0x%x\n", IO_DISP.HDMI_TX.fc_ctrldur));
	Ddim_Print(("fc_exctrldur     = 0x%x\n", IO_DISP.HDMI_TX.fc_exctrldur));
	Ddim_Print(("fc_exctrlspac    = 0x%x\n", IO_DISP.HDMI_TX.fc_exctrlspac));
	Ddim_Print(("fc_ch0pream      = 0x%x\n", IO_DISP.HDMI_TX.fc_ch0pream));
	Ddim_Print(("fc_ch1pream      = %p\n", IO_DISP.HDMI_TX.fc_ch1pream.byte));
	Ddim_Print(("fc_ch2pream      = %p\n", IO_DISP.HDMI_TX.fc_ch2pream.byte));
	Ddim_Print(("mc_clkdis        = %p\n", IO_DISP.HDMI_TX.mc_clkdis.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi1_printf3()
{
	Ddim_Print(("----------\n"));
	Ddim_Print(("read data:\n"));
}

VOID ct_im_hdmi1_printf4()
{
	Ddim_Print(("register:\n"));
	Ddim_Print(("i2cm_slave     = %p\n", IO_DISP.HDMI_TX.i2cm_slave.byte));
	Ddim_Print(("i2cm_segaddr   = %p\n", IO_DISP.HDMI_TX.i2cm_segaddr.byte));
	Ddim_Print(("i2cm_segptr    = 0x%x\n", IO_DISP.HDMI_TX.i2cm_segptr));
	Ddim_Print(("i2cm_operation = %p\n", IO_DISP.HDMI_TX.i2cm_operation.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi1_printf5()
{
	Ddim_Print(("Im_HDMI_Ctrl() : Normal end\n"));
	// check register
	Ddim_Print(("----------\n"));
	Ddim_Print(("register:\n"));
	Ddim_Print(("tx_invid0          = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte));
	Ddim_Print(("fc_invidconf       = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0       = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1       = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_invactiv0       = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1       = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_invact_2d0      = %p\n", IO_DISP.HDMI_TX.fc_invact_2d0.byte));
	Ddim_Print(("fc_invact_2d1      = %p\n", IO_DISP.HDMI_TX.fc_invact_2d1.byte));
	Ddim_Print(("fc_actspc_hdlr_cfg = %p\n", IO_DISP.HDMI_TX.fc_actspc_hdlr_cfg.byte));
	Ddim_Print(("fc_inhblank0       = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1       = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invblank        = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0   = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1   = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_vsyncindelay    = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_hsyncinwidth0   = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth1   = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth1.byte));
	Ddim_Print(("fc_vsyncinwidth    = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("PLL\n"));
	Ddim_Print((" - vp_pr_cd         = %p\n", IO_DISP.HDMI_TX.vp_pr_cd.byte));
	Ddim_Print((" - phy_i2cm_address = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_address));
	Ddim_Print((" - phy_i2cm_datao_0 = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_datao_0));
	Ddim_Print((" - phy_i2cm_datao_1 = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_datao_1));
	Ddim_Print(("Audio\n"));
	Ddim_Print((" - aud_conf0      = %p\n", IO_DISP.HDMI_TX.aud_conf0.byte));
	Ddim_Print((" - aud_conf1      = %p\n", IO_DISP.HDMI_TX.aud_conf1.byte));
	Ddim_Print((" - aud_conf2      = %p\n", IO_DISP.HDMI_TX.aud_conf2.byte));
	Ddim_Print((" - aud_spdif1     = %p\n", IO_DISP.HDMI_TX.aud_spdif1.byte));
	Ddim_Print((" - aud_inputclkfs = %p\n", IO_DISP.HDMI_TX.aud_inputclkfs.byte));
	Ddim_Print((" - aud_n1         = 0x%x\n", IO_DISP.HDMI_TX.aud_n1));
	Ddim_Print((" - aud_n2         = 0x%x\n", IO_DISP.HDMI_TX.aud_n2));
	Ddim_Print((" - aud_n3         = %p\n", IO_DISP.HDMI_TX.aud_n3.byte));
	Ddim_Print((" - aud_cts1       = 0x%x\n", IO_DISP.HDMI_TX.aud_cts1));
	Ddim_Print((" - aud_cts2       = 0x%x\n", IO_DISP.HDMI_TX.aud_cts2));
	Ddim_Print((" - aud_cts3       = %p\n", IO_DISP.HDMI_TX.aud_cts3.byte));
	Ddim_Print(("Infoframes\n"));
	Ddim_Print((" - fc_aviconf0       = %p\n", IO_DISP.HDMI_TX.fc_aviconf0.byte));
	Ddim_Print((" - fc_aviconf1       = %p\n", IO_DISP.HDMI_TX.fc_aviconf1.byte));
	Ddim_Print((" - fc_aviconf2       = %p\n", IO_DISP.HDMI_TX.fc_aviconf2.byte));
	Ddim_Print((" - fc_aviconf3       = %p\n", IO_DISP.HDMI_TX.fc_aviconf3.byte));
	Ddim_Print((" - fc_avivid         = %p\n", IO_DISP.HDMI_TX.fc_avivid.byte));
	Ddim_Print((" - fc_prconf         = %p\n", IO_DISP.HDMI_TX.fc_prconf.byte));
	Ddim_Print((" - fc_audiconf0      = %p\n", IO_DISP.HDMI_TX.fc_audiconf0.byte));
	Ddim_Print((" - fc_audiconf1      = %p\n", IO_DISP.HDMI_TX.fc_audiconf1.byte));
	Ddim_Print((" - fc_audiconf2      = 0x%x\n", IO_DISP.HDMI_TX.fc_audiconf2));
	Ddim_Print((" - fc_audiconf3      = %p\n", IO_DISP.HDMI_TX.fc_audiconf3.byte));
	Ddim_Print((" - fc_vsdieeeid0     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid0));
	Ddim_Print((" - fc_vsdieeeid1     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid1));
	Ddim_Print((" - fc_vsdieeeid2     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid2));
}

VOID ct_im_hdmi1_printf6()
{
	Ddim_Print(("Im_HDMI_Get_Ctrl() : Normal end\n"));
	// check register
	Ddim_Print(("----------\n"));
	Ddim_Print(("result:\n"));
	Ddim_Print(("video_input_mapping = 0x%x\n", data.ctrl->video_input_mapping));
	Ddim_Print(("vsync_in_polarity   = 0x%x\n", data.ctrl->vsync_in_polarity));
	Ddim_Print(("hsync_in_polarity   = 0x%x\n", data.ctrl->hsync_in_polarity));
	Ddim_Print(("de_in_polarity      = 0x%x\n", data.ctrl->de_in_polarity));
	Ddim_Print(("DVI_modez           = 0x%x\n", data.ctrl->DVI_modez));
	Ddim_Print(("r_v_blank_in_osc    = 0x%x\n", data.ctrl->r_v_blank_in_osc));
	Ddim_Print(("in_i_p              = 0x%x\n", data.ctrl->in_i_p));
	Ddim_Print(("h_in_activ          = 0x%x\n", data.ctrl->h_in_activ));
	Ddim_Print(("v_in_activ          = 0x%x\n", data.ctrl->v_in_activ));
	Ddim_Print(("fc_invact_2d        = 0x%x\n", data.ctrl->fc_invact_2d));
	Ddim_Print(("fc_actspc_hdlr_cfg  = 0x%x\n", data.ctrl->fc_actspc_hdlr_cfg.byte));
	Ddim_Print(("fc_inhblank         = 0x%x\n", data.ctrl->fc_inhblank));
	Ddim_Print(("fc_invblank         = 0x%x\n", data.ctrl->fc_invblank));
	Ddim_Print(("fc_hsyncindelay     = 0x%x\n", data.ctrl->fc_hsyncindelay));
	Ddim_Print(("fc_hsyncinwidth     = 0x%x\n", data.ctrl->fc_hsyncinwidth));
	Ddim_Print(("fc_vsyncindelay     = 0x%x\n", data.ctrl->fc_vsyncindelay));
	Ddim_Print(("fc_vsyncinwidth     = 0x%x\n", data.ctrl->fc_vsyncinwidth));
	Ddim_Print(("pll_config\n"));
	Ddim_Print((" - vp_pr_cd          = 0x%x\n", data.ctrl->pll_config.vp_pr_cd.byte));
	//	Ddim_Print( (" - phy_i2cm_address  = 0x%x\n", data.ctrl->pll_config.phy_i2cm_address) );
	//	Ddim_Print( (" - phy_i2cm_datao[0] = 0x%x\n", data.ctrl->pll_config.phy_i2cm_datao[0]) );
	//	Ddim_Print( (" - phy_i2cm_datao[1] = 0x%x\n", data.ctrl->pll_config.phy_i2cm_datao[1]) );
	Ddim_Print(("audio_confi\n"));
	Ddim_Print((" - i2s_select      = 0x%x\n", data.ctrl->audio_config.i2s_select));
	Ddim_Print((" - aud_conf1       = 0x%x\n", data.ctrl->audio_config.aud_conf1.byte));
	Ddim_Print((" - aud_conf2       = 0x%x\n", data.ctrl->audio_config.aud_conf2.byte));
	Ddim_Print((" - aud_spdif1      = 0x%x\n", data.ctrl->audio_config.aud_spdif1.byte));
	Ddim_Print((" - aud_inputclkfs  = 0x%x\n", data.ctrl->audio_config.aud_inputclkfs));
	Ddim_Print((" - aud_n1          = 0x%x\n", data.ctrl->audio_config.aud_n1));
	Ddim_Print((" - aud_n2          = 0x%x\n", data.ctrl->audio_config.aud_n2));
	Ddim_Print((" - aud_n3_audn     = 0x%x\n", data.ctrl->audio_config.aud_n3_audn));
	Ddim_Print((" - cts_manual      = 0x%x\n", data.ctrl->audio_config.cts_manual));
	Ddim_Print((" - aud_cts1        = 0x%x\n", data.ctrl->audio_config.aud_cts1));
	Ddim_Print((" - aud_cts2        = 0x%x\n", data.ctrl->audio_config.aud_cts2));
	Ddim_Print((" - aud_cts3_audcts = 0x%x\n", data.ctrl->audio_config.aud_cts3_audcts));
	Ddim_Print(("info_frames\n"));
	Ddim_Print((" - fc_aviconf0             = 0x%x\n", data.ctrl->info_frames.fc_aviconf0.byte));
	Ddim_Print((" - fc_aviconf1             = 0x%x\n", data.ctrl->info_frames.fc_aviconf1.byte));
	Ddim_Print((" - fc_aviconf2             = 0x%x\n", data.ctrl->info_frames.fc_aviconf2.byte));
	Ddim_Print((" - fc_aviconf3             = 0x%x\n", data.ctrl->info_frames.fc_aviconf3.byte));
	Ddim_Print((" - fc_avivid               = 0x%x\n", data.ctrl->info_frames.fc_avivid));
	Ddim_Print((" - fc_prconf               = 0x%x\n", data.ctrl->info_frames.fc_prconf.byte));
	Ddim_Print((" - fc_audiconf0            = 0x%x\n", data.ctrl->info_frames.fc_audiconf0.byte));
	Ddim_Print((" - fc_audiconf1            = 0x%x\n", data.ctrl->info_frames.fc_audiconf1.byte));
	Ddim_Print((" - fc_audiconf2            = 0x%x\n", data.ctrl->info_frames.fc_audiconf2));
	Ddim_Print((" - fc_audiconf3            = 0x%x\n", data.ctrl->info_frames.fc_audiconf3.byte));
	Ddim_Print((" - fc_vsdieeeid[0]         = 0x%x\n", data.ctrl->info_frames.fc_vsdieeeid[0]));
	Ddim_Print((" - fc_vsdieeeid[1]         = 0x%x\n", data.ctrl->info_frames.fc_vsdieeeid[1]));
	Ddim_Print((" - fc_vsdieeeid[2]         = 0x%x\n", data.ctrl->info_frames.fc_vsdieeeid[2]));
	Ddim_Print((" - video_mode              = 0x%x\n", data.ctrl->info_frames.video_mode));
	Ddim_Print((" - video_format            = 0x%x\n", data.ctrl->info_frames.video_format));
	Ddim_Print((" - meta_present            = 0x%x\n", data.ctrl->info_frames.meta_present));
	Ddim_Print((" - additional_video_format = 0x%x\n", data.ctrl->info_frames.additional_video_format));
	Ddim_Print((" - meta_type               = 0x%x\n", data.ctrl->info_frames.meta_type));
	Ddim_Print((" - meta_length             = 0x%x\n", data.ctrl->info_frames.meta_length));
	Ddim_Print((" - meta_data[0]            = 0x%x\n", data.ctrl->info_frames.meta_data[0]));
	Ddim_Print((" - meta_data[1]            = 0x%x\n", data.ctrl->info_frames.meta_data[1]));
	Ddim_Print((" - meta_data[2]            = 0x%x\n", data.ctrl->info_frames.meta_data[2]));
	Ddim_Print((" - meta_data[3]            = 0x%x\n", data.ctrl->info_frames.meta_data[3]));
	Ddim_Print((" - meta_data[4]            = 0x%x\n", data.ctrl->info_frames.meta_data[4]));
	Ddim_Print((" - meta_data[5]            = 0x%x\n", data.ctrl->info_frames.meta_data[5]));
	Ddim_Print((" - meta_data[6]            = 0x%x\n", data.ctrl->info_frames.meta_data[6]));
	Ddim_Print((" - meta_data[7]            = 0x%x\n", data.ctrl->info_frames.meta_data[7]));
	Ddim_Print(("register:\n"));
	Ddim_Print(("tx_invid0          = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte));
	Ddim_Print(("fc_invidconf       = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0       = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1       = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_invactiv0       = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1       = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_invact_2d0      = %p\n", IO_DISP.HDMI_TX.fc_invact_2d0.byte));
	Ddim_Print(("fc_invact_2d1      = %p\n", IO_DISP.HDMI_TX.fc_invact_2d1.byte));
	Ddim_Print(("fc_actspc_hdlr_cfg = %p\n", IO_DISP.HDMI_TX.fc_actspc_hdlr_cfg.byte));
	Ddim_Print(("fc_inhblank0       = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1       = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invblank        = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0   = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1   = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_vsyncindelay    = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_hsyncinwidth0   = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth1   = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth1.byte));
	Ddim_Print(("fc_vsyncinwidth    = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("PLL\n"));
	Ddim_Print((" - vp_pr_cd         = %p\n", IO_DISP.HDMI_TX.vp_pr_cd.byte));
	Ddim_Print((" - phy_i2cm_address = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_address));
	Ddim_Print((" - phy_i2cm_datao_0 = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_datao_0));
	Ddim_Print((" - phy_i2cm_datao_1 = 0x%x\n", IO_DISP.HDMI_TX.phy_i2cm_datao_1));
	Ddim_Print(("Audio\n"));
	Ddim_Print((" - aud_conf0      = %p\n", IO_DISP.HDMI_TX.aud_conf0.byte));
	Ddim_Print((" - aud_conf1      = %p\n", IO_DISP.HDMI_TX.aud_conf1.byte));
	Ddim_Print((" - aud_conf2      = %p\n", IO_DISP.HDMI_TX.aud_conf2.byte));
	Ddim_Print((" - aud_spdif1     = %p\n", IO_DISP.HDMI_TX.aud_spdif1.byte));
	Ddim_Print((" - aud_inputclkfs = %p\n", IO_DISP.HDMI_TX.aud_inputclkfs.byte));
	Ddim_Print((" - aud_n1         = 0x%x\n", IO_DISP.HDMI_TX.aud_n1));
	Ddim_Print((" - aud_n2         = 0x%x\n", IO_DISP.HDMI_TX.aud_n2));
	Ddim_Print((" - aud_n3         = %p\n", IO_DISP.HDMI_TX.aud_n3.byte));
	Ddim_Print((" - aud_cts1       = 0x%x\n", IO_DISP.HDMI_TX.aud_cts1));
	Ddim_Print((" - aud_cts2       = 0x%x\n", IO_DISP.HDMI_TX.aud_cts2));
	Ddim_Print((" - aud_cts3       = %p\n", IO_DISP.HDMI_TX.aud_cts3.byte));
	Ddim_Print(("Infoframes\n"));
	Ddim_Print((" - fc_aviconf0       = %p\n", IO_DISP.HDMI_TX.fc_aviconf0.byte));
	Ddim_Print((" - fc_aviconf1       = %p\n", IO_DISP.HDMI_TX.fc_aviconf1.byte));
	Ddim_Print((" - fc_aviconf2       = %p\n", IO_DISP.HDMI_TX.fc_aviconf2.byte));
	Ddim_Print((" - fc_aviconf3       = %p\n", IO_DISP.HDMI_TX.fc_aviconf3.byte));
	Ddim_Print((" - fc_avivid         = %p\n", IO_DISP.HDMI_TX.fc_avivid.byte));
	Ddim_Print((" - fc_prconf         = %p\n", IO_DISP.HDMI_TX.fc_prconf.byte));
	Ddim_Print((" - fc_audiconf0      = %p\n", IO_DISP.HDMI_TX.fc_audiconf0.byte));
	Ddim_Print((" - fc_audiconf1      = %p\n", IO_DISP.HDMI_TX.fc_audiconf1.byte));
	Ddim_Print((" - fc_audiconf2      = 0x%x\n", IO_DISP.HDMI_TX.fc_audiconf2));
	Ddim_Print((" - fc_audiconf3      = %p\n", IO_DISP.HDMI_TX.fc_audiconf3.byte));
	Ddim_Print((" - fc_vsdieeeid0     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid0));
	Ddim_Print((" - fc_vsdieeeid1     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid1));
	Ddim_Print((" - fc_vsdieeeid2     = 0x%x\n", IO_DISP.HDMI_TX.fc_vsdieeeid2));
}

VOID ct_im_hdmi1_printf7()
{
	// set paramter.
	data.ctrl->video_input_mapping = E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT;
	data.ctrl->vsync_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->hsync_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->de_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->DVI_modez = D_IM_HDMI_DVI_MODEZ_DVI;
	data.ctrl->r_v_blank_in_osc = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->in_i_p = D_IM_HDMI_IN_I_P_PROGRESSIVE;
	data.ctrl->h_in_activ = 0;
	data.ctrl->v_in_activ = 0;
	data.ctrl->fc_invact_2d = 0;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_en = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_tgl = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->fc_inhblank = 0;
	data.ctrl->fc_invblank = 0;
	data.ctrl->fc_hsyncindelay = 0;
	data.ctrl->fc_hsyncinwidth = 0;
	data.ctrl->fc_vsyncindelay = 0;
	data.ctrl->fc_vsyncinwidth = 0;
	// PLL
	data.ctrl->pll_config.vp_pr_cd.bit.desired_pr_factor = 0;
	data.ctrl->pll_config.vp_pr_cd.bit.color_depth = E_IM_HDMI_COLOR_DEPTH_8BIT;
	//				data.ctrl->pll_config.phy_i2cm_address								= 0x00;
	//				data.ctrl->pll_config.phy_i2cm_datao[0]								= 0x00;
	//				data.ctrl->pll_config.phy_i2cm_datao[1]								= 0x00;
	// Audio
	data.ctrl->audio_config.i2s_select = E_IM_HDMI_I2S_SELECT_I2S;
	data.ctrl->audio_config.aud_conf1.bit.I2S_width = 16;
	data.ctrl->audio_config.aud_conf1.bit.I2S_mode = E_IM_HDMI_I2S_MODE_STANDARD;
	data.ctrl->audio_config.aud_conf2.bit.HBR = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_conf2.bit.NLPCM = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_width = 16;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_hbr_mode = 0;
	data.ctrl->audio_config.aud_spdif1.bit.setnlpcm = 0;
	data.ctrl->audio_config.aud_inputclkfs = E_IM_HDMI_AUD_IFSFACTOR_128XFS;
	data.ctrl->audio_config.aud_n1 = 0;
	data.ctrl->audio_config.aud_n2 = 0;
	data.ctrl->audio_config.aud_n3_audn = 0;
	data.ctrl->audio_config.cts_manual = E_IM_HDMI_CTS_MANUAL_AUTO;
	data.ctrl->audio_config.aud_cts1 = 0;
	data.ctrl->audio_config.aud_cts2 = 0;
	data.ctrl->audio_config.aud_cts3_audcts = 0;
	// Infoframes
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.bar_information = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.scan_information = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.active_format_present = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication_2 = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.active_aspect_ratio = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.picture_aspect_ratio = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.Colorimetry = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.non_uniform_picture_scaling = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.quantization_range = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.extended_colorimetry = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.it_content = 0;
	data.ctrl->info_frames.fc_aviconf3.bit.CN = 0;
	data.ctrl->info_frames.fc_aviconf3.bit.YQ = 0;
	data.ctrl->info_frames.fc_avivid = 0;
	data.ctrl->info_frames.fc_prconf.bit.output_pr_factor = 0;
	data.ctrl->info_frames.fc_prconf.bit.incoming_pr_factor = 0;
	data.ctrl->info_frames.fc_audiconf0.bit.CT = 0;
	data.ctrl->info_frames.fc_audiconf0.bit.CC = 0;
	data.ctrl->info_frames.fc_audiconf1.bit.SF = 0;
	data.ctrl->info_frames.fc_audiconf1.bit.SS = 0;
	data.ctrl->info_frames.fc_audiconf2 = 0;
	data.ctrl->info_frames.fc_audiconf3.bit.LSV = 0;
	data.ctrl->info_frames.fc_audiconf3.bit.DM_INH = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->info_frames.fc_audiconf3.bit.LFEPBL = 0;
	data.ctrl->info_frames.fc_vsdieeeid[0] = 0;
	data.ctrl->info_frames.fc_vsdieeeid[1] = 0;
	data.ctrl->info_frames.fc_vsdieeeid[2] = 0;
	data.ctrl->info_frames.video_mode = D_IM_HDMI_VIDEO_MODE_HDMI;
	data.ctrl->info_frames.video_format = 0;
	data.ctrl->info_frames.meta_present = 0;
	data.ctrl->info_frames.additional_video_format = 0;
	data.ctrl->info_frames.meta_type = 0;
	data.ctrl->info_frames.meta_length = 0;
	data.ctrl->info_frames.meta_data[0] = 0;
	data.ctrl->info_frames.meta_data[1] = 0;
	data.ctrl->info_frames.meta_data[2] = 0;
	data.ctrl->info_frames.meta_data[3] = 0;
	data.ctrl->info_frames.meta_data[4] = 0;
	data.ctrl->info_frames.meta_data[5] = 0;
	data.ctrl->info_frames.meta_data[6] = 0;
	data.ctrl->info_frames.meta_data[7] = 0;
}

VOID ct_im_hdmi1_printf8()
{
	// set paramter.
	data.ctrl->video_input_mapping = E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_16BIT;
	data.ctrl->vsync_in_polarity = D_IM_HDMI_ACTIVE_HIGH;
	data.ctrl->hsync_in_polarity = D_IM_HDMI_ACTIVE_HIGH;
	data.ctrl->de_in_polarity = D_IM_HDMI_ACTIVE_HIGH;
	data.ctrl->DVI_modez = D_IM_HDMI_DVI_MODEZ_HDMI;
	data.ctrl->r_v_blank_in_osc = D_IM_HDMI_ACTIVE_HIGH;
	data.ctrl->in_i_p = D_IM_HDMI_IN_I_P_INTERLACED;
	data.ctrl->h_in_activ = 16383;
	data.ctrl->v_in_activ = 8191;
	data.ctrl->fc_invact_2d = 0xFF;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_en = D_IM_HDMI_ENABLE_ON;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_tgl = D_IM_HDMI_ENABLE_ON;
	data.ctrl->fc_inhblank = 8191;
	data.ctrl->fc_invblank = 255;
	data.ctrl->fc_hsyncindelay = 8191;
	data.ctrl->fc_hsyncinwidth = 1023;
	data.ctrl->fc_vsyncindelay = 255;
	data.ctrl->fc_vsyncinwidth = 63;
	// PLL
	data.ctrl->pll_config.vp_pr_cd.bit.desired_pr_factor = 9;
	data.ctrl->pll_config.vp_pr_cd.bit.color_depth = E_IM_HDMI_COLOR_DEPTH_16BIT;
	//				data.ctrl->pll_config.phy_i2cm_address								= 0xFF;
	//				data.ctrl->pll_config.phy_i2cm_datao[0]								= 0xFF;
	//				data.ctrl->pll_config.phy_i2cm_datao[1]								= 0xFF;
	// Audio
	data.ctrl->audio_config.i2s_select = E_IM_HDMI_I2S_SELECT_I2S;
	data.ctrl->audio_config.aud_conf1.bit.I2S_width = 16;
	data.ctrl->audio_config.aud_conf1.bit.I2S_mode = E_IM_HDMI_I2S_MODE_STANDARD;
	data.ctrl->audio_config.aud_conf2.bit.HBR = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_conf2.bit.NLPCM = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_width = 24;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_hbr_mode = 1;
	data.ctrl->audio_config.aud_spdif1.bit.setnlpcm = 1;
	data.ctrl->audio_config.aud_inputclkfs = E_IM_HDMI_AUD_IFSFACTOR_64XFS;
	data.ctrl->audio_config.aud_n1 = 0xFF;
	data.ctrl->audio_config.aud_n2 = 0xFF;
	data.ctrl->audio_config.aud_n3_audn = 0xF;
	data.ctrl->audio_config.cts_manual = E_IM_HDMI_CTS_MANUAL_MANUAL;
	data.ctrl->audio_config.aud_cts1 = 0xFF;
	data.ctrl->audio_config.aud_cts2 = 0xFF;
	data.ctrl->audio_config.aud_cts3_audcts = 0xF;
	// Infoframes
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication = 3;
	data.ctrl->info_frames.fc_aviconf0.bit.bar_information = 3;
	data.ctrl->info_frames.fc_aviconf0.bit.scan_information = 3;
	data.ctrl->info_frames.fc_aviconf0.bit.active_format_present = 1;
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication_2 = 1;
	data.ctrl->info_frames.fc_aviconf1.bit.active_aspect_ratio = 15;
	data.ctrl->info_frames.fc_aviconf1.bit.picture_aspect_ratio = 3;
	data.ctrl->info_frames.fc_aviconf1.bit.Colorimetry = 3;
	data.ctrl->info_frames.fc_aviconf2.bit.non_uniform_picture_scaling = 3;
	data.ctrl->info_frames.fc_aviconf2.bit.quantization_range = 3;
	data.ctrl->info_frames.fc_aviconf2.bit.extended_colorimetry = 7;
	data.ctrl->info_frames.fc_aviconf2.bit.it_content = 1;
	data.ctrl->info_frames.fc_aviconf3.bit.CN = 3;
	data.ctrl->info_frames.fc_aviconf3.bit.YQ = 3;
	data.ctrl->info_frames.fc_avivid = 255;
	data.ctrl->info_frames.fc_prconf.bit.output_pr_factor = 10;
	data.ctrl->info_frames.fc_prconf.bit.incoming_pr_factor = 10;
	data.ctrl->info_frames.fc_audiconf0.bit.CT = 15;
	data.ctrl->info_frames.fc_audiconf0.bit.CC = 7;
	data.ctrl->info_frames.fc_audiconf1.bit.SF = 7;
	data.ctrl->info_frames.fc_audiconf1.bit.SS = 3;
	data.ctrl->info_frames.fc_audiconf2 = 255;
	data.ctrl->info_frames.fc_audiconf3.bit.LSV = 0xF;
	data.ctrl->info_frames.fc_audiconf3.bit.DM_INH = D_IM_HDMI_ENABLE_ON;
	data.ctrl->info_frames.fc_audiconf3.bit.LFEPBL = 3;
	data.ctrl->info_frames.fc_vsdieeeid[0] = 255;
	data.ctrl->info_frames.fc_vsdieeeid[1] = 255;
	data.ctrl->info_frames.fc_vsdieeeid[2] = 255;
	data.ctrl->info_frames.video_mode = D_IM_HDMI_VIDEO_MODE_3D;
	data.ctrl->info_frames.video_format = 255;
	data.ctrl->info_frames.meta_present = 1;
	data.ctrl->info_frames.additional_video_format = 15;
	data.ctrl->info_frames.meta_type = 7;
	data.ctrl->info_frames.meta_length = 31;
	data.ctrl->info_frames.meta_data[0] = 255;
	data.ctrl->info_frames.meta_data[1] = 255;
	data.ctrl->info_frames.meta_data[2] = 255;
	data.ctrl->info_frames.meta_data[3] = 255;
	data.ctrl->info_frames.meta_data[4] = 255;
	data.ctrl->info_frames.meta_data[5] = 255;
	data.ctrl->info_frames.meta_data[6] = 255;
	data.ctrl->info_frames.meta_data[7] = 255;
}
VOID ct_im_hdmi1_printf9()
{
	// set paramter.
	data.ctrl->video_input_mapping = E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT;
	data.ctrl->vsync_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->hsync_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->de_in_polarity = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->DVI_modez = D_IM_HDMI_DVI_MODEZ_HDMI;
	data.ctrl->r_v_blank_in_osc = D_IM_HDMI_ACTIVE_LOW;
	data.ctrl->in_i_p = D_IM_HDMI_IN_I_P_PROGRESSIVE;
	data.ctrl->h_in_activ = 0;
	data.ctrl->v_in_activ = 0;
	data.ctrl->fc_invact_2d = 0;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_en = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->fc_actspc_hdlr_cfg.bit.actspc_hdlr_tgl = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->fc_inhblank = 0;
	data.ctrl->fc_invblank = 0;
	data.ctrl->fc_hsyncindelay = 0;
	data.ctrl->fc_hsyncinwidth = 0;
	data.ctrl->fc_vsyncindelay = 0;
	data.ctrl->fc_vsyncinwidth = 0;
	// PLL
	data.ctrl->pll_config.vp_pr_cd.bit.desired_pr_factor = 0;
	data.ctrl->pll_config.vp_pr_cd.bit.color_depth = E_IM_HDMI_COLOR_DEPTH_8BIT;
	//				data.ctrl->pll_config.phy_i2cm_address								= 0x00;
	//				data.ctrl->pll_config.phy_i2cm_datao[0]								= 0x00;
	//				data.ctrl->pll_config.phy_i2cm_datao[1]								= 0x00;
	// Audio
	data.ctrl->audio_config.i2s_select = E_IM_HDMI_I2S_SELECT_I2S;
	data.ctrl->audio_config.aud_conf1.bit.I2S_width = 16;
	data.ctrl->audio_config.aud_conf1.bit.I2S_mode = E_IM_HDMI_I2S_MODE_STANDARD;
	data.ctrl->audio_config.aud_conf2.bit.HBR = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_conf2.bit.NLPCM = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_width = 16;
	data.ctrl->audio_config.aud_spdif1.bit.spdif_hbr_mode = 0;
	data.ctrl->audio_config.aud_spdif1.bit.setnlpcm = 0;
	data.ctrl->audio_config.aud_inputclkfs = E_IM_HDMI_AUD_IFSFACTOR_128XFS;
	data.ctrl->audio_config.aud_n1 = 0;
	data.ctrl->audio_config.aud_n2 = 0;
	data.ctrl->audio_config.aud_n3_audn = 0;
	data.ctrl->audio_config.cts_manual = E_IM_HDMI_CTS_MANUAL_AUTO;
	data.ctrl->audio_config.aud_cts1 = 0;
	data.ctrl->audio_config.aud_cts2 = 0;
	data.ctrl->audio_config.aud_cts3_audcts = 0;
	// Infoframes
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.bar_information = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.scan_information = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.active_format_present = 0;
	data.ctrl->info_frames.fc_aviconf0.bit.rgc_ycc_indication_2 = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.active_aspect_ratio = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.picture_aspect_ratio = 0;
	data.ctrl->info_frames.fc_aviconf1.bit.Colorimetry = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.non_uniform_picture_scaling = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.quantization_range = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.extended_colorimetry = 0;
	data.ctrl->info_frames.fc_aviconf2.bit.it_content = 0;
	data.ctrl->info_frames.fc_aviconf3.bit.CN = 0;
	data.ctrl->info_frames.fc_aviconf3.bit.YQ = 0;
	data.ctrl->info_frames.fc_avivid = 0;
	data.ctrl->info_frames.fc_prconf.bit.output_pr_factor = 0;
	data.ctrl->info_frames.fc_prconf.bit.incoming_pr_factor = 0;
	data.ctrl->info_frames.fc_audiconf0.bit.CT = 0;
	data.ctrl->info_frames.fc_audiconf0.bit.CC = 0;
	data.ctrl->info_frames.fc_audiconf1.bit.SF = 0;
	data.ctrl->info_frames.fc_audiconf1.bit.SS = 0;
	data.ctrl->info_frames.fc_audiconf2 = 0;
	data.ctrl->info_frames.fc_audiconf3.bit.LSV = 0;
	data.ctrl->info_frames.fc_audiconf3.bit.DM_INH = D_IM_HDMI_ENABLE_OFF;
	data.ctrl->info_frames.fc_audiconf3.bit.LFEPBL = 0;
	data.ctrl->info_frames.fc_vsdieeeid[0] = 0;
	data.ctrl->info_frames.fc_vsdieeeid[1] = 0;
	data.ctrl->info_frames.fc_vsdieeeid[2] = 0;

	// paramter ng
	data.ctrl->info_frames.video_mode = 0;

	data.ctrl->info_frames.video_format = 0;
	data.ctrl->info_frames.meta_present = 0;
	data.ctrl->info_frames.additional_video_format = 0;
	data.ctrl->info_frames.meta_type = 0;
	data.ctrl->info_frames.meta_length = 0;
	data.ctrl->info_frames.meta_data[0] = 0;
	data.ctrl->info_frames.meta_data[1] = 0;
	data.ctrl->info_frames.meta_data[2] = 0;
	data.ctrl->info_frames.meta_data[3] = 0;
	data.ctrl->info_frames.meta_data[4] = 0;
	data.ctrl->info_frames.meta_data[5] = 0;
	data.ctrl->info_frames.meta_data[6] = 0;
	data.ctrl->info_frames.meta_data[7] = 0;
}

VOID ct_im_hdmi1_printf10()
{
	// set parameter.
	data.frameComposer->fc_invidconf.bit.in_I_P = D_IM_HDMI_IN_I_P_PROGRESSIVE;	   // Input video mode
	data.frameComposer->fc_invidconf.bit.r_v_blank_in_osc = D_IM_HDMI_ACTIVE_LOW;  // Used for CEA861-D modes with fractional Vblank
	data.frameComposer->fc_invidconf.bit.DVI_modez = D_IM_HDMI_DVI_MODEZ_DVI;	   // DVI mode selected
	data.frameComposer->fc_invidconf.bit.de_in_polarity = D_IM_HDMI_ACTIVE_LOW;	   // Data enable input polarity
	data.frameComposer->fc_invidconf.bit.hsync_in_polarity = D_IM_HDMI_ACTIVE_LOW; // Hsync input polarity
	data.frameComposer->fc_invidconf.bit.vsync_in_polarity = D_IM_HDMI_ACTIVE_LOW; // Vsync input polarity
	data.frameComposer->fc_invidconf.bit.HDCP_keepout = D_IM_HDMI_ACTIVE_LOW;	   // Start/stop HDCP keepout window generation
	data.frameComposer->fc_inhactiv = 16838;									   // fc_inhactiv: Frame Composer Input Video HActive Pixels
	data.frameComposer->fc_inhblank = 8191;										   // fc_inhblank: Frame Composer Input Video HBlank Pixels
	data.frameComposer->fc_invactiv = 8191;										   // fc_invactiv: Frame Composer Input Video VActive Pixels
	data.frameComposer->fc_invblank = 255;										   // fc_invblank: Frame Composer Input Video VBlank Pixels
	data.frameComposer->fc_hsyncindelay = 8191;									   // fc_hsyncindelay: Frame Composer Input Video HSync Front
	data.frameComposer->fc_hsyncinwidth = 1023;									   // fc_hsyncinwidth: Frame Composer Input Video HSync Width
	data.frameComposer->fc_vsyncindelay = 255;									   // fc_vsyncindelay: Frame Composer Input Video VSync Front Porch
	data.frameComposer->fc_vsyncinwidth = 63;									   // Frame Composer Input Video VSync Width
	data.frameComposer->fc_aviconf3.bit.CN = 3;									   // IT content type according to CEA the specification
	data.frameComposer->fc_aviconf3.bit.YQ = 3;									   // YCC Quantization range according to the CEA specification
	data.frameComposer->fc_aviconf0.bit.rgc_ycc_indication = 0;					   // Y1,Y0 RGB or YCC indicator : 0:RGB
	data.frameComposer->fc_aviconf0.bit.bar_information = 0;					   // Bar information data valid
	data.frameComposer->fc_aviconf0.bit.scan_information = 0;					   // Scan information
	data.frameComposer->fc_aviconf0.bit.active_format_present = 0;				   // Active format present
	data.frameComposer->fc_aviconf0.bit.rgc_ycc_indication_2 = 0;				   // Y2, Bit 2 of rgc_ycc_indication
	data.frameComposer->fc_aviconf1.bit.active_aspect_ratio = 0;				   // Active aspect ratio
	data.frameComposer->fc_aviconf1.bit.picture_aspect_ratio = 0;				   // Picture aspect ratio
	data.frameComposer->fc_aviconf1.bit.Colorimetry = 0;						   // Colorimetry
	data.frameComposer->fc_aviconf2.bit.non_uniform_picture_scaling = 0;		   // Non-uniform picture scaling
	data.frameComposer->fc_aviconf2.bit.quantization_range = 0;					   // Quantization range
	data.frameComposer->fc_aviconf2.bit.extended_colorimetry = 0;				   // Extended colorimetry
	data.frameComposer->fc_aviconf2.bit.it_content = 0;							   // IT content
	data.frameComposer->fc_avivid = 0;											   // Frame Composer AVI Packet VIC
	data.frameComposer->fc_prconf.bit.output_pr_factor = 0;						   // Input video pixel will be sent a specified number of times
	data.frameComposer->fc_prconf.bit.incoming_pr_factor = 0;					   // Output video pixel will be sent a specified number of times
}

VOID ct_im_hdmi1_printf11()
{
	// set parameter.
	data.frameComposer->fc_invidconf.bit.in_I_P = D_IM_HDMI_IN_I_P_INTERLACED;		// Input video mode
	data.frameComposer->fc_invidconf.bit.r_v_blank_in_osc = D_IM_HDMI_ACTIVE_HIGH;	// Used for CEA861-D modes with fractional Vblank
	data.frameComposer->fc_invidconf.bit.DVI_modez = D_IM_HDMI_DVI_MODEZ_HDMI;		// DVI mode selected
	data.frameComposer->fc_invidconf.bit.de_in_polarity = D_IM_HDMI_ACTIVE_HIGH;	// Data enable input polarity
	data.frameComposer->fc_invidconf.bit.hsync_in_polarity = D_IM_HDMI_ACTIVE_HIGH; // Hsync input polarity
	data.frameComposer->fc_invidconf.bit.vsync_in_polarity = D_IM_HDMI_ACTIVE_HIGH; // Vsync input polarity
	data.frameComposer->fc_invidconf.bit.HDCP_keepout = D_IM_HDMI_ACTIVE_HIGH;		// Start/stop HDCP keepout window generation
	data.frameComposer->fc_inhactiv = 16838;										// fc_inhactiv: Frame Composer Input Video HActive Pixels
	data.frameComposer->fc_inhblank = 8191;											// fc_inhblank: Frame Composer Input Video HBlank Pixels
	data.frameComposer->fc_invactiv = 8191;											// fc_invactiv: Frame Composer Input Video VActive Pixels
	data.frameComposer->fc_invblank = 255;											// fc_invblank: Frame Composer Input Video VBlank Pixels
	data.frameComposer->fc_hsyncindelay = 8191;										// fc_hsyncindelay: Frame Composer Input Video HSync Front
	data.frameComposer->fc_hsyncinwidth = 1023;										// fc_hsyncinwidth: Frame Composer Input Video HSync Width
	data.frameComposer->fc_vsyncindelay = 255;										// fc_vsyncindelay: Frame Composer Input Video VSync Front Porch
	data.frameComposer->fc_vsyncinwidth = 63;										// Frame Composer Input Video VSync Width
	data.frameComposer->fc_aviconf3.bit.CN = 3;										// IT content type according to CEA the specification
	data.frameComposer->fc_aviconf3.bit.YQ = 3;										// YCC Quantization range according to the CEA specification
	data.frameComposer->fc_aviconf0.bit.rgc_ycc_indication = 3;						// Y1,Y0 RGB or YCC indicator : 3:YCC420
	data.frameComposer->fc_aviconf0.bit.bar_information = 3;						// Bar information data valid
	data.frameComposer->fc_aviconf0.bit.scan_information = 3;						// Scan information
	data.frameComposer->fc_aviconf0.bit.active_format_present = 1;					// Active format present
	data.frameComposer->fc_aviconf0.bit.rgc_ycc_indication_2 = 1;					// Y2, Bit 2 of rgc_ycc_indication
	data.frameComposer->fc_aviconf1.bit.active_aspect_ratio = 15;					// Active aspect ratio
	data.frameComposer->fc_aviconf1.bit.picture_aspect_ratio = 3;					// Picture aspect ratio
	data.frameComposer->fc_aviconf1.bit.Colorimetry = 3;							// Colorimetry
	data.frameComposer->fc_aviconf2.bit.non_uniform_picture_scaling = 3;			// Non-uniform picture scaling
	data.frameComposer->fc_aviconf2.bit.quantization_range = 3;						// Quantization range
	data.frameComposer->fc_aviconf2.bit.extended_colorimetry = 7;					// Extended colorimetry
	data.frameComposer->fc_aviconf2.bit.it_content = 1;								// IT content
	data.frameComposer->fc_avivid = 255;											// Frame Composer AVI Packet VIC
	data.frameComposer->fc_prconf.bit.output_pr_factor = 10;						// Input video pixel will be sent a specified number of times
	data.frameComposer->fc_prconf.bit.incoming_pr_factor = 10;						// Output video pixel will be sent a specified number of times
}

VOID ct_im_hdmi1_printf12()
{
	// check register
	Ddim_Print(("----------\n"));
	Ddim_Print(("fc_invidconf    = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0    = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1    = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_inhblank0    = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1    = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invactiv0    = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1    = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_invblank     = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_hsyncinwidth0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_vsyncindelay = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_vsyncinwidth = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("fc_aviconf3     = %p\n", IO_DISP.HDMI_TX.fc_aviconf3.byte));
	Ddim_Print(("fc_aviconf0     = %p\n", IO_DISP.HDMI_TX.fc_aviconf0.byte));
	Ddim_Print(("fc_aviconf1     = %p\n", IO_DISP.HDMI_TX.fc_aviconf1.byte));
	Ddim_Print(("fc_aviconf2     = %p\n", IO_DISP.HDMI_TX.fc_aviconf2.byte));
	Ddim_Print(("fc_avivid       = %p\n", IO_DISP.HDMI_TX.fc_avivid.byte));
	Ddim_Print(("fc_prconf       = %p\n", IO_DISP.HDMI_TX.fc_prconf.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi1_printf13()
{
	// check get data
	Ddim_Print(("----------\n"));
	Ddim_Print(("result:\n"));
	Ddim_Print(("fc_invidconf    : 0x%x\n", data.frameComposer->fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv     : 0x%x\n", data.frameComposer->fc_inhactiv));
	Ddim_Print(("fc_inhblank     : 0x%x\n", data.frameComposer->fc_inhblank));
	Ddim_Print(("fc_invactiv     : 0x%x\n", data.frameComposer->fc_invactiv));
	Ddim_Print(("fc_invblank     : 0x%x\n", data.frameComposer->fc_invblank));
	Ddim_Print(("fc_hsyncindelay : 0x%x\n", data.frameComposer->fc_hsyncindelay));
	Ddim_Print(("fc_hsyncinwidth : 0x%x\n", data.frameComposer->fc_hsyncinwidth));
	Ddim_Print(("fc_vsyncindelay : 0x%x\n", data.frameComposer->fc_vsyncindelay));
	Ddim_Print(("fc_vsyncinwidth : 0x%x\n", data.frameComposer->fc_vsyncinwidth));
	Ddim_Print(("fc_aviconf3     : 0x%x\n", data.frameComposer->fc_aviconf3.byte));
	Ddim_Print(("fc_aviconf0     : 0x%x\n", data.frameComposer->fc_aviconf0.byte));
	Ddim_Print(("fc_aviconf1     : 0x%x\n", data.frameComposer->fc_aviconf1.byte));
	Ddim_Print(("fc_aviconf2     : 0x%x\n", data.frameComposer->fc_aviconf2.byte));
	Ddim_Print(("fc_avivid       : 0x%x\n", data.frameComposer->fc_avivid));
	Ddim_Print(("fc_prconf       : 0x%x\n", data.frameComposer->fc_prconf.byte));
	Ddim_Print(("register:\n"));
	Ddim_Print(("fc_invidconf    = %p\n", IO_DISP.HDMI_TX.fc_invidconf.byte));
	Ddim_Print(("fc_inhactiv0    = %p\n", IO_DISP.HDMI_TX.fc_inhactiv0.byte));
	Ddim_Print(("fc_inhactiv1    = %p\n", IO_DISP.HDMI_TX.fc_inhactiv1.byte));
	Ddim_Print(("fc_inhblank0    = %p\n", IO_DISP.HDMI_TX.fc_inhblank0.byte));
	Ddim_Print(("fc_inhblank1    = %p\n", IO_DISP.HDMI_TX.fc_inhblank1.byte));
	Ddim_Print(("fc_invactiv0    = %p\n", IO_DISP.HDMI_TX.fc_invactiv0.byte));
	Ddim_Print(("fc_invactiv1    = %p\n", IO_DISP.HDMI_TX.fc_invactiv1.byte));
	Ddim_Print(("fc_invblank     = 0x%x\n", IO_DISP.HDMI_TX.fc_invblank));
	Ddim_Print(("fc_hsyncindelay0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay0.byte));
	Ddim_Print(("fc_hsyncindelay1 = %p\n", IO_DISP.HDMI_TX.fc_hsyncindelay1.byte));
	Ddim_Print(("fc_hsyncinwidth0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_hsyncinwidth0 = %p\n", IO_DISP.HDMI_TX.fc_hsyncinwidth0.byte));
	Ddim_Print(("fc_vsyncindelay = 0x%x\n", IO_DISP.HDMI_TX.fc_vsyncindelay));
	Ddim_Print(("fc_vsyncinwidth = %p\n", IO_DISP.HDMI_TX.fc_vsyncinwidth.byte));
	Ddim_Print(("fc_aviconf3     = %p\n", IO_DISP.HDMI_TX.fc_aviconf3.byte));
	Ddim_Print(("fc_aviconf0     = %p\n", IO_DISP.HDMI_TX.fc_aviconf0.byte));
	Ddim_Print(("fc_aviconf1     = %p\n", IO_DISP.HDMI_TX.fc_aviconf1.byte));
	Ddim_Print(("fc_aviconf2     = %p\n", IO_DISP.HDMI_TX.fc_aviconf2.byte));
	Ddim_Print(("fc_avivid       = %p\n", IO_DISP.HDMI_TX.fc_avivid.byte));
	Ddim_Print(("fc_prconf       = %p\n", IO_DISP.HDMI_TX.fc_prconf.byte));
	Ddim_Print(("----------\n"));
}

VOID ct_im_hdmi1_printf14()
{
	// check get data
	Ddim_Print(("----------\n"));
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

/**
 * @brief       HDMI PCSim Test..
 * @param       VOID
 * @return      VOID
 */
VOID ct_im_hdmi1_pcsim_test(VOID)
{
#ifdef CO_DEBUG_ON_PC
	int cmd_cnt = 0;

	// HDMI Test command data
	//	char hdmi_test_argv1[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = { "imhdmi", "init", "0", "0" };
	char hdmi_test_argv2[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "init", "1"};
	//	char hdmi_test_argv3[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = { "imhdmi", "init", "2" };
	//	char hdmi_test_argv4[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = { "imhdmi", "sinks", "0", "0" };
	char hdmi_test_argv5[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "sinks", "1"};
	char hdmi_test_argv6[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "sinks", "0", "1"};
	char hdmi_test_argv7[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "set", "0", "0"};
	char hdmi_test_argv8[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "set", "1"};
	char hdmi_test_argv9[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "set", "2", "0"};
	char hdmi_test_argv10[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "set", "0", "2"};
	char hdmi_test_argv11[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "get", "0"};
	char hdmi_test_argv12[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "ctrl", "get", "1"};
	char hdmi_test_argv13[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "clk", "set", "0"};
	char hdmi_test_argv14[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "clk", "get", "0"};
	char hdmi_test_argv15[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "clk", "get", "1"};
	char hdmi_test_argv16[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "term", "set", "0"};
	char hdmi_test_argv17[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "term", "get", "0"};
	char hdmi_test_argv18[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "term", "get", "1"};
	char hdmi_test_argv19[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "tc", "set", "0"};
	char hdmi_test_argv20[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "tc", "get", "0"};
	char hdmi_test_argv21[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "tc", "get", "1"};
	char hdmi_test_argv22[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vol", "set", "0"};
	char hdmi_test_argv23[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vol", "get", "0"};
	char hdmi_test_argv24[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vol", "get", "1"};
	char hdmi_test_argv25[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "csc", "set", "0", "0"};
	char hdmi_test_argv26[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "csc", "set", "1"};
	char hdmi_test_argv27[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vs", "set", "0"};
	char hdmi_test_argv28[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vs", "get", "0"};
	char hdmi_test_argv29[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vs", "get", "1"};
	char hdmi_test_argv30[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vp", "set", "0", "0"};
	char hdmi_test_argv31[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vp", "set", "1"};
	char hdmi_test_argv32[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vp", "get", "0"};
	char hdmi_test_argv33[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "vp", "get", "1"};
	char hdmi_test_argv34[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "fc", "set", "0", "0"};
	char hdmi_test_argv35[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "fc", "set", "1"};
	char hdmi_test_argv36[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "fc", "get", "0"};
	char hdmi_test_argv37[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "fc", "get", "1"};
	char hdmi_test_argv38[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mc", "set", "0", "0"};
	char hdmi_test_argv39[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mc", "set", "4"};
	char hdmi_test_argv40[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mc", "get", "0"};
	char hdmi_test_argv41[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mc", "get", "1"};
	char hdmi_test_argv42[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "audio", "set", "0", "0"};
	char hdmi_test_argv43[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "audio", "set", "1"};
	char hdmi_test_argv44[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "audio", "get", "0"};
	char hdmi_test_argv45[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "audio", "get", "1"};
	char hdmi_test_argv46[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "cb", "set", "0", "0"};
	char hdmi_test_argv47[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "cb", "set", "47", "1"};
	char hdmi_test_argv48[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mute", "set", "0"};
	char hdmi_test_argv49[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mute", "get", "0"};
	char hdmi_test_argv50[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "mute", "get", "1"};
	char hdmi_test_argv51[][CtImHdmi_D_HDMI_TEST_CMD_LEN] = {"imhdmi", "int", "0"};

	//
	memset((VOID *)&(IO_DISP.HDMI_TX), 0, sizeof(IO_DISP.HDMI_TX));

	Ddim_Print(("\n======== HDMI ========\n"));
	Ddim_Print((">> Test 1-1-1\n"));
	//	cmd_cnt = (sizeof(hdmi_test_argv1) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	//	ctImHdmiSetCmd(cmd_cnt, (char*)hdmi_test_argv1);
	//	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-2\n"));
	cmd_cnt = (sizeof(hdmi_test_argv2) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv2);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-3\n"));
	//	cmd_cnt = (sizeof(hdmi_test_argv3) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	//	ctImHdmiSetCmd(cmd_cnt, (char*)hdmi_test_argv3);
	//	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-4\n"));
	//	cmd_cnt = (sizeof(hdmi_test_argv4) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	//	ctImHdmiSetCmd(cmd_cnt, (char*)hdmi_test_argv4);
	//	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-5\n"));
	cmd_cnt = (sizeof(hdmi_test_argv5) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv5);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-6\n"));
	cmd_cnt = (sizeof(hdmi_test_argv6) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv6);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-7\n"));
	cmd_cnt = (sizeof(hdmi_test_argv7) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv7);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-8\n"));
	cmd_cnt = (sizeof(hdmi_test_argv8) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv8);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-9\n"));
	cmd_cnt = (sizeof(hdmi_test_argv9) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv9);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-10\n"));
	cmd_cnt = (sizeof(hdmi_test_argv10) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv10);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-11\n"));
	cmd_cnt = (sizeof(hdmi_test_argv11) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv11);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-12\n"));
	cmd_cnt = (sizeof(hdmi_test_argv12) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv12);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-13\n"));
	cmd_cnt = (sizeof(hdmi_test_argv13) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv13);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-14\n"));
	cmd_cnt = (sizeof(hdmi_test_argv14) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv14);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-15\n"));
	cmd_cnt = (sizeof(hdmi_test_argv15) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv15);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-16\n"));
	cmd_cnt = (sizeof(hdmi_test_argv16) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv16);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-17\n"));
	cmd_cnt = (sizeof(hdmi_test_argv17) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv17);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-18\n"));
	cmd_cnt = (sizeof(hdmi_test_argv18) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv18);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-19\n"));
	cmd_cnt = (sizeof(hdmi_test_argv19) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv19);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-20\n"));
	cmd_cnt = (sizeof(hdmi_test_argv20) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv20);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-21\n"));
	cmd_cnt = (sizeof(hdmi_test_argv21) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv21);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-22\n"));
	cmd_cnt = (sizeof(hdmi_test_argv22) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv22);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-23\n"));
	cmd_cnt = (sizeof(hdmi_test_argv23) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv23);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-24\n"));
	cmd_cnt = (sizeof(hdmi_test_argv24) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv24);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-25\n"));
	cmd_cnt = (sizeof(hdmi_test_argv25) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv25);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-26\n"));
	cmd_cnt = (sizeof(hdmi_test_argv26) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv26);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-27\n"));
	cmd_cnt = (sizeof(hdmi_test_argv27) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv27);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-28\n"));
	cmd_cnt = (sizeof(hdmi_test_argv28) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv28);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-29\n"));
	cmd_cnt = (sizeof(hdmi_test_argv29) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv29);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-30\n"));
	cmd_cnt = (sizeof(hdmi_test_argv30) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv30);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-31\n"));
	cmd_cnt = (sizeof(hdmi_test_argv31) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv31);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-32\n"));
	cmd_cnt = (sizeof(hdmi_test_argv32) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv32);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-33\n"));
	cmd_cnt = (sizeof(hdmi_test_argv33) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv33);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-34\n"));
	cmd_cnt = (sizeof(hdmi_test_argv34) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv34);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-35\n"));
	cmd_cnt = (sizeof(hdmi_test_argv35) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv35);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-36\n"));
	cmd_cnt = (sizeof(hdmi_test_argv36) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv36);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-37\n"));
	cmd_cnt = (sizeof(hdmi_test_argv37) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv37);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-38\n"));
	cmd_cnt = (sizeof(hdmi_test_argv38) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv38);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-39\n"));
	cmd_cnt = (sizeof(hdmi_test_argv39) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv39);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-40\n"));
	cmd_cnt = (sizeof(hdmi_test_argv40) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv40);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-41\n"));
	cmd_cnt = (sizeof(hdmi_test_argv41) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv41);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-42\n"));
	cmd_cnt = (sizeof(hdmi_test_argv42) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv42);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-43\n"));
	cmd_cnt = (sizeof(hdmi_test_argv43) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv43);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-44\n"));
	cmd_cnt = (sizeof(hdmi_test_argv44) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv44);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-45\n"));
	cmd_cnt = (sizeof(hdmi_test_argv45) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv45);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-46\n"));
	cmd_cnt = (sizeof(hdmi_test_argv46) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv46);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-47\n"));
	cmd_cnt = (sizeof(hdmi_test_argv47) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv47);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-48\n"));
	cmd_cnt = (sizeof(hdmi_test_argv48) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv48);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-49\n"));
	cmd_cnt = (sizeof(hdmi_test_argv49) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv49);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-50\n"));
	cmd_cnt = (sizeof(hdmi_test_argv50) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv50);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);

	Ddim_Print(("\n>> Test 1-1-51\n"));
	cmd_cnt = (sizeof(hdmi_test_argv51) / CtImHdmi_D_HDMI_TEST_CMD_LEN);
	ctImHdmiSetCmd(cmd_cnt, (char *)hdmi_test_argv51);
	ct_im_hdmi_main(cmd_cnt, gCmdArgv);
#endif // CO_DEBUG_ON_PC
}

CtImHdmi1* ct_im_hdmi1_new(void)
{
	CtImHdmi1* self = k_object_new_with_private(CT_TYPE_IM_HDMI1, sizeof(CtImHdmi1Private));

	return self;
}

CtImHdmi1* ct_im_hdmi1_get(void)
{
	static CtImHdmi1* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_HDMI1, sizeof(CtImHdmi1Private));
	}

	return self;
}
