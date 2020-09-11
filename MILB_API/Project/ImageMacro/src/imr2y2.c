/*
 * imr2y2.c
 *
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :gonghaotian
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

#include "imr2y2.h"
#include "imr2yproc.h"
#include "im_r2y.h"
#include "driver_common.h"
#include "imr2yclk.h"
#include "dd_arm.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2y2, im_r2y2);
#define IM_R2Y2_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2y2Private, IM_TYPE_R2Y2))


#define im_r2y_rounddown_2(a)					(((a) >> 1) << 1)					// for 2 byte alignment

#define D_IM_R2Y_PACK12_MSB_CYCLE_PIXS	(2)
#define im_r2y_wait_usec( usec )				Dd_ARM_Wait_ns( (usec) * 1000 )

// YYRHSIZ register value
#define D_IM_R2Y_YYRHSIZ_MIN			(96)
#define D_IM_R2Y_YYRHSIZ_MAX			(2360)

// YYRVSIZ register value
#define D_IM_R2Y_YYRVSIZ_MIN			(72)
#define D_IM_R2Y_YYRVSIZ_MAX			(8960)


#define im_r2y_inc_bank_index(bank_index, max)	(((bank_index) + 1) % (max))


struct _ImR2y2Private
{
	int a;
};


typedef struct {
	ULONG					x_start_pos;	// resize horizontal start pos		@RSZ0HSTA, @RSZ1HSTA, @RSZ2HSTA
	ULONG					x_pitch;		// resize horizontal pitch			@RSZ0HPIT, @RSZ1HPIT, @RSZ2HPIT
	ULONG					y_start_pos;	// resize vertical start pos		@RSZ0VSTA, @RSZ1VSTA, @RSZ2VSTA
	ULONG					y_pitch;		// resize vertical pitch			@RSZ0VPIT, @RSZ1VPIT, @RSZ2VPIT
} T_IM_R2Y_OUT_PITCH;

//TODO
static volatile UCHAR gim_r2y_yyw_param_hold_ctrl_cnt[D_IM_R2Y_PIPE_COUNT] = {0,0};

// Resize parameter
static volatile T_IM_R2Y_RESIZE_PARAM gIM_R2Y_Resize_Param[D_IM_R2Y_PIPE_COUNT];

static ULONG gOsUsr_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));



static VOID imR2yCalcTopMsbOffsetSdramInput( UCHAR pipe_no );
static VOID imR2yCalcYyrAddressSdramInput( UCHAR pipe_no );
static VOID imR2ySetOutPitch( UCHAR pipe_no, T_IM_R2Y_OUT_PITCH const r2y_out_pitch[D_IM_R2Y_YYW_CH_MAX] );
static VOID imR2yCalcOutPitch( UCHAR pipe_no );
static VOID imR2yCalcInRectSdramInput( UCHAR pipe_no );


/*
 * IMPL
 */
static void im_r2y2_constructor(ImR2y2 *self)
{
	ImR2y2Private *priv = IM_R2Y2_GET_PRIVATE(self);
}

static void im_r2y2_destructor(ImR2y2 *self)
{
	ImR2y2Private *priv = IM_R2Y2_GET_PRIVATE(self);
}


/* Calculate top-left pixel MSB offset bit.
 */
static VOID imR2yCalcTopMsbOffsetSdramInput( UCHAR pipe_no )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

	static const UCHAR msb_offset_pack12[D_IM_R2Y_PACK12_MSB_CYCLE_PIXS * 2] = {
		0, 4, 0, 4
	};
	static const UCHAR msb_offset_pack8_16[1] = {
		0
	};
	USHORT trim_left[D_IM_R2Y_PORT_MAX];
	USHORT msb_array_idx[D_IM_R2Y_PORT_MAX];
	USHORT cycle_pixs;
	UCHAR const* p_msb_offset;

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcTopMsbOffsetSdramInput error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );

	switch( gIM_R2Y_State[pipe_no].input_dtype ) {
		case D_IM_R2Y_READ_DTYP_PACK8:	// FALL THROUGH
		case D_IM_R2Y_READ_DTYP_PACK16:
			p_msb_offset = &msb_offset_pack8_16[0];
			cycle_pixs = 1;
			msb_array_idx[D_IM_R2Y_PORT_0] = 0;
			msb_array_idx[D_IM_R2Y_PORT_1] = 0;
			msb_array_idx[D_IM_R2Y_PORT_2] = 0;
			break;
//		case D_IM_R2Y_READ_DTYP_PACK12:
		default:
			p_msb_offset = &msb_offset_pack12[0];
			cycle_pixs = D_IM_R2Y_PACK12_MSB_CYCLE_PIXS;
			msb_array_idx[D_IM_R2Y_PORT_0] = (gIM_R2Y_State[pipe_no].top_offset[D_IM_R2Y_PORT_0] == 0)?(0):(1);
			msb_array_idx[D_IM_R2Y_PORT_1] = (gIM_R2Y_State[pipe_no].top_offset[D_IM_R2Y_PORT_1] == 0)?(0):(1);
			msb_array_idx[D_IM_R2Y_PORT_2] = (gIM_R2Y_State[pipe_no].top_offset[D_IM_R2Y_PORT_2] == 0)?(0):(1);
			break;
	}

	trim_left[D_IM_R2Y_PORT_0] = gIM_R2Y_State[pipe_no].input_size.img_left;
	trim_left[D_IM_R2Y_PORT_1] = gIM_R2Y_State[pipe_no].input_size.img_left;
	trim_left[D_IM_R2Y_PORT_2] = gIM_R2Y_State[pipe_no].input_size.img_left;

	msb_array_idx[D_IM_R2Y_PORT_0] += (USHORT)( trim_left[D_IM_R2Y_PORT_0] % cycle_pixs );
	msb_array_idx[D_IM_R2Y_PORT_1] += (USHORT)( trim_left[D_IM_R2Y_PORT_1] % cycle_pixs );
	msb_array_idx[D_IM_R2Y_PORT_2] += (USHORT)( trim_left[D_IM_R2Y_PORT_2] % cycle_pixs );

