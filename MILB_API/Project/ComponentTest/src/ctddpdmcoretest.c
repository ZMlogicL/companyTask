/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :guguangjian
*@brief               :CtDdPdmCoretest类
*@rely                :klib
*@function
*1.0.0 2020年09月开始开发
*设计的主要功能:
*1、
*@version
*
*/

#include <string.h>
#include <stdlib.h>
#include "pdm.h"
#include "dd_pdm.h"
#include "ct_dd_pdm.h"
#include "dd_top.h"
#include "dd_cache.h"
#include "dd_gic.h"
#include "dd_audio.h"
#include "dd_hdmac0.h"
#include "peripheral.h"
#include "ctddpdmmain.h"
#include "ctddpdmcoretest.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPdmCoretest, ct_dd_pdm_coretest);
#define CT_DD_PDM_CORETEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPdmCoretestPrivate,CT_TYPE_DD_PDM_CORETEST))

struct _CtDdPdmCoretestPrivate
{
	kint a;
};

static void ct_dd_pdm_coretest_constructor(CtDdPdmCoretest *self) 
{
	self->test = NULL;
}

static void ct_dd_pdm_coretest_destructor(CtDdPdmCoretest *self) 
{
	self->test = NULL;
}

/*
 *PUBLIC
 */
void ct_dd_pdm_coretest_set_test(CtDdPdmCoretest *self,CtDdPdmOthertest *test)
{
	self->test = test;
}

void ct_dd_pdm_coretest_ctrl(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e1(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = (E_DD_PDM_CORE_LR_SWAP)2;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e2(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = (E_DD_PDM_CORE_PGA)16;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e3(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = (E_DD_PDM_CORE_PGA)16;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e4(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 32;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e5(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 64;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e6(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = 2;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e7(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);
	
	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	coreCfg.s_cycle = (E_DD_PDM_CORE_S_CYCLE)8;
	coreCfg.soft_mute = D_DD_PDM_ENABLE;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e8(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);

	coreCfg.swap = E_DD_PDM_CORE_LR_SWAP_SWAP;
	coreCfg.pga_r = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.pga_l = E_DD_PDM_CORE_PGA_P_10_5_DB;
	coreCfg.mclk_div = 12;
	coreCfg.sinc_rate = 48;
	coreCfg.adc_hpd = D_DD_PDM_ENABLE;
	coreCfg.hp_cutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.s_cycle = E_DD_PDM_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.soft_mute = 2;
	
	result = Dd_Pdm_Ctrl_Core(self->test->ch, &coreCfg);
	
	if (self->test->ch <= 1){
		Ddim_Print(("LRSWAP=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.LRSWAP));
		Ddim_Print(("PGA_R=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_R));
		Ddim_Print(("PGA_L=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.PGA_L));
		Ddim_Print(("MCLKDIV=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.MCLKDIV));
		Ddim_Print(("SINC_RATE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SINC_RATE));
		Ddim_Print(("ADCHPD=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.ADCHPD));
		Ddim_Print(("HPCUTOFF=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.HPCUTOFF));
		Ddim_Print(("S_CYCLES=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.S_CYCLES));
		Ddim_Print(("SOFT_MUTE=%d\n", IO_PDM[self->test->ch].CORE_CFG.bit.SOFT_MUTE));
	}
	
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_ctrl_e9(CtDdPdmCoretest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	result = Dd_Pdm_Ctrl_Core(self->test->ch, NULL);
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_get_ctrl(CtDdPdmCoretest *self)
{
	kint32 result;
	T_DD_PDM_CORE_CFG coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	ct_dd_pdm_main_reg_init();
	Dd_Pdm_Init();

	result = Dd_Pdm_Get_Ctrl_Core(self->test->ch, &coreCfg);
	
	Ddim_Print(("swap=0x%x\n", coreCfg.swap));
	Ddim_Print(("pga_r=0x%x\n", coreCfg.pga_r));
	Ddim_Print(("pga_l=0x%x\n", coreCfg.pga_l));
	Ddim_Print(("mclk_div=0x%x\n", coreCfg.mclk_div));
	Ddim_Print(("sinc_rate=0x%x\n", coreCfg.sinc_rate));
	Ddim_Print(("adc_hpd=0x%x\n", coreCfg.adc_hpd));
	Ddim_Print(("hp_cutoff=0x%x\n", coreCfg.hp_cutoff));
	Ddim_Print(("s_cycle=0x%x\n", coreCfg.s_cycle));
	Ddim_Print(("soft_mute=0x%x\n", coreCfg.soft_mute));
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_get_ctrl_e1(CtDdPdmCoretest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	result = Dd_Pdm_Get_Ctrl_Core(self->test->ch, NULL);
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

CtDdPdmCoretest* ct_dd_pdm_coretest_new(void) 
{
    CtDdPdmCoretest *self = k_object_new_with_private(CT_TYPE_DD_PDM_CORETEST, sizeof(CtDdPdmCoretestPrivate));
    return self;
}
