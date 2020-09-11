/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h> 
#include <ImageMacro/src/imelacore.h>
#include <ImageMacro/src/imelareg.h>
#include <ImageMacro/src/imela.h>
#include "jdsela.h"
#include "im_ela.h"
#include "driver_common.h"
#include "dd_top.h"
#include "ctimela.h"
#include "ctimela1.h"
#include "ctimela2.h"
#include "ctimela3.h"
#include "ctimela4.h"
#include "ctimela5.h"
#include "ctimela6.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImEla, ct_im_ela);
#define CT_IM_ELA_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImElaPrivate,CT_TYPE_IM_ELA))

#define	CtImEla_D_IM_ELA_S_SYNC_SEL_SYNC							(0)		/* SYNC				*/
#define	CtImEla_D_IM_ELA_S_SYNC_SEL_ASYNC_CALLBACK		(1)		/* ASYNC Callback	*/
#define	CtImEla_D_IM_ELA_S_SYNC_SEL_ASYNC_WAIT				(2)		/* ASYNC Wait End	*/
#define	CtImEla_D_IM_ELA_S_SYNC_SEL_UNKNOWN				(3)		/* Unknown			*/
#define	CtImEla_CT_IM_ELA_SET_TEST_DATA
//#define	CT_IM_ELA_MSG_PRINT_ON

struct _CtImElaPrivate
{
	CtImEla1* ela1;
	CtImEla2* ela2;
	CtImEla3* ela3;
	CtImEla4* ela4;
	CtImEla5* ela5;
	CtImEla6* ela6;
	ImElaReg* elareg;
	DdimUserCustom* usercustom;
	ImElaCore* elacore;
	ImEla* imela;
};

/* Execution watch flag of ELA */
#ifdef CO_ACT_PCLOCK
// PCLK_ELA setting task counter (0~255)
static kuchar S_GCT_IM_ELA_PCLK_COUNTER = 0;
#endif //CO_ACT_PCLOCK

#ifdef CO_ACT_ICLOCK
static kuchar S_GIM_ELA_CLK_COUNTER;
static kuchar S_GIM_ELA_ICLK_COUNTER;
#endif //CO_ACT_ICLOCK

#ifdef ELA_TEST
static	SYSTIME S_SYS_TIME = {0};
#endif

#if 0
static kuchar		ctImElaCnvParam2Syncsel(kuchar p_sync);
static kuint32		ctImElaCnvParam2Deknee(kuchar p_deknee, kuchar* deknee_enable);
static kuint32		ctImElaCnvParam2TopOffset(kuchar p_top_offset, kuchar p_dtype, kuchar* top_offset);
static kuint32		ctImElaCnvParam2Size(kuchar p_size, kushort* hsize);
static kuint32		ctImElaCnvParam2NoiseOffset(kuchar p_offset);
static kuint32		ctImElaCnvParam2NoiseGain(kuchar p_gain);
static kuint32		ctImElaCnvParam2NoiseBorder(kuchar p_border);
static kuint32		ctImElaCnvParam2NoiseThreshOffset(kuchar p_offset);
static kuint32		ctImElaCnvParam2NoiseThreshGain(kuchar p_gain);
static kuint32		ctImElaCnvParam2NoiseThreshLowHi(kuchar p_low_hi);
static kuint32		ctImElaCnvParam2NoiseAlphaLimit(kuchar p_alpha_limit);
static kuint32		ctImElaCnvParam2NoiseLimit(kuchar p_limit);
static kuint32		ctImElaStart(kuchar p_sync);
/* Callback Function	*/
static void			ctImElaEndCallback(void);
#endif

static void 		ctImElaEachRegPrint(CtImEla *self);
static void 		ctImElaInterruptRegPrint(CtImEla *self);
static void 		ctImElaCtrlRegPrint(CtImEla *self);
static void 		ctImElaCoreRegPrint(CtImEla *self);
static void 		ctImElaCurtailBayerTblPrint(CtImEla *self);
static void 		ctImElaExtractNoiseTblPrint(CtImEla *self);
static void 		ctImElaOnPclk(CtImEla *self);
static void 		ctImElaOffPclk(CtImEla *self);

static void ct_im_ela_constructor(CtImEla *self) 
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);
	
	priv->ela1 = ct_im_ela1_new();
	priv->ela2 = ct_im_ela2_new();
	priv->ela3 = ct_im_ela3_new();
	priv->ela4 = ct_im_ela4_new();
	priv->ela5 = ct_im_ela5_new();
	priv->ela6 = ct_im_ela6_new();	
	priv->elareg = im_ela_reg_new();
	priv->usercustom = ddim_user_custom_new();
	priv->elacore =  im_ela_core_new();
	priv->imela = im_ela_get();			
}

static void ct_im_ela_destructor(CtImEla *self) 
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);

	if(priv->ela1 != NULL)
	{
		k_object_unref(priv->ela1);
		priv->ela1 = NULL;		
	}	
	if(priv->ela2 != NULL)
	{
		k_object_unref(priv->ela2);
		priv->ela2 = NULL;		
	}
	if(priv->ela3 != NULL)
	{
		k_object_unref(priv->ela3);
		priv->ela3 = NULL;		
	}
	if(priv->ela4 != NULL)
	{
		k_object_unref(priv->ela4);
		priv->ela4 = NULL;		
	}
	if(priv->ela5 != NULL)
	{
		k_object_unref(priv->ela5);
		priv->ela5 = NULL;		
	}
	if(priv->ela6 != NULL)
	{
		k_object_unref(priv->ela6);
		priv->ela6 = NULL;		
	}
	if(priv->elareg != NULL)
	{
		k_object_unref(priv->elareg);
		priv->elareg = NULL;			
	}
	if(priv->usercustom != NULL)
	{
		k_object_unref(priv->usercustom);
		priv->usercustom = NULL;			
	}
	if(priv->elacore != NULL)
	{
		k_object_unref(priv->elacore);
		priv->elacore = NULL;			
	}					
}

