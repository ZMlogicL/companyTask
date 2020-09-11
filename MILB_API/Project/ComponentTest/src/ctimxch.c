/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-03
*@author            :吴雨莎
*@brief             :ctimxch
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*
*/

/**
 * @file		ct_im_xch.c
 * @brief		ct code for im_xch.
 * @note		None
 * @attention	None
 *
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#include <string.h>
#include <stdlib.h>

//#include "ct_im_xch.h"
#include "ctimxch.h"
#include "im_xch.h"
#include "ddim_user_custom.h"
#include "jdsxch.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImXch, ct_im_xch)
#define CT_IM_XCH_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), CtImXchPrivate, CT_TYPE_IM_XCH))

#define CtImXch_D_CT_XCH_TOUT		(3000)


typedef enum {
	CtImXch_E_CT_XCH_PRINT_PTN_COMM = 0,
	CtImXch_E_CT_XCH_PRINT_PTN_THIN,
	CtImXch_E_CT_XCH_PRINT_PTN_HALF_THIN,
	CtImXch_E_CT_XCH_PRINT_PTN_HIST,
	CtImXch_E_CT_XCH_PRINT_PTN_COPY,
	CtImXch_E_CT_XCH_PRINT_PTN_FILL
} CtImXchECtXchPrintPtn;


struct  _CtImXchPrivate
{
	UCHAR sGctXchCb0EndFlag;
	UCHAR sGctXchCb1EndFlag;
	ULONG sGctXchHistBuffer[256];
};


#ifdef D_IM_XCH_PRINT_ST
extern void Im_Xch_Print_ClockStatus( void );
#endif


/*
 * DECLS
 */
static void ctXchCtrlPrint( CtImXchECtXchPrintPtn ptn, void* ctrl );


/*
 *IMPL
 */
static void ct_im_xch_constructor(CtImXch *self)
{
	CtImXchPrivate *priv = CT_IM_XCH_GET_PRIVATE(self);
	priv->sGctXchCb0EndFlag = 0;
	priv->sGctXchCb1EndFlag = 0;
	//sGctXchHistBuffer
}

static void ct_im_xch_destructor(CtImXch *self)
{
}

static void ctXchCtrlPrint( CtImXchECtXchPrintPtn ptn, void* ctrl )
{
	ImXchCtrlThin thin;
	ImXchCtrlHalfThin halfThin;
	ImXchCtrlHist hist;
	ImXchCtrlCopy copy;
	ImXchCtrlCmn com;

	switch( ptn ) {
		case CtImXch_E_CT_XCH_PRINT_PTN_THIN:
			memcpy( &thin, ctrl, sizeof(ImXchCtrlThin) );
			Ddim_Print(("Thin Setting print start\n"));
			Ddim_Print(("xdtype [0x%X]\n", thin.xdtype));
			Ddim_Print(("hcyc [0x%X]\n", thin.hcyc));
			Ddim_Print(("vcyc [0x%X]\n", thin.vcyc));
			Ddim_Print(("hen [0x%X]\n", thin.hen));
			Ddim_Print(("ven [0x%X]\n", thin.ven));
			Ddim_Print(("sHsize [%d]\n", thin.sHsize));
			Ddim_Print(("srcAddr [0x%X]\n", thin.srcAddr));
			Ddim_Print(("Thin Setting print end\n"));
			break;
		case CtImXch_E_CT_XCH_PRINT_PTN_HALF_THIN:
			memcpy( &halfThin, ctrl, sizeof(ImXchCtrlHalfThin) );
			Ddim_Print(("Half Thin Setting print start\n"));
			Ddim_Print(("vcyc [0x%X]\n", halfThin.vcyc));
			Ddim_Print(("ven [0x%X]\n", halfThin.ven));
			Ddim_Print(("sHsize [%d]\n", halfThin.sHsize));
			Ddim_Print(("srcAddr [0x%X]\n", halfThin.srcAddr));
			Ddim_Print(("Half Thin Setting print end\n"));
			break;
		case CtImXch_E_CT_XCH_PRINT_PTN_HIST:
			memcpy( &hist, ctrl, sizeof(ImXchCtrlHist) );
			Ddim_Print(("Hist Setting print start\n"));
			Ddim_Print(("xdtype [0x%X]\n", hist.xdtype));
			Ddim_Print(("hcyc [0x%X]\n", hist.hcyc));
			Ddim_Print(("vcyc [0x%X]\n", hist.vcyc));
			Ddim_Print(("hen [0x%X]\n", hist.hen));
			Ddim_Print(("ven [0x%X]\n", hist.ven));
			Ddim_Print(("sHsize [%d]\n", hist.sHsize));
			Ddim_Print(("srcAddr [0x%X]\n", hist.srcAddr));
			Ddim_Print(("hcnt [0x%X]\n", hist.hcnt));
			Ddim_Print(("Hist Setting print end\n"));
			break;
		case CtImXch_E_CT_XCH_PRINT_PTN_COPY:
			memcpy( &copy, ctrl, sizeof(ImXchCtrlCopy) );
			Ddim_Print(("Copy Setting print start\n"));
			Ddim_Print(("vcyc [0x%X]\n", copy.vcyc));
			Ddim_Print(("ven [0x%X]\n", copy.ven));
			Ddim_Print(("sHsize [%d]\n", copy.sHsize));
			Ddim_Print(("srcAddr [0x%X]\n", copy.srcAddr));
			Ddim_Print(("Copy Setting print end\n"));
			break;
		case CtImXch_E_CT_XCH_PRINT_PTN_COMM:
		default:
			memcpy( &com, ctrl, sizeof(ImXchCtrlCmn) );
			Ddim_Print(("Common Setting print start\n"));
			Ddim_Print(("mode [0x%X]\n", com.mode));
			Ddim_Print(("gHsize [%d]\n", com.gHsize));
			Ddim_Print(("dHsize [%d]\n", com.dHsize));
			Ddim_Print(("dVsize [%d]\n", com.dVsize));
			Ddim_Print(("dstAddr [0x%X]\n", com.dstAddr));
			Ddim_Print(("Common Setting print end\n"));
			break;
	}
	return;
}


/*
 * PUBLIC
 */
void ct_im_xch_callback_0_cb( void )
{
	CtImXch *self = ct_im_xch_get();
	CtImXchPrivate *priv = CT_IM_XCH_GET_PRIVATE(self);
	priv->sGctXchCb0EndFlag = 1;		// process normal end
	Ddim_Print(("----- ct_x0ch_callback -----\n"));
	return;
}

