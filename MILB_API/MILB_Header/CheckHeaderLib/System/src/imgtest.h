/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :陈柱
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/
#ifndef __IMG_TEST_H__
#define __IMG_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define IMG_TYPE_TEST								(img_test_get_type())
#define IMG_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, IMG_TYPE_TEST, ImgTest))
#define IMG_TEST_CALSS(klass)              	(G_TYPE_CHECK_CLASS_CAST((klass), IMG_TYPE_TEST, ImgTestClass))
#define IMG_IS_TEST(obj)                        	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IMG_TYPE_TEST))
#define IMG_IS_TEST_CLASS(klass)         	(G_TYPE_CHECK_CLASS_TYPE ((klass), IMG_TYPE_TEST))
#define IMG_TEST_GET_CLASS(obj)         	(G_TYPE_INSTANCE_GET_CLASS ((obj), IMG_TYPE_TEST, ImgTestClass))


typedef struct _ImgTest                       	ImgTest;
typedef struct _ImgTestClass            		ImgTestClass;
typedef struct _ImgTestPrivate           	ImgTestPrivate;


struct _ImgTest
{
	AbsHeaderTest    parent;
};

struct _ImgTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						img_test_get_type(void) G_GNUC_CONST;
ImgTest *         		img_test_new(void);


G_END_DECLS


#endif /* __IMG_TEST_H__ */
