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


#ifndef __IM_HDMI_STRUCT_H__
#define __IM_HDMI_STRUCT_H__


#include <stdio.h>
#include <glib-object.h>
#include "imhdmiunion.h"


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_HDMI_STRUCT			(im_hdmi_struct_struct_get_type ())
#define IM_HDMI_STRUCT(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_HDMI_STRUCT, ImHdmiStruct))
#define IM_HDMI_STRUCT_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_HDMI_STRUCT, ImHdmiStructClass))
#define IM_IS_HDMI_STRUCT(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_HDMI_STRUCT))
#define IM_IS_HDMI_STRUCT_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_HDMI_STRUCT))
#define IM_HDMI_STRUCT_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_HDMI_STRUCT, ImHdmiStructClass))


// Frame Composer SPD packet Data number.
/**< Vendor Name:8.		*/
#define ImHdmi_D_IM_HDMI_FC_SPD_VENDER_NAME_NUM	(8)
/**< Product Name:16.	*/
#define ImHdmi_D_IM_HDMI_FC_SPD_PRO_NAME_NUM			(16)

// Frame Composer VSD packet Data number.
/**< IEEE:3.		*/
#define ImHdmi_D_IM_HDMI_FC_VSD_IEEE_DATA_NUM			(3)
/**< Payload:24.	*/
#define ImHdmi_D_IM_HDMI_FC_VSD_PAYLOAD_NUM			(24)

/**< PHY Register number	*/
#define ImHdmi_D_IM_HDMI_PHY_REG_NUM							(8)

// CSC Matrix number.
/**< CSC Matrix columns:A-C.	*/
#define ImHdmiStruct_D_IM_HDMI_CSC_CONF_COLUMN_NUM		(3)
/**< CSC Matrix rows:1-4.		*/
#define ImHdmiStruct_D_IM_HDMI_CSC_CONF_ROW_NUM				(4)


typedef struct _ThdmiVideoPacketizer			ThdmiVideoPacketizer;
typedef struct _ThdmiFrameComposer			ThdmiFrameComposer;
typedef struct _ThdmiFcSpd								ThdmiFcSpd;
typedef struct _ThdmiFcVsd								ThdmiFcVsd;
typedef struct _ThdmiAudio								ThdmiAudio;
typedef struct _ThdmiCscConfig						ThdmiCscConfig;
typedef struct _ThdmiCscCoef							ThdmiCscCoef;
typedef struct _ThdmiPllConfig						ThdmiPllConfig;
typedef struct _ThdmiAudioConfig					ThdmiAudioConfig;
typedef struct _ThdmiInfoFrames					ThdmiInfoFrames;
typedef struct _ThdmiPhyI2cmConfig				ThdmiPhyI2cmConfig;
typedef struct _ThdmiI2cmConfig					ThdmiI2cmConfig;
typedef struct _ImHdmiStruct							ImHdmiStruct;
typedef struct _ImHdmiStructClass					ImHdmiStructClass;
typedef struct _ImHdmiStructPrivate 			ImHdmiStructPrivate;


/*----------------------------------------------------------------------	*/
/* Structure  																	*/
/*----------------------------------------------------------------------	*/
/**
Control data of Video Packetizer.<br>
*/
struct _ThdmiVideoPacketizer
{
		/**< vpPrCd: Video Packetizer Pixel Repetition and Color Depth Register.				*/
		UhdmiVpPrCd vpPrCd;
		/**< vpRemap: Video Packetizer YCC422 Remapping Register.<br>
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_VP_REMAP_16BIT
		 <li>@ref ImHdmiEnum_E_IM_HDMI_VP_REMAP_20BIT
		 <li>@ref ImHdmiEnum_E_IM_HDMI_VP_REMAP_24BIT</ul>										*/
		EhdmiVpRemap vpRemap;
		/**< vpConf: Video Packetizer Output, Bypass and Enable Configuration Register.	*/
		UhdmiVpConf vpConf;
} ;

