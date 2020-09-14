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


#define im_r2y_inc_bank_index(bankIndex, max)	(((bankIndex) + 1) % (max))


struct _ImR2y2Private
{
	int a;
};


typedef struct {
	kulong					x_start_pos;	// resize horizontal start pos		@RSZ0HSTA, @RSZ1HSTA, @RSZ2HSTA
	kulong					x_pitch;		// resize horizontal pitch			@RSZ0HPIT, @RSZ1HPIT, @RSZ2HPIT
	kulong					y_start_pos;	// resize vertical start pos		@RSZ0VSTA, @RSZ1VSTA, @RSZ2VSTA
	kulong					y_pitch;		// resize vertical pitch			@RSZ0VPIT, @RSZ1VPIT, @RSZ2VPIT
} T_IM_R2Y_OUT_PITCH;

//TODO
static volatile kuint16 gim_r2y_yyw_param_hold_ctrl_cnt[ImR2yUtils_PIPE_COUNT] = {0,0};

// Resize parameter
static volatile R2yResizeParam gIM_R2Y_Resize_Param[ImR2yUtils_PIPE_COUNT];

static kulong gOsUsr_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64)));



static void imR2yCalcTopMsbOffsetSdramInput( kuint16 pipeNo );
static void imR2yCalcYyrAddressSdramInput( kuint16 pipeNo );
static void imR2ySetOutPitch( kuint16 pipeNo, T_IM_R2Y_OUT_PITCH const r2y_out_pitch[ImR2yCtrl_YYW_CH_MAX] );
static void imR2yCalcOutPitch( kuint16 pipeNo );
static void imR2yCalcInRectSdramInput( kuint16 pipeNo );


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
static void imR2yCalcTopMsbOffsetSdramInput( kuint16 pipeNo )
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

	static const kuint16 msb_offset_pack12[D_IM_R2Y_PACK12_MSB_CYCLE_PIXS * 2] = {
		0, 4, 0, 4
	};
	static const kuint16 msb_offset_pack8_16[1] = {
		0
	};
	kuint16 trim_left[ImR2yCtrl_PORT_MAX];
	kuint16 msb_array_idx[ImR2yCtrl_PORT_MAX];
	kuint16 cycle_pixs;
	kuint16 const* p_msb_offset;

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcTopMsbOffsetSdramInput error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );

	switch( gImR2yState[pipeNo].inputDtype ) {
		case ImR2yCtrl_READ_DTYP_PACK8:	// FALL THROUGH
		case ImR2yCtrl_READ_DTYP_PACK16:
			p_msb_offset = &msb_offset_pack8_16[0];
			cycle_pixs = 1;
			msb_array_idx[ImR2yCtrl_PORT_0] = 0;
			msb_array_idx[ImR2yCtrl_PORT_1] = 0;
			msb_array_idx[ImR2yCtrl_PORT_2] = 0;
			break;
//		case ImR2yCtrl_READ_DTYP_PACK12:
		default:
			p_msb_offset = &msb_offset_pack12[0];
			cycle_pixs = D_IM_R2Y_PACK12_MSB_CYCLE_PIXS;
			msb_array_idx[ImR2yCtrl_PORT_0] = (gImR2yState[pipeNo].topOffset[ImR2yCtrl_PORT_0] == 0)?(0):(1);
			msb_array_idx[ImR2yCtrl_PORT_1] = (gImR2yState[pipeNo].topOffset[ImR2yCtrl_PORT_1] == 0)?(0):(1);
			msb_array_idx[ImR2yCtrl_PORT_2] = (gImR2yState[pipeNo].topOffset[ImR2yCtrl_PORT_2] == 0)?(0):(1);
			break;
	}

	trim_left[ImR2yCtrl_PORT_0] = gImR2yState[pipeNo].inputSize.imgLeft;
	trim_left[ImR2yCtrl_PORT_1] = gImR2yState[pipeNo].inputSize.imgLeft;
	trim_left[ImR2yCtrl_PORT_2] = gImR2yState[pipeNo].inputSize.imgLeft;

	msb_array_idx[ImR2yCtrl_PORT_0] += (kuint16)( trim_left[ImR2yCtrl_PORT_0] % cycle_pixs );
	msb_array_idx[ImR2yCtrl_PORT_1] += (kuint16)( trim_left[ImR2yCtrl_PORT_1] % cycle_pixs );
	msb_array_idx[ImR2yCtrl_PORT_2] += (kuint16)( trim_left[ImR2yCtrl_PORT_2] % cycle_pixs );

