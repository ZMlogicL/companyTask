/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-10
*@author : 刘嫚鶄
*@brief : ImElaTestCase
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __IM_ELA_TEST_CASE_H__
#define __IM_ELA_TEST_CASE_H__


#include <klib.h>


#define IM_TYPE_ELA_TEST_CASE                  (im_ela_test_case_get_type())
#define IM_ELA_TEST_CASE(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, ImElaTestCase)) 
#define IM_IS_ELA_TEST_CASE(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, IM_TYPE_ELA_TEST_CASE)) 


typedef struct _ImElaTestCase ImElaTestCase;
typedef struct _ImElaTestCasePrivate ImElaTestCasePrivate;

struct _ImElaTestCase 
{
	KObject parent;
};


KConstType im_ela_test_case_get_type(void);
ImElaTestCase* im_ela_test_case_new(void);

/*
 * PUBLIC
 */

void	 				im_ela_test_case_choose_case(ImElaTestCase*self,UCHAR type1);

#endif /* __IM_ELA_TEST_CASE_H__ */