/**
Control data of Frame Composer.<br>
*/
struct _ThdmiFrameComposer
{
		/**< fcInvidconf: Frame Composer Input Video Configuration.							*/
		UhdmiFcInvidconf fcInvidconf;
		/**< fcInhactiv: Frame Composer Input Video HActive Pixels Register 0/1.<br>
		 Value range : 0~16838.																								*/
		gushort fcInhactiv;
		/**< fcInhblank: Frame Composer Input Video HBlank Pixels Register 0/1.<br>
		 Value range : 0~8191.																								*/
		gushort fcInhblank;
		/**< fcInvactiv: Frame Composer Input Video VActive Pixels Register 0/1.<br>
		 Value range : 0~8191.																								*/
		gushort fcInvactiv;
		/**< fcInvblank: Frame Composer Input Video VBlank Pixels Register.<br>
		 Value range : 0~255.																									*/
		guchar fcInvblank;
		/**< fcHsyncindelay: Frame Composer Input Video HSync Front Porch Register 0/1.<br>
		 Value range : 0~8191.																								*/
		gushort fcHsyncindelay;
		/**< fcHsyncinwidth: Frame Composer Input Video HSync Width Register 0/1.<br>
		 Value range : 0~1023.																								*/
		gushort fcHsyncinwidth;
		/**< fcVsyncindelay: Frame Composer Input Video VSync Front Porch Register.<br>
		 Value range : 0~255.																									*/
		guchar fcVsyncindelay;
		/**< fcVsyncinwidth: Frame Composer Input Video VSync Width Register.<br>
		 Value range : 0~63.																									*/
		guchar fcVsyncinwidth;
		/**< fcAviconf3: Frame Composer AVI Packet Configuration Register 3.				*/
		UhdmiFcAviconf3 fcAviconf3;
		/**< fcAviconf0: Frame Composer AVI Packet Configuration Register 0.				*/
		UhdmiFcAviconf0 fcAviconf0;
		/**< fcAviconf1: Frame Composer AVI Packet Configuration Register 1.				*/
		UhdmiFcAviconf1 fcAviconf1;
		/**< fcAviconf2: Frame Composer AVI Packet Configuration Register 2.				*/
		UhdmiFcAviconf2 fcAviconf2;
		/**< fcAvivid: Frame Composer AVI Packet VIC Register.<br>
		 Value range : 0~255.																									*/
		guchar fcAvivid;
		/**< fcPrconf: Frame Composer Pixel Repetition Configuration Register.			*/
		UhdmiFcPrconf fcPrconf;
} ;

/**
Control data of Frame Composer SPD Packet data.<br>
*/
struct _ThdmiFcSpd
{
		/**< fcSpdvendorname[]: Vendor Name Regsiter Array.		*/
		guchar fcSpdvendorname[ImHdmi_D_IM_HDMI_FC_SPD_VENDER_NAME_NUM];
		/**< fcSpdproductname[]: Product Name Regsiter Array.		*/
		guchar fcSpdproductname[ImHdmi_D_IM_HDMI_FC_SPD_PRO_NAME_NUM];
		/**< fcSpddeviceinf: Source Product Descriptor Regsiter.		*/
		guchar fcSpddeviceinf;
} ;

/**
Control data of Frame Composer VSI Packet data.<br>
*/
struct _ThdmiFcVsd
{
		/**< fcVsdieeeid[]: VSI IEEE registration identifier.					*/
		guchar fcVsdieeeid[ImHdmi_D_IM_HDMI_FC_VSD_IEEE_DATA_NUM];
		/**< fcVsdsize: VSI Packet Data Size.											*/
		guchar fcVsdsize;
		/**< fcVsdpayload[]: VSI Packet Data Payload Register Array.	*/
		guchar fcVsdpayload[ImHdmi_D_IM_HDMI_FC_VSD_PAYLOAD_NUM];
} ;

