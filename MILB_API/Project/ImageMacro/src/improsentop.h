/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __IMPRO_SENTOP_H__
#define __IMPRO_SENTOP_H__


#include <klib.h>
#include "jdspro.h"
#include "improcommon.h"
#include "dd_top.h"


#define IMPRO_TYPE_SENTOP        (impro_sentop_get_type())
#define IMPRO_SENTOP(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSentop))
#define IMPRO_IS_SENTOP(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENTOP))


/*宏定义区域*/
/**< Number of PWSW			*/
#define	ImproSentop_D_IM_PRO_SENTOP_PWSW_NUM		(4)
/**< Number of BS			*/
#define	ImproSentop_D_IM_PRO_SEN_BS_NUM				(4)
	/**< Number of ComboPHY		*/
#define	ImproSentop_D_IM_PRO_SENTOP_CPHY_NUM		(4)
	/**< Number of SG			*/
#define	ImproSentop_D_IM_PRO_SEN_SG_NUM				(4)


/*其他结构体或类型定义区域*/
/** LDIV maximum horizontal size of RAM
*/
typedef enum {
	/**< LDIV0:2960  LDIV1:2960        LDIV2:2960        LDIV3:2960	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_0 = 0,
	/**< LDIV0:5920  LDIV1:5920        LDIV2:Unavailable LDIV3:1024	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_1,
	/**< LDIV0:11840 LDIV1:Unavailable LDIV2:Unavailable LDIV3:1024	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_2,
	/**< Setting prohibited(Reserved)	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_3,
} EimproSentopLdivMaxHsizeCtrl;

/** Sensor connect type
*/
typedef enum {
	/**< Connect to LVDS	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS = 0,
	/**< Connect to SLVS-EC	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_SLVS,
	/**< Connect to MIPI D-PHY	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_DMIPI,
	/**< Connect to MIPI C-PHY	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_CMIPI,
	/**< Connect to other SENCORE's SLVS-EC for Multi stream	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_SLVS,
	/**< Connect to other SENCORE's MIPI D-PHY for Virtual channel	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_DMIPI_VC,
	/**< Connect to other SENCORE's MIPI C-PHY for Virtual channel	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_CMIPI_VC,
	/**< Connect to other SENCORE's LVDS	*/
	ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_EXT_LVDS,
} EimproSentopConnTypeSel;

/** Macro block selection of input to BLOB.
*/
typedef enum {
	/**< LDIV0 of output0 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0 = 0,
	/**< LDIV0 of output1 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_1,
	/**< LDIV0 of output2 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_2,
	/**< LDIV0 of output3 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_3,
	/**< LDIV1 of output0 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV1_0,
	/**< LDIV1 of output1 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV1_1,
	/**< LDIV2 of output0 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV2_0,
	/**< LDIV3 of output0 connect to BLOB	*/
	ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV3_0,
} EimproSentopInputToBlob;

/** Output type for P2M macro.
*/
typedef enum {
	/**< LDIV0 of output0 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_PRE_BLOB = 0,
	/**< LDIV0 of output0 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_POST_BLOB,
	/**< LDIV0 of output1 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_1_PRE_BLOB,
	/**< LDIV0 of output1 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_1_POST_BLOB,
	/**< LDIV0 of output2 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_2_PRE_BLOB,
	/**< LDIV0 of output2 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_2_POST_BLOB,
	/**< LDIV0 of output3 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_3_PRE_BLOB,
	/**< LDIV0 of output3 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_3_POST_BLOB,
	/**< LDIV1 of output0 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV1_0_PRE_BLOB,
	/**< LDIV1 of output0 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV1_0_POST_BLOB,
	/**< LDIV1 of output1 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV1_1_PRE_BLOB,
	/**< LDIV1 of output1 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV1_1_POST_BLOB,
	/**< LDIV2 of output0 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV2_0_PRE_BLOB,
	/**< LDIV2 of output0 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV2_0_POST_BLOB,
	/**< LDIV3 of output0 (pre-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_PRE_BLOB,
	/**< LDIV3 of output0 (post-BLOB)	*/
	ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV3_0_POST_BLOB,
} EimproSentopSdramOutputType;

/** Output selection to SRO2 I/F
*/
typedef enum {
	/**< Output from LDIV0	*/
	ImproSentop_E_IM_PRO_SENTOP_OUT_SEL_LDIV0 = 0,
	/**< Output from LDIV1	*/
	ImproSentop_E_IM_PRO_SENTOP_OUT_SEL_LDIV1,
} EimproSentopOutSel;

/** LDIV multi channel input control
*/
typedef enum {
	/**< Separated operation	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_DISABLE = 0,
	/**< 2ch multi connect operation	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_2CH,
	/**< 4ch multi connect operation	*/
	ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_4CH,
} EimproSentopLdivMultiInputCtrl;

/** SENTOP Clock Type
*/
typedef enum {
	/**< SENSORCLK		*/
	ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK = 0,
	/**< APCLK_0(SG0)	*/
	ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0,
	/**< APCLK_1(SG1)	*/
	ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK1,
	/**< APCLK_2(SG2)	*/
	ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2,
	/**< APCLK_3(SG3)	*/
	ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK3,
} EimproSentopClkType;

/** BitShift macro shift value
*/
typedef enum {
	/**< 0bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT	= 0,
	/**< 1bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_1BIT,
	/**< 2bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_2BIT,
	/**< 3bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_3BIT,
	/**< 4bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_4BIT,
	/**< 5bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_5BIT,
	/**< 6bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_6BIT,
} EimproSentopBsShift;

/** Saturation compensation when bit shift
*/
typedef enum {
	/**< saturation no compensation	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP	= 0,
	/**< saturation compensation	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP
} EimproSentopBsSat;

/** Bit shift direction
*/
typedef enum {
	/**< Left bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L	= 0,
	/**< Right bit shift	*/
	ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_R
} EimproSentopBsBitShiftDir;

/** OBT communication parttern
*/
typedef enum {
	/**< Communication between any 2sets	*/
	ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_ANY_2SETS = 0,
	/**< Communication between any 3sets	*/
	ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_ANY_3SETS,
	/**< Communication between 4sets	*/
	ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_4SETS,
	/**< Communication between BLOB0 and BLOB1, and BLOB2 and BLOB3	*/
	ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_BLOB0_1_BLOB2_3,
} EimproSentopObtCommParttern;

/** SLVS Link connect control
*/
typedef enum {
	/**< Connect PHY0's 20 divided clock to LINK.	*/
	ImproSentop_E_IM_PRO_SENTOP_SLVS_LINK_CONN_PHY0 = 0,
	/**< Connect PHY1's 20 divided clock to LINK.	*/
	ImproSentop_E_IM_PRO_SENTOP_SLVS_LINK_CONN_PHY1,
} EimproSentopSlvsLinkConn;

/** SG I/F output select contrpl
*/
typedef enum {
	/**< SG macro output 0 connected	*/
	ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG0 = 0,
	/**< SG macro output 1 connected	*/
	ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG1,
	/**< SG macro output 2 connected	*/
	ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG2,
	/**< SG macro output 3 connected	*/
	ImproSentop_E_IM_PRO_SENTOP_SG_IF_OUTPUT_SEL_SG3,
} EimproSentopSgIfOutputSel;

typedef enum {
	/**< SENCORE0:2960  SENCORE1:2960        SENCORE2:2960        SENCORE3:2960	*/
	ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_0 = 0,
	/**< SENCORE0:5920  SENCORE1:5920        SENCORE2:Unavailable SENCORE3:1024	*/
	ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_1,
	/**< SENCORE0:11840 SENCORE1:Unavailable SENCORE2:Unavailable SENCORE3:1024	*/
	ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_2,
	/**< Setting prohibited(Reserved)	*/
	ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_3,
} EimproSentopSencoreMaxHsizeCtrl;


/** SENTOP Macro Control Information
*/
typedef struct {
	/**< Select an input sensor type of each SENCORE. SENTOPCTL1@@SENIN0-@@SENIN3 */
	EimproSentopConnTypeSel				senConnectTypeSel[ImproBase_D_IM_PRO_SEN_SENCORE_NUM];
	/**< Select an input block type of each BLOB. SENTOPCTL1@@BLOBSET0-@@BLOBSET3 */
	EimproSentopInputToBlob				blobInputSel[ImproBase_D_IM_PRO_SENTOP_BLOB_NUM];
	/**< Select a type of output to SDRAM from LDIV. SENTOPCTL1@@PWSW0-@@PWSW3 */
	EimproSentopSdramOutputType		sdramOutputType[ImproSentop_D_IM_PRO_SENTOP_PWSW_NUM];
	/**< Select an output block to SRO2 I/F. SENTOPCTL1@@PIPE2S */
	EimproSentopOutSel							outputSelSro2;
	/**< Select a SENCORE horizontal maxumum size control. SENTOPCTL1@@SENRAMSW */
	EimproSentopSencoreMaxHsizeCtrl	sencoreHmaxSizeCtrl;
	/**< Select a LDIV horizontal maxumum size control. SENTOPCTL1@@LDIVRAMSW */
	EimproSentopLdivMaxHsizeCtrl		ldivHmaxSizeCtrl;
	/**< Select a LDIV multi channel input control. SENTOPCTL1@@LDIVMCH */
	EimproSentopLdivMultiInputCtrl		ldivMultiChInputCtrl;
	/**< Select a Bayer first pixel for each PAT block input SENTOPCTL2@@ORG00-@@ORG31 */
	EimproOrg									firstPixel[ImproBase_D_IM_PRO_SENTOP_BLOB_NUM][2];
} TimproSentopCtrl;

/** ComboPHY Common Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_BITWIDTHSEL" pin control. @@PHYx_BITWIDTHSEL. */
	UCHAR								bitwidthsel;
	/**< ComboPHY "I_RXMODE" pin control.      @@PHYx_RXMODE. */
	UCHAR								rxmode;
	/**< ComboPHY "I_D0SETSEL" pin control.    @@PHYx_D0SETSEL. */
	UCHAR								d0setsel;
	/**< ComboPHY "I_D1SETSEL" pin control.    @@PHYx_D1SETSEL. */
	UCHAR								d1setsel;
	/**< ComboPHY "I_D2SETSEL" pin control.    @@PHYx_D2SETSEL. */
	UCHAR								d2setsel;
	/**< ComboPHY "I_D3SETSEL" pin control.    @@PHYx_D3SETSEL. */
	UCHAR								d3setsel;
} TimproSentopCphyCommonModeCtrl;

/** SENTOP BitShift Macro Control Information
*/
typedef struct {
	/**< Bit shift value for BS0 ~ BS3 macro. target registor	:BSAMNTx@@BSCTL	*/
	EimproSentopBsShift					shiftValue[ImproSentop_D_IM_PRO_SEN_BS_NUM];
	/**< Saturation compensation for BS0 ~ BS3 macro. [0:Disable 1:Enable] target registor	:BSLMDx@@BSCTL	*/
	EimproSentopBsSat					satCompensation[ImproSentop_D_IM_PRO_SEN_BS_NUM];
	/**< Bit shift direction value for BS0 ~ BS3 macro. target registor	:BSLRx@@BSCTL	*/
	EimproSentopBsBitShiftDir		shiftDir[ImproSentop_D_IM_PRO_SEN_BS_NUM];
} TimproSentopBsCtrl;

/** SENTOP OBT Macro Control Information
*/
typedef struct {
	/**< Select an OBT macro communication perttern. OBTCDCCTL1@@OBTCPAT */
	EimproSentopObtCommParttern		obtCommPerttern;
} TimproSentopObtCtrl;

/** OBT communication parttern
*/
typedef struct {
	/**< OBT weight coefficient  target registor	:OBTCDCCTL2@@OBTDWC00 - @@OBTDWC31	*/
	UCHAR									coeff[4][2];
} TimproSentopObtWeightCoeff;

/** SENTOP LVDS Macro Power-Down Control
*/
typedef struct {
	/**< LVDS PHY clock lane control. LVDSCTL@@LVDSCKPD */
	USHORT								clockLanePowerdown;
	/**< LVDS PHY data lane control. LVDSCTL@@LVDSDLPD */
	USHORT								dataLanePowerdown;
} TimproSentopLvdsCtrl;

/** SENTOP SLVS Macro Control
*/
typedef struct {
	/**< Enable Clock control. FALSE: skip the setting the phy0Rxpclk2aen and phy1Rxpclk2aen.
	 *  TRUE:  set the phy0Rxpclk2aen and phy1Rxpclk2aen.  */
	BOOL											clkCtrlEnabled;
	/**< SLVS link connect control. SLVSECCTL@@SLVSECSEL */
	EimproSentopSlvsLinkConn		linkMode;
	/**< ComboPHY0 "I_RXPDCK" pin control. SLVSECCTL@@PHY0_RXPDCK<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy0Rxpdck;
	/**< ComboPHY0 "I_RXPDCK" pin control. SLVSECCTL@@PHY1_RXPDCK<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy1Rxpdck;
	/**< ComboPHY0 "I_RXPDCK" pin control. SLVSECCTL@@PHY2_RXPDCK<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy2Rxpdck;
	/**< ComboPHY0 "I_RXPDCK" pin control. SLVSECCTL@@PHY3_RXPDCK<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy3Rxpdck;
	/**< ComboPHY0 "I_RXPCLK2AEN" pin control. SLVSECCTL@@PHY0_RXPCLK2AEN<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy0Rxpclk2aen;
	/**< ComboPHY1 "I_RXPCLK2AEN" pin control. SLVSECCTL@@PHY1_RXPCLK2AEN<br>
	detail of this setting value, please refer to ComboPHY specifications. */
	UCHAR											phy1Rxpclk2aen;
} TimproSentopSlvsCtrl;

/** SENTOP SGHDEG0 Macro Control
*/
typedef struct {
	/**< Select an SG I/F output control. SGOUTCTL@@SGSEL0 - @@SGSEL3 */
	EimproSentopSgIfOutputSel		sgIfOutputSel[ImproSentop_D_IM_PRO_SEN_SG_NUM];
} TimproSentopSgCtrl;

/** ComboPHY Common I/F Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_PREGCNT" pin control.   @@PHY_PREGCNT. */
	UCHAR								pregcnt;
	/**< ComboPHY "I_FREQCNT" pin control.   @@PHY_FREQCNT. */
	UCHAR								freqcnt;
	/**< ComboPHY "I_PDCNT" pin control.     @@PHY_PDCCNT. */
	UCHAR								pdccnt;
	/**< ComboPHY "I_SETDF" pin control.     @@PHY_SETDF. */
	UCHAR								setdf;
	/**< ComboPHY "I_PICODETST" pin control. @@PHY_PICODETST. */
	UCHAR								picodetst;
	/**< ComboPHY "I_PMONSEL" pin control.   @@PHY_PMONSEL. */
	UCHAR								pmonsel;
	/**< ComboPHY "I_DMONSEL" pin control.   @@PHY_DMONSEL. */
	UCHAR								dmonsel;
	/**< ComboPHY "I_CNTSEL" pin control.    @@PHY_CNTSEL. */
	UCHAR								cntsel;
	/**< ComboPHY "I_MULGAINF" pin control.  @@PHY_MULGAINF. */
	UCHAR								mulgainf;
	/**< ComboPHY "I_MULGAINP" pin control.  @@PHY_MULGAINP. */
	UCHAR								mulgainp;
	/**< ComboPHY "I_CDRFUNC" pin control.   @@PHY_CDRFUNC. */
	UCHAR								cdrfunc;
} TimproSentopCphyCommonIfCtrl;

/** ComboPHY CP Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_ZEROP3UI_CP0" pin control. @@PHYx_ZEROP3UICP0. */
	UCHAR								zerop3uicp0;
	/**< ComboPHY "I_ZEROP4UI_CP0" pin control. @@PHYxZerop4uicp0. */
	UCHAR								zerop4uicp0;
	/**< ComboPHY "I_ZEROP5UI_CP0" pin control. @@PHYxZerop5uicp0. */
	UCHAR								zerop5uicp0;
	/**< ComboPHY "I_ZEROP6UI_CP0" pin control. @@PHYxZerop6uicp0. */
	UCHAR								zerop6uicp0;
	/**< ComboPHY "I_ZEROP3UI_CP1" pin control. @@PHYx_ZEROP3UICP1. */
	UCHAR								zerop3uicp1;
	/**< ComboPHY "I_ZEROP4UI_CP1" pin control. @@PHYxZerop4uicp1. */
	UCHAR								zerop4uicp1;
	/**< ComboPHY "I_ZEROP5UI_CP1" pin control. @@PHYxZerop5uicp1. */
	UCHAR								zerop5uicp1;
	/**< ComboPHY "I_ZEROP6UI_CP1" pin control. @@PHYxZerop6uicp1. */
	UCHAR								zerop6uicp1;
	/**< ComboPHY "I_ZEROP3UI_CP2" pin control. @@PHYx_ZEROP3UICP2. */
	UCHAR								zerop3uicp2;
	/**< ComboPHY "I_ZEROP4UI_CP2" pin control. @@PHYxZerop4uicp2. */
	UCHAR								zerop4uicp2;
	/**< ComboPHY "I_ZEROP5UI_CP2" pin control. @@PHYxZerop5uicp2. */
	UCHAR								zerop5uicp2;
	/**< ComboPHY "I_ZEROP6UI_CP2" pin control. @@PHYxZerop6uicp2. */
	UCHAR								zerop6uicp2;
	/**< ComboPHY "IDetcntCp0" pin control.   @@PHYxDetcntCp0. */
	UCHAR								detcntCp0;
	/**< ComboPHY "IDetcntCp1" pin control.   @@PHYxDetcntCp1. */
	UCHAR								detcntCp1;
	/**< ComboPHY "IDetcntCp2" pin control.   @@PHYxDetcntCp1. */
	UCHAR								detcntCp2;
	/**< ComboPHY "I_EQ_EN_CP0" pin control.    @@PHYx_EQ_EN_CP0. */
	UCHAR								eqEnCp0;
	/**< ComboPHY "I_EQ_EN_CP1" pin control.    @@PHYx_EQ_EN_CP1. */
	UCHAR								eqEnCp1;
	/**< ComboPHY "I_EQ_EN_CP2" pin control.    @@PHYx_EQ_EN_CP2. */
	UCHAR								eqEnCp2;
	/**< ComboPHY "I_EQ_SET_CP0" pin control.   @@PHYx_EQ_SET_CP0. */
	UCHAR								eqSetCp0;
	/**< ComboPHY "I_EQ_SET_CP1" pin control.   @@PHYx_EQ_SET_CP1. */
	UCHAR								eqSetCp1;
	/**< ComboPHY "I_EQ_SET_CP2" pin control.   @@PHYx_EQ_SET_CP2. */
	UCHAR								eqSetCp2;
} TimproSentopCphyCpmodeCtrl;
/** ComboPHY Delay line Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_D0RXSPEED" pin control.  @@PHYx_D0RXSPEED. */
	UCHAR								d0rxspeed;
	/**< ComboPHY "I_D1RXSPEED" pin control.  @@PHYx_D1RXSPEED. */
	UCHAR								d1rxspeed;
	/**< ComboPHY "I_D2RXSPEED" pin control.  @@PHYx_D2RXSPEED. */
	UCHAR								d2rxspeed;
	/**< ComboPHY "I_D3RXSPEED" pin control.  @@PHYx_D3RXSPEED. */
	UCHAR								d3rxspeed;
	/**< ComboPHY "I_SKEWADJSE0" pin control. @@PHYx_SKWSEL_CP0. */
	UCHAR								skwselCp0;
	/**< ComboPHY "I_SKEWADJSE1" pin control. @@PHYx_SKWSEL_CP1. */
	UCHAR								skwselCp1;
	/**< ComboPHY "I_SKEWADJSE2" pin control. @@PHYx_SKWSEL_CP2. */
	UCHAR								skwselCp2;
} TimproSentopCphyDelayCtrl;

