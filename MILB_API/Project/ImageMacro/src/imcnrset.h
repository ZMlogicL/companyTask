/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-07
*@author              :李昕
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef _IM_CNR_SET_H_
#define _IM_CNR_SET_H_

#include <klib.h>
#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include "imcnr.h"

#define IM_TYPE_CNR_SET		(im_cnr_set_get_type())
#define IM_CNR_SET(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImCnrSet))
#define IM_IS_CNR_SET(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_CNR_SET))

typedef struct 				_ImCnrSet ImCnrSet;
typedef struct 				_ImCnrSetPrivate ImCnrSetPrivate;

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
/** Ctrl_C Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	CSPREN;			/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	ULONG	CGDKEN;			/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	ULONG	MCEN;			/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	ULONG	MCYTHH;			/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	ULONG	MCYTHV;			/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	ULONG	MCCTHH;			/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	ULONG	MCCTHV;			/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	ULONG	MCYDYM;			/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	ULONG	MCYDYMDT;		/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	ULONG	MCYSCL;			/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	ULONG	MCCSCL;			/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	ULONG	MCSSCL;			/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	ULONG	LCEN;			/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	ULONG	LCYTHH;			/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	ULONG	LCYTHV;			/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	ULONG	LCCTHH;			/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	ULONG	LCCTHV;			/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	ULONG	LCYDYM;			/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	ULONG	LCYDYMDT;		/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	ULONG	LCYSCL;			/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	ULONG	LCCSCL;			/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	ULONG	LCSSCL;			/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	ULONG	BLEND;			/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	ULONG	WHTMD;			/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} T_IM_CNR_RDMA_ADDR_CTRL_C;

/** Ctrl_C Table (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_cspren		CSPREN;		/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	union	io_cnr_cspr_reg_cgdken		CGDKEN;		/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	union	io_cnr_cspr_reg_mcen		MCEN;		/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	union	io_cnr_cspr_reg_mcythh		MCYTHH;		/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	union	io_cnr_cspr_reg_mcythv		MCYTHV;		/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	union	io_cnr_cspr_reg_mccthh		MCCTHH;		/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	union	io_cnr_cspr_reg_mccthv		MCCTHV;		/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	union	io_cnr_cspr_reg_mcydym		MCYDYM;		/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	union	io_cnr_cspr_reg_mcydymdt	MCYDYMDT;	/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	union	io_cnr_cspr_reg_mcyscl		MCYSCL;		/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	union	io_cnr_cspr_reg_mccscl		MCCSCL;		/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	union	io_cnr_cspr_reg_mcsscl		MCSSCL;		/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	union	io_cnr_cspr_reg_lcen		LCEN;		/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	union	io_cnr_cspr_reg_lcythh		LCYTHH;		/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	union	io_cnr_cspr_reg_lcythv		LCYTHV;		/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	union	io_cnr_cspr_reg_lccthh		LCCTHH;		/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	union	io_cnr_cspr_reg_lccthv		LCCTHV;		/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	union	io_cnr_cspr_reg_lcydym		LCYDYM;		/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	union	io_cnr_cspr_reg_lcydymdt	LCYDYMDT;	/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	union	io_cnr_cspr_reg_lcyscl		LCYSCL;		/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	union	io_cnr_cspr_reg_lccscl		LCCSCL;		/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	union	io_cnr_cspr_reg_lcsscl		LCSSCL;		/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	union	io_cnr_cspr_reg_blend 		BLEND;		/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	union	io_cnr_cspr_reg_whtmd		WHTMD;		/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} T_IM_CNR_RDMA_DATA_CTRL_C;

/** OFL CTRL Y (OFL)
address
*/
typedef struct {
	ULONG	YSPREN;			/**< 2842_(4000 - 4003h) */
	ULONG	YSPRMODE;		/**< 2842_(4004 - 4007h) */
	ULONG	YSPRFXEY;		/**< 2842_(4020 - 4023h) */
	ULONG	YSPRFXEC;		/**< 2842_(4024 - 4027h) */
	ULONG	YSPRALPBD;		/**< 2842_(4028 - 402Bh) */
} T_IM_CNR_RDMA_ADDR_OFL_CTRL_Y;