static void ctImElaEachRegPrint(CtImEla *self)
{
	Ddim_Print(("---EAch Area---\n"));
	ctImElaOnPclk(self);

	// ELA
	Ddim_Print(("EARCACHE[0] = 0x%02x\n", IO_ELA.EARCACHE.bit.EARCACHE_0));
	Ddim_Print(("EARCACHE[1] = 0x%02x\n", IO_ELA.EARCACHE.bit.EARCACHE_1));
	Ddim_Print(("EARCACHE[2] = 0x%02x\n", IO_ELA.EARCACHE.bit.EARCACHE_2));

	Ddim_Print(("EAWCACHE[0] = 0x%02x\n", IO_ELA.EAWCACHE.bit.EAWCACHE_0));
	Ddim_Print(("EAWCACHE[1] = 0x%02x\n", IO_ELA.EAWCACHE.bit.EAWCACHE_1));
	Ddim_Print(("EAWCACHE[2] = 0x%02x\n", IO_ELA.EAWCACHE.bit.EAWCACHE_2));

	Ddim_Print(("EARPROT[0] = 0x%02x\n", IO_ELA.EARPROT.bit.EARPROT_0));
	Ddim_Print(("EARPROT[1] = 0x%02x\n", IO_ELA.EARPROT.bit.EARPROT_1));
	Ddim_Print(("EARPROT[2] = 0x%02x\n", IO_ELA.EARPROT.bit.EARPROT_2));

	Ddim_Print(("EAWPROT[0] = 0x%02x\n", IO_ELA.EAWPROT.bit.EAWPROT_0));
	Ddim_Print(("EAWPROT[1] = 0x%02x\n", IO_ELA.EAWPROT.bit.EAWPROT_1));
	Ddim_Print(("EAWPROT[2] = 0x%02x\n", IO_ELA.EAWPROT.bit.EAWPROT_2));

	Ddim_Print(("RRESP[0] = 0x%02x\n", IO_ELA.EARAXSTS.bit.RRESP_0));
	Ddim_Print(("RRESP[1] = 0x%02x\n", IO_ELA.EARAXSTS.bit.RRESP_1));
	Ddim_Print(("RRESP[2] = 0x%02x\n", IO_ELA.EARAXSTS.bit.RRESP_2));

	Ddim_Print(("BRESP[0] = 0x%02x\n", IO_ELA.EAWAXSTS.bit.BRESP_0));
	Ddim_Print(("BRESP[1] = 0x%02x\n", IO_ELA.EAWAXSTS.bit.BRESP_1));
	Ddim_Print(("BRESP[2] = 0x%02x\n", IO_ELA.EAWAXSTS.bit.BRESP_2));

	Ddim_Print(("EARREQMSK[0] = 0x%02x\n", IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_0));
	Ddim_Print(("EARREQMSK[1] = 0x%02x\n", IO_ELA.EARREQMSK.EARREQMSK1.bit.EARREQMSK_1));
	Ddim_Print(("EARREQMSK[2] = 0x%02x\n", IO_ELA.EARREQMSK.EARREQMSK2.bit.EARREQMSK_2));

	Ddim_Print(("EAWREQMSK[0] = 0x%02x\n", IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_0));
	Ddim_Print(("EAWREQMSK[1] = 0x%02x\n",	 IO_ELA.EAWREQMSK.EAWREQMSK1.bit.EAWREQMSK_1));
	Ddim_Print(("EAWREQMSK[2] = 0x%02x\n", IO_ELA.EAWREQMSK.EAWREQMSK2.bit.EAWREQMSK_2));

	ctImElaOffPclk(self);
//	ddim_user_custom_dly_tsk(10);
}

static void ctImElaInterruptRegPrint(CtImEla *self)
{
	Ddim_Print(("---Interrupt Register---\n"));

	ctImElaOnPclk(self);

	// ELA
	Ddim_Print(("ENWE = 0x%02x\n", IO_ELA.ELAINTE.bit.ENWE));
	Ddim_Print(("AXRERE = 0x%02x\n", IO_ELA.ELAINTE.bit.AXRERE));
	Ddim_Print(("AXWERE = 0x%02x\n", IO_ELA.ELAINTE.bit.AXWERE));
	Ddim_Print(("ENWF = 0x%02x\n", IO_ELA.ELAINTF.bit.__ENWF));
	Ddim_Print(("AXRERF = 0x%02x\n", IO_ELA.ELAINTF.bit.__AXRERF));
	Ddim_Print(("AXWERF = 0x%02x\n", IO_ELA.ELAINTF.bit.__AXWERF));

	ctImElaOffPclk(self);
//	ddim_user_custom_dly_tsk(10);
}

