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
#include "ddarm.h"
#include "imdisp.h"
#include "imhdmi.h"


G_DEFINE_TYPE(ImHdmi, im_hdmi, G_TYPE_OBJECT);
#define IM_HDMI_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_HDMI, ImHdmiPrivate));

// wait.
#define ImHdmi_IM_HDMI_WAIT_US( usec )								Dd_ARM_Wait_ns( usec * 1000 )
#define ImHdmi_IM_HDMI_WAIT_NS( nsec )								Dd_ARM_Wait_ns( nsec )

struct _ImHdmiPrivate
{
	gint a;
};


/*----------------------------------------------------------------------	*/
/* Global Data																*/
/*----------------------------------------------------------------------	*/
static volatile VP_HDMI_CALLBACK S_GIM_HDMI_INT_CALLBACK = NULL;
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
static void 		imHdmiCallbackInterruptI2cm(void);
static void 		imHdmiCallbackInterruptI2cmphy(void);
static void 		imHdmiCallbackInterruptPhyLock(void);
static gint32 		imHdmiPhyWrite(guchar address, gushort data);
/**
 *IMPL
 */
static void 		im_hdmi_class_init(ImHdmiClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_aim_private(klass, sizeof(ImHdmiPrivate));
}

static void 		im_hdmi_init(ImHdmi *self)
{
	ImHdmiPrivate *priv = IM_HDMI_GET_PRIVATE(self);
	self->ddimUserCustomTest = ddim_user_custom_test_new();
	self->imHdmiEnum = im_hdmi_enum_new();
}