/** OFL CTRL Y (OFL)
data
*/
typedef struct {
	union	io_cnr_ofl_reg_yspr_yspren		YSPREN;		/**< 2842_(4000 - 4003h) */
	union	io_cnr_ofl_reg_yspr_ysprmode	YSPRMODE;	/**< 2842_(4004 - 4007h) */
	union	io_cnr_ofl_reg_yspr_ysprfxey	YSPRFXEY;	/**< 2842_(4020 - 4023h) */
	union	io_cnr_ofl_reg_yspr_ysprfxec	YSPRFXEC;	/**< 2842_(4024 - 4027h) */
	union	io_cnr_ofl_reg_yspr_yspralpbd	YSPRALPBD;	/**< 2842_(4028 - 402Bh) */
} T_IM_CNR_RDMA_DATA_OFL_CTRL_Y;

/** OFL Y YSPR Table (OFL)
address
*/
typedef struct {
	ULONG	YSPRDYEYOF_1;	/**< 2842_(4030 - 4033h) */
	ULONG	YSPRDYEYOF_2;	/**< 2842_(4034 - 4037h) */
	ULONG	YSPRDYEYGA_1;	/**< 2842_(4038 - 403Bh) */
	ULONG	YSPRDYEYGA_2;	/**< 2842_(403C - 403Fh) */
	ULONG	YSPRDYEYBD_1;	/**< 2842_(4040 - 4043h) */
	ULONG	YSPRDYEYBD_2;	/**< 2842_(4044 - 4047h) */
} T_IM_CNR_RDMA_ADDR_OFL_YSPR_TBL;
/** OFL Y YSPR Table (OFL)
data
*/
typedef struct {
	struct	io_cnr_ofl_reg_yspr_ysprdyeyof	YSPRDYEYOF;	/**< 2842_(4030 - 4037h) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeyga	YSPRDYEYGA;	/**< 2842_(4038 - 403Fh) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeybd	YSPRDYEYBD;	/**< 2842_(4040 - 4047h) */
} T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL;

