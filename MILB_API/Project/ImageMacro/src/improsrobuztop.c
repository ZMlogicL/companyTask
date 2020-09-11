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
#include "improbase.h"
#include"improsrobuztop.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSrobuztop, impro_srobuztop);
#define IMPRO_SROBUZTOP_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSrobuztopPrivate, IMPRO_TYPE_SROBUZTOP));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSrobuztopPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_srobuztop_constructor(ImproSrobuztop *self)
{
	ImproSrobuztopPrivate *priv = IMPRO_SROBUZTOP_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_srobuztop_destructor(ImproSrobuztop *self)
{
	ImproSrobuztopPrivate *priv = IMPRO_SROBUZTOP_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
// --- REMOVE_BUZ BEGIN
/** @addtogroup im_pro_sro_buztop BUZTOP
@{
*/
/**
Software reset of BUZTOP macro.
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_srobuztop_sr( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.buz.sr.bit.sr = D_IM_PRO_SR_RESET;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Software reset release of BUZTOP.
@param[in]	unitNo : Unit number.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_srobuztop_sr_rlease( E_IM_PRO_UNIT_NUM unitNo )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	// Dd_Top_Stop_Clock
	ioPro.imgPipe[unitNo].sro.buz.sr.bit.sr = D_IM_PRO_SR_RELEASE;
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/**
BUZTOP control data setting
@param[in]	unitNo : Unit number.
@param[in]	buzCtrl : BUZTOP control information
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_srobuztop_ctrl( E_IM_PRO_UNIT_NUM unitNo, TimproBuztopCtrl* buzCtrl )
{
#ifdef CO_PARAM_CHECK
	if (buzCtrl == NULL){
		Ddim_Assertion(("I:impro_srobuztop_ctrl error. buzCtrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrobuztop_D_IM_PRO_BUZ_BUZH_MIN, ImproSrobuztop_D_IM_PRO_BUZ_BUZH_MAX,
					buzCtrl->inPosX, "impro_srobuztop_ctrl : inPosX" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrobuztop_D_IM_PRO_BUZ_BUZV_MIN, ImproSrobuztop_D_IM_PRO_BUZ_BUZV_MAX,
					buzCtrl->inPosY, "impro_srobuztop_ctrl : inPosY" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrobuztop_D_IM_PRO_BUZ_BUZHW_MIN, ImproSrobuztop_D_IM_PRO_BUZ_BUZHW_MAX,
					buzCtrl->inWidth, "impro_srobuztop_ctrl : inWidth" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrobuztop_D_IM_PRO_BUZ_BUZVW_MIN, ImproSrobuztop_D_IM_PRO_BUZ_BUZVW_MAX,
					buzCtrl->inLines, "impro_srobuztop_ctrl : inLines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSrobuztop_D_IM_PRO_BUZ_BUZOHW_MIN, ImproSrobuztop_D_IM_PRO_BUZ_BUZOHW_MAX,
					buzCtrl->outWidth, "impro_srobuztop_ctrl : outWidth" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.buz.buzh.bit.buzh		= buzCtrl->inPosX;
	ioPro.imgPipe[unitNo].sro.buz.buzv.bit.buzv		= buzCtrl->inPosY;
	ioPro.imgPipe[unitNo].sro.buz.buzhw.bit.buzhw	= buzCtrl->inWidth;
	ioPro.imgPipe[unitNo].sro.buz.buzvw.bit.buzvw	= buzCtrl->inLines;
	ioPro.imgPipe[unitNo].sro.buz.buzohw.bit.buzohw	= buzCtrl->outWidth;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/**
A setup of enable access to the built-in RAM of BUZTOP.
@param[in]	unitNo : Unit number.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
INT32 impro_srobuztop_set_paen( E_IM_PRO_UNIT_NUM unitNo, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.imgPipe[unitNo].sro.srotop.brszsl.bit.brszsl != 0 ) ) {
		Ddim_Assertion(("I:impro_srobuztop_set_paen. Buz is not selected error.\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.buz.paen.bit.paen = paenTrg;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
A setup of Resizer select.
@param[in]	unitNo : Unit number.
@param[in]	sel     : Raw resizer select.
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
INT32 impro_srobuztop_set_resizer_sel( E_IM_PRO_UNIT_NUM unitNo, EimproBuztopSel sel )
{
	// Dd_Top_Start_Clock
	im_pro_on_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.srotop.brszsl.bit.brszsl = sel;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSrobuztop类的一个实例
 *
 */
ImproSrobuztop* 	impro_srobuztop_new()
{
	ImproSrobuztop* self = k_object_new_with_private(IMPRO_TYPE_SROBUZTOP,sizeof(ImproSrobuztopPrivate));
	ImproSrobuztopPrivate* priv = IMPRO_SROBUZTOP_GET_PRIVATE(self);
	
	e_warning_o(self," impro_srobuztop_new \n");
	return self;
}
