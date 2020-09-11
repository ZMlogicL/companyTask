/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 陈阳
*@brief : ImProDebug
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_PRO_DEBUG_H__
#define __IM_PRO_DEBUG_H__


#include <klib.h>
#include "ctimprofile.h"


#define IM_TYPE_PRO_DEBUG                  (im_pro_debug_get_type())
#define IM_PRO_DEBUG(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImProDebug)) 
#define IM_IS_PRO_DEBUG(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_PRO_DEBUG)) 


typedef struct _ImProDebug ImProDebug;
typedef struct _ImProDebugPrivate ImProDebugPrivate;

struct _ImProDebug 
{
	KObject parent;
};


KConstType im_pro_debug_get_type(void);
ImProDebug* im_pro_debug_new(void);
ImProDebug* im_pro_debug_get(void);

#ifndef CO_CT_IM_PRO_DISABLE
#ifdef CO_DEBUG_ON_PC
void im_pro_debug_pwch_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_prch_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_ldiv_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_obd_intflg_fill(ImProDebug *self, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_obt_intflg_fill(ImProDebug *self, kuint32 blockNum, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_sentop_vd_intflg_fill(ImProDebug *self, kuint32 vdInte, kuint32 vdIntf, kuint32 sgVdInte, 
								kuint32 sgVdIntf, kuint32 gyroVdInte, kuint32 gyroVdIntf );
void im_pro_debug_sentop_hd_intflg_fill(ImProDebug *self, kuint32 hdInte, kuint32 hdIntf, kuint32 sgHdInte, kuint32 sgHdIntf );
void im_pro_debug_slvs_comm_intflg_fill(ImProDebug *self, kuint32 inte, kuint32 intf );
void im_pro_debug_slvs_strm_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf, kuint32 leinte, 
								kuint32 leintf, kuint32 meinte0, kuint32 meintf0, kuint32 meinte1, kuint32 meintf1 );
void im_pro_debug_lvds_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte1, kuint32 intf1, kuint32 inte2, kuint32 intf2, 
								kuint32 inte3, kuint32 intf3 );
void im_pro_debug_dmipi_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_cmipi_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte1, kuint32 intf1, kuint32 inte2, kuint32 intf2 );
void im_pro_debug_moni_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_sro_moni_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 inte, kuint32 intf );
void im_pro_debug_sro_sdc_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 ch, kuint32 inte, kuint32 intf );
void im_pro_debug_srotop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf );
void im_pro_debug_srotop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf );
void im_pro_debug_b2btop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf );
void im_pro_debug_b2btop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf );
void im_pro_debug_stat_aeawb_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 aeawb_inte, kuint32 aeawbIntf );
void im_pro_debug_stat_af_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 afInte, kuint32 afIntf );
void im_pro_debug_stat_hist_intflg_fill(ImProDebug *self, kuint32 ch, kuint32 histInte, kuint32 histIntf );
void im_pro_debug_pastop_vd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 vdInte, kuint32 vdIntf );
void im_pro_debug_pastop_hd_intflg_fill(ImProDebug *self, kuint32 unitNo, kuint32 hdInte, kuint32 hdIntf );
#endif  // CO_DEBUG_ON_PC
#endif  // CO_CT_IM_PRO_DISABLE

#endif /* __IM_PRO_DEBUG_H__ */
