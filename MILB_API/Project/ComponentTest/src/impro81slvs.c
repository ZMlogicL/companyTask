/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImPro81Slvs
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ctimpro1.h"
#include "impro81slvs.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro81Slvs, im_pro_8_1_slvs, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_8_1_SLVS_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro81SlvsPrivate, IM_TYPE_PRO_8_1_SLVS))
#define M_ROUNDUP_32(val)	(((kuint32)(val) +31) & 0xFFFFFFE0)
#define M_ROUNDUP_64(val)	(((kuint32)(val) +63) & 0xFFFFFFC0)


struct _ImPro81SlvsPrivate
{
};


/**
 * IMPL
 */
static void im_pro_8_1_slvs_constructor(ImPro81Slvs *self)
{
	ImPro81SlvsPrivate *priv = IM_PRO_8_1_SLVS_GET_PRIVATE(self);
	// ((AbsImProPrint*)self)->ioPro = ioPro;
}

static void im_pro_8_1_slvs_destructor(ImPro81Slvs *self)
{
	ImPro81SlvsPrivate *priv = IM_PRO_8_1_SLVS_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_8_1_slvs_common_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SLVS_Common_CB %u %u %u %lx %lx", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_normal_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SLVS_Normal_CB %u %u %u %lx %lx", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_link_err_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SLVS_Lerr_CB %u %u %u %lx %lx", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_mac_err1_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SLVS_Merr1_CB %u %u %u %lx %lx", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_mac_err2_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SLVS_Merr2_CB %u %u %u %lx %lx", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_init_combo_phy(ImPro81Slvs* self)
{
	kint32 ret = D_DDIM_OK;
	T_IM_PRO_SENTOP_CPHY_CLK_CTRL	clkCtrl[D_IM_PRO_SENTOP_CPHY_NUM] = {
		{
			.clklanesel = 0,
			.clkmodesel = 0,
			.clkoutren = 0,
			.clkoutlen = 0,
		}, {
			.clklanesel = 0,
			.clkmodesel = 0,
			.clkoutren = 0,
			.clkoutlen = 0,
		}, {
			.clklanesel = 0,
			.clkmodesel = 0,
			.clkoutren = 0,
			.clkoutlen = 0,
		}, {
			.clklanesel = 0,
			.clkmodesel = 0,
			.clkoutren = 0,
			.clkoutlen = 0,
		},
	};

	T_IM_PRO_SENTOP_CPHY_BIAS_CTRL	biasCtrl = {
		.phy0Xbgrpd = 1,
		.phy1Xbgrpd = 1,
		.phy2Xbgrpd = 0,
		.phy3Xbgrpd = 0,
	};

	T_IM_PRO_SENTOP_SLVS_CTRL		slvsCtrl = {
		.linkMode = ImproSentop_E_IM_PRO_SENTOP_SLVS_LINK_CONN_PHY0,
		.phy0Rxpdck = 1, // enable
		.phy1Rxpdck = 1, // enable
		.phy2Rxpdck = 0, // disable
		.phy3Rxpdck = 0, // disable
		.phy0Rxpclk2aen = 1, // enable
		.phy1Rxpclk2aen = 0, // disable
	};

	T_IM_PRO_SENTOP_CPHY_CTRL cphyCtrl = {
		.commonIfCtrl.pregcnt = 0xA, 	// normal (default)
		.commonIfCtrl.freqcnt = 0, 	// normal (default)
		.commonIfCtrl.pdccnt = 0, 		// normal (default)
		.commonIfCtrl.setdf = 0, 		// normal (default)
		.commonIfCtrl.picodetst = 0, 	// normal (default)
		.commonIfCtrl.pmonsel = 0, 	// normal (default)
		.commonIfCtrl.dmonsel = 0, 	// normal (default)
		.commonIfCtrl.cntsel = 0, 		// normal (default)
		.commonIfCtrl.mulgainf = 0, 	// 00 : x1(default)
		.commonIfCtrl.mulgainp = 0, 	// 00 : x1(default)
		.commonIfCtrl.cdrfunc = 0, 	// reserved
		.cpmodeCtrl[0].zerop3uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[0].zerop4uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[0].zerop5uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[0].zerop6uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[0].detcntCp0 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[0].eqEnCp0 = 0, 	// 0: disable (default)
		.cpmodeCtrl[0].eqSetCp0 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[0].zerop3uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop4uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop5uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop6uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[0].detcntCp1 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[0].eqEnCp1 = 0, 	// 0: disable (default)
		.cpmodeCtrl[0].eqSetCp1 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[0].zerop3uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop4uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop5uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[0].zerop6uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[0].detcntCp2 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[0].eqEnCp2 = 0, 	// 0: disable (default)
		.cpmodeCtrl[0].eqSetCp2 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[1].zerop3uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[1].zerop4uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[1].zerop5uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[1].zerop6uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[1].detcntCp0 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[1].eqEnCp0 = 0, 	// 0: disable (default)
		.cpmodeCtrl[1].eqSetCp0 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[1].zerop3uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop4uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop5uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop6uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[1].detcntCp1 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[1].eqEnCp1 = 0, 	// 0: disable (default)
		.cpmodeCtrl[1].eqSetCp1 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[1].zerop3uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop4uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop5uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[1].zerop6uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[1].detcntCp2 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[1].eqEnCp2 = 0, 	// 0: disable (default)
		.cpmodeCtrl[1].eqSetCp2 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[2].zerop3uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[2].zerop4uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[2].zerop5uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[2].zerop6uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[2].detcntCp0 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[2].eqEnCp0 = 0, 	// 0: disable (default)
		.cpmodeCtrl[2].eqSetCp0 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[2].zerop3uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop4uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop5uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop6uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[2].detcntCp1 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[2].eqEnCp1 = 0, 	// 0: disable (default)
		.cpmodeCtrl[2].eqSetCp1 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[2].zerop3uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop4uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop5uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[2].zerop6uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[2].detcntCp2 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[2].eqEnCp2 = 0, 	// 0: disable (default)
		.cpmodeCtrl[2].eqSetCp2 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[3].zerop3uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[3].zerop4uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[3].zerop5uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[3].zerop6uicp0 = 0, // 0: disable (default)
		.cpmodeCtrl[3].detcntCp0 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[3].eqEnCp0 = 0, 	// 0: disable (default)
		.cpmodeCtrl[3].eqSetCp0 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[3].zerop3uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop4uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop5uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop6uicp1 = 0, // 000: disable (default)
		.cpmodeCtrl[3].detcntCp1 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[3].eqEnCp1 = 0, 	// 0: disable (default)
		.cpmodeCtrl[3].eqSetCp1 = 0, 	// 000: disable (default) 
		.cpmodeCtrl[3].zerop3uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop4uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop5uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[3].zerop6uicp2 = 0, // 000: disable (default)
		.cpmodeCtrl[3].detcntCp2 = 0x72, // 0111 0010: (default) 
		.cpmodeCtrl[3].eqEnCp2 = 0, 	// 0: disable (default)
		.cpmodeCtrl[3].eqSetCp2 = 0, 	// 000: disable (default) 
		.delayCtrl[0].d0rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[0].d1rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[0].d2rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[0].d3rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[0].skwselCp0 = 0, 	// 0: disable (default) 
		.delayCtrl[0].skwselCp1 = 0, 	// 0: disable (default) 
		.delayCtrl[0].skwselCp2 = 0, 	// 0: disable (default) 
		.delayCtrl[1].d0rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[1].d1rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[1].d2rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[1].d3rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[1].skwselCp0 = 0, 	// 0: disable (default) 
		.delayCtrl[1].skwselCp1 = 0, 	// 0: disable (default) 
		.delayCtrl[1].skwselCp2 = 0, 	// 0: disable (default) 
		.delayCtrl[2].d0rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[2].d1rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[2].d2rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[2].d3rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[2].skwselCp0 = 0, 	// 0: disable (default) 
		.delayCtrl[2].skwselCp1 = 0, 	// 0: disable (default) 
		.delayCtrl[2].skwselCp2 = 0, 	// 0: disable (default) 
		.delayCtrl[3].d0rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[3].d1rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[3].d2rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[3].d3rxspeed = 0, 	// 000 : delay Line not used (default)
		.delayCtrl[3].skwselCp0 = 0, 	// 0: disable (default) 
		.delayCtrl[3].skwselCp1 = 0, 	// 0: disable (default) 
		.delayCtrl[3].skwselCp2 = 0, 	// 0: disable (default) 
		.desknewCtrl[0].rxspden = 2, 	// 2’b10 : (default).
		.desknewCtrl[0].dcntnum = 3, 	// 3’b010 : 4byte data (default)
		.desknewCtrl[0].grdwidth = 0, 	// 0 : (default)
		.desknewCtrl[0].rdwait = 0, 	// 2’b10 : (default)
		.desknewCtrl[0].vldprd = 0, 	// 2’b00 : 1 code in valid window (default)
		.desknewCtrl[1].rxspden = 2, 	// 2’b10 : (default).
		.desknewCtrl[1].dcntnum = 3, 	// 3’b010 : 4byte data (default)
		.desknewCtrl[1].grdwidth = 0, 	// 0 : (default)
		.desknewCtrl[1].rdwait = 0, 	// 2’b10 : (default)
		.desknewCtrl[1].vldprd = 0, 	// 2’b00 : 1 code in valid window (default)
		.desknewCtrl[2].rxspden = 2, 	// 2’b10 : (default).
		.desknewCtrl[2].dcntnum = 3, 	// 3’b010 : 4byte data (default)
		.desknewCtrl[2].grdwidth = 0, 	// 0 : (default)
		.desknewCtrl[2].rdwait = 0, 	// 2’b10 : (default)
		.desknewCtrl[2].vldprd = 0, 	// 2’b00 : 1 code in valid window (default)
		.desknewCtrl[3].rxspden = 2, 	// 2’b10 : (default).
		.desknewCtrl[3].dcntnum = 3, 	// 3’b010 : 4byte data (default)
		.desknewCtrl[3].grdwidth = 0, 	// 0 : (default)
		.desknewCtrl[3].rdwait = 0, 	// 2’b10 : (default)
		.desknewCtrl[3].vldprd = 0, 	// 2’b00 : 1 code in valid window (default)
		.pll0Ctrl.ibcnt = 3, 			// 011 : default
		.pll0Ctrl.ilfsel = 0, 			// 0 : normal operation(default)
		.pll0Ctrl.ioclken = 0, 			// 0 : disable(default)
		.pll0Ctrl.itxpclk2aen = 0, 		// 0 : disable
	};

	T_IM_PRO_SENTOP_CPHY_IF_EXT_SIGNAL_CTRL	extSignalCtrl[4] = {
		{
			.clksetsel = 0, 					// reserved
			.cphysetCp0 = 0, 				// reserved
			.cphysetCp1 = 0, 				// reserved
			.cphysetCp2 = 0, 				// reserved
			.funcselck = 0, 					// reserved
			.funcseld0 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld1 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld2 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld3 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
		}, {
			.clksetsel = 0, 					// reserved
			.cphysetCp0 = 0, 				// reserved
			.cphysetCp1 = 0, 				// reserved
			.cphysetCp2 = 0, 				// reserved
			.funcselck = 0, 					// reserved
			.funcseld0 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld1 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld2 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld3 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
		}, {
			.clksetsel = 0, 					// reserved
			.cphysetCp0 = 0, 				// reserved
			.cphysetCp1 = 0, 				// reserved
			.cphysetCp2 = 0, 				// reserved
			.funcselck = 0, 					// reserved
			.funcseld0 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld1 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld2 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld3 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
		}, {
			.clksetsel = 0, 					// reserved
			.cphysetCp0 = 0, 				// reserved
			.cphysetCp1 = 0, 				// reserved
			.cphysetCp2 = 0, 				// reserved
			.funcselck = 0, 					// reserved
			.funcseld0 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld1 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld2 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
			.funcseld3 = 0xA, 				// 4’b1010 : current code +/- 2code (default)
		},
	};

	T_IM_PRO_SENTOP_CPHY_SLVS_MODE_CTRL		modeCtrl[D_IM_PRO_SENTOP_CPHY_NUM] = {{{ 0 }}};

	DriverCommon_DDIM_PRINT(("init_combo_phy() start.\n"));

	//  Set I_CLKLANESEL[1:0], I_CLKMODESEL[2:0], I_CLKOUTREN, I_CLKOUTLEN to valid value.
	clkCtrl[0].clklanesel = 0;
	clkCtrl[0].clkmodesel = 0x7;
	clkCtrl[0].clkoutren = 0;
	clkCtrl[0].clkoutlen = 0;
	clkCtrl[1].clklanesel = 0;
	clkCtrl[1].clkmodesel = 0x7;
	clkCtrl[1].clkoutren = 0;
	clkCtrl[1].clkoutlen = 0;
	clkCtrl[2].clklanesel = 0;
	clkCtrl[2].clkmodesel = 0x0;
	clkCtrl[2].clkoutren = 0;
	clkCtrl[2].clkoutlen = 0;
	clkCtrl[3].clklanesel = 0;
	clkCtrl[3].clkmodesel = 0x0;
	clkCtrl[3].clkoutren = 0;
	clkCtrl[3].clkoutlen = 0;
	ret = Im_PRO_SENTOP_CPHY_Clk_Ctrl(clkCtrl);
	if(ret != D_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl(): error %u\n", ret));
	} else {
        if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clklanesel != clkCtrl[0].clklanesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy0Clklanesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clklanesel,clkCtrl[0].clklanesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkmodesel != clkCtrl[0].clkmodesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy0Clkmodesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkmodesel,clkCtrl[0].clkmodesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkoutren != clkCtrl[0].clkoutren) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy0Clkoutren (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkoutren,clkCtrl[0].clkoutren));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkoutlen != clkCtrl[0].clkoutlen) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy0Clkoutlen (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0clkctl.bit.phy0Clkoutlen,clkCtrl[0].clkoutlen));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clklanesel != clkCtrl[1].clklanesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy1Clklanesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clklanesel,clkCtrl[1].clklanesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkmodesel != clkCtrl[1].clkmodesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy1Clkmodesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkmodesel,clkCtrl[1].clkmodesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkoutren != clkCtrl[1].clkoutren) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy1Clkoutren (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkoutren,clkCtrl[1].clkoutren));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkoutlen != clkCtrl[1].clkoutlen) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy1Clkoutlen (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1clkctl.bit.phy1Clkoutlen,clkCtrl[1].clkoutlen));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clklanesel != clkCtrl[2].clklanesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy2Clklanesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clklanesel,clkCtrl[2].clklanesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkmodesel != clkCtrl[2].clkmodesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy2Clkmodesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkmodesel,clkCtrl[2].clkmodesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkoutren != clkCtrl[2].clkoutren) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy2Clkoutren (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkoutren,clkCtrl[2].clkoutren));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkoutlen != clkCtrl[2].clkoutlen) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy2Clkoutlen (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2clkctl.bit.phy2Clkoutlen,clkCtrl[2].clkoutlen));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clklanesel != clkCtrl[3].clklanesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy3Clklanesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clklanesel,clkCtrl[3].clklanesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkmodesel != clkCtrl[3].clkmodesel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy3Clkmodesel (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkmodesel,clkCtrl[3].clkmodesel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkoutren != clkCtrl[3].clkoutren) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy3Clkoutren (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkoutren,clkCtrl[3].clkoutren));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkoutlen != clkCtrl[3].clkoutlen) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Clk_Ctrl() result:phy3Clkoutlen (%d) in(%d)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3clkctl.bit.phy3Clkoutlen,clkCtrl[3].clkoutlen));
		}
    }

	// BIAS macro is startup (I_XBGRPD=1). Until BIAS macro is stable, wait 5us more then.
	ret = Im_PRO_SENTOP_CPHY_Bias_Ctrl(&biasCtrl);
	if(ret != D_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Bias_Ctrl(): error %u\n", ret));
	} else {
        if(((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy0Xbgrpd != biasCtrl.phy0Xbgrpd) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Bias_Ctrl() result:phy0Clklanesel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy0Xbgrpd,biasCtrl.phy0Xbgrpd));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy1Xbgrpd != biasCtrl.phy1Xbgrpd) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Bias_Ctrl() result:phy0Clklanesel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy1Xbgrpd,biasCtrl.phy1Xbgrpd));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy2Xbgrpd != biasCtrl.phy2Xbgrpd) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Bias_Ctrl() result:phy0Clklanesel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy2Xbgrpd,biasCtrl.phy2Xbgrpd));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy3Xbgrpd != biasCtrl.phy3Xbgrpd) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Bias_Ctrl() result:phy0Clklanesel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.biasctl.bit.phy3Xbgrpd,biasCtrl.phy3Xbgrpd));
		}
	}

	// wait 5us
	Dd_ARM_Wait_ns(5 * 1000);

	// While waiting, ComboRx Setting Signals & SLVS-EC interface signals are set to valid value 
    ret = Im_PRO_SENTOP_CPHY_Ctrl(&cphyCtrl);
    if(ret != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ctrl() min_para Error ret=0x%x\n", ret));
    } else {
        im_pro_1_1_print_1(im_pro_1_1_print_get(), "", &cphyCtrl);
    }

	modeCtrl[0].commonCtrl.bitwidthsel = 1;	// 10bit
	modeCtrl[1].commonCtrl.bitwidthsel = 1;	// 10bit
	modeCtrl[2].commonCtrl.bitwidthsel = 1;	// 10bit
	modeCtrl[3].commonCtrl.bitwidthsel = 1;	// 10bit

	// PHY0
	modeCtrl[0].commonCtrl.rxmode = 3;	// SLVS-EC 
	modeCtrl[0].commonCtrl.d0setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[0].commonCtrl.d1setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[0].commonCtrl.d2setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[0].commonCtrl.d3setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[0].pimode = 1;	// 2.3Gbps-Mode (default) 
	modeCtrl[0].picnt = 0;	// normal (default) 

	// PHY1
	modeCtrl[1].commonCtrl.rxmode = 3;	// SLVS-EC 
	modeCtrl[1].commonCtrl.d0setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[1].commonCtrl.d1setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[1].commonCtrl.d2setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[1].commonCtrl.d3setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[1].pimode = 1;	// 2.3Gbps-Mode (default) 
	modeCtrl[1].picnt = 0;	// normal (default) 

	// PHY2(dummy)
	modeCtrl[2].commonCtrl.rxmode = 0;	// PowerDown
	modeCtrl[2].commonCtrl.d0setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[2].commonCtrl.d1setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[2].commonCtrl.d2setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[2].commonCtrl.d3setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[2].pimode = 1;	// 2.3Gbps-Mode (default) 
	modeCtrl[2].picnt = 0;	// normal (default) 

	// PHY3(dummy)
	modeCtrl[2].commonCtrl.rxmode = 0;	// PowerDown
	modeCtrl[3].commonCtrl.d0setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[3].commonCtrl.d1setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[3].commonCtrl.d2setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[3].commonCtrl.d3setsel = 0;	// ComboRx be inputed Reference Clock from Image Sensor directly
	modeCtrl[3].pimode = 1;	// 2.3Gbps-Mode (default) 
	modeCtrl[3].picnt = 0;	// normal (default) 
	ret = Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl(modeCtrl);
	if(ret != D_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl(): error %u\n", ret));
	} else {
        if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Bitwidthsel != modeCtrl[0].commonCtrl.bitwidthsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0Bitwidthsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Bitwidthsel, modeCtrl[0].commonCtrl.bitwidthsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Rxmode != modeCtrl[0].commonCtrl.rxmode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0Rxmode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Rxmode, modeCtrl[0].commonCtrl.rxmode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D0setsel != modeCtrl[0].commonCtrl.d0setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0D0setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D0setsel, modeCtrl[0].commonCtrl.d0setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D1setsel != modeCtrl[0].commonCtrl.d1setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0D1setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D1setsel, modeCtrl[0].commonCtrl.d1setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D2setsel != modeCtrl[0].commonCtrl.d2setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0D2setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0D2setsel, modeCtrl[0].commonCtrl.d2setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0D3setsel != modeCtrl[0].commonCtrl.d3setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0D3setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0D3setsel, modeCtrl[0].commonCtrl.d3setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Bitwidthsel != modeCtrl[1].commonCtrl.bitwidthsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1Bitwidthsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Bitwidthsel, modeCtrl[1].commonCtrl.bitwidthsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Rxmode != modeCtrl[1].commonCtrl.rxmode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1Rxmode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Rxmode, modeCtrl[1].commonCtrl.rxmode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D0setsel != modeCtrl[1].commonCtrl.d0setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1D0setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D0setsel, modeCtrl[1].commonCtrl.d0setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D1setsel != modeCtrl[1].commonCtrl.d1setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1D1setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D1setsel, modeCtrl[1].commonCtrl.d1setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D2setsel != modeCtrl[1].commonCtrl.d2setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1D2setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1D2setsel, modeCtrl[1].commonCtrl.d2setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1D3setsel != modeCtrl[1].commonCtrl.d3setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1D3setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1D3setsel, modeCtrl[1].commonCtrl.d3setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Bitwidthsel != modeCtrl[2].commonCtrl.bitwidthsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2Bitwidthsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Bitwidthsel, modeCtrl[2].commonCtrl.bitwidthsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Rxmode != modeCtrl[2].commonCtrl.rxmode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2Rxmode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Rxmode, modeCtrl[2].commonCtrl.rxmode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D0setsel != modeCtrl[2].commonCtrl.d0setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2D0setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D0setsel, modeCtrl[2].commonCtrl.d0setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D1setsel != modeCtrl[2].commonCtrl.d1setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2D1setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D1setsel, modeCtrl[2].commonCtrl.d1setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D2setsel != modeCtrl[2].commonCtrl.d2setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2D2setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2D2setsel, modeCtrl[2].commonCtrl.d2setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2D3setsel != modeCtrl[2].commonCtrl.d3setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2D3setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2D3setsel, modeCtrl[2].commonCtrl.d3setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Bitwidthsel != modeCtrl[3].commonCtrl.bitwidthsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3Bitwidthsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Bitwidthsel, modeCtrl[3].commonCtrl.bitwidthsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Rxmode != modeCtrl[3].commonCtrl.rxmode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3Rxmode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Rxmode, modeCtrl[3].commonCtrl.rxmode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D0setsel != modeCtrl[3].commonCtrl.d0setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3D0setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D0setsel, modeCtrl[3].commonCtrl.d0setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D1setsel != modeCtrl[3].commonCtrl.d1setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3D1setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D1setsel, modeCtrl[3].commonCtrl.d1setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D2setsel != modeCtrl[3].commonCtrl.d2setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3D2setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3D2setsel, modeCtrl[3].commonCtrl.d2setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3D3setsel != modeCtrl[3].commonCtrl.d3setsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3D3setsel (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3D3setsel, modeCtrl[3].commonCtrl.d3setsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Pimode != modeCtrl[0].pimode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0Pimode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Pimode, modeCtrl[0].pimode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Picnt != modeCtrl[0].picnt) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy0Picnt (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0mdctl.bit.phy0Picnt, modeCtrl[0].picnt));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Pimode != modeCtrl[1].pimode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1Pimode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Pimode, modeCtrl[1].pimode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Picnt != modeCtrl[1].picnt) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy1Picnt (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1mdctl.bit.phy1Picnt, modeCtrl[1].picnt));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Pimode != modeCtrl[2].pimode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2Pimode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Pimode, modeCtrl[2].pimode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Picnt != modeCtrl[2].picnt) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy2Picnt (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2mdctl.bit.phy2Picnt, modeCtrl[2].picnt));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Pimode != modeCtrl[3].pimode) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3Pimode (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Pimode, modeCtrl[3].pimode));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Picnt != modeCtrl[3].picnt) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Slvs_Mode_Ctrl() result:phy3Picnt (%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3mdctl.bit.phy3Picnt, modeCtrl[3].picnt));
		}
	}

	// Extension Signals setting
	ret = Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl(extSignalCtrl);
	if(ret != D_DDIM_OK) {
		DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl(): error %u\n", ret));
	} else {
        if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0Clksetsel	!= extSignalCtrl[0].clksetsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Clksetsel	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl1.bit.phy0Clksetsel	, extSignalCtrl[0].clksetsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp0	!= extSignalCtrl[0].cphysetCp0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0CphysetCp0	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp0, extSignalCtrl[0].cphysetCp0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp1	!= extSignalCtrl[0].cphysetCp1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0CphysetCp1	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp1, extSignalCtrl[0].cphysetCp1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp2	!= extSignalCtrl[0].cphysetCp2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0CphysetCp2	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl2.bit.phy0CphysetCp2, extSignalCtrl[0].cphysetCp2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl3.bit.phy0Funcselck	!= extSignalCtrl[0].funcselck) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Funcselck	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl3.bit.phy0Funcselck	, extSignalCtrl[0].funcselck));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl4.bit.phy0Funcseld0	!= extSignalCtrl[0].funcseld0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Funcseld0	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl4.bit.phy0Funcseld0	, extSignalCtrl[0].funcseld0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl5.bit.phy0Funcseld1	!= extSignalCtrl[0].funcseld1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Funcseld1	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl5.bit.phy0Funcseld1	, extSignalCtrl[0].funcseld1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl6.bit.phy0Funcseld2	!= extSignalCtrl[0].funcseld2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Funcseld2	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl6.bit.phy0Funcseld2	, extSignalCtrl[0].funcseld2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl7.bit.phy0Funcseld3	!= extSignalCtrl[0].funcseld3) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy0Funcseld3	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy0ifctl.phy0ifctl7.bit.phy0Funcseld3	, extSignalCtrl[0].funcseld3));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1Clksetsel	!= extSignalCtrl[1].clksetsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Clksetsel	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl1.bit.phy1Clksetsel	, extSignalCtrl[1].clksetsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp0	!= extSignalCtrl[1].cphysetCp0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1CphysetCp0	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp0, extSignalCtrl[1].cphysetCp0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp1	!= extSignalCtrl[1].cphysetCp1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1CphysetCp1	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp1, extSignalCtrl[1].cphysetCp1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp2	!= extSignalCtrl[1].cphysetCp2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1CphysetCp2	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl2.bit.phy1CphysetCp2, extSignalCtrl[1].cphysetCp2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl3.bit.phy1Funcselck	!= extSignalCtrl[1].funcselck) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Funcselck	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl3.bit.phy1Funcselck	, extSignalCtrl[1].funcselck));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl4.bit.phy1Funcseld0	!= extSignalCtrl[1].funcseld0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Funcseld0	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl4.bit.phy1Funcseld0	, extSignalCtrl[1].funcseld0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl5.bit.phy1Funcseld1	!= extSignalCtrl[1].funcseld1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Funcseld1	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl5.bit.phy1Funcseld1	, extSignalCtrl[1].funcseld1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl6.bit.phy1Funcseld2	!= extSignalCtrl[1].funcseld2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Funcseld2	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl6.bit.phy1Funcseld2	, extSignalCtrl[1].funcseld2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl7.bit.phy1Funcseld3	!= extSignalCtrl[1].funcseld3) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy1Funcseld3	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy1ifctl.phy1ifctl7.bit.phy1Funcseld3	, extSignalCtrl[1].funcseld3));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2Clksetsel	!= extSignalCtrl[2].clksetsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Clksetsel	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl1.bit.phy2Clksetsel	, extSignalCtrl[2].clksetsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp0	!= extSignalCtrl[2].cphysetCp0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2CphysetCp0	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp0, extSignalCtrl[2].cphysetCp0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp1	!= extSignalCtrl[2].cphysetCp1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2CphysetCp1	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp1, extSignalCtrl[2].cphysetCp1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp2	!= extSignalCtrl[2].cphysetCp2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2CphysetCp2	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl2.bit.phy2CphysetCp2, extSignalCtrl[2].cphysetCp2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl3.bit.phy2Funcselck	!= extSignalCtrl[2].funcselck) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Funcselck	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl3.bit.phy2Funcselck	, extSignalCtrl[2].funcselck));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl4.bit.phy2Funcseld0	!= extSignalCtrl[2].funcseld0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Funcseld0	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl4.bit.phy2Funcseld0	, extSignalCtrl[2].funcseld0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl5.bit.phy2Funcseld1	!= extSignalCtrl[2].funcseld1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Funcseld1	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl5.bit.phy2Funcseld1	, extSignalCtrl[2].funcseld1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl6.bit.phy2Funcseld2	!= extSignalCtrl[2].funcseld2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Funcseld2	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl6.bit.phy2Funcseld2	, extSignalCtrl[2].funcseld2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl7.bit.phy2Funcseld3	!= extSignalCtrl[2].funcseld3) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy2Funcseld3	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy2ifctl.phy2ifctl7.bit.phy2Funcseld3	, extSignalCtrl[2].funcseld3));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3Clksetsel	!= extSignalCtrl[3].clksetsel) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Clksetsel	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl1.bit.phy3Clksetsel	, extSignalCtrl[3].clksetsel));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp0	!= extSignalCtrl[3].cphysetCp0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3CphysetCp0	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp0, extSignalCtrl[3].cphysetCp0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp1	!= extSignalCtrl[3].cphysetCp1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3CphysetCp1	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp1, extSignalCtrl[3].cphysetCp1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp2	!= extSignalCtrl[3].cphysetCp2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3CphysetCp2	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl2.bit.phy3CphysetCp2, extSignalCtrl[3].cphysetCp2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl3.bit.phy3Funcselck	!= extSignalCtrl[3].funcselck) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Funcselck	(%u) in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl3.bit.phy3Funcselck	, extSignalCtrl[3].funcselck));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl4.bit.phy3Funcseld0	!= extSignalCtrl[3].funcseld0) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Funcseld0	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl4.bit.phy3Funcseld0	, extSignalCtrl[3].funcseld0));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl5.bit.phy3Funcseld1	!= extSignalCtrl[3].funcseld1) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Funcseld1	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl5.bit.phy3Funcseld1	, extSignalCtrl[3].funcseld1));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl6.bit.phy3Funcseld2	!= extSignalCtrl[3].funcseld2) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Funcseld2	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl6.bit.phy3Funcseld2	, extSignalCtrl[3].funcseld2));
		}
		
	    if(((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl7.bit.phy3Funcseld3	!= extSignalCtrl[3].funcseld3) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Ext_Signal_Ctrl() result:phy3Funcseld3	(%lu)in(%u)\n", 
			((AbsImProPrint*)self)->ioPro->sen.sentop.phy3ifctl.phy3ifctl7.bit.phy3Funcseld3	, extSignalCtrl[3].funcseld3));
		}
	}

	// Waiting 200us or more until PLL is lockup
	ret = Im_PRO_SENTOP_SLVS_Ctrl(&slvsCtrl);
    if(ret != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_SLVS_Ctrl() Error ret=0x%x\n", ret));
        return;
    } else {
        im_pro_1_0_print_9(im_pro_1_0_print_get(), "", &slvsCtrl);
    }

    Im_PRO_SLVS_Pma_Pll_Power_Down(E_IM_PRO_SLVS_PD_STATE_NORMAL);

	// wait 200us
	Dd_ARM_Wait_ns(200 * 1000);

	DriverCommon_DDIM_PRINT(("init_combo_phy() end.\n"));
}

