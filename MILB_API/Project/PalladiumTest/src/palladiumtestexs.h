/*
*@Copyright (C) 2010-2015 上海网用软件有限公司
*@date                :2020-04-20
*@author              :
*@brief               :snsnet网络协议栈
*@rely                :klib
*@function
*SNSNET，采用ETK-C语言编写
*设计的主要功能:
*@version
*1.0.0 2020年04月开始开发
*/

#ifndef __PALLADIUM_TEST_EXS_H__
#define __PALLADIUM_TEST_EXS_H__

#include <klib.h>
#include "ddim_user_custom.h"
#include "palladium_test_common.h"
#include "palladium_test.h"
#include "dd_gic.h"
#include "dd_top.h"


#define PALLADIUM_TYPE_TEST_EXS		(palladium_test_exs_get_type())
#define PALLADIUM_TEST_EXS(obj) 		K_TYPE_CHECK_INSTANCE_CAST(obj, PalladiumTestExs)
#define PALLADIUM_IS_TEST_EXS(obj) 	K_TYPE_CHECK_INSTANCE_TYPE(obj, PALLADIUM_TYPE_TEST_EXS)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define PalladiumTestExs_PT_DD_EXS_CMD_LEN			(20)


typedef struct _PalladiumTestExs 				PalladiumTestExs;
typedef struct _PalladiumTestExsPrivate 	PalladiumTestExsPrivate;

struct _PalladiumTestExs {
	KObject parent;
};


KConstType 					palladium_test_exs_get_type(void);
PalladiumTestExs* 		palladium_test_exs_new(void);

VOID 								palladium_test_exs_dd_exs_main( VOID );
void 								palladium_test_exs_execute_cmd(int cmdArgc, char* cmdArgv);

#endif /* __PALLADIUM_TEST_EXS_H__ */