void ct_im_xch_callback_1_cb( void )
{
	CtImXch *self = ct_im_xch_get();
	CtImXchPrivate *priv = CT_IM_XCH_GET_PRIVATE(self);

	priv->sGctXchCb1EndFlag = 1;		// process normal end
	Ddim_Print(("----- ct_x1ch_callback -----\n"));
	return;
}

/**
 * @brief  Command main function for Xch test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 */
void ct_im_xch_main( CtImXch *self, kint32 argc, CHAR** argv )
{
	kint32 ret;
	kint32 ctArg1;
	ImXchEImXchChSel xch = ImXch_E_IM_XCH_CH_SEL_0;
	CtImXchPrivate *priv = CT_IM_XCH_GET_PRIVATE(self);

	ctArg1 = atoi((const kchar *)argv[1]);

	if( ctArg1 != 0
	&&	ctArg1 != 10
	&&	ctArg1 != 11
	&&	ctArg1 != 18
	&&	ctArg1 != 20
	&&	ctArg1 != 26
	&&	ctArg1 != 27
	&&	ctArg1 != 28
	&&	ctArg1 != 35
	&&	ctArg1 != 36
	&&	ctArg1 != 37 ) {
		if( atoi((const kchar *)argv[2] ) == 0 ) {
			xch = ImXch_E_IM_XCH_CH_SEL_0;
		} else {
			xch = ImXch_E_IM_XCH_CH_SEL_1;
		}
	}

	if( argc > 1 ) {
		// im_xch_init
		if( ctArg1 == 0 ) {

#ifdef CO_DEBUG_ON_PC
		memset( (USHORT*)&ioXch, 0, sizeof(ioXch) );
#endif

#ifdef CO_DEBUG_ON_PC
			ioXch.SR.bit.SR = 1;
#endif
			im_xch_init();
			Ddim_Print(( "im_xch_init()\n"));
		}
		// im_xch_open
		else if( ctArg1 == 1 ) {
			kint32 tmout;

			tmout = atoi((const kchar *)argv[3]);

			ret = im_xch_open( xch, tmout );

			Ddim_Print(( "im_xch_open() ret = 0x%X\n", ret));
		}
		// im_xch_close
		else if( ctArg1 == 2 ) {
			ret = im_xch_close( xch );

			Ddim_Print(( "im_xch_close() ret = 0x%X\n", ret));
		}
		// im_xch1_ctrl_common
		else if( ctArg1 == 3 ) {
			ImXchCtrlCmn ctrlCmn;

			ctrlCmn.mode = atoi((const kchar *)argv[3]);
			ctrlCmn.gHsize = atoi((const kchar *)argv[4]);
			ctrlCmn.dHsize = atoi((const kchar *)argv[5]);
			ctrlCmn.dVsize = atoi((const kchar *)argv[6]);
			ctrlCmn.dstAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;
			ctrlCmn.pCallBack = NULL;

			if( atoi((const kchar *)argv[7]) == 1 ) {
				if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
					priv->sGctXchCb0EndFlag = 0;
					ctrlCmn.pCallBack = (VpCallbackFunc)ct_im_xch_callback_0_cb;
				} else {
					priv->sGctXchCb1EndFlag = 0;
					ctrlCmn.pCallBack = (VpCallbackFunc)ct_im_xch_callback_1_cb;
				}
			}
			ctXchCtrlPrint( CtImXch_E_CT_XCH_PRINT_PTN_COMM, (void *)&ctrlCmn );

			ret = im_xch1_ctrl_common( xch, &ctrlCmn );

			Ddim_Print(( "im_xch1_ctrl_common() ret = 0x%X\n", ret));
		}
		// im_xch1_ctrl_thin
		else if( ctArg1 == 4 ) {
			ImXchCtrlThin ctrlThin;
			kuint32 cyc;
			kuint32 ptn;

			ctrlThin.xdtype = atoi((const kchar *)argv[3]);
			cyc = atoi((const kchar *)argv[4]);
			ctrlThin.hcyc = cyc;
			ctrlThin.vcyc = cyc;

			ptn = strtoul((const kchar *)argv[5], NULL, 0);
			ctrlThin.hen = ptn;		/* pgr0539 */
			ctrlThin.ven = ptn;		/* pgr0539 */

			ctrlThin.sHsize = strtoul((const kchar *)argv[6], NULL, 0);
			ctrlThin.srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;

			ctXchCtrlPrint( CtImXch_E_CT_XCH_PRINT_PTN_THIN, (void *)&ctrlThin );

			ret = im_xch1_ctrl_thin( xch, &ctrlThin );

			Ddim_Print(( "im_xch1_ctrl_thin() ret = 0x%X\n", ret));
		}
		// im_xch1_ctrl_hist
		else if( ctArg1 == 5 ) {
			ImXchCtrlHist ctrlHist;
			kuint32 cyc;
			kuint32 ptn;

			ctrlHist.xdtype = atoi((const kchar *)argv[3]);
			cyc = atoi((const kchar *)argv[4]);
			ctrlHist.hcyc = cyc;
			ctrlHist.vcyc = cyc;

			// dsp pattern
			ptn = strtoul((const kchar *)argv[5], NULL, 0);
			ctrlHist.hen = ptn;		/* pgr0539 */
			ctrlHist.ven = ptn;		/* pgr0539 */

			ctrlHist.sHsize = atoi((const kchar *)argv[6]);
			ctrlHist.srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			ctrlHist.hcnt = atoi((const kchar *)argv[7]);

			// degug print
			ctXchCtrlPrint( CtImXch_E_CT_XCH_PRINT_PTN_HIST, (void *)&ctrlHist );

			ret = im_xch1_ctrl_hist( xch, &ctrlHist );

			Ddim_Print(( "im_xch1_ctrl_hist() ret = 0x%X\n", ret));
		}
		// im_xch1_ctrl_half_thin
		else if( ctArg1 == 6 ) {
			ImXchCtrlHalfThin ctrlHalfThin;
			kuint32 cyc;
			kuint32 ptn;

			cyc = atoi((const kchar *)argv[3]);
			ctrlHalfThin.vcyc = cyc;

			ptn = strtoul((const kchar *)argv[4], NULL, 0);
			ctrlHalfThin.ven = ptn;	/* pgr0539 */

			ctrlHalfThin.sHsize = atoi((const kchar *)argv[5]);
			ctrlHalfThin.srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;

			// degug print
			ctXchCtrlPrint( CtImXch_E_CT_XCH_PRINT_PTN_HALF_THIN, (void *)&ctrlHalfThin );

			ret = im_xch1_ctrl_half_thin( xch, &ctrlHalfThin );

			Ddim_Print(( "im_xch1_ctrl_half_thin() ret = 0x%X\n", ret));
		} else if( ctArg1 == 7 ) {
			ImXchCtrlCopy ctrlCpy;
			kuint32 cyc;
			kuint32 ptn;

			cyc = atoi((const kchar *)argv[3]);
			ctrlCpy.vcyc = cyc;

			ptn = strtoul((const kchar *)argv[4], NULL, 10);
			ctrlCpy.ven	 = ptn;		/* pgr0539 */

			ctrlCpy.sHsize = atoi((const kchar *)argv[5]);
			ctrlCpy.srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;

			ctXchCtrlPrint( CtImXch_E_CT_XCH_PRINT_PTN_COPY, (void *)&ctrlCpy );

			ret = im_xch1_ctrl_copy( xch, &ctrlCpy );

			Ddim_Print(( "im_xch1_ctrl_copy() ret = 0x%X\n", ret));
		}
		// im_xch1_ctrl_fill
		else if( ctArg1 == 8 ) {
			UCHAR data;

			data = (UCHAR)atoi((const kchar *)argv[3]);

			ret = im_xch1_ctrl_fill( xch, data );

			Ddim_Print(( "im_xch1_ctrl_fill() ret = 0x%X\n", ret));
		}
		// im_xch_start_sync
		// im_xch_start_async
		// im_xch_wait_end
		else if( ctArg1 == 9 ) {
			kuint32 syncPtn;

			syncPtn = atoi((const kchar *)argv[3]);

			if( syncPtn == 0 ) {
			// Sync
				ret = im_xch_start_sync( xch );
				Ddim_Print(( "im_xch_start_sync() ret = 0x%X\n", ret));
			} else if( syncPtn == 1 ) {
			// Async wait end
				ret = im_xch_start_async( xch );
				Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));
				if( ret == D_IM_XCH_OK ) {
#ifdef CO_DEBUG_ON_PC
					if( xch == 0 ) {
						ioXch.XCHICE.bit.XE0 = 1;
						ioXch.XCHICF.bit.__XF0 = 1;
					}
					else{
						ioXch.XCHICE.bit.XE1 = 1;
						ioXch.XCHICF.bit.__XF1 = 1;
					}
					im_xch_int_handler();
#endif
					ret = im_xch_wait_end( xch );
					Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret));
				}
			} else if( syncPtn == 2 ) {
			// Async callback
				ret = im_xch_start_async( xch );
				Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));

				if( ret == D_IM_XCH_OK ) {
#ifdef CO_DEBUG_ON_PC
					if( xch == 0 ) {
						ioXch.XCHICE.bit.XE0 = 1;
						ioXch.XCHICF.bit.__XF0 = 1;
					} else {
						ioXch.XCHICE.bit.XE1 = 1;
						ioXch.XCHICF.bit.__XF1 = 1;
					}
					im_xch_int_handler();
#endif
					if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
						while( !priv->sGctXchCb0EndFlag ) {
							DDIM_User_Tslp_Tsk( 10 );		// wait 10ms
						}
						Ddim_Print(("----- Callback 0ch End -----\n"));
					} else {
						while( !priv->sGctXchCb1EndFlag ) {
							DDIM_User_Tslp_Tsk( 10 );		// wait 10ms
						}
						Ddim_Print(("----- Callback 1ch End -----\n"));
					}
				}
			} else {
				Ddim_Print(("input parameter error\n"));
			}
		}
		// im_xch1_get_histogram_max
		else if( ctArg1 == 10 ) {
			UCHAR max;

			max = im_xch1_get_histogram_max();

			Ddim_Print(( "im_xch1_get_histogram_max() Max = %d\n", max ));
		}
		// im_xch_get_histogram
		else if( ctArg1 == 11 ) {

			memset( &priv->sGctXchHistBuffer, 0, sizeof(priv->sGctXchHistBuffer) );

			ret = im_xch_get_histogram( priv->sGctXchHistBuffer );
			Ddim_Print(( "im_xch_get_histogram() ret = 0x%X\n", ret ));

			if( ret == D_IM_XCH_OK ) {
				Ddim_Print(("***** priv->sGctXchHistBuffer[  0] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[0]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[ 50] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[50]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[100] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[100]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[150] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[150]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[200] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[200]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[250] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[250]));
				Ddim_Print(("***** priv->sGctXchHistBuffer[255] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[255]));
			}
		}
		// im_xch1_get_ctrl_common
		else if( ctArg1 == 12 ) {
			ImXchCtrlCmn ctrlCmn;

			memset( &ctrlCmn, 0, sizeof(ctrlCmn) );

			ret = im_xch1_get_ctrl_common( xch, &ctrlCmn );
			Ddim_Print(( "im_xch1_get_ctrl_common() ret = 0x%X\n", ret ));

			if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
				Ddim_Print(( "ioXch.XCHCTL0.XMD = %d\n" , ctrlCmn.mode ));
				Ddim_Print(( "ioXch.XCHCTL0.XGHW = 0x%X\n" , ctrlCmn.gHsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XDHW = 0x%X\n" , ctrlCmn.dHsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XDVW = 0x%X\n" , ctrlCmn.dVsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XDA = 0x%X\n" , ctrlCmn.dstAddr ));
			} else {
				Ddim_Print(( "ioXch.XCHCTL1.XMD = %d\n"  , ctrlCmn.mode ));
				Ddim_Print(( "ioXch.XCHCTL1.XGHW = 0x%X\n", ctrlCmn.gHsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XDHW = 0x%X\n", ctrlCmn.dHsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XDVW = 0x%X\n", ctrlCmn.dVsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XDA = 0x%X\n", ctrlCmn.dstAddr ));
			}
		}
		// im_xch1_get_ctrl_thin
		else if( ctArg1 == 13 ) {
			ImXchCtrlThin ctrlThin;

			memset( &ctrlThin, 0, sizeof(ctrlThin) );

			ret = im_xch1_get_ctrl_thin( xch, &ctrlThin );
			Ddim_Print(( "im_xch1_get_ctrl_thin() ret = 0x%X\n", ret ));

			if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
				Ddim_Print(( "ioXch.XCHCTL0.XDTYPE     = %d\n"  , ctrlThin.xdtype ));
				Ddim_Print(( "ioXch.XCHCTL0.XCYC.XHCYC = 0x%X\n", ctrlThin.hcyc ));
				Ddim_Print(( "ioXch.XCHCTL0.XCYC.XVCYC = 0x%X\n", ctrlThin.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL0.XHEN = 0x%X\n", ctrlThin.hen ));
				Ddim_Print(( "ioXch.XCHCTL0.XVEN = 0x%X\n", ctrlThin.ven ));
				Ddim_Print(( "ioXch.XCHCTL0.XSHW = 0x%X\n", ctrlThin.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XSA = 0x%X\n", ctrlThin.srcAddr ));
			} else {
				Ddim_Print(( "ioXch.XCHCTL1.XDTYPE     = %d\n"  , ctrlThin.xdtype ));
				Ddim_Print(( "ioXch.XCHCTL1.XCYC.XHCYC = 0x%X\n", ctrlThin.hcyc ));
				Ddim_Print(( "ioXch.XCHCTL1.XCYC.XVCYC = 0x%X\n", ctrlThin.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL1.XHEN = 0x%X\n", ctrlThin.hen ));
				Ddim_Print(( "ioXch.XCHCTL1.XVEN = 0x%X\n", ctrlThin.ven ));
				Ddim_Print(( "ioXch.XCHCTL1.XSHW = 0x%X\n", ctrlThin.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XSA = 0x%X\n", ctrlThin.srcAddr ));
			}
		}
		// im_xch1_get_ctrl_hist
		else if( ctArg1 == 14 ) {
			ImXchCtrlHist ctrlHist;

			memset( &ctrlHist, 0, sizeof(ctrlHist) );

			ret = im_xch1_get_ctrl_hist( xch, &ctrlHist );
			Ddim_Print(( "im_xch1_get_ctrl_hist() ret = 0x%X\n", ret ));

			Ddim_Print(( "ioXch.XCHCTL0.XDTYPE = %d\n" , ctrlHist.xdtype ));
			Ddim_Print(( "ioXch.XCHCTL0.XCYC.XHCYC = 0x%X\n" , ctrlHist.hcyc ));
			Ddim_Print(( "ioXch.XCHCTL0.XCYC.XVCYC = 0x%X\n" , ctrlHist.vcyc ));
			Ddim_Print(( "ioXch.XCHCTL0.XHEN = 0x%X\n", ctrlHist.hen ));
			Ddim_Print(( "ioXch.XCHCTL0.XVEN = 0x%X\n" , ctrlHist.ven ));
			Ddim_Print(( "ioXch.XCHCTL0.XSHW = 0x%X\n" , ctrlHist.sHsize ));
			Ddim_Print(( "ioXch.XCHCTL0.XSA = 0x%X\n" , ctrlHist.srcAddr ));
			Ddim_Print(( "ioXch.XHISTG0.XHCNT0 = %d\n" , ctrlHist.hcnt ));
		}
		// im_xch1_get_ctrl_half_thin
		else if( ctArg1 == 15 ) {
			ImXchCtrlHalfThin ctrlHalfThin;

			memset( &ctrlHalfThin, 0, sizeof(ctrlHalfThin) );

			ret = im_xch1_get_ctrl_half_thin( xch, &ctrlHalfThin );
			Ddim_Print(( "im_xch1_get_ctrl_half_thin() ret = 0x%X\n", ret ));

			if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
				Ddim_Print(( "ioXch.XCHCTL0.XCYC.XVCYC = 0x%X\n", ctrlHalfThin.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL0.XVEN = 0x%X\n", ctrlHalfThin.ven ));
				Ddim_Print(( "ioXch.XCHCTL0.XSHW = 0x%X\n", ctrlHalfThin.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XSA = 0x%X\n", ctrlHalfThin.srcAddr ));
			} else {
				Ddim_Print(( "ioXch.XCHCTL1.XCYC.XVCYC = 0x%X\n", ctrlHalfThin.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL1.XVEN = 0x%X\n", ctrlHalfThin.ven ));
				Ddim_Print(( "ioXch.XCHCTL1.XSHW = 0x%X\n", ctrlHalfThin.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XSA = 0x%X\n", ctrlHalfThin.srcAddr ));
			}

		}
		// im_xch1_get_ctrl_copy
		else if( ctArg1 == 16 ) {
			ImXchCtrlCopy ctrlCpy;

			memset( &ctrlCpy, 0, sizeof(ctrlCpy) );

			ret = im_xch1_get_ctrl_copy( xch, &ctrlCpy );
			Ddim_Print(( "im_xch1_get_ctrl_copy() ret = 0x%X\n", ret ));

			if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
				Ddim_Print(( "ioXch.XCHCTL0.XCYC.XVCYC = 0x%X\n", ctrlCpy.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL0.XVEN = 0x%X\n", ctrlCpy.ven ));
				Ddim_Print(( "ioXch.XCHCTL0.XSHW = 0x%X\n", ctrlCpy.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL0.XSA = 0x%X\n", ctrlCpy.srcAddr ));
			} else {
				Ddim_Print(( "ioXch.XCHCTL1.XCYC.XVCYC = 0x%X\n", ctrlCpy.vcyc ));
				Ddim_Print(( "ioXch.XCHCTL1.XVEN = 0x%X\n", ctrlCpy.ven ));
				Ddim_Print(( "ioXch.XCHCTL1.XSHW = 0x%X\n", ctrlCpy.sHsize ));
				Ddim_Print(( "ioXch.XCHCTL1.XSA = 0x%X\n", ctrlCpy.srcAddr ));
			}

		}
		// im_xch1_get_ctrl_fill
		else if( ctArg1 == 17 ) {
			UCHAR data;

			ret = im_xch1_get_ctrl_fill( xch, &data );
			Ddim_Print(( "im_xch1_get_ctrl_fill() ret = 0x%X\n", ret ));

			if( xch == ImXch_E_IM_XCH_CH_SEL_0 ) {
				Ddim_Print(( "ioXch.XCHCTL0.XFDT = 0x%X\n", data ));
			} else {
				Ddim_Print(( "ioXch.XCHCTL1.XFDT = 0x%X\n", data ));
			}
		}
		// im_xch_stop
		else if( ctArg1 == 18 ) {
			ret = im_xch_stop();
			Ddim_Print(( "im_xch_stop() ret = 0x%X\n", ret ));
		}
		// im_xch1_get_xtrg
		else if( ctArg1 == 19 ) {
			ImXchEImXchSt st;

			if( atoi((const kchar *)argv[3]) == 1 ) {
				ret = im_xch_start_async( xch );
				Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));
			}

			ret = im_xch1_get_xtrg( xch, &st );
			Ddim_Print(( "im_xch1_get_xtrg() ret = 0x%X\n", ret ));

			if( st == ImXch_E_IM_XCH_ST_RUNNING ) {
				Ddim_Print(( "X%dch Running\n", xch ));
			} else {
				Ddim_Print(( "X%dch Stopped\n", xch ));
			}
		}
		// im_xch_int_handler
		else if( ctArg1 == 20 ) {
			im_xch_int_handler();
#ifdef CO_DEBUG_ON_PC
			Ddim_Print(( "ioXch.XCHICF.bit.__XF0 = 0x%X\n", ioXch.XCHICF.bit.__XF0 ));
			Ddim_Print(( "ioXch.XCHICF.bit.__XF1 = 0x%X\n", ioXch.XCHICF.bit.__XF1 ));
#endif
		}
		// im_xch2_copy
		else if( ctArg1 == 21 ) {
			kuint32 srcAddr;
			kuint32 dstAddr;
			kuint32 srcGlWidth;
			kuint32 dstGlWidth;
			kuint32 width;
			kuint32 lines;

			srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			dstAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			width = atoi((const kchar *)argv[3]);
			lines = atoi((const kchar *)argv[4]);
			srcGlWidth = width;
			dstGlWidth = width;

			ret = im_xch2_copy( xch, srcAddr, srcGlWidth, dstGlWidth, dstAddr, width, lines );
			Ddim_Print(( "im_xch2_copy() ret = 0x%X\n", ret ));
		}
		// im_xch2_copy_ex_sync
		// im_xch2_copy_ex_async
		else if( ctArg1 == 22 ) {
			ImXchCopyEx ctrlCpyEx;
			ImXchEImXchCopySel type;
			kuint32 gWidth;
			kuint32 width;
			kuint32 lines;
			kuint32 syncType;

			if( atoi((const kchar *)argv[3]) == 0 ) {
				type = ImXch_E_IM_XCH_COPY_SEL_HI;
			} else {
				type = ImXch_E_IM_XCH_COPY_SEL_NORMAL;
			}

			gWidth = atoi((const kchar *)argv[4]);
			width = atoi((const kchar *)argv[5]);
			lines = atoi((const kchar *)argv[6]);
			syncType = atoi((const kchar *)argv[7]);

			ctrlCpyEx.xch = xch;
			ctrlCpyEx.copyType = type;
			ctrlCpyEx.size.width = width;
			ctrlCpyEx.size.lines = lines;
			ctrlCpyEx.size.srcGlWidth = width;
			ctrlCpyEx.size.dstGlWidth = gWidth;
			ctrlCpyEx.addr.src = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			ctrlCpyEx.addr.dst = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			if( syncType == 0 ) {
			// Sync
				ret = im_xch2_copy_ex_sync( &ctrlCpyEx );
				Ddim_Print(( "im_xch2_copy_ex_sync() ret = 0x%X\n", ret ));
			} else {
			// Async
				ret = im_xch_open( xch, CtImXch_D_CT_XCH_TOUT );
				Ddim_Print(( "im_xch_open() ret = 0x%X\n", ret ));

				ret = im_xch2_copy_ex_async( &ctrlCpyEx, NULL );
				Ddim_Print(( "im_xch2_copy_ex_async() ret = 0x%X\n", ret ));
#ifdef CO_DEBUG_ON_PC
				if( xch == 0 ) {
					ioXch.XCHICE.bit.XE0 = 1;
					ioXch.XCHICF.bit.__XF0 = 1;
				} else {
					ioXch.XCHICE.bit.XE1 = 1;
					ioXch.XCHICF.bit.__XF1 = 1;
				}
				im_xch_int_handler();
#endif
				ret = im_xch_wait_end( xch );
				Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret ));

				ret = im_xch_close( xch );
				Ddim_Print(( "im_xch_close() ret = 0x%X\n", ret ));
			}
		}
		// im_xch_fill
		else if( ctArg1 == 23 ) {
			kuint32 fillData;
			kuint32 glWidth;
			kuint32 width;
			kuint32 lines;
			kuint32 dstAddr;

			glWidth = atoi((const kchar *)argv[3]);
			width = atoi((const kchar *)argv[4]);
			lines = atoi((const kchar *)argv[5]);
			fillData = atoi((const kchar *)argv[6]);
			dstAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			ret = im_xch_fill( xch, fillData, glWidth, dstAddr, width, lines );
			Ddim_Print(( "im_xch_fill() ret = 0x%X\n", ret ));
		}
		// im_xch_fill_ex_sync
		// im_xch_fill_ex_async
		else if( ctArg1 == 24 ) {
			ImXchFillEx ctrlFillEx;
			kuint32 syncType;

			ctrlFillEx.xch = xch;
			ctrlFillEx.size.glWidth = atoi((const kchar *)argv[3]);
			ctrlFillEx.size.width = atoi((const kchar *)argv[4]);
			ctrlFillEx.size.lines = atoi((const kchar *)argv[5]);
			ctrlFillEx.fillData = atoi((const kchar *)argv[6]);
			ctrlFillEx.fillAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			syncType = atoi((const kchar *)argv[7]);

			if( syncType == 0 ) {
			// Sync
				ret = im_xch_fill_ex_sync( &ctrlFillEx );
				Ddim_Print(( "im_xch_fill_ex_sync() ret = 0x%X\n", ret ));
			} else {
			// Async
				ret = im_xch_open( xch, CtImXch_D_CT_XCH_TOUT );
				Ddim_Print(( "im_xch_open() ret = 0x%X\n", ret ));

				ret = im_xch_fill_ex_async( &ctrlFillEx, NULL );
				Ddim_Print(( "im_xch_fill_ex_async() ret = 0x%X\n", ret ));
#ifdef CO_DEBUG_ON_PC
				if( xch == 0 ) {
					ioXch.XCHICE.bit.XE0 = 1;
					ioXch.XCHICF.bit.__XF0 = 1;
				} else {
					ioXch.XCHICE.bit.XE1 = 1;
					ioXch.XCHICF.bit.__XF1 = 1;
				}
				im_xch_int_handler();
#endif

				ret = im_xch_wait_end( xch );
				Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret ));

				ret = im_xch_close( xch );
				Ddim_Print(( "im_xch_close() ret = 0x%X\n", ret ));
			}
		}
		// im_xch2_convert_thinning_sync
		// im_xch2_convert_thinning_async
		else if( ctArg1 == 25 ) {
			ImXchConvThin ctrlThinEx;
			kuint32 srcGlWidth;
			kuint32 dstGlWidth;
			kuint32 width;
			kuint32 lines;
			kuint32 syncType;

			ctrlThinEx.xch = xch;

			switch( atoi((const kchar *)argv[3]) ) {
				case 0:
					ctrlThinEx.thinWidth = ImXch_D_IM_XCH_THIN_SEL_1_1;
					break;
				case 1:
					ctrlThinEx.thinWidth = ImXch_D_IM_XCH_THIN_SEL_1_2;
					break;
				case 2:
					ctrlThinEx.thinWidth = ImXch_D_IM_XCH_THIN_SEL_1_4;
					break;
				case 3:
					ctrlThinEx.thinWidth = ImXch_D_IM_XCH_THIN_SEL_3_4;
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					return;
			}

			switch( atoi((const kchar *)argv[4]) ) {
				case 0:
					ctrlThinEx.thinLines = ImXch_D_IM_XCH_THIN_SEL_1_1;
					break;
				case 1:
					ctrlThinEx.thinLines = ImXch_D_IM_XCH_THIN_SEL_1_2;
					break;
				case 2:
					ctrlThinEx.thinLines = ImXch_D_IM_XCH_THIN_SEL_1_4;
					break;
				case 3:
					ctrlThinEx.thinLines = ImXch_D_IM_XCH_THIN_SEL_3_4;
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					return;
			}

			dstGlWidth = atoi((const kchar *)argv[5]);
			width = atoi((const kchar *)argv[6]);
			lines = atoi((const kchar *)argv[7]);
			srcGlWidth = width;

			ctrlThinEx.size.width = width;
			ctrlThinEx.size.lines = lines;
			ctrlThinEx.size.srcGlWidth = srcGlWidth;
			ctrlThinEx.size.dstGlWidth = dstGlWidth;
			ctrlThinEx.addr.src = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			ctrlThinEx.addr.dst = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			syncType = atoi((const kchar *)argv[8]);

			if( syncType == 0 ) {
			// Sync
				ret = im_xch2_convert_thinning_sync( &ctrlThinEx );
				Ddim_Print(( "im_xch2_convert_thinning_sync() ret = 0x%X\n", ret ));
			}
			else{
			// Async
				ret = im_xch_open( xch, CtImXch_D_CT_XCH_TOUT );
				Ddim_Print(( "im_xch_open() ret = 0x%X\n", ret ));

				ret = im_xch2_convert_thinning_async( &ctrlThinEx, NULL );
				Ddim_Print(( "im_xch2_convert_thinning_async() ret = 0x%X\n", ret ));

#ifdef CO_DEBUG_ON_PC
				if( xch == 0 ) {
					ioXch.XCHICE.bit.XE0 = 1;
					ioXch.XCHICF.bit.__XF0 = 1;
				} else {
					ioXch.XCHICE.bit.XE1 = 1;
					ioXch.XCHICF.bit.__XF1 = 1;
				}
				im_xch_int_handler();
#endif
				ret = im_xch_wait_end( xch );
				Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret ));

				ret = im_xch_close( xch );
				Ddim_Print(( "im_xch_close() ret = 0x%X\n", ret ));
			}
		}
		// im_xch2_examine_histogram_sync
		// im_xch2_examine_histogram_async
		else if( ctArg1 == 26 ) {
			ImXchExamineHist ctrlHistEx;
			UCHAR histMax;
			kuint32 syncType;

			ctrlHistEx.histAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;

			ctrlHistEx.size.width = atoi((const kchar *)argv[2]);
			ctrlHistEx.size.lines = atoi((const kchar *)argv[3]);
			syncType = atoi((const kchar *)argv[4]);
			memset( &priv->sGctXchHistBuffer, 0, sizeof(priv->sGctXchHistBuffer) );

			if( syncType == 0 ) {
			// Sync
				ret = im_xch2_examine_histogram_sync( &ctrlHistEx, priv->sGctXchHistBuffer, &histMax );
				Ddim_Print(( "im_xch2_examine_histogram_sync() ret = 0x%X\n", ret ));
				Ddim_Print(( "Histogram Max = %d\n", histMax ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[  0] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[0] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[ 50] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[50] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[100] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[100] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[150] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[150] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[200] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[200] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[250] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[250] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[255] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[255] ));
			} else {
			// Async
				ret = im_xch_open( ImXch_E_IM_XCH_CH_SEL_0, CtImXch_D_CT_XCH_TOUT );
				Ddim_Print(( "im_xch_open() ret = 0x%X\n", ret ));

				ret = im_xch2_examine_histogram_async( &ctrlHistEx, NULL );
				Ddim_Print(( "im_xch2_examine_histogram_async() ret = 0x%X\n", ret ));

#ifdef CO_DEBUG_ON_PC
				if( xch == 0 ) {
					ioXch.XCHICE.bit.XE0 = 1;
					ioXch.XCHICF.bit.__XF0 = 1;
				} else {
					ioXch.XCHICE.bit.XE1 = 1;
					ioXch.XCHICF.bit.__XF1 = 1;
				}
				im_xch_int_handler();
#endif
				ret = im_xch_wait_end( ImXch_E_IM_XCH_CH_SEL_0 );
				Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret ));
#ifdef CO_DEBUG_ON_PC
				ioXch.XCHCTL0.XTRG.bit.XTRG = 2;
#endif
				histMax = im_xch1_get_histogram_max();
				Ddim_Print(( "im_xch1_get_histogram_max() Histogram Max = %d\n", histMax ));

				ret = im_xch_get_histogram( priv->sGctXchHistBuffer );
				Ddim_Print(( "im_xch_get_histogram() ret = 0x%X\n", ret ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[  0] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[0] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[ 50] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[50] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[100] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[100] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[150] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[150] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[200] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[200] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[250] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[250] ));
				Ddim_Print(( "***** priv->sGctXchHistBuffer[255] = 0x%lX *****\n",
						priv->sGctXchHistBuffer[255] ));

				ret = im_xch_close( ImXch_E_IM_XCH_CH_SEL_0 );
				Ddim_Print(( "im_xch_close() ret = 0x%X\n", ret ));
			}
		}
		// Im_Xch_Copy_Dual_Channel
		else if( ctArg1 == 27 ) {
			kuint32 width;
			kuint32 lines;
			kuint32 srcAddr;
			kuint32 dstAddr;
			kint32 size;

			width = atoi((const kchar *)argv[2]);
			lines = atoi((const kchar *)argv[3]);
			size = width * lines;

			srcAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			dstAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;

			ret = Im_Xch_Copy_Dual_Channel( (void *)dstAddr, (void *)srcAddr, size );
			Ddim_Print(( "Im_Xch_Copy_Dual_Channel() ret = 0x%X\n", ret ));
		}
		// Parameter Check
		else if( ctArg1 == 28 ) {
			ImXchCtrlCmn xchCtrlCmn;
			ImXchCtrlThin xchCtrlThin;
			ImXchCtrlHist xchCtrlHist;
			ImXchCtrlHalfThin xchCtrlHalfThin;
			ImXchCtrlCopy xchCtrlCopy;
			ImXchExamineHist xchHistParam;
			ImXchConvThin xchThinParam;
			UCHAR histMax;

			memset( &xchCtrlCmn, 0, sizeof(ImXchCtrlCmn) );
			memset( &xchCtrlThin, 0, sizeof(ImXchCtrlThin) );
			memset( &xchCtrlHist, 0, sizeof(ImXchCtrlHist) );
			memset( &xchCtrlHalfThin, 0, sizeof(ImXchCtrlHalfThin) );
			memset( &xchCtrlCopy, 0, sizeof(ImXchCtrlCopy) );
			memset( &xchHistParam, 0, sizeof(ImXchExamineHist) );
			memset( &xchThinParam, 0, sizeof(ImXchConvThin) );

			// im_xch_open
			ret = im_xch_open( ImXch_E_IM_XCH_CH_SEL_0, -2 );
			Ddim_Print(( "im_xch_open(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_common
			ret = im_xch1_ctrl_common( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_ctrl_common(): ret = 0x%X\n", ret ));

			xchCtrlCmn.mode = D_IM_XCH_MD_HISTGRAM_DOWN;
			ret = im_xch1_ctrl_common( ImXch_E_IM_XCH_CH_SEL_1, &xchCtrlCmn );
			Ddim_Print(( "im_xch1_ctrl_common(): ret = 0x%X\n", ret ));

			xchCtrlCmn.mode = D_IM_XCH_MD_HISTGRAM;
			ret = im_xch1_ctrl_common( ImXch_E_IM_XCH_CH_SEL_1, &xchCtrlCmn );
			Ddim_Print(( "im_xch1_ctrl_common(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_thin
			ret = im_xch1_ctrl_thin( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_ctrl_thin(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_hist
			ret = im_xch1_ctrl_hist( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_ctrl_hist(): ret = 0x%X\n", ret ));

			ret = im_xch1_ctrl_hist( ImXch_E_IM_XCH_CH_SEL_1, &xchCtrlHist );
			Ddim_Print(( "im_xch1_ctrl_hist(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_half_thin
			ret = im_xch1_ctrl_half_thin( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_ctrl_half_thin(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_copy
			ret = im_xch1_ctrl_copy( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_ctrl_copy(): ret = 0x%X\n", ret ));

			// im_xch1_ctrl_copy
			ret = im_xch_get_histogram( NULL );
			Ddim_Print(( "im_xch_get_histogram(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_common
			ret = im_xch1_get_ctrl_common( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_common(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_thin
			ret = im_xch1_get_ctrl_thin( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_thin(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_hist
			ret = im_xch1_get_ctrl_hist( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_hist(): ret = 0x%X\n", ret ));

			ret = im_xch1_get_ctrl_hist( ImXch_E_IM_XCH_CH_SEL_1, &xchCtrlHist );
			Ddim_Print(( "im_xch1_get_ctrl_hist(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_half_thin
			ret = im_xch1_get_ctrl_half_thin( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_half_thin(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_copy
			ret = im_xch1_get_ctrl_copy( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_copy(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_half_thin
			ret = im_xch1_get_ctrl_half_thin( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_half_thin(): ret = 0x%X\n", ret ));

			// im_xch1_get_ctrl_fill
			ret = im_xch1_get_ctrl_fill( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_ctrl_fill(): ret = 0x%X\n", ret ));

			// im_xch1_get_xtrg
			ret = im_xch1_get_xtrg( ImXch_E_IM_XCH_CH_SEL_0, NULL );
			Ddim_Print(( "im_xch1_get_xtrg(): ret = 0x%X\n", ret ));

			// im_xch2_copy_ex_sync
			ret = im_xch2_copy_ex_sync( NULL );
			Ddim_Print(( "im_xch2_copy_ex_sync(): ret = 0x%X\n", ret ));

			// im_xch2_copy_ex_async
			ret = im_xch2_copy_ex_async( NULL, NULL );
			Ddim_Print(( "im_xch2_copy_ex_async(): ret = 0x%X\n", ret ));

			// im_xch_fill_ex_sync
			ret = im_xch_fill_ex_sync( NULL );
			Ddim_Print(( "im_xch_fill_ex_sync(): ret = 0x%X\n", ret ));

			// im_xch_fill_ex_async
			ret = im_xch_fill_ex_async( NULL, NULL );
			Ddim_Print(( "im_xch_fill_ex_async(): ret = 0x%X\n", ret ));

			// im_xch2_examine_histogram_sync
			ret = im_xch2_examine_histogram_sync( NULL, NULL, &histMax );
			Ddim_Print(( "im_xch2_examine_histogram_sync(): ret = 0x%X\n", ret ));

			ret = im_xch2_examine_histogram_sync( &xchHistParam, NULL, NULL );
			Ddim_Print(( "im_xch2_examine_histogram_sync(): ret = 0x%X\n", ret ));

			// im_xch2_examine_histogram_async
			ret = im_xch2_examine_histogram_async( NULL, NULL );
			Ddim_Print(( "im_xch2_examine_histogram_async(): ret = 0x%X\n", ret ));

			// im_xch2_convert_thinning_sync
			ret = im_xch2_convert_thinning_sync( NULL );
			Ddim_Print(( "im_xch2_convert_thinning_sync(): ret = 0x%X\n", ret ));

			// im_xch2_convert_thinning_async
			ret = im_xch2_convert_thinning_async( NULL, NULL );
			Ddim_Print(( "im_xch2_convert_thinning_async(): ret = 0x%X\n", ret ));
		}
		// im_xch_start_sync
		else if( ctArg1 == 29 ) {
			ret = im_xch_start_sync( xch );
			Ddim_Print(( "im_xch_start_sync() ret = 0x%X\n", ret));
		}
		// im_xch_start_async
		else if( ctArg1 == 30 ) {
			ret = im_xch_start_async( xch );
			Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));
		}
		// im_xch_wait_end
		else if( ctArg1 == 31 ) {
			ret = im_xch_wait_end( xch );
			Ddim_Print(( "im_xch_wait_end() ret = 0x%X\n", ret));
		}
		// for Macro busy
		else if( ctArg1 == 32 ) {
			kint32 ctArg2;

			ctArg2 = atoi((const kchar *)argv[3]);

			ret = im_xch_start_async( xch );
			Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));

			switch( ctArg2 ) {
				case 0:
					ret = im_xch_start_sync( xch );
					Ddim_Print(( "im_xch_start_sync() ret = 0x%X\n", ret));
					break;
				case 1:
					ret = im_xch_start_async( xch );
					Ddim_Print(( "im_xch_start_async() ret = 0x%X\n", ret));
					break;
				case 2:
					ret = im_xch_get_histogram(priv->sGctXchHistBuffer);
					Ddim_Print(( "im_xch_get_histogram() ret = 0x%X\n", ret));
					break;
				default:
					Ddim_Print(("input parameter error\n"));
					return;
			}
		}
		// src area init
		else if( ctArg1 == 35 ) {
			ImXchFillEx ctrlFillEx;
			kuint32 ctArg2;
			kuint32 ctArg3;
			UCHAR dat;

			dat = atoi((const kchar *)argv[2]);
			ctArg2 = atoi((const kchar *)argv[3]);
			ctArg3 = atoi((const kchar *)argv[4]);

			ctrlFillEx.xch = ImXch_E_IM_XCH_CH_SEL_0;
			// Set fill data
			if( dat == 0 ) {
				ctrlFillEx.fillData = 0x00;
			} else {
				ctrlFillEx.fillData = dat;
			}

			if( ctArg2 == 0 ) {
				ctrlFillEx.size.glWidth = 0x4000;
				ctrlFillEx.size.width = ctrlFillEx.size.glWidth;
				ctrlFillEx.size.lines = 0x800;
			} else {
				ctrlFillEx.size.glWidth = ctArg2;
				ctrlFillEx.size.width = ctrlFillEx.size.glWidth;
				ctrlFillEx.size.lines = ctArg3;
			}
			ctrlFillEx.fillAddr = CtImXch_D_CT_XCH_SRC_TOP_ADDR;
			// Sync
			ret = im_xch_fill_ex_sync( &ctrlFillEx );
			Ddim_Print(( "im_xch_fill_ex_sync() ret = 0x%X\n", ret ));
			Ddim_Print(("src area clear\n"));
		}
		// dst area init
		else if( ctArg1 == 36 ) {
			ImXchFillEx ctrlFillEx;
			kuint32 ctArg2;
			kuint32 ctArg3;
			kint32 dat;

			dat = atoi((const kchar *)argv[2]);
			ctArg2 = atoi((const kchar *)argv[3]);
			ctArg3 = atoi((const kchar *)argv[4]);

			ctrlFillEx.xch = ImXch_E_IM_XCH_CH_SEL_0;

			// Set fill data
			if( dat == 0 ) {
				ctrlFillEx.fillData = 0x00;
			} else {
				ctrlFillEx.fillData = (UCHAR)dat;
			}

			if( ctArg2 == 0 ) {
				ctrlFillEx.size.glWidth = 0x4000;
				ctrlFillEx.size.width = ctrlFillEx.size.glWidth;
				ctrlFillEx.size.lines = 0x800;
			} else {
				ctrlFillEx.size.glWidth = ctArg2;
				ctrlFillEx.size.width = ctrlFillEx.size.glWidth;
				ctrlFillEx.size.lines = ctArg3;
			}
			ctrlFillEx.fillAddr = CtImXch_D_CT_XCH_DST_TOP_ADDR;
			// Sync
			ret = im_xch_fill_ex_sync( &ctrlFillEx );
			Ddim_Print(( "im_xch_fill_ex_sync() ret = 0x%X\n", ret ));
			Ddim_Print(("dst area clear\n"));
		}
		// Initialize register for PC debug
		else if( ctArg1 == 37 ) {
#ifdef CO_DEBUG_ON_PC
			ioXch.XCHCTL0.XDTYPE.bit.XSDTYPE = 1;
			ioXch.XCHCTL0.XDTYPE.bit.XDDTYPE = 1;
			ioXch.XCHCTL0.XMD.bit.XMD = 7;
			ioXch.XCHCTL0.XGHW.bit.XGHW = 0xFFF0;
			ioXch.XCHCTL0.XDHW.bit.XDHW = 0x7FFF;
			ioXch.XCHCTL0.XDVW.bit.XDVW = 0x3FFF;
			ioXch.XCHCTL0.XCYC.bit.XHCYC = 0x1F;
			ioXch.XCHCTL0.XCYC.bit.XVCYC = 0x1F;
			ioXch.XCHCTL0.XHEN.bit.XHEN = 0xFFFFFFFF;
			ioXch.XCHCTL0.XVEN.bit.XVEN = 0xFFFFFFFF;
			ioXch.XCHCTL0.XSHW.bit.XSHW = 0xFFF0;
			ioXch.XCHCTL0.XSA.bit.XSA = 0xFFFFFFFF;
			ioXch.XCHCTL0.XDA.bit.XDA = 0xFFFFFFFF;
			ioXch.XCHCTL0.XFDT.bit.XFDT = 0xFF;
			ioXch.XHISTG0.bit.XHCNT0 = 0x1;

			ioXch.XCHCTL1.XDTYPE.bit.XSDTYPE = 0;
			ioXch.XCHCTL1.XDTYPE.bit.XDDTYPE = 0;
			ioXch.XCHCTL1.XMD.bit.XMD = 0;
			ioXch.XCHCTL1.XGHW.bit.XGHW = 0x0;
			ioXch.XCHCTL1.XDHW.bit.XDHW = 0x0;
			ioXch.XCHCTL1.XDVW.bit.XDVW = 0x0;
			ioXch.XCHCTL1.XCYC.bit.XHCYC = 0x0;
			ioXch.XCHCTL1.XCYC.bit.XVCYC = 0x0;
			ioXch.XCHCTL1.XHEN.bit.XHEN = 0x1;
			ioXch.XCHCTL1.XVEN.bit.XVEN = 0x1;
			ioXch.XCHCTL1.XSHW.bit.XSHW = 0x0;
			ioXch.XCHCTL1.XSA.bit.XSA = 0x0;
			ioXch.XCHCTL1.XDA.bit.XDA = 0x0;
			ioXch.XCHCTL1.XFDT.bit.XFDT = 0x0;
#endif
		}
		// im_xch_fill
		else if( ctArg1 == 38 ) {
			kuint32 fillData;
			kuint32 glWidth;
			kuint32 width;
			kuint32 lines;
			kuint32 dstAddr;

			glWidth = atoi((const kchar *)argv[3]);
			width = atoi((const kchar *)argv[4]);
			lines = atoi((const kchar *)argv[5]);
			fillData = atoi((const kchar *)argv[6]);
			dstAddr = strtoul((const kchar *)argv[7], NULL, 0);

			ret = im_xch_fill( xch, fillData, glWidth, dstAddr, width, lines );		/* pgr0539 */
			Ddim_Print(( "im_xch_fill() ret = 0x%X\n", ret ));
		}
		// Error
		else {
			Ddim_Print(("input parameter error\n"));
		}
	}

#ifdef D_IM_XCH_PRINT_ST
	Im_Xch_Print_ClockStatus();
#endif
	Ddim_Print(("xch command complete\n"));

	ddim_user_custom_l1l2cache_clean_flush_all();
	return;
}

CtImXch *ct_im_xch_get(void)
{
	static CtImXch *self = NULL;
	if ( !self )
	{
		self = k_object_new_with_private(CT_TYPE_IM_XCH, sizeof(CtImXchPrivate));
	}
	return self;
}
