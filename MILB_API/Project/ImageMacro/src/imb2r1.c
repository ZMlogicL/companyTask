/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsb2r.h"
//#include "imrdma.h"
#include"imb2r.h"
#include "imb2r1.h"
#include"imb2r2.h"
#include"imb2r3.h"
#include "imb2r4.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImB2r1, im_b2r1);
#define IM_B2R1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImB2r1Private, IM_TYPE_B2R1))

/*----------------------------------------------------------------------*/
/* Structure  															*/
/*----------------------------------------------------------------------*/
struct _ImB2r1Private
{
	int a;
};

// Output address management information
typedef struct {
	T_IM_B2R_OUTBANK_INFO	bankInfo;		// Output bank information
	UCHAR					latestIdx;		// Latest Output bank index.
	T_IM_B2R_OUTADDR_INFO	latestAddr;	// Latest Output address.
} TImB2rOutputMng;

// Interrupt parameter table
typedef struct {
	ULONG				flgBitmask;		// Bitmask of interrupt flag.
	ULONG				enaBitmask;		// Bitmask of inaerrupt enable.
	ULONG				waitflg;			// Value of set_flg.
	ULONG				intStatus;			// Value of gIM_B2R_State.intStatus.
	ULONG				busyState;			// Value of gIM_B2R_State.busyState.
} TImB2rIntflgTbl;

typedef struct {
	USHORT	ofsXPixs;
	USHORT	ofsYPixs;
	ULONG	ofsBytes;
} TImB2rYbraOfsInfo;

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
static const TImB2rIntflgTbl S_G_IM_B2R_INTTBL_FB2R[ImB2r1_D_IM_B2R_PIPE_COUNT] = {
	{ 0x00000001, 0x00000001, D_IM_B2R1_INT_FLG_CPERR_ERR, D_IM_B2R1_INT_STATE_CPERR_ERR, 0 },	// CPERE
	{ 0x00000001, 0x00000001, D_IM_B2R2_INT_FLG_CPERR_ERR, D_IM_B2R2_INT_STATE_CPERR_ERR, 0 },	// CPERE
};
// YBRA offset information
static volatile TImB2rYbraOfsInfo S_G_IM_B2R_YBRA_OFS_INFO[ImB2r1_D_IM_B2R_PIPE_COUNT];

// rectangle parameter
static volatile T_IM_B2R_RECT S_G_IM_B2R_RECT_PARAM[ImB2r1_D_IM_B2R_PIPE_COUNT];

//
// Interrupt parameter table
//
static const TImB2rIntflgTbl S_G_IM_B2R_INTTBL_JDSB2R[ImB2r1_D_IM_B2R_PIPE_COUNT][8] = {
	{
		{ 0x00000001, 0x00000001, D_IM_B2R1_INT_FLG_YBR_END,  D_IM_B2R1_INT_STATE_YBR_END,  ImB2r1_D_IM_B2R_STATE_BUSY_YBR },	// YBREE
		{ 0x00000002, 0x00000002, D_IM_B2R1_INT_FLG_YBW_END,  D_IM_B2R1_INT_STATE_YBW_END,  ImB2r1_D_IM_B2R_STATE_BUSY_YBW },	// YBWEE
		{ 0x00000010, 0x00000010, D_IM_B2R1_INT_FLG_FB2R_END, D_IM_B2R1_INT_STATE_FB2R_END, 0 },						// FB2REE
		{ 0x00000020, 0x00000020, D_IM_B2R1_INT_FLG_LINE_END, D_IM_B2R1_INT_STATE_LINE_END, 0 },						// ELNEE
		{ 0x00000100, 0x00000100, D_IM_B2R1_INT_FLG_YBR_ERR,  D_IM_B2R1_INT_STATE_YBR_ERR,  ImB2r1_D_IM_B2R_STATE_BUSY_YBR },	// YBRERE
		{ 0x00000200, 0x00000200, D_IM_B2R1_INT_FLG_YBW_ERR,  D_IM_B2R1_INT_STATE_YBW_ERR,  ImB2r1_D_IM_B2R_STATE_BUSY_YBW },	// YBWERE
		{ 0x00001000, 0x00001000, D_IM_B2R1_INT_FLG_AXR_ERR,  D_IM_B2R1_INT_STATE_AXR_ERR,  0 },						// AXRERE
		{ 0x00002000, 0x00002000, D_IM_B2R1_INT_FLG_AXW_ERR,  D_IM_B2R1_INT_STATE_AXW_ERR,  0 },						// AXWERE
	},
	{
		{ 0x00000001, 0x00000001, D_IM_B2R2_INT_FLG_YBR_END,  D_IM_B2R2_INT_STATE_YBR_END,  ImB2r1_D_IM_B2R_STATE_BUSY_YBR },	// YBREE
		{ 0x00000002, 0x00000002, D_IM_B2R2_INT_FLG_YBW_END,  D_IM_B2R2_INT_STATE_YBW_END,  ImB2r1_D_IM_B2R_STATE_BUSY_YBW },	// YBWEE
		{ 0x00000010, 0x00000010, D_IM_B2R2_INT_FLG_FB2R_END, D_IM_B2R2_INT_STATE_FB2R_END, 0 },						// FB2REE
		{ 0x00000020, 0x00000020, D_IM_B2R2_INT_FLG_LINE_END, D_IM_B2R2_INT_STATE_LINE_END, 0 },						// ELNEE
		{ 0x00000100, 0x00000100, D_IM_B2R2_INT_FLG_YBR_ERR,  D_IM_B2R2_INT_STATE_YBR_ERR,  ImB2r1_D_IM_B2R_STATE_BUSY_YBR },	// YBRERE
		{ 0x00000200, 0x00000200, D_IM_B2R2_INT_FLG_YBW_ERR,  D_IM_B2R2_INT_STATE_YBW_ERR,  ImB2r1_D_IM_B2R_STATE_BUSY_YBW },	// YBWERE
		{ 0x00001000, 0x00001000, D_IM_B2R2_INT_FLG_AXR_ERR,  D_IM_B2R2_INT_STATE_AXR_ERR,  0 },						// AXRERE
		{ 0x00002000, 0x00002000, D_IM_B2R2_INT_FLG_AXW_ERR,  D_IM_B2R2_INT_STATE_AXW_ERR,  0 },						// AXWERE
	},
};

