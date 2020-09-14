/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/


#ifndef __CHECK_HEADER_MAIN_DEFS_H__
#define __CHECK_HEADER_MAIN_DEFS_H__


#include <klib.h>
#if 0
#include "jdspro.h"
#endif


#define CheckHeaderMain_RS_PRINTF printf


typedef enum _EProBlockType{
	CheckHeaderMain_E_PRO_BLOCK_TYPE_SEN	= 0,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO1,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO2,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO3,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B1,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B2,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B3,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_STAT,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_PAS,
	CheckHeaderMain_E_PRO_BLOCK_TYPE_TABLE,
} EProBlockType;


#endif /* __CHECK_HEADER_MAIN_DEFS_H__ */
