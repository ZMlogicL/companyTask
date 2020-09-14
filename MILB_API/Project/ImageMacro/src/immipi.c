/*
 * camera.c
 *
 *  Created on: 2020年6月2日
 *      Author: sns
 */


#include "jdsdisp3a.h"

#include "dd_top.h"
#include "dd_arm.h"
#include "im_disp.h"
#include "immipi.h"

typedef struct _ImMipiPrivate ImMipiPrivate;
 struct _ImMipiPrivate
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImMipiPrivate, im_mipi, sizeof(ImMipiPrivate),K_TYPE_OBJECT)
#define IM_MIPI_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImMipiPrivate, IM_TYPE_MIPI))


static void im_mipi_constructor(ImMipiPrivate *self)
{
	ImMipiPrivate *priv = IM_MIPI_GET_PRIVATE(self);
	priv-> a =  0;
}

static void im_mipi_destructor(ImMipiPrivate *self)
{
	ImMipiPrivate *priv = IM_MIPI_GET_PRIVATE(self);
	priv-> a =  0;
}

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Bit of PHY_STATUS register corresponding to the specified number of lanes.
#define ImMipi_IM_MIPI_PHY_STATUS_1LANE				(0x003C)		// 1 data lane (lane 0) and clock lane					: PHY_STATUS[5:2].
#define ImMipi_IM_MIPI_PHY_STATUS_2LANES				(0x01BC)		// 2 lanes (lane 0 and lane 1) and clock lane			: PHY_STATUS[8:2].
#define ImMipi_IM_MIPI_PHY_STATUS_3LANES				(0x07BC)		// 3 lanes (lane 0, 1, and lane 2) and clock lane		: PHY_STATUS[10:2].
#define ImMipi_IM_MIPI_PHY_STATUS_4LANES				(0x1FBC)		// 4 lanes (lane 0, 1, 2,  and lane 3) and clock lane	: PHY_STATUS[12:2].

#define ImMipi_IM_MIPI_PHY_STATUS_ALL_ACTIVE_NOT		(0x1528)		// phy_ulpsactivenot0/1/2/3/clklane bits				: PHY_STATUS[12][10][8][5][3].

// Interrupt status.
#define ImMipi_IM_MIPI_INT_TO_HS_TX					(0x00000001)	// INT_ST1.toHsTx.
#define ImMipi_IM_MIPI_INT_DPI_PLD_WR_ERR				(0x00000080)	// INT_ST1.dpiPldWrErr.
#define ImMipi_IM_MIPI_INT_GEN_CMD_WR_ERR				(0x00000100)	// INT_ST1.genCmdWrErr.
#define ImMipi_IM_MIPI_INT_GEN_PLD_WR_ERR				(0x00000200)	// INT_ST1.genPldWrErr.
#define ImMipi_IM_MIPI_INT_GEN_PLD_SEND_ERR			(0x00000400)	// INT_ST1.genPldSendErr.
#define ImMipi_IM_MIPI_INT_NUM							(5)				// Max number.

// wait.
#define ImMipi_IM_MIPI_WAIT_US( usec )					Dd_ARM_Wait_ns( usec * 1000 )

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static volatile VP_CALLBACK		S_GIM_MIPI_INT_CALLBACK[ImMipi_IM_MIPI_INT_NUM] = {
	NULL, NULL, NULL, NULL, NULL
};

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
static VOID imMipiPclkOn(VOID);
static VOID imMipiPclkOff(VOID);

static VOID imMipiPclkOn(VOID)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_On();
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief	PCLK change to OFF.
 * @param	VOID.
 * @retval	VOID.
 */
static VOID imMipiPclkOff(VOID)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_Off();
#endif	// CO_ACT_PCLOCK
}

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief	Initialization and recovery form shutdown.
 */
VOID im_mipi_init(ImMipi*self,EImMipiActiveDataLane lane)
{
	imMipiPclkOn();

	// Initialization and Recovery form Shutdown.
	IO_DISP.MIPI_DSI.PHY_IF_CFG.bit.n_lanes			= lane;								// data lane.
	IO_DISP.MIPI_DSI.PHY_RSTZ.bit.phy_shutdownz		= 1;								// Power-down state.
	IO_DISP.MIPI_DSI.PWR_UP.bit.shutdownz			= ImMipi_E_IM_MIPI_SHUTDOWNZ_POWER_UP;		// Power-up.

	imMipiPclkOff();
}

/**
 * @brief	LPCLK control.
 */