/** ComboPHY DeSkew Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_RXSPDEN" pin control.  @@PHYx_RXSPDEN. */
	UCHAR								rxspden;
	/**< ComboPHY "I_DCNTNUM" pin control.  @@PHYx_DCNTNUM. */
	UCHAR								dcntnum;
	/**< ComboPHY "I_GRDWIDTH" pin control.  @@PHYx_GRDWIDTH. */
	UCHAR								grdwidth;
	/**< ComboPHY "I_RDWAIT" pin control.  @@PHYx_RDWAIT. */
	UCHAR								rdwait;
	/**< ComboPHY "I_VLDPRD" pin control.  @@PHY0_VLDPRD. */
	UCHAR								vldprd;
} TimproSentopCphyDesknewCtrl;

/** ComboPHY PLL0 Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_IBCNT" pin control.  @@PLL0_IBCNT. */
	UCHAR								ibcnt;
	/**< ComboPHY "I_ILFSEL" pin control.  @@PLL0_ILFSEL. */
	UCHAR								ilfsel;
	/**< ComboPHY "I_IOCLKEN" pin control.  @@PLL0_IOCLKEN. */
	UCHAR								ioclken;
	/**< ComboPHY "I_ITXPCLK2AEN" pin control.  @@PLL0_ITXPCLK2AEN. */
	UCHAR								itxpclk2aen;
} TimproSentopCphyPll0Ctrl;

