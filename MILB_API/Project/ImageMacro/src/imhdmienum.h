/*
 *
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-07
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_HDMI_ENUM_H__
#define __IM_HDMI_ENUM_H__


#include <stdio.h>
#include <glib-object.h>


G_BEGIN_DECLS


#ifdef __cplusplus
extern "C" {
#endif


#define IM_TYPE_HDMI_ENUM			(im_hdmi_enum_enum_get_type ())
#define IM_HDMI_ENUM(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_HDMI_ENUM, ImHdmiEnum))
#define IM_HDMI_ENUM_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_HDMI_ENUM, ImHdmiEnumClass))
#define IM_IS_HDMI_ENUM(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_HDMI_ENUM))
#define IM_IS_HDMI_ENUM_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_HDMI_ENUM))
#define IM_HDMI_ENUM_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_HDMI_ENUM, ImHdmiEnumClass))


typedef enum _EhdmiVideoMapping			EhdmiVideoMapping;
typedef enum _EhdmiColorDepth				EhdmiColorDepth;
typedef enum _EhdmiIntReg						EhdmiIntReg;
typedef enum _EhdmiIntType						EhdmiIntType;
typedef enum _EhdmiIhFcStat0					EhdmiIhFcStat0;
typedef enum _EhdmiIhFcStat1					EhdmiIhFcStat1;
typedef enum _EhdmiIhFcStat2					EhdmiIhFcStat2;
typedef enum _EhdmiIhAsStat0					EhdmiIhAsStat0;
typedef enum _EhdmiIhPhyStat0				EhdmiIhPhyStat0;
typedef enum _EhdmiIhI2cmStat0				EhdmiIhI2cmStat0;
typedef enum _EhdmiIhCecStat0				EhdmiIhCecStat0;
typedef enum _EhdmiIhVpStat0					EhdmiIhVpStat0;
typedef enum _EhdmiIhI2cmphyStat0		EhdmiIhI2cmphyStat0;
typedef enum _EhdmiVpRemap					EhdmiVpRemap;
typedef enum _EhdmiOutputSelector			EhdmiOutputSelector;
typedef enum _EhdmiBypassSelect			EhdmiBypassSelect;
typedef enum _EhdmiI2sSelect					EhdmiI2sSelect;
typedef enum _EhdmiI2sMode					EhdmiI2sMode;
typedef enum _EhdmiCtsManual				EhdmiCtsManual;
typedef enum _EhdmiAudIfsfactor				EhdmiAudIfsfactor;
typedef enum _EhdmiI2cmOperation		EhdmiI2cmOperation;

typedef struct _ImHdmiEnum						ImHdmiEnum;
typedef struct _ImHdmiEnumClass				ImHdmiEnumClass;
typedef struct _ImHdmiEnumPrivate 		ImHdmiEnumPrivate;


/*----------------------------------------------------------------------	*/
/* Enumeration																*/
/*----------------------------------------------------------------------	*/
/** Video Input mapping (color space/color depth)	*/
enum _EhdmiVideoMapping
{
	/**< RGB 4:4:4 8 bits					*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_8BIT = 0x01,
	/**< RGB 4:4:4/10 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_10BIT = 0x03,
	/**< RGB 4:4:4/12 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_12BIT = 0x05,
	/**< RGB 4:4:4/16 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_RGB444_16BIT = 0x07,
	/**< YCbCr 4:4:4 or 4:2:0/8 bits	*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_8BIT = 0x09,
	/**< YCbCr 4:4:4 or 4:2:0/10 bits	*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_10BIT = 0x0B,
	/**< YCbCr 4:4:4 or 4:2:0/12 bits	*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_12BIT = 0x0D,
	/**< YCbCr 4:4:4 or 4:2:0/16 bits	*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_420_16BIT = 0x0F,
	/**< YCbCr 4:2:2/12 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_12BIT = 0x12,
	/**< YCbCr 4:2:2/10 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_10BIT = 0x14,
	/**< YCbCr 4:2:2/8 bits				*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_8BIT = 0x16,
	/**< YCbCr 4:4:4 (IPI)/8 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_8BIT = 0x17,
	/**< YCbCr 4:4:4 (IPI)/10 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_10BIT = 0x18,
	/**< YCbCr 4:4:4 (IPI)/12 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_12BIT = 0x19,
	/**< YCbCr 4:4:4 (IPI)/16 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC444_IPI_16BIT = 0x1A,
	/**< YCbCr 4:2:2 (IPI)/12 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC422_IPI_12BIT = 0x1B,
	/**< YCbCr 4:2:0 (IPI)/8 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_8BIT = 0x1C,
	/**< YCbCr 4:2:0 (IPI)/10 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_10BIT = 0x1D,
	/**< YCbCr 4:2:0 (IPI)/12 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_12BIT = 0x1E,
	/**< YCbCr 4:2:0 (IPI)/16 bits		*/
	ImHdmiEnum_E_IM_HDMI_VIDEO_MAPPING_YCC420_IPI_16BIT = 0x1F
} ;

