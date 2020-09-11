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


 #ifndef __JDSDISP_DCORE_H__
 #define __JDSDISP_DCORE_H__


 #include <klib.h>


 #define JDSDISP_TYPE_DCORE				(jdsdisp_dcore_get_type())
 #define JDSDISP_DCORE(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispDcore))
 #define JDSDISP_IS_DCORE(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_DCORE))


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
 typedef struct 				_JdsdispDcore JdsdispDcore;
 typedef struct 				_JdsdispDcorePrivate	JdsdispDcorePrivate;

 union _IoJdsdcoreRegReset{
     kulong       word;
     struct {
         kulong   sr  :1;
         kulong       :31;
     }bit;
 };

 /*  structure of IFS    (2890_1100h)    */
 union _IoJdsdcoreRegIfs{
     kulong       word;
     struct {
         kulong   ifs :2;
         kulong       :30;
     }bit;
 };

 /*  structure of TRG    (2890_1200h)    */
 union _IoJdsdcoreRegTrg{
     kulong       word;
     struct {
         kulong   trg     :2;
         kulong           :2;
         kulong   tgkmd   :1;
         kulong           :27;
     }bit;
 };

 /*  structure of TGKST  (2890_1204h)    */
 union _IoJdsdcoreRegTgkst{
     kulong       word;
     struct {
         kulong   tgkdl   :12;
         kulong           :20;
     }bit;
 };

 /*  structure of TOCTL  (2890_1208h)    */
 union _IoJdsdcoreRegToctl{
     kulong       word;
     struct {
         kulong   con     :1;
         kulong           :3;
         kulong           :2;
         kulong           :2;
         kulong   ckoen   :1;
         kulong   ckicen  :1;
         kulong           :2;
         kulong           :4;
         kulong   wben    :1;
         kulong           :15;
     }bit;
 };

 /*  structure of INTC   (2890_120Ch)    */
 union _IoJdsdcoreRegIntc{
     kulong       word;
     struct {
         kulong   vftmg   :2;
         kulong           :30;
     }bit;
 };

 /*  structure of INTE   (2890_1210h)    */
 union _IoJdsdcoreRegInte{
     kulong       word;
     struct {
         kulong   lee     :1;
         kulong           :3;
         kulong   gr0ee   :1;
         kulong   gr1ee   :1;
         kulong   ga0ee   :1;
         kulong   ga1ee   :1;
         kulong   lree    :1;
         kulong           :3;
         kulong   gr0ree  :1;
         kulong   gr1ree  :1;
         kulong   ga0ree  :1;
         kulong   ga1ree  :1;
         kulong   ve      :1;
         kulong           :3;
         kulong   ve2     :1;
         kulong           :11;
     }bit;
 };

 /*  structure of INTF   (2890_1214h)    */
 union _IoJdsdcoreRegIntf{
     kulong       word;
     struct {
         kulong   lef     :1;
         kulong           :3;
         kulong   gr0ef   :1;
         kulong   gr1ef   :1;
         kulong   ga0ef   :1;
         kulong   ga1ef   :1;
         kulong   lref    :1;
         kulong           :3;
         kulong   gr0ref  :1;
         kulong   gr1ref  :1;
         kulong   ga0ref  :1;
         kulong   ga1ref  :1;
         kulong   vf      :1;
         kulong           :3;
         kulong   vf2     :1;
         kulong           :11;
     }bit;
 };

 /*  structure of AXISTS (2890_1218h)    */
 union _IoJdsdcoreRegAxists{
     kulong       word;
     struct {
         kulong   lresp       :2;
         kulong               :2;
         kulong               :2;
         kulong               :2;
         kulong               :2;
         kulong               :2;
         kulong               :2;
         kulong               :2;
         kulong   gr0resp     :2;
         kulong               :2;
         kulong   gr1resp     :2;
         kulong               :2;
         kulong   gra0resp    :2;
         kulong               :2;
         kulong   gra1resp    :2;
         kulong               :2;
     }bit;
 };

 /*  structure of RPGCTL (2890_1220h)    */
 union _IoJdsdcoreRegRpgctl{
     kulong       word;
     struct {
         kulong   rpgtmg  :1;
         kulong           :31;
     }bit;
 };

 /*  structure of RPGEN  (2890_1224h)    */
 union _IoJdsdcoreRegRpgen{
     kulong       word;
     struct {
         kulong   rpgen   :1;
         kulong           :31;
     }bit;
 };

 /*  structure of POLSEL (2890_1300h)    */
 union _IoJdsdcoreRegPolsel{
     kulong       word;
     struct {
         kulong   vdps    :1;
         kulong           :3;
         kulong   hdps    :1;
         kulong           :3;
         kulong   veps    :1;
         kulong           :3;
         kulong   heps    :1;
         kulong           :3;
         kulong   ckeg    :1;
         kulong           :15;
     }bit;
 };

 /*  structure of TSL    (2890_1304h)    */
 union _IoJdsdcoreRegTsl{
     kulong       word;
     struct {
         kulong   tsl :1;
         kulong       :31;
     }bit;
 };

 /*  structure of VCYC   (2890_1308h)    */
 union _IoJdsdcoreRegVcyc{
     kulong       word;
     struct {
         kulong   vcyc1   :14;
         kulong           :2;
         kulong   vcyc2   :14;
         kulong           :1;
         kulong   vdsft   :1;
     }bit;
 };

 /*  structure of HCYC   (2890_130Ch)    */
 union _IoJdsdcoreRegHcyc{
     kulong       word;
     struct {
         kulong   hcyc    :16;
         kulong           :16;
     }bit;
 };

 /*  structure of OVPW   (2890_1310h)    */
 union _IoJdsdcoreRegOvpw{
     kulong       word;
     struct {
         kulong   ovpw    :10;
         kulong           :2;
         kulong           :1;
         kulong           :3;
         kulong   ovpwu   :1;
         kulong           :15;
     }bit;
 };

 /*  structure of HPW    (2890_1314h)    */
 union _IoJdsdcoreRegHpw{
     kulong       word;
     struct {
         kulong   hpw :10;
         kulong       :22;
     }bit;
 };

 /*  structure of VBLK   (2890_1318h)    */
 union _IoJdsdcoreRegVblk{
     kulong       word;
     struct {
         kulong   vblk1   :8;
         kulong   vblk2   :8;
         kulong           :16;
     }bit;
 };

 /*  structure of HBLK   (2890_131Ch)    */
 union _IoJdsdcoreRegHblk{
     kulong       word;
     struct {
         kulong   hblk    :10;
         kulong           :22;
     }bit;
 };

 /*  structure of VDLY   (2890_1320h)    */
 union _IoJdsdcoreRegVdly{
     kulong       word;
     struct {
         kulong   vdly    :8;
         kulong           :24;
     }bit;
 };

 /*  structure of HDLY   (2890_1324h)    */
 union _IoJdsdcoreRegHdly{
     kulong       word;
     struct {
         kulong   hdly    :8;
         kulong           :24;
     }bit;
 };

 /*  structure of OVSIZE (2890_1328h)    */
 union _IoJdsdcoreRegOvsize{
     kulong       word;
     struct {
         kulong   ovsize  :14;
         kulong           :18;
     }bit;
 };

 /*  structure of OHSIZE (2890_132Ch)    */
 union _IoJdsdcoreRegOhsize{
     kulong       word;
     struct {
         kulong   ohsize  :16;
         kulong           :16;
     }bit;
 };

 /*  structure of VRFCTL (2890_1330h)    */
 union _IoJdsdcoreRegVrfctl{
     kulong       word;
     struct {
         kulong   vens    :1;
         kulong           :31;
     }bit;
 };

 /*  structure of HRFCTL (2890_1338h)    */
 union _IoJdsdcoreRegHrfctl{
     kulong       word;
     struct {
         kulong   hens    :1;
         kulong           :31;
     }bit;
 };

 /*  structure of HABLK  (2890_1340h)    */
 union _IoJdsdcoreRegHablk{
     kulong       word;
     struct {
         kulong   hablk   :12;
         kulong           :20;
     }bit;
 };

 /*  structure of DOMD   (2890_1400h)    */
 union _IoJdsdcoreRegDomd{
     kulong       word;
     struct {
         kulong   mode    :8;
         kulong           :8;
         kulong   obpsl   :1;
         kulong           :3;
         kulong           :4;
         kulong   obusl   :2;
         kulong           :6;
     }bit;
 };

 /*  structure of FDOEN  (2890_1410h)    */
 union _IoJdsdcoreRegFdoen{
     kulong       word;
     struct {
         kulong   fden    :1;
         kulong           :31;
     }bit;
 };

 /*  structure of FODATA (2890_1414h)    */
 union _IoJdsdcoreRegFodata{
     kulong       word;
     struct {
         kulong   fod0   :8;
         kulong   fod1   :8;
         kulong   fod2   :8;
         kulong           :8;
     }bit;
 };

 /*  structure of BLANKDT    (2890_1420h)    */
 union _IoJdsdcoreRegBlankdt1{
     kulong       word;
     struct {
         kulong   bdt0   :16;
         kulong   bdt1   :16;
     }bit;
 };
 union _IoJdsdcoreRegBlankdt2{
     kulong       word;
     struct {
         kulong   bdt2   :16;
         kulong           :16;
     }bit;
 };
 struct _IoJdsdcoreRegBlankdt{
	 IoJdsdcoreRegBlankdt1 blankdt1;
	 IoJdsdcoreRegBlankdt2 blankdt2;
 };

 /*  structure of CLBHSIZE   (2890_1430h)    */
 union _IoJdsdcoreRegClbhsize{
     kulong       word;
     struct {
         kulong   clbhsize    :16;
         kulong               :16;
     }bit;
 };

 /*  structure of CLBDT  (2890_1440h)    */
 union _IoJdsdcoreRegClbdt{
     kulong       word;
     struct {
         kulong   clbr    :8;
         kulong   clbg    :8;
         kulong   clbb    :8;
         kulong           :8;
     }bit;
 };

 /*  structure of BLDCTL (2890_1480h)    */
 union _IoJdsdcoreRegBldctl{
     kulong       word;
     struct {
         kulong   bld1    :2;
         kulong           :2;
         kulong   bld2    :2;
         kulong           :2;
         kulong   bld3    :2;
         kulong           :2;
         kulong   bld4    :2;
         kulong           :18;
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
     kulong       word;
     struct {
         kulong   ycph    :16;
         kulong   ycpl    :16;
     }bit;
 };

 /*  structure of CBCAL  (2890_14BCh)    */
 union _IoJdsdcoreRegCbcal{
     kulong       word;
     struct {
         kulong   cbgain  :16;
         kulong   cbofs   :14;
         kulong           :2;
     }bit;
 };

 /*  structure of CBCLIP (2890_14C0h)    */
 union _IoJdsdcoreRegCbclip{
     kulong       word;
     struct {
         kulong   cbcph   :16;
         kulong   cbcpl   :16;
     }bit;
 };

 /*  structure of CRCAL  (2890_14C4h)    */
 union _IoJdsdcoreRegCrcal{
     kulong       word;
     struct {
         kulong   crgain  :16;
         kulong   crofs   :14;
         kulong           :2;
     }bit;
 };

 /*  structure of CRCLIP (2890_14C8h)    */
 union _IoJdsdcoreRegCrclip{
     kulong       word;
     struct {
         kulong   crcph   :16;
         kulong   crcpl   :16;
     }bit;
 };

 /*  structure of DOCTL0 (2890_14D0h)    */
 union _IoJdsdcoreRegDoctl0{
     kulong       word;
     struct {
         kulong   dto1    :2;
         kulong           :2;
         kulong   dto2    :2;
         kulong           :2;
         kulong   dto3    :2;
         kulong           :2;
         kulong   dto4    :2;
         kulong           :2;
         kulong   dto5    :2;
         kulong           :2;
         kulong   dto6    :2;
         kulong           :10;
     }bit;
 };

 /*  structure of DOCTL1 (2890_14D4h)    */
 union _IoJdsdcoreRegDoctl1{
     kulong       word;
     struct {
         kulong   soo     :1;
         kulong           :3;
         kulong   soe     :1;
         kulong           :3;
         kulong   odo0    :1;
         kulong   odo1    :1;
         kulong   odo2    :1;
         kulong           :1;
         kulong   ode0    :1;
         kulong   ode1    :1;
         kulong   ode2    :1;
         kulong           :17;
     }bit;
 };

 /*  structure of DOCTL2 (2890_14D8h)    */
 union _IoJdsdcoreRegDoctl2{
     kulong       word;
     struct {
         kulong   clvs    :1;
         kulong           :3;
         kulong   ctoh    :2;
         kulong           :2;
         kulong   ctov    :1;
         kulong           :3;
         kulong           :4;
         kulong   trsos   :2;
         kulong           :14;
     }bit;
 };

 /*  structure of TRSCODE0   (2890_14E0h)    */
 union _IoJdsdcoreRegTrscode0{
     kulong       word;
     struct {
         kulong   eav00   :8;
         kulong   sav00   :8;
         kulong   eav01   :8;
         kulong   sav01   :8;
     }bit;
 };

 /*  structure of TRSCODE1   (2890_14E4h)    */
 union _IoJdsdcoreRegTrscode1{
     kulong       word;
     struct {
         kulong   eav10   :8;
         kulong   sav10   :8;
         kulong   eav11   :8;
         kulong   sav11   :8;
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
     kulong       word;
     struct {
         kulong   gmtaen  :1;
         kulong   gmen    :1;
         kulong   gmtsl   :1;
         kulong           :1;
         kulong           :1;
         kulong           :3;
         kulong   ysatta  :1;
         kulong   ysaten  :1;
         kulong   ysatsl  :1;
         kulong           :1;
         kulong           :1;
         kulong           :3;
         kulong   gmtmn   :1;
         kulong           :3;
         kulong           :1;
         kulong           :3;
         kulong   ysatmn  :1;
         kulong           :7;
     }bit;
 };

 /*  structure of GHDSTA (2890_1600h)    */
 union _IoJdsdcoreRegGhdsta{
     kulong       word;
     struct {
         kulong   ghdsh   :16;
         kulong   ghdsv   :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GVDSTA (2890_1604h)    */
 union _IoJdsdcoreRegGvdsta{
     kulong       word;
     struct {
         kulong   gvdsh   :16;
         kulong   gvdsv   :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GLENGTH    (2890_1608h)    */
 union _IoJdsdcoreRegGlength{
     kulong       word;
     struct {
         kulong   ghlen   :16;
         kulong   gvlen   :14;
         kulong           :2;
     }bit;
 };

 /*  structure of GWIDTH (2890_160Ch)    */
 union _IoJdsdcoreRegGwidth{
     kulong       word;
     struct {
         kulong   ghwid   :6;
         kulong           :2;
         kulong           :8;
         kulong   gvwid   :6;
         kulong           :10;
     }bit;
 };

 /*  structure of GITVL  (2890_1610h)    */
 union _IoJdsdcoreRegGitvl{
     kulong       word;
     struct {
         kulong   ghitv   :14;
         kulong           :2;
         kulong   gvitv   :16;
     }bit;
 };

 /*  structure of GNUM   (2890_1614h)    */
 union _IoJdsdcoreRegGnum{
     kulong       word;
     struct {
         kulong   ghnum   :3;
         kulong           :5;
         kulong           :8;
         kulong   gvnum   :3;
         kulong           :13;
     }bit;
 };

 /*  structure of GDCTL  (2890_1618h)    */
 union _IoJdsdcoreRegGdctl{
     kulong       word;
     struct {
         kulong   gclrr   :8;
         kulong   gclrg   :8;
         kulong   gclrb   :8;
         kulong   galp    :2;
         kulong           :6;
     }bit;
 };

 /*  structure of GDISPEN    (2890_1620h)    */
 union _IoJdsdcoreRegGdispen{
     kulong       word;
     struct {
         kulong   gden    :1;
         kulong           :31;
     }bit;
 };

 /*  structure of FFDSTA (2890_1800h)    */
 union _IoJdsdcoreRegFfdsta{
     kulong       word;
     struct {
         kulong   ffdsh       :16;
         kulong   ffdsv       :14;
         kulong               :2;
     }bit;
 };

 /*  structure of FFSIZE (2890_1900h)    */
 union _IoJdsdcoreRegFfsize{
     kulong       word;
     struct {
         kulong   ffhsz       :16;
         kulong   ffvsz       :14;
         kulong               :2;
     }bit;
 };

 /*  structure of FFWIDTH    (2890_1A00h)    */
 union _IoJdsdcoreRegFfwidth{
     kulong       word;
     struct {
         kulong   ffhwid      :6;
         kulong               :2;
         kulong               :8;
         kulong   ffvwid      :6;
         kulong               :10;
     }bit;
 };

 /*  structure of FFCLR  (2890_1B00h)    */
 union _IoJdsdcoreRegFfclr{
     kulong       word;
     struct {
         kulong   ffclrr      :8;
         kulong   ffclrg      :8;
         kulong   ffclrb      :8;
         kulong               :8;
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
     kulong       word;
     struct {
         kulong   msff    :6;
         kulong           :26;
     }bit;
 };

 /* Define i/o mapping */
 struct _IoJdsdcoreReg{
	 /* 2890_(1000 - 1003h) */
	 IoJdsdcoreRegReset    reset;
	 /* 2890_(1004 - 10FFh) */
     kuchar dmy100410ff[0x1100-0x1004];
     /* 2890_(1100 - 1103h) */
     IoJdsdcoreRegIfs      ifs;
     /* 2890_(1104 - 11FFh) */
     kuchar dmy110411ff[0x1200-0x1104];
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
     kuchar dmy121c121f[0x1220-0x121C];
     /* 2890_(1220 - 1223h) */
     IoJdsdcoreRegRpgctl   rpgctl;
     /* 2890_(1224 - 1227h) */
     IoJdsdcoreRegRpgen    rpgen;
     /* 2890_(1228 - 12FFh) */
     kuchar dmy122812ff[0x1300-0x1228];
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
     kuchar dmy13341337[0x1338-0x1334];
     /* 2890_(1338 - 133Bh) */
     IoJdsdcoreRegHrfctl   HRFCTL;
     /* 2890_(133C - 133Fh) */
     kuchar dmy133c133f[0x1340-0x133C];
     /* 2890_(1340 - 1343h) */
     IoJdsdcoreRegHablk    HABLK;
     /* 2890_(1344 - 13FFh) */
     kuchar dmy134413ff[0x1400-0x1344];
     /* 2890_(1400 - 1403h) */
     IoJdsdcoreRegDomd     domd;
     /* 2890_(1404 - 140Fh) */
     kuchar dmy1404140f[0x1410-0x1404];
     /* 2890_(1410 - 1413h) */
     IoJdsdcoreRegFdoen    fdoen;
     /* 2890_(1414 - 1417h) */
     IoJdsdcoreRegFodata   fodata;
     /* 2890_(1418 - 141Fh) */
     kuchar dmy1418141f[0x1420-0x1418];
     /* 2890_(1420 - 1427h) */
     IoJdsdcoreRegBlankdt  blankdt;
     /* 2890_(1428 - 142Fh) */
     kuchar dmy1428142f[0x1430-0x1428];
     /* 2890_(1430 - 1433h) */
     IoJdsdcoreRegClbhsize clbhsize;
     /* 2890_(1434 - 143Fh) */
     kuchar dmy1434143f[0x1440-0x1434];
     /* 2890_(1440 - 147Fh) */
     IoJdsdcoreRegClbdt    clbdt[16];
     /* 2890_(1480 - 1483h) */
     IoJdsdcoreRegBldctl   bldctl;
     /* 2890_(1484 - 148Fh) */
     kuchar dmy1484148f[0x1490-0x1484];
     /* 2890_(1490 - 14A7h) */
     IoJdsdcoreRegR2y      r2y[3];
     /* 2890_(14A8 - 14AFh) */
     kuchar dmy14a814af[0x14B0-0x14A8];
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
     kuchar dmy14cc14cf[0x14D0-0x14CC];
     /* 2890_(14D0 - 14D3h) */
     IoJdsdcoreRegDoctl0   doctl0;
     /* 2890_(14D4 - 14D7h) */
     IoJdsdcoreRegDoctl1   doctl1;
     /* 2890_(14D8 - 14DBh) */
     IoJdsdcoreRegDoctl2   doctl2;
     /* 2890_(14DC - 14DFh) */
     kuchar dmy14dc14df[0x14E0-0x14DC];
     /* 2890_(14E0 - 14E3h) */
     IoJdsdcoreRegTrscode0 trscode0;
     /* 2890_(14E4 - 14E7h) */
     IoJdsdcoreRegTrscode1 trscode1;
     /* 2890_(14E8 - 14EFh) */
     kuchar dmy14e814ef[0x14F0-0x14E8];
     /* 2890_(14F0 - 1507h) */
     IoJdsdcoreRegY2r      y2r[3];
     /* 2890_(1508 - 150Fh) */
     kuchar dmy1508150f[0x1510-0x1508];
     /* 2890_(1510 - 1513h) */
     IoJdsdcoreRegTblaset  TBLASET;
     /* 2890_(1514 - 15FFh) */
     kuchar dmy151415FF[0x1600-0x1514];
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
     kuchar dmy161c161f[0x1620-0x161C];
     /* 2890_(1620 - 1623h) */
     IoJdsdcoreRegGdispen  gdispen;
     /* 2890_(1624 - 17FFh) */
     kuchar dmy162417ff[0x1800-0x1624];
     /* 2890_(1800 - 18A7h) */
     IoJdsdcoreRegFfdsta   ffdsta[42];
     /* 2890_(18A8 - 18FFh) */
     kuchar dmy18a818ff[0x1900-0x18A8];
     /* 2890_(1900 - 19A7h) */
     IoJdsdcoreRegFfsize   ffsize[42];
     /* 2890_(19A8 - 19FFh) */
     kuchar dmy19a819ff[0x1A00-0x19A8];
     /* 2890_(1A00 - 1AA7h) */
     IoJdsdcoreRegFfwidth  ffwidth[42];
     /* 2890_(1AA8 - 1AFFh) */
     kuchar dmy1aa81aff[0x1B00-0x1AA8];
     /* 2890_(1B00 - 1BA7h) */
     IoJdsdcoreRegFfclr    ffclr[42];
     /* 2890_(1BA8 - 1BFFh) */
     kuchar dmy1ba81bff[0x1C00-0x1BA8];
     /* 2890_(1C00 - 1C07h) */
     IoJdsdcoreRegFfdispen ffdispen;
     /* 2890_(1C08 - 1C0Bh) */
     IoJdsdcoreRegFfdo     ffdo;
     /* 2890_(1C0C - 1FFFh) */
     kuchar dmy1c0c1fff[0x2000-0x1C0C];
 };

 struct  _JdsdispDcore
 {
 	KObject parent;
 };


 KConstType				jdsdisp_dcore_get_type(void);
 JdsdispDcore*			jdsdisp_dcore_new(void);


 #endif/*__JDSDISP_DCORE_H__*/