#ifdef IM_R2Y_DEBUG_PRINT
#if 0
	Ddim_Print(( "imR2yCalcTopMsbOffsetSdramInput(): msb=%u\n", p_msb_offset[msb_array_idx] ));
#endif
#endif

	gImIoR2yRegPtr[pipeNo]->YYR.YYROFS.bit.YYROFS_0 = p_msb_offset[msb_array_idx[ImR2yCtrl_PORT_0]];
	gImIoR2yRegPtr[pipeNo]->YYR.YYROFS.bit.YYROFS_1 = p_msb_offset[msb_array_idx[ImR2yCtrl_PORT_1]];
	gImIoR2yRegPtr[pipeNo]->YYR.YYROFS.bit.YYROFS_2 = p_msb_offset[msb_array_idx[ImR2yCtrl_PORT_2]];

	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
}

/* Calculate RGB trimming bytes from RGB address set by im_r2y_set_inaddr_info(im_r2y_new(),)
 */
static void imR2yCalcYyrAddressSdramInput( kuint16 pipeNo )
{
	kulong tmp_top;
	kulong tmp_left;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);
	volatile R2yYyraOfsInfo* gImR2yYyraOfsInfo = im_r2y_utils_get_yyra_ofs_info(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcYyrAddressSdramInput error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	// Setting of offset pixs
	gImR2yYyraOfsInfo[pipeNo].ofsXPixs = gImR2yState[pipeNo].inputSize.imgLeft;
	gImR2yYyraOfsInfo[pipeNo].ofsYPixs = gImR2yState[pipeNo].inputSize.imgTop;

	// Auto calcurate of Overlap width
	switch( gImR2yState[pipeNo].inputDtype ) {
		case ImR2yCtrl_READ_DTYP_PACK12:
			tmp_top  = (gImR2yState[pipeNo].inputGlobal * gImR2yYyraOfsInfo[pipeNo].ofsYPixs);
			tmp_left = (gImR2yYyraOfsInfo[pipeNo].ofsXPixs * 3 / 2);	// x1.5
			break;
		case ImR2yCtrl_READ_DTYP_PACK16:
			tmp_top  = (gImR2yState[pipeNo].inputGlobal * gImR2yYyraOfsInfo[pipeNo].ofsYPixs);
			tmp_left = (gImR2yYyraOfsInfo[pipeNo].ofsXPixs * 2);		// x2.0
			break;
		default:// ImR2yCtrl_READ_DTYP_PACK8
			tmp_top  = (gImR2yState[pipeNo].inputGlobal * gImR2yYyraOfsInfo[pipeNo].ofsYPixs);
			tmp_left = (gImR2yYyraOfsInfo[pipeNo].ofsXPixs);			// x1.0
			break;
	}

	gImR2yYyraOfsInfo[pipeNo].ofsBytes = (tmp_top + tmp_left);
}

/* Set output(YYW) start and pitch registers.
 */
static void imR2ySetOutPitch( kuint16 pipeNo, T_IM_R2Y_OUT_PITCH const r2y_out_pitch[ImR2yCtrl_YYW_CH_MAX] )
{
	UINT32 yywNo;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);


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
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2ySetOutPitch error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_clk_on_pclk(im_r2y_clk_new(), pipeNo);
	for( yywNo = ImR2yCtrl_YYW_CH_0; yywNo < ImR2yCtrl_YYW_CH_MAX - 1; yywNo++ ) {
		switch( yywNo ) {
			default:
				break;
			case ImR2yCtrl_YYW_CH_0:
				if( gImR2yState[pipeNo].yywEnable[yywNo] == ImR2yCtrl_ENABLE_OFF ) {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT = ImR2yCtrl_STA_PIT_1_0;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT = ImR2yCtrl_STA_PIT_1_0;
				}
				else {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA = r2y_out_pitch[yywNo].x_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT = r2y_out_pitch[yywNo].x_pitch;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA = r2y_out_pitch[yywNo].y_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT = r2y_out_pitch[yywNo].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA;
				r2y_out_pitch_temp.x_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT;
				r2y_out_pitch_temp.y_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA;
				r2y_out_pitch_temp.y_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yywNo=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						0,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HSTA.bit.RSZ0HSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ0HPIT.bit.RSZ0HPIT,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VSTA.bit.RSZ0VSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ0VPIT.bit.RSZ0VPIT
						));
#endif
				break;
			case ImR2yCtrl_YYW_CH_1:
				if( gImR2yState[pipeNo].yywEnable[yywNo] == ImR2yCtrl_ENABLE_OFF ) {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT = ImR2yCtrl_STA_PIT_1_0;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT = ImR2yCtrl_STA_PIT_1_0;
				}
				else {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA = r2y_out_pitch[yywNo].x_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT = r2y_out_pitch[yywNo].x_pitch;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA = r2y_out_pitch[yywNo].y_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT = r2y_out_pitch[yywNo].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA;
				r2y_out_pitch_temp.x_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT;
				r2y_out_pitch_temp.y_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA;
				r2y_out_pitch_temp.y_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yywNo=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						1,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HSTA.bit.RSZ1HSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ1HPIT.bit.RSZ1HPIT,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VSTA.bit.RSZ1VSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ1VPIT.bit.RSZ1VPIT
						));