static void ctImElaCtrlRegPrint(CtImEla *self)
{
	kuint32 i;

	Ddim_Print(("---ELA Area---\n"));
	ctImElaOnPclk(self);

	// ELA
	Ddim_Print(("ELATRG.ELATRG = 0x%02x\n", IO_ELA.ELATRG.bit.ELATRG));

	Ddim_Print(("ELACTL.ELACNT = 0x%02x\n", IO_ELA.ELACTL.bit.ELACNT));
	Ddim_Print(("ELACTL.ELAMD = 0x%02x\n", IO_ELA.ELACTL.bit.ELAMD));
	Ddim_Print(("ELACTL.ELAACT = 0x%02x\n",	IO_ELA.ELACTL.bit.ELAACT));

	Ddim_Print(("ELABYR.EIRTYP = 0x%02x\n", IO_ELA.ELABYR.bit.EIRTYP));
	Ddim_Print(("ELABYR.EIRSFT = 0x%02x\n", IO_ELA.ELABYR.bit.EIRSFT));
	Ddim_Print(("ELABYR.EIWSFT = 0x%02x\n", IO_ELA.ELABYR.bit.EIWSFT));
	Ddim_Print(("ELABYR.EIWTYP = 0x%02x\n", IO_ELA.ELABYR.bit.EIWTYP));
	Ddim_Print(("ELABYR.EIWOUT = 0x%02x\n", IO_ELA.ELABYR.bit.EIWOUT));
	Ddim_Print(("ELABYR.DKNEN = 0x%02x\n", IO_ELA.ELABYR.bit.DKNEN));
	Ddim_Print(("ELABYR.EOBAEN = 0x%02x\n", IO_ELA.ELABYR.bit.EOBAEN));
	Ddim_Print(("ELABYR.DKNACT = 0x%02x\n", IO_ELA.ELABYR.bit.DKNACT));

	Ddim_Print(("NSLMD.NSLMD = 0x%02x\n", IO_ELA.NSLMD.bit.NSLMD));
	Ddim_Print(("NSLMD.NSLRES = 0x%02x\n", IO_ELA.NSLMD.bit.NSLRES));
	Ddim_Print(("NSLMD.NSLKNE = 0x%02x\n", IO_ELA.NSLMD.bit.NSLKNE));

	Ddim_Print(("OBOF.EOBRR = 0x%04x\n", IO_ELA.OBOF.OBOF1.bit.EOBRR));
	Ddim_Print(("OBOF.EOBBB = 0x%04x\n", IO_ELA.OBOF.OBOF1.bit.EOBBB));
	Ddim_Print(("OBOF.EOBGR = 0x%04x\n", IO_ELA.OBOF.OBOF2.bit.EOBGR));
	Ddim_Print(("OBOF.EOBGB = 0x%04x\n", IO_ELA.OBOF.OBOF2.bit.EOBGB));

	Ddim_Print(("EZSFTA1 = 0x%04x\n", IO_ELA.EZSFTA1.bit.EZSFTA1));

	Ddim_Print(("NSLNGLMM = 0x%04x\n", IO_ELA.NSLNGLMT.bit.NSLNGLMM));
	Ddim_Print(("NSLNGLMP = 0x%04x\n", IO_ELA.NSLNGLMT.bit.NSLNGLMP));

	Ddim_Print(("EIRA = 0x%08lx\n", IO_ELA.EIRA.word));
	Ddim_Print(("EIROFS = 0x%02x\n", IO_ELA.EIROFS.bit.EIROFS));
	Ddim_Print(("EIRDEF = 0x%04x\n", IO_ELA.EIRDEF.bit.EIRDEF));
	Ddim_Print(("EIRHSIZ = 0x%04x\n", IO_ELA.EIRHSIZ.bit.EIRHSIZ));
	Ddim_Print(("EIRVSIZ = 0x%04x\n", IO_ELA.EIRVSIZ.bit.EIRVSIZ));

	for(i = 0; i < 4; i++){
		Ddim_Print(("EIWA[%d] = 0x%08lx\n",	i, IO_ELA.EIWA.word[i]));
	}
	Ddim_Print(("EIWDEF = 0x%04x\n", IO_ELA.EIWDEF.bit.EIWDEF));

	Ddim_Print(("ENWA = 0x%08lx\n", IO_ELA.ENWA.word));
	Ddim_Print(("ENWDEF = 0x%04x\n", IO_ELA.ENWDEF.bit.ENWDEF));

	for(i = 0; i < 16; i++){
		Ddim_Print(("ENRA[%d] = 0x%08lx\n",	i, IO_ELA.ENRA.word[i]));
	}
	Ddim_Print(("ENRHSIZ = 0x%04x\n", IO_ELA.ENRHSIZ.bit.ENRHSIZ));
	Ddim_Print(("ENRVSIZ = 0x%04x\n", IO_ELA.ENRVSIZ.bit.ENRVSIZ));

	Ddim_Print(("ENSA = 0x%08lx\n", IO_ELA.ENSA.word));
	Ddim_Print(("ENSDEF = 0x%04x\n", IO_ELA.ENSDEF.bit.ENSDEF));
	Ddim_Print(("ENSHSIZ = 0x%04x\n", IO_ELA.ENSHSIZ.bit.ENSHSIZ));
	Ddim_Print(("ENSVSIZ = 0x%04x\n", IO_ELA.ENSVSIZ.bit.ENSVSIZ));

	ctImElaOffPclk(self);
//	ddim_user_custom_dly_tsk(10);
}