/** ComboPHY Control
*/
typedef struct {
	/**< ComboPHY Common I/F Control. */
	TimproSentopCphyCommonIfCtrl		commonIfCtrl;
	/**< ComboPHY CP mode Control. */
	TimproSentopCphyCpmodeCtrl			cpmodeCtrl[ImproSentop_D_IM_PRO_SENTOP_CPHY_NUM];
	/**< ComboPHY Delay line Control. */
	TimproSentopCphyDelayCtrl					delayCtrl[ImproSentop_D_IM_PRO_SENTOP_CPHY_NUM];
	/**< ComboPHY DeSkew I/F Control. */
	TimproSentopCphyDesknewCtrl			desknewCtrl[ImproSentop_D_IM_PRO_SENTOP_CPHY_NUM];
	/**< ComboPHY PLL0 I/F Control. */
	TimproSentopCphyPll0Ctrl					pll0Ctrl;
} TimproSentopCphyCtrl;

/** ComboPHY Clock Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_CLKLANESEL" pin control. @@PHYx_CLKLANESEL. */
	UCHAR								clklanesel;
	/**< ComboPHY "I_CLKMODESEL" pin control. @@PHYx_CLKMODESEL. */
	UCHAR								clkmodesel;
	/**< ComboPHY "I_CLKOUTREN" pin control.  @@PHYx_CLKOUTREN. */
	UCHAR								clkoutren;
	/**< ComboPHY "I_CLKOUTLEN" pin control.  @@PHYx_CLKOUTLEN. */
	UCHAR								clkoutlen;
} TimproSentopCphyClkCtrl;

