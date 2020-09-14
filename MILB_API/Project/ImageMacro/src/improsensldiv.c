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
#include"improsensldiv.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSensldiv, impro_sensldiv);
#define IMPRO_SENSLDIV_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSensldivPrivate, IMPRO_TYPE_SENSLDIV));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSensldivPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const USHORT gim_pro_maximum_size_ldiv[ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_3 + 1]
                                           [ImproBase_E_IM_PRO_LDIV_CH_3 + 1] = {
	{2960,	2960,	2960,	2960},
	{5920,	5920,	0,		1024},
	{11840,	0,		0,		1024},
	{0,		0,		0,		0	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sensldiv_constructor(ImproSensldiv *self)
{
	ImproSensldivPrivate *priv = IMPRO_SENSLDIV_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sensldiv_destructor(ImproSensldiv *self)
{
	ImproSensldivPrivate *priv = IMPRO_SENSLDIV_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
LDIV macro start.
@param[in]	ch : Channel No.
*/
INT32 impro_sensldiv_start( EimproLdivCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	// check called of the other macro
	ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg	= D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_LDIV0, ch);

	return D_DDIM_OK;
}

/**
Stop LDIV information
@param[in]	ch : Channel No.
@param[in]	force : force stop option
*/
INT32 impro_sensldiv_stop( EimproLdivCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg	= D_IM_PRO_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg	= D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_LDIV0, ch);

	return D_DDIM_OK;
}

/**
LDIV macro control parameter is set.
@param[in]	ch : Channel No.
@param[in]	ldivCtrl : LDIV control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sensldiv_ctrl( EimproLdivCh ch, TimproLdivCtrl* ldivCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ldivCtrl == NULL){
		Ddim_Assertion(("I:impro_sensldiv_ctrl error. ch=%d ldivCtrl=NULL\n", ch));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.ldiv[ch].ldivctl.bit.ldstmd	= ldivCtrl->mode;
	ioPro.sen.ldiv[ch].ldivctl.bit.ldipmd	= ldivCtrl->ldipmd;
	ioPro.sen.ldiv[ch].ldivctl.bit.ldvdmd	= ldivCtrl->ldvdmd;
	ioPro.sen.ldiv[ch].ldivctl.bit.ldhdmd	= ldivCtrl->hdInsertionEn;
	ioPro.sen.ldiv[ch].ldivctl.bit.ldmch	= ldivCtrl->ldmch;
	ioPro.sen.ldiv[ch].ldivctl.bit.lddivmd	= ldivCtrl->lddivmd;
	ioPro.sen.ldiv[ch].ldivctl.bit.ldopmd	= ldivCtrl->ldopmd;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The area for Top OB detection is set up.
@param[in]	ch : Channel No.
@param[in]	ldivArea	:The area of LDIV processing. See @ref TimproLdivArea.
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_sensldiv_set_area( EimproLdivCh ch, TimproLdivArea* ldivArea )
{
#ifdef CO_PARAM_CHECK
	if (ldivArea == NULL){
		Ddim_Assertion(("I:impro_sensldiv_set_area error. ch=%d ldivArea=NULL\n", ch));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ldivArea->inWidth > gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1
	                 .sentopctl13.bit.ldivramsw][ch] ) {
		Ddim_Assertion(("I:impro_sensldiv_set_area. inputSize value over!! limit value:%u (%u)\n",
				gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ,
				ldivArea->inWidth ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ( ldivArea->outPosX[0] + ldivArea->outWidth[0] ) > gim_pro_maximum_size_ldiv[IoPro
	              .sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ) {
		Ddim_Assertion(("I:impro_sensldiv_set_area. outPosX[0] + outWidth[0] value over!! limit value:%u (%u + %u)\n",
				gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ,
				ldivArea->outPosX[0], ldivArea->outWidth[0] ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ( ldivArea->outPosX[1] + ldivArea->outWidth[1] ) > gim_pro_maximum_size_ldiv[ioPro.
	              sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ) {
		Ddim_Assertion(("I:impro_sensldiv_set_area. outPosX[1] + outWidth[1] value over!! limit value:%u (%u + %u)\n",
				gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ,
				ldivArea->outPosX[0], ldivArea->outWidth[0] ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ( ldivArea->outPosX[2] + ldivArea->outWidth[2] ) > gim_pro_maximum_size_ldiv[ioPro.
	              sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ) {
		Ddim_Assertion(("I:impro_sensldiv_set_area. outPosX[2] + outWidth[2] value over!! limit value:%u (%u + %u)\n",
				gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ,
				ldivArea->outPosX[0], ldivArea->outWidth[0] ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ( ldivArea->outPosX[3] + ldivArea->outWidth[3] ) > gim_pro_maximum_size_ldiv[ioPro.
	              sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ) {
		Ddim_Assertion(("I:impro_sensldiv_set_area. outPosX[3] + outWidth[3] value over!! limit value:%u (%u + %u)\n",
				gim_pro_maximum_size_ldiv[ioPro.sen.sentop.sentopctl1.sentopctl13.bit.ldivramsw][ch] ,
				ldivArea->outPosX[0], ldivArea->outWidth[0] ));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.ldiv[ch].ldivihw.bit.ldivihw				= ldivArea->inWidth;
	ioPro.sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh0		= ldivArea->outPosX[0];
	ioPro.sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh1		= ldivArea->outPosX[1];
	ioPro.sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh2		= ldivArea->outPosX[2];
	ioPro.sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh3		= ldivArea->outPosX[3];
	ioPro.sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw0	= ldivArea->outWidth[0];
	ioPro.sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw1	= ldivArea->outWidth[1];
	ioPro.sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw2	= ldivArea->outWidth[2];
	ioPro.sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw3	= ldivArea->outWidth[3];
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
A setup of enable access to the built-in RAM of LDIV.
@param[in]	ch : Channel No.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sensldiv_set_paen( EimproLdivCh ch, UCHAR paenTrg )
{
#ifdef CO_PARAM_CHECK
	if( ( paenTrg == 0 ) && ( ioPro.sen.ldiv[ch].ldivtrg.bit.ldivtrg != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:impro_sensldiv_set_paen. macro has not stopped error.\n"));
		return ImproBase_D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.ldiv[ch].ldivpaen.bit.ldpaen = paenTrg;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSensldiv类的一个实例
 *
 */
ImproSensldiv* 	impro_sensldiv_new()
{
	ImproSensldiv* self = k_object_new_with_private(IMPRO_TYPE_SENSLDIV,sizeof(ImproSensldivPrivate));
	ImproSensldivPrivate* priv = IMPRO_SENSLDIV_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sensldiv_new \n");
	return self;
}
