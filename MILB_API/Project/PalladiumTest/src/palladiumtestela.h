/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : PalladiumTestEla
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __PALLADIUM_TEST_ELA_H__
#define __PALLADIUM_TEST_ELA_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_ELA                  (palladium_test_ela_get_type())
#define PALLADIUM_TEST_ELA(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestEla)) 
#define PALLADIUM_IS_TEST_ELA(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_ELA)) 

#define D_IM_ELA_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP6())
#define D_IM_ELA_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP6())
#define D_IM_ELA_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP6())
#define D_IM_ELA_CLK_REG_BIT	D_DD_TOP_ELACK_BIT	// bit24
#define D_IM_ELA_PCLK_REG_BIT	D_DD_TOP_ELAAP_BIT	// bit25
#define D_IM_ELA_ICLK_REG_BIT	D_DD_TOP_ELAAX_BIT	// bit27
// Input: 12bit packed raw ch0
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_01"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_01
// Input: 12bit packed raw ch1
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_02"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_01
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_03"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_02
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_04"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_02
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_05"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_03
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_06"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_03
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_07"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_04
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_08"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_04
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_09"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_05
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_10"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_05
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_11"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_06
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_12"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_06
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_13"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_07
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_14"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_07
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_15"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_08
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_16"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_08
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_17"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_09
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_18"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_09
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_19"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_10
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_20"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_10
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_21"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_11
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_22"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_11
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_23"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_12
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_24"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_12
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_25"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_13
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_26"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_13
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_27"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_14
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_28"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_14
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_29"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_15
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_30"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_15
// Input: 8bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_31"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_16
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_32"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_16
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_33"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_17
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_34"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_17
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_36"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_18
// Input: 16// Input: 16bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_35"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_18
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_37"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_19
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_38"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_19
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_39"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_20
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_40"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_20
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_41"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_21
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_42"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_21
// Input: 8bit raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_43"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_22
// Input: 8bit raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_44"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_22
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_45"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_23bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_35"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_18
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_37"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_19
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_38"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_19
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_39"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_20
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_40"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_20
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_41"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_21
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_42"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_21
// Input: 8bit raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_43"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_22
// Input: 8bit raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_44"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_22
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_45"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_23
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_47"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_24
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_46"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_23
// Input: 12bit packed raw
#undef D_IM_ELA_TEST_NO
#define D_IM_ELA_TEST_NO "2_48"
#undef D_IM_ELA_CT_FUNC
#define D_IM_ELA_CT_FUNC CT_Im_Ela_2_24

typedef struct _PalladiumTestEla PalladiumTestEla;
typedef struct _PalladiumTestElaPrivate PalladiumTestElaPrivate;

struct _PalladiumTestEla 
{
	KObject parent;
};


KConstType palladium_test_ela_get_type(void);
PalladiumTestEla* palladium_test_ela_new(void);

/*
 * PUBLIC
 */

VOID pt_im_ela_main( VOID );

#endif /* __PALLADIUM_TEST_ELA_H__ */