// Output parameter
static volatile TImB2rOutputMng S_G_IM_B2R_OUT_MNG[ImB2r1_D_IM_B2R_PIPE_COUNT];
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
static VOID imB2rReset( UCHAR pipe_no );
static VOID imB2rManagerInit( UCHAR pipe_no );
static VOID imB2rSetYbrAddressSdramInput( UCHAR pipe_no );
static VOID imB2rLatestAddrUpdate( UCHAR pipe_no );
static VOID imB2rCalcRingPixs( UCHAR pipe_no );

static VOID imB2rSetTopColorB2bDirect( UCHAR pipe_no );
static VOID imB2rCalcTopMsbOffsetSdramInput( UCHAR pipe_no );

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

static void im_b2r1_constructor(ImB2r1 *self)
{
	//ImB2r1Private *priv = IM_B2R1_GET_PRIVATE(self);
}

static void im_b2r1_destructor(ImB2r1 *self)
{
	//ImB2r1Private *priv = IM_B2R1_GET_PRIVATE(self);
}

//---------------------- driver  section -------------------------------
/* B2R reset sequence
 */
static VOID imB2rReset( UCHAR pipe_no )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rReset error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );
	Im_B2R_On_Hclk( pipe_no );
	Im_B2R_On_Iclk( pipe_no );
	Im_B2R_On_Clk( pipe_no );	// TRG off control accompanies the B2R reset
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.CNTL.word = 0x0000;
	Im_B2R_Off_Clk( pipe_no );
	Im_B2R_Off_Iclk( pipe_no );
	Im_B2R_Off_Hclk( pipe_no );
	Im_B2R_Off_Pclk( pipe_no );
}

/* Reset internal value
 */
static VOID imB2rManagerInit( UCHAR pipe_no )
{
	UCHAR size_coef = 1;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rManagerInit error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( pipe_no == D_IM_B2R_PIPE12 ){
		size_coef = 2;
		pipe_no = 0;
	}

	// Initialize of State & Handler management information
	memset( (USHORT*)&im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no), 0, sizeof(TImB2rStateMng) * size_coef );

	// Initialize of Address management information
	memset( (USHORT*)&S_G_IM_B2R_OUT_MNG[pipe_no], 0, sizeof(TImB2rOutputMng) * size_coef );

	// initialize of Rectangle information
	memset( (USHORT*)&S_G_IM_B2R_RECT_PARAM[pipe_no], 0, sizeof(T_IM_B2R_RECT) * size_coef );

	// Initialize of control information
	memset( (USHORT*)&S_G_IM_B2R_YBRA_OFS_INFO[pipe_no], 0, sizeof(TImB2rYbraOfsInfo) * size_coef );

	//因为变量共享，用函数来调用变量
	im_b2r_for_g_im_b2r_clk_ctrl_cnt_disable(pipe_no, size_coef);

	return;
}

/* Update of Address information */
static VOID imB2rLatestAddrUpdate( UCHAR pipe_no )
{
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rLatestAddrUpdate error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk(pipe_no);

	S_G_IM_B2R_OUT_MNG[pipe_no].latestIdx = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWBANK.bit.BANKSTS;
	S_G_IM_B2R_OUT_MNG[pipe_no].latestAddr = S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[ S_G_IM_B2R_OUT_MNG[pipe_no].latestIdx ];

	Im_B2R_Off_Pclk(pipe_no);
}

