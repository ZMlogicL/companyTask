/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsjp7
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


#ifndef __K_JDSJP7_H__
#define __K_JDSJP7_H__


#include <klib.h>


#define K_TYPE_JDSJP7					(k_jdsjp7_get_type())
#define K_JDSJP7(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsjp7))
#define K_IS_JDSJP7(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSJP7))


typedef struct _KJdsjp7				KJdsjp7;
typedef struct _KJdsjp7Private	KJdsjp7Private;

struct  _KJdsjp7
{
	KObject parent;
};


/*	structure of jpmode				(298C_0000h)	*/
typedef union _IoJpeg7cJpmode
{
	kulong word;
	struct {
		kulong mmode :3;
		kulong disposal :1;
		kulong pEndian :1;
		kulong sEndian :1;
		kulong :26;
	} bit;
} IoJpeg7cJpmode;

/*	structure of jpcmd				(298C_0004h)	*/
typedef union _IoJpeg7cJpcmd
{
	kulong word;
	struct {
		kulong jstart :1;
		kulong jrstart :1;
		kulong :29;
		kulong jreset :1;
	} bit;
} IoJpeg7cJpcmd;

/*	structure of jpstatus			(298C_0008h)	*/
typedef union _IoJpeg7cJpstatus
{
	kulong word;
	struct {
		kulong jpstatus :1;
		kulong :31;
	} bit;
} IoJpeg7cJpstatus;

/*	structure of jpqtable			(298C_000Ch)	*/
typedef union _IoJpeg7cJpqtable
{
	kulong word;
	struct {
		kulong qt0l :1;
		kulong qt0u :1;
		kulong qt1l :1;
		kulong qt1u :1;
		kulong qt2l :1;
		kulong qt2u :1;
		kulong :26;
	} bit;
} IoJpeg7cJpqtable;

/*	structure of jphtable			(298C_0010h)	*/
typedef union _IoJpeg7cJphtable
{
	kulong word;
	struct {
		kulong ht0dc :1;
		kulong ht0ac :1;
		kulong ht1dc :1;
		kulong ht1ac :1;
		kulong ht2dc :1;
		kulong ht2ac :1;
		kulong :26;
	} bit;
} IoJpeg7cJphtable;

/*	structure of jpdriset			(298C_0014h)	*/
typedef union _IoJpeg7cJpdriset
{
	kulong word;
	struct {
		kulong jpdriset :16;
		kulong :16;
	} bit;
} IoJpeg7cJpdriset;

/*	structure of jpheight			(298C_0018h)	*/
typedef union _IoJpeg7cJpheight
{
	kulong word;
	struct {
		kulong jpheight :16;
		kulong :16;
	} bit;
} IoJpeg7cJpheight;

/*	structure of jpwidth			(298C_001Ch)	*/
typedef union _IoJpeg7cJpwidth
{
	kulong word;
	struct {
		kulong jpwidth :16;
		kulong :16;
	} bit;
} IoJpeg7cJpwidth;

/*	structure of jpbytcnt			(298C_0020h)	*/
typedef union _IoJpeg7cJpbytcnt
{
	kulong word;
	struct {
		kulong jpbytcnt :32;
	} bit;
} IoJpeg7cJpbytcnt;

/*	structure of jpformat			(298C_0024h)	*/
typedef union _IoJpeg7cJpformat
{
	kulong word;
	struct {
		kulong codecnt :1;
		kulong mkskip :1;
		kulong exifmod :1;
		kulong :29;
	} bit;
} IoJpeg7cJpformat;

/*	structure of jpintset			(298C_0028h)	*/
typedef union _IoJpeg7cJpintset
{
	kulong word;
	struct {
		kulong appmkset :1;
		kulong commkset :1;
		kulong umkset :1;
		kulong regrdset :1;
		kulong qtwset :1;
		kulong :3;
		kulong rstset :1;
		kulong sizset :1;
		kulong corset :1;
		kulong :20;
		kulong intset :1;
	} bit;
} IoJpeg7cJpintset;

