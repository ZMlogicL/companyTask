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
	ULONG	csprEn;			/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	ULONG	cgdkEn;			/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	ULONG	mcEn;			/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	ULONG	mcYthh;			/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	ULONG	mcYthv;			/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	ULONG	mcCthh;			/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	ULONG	mcCthv;			/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	ULONG	mcYdym;			/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	ULONG	mcYdymDt;		/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	ULONG	mcYscl;			/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	ULONG	mcCscl;			/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	ULONG	mcSscl;			/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	ULONG	lcEn;			/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	ULONG	lcYthh;			/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	ULONG	lcYthv;			/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	ULONG	lcCthh;			/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	ULONG	lcCthv;			/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	ULONG	lcYdym;			/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	ULONG	lcYdymDt;		/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	ULONG	lcYscl;			/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	ULONG	lcCscl;			/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	ULONG	lcSscl;			/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	ULONG	blEnd;			/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	ULONG	whTmd;			/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} TImCnrRdmaAddrCtrlC;

/** Ctrl_C Table (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_cspren		csprEn;		/**< 2842_(1000 - 1003h),	2842_(3000 - 3003h) */
	union	io_cnr_cspr_reg_cgdken		cgdkEn;		/**< 2842_(1008 - 100Bh),	2842_(3008 - 300Bh) */
	union	io_cnr_cspr_reg_mcen		mcEn;		/**< 2842_(1020 - 1023h),	2842_(3020 - 3023h) */
	union	io_cnr_cspr_reg_mcythh		mcYthh;		/**< 2842_(1024 - 1027h),	2842_(3024 - 3027h) */
	union	io_cnr_cspr_reg_mcythv		mcYthv;		/**< 2842_(1028 - 102Bh),	2842_(3028 - 302Bh) */
	union	io_cnr_cspr_reg_mccthh		mcCthh;		/**< 2842_(102C - 102Fh),	2842_(302C - 302Fh) */
	union	io_cnr_cspr_reg_mccthv		mcCthv;		/**< 2842_(1030 - 1033h),	2842_(3030 - 3033h) */
	union	io_cnr_cspr_reg_mcydym		mcYdym;		/**< 2842_(1034 - 1037h),	2842_(3034 - 3037h) */
	union	io_cnr_cspr_reg_mcydymdt	mcYdymDt;	/**< 2842_(1038 - 103Bh),	2842_(3038 - 303Bh) */
	union	io_cnr_cspr_reg_mcyscl		mcYscl;		/**< 2842_(1040 - 1043h),	2842_(3040 - 3043h) */
	union	io_cnr_cspr_reg_mccscl		mcCscl;		/**< 2842_(1060 - 1063h),	2842_(3060 - 3063h) */
	union	io_cnr_cspr_reg_mcsscl		mcSscl;		/**< 2842_(1080 - 1083h),	2842_(3080 - 3083h) */
	union	io_cnr_cspr_reg_lcen		lcEn;		/**< 2842_(10C0 - 10C3h),	2842_(30C0 - 30C3h) */
	union	io_cnr_cspr_reg_lcythh		lcYthh;		/**< 2842_(10C4 - 10C7h),	2842_(30C4 - 30C7h) */
	union	io_cnr_cspr_reg_lcythv		lcYthv;		/**< 2842_(10C8 - 10CBh),	2842_(30C8 - 30CBh) */
	union	io_cnr_cspr_reg_lccthh		lcCthh;		/**< 2842_(10CC - 10CFh),	2842_(30CC - 30CFh) */
	union	io_cnr_cspr_reg_lccthv		lcCthv;		/**< 2842_(10D0 - 10D3h),	2842_(30D0 - 30D3h) */
	union	io_cnr_cspr_reg_lcydym		lcYdym;		/**< 2842_(10D4 - 10D7h),	2842_(30D4 - 30D7h) */
	union	io_cnr_cspr_reg_lcydymdt	lcYdymDt;	/**< 2842_(10D8 - 10DBh),	2842_(30D8 - 30DBh) */
	union	io_cnr_cspr_reg_lcyscl		lcYscl;		/**< 2842_(10E0 - 10E3h),	2842_(30E0 - 30E3h) */
	union	io_cnr_cspr_reg_lccscl		lcCscl;		/**< 2842_(1100 - 1103h),	2842_(3100 - 3103h) */
	union	io_cnr_cspr_reg_lcsscl		lcSscl;		/**< 2842_(1120 - 1123h),	2842_(3120 - 3123h) */
	union	io_cnr_cspr_reg_blend 		blEnd;		/**< 2842_(1160 - 1163h),	2842_(3160 - 3163h) */
	union	io_cnr_cspr_reg_whtmd		whTmd;		/**< 2842_(11D0 - 11D3h),	2842_(31D0 - 31D3h) */
} TImCnrRdmaDataCtrlC;

