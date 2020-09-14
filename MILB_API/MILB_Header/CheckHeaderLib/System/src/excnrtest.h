/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :excnrtest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __EX_CNR_TEST_H__
#define __EX_CNR_TEST_H__


#include <klib.h>


#define EX_TYPE_CNR_TEST	       (ex_cnr_test_get_type())
#define EX_CNR_TEST(obj)	       (K_TYPE_CHECK_INSTANCE_CAST((obj), ExCnrTest))
#define EX_IS_CNR_TEST(obj)	       (K_TYPE_CHECK_INSTANCE_TYPE((obj), EX_TYPE_CNR_TEST))


typedef struct _ExCnrTest	        ExCnrTest;
typedef struct _ExCnrTestPrivate	ExCnrTestPrivate;


struct  _ExCnrTest
{
	KObject parent;
};


KConstType	ex_cnr_test_get_type(void);
ExCnrTest*	ex_cnr_test_new(void);
void        ex_cnr_test_exstop_test(ExCnrTest* self);
void        ex_cnr_test_exsgpv_test(ExCnrTest* self);
void        ex_cnr_test_cnr_test(ExCnrTest* self);


#endif/*__EX_CNR_TEST_H__*/
