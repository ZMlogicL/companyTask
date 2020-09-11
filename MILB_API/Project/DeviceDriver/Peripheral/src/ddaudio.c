/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月4日
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
#include "dd_top.h"
#include "ddim_user_custom.h"
#include "ddaudio.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdAudio, dd_audio);
#define DD_AUDIO_GET_PRIVATE(o) (K_TYPE_INSTANCE_GET_PRIVATE ((o), DdAudioPrivate, DD_TYPE_AUDIO))


struct _DdAudioPrivate
{
	DdAudioCtrl* audioCtrl;
	DdAudioDma* audioDma;
	DdAudioI2s* audioI2s;
	DdAudioIo* audioIo;
	DdAudioLoopback* audioLoopBack;
	DdAudioReg* audioReg;
	volatile DdAudioRegFunc gDd_Audio_OverFlow_Callback_Func[DdAudio_IF_CH_NUM_MAX];
	volatile DdAudioRegFunc gDd_Audio_Input_Callback_Func[DdAudio_IF_CH_NUM_MAX];
	volatile DdAudioRegFunc gDd_Audio_Output_Callback_Func[DdAudio_IF_CH_NUM_MAX];
};


static 	ULONG gDd_Audio_Spin_Lock __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;


static INT32 dd_audio_set_sw_reset(UINT8 ch);
static BOOL dd_audio_get_in_full(UINT8 ch);
static BOOL dd_audio_get_out_empty(UINT8 ch);
static BOOL dd_audio_get_in_overflow_flag(UINT8 ch);
static BOOL dd_audio_get_out_underflow_flag(UINT8 ch);
static BOOL dd_audio_get_enable_in_overflow_intr(UINT8 ch);
static BOOL dd_audio_get_enable_out_underflow_intr(UINT8 ch);
static BOOL dd_audio_get_in_usage_flag(UINT8 ch);
static BOOL dd_audio_get_out_usage_flag(UINT8 ch);


static void dd_audio_constructor(DdAudio *self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	int i;

	for(i = 0; i < DdAudio_IF_CH_NUM_MAX; i++)
	{
		priv->gDd_Audio_OverFlow_Callback_Func[i] = NULL;
		priv->gDd_Audio_Input_Callback_Func[i] = NULL;
		priv->gDd_Audio_Output_Callback_Func[i] = NULL;
	}

	priv->audioCtrl = dd_audio_ctrl_new();
	priv->audioDma = dd_audio_dma_new();
	priv->audioI2s = dd_audio_i2s_new();
	priv->audioIo = dd_audio_io_new();
	priv->audioLoopBack = dd_audio_loopback_new();
	priv->audioReg = dd_audio_reg_new();
}

static void dd_audio_destructor(DdAudio *self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	if(priv->audioCtrl)
	{
		k_object_unref(priv->audioCtrl);
		priv->audioCtrl = NULL;
	}

	if(priv->audioDma)
	{
		k_object_unref(priv->audioDma);
		priv->audioDma = NULL;
	}

	if(priv->audioI2s)
	{
		k_object_unref(priv->audioI2s);
		priv->audioI2s = NULL;
	}

	if(priv->audioIo)
	{
		k_object_unref(priv->audioIo);
		priv->audioIo = NULL;
	}

	if(priv->audioLoopBack)
	{
		k_object_unref(priv->audioLoopBack);
		priv->audioLoopBack = NULL;
	}

	if(priv->audioReg)
	{
		k_object_unref(priv->audioReg);
		priv->audioReg = NULL;
	}
}

