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
*1、
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


K_TYPE_DEFINE_WITH_PRIVATE(ImXch1, im_xch1)
#define IM_XCH1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImXch1Private,IM_TYPE_XCH1))


struct _ImXch1Private
{
	int a;
};


static void im_xch1_constructor(ImXch1 *self)
{
//	ImXch1Private *priv = IM_XCH1_GET_PRIVATE(self);
}

static void im_xch1_destructor(ImXch1 *self)
{
}

/*
PUBLIC
 */

INT32 im_xch1_ctrl_common( ImXch1*self,ImXchChSel xch, ImXchCtrlCmn* xch_ctrl_cmn )
{
	ImXch* imXch = im_xch_get();


#ifdef CO_PARAM_CHECK
	if( xch_ctrl_cmn == NULL ){
		// xch_ctrl_cmn is Error because of NULL
		Ddim_Assertion(("I:im_xch1_ctrl_common: Null check error. xch_ctrl_cmn = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
	if( (xch != ImXch_XCH_CH_SEL_0) && ( (xch_ctrl_cmn->mode == D_IM_XCH_MD_HISTGRAM_DOWN) || (xch_ctrl_cmn->mode == D_IM_XCH_MD_HISTGRAM) ) ){
		// A channel does not match Mode error
		Ddim_Assertion(("I:im_xch1_ctrl_common: channel does not match histogram mode error. Xch = %d\n", xch));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	// Initialize the save user data.
	memset( (USHORT*)&im_xch_get_gIM_Xch_Mng_Save(imXch,xch), 0, sizeof(ImXchMngSave) );

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xmd		= xch_ctrl_cmn->mode;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xghw		= xch_ctrl_cmn->gHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdhw		= xch_ctrl_cmn->dHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdvw		= xch_ctrl_cmn->dVsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xda		= xch_ctrl_cmn->dstAddr;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).pCallBack	= xch_ctrl_cmn->pCallBack;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xmd        =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xmd));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xghw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xghw));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xdhw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdhw));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xdvw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdvw));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xda        =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xda));
#endif

	return D_IM_XCH_OK;
}