/* Calculate YBRA address after trimming.
 */
static VOID imB2rSetYbrAddressSdramInput( UCHAR pipe_no )
{
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rSetYbrAddressSdramInput error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk(pipe_no);

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRA.word = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inAddr + S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsBytes);

	Im_B2R_Off_Pclk(pipe_no);
}

#ifdef IM_B2R_STATUS_PRINT
// Calculate YBW output image width
static UINT32 im_b2r_calc_ybw_out_width( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;

	ImB2r2 *imB2r2=im_b2r2_get();

	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Print(( "im_b2r_calc_ybw_out_width:pipe_no err\n" ));
		return 0;
	}

	Im_B2R_On_Pclk(pipe_no);
	if( im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).videoPhotoMode == ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT ) {
		// Trimming is disable and photo mode.
		in_pixs = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRHSIZ.word;
		refPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs;
	}
	else {
		// Trimming is disable and movie mode.
		in_pixs = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINHSIZ.word;
		refPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs;
	}

	out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	Im_B2R_Off_Pclk(pipe_no);

	return out_pixs;
}

// Calculate YBW output image lines
static UINT32 im_b2r_calc_ybw_out_lines( UCHAR pipe_no )
{
	UINT32 in_pixs;
	UINT32 out_pixs;
	UINT32 refPixs;

	ImB2r2 *imB2r2=im_b2r2_get();

	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Print(( "im_b2r_calc_ybw_out_lines:pipe_no err\n" ));
		return 0;
	}

	Im_B2R_On_Pclk(pipe_no);
	if( im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).videoPhotoMode == ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT ) {
		// Trimming is disable and photo mode.
		in_pixs = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRVSIZ.word;
		refPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs;
	}
	else {
		// Trimming is disable and movie mode.
		in_pixs = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.DINVSIZ.word;
		refPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).ringPixsInfo.refPixs;
	}

	out_pixs = ((in_pixs - refPixs) & 0x1FFE);
	Im_B2R_Off_Pclk(pipe_no);

	return out_pixs;
}
#endif

/* Calculate padding pixs and referenced pixs with filter mode
 */
static VOID imB2rCalcRingPixs( UCHAR pipe_no )
{
	ImB2r2 *imB2r2=im_b2r2_get();

	static const TImB2rRingPixs ring_pixs_info_tbl[2][2] = {	// CIABYP, CIAPDD
		{	// CIABYP=0
			{ D_IM_B2R_ENABLE_OFF, 3, 0, 6 },	// CIABYP=0, CIAPDD=0
			{ D_IM_B2R_ENABLE_ON,  3, 6, 0 },	// CIABYP=0, CIAPDD=1
		},
		{	// CIABYP=1
			{ D_IM_B2R_ENABLE_OFF, 0, 0, 0 },	// CIABYP=1, CIAPDD=0
			{ D_IM_B2R_ENABLE_ON,  0, 0, 0 },	// CIABYP=1, CIAPDD=1	NG Setting
		}
	};
	UCHAR loop_cnt, loop_sta, loop_end;

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rCalcRingPixs error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// Get current ring pixel information
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ringPixsInfo = ring_pixs_info_tbl[im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaBypass][im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaPadding];

#ifdef IM_B2R_DEBUG_PRINT
		Ddim_Print(( "imB2rCalcRingPixs(): en=%u ring=%u pad=%u ref=%u\n",
					im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ringPixsInfo.padEnable,
					im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ringPixsInfo.ringPixs,
					im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ringPixsInfo.padPixs,
					im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ringPixsInfo.refPixs ));
#endif
	}
}

/* Calculate bayer trimming bytes from bayer address set by Im_B2R_Set_InAddr_Info()
 */
static VOID im_b2r_calc_ybr_address_sdram_input( UCHAR pipe_no )
{
	ULONG tmp_top;
	ULONG tmp_left;

	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "im_b2r_calc_ybr_address_sdram_input error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsXPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_left;
	S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsYPixs = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_top;

	switch( im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputDtype ) {
		case D_IM_B2R_STL_DTYP_PACK12:
			tmp_top  = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputGlobal * S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsYPixs);
			tmp_left = (S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsXPixs * 3 / 2);	// x1.5
			break;
		case D_IM_B2R_STL_DTYP_PACK10:
			tmp_top  = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputGlobal * S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsYPixs);
			tmp_left = (S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsXPixs * 5 / 4);	// x1.25
			break;
		case D_IM_B2R_STL_DTYP_PACK16:
			tmp_top  = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputGlobal * S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsYPixs);
			tmp_left = (S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsXPixs * 2);		// x2.0
			break;
		default:// 8 bit PACK
			tmp_top  = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputGlobal * S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsYPixs);
			tmp_left = (S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsXPixs);			// x1.0
			break;
	}

	S_G_IM_B2R_YBRA_OFS_INFO[pipe_no].ofsBytes = (tmp_top + tmp_left);
}