/**
Control data of Audio.<br>
*/
struct _ThdmiAudio
{
		/**< audConf0: Audio I2S Control Register 0.																				*/
		UhdmiAudConf0 audConf0;
		/**< audConf1: Audio I2S Control Register 1.																				*/
		UhdmiAudConf1 audConf1;
		/**< audConf2: Audio I2S Control Register 2.																				*/
		UhdmiAudConf2 audConf2;
		/**< audN1 : Audio Clock Regenerator N Value Register 1.<br>
		 Value range : 0x00~0xFF.																												*/
		guchar audN1;
		/**< audN2 : Audio Clock Regenerator N Value Register 2.<br>
		 Value range : 0x00~0xFF.																												*/
		guchar audN2;
		/**< aud_n3.AudN : HDMI Audio Clock Regenerator N value.<br>
		 Value range : 0x0~0xF.																													*/
		guchar audN3Audn;
		/**< aud_n3.ncts_atomic_write : HDMI Audio Clock Regenerator N value.<br>
		 Value range : 0x0~0x1.																													*/
		guchar audNctsAtomicWrite;
		/**< aud_cts3.CTS_manual : To select whether the CTS value manually to use.
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_AUTO
		 <li>@ref ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_MANUAL</ul>																	*/
		EhdmiCtsManual ctsManual;
		/**< audCts1 : Audio Clock Regenerator CTS Value Register 1.<br>
		 Value range : 0x00~0xFF.																												*/
		guchar audCts1;
		/**< audCts2 : Audio Clock Regenerator CTS Value Register 2.<br>
		 Value range : 0x00~0xFF.																												*/
		guchar audCts2;
		/**< aud_cts3.AudCTS : HDMI Audio Clock Regenerator CTS calculated value.<br>
		 Value range : 0x0~0xF.																													*/
		guchar audCts3Audcts;
		/**< audSpdif1: Audio SPDIF Control Register 1.																		*/
		UhdmiAudSpdif1 audSpdif1;
		/**< audInputclkfs: Audio Input Clock FS Factor Register.<br>
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_128XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_256XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_512XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_64XFS</ul><br>
		 If the value is 3, invalid.<br>
		 If the value is 5-7, same as ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_128XFS(= 0).										*/
		guchar audInputclkfs;
		/**< fcAudiconf0 : Frame Composer AUD Packet Configuration Register 0.							*/
		UhdmiFcAudiconf0 fcAudiconf0;
		/**< fcAudiconf1 : Frame Composer AUD Packet Configuration Register 1.							*/
		UhdmiFcAudiconf1 fcAudiconf1;
		/**< fcAudiconf2 : Frame Composer AUD Packet Configuration Register 2.<br>
		 Value range : 0~255.																														*/
		guchar fcAudiconf2;
		/**< fcAudiconf3 : Frame Composer AUD Packet Configuration Register 3.							*/
		UhdmiFcAudiconf3 fcAudiconf3;
		/**< fcAudsconf: Frame Composer Audio Sample Flat and Layout Configuration Register.*/
		UhdmiFcAudsconf fcAudsconf;
		/**< fc_audschnl7.oiec_sampfreq: Sampling frequency.<br>													*/
		guchar sampfreq;
		/**< fc_audschnl8.oiecWordlength: Word length configuration.<br>										*/
		guchar oiecWordlength;
} ;

/**
Color Space Converter configuration.<br>
*/
struct _ThdmiCscConfig
{
		/**< Color Space Converter Interpolation and Decimation Configuration Register.	*/
		UhdmiCscCfg cscCfg;
		/**< Color Space Converter Scale and Deep Color Configuration Register.				*/
		UhdmiCscScale cscScale;
} ;

/**
Color Space Converter Matrix Coefficient table.<br>
*/
struct _ThdmiCscCoef
{
		/**< Color Space Converter Matrix Coefficient Register MSB.<br>
		 Value range :0x00~0xFF.																	*/
		guchar msb;
		/**< Color Space Converter Matrix Coefficient Register LSB.<br>
		 Value range :0x00~0xFF.																	*/
		guchar lsb;
} ;

