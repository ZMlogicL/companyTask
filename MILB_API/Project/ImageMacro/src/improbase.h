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
#define D_IM_PRO_INPUT_PARAM_ERROR	(D_IM_PRO | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error	*/
#define D_IM_PRO_MACRO_BUSY_NG		(D_IM_PRO | D_DDIM_MACRO_BUSY_NG)		/**< Clock is enable */
#define	D_IM_PRO_STAT_AF_CH_NUM		(2)		/**< Number of VD/HD ch	*/
#define	D_IM_PRO_STAT_FLCK_CH_NUM	(2)		/**< Number of VD/HD ch	*/
#define	D_IM_PRO_STAT_AEAWB_CH_NUM	(4)		/**< Number of VD/HD ch	*/
#define	D_IM_PRO_STAT_HIST_CH_NUM	(4)		/**< Number of VD/HD ch	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG	(1<< 5) 	/**< Stream A FrameStart is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG	(1<< 4)		/**< Stream A FrameStart is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG	(1<< 3)		/**< Stream A FrameEnd is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG	(1<< 2)		/**< Stream A FrameEnd is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG	(1<< 1)		/**< Stream A Training Sequence is ended interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG	(1<< 0)	/**< Stream A Standby Sequence is detected interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG	(1<<13)	/**< Stream bb FrameStart is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG	(1<<12)	/**< Stream bb FrameStart is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG	(1<<11)	/**< Stream bb FrameEnd is detected in the preprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG	(1<<10)	/**< Stream bb FrameEnd is detected in the postprocessing of Line Buffer interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG	(1<< 9)		/**< Stream bb Training Sequence is ended interrupt wait flag	*/
#define	D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG	(1<< 8)	/**< Stream bb Standby Sequence is detected interrupt wait flag	*/

#define	D_IM_PRO_SEN_SENCORE_NUM		(4)									/**< Number of SENCORE		*/
#define	D_IM_PRO_SENTOP_BLOB_NUM		(4)									/**< Number of BLOB			*/
#define	D_IM_PRO_SEN_SG_NUM				(4)									/**< Number of SG			*/
#define D_IM_PRO_SEN_OBT_CNT			(E_IM_PRO_OBT_CH_3_1 + 1)			/**< Total Number of OBD	*/
//}涉及其他人部分



/*其他结构体或类型定义区域*/
//涉及其他人修改调用(im_pro_common.c){
typedef enum {
	E_IM_PRO_LDIV_CH_0 = 0,						/**< ch0	*/
	E_IM_PRO_LDIV_CH_1,							/**< ch1	*/
	E_IM_PRO_LDIV_CH_2,							/**< ch1	*/
	E_IM_PRO_LDIV_CH_3,							/**< ch1	*/
} E_IM_PRO_LDIV_CH;

/** OBD channel number
*/
typedef enum {
	E_IM_PRO_OBD_CH_0_0 = 0,			/**< BLOB0 OBD ch0	*/
	E_IM_PRO_OBD_CH_0_1,				/**< BLOB0 OBD ch1	*/
	E_IM_PRO_OBD_CH_1_0,				/**< BLOB1 OBD ch0	*/
	E_IM_PRO_OBD_CH_1_1,				/**< BLOB1 OBD ch1	*/
	E_IM_PRO_OBD_CH_2_0,				/**< BLOB2 OBD ch0	*/
	E_IM_PRO_OBD_CH_2_1,				/**< BLOB2 OBD ch1	*/
	E_IM_PRO_OBD_CH_3_0,				/**< BLOB3 OBD ch0	*/
	E_IM_PRO_OBD_CH_3_1,				/**< BLOB3 OBD ch1	*/
} E_IM_PRO_OBD_CH;

/** SDC channel number.
*/
typedef enum {
	E_IM_PRO_SDC_CH0 = 0,		/**< SDC0 */
	E_IM_PRO_SDC_CH1			/**< SDC1 */
} E_IM_PRO_SDC_CH;

/** AEAWB channel number.
*/
typedef enum {
	E_IM_PRO_AEAWB_CH0 = 0,		/**< AEAWB ch0 */
	E_IM_PRO_AEAWB_CH1,			/**< AEAWB ch1 */
	E_IM_PRO_AEAWB_CH2,			/**< AEAWB ch2 */
	E_IM_PRO_AEAWB_CH3,			/**< AEAWB ch3 */
} E_IM_PRO_AEAWB_CH;

/** PRO Bayer first pixel
*/
typedef enum {
	E_IM_PRO_ORG_R = 0,				/**< rr pixel standard	*/
	E_IM_PRO_ORG_B,					/**< bb pixel standard	*/
	E_IM_PRO_ORG_GR,				/**< gr pixel standard	*/
	E_IM_PRO_ORG_GB					/**< gb pixel standard	*/
} E_IM_PRO_ORG;



/** LVDS channel number.
*/
typedef enum {
	E_IM_PRO_LVDS_CH_0 = 0,						/**< ch0	*/
	E_IM_PRO_LVDS_CH_1,							/**< ch1	*/
	E_IM_PRO_LVDS_CH_2,							/**< ch1	*/
	E_IM_PRO_LVDS_CH_3,							/**< ch1	*/
} E_IM_PRO_LVDS_CH;

