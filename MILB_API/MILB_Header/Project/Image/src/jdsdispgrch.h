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


 #ifndef __JDSDISP_GRCH_H__
 #define __JDSDISP_GRCH_H__


 #include <klib.h>


 #define JDSDISP_TYPE_GRCH				(jdsdisp_grch_get_type())
 #define JDSDISP_GRCH(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispGrch))
 #define JDSDISP_IS_GRCH(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_GRCH))


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
 typedef struct 				_JdsdispGrch JdsdispGrch;
 typedef struct 				_JdsdispGrchPrivate	JdsdispGrchPrivate;

 union _IoJdsgrchRegGrrst{
     kulong       word;
     struct {
         kulong   sr  :1;
         kulong       :31;
     }bit;
 };

 /*  structure of GRTRG  (2890_2100h)    */
 union _IoJdsgrchRegGrtrg{
     kulong       word;
     struct {
         kulong   trg :2;
         kulong       :30;
     }bit;
 };

 /*  structure of GRRPGCTL   (2890_2110h)    */
 union _IoJdsgrchRegGrrpgctl{
     kulong       word;
     struct {
         kulong   rpgtmg  :1;
         kulong           :31;
     }bit;
 };

 /*  structure of GRIDT  (2890_2200h)    */
 union _IoJdsgrchRegGridt{
     kulong       word;
     struct {
         kulong   ifmt    :3;
         kulong           :1;
         kulong   nbt     :2;
         kulong           :2;
         kulong           :8;
         kulong   cache   :4;
         kulong   prot    :3;
         kulong           :1;
         kulong   slvsl   :1;
         kulong   aslvsl  :1;
         kulong           :2;
         kulong   ifbtmu  :1;
         kulong           :3;
     }bit;
 };

 /*  structure of GRTISIZE   (2890_2204h)    */
 union _IoJdsgrchRegGrtisize{
     kulong       word;
     struct {
         kulong   tihsize :16;
         kulong   tivsize :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GRTDSTA    (2890_2208h)    */
 union _IoJdsgrchRegGrtdsta{
     kulong       word;
     struct {
         kulong   tdsh    :16;
         kulong   tdsv    :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GRIPO  (2890_2210h)    */
 union _IoJdsgrchRegGripo{
     kulong       word;
     struct {
         kulong   ipo1    :2;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   ipo2    :2;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   ipo3    :2;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   ipo4    :2;
         kulong           :6;
     }bit;
 };

 /*  structure of GRSCCTL    (2890_2214h)    */
 union _IoJdsgrchRegGrscctl{
     kulong       word;
     struct {
         kulong   scen    :2;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   idset   :2;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   idm     :2;
         kulong           :14;
     }bit;
 };

 /*  structure of GRERCV (2890_2218h)    */
 union _IoJdsgrchRegGrercv{
     kulong       word;
     struct {
         kulong   ercv    :1;
         kulong           :31;
     }bit;
 };

 /*  structure of GRISIZE    (2890_2400h)    */
 union _IoJdsgrchRegGrisize{
     kulong       word;
     struct {
         kulong   ihsize      :16;
         kulong   ivsize      :14;
         kulong               :2;
     }bit;
 };

 /*  structure of GRSA0  (2890_2440h)    */
 union _IoJdsgrchRegGrsa0{
     kulong       word;
     struct {
         kulong   sa0   :32;
     }bit;
 };

 /*  structure of GRSA   (2890_2480h)    */
 union _IoJdsgrchRegGrsa{
     kulong       word;
     struct {
         kulong   sa      :32;
     }bit;
 };

 /*  structure of GRASA  (2890_24C0h)    */
 union _IoJdsgrchRegGrasa{
     kulong       word;
     struct {
         kulong   asa     :32;
     }bit;
 };

 /*  structure of GRHGA  (2890_2500h)    */
 union _IoJdsgrchRegGrhga{
     kulong       word;
     struct {
         kulong   hga     :16;
         kulong           :16;
     }bit;
 };

 /*  structure of GRAHGA (2890_2540h)    */
 union _IoJdsgrchRegGrahga{
     kulong       word;
     struct {
         kulong   ahga    :16;
         kulong           :16;
     }bit;
 };

 /*  structure of GRDSTA (2890_2580h)    */
 union _IoJdsgrchRegGrdsta{
     kulong       word;
     struct {
         kulong   dsh     :16;
         kulong   dsv     :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GRAREN (2890_25C0h)    */
 union _IoJdsgrchRegGraren{
     kulong       word;
     struct {
         kulong   aren    :10;
         kulong           :22;
     }bit;
 };

 /*  structure of GRBSL  (2890_25C4h)    */
 union _IoJdsgrchRegGrbsl{
     kulong       word;
     struct {
         kulong   bsl :10;
         kulong       :22;
     }bit;
 };

 /*  structure of GRBLINK    (2890_25E0h)    */
 union _IoJdsgrchRegGrblink{
     kulong       word[5];
     struct {
         kulong   btimh0 :6;
         kulong           :2;
         kulong   btiml0 :6;
         kulong           :2;
         kulong   btimh1 :6;
         kulong           :2;
         kulong   btiml1 :6;
         kulong           :2;
         kulong   btimh2 :6;
         kulong           :2;
         kulong   btiml2 :6;
         kulong           :2;
         kulong   btimh3 :6;
         kulong           :2;
         kulong   btiml3 :6;
         kulong           :2;
         kulong   btimh4 :6;
         kulong           :2;
         kulong   btiml4 :6;
         kulong           :2;
         kulong   btimh5 :6;
         kulong           :2;
         kulong   btiml5 :6;
         kulong           :2;
         kulong   btimh6 :6;
         kulong           :2;
         kulong   btiml6 :6;
         kulong           :2;
         kulong   btimh7 :6;
         kulong           :2;
         kulong   btiml7 :6;
         kulong           :2;
         kulong   btimh8 :6;
         kulong           :2;
         kulong   btiml8 :6;
         kulong           :2;
         kulong   btimh9 :6;
         kulong           :2;
         kulong   btiml9 :6;
         kulong           :2;
     }bit;
 };

 /*  structure of GRBINIT    (2890_2600h)    */
 union _IoJdsgrchRegGrbinit{
     kulong       word;
     struct {
         kulong   binit   :10;
         kulong           :22;
     }bit;
 };

 /*  structure of GRBITRG    (2890_2604h)    */
 union _IoJdsgrchRegGrbitrg{
     kulong       word;
     struct {
         kulong   bitrg   :2;
         kulong           :30;
     }bit;
 };

 /*  structure of GRRSZ0 (2890_2810h)    */
 union _IoJdsgrchRegGrrsz0{
     kulong       word;
     struct {
         kulong   rszsl   :1;
         kulong           :31;
     }bit;
 };

 /*  structure of GRRSZ1 (2890_2814h)    */
 union _IoJdsgrchRegGrrsz1{
     kulong       word;
     struct {
         kulong   hrszm   :5;
         kulong           :3;
         kulong   hrszn   :5;
         kulong           :3;
         kulong           :7;
         kulong           :1;
         kulong   hrszof  :5;
         kulong           :3;
     }bit;
 };

 /*  structure of GRRSZ2 (2890_2818h)    */
 union _IoJdsgrchRegGrrsz2{
     kulong       word;
     struct {
         kulong   vrszm   :5;
         kulong           :3;
         kulong   vrszn   :5;
         kulong           :3;
         kulong           :8;
         kulong   vrszof  :5;
         kulong           :3;
     }bit;
 };

 /*  structure of GRRSZ3 (2890_281Ch)    */
 union _IoJdsgrchRegGrrsz3{
     kulong       word;
     struct {
         kulong   hcsta   :6;
         kulong           :2;
         kulong   vcsta   :6;
         kulong           :18;
     }bit;
 };

 /*  structure of GRY2R0 - GRY2R2 (2890_2840 h)    */
 union _IoJdsgrchRegGry2r{
     kulong       word;
     struct {
         kulong   yr0     :8;
         kulong   yr1     :8;
         kulong   yr2     :8;
         kulong           :8;
     }bit;
 };

 /*  structure of GRALP  (2890_2880h)    */
 union _IoJdsgrchRegGralp{
     kulong       word;
     struct {
         kulong   alp :8;
         kulong       :24;
     }bit;
 };

 /* Define i/o mapping */
 struct _IoJdsgrchReg{
     /* JDSIMG */
	 /* 2890_(2000 - 2003h) */
	 IoJdsgrchRegGrrst     grrst;
	 /* 2890_(2004 - 20FFh) */
     kuchar dmy200420ff[0x2100-0x2004];
     /* 2890_(2100 - 2103h) */
     IoJdsgrchRegGrtrg     grtrg;
     /* 2890_(2104 - 210Fh) */
     kuchar dmy2104210f[0x2110-0x2104];
     /* 2890_(2110 - 2113h) */
     IoJdsgrchRegGrrpgctl  grrpgctl;
     /* 2890_(2114 - 21FFh) */
     kuchar dmy211421ff[0x2200-0x2114];
     /* 2890_(2200 - 2203h) */
     IoJdsgrchRegGridt     gridt;
     /* 2890_(2204 - 2207h) */
     IoJdsgrchRegGrtisize  grtisize;
     /* 2890_(2208 - 220Bh) */
     IoJdsgrchRegGrtdsta   grtdsta;
     /* 2890_(220C - 220Fh) */
     kuchar dmy220c220f[0x2210-0x220C];
     /* 2890_(2210 - 2213h) */
     IoJdsgrchRegGripo     gripo;
     /* 2890_(2214 - 2217h) */
     IoJdsgrchRegGrscctl   grscctl;
     /* 2890_(2218 - 221Bh) */
     IoJdsgrchRegGrercv    grercv;
     /* 2890_(221C - 23FFh) */
     kuchar dmy221c23ff[0x2400-0x221C];
     /* 2890_(2400 - 2427h) */
     IoJdsgrchRegGrisize   grisize[10];
     /* 2890_(2428 - 243Fh) */
     kuchar dmy2428243f[0x2440-0x2428];
     /* 2890_(2440 - 244Fh) */
     IoJdsgrchRegGrsa0     grsa0[4];
     /* 2890_(2450 - 247Fh) */
     kuchar dmy2450247f[0x2480-0x2450];
     /* 2890_(2480 - 24A3h) */
     IoJdsgrchRegGrsa      grsa[9];
     /* 2890_(24A4 - 24BFh) */
     kuchar dmy24a424bf[0x24C0-0x24A4];
     /* 2890_(24C0 - 24E7h) */
     IoJdsgrchRegGrasa     grasa[10];
     /* 2890_(24E8 - 24FFh) */
     kuchar dmy24e824ff[0x2500-0x24E8];
     /* 2890_(2500 - 2527h) */
     IoJdsgrchRegGrhga     grhga[10];
     /* 2890_(2528 - 253Fh) */
     kuchar dmy2528253f[0x2540-0x2528];
     /* 2890_(2540 - 2567h) */
     IoJdsgrchRegGrahga    grahga[10];
     /* 2890_(2568 - 257Fh) */
     kuchar dmy2568257f[0x2580-0x2568];
     /* 2890_(2580 - 25A7h) */
     IoJdsgrchRegGrdsta    grdsta[10];
     /* 2890_(25A8 - 25BFh) */
     kuchar dmy25a825bf[0x25C0-0x25A8];
     /* 2890_(25C0 - 25C3h) */
     IoJdsgrchRegGraren    graren;
     /* 2890_(25C4 - 25C7h) */
     IoJdsgrchRegGrbsl     grbsl;
     /* 2890_(25C8 - 25DFh) */
     kuchar dmy25c825df[0x25E0-0x25C8];
     /* 2890_(25E0 - 25F3h) */
     IoJdsgrchRegGrblink   grblink;
     /* 2890_(25F4 - 25FFh) */
     kuchar dmy25f425ff[0x2600-0x25F4];
     /* 2890_(2600 - 2603h) */
     IoJdsgrchRegGrbinit   grbinit;
     /* 2890_(2604 - 2607h) */
     IoJdsgrchRegGrbitrg   grbitrg;
     /* 2890_(2608 - 280Fh) */
     kuchar dmy2608280f[0x2810-0x2608];
     /* 2890_(2810 - 2813h) */
     IoJdsgrchRegGrrsz0    grrsz0;
     /* 2890_(2814 - 2817h) */
     IoJdsgrchRegGrrsz1    grrsz1;
     /* 2890_(2818 - 281Bh) */
     IoJdsgrchRegGrrsz2    grrsz2;
     /* 2890_(281C - 281Fh) */
     IoJdsgrchRegGrrsz3    grrsz3;
     /* 2890_(2820 - 283Fh) */
     kuchar dmy2820283f[0x2840-0x2820];
     /* 2890_(2840 - 284Bh) */
     IoJdsgrchRegGry2r     gry2r[3];
     /* 2890_(284C - 287Fh) */
     kuchar dmy284c287f[0x2880-0x284C];
     /* 2890_(2880 - 2883h) */
     IoJdsgrchRegGralp     gralp;
     /* 2890_(2884 - 2FFFh) */
     kuchar dmy28842fff[0x3000-0x2884];
 };

 struct  _JdsdispGrch
 {
 	KObject parent;
 };


 KConstType				jdsdisp_grch_get_type(void);
 JdsdispGrch*				jdsdisp_grch_new(void);


 #endif/*__JDSDISP_GRCH_H__*/
