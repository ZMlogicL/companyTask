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


#ifndef __IM_HDMI_UNION_H__
#define __IM_HDMI_UNION_H__


#include <stdio.h>
#include <glib-object.h>
#include "imhdmienum.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_HDMI_UNION			(im_hdmi_union_union_get_type ())
#define IM_HDMI_UNION(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_HDMI_UNION, ImHdmiUnion))
#define IM_HDMI_UNION_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_HDMI_UNION, ImHdmiUnionClass))
#define IM_IS_HDMI_UNION(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_HDMI_UNION))
#define IM_IS_HDMI_UNION_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_HDMI_UNION))
#define IM_HDMI_UNION_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_HDMI_UNION, ImHdmiUnionClass))


typedef union _UhdmiAudConf0				UhdmiAudConf0;
typedef union _UhdmiAudConf1				UhdmiAudConf1;
typedef union _UhdmiAudConf2				UhdmiAudConf2;
typedef union _UhdmiAudSpdif1			UhdmiAudSpdif1;
typedef union _UhdmiFcAudsconf			UhdmiFcAudsconf;
typedef union _UhdmiFcInvidconf			UhdmiFcInvidconf;
typedef union _UhdmiFcAviconf3			UhdmiFcAviconf3;
typedef union _UhdmiFcAviconf0			UhdmiFcAviconf0;
typedef union _UhdmiFcAviconf1			UhdmiFcAviconf1;
typedef union _UhdmiFcAviconf2			UhdmiFcAviconf2;
typedef union _UhdmiFcAudiconf0			UhdmiFcAudiconf0;
typedef union _UhdmiFcAudiconf1			UhdmiFcAudiconf1;
typedef union _UhdmiFcAudiconf3			UhdmiFcAudiconf3;
typedef union _UhdmiFcPrconf				UhdmiFcPrconf;
typedef union _UhdmiActspcHdlrCfg 		UhdmiActspcHdlrCfg;
typedef union _UhdmiTxInvid0				UhdmiTxInvid0;
typedef union _UhdmiVpPrCd 				UhdmiVpPrCd;
typedef union _UhdmiVpConf 					UhdmiVpConf;
typedef union _UhdmiCscCfg 					UhdmiCscCfg;
typedef union _UhdmiCscScale 				UhdmiCscScale;
typedef union _UhdmiPhyStat0 				UhdmiPhyStat0;

typedef struct _ImHdmiUnion					ImHdmiUnion;
typedef struct _ImHdmiUnionClass		ImHdmiUnionClass;
typedef struct _ImHdmiUnionPrivate 	ImHdmiUnionPrivate;


/*----------------------------------------------------------------------	*/
/* Union  																	*/
/*----------------------------------------------------------------------	*/
/** structure of audConf0 register */
union _UhdmiAudConf0
{
		/**< guchar data access				*/
		guchar byte;
		/**< for bit access							*/
		struct
		{
				/**< i2sInEn : enable I2C data.<br>
				 * bit d[0]:I2Sdata[0] ~ d[3]:I2Sdata[3].								*/
				guchar i2sInEn 						:4;
				/**< Reserve																		*/
				guchar 										:1;
				/**< i2sSelect : Interface selection I2S/SPDIF.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_I2S_SELECT_S_PDIF
				 <li>@ref ImHdmiEnum_E_IM_HDMI_I2S_SELECT_I2S</ul>						*/
				guchar i2sSelect 						:1;
				/**< Reserve																		*/
				guchar 										:1;
				/**< swAudioFifoRst : Audio FIFOs software reset.<br>
				 Writing 0b: no action taken.<br>
				 Writing 1b: Resets all audio FIFOs.<br>
				 Reading from this register always returns 0b.					*/
				guchar swAudioFifoRst 			:1;
		} bit;
} ;

/** structure of audConf1 register */
union _UhdmiAudConf1
{
		/**< guchar data access			*/
		guchar byte;
		/**< for bit access						*/
		struct {
				/**< i2sWidth : I2S input data width.<br>
				 *  Value range : 16~24.															*/
				guchar i2sWidth 				:5;
				/**< i2sMode : I2S input data mode.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_I2S_MODE_STANDARD
				 <li>@ref ImHdmiEnum_E_IM_HDMI_I2S_MODE_RIGHT_JUSTIFIED
				 <li>@ref ImHdmiEnum_E_IM_HDMI_I2S_MODE_LEFT_JUSTIFIED</ul>		*/
				guchar i2sMode 				:3;
		} bit;
} ;

/** structure of audConf2 register */
union _UhdmiAudConf2
{
		/**< guchar data access	*/
		guchar byte;
		/**< for bit access				*/
		struct {
				/**< hbr : I2S hbr Mode Enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>		*/
				guchar hbr 				:1;
				/**< nlpcm : I2S nlpcm Mode Enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>		*/
				guchar nlpcm 		:1;
				/**< Reserve*/
				guchar 					:6;
		} bit;
} ;

