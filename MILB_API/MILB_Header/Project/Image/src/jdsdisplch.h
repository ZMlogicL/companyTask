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


#ifndef __JDSDISP_LCH_H__
#define __JDSDISP_LCH_H__


#include <klib.h>


#define JDSDISP_TYPE_LCH				(jdsdisp_lch_get_type())
#define JDSDISP_LCH(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), JdsdispLch))
#define JDSDISP_IS_LCH(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), JDSDISP_TYPE_LCH))


typedef union 				_IoJdslchRegLrst IoJdslchRegLrst;
typedef union 				_IoJdslchRegLtrg IoJdslchRegLtrg;
typedef union 				_IoJdslchRegLrpgctl IoJdslchRegLrpgctl;
typedef union 				_IoJdslchRegLidt0 IoJdslchRegLidt0;
typedef union 				_IoJdslchRegLidt1 IoJdslchRegLidt1;
typedef union 				_IoJdslchRegLisize IoJdslchRegLisize;
typedef union 				_IoJdslchRegLysa IoJdslchRegLysa;
typedef union 				_IoJdslchRegLcsa IoJdslchRegLcsa;
typedef union 				_IoJdslchRegLyhga IoJdslchRegLyhga;
typedef union 				_IoJdslchRegLchga IoJdslchRegLchga;
typedef union 				_IoJdslchRegLibctl IoJdslchRegLibctl;
typedef union 				_IoJdslchRegLrsz0 IoJdslchRegLrsz0;
typedef union 				_IoJdslchRegLrsz1 IoJdslchRegLrsz1;
typedef union 				_IoJdslchRegLrsz2 IoJdslchRegLrsz2;
typedef union 				_IoJdslchRegLrsz3 IoJdslchRegLrsz3;
typedef union 				_IoJdslchRegLyhlpctl IoJdslchRegLyhlpctl;
typedef union 				_IoJdslchRegLyhlpk0 IoJdslchRegLyhlpk0;
typedef union 				_IoJdslchRegLyhlpk1 IoJdslchRegLyhlpk1;
typedef union 				_IoJdslchRegLyhlpol IoJdslchRegLyhlpol;
typedef union 				_IoJdslchRegLyhlpclr IoJdslchRegLyhlpclr;
typedef union 				_IoJdslchRegLywctl IoJdslchRegLywctl;
typedef union 				_IoJdslchRegLyw0th IoJdslchRegLyw0th;
typedef union 				_IoJdslchRegLyw1th IoJdslchRegLyw1th;
typedef union 				_IoJdslchRegLyw0st IoJdslchRegLyw0st;
typedef union 				_IoJdslchRegLyw0ca IoJdslchRegLyw0ca;
typedef union 				_IoJdslchRegLyw0cb IoJdslchRegLyw0cb;
typedef union 				_IoJdslchRegLyw1st IoJdslchRegLyw1st;
typedef union 				_IoJdslchRegLyw1ca IoJdslchRegLyw1ca;
typedef union 				_IoJdslchRegLyw1cb IoJdslchRegLyw1cb;
typedef union 				_IoJdslchRegLbltmr IoJdslchRegLbltmr;
typedef union 				_IoJdslchRegLbost IoJdslchRegLbost;
typedef union 				_IoJdslchRegLzbwid IoJdslchRegLzbwid;
typedef union 				_IoJdslchRegLzbv IoJdslchRegLzbv;
typedef union 				_IoJdslchRegLzbpt IoJdslchRegLzbpt;
typedef union 				_IoJdslchRegLy2r IoJdslchRegLy2r;
typedef union 				_IoJdslchRegLtblaset IoJdslchRegLtblaset;
typedef union 				_IoJdslchRegLcc IoJdslchRegLcc;
typedef union 				_IoJdslchRegLgmmd IoJdslchRegLgmmd;
typedef union 				_IoJdslchRegLalp IoJdslchRegLalp;
typedef union 				_IoJdslchRegLdsta IoJdslchRegLdsta;
typedef union 				_IoJdslchRegLrevdisp IoJdslchRegLrevdisp;
typedef struct 				_IoJdslchReg IoJdslchReg;
typedef struct 				_JdsdispLch JdsdispLch;
typedef struct 				_JdsdispLchPrivate	JdsdispLchPrivate;

union _IoJdslchRegLrst{
    kulong       word;
    struct {
        kulong   sr  :1;
        kulong       :31;
    }bit;
};

