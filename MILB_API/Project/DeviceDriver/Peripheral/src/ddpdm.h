/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#ifndef _DD_PDM_H_
#define _DD_PDM_H_

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_PDM				(dd_pdm_get_type())
#define DD_PDM(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdPdm))
#define DD_IS_PDM(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PDM))


/* Return Value */
#define DdPdm_INPUT_PARAM_ERROR		(D_DD_PDM | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */
#define DdPdm_MACRO_BUSY_NG			(D_DD_PDM | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy */
#define DdPdm_SEM_TIMEOUT			(D_DD_PDM | D_DDIM_SEM_TIMEOUT)			/**< Semaphore acquisition Time Out */
#define DdPdm_SEM_NG				(D_DD_PDM | D_DDIM_SEM_NG)				/**< Semaphore acquisition NG */
#define DdPdm_SYSTEM_ERROR			(D_DD_PDM | D_DDIM_SYSTEM_ERROR)		/**< System error */

#define DdPdm_CH0					(0x00)										/**< PDM Channel 0  */
#define DdPdm_CH1					(0x01)										/**< PDM Channel 1 */
#define DdPdm_CH_NUM_MAX			(0x02)										/**< Channel Max Number */

/* Function Enable */
#define	DdPdm_DISABLE				(0)											/**< Disable	*/
#define	DdPdm_ENABLE				(1)											/**< Enable		*/


/** LR Channel Swap Setting */
typedef enum {
	DdPdm_CORE_LR_SWAP_NO_SWAP	= 0,							/**< No Swap */
	DdPdm_CORE_LR_SWAP_SWAP										/**< Right/Left Channel Recording Swap */
} PdmCoreLrSwap;

/** PGA Gain */
typedef enum {
	DdPdm_CORE_PGA_0_0_DB		= 0,							/**< PGA Gain:  0.0[dB] */
	DdPdm_CORE_PGA_P_1_5_DB,										/**< PGA Gain: +1.5[dB] */
	DdPdm_CORE_PGA_P_3_0_DB,										/**< PGA Gain: +3.0[dB] */
	DdPdm_CORE_PGA_P_4_5_DB,										/**< PGA Gain: +4.5[dB] */
	DdPdm_CORE_PGA_P_6_0_DB,										/**< PGA Gain: +6.0[dB] */
	DdPdm_CORE_PGA_P_7_5_DB,										/**< PGA Gain: +7.5[dB] */
	DdPdm_CORE_PGA_P_9_0_DB,										/**< PGA Gain: +9.0[dB] */
	DdPdm_CORE_PGA_P_10_5_DB,									/**< PGA Gain: +10.5[dB] */
	DdPdm_CORE_PGA_M_12_0_DB,									/**< PGA Gain: -12.0[dB] */
	DdPdm_CORE_PGA_M_10_5_DB,									/**< PGA Gain: -10.5[dB] */
	DdPdm_CORE_PGA_M_9_0_DB,										/**< PGA Gain: -9.0[dB] */
	DdPdm_CORE_PGA_M_7_5_DB,										/**< PGA Gain: -7.5[dB] */
	DdPdm_CORE_PGA_M_6_0_DB,										/**< PGA Gain: -6.0[dB] */
	DdPdm_CORE_PGA_M_4_5_DB,										/**< PGA Gain: -4.5[dB] */
	DdPdm_CORE_PGA_M_3_0_DB,										/**< PGA Gain: -3.0[dB] */
	DdPdm_CORE_PGA_M_1_5_DB,										/**< PGA Gain: -1.5[dB] */
} PdmCorePga;

