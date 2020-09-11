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


#include "jdsdisp3a.h"
#include "imhdmi.h"
#include "ddarm.h"
#include "imdisp.h"
#include "imhdmienum.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImHdmiEnum, im_hdmi_enum);
#define IM_HDMI_ENUM_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImHdmiEnumPrivate, IM_TYPE_HDMI_ENUM	))


struct _ImHdmiEnumPrivate
{
	kint a;
};
/**
 * IMPL
 */
static void im_hdmi_enum_constructor(ImHdmiEnum *self)
{
//	ImHdmiEnumPrivate *priv = IM_HDMI_ENUM_GET_PRIVATE(self);
}

static void im_hdmi_enum_destructor(ImHdmiEnum *self)
{
//	ImHdmiEnumPrivate *priv = IM_HDMI_ENUM_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/**
 * @brief	Get interrupt type.
 * @param[in]	int_reg		Interrupt register.
 * @param[in]	reg_bit		Bit of the specified interrupt register.
 * @retval		EhdmiIntType		Interrupt type.
 */
EhdmiIntType im_hdmi_get_interrupt_type(EhdmiIntReg int_reg, kuchar reg_bit)
{
	EhdmiIntType interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// Interrupt register.
	switch (int_reg) {
		// ihFcStat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0:
			// register bit.
			switch (reg_bit) {
				// NULL.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NULL:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_NULL;
					break;
				// ACR.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ACR;
					break;
				// AUDS.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDS:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AUDS;
					break;
				// NVBI.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NVBI:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_NVBI;
					break;
				// MAS.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_MAS:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_MAS;
					break;
				// hbr.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_HBR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_HBR;
					break;
				// ACP.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ACP;
					break;
				// AUDI.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDI:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AUDI;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ihFcStat1.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1:
			// register bit.
			switch (reg_bit) {
				// GCP.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GCP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_GCP;
					break;
				// AVI.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AVI:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AVI;
					break;
				// AMP.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AMP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AMP;
					break;
				// SPD.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_SPD:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_SPD;
					break;
				// VSD.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_VSD:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_VSD;
					break;
				// ISCR2.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR2:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ISCR2;
					break;
				// ISCR1.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR1:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ISCR1;
					break;
				// GMD.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GMD:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_GMD;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ihFcStat2.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2:
			// register bit.
			switch (reg_bit) {
				// HighPriority_overflow.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_HP_OF:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_HP_OF;
					break;
				// LowPriority_overflow.
				case ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_LP_OF:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_LP_OF;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_as_stat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0:
			// register bit.
			switch (reg_bit) {
				// Aud_fifo_overflow.
				case ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OF:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_OF;
					break;
				// Aud_fifo_underflow.
				case ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_UF:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_UF;
					break;
				// fifo_overrun.
				case ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_OR;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_phy_stat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0:
			// register bit.
			switch (reg_bit) {
				// HDP.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_HDP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_HDP;
					break;
				// txPhyLock.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_TX_PHY_LOCK:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_TX_PHY_LOCK;
					break;
				// pxSense0.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_0:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_0;
					break;
				// rxSense1.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_1:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_1;
					break;
				// rxSense2.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_2:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_2;
					break;
				// rxSense3.
				case ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_3:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_3;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_i2cm_stat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0:
			// register bit.
			switch (reg_bit) {
				// I2Cmastererror.
				case ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_ERR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_M_ERR;
					break;
				// I2Cmasterdone.
				case ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_DONE:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_M_DONE;
					break;
				// scdc_readreq.
				case ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_SDSC:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_SDSC;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_cec_stat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0:
			// register bit.
			switch (reg_bit) {
				// DONE.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_DONE:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_DONE;
					break;
				// EOM.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_EOM:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_EOM;
					break;
				// NACK.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_NACK:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_NACK;
					break;
				// ARB_LOST.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ARB_LOST:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ARB_LOST;
					break;
				// ERROR_INITIATOR.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_INITIATOR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ERR_INIT;
					break;
				// ERROR_FOLLOW.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_FOLLOW:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ERR_FOL;
					break;
				// WAKEUP.
				case ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_WAKEUP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_WAKEUP;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_vp_stat0.
		case ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0:
			// register bit.
			switch (reg_bit) {
				// fifoemptybyp.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_BYP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_BYP;
					break;
				// fifofullbyp.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_BYP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_BYP;
					break;
				// fifoemptyremap.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REMAP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_REMAP;
					break;
				// fifofullremap.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REMAP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_REMAP;
					break;
				// fifoemptypp.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_PP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_PP;
					break;
				// fifofullpp.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_PP:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_PP;
					break;
				// fifoemptyrepet.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REPET:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_REPET;
					break;
				// fifofullrepet.
				case ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REPET:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_REPET;
					break;
				default:
					// no process.
					break;
			}
			break;

			// ih_i2cmphy_stat0.
		default:
			// register bit.
			switch (reg_bit) {
				// I2Cmphyerror.
				case ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_ERR:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CMPHY_ERR;
					break;
				// I2Cmphydone.
				case ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_DONE:
					interrupt_type = ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CMPHY_DONE;
					break;
				default:
					// no process.
					break;
			}
			break;
	}

	return interrupt_type;
}

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief	HDMI PHY Power On/Off.
 */
kint32 im_hdmi_power_on(ImHdmiEnum*self, kuchar power)
{
#ifdef CO_PARAM_CHECK
	if ((power != ImHdmi_D_IM_HDMI_ENABLE_OFF) && (power != ImHdmi_D_IM_HDMI_ENABLE_ON)) {
		Ddim_Assertion(("im_hdmi_power_on Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif

	// PHY TXPWRON.
	ioDisp.hdmiTx.phyConf0.bit.txpwron = power;

	return D_DDIM_OK;
}

/**
 * @brief	Initialize HDMI Transmitter macro.
 */
kint32 im_hdmi_init(ImHdmiEnum*self,)
{
	im_hdmi_pclk_on();

	// status clear
	ioDisp.hdmiTx.ihFcStat0.byte[0] = 0xff;
	ioDisp.hdmiTx.ihFcStat1.byte[0] = 0xff;
	ioDisp.hdmiTx.ihFcStat2.byte[0] = 0x03;
	ioDisp.hdmiTx.ihAsStat0.byte[0] = 0x0b;
	ioDisp.hdmiTx.ihPhyStat0.byte[0] = 0x3f;
	ioDisp.hdmiTx.ihI2cmStat0.byte[0] = 0x07;
	ioDisp.hdmiTx.ihCecStat0.byte[0] = 0x7f;
	ioDisp.hdmiTx.ihVpStat0.byte[0] = 0xff;
	ioDisp.hdmiTx.ihI2cmphyStat0.byte[0] = 0x03;

	// mute off
	ioDisp.hdmiTx.ihMute.byte[0] = 0x00;

	// mute on
	ioDisp.hdmiTx.ihMuteFcStat0.byte[0] = 0xff;
	ioDisp.hdmiTx.ihMuteFcStat1.byte[0] = 0xff;
	ioDisp.hdmiTx.ihMuteFcStat2.byte[0] = 0x03;
	ioDisp.hdmiTx.ihMuteAsStat0.byte[0] = 0x0b;
	//	ioDisp.hdmiTx.ih_mute_phy_stat0.byte[0]	= 0x3f;
	ioDisp.hdmiTx.ihMuteCecStat0.byte[0] = 0x7f;
	ioDisp.hdmiTx.ihMuteVpStat0.byte[0] = 0xff;
	// mask on
	ioDisp.hdmiTx.fcMask0.byte[0] = 0xff;
	ioDisp.hdmiTx.fcMask1.byte[0] = 0xff;
	ioDisp.hdmiTx.audInt.byte[0] = 0xff;
	//	ioDisp.hdmiTx.phy_mask0.byte[0]			= 0xff;
	ioDisp.hdmiTx.cecMask.byte[0] = 0xff;
	ioDisp.hdmiTx.vpMask.byte[0] = 0xff;

	// Power-on the HDMI TX PHY hpd Detector.
	ioDisp.hdmiTx.phyConf0.bit.enhpdrxsense = 1;

	im_hdmi_pclk_off();

	return D_DDIM_OK;
}

/**
 * @brief	Configure VGA DVI Video Mode.
 */
kint32 im_hdmi_configure_vga_dvi_video_mode(ImHdmiEnum*self, ThdmiPllConfig const *const pllConfig)
{
#ifdef CO_PARAM_CHECK
	if (pllConfig == NULL) {
		Ddim_Assertion(("im_hdmi_configure_vga_dvi_video_mode Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif

	im_hdmi_pclk_on();

	// Clock Domain Disable
	ioDisp.hdmiTx.mcClkdis.bit.pixelclkDisable = 1;
	ioDisp.hdmiTx.mcClkdis.bit.tmdsclkDisable = 1;

	// Set VGA (640x480p) in DVI mode.
	// Select the Video Mapping input RGB444, 8-bits per color components (24-bits RGB).
	ioDisp.hdmiTx.txInvid0.bit.videoMapping = ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT;
	// Configure VGA timing information (CEA mode 1)
	ioDisp.hdmiTx.fcInvidconf.bit.vsyncInPolarity = ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ioDisp.hdmiTx.fcInvidconf.bit.hsyncInPolarity = ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ioDisp.hdmiTx.fcInvidconf.bit.deInPolarity = ImHdmi_D_IM_HDMI_ACTIVE_HIGH;
	ioDisp.hdmiTx.fcInvidconf.bit.rVBlankInOsc = ImHdmi_D_IM_HDMI_ACTIVE_LOW;
	ioDisp.hdmiTx.fcInvidconf.bit.inIP = ImHdmi_D_IM_HDMI_IN_I_P_PROGRESSIVE;
	// 640 H active pixels: 0x280
	ioDisp.hdmiTx.fcInhactiv0.bit.hInActiv = 0x80;
	ioDisp.hdmiTx.fcInhactiv1.bit.hInActiv = 0x02;
	// 480 V active pixels: 0x1E0
	ioDisp.hdmiTx.fcInvactiv0.bit.vInActiv = 0xE0;
	ioDisp.hdmiTx.fcInvactiv1.bit.vInActiv = 0x01;
	// 160 H blanking pixels: 0xA0
	ioDisp.hdmiTx.fcInhblank0.bit.hInBlank = 0xA0;
	ioDisp.hdmiTx.fcInhblank1.bit.hInBlank = 0x00;
	// 45 V blanking pixels: 0x2D
	ioDisp.hdmiTx.fcInvblank = 0x2D;
	// 16 Sync offset: 0x10
	ioDisp.hdmiTx.fcHsyncindelay0.bit.hInDelay = 0x10;
	ioDisp.hdmiTx.fcHsyncindelay1.bit.hInDelay = 0x00;
	// 10 Vsync offset: 0x0A
	ioDisp.hdmiTx.fcVsyncindelay = 0x0A;
	// 96 HSync pulse width: 0x60
	ioDisp.hdmiTx.fcHsyncinwidth0.bit.hInWidth = 0x60;
	ioDisp.hdmiTx.fcHsyncinwidth1.bit.hInWidth = 0x00;
	// 2 VSync pulse width: 0x02
	ioDisp.hdmiTx.fcVsyncinwidth.bit.vInWidth = 0x02;
	// To select the DVI mode
	ioDisp.hdmiTx.fcInvidconf.bit.dviModez = ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI;

	// Configuring the PLL.
	if (im_hdmi_configure_pll(pllConfig) != D_DDIM_OK) {
		// the PLL does not lock and no activity.
		im_hdmi_pclk_off();
		return ImHdmi_D_IM_HDMI_NG;
	}

	// Enable the video path.
	// Set default parameters.
	// Control period duration.
	ioDisp.hdmiTx.fcCtrldur = 0x0C;
	// Extended Control period duration.
	ioDisp.hdmiTx.fcExctrldur = 0x20;
	// Max spacing between extended Control period duration.
	ioDisp.hdmiTx.fcExctrlspac = 0x01;
	// Preamble filters to fill TMDS data channels.
	ioDisp.hdmiTx.fcCh0pream = 0x0B;
	ioDisp.hdmiTx.fcCh1pream.byte[0] = 0x16;
	ioDisp.hdmiTx.fcCh2pream.byte[0] = 0x21;

	// Enable pixel clock data path.
	ioDisp.hdmiTx.mcClkdis.bit.pixelclkDisable = 0;
	// Enable TMDS clock data path.
	ioDisp.hdmiTx.mcClkdis.bit.tmdsclkDisable = 0;
	ioDisp.hdmiTx.fcVsyncinwidth.bit.vInWidth = 0x02;

	im_hdmi_pclk_off();

	return D_DDIM_OK;
}

/**
 * @brief	Set TMDS Scramble by I2C
 * @retval	D_DDIM_OK						Success.
 * @retval	ImHdmi_D_IM_HDMI_TIMEOUT				timeout.
 */
kint32 im_hdmi_set_tmds_scramble(ImHdmiEnum*self, BOOL enable)
{
	DDIM_USER_FLGPTN flg_ptn;

	im_hdmi_pclk_on();

	// clear Interrupt flag.
	DDIM_User_Clr_Flg(FID_IM_HDMI, ~(ImHdmi_D_IM_HDMI_INT_FLG_I2CM));

	// configure.
	// PHY I2C SW reset control register.
	ioDisp.hdmiTx.i2cmSoftrstz.byte[0] = 0x00;
	// I2C DDC Speed Control Register.
	ioDisp.hdmiTx.i2cmDiv.byte[0] = 0x03;
	// I2C slave. (SCDC)
	ioDisp.hdmiTx.i2cmSlave.byte[0] = 0x54;
	// I2C slave address. (TMDS_Config)
	ioDisp.hdmiTx.i2cmAddress = 0x20;
	if (enable) {
		// I2C datao. (Scrambling_Enable=1, TMDS_Bit_Clock_Ratio=1)
		ioDisp.hdmiTx.i2cmDatao = 0x03;
	}
	else {
		// I2C datao. (Scrambling_Enable=1, TMDS_Bit_Clock_Ratio=1)
		ioDisp.hdmiTx.i2cmDatao = 0x00;
	}
	// I2C operation.
	ioDisp.hdmiTx.i2cmOperation.byte[0] = 0x10;

	// Wait for interruption.
	if (DDIM_User_Twai_Flg(FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME) != D_DDIM_USER_E_OK) {
		im_hdmi_pclk_off();
		return ImHdmi_D_IM_HDMI_TIMEOUT;
	}

	im_hdmi_pclk_off();

	return D_DDIM_OK;
}

/**
 * @brief		Read Sink's E-EDID.
 */
kint32 im_hdmi_read_sinks_e_edid(ImHdmiEnum*self, ThdmiI2cmConfig const *const i2cmConfig, kuchar readData[8])
{
	DDIM_USER_FLGPTN flg_ptn;
	kint32 index;
#ifdef CO_PARAM_CHECK
	if (i2cmConfig == NULL) {
		Ddim_Assertion(("im_hdmi_read_sinks_e_edid Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif

	// clear Interrupt flag.
	DDIM_User_Clr_Flg(FID_IM_HDMI, ~(ImHdmi_D_IM_HDMI_INT_FLG_I2CM));

	im_hdmi_pclk_on();

	// configure.
	// I2C slave address.
	ioDisp.hdmiTx.i2cmSlave.byte[0] = i2cmConfig->i2cmSlaveaddr;
	ioDisp.hdmiTx.i2cmDiv.byte[0] = 0x03;
	if ((i2cmConfig->i2cmOperation == ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8) || (i2cmConfig->i2cmOperation == ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD)) {
		// i2C address.
		ioDisp.hdmiTx.i2cmAddress = i2cmConfig->i2cmAddress;
	}
	else {
		// I2C segment address.
		ioDisp.hdmiTx.i2cmSegaddr.byte[0] = i2cmConfig->i2cmSegaddr;
		// I2C segment pointer.
		ioDisp.hdmiTx.i2cmSegptr = i2cmConfig->i2cmSegptr;
		// i2C address.
		ioDisp.hdmiTx.i2cmAddress = i2cmConfig->i2cmAddress;
	}
	// I2C operation.
	ioDisp.hdmiTx.i2cmOperation.byte[0] = i2cmConfig->i2cmOperation;

	// Wait for interruption.
	if (DDIM_User_Twai_Flg(FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME) != D_DDIM_USER_E_OK) {
		Ddim_Print(("im_hdmi_read_sinks_e_edid Wait i2cmphy INT is timeout!!\n"));
		im_hdmi_pclk_off();
		return ImHdmi_D_IM_HDMI_TIMEOUT;
	}

	// Read data result.
	if ((i2cmConfig->i2cmOperation == ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8)
		|| (i2cmConfig->i2cmOperation == ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8_EXT)) {
		for (index = 0; index < 8; index++) {
			readData[index] = ioDisp.hdmiTx.i2cmReadBuff[index].byte[0];
		}
	}
	else {
		readData[0] = ioDisp.hdmiTx.i2cmDatai;
	}

	im_hdmi_pclk_off();

	return D_DDIM_OK;
}
kint32 im_hdmi_ctrl(ImHdmiEnum*self, ThdmiCtrl const *const ctrl )
{
	kint32 ret = D_DDIM_OK;
#ifdef CO_PARAM_CHECK
	if (ctrl == NULL) {
		Ddim_Assertion(("im_hdmi_ctrl Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif
	im_hdmi_pclk_on();

	// Power-down HDMI TX PHY Detector.
	// PHY SVSRET, PHY ENHPDRXSENSE signal.
	ioDisp.hdmiTx.phyConf0.byte[0] = 0x26;
	// PHY PDDQ, PHY ENHPDRXSENSE signal.
	ioDisp.hdmiTx.phyConf0.byte[0] = 0x16;

	// Set desired video mode.
	// select the Video Mapping input mode.
	ioDisp.hdmiTx.txInvid0.bit.videoMapping = ctrl->videoInputMapping;

	// Set video timing information configuration.
	// Set fcInvidconf.
	ioDisp.hdmiTx.fcInvidconf.bit.hdcpKeepout = ctrl->hdcpKeepout;
	ioDisp.hdmiTx.fcInvidconf.bit.vsyncInPolarity = ctrl->vsyncInPolarity;
	ioDisp.hdmiTx.fcInvidconf.bit.hsyncInPolarity = ctrl->hsyncInPolarity;
	ioDisp.hdmiTx.fcInvidconf.bit.deInPolarity = ctrl->deInPolarity;
	ioDisp.hdmiTx.fcInvidconf.bit.rVBlankInOsc = ctrl->rVBlankInOsc;
	ioDisp.hdmiTx.fcInvidconf.bit.inIP = ctrl->inIP;

	// Set fcInvactiv.
	ioDisp.hdmiTx.fcInhactiv0.byte[0] = (ctrl->hInActiv & 0x00FF);
	ioDisp.hdmiTx.fcInhactiv1.byte[0] = (ctrl->hInActiv >> 8);

	ioDisp.hdmiTx.fcInvactiv0.byte[0] = (ctrl->vInActiv & 0x00FF);
	ioDisp.hdmiTx.fcInvactiv1.byte[0] = (ctrl->vInActiv >> 8);
	// Set fc_invact_2d_0/1, fcActspcHdlrCfg.
	ioDisp.hdmiTx.fcInvact2d0.byte[0] = (ctrl->fcInvact2d & 0x00FF);
	ioDisp.hdmiTx.fcInvact2d1.byte[0] = (ctrl->fcInvact2d >> 8);

	ioDisp.hdmiTx.fcActspcHdlrCfg.byte[0] = ctrl->fcActspcHdlrCfg.byte;
	// H blanking pixels / V blanking pixels.
	ioDisp.hdmiTx.fcInhblank0.byte[0] = (ctrl->fcInhblank & 0x00FF);
	ioDisp.hdmiTx.fcInhblank1.byte[0] = (ctrl->fcInhblank >> 8);

	ioDisp.hdmiTx.fcInvblank = ctrl->fcInvblank;
	// HSync offset / VSync offset.
	ioDisp.hdmiTx.fcHsyncindelay0.byte[0] = (ctrl->fcHsyncindelay & 0x00FF);
	ioDisp.hdmiTx.fcHsyncindelay1.byte[0] = (ctrl->fcHsyncindelay >> 8);

	ioDisp.hdmiTx.fcVsyncindelay = ctrl->fcVsyncindelay;
	// HSync pulse width / VSync pulse width.
	ioDisp.hdmiTx.fcHsyncinwidth0.byte[0] = (ctrl->fcHsyncinwidth & 0x00FF);
	ioDisp.hdmiTx.fcHsyncinwidth1.byte[0] = (ctrl->fcHsyncinwidth >> 8);
	ioDisp.hdmiTx.fcVsyncinwidth.byte[0] = ctrl->fcVsyncinwidth;

	// DVI mode
	ioDisp.hdmiTx.fcInvidconf.bit.dviModez = ctrl->dviModez;
	ioDisp.hdmiTx.i2cmDiv.byte[0] = 0x03;

	// Configuring the PLL.
	if (im_hdmi_configure_pll(&(ctrl->pllConfig)) != D_DDIM_OK) {
		// the PLL does not lock and no activity.
		im_hdmi_pclk_off();
		return ImHdmi_D_IM_HDMI_NG;
	}

	// Perform a reset to all clock domains.
	ioDisp.hdmiTx.mcSwrstzreq.byte[0] = 0x00;
	// Re-Write the VSync pulse width.
	ioDisp.hdmiTx.fcVsyncinwidth.bit.vInWidth = ctrl->fcVsyncinwidth;

	// configure Infoframes.
	ret = im_hdmi_configure_infoframes(&(ctrl->infoFrames));
	if (ret != D_DDIM_OK) {
		// result NG.
	}

	im_hdmi_pclk_off();
	return ret;
}

ImHdmiEnum* im_hdmi_enum_new(void)
{
	ImHdmiEnum *self = k_object_new_with_private(IM_TYPE_HDMI_ENUM, sizeof(ImHdmiEnumPrivate));
	return self;
}