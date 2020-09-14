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

#ifndef __DD_AUDIO_I2S_H__
#define __DD_AUDIO_I2S_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_AUDIO_I2S				(dd_audio_i2s_get_type())
#define DD_AUDIO_I2S(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdAudioI2s))
#define DD_IS_AUDIO_I2S(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_AUDIO_I2S))


/** Valid Bit Count */
typedef enum {
	DdAudioI2s_BIT_8BIT		= 0,										/**< 8bit */
	DdAudioI2s_BIT_16BIT,												/**< 16bit */
	DdAudioI2s_BIT_24BIT												/**< 24bit */
} AudioBit;

/** I2S Data Format */
typedef enum {
	DdAudioI2s_MODE_L_JUST	= 0,										/**< Left justified */
	DdAudioI2s_MODE_R_JUST,												/**< Right justified */
	DdAudioI2s_MODE_I2S													/**< I2S format */
} AudioMode;

/** I2S master/slave mode */
typedef enum {
	DdAudioI2s_CLK_MASTER = 0,											/**< MASTER */
	DdAudioI2s_CLK_SLAVE												/**< SLAVE */
} AudioClkMode;

/** Serial Clock vs LR Channel Clock */
typedef enum {
	DdAudioI2s_FS_32FS = 0,												/**< 32fs */
	DdAudioI2s_FS_48FS,													/**< 48fs */
	DdAudioI2s_FS_64FS,													/**< 64fs */
	DdAudioI2s_FS_128FS													/**< 128fs */
} AudioFs;

/** Audio Master Clock Setting */
typedef enum {
	DdAudioI2s_MASTER_CLOCK_8_192 = 0,									/**< 8.192MHz */
	DdAudioI2s_MASTER_CLOCK_22_5792,									/**< 22.5792MHz */
	DdAudioI2s_MASTER_CLOCK_24_576,										/**< 24.576MHz */
	DdAudioI2s_MASTER_CLOCK_36_864,										/**< 36.864MHz */
	DdAudioI2s_MASTER_CLOCK_AUMCLKI										/**< AUMCLKI */
} AudioMasterClock;

/** AUMCLKO Clock Division Ratio */
typedef enum {
	DdAudioI2s_AUMCLKO_DIV_1	= 0,									/**< Divide reference clock by 1 */
	DdAudioI2s_AUMCLKO_DIV_2	= 1,									/**< Divide reference clock by 2 */
	DdAudioI2s_AUMCLKO_DIV_4	= 3,									/**< Divide reference clock by 4 */
	DdAudioI2s_AUMCLKO_DIV_6	= 5,									/**< Divide reference clock by 6 */
	DdAudioI2s_AUMCLKO_DIV_8	= 7,									/**< Divide reference clock by 8 */
	DdAudioI2s_AUMCLKO_DIV_10	= 9,									/**< Divide reference clock by 10 */
	DdAudioI2s_AUMCLKO_DIV_12	= 11,									/**< Divide reference clock by 12 */
	DdAudioI2s_AUMCLKO_DIV_14	= 13,									/**< Divide reference clock by 14 */
	DdAudioI2s_AUMCLKO_DIV_16	= 15,									/**< Divide reference clock by 16 */
	DdAudioI2s_AUMCLKO_DIV_18	= 17,									/**< Divide reference clock by 18 */
	DdAudioI2s_AUMCLKO_DIV_20	= 19,									/**< Divide reference clock by 20 */
	DdAudioI2s_AUMCLKO_DIV_22	= 21,									/**< Divide reference clock by 22 */
	DdAudioI2s_AUMCLKO_DIV_24	= 23,									/**< Divide reference clock by 24 */
	DdAudioI2s_AUMCLKO_DIV_26	= 25,									/**< Divide reference clock by 26 */
	DdAudioI2s_AUMCLKO_DIV_28	= 27,									/**< Divide reference clock by 28 */
	DdAudioI2s_AUMCLKO_DIV_30	= 29,									/**< Divide reference clock by 30 */
	DdAudioI2s_AUMCLKO_DIV_32	= 31									/**< Divide reference clock by 32 */
}AudioAumclkoDivClk;

/** AUCLK Clock Division Ratio */
typedef enum {
	DdAudioI2s_AUCLK_DIV_4	= 0,										/**< Divide AUMCLKO clock by 4 */
	DdAudioI2s_AUCLK_DIV_8,												/**< Divide AUMCLKO clock by 8 */
	DdAudioI2s_AUCLK_DIV_12,											/**< Divide AUMCLKO clock by 12 */
	DdAudioI2s_AUCLK_DIV_16,											/**< Divide AUMCLKO clock by 16 */
	DdAudioI2s_AUCLK_DIV_20,											/**< Divide AUMCLKO clock by 20 */
	DdAudioI2s_AUCLK_DIV_24,											/**< Divide AUMCLKO clock by 24 */
	DdAudioI2s_AUCLK_DIV_28,											/**< Divide AUMCLKO clock by 28 */
	DdAudioI2s_AUCLK_DIV_32												/**< Divide AUMCLKO clock by 32 */
}AudioAuclkDivClk;

/** AULR Clock Division Ratio */
typedef enum {
	DdAudioI2s_AULR_DIV_16	= 0,										/**< Divide AUCLK clock by 16 */
	DdAudioI2s_AULR_DIV_32,												/**< Divide AUCLK clock by 32 */
	DdAudioI2s_AULR_DIV_48,												/**< Divide AUCLK clock by 48 */
	DdAudioI2s_AULR_DIV_64												/**< Divide AUCLK clock by 64 */
}AudioAulrDivClk;