/** OFL CTRL Y (OFL)
address
*/
typedef struct {
	ULONG	ysprEn;			/**< 2842_(4000 - 4003h) */
	ULONG	ysprMode;		/**< 2842_(4004 - 4007h) */
	ULONG	ysprFxey;		/**< 2842_(4020 - 4023h) */
	ULONG	ysprFxec;		/**< 2842_(4024 - 4027h) */
	ULONG	ysprAlpbd;		/**< 2842_(4028 - 402Bh) */
} TImCnrRdmaAddrOflCtrlY;

/** OFL CTRL Y (OFL)
data
*/
typedef struct {
	union	io_cnr_ofl_reg_yspr_yspren		ysprEn;		/**< 2842_(4000 - 4003h) */
	union	io_cnr_ofl_reg_yspr_ysprmode	ysprMode;	/**< 2842_(4004 - 4007h) */
	union	io_cnr_ofl_reg_yspr_ysprfxey	ysprFxey;	/**< 2842_(4020 - 4023h) */
	union	io_cnr_ofl_reg_yspr_ysprfxec	ysprFxec;	/**< 2842_(4024 - 4027h) */
	union	io_cnr_ofl_reg_yspr_yspralpbd	ysprAlpbd;	/**< 2842_(4028 - 402Bh) */
} TImCnrRdmaDataOflCtrlY;

/** OFL Y YSPR Table (OFL)
address
*/
typedef struct {
	ULONG	ysprDyeyof1;	/**< 2842_(4030 - 4033h) */
	ULONG	ysprDyeyof2;	/**< 2842_(4034 - 4037h) */
	ULONG	ysprDyeyga1;	/**< 2842_(4038 - 403Bh) */
	ULONG	ysprDyeyga2;	/**< 2842_(403C - 403Fh) */
	ULONG	ysprDyeybd1;	/**< 2842_(4040 - 4043h) */
	ULONG	ysprDyeybd2;	/**< 2842_(4044 - 4047h) */
}TImCnrRdmaAddrOflYsprTbl;
/** OFL Y YSPR Table (OFL)
data
*/
typedef struct {
	struct	io_cnr_ofl_reg_yspr_ysprdyeyof	ysprDyeyof;	/**< 2842_(4030 - 4037h) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeyga	ysprDyeyga;	/**< 2842_(4038 - 403Fh) */
	struct	io_cnr_ofl_reg_yspr_ysprdyeybd	ysprDyeybd;	/**< 2842_(4040 - 4047h) */
} TImCnrRdmaDataOflYsprTbl;

/** CSPR Middle Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	mcysClof1;		/**< 2842_(1048 - 104Bh),	2842_(3048 - 304Bh) */
	ULONG	mcysClof2;		/**< 2842_(104C - 104Fh),	2842_(304C - 304Fh) */
	ULONG	mcysClga1;		/**< 2842_(1050 - 1053h),	2842_(3050 - 3053h) */
	ULONG	mcysClga2;		/**< 2842_(1054 - 1057h),	2842_(3054 - 3057h) */
	ULONG	mcysClbd1;		/**< 2842_(1058 - 105Bh),	2842_(3058 - 305Bh) */
	ULONG	mcysClbd2;		/**< 2842_(105C - 105Fh),	2842_(305C - 305Fh) */
} TImCnrRdmaAddrCsprMidYTbl;
/** CSPR Middle Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcysclof	mcysClof;	/**< 2842_(1048 - 104Fh),	2842_(3048 - 304Fh) */
	struct io_cnr_cspr_reg_mcysclga	mcysClga;	/**< 2842_(1050 - 1057h),	2842_(3050 - 3057h) */
	struct io_cnr_cspr_reg_mcysclbd	mcysClbd;	/**< 2842_(1058 - 105Fh),	2842_(3058 - 305Fh) */
} TImCnrRdmaDataCsprMidYTbl;