#endif
				break;
			case ImR2yCtrl_YYW_CH_2:
				if( gImR2yState[pipeNo].yywEnable[yywNo] == ImR2yCtrl_ENABLE_OFF ) {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT = ImR2yCtrl_STA_PIT_1_0;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA = 0x00000000;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT = ImR2yCtrl_STA_PIT_1_0;
				}
				else {
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA = r2y_out_pitch[yywNo].x_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT = r2y_out_pitch[yywNo].x_pitch;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA = r2y_out_pitch[yywNo].y_start_pos;
					gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT = r2y_out_pitch[yywNo].y_pitch;
				}
				r2y_out_pitch_temp.x_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA;
				r2y_out_pitch_temp.x_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT;
				r2y_out_pitch_temp.y_start_pos	= gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA;
				r2y_out_pitch_temp.y_pitch		= gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT;
#ifdef IM_R2Y_DEBUG_PRINT
				Ddim_Print(( "imR2ySetOutPitch(): yywNo=%u, hsta=%x, hpit=%x, vsta=%x, vpit=%x\n",
						1,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HSTA.bit.RSZ2HSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ2HPIT.bit.RSZ2HPIT,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VSTA.bit.RSZ2VSTA,
						gImIoR2yRegPtr[pipeNo]->YYW.RSZ2VPIT.bit.RSZ2VPIT
						));
#endif
				break;
		}
		gIM_R2Y_Resize_Param[pipeNo].r2yResizePitch.outputPitch[yywNo].outputXStartPos	= r2y_out_pitch_temp.x_start_pos;
		gIM_R2Y_Resize_Param[pipeNo].r2yResizePitch.outputPitch[yywNo].outputXPitch		= r2y_out_pitch_temp.x_pitch;
		gIM_R2Y_Resize_Param[pipeNo].r2yResizePitch.outputPitch[yywNo].outputYStartPos	= r2y_out_pitch_temp.y_start_pos;
		gIM_R2Y_Resize_Param[pipeNo].r2yResizePitch.outputPitch[yywNo].outputYPitch		= r2y_out_pitch_temp.y_pitch;
	}
	im_r2y_clk_off_pclk(im_r2y_clk_new(), pipeNo);
}


/* Calculate output(YYW) start and pitch value.
 */
static void imR2yCalcOutPitch( kuint16 pipeNo )
{
	UINT32 yywNo;
	kulong  input_width;			// XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX . (32bits)
	kulong  input_lines;			// XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX_XXXX . (32bits)
	kulong  input_calc_width;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  input_calc_lines;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  input_calc_width_l;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  input_calc_lines_l;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  input_calc_width_c;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  input_calc_lines_c;	// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  x_pitch;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  y_pitch;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  x_start;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  y_start;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  x_ref;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	kulong  y_ref;				// XXXX_XXXX_XXXX_XXXX_XX . XX_XXXX_XXXX_XXXX (32bits)
	T_IM_R2Y_OUT_PITCH r2y_out_pitch[ImR2yCtrl_YYW_CH_MAX];
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);


