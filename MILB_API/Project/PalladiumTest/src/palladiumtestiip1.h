/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_IIP1_H__
#define __PALLADIUM_TEST_IIP1_H__

#include <klib.h>
#include "ddim_typedef.h"

#define PALLADIUM_TYPE_TEST_IIP1	(palladium_test_iip1_get_type())
#define PALLADIUM_TEST_IIP1(obj) 	K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestIip1)
#define PALLADIUM_IS_TEST_IIP1(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_IIP1)

typedef struct	_PalladiumTestIip1 PalladiumTestIip1;
typedef struct _PalladiumTestIip1Private		PalladiumTestIip1Private;

struct	_PalladiumTestIip1{
	KObject parent;
};


KConstType 				palladium_test_iip1_get_type(void);

VOID 							palladium_test_iip1_pt_im_iip_start_clock( PalladiumTestIip1* self );
VOID 							palladium_test_iip1_pt_im_iip_enable_gic( PalladiumTestIip1* self );
VOID 							palladium_test_iip1_pt_im_iip_run_1_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_2( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_4( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_5( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_6( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_2_7(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_3_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_3_2( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_4_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_5_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_6_1(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID							palladium_test_iip1_pt_im_iip_run_6_2(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_7_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID	 						palladium_test_iip1_pt_im_iip_run_8_1( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_9_1(PalladiumTestIip1* self , kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
VOID 							palladium_test_iip1_pt_im_iip_run_9_2( PalladiumTestIip1* self ,kuchar const ctNo1st, kuchar const ctNo2st, kuchar const ctNo3st );
PalladiumTestIip1* 	palladium_test_iip1_new(void);
#endif /* __PALLADIUM_TEST_IIP1_H__ */