/**
Control data of PLL configuration.<br>
*/
struct _ThdmiPllConfig
{
		/**< vpPrCd: Video Packetizer Pixel Repetition and Color Depth Register.	*/
		UhdmiVpPrCd vpPrCd;
		/**< phyRegAddr: PHY Register Number.<br>
		 Value range : 1~8																									*/
		guchar phyRegNum;
		/**< phyRegAddr : PHY Register Address (Offset).<br>
		 Address:
		 <ul><li>0x00 : PWRCTRL<br>
		 <li>0x06 : OPMODE_PLLCFG<br>
		 <li>0x09 : CKSYMTXCTRL<br>
		 <li>0x0E : VLEVCTRL<br>
		 <li>0x10 : PLLCURRCTRL<br>
		 <li>0x14 : PLLCTRL<br>
		 <li>0x15 : PLLGMPCTRL<br>
		 <li>0x19 : TXTERM<br></ul>																					*/
		guchar phyRegAddr[ImHdmi_D_IM_HDMI_PHY_REG_NUM];
		/**< phyRegData : PHY Register Value.<br>
		 Value range : 0x0000~0xFFFF.																				*/
		gushort phyRegData[ImHdmi_D_IM_HDMI_PHY_REG_NUM];
} ;

/**
Control data of Audio configuration.<br>
*/
struct _ThdmiAudioConfig
{
		/**< i2sSelect : Interface selction I2S/SPDIF.<br>
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_I2S_SELECT_S_PDIF
		 <li>@ref ImHdmiEnum_E_IM_HDMI_I2S_SELECT_I2S</ul>							*/
		EhdmiI2sSelect i2sSelect;
		/**< audConf1: Audio I2S Control Register 1.													*/
		UhdmiAudConf1 audConf1;
		/**< audConf2: Audio I2S Control Register 2.													*/
		UhdmiAudConf2 audConf2;
		/**< audSpdif1: Audio SPDIF Control Register 1.											*/
		UhdmiAudSpdif1 audSpdif1;
		/**< audInputclkfs: Audio Input Clock FS Factor Register.<br>
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_128XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_256XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_512XFS
		 <li>@ref ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_64XFS</ul><br>
		 If the value is 3, invalid.<br>
		 If the value is 5-7, same as ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_128XFS(= 0).	*/
		guchar audInputclkfs;
		/**< audN1 : Audio Clock Regenerator N Value Register 1.<br>
		 Value range : 0x00~0xFF.																					*/
		guchar audN1;
		/**< audN2 : Audio Clock Regenerator N Value Register 2.<br>
		 Value range : 0x00~0xFF.																					*/
		guchar audN2;
		/**< aud_n3.AudN : HDMI Audio Clock Regenerator N value.<br>
		 Value range : 0x0~0xF.																						*/
		guchar audN3Audn;
		/**< aud_n3.ncts_atomic_write : HDMI Audio Clock Regenerator N value.<br>
		 Value range : 0x0~0x1.																						*/
		guchar audNctsAtomicWrite;
		/**< aud_cts3.CTS_manual : To select whether the CTS value manually to use.
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_AUTO
		 <li>@ref ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_MANUAL</ul>			*/
		EhdmiCtsManual ctsManual;
		/**< audCts1 : Audio Clock Regenerator CTS Value Register 1.<br>
		 Value range : 0x00~0xFF.																					*/
		guchar audCts1;
		/**< audCts2 : Audio Clock Regenerator CTS Value Register 2.<br>
		 Value range : 0x00~0xFF.																					*/
		guchar audCts2;
		/**< aud_cts3.AudCTS : HDMI Audio Clock Regenerator CTS calculated value.<br>
		 Value range : 0x0~0xF.																						*/
		guchar audCts3Audcts;
		/**< fc_audschnl7.oiec_sampfreq: Sampling frequency.<br>						*/
		guchar sampfreq;
		/**< fc_audschnl8.oiecWordlength: Word length configuration.<br>			*/
		guchar oiecWordlength;
		/**< fcAudsconf: Frame Composer Audio Sample Flat and Layout Configuration Register.	*/
		UhdmiFcAudsconf fcAudsconf;
} ;