/** ComboPHY BIAS Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_XBGRPD" pin control.  @@PHY0_XBGRPD. */
	UCHAR								phy0Xbgrpd;
	/**< ComboPHY "I_XBGRPD" pin control.  @@PHY1_XBGRPD. */
	UCHAR								phy1Xbgrpd;
	/**< ComboPHY "I_XBGRPD" pin control.  @@PHY2_XBGRPD. */
	UCHAR								phy2Xbgrpd;
	/**< ComboPHY "I_XBGRPD" pin control.  @@PHY3_XBGRPD. */
	UCHAR								phy3Xbgrpd;
} TimproSentopCphyBiasCtrl;

/** ComboPHY SLVS-EC Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY Common Mode Control. */
	TimproSentopCphyCommonModeCtrl			commonCtrl;
	/**< ComboPHY "I_PIMODE" pin control.      @@PHYx_PIMODE. */
	UCHAR																pimode;
	/**< ComboPHY "I_PICNT" pin control.       @@PHYx_PICNT. */
	UCHAR																picnt;
} TimproSentopCphySlvsModeCtrl;

/** ComboPHY Sub-LVDS Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY Common Mode Control. */
	TimproSentopCphyCommonModeCtrl	commonCtrl;
} TimproSentopCphyLvdsModeCtrl;

