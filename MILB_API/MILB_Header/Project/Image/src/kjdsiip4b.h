/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :陈倩
 *@brief             :kjdsiip4b
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


#ifndef __K_JDSIIP4B_H__
#define __K_JDSIIP4B_H__


#include <klib.h>
//#include "__jdsiip4b_pixfmttbl.h"
//#include "__jdsiip4b_uinftbl.h"
//#include "__jdsiip4b_ram.h"
//#include "__jdsiip4b_ram_lut.h"
//#include "__jdsiip4b_ram_histgram.h"
#include "kjdsiip4b1.h"


#define K_TYPE_JDSIIP4B				(k_jdsiip4b_get_type())
#define K_JDSIIP4B(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsiip4b))
#define K_IS_JDSIIP4B(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSIIP4B))


typedef struct _KJdsiip4b 			KJdsiip4b;
typedef struct _KJdsiip4bPrivate KJdsiip4bPrivate;


struct _KJdsiip4b
{
	KObject parent;
};


/* Define i/o mapping */
typedef struct _IoIipRamLut
{
	/* JDSIMG */
	IoIipLutram lutram; /* 2982_(0000 - 5FFFh) */

	unsigned char dmy298260002982ffff[0x29830000 - 0x29826000]; /* 2982_6000 - 2982_FFFFh */

} IoIipRamLut;

/*  structure of histgram   (2983_0000h)    */
typedef union _IoIipHistgram
{
	unsigned long word[4][256];
	struct
	{
		unsigned long hist :24;
		unsigned long :8;
	} bit[4][256];
} IoIipHistgram;

/* Define i/o mapping */
typedef struct _IoIipRamHistgram
{
	/* JDSIMG */
	IoIipHistgram histgram; /* 2983_(0000 - 0FFFh) */

	unsigned char dmy298310002983ffff[0x29840000 - 0x29831000]; /* 2983_1000 - 2983_FFFFh */

} IoIipRamHistgram;

/* Define i/o mapping */
typedef struct _IoIipRam
{
	/* JDSIMG */
	IoIipRamLut lutram; /* 2982_(0000 - FFFFh) */
	IoIipRamHistgram histgram; /* 2983_(0000 - FFFFh) */
} IoIipRam;

/*  structure of izactl0    (2888_0000h)    */
typedef union _IoIipIzactl0
{
	unsigned long word;
	struct
	{
		unsigned long sr :1;
		unsigned long :31;
	} bit;
} IoIipIzactl0;

/*  structure of izactl1    (2888_0004h)    */
typedef union _IoIipIzactl1
{
	unsigned long word;
	struct
	{
		unsigned long trg :2;
		unsigned long slale :1;
		unsigned long :1;
		unsigned long frm :1;
		unsigned long :3;
		unsigned long usebank :2;
		unsigned long exebkno :2;
		unsigned long startbk :3;
		unsigned long lken :1;
		unsigned long lksl :4;
		unsigned long ovr128 :1;
		unsigned long dsini :1;
		unsigned long dben :1;
		unsigned long :1;
		unsigned long selrdregUnit :6;
		unsigned long :2;
	} bit;
} IoIipIzactl1;

/*  structure of izactl2    (2888_0008h)    */
typedef union _IoIipIzactl2
{
	unsigned long word;
	struct
	{
		unsigned long abort :2;
		unsigned long :30;
	} bit;
} IoIipIzactl2;

/*  structure of inten0 (2888_000Ch)    */
typedef union _IoIipInten0
{
	unsigned long word;
	struct
	{
		unsigned long izaen :1;
		unsigned long :1;
		unsigned long axeen :1;
		unsigned long :29;
	} bit;
} IoIipInten0;

/*  structure of inten1 (2888_0010h)    */
typedef union _IoIipInten1
{
	unsigned long word;
	struct
	{
		unsigned long sl0fen :1;
		unsigned long sl1fen :1;
		unsigned long sl2fen :1;
		unsigned long sl3fen :1;
		unsigned long sl4fen :1;
		unsigned long sl5fen :1;
		unsigned long sl6fen :1;
		unsigned long sl7fen :1;
		unsigned long sl8fen :1;
		unsigned long :3;
		unsigned long :4;
		unsigned long sl0men :1;
		unsigned long sl1men :1;
		unsigned long sl2men :1;
		unsigned long sl3men :1;
		unsigned long sl4men :1;
		unsigned long sl5men :1;
		unsigned long sl6men :1;
		unsigned long sl7men :1;
		unsigned long sl8men :1;
		unsigned long :7;
	} bit;
} IoIipInten1;

