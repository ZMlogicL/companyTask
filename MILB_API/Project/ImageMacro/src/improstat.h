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


#ifndef  __IM_PRO_STAT_H__
#define __IM_PRO_STAT_H__


#include <glib-object.h>


G_BEGIN_DECLS


#define IM_TYPE_PRO_STAT							(im_pro_stat_get_type ())
#define IM_PRO_STAT(obj)							(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_PRO_STAT, ImProStat))
#define IM_PRO_STAT_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_PRO_STAT, ImProStatClass))
#define IM_IS_PRO_STAT(obj)						(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_PRO_STAT))
#define IM_IS_PRO_STAT_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_PRO_STAT))
#define IM_PRO_STAT_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_PRO_STAT, ImProStatClass))


struct 				   _ImProStat;
typedef struct _ImProStat 							ImProStat;
typedef struct _ImProStatClass 					ImProStatClass;
typedef struct _ImProStatPrivate 				ImProStatPrivate;

struct _ImProStat{
	GObject parent;
};

struct _ImProStatClass{
	GObjectClass parentclass;
};


GType 						im_pro_stat_get_type(void) G_GNUC_CONST;
ImProStat* 				im_pro_stat_new(void);

/**
STATTOP Macro initialize
@remarks	Please Call at the time of system starting.
*/
extern	VOID im_pro_stat_stattop_init( ImProStat *self );

/**
STATTOP Macro software reset
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: All macro not stopped NG
*/
extern	INT32 im_pro_stat_stattop_sw_reset( ImProStat *self );

/**
STATTOP Macro clock control
@param[in]	clkType	: STATTOP Macro clock type
@param[in]	onOff		: 0:clock on 1:clock off
@param[in]	waitSkip	: 0:non wait 1:wait 1ms. for wait PROCLK/CDK 5 cycle.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_stattop_control_clock(ImProStat *self, E_IM_PRO_STATTOP_CLK_TYPE clkType,
		UCHAR onOff, UCHAR waitSkip );

/**
STATTOP macro control data setting
@param[in]	ctrl : STATTOP macro control information structure
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_stattop_ctrl(ImProStat *self, T_IM_PRO_STATTOP_CTRL* ctrl );

/** @addtogroup im_pro_stat_aeawb AEAWB
@{
*/
/**
AEAWB macro start
@param[in]	ch : Channel No.
@retval		D_DDIM_OK				: Processing OK
@retval		D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
extern	INT32 im_pro_stat_aeawb_start(ImProStat *self, E_IM_PRO_AEAWB_CH ch );

/**
AEAWB macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
extern	INT32 im_pro_stat_aeawb_stop(ImProStat *self, E_IM_PRO_AEAWB_CH ch, UCHAR force );

/**
AE/AWB data SDRAM write enable set
@param[in]	ch : Channel No.
@param[in]	aeawbCtrl : AEAWB Information @ref T_IM_PRO_AEAWB_CTRL
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawbCtrl(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CTRL* aeawbCtrl );

/**
A setup of enable access to the built-in RAM of AEAWB.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32 im_pro_stat_aeawb_set_paen(ImProStat *self, E_IM_PRO_AEAWB_CH ch, UCHAR paenTrg );

/**
AWB detect data format select.
@param[in]	ch : Channel No.
@param[in]	awbFormat : AWB detect data format @ref E_IM_PRO_AWB_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_awbdataformat(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AWB_MODE awbFormat );

/**
AE/AWB detecting mode set
@param[in]	ch : Channel No.
@param[in]	wbMode : AEAWB Detecting mode @ref E_IM_PRO_AEAWB_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_wd_mode(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AEAWB_MODE wbMode );

/**
AE/AWB detecting window mode set
@param[in]	ch : Channel No.
@param[in]	wbWinMode : AEAWB Detecting window mode @ref E_IM_PRO_AEAWB_WD_WINDOW_MODE
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_wd_window_mode(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		E_IM_PRO_AEAWB_WD_WINDOW_MODE wbWinMode );

/**
Set AE/AWB Window size
@param[in]	ch : Channel No.
@param[in]	aeawbArea :aeawb window information.

@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_area(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_AREA* aeawbArea );

/**
Set AE/AWB Window block number
@param[in]	ch : Channel No.
@param[in]	hBcNum :horizontal AEAWB Window block number<br>
						value range  :[1 - 64]<br>
						target registor  :@@AEHBC<br>
						Note that if level WB is enabled (aeawbMode=E_IM_PRO_AEAWB_MODE_LWB~E_IM_PRO_AEAWB_MODE_AE_AWB_LWB),
						the upper limit of this register is 32.

@param[in]	vBcNum :vertical AEAWB Window block number<br>
					  value range  :[1 - 64]<br>
					  target registor  :@@AEVBC
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32	im_pro_stat_aeawb_set_blocks(ImProStat *self, E_IM_PRO_AEAWB_CH ch, USHORT hBcNum, USHORT vBcNum );

/**
Set calculation permission in AE/AWB Window block.
@param[in]	ch : Channel No.
@param[in]	aeawbCw :AE/AWB Addition permission size in a block information<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_cw(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_CW* aeawbCw );

/**
AWB RGB level gate threshold
@param[in]	ch : Channel No.
@param[in]	lvGate	:	AWB RGB gate threshold
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_lv_gate(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_LV_GATE* lvGate );

/**
AWB matrix level gate threshold
@param[in]	ch : Channel No.
@param[in]	mtLvGate	:AWB Matrix gate
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_matrix_lv_gate(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		T_IM_PRO_AEAWB_MATRIX_LV_GATE* mtLvGate );

/**
AE Y coefficient
@param[in]	ch : Channel No.
@param[in]	aeyk	:Luminosity generation coefficient Information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_aeyk(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeyk );

/**
Get Luminance generation coefficient.
@param[in]	ch : Channel No.
@param[out]	aeyk	:Luminosity generation coefficient Information
@retval		Luminance generation coefficient.
*/
extern	INT32	im_pro_stat_aeawb_get_aeyk(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_STAT_YK* aeyk );