/** Setting Cycle(during gain setting / soft mute) */
typedef enum {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	DdPdm_CORE_S_CYCLE_167US		= 0,							/**< Setting Cycle:  167[us] */
	DdPdm_CORE_S_CYCLE_333US,									/**< Setting Cycle:  333[us] */
	DdPdm_CORE_S_CYCLE_500US,									/**< Setting Cycle:  500[us] */
	DdPdm_CORE_S_CYCLE_667US,									/**< Setting Cycle:  667[us] */
	DdPdm_CORE_S_CYCLE_833US,									/**< Setting Cycle:  833[us] */
	DdPdm_CORE_S_CYCLE_1000US,									/**< Setting Cycle:  1000[us] */
	DdPdm_CORE_S_CYCLE_1167US,									/**< Setting Cycle:  1167[us] */
	DdPdm_CORE_S_CYCLE_1333US,									/**< Setting Cycle:  1333[us] */
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	DdPdm_CORE_S_CYCLE_0		= 0,								/**< Setting Cycle:  FS=48kHz/32kHz:167[us], FS=24kHz/16kHz:333[us] */
	DdPdm_CORE_S_CYCLE_1,										/**< Setting Cycle:  FS=48kHz/32kHz:333[us], FS=24kHz/16kHz:667[us] */
	DdPdm_CORE_S_CYCLE_2,										/**< Setting Cycle:  FS=48kHz/32kHz:500[us], FS=24kHz/16kHz:1000[us] */
	DdPdm_CORE_S_CYCLE_3,										/**< Setting Cycle:  FS=48kHz/32kHz:667[us], FS=24kHz/16kHz:1333[us] */
	DdPdm_CORE_S_CYCLE_4,										/**< Setting Cycle:  FS=48kHz/32kHz:833[us], FS=24kHz/16kHz:1667[us] */
	DdPdm_CORE_S_CYCLE_5,										/**< Setting Cycle:  FS=48kHz/32kHz:1000[us], FS=24kHz/16kHz:2000[us] */
	DdPdm_CORE_S_CYCLE_6,										/**< Setting Cycle:  FS=48kHz/32kHz:1167[us], FS=24kHz/16kHz:2333[us] */
	DdPdm_CORE_S_CYCLE_7,										/**< Setting Cycle:  FS=48kHz/32kHz:1333[us], FS=24kHz/16kHz:2667[us] */
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
} PdmCoreSCycle;

/** DMA Burst Length Setting */
typedef enum {
	DdPdm_DMA_BURST_LEN_1	= 0,								/**< DMA burst length: 1 word */
	DdPdm_DMA_BURST_LEN_4,										/**< DMA burst length: 4 word */
	DdPdm_DMA_BURST_LEN_8,										/**< DMA burst length: 8 word */
	DdPdm_DMA_BURST_LEN_16,										/**< DMA burst length: 16 word */
} PdmDmaBurstLen;

/** PCM Output Channel Setting(DMA Transfer Mode) */
typedef enum {
	DdPdm_DMA_PCM_CH_DISABLE	= 0,								/**< PCM Channel: Disable */
	DdPdm_DMA_PCM_CH_LEFT,										/**< PCM Channel: Mono(Left Channel) */
	DdPdm_DMA_PCM_CH_RIGHT,										/**< PCM Channel: Mono(Right Channel) */
	DdPdm_DMA_PCM_CH_STEREO,										/**< PCM Channel: Stereo */
} PdmDmaPcmCh;

/** PCM Data Word Length Setting(DMA Transfer Mode) */
typedef enum {
	DdPdm_DMA_PCM_WD_16	= 0,									/**< PCM Data Word Length: 16bit */
	DdPdm_DMA_PCM_WD_18,											/**< PCM Data Word Length: 18bit */
	DdPdm_DMA_PCM_WD_20,											/**< PCM Data Word Length: 20bit */
	DdPdm_DMA_PCM_WD_24,											/**< PCM Data Word Length: 24bit */
} PdmDmaPcmWd;

/** Type of Interrupt */
typedef enum {
	DdPdm_INT_TYPE_FFOVF	= 0,									/**< FIFO OverFlow Interrupt*/
	DdPdm_INT_TYPE_DMA0,											/**< DMA0 Interrupt */
	DdPdm_INT_TYPE_DMA1,											/**< DMA1 Interrupt */
} DdPdmIntType;

typedef struct _DdPdmCoreCfg DdPdmCoreCfg;
typedef struct _DdPdmDmaCfg DdPdmDmaCfg;
typedef struct _DdPdmDmaLen DdPdmDmaLen;