/*  structure of inten2 (2888_0014h)    */
typedef union _IoIipInten2
{
	unsigned long word;
	struct
	{
		unsigned long reaf0e :1;
		unsigned long reaf1e :1;
		unsigned long reaf2e :1;
		unsigned long reaf3e :1;
		unsigned long refr0e :1;
		unsigned long refr1e :1;
		unsigned long reflte :1;
		unsigned long :25;
	} bit;
} IoIipInten2;

/*  structure of intiz0 (2888_0018h)    */
typedef union _IoIipIntiz0
{
	unsigned long word;
	struct
	{
		unsigned long __izaflg :1;
		unsigned long :1;
		unsigned long __axeflg :1;
		unsigned long :29;
	} bit;
} IoIipIntiz0;

/*  structure of intiz1 (2888_001Ch)    */
typedef union _IoIipIntiz1
{
	unsigned long word;
	struct
	{
		unsigned long __sl0ff :1;
		unsigned long __sl1ff :1;
		unsigned long __sl2ff :1;
		unsigned long __sl3ff :1;
		unsigned long __sl4ff :1;
		unsigned long __sl5ff :1;
		unsigned long __sl6ff :1;
		unsigned long __sl7ff :1;
		unsigned long __sl8ff :1;
		unsigned long :3;
		unsigned long :1;
		unsigned long :3;
		unsigned long __sl0mf :1;
		unsigned long __sl1mf :1;
		unsigned long __sl2mf :1;
		unsigned long __sl3mf :1;
		unsigned long __sl4mf :1;
		unsigned long __sl5mf :1;
		unsigned long __sl6mf :1;
		unsigned long __sl7mf :1;
		unsigned long __sl8mf :1;
		unsigned long :7;
	} bit;
} IoIipIntiz1;

/*  structure of intiz2 (2888_0020h)    */
typedef union _IoIipIntiz2
{
	unsigned long word;
	struct
	{
		unsigned long __reaf0f :1;
		unsigned long __reaf1f :1;
		unsigned long __reaf2f :1;
		unsigned long __reaf3f :1;
		unsigned long __refr0f :1;
		unsigned long __refr1f :1;
		unsigned long __refltf :1;
		unsigned long :25;
	} bit;
} IoIipIntiz2;

/*  structure of pftrewtflg (2888_0028h)    */
typedef union _IoIipPftrewtflg
{
	unsigned long word;
	struct
	{
		unsigned long pftflg :1;
		unsigned long :31;
	} bit;
} IoIipPftrewtflg;

/*  structure of pftrewt    (2888_002Ch)    */
typedef union _IoIipPftrewt
{
	unsigned long word;
	struct
	{
		unsigned long pftrewt :4;
		unsigned long :28;
	} bit;
} IoIipPftrewt;

/*  structure of pdcctl (2888_0030h)    */
typedef union _IoIipPdcctl
{
	unsigned long word;
	struct
	{
		unsigned long flhall :1;
		unsigned long :3;
		unsigned long extbit :1;
		unsigned long :3;
		unsigned long pdcpkg :1;
		unsigned long :3;
		unsigned long pdcarcache :4;
		unsigned long pdcarprot :3;
		unsigned long :13;
	} bit;
} IoIipPdcctl;

/*  structure of pdcrac (2888_0040h)    */
typedef union _IoIipPdcrac
{
	unsigned long word;
	struct
	{
		unsigned long pdcrac :32;
	} bit;
} IoIipPdcrac;

/*  structure of pdcrmc (2888_0050h)    */
typedef union _IoIipPdcrmc
{
	unsigned long word;
	struct
	{
		unsigned long pdcrmc :32;
	} bit;
} IoIipPdcrmc;

