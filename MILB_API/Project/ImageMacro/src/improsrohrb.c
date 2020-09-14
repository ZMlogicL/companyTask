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


#include<stdint.h>
#include<string.h>
#include<math.h>
#include <klib.h>
#include"improsrohrb.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrohrb, impro_srohrb);
#define IMPRO_SROHRB_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrohrbPrivate, IMPRO_TYPE_SROHRB));


/*宏定义区域*/
/* HRB				*/
#define	ImproSrohrb_D_IM_SRO1_STATUS_HRB		((0x00000000UL)&(1<<15))
/* HRB				*/
#define	ImproSrohrb_D_IM_SRO2_STATUS_HRB		((0x10000000UL)&(1<<15))
/* Image Pipe1&2 HRB	*/
#define	ImproSrohrb_D_IM_SRO_STATUS_HRB_BOTH	( ImproSrohrb_D_IM_SRO1_STATUS_HRB	| ImproSrohrb_D_IM_SRO2_STATUS_HRB)
/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrohrbPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const UINT32	S_G_IM_PRO_HRB_STATUS_TBL[ImproBase_E_IM_PRO_UNIT_NUM_MAX] = {
	ImproSrohrb_D_IM_SRO1_STATUS_HRB,	ImproSrohrb_D_IM_SRO2_STATUS_HRB,	ImproSrohrb_D_IM_SRO_STATUS_HRB_BOTH,
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srohrb_constructor(ImproSrohrb *self)
{
	ImproSrohrbPrivate *priv = IMPRO_SROHRB_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srohrb_destructor(ImproSrohrb *self)
{
	ImproSrohrbPrivate *priv = IMPRO_SROHRB_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start HRB
@param[in]	unitNo : Unit number.
*/
VOID impro_srohrb_start( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(S_G_IM_PRO_HRB_STATUS_TBL[unitNo], 0);
}

/**
Stop HRB
@param[in]	unitNo : Unit number.
@param[in]	force : force stop option
*/
VOID impro_srohrb_stop( E_IM_PRO_UNIT_NUM unitNo, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(S_G_IM_PRO_HRB_STATUS_TBL[unitNo], 0);
}

/**
HRB control data setting
@param[in]	unitNo : Unit number.
@param[in]	hrbCtrl : HRB control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srohrbCtrl( E_IM_PRO_UNIT_NUM unitNo, TimproHrbCtrl* hrbCtrl )
{
#ifdef CO_PARAM_CHECK
	if (hrbCtrl == NULL){
		Ddim_Assertion(("I:impro_srohrbCtrl error. hrbCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBH_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBH_MAX,
			hrbCtrl->inPosX, "impro_srohrbCtrl : inPosX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBV_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBV_MAX,
			hrbCtrl->inPosY, "impro_srohrbCtrl : inPosY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBHW_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBHW_MAX,
			hrbCtrl->inWidth, "impro_srohrbCtrl : inWidth" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBVW_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBVW_MAX,
			hrbCtrl->inLines, "impro_srohrbCtrl : inLines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBOHW_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBOHW_MAX,
			hrbCtrl->outWidth, "impro_srohrbCtrl : outWidth" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBSCYC_MAX,
			hrbCtrl->cycle, "impro_srohrbCtrl : cycle" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MIN, ImproSrohrb_D_IM_PRO_HRB_HRBOSM_MAX,
			hrbCtrl->outTiming, "impro_srohrbCtrl : outTiming" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.hrb.hrbh.bit.hrbh				= hrbCtrl->inPosX;
	ioPro.imgPipe[unitNo].sro.hrb.hrbv.bit.hrbv				= hrbCtrl->inPosY;
	ioPro.imgPipe[unitNo].sro.hrb.hrbhw.bit.hrbhw			= hrbCtrl->inWidth;
	ioPro.imgPipe[unitNo].sro.hrb.hrbvw.bit.hrbvw			= hrbCtrl->inLines;
	ioPro.imgPipe[unitNo].sro.hrb.hrbohw.bit.hrbohw			= hrbCtrl->outWidth;
	ioPro.imgPipe[unitNo].sro.hrb.hrbscyc.bit.hrbscyc		= hrbCtrl->cycle;
	ioPro.imgPipe[unitNo].sro.hrb.hrbosm.bit.hrbosm			= hrbCtrl->outTiming;

	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk00	= hrbCtrl->coefficient[ 0][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk1.bit.hrbk01	= hrbCtrl->coefficient[ 0][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk02	= hrbCtrl->coefficient[ 0][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk2.bit.hrbk03	= hrbCtrl->coefficient[ 0][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk04	= hrbCtrl->coefficient[ 0][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk3.bit.hrbk10	= hrbCtrl->coefficient[ 1][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk11	= hrbCtrl->coefficient[ 1][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk4.bit.hrbk12	= hrbCtrl->coefficient[ 1][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk13	= hrbCtrl->coefficient[ 1][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk5.bit.hrbk14	= hrbCtrl->coefficient[ 1][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk20	= hrbCtrl->coefficient[ 2][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk6.bit.hrbk21	= hrbCtrl->coefficient[ 2][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk22	= hrbCtrl->coefficient[ 2][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk7.bit.hrbk23	= hrbCtrl->coefficient[ 2][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk24	= hrbCtrl->coefficient[ 2][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk8.bit.hrbk30	= hrbCtrl->coefficient[ 3][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk31	= hrbCtrl->coefficient[ 3][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk9.bit.hrbk32	= hrbCtrl->coefficient[ 3][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk33	= hrbCtrl->coefficient[ 3][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk10.bit.hrbk34	= hrbCtrl->coefficient[ 3][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk40	= hrbCtrl->coefficient[ 4][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk11.bit.hrbk41	= hrbCtrl->coefficient[ 4][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk42	= hrbCtrl->coefficient[ 4][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk12.bit.hrbk43	= hrbCtrl->coefficient[ 4][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk44	= hrbCtrl->coefficient[ 4][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk13.bit.hrbk50	= hrbCtrl->coefficient[ 5][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk51	= hrbCtrl->coefficient[ 5][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk14.bit.hrbk52	= hrbCtrl->coefficient[ 5][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk53	= hrbCtrl->coefficient[ 5][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk15.bit.hrbk54	= hrbCtrl->coefficient[ 5][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk60	= hrbCtrl->coefficient[ 6][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk16.bit.hrbk61	= hrbCtrl->coefficient[ 6][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk62	= hrbCtrl->coefficient[ 6][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk17.bit.hrbk63	= hrbCtrl->coefficient[ 6][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk64	= hrbCtrl->coefficient[ 6][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk18.bit.hrbk70	= hrbCtrl->coefficient[ 7][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk71	= hrbCtrl->coefficient[ 7][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk19.bit.hrbk72	= hrbCtrl->coefficient[ 7][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk73	= hrbCtrl->coefficient[ 7][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk20.bit.hrbk74	= hrbCtrl->coefficient[ 7][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk80	= hrbCtrl->coefficient[ 8][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk21.bit.hrbk81	= hrbCtrl->coefficient[ 8][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk82	= hrbCtrl->coefficient[ 8][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk22.bit.hrbk83	= hrbCtrl->coefficient[ 8][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk84	= hrbCtrl->coefficient[ 8][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk23.bit.hrbk90	= hrbCtrl->coefficient[ 9][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk91	= hrbCtrl->coefficient[ 9][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk24.bit.hrbk92	= hrbCtrl->coefficient[ 9][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk93	= hrbCtrl->coefficient[ 9][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk25.bit.hrbk94  = hrbCtrl->coefficient[ 9][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk100    = hrbCtrl->coefficient[10][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk26.bit.hrbk101	= hrbCtrl->coefficient[10][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk102	= hrbCtrl->coefficient[10][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk27.bit.hrbk103	= hrbCtrl->coefficient[10][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk104	= hrbCtrl->coefficient[10][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk28.bit.hrbk110	= hrbCtrl->coefficient[11][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk111	= hrbCtrl->coefficient[11][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk29.bit.hrbk112	= hrbCtrl->coefficient[11][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk113	= hrbCtrl->coefficient[11][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk30.bit.hrbk114	= hrbCtrl->coefficient[11][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk120	= hrbCtrl->coefficient[12][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk31.bit.hrbk121	= hrbCtrl->coefficient[12][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk122	= hrbCtrl->coefficient[12][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk32.bit.hrbk123	= hrbCtrl->coefficient[12][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk124	= hrbCtrl->coefficient[12][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk33.bit.hrbk130	= hrbCtrl->coefficient[13][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk131	= hrbCtrl->coefficient[13][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk34.bit.hrbk132	= hrbCtrl->coefficient[13][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk133	= hrbCtrl->coefficient[13][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk35.bit.hrbk134	= hrbCtrl->coefficient[13][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk140	= hrbCtrl->coefficient[14][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk36.bit.hrbk141	= hrbCtrl->coefficient[14][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk142	= hrbCtrl->coefficient[14][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk37.bit.hrbk143	= hrbCtrl->coefficient[14][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk144	= hrbCtrl->coefficient[14][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk38.bit.hrbk150	= hrbCtrl->coefficient[15][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk151	= hrbCtrl->coefficient[15][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk39.bit.hrbk152	= hrbCtrl->coefficient[15][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk153	= hrbCtrl->coefficient[15][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk40.bit.hrbk154	= hrbCtrl->coefficient[15][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk160	= hrbCtrl->coefficient[16][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk41.bit.hrbk161	= hrbCtrl->coefficient[16][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk162	= hrbCtrl->coefficient[16][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk42.bit.hrbk163	= hrbCtrl->coefficient[16][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk164	= hrbCtrl->coefficient[16][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk43.bit.hrbk170	= hrbCtrl->coefficient[17][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk171	= hrbCtrl->coefficient[17][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk44.bit.hrbk172	= hrbCtrl->coefficient[17][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk173	= hrbCtrl->coefficient[17][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk45.bit.hrbk174	= hrbCtrl->coefficient[17][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk180	= hrbCtrl->coefficient[18][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk46.bit.hrbk181	= hrbCtrl->coefficient[18][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk182	= hrbCtrl->coefficient[18][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk47.bit.hrbk183	= hrbCtrl->coefficient[18][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk184	= hrbCtrl->coefficient[18][4];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk48.bit.hrbk190	= hrbCtrl->coefficient[19][0];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk191	= hrbCtrl->coefficient[19][1];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk49.bit.hrbk192	= hrbCtrl->coefficient[19][2];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk193    = hrbCtrl->coefficient[19][3];
	ioPro.imgPipe[unitNo].sro.hrb.hrbk.hrbk50.bit.hrbk194    = hrbCtrl->coefficient[19][4];
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of hrb.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srohrb_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.hrb.hrbtrg.bit.hrbtrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_srohrb_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.hrb.HRBPAEN.bit.PAEN = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrohrb类的一个实例
 *
 */
ImproSrohrb* 	impro_srohrb_new()
{
	ImproSrohrb* self = k_object_new_with_private(IMPRO_TYPE_SROHRB,sizeof(ImproSrohrbPrivate));
	ImproSrohrbPrivate* priv = IMPRO_SROHRB_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srohrb_new \n");
	return self;
}