/** ComboPHY MIPI D-PHY Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY Common Mode Control. */
	TimproSentopCphyCommonModeCtrl			commonCtrl;
	/**< ComboPHY "I_RXSPDEN" pin control.  @@PHYx_RXSPDEN. */
	UCHAR																rxspden;
	/**< ComboPHY "I_DCNTNUM" pin control.  @@PHYx_DCNTNUM. */
	UCHAR																dcntnum;
	/**< ComboPHY "I_GRDW	IDTH" pin control.  @@PHYx_GRDWIDTH. */
	UCHAR																grdwidth;
	/**< ComboPHY "I_RDWAIT" pin control.  @@PHYx_RDWAIT. */
	UCHAR																rdwait;
	/**< ComboPHY "I_FUNCSELD0" pin control.   @@PHYx_FUNCSELD0. */
	UINT32															funcseld0;
	/**< ComboPHY "I_VLDPRD" pin control.  @@PHY0_VLDPRD. */
	UCHAR																vldprd;
} TimproSentopCphyDmipiModeCtrl;

/** ComboPHY MIPI D-PHY Mode Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY Common Mode Control. */
	TimproSentopCphyCommonModeCtrl		commonCtrl;
	/**< ComboPHY "I_EQ_EN_CP0" pin control.    @@PHYx_EQ_EN_CP0. */
	UCHAR															eqEnCp0;
	/**< ComboPHY "I_EQ_EN_CP1" pin control.    @@PHYx_EQ_EN_CP1. */
	UCHAR															eqEnCp1;
	/**< ComboPHY "I_EQ_EN_CP2" pin control.    @@PHYx_EQ_EN_CP2. */
	UCHAR															eqEnCp2;
	/**< ComboPHY "I_EQ_SET_CP0" pin control.   @@PHYx_EQ_SET_CP0. */
	UCHAR															eqSetCp0;
	/**< ComboPHY "I_EQ_SET_CP1" pin control.   @@PHYx_EQ_SET_CP1. */
	UCHAR															eqSetCp1;
	/**< ComboPHY "I_EQ_SET_CP2" pin control.   @@PHYx_EQ_SET_CP2. */
	UCHAR															eqSetCp2;
	/**< ComboPHY "I_SKEWADJSE0" pin control. @@PHYx_SKWSEL_CP0. */
	UCHAR															skwselCp0;
	/**< ComboPHY "I_SKEWADJSE1" pin control. @@PHYx_SKWSEL_CP1. */
	UCHAR															skwselCp1;
	/**< ComboPHY "I_SKEWADJSE2" pin control. @@PHYx_SKWSEL_CP2. */
	UCHAR															skwselCp2;
	/**< ComboPHY "I_ZEROP3UI_CP0" pin control. @@PHYx_ZEROP3UICP0. */
	UCHAR															zerop3uicp0;
	/**< ComboPHY "I_ZEROP4UI_CP0" pin control. @@PHYxZerop4uicp0. */
	UCHAR															zerop4uicp0;
	/**< ComboPHY "I_ZEROP5UI_CP0" pin control. @@PHYxZerop5uicp0. */
	UCHAR															zerop5uicp0;
	/**< ComboPHY "I_ZEROP6UI_CP0" pin control. @@PHYxZerop6uicp0. */
	UCHAR															zerop6uicp0;
	/**< ComboPHY "I_ZEROP3UI_CP1" pin control. @@PHYx_ZEROP3UICP1. */
	UCHAR															zerop3uicp1;
	/**< ComboPHY "I_ZEROP4UI_CP1" pin control. @@PHYxZerop4uicp1. */
	UCHAR															zerop4uicp1;
	/**< ComboPHY "I_ZEROP5UI_CP1" pin control. @@PHYxZerop5uicp1. */
	UCHAR															zerop5uicp1;
	/**< ComboPHY "I_ZEROP6UI_CP1" pin control. @@PHYxZerop6uicp1. */
	UCHAR															zerop6uicp1;
	/**< ComboPHY "I_ZEROP3UI_CP2" pin control. @@PHYx_ZEROP3UICP2. */
	UCHAR															zerop3uicp2;
	/**< ComboPHY "I_ZEROP4UI_CP2" pin control. @@PHYxZerop4uicp2. */
	UCHAR															zerop4uicp2;
	/**< ComboPHY "I_ZEROP5UI_CP2" pin control. @@PHYxZerop5uicp2. */
	UCHAR															zerop5uicp2;
	/**< ComboPHY "I_ZEROP6UI_CP2" pin control. @@PHYxZerop6uicp2. */
	UCHAR															zerop6uicp2;
	/**< ComboPHY "IDetcntCp0" pin control.   @@PHYxDetcntCp0. */
	UCHAR															detcntCp0;
	/**< ComboPHY "IDetcntCp1" pin control.   @@PHYxDetcntCp1. */
	UCHAR															detcntCp1;
	/**< ComboPHY "IDetcntCp2" pin control.   @@PHYxDetcntCp1. */
	UCHAR															detcntCp2;
} TimproSentopCphyCmipiModeCtrl;

