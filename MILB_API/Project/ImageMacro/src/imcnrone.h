/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#ifndef  __IM_CNRONE_H__
#define __IM_CNRONE_H__


#include "driver_common.h"
#include "ddim_typedef.h"
// get register value for RDMA
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"
#include "_jdscnr_otf_reg_rw.h"
#include "imcnr.h"
#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_CNRONE							(im_cnrone_get_type ())
#define IM_CNRONE(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_CNRONE, ImCnrone))
#define IM_CNRONE_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_CNRONE, ImCnroneClass))
#define IM_IS_CNRONE(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_CNRONE))
#define IM_IS_CNRONE_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_CNRONE))
#define IM_CNRONE_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_CNRONE, ImCnroneClass))


struct 				   _ImCnrone;
typedef struct _ImCnrone 							ImCnrone;
typedef struct _ImCnroneClass 					ImCnroneClass;
typedef struct _ImCnronePrivate 				ImCnronePrivate;

struct _ImCnrone{
	GObject parent;
};

struct _ImCnroneClass{
	GObjectClass parentclass;
};

#ifdef CO_DDIM_UTILITY_USE
/** CSPR Low CC Y Table (OTF/OFL)
data
*/

typedef struct _ImCnroneRdmaDataCsprLowCcYTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_lccsclof		LCCSCLOF;	/**< 2842_(1108 - 110Fh),	2842_(3108 - 310Fh) */
	struct io_cnr_cspr_reg_lccsclga	LCCSCLGA;	/**< 2842_(1110 - 1117h),	2842_(3110 - 3117h) */
	struct io_cnr_cspr_reg_lccsclbd	LCCSCLBD;	/**< 2842_(1118 - 111Fh),	2842_(3118 - 311Fh) */
} ImCnroneRdmaDataCsprLowCcYTbl;

/** CSPR Low CC C Table (OTF/OFL)
address
*/
typedef struct _ImCnroneRdmaAddrCsprLowCcCTbl{
	//						OTF							OFL
	ULONG	LCSSCLOF_1;		/**< 2842_(1128 - 112Bh),	2842_(3128 - 312Bh) */
	ULONG	LCSSCLOF_2;		/**< 2842_(112C - 112Fh),	2842_(312C - 312Fh) */
	ULONG	LCSSCLGA_1;		/**< 2842_(1130 - 1133h),	2842_(3130 - 3133h) */
	ULONG	LCSSCLGA_2;		/**< 2842_(1134 - 1137h),	2842_(3134 - 3137h) */
	ULONG	LCSSCLBD_1;		/**< 2842_(1138 - 1138h),	2842_(3138 - 3138h) */
	ULONG	LCSSCLBD_2;		/**< 2842_(113C - 113Fh),	2842_(313C - 313Fh) */
} ImCnroneRdmaAddrCsprLowCcCTbl;

/** CSPR Low CC C Table (OTF/OFL)
data
*/
typedef struct _ImCnroneRdmaDataCsprLowCcCTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_lcssclof	LCSSCLOF;	/**< 2842_(1128 - 112Fh),	2842_(3128 - 312Fh) */
	struct io_cnr_cspr_reg_lcssclga	LCSSCLGA;	/**< 2842_(1130 - 1137h),	2842_(3130 - 3137h) */
	struct io_cnr_cspr_reg_lcssclbd	LCSSCLBD;	/**< 2842_(1138 - 113Fh),	2842_(3138 - 313Fh) */
} ImCnroneRdmaDataCsprLowCcCTbl;

/** CSPR Edge Table (OTF/OFL)
address
*/
typedef struct _ImCnroneRdmaAddrCsprEdgeTbl{
	//						OTF							OFL
	ULONG	CESCLOF_1;		/**< 2842_(1168 - 116Bh),	2842_(3168 - 316Bh) */
	ULONG	CESCLOF_2;		/**< 2842_(116C - 116Fh),	2842_(316C - 316Fh) */
	ULONG	CESCLGA_1;		/**< 2842_(1170 - 1173h),	2842_(3170 - 3173h) */
	ULONG	CESCLGA_2;		/**< 2842_(1174 - 1177h),	2842_(3174 - 3177h) */
	ULONG	CESCLBD_1;		/**< 2842_(1178 - 1178h),	2842_(3178 - 3178h) */
	ULONG	CESCLBD_2;		/**< 2842_(117C - 117Fh),	2842_(317C - 317Fh) */
} ImCnroneRdmaAddrCsprEdgeTbl;

/** CSPR Edge Table (OTF/OFL)
data
*/
typedef struct _ImCnroneRdmaDataCsprEdgeTbl{
	//											OTF							OFL
	struct io_cnr_cspr_reg_cesclof	CESCLOF;	/**< 2842_(1168 - 116Fh),	2842_(3168 - 316Fh) */
	struct io_cnr_cspr_reg_cesclga	CESCLGA;	/**< 2842_(1170 - 1177h),	2842_(3170 - 3177h) */
	struct io_cnr_cspr_reg_cesclbd	CESCLBD;	/**< 2842_(1178 - 117Fh),	2842_(3178 - 317Fh) */
} ImCnroneRdmaDataCsprEdgeTbl;