/*  structure of LTRG   (2890_0100h)    */
union _IoJdslchRegLtrg{
    kulong       word;
    struct {
        kulong   trg :2;
        kulong       :30;
    }bit;
};

/*  structure of LRPGCTL    (2890_0110h)    */
union _IoJdslchRegLrpgctl{
    kulong       word;
    struct {
        kulong   rpgtmg  :1;
        kulong           :31;
    }bit;
};

/*  structure of LIDT0  (2890_0200h)    */
union _IoJdslchRegLidt0{
    kulong       word;
    struct {
        kulong   ifmt    :5;
        kulong           :3;
        kulong   nbt     :2;
        kulong           :2;
        kulong   ifew    :2;
        kulong           :2;
        kulong   lvfm    :1;
        kulong           :15;
    }bit;
};

/*  structure of LIDT1  (2890_0204h)    */
union _IoJdslchRegLidt1{
    kulong       word;
    struct {
        kulong   pkgdv   :4;
        kulong   cache   :4;
        kulong   prot    :3;
        kulong           :1;
        kulong   yslvsl  :1;
        kulong   cslvsl  :1;
        kulong           :18;
    }bit;
};

/*  structure of LISIZE (2890_0208h)    */
union _IoJdslchRegLisize{
    kulong       word;
    struct {
        kulong   ihsize  :16;
        kulong   ivsize  :14;
        kulong           :2;
    }bit;
};

/*  structure of LYSA0-3  (2890_0210h)    */
union _IoJdslchRegLysa{
    kulong       word;
    struct {
        kulong   ysa    :32;
    }bit;
};

/*  structure of LCSA0-3  (2890_0220h)    */
union _IoJdslchRegLcsa{
    kulong       word;
    struct {
        kulong   csa     :32;
    }bit;
};

/*  structure of LYHGA  (2890_0240h)    */
union _IoJdslchRegLyhga{
    kulong       word;
    struct {
        kulong   yhga    :16;
        kulong           :16;
    }bit;
};

/*  structure of LCHGA  (2890_0250h)    */
union _IoJdslchRegLchga{
    kulong       word;
    struct {
        kulong   chga    :16;
        kulong           :16;
    }bit;
};

/*  structure of LIBCTL (2890_0260h)    */
union _IoJdslchRegLibctl{
    kulong       word;
    struct {
        kulong   iben    :1;
        kulong           :3;
        kulong           :4;
        kulong   ibset   :2;
        kulong           :2;
        kulong           :4;
        kulong   ibmnt   :2;
        kulong           :2;
        kulong           :4;
        kulong           :8;
    }bit;
};

/*  structure of LRSZ0  (2890_0400h)    */
union _IoJdslchRegLrsz0{
    kulong       word;
    struct {
        kulong   rszsl   :1;
        kulong           :31;
    }bit;
};

