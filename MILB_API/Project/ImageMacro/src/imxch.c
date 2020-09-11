/*
 * imxch.c
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :卢樊
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、interrupt setting process api
*2、
*@version:        1.0.0
*/

#if defined(CO_ACT_ICLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "dd_arm.h"

#include "ddim_user_custom.h"
#include "jdsxch.h"

#include <string.h>

#include "imxch1.h"
#include "imxch2.h"
#include "imxch.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImXch, im_xch)
#define IM_XCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImXchPrivate,IM_TYPE_XCH))



struct _ImXchPrivate
{
	int a;
};


static void im_xch_constructor(ImXch *self)
{
//	ImXchPrivate *priv = IM_XCH_GET_PRIVATE(self);
}

static void im_xch_destructor(ImXch *self)
{
}


#ifdef CO_ACT_XCH_PCLOCK
static volatile UCHAR S_G_IM_XCH_PCLK_CTRL_CNT = 0;
#endif // CO_ACT_XCH_PCLOCK
#ifdef CO_ACT_XCH_ICLOCK
static volatile UCHAR S_G_IM_XCH_ICLK_CTRL_CNT = 0;
#endif // CO_ACT_XCH_ICLOCK

/*
 DECLS
 */
static VOID imXchOnIclk( VOID );
static VOID imXchOffIclk( VOID );
static VOID imXchInthandSub( E_IM_XCH_CH_SEL xch );
static INT32 imXchStartProcess( E_IM_XCH_CH_SEL xch );


/*
 IMPL
 */

static VOID imXchOnIclk( VOID )
{
#ifdef CO_ACT_XCH_ICLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_XCH_ICLK_CTRL_CNT, D_IM_XCH_AXCLK_REG_ADDR, ~D_IM_XCH_ICLK_REG_BIT );
#endif	// CO_ACT_XCH_ICLOCK
}

static VOID imXchOffIclk( VOID )
{
#ifdef CO_ACT_XCH_ICLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_XCH_ICLK_CTRL_CNT, D_IM_XCH_AXCLK_REG_ADDR, D_IM_XCH_ICLK_REG_BIT );
#endif	// CO_ACT_XCH_ICLOCK
}

