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
#ifndef __ABS_HEADER_TEST_H__
#define __ABS_HEADER_TEST_H__


#include <stdio.h>
#include <glib-object.h>


G_BEGIN_DECLS


#define ABS_TYPE_HEADER_TEST								(abs_header_test_get_type())
#define ABS_HEADER_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, ABS_TYPE_HEADER_TEST, AbsHeaderTest))
#define ABS_HEADER_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), ABS_TYPE_HEADER_TEST, AbsHeaderTestClass))
#define ABS_IS_HEADER(obj)                        				(G_TYPE_CHECK_INSTANCE_TYPE ((obj), ABS_TYPE_HEADER_TEST))
#define ABS_IS_HEADER_CLASS(klass)         				(G_TYPE_CHECK_CLASS_TYPE ((klass), ABS_TYPE_HEADER_TEST))
#define ABS_HEADER_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), ABS_TYPE_HEADER_TEST, AbsHeaderTestClass))


typedef struct _AbsHeaderTest                       	AbsHeaderTest;
typedef struct _AbsHeaderTestClass            		AbsHeaderTestClass;
typedef struct _AbsHeaderTestPrivate           		AbsHeaderTestPrivate;


struct _AbsHeaderTest
{
	GObject    parent;
};

struct _AbsHeaderTestClass
{
	GObjectClass    	parentclass;
	void 					(*run) (AbsHeaderTest *self);
};


GType 									abs_header_test_get_type(void) G_GNUC_CONST;
AbsHeaderTest *         		abs_header_test_new(void);


G_END_DECLS


#endif /* __ABS_HEADER_TEST_H__ */
