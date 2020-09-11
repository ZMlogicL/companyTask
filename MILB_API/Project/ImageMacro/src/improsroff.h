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


#ifndef __IMPRO_SROFF_H__
#define __IMPRO_SROFF_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROFF        (impro_sroff_get_type())
#define IMPRO_SROFF(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSroff))
#define IMPRO_IS_SROFF(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROFF))


/*宏定义区域*/
	/**< Number of SRO FF		*/
#define ImproSroff_D_IM_PRO_SRO_FF_CH_NUM			(ImproSroff_E_IM_PRO_FF_CH1 + 1)
/** @addtogroup im_pro_sro_ff FF*/
/**< Minimum setting of FFV	*/
#define	ImproSroff_D_IM_PRO_FF_FFV_MIN				(0)
/**< Maximum setting of FFV	*/
#define	ImproSroff_D_IM_PRO_FF_FFV_MAX				(8191)
/**< Minimum setting of FFH	*/
#define	ImproSroff_D_IM_PRO_FF_FFH_MIN				(0)
/**< Maximum setting of FFH	*/
#define	ImproSroff_D_IM_PRO_FF_FFH_MAX				(12287)
/**< Minimum setting of FFVW	*/
#define	ImproSroff_D_IM_PRO_FF_FFVW_MIN			(4)
/**< Maximum setting of FFVW	*/
#define	ImproSroff_D_IM_PRO_FF_FFVW_MAX			(8192)
/**< Minimum setting of FFHW	*/
#define	ImproSroff_D_IM_PRO_FF_FFHW_MIN			(4)
/**< Maximum setting of FFHW	*/
#define	ImproSroff_D_IM_PRO_FF_FFHW_MAX			(12288)
/*	@}*/	// im_pro_sro_ff
/*其他结构体或类型定义区域*/

/** FF channel number.
*/
typedef enum {
	/**< FF0 */
	ImproSroff_E_IM_PRO_FF_CH0 = 0,
	/**< FF1 */
	ImproSroff_E_IM_PRO_FF_CH1
} EimproFfCh;

/** FF Control information
*/
typedef struct {
	/**< threshold to perform white noise determination of the input image during the frame filter
	 * processing. value range :[0 - 16383] target registor :@@FFDEFTS	*/
	USHORT ffdefts;
	/**< Main line input fixed coefficient. value range :[-512 - 511] target registor :@@FFMNWGT			*/
	SHORT mnwgt;
	/**< FF input fixed coefficient. value range :[-512 - 511] target registor :@@FFSBWGT			*/
	SHORT sbwgt;
} TimproFfCtrl;


/** FF LPF Control information.<br>
Set these 3 registers so that they can meet the following condition.<br>
Constraint: FFLPB0 + 2*(FFLPB1 + FFLPB2) = 128
*/
typedef struct {
	 /**< Frame filter coefficient b0 for LPF value range :[0 - 255] target registor :@@FFLPB0	*/
	UCHAR	b0;
	 /**< Frame filter coefficient b1 for LPF value range :[0 - 255] target registor :@@FFLPB1	*/
	UCHAR	b1;
	/**< Frame filter coefficient b2 for LPF value range :[0 - 255] target registor :@@FFLPB2	*/
	UCHAR	b2;
} TimproFfLpfCtrl;



/*类型定义区域*/
typedef struct _ImproSroff							ImproSroff;
typedef struct _ImproSroffPrivate				ImproSroffPrivate;


/*对象结构体区域*/
struct _ImproSroff
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sroff_get_type(void);
ImproSroff*			impro_sroff_new();
/**
FF start.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroff_start( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch );
/**
FF stop.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroff_stop( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, UCHAR force );
/**
Setup of FF control parameter.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffCtrl : FF Controller
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroff_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, TimproFfCtrl* ffCtrl );
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
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroff_area( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, T_IM_PRO_AREA_INFO* ffArea );
/**
FIR coefficient setting.
@param[in]	unitNo : Unit number.
@param[in]	ch : FFSH channel
@param[in]	ffCtrl :LPF Control information.<br>
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_sroff_set_fir_filter( E_IM_PRO_UNIT_NUM unitNo, EimproFfCh ch, TimproFfLpfCtrl* ffCtrl );


#endif /* __IMPRO_SROFF_H__ */