/** structure of audSpdif1 register */
union _UhdmiAudSpdif1
{
		/**< guchar data access				*/
		guchar byte;
		/**< for bit access							*/
		struct {
				/**< spdifWidth : SPDIF input data width.<br>
				 * Value range : 16~24.														*/
				guchar spdifWidth 		:5;
				/**< Reserve																		*/
				guchar 							:1;
				/**< spdifHbrMode : SPDIF hbr mode.<br>
				 Value 0: Transmitted in the HDMI hbr packets.<br>
				 Value 1: Transmitted in the HDMI AUDS packets.			*/
				guchar spdifHbrMode :1;
				/**< setnlpcm : Select Non-Linear/Linear PCM mode.<br>
				 Value 0: Non-Linear PCM mode.<br>
				 Value 1: Linear PCM mode.												*/
				guchar setnlpcm 			:1;
		} bit;
} ;

/** structure of fcAudsconf register */
union _UhdmiFcAudsconf
{
		/**< guchar data access*/
		guchar byte;
		/**< for bit access	*/
		struct {
				/**< audPacketLayout : Set the audio packet layout.<br>
				 Value 0:layout 0, 1:layout 1.						*/
				guchar audPacketLayout		 	:1;
				/**< Reserve*/
				guchar 										:3;
				/**< Set the audio packet sample flat value.<br>
				 Value range : 0~15.									*/
				guchar audPacketSampflt 		:4;
		} bit;
} ;

/** structure of fcInvidconf register */
union _UhdmiFcInvidconf
{
		/**< guchar data access*/
		guchar byte;
		/**< for bit access	*/
		struct {
				/**< inIP : Input video mode.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_IN_I_P_PROGRESSIVE
				 <li>@ref ImHdmi_D_IM_HDMI_IN_I_P_INTERLACED</ul>	*/
				guchar inIP 							:1;
				/**< rVBlankInOsc : Used for CEA861-D modes with fractional Vblank.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
				 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>			*/
				guchar rVBlankInOsc 		:1;
				/**< Reserve	*/
				guchar 									:1;
				/**< dviModez : DVI mode selected.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI
				 <li>@ref ImHdmi_D_IM_HDMI_DVI_MODEZ_HDMI</ul>	*/
				guchar dviModez 				:1;
				/**< deInPolarity : Data enable input polarity.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
				 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>			*/
				guchar deInPolarity 			:1;
				/**< hsyncInPolarity : Hsync input polarity.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
				 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>			*/
				guchar hsyncInPolarity 		:1;
				/**< vsyncInPolarity : Vsync input polarity.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
				 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>			*/
				guchar vsyncInPolarity 		:1;
				/**< hdcpKeepout : Start/stop HDCP keepout window generation.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
				 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>			*/
				guchar hdcpKeepout 			:1;
		} bit;
} ;

/** structure of fcAviconf3 register */
union _UhdmiFcAviconf3
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< cn : IT content type according to CEA the specification.<br>
				 Value range : 0~3.													*/
				guchar cn :2;
				/**< Reserve															*/
				guchar :4;
				/**< yq : YCC Quantization range according to the CEA specification.<br>
				 Value range : 0~3.													*/
				guchar yq :2;
		} bit;
} ;

/** structure of fcAviconf0 register */
union _UhdmiFcAviconf0
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< rgcYccIndication : Y1,Y0 RGB or YCC indicator.<br>
				 Value 0:RGB, 1:YCC422 2:YCC444 3:YCC420.			*/
				guchar rgcYccIndication 		:2;
				/**< barInformation : Bar information data valid.<br>
				 Value range : 0~3.														*/
				guchar barInformation 			:2;
				/**< scanInformation : Scan information.<br>
				 Value range : 0~3.														*/
				guchar scanInformation 			:2;
				/**< activeFormatPresent : Active format present.<br>
				 Value range : 0~1.														*/
				guchar activeFormatPresent 	:1;
				/**< rgcYccIndication2 : Y2, Bit 2 of rgcYccIndication.<br>
				 Value range : 0~1.														*/
				guchar rgcYccIndication2 	:1;
		} bit;
} ;

/** structure of fcAviconf1 register */
union _UhdmiFcAviconf1
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< activeAspectRatio : Active aspect ratio.<br>
				 Value range : 0~15.													*/
				guchar activeAspectRatio	 	:4;
				/**< pictureAspectRatio : Picture aspect ratio.<br>
				 Value range : 0~3.														*/
				guchar pictureAspectRatio 		:2;
				/**< colorimetry : colorimetry.<br>
				 Value range : 0~3.														*/
				guchar colorimetry 					:2;
		} bit;
} ;