/* Calculate top-left pixel MSB offset bit.
 */
static VOID imB2rCalcTopMsbOffsetSdramInput( UCHAR pipe_no )
{
	static const UCHAR msb_offset_pack12[ImB2r1_D_IM_B2R_PACK12_MSB_CYCLE_PIXS * 2] = {
		0, 4, 0, 4
	};
	static const UCHAR msb_offset_pack10[ImB2r1_D_IM_B2R_PACK10_MSB_CYCLE_PIXS * 2] = {
		0, 2, 4, 6, 0, 2, 4, 6
	};
	static const UCHAR msb_offset_to_pixs_pack10[8] = {	// from msb offset to msb_offset_pack10' s index number
		0, 0, 1, 0, 2, 0, 3, 0
	};
	static const UCHAR msb_offset_pack8_16[1] = {
		0
	};
	USHORT trim_left;
	USHORT msb_array_idx;
	USHORT cycle_pixs;
	UCHAR const* p_msb_offset;

	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rCalcTopMsbOffsetSdramInput error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );

	switch( im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputDtype ) {
		case D_IM_B2R_STL_DTYP_PACK8:	// FALL THROUGH
		case D_IM_B2R_STL_DTYP_PACK16:
			p_msb_offset = &msb_offset_pack8_16[0];
			cycle_pixs = 1;
			msb_array_idx = 0;
			break;
		case D_IM_B2R_STL_DTYP_PACK10:
			p_msb_offset = &msb_offset_pack10[0];
			cycle_pixs = ImB2r1_D_IM_B2R_PACK10_MSB_CYCLE_PIXS;
			msb_array_idx = msb_offset_to_pixs_pack10[im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).topOffset];
			break;
//		case D_IM_B2R_STL_DTYP_PACK12:
		default:
			p_msb_offset = &msb_offset_pack12[0];
			cycle_pixs = ImB2r1_D_IM_B2R_PACK12_MSB_CYCLE_PIXS;
			msb_array_idx = (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).topOffset == 0)?(0):(1);
			break;
	}

	trim_left = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).inputSize.img_left;

	msb_array_idx += (USHORT)( trim_left % cycle_pixs );

#ifdef IM_B2R_DEBUG_PRINT
#if 0
	Ddim_Print(( "imB2rCalcTopMsbOffsetSdramInput(): msb=%u\n", p_msb_offset ));
#endif
#endif

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBROFS.word = p_msb_offset[msb_array_idx];

	Im_B2R_Off_Pclk( pipe_no );
}

/* Top color set to register
 */
static VOID imB2rSetTopColorB2bDirect( UCHAR pipe_no )
{
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "imB2rSetTopColorB2bDirect error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	Im_B2R_On_Pclk( pipe_no );

	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRCTL.bit.PIXEL = im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).bayerTopPixel;

	Im_B2R_Off_Pclk( pipe_no );
}
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/* B2R Initialize
 */
INT32 Im_B2R_Init(UCHAR pipe_no )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Init error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imB2rReset( pipe_no );
	ImB2r1_IM_B2R_DSB();

	// Initalize of Managemnet information & Reset of Internal buffer
	imB2rManagerInit( pipe_no );

	imB2rCalcRingPixs( pipe_no );

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).topOffset = 0;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).wasStarted = ImB2r1_D_IM_B2R_FALSE;
	}

#ifdef CO_DEBUG_ON_PC
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->F_B2R.CNTL.CNTL.bit.TRG = ImB2r1_D_IM_B2R_FB2RTRG_IDLE;
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBR.YBRTRG.bit.YBRTRG = ImB2r1_D_IM_B2R_YBRTRG_IDLE;
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->YBW.YBWTRG.bit.YBWTRG = ImB2r1_D_IM_B2R_YBWTRG_IDLE;
	}
#endif

	return D_DDIM_OK;
}

/* Set Managed Input Address information
 */
INT32 Im_B2R_Set_InAddr_Info(UCHAR pipe_no, const T_IM_B2R_INADDR_INFO* const in_addr )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( in_addr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_Still_InAddr_Info error. in_addr = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_InAddr_Info error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inAddr = (ULONG)in_addr->raw.addr;
		imB2rSetYbrAddressSdramInput( loop_cnt );
	}

	return D_DDIM_OK;
}

/* B2R Interrupt Handler
 */