/** CSPR_Hue_Specified (OTF/OFL)
address
*/
typedef struct _ImCnroneRdmaAddrCsprHueTbl{
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
} ImCnroneRdmaAddrCsprHueTbl;

/** CSPR_Hue_Specified (OTF/OFL)
data
*/
typedef struct _ImCnroneRdmaDataCsprHueTbl{
	//												OTF							OFL
	union	io_cnr_cspr_reg_cphpt		CPHPT;		/**< 2842_(1190 - 1193h),	2842_(3190 - 3193h) */
	union	io_cnr_cspr_reg_cphptk		CPHPTK;		/**< 2842_(1194 - 1197h),	2842_(3194 - 3197h) */
	struct	io_cnr_cspr_reg_cdsclof		CDSCLOF;	/**< 2842_(11A0 - 11ABh),	2842_(31A0 - 31ABh) */
	struct	io_cnr_cspr_reg_cdsclga		CDSCLGA;	/**< 2842_(11B0 - 11BBh),	2842_(31B0 - 31BBh) */
	struct	io_cnr_cspr_reg_cdsclbd		CDSCLBD;	/**< 2842_(11C0 - 11CBh),	2842_(31C0 - 31CBh) */
} ImCnroneRdmaDataCsprHueTbl;

/** SPRS (OTF/OFL)
address
*/
typedef struct _ImCnroneRdmaAddrSprsCcTbl{
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
} ImCnroneRdmaAddrSprsCcTbl;

/** SPRS (OTF/OFL)
data
*/
typedef struct _ImCnrRdmaDataSprsCcTbl{
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprs		SPRS;		/**< 2842_(1200 - 1203h),	2842_(3200 - 3203h) */
	struct	io_cnr_cspr_reg_sprscbof	SPRSCBOF;	/**< 2842_(1208 - 120Fh),	2842_(3208 - 320Fh) */
	struct	io_cnr_cspr_reg_sprscbga	SPRSCBGA;	/**< 2842_(1210 - 121Bh),	2842_(3210 - 321Bh) */
	struct	io_cnr_cspr_reg_sprscbbd	SPRSCBBD;	/**< 2842_(1220 - 1227h),	2842_(3220 - 3227h) */
	struct	io_cnr_cspr_reg_sprscrof	SPRSCROF;	/**< 2842_(1228 - 122Fh),	2842_(3228 - 322Fh) */
	struct	io_cnr_cspr_reg_sprscrga	SPRSCRGA;	/**< 2842_(1230 - 123Bh),	2842_(3230 - 323Bh) */
	struct	io_cnr_cspr_reg_sprscrbd	SPRSCRBD;	/**< 2842_(1240 - 1247h),	2842_(3240 - 3247h) */
} ImCnrRdmaDataSprsCcTbl;

/** SPRD (OTF/OFL)
address
*/
typedef struct _ImCnroneRdmaAddrSprdCcTbl{
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
} ImCnroneRdmaAddrSprdCcTbl;

/** SPRD (OTF/OFL)
data
*/
typedef struct _ImCnroneRdmaDataSprdCcTbl{
	//												OTF							OFL
	union	io_cnr_cspr_reg_sprd		SPRD;		/**< 2842_(1280 - 1283h),	2842_(3280 - 3283h) */
	struct	io_cnr_cspr_reg_sprdcbof	SPRDCBOF;	/**< 2842_(1288 - 128Fh),	2842_(3288 - 328Fh) */
	struct	io_cnr_cspr_reg_sprdcbga	SPRDCBGA;	/**< 2842_(1290 - 129Bh),	2842_(3290 - 329Bh) */
	struct	io_cnr_cspr_reg_sprdcbbd	SPRDCBBD;	/**< 2842_(12A0 - 12A7h),	2842_(32A0 - 32A7h) */
	struct	io_cnr_cspr_reg_sprdcrof	SPRDCROF;	/**< 2842_(12A8 - 12AFh),	2842_(32A8 - 32AFh) */
	struct	io_cnr_cspr_reg_sprdcrga	SPRDCRGA;	/**< 2842_(12B0 - 12BBh),	2842_(32B0 - 32BBh) */
	struct	io_cnr_cspr_reg_sprdcrbd	SPRDCRBD;	/**< 2842_(12C0 - 12C7h),	2842_(32C0 - 32C7h) */
} ImCnroneRdmaDataSprdCcTbl;

#endif

