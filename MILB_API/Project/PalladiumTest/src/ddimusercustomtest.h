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


#ifndef __DDIM_USER_CUSTOM_TEST_H__
#define __DDIM_USER_CUSTOM_TEST_H__


#include <klib.h>


#define DDIM_TYPE_USER_CUSTOM_TEST                  (ddim_user_custom_test_get_type())
#define DDIM_USER_CUSTOM_TEST(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, DdimUserCustomTest)) 
#define DDIM_IS_USER_CUSTOM_TEST(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, DDIM_TYPE_USER_CUSTOM_TEST)) 


typedef struct _DdimUserCustomTest DdimUserCustomTest;
typedef struct _DdimUserCustomTestPrivate DdimUserCustomTestPrivate;

struct _DdimUserCustomTest 
{
	KObject parent;
};

KConstType ddim_user_custom_test_get_type(void);
DdimUserCustomTest* ddim_user_custom_test_new(void);

/*
 * PUBLIC
 */

DDIM_USER_ER			ddim_user_custom_tslp_tsk(DdimUserCustom *self,DDIM_USER_TMO timeout);
VOID							ddim_user_custom_ext_tsk(DdimUserCustom *self);
DDIM_USER_ER			ddim_user_custom_dly_tsk(DdimUserCustom *self,DDIM_USER_RELTIM delaytime);
DDIM_USER_ER			ddim_user_custom_sig_sem(DdimUserCustom *self,DDIM_USER_ID semid);
DDIM_USER_ER			ddim_user_custom_pol_sem(DdimUserCustom *self,DDIM_USER_ID semid);
DDIM_USER_ER			ddim_user_custom_wai_sem(DdimUserCustom *self,DDIM_USER_ID semid);
DDIM_USER_ER			ddim_user_custom_twai_sem(DdimUserCustom *self,DDIM_USER_ID semid, DDIM_USER_TMO tmout);
DDIM_USER_ER			ddim_user_custom_ref_sem(DdimUserCustom *self,DDIM_USER_ID semid, TDdimUserRsem* pk_rsm);
DDIM_USER_ER			ddim_user_custom_set_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN setptn);
DDIM_USER_ER			ddim_user_custom_clr_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN clrptn);
DDIM_USER_ER			ddim_user_custom_pol_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn);
DDIM_USER_ER			ddim_user_custom_wai_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn);
DDIM_USER_ER			ddim_user_custom_twai_flg(DdimUserCustom *self,DDIM_USER_ID flagid, DDIM_USER_FLGPTN waiptn, DDIM_USER_MODE wfmode, DDIM_USER_FLGPTN* p_flgptn, DDIM_USER_TMO timeout);
DDIM_USER_ER			ddim_user_custom_ref_flg(DdimUserCustom *self,DDIM_USER_ID flgid, TDdimUserRflg* pkRflg);
DDIM_USER_ER			ddim_user_custom_get_tim(DdimUserCustom *self,DDIM_USER_SYSTIM* pSystime);
DDIM_USER_ER			ddim_user_custom_acre_cyc(DdimUserCustom *self,TDdimUserCcyc* pkCcyc);
DDIM_USER_ER			ddim_user_custom_sta_cyc(DdimUserCustom *self,DDIM_USER_ID cycid);
DDIM_USER_ER			ddim_user_custom_stp_cyc(DdimUserCustom *self,DDIM_USER_ID cycid);
BOOL 							ddim_user_custom_sns_ctc(DdimUserCustom *sel);
VOID            				ddim_user_custom_spin_lock(DdimUserCustom *self);
VOID            				ddim_user_custom_spin_unlock(DdimUserCustom *self);
VOID            				ddim_user_custom_l1l2cache_flush_all(DdimUserCustom *self);
VOID            				ddim_user_custom_l1l2cache_clean_all(DdimUserCustom *self);
VOID            				ddim_user_custom_l1l2cache_clean_flush_all(DdimUserCustom *self);
VOID           				ddim_user_custom_l1l2cache_flush_addr(DdimUserCustom *self,kuint32 address, kuint32 size);
VOID            				ddim_user_custom_l1l2cache_clean_addr(DdimUserCustom *self,kuint32 address, kuint32 size);
VOID            				ddim_user_custom_l1l2cache_clean_flush_addr(DdimUserCustom *self,kuint32 address, kuint32 size);

#endif /* __DDIM_USER_CUSTOM_TEST_H__ */