static void ctImElaCoreRegPrint(CtImEla *self)
{
	Ddim_Print(("---CORE Area---\n"));
	ctImElaOnPclk(self);

	// ELA
	Ddim_Print(("BYRTYP.ORG = 0x%02x\n", IO_ELA.BYRTYP.bit.ORG));
	Ddim_Print(("BYRTYP.ELADCMD = 0x%02x\n", IO_ELA.BYRTYP.bit.ELADCMD));

	Ddim_Print(("ELFZP = 0x%04x\n", IO_ELA.ELFZP.bit.ELFZP));

	Ddim_Print(("ELFL_1 = 0x%04x\n", IO_ELA.ELFL.ELFL1.bit.ELFL_1));
	Ddim_Print(("ELFL_2 = 0x%04x\n", IO_ELA.ELFL.ELFL1.bit.ELFL_2));
	Ddim_Print(("ELFL_3 = 0x%04x\n", IO_ELA.ELFL.ELFL2.bit.ELFL_3));
	Ddim_Print(("ELFL_4 = 0x%04x\n", IO_ELA.ELFL.ELFL2.bit.ELFL_4));

	Ddim_Print(("ANBOR[0] = 0x%04x\n", IO_ELA.ANBOR.ANBOR1.bit.ANBOR_0));
	Ddim_Print(("ANBOR[1] = 0x%04x\n", IO_ELA.ANBOR.ANBOR1.bit.ANBOR_1));
	Ddim_Print(("ANBOR[2] = 0x%04x\n", IO_ELA.ANBOR.ANBOR2.bit.ANBOR_2));
	Ddim_Print(("ANBOR[3] = 0x%04x\n", IO_ELA.ANBOR.ANBOR2.bit.ANBOR_3));

	Ddim_Print(("ANBKR[0] = 0x%04x\n", IO_ELA.ANBKR.ANBKR1.bit.ANBKR_0));
	Ddim_Print(("ANBKR[1] = 0x%04x\n", IO_ELA.ANBKR.ANBKR1.bit.ANBKR_1));
	Ddim_Print(("ANBKR[2] = 0x%04x\n", IO_ELA.ANBKR.ANBKR2.bit.ANBKR_2));
	Ddim_Print(("ANBKR[3] = 0x%04x\n", IO_ELA.ANBKR.ANBKR2.bit.ANBKR_3));

	Ddim_Print(("ANBDR[0] = 0x%04x\n", IO_ELA.ANBDR.ANBDR1.bit.ANBDR_0));
	Ddim_Print(("ANBDR[1] = 0x%04x\n", IO_ELA.ANBDR.ANBDR1.bit.ANBDR_1));
	Ddim_Print(("ANBDR[2] = 0x%04x\n", IO_ELA.ANBDR.ANBDR2.bit.ANBDR_2));
	Ddim_Print(("ANBDR[3] = 0x%04x\n", IO_ELA.ANBDR.ANBDR2.bit.ANBDR_3));

	Ddim_Print(("ANBOG[0] = 0x%04x\n", IO_ELA.ANBOG.ANBOG1.bit.ANBOG_0));
	Ddim_Print(("ANBOG[1] = 0x%04x\n", IO_ELA.ANBOG.ANBOG1.bit.ANBOG_1));
	Ddim_Print(("ANBOG[2] = 0x%04x\n", IO_ELA.ANBOG.ANBOG2.bit.ANBOG_2));
	Ddim_Print(("ANBOG[3] = 0x%04x\n", IO_ELA.ANBOG.ANBOG2.bit.ANBOG_3));

	Ddim_Print(("ANBKG[0] = 0x%04x\n", IO_ELA.ANBKG.ANBKG1.bit.ANBKG_0));
	Ddim_Print(("ANBKG[1] = 0x%04x\n", IO_ELA.ANBKG.ANBKG1.bit.ANBKG_1));
	Ddim_Print(("ANBKG[2] = 0x%04x\n", IO_ELA.ANBKG.ANBKG2.bit.ANBKG_2));
	Ddim_Print(("ANBKG[3] = 0x%04x\n", IO_ELA.ANBKG.ANBKG2.bit.ANBKG_3));

	Ddim_Print(("ANBDG[0] = 0x%04x\n", IO_ELA.ANBDG.ANBDG1.bit.ANBDG_0));
	Ddim_Print(("ANBDG[1] = 0x%04x\n", IO_ELA.ANBDG.ANBDG1.bit.ANBDG_1));
	Ddim_Print(("ANBDG[2] = 0x%04x\n", IO_ELA.ANBDG.ANBDG2.bit.ANBDG_2));
	Ddim_Print(("ANBDG[3] = 0x%04x\n", IO_ELA.ANBDG.ANBDG2.bit.ANBDG_3));

	Ddim_Print(("ANBOB[0] = 0x%04x\n", IO_ELA.ANBOB.ANBOB1.bit.ANBOB_0));
	Ddim_Print(("ANBOB[1] = 0x%04x\n", IO_ELA.ANBOB.ANBOB1.bit.ANBOB_1));
	Ddim_Print(("ANBOB[2] = 0x%04x\n", IO_ELA.ANBOB.ANBOB2.bit.ANBOB_2));
	Ddim_Print(("ANBOB[3] = 0x%04x\n", IO_ELA.ANBOB.ANBOB2.bit.ANBOB_3));
	
	Ddim_Print(("ANBKB[0] = 0x%04x\n", IO_ELA.ANBKB.ANBKB1.bit.ANBKB_0));
	Ddim_Print(("ANBKB[1] = 0x%04x\n", IO_ELA.ANBKB.ANBKB1.bit.ANBKB_1));
	Ddim_Print(("ANBKB[2] = 0x%04x\n", IO_ELA.ANBKB.ANBKB2.bit.ANBKB_2));
	Ddim_Print(("ANBKB[3] = 0x%04x\n", IO_ELA.ANBKB.ANBKB2.bit.ANBKB_3));

	Ddim_Print(("ANBDB[0] = 0x%04x\n", IO_ELA.ANBDB.ANBDB1.bit.ANBDB_0));
	Ddim_Print(("ANBDB[1] = 0x%04x\n", IO_ELA.ANBDB.ANBDB1.bit.ANBDB_1));
	Ddim_Print(("ANBDB[2] = 0x%04x\n", IO_ELA.ANBDB.ANBDB2.bit.ANBDB_2));
	Ddim_Print(("ANBDB[3] = 0x%04x\n", IO_ELA.ANBDB.ANBDB2.bit.ANBDB_3));

	Ddim_Print(("LGTWR = 0x%04x\n", IO_ELA.LGTW.LGTW1.bit.LGTWR));
	Ddim_Print(("LGTWG = 0x%04x\n", IO_ELA.LGTW.LGTW1.bit.LGTWG));
	Ddim_Print(("LGTWB = 0x%04x\n", IO_ELA.LGTW.LGTW2.bit.LGTWB));

	Ddim_Print(("LGTR = 0x%02x\n", IO_ELA.LGT.bit.LGTR));
	Ddim_Print(("LGTG = 0x%02x\n", IO_ELA.LGT.bit.LGTG));
	Ddim_Print(("LGTB = 0x%02x\n", IO_ELA.LGT.bit.LGTB));
	Ddim_Print(("LGTC = 0x%02x\n", IO_ELA.LGT.bit.LGTC));

	Ddim_Print(("LGTER = 0x%02x\n", IO_ELA.LGTE.bit.LGTER));
	Ddim_Print(("LGTEG = 0x%02x\n", IO_ELA.LGTE.bit.LGTEG));
	Ddim_Print(("LGTEB = 0x%02x\n", IO_ELA.LGTE.bit.LGTEB));

	Ddim_Print(("EDG2ANBA = 0x%04x\n", IO_ELA.EDG2ANBA.bit.EDG2ANBA));
	Ddim_Print(("EDGSCLA = 0x%04x\n", IO_ELA.EDGSCLA.bit.EDGSCLA));

	Ddim_Print(("EDG2ANBB = 0x%04x\n", IO_ELA.EDG2ANBB.bit.EDG2ANBB));
	Ddim_Print(("EDGSCLB = 0x%04x\n", IO_ELA.EDGSCLB.bit.EDGSCLB));

	Ddim_Print(("ALNGE1 = 0x%04x\n", IO_ELA.ALNGE.ALNGE1.bit.ALNGE_1));
	Ddim_Print(("ALNGE2 = 0x%04x\n", IO_ELA.ALNGE.ALNGE1.bit.ALNGE_2));
	Ddim_Print(("ALNGE3 = 0x%04x\n", IO_ELA.ALNGE.ALNGE2.bit.ALNGE_3));

	Ddim_Print(("ALNGL1E1N = 0x%04x\n",	IO_ELA.ALNG.ALNG1.bit.ALNGL1E1N));
	Ddim_Print(("ALNGL1E2N = 0x%04x\n",	IO_ELA.ALNG.ALNG1.bit.ALNGL1E2N));
	Ddim_Print(("ALNGL1E3N = 0x%04x\n",	IO_ELA.ALNG.ALNG2.bit.ALNGL1E3N));
	Ddim_Print(("ALNGL2E1N = 0x%04x\n",	IO_ELA.ALNG.ALNG2.bit.ALNGL2E1N));
	Ddim_Print(("ALNGL2E2N = 0x%04x\n",	IO_ELA.ALNG.ALNG3.bit.ALNGL2E2N));
	Ddim_Print(("ALNGL2E3N = 0x%04x\n",	IO_ELA.ALNG.ALNG3.bit.ALNGL2E3N));
	Ddim_Print(("ALNGL3E1N = 0x%04x\n",	IO_ELA.ALNG.ALNG4.bit.ALNGL3E1N));
	Ddim_Print(("ALNGL3E2N = 0x%04x\n",	IO_ELA.ALNG.ALNG4.bit.ALNGL3E2N));
	Ddim_Print(("ALNGL3E3N = 0x%04x\n",	IO_ELA.ALNG.ALNG5.bit.ALNGL3E3N));
	Ddim_Print(("ALNGL4E1N = 0x%04x\n",	IO_ELA.ALNG.ALNG5.bit.ALNGL4E1N));
	Ddim_Print(("ALNGL4E2N = 0x%04x\n",	IO_ELA.ALNG.ALNG6.bit.ALNGL4E2N));
	Ddim_Print(("ALNGL4E3N = 0x%04x\n",	IO_ELA.ALNG.ALNG6.bit.ALNGL4E3N));

	Ddim_Print(("LFTH = 0x%04x\n", IO_ELA.LFTH.bit.LFTH));

	Ddim_Print(("LCOME1 = 0x%04x\n", IO_ELA.LCOME.bit.LCOME1));
	Ddim_Print(("LCOME2 = 0x%04x\n", IO_ELA.LCOME.bit.LCOME2));

	Ddim_Print(("LCOME1N = 0x%04x\n", IO_ELA.LCOMEN.bit.LCOME1N));
	Ddim_Print(("LCOME2N = 0x%04x\n", IO_ELA.LCOMEN.bit.LCOME2N));

	ctImElaOffPclk(self);
//	ddim_user_custom_dly_tsk(10);
}

