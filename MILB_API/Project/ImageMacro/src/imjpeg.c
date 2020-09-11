/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-08
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/

#include <string.h>
#include "ddtop.h"
#include "ddimusercustom.h"
#include "jdsjp7.h"
#include "jdsimg.h"
#include "imjpeg.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImJpeg, im_jpeg);
#define IM_JPEG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImJpegPrivate, IM_TYPE_JPEG))


struct _ImJpegPrivate
{
	kint a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// quantization table for the next frame
static TimgQuatTblPack S_GIM_JPEG_NEXT_FRAME_QUANT_TBL;
static volatile kuchar S_GIM_JPEG_UPDATE_QUANT_FLG = 0;

// encode setting table
static TimgEncMng S_GIM_JPEG_ENC_MNG;

// decode setting table
static TimgDecMng S_GIM_JPEG_DEC_MNG;
static TimgDecFrameMng S_GIM_JPEG_DEC_FRAME_MNG;

// Clock control counter (0~255)
#ifdef ImJpegCommon_CO_ACT_JPEG_CLOCK
volatile kuchar gImJpgClkCtrlCnt = 0;
#endif // ImJpegCommon_CO_ACT_JPEG_CLOCK
#ifdef ImJpegCommon_CO_ACT_JPEG_HCLOCK
volatile kuchar gImJpgHclkCtrlCnt = 0;
#endif // ImJpegCommon_CO_ACT_JPEG_HCLOCK
#ifdef ImJpegCommon_CO_ACT_JPEG_ICLOCK
volatile kuchar gImJpgIclkCtrlCnt = 0;
#endif // ImJpegCommon_CO_ACT_JPEG_ICLOCK

static kint32 S_GIM_JPEG_RESULT_JUDGE = 0;

/********************************************************/
/* Default Quantization Table							*/
/********************************************************/
// for Y
static const TimgQuatTbl S_GDEFAULT_QUANTIZE_TBL_LUMA = {
	{	0x10, 0x0B, 0x0A, 0x10, 0x18, 0x28, 0x33, 0x3D,
		0x0C, 0x0C, 0x0E, 0x13, 0x1A, 0x3A, 0x3C, 0x37,
		0x0E, 0x0D, 0x10, 0x18, 0x28, 0x39, 0x45, 0x38,
		0x0E, 0x11, 0x16, 0x1D, 0x33, 0x57, 0x50, 0x3E,
		0x12, 0x16, 0x25, 0x38, 0x44, 0x6D, 0x67, 0x4D,
		0x18, 0x23, 0x37, 0x40, 0x51, 0x68, 0x71, 0x5C,
		0x31, 0x40, 0x4E, 0x57, 0x67, 0x79, 0x78, 0x65,
		0x48, 0x5C, 0x5F, 0x62, 0x70, 0x64, 0x67, 0x63	}
};

// for Cb/Cr
static const TimgQuatTbl S_GDEFAULT_QUANTIZE_TBL_CHROMA = {
	{	0x11, 0x12, 0x18, 0x2F, 0x63, 0x63, 0x63, 0x63,
		0x12, 0x15, 0x1A, 0x42, 0x63, 0x63, 0x63, 0x63,
		0x18, 0x1A, 0x38, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x2F, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
		0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63	}
};
/**
 *IMPL
 */
static void im_jpeg_constructor(ImJpeg *self)
{
//	ImJpegPrivate *priv = IM_JPEG_GET_PRIVATE(self);
}

static void im_jpeg_destructor(ImJpeg *self)
{
//	ImJpegPrivate *priv = IM_JPEG_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/*----------------------------------------------------------------------	*/
/* Function																		*/
/*----------------------------------------------------------------------	*/
/**
 * @brief		the Jpeg clock on.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_on_clk(ImJpeg*self)
{
#ifdef ImJpegCommon_CO_ACT_JPEG_CLOCK
	Dd_Top_Start_Clock((kuchar*) &gImJpgClkCtrlCnt, ImJpegCommon_D_IM_JPEG_CLK_REG_ADDR, ~ImJpegCommon_D_IM_JPEG_CLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_CLOCK
}

/**
 * @brief		the Jpeg clock off.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_off_clk(ImJpeg*self)
{
#ifdef ImJpegCommon_CO_ACT_JPEG_CLOCK
	Dd_Top_Stop_Clock((kuchar*) &gImJpgClkCtrlCnt, ImJpegCommon_D_IM_JPEG_CLK_REG_ADDR, ImJpegCommon_D_IM_JPEG_CLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_CLOCK
}

/**
 * @brief		the AHB bus clock off.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_on_hclk(ImJpeg*self)
{
#ifdef ImJpegCommon_CO_ACT_JPEG_HCLOCK
	Dd_Top_Start_Clock((kuchar*) &gImJpgHclkCtrlCnt, ImJpegCommon_D_IM_JPEG_HCLK_REG_ADDR, ~ImJpegCommon_D_IM_JPEG_HCLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_HCLOCK
}

/**
 * @brief		the AHB bus clock on.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_off_hclk(ImJpeg*self)
{
#ifdef ImJpegCommon_CO_ACT_JPEG_HCLOCK
	Dd_Top_Stop_Clock((kuchar*) &gImJpgHclkCtrlCnt, ImJpegCommon_D_IM_JPEG_HCLK_REG_ADDR, ImJpegCommon_D_IM_JPEG_HCLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_HCLOCK
}

/**
 * @brief  the AXI bus clock on.
 * @param[in]	None
 * @param[out]	None
 * @return None
 */
void im_jpeg_on_iclk( ImJpeg*self )
{
#ifdef ImJpegCommon_CO_ACT_JPEG_ICLOCK
	Dd_Top_Start_Clock((kuchar*) &gImJpgIclkCtrlCnt, ImJpegCommon_D_IM_JPEG_ICLK_REG_ADDR, ~ImJpegCommon_D_IM_JPEG_ICLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_ICLOCK
}

/**
 * @brief  the AXI bus clock off.
 * @param[in]	None
 * @param[out]	None
 * @return None
 */
void im_jpeg_off_iclk( ImJpeg*self )
{
#ifdef ImJpegCommon_CO_ACT_JPEG_ICLOCK
	Dd_Top_Stop_Clock((kuchar*) &gImJpgIclkCtrlCnt, ImJpegCommon_D_IM_JPEG_ICLK_REG_ADDR, ImJpegCommon_D_IM_JPEG_ICLK_BIT);
#endif	// ImJpegCommon_CO_ACT_JPEG_ICLOCK
}

/**
 * @brief  Jpeg macro reset for stop.
 * @param[in]	None
 * @param[out]	None
 * @return None
 */
void im_jpeg_reset( ImJpeg*self )
{
	// trriger off
	ioJpg7.jictl.bit.jitrg = 0;
	ioJpg7.jcctl.bit.jctrg = 0;

	// reset
	ioJpg7.jpcmd.bit.jreset = 1;

	ImJpegCommon_IM_JPEG_DSB();

#ifdef CO_IM_JPEG_DEBUG
	Ddim_Print(("ioJpg7.jstate.bit.jallrstp =[0x%X]\n", ioJpg7.jstate.bit.jallrstp));
#endif

	while (ioJpg7.jstate.bit.jallrstp == 1) {
		;	// during reset
#ifdef CO_DEBUG_ON_PC
		ioJpg7.jstate.bit.jallrstp = 0;
#endif
	}
}

/**
 * @brief  Set JPEG Quantization table.
 * @param  TimgQuatTblPack* pQuantTbl :Pointer to Quantization Table
 * @return NONE
 */
void im_jpeg_set_quant_tbl(ImJpeg*self, TimgQuatTblPack* pQuantTbl )
{
	kint32 i, index;
	// HCLK on
	im_jpeg_on_hclk(NULL);

	// QTTBL SRAM power down off.
	ioImg.srampd.bit.jpegpd &= ~0x8;

	ImJpegCommon_IM_JPEG_DSB();

	// QTTBL SRAM power down control wait time.
	Dd_ARM_Wait_ns(1000);

	if (pQuantTbl == NULL) {
		// Quantization table No.0 for Y
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt0.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index] << 24)
				| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 1] << 16) | (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 2] << 8)
				| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 3]));
			index = index + 4;
		}
		// Quantization table No.1 for CbCr
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt1.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index] << 24)
				| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 1] << 16)
				| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 2] << 8) | (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 3]));
			index = index + 4;
		}
		// Quantization table No.2 for Y
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt2.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index] << 24)
				| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 1] << 16) | (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 2] << 8)
				| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 3]));
			index = index + 4;
		}
		// Quantization table No.3 for CbCr
		for (i = 0, index = 0; i < 16; i++) {
			ioJpg7.jpqt3.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index] << 24)
				| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 1] << 16)
				| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 2] << 8) | (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 3]));
			index = index + 4;
		}
	}
	else {

		if (pQuantTbl->quantizationTbl0 != NULL) {
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt0.word[i] = ((pQuantTbl->quantizationTbl0->quantValue[index] << 24)
					| (pQuantTbl->quantizationTbl0->quantValue[index + 1] << 16)
					| (pQuantTbl->quantizationTbl0->quantValue[index + 2] << 8)
					| (pQuantTbl->quantizationTbl0->quantValue[index + 3]));
				index = index + 4;
			}
		}
		else {
			// Quantization table No.0 for Y
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt0.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index] << 24)
					| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 1] << 16)
					| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 2] << 8) | (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 3]));
				index = index + 4;
			}
		}

		if (pQuantTbl->quantizationTbl1 != NULL) {
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt1.word[i] = ((pQuantTbl->quantizationTbl1->quantValue[index] << 24)
					| (pQuantTbl->quantizationTbl1->quantValue[index + 1] << 16)
					| (pQuantTbl->quantizationTbl1->quantValue[index + 2] << 8)
					| (pQuantTbl->quantizationTbl1->quantValue[index + 3]));
				index = index + 4;
			}
		}
		else {
			// Quantization table No.1 for CbCr
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt1.word[i] =
					((S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index] << 24)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 1] << 16)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 2] << 8)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 3]));
				index = index + 4;
			}
		}

		if (pQuantTbl->quantizationTbl2 != NULL) {
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt2.word[i] = ((pQuantTbl->quantizationTbl2->quantValue[index] << 24)
					| (pQuantTbl->quantizationTbl2->quantValue[index + 1] << 16)
					| (pQuantTbl->quantizationTbl2->quantValue[index + 2] << 8)
					| (pQuantTbl->quantizationTbl2->quantValue[index + 3]));
				index = index + 4;
			}
		}
		else {
			// Quantization table No.2 for Y
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt2.word[i] = ((S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index] << 24)
					| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 1] << 16)
					| (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 2] << 8) | (S_GDEFAULT_QUANTIZE_TBL_LUMA.quantValue[index + 3]));
				index = index + 4;
			}
		}

		if (pQuantTbl->quantizationTbl3 != NULL) {
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt3.word[i] = ((pQuantTbl->quantizationTbl3->quantValue[index] << 24)
					| (pQuantTbl->quantizationTbl3->quantValue[index + 1] << 16)
					| (pQuantTbl->quantizationTbl3->quantValue[index + 2] << 8)
					| (pQuantTbl->quantizationTbl3->quantValue[index + 3]));
				index = index + 4;
			}
		}
		else {
			// Quantization table No.3 for CbCr
			for (i = 0, index = 0; i < 16; i++) {
				ioJpg7.jpqt3.word[i] =
					((S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index] << 24)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 1] << 16)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 2] << 8)
						| (S_GDEFAULT_QUANTIZE_TBL_CHROMA.quantValue[index + 3]));
				index = index + 4;
			}
		}
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	return;
}