void im_pro_8_1_slvs_mode_change(ImPro81Slvs* self)
{
	kint32					ercd;
	T_IM_PRO_SLVS_CTRL		slvsCtrl;
	T_IM_PRO_SLVS_MODE_CFG	modeCtrl;
	T_IM_PRO_SLVS_TRIM_CFG	trimCtrl;
	T_IM_PRO_INT_CFG		intCfg;
	TImProCallbackCfg	callbackCfg;
	T_IM_PRO_SLVS_PMA_PD	pmaPd;

	DriverCommon_DDIM_PRINT(("mode_change_slvs() start.\n"));
	for(E_IM_PRO_SLVS_STREAM_TYPE type = E_IM_PRO_SLVS_STREAM_TYPE_A; type < E_IM_PRO_SLVS_STREAM_TYPE_BOTH; type++) {
		slvsCtrl.ramPdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		slvsCtrl.vdoutCtrl = E_IM_PRO_SLVS_VDOUT_CTRL_OUTPUT;
		slvsCtrl.ecccrcOpt = E_IM_PRO_SLVS_ECCCRC_OPT_WO_ECC_CRC;
		slvsCtrl.expectVal = E_IM_PRO_SLVS_EXPECT_VAL_H_0000;
		ercd = Im_PRO_SLVS_Ctrl(type, &slvsCtrl);
		if(ercd != DdimUserCustom_E_OK) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Ctrl() Error ercd=0x%x\n", ercd));
		} else {
			im_pro_1_2_print_3(im_pro_1_2_print_get(), "", type, &slvsCtrl);
		}

		modeCtrl.pixelbit = E_IM_PRO_SLVS_PIXEL_BIT_10BIT;
		modeCtrl.lanenum = E_IM_PRO_SLVS_LANE_NUM_8LANE;
		modeCtrl.linelength = 4200;
		modeCtrl.outputFormat = E_IM_PRO_SLVS_OUT_FORMAT_8POINT;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_0;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_1] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_1;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_2] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_2;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_3] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_3;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_4] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_4;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_5] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_5;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_6] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_6;
		modeCtrl.swapLane[E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7] = E_IM_PRO_SLVS_LANE_SWAP_INPUT_PORT_SEL_7;
		modeCtrl.validLane.lane0 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane1 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane2 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane3 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane4 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane5 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane6 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		modeCtrl.validLane.lane7 = E_IM_PRO_SLVS_LANE_ENABLE_EN;
		ercd = Im_PRO_SLVS_Mode_Cfg(type, &modeCtrl);
		if(ercd != DdimUserCustom_E_OK) {
			DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Mode_Cfg() Error ercd=0x%x\n", ercd));
		} else {
			im_pro_1_2_print_4(im_pro_1_2_print_get(), "", type, &modeCtrl);
		}

		trimCtrl.enabled = FALSE;
		trimCtrl.startX = 0;
		trimCtrl.width = 0;
		ercd = Im_PRO_SLVS_Trim_Cfg(type, &trimCtrl);
        if(ercd != DdimUserCustom_E_OK) {
            DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Trim_Cfg() Error ercd=0x%x\n", ercd));
        } else {
            im_pro_1_2_print_5(im_pro_1_2_print_get(), "", type, &trimCtrl);
        }

		Im_PRO_SLVS_Update_Cfg(E_IM_PRO_SLVS_STREAM_TYPE_A);

		intCfg.permissionFlg = 1;
		intCfg.interruptBit = (	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE7_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE6_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE5_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE4_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE7_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE6_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE5_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE4_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE7_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE6_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE5_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE4_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2_BIT |
								D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1_BIT | D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0_BIT	);
		Im_PRO_SLVS_Set_Common_Interrupt(&intCfg);

		intCfg.interruptBit = (	D_IM_PRO_SLVS_INTST_FSI_BIT	 | D_IM_PRO_SLVS_INTST_FSO_BIT	 |
								D_IM_PRO_SLVS_INTST_FEI_BIT	 | D_IM_PRO_SLVS_INTST_FEO_BIT	 |
								D_IM_PRO_SLVS_INTST_RDY_BIT	 | D_IM_PRO_SLVS_INTST_STBY_BIT	);
		Im_PRO_SLVS_Set_Interrupt(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &intCfg);

		intCfg.interruptBit = (	D_IM_PRO_SLVS_LEINTST_LBOVF_BIT	 | D_IM_PRO_SLVS_LEINTST_LNE_BIT	 |
								D_IM_PRO_SLVS_LEINTST_ECCE_BIT	 | D_IM_PRO_SLVS_LEINTST_ECC2C_BIT	 |
								D_IM_PRO_SLVS_LEINTST_ECC1C_BIT	 | D_IM_PRO_SLVS_LEINTST_HCRCE_BIT	 |
								D_IM_PRO_SLVS_LEINTST_HCRC2C_BIT | D_IM_PRO_SLVS_LEINTST_HCRC1C_BIT |
								D_IM_PRO_SLVS_LEINTST_PCRCE_BIT	 | D_IM_PRO_SLVS_LEINTST_LLE_BIT		);
		Im_PRO_SLVS_Set_Interrupt(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, &intCfg);

		intCfg.interruptBit = (	D_IM_PRO_SLVS_MEINTST0_DSD_BIT | D_IM_PRO_SLVS_MEINTST0_DCL_BIT |
								D_IM_PRO_SLVS_MEINTST0_SCL_BIT | D_IM_PRO_SLVS_MEINTST0_ECL_BIT	);
		Im_PRO_SLVS_Set_Interrupt(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, &intCfg);

		intCfg.interruptBit = (	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE7_BIT | D_IM_PRO_SLVS_MEINTST1_FUNF_LANE6_BIT |
								D_IM_PRO_SLVS_MEINTST1_FUNF_LANE5_BIT | D_IM_PRO_SLVS_MEINTST1_FUNF_LANE4_BIT |
								D_IM_PRO_SLVS_MEINTST1_FUNF_LANE3_BIT | D_IM_PRO_SLVS_MEINTST1_FUNF_LANE2_BIT |
								D_IM_PRO_SLVS_MEINTST1_FUNF_LANE1_BIT | D_IM_PRO_SLVS_MEINTST1_FUNF_LANE0_BIT |
								D_IM_PRO_SLVS_MEINTST1_FOVF_LANE7_BIT | D_IM_PRO_SLVS_MEINTST1_FOVF_LANE6_BIT |
								D_IM_PRO_SLVS_MEINTST1_FOVF_LANE5_BIT | D_IM_PRO_SLVS_MEINTST1_FOVF_LANE4_BIT |
								D_IM_PRO_SLVS_MEINTST1_FOVF_LANE3_BIT | D_IM_PRO_SLVS_MEINTST1_FOVF_LANE2_BIT |
								D_IM_PRO_SLVS_MEINTST1_FOVF_LANE1_BIT | D_IM_PRO_SLVS_MEINTST1_FOVF_LANE0_BIT	);
		Im_PRO_SLVS_Set_Interrupt(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, &intCfg);

		callbackCfg.inthandler = im_pro_8_1_slvs_common_cb;
		callbackCfg.userParam = 0;	// tentative
		Im_PRO_SLVS_Set_Common_Int_Handler(&callbackCfg);

		callbackCfg.inthandler = im_pro_8_1_slvs_normal_cb;
		Im_PRO_SLVS_Set_Int_Handler(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_INTN_O, &callbackCfg);

		callbackCfg.inthandler = im_pro_8_1_slvs_link_err_cb;
		Im_PRO_SLVS_Set_Int_Handler(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_LINK_ERR, &callbackCfg);

		callbackCfg.inthandler = im_pro_8_1_slvs_mac_err1_cb;
		Im_PRO_SLVS_Set_Int_Handler(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1, &callbackCfg);

		callbackCfg.inthandler = im_pro_8_1_slvs_mac_err2_cb;
		Im_PRO_SLVS_Set_Int_Handler(E_IM_PRO_SLVS_STREAM_TYPE_A, E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2, &callbackCfg);

		pmaPd.lane0PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane1PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane2PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane3PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane4PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane5PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane6PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		pmaPd.lane7PdState = E_IM_PRO_SLVS_PD_STATE_NORMAL;
		ercd = Im_PRO_SLVS_Pma_Power_Down(&pmaPd);
        if(ercd != DdimUserCustom_E_OK) {
            DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Power_Down() Error ercd=0x%x\n", ercd));
        } else {
            im_pro_1_2_print_1(im_pro_1_2_print_get(), "", &pmaPd);
        }
	}
	DriverCommon_DDIM_PRINT(("mode_change_slvs() end.\n"));
}