/** Color depth */
enum _EhdmiColorDepth
{
	/**< 8-bit packing mode(24 bits per pixel video).	*/
	ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_8BIT = 4,
	/**< 10-bit packing mode(30 bits per pixel video).	*/
	ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_10BIT = 5,
	/**< 12-bit packing mode(36 bits per pixel video).	*/
	ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_12BIT = 6,
	/**< 16-bit packing mode(48 bits per pixel video).	*/
	ImHdmiEnum_E_IM_HDMI_COLOR_DEPTH_16BIT = 7
} ;

/** Interrupt register */
enum _EhdmiIntReg
{
	/**< ih_fc_stat0.				*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT0,
	/**< ih_fc_stat1.				*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT1,
	/**< ih_fc_stat2.				*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_FC_STAT2,
	/**< ih_as_stat0.				*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_AS_STAT0,
	/**< ih_phy_stat0.			*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_PHY_STAT0,
	/**< ih_i2cm_stat0.		*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_I2CM_STAT0,
	/**< ih_cec_stat0.			*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_CEC_STAT0,
	/**< ih_vp_stat0.				*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_VP_STAT0,
	/**< ih_i2cmphy_stat0.	*/
	ImHdmiEnum_E_IM_HDMI_INT_REG_I2CMPHY_STAT0
} ;

