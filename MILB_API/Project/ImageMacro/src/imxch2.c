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
#include "imxch2.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImXch2, im_xch2)
#define IM_XCH2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImXch2Private,IM_TYPE_XCH2))

struct _ImXch2Private
{
	int a;
};

static void im_xch2_constructor(ImXch2 *self)
{
//	ImXch2Private *priv = IM_XCH2_GET_PRIVATE(self);
}

static void im_xch2_destructor(ImXch2 *self)
{
}

/*
 DECLS
 */

static int imXchCopy2ch( UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines );
static INT32 imXchCopyByte( UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines );

/*
 IMPL
 */

#ifdef CO_DDIM_UTILITY_USE

static int imXchCopy2ch( UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines )
{
	INT32				ret;
	USHORT				lines_0ch;
	USHORT				lines_1ch;
	UINT32				src_second_addr;
	UINT32				dst_second_addr;
	ImXchCopyEx	xch_copy_0ch;
	ImXchCopyEx	xch_copy_1ch;

	lines_0ch = lines >> 1;			// 0ch lines
	lines_1ch = lines - lines_0ch;	// 1ch lines
	src_second_addr = src_addr + src_gl_width * lines_0ch;
	dst_second_addr = dst_addr + dst_gl_width * lines_0ch;

	// initialize
	memset( &xch_copy_0ch, 0, sizeof(ImXchCopyEx) );
	memset( &xch_copy_1ch, 0, sizeof(ImXchCopyEx) );

	// X0ch open
	ret = im_xch_open(NULL, ImXch_XCH_CH_SEL_0, D_DDIM_WAIT_END_FOREVER );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:imXchCopy2ch: im_xch_open(0ch) error. ret = 0x%X\n", ret));
		return ret;
	}

	// X1ch open
	ret = im_xch_open(NULL, ImXch_XCH_CH_SEL_1, D_DDIM_WAIT_END_FOREVER );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		Ddim_Print(("I:imXchCopy2ch: im_xch_open(1ch) error. ret = 0x%X\n", ret));
		return ret;
	}

	// set 0ch control
	if( ((src_addr & 0xF) != 0) || ((dst_addr & 0xF) != 0) ){
		// normal copy mode
		xch_copy_0ch.copyType	= ImXch_XCH_COPY_SEL_NORMAL;
	}
	else{
		// hi-speed copy mode
		xch_copy_0ch.copyType	= ImXch_XCH_COPY_SEL_HI;
	}

	xch_copy_0ch.xch	= ImXch_XCH_CH_SEL_0;
	xch_copy_0ch.size.width			= width;
	xch_copy_0ch.size.lines			= lines_0ch;
	xch_copy_0ch.size.srcGlWidth	= src_gl_width;
	xch_copy_0ch.size.dstGlWidth	= dst_gl_width;
	xch_copy_0ch.addr.src		= src_addr;
	xch_copy_0ch.addr.dst		= dst_addr;

	// set 1ch control
	if( ((src_second_addr & 0xF) != 0) || ((dst_second_addr & 0xF) != 0) ){
		// normal copy mode
		xch_copy_1ch.copyType	= ImXch_XCH_COPY_SEL_NORMAL;
	}
	else{
		// hi-speed copy mode
		xch_copy_1ch.copyType	= ImXch_XCH_COPY_SEL_HI;
	}

	xch_copy_1ch.xch	= ImXch_XCH_CH_SEL_1;
	xch_copy_1ch.size.width			= width;
	xch_copy_1ch.size.lines			= lines_1ch;
	xch_copy_1ch.size.srcGlWidth	= src_gl_width;
	xch_copy_1ch.size.dstGlWidth	= dst_gl_width;
	xch_copy_1ch.addr.src	= src_second_addr;
	xch_copy_1ch.addr.dst	= dst_second_addr;

#ifdef CO_DEBUG_ON_PC
	IO_XCH.XCHCTL0.XTRG.bit.XTRG	= 2;
	IO_XCH.XCHCTL1.XTRG.bit.XTRG	= 2;