void im_pro_8_1_slvs_init(ImPro81Slvs* self)
{
	kint32						ercd;
	T_IM_PRO_SLVS_PMA_INIT		pmaInit;
	T_IM_PRO_SLVS_COMMON_CFG	commonCfg;

	DriverCommon_DDIM_PRINT(("init_slvs() start.\n"));
	pmaInit.invertSel.lane0 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane1 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane2 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane3 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane4 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane5 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane6 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;
	pmaInit.invertSel.lane7 = E_IM_PRO_SLVS_INPUT_DATA_INVERSION_NORMAL;

	pmaInit.multiplicationFactor = E_IM_PRO_SLVS_MULTIPLICATION_FACTOR_REF_CLK_72MHZ;

	pmaInit.optInitParam.enabled = FALSE;
	pmaInit.optInitParam.refsel = 0x0;
	pmaInit.optInitParam.icpcode = 0x3;
	ercd = Im_PRO_SLVS_Pma_Init(&pmaInit);
	if(ercd != DdimUserCustom_E_OK) {
		DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Pma_Init() min_para Error ercd=0x%x\n", ercd));
	} else {
		im_pro_1_2_print_0(im_pro_1_2_print_get(), "", &pmaInit);
	}

#if 1	// D code
	commonCfg.StandbyLength = 0x20;
	commonCfg.StandbySymbolType = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;	// tentative
	commonCfg.StandbySymbol = 0x03;								// tentative D03.0

	commonCfg.DeskewInterval = 0x14;
	commonCfg.DeskewLength = 0x10;
	commonCfg.DeskewSymbolType = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;	// tentative
	commonCfg.DeskewSymbol = 0x60;								// tentative D00.3
#else // K Code
	commonCfg.StandbyLength = 0x20;
	commonCfg.StandbySymbolType = E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE;	// tentative
	commonCfg.StandbySymbol = 0xBC;								// tentative K28.5

	commonCfg.DeskewInterval = 0x14;
	commonCfg.DeskewLength = 0x10;
	commonCfg.DeskewSymbolType = E_IM_PRO_SLVS_SYMBOL_TYPE_K_CODE;
	commonCfg.DeskewSymbol = 0xBC;	// K28.5
#endif

	commonCfg.IdleSymbolType0 = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;
	commonCfg.IdleSymbol0 = 0x00;	// D.00.0
	commonCfg.IdleSymbolType1 = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;
	commonCfg.IdleSymbol1 = 0x00;	// D.00.0
	commonCfg.IdleSymbolType2 = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;
	commonCfg.IdleSymbol2 = 0x00;	// D.00.0
	commonCfg.IdleSymbolType3 = E_IM_PRO_SLVS_SYMBOL_TYPE_DATA;
	commonCfg.IdleSymbol3 = 0x00;	// D.00.0
	ercd = Im_PRO_SLVS_Common_Cfg(&commonCfg);
    if(ercd != DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(("Im_PRO_SLVS_Common_Cfg() min_para Error ercd=0x%x\n", ercd));
    } else {
        im_pro_1_2_print_2(im_pro_1_2_print_get(), "", &commonCfg);
    }

	im_pro_8_1_slvs_mode_change(NULL);

	Im_PRO_SLVS_SR_Rlease(E_IM_PRO_SLVS_STREAM_TYPE_A);

	DriverCommon_DDIM_PRINT(("init_slvs() end.\n"));
}