/** structure of fcAviconf2 register */
union _UhdmiFcAviconf2
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< nonUniformPictureScaling : Non-uniform picture scaling.<br>
				 Value range : 0~3.														*/
				guchar nonUniformPictureScaling 	:2;
				/**< quantizationRange : Quantization range.<br>
				 Value range : 0~3.														*/
				guchar quantizationRange 					:2;
				/**< extendedColorimetry : Extended colorimetry.<br>
				 Value range : 0~7.														*/
				guchar extendedColorimetry 				:3;
				/**< itContent : IT content.<br>
				 Value range : 0~1.														*/
				guchar itContent 									:1;
		} bit;
} ;

/** structure of fcAudiconf0 register */
union _UhdmiFcAudiconf0
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< cT : Coding Type.<br>
				 Value range : 0~31.		*/
				guchar cT 	:4;
				/**< cC : Channel count.<br>
				 Value range : 0~7.			*/
				guchar cC 	:3;
				/**< Reserve					*/
				guchar 		:1;
		} bit;
} ;

/** structure of fcAudiconf1 register */
union _UhdmiFcAudiconf1
{
		/**< guchar data access			*/
		guchar byte;
		/**< for bit access						*/
		struct {
				/**< sF : Sampling frequency.<br>
				 Value range : 0~7.				*/
				guchar sF 	:3;
				/**< Reserve						*/
				guchar		 	:1;
				/**< sS : Sampling size.<br>
				 Value range : 0~3.				*/
				guchar sS 	:2;
				/**< Reserve						*/
				guchar 		:2;
		} bit;
} ;

/** structure of fcAudiconf3 register */
union _UhdmiFcAudiconf3
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< lsv : Level shift value (for down mixing).<br>
				 Value range : 0x0~0xF.										*/
				guchar lsv 			:4;
				/**< dmInh : Down mix enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>			*/
				guchar dmInh 	:1;
				/**< lfepbl : LFE playback information.<br>
				 Value range : 0~3.												*/
				guchar lfepbl 	:2;
				/**< Reserve														*/
				guchar 				:1;
		} bit;
} ;

/** structure of fcPrconf register */
union _UhdmiFcPrconf
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< outputPrFactor : Outout video pixel repetition.<br>
				 Value:<br>
				 0:No action. Not used.<br>
				 1:No pixel repetition (pixel sent only once).<br>
				 2~10:Pixel will be sent a specified number of times.<br>
				 other:Reserved. Not used.								 	*/
				guchar outputPrFactor 		:4;
				/**< incomingPrFactor : Input video pixel repetition.<br>
				 Value:<br>
				 0:No action. Not used.<br>
				 1:No pixel repetition (pixel sent only once).<br>
				 2~10:Pixel will be sent a specified number of times.<br>
				 other:Reserved. Not used.								 	*/
				guchar incomingPrFactor 	:4;
		} bit;
} ;

/** structure of fcActspcHdlrCfg register */
union _UhdmiActspcHdlrCfg
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< actspcHdlrEn : active space value mode enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>				*/
				guchar actspcHdlrEn 	:1;
				/**< actspcHdlrTgl : Active space oscillating.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>				*/
				guchar actspcHdlrTgl 	:1;
				/**< Reserve															*/
				guchar 							:6;
		} bit;
} ;

/** structure of txInvid0 register */
union _UhdmiTxInvid0
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< videoMapping : Video Input mapping (color space/color depth).<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_16BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_16BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_16BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_IPI_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_16BIT</ul><br>			*/
				guchar videoMapping 				:5;
				/**< Reserve																										*/
				guchar 										:2;
				/**< internalDeGenerator : Internal data enable (DE) generator enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>															*/
				guchar internalDeGenerator	:1;
		} bit;
} ;

/** structure of vpPrCd register */
union _UhdmiVpPrCd
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< desiredPrFactor : Desired pixel repetition factor configuration.<br>
				 Value:<br>
				 0:No pixel repetition (pixel sent only once).<br>
				 1:Pixel sent 2 times (pixel repeated once) ~ 9:Pixel sent 10 times.<br>
				 other:Reserved. Not used.											 							*/
				guchar desiredPrFactor 	:4;
				/**< colorDepth : Color depth.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_16BIT</ul><br>
				 If the value is 0, same as ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT(= 4).			*/
				guchar colorDepth 			:4;
		} bit;
} ;

