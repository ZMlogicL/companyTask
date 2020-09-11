/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :zhangxinyue
*@brief               :CtImEla类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_ELA_H_
#define __CT_IM_ELA_H_

#include <klib.h>
#include "driver_common.h"

#define CT_TYPE_IM_ELA					(ct_im_ela_get_type())
#define CT_IM_ELA(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImEla)) 
#define CT_IS_IM_ELA(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_ELA))

#define CtImEla_S_ELA_BAYER_16M_WIDTH	(4704)
#define CtImEla_S_ELA_BAYER_16M_LINES	(3488)
#define CtImEla_S_ELA_BAYER_12M_WIDTH	(4032)
#define CtImEla_S_ELA_BAYER_12M_LINES	(3024)
#define CtImEla_S_ELA_BAYER_FHD_WIDTH	(2796)
#define CtImEla_S_ELA_BAYER_FHD_LINES		(1560)
/* 4424(+24) */
#define CtImEla_S_ELA_BAYER_4K2K_WIDTH	(4448)
#define CtImEla_S_ELA_BAYER_4K2K_LINES	(2488)

#define CtImEla_S_SDRAM_ELA_SIZ_16M		(CtImEla_S_ELA_BAYER_16M_WIDTH * CtImEla_S_ELA_BAYER_16M_LINES * 3 / 2)
#define CtImEla_S_SDRAM_ELA_SIZ_12M		(CtImEla_S_ELA_BAYER_12M_WIDTH * CtImEla_S_ELA_BAYER_12M_LINES * 3 / 2)
#define CtImEla_S_SDRAM_ELA_SIZ_FHD		(CtImEla_S_ELA_BAYER_FHD_WIDTH * CtImEla_S_ELA_BAYER_FHD_LINES * 3 / 2)
#define CtImEla_S_SDRAM_ELA_SIZ_4K2K		(CtImEla_S_ELA_BAYER_4K2K_WIDTH * CtImEla_S_ELA_BAYER_4K2K_LINES * 3 / 2)
/* Noise Suppress Data : 16M */
#define CtImEla_S_SDRAM_ELA_NOISE_SUPPRESS	(0x1000000)
/* Extract Noise Data : 38M */
#define CtImEla_S_SDRAM_ELA_EXTRACT_NOISE		(0x2600000)
/* Bayer Data : 84M */
#define CtImEla_S_SDRAM_ELA_OUT_BAYER				(0x5400000)

//#define CtImEla_S_SDRAM_ELA_BASE			(0x81000000)
//#define CtImEla_S_SDRAM_ELA_BASE			(0x21000000)
#define CtImEla_S_SDRAM_ELA_BASE				(0x48000000)

/* 0x79778A00 */
#define CtImEla_S_SDRAM_ELA_ADR_IN_BAYER		(CtImEla_S_SDRAM_ELA_BASE)
#define CtImEla_S_SDRAM_ELA_ADR_NOISE_SUPPRESS	(CtImEla_S_SDRAM_ELA_ADR_IN_BAYER + CtImEla_S_SDRAM_ELA_SIZ_16M)
/* 0x7A778A00 */
#define CtImEla_S_SDRAM_ELA_ADR_EXTRACT_NOISE		(CtImEla_S_SDRAM_ELA_ADR_NOISE_SUPPRESS + CtImEla_S_SDRAM_ELA_NOISE_SUPPRESS)
/* 0x7CD78A00 */
#define CtImEla_S_SDRAM_ELA_ADR_OUT_BAYER		(CtImEla_S_SDRAM_ELA_ADR_EXTRACT_NOISE  + CtImEla_S_SDRAM_ELA_EXTRACT_NOISE)

typedef struct 		_CtImEla CtImEla;
typedef struct 		_CtImElaPrivate CtImElaPrivate;

struct _CtImEla
{
	KObject parent;
};

KConstType 	ct_im_ela_get_type(void);
CtImEla* 		ct_im_ela_new(void);

void 				ct_im_ela_ctrl_set_test_data(CtImEla *self, T_IM_ELA_CTRL* const ctrl_ela);

#if 1
void 				ct_im_ela_multiple_set_test_data(CtImEla *self, T_IM_ELA_MULTIPLE_TIMES_INFO* multiple_exec_info);
#endif

void 				ct_im_ela_clk_chk(CtImEla *self);
void 				ct_im_ela_reg_print(CtImEla *self);
void 				ct_im_ela_main(CtImEla *self, kint32 argc, kchar** argv);
void 				ct_im_ela_1_01(CtImEla *self);
void 				ct_im_ela_1_02(CtImEla *self);
void 				ct_im_ela_1_03(CtImEla *self);

#endif /* __CT_IM_ELA_H_ */