static VOID imXchInthandSub( E_IM_XCH_CH_SEL xch )
{
	DDIM_USER_ER	ercd;

	ImXch* imXch = im_xch_get();


	if( xch == E_IM_XCH_CH_SEL_0 ){
		// X0ch
		ercd = DDIM_User_Set_Flg( FID_IM_XCH, D_IM_XCH_FLG_0_WAIT_END );
		if( ercd != D_DDIM_USER_E_OK ){
			// DDIM_User_Set_Flg error
			Ddim_Print(("I:im_xch_int_handler. DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}

#ifdef CO_DEBUG_ON_PC
//		Ddim_Print(("I:imXchInthandSub. X0Ch OK\n"));
#endif //CO_DEBUG_ON_PC

	}
	else{
		// X1ch
		ercd = DDIM_User_Set_Flg( FID_IM_XCH, D_IM_XCH_FLG_1_WAIT_END );
		if( ercd != D_DDIM_USER_E_OK ){
			// DDIM_User_Set_Flg error
			Ddim_Print(("I:im_xch_int_handler. DDIM_User_Set_Flg error. ercd = %d\n", ercd));
		}

#ifdef CO_DEBUG_ON_PC
//		Ddim_Print(("I:imXchInthandSub. X1Ch OK\n"));
#endif //CO_DEBUG_ON_PC

	}

	if( (im_xch_get_gIM_Xch_Mng_Save(imXch,xch).syncType == E_IM_XCH_SYNC_TYPE_ASYNC) && (im_xch_get_gIM_Xch_Mng_Save(imXch,xch).pCallBack) ){
		// Call Back function
		((VOID (*)()) im_xch_get_gIM_Xch_Mng_Save(imXch,xch).pCallBack)();
	}
}

static INT32 imXchStartProcess( E_IM_XCH_CH_SEL xch )
{
	DDIM_USER_ER ercd;
	DDIM_USER_FLGPTN flg_ptn;

	ImXch* imXch = im_xch_get();


	if( xch == E_IM_XCH_CH_SEL_0 ){
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		// Set parameter
		IO_XCH.XCHCTL0.XMD.bit.XMD				= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xmd;
		IO_XCH.XCHCTL0.XFDT.bit.XFDT			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xfdt;
		IO_XCH.XCHCTL0.XDTYPE.bit.XSDTYPE		= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype;
		IO_XCH.XCHCTL0.XDTYPE.bit.XDDTYPE		= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype;
		IO_XCH.XCHCTL0.XCYC.bit.XHCYC			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc;
		IO_XCH.XCHCTL0.XCYC.bit.XVCYC			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc;
		IO_XCH.XCHCTL0.XHEN.bit.XHEN			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen;
		IO_XCH.XCHCTL0.XVEN.bit.XVEN			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven;
		IO_XCH.XCHCTL0.XSHW.bit.XSHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw;
		IO_XCH.XCHCTL0.XGHW.bit.XGHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xghw;
		IO_XCH.XCHCTL0.XDHW.bit.XDHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdhw;
		IO_XCH.XCHCTL0.XDVW.bit.XDVW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdvw;
		IO_XCH.XCHCTL0.XSA.word					= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa;
		IO_XCH.XCHCTL0.XDA.word					= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xda;
		IO_XCH.XHISTG0.bit.XHCNT0				= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcnt;

#ifdef CO_IM_XCH_DEBUG
		Ddim_Print(("IO_XCH.XCHCTL0.XMD.bit.XMD        =%d\n", IO_XCH.XCHCTL0.XMD.bit.XMD));
		Ddim_Print(("IO_XCH.XCHCTL0.XFDT.bit.XFDT      =%d\n", IO_XCH.XCHCTL0.XFDT.bit.XFDT));
		Ddim_Print(("IO_XCH.XCHCTL0.XDTYPE.bit.XSDTYPE =%d\n", IO_XCH.XCHCTL0.XDTYPE.bit.XSDTYPE));
		Ddim_Print(("IO_XCH.XCHCTL0.XDTYPE.bit.XDDTYPE =%d\n", IO_XCH.XCHCTL0.XDTYPE.bit.XDDTYPE));
		Ddim_Print(("IO_XCH.XCHCTL0.XCYC.bit.XHCYC     =%d\n", IO_XCH.XCHCTL0.XCYC.bit.XHCYC));
		Ddim_Print(("IO_XCH.XCHCTL0.XCYC.bit.XVCYC     =%d\n", IO_XCH.XCHCTL0.XCYC.bit.XVCYC));
		Ddim_Print(("IO_XCH.XCHCTL0.XHEN.bit.XHEN      =0x%lX\n", IO_XCH.XCHCTL0.XHEN.bit.XHEN));
		Ddim_Print(("IO_XCH.XCHCTL0.XVEN.bit.XVEN      =0x%lX\n", IO_XCH.XCHCTL0.XVEN.bit.XVEN));
		Ddim_Print(("IO_XCH.XCHCTL0.XSHW.bit.XSHW      =%d\n", IO_XCH.XCHCTL0.XSHW.bit.XSHW));
		Ddim_Print(("IO_XCH.XCHCTL0.XGHW.bit.XGHW      =%d\n", IO_XCH.XCHCTL0.XGHW.bit.XGHW));
		Ddim_Print(("IO_XCH.XCHCTL0.XDHW.bit.XDHW      =%d\n", IO_XCH.XCHCTL0.XDHW.bit.XDHW));
		Ddim_Print(("IO_XCH.XCHCTL0.XDVW.bit.XDVW      =%d\n", IO_XCH.XCHCTL0.XDVW.bit.XDVW));
		Ddim_Print(("IO_XCH.XCHCTL0.XSA.word           =0x%lX\n", IO_XCH.XCHCTL0.XSA.word));
		Ddim_Print(("IO_XCH.XCHCTL0.XDA.word           =0x%lX\n", IO_XCH.XCHCTL0.XDA.word));
		Ddim_Print(("IO_XCH.XHISTG0.bit.XHCNT0         =%d\n", IO_XCH.XHISTG0.bit.XHCNT0));
#endif

		// X0ch
		ercd = DDIM_User_Clr_Flg( FID_IM_XCH, ~D_IM_XCH_FLG_0_WAIT_END );
		if( ercd != D_DDIM_USER_E_OK ){
			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();
			// DDIM_User_Clr_Flg error
			Ddim_Print(("I:imXchStartProcess. DDIM_User_Clr_Flg error. ercd = %d\n", ercd));
			return D_IM_XCH_NG;
		}

		// X0ch start
		IO_XCH.XCHCTL0.XTRG.bit.XTRG = D_IM_XCH_START;

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();

		if( im_xch_get_gIM_Xch_Mng_Save(imXch,xch).syncType == E_IM_XCH_SYNC_TYPE_SYNC ){
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(("Call Im_Xch_Int_Handler() for PC route check.\n"));
			IO_XCH.XCHICE.bit.XE0	= 1;
			IO_XCH.XCHICF.bit.__XF0	= 1;
			IO_XCH.XCHCTL0.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
			im_xch_int_handler();
#endif

			// Xch end wait
			ercd = DDIM_User_Twai_Flg( FID_IM_XCH, D_IM_XCH_FLG_0_WAIT_END, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME );
			if( ercd != D_DDIM_USER_E_OK ){
				// DDIM_User_Twai_Flg error
				Ddim_Print(("I:imXchStartProcess. DDIM_User_Twai_Flg error. ercd = %d\n", ercd));
				return D_IM_XCH_NG;
			}
		}
	}
	else {
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		IO_XCH.XCHCTL1.XMD.bit.XMD				= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xmd;
		IO_XCH.XCHCTL1.XFDT.bit.XFDT			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xfdt;
		IO_XCH.XCHCTL1.XDTYPE.bit.XSDTYPE		= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype;
		IO_XCH.XCHCTL1.XDTYPE.bit.XDDTYPE		= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype;
		IO_XCH.XCHCTL1.XCYC.bit.XHCYC			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc;
		IO_XCH.XCHCTL1.XCYC.bit.XVCYC			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc;
		IO_XCH.XCHCTL1.XHEN.bit.XHEN			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen;
		IO_XCH.XCHCTL1.XVEN.bit.XVEN			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven;
		IO_XCH.XCHCTL1.XSHW.bit.XSHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw;
		IO_XCH.XCHCTL1.XGHW.bit.XGHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xghw;
		IO_XCH.XCHCTL1.XDHW.bit.XDHW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdhw;
		IO_XCH.XCHCTL1.XDVW.bit.XDVW			= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdvw;
		IO_XCH.XCHCTL1.XSA.word					= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa;
		IO_XCH.XCHCTL1.XDA.word					= im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xda;

#ifdef CO_IM_XCH_DEBUG
		Ddim_Print(("IO_XCH.XCHCTL1.XMD.bit.XMD        =%d\n", IO_XCH.XCHCTL1.XMD.bit.XMD));
		Ddim_Print(("IO_XCH.XCHCTL1.XFDT.bit.XFDT      =%d\n", IO_XCH.XCHCTL1.XFDT.bit.XFDT));
		Ddim_Print(("IO_XCH.XCHCTL1.XDTYPE.bit.XSDTYPE =%d\n", IO_XCH.XCHCTL1.XDTYPE.bit.XSDTYPE));
		Ddim_Print(("IO_XCH.XCHCTL1.XDTYPE.bit.XDDTYPE =%d\n", IO_XCH.XCHCTL1.XDTYPE.bit.XDDTYPE));
		Ddim_Print(("IO_XCH.XCHCTL1.XCYC.bit.XHCYC     =%d\n", IO_XCH.XCHCTL1.XCYC.bit.XHCYC));
		Ddim_Print(("IO_XCH.XCHCTL1.XCYC.bit.XVCYC     =%d\n", IO_XCH.XCHCTL1.XCYC.bit.XVCYC));
		Ddim_Print(("IO_XCH.XCHCTL1.XHEN.bit.XHEN      =0x%lX\n", IO_XCH.XCHCTL1.XHEN.bit.XHEN));
		Ddim_Print(("IO_XCH.XCHCTL1.XVEN.bit.XVEN      =0x%lX\n", IO_XCH.XCHCTL1.XVEN.bit.XVEN));
		Ddim_Print(("IO_XCH.XCHCTL1.XSHW.bit.XSHW      =%d\n", IO_XCH.XCHCTL1.XSHW.bit.XSHW));
		Ddim_Print(("IO_XCH.XCHCTL1.XGHW.bit.XGHW      =%d\n", IO_XCH.XCHCTL1.XGHW.bit.XGHW));
		Ddim_Print(("IO_XCH.XCHCTL1.XDHW.bit.XDHW      =%d\n", IO_XCH.XCHCTL1.XDHW.bit.XDHW));
		Ddim_Print(("IO_XCH.XCHCTL1.XDVW.bit.XDVW      =%d\n", IO_XCH.XCHCTL1.XDVW.bit.XDVW));
		Ddim_Print(("IO_XCH.XCHCTL1.XSA.word           =0x%lX\n", IO_XCH.XCHCTL1.XSA.word));
		Ddim_Print(("IO_XCH.XCHCTL1.XDA.word           =0x%lX\n", IO_XCH.XCHCTL1.XDA.word));
#endif

		// X1ch
		ercd = DDIM_User_Clr_Flg( FID_IM_XCH, ~D_IM_XCH_FLG_1_WAIT_END );
		if( ercd != D_DDIM_USER_E_OK ){
			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();
			// DDIM_User_Clr_Flg error
			Ddim_Print(("I:imXchStartProcess. DDIM_User_Clr_Flg error. ercd = %d\n", ercd));
			return D_IM_XCH_NG;
		}

		// X1ch start
		IO_XCH.XCHCTL1.XTRG.bit.XTRG = D_IM_XCH_START;

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();

		if( im_xch_get_gIM_Xch_Mng_Save(imXch,xch).syncType == E_IM_XCH_SYNC_TYPE_SYNC ){
#ifdef CO_DEBUG_ON_PC
//			Ddim_Print(("Call Im_Xch_Int_Handler() for PC route check.\n"));
			IO_XCH.XCHICE.bit.XE1	= 1;
			IO_XCH.XCHICF.bit.__XF1	= 1;
			IO_XCH.XCHCTL1.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
			im_xch_int_handler();
#endif
			// XCH end wait
			ercd = DDIM_User_Twai_Flg( FID_IM_XCH, D_IM_XCH_FLG_1_WAIT_END, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME );
			if( ercd != D_DDIM_USER_E_OK ){
				// DDIM_User_Twai_Flg error
				Ddim_Print(("I:imXchStartProcess. DDIM_User_Twai_Flg error. ercd = %d\n", ercd));
				return D_IM_XCH_NG;
			}
		}
	}

	return D_IM_XCH_OK;
}

/*
PUBLIC
 */

VOID im_xch_off_pclk(ImXch*self )
{
#ifdef CO_ACT_XCH_PCLOCK
	Dd_Top_Stop_Clock( (UCHAR*)&S_G_IM_XCH_PCLK_CTRL_CNT, D_IM_XCH_APCLK_REG_ADDR, D_IM_XCH_PCLK_REG_BIT );
#endif	// CO_ACT_XCH_PCLOCK
}

VOID im_xch_on_pclk( ImXch*self )
{
#ifdef CO_ACT_XCH_PCLOCK
	Dd_Top_Start_Clock( (UCHAR*)&S_G_IM_XCH_PCLK_CTRL_CNT, D_IM_XCH_APCLK_REG_ADDR, ~D_IM_XCH_PCLK_REG_BIT );
#endif	// CO_ACT_XCH_PCLOCK
}


INT32 im_xch_softreset( ImXch*self )
{
	if( (IO_XCH.XCHCTL0.XTRG.bit.XTRG == D_IM_XCH_STOPPED) && (IO_XCH.XCHCTL1.XTRG.bit.XTRG == D_IM_XCH_STOPPED) ){
		// Software reset
		IO_XCH.SR.bit.SR = 1;
		Im_XCH_Dsb();

		// AXICLK        = MAX 200.0MHz(400/2)	MIN 41.7MHz(250/6)
		// APB clock     = MAX  66.7MHz			MIN 20.8MHz
		// --> Lowest-speed clock setting( AXICLK:83.33  APBCLK:41.67 )
		//     Please refer to chapter 6.3.6.1 of MB86S27A LSI specification.
		// -->   ( (1/AXICLK)  / (1/APB clock)  ) * 2 + 1
		//     = ( (1/83.33)   / (1/41.67)      ) * 2 + 1
		//     = ( (0.0120004800...) / (0.0239980802...) ) * 2 + 1
		//     = 2.0001200048  => 3 APB cycle

		// wait
		IO_XCH.SR.word;	// 2 cycle
		IO_XCH.SR.word;	// 2 cycle

		Im_XCH_Dsb();

		// Software reset release
		IO_XCH.SR.bit.SR = 0;
		Im_XCH_Dsb();

		// wait
		IO_XCH.SR.word;	// 2 cycle
		IO_XCH.SR.word;	// 2 cycle

		Im_XCH_Dsb();
	}
	else{
		return D_IM_XCH_MACRO_BUSY_NG;
	}

	return D_IM_XCH_OK;
}

INT32 im_xch_open( ImXch*self,E_IM_XCH_CH_SEL xch, INT32 tmout )
{
	DDIM_USER_ER	ercd;

#ifdef CO_PARAM_CHECK
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ){
		Ddim_Assertion(("I:im_xch_open: input param error. tmout = %x\n", tmout));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif

	if( D_DDIM_USER_SEM_WAIT_POL == tmout ){
		ercd = DDIM_User_Pol_Sem( SID_IM_XCH(xch) );						// pol_sem()
	}
	else{
		ercd = DDIM_User_Twai_Sem( SID_IM_XCH(xch), (DDIM_USER_TMO)tmout );	// twai_sem()
	}

	if( D_DDIM_USER_E_OK != ercd ){
		// twai_sem error
		if( D_DDIM_USER_E_TMOUT == ercd ){
			// Semaphore Get Time Out
			Ddim_Print(("I:im_xch_open() Error : Semaphore Get Time Out. ercd = %d\n", ercd));
			return D_IM_XCH_SEM_TIMEOUT;
		}
		// Semaphore Get Error
		Ddim_Print(("I:im_xch_open() Error : Semaphore Get Error. ercd = %d\n", ercd));
		return D_IM_XCH_SEM_NG;
	}

	imXchOnIclk();
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}


VOID im_xch_init( ImXch*self )
{
	im_xch_on_pclk(NULL);	// PCLK on

	// Software reset release
	IO_XCH.SR.bit.SR = 0;
	Im_XCH_Dsb();

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("IO_XCH.SR.bit.SR        =%d\n", IO_XCH.SR.bit.SR));
#endif

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

#ifdef CO_DEBUG_ON_PC
	IO_XCH.XCHCTL0.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
	IO_XCH.XCHCTL1.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
#endif

	return;
}

INT32 im_xch_start_sync( ImXch*self,E_IM_XCH_CH_SEL xch )
{
	INT32 ercd;

	ImXch* imXch = im_xch_get();


	if( xch == E_IM_XCH_CH_SEL_0 ){
		//X0ch
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		// Check Xch running
		if( IO_XCH.XCHCTL0.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){

			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();

			Ddim_Print(("I:im_xch_start_sync: Macro busy error.\n"));
			return D_IM_XCH_MACRO_BUSY_NG;
		}

		IO_XCH.XCHICF.word		&= D_IM_XCH_ICF_XF0_OFF;
		IO_XCH.XCHICE.bit.XE0	= 1;
		Im_XCH_Dsb();

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();
	}
	else{
		// X1ch
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		// Check Xch running
		if( IO_XCH.XCHCTL1.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){

			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();

			Ddim_Print(("I:im_xch_start_sync: Macro busy error.\n"));
			return D_IM_XCH_MACRO_BUSY_NG;
		}

		IO_XCH.XCHICF.word		&= D_IM_XCH_ICF_XF1_OFF;
		IO_XCH.XCHICE.bit.XE1	= 1;
		Im_XCH_Dsb();

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();
	}

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).syncType = E_IM_XCH_SYNC_TYPE_SYNC;

	// Processing Start
	ercd = imXchStartProcess( xch );
	if( ercd != D_IM_XCH_OK ){
		Ddim_Print(("I:im_xch_start_sync: imXchStartProcess error. ercd = 0x%X\n", ercd));
		return D_IM_XCH_NG;
	}

	return D_IM_XCH_OK;
}

INT32 im_xch_start_async( ImXch*self,E_IM_XCH_CH_SEL xch )
{
	INT32 ercd;

	ImXch* imXch = im_xch_get();


	if( xch == E_IM_XCH_CH_SEL_0 ){
		// X0ch
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		// Check Xch running
		if( IO_XCH.XCHCTL0.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){

			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();

			Ddim_Print(("I:im_xch_start_async: Macro busy error.\n"));
			return D_IM_XCH_MACRO_BUSY_NG;
		}

		IO_XCH.XCHICF.word &= D_IM_XCH_ICF_XF0_OFF;
		IO_XCH.XCHICE.bit.XE0 = 1;
		Im_XCH_Dsb();

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();
	}
	else{
		// X1ch
		im_xch_on_pclk(NULL);	// PCLK on
		Im_XCH_Dsb();

		// Check Xch running
		if( IO_XCH.XCHCTL1.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){
			im_xch_off_pclk(NULL);	// PCLK off
			Im_XCH_Dsb();

			Ddim_Print(("I:im_xch_start_async: Macro busy error.\n"));
			return D_IM_XCH_MACRO_BUSY_NG;
		}

		IO_XCH.XCHICF.word &= D_IM_XCH_ICF_XF1_OFF;
		IO_XCH.XCHICE.bit.XE1 = 1;
		Im_XCH_Dsb();

		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();
	}

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).syncType = E_IM_XCH_SYNC_TYPE_ASYNC;

	ercd = imXchStartProcess( xch );
	if( ercd != D_IM_XCH_OK ){
		Ddim_Print(("I:im_xch_start_async: imXchStartProcess error. ercd = 0x%X\n", ercd));
		return D_IM_XCH_NG;
	}

	return D_IM_XCH_OK;
}