/** ComboPHY IF Extension Signals Control.<br>
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_CLKSETSEL" pin control.   @@PHYx_CLKSETSEL. */
	UCHAR								clksetsel;
	/**< ComboPHY "I_CPHYSET_CP0" pin control. @@PHYx_CPHYSET_CP0. */
	UCHAR								cphysetCp0;
	/**< ComboPHY "I_CPHYSET_CP1" pin control. @@PHYx_CPHYSET_CP1. */
	UCHAR								cphysetCp1;
	/**< ComboPHY "I_CPHYSET_CP2" pin control. @@PHYx_CPHYSET_CP2. */
	UCHAR								cphysetCp2;
	/**< ComboPHY "I_FUNCSELCK" pin control.   @@PHYx_FUNCSELCK. */
	USHORT								funcselck;
	/**< ComboPHY "I_FUNCSELD0" pin control.   @@PHYx_FUNCSELD0. */
	UINT32								funcseld0;
	/**< ComboPHY "I_FUNCSELD1" pin control.   @@PHYx_FUNCSELD1. */
	UINT32								funcseld1;
	/**< ComboPHY "I_FUNCSELD2" pin control.   @@PHYx_FUNCSELD2. */
	UINT32								funcseld2;
	/**< ComboPHY "I_FUNCSELD3" pin control.   @@PHYx_FUNCSELD3. */
	UINT32								funcseld3;
} TimproSentopCphyIfExtSignalCtrl;