#ifdef IM_R2Y_DEBUG_PRINT
#if 0
	Ddim_Print(( "imR2yCalcTopMsbOffsetSdramInput(): msb=%u\n", p_msb_offset[msb_array_idx] ));
#endif
#endif

	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYROFS.bit.YYROFS_0 = p_msb_offset[msb_array_idx[D_IM_R2Y_PORT_0]];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYROFS.bit.YYROFS_1 = p_msb_offset[msb_array_idx[D_IM_R2Y_PORT_1]];
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYROFS.bit.YYROFS_2 = p_msb_offset[msb_array_idx[D_IM_R2Y_PORT_2]];

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
}

/* Calculate RGB trimming bytes from RGB address set by im_r2y_set_inaddr_info(im_r2y_new(),)
 */
static VOID imR2yCalcYyrAddressSdramInput( UCHAR pipe_no )
{
	ULONG tmp_top;
	ULONG tmp_left;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile T_IM_R2Y_YYRA_OFS_INFO* gIM_R2Y_yyra_ofs_info = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcYyrAddressSdramInput error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	// Setting of offset pixs
	gIM_R2Y_yyra_ofs_info[pipe_no].ofs_x_pixs = gIM_R2Y_State[pipe_no].input_size.img_left;
	gIM_R2Y_yyra_ofs_info[pipe_no].ofs_y_pixs = gIM_R2Y_State[pipe_no].input_size.img_top;

	// Auto calcurate of Overlap width
	switch( gIM_R2Y_State[pipe_no].input_dtype ) {
		case D_IM_R2Y_READ_DTYP_PACK12:
			tmp_top  = (gIM_R2Y_State[pipe_no].input_global * gIM_R2Y_yyra_ofs_info[pipe_no].ofs_y_pixs);
			tmp_left = (gIM_R2Y_yyra_ofs_info[pipe_no].ofs_x_pixs * 3 / 2);	// x1.5
			break;
		case D_IM_R2Y_READ_DTYP_PACK16:
			tmp_top  = (gIM_R2Y_State[pipe_no].input_global * gIM_R2Y_yyra_ofs_info[pipe_no].ofs_y_pixs);
			tmp_left = (gIM_R2Y_yyra_ofs_info[pipe_no].ofs_x_pixs * 2);		// x2.0
			break;
		default:// D_IM_R2Y_READ_DTYP_PACK8
			tmp_top  = (gIM_R2Y_State[pipe_no].input_global * gIM_R2Y_yyra_ofs_info[pipe_no].ofs_y_pixs);
			tmp_left = (gIM_R2Y_yyra_ofs_info[pipe_no].ofs_x_pixs);			// x1.0
			break;
	}

	gIM_R2Y_yyra_ofs_info[pipe_no].ofs_bytes = (tmp_top + tmp_left);
}

/* Set output(YYW) start and pitch registers.
 */
static VOID imR2ySetOutPitch( UCHAR pipe_no, T_IM_R2Y_OUT_PITCH const r2y_out_pitch[D_IM_R2Y_YYW_CH_MAX] )
{
	UINT32 yyw_no;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);


	T_IM_R2Y_OUT_PITCH r2y_out_pitch_temp = {
		.x_start_pos = 0,
		.x_pitch = 0,
		.y_start_pos = 0,
		.y_pitch = 0,
	};