/**
Control data of Infoframes configuration.<br>
*/
struct _ThdmiInfoFrames
{
		/**< fcAviconf0: Frame Composer AVI Packet Configuration Register 0.					*/
		UhdmiFcAviconf0 fcAviconf0;
		/**< fcAviconf1: Frame Composer AVI Packet Configuration Register 1.					*/
		UhdmiFcAviconf1 fcAviconf1;
		/**< fcAviconf2: Frame Composer AVI Packet Configuration Register 2.					*/
		UhdmiFcAviconf2 fcAviconf2;
		/**< fcAviconf3: Frame Composer AVI Packet Configuration Register 3.					*/
		UhdmiFcAviconf3 fcAviconf3;
		/**< fcAvivid: Frame Composer AVI Packet VIC Register.<br>
		 Value range : 0~255.																										*/
		guchar fcAvivid;
		/**< fcPrconf: Frame Composer Pixel Repetition Configuration Register.				*/
		UhdmiFcPrconf fcPrconf;
		/**< fcAudiconf0 : Frame Composer AUD Packet Configuration Register 0.			*/
		UhdmiFcAudiconf0 fcAudiconf0;
		/**< fcAudiconf1 : Frame Composer AUD Packet Configuration Register 1.			*/
		UhdmiFcAudiconf1 fcAudiconf1;
		/**< fcAudiconf2 : Frame Composer AUD Packet Configuration Register 2.<br>
		 Value range : 0~255.																										*/
		guchar fcAudiconf2;
		/**< fcAudiconf3 : Frame Composer AUD Packet Configuration Register 3.			*/
		UhdmiFcAudiconf3 fcAudiconf3;
		/**< fc_vsdieeeid0/1/2 : 24bits IEEE ID.<br>
		 index=0 -> fc_vsdieeeid0 ~ index=2 -> fc_vsdieeeid2.<br>
		 Value range : 0~255.																										*/
		guchar fcVsdieeeid[3];
		/**< Video Mode.<br>
		 <ul><li>@ref ImHdmi_D_IM_HDMI_VIDEO_MODE_HDMI
		 <li>@ref ImHdmi_D_IM_HDMI_VIDEO_MODE_3D</ul>											*/
		guchar videoMode;
		/**< Video Format.<br>
		 If Video Mode=HDMI, this is HDMI Video Format.<br>
		 - Value range : 0~255.<br>
		 If Video Mode=3D, this is Format of 3D Video data and 3D_Meta_present.<br>
		 - bit[7:4]: Format of 3D Video data.<br>
		 - bit[3]: 3D_Meta_present.																							*/
		guchar videoFormat;
		/**< 3D_Meta_present.<br>
		 Value range : 0~1.																										*/
		guchar metaPresent;
		/**< 3D_EXT_DATA – Additional Video Format.<br>
		 Value range : 0~15.																										*/
		guchar additionalVideoFormat;
		/**< 3D_Metadata_Type.<br>
		 Value range : 0~7.																										*/
		guchar metaType;
		/**< 3D_Metadata_Length.<br>
		 Value range : 0~31.																										*/
		guchar metaLength;
		/**< 3D_Metadata.<br>
		 Value range : 0~255.																									*/
		guchar metaData[8];
		/**< the HDMI 2.0 scrambler feature.																		*/
		guchar scramblerOn;
} ;

/**
Control data of phy_i2cm.<br>
*/
struct _ThdmiPhyI2cmConfig
{
		/**< phyI2cmAddress: PHY I2C Address Configuration Register.<br>
		 Value range : 0x00~0xFF.												*/
		guchar phyI2cmAddress;
		/**< phy_i2cm_datao_0/phy_i2cm_datao_1: PHY I2C Data Write Register.<br>
		 Value range : 0x00~0xFF.												*/
		guchar phyI2cmDatao[2];
} ;

