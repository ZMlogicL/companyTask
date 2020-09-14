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


 #ifndef __JDSDISP_GRCH_H__
 #define __JDSDISP_GRCH_H__


#include <stdio.h>
#include <glib-object.h>


 typedef union 				_IoJdsgrchRegGrrst IoJdsgrchRegGrrst;
 typedef union 				_IoJdsgrchRegGrtrg IoJdsgrchRegGrtrg;
 typedef union 				_IoJdsgrchRegGrrpgctl IoJdsgrchRegGrrpgctl;
 typedef union 				_IoJdsgrchRegGridt IoJdsgrchRegGridt;
 typedef union 				_IoJdsgrchRegGrtisize IoJdsgrchRegGrtisize;
 typedef union 				_IoJdsgrchRegGrtdsta IoJdsgrchRegGrtdsta;
 typedef union 				_IoJdsgrchRegGripo IoJdsgrchRegGripo;
 typedef union 				_IoJdsgrchRegGrscctl IoJdsgrchRegGrscctl;
 typedef union 				_IoJdsgrchRegGrercv IoJdsgrchRegGrercv;
 typedef union 				_IoJdsgrchRegGrisize IoJdsgrchRegGrisize;
 typedef union 				_IoJdsgrchRegGrsa0 IoJdsgrchRegGrsa0;
 typedef union 				_IoJdsgrchRegGrsa IoJdsgrchRegGrsa;
 typedef union 				_IoJdsgrchRegGrasa IoJdsgrchRegGrasa;
 typedef union 				_IoJdsgrchRegGrhga IoJdsgrchRegGrhga;
 typedef union 				_IoJdsgrchRegGrahga IoJdsgrchRegGrahga;
 typedef union 				_IoJdsgrchRegGrdsta IoJdsgrchRegGrdsta;
 typedef union 				_IoJdsgrchRegGraren IoJdsgrchRegGraren;
 typedef union 				_IoJdsgrchRegGrbsl IoJdsgrchRegGrbsl;
 typedef union 				_IoJdsgrchRegGrblink IoJdsgrchRegGrblink;
 typedef union 				_IoJdsgrchRegGrbinit IoJdsgrchRegGrbinit;
 typedef union 				_IoJdsgrchRegGrbitrg IoJdsgrchRegGrbitrg;
 typedef union 				_IoJdsgrchRegGrrsz0 IoJdsgrchRegGrrsz0;
 typedef union 				_IoJdsgrchRegGrrsz1 IoJdsgrchRegGrrsz1;
 typedef union 				_IoJdsgrchRegGrrsz2 IoJdsgrchRegGrrsz2;
 typedef union 				_IoJdsgrchRegGrrsz3 IoJdsgrchRegGrrsz3;
 typedef union 				_IoJdsgrchRegGry2r IoJdsgrchRegGry2r;
 typedef union 				_IoJdsgrchRegGralp IoJdsgrchRegGralp;
 typedef struct 				_IoJdsgrchReg IoJdsgrchReg;

 union _IoJdsgrchRegGrrst{
     gulong       word;
     struct {
         gulong   sr  :1;
         gulong       :31;
     }bit;
 };

 /*  structure of GRTRG  (2890_2100h)    */
 union _IoJdsgrchRegGrtrg{
     gulong       word;
     struct {
         gulong   trg :2;
         gulong       :30;
     }bit;
 };

 /*  structure of GRRPGCTL   (2890_2110h)    */
 union _IoJdsgrchRegGrrpgctl{
     gulong       word;
     struct {
         gulong   rpgtmg  :1;
         gulong           :31;
     }bit;
 };

 /*  structure of GRIDT  (2890_2200h)    */
 union _IoJdsgrchRegGridt{
     gulong       word;
     struct {
         gulong   ifmt    :3;
         gulong           :1;
         gulong   nbt     :2;
         gulong           :2;
         gulong           :8;
         gulong   cache   :4;
         gulong   prot    :3;
         gulong           :1;
         gulong   slvsl   :1;
         gulong   aslvsl  :1;
         gulong           :2;
         gulong   ifbtmu  :1;
         gulong           :3;
     }bit;
 };

 /*  structure of GRTISIZE   (2890_2204h)    */
 union _IoJdsgrchRegGrtisize{
     gulong       word;
     struct {
         gulong   tihsize :16;
         gulong   tivsize :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GRTDSTA    (2890_2208h)    */
 union _IoJdsgrchRegGrtdsta{
     gulong       word;
     struct {
         gulong   tdsh    :16;
         gulong   tdsv    :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GRIPO  (2890_2210h)    */
 union _IoJdsgrchRegGripo{
     gulong       word;
     struct {
         gulong   ipo1    :2;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   ipo2    :2;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   ipo3    :2;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   ipo4    :2;
         gulong           :6;
     }bit;
 };

 /*  structure of GRSCCTL    (2890_2214h)    */
 union _IoJdsgrchRegGrscctl{
     gulong       word;
     struct {
         gulong   scen    :2;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   idset   :2;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   idm     :2;
         gulong           :14;
     }bit;
 };

 /*  structure of GRERCV (2890_2218h)    */
 union _IoJdsgrchRegGrercv{
     gulong       word;
     struct {
         gulong   ercv    :1;
         gulong           :31;
     }bit;
 };

 /*  structure of GRISIZE    (2890_2400h)    */
 union _IoJdsgrchRegGrisize{
     gulong       word;
     struct {
         gulong   ihsize      :16;
         gulong   ivsize      :14;
         gulong               :2;
     }bit;
 };

 /*  structure of GRSA0  (2890_2440h)    */
 union _IoJdsgrchRegGrsa0{
     gulong       word;
     struct {
         gulong   sa0   :32;
     }bit;
 };

 /*  structure of GRSA   (2890_2480h)    */
 union _IoJdsgrchRegGrsa{
     gulong       word;
     struct {
         gulong   sa      :32;
     }bit;
 };

 /*  structure of GRASA  (2890_24C0h)    */
 union _IoJdsgrchRegGrasa{
     gulong       word;
     struct {
         gulong   asa     :32;
     }bit;
 };

 /*  structure of GRHGA  (2890_2500h)    */
 union _IoJdsgrchRegGrhga{
     gulong       word;
     struct {
         gulong   hga     :16;
         gulong           :16;
     }bit;
 };

 /*  structure of GRAHGA (2890_2540h)    */
 union _IoJdsgrchRegGrahga{
     gulong       word;
     struct {
         gulong   ahga    :16;
         gulong           :16;
     }bit;
 };

 /*  structure of GRDSTA (2890_2580h)    */
 union _IoJdsgrchRegGrdsta{
     gulong       word;
     struct {
         gulong   dsh     :16;
         gulong   dsv     :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GRAREN (2890_25C0h)    */
 union _IoJdsgrchRegGraren{
     gulong       word;
     struct {
         gulong   aren    :10;
         gulong           :22;
     }bit;
 };

 /*  structure of GRBSL  (2890_25C4h)    */
 union _IoJdsgrchRegGrbsl{
     gulong       word;
     struct {
         gulong   bsl :10;
         gulong       :22;
     }bit;
 };

 /*  structure of GRBLINK    (2890_25E0h)    */
 union _IoJdsgrchRegGrblink{
     gulong       word[5];
     struct {
         gulong   btimh0 :6;
         gulong           :2;
         gulong   btiml0 :6;
         gulong           :2;
         gulong   btimh1 :6;
         gulong           :2;
         gulong   btiml1 :6;
         gulong           :2;
         gulong   btimh2 :6;
         gulong           :2;
         gulong   btiml2 :6;
         gulong           :2;
         gulong   btimh3 :6;
         gulong           :2;
         gulong   btiml3 :6;
         gulong           :2;
         gulong   btimh4 :6;
         gulong           :2;
         gulong   btiml4 :6;
         gulong           :2;
         gulong   btimh5 :6;
         gulong           :2;
         gulong   btiml5 :6;
         gulong           :2;
         gulong   btimh6 :6;
         gulong           :2;
         gulong   btiml6 :6;
         gulong           :2;
         gulong   btimh7 :6;
         gulong           :2;
         gulong   btiml7 :6;
         gulong           :2;
         gulong   btimh8 :6;
         gulong           :2;
         gulong   btiml8 :6;
         gulong           :2;
         gulong   btimh9 :6;
         gulong           :2;
         gulong   btiml9 :6;
         gulong           :2;
     }bit;
 };

 /*  structure of GRBINIT    (2890_2600h)    */
 union _IoJdsgrchRegGrbinit{
     gulong       word;
     struct {
         gulong   binit   :10;
         gulong           :22;
     }bit;
 };

 /*  structure of GRBITRG    (2890_2604h)    */
 union _IoJdsgrchRegGrbitrg{
     gulong       word;
     struct {
         gulong   bitrg   :2;
         gulong           :30;
     }bit;
 };

 /*  structure of GRRSZ0 (2890_2810h)    */
 union _IoJdsgrchRegGrrsz0{
     gulong       word;
     struct {
         gulong   rszsl   :1;
         gulong           :31;
     }bit;
 };

 /*  structure of GRRSZ1 (2890_2814h)    */
 union _IoJdsgrchRegGrrsz1{
     gulong       word;
     struct {
         gulong   hrszm   :5;
         gulong           :3;
         gulong   hrszn   :5;
         gulong           :3;
         gulong           :7;
         gulong           :1;
         gulong   hrszof  :5;
         gulong           :3;
     }bit;
 };

 /*  structure of GRRSZ2 (2890_2818h)    */
 union _IoJdsgrchRegGrrsz2{
     gulong       word;
     struct {
         gulong   vrszm   :5;
         gulong           :3;
         gulong   vrszn   :5;
         gulong           :3;
         gulong           :8;
         gulong   vrszof  :5;
         gulong           :3;
     }bit;
 };

 /*  structure of GRRSZ3 (2890_281Ch)    */
 union _IoJdsgrchRegGrrsz3{
     gulong       word;
     struct {
         gulong   hcsta   :6;
         gulong           :2;
         gulong   vcsta   :6;
         gulong           :18;
     }bit;
 };

 /*  structure of GRY2R0 - GRY2R2 (2890_2840 h)    */
 union _IoJdsgrchRegGry2r{
     gulong       word;
     struct {
         gulong   yr0     :8;
         gulong   yr1     :8;
         gulong   yr2     :8;
         gulong           :8;
     }bit;
 };

 /*  structure of GRALP  (2890_2880h)    */
 union _IoJdsgrchRegGralp{
     gulong       word;
     struct {
         gulong   alp :8;
         gulong       :24;
     }bit;
 };

 /* Define i/o mapping */
 struct _IoJdsgrchReg{
     /* JDSIMG */
	 /* 2890_(2000 - 2003h) */
	 IoJdsgrchRegGrrst     grrst;
	 /* 2890_(2004 - 20FFh) */
     guchar dmy200420ff[0x2100-0x2004];
     /* 2890_(2100 - 2103h) */
     IoJdsgrchRegGrtrg     grtrg;
     /* 2890_(2104 - 210Fh) */
     guchar dmy2104210f[0x2110-0x2104];
     /* 2890_(2110 - 2113h) */
     IoJdsgrchRegGrrpgctl  grrpgctl;
     /* 2890_(2114 - 21FFh) */
     guchar dmy211421ff[0x2200-0x2114];
     /* 2890_(2200 - 2203h) */
     IoJdsgrchRegGridt     gridt;
     /* 2890_(2204 - 2207h) */
     IoJdsgrchRegGrtisize  grtisize;
     /* 2890_(2208 - 220Bh) */
     IoJdsgrchRegGrtdsta   grtdsta;
     /* 2890_(220C - 220Fh) */
     guchar dmy220c220f[0x2210-0x220C];
     /* 2890_(2210 - 2213h) */
     IoJdsgrchRegGripo     gripo;
     /* 2890_(2214 - 2217h) */
     IoJdsgrchRegGrscctl   grscctl;
     /* 2890_(2218 - 221Bh) */
     IoJdsgrchRegGrercv    grercv;
     /* 2890_(221C - 23FFh) */
     guchar dmy221c23ff[0x2400-0x221C];
     /* 2890_(2400 - 2427h) */
     IoJdsgrchRegGrisize   grisize[10];
     /* 2890_(2428 - 243Fh) */
     guchar dmy2428243f[0x2440-0x2428];
     /* 2890_(2440 - 244Fh) */
     IoJdsgrchRegGrsa0     grsa0[4];
     /* 2890_(2450 - 247Fh) */
     guchar dmy2450247f[0x2480-0x2450];
     /* 2890_(2480 - 24A3h) */
     IoJdsgrchRegGrsa      grsa[9];
     /* 2890_(24A4 - 24BFh) */
     guchar dmy24a424bf[0x24C0-0x24A4];
     /* 2890_(24C0 - 24E7h) */
     IoJdsgrchRegGrasa     grasa[10];
     /* 2890_(24E8 - 24FFh) */
     guchar dmy24e824ff[0x2500-0x24E8];
     /* 2890_(2500 - 2527h) */
     IoJdsgrchRegGrhga     grhga[10];
     /* 2890_(2528 - 253Fh) */
     guchar dmy2528253f[0x2540-0x2528];
     /* 2890_(2540 - 2567h) */
     IoJdsgrchRegGrahga    grahga[10];
     /* 2890_(2568 - 257Fh) */
     guchar dmy2568257f[0x2580-0x2568];
     /* 2890_(2580 - 25A7h) */
     IoJdsgrchRegGrdsta    grdsta[10];
     /* 2890_(25A8 - 25BFh) */
     guchar dmy25a825bf[0x25C0-0x25A8];
     /* 2890_(25C0 - 25C3h) */
     IoJdsgrchRegGraren    graren;
     /* 2890_(25C4 - 25C7h) */
     IoJdsgrchRegGrbsl     grbsl;
     /* 2890_(25C8 - 25DFh) */
     guchar dmy25c825df[0x25E0-0x25C8];
     /* 2890_(25E0 - 25F3h) */
     IoJdsgrchRegGrblink   grblink;
     /* 2890_(25F4 - 25FFh) */
     guchar dmy25f425ff[0x2600-0x25F4];
     /* 2890_(2600 - 2603h) */
     IoJdsgrchRegGrbinit   grbinit;
     /* 2890_(2604 - 2607h) */
     IoJdsgrchRegGrbitrg   grbitrg;
     /* 2890_(2608 - 280Fh) */
     guchar dmy2608280f[0x2810-0x2608];
     /* 2890_(2810 - 2813h) */
     IoJdsgrchRegGrrsz0    grrsz0;
     /* 2890_(2814 - 2817h) */
     IoJdsgrchRegGrrsz1    grrsz1;
     /* 2890_(2818 - 281Bh) */
     IoJdsgrchRegGrrsz2    grrsz2;
     /* 2890_(281C - 281Fh) */
     IoJdsgrchRegGrrsz3    grrsz3;
     /* 2890_(2820 - 283Fh) */
     guchar dmy2820283f[0x2840-0x2820];
     /* 2890_(2840 - 284Bh) */
     IoJdsgrchRegGry2r     gry2r[3];
     /* 2890_(284C - 287Fh) */
     guchar dmy284c287f[0x2880-0x284C];
     /* 2890_(2880 - 2883h) */
     IoJdsgrchRegGralp     gralp;
     /* 2890_(2884 - 2FFFh) */
     guchar dmy28842fff[0x3000-0x2884];
 };


 #endif/*__JDSDISP_GRCH_H__*/
