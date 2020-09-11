/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsela2d
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


#ifndef __K_JDSELA2D_H__
#define __K_JDSELA2D_H__


#include <klib.h>


#define K_TYPE_JDSELA2D			(k_jdsela2d_get_type())
#define K_JDSELA2D(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsela2d))
#define K_IS_JDSELA2D(obj)		(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSELA2D))


typedef struct _KJdsela2d				KJdsela2d;
typedef struct _KJdsela2dPrivate	KJdsela2dPrivate;

struct  _KJdsela2d
{
	KObject parent;
};


/*  structure of earcache   (288B_0000h)    */
typedef union _IoElaEarcache
{
	unsigned long word;
	struct {
		unsigned long earcache0 :4;
		unsigned long :4;
		unsigned long earcache1 :4;
		unsigned long :4;
		unsigned long earcache2 :4;
		unsigned long :4;
		unsigned long :8;
	} bit;
} IoElaEarcache;

/*  structure of eawcache   (288B_0004h)    */
typedef union _IoElaEawcache
{
	unsigned long word;
	struct {
		unsigned long eawcache0 :4;
		unsigned long :4;
		unsigned long eawcache1 :4;
		unsigned long :4;
		unsigned long eawcache2 :4;
		unsigned long :4;
		unsigned long :8;
	} bit;
} IoElaEawcache;

/*  structure of earprot    (288B_0008h)    */
typedef union _IoElaEarprot{
    unsigned long       word;
	struct {
		unsigned long earprot0 :3;
		unsigned long :5;
		unsigned long earprot1 :3;
		unsigned long :5;
		unsigned long earprot2 :3;
		unsigned long :5;
		unsigned long :8;
	} bit;
} IoElaEarprot;

/*  structure of eawprot    (288B_000Ch)    */
typedef union _IoElaEawprot
{
	unsigned long word;
	struct {
		unsigned long eawprot0 :3;
		unsigned long :5;
		unsigned long eawprot1 :3;
		unsigned long :5;
		unsigned long eawprot2 :3;
		unsigned long :5;
		unsigned long :8;
	} bit;
} IoElaEawprot;

/*  structure of earaxsts   (288B_0010h)    */
typedef union _IoElaEaraxsts
{
	unsigned long word;
	struct {
		unsigned long rresp0 :2;
		unsigned long :6;
		unsigned long rresp1 :2;
		unsigned long :6;
		unsigned long rresp2 :2;
		unsigned long :6;
		unsigned long :8;
	} bit;
} IoElaEaraxsts;

/*  structure of eawaxsts   (288B_0014h)    */
typedef union _IoElaEawaxsts
{
	unsigned long word;
	struct {
		unsigned long bresp0 :2;
		unsigned long :6;
		unsigned long bresp1 :2;
		unsigned long :6;
		unsigned long bresp2 :2;
		unsigned long :6;
		unsigned long :8;
	} bit;
} IoElaEawaxsts;

/*  structure of earreqmsk  (288B_0020h)    */
typedef union _IoElaEarreqmsk1
{
	unsigned long word;
	struct {
		unsigned long earreqmsk00 :12;
		unsigned long :4;
		unsigned long earreqmsk11 :12;
		unsigned long :4;
	} bit;
} IoElaEarreqmsk1;

typedef union _IoElaEarreqmsk2
{
	unsigned long word;
	struct {
		unsigned long earreqmsk22 :12;
		unsigned long :4;
		unsigned long :16;
	} bit;
} IoElaEarreqmsk2;

typedef struct _IoElaEarreqmsk
{
	IoElaEarreqmsk1 earreqmsk1;
	IoElaEarreqmsk2 earreqmsk2;
} IoElaEarreqmsk;

/*  structure of eawreqmsk  (288B_0028h)    */
typedef union _ioElaEawreqmsk1
{
	unsigned long word;
	struct {
		unsigned long eawreqmsk0 :12;
		unsigned long :4;
		unsigned long eawreqmsk11 :12;
		unsigned long :4;
	} bit;
} ioElaEawreqmsk1;

