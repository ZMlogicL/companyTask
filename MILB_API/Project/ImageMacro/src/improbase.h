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


#ifndef __IMPRO_BASE_H__
#define __IMPRO_BASE_H__


#include <klib.h>
#include "driver_common.h"
#include "ddim_user_custom.h"

#define IMPRO_TYPE_BASE				(impro_base_get_type())
#define IMPRO_BASE(obj)				(K_TYPE_CHECK_INSTANCE_CAST (obj, ImproBase))
#define IMPRO_IS_BASE(obj)			(K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_BASE))



/*宏定义区域*/
//涉及其他人调用(im_pro_interrupt.c){
/**< Input Parameter Error	*/
#define ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	(D_IM_PRO | D_DDIM_INPUT_PARAM_ERROR)
/**< Clock is enable */
#define ImproBase_D_IM_PRO_MACRO_BUSY_NG		(D_IM_PRO | D_DDIM_MACRO_BUSY_NG)
//	/**< Number of VD/HD ch	*/
//#define	D_IM_PRO_STAT_AF_CH_NUM		(2)
///**< Number of VD/HD ch	*/
//#define	D_IM_PRO_STAT_FLCK_CH_NUM	(2)
/**< Number of VD/HD ch	*/
//#define	D_IM_PRO_STAT_AEAWB_CH_NUM	(4)
/**< Number of VD/HD ch	*/
//#define	D_IM_PRO_STAT_HIST_CH_NUM	(4)
/**< Stream A FrameStart is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG	(1<< 5)
/**< Stream A FrameStart is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG	(1<< 4)
/**< Stream A FrameEnd is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG	(1<< 3)
/**< Stream A FrameEnd is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG	(1<< 2)
/**< Stream A Training Sequence is ended interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG	(1<< 1)
	/**< Stream A Standby Sequence is detected interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG	(1<< 0)
/**< Stream bb FrameStart is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG	(1<<13)
/**< Stream bb FrameStart is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG	(1<<12)
/**< Stream bb FrameEnd is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG	(1<<11)
/**< Stream bb FrameEnd is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG	(1<<10)
/**< Stream bb Training Sequence is ended interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG	(1<< 9)
/**< Stream bb Standby Sequence is detected interrupt wait flag	*/
#define	ImproBase_D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG	(1<< 8)

	/**< Number of SENCORE		*/
#define	ImproBase_D_IM_PRO_SEN_SENCORE_NUM		(4)
	/**< Number of BLOB			*/
#define	ImproBase_D_IM_PRO_SENTOP_BLOB_NUM		(4)

	/**< Total Number of OBD	*/
#define ImproBase_D_IM_PRO_SEN_OBT_CNT			(ImproBase_E_IM_PRO_OBT_CH_3_1 + 1)


/*其他结构体或类型定义区域*/
//涉及其他人修改调用(im_pro_common.c){
typedef enum {
	/**< ch0	*/
	ImproBase_E_IM_PRO_LDIV_CH_0 = 0,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LDIV_CH_1,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LDIV_CH_2,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LDIV_CH_3,
} EimproLdivCh;

/** OBD channel number
*/
typedef enum {
	/**< BLOB0 OBD ch0	*/
	ImproBase_E_IM_PRO_OBD_CH_0_0 = 0,
	/**< BLOB0 OBD ch1	*/
	ImproBase_E_IM_PRO_OBD_CH_0_1,
	/**< BLOB1 OBD ch0	*/
	ImproBase_E_IM_PRO_OBD_CH_1_0,
	/**< BLOB1 OBD ch1	*/
	ImproBase_E_IM_PRO_OBD_CH_1_1,
	/**< BLOB2 OBD ch0	*/
	ImproBase_E_IM_PRO_OBD_CH_2_0,
	/**< BLOB2 OBD ch1	*/
	E_IM_PRO_OBD_CH_2_1,
	/**< BLOB3 OBD ch0	*/
	E_IM_PRO_OBD_CH_3_0,
	/**< BLOB3 OBD ch1	*/
	E_IM_PRO_OBD_CH_3_1,
} EimproObdCh;

/** SDC channel number.
*/
typedef enum {
	/**< SDC0 */
	ImproBase_E_IM_PRO_SDC_CH0 = 0,
	/**< SDC1 */
	ImproBase_E_IM_PRO_SDC_CH1
} EimproSdcCh;

/** PRO Bayer first pixel
*/
typedef enum {
	/**< rr pixel standard	*/
	ImproBase_E_IM_PRO_ORG_R = 0,
	/**< bb pixel standard	*/
	ImproBase_E_IM_PRO_ORG_B,
	/**< gr pixel standard	*/
	ImproBase_E_IM_PRO_ORG_GR,
	/**< gb pixel standard	*/
	ImproBase_E_IM_PRO_ORG_GB
} EimproOrg;