/*	structure of jpintsta			(298C_002Ch)	*/
typedef union _IoJpeg7cJpintsta
{
	kulong word;
	struct {
		kulong appmkinfo :1;
		kulong commkinfo :1;
		kulong umksinfo :1;
		kulong regrdint :1;
		kulong qtwint :1;
		kulong :3;
		kulong rsterr :1;
		kulong sizerr :1;
		kulong errflg :1;
		kulong :19;
		kulong corend :1;
		kulong intflg :1;
	} bit;
} IoJpeg7cJpintsta;

/*	structure of jperrcod			(298C_0030h)	*/
typedef union _IoJpeg7cJperrcod
{
	kulong word;
	struct {
		kulong jperrcod :6;
		kulong :26;
	} bit;
} IoJpeg7cJperrcod;

/*	structure of jpcorsta			(298C_0034h)	*/
typedef union _IoJpeg7cJpcorsta
{
	kulong word;
	struct {
		kulong cordriinfo :1;
		kulong corsizinfo :1;
		kulong :30;
	} bit;
} IoJpeg7cJpcorsta;

/*	structure of jpsuspend			(298C_0038h)	*/
typedef union _IoJpeg7cJpsuspend
{
	kulong word;
	struct {
		kulong jpsuspend :1;
		kulong :31;
	} bit;
} IoJpeg7cJpsuspend;

/*	structure of jpdnlset			(298C_003Ch)	*/
typedef union _IoJpeg7cJpdnlset
{
	kulong word;
	struct {
		kulong jpdnlset :16;
		kulong :16;
	} bit;
} IoJpeg7cJpdnlset;

/*	structure of Quantization table		(298C_0100h) (298C_0140h) (298C_0180h) (298C_01C0h)	*/
typedef union _IoJpeg7cJpqt
{
	kulong word[16];
	struct {
		kulong qt3 :8;
		kulong qt2 :8;
		kulong qt1 :8;
		kulong qt0 :8;
	} bit[16];
} IoJpeg7cJpqt;

/*	structure of Huffman DC Num			(298C_0200h) (298C_0300h)	*/	// Not Used
typedef union _IoJpeg7cJphtdn
{
	kulong word[4];
	struct {
		kulong htdn4 :8;
		kulong htdn3 :8;
		kulong htdn2 :8;
		kulong htdn1 :8;
	} bit[4];
} IoJpeg7cJphtdn;

/*	structure of Huffman DC Group No	(298C_0210h) (298C_0310h)	*/	// Not Used
typedef union _IoJpeg7cJphtds
{
	kulong word[3];
	struct {
		kulong htds3 :8;
		kulong htds2 :8;
		kulong htds1 :8;
		kulong htds0 :8;
	} bit[3];
} IoJpeg7cJphtds;

/*	structure of Huffman AC Num			(298C_0220h) (298C_0320h)	*/	// Not Used
typedef union _IoJpeg7cJphtan
{
	kulong word[4];
	struct {
		kulong htan4 :8;
		kulong htan3 :8;
		kulong htan2 :8;
		kulong htan1 :8;
	} bit[4];
} IoJpeg7cJphtan;

/*	structure of Huffman AC rs			(298C_0230h) (298C_0330h)	*/	// Not Used
typedef union _IoJpeg7cJphtars
{
	kulong word[40];
	struct {
		kulong htars3 :8;
		kulong htars2 :8;
		kulong htars1 :8;
		kulong htars0 :8;
	} bit[40];
} IoJpeg7cJphtars;

/*	structure of Huffman AC rs			(298C_02D0h) (298C_03D0h)	*/	// Not Used
typedef union _IoJpeg7cJphtars28
{
	kulong word;
	struct {
		kulong :16;
		kulong htars162 :8;
		kulong htars161 :8;
	} bit;
} IoJpeg7cJphtars28;

/*	structure of jictl			(298C_0400h)	*/
typedef union _IoJpeg7cJictl
{
	kulong word;
	struct {
		kulong :1;
		kulong b12m :1;
		kulong jirp :2;
		kulong jixp :2;
		kulong :8;
		kulong jitrg :2;
		kulong :16;
	} bit;
} IoJpeg7cJictl;

/*	structure of jcctl			(298C_0404h)	*/
typedef union _IoJpeg7cJcctl
{
	kulong word;
	struct {
		kulong jcps :1;
		kulong jcc :1;
		kulong jcrp :2;
		kulong :10;
		kulong jctrg :2;
		kulong :16;
	} bit;
} IoJpeg7cJcctl;

