/*
 * imdisp7.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP7_H__
#define __IM_DISP7_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp8.h"
#define IM_TYPE_DISP7				(im_disp7_get_type())
#define IM_DISP7(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp7))
#define IM_IS_DISP7(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP7))

typedef struct   _ImDisp7 			ImDisp7;
typedef struct   _ImDisp7Private		ImDisp7Private;

struct _ImDisp7 {
	KObject parent;
};


KConstType 		im_disp7_get_type(void);
ImDisp7*	im_disp7_new(void);

#define D_IM_DISP_GRID_NUM				(8)				/**< Max number of grid line		*/

/** Write channel block number 0/1. */
typedef enum {
	E_IM_DISP_WC_NUM_0	= 0,	/**< Write channel 0 (Luminance data)	*/
	E_IM_DISP_WC_NUM_1			/**< Write channel 1 (Chrominance data)	*/
} E_IM_DISP_WC_NUM;

#ifdef CO_DDIM_UTILITY_USE
/**
@name Utility Enumeration
@{
*/
//---------------------- utility section -------------------------------
/** CC information */
typedef enum {
	E_IM_DISP_CC_MATRIX_NOCONVERT = 0, /**< No any convert */
	E_IM_DISP_CC_MATRIX_709			/**< Convert to 709 */
} E_IM_DISP_CC_MATRIX;
//---------------------- colabo  section -------------------------------
/*		@}*/ /* end of im_disp_util */
#endif // CO_DDIM_UTILITY_USE


/** PWAXCTL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	AWCACHE	:4;	/**< AWCACHE: Cache type.<br>
								 d[0]:Bufferable bit. Value 0:Nonbufferable, 1:Bufferable.<br>
								 d[1]:Cacheable bit. Value 0:Noncacheable, 1:Cacheable.<br>
								 d[2]:Read allocate bit. Value 0:Read through, 1:Allocate on Reads.<br>
								 d[3]:Write allocate bit. Value 0:Write through, 1:Allocate on writes.<br>	*/
		ULONG			:4;	/**< Reserve																	*/
		ULONG	AWPROT	:3;	/**< AWPROT: Protect type.<br>
								 d[0]:Normal or privileged. Value 0:Normal access, 1:Privileged access.<br>
								 d[1]:Secure or non-secure. Value 0:Secure access, 1:Non-secure access.<br>
								 d[2]:Instruction or Data. Value 0:Data access, 1:Instrauction access.<br>	*/
		ULONG			:21;	/**< Reserve																*/
	}bit;	/**< Bit field */
}U_IM_DISP_PWAXCTL;

/** PWCHINTENB register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	PWE		:1;		/**< PWE: PWCH successful completion interrupt request permission.<br>
									 <ul><li>@ref D_IM_DISP_ENABLE_OFF
										 <li>@ref D_IM_DISP_ENABLE_ON</ul>								*/
		ULONG			:3;		/**< Reserve															*/
		ULONG	PWEE	:1;		/**< PWEE: PWCH transmission error interrupt request permission.<br>
									 <ul><li>@ref D_IM_DISP_ENABLE_OFF
										 <li>@ref D_IM_DISP_ENABLE_ON</ul>								*/
		ULONG			:3;		/**< Reserve															*/
		ULONG	PWXE	:1;		/**< PWXE: PWCH AXI error interrupt request permission.<br>
									 <ul><li>@ref D_IM_DISP_ENABLE_OFF
										 <li>@ref D_IM_DISP_ENABLE_ON</ul>								*/
		ULONG			:23;	/**< Reserve															*/
	}bit;	/**< Bit field */
}U_IM_DISP_PWCHINTENB;