VOID im_mipi_lpclk_ctrl(ImMipi*self,UCHAR lpclk)
{
	imMipiPclkOn();

	IO_DISP.MIPI_DSI.LPCLK_CTRL.bit.phy_txrequestclkhs	= lpclk;	// D-PHY PPI txrequestclkhs signal.

	// Wait Tinit (Tinit : min 1us).
	ImMipi_IM_MIPI_WAIT_US(1);

	imMipiPclkOff();
}

/**
 * @brief	Power-up/down control.
 */
VOID im_mipi_power_ctrl(ImMipi*self,EImMipiPhyShutdownz power, EImMipiShutdownz reset)
{
	imMipiPclkOn();

	IO_DISP.MIPI_DSI.PHY_RSTZ.bit.phy_shutdownz		= power;	// Power-down state.

	// Power-up.
	if (power == ImMipi_E_IM_MIPI_PHY_SHUTDOWNZ_POWER_UP) {
		IO_DISP.MIPI_DSI.PWR_UP.bit.shutdownz		= reset;	// Power-up / Reset.
	}

	imMipiPclkOff();
}

/**
 * @brief	Enter ULPS on both clock lane and data lane.
 */
INT32 im_mipi_enter_ulps(ImMipi*self)
{
	ULONG	phy_status	= 0;

	imMipiPclkOn();

	// Verify the initial status.
	if ((IO_DISP.MIPI_DSI.PHY_ULPS_CTRL.word != 0) ||
		(IO_DISP.MIPI_DSI.PHY_TX_TRIGGERS.word != 0)) {
		// status NG.
		imMipiPclkOff();
		return ImMipi_D_IM_MIPI_NG;
	}

	// check number of data lanes.
	switch (IO_DISP.MIPI_DSI.PHY_IF_CFG.bit.n_lanes) {
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_1:		// One data lane.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_1LANE;
			break;
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_2:		// Two data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_2LANES;
			break;
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_3:		// Three data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_3LANES;
			break;
		default:								// Four data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_4LANES;
			break;
	}

	// Verify that all active lanes are in Stop state.
	if ((IO_DISP.MIPI_DSI.PHY_STATUS.word & phy_status) != phy_status) {
		// status NG.
		imMipiPclkOff();
		return ImMipi_D_IM_MIPI_NG;
	}

	// ULPS mode Request on all active data lanes, Request on clock lane.
	IO_DISP.MIPI_DSI.PHY_ULPS_CTRL.word	= 0x00000005;

	// Wait until the D-PHY active lanes enter into ULPS.
	while ((IO_DISP.MIPI_DSI.PHY_STATUS.word & ImMipi_IM_MIPI_PHY_STATUS_4LANES) != 0) {
		// Wait.
		DDIM_User_Dly_Tsk(1);
	}

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Exit ULPS on both clock lane and data lane.
 */
INT32 im_mipi_exit_ulps(ImMipi*self)
{
	ULONG	phy_status	= 0;

	imMipiPclkOn();

	// check number of data lanes.
	switch (IO_DISP.MIPI_DSI.PHY_IF_CFG.bit.n_lanes) {
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_1:		// One data lane.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_1LANE;
			break;
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_2:		// Two data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_2LANES;
			break;
		case ImMipi_E_IM_MIPI_ACTIVE_DATA_LANE_3:		// Three data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_3LANES;
			break;
		default:								// Four data lanes.
			phy_status = ImMipi_IM_MIPI_PHY_STATUS_4LANES;
			break;
	}

	// Verify that all active lanes are ULPS.
	if ((IO_DISP.MIPI_DSI.PHY_STATUS.word & phy_status) != 0) {
		// status NG.
		imMipiPclkOff();
		return ImMipi_D_IM_MIPI_NG;
	}

	// Without deasserting the ULPS request bits, assert the Exit ULPS bits by setting.
	IO_DISP.MIPI_DSI.PHY_ULPS_CTRL.word	= 0x000F;

	// Wait until all active lanes exit ULPS.
	while ((IO_DISP.MIPI_DSI.PHY_STATUS.word & ImMipi_IM_MIPI_PHY_STATUS_ALL_ACTIVE_NOT) != ImMipi_IM_MIPI_PHY_STATUS_ALL_ACTIVE_NOT) {
		// Wait.
		DDIM_User_Dly_Tsk(1);
	}

	// Deassert the ULPS request and the ULPS exit bits by setting.
	IO_DISP.MIPI_DSI.PHY_ULPS_CTRL.word	= 0x0000;

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Set clock lane / data lane / TCLK POST.
 */
INT32 im_mipi_set_lane_info( TImMipiDpiLaneInfo const *const lane_info )
{
#ifdef CO_PARAM_CHECK
	if (lane_info == NULL) {
		Ddim_Assertion(("im_mipi_set_lane_info Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// set Lane.
	IO_DISP.MIPI_DSI.PHY_SETUP_CL.word			= lane_info->clockLane.word;	// clock lane.
	IO_DISP.MIPI_DSI.PHY_SETUP_DL.word			= lane_info->dataLane.word;	// data lane.
	IO_DISP.MIPI_DSI.PHY_TCLKPOST.bit.TCLK_POST	= lane_info->tclkpPost;		// TCLK POST.

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Get clock lane / data lane / TCLK POST.
 */
INT32 im_mipi_get_lane_info( TImMipiDpiLaneInfo *const lane_info )
{
#ifdef CO_PARAM_CHECK
	if (lane_info == NULL) {
		Ddim_Assertion(("im_mipi_set_lane_info Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Get Lane.
	lane_info->clockLane.word	= IO_DISP.MIPI_DSI.PHY_SETUP_CL.word;			// clock lane.
	lane_info->dataLane.word	= IO_DISP.MIPI_DSI.PHY_SETUP_DL.word;			// data lane.
	lane_info->tclkpPost		= IO_DISP.MIPI_DSI.PHY_TCLKPOST.bit.TCLK_POST;	// TCLK POST.

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Set DPI Resolution data.
 */
INT32 im_mipi_set_dpi_resolution( TImMipiDplResolution const *const dpi )
{
#ifdef CO_PARAM_CHECK
	if (dpi == NULL) {
		Ddim_Assertion(("im_mipi_set_dpi_resolution Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Global configuration.
	IO_DISP.MIPI_DSI.PHY_IF_CFG.bit.n_lanes					= dpi->lane;				// data lane.

	// Configure the DPI Interface to define how the DPI interface interacts with the controller.
	IO_DISP.MIPI_DSI.DPI_VCID.word							= dpi->vcid;				// virtual channel.
	IO_DISP.MIPI_DSI.DPI_COLOR_CODING.bit.dpi_color_coding	= dpi->colorCoding;		// color coding.
	IO_DISP.MIPI_DSI.DPI_COLOR_CODING.bit.loosely18En		= dpi->loosely18En;		// loosely enable.
	IO_DISP.MIPI_DSI.DPI_CFG_POL.word						= dpi->cfgPol.word;		// configures the polarity of the DPI signals.

	// set operation mode.
	IO_DISP.MIPI_DSI.MODE_CFG.bit.cmd_video_mode			= dpi->modeCfg;

	if (dpi->modeCfg == ImMipi_E_IM_MIPI_MODE_CFG_VIDEO) {
		// Video mode.

		// Select the Video Transmission Mode.
		IO_DISP.MIPI_DSI.VID_MODE_CFG.word						= dpi->vidModeCfg.word;	// configure low-power transitions.
		IO_DISP.MIPI_DSI.VID_PKT_SIZE.word						= dpi->vidPktSize;		// configure size of the active line period.

		// check Video mode transmission type : Burst Mode / Non-Burst.
		if ((dpi->vidModeCfg.bit.vidModeType & ImMipi_D_IM_MIPI_VID_MODE_TYPE_BURST) != ImMipi_D_IM_MIPI_VID_MODE_TYPE_BURST)
		{
			// Non-Burst.
			IO_DISP.MIPI_DSI.VID_NUM_CHUNKS.word				= dpi->vidNumChunks;		// configures the number of chunks to use.
			IO_DISP.MIPI_DSI.VID_NULL_SIZE.word					= dpi->vidNullSize;		// configures ths size of null packets.
		}

		// Define the DPI Horizontal timing configuration.
		IO_DISP.MIPI_DSI.VID_HLINE_TIME.word					= dpi->vidHlineTime;		// the overall time for each video line.
	    IO_DISP.MIPI_DSI.VID_HSA_TIME.word						= dpi->vidHsaTime;		// the video Horizontal Synchronism Active time.
		IO_DISP.MIPI_DSI.VID_HBP_TIME.word						= dpi->vidHbpTime;		// the video Horizontal Back Porch time.

		// Define the Vertical line configuration.
		IO_DISP.MIPI_DSI.VID_VSA_LINES.word						= dpi->vidVsaLines;		// DPI Vertical Sync Active period.
	    IO_DISP.MIPI_DSI.VID_VBP_LINES.word						= dpi->vidVbpLines;		// DPI Vertical Back Porch period.
		IO_DISP.MIPI_DSI.VID_VFP_LINES.word						= dpi->vidVfpLines;		// DPI Vertical Front Porch period.
		IO_DISP.MIPI_DSI.VID_VACTIVE_LINES.word					= dpi->vidVactiveLines;	// DPI Vertical Active period.
	}
	else {
		// Commnad mode.
		IO_DISP.MIPI_DSI.CMD_MODE_CFG.word						= dpi->cmdModeCfg.word;	// configure command transitions.
	}

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Get DPI Resolution data.
 */
INT32 im_mipi_get_dpi_resolution(TImMipiDplResolution *const dpi)
{
#ifdef CO_PARAM_CHECK
	if (dpi == NULL) {
		Ddim_Assertion(("im_mipi_get_dpi_resolution Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Get DPI Resolution.
	// PHY_IF_CFG.
	dpi->lane				= (EImMipiActiveDataLane)IO_DISP.MIPI_DSI.PHY_IF_CFG.bit.n_lanes;
	// DPI_VCID/DPI_COLOR_CODING/DPI_CFG_POL.
	dpi->vcid				= IO_DISP.MIPI_DSI.DPI_VCID.word;
	dpi->colorCoding		= IO_DISP.MIPI_DSI.DPI_COLOR_CODING.bit.dpi_color_coding;
	dpi->loosely18En		= IO_DISP.MIPI_DSI.DPI_COLOR_CODING.bit.loosely18En;
	dpi->cfgPol.word		= IO_DISP.MIPI_DSI.DPI_CFG_POL.word;
	// MODE_CFG.
	dpi->modeCfg			= (EImMipiModeCfg)IO_DISP.MIPI_DSI.MODE_CFG.bit.cmd_video_mode;
	// VID_MODE_CFG/VID_PKT_SIZE/VID_NUM_CHUNKS/VID_NULL_SIZE.
	dpi->vidModeCfg.word	= IO_DISP.MIPI_DSI.VID_MODE_CFG.word;
	dpi->vidPktSize		= IO_DISP.MIPI_DSI.VID_PKT_SIZE.word;
	dpi->vidNumChunks		= IO_DISP.MIPI_DSI.VID_NUM_CHUNKS.word;
	dpi->vidNullSize		= IO_DISP.MIPI_DSI.VID_NULL_SIZE.word;
	// VID_HLINE_TIME/VID_HSA_TIME/VID_HBP_TIME.
	dpi->vidHlineTime		= IO_DISP.MIPI_DSI.VID_HLINE_TIME.word;
    dpi->vidHsaTime		= IO_DISP.MIPI_DSI.VID_HSA_TIME.word;
	dpi->vidHbpTime		= IO_DISP.MIPI_DSI.VID_HBP_TIME.word;
	// VID_VSA_LINES/VID_VBP_LINES/VID_VFP_LINES/VID_VACTIVE_LINES.
	dpi->vidVsaLines		= IO_DISP.MIPI_DSI.VID_VSA_LINES.word;
    dpi->vidVbpLines		= IO_DISP.MIPI_DSI.VID_VBP_LINES.word;
	dpi->vidVfpLines		= IO_DISP.MIPI_DSI.VID_VFP_LINES.word;
	dpi->vidVactiveLines	= IO_DISP.MIPI_DSI.VID_VACTIVE_LINES.word;
	// CMD_MODE_CFG.
	dpi->cmdModeCfg.word	= IO_DISP.MIPI_DSI.CMD_MODE_CFG.word;

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Updating the DPI Configuration.
 */
INT32 im_mipi_update_dpi(VOID)
{
	imMipiPclkOn();

	// Update availability check.
	if (IO_DISP.MIPI_DSI.VID_SHADOW_CTRL.bit.vid_shadow_en == ImMipi_D_IM_MIPI_ENABLE_OFF) {
		// Update disable.
		imMipiPclkOff();
		return ImMipi_D_IM_MIPI_NG;
	}

	// Update check.
	if (IO_DISP.MIPI_DSI.VID_SHADOW_CTRL.bit.vid_shadow_req == ImMipi_D_IM_MIPI_ENABLE_ON) {
		// Updateing now.
		imMipiPclkOff();
		return ImMipi_D_IM_MIPI_NG;
	}

	// Request update.
	IO_DISP.MIPI_DSI.VID_SHADOW_CTRL.bit.vid_shadow_req = ImMipi_D_IM_MIPI_ENABLE_ON;

	// wait update complete.
	if (IO_DISP.MIPI_DSI.VID_SHADOW_CTRL.bit.vid_shadow_req == ImMipi_D_IM_MIPI_ENABLE_ON) {
		// 100us wait.
		ImMipi_IM_MIPI_WAIT_US(100);
	}

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Set Transmission Configuration.
 */
INT32 im_mipi_set_transmission_configutation(TImMipiTransConfig const *const config)
{
#ifdef CO_PARAM_CHECK
	if (config == NULL) {
		Ddim_Assertion(("im_mipi_set_transmission_configutation Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Set CLKMGR_CFG.
	IO_DISP.MIPI_DSI.CLKMGR_CFG.word			= config->clkmgrCfg.word;

	// Set DPI_LP_CMD_TIM.
	IO_DISP.MIPI_DSI.DPI_LP_CMD_TIM.word		= config->dpiLpCmdTim.word;

	// Set TO_CNT_CFG(timer counter).
	IO_DISP.MIPI_DSI.TO_CNT_CFG.bit.hstx_to_cnt	= config->timerCount;

	// Set PHY_TMR_LPCLK_CFG.
	IO_DISP.MIPI_DSI.PHY_TMR_LPCLK_CFG.word		= config->phyTmrLpclkCfg.word;

	// Set PHY_TMR_CFG.
	IO_DISP.MIPI_DSI.PHY_TMR_CFG.word			= config->phyTmrCfg.word;

	imMipiPclkOff();

	return D_DDIM_OK;
}


/**
 * @brief	Get Transmission Configuration.
 */
INT32 im_mipi_get_transmission_configutation(TImMipiTransConfig *const config)
{
#ifdef CO_PARAM_CHECK
	if (config == NULL) {
		Ddim_Assertion(("im_mipi_get_transmission_configutation Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Get CLKMGR_CFG.
	config->clkmgrCfg.word		= IO_DISP.MIPI_DSI.CLKMGR_CFG.word;

	// Get DPI_LP_CMD_TIM.
	config->dpiLpCmdTim.word	= IO_DISP.MIPI_DSI.DPI_LP_CMD_TIM.word;

	// Get TO_CNT_CFG.
	config->timerCount			= IO_DISP.MIPI_DSI.TO_CNT_CFG.bit.hstx_to_cnt;

	// Get PHY_TMR_LPCLK_CFG.
	config->phyTmrLpclkCfg.word	= IO_DISP.MIPI_DSI.PHY_TMR_LPCLK_CFG.word;

	// Get PHY_TMR_CFG.
	config->phyTmrCfg.word	= IO_DISP.MIPI_DSI.PHY_TMR_CFG.word;

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Paket Transmission.
 */
INT32 im_mipi_packet_transmission(UCHAR header_num, UCHAR payload_num, const UImMipiGenHdr header[ImMipi_D_IM_MIPI_PACKET_NUM_MAX], const ULONG payload[ImMipi_D_IM_MIPI_PACKET_NUM_MAX])
{
	INT32 loop;
	INT32 wait_counter1 = 0;
	INT32 wait_counter2 = 0;

#ifdef CO_PARAM_CHECK
	if ((header == NULL) || (payload == NULL)) {
		Ddim_Assertion(("im_mipi_packet_transmission Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
	if (header_num > ImMipi_D_IM_MIPI_PACKET_NUM_MAX) {
		Ddim_Assertion(("im_mipi_packet_transmission Input_Param_Err pkt_num=0\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	for (loop = 0; loop < payload_num; loop++) {
		// Write payload data.
		IO_DISP.MIPI_DSI.GEN_PLD_DATA.word = payload[loop];
	}

	for (loop = 0; loop < header_num; loop++) {
		// Write header data.
		IO_DISP.MIPI_DSI.GEN_HDR.word = header[loop].word;
	}

	// wait FIFO empty.
	while(wait_counter1 < 100) {
		if( IO_DISP.MIPI_DSI.CMD_PKT_STATUS.bit.gen_cmd_empty != ImMipi_D_IM_MIPI_ENABLE_OFF) {
			break;
		}
		wait_counter1++;
		// wait.
		ImMipi_IM_MIPI_WAIT_US(100);
	}

	// PHY status check
	while(wait_counter2 < 100) {
		if( (IO_DISP.MIPI_DSI.PHY_STATUS.bit.phy_stopstate0lane != ImMipi_D_IM_MIPI_ENABLE_OFF) &&
			(IO_DISP.MIPI_DSI.PHY_STATUS.bit.phy_stopstate1lane != ImMipi_D_IM_MIPI_ENABLE_OFF) &&
			(IO_DISP.MIPI_DSI.PHY_STATUS.bit.phy_stopstate2lane != ImMipi_D_IM_MIPI_ENABLE_OFF) &&
			(IO_DISP.MIPI_DSI.PHY_STATUS.bit.phy_stopstate3lane != ImMipi_D_IM_MIPI_ENABLE_OFF) ) {
			break;
		}
		wait_counter2++;
		// wait.
		ImMipi_IM_MIPI_WAIT_US(100);
	}
	if( (wait_counter1 == 100) || (wait_counter2 == 100) ){
		Ddim_Print(("im_mipi_packet_transmission TimeOut Error. wait1=%x,wait2=%x\n", wait_counter1,wait_counter2));
		return D_DDIM_TIMEOUT;
	}

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Set Timeer count.
 */
VOID im_mipi_set_timer_count(ImMipi*self,UCHAR count)
{
	imMipiPclkOn();

	// Set CLKMGR_CFG.toClkDivision.
	IO_DISP.MIPI_DSI.CLKMGR_CFG.bit.toClkDivision	= count;

	imMipiPclkOff();
}

/**
 * @brief	Set Interrupt mask.
 */
VOID im_mipi_set_int_mask(ImMipi*self,UImMipiIntMsk1 int_msk1)
{
	imMipiPclkOn();

	// Set INT_MSK1.
	IO_DISP.MIPI_DSI.INT_MSK1.word	= int_msk1.word;

	imMipiPclkOff();
}

/**
 * @brief	Get Interrupt mask.
 */
INT32 im_mipi_get_int_mask(UImMipiIntMsk1* int_msk1)
{
#ifdef CO_PARAM_CHECK
	if (int_msk1 == NULL) {
		Ddim_Assertion(("im_mipi_get_int_mask Input_Param_Err status NULL\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif
	imMipiPclkOn();

	// Get INT_MSK1.
	int_msk1->word	= IO_DISP.MIPI_DSI.INT_MSK1.word;

	imMipiPclkOff();

	return D_DDIM_OK;
}

/**
 * @brief	Set interrupt callback function.
 */
INT32 im_mipi_set_int_callback(EImMipiIntType interrupt_type, VP_CALLBACK vp_callback)
{
#ifdef CO_PARAM_CHECK
	if (interrupt_type == ImMipi_E_IM_MIPI_INT_TYPE_MAX) {
		Ddim_Assertion(("im_mipi_set_int_callback Input_Param_Err NG\n"));
		return ImMipi_D_IM_MIPI_INPUT_PARAM_ERROR;
	}
#endif

	// Set interrupt callback.
	S_GIM_MIPI_INT_CALLBACK[interrupt_type] = vp_callback;

	return D_DDIM_OK;
}

/**
 * @brief	Interrupt handler.
 */
VOID im_mipi_int_handler(VOID)
{
	INT32 loop;

	// INT_ST1 register bit.
	ULONG int_st1_bit[] = {
		ImMipi_IM_MIPI_INT_TO_HS_TX,
		ImMipi_IM_MIPI_INT_DPI_PLD_WR_ERR,
		ImMipi_IM_MIPI_INT_GEN_CMD_WR_ERR,
		ImMipi_IM_MIPI_INT_GEN_PLD_WR_ERR,
		ImMipi_IM_MIPI_INT_GEN_PLD_SEND_ERR
	};

	imMipiPclkOn();

	// Interrupt status.
	for (loop = 0; loop < sizeof(int_st1_bit)/sizeof(int_st1_bit[0]); loop++) {
		// check register bit.
		if ((IO_DISP.MIPI_DSI.INT_ST1.word & int_st1_bit[loop]) == int_st1_bit[loop]) {
			// callback.
			if (S_GIM_MIPI_INT_CALLBACK[loop] != NULL) {
				S_GIM_MIPI_INT_CALLBACK[loop]();
			}
		}
	}

	imMipiPclkOff();

	return;
}


ImMipi *im_mipi_new(void)
{
	ImMipi* self = k_object_new(IM_TYPE_MIPI);
	return self;
}
