/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __JDSPRO_PWCH_H__
#define __JDSPRO_PWCH_H__


#include <klib.h>


#define JDSPRO_TYPE_PWCH				(jdspro_pwch_get_type())
#define JDSPRO_PWCH(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsproPwch))
#define JDSPRO_IS_PWCH(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSPRO_TYPE_PWCH))


typedef union 				_IoPwchtrg IoPwchtrg;
typedef union 				_IoPws IoPws;
typedef union 				_IoPwaxctl IoPwaxctl;
typedef union 				_IoPwchctl IoPwchctl;
typedef union 				_IoPwchintenb IoPwchintenb;
typedef union 				_IoPwchintflg IoPwchintflg;
typedef union 				_IoPwchbresp IoPwchbresp;
typedef union 				_IoPwsa IoPwsa;
typedef union 				_IoPwlsize IoPwlsize;
typedef union 				_IoPwdw IoPwdw;
typedef union 				_IoPwvfm IoPwvfm;
typedef struct 				_IoPwch IoPwch;
typedef struct 				_JdsproPwch JdsproPwch;
typedef struct 				_JdsproPwchPrivate	JdsproPwchPrivate;

/*  structure of PWCHTRG    (2800_C800h)    */
union _IoPwchtrg{
    kulong       word;
    struct {
        kulong   pwchtrg :2;
        kulong           :30;
    }bit;
};

/*  structure of PWS    (2800_C804h)    */
union _IoPws{
    kulong       word;
    struct {
        kulong   pws :1;
        kulong       :31;
    }bit;
};

/*  structure of PWAXCTL    (2800_C808h)    */
union _IoPwaxctl{
    kulong       word;
    struct {
        kulong   awcache :4;
        kulong           :4;
        kulong   awprot  :3;
        kulong           :21;
    }bit;
};

/*  structure of PWCHCTL    (2800_C80Ch)    */
union _IoPwchctl{
    kulong       word;
    struct {
        kulong   pwbmd   :2;
        kulong           :2;
        kulong   pwlv    :3;
        kulong           :1;
        kulong   pwmw    :1;
        kulong           :23;
    }bit;
};

/*  structure of PWCHINTENB (2800_C810h)    */
union _IoPwchintenb{
    kulong       word;
    struct {
        kulong   pwe     :1;
        kulong           :3;
        kulong   pwee    :1;
        kulong           :3;
        kulong   pwxe    :1;
        kulong           :23;
    }bit;
};

/*  structure of PWCHINTFLG (2800_C814h)    */
union _IoPwchintflg{
    kulong       word;
    struct {
        kulong   pwfTemp2     :1;
        kulong             :3;
        kulong   pwefTemp2    :1;
        kulong             :3;
        kulong   pwxfTemp2    :1;
        kulong             :23;
    }bit;
};

/*  structure of PWCHBRESP  (2800_C818h)    */
union _IoPwchbresp{
    kulong       word;
    struct {
        kulong   pwchbresp   :2;
        kulong               :30;
    }bit;
};

/*  structure of PWSA   (2800_C81Ch)    */
union _IoPwsa{
    kulong       word;
    struct {
        kulong   pwsa    :32;
    }bit;
};

/*  structure of PWLSIZE    (2800_C820h)    */
union _IoPwlsize{
    kulong       word;
    struct {
        kulong   pwlsize :32;
    }bit;
};

/*  structure of PWDW   (2800_C824h)    */
union _IoPwdw{
    kulong       word;
    struct {
        kulong   pwdw    :2;
        kulong           :30;
    }bit;
};

/*  structure of PWVFM  (2800_C828h)    */
union _IoPwvfm{
    kulong       word;
    struct {
        kulong   pwvfm   :1;
        kulong           :31;
    }bit;
};

/* Define i/o mapping */
struct _IoPwch{
    /* JDSIMG */
	/* 2800_(C800 - C803h) */
	IoPwchtrg       pwchtrg;
	/* 2800_(C804 - C807h) */
	IoPws           pws;
	/* 2800_(C808 - C80Bh) */
	IoPwaxctl       pwaxctl;
	/* 2800_(C80C - C80Fh) */
	IoPwchctl       pwchctl;
	/* 2800_(C810 - C813h) */
	IoPwchintenb    pwchintenb;
	/* 2800_(C814 - C817h) */
	IoPwchintflg    pwchintflg;
	/* 2800_(C818 - C81Bh) */
	IoPwchbresp     pwchbresp;
	/* 2800_(C81C - C81Fh) */
	IoPwsa          pwsa;
	/* 2800_(C820 - C823h) */
	IoPwlsize       pwlsize;
	/* 2800_(C824 - C827h) */
	IoPwdw          pwdw;
	/* 2800_(C828 - C82Bh) */
	IoPwvfm         pwvfm;
	/* 2800_(C82C - C8FFh) */
    kuchar dmyC82cC8ff[0xC900-0xC82C];
};

struct  _JdsproPwch
{
	KObject parent;
};


KConstType				jdspro_pwch_get_type(void);
JdsproPwch*			jdspro_pwch_new(void);


#endif/*__JDSPRO_PWCH_H__*/