/** ComboPHY MIPI D-PHY DesKnew Monitor pin status.
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "I_VLDWINDOW2" pin control.  @@PHYx_VLDWINDOW2.	*/
	UCHAR								vldwindow2	:7;
	/**< Not used													*/
	USHORT							dummy01		:1;
	/**< ComboPHY "I_VLDWINDOW3" pin control.  @@PHYx_VLDWINDOW3.	*/
	UCHAR								vldwindow3	:7;
	/**< Not used													*/
	ULONG							dummy02		:17;
	/**< ComboPHY "I_DTYPEMON0" pin control.  @@PHYx_DTYPEMON0.		*/
	UCHAR								dtypemon0	:2;
	/**< Not used													*/
	USHORT							dummy03		:2;
	/**< ComboPHY "I_DTYPEMON1" pin control.  @@PHYx_DTYPEMON1.		*/
	UCHAR								dtypemon1	:2;
	/**< Not used													*/
	USHORT							dummy04		:2;
	/**< ComboPHY "I_DTYPEMON2" pin control.  @@PHYx_DTYPEMON2.		*/
	UCHAR								dtypemon2	:2;
	/**< Not used													*/
	USHORT							dummy05		:2;
	/**< ComboPHY "I_DTYPEMON3" pin control.  @@PHYx_DTYPEMON3. 	*/
	UCHAR								dtypemon3	:2;
	/**< Not used													*/
	USHORT							dummy06		:2;
	/**< ComboPHY "I_VLDWINDOW0" pin control.  @@PHYx_VLDWINDOW0.	*/
	UCHAR								vldwindow0	:7;
	/**< Not used													*/
	USHORT							dummy07		:1;
	/**< ComboPHY "I_VLDWINDOW1" pin control.  @@PHYx_VLDWINDOW1.	*/
	UCHAR								vldwindow1	:7;
	/**< Not used													*/
	USHORT							dummy08		:1;
} TimproSentopCphyDesknewMoniStatus;


/** ComboPHY DesKnew Monitor information.
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY0~3 DesKnew Monitor information. */
	TimproSentopCphyDesknewMoniStatus	desknew_moni[4];
} TimproSentopCphyDesknewMonitor;

/** ComboPHY Delayline Monitor pin status.
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "O_CODE_CP2" pin control.  @@PHYx_CODE_CP2.		*/
	ULONG								phy_code_cp2	:18;
	/**< Not used													*/
	USHORT								dummy02			:14;
	/**< ComboPHY "O_CODE_CP1" pin control.  @@PHYx_CODE_CP1.		*/
	ULONG								phy_code_cp1	:18;
	/**< Not used													*/
	USHORT								dummy01			:14;
	/**< ComboPHY "O_CODE_CP0" pin control.  @@PHYx_CODE_CP0.		*/
	ULONG								phy_code_cp0	:18;
	/**< Not used													*/
	USHORT								dummy00			:14;
} TimproSentopCphyDelaylineMoniStatus;


/** ComboPHY Delayline Monitor information.
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY0~3 Delayline Monitor information. */
	TimproSentopCphyDelaylineMoniStatus	delayline_moni[4];
} TimproSentopCphyDelaylineMonitor;

/** ComboPHY Common I/F Monitor information.
	detail of these setting value, please refer to ComboPHY specifications.
*/
typedef struct {
	/**< ComboPHY "O_CDRMON" pin control.  @@PHY0_CDRMON.		*/
	ULLONG								phy0Cdrmon;

	ULLONG								phy1Cdrmon;											/**< ComboPHY "1_CDRMON" pin control.  @@PHY1_CDRMON.		*/

	ULLONG								phy2Cdrmon;											/**< ComboPHY "2_CDRMON" pin control.  @@PHY2_CDRMON.		*/

	ULLONG								phy3Cdrmon;											/**< ComboPHY "3_CDRMON" pin control.  @@PHY2_CDRMON.		*/
} TimproSentopCphyCommonIfMonitor;



