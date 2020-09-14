/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :郑蛘钊
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#ifndef __MXIC_TEST_H__
#define __MXIC_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define MXIC_TYPE_TEST				   (mxic_test_get_type())
#define MXIC_TEST(obj)				   (G_TYPE_CHECK_INSTANCE_CAST(obj, MXIC_TYPE_TEST, Mxic))
#define MXIC_TEST_CALSS(klass)         (G_TYPE_CHECK_CLASS_CAST((klass), MXIC_TYPE_TEST, MxicClass))
#define MXIC_IS_TEST(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MXIC_TYPE_TEST))
#define MXIC_IS_TEST_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), MXIC_TYPE_TEST))
#define MXIC_TEST_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), MXIC_TYPE_TEST, MxicClass))


typedef struct _Mxic                    Mxic;
typedef struct _MxicClass            	MxicClass;
typedef struct _MxicPrivate           	MxicPrivate;


struct _Mxic
{
	AbsHeaderTest    parent;
};

struct _MxicClass
{
	AbsHeaderTestClass    parentclass;
};


GType 		mxic_test_get_type(void) G_GNUC_CONST;
Mxic*       mxic_test_new(void);
void        mxic_test(Mxic* self);


G_END_DECLS


#endif /* __MXIC_TEST_H__ */