/** CSPR Middle CC Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	mccsClof1;		/**< 2842_(1068 - 106Bh),	2842_(3068 - 306Bh) */
	ULONG	mccsClof2;		/**< 2842_(106C - 106Fh),	2842_(306C - 306Fh) */
	ULONG	mccsClga1;		/**< 2842_(1070 - 1073h),	2842_(3070 - 3073h) */
	ULONG	mccsClga2;		/**< 2842_(1074 - 1077h),	2842_(3074 - 3077h) */
	ULONG	mccsClbd1;		/**< 2842_(1078 - 107Bh),	2842_(3078 - 307Bh) */
	ULONG	mccsClbd2;		/**< 2842_(107C - 107Fh),	2842_(307C - 307Fh) */
} TImCnrRdmaAddrCsprMidCcYTbl;
/** CSPR Middle CC Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mccsclof	    mccsClof;	/**< 2842_(1068 - 106Fh),	2842_(3068 - 306Fh) */
	struct io_cnr_cspr_reg_mccsclga	    mccsClga;	/**< 2842_(1070 - 1077h),	2842_(3070 - 3077h) */
	struct io_cnr_cspr_reg_mccsclbd	mccsClbd;	/**< 2842_(1078 - 107Fh),	2842_(3078 - 307Fh) */
} TImCnrRdmaDataCsprMidCcYTbl;

/** CSPR Middle CC C Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	mcssClof1;		/**< 2842_(1088 - 108Bh),	2842_(3088 - 308Bh) */
	ULONG	mcssClof2;		/**< 2842_(108C - 108Fh),	2842_(308C - 308Fh) */
	ULONG	mcssClga1;		/**< 2842_(1090 - 1093h),	2842_(3090 - 3093h) */
	ULONG	mcssClga2;		/**< 2842_(1094 - 1097h),	2842_(3094 - 3097h) */
	ULONG	mcssClbd1;		/**< 2842_(1098 - 109Bh),	2842_(3098 - 309Bh) */
	ULONG	mcssClbd2;		/**< 2842_(109C - 109Fh),	2842_(309C - 309Fh) */
} TImCnrRdmaAddrCsprMidCcCTbl;
/** CSPR Middle CC C Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_mcssclof	    mcssClof;	/**< 2842_(1088 - 108Fh),	2842_(3088 - 308Fh) */
	struct io_cnr_cspr_reg_mcssclga    mcssClga;	/**< 2842_(1090 - 1097h),	2842_(3090 - 3097h) */
	struct io_cnr_cspr_reg_mcssclbd	mcssClbd;	/**< 2842_(1098 - 109Fh),	2842_(3098 - 309Fh) */
} TImCnrRdmaDataCsprMidCcCTbl;

/** CSPR Low Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	lcysClof1;		/**< 2842_(10E8 - 10EBh),	2842_(30E8 - 30EBh) */
	ULONG	lcysClof2;		/**< 2842_(10EC - 10EFh),	2842_(30EC - 30EFh) */
	ULONG	lcysClga1;		/**< 2842_(10F0 - 10F3h),	2842_(30F0 - 30F3h) */
	ULONG	lcysClga2;		/**< 2842_(10F4 - 10F7h),	2842_(30F4 - 30F7h) */
	ULONG	lcysClbd1;		/**< 2842_(10F8 - 10F8h),	2842_(30F8 - 30F8h) */
	ULONG	lcysClbd2;		/**< 2842_(10FC - 10FFh),	2842_(30FC - 30FFh) */
} TImCnrRdmaAddrCsprLowYTbl;
/** CSPR Low Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcysclof	lcysClof;	/**< 2842_(10E8 - 10EFh),	2842_(30E8 - 30EFh) */
	struct io_cnr_cspr_reg_lcysclga	lcysClga;	/**< 2842_(10F0 - 10F7h),	2842_(30F0 - 30F7h) */
	struct io_cnr_cspr_reg_lcysclbd	lcysClbd;	/**< 2842_(10F8 - 10FFh),	2842_(30F8 - 30FFh) */
} TImCnrRdmaDataCsprLowYTbl;