/** CSPR Middle Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	MCYSCLOF_1;		/**< 2842_(1048 - 104Bh),	2842_(3048 - 304Bh) */
	ULONG	MCYSCLOF_2;		/**< 2842_(104C - 104Fh),	2842_(304C - 304Fh) */
	ULONG	MCYSCLGA_1;		/**< 2842_(1050 - 1053h),	2842_(3050 - 3053h) */
	ULONG	MCYSCLGA_2;		/**< 2842_(1054 - 1057h),	2842_(3054 - 3057h) */
	ULONG	MCYSCLBD_1;		/**< 2842_(1058 - 105Bh),	2842_(3058 - 305Bh) */
	ULONG	MCYSCLBD_2;		/**< 2842_(105C - 105Fh),	2842_(305C - 305Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_MID_Y_TBL;
/** CSPR Middle Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcysclof	MCYSCLOF;	/**< 2842_(1048 - 104Fh),	2842_(3048 - 304Fh) */
	struct io_cnr_cspr_reg_mcysclga	MCYSCLGA;	/**< 2842_(1050 - 1057h),	2842_(3050 - 3057h) */
	struct io_cnr_cspr_reg_mcysclbd	MCYSCLBD;	/**< 2842_(1058 - 105Fh),	2842_(3058 - 305Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL;

/** CSPR Middle CC Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	MCCSCLOF_1;		/**< 2842_(1068 - 106Bh),	2842_(3068 - 306Bh) */
	ULONG	MCCSCLOF_2;		/**< 2842_(106C - 106Fh),	2842_(306C - 306Fh) */
	ULONG	MCCSCLGA_1;		/**< 2842_(1070 - 1073h),	2842_(3070 - 3073h) */
	ULONG	MCCSCLGA_2;		/**< 2842_(1074 - 1077h),	2842_(3074 - 3077h) */
	ULONG	MCCSCLBD_1;		/**< 2842_(1078 - 107Bh),	2842_(3078 - 307Bh) */
	ULONG	MCCSCLBD_2;		/**< 2842_(107C - 107Fh),	2842_(307C - 307Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_Y_TBL;
/** CSPR Middle CC Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mccsclof	MCCSCLOF;	/**< 2842_(1068 - 106Fh),	2842_(3068 - 306Fh) */
	struct io_cnr_cspr_reg_mccsclga	MCCSCLGA;	/**< 2842_(1070 - 1077h),	2842_(3070 - 3077h) */
	struct io_cnr_cspr_reg_mccsclbd	MCCSCLBD;	/**< 2842_(1078 - 107Fh),	2842_(3078 - 307Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL;

/** CSPR Middle CC C Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	MCSSCLOF_1;		/**< 2842_(1088 - 108Bh),	2842_(3088 - 308Bh) */
	ULONG	MCSSCLOF_2;		/**< 2842_(108C - 108Fh),	2842_(308C - 308Fh) */
	ULONG	MCSSCLGA_1;		/**< 2842_(1090 - 1093h),	2842_(3090 - 3093h) */
	ULONG	MCSSCLGA_2;		/**< 2842_(1094 - 1097h),	2842_(3094 - 3097h) */
	ULONG	MCSSCLBD_1;		/**< 2842_(1098 - 109Bh),	2842_(3098 - 309Bh) */
	ULONG	MCSSCLBD_2;		/**< 2842_(109C - 109Fh),	2842_(309C - 309Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_MID_CC_C_TBL;
/** CSPR Middle CC C Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcssclof	MCSSCLOF;	/**< 2842_(1088 - 108Fh),	2842_(3088 - 308Fh) */
	struct io_cnr_cspr_reg_mcssclga	MCSSCLGA;	/**< 2842_(1090 - 1097h),	2842_(3090 - 3097h) */
	struct io_cnr_cspr_reg_mcssclbd	MCSSCLBD;	/**< 2842_(1098 - 109Fh),	2842_(3098 - 309Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL;

/** CSPR Low Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	LCYSCLOF_1;		/**< 2842_(10E8 - 10EBh),	2842_(30E8 - 30EBh) */
	ULONG	LCYSCLOF_2;		/**< 2842_(10EC - 10EFh),	2842_(30EC - 30EFh) */
	ULONG	LCYSCLGA_1;		/**< 2842_(10F0 - 10F3h),	2842_(30F0 - 30F3h) */
	ULONG	LCYSCLGA_2;		/**< 2842_(10F4 - 10F7h),	2842_(30F4 - 30F7h) */
	ULONG	LCYSCLBD_1;		/**< 2842_(10F8 - 10F8h),	2842_(30F8 - 30F8h) */
	ULONG	LCYSCLBD_2;		/**< 2842_(10FC - 10FFh),	2842_(30FC - 30FFh) */
} T_IM_CNR_RDMA_ADDR_CSPR_LOW_Y_TBL;
/** CSPR Low Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcysclof	LCYSCLOF;	/**< 2842_(10E8 - 10EFh),	2842_(30E8 - 30EFh) */
	struct io_cnr_cspr_reg_lcysclga	LCYSCLGA;	/**< 2842_(10F0 - 10F7h),	2842_(30F0 - 30F7h) */
	struct io_cnr_cspr_reg_lcysclbd	LCYSCLBD;	/**< 2842_(10F8 - 10FFh),	2842_(30F8 - 30FFh) */
} T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL;

