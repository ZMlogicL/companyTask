/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-11
*@author : 刘嫚鶄
*@brief : DdimUserCustomTest
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "../include/os_user_custom.h"
#include "dd_arm.h"
#include "dd_cache.h"

#include "ddimusercustomtest.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdimUserCustomTest, ddim_user_custom_test)
#define DDIM_USER_CUSTOM_TEST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdimUserCustomTestPrivate, DDIM_TYPE_USER_CUSTOM_TEST))


struct _DdimUserCustomTestPrivate
{

};

extern void MMU_Flush_Dcache_All(void);//索喜.a库的东西
extern void MMU_Clean_Dcache_All(void);//索喜.a库的东西
extern void MMU_Flush_Clean_Dcache_All(void);//索喜.a库的东西
extern void MMU_Flush_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西
extern void MMU_Clean_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西
extern void MMU_Flush_Clean_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西

static void ddim_user_custom_test_constructor(DdimUserCustomTest *self)
{
//	DdimUserCustomTestPrivate *priv = DDIM_USER_CUSTOM_TEST_GET_PRIVATE(self);
}

static void ddim_user_custom_test_destructor(DdimUserCustomTest *self)
{
	DdimUserCustomTestPrivate *priv = DDIM_USER_CUSTOM_TEST_GET_PRIVATE(self);
}

DDIM_USER_ER	ddim_user_custom_tslp_tsk(DdimUserCustom *self,DDIM_USER_TMO timeout)
{
	return (DDIM_USER_ER)OS_User_Tslp_Tsk((OS_USER_TMO)timeout);
}

VOID	ddim_user_custom_ext_tsk(DdimUserCustom *self)
{
	OS_User_Ext_Tsk();
}

DDIM_USER_ER	ddim_user_custom_dly_tsk(DdimUserCustom *self,DDIM_USER_RELTIM delaytime)
{
	return (DDIM_USER_ER)OS_User_Dly_Tsk((RELTIM)delaytime);
}

DDIM_USER_ER	ddim_user_custom_sig_sem(DdimUserCustom *self,DDIM_USER_ID semid)
{
	return (DDIM_USER_ER)OS_User_Sig_Sem((ID)semid);
}

DDIM_USER_ER	ddim_user_custom_pol_sem(DdimUserCustom *self,DDIM_USER_ID semid)
{
	return (DDIM_USER_ER)OS_User_Pol_Sem((ID)semid);
}

DDIM_USER_ER	ddim_user_custom_wai_sem(DdimUserCustom *self,DDIM_USER_ID semid)
{
	return (DDIM_USER_ER)OS_User_Wai_Sem((ID)semid);
}

DDIM_USER_ER	ddim_user_custom_twai_sem(DdimUserCustom *self,DDIM_USER_ID semid, DDIM_USER_TMO tmout)
{
	return (DDIM_USER_ER)OS_User_Twai_Sem((ID)semid, (TMO)tmout);
}

DDIM_USER_ER	ddim_user_custom_ref_sem(DdimUserCustom *self,DDIM_USER_ID semid, TDdimUserRsem* pk_rsm)
{
	OS_USER_ER	ercd;
	T_OS_USER_RSEM			pkRefSem;

	ercd = OS_User_Ref_Sem((OS_USER_ID)semid, &pkRefSem);
	pk_rsm->wtskid = (DDIM_USER_ID)pkRefSem.wtskid;
	pk_rsm->semcnt = pkRefSem.semcnt;

	return (DDIM_USER_ER)ercd;
}

DDIM_USER_ER	ddim_user_custom_set_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN setptn)
{
	return (DDIM_USER_ER)OS_User_Set_Flg((OS_USER_ID)flagid, (OS_USER_FLGPTN)setptn);
}

DDIM_USER_ER	ddim_user_custom_clr_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN clrptn)
{
	return (DDIM_USER_ER)OS_User_Clr_Flg((OS_USER_ID)flagid, (OS_USER_FLGPTN)clrptn);
}

DDIM_USER_ER	ddim_user_custom_pol_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn)
{
	return (DDIM_USER_ER)OS_User_Pol_Flg((OS_USER_ID)flagid, (OS_USER_FLGPTN)waiptn, (OS_USER_MODE)wfmode, (OS_USER_FLGPTN*)p_flgptn);
}

DDIM_USER_ER	ddim_user_custom_wai_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn)
{
	return (DDIM_USER_ER)OS_User_Wai_Flg((OS_USER_ID)flagid, (OS_USER_FLGPTN)waiptn, (OS_USER_MODE)wfmode, (OS_USER_FLGPTN *)p_flgptn);
}

