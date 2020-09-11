/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :王梦雅
*@brief             :iipfrecttblarraya
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/

#ifndef __IIP_FRECTTBL_ARRAY_A_H__
#define __IIP_FRECTTBL_ARRAY_A_H__


// im_iip header
#include "../../ImageMacro/src/imiipparam.h"


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// FRECT table number (for FullHD 2340x1296)
#define D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_X_NUM	(18)		// (2304 / 64 /2)
#define D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_Y_NUM	(162)		// (1296 / 8)
#define D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_NUM		(D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_X_NUM * D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_Y_NUM)
#define D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_0_X_OFS	(0)


#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif/*__IIP_FRECTTBL_ARRAY_A_H__*/
