/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :王梦雅
*@brief             :iipfrecttblarrayb
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


#include "iipfrecttblarrayb.h"
#include "iipfrecttblarrayb1.h"
#include "iipfrecttblarrayb2.h"
#include "iipfrecttblarrayb3.h"
#include "iipfrecttblarrayb4.h"
#include "iipfrecttblarrayb5.h"
#include "iipfrecttblarrayb6.h"
#include "iipfrecttblarrayb7.h"
#include "iipfrecttblarrayb8.h"
#include "iipfrecttblarrayb9.h"
#include "iipfrecttblarrayb10.h"
#include "iipfrecttblarrayb11.h"
#include "iipfrecttblarrayb12.h"
#include "iipfrecttblarrayb13.h"
#include "iipfrecttblarrayb14.h"
#include "iipfrecttblarrayb15.h"
#include "iipfrecttblarrayb16.h"


#ifndef CO_CT_IM_IIP_DISABLE

#if !defined(CO_CT_IM_IIP_2_5_3_DISABLE_FRECT_TBL) || !defined(CO_CT_IM_IIP_2_5_4_DISABLE_FRECT_TBL)
// 2304x1296 right-side table (distortion=-9%)
#ifdef __GNUC__
TImIipParamFrectOpcol0
gCtImIipFrecttbl1FullhdVis[D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_1_NUM] __attribute__((aligned(8))) = {
#else
__align(8) TImIipParamFrectOpcol0
gCtImIipFrecttbl1FullhdVis[D_CT_IM_IIP_FRECT_TBL_FULLHD_VIS_1_NUM] = {
#endif
		G_CT_IM_IIP_FRECTTBL_B1_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B2_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B3_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B4_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B5_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B6_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B7_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B8_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B9_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B10_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B11_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B12_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B13_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B14_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B15_FULLHD_VIS(),
		G_CT_IM_IIP_FRECTTBL_B16_FULLHD_VIS(),
};

#endif //!CO_CT_IM_IIP_2_5_3_DISABLE_FRECT_TBL || !CO_CT_IM_IIP_2_5_4_DISABLE_FRECT_TBL

#endif