/** CSPR Low CC Y Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	lccsClof1;		/**< 2842_(1108 - 110Bh),	2842_(3108 - 310Bh) */
	ULONG	lccsClof2;		/**< 2842_(110C - 110Fh),	2842_(310C - 310Fh) */
	ULONG	lccsClga1;		/**< 2842_(1110 - 1113h),	2842_(3110 - 3113h) */
	ULONG	lccsClga2;		/**< 2842_(1114 - 1117h),	2842_(3114 - 3117h) */
	ULONG	lccsClbd1;		/**< 2842_(1118 - 1118h),	2842_(3118 - 3118h) */
	ULONG	lccsClbd2;		/**< 2842_(111C - 111Fh),	2842_(311C - 311Fh) */
} TImCnrRdmaAddrCsprLowCcYTbl;
/** CSPR Low CC Y Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lccsclof	lccsClof;	/**< 2842_(1108 - 110Fh),	2842_(3108 - 310Fh) */
	struct io_cnr_cspr_reg_lccsclga	lccsClga;	/**< 2842_(1110 - 1117h),	2842_(3110 - 3117h) */
	struct io_cnr_cspr_reg_lccsclbd	lccsClbd;	/**< 2842_(1118 - 111Fh),	2842_(3118 - 311Fh) */
} TImCnrRdmaDataCsprLowCcYTbl;

/** CSPR Low CC C Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	lcssClof1;		/**< 2842_(1128 - 112Bh),	2842_(3128 - 312Bh) */
	ULONG	lcssClof2;		/**< 2842_(112C - 112Fh),	2842_(312C - 312Fh) */
	ULONG	lcssClga1;		/**< 2842_(1130 - 1133h),	2842_(3130 - 3133h) */
	ULONG	lcssClga2;		/**< 2842_(1134 - 1137h),	2842_(3134 - 3137h) */
	ULONG	lcssClbd1;		/**< 2842_(1138 - 1138h),	2842_(3138 - 3138h) */
	ULONG	lcssClbd2;		/**< 2842_(113C - 113Fh),	2842_(313C - 313Fh) */
} TImCnrRdmaAddrCsprLowCcCTbl;
/** CSPR Low CC C Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcssclof	lcssClof;	/**< 2842_(1128 - 112Fh),	2842_(3128 - 312Fh) */
	struct io_cnr_cspr_reg_lcssclga	lcssClga;	/**< 2842_(1130 - 1137h),	2842_(3130 - 3137h) */
	struct io_cnr_cspr_reg_lcssclbd	lcssClbd;	/**< 2842_(1138 - 113Fh),	2842_(3138 - 313Fh) */
} TImCnrRdmaDataCsprLowCcCTbl;

/** CSPR Edge Table (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	cesClof1;		/**< 2842_(1168 - 116Bh),	2842_(3168 - 316Bh) */
	ULONG	cesClof2;		/**< 2842_(116C - 116Fh),	2842_(316C - 316Fh) */
	ULONG	cesClga1;		/**< 2842_(1170 - 1173h),	2842_(3170 - 3173h) */
	ULONG	cesClga2;		/**< 2842_(1174 - 1177h),	2842_(3174 - 3177h) */
	ULONG	cesClbd1;		/**< 2842_(1178 - 1178h),	2842_(3178 - 3178h) */
	ULONG	cesClbd2;		/**< 2842_(117C - 117Fh),	2842_(317C - 317Fh) */
} TImCnrRdmaAddrCsprEdgeTbl;
/** CSPR Edge Table (OTF/OFL)
data
*/
typedef struct {
	//											OTF							OFL
	struct io_cnr_cspr_reg_cesclof  	cesClof;	/**< 2842_(1168 - 116Fh),	2842_(3168 - 316Fh) */
	struct io_cnr_cspr_reg_cesclga	cesClga;	/**< 2842_(1170 - 1177h),	2842_(3170 - 3177h) */
	struct io_cnr_cspr_reg_cesclbd	cesClbd;	/**< 2842_(1178 - 117Fh),	2842_(3178 - 317Fh) */
} TImCnrRdmaDataCsprEdgeTbl;

