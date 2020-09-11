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
#include "imjpeg.h"
#include "ddtop.h"
#include "ddimusercustom.h"
#include "jdsjp7.h"
#include "jdsimg.h"
#include "imjpegshare.h"
#include "imjpegskip.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImJpegSkip, im_jpeg_skip);
#define IM_JPEG_SKIP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImJpegSkipPrivate, IM_TYPE_JPEG_SKIP))

struct _ImJpegSkipPrivate
{
	kint a;
};

/*----------------------------------------------------------------------*/
/* Global Data																*/
/*----------------------------------------------------------------------*/
// counter
static volatile kushort S_GIM_JPEG_LINE_CNT = 0;
static volatile kulong S_GIM_JPEG_SECT_CNT = 0;

// encode setting table
static TimgEncMng S_GIM_JPEG_ENC_MNG;

// decode setting table
static TimgDecMng S_GIM_JPEG_DEC_MNG;

static kint32 S_GIM_JPEG_RESULT_JUDGE = 0;

// Spin Lock
static kulong S_GIM_JPG_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;
/**
 *IMPL
 */
static void im_jpeg_skip_constructor(ImJpegSkip *self)
{
//	ImJpegSkipPrivate *priv = IM_JPEG_SKIP_GET_PRIVATE(self);
}