INT32 im_xch_get_histogram( ImXch*self,ULONG* histogram_buf )
{
	UINT32 cnt;

#ifdef CO_PARAM_CHECK
	if( histogram_buf == NULL ){
		// histogram_buf is Error because of NULL
		Ddim_Assertion(("I:Im_X0ch_Get_Histgram: Null check error. histogram_buf = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	 if( IO_XCH.XCHCTL0.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){
		im_xch_off_pclk(NULL);	// PCLK off
		Im_XCH_Dsb();

		Ddim_Print(("I:im_xch_get_histogram: Macro busy error.\n"));
		return D_IM_XCH_MACRO_BUSY_NG;
	}

	// Read access enable
	IO_XCH.XHISTG0.bit.XHREN0 = 1;
	Im_XCH_Dsb();

	for( cnt = 0; cnt < 256; cnt++ ){
		histogram_buf[cnt] = IO_XCH.XHBF[cnt].word;
	}

	// Read access disable
	IO_XCH.XHISTG0.bit.XHREN0 = 0;

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch_wait_end( ImXch*self,E_IM_XCH_CH_SEL xch )
{
	DDIM_USER_FLGPTN flg_ptn;
	DDIM_USER_ER ercd;

	if( xch == E_IM_XCH_CH_SEL_0 ){
		// X0ch
		ercd = DDIM_User_Twai_Flg( FID_IM_XCH, D_IM_XCH_FLG_0_WAIT_END, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_xch_wait_end: DDIM_User_Twai_Flg error. ercd = %d\n", ercd));
			return D_IM_XCH_NG;
		}
	}
	else{
		// X1ch
		ercd = DDIM_User_Twai_Flg( FID_IM_XCH, D_IM_XCH_FLG_1_WAIT_END, D_DDIM_USER_TWF_ORW, &flg_ptn, D_DDIM_WAIT_END_TIME );
		if( ercd != D_DDIM_USER_E_OK ){
			Ddim_Print(("I:im_xch_wait_end: DDIM_User_Twai_Flg error. ercd = %d\n", ercd));
			return D_IM_XCH_NG;
		}
	}
	return D_IM_XCH_OK;
}

INT32 im_xch_close( ImXch*self,E_IM_XCH_CH_SEL xch )
{
	DDIM_USER_ER ercd;

	// ICLK off
	imXchOffIclk();
	Im_XCH_Dsb();

	ercd = DDIM_User_Sig_Sem( SID_IM_XCH(xch) );				// sig_sem()

	if( D_DDIM_USER_E_OK != ercd ){
		// sig_sem error
		Ddim_Print(("I:im_xch_close: Semaphore error : ercd = %d\n", ercd));
		return D_IM_XCH_SEM_NG;
	}

	return D_IM_XCH_OK;
}

INT32 im_xch_stop( ImXch*self )
{
	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( IO_XCH.XCHCTL0.XTRG.bit.XTRG == D_IM_XCH_RUNNING ){
		// Macro Stop
		IO_XCH.XCHCTL0.XTRG.bit.XTRG = D_IM_XCH_STOP;
		Im_XCH_Dsb();

		while( IO_XCH.XCHCTL0.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){

#ifdef CO_DEBUG_ON_PC
			IO_XCH.XCHCTL0.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
#endif //CO_DEBUG_ON_PC

			// Wait until stopped
			DDIM_User_Dly_Tsk(1);
		}
	}
	if( IO_XCH.XCHCTL1.XTRG.bit.XTRG == D_IM_XCH_RUNNING ){
		// Macro Stop
		IO_XCH.XCHCTL1.XTRG.bit.XTRG = D_IM_XCH_STOP;
		Im_XCH_Dsb();

		while( IO_XCH.XCHCTL1.XTRG.bit.XTRG != D_IM_XCH_STOPPED ){
#ifdef CO_DEBUG_ON_PC
			IO_XCH.XCHCTL1.XTRG.bit.XTRG = D_IM_XCH_STOPPED;
#endif //CO_DEBUG_ON_PC

			// Wait until stopped
			DDIM_User_Dly_Tsk(1);
		}
	}

	// Soft reset
	im_xch_softreset(NULL);

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

VOID im_xch_int_handler( VOID )
{
	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( IO_XCH.XCHICE.bit.XE0 == 0 && IO_XCH.XCHICE.bit.XE1 == 0 ){
		// Unknown channel error
		Ddim_Print(("I:im_xch_int_handler: Unknown channel error\n"));
	}
	else if( IO_XCH.XCHICF.bit.__XF0 == 0 && IO_XCH.XCHICF.bit.__XF1 == 0 ){
		// Xch doesn't start error
		Ddim_Print(("I:im_xch_int_handler: Xch doesn't end error\n"));
	}
	else{
		if( IO_XCH.XCHICE.bit.XE0 == 1 ){
			// X0ch
			if( (IO_XCH.XCHICE.bit.XE0 == 1) && (IO_XCH.XCHICF.bit.__XF0 == 1) ){
				IO_XCH.XCHICF.word &= D_IM_XCH_ICF_XF0_OFF;	// clear interrupt factor flag X0ch
				imXchInthandSub( E_IM_XCH_CH_SEL_0 );
			}
		}
		if( IO_XCH.XCHICE.bit.XE1 == 1 ){
			// X1ch
			if( (IO_XCH.XCHICE.bit.XE1 == 1) && (IO_XCH.XCHICF.bit.__XF1 == 1) ){
				IO_XCH.XCHICF.word &= D_IM_XCH_ICF_XF1_OFF;	// clear interrupt factor flag X1ch
				imXchInthandSub( E_IM_XCH_CH_SEL_1 );
			}
		}
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();
}

INT32 im_xch_fill( ImXch*self,E_IM_XCH_CH_SEL xch, UCHAR fill_data, USHORT gl_width, UINT32 dst_addr, USHORT width, USHORT lines )
{
	INT32 ret;
	ImXchCtrlCmn	xch_ctrl_cmn;

#ifdef CO_PARAM_CHECK
	if( (xch != E_IM_XCH_CH_SEL_0) && (xch != E_IM_XCH_CH_SEL_1) ){
		// Channel number error
		Ddim_Assertion(("I:im_xch_fill: Channel number error. xch = %d\n", xch));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	memset(&xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn));

	// set control structure
	xch_ctrl_cmn.mode		= D_IM_XCH_MD_FILL;
	xch_ctrl_cmn.gHsize	= gl_width;
	xch_ctrl_cmn.dHsize	= width;
	xch_ctrl_cmn.dVsize	= lines;
	xch_ctrl_cmn.dstAddr	= dst_addr;
	xch_ctrl_cmn.pCallBack	= NULL;

	ret = im_xch_open(NULL, xch, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch_fill: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = Im_Xch_Ctrl_Common( xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL, xch );
		Ddim_Print(("I:im_xch_fill: Im_Xch_Ctrl_Common error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = Im_Xch_Ctrl_Fill( xch, fill_data );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Fill error
		im_xch_close(NULL, xch );
		Ddim_Print(("I:im_xch_fill: Im_Xch_Ctrl_Fill error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch_start_sync(NULL,xch);
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL, xch );
		Ddim_Print(("I:im_xch_fill: im_xch_start_sync error. ret = 0x%X\n", ret));
	}

	ret = im_xch_close(NULL,xch);
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch_fill: im_xch_close error. ret = 0x%X\n", ret));
		return ret;
	}

	return D_IM_XCH_OK;
}

INT32 im_xch_fill_ex_sync( ImXch*self,ImXchFillEx* fill_param )
{
	INT32				ret = D_IM_XCH_OK;
	ImXchCtrlCmn	xch_ctrl_cmn;

#ifdef CO_PARAM_CHECK
	if( fill_param == NULL ){
		// fill_param is Error because of NULL
		Ddim_Assertion(("I:im_xch_fill_ex_sync: Null check error. fill_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );

	// set control structur
	xch_ctrl_cmn.pCallBack	= NULL;

	// set common control structure
	im_xch_conv_fill_param( fill_param, &xch_ctrl_cmn );

	// Xch open
	ret = im_xch_open(NULL, fill_param->xch, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch_fill_ex_sync: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	// set control
	ret = Im_Xch_Ctrl_Common( fill_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL, fill_param->xch );
		Ddim_Print(("I:im_xch_fill_ex_sync: Im_Xch_Ctrl_Common error. ret = 0x%X\n", ret));
		return ret;
	}
	ret = Im_Xch_Ctrl_Fill( fill_param->xch, fill_param->fillDate );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Fill error
		im_xch_close(NULL, fill_param->xch );
		Ddim_Print(("I:im_xch_fill_ex_sync: Im_Xch_Ctrl_Fill error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Sync)
	ret = im_xch_start_sync(NULL, fill_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL, fill_param->xch );
		Ddim_Print(("I:im_xch_fill_ex_sync: im_xch_start_sync error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch close
	ret = im_xch_close(NULL, fill_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch_fill_ex_sync: im_xch_close error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 im_xch_fill_ex_async( ImXch*self,ImXchFillEx* fill_param, VP_CALLBACK pCallBack )
{
	ImXchCtrlCmn	xch_ctrl_cmn;
	INT32				ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( fill_param == NULL ){
		// fill_param is Error because of NULL
		Ddim_Assertion(("I:im_xch_fill_ex_async: Null check error. fill_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );

	// set control structure
	xch_ctrl_cmn.pCallBack	= pCallBack;

	// set common control structure
	im_xch_conv_fill_param( fill_param, &xch_ctrl_cmn );

	// set control
	ret = Im_Xch_Ctrl_Common( fill_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		Ddim_Print(("I:im_xch_fill_ex_async: Im_Xch_Ctrl_Common error. ret = 0x%X\n", ret));
		return ret;
	}
	ret = Im_Xch_Ctrl_Fill( fill_param->xch, fill_param->fillDate );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Fill error
		Ddim_Print(("I:im_xch_fill_ex_async: Im_Xch_Ctrl_Fill error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Async)
	ret = im_xch_start_async(NULL, fill_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Async error
		Ddim_Print(("I:im_xch_fill_ex_async: im_xch_start_async error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

ImXch *im_xch_get()
{
	static ImXch *imXch = NULL;
	if(!imXch)
		imXch = k_object_new_with_private(IM_TYPE_XCH,sizeof(ImXchPrivate));
	return imXch;
}