/**
 * @brief  Set JPEG Next Quantization table.
 * @param  TimgQuatTblPack* pQuantTbl :Pointer to Next Quantization Table
 * @return NONE
 */
void im_jpeg_set_next_quant_tbl(ImJpeg*self, TimgQuatTblPack* pQuantTbl )
{
	if (pQuantTbl == NULL) {
		// Set default table
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_LUMA;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_CHROMA;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_LUMA;
		S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_CHROMA;
	}
	else {
		if (pQuantTbl->quantizationTbl0 != NULL) {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0 = pQuantTbl->quantizationTbl0;
		}
		else {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_LUMA;
		}
		if (pQuantTbl->quantizationTbl1 != NULL) {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1 = pQuantTbl->quantizationTbl1;
		}
		else {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_CHROMA;
		}
		if (pQuantTbl->quantizationTbl2 != NULL) {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2 = pQuantTbl->quantizationTbl2;
		}
		else {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_LUMA;
		}
		if (pQuantTbl->quantizationTbl3 != NULL) {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3 = pQuantTbl->quantizationTbl3;
		}
		else {
			S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3 = (TimgQuatTbl*) &S_GDEFAULT_QUANTIZE_TBL_CHROMA;
		}
	}

#ifdef CO_IM_JPEG_DEBUG
	kuchar i;
	for ( i=0; i < 64; i++ ) {
		Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl0->quantValue[i]));
	}
	for ( i=0; i < 64; i++ ) {
		Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl1->quantValue[i]));
	}
	for ( i=0; i < 64; i++ ) {
		Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl2->quantValue[i]));
	}
	for ( i=0; i < 64; i++ ) {
		Ddim_Print(("S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3.quantValue[%d]=0x%X\n", i,
				S_GIM_JPEG_NEXT_FRAME_QUANT_TBL.quantizationTbl3->quantValue[i]));
	}