#ifdef CO_PARAM_CHECK
	if( r2y_out_pitch == NULL ) {
		Ddim_Assertion(( "imR2ySetOutPitch error. r2y_out_pitch == NULL\n" ));
		return;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2ySetOutPitch error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(), pipe_no);
	for( yyw_no = D_IM_R2Y_YYW_CH_0; yyw_no < D_IM_R2Y_YYW_CH_MAX - 1; yyw_no++ ) {
		switch( yyw_no ) {
			default:
				break;
			case D_IM_R2Y_YYW_CH_0:
				if( gIM_R2Y_State[pipe_no].yyw_enable[yyw_no] == D_IM_R2Y_ENABLE_OFF ) {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT = D_IM_R2Y_STA_PIT_1_0;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT = D_IM_R2Y_STA_PIT_1_0;
				}
				else {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA = r2y_out_pitch[yyw_no].x_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT = r2y_out_pitch[yyw_no].x_pitch;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA = r2y_out_pitch[yyw_no].y_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT = r2y_out_pitch[yyw_no].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA;
				r2y_out_pitch_temp.x_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT;
				r2y_out_pitch_temp.y_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA;
				r2y_out_pitch_temp.y_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yyw_no=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						0,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HSTA.bit.RSZ0HSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0HPIT.bit.RSZ0HPIT,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VSTA.bit.RSZ0VSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ0VPIT.bit.RSZ0VPIT
						));
#endif
				break;
			case D_IM_R2Y_YYW_CH_1:
				if( gIM_R2Y_State[pipe_no].yyw_enable[yyw_no] == D_IM_R2Y_ENABLE_OFF ) {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT = D_IM_R2Y_STA_PIT_1_0;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT = D_IM_R2Y_STA_PIT_1_0;
				}
				else {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA = r2y_out_pitch[yyw_no].x_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT = r2y_out_pitch[yyw_no].x_pitch;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA = r2y_out_pitch[yyw_no].y_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT = r2y_out_pitch[yyw_no].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA;
				r2y_out_pitch_temp.x_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT;
				r2y_out_pitch_temp.y_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA;
				r2y_out_pitch_temp.y_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yyw_no=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						1,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HSTA.bit.RSZ1HSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1HPIT.bit.RSZ1HPIT,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VSTA.bit.RSZ1VSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ1VPIT.bit.RSZ1VPIT
						));
#endif
				break;
			case D_IM_R2Y_YYW_CH_2:
				if( gIM_R2Y_State[pipe_no].yyw_enable[yyw_no] == D_IM_R2Y_ENABLE_OFF ) {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT = D_IM_R2Y_STA_PIT_1_0;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA = 0x00000000;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT = D_IM_R2Y_STA_PIT_1_0;
				}
				else {
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA = r2y_out_pitch[yyw_no].x_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT = r2y_out_pitch[yyw_no].x_pitch;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA = r2y_out_pitch[yyw_no].y_start_pos;
					gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT = r2y_out_pitch[yyw_no].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA;
				r2y_out_pitch_temp.x_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT;
				r2y_out_pitch_temp.y_start_pos	= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA;
				r2y_out_pitch_temp.y_pitch		= gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yyw_no=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						1,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HSTA.bit.RSZ2HSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2HPIT.bit.RSZ2HPIT,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VSTA.bit.RSZ2VSTA,
						gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.RSZ2VPIT.bit.RSZ2VPIT
						));
#endif
				break;
		}
		gIM_R2Y_Resize_Param[pipe_no].r2y_resize_pitch.output_pitch[yyw_no].output_x_start_pos	= r2y_out_pitch_temp.x_start_pos;
		gIM_R2Y_Resize_Param[pipe_no].r2y_resize_pitch.output_pitch[yyw_no].output_x_pitch		= r2y_out_pitch_temp.x_pitch;
		gIM_R2Y_Resize_Param[pipe_no].r2y_resize_pitch.output_pitch[yyw_no].output_y_start_pos	= r2y_out_pitch_temp.y_start_pos;
		gIM_R2Y_Resize_Param[pipe_no].r2y_resize_pitch.output_pitch[yyw_no].output_y_pitch		= r2y_out_pitch_temp.y_pitch;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(), pipe_no);
}


/* Calculate output(YYW) start and pitch value.
 */
static VOID imR2yCalcOutPitch( UCHAR pipe_no )
{
	UINT32 yyw_no;
	ULONG  input_width;			// XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX . (32bits)
	ULONG  input_lines;			// XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX . (32bits)
	ULONG  input_calc_width;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  input_calc_lines;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  input_calc_width_l;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  input_calc_lines_l;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  input_calc_width_c;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  input_calc_lines_c;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  x_pitch;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  y_pitch;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  x_start;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  y_start;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  x_ref;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	ULONG  y_ref;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	T_IM_R2Y_OUT_PITCH r2y_out_pitch[D_IM_R2Y_YYW_CH_MAX];
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);


