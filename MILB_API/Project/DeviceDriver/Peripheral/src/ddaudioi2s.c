/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月3日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#include <string.h>
#include "audio_if.h"
#include "dd_arm.h"
#include "ddaudio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioI2s, dd_audio_i2s);
#define DD_AUDIO_I2S_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioI2sPrivate, DD_TYPE_AUDIO_I2S))


struct _DdAudioI2sPrivate
{
	volatile AudioMasterClock gDd_Audio_MasterClock;
	volatile AudioI2sCmmn cmmnData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sIn inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sOut outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sCmmn *gDd_Audio_I2S_Cmmn[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sIn *gDd_Audio_I2S_In[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sOut *gDd_Audio_I2S_Out[DdAudio_IF_CH_NUM_MAX];
};


static const UINT8	gDd_Audio_AUOF_Tbl_8_L[4] =			// 8bit Left-Justified
{
	0x00,				// 32FS
	0x10,				// 48FS
	0x01,				// 64FS
	0x20				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_8_R[4] =			// 8bit Right-Justified
{
	0x02,				// 32FS
	0x12,				// 48FS
	0x03,				// 64FS
	0x22				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_8_I2S[4] =			// 8bit I2S
{
	0x40,				// 32FS
	0x50,				// 48FS
	0x41,				// 64FS
	0x60				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_16_L[4] =			// 16bit Left-Justified
{
	0x04,				// 32FS
	0x14,				// 48FS
	0x05,				// 64FS
	0x24				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_16_R[4] =			// 16bit Right-Justified
{
	0x06,				// 32FS
	0x17,				// 48FS
	0x07,				// 64FS
	0x27				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_16_I2S[4] =			// 16bit I2S
{
	0x44,				// 32FS
	0x54,				// 48FS
	0x45,				// 64FS
	0x64				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_24_L[4] =			// 24bit Left-Justified
{
	0xFF,				// 32FS
	0x18,				// 48FS
	0x09,				// 64FS
	0x28				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_24_R[4] =			// 24bit Right-Justified
{
	0xFF,				// 32FS
	0x1A,				// 48FS
	0x0B,				// 64FS
	0x2B				// 128FS
};

static const UINT8	gDd_Audio_AUOF_Tbl_24_I2S[4] =			// 24bit I2S
{
	0xFF,				// 32FS
	0x58,				// 48FS
	0x49,				// 64FS
	0x68				// 128FS
};

static const UINT8	*gDd_Audio_AUOF_Tbl[3][3] =			// index [bits][mode]
{
	//	L							R							I2S
	{	gDd_Audio_AUOF_Tbl_8_L,		gDd_Audio_AUOF_Tbl_8_R,		gDd_Audio_AUOF_Tbl_8_I2S	},	// 8bit
	{	gDd_Audio_AUOF_Tbl_16_L,	gDd_Audio_AUOF_Tbl_16_R,	gDd_Audio_AUOF_Tbl_16_I2S	},	// 16bit
	{	gDd_Audio_AUOF_Tbl_24_L,	gDd_Audio_AUOF_Tbl_24_R,	gDd_Audio_AUOF_Tbl_24_I2S	}	// 24bit
};

static const UINT8	gDd_Audio_AUIF_Tbl[3][3] =				// index [bits][mode]
{
	//  L       R       I2S
	{	0x00,	0x01,	0x08	},		// 8bit
	{	0x02,	0x03,	0x0A	},		// 16bit
	{	0x04,	0x05,	0x0C	}		// 24bit
};


static INT32 dd_audio_set_enable_in_data24bit(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_enable_out_data24bit(UINT8 ch, UINT8 enable);
static INT32 dd_audio_set_input_data_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_output_data_format(UINT8 ch, UINT8 format);
static INT32 dd_audio_set_clock_div(UINT8 ch, UINT8 mclock, UINT8 auclock, UINT8 lrclock);
static INT32 dd_audio_set_enable_clock_division(UINT8 ch, UINT8 enable);
static BOOL dd_audio_get_enable_clock_division(UINT8 ch);
static INT32 dd_audio_set_enable_output_clock(UINT8 ch, UINT8 enable);
static VOID dd_audio_set_clkstop_auxck(UINT8 ch, UINT8 val);
static VOID dd_audio_set_clkstop_auxck_all(UINT8 val);
static VOID dd_audio_set_clksel_auxsel(UINT8 ch, UINT8 val);
static VOID dd_audio_select_aumclk_in(UINT8 ch, UINT8 val);
static INT32 dd_audio_set_masterclock(AudioMasterClock mclk);


static void dd_audio_i2s_constructor(DdAudioI2s *self)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->cmmnData[i].aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
		priv->cmmnData[i].divAumclko = DdAudioI2s_AUMCLKO_DIV_2;
		priv->cmmnData[i].divAuclk = DdAudioI2s_AUCLK_DIV_16;
		priv->cmmnData[i].divLrclk = DdAudioI2s_AULR_DIV_32;
		priv->cmmnData[i].clkDivEnable = DdAudio_DISABLE;
		priv->cmmnData[i].masterSlave = DdAudioI2s_CLK_SLAVE;

		priv->inData[i].modeIn = DdAudioI2s_MODE_L_JUST;
		priv->inData[i].bitIn = DdAudioI2s_BIT_8BIT;

		priv->outData[i].modeOut = DdAudioI2s_MODE_L_JUST;
		priv->outData[i].bitOut = DdAudioI2s_BIT_8BIT;
		priv->outData[i].fs = DdAudioI2s_FS_32FS;

		priv->gDd_Audio_I2S_Cmmn[i] = &priv->cmmnData[i];
		priv->gDd_Audio_I2S_In[i] = &priv->inData[i];
		priv->gDd_Audio_I2S_Out[i] = &priv->outData[i];
	}

	priv->gDd_Audio_MasterClock = (AudioMasterClock)0xFF;
}

static void dd_audio_i2s_destructor(DdAudioI2s *self)
{

}

/**
 * @brief  Set register AUIDSEL.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_in_data24bit(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDSEL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUIDSEL:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;
	aucr.bit.AUIDSEL = enable;
	IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register AUODSEL.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_out_data24bit(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUODSEL:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUODSEL:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;
	aucr.bit.AUODSEL = enable;
	IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register AUIF.
 * @param  UINT8 ch
 * @param  UINT8 format
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_input_data_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUIF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 0x0E){
		Ddim_Assertion(("[DD_AUDIO]Set AUIF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.AUIF != format){						/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIF Error:AUIEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.AUIF = format;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUOF.
 * @param  UINT8 ch
 * @param  UINT8 format
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_output_data_format(UINT8 ch, UINT8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucr aucr;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUOF:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (format > 0x6D){
		Ddim_Assertion(("[DD_AUDIO]Set AUOF:input format error : %d\n", format));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucr.word = IO_AUDIO.AUDIOIF[ch].AUCR.word;

	if (aucr.bit.AUOF != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUOF Error:AUOEF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUOF Error:LBF = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.AUOF = format;
			IO_AUDIO.AUDIOIF[ch].AUCR.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Get register DIVE.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static BOOL dd_audio_get_enable_clock_division(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DIVE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register DIVMCK/DIVCK/DIVLR.
 * @param  UINT8 ch
 * @param  UINT8 mclock
 * @param  UINT8 auclock
 * @param  UINT8 lrclock
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_clock_div(UINT8 ch, UINT8 mclock, UINT8 auclock, UINT8 lrclock)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucc aucc;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DIVCLK:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (mclock > 31){
		Ddim_Assertion(("[DD_AUDIO]Set DIVCLK:input mclock error : %d\n", mclock));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (auclock > 7){
		Ddim_Assertion(("[DD_AUDIO]Set DIVCLK:input auclock error : %d\n", auclock));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (lrclock > 3){
		Ddim_Assertion(("[DD_AUDIO]Set DIVCLK:input lrclock error : %d\n", lrclock));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucc.word = IO_AUDIO.AUDIOIF[ch].AUCC.word;

	if ((aucc.bit.DIVMCK != mclock)	||				/* pgr0872 */
		(aucc.bit.DIVCK != auclock)	||				/* pgr0872 */
		(aucc.bit.DIVLR != lrclock)	){				/* pgr0872 */

		if (dd_audio_get_enable_clock_division(ch) != FALSE){
			Ddim_Assertion(("[DD_AUDIO]Set DIVCLK Error:DIVE = 1\n"));
			ret_val = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucc.bit.DIVMCK = mclock;
			aucc.bit.DIVCK = auclock;
			aucc.bit.DIVLR = lrclock;
			IO_AUDIO.AUDIOIF[ch].AUCC.word = aucc.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register DIVE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_clock_division(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucc aucc;
	INT32 ret_val = D_DDIM_OK;
	volatile UINT32 wait_counter;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set DIVE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set DIVE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucc.word = IO_AUDIO.AUDIOIF[ch].AUCC.word;

	if (aucc.bit.DIVE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:AUIEF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:AUOEF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:LBF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucc.bit.DIVE = enable;
				IO_AUDIO.AUDIOIF[ch].AUCC.word = aucc.word;
			}
		}
		else {
			aucc.bit.DIVE = enable;
			IO_AUDIO.AUDIOIF[ch].AUCC.word = aucc.word;
		}
	}

	Dd_ARM_Dsb_Pou();

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

//	printf("[Set]DIVE%d=%d\n", ch, IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE);
//	printf("[Set]DIVE%d=%d\n", ch, aucc.bit.DIVE);

	// wait DIVE readable
	if (IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE != aucc.bit.DIVE){
		wait_counter = 0;
		while (IO_AUDIO.AUDIOIF[ch].AUCC.bit.DIVE != aucc.bit.DIVE){
			DDIM_User_Dly_Tsk(0);

			if (wait_counter > 10){
				Ddim_Print(("[DD_AUDIO]DIVE not read correct value\n"));
				break;
			}
			wait_counter++;
		}
	}

	return ret_val;
}

/**
 * @brief  Set register AUCKOE.
 * @param  UINT8 ch
 * @param  UINT8 enable
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_enable_output_clock(UINT8 ch, UINT8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);
	volatile union io_audio_aucc aucc;
	INT32 ret_val = D_DDIM_OK;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Set AUCKOE: input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}

	if (enable > 1){
		Ddim_Assertion(("[DD_AUDIO]Set AUCKOE:input enable error : %d\n", enable));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	aucc.word = IO_AUDIO.AUDIOIF[ch].AUCC.word;

	if (aucc.bit.AUCKOE != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:AUIEF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:AUOEF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:LBF = 1\n"));
				ret_val = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucc.bit.AUCKOE = enable;
				IO_AUDIO.AUDIOIF[ch].AUCC.word = aucc.word;
			}
		}
		else {
			aucc.bit.AUCKOE = enable;
			IO_AUDIO.AUDIOIF[ch].AUCC.word = aucc.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return ret_val;
}

/**
 * @brief  Set register AUxCK.
 * @param  UINT8 ch
 * @param  UINT8 val[1:stop/0:supply]
 */
static VOID dd_audio_set_clkstop_auxck(UINT8 ch, UINT8 val)
{
	switch (ch){
		case DdAudio_IF_CH0 :
			Dd_Top_Set_CLKSTOP1_AU0CK(val);
			break;
		case DdAudio_IF_CH2 :
			Dd_Top_Set_CLKSTOP1_AU2CK(val);
			break;
		case DdAudio_IF_CH3 :
			Dd_Top_Set_CLKSTOP1_AU3CK(val);
			break;
		case DdAudio_IF_CH4 :
			Dd_Top_Set_CLKSTOP1_AU4CK(val);
			break;
		case DdAudio_IF_CH5 :
			Dd_Top_Set_CLKSTOP1_AU5CK(val);
			break;
		default :
			break;
	}
}

/**
 * @brief  Set register all AUxCK.
 * @param  UINT8 val[1:stop/0:supply]
 */
static VOID dd_audio_set_clkstop_auxck_all(UINT8 val)
{
	Dd_Top_Set_CLKSTOP1_AU0CK(val);
	Dd_Top_Set_CLKSTOP1_AU2CK(val);
	Dd_Top_Set_CLKSTOP1_AU3CK(val);
	Dd_Top_Set_CLKSTOP1_AU4CK(val);
	Dd_Top_Set_CLKSTOP1_AU5CK(val);
}

/**
 * @brief  Set register AUCKSEL.
 * @param  UINT8 ch
 * @param  UINT8 val
 */
static VOID dd_audio_set_clksel_auxsel(UINT8 ch, UINT8 val)
{
	switch (ch){
		case DdAudio_IF_CH0 :
			Dd_Top_Set_CLKSEL8_AU0SEL(val);
			break;
		case DdAudio_IF_CH2 :
			Dd_Top_Set_CLKSEL8_AU2SEL(val);
			break;
		case DdAudio_IF_CH3 :
			Dd_Top_Set_CLKSEL8_AU3SEL(val);
			break;
		default :
			break;
	}
}

/**
 * @brief  Change AUCKSEL.
 * @param  UINT8 ch
 * @param  UINT8 val
 */
static VOID dd_audio_select_aumclk_in(UINT8 ch, UINT8 val)
{
	DdAudio* ddAudio = dd_audio_get();
	ULONG* pSpinLock  = dd_audio_get_spin_lock_addr(ddAudio);

	switch (ch){
		case DdAudio_IF_CH0 :
			if (Dd_Top_Get_CLKSEL8_AU0SEL() == (val & 0x01)){
				return ;
			}
			break;
		case DdAudio_IF_CH2 :
			if (Dd_Top_Get_CLKSEL8_AU2SEL() == (val & 0x01)){
				return ;
			}
			break;
		case DdAudio_IF_CH3 :
			if (Dd_Top_Get_CLKSEL8_AU3SEL() == (val & 0x01)){
				return ;
			}
			break;
		default :
			return;
	}

	// SpinLock
	Dd_ARM_Critical_Section_Start(*pSpinLock);

	dd_audio_set_clkstop_auxck(ch, 1);
	dd_audio_set_clksel_auxsel(ch, val);
	dd_audio_set_clkstop_auxck(ch, 0);

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);
}

/**
 * @brief  Set AudioMasterClock.
 * @param  AudioMasterClock mclk
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_masterclock(AudioMasterClock mclk)
{
/*
	MCLK[MHz]	|	AUCLK	|	P10APLLDIV
	--------------------------------------
	8.192		|	3		|	0
	22.5792		|	1		|	1
	24.576		|	2		|	0
	36.864		|	0		|	2
*/

	volatile UINT8 net_auck;

	if (Dd_Top_Get_PLLCNT1_PL10ST() == 0){
		Ddim_Print(("[DD_AUDIO]dd_audio_set_masterclock:PLL10 is not started. \n"));
		return DdAudio_SYSTEM_ERROR;
	}

	net_auck = Dd_Top_Get_CLKSTOP1_NETAUCK();

	switch (mclk){
		case DdAudioI2s_MASTER_CLOCK_8_192:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 0)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 3)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				dd_audio_set_clkstop_auxck_all(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(0);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(3);
			}

			dd_audio_set_clkstop_auxck_all(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(net_auck);
			break;

		case DdAudioI2s_MASTER_CLOCK_22_5792:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 1)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 1)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				dd_audio_set_clkstop_auxck_all(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(1);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(1);
			}

			dd_audio_set_clkstop_auxck_all(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(net_auck);
			break;

		case DdAudioI2s_MASTER_CLOCK_24_576:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 0)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 2)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				dd_audio_set_clkstop_auxck_all(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(0);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(2);
			}

			dd_audio_set_clkstop_auxck_all(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(net_auck);
			break;

		case DdAudioI2s_MASTER_CLOCK_36_864:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 2)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 0)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				dd_audio_set_clkstop_auxck_all(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(2);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(0);
			}

			dd_audio_set_clkstop_auxck_all(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(net_auck);
			break;

		case DdAudioI2s_MASTER_CLOCK_AUMCLKI:
			break;

		default:
			Ddim_Print(("[DD_AUDIO]dd_audio_set_masterclock: input mclk error : %d\n", mclk));
			return DdAudio_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/**
 * @brief  Set I2S Common Setting
 * @param  UINT8 ch
 * @param  AudioI2sCmmn *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_i2s_ctrl_i2s_cmmn(DdAudioI2s *self, UINT8 ch, AudioI2sCmmn* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	INT32 ret;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if ((ch >= DdAudio_IF_CH4) && (i2s_setting->aumclki == DdAudioI2s_MASTER_CLOCK_AUMCLKI)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Invalid setting ch=%d, aumclki=%d\n", ch, i2s_setting->aumclki));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH1){
		return D_DDIM_OK;
	}
	
	if (priv->gDd_Audio_MasterClock != i2s_setting->aumclki){
		if (i2s_setting->aumclki == DdAudioI2s_MASTER_CLOCK_AUMCLKI){
			// APLCLK -> AUMCLKI
			dd_audio_select_aumclk_in(ch, 1);
		}
		else {
			dd_audio_select_aumclk_in(ch, 0);
		}
		
		Dd_ARM_Dsb_Pou();
		
		ret = dd_audio_set_masterclock(i2s_setting->aumclki);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_masterclock() = %x\n", ret));
			return ret;
		}
		priv->gDd_Audio_I2S_Cmmn[ch]->aumclki = i2s_setting->aumclki;
		priv->gDd_Audio_MasterClock = i2s_setting->aumclki;
	}
	
	if ((priv->gDd_Audio_I2S_Cmmn[ch]->divAumclko != i2s_setting->divAumclko)	||
		(priv->gDd_Audio_I2S_Cmmn[ch]->divAuclk != i2s_setting->divAuclk)		||
		(priv->gDd_Audio_I2S_Cmmn[ch]->divLrclk != i2s_setting->divLrclk)		){
		
		ret = dd_audio_set_enable_clock_division(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_enable_clock_division() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		ret = dd_audio_set_clock_div(ch, i2s_setting->divAumclko, i2s_setting->divAuclk, i2s_setting->divLrclk);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_clock_div() = %x\n", ret));
			return ret;
		}
		else {
			priv->gDd_Audio_I2S_Cmmn[ch]->divAumclko = i2s_setting->divAumclko;
			priv->gDd_Audio_I2S_Cmmn[ch]->divAuclk = i2s_setting->divAuclk;
			priv->gDd_Audio_I2S_Cmmn[ch]->divLrclk = i2s_setting->divLrclk;
		}
	}
	
	if (i2s_setting->masterSlave == DdAudioI2s_CLK_MASTER){
		ret = dd_audio_set_enable_output_clock(ch, DdAudio_ENABLE);
	}
	else if (i2s_setting->masterSlave == DdAudioI2s_CLK_SLAVE){
		ret = dd_audio_set_enable_output_clock(ch, DdAudio_DISABLE);
	}
	else {
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:masterSlave is invalid(=%d)\n", i2s_setting->masterSlave));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Set AUCKOE: ret=%x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_I2S_Cmmn[ch]->masterSlave = i2s_setting->masterSlave;
	}
	
	ret = dd_audio_set_enable_clock_division(ch, i2s_setting->clkDivEnable);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Set DIVE: ret=%x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_I2S_Cmmn[ch]->clkDivEnable = i2s_setting->clkDivEnable;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Common Setting
 * @param  UINT8 ch
 * @param  AudioI2sCmmn *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_i2s_get_ctrl_i2s_cmmn(DdAudioI2s *self, UINT8 ch, AudioI2sCmmn* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_cmmn:input channel error : %d\n", ch));
		*i2s_setting = *priv->gDd_Audio_I2S_Cmmn[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_cmmn:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2s_setting = *priv->gDd_Audio_I2S_Cmmn[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set I2S Setting(Input)
 * @param  UINT8 ch
 * @param  AudioI2sIn *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_i2s_ctrl_i2s_in(DdAudioI2s *self, UINT8 ch, AudioI2sIn* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	INT32 ret;
	UINT8 format;
	
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting->bitIn > DdAudioI2s_BIT_24BIT){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:bitIn error = %d\n", i2s_setting->bitIn));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting->modeIn > DdAudioI2s_MODE_I2S){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:modeIn error = %d\n", i2s_setting->modeIn));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	format = gDd_Audio_AUIF_Tbl[i2s_setting->bitIn][i2s_setting->modeIn];
	
	ret = dd_audio_set_input_data_format(ch, format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]Dd_Audio_Set_Ctrl_I2sIn:dd_audio_set_input_data_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->gDd_Audio_I2S_In[ch]->modeIn = i2s_setting->modeIn;
		priv->gDd_Audio_I2S_In[ch]->bitIn = i2s_setting->bitIn;
	}
	
	if (i2s_setting->bitIn == DdAudioI2s_BIT_24BIT){
		ret = dd_audio_set_enable_in_data24bit(ch, DdAudio_ENABLE);
	}
	else {
		ret = dd_audio_set_enable_in_data24bit(ch, DdAudio_DISABLE);
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:dd_audio_set_enable_in_data24bit() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Setting Information
 * @param  UINT8 ch
 * @param  AudioI2sIn *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_i2s_get_ctrl_i2s_in(DdAudioI2s *self, UINT8 ch, AudioI2sIn* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_in:input channel error : %d\n", ch));
		*i2s_setting = *priv->gDd_Audio_I2S_In[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_in:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2s_setting = *priv->gDd_Audio_I2S_In[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set I2S Setting(Output)
 * @param  UINT8 ch
 * @param  AudioI2sOut *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_i2s_ctrl_i2s_out(DdAudioI2s *self, UINT8 ch, AudioI2sOut* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	INT32 ret;
	UINT8 format;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting->bitOut > DdAudioI2s_BIT_24BIT){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:bitOut error = %d\n", i2s_setting->bitOut));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting->modeOut > DdAudioI2s_MODE_I2S){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:modeOut error = %d\n", i2s_setting->modeOut));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting->fs > DdAudioI2s_FS_128FS){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:fs error = %d\n", i2s_setting->fs));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	format = (gDd_Audio_AUOF_Tbl[i2s_setting->bitOut][i2s_setting->modeOut])[i2s_setting->fs];
	if (0xFF == format){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:AUOF Not Set: bit=%d, mode=%d, fs=%d\n", 
					(int)i2s_setting->bitOut, (int)i2s_setting->modeOut, (int)i2s_setting->fs));
		return DdAudio_SYSTEM_ERROR;
	}
	else {
		ret = dd_audio_set_output_data_format(ch, format);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:dd_audio_set_output_data_format() = %x\n", ret));
			return ret;
		}
		else {
			priv->gDd_Audio_I2S_Out[ch]->modeOut = i2s_setting->modeOut;
			priv->gDd_Audio_I2S_Out[ch]->bitOut = i2s_setting->bitOut;
			priv->gDd_Audio_I2S_Out[ch]->fs = i2s_setting->fs;
		}
	}
	
	if (i2s_setting->bitOut == DdAudioI2s_BIT_24BIT){
		ret = dd_audio_set_enable_out_data24bit(ch, DdAudio_ENABLE);
	}
	else {
		ret = dd_audio_set_enable_out_data24bit(ch, DdAudio_DISABLE);
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:dd_audio_set_enable_out_data24bit() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Setting Information
 * @param  UINT8 ch
 * @param  AudioI2sOut *i2s_setting
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_i2s_get_ctrl_i2s_out(DdAudioI2s *self, UINT8 ch, AudioI2sOut* i2s_setting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_out:input channel error : %d\n", ch));
		*i2s_setting = *priv->gDd_Audio_I2S_Out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2s_setting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_out:i2s_setting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2s_setting = *priv->gDd_Audio_I2S_Out[ch];
	
	return D_DDIM_OK;
}

void dd_audio_i2s_set_master_clock(DdAudioI2s *self, AudioMasterClock clk)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->gDd_Audio_MasterClock = clk;
}

void dd_audio_i2s_cmmn_init(DdAudioI2s *self, UINT8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->gDd_Audio_I2S_Cmmn[ch]->aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	priv->gDd_Audio_I2S_Cmmn[ch]->divAumclko = DdAudioI2s_AUMCLKO_DIV_2;
	priv->gDd_Audio_I2S_Cmmn[ch]->divAuclk = DdAudioI2s_AUCLK_DIV_16;
	priv->gDd_Audio_I2S_Cmmn[ch]->divLrclk = DdAudioI2s_AULR_DIV_32;
	priv->gDd_Audio_I2S_Cmmn[ch]->clkDivEnable = DdAudio_DISABLE;
	priv->gDd_Audio_I2S_Cmmn[ch]->masterSlave = DdAudioI2s_CLK_SLAVE;
}

AudioClkMode dd_audio_i2s_get_cmmn_master_slave(DdAudioI2s *self, UINT8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	return priv->gDd_Audio_I2S_Cmmn[ch]->masterSlave;
}

void dd_audio_i2s_in_init(DdAudioI2s *self, UINT8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->gDd_Audio_I2S_In[ch]->modeIn = DdAudioI2s_MODE_L_JUST;
	priv->gDd_Audio_I2S_In[ch]->bitIn = DdAudioI2s_BIT_8BIT;
}

void dd_audio_i2s_out_init(DdAudioI2s *self, UINT8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->gDd_Audio_I2S_Out[ch]->modeOut = DdAudioI2s_MODE_L_JUST;
	priv->gDd_Audio_I2S_Out[ch]->bitOut = DdAudioI2s_BIT_8BIT;
	priv->gDd_Audio_I2S_Out[ch]->fs = DdAudioI2s_FS_32FS;
}

DdAudioI2s* dd_audio_i2s_new(void)
{
	DdAudioI2s* self = k_object_new_with_private(DD_TYPE_AUDIO_I2S, sizeof(DdAudioI2sPrivate));

	return self;
}