/*类型定义区域*/
typedef struct _ImproSentop					ImproSentop;
typedef struct _ImproSentopPrivate				ImproSentopPrivate;


/*对象结构体区域*/
struct _ImproSentop
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sentop_get_type(void);
ImproSentop*		impro_sentop_new();
VOID						impro_sentop_set_cphy_common_ctrl( UCHAR phyNo, TimproSentopCphyCommonModeCtrl* cphyCommon );
/**
SENTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
extern	VOID			impro_sentop_init( VOID );
/**
SENTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
extern	INT32			impro_sentop_sw_reset( VOID );
/**
SENTOP Macro clock control
@param[in]	clkType	: SENTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sentop_control_clock( EimproSentopClkType clkType, UCHAR onOff, UCHAR waitSkip );
/**
SENTOP macro control data setting
@param[in]	ctrl : SENTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sentop_ctrl( TimproSentopCtrl* ctrl );
/**
SENTOP BitShift macro control data setting
@param[in]	ctrl : SENTOP BitShift macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sentop_bs_ctrl( TimproSentopBsCtrl* ctrl );
/**
SENTOP OBT macro setting
@param[in]	ctrl : SENTOP BitShift macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_obt_ctrl( TimproSentopObtCtrl* ctrl );
/**
SENTOP OBT macro weight coefficient setting
@param[in]	coeff : SENTOP OBT macro weight coefficient information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_obt_set_weight_coeff( TimproSentopObtWeightCoeff* coeff );
/**
SENTOP LVDS macro setting
@param[in]	ctrl : SENTOP LVDS macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_lvds_ctrl( TimproSentopLvdsCtrl* ctrl );
/**
SENTOP SLVS macro setting
@param[in]	ctrl : SENTOP SLVS macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_slvs_ctrl( TimproSentopSlvsCtrl* ctrl );
/**
SENTOP SG macro setting
@param[in]	ctrl : SG macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_sgCtrl( TimproSentopSgCtrl* ctrl );
/**
SENTOP ComboPHY macro setting
@param[in]	cphyCtrl : ComboPHY control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_ctrl( TimproSentopCphyCtrl* cphyCtrl );
/**
SENTOP ComboPHY macro Clock setting
@param[in]	clkCtrl : ComboPHY clock control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_clk_ctrl( TimproSentopCphyClkCtrl* clkCtrl );
/**
SENTOP ComboPHY macro Bias setting
@param[in]	biasCtrl : ComboPHY Bias control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_bias_ctrl( TimproSentopCphyBiasCtrl* biasCtrl );
/**
SENTOP ComboPHY SLVS-EC mode setting
@param[in]	modeCtrl : ComboPHY mode control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_slvs_mode_ctrl( TimproSentopCphySlvsModeCtrl* modeCtrl );
/**
SENTOP ComboPHY Sub-LVDS mode setting
@param[in]	modeCtrl : ComboPHY mode control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_lvds_mode_ctrl( TimproSentopCphyLvdsModeCtrl* modeCtrl );
/**
SENTOP ComboPHY MIPI D-PHY mode setting
@param[in]	modeCtrl : ComboPHY mode control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_dmipi_mode_ctrl( TimproSentopCphyDmipiModeCtrl* modeCtrl );
/**
SENTOP ComboPHY MIPI C-PHY mode setting
@param[in]	modeCtrl : ComboPHY mode control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_cmipi_mode_ctrl( TimproSentopCphyCmipiModeCtrl* modeCtrl );
/**
SENTOP ComboPHY Extension Signals setting
@param[in]	extSignal : ComboPHY extension signals control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_ext_signal_ctrl( TimproSentopCphyIfExtSignalCtrl* extSignal );
/**
Get CPHY DesKnew Monitor pin status.
@param[out]	cphyMoni : CPHY DesKnew Monitor pin status information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_get_des_knew_ctrl( TimproSentopCphyDesknewMonitor* cphyMoni );
/**
Get CPHY DelayLine Monitor pin status.
@param[out]	cphyMoni : CPHY DelayLine Monitor pin status information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_get_delay_line_monitor( TimproSentopCphyDelaylineMonitor* cphyMoni );
/**
Get CPHY Common I/F Monitor pin status.
@param[out]	cphyMoni : CPHY Common I/F Monitor pin status information.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern INT32			impro_sentop_cphy_get_common_if_monitor( TimproSentopCphyCommonIfMonitor* cphyMoni );
/**
SENTOP Pseudo VD Issue setting
@retval		D_DDIM_OK					: Setting OK
*/
extern INT32			impro_sentop_pseudo_vd_issue( VOID );






#endif /* __IMPRO_SENTOP_H__ */

