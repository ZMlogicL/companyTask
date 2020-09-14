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


 #ifndef __JDSDISP_DCORE_H__
 #define __JDSDISP_DCORE_H__


#include <stdio.h>
#include <glib-object.h>


 typedef union 				_IoJdsdcoreRegReset IoJdsdcoreRegReset;
 typedef union 				_IoJdsdcoreRegIfs IoJdsdcoreRegIfs;
 typedef union 				_IoJdsdcoreRegTrg IoJdsdcoreRegTrg;
 typedef union 				_IoJdsdcoreRegTgkst IoJdsdcoreRegTgkst;
 typedef union 				_IoJdsdcoreRegToctl IoJdsdcoreRegToctl;
 typedef union 				_IoJdsdcoreRegIntc IoJdsdcoreRegIntc;
 typedef union 				_IoJdsdcoreRegInte IoJdsdcoreRegInte;
 typedef union 				_IoJdsdcoreRegIntf IoJdsdcoreRegIntf;
 typedef union 				_IoJdsdcoreRegAxists IoJdsdcoreRegAxists;
 typedef union 				_IoJdsdcoreRegRpgctl IoJdsdcoreRegRpgctl;
 typedef union 				_IoJdsdcoreRegRpgen IoJdsdcoreRegRpgen;
 typedef union 				_IoJdsdcoreRegPolsel IoJdsdcoreRegPolsel;
 typedef union 				_IoJdsdcoreRegTsl IoJdsdcoreRegTsl;
 typedef union 				_IoJdsdcoreRegVcyc IoJdsdcoreRegVcyc;
 typedef union	 			_IoJdsdcoreRegHcyc IoJdsdcoreRegHcyc;
 typedef union 				_IoJdsdcoreRegOvpw IoJdsdcoreRegOvpw;
 typedef union 				_IoJdsdcoreRegHpw IoJdsdcoreRegHpw;
 typedef union 				_IoJdsdcoreRegVblk IoJdsdcoreRegVblk;
 typedef union 				_IoJdsdcoreRegHblk IoJdsdcoreRegHblk;
 typedef union 				_IoJdsdcoreRegVdly IoJdsdcoreRegVdly;
 typedef union 				_IoJdsdcoreRegHdly IoJdsdcoreRegHdly;
 typedef union 				_IoJdsdcoreRegOvsize IoJdsdcoreRegOvsize;
 typedef union 				_IoJdsdcoreRegOhsize IoJdsdcoreRegOhsize;
 typedef union 				_IoJdsdcoreRegVrfctl IoJdsdcoreRegVrfctl;
 typedef union 				_IoJdsdcoreRegHrfctl IoJdsdcoreRegHrfctl;
 typedef union 				_IoJdsdcoreRegHablk IoJdsdcoreRegHablk;
 typedef union 				_IoJdsdcoreRegDomd IoJdsdcoreRegDomd;
 typedef union 				_IoJdsdcoreRegFdoen IoJdsdcoreRegFdoen;
 typedef union 				_IoJdsdcoreRegFodata IoJdsdcoreRegFodata;
 typedef union 				_IoJdsdcoreRegBlankdt1 IoJdsdcoreRegBlankdt1;
 typedef union 				_IoJdsdcoreRegBlankdt2 IoJdsdcoreRegBlankdt2;
 typedef struct 				_IoJdsdcoreRegBlankdt IoJdsdcoreRegBlankdt;
 typedef union 				_IoJdsdcoreRegClbhsize IoJdsdcoreRegClbhsize;
 typedef union 				_IoJdsdcoreRegClbdt IoJdsdcoreRegClbdt;
 typedef union 				_IoJdsdcoreRegBldctl IoJdsdcoreRegBldctl;
 typedef union 				_IoJdsdcoreRegR2y IoJdsdcoreRegR2y;
 typedef union 				_IoJdsdcoreRegYcal IoJdsdcoreRegYcal;
 typedef union 				_IoJdsdcoreRegYclip IoJdsdcoreRegYclip;
 typedef union 				_IoJdsdcoreRegCbcal IoJdsdcoreRegCbcal;
 typedef union 				_IoJdsdcoreRegCbclip IoJdsdcoreRegCbclip;
 typedef union 				_IoJdsdcoreRegCrcal IoJdsdcoreRegCrcal;
 typedef union 				_IoJdsdcoreRegCrclip IoJdsdcoreRegCrclip;
 typedef union 				_IoJdsdcoreRegDoctl0 IoJdsdcoreRegDoctl0;
 typedef union 				_IoJdsdcoreRegDoctl1 IoJdsdcoreRegDoctl1;
 typedef union 				_IoJdsdcoreRegDoctl2 IoJdsdcoreRegDoctl2;
 typedef union 				_IoJdsdcoreRegTrscode0 IoJdsdcoreRegTrscode0;
 typedef union 				_IoJdsdcoreRegTrscode1 IoJdsdcoreRegTrscode1;
 typedef union 				_IoJdsdcoreRegY2r IoJdsdcoreRegY2r;
 typedef union 				_IoJdsdcoreRegTblaset IoJdsdcoreRegTblaset;
 typedef union 				_IoJdsdcoreRegGhdsta IoJdsdcoreRegGhdsta;
 typedef union 				_IoJdsdcoreRegGvdsta IoJdsdcoreRegGvdsta;
 typedef union 				_IoJdsdcoreRegGlength IoJdsdcoreRegGlength;
 typedef union 				_IoJdsdcoreRegGwidth IoJdsdcoreRegGwidth;
 typedef union 				_IoJdsdcoreRegGitvl IoJdsdcoreRegGitvl;
 typedef union 				_IoJdsdcoreRegGnum IoJdsdcoreRegGnum;
 typedef union 				_IoJdsdcoreRegGdctl IoJdsdcoreRegGdctl;
 typedef union 				_IoJdsdcoreRegGdispen IoJdsdcoreRegGdispen;
 typedef union 				_IoJdsdcoreRegFfdsta IoJdsdcoreRegFfdsta;
 typedef union 				_IoJdsdcoreRegFfsize IoJdsdcoreRegFfsize;
 typedef union 				_IoJdsdcoreRegFfwidth IoJdsdcoreRegFfwidth;
 typedef union 				_IoJdsdcoreRegFfclr IoJdsdcoreRegFfclr;
 typedef union 				_IoJdsdcoreRegFfdispen IoJdsdcoreRegFfdispen;
 typedef union 				_IoJdsdcoreRegFfdo IoJdsdcoreRegFfdo;
 typedef struct 				_IoJdsdcoreReg IoJdsdcoreReg;

 union _IoJdsdcoreRegReset{
     gulong       word;
     struct {
         gulong   sr  :1;
         gulong       :31;
     }bit;
 };

 /*  structure of IFS    (2890_1100h)    */
 union _IoJdsdcoreRegIfs{
     gulong       word;
     struct {
         gulong   ifs :2;
         gulong       :30;
     }bit;
 };

 /*  structure of TRG    (2890_1200h)    */
 union _IoJdsdcoreRegTrg{
     gulong       word;
     struct {
         gulong   trg     :2;
         gulong           :2;
         gulong   tgkmd   :1;
         gulong           :27;
     }bit;
 };

 /*  structure of TGKST  (2890_1204h)    */
 union _IoJdsdcoreRegTgkst{
     gulong       word;
     struct {
         gulong   tgkdl   :12;
         gulong           :20;
     }bit;
 };

 /*  structure of TOCTL  (2890_1208h)    */
 union _IoJdsdcoreRegToctl{
     gulong       word;
     struct {
         gulong   con     :1;
         gulong           :3;
         gulong           :2;
         gulong           :2;
         gulong   ckoen   :1;
         gulong   ckicen  :1;
         gulong           :2;
         gulong           :4;
         gulong   wben    :1;
         gulong           :15;
     }bit;
 };

 /*  structure of INTC   (2890_120Ch)    */
 union _IoJdsdcoreRegIntc{
     gulong       word;
     struct {
         gulong   vftmg   :2;
         gulong           :30;
     }bit;
 };

 /*  structure of INTE   (2890_1210h)    */
 union _IoJdsdcoreRegInte{
     gulong       word;
     struct {
         gulong   lee     :1;
         gulong           :3;
         gulong   gr0ee   :1;
         gulong   gr1ee   :1;
         gulong   ga0ee   :1;
         gulong   ga1ee   :1;
         gulong   lree    :1;
         gulong           :3;
         gulong   gr0ree  :1;
         gulong   gr1ree  :1;
         gulong   ga0ree  :1;
         gulong   ga1ree  :1;
         gulong   ve      :1;
         gulong           :3;
         gulong   ve2     :1;
         gulong           :11;
     }bit;
 };

 /*  structure of INTF   (2890_1214h)    */
 union _IoJdsdcoreRegIntf{
     gulong       word;
     struct {
         gulong   lef     :1;
         gulong           :3;
         gulong   gr0ef   :1;
         gulong   gr1ef   :1;
         gulong   ga0ef   :1;
         gulong   ga1ef   :1;
         gulong   lref    :1;
         gulong           :3;
         gulong   gr0ref  :1;
         gulong   gr1ref  :1;
         gulong   ga0ref  :1;
         gulong   ga1ref  :1;
         gulong   vf      :1;
         gulong           :3;
         gulong   vf2     :1;
         gulong           :11;
     }bit;
 };

 /*  structure of AXISTS (2890_1218h)    */
 union _IoJdsdcoreRegAxists{
     gulong       word;
     struct {
         gulong   lresp       :2;
         gulong               :2;
         gulong               :2;
         gulong               :2;
         gulong               :2;
         gulong               :2;
         gulong               :2;
         gulong               :2;
         gulong   gr0resp     :2;
         gulong               :2;
         gulong   gr1resp     :2;
         gulong               :2;
         gulong   gra0resp    :2;
         gulong               :2;
         gulong   gra1resp    :2;
         gulong               :2;
     }bit;
 };

 /*  structure of RPGCTL (2890_1220h)    */
 union _IoJdsdcoreRegRpgctl{
     gulong       word;
     struct {
         gulong   rpgtmg  :1;
         gulong           :31;
     }bit;
 };

 /*  structure of RPGEN  (2890_1224h)    */
 union _IoJdsdcoreRegRpgen{
     gulong       word;
     struct {
         gulong   rpgen   :1;
         gulong           :31;
     }bit;
 };

 /*  structure of POLSEL (2890_1300h)    */
 union _IoJdsdcoreRegPolsel{
     gulong       word;
     struct {
         gulong   vdps    :1;
         gulong           :3;
         gulong   hdps    :1;
         gulong           :3;
         gulong   veps    :1;
         gulong           :3;
         gulong   heps    :1;
         gulong           :3;
         gulong   ckeg    :1;
         gulong           :15;
     }bit;
 };

 /*  structure of TSL    (2890_1304h)    */
 union _IoJdsdcoreRegTsl{
     gulong       word;
     struct {
         gulong   tsl :1;
         gulong       :31;
     }bit;
 };

 /*  structure of VCYC   (2890_1308h)    */
 union _IoJdsdcoreRegVcyc{
     gulong       word;
     struct {
         gulong   vcyc1   :14;
         gulong           :2;
         gulong   vcyc2   :14;
         gulong           :1;
         gulong   vdsft   :1;
     }bit;
 };

 /*  structure of HCYC   (2890_130Ch)    */
 union _IoJdsdcoreRegHcyc{
     gulong       word;
     struct {
         gulong   hcyc    :16;
         gulong           :16;
     }bit;
 };

 /*  structure of OVPW   (2890_1310h)    */
 union _IoJdsdcoreRegOvpw{
     gulong       word;
     struct {
         gulong   ovpw    :10;
         gulong           :2;
         gulong           :1;
         gulong           :3;
         gulong   ovpwu   :1;
         gulong           :15;
     }bit;
 };

 /*  structure of HPW    (2890_1314h)    */
 union _IoJdsdcoreRegHpw{
     gulong       word;
     struct {
         gulong   hpw :10;
         gulong       :22;
     }bit;
 };

 /*  structure of VBLK   (2890_1318h)    */
 union _IoJdsdcoreRegVblk{
     gulong       word;
     struct {
         gulong   vblk1   :8;
         gulong   vblk2   :8;
         gulong           :16;
     }bit;
 };

 /*  structure of HBLK   (2890_131Ch)    */
 union _IoJdsdcoreRegHblk{
     gulong       word;
     struct {
         gulong   hblk    :10;
         gulong           :22;
     }bit;
 };

 /*  structure of VDLY   (2890_1320h)    */
 union _IoJdsdcoreRegVdly{
     gulong       word;
     struct {
         gulong   vdly    :8;
         gulong           :24;
     }bit;
 };

 /*  structure of HDLY   (2890_1324h)    */
 union _IoJdsdcoreRegHdly{
     gulong       word;
     struct {
         gulong   hdly    :8;
         gulong           :24;
     }bit;
 };

 /*  structure of OVSIZE (2890_1328h)    */
 union _IoJdsdcoreRegOvsize{
     gulong       word;
     struct {
         gulong   ovsize  :14;
         gulong           :18;
     }bit;
 };

 /*  structure of OHSIZE (2890_132Ch)    */
 union _IoJdsdcoreRegOhsize{
     gulong       word;
     struct {
         gulong   ohsize  :16;
         gulong           :16;
     }bit;
 };

 /*  structure of VRFCTL (2890_1330h)    */
 union _IoJdsdcoreRegVrfctl{
     gulong       word;
     struct {
         gulong   vens    :1;
         gulong           :31;
     }bit;
 };

 /*  structure of HRFCTL (2890_1338h)    */
 union _IoJdsdcoreRegHrfctl{
     gulong       word;
     struct {
         gulong   hens    :1;
         gulong           :31;
     }bit;
 };

 /*  structure of HABLK  (2890_1340h)    */
 union _IoJdsdcoreRegHablk{
     gulong       word;
     struct {
         gulong   hablk   :12;
         gulong           :20;
     }bit;
 };

 /*  structure of DOMD   (2890_1400h)    */
 union _IoJdsdcoreRegDomd{
     gulong       word;
     struct {
         gulong   mode    :8;
         gulong           :8;
         gulong   obpsl   :1;
         gulong           :3;
         gulong           :4;
         gulong   obusl   :2;
         gulong           :6;
     }bit;
 };

 /*  structure of FDOEN  (2890_1410h)    */
 union _IoJdsdcoreRegFdoen{
     gulong       word;
     struct {
         gulong   fden    :1;
         gulong           :31;
     }bit;
 };

 /*  structure of FODATA (2890_1414h)    */
 union _IoJdsdcoreRegFodata{
     gulong       word;
     struct {
         gulong   fod0   :8;
         gulong   fod1   :8;
         gulong   fod2   :8;
         gulong           :8;
     }bit;
 };

 /*  structure of BLANKDT    (2890_1420h)    */
 union _IoJdsdcoreRegBlankdt1{
     gulong       word;
     struct {
         gulong   bdt0   :16;
         gulong   bdt1   :16;
     }bit;
 };
 union _IoJdsdcoreRegBlankdt2{
     gulong       word;
     struct {
         gulong   bdt2   :16;
         gulong           :16;
     }bit;
 };
 struct _IoJdsdcoreRegBlankdt{
	 IoJdsdcoreRegBlankdt1 blankdt1;
	 IoJdsdcoreRegBlankdt2 blankdt2;
 };

 /*  structure of CLBHSIZE   (2890_1430h)    */
 union _IoJdsdcoreRegClbhsize{
     gulong       word;
     struct {
         gulong   clbhsize    :16;
         gulong               :16;
     }bit;
 };

 /*  structure of CLBDT  (2890_1440h)    */
 union _IoJdsdcoreRegClbdt{
     gulong       word;
     struct {
         gulong   clbr    :8;
         gulong   clbg    :8;
         gulong   clbb    :8;
         gulong           :8;
     }bit;
 };

 /*  structure of BLDCTL (2890_1480h)    */
 union _IoJdsdcoreRegBldctl{
     gulong       word;
     struct {
         gulong   bld1    :2;
         gulong           :2;
         gulong   bld2    :2;
         gulong           :2;
         gulong   bld3    :2;
         gulong           :2;
         gulong   bld4    :2;
         gulong           :18;
     }bit;
 };

 /*  structure of R2Y0/R2Y1/R2Y2   (2890_1490h)    */
 union _IoJdsdcoreRegR2y{
     unsigned long long      dword;
     struct {
         unsigned long long  ry0     :16;
         unsigned long long  ry1     :16;
         unsigned long long  ry2     :16;
         unsigned long long          :16;
     }bit;
 };

 /*  structure of YCAL   (2890_14B0h)    */
 union _IoJdsdcoreRegYcal{
     unsigned long long      dword;
     struct {
         unsigned long long  ygain   :17;
         unsigned long long          :15;
         unsigned long long  yofs    :13;
         unsigned long long          :19;
     }bit;
 };

 /*  structure of YCLIP  (2890_14B8h)    */
 union _IoJdsdcoreRegYclip{
     gulong       word;
     struct {
         gulong   ycph    :16;
         gulong   ycpl    :16;
     }bit;
 };

 /*  structure of CBCAL  (2890_14BCh)    */
 union _IoJdsdcoreRegCbcal{
     gulong       word;
     struct {
         gulong   cbgain  :16;
         gulong   cbofs   :14;
         gulong           :2;
     }bit;
 };

 /*  structure of CBCLIP (2890_14C0h)    */
 union _IoJdsdcoreRegCbclip{
     gulong       word;
     struct {
         gulong   cbcph   :16;
         gulong   cbcpl   :16;
     }bit;
 };

 /*  structure of CRCAL  (2890_14C4h)    */
 union _IoJdsdcoreRegCrcal{
     gulong       word;
     struct {
         gulong   crgain  :16;
         gulong   crofs   :14;
         gulong           :2;
     }bit;
 };

 /*  structure of CRCLIP (2890_14C8h)    */
 union _IoJdsdcoreRegCrclip{
     gulong       word;
     struct {
         gulong   crcph   :16;
         gulong   crcpl   :16;
     }bit;
 };

 /*  structure of DOCTL0 (2890_14D0h)    */
 union _IoJdsdcoreRegDoctl0{
     gulong       word;
     struct {
         gulong   dto1    :2;
         gulong           :2;
         gulong   dto2    :2;
         gulong           :2;
         gulong   dto3    :2;
         gulong           :2;
         gulong   dto4    :2;
         gulong           :2;
         gulong   dto5    :2;
         gulong           :2;
         gulong   dto6    :2;
         gulong           :10;
     }bit;
 };

 /*  structure of DOCTL1 (2890_14D4h)    */
 union _IoJdsdcoreRegDoctl1{
     gulong       word;
     struct {
         gulong   soo     :1;
         gulong           :3;
         gulong   soe     :1;
         gulong           :3;
         gulong   odo0    :1;
         gulong   odo1    :1;
         gulong   odo2    :1;
         gulong           :1;
         gulong   ode0    :1;
         gulong   ode1    :1;
         gulong   ode2    :1;
         gulong           :17;
     }bit;
 };

 /*  structure of DOCTL2 (2890_14D8h)    */
 union _IoJdsdcoreRegDoctl2{
     gulong       word;
     struct {
         gulong   clvs    :1;
         gulong           :3;
         gulong   ctoh    :2;
         gulong           :2;
         gulong   ctov    :1;
         gulong           :3;
         gulong           :4;
         gulong   trsos   :2;
         gulong           :14;
     }bit;
 };

 /*  structure of TRSCODE0   (2890_14E0h)    */
 union _IoJdsdcoreRegTrscode0{
     gulong       word;
     struct {
         gulong   eav00   :8;
         gulong   sav00   :8;
         gulong   eav01   :8;
         gulong   sav01   :8;
     }bit;
 };

 /*  structure of TRSCODE1   (2890_14E4h)    */
 union _IoJdsdcoreRegTrscode1{
     gulong       word;
     struct {
         gulong   eav10   :8;
         gulong   sav10   :8;
         gulong   eav11   :8;
         gulong   sav11   :8;
     }bit;
 };

 /*  structure of Y2R0-2   (2890_14F0h)    */
 union _IoJdsdcoreRegY2r{
     unsigned long long      dword;
     struct {
         unsigned long long  yr0     :16;
         unsigned long long  yr1     :16;
         unsigned long long  yr2     :16;
         unsigned long long          :16;
     }bit;
 };

 /*  structure of TBLASET    (2890_1510h)    */
 union _IoJdsdcoreRegTblaset{
     gulong       word;
     struct {
         gulong   gmtaen  :1;
         gulong   gmen    :1;
         gulong   gmtsl   :1;
         gulong           :1;
         gulong           :1;
         gulong           :3;
         gulong   ysatta  :1;
         gulong   ysaten  :1;
         gulong   ysatsl  :1;
         gulong           :1;
         gulong           :1;
         gulong           :3;
         gulong   gmtmn   :1;
         gulong           :3;
         gulong           :1;
         gulong           :3;
         gulong   ysatmn  :1;
         gulong           :7;
     }bit;
 };

 /*  structure of GHDSTA (2890_1600h)    */
 union _IoJdsdcoreRegGhdsta{
     gulong       word;
     struct {
         gulong   ghdsh   :16;
         gulong   ghdsv   :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GVDSTA (2890_1604h)    */
 union _IoJdsdcoreRegGvdsta{
     gulong       word;
     struct {
         gulong   gvdsh   :16;
         gulong   gvdsv   :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GLENGTH    (2890_1608h)    */
 union _IoJdsdcoreRegGlength{
     gulong       word;
     struct {
         gulong   ghlen   :16;
         gulong   gvlen   :14;
         gulong           :2;
     }bit;
 };

 /*  structure of GWIDTH (2890_160Ch)    */
 union _IoJdsdcoreRegGwidth{
     gulong       word;
     struct {
         gulong   ghwid   :6;
         gulong           :2;
         gulong           :8;
         gulong   gvwid   :6;
         gulong           :10;
     }bit;
 };

 /*  structure of GITVL  (2890_1610h)    */
 union _IoJdsdcoreRegGitvl{
     gulong       word;
     struct {
         gulong   ghitv   :14;
         gulong           :2;
         gulong   gvitv   :16;
     }bit;
 };

 /*  structure of GNUM   (2890_1614h)    */
 union _IoJdsdcoreRegGnum{
     gulong       word;
     struct {
         gulong   ghnum   :3;
         gulong           :5;
         gulong           :8;
         gulong   gvnum   :3;
         gulong           :13;
     }bit;
 };

 /*  structure of GDCTL  (2890_1618h)    */
 union _IoJdsdcoreRegGdctl{
     gulong       word;
     struct {
         gulong   gclrr   :8;
         gulong   gclrg   :8;
         gulong   gclrb   :8;
         gulong   galp    :2;
         gulong           :6;
     }bit;
 };

 /*  structure of GDISPEN    (2890_1620h)    */
 union _IoJdsdcoreRegGdispen{
     gulong       word;
     struct {
         gulong   gden    :1;
         gulong           :31;
     }bit;
 };

 /*  structure of FFDSTA (2890_1800h)    */
 union _IoJdsdcoreRegFfdsta{
     gulong       word;
     struct {
         gulong   ffdsh       :16;
         gulong   ffdsv       :14;
         gulong               :2;
     }bit;
 };

 /*  structure of FFSIZE (2890_1900h)    */
 union _IoJdsdcoreRegFfsize{
     gulong       word;
     struct {
         gulong   ffhsz       :16;
         gulong   ffvsz       :14;
         gulong               :2;
     }bit;
 };

 /*  structure of FFWIDTH    (2890_1A00h)    */
 union _IoJdsdcoreRegFfwidth{
     gulong       word;
     struct {
         gulong   ffhwid      :6;
         gulong               :2;
         gulong               :8;
         gulong   ffvwid      :6;
         gulong               :10;
     }bit;
 };

 /*  structure of FFCLR  (2890_1B00h)    */
 union _IoJdsdcoreRegFfclr{
     gulong       word;
     struct {
         gulong   ffclrr      :8;
         gulong   ffclrg      :8;
         gulong   ffclrb      :8;
         gulong               :8;
     }bit;
 };

 /*  structure of FFDISPEN   (2890_1C00h)    */
 union _IoJdsdcoreRegFfdispen{
     unsigned long long      dword;
     struct {
         unsigned long long  ffden   :42;
         unsigned long long          :22;
     }bit;
 };

 /*  structure of FFDO   (2890_1C08h)    */
 union _IoJdsdcoreRegFfdo{
     gulong       word;
     struct {
         gulong   msff    :6;
         gulong           :26;
     }bit;
 };

 /* Define i/o mapping */
 struct _IoJdsdcoreReg{
	 /* 2890_(1000 - 1003h) */
	 IoJdsdcoreRegReset    reset;
	 /* 2890_(1004 - 10FFh) */
     guchar dmy100410ff[0x1100-0x1004];
     /* 2890_(1100 - 1103h) */
     IoJdsdcoreRegIfs      ifs;
     /* 2890_(1104 - 11FFh) */
     guchar dmy110411ff[0x1200-0x1104];
     /* 2890_(1200 - 1203h) */
     IoJdsdcoreRegTrg      trg;
     /* 2890_(1204 - 1207h) */
     IoJdsdcoreRegTgkst    tgkst;
     /* 2890_(1208 - 120Bh) */
     IoJdsdcoreRegToctl    toctl;
     /* 2890_(120C - 120Fh) */
     IoJdsdcoreRegIntc     intc;
     /* 2890_(1210 - 1213h) */
     IoJdsdcoreRegInte     inte;
     /* 2890_(1214 - 1217h) */
     IoJdsdcoreRegIntf     intf;
     /* 2890_(1218 - 121Bh) */
     IoJdsdcoreRegAxists   axists;
     /* 2890_(121C - 121Fh) */
     guchar dmy121c121f[0x1220-0x121C];
     /* 2890_(1220 - 1223h) */
     IoJdsdcoreRegRpgctl   rpgctl;
     /* 2890_(1224 - 1227h) */
     IoJdsdcoreRegRpgen    rpgen;
     /* 2890_(1228 - 12FFh) */
     guchar dmy122812ff[0x1300-0x1228];
     /* 2890_(1300 - 1303h) */
     IoJdsdcoreRegPolsel   polsel;
     /* 2890_(1304 - 1307h) */
     IoJdsdcoreRegTsl      tsl;
     /* 2890_(1308 - 130Bh) */
     IoJdsdcoreRegVcyc     vcyc;
     /* 2890_(130C - 130Fh) */
     IoJdsdcoreRegHcyc     hcyc;
     /* 2890_(1310 - 1313h) */
     IoJdsdcoreRegOvpw     ovpw;
     /* 2890_(1314 - 1317h) */
     IoJdsdcoreRegHpw      hpw;
     /* 2890_(1318 - 131Bh) */
     IoJdsdcoreRegVblk     vblk;
     /* 2890_(131C - 131Fh) */
     IoJdsdcoreRegHblk     hblk;
     /* 2890_(1320 - 1323h) */
     IoJdsdcoreRegVdly     vdly;
     /* 2890_(1324 - 1327h) */
     IoJdsdcoreRegHdly     hdly;
     /* 2890_(1328 - 132Bh) */
     IoJdsdcoreRegOvsize   ovsize;
     /* 2890_(132C - 132Fh) */
     IoJdsdcoreRegOhsize   ohsize;
     /* 2890_(1330 - 1333h) */
     IoJdsdcoreRegVrfctl   vrfctl;
     /* 2890_(1334 - 1337h) */
     guchar dmy13341337[0x1338-0x1334];
     /* 2890_(1338 - 133Bh) */
     IoJdsdcoreRegHrfctl   HRFCTL;
     /* 2890_(133C - 133Fh) */
     guchar dmy133c133f[0x1340-0x133C];
     /* 2890_(1340 - 1343h) */
     IoJdsdcoreRegHablk    HABLK;
     /* 2890_(1344 - 13FFh) */
     guchar dmy134413ff[0x1400-0x1344];
     /* 2890_(1400 - 1403h) */
     IoJdsdcoreRegDomd     domd;
     /* 2890_(1404 - 140Fh) */
     guchar dmy1404140f[0x1410-0x1404];
     /* 2890_(1410 - 1413h) */
     IoJdsdcoreRegFdoen    fdoen;
     /* 2890_(1414 - 1417h) */
     IoJdsdcoreRegFodata   fodata;
     /* 2890_(1418 - 141Fh) */
     guchar dmy1418141f[0x1420-0x1418];
     /* 2890_(1420 - 1427h) */
     IoJdsdcoreRegBlankdt  blankdt;
     /* 2890_(1428 - 142Fh) */
     guchar dmy1428142f[0x1430-0x1428];
     /* 2890_(1430 - 1433h) */
     IoJdsdcoreRegClbhsize clbhsize;
     /* 2890_(1434 - 143Fh) */
     guchar dmy1434143f[0x1440-0x1434];
     /* 2890_(1440 - 147Fh) */
     IoJdsdcoreRegClbdt    clbdt[16];
     /* 2890_(1480 - 1483h) */
     IoJdsdcoreRegBldctl   bldctl;
     /* 2890_(1484 - 148Fh) */
     guchar dmy1484148f[0x1490-0x1484];
     /* 2890_(1490 - 14A7h) */
     IoJdsdcoreRegR2y      r2y[3];
     /* 2890_(14A8 - 14AFh) */
     guchar dmy14a814af[0x14B0-0x14A8];
     /* 2890_(14B0 - 14B7h) */
     IoJdsdcoreRegYcal     ycal;
     /* 2890_(14B8 - 14BBh) */
     IoJdsdcoreRegYclip    yclip;
     /* 2890_(14BC - 14BFh) */
     IoJdsdcoreRegCbcal    cbcal;
     /* 2890_(14C0 - 14C3h) */
     IoJdsdcoreRegCbclip   cbclip;
     /* 2890_(14C4 - 14C7h) */
     IoJdsdcoreRegCrcal    crcal;
     /* 2890_(14C8 - 14CBh) */
     IoJdsdcoreRegCrclip   crclip;
     /* 2890_(14CC - 14CFh) */
     guchar dmy14cc14cf[0x14D0-0x14CC];
     /* 2890_(14D0 - 14D3h) */
     IoJdsdcoreRegDoctl0   doctl0;
     /* 2890_(14D4 - 14D7h) */
     IoJdsdcoreRegDoctl1   doctl1;
     /* 2890_(14D8 - 14DBh) */
     IoJdsdcoreRegDoctl2   doctl2;
     /* 2890_(14DC - 14DFh) */
     guchar dmy14dc14df[0x14E0-0x14DC];
     /* 2890_(14E0 - 14E3h) */
     IoJdsdcoreRegTrscode0 trscode0;
     /* 2890_(14E4 - 14E7h) */
     IoJdsdcoreRegTrscode1 trscode1;
     /* 2890_(14E8 - 14EFh) */
     guchar dmy14e814ef[0x14F0-0x14E8];
     /* 2890_(14F0 - 1507h) */
     IoJdsdcoreRegY2r      y2r[3];
     /* 2890_(1508 - 150Fh) */
     guchar dmy1508150f[0x1510-0x1508];
     /* 2890_(1510 - 1513h) */
     IoJdsdcoreRegTblaset  TBLASET;
     /* 2890_(1514 - 15FFh) */
     guchar dmy151415FF[0x1600-0x1514];
     /* 2890_(1600 - 1603h) */
     IoJdsdcoreRegGhdsta   ghdsta;
     /* 2890_(1604 - 1607h) */
     IoJdsdcoreRegGvdsta   gvdsta;
     /* 2890_(1608 - 160Bh) */
     IoJdsdcoreRegGlength  glength;
     /* 2890_(160C - 160Fh) */
     IoJdsdcoreRegGwidth   gwidth;
     /* 2890_(1610 - 1613h) */
     IoJdsdcoreRegGitvl    gitvl;
     /* 2890_(1614 - 1617h) */
     IoJdsdcoreRegGnum     gnum;
     /* 2890_(1618 - 161Bh) */
     IoJdsdcoreRegGdctl    gdctl;
     /* 2890_(161C - 161Fh) */
     guchar dmy161c161f[0x1620-0x161C];
     /* 2890_(1620 - 1623h) */
     IoJdsdcoreRegGdispen  gdispen;
     /* 2890_(1624 - 17FFh) */
     guchar dmy162417ff[0x1800-0x1624];
     /* 2890_(1800 - 18A7h) */
     IoJdsdcoreRegFfdsta   ffdsta[42];
     /* 2890_(18A8 - 18FFh) */
     guchar dmy18a818ff[0x1900-0x18A8];
     /* 2890_(1900 - 19A7h) */
     IoJdsdcoreRegFfsize   ffsize[42];
     /* 2890_(19A8 - 19FFh) */
     guchar dmy19a819ff[0x1A00-0x19A8];
     /* 2890_(1A00 - 1AA7h) */
     IoJdsdcoreRegFfwidth  ffwidth[42];
     /* 2890_(1AA8 - 1AFFh) */
     guchar dmy1aa81aff[0x1B00-0x1AA8];
     /* 2890_(1B00 - 1BA7h) */
     IoJdsdcoreRegFfclr    ffclr[42];
     /* 2890_(1BA8 - 1BFFh) */
     guchar dmy1ba81bff[0x1C00-0x1BA8];
     /* 2890_(1C00 - 1C07h) */
     IoJdsdcoreRegFfdispen ffdispen;
     /* 2890_(1C08 - 1C0Bh) */
     IoJdsdcoreRegFfdo     ffdo;
     /* 2890_(1C0C - 1FFFh) */
     guchar dmy1c0c1fff[0x2000-0x1C0C];
 };


 #endif/*__JDSDISP_DCORE_H__*/