static void 		dispose_od(GObject *object)
{
	ImHdmiPrivate *priv = IM_HDMI_GET_PRIVATE(object);
	ImHdmi *self = im_hdmi_new();
	if(self->ddimUserCustomTest){
		g_object_unref(self->ddimUserCustomTest);
		self->ddimUserCustomTest = NULL;
	}
	if(self->imHdmiEnum){
		g_object_unref(self->imHdmiEnum);
		self->imHdmiEnum = NULL;
	}
	G_OBJECT_CLASS(im_hdmi_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	ImHdmiPrivate *priv = IM_HDMI_GET_PRIVATE(object);
	G_OBJECT_CLASS(im_hdmi_parent_class) -> dispose(object);
}

/**
 * @brief	Interrupt callback (i2cm).
 * @param	void.
 * @retval	void.
 */
static void imHdmiCallbackInterruptI2cm(void)
{
	ImHdmi *self = im_hdmi_new();
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	ret = ddim_user_custom_set_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM);
	if(ret != DdimUserCustom_E_OK){
		Ddim_Print(("Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
	}
}

/**
 * @brief	Interrupt callback (i2cmphy).
 * @param	void.
 * @retval	void.
 */
static void imHdmiCallbackInterruptI2cmphy(void)
{
	ImHdmi *self = im_hdmi_new();
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	ret = ddim_user_custom_set_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM);
	if(ret != DdimUserCustom_E_OK){
		Ddim_Print(("imHdmiCallbackInterruptI2cmphy Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
	}
}

/**
 * @brief	Interrupt callback (phy_lock).
 * @param	void.
 * @retval	void.
 */
static void imHdmiCallbackInterruptPhyLock(void)
{
	ImHdmi *self = im_hdmi_new();
	DdimUserCustom_ER ret = DdimUserCustom_E_OK;

	ret = ddim_user_custom_set_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM);
	if(ret != DdimUserCustom_E_OK){
		Ddim_Print(("imHdmiCallbackInterruptPhyLock Error DDIM_User_Set_Flg!! ret = 0x%x\n", ret));
	}
}

/**
 * @brief	PHY Write.
 * @param[in]	address		PHY Register Address (Offset).
 * @param[in]	data		Write data.
 * @retval	D_DDIM_OK						Success.
 * @retval	ImHdmi_D_IM_HDMI_TIMEOUT				timeout.
 */
static gint32 imHdmiPhyWrite(guchar address, gushort data)
{
	ImHdmi *self = im_hdmi_new();
	DdimUserCustom_FLGPTN flgptn = 0;

	// clear Interrupt flag.
	ddim_user_custom_clr_flg(self->ddimUserCustomTest, FID_IM_HDMI, ~(ImHdmi_D_IM_HDMI_INT_FLG_I2CM));

	// 0:Standard Mode
	ioDisp.hdmiTx.phyI2cmDiv.bit.fastStdMode = 0;

	// Set the PHY slave address.
	ioDisp.hdmiTx.phyI2cmSlave.byte[0] = 0x69;
	// Write register address.
	ioDisp.hdmiTx.phyI2cmAddress = address;
	// Write data.
	ioDisp.hdmiTx.phyI2cmDatao1 = (guchar) (data >> 8);
	ioDisp.hdmiTx.phyI2cmDatao0 = (guchar) (data & 0x00FF);
	// Write operation.
	ioDisp.hdmiTx.phyI2cmOperation.byte[0] = 0x10;

	// Wait for a done interruption from the I2C master.
	if (ddim_user_custom_twai_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM,
		DdimUserCustom_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME) != DdimUserCustom_E_OK) {
		return ImHdmi_D_IM_HDMI_TIMEOUT;
	}

	return D_DDIM_OK;
}
/**
 * PUBLIC
 */
/*----------------------------------------------------------------------	*/
/* Function																		*/
/*----------------------------------------------------------------------	*/
/**
 * @brief	PCLK change to ON.
 * @param	void.
 * @retval	void.
 */
void im_hdmi_pclk_on (ImHdmi *self) {
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_On();
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief	PCLK change to OFF.
 * @param	void.
 * @retval	void.
 */
void im_hdmi_pclk_off(ImHdmi *self)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_Off();
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief	PHY Read.
 * @param[in]	address		PHY Register Address (Offset).
 * @param[out]	data		Read data.
 * @retval	D_DDIM_OK						Success.
 * @retval	ImHdmi_D_IM_HDMI_TIMEOUT				timeout.
 */
gint32 im_hdmi_phy_read(ImHdmi *self, guchar address, gushort *data)
{
	DdimUserCustom_FLGPTN flgptn = 0;

	// clear Interrupt flag.
	ddim_user_custom_clr_flg(self->ddimUserCustomTest, FID_IM_HDMI, ~(ImHdmi_D_IM_HDMI_INT_FLG_I2CM));

	 // 0:Standard Mode
	ioDisp.hdmiTx.phyI2cmDiv.bit.fastStdMode = 0;

	// Set the PHY slave address.
	ioDisp.hdmiTx.phyI2cmSlave.byte[0] = 0x69;
	// Read register address.
	ioDisp.hdmiTx.phyI2cmAddress = address;
	// Read operation.
	ioDisp.hdmiTx.phyI2cmOperation.byte[0] = 0x01;

	// Wait for a done interruption from the I2C master.
	if (ddim_user_custom_twai_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM,
		DdimUserCustom_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME) != DdimUserCustom_E_OK) {
		return ImHdmi_D_IM_HDMI_TIMEOUT;
	}

	// Read data.
	*data = (ioDisp.hdmiTx.phyI2cmDatai1 << 8) | ioDisp.hdmiTx.phyI2cmDatai0;

	return D_DDIM_OK;
}

/**
 * @brief	Configure the PLL.
 * @param[in]	pllConfig		configure paramter.
 * @retval	D_DDIM_OK						Success.
 * @retval	ImHdmi_D_IM_HDMI_NG					NG.
 * @retval	ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR		Input parameter error.
 * @retval	ImHdmi_D_IM_HDMI_TIMEOUT				timeout.
 */
gint32 im_hdmi_configure_pll(ImHdmi *self, ThdmiPllConfig const *const pllConfig)
{
	gint32 ret = D_DDIM_OK;
	DdimUserCustom_FLGPTN flgptn = 0;
	gint loop;

#ifdef CO_PARAM_CHECK
	if (pllConfig == NULL) {
		Ddim_Assertion(("im_hdmi_configure_pll Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
	if (pllConfig->phyRegNum > ImHdmi_D_IM_HDMI_PHY_REG_NUM) {
		Ddim_Assertion(("im_hdmi_configure_pll phyRegNum Max size over\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif

	// Power-on, configure the PLL, and reset the HDMI TX PHY.
	// Configure a HDMI TX PHY.
	// PHY SVSRET, PHY PDDQ, PHY ENHPDRXSENSE signal.
	ioDisp.hdmiTx.phyConf0.byte[0] = 0x36;

	// Reset.
	ioDisp.hdmiTx.mcPhyrstz.byte[0] = ImHdmi_D_IM_HDMI_PHYRSTZ_RESET;

	// Video Packetizer Pixel Repetition and Color Depth.
	ioDisp.hdmiTx.vpPrCd.byte[0] = pllConfig->vpPrCd.byte;

	// wait 450ns.
	ImHdmi_IM_HDMI_WAIT_NS(450);

	// Reset cancel.
	ioDisp.hdmiTx.mcPhyrstz.byte[0] = ImHdmi_D_IM_HDMI_PHYRSTZ_CANCEL;

	// PHY Register setting.
	for (loop = 0; loop < pllConfig->phyRegNum; loop++) {
		ret = imHdmiPhyWrite(pllConfig->phyRegAddr[loop], pllConfig->phyRegData[loop]);
		if (ret != D_DDIM_OK) {
			return ret;
		}
	}

	// set power-on mode
	// PHY SVSRET, PHY TXPWRON, PHY ENHPDRXSENSE signal.
	ioDisp.hdmiTx.phyConf0.byte[0] = 0x2E;

	// clear Interrupt flag.
	ddim_user_custom_clr_flg(self->ddimUserCustomTest, FID_IM_HDMI, ~(ImHdmi_D_IM_HDMI_INT_FLG_I2CM));

	// check PHY lock
	// Wait for a done interruption from the PHY.
	if (ddim_user_custom_twai_flg(self->ddimUserCustomTest, FID_IM_HDMI, ImHdmi_D_IM_HDMI_INT_FLG_I2CM,
		DdimUserCustom_TWF_ORW, &flgptn, D_DDIM_WAIT_END_TIME) != DdimUserCustom_E_OK) {
		return ImHdmi_D_IM_HDMI_TIMEOUT;
	}

	return ret;
}

/**
 * @brief	Configure Infoframes.
 * @param[in]	infoFrames		configure paramter.
 * @retval		D_DDIM_OK						Success.
 * @retval		ImHdmi_D_IM_HDMI_NG					NG.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR		Input parameter error.
 */
gint32 im_hdmi_configure_infoframes(ImHdmi *self, ThdmiInfoFrames const *const infoFrames)
{
	gint32 ret = D_DDIM_OK;
	gint index;
#ifdef CO_PARAM_CHECK
	if (infoFrames == NULL) {
		Ddim_Assertion(("im_hdmi_configure_infoframes Input_Param_Err status NULL\n"));
		return ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}
#endif

	// AVI InfoFrame.
	ioDisp.hdmiTx.fcAviconf0.byte[0] = infoFrames->fcAviconf0.byte;
	ioDisp.hdmiTx.fcAviconf1.byte[0] = infoFrames->fcAviconf1.byte;
	ioDisp.hdmiTx.fcAviconf2.byte[0] = infoFrames->fcAviconf2.byte;
	ioDisp.hdmiTx.fcAviconf3.byte[0] = infoFrames->fcAviconf3.byte;
	ioDisp.hdmiTx.fcAvivid.byte[0] = infoFrames->fcAvivid;
	ioDisp.hdmiTx.fcPrconf.byte[0] = infoFrames->fcPrconf.byte;

	ioDisp.hdmiTx.fcScramblerCtrl.bit.scramblerOn = infoFrames->scramblerOn;

	// HDMI Vendor-Specific Infoframe.
	ioDisp.hdmiTx.fcVsdieeeid0 = infoFrames->fcVsdieeeid[0];
	ioDisp.hdmiTx.fcVsdieeeid1 = infoFrames->fcVsdieeeid[1];
	ioDisp.hdmiTx.fcVsdieeeid2 = infoFrames->fcVsdieeeid[2];

	// Video Mode (HDMI or 3D)
	ioDisp.hdmiTx.fcVsdpayload[0].byte[0] = infoFrames->videoMode;

	if (infoFrames->videoMode == ImHdmi_D_IM_HDMI_VIDEO_MODE_HDMI) {
		// HDMI Video Mode.
		ioDisp.hdmiTx.fcVsdpayload[1].byte[0] = infoFrames->videoFormat;
	}
	else if (infoFrames->videoMode == ImHdmi_D_IM_HDMI_VIDEO_MODE_3D) {
		// 3D Video Mode.
		ioDisp.hdmiTx.fcVsdpayload[1].byte[0] = (infoFrames->videoFormat << 4) | (infoFrames->metaPresent << 3);
		ioDisp.hdmiTx.fcVsdpayload[2].byte[0] = infoFrames->additionalVideoFormat << 4;
		ioDisp.hdmiTx.fcVsdpayload[3].byte[0] = (infoFrames->metaType << 5) | infoFrames->metaLength;
		for (index = 0; index < 8; index++) {
			ioDisp.hdmiTx.fcVsdpayload[4 + index].byte[0] = infoFrames->metaData[index];
		}
	}
	else {
		// input paramter NG.
		ret = ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR;
	}

	// Enables SPD automatic packet scheduling
	ioDisp.hdmiTx.fcDatauto0.bit.spdAuto = 1;
	// Enables VSD automatic packet scheduling
	ioDisp.hdmiTx.fcDatauto0.bit.vsdAuto = 1;
	// auto_frame_packets
	ioDisp.hdmiTx.fcDatauto2.bit.autoFramePackets = 1;

	ioDisp.hdmiTx.fcDatauto0.bit.acpAuto = 0;
	ioDisp.hdmiTx.fcDatauto0.bit.iscr1Auto = 0;
	ioDisp.hdmiTx.fcDatauto0.bit.iscr2Auto = 0;

	return ret;
}


/**
 * @brief	Interrupt check (ihFcStat0/ihFcStat1/ihFcStat2).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_fc(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihFcStat0 register bit.
	EhdmiIhFcStat0 fcStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NULL,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACR,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDS,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NVBI,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_MAS,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_HBR,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACP,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDI
	};
	// ihFcStat1 register bit.
	EhdmiIhFcStat1 fcStat1Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GCP,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AVI,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AMP,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_SPD,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_VSD,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR2,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR1,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GMD
	};
	// ihFcStat2 register bit.
	EhdmiIhFcStat2 fcStat2Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_HP_OF,
		ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_LP_OF
	};

	// Frame Composer Interrupt Status Register 0.
	for (loop = 0; loop < sizeof(fcStat0Bit) / sizeof(fcStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihFcStat0.byte[0] & fcStat0Bit[loop]) == fcStat0Bit[loop]) {

			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0, (guchar) fcStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihFcStat0.byte[0] = fcStat0Bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}

	// Frame Composer Interrupt Status Register 1.
	for (loop = 0; loop < sizeof(fcStat1Bit) / sizeof(fcStat1Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihFcStat1.byte[0] & fcStat1Bit[loop]) == fcStat1Bit[loop]) {

			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1, (guchar) fcStat1Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihFcStat1.byte[0] = fcStat1Bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}

	// Frame Composer Interrupt Status Register 2.
	for (loop = 0; loop < sizeof(fcStat2Bit) / sizeof(fcStat2Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihFcStat2.byte[0] & fcStat2Bit[loop]) == fcStat2Bit[loop]) {

			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2, (guchar) fcStat2Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihFcStat2.byte[0] = fcStat2Bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}
/**
 * @brief	Interrupt check (ihAsStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_as(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihAsStat0 register bit.
	EhdmiIhAsStat0 as_stat0_bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OF,
		ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_UF,
		ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OR
	};

	// Audio Sampler Interrupt Status Register.
	for (loop = 0; loop < sizeof(as_stat0_bit) / sizeof(as_stat0_bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihAsStat0.byte[0] & as_stat0_bit[loop]) == as_stat0_bit[loop]) {

			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0, (guchar) as_stat0_bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihAsStat0.byte[0] = as_stat0_bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}

/**
 * @brief	Interrupt check (ihPhyStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_phy(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihPhyStat0 register bit.
	EhdmiIhPhyStat0 phyStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_HDP,
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_TX_PHY_LOCK,
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_0,
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_1,
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_2,
		ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_3
	};

	// PHY Interface Interrupt Status Register.
	for (loop = 0; loop < sizeof(phyStat0Bit) / sizeof(phyStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihPhyStat0.byte[0] & phyStat0Bit[loop]) == phyStat0Bit[loop]) {

			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0, (guchar) phyStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			//  bit clear.
			if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_HDP) {
				ioDisp.hdmiTx.phyPol0.bit.hpd = ~ioDisp.hdmiTx.phyPol0.bit.hpd;
			}
			else if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_TX_PHY_LOCK) {
				ioDisp.hdmiTx.phyPol0.bit.txPhyLock = ~ioDisp.hdmiTx.phyPol0.bit.txPhyLock;
			}
			else if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_0) {
				ioDisp.hdmiTx.phyPol0.bit.rxSense0 = ~ioDisp.hdmiTx.phyPol0.bit.rxSense0;
			}
			else if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_1) {
				ioDisp.hdmiTx.phyPol0.bit.rxSense1 = ~ioDisp.hdmiTx.phyPol0.bit.rxSense1;
			}
			else if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_2) {
				ioDisp.hdmiTx.phyPol0.bit.rxSense2 = ~ioDisp.hdmiTx.phyPol0.bit.rxSense2;
			}
			else if (phyStat0Bit[loop] == ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_3) {
				ioDisp.hdmiTx.phyPol0.bit.rxSense3 = ~ioDisp.hdmiTx.phyPol0.bit.rxSense3;
			}
			// Interrupt bit clear.
			ioDisp.hdmiTx.ihPhyStat0.byte[0] = phyStat0Bit[loop];

			// Interrupt type : ihPhyStat0.txPhyLock
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_TX_PHY_LOCK) {
				imHdmiCallbackInterruptPhyLock();
			}

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}

/**
 * @brief	Interrupt check (ihI2cmStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_i2cm(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihI2cmStat0 register bit.
	EhdmiIhI2cmStat0 i2cmStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_ERR,
		ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_DONE,
		ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_SDSC
	};

	// E-DDC I2C Master Interrupt Status Register.
	for (loop = 0; loop < sizeof(i2cmStat0Bit) / sizeof(i2cmStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihI2cmStat0.byte[0] & i2cmStat0Bit[loop]) == i2cmStat0Bit[loop]) {
			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0, (guchar) i2cmStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihI2cmStat0.byte[0] = i2cmStat0Bit[loop];

			// Interrupt type : ihI2cmStat0 Register.I2Cmasterdone
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_M_DONE) {
				imHdmiCallbackInterruptI2cm();
			}

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}

/**
 * @brief	Interrupt check (ihCecStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_cec(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihCecStat0 register bit.
	EhdmiIhCecStat0 cecStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_DONE,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_EOM,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_NACK,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ARB_LOST,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_INITIATOR,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_FOLLOW,
		ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_WAKEUP
	};

	// CEC Interrupt Status Register.
	for (loop = 0; loop < sizeof(cecStat0Bit)/sizeof(cecStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihCecStat0.byte[0] & cecStat0Bit[loop]) == cecStat0Bit[loop]) {
			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0, (guchar)cecStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihCecStat0.byte[0] = cecStat0Bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar)interruptType);
			}
		}
	}
}

/**
 * @brief	Interrupt check (ihVpStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_vp(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihVpStat0 register bit.
	EhdmiIhVpStat0 vpStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_BYP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_BYP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REMAP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REMAP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_PP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_PP,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REPET,
		ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REPET
	};

	// Video Packetizer Interrupt Status Register.
	for (loop = 0; loop < sizeof(vpStat0Bit) / sizeof(vpStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihVpStat0.byte[0] & vpStat0Bit[loop]) == vpStat0Bit[loop]) {
			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0, (guchar) vpStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihVpStat0.byte[0] = vpStat0Bit[loop];

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}

/**
 * @brief	Interrupt check (ihI2cmphyStat0).
 * @param	void.
 * @return	void.
 */
void im_hdmi_check_interrupt_i2cmphy(ImHdmi *self)
{
	gint32 loop;
	EhdmiIntType interruptType = ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX;

	// ihI2cmphyStat0 register bit.
	EhdmiIhFcStat0 i2cmphyStat0Bit[] = {
		ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_ERR,
		ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_DONE
	};

	// PHY GEN2 I2C Master Interrupt Status Register.
	for (loop = 0; loop < sizeof(i2cmphyStat0Bit) / sizeof(i2cmphyStat0Bit[0]); loop++) {
		// check register bit.
		if ((ioDisp.hdmiTx.ihI2cmphyStat0.byte[0] & i2cmphyStat0Bit[loop]) == i2cmphyStat0Bit[loop]) {
			// Get Interrupt type.
			interruptType = im_hdmi_enum_get_interrupt_type(self->imHdmiEnum, ImHdmiEnum_E_IM_HDMI_INT_REG_I2CMPHY_STAT0, (guchar) i2cmphyStat0Bit[loop]);
			// Illegal type(fail safe).
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX) {
				continue;
			}

			// Interrupt bit clear.
			ioDisp.hdmiTx.ihI2cmphyStat0.byte[0] = i2cmphyStat0Bit[loop];

			// Interrupt type : ihI2cmphyStat0.I2Cmphydone
			if (interruptType == ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CMPHY_DONE) {
				imHdmiCallbackInterruptI2cmphy();
			}

			// callback.
			if (S_GIM_HDMI_INT_CALLBACK != NULL) {
				S_GIM_HDMI_INT_CALLBACK((guchar) interruptType);
			}
		}
	}
}

ImHdmi* 		im_hdmi_new(void)
{
	ImHdmi *self = g_object_new(IM_TYPE_HDMI, NULL);
	return self;
}
