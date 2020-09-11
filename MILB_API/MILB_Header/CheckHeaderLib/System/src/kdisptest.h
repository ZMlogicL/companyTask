/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :kdisptest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __K_DISP_TEST_H__
#define __K_DISP_TEST_H__


#include <klib.h>


#define K_TYPE_DISP_TEST	        (k_disp_test_get_type())
#define K_DISP_TEST(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KDispTest))
#define K_IS_DISP_TEST(obj)	        (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_DISP_TEST))


typedef struct _KDispTest	        KDispTest;
typedef struct _KDispTestPrivate	KDispTestPrivate;

struct  _KDispTest
{
	KObject parent;
};


KConstType	k_disp_test_get_type(void);
KDispTest*	k_disp_test_new(void);
void        k_disp_test_disp_test(KDispTest *self);
void        k_disp_test_xch_test(KDispTest *self);
void        k_disp_test_ela_test(KDispTest *self);
void        k_disp_test_jpeg_enc_test(KDispTest *self);
void        k_disp_test_jpeg_dec_test(KDispTest *self);


#endif/*__K_DISP_TEST_H__*/