/*  structure of genline    (2888_00C0h)    */
typedef union _IoIipGenline1
{
	unsigned long word[2];
	struct
	{
		unsigned long b2yOutlineno :14;
		unsigned long :2;
		unsigned long afn0Outlineno :14;
		unsigned long :2;
		unsigned long afn1Outlineno :14;
		unsigned long :2;
		unsigned long afn2Outlineno :14;
		unsigned long :2;
	} bit;
} IoIipGenline1;

typedef union _IoIipGenline2
{
	unsigned long word[2];
	struct
	{
		unsigned long afn3Outlineno :14;
		unsigned long :2;
		unsigned long fr0Outlineno :14;
		unsigned long :2;
		unsigned long fr1Outlineno :14;
		unsigned long :2;
		unsigned long ld0Outlineno :14;
		unsigned long :2;
	} bit;
} IoIipGenline2;

typedef union _IoIipGenline3
{
	unsigned long word[2];
	struct
	{
		unsigned long ld1Outlineno :14;
		unsigned long :2;
		unsigned long ld2Outlineno :14;
		unsigned long :2;
		unsigned long ld3Outlineno :14;
		unsigned long :2;
		unsigned long ld4Outlineno :14;
		unsigned long :2;
	} bit;
} IoIipGenline3;

typedef union _IoIipGenline4
{
	unsigned long word[2];
	struct
	{
		unsigned long ld5Outlineno :14;
		unsigned long :2;
		unsigned long ld6Outlineno :14;
		unsigned long :2;
		unsigned long fltOutlineno :14;
		unsigned long :18;
	} bit;
} IoIipGenline4;

typedef struct _IoIipGenline
{
	IoIipGenline1 genline1;
	IoIipGenline2 genline2;
	IoIipGenline3 genline3;
	IoIipGenline4 genline4;
} IoIipGenline;

/*  structure of lkslCtl   (2888_00E0h)    */
typedef union _IoIipLkslCtl
{
	unsigned long word;
	struct
	{
		unsigned long vsizeCop :14;
		unsigned long :2;
		unsigned long lineValCop :8;
		unsigned long :8;
	} bit;
} IoIipLkslCtl;

/*  structure of lineValIntSl0   (2888_00E4h)    */
/*  structure of lineValIntSl1   (2888_00E8h)    */
/*  structure of lineValIntSl2   (2888_00ECh)    */
/*  structure of lineValIntSl3   (2888_00F0h)    */
/*  structure of lineValIntSl4   (2888_00F4h)    */
/*  structure of lineValIntSl5   (2888_00F8h)    */
/*  structure of lineValIntSl6   (2888_00FCh)    */
/*  structure of lineValIntSl7   (2888_0100h)    */
/*  structure of lineValIntSl8   (2888_0104h)    */
typedef union _IoIipLineValIntSl
{
	unsigned long word;
	struct
	{
		unsigned long lineValIntSl :14;
		unsigned long :18;
	} bit;
} IoIipLineValIntSl;

/*  structure of dpaxictl   (2888_010Ch)    */
typedef union _IoIipDpaxictl
{
	unsigned long word;
	struct
	{
		unsigned long dprs :1;
		unsigned long :3;
		unsigned long :1;
		unsigned long :3;
		unsigned long dparcache :4;
		unsigned long dparprot :3;
		unsigned long :17;
	} bit;
} IoIipDpaxictl;

/*  structure of afnaxictl  (2888_0110h)    */
typedef union _IoIipAfnaxictl
{
	unsigned long word[2];
	struct
	{
		unsigned long afn0rs :1;
		unsigned long :3;
		unsigned long afn0pk :1;
		unsigned long :3;
		unsigned long afn0arcache :4;
		unsigned long afn0arprot :3;
		unsigned long :1;
		unsigned long afn1rs :1;
		unsigned long :3;
		unsigned long afn1pk :1;
		unsigned long :3;
		unsigned long afn1arcache :4;
		unsigned long afn1arprot :3;
		unsigned long :1;
		unsigned long afn2rs :1;
		unsigned long :3;
		unsigned long afn2pk :1;
		unsigned long :3;
		unsigned long afn2arcache :4;
		unsigned long afn2arprot :3;
		unsigned long :1;
		unsigned long afn3rs :1;
		unsigned long :3;
		unsigned long afn3pk :1;
		unsigned long :3;
		unsigned long afn3arcache :4;
		unsigned long afn3arprot :3;
		unsigned long :1;
	} bit;
} IoIipAfnaxictl;