/*	structure of jmode			(298C_0408h)	*/
typedef union _IoJpeg7cJmode
{
	kulong word;
	struct {
		kulong jburstAlOn :1;
		kulong :9;
		kulong jjbendian :1;
		kulong jpbendian :1;
		kulong :4;
		kulong jmemform :2;
		kulong :2;
		kulong jpbdext :1;
		kulong :7;
		kulong jcscccen :1;
		kulong :3;
	} bit;
} IoJpeg7cJmode;

/*	structure of jimgygh		(298C_0410h)	*/
typedef union _IoJpeg7cJimgygh
{
	kulong word;
	struct {
		kulong jimgygh :20;
		kulong :12;
	} bit;
} IoJpeg7cJimgygh;

/*	structure of jimgcgh		(298C_0414h)	*/
typedef union _IoJpeg7cJimgcgh
{
	kulong word;
	struct {
		kulong jimgcgh :20;
		kulong :12;
	} bit;
} IoJpeg7cJimgcgh;

/*	structure of jimgsh			(298C_0418h)	*/
typedef union _IoJpeg7cJimgsh
{
	kulong word;
	struct {
		kulong jimgsh :16;
		kulong :16;
	} bit;
} IoJpeg7cJimgsh;

/*	structure of jimgsv			(298C_041Ch)	*/
typedef union _IoJpeg7cJimgsv
{
	kulong word;
	struct {
		kulong jimgsv :16;
		kulong :16;
	} bit;
} IoJpeg7cJimgsv;

/*	structure of jimgshdg		(298C_0420h)	*/
typedef union _IoJpeg7cJimgshdg
{
	kulong word;
	struct {
		kulong jimgshdg :16;
		kulong :16;
	} bit;
} IoJpeg7cJimgshdg;

/*	structure of jhoffset		(298C_0424h)	*/
typedef union _IoJpeg7cJhoffset
{
	kulong word;
	struct {
		kulong jhoffset :16;
		kulong :16;
	} bit;
} IoJpeg7cJhoffset;

/*	structure of jvoffset		(298C_0428h)	*/
typedef union _IoJpeg7cJvoffset
{
	kulong word;
	struct {
		kulong jvoffset :16;
		kulong :16;
	} bit;
} IoJpeg7cJvoffset;

/*	structure of jimgay			(298C_0430h)	*/
typedef union _IoJpeg7cJimgay
{
	kulong word;
	struct {
		kulong jimgay :32;
	} bit;
} IoJpeg7cJimgay;

/*	structure of jimgacb		(298C_0434h)	*/
typedef union _IoJpeg7cJimgacb
{
	kulong word;
	struct {
		kulong jimgacb :32;
	} bit;
} IoJpeg7cJimgacb;

/*	structure of JC0DA			(298C_0440h)	*/
typedef union _IoJpeg7cJcoda
{
	kulong word;
	struct {
		kulong jcoda :32;
	} bit;
} IoJpeg7cJcoda;

/*	structure of jlineval		(298C_0450h)	*/
typedef union _IoJpeg7cJlineval
{
	kulong word;
	struct {
		kulong jlineval :16;
		kulong :16;
	} bit;
} IoJpeg7cJlineval;

/*	structure of jsectval		(298C_0454h)	*/
typedef union _IoJpeg7cJsectval
{
	kulong word;
	struct {
		kulong jsectval :32;
	} bit;
} IoJpeg7cJsectval;

/*	structure of JC0DSV			(298C_0458h)	*/
typedef union _IoJpeg7cJcodsv
{
	kulong word;
	struct {
		kulong jcodsv :32;
	} bit;
} IoJpeg7cJcodsv;

/*	structure of jisvmn			(298C_0470h)	*/
typedef union _IoJpeg7cJisvmn
{
	kulong word;
	struct {
		kulong jisvmn :16;
		kulong :16;
	} bit;
} IoJpeg7cJisvmn;

/*	structure of jsctc			(298C_0474h)	*/
typedef union _IoJpeg7cJsctc
{
	kulong word;
	struct {
		kulong jsctc :32;
	} bit;
} IoJpeg7cJsctc;