static void ctImElaCurtailBayerTblPrint(CtImEla *self)
{
	kuint32 i, j;
	TImElaCurtailBayerData curtail_bayer[ImElaReg_D_IM_ELA_STAGE_MAX];

	Ddim_Print(("---Curtail Bayer Data Tbl---\n"));

	im_ela_reg_get_curtail_bayer_data_tbl(priv->elareg, curtail_bayer);
	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		Ddim_Print(("(((Stage%d)))\n", i + 1));
		Ddim_Print(("gl_hbyte = %d\n",	curtail_bayer[i].gl_hbyte));
		Ddim_Print(("hsize = %d\n",	curtail_bayer[i].hsize));
		Ddim_Print(("vline = %d\n",	curtail_bayer[i].vline));
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			Ddim_Print(("(Sterp%02d)bayer_addr = 0x%08X\n", j, curtail_bayer[i].bayer_addr[j]));
//			ddim_user_custom_dly_tsk(10);
		}
	}
}

static void ctImElaExtractNoiseTblPrint(CtImEla *self)
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);
	kuint32 i, j;
	TImElaExtractNoiseData extract_noise[ImElaReg_D_IM_ELA_STAGE_MAX];

	Ddim_Print(("---Extract Noise Data Tbl---\n"));

	im_ela_reg_get_extract_noise_data_tbl(priv->elareg, extract_noise);
	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		Ddim_Print(("(((Stage%d)))\n", i + 1));
		Ddim_Print(("gl_hbyte = %d\n",	extract_noise[i].gl_hbyte));
		Ddim_Print(("hsize = %d\n",	extract_noise[i].hsize));
		Ddim_Print(("vline = %d\n",	extract_noise[i].vline));
		for(j = 0; j < ImElaReg_D_IM_ELA_STEP_MAX; j++){
			Ddim_Print(("(Sterp%02d)noise_data_addr = 0x%08X\n", j, extract_noise[i].noise_data_addr[j]));
//			ddim_user_custom_dly_tsk(10);
		}
	}
}

static void ctImElaOnPclk(CtImEla *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Start_Clock((kuchar*)&S_GCT_IM_ELA_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), ~D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

/* ELA PCLK change to OFF */
static void ctImElaOffPclk(CtImEla *self)
{
#ifdef CO_ACT_PCLOCK
	Dd_Top_Stop_Clock((kuchar*)&S_GCT_IM_ELA_PCLK_COUNTER, &Dd_Top_Get_CLKSTOP6(), D_DD_TOP_ELAAP_BIT);
#endif	// CO_ACT_PCLOCK
}

void ct_im_ela_ctrl_set_test_data(CtImEla *self, TImElaCtrl* const ctrl_ela)
{
	ctrl_ela->next_ctrl_flag = ImEla_D_IM_ELA_DISABLE;

	ctrl_ela->ela_elf_level = ImEla_E_IM_ELA_ELF_LEVEL_5;
	ctrl_ela->ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_1] = ImEla_E_IM_ELA_DENSITY_MODE_1;
	ctrl_ela->ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_2] = ImEla_E_IM_ELA_DENSITY_MODE_2;
	ctrl_ela->ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_3] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrl_ela->ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_4] = ImEla_E_IM_ELA_DENSITY_MODE_3;
	ctrl_ela->ela_density_mode[ImEla_E_IM_ELA_ELF_LEVEL_5] = ImEla_E_IM_ELA_DENSITY_MODE_3;

	ctrl_ela->ctrl_common.noise_data_mode = ImEla_D_IM_ELA_NSLMD_SAME;
	ctrl_ela->ctrl_common.noise_data_precision = ImEla_D_IM_ELA_NSLRES_PRECISION_2;
	ctrl_ela->ctrl_common.noise_data_compress_enable = ImEla_D_IM_ELA_ENABLE;
	ctrl_ela->ctrl_common.bayer_start_pixel_type = ImEla_D_IM_ELA_ORG_R;

	ctrl_ela->ctrl_byr.in_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrl_ela->ctrl_byr.in_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrl_ela->ctrl_byr.out_data_type = ImEla_D_IM_ELA_DATATYP_12BIT;
	ctrl_ela->ctrl_byr.out_data_shift_mode = ImEla_D_IM_ELA_BIT_SHIFT_MODE_NONE;
	ctrl_ela->ctrl_byr.deknee_enable = ImEla_D_IM_ELA_DISABLE;
	ctrl_ela->ctrl_byr.ob_zsf_enable = ImEla_D_IM_ELA_DISABLE;

	//OB Correction control
	ctrl_ela->ob_correction.ob_rr = 0x001;
	ctrl_ela->ob_correction.ob_bb = 0x002;
	ctrl_ela->ob_correction.ob_gr = 0x003;
	ctrl_ela->ob_correction.ob_gb = 0x004;

	ctrl_ela->ctrl_eirch.in_bayer_top_addr = CtImEla_S_SDRAM_ELA_ADR_IN_BAYER;
	ctrl_ela->ctrl_eirch.in_bayer_top_offset = 0;
	ctrl_ela->ctrl_eirch.in_bayer_total_hsize = 6048;
	ctrl_ela->ctrl_eirch.in_bayer_hsize = CtImEla_S_ELA_BAYER_12M_WIDTH;
	ctrl_ela->ctrl_eirch.in_bayer_vline = CtImEla_S_ELA_BAYER_12M_LINES;

	ctrl_ela->out_bayer_addr = CtImEla_S_SDRAM_ELA_ADR_OUT_BAYER;
	ctrl_ela->extract_noise_addr = CtImEla_S_SDRAM_ELA_ADR_EXTRACT_NOISE;
	ctrl_ela->noise_suppress_addr = CtImEla_S_SDRAM_ELA_ADR_NOISE_SUPPRESS;
}