#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcOutPitch error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( gIM_R2Y_State[pipe_no].yyw_rect_valid != D_IM_R2Y_ENABLE_ON ) {
		return;
	}

	// calc. and set new output size to r2y_ctrl(YYW)
	/*
	 * refer JDSR2Y_F2E section 5.2.3 Output size
	 *
	 * Parameter Description
	 *     for SDRAM input mode:
	 *        R_HSZ = YYRHSIZ
	 *        R_VSZ = YYRVSIZ
	 *     for direct input mode:
	 *        R_HSZ = H_Size is based on processing of connection origin.
	 *        R_VSZ = V_Size is based on processing of connection origin.
	 *     common parameter:
	 *        mYCF = R2YMODE.YCFPDD + R2YMODE.YCFBYP
	 *            mYCF = 0 : RP = 6
	 *            mYCF > 0 : RP = 0
	 *        F_HSZ = R_HSZ - RP
	 *        F_VSZ = R_VSZ - RP
	 *
	 * Calculating formula
	 *     for Bi-linear interpolation(YYW ch0/ch1/ch2 resizer)
	 *         RS_HSZx = ((((F_HSZ - 1) * 16384 - RSZxHSTA) / RSZxHPIT) + 1)
	 *             ==>
	 *         RSZxHPIT = ((F_HSZ - 1) * 16384) / (RS_HSZx - 1)					(RSZxHSTA assume 0)
	 *
	 *         RS_VSZx = ((((F_VSZ - 1) * 16384 - RSZxVSTA) / RSZxVPIT) + 1)
	 *             ==>
	 *         RSZxVPIT = ((F_VSZ - 1) * 16384) / (RS_VSZx - 1)					(RSZxVSTA assume 0)
	 *
	 *     for Bi-cubic interpolation(YYW ch0/ch1 resizer)
	 *         RS_HSZx = ((((F_HSZ - 2) * 16384 - RSZxHSTA - 1) / RSZxHPIT) + 1)
	 *             ==>
	 *         RSZxHPIT = ((F_HSZ - 2) * 16384 - 1) / (RS_HSZx - 1)				(RSZxHSTA assume 0)
	 *
	 *         RS_VSZx = ((((F_VSZ - 2) * 16384 - RSZxVSTA - 1) / RSZxVPIT) + 1)
	 *             ==>
	 *         RSZxVPIT = ((F_VSZ - 2) * 16384 - 1) / (RS_VSZx - 1)				(RSZxVSTA assume 0)
	 */

	input_width = gIM_R2Y_State[pipe_no].input_size.img_width
				- gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;
	input_lines = gIM_R2Y_State[pipe_no].input_size.img_lines
				- gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs;

	input_calc_width_l = ((ULONG)(input_width - 1)) * D_IM_R2Y_STA_PIT_1_0;
	input_calc_lines_l = ((ULONG)(input_lines - 1)) * D_IM_R2Y_STA_PIT_1_0;
	input_calc_width_c = ((ULONG)(input_width - 2)) * D_IM_R2Y_STA_PIT_1_0 - 1;
	input_calc_lines_c = ((ULONG)(input_lines - 2)) * D_IM_R2Y_STA_PIT_1_0 - 1;

#ifdef IM_R2Y_DEBUG_PRINT
#if 1
	Ddim_Print(( "imR2yCalcOutPitch(): input_calc_width_l=%lx, input_calc_lines_l=%lx\n",
			input_calc_width_l,
			input_calc_lines_l
			));
	Ddim_Print(( "imR2yCalcOutPitch(): input_calc_width_c=%lx, input_calc_lines_c=%lx\n",
			input_calc_width_c,
			input_calc_lines_c
			));
