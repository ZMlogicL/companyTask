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
// #include "dd_pdm.h"
#include "ct_dd_pdm.h"
// #include "dd_top.h"
// #include "dd_cache.h"
// #include "dd_gic.h"
// #include "dd_audio.h"
// #include "dd_hdmac0.h"
#include "../../DeviceDriver/Peripheral/src/ddpdm.h"
#include "../../DeviceDriver/Peripheral/src/ddaudio.h"
#include "../../DeviceDriver/Peripheral/src/ddhdmac0.h"
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = (PdmCoreLrSwap)2;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = (PdmCorePga)16;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = (PdmCorePga)16;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 32;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 64;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = 2;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	coreCfg.sCycle = (PdmCoreSCycle)8;
	coreCfg.softMute = DdAudio_ENABLE;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	
	dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);

	coreCfg.swap = DdPdm_CORE_LR_SWAP_SWAP;
	coreCfg.pgaR = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.pgaL = DdPdm_CORE_PGA_P_10_5_DB;
	coreCfg.mclkDiv = 12;
	coreCfg.sincRate = 48;
	coreCfg.adcHpd = DdAudio_ENABLE;
	coreCfg.hpCutoff = 2;
	
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	coreCfg.sCycle = E_DD_PDM_CORE_S_CYCLE_1000US;
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	coreCfg.sCycle = DdPdm_CORE_S_CYCLE_5;
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	coreCfg.softMute = 2;
	
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
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
	result = dd_pdm_ctrl_core(dd_pdm_get(),self->test->ch, NULL);
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_get_ctrl(CtDdPdmCoretest *self)
{
	kint32 result;
	DdPdmCoreCfg coreCfg;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	ct_dd_pdm_main_reg_init();
	dd_pdm_init(dd_pdm_get());

	result = dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, &coreCfg);
	
	Ddim_Print(("swap=0x%x\n", coreCfg.swap));
	Ddim_Print(("pgaR=0x%x\n", coreCfg.pgaR));
	Ddim_Print(("pgaL=0x%x\n", coreCfg.pgaL));
	Ddim_Print(("mclkDiv=0x%x\n", coreCfg.mclkDiv));
	Ddim_Print(("sincRate=0x%x\n", coreCfg.sincRate));
	Ddim_Print(("adcHpd=0x%x\n", coreCfg.adcHpd));
	Ddim_Print(("hpCutoff=0x%x\n", coreCfg.hpCutoff));
	Ddim_Print(("sCycle=0x%x\n", coreCfg.sCycle));
	Ddim_Print(("softMute=0x%x\n", coreCfg.softMute));
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

void ct_dd_pdm_coretest_get_ctrl_e1(CtDdPdmCoretest *self)
{
	kint32 result;
	
	Ddim_Print(( "<%s> Start\n", __FUNCTION__ ));
	result = dd_pdm_get_ctrl_core(dd_pdm_get(),self->test->ch, NULL);
	Ddim_Print(("<%s> End. result=0x%x, self->test->ch=%d\n", __FUNCTION__, result, self->test->ch));
}

CtDdPdmCoretest* ct_dd_pdm_coretest_new(void) 
{
    CtDdPdmCoretest *self = k_object_new_with_private(CT_TYPE_DD_PDM_CORETEST, sizeof(CtDdPdmCoretestPrivate));
    return self;
}
