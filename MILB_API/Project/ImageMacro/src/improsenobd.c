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
#include"improsenobd.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSenobd, impro_senobd);
#define IMPRO_SENOBD_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSenobdPrivate, IMPRO_TYPE_SENOBD));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSenobdPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_senobd_constructor(ImproSenobd *self)
{
	ImproSenobdPrivate *priv = IMPRO_SENOBD_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_senobd_destructor(ImproSenobd *self)
{
	ImproSenobdPrivate *priv = IMPRO_SENOBD_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start OBD
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobd_start( EimproObdCh ch )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_OBD00, ch);

	return D_DDIM_OK;
}

/**
Stop OBD
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobd_stop( EimproObdCh ch, UCHAR force )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.sen.obd[blockNum][chNum].obdtrg.bit.obdtrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_OBD00, ch);

	return D_DDIM_OK;
}

/**
The control parameter of OBD compensation is set.
@param[in]	ch : Channel No.
@param[in]	obCtrl	:	OBD Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobd_ctrl( EimproObdCh ch, TimproObdCtrl* obCtrl )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

#ifdef CO_PARAM_CHECK
	if (obCtrl == NULL){
		Ddim_Assertion(("I:impro_senobd_ctrl error. obCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdlthbit	= obCtrl->obMinValue;
	ioPro.sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdhthbit	= obCtrl->obMaxValue;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The area for OBD detection is set up.
@param[in]	ch : Channel No.
@param[in]	obArea	:The area for OB detection<br>
					value range :posX[0 - 12287]<br>
					target registor :@@OBDH<br>
					value range :posY[0 - 8191]<br>
					target registor :@@OBDV<br>
					value range :width[2 - 12288] 2pixel boundary<br>
					target registor :@@OBDHW<br>
					value range :lines[2 - 8192] 2pixel boundary<br>
					target registor :@@OBDVW<br>
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_senobd_set_area( EimproObdCh ch, TimproAreaInfo* obArea )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

#ifdef CO_PARAM_CHECK
	if (obArea == NULL){
		Ddim_Assertion(("I:impro_senobd_set_area error. obArea=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobd_D_IM_PRO_OBD_OBDH_MIN, ImproSenobd_D_IM_PRO_OBD_OBDH_MAX,
					obArea->posX , "impro_senobd_set_area : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobd_D_IM_PRO_OBD_OBDV_MIN, ImproSenobd_D_IM_PRO_OBD_OBDV_MAX,
					obArea->posY , "impro_senobd_set_area : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobd_D_IM_PRO_OBD_OBDHW_MIN, ImproSenobd_D_IM_PRO_OBD_OBDHW_MAX,
					obArea->width , "impro_senobd_set_area : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobd_D_IM_PRO_OBD_OBDVW_MIN, ImproSenobd_D_IM_PRO_OBD_OBDVW_MAX,
					obArea->lines , "impro_senobd_set_area : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obd[blockNum][chNum].obdcore.obdh.bit.obdh		= obArea->posX;
	ioPro.sen.obd[blockNum][chNum].obdcore.obdv.bit.obdv		= obArea->posY;
	ioPro.sen.obd[blockNum][chNum].obdcore.obdhw.bit.obdhw	= obArea->width;
	ioPro.sen.obd[blockNum][chNum].obdcore.obdvw.bit.obdvw	= obArea->lines;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Get OBD count
@param[in]	ch : Channel No.
@param[out]	obcnt :	OBCNT<br>
			each colors count value range :0 - 0xFFFFF<br>
@retval		D_DDIM_OK					: Getting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
INT32 impro_senobd_get_ob_cnt( EimproObdCh ch, TimproRgb4* obcnt )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );
	im_pro_comm_get_obd_cnt( blockNum, chNum, obcnt );
	return D_DDIM_OK;
}

/**
Get OBD data
@param[in]	ch : Channel No.
@param[out]	obdata : OBD Data
@retval		D_DDIM_OK					: Getting OK
@retval		D_IM_PRO_NG					: Getting NG
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Getting NG
*/
INT32 impro_senobd_get_ob_data( EimproObdCh ch, TimproRgb4* obdata )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obd_block_ch( ch, &blockNum, &chNum );
	im_pro_comm_get_obd_data( blockNum, chNum, obdata );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSenobd类的一个实例
 *
 */
ImproSenobd* 	impro_senobd_new()
{
	ImproSenobd* self = k_object_new_with_private(IMPRO_TYPE_SENOBD,sizeof(ImproSenobdPrivate));
	ImproSenobdPrivate* priv = IMPRO_SENOBD_GET_PRIVATE(self);
	
	e_warning_o(self," impro_senobd_new \n");
	return self;
}