#if 1
void ct_im_ela_multiple_set_test_data(CtImEla *self, TImElaMultipleTimesInfo* multiple_exec_info)
{
	kint32 i;

	for(i = 0; i < ImElaReg_D_IM_ELA_STAGE_MAX; i++){
		multiple_exec_info->core[i]->defect_correction_mode = ImEla_D_IM_ELA_ELADCMD_WEAK;
		multiple_exec_info->core[i]->zero_point_level = 0x00C7;
		multiple_exec_info->core[i]->optical_zero_level_shift	= 0;

		multiple_exec_info->core[i]->elflt[ImEla_E_IM_ELA_ELFL_T1] = 0x00B2;
		multiple_exec_info->core[i]->elflt[ImEla_E_IM_ELA_ELFL_T2] = 0x0134;
		multiple_exec_info->core[i]->elflt[ImEla_E_IM_ELA_ELFL_T3] = 0x0202;
		multiple_exec_info->core[i]->elflt[ImEla_E_IM_ELA_ELFL_T4] = 0x02f2;

		multiple_exec_info->core[i]->anb_r.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
		multiple_exec_info->core[i]->anb_r.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
		multiple_exec_info->core[i]->anb_r.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
		multiple_exec_info->core[i]->anb_r.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
		multiple_exec_info->core[i]->anb_r.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
		multiple_exec_info->core[i]->anb_r.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
		multiple_exec_info->core[i]->anb_r.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
		multiple_exec_info->core[i]->anb_r.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
		multiple_exec_info->core[i]->anb_r.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
		multiple_exec_info->core[i]->anb_r.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
		multiple_exec_info->core[i]->anb_r.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
		multiple_exec_info->core[i]->anb_r.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;

		multiple_exec_info->core[i]->anb_g.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
		multiple_exec_info->core[i]->anb_g.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
		multiple_exec_info->core[i]->anb_g.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
		multiple_exec_info->core[i]->anb_g.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
		multiple_exec_info->core[i]->anb_g.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
		multiple_exec_info->core[i]->anb_g.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
		multiple_exec_info->core[i]->anb_g.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
		multiple_exec_info->core[i]->anb_g.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
		multiple_exec_info->core[i]->anb_g.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
		multiple_exec_info->core[i]->anb_g.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
		multiple_exec_info->core[i]->anb_g.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
		multiple_exec_info->core[i]->anb_g.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;

		multiple_exec_info->core[i]->anb_b.offset[ImEla_E_IM_ELA_ANB_1] = 0x0058;
		multiple_exec_info->core[i]->anb_b.offset[ImEla_E_IM_ELA_ANB_2] = 0x0093;
		multiple_exec_info->core[i]->anb_b.offset[ImEla_E_IM_ELA_ANB_3] = 0x00c5;
		multiple_exec_info->core[i]->anb_b.offset[ImEla_E_IM_ELA_ANB_4] = 0x0103;
		multiple_exec_info->core[i]->anb_b.gain[ImEla_E_IM_ELA_ANB_1] = 0x0273;
		multiple_exec_info->core[i]->anb_b.gain[ImEla_E_IM_ELA_ANB_2] = 0x0215;
		multiple_exec_info->core[i]->anb_b.gain[ImEla_E_IM_ELA_ANB_3] = 0x0149;
		multiple_exec_info->core[i]->anb_b.gain[ImEla_E_IM_ELA_ANB_4] = 0x00f5;
		multiple_exec_info->core[i]->anb_b.boundary[ImEla_E_IM_ELA_ANB_1] = 0x0000;
		multiple_exec_info->core[i]->anb_b.boundary[ImEla_E_IM_ELA_ANB_2] = 0x0180;
		multiple_exec_info->core[i]->anb_b.boundary[ImEla_E_IM_ELA_ANB_3] = 0x0300;
		multiple_exec_info->core[i]->anb_b.boundary[ImEla_E_IM_ELA_ANB_4] = 0x0600;
                                                                      
		multiple_exec_info->core[i]->lumen_gain_r = 0x100;
		multiple_exec_info->core[i]->lumen_gain_g = 0x100;
		multiple_exec_info->core[i]->lumen_gain_b = 0x100;

		multiple_exec_info->core[i]->lumen_factor_r = 0x4;
		multiple_exec_info->core[i]->lumen_factor_g = 0x8;
		multiple_exec_info->core[i]->lumen_factor_b = 0x4;
		multiple_exec_info->core[i]->lumen_factor_c = 0x8;

		multiple_exec_info->core[i]->lumen_edge_r = 0x4;
		multiple_exec_info->core[i]->lumen_edge_g = 0x8;
		multiple_exec_info->core[i]->lumen_edge_b = 0x4;

		multiple_exec_info->core[i]->edge_adjust_a1 = 0x008a;
		multiple_exec_info->core[i]->edge_adjust_a2 = 0x0083;
		multiple_exec_info->core[i]->edge_adjust_b1 = 0x02fc;
		multiple_exec_info->core[i]->edge_adjust_b2 = 0x0033;

		multiple_exec_info->core[i]->edge_threshold[ImEla_E_IM_ELA_ALNGE_1] = 0x008e;
		multiple_exec_info->core[i]->edge_threshold[ImEla_E_IM_ELA_ALNGE_2] = 0x00d5;
		multiple_exec_info->core[i]->edge_threshold[ImEla_E_IM_ELA_ALNGE_3] = 0x011c;

		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L1E1N] = 0x00b4;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L1E2N] = 0x0082;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L1E3N] = 0x0000;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L2E1N] = 0x00a0;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L2E2N] = 0x0069;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L2E3N] = 0x0000;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L3E1N] = 0x008c;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L3E2N] = 0x0050;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L3E3N] = 0x0000;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L4E1N] = 0x0078;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L4E2N] = 0x003c;
		multiple_exec_info->core[i]->nr[ImEla_E_IM_ELA_ALNG_L4E3N] = 0x0000;

		multiple_exec_info->core[i]->l_noise = 0x00c8;

		multiple_exec_info->core[i]->l_edge[ImEla_E_IM_ELA_LCOME_1] = 0x008e;
		multiple_exec_info->core[i]->l_edge[ImEla_E_IM_ELA_LCOME_2] = 0x011c;

		multiple_exec_info->core[i]->l_intense[ImEla_E_IM_ELA_LCOMEN_1] = 0x0000;
		multiple_exec_info->core[i]->l_intense[ImEla_E_IM_ELA_LCOMEN_2] = 0x00cd;

		multiple_exec_info->core[i]->limit.noise_plus_limit = 0x0277;
		multiple_exec_info->core[i]->limit.noise_minus_limit = 0x0277;
	}
}
#endif