/** LVDS channel number.
*/
typedef enum {
	/**< ch0	*/
	ImproBase_E_IM_PRO_LVDS_CH_0 = 0,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LVDS_CH_1,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LVDS_CH_2,
	/**< ch1	*/
	ImproBase_E_IM_PRO_LVDS_CH_3,
} EimproLvdsCh;


/** MIPI-CPHY channel number.
*/
typedef enum {
	/**< MIPI-DPHY0 */
	ImproBase_E_IM_PRO_CMIPI_CH0 = 0,
	/**< MIPI-DPHY1 */
	ImproBase_E_IM_PRO_CMIPI_CH1,
	/**< MIPI-DPHY2 */
	ImproBase_E_IM_PRO_CMIPI_CH2,
	/**< MIPI-DPHY3 */
	ImproBase_E_IM_PRO_CMIPI_CH3,
} EimproCmipiCh;

/** MIPI-DPHY channel number.
*/
typedef enum {
	/**< MIPI-DPHY0 */
	ImproBase_E_IM_PRO_DMIPI_CH0 = 0,
	/**< MIPI-DPHY1 */
	ImproBase_E_IM_PRO_DMIPI_CH1,
	/**< MIPI-DPHY2 */
	ImproBase_E_IM_PRO_DMIPI_CH2,
	/**< MIPI-DPHY3 */
	ImproBase_E_IM_PRO_DMIPI_CH3,
} EimproDmipiCh;

//}涉及其他人部分




//涉及其他人修改调用(im_pro_common.c等){
typedef enum {
	/**< UNIT number 1 block	*/
	ImproBase_E_IM_PRO_UNIT_NUM_1 = 0,
	/**< UNIT number 2 block	*/
	ImproBase_E_IM_PRO_UNIT_NUM_2,
	/**< UNIT 1 & 2 block	*/
	ImproBase_E_IM_PRO_BOTH_UNIT,
	/**< MAX value	*/
	ImproBase_E_IM_PRO_UNIT_NUM_MAX,
}EimproUnitNum;

typedef enum {
	/**< RAM0(SPTTBL0)	*/
	ImproBase_E_IM_PRO_SPT_TBL_SEL_SPTTBL0 = 0,
	/**< RAM1(SPTTBL1)	*/
	ImproBase_E_IM_PRO_SPT_TBL_SEL_SPTTBL1,
} EimproSptTblSel;
//}涉及其他人部分


//涉及其他人修改调用(im_pro_common.c等){
/** PRO Clock block type
*/
typedef enum {
	/**< SEN block	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN = 0,
	/**< SRO block	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO,
	/**< SRO2 block(behind HRB)	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO2,
	/**< B2B block	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_B2B,
	/**< STAT block	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_STAT,
	/**< PAS block	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_PAS,
	/**< MAX value	*/
	ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_MAX,
} EimproClkBlockType;
//}涉及其他人部分

//涉及其他人修改调用(im_pro_common.c等){
/** AF channel number.
*/
typedef enum {
	/**< AF ch0 */
	ImproBase_E_IM_PRO_AF_CH0 = 0,
	/**< AF ch1 */
	ImproBase_E_IM_PRO_AF_CH1,
} EimproAfCh;

/** AF Window Number
*/
typedef enum {
	/**< AF Window 0			*/
	ImproBase_E_IM_PRO_AF_WINDOW_0 = 0,
	/**< AF Window 1			*/
	ImproBase_E_IM_PRO_AF_WINDOW_1,
	/**< AF Window 2			*/
	ImproBase_E_IM_PRO_AF_WINDOW_2,
	/**< AF Window 3			*/
	ImproBase_E_IM_PRO_AF_WINDOW_3,
	/**< AF Window 4			*/
	ImproBase_E_IM_PRO_AF_WINDOW_4,
	/**< AF Window 5			*/
	ImproBase_E_IM_PRO_AF_WINDOW_5,
	/**< AF Window 6			*/
	ImproBase_E_IM_PRO_AF_WINDOW_6,
	/**< AF Window 7			*/
	ImproBase_E_IM_PRO_AF_WINDOW_7,
	/**< AF Window 8			*/
	ImproBase_E_IM_PRO_AF_WINDOW_8,
	/**< AF Window 9			*/
	ImproBase_E_IM_PRO_AF_WINDOW_9,
	/**< AF Window 10			*/
	ImproBase_E_IM_PRO_AF_WINDOW_10,
	/**< AF Window 11			*/
	ImproBase_E_IM_PRO_AF_WINDOW_11,
	/**< AF Window 12			*/
	ImproBase_E_IM_PRO_AF_WINDOW_12,
	/**< AF Window 13			*/
	ImproBase_E_IM_PRO_AF_WINDOW_13,
	/**< AF Window 14			*/
	ImproBase_E_IM_PRO_AF_WINDOW_14,
	/**< AF Window Max			*/
	ImproBase_E_IM_PRO_AF_WINDOW_MAX
} EimproAfWindow;

