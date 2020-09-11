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
#ifndef __CHECK_MAIN_H__
#define __CHECK_MAIN_H__


#include <stdio.h>
#include <glib-object.h>


G_BEGIN_DECLS


#define CHECK_TYPE_MAIN									(check_main_get_type())
#define CHECK_MAIN(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, CHECK_TYPE_MAIN, CheckMain))
#define CHECK_MAIN_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), CHECK_TYPE_MAIN, CheckMainClass))
#define CHECK_IS_MAIN(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHECK_TYPE_MAIN))
#define CHECK_IS_MAIN_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), CHECK_TYPE_MAIN))
#define CHECK_MAIN_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), CHECK_TYPE_MAIN, CheckMainClass))


typedef struct _CheckMain                       	CheckMain;
typedef struct _CheckMainClass            		CheckMainClass;
typedef struct _CheckMainPrivate           	CheckMainPrivate;


struct _CheckMain
{
	GObject    parent;
};

struct _CheckMainClass
{
	GObjectClass    parentclass;
};


GType 							check_main_get_type(void) G_GNUC_CONST;
CheckMain *         		check_main_new(void);


G_END_DECLS


#endif /* __CHECK_MAIN_H__ */