/*  structure of LRSZ1  (2890_0404h)    */
union _IoJdslchRegLrsz1{
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

/*  structure of LRSZ2  (2890_0408h)    */
union _IoJdslchRegLrsz2{
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

/*  structure of LRSZ3  (2890_040Ch)    */
union _IoJdslchRegLrsz3{
    kulong       word;
    struct {
        kulong   hcsta   :6;
        kulong           :2;
        kulong   vcsta   :6;
        kulong           :18;
    }bit;
};

/*  structure of LYHLPCTL   (2890_0410h)    */
union _IoJdslchRegLyhlpctl{
    kulong       word;
    struct {
        kulong   yhlpen  :1;
        kulong           :3;
        kulong           :4;
        kulong   yhlpmd  :2;
        kulong           :22;
    }bit;
};

/*  structure of LYHLPK0    (2890_0414h)    */
union _IoJdslchRegLyhlpk0{
    kulong       word;
    struct {
        kulong   yhlpk0  :9;
        kulong           :7;
        kulong   yhlpk1  :8;
        kulong           :8;
    }bit;
};

/*  structure of LYHLPK1    (2890_0418h)    */
union _IoJdslchRegLyhlpk1{
    kulong       word;
    struct {
        kulong   yhlpk2  :8;
        kulong           :8;
        kulong   yhlpk3  :8;
        kulong           :8;
    }bit;
};

/*  structure of LYHLPOL    (2890_041Ch)    */
union _IoJdslchRegLyhlpol{
    kulong       word;
    struct {
        kulong   yhlpcor :16;
        kulong   yhlpth  :16;
    }bit;
};

/*  structure of LYHLPCLR   (2890_0420h)    */
union _IoJdslchRegLyhlpclr{
    unsigned long long      dword;
    struct {
        unsigned long long  yhlpy   :16;
        unsigned long long  yhlpcb  :16;
        unsigned long long  yhlpcr  :16;
        unsigned long long          :16;
    }bit;
};

/*  structure of LYWCTL (2890_0430h)    */
union _IoJdslchRegLywctl{
    kulong       word;
    struct {
        kulong   ywen    :1;
        kulong           :3;
        kulong           :4;
        kulong   ywsl    :2;
        kulong           :22;
    }bit;
};

/*  structure of LYW0TH (2890_0434h)    */
union _IoJdslchRegLyw0th{
    kulong       word;
    struct {
        kulong   yw0thh  :16;
        kulong   yw0thl  :16;
    }bit;
};

/*  structure of LYW1TH (2890_0438h)    */
union _IoJdslchRegLyw1th{
    kulong       word;
    struct {
        kulong   yw1thh  :16;
        kulong   yw1thl  :16;
    }bit;
};

/*  structure of LYW0ST (2890_043Ch)    */
union _IoJdslchRegLyw0st{
    kulong       word;
    struct {
        kulong   yw0md   :2;
        kulong           :30;
    }bit;
};

/*  structure of LYW0CA (2890_0440h)    */
union _IoJdslchRegLyw0ca{
    unsigned long long      dword;
    struct {
        unsigned long long  yw0ay   :16;
        unsigned long long  yw0acb  :16;
        unsigned long long  yw0acr  :16;
        unsigned long long  yw0aa   :8;
        unsigned long long          :8;
    }bit;
};

/*  structure of LYW0CB (2890_0448h)    */
union _IoJdslchRegLyw0cb{
    unsigned long long      dword;
    struct {
        unsigned long long  yw0by   :16;
        unsigned long long  yw0bcb  :16;
        unsigned long long  yw0bcr  :16;
        unsigned long long  yw0ba   :8;
        unsigned long long          :8;
    }bit;
};

/*  structure of LYW1ST (2890_0450h)    */
union _IoJdslchRegLyw1st{
    kulong       word;
    struct {
        kulong   yw1md   :2;
        kulong           :30;
    }bit;
};

/*  structure of LYW1CA (2890_0458h)    */
union _IoJdslchRegLyw1ca{
    unsigned long long      dword;
    struct {
        unsigned long long  yw1ay   :16;
        unsigned long long  yw1acb  :16;
        unsigned long long  yw1acr  :16;
        unsigned long long  yw1aa   :8;
        unsigned long long          :8;
    }bit;
};

/*  structure of LYW1CB (2890_0460h)    */
union _IoJdslchRegLyw1cb{
    unsigned long long      dword;
    struct {
        unsigned long long  yw1by   :16;
        unsigned long long  yw1bcb  :16;
        unsigned long long  yw1bcr  :16;
        unsigned long long  yw1ba   :8;
        unsigned long long          :8;
    }bit;
};

/*  structure of LBLTMR (2890_0468h)    */
union _IoJdslchRegLbltmr{
    kulong       word;
    struct {
        kulong   btimh   :8;
        kulong   btiml   :8;
        kulong   btimd   :1;
        kulong           :15;
    }bit;
};

/*  structure of LBOST  (2890_046Ch)    */
union _IoJdslchRegLbost{
    kulong       word;
    struct {
        kulong   bomd    :1;
        kulong           :31;
    }bit;
};

/*  structure of LZBWID (2890_0470h)    */
union _IoJdslchRegLzbwid{
    kulong       word;
    struct {
        kulong   zbhh    :8;
        kulong   zbhl    :8;
        kulong           :16;
    }bit;
};

/*  structure of LZBV   (2890_0474h)    */
union _IoJdslchRegLzbv{
    kulong       word;
    struct {
        kulong   zbvsta  :1;
        kulong           :3;
        kulong           :4;
        kulong   zbvcyc  :1;
        kulong           :23;
    }bit;
};

/*  structure of LZBPT  (2890_0478h)    */
union _IoJdslchRegLzbpt{
    kulong       word;
    struct {
        kulong   zbdir   :1;
        kulong           :31;
    }bit;
};

/*  structure of LY2R0/1/2  (2890_04A0h)    */
union _IoJdslchRegLy2r{
    unsigned long long      dword;
    struct {
        unsigned long long  yr0     :16;
        unsigned long long  yr1     :16;
        unsigned long long  yr2     :16;
        unsigned long long          :16;
    }bit;
};

/*  structure of LTBLASET   (2890_04C0h)    */
union _IoJdslchRegLtblaset{
    kulong       word;
    struct {
        kulong   igtaen  :1;
        kulong   igen    :1;
        kulong   igtsl   :1;
        kulong           :1;
        kulong           :1;
        kulong           :1;
        kulong           :2;
        kulong   gtaen   :1;
        kulong   gmen    :1;
        kulong   gmtsl   :1;
        kulong           :1;
        kulong           :1;
        kulong           :3;
        kulong   igtmn   :1;
        kulong           :3;
        kulong           :1;
        kulong           :3;
        kulong   gmtmn   :1;
        kulong           :7;
    }bit;
};

/*  structure of LCC0-2   (2890_04D0h)    */
union _IoJdslchRegLcc{
    unsigned long long      dword;
    struct {
        unsigned long long  cc0     :12;
        unsigned long long          :4;
        unsigned long long  cc1     :12;
        unsigned long long          :4;
        unsigned long long  cc2     :12;
        unsigned long long          :20;
    }bit;
};

/*  structure of LGMMD  (2890_04F0h)    */
union _IoJdslchRegLgmmd{
    kulong       word;
    struct {
        kulong   gmmd    :1;
        kulong           :31;
    }bit;
};

/*  structure of LALP   (2890_0500h)    */
union _IoJdslchRegLalp{
    kulong       word;
    struct {
        kulong   alp :8;
        kulong       :24;
    }bit;
};

/*  structure of LDSTA  (2890_0600h)    */
union _IoJdslchRegLdsta{
    kulong       word;
    struct {
        kulong   dsh :16;
        kulong   dsv :14;
        kulong       :2;
    }bit;
};

/*  structure of LREVDISP   (2890_0604h)    */
union _IoJdslchRegLrevdisp{
    kulong       word;
    struct {
        kulong   hrev    :1;
        kulong           :3;
        kulong           :1;
        kulong           :3;
        kulong   vrev    :1;
        kulong           :23;
    }bit;
};

/* Define i/o mapping */
struct _IoJdslchReg{
    /* JDSIMG */
	/* 2890_(0000 - 0003h) */
	IoJdslchRegLrst       lrst;
	/* 2890_(0004 - 00FFh) */
    kuchar dmy000400ff[0x0100-0x0004];
    /* 2890_(0100 - 0103h) */
    IoJdslchRegLtrg       ltrg;
    /* 2890_(0104 - 010Fh) */
    kuchar dmy0104010f[0x0110-0x0104];
    /* 2890_(0110 - 0113h) */
    IoJdslchRegLrpgctl    lrpgctl;
    /* 2890_(0114 - 01FFh) */
    kuchar dmy011401ff[0x0200-0x0114];
    /* 2890_(0200 - 0203h) */
    IoJdslchRegLidt0      lidt0;
    /* 2890_(0204 - 0207h) */
    IoJdslchRegLidt1      lidt1;
    /* 2890_(0208 - 020Bh) */
    IoJdslchRegLisize     lisize;
    /* 2890_(020C - 020Fh) */
    kuchar dmy020c020f[0x0210-0x020C];
    /* 2890_(0210 - 021Fh) */
    IoJdslchRegLysa       lysa[4];
    /* 2890_(0220 - 022Fh) */
    IoJdslchRegLcsa       lcsa[4];
    /* 2890_(0230 - 023Fh) */
    kuchar dmy0230023f[0x0240-0x0230];
    /* 2890_(0240 - 0243h) */
    IoJdslchRegLyhga      lyhga;
    /* 2890_(0244 - 024Fh) */
    kuchar dmy0244024f[0x0250-0x0244];
    /* 2890_(0250 - 0253h) */
    IoJdslchRegLchga      lchga;
    /* 2890_(0254 - 025Fh) */
    kuchar dmy0254025f[0x0260-0x0254];
    /* 2890_(0260 - 0263h) */
    IoJdslchRegLibctl     libctl;
    /* 2890_(0264 - 03FFh) */
    kuchar dmy026403ff[0x0400-0x0264];
    /* 2890_(0400 - 0403h) */
    IoJdslchRegLrsz0      lrsz0;
    /* 2890_(0404 - 0407h) */
    IoJdslchRegLrsz1      lrsz1;
    /* 2890_(0408 - 040Bh) */
    IoJdslchRegLrsz2      lrsz2;
    /* 2890_(040C - 040Fh) */
    IoJdslchRegLrsz3      lrsz3;
    /* 2890_(0410 - 0413h) */
    IoJdslchRegLyhlpctl   lyhlpctl;
    /* 2890_(0414 - 0417h) */
    IoJdslchRegLyhlpk0    lyhlpk0;
    /* 2890_(0418 - 041Bh) */
    IoJdslchRegLyhlpk1    lyhlpk1;
    /* 2890_(041C - 041Fh) */
    IoJdslchRegLyhlpol    lyhlpol;
    /* 2890_(0420 - 0427h) */
    IoJdslchRegLyhlpclr   lyhlpclr;
    /* 2890_(0428 - 042Fh) */
    kuchar dmy0428042f[0x0430-0x0428];
    /* 2890_(0430 - 0433h) */
    IoJdslchRegLywctl     lywctl;
    /* 2890_(0434 - 0437h) */
    IoJdslchRegLyw0th     lyw0th;
    /* 2890_(0438 - 043Bh) */
    IoJdslchRegLyw1th     lyw1th;
    /* 2890_(043C - 043Fh) */
    IoJdslchRegLyw0st     lyw0st;
    /* 2890_(0440 - 0447h) */
    IoJdslchRegLyw0ca     lyw0ca;
    /* 2890_(0448 - 044Fh) */
    IoJdslchRegLyw0cb     lyw0cb;
    /* 2890_(0450 - 0453h) */
    IoJdslchRegLyw1st     lyw1st;
    /* 2890_(0454 - 0457h) */
    kuchar dmy04540457[0x0458-0x0454];
    /* 2890_(0458 - 045Fh) */
    IoJdslchRegLyw1ca     lyw1ca;
    /* 2890_(0460 - 0467h) */
    IoJdslchRegLyw1cb     lyw1cb;
    /* 2890_(0468 - 046Bh) */
    IoJdslchRegLbltmr     lbltmr;
    /* 2890_(046C - 046Fh) */
    IoJdslchRegLbost      lbost;
    /* 2890_(0470 - 0473h) */
    IoJdslchRegLzbwid     lzbwid;
    /* 2890_(0474 - 0477h) */
    IoJdslchRegLzbv       lzbv;
    /* 2890_(0478 - 047Bh) */
    IoJdslchRegLzbpt      lzbpt;
    /* 2890_(047C - 049Fh) */
    kuchar dmy047c049f[0x04A0-0x047C];
    /* 2890_(04A0 - 04B7h) */
    IoJdslchRegLy2r       ly2r[3];
    /* 2890_(04B8 - 04BFh) */
    kuchar dmy04b804bf[0x04C0-0x04B8];
    /* 2890_(04C0 - 04C3h) */
    IoJdslchRegLtblaset   ltblaset;
    /* 2890_(04C4 - 04CFh) */
    kuchar dmy04c404cf[0x04D0-0x04C4];
    /* 2890_(04D0 - 04E7h) */
    IoJdslchRegLcc        lcc[3];
    /* 2890_(04E8 - 04EFh) */
    kuchar dmy04e804ef[0x04F0-0x04E8];
    /* 2890_(04F0 - 04F3h) */
    IoJdslchRegLgmmd      lgmmd;
    /* 2890_(04F4 - 04FFh) */
    kuchar dmy04f404ff[0x0500-0x04F4];
    /* 2890_(0500 - 0503h) */
    IoJdslchRegLalp       lalp;
    /* 2890_(0504 - 05FFh) */
    kuchar dmy050405ff[0x0600-0x0504];
    /* 2890_(0600 - 0603h) */
    IoJdslchRegLdsta      ldsta;
    /* 2890_(0604 - 0607h) */
    IoJdslchRegLrevdisp   lrevdisp;
    /* 2890_(0608 - 0FFFh) */
    kuchar dmy06080fff[0x1000-0x0608];
};

struct  _JdsdispLch
{
	KObject parent;
};


KConstType			jdsdisp_lch_get_type(void);
JdsdispLch*			jdsdisp_lch_new(void);


#endif/*__JDSDISP_LCH_H__*/
