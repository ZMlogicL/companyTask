/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-05
*@author            :陈倩
*@brief             :kjdscnr1a
*@rely              :klib
*@function
*设计的主要功能:
*1、
*2、
*3、
*4、
*5、
*@version
*
*/


#ifndef __K_JDSCNR1A_H__
#define __K_JDSCNR1A_H__


#include <klib.h>
#include "_jdscnr_otf_reg_rw.h"
#include "_jdscnr_cspr_reg.h"
#include "_jdscnr_ofl_reg_rw.h"
#include "_jdscnr_ofl_reg_yspr.h"


#define K_TYPE_JDSCNR1A				(k_jdscnr1a_get_type())
#define K_JDSCNR1A(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdscnr1a))
#define K_IS_JDSCNR1A(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSCNR1A))


typedef struct _KJdscnr1a				KJdscnr1a;
typedef struct _KJdscnr1aPrivate	KJdscnr1aPrivate;

struct  _KJdscnr1a
{
	KObject parent;
};


/* Define i/o mapping */
typedef struct _IoCnrReg
{
	/* JDSIMG */
	/* 2842_(0000 - 0FFFh) */
	struct IoCnrOtfRegRw otfRegRw;
	/* 2842_(1000 - 1FFFh) */
	struct IoCnrCsprReg otfCsprReg;
	/* 2842_(2000 - 2FFFh) */
	struct IoCnrOflRegRw oflRegRw;
	/* 2842_(3000 - 3FFFh) */
	struct IoCnrCsprReg oflCsprReg;
	/* 2842_(4000 - 4FFFh) */
	struct IoCnrOflRegYspr oflRegYspr;
	/* 2842_5000 - 2842_FFFFh */
	unsigned char dmy284250002842ffff[0x28430000 - 0x28425000];

} IoCnrReg;

extern volatile IoCnrReg		ioCnr1;
extern volatile IoCnrReg		ioCnr2;
extern volatile IoCnrReg		ioCnr3;


KConstType	k_jdscnr1a_get_type(void);
KJdscnr1a*	k_jdscnr1a_new(void);


#endif/*__K_JDSCNR1A_H__*/