typedef union _IoElaEawreqmsk2
{
	unsigned long word;
	struct {
		unsigned long eawreqmsk22 :12;
		unsigned long :4;
		unsigned long :16;
	} bit;
} IoElaEawreqmsk2;

typedef struct _IoElaEawreqmsk
{
	ioElaEawreqmsk1 eawreqmsk1;
	IoElaEawreqmsk2 eawreqmsk2;
} IoElaEawreqmsk;

/*  structure of elainte    (288B_0100h)    */
typedef union _IoElaElainte
{
	unsigned long word;
	struct {
		unsigned long :1;
		unsigned long enwe :1;
		unsigned long :2;
		unsigned long axrere :1;
		unsigned long axwere :1;
		unsigned long :26;
	} bit;
} IoElaElainte;

/*  structure of elaintf    (288B_0104h)    */
typedef union _IoElaElaintf
{
	unsigned long word;
	struct {
		unsigned long :1;
		unsigned long __enwf :1;
		unsigned long :2;
		unsigned long __axrerf :1;
		unsigned long __axwerf :1;
		unsigned long :26;
	} bit;
} IoElaElaintf;

/*  structure of sramact    (288B_0108h)    */
typedef union _IoElaSramact
{
	unsigned long word;
	struct {
		unsigned long sramact :2;
		unsigned long :30;
	} bit;
} IoElaSramact;

/*  structure of elatrg (288B_0110h)    */
typedef union _IoElaElatrg
{
	unsigned long word;
	struct {
		unsigned long elatrg :2;
		unsigned long :30;
	} bit;
} IoElaElatrg;

/*  structure of elactl (288B_0114h)    */
typedef union _IoElaElactl
{
	unsigned long word;
	struct {
		unsigned long elacnt :3;
		unsigned long :1;
		unsigned long elamd :2;
		unsigned long :1;
		unsigned long elaact :1;
		unsigned long :24;
	} bit;
} IoElaElactl;

/*  structure of elabyr (288B_0118h)    */
typedef union _IoElaElabyr
{
	unsigned long word;
	struct {
		unsigned long eirtyp :2;
		unsigned long :2;
		unsigned long eirsft :2;
		unsigned long :2;
		unsigned long eiwsft :2;
		unsigned long :2;
		unsigned long eiwtyp :2;
		unsigned long :2;
		unsigned long eiwout :2;
		unsigned long :2;
		unsigned long dknen :1;
		unsigned long eobaen :1;
		unsigned long :2;
		unsigned long :4;
		unsigned long dknact :1;
		unsigned long :3;
	} bit;
} IoElaElabyr;

/*  structure of nslmd  (288B_011Ch)    */
typedef union _IoElaNslmd
{
	unsigned long word;
	struct {
		unsigned long nslmd :1;
		unsigned long :3;
		unsigned long nslres :2;
		unsigned long :2;
		unsigned long nslkne :1;
		unsigned long :23;
	} bit;
} IoElaNslmd;

/*  structure of obof   (288B_0120h)    */
typedef union _IoElaObof1
{
	unsigned long word;
	struct {
		long eobrr :11;
		unsigned long :5;
		long eobbb :11;
		unsigned long :5;
	} bit;
} IoElaObof1;

typedef union _IoElaObof2
{
	unsigned long word;
	struct {
		long eobgr :11;
		unsigned long :5;
		long eobgb :11;
		unsigned long :5;
	} bit;
} IoElaObof2;

typedef struct _IoElaObof
{
	IoElaObof1 obof1;
	IoElaObof2 obof2;
} IoElaObof;

/*  structure of ezsfta1    (288B_0128h)    */
typedef union _IoElaEzsfta1
{
	unsigned long word;
	struct {
		long ezsfta1 :11;
		unsigned long :21;
	} bit;
} IoElaEzsfta1;