/**
Control data of i2cm.<br>
*/
struct _ThdmiI2cmConfig
{
		/**< i2cmAddress: I2C DDC Slave Configuration Register.<br>
		 Value range : 0x00~0xFF.															*/
		guchar i2cmSlaveaddr;
		/**< i2cmAddress: I2C DDC Address Configuration Register.<br>
		 Value range : 0x00~0xFF.															*/
		guchar i2cmAddress;
		/**< i2cmSegaddr: PHY I2C Data Write Register.<br>
		 Value range : 0x00~0xFF.															*/
		guchar i2cmSegaddr;
		/**< i2cmSegptr: PHY I2C Data Write Register.<br>
		 Value range : 0x00~0xFF.															*/
		guchar i2cmSegptr;
		/**< i2cmOperation: I2C DDC RD/RD_EXT/WR Operation Register.<br>
		 <ul><li>@ref ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD
		 <li>@ref ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD_EXT
		 <li>@ref ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8
		 <li>@ref ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8_EXT
		 <li>@ref ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_WR</ul>	*/
		EhdmiI2cmOperation i2cmOperation;
} ;


struct _ImHdmiStruct
{
	GObject parent;
	ImHdmi *imHdmi;
	/**< txInvid0.videoMapping: Video Input mapping.<br>
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
	 <li>@ref ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_16BIT</ul><br>		*/
	EhdmiVideoMapping 	videoInputMapping;
	/**< fcInvidconf.hdcpKeepout: Start/stop HDCP keepout window generation.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
	 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>													*/
	guchar 										hdcpKeepout;
	/**< fcInvidconf.vsyncInPolarity: Vsync input polarity.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
	 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>													*/
	guchar 										vsyncInPolarity;
	/**< fcInvidconf.hsyncInPolarity: Hsync input polarity.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
	 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>													*/
	guchar 										hsyncInPolarity;
	/**< fcInvidconf.deInPolarity: Data enable input polarity.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
	 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>													*/
	guchar 										deInPolarity;
	/**< fcInvidconf.dviModez : DVI mode selected.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_DVI_MODEZ_DVI
	 <li>@ref ImHdmi_D_IM_HDMI_DVI_MODEZ_HDMI</ul>											*/
	guchar 										dviModez;
	/**< fcInvidconf.rVBlankInOsc: Used for CEA861-D modes.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_ACTIVE_LOW
	 <li>@ref ImHdmi_D_IM_HDMI_ACTIVE_HIGH</ul>													*/
	guchar 										rVBlankInOsc;
	/**< fcInvidconf.inIP: Input video mode.<br>
	 <ul><li>@ref ImHdmi_D_IM_HDMI_IN_I_P_PROGRESSIVE
	 <li>@ref ImHdmi_D_IM_HDMI_IN_I_P_INTERLACED</ul>										*/
	guchar 										inIP;
	/**< fc_inhactiv0/1: Input video Horizontal active pixel region width.<br>
	 Value range :0~16383.																				*/
	gushort 										hInActiv;
	/**< fc_invactiv0/1: Input video Vertical active pixel region width.<br>
	 Value range :0~8191.																					*/
	gushort 										vInActiv;
	/**< fc_invact_2d_0/1: 2D Input video vertical active pixel region width.<br>
	 Value range :0~4095.																					*/
	gushort 										fcInvact2d;
	/**< fcActspcHdlrCfg: Frame Composer Active Space Control.				*/
	UhdmiActspcHdlrCfg fcActspcHdlrCfg;
	/**< fcInhblank: Frame Composer Input Video HBlank Pixels Register 0/1.<br>
	 Value range : 0~8191.																					*/
	gushort 										fcInhblank;
	/**< fcInvblank: Frame Composer Input Video VBlank Pixels Register.<br>
	 Value range : 0~255.																					*/
	guchar 										fcInvblank;
	/**< fcHsyncindelay: Frame Composer Input Video HSync Front Porch Register 0/1.<br>
	 Value range : 0~8191.																					*/
	gushort 										fcHsyncindelay;
	/**< fcHsyncinwidth: Frame Composer Input Video HSync Width Register 0/1.<br>
	 Value range : 0~1023.																					*/
	gushort	 									fcHsyncinwidth;
	/**< fcVsyncindelay: Frame Composer Input Video VSync Front Porch Register.<br>
	 Value range : 0~255.																					*/
	guchar 										fcVsyncindelay;
	/**< fcVsyncinwidth: Frame Composer Input Video VSync Width Register.<br>
	 Value range : 0~63.																						*/
	guchar 										fcVsyncinwidth;
	/**< PLL configuration data.																		*/
	ThdmiPllConfig 			pllConfig;
	/**< Audio configuration data.																	*/
	ThdmiAudioConfig 	audioConfig;
	/**< Infoframes configuration data.															*/
	ThdmiInfoFrames 		infoFrames;
};

