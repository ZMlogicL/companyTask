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

void  palladium_test_r2y_com_do_test_3_1(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_2(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_3(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_4(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_5(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_6(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_12(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_13(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_14(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_15(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_16(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_17(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_18(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_19(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_20(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_21(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_22(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_23(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_24(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_25(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_26(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_27(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_28(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_29(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_30(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_31(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );
void  palladium_test_r2y_com_do_test_3_32(PalladiumTestR2yCom* self, const kuint32 ctIdx1st,
					const kuint32 ctIdx2nd, const kuint32 ctIdx3rd );

#endif /* __PALLADIUM_TEST_R2Y_COM_H__ */