/*  structure of nslnglmt   (288B_012Ch)    */
typedef union _IoElaNslnglmt
{
	unsigned long word;
	struct {
		unsigned long nslnglmm :10;
		unsigned long :6;
		unsigned long nslnglmp :10;
		unsigned long :6;
	} bit;
} IoElaNslnglmt;

/*  structure of eira   (288B_0130h)    */
typedef union _IoElaEira
{
	unsigned long word;
	struct {
		unsigned long eira :32;
	} bit;
} IoElaEira;

/*  structure of eirofs (288B_0134h)    */
typedef union _IoElaEirofs
{
	unsigned long word;
	struct {
		unsigned long eirofs :3;
		unsigned long :29;
	} bit;
} IoElaEirofs;

/*  structure of eirdef (288B_0138h)    */
typedef union _IoElaEirdef
{
	unsigned long word;
	struct {
		unsigned long eirdef :15;
		unsigned long :17;
	} bit;
} IoElaEirdef;

/*  structure of eirhsiz    (288B_013Ch)    */
typedef union _IoElaEirhsiz
{
	unsigned long word;
	struct {
		unsigned long eirhsiz :14;
		unsigned long :18;
	} bit;
} IoElaEirhsiz;

/*  structure of eirvsiz    (288B_0140h)    */
typedef union _IoElaEirvsiz
{
	unsigned long word;
	struct {
		unsigned long eirvsiz :14;
		unsigned long :18;
	} bit;
} IoElaEirvsiz;

/*  structure of eiwa   (288B_0150h)    */
typedef union _IoElaEiwa
{
	unsigned long word[4];
	struct {
		unsigned long eiwa :32;
	} bit[4];
} IoElaEiwa;

/*  structure of eiwdef (288B_0160h)    */
typedef union _IoElaEiwdef{
	unsigned long word;
	struct {
		unsigned long eiwdef :14;
		unsigned long :18;
	} bit;
} IoElaEiwdef;

/*  structure of enwa   (288B_0164h)    */
typedef union _IoElaEnwa
{
	unsigned long word;
	struct {
		unsigned long enwa :32;
	} bit;
} IoElaEnwa;

/*  structure of enwdef (288B_0168h)    */
typedef union _IoElaEnwdef
{
	unsigned long word;
	struct {
		unsigned long enwdef :14;
		unsigned long :18;
	} bit;
} IoElaEnwdef;

/*  structure of enra   (288B_0180h)    */
typedef union _IoElaEnra
{
	unsigned long word[16];
	struct {
		unsigned long enra :32;
	} bit[16];
} IoElaEnra;

/*  structure of enrhsiz    (288B_01C0h)    */
typedef union _IoElaEnrhsiz
{
	unsigned long word;
	struct {
		unsigned long enrhsiz :14;
		unsigned long :18;
	} bit;
} IoElaEnrhsiz;

/*  structure of enrvsiz    (288B_01C4h)    */
typedef union _IoElaEnrvsiz
{
	unsigned long word;
	struct {
		unsigned long enrvsiz :14;
		unsigned long :18;
	} bit;
} IoElaEnrvsiz;

/*  structure of ensa   (288B_01C8h)    */
typedef union _IoElaEnsa
{
	unsigned long word;
	struct {
		unsigned long ensa :32;
	} bit;
} IoElaEnsa;

/*  structure of ensdef (288B_01CCh)    */
typedef union _IoElaEnsdef
{
	unsigned long word;
	struct {
		unsigned long ensdef :14;
		unsigned long :18;
	} bit;
} IoElaEnsdef;

/*  structure of enshsiz    (288B_01D0h)    */
typedef union _IoElaEnshsiz
{
	unsigned long word;
	struct {
		unsigned long enshsiz :14;
		unsigned long :18;
	} bit;
} IoElaEnshsiz;

/*  structure of ensvsiz    (288B_01D4h)    */
typedef union _IoElaEnsvsiz
{
	unsigned long word;
	struct {
		unsigned long ensvsiz :14;
		unsigned long :18;
	} bit;
} IoElaEnsvsiz;

