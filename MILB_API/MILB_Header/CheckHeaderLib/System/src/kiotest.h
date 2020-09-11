/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-02
*@author            :郑蛘钊
*@brief             :kiotest
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __K_IO_TEST_H__
#define __K_IO_TEST_H__


#include <klib.h>


#define K_TYPE_IO_TEST	        (k_io_test_get_type())
#define K_IO_TEST(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KIoTest))
#define K_IS_IO_TEST(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_IO_TEST))


typedef struct _KIoTest     	KIoTest;
typedef struct _KIoTestPrivate	KIoTestPrivate;

struct  _KIoTest
{
	KObject parent;
};


KConstType	k_io_test_get_type(void);
KIoTest*	k_io_test_new(void);
void        k_io_test_pas_table_test(KDispTest *self, E_PRO_BLOCK_TYPE type, IoPro ioPro, IoProTbl ioProTbl);
void        k_io_test_iip_test(KIoTest *self);
void        k_io_test_audio_test(KIoTest *self);
void        k_io_test_hdmi_test(KIoTest *self);

#endif/*__K_IO_TEST_H__*/