#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcOutPitch error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	if( gImR2yState[pipeNo].yywRectValid != ImR2yCtrl_ENABLE_ON ) {
		return;
	}

	// calc. and set new output size to r2yCtrl(YYW)
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

	input_width = gImR2yState[pipeNo].inputSize.imgWidth
				- gImR2yState[pipeNo].ringPixsInfo.refPixs;
	input_lines = gImR2yState[pipeNo].inputSize.imgLines
				- gImR2yState[pipeNo].ringPixsInfo.refPixs;

	input_calc_width_l = ((kulong)(input_width - 1)) * ImR2yCtrl_STA_PIT_1_0;
	input_calc_lines_l = ((kulong)(input_lines - 1)) * ImR2yCtrl_STA_PIT_1_0;
	input_calc_width_c = ((kulong)(input_width - 2)) * ImR2yCtrl_STA_PIT_1_0 - 1;
	input_calc_lines_c = ((kulong)(input_lines - 2)) * ImR2yCtrl_STA_PIT_1_0 - 1;

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

	for( yywNo = ImR2yCtrl_YYW_CH_0; yywNo < ImR2yCtrl_YYW_CH_MAX - 1; yywNo++ ) {
		if( (input_width == gImR2yState[pipeNo].yywWidth[yywNo])
		 && (input_lines == gImR2yState[pipeNo].yywLines[yywNo])
			) {
			// x1.0 mode (dot by dot mode)
			x_pitch = ImR2yCtrl_STA_PIT_1_0;
			y_pitch = ImR2yCtrl_STA_PIT_1_0;
			x_start = 0;
			y_start = 0;
		}
		else {
			// Resized mode

			switch( yywNo ){
				case ImR2yCtrl_YYW_CH_0:		// FALL THROUGH
				case ImR2yCtrl_YYW_CH_1:
					if( gImR2yState[pipeNo].resizeMode[yywNo] == ImR2yCtrl_RSZ_BICUBIC ){
						input_calc_width = input_calc_width_c;
						input_calc_lines = input_calc_lines_c;
					}
					else{
						input_calc_width = input_calc_width_l;
						input_calc_lines = input_calc_lines_l;
					}
					break;
//				case ImR2yCtrl_YYW_CH_2:
				default:
					input_calc_width = input_calc_width_l;
					input_calc_lines = input_calc_lines_l;
					break;
			}
			x_pitch = (kulong)input_calc_width / (im_r2y_rounddown_2(gImR2yState[pipeNo].yywWidth[yywNo]) - 1);
			y_pitch = (kulong)input_calc_lines / (im_r2y_rounddown_2(gImR2yState[pipeNo].yywLines[yywNo]) - 1);

			// YYW2 is only supported image size reducion
			if( yywNo == ImR2yCtrl_YYW_CH_2 ) {
				if( x_pitch < ImR2yCtrl_STA_PIT_1_0 ) {
#ifdef IM_R2Y_DEBUG_PRINT
					Ddim_Print(( "YYW2 width overflow. pit=%lx\n", x_pitch ));
#endif
					x_pitch = ImR2yCtrl_STA_PIT_1_0;
				}
				if( y_pitch < ImR2yCtrl_STA_PIT_1_0 ) {
#ifdef IM_R2Y_DEBUG_PRINT
					Ddim_Print(( "YYW2 lines overflow. pit=%lx\n", y_pitch ));
#endif
					y_pitch = ImR2yCtrl_STA_PIT_1_0;
				}
			}

			x_ref = (im_r2y_rounddown_2(gImR2yState[pipeNo].yywWidth[yywNo]) - 1) * x_pitch;
			if( input_calc_width < x_ref ) {
				x_start = 0;
			}
			else {
				x_start = input_calc_width - x_ref;
			}
			y_ref = (im_r2y_rounddown_2(gImR2yState[pipeNo].yywLines[yywNo]) - 1) * y_pitch;
			if( input_calc_lines < y_ref ) {
				y_start = 0;
			}
			else {
				y_start = input_calc_lines - y_ref;
			}
		}

		r2y_out_pitch[yywNo].x_start_pos = x_start;
		r2y_out_pitch[yywNo].y_start_pos = y_start;
		r2y_out_pitch[yywNo].x_pitch = x_pitch;
		r2y_out_pitch[yywNo].y_pitch = y_pitch;

#ifdef IM_R2Y_DEBUG_PRINT
#if 1
		{
			kulong width;
			kulong lines;
			Ddim_Print(( "imR2yCalcOutPitch(): yywWidth=%u, yywLines=%u\n",
					gImR2yState[pipeNo].yywWidth[yywNo],
					gImR2yState[pipeNo].yywLines[yywNo]
					));
			Ddim_Print(( "imR2yCalcOutPitch(): yywNo=%u, hsta=%lx, hpit=%lx, vsta=%lx, vpit=%lx\n",
					yywNo,
					x_start,
					x_pitch,
					y_start,
					y_pitch
					));


			if( gImR2yState[pipeNo].yywEnable[yywNo] == ImR2yCtrl_ENABLE_OFF ) {
				continue;
			}

			if( r2y_out_pitch[yywNo].x_pitch != 0 ) {
				width = (input_calc_width - r2y_out_pitch[yywNo].x_start_pos) / (r2y_out_pitch[yywNo].x_pitch) + 1;
			}
			else {
				width = 0;
			}

			if( r2y_out_pitch[yywNo].y_pitch != 0 ) {
				lines = (input_calc_lines - r2y_out_pitch[yywNo].y_start_pos) / (r2y_out_pitch[yywNo].y_pitch) + 1;
			}
			else {
				lines = 0;
			}
			Ddim_Print(( "imR2yCalcOutPitch(): recalc width=%u, line=%u\n", (UINT32)(width), (UINT32)(lines) ));
		}
#endif
#endif
	}

	imR2ySetOutPitch( pipeNo, r2y_out_pitch );
}