/** LVDS output mode.
*/
typedef enum {
	/*< Normal output mode.<br>
	synchronous code detection is performed using only synchronous code0 (SAV[0]/EAV[0]/SAB[0]/EAB[0]),<br>
	the detected data is output from LVDS output0.	*/
	ImproBase_E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL = 0,
	/**< DOL output mode 1.<br>
	synchronous code detection is performed using synchronous code0(SAV[0]/EAV[0]/SAB[0]/EAB[0]) and
	code1(SAV[1]/EAV[1]/SAB[1]/EAB[1]),<br>
	the data of the line detected by synchronous code0 is output from LVDS output0,<br>
	and the data of the line detected by synchronous code1 is output from LVDS output1.	*/
	ImproBase_E_IM_PRO_LVDS_OUTPUT_MODE_DOL1,
	/**< DOL output mode 2. synchronous code detection is performed using 3 groups of synchronous code:<br>
	code0(SAV[0]/EAV[0]/SAB[0]/EAB[0]), code1(SAV[1]/EAV[1]/SAB[1]/EAB[1]) and code2(SAV[2]/EAV[2]/SAB[2]/EAB[2]),<br>
	the data of the line detected by synchronous code0 is output from LVDS output0,<br>
	the data of the line detected by synchronous code1 is output from LVDS output1,<br>
	and the data of the line detected by synchronous code2 is output from LVDS output2.	*/
	ImproBase_E_IM_PRO_LVDS_OUTPUT_MODE_DOL2,
	/**< MAX value	*/
	ImproBase_E_IM_PRO_LVDS_OUTPUT_MODE_MAX,
} EimproLvdsOutputMode;

/** OBT channel number
*/
typedef enum {
	/**< BLOB0 OBT ch0	*/
	ImproBase_E_IM_PRO_OBT_CH_0_0 = 0,
	/**< BLOB0 OBT ch1	*/
	ImproBase_E_IM_PRO_OBT_CH_0_1,
	/**< BLOB1 OBT ch0	*/
	ImproBase_E_IM_PRO_OBT_CH_1_0,
	/**< BLOB1 OBT ch1	*/
	ImproBase_E_IM_PRO_OBT_CH_1_1,
	/**< BLOB2 OBT ch0	*/
	ImproBase_E_IM_PRO_OBT_CH_2_0,
	/**< BLOB2 OBT ch1	*/
	ImproBase_E_IM_PRO_OBT_CH_2_1,
	/**< BLOB3 OBT ch0	*/
	ImproBase_E_IM_PRO_OBT_CH_3_0,
	/**< BLOB3 OBT ch1	*/
	ImproBase_E_IM_PRO_OBT_CH_3_1,
} EimproObtCh;

/** SLVS stream type.
*/
typedef enum {
	/**< Stream A		*/
	ImproBase_E_IM_PRO_SLVS_STREAM_TYPE_A = 0,
	/**< Stream bb		*/
	ImproBase_E_IM_PRO_SLVS_STREAM_TYPE_B,
	/**< Stream A & bb	*/
	ImproBase_E_IM_PRO_SLVS_STREAM_TYPE_BOTH,
} EimproSlvsStreamType;




/** Area information for macro processing
*/
typedef struct {
	/**< Start position x */
	USHORT		posX;
	/**< Start position y */
	USHORT		posY;
	/**< Width of macro processing area */
	USHORT		width;
	/**< Line of macro processing area */
	USHORT		lines;
} TimproAreaInfo;

/** PRO Get RGB SHORT data
*/
typedef struct {
	/**< rr		*/
	SHORT		rr;
	/**< gr		*/
	SHORT		gr;
	/**< gb		*/
	SHORT		gb;
	/**< bb		*/
	SHORT		bb;
} TimproARgb2;

/** Histgram result data format.
*/
typedef struct {
	/**< most frequent value inside the HIST window.<br>
	target registor	:[0]@@HISTRMODE [1]@@HISTGMODE [2]@@HISTBMODE [3]@@HISTYMODE */
	ULONG						mostFrequentValue[4];
	/**< accumulation value inside the HIST window.<br>
	target registor	:[0]@@HISTRSUM [1]@@HISTGSUM [2]@@HISTBSUM [3]@@HISTYSUM */
	ULONG						accumulationValue[4];
}TimproHistData;

/** Histgram result RAM data format.
*/
typedef struct {
	/**< frequency of each pixel level of rr. target registor	@@HISTRDATA */
	ULONG						r[256];
	/**< frequency of each pixel level of G. target registor	@@HISTGDATA */
	ULONG						g[256];
	/**< frequency of each pixel level of bb. target registor	@@HISTBDATA */
	ULONG						b[256];
	/**< frequency of each pixel level of Y. target registor	@@HISTYDATA */
	ULONG						y[256];
} TimproHistRamData;

//}涉及其他人部分



/*类型定义区域*/
typedef struct _ImproBase							ImproBase;
typedef struct _ImproBasePrivate				ImproBasePrivate;


/*对象结构体区域*/
struct _ImproBase
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType			impro_base_get_type(void);
ImproBase*		impro_base_new();


#endif /* __IMPRO_BASE_H__ */

