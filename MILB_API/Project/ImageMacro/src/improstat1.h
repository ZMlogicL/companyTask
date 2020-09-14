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


#ifndef  __IM_PRO_STAT1_H__
#define __IM_PRO_STAT1_H__


#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_PRO_STAT1							(im_pro_stat1_get_type ())
#define IM_PRO_STAT1(obj)								(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_PRO_STAT1, ImProStat1))
#define IM_PRO_STAT1_CLASS(klass)				(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_PRO_STAT1, ImProStat1Class))
#define IM_IS_PRO_STAT1(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_PRO_STAT1))
#define IM_IS_PRO_STAT1_CLASS(klass)		    (G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_PRO_STAT1))
#define IM_PRO_STAT1_GET_CLASS(obj)			(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_PRO_STAT1, ImProStat1Class))


struct 				   _ImProStat1;
typedef struct _ImProStat1 							ImProStat1;
typedef struct _ImProStat1Class 					ImProStat1Class;
typedef struct _ImProStat1Private 					ImProStat1Private;

struct _ImProStat1{
	GObject parent;
};

struct _ImProStat1Class{
	GObjectClass parentclass;
};


#ifdef __cplusplus
	extern "c1" {
#endif

GType 						im_pro_stat1_get_type(void) G_GNUC_CONST;
ImProStat1* 			im_pro_stat1_new(void);

/**
A setup of enable access to the built-in RAM of AF.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
			value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32 im_pro_stat1_af_set_paen(ImProStat1 *self, E_IM_PRO_AF_CH ch, UCHAR paenTrg );


/**
Set AF Global Window
@param[in]	ch : Channel No.
@param[in]	globalWin :AF global area information<br>
							value range :pos_x[0 - 8190](Multiples of 2)<br>
							target registor :@@AFGH<br>
							value range :pos_y[0 - 16382](Multiples of 2)<br>
							target registor :@@AFGV<br>
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
							value range :width[2 - 2496] 2pixel boundary<br>
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
							value range :width[2 - 2900] 2pixel boundary<br>
// --- REMOVE_ES3_HARDWARE END --
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
							target registor :@@AFGHW<br>
							value range :lines[2 - 16382] 2pixel boundary<br>
							target registor :@@AFGVW<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@attention	None
*/
extern	INT32 im_pro_stat1_af_set_global_area(ImProStat1 *self, E_IM_PRO_AF_CH ch, T_IM_PRO_AREA_INFO* globalWin );

/**
AF Surface color Information
@param[in]	ch : Channel No.
@param[in]	unitNo	:				Evaluated value calculation unit number. See @ref E_IM_PRO_AF_EVAL_CALC_UNIT<br>
@param[in]	afEvalCalcCtrl	:	Evaluated value calculation unit Information. See @ref T_IM_PRO_AF_EVAL_CALC_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat1_af_ctrl_eval_calc(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_EVAL_CALC_UNIT unitNo,
		T_IM_PRO_AF_EVAL_CALC_CTRL* afEvalCalcCtrl );

/**
AF Vertical detection Information
@param[in]	ch : Channel No.
@param[in]	afVerticalCtrl	:	Vertical detection Information See @ref T_IM_PRO_AF_VERTICAL_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat1_af_ctrl_vertical(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		T_IM_PRO_AF_VERTICAL_CTRL* afVerticalCtrl );


/**
AF Horizontal detection Information
@param[in]	ch : Channel No.
@param[in]	tapNo	:			Horizontal detection TAP number See @ref E_IM_PRO_AF_TAP<br>
@param[in]	afHorizonCtrl	:	Horizontal detection Information See @ref T_IM_PRO_AF_HORIZON_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat1_af_ctrl_horizon(ImProStat1 *self, E_IM_PRO_AF_CH ch, E_IM_PRO_AF_TAP tapNo,
		T_IM_PRO_AF_HORIZON_CTRL* afHorizonCtrl );

/**
AF Window Information Setting
@param[in]	ch : Channel No.
@param[in]	winNo		:	Window No. See @ref E_IM_PRO_AF_WINDOW_NO
@param[in]	afWinCtrl	:	Window Information See @ref T_IM_PRO_AF_WIN_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat1_af_ctrl_win(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo,
		T_IM_PRO_AF_WIN_CTRL* afWinCtrl );

/**
Get AF evaluated calculation Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_eval_calc_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Bright block Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_bright_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Dark block Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_dark_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Horizontal Detection 0 Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The AF Horizontal 0 data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal0_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Horizontal Detection 1 Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The AF Horizontal 1 data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal1_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Horizontal Detection 2 Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The AF Horizontal 2 data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal2_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Vertical Detection Data
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The AF Vertical data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_vertical_data(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result maximum evaluated calculation value AF detection window
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The maximum color value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_max_eval_calc_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result minimum evaluated calculation value AF detection window
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The minimum color value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_min_eval_calc_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result maximum assessment value AF detection window
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_max_assess_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result minimum assessment value AF detection window
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The minimum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_min_assess_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Detection Window Horizontal0 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal0_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Detection Window Horizontal1 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal1_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Detection Window Horizontal2 Detection Each Line Maximum Value Accumulation result.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal2_line_accum_max_value(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF evaluated calculation Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF evaluated calculation Bright block Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_bright_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF evaluated calculation Dark block Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_dark_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );


/**
Get AF Horizontal 0 Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal0_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Horizontal 1 Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal1_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Horizontal 2 Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal2_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Vertical Data for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG brightness data address pointer
@remarks	The brightness data is acquired.
*/
extern	ULONG im_pro_stat1_af_get_vertical_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );


/**
Get As a result maximum evaluated calculation value AF detection window for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The maximum color value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_max_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result minimum evaluated calculation value AF detection window for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The minimum color value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_min_eval_calc_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result maximum assessment value AF detection window for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_max_assess_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get As a result minimum assessment value AF detection window for AFE long exposure
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The minimum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_min_assess_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );


/**
Get AF Detection Window Horizontal0 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal0_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Detection Window Horizontal1 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal1_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );

/**
Get AF Detection Window Horizontal2 Detection Each Line Maximum Value Accumulation result for AFE long exposure.
@param[in]	ch : Channel No.
@param[in]	winNo	:	Window Number( AF0 - 14 )
@retval		ULONG* data address pointer
@remarks	The maximum assessment value is acquired.
*/
extern	ULONG im_pro_stat1_af_get_horizontal2_line_accum_max_lastdata(ImProStat1 *self, E_IM_PRO_AF_CH ch,
		E_IM_PRO_AF_WINDOW_NO winNo );


#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif /* __IM_PRO_STAT1_H__ */