/**
Control data of PWCH macro in write channel block.
*/
typedef struct {
	U_IM_DISP_PWAXCTL		pwaxctl;		/**< PWAXCTL: PWCH AXI control register.					*/
	BYTE					pwmw;			/**< PWCHCTL.PWMW: PWCH mask with writing control.<br>
												 <ul><li>@ref D_IM_DISP_ENABLE_OFF
													 <li>@ref D_IM_DISP_ENABLE_ON</ul>					*/
	U_IM_DISP_PWCHINTENB	pwchintenb;		/**< PWCHINTENB: PWCH interrupt enable register.			*/
	ULONG					pwsa;			/**< PWSA: PWCH top address setting register.<br>
												 Value range:0~4294967288.								*/
	ULONG					pwlsize;		/**< PWLSIZE: PWCH line feed size setting register.<br>
												 Value range:0~2147483640.<br>
												 d[31]:Sign bit, this register set in two's complement.	*/
	BYTE					pwvfm;			/**< PWVFM: PWCH video format selection register.<br>
												 <ul><li>@ref D_IM_DISP_FORMAT_NORMAL
													 <li>@ref D_IM_DISP_FORMAT_VIDEO</ul>				*/
} T_IM_DISP_CTRL_PWCH;

extern INT32 Im_DISP_Set_Luminance_Table(E_IM_DISP_SEL block, BYTE surface, USHORT* tbl);

/**
Get Luminance correct table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Luminance correct table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[out]	tbl				Luminance correct table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
extern INT32 Im_DISP_Get_Luminance_Table(E_IM_DISP_SEL block, BYTE surface, USHORT* tbl);

/**
Set Chroma correct gain table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Chroma correct gain table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[in]	tbl				Chroma correct gain table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
extern INT32 Im_DISP_Set_Chroma_Gain_Table(E_IM_DISP_SEL block, BYTE surface, USHORT* tbl);

/**
Get Chroma correct gain table.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	surface			Chroma correct gain table surface.<br>
							<ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
								<li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>
@param[out]	tbl				Chroma correct gain table.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
extern INT32 Im_DISP_Get_Chroma_Gain_Table(E_IM_DISP_SEL block, BYTE surface, USHORT* tbl);

/**
Set MIPI-DSI IP input pin control 0.
@param[in]	shudown			Snutdown input control.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@param[in]	color_mode		Color mode input control.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_MACRO_BUSY_NG			Fail - Macro busy
*/
extern INT32 Im_DISP_Set_Mipi_Dsi_Ctrl0(BYTE shudown, BYTE color_mode);

/**
Get MIPI-DSI IP input pin control 0.
@param[out]	shudown			Snutdown input control.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@param[out]	color_mode		Color mode input control.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Mipi_Dsi_Ctrl0(BYTE* shudown, BYTE* color_mode);

/**
Set MIPI-DSI IP input pin control 1 (DPIUPDATECFG_I 1shot generation).
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_STATUS_ABNORMAL		DPI configuration update waiting.
*/
extern INT32 Im_DISP_Set_Mipi_Dsi_Ctrl1(void);