struct _ImHdmiStructClass
{
	GObjectClass parentClass;
};

GType						im_hdmi_struct_struct_get_type(void)	G_GNUC_CONST;
ImHdmiStruct*					im_hdmi_struct_struct_new(void);
/**
 * @brief	Set Color Space Converter.
 * @param[in]	config		CSC configuration data.
 * @param[in]	matrix		Color Space Converter Matrix.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_csc(ImHdmiStruct *self, ThdmiCscConfig const *const config,
													const ThdmiCscCoef matrix[ImHdmiStruct_D_IM_HDMI_CSC_CONF_COLUMN_NUM][ImHdmiStruct_D_IM_HDMI_CSC_CONF_ROW_NUM]);
/**
 * @brief	Set Video Sampler.
 * @param[in]	txInvid0		Video Sampler register.
 * @retval		void.
 */
extern	void im_hdmi_struct_set_video_sampler(ImHdmiStruct *self, UhdmiTxInvid0 txInvid0);
/**
 * @brief	Get Video Sampler.
 * @param[out]	txInvid0		Video Sampler register.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_video_sampler(ImHdmiStruct *self, UhdmiTxInvid0* txInvid0);
/**
 * @brief	Set Video Packetizer.
 * @param[in]	videoPacketizer		Video Packetizer data.
 * @retval		D_DDIM_OK					success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_video_packetizer(ImHdmiStruct *self, ThdmiVideoPacketizer const *const videoPacketizer);
/**
 * @brief	Get Video Packetizer.
 * @param[out]	videoPacketizer		Video Packetizer data.
 * @retval		D_DDIM_OK					success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_video_packetizer(ImHdmiStruct *self, ThdmiVideoPacketizer *const videoPacketizer);
/**
 * @brief	Set Frame Composer.
 * @param[in]	frameComposer		Frame Composer data.
 * @retval		D_DDIM_OK					success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_frame_composer(ImHdmiStruct *self, ThdmiFrameComposer const *const frameComposer);
/**
 * @brief	Get Frame Composer.
 * @param[out]	frameComposer		Frame Composer data.
 * @retval		D_DDIM_OK					success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_frame_composer(ImHdmiStruct *self, ThdmiFrameComposer *const frameComposer);
/**
 * @brief	Set Frame Composer (SPD Packet Data).
 * @param[in]	fcSpd		Frame Composer SPD Packet data.
 * @retval	D_DDIM_OK	success.
 * @retval	ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_frame_composer_spd(ImHdmiStruct *self, ThdmiFcSpd const *const fcSpd);
/**
 * @brief	Get Frame Composer (SPD Packet Data).
 * @param[out]	fcSpd		Frame Composer SPD Packet data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_frame_composer_spd(ImHdmiStruct *self, ThdmiFcSpd *const fcSpd);
/**
 * @brief	Set Frame Composer (Vendor Specific).
 * @param[in]	fcVsd		Frame Composer VSI Packet data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_frame_composer_vsd(ImHdmiStruct *self, ThdmiFcVsd const *const fcVsd);
/**
 * @brief	Get Frame Composer (Vendor Specific).
 * @param[out]	fcVsd		Frame Composer VSI Packet data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_frame_composer_vsd(ImHdmiStruct *self, ThdmiFcVsd *const fcVsd);
/**
 * @brief	Set Main Controller.
 * @param[in]	mcFlowctrl		Main Controller Feed Through Control Register.<br>
 * Value 0:CSC is bypassed, 1:CSC is in the video data path.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_main_controller(ImHdmiStruct *self, guchar mcFlowctrl);

/**
 * @brief	Get Main Controller.
 * @param[out]	mcFlowctrl		Main Controller Feed Through Control Register.
 * Value 0:CSC is bypassed, 1:CSC is in the video data path.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_main_controller(ImHdmiStruct *self, guchar* mcFlowctrl);

/**
 * @brief	Set Audio data.
 * @param[in]	audio		Audio data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_set_audio(ImHdmiStruct *self, ThdmiAudio const *const audio);

/**
 * @brief	Get Audio data.
 * @param[out]	audio		Audio data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_audio(ImHdmiStruct *self, ThdmiAudio *const audio);

/**
 * @brief	Set Interrupt callback function.
 * @param[in]	vpCallback		callback funcion pointer.
 * @retval		void.
 */
