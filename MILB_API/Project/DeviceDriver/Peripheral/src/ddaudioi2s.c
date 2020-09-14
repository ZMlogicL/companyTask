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
#include "ddarm.h"
#include "ddaudio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudioI2s, dd_audio_i2s);
#define DD_AUDIO_I2S_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioI2sPrivate, DD_TYPE_AUDIO_I2S))


struct _DdAudioI2sPrivate
{
	volatile AudioMasterClock masterClock;
	volatile AudioI2sCmmn cmmnData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sIn inData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sOut outData[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sCmmn *cmmn[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sIn *in[DdAudio_IF_CH_NUM_MAX];
	volatile AudioI2sOut *out[DdAudio_IF_CH_NUM_MAX];
};


static const kuint8	S_DD_AUDIO_AUOF_TBL_8_L[4] =			// 8bit Left-Justified
{
	0x00,				// 32FS
	0x10,				// 48FS
	0x01,				// 64FS
	0x20				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_8_R[4] =			// 8bit Right-Justified
{
	0x02,				// 32FS
	0x12,				// 48FS
	0x03,				// 64FS
	0x22				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_8_I2S[4] =			// 8bit I2S
{
	0x40,				// 32FS
	0x50,				// 48FS
	0x41,				// 64FS
	0x60				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_16_L[4] =			// 16bit Left-Justified
{
	0x04,				// 32FS
	0x14,				// 48FS
	0x05,				// 64FS
	0x24				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_16_R[4] =			// 16bit Right-Justified
{
	0x06,				// 32FS
	0x17,				// 48FS
	0x07,				// 64FS
	0x27				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_16_I2S[4] =			// 16bit I2S
{
	0x44,				// 32FS
	0x54,				// 48FS
	0x45,				// 64FS
	0x64				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_24_L[4] =			// 24bit Left-Justified
{
	0xFF,				// 32FS
	0x18,				// 48FS
	0x09,				// 64FS
	0x28				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_24_R[4] =			// 24bit Right-Justified
{
	0xFF,				// 32FS
	0x1A,				// 48FS
	0x0B,				// 64FS
	0x2B				// 128FS
};

static const kuint8	S_DD_AUDIO_AUOF_TBL_24_I2S[4] =			// 24bit I2S
{
	0xFF,				// 32FS
	0x58,				// 48FS
	0x49,				// 64FS
	0x68				// 128FS
};

static const kuint8	*S_DD_AUDIO_AUOF_TBL[3][3] =			// index [bits][mode]
{
	//	L							R							I2S
	{	S_DD_AUDIO_AUOF_TBL_8_L,		S_DD_AUDIO_AUOF_TBL_8_R,		S_DD_AUDIO_AUOF_TBL_8_I2S	},	// 8bit
	{	S_DD_AUDIO_AUOF_TBL_16_L,	S_DD_AUDIO_AUOF_TBL_16_R,	S_DD_AUDIO_AUOF_TBL_16_I2S	},	// 16bit
	{	S_DD_AUDIO_AUOF_TBL_24_L,	S_DD_AUDIO_AUOF_TBL_24_R,	S_DD_AUDIO_AUOF_TBL_24_I2S	}	// 24bit
};

static const kuint8	S_DD_AUDIO_AUIF_TBL[3][3] =				// index [bits][mode]
{
	//  L       R       I2S
	{	0x00,	0x01,	0x08	},		// 8bit
	{	0x02,	0x03,	0x0A	},		// 16bit
	{	0x04,	0x05,	0x0C	}		// 24bit
};


static kint32 ddAudioSetEnableInData24bit(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetEnableOutData24bit(kuint8 ch, kuint8 enable);
static kint32 ddAudioSetInputDataFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetOutputDataFormat(kuint8 ch, kuint8 format);
static kint32 ddAudioSetClockDiv(kuint8 ch, kuint8 mclock, kuint8 auclock, kuint8 lrclock);
static kint32 ddAudioSetEnableClockDivision(kuint8 ch, kuint8 enable);
static kboolean ddAudioGetEnableClockDivision(kuint8 ch);
static kint32 ddAudioSetEnableOutputClock(kuint8 ch, kuint8 enable);
static void ddAudioSetClkstopAuxck(kuint8 ch, kuint8 val);
static void ddAudioSetClkstopAuxckAll(kuint8 val);
static void ddAudioSetClkselAuxsel(kuint8 ch, kuint8 val);
static void ddAudioSelectAumclkIn(kuint8 ch, kuint8 val);
static kint32 ddAudioSetMasterclock(AudioMasterClock mclk);


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

		priv->cmmn[i] = &priv->cmmnData[i];
		priv->in[i] = &priv->inData[i];
		priv->out[i] = &priv->outData[i];
	}

	priv->masterClock = (AudioMasterClock)0xFF;
}

static void dd_audio_i2s_destructor(DdAudioI2s *self)
{

}

/**
 * @brief  Set register AUIDSEL.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableInData24bit(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;
	aucr.bit.auidsel = enable;
	ioAudio.audioif[ch].aucr.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register AUODSEL.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableOutData24bit(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;
	aucr.bit.auodsel = enable;
	ioAudio.audioif[ch].aucr.word = aucr.word;

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return D_DDIM_OK;
}

/**
 * @brief  Set register AUIF.
 * @param  kuint8 ch
 * @param  kuint8 format
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetInputDataFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.auif != format){						/* pgr0872 */
		if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUIF Error:AUIEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.auif = format;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUOF.
 * @param  kuint8 ch
 * @param  kuint8 format
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetOutputDataFormat(kuint8 ch, kuint8 format)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucr aucr;
	kint32 retVal = D_DDIM_OK;

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

	aucr.word = ioAudio.audioif[ch].aucr.word;

	if (aucr.bit.auof != format){								/* pgr0872 */
		if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUOF Error:AUOEF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
			Ddim_Print(("[DD_AUDIO]Set AUOF Error:LBF = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucr.bit.auof = format;
			ioAudio.audioif[ch].aucr.word = aucr.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Get register DIVE.
 * @param  kuint8 ch
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kboolean ddAudioGetEnableClockDivision(kuint8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get DIVE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ioAudio.audioif[ch].aucc.bit.dive == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Set register DIVMCK/DIVCK/DIVLR.
 * @param  kuint8 ch
 * @param  kuint8 mclock
 * @param  kuint8 auclock
 * @param  kuint8 lrclock
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetClockDiv(kuint8 ch, kuint8 mclock, kuint8 auclock, kuint8 lrclock)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucc aucc;
	kint32 retVal = D_DDIM_OK;

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

	aucc.word = ioAudio.audioif[ch].aucc.word;

	if ((aucc.bit.divmck != mclock)	||				/* pgr0872 */
		(aucc.bit.divck != auclock)	||				/* pgr0872 */
		(aucc.bit.divlr != lrclock)	){				/* pgr0872 */

		if (ddAudioGetEnableClockDivision(ch) != FALSE){
			Ddim_Assertion(("[DD_AUDIO]Set DIVCLK Error:DIVE = 1\n"));
			retVal = DdAudio_SYSTEM_ERROR;
		}
		else {
			aucc.bit.divmck = mclock;
			aucc.bit.divck = auclock;
			aucc.bit.divlr = lrclock;
			ioAudio.audioif[ch].aucc.word = aucc.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register DIVE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableClockDivision(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucc aucc;
	kint32 retVal = D_DDIM_OK;
	volatile kuint32 waitCounter;

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

	aucc.word = ioAudio.audioif[ch].aucc.word;

	if (aucc.bit.dive != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:AUIEF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:AUOEF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set DIVE Error:LBF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucc.bit.dive = enable;
				ioAudio.audioif[ch].aucc.word = aucc.word;
			}
		}
		else {
			aucc.bit.dive = enable;
			ioAudio.audioif[ch].aucc.word = aucc.word;
		}
	}

	Dd_ARM_Dsb_Pou();

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

//	printf("[Set]DIVE%d=%d\n", ch, ioAudio.audioif[ch].aucc.bit.dive);
//	printf("[Set]DIVE%d=%d\n", ch, aucc.bit.dive);

	// wait DIVE readable
	if (ioAudio.audioif[ch].aucc.bit.dive != aucc.bit.dive){
		waitCounter = 0;
		while (ioAudio.audioif[ch].aucc.bit.dive != aucc.bit.dive){
			DDIM_User_Dly_Tsk(0);

			if (waitCounter > 10){
				Ddim_Print(("[DD_AUDIO]DIVE not read correct value\n"));
				break;
			}
			waitCounter++;
		}
	}

	return retVal;
}

/**
 * @brief  Set register AUCKOE.
 * @param  kuint8 ch
 * @param  kuint8 enable
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetEnableOutputClock(kuint8 ch, kuint8 enable)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);
	volatile IoAudioAucc aucc;
	kint32 retVal = D_DDIM_OK;

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

	aucc.word = ioAudio.audioif[ch].aucc.word;

	if (aucc.bit.auckoe != enable){								/* pgr0872 */
		if (enable == DdAudio_ENABLE){
			if (dd_audio_get_audio_in_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:AUIEF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_audio_out_enable_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:AUOEF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else if (dd_audio_get_loopback_flag(ddAudio, ch) != FALSE){
				Ddim_Print(("[DD_AUDIO]Set AUCKOE Error:LBF = 1\n"));
				retVal = DdAudio_SYSTEM_ERROR;
			}
			else {
				aucc.bit.auckoe = enable;
				ioAudio.audioif[ch].aucc.word = aucc.word;
			}
		}
		else {
			aucc.bit.auckoe = enable;
			ioAudio.audioif[ch].aucc.word = aucc.word;
		}
	}

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);

	return retVal;
}

/**
 * @brief  Set register AUxCK.
 * @param  kuint8 ch
 * @param  kuint8 val[1:stop/0:supply]
 */
static void ddAudioSetClkstopAuxck(kuint8 ch, kuint8 val)
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
 * @param  kuint8 val[1:stop/0:supply]
 */
static void ddAudioSetClkstopAuxckAll(kuint8 val)
{
	Dd_Top_Set_CLKSTOP1_AU0CK(val);
	Dd_Top_Set_CLKSTOP1_AU2CK(val);
	Dd_Top_Set_CLKSTOP1_AU3CK(val);
	Dd_Top_Set_CLKSTOP1_AU4CK(val);
	Dd_Top_Set_CLKSTOP1_AU5CK(val);
}

/**
 * @brief  Set register AUCKSEL.
 * @param  kuint8 ch
 * @param  kuint8 val
 */
static void ddAudioSetClkselAuxsel(kuint8 ch, kuint8 val)
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
 * @param  kuint8 ch
 * @param  kuint8 val
 */
static void ddAudioSelectAumclkIn(kuint8 ch, kuint8 val)
{
	DdAudio* ddAudio = dd_audio_get();
	kulong* pSpinLock = dd_audio_get_spin_lock_addr(ddAudio);

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

	ddAudioSetClkstopAuxck(ch, 1);
	ddAudioSetClkselAuxsel(ch, val);
	ddAudioSetClkstopAuxck(ch, 0);

	// SpinUnLock
	Dd_ARM_Critical_Section_End(*pSpinLock);
}

/**
 * @brief  Set AudioMasterClock.
 * @param  AudioMasterClock mclk
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static kint32 ddAudioSetMasterclock(AudioMasterClock mclk)
{
/*
	MCLK[MHz]	|	AUCLK	|	P10APLLDIV
	--------------------------------------
	8.192		|	3		|	0
	22.5792		|	1		|	1
	24.576		|	2		|	0
	36.864		|	0		|	2
*/

	volatile kuint8 netAuck;

	if (Dd_Top_Get_PLLCNT1_PL10ST() == 0){
		Ddim_Print(("[DD_AUDIO]dd_audio_set_masterclock:PLL10 is not started. \n"));
		return DdAudio_SYSTEM_ERROR;
	}

	netAuck = Dd_Top_Get_CLKSTOP1_NETAUCK();

	switch (mclk){
		case DdAudioI2s_MASTER_CLOCK_8_192:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 0)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 3)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				ddAudioSetClkstopAuxckAll(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(0);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(3);
			}

			ddAudioSetClkstopAuxckAll(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(netAuck);
			break;

		case DdAudioI2s_MASTER_CLOCK_22_5792:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 1)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 1)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				ddAudioSetClkstopAuxckAll(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(1);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(1);
			}

			ddAudioSetClkstopAuxckAll(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(netAuck);
			break;

		case DdAudioI2s_MASTER_CLOCK_24_576:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 0)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 2)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				ddAudioSetClkstopAuxckAll(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(0);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(2);
			}

			ddAudioSetClkstopAuxckAll(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(netAuck);
			break;

		case DdAudioI2s_MASTER_CLOCK_36_864:
			if ((Dd_Top_Get_PLLCNT9_P10APLLDIV() != 2)	||
				(Dd_Top_Get_CLKSEL8_AUCLK() != 0)		||
				(Dd_Top_Get_PLLCNT2_PL10ASEL() == 0)	){

				ddAudioSetClkstopAuxckAll(1);
				Dd_Top_Set_CLKSTOP1_NETAUCK(1);
				Dd_Top_Stop_Pll10A();
				DdAudio_WAIT_USEC(6);			// wait 6us
				Dd_Top_Set_PLLCNT9_P10APLLDIV(2);
				Dd_Top_Start_Pll10A();
				Dd_Top_Set_CLKSEL8_AUCLK(0);
			}

			ddAudioSetClkstopAuxckAll(0);
			Dd_Top_Set_CLKSTOP1_NETAUCK(netAuck);
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
 * @param  kuint8 ch
 * @param  AudioI2sCmmn *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_i2s_ctrl_i2s_cmmn(DdAudioI2s *self, kuint8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	kint32 ret;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if ((ch >= DdAudio_IF_CH4) && (i2sSetting->aumclki == DdAudioI2s_MASTER_CLOCK_AUMCLKI)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Invalid setting ch=%d, aumclki=%d\n", ch, i2sSetting->aumclki));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
#endif	// CO_PARAM_CHECK
	
	if (ch == DdAudio_IF_CH1){
		return D_DDIM_OK;
	}
	
	if (priv->masterClock != i2sSetting->aumclki){
		if (i2sSetting->aumclki == DdAudioI2s_MASTER_CLOCK_AUMCLKI){
			// APLCLK -> AUMCLKI
			ddAudioSelectAumclkIn(ch, 1);
		}
		else {
			ddAudioSelectAumclkIn(ch, 0);
		}
		
		Dd_ARM_Dsb_Pou();
		
		ret = ddAudioSetMasterclock(i2sSetting->aumclki);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_masterclock() = %x\n", ret));
			return ret;
		}
		priv->cmmn[ch]->aumclki = i2sSetting->aumclki;
		priv->masterClock = i2sSetting->aumclki;
	}
	
	if ((priv->cmmn[ch]->divAumclko != i2sSetting->divAumclko)	||
		(priv->cmmn[ch]->divAuclk != i2sSetting->divAuclk)		||
		(priv->cmmn[ch]->divLrclk != i2sSetting->divLrclk)		){
		
		ret = ddAudioSetEnableClockDivision(ch, DdAudio_DISABLE);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_enable_clock_division() = %x\n", ret));
			return ret;
		}
		
		Dd_ARM_Dsb_Pou();
		
		ret = ddAudioSetClockDiv(ch, i2sSetting->divAumclko, i2sSetting->divAuclk, i2sSetting->divLrclk);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:dd_audio_set_clock_div() = %x\n", ret));
			return ret;
		}
		else {
			priv->cmmn[ch]->divAumclko = i2sSetting->divAumclko;
			priv->cmmn[ch]->divAuclk = i2sSetting->divAuclk;
			priv->cmmn[ch]->divLrclk = i2sSetting->divLrclk;
		}
	}
	
	if (i2sSetting->masterSlave == DdAudioI2s_CLK_MASTER){
		ret = ddAudioSetEnableOutputClock(ch, DdAudio_ENABLE);
	}
	else if (i2sSetting->masterSlave == DdAudioI2s_CLK_SLAVE){
		ret = ddAudioSetEnableOutputClock(ch, DdAudio_DISABLE);
	}
	else {
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:masterSlave is invalid(=%d)\n", i2sSetting->masterSlave));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Set AUCKOE: ret=%x\n", ret));
		return ret;
	}
	else {
		priv->cmmn[ch]->masterSlave = i2sSetting->masterSlave;
	}
	
	ret = ddAudioSetEnableClockDivision(ch, i2sSetting->clkDivEnable);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_cmmn:Set DIVE: ret=%x\n", ret));
		return ret;
	}
	else {
		priv->cmmn[ch]->clkDivEnable = i2sSetting->clkDivEnable;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Common Setting
 * @param  kuint8 ch
 * @param  AudioI2sCmmn *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_i2s_get_ctrl_i2s_cmmn(DdAudioI2s *self, kuint8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_cmmn:input channel error : %d\n", ch));
		*i2sSetting = *priv->cmmn[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_cmmn:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2sSetting = *priv->cmmn[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set I2S Setting(Input)
 * @param  kuint8 ch
 * @param  AudioI2sIn *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_i2s_ctrl_i2s_in(DdAudioI2s *self, kuint8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	kint32 ret;
	kuint8 format;
	
#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting->bitIn > DdAudioI2s_BIT_24BIT){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:bitIn error = %d\n", i2sSetting->bitIn));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting->modeIn > DdAudioI2s_MODE_I2S){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:modeIn error = %d\n", i2sSetting->modeIn));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	format = S_DD_AUDIO_AUIF_TBL[i2sSetting->bitIn][i2sSetting->modeIn];
	
	ret = ddAudioSetInputDataFormat(ch, format);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]Dd_Audio_Set_Ctrl_I2sIn:dd_audio_set_input_data_format() = %x\n", ret));
		return ret;
	}
	else {
		priv->in[ch]->modeIn = i2sSetting->modeIn;
		priv->in[ch]->bitIn = i2sSetting->bitIn;
	}
	
	if (i2sSetting->bitIn == DdAudioI2s_BIT_24BIT){
		ret = ddAudioSetEnableInData24bit(ch, DdAudio_ENABLE);
	}
	else {
		ret = ddAudioSetEnableInData24bit(ch, DdAudio_DISABLE);
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_in:dd_audio_set_enable_in_data24bit() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Setting Information
 * @param  kuint8 ch
 * @param  AudioI2sIn *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_i2s_get_ctrl_i2s_in(DdAudioI2s *self, kuint8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_in:input channel error : %d\n", ch));
		*i2sSetting = *priv->in[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_in:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2sSetting = *priv->in[ch];
	
	return D_DDIM_OK;
}

/**
 * @brief  Set I2S Setting(Output)
 * @param  kuint8 ch
 * @param  AudioI2sOut *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
kint32 dd_audio_i2s_ctrl_i2s_out(DdAudioI2s *self, kuint8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);
	kint32 ret;
	kuint8 format;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting->bitOut > DdAudioI2s_BIT_24BIT){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:bitOut error = %d\n", i2sSetting->bitOut));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting->modeOut > DdAudioI2s_MODE_I2S){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:modeOut error = %d\n", i2sSetting->modeOut));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting->fs > DdAudioI2s_FS_128FS){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:fs error = %d\n", i2sSetting->fs));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	format = (S_DD_AUDIO_AUOF_TBL[i2sSetting->bitOut][i2sSetting->modeOut])[i2sSetting->fs];
	if (0xFF == format){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:AUOF Not Set: bit=%d, mode=%d, fs=%d\n", 
					(int)i2sSetting->bitOut, (int)i2sSetting->modeOut, (int)i2sSetting->fs));
		return DdAudio_SYSTEM_ERROR;
	}
	else {
		ret = ddAudioSetOutputDataFormat(ch, format);
		if (ret != D_DDIM_OK){
			Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:dd_audio_set_output_data_format() = %x\n", ret));
			return ret;
		}
		else {
			priv->out[ch]->modeOut = i2sSetting->modeOut;
			priv->out[ch]->bitOut = i2sSetting->bitOut;
			priv->out[ch]->fs = i2sSetting->fs;
		}
	}
	
	if (i2sSetting->bitOut == DdAudioI2s_BIT_24BIT){
		ret = ddAudioSetEnableOutData24bit(ch, DdAudio_ENABLE);
	}
	else {
		ret = ddAudioSetEnableOutData24bit(ch, DdAudio_DISABLE);
	}
	
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_i2s_ctrl_i2s_out:dd_audio_set_enable_out_data24bit() = %x\n", ret));
		return ret;
	}
	
	return D_DDIM_OK;
}

/**
 * @brief  Get I2S Setting Information
 * @param  kuint8 ch
 * @param  AudioI2sOut *i2sSetting
 * @return kint32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
kint32 dd_audio_i2s_get_ctrl_i2s_out(DdAudioI2s *self, kuint8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_out:input channel error : %d\n", ch));
		*i2sSetting = *priv->out[0];
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (i2sSetting == NULL){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_i2s_get_ctrl_i2s_out:i2sSetting = NULL\n"));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	*i2sSetting = *priv->out[ch];
	
	return D_DDIM_OK;
}

void dd_audio_i2s_set_master_clock(DdAudioI2s *self, AudioMasterClock clk)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->masterClock = clk;
}

void dd_audio_i2s_cmmn_init(DdAudioI2s *self, kuint8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->cmmn[ch]->aumclki = DdAudioI2s_MASTER_CLOCK_8_192;
	priv->cmmn[ch]->divAumclko = DdAudioI2s_AUMCLKO_DIV_2;
	priv->cmmn[ch]->divAuclk = DdAudioI2s_AUCLK_DIV_16;
	priv->cmmn[ch]->divLrclk = DdAudioI2s_AULR_DIV_32;
	priv->cmmn[ch]->clkDivEnable = DdAudio_DISABLE;
	priv->cmmn[ch]->masterSlave = DdAudioI2s_CLK_SLAVE;
}

AudioClkMode dd_audio_i2s_get_cmmn_master_slave(DdAudioI2s *self, kuint8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	return priv->cmmn[ch]->masterSlave;
}

void dd_audio_i2s_in_init(DdAudioI2s *self, kuint8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->in[ch]->modeIn = DdAudioI2s_MODE_L_JUST;
	priv->in[ch]->bitIn = DdAudioI2s_BIT_8BIT;
}

void dd_audio_i2s_out_init(DdAudioI2s *self, kuint8 ch)
{
	DdAudioI2sPrivate *priv = DD_AUDIO_I2S_GET_PRIVATE(self);

	priv->out[ch]->modeOut = DdAudioI2s_MODE_L_JUST;
	priv->out[ch]->bitOut = DdAudioI2s_BIT_8BIT;
	priv->out[ch]->fs = DdAudioI2s_FS_32FS;
}

DdAudioI2s* dd_audio_i2s_new(void)
{
	DdAudioI2s* self = k_object_new_with_private(DD_TYPE_AUDIO_I2S, sizeof(DdAudioI2sPrivate));

	return self;
}