/*	structure of jint			(298C_0480h)	*/
typedef union _IoJpeg7cJint
{
	kulong word;
	struct {
		kulong :12;
		kulong __jcpf :1;
		kulong :1;
		kulong __jcf :1;
		kulong __jif :1;
		kulong __jsectint :1;
		kulong __jlineint :1;
		kulong __jclrfmer :1;
		kulong :3;
		kulong __jjbint :1;
		kulong __jpbint :1;
		kulong jjirqst :3;
		kulong jjirq :1;
		kulong :1;
		kulong jerrint :1;
		kulong :1;
		kulong jallint :1;
	} bit;
} IoJpeg7cJint;

/*	structure of jinten			(298C_0484h)	*/
typedef union _IoJpeg7cJinten
{
	kulong word;
	struct {
		kulong :12;
		kulong jcpfen :1;
		kulong :1;
		kulong jcfen :1;
		kulong jifen :1;
		kulong jsecten :1;
		kulong jlineen :1;
		kulong jclrfmeren :1;
		kulong :3;
		kulong jjben :1;
		kulong jpben :1;
		kulong :8;
	} bit;
} IoJpeg7cJinten;

/*	structure of jstate			(298C_0488h)	*/
typedef union _IoJpeg7cJstate
{
	kulong word;
	struct {
		kulong :6;
		kulong jjbactp :1;
		kulong jpbactp :1;
		kulong :7;
		kulong jallactp :1;
		kulong :6;
		kulong jjbrstp :1;
		kulong jpbrstp :1;
		kulong :7;
		kulong jallrstp :1;
	} bit;
} IoJpeg7cJstate;

/*	structure of jpbsta			(298C_0490h)	*/
typedef union _IoJpeg7cJpbsta
{
	kulong word;
	struct {
		kulong jpaprot :3;
		kulong :1;
		kulong jpacache :4;
		kulong :12;
		kulong jpissueset :2;
		kulong :2;
		kulong jpres :2;
		kulong :6;
	} bit;
} IoJpeg7cJpbsta;

/*	structure of jjbsta			(298C_0494h)	*/
typedef union _IoJpeg7cJjbsta
{
	kulong word;
	struct {
		kulong japrot :3;
		kulong :1;
		kulong jjacache :4;
		kulong :12;
		kulong jjissueset :2;
		kulong :2;
		kulong jjres :2;
		kulong :6;
	} bit;
} IoJpeg7cJjbsta;

/*	structure of jbandcolor			(298C_04B0h)	*/
typedef union _IoJpeg7cJbandcolor
{
	kulong word;
	struct {
		kulong jbandy :8;
		kulong jbandcb :8;
		kulong jbandcr :8;
		kulong :8;
	} bit;
} IoJpeg7cJbandcolor;

/*	structure of jcsccc0-1			(298C_04C0h)	*/
/*	structure of jcsccc1-1			(298C_04C8h)	*/
/*	structure of JCSCCC2-1			(298C_04D0h)	*/
typedef union _IoJpeg7cJcsccc1
{
	kulong word;
	struct {
		kulong jcsccc0 :10;
		kulong :6;
		kulong jcsccc1 :10;
		kulong :6;
	} bit;
} IoJpeg7cJcsccc1;

/*	structure of jcsccc0-2			(298C_04C4h)	*/
/*	structure of jcsccc1-2			(298C_04CCh)	*/
/*	structure of JCSCCC2-2			(298C_04D4h)	*/
typedef union _IoJpeg7cJcsccc2
{
	kulong word;
	struct {
		kulong jcsccc2 :10;
		kulong :22;
	} bit;
} IoJpeg7cJcsccc2;

/*	structure of iipset				(298C_04E0h)	*/
typedef union _IoJpeg7cIipset
{
	kulong word;
	struct {
		kulong portMode :3;
		kulong ringOn :1;
		kulong blkSize :2;
		kulong :2;
		kulong ringSize :8;
		kulong :16;
	} bit;
} IoJpeg7cIipset;