/*  structure of fraxictl   (2888_0118h)    */
typedef union _IoIipFraxictl
{
	unsigned long word;
	struct
	{
		unsigned long fr0rs :1;
		unsigned long :3;
		unsigned long fr0pkg :1;
		unsigned long :3;
		unsigned long fr0arcache :4;
		unsigned long fr0arprot :3;
		unsigned long :1;
		unsigned long fr1rs :1;
		unsigned long :3;
		unsigned long fr1pkg :1;
		unsigned long :3;
		unsigned long fr1arcache :4;
		unsigned long fr1arprot :3;
		unsigned long :1;
	} bit;
} IoIipFraxictl;

/*  structure of gpcaxictl  (2888_011Ch)    */
typedef union _IoIipGpcaxictl
{
	unsigned long word;
	struct
	{
		unsigned long gpcrs :1;
		unsigned long :3;
		unsigned long :1;
		unsigned long :3;
		unsigned long gpcarcache :4;
		unsigned long gpcarprot :3;
		unsigned long :17;
	} bit;
} IoIipGpcaxictl;

/*  structure of slaxictl   (2888_0120h)    */
typedef union _IoIipSlaxictl1
{
	unsigned long word;
	struct
	{
		unsigned long :4;
		unsigned long sl0pkg :2;
		unsigned long :2;
		unsigned long sl0awcache :4;
		unsigned long sl0awprot :3;
		unsigned long :1;
		unsigned long :4;
		unsigned long sl1pkg :2;
		unsigned long :2;
		unsigned long sl1awcache :4;
		unsigned long sl1awprot :3;
		unsigned long :1;
	} bit;
} IoIipSlaxictl1;

typedef union _IoIipSlaxictl2
{
	unsigned long word;
	struct
	{
		unsigned long :4;
		unsigned long sl2pkg :2;
		unsigned long :2;
		unsigned long sl2awcache :4;
		unsigned long sl2awprot :3;
		unsigned long :1;
		unsigned long :4;
		unsigned long sl3pkg :2;
		unsigned long :2;
		unsigned long sl3awcache :4;
		unsigned long sl3awprot :3;
		unsigned long :1;
	} bit;
} IoIipSlaxictl2;

typedef union _IoIipSlaxictl3
{
	unsigned long word;
	struct
	{
		unsigned long :4;
		unsigned long sl4pkg :2;
		unsigned long :2;
		unsigned long sl4awcache :4;
		unsigned long sl4awprot :3;
		unsigned long :1;
		unsigned long :4;
		unsigned long sl5pkg :2;
		unsigned long :2;
		unsigned long sl5awcache :4;
		unsigned long sl5awprot :3;
		unsigned long :1;
	} bit;
} IoIipSlaxictl3;

typedef union _IoIipSlaxictl4
{
	unsigned long word;
	struct
	{
		unsigned long :4;
		unsigned long sl6pkg :2;
		unsigned long :2;
		unsigned long sl6awcache :4;
		unsigned long sl6awprot :3;
		unsigned long :1;
		unsigned long :4;
		unsigned long sl7pkg :2;
		unsigned long :2;
		unsigned long sl7awcache :4;
		unsigned long sl7awprot :3;
		unsigned long :1;
	} bit;
} IoIipSlaxictl4;

typedef union _IoIipSlaxictl5
{
	unsigned long word;
	struct
	{
		unsigned long :4;
		unsigned long sl8pkg :2;
		unsigned long :2;
		unsigned long sl8awcache :4;
		unsigned long sl8awprot :3;
		unsigned long :17;
	} bit;
} IoIipSlaxictl5;

typedef struct _IoIipSlaxictl
{
	IoIipSlaxictl1 slaxictl1;
	IoIipSlaxictl2 slaxictl2;
	IoIipSlaxictl3 slaxictl3;
	IoIipSlaxictl4 slaxictl4;
	IoIipSlaxictl5 slaxictl5;
} IoIipSlaxictl;