/**
Get MIPI-DSI IP input pin control 1.
@param[out]	update_config	Update configuration input control.<br>
							<ul><li>@ref D_IM_DISP_MDSUDC_READ_STOP
								<li>@ref D_IM_DISP_MDSUDC_READ_UPDATE_WAIT</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Mipi_Dsi_Ctrl1(BYTE* update_config);

/**
Set SR of IP (HDMI, MIPI).
@param[in]	ip	IP selection.<br>
				<ul><li>@ref D_IM_DISP_IP_HDMI
					<li>@ref D_IM_DISP_IP_MIPI</ul>
@param[in]	sr	SR to set.<br>
				<ul><li>@ref D_IM_DISP_SR_CANCEL
					<li>@ref D_IM_DISP_SR_RESET</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_SR_IP(BYTE ip, BYTE sr);

/**
Get SR of IP (HDMI, MIPI).
@param[out]	sr	SR status.<br>
				The value corresponding to each IP SR is set up.<br>
				(Two or more IP can be specified by the OR value.)<br>
				<ul><li>@ref D_IM_DISP_IP_HDMI
					<li>@ref D_IM_DISP_IP_MIPI</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_SR_IP(BYTE *sr);

/**
Set Write Channel control.
@param[in]	number	Write channel block number selection.<br>
					<ul><li>@ref E_IM_DISP_WC_NUM_0
						<li>@ref E_IM_DISP_WC_NUM_1</ul>
@param[in]	p2m		P2M macro setting parameters.<br>
@param[in]	pwch	PWCH macro setting parameters.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Set_Write_Channel_Ctrl(E_IM_DISP_WC_NUM number, T_IM_DISP_CTRL_P2M const *const p2m, T_IM_DISP_CTRL_PWCH const *const pwch);

/**
Get Write Channel control.
@param[in]	number	Write channel block number selection.<br>
					<ul><li>@ref E_IM_DISP_WC_NUM_0
						<li>@ref E_IM_DISP_WC_NUM_1</ul>
@param[out]	p2m		Register set value of P2M macro.<br>
@param[out]	pwch	Register set value of PWCH macro.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Write_Channel_Ctrl(E_IM_DISP_WC_NUM number, T_IM_DISP_CTRL_P2M  *const p2m, T_IM_DISP_CTRL_PWCH *const pwch);

/**
Get write channel response.
@param[in]	number		Write channel block number selection.<br>
						<ul><li>@ref E_IM_DISP_WC_NUM_0
							<li>@ref E_IM_DISP_WC_NUM_1</ul>
@param[out]	response	PWCH macro of AXI status (response value).<br>
						Value:<br>
						00b:Normal access success or Exclusive failure.<br>
						01b:Exclusive access.<br>
						10b:Slave error.<br>
						11b:Decode error.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Get_Write_Channel_Response(E_IM_DISP_WC_NUM number, ULONG *response);


#ifdef CO_DDIM_UTILITY_USE
/**
@name Utility Fucntions
@{
*/
//---------------------- utility section -------------------------------
/**
Set CSC matrix to covert from BT.601 to BT.709's RGB or no any convert.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			layer selection.<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_DCORE</ul>
@param[in]	convert			Convert type.<br>
							<ul><li>@ref E_IM_DISP_CC_MATRIX_NOCONVERT
								<li>@ref E_IM_DISP_CC_MATRIX_709</ul>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Change_CSC_Matrix(E_IM_DISP_SEL block, E_IM_DISP_SEL_LAYER layer, E_IM_DISP_CC_MATRIX convert);

/**
Change color bar's color which was used as black back.
@param[in]	block				Common block selection.<br>
								<ul><li>@ref E_IM_DISP_HDMI
									<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	black_back_color	The color used as black back.
*/
extern VOID Im_DISP_Change_BB_Color(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR black_back_color);

/**
Get the color bar's color which was used as black back.
@param[in]	block				Common block selection.<br>
								<ul><li>@ref E_IM_DISP_HDMI
									<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[out]	black_back_color	The color used as black back.
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Check_BB_Color(E_IM_DISP_SEL block, U_IM_DISP_IMAGE_COLOR* black_back_color);

/**
Change grid.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	ghnum			Number of horizontal grid line.<br>
							Value range:0~7.<br>
@param[in]	gvnum			Number of vertical grid line.<br>
							Value range:0~7.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Change_Grid(E_IM_DISP_SEL block, UINT32 ghnum, UINT32 gvnum);

/**
Draw single face frame.<br>
@param[in]	block			Common block selection.<br>
							<ul><li>@ref E_IM_DISP_HDMI
								<li>@ref E_IM_DISP_LCD_MIPI</ul>
@param[in]	index			Face frame data index.<br>
							Value range:0~15.<br>
@param[in]	enable			Face frame display enable.<br>
							<ul><li>@ref D_IM_DISP_ENABLE_OFF
								<li>@ref D_IM_DISP_ENABLE_ON</ul>
@param[in]	face			Face frame data parameter.<br>
@retval	D_DDIM_OK						Success.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
*/
extern INT32 Im_DISP_Draw_Face_Frame_Single(E_IM_DISP_SEL block, INT32 index, INT32 enable, T_IM_DISP_FACE_FRAME_PARAM const *const face);

//---------------------- colabo  section -------------------------------
/*		@}*/ /* end of im_disp_util */
#endif // CO_DDIM_UTILITY_USE
#endif /* __IM_DISP7_H__ */
