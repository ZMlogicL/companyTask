/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : CtImPro
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

//#define CO_CT_IM_PRO_DISABLE
#ifndef CO_CT_IM_PRO_DISABLE
/*----------------------------------------------------------------------*/
/* Definition                                                           */
/*----------------------------------------------------------------------*/
#define D_FUNC_TABLE_CATE_NUM	(8)
#define D_FUNC_TABLE_FUNC_NUM	(100)
/*----------------------------------------------------------------------*/
/* Enumeration                                                          */
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure                                                            */
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data                                                          */
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Method Definition                                              */
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Function                                                       */
/*----------------------------------------------------------------------*/
#ifdef CO_PRO_DEBUG_PRINT_FUNC
extern void Im_PRO_Print_ClockStatus( void );
#endif  // CO_PRO_DEBUG_PRINT_FUNC

typedef void (*T_ct_im_pro_Func)( const kuint32 idx );
#endif