#endif
#endif

	for( yyw_no = D_IM_R2Y_YYW_CH_0; yyw_no < D_IM_R2Y_YYW_CH_MAX - 1; yyw_no++ ) {
		if( (input_width == gIM_R2Y_State[pipe_no].yyw_width[yyw_no])
		 && (input_lines == gIM_R2Y_State[pipe_no].yyw_lines[yyw_no])
			) {
			// x1.0 mode (dot by dot mode)
			x_pitch = D_IM_R2Y_STA_PIT_1_0;
			y_pitch = D_IM_R2Y_STA_PIT_1_0;
			x_start = 0;
			y_start = 0;
		}
		else {
			// Resized mode

			switch( yyw_no ){
				case D_IM_R2Y_YYW_CH_0:		// FALL THROUGH
				case D_IM_R2Y_YYW_CH_1:
					if( gIM_R2Y_State[pipe_no].resize_mode[yyw_no] == D_IM_R2Y_RSZ_BICUBIC ){
						input_calc_width = input_calc_width_c;
						input_calc_lines = input_calc_lines_c;
					}
					else{
						input_calc_width = input_calc_width_l;
						input_calc_lines = input_calc_lines_l;
					}
					break;
//				case D_IM_R2Y_YYW_CH_2:
				default:
					input_calc_width = input_calc_width_l;
					input_calc_lines = input_calc_lines_l;
					break;
			}
			x_pitch = (ULONG)input_calc_width / (im_r2y_rounddown_2(gIM_R2Y_State[pipe_no].yyw_width[yyw_no]) - 1);
			y_pitch = (ULONG)input_calc_lines / (im_r2y_rounddown_2(gIM_R2Y_State[pipe_no].yyw_lines[yyw_no]) - 1);

			// YYW2 is only supported image size reducion
			if( yyw_no == D_IM_R2Y_YYW_CH_2 ) {
				if( x_pitch < D_IM_R2Y_STA_PIT_1_0 ) {
#ifdef IM_R2Y_DEBUG_PRINT
					Ddim_Print(( "YYW2 width overflow. pit=%lx\n", x_pitch ));
#endif
					x_pitch = D_IM_R2Y_STA_PIT_1_0;
				}
				if( y_pitch < D_IM_R2Y_STA_PIT_1_0 ) {
#ifdef IM_R2Y_DEBUG_PRINT
					Ddim_Print(( "YYW2 lines overflow. pit=%lx\n", y_pitch ));
#endif
					y_pitch = D_IM_R2Y_STA_PIT_1_0;
				}
			}

			x_ref = (im_r2y_rounddown_2(gIM_R2Y_State[pipe_no].yyw_width[yyw_no]) - 1) * x_pitch;
			if( input_calc_width < x_ref ) {
				x_start = 0;
			}
			else {
				x_start = input_calc_width - x_ref;
			}
			y_ref = (im_r2y_rounddown_2(gIM_R2Y_State[pipe_no].yyw_lines[yyw_no]) - 1) * y_pitch;
			if( input_calc_lines < y_ref ) {
				y_start = 0;
			}
			else {
				y_start = input_calc_lines - y_ref;
			}
		}

		r2y_out_pitch[yyw_no].x_start_pos = x_start;
		r2y_out_pitch[yyw_no].y_start_pos = y_start;
		r2y_out_pitch[yyw_no].x_pitch = x_pitch;
		r2y_out_pitch[yyw_no].y_pitch = y_pitch;

#ifdef IM_R2Y_DEBUG_PRINT
#if 1
		{
			ULONG width;
			ULONG lines;
			Ddim_Print(( "imR2yCalcOutPitch(): yyw_width=%u, yyw_lines=%u\n",
					gIM_R2Y_State[pipe_no].yyw_width[yyw_no],
					gIM_R2Y_State[pipe_no].yyw_lines[yyw_no]
					));
			Ddim_Print(( "imR2yCalcOutPitch(): yyw_no=%u, hsta=%lx, hpit=%lx, vsta=%lx, vpit=%lx\n",
					yyw_no,
					x_start,
					x_pitch,
					y_start,
					y_pitch
					));


			if( gIM_R2Y_State[pipe_no].yyw_enable[yyw_no] == D_IM_R2Y_ENABLE_OFF ) {
				continue;
			}

			if( r2y_out_pitch[yyw_no].x_pitch != 0 ) {
				width = (input_calc_width - r2y_out_pitch[yyw_no].x_start_pos) / (r2y_out_pitch[yyw_no].x_pitch) + 1;
			}
			else {
				width = 0;
			}

			if( r2y_out_pitch[yyw_no].y_pitch != 0 ) {
				lines = (input_calc_lines - r2y_out_pitch[yyw_no].y_start_pos) / (r2y_out_pitch[yyw_no].y_pitch) + 1;
			}
			else {
				lines = 0;
			}
			Ddim_Print(( "imR2yCalcOutPitch(): recalc width=%u, line=%u\n", (UINT32)(width), (UINT32)(lines) ));
		}
#endif
#endif
	}

	imR2ySetOutPitch( pipe_no, r2y_out_pitch );
}

/* Calculate input(YYR) width and lines when SDRAM input mode.
 */
static VOID imR2yCalcInRectSdramInput( UCHAR pipe_no )
{
	USHORT img_width;
	USHORT img_lines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcInRectSdramInput error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	// YYRHSIZ (2pixels alignment & Advancing)
	img_width = gIM_R2Y_State[pipe_no].input_size.img_width;
	img_width = im_r2y_min( img_width, (USHORT)D_IM_R2Y_YYRHSIZ_MAX );
	img_width = im_r2y_max( img_width, (USHORT)(D_IM_R2Y_YYRHSIZ_MIN + gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs) );

	// YYRVSIZ
	img_lines = gIM_R2Y_State[pipe_no].input_size.img_lines;
	img_lines = im_r2y_min( img_lines, (USHORT)D_IM_R2Y_YYRVSIZ_MAX );
	img_lines = im_r2y_max( img_lines, (USHORT)(D_IM_R2Y_YYRVSIZ_MIN + gIM_R2Y_State[pipe_no].ring_pixs_info.ref_pixs) );

	im_r2y_clk_on_pclk(im_r2y_clk_new(), pipe_no);
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRHSIZ.word = img_width;
	gIM_Io_R2y_Reg_Ptr[pipe_no]->YYR.YYRVSIZ.word = img_lines;
	im_r2y_clk_off_pclk(im_r2y_clk_new(), pipe_no);
}


