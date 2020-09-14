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


#ifndef __IMPRO_SENSG_H__
#define __IMPRO_SENSG_H__


#include <klib.h>
#include "improbase.h"
#include "improsentop.h"

#define IMPRO_TYPE_SENSG        (impro_sensg_get_type())
#define IMPRO_SENSG(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSensg))
#define IMPRO_IS_SENSG(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SENSG))


/*宏定义区域*/
/** @addtogroup impro_sensg SG*/
/**< Number of SG VD/HD ch	*/
#define	ImproSensg_D_IM_PRO_SG_VHD_CH_NUM		(2)
/**< Minimum setting of VDOCYC	*/
#define	ImproSensg_D_IM_PRO_SG_VDOCYC_MIN		(0x0004)
/**< Maximum setting of VDDLY	*/
#define	ImproSensg_D_IM_PRO_SG_VDDLY_MAX		(255)
/**< Maximum setting of HDOCYC	*/
#define	ImproSensg_D_IM_PRO_SG_HDOCYC_MAX		(0x3FFF)
/**< Maximum setting of HDOW	*/
#define	ImproSensg_D_IM_PRO_SG_HDOW_MAX		(0x1FF)
/**< Maximum setting of VDOW	*/
#define	ImproSensg_D_IM_PRO_SG_VDOW_MAX		(0x1FF)
// im_pro_sen_sg


/*其他结构体或类型定义区域*/
/** SG channel number*/
typedef enum {
	/**< ch0	*/
	ImproSensg_E_IM_PRO_SG_CH_0 = 0,
	/**< ch1	*/
	ImproSensg_E_IM_PRO_SG_CH_1,
	/**< ch1	*/
	ImproSensg_E_IM_PRO_SG_CH_2,
	/**< ch1	*/
	ImproSensg_E_IM_PRO_SG_CH_3,
} EimproSgCh;


/** SG Control information*/
typedef struct {
	/**< VD/HD I/O control. value range		:[0:Input 1:Output] target registor	:@@VHDO		*/
	UCHAR				vhdo;
	/**< VD output timing. value range			:[0:HD0 2cycle 1:HD0 1cycle] target registor :@@VDOT		*/
	UCHAR				vdot;
	/**< VD inverted output. value range		:[0:L out 1:H out] target registor	:@@VDINV	*/
	USHORT			vdinv;
	/**< HD inverted output. value range		:[0:L out 1:H out] target registor :@@HDINV	*/
	UCHAR				hdinv;
	/**< Last HDO output switch mode. value range		:[0:HDO output cycle is always constant 1:HDO
	 * output is switched for only the last line] target registor :@@HDCHG	*/
	UCHAR				hdchg;
	/**< VD output delay. value range			:[0-255] target registor :@@VDDLY	*/
	UCHAR				vddly;
	/**< VD0 output cycle. value range			:[0(=0x1000000) 0x000004 - 0xFFFFFF] target registor	:@@VDOCYC*/
	ULONG			vdocyc;
	/**< VD0 output width. value range			:[0(=512) 1 - 511] target registor	:@@VDOW		*/
	USHORT			vdow;
	/**< HD0 output cycle. value range			:[0(=0x4000) 0x0001 - 0x3FFF] target registor	:@@HDOCYC	*/
	USHORT			hdocyc;
	/**< HD0 output width. value range			:[0(=512) 1 - 511] target registor	:@@HDOW		*/
	USHORT			hdow;
	/**< HD0 output cycle2. value range		:[0(=0x4000) 0x0001 - 0x3FFF] target registor	:@@HDOCYC2	*/
	USHORT			hdocyc2;
	/**< VD0 output width2. value range		:[0(=512) 1 - 511] target registor	:@@HDOW2	*/
	USHORT			hdow2;
} TimproSgCtrl;

/** SG monitor information*/
typedef struct {
	/**< monitor the input VD signal from the outside.	 */
	UCHAR				inputVdSignal;
	/**< monitor the input HD signal from the outside.	 */
	UCHAR				inputHdSignal;
} TimproSgMoniInfo;

/*类型定义区域*/
typedef struct _ImproSensg							ImproSensg;
typedef struct _ImproSensgPrivate				ImproSensgPrivate;


/*对象结构体区域*/
struct _ImproSensg
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType			impro_sensg_get_type(void);
ImproSensg*		impro_sensg_new();
/**
The SG operation(Trigger) started.
@param[in]	ch : SG ch number
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32		impro_sensg_start( EimproSgCh ch );
/**
The SG operation(Trigger) stopped(Frame).
@param[in]	ch : SG ch number
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32		impro_sensg_stop( EimproSgCh ch, UCHAR force );
/**
The SG operation condition is set.
@param[in]	ch : SG ch number
@param[in]	sgCtrl : SG Control info
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32		impro_sensg_ctrl( EimproSgCh ch, TimproSgCtrl* sgCtrl );
/**
The SG operation condition is get.
@param[in]	ch : SG ch number
@param[out]	sgCtrl : SG Control info
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32		impro_sensg_get_cycle( EimproSgCh ch, TimproSgCtrl* sgCtrl );
/**
Get monitoring result of the input VD and HD signals.
@param[in]	ch : SG ch number
@param[out]	sgMoniInfo : SG monitor information
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32		impro_sensg_get_monitor_info( EimproSgCh ch, TimproSgMoniInfo* sgMoniInfo );







#endif /* __IMPRO_SENSG_H__ */