/** PDM Core Config */
struct _DdPdmCoreCfg {
	PdmCoreLrSwap		swap;									/**< Right/Left Channel Swap Setting<BR><BR>
																			 Default value : DdPdm_CORE_LR_SWAP_NO_SWAP */
	PdmCorePga			pgaR;									/**< Right Channel PGA Gain<BR><BR>
																			 Default value : DdPdm_CORE_PGA_0_0_DB */
	PdmCorePga			pgaL;									/**< Left Channel PGA Gain<BR><BR>
																			 Default value : DdPdm_CORE_PGA_0_0_DB */
	UINT16				mclkDiv;								/**< PDM_CLK Frequency divisor<BR><BR>
																			 value Range: [0x2-0x3F]<BR>
																			 Default value : 0x4 */
	UINT16				sincRate;								/**< SINC Decimation Rate<BR><BR>
																			 value Range: [0x1-0x7F]<BR>
																			 Default value : 0xd10 */
	kuint8				adcHpd;								/**< High Pass Filter<BR><BR>
																			 value Range: DdPdm_ENABLE / DdPdm_DISABLE<BR>
																			 Default value : DdPdm_DISABLE */
	kuint8				hpCutoff;								/**< High Pass Filter Coefficients<BR><BR>
																			 Default value : 0xB */
	PdmCoreSCycle		sCycle;								/**< Set number of PDM_CLK during gain-setting changes or soft mute<BR><BR>
// --- REMOVE_ES1_HARDWARE BEGIN ---
																			 Default value : DdPdm_CORE_S_CYCLE_333US
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
																			 Default value : DdPdm_CORE_S_CYCLE_1
// --- REMOVE_ES3_HARDWARE END ---
																			  */
	kuint8				softMute;								/**< Soft Mute<BR><BR>
																			 value Range: DdPdm_ENABLE / DdPdm_DISABLE<BR>
																			 Default value : DdPdm_DISABLE */
};

/** PDM DMAC Config */
struct _DdPdmDmaCfg {
	kuint8				dmickDly;								/**< Input Data Sampling with number of PDM clock cycle delay<BR><BR>
																			 value Range: [0-3]<BR>
																			 Default value : 0x0 */
	PdmDmaBurstLen		dmaBurstlen;							/**< DMA Burst Length<BR><BR>
																			 Default value : DdPdm_DMA_BURST_LEN_4 */
	PdmDmaPcmCh			pcmChset;								/**< Set PCM Output Channels as Mono or Stereo<BR><BR>
																			 Default value : DdPdm_DMA_PCM_CH_LEFT */
	PdmDmaPcmWd			pcmWdlen;								/**< PCM Data Word Length<BR><BR>
																			 Default value : DdPdm_DMA_PCM_WD_16 */
	kuint8				dmaEn;									/**< DMA Transfer<BR><BR>
																			 value Range: DdPdm_ENABLE / DdPdm_DISABLE<BR>
																			 Default value : DdPdm_DISABLE */
};

/** PDM DMA Transfer Length */
struct _DdPdmDmaLen {
	UINT16		ttsize;								/**< DMA total fransfer length in word<BR><BR>
													value Range: [0x0001-0xFFFF]<BR>
													 Default value : 0x78 */
	kuint8		tsize;								/**< DMA block transfer length in word<BR><BR>
													 value Range: [0x01-0xFF]<BR>
													 Default value : 0x18 */
};


typedef struct _DdPdm 			DdPdm;
typedef struct _DdPdmPrivate 	DdPdmPrivate;
typedef void (*DdPdmFunc)(DdPdm *ddPdm);								/**< Callback function pointer	*/

struct  _DdPdm {
	KObject parent;
};