//TODO 转公有
// Control access enable register.
INT32 im_r2y_set_access_enable(ImR2y2 *self, UCHAR pipe_no, volatile T_IM_R2Y_ACCESS_ENABLE_MANAGE* const acc_en_mng, const UCHAR acc_enable, const UCHAR wait_enable, const CHAR errmsg[] )
{
	INT32 ret = D_DDIM_OK;
	UCHAR cnt;
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		cnt = acc_en_mng->ctrl_cnt[loop_cnt];
		if( acc_enable == 0 ) {
			if( cnt != 0 ) {
				cnt--;
				if( cnt == 0 ) {
					if( im_r2y_yyw_is_activated( loop_cnt ) ) {
						// Macro busy error
						Ddim_Assertion(( errmsg ));
						ret = D_IM_R2Y_MACRO_BUSY;
					}
					else{
						acc_en_mng->reg_set_func( loop_cnt, 0 );
					}
				}
			}
		}
		else {
			if( cnt == 0 ) {
				if( im_r2y_yyw_is_activated( loop_cnt ) ) {
					// Macro busy error
					Ddim_Assertion(( errmsg ));
					ret = D_IM_R2Y_MACRO_BUSY;
				}
				else{
					cnt++;
					acc_en_mng->reg_set_func( loop_cnt, 1 );

					if( wait_enable != D_IM_R2Y_WAIT_OFF ) {
						im_r2y_wait_usec( D_IM_R2Y_SRAM_WAIT_USEC );
					}
				}
			}
			else if((0 < cnt) && (cnt < 255)) {
				cnt++;
			}
		}
		acc_en_mng->ctrl_cnt[loop_cnt] = cnt;
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );

	return ret;
}

void im_r2y2_loop_set(ImR2y2 *self, UCHAR loop_cnt)
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
	gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
	gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
	gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS = im_r2y_inc_bank_index( gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );

}

void im_r2y2_sta_manage_init(ImR2y2 *self, UCHAR pipe_no, UCHAR size_coef)
{
	// initialize of Resize information
			memset( (USHORT*)&gIM_R2Y_Resize_Param[pipe_no], 0, sizeof(T_IM_R2Y_RESIZE_PARAM) * size_coef );
}

/* Set YYW parameter hold
 */
INT32 im_r2y2_set_yyw_param_hold(ImR2y2 *self, UCHAR pipe_no, UCHAR hold_enable )
{
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_yyw_param_hold error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( hold_enable == 0 ) {
			if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] != 0 ) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]--;
				if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] == 0 ) {
					gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWKPP.bit.YYWKPP = 0;
				}
			}
		}
		else {
			if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] == 0 ) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]++;
				gIM_Io_R2y_Reg_Ptr[loop_cnt]->YYW.YYWKPP.bit.YYWKPP = 1;
			}
			else if((0 < gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]) && (gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] < 255)) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]++;
			}
		}
	}
	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y resize rectangle Control
 */
