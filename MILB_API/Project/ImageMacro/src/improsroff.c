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
#include"improsroff.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproSroff, impro_sroff);
#define IMPRO_SROFF_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproSroffPrivate, IMPRO_TYPE_SROFF));


/*宏定义区域*/
/* All stopped		*/
#define	ImproSroff_D_IM_SRO1_STATUS_NONE		(0x00000000UL)
/* FF0				*/
#define	ImproSroff_D_IM_SRO1_STATUS_FF0		((0x00000000UL)&(1<< 0))
/* FF1				*/
#define	ImproSroff_D_IM_SRO1_STATUS_FF1		((0x00000000UL)&(1<< 1))
/* PGAIN0			*/
#define	ImproSroff_D_IM_SRO1_STATUS_PGAIN0		((0x00000000UL)&(1<< 2))
/* All stopped		*/
#define	ImproSroff_D_IM_SRO2_STATUS_NONE		(0x00000000UL)
/* Image Pipe1&2 PGAIN0	*/
#define	ImproSroff_D_IM_SRO2_STATUS_FF0		((0x10000000UL)&(1<< 0))
/* FF1				*/
#define	ImproSroff_D_IM_SRO2_STATUS_FF1		((0x10000000UL)&(1<< 1))
/* PGAIN0			*/
#define	ImproSroff_D_IM_SRO2_STATUS_PGAIN0		((0x10000000UL)&(1<< 2))
/* Image Pipe1&2 FF0	*/
#define	ImproSroff_D_IM_SRO_STATUS_FF0_BOTH	( ImproSroff_D_IM_SRO1_STATUS_FF0 | ImproSroff_D_IM_SRO2_STATUS_FF0		)
/* Image Pipe1&2 FF0	*/
#define	ImproSroff_D_IM_SRO_STATUS_FF1_BOTH	( ImproSroff_D_IM_SRO1_STATUS_FF1		| ImproSroff_D_IM_SRO2_STATUS_FF1		)
/* Image Pipe1&2 PGAIN0	*/
#define	ImproSroff_D_IM_SRO_STATUS_PGAIN0_BOTH	( ImproSroff_D_IM_SRO1_STATUS_PGAIN0	| ImproSroff_D_IM_SRO2_STATUS_PGAIN0	)


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproSroffPrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/
static const UINT32	gIM_PRO_FF_Status_Tbl[ImproBase_E_IM_PRO_UNIT_NUM_MAX][ImproSroff_D_IM_PRO_SRO_FF_CH_NUM] = {
	// ImproBase_E_IM_PRO_UNIT_NUM_1
	{
		ImproSroff_D_IM_SRO1_STATUS_FF0,		ImproSroff_D_IM_SRO1_STATUS_FF1,
	},
	// ImproBase_E_IM_PRO_UNIT_NUM_2
	{
		ImproSroff_D_IM_SRO2_STATUS_FF0,		ImproSroff_D_IM_SRO2_STATUS_FF1,
	},
	// ImproBase_E_IM_PRO_BOTH_UNIT
	{
		ImproSroff_D_IM_SRO_STATUS_FF0_BOTH,	ImproSroff_D_IM_SRO_STATUS_FF1_BOTH,
	},
};

