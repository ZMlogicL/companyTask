/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-08
*@author : aorongxing
*@brief : PalladiumTestR2yCom
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 
*
*/


#ifndef __PALLADIUM_TEST_R2Y_COM_H__
#define __PALLADIUM_TEST_R2Y_COM_H__


#include <klib.h>


#define PALLADIUM_TYPE_TEST_R2Y_COM                  (palladium_test_r2y_com_get_type())
#define PALLADIUM_TEST_R2Y_COM(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, PalladiumTestR2yCom)) 
#define PALLADIUM_IS_TEST_R2Y_COM(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, PALLADIUM_TYPE_TEST_R2Y_COM))


typedef struct _PalladiumTestR2yCom PalladiumTestR2yCom;
typedef struct _PalladiumTestR2yComPrivate PalladiumTestR2yComPrivate;

struct _PalladiumTestR2yCom 
{
	KObject parent;
};


KConstType palladium_test_r2y_com_get_type(void);
PalladiumTestR2yCom* palladium_test_r2y_com_new(void);
PalladiumTestR2yCom* palladium_test_r2y_com_get(void);

VOID pt_im_r2y_do_test_3_1( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_2( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_3( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_4( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_5( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_6( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_12( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_13( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_14( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_15( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_16( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_17( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_18( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_19( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_20( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_21( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_22( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_23( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_24( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_25( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_26( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_27( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_28( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_29( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_30( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_31( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );
VOID pt_im_r2y_do_test_3_32( const UINT32 ctIdx1st, const UINT32 ctIdx2nd, const UINT32 ctIdx3rd );

#endif /* __PALLADIUM_TEST_R2Y_COM_H__ */