/* Calculate input(YYR) width and lines when SDRAM input mode.
 */
static void imR2yCalcInRectSdramInput( kuint16 pipeNo )
{
	kuint16 imgWidth;
	kuint16 imgLines;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "imR2yCalcInRectSdramInput error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return;
	}
#endif	// CO_PARAM_CHECK

	// YYRHSIZ (2pixels alignment & Advancing)
	imgWidth = gImR2yState[pipeNo].inputSize.imgWidth;
	imgWidth = ImR2yUtils_MIN( imgWidth, (kuint16)D_IM_R2Y_YYRHSIZ_MAX );
	imgWidth = ImR2yUtils_MAX( imgWidth, (kuint16)(D_IM_R2Y_YYRHSIZ_MIN + gImR2yState[pipeNo].ringPixsInfo.refPixs) );

	// YYRVSIZ
	imgLines = gImR2yState[pipeNo].inputSize.imgLines;
	imgLines = ImR2yUtils_MIN( imgLines, (kuint16)D_IM_R2Y_YYRVSIZ_MAX );
	imgLines = ImR2yUtils_MAX( imgLines, (kuint16)(D_IM_R2Y_YYRVSIZ_MIN + gImR2yState[pipeNo].ringPixsInfo.refPixs) );

	im_r2y_clk_on_pclk(im_r2y_clk_new(), pipeNo);
	gImIoR2yRegPtr[pipeNo]->YYR.YYRHSIZ.word = imgWidth;
	gImIoR2yRegPtr[pipeNo]->YYR.YYRVSIZ.word = imgLines;
	im_r2y_clk_off_pclk(im_r2y_clk_new(), pipeNo);
}


//TODO 转公有
// Control access enable register.
INT32 im_r2y_set_access_enable(ImR2y2 *self, kuint16 pipeNo, volatile R2yAccessEnableManage* const acc_en_mng, const kuint16 acc_enable, const kuint16 wait_enable, const CHAR errmsg[] )
{
	INT32 ret = D_DDIM_OK;
	kuint16 cnt;
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		cnt = acc_en_mng->ctrlCnt[loop_cnt];
		if( acc_enable == 0 ) {
			if( cnt != 0 ) {
				cnt--;
				if( cnt == 0 ) {
					if( im_r2y_yyw_is_activated( loop_cnt ) ) {
						// Macro busy error
						Ddim_Assertion(( errmsg ));
						ret = ImR2yUtils_MACRO_BUSY;
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
					ret = ImR2yUtils_MACRO_BUSY;
				}
				else{
					cnt++;
					acc_en_mng->reg_set_func( loop_cnt, 1 );

					if( wait_enable != ImR2yCtrl_WAIT_OFF ) {
						im_r2y_wait_usec( ImR2yUtils_SRAM_WAIT_USEC );
					}
				}
			}
			else if((0 < cnt) && (cnt < 255)) {
				cnt++;
			}
		}
		acc_en_mng->ctrlCnt[loop_cnt] = cnt;
	}

	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );

	return ret;
}

void im_r2y2_loop_set(ImR2y2 *self, kuint16 loop_cnt)
{
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK0STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK0 + 1 );
	gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANKASTS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANKA + 1 );
	gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK1STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK1 + 1 );
	gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS = im_r2y_inc_bank_index( gImIoR2yRegPtr[loop_cnt]->YYW.YYWBANK.bit.BANK2STS, gImIoR2yRegPtr[loop_cnt]->YYW.YYWCTL.bit.USEBANK2 + 1 );

}

void im_r2y2_sta_manage_init(ImR2y2 *self, kuint16 pipeNo, kuint16 size_coef)
{
	// initialize of Resize information
			memset( (kuint16*)&gIM_R2Y_Resize_Param[pipeNo], 0, sizeof(R2yResizeParam) * size_coef );
}

