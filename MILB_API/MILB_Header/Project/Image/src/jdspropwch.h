/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-09
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
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


#include <stdio.h>
#include <glib-object.h>


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

/*  structure of PWCHTRG    (2800_C800h)    */
union _IoPwchtrg{
    gulong       word;
    struct {
        gulong   pwchtrg :2;
        gulong           :30;
    }bit;
};

/*  structure of PWS    (2800_C804h)    */
union _IoPws{
    gulong       word;
    struct {
        gulong   pws :1;
        gulong       :31;
    }bit;
};

/*  structure of PWAXCTL    (2800_C808h)    */
union _IoPwaxctl{
    gulong       word;
    struct {
        gulong   awcache :4;
        gulong           :4;
        gulong   awprot  :3;
        gulong           :21;
    }bit;
};

/*  structure of PWCHCTL    (2800_C80Ch)    */
union _IoPwchctl{
    gulong       word;
    struct {
        gulong   pwbmd   :2;
        gulong           :2;
        gulong   pwlv    :3;
        gulong           :1;
        gulong   pwmw    :1;
        gulong           :23;
    }bit;
};

/*  structure of PWCHINTENB (2800_C810h)    */
union _IoPwchintenb{
    gulong       word;
    struct {
        gulong   pwe     :1;
        gulong           :3;
        gulong   pwee    :1;
        gulong           :3;
        gulong   pwxe    :1;
        gulong           :23;
    }bit;
};

/*  structure of PWCHINTFLG (2800_C814h)    */
union _IoPwchintflg{
    gulong       word;
    struct {
        gulong   pwfTemp2     :1;
        gulong             :3;
        gulong   pwefTemp2    :1;
        gulong             :3;
        gulong   pwxfTemp2    :1;
        gulong             :23;
    }bit;
};

/*  structure of PWCHBRESP  (2800_C818h)    */
union _IoPwchbresp{
    gulong       word;
    struct {
        gulong   pwchbresp   :2;
        gulong               :30;
    }bit;
};

/*  structure of PWSA   (2800_C81Ch)    */
union _IoPwsa{
    gulong       word;
    struct {
        gulong   pwsa    :32;
    }bit;
};

/*  structure of PWLSIZE    (2800_C820h)    */
union _IoPwlsize{
    gulong       word;
    struct {
        gulong   pwlsize :32;
    }bit;
};

/*  structure of PWDW   (2800_C824h)    */
union _IoPwdw{
    gulong       word;
    struct {
        gulong   pwdw    :2;
        gulong           :30;
    }bit;
};

/*  structure of PWVFM  (2800_C828h)    */
union _IoPwvfm{
    gulong       word;
    struct {
        gulong   pwvfm   :1;
        gulong           :31;
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
    guchar dmyC82cC8ff[0xC900-0xC82C];
};


#endif/*__JDSPRO_PWCH_H__*/
