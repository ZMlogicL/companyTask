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


#ifndef __IMPRO_SROAFPB_H__
#define __IMPRO_SROAFPB_H__


#include <klib.h>
#include "improbase.h"
#include "improsrotop.h"

#define IMPRO_TYPE_SROAFPB        (impro_sroafpb_get_type())
#define IMPRO_SROAFPB(obj)       (K_TYPE_CHECK_INSTANCE_CAST (obj, ImproSroafpb))
#define IMPRO_IS_SROAFPB(obj)    (K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_SROAFPB))


/*宏定义区域*/
	/**< Number of SRO AFPB		*/
#define ImproSroafpb_D_IM_PRO_SRO_AFPB_CH_NUM		(ImproSroafpb_E_IM_PRO_AFPB_CH_G + 1)
// @addtogroup im_pro_sro_afpb AFPB
/**< Minimum setting of AFPBV	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBV_MIN			(0)
	/**< Maximum setting of AFPBV	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBV_MAX			(16380)
	/**< Minimum setting of AFPBH	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBH_MIN			(0)
	/**< Maximum setting of AFPBH	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBH_MAX			(16382)
	/**< Minimum setting of AFPBVW	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBVW_MIN		(2)
/**< Maximum setting of AFPBVW	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBVW_MAX		(16382)
	/**< Minimum setting of AFPBHW	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBHW_MIN		(1)
	/**< Maximum setting of AFPBHW	*/
#define	ImproSroafpb_D_IM_PRO_AFPB_AFPBHW_MAX		(16383)


/*其他结构体或类型定义区域*/
/** AFPB channel number
*/
typedef enum {
	/**< ch A	*/
	ImproSroafpb_E_IM_PRO_AFPB_CH_A = 0,
	/**< ch G	*/
	ImproSroafpb_E_IM_PRO_AFPB_CH_G,
} EimproAfpbCh;

/** AFPB Control information
*/
typedef struct {
	/**< AFPB Window information value range  :posX[0 - 16382] target registor
	 *   :@@AFPBH value range  :posY[0 - 16380] target registor  :@@AFPBV value
	 *    range  :width[2 - 16382] target registor  :@@AFPBHW value range
	 *    :lines[2 - 16382] target registor  :@@AFPBVW */
	TimproAreaInfo		afpbArea;
} TimproAfpbCtrl;

/*类型定义区域*/
typedef struct _ImproSroafpb							ImproSroafpb;
typedef struct _ImproSroafpbPrivate				ImproSroafpbPrivate;


/*对象结构体区域*/
struct _ImproSroafpb
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_sroafpb_get_type(void);
ImproSroafpb*		impro_sroafpb_new();
/**
Start AFPB
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
*/
extern	VOID			impro_sroafpb_start( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch );
/**
Stop AFPB
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	force : force stop option
*/
extern	VOID			impro_sroafpb_stop( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch, UCHAR force );
/**
Set AFPB control information
@param[in]	unitNo : Unit number.
@param[in]	ch : Channel No.
@param[in]	afpbCtrl	: AFPB control Information.
*/
extern	INT32			impro_sroafpb_ctrl( E_IM_PRO_UNIT_NUM unitNo, EimproAfpbCh ch, TimproAfpbCtrl* afpbCtrl );



#endif /* __IMPRO_SROAFPB_H__ */

