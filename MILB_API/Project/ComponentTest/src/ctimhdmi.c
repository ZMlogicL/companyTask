/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 杨文
*@brief : CtImHdmi
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimhdmi.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */


K_TYPE_DEFINE_WITH_PRIVATE(CtImHdmi, ct_im_hdmi)
#define CT_IM_HDMI_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImHdmiPrivate, CT_TYPE_IM_HDMI))


struct _CtImHdmiPrivate
{
	int a;
};


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// nothing special.


/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static const T_IM_HDMI_CSC_COEF S_GCT_IM_HDMI_CSC_MATRIX[D_IM_HDMI_CSC_CONF_COLUMN_NUM][D_IM_HDMI_CSC_CONF_ROW_NUM] = {
	{{0x00, 0x00}, {0x00, 0x0F}, {0x0F, 0x00}, {0x0F, 0x0F}},
	{{0x01, 0x01}, {0x20, 0x02}, {0x04, 0x40}, {0x80, 0x80}},
	{{0x44, 0x44}, {0x88, 0x88}, {0xCC, 0xCC}, {0xFF, 0xFF}}
};


/**
 * DECLS
 */
static VOID ctImHdmiPclkOn(VOID);
static VOID ctImHdmiPclkOff(VOID);
static VOID ctImHdmiCb0( UCHAR interruptType );


/**
 * IMPL
 */
static void ct_im_hdmi_constructor(CtImHdmi *self)
{
	CtImHdmiPrivate *priv = CT_IM_HDMI_GET_PRIVATE(self);

	priv->a = 0;
}

static void ct_im_hdmi_destructor(CtImHdmi *self)
{
	CtImHdmiPrivate *priv = CT_IM_HDMI_GET_PRIVATE(self);

	priv->a = 0;
}

/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
/**
 * @brief	PCLK change to ON.
 * @param	VOID.
 * @retval	VOID.
 */
static VOID ctImHdmiPclkOn(VOID)
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
static VOID ctImHdmiPclkOff(VOID)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_Off();
#endif	// CO_ACT_PCLOCK
}

static VOID ctImHdmiCb0( UCHAR interruptType )
{
	Ddim_Print((">> call ctImHdmiCb0() : interruptType=%d\n", interruptType));
	return;
}


/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief       Command processing of HDMI.
 * @param[in]   INT32 argc
 * @param[in]   CHAR** argv
 * @return      VOID
 */