/** Interrupt type */
enum _EhdmiIntType
{
	/**< ih_fc_stat0 Register - NULL.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_NULL = 0,
	/**< ih_fc_stat0 Register - ACR.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ACR,
	/**< ih_fc_stat0 Register - AUDS.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AUDS,
	/**< ih_fc_stat0 Register - NVBI.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_NVBI,
	/**< ih_fc_stat0 Register - MAS.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_MAS,
	/**< ih_fc_stat0 Register - hbr.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_HBR,
	/**< ih_fc_stat0 Register - ACP.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ACP,
	/**< ih_fc_stat0 Register - AUDI.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AUDI,
	/**< ih_fc_stat1 Register - GCP.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_GCP,
	/**< ih_fc_stat1 Register - AVI.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AVI,
	/**< ih_fc_stat1 Register - AMP.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_AMP,
	/**< ih_fc_stat1 Register - SPD.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_SPD,
	/**< ih_fc_stat1 Register - VSD.									*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_VSD,
	/**< ih_fc_stat1 Register - ISCR2.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ISCR2,
	/**< ih_fc_stat1 Register - ISCR1.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_ISCR1,
	/**< ih_fc_stat1 Register - GMD.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_GMD,
	/**< ih_fc_stat2 Register - HighPriority_overflow.	*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_HP_OF,
	/**< ih_fc_stat2 Register - LowPriority_overflow.		*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_FC_LP_OF,
	/**< ih_as_stat0 Register - Aud_fifo_overflow.			*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_OF,
	/**< ih_as_stat0 Register - Aud_fifo_underflow.		*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_UF,
	/**< ih_as_stat0 Register - fifo_overrun.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_AS_OR,
	/**< ih_phy_stat0 Register - HDP.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_HDP,
	/**< ih_phy_stat0 Register - txPhyLock.				*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_TX_PHY_LOCK,
	/**< ih_phy_stat0 Register - pxSense0.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_0,
	/**< ih_phy_stat0 Register - rxSense1.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_1,
	/**< ih_phy_stat0 Register - rxSense2.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_2,
	/**< ih_phy_stat0 Register - rxSense3.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_PHY_RX_SENSE_3,
	/**< ih_i2cm_stat0 Register - I2Cmastererror.			*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_M_ERR,
	/**< ih_i2cm_stat0 Register - I2Cmasterdone.			*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_M_DONE,
	/**< ih_i2cm_stat0 Register - scdc_readreq.				*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CM_SDSC,
	/**< ih_cec_stat0 Register - DONE.							*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_DONE,
	/**< ih_cec_stat0 Register - EOM.								*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_EOM,
	/**< ih_cec_stat0 Register - NACK.							*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_NACK,
	/**< ih_cec_stat0 Register - ARB_LOST.						*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ARB_LOST,
	/**< ih_cec_stat0 Register - ERROR_INITIATOR.		*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ERR_INIT,
	/**< ih_cec_stat0 Register - ERROR_FOLLOW.			*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_ERR_FOL,
	/**< ih_cec_stat0 Register - WAKEUP.						*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_CEC_WAKEUP,
	/**< ih_vp_stat0 Register - fifoemptybyp.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_BYP,
	/**< ih_vp_stat0 Register - fifofullbyp.						*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_BYP,
	/**< ih_vp_stat0 Register - fifoemptyremap.			*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_REMAP,
	/**< ih_vp_stat0 Register - fifofullremap.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_REMAP,
	/**< ih_vp_stat0 Register - fifoemptypp.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_PP,
	/**< ih_vp_stat0 Register - fifofullpp.						*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_PP,
	/**< ih_vp_stat0 Register - fifoemptyrepet.				*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_E_REPET,
	/**< ih_vp_stat0 Register - fifofullrepet.					*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_VP_F_REPET,
	/**< ih_i2cmphy_stat0 Register - I2Cmphyerror.		*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CMPHY_ERR,
	/**< ih_i2cmphy_stat0 Register - I2Cmphydone.		*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_I2CMPHY_DONE,
	/**< Interrupt type maximum value.						*/
	ImHdmiEnum_E_IM_HDMI_INT_TYPE_MAX
} ;