#endif

	return;
}

/**
 * @brief  interrupt handler for QTWINT.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return None
 */
void im_jpeg_sub_int_handler_enc_core_qtwint(ImJpeg*self, kint32* result )
{
	// Check update enable
	if (ioJpg7.jpintsta.bit.qtwint == 1) {
		if (S_GIM_JPEG_UPDATE_QUANT_FLG) {
			// Set quantize table
			im_jpeg_set_quant_tbl(NULL, &S_GIM_JPEG_NEXT_FRAME_QUANT_TBL);
			// Flag clear
			S_GIM_JPEG_UPDATE_QUANT_FLG = 0;
		}
		// QTWINT bit clear
		ioJpg7.jpintsta.bit.qtwint = 0;

		// Set result
		*result |= ImJpegCommon_D_IM_JPEG_QTWINT;

	}

	return;
}

/**
 * @brief  Encode normal end handler.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return None
 */
void im_jpeg_sub_int_handler_enc_core_end(ImJpeg*self, kint32* result )
{
	// Normal end
	if (ioJpg7.jpintsta.bit.intflg == 1) {
		// INTFLG bit clear
		ioJpg7.jpintsta.bit.intflg = 0;
	}

	// Write code size
	// Count value of compression volume of data
	S_GIM_JPEG_ENC_MNG.codeSize = ioJpg7.jpbytcnt.word;

	// Set result
	*result |= ImJpegCommon_D_IM_JPEG_NML_END;
	S_GIM_JPEG_RESULT_JUDGE |= ImJpegCommon_D_IM_JPEG_NML_END;

	return;
}