/** CSPR Low CC Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	LCCSCLOF_1;		/**< 2842_(1108 - 110Bh),	2842_(3108 - 310Bh) */
	ULONG	LCCSCLOF_2;		/**< 2842_(110C - 110Fh),	2842_(310C - 310Fh) */
	ULONG	LCCSCLGA_1;		/**< 2842_(1110 - 1113h),	2842_(3110 - 3113h) */
	ULONG	LCCSCLGA_2;		/**< 2842_(1114 - 1117h),	2842_(3114 - 3117h) */
	ULONG	LCCSCLBD_1;		/**< 2842_(1118 - 1118h),	2842_(3118 - 3118h) */
	ULONG	LCCSCLBD_2;		/**< 2842_(111C - 111Fh),	2842_(311C - 311Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_Y_TBL;
/** CSPR Low CC Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lccsclof	LCCSCLOF;	/**< 2842_(1108 - 110Fh),	2842_(3108 - 310Fh) */
	struct io_cnr_cspr_reg_lccsclga	LCCSCLGA;	/**< 2842_(1110 - 1117h),	2842_(3110 - 3117h) */
	struct io_cnr_cspr_reg_lccsclbd	LCCSCLBD;	/**< 2842_(1118 - 111Fh),	2842_(3118 - 311Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL;

/** CSPR Low CC C Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	LCSSCLOF_1;		/**< 2842_(1128 - 112Bh),	2842_(3128 - 312Bh) */
	ULONG	LCSSCLOF_2;		/**< 2842_(112C - 112Fh),	2842_(312C - 312Fh) */
	ULONG	LCSSCLGA_1;		/**< 2842_(1130 - 1133h),	2842_(3130 - 3133h) */
	ULONG	LCSSCLGA_2;		/**< 2842_(1134 - 1137h),	2842_(3134 - 3137h) */
	ULONG	LCSSCLBD_1;		/**< 2842_(1138 - 1138h),	2842_(3138 - 3138h) */
	ULONG	LCSSCLBD_2;		/**< 2842_(113C - 113Fh),	2842_(313C - 313Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_LOW_CC_C_TBL;
/** CSPR Low CC C Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcssclof	LCSSCLOF;	/**< 2842_(1128 - 112Fh),	2842_(3128 - 312Fh) */
	struct io_cnr_cspr_reg_lcssclga	LCSSCLGA;	/**< 2842_(1130 - 1137h),	2842_(3130 - 3137h) */
	struct io_cnr_cspr_reg_lcssclbd	LCSSCLBD;	/**< 2842_(1138 - 113Fh),	2842_(3138 - 313Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL;

/** CSPR Edge Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	CESCLOF_1;		/**< 2842_(1168 - 116Bh),	2842_(3168 - 316Bh) */
	ULONG	CESCLOF_2;		/**< 2842_(116C - 116Fh),	2842_(316C - 316Fh) */
	ULONG	CESCLGA_1;		/**< 2842_(1170 - 1173h),	2842_(3170 - 3173h) */
	ULONG	CESCLGA_2;		/**< 2842_(1174 - 1177h),	2842_(3174 - 3177h) */
	ULONG	CESCLBD_1;		/**< 2842_(1178 - 1178h),	2842_(3178 - 3178h) */
	ULONG	CESCLBD_2;		/**< 2842_(117C - 117Fh),	2842_(317C - 317Fh) */
} T_IM_CNR_RDMA_ADDR_CSPR_EDGE_TBL;
/** CSPR Edge Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_cesclof	CESCLOF;	/**< 2842_(1168 - 116Fh),	2842_(3168 - 316Fh) */
	struct io_cnr_cspr_reg_cesclga	CESCLGA;	/**< 2842_(1170 - 1177h),	2842_(3170 - 3177h) */
	struct io_cnr_cspr_reg_cesclbd	CESCLBD;	/**< 2842_(1178 - 117Fh),	2842_(3178 - 317Fh) */
} T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL;