/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#ifdef __cplusplus
extern "C" {
#endif

KConstType 	dd_pdm_get_type(void);
DdPdm* 		dd_pdm_get(void);

/**
Initialize PDM macro<br>
@retval D_DDIM_OK					OK
*@retval DdPdm_SYSTEM_ERROR		System Error
*/
kint32		dd_pdm_init(DdPdm *self);

/**
Execute exclusive control for PDM macro<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	tmout	Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref DdimUserCustom_SEM_WAIT_POL
							<li>@ref DdimUserCustom_SEM_WAIT_FEVR</ul>
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERR	Input Parameter Error
@retval DdPdm_SEM_NG				Semaphore acquisition NG
@retval DdPdm_SEM_TIMEOUT		Semaphore acquisition Time Out
@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32		dd_pdm_open(DdPdm *self, kuint8 ch, kint32 tmout);

/**
Cancel exclusive control for PDM macro<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@retval D_DDIM_OK				OK
@retval DdPdm_SEM_NG			Semaphore release NG 
@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32		dd_pdm_close(DdPdm *self, kuint8 ch);

/**
DMA0 Interrupt handler for PDM macro<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
*/
void		dd_pdm_dma0_int_handler(DdPdm *self, kuint8 ch);

/**
DMA1 Interrupt handler for PDM macro<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
*/
void		dd_pdm_dma1_int_handler(DdPdm *self, kuint8 ch);

/**
OverFlow Interrupt handler for PDM macro<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
*/
void		dd_pdm_overflow_int_handler(DdPdm *self, kuint8 ch);

/**
Set pdm core control information<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	coreCfg	pcm core control information. See @ref DdPdmCoreCfg
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32		dd_pdm_ctrl_core(DdPdm *self, kuint8 ch, DdPdmCoreCfg* coreCfg);

/**
Get pcm core control information(Common Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[out]	coreCfg	pcm core control information. See @ref DdPdmCoreCfg
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32 		dd_pdm_get_ctrl_core(DdPdm *self, kuint8 ch, DdPdmCoreCfg* coreCfg);

/**
Start Data Streaming<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32		dd_pdm_start_streaming(DdPdm *self, kuint8 ch);

/**
Stop Data Streaming<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32		dd_pdm_stop_streaming(DdPdm *self, kuint8 ch);

/**
Set pdm dma control information<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	dmaCfg		pcm dma control information. See @ref DdPdmDmaCfg
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32		dd_pdm_ctrl_dma(DdPdm *self, kuint8 ch, DdPdmDmaCfg* dmaCfg);

/**
Get pcm core control information(Common Setting)<br>
@param[in]	ch	channel<br>
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[out]	dmaCfg		pcm dma control information. See @ref DdPdmDmaCfg
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32 		dd_pdm_get_ctrl_dma(DdPdm *self, kuint8 ch, DdPdmDmaCfg* dmaCfg);

/**
Set callback function of Dma0 Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_callback_dma0_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback);

/**
Set enable Dma0 Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_enable_dma0_intr(DdPdm *self, kuint8 ch, kuint8 enable);

/**
Set callback function of Dma1 Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_callback_dma1_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback);

/**
Set callback function of Dma1 Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_enable_dma1_intr(DdPdm *self, kuint8 ch, kuint8 enable);

/**
Set callback function of OverFlow Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	callback	Callback function pointer
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_callback_over_flow_intr(DdPdm *self, kuint8 ch, DdPdmFunc callback);

/**
Set callback function of OverFlow Interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	enable	[1:enable interrupt request, 0:disable interrupt request]
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_enable_over_flow_intr(DdPdm *self, kuint8 ch, kuint8 enable);

/**
Set DMA0 distination address<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	addr	distination address(4byte unit)
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32		dd_pdm_set_dma0_dst_addr(DdPdm *self, kuint8 ch, kuint32 addr);

/**
Set DMA1 distination address<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	addr	distination address(4byte unit)
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32		dd_pdm_set_dma1_dst_addr(DdPdm *self, kuint8 ch, kuint32 addr);

/**
Set DMA Transfer Size<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	dmaLen		dma transfer length information. See @ref DdPdmDmaLen
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_set_dma_trans_length(DdPdm *self, kuint8 ch, DdPdmDmaLen* dmaLen);

/**
DMA FIFO Flush<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@retval D_DDIM_OK						OK
@retval DdPdm_INPUT_PARAM_ERROR		Input Parameter Error
*/
kint32		dd_pdm_flush_dma_fifo(DdPdm *self, kuint8 ch);

/**
Get log of interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	type		type of interrupt. See @ref DdPdmIntType
@param[out]	status		status of interrupt.[1:Interrupt done / 0: Interrupt not done]
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_get_status(DdPdm *self, kuint8 ch, DdPdmIntType type, kuint8* status);

/**
Clear log of interrupt<br>
@param[in]	ch	channel
						<ul><li>@ref DdPdm_CH0
							<li>@ref DdPdm_CH1</ul>
@param[in]	type		type of interrupt. See @ref DdPdmIntType
@retval D_DDIM_OK					OK
@retval DdPdm_INPUT_PARAM_ERROR	Input Parameter Error
*/
kint32 		dd_pdm_clear_status(DdPdm *self, kuint8 ch, DdPdmIntType type);


#ifdef __cplusplus
}
#endif

#endif	// _DD_PDM_H_