VOID Im_B2R_Int_Handler( UCHAR pipe_no )
{
	UINT32			loopcnt;
	DDIM_USER_ER	ercd;
	ULONG			b2r_inte;
	ULONG			b2r_intf;
	ULONG			b2r_intf_clr;
	ULONG			f_b2r_inte;
	ULONG			f_b2r_intf;
	ULONG			f_b2r_intf_clr;

	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Int_Handler error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler begin\n" ));
#endif

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler on pclk\n" ));
#endif
	Im_B2R_On_Pclk( pipe_no );

	if( im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).videoPhotoMode == ImB2r1_D_IM_B2R_MODE_SDRAM_INPUT ) {
		if( !((im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRTRG.bit.YBRTRG != ImB2r1_D_IM_B2R_YBRTRG_IDLE )
		   || (im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWTRG.bit.YBWTRG != ImB2r1_D_IM_B2R_YBWTRG_IDLE )
		   || (im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWCTL.bit.YBWCSE != 0 ))) {
#ifdef CO_DEBUG_PRINT_IM_B2R
			Ddim_Print(( "Im_B2R_Int_Handler off clk\n" ));
#endif
			Im_B2R_Off_Clk( pipe_no );
			Im_B2R_Off_Iclk( pipe_no );
		}
	}
	ImB2r1_IM_B2R_DSB();

	b2r_inte = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTE.word;
	b2r_intf = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTF.word;
	b2r_intf_clr = 0;
	f_b2r_inte = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTE.word;
	f_b2r_intf = im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTF.word;
	f_b2r_intf_clr = 0;

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler inte=0x%lx, intf=0x%lx f_inte=0x%lx f_intf=0x%lx\n", b2r_inte, b2r_intf, f_b2r_inte, f_b2r_intf ));
#endif

	// Call of Callback API for interrupt status

	for( loopcnt = 0; loopcnt < (sizeof(S_G_IM_B2R_INTTBL_JDSB2R[0]) / sizeof(S_G_IM_B2R_INTTBL_JDSB2R[0][0])); loopcnt++ ) {
		if( ((b2r_intf & S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].flgBitmask) != 0)
		 && ((b2r_inte & S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].enaBitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_B2R
			Ddim_Print(( "Im_B2R_Int_Handler begin JDSB2R 0x%x\n", S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].flgBitmask ));
#endif

			if(( S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].intStatus == D_IM_B2R1_INT_STATE_YBW_END )
			|| ( S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].intStatus == D_IM_B2R2_INT_STATE_YBW_END )) {
				imB2rLatestAddrUpdate( pipe_no );
			}

			im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).intStatus = S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].intStatus;
			im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).busyState &= ~(S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].busyState);

			b2r_intf_clr |= S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].flgBitmask;

			ercd = DDIM_User_Set_Flg( FID_IM_B2R, S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].waitflg );
			if( ercd != D_DDIM_USER_E_OK ) {
				Ddim_Print(( "Im_B2R_Int_Handler: invalid FID. 0x%lx\n", S_G_IM_B2R_INTTBL_JDSB2R[pipe_no][loopcnt].waitflg ));
			}

			if (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).b2rUserHandler) {
				im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).b2rUserHandler( (UINT32*)&im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).intStatus, im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).userParam );
			}
		}
	}

	if( ((f_b2r_intf & S_G_IM_B2R_INTTBL_FB2R[pipe_no].flgBitmask) != 0)
	 && ((f_b2r_inte & S_G_IM_B2R_INTTBL_FB2R[pipe_no].enaBitmask) != 0) ) {

#ifdef CO_DEBUG_PRINT_IM_B2R
		Ddim_Print(( "Im_B2R_Int_Handler begin FB2R 0x%x\n", S_G_IM_B2R_INTTBL_FB2R[pipe_no].flgBitmask ));
#endif

		im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).intStatus = S_G_IM_B2R_INTTBL_FB2R[pipe_no].intStatus;
		im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).busyState &= ~(S_G_IM_B2R_INTTBL_FB2R[pipe_no].busyState);

		f_b2r_intf_clr |= S_G_IM_B2R_INTTBL_FB2R[pipe_no].flgBitmask;

		ercd = DDIM_User_Set_Flg( FID_IM_B2R, S_G_IM_B2R_INTTBL_FB2R[pipe_no].waitflg );
		if( ercd != D_DDIM_USER_E_OK ) {
			Ddim_Print(( "Im_B2R_Int_Handler: invalid FID. 0x%lx\n", S_G_IM_B2R_INTTBL_FB2R[pipe_no].waitflg ));
		}

		if (im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).b2rUserHandler) {
			im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).b2rUserHandler( (UINT32*)&im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).intStatus, im_b2r2_get_g_im_b2r_state(imB2r2,pipe_no).userParam );
		}
	}

	// Clear interrupt
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTF.word = b2r_intf_clr;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTF.word = f_b2r_intf_clr;


