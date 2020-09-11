/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :申雨
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/


#ifndef __SPI_TEST_H__
#define __SPI_TEST_H__


#include <stdio.h>
#include <glib-object.h>
#include "internals.h"
#include "absheadertest.h"


G_BEGIN_DECLS


#define SPI_TYPE_TEST								(spi_test_get_type())
#define SPI_TEST(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, SPI_TYPE_TEST, SpiTest))
#define SPI_TEST_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), SPI_TYPE_TEST, SpiTestClass))
#define SPI_IS_TEST(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), SPI_TYPE_TEST))
#define SPI_IS_TEST_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), SPI_TYPE_TEST))
#define SPI_TEST_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), SPI_TYPE_TEST, SpiTestClass))


typedef struct _SpiTest                       	SpiTest;
typedef struct _SpiTestClass            	SpiTestClass;
typedef struct _SpiTestPrivate           	SpiTestPrivate;

struct _SpiTest
{
	AbsHeaderTest    parent;
};

struct _SpiTestClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						spi_test_get_type(void) G_GNUC_CONST;
SpiTest *         			spi_test_new(void);
void 						spi_test();


G_END_DECLS


#endif /* __SPI_TEST_H__ */