/** HIST channel number.
*/
typedef enum {
	E_IM_PRO_HIST_CH0 = 0,		/**< HIST ch0 */
	E_IM_PRO_HIST_CH1,			/**< HIST ch1 */
	E_IM_PRO_HIST_CH2,			/**< HIST ch2 */
	E_IM_PRO_HIST_CH3,			/**< HIST ch3 */
} E_IM_PRO_HIST_CH;

/** MIPI-CPHY channel number.
*/
typedef enum {
	E_IM_PRO_CMIPI_CH0 = 0,		/**< MIPI-DPHY0 */
	E_IM_PRO_CMIPI_CH1,			/**< MIPI-DPHY1 */
	E_IM_PRO_CMIPI_CH2,			/**< MIPI-DPHY2 */
	E_IM_PRO_CMIPI_CH3,			/**< MIPI-DPHY3 */
} E_IM_PRO_CMIPI_CH;

/** MIPI-DPHY channel number.
*/
typedef enum {
	E_IM_PRO_DMIPI_CH0 = 0,		/**< MIPI-DPHY0 */
	E_IM_PRO_DMIPI_CH1,			/**< MIPI-DPHY1 */
	E_IM_PRO_DMIPI_CH2,			/**< MIPI-DPHY2 */
	E_IM_PRO_DMIPI_CH3,			/**< MIPI-DPHY3 */
} E_IM_PRO_DMIPI_CH;

//}涉及其他人部分




//涉及其他人修改调用(im_pro_common.c等){
typedef enum {
	E_IM_PRO_UNIT_NUM_1 = 0,	/**< UNIT number 1 block	*/
	E_IM_PRO_UNIT_NUM_2,		/**< UNIT number 2 block	*/
	E_IM_PRO_BOTH_UNIT,			/**< UNIT 1 & 2 block	*/
	E_IM_PRO_UNIT_NUM_MAX,		/**< MAX value	*/
} E_IM_PRO_UNIT_NUM;

typedef enum {
													E_IM_PRO_SPT_TBL_SEL_SPTTBL0 = 0,			/**< RAM0(SPTTBL0)	*/
													E_IM_PRO_SPT_TBL_SEL_SPTTBL1,				/**< RAM1(SPTTBL1)	*/
												} E_IM_PRO_SPT_TBL_SEL;
//}涉及其他人部分


//涉及其他人修改调用(im_pro_common.c等){
/** PRO Clock block type
*/
typedef enum {
	E_IM_PRO_CLK_BLOCK_TYPE_SEN = 0,	/**< SEN block	*/
	E_IM_PRO_CLK_BLOCK_TYPE_SRO,		/**< SRO block	*/
	E_IM_PRO_CLK_BLOCK_TYPE_SRO2,		/**< SRO2 block(behind HRB)	*/
	E_IM_PRO_CLK_BLOCK_TYPE_B2B,		/**< B2B block	*/
	E_IM_PRO_CLK_BLOCK_TYPE_STAT,		/**< STAT block	*/
	E_IM_PRO_CLK_BLOCK_TYPE_PAS,		/**< PAS block	*/
	E_IM_PRO_CLK_BLOCK_TYPE_MAX,		/**< MAX value	*/
} E_IM_PRO_CLK_BLOCK_TYPE;
//}涉及其他人部分



















//涉及其他人修改调用(im_pro_common.c等){
/** AF channel number.
*/
typedef enum {
	E_IM_PRO_AF_CH0 = 0,		/**< AF ch0 */
	E_IM_PRO_AF_CH1,			/**< AF ch1 */
} E_IM_PRO_AF_CH;

/** AF Window Number
*/
typedef enum {
	E_IM_PRO_AF_WINDOW_0 = 0,			/**< AF Window 0			*/
	E_IM_PRO_AF_WINDOW_1,				/**< AF Window 1			*/
	E_IM_PRO_AF_WINDOW_2,				/**< AF Window 2			*/
	E_IM_PRO_AF_WINDOW_3,				/**< AF Window 3			*/
	E_IM_PRO_AF_WINDOW_4,				/**< AF Window 4			*/
	E_IM_PRO_AF_WINDOW_5,				/**< AF Window 5			*/
	E_IM_PRO_AF_WINDOW_6,				/**< AF Window 6			*/
	E_IM_PRO_AF_WINDOW_7,				/**< AF Window 7			*/
	E_IM_PRO_AF_WINDOW_8,				/**< AF Window 8			*/
	E_IM_PRO_AF_WINDOW_9,				/**< AF Window 9			*/
	E_IM_PRO_AF_WINDOW_10,				/**< AF Window 10			*/
	E_IM_PRO_AF_WINDOW_11,				/**< AF Window 11			*/
	E_IM_PRO_AF_WINDOW_12,				/**< AF Window 12			*/
	E_IM_PRO_AF_WINDOW_13,				/**< AF Window 13			*/
	E_IM_PRO_AF_WINDOW_14,				/**< AF Window 14			*/
	E_IM_PRO_AF_WINDOW_MAX				/**< AF Window Max			*/
} E_IM_PRO_AF_WINDOW_NO;