/** ih_fc_stat0 Register - Interrupt type. */
enum _EhdmiIhFcStat0
{
	/**< Successful transmission of Null packet.							*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NULL = 0x01,
	/**< Successful transmission of ACR packet.							*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACR = 0x02,
	/**< Successful transmission of Audio Sample packet.			*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDS = 0x04,
	/**< successful transmission of NTSC VBI packet.					*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_NVBI = 0x08,
	/**< successful transmission of MultiStream Audio packet.	*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_MAS = 0x10,
	/**< successful transmission of Audio hbr packet.				*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_HBR = 0x20,
	/**< successful transmission of ACP packet.							*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_ACP = 0x40,
	/**< successful transmission of Audio InfoFrame packet.		*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT0_AUDI = 0x80
} ;

/** ih_fc_stat1 Register - Interrupt type. */
enum _EhdmiIhFcStat1
{
	/**< Successful transmission of General Control Packet.		*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GCP = 0x01,
	/**< Successful transmission of AVI InfoFrame packet.			*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AVI = 0x02,
	/**< Successful transmission of Audio Metadata packet.		*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_AMP = 0x04,
	/**< successful transmission of SPD InfoFrame packet.			*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_SPD = 0x08,
	/**< successful transmission of VSD InfoFrame packet.			*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_VSD = 0x10,
	/**< successful transmission of ISCR2 packet.							*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR2 = 0x20,
	/**< successful transmission of ISCR1 packet.							*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_ISCR1 = 0x40,
	/**< successful transmission of Gamut metadata packet.		*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT1_GMD = 0x80
} ;

/** ih_fc_stat2 Register - Interrupt type. */
enum _EhdmiIhFcStat2
{
	/**< High priority packet queue descriptor overflow indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_HP_OF = 0x01,
	/**< Low priority packet queue descriptor overflow indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_FC_STAT2_LP_OF = 0x02
} ;

/** ih_as_stat0 Register - Interrupt type. */
enum _EhdmiIhAsStat0
{
	/**< Audio Sampler audio FIFO full indication.		*/
	ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OF = 0x01,
	/**< Audio Sampler audio FIFO empty indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_UF = 0x02,
	/**< Indicates an overrun on the audio FIFO.			*/
	ImHdmiEnum_E_IM_HDMI_IH_AS_STAT0_OR = 0x08
} ;
/** ih_phy_stat0 Register - Interrupt type. */
enum _EhdmiIhPhyStat0
{
	/**< HDMI Hot Plug Detect indication.				*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_HDP = 0x01,
	/**< TX PHY PLL lock indication.							*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_TX_PHY_LOCK = 0x02,
	/**< TX PHY RX_SENSE indication for driver 0.	*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_0 = 0x04,
	/**< TX PHY RX_SENSE indication for driver 1.	*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_1 = 0x08,
	/**< TX PHY RX_SENSE indication for driver 2.	*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_2 = 0x10,
	/**< TX PHY RX_SENSE indication for driver 3.	*/
	ImHdmiEnum_E_IM_HDMI_IH_PHY_STAT0_RX_SENSE_3 = 0x20
} ;
/** ih_i2cm_stat0 Register - Interrupt type. */
enum _EhdmiIhI2cmStat0
{
	/**< I2C Master error indication.								*/
	ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_ERR = 0x01,
	/**< I2C Master done indication.								*/
	ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_MASTER_DONE = 0x02,
	/**< I2C Master SCDC read request indication.		*/
	ImHdmiEnum_E_IM_HDMI_IH_I2CM_STAT0_SDSC = 0x04
} ;

/** ih_cec_stat0 Register - Interrupt type. */
enum _EhdmiIhCecStat0
{
	/**< CEC Done Indication.							*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_DONE = 0x01,
	/**< CEC End of Message Indication.		*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_EOM = 0x02,
	/**< CEC Not Acknowledge indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_NACK = 0x04,
	/**< CEC Arbitration Lost indication.		*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ARB_LOST = 0x08,
	/**< CEC Error Initiator indication.			*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_INITIATOR = 0x10,
	/**< CEC Error Follow indication.				*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_ERR_FOLLOW = 0x20,
	/**< CEC Wake-up indication.					*/
	ImHdmiEnum_E_IM_HDMI_IH_CEC_STAT0_WAKEUP = 0x40
} ;

/** ih_vp_stat0 Register - Interrupt type. */
enum _EhdmiIhVpStat0
{
	/**< 8 bit bypass FIFO empty interrupt.						*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_BYP = 0x01,
	/**< 8 bit bypass FIFO full interrupt.							*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_BYP = 0x02,
	/**< Pixel YCC422 re-mapper FIFO empty interrupt.	*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REMAP = 0x04,
	/**< Pixel YCC422 re-mapper FIFO full interrupt.		*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REMAP = 0x08,
	/**< Pixel packing FIFO empty interrupt.						*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_PP = 0x10,
	/**< Pixel packing FIFO full interrupt.							*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_PP = 0x20,
	/**< Pixel repeater FIFO empty interrupt.					*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_EMPTY_REPET = 0x40,
	/**< Pixel repeater FIFO full interrupt.							*/
	ImHdmiEnum_E_IM_HDMI_IH_VP_STAT0_FULL_REPET = 0x80
} ;
/** ih_i2cmphy_stat0 Register - Interrupt type. */
enum _EhdmiIhI2cmphyStat0
{
	/**< I2C Master PHY error indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_ERR = 0x01,
	/**< I2C Master PHY done indication.	*/
	ImHdmiEnum_E_IM_HDMI_IH_I2CMPHY_STAT0_MASTER_DONE = 0x02
};
/** vpRemap Register - ycc422_size (YCC 422 remap input video size) */
enum _EhdmiVpRemap
{
	/**< YCC 422 16-bit input video (8 bits per component).		*/
	ImHdmiEnum_E_IM_HDMI_VP_REMAP_16BIT = 0,
	/**< YCC 422 20-bit input video (10 bits per component).		*/
	ImHdmiEnum_E_IM_HDMI_VP_REMAP_20BIT = 1,
	/**< YCC 422 24-bit input video (12 bits per component).		*/
	ImHdmiEnum_E_IM_HDMI_VP_REMAP_24BIT = 2
};
/** vpConf Register - outputSelector (Video Packetizer output selection) */
enum _EhdmiOutputSelector
{
	/**< Data from pixel packing block.				*/
	ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_PIXEL_PACKING = 0,
	/**< Data from YCC 422 remap block.			*/
	ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_YCC422_REMAP,
	/**< Data from 8-bit bypass block.				*/
	ImHdmiEnum_E_IM_HDMI_OUTPUT_SELECTOR_8BIT_BYPASS
};
/** vpConf Register - bypassSelect (bypass select) */
enum _EhdmiBypassSelect
{
	/**< Data from pixel repeater block.						*/
	ImHdmiEnum_E_IM_HDMI_BYPASS_SELECT_PIXEL_REPEATER = 0,
	/**< Data from input of Video Packetizer block.		*/
	ImHdmiEnum_E_IM_HDMI_BYPASS_SELECT_VIDEO_PACKETIZER
};

/** audConf0 Register - i2sSelect (Select I2S interface) */
enum _EhdmiI2sSelect
{
	/**< Selects SPDIF interface				*/
	ImHdmiEnum_E_IM_HDMI_I2S_SELECT_S_PDIF = 0,
	/**< Selects I2S Audio Interface		*/
	ImHdmiEnum_E_IM_HDMI_I2S_SELECT_I2S
};

/** audConf1 Register - i2sMode (I2S input data mode) */
enum _EhdmiI2sMode
{
	/**< Standard I2S mode			*/
	ImHdmiEnum_E_IM_HDMI_I2S_MODE_STANDARD = 0,
	/**< Right-justified I2S mode	*/
	ImHdmiEnum_E_IM_HDMI_I2S_MODE_RIGHT_JUSTIFIED,
	/**< Left-justified I2S mode		*/
	ImHdmiEnum_E_IM_HDMI_I2S_MODE_LEFT_JUSTIFIED
};

/** aud_cts3 Register - CTS_manual (Select CTS Automatic/Manual) */
enum _EhdmiCtsManual
{
	/**< 00:Divides by 1		*/
	ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_AUTO = 0,
	/**< Manual					*/
	ImHdmiEnum_E_IM_HDMI_CTS_MANUAL_MANUAL
};

/** audInputclkfs Register - ifsfactor (Fs factor configuration) */
enum _EhdmiAudIfsfactor
{
	/**< 128xFs		*/
	ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_128XFS = 0,
	/**< 256xFs		*/
	ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_256XFS = 1,
	/**< 512xFs		*/
	ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_512XFS = 2,
	/**< 64xFs		*/
	ImHdmiEnum_E_IM_HDMI_AUD_IFSFACTOR_64XFS = 4
};

/** i2cmOperation Register */
enum _EhdmiI2cmOperation
{
	/**< Single byte read operation request.									*/
	ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD = 0x01,
	/**< Extended data read operation(E-DDC read operation).*/
	ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD_EXT = 0x02,
	/**< Sequential read operation request.									*/
	ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8 = 0x04,
	/**< Extended sequential read operation request.				*/
	ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_RD8_EXT = 0x08,
	/**< Single byte write operation request.								*/
	ImHdmiEnum_E_IM_HDMI_I2CM_OPERATION_WR = 0x10
};


struct _ImHdmiEnum
{
	GObject parent;
	DdimUserCustomTest *ddimUserCustomTest;
	ImHdmi *imHdmi;
};

struct _ImHdmiEnumClass
{
	GObjectClass parentClass;
};



GType								im_hdmi_enum_enum_get_type(void)	G_GNUC_CONST;
ImHdmiEnum*				im_hdmi_enum_enum_new(void);
EhdmiIntType 				im_hdmi_enum_get_interrupt_type(ImHdmiEnum*self, EhdmiIntReg intReg, guchar regBit);
/**
 * @brief	HDMI PHY Power On/Off.
 * @param[in]	power		Power On/Off.
 * <ul><li>@ref ImHdmi_D_IM_HDMI_ENABLE_OFF
 * <li>@ref ImHdmi_D_IM_HDMI_ENABLE_ON</ul>
 * @retval		D_DDIM_OKSuccess.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input parameter error.
 */
extern	gint32 im_hdmi_enum_power_on(ImHdmiEnum*self, guchar power);

/**
 * @brief	Initialize HDMI Transmitter macro.
 * @retval		D_DDIM_OK						Success.
 * @retval		ImHdmi_D_IM_HDMI_NG					NG.
 */
extern	gint32 im_hdmi_enum_init(ImHdmiEnum*self,);

/**
 * @brief	Configure VGA DVI Video Mode.
 * @param[in]	pllConfig		PLL configure paramter.
 * @retval		D_DDIM_OK	Success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR		Input parameter error.
 * @retval		ImHdmi_D_IM_HDMI_NG	NG.
 * @remarks	This API uses DDIM_User_Clr_Flg().
 * @remarks	This API uses DDIM_User_Twai_Flg().
 */
extern	gint32 im_hdmi_enum_configure_vga_dvi_video_mode(ImHdmiEnum*self, ThdmiPllConfig const *const pllConfig);

/**
 * @brief	Set TMDS Scramble by I2C
 * @retval	D_DDIM_OK	Success.
 * @retval	ImHdmi_D_IM_HDMI_TIMEOUT	timeout.
 * @remarks	This API uses DDIM_User_Clr_Flg().
 * @remarks	This API uses DDIM_User_Twai_Flg().
 */
extern gint32 im_hdmi_enum_set_tmds_scramble(ImHdmiEnum*self, BOOL enable);

/**
 * @brief	Read Sink's E-EDID.
 * @param[in]	i2cmConfig	configure paramter.
 * @param[out]	readData	read data.
 * Value range:0x00~0xFF.
 * @retval		D_DDIM_OK	Success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input parameter error.
 * @retval		ImHdmi_D_IM_HDMI_TIMEOUT 	timeout.
 * @remarks	This API uses DDIM_User_Clr_Flg().
 * @remarks	This API uses DDIM_User_Twai_Flg().
 */
extern	gint32 im_hdmi_enum_read_sinks_e_edid(ImHdmiEnum*self, ThdmiI2cmConfig const *const i2cmConfig, guchar readData[8]);
/**
 * @brief		Set control data of HDMI Transmitter.
 * @param[in]	ctrl	Control data.
 * @retval		D_DDIM_OK	success.
 * @retval		ImHdmi_D_IM_HDMI_INPUT_PARAM_ERROR	Input Parameter Error.
 * @remarks	This API uses DDIM_User_Clr_Flg().
 * @remarks	This API uses DDIM_User_Twai_Flg().
 */
extern	gint32 im_hdmi_enum_ctrl(ImHdmiEnum*self, ImHdmiStruct const *const ctrl );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_HDMI_ENUM_H__ */