#endif

	// Xch start copy process
	ret = im_xch2_copy_ex_async(NULL, &xch_copy_0ch, NULL );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Copy_Ex_Async error(0ch)
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
		Ddim_Print(("I:imXchCopy2ch: im_xch2_copy_ex_async(0ch) error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch2_copy_ex_async(NULL, &xch_copy_1ch, NULL );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Copy_Ex_Async error(1ch)
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
		Ddim_Print(("I:imXchCopy2ch: im_xch2_copy_ex_async(1ch) error. ret = 0x%X\n", ret));
		return ret;
	}

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("Call im_xch_int_handler() for PC route check.\n"));
	IO_XCH.XCHICE.bit.XE0	= 1;
	IO_XCH.XCHICF.bit.__XF0	= 1;
	IO_XCH.XCHICE.bit.XE1	= 0;
	IO_XCH.XCHICF.bit.__XF1	= 0;
	im_xch_int_handler();
#endif

	// Xch wait end
	ret = im_xch_wait_end(NULL, ImXch_XCH_CH_SEL_0 );
	if( ret != D_IM_XCH_OK ){
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
		Ddim_Print(("I:imXchCopy2ch: im_xch_wait_end(0ch) error. ret = 0x%X\n", ret));
		return ret;
	}

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("Call im_xch_int_handler() for PC route check.\n"));
	IO_XCH.XCHICE.bit.XE0	= 0;
	IO_XCH.XCHICF.bit.__XF0	= 0;
	IO_XCH.XCHICE.bit.XE1	= 1;
	IO_XCH.XCHICF.bit.__XF1	= 1;
	im_xch_int_handler();
#endif

	ret = im_xch_wait_end(NULL, ImXch_XCH_CH_SEL_1 );
	if( ret != D_IM_XCH_OK ){
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
		Ddim_Print(("I:imXchCopy2ch: im_xch_wait_end(1ch) error. ret = 0x%X\n", ret));
		return ret;
	}
	// 0ch Close
	ret = im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error(0ch)
		im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
		Ddim_Print(("I:imXchCopy2ch: Im_Xch_Close(0ch) error. ret = 0x%X\n", ret));
		return ret;
	}
	// 1ch Close
	ret = im_xch_close(NULL,ImXch_XCH_CH_SEL_1 );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error(1ch)
		Ddim_Print(("I:imXchCopy2ch: Im_Xch_Close(1ch) error. ret = 0x%X\n", ret));
		return ret;
	}

	return D_IM_XCH_OK;
}

static INT32 imXchCopyByte( UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines )
{
	INT32				ret;
	ImXchCopyEx	xch_copy;
	T_DDIM_USER_RSEM	xch_sem_param;
	ImXchChSel		xch	= ImXch_XCH_CH_SEL_0;

	// initialize
	memset( &xch_copy, 0, sizeof(ImXchCopyEx) );
	DDIM_User_Ref_Sem( SID_IM_XCH(ImXch_XCH_CH_SEL_0), &xch_sem_param );

	if( xch_sem_param.semcnt == 0 ){
		// The X0ch has not become empty.
		DDIM_User_Ref_Sem( SID_IM_XCH( ImXch_XCH_CH_SEL_1 ), &xch_sem_param );

		if( xch_sem_param.semcnt == 0 ){
			// The X1ch has not become empty.
			Ddim_Print(("I:imXchCopyByte: The channel has not become empty. . \n"));
			return D_IM_XCH_NG;
		}
		xch = ImXch_XCH_CH_SEL_1;
	}
	else{
		// The channel has become empty.
		xch = ImXch_XCH_CH_SEL_0;
	}

	// Xch open
	ret = im_xch_open(NULL, xch, D_DDIM_WAIT_END_FOREVER );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:imXchCopyByte: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	// set copy control
	if( ((src_addr & 0xF) != 0) || ((dst_addr & 0xF) != 0) || ((width & 0xF) != 0) ){
		// normal copy mode
		xch_copy.copyType	= ImXch_XCH_COPY_SEL_NORMAL;
	}
	else{
		// hi-speed copy mode
		xch_copy.copyType	= ImXch_XCH_COPY_SEL_HI;
	}

	xch_copy.xch				= xch;
	xch_copy.size.width			= width;
	xch_copy.size.lines			= lines;
	xch_copy.size.srcGlWidth	= src_gl_width;
	xch_copy.size.dstGlWidth	= dst_gl_width;
	xch_copy.addr.src			= src_addr;
	xch_copy.addr.dst			= dst_addr;

#ifdef CO_DEBUG_ON_PC
	IO_XCH.XCHCTL0.XTRG.bit.XTRG	= 2;
	IO_XCH.XCHCTL1.XTRG.bit.XTRG	= 2;
#endif

	// Xch start copy process
	ret = im_xch2_copy_ex_async(NULL, &xch_copy, NULL );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Copy_Ex_Async error
		im_xch_close(NULL,xch );
		Ddim_Print(("I:imXchCopyByte: im_xch2_copy_ex_async error. ret = 0x%X\n", ret));
		return ret;
	}

