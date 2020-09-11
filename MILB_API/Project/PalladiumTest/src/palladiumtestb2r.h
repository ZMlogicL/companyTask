/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : PalladiumTestB2r
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __PALLADIUM_TEST_B2R_H__
#define __PALLADIUM_TEST_B2R_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_B2R                  (palladium_test_b2r_get_type())
#define PALLADIUM_TEST_B2R(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestB2r)) 
#define PALLADIUM_IS_TEST_B2R(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_B2R)) 

#define PalladiumTestB2r_PalladiumTestB2r_D_IM_B2R1_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define PalladiumTestB2r_D_IM_B2R1_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define PalladiumTestB2r_D_IM_B2R1_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define PalladiumTestB2r_D_IM_B2R1_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP10())
#define PalladiumTestB2r_PalladiumTestB2r_D_IM_B2R1_CLK_REG_BIT	D_DD_TOP_B2R1CK_BIT	// bit20~21
#define PalladiumTestB2r_D_IM_B2R1_ICLK_REG_BIT	D_DD_TOP_B2R1AX_BIT	// bit22~23
#define PalladiumTestB2r_D_IM_B2R1_HCLK_REG_BIT	D_DD_TOP_B2R1AH_BIT	// bit24~25
#define PalladiumTestB2r_D_IM_B2R1_PCLK_REG_BIT	D_DD_TOP_B2R1AP_BIT	// bit26~27
#define PalladiumTestB2r_D_IM_B2R2_CLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define PalladiumTestB2r_D_IM_B2R2_ICLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define PalladiumTestB2r_D_IM_B2R2_HCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define PalladiumTestB2r_D_IM_B2R2_PCLK_REG_ADDR	(&Dd_Top_Get_CLKSTOP12())
#define PalladiumTestB2r_D_IM_B2R2_CLK_REG_BIT	D_DD_TOP_B2R2CK_BIT	// bit20~21
#define PalladiumTestB2r_D_IM_B2R2_ICLK_REG_BIT	D_DD_TOP_B2R2AX_BIT	// bit22~23
#define PalladiumTestB2r_D_IM_B2R2_HCLK_REG_BIT	D_DD_TOP_B2R2AH_BIT	// bit24~25
#define PalladiumTestB2r_D_IM_B2R2_PCLK_REG_BIT	D_DD_TOP_B2R2AP_BIT	// bit26~27

#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_1"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_22"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_32"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_38"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_46"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "2_1"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_1"
// Input: 16bit non-packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_2"
// Input: 12bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_3"
// Input: 12bit packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_4"
// Input: 10bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_5"
// Input: 10bit packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_6"
// Input: 8bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_7"
// Input: 8bit non-packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_8"
// Input: 12bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_9"
// Input: 12bit non-packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_10"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_11"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_17"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_18"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_19"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_20"
// Input: 12bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_21"
// Input: 10bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_23"
// Input: 8bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_25"
// Input: 8bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_26"
// Input: 8bit non-packed raw,  Output: RGB P12
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_28"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_30"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_32"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_34"
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "1_"
// Input: 12bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_22"
// Input: 10bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_24"
// Input: 12bit packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_27"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_29"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_31"
// Input: 16bit non-packed raw,  Output: RGB U8
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_33"
// Input: 16bit non-packed raw,  Output: RGB U16
#undef PalladiumTestB2r_D_IM_B2R_TEST_NO
#define PalladiumTestB2r_D_IM_B2R_TEST_NO "3_35"

typedef struct _PalladiumTestB2r PalladiumTestB2r;
typedef struct _PalladiumTestB2rPrivate PalladiumTestB2rPrivate;

struct _PalladiumTestB2r 
{
	KObject parent;
};


KConstType palladium_test_b2r_get_type(void);
PalladiumTestB2r* palladium_test_b2r_new(void);

/*
 * PUBLIC
 */

VOID pt_im_b2r_main( VOID );

#endif /* __PALLADIUM_TEST_B2R_H__ */