/*  structure of axrsts (2888_0140h)    */
typedef union _IoIipAxrsts
{
	unsigned long word;
	struct
	{
		unsigned long dprresp :2;
		unsigned long :2;
		unsigned long pdc0rresp :2;
		unsigned long pdc1rresp :2;
		unsigned long pdc2rresp :2;
		unsigned long afn0rresp :2;
		unsigned long afn1rresp :2;
		unsigned long afn2rresp :2;
		unsigned long afn3rresp :2;
		unsigned long fr0rresp :2;
		unsigned long fr1rresp :2;
		unsigned long gpcrresp :2;
		unsigned long :8;
	} bit;
} IoIipAxrsts;

/*  structure of axwsts (2888_0144h)    */
typedef union _IoIipAxwsts
{
	unsigned long word;
	struct
	{
		unsigned long sl0wresp :2;
		unsigned long sl1wresp :2;
		unsigned long sl2wresp :2;
		unsigned long sl3wresp :2;
		unsigned long sl4wresp :2;
		unsigned long sl5wresp :2;
		unsigned long sl6wresp :2;
		unsigned long sl7wresp :2;
		unsigned long sl8wresp :2;
		unsigned long :14;
	} bit;
} IoIipAxwsts;

/*  structure of ahbsts (2888_0148h)    */
typedef union _IoIipAhbsts
{
	unsigned long word;
	struct
	{
		unsigned long lutast :1;
		unsigned long lutbst :1;
		unsigned long lutcst :1;
		unsigned long lutdst :1;
		unsigned long lutest :1;
		unsigned long lutfst :1;
		unsigned long :2;
		unsigned long hissts :1;
		unsigned long :23;
	} bit;
} IoIipAhbsts;

/*  structure of acesen0    (2888_014Ch)    */
typedef union _IoIipAcesen0
{
	unsigned long word;
	struct
	{
		unsigned long izarac :1;
		unsigned long :3;
		unsigned long ca1rac :1;
		unsigned long ca2rac :1;
		unsigned long :2;
		unsigned long luarac :1;
		unsigned long lubrac :1;
		unsigned long lucrac :1;
		unsigned long ludrac :1;
		unsigned long luerac :1;
		unsigned long lufrac :1;
		unsigned long :2;
		unsigned long mo0rac :1;
		unsigned long mo1rac :1;
		unsigned long mo2rac :1;
		unsigned long mo3rac :1;
		unsigned long sl0rac :1;
		unsigned long sl1rac :1;
		unsigned long sl2rac :1;
		unsigned long sl3rac :1;
		unsigned long sl4rac :1;
		unsigned long sl5rac :1;
		unsigned long sl6rac :1;
		unsigned long sl7rac :1;
		unsigned long sl8rac :1;
		unsigned long :3;
	} bit;
} IoIipAcesen0;

/*  structure of dtoutMon  (2888_0178h)    */
typedef union _IoIipDtoutMon
{
	unsigned long word[2];
	struct
	{
		unsigned long dtoutMonLo :32;
		unsigned long dtoutMonHi :32;
	} bit;
} IoIipDtoutMon;

/*  structure of waitMon   (2888_0180h)    */
typedef union _IoIipWaitMon
{
	unsigned long word[2];
	struct
	{
		unsigned long waitMonLo :32;
		unsigned long waitMonHi :32;
	} bit;
} IoIipWaitMon;

/*  structure of pdcDtoutMon  (2888_0188h)    */
typedef union _IoIipPdcDtoutMon1
{
	unsigned long word;
	struct
	{
		unsigned long pdcDtoutMon0 :15;
		unsigned long :1;
		unsigned long pdcDtoutMon11 :15;
		unsigned long :1;
	} bit;
} IoIipPdcDtoutMon1;

typedef union _IoIipPdcDtoutMon2
{
	unsigned long word;
	struct
	{
		unsigned long pdcDtoutMon22 :15;
		unsigned long :1;
		unsigned long :16;
	} bit;
} IoIipPdcDtoutMon2;

typedef struct _IoIipPdcDtoutMon
{
	IoIipPdcDtoutMon1 pdcDtoutMon1;
	IoIipPdcDtoutMon2 pdcDtoutMon2;
} IoIipPdcDtoutMon;

