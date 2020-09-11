/*
 * imdisp5.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP5_H__
#define __IM_DISP5_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp8.h"
#define IM_TYPE_DISP5				(im_disp5_get_type())
#define IM_DISP5(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp5))
#define IM_IS_DISP5(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP5))

typedef struct   _ImDisp5 			ImDisp5;
typedef struct   _ImDisp5Private		ImDisp5Private;

struct _ImDisp5 {
	KObject parent;
};


KConstType 		im_disp5_get_type(void);
ImDisp5*	im_disp5_new(void);


/** OSD start address no. */
typedef enum {
	E_IM_DISP_OSD_SA_BANK_NO_0_0 = 0,	/**< OSD start address bank no 0_0	*/
	E_IM_DISP_OSD_SA_BANK_NO_0_1,		/**< OSD start address bank no 0_1	*/
	E_IM_DISP_OSD_SA_BANK_NO_0_2,		/**< OSD start address bank no 0_2	*/
	E_IM_DISP_OSD_SA_BANK_NO_0_3,		/**< OSD start address bank no 0_3	*/
	E_IM_DISP_OSD_SA_BANK_NO_1,			/**< OSD start address bank no 1	*/
	E_IM_DISP_OSD_SA_BANK_NO_2,			/**< OSD start address bank no 2	*/
	E_IM_DISP_OSD_SA_BANK_NO_3,			/**< OSD start address bank no 3	*/
	E_IM_DISP_OSD_SA_BANK_NO_4,			/**< OSD start address bank no 4	*/
	E_IM_DISP_OSD_SA_BANK_NO_5,			/**< OSD start address bank no 5	*/
	E_IM_DISP_OSD_SA_BANK_NO_6,			/**< OSD start address bank no 6	*/
	E_IM_DISP_OSD_SA_BANK_NO_7,			/**< OSD start address bank no 7	*/
	E_IM_DISP_OSD_SA_BANK_NO_8,			/**< OSD start address bank no 8	*/
	E_IM_DISP_OSD_SA_BANK_NO_9,			/**< OSD start address bank no 9	*/
} E_IM_DISP_OSD_SA_BANK_NO;


/** DBGSL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	VDMSL	:1;		/**< VDMSL: Vertical sync signal selection for debugging.<br>
									 Value 0:HDMI, 1:MIPI-DSI										*/
		ULONG			:3;		/**< Reserve														*/
		ULONG	HDMSL	:1;		/**< HDMSL: Horizontal sync signal selection for debugging.<br>
									 Value 0:HDMI, 1:MIPI-DSI										*/
		ULONG			:3;		/**< Reserve														*/
		ULONG	HDEMSL	:1;		/**< HDEMSL: Horizontal enable signal selection for debugging.<br>
									 Value 0:HDMI, 1:MIPI-DSI										*/
		ULONG			:23;	/**< Reserve														*/
	}bit;	/**< Bit field */
}U_IM_DISP_DBGSL;

extern INT32 Im_DISP_Set_Face_Frame(E_IM_DISP_SEL block, UINT32 frame_count, T_IM_DISP_FACE_FRAME const *const face);