VOID ct_im_hdmi_main( INT32 argc, char** argv )
{
	INT32	ret;
	INT32	param2;
	INT32	param3;
	INT32	param4;
	INT32	loop1;
	T_IM_HDMI_PLL_CONFIG pll_config;
	T_IM_HDMI_I2CM_CONFIG i2cmConfig;
	UCHAR read_data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	T_IM_HDMI_CTRL ctrl;
#if 0
	USHORT gmpCtrl;
	U_IM_HDMI_PLLCURRCTRL pllCurrCtrl;
	U_IM_HDMI_OPMODE_PLLCFG opMode;
	E_IM_HDMI_TXTERM txterm;
	U_IM_HDMI_CKSYMTXCTRL cksymtxctrl;
	U_IM_HDMI_VLEVCTRL vlevctrl;
#endif
	T_IM_HDMI_CSC_CONFIG cscConfig;
	U_IM_HDMI_TX_INVID0 tx_invid0;
	T_IM_HDMI_VIDEO_PACKETIZER videoPacketizer;
	T_IM_HDMI_FRAME_COMPOSER frameComposer;
	UCHAR mc_flowctrl;
	T_IM_HDMI_AUDIO audio;
	VP_HDMI_CALLBACK vpCallback;
	E_IM_HDMI_INT_REG interruptRegister;
	UCHAR mute;

	// check number of parameter
	if( argc > 20 ) { 
		Ddim_Print(("The number of input parameters is exceeded!\n"));
		return;
	}

	// 1st param check
	if( strcmp(argv[1], "init") == 0 ) {
		// Init
		ret = Im_HDMI_Init();
		if (ret == D_DDIM_OK) {
			Ddim_Print(("Im_HDMI_Init() : Normal end\n"));
			// check register
			ctImHdmiPclkOn();
			ct_im_hdmi1_printf1();
			ctImHdmiPclkOff();
		}
		else {
			Ddim_Print(("im_HDMI_Init() : Error  err_code=0x%x\n", ret));
		}
	}
	else if( strcmp(argv[1], "conf_dvi") == 0 ) {
		// Init
		// 2nd param check
		param2 = atoi((const char *)argv[2]);
		if (param2 == 0) {
			// 2nd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// PLL Config (Normal).
				pll_config.vp_pr_cd.bit.desired_pr_factor	= 0;
				pll_config.vp_pr_cd.bit.color_depth			= E_IM_HDMI_COLOR_DEPTH_8BIT;
//				pll_config.phy_i2cm_address					= 0x00;
//				pll_config.phy_i2cm_datao[0]				= 0x00;
//				pll_config.phy_i2cm_datao[1]				= 0x00;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
		}
		else if (param2 == 1) {
			// Invalid parameter (pll_config = NULL)
			ret = Im_HDMI_Configure_VGA_DVI_Video_Mode(NULL);
			Ddim_Print(("Im_HDMI_Configure_VGA_DVI_Video_Mode() : Error  err_code=0x%x\n", ret));
			// end
			return;
		}
		else if (param2 == 2) {
			// PLL Config (NG).
			pll_config.vp_pr_cd.bit.desired_pr_factor	= 0;
			pll_config.vp_pr_cd.bit.color_depth			= E_IM_HDMI_COLOR_DEPTH_8BIT;
//			pll_config.phy_i2cm_address					= 0x00;
//			pll_config.phy_i2cm_datao[0]				= 0x00;
//			pll_config.phy_i2cm_datao[1]				= 0x00;
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud : %d\n", param2));
			return;
		}
		
		ret = Im_HDMI_Configure_VGA_DVI_Video_Mode(&pll_config);
		if (ret == D_DDIM_OK) {
			Ddim_Print(("Im_HDMI_Configure_VGA_DVI_Video_Mode() : Normal end\n"));
			// check register
			ctImHdmiPclkOn();
			ct_im_hdmi1_printf2();
			ctImHdmiPclkOff();
		} else {
			Ddim_Print(("Im_HDMI_Configure_VGA_DVI_Video_Mode() : Error  err_code=0x%x\n", ret));
		}
	}
	else if( strcmp(argv[1], "sinks") == 0 ) {
		// Init
		// 2nd param check
		param2 = atoi((const char *)argv[2]);
		if (param2 == 0) {
			
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				ct_im_hdmi2_printf14();
			}
			else if (param3 == 1) {
				ct_im_hdmi2_printf15();
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
		}
		else if (param2 == 1) {
			ret = Im_HDMI_Read_Sinks_E_EDID(NULL, read_data);
			Ddim_Print(("Im_HDMI_Read_Sinks_E_EDID() : Error  err_code=0x%x\n", ret));
			// end
			return;
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud : %d\n", param2));
			return;
		}	
		ret = Im_HDMI_Read_Sinks_E_EDID(&i2cmConfig, read_data);
		if (ret == D_DDIM_OK) {
			Ddim_Print(("Im_HDMI_Read_Sinks_E_EDID() : Normal end\n"));
			// check register
			ctImHdmiPclkOn();
			ct_im_hdmi1_printf3();
			Ddim_Print( ("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
						 read_data[0], read_data[1], read_data[2], read_data[3],
						 read_data[4], read_data[5], read_data[6], read_data[7]) );
			ct_im_hdmi1_printf4();
			ctImHdmiPclkOff();
		} else {
			Ddim_Print(("Im_HDMI_Read_Sinks_E_EDID() : Error  err_code=0x%x\n", ret));
		}
	}
	else if( strcmp(argv[1], "ctrl") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 1) {
				// Invalid parameter (ctrl = NULL)
				ret = Im_HDMI_Ctrl(NULL);
				Ddim_Print(("Im_HDMI_Ctrl() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			else if (param3 == 2) {
				// PLL NG.
				ctImHdmiPclkOn();
				IO_DISP.HDMI_TX.phy_stat0.bit.TX_PHY_LOCK = 0;
				ctImHdmiPclkOff();
			}
			else if (param3 != 0) {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			memset(&ctrl, 0, sizeof( T_IM_HDMI_CTRL ));

			// 4th param check
			param4 = atoi((const char *)argv[4]);
			if (param4 == 0) {
				ct_im_hdmi1_printf7();	
			}
			else if (param4 == 1) {
				ct_im_hdmi1_printf8();
			}
			else if (param4 == 2) {
				ct_im_hdmi1_printf9();
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			ret = Im_HDMI_Ctrl(&ctrl);
			if (ret == D_DDIM_OK) {
				ct_im_hdmi1_printf5();
				for (loop1 = 0; loop1 < 24; loop1++) {
					Ddim_Print( (" - fc_vsdpayload[%d] = 0x%x\n", loop1, 
					IO_DISP.HDMI_TX.fc_vsdpayload[loop1].bit.fc_vsdpayload) );
				}
				Ddim_Print( ("----------\n") );
			} else {
				Ddim_Print(("Im_HDMI_Ctrl() : Error  err_code=0x%x\n", ret));
			}
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// table clear.
				memset( &ctrl, 0, sizeof( T_IM_HDMI_CTRL ) );
			} else {
				// Invalid parameter (ctrl = NULL)
				ret = Im_HDMI_Get_Ctrl(NULL);
				Ddim_Print(("Im_HDMI_Get_Ctrl() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Ctrl(&ctrl);
			if (ret == D_DDIM_OK) {
				ct_im_hdmi1_printf6();
				for (loop1 = 0; loop1 < 24; loop1++) {
					Ddim_Print( (" - fc_vsdpayload[%d] = 0x%x\n", loop1, IO_DISP.HDMI_TX.fc_vsdpayload[loop1].bit.fc_vsdpayload) );
				}
				Ddim_Print( ("----------\n") );
			} else {
				Ddim_Print(("Im_HDMI_Get_Ctrl() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}

#if 0
	else if ( strcmp(argv[1], "clk") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// input parameter clear.
			pllCurrCtrl.hword = 0;
			opMode.hword = 0;
			
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// set parameter.
				gmpCtrl = 0;
				pllCurrCtrl.bit.mpll_int_cntrl	= 0;
				pllCurrCtrl.bit.mpll_prop_cntrl	= 0;
				opMode.bit.n_cntrl					= 0;
				opMode.bit.ref_cntrl				= E_IM_HDMI_REF_CNTRL_DIVIDES_1;
				opMode.bit.fbdiv1_cntrl			= E_IM_HDMI_FBDIV1_CNTRL_DIVIDES_1;
				opMode.bit.fbdiv2_cntrl			= E_IM_HDMI_FBDIV2_CNTRL_DIVIDES_1;
				opMode.bit.opmode					= E_IM_HDMI_OP_MODE_HDMI14;
				opMode.bit.tmdsmhl_cntrl			= 0;
				opMode.bit.pre_pdiv				= E_IM_HDMI_PRE_PDIV_DIVIDES_2;
			}
			else if (param3 == 1) {
				// set parameter.
				gmpCtrl							= 3;
				pllCurrCtrl.bit.mpll_int_cntrl	= 7;
				pllCurrCtrl.bit.mpll_prop_cntrl	= 7;
				opMode.bit.n_cntrl					= 3;
				opMode.bit.ref_cntrl				= E_IM_HDMI_REF_CNTRL_DIVIDES_4;
				opMode.bit.fbdiv1_cntrl			= E_IM_HDMI_FBDIV1_CNTRL_DIVIDES_4;
				opMode.bit.fbdiv2_cntrl			= E_IM_HDMI_FBDIV2_CNTRL_DIVIDES_6;
				opMode.bit.opmode					= E_IM_HDMI_OP_MODE_HDMI20;
				opMode.bit.tmdsmhl_cntrl			= 0;
				opMode.bit.pre_pdiv				= E_IM_HDMI_PRE_PDIV_DIVIDES_1;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			Im_HDMI_Set_Clock(gmpCtrl, pllCurrCtrl, opMode);
			Ddim_Print(("Im_HDMI_Set_Clock() : Normal end\n"));
			ctImHdmiPclkOn();
			ct_im_hdmi2_printf11();
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output parameter clear.
				gmpCtrl = 0;
				pllCurrCtrl.hword = 0;
				opMode.hword = 0;
			}
			else if (param3 == 1) {
				// Invalid parameter (gmpCtrl = NULL)
				ret = Im_HDMI_Get_Clock(NULL, &pllCurrCtrl, &opMode);
				Ddim_Print(("Im_HDMI_Get_Clock() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			else if (param3 == 2) {
				// Invalid parameter (pllCurrCtrl = NULL)
				ret = Im_HDMI_Get_Clock(&gmpCtrl, NULL, &opMode);
				Ddim_Print(("Im_HDMI_Get_Clock() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			else if (param3 == 3) {
				// Invalid parameter (opMode = NULL)
				ret = Im_HDMI_Get_Clock(&gmpCtrl, &pllCurrCtrl, NULL);
				Ddim_Print(("Im_HDMI_Get_Clock() : Error  err_code=0x%x\n", ret));
				// end
				return;
			} else {
				// Invalid parameter (NULL)
				ret = Im_HDMI_Get_Clock(NULL, NULL, NULL);
				Ddim_Print(("Im_HDMI_Get_Clock() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Clock(&gmpCtrl, &pllCurrCtrl, &opMode);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Clock() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("gmpCtrl      : 0x%x\n", gmpCtrl) );
				Ddim_Print( ("pllCurrCtrl : 0x%x\n", pllCurrCtrl.hword) );
				Ddim_Print( ("opMode       : 0x%x\n", opMode.hword) );
				ct_im_hdmi2_printf12();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Clock() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "term") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if ((param3 >= E_IM_HDMI_TXTERM_50OHM) && (param3 <= E_IM_HDMI_TXTERM_OPEN_CIRCUIT)) {
				// set paramter.
				txterm	= (E_IM_HDMI_TXTERM)param3;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}

			Im_HDMI_Set_Tx_Term(txterm);
			Ddim_Print(("Im_HDMI_Set_Tx_Term() : Normal end\n"));
			ctImHdmiPclkOn();
			// check register
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("register:\n") );
			Ddim_Print( ("TXTERM = 0x%x\n", IO_DISP.HDMI_TX.TXTERM.hword) );
			Ddim_Print( ("----------\n") );
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output paramter clear.
				txterm = E_IM_HDMI_TXTERM_50OHM;
			} else {
				// Invalid parameter (txterm = NULL)
				ret = Im_HDMI_Get_Tx_Term(NULL);
				Ddim_Print(("Im_HDMI_Get_Tx_Term() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Tx_Term(&txterm);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Tx_Term() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("txterm : 0x%x\n", txterm) );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("TXTERM = 0x%x\n", IO_DISP.HDMI_TX.TXTERM.hword) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Tx_Term() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "tc") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// input paramter clear.
			vlevctrl.hword = 0;
			
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// set parameter.
				cksymtxctrl.bit.Ck_symon	= D_IM_HDMI_ENABLE_OFF;
				cksymtxctrl.bit.Tx_trbon	= D_IM_HDMI_ENABLE_OFF;
				cksymtxctrl.bit.Tx_traon	= D_IM_HDMI_ENABLE_OFF;
				cksymtxctrl.bit.Tx_symon	= D_IM_HDMI_ENABLE_OFF;
				cksymtxctrl.bit.slopeboost	= E_IM_HDMI_SLOPE_BOOSTING_HDMI14_297GBPS;
				cksymtxctrl.bit.Override	= 0;
			}
			else if (param3 == 1) {
				// set parameter.
				cksymtxctrl.bit.Ck_symon	= D_IM_HDMI_ENABLE_ON;
				cksymtxctrl.bit.Tx_trbon	= D_IM_HDMI_ENABLE_ON;
				cksymtxctrl.bit.Tx_traon	= D_IM_HDMI_ENABLE_ON;
				cksymtxctrl.bit.Tx_symon	= D_IM_HDMI_ENABLE_ON;
				cksymtxctrl.bit.slopeboost	= E_IM_HDMI_SLOPE_BOOSTING_HDMI20;
				cksymtxctrl.bit.Override	= 1;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			Im_HDMI_Set_Transmitter_Control(cksymtxctrl);
			Ddim_Print(("Im_HDMI_Set_Transmitter_Control() : Normal end\n"));
			ctImHdmiPclkOn();
			// check register
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("register:\n") );
			Ddim_Print( ("CKSYMTXCTRL = 0x%x\n", IO_DISP.HDMI_TX.CKSYMTXCTRL.hword) );
			Ddim_Print( ("----------\n") );
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output parameter clear.
				vlevctrl.hword = 0;
			} else {
				// Invalid parameter (vlevctrl = NULL)
				ret = Im_HDMI_Get_Transmitter_Control(NULL);
				Ddim_Print(("Im_HDMI_Get_Transmitter_Control() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Transmitter_Control(&cksymtxctrl);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Transmitter_Control() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("cksymtxctrl : 0x%x\n", cksymtxctrl.hword) );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("CKSYMTXCTRL = 0x%x\n", IO_DISP.HDMI_TX.CKSYMTXCTRL.hword) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Transmitter_Control() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "vol") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// input parameter clear.
			vlevctrl.hword = 0;
			
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// set parameter.
				vlevctrl.bit.sup_ck_lvl	= E_IM_HDMI_SUP_LVL_HDMI2_34_6GBPS;
				vlevctrl.bit.sup_tx_lvl	= E_IM_HDMI_SUP_LVL_HDMI2_34_6GBPS;
				vlevctrl.bit.Override	= 0;
			}
			else if (param3 == 1) {
				// set parameter.
				vlevctrl.bit.sup_ck_lvl	= E_IM_HDMI_SUP_LVL_HDMI14_222GBPS;
				vlevctrl.bit.sup_tx_lvl	= E_IM_HDMI_SUP_LVL_HDMI14_222GBPS;
				vlevctrl.bit.Override	= 1;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			Im_HDMI_Set_Voltage_Level(vlevctrl);
			Ddim_Print(("Im_HDMI_Set_Voltage_Level() : Normal end\n"));
			ctImHdmiPclkOn();
			// check register
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("register:\n") );
			Ddim_Print( ("VLEVCTRL = 0x%x\n", IO_DISP.HDMI_TX.VLEVCTRL.hword) );
			Ddim_Print( ("----------\n") );
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output parameter clear.
				vlevctrl.hword = 0;
			} else {
				// Invalid parameter (vlevctrl = NULL)
				ret = Im_HDMI_Get_Voltage_Level(NULL);
				Ddim_Print(("Im_HDMI_Get_Voltage_Level() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Voltage_Level(&vlevctrl);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Voltage_Level() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("vlevctrl : 0x%x\n", vlevctrl.hword) );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("VLEVCTRL = 0x%x\n", IO_DISP.HDMI_TX.VLEVCTRL.hword) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Voltage_Level() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	
#endif

	else if ( strcmp(argv[1], "csc") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// 4th param check
				param4 = atoi((const char *)argv[4]);
				if (param4 == 0) {
					ct_im_hdmi2_printf9();
				}
				else if (param4 == 1) {
					ct_im_hdmi2_printf10();
				} else {
					// end
					Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
					return;
				}
			}
			else if (param3 == 1) {
				// Invalid parameter (config = NULL)
				ret = Im_HDMI_CSC(NULL, S_GCT_IM_HDMI_CSC_MATRIX);
				Ddim_Print(("Im_HDMI_CSC() : Error  err_code=0x%x\n", ret));
				// end
				return;
			} else {
				// Invalid parameter (matrix = NULL)
				ret = Im_HDMI_CSC(&cscConfig, NULL);
				Ddim_Print(("Im_HDMI_CSC() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_CSC(&cscConfig, S_GCT_IM_HDMI_CSC_MATRIX);
			Ddim_Print(("Im_HDMI_CSC() : Normal end\n"));
			ctImHdmiPclkOn();
			// check register
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("register:\n") );
			Ddim_Print( ("csc_cfg          = %p\n", IO_DISP.HDMI_TX.csc_cfg.byte) );
			Ddim_Print( ("csc_scale        = %p\n", IO_DISP.HDMI_TX.csc_scale.byte) );
			for (loop1 = 0; loop1 < D_IM_HDMI_CSC_CONF_ROW_NUM; loop1++) {
					Ddim_Print( ("csc_coef_a%d_msb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[0][loop1].msb) );
					Ddim_Print( ("csc_coef_a%d_lsb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[0][loop1].lsb) );
			}
			for (loop1 = 0; loop1 < D_IM_HDMI_CSC_CONF_ROW_NUM; loop1++) {
					Ddim_Print( ("csc_coef_b%d_msb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[1][loop1].msb) );
					Ddim_Print( ("csc_coef_b%d_lsb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[1][loop1].lsb) );
			}
			for (loop1 = 0; loop1 < D_IM_HDMI_CSC_CONF_ROW_NUM; loop1++) {
					Ddim_Print( ("csc_coef_c%d_msb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[2][loop1].msb) );
					Ddim_Print( ("csc_coef_c%d_lsb = 0x%x\n", loop1, IO_DISP.HDMI_TX.csc_coef[2][loop1].lsb) );
			}
			Ddim_Print( ("----------\n") );
			ctImHdmiPclkOff();
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "vs") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// set parameter.
				tx_invid0.bit.video_mapping			= E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT;
				tx_invid0.bit.internal_de_generator	= D_IM_HDMI_ENABLE_OFF;
			}
			else if (param3 == 1) {
				// set parameter.
				tx_invid0.bit.video_mapping			= E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_16BIT;
				tx_invid0.bit.internal_de_generator	= D_IM_HDMI_ENABLE_ON;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			Im_HDMI_Set_Video_Sampler(tx_invid0);
			Ddim_Print(("Im_HDMI_Set_Video_Sampler() : Normal end\n"));
			ctImHdmiPclkOn();
			// check register
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("register:\n") );
			Ddim_Print( ("tx_invid0 = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte) );
			Ddim_Print( ("----------\n") );
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output parameter clear.
				tx_invid0.byte = 0;
			} else {
				// Invalid parameter (tx_invid0 = NULL)
				ret = Im_HDMI_Get_Video_Sampler(NULL);
				Ddim_Print(("Im_HDMI_Get_Video_Sampler() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Video_Sampler(&tx_invid0);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Video_Sampler() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("tx_invid0 : 0x%x\n", tx_invid0.byte) );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("tx_invid0 = %p\n", IO_DISP.HDMI_TX.tx_invid0.byte) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Video_Sampler() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "vp") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 != 0) {
				// Invalid parameter (audio = NULL)
				ret = Im_HDMI_Set_Video_Packetizer(NULL);
				Ddim_Print(("Im_HDMI_Set_Video_Packetizer() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			// table clear.
			memset( &videoPacketizer, 0, sizeof( T_IM_HDMI_VIDEO_PACKETIZER ) );
			
			// 4th param check
			param4 = atoi((const char *)argv[4]);
			if (param4 == 0) {
				ct_im_hdmi2_printf1();
				
			}
			else if (param4 == 1) {
				ct_im_hdmi2_printf2();
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			ret = Im_HDMI_Set_Video_Packetizer(&videoPacketizer);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Set_Video_Packetizer() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi2_printf13();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Set_Video_Packetizer() : Error  err_code=0x%x\n", ret));
			}
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// table clear.
				memset( &videoPacketizer, 0, sizeof( T_IM_HDMI_VIDEO_PACKETIZER ) );
			} else {
				// Invalid parameter (videoPacketizer = NULL)
				ret = Im_HDMI_Get_Video_Packetizer(NULL);
				Ddim_Print(("Im_HDMI_Get_Video_Packetizer() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Video_Packetizer(&videoPacketizer);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Video_Packetizer() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi2_printf3();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Video_Packetizer() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "fc") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 != 0) {
				// Invalid parameter (audio = NULL)
				ret = Im_HDMI_Set_Frame_Composer(NULL);
				Ddim_Print(("Im_HDMI_Set_Frame_Composer() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			// table clear.
			memset( &frameComposer, 0, sizeof( T_IM_HDMI_FRAME_COMPOSER ) );
			
			// 4th param check
			param4 = atoi((const char *)argv[4]);
			if (param4 == 0) {
				ct_im_hdmi1_printf10();
			}
			else if (param4 == 1) {
				ct_im_hdmi1_printf11();
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			ret = Im_HDMI_Set_Frame_Composer(&frameComposer);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Set_Frame_Composer() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi1_printf12();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Set_Frame_Composer() : Error  err_code=0x%x\n", ret));
			}
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// table clear.
				memset( &frameComposer, 0, sizeof( T_IM_HDMI_FRAME_COMPOSER ) );
			} else {
				// Invalid parameter (frameComposer = NULL)
				ret = Im_HDMI_Get_Frame_Composer(NULL);
				Ddim_Print(("Im_HDMI_Get_Frame_Composer() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Frame_Composer(&frameComposer);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Frame_Composer() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi1_printf13();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Frame_Composer() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "mc") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param
			mc_flowctrl = atoi((const char *)argv[3]);
			
			ret = Im_HDMI_Set_Main_Controller(mc_flowctrl);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Set_Main_Controller() : Normal end\n"));
				ctImHdmiPclkOn();
				// check register
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("mc_flowctrl = %p\n", IO_DISP.HDMI_TX.mc_flowctrl.byte) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Set_Main_Controller() : Error  err_code=0x%x\n", ret));
			}
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// output parameter clear.
				mc_flowctrl = 0;
			} else {
				// Invalid parameter (mc_flowctrl = NULL)
				ret = Im_HDMI_Get_Main_Controller(NULL);
				Ddim_Print(("Im_HDMI_Get_Main_Controller() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Main_Controller(&mc_flowctrl);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Main_Controller() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("mc_flowctrl : 0x%x\n", mc_flowctrl) );
				Ddim_Print( ("register:\n") );
				Ddim_Print( ("mc_flowctrl = %p\n", IO_DISP.HDMI_TX.mc_flowctrl.byte) );
				Ddim_Print( ("----------\n") );
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Main_Controller() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "audio") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 != 0) {
				// Invalid parameter (audio = NULL)
				ret = Im_HDMI_Set_Audio(NULL);
				Ddim_Print(("Im_HDMI_Set_Audio() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			// table clear.
			memset( &audio, 0, sizeof( T_IM_HDMI_AUDIO ) );
			
			// 4th param check
			param4 = atoi((const char *)argv[4]);
			if (param4 == 0) {
				ct_im_hdmi2_printf4();
			}
			else if (param4 == 1) {
				ct_im_hdmi2_printf5();
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			ret = Im_HDMI_Set_Audio(&audio);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Set_Audio() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi1_printf14();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Set_Audio() : Error  err_code=0x%x\n", ret));
			}
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				// table clear.
				memset( &audio, 0, sizeof( T_IM_HDMI_AUDIO ) );
			} else {
				// Invalid parameter (audio = NULL)
				ret = Im_HDMI_Get_Audio(NULL);
				Ddim_Print(("Im_HDMI_Get_Audio() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			ret = Im_HDMI_Get_Audio(&audio);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Audio() : Normal end\n"));
				ctImHdmiPclkOn();
				ct_im_hdmi2_printf6();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Audio() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "cb") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				vpCallback = NULL;
			}
			else if (param3 == 1) {
				vpCallback = (VP_HDMI_CALLBACK)ctImHdmiCb0;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			Im_HDMI_Set_Int_Callback(vpCallback);
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	else if ( strcmp(argv[1], "mute") == 0 ) {
		// 2nd param check
		if( strcmp(argv[2], "set") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if ((param3 >= E_IM_HDMI_INT_REG_FC_STAT0) && (param3 <= E_IM_HDMI_INT_REG_I2CMPHY_STAT0)) {
				interruptRegister = (E_IM_HDMI_INT_REG)param3;
			} else {
				// end
				Ddim_Print(("!! 3rd parameter fraud : %d\n", param3));
				return;
			}
			
			// 4th param
			param4 = atoi((const char *)argv[4]);
			if ((param4 >= 0) && (param4 <= 0xFF)) {
				mute = (UCHAR)param4;
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			Im_HDMI_Set_Int_Mute(interruptRegister, mute);
			
			// check register
			Ddim_Print(("Im_HDMI_Set_Int_Mute() : Normal end\n"));
			ctImHdmiPclkOn();
			Ddim_Print( ("----------\n") );
			Ddim_Print( ("parameter:\n") );
			Ddim_Print( ("interruptRegister : %d\n", interruptRegister) );
			Ddim_Print( ("mute               : 0x%02x\n", mute) );
			ct_im_hdmi2_printf7();
			ctImHdmiPclkOff();
		}
		else if( strcmp(argv[2], "get") == 0 ) {
			// 3rd param check
			param3 = atoi((const char *)argv[3]);
			if (param3 == 0) {
				mute = 0;
			} else {
				// Invalid parameter (mute = NULL)
				interruptRegister = E_IM_HDMI_INT_REG_FC_STAT0;
				ret = Im_HDMI_Get_Int_Mute(interruptRegister, NULL);
				Ddim_Print(("Im_HDMI_Get_Int_Mute() : Error  err_code=0x%x\n", ret));
				// end
				return;
			}
			
			// 4th param check
			param4 = atoi((const char *)argv[4]);
			if ((param4 >= E_IM_HDMI_INT_REG_FC_STAT0) && (param4 <= E_IM_HDMI_INT_REG_I2CMPHY_STAT0)) {
				interruptRegister = (E_IM_HDMI_INT_REG)param4;
			} else {
				// end
				Ddim_Print(("!! 4th parameter fraud : %d\n", param4));
				return;
			}
			
			ret = Im_HDMI_Get_Int_Mute(interruptRegister, &mute);
			if (ret == D_DDIM_OK) {
				Ddim_Print(("Im_HDMI_Get_Int_Mute() : Normal end\n"));
				ctImHdmiPclkOn();
				// check get data
				Ddim_Print( ("----------\n") );
				Ddim_Print( ("result:\n") );
				Ddim_Print( ("interruptRegister : %d\n", interruptRegister) );
				Ddim_Print( ("mute               : 0x%02x\n", mute) );
				ct_im_hdmi2_printf8();
				ctImHdmiPclkOff();
			} else {
				Ddim_Print(("Im_HDMI_Get_Int_Mute() : Error  err_code=0x%x\n", ret));
			}
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud\n"));
			return;
		}
	}
	// VOID ct_im_hdmi2_main( INT32 argc, char** argv );
	else if ( strcmp(argv[1], "int") == 0 ) {
		// 2nd param check
		param2 = atoi((const char *)argv[2]);
		if (param2 == 0) {
			// set callback function.
			Im_HDMI_Set_Int_Callback(ctImHdmiCb0);
			// ih_fc_stat0 interrupt enalbe (mute calcel).
			Im_HDMI_Set_Int_Mute(E_IM_HDMI_INT_REG_FC_STAT0, 0x00);
#ifdef CO_DEBUG_ON_PC
			// set Interrupt register : ih_fc_stat0.NULL_PKT on.
			ctImHdmiPclkOn();
			IO_DISP.HDMI_TX.ih_fc_stat0.bit.NULL_PKT = 1;
			ctImHdmiPclkOff();
#endif	// CO_DEBUG_ON_PC
		} else {
			// end
			Ddim_Print(("!! 2nd parameter fraud : %d\n", param2));
			return;
		}
		
		Im_HDMI_Int_Handler();
		Ddim_Print(("Im_HDMI_Int_Handler() : Normal end\n"));
	} else {
		Ddim_Print( ("please check 1st parameter!\n") );
	}
	
	return ;
}

CtImHdmi* ct_im_hdmi_new(void)
{
	CtImHdmi* self = k_object_new_with_private(CT_TYPE_IM_HDMI, sizeof(CtImHdmiPrivate));

	return self;
}