/* Set YYW parameter hold
 */
INT32 im_r2y2_set_yyw_param_hold(ImR2y2 *self, kuint16 pipeNo, kuint16 hold_enable )
{
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_yyw_param_hold error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	Dd_ARM_Critical_Section_Start(gOsUsr_Spin_Lock);
	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		if( hold_enable == 0 ) {
			if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] != 0 ) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]--;
				if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] == 0 ) {
					gImIoR2yRegPtr[loop_cnt]->YYW.YYWKPP.bit.YYWKPP = 0;
				}
			}
		}
		else {
			if( gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] == 0 ) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]++;
				gImIoR2yRegPtr[loop_cnt]->YYW.YYWKPP.bit.YYWKPP = 1;
			}
			else if((0 < gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]) && (gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt] < 255)) {
				gim_r2y_yyw_param_hold_ctrl_cnt[loop_cnt]++;
			}
		}
	}
	Dd_ARM_Critical_Section_End(gOsUsr_Spin_Lock);
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y resize rectangle Control
 */
INT32 im_r2y2_set_resize_rect(ImR2y2 *self, kuint16 pipeNo, const R2yResizeRect* const r2y_resize_param )
{
	UINT32 yywNo;
	kuint16 loop_cnt, loop_sta, loop_end;
	kuint16 div_0a;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2y_resize_param == NULL) {
		Ddim_Assertion(("im_r2y2_set_resize_rect error. r2y_resize_param = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_resize_rect error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		gImR2yState[loop_cnt].inputSize = r2y_resize_param->inputSize;
		gImR2yState[loop_cnt].inputSize.imgWidth = im_r2y_rounddown_2(gImR2yState[loop_cnt].inputSize.imgWidth);
		gIM_R2Y_Resize_Param[pipeNo].r2yResizePitch.inputSize = gImR2yState[loop_cnt].inputSize;	/* pgr0869 */

		for( yywNo = ImR2yCtrl_YYW_CH_0; yywNo < ImR2yCtrl_YYW_CH_MAX-1; yywNo++ ) {
			gImR2yState[loop_cnt].yywWidth[yywNo] = r2y_resize_param->outputSize[yywNo].yywWidth;
			gImR2yState[loop_cnt].yywLines[yywNo] = r2y_resize_param->outputSize[yywNo].yywLines;
		}

		gImR2yState[loop_cnt].yywRectValid = ImR2yCtrl_ENABLE_ON;

		if( gImR2yState[loop_cnt].videoPhotoMode == ImR2yUtils_MODE_SDRAM_INPUT ) {
			imR2yCalcYyrAddressSdramInput( loop_cnt );
			imR2yCalcInRectSdramInput( loop_cnt );
			imR2yCalcTopMsbOffsetSdramInput( loop_cnt );
		}
		imR2yCalcOutPitch( loop_cnt );
	}

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		for( yywNo = ImR2yCtrl_YYW_CH_0; yywNo < ImR2yCtrl_YYW_CH_MAX; yywNo++ ) {
			if( yywNo < ImR2yCtrl_YYW_CH_MAX - 1 ){
				if( gImR2yState[loop_cnt].yywEnable[yywNo] == ImR2yCtrl_ENABLE_ON ) {	/* pgr0013 pgr0862 */
					if( gImR2yState[loop_cnt].pixAvgReductEn[yywNo] == ImR2yCtrl_ENABLE_ON ) {	/* pgr0013 pgr0862 */
						gImR2yState[loop_cnt].yywWidth[yywNo] = (r2y_resize_param->outputSize[yywNo].yywWidth / 2^(gImR2yState[loop_cnt].pixAvgReductMode[yywNo] + 1)) & 0x1FFE;	/* pgr0013 pgr0862 */
						gImR2yState[loop_cnt].yywLines[yywNo] = (r2y_resize_param->outputSize[yywNo].yywLines / 2^(gImR2yState[loop_cnt].pixAvgReductMode[yywNo] + 1)) & 0x1FFE;	/* pgr0013 pgr0862 */
					}
				}
			}
			gIM_R2Y_Resize_Param[loop_cnt].r2yResizePitch.outputPitch[yywNo].outputGlobalW[ImR2yCtrl_PORT_0]	= r2y_resize_param->outputSize[yywNo].outputGlobalW[ImR2yCtrl_PORT_0];
			gIM_R2Y_Resize_Param[loop_cnt].r2yResizePitch.outputPitch[yywNo].outputGlobalW[ImR2yCtrl_PORT_1]	= r2y_resize_param->outputSize[yywNo].outputGlobalW[ImR2yCtrl_PORT_1];
			gIM_R2Y_Resize_Param[loop_cnt].r2yResizePitch.outputPitch[yywNo].outputGlobalW[ImR2yCtrl_PORT_2]	= r2y_resize_param->outputSize[yywNo].outputGlobalW[ImR2yCtrl_PORT_2];
		}

		if( gImR2yState[loop_cnt].yywEnable[ImR2yCtrl_YYW_CH_0] == ImR2yCtrl_ENABLE_ON && gImR2yState[loop_cnt].outputMode0a != ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP ) {
			switch( gImR2yState[loop_cnt].outputMode0a ){
				case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_4_Y:
					div_0a = 4;
					break;
				case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_8_Y:
					div_0a = 8;
					break;
				case ImR2yCtrl_YYW0A_OUTPUT_MODE_DIV_32_SP:
					div_0a = 32;
					break;
//				case ImR2yCtrl_YYW0A_OUTPUT_MODE_STOP:
				default:
					div_0a = 1;
					break;
			}

			if( gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0] % div_0a ){
				gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0A] = gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0] / div_0a + 1;
			}
			else{
				gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0A] = gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0] / div_0a;
			}
			if( gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0] % div_0a ){
				gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0A] = gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0] / div_0a + 1;
			}
			else{
				gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0A] = gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0] / div_0a;
			}
			gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0A] = ( gImR2yState[loop_cnt].yywWidth[ImR2yCtrl_YYW_CH_0A] + 1 ) & 0x1FFE;
			gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0A] = ( gImR2yState[loop_cnt].yywLines[ImR2yCtrl_YYW_CH_0A] + 1 ) & 0x1FFE;
		}

		gIM_R2Y_Resize_Param[loop_cnt].resizeSelect = 0;
		gIM_R2Y_Resize_Param[loop_cnt].r2yResizeRect = *r2y_resize_param;
		gIM_R2Y_Resize_Param[loop_cnt].resizeSelect = 1;
	}

	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_0, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_1, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_0, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_1, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.YYW2DEF, union io_r2y_yyw2def, YYW2DEF, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.YYWADEF, union io_r2y_yywadef, YYWADEF, r2y_resize_param->outputSize[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_0] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return D_DDIM_OK;
}