/**
Luminosity is integrated from the specified line in the AEAWB detection Window
@param[in]	ch : Channel No.
@param[in]	lineInfo
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_set_lineData_position(ImProStat *self, E_IM_PRO_AEAWB_CH ch,
		T_IM_PRO_AEAWB_LINE_INFO* lineInfo );

/**
Get flicker result line data. Result is ULONG [4] address.
@param[in]	ch : Channel No.
@param[out]	lineData	:line data Result of ULONG [4].
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_get_lineData(ImProStat *self, E_IM_PRO_AEAWB_CH ch, ULONG* lineData );

/**
Get AE Data
@param[in]	ch : Channel No.
@retval		AE Data Address	:	AE Data Storing Area Address
*/
extern	ULONG im_pro_stat_aeawb_get_aeawbdata(ImProStat *self, E_IM_PRO_AEAWB_CH ch );

/**
Get AE Data last VD for AFE long exposure
@param[in]	ch : Channel No.
@retval		ULONG AE Data Storing Area Address for AFE long exposure
*/
extern	ULONG im_pro_stat_aeawb_get_lastaeawbdata(ImProStat *self, E_IM_PRO_AEAWB_CH ch );

/**
Get Wave Detection Data information
@param[in]	ch : Channel No.
@param[out]	wdInfo : Wave Detection Data information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_aeawb_get_wdInfo(ImProStat *self, E_IM_PRO_AEAWB_CH ch, T_IM_PRO_AEAWB_WD_INFO* wdInfo );

/** @addtogroup im_pro_stat_af AF
@{
*/
/**
AF macro start
@param[in]	ch : Channel No.
*/
extern	VOID im_pro_stat_af_start(ImProStat *self, E_IM_PRO_AF_CH ch );


/**
AF macro stop
@param[in]	ch : Channel No.
@param[in]	force : force stop option
*/
extern	VOID im_pro_stat_af_stop(ImProStat *self, E_IM_PRO_AF_CH ch, UCHAR force );

/**
AF Information Setting
@param[in]	ch : Channel No.
@param[in]	afCtrl	:	Window Information See @ref T_IM_PRO_AF_CTRL<br>
@retval		D_DDIM_OK						: Setting OK
@retval		D_IM_PRO_AF_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32 im_pro_stat_afctrl(ImProStat *self, E_IM_PRO_AF_CH ch, T_IM_PRO_AF_CTRL* afCtrl );


G_END_DECLS


#endif /* __IM_PRO_STAT2_H__ */