/** CSPR_Hue_Specified (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	cphpt;			/**< 2842_(1190 - 1193h),	2842_(3190 - 3193h) */
	ULONG	cphptk;			/**< 2842_(1194 - 1197h),	2842_(3194 - 3197h) */
	ULONG	cdsClof1;		/**< 2842_(11A0 - 11A3h),	2842_(31A0 - 31A3h) */
	ULONG	cdsClof2;		/**< 2842_(11A4 - 11A7h),	2842_(31A4 - 31A7h) */
	ULONG	cdsClof3;		/**< 2842_(11A8 - 11ABh),	2842_(31A8 - 31ABh) */
	ULONG	cdsClga1;		/**< 2842_(11B0 - 11B3h),	2842_(31B0 - 31B3h) */
	ULONG	cdsClga2;		/**< 2842_(11B4 - 11B7h),	2842_(31B4 - 31B7h) */
	ULONG	cdsClga3;		/**< 2842_(11B8 - 11BBh),	2842_(31B8 - 31BBh) */
	ULONG	cdsClbd1;		/**< 2842_(11C0 - 11C3h),	2842_(31C0 - 31C3h) */
	ULONG	cdsClbd2;		/**< 2842_(11C4 - 11C7h),	2842_(31C4 - 31C7h) */
	ULONG	cdsClbd3;		/**< 2842_(11C8 - 11CBh),	2842_(31C8 - 31CBh) */
} TImCnrRdmaAddrCsprHueTbl;
/** CSPR_Hue_Specified (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_cphpt		cphpt;		/**< 2842_(1190 - 1193h),	2842_(3190 - 3193h) */
	union	io_cnr_cspr_reg_cphptk		cphptk;		/**< 2842_(1194 - 1197h),	2842_(3194 - 3197h) */
	struct	io_cnr_cspr_reg_cdsclof		cdsClof;	/**< 2842_(11A0 - 11ABh),	2842_(31A0 - 31ABh) */
	struct	io_cnr_cspr_reg_cdsclga		cdsClga;	/**< 2842_(11B0 - 11BBh),	2842_(31B0 - 31BBh) */
	struct	io_cnr_cspr_reg_cdsclbd		cdsClbd;	/**< 2842_(11C0 - 11CBh),	2842_(31C0 - 31CBh) */
} TImCnrRdmaDataCsprHueTbl;

/** sprs (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	sprs;			/**< 2842_(1200 - 1203h),	2842_(3200 - 3203h) */
	ULONG	sprsCbof1;		/**< 2842_(1208 - 120Bh),	2842_(3208 - 320Bh) */
	ULONG	sprsCbof2;		/**< 2842_(120C - 120Fh),	2842_(320C - 320Fh) */
	ULONG	sprsCbga1;		/**< 2842_(1210 - 1213h),	2842_(3210 - 3213h) */
	ULONG	sprsCbga2;		/**< 2842_(1214 - 1217h),	2842_(3214 - 3217h) */
	ULONG	sprsCbga3;		/**< 2842_(1218 - 121Bh),	2842_(3218 - 321Bh) */
	ULONG	sprsCbbd1;		/**< 2842_(1220 - 1223h),	2842_(3220 - 3223h) */
	ULONG	sprsCbbd2;		/**< 2842_(1224 - 1227h),	2842_(3224 - 3227h) */
	ULONG	sprsCrof1;		/**< 2842_(1228 - 122Bh),	2842_(3228 - 322Bh) */
	ULONG	sprsCrof2;		/**< 2842_(122C - 122Fh),	2842_(322C - 322Fh) */
	ULONG	sprsCrga1;		/**< 2842_(1230 - 1233h),	2842_(3230 - 3233h) */
	ULONG	sprsCrga2;		/**< 2842_(1234 - 1237h),	2842_(3234 - 3237h) */
	ULONG	sprsCrga3;		/**< 2842_(1238 - 123Bh),	2842_(3238 - 323Bh) */
	ULONG	sprsCrbd1;		/**< 2842_(1240 - 1243h),	2842_(3240 - 3243h) */
	ULONG	sprsCrbd2;		/**< 2842_(1244 - 1247h),	2842_(3244 - 3247h) */
} TImCnrRdmaAddrSprsCcTbl;
/** sprs (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprs		sprs;		/**< 2842_(1200 - 1203h),	2842_(3200 - 3203h) */
	struct	io_cnr_cspr_reg_sprscbof	sprsCbof;	/**< 2842_(1208 - 120Fh),	2842_(3208 - 320Fh) */
	struct	io_cnr_cspr_reg_sprscbga	sprsCbga;	/**< 2842_(1210 - 121Bh),	2842_(3210 - 321Bh) */
	struct	io_cnr_cspr_reg_sprscbbd	sprsCbbd;	/**< 2842_(1220 - 1227h),	2842_(3220 - 3227h) */
	struct	io_cnr_cspr_reg_sprscrof	    sprsCrof;	/**< 2842_(1228 - 122Fh),	2842_(3228 - 322Fh) */
	struct	io_cnr_cspr_reg_sprscrga	sprsCrga;	/**< 2842_(1230 - 123Bh),	2842_(3230 - 323Bh) */
	struct	io_cnr_cspr_reg_sprscrbd	sprsCrbd;	/**< 2842_(1240 - 1247h),	2842_(3240 - 3247h) */
} TImCnrRdmaDataSprsCcTbl;