void im_pro_8_1_slvs_raw_output(ImPro81Slvs* self)
{
	E_IM_PRO_P2M_CH		p2mOddCh = E_IM_PRO_P2M_CH0;
	E_IM_PRO_P2M_CH		p2mEvenCh = E_IM_PRO_P2M_CH1;
	E_IM_PRO_PWCH		pwchOddCh = E_IM_PRO_PWCH_0;
	E_IM_PRO_PWCH		pwchEvenCh = E_IM_PRO_PWCH_1;
	T_IM_PRO_P2M_CTRL	p2mCtrl;
	T_IM_PRO_PWCH_CTRL	pwchCtrl;
	kulong				lineFeed;
	T_IM_PRO_PWCH_INFO pwchInfo = {
		.bufferNum = 1,
		.buffAddr[0] = 0x58000000,
	};
	T_IM_PRO_INT_CFG intCfg = {
		.interruptBit = (D_IM_PRO_PWCHINTENB_PWE | D_IM_PRO_PWCHINTENB_PWEE | D_IM_PRO_PWCHINTENB_PWXE),
		.permissionFlg = 1,
	};
	TImProCallbackCfg callbackCfg = {
		.inthandler = im_pro_8_1_slvs_pwch_cb,
		.userParam = 0,
	};

	DriverCommon_DDIM_PRINT(("raw_output() start.\n"));

	// P2M
	p2mCtrl.kneeEnable = E_IM_PRO_P2M_KNEE_DIS;
	p2mCtrl.lpfMode = E_IM_PRO_P2M_LPF_MODE_OFF;

	p2mCtrl.startY = 18 >> 1;
	p2mCtrl.height = 2160 >> 1;
	p2mCtrl.startX = 26;
	p2mCtrl.width = (4152 >> 1) - p2mCtrl.startX;
	p2mCtrl.recMode = E_IM_PRO_P2M_REC_MODE_12BIT;
	lineFeed = M_ROUNDUP_64(4096 * 3);

	p2mCtrl.shiftValue = 0;
	p2mCtrl.shiftBit = E_IM_PRO_P2M_SHIFT_0BIT;
	p2mCtrl.clipValue = 0;
	p2mCtrl.verticalThin = 1;
	p2mCtrl.horizonThin = 1;
	p2mCtrl.sampleLine = 0x8000000000000000;
	p2mCtrl.sampleWidth = 0x8000000000000000;
	p2mCtrl.enableMirror = 0;
	p2mCtrl.inputMode = E_IM_PRO_P2M_INPUT_MODE_1POINT;

	// PWCH
	pwchCtrl.transTo = E_IM_PRO_PWCH_TRANS_IO_0;
	pwchCtrl.reqThreshold = E_IM_PRO_PWCH_CNT_NOLIMIT;
	pwchCtrl.writeMask = E_IM_PRO_PWCH_WRITE_MASK_EN;
	pwchCtrl.outputFormat = E_IM_PRO_PWCH_OUTPUT_FORMAT_NORMAL;

	p2mOddCh = E_IM_PRO_P2M_CH0;
	p2mEvenCh = E_IM_PRO_P2M_CH1;
	pwchOddCh = E_IM_PRO_PWCH_0;
	pwchEvenCh = E_IM_PRO_PWCH_1;

	Im_PRO_P2M_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh,  &p2mCtrl);
	Im_PRO_PWch_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &pwchCtrl);
	Im_PRO_PWch_Set_LineFeed(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  lineFeed);

	Im_PRO_P2M_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh, &p2mCtrl);
	Im_PRO_PWch_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &pwchCtrl);
	Im_PRO_PWch_Set_LineFeed(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, lineFeed);

	Im_PRO_PWch_Set_Buf_Addr(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh, &pwchInfo);
	pwchInfo.buffAddr[0] += lineFeed;
	Im_PRO_PWch_Set_Buf_Addr(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &pwchInfo);

	Im_PRO_PWch_Set_Interrupt(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &intCfg);
	Im_PRO_PWch_Set_Interrupt(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &intCfg);
	Im_PRO_PWch_Set_Int_Handler(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &callbackCfg);
	Im_PRO_PWch_Set_Int_Handler(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &callbackCfg);

	p2mOddCh = E_IM_PRO_P2M_CH2;
	p2mEvenCh = E_IM_PRO_P2M_CH3;
	pwchOddCh = E_IM_PRO_PWCH_2;
	pwchEvenCh = E_IM_PRO_PWCH_3;

	p2mCtrl.startX = 0;
	Im_PRO_P2M_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh,  &p2mCtrl);
	Im_PRO_PWch_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &pwchCtrl);
	Im_PRO_PWch_Set_LineFeed(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  lineFeed);

	Im_PRO_P2M_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh, &p2mCtrl);
	Im_PRO_PWch_Ctrl(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &pwchCtrl);
	Im_PRO_PWch_Set_LineFeed(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, lineFeed);

	pwchInfo.buffAddr[0] += M_ROUNDUP_64(p2mCtrl.width * 3);
	Im_PRO_PWch_Set_Buf_Addr(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh, &pwchInfo);
	pwchInfo.buffAddr[0] += lineFeed;
	Im_PRO_PWch_Set_Buf_Addr(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &pwchInfo);

	Im_PRO_PWch_Set_Interrupt(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &intCfg);
	Im_PRO_PWch_Set_Interrupt(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &intCfg);
	Im_PRO_PWch_Set_Int_Handler(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh,  &callbackCfg);
	Im_PRO_PWch_Set_Int_Handler(E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh, &callbackCfg);

	DriverCommon_DDIM_PRINT(("raw_output() end.\n"));
}

void im_pro_8_1_slvs_sen_vd_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("SEN_VD_CB %u %u %u %lx %lx\n", id->unitNo, id->blockType, id->channel, result, userParam));
}

void im_pro_8_1_slvs_pwch_cb(T_CALLBACK_ID* id, kulong result, kulong userParam)
{
	DriverCommon_DDIM_PRINT(("PWCH_CB %u %u %u %lx %lx\n", id->unitNo, id->blockType, id->channel, result, userParam));

	Im_PRO_PWch_Stop(id->unitNo, id->blockType, id->channel, 0);
	Im_PRO_P2M_Stop(id->unitNo, id->blockType, id->channel, 0);
	Im_PRO_P2M_Set_PAEN(id->unitNo, id->blockType, id->channel, 0);
}
#endif

ImPro81Slvs* im_pro_8_1_slvs_new(void)
{
	ImPro81Slvs* self = k_object_new_with_private(IM_TYPE_PRO_8_1_SLVS, sizeof(ImPro81SlvsPrivate));

	return self;
}

ImPro81Slvs* im_pro_8_1_slvs_get(void)
{
	static ImPro81Slvs* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_8_1_SLVS, sizeof(ImPro81SlvsPrivate));
	}

	return self;
}