/* Define i/o mapping */
typedef struct _IoFJpg7cWrap
{
	/* 298C_(0000 - 0003h) */
	IoJpeg7cJpmode jpmode;
	/* 298C_(0004 - 0007h) */
	IoJpeg7cJpcmd jpcmd;
	/* 298C_(0008 - 000Bh) */
	IoJpeg7cJpstatus jpstatus;
	/* 298C_(000C - 000Fh) */
	IoJpeg7cJpqtable jpqtable;
	/* 298C_(0010 - 0013h) */
	IoJpeg7cJphtable jphtable;
	/* 298C_(0014 - 0017h) */
	IoJpeg7cJpdriset jpdriset;
	/* 298C_(0018 - 001Bh) */
	IoJpeg7cJpheight jpheight;
	/* 298C_(001C - 001Fh) */
	IoJpeg7cJpwidth jpwidth;
	/* 298C_(0020 - 0023h) */
	IoJpeg7cJpbytcnt jpbytcnt;
	/* 298C_(0024 - 0027h) */
	IoJpeg7cJpformat jpformat;
	/* 298C_(0028 - 002Bh) */
	IoJpeg7cJpintset jpintset;
	/* 298C_(002C - 002Fh) */
	IoJpeg7cJpintsta jpintsta;
	/* 298C_(0030 - 0033h) */
	IoJpeg7cJperrcod jperrcod;
	/* 298C_(0034 - 0037h) */
	IoJpeg7cJpcorsta jpcorsta;
	/* 298C_(0038 - 003Bh) */
	IoJpeg7cJpsuspend jpsuspend;
	/* 298C_(003C - 003Fh) */
	IoJpeg7cJpdnlset jpdnlset;
	/* 298C_(0040 - 00FFh) */
	kuchar dmy004000ff[0x0100 - 0x0040];
	/* 298C_(0100 - 013Fh) */
	IoJpeg7cJpqt jpqt0;
	/* 298C_(0140 - 017Fh) */
	IoJpeg7cJpqt jpqt1;
	/* 298C_(0180 - 01BFh) */
	IoJpeg7cJpqt jpqt2;
	/* 298C_(01C0 - 01FFh) */
	IoJpeg7cJpqt jpqt3;
	/* 298C_(0200 - 020Fh) */
	IoJpeg7cJphtdn jphtd0n;
	/* 298C_(0210 - 021Bh) */
	IoJpeg7cJphtds jphtd0s;
	/* 298C_(021C - 021Fh) */
	kuchar dmy021c021f[0x0220 - 0x021C];
	/* 298C_(0220 - 022Fh) */
	IoJpeg7cJphtan jphta0n;
	/* 298C_(0230 - 02CFh) */
	IoJpeg7cJphtars jphta0rs;
	/* 298C_(02D0 - 02D3h) */
	IoJpeg7cJphtars28 jphta0rs28;
	/* 298C_(02D4 - 02FFh) */
	kuchar dmy02d402ff[0x0300 - 0x02D4];
	/* 298C_(0300 - 030Fh) */
	IoJpeg7cJphtdn jphtd1n;
	/* 298C_(0310 - 031Bh) */
	IoJpeg7cJphtds jphtd1s;
	/* 298C_(031C - 031Fh) */
	kuchar dmy031c031f[0x0320 - 0x031C];
	/* 298C_(0320 - 032Fh) */
	IoJpeg7cJphtan jphta1n;
	/* 298C_(0330 - 03CFh) */
	IoJpeg7cJphtars jphta1rs;
	/* 298C_(03D0 - 03D3h) */
	IoJpeg7cJphtars28 jphta1rs28;
	/* 298C_(03D4 - 03FFh) */
	kuchar dmy03d403ff[0x0400 - 0x03D4];
	/* 298C_(0400 - 0403h) */
	IoJpeg7cJictl jictl;
	/* 298C_(0404 - 0407h) */
	IoJpeg7cJcctl jcctl;
	/* 298C_(0408 - 040Bh) */
	IoJpeg7cJmode jmode;
	/* 298C_(040C - 040Fh) */
	kuchar dmy040c040f[0x0410 - 0x040C];
	/* 298C_(0410 - 0413h) */
	IoJpeg7cJimgygh jimgygh;
	/* 298C_(0414 - 0417h) */
	IoJpeg7cJimgcgh jimgcgh;
	/* 298C_(0418 - 041Bh) */
	IoJpeg7cJimgsh jimgsh;
	/* 298C_(041C - 041Fh) */
	IoJpeg7cJimgsv jimgsv;
	/* 298C_(0420 - 0423h) */
	IoJpeg7cJimgshdg jimgshdg;
	/* 298C_(0424 - 0427h) */
	IoJpeg7cJhoffset jhoffset;
	/* 298C_(0428 - 042Bh) */
	IoJpeg7cJvoffset jvoffset;
	/* 298C_(042C - 042Fh) */
	kuchar dmy042c042f[0x0430 - 0x042C];
	/* 298C_(0430 - 0433h) */
	IoJpeg7cJimgay jimgay;
	/* 298C_(0434 - 0437h) */
	IoJpeg7cJimgacb jimgacb;
	/* 298C_(0438 - 043Fh) */
	kuchar dmy0438043f[0x0440 - 0x0438];
	/* 298C_(0440 - 0443h) */
	IoJpeg7cJcoda jcoda;
	/* 298C_(0444 - 044Fh) */
	kuchar dmy0444044f[0x0450 - 0x0444];
	/* 298C_(0450 - 0453h) */
	IoJpeg7cJlineval jlineval;
	/* 298C_(0454 - 0457h) */
	IoJpeg7cJsectval jsectval;
	/* 298C_(0458 - 045Bh) */
	IoJpeg7cJcodsv jcodsv;
	/* 298C_(045C - 046Fh) */
	kuchar dmy045c046f[0x0470 - 0x045C];
	/* 298C_(0470 - 0473h) */
	IoJpeg7cJisvmn jisvmn;
	/* 298C_(0474 - 0477h) */
	IoJpeg7cJsctc jsctc;
	/* 298C_(0478 - 047Fh) */
	kuchar dmy0478047f[0x0480 - 0x0478];
	/* 298C_(0480 - 0483h) */
	IoJpeg7cJint jint;
	/* 298C_(0484 - 0487h) */
	IoJpeg7cJinten jinten;
	/* 298C_(0488 - 048Bh) */
	IoJpeg7cJstate jstate;
	/* 298C_(048C - 048Fh) */
	kuchar dmy048c048f[0x0490 - 0x048C];
	/* 298C_(0490 - 0493h) */
	IoJpeg7cJpbsta jpbsta;
	/* 298C_(0494 - 0497h) */
	IoJpeg7cJjbsta jjbsta;
	/* 298C_(0498 - 04AFh) */
	kuchar dmy049804af[0x04B0 - 0x0498];
	/* 298C_(04B0 - 04B3h) */
	IoJpeg7cJbandcolor jbandcolor;
	/* 298C_(04B4 - 04BFh) */
	kuchar dmy04b404bf[0x04C0 - 0x04B4];
	/* 298C_(04C0 - 04C3h) */
	IoJpeg7cJcsccc1 jcsccc01;
	/* 298C_(04C4 - 04C7h) */
	IoJpeg7cJcsccc2 jcsccc02;
	/* 298C_(04C8 - 04CBh) */
	IoJpeg7cJcsccc1 jcsccc11;
	/* 298C_(04CC - 04CFh) */
	IoJpeg7cJcsccc2 jcsccc12;
	/* 298C_(04D0 - 04D3h) */
	IoJpeg7cJcsccc1 jcsccc21;
	/* 298C_(04D4 - 04D7h) */
	IoJpeg7cJcsccc2 jcsccc22;
	/* 298C_(04D8 - 04DFh) */
	kuchar dmy04d804df[0x04E0 - 0x04D8];
	/* 298C_(04E0 - 04E3h) */
	IoJpeg7cIipset iipset;
	/* 298C_04E4 - 298C_0FFFh) */
	kuchar dmy298c04e4298c0fff[0x298C1000 - 0x298C04E4];
} IoFJpg7cWrap;

extern volatile IoFJpg7cWrap	ioJpg7;


KConstType	k_jdsjp7_get_type(void);
KJdsjp7*	k_jdsjp7_new(void);


#endif/*__K_JDSJP7_H__*/

