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


#ifndef  __IM_PRO_STAT2_H__
#define __IM_PRO_STAT2_H__


#include <glib-object.h>


G_BEGIN_DECLS


#ifdef __cplusplus
	extern "c1" {
#endif


#define IM_TYPE_PRO_STAT2							(im_pro_stat2_get_type ())
#define IM_PRO_STAT2(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_PRO_STAT2, ImProStat2))
#define IM_PRO_STAT2_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_PRO_STAT2, ImProStat2Class))
#define IM_IS_PRO_STAT2(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_PRO_STAT2))
#define IM_IS_PRO_STAT2_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_PRO_STAT2))
#define IM_PRO_STAT2_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_PRO_STAT2, ImProStat2Class))


struct 				   _ImProStat2;
typedef struct _ImProStat2 							ImProStat2;
typedef struct _ImProStat2Class 					ImProStat2Class;
typedef struct _ImProStat2Private 				ImProStat2Private;

struct _ImProStat2{
	GObject parent;
};

struct _ImProStat2Class{
	GObjectClass parentclass;
};


GType 						im_pro_stat2_get_type(void) G_GNUC_CONST;
ImProStat2* 			im_pro_stat2_new(void);

/** @addtogroup im_pro_stat_hist HIST
@{
*/
/**
HIST macro start
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
extern	INT32 im_pro_stat2_hist_start(ImProStat2 *self, E_IM_PRO_HIST_CH ch );

/**
HIST macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
extern	INT32 im_pro_stat2_hist_stop(ImProStat2 *self, E_IM_PRO_HIST_CH ch, UCHAR force );

/**
HIST detecting information set
@param[in]	ch : Channel No.
@param[in]	histCtrl : HIST Information @ref T_IM_PRO_HIST_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_ctrl(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_CTRL* histCtrl );

/**
A setup of enable access to the built-in RAM of HIST.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32 im_pro_stat2_hist_set_paen(ImProStat2 *self, E_IM_PRO_HIST_CH ch, UCHAR paenTrg );

/**
HIST detecting mode set
@param[in]	ch : Channel No.
@param[in]	histCycle : HIST horizontal subsampling cycle. @ref E_IM_PRO_HIST_CYCLE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_set_h_cycle(ImProStat2 *self, E_IM_PRO_HIST_CH ch, E_IM_PRO_HIST_CYCLE histCycle );

/**
Set HIST Window size
@param[in]	ch : Channel No.
@param[in]	histArea : HIST window information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_set_area(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_AREA* histArea );

/**
Set HIST Window size
@param[in]	ch : Channel No.
@param[in]	histGain : HIST window information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_set_gain(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_GAIN* histGain );

/**
HIST Y coefficient
@param[in]	ch : Channel No.
@param[in]	histyk	:Luminosity generation coefficient Information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_set_histyk(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_STAT_YK* histyk );

/**
Get HIST result Data
@param[in]	ch : Channel No.
@param[out]	histData :Histgram result value inside the HIST window.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_get_hist_data(ImProStat2 *self, E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_DATA* histData );

/**
Get HIST result RAM Data
@param[in]	ch : Channel No.
@param[out]	histRamData :Histgram result RAM value inside the HIST window.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_hist_get_hist_ram(ImProStat2 *self, E_IM_PRO_HIST_CH ch,
		T_IM_PRO_HIST_RAM_DATA* histRamData );

/** @addtogroup im_pro_stat_flck FLCK
@{
*/
/**
FLCK macro start
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
extern	INT32 im_pro_stat2_flck_start(ImProStat2 *self, E_IM_PRO_FLCK_CH ch );


/**
FLCK macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
extern	INT32 im_pro_stat2_flck_stop(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, UCHAR force );

/**
FLCK detecting information set
@param[in]	ch : Channel No.
@param[in]	flckCtrl : FLCK Information @ref T_IM_PRO_FLCK_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_ctrl(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_CTRL* flckCtrl );

/**
FLCK detect data format select.
@param[in]	ch : Channel No.
@param[in]	flckFormat : FLCK detect data format @ref E_IM_PRO_FLCK_TYPE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_flckdataformat(ImProStat2 *self, E_IM_PRO_FLCK_CH ch,
		E_IM_PRO_FLCK_TYPE flckFormat );

/**
FLCK detecting mode set
@param[in]	ch : Channel No.
@param[in]	flckMode : FLCK Detecting mode @ref E_IM_PRO_FLCK_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_wd_mode(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, E_IM_PRO_FLCK_MODE flckMode );

/**
Set FLCK Window size
@param[in]	ch : Channel No.
@param[in]	flckArea : flck window information<br>
						value range :[0 - 8190] 2pixel boundary<br>
						target registor :@@FLH<br>
						value range :[0 - 8190] 2pixel boundary<br>
						target registor :@@FLV<br>
						value range :[6 - 8192] 2pixel boundary<br>
						target registor :@@FLHW<br>
						value range :[2 - 1024] 2pixel boundary(FLWLMD=0)<br>
												4pixel boundary(FLWLMD=1)<br>
						target registor :@@FLVW<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_area(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_AREA* flckArea );

/**
Set FLCK Window block number
@param[in]	ch : Channel No.
@param[in]	bcNum :FLCK Window block number<br>
					value range :[1 - 4096]<br>
					target registor :@@FLBC<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_blocks(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, USHORT bcNum );

/**
Set calculation permission in FLCK Window block
@param[in]	ch : Channel No.
@param[in]	flcvw : FLCK Addition permission size in a block information<br>
					 value range :[2 - 1024] 2pixel boundary(FLWLMD=0)<br>
											 4pixel boundary(FLWLMD=1)<br>
					 target registor :@@FLCVW<br>

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_cw(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, USHORT flcvw );

/**
FLCK RGB level gate threshold
@param[in]	ch : Channel No.
@param[in]	lvGate	:	FLCK RGB gate threshold
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_lv_gate(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_FLCK_LV_GATE* lvGate );

/**
FLCK matrix level gate threshold
@param[in]	ch : Channel No.
@param[in]	mtLvGate	:FLCK Matrix gate
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_matrix_lv_gate(ImProStat2 *self, E_IM_PRO_FLCK_CH ch,
		T_IM_PRO_FLCK_MATRIX_LV_GATE* mtLvGate );

/**
FLCK Y coefficient
@param[in]	ch : Channel No.
@param[in]	flckyk	:Luminosity generation coefficient Information

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat2_flck_set_flyk(ImProStat2 *self, E_IM_PRO_FLCK_CH ch, T_IM_PRO_STAT_YK* flckyk );

/**
Get FLCK Data
@retval		FLCK Data Address	:	FLCK Data Storing Area Address
*/
extern	ULONG im_pro_stat2_flck_get_flckdata(ImProStat2 *self, E_IM_PRO_FLCK_CH ch );

/**
Get FLCK Last Data
@param[in]	ch : Channel No.
@retval		FLCK Data Address	:	FLCK Data Storing Area Address(Last address)
*/
extern	ULONG im_pro_stat2_flck_get_lastflckdata(ImProStat2 *self, E_IM_PRO_FLCK_CH ch );




#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_PRO_STAT2_H__ */