#ifdef CO_DEBUG_ON_PC
	Ddim_Print(("Call im_xch_int_handler() for PC route check.\n"));
	if( xch == ImXch_XCH_CH_SEL_0 ){
		IO_XCH.XCHICE.bit.XE0	= 1;
		IO_XCH.XCHICF.bit.__XF0	= 1;
		IO_XCH.XCHICE.bit.XE1	= 0;
		IO_XCH.XCHICF.bit.__XF1	= 0;
	}
	else{
		IO_XCH.XCHICE.bit.XE0	= 0;
		IO_XCH.XCHICF.bit.__XF0	= 0;
		IO_XCH.XCHICE.bit.XE1	= 1;
		IO_XCH.XCHICF.bit.__XF1	= 1;
	}
	im_xch_int_handler();
#endif

	// Xch wait end
	ret = im_xch_wait_end(NULL, xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Copy_Ex_Async error
		im_xch_close(NULL,xch );
		Ddim_Print(("I:imXchCopyByte: im_xch_wait_end"
				" error. ret = 0x%X\n", ret));
		return ret;
	}
	// Xch Close
	ret = im_xch_close(NULL,xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:imXchCopyByte: Im_Xch_Close error. ret = 0x%X\n", ret));
		return ret;
	}
	return D_IM_XCH_OK;
}

/*
PUBLIC
 */

INT32 im_xch2_conv_copy_param( ImXch2*self,ImXchCopyEx* copy_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlThin* xch_ctrl_thin, ImXchCtrlCopy* xch_ctrl_copy )
{
	if( copy_param->copyType == ImXch_XCH_COPY_SEL_HI ){
		// hi-speed copy
		xch_ctrl_cmn->mode = D_IM_XCH_MD_COPY;
		xch_ctrl_copy->vcyc		= 0x0;
		xch_ctrl_copy->ven		= 0xFFFFFFFF;
		xch_ctrl_copy->sHsize	= copy_param->size.srcGlWidth;
		xch_ctrl_copy->srcAddr	= copy_param->addr.src;
	}
	else{
		// normal-speed copy
		xch_ctrl_cmn->mode = D_IM_XCH_MD_DOWN_HI_SPEED;
		xch_ctrl_thin->hcyc		= 0x0;
		xch_ctrl_thin->vcyc		= 0x0;
		xch_ctrl_thin->hen		= 0xFFFFFFFF;
		xch_ctrl_thin->ven		= 0xFFFFFFFF;
		xch_ctrl_thin->sHsize	= copy_param->size.srcGlWidth;
		xch_ctrl_thin->srcAddr	= copy_param->addr.src;
	}
	// set control structure
	xch_ctrl_cmn->gHsize	= copy_param->size.dstGlWidth;
	xch_ctrl_cmn->dHsize	= copy_param->size.width;
	xch_ctrl_cmn->dVsize	= copy_param->size.lines;
	xch_ctrl_cmn->dstAddr	= copy_param->addr.dst;
	return D_IM_XCH_OK;
}

VOID im_xch2_conv_fill_param( ImXch2*self,ImXchFillEx* fill_param, ImXchCtrlCmn* xch_ctrl_cmn )
{
	// set common control structure
	xch_ctrl_cmn->mode		= D_IM_XCH_MD_FILL;
	xch_ctrl_cmn->gHsize	= fill_param->size.glWidth;
	xch_ctrl_cmn->dHsize	= fill_param->size.width;
	xch_ctrl_cmn->dVsize	= fill_param->size.lines;
	xch_ctrl_cmn->dstAddr	= fill_param->fillAddr;
	return;
}

VOID im_xch2_conv_hist_param( ImXch2*self,ImXchExamineHist* hist_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlHist* xch_ctrl_hist )
{
	// set common control structure
	xch_ctrl_cmn->mode		= D_IM_XCH_MD_HISTGRAM;
	xch_ctrl_cmn->gHsize	= hist_param->size.width;
	xch_ctrl_cmn->dHsize	= hist_param->size.width;
	xch_ctrl_cmn->dVsize	= hist_param->size.lines;
	xch_ctrl_cmn->dstAddr	= hist_param->histAddr;
	// set histogram control structure
	xch_ctrl_hist->xdtype	= D_IM_XCH_XDTYPE_8;
	xch_ctrl_hist->hcyc		= 0x00;
	xch_ctrl_hist->vcyc		= 0x00;
	xch_ctrl_hist->hen		= 0xFFFFFFFF;
	xch_ctrl_hist->ven		= 0xFFFFFFFF;
	xch_ctrl_hist->sHsize	= hist_param->size.width;
	xch_ctrl_hist->srcAddr	= hist_param->histAddr;
	xch_ctrl_hist->hcnt		= 0;
	return;
}

INT32 im_xch2_conv_thin_param( ImXch2*self,ImXchConvThin* thin_param, ImXchCtrlCmn* xch_ctrl_cmn, ImXchCtrlThin* xch_ctrl_thin )
{
	switch( thin_param->thinWidth ){
		case D_IM_XCH_THIN_SEL_1_2:
			// 1/2 down sampling
			xch_ctrl_cmn->dHsize	= (thin_param->size.width >> 1);
			xch_ctrl_thin->hen		= 0xAAAAAAAA;
			break;
		case D_IM_XCH_THIN_SEL_1_4:
			// 1/4 down sampling
			xch_ctrl_cmn->dHsize	= (thin_param->size.width >> 2);
			xch_ctrl_thin->hen		= 0x44444444;
			break;
		case D_IM_XCH_THIN_SEL_3_4:
			// 3/4 down sampling
			xch_ctrl_cmn->dHsize	= ((thin_param->size.width * 3) >> 2);
			xch_ctrl_thin->hen		= 0xBBBBBBBB;
			break;
		case D_IM_XCH_THIN_SEL_1_1:
		default:
			// not down sampling
			xch_ctrl_cmn->dHsize	= thin_param->size.width;
			xch_ctrl_thin->hen		= 0xFFFFFFFF;
			break;
	}

	switch( thin_param->thinLines ){
		case D_IM_XCH_THIN_SEL_1_2:
			// 1/2 down sampling
			xch_ctrl_cmn->dVsize	= (thin_param->size.lines >> 1);
			xch_ctrl_thin->ven		= 0xAAAAAAAA;
			break;
		case D_IM_XCH_THIN_SEL_1_4:
			// 1/4 down sampling
			xch_ctrl_cmn->dVsize	= (thin_param->size.lines >> 2);
			xch_ctrl_thin->ven		= 0x44444444;
			break;
		case D_IM_XCH_THIN_SEL_3_4:
			// 3/4 down sampling
			xch_ctrl_cmn->dVsize	= ((thin_param->size.lines * 3) >> 2);
			xch_ctrl_thin->ven		= 0xBBBBBBBB;
			break;
		case D_IM_XCH_THIN_SEL_1_1:
		default:
			// not down sampling
			xch_ctrl_cmn->dVsize	= thin_param->size.lines;
			xch_ctrl_thin->ven		= 0xFFFFFFFF;
			break;
	}
	// set control structure
	xch_ctrl_cmn->mode			= D_IM_XCH_MD_DOWN_HI_SPEED;
	xch_ctrl_cmn->gHsize		= thin_param->size.dstGlWidth;
	xch_ctrl_cmn->dstAddr		= thin_param->addr.dst;
	xch_ctrl_thin->xdtype		= D_IM_XCH_XDTYPE_8;
	xch_ctrl_thin->sHsize		= thin_param->size.srcGlWidth;
	xch_ctrl_thin->srcAddr		= thin_param->addr.src;
	xch_ctrl_thin->hcyc			= 0x0;	// 32 byte cycle
	xch_ctrl_thin->vcyc			= 0x0;	// 32 line cycle
	return D_IM_XCH_OK;
}

INT32 im_xch2_copy_dual_channel( ImXch2*self,VOID* dst_addr, VOID* src_addr, INT32 size )
{
	INT32	ret = D_IM_XCH_OK;
	UINT32	src;
	UINT32	dst;
	USHORT	vsize;
	src = (UINT32)src_addr;
	dst = (UINT32)dst_addr;

	while( size >= 0x4000000 ){
#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("I:im_xch2_copy_dual_channel: 0x4000000 copy root.\n"));
#endif //CO_DEBUG_ON_PC

		// 8192 x 8192 byte copy
		ret = imXchCopy2ch( src, 0x2000, 0x2000, dst, 0x2000, 0x2000 );
		if( ret != D_IM_XCH_OK ){
			// imXchCopy2ch error
			Ddim_Print(("I:im_xch2_copy_dual_channel: imXchCopy2ch error. ret = 0x%X\n", ret));
			return ret;
		}
		size -= 0x4000000;
		src += 0x4000000;
		dst += 0x4000000;
	}

	while( size >= 0x4000 ){
#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("I:im_xch2_copy_dual_channel: 0x4000 copy root.\n"));
#endif //CO_DEBUG_ON_PC

		// 8192 * 2 byte copy
		vsize = size >> 13;
		ret = imXchCopy2ch( src, 0x2000, 0x2000, dst, 0x2000, vsize );
		if( ret != D_IM_XCH_OK ){
			// imXchCopy2ch error
			Ddim_Print(("I:im_xch2_copy_dual_channel: imXchCopy2ch error. ret = 0x%X\n", ret));
			return ret;
		}
		size -= vsize * 0x2000;
		src += vsize * 0x2000;
		dst += vsize * 0x2000;
	}

	while( size >= 0x2000 ){
#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("I:im_xch2_copy_dual_channel: 0x2000 copy root.\n"));
#endif //CO_DEBUG_ON_PC

		// 8192 byte copy
		vsize = size >> 13;
		ret = imXchCopyByte( src, 0x2000, 0x2000, dst, 0x2000, vsize );
		if( ret != D_IM_XCH_OK ){
			// imXchCopy2ch error
			Ddim_Print(("I:im_xch2_copy_dual_channel: imXchCopyByte error. ret = 0x%X\n", ret));
			return ret;
		}
		size -= vsize * 0x2000;
		src += vsize * 0x2000;
		dst += vsize * 0x2000;
	}

	if( size > 0 ){
#ifdef CO_DEBUG_ON_PC
		Ddim_Print(("I:im_xch2_copy_dual_channel: 0 copy root.\n"));
#endif //CO_DEBUG_ON_PC

		//
		ret = imXchCopyByte( src, 0x2000, 0x2000, dst, size, 1 );
		if( ret != D_IM_XCH_OK ){
			// imXchCopyByte error
			Ddim_Print(("I:im_xch2_copy_dual_channel: imXchCopyByte error. ret = 0x%X\n", ret));
			return ret;
		}
	}

	return ret;
}

INT32 im_xch2_copy( ImXch2*self,ImXchChSel xch, UINT32 src_addr, USHORT src_gl_width, USHORT dst_gl_width, UINT32 dst_addr, USHORT width, USHORT lines )
{
	INT32 ret;

	ImXchCtrlCmn	xch_ctrl_cmn;
	ImXchCtrlCopy	xch_ctrl_copy;

#ifdef CO_PARAM_CHECK
	if( (xch != ImXch_XCH_CH_SEL_0) && (xch != ImXch_XCH_CH_SEL_1) ){
		// Channel number error
		Ddim_Assertion(("I:im_xch2_copy: Unknown channel error. Xch = %d\n", xch));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif // CO_PARAM_CHECK

	memset(&xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn));
	memset(&xch_ctrl_copy, 0, sizeof(ImXchCtrlCopy));

	xch_ctrl_cmn.mode		= D_IM_XCH_MD_COPY;
	xch_ctrl_cmn.gHsize	= dst_gl_width;
	xch_ctrl_cmn.dHsize	= width;
	xch_ctrl_cmn.dVsize	= lines;
	xch_ctrl_cmn.dstAddr	= dst_addr;
	xch_ctrl_cmn.pCallBack	= NULL;
	xch_ctrl_copy.vcyc		= 0;
	xch_ctrl_copy.ven		= 0xFFFFFFFF;
	xch_ctrl_copy.sHsize	= src_gl_width;
	xch_ctrl_copy.srcAddr	= src_addr;
	ret = im_xch_open(NULL, xch, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch2_copy: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch1_ctrl_common(NULL, xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL,xch );
		Ddim_Print(("I:im_xch2_copy: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}
	ret = im_xch1_ctrl_copy(NULL, xch, &xch_ctrl_copy );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Copy error
		im_xch_close(NULL,xch );
		Ddim_Print(("I:im_xch2_copy: im_xch1_ctrl_copy error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch_start_sync(NULL, xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		im_xch_close(NULL,xch );
		Ddim_Print(("I:im_xch2_copy: im_xch_start_sync error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch_close(NULL,xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch2_copy: Im_Xch_Close error. ret = 0x%X\n", ret));
		return ret;
	}

	return D_IM_XCH_OK;

}

INT32 im_xch2_copy_ex_sync( ImXch2*self,ImXchCopyEx* copy_param )
{
	ImXchCtrlCmn		xch_ctrl_cmn;
	ImXchCtrlThin		xch_ctrl_thin;
	ImXchCtrlCopy		xch_ctrl_copy;
	INT32					ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( copy_param == NULL ){
		// copy_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_copy_ex_sync: Null check error. copy_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_thin, 0, sizeof(ImXchCtrlThin) );
	memset( &xch_ctrl_copy, 0, sizeof(ImXchCtrlCopy) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= NULL;
	// set control structure
	ret = im_xch2_conv_copy_param( NULL,copy_param, &xch_ctrl_cmn, &xch_ctrl_thin, &xch_ctrl_copy );
	if( ret != D_IM_XCH_OK ){
		// im_xch_prepare_copy_ex_param error
		Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch2_conv_copy_param error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch open
	ret = im_xch_open(NULL, copy_param->xch, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}
	// set control
	ret = im_xch1_ctrl_common(NULL, copy_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL,copy_param->xch );
		Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}

	if( copy_param->copyType == ImXch_XCH_COPY_SEL_HI ){
		// hi-speed copy
		ret = im_xch1_ctrl_copy(NULL, copy_param->xch, &xch_ctrl_copy );
		if( ret != D_IM_XCH_OK ){
			// Im_Xch_Ctrl_Copy error
			im_xch_close(NULL,copy_param->xch );
			Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch1_ctrl_copy error. ret = 0x%X\n", ret));
			return ret;
		}
	}
	else{
		// normal-speed copy
		ret = im_xch1_ctrl_thin(NULL, copy_param->xch, &xch_ctrl_thin );
		if( ret != D_IM_XCH_OK ){
			// Im_Xch_Ctrl_Thin error
			im_xch_close(NULL,copy_param->xch );
			Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch1_ctrl_thin error. ret = 0x%X\n", ret));
			return ret;
		}
	}
	// Xch start(Sync)
	ret = im_xch_start_sync(NULL, copy_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL,copy_param->xch );
		Ddim_Print(("I:im_xch2_copy_ex_sync: im_xch_start_sync error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch close
	ret = im_xch_close(NULL,copy_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch2_copy_ex_sync: Im_Xch_Close error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 im_xch2_copy_ex_async( ImXch2*self,ImXchCopyEx* copy_param, VP_CALLBACK pCallBack )
{
	ImXchCtrlCmn		xch_ctrl_cmn;
	ImXchCtrlThin		xch_ctrl_thin;
	ImXchCtrlCopy		xch_ctrl_copy;
	INT32					ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( copy_param == NULL ){
		// copy_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_copy_ex_async: Null check error. copy_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_thin, 0, sizeof(ImXchCtrlThin) );
	memset( &xch_ctrl_copy, 0, sizeof(ImXchCtrlCopy) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= pCallBack;

	// set control structure
	ret = im_xch2_conv_copy_param( NULL,copy_param, &xch_ctrl_cmn, &xch_ctrl_thin, &xch_ctrl_copy );
	if( ret != D_IM_XCH_OK ){
		// im_xch_prepare_copy_ex_param error
		Ddim_Print(("I:im_xch2_copy_ex_async: im_xch2_conv_copy_param error. ret = 0x%X\n", ret));
		return ret;
	}

	// set control
	ret = im_xch1_ctrl_common(NULL, copy_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		Ddim_Print(("I:im_xch2_copy_ex_async: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}

	if( copy_param->copyType == ImXch_XCH_COPY_SEL_HI ){
		// hi-speed copy
		ret = im_xch1_ctrl_copy(NULL, copy_param->xch, &xch_ctrl_copy );
		if( ret != D_IM_XCH_OK ){
			// Im_Xch_Ctrl_Copy error
			Ddim_Print(("I:im_xch2_copy_ex_async: im_xch1_ctrl_copy error. ret = 0x%X\n", ret));
			return ret;
		}
	}
	else{
		// normal-speed copy
		ret = im_xch1_ctrl_thin(NULL, copy_param->xch, &xch_ctrl_thin );
		if( ret != D_IM_XCH_OK ){
			// Im_Xch_Ctrl_Thin error
			Ddim_Print(("I:im_xch2_copy_ex_async: im_xch1_ctrl_thin error. ret = 0x%X\n", ret));
			return ret;
		}
	}

	// Xch start(Async)
	ret = im_xch_start_async(NULL, copy_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Async error
		Ddim_Print(("I:im_xch2_copy_ex_async: im_xch_start_async error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 im_xch2_examine_histogram_sync( ImXch2*self,ImXchExamineHist* hist_param, ULONG* hist_buffer, UCHAR* hist_max )
{
	ImXchCtrlCmn	xch_ctrl_cmn;
	ImXchCtrlHist	xch_ctrl_hist;
	INT32				ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( hist_param == NULL ){
		// hist_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_examine_histogram_sync: Null check error. hist_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
	if( hist_max == NULL ){
		// hist_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_examine_histogram_sync: Null check error. hist_max = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_hist, 0, sizeof(ImXchCtrlHist) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= NULL;

	// set control structure
	im_xch2_conv_hist_param( NULL,hist_param, &xch_ctrl_cmn, &xch_ctrl_hist );

	// X0ch open
	ret = im_xch_open(NULL, ImXch_XCH_CH_SEL_0, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch2_examine_histogram_sync: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	// set control
	ret = im_xch1_ctrl_common(NULL, ImXch_XCH_CH_SEL_0, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		Ddim_Print(("I:im_xch2_examine_histogram_sync: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch1_ctrl_hist(NULL, ImXch_XCH_CH_SEL_0, &xch_ctrl_hist );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Hist error
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		Ddim_Print(("I:im_xch2_examine_histogram_sync: im_xch1_ctrl_hist error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Sync)
	ret = im_xch_start_sync(NULL, ImXch_XCH_CH_SEL_0 );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		Ddim_Print(("I:im_xch2_examine_histogram_sync: im_xch_start_sync error. ret = 0x%X\n", ret));
		return ret;
	}

#ifdef CO_DEBUG_ON_PC
	IO_XCH.XCHCTL0.XTRG.bit.XTRG = 2;
#endif //CO_DEBUG_ON_PC

	// Get histogram buffer
	ret = im_xch_get_histogram(NULL, hist_buffer );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
		Ddim_Print(("I:im_xch2_examine_histogram_sync: im_xch_get_histogram error. ret = 0x%X\n", ret));
		return ret;
	}

	// Get histogram max
	*hist_max = im_xch1_get_histogram_max(NULL);

	// X0ch close
	ret = im_xch_close(NULL,ImXch_XCH_CH_SEL_0 );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch2_examine_histogram_sync: Im_Xch_Close error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 Im_Xch_Examine_Histogram_Async( ImXch2*self,ImXchExamineHist* hist_param, VP_CALLBACK pCallBack )
{
	ImXchCtrlCmn	xch_ctrl_cmn;
	ImXchCtrlHist	xch_ctrl_hist;
	INT32				ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( hist_param == NULL ){
		// hist_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_examine_histogram_async: Null check error. hist_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_hist, 0, sizeof(ImXchCtrlHist) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= pCallBack;

	// set control structure
	im_xch2_conv_hist_param( NULL,hist_param, &xch_ctrl_cmn, &xch_ctrl_hist );

	// set control
	ret = im_xch1_ctrl_common(NULL, ImXch_XCH_CH_SEL_0, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		Ddim_Print(("I:im_xch2_examine_histogram_async: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}
	ret = im_xch1_ctrl_hist(NULL, ImXch_XCH_CH_SEL_0, &xch_ctrl_hist );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Hist error
		Ddim_Print(("I:im_xch2_examine_histogram_async: im_xch1_ctrl_hist error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Async)
	ret = im_xch_start_async(NULL, ImXch_XCH_CH_SEL_0 );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Async error
		Ddim_Print(("I:im_xch2_examine_histogram_async: im_xch_start_async error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 im_xch2_convert_thinning_sync( ImXch2*self,ImXchConvThin* thin_param )
{
	ImXchCtrlCmn		xch_ctrl_cmn;
	ImXchCtrlThin		xch_ctrl_thin;
	INT32					ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( thin_param == NULL ){
		// thin_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_convert_thinning_sync. Null check error. thin_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_thin, 0, sizeof(ImXchCtrlThin) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= NULL;

	// set control structure
	ret = im_xch2_conv_thin_param( NULL,thin_param, &xch_ctrl_cmn, &xch_ctrl_thin );
	if( ret != D_IM_XCH_OK ){
		// im_xch_conv_thin_param error
		Ddim_Print(("I:im_xch2_convert_thinning_sync: im_xch2_conv_thin_param error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch open
	ret = im_xch_open(NULL, thin_param->xch, D_DDIM_WAIT_END_TIME );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Open error
		Ddim_Print(("I:im_xch2_convert_thinning_sync: im_xch_open error. ret = 0x%X\n", ret));
		return ret;
	}

	// set control
	ret = im_xch1_ctrl_common(NULL, thin_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		im_xch_close(NULL,thin_param->xch );
		Ddim_Print(("I:im_xch2_convert_thinning_sync: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}
	ret = im_xch1_ctrl_thin(NULL, thin_param->xch, &xch_ctrl_thin );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Fill error
		im_xch_close(NULL,thin_param->xch );
		Ddim_Print(("I:im_xch2_convert_thinning_sync: im_xch1_ctrl_thin error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Sync)
	ret = im_xch_start_sync(NULL, thin_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Sync error
		im_xch_close(NULL,thin_param->xch );
		Ddim_Print(("I:im_xch2_convert_thinning_sync: im_xch_start_sync error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch close
	ret = im_xch_close(NULL,thin_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Close error
		Ddim_Print(("I:im_xch2_convert_thinning_sync: Im_Xch_Close error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

INT32 im_xch2_convert_thinning_async( ImXch2*self,ImXchConvThin* thin_param, VP_CALLBACK pCallBack )
{
	ImXchCtrlCmn		xch_ctrl_cmn;
	ImXchCtrlThin		xch_ctrl_thin;
	INT32					ret = D_IM_XCH_OK;

#ifdef CO_PARAM_CHECK
	if( thin_param == NULL ){
		// thin_param is Error because of NULL
		Ddim_Assertion(("I:im_xch2_convert_thinning_async. thin_param = NULL\n"));
		return D_IM_XCH_INPUT_PARAM_ERR;
	}
#endif	// CO_PARAM_CHECK

	// initialize
	memset( &xch_ctrl_cmn, 0, sizeof(ImXchCtrlCmn) );
	memset( &xch_ctrl_thin, 0, sizeof(ImXchCtrlThin) );

	// set call back function
	xch_ctrl_cmn.pCallBack	= pCallBack;

	// set control structure
	ret = im_xch2_conv_thin_param( NULL,thin_param, &xch_ctrl_cmn, &xch_ctrl_thin );
	if( ret != D_IM_XCH_OK ){
		// im_xch_conv_thin_param error
		Ddim_Print(("I:im_xch2_convert_thinning_async: im_xch2_conv_thin_param error. ret = 0x%X\n", ret));
		return ret;
	}

	// set control
	ret = im_xch1_ctrl_common(NULL, thin_param->xch, &xch_ctrl_cmn );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Common error
		Ddim_Print(("I:im_xch2_convert_thinning_async: im_xch1_ctrl_common error. ret = 0x%X\n", ret));
		return ret;
	}

	ret = im_xch1_ctrl_thin(NULL, thin_param->xch, &xch_ctrl_thin );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Ctrl_Fill error
		Ddim_Print(("I:im_xch2_convert_thinning_async: im_xch1_ctrl_thin error. ret = 0x%X\n", ret));
		return ret;
	}

	// Xch start(Async)
	ret = im_xch_start_async(NULL, thin_param->xch );
	if( ret != D_IM_XCH_OK ){
		// Im_Xch_Start_Async error
		Ddim_Print(("I:im_xch2_convert_thinning_async: im_xch_start_async error. ret = 0x%X\n", ret));
		return ret;
	}

	return ret;
}

#endif	// CO_DDIM_UTILITY_USE

ImXch2 *im_xch2_new(void)
{
	ImXch2* self = k_object_new_with_private(IM_TYPE_XCH2,sizeof(ImXch2Private));
	return self;
}