/** CSPR_Hue_Specified (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	CPHPT;			/**< 2842_(1190 - 1193h),	2842_(3190 - 3193h) */
	ULONG	CPHPTK;			/**< 2842_(1194 - 1197h),	2842_(3194 - 3197h) */
	ULONG	CDSCLOF_1;		/**< 2842_(11A0 - 11A3h),	2842_(31A0 - 31A3h) */
	ULONG	CDSCLOF_2;		/**< 2842_(11A4 - 11A7h),	2842_(31A4 - 31A7h) */
	ULONG	CDSCLOF_3;		/**< 2842_(11A8 - 11ABh),	2842_(31A8 - 31ABh) */
	ULONG	CDSCLGA_1;		/**< 2842_(11B0 - 11B3h),	2842_(31B0 - 31B3h) */
	ULONG	CDSCLGA_2;		/**< 2842_(11B4 - 11B7h),	2842_(31B4 - 31B7h) */
	ULONG	CDSCLGA_3;		/**< 2842_(11B8 - 11BBh),	2842_(31B8 - 31BBh) */
	ULONG	CDSCLBD_1;		/**< 2842_(11C0 - 11C3h),	2842_(31C0 - 31C3h) */
	ULONG	CDSCLBD_2;		/**< 2842_(11C4 - 11C7h),	2842_(31C4 - 31C7h) */
	ULONG	CDSCLBD_3;		/**< 2842_(11C8 - 11CBh),	2842_(31C8 - 31CBh) */
} T_IM_CNR_RDMA_ADDR_CSPR_HUE_TBL;
/** CSPR_Hue_Specified (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_cphpt		CPHPT;		/**< 2842_(1190 - 1193h),	2842_(3190 - 3193h) */
	union	io_cnr_cspr_reg_cphptk		CPHPTK;		/**< 2842_(1194 - 1197h),	2842_(3194 - 3197h) */
	struct	io_cnr_cspr_reg_cdsclof		CDSCLOF;	/**< 2842_(11A0 - 11ABh),	2842_(31A0 - 31ABh) */
	struct	io_cnr_cspr_reg_cdsclga		CDSCLGA;	/**< 2842_(11B0 - 11BBh),	2842_(31B0 - 31BBh) */
	struct	io_cnr_cspr_reg_cdsclbd		CDSCLBD;	/**< 2842_(11C0 - 11CBh),	2842_(31C0 - 31CBh) */
} T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL;

/** SPRS (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	SPRS;			/**< 2842_(1200 - 1203h),	2842_(3200 - 3203h) */
	ULONG	SPRSCBOF_1;		/**< 2842_(1208 - 120Bh),	2842_(3208 - 320Bh) */
	ULONG	SPRSCBOF_2;		/**< 2842_(120C - 120Fh),	2842_(320C - 320Fh) */
	ULONG	SPRSCBGA_1;		/**< 2842_(1210 - 1213h),	2842_(3210 - 3213h) */
	ULONG	SPRSCBGA_2;		/**< 2842_(1214 - 1217h),	2842_(3214 - 3217h) */
	ULONG	SPRSCBGA_3;		/**< 2842_(1218 - 121Bh),	2842_(3218 - 321Bh) */
	ULONG	SPRSCBBD_1;		/**< 2842_(1220 - 1223h),	2842_(3220 - 3223h) */
	ULONG	SPRSCBBD_2;		/**< 2842_(1224 - 1227h),	2842_(3224 - 3227h) */
	ULONG	SPRSCROF_1;		/**< 2842_(1228 - 122Bh),	2842_(3228 - 322Bh) */
	ULONG	SPRSCROF_2;		/**< 2842_(122C - 122Fh),	2842_(322C - 322Fh) */
	ULONG	SPRSCRGA_1;		/**< 2842_(1230 - 1233h),	2842_(3230 - 3233h) */
	ULONG	SPRSCRGA_2;		/**< 2842_(1234 - 1237h),	2842_(3234 - 3237h) */
	ULONG	SPRSCRGA_3;		/**< 2842_(1238 - 123Bh),	2842_(3238 - 323Bh) */
	ULONG	SPRSCRBD_1;		/**< 2842_(1240 - 1243h),	2842_(3240 - 3243h) */
	ULONG	SPRSCRBD_2;		/**< 2842_(1244 - 1247h),	2842_(3244 - 3247h) */
} T_IM_CNR_RDMA_ADDR_SPRS_CC_TBL;
/** SPRS (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprs		SPRS;		/**< 2842_(1200 - 1203h),	2842_(3200 - 3203h) */
	struct	io_cnr_cspr_reg_sprscbof	SPRSCBOF;	/**< 2842_(1208 - 120Fh),	2842_(3208 - 320Fh) */
	struct	io_cnr_cspr_reg_sprscbga	SPRSCBGA;	/**< 2842_(1210 - 121Bh),	2842_(3210 - 321Bh) */
	struct	io_cnr_cspr_reg_sprscbbd	SPRSCBBD;	/**< 2842_(1220 - 1227h),	2842_(3220 - 3227h) */
	struct	io_cnr_cspr_reg_sprscrof	SPRSCROF;	/**< 2842_(1228 - 122Fh),	2842_(3228 - 322Fh) */
	struct	io_cnr_cspr_reg_sprscrga	SPRSCRGA;	/**< 2842_(1230 - 123Bh),	2842_(3230 - 323Bh) */
	struct	io_cnr_cspr_reg_sprscrbd	SPRSCRBD;	/**< 2842_(1240 - 1247h),	2842_(3240 - 3247h) */
} T_IM_CNR_RDMA_DATA_SPRS_CC_TBL;