/** sprd (OTF/OFL)
address
*/
typedef struct {
	//						OTF							OFL
	ULONG	sprd;			/**< 2842_(1280 - 1283h),	2842_(3280 - 3283h) */
	ULONG	sprdCbof1;		/**< 2842_(1288 - 128Bh),	2842_(3288 - 328Bh) */
	ULONG	sprdCbof2;		/**< 2842_(128C - 128Fh),	2842_(328C - 328Fh) */
	ULONG	sprdCbga1;		/**< 2842_(1290 - 1293h),	2842_(3290 - 3293h) */
	ULONG	sprdCbga2;		/**< 2842_(1294 - 1297h),	2842_(3294 - 3297h) */
	ULONG	sprdCbga3;		/**< 2842_(1298 - 129Bh),	2842_(3298 - 329Bh) */
	ULONG	sprdCbbd1;		/**< 2842_(12A0 - 12A3h),	2842_(32A0 - 32A3h) */
	ULONG	sprdCbbd2;		/**< 2842_(12A4 - 12A7h),	2842_(32A4 - 32A7h) */
	ULONG	sprdCrof1;		/**< 2842_(12A8 - 122Ah),	2842_(32A8 - 322Ah) */
	ULONG	sprdCrof2;		/**< 2842_(12AC - 122Ah),	2842_(32AC - 322Ah) */
	ULONG	sprdCrga1;		/**< 2842_(12B0 - 12B3h),	2842_(32B0 - 32B3h) */
	ULONG	sprdCrga2;		/**< 2842_(12B4 - 12B7h),	2842_(32B4 - 32B7h) */
	ULONG	sprdCrga3;		/**< 2842_(12B8 - 12BBh),	2842_(32B8 - 32BBh) */
	ULONG	sprdCrbd1;		/**< 2842_(12C0 - 12C3h),	2842_(32C0 - 32C3h) */
	ULONG	sprdCrbd2;		/**< 2842_(12C4 - 12C7h),	2842_(32C4 - 32C7h) */
} TImCnrRdmaAddrSprdCcTbl;

/** sprd (OTF/OFL)
data
*/
typedef struct {
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprd		sprd;		/**< 2842_(1280 - 1283h),	2842_(3280 - 3283h) */
	struct	io_cnr_cspr_reg_sprdcbof	sprdCbof;	/**< 2842_(1288 - 128Fh),	2842_(3288 - 328Fh) */
	struct	io_cnr_cspr_reg_sprdcbga	sprdCbga;	/**< 2842_(1290 - 129Bh),	2842_(3290 - 329Bh) */
	struct	io_cnr_cspr_reg_sprdcbbd	sprdCbbd;	/**< 2842_(12A0 - 12A7h),	2842_(32A0 - 32A7h) */
	struct	io_cnr_cspr_reg_sprdcrof	sprdCrof;	/**< 2842_(12A8 - 12AFh),	2842_(32A8 - 32AFh) */
	struct	io_cnr_cspr_reg_sprdcrga	sprdCrga;	/**< 2842_(12B0 - 12BBh),	2842_(32B0 - 32BBh) */
	struct	io_cnr_cspr_reg_sprdcrbd	sprdCrbd;	/**< 2842_(12C0 - 12C7h),	2842_(32C0 - 32C7h) */
} TImCnrRdmaDataSprdCcTbl;
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
INT32 im_cnr_set_rdma_value_ofl_ctrl_c(ImCnrSet*self, const TImCnrCtrlC* const spr_ctrl_c, TImCnrRdmaDataCtrlC* const rdma_ctrl_c );