/**
 * @brief  Reset Audio Interface.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
static INT32 dd_audio_set_sw_reset(UINT8 ch)
{
	volatile union io_audio_aures aures;
	
	aures.word = IO_AUDIO.AUDIOIF_CTRL.AURES.word;
	
	switch (ch){
		case DdAudio_IF_CH0 :
			aures.bit.AUIF0_RST = 1;
			break;
		case DdAudio_IF_CH1 :
			aures.bit.AUIF1_RST = 1;
			break;
		case DdAudio_IF_CH2 :
			aures.bit.AUIF2_RST = 1;
			break;
		case DdAudio_IF_CH3 :
			aures.bit.AUIF3_RST = 1;
			break;
		case DdAudio_IF_CH4 :
			aures.bit.AUIF4_RST = 1;
			break;
		case DdAudio_IF_CH5 :
			aures.bit.AUIF5_RST = 1;
			break;
		default :
#ifdef CO_PARAM_CHECK
			Ddim_Assertion(("[DD_AUDIO]]AUDIO Reset:input channel error : %d\n", ch));
#endif	// CO_PARAM_CHECK
			return DdAudio_INPUT_PARAM_ERROR;
	}
	
	// bit6 = 0
	aures.word &= 0x3F;
	
	// SpinLock
	Dd_ARM_Critical_Section_Start(gDd_Audio_Spin_Lock);
	
	IO_AUDIO.AUDIOIF_CTRL.AURES.word = aures.word;
	IO_AUDIO.AUDIOIF_CTRL.AURES.word = 0;
	
	// SpinUnLock
	Dd_ARM_Critical_Section_End(gDd_Audio_Spin_Lock);
	
	return D_DDIM_OK;
}

/**
 * @brief  Get register INTI.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_in_full(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTI:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTI == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTO.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_out_empty(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTO:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTO == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register IROF.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_in_overflow_flag(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get IROF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.IROF == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register ORUF.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_out_underflow_flag(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get ORUF:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.ORUF == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register OFIE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_enable_in_overflow_intr(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get OFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.OFIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register UFIE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
static BOOL dd_audio_get_enable_out_underflow_intr(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get UFIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.UFIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTI.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_in_usage_flag(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTI:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTI == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTO.
 * @param  UINT8 ch
 * @return TRUE/FALSE
 */