INT32 im_xch1_ctrl_thin( ImXch1*self,ImXchChSel xch, ImXchCtrlThin* xch_ctrl_thin )
{
	ImXch* imXch = im_xch_get();


#ifdef CO_PARAM_CHECK
	if( xch_ctrl_thin == NULL ){
		// xch_ctrl_thin is Error because of NULL
		Ddim_Assertion(("I:im_xch1_ctrl_thin: Null check error. xch_ctrl_thin = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype	= xch_ctrl_thin->xdtype;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc		= xch_ctrl_thin->hcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc		= xch_ctrl_thin->vcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen		= xch_ctrl_thin->hen;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven		= xch_ctrl_thin->ven;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw		= xch_ctrl_thin->sHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa		= xch_ctrl_thin->srcAddr;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xdtype     =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xhcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xvcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xhen       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xven       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xshw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xsa        =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa   ));
#endif

	return D_IM_XCH_OK;
}

INT32 im_xch1_ctrl_hist( ImXch1*self,ImXchChSel xch, ImXchCtrlHist* xch_ctrl_hist )
{
	ImXch* imXch = im_xch_get();


#ifdef CO_PARAM_CHECK
	if( xch != ImXch_XCH_CH_SEL_0 ){
		// Channel number error. ( Only Histogram Mode : X0ch )
		Ddim_Assertion(("I:im_xch1_ctrl_hist: Channel number error. Xch = %d\n", xch));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
	if( xch_ctrl_hist == NULL ){
		// xch_ctrl_hist is Error because of NULL
		Ddim_Assertion(("I:im_xch1_ctrl_hist: Null check error. xch_ctrl_hist = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype	= xch_ctrl_hist->xdtype;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc		= xch_ctrl_hist->hcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc		= xch_ctrl_hist->vcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen		= xch_ctrl_hist->hen;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven		= xch_ctrl_hist->ven;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw		= xch_ctrl_hist->sHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa		= xch_ctrl_hist->srcAddr;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcnt		= xch_ctrl_hist->hcnt;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xdtype     =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xdtype));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xhcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xvcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xhen       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhen  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xven       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xshw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xsa        =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa   ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xhcnt      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xhcnt ));
#endif

	return D_IM_XCH_OK;
}

INT32 im_xch1_ctrl_half_thin( ImXch1*self,ImXchChSel xch, ImXchCtrlHalfThin* xch_ctrl_half_thin )
{
	ImXch* imXch = im_xch_get();


#ifdef CO_PARAM_CHECK
	if( xch_ctrl_half_thin == NULL ){
		// xch_ctrl_half_thin is Error because of NULL
		Ddim_Assertion(("I:im_xch1_ctrl_half_thin: Null check error. xch_ctrl_half_thin = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc	= xch_ctrl_half_thin->vcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven	= xch_ctrl_half_thin->ven;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw	= xch_ctrl_half_thin->sHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa	= xch_ctrl_half_thin->srcAddr;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xvcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xven       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xshw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xsa        =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa   ));
#endif

	return D_IM_XCH_OK;
}

INT32 im_xch1_ctrl_copy( ImXch1*self,ImXchChSel xch, ImXchCtrlCopy* xch_ctrl_copy )
{
	ImXch* imXch = im_xch_get();


#ifdef CO_PARAM_CHECK
	if( xch_ctrl_copy == NULL ){
		// xch_ctrl_copy is Error because of NULL
		Ddim_Assertion(("I:im_xch1_ctrl_copy: Null check error. xch_ctrl_copy = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc	= xch_ctrl_copy->vcyc;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven	= xch_ctrl_copy->ven;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw	= xch_ctrl_copy->sHsize;
	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa	= xch_ctrl_copy->srcAddr;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xvcyc      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xvcyc ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xven       =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xven  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xshw       =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xshw  ));
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xsa        =0x%lX\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xsa   ));
#endif

	return D_IM_XCH_OK;
}

INT32 im_xch1_ctrl_fill( ImXch1*self,ImXchChSel xch, UCHAR fill_data )
{
	ImXch* imXch = im_xch_get();


	im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xfdt	= fill_data;

#ifdef CO_IM_XCH_DEBUG
	Ddim_Print(("im_xch_get_gIM_Xch_Mng_Save(imXch,%d).xfdt      =0x%X\n", xch, im_xch_get_gIM_Xch_Mng_Save(imXch,xch).xfdt ));
#endif

	return D_IM_XCH_OK;
}


UCHAR im_xch1_get_histogram_max( ImXch1*self )
{
	UCHAR ret;

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	ret = (UCHAR)IO_XCH.XHISTG0.bit.XHMAX0;

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return ret;
}

INT32 im_xch1_get_ctrl_common( ImXch1*self,ImXchChSel xch, ImXchCtrlCmn* xch_ctrl_cmn )
{
#ifdef CO_PARAM_CHECK
	if( xch_ctrl_cmn == NULL ){
		// xch_ctrl_cmn is Error because of NULL
		Ddim_Assertion(("I:im_xch1_get_ctrl_common: Null check error. xch_ctrl_cmn = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		xch_ctrl_cmn->mode		= IO_XCH.XCHCTL0.XMD.bit.XMD;
		xch_ctrl_cmn->gHsize	= IO_XCH.XCHCTL0.XGHW.bit.XGHW;
		xch_ctrl_cmn->dHsize	= IO_XCH.XCHCTL0.XDHW.bit.XDHW;
		xch_ctrl_cmn->dVsize	= IO_XCH.XCHCTL0.XDVW.bit.XDVW;
		xch_ctrl_cmn->dstAddr	= IO_XCH.XCHCTL0.XDA.word;
	}
	else{
		// X1ch
		xch_ctrl_cmn->mode		= IO_XCH.XCHCTL1.XMD.bit.XMD;
		xch_ctrl_cmn->gHsize	= IO_XCH.XCHCTL1.XGHW.bit.XGHW;
		xch_ctrl_cmn->dHsize	= IO_XCH.XCHCTL1.XDHW.bit.XDHW;
		xch_ctrl_cmn->dVsize	= IO_XCH.XCHCTL1.XDVW.bit.XDVW;
		xch_ctrl_cmn->dstAddr	= IO_XCH.XCHCTL1.XDA.word;
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_ctrl_thin( ImXch1*self,ImXchChSel xch, ImXchCtrlThin* xch_ctrl_thin )
{
#ifdef CO_PARAM_CHECK
	if( xch_ctrl_thin == NULL ){
		// xch_ctrl_thin is Error because of NULL
		Ddim_Assertion(("I:im_xch1_get_ctrl_thin: Null check error. xch_ctrl_thin = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		xch_ctrl_thin->xdtype	= IO_XCH.XCHCTL0.XDTYPE.bit.XSDTYPE;
		xch_ctrl_thin->hcyc		= IO_XCH.XCHCTL0.XCYC.bit.XHCYC;
		xch_ctrl_thin->vcyc		= IO_XCH.XCHCTL0.XCYC.bit.XVCYC;
		xch_ctrl_thin->hen		= IO_XCH.XCHCTL0.XHEN.bit.XHEN;
		xch_ctrl_thin->ven		= IO_XCH.XCHCTL0.XVEN.bit.XVEN;
		xch_ctrl_thin->sHsize	= IO_XCH.XCHCTL0.XSHW.bit.XSHW;
		xch_ctrl_thin->srcAddr	= IO_XCH.XCHCTL0.XSA.word;
	}
	else{
		// X1ch
		xch_ctrl_thin->xdtype	= IO_XCH.XCHCTL1.XDTYPE.bit.XSDTYPE;
		xch_ctrl_thin->hcyc		= IO_XCH.XCHCTL1.XCYC.bit.XHCYC;
		xch_ctrl_thin->vcyc		= IO_XCH.XCHCTL1.XCYC.bit.XVCYC;
		xch_ctrl_thin->hen		= IO_XCH.XCHCTL1.XHEN.bit.XHEN;
		xch_ctrl_thin->ven		= IO_XCH.XCHCTL1.XVEN.bit.XVEN;
		xch_ctrl_thin->sHsize	= IO_XCH.XCHCTL1.XSHW.bit.XSHW;
		xch_ctrl_thin->srcAddr	= IO_XCH.XCHCTL1.XSA.word;
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_ctrl_hist( ImXch1*self,ImXchChSel xch, ImXchCtrlHist* xch_ctrl_hist )
{
#ifdef CO_PARAM_CHECK
	if( xch != ImXch_XCH_CH_SEL_0 ){
		Ddim_Assertion(("I:im_xch1_get_ctrl_hist: Channel number error. Xch = %d\n", xch));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
	if( xch_ctrl_hist == NULL ){
		// xch_ctrl_hist is Error because of NULL
		Ddim_Assertion(("I:im_xch1_get_ctrl_hist: NULL check error. xch_ctrl_hist=NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	xch_ctrl_hist->xdtype	= IO_XCH.XCHCTL0.XDTYPE.bit.XSDTYPE;
	xch_ctrl_hist->hcyc		= IO_XCH.XCHCTL0.XCYC.bit.XHCYC;
	xch_ctrl_hist->vcyc		= IO_XCH.XCHCTL0.XCYC.bit.XVCYC;
	xch_ctrl_hist->hen		= IO_XCH.XCHCTL0.XHEN.bit.XHEN;
	xch_ctrl_hist->ven		= IO_XCH.XCHCTL0.XVEN.bit.XVEN;
	xch_ctrl_hist->sHsize	= IO_XCH.XCHCTL0.XSHW.bit.XSHW;
	xch_ctrl_hist->srcAddr	= IO_XCH.XCHCTL0.XSA.word;
	xch_ctrl_hist->hcnt		= IO_XCH.XHISTG0.bit.XHCNT0;

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_ctrl_half_thin( ImXch1*self,ImXchChSel xch, ImXchCtrlHalfThin* xch_ctrl_half_thin )
{
#ifdef CO_PARAM_CHECK
	if( xch_ctrl_half_thin == NULL ){
		// xch_ctrl_half_thin is Error because of NULL
		Ddim_Assertion(("I:im_xch1_get_ctrl_half_thin: NULL check error. xch_ctrl_half_thin = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		xch_ctrl_half_thin->vcyc		= IO_XCH.XCHCTL0.XCYC.bit.XVCYC;
		xch_ctrl_half_thin->ven			= IO_XCH.XCHCTL0.XVEN.bit.XVEN;
		xch_ctrl_half_thin->sHsize		= IO_XCH.XCHCTL0.XSHW.bit.XSHW;
		xch_ctrl_half_thin->srcAddr	= IO_XCH.XCHCTL0.XSA.word;
	}
	else{
		// X1ch
		xch_ctrl_half_thin->vcyc		= IO_XCH.XCHCTL1.XCYC.bit.XVCYC;
		xch_ctrl_half_thin->ven			= IO_XCH.XCHCTL1.XVEN.bit.XVEN;
		xch_ctrl_half_thin->sHsize		= IO_XCH.XCHCTL1.XSHW.bit.XSHW;
		xch_ctrl_half_thin->srcAddr	= IO_XCH.XCHCTL1.XSA.word;
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_ctrl_copy( ImXch1*self,ImXchChSel xch, ImXchCtrlCopy* xch_ctrl_copy )
{
#ifdef CO_PARAM_CHECK
	if( xch_ctrl_copy == NULL ){
		// xch_ctrl_copy is Error because of NULL
		Ddim_Assertion(("I:im_xch1_get_ctrl_copy. NULL check error. xch_ctrl_copy = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		xch_ctrl_copy->vcyc		= IO_XCH.XCHCTL0.XCYC.bit.XVCYC;
		xch_ctrl_copy->ven		= IO_XCH.XCHCTL0.XVEN.bit.XVEN;
		xch_ctrl_copy->sHsize	= IO_XCH.XCHCTL0.XSHW.bit.XSHW;
		xch_ctrl_copy->srcAddr	= IO_XCH.XCHCTL0.XSA.word;
	}
	else{
		// X1ch
		xch_ctrl_copy->vcyc		= IO_XCH.XCHCTL1.XCYC.bit.XVCYC;
		xch_ctrl_copy->ven		= IO_XCH.XCHCTL1.XVEN.bit.XVEN;
		xch_ctrl_copy->sHsize	= IO_XCH.XCHCTL1.XSHW.bit.XSHW;
		xch_ctrl_copy->srcAddr	= IO_XCH.XCHCTL1.XSA.word;
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_ctrl_fill( ImXch1*self,ImXchChSel xch, UCHAR* fill_data )
{
#ifdef CO_PARAM_CHECK
	if( fill_data == NULL ) {
		// Channel number error
		Ddim_Assertion(("I:im_xch1_get_ctrl_fill: NULL check error. fill_data = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		*fill_data = IO_XCH.XCHCTL0.XFDT.bit.XFDT;
	}
	else{
		// X1ch
		*fill_data = IO_XCH.XCHCTL1.XFDT.bit.XFDT;
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}

INT32 im_xch1_get_xtrg( ImXch1*self,ImXchChSel xch, ImXchSt* status )
{
#ifdef CO_PARAM_CHECK
	if( status == NULL ){
		// Channel number error
		Ddim_Assertion(("I:im_xch1_get_xtrg: NULL check error. status = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	im_xch_on_pclk(NULL);	// PCLK on
	Im_XCH_Dsb();

	if( xch == ImXch_XCH_CH_SEL_0 ){
		// X0ch
		if( IO_XCH.XCHCTL0.XTRG.bit.XTRG == D_IM_XCH_RUNNING ){
			*status = ImXch_XCH_ST_RUNNING;
		}
		else{
			*status = ImXch_XCH_ST_STOPPED;
		}
	}
	else{
		// X1ch
		if( IO_XCH.XCHCTL1.XTRG.bit.XTRG == D_IM_XCH_RUNNING ){
			*status = ImXch_XCH_ST_RUNNING;
		}
		else{
			*status = ImXch_XCH_ST_STOPPED;
		}
	}

	im_xch_off_pclk(NULL);	// PCLK off
	Im_XCH_Dsb();

	return D_IM_XCH_OK;
}



ImXch1 *im_xch1_new(void)
{
	ImXch1* self = k_object_new_with_private(IM_TYPE_XCH1,sizeof(ImXch1Private));
	return self;
}