/**
 * @brief  Decode err handler.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return None
 */
void im_jpeg_sub_int_handler_dec_core_errint(ImJpeg*self, kint32* result )
{
	kint32 res = 0;

	// get error code
	S_GIM_JPEG_DEC_MNG.errCode = ioJpg7.jperrcod.bit.jperrcod;

	if ( ioJpg7.jpintsta.bit.errflg != 0 ) {
		res |= ImJpegCommon_D_IM_JPEG_ERR;
	}

	// Status clear
	ioJpg7.jpintsta.word = 0x00000000;

	// Set result
	*result |= res;

	// Error reset
	im_jpeg_reset(NULL);

	return;
}

/**
 * @brief  interrupt handler for REGRDINT.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return	kint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_DECODE_ERR
 */
kint32 im_jpeg_sub_int_handler_dec_core_regrdint(ImJpeg*self, kint32* result )
{
	kushort width;
	kushort lines;

	if (ioJpg7.jpintsta.bit.regrdint == 1) {
		// REGRDINT bit clear
		ioJpg7.jpintsta.bit.regrdint = 0;
	}

	// Set result
	*result |= ImJpegCommon_D_IM_JPEG_REGRDINT;

	// Get the target image size
	S_GIM_JPEG_DEC_MNG.orgWidth = ioJpg7.jpwidth.bit.jpwidth;

	if (ioJpg7.jpdnlset.bit.jpdnlset == 0) {
		S_GIM_JPEG_DEC_MNG.orgLines = ioJpg7.jpheight.bit.jpheight;
	}
	else {
		// set DNL line value
		S_GIM_JPEG_DEC_MNG.orgLines = ioJpg7.jpdnlset.bit.jpdnlset;
	}

	// Check sampling type
	if (S_GIM_JPEG_DEC_MNG.smplType != (EimgSmplType) ioJpg7.jpmode.bit.mmode) {
		S_GIM_JPEG_DEC_MNG.smplType = (EimgSmplType) ioJpg7.jpmode.bit.mmode;
		// Set result
		*result |= ImJpegCommon_D_IM_JPEG_SMPL_TYPE_NG;
		// Error reset
		im_jpeg_reset(NULL);

		return ImJpegCommon_D_IM_JPEG_DECODE_ERR;

	}

	// Cutout enable check
	if (S_GIM_JPEG_DEC_FRAME_MNG.cutoutFlg) {
		if (S_GIM_JPEG_DEC_MNG.smplType == ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420) {
			// Set result
			*result |= ImJpegCommon_D_IM_JPEG_CUTOUT_ERR;
			// Error reset
			im_jpeg_reset(NULL);

			return ImJpegCommon_D_IM_JPEG_DECODE_ERR;
		}
	}

#ifdef CO_IM_JPEG_DEBUG
	Ddim_Print(("ioJpg7.JPWIDTH.bit.JPWIDTH.   =[%d]\n", ioJpg7.JPWIDTH.bit.JPWIDTH));
	Ddim_Print(("ioJpg7.JPHEIGHT.bit.JPHEIGHT. =[%d]\n", ioJpg7.JPHEIGHT.bit.JPHEIGHT));
	Ddim_Print(("ioJpg7.JPDNLSET.bit.JPDNLSET. =[%d]\n", ioJpg7.JPDNLSET.bit.JPDNLSET));
	Ddim_Print(("ioJpg7.JPMODE.bit.MMODE.      =[0x%X]\n", ioJpg7.JPMODE.bit.MMODE));
#endif

	width = S_GIM_JPEG_DEC_MNG.orgWidth;

	if ((width & 0x01) != 0) {
		if (S_GIM_JPEG_DEC_MNG.smplType == ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC422 ||
			S_GIM_JPEG_DEC_MNG.smplType == ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420) {
			// 2pix unit
			width = (kushort) (((width >> 1) << 1) + 2);
		}
	}

	lines = S_GIM_JPEG_DEC_MNG.orgLines;

	if ((lines & 0x01) != 0) {
		if (S_GIM_JPEG_DEC_MNG.smplType == ImJpegCommon_E_IM_JPEG_SMPL_TYPE_YCC420) {
			// 2lines unit
			lines = (kushort) (((lines >> 1) << 1) + 2);
		}
	}

	if (S_GIM_JPEG_DEC_FRAME_MNG.cutoutFlg) {
		ioJpg7.jimgshdg.bit.jimgshdg = width;
		ioJpg7.jimgsh.bit.jimgsh = S_GIM_JPEG_DEC_FRAME_MNG.cutoutWidth;
		ioJpg7.jimgsv.bit.jimgsv = S_GIM_JPEG_DEC_FRAME_MNG.cutoutLines;
		ioJpg7.jhoffset.bit.jhoffset = S_GIM_JPEG_DEC_FRAME_MNG.cutoutOffsetH;
		ioJpg7.jvoffset.bit.jvoffset = S_GIM_JPEG_DEC_FRAME_MNG.cutoutOffsetV;
	}
	else {
		ioJpg7.jimgsh.bit.jimgsh = width;
		ioJpg7.jimgsv.bit.jimgsv = lines;
		ioJpg7.jimgshdg.bit.jimgshdg = 0;
		ioJpg7.jhoffset.bit.jhoffset = 0;
		ioJpg7.jvoffset.bit.jvoffset = 0;
	}

	// Set the frame memory
	ioJpg7.jimgygh.bit.jimgygh = S_GIM_JPEG_DEC_FRAME_MNG.globalYWidth;
	ioJpg7.jimgcgh.bit.jimgcgh = S_GIM_JPEG_DEC_FRAME_MNG.globalCWidth;

#ifdef CO_IM_JPEG_DEBUG
	Ddim_Print(("ioJpg7.jimgygh  =[%ld]\n", ioJpg7.jimgygh.word));
	Ddim_Print(("ioJpg7.jimgcgh  =[%ld]\n", ioJpg7.jimgcgh.word));
	Ddim_Print(("ioJpg7.jimgshdg =[%ld]\n", ioJpg7.jimgshdg.word));
	Ddim_Print(("ioJpg7.jimgsh   =[%ld]\n", ioJpg7.jimgsh.word));
	Ddim_Print(("ioJpg7.jimgsv   =[%ld]\n", ioJpg7.jimgsv.word));
	Ddim_Print(("ioJpg7.jhoffset =[%ld]\n", ioJpg7.jhoffset.word));
	Ddim_Print(("ioJpg7.jvoffset =[%ld]\n", ioJpg7.jvoffset.word));
#endif

	// PBUF start
	ioJpg7.jictl.bit.jitrg = 1;

	if (ioJpg7.jpsuspend.bit.jpsuspend) {
		// during suspend
		// Core restart
		ioJpg7.jpcmd.bit.jrstart = 1;
	}

	ImJpegCommon_IM_JPEG_DSB();

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief  Decode normal end.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return	None
 */
void im_jpeg_sub_int_handler_dec_core_end(ImJpeg*self, kint32* result )
{
	kint32 res = 0;

	// correction process end
	if (ioJpg7.jpintsta.bit.corend == 1) {
		// bit clear
		ioJpg7.jpintsta.bit.corend = 0;

		if (ioJpg7.jpcorsta.bit.corsizinfo == 1) {
			// Set result
			res |= ImJpegCommon_D_IM_JPEG_CORSIZINFO;
		}
		if (ioJpg7.jpcorsta.bit.cordriinfo == 1) {
			// Set result
			res |= ImJpegCommon_D_IM_JPEG_CORDRIINFO;
		}

		if (ioJpg7.jpintsta.bit.intflg == 1) {
			// INTFLG bit clear
			ioJpg7.jpintsta.bit.intflg = 0;
		}

		// Set result
		res |= ImJpegCommon_D_IM_JPEG_CORRECT_END;
	}
	else {
		// Normal end
		if (ioJpg7.jpintsta.bit.intflg == 1) {
			// INTFLG bit clear
			ioJpg7.jpintsta.bit.intflg = 0;
		}
		// Set result
		res |= ImJpegCommon_D_IM_JPEG_NML_END;
	}

	// Set result
	*result |= res;
	S_GIM_JPEG_RESULT_JUDGE |= ImJpegCommon_D_IM_JPEG_NML_END;

	return;
}

/**
 * @brief  Detection segment interrupt handler.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return	None
 */
void im_jpeg_sub_int_handler_dec_core_segint(ImJpeg*self, kint32* result )
{
	kint32 res = 0;

	// Segment error
	if (ioJpg7.jpintsta.bit.sizerr != 0) {
		ioJpg7.jpintsta.bit.sizerr = 0;
		res |= ImJpegCommon_D_IM_JPEG_SIZERR;
	}
	else if (ioJpg7.jpintsta.bit.rsterr != 0) {
		ioJpg7.jpintsta.bit.rsterr = 0;
		res |= ImJpegCommon_D_IM_JPEG_RSTERR;
	}
	else {
		// Do Nothing
	}

	// get error code
	S_GIM_JPEG_DEC_MNG.errCode = ioJpg7.jperrcod.bit.jperrcod;

	// Set result
	*result |= res;

	// Error reset
	im_jpeg_reset(NULL);

	return;
}

/**
 * @brief  Detection marker interrupt handler.
 * @param[in]	None
 * @param[out]	kint32* result
 * @return	None
 */
void im_jpeg_sub_int_handler_dec_core_mkint(ImJpeg*self, kint32* result )
{
	kint32 res = 0;

	// Marker detection interrupt
	if (ioJpg7.jpintsta.bit.umksinfo == 1) {
		ioJpg7.jpintsta.bit.umksinfo = 0;
		// Set result
		res |= ImJpegCommon_D_IM_JPEG_UMKSINFO;
	}
	else if (ioJpg7.jpintsta.bit.commkinfo == 1) {
		ioJpg7.jpintsta.bit.commkinfo = 0;
		// Set result
		res |= ImJpegCommon_D_IM_JPEG_COMMKINFO;
	}
	else if (ioJpg7.jpintsta.bit.appmkinfo == 1) {
		ioJpg7.jpintsta.bit.appmkinfo = 0;
		// Set result
		res |= ImJpegCommon_D_IM_JPEG_APPMKINFO;
	}
	else {
		// Fail Safe
		// Status clear
		ioJpg7.jpintsta.word = 0x00000000;
		res |= ImJpegCommon_D_IM_JPEG_ERR;
	}

	if (ioJpg7.jpsuspend.bit.jpsuspend) {
		// during suspend
		// Core restart
		ioJpg7.jpcmd.bit.jrstart = 1;
	}

	// Set result
	*result |= res;

	return;
}

ImJpeg* im_jpeg_new(void)
{
	ImJpeg *self = k_object_new_with_private(IM_TYPE_JPEG, sizeof(ImJpegPrivate));
	return self;
}