extern	void im_hdmi_struct_set_int_callback(ImHdmiStruct *self, VP_HDMI_CALLBACK vpCallback);

/**
 * @brief	Set Interrupt Mute.
 * @param[in]	interruptRegister	Interrupt register type.<br>
 * 									<ul><li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_I2CMPHY_STAT0
 * 								 </ul>
 * @param[in]	mute	mute setting value.<br>
 * bit d[0] ~ d[7]:Detailed interrupt types.<br>
 * Value 0:mute cancel, 1:mute.
 * @retval	void.
 * @remarks
 * The 2nd parameter (mute) is the interrupt type is determined for each bit of each interrupt register.<br>
 * For more information see below.<br><br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0		- @ref EhdmiIhFcStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1		- @ref EhdmiIhFcStat1<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2		- @ref EhdmiIhFcStat2<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0		- @ref EhdmiIhAsStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0		- @ref EhdmiIhPhyStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0	- @ref EhdmiIhI2cmStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0		- @ref EhdmiIhCecStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0		- @ref EhdmiIhVpStat0<br>
 * 	Interrupt register type:ImHdmiEnum_E_IM_HDMI_INT_REG_I2CMPHY_STAT0	- @ref EhdmiIhI2cmphyStat0
 */
extern	void im_hdmi_struct_set_int_mute(ImHdmiStruct *self, EhdmiIntReg interruptRegister, guchar mute);

/**
 * @brief	Get Interrupt Mute.
 * @param[in]	interruptRegister	Interrupt register type.
 * 									<ul><li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0
 * 										<li>@ref ImHdmiEnum_E_IM_HDMI_INT_REG_I2CMPHY_STAT0
 * 									</ul>
 * @param[out]	mute mute setting value.<br>
 * bit d[0] ~ d[7]:Detailed interrupt types.<br>
 * Value 0:mute cancel, 1:mute.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 * @remarks
 * Specification of the second parameter is similar to im_hdmi_struct_set_int_mute().
 */
extern	gint32 im_hdmi_struct_get_int_mute(ImHdmiStruct *self, EhdmiIntReg interruptRegister, guchar* mute);

/**
 * @brief	Get PHY status.
 * @param[out]	status		PHY status register.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 */
extern	gint32 im_hdmi_struct_get_phy_status(ImHdmiStruct *self, UhdmiPhyStat0 *status);

/**
 * @brief	HDMI Interrupt Handler.
 * @retval	void.
 * @remarks	This API uses DDIM_User_Set_Flg().
 */
extern	void im_hdmi_struct_int_handler(ImHdmiStruct *self);


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_HDMI_STRUCT_H__ */
