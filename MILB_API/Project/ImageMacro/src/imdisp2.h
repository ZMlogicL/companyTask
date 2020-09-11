/*
 * imdisp2.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP2_H__
#define __IM_DISP2_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp8.h"

#define IM_TYPE_DISP2				(im_disp2_get_type())
#define IM_DISP2(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp2))
#define IM_IS_DISP2(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP2))

typedef struct   _ImDisp2 			ImDisp2;
typedef struct   _ImDisp2Private		ImDisp2Private;

struct _ImDisp2 {
	KObject parent;
};

KConstType 		im_disp2_get_type(void);
ImDisp2*	im_disp2_new(void);

// VFTMG value
typedef enum {
	E_IM_DISP_VFTMG_NONE_FLAG = 0x00000000,		// None flag generate
	E_IM_DISP_VFTMG_FIRST_FLAG,					// First field generate a flag
	E_IM_DISP_VFTMG_SECOND_FLAG,				// Second field generate a flag
	E_IM_DISP_VFTMG_BOTH_FLAG,					// Both field generate a flag
} E_IM_DISP_VFTMG;

/** Selection whether stop of channel is waited or do not wait. */
typedef enum {
	E_IM_DISP_STOP_TYPE_WITHOUT_WAIT	= 0x00000000,	/**< Forced stop.		*/
	E_IM_DISP_STOP_TYPE_WITH_WAIT		= 0x00000002	/**< Stop with wait.	*/
} E_IM_DISP_STOP_TYPE;


/** Frequency in which VSYNC is waited. */
typedef enum {
	E_IM_DISP_WAIT_1_TIME = 1,		/**< Wait one time	*/
	E_IM_DISP_WAIT_2_TIME			/**< Wait two times	*/
} E_IM_DISP_WAIT;


extern INT32 Im_DISP_Ctrl_Main_Tbl(E_IM_DISP_SEL block, T_IM_DISP_CTRL_MAIN_TBL const *const ctrl_tbl);

/**
Get Gamma table of main data input block.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	ctrl_tbl		Table setting data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Ctrl_Main_Tbl(E_IM_DISP_SEL block, T_IM_DISP_CTRL_MAIN_TBL *const ctrl_tbl);

/**
Set Gamma table of data output block.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	ctrl_tbl		Table setting data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks If NULL is specified for the argument, the acquisition of the item can be skipped.<br>
*/
extern INT32 Im_DISP_Ctrl_Output_Tbl(E_IM_DISP_SEL block, T_IM_DISP_CTRL_OUTPUT_TBL const *const ctrl_tbl);