/** structure of vpConf register */
union _UhdmiVpConf
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< outputSelector : Video Packetizer output selection.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_PIXEL_PACKING
				 <li>@ref ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_YCC422_REMAP
				 <li>@ref ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_8BIT_BYPASS</ul><br>
				 If the value is 3, same as ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_8BIT_BYPASS(= 2).	*/
				guchar outputSelector 	:4;
				/**< bypassSelect : bypass select.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_BYPASS_SELECT_PIXEL_REPEATER
				 <li>@ref ImHdmiEnum_E_IM_HDMI_BYPASS_SELECT_VIDEO_PACKETIZER</ul>							*/
				guchar bypassSelect 	:4;
				/**< ycc422En : YCC422 select enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>																	*/
				guchar ycc422En 			:1;
				/**< prEn : Pixel repeater enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>																	*/
				guchar prEn 					:1;
				/**< ppEn : Pixel packing enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>																	*/
				guchar ppEn 				:1;
				/**< bypassEn : Bypass enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>																	*/
				guchar bypassEn 			:1;
				/**< Reserve																																*/
				guchar 							:1;
		} bit;
} ;

/** structure of cscCfg register */
union _UhdmiCscCfg
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< decmode : Chroma decimation configuration.<br>
				 Value:<br>
				 0:decimation disabled<br>
				 1:Hd(z) = 1<br>
				 2:Hu(z) = 1/ 2 + z^(-11)+1/2 z^(-2)<br>
				 3:Hd(z)x2^(11) = -5+12z^(-2) - 22z^(-4)+39z^(-8)+109z^(-10) <br>
				 -204z^(-12)+648z^(-14) + 1024z^(-15) <br>
				 +648z^(-16)-204z^(-18) +109z^(-20)- 65z^(-22) <br>
				 +39z^(-24) -22z^(-26)+12z^(-28)-5z^(-30)					*/
				guchar decmode 	:2;
				/**< Reserve																*/
				guchar 					:2;
				/**< intmode : Chroma interpolation configuration.<br>
				 Value:<br>
				 0:interpolation disabled<br>
				 1:Hd(z) = Hu (z) =1 + z^(-1)<br>
				 2:Hu(z) = Hu(z)=1/ 2 + z^(-11)+1/2 z^(-2)<br>
				 3:interpolation disabled											*/
				guchar intmode 	:2;
				/**< Reserve																*/
				guchar 					:1;
				/**< cscLimit : CSC limit setting enable.<br>
				 <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
				 <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>					*/
				guchar cscLimit :1;
		} bit;
} ;

/** structure of cscScale register */
union _UhdmiCscScale
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< cscscale : Scale factor.<br>
				 Value range : 0~2.																						*/
				guchar cscscale 				:2;
				/**< Reserve																								*/
				guchar	 							:2;
				/**< cscColorDepth : Color space converter color depth configuration.<br>
				 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_10BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_12BIT
				 <li>@ref ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_16BIT</ul><br>
				 If the value is 0, same as ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT(= 4).			*/
				guchar cscColorDepth :4;
		} bit;
} ;

/** structure of phy_stat0 register */
union _UhdmiPhyStat0
{
		/**< guchar data access		*/
		guchar byte;
		/**< for bit access					*/
		struct {
				/**< txPhyLock : TX PHY PLL lock indication.<br>
				 Value 0:PLL is unlocked, 1:PLL is locked.						*/
				guchar txPhyLock	:1;
				/**< hpd : HDMI Hot Plug Detect indication.<br>
				 Value 0:non active, 1:active.											*/
				guchar hpd 				:1;
				/**< Reserve																	*/
				guchar 						:2;
				/**< pxSense0 : TX PHY RX_SENSE indication for TMDS channel 0 driver.<br>
				 Value 0:non active, 1:active.											*/
				guchar pxSense0 	:1;
				/**< rxSense1 : TX PHY RX_SENSE indication for TMDS channel 1 driver.<br>
				 Value 0:non active, 1:active.											*/
				guchar rxSense1 	:1;
				/**< rxSense2 : TX PHY RX_SENSE indication for TMDS channel 2 driver.<br>
				 Value 0:non active, 1:active.											*/
				guchar rxSense2 	:1;
				/**< rxSense3 : TX PHY RX_SENSE indication for TMDS channel 3 driver.<br>
				 Value 0:non active, 1:active.											*/
				guchar rxSense3 	:1;
		} bit;
} ;


struct _ImHdmiUnion
{
		GObject parent;
		ImHdmi *imhdmi;
		ImHdmiStruct *imHdmiStruct;
};

struct _ImHdmiUnionClass
{
		GObjectClass parentClass;
};


GType									im_hdmi_union_union_get_type(void)	G_GNUC_CONST;
ImHdmiUnion*					im_hdmi_union_union_new(void);
/**
 * @brief	Get control data of HDMI Transmitter.
 * @param[out]	ctrl			Control data.
 * @retval		D_DDIM_OK						success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR		Input Parameter Error.
 * @remarks		This API uses DDIM_User_Clr_Flg().
 */
extern	gint32 im_hdmi_get_ctrl(ImHdmiUnion *self);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_HDMI_UNION_H__ */