/** SPRD (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	SPRD;			/**< 2842_(1280 - 1283h),	2842_(3280 - 3283h) */
	ULONG	SPRDCBOF_1;		/**< 2842_(1288 - 128Bh),	2842_(3288 - 328Bh) */
	ULONG	SPRDCBOF_2;		/**< 2842_(128C - 128Fh),	2842_(328C - 328Fh) */
	ULONG	SPRDCBGA_1;		/**< 2842_(1290 - 1293h),	2842_(3290 - 3293h) */
	ULONG	SPRDCBGA_2;		/**< 2842_(1294 - 1297h),	2842_(3294 - 3297h) */
	ULONG	SPRDCBGA_3;		/**< 2842_(1298 - 129Bh),	2842_(3298 - 329Bh) */
	ULONG	SPRDCBBD_1;		/**< 2842_(12A0 - 12A3h),	2842_(32A0 - 32A3h) */
	ULONG	SPRDCBBD_2;		/**< 2842_(12A4 - 12A7h),	2842_(32A4 - 32A7h) */
	ULONG	SPRDCROF_1;		/**< 2842_(12A8 - 122Ah),	2842_(32A8 - 322Ah) */
	ULONG	SPRDCROF_2;		/**< 2842_(12AC - 122Ah),	2842_(32AC - 322Ah) */
	ULONG	SPRDCRGA_1;		/**< 2842_(12B0 - 12B3h),	2842_(32B0 - 32B3h) */
	ULONG	SPRDCRGA_2;		/**< 2842_(12B4 - 12B7h),	2842_(32B4 - 32B7h) */
	ULONG	SPRDCRGA_3;		/**< 2842_(12B8 - 12BBh),	2842_(32B8 - 32BBh) */
	ULONG	SPRDCRBD_1;		/**< 2842_(12C0 - 12C3h),	2842_(32C0 - 32C3h) */
	ULONG	SPRDCRBD_2;		/**< 2842_(12C4 - 12C7h),	2842_(32C4 - 32C7h) */
} T_IM_CNR_RDMA_ADDR_SPRD_CC_TBL;

/** SPRD (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprd		SPRD;		/**< 2842_(1280 - 1283h),	2842_(3280 - 3283h) */
	struct	io_cnr_cspr_reg_sprdcbof	SPRDCBOF;	/**< 2842_(1288 - 128Fh),	2842_(3288 - 328Fh) */
	struct	io_cnr_cspr_reg_sprdcbga	SPRDCBGA;	/**< 2842_(1290 - 129Bh),	2842_(3290 - 329Bh) */
	struct	io_cnr_cspr_reg_sprdcbbd	SPRDCBBD;	/**< 2842_(12A0 - 12A7h),	2842_(32A0 - 32A7h) */
	struct	io_cnr_cspr_reg_sprdcrof	SPRDCROF;	/**< 2842_(12A8 - 12AFh),	2842_(32A8 - 32AFh) */
	struct	io_cnr_cspr_reg_sprdcrga	SPRDCRGA;	/**< 2842_(12B0 - 12BBh),	2842_(32B0 - 32BBh) */
	struct	io_cnr_cspr_reg_sprdcrbd	SPRDCRBD;	/**< 2842_(12C0 - 12C7h),	2842_(32C0 - 32C7h) */
} T_IM_CNR_RDMA_DATA_SPRD_CC_TBL;
#endif