/**
Set SPR setting parameter information for C for On The Fly
@param[in]	spr_ctrl_c		C suppre parameter
@param[out]	rdma_ctrl_c		C suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_ctrl_c(ImCnrSet*self, const TImCnrCtrlC* const spr_ctrl_c, TImCnrRdmaDataCtrlC* const rdma_ctrl_c );

/**
Set CSPR Mid-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_y			C suppre Middle-Y parameter
@param[out]	rdma_cspr_mid_y_table	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* const rdma_cspr_mid_y_table );

/**
Set CSPR Mid-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_y			C suppre Middle-Y parameter
@param[out]	rdma_cspr_mid_y_table	C suppre Middle-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_y, TImCnrRdmaDataCsprMidYTbl* const rdma_cspr_mid_y_table );

/**
Set CSPR Mid-CC-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_cc_y			C suppre Middle-CC-Y parameter
@param[out]	rdma_cspr_mid_cc_y_table	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* const rdma_cspr_mid_cc_y_table );

/**
Set CSPR Mid-CC-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_cc_y			C suppre Middle-CC-Y parameter
@param[out]	rdma_cspr_mid_cc_y_table	C suppre Middle-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_y, TImCnrRdmaDataCsprMidCcYTbl* const rdma_cspr_mid_cc_y_table );

/**
Set CSPR Mid-CC-C setting parameter information for C for Off Line
@param[in]	spr_cspr_mid_cc_c			C suppre Middle-CC-C parameter
@param[out]	rdma_cspr_mid_cc_c_table	C suppre Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_mid_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* const rdma_cspr_mid_cc_c_table );

/**
Set CSPR Mid-CC-C setting parameter information for C for On The Fly
@param[in]	spr_cspr_mid_cc_c			C suppre Middle-CC-C Middle-CC-C parameter
@param[out]	rdma_cspr_mid_cc_c_table	C suppre Middle-CC-C Middle-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_mid_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_mid_cc_c, TImCnrRdmaDataCsprMidCcCTbl* const rdma_cspr_mid_cc_c_table );

/**
Set CSPR Low-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_low_y			C suppre Low-Y parameter
@param[out]	rdma_cspr_low_y_table	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* const rdma_cspr_low_y_table );

/**
Set CSPR Low-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_y			C suppre Low-Y parameter
@param[out]	rdma_cspr_low_y_table	C suppre Low-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_y, TImCnrRdmaDataCsprLowYTbl* const rdma_cspr_low_y_table );

/**
Set CSPR Low-CC-Y setting parameter information for C for Off Line
@param[in]	spr_cspr_low_cc_y			C suppre Low-CC-Y parameter
@param[out]	rdma_cspr_low_cc_y_table	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* const rdma_cspr_low_cc_y_table );

/**
Set CSPR Low-CC-Y setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_cc_y			C suppre Low-CC-Y parameter
@param[out]	rdma_cspr_low_cc_y_table	C suppre Low-CC-Y parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_cc_y_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_y, TImCnrRdmaDataCsprLowCcYTbl* const rdma_cspr_low_cc_y_table );

/**
Set CSPR Low-CC-C setting parameter information for C for Off Line
@param[in]	spr_cspr_low_cc_c			C suppre Low-CC-C parameter
@param[out]	rdma_cspr_low_cc_c_table	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_low_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* const rdma_cspr_low_cc_c_table );

/**
Set CSPR Low-CC-C setting parameter information for C for On The Fly
@param[in]	spr_cspr_low_cc_c			C suppre Low-CC-C parameter
@param[out]	rdma_cspr_low_cc_c_table	C suppre Low-CC-C parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_low_cc_c_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_low_cc_c, TImCnrRdmaDataCsprLowCcCTbl* const rdma_cspr_low_cc_c_table );

/**
Set CSPR Edge setting parameter information for C for Off Line
@param[in]	spr_cspr_edge			C suppre Edge parameter
@param[out]	rdma_cspr_edge_table	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_edge_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_edge, TImCnrRdmaDataCsprEdgeTbl* const rdma_cspr_edge_table );

/**
Set CSPR Edge setting parameter information for C for On The Fly
@param[in]	spr_cspr_edge			C suppre Edge parameter
@param[out]	rdma_cspr_edge_table	C suppre Edge parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_edge_table(ImCnrSet*self, const TImCnrTable* const spr_cspr_edge, TImCnrRdmaDataCsprEdgeTbl* const rdma_cspr_edge_table );

/**
Set CSPR Hue Specified setting parameter information for C for Off Line
@param[in]	spr_cspr_hue			C suppre Hue Specified parameter
@param[out]	rdma_cspr_hue_table		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_hue_spec_table(ImCnrSet*self, const TImCnrHueSpecTable* const spr_cspr_hue, TImCnrRdmaDataCsprHueTbl* const rdma_cspr_hue_table );

/**
Set CSPR Hue Specified setting parameter information for C for On The Fly
@param[in]	spr_cspr_hue			C suppre Hue Specified parameter
@param[out]	rdma_cspr_hue_table		C suppre Hue Specified parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_hue_spec_table(ImCnrSet*self, const TImCnrHueSpecTable* const spr_cspr_hue, TImCnrRdmaDataCsprHueTbl* const rdma_cspr_hue_table );

/**
Set CSPR sprs setting parameter information for C for Off Line
@param[in]	cspr_sprs_cc			C suppre sprs CC parameter
@param[out]	rdma_cspr_sprs_cc		C suppre sprs CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_sprs_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprs_cc, TImCnrRdmaDataSprsCcTbl* const rdma_cspr_sprs_cc );

/**
Set CSPR sprs setting parameter information for C for On The Fly
@param[in]	cspr_sprs_cc			C suppre sprs CC parameter
@param[out]	rdma_cspr_sprs_cc		C suppre sprs CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_sprs_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprs_cc, TImCnrRdmaDataSprsCcTbl* const rdma_cspr_sprs_cc );

/**
Set CSPR sprd setting parameter information for C for Off Line
@param[in]	cspr_sprd_cc			C suppre sprd CC parameter
@param[out]	rdma_cspr_sprd_cc		C suppre sprd CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_cspr_sprd_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprd_cc, TImCnrRdmaDataSprdCcTbl* const rdma_cspr_sprd_cc );

/**
Set CSPR sprd setting parameter information for C for On The Fly
@param[in]	cspr_sprd_cc			C suppre sprd CC parameter
@param[out]	rdma_cspr_sprd_cc		C suppre sprd CC parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_otf_cspr_sprd_cc_table(ImCnrSet*self, const TImCnrCtrlCcSrcDst* const cspr_sprd_cc, TImCnrRdmaDataSprdCcTbl* const rdma_cspr_sprd_cc );

/**
Set SPR table setting parameter information for Y for Off Line
@param[in]	yspr_table		Y suppre table parameter
@param[out]	rdma_yspr_table	Y suppre table parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_yspr_table(ImCnrSet*self, const TImCnrTable* const yspr_table, TImCnrRdmaDataOflYsprTbl* const rdma_yspr_table );

/**
Set SPR setting parameter information for Y for Off Line
@param[in]	spr_ctrl_y		Y suppre parameter
@param[out]	rdma_ctrl_y		Y suppre parameter for RDMA
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
INT32 im_cnr_set_rdma_value_ofl_ctrl_y(ImCnrSet*self, const TImCnrOflCtrlY* const spr_ctrl_y, TImCnrRdmaDataOflCtrlY* const rdma_ctrl_y );

#endif

#ifdef __cplusplus
}
#endif

#endif//_IM_CNR_SET_H_
