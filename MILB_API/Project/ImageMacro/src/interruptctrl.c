/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :王睿
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "interruptctrl.h"
#include "interruptdefine.h"
#include "interruptfactor.h"

#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"
K_TYPE_DEFINE_WITH_PRIVATE(InterruptCtrl, interrupt_ctrl);
#define INTERRUPT_CTRL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptCtrlPrivate, INTERRUPT_TYPE_CTRL))

struct _InterruptCtrlPrivate
{
	int a;
};


static void interrupt_ctrl_constructor(InterruptCtrl *self)
{
	InterruptCtrlPrivate *priv = INTERRUPT_CTRL_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_ctrl_destructor(InterruptCtrl *self)
{
	InterruptCtrlPrivate *priv = INTERRUPT_CTRL_GET_PRIVATE(self);
	priv->a=0;
}

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static	volatile	TimproCallbackInfo	S_GIM_PRO_LDIV_CALLBACK_FUNC[D_IM_PRO_SEN_LDIV_CH_NUM]								= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_OBD_CALLBACK_FUNC[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBD_CH_NUM]						= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_OBT_CALLBACK_FUNC[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBT_CH_NUM]						= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SRO_VD_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM]										= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SRO_HD_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM]										= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_B2B_VD_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM]										= {{0}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_B2B_HD_CALLBACK_FUNC[D_IM_PRO_PIPE_NUM]										= {{0}};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_LDIV_INT[1] = {
	{ D_IM_PRO_LDIVINTFLG_LDIVEF,	D_IM_PRO_LDIVINTENB_LDIVEE,	D_IM_PRO_LDIVINTFLG_LDIVEF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_OBD_INT[1] = {
	{ D_IM_PRO_OBDINTFLG_OBDF,	D_IM_PRO_OBDINTENB_OBDE,		D_IM_PRO_OBDINTFLG_OBDF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_OBT_INT[1] = {
	{ D_IM_PRO_OBTINTFLG_OBTF,	D_IM_PRO_OBTINTENB_OBTE,		D_IM_PRO_OBTINTFLG_OBTF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SRO_VD[2] = {
	{ D_IM_PRO_SROTOP_INT_VDF0,	D_IM_PRO_SROTOP_INT_VDE0,		D_IM_PRO_SROTOP_INT_VDF0 },
	{ D_IM_PRO_SROTOP_INT_VDF1,	D_IM_PRO_SROTOP_INT_VDE1,		D_IM_PRO_SROTOP_INT_VDF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SRO_HD[2] = {
	{ D_IM_PRO_SROTOP_INT_HDF0,	D_IM_PRO_SROTOP_INT_HDE0,		D_IM_PRO_SROTOP_INT_HDF0 },
	{ D_IM_PRO_SROTOP_INT_HDF1,	D_IM_PRO_SROTOP_INT_HDE1,		D_IM_PRO_SROTOP_INT_HDF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_B2B_VD[2] = {
	{ D_IM_PRO_B2BTOP_INT_VDF0,	D_IM_PRO_B2BTOP_INT_VDE0,		D_IM_PRO_B2BTOP_INT_VDF0 },
	{ D_IM_PRO_B2BTOP_INT_VDF1,	D_IM_PRO_B2BTOP_INT_VDE1,		D_IM_PRO_B2BTOP_INT_VDF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_B2B_HD[2] = {
	{ D_IM_PRO_B2BTOP_INT_HDF0,	D_IM_PRO_B2BTOP_INT_HDE0,		D_IM_PRO_B2BTOP_INT_HDF0 },
	{ D_IM_PRO_B2BTOP_INT_HDF1,	D_IM_PRO_B2BTOP_INT_HDE1,		D_IM_PRO_B2BTOP_INT_HDF1 },
};

/*----------------------------------------------------------------------*/
/* DECLS                           											   */
/*----------------------------------------------------------------------*/
static VOID imProSenIntHandlerPrint( UCHAR status );
static VOID imProSroVdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProSroVdProc( E_IM_PRO_UNIT_NUM unitNo );
static VOID imProSroHdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProSroHdProc( E_IM_PRO_UNIT_NUM unitNo );
static VOID imProB2bVdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProB2bVdProc( E_IM_PRO_UNIT_NUM unitNo );
static VOID imProB2bHdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status );
static VOID imProB2bHdProc( E_IM_PRO_UNIT_NUM unitNo );

/*----------------------------------------------------------------------*/
/* IMPL														                   */
/*----------------------------------------------------------------------*/
static VOID imProSenIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	for(UCHAR i = 0; i < D_IM_PRO_SEN_LDIV_CH_NUM; i++) {
		Ddim_Print(( "imProSenIntHandlerPrint() LDIV LDIVINTFLG(0x%08x) LDIVINTENB(0x%08x) (status:%u)\n", IO_PRO.SEN.LDIV[i].LDIVINTFLG.word, IO_PRO.SEN.LDIV[i].LDIVINTENB.word, status ));
	}

	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_SENTOP_BLOB_NUM; loopcnt++ ) {
		for( UCHAR loopcnt_ch = 0; loopcnt_ch < D_IM_PRO_SEN_OBD_CH_NUM; loopcnt_ch++ ) {
			Ddim_Print(( "imProSenIntHandlerPrint() OBD[%u][%u] OBDINTFLG(0x%08x) OBDINTENB(0x%08x) (status:%u)\n", loopcnt, loopcnt_ch, IO_PRO.SEN.OBD[loopcnt][loopcnt_ch].OBDINTFLG.word, IO_PRO.SEN.OBD[loopcnt][loopcnt_ch].OBDINTENB.word, status ));
		}

		for( UCHAR loopcnt_ch = 0; loopcnt_ch < D_IM_PRO_SEN_OBT_CH_NUM; loopcnt_ch++ ) {
			Ddim_Print(( "imProSenIntHandlerPrint() OBT[%u][%u] OBTINTFLG(0x%08x) OBTINTENB(0x%08x) (status:%u)\n", loopcnt, loopcnt_ch, IO_PRO.SEN.OBT[loopcnt][loopcnt_ch].OBTINTFLG.word, IO_PRO.SEN.OBT[loopcnt][loopcnt_ch].OBTINTENB.word, status ));
		}
	}

	for(UCHAR i = 0; i < D_IM_PRO_SRO_PWCH_CH_NUM; i++) {
		Ddim_Print(( "imProSenIntHandlerPrint() PWCH%u PWCHINTFLG(0x%08x) PWCHINTENB(0x%08x) (status:%u)\n", i, IO_PRO.SEN.PWCH[i].PWCHINTFLG.word, IO_PRO.SEN.PWCH[i].PWCHINTENB.word, status ));
	}
#endif
}

static VOID imProSroVdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProSroVdProcPrint(%u) VD VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", unitNo, IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word, status ));
#endif
}

static VOID imProSroVdProc( E_IM_PRO_UNIT_NUM unitNo )
{
	UINT32			loopcnt;
	ULONG			vdIntf = 0;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	Im_Pro_Dsb();
	imProSroVdProcPrint( unitNo, 0 );

	// Get interrupt flag
	vdIntf	= IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word & IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word & D_IM_PRO_SROTOP_INT_VD_ALL;

	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word	= vdIntf;

	Im_Pro_Dsb();
	imProSroVdProcPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	/***********/
	/* VD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SRO_VD) / sizeof(S_GIM_PRO_INTTBL_SRO_VD[0])); loopcnt++ ) {
		if( (vdIntf & S_GIM_PRO_INTTBL_SRO_VD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SRO_VD[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_SRO_VD_CALLBACK_FUNC[unitNo].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SRO,
		cbId.channel		= 0,
		S_GIM_PRO_SRO_VD_CALLBACK_FUNC[unitNo].pCallback( &cbId, callbackResult, S_GIM_PRO_SRO_VD_CALLBACK_FUNC[unitNo].userParam );
	}
}

static VOID imProSroHdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProSroHdProcPrint(%u) HD VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", unitNo, IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word, IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word, status ));
#endif
}

static VOID imProSroHdProc( E_IM_PRO_UNIT_NUM unitNo )
{
	UINT32			loopcnt;
	ULONG			vdIntf;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	Im_Pro_Dsb();
	imProSroHdProcPrint( unitNo, 0 );

	// Get interrupt flag
	vdIntf	= IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word & IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTENB.word & D_IM_PRO_SROTOP_INT_HD_ALL;

	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].SRO.SROTOP.VHDINTFLG.word	= vdIntf;

	Im_Pro_Dsb();
	imProSroHdProcPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	/***********/
	/* HD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SRO_HD) / sizeof(S_GIM_PRO_INTTBL_SRO_HD[0])); loopcnt++ ) {
		if( (vdIntf & S_GIM_PRO_INTTBL_SRO_HD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SRO_HD[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_SRO_HD_CALLBACK_FUNC[unitNo].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SRO,
		cbId.channel		= 0,
		S_GIM_PRO_SRO_HD_CALLBACK_FUNC[unitNo].pCallback( &cbId, callbackResult, S_GIM_PRO_SRO_HD_CALLBACK_FUNC[unitNo].userParam );
	}
}

static VOID imProB2bVdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProB2bVdProcPrint(%u) VD VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", unitNo, IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word, IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word, status ));
#endif
}

static VOID imProB2bVdProc( E_IM_PRO_UNIT_NUM unitNo )
{
	UINT32			loopcnt;
	ULONG			vdIntf;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
	Im_Pro_Dsb();
	imProB2bVdProcPrint( unitNo, 0 );

	// Get interrupt flag
	vdIntf	= IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word & IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word & D_IM_PRO_B2BTOP_INT_VD_ALL;

	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word	= vdIntf;

	Im_Pro_Dsb();
	imProB2bVdProcPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );

	/***********/
	/* VD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_B2B_VD) / sizeof(S_GIM_PRO_INTTBL_B2B_VD[0])); loopcnt++ ) {
		if( (vdIntf & S_GIM_PRO_INTTBL_B2B_VD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_B2B_VD[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_B2B_VD_CALLBACK_FUNC[unitNo].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_B2B,
		cbId.channel		= 0,
		S_GIM_PRO_B2B_VD_CALLBACK_FUNC[unitNo].pCallback( &cbId, callbackResult, S_GIM_PRO_B2B_VD_CALLBACK_FUNC[unitNo].userParam );
	}
}

static VOID imProB2bHdProcPrint( E_IM_PRO_UNIT_NUM unitNo, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProB2bHdProcPrint(%u) VD VHDINTFLG(0x%08x) VHDINTENB(0x%08x) (status:%u)\n", unitNo, IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word, IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word, status ));
#endif
}

static VOID imProB2bHdProc( E_IM_PRO_UNIT_NUM unitNo )
{
	UINT32			loopcnt;
	ULONG			vdIntf;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProB2bHdProc %u begin\n", unitNo ));
#endif
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );
	Im_Pro_Dsb();
	imProB2bHdProcPrint( unitNo, 0 );

	// Get interrupt flag
	vdIntf	= IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word & IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTENB.word & D_IM_PRO_B2BTOP_INT_HD_ALL;

	// Clear interrupt flag
	IO_PRO.IMG_PIPE[unitNo].B2B.B2BTOP.VHDINTFLG.word	= vdIntf;

	Im_Pro_Dsb();
	imProB2bHdProcPrint( unitNo, 1 );
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_B2B );

	/***********/
	/* VD Edge */
	/***********/
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_B2B_HD) / sizeof(S_GIM_PRO_INTTBL_B2B_HD[0])); loopcnt++ ) {
		if( (vdIntf & S_GIM_PRO_INTTBL_B2B_HD[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_B2B_HD[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_B2B_HD_CALLBACK_FUNC[unitNo].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= unitNo,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_B2B,
		cbId.channel		= 0,
		S_GIM_PRO_B2B_HD_CALLBACK_FUNC[unitNo].pCallback( &cbId, callbackResult, S_GIM_PRO_B2B_HD_CALLBACK_FUNC[unitNo].userParam );
	}
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProB2bHdProc %u end\n", unit_no ));
#endif
}

/*----------------------------------------------------------------------*/
/*PUBLIC   																       */
/*----------------------------------------------------------------------*/
/**
SEN block Int handler except VD, HD, and Sensor I/F interrupts.
*/
VOID interrupt_ctrl_sen_int_handler( VOID )
{
	UINT32					loopcnt = 0;
	UINT32					loopcntCh = 0;
	UINT32					loopcntBlock = 0;
	ULONG					ldivIntf[D_IM_PRO_SEN_LDIV_NUM] = {0};
	ULONG					obdIntf[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBD_CH_NUM] = {{0}};
	ULONG					obtIntf[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBT_CH_NUM] = {{0}};
	ULONG					pwchIntf[E_IM_PRO_PWCH_MAX] = {0};
	TimproPwchIntInfo	pwchInfo = {0};
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_sen_int_handler begin\n" ));
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	Im_Pro_Dsb();
	imProSenIntHandlerPrint( 0 );

	/***********/
	/* PWCH    */
	/***********/
	// Get & clear interrupt flag
	pwchInfo.unitNo		= E_IM_PRO_UNIT_NUM_1;
	pwchInfo.blockType	= E_IM_PRO_BLOCK_TYPE_SEN;
	pwchInfo.regPtr		= IO_PRO.SEN.PWCH;
	interrupt_factor_pwch_clear_int_factor( interrupt_factor_new(),&pwchInfo, pwchIntf, E_IM_PRO_PWCH_MAX );

	/***********/
	/* LDIV    */
	/***********/
	// Get & clear interrupt flag
	for( loopcnt = 0; loopcnt < D_IM_PRO_SEN_LDIV_NUM; loopcnt++ ) {
		ldivIntf[loopcnt]	= IO_PRO.SEN.LDIV[loopcnt].LDIVINTFLG.word & IO_PRO.SEN.LDIV[loopcnt].LDIVINTENB.word;
		IO_PRO.SEN.LDIV[loopcnt].LDIVINTFLG.word = ldivIntf[loopcnt];
	}

	/***********/
	/* OBD/OBT */
	/***********/
	// Get & clear interrupt flag
	for( loopcnt = 0; loopcnt < D_IM_PRO_SENTOP_BLOB_NUM; loopcnt++ ) {
		for( loopcntCh = 0; loopcntCh < D_IM_PRO_SEN_OBD_CH_NUM; loopcntCh++ ) {
			obdIntf[loopcnt][loopcntCh]	= IO_PRO.SEN.OBD[loopcnt][loopcntCh].OBDINTFLG.word & IO_PRO.SEN.OBD[loopcnt][loopcntCh].OBDINTENB.word;
			IO_PRO.SEN.OBD[loopcnt][loopcntCh].OBDINTFLG.word = obdIntf[loopcnt][loopcntCh];

			if( ( obdIntf[loopcnt][loopcntCh] & D_IM_PRO_OBDINTFLG_OBDF ) != 0 ) {
				im_pro_comm_update_obd_result( loopcnt, loopcntCh );
			}
		}

		for( loopcntCh = 0; loopcntCh < D_IM_PRO_SEN_OBT_CH_NUM; loopcntCh++ ) {
			obtIntf[loopcnt][loopcntCh]	= IO_PRO.SEN.OBT[loopcnt][loopcntCh].OBTINTFLG.word & IO_PRO.SEN.OBT[loopcnt][loopcntCh].OBTINTENB.word;
			IO_PRO.SEN.OBT[loopcnt][loopcntCh].OBTINTFLG.word = obtIntf[loopcnt][loopcntCh];

			if( ( obtIntf[loopcnt][loopcntCh] & D_IM_PRO_OBTINTFLG_OBTF ) != 0 ) {
				im_pro_comm_update_obt_result( loopcnt, loopcntCh );
			}
		}
	}

	Im_Pro_Dsb();
	imProSenIntHandlerPrint( 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_sen_int_handler Int factor PWCH[0]=0x%lx PWCH[1]=0x%lx PWCH[2]=0x%lx PWCH[3]=0x%lx PWCH[4]=0x%lx PWCH[5]=0x%lx PWCH[6]=0x%lx PWCH[7]=0x%lx\n", pwchIntf[0], pwchIntf[1], pwchIntf[2], pwchIntf[3], pwchIntf[4], pwchIntf[5], pwchIntf[6], pwchIntf[7] ));
	Ddim_Print(( "interrupt_ctrl_sen_int_handler Int factor LDIV[0]=0x%lx LDIV[1]=0x%lx LDIV[2]=0x%lx LDIV[3]=0x%lx \n", ldivIntf[0], ldivIntf[1], ldivIntf[2], ldivIntf[3] ));
	Ddim_Print(( "interrupt_ctrl_sen_int_handler Int factor OBD[0][0]=0x%lx OBD[0][1]=0x%lx OBD[1][0]=0x%lx OBD[1][1]=0x%lx OBD[2][0]=0x%lx OBD[2][1]=0x%lx OBD[3][0]=0x%lx OBD[3][1]=0x%lx\n", obdIntf[0][0], obdIntf[0][1], obdIntf[1][0], obdIntf[1][1], obdIntf[2][0], obdIntf[2][1], obdIntf[3][0], obdIntf[3][1] ));
	Ddim_Print(( "interrupt_ctrl_sen_int_handler Int factor OBT[0][0]=0x%lx OBT[0][1]=0x%lx OBT[1][0]=0x%lx OBT[1][1]=0x%lx OBT[2][0]=0x%lx OBT[2][1]=0x%lx OBT[3][0]=0x%lx OBT[3][1]=0x%lx\n", obtIntf[0][0], obtIntf[0][1], obtIntf[1][0], obtIntf[1][1], obtIntf[2][0], obtIntf[2][1], obtIntf[3][0], obtIntf[3][1] ));
#endif
	/***********/
	/* PWCH    */
	/***********/
	for( loopcntCh = 0; loopcntCh < E_IM_PRO_PWCH_MAX; loopcntCh++ ) {
		interrupt_factor_pwch_callback_int_factor( interrupt_factor_new(),0, E_IM_PRO_BLOCK_TYPE_SEN, (E_IM_PRO_PWCH)loopcntCh, pwchIntf );
	}
	Im_Pro_Dsb();

	/***********/
	/* LDIV    */
	/***********/
	for( loopcntCh = 0; loopcntCh < D_IM_PRO_SEN_LDIV_NUM; loopcntCh++ ) {
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_LDIV_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_LDIV_INT[0])); loopcnt++ ) {
			if( (ldivIntf[loopcntCh] & S_GIM_PRO_INTTBL_SEN_LDIV_INT[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SEN_LDIV_INT[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_LDIV_CALLBACK_FUNC[loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= E_IM_PRO_UNIT_NUM_1;
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN;
			cbId.channel		= loopcntCh;
			S_GIM_PRO_LDIV_CALLBACK_FUNC[loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_LDIV_CALLBACK_FUNC[loopcntCh].userParam );
		}
	}
	Im_Pro_Dsb();

	/***********/
	/* OBD     */
	/***********/
	for( loopcntBlock = 0; loopcntBlock < D_IM_PRO_SENTOP_BLOB_NUM; loopcntBlock++ ) {
		for( loopcntCh = 0; loopcntCh < D_IM_PRO_SEN_OBD_CH_NUM; loopcntCh++ ) {
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_OBD_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_OBD_INT[0])); loopcnt++ ) {
				if( (obdIntf[loopcntBlock][loopcntCh] & S_GIM_PRO_INTTBL_SEN_OBD_INT[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_OBD_INT[loopcnt].intFact;
				}
			}
			// Callback
			if (( S_GIM_PRO_OBD_CALLBACK_FUNC[loopcntBlock][loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1;
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN;
				im_pro_comm_get_obd_ch(loopcntBlock, loopcntCh, (E_IM_PRO_OBD_CH*)&cbId.channel);
				S_GIM_PRO_OBD_CALLBACK_FUNC[loopcntBlock][loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_OBD_CALLBACK_FUNC[loopcntBlock][loopcntCh].userParam );
			}
		}
	}
	Im_Pro_Dsb();

	/***********/
	/* OBT     */
	/***********/
	for( loopcntBlock = 0; loopcntBlock < D_IM_PRO_SENTOP_BLOB_NUM; loopcntBlock++ ) {
		for( loopcntCh = 0; loopcntCh < D_IM_PRO_SEN_OBT_CH_NUM; loopcntCh++ ) {
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_OBT_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_OBT_INT[0])); loopcnt++ ) {
				if( (obtIntf[loopcntBlock][loopcntCh] & S_GIM_PRO_INTTBL_SEN_OBT_INT[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_OBT_INT[loopcnt].intFact;
				}
			}
			// Callback
			if (( S_GIM_PRO_OBT_CALLBACK_FUNC[loopcntBlock][loopcntCh].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1;
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN;
				im_pro_comm_get_obt_ch(loopcntBlock, loopcntCh, (E_IM_PRO_OBT_CH*)&cbId.channel);
				S_GIM_PRO_OBT_CALLBACK_FUNC[loopcntBlock][loopcntCh].pCallback( &cbId, callbackResult, S_GIM_PRO_OBT_CALLBACK_FUNC[loopcntBlock][loopcntCh].userParam );
			}
		}
	}
	Im_Pro_Dsb();
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_sen_int_handler end\n" ));
#endif
}


/**
CallBackFunction which Call to the interruption timing of LDIV is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : LDIV Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_ldiv_set_int_handler( InterruptCtrl*self,E_IM_PRO_LDIV_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_LDIV_CALLBACK_FUNC[ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_LDIV_CALLBACK_FUNC[ch].userParam = callbackCfg->user_param;

	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of OB is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : OBD Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_obd_set_int_handler( InterruptCtrl*self,E_IM_PRO_OBD_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	S_GIM_PRO_OBD_CALLBACK_FUNC[blockNum][chNum].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_OBD_CALLBACK_FUNC[blockNum][chNum].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}


/**
CallBackFunction which Call to the interruption timing of OBT is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : OBT Interrupt callback function address
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_ctrl_obt_set_int_handler( InterruptCtrl*self,E_IM_PRO_OBT_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	S_GIM_PRO_OBT_CALLBACK_FUNC[blockNum][chNum].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_OBT_CALLBACK_FUNC[blockNum][chNum].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SRO pipe VD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_srotop_pipe_set_vd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
#ifdef CO_PARAM_CHECK
	if (unitNo >= E_IM_PRO_BOTH_UNIT){
		Ddim_Assertion(("I:interrupt_ctrl_srotop_pipe_set_vd_int_handler. unit no value error!! (unitNo:%d)\n", unitNo));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	S_GIM_PRO_SRO_VD_CALLBACK_FUNC[unitNo].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SRO_VD_CALLBACK_FUNC[unitNo].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SRO Macro Pipe1 VD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe1_vd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe1_vd_int_handler begin\n" ));
#endif
	imProSroVdProc( E_IM_PRO_UNIT_NUM_1 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe1_vd_int_handler end\n" ));
#endif
}

/**
SRO Macro Pipe2 VD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe2_vd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe2_vd_int_handler begin\n" ));
#endif
	imProSroVdProc( E_IM_PRO_UNIT_NUM_2 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe2_vd_int_handler end\n" ));
#endif
}

/**
SRO pipe HD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_srotop_pipe_set_hd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
#ifdef CO_PARAM_CHECK
	if (unitNo >= E_IM_PRO_BOTH_UNIT){
		Ddim_Assertion(("I:interrupt_ctrl_srotop_pipe_set_hd_int_handler. unit no value error!! (unitNo:%d)\n", unitNo));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	S_GIM_PRO_SRO_HD_CALLBACK_FUNC[unitNo].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SRO_HD_CALLBACK_FUNC[unitNo].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SRO Macro Pipe1 HD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe1_hd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe1_hd_int_handler begin\n" ));
#endif
	imProSroHdProc( E_IM_PRO_UNIT_NUM_1 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe1_hd_int_handler end\n" ));
#endif
}

/**
SRO Macro Pipe2 HD Int handler.
*/
VOID interrupt_ctrl_srotop_pipe2_hd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe2_hd_int_handler begin\n" ));
#endif
	imProSroHdProc( E_IM_PRO_UNIT_NUM_2 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_srotop_pipe2_hd_int_handler end\n" ));
#endif
}

/**
B2B pipe VD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_b2btop_pipe_set_vd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
#ifdef CO_PARAM_CHECK
	if (unitNo >= E_IM_PRO_BOTH_UNIT){
		Ddim_Assertion(("I:interrupt_ctrl_b2btop_pipe_set_vd_int_handler. unit no value error!! (unitNo:%d)\n", unitNo));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	S_GIM_PRO_B2B_VD_CALLBACK_FUNC[unitNo].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_B2B_VD_CALLBACK_FUNC[unitNo].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
B2B Macro Pipe1 VD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe1_vd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe1_vd_int_handler begin\n" ));
#endif
	imProB2bVdProc( E_IM_PRO_UNIT_NUM_1 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe1_vd_int_handler end\n" ));
#endif
}

/**
B2B Macro Pipe2 VD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe2_vd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe2_vd_int_handler begin\n" ));
#endif
	imProB2bVdProc( E_IM_PRO_UNIT_NUM_2 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe2_vd_int_handler end\n" ));
#endif
}

/**
B2B pipe HD Int handler setting.
@param[in]	unitNo : Unit number.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					:setting ok
@retval		D_IM_PRO_PARAM_ERROR		:setting ng
*/
INT32 interrupt_ctrl_b2btop_pipe_set_hd_int_handler( InterruptCtrl*self,E_IM_PRO_UNIT_NUM unitNo, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
#ifdef CO_PARAM_CHECK
	if (unitNo >= E_IM_PRO_BOTH_UNIT){
		Ddim_Assertion(("I:interrupt_ctrl_b2btop_pipe_set_hd_int_handler. unit no value error!! (unitNo:%d)\n", unitNo));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	S_GIM_PRO_B2B_HD_CALLBACK_FUNC[unitNo].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_B2B_HD_CALLBACK_FUNC[unitNo].userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
B2B Macro Pipe1 HD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe1_hd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe1_hd_int_handler begin\n" ));
#endif
	imProB2bHdProc( E_IM_PRO_UNIT_NUM_1 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe1_hd_int_handler end\n" ));
#endif
}

/**
B2B Macro Pipe2 HD Int handler.
*/
VOID interrupt_ctrl_b2btop_pipe2_hd_int_handler( VOID )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe2_hd_int_handler begin\n" ));
#endif
	imProB2bHdProc( E_IM_PRO_UNIT_NUM_2 );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_ctrl_b2btop_pipe2_hd_int_handler end\n" ));
#endif
}

InterruptCtrl *interrupt_ctrl_new(void)
{
	InterruptCtrl* self = k_object_new_with_private(INTERRUPT_TYPE_CTRL,sizeof(InterruptCtrlPrivate));
	return self;
}