struct _ImCnrSet {
	KObject parent;
};

KConstType 		    im_cnr_set_get_type(void);
ImCnrSet*		        im_cnr_set_new(void);

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------
#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
//------------ for RDMA ----------------
/**
Set SPR setting parameter information for C for Off Line
@param[in]	spr_ctrl_c		C suppre parameter
@param[out]	rdma_ctrl_c		C suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_Ctrl_C( const T_IM_CNR_CTRL_C* const spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* const rdma_ctrl_c );

/**
Set SPR setting parameter information for C for On The Fly
@param[in]	spr_ctrl_c		C suppre parameter
@param[out]	rdma_ctrl_c		C suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_Ctrl_C( const T_IM_CNR_CTRL_C* const spr_ctrl_c, T_IM_CNR_RDMA_DATA_CTRL_C* const rdma_ctrl_c );

/**
Set CSPR Mid-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_y			C suppre Middle-Y parameter
@param[out]	rdma_cspr_mid_y_table	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* const rdma_cspr_mid_y_table );

/**
Set CSPR Mid-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_y			C suppre Middle-Y parameter
@param[out]	rdma_cspr_mid_y_table	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_y, T_IM_CNR_RDMA_DATA_CSPR_MID_Y_TBL* const rdma_cspr_mid_y_table );

/**
Set CSPR Mid-CC-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_cc_y			C suppre Middle-CC-Y parameter
@param[out]	rdma_cspr_mid_cc_y_table	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* const rdma_cspr_mid_cc_y_table );

/**
Set CSPR Mid-CC-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_cc_y			C suppre Middle-CC-Y parameter
@param[out]	rdma_cspr_mid_cc_y_table	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_y, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_Y_TBL* const rdma_cspr_mid_cc_y_table );

/**
Set CSPR Mid-CC-C setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_cc_c			C suppre Middle-CC-C parameter
@param[out]	rdma_cspr_mid_cc_c_table	C suppre Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Mid_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* const rdma_cspr_mid_cc_c_table );

/**
Set CSPR Mid-CC-C setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_cc_c			C suppre Middle-CC-C Middle-CC-C parameter
@param[out]	rdma_cspr_mid_cc_c_table	C suppre Middle-CC-C Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Mid_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_mid_cc_c, T_IM_CNR_RDMA_DATA_CSPR_MID_CC_C_TBL* const rdma_cspr_mid_cc_c_table );

/**
Set CSPR Low-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_low_y			C suppre Low-Y parameter
@param[out]	rdma_cspr_low_y_table	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* const rdma_cspr_low_y_table );

/**
Set CSPR Low-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_y			C suppre Low-Y parameter
@param[out]	rdma_cspr_low_y_table	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_Y_TBL* const rdma_cspr_low_y_table );

/**
Set CSPR Low-CC-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_low_cc_y			C suppre Low-CC-Y parameter
@param[out]	rdma_cspr_low_cc_y_table	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* const rdma_cspr_low_cc_y_table );

/**
Set CSPR Low-CC-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_cc_y			C suppre Low-CC-Y parameter
@param[out]	rdma_cspr_low_cc_y_table	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_Y_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_y, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_Y_TBL* const rdma_cspr_low_cc_y_table );

/**
Set CSPR Low-CC-C setting parameter information for C for Off Line
@param[in]	spr_cspr_low_cc_c			C suppre Low-CC-C parameter
@param[out]	rdma_cspr_low_cc_c_table	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Low_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* const rdma_cspr_low_cc_c_table );

/**
Set CSPR Low-CC-C setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_cc_c			C suppre Low-CC-C parameter
@param[out]	rdma_cspr_low_cc_c_table	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Low_CC_C_Table( const T_IM_CNR_TABLE* const spr_cspr_low_cc_c, T_IM_CNR_RDMA_DATA_CSPR_LOW_CC_C_TBL* const rdma_cspr_low_cc_c_table );

/**
Set CSPR Edge setting parameter information for C for Off Line
@param[in]	spr_cspr_edge			C suppre Edge parameter
@param[out]	rdma_cspr_edge_table	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Edge_Table( const T_IM_CNR_TABLE* const spr_cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* const rdma_cspr_edge_table );

/**
Set CSPR Edge setting parameter information for C for On The Fly
@param[in]	spr_cspr_edge			C suppre Edge parameter
@param[out]	rdma_cspr_edge_table	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Edge_Table( const T_IM_CNR_TABLE* const spr_cspr_edge, T_IM_CNR_RDMA_DATA_CSPR_EDGE_TBL* const rdma_cspr_edge_table );

/**
Set CSPR Hue Specified setting parameter information for C for Off Line
@param[in]	spr_cspr_hue			C suppre Hue Specified parameter
@param[out]	rdma_cspr_hue_table		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_Hue_Spec_Table( const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* const rdma_cspr_hue_table );

/**
Set CSPR Hue Specified setting parameter information for C for On The Fly
@param[in]	spr_cspr_hue			C suppre Hue Specified parameter
@param[out]	rdma_cspr_hue_table		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_Hue_Spec_Table( const T_IM_CNR_HUE_SPEC_TABLE* const spr_cspr_hue, T_IM_CNR_RDMA_DATA_CSPR_HUE_TBL* const rdma_cspr_hue_table );

/**
Set CSPR SPRS setting parameter information for C for Off Line
@param[in]	cspr_sprs_cc			C suppre SPRS CC parameter
@param[out]	rdma_cspr_sprs_cc		C suppre SPRS CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_SPRS_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprs_cc, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* const rdma_cspr_sprs_cc );

/**
Set CSPR SPRS setting parameter information for C for On The Fly
@param[in]	cspr_sprs_cc			C suppre SPRS CC parameter
@param[out]	rdma_cspr_sprs_cc		C suppre SPRS CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_SPRS_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprs_cc, T_IM_CNR_RDMA_DATA_SPRS_CC_TBL* const rdma_cspr_sprs_cc );

/**
Set CSPR SPRD setting parameter information for C for Off Line
@param[in]	cspr_sprd_cc			C suppre SPRD CC parameter
@param[out]	rdma_cspr_sprd_cc		C suppre SPRD CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_CSPR_SPRD_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprd_cc, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* const rdma_cspr_sprd_cc );

/**
Set CSPR SPRD setting parameter information for C for On The Fly
@param[in]	cspr_sprd_cc			C suppre SPRD CC parameter
@param[out]	rdma_cspr_sprd_cc		C suppre SPRD CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OTF_CSPR_SPRD_CC_Table( const T_IM_CNR_CTRL_CC_SRC_DST* const cspr_sprd_cc, T_IM_CNR_RDMA_DATA_SPRD_CC_TBL* const rdma_cspr_sprd_cc );


/**
Set SPR table setting parameter information for Y for Off Line
@param[in]	yspr_table		Y suppre table parameter
@param[out]	rdma_yspr_table	Y suppre table parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_YSPR_Table( const T_IM_CNR_TABLE* const yspr_table, T_IM_CNR_RDMA_DATA_OFL_YSPR_TBL* const rdma_yspr_table );

/**
Set SPR setting parameter information for Y for Off Line
@param[in]	spr_ctrl_y		Y suppre parameter
@param[out]	rdma_ctrl_y		Y suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 Im_CNR_Set_RdmaValue_OFL_Ctrl_Y( const T_IM_CNR_OFL_CTRL_Y* const spr_ctrl_y, T_IM_CNR_RDMA_DATA_OFL_CTRL_Y* const rdma_ctrl_y );

#endif

#ifdef __cplusplus
}
#endif

#endif//_IM_CNR_SET_H_