void ct_im_ela_clk_chk(CtImEla *self)
{
#ifdef CO_ACT_ICLOCK
	if(S_GIM_ELA_CLK_COUNTER != 0){
		Ddim_Print(("E:Pclk NG : S_GIM_ELA_CLK_COUNTER=%d.\n", S_GIM_ELA_CLK_COUNTER));
	}
	if(S_GIM_ELA_ICLK_COUNTER != 0){
		Ddim_Print(("E:Pclk NG : S_GIM_ELA_ICLK_COUNTER=%d.\n", S_GIM_ELA_ICLK_COUNTER));
	}
#endif //CO_ACT_ICLOCK
#ifdef CO_ACT_MXIC_PCLOCK
	if(gIM_SDI_PCLK_Counter != 0){
		Ddim_Print(("E:Pclk NG : gIM_SDI_PCLK_Counter=%d.\n", gIM_SDI_PCLK_Counter));
	}
#endif // CO_ACT_MXIC_PCLOCK
//	ddim_user_custom_dly_tsk(10);
}

void ct_im_ela_reg_print(CtImEla *self)
{
	ctImElaEachRegPrint(self);
	ctImElaCtrlRegPrint(self);
	ctImElaCoreRegPrint(self);
	ctImElaInterruptRegPrint(self);
	ctImElaCurtailBayerTblPrint(self);
	ctImElaExtractNoiseTblPrint(self);
}

/**
 * @brief       Command processing of ELA.
 * @param[in]   kint32 argc
 * @param[in]   kchar** argv
 * @return      None
 * @note        Command processing of ELA.
 * @attention   None
 */
void ct_im_ela_main(CtImEla *self, kint32 argc, kchar** argv)
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);

//	Dd_MMU_Clean_Flush_Dcache_All();
	ddim_user_custom_l1l2cache_clean_flush_all(priv->usercustom);

	if (strcmp((KConstType)argv[1], "ct") == 0){
		if(atoi((KConstType)argv[2]) == 1){
			switch(atoi((KConstType)argv[3])){
				case 1:
					ct_im_ela_1_01(self);
					break;
				case 2:
					ct_im_ela_1_02(self);
					break;
				case 3:
					ct_im_ela_1_03(self);
					break;
				case 4:
					ct_im_ela1_1_04(priv->ela1);
					break;
				case 5:
					ct_im_ela1_1_05(priv->ela1);
					break;
				case 6:
					ct_im_ela1_1_06(priv->ela1);
					break;
				case 7:
					ct_im_ela1_1_07(priv->ela1);
					break;
				case 8:
					ct_im_ela1_1_08(priv->ela1);
					break;
				case 9:
					ct_im_ela1_1_09(priv->ela1);
					break;
				case 10:
					ct_im_ela1_1_10(priv->ela1);
					break;
				case 11:
					ct_im_ela1_1_11(priv->ela1);
					break;
				case 12:
					ct_im_ela2_1_12(priv->ela2);
					break;
				case 13:
					ct_im_ela2_1_13(priv->ela2);
					break;
				case 14:
					ct_im_ela2_1_14(priv->ela2);
					break;
				case 15:
					ct_im_ela2_1_15(priv->ela2);
					break;
				case 16:
					ct_im_ela2_1_16(priv->ela2);
					break;
				case 17:
					ct_im_ela2_1_17(priv->ela2);
					break;
				case 18:
					ct_im_ela2_1_18(priv->ela2);
					break;
				case 19:
					ct_im_ela2_1_19(priv->ela2);
					break;
				case 20:
					ct_im_ela2_1_20(priv->ela2);
					break;
				case 21:
					ct_im_ela2_1_21(priv->ela2);
					break;
				case 22:
					ct_im_ela2_1_22(priv->ela2);
					break;
				case 23:
					ct_im_ela2_1_23(priv->ela2);
					break;
				case 24:
					ct_im_ela2_1_24(priv->ela2);
					break;
				case 25:
					ct_im_ela2_1_25(priv->ela2);
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					break;
				}
		}
		else if(atoi((KConstType)argv[2]) == 2){
			switch(atoi((KConstType)argv[3])){
				case 1:
					ct_im_ela3_2_01(priv->ela3);
					break;
				case 2:
					ct_im_ela3_2_02(priv->ela3);
					break;
				case 3:
					ct_im_ela3_2_03(priv->ela3);
					break;
				case 4:
					ct_im_ela3_2_04(priv->ela3);
					break;
				case 5:
					ct_im_ela3_2_05(priv->ela3);
					break;
				case 6:
					ct_im_ela3_2_06(priv->ela3);
					break;
				case 7:
					ct_im_ela3_2_07(priv->ela3);
					break;
				case 8:
					ct_im_ela3_2_08(priv->ela3);
					break;
				case 9:
					ct_im_ela4_2_09(priv->ela4);
					break;
				case 10:
					ct_im_ela4_2_10(priv->ela4);
					break;
				case 11:
					ct_im_ela4_2_11(priv->ela4);
					break;
				case 12:
					ct_im_ela4_2_12(priv->ela4);
					break;
				case 13:
					ct_im_ela4_2_13(priv->ela4);
					break;
				case 14:
					ct_im_ela4_2_14(priv->ela4);
					break;
				case 15:
					ct_im_ela4_2_15(priv->ela4);
					break;
				case 16:
					ct_im_ela4_2_16(priv->ela4);
					break;
				case 17:
					ct_im_ela5_2_17(priv->ela5);
					break;
				case 18:
					ct_im_ela5_2_18(priv->ela5);
					break;
				case 19:
					ct_im_ela5_2_19(priv->ela5);
					break;
				case 20:
					ct_im_ela5_2_20(priv->ela5);
					break;
				case 21:
					ct_im_ela5_2_21(priv->ela5);
					break;
				case 22:
					ct_im_ela5_2_22(priv->ela5);
					break;
				case 23:
					ct_im_ela5_2_23(priv->ela5);
					break;
				case 24:
					ct_im_ela5_2_24(priv->ela5);
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					break;					
				}				
			}
		if(atoi((KConstType)argv[2]) == 3){
			switch(atoi((KConstType)argv[3])){
				case 1:
					ct_im_ela6_3_01(priv->ela6);
					break;
				case 2:
					ct_im_ela6_3_02(priv->ela6);
					break;
				case 3:
					ct_im_ela6_3_03(priv->ela6);
					break;
				case 4:
					ct_im_ela6_3_04(priv->ela6);
					break;
				case 5:
					ct_im_ela6_3_05(priv->ela6);
					break;
				case 6:
					ct_im_ela6_3_06(priv->ela6);
					break;
				case 7:
					ct_im_ela6_3_07(priv->ela6);
					break;
				case 8:
					ct_im_ela6_3_08(priv->ela6);
					break;
				case 9:
					ct_im_ela6_3_09(priv->ela6);
					break;
				case 10:
					ct_im_ela6_3_10(priv->ela6);
					break;
				case 11:
					ct_im_ela6_3_11(priv->ela6);
					break;
				case 12:
					ct_im_ela6_3_12(priv->ela6);
					break;
				case 13:
					ct_im_ela6_3_13(priv->ela6);
					break;
				case 14:
					ct_im_ela6_3_14(priv->ela6);
					break;
				case 15:
					ct_im_ela6_3_15(priv->ela6);
					break;
				case 16:
					ct_im_ela6_3_16(priv->ela6);
					break;
				case 17:
					ct_im_ela6_3_17(priv->ela6);
					break;
				case 18:
					ct_im_ela6_3_18(priv->ela6);
					break;
				case 19:
					ct_im_ela6_3_19(priv->ela6);
					break;
				case 20:
					ct_im_ela6_3_20(priv->ela6);
					break;
				case 21:
					ct_im_ela6_3_21(priv->ela6);
					break;
				case 22:
					ct_im_ela6_3_22(priv->ela6);
					break;
				case 23:
					ct_im_ela6_3_23(priv->ela6);
					break;
				case 24:
					ct_im_ela6_3_24(priv->ela6);
					break;
				case 25:
					ct_im_ela6_3_25(priv->ela6);
					break;
				case 26:
					ct_im_ela6_3_26(priv->ela6);
					break;
				case 27:
					ct_im_ela6_3_27(priv->ela6);
					break;
				case 28:
					ct_im_ela6_3_28(priv->ela6);
					break;
				case 29:
					ct_im_ela6_3_29(priv->ela6);
					break;
				case 30:
					ct_im_ela6_3_30(priv->ela6);
					break;
				case 31:
					ct_im_ela6_3_31(priv->ela6);
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					break;
				}
		}
		else{
			Ddim_Print(("input parameter error\n"));
			return;
			}
		}
	else{
		Ddim_Print(("Error: Unknown command.\n"));
	}