#ifdef __cplusplus
extern "C" {
#endif
//---------------------------- driver section ----------------------------


GType 						im_cnrone_get_type(void) G_GNUC_CONST;
ImCnrone* 				im_cnrone_new(void);
/**
@weakgroup im_cnr
@{
*/
/**
PCLK ON
@param [in]	ch				channel[0 - 1]
@remarks		For debugging use only (for register dump on debugger)
*/
extern	VOID im_cnrone_on_pclk(ImCnrone *self, UCHAR ch );

/**
PCLK OFF
@param [in]	ch				channel[0 - 1]
@remarks		For debugging use only (for register dump on debugger)
*/
extern	VOID im_cnrone_off_pclk(ImCnrone *self, UCHAR ch );

/**
The semaphore of SPR is acquired for Off Line
@param [in]	ch				channel[0 - 1]
@param[in]	tmOut		Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref D_DDIM_USER_SEM_WAIT_POL
							<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		ImCnr_SEM_NG					Lock Error (System Using designated channel number)
@retval		D_IM_CNR_TIMEOUT				Input Parameter Error
@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
extern	INT32 im_cnrone_ofl_open(ImCnrone *self, UCHAR ch, const INT32 tmOut );


/**
The semaphore of SPR is acquired for On The Fly
@param [in]	ch				channel[0 - 1]
@param[in]	tmOut		Time of timeout<br>
						<ul><li>Positive Value(Time of timeout)
							<li>@ref D_DDIM_USER_SEM_WAIT_POL
							<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@retval		ImCnr_SEM_NG					Lock Error (System Using designated channel number)
@retval		D_IM_CNR_TIMEOUT				Input Parameter Error
@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
extern	INT32 im_cnrone_otf_open(ImCnrone *self, UCHAR ch, const INT32 tmOut );

/**
Suppre Control for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCtrl
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre is set.
			Please call Y, C or both setting after this function if necessary.
*/
extern	INT32 im_cnrone_ofl_ctrl(ImCnrone *self, UCHAR ch, const ImCnrOflCtrl* const cnrCtrl );

/**
Suppre Control for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCtrl
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre is set.
			Please call Y, C or both setting after this function if necessary.
*/
extern	INT32 im_cnrone_otf_ctrl(ImCnrone *self, UCHAR ch, const ImCnrOtfCtrl* const cnrCtrl );

/**
Set Suppre output address information for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	addrInfo
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_otf_set_outaddr_info(ImCnrone *self, UCHAR ch, const ImCnrOtfOutaddrInfo* const addrInfo );

/**
Increment Suppre output address index for On The Fly
@param [in]	ch				channel[0 - 1]
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_otf_increment_outaddr_index(ImCnrone *self, UCHAR ch );

/**
Suppre Control set AXI bus I/F Control for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	axiCtrl	AXI bus I/F control parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_ofl_ctrl_Axi(ImCnrone *self, UCHAR ch, const ImCnrOflAxi* const axiCtrl );

/**
Suppre Control set AXI bus I/F Control for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	axiCtrl	AXI bus I/F control parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_otf_ctrl_axi(ImCnrone *self, UCHAR ch, const ImCnrOtfAxi* const axiCtrl );

/**
Get AXI bus I/F Status for Off Line
@param [in]	ch				channel[0 - 1]
@param[out]	sts	AXI bus I/F status parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_ofl_get_axi_status(ImCnrone *self, UCHAR ch, ImCnrOflAxiStatus* const sts );

/**
Get AXI bus I/F Status for On The Fly
@param [in]	ch				channel[0 - 1]
@param[out]	sts	AXI bus I/F status parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
*/
extern	INT32 im_cnrone_otf_get_axi_status(ImCnrone *self, UCHAR ch, ImCnrOtfAxiStatus* const sts );

/**
Set SPR setting for CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCtrlY	CbCr suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for CbCr is set.
*/
extern	INT32 im_cnrone_ofl_ctrl_c(ImCnrone *self, UCHAR ch, const ImCnrCtrlC* const cnrCtrlY );

/**
Set SPR setting for CbCr for On The Fly
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCtrlY	CbCr suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for CbCr is set.
*/
extern	INT32 im_cnrone_otf_ctrl_c(ImCnrone *self, UCHAR ch, const ImCnrCtrlC* const cnrCtrlY );

/**
Set SPR setting for Y for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCtrlY	Y suppre parameter
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	The calcurate mode of the Suppre for Y is set.
*/
extern	INT32 im_cnrone_ofl_ctrl_y(ImCnrone *self, UCHAR ch, const ImCnrOflCtrlY* const cnrCtrlY );

/**
Set SPR table for Y for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrYspr	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre YSPR table for Y is set.
*/
extern	INT32 im_cnrone_ofl_set_yspr_table(ImCnrone *self, UCHAR ch, const ImCnrTable* const cnrYspr );

/**
Set SPR Y table for Middle frequency CbCr for Off Line
@param [in]	ch				channel[0 - 2]
@param[in]	cnrCsprMidY	table value
@retval		D_DDIM_OK						Success
@retval		D_IM_CNR_INPUT_PARAMETER_ERROR	parameter error.
@remarks	Suppre CSPR Y table for CbCr is set.
*/
extern	INT32 im_cnrone_ofl_set_cspr_mid_y_table(ImCnrone *self, UCHAR ch, const ImCnrTable* const cnrCsprMidY );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif
