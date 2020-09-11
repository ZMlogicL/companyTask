/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-09
*@author : 刘嫚鶄
*@brief : DdimUserCustom
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "../include/os_user_custom.h"
#include "dd_arm.h"
#include "dd_cache.h"

#include "ddimusercustom.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdimUserCustom, ddim_user_custom)
#define DDIM_USER_CUSTOM_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdimUserCustomPrivate, DDIM_TYPE_USER_CUSTOM))

struct _DdimUserCustomPrivate
{

};

static void ddim_user_custom_constructor(DdimUserCustom *self)
{
//	DdimUserCustomPrivate *priv = DDIM_USER_CUSTOM_GET_PRIVATE(self);
}

static void ddim_user_custom_destructor(DdimUserCustom *self)
{
//	DdimUserCustomPrivate *priv = DDIM_USER_CUSTOM_GET_PRIVATE(self);
}

extern void MMU_Flush_Dcache_All(void);//索喜.a库的东西
extern void MMU_Clean_Dcache_All(void);//索喜.a库的东西
extern void MMU_Flush_Clean_Dcache_All(void);//索喜.a库的东西
extern void MMU_Flush_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西
extern void MMU_Clean_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西
extern void MMU_Flush_Clean_Dcache_Addr(unsigned address, unsigned size);//索喜.a库的东西

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

DDIM_USER_ER	ddim_user_custom_ref_sem(DdimUserCustom *self,DDIM_USER_ID semid, T_DDIM_USER_RSEM* pk_rsm)
{
	OS_USER_ER	ercd;
	T_OS_USER_RSEM			pk_ref_sem;

	ercd = OS_User_Ref_Sem((OS_USER_ID)semid, &pk_ref_sem);
	pk_rsm->wtskid = (DDIM_USER_ID)pk_ref_sem.wtskid;
	pk_rsm->semcnt = pk_ref_sem.semcnt;

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

DDIM_USER_ER	ddim_user_custom_ref_flg(DdimUserCustom *self,DDIM_USER_ID flgid, T_DDIM_USER_RFLG* pk_rflg)
{
	OS_USER_ER ercd;
	T_OS_USER_RFLG rflg;

	ercd = OS_User_Ref_Flg((OS_USER_ID)flgid, &rflg);

	pk_rflg->wtskid = (DDIM_USER_ID)rflg.wtskid;
	pk_rflg->flgptn = (DDIM_USER_FLGPTN)rflg.flgptn;

	return ercd;
}

DDIM_USER_ER	ddim_user_custom_get_tim(DdimUserCustom *self,DDIM_USER_SYSTIM* p_systime)
{
	return (DDIM_USER_ER)OS_User_Get_Tim((OS_USER_SYSTIM *)p_systime);
}

DDIM_USER_ER	ddim_user_custom_acre_cyc(DdimUserCustom *self,T_DDIM_USER_CCYC* pk_ccyc)
{
	T_OS_USER_CCYC pk_acre_cyc;

	pk_acre_cyc.cycatr = (OS_USER_ATR)pk_ccyc->cycatr;
	pk_acre_cyc.exinf  = (OS_USER_VP_INT)pk_ccyc->exinf;
	pk_acre_cyc.cychdr = (OS_USER_FP)pk_ccyc->cychdr;
	pk_acre_cyc.cyctim = (OS_USER_RELTIM)pk_ccyc->cyctim;
	pk_acre_cyc.cycphs = (OS_USER_RELTIM)pk_ccyc->cycphs;

	return (DDIM_USER_ER)OS_User_Acre_Cyc(&pk_acre_cyc);
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

VOID ddim_user_custom_spin_unlock(DdimUserCustom *self,VOID)
{

}

VOID ddim_user_custom_l1l2cache_flush_all(DdimUserCustom *self,VOID)
{
//	Dd_CACHE_L1_Flush_Dcache_All();
//	Dd_CACHE_L2_Flush_Dcache_All();
	MMU_Flush_Dcache_All();
}

VOID ddim_user_custom_l1l2cache_clean_all(DdimUserCustom *self,VOID)
{
//	Dd_CACHE_L1_Clean_Dcache_All();
//	Dd_CACHE_L2_Clean_Dcache_All();
	MMU_Clean_Dcache_All();
}

VOID ddim_user_custom_l1l2cache_clean_flush_all(DdimUserCustom *self,VOID)
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

DdimUserCustom* ddim_user_custom_new(void)
{
	DdimUserCustom* self = k_object_new_with_private(DDIM_TYPE_USER_CUSTOM, sizeof(DdimUserCustomPrivate));

	return self;
}