//	Dd_MMU_Clean_Flush_Dcache_All();
	ddim_user_custom_l1l2cache_clean_flush_all(priv->usercustom);

	return;
}

void ct_im_ela_1_01(CtImEla *self)
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);	
	Ddim_Print(("<%s>\n", __FUNCTION__));

	im_ela_reg_open(priv->elareg, 100);

	im_ela_core_init(priv->elacore);

	ctImElaOnPclk(self);
	Ddim_Print(("ENWE = 0x%02x\n", IO_ELA.ELAINTE.bit.ENWE));
	Ddim_Print(("AXRERE = 0x%02x\n", IO_ELA.ELAINTE.bit.AXRERE));
	Ddim_Print(("AXWERE = 0x%02x\n", IO_ELA.ELAINTE.bit.AXWERE));
	Ddim_Print(("ENWF = 0x%02x\n", IO_ELA.ELAINTF.bit.__ENWF));
	Ddim_Print(("AXRERF = 0x%02x\n", IO_ELA.ELAINTF.bit.__AXRERF));
	Ddim_Print(("AXWERF = 0x%02x\n", IO_ELA.ELAINTF.bit.__AXWERF));
	ctImElaOffPclk(self);

	ct_im_ela_clk_chk(self);

	im_ela_reg_close(priv->elareg);

	ddim_user_custom_dly_tsk(10);
}

void ct_im_ela_1_02(CtImEla *self)
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);		
	kuchar result;
	Ddim_Print(("<%s>\n", __FUNCTION__));
	
#ifdef CtImEla_CT_IM_ELA_SET_TEST_DATA
	ctImElaOnPclk(self);
	IO_ELA.ELACTL.bit.ELACNT = 3;
	ctImElaOffPclk(self);
#endif

	im_ela_reg_open(priv->elareg, 100);

	result = im_ela_reg_get_exe_cnt(priv->elareg);
	Ddim_Print(("im_ela_reg_get_exe_cnt = %d\n", result));

	ctImElaOnPclk(self);
	Ddim_Print(("ELACNT = 0x%02x\n", IO_ELA.ELACTL.bit.ELACNT));
	ctImElaOffPclk(self);

	ct_im_ela_clk_chk(self);

	im_ela_reg_close(priv->elareg);
}

void ct_im_ela_1_03(CtImEla *self)
{
	CtImElaPrivate *priv = CT_IM_ELA_GET_PRIVATE(self);		
	kuint32 result;
	TImElaCtrl ctrl_ela = {0};

	Ddim_Print(("<%s>\n", __FUNCTION__));

	ct_im_ela_ctrl_set_test_data(self, &ctrl_ela);

	ctrl_ela.ctrl_byr.deknee_enable = ImEla_D_IM_ELA_ENABLE;
	ctrl_ela.ctrl_byr.ob_zsf_enable = ImEla_D_IM_ELA_ENABLE;

	ctrl_ela.ob_correction.ob_rr = 0x03FF;
	ctrl_ela.ob_correction.ob_bb = 0x03FF;
	ctrl_ela.ob_correction.ob_gr = 0x03FF;
	ctrl_ela.ob_correction.ob_gb = 0x03FF;

	im_ela_reg_open(priv->elareg, 100);

	result = im_ela_ctrl(priv->imela, &ctrl_ela);
	Ddim_Print(("im_ela_ctrl = %d\n", result));

	ctImElaCtrlRegPrint(self);
	ctImElaCurtailBayerTblPrint(self);
	ctImElaExtractNoiseTblPrint(self);
	ctImElaCoreRegPrint(self);

	ct_im_ela_clk_chk(self);

	im_ela_reg_close(priv->elareg);
}

CtImEla* ct_im_ela_new(void) 
{
    CtImEla *self = k_object_new_with_private(CT_TYPE_IM_ELA, sizeof(CtImElaPrivate));
    return self;
}