INT32 im_r2y2_set_resize_rect(ImR2y2 *self, UCHAR pipe_no, const T_IM_R2Y_RESIZE_RECT* const r2y_resize_param )
{
	UINT32 yyw_no;
	UCHAR loop_cnt, loop_sta, loop_end;
	UCHAR div_0a;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_resize_param == NULL) {
		Ddim_Assertion(("im_r2y2_set_resize_rect error. r2y_resize_param = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_resize_rect error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gIM_R2Y_State[loop_cnt].input_size = r2y_resize_param->input_size;
		gIM_R2Y_State[loop_cnt].input_size.img_width = im_r2y_rounddown_2(gIM_R2Y_State[loop_cnt].input_size.img_width);
		gIM_R2Y_Resize_Param[pipe_no].r2y_resize_pitch.input_size = gIM_R2Y_State[loop_cnt].input_size;	/* pgr0869 */

		for( yyw_no = D_IM_R2Y_YYW_CH_0; yyw_no < D_IM_R2Y_YYW_CH_MAX-1; yyw_no++ ) {
			gIM_R2Y_State[loop_cnt].yyw_width[yyw_no] = r2y_resize_param->output_size[yyw_no].yyw_width;
			gIM_R2Y_State[loop_cnt].yyw_lines[yyw_no] = r2y_resize_param->output_size[yyw_no].yyw_lines;
		}

		gIM_R2Y_State[loop_cnt].yyw_rect_valid = D_IM_R2Y_ENABLE_ON;

		if( gIM_R2Y_State[loop_cnt].video_photo_mode == D_IM_R2Y_MODE_SDRAM_INPUT ) {
			imR2yCalcYyrAddressSdramInput( loop_cnt );
			imR2yCalcInRectSdramInput( loop_cnt );
			imR2yCalcTopMsbOffsetSdramInput( loop_cnt );
		}
		imR2yCalcOutPitch( loop_cnt );
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		for( yyw_no = D_IM_R2Y_YYW_CH_0; yyw_no < D_IM_R2Y_YYW_CH_MAX; yyw_no++ ) {
			if( yyw_no < D_IM_R2Y_YYW_CH_MAX - 1 ){
				if( gIM_R2Y_State[loop_cnt].yyw_enable[yyw_no] == D_IM_R2Y_ENABLE_ON ) {	/* pgr0013 pgr0862 */
					if( gIM_R2Y_State[loop_cnt].pix_avg_reduct_en[yyw_no] == D_IM_R2Y_ENABLE_ON ) {	/* pgr0013 pgr0862 */
						gIM_R2Y_State[loop_cnt].yyw_width[yyw_no] = (r2y_resize_param->output_size[yyw_no].yyw_width / 2^(gIM_R2Y_State[loop_cnt].pix_avg_reduct_mode[yyw_no] + 1)) & 0x1FFE;	/* pgr0013 pgr0862 */
						gIM_R2Y_State[loop_cnt].yyw_lines[yyw_no] = (r2y_resize_param->output_size[yyw_no].yyw_lines / 2^(gIM_R2Y_State[loop_cnt].pix_avg_reduct_mode[yyw_no] + 1)) & 0x1FFE;	/* pgr0013 pgr0862 */
					}
				}
			}
			gIM_R2Y_Resize_Param[loop_cnt].r2y_resize_pitch.output_pitch[yyw_no].output_global_w[D_IM_R2Y_PORT_0]	= r2y_resize_param->output_size[yyw_no].output_global_w[D_IM_R2Y_PORT_0];
			gIM_R2Y_Resize_Param[loop_cnt].r2y_resize_pitch.output_pitch[yyw_no].output_global_w[D_IM_R2Y_PORT_1]	= r2y_resize_param->output_size[yyw_no].output_global_w[D_IM_R2Y_PORT_1];
			gIM_R2Y_Resize_Param[loop_cnt].r2y_resize_pitch.output_pitch[yyw_no].output_global_w[D_IM_R2Y_PORT_2]	= r2y_resize_param->output_size[yyw_no].output_global_w[D_IM_R2Y_PORT_2];
		}

		if( gIM_R2Y_State[loop_cnt].yyw_enable[D_IM_R2Y_YYW_CH_0] == D_IM_R2Y_ENABLE_ON && gIM_R2Y_State[loop_cnt].output_mode_0a != D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP ) {
			switch( gIM_R2Y_State[loop_cnt].output_mode_0a ){
				case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_4_Y:
					div_0a = 4;
					break;
				case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_8_Y:
					div_0a = 8;
					break;
				case D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_32_SP:
					div_0a = 32;
					break;
//				case D_IM_R2Y_YYW0A_OUTPUT_MODE_STOP:
				default:
					div_0a = 1;
					break;
			}

			if( gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0] % div_0a ){
				gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0A] = gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0] / div_0a + 1;
			}
			else{
				gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0A] = gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0] / div_0a;
			}
			if( gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0] % div_0a ){
				gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0A] = gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0] / div_0a + 1;
			}
			else{
				gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0A] = gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0] / div_0a;
			}
			gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0A] = ( gIM_R2Y_State[loop_cnt].yyw_width[D_IM_R2Y_YYW_CH_0A] + 1 ) & 0x1FFE;
			gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0A] = ( gIM_R2Y_State[loop_cnt].yyw_lines[D_IM_R2Y_YYW_CH_0A] + 1 ) & 0x1FFE;
		}

		gIM_R2Y_Resize_Param[loop_cnt].resize_select = 0;
		gIM_R2Y_Resize_Param[loop_cnt].r2y_resize_rect = *r2y_resize_param;
		gIM_R2Y_Resize_Param[loop_cnt].resize_select = 1;
	}

	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_0, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_1, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_0, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_1, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2DEF, union io_r2y_yyw2def, YYW2DEF, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWADEF, union io_r2y_yywadef, YYWADEF, r2y_resize_param->output_size[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y resize pitch Control
 */
INT32 im_r2y2_set_resize_pitch(ImR2y2 *self, UCHAR pipe_no, const T_IM_R2Y_RESIZE_PITCH* const r2y_resize_pitch )
{
	UINT32 yyw_no;
	T_IM_R2Y_OUT_PITCH r2y_out_pitch[D_IM_R2Y_YYW_CH_MAX];
	UINT32 output_x_pitch;
	UINT32 output_y_pitch;
	INT32 ercd = D_DDIM_OK;
	UCHAR loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gIM_Io_R2y_Reg_Ptr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile T_IM_R2Y_STATE_MNG* gIM_R2Y_State = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_resize_pitch == NULL) {
		// Parameter setting error
		Ddim_Assertion(("im_r2y2_set_resize_pitch error. r2y_resize_pitch = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no > D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_resize_pitch error. pipe_no>D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipe_no, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// set new rectangle to gIM_R2Y_State
		gIM_R2Y_State[loop_cnt].input_size = r2y_resize_pitch->input_size;

		gIM_R2Y_State[loop_cnt].yyw_rect_valid = D_IM_R2Y_ENABLE_OFF;

		if( gIM_R2Y_State[loop_cnt].video_photo_mode == D_IM_R2Y_MODE_DIRECT ) {
		}
		else {
			imR2yCalcYyrAddressSdramInput( loop_cnt );
			imR2yCalcInRectSdramInput( loop_cnt );
			imR2yCalcTopMsbOffsetSdramInput( loop_cnt );
		}

		for( yyw_no = D_IM_R2Y_YYW_CH_0; yyw_no < D_IM_R2Y_YYW_CH_MAX-1; yyw_no++ ) {
			output_x_pitch = r2y_resize_pitch->output_pitch[yyw_no].output_x_pitch;
			output_y_pitch = r2y_resize_pitch->output_pitch[yyw_no].output_y_pitch;
			if( yyw_no == D_IM_R2Y_YYW_CH_2 ) {
				if( output_x_pitch < D_IM_R2Y_STA_PIT_1_0 ) {
					Ddim_Print(( "YYW2 width overflow. %x\n", output_x_pitch ));
					output_x_pitch = D_IM_R2Y_STA_PIT_1_0;
					ercd = D_IM_R2Y_PARAM_ERROR;
				}
				if( output_y_pitch < D_IM_R2Y_STA_PIT_1_0 ) {
					Ddim_Print(( "YYW2 lines overflow. %x\n", output_y_pitch ));
					output_y_pitch = D_IM_R2Y_STA_PIT_1_0;
					ercd = D_IM_R2Y_PARAM_ERROR;
				}
			}

			r2y_out_pitch[yyw_no].x_start_pos = r2y_resize_pitch->output_pitch[yyw_no].output_x_start_pos;
			r2y_out_pitch[yyw_no].y_start_pos = r2y_resize_pitch->output_pitch[yyw_no].output_y_start_pos;
			r2y_out_pitch[yyw_no].x_pitch = output_x_pitch;
			r2y_out_pitch[yyw_no].y_pitch = output_y_pitch;
#ifdef IM_R2Y_DEBUG_PRINT
			Ddim_Print(( "im_r2y2_set_resize_pitch(): yyw_no=%u, hsta=%lx, hpit=%lx, vsta=%lx, vpit=%lx\n",
						 yyw_no,
						 r2y_out_pitch[yyw_no].x_start_pos,
						 r2y_out_pitch[yyw_no].x_pitch,
						 r2y_out_pitch[yyw_no].y_start_pos,
						 r2y_out_pitch[yyw_no].y_pitch
						 ));
#endif
		}
		imR2ySetOutPitch( loop_cnt, r2y_out_pitch );

		gIM_R2Y_Resize_Param[loop_cnt].resize_select = 0;
		gIM_R2Y_Resize_Param[loop_cnt].r2y_resize_pitch = *r2y_resize_pitch;
		gIM_R2Y_Resize_Param[loop_cnt].resize_select = 2;
	}

	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipe_no );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_0, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_1, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_0].output_global_w[D_IM_R2Y_PORT_1] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_0, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed_a( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_1, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_1].output_global_w[D_IM_R2Y_PORT_1] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYW2DEF, union io_r2y_yyw2def, YYW2DEF, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_2].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_set_reg_signed( gIM_Io_R2y_Reg_Ptr[pipe_no]->YYW.YYWADEF, union io_r2y_yywadef, YYWADEF, r2y_resize_pitch->output_pitch[D_IM_R2Y_YYW_CH_0A].output_global_w[D_IM_R2Y_PORT_0] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipe_no );
	Im_R2Y_Dsb();

	return ercd;
}

/* R2Y get resize rectangle Control information.
 */
INT32 im_r2y2_get_resize_param(ImR2y2 *self, UCHAR pipe_no, T_IM_R2Y_RESIZE_PARAM* const r2y_resize_param )
{
#ifdef CO_PARAM_CHECK
	if( r2y_resize_param == NULL ) {
		Ddim_Assertion(("im_r2y2_get_resize_param error. r2y_resize_param = NULL\n"));
		return D_IM_R2Y_PARAM_ERROR;
	}
	if( pipe_no >= D_IM_R2Y_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_get_resize_param error. pipe_no>=D_IM_R2Y_PIPE12\n" ));
		return D_IM_R2Y_PARAM_ERROR;
	}
#endif

	*r2y_resize_param = gIM_R2Y_Resize_Param[pipe_no];

	return D_DDIM_OK;
}

ImR2y2 *im_r2y2_new(void)
{
	ImR2y2* self = k_object_new_with_private(IM_TYPE_R2Y2,sizeof(ImR2y2Private));
	return self;
}