/*  structure of pdcRdyMon    (2888_0190h)    */
typedef union _IoIipPdcRdyMon1
{
	unsigned long word;
	struct
	{
		unsigned long pdcRdyMon0 :15;
		unsigned long :1;
		unsigned long pdcRdyMon11 :15;
		unsigned long :1;
	} bit;
} IoIipPdcRdyMon1;

typedef union _IoIipPdcRdyMon2
{
	unsigned long word;
	struct
	{
		unsigned long pdcRdyMon22 :15;
		unsigned long :1;
		unsigned long :16;
	} bit;
} IoIipPdcRdyMon2;

typedef struct _IoIipPdcRdyMon
{
	IoIipPdcRdyMon1 pdcRdyMon1;
	IoIipPdcRdyMon2 pdcRdyMon2;
} IoIipPdcRdyMon;

/*  structure of histmax    (2888_0200h)    */
typedef union _IoIipHistmax1
{
	unsigned long word;
	struct
	{
		unsigned long histmax0 :8;
		unsigned long histmax11 :8;
		unsigned long histmax2 :8;
		unsigned long histmax3 :8;
	} bit;
} IoIipHistmax1;

typedef struct _IoIipHistmax
{
	IoIipHistmax1 histmax1;
} IoIipHistmax;

/*  structure of maxmon (2888_0220h)    */
typedef union _IoIipMaxmon
{
	unsigned long word[2];
	struct
	{
		unsigned long hpointmax :14;
		unsigned long :2;
		unsigned long vpointmax :14;
		unsigned long :2;
		long maxval :15;
		unsigned long :17;
	} bit;
} IoIipMaxmon;

/*  structure of minmon (2888_0240h)    */
typedef union _IoIipMinmon
{
	unsigned long word[2];
	struct
	{
		unsigned long hpointmin :14;
		unsigned long :2;
		unsigned long vpointmin :14;
		unsigned long :2;
		long minval :15;
		unsigned long :17;
	} bit;
} IoIipMinmon;

/*  structure of addmon (2888_0260h)    */
typedef union _IoIipAddmon
{
	unsigned long word[2];
	struct
	{
		unsigned long hpointadd :14;
		unsigned long :2;
		unsigned long vpointadd :14;
		unsigned long :2;
		long addval :32;
	} bit;
} IoIipAddmon;

/*  structure of moninit    (2888_0280h)    */
typedef union _IoIipMoninit
{
	unsigned long word;
	struct
	{
		unsigned long init :1;
		unsigned long :31;
	} bit;
} IoIipMoninit;