/**
Get face frame data.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	face			Face frame data.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Face_Frame(E_IM_DISP_SEL block, T_IM_DISP_FACE_FRAME *const face);

/**
Set face frame display enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	ffden			Face frame display enable.<br>
							bit d[0]:Face frame 0 ~ d[41]:Face frame 41<br>
							value 0:disable, 1:enable<br>
							(Two or more frame can be specified by the OR value.)<br>
@param[in]	msff			FFDISPEN.MSFF: Top face frame setting register.<br>
							Value range:0~41 (face frame 0 ~ face frame 41)
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Face_Frame_Enable(E_IM_DISP_SEL block, UINT64 ffden, BYTE msff);

/**
Get face frame display enable.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	ffden			Face frame display enable.<br>
							bit d[0]:Face frame 0 ~ d[41]:Face frame 41<br>
							value 0:disable, 1:enable<br>
							(Two or more frame can be specified by the OR value.)<br>
@param[out]	msff			FFDISPEN.MSFF: Top face frame setting register.<br>
							Value range:0~41 (face frame 0 ~ face frame 41)
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Face_Frame_Enable(E_IM_DISP_SEL block, UINT64 *ffden, BYTE *msff);

/**
Set parameter reflect timing of a OSD layer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
extern INT32 Im_DISP_Set_OSD_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_RPGTMG timing);

/**
Get parameter reflect timing of a OSD layer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	timing			Register parameter reflect timing.<br>
							<ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
								<li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Parameter_Reflect_Timing(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_RPGTMG *timing);

/**
Set input data transfer of a OSD layer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	gridt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRIDT.IFMT <= @ref D_IM_DISP_GRIDT_IFMT_RGBA5551
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Input_Data_Transfer(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRIDT gridt);

/**
Get input data transfer of a OSD layer.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	gridt			Input data forwarding setting register.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Input_Data_Transfer(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_GRIDT *gridt);

/**
Set OSD data territory size.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	territory_size	Width and height of OSD data territory.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRTISIZE.TIHSIZE is a multiple of 2
				<li>GRTISIZE.TIHSIZE >= 8
				<li>GRDSTA.DSH + GRTISIZE.TIHSIZE * (GRRSZ1.HRSZM / GRRSZ1.HRSZN) <= OHSIZE
				<li>GRTISIZE.TIVSIZE is a multiple of 2
				<li>GRTISIZE.TIVSIZE >= 8
				<li>GRDSTA.DSV + GRTISIZE.TIVSIZE * (GRRSZ2.VRSZM / GRRSZ2.VRSZN) <= OVSIZE
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Territory_Size(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE territory_size);

/**
Get OSD data territory size.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	territory_size	Width and height of OSD data territory.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Territory_Size(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE *territory_size);

/**
Set display position for OSD.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	position		Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRTDSTA.DSH is a multiple of 2
				<li>GRTDSTA.DSV is a multiple of 2
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Territory_Position(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_DSTA position);

/**
Get display position for OSD.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	position		Display position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Territory_Position(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_DSTA* position);

/**
Set input data area to access.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	area			Input data area.<br>
							<ul><li>@ref E_IM_DISP_INPUT_DATA_AREA_0
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_1
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_2
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_3</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_OSD_Area0_Switch(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_INPUT_DATA_AREA area);

/**
Get input data area to access.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	area			Input data area.<br>
							<ul><li>@ref E_IM_DISP_INPUT_DATA_AREA_0
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_1
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_2
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_3</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Area0_Switch(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_INPUT_DATA_AREA *area);

/**
Get input data area inder processing.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[out]	area			Input data area.<br>
							<ul><li>@ref E_IM_DISP_INPUT_DATA_AREA_0
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_1
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_2
								<li>@ref E_IM_DISP_INPUT_DATA_AREA_3</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Area0_Monitor(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_INPUT_DATA_AREA *area);

/**
Set input data size of OSD.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	input_size		Width and height of input data buffer.<br>
@param[in]	input_size_count input_size's number.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRISIZE.IHSIZE is a multiple of 4
				<li>GRISIZE.IHSIZE >= 8
				<li>GRISIZE.IVSIZE is a multiple of 2
				<li>GRISIZE.IVSIZE >= 8
				<li>GRDSTA.DSH + GRISIZE.IHSIZE <= GRTISIZE.TIHSIZE
				<li>GRDSTA.DSV + GRISIZE.IVSIZE <= GRTISIZE.TIVSIZE
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Area_Size(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer,
								U_IM_DISP_SIZE input_size[D_IM_DISP_OSD_DISPLAY_AREA_COUNT],
								UINT32 input_size_count);
/**
Get input data size of OSD.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	input_size		Width and height of input data buffer.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Area_Size(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, U_IM_DISP_SIZE input_size[D_IM_DISP_OSD_DISPLAY_AREA_COUNT]);

/**
Connect OSD input data address with the bank index.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	bank_no			OSD start address bank no.<br>
							<ul><li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_0
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_1
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_2
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_3
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_1
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_2
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_3
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_4
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_5
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_6
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_7
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_8
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_9</ul>
@param[in]	address			OSD start address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRSA0 is a multiple of 8
				<li>GRSA is a multiple of 8
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Area_Addr(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_OSD_SA_BANK_NO bank_no, ULONG address);

/**
Get OSD input data address of the bank index specified.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	bank_no			OSD start address bank no.<br>
							<ul><li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_0
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_1
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_2
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_0_3
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_1
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_2
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_3
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_4
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_5
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_6
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_7
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_8
								<li>@ref E_IM_DISP_OSD_SA_BANK_NO_9</ul>
@param[out]	address			OSD start address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Area_Addr(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_OSD_SA_BANK_NO bank_no, ULONG *address);

/**
Connect OSD input data address (A data) with the bank index.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	bank_no			Bank No. Value range:0~9.<br>
@param[in]	address			OSD A data start address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRSA0 is a multiple of 8
				<li>GRSA is a multiple of 8
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Area_Adata_Addr(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG address);

/**
Get OSD input data address (A data) of the bank index specified.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	bank_no			Bank No. Value range:0~9.<br>
@param[out]	address			OSD A data start address.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Area_Adata_Addr(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *address);

/**
Set the horizontal global area width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	bank_no			Bank No. Value range:0~9.<br>
@param[in]	width			Horizontal global area width.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRHGA > 0
				<li>GRHGA <= 0xFFF8
				<li>GRHGA is a multiple of 8
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Lfd(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG width);

/**
Get the horizontal global area width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	bank_no			Bank No.<br>
@param[out]	width			Horizontal global area width.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Lfd(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *width);

/**
Set the A data horizontal global area width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	bank_no			Bank No. Value range:0~9.<br>
@param[in]	width			A data horizontal global area width.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRHGA > 0
				<li>GRHGA <= 0xFFF8
				<li>GRHGA is a multiple of 8
			</ul>
*/
extern INT32 Im_DISP_Set_OSD_Adata_Lfd(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG width);

/**
Get the A data horizontal global area width.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1</ul>
@param[in]	bank_no			Bank No.<br>
@param[out]	width			A data horizontal global area width.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_OSD_Adata_Lfd(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, UINT32 bank_no, ULONG *width);

/**
Set input start position.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			OSD layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	bank_no			Bank No. Value range:0~9.
@param[in]	position		Input start position.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@remarks	It is necessary to fulfill the following conditions. <br>
			<ul><li>GRDSTA.DSH is a multiple of 2
				<li>GRDSTA.DSH is a multiple of 2
				<li>GRDSTA.DSH_0 <= DSH_1 <= DSH_2 ... <= DSH_9 (in order of bank_no)
				<li>(in case of same DSH) GRDSTA.DSV_0 <= DSV_1 <= DSV_2 ... <= DSV_9
			</ul>
*/

#endif /* __IM_DISP5_H__ */
