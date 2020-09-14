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
#include"improsenobt.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSenobt, impro_senobt);
#define IMPRO_SENOBT_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSenobtPrivate, IMPRO_TYPE_SENOBT));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSenobtPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
// RDMA I/F
static const TimproRdmaObtAddr S_G_IM_PRO_OBT_Addr[ImproBase_D_IM_PRO_SEN_OBT_CNT] = {
	// ImproBase_E_IM_PRO_OBT_CH_0_0
	{
		0x2800B8C0,0x2800B8D4,0x2800B8E8,0x2800B8EC,
		0x2800B8F0,0x2800B8F4,
	},
	// E_IM_PRO_OBT_CH_0_1
	{
		0x2800B9C0,0x2800B9D4,0x2800B9E8,0x2800B9EC,
		0x2800B9F0,0x2800B9F4,
	},
	// E_IM_PRO_OBT_CH_1_0
	{
		0x2800BAC0,0x2800BAD4,0x2800BAE8,0x2800BAEC,
		0x2800BAF0,0x2800BAF4,
	},
	// E_IM_PRO_OBT_CH_1_1
	{
		0x2800BBC0,0x2800BBD4,0x2800BBE8,0x2800BBEC,
		0x2800BBF0,0x2800BBF4,
	},
	// E_IM_PRO_OBT_CH_2_0
	{
		0x2800BCC0,0x2800BCD4,0x2800BCE8,0x2800BCEC,
		0x2800BCF0,0x2800BCF4,
	},
	// E_IM_PRO_OBT_CH_2_1
	{
		0x2800BDC0,0x2800BDD4,0x2800BDE8,0x2800BDEC,
		0x2800BDF0,0x2800BDF4,
	},
	// E_IM_PRO_OBT_CH_3_0
	{
		0x2800BEC0,0x2800BED4,0x2800BEE8,0x2800BEEC,
		0x2800BEF0,0x2800BEF4,
	},
	// E_IM_PRO_OBT_CH_3_1
	{
		0x2800BFC0,0x2800BFD4,0x2800BFE8,0x2800BFEC,
		0x2800BFF0,0x2800BFF4,
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_senobt_constructor(ImproSenobt *self)
{
	ImproSenobtPrivate *priv = IMPRO_SENOBT_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_senobt_destructor(ImproSenobt *self)
{
	ImproSenobtPrivate *priv = IMPRO_SENOBT_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
Start TOP OB macro.
@param[in]	ch : Channel No.
@retval		D_DDIM_OK					: Processing OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Processing NG
*/
INT32 impro_senobt_start( EimproObtCh ch )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = D_IM_PRO_TRG_START;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_common_fig_im_pro_sen_set_start_status(D_IM_SEN_STATUS_OBT00, ch);

	return D_DDIM_OK;
}

/**
Stop TOP OB macro.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobt_stop( EimproObtCh ch, UCHAR force )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	if (force == 0){
		// frame stop
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else{
		// force stop
		ioPro.sen.obt[blockNum][chNum].obttrg.bit.obttrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	im_pro_common_fig_im_pro_sen_set_stop_status(D_IM_SEN_STATUS_OBT00, ch);

	return D_DDIM_OK;
}

/**
The control parameter of TOP OB compensation is set.
@param[in]	ch : Channel No.
@param[in]	obtCtrl	:	TOP OB Control information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobt_ctrl( EimproObtCh ch, TimproObtCtrl* obtCtrl )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

#ifdef CO_PARAM_CHECK
	if (obtCtrl == NULL){
		Ddim_Assertion(("I:impro_senobt_ctrl error. obtCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obt[blockNum][chNum].obtcore.obtctl.bit.obten			= obtCtrl->obtEnable;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtmd			= obtCtrl->mode;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtsl			= obtCtrl->sel;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtcen			= obtCtrl->intercommEnable;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obththbit	= obtCtrl->obMaxValue;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obtlthbit	= obtCtrl->obMinValue;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
The area for Top OB detection is set up.
@param[in]	ch : Channel No.
@param[in]	obtArea	:The area for Top OB detection. See @ref TimproAreaInfo<br>
							value range  :posX[0 - 12287]<br>
							target registor  :@@OBTH<br>
							value range  :posY[0 - 8191]<br>
							target registor  :@@OBTV<br>
							value range  :width[1 - 12288]	1pixel boundary(OBTMD=0)<br>
															2pixel boundary(OBTMD=1)<br>
							target registor  :@@OBTHW<br>
							value range  :lines[1 - 127]	1pixel boundary(OBTMD=0)<br>
															2pixel boundary(OBTMD=1)<br>
							target registor  :@@OBTVW
@retval		D_DDIM_OK						: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR		: Setting NG
*/
INT32 impro_senobt_set_area( EimproObtCh ch, TimproAreaInfo* obtArea )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

#ifdef CO_PARAM_CHECK
	if (obtArea == NULL){
		Ddim_Assertion(("I:impro_senobt_set_area error. obtArea=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobt_D_IM_PRO_OBT_OBTH_MIN, ImproSenobt_D_IM_PRO_OBT_OBTH_MAX,
					obtArea->posX, "impro_senobt_set_area : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobt_D_IM_PRO_OBT_OBTV_MIN, ImproSenobt_D_IM_PRO_OBT_OBTV_MAX,
					obtArea->posY, "impro_senobt_set_area : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobt_D_IM_PRO_OBT_OBTHW_MIN, ImproSenobt_D_IM_PRO_OBT_OBTHW_MAX,
					obtArea->width, "impro_senobt_set_area : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSenobt_D_IM_PRO_OBT_OBTVW_MIN, ImproSenobt_D_IM_PRO_OBT_OBTVW_MAX,
					obtArea->lines, "impro_senobt_set_area : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	ioPro.sen.obt[blockNum][chNum].obtcore.obth.bit.obth		= obtArea->posX;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtv.bit.obtv		= obtArea->posY;
	ioPro.sen.obt[blockNum][chNum].obtcore.obthw.bit.obthw	= obtArea->width;
	ioPro.sen.obt[blockNum][chNum].obtcore.obtvw.bit.obtvw	= obtArea->lines;
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Set TOP OB offset
@param[in]	ch : Channel No.<br>
				 value range:[0 - 1]<br>
@param[in]	offset : TOP OB offset<br>
					 value range : rr :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsr<br>
					 value range : gr :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsgr<br>
					 value range : gb :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsgb<br>
					 value range : bb :[0x4000(=-16384) - 0x3FFF(=+16383)]<br>
					 target registor :@@obtOfsb
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@remarks	Please set up a minus value by a complement. bit15 is sign bit
*/
INT32 impro_senobt_set_offset( EimproObtCh ch, TimproARgb2* offset )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

#ifdef CO_PARAM_CHECK
	if (offset == NULL){
		Ddim_Assertion(("I:impro_senobt_set_offset error. offset=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	im_pro_set_reg_signed( ioPro.sen.obt[blockNum][chNum].obtcore.obtofsr, union IoObtofsr, obtofsr, offset->rr );
	im_pro_set_reg_signed( ioPro.sen.obt[blockNum][chNum].obtcore.obtofsgr, union IoObtofsgr, obtofsgr, offset->gr );
	im_pro_set_reg_signed( ioPro.sen.obt[blockNum][chNum].obtcore.obtofsgb, union IoObtofsgb, obtofsgb, offset->gb );
	im_pro_set_reg_signed( ioPro.sen.obt[blockNum][chNum].obtcore.obtofsb, union IoObtofsb, obtofsb, offset->bb );
	// Dd_Top_Start_Clock
	im_pro_off_pclk( ImproBase_E_IM_PRO_UNIT_NUM_1, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SEN );

	return D_DDIM_OK;
}

/**
Get TOP OB detection data
@param[in]	ch : Channel No.<br>
				 value range:[0 - 1]<br>
@param[out]	obtdata : OBTDATA
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_senobt_get_bot_data( EimproObtCh ch, TimproARgb2* obtdata )
{
	UCHAR blockNum = 0;
	UCHAR chNum = 0;

	im_pro_comm_get_obt_block_ch( ch, &blockNum, &chNum );
	im_pro_comm_get_obt_data( blockNum, chNum, obtdata );

	return D_DDIM_OK;
}

/**
Get the top address of the address array of OBT control.
@param[in]		ch : Channel No.
@param[out]		addr					: Top address of the address array of OBT control.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
INT32 impro_senobt_get_rdma_addr_obt_cntl( EimproObtCh ch, const TimproRdmaObtAddr** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:impro_senobt_get_rdma_addr_obt_cntl. error. addr=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_PRO_OBT_Addr[ch]);

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSenobt类的一个实例
 *
 */
ImproSenobt* 	impro_senobt_new()
{
	ImproSenobt* self = k_object_new_with_private(IMPRO_TYPE_SENOBT,sizeof(ImproSenobtPrivate));
	ImproSenobtPrivate* priv = IMPRO_SENOBT_GET_PRIVATE(self);
	
	e_warning_o(self," impro_senobt_new \n");
	return self;
}