/* Define i/o mapping */
typedef struct _IoIip
{
	/* JDSIMG */
	/* 2888_(0000 - 0003h) */
	IoIipIzactl0 izactl0;
	/* 2888_(0004 - 0007h) */
	IoIipIzactl1 izactl1;
	/* 2888_(0008 - 000Bh) */
	IoIipIzactl2 izactl2;
	/* 2888_(000C - 000Fh) */
	IoIipInten0 inten0;
	/* 2888_(0010 - 0013h) */
	IoIipInten1 inten1;
	/* 2888_(0014 - 0017h) */
	IoIipInten2 inten2;
	/* 2888_(0018 - 001Bh) */
	IoIipIntiz0 intiz0;
	/* 2888_(001C - 001Fh) */
	IoIipIntiz1 intiz1;
	/* 2888_(0020 - 0023h) */
	IoIipIntiz2 intiz2;
	/* 2888_(0024 - 0027h) */
	unsigned char dmy00240027[0x0028 - 0x0024];
	/* 2888_(0028 - 002Bh) */
	IoIipPftrewtflg pftrewtflg;
	/* 2888_(002C - 002Fh) */
	IoIipPftrewt pftrewt;
	/* 2888_(0030 - 003Bh) */
	IoIipPdcctl pdcctl[3];
	/* 2888_(003C - 003Fh) */
	unsigned char dmy003c003f[0x0040 - 0x003C];
	/* 2888_(0040 - 004Bh) */
	IoIipPdcrac pdcrac[3];
	/* 2888_(004C - 004Fh) */
	unsigned char dmy004c004f[0x0050 - 0x004C];
	/* 2888_(0050 - 005Bh) */
	IoIipPdcrmc pdcrmc[3];
	/* 2888_(005C - 00BFh) */
	unsigned char dmy005c00bf[0x00C0 - 0x005C];
	/* 2888_(00C0 - 00DFh) */
	IoIipGenline genline;
	/* 2888_(00E0 - 00E3h) */
	IoIipLkslCtl lkslCtl;
	/* 2888_(00E4 - 00E7h) */
	IoIipLineValIntSl lineValIntSl0;
	/* 2888_(00E8 - 00EBh) */
	IoIipLineValIntSl lineValIntSl1;
	/* 2888_(00EC - 00EFh) */
	IoIipLineValIntSl lineValIntSl2;
	/* 2888_(00F0 - 00F3h) */
	IoIipLineValIntSl lineValIntSl3;
	/* 2888_(00F4 - 00F7h) */
	IoIipLineValIntSl lineValIntSl4;
	/* 2888_(00F8 - 00FBh) */
	IoIipLineValIntSl lineValIntSl5
	/* 2888_(00FC - 00FFh) */;
	IoIipLineValIntSl lineValIntSl6;
	/* 2888_(0100 - 0103h) */
	IoIipLineValIntSl lineValIntSl7;
	/* 2888_(0104 - 0107h) */
	IoIipLineValIntSl lineValIntSl8;
	/* 2888_(0108 - 010Bh) */
	unsigned char dmy0108010b[0x010C - 0x0108];
	/* 2888_(010C - 010Fh) */
	IoIipDpaxictl dpaxictl;
	/* 2888_(0110 - 0117h) */
	IoIipAfnaxictl afnaxictl;
	/* 2888_(0118 - 011Bh) */
	IoIipFraxictl fraxictl;
	/* 2888_(011C - 011Fh) */
	IoIipGpcaxictl gpcaxictl;
	/* 2888_(0120 - 0133h) */
	IoIipSlaxictl slaxictl;
	/* 2888_(0134 - 013Fh) */
	unsigned char dmy0134013f[0x0140 - 0x0134];
	/* 2888_(0140 - 0143h) */
	IoIipAxrsts axrsts;
	/* 2888_(0144 - 0147h) */
	IoIipAxwsts axwsts;
	/* 2888_(0148 - 014Bh) */
	IoIipAhbsts ahbsts;
	/* 2888_(014C - 014Fh) */
	IoIipAcesen0 acesen0;
	/* 2888_(0150 - 0177h) */
	unsigned char dmy01500177[0x0178 - 0x0150];
	/* 2888_(0178 - 017Fh) */
	IoIipDtoutMon dtoutMon;
	/* 2888_(0180 - 0187h) */
	IoIipWaitMon waitMon;
	/* 2888_(0188 - 018Fh) */
	IoIipPdcDtoutMon pdcDtoutMon;
	/* 2888_(0190 - 0197h) */
	IoIipPdcRdyMon pdcRdyMon;
	/* 2888_(0198 - 01FFh) */
	unsigned char dmy019801ff[0x0200 - 0x0198];
	/* 2888_(0200 - 0203h) */
	IoIipHistmax histmax;
	/* 2888_(0204 - 021Fh) */
	unsigned char dmy0204021f[0x0220 - 0x0204];
	/* 2888_(0220 - 023Fh) */
	IoIipMaxmon maxmon[4];
	/* 2888_(0240 - 025Fh) */
	IoIipMinmon minmon[4];
	/* 2888_(0260 - 027Fh) */
	IoIipAddmon addmon[4];
	/* 2888_(0280 - 0283h) */
	IoIipMoninit moninit;
	/* 2888_(0284 - 02FFh) */
	unsigned char dmy028402ff[0x0300 - 0x0284];
	/* 2888_(0300 - 05FFh) */
	IoIipPixfmttbl pixfmttbl[12];
	/* 2888_(0600 - 07FFh) */
	unsigned char dmy060007ff[0x0800 - 0x0600];
	/* 2888_(0800 - 081Fh) */
	IoIipUinftbl unitinftblLd0;
	/* 2888_(0820 - 083Fh) */
	IoIipUinftbl unitinftblLd1;
	/* 2888_(0840 - 085Fh) */
	IoIipUinftbl unitinftblLd2;
	/* 2888_(0860 - 087Fh) */
	IoIipUinftbl unitinftblLd3;
	/* 2888_(0880 - 089Fh) */
	IoIipUinftbl unitinftblFlt;
	/* 2888_(08A0 - 08BFh) */
	IoIipUinftbl unitinftblAfn0;
	/* 2888_(08C0 - 08DFh) */
	IoIipUinftbl unitinftblAfn1;
	/* 2888_(08E0 - 08FFh) */
	IoIipUinftbl unitinftblAfn2;
	/* 2888_(0900 - 091Fh) */
	IoIipUinftbl unitinftblFrc0;
	/* 2888_(0920 - 093Fh) */
	IoIipUinftbl unitinftblMon;
	/* 2888_(0940 - 095Fh) */
	IoIipUinftbl unitinftblSl0;
	/* 2888_(0960 - 097Fh) */
	IoIipUinftbl unitinftblSl1;
	/* 2888_(0980 - 099Fh) */
	IoIipUinftbl unitinftblSl2;
	/* 2888_(09A0 - 09BFh) */
	IoIipUinftbl unitinftblSl3;
	/* 2888_(09C0 - 09DFh) */
	IoIipUinftbl unitinftblSl4;
	/* 2888_(09E0 - 09FFh) */
	IoIipUinftbl unitinftblSl5;
	/* 2888_(0A00 - 0A1Fh) */
	IoIipUinftbl unitinftblCsc0;
	/* 2888_(0A20 - 0A3Fh) */
	IoIipUinftbl unitinftblCsc1;
	/* 2888_(0A40 - 0A5Fh) */
	IoIipUinftbl unitinftblLut;
	/* 2888_(0A60 - 0A7Fh) */
	IoIipUinftbl unitinftblGpc;
	/* 2888_(0A80 - 0A9Fh) */
	IoIipUinftbl unitinftblBld0;
	/* 2888_(0AA0 - 0ABFh) */
	IoIipUinftbl unitinftblBld1;
	/* 2888_(0AC0 - 0ADFh) */
	IoIipUinftbl unitinftblFrc1;
	/* 2888_(0AE0 - 0AFFh) */
	IoIipUinftbl unitinftblCfl0;
	/* 2888_(0B00 - 0B5Fh) */
	unsigned char dmy0b000b5f[0x0B60 - 0x0B00];
	/* 2888_(0B60 - 0B7Fh) */
	IoIipUinftbl unitinftblCsc2;
	/* 2888_(0B80 - 0B9Fh) */
	IoIipUinftbl unitinftblCsc3;
	/* 2888_(0BA0 - 0BBFh) */
	IoIipUinftbl unitinftblSl6;
	/* 2888_(0BC0 - 0BDFh) */
	IoIipUinftbl unitinftblSl7;
	/* 2888_(0BE0 - 0BFFh) */
	IoIipUinftbl unitinftblSl8;
	/* 2888_(0C00 - 0C1Fh) */
	IoIipUinftbl unitinftblLd4;
	/* 2888_(0C20 - 0C3Fh) */
	IoIipUinftbl unitinftblLd5;
	/* 2888_(0C40 - 0C5Fh) */
	IoIipUinftbl unitinftblLd6;
	/* 2888_(0C60 - 0C7Fh) */
	IoIipUinftbl unitinftblLd7;
	/* 2888_(0C80 - 0C9Fh) */
	IoIipUinftbl unitinftblAfn3;
	/* 2888_(0CA0 - 0CBFh) */
	IoIipUinftbl unitinftblMft;
	/* 2888_0CC0 - 2888_FFFFh */
	unsigned char dmy28880cc02888ffff[0x28890000 - 0x28880CC0];
	/* 2889_(0000 - FFFFh) */
	unsigned long unitdebug[0x10000 / 4];

} IoIip;


extern volatile IoIipRam ioIipTbl;
extern volatile IoIip ioIip;


KConstType 	k_jdsiip4b_get_type(void);
KJdsiip4b* 		k_jdsiip4b_new(void);


#endif/*__K_JDSIIP4B_H__*/