/*  structure of byrtyp (288B_0200h)    */
typedef union _IoElaByrtyp
{
	unsigned long word;
	struct {
		unsigned long org :2;
		unsigned long :2;
		unsigned long eladcmd :2;
		unsigned long :26;
	} bit;
} IoElaByrtyp;

/*  structure of elfzp  (288B_0204h)    */
typedef union _IoElaElfzp
{
	unsigned long word;
	struct {
		unsigned long elfzp :12;
		unsigned long :20;
	} bit;
} IoElaElfzp;

/*  structure of elfl   (288B_0208h)    */
typedef union _EoElaElfl1
{
	unsigned long word;
	struct {
		unsigned long elfl11 :12;
		unsigned long :4;
		unsigned long elfl22 :12;
		unsigned long :4;
	} bit;
} EoElaElfl1;

typedef union _IoElaElfl2
{
	unsigned long word;
	struct {
		unsigned long elfl33 :12;
		unsigned long :4;
		unsigned long elfl44 :12;
		unsigned long :4;
	} bit;
} IoElaElfl2;

typedef struct _IoElaElfl
{
	EoElaElfl1 elfl1;
	IoElaElfl2 elfl2;
} IoElaElfl;

/*  structure of anbor  (288B_0210h)    */
typedef union _IoElaAnbor1
{
	unsigned long word;
	struct {
		unsigned long anbor0 :12;
		unsigned long :4;
		unsigned long anbor11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbor1;

typedef union _IoElaAnbor2
{
	unsigned long word;
	struct {
		unsigned long anbor22 :12;
		unsigned long :4;
		unsigned long anbor3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbor2;

typedef struct _IoElaAnbor
{
	IoElaAnbor1 anbor1;
	IoElaAnbor2 anbor2;
} IoElaAnbor;

/*  structure of anbkr  (288B_0218h)    */
typedef union _IoElaAnbkr1
{
	unsigned long word;
	struct {
		unsigned long anbkr0 :12;
		unsigned long :4;
		unsigned long anbkr11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkr1;

typedef union _IoElaAnbkr2
{
	unsigned long word;
	struct {
		unsigned long anbkr22 :12;
		unsigned long :4;
		unsigned long anbkr3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkr2;

typedef struct _IoElaAnbkr
{
	IoElaAnbkr1 anbkr1;
	IoElaAnbkr2 anbkr2;
} IoElaAnbkr;

/*  structure of anbdr  (288B_0220h)    */
typedef struct _IoElaAnbdr1
{
	unsigned long word;
	struct {
		unsigned long anbdr0 :12;
		unsigned long :4;
		unsigned long anbdr11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdr1;

typedef union _IoElaAnbdr2
{
	unsigned long word;
	struct {
		unsigned long anbdr22 :12;
		unsigned long :4;
		unsigned long anbdr3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdr2;

typedef struct _IoElaAnbdr
{
	IoElaAnbdr1 anbdr1;
	IoElaAnbdr2 anbdr2;
} IoElaAnbdr;

/*  structure of anbog  (288B_0228h)    */
typedef union _IoElaAnbog1
{
	unsigned long word;
	struct {
		unsigned long anbog0 :12;
		unsigned long :4;
		unsigned long anbog11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbog1;

typedef union _IoElaAnbog2
{
	unsigned long word;
	struct {
		unsigned long anbog22 :12;
		unsigned long :4;
		unsigned long anbog3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbog2;

typedef struct _IoElaAnbog
{
	IoElaAnbog1 anbog1;
	IoElaAnbog2 anbog2;
} IoElaAnbog;

/*  structure of anbkg  (288B_0230h)    */
typedef union _IoElaAnbkg1
{
	unsigned long word;
	struct {
		unsigned long anbkg0 :12;
		unsigned long :4;
		unsigned long anbkg11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkg1;

typedef union _IoElaAnbkg2
{
	unsigned long word;
	struct {
		unsigned long anbkg22 :12;
		unsigned long :4;
		unsigned long anbkg3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkg2;

typedef struct _IoElaAnbkg
{
	IoElaAnbkg1 anbkg1;
	IoElaAnbkg2 anbkg2;
} IoElaAnbkg;

/*  structure of anbdg  (288B_0238h)    */
typedef union _IoElaAnbdg1
{
	unsigned long word;
	struct {
		unsigned long anbdg0 :12;
		unsigned long :4;
		unsigned long anbdg11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdg1;

typedef union _IoElaAnbdg2
{
	unsigned long word;
	struct {
		unsigned long anbdg22 :12;
		unsigned long :4;
		unsigned long anbdg3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdg2;

typedef struct _IoElaAnbdg
{
	IoElaAnbdg1 anbdg1;
	IoElaAnbdg2 anbdg2;
} IoElaAnbdg;

/*  structure of anbob  (288B_0240h)    */
typedef union _IoElaAnbob1
{
	unsigned long word;
	struct {
		unsigned long anbob0 :12;
		unsigned long :4;
		unsigned long anbob11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbob1;

typedef union _IoElaAnbob2
{
	unsigned long word;
	struct {
		unsigned long anbob22 :12;
		unsigned long :4;
		unsigned long anbob3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbob2;

typedef struct _IoElaAnbob
{
	IoElaAnbob1 anbob1;
	IoElaAnbob2 anbob2;
} IoElaAnbob;

/*  structure of anbkb  (288B_0248h)    */
typedef union _IoElaAnbkb1
{
	unsigned long word;
	struct {
		unsigned long anbkb0 :12;
		unsigned long :4;
		unsigned long anbkb11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkb1;

typedef union _IoElaAnbkb2
{
	unsigned long word;
	struct {
		unsigned long anbkb22 :12;
		unsigned long :4;
		unsigned long anbkb3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbkb2;

typedef struct _IoElaAnbkb
{
	IoElaAnbkb1 anbkb1;
	IoElaAnbkb2 anbkb2;
} IoElaAnbkb;

/*  structure of anbdb  (288B_0250h)    */
typedef union _IoElaAnbdb1
{
	unsigned long word;
	struct {
		unsigned long anbdb0 :12;
		unsigned long :4;
		unsigned long anbdb11 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdb1;

typedef union _IoElaAnbdb2
{
	unsigned long word;
	struct {
		unsigned long anbdb22 :12;
		unsigned long :4;
		unsigned long anbdb3 :12;
		unsigned long :4;
	} bit;
} IoElaAnbdb2;

typedef struct _IoElaAnbdb
{
	IoElaAnbdb1 anbdb1;
	IoElaAnbdb2 anbdb2;
} IoElaAnbdb;

/*  structure of lgtw   (288B_0258h)    */
typedef union _IoElaLgtw1
{
	unsigned long word;
	struct {
		unsigned long lgtwr :10;
		unsigned long :6;
		unsigned long lgtwg :10;
		unsigned long :6;
	} bit;
} IoElaLgtw1;

typedef union _IoElaLgtw2
{
	unsigned long word;
	struct {
		unsigned long lgtwb :10;
		unsigned long :22;
	} bit;
} IoElaLgtw2;

typedef struct _IoElaLgtw
{
	IoElaLgtw1 lgtw1;
	IoElaLgtw2 lgtw2;
} IoElaLgtw;

/*  structure of lgt    (288B_0260h)    */
typedef union _IoElaLgt
{
	unsigned long word;
	struct {
		unsigned long lgtr :5;
		unsigned long :3;
		unsigned long lgtg :5;
		unsigned long :3;
		unsigned long lgtb :5;
		unsigned long :3;
		unsigned long lgtc :5;
		unsigned long :3;
	} bit;
} IoElaLgt;

/*  structure of lgte   (288B_0264h)    */
typedef union _IoElaLgte
{
	unsigned long word;
	struct {
		unsigned long lgter :5;
		unsigned long :3;
		unsigned long lgteg :5;
		unsigned long :3;
		unsigned long lgteb :5;
		unsigned long :11;
	} bit;
} IoElaLgte;

/*  structure of edg2anba   (288B_0268h)    */
typedef union _IoElaEdg2anba
{
	unsigned long word;
	struct {
		unsigned long edg2anba :8;
		unsigned long :24;
	} bit;
} IoElaEdg2anba;

/*  structure of edgscla    (288B_026Ch)    */
typedef union _IoElaEdgscla
{
	unsigned long word;
	struct {
		unsigned long edgscla :10;
		unsigned long :22;
	} bit;
} IoElaEdgscla;

/*  structure of edg2anbb   (288B_0274h)    */
typedef union _IoElaEdg2anbb
{
	unsigned long word;
	struct {
		unsigned long edg2anbb :10;
		unsigned long :22;
	} bit;
} IoElaEdg2anbb;

/*  structure of edgsclb    (288B_0278h)    */
typedef union _IoElaEdgsclb
{
	unsigned long word;
	struct {
		unsigned long edgsclb :10;
		unsigned long :22;
	} bit;
} IoElaEdgsclb;

/*  structure of alnge  (288B_0280h)    */
typedef union _IoElaAlnge1
{
	unsigned long word;
	struct {
		unsigned long alnge11 :12;
		unsigned long :4;
		unsigned long alnge22 :12;
		unsigned long :4;
	} bit;
} IoElaAlnge1;

typedef union _IoElaAlnge2
{
	unsigned long word;
	struct {
		unsigned long alnge3 :12;
		unsigned long :20;
	} bit;
} IoElaAlnge2;

typedef struct _IoElaAlnge
{
	IoElaAlnge1 alnge1;
	IoElaAlnge2 alnge2;
} IoElaAlnge;

/*  structure of alng   (288B_02A0h)    */
typedef union _IoElaAlng1
{
	unsigned long word;
	struct {
		unsigned long alngl1e1n :9;
		unsigned long :7;
		unsigned long alngl1e2n :9;
		unsigned long :7;
	} bit;
} IoElaAlng1;

typedef union _IoElaAlng2
{
	unsigned long word;
	struct {
		unsigned long alngl1e3n :9;
		unsigned long :7;
		unsigned long alngl2e1n :9;
		unsigned long :7;
	} bit;
} IoElaAlng2;

typedef union _IoElaAlng3
{
	unsigned long word;
	struct {
		unsigned long alngl2e2n :9;
		unsigned long :7;
		unsigned long alngl2e3n :9;
		unsigned long :7;
	} bit;
} IoElaAlng3;

typedef union _IoElaAlng4
{
    unsigned long       word;
    struct {
        unsigned long   alngl3e1n   :9;
        unsigned long               :7;
        unsigned long   alngl3e2n   :9;
        unsigned long               :7;
    }bit;
}IoElaAlng4;

typedef union _IoElaAlng5
{
	unsigned long word;
	struct {
		unsigned long alngl3e3n :9;
		unsigned long :7;
		unsigned long alngl4e1n :9;
		unsigned long :7;
	} bit;
} IoElaAlng5;

typedef union _IoElaAlng6
{
	unsigned long word;
	struct {
		unsigned long alngl4e2n :9;
		unsigned long :7;
		unsigned long alngl4e3n :9;
		unsigned long :7;
	} bit;
} IoElaAlng6;

typedef struct _IoElaAlng
{
	IoElaAlng1 alng1;
	IoElaAlng2 alng2;
	IoElaAlng3 alng3;
	IoElaAlng4 alng4;
	IoElaAlng5 alng5;
	IoElaAlng6 alng6;
} IoElaAlng;

/*  structure of lfth   (288B_02C0h)    */
typedef union _IoElaLfth
{
	unsigned long word;
	struct {
		unsigned long lfth :12;
		unsigned long :20;
	} bit;
} IoElaLfth;

/*  structure of lcome  (288B_02C8h)    */
typedef union _IoElaLcome
{
	unsigned long word;
	struct {
		unsigned long lcome1 :12;
		unsigned long :4;
		unsigned long lcome2 :12;
		unsigned long :4;
	} bit;
} IoElaLcome;

/*  structure of lcomen (288B_02CCh)    */
typedef union _IoElaLcomen
{
	unsigned long word;
	struct {
		unsigned long lcome1n :9;
		unsigned long :7;
		unsigned long lcome2n :9;
		unsigned long :7;
	} bit;
} IoElaLcomen;

/*  structure of dkntbl (288B_0400h)    */
typedef union _IoElaDkntbl
{
	unsigned long word[128];
	struct {
		unsigned long dkntbl0 :12;
		unsigned long :4;
		unsigned long dkntbl1 :12;
		unsigned long :4;
	} bit[128];
} IoElaDkntbl;

/* Define i/o mapping */
typedef struct _IoEla
{
	/* JDSIMG */
	/* 288B_(0000 - 1003h) */
	IoElaEarcache earcache;
	/* 288B_(0004 - 1007h) */
	IoElaEawcache eawcache;
	/* 288B_(0008 - 100Bh) */
	IoElaEarprot earprot;
	/* 288B_(000C - 100Fh) */
	IoElaEawprot eawprot;
	/* 288B_(0010 - 1013h) */
	IoElaEaraxsts earaxsts;
	/* 288B_(0014 - 1017h) */
	IoElaEawaxsts eawaxsts;
	/* 288B_(0018 - 101Fh) */
	unsigned char dmy1018101f[0x1020 - 0x1018];
	/* 288B_(0020 - 1027h) */
	IoElaEarreqmsk earreqmsk;
	/* 288B_(0028 - 102Fh) */
	IoElaEawreqmsk eawreqmsk;
	/* 288B_(0030 - 10FFh) */
	unsigned char dmy103010ff[0x1100 - 0x1030];
	/* 288B_(0100 - 1103h) */
	IoElaElainte elainte;
	/* 288B_(0104 - 1107h) */
	IoElaElaintf elaintf;
	/* 288B_(0108 - 110Bh) */
	IoElaSramact sramact;
	/* 288B_(010C - 110Fh) */
	unsigned char dmy110c110f[0x1110 - 0x110C];
	/* 288B_(0110 - 1113h) */
	IoElaElatrg elatrg;
	/* 288B_(0114 - 1117h) */
	IoElaElactl elactl;
	/* 288B_(0118 - 111Bh) */
	IoElaElabyr elabyr;
	/* 288B_(011C - 111Fh) */
	IoElaNslmd nslmd;
	/* 288B_(0120 - 1127h) */
	IoElaObof obof;
	/* 288B_(0128 - 112Bh) */
	IoElaEzsfta1 ezsfta1;
	/* 288B_(012C - 112Fh) */
	IoElaNslnglmt nslnglmt;
	/* 288B_(0130 - 1133h) */
	IoElaEira eira;
	/* 288B_(0134 - 1137h) */
	IoElaEirofs eirofs;
	/* 288B_(0138 - 113Bh) */
	IoElaEirdef eirdef;
	/* 288B_(013C - 113Fh) */
	IoElaEirhsiz eirhsiz;
	/* 288B_(0140 - 1143h) */
	IoElaEirvsiz eirvsiz;
	/* 288B_(0144 - 114Fh) */
	unsigned char dmy1144114f[0x1150 - 0x1144];
	/* 288B_(0150 - 115Fh) */
	IoElaEiwa eiwa;
	/* 288B_(0160 - 1163h) */
	IoElaEiwdef eiwdef;
	/* 288B_(0164 - 1167h) */
	IoElaEnwa enwa;
	/* 288B_(0168 - 116Bh) */
	IoElaEnwdef enwdef;
	/* 288B_(016C - 117Fh) */
	unsigned char dmy116c117f[0x1180 - 0x116C];
	/* 288B_(0180 - 11BFh) */
	IoElaEnra enra;
	/* 288B_(01C0 - 11C3h) */
	IoElaEnrhsiz enrhsiz;
	/* 288B_(01C4 - 11C7h) */
	IoElaEnrvsiz enrvsiz;
	/* 288B_(01C8 - 11CBh) */
	IoElaEnsa ensa;
	/* 288B_(01CC - 11CFh) */
	IoElaEnsdef ensdef;
	/* 288B_(01D0 - 11D3h) */
	IoElaEnshsiz enshsiz;
	/* 288B_(01D4 - 11D7h) */
	IoElaEnsvsiz ensvsiz;
	/* 288B_(01D8 - 11FFh) */
	unsigned char dmy11d811ff[0x1200 - 0x11D8];
	/* 288B_(0200 - 1203h) */
	IoElaByrtyp byrtyp;
	/* 288B_(0204 - 1207h) */
	IoElaElfzp elfzp;
	/* 288B_(0208 - 120Fh) */
	IoElaElfl elfl;
	/* 288B_(0210 - 1217h) */
	IoElaAnbor anbor;
	/* 288B_(0218 - 121Fh) */
	IoElaAnbkr anbkr;
	/* 288B_(0220 - 1227h) */
	IoElaAnbdr anbdr;
	/* 288B_(0228 - 122Fh) */
	IoElaAnbog anbog;
	/* 288B_(0230 - 1237h) */
	IoElaAnbkg anbkg;
	/* 288B_(0238 - 123Fh) */
	IoElaAnbdg anbdg;
	/* 288B_(0240 - 1247h) */
	IoElaAnbob anbob;
	/* 288B_(0248 - 124Fh) */
	IoElaAnbkb anbkb;
	/* 288B_(0250 - 1257h) */
	IoElaAnbdb anbdb;
	/* 288B_(0258 - 125Fh) */
	IoElaLgtw lgtw;
	/* 288B_(0260 - 1263h) */
	IoElaLgt lgt;
	/* 288B_(0264 - 1267h) */
	IoElaLgte lgte;
	/* 288B_(0268 - 126Bh) */
	IoElaEdg2anba edg2anba;
	/* 288B_(026C - 126Fh) */
	IoElaEdgscla edgscla;
	/* 288B_(0270 - 1273h) */
	unsigned char dmy12701273[0x1274 - 0x1270];
	/* 288B_(0274 - 1277h) */
	IoElaEdg2anbb edg2anbb;
	/* 288B_(0278 - 127Bh) */
	IoElaEdgsclb edgsclb;
	/* 288B_(027C - 127Fh) */
	unsigned char dmy127c127f[0x1280 - 0x127C];
	/* 288B_(0280 - 1287h) */
	IoElaAlnge alnge;
	/* 288B_(0288 - 129Fh) */
	unsigned char dmy1288129f[0x12A0 - 0x1288];
	/* 288B_(02A0 - 12B7h) */
	IoElaAlng alng;
	/* 288B_(02B8 - 12BFh) */
	unsigned char dmy12b812bf[0x12C0 - 0x12B8];
	/* 288B_(02C0 - 12C3h) */
	IoElaLfth lfth;
	/* 288B_(02C4 - 12C7h) */
	unsigned char dmy12c412c7[0x12C8 - 0x12C4];
	/* 288B_(02C8 - 12CBh) */
	IoElaLcome lcome;
	/* 288B_(02CC - 12CFh) */
	IoElaLcomen lcomen;
	/* 288B_(02D0 - 13FFh) */
	unsigned char dmy12d013ff[0x1400 - 0x12D0];
	/* 288B_(0400 - 15FFh) */
	 IoElaDkntbl dkntbl;
	 /* 288B_(0600 - 1FFFh) */
	unsigned char dmy16001fff[0x2000 - 0x1600];

} IoEla;

extern volatile IoEla		ioEla;


KConstType	k_jdsela2d_get_type(void);
KJdsela2d*	k_jdsela2d_new(void);


#endif/*__K_JDSELA2D_H__*/