/* R2Y resize pitch Control
 */
INT32 im_r2y2_set_resize_pitch(ImR2y2 *self, kuint16 pipeNo, const R2yResizePitch* const r2yResizePitch )
{
	UINT32 yywNo;
	T_IM_R2Y_OUT_PITCH r2y_out_pitch[ImR2yCtrl_YYW_CH_MAX];
	UINT32 outputXPitch;
	UINT32 outputYPitch;
	INT32 ercd = D_DDIM_OK;
	kuint16 loop_cnt, loop_sta, loop_end;
	ImR2yUtils* imR2yUtils = im_r2y_utils_get();
	volatile struct io_r2y** gImIoR2yRegPtr = im_r2y_utils_get_io_reg(imR2yUtils);
	volatile R2yStateMng* gImR2yState = im_r2y_utils_get_state_mng(imR2yUtils);

#ifdef CO_PARAM_CHECK
	if(r2yResizePitch == NULL) {
		// Parameter setting error
		Ddim_Assertion(("im_r2y2_set_resize_pitch error. r2yResizePitch = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo > ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_set_resize_pitch error. pipeNo>ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	im_r2y_utils_get_loop_val(imR2yUtils, pipeNo, &loop_sta, &loop_end );

	for( loop_cnt = loop_sta; loop_cnt <= loop_end; loop_cnt++ ){
		// set new rectangle to gImR2yState
		gImR2yState[loop_cnt].inputSize = r2yResizePitch->inputSize;

		gImR2yState[loop_cnt].yywRectValid = ImR2yCtrl_ENABLE_OFF;

		if( gImR2yState[loop_cnt].videoPhotoMode == ImR2yUtils_MODE_DIRECT ) {
		}
		else {
			imR2yCalcYyrAddressSdramInput( loop_cnt );
			imR2yCalcInRectSdramInput( loop_cnt );
			imR2yCalcTopMsbOffsetSdramInput( loop_cnt );
		}

		for( yywNo = ImR2yCtrl_YYW_CH_0; yywNo < ImR2yCtrl_YYW_CH_MAX-1; yywNo++ ) {
			outputXPitch = r2yResizePitch->outputPitch[yywNo].outputXPitch;
			outputYPitch = r2yResizePitch->outputPitch[yywNo].outputYPitch;
			if( yywNo == ImR2yCtrl_YYW_CH_2 ) {
				if( outputXPitch < ImR2yCtrl_STA_PIT_1_0 ) {
					Ddim_Print(( "YYW2 width overflow. %x\n", outputXPitch ));
					outputXPitch = ImR2yCtrl_STA_PIT_1_0;
					ercd = ImR2yUtils_PARAM_ERROR;
				}
				if( outputYPitch < ImR2yCtrl_STA_PIT_1_0 ) {
					Ddim_Print(( "YYW2 lines overflow. %x\n", outputYPitch ));
					outputYPitch = ImR2yCtrl_STA_PIT_1_0;
					ercd = ImR2yUtils_PARAM_ERROR;
				}
			}

			r2y_out_pitch[yywNo].x_start_pos = r2yResizePitch->outputPitch[yywNo].outputXStartPos;
			r2y_out_pitch[yywNo].y_start_pos = r2yResizePitch->outputPitch[yywNo].outputYStartPos;
			r2y_out_pitch[yywNo].x_pitch = outputXPitch;
			r2y_out_pitch[yywNo].y_pitch = outputYPitch;
#ifdef IM_R2Y_DEBUG_PRINT
			Ddim_Print(( "im_r2y2_set_resize_pitch(): yywNo=%u, hsta=%lx, hpit=%lx, vsta=%lx, vpit=%lx\n",
						 yywNo,
						 r2y_out_pitch[yywNo].x_start_pos,
						 r2y_out_pitch[yywNo].x_pitch,
						 r2y_out_pitch[yywNo].y_start_pos,
						 r2y_out_pitch[yywNo].y_pitch
						 ));
#endif
		}
		imR2ySetOutPitch( loop_cnt, r2y_out_pitch );

		gIM_R2Y_Resize_Param[loop_cnt].resizeSelect = 0;
		gIM_R2Y_Resize_Param[loop_cnt].r2yResizePitch = *r2yResizePitch;
		gIM_R2Y_Resize_Param[loop_cnt].resizeSelect = 2;
	}

	// It sets it to the register at once.
	im_r2y_clk_on_pclk(im_r2y_clk_new(),  pipeNo );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_0, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW0DEF, union io_r2y_yyw0def, YYW0DEF_1, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_0].outputGlobalW[ImR2yCtrl_PORT_1] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_0, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED_A( gImIoR2yRegPtr[pipeNo]->YYW.YYW1DEF, union io_r2y_yyw1def, YYW1DEF_1, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_1].outputGlobalW[ImR2yCtrl_PORT_1] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.YYW2DEF, union io_r2y_yyw2def, YYW2DEF, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_2].outputGlobalW[ImR2yCtrl_PORT_0] );
	imR2yUtils_SET_REG_SIGNED( gImIoR2yRegPtr[pipeNo]->YYW.YYWADEF, union io_r2y_yywadef, YYWADEF, r2yResizePitch->outputPitch[ImR2yCtrl_YYW_CH_0A].outputGlobalW[ImR2yCtrl_PORT_0] );
	im_r2y_clk_off_pclk(im_r2y_clk_new(),  pipeNo );
	Im_R2Y_Dsb();

	return ercd;
}

/* R2Y get resize rectangle Control information.
 */
INT32 im_r2y2_get_resize_param(ImR2y2 *self, kuint16 pipeNo, R2yResizeParam* const r2y_resize_param )
{
#ifdef CO_PARAM_CHECK
	if( r2y_resize_param == NULL ) {
		Ddim_Assertion(("im_r2y2_get_resize_param error. r2y_resize_param = NULL\n"));
		return ImR2yUtils_PARAM_ERROR;
	}
	if( pipeNo >= ImR2yCtrl_PIPE12 ){
		Ddim_Assertion(( "im_r2y2_get_resize_param error. pipeNo>=ImR2yCtrl_PIPE12\n" ));
		return ImR2yUtils_PARAM_ERROR;
	}
#endif

	*r2y_resize_param = gIM_R2Y_Resize_Param[pipeNo];

	return D_DDIM_OK;
}

ImR2y2 *im_r2y2_new(void)
{
	ImR2y2* self = k_object_new_with_private(IM_TYPE_R2Y2,sizeof(ImR2y2Private));
	return self;
}