/** LVDS output mode.
*/
typedef enum {
	E_IM_PRO_LVDS_OUTPUT_MODE_NORNAL = 0,		/**< Normal output mode.<br>
														synchronous code detection is performed using only synchronous code0 (SAV[0]/EAV[0]/SAB[0]/EAB[0]),<br>
														the detected data is output from LVDS output0.	*/
	E_IM_PRO_LVDS_OUTPUT_MODE_DOL1,				/**< DOL output mode 1.<br>
														synchronous code detection is performed using synchronous code0(SAV[0]/EAV[0]/SAB[0]/EAB[0]) and code1(SAV[1]/EAV[1]/SAB[1]/EAB[1]),<br>
														the data of the line detected by synchronous code0 is output from LVDS output0,<br>
														and the data of the line detected by synchronous code1 is output from LVDS output1.	*/
	E_IM_PRO_LVDS_OUTPUT_MODE_DOL2,				/**< DOL output mode 2. synchronous code detection is performed using 3 groups of synchronous code:<br>
														code0(SAV[0]/EAV[0]/SAB[0]/EAB[0]), code1(SAV[1]/EAV[1]/SAB[1]/EAB[1]) and code2(SAV[2]/EAV[2]/SAB[2]/EAB[2]),<br>
														the data of the line detected by synchronous code0 is output from LVDS output0,<br>
														the data of the line detected by synchronous code1 is output from LVDS output1,<br>
														and the data of the line detected by synchronous code2 is output from LVDS output2.	*/
	E_IM_PRO_LVDS_OUTPUT_MODE_MAX,				/**< MAX value	*/
} E_IM_PRO_LVDS_OUTPUT_MODE;

/** OBT channel number
*/
typedef enum {
	E_IM_PRO_OBT_CH_0_0 = 0,			/**< BLOB0 OBT ch0	*/
	E_IM_PRO_OBT_CH_0_1,				/**< BLOB0 OBT ch1	*/
	E_IM_PRO_OBT_CH_1_0,				/**< BLOB1 OBT ch0	*/
	E_IM_PRO_OBT_CH_1_1,				/**< BLOB1 OBT ch1	*/
	E_IM_PRO_OBT_CH_2_0,				/**< BLOB2 OBT ch0	*/
	E_IM_PRO_OBT_CH_2_1,				/**< BLOB2 OBT ch1	*/
	E_IM_PRO_OBT_CH_3_0,				/**< BLOB3 OBT ch0	*/
	E_IM_PRO_OBT_CH_3_1,				/**< BLOB3 OBT ch1	*/
} E_IM_PRO_OBT_CH;

/** SLVS stream type.
*/
typedef enum {
	E_IM_PRO_SLVS_STREAM_TYPE_A = 0,		/**< Stream A		*/
	E_IM_PRO_SLVS_STREAM_TYPE_B,			/**< Stream bb		*/
	E_IM_PRO_SLVS_STREAM_TYPE_BOTH,			/**< Stream A & bb	*/
} E_IM_PRO_SLVS_STREAM_TYPE;




/** Area information for macro processing
*/
typedef struct {
	USHORT		posX;	/**< Start position x */
	USHORT		posY;	/**< Start position y */
	USHORT		width;	/**< Width of macro processing area */
	USHORT		lines;	/**< Line of macro processing area */
} T_IM_PRO_AREA_INFO;

/** PRO Get RGB SHORT data
*/
typedef struct {
	SHORT		rr;		/**< rr		*/
	SHORT		gr;		/**< gr		*/
	SHORT		gb;		/**< gb		*/
	SHORT		bb;		/**< bb		*/
} T_IM_PRO_RGB2;

/** Histgram result data format.
*/
typedef struct {
	ULONG						most_frequent_value[4];	/**< most frequent value inside the HIST window.<br>
															target registor	:[0]@@HISTRMODE [1]@@HISTGMODE [2]@@HISTBMODE [3]@@HISTYMODE */
	ULONG						accumulation_value[4];	/**< accumulation value inside the HIST window.<br>
															target registor	:[0]@@HISTRSUM [1]@@HISTGSUM [2]@@HISTBSUM [3]@@HISTYSUM */
} T_IM_PRO_HIST_DATA;

/** Histgram result RAM data format.
*/
typedef struct {
	ULONG						r[256];	/**< frequency of each pixel level of rr.<br>
															target registor	@@HISTRDATA */
	ULONG						g[256];	/**< frequency of each pixel level of G.<br>
															target registor	@@HISTGDATA */
	ULONG						b[256];	/**< frequency of each pixel level of bb.<br>
															target registor	@@HISTBDATA */
	ULONG						y[256];	/**< frequency of each pixel level of Y.<br>
															target registor	@@HISTYDATA */
} T_IM_PRO_HIST_RAM_DATA;

//}涉及其他人部分







/*类型定义区域*/
typedef struct _ImproBase					ImproBase;
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