/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_sroff_constructor(ImproSroff *self)
{
	ImproSroffPrivate *priv = IMPRO_SROFF_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_sroff_destructor(ImproSroff *self)
{
	ImproSroffPrivate *priv = IMPRO_SROFF_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/
/**
FF start.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroff_start( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ff[ch].fftrg.bit.fftrg = D_IM_PRO_TRG_START;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_START_STATUS(gIM_PRO_FF_Status_Tbl[unitNo][ch], 0);

	return D_DDIM_OK;
}

/**
FF stop.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroff_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, UCHAR force )
{
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	if(force == 0) {
		// stop
		ioPro.imgPipe[unitNo].sro.ff[ch].fftrg.bit.fftrg = D_IM_PRO_TRG_FRAME_STOP;
	}
	else {
		// force stop
		ioPro.imgPipe[unitNo].sro.ff[ch].fftrg.bit.fftrg = D_IM_PRO_TRG_FORCE_STOP;
	}
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	ImproSrotop_IM_PRO_SRO_SET_STOP_STATUS(gIM_PRO_FF_Status_Tbl[unitNo][ch], 0);

	return D_DDIM_OK;
}

/**
Setup of FF control parameter.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffCtrl : FF Controller
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroff_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, TimproFfCtrl* ffCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ffCtrl == NULL){
		Ddim_Assertion(("I:impro_sroff_ctrl error. ffCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ff[ch].FFDEFTS.bit.FFDEFTS	= ffCtrl->ffdefts;
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ff[ch].ffmnwgt, union io_ffmnwgt, ffmnwgt, ffCtrl->mnwgt );
	im_pro_set_reg_signed( ioPro.imgPipe[unitNo].sro.ff[ch].ffsbwgt, union io_ffsbwgt, ffsbwgt, ffCtrl->sbwgt );
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
Setup of input position .
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffArea	:The area for OB detection<br>
					value range :posX[0 - 12287]<br>
					target registor :@@FFH<br>
					value range :posY[0 - 8191]<br>
					target registor :@@FFV<br>
					value range :width[4 - 12288] 4pixel boundary<br>
					target registor :@@FFHW<br>
					value range :lines[4 - 8192] 4pixel boundary<br>
					target registor :@@FFVW<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroff_area( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, TimproAreaInfo* ffArea )
{
#ifdef CO_PARAM_CHECK
	if (ffArea == NULL){
		Ddim_Assertion(("I:impro_sroff_area error. ffArea=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroff_D_IM_PRO_FF_FFH_MIN, ImproSroff_D_IM_PRO_FF_FFH_MAX,
			ffArea->posX, "impro_sroff_area : posX" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroff_D_IM_PRO_FF_FFV_MIN, ImproSroff_D_IM_PRO_FF_FFV_MAX,
			ffArea->posY, "impro_sroff_area : posY" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroff_D_IM_PRO_FF_FFHW_MIN, ImproSroff_D_IM_PRO_FF_FFHW_MAX,
			ffArea->width, "impro_sroff_area : width" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( ImproSroff_D_IM_PRO_FF_FFVW_MIN, ImproSroff_D_IM_PRO_FF_FFVW_MAX,
			ffArea->lines, "impro_sroff_area : lines" ) == FALSE ) {
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ff[ch].ffh.bit.ffh		= ffArea->posX;
	ioPro.imgPipe[unitNo].sro.ff[ch].ffv.bit.ffv		= ffArea->posY;
	ioPro.imgPipe[unitNo].sro.ff[ch].ffhw.bit.ffhw	= ffArea->width;
	ioPro.imgPipe[unitNo].sro.ff[ch].ffvw.bit.ffvw	= ffArea->lines;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}

/**
FIR coefficient setting.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffCtrl :LPF Control information.<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 impro_sroff_set_fir_filter( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, TimproFfLpfCtrl* ffCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ffCtrl == NULL){
		Ddim_Assertion(("I:impro_sroff_set_fir_filter error. ffCtrl=NULL\n"));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( ( ffCtrl->b0 + 2 * ( ffCtrl->b1 + ffCtrl->b2 ) ) != 128 ) {
		Ddim_Assertion(("I:impro_sroff_set_fir_filter parameter error. Please satisfy following relationship."
				" ffCtrl->b0 + 2*(ffCtrl->b1 + ffCtrl->b2) == 128  (%u %u %u)\n", ffCtrl->b0, ffCtrl->b1, ffCtrl->b2));
		return ImproBase_D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	// Dd_Top_Start_Clock
	im_pro_common_fig_im_pro_on_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );
	ioPro.imgPipe[unitNo].sro.ff[ch].fflpb0.bit.fflpb0	= ffCtrl->b0;
	ioPro.imgPipe[unitNo].sro.ff[ch].fflpb1.bit.fflpb1	= ffCtrl->b1;
	ioPro.imgPipe[unitNo].sro.ff[ch].fflpb2.bit.fflpb2	= ffCtrl->b2;
	// Dd_Top_Stop_Clock
	im_pro_off_pclk( unitNo, ImproBase_E_IM_PRO_CLK_BLOCK_TYPE_SRO );

	return D_DDIM_OK;
}


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproSroff类的一个实例
 *
 */
ImproSroff* 	impro_sroff_new()
{
	ImproSroff* self = k_object_new_with_private(IMPRO_TYPE_SROFF,sizeof(ImproSroffPrivate));
	ImproSroffPrivate* priv = IMPRO_SROFF_GET_PRIVATE(self);
	
	e_warning_o(self," impro_sroff_new \n");
	return self;
}
