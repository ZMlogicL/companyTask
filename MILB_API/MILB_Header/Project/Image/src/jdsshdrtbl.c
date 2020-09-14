/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-10
 *@author            :郑蛘钊
 *@brief             :jdsshdrtbl
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#include "jdsshdrtbl.h"


K_TYPE_DEFINE_WITH_PRIVATE(JdsshdrTbl, jdsshdr_tbl);

#define JDSSHDR_TBL_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), JdsshdrTblPrivate, JDSSHDR_TYPE_TBL))


struct _JdsshdrTblPrivate
{

};
/**
 *IMPL
 */
static void jdsshdr_tbl_constructor(JdsshdrTbl *self)
{
    //JdsshdrTblPrivate *priv = JDSSHDR_TBL_GET_PRIVATE(self);
}

static void jdsshdr_tbl_destructor(JdsshdrTbl *self)
{
    //JdsshdrTblPrivate *priv = JDSSHDR_TBL_GET_PRIVATE(self);
}
/**
 *PUBLIC
 */
JdsshdrTbl* jdsshdr_tbl_new(void)
{
    JdsshdrTbl* self = k_object_new_with_private(JDSSHDR_TYPE_TBL, sizeof(JdsshdrTblPrivate));
    return self;
}
