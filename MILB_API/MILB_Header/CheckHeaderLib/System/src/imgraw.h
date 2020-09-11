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
#ifndef __IMG_RAW_H__
#define __IMG_RAW_H__


#include <stdio.h>
#include <glib-object.h>
#include "absheadertest.h"


G_BEGIN_DECLS


#define IMG_TYPE_RAW								(img_raw_get_type())
#define IMG_RAW(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, IMG_TYPE_RAW, ImgRaw))
#define IMG_RAW_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), IMG_TYPE_RAW, ImgRawClass))
#define IMG_IS_RAW(obj)                        	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IMG_TYPE_RAW))
#define IMG_IS_RAW_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), IMG_TYPE_RAW))
#define IMG_RAW_GET_CLASS(obj)         	(G_TYPE_INSTANCE_GET_CLASS ((obj), IMG_TYPE_RAW, ImgRawClass))


typedef struct _ImgRaw                       	ImgRaw;
typedef struct _ImgRawClass            		ImgRawClass;
typedef struct _ImgRawPrivate           	ImgRawPrivate;


struct _ImgRaw
{
	AbsHeaderTest    parent;
};

struct _ImgRawClass
{
	AbsHeaderTestClass    parentclass;
};


GType 						img_raw_get_type(void) G_GNUC_CONST;
ImgRaw *         		img_raw_new(void);


G_END_DECLS


#endif /* __IMG_RAW_H__ */