static BOOL dd_audio_get_out_usage_flag(UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTO:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK
	
	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTO == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTOE.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
BOOL dd_audio_get_enable_out_empty_intr(DdAudio* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTOE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register INTIE.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
BOOL dd_audio_get_enable_in_full_intr(DdAudio* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get INTIE:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUCR.bit.INTIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTIE.
 * @param  UINT8 ch
 * @return BOOL TRUE/FALSE
 */
BOOL dd_audio_get_enable_in_usage_intr(DdAudio* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTIE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTIE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

/**
 * @brief  Get register EINTOE.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR
 */
BOOL dd_audio_get_enable_out_usage_intr(DdAudio* self, UINT8 ch)
{
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]Get EINTOE:input channel error : %d\n", ch));
		return FALSE;
	}
#endif	// CO_PARAM_CHECK

	if (IO_AUDIO.AUDIOIF[ch].AUST.bit.EINTOE == 1){
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL dd_audio_get_loopback_flag(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_flag_get(priv->audioLoopBack, ch);
}

/**
 * @brief  The audio input channel is exclusively controlled.
 * @param  UINT8 ch
 * @param  INT32 tmout
 * @return INT32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR/DdAudio_SEM_TIMEOUT
 */
INT32 dd_audio_open_input(DdAudio* self, UINT8 ch, INT32 tmout)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_input:input timeout error : %d\n", tmout));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == D_DDIM_USER_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_AUDIO_IF_IN(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_AUDIO_IF_IN(ch), (DDIM_USER_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case D_DDIM_USER_E_OK:
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
			return DdAudio_SEM_TIMEOUT;
		default:
			return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The audio output channel is exclusively controlled.
 * @param  UINT8 ch
 * @param  INT32 tmout
 * @return INT32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR/DdAudio_SEM_TIMEOUT
 */
INT32 dd_audio_open_output(DdAudio* self, UINT8 ch, INT32 tmout)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
	
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_open_output:input timeout error : %d\n", tmout));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	
	// Exclusive check
	if (tmout == D_DDIM_USER_SEM_WAIT_POL){
		ercd = DDIM_User_Pol_Sem(SID_DD_AUDIO_IF_OUT(ch));							// pol_sem()
	}
	else {
		ercd = DDIM_User_Twai_Sem(SID_DD_AUDIO_IF_OUT(ch), (DDIM_USER_TMO)tmout);	// twai_sem()
	}
	
	switch (ercd){
		case D_DDIM_USER_E_OK:
			return D_DDIM_OK;
		case D_DDIM_USER_E_TMOUT:
			return DdAudio_SEM_TIMEOUT;
		default:
			return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Input Channel it is released.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_close_input(DdAudio* self, UINT8 ch)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if ((ch >= DdAudio_IF_IN_CH_NUM_MAX) || (ch == DdAudio_IF_CH3)){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_close_input:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_AUDIO_IF_IN(ch));					// sig_sem()
	if (ercd == D_DDIM_USER_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdAudio_SEM_NG;
	}
}

/**
 * @brief  The exclusive control of control Output Channel it is released.
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_SEM_NG/DdAudio_INPUT_PARAM_ERROR
 */
INT32 dd_audio_close_output(DdAudio* self, UINT8 ch)
{
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_OUT_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_close_output:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	// Exclusive release
	ercd = DDIM_User_Sig_Sem(SID_DD_AUDIO_IF_OUT(ch));					// sig_sem()
	if (ercd == D_DDIM_USER_E_OK){
		return D_DDIM_OK;
	}
	else {
		return DdAudio_SEM_NG;
	}
}

/**
 * @brief  AudioI/F interrupt handler
 * @param  UINT8 ch
 */
VOID dd_audio_int_handler(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	DdAudioRegFunc callback_func;
	
#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_int_handler:input channel error : %d\n", ch));
		return ;
	}
#endif	// CO_PARAM_CHECK
	
	// input interrupt
	if ((dd_audio_get_enable_in_full_intr(self, ch) != FALSE) && (dd_audio_get_in_full(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:InputRegisterFull[%d]\n",ch));
		
		(VOID)dd_audio_set_enable_in_full_intr(self, ch, DdAudio_DISABLE);
		
		callback_func = priv->gDd_Audio_Input_Callback_Func[ch];
		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
	
	if ((dd_audio_get_enable_in_usage_intr(self, ch) != FALSE) && (dd_audio_get_in_usage_flag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:Write Completion to Input Register[%d]\n",ch));
		
		(VOID)dd_audio_set_enable_in_usage_intr(self, ch, DdAudio_DISABLE);
		
		callback_func = priv->gDd_Audio_Input_Callback_Func[ch];
		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
	
	// input error interrupt
	if ((dd_audio_get_enable_in_overflow_intr(ch) != FALSE) && (dd_audio_get_in_overflow_flag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:OverFlow[%d]\n",ch));
		
		(VOID)dd_audio_clear_in_overflow_flag(self, ch);
		
		callback_func = priv->gDd_Audio_OverFlow_Callback_Func[ch];
		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
	
	// output interrupt
	if ((dd_audio_get_enable_out_empty_intr(self, ch) != FALSE) && (dd_audio_get_out_empty(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:OutputRegisterEmpty[%d]\n",ch));
		
		(VOID)dd_audio_set_enable_out_empty_intr(self, ch, DdAudio_DISABLE);
		
		callback_func = priv->gDd_Audio_Output_Callback_Func[ch];
		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
	
	if ((dd_audio_get_enable_out_usage_intr(self, ch) != FALSE) && (dd_audio_get_out_usage_flag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:Read Completion from Output Register[%d]\n",ch));
		
		(VOID)dd_audio_set_enable_out_usage_intr(self, ch, DdAudio_DISABLE);
		
		callback_func = priv->gDd_Audio_Output_Callback_Func[ch];
		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
	
	// output error interrupt
	if ((dd_audio_get_enable_out_underflow_intr(ch) != FALSE) && (dd_audio_get_out_underflow_flag(ch) != FALSE)){
		
		Ddim_Print(("[DD_AUDIO]Interrupt:UnderFlow[%d]\n",ch))
		
		(VOID)dd_audio_clear_out_underflow_flag(self, ch);
		
		callback_func = dd_audio_reg_get_under_flow_func(priv->audioReg, ch);

		if (callback_func != NULL){
			callback_func(priv->audioReg);
		}
	}
}

/**
 * @brief  Initialized AudioMacro Setting
 */
VOID dd_audio_init(DdAudio* self)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	// software reset
	(VOID)dd_audio_reset(self, DdAudio_IF_CH0);
	(VOID)dd_audio_reset(self, DdAudio_IF_CH1);
	(VOID)dd_audio_reset(self, DdAudio_IF_CH2);
	(VOID)dd_audio_reset(self, DdAudio_IF_CH3);
	(VOID)dd_audio_reset(self, DdAudio_IF_CH4);
	(VOID)dd_audio_reset(self, DdAudio_IF_CH5);
	
	// Set Audio PLL
	if (Dd_Top_Get_PLLCNT1_PL10AST() == 0){
		Dd_Top_Stop_Pll10A();
		DdAudio_WAIT_USEC(6);			// wait 6us
		
		Dd_Top_Set_CLKSTOP3_PDM0CK(1);
		Dd_Top_Set_CLKSTOP3_PDM1CK(1);
		
		Dd_Top_Start_Pll10A();
	}
	
	dd_audio_i2s_set_master_clock(priv->audioI2s, (AudioMasterClock)0xFF);
}

/**
 * @brief  Reset AudioI/F Macro
 * @param  UINT8 ch
 * @return INT32 D_DDIM_OK/DdAudio_INPUT_PARAM_ERROR/DdAudio_SYSTEM_ERROR
 */
INT32 dd_audio_reset(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);
	INT32 ret;

#ifdef CO_PARAM_CHECK
	if (ch >= DdAudio_IF_CH_NUM_MAX){
		Ddim_Assertion(("[DD_AUDIO]dd_audio_reset:input channel error : %d\n", ch));
		return DdAudio_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK
	ret = dd_audio_set_sw_reset(ch);
	if (ret != D_DDIM_OK){
		Ddim_Print(("[DD_AUDIO]dd_audio_reset:dd_audio_set_sw_reset() = %x\n", ret));
		return DdAudio_SYSTEM_ERROR;
	}
	
	// Initialize Global Data
	dd_audio_ctrl_set_cmmn_fifo_usage(priv->audioCtrl, ch, DdAudioCtrl_FIFO_USAGE_STAGES_8);
	dd_audio_ctrl_set_cmmn_channel(priv->audioCtrl, ch, DdAudioCtrl_CHANNEL_MONO);
	
	dd_audio_ctrl_set_in_format(priv->audioCtrl, ch, DdAudioCtrl_DATA_REG_FRMT_R_JUST);
	dd_audio_ctrl_set_in_fifo_stages(priv->audioCtrl, ch, DdAudioCtrl_FIFO_STAGES_1);
	dd_audio_ctrl_set_in_ahb_format(priv->audioCtrl, ch, DdAudioCtrl_AHB_FRMT_R_JUST);
	dd_audio_ctrl_set_in_bit_shift(priv->audioCtrl, ch, DdAudioCtrl_BIT_SHIFT_0);
	
	dd_audio_ctrl_set_out_format(priv->audioCtrl, ch, DdAudioCtrl_DATA_REG_FRMT_R_JUST);
	dd_audio_ctrl_set_out_fifo_stages(priv->audioCtrl, ch, DdAudioCtrl_FIFO_STAGES_1);
	dd_audio_ctrl_set_out_ahb_format(priv->audioCtrl, ch, DdAudioCtrl_AHB_FRMT_R_JUST);
	dd_audio_ctrl_set_out_lr_copy(priv->audioCtrl, ch, DdAudio_DISABLE);
	dd_audio_ctrl_set_out_mix_play(priv->audioCtrl, ch, DdAudio_DISABLE);
	dd_audio_ctrl_set_out_bit_shift(priv->audioCtrl, ch, DdAudioCtrl_BIT_SHIFT_0);
	
	if (ch != DdAudio_IF_CH1){
		dd_audio_i2s_cmmn_init(priv->audioI2s, ch);
	}
	
	dd_audio_i2s_in_init(priv->audioI2s, ch);

	dd_audio_i2s_out_init(priv->audioI2s, ch);
	
	dd_audio_dma_set_in_2ch(priv->audioDma, ch, DdAudio_DISABLE);
	dd_audio_dma_set_in_trnsf_cnt(priv->audioDma, ch, 0);
	
	dd_audio_dma_set_out_2ch(priv->audioDma, ch, DdAudio_DISABLE);
	dd_audio_dma_set_out_trnsf_cnt(priv->audioDma, ch, 0);
	
	priv->gDd_Audio_OverFlow_Callback_Func[ch] = NULL;
	dd_audio_reg_set_under_flow_func(priv->audioReg, NULL, ch);
	priv->gDd_Audio_Input_Callback_Func[ch] = NULL;
	priv->gDd_Audio_Output_Callback_Func[ch] = NULL;
	
	return D_DDIM_OK;
}

INT32 dd_audio_ctrl_common(DdAudio *self, UINT8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_common(priv->audioCtrl, ch, ctrl_inf);
}

INT32 dd_audio_get_ctrl_common(DdAudio *self, UINT8 ch, AudioCtrlCommon* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_common(priv->audioCtrl, ch, ctrl_inf);
}

INT32 dd_audio_ctrl_input(DdAudio *self, UINT8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_input(priv->audioCtrl, ch, ctrl_inf);
}

INT32 dd_audio_get_ctrl_input(DdAudio *self, UINT8 ch, AudioCtrlIn* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_input(priv->audioCtrl, ch, ctrl_inf);
}

INT32 dd_audio_ctrl_output(DdAudio *self, UINT8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_ctrl_output(priv->audioCtrl, ch, ctrl_inf);
}

INT32 dd_audio_get_ctrl_output(DdAudio *self, UINT8 ch, AudioCtrlOut* ctrl_inf)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_ctrl_output(priv->audioCtrl, ch, ctrl_inf);
}

void dd_audio_set_over_flow_func(DdAudio* self, DdAudioRegFunc overFlowFunc, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->gDd_Audio_OverFlow_Callback_Func[index] = overFlowFunc;
}

void dd_audio_set_input_func(DdAudio* self, DdAudioRegFunc input, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->gDd_Audio_Input_Callback_Func[index] = input;
}

void dd_audio_set_output_func(DdAudio* self, DdAudioRegFunc output, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	priv->gDd_Audio_Output_Callback_Func[index] = output;
}

ULONG* dd_audio_get_spin_lock_addr(DdAudio* self)
{
	return &gDd_Audio_Spin_Lock;
}

AudioFifoUsage dd_audio_get_cmmn_fifo_usage(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_cmmn_fifo_usage(priv->audioCtrl, index);
}

AudioFifoStages dd_audio_get_in_fifo_stages(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_in_fifo_stages(priv->audioCtrl, index);
}

AudioFifoStages dd_audio_get_out_fifo_stages(DdAudio* self, int index)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_ctrl_get_out_fifo_stages(priv->audioCtrl, index);
}

INT32 dd_audio_ctrl_dma_in(DdAudio *self, UINT8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_ctrl_dma_in(priv->audioDma, ch, dmaSetting);
}

INT32 dd_audio_get_ctrl_dma_in(DdAudio *self, UINT8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_ctrl_dma_in(priv->audioDma, ch, dmaSetting);
}

INT32 dd_audio_ctrl_dma_out(DdAudio *self, UINT8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_ctrl_dma_out(priv->audioDma, ch, dmaSetting);
}

INT32 dd_audio_get_ctrl_dma_out(DdAudio *self, UINT8 ch, AudioDma* dmaSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_ctrl_dma_out(priv->audioDma, ch, dmaSetting);
}

INT32 dd_audio_set_enable_fifo_full_dmain(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_enable_fifo_full_dmain(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_enable_fifo_empty_dma_out(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_enable_fifo_empty_dma_out(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_input_dma_request_enable(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_input_dma_request_enable(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_output_dma_request_enable(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_output_dma_request_enable(priv->audioDma, ch, enable);
}

UINT16 dd_audio_get_in_dma_sample(DdAudio *self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_in_dma_sample(priv->audioDma, ch);
}

UINT16 dd_audio_get_out_dma_sample(DdAudio *self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_get_out_dma_sample(priv->audioDma, ch);
}

INT32 dd_audio_set_swap_byte_auidlr(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swapbyte_auidlr(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_swap_hw_auidlr(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_hw_auidlr(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_swap_byte_auodlr(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_byte_auodlr(priv->audioDma, ch, enable);
}

INT32 dd_audio_set_swap_hw_auodlr(DdAudio *self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_dma_set_swap_hw_auodlr(priv->audioDma, ch, enable);
}

AudioClkMode dd_audio_get_cmmn_master_slave(DdAudio *self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_cmmn_master_slave(priv->audioI2s, ch);
}

INT32 dd_audio_ctrl_i2s_cmmn(DdAudio *self, UINT8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_cmmn(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_get_ctrl_i2s_cmmn(DdAudio *self, UINT8 ch, AudioI2sCmmn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_cmmn(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_ctrl_i2s_in(DdAudio *self, UINT8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_in(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_get_ctrl_i2s_in(DdAudio *self, UINT8 ch, AudioI2sIn* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_in(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_ctrl_i2s_out(DdAudio *self, UINT8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_ctrl_i2s_out(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_get_ctrl_i2s_out(DdAudio *self, UINT8 ch, AudioI2sOut* i2sSetting)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_i2s_get_ctrl_i2s_out(priv->audioI2s, ch, i2sSetting);
}

INT32 dd_audio_start_input(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_start_input(priv->audioIo, ch);
}

INT32 dd_audio_stop_input(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_stop_input(priv->audioIo, ch);
}

BOOL dd_audio_get_status_input(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_get_status_input(priv->audioIo, ch);
}

INT32 dd_audio_start_output(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_start_output(priv->audioIo, ch);
}

INT32 dd_audio_stop_output(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_stop_output(priv->audioIo, ch);
}

BOOL dd_audio_get_status_output(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_io_get_status_output(priv->audioIo, ch);
}

INT32 dd_audio_start_loop_back(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_start(priv->audioLoopBack, ch);
}

INT32 dd_audio_stop_loop_back(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_stop(priv->audioLoopBack, ch);
}

BOOL dd_audio_get_status_loop_back(DdAudio* self, UCHAR ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_loopback_get_status(priv->audioLoopBack, ch);
}

UINT32 dd_audio_get_addr_reg_auidlr(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidlr(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auodlr(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodlr(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auidl(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidl(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auidr(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auidr(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auodl(DdAudio* self, UCHAR ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodl(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auodr(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auodr(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auiddmapt(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auiddmapt(priv->audioReg, ch);
}

UINT32 dd_audio_get_addr_reg_auoddmapt(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_addr_reg_auoddmapt(priv->audioReg, ch);
}

INT32 dd_audio_set_enable_input_intr(DdAudio* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_input_intr(priv->audioReg, ch, enable, callback);
}

INT32 dd_audio_set_enable_output_intr(DdAudio* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_output_intr(priv->audioReg, ch, enable, callback);
}

INT32 dd_audio_set_enable_in_over_flow_intr(DdAudio* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_over_flow_intr(priv->audioReg, ch, enable, callback);
}

INT32 dd_audio_set_enable_out_under_flow_intr(DdAudio* self, UINT8 ch, UINT8 enable, DdAudioRegFunc callback)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_under_flow_intr(priv->audioReg, ch, enable, callback);
}

UINT32 dd_audio_get_input_fifo_status(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_input_fifo_status(priv->audioReg, ch);
}

UINT32 dd_audio_get_output_fifo_status(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_output_fifo_status(priv->audioReg, ch);
}

INT32 dd_audio_set_enable_in_full_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_full_intr(priv->audioReg, ch, enable);
}

INT32 dd_audio_set_enable_out_empty_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_empty_intr(priv->audioReg, ch, enable);
}

BOOL dd_audio_get_audio_in_enable_flag(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_audio_in_enable_flag(priv->audioReg, ch);
}

BOOL dd_audio_get_audio_out_enable_flag(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_get_audio_out_enable_flag(priv->audioReg, ch);
}

INT32 dd_audio_clear_out_underflow_flag(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_clear_out_underflow_flag(priv->audioReg, ch);
}

INT32 dd_audio_set_enable_in_overflow_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_overflow_intr(priv->audioReg, ch, enable);
}

INT32 dd_audio_set_enable_out_underflow_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_underflow_intr(priv->audioReg, ch, enable);
}

INT32 dd_audio_set_enable_in_usage_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_in_usage_intr(priv->audioReg, ch, enable);
}

INT32 dd_audio_clear_in_overflow_flag(DdAudio* self, UINT8 ch)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_clear_in_overflow_flag(priv->audioReg, ch);
}

INT32 dd_audio_set_enable_out_usage_intr(DdAudio* self, UINT8 ch, UINT8 enable)
{
	DdAudioPrivate *priv = DD_AUDIO_GET_PRIVATE(self);

	return dd_audio_reg_set_enable_out_usage_intr(priv->audioReg, ch, enable);
}

DdAudio* dd_audio_get(void)
{
	static DdAudio* self = NULL;

	if(!self)
		self = k_object_new_with_private(DD_TYPE_AUDIO, sizeof(DdAudioPrivate));

	return self;
}