static void im_jpeg_skip_destructor(ImJpegSkip *self)
{
//	ImJpegSkipPrivate *priv = IM_JPEG_SKIP_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/**
 * @brief		JPEG Decoding process asynchronous for marker skip mode.
 * @param[in]	None
 * @param[out]	None
 * @return		kint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR
 */
kint32 im_jpeg_start_skip_marker_dec( ImJpegSkip*self )
{
	DDIM_USER_ER ercd;

	DDIM_User_AhbReg_SpinLock();

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// F_JPEG7 macro In-use check
	if (ioJpg7.jpstatus.bit.jpstatus != 0) {
		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		DDIM_User_AhbReg_SpinUnLock();
		// macro running
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinUnLock();

	// Initialize
	// Decompression Error Code
	S_GIM_JPEG_DEC_MNG.errCode = 0;
	// Processing result
	S_GIM_JPEG_DEC_MNG.result = 0;
	S_GIM_JPEG_RESULT_JUDGE = 0;
	S_GIM_JPEG_LINE_CNT = 0;
	S_GIM_JPEG_SECT_CNT = 0;

	ercd = DDIM_User_Clr_Flg( FID_IM_JPEG, ~ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	if ( D_DDIM_USER_E_OK != ercd) {
		return ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR;
	}

	DDIM_User_AhbReg_SpinLock();

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// interrupt setting
	ioJpg7.jinten.word |= 0xC4D000;
	// JBUF start
	ioJpg7.jcctl.bit.jctrg = 1;
	// PBUF start
	ioJpg7.jictl.bit.jitrg = 1;
	// CORE start
	ioJpg7.jpcmd.bit.jstart = 1;

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinLock();

	return ImJpegCommon_D_IM_JPEG_OK;

}


/**
 * @brief		Waiting to be processed JPEG decoding.
 * @param[out]	TimgDecMng*	pJpgDecMng		: Result of the JPEG decoding process
 * @param[in]	kint32				timeOut			: Time-out period
 * @return		kint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_TIMEOUT /
 * ImJpegCommon_D_IM_JPEG_DECODE_ERR / ImJpegCommon_D_IM_JPEG_PARAM_ERROR / ImJpegCommon_D_IM_JPEG_DECODE_PAUSE
 */
kint32 im_jpeg_wait_end_dec(ImJpegSkip*self,  TimgDecMng* pJpgDecMng, kint32 timeOut )
{
	DDIM_USER_FLGPTN flgptn = 0;
	DDIM_USER_ER ercd;
	kint32 ret;

#ifdef CO_PARAM_CHECK
	if (pJpgDecMng == NULL) {
		Ddim_Assertion(("im_jpeg_wait_end_dec(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
	if (timeOut < D_DDIM_WAIT_END_FOREVER) {
		Ddim_Assertion(("im_jpeg_wait_end_dec(): input param error. timeOut = %x\n", timeOut));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	ercd = DDIM_User_Twai_Flg( FID_IM_JPEG, ImJpegCommon_D_IM_JPEG_FLG_WAIT_END, D_DDIM_USER_TWF_ORW, &flgptn, timeOut);

	*pJpgDecMng = S_GIM_JPEG_DEC_MNG;

	if (ercd != D_DDIM_USER_E_OK) {
		ret = ImJpegCommon_D_IM_JPEG_TIMEOUT;
	}
	else {
		// judge the result
		if (((pJpgDecMng->result & ImJpegCommon_D_IM_JPEG_JJBINT) == ImJpegCommon_D_IM_JPEG_JJBINT)
			|| ((pJpgDecMng->result & ImJpegCommon_D_IM_JPEG_JPBINT) == ImJpegCommon_D_IM_JPEG_JPBINT)) {
			// bus error
			ret = ImJpegCommon_D_IM_JPEG_AXI_ERR;
		}
		else if ((pJpgDecMng->result & ( ImJpegCommon_D_IM_JPEG_JCLRFMER | ImJpegCommon_D_IM_JPEG_SIZERR | ImJpegCommon_D_IM_JPEG_RSTERR
			| ImJpegCommon_D_IM_JPEG_ERR | ImJpegCommon_D_IM_JPEG_SMPL_TYPE_NG | ImJpegCommon_D_IM_JPEG_CUTOUT_ERR)) != 0) {
			ret = ImJpegCommon_D_IM_JPEG_DECODE_ERR;
		}
		else if ((pJpgDecMng->result & ImJpegCommon_D_IM_JPEG_PAUSE) == ImJpegCommon_D_IM_JPEG_PAUSE) {
			// pausing end or code size over
			ret = ImJpegCommon_D_IM_JPEG_DECODE_PAUSE;
		}
		else {
			// encode process finished
			ret = ImJpegCommon_D_IM_JPEG_OK;
		}
	}

	return ret;
}

/**
 * @brief		JPEG decode restart.(Restart from the state is paused decoding)
 * @param[in]	TimgDecFrameMng*	pJpgDecFrmMng	: Pointer to JPEG Decode frame management table
 * @param[out]	None
 * @return		kint32	ImJpegCommon_D_IM_JPEG_OK / ImJpegCommon_D_IM_JPEG_RUNNING_NG / ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
kint32 im_jpeg_restart_dec(ImJpegSkip*self,  TimgDecFrameMng* pJpgDecFrmMng )
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (pJpgDecFrmMng == NULL) {
		Ddim_Assertion(("im_jpeg_restart_dec(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	DDIM_User_AhbReg_SpinLock();
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	if (ioJpg7.jcctl.bit.jctrg != 2) {
		// HCLK off
		im_jpeg_off_hclk(NULL);
		ImJpegCommon_IM_JPEG_DSB();
		DDIM_User_AhbReg_SpinUnLock();
		// Coding not stopped
		return ImJpegCommon_D_IM_JPEG_RUNNING_NG;
	}

	// Initialize result
	// Processing result
	S_GIM_JPEG_DEC_MNG.result = 0;
	S_GIM_JPEG_RESULT_JUDGE = 0;

	// Set destination addr
	ioJpg7.jcoda.bit.jcoda = pJpgDecFrmMng->codeAddr;

	if (pJpgDecFrmMng->codeSize == 0) {
		ioJpg7.jinten.bit.jcpfen = 0;
		ioJpg7.jcodsv.word = 0;
	}
	else {
		ioJpg7.jinten.bit.jcpfen = 1;
		ioJpg7.jcodsv.word = (kulong) (((pJpgDecFrmMng->codeSize) / ImJpegCommon_D_IM_JPEG_SECT_CNT) + 1);
	}
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinUnLock();

	ercd = DDIM_User_Clr_Flg( FID_IM_JPEG, ~ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	if ( D_DDIM_USER_E_OK != ercd) {
		return ImJpegCommon_D_IM_JPEG_SYSTEMCALL_ERR;
	}

	DDIM_User_AhbReg_SpinLock();
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	// JBUF restart
	ioJpg7.jcctl.bit.jctrg = 1;
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinUnLock();

	return ImJpegCommon_D_IM_JPEG_OK;
}

/**
 * @brief		Stop JPEG process.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_stop( ImJpegSkip*self )
{
	DDIM_User_AhbReg_SpinLock();

	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	im_jpeg_reset(NULL);

	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinUnLock();
	return;
}

/**
 * @brief		Get JPEG AXI (JBUF and PBUF) State of frame processing
 * @param[in]	None
 * @param[out]	EimgAxiSt*	pJpAxiState	:AXI state
 * @return		kint32	D_DDIM_OK / ImJpegCommon_D_IM_JPEG_PARAM_ERROR
 */
kint32 im_jpeg_get_axi_state(ImJpegSkip*self,  EimgAxiSt* pJpAxiState )
{
#ifdef CO_PARAM_CHECK
	if (pJpAxiState == NULL) {
		Ddim_Assertion(("im_jpeg_get_axi_state(): Null check error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	DDIM_User_AhbReg_SpinLock();
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	if (ioJpg7.jstate.bit.jallactp) {
		if ((ioJpg7.jstate.word & 0xC0) == 0xC0) {
			*pJpAxiState = ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_BOTH;
		}
		else if (ioJpg7.jstate.bit.jjbactp) {
			*pJpAxiState = ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_JBUF;
		}
		else {
			*pJpAxiState = ImJpegCommon_E_IM_JPEG_AXI_ST_ACTIVE_PBUF;
		}
	}
	else {
		*pJpAxiState = ImJpegCommon_E_IM_JPEG_AXI_ST_INACTIVE_BOTH;
	}
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();

	DDIM_User_AhbReg_SpinUnLock();

	return D_DDIM_OK;
}

/*
 * @brief		Returns the lines of the processed image of the vertical.
 * @param[in]	None
 * @param[out]	None
 * @return		USHOUT	Number of the line counts
 */
kushort im_jpeg_get_line_cnt( ImJpegSkip*self )
{
	kushort retCnt;

	// SpinLock.
	Dd_ARM_Critical_Section_Start(S_GIM_JPG_SPIN_LOCK);
	retCnt = S_GIM_JPEG_LINE_CNT;

	// SpinUnLock.
	Dd_ARM_Critical_Section_End(S_GIM_JPG_SPIN_LOCK);

	return retCnt;
}

/*
 * @brief		Returns the lines of the processed image of the vertical.
 * @param[in]	None
 * @param[out]	None
 * @return		kulong	Number of the sect counts
 */
kulong im_jpeg_get_sect_cnt( ImJpegSkip*self )
{
	kulong retCnt;

	// SpinLock.
	Dd_ARM_Critical_Section_Start(S_GIM_JPG_SPIN_LOCK);
	retCnt = S_GIM_JPEG_SECT_CNT;

	// SpinUnLock.
	Dd_ARM_Critical_Section_End(S_GIM_JPG_SPIN_LOCK);


	return retCnt;
}

/**
 * @brief		JPEG interrupt handler.
 * @param[in]	None
 * @param[out]	None
 * @return		None
 */
void im_jpeg_int_handler( ImJpegSkip*self )
{
	kuchar encDecFlg = 0;
	kint32 result = 0;
	kuchar procEnd = 0;
	kuchar forceEnd = 0;
	kuchar pbufErr = 0;
	kuchar jbufErr = 0;
	VpCallback pcallback = NULL;
	kint32 ret;
	IoJpeg7cJint _jint;

	DDIM_User_AhbReg_SpinLock();
	// HCLK on
	im_jpeg_on_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	_jint.word = ioJpg7.jint.word;

#ifdef CO_IM_JPEG_DEBUG
	Ddim_Print(("ioJpg7.JINT.     =[0x%08lX]\n", _jint.word));
	Ddim_Print(("ioJpg7.JPINTSTA. =[0x%08lX]\n", ioJpg7.JPINTSTA.word));
#endif
	if (ioJpg7.jpmode.bit.disposal == 0) {
		// encode
		encDecFlg = 1;
	}
	else {
		// decode
		encDecFlg = 0;
	}

	while (1) {
		/* pgr0872 */
		if (_jint.bit.jerrint == 1) {
			// Module error
			/* pgr0872 */
			if ((ioJpg7.jinten.bit.jclrfmeren == 1) && (_jint.bit.__jclrfmer == 1)) {
				// Unsupport Format error
				// JCLRFMER bit clear
				ioJpg7.jint.word = 0x00040000;
				result |= ImJpegCommon_D_IM_JPEG_JCLRFMER;
			}
			/* pgr0872 */
			if ((ioJpg7.jinten.bit.jjben == 1) && (_jint.bit.__jjbint == 1)) {
				// JBUF error
				// Get the error factor
				jbufErr = ioJpg7.jjbsta.bit.jjres;
				// JJBINT bit clear
				ioJpg7.jint.word = 0x00400000;
				result |= ImJpegCommon_D_IM_JPEG_JJBINT;
			}
			/* pgr0872 */
			if ((ioJpg7.jinten.bit.jpben == 1) && (_jint.bit.__jpbint == 1)) {
				// PBUF error
				// Get the error factor
				pbufErr = ioJpg7.jpbsta.bit.jpres;
				// JPBINT bit clear
				ioJpg7.jint.word = 0x00800000;
				result |= ImJpegCommon_D_IM_JPEG_JPBINT;
			}
			// soft reset
			im_jpeg_reset(NULL);
			// end of process
			forceEnd = 1;
			break;
		}

		/* pgr0872 */
		if (_jint.bit.jjirq != 0) {
			// Interrupt from core(F_JPEG7)
			if (encDecFlg == 1) {
				// endcode
				// check the quant table
				im_jpeg_sub_int_handler_enc_core_qtwint(NULL, &result);

				if ((ioJpg7.jint.bit.jjirqst & 0x04) == 0x04) {
					// encode normal end
					im_jpeg_sub_int_handler_enc_core_end(NULL, &result);
				}
			}
			else {
				/* pgr0872 */
				if ((_jint.bit.jjirqst & 0x01) == 0x01) {
					// decode error
					im_jpeg_sub_int_handler_dec_core_errint(NULL, &result);
					// end of process
					forceEnd = 1;
				}
				else if ((_jint.bit.jjirqst & 0x04) == 0x04 || ioJpg7.jpintsta.bit.corend == 1) {
					// decode normal end
					im_jpeg_sub_int_handler_dec_core_end(NULL, &result);
				}
				else if ((_jint.bit.jjirqst & 0x02) == 0x02) {
					// read size enable
					ret = im_jpeg_sub_int_handler_dec_core_regrdint(NULL, &result);
					if (ret != ImJpegCommon_D_IM_JPEG_OK) {
						// end of process
						forceEnd = 1;
					}
				}
				else {
					if ((ioJpg7.jpintsta.bit.sizerr != 0) || (ioJpg7.jpintsta.bit.rsterr != 0)) {
						// check huffman segment error kint
						im_jpeg_sub_int_handler_dec_core_segint(NULL, &result);
						// end of process
						forceEnd = 1;
					}
					else {
						// check marker kint
						im_jpeg_sub_int_handler_dec_core_mkint(NULL, &result);
					}
				}
			}

//			break;
		}
		/* pgr0872 */
		if ((ioJpg7.jinten.bit.jifen == 1) && (_jint.bit.__jif == 1)) {
			// Whether forwarding the image of one frame was completed is judged
			// Set result
			result |= ImJpegCommon_D_IM_JPEG_JIF;
			S_GIM_JPEG_RESULT_JUDGE |= ImJpegCommon_D_IM_JPEG_JIF;
			// JIF bit clear
			ioJpg7.jint.word = 0x00008000;
			// SpinLock.
			Dd_ARM_Critical_Section_Start(S_GIM_JPG_SPIN_LOCK);
			// Get processed line
			S_GIM_JPEG_LINE_CNT = ioJpg7.jisvmn.bit.jisvmn;
			// SpinUnLock.
			Dd_ARM_Critical_Section_End(S_GIM_JPG_SPIN_LOCK);
#ifdef CO_IM_JPEG_DEBUG
			Ddim_Print(("ioJpg7.JISVMN =[0x%X]\n", S_GIM_JPEG_LINE_CNT));
#endif
		}
		/* pgr0872 */
		if ((ioJpg7.jinten.bit.jcfen == 1) && (_jint.bit.__jcf == 1)) {
			// Whether the sign data transfer of one frame was completed is judged
			// Set result
			result |= ImJpegCommon_D_IM_JPEG_JCF;
			S_GIM_JPEG_RESULT_JUDGE |= ImJpegCommon_D_IM_JPEG_JCF;
			// JCF bit clear
			ioJpg7.jint.word = 0x00004000;
			// SpinLock.
			Dd_ARM_Critical_Section_Start(S_GIM_JPG_SPIN_LOCK);
			// Get processed sect
			S_GIM_JPEG_SECT_CNT = ioJpg7.jsctc.bit.jsctc;
			// SpinUnLock.
			Dd_ARM_Critical_Section_End(S_GIM_JPG_SPIN_LOCK);
#ifdef CO_IM_JPEG_DEBUG
			Ddim_Print(("ioJpg7.JSCTC =[0x%lX]\n", S_GIM_JPEG_SECT_CNT));
#endif
		}
		/* pgr0872 */
		if ((ioJpg7.jinten.bit.jcpfen == 1) && (_jint.bit.__jcpf == 1)) {
			// Whether the transmission of the number of sectors specified by JCODSV is completed is judged.
			// Set result
			result |= ImJpegCommon_D_IM_JPEG_PAUSE;
			// JCPF bit clear
			ioJpg7.jint.word = 0x00001000;
			// Write code size
			// Count value of compression volume of data
			S_GIM_JPEG_ENC_MNG.codeSize = ioJpg7.jpbytcnt.word - 8;
			// Process end
			forceEnd = 1;
		}
		/* pgr0872 */
		if ((ioJpg7.jinten.bit.jsecten == 1) && (_jint.bit.__jsectint == 1)) {
			// Whether the transmission of the number of sectors specified by JSECTVAL is completed is judged.
			// Set result
			result |= ImJpegCommon_D_IM_JPEG_PSECTINT;
			// JSECTINT bit clear
			ioJpg7.jint.word = 0x00010000;
		}
		/* pgr0872 */
		if ((ioJpg7.jinten.bit.jlineen == 1) && (_jint.bit.__jlineint == 1)) {
			// Whether the transmission of the number of lines specified by JLINEVAL is completed is judged.
			// Set result
			result |= ImJpegCommon_D_IM_JPEG_PLINEINT;
			// JLINEINT bit clear
			ioJpg7.jint.word = 0x00020000;
		}

		break;
	}
	// HCLK off
	im_jpeg_off_hclk(NULL);
	ImJpegCommon_IM_JPEG_DSB();
	DDIM_User_AhbReg_SpinUnLock();

	if (forceEnd || (S_GIM_JPEG_RESULT_JUDGE & ImJpegCommon_D_IM_JPEG_PROC_END) == ImJpegCommon_D_IM_JPEG_PROC_END) {
		procEnd = 1;
	}

	if (encDecFlg == 1) {
		//when restart, save previous result value.
		if (jbufErr) {
			S_GIM_JPEG_ENC_MNG.jbufCtrl.errState = jbufErr;
		}
		if (pbufErr) {
			S_GIM_JPEG_ENC_MNG.pbufCtrl.errState = pbufErr;
		}

		S_GIM_JPEG_ENC_MNG.result |= result;

		pcallback = S_GIM_JPEG_ENC_MNG.pcallback;
		if ((pcallback != NULL) && (procEnd == 1)) {
			((void (*) ()) pcallback)(&S_GIM_JPEG_ENC_MNG);
		}
	}
	else {
		//when restart, save previous result value.
		if (jbufErr) {
			S_GIM_JPEG_DEC_MNG.jbufCtrl.errState = jbufErr;
		}
		if (pbufErr) {
			S_GIM_JPEG_DEC_MNG.pbufCtrl.errState = pbufErr;
		}

		S_GIM_JPEG_DEC_MNG.result |= result;
		pcallback = S_GIM_JPEG_DEC_MNG.pcallback;
		if ((pcallback != NULL) && (procEnd == 1)) {
			((void (*) ()) pcallback)(&S_GIM_JPEG_DEC_MNG);
		}
	}

	if (procEnd != 0) {
		// Flag set
		(void) DDIM_User_Set_Flg( FID_IM_JPEG, ImJpegCommon_D_IM_JPEG_FLG_WAIT_END);
	}
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------

/**
 * @brief		The decode of jpeg
 * @param[in]	TimgDecInput* inputParam
 * @param[out]	TimgDecOutput* outputParam
 * @return		kint32 D_DDIM_OK / D_IM_JPEG_DECODE_NG / ImJpegCommon_D_IM_JPEG_PARAM_ERROR /
 *  D_IM_JPEG_DECODE_TIMEOUT / D_IM_JPEG_DECODE_HEADER_NG / D_IM_JPEG_DECODE_16BYTE_NG / D_IM_JPEG_DECODE_ENCODE_NG
 * @note		None
 * @attention	None
 */
kint32 im_jpeg_decode_sync(ImJpegSkip*self, TimgDecInput* inputParam, TimgDecOutput* outputParam)
{
	kint32 ret = 0;
	TimgDecMng jpgmng;
	TimgDecFrameMng jpgfrmmng;

#ifdef CO_PARAM_CHECK
	if (inputParam == NULL) {
		// inputParam is Error because of NULL
		Ddim_Print(("I:im_jpeg_decode_sync. inputParam = NULL\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
	if (outputParam == NULL) {
		// outputParam is Error because of NULL
		Ddim_Print(("I:im_jpeg_decode_sync. outputParam = NULL\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
#endif

	if ((inputParam->codeAddr & 0x7) != 0) {
		// src address error
		Ddim_Print(("I:im_jpeg_decode_sync. code address error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
	if ((inputParam->dstYccAddr.y & 0x7) != 0) {
		// dst Y address error
		Ddim_Print(("I:im_jpeg_decode_sync. dst Y address error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}
	if ((inputParam->dstYccAddr.c & 0x7) != 0) {
		// dst Cb address error
		Ddim_Print(("I:im_jpeg_decode_sync. dst Cb address error.\n"));
		return ImJpegCommon_D_IM_JPEG_PARAM_ERROR;
	}

	// initialize
	memset(&jpgmng, 0, sizeof(TimgDecMng));
	memset(&jpgfrmmng, 0, sizeof(TimgDecFrameMng));

	// set control structure
	jpgmng.memFormat = inputParam->memFormat;
	jpgmng.extMode = ImJpegCommon_E_IM_JPEG_RESIZE_EXT_DIRECT;
	jpgmng.corrMode = ImJpegCommon_D_IM_JPEG_ENABLE_ON;
	jpgmng.skipMkFlg = ImJpegCommon_D_IM_JPEG_ENABLE_OFF;
	jpgmng.smplType = inputParam->smplType;
	jpgmng.pcallback = NULL;

	jpgfrmmng.globalYWidth = inputParam->globalYWidth;
	jpgfrmmng.globalCWidth = inputParam->globalCWidth;
	jpgfrmmng.codeSize = inputParam->codeSize;
	jpgfrmmng.yccAddr.y = inputParam->dstYccAddr.y;
	jpgfrmmng.yccAddr.c = inputParam->dstYccAddr.c;
	jpgfrmmng.codeAddr = inputParam->codeAddr;

	ret = im_jpeg_open(NULL, D_DDIM_WAIT_END_TIME);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		Ddim_Print(("im_jpeg_open error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_ctrl_dec(NULL, &jpgmng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_dec error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_ctrl_dec_frame(NULL, &jpgfrmmng);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_ctrl_dec_frame error! ercd = %d\n", ret));
		return ret;
	}

	ret = im_jpeg_start_dec(NULL);
	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		im_jpeg_close(NULL);
		Ddim_Print(("im_jpeg_start_dec error! ercd = %d\n", ret));
		return ret;
	}

#ifdef CO_DEBUG_ON_PC
	{
		ioJpg7.JPMODE.bit.MMODE = (kuchar)inputParam->smplType;
		ioJpg7.JSTATE.bit.JALLRSTP = 1;
		ioJpg7.JINT.word = 0x0A000000;
		ioJpg7.JPINTSTA.word = 0x00000008;
		ioJpg7.JPSUSPEND.bit.JPSUSPEND = 1;
		im_jpeg_int_handler(NULL);
		// JIF
		ioJpg7.JINT.word = 0x8000;
		im_jpeg_int_handler(NULL);
		// JCF
		ioJpg7.JINT.word = 0x4000;
		im_jpeg_int_handler(NULL);
		ioJpg7.JINT.word = 0x0C000000;
		ioJpg7.JPINTSTA.word = 0x80000000;
		ioJpg7.JPSTATUS.bit.JPSTATUS = 1;
		im_jpeg_int_handler(NULL);
	}
#endif // CO_DEBUG_ON_PC

	ret = im_jpeg_wait_end_dec(NULL, &jpgmng, D_DDIM_WAIT_END_TIME);

	outputParam->smplType = jpgmng.smplType;
	outputParam->errCode = jpgmng.errCode;
	outputParam->orgWidth = jpgmng.orgWidth;
	outputParam->orgLines = jpgmng.orgLines;

	if (ret != ImJpegCommon_D_IM_JPEG_OK) {
		switch (ret) {
			case ImJpegCommon_D_IM_JPEG_DECODE_PAUSE:
				Ddim_Print(("im_jpeg_start_dec Code size over! ercd = %d\n", ret));
				break;
			case ImJpegCommon_D_IM_JPEG_AXI_ERR:
				if ((jpgmng.result & ImJpegCommon_D_IM_JPEG_JJBINT) == ImJpegCommon_D_IM_JPEG_JJBINT) {
					Ddim_Print(("im_jpeg_start_dec JBUF error! ercd = %d\n", jpgmng.jbufCtrl.errState ));
				}
				else {
					Ddim_Print(("im_jpeg_start_dec PBUF error! ercd = %d\n", jpgmng.pbufCtrl.errState ));
				}
				break;
			case ImJpegCommon_D_IM_JPEG_DECODE_ERR:
				if ((jpgmng.result & ImJpegCommon_D_IM_JPEG_SMPL_TYPE_NG) == ImJpegCommon_D_IM_JPEG_SMPL_TYPE_NG) {
					Ddim_Print(("im_jpeg_start_dec sampling type not matching! ercd = %d\n", ret));
				}
				else if ((jpgmng.result & ImJpegCommon_D_IM_JPEG_JCLRFMER) == ImJpegCommon_D_IM_JPEG_JCLRFMER) {
					Ddim_Print(("im_jpeg_start_dec unsupported format error! ercd = %d\n", ret));
				}
				else {
					Ddim_Print(("im_jpeg_start_dec encode data error! ercd = %d\n", ret));
				}
				break;
			case ImJpegCommon_D_IM_JPEG_TIMEOUT:
				Ddim_Print(("im_jpeg_start_dec time out error! ercd = %d\n", ret));
				break;
			default:
				Ddim_Print(("im_jpeg_start_dec system error! ercd = %d\n", ret))	;
				break;
		}
		// macro stop
		im_jpeg_stop(NULL);
	}
	// close
	im_jpeg_close(NULL);

	return ret;
}
//---------------------- colabo  section -------------------------------
#endif	// CO_DDIM_UTILITY_USE

ImJpegSkip* im_jpeg_skip_new(void)
{
	ImJpegSkip *self = k_object_new_with_private(IM_TYPE_JPEG_SKIP, sizeof(ImJpegSkipPrivate));
	return self;
}