DDIM_USER_ER	ddim_user_custom_twai_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn, DDIM_USER_TMO timeout)
{
	return (DDIM_USER_ER)OS_User_Twai_Flg((OS_USER_ID)flagid, (OS_USER_FLGPTN)waiptn, (OS_USER_MODE)wfmode, (OS_USER_FLGPTN *)p_flgptn, (OS_USER_TMO)timeout);
}

DDIM_USER_ER	ddim_user_custom_ref_flg(DdimUserCustom *self,DDIM_USER_ID flgid, TDdimUserRflg* pkRflg)
{
	OS_USER_ER ercd;
	T_OS_USER_RFLG rflg;

	ercd = OS_User_Ref_Flg((OS_USER_ID)flgid, &rflg);

	pkRflg->wtskid = (DDIM_USER_ID)rflg.wtskid;
	pkRflg->flgptn = (DDIM_USER_FLGPTN)rflg.flgptn;

	return ercd;
}

DDIM_USER_ER	ddim_user_custom_get_tim(DdimUserCustom *self,DDIM_USER_SYSTIM* pSystime)
{
	return (DDIM_USER_ER)OS_User_Get_Tim((OS_USER_SYSTIM *)pSystime);
}

DDIM_USER_ER	ddim_user_custom_acre_cyc(DdimUserCustom *self,TDdimUserCcyc* pkCcyc)
{
	T_OS_USER_CCYC pkAcreCyc;

	pkAcreCyc.cycatr = (OS_USER_ATR)pkCcyc->cycatr;
	pkAcreCyc.exinf  = (OS_USER_VP_INT)pkCcyc->exinf;
	pkAcreCyc.cychdr = (OS_USER_FP)pkCcyc->cychdr;
	pkAcreCyc.cyctim = (OS_USER_RELTIM)pkCcyc->cyctim;
	pkAcreCyc.cycphs = (OS_USER_RELTIM)pkCcyc->cycphs;

	return (DDIM_USER_ER)OS_User_Acre_Cyc(&pkAcreCyc);
}

DDIM_USER_ER	ddim_user_custom_sta_cyc(DdimUserCustom *self,DDIM_USER_ID cycid)
{
	return (DDIM_USER_ER)OS_User_Sta_Cyc((OS_USER_ID)cycid);
}

DDIM_USER_ER	ddim_user_custom_stp_cyc(DdimUserCustom *self,DDIM_USER_ID cycid)
{
	return (DDIM_USER_ER)OS_User_Stp_Cyc((OS_USER_ID)cycid);
}

BOOL ddim_user_custom_sns_ctc(DdimUserCustom *sel)
{
	return OS_User_Sns_Ctx();
}

VOID ddim_user_custom_spin_lock(DdimUserCustom *self)
{

}

VOID ddim_user_custom_spin_unlock(DdimUserCustom *self)
{

}

VOID ddim_user_custom_l1l2cache_flush_all(DdimUserCustom *self)
{
//	Dd_CACHE_L1_Flush_Dcache_All();
//	Dd_CACHE_L2_Flush_Dcache_All();
	MMU_Flush_Dcache_All();
}

VOID ddim_user_custom_l1l2cache_clean_all(DdimUserCustom *self)
{
//	Dd_CACHE_L1_Clean_Dcache_All();
//	Dd_CACHE_L2_Clean_Dcache_All();
	MMU_Clean_Dcache_All();
}

VOID ddim_user_custom_l1l2cache_clean_flush_all(DdimUserCustom *self)
{
//	Dd_CACHE_L1_Clean_Flush_Dcache_All();
//	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	MMU_Flush_Clean_Dcache_All();
}

VOID ddim_user_custom_l1l2cache_flush_addr(DdimUserCustom *self,kuint32 address, kuint32 size)
{
//	Dd_CACHE_L1_Flush_Dcache_Addr(address, size);
//	Dd_CACHE_L2_Flush_Dcache_Addr(address, size);
	MMU_Flush_Dcache_Addr(address, size);
}

VOID ddim_user_custom_l1l2cache_clean_addr(DdimUserCustom *self,kuint32 address, kuint32 size)
{
//	Dd_CACHE_L1_Clean_Dcache_Addr(address, size);
//	Dd_CACHE_L2_Clean_Dcache_Addr(address, size);
	MMU_Clean_Dcache_Addr(address, size);
}

VOID ddim_user_custom_l1l2cache_clean_flush_addr(DdimUserCustom *self,kuint32 address, kuint32 size)
{
//	Dd_CACHE_L1_Clean_Flush_Dcache_Addr(address, size);
//	Dd_CACHE_L2_Clean_Flush_Dcache_Addr(address, size);
	MMU_Flush_Clean_Dcache_Addr(address, size);
}

DdimUserCustomTest* ddim_user_custom_test_new(void)
{
//	DdimUserCustomTest* self = k_object_new_with_private(DDIM_TYPE_USER_CUSTOM_TEST, sizeof(DdimUserCustomTestPrivate));

	return self;
}