typedef struct _AudioI2sCmmn	AudioI2sCmmn;
typedef struct _AudioI2sIn 		AudioI2sIn;
typedef struct _AudioI2sOut 	AudioI2sOut;

/** Audio I2S Control(Common) */
struct _AudioI2sCmmn {
	AudioMasterClock	aumclki;									/**< Audio Master Clock(input)<BR><BR>
																	Default value : @ref DdAudioI2s_MASTER_CLOCK_8_192 */
	AudioAumclkoDivClk	divAumclko;								/**< AUMCLKO Output Clock Division Ratio<BR><BR>
																	Default value : @ref DdAudioI2s_AUMCLKO_DIV_2 */
	AudioAuclkDivClk	divAuclk;									/**< AUCLK Output Clock Division Ratio<BR><BR>
																	Default value : DdAudioI2s_AUCLK_DIV_16 */
	AudioAulrDivClk		divLrclk;									/**< AULR Output Clock Division Ratio<BR><BR>
																	Default value : DdAudioI2s_AULR_DIV_32 */
	kuint8				clkDivEnable;								/**< Clock division enable <BR><BR>
																	 Value Range:DdAudio_DISABLE / DdAudio_ENABLE<BR>
																	 <ul><li>@ref DdAudio_DISABLE
																	 <li>@ref DdAudio_ENABLE</ul>	*/
	AudioClkMode		masterSlave;								/**< Master/Slave setting of clock<BR><BR>
																	Default value : DdAudioI2s_CLK_SLAVE */
};

/** Audio I2S Control(Input) */
struct _AudioI2sIn {
	AudioMode	modeIn;									/**< Input Data Format<BR><BR>
														Default value : @ref DdAudioI2s_MODE_L_JUST */
	AudioBit	bitIn;									/**< Valid Bit of Input Data<BR><BR>
														Default value : DdAudioI2s_BIT_8BIT */
};

/** Audio I2S Control(Input) */
struct _AudioI2sOut {
	AudioMode	modeOut;									/**< Output Data Format<BR><BR>
															Default value : @ref DdAudioI2s_MODE_L_JUST */
	AudioBit	bitOut;									/**< Valid Bit of Output Data<BR><BR>
															Default value : DdAudioI2s_BIT_8BIT */
	AudioFs		fs;											/**< AUCLK(sirial clock) vs AULRO(LR channel clock)<BR><BR>
															Default value : DdAudioI2s_FS_32FS */
};


typedef struct _DdAudioI2s 			DdAudioI2s;
typedef struct _DdAudioI2sPrivate 	DdAudioI2sPrivate;

struct  _DdAudioI2s {
	KObject parent;
};


#ifdef __cplusplus
extern "C" {
#endif


KConstType 		dd_audio_i2s_get_type(void);
DdAudioI2s* 	dd_audio_i2s_new(void);

/**
Set I2S control information(Common Clock Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	i2sSetting	I2S control information. See @ref AudioI2sCmmn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
@remarks This API uses DDIM_User_Dly_Tsk().
*/
kint32			dd_audio_i2s_ctrl_i2s_cmmn(DdAudioI2s *self, kuint8 ch, AudioI2sCmmn* i2sSetting);

/**
Get I2S control information(Common Clock Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[out]	i2sSetting	I2S control information. See @ref AudioI2sCmmn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_i2s_get_ctrl_i2s_cmmn(DdAudioI2s *self, kuint8 ch, AudioI2sCmmn* i2sSetting);

/**
Set I2S control information(Input Data Setting)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[in]	i2sSetting	I2S control information. See @ref AudioI2sIn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32			dd_audio_i2s_ctrl_i2s_in(DdAudioI2s *self, kuint8 ch, AudioI2sIn* i2sSetting);

/**
Get I2S control information(Input Data Setting)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH4
							<li>@ref DdAudio_IF_CH5</ul>
@param[out]	i2sSetting	I2S control information. See @ref AudioI2sIn
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_i2s_get_ctrl_i2s_in(DdAudioI2s *self, kuint8 ch, AudioI2sIn* i2sSetting);

/**
Set I2S control information(Output Data Setting)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[in]	i2sSetting	I2S control information. See @ref AudioI2sOut
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
@retval DdAudio_SYSTEM_ERROR			System Error
*/
kint32			dd_audio_i2s_ctrl_i2s_out(DdAudioI2s *self, kuint8 ch, AudioI2sOut* i2sSetting);

/**
Get I2S control information(Output Data Setting)<br>
@param[in]	ch	channel
						<ul><li>@ref DdAudio_IF_CH0
							<li>@ref DdAudio_IF_CH1
							<li>@ref DdAudio_IF_CH2
							<li>@ref DdAudio_IF_CH3</ul>
@param[out]	i2sSetting	I2S control information. See @ref AudioI2sOut
@retval D_DDIM_OK						OK
@retval DdAudio_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 			dd_audio_i2s_get_ctrl_i2s_out(DdAudioI2s *self, kuint8 ch, AudioI2sOut* i2sSetting);

void 			dd_audio_i2s_set_master_clock(DdAudioI2s *self, AudioMasterClock clk);
void 			dd_audio_i2s_cmmn_init(DdAudioI2s *self, kuint8 ch);
AudioClkMode 	dd_audio_i2s_get_cmmn_master_slave(DdAudioI2s *self, kuint8 ch);
void 			dd_audio_i2s_in_init(DdAudioI2s *self, kuint8 ch);
void 			dd_audio_i2s_out_init(DdAudioI2s *self, kuint8 ch);


#ifdef __cplusplus
}
#endif

#endif	// __DD_AUDIO_I2S_H__

