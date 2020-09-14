/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-08
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


#ifndef __K_JDSDISP3A_H__
#define __K_JDSDISP3A_H__


#include <stdio.h>
#include <glib-object.h>
#include "jdsdisplch.h"
#include "jdsdispdcore.h"
#include "jdsdispgrch.h"
#include "jdsdispdbg.h"
#include "jdsdispdsi.h"
#include "jdsdisphdmi.h"
#include "jdsprop2m.h"
#include "jdspropwch.h"
#include "fhdmitx2p0lp1.h"
#include "fhdmitx2p0lp2.h"
#include "fhdmitx2p0lp3.h"
#include "fmipidsi11txlp.h"
#include "jdsdisplchtbl.h"
#include "jdsdispdcoretbl.h"


G_BEGIN_DECLS


#define K_TYPE_JDSDISP3A									(k_jdsdisp3a_get_type())
#define K_JDSDISP3A(obj)									(G_TYPE_CHECK_INSTANCE_CAST(obj, K_TYPE_JDSDISP3A, KJdsdisp3a))
#define K_JDSDISP3A_CALSS(klass)              		(G_TYPE_CHECK_CLASS_CAST((klass), K_TYPE_JDSDISP3A, KJdsdisp3aClass))
#define K_IS_JDSDISP3A(obj)                        		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), K_TYPE_JDSDISP3A))
#define K_IS_JDSDISP3A_CLASS(klass)         		(G_TYPE_CHECK_CLASS_TYPE ((klass), K_TYPE_JDSDISP3A))
#define K_JDSDISP3A_GET_CLASS(obj)         		(G_TYPE_INSTANCE_GET_CLASS ((obj), K_TYPE_JDSDISP3A, KJdsdisp3aClass))


typedef struct 				_IoJdsdispMain IoJdsdispMain;
typedef struct 				_IoJdsdispTop IoJdsdispTop;
typedef struct 				_IoJdsdispMainTbl IoJdsdispMainTbl;
typedef struct 				_IoJdsdispTbl IoJdsdispTbl;
typedef struct 				_KJdsdisp3a  KJdsdisp3a;
typedef struct 				_KJdsdisp3aClass  KJdsdisp3aClass;
typedef struct 				_KJdsdisp3aPrivate  KJdsdisp3aPrivate;

/* Define i/o mapping */

/* main (Common block 0/1) */
struct _IoJdsdispMain {
	/* 2890_(0000 - 0FFFh) */
	IoJdslchReg lch;
	/* 2890_(1000 - 1FFFh) */
	IoJdsdcoreReg dcore;
	/* 2890_(2000 - 3FFFh) */
	IoJdsgrchReg grch[2];
};

/* DISP TOP */
struct _IoJdsdispTop {
	/* JDSIMG */
	/* 2890_(0000 - 7FFFh) */
	IoJdsdispMain main[2];
	/* 2890_(8000 - AFFFh) */
	guchar dmy8000Afff[0xB000 - 0x8000];
	/* 2890_(B000 - BFFFh) */
	IoJdsddbgReg dbgctl;
	/* 2890_(C000 - CFFFh) */
	IoFMipidsi11txLp mipiDsi;
	/* 2890_(D000 - DFFFh) */
	IoJdsdispDsi mdsctl;
	/* 2890_(E000 - EFFFh) */
	IoJddispHdmi jddispHdmiHdmic;
	/* 2890_F000 - 2890_FFFFh */
	guchar dmy2890f0002890ffff[0x28910000 - 0x2890F000];
	/* 2891_(0000 - 01FFh) */
	IoP2m p2m[2];
	/* 2891_(0200 - 03FFh) */
	IoPwch pwch[2];
	/* 2891_0400 - 2891_FFFFh */
	guchar dmy289104002891ffff[0x28920000 - 0x28910400];
	/* 2892_0000 - 2893_FFFFh */
	IoFHdmitx2p0Lp hdmiTx;
};

/* Define i/o mapping */

/* main (Common block 0/1) */
struct _IoJdsdispMainTbl {
	/* 298E_(0000 - 3FFFh) */
	IoJdslchTbl    lch;
    /* 298E_(4000 - 7FFFh) */
	IoJdsdcoreTbl  dcore;
    /* 298E_(8000 - FFFFh) */
    guchar dmy8000ffff[0x10000-0x8000];
};

/* DISP TBL */
struct _IoJdsdispTbl {
	/* JDSIMG */
	/* 298E_0000 - 298F_FFFFh */
	IoJdsdispMainTbl main[2];
};

struct _KJdsdisp3a
{
	GObject    parent;
};

struct _KJdsdisp3aClass
{
	GObject    parentclass;
};

extern volatile IoJdsdispTop	ioDisp;
extern volatile IoJdsdispTbl	ioDispTbl;


GType 							k_jdsdisp3a_get_type(void) G_GNUC_CONST;
KJdsdisp3a *         		k_jdsdisp3a_new(void);


G_END_DECLS


#endif/*__K_JDSDISP3A_H__*/