/**
Get Gamma table of data output block.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	ctrl_tbl		Table setting data.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Ctrl_Output_Tbl(E_IM_DISP_SEL block, T_IM_DISP_CTRL_OUTPUT_TBL *const ctrl_tbl);

/**
The block is started.
@param[in]	hdmi_layer		Layer selection for HDMI block(common block 0).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[in]	lcd_mipi_layer	Layer selection for LCD or MIPI block(common block 1).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[in]	write_channel	Write channel block selection.<br>
							Value:<br>
							0 : not select<br>
							1 : Write channel 0 (Luminance data)<br>
							2 : Write channel 1 (Chrominance data)<br>
							3 : Write channel 0 & 1<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_ACCESS_ERR			TRG cannot be set up.
@retval	D_IM_DISP_TIMEOUT				The channel cannot stop within 33ms.
@remarks	@ref Im_DISP_Start or @ref Im_DISP_Stop can be called 1 time only at same frame.<br>
			It must be interval (system's cycle/CPU's cycle + 2*CPU's cycle + 1) if the TRG was written continuously.<br>
			That is 266 / 27 + 2 + 1 = 19<br>
			It's no any problem because the following instructions are over 19 assemble instruction.<br>
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
extern INT32 Im_DISP_Start(UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE write_channel);

/**
The block is stopped.
@param[in]	hdmi_layer		Layer selection for HDMI block(common block 0).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[in]	lcd_mipi_layer	Layer selection for LCD or MIPI block(common block 1).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[in]	write_channel	Write channel block selection.<br>
							Value:<br>
							0 : not select<br>
							1 : Write channel 0 (Luminance data)<br>
							2 : Write channel 1 (Chrominance data)<br>
							3 : Write channel 0 & 1<br>
@param[in]	stop_type		Selection whether stop of block is waited or do not wait.<br>
							<ul><li>@ref E_IM_DISP_STOP_TYPE_WITHOUT_WAIT
								<li>@ref E_IM_DISP_STOP_TYPE_WITH_WAIT</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_ACCESS_ERR			TRG cannot be set up.
@retval	D_IM_DISP_TIMEOUT				The channel cannot stop within 33ms.
@remarks	If it's necessary, call the @ref Im_DISP_Wait_Stop to wait the channel stopping <br>
			when the @ref E_IM_DISP_STOP_TYPE_WITH_WAIT was used.<br>
			@ref Im_DISP_Start or @ref Im_DISP_Stop can be called 1 time only at same frame.<br>
			It must be interval (system's cycle/CPU's cycle + 2*CPU's cycle + 1) if the SR was written continuously.<br>
			That is 266 / 27 + 2 + 1 = 19<br>
			It's no any problem because the following instructions are over 19 assemble instruction.<br>
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
extern INT32 Im_DISP_Stop(UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE write_channel, E_IM_DISP_STOP_TYPE stop_type);

/**
Get startup status of all blocks.
@param[out]	hdmi_layer		Layer status for HDMI block(common block 0).<br>
							The value corresponding to each block starting layer is set up.<br>
							(When two or more layers are starting, OR value of them is set up.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[out]	lcd_mipi_layer	Layer status for LCD or MIPI block(common block 1).<br>
							The value corresponding to each block starting layer is set up.<br>
							(When two or more layers are starting, OR value of them is set up.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Status(UINT32* hdmi_layer, UINT32* lcd_mipi_layer);

/**
Wait VSYNC interruption.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	interruption_select	Bit map to select wait item. <br>
							<ul><li>@ref E_IM_DISP_INTERRUPTION_SELECT_VE
								<li>@ref E_IM_DISP_INTERRUPTION_SELECT_VE2
								<li>@ref E_IM_DISP_CORRECT_SELECT_ALL_VE</ul>
@param[in]	wait_time		Wait frequency.<br>
							<ul><li>@ref E_IM_DISP_WAIT_1_TIME
								<li>@ref E_IM_DISP_WAIT_2_TIME</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_STATUS_ABNORMAL		Can not wait because INTE was not set to 1 or<br>
										INTC was 0.
@remarks	This API uses DDIM_User_Clr_Flg().
@remarks	This API uses DDIM_User_Twai_Flg().
*/
extern INT32 Im_DISP_Wait_Vsync(E_IM_DISP_SEL block, E_IM_DISP_INTERRUPTION_SELECT interruption_select, E_IM_DISP_WAIT wait_time);

/**
Wait the block stopping after the @ref Im_DISP_Stop was called if it was necessary.
@param [in]	hdmi_layer		Layer selection for HDMI block(common block 0).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param [in]	lcd_mipi_layer	Layer selection for LCD or MIPI block(common block 1).<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_TIMEOUT				Time-out occur when waitng the block stop.
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
extern INT32 Im_DISP_Wait_Stop(UINT32 hdmi_layer, UINT32 lcd_mipi_layer);

/**
DISP interrupt handler.
@remarks This API uses DDIM_User_Set_Flg().
*/
extern VOID Im_DISP_Int_Handler(VOID);

/**
Set SR.<br>
@param [in]	hdmi_layer		Layer SR status for HDMI block(common block 0).<br>
							The value corresponding to each block SR layer is set up.<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param [in]	lcd_mipi_layer	Layer SR status for LCD or MIPI block(common block 1).<br>
							The value corresponding to each block SR layer is set up.<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[in]	sr				SR to set.<br>
							<ul><li>@ref D_IM_DISP_SR_CANCEL
								<li>@ref D_IM_DISP_SR_RESET</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It must be interval (system's cycle/CPU's cycle + 2*CPU's cycle + 1) if the SR was written continuously.<br>
			That is 266 / 27 + 2 + 1 = 19<br>
			It's no any problem because the following instructions are over 19 assemble instruction.<br>
*/
extern INT32 Im_DISP_Set_SR(UINT32 hdmi_layer, UINT32 lcd_mipi_layer, BYTE sr);

/**
Get SR.<br>
@param[out]	hdmi_layer		Layer SR status for HDMI block(common block 0).<br>
							The value corresponding to each block SR layer is set up.<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@param[out]	lcd_mipi_layer	Layer SR status for LCD or MIPI block(common block 1).<br>
							The value corresponding to each block SR layer is set up.<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_NONE
								<li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL
								<li>@ref E_IM_DISP_SEL_LAYER_ALL</ul>
@retval	D_DDIM_OK						Success
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_SR(UINT32* hdmi_layer, UINT32* lcd_mipi_layer);

/**
Set parameter reflect timing.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/

#endif /* __IM_DISP2_H__ */