#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler intf=0x%lx, %0xlx\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.YBINTF.word, im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CNTL.B2RINTF.word ));
#endif

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler off pclk\n" ));
#endif
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

#ifdef CO_DEBUG_PRINT_IM_B2R
	Ddim_Print(( "Im_B2R_Int_Handler end\n" ));
#endif
}

#ifdef IM_B2R_STATUS_PRINT
VOID Im_B2R_Print_Status( VOID )
{
	UINT32 loopcnt;
	UINT32 loopcnt2;
	ImB2r2 *imB2r2=im_b2r2_get();

	for( loopcnt2 = 0; loopcnt2 < 2; loopcnt2++ ) {
		Ddim_Print(( "PIPE%u:\n", loopcnt2 ));
		Ddim_Print(( "\tOutput pixs:\n" ));
		Ddim_Print(( "\t\tYBW x=%u, y=%u\n", im_b2r_calc_ybw_out_width(loopcnt2), im_b2r_calc_ybw_out_lines(loopcnt2) ));
		Ddim_Print(( "\tgIM_B2R_State:\n" ));
		Ddim_Print(( "\t\twas_started = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).wasStarted ));
		Ddim_Print(( "\t\tvideo_photo_mode = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).videoPhotoMode ));
		Ddim_Print(( "\t\tbusy_state = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).busyState ));
		Ddim_Print(( "\t\tcia_bypass = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ciaBypass ));
		Ddim_Print(( "\t\tcia_padding = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ciaPadding ));
		Ddim_Print(( "\t\tint_status = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).intStatus ));
		Ddim_Print(( "\t\tb2r_user_handler = 0x%x\n", (UINT32)im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).b2rUserHandler ));
		Ddim_Print(( "\t\tuser_param = 0x%x\n", (UINT32)im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).userParam ));
		Ddim_Print(( "\t\tinput_dtype = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputDtype ));
		Ddim_Print(( "\t\tbayer_top_pixel = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).bayerTopPixel ));
		Ddim_Print(( "\t\tin_addr = 0x%x\n", (UINT32)im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inAddr ));
		Ddim_Print(( "\t\tinput_global = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputGlobal ));
		Ddim_Print(( "\t\ttop_offset = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).topOffset ));
		Ddim_Print(( "\t\tring_pixs_info.padEnable = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ringPixsInfo.padEnable ));
		Ddim_Print(( "\t\tring_pixs_info.ringPixs = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ringPixsInfo.ringPixs ));
		Ddim_Print(( "\t\tring_pixs_info.padPixs = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ringPixsInfo.padPixs ));
		Ddim_Print(( "\t\tring_pixs_info.refPixs = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).ringPixsInfo.refPixs ));
		Ddim_Print(( "\t\tinput_size.img_top = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputSize.img_top ));
		Ddim_Print(( "\t\tinput_size.img_left = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputSize.img_left ));
		Ddim_Print(( "\t\tinput_size.img_width = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputSize.img_width ));
		Ddim_Print(( "\t\tinput_size.img_lines = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).inputSize.img_lines ));
		Ddim_Print(( "\t\ttrim.trimming_enable = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).trim.trimming_enable ));
		Ddim_Print(( "\t\ttrim.start_x = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).trim.start_x ));
		Ddim_Print(( "\t\ttrim.start_y = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).trim.start_y ));
		Ddim_Print(( "\t\ttrim.width = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).trim.width ));
		Ddim_Print(( "\t\ttrim.lines = %u\n", im_b2r2_get_g_im_b2r_state(imB2r2,loopcnt2).trim.lines ));
		Ddim_Print(( "\tgIM_B2R_Out_Mng[%u]:\n", loopcnt2 ));
		Ddim_Print(( "\t\tlatest_idx = %u\n", S_G_IM_B2R_OUT_MNG[loopcnt2].latestIdx ));
		Ddim_Print(( "\t\tbank_initial_position = %u\n", S_G_IM_B2R_OUT_MNG[loopcnt2].bankInfo.bank_initial_position ));
		Ddim_Print(( "\t\tuse_bank_num = %u\n", S_G_IM_B2R_OUT_MNG[loopcnt2].bankInfo.use_bank_num ));
		for( loopcnt = 0; loopcnt < D_IM_B2R_YBW_BANK_MAX; loopcnt++ ) {
			Ddim_Print(( "\t\tBankNum = %u\n", loopcnt ));
			Ddim_Print(( "\t\t\tout_addr[R] = 0x%x\n", (UINT32)S_G_IM_B2R_OUT_MNG[loopcnt2].bankInfo.output_addr[loopcnt].rgb.addr_R ));
			Ddim_Print(( "\t\t\tout_addr[G] = 0x%x\n", (UINT32)S_G_IM_B2R_OUT_MNG[loopcnt2].bankInfo.output_addr[loopcnt].rgb.addr_G ));
			Ddim_Print(( "\t\t\tout_addr[B] = 0x%x\n", (UINT32)S_G_IM_B2R_OUT_MNG[loopcnt2].bankInfo.output_addr[loopcnt].rgb.addr_B ));
		}

		Ddim_Print(( "\tgIM_B2R_ybra_ofs_info:\n" ));
		Ddim_Print(( "\t\tofs_x_pixs[%u] = %u\n", loopcnt2, S_G_IM_B2R_YBRA_OFS_INFO[loopcnt2].ofsXPixs ));
		Ddim_Print(( "\t\tofs_y_pixs[%u] = %u\n", loopcnt2, S_G_IM_B2R_YBRA_OFS_INFO[loopcnt2].ofsYPixs ));
		Ddim_Print(( "\t\tofs_bytes[%u] = %lu\n", loopcnt2, S_G_IM_B2R_YBRA_OFS_INFO[loopcnt2].ofsBytes ));
	}
}

VOID Im_B2R_Print_AccEnStatus( VOID )
{
	UINT32 loopcnt;
	ImB2r2 *imB2r2=im_b2r2_get();

	Im_B2R_On_Pclk( D_IM_B2R_PIPE12 );
	for( loopcnt = 0; loopcnt < 2; loopcnt++ ) {
		Ddim_Print(( "RAMAEN_BAY_DEKNEE = 0x%x\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loopcnt)->B2R_CMN.RAMAEN.bit.RAMAEN_BAY_DEKNEE ));
		Ddim_Print(( "RAMAEN_RGB_KNEE = 0x%x\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loopcnt)->B2R_CMN.RAMAEN.bit.RAMAEN_RGB_KNEE ));
		Ddim_Print(( "RAMAEN_YBR = 0x%x\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loopcnt)->B2R_CMN.RAMAEN.bit.RAMAEN_YBR ));
		Ddim_Print(( "RAMAEN_YBW = 0x%x\n", im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loopcnt)->B2R_CMN.RAMAEN.bit.RAMAEN_YBW ));
	}
	Im_B2R_Off_Pclk( D_IM_B2R_PIPE12 );
}
#endif



/* Set Managed bank information
 */
INT32 Im_B2R_Set_OutBankInfo( UCHAR pipe_no, const T_IM_B2R_OUTBANK_INFO* const b2r_bank )
{
	INT32 ercd;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( b2r_bank == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_OutBank_Info error. b2r_bank = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_OutBankInfo error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo = *b2r_bank;

	// YBWA
	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWCTL.bit.USEBANK = S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.use_bank_num;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_0_0 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_1_0 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_G;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_2_0 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_0].rgb.addr_B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_0_1 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_1_1 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_G;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_2_1 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_1].rgb.addr_B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_0_2 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_1_2 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_G;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_2_2 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_2].rgb.addr_B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_0_3 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_1_3 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_G;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWA.bit.YBWA_2_3 = (ULONG)S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.output_addr[D_IM_B2R_YBW_BANK_3].rgb.addr_B;
	Im_B2R_Off_Pclk( pipe_no );

	// Set bank index & top address information
	ercd = Im_B2R_Set_OutBankIndex( pipe_no, S_G_IM_B2R_OUT_MNG[pipe_no].bankInfo.bank_initial_position );
	if( ercd != D_DDIM_OK ) {
		return ercd;
	}

	return D_DDIM_OK;
}

/* Get Latest Address information
 */
INT32 Im_B2R_Get_Latest_OutAddr( UCHAR pipe_no, UCHAR* const latest_bank_idx, T_IM_B2R_OUTADDR_INFO* const latestAddr )
{
#ifdef CO_PARAM_CHECK
	if( latestAddr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_Latest_OutAddr error. latestAddr = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_Latest_OutAddr error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*latest_bank_idx = S_G_IM_B2R_OUT_MNG[pipe_no].latestIdx;
	*latestAddr     = S_G_IM_B2R_OUT_MNG[pipe_no].latestAddr;

	return D_DDIM_OK;
}


/* Get bank index value
 */
INT32 Im_B2R_Get_OutBankIndex( UCHAR pipe_no, UCHAR* const bank_index )
{
#ifdef CO_PARAM_CHECK
	if( bank_index == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_BankIndex error. bank_index = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_OutBankIndex error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	*bank_index = S_G_IM_B2R_OUT_MNG[pipe_no].latestIdx;

	return D_DDIM_OK;
}


/* B2R get rectangle Control information.
 */
INT32 Im_B2R_Get_Rect_Param( UCHAR pipe_no, T_IM_B2R_RECT* const b2r_rect_param )
{
#ifdef CO_PARAM_CHECK
	if( b2r_rect_param == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Get_Rect_Param error. b2r_rect_param = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_Rect_Param error. pipe_no>=D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif

	*b2r_rect_param = S_G_IM_B2R_RECT_PARAM[pipe_no];

	return D_DDIM_OK;
}

/* B2R rectangle Control
 */
INT32 Im_B2R_Set_Rect( UCHAR pipe_no, const T_IM_B2R_RECT* const b2r_rect_param )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if(b2r_rect_param == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_Rect error. b2r_rect_param = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_Rect error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inputSize = b2r_rect_param->input_size;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inputSize.img_width = ImB2r1_IM_B2R_ROUNDDOWN_2(im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).inputSize.img_width);

		if( im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).videoPhotoMode == ImB2r1_D_IM_B2R_MODE_B2B_DIRECT ) {
			im_b2r_calc_in_rect_b2b_direct( loop_cnt );
			imB2rSetTopColorB2bDirect( loop_cnt );
		}
		else {
			im_b2r_calc_ybr_address_sdram_input( loop_cnt );
			im_b2r_calc_in_rect_sdram_input( loop_cnt );
			im_b2r_calc_top_color_sdram_input( loop_cnt );
			imB2rCalcTopMsbOffsetSdramInput( loop_cnt );
		}
		S_G_IM_B2R_RECT_PARAM[loop_cnt] = *b2r_rect_param;
	}

	// It sets it to the register at once.
	Im_B2R_On_Pclk( pipe_no );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWDEF, union io_b2r_ybwdef, YBWDEF, b2r_rect_param->output_size.output_global_w );
	Im_B2R_Off_Pclk( pipe_no );
	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}

/* B2R Control (each mode common control)
 */
INT32 Im_B2R_Ctrl( UCHAR pipe_no, const T_IM_B2R_CTRL* const b2r_ctrl )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImB2r2 *imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	if( b2r_ctrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl error. b2r_ctrl = NULL\n"));
		return D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl error. pipe_no>D_IM_B2R_PIPE12\n" ));
		return D_IM_B2R_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_b2r_get_loop_val( pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).bayerTopPixel  = b2r_ctrl->bayer_top_pixel;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaBypass       = b2r_ctrl->cia_bypass;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaPadding      = b2r_ctrl->cia_padding;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).b2rUserHandler = b2r_ctrl->b2r_user_handler;
		im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).userParam       = b2r_ctrl->user_param;
	}

	Im_B2R_On_Pclk( pipe_no );

	// YBR
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBR.YBRCTL.bit.DKNEN = b2r_ctrl->deknee_enable;

	// YBCH
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWDOS        = b2r_ctrl->ybw.axi_write_mode.out_sel;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWAXMD.bit.YBWBL         = b2r_ctrl->ybw.axi_write_mode.burst_length;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWREQMSK.bit.YBWREQMSK_0 = b2r_ctrl->ybw.write_request_mask[D_IM_B2R_PORT_0];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWREQMSK.bit.YBWREQMSK_1 = b2r_ctrl->ybw.write_request_mask[D_IM_B2R_PORT_1];
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBCH.YBWREQMSK.bit.YBWREQMSK_2 = b2r_ctrl->ybw.write_request_mask[D_IM_B2R_PORT_2];

	// B2R_CMN
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.ELNLV.word  = b2r_ctrl->line_intr.count;
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.B2RMODE.bit.CIABYP = im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaBypass;
		im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,loop_cnt)->B2R_CMN.B2RMODE.bit.CIAPDD = im_b2r2_get_g_im_b2r_state(imB2r2,loop_cnt).ciaPadding;
	}
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.DINSEL.bit.EXTOEN   = b2r_ctrl->ext_out_en;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->B2R_CMN.EXALMSL.bit.EXALMSL = b2r_ctrl->ext_out_alarm;

	// YBW
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWCTL.bit.YBWDTYP = b2r_ctrl->ybw.output_dtype;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWCTL.bit.YBWCSE  = b2r_ctrl->ybw_continue_start_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWMD.bit.TRMEN    = b2r_ctrl->ybw.trim_out_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->YBW.YBWMD.bit.KNEEN    = b2r_ctrl->ybw.knee_enable;

	Im_B2R_Off_Pclk( pipe_no );

	imB2rCalcRingPixs( pipe_no );

	ImB2r1_IM_B2R_DSB();

	return D_DDIM_OK;
}


ImB2r1 *im_b2r1_get()
{
	static ImB2r1 *imB2r1 = NULL;
	if(!imB2r1)
		imB2r1 = k_object_new_with_private(IM_TYPE_B2R1,sizeof(ImB2r1Private));
	return imB2r1;
}

