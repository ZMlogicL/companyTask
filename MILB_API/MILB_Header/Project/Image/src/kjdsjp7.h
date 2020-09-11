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
	unsigned long word;
	struct {
		unsigned long mmode :3;
		unsigned long disposal :1;
		unsigned long pEndian :1;
		unsigned long sEndian :1;
		unsigned long :26;
	} bit;
} IoJpeg7cJpmode;

/*	structure of jpcmd				(298C_0004h)	*/
typedef union _IoJpeg7cJpcmd
{
	unsigned long word;
	struct {
		unsigned long jstart :1;
		unsigned long jrstart :1;
		unsigned long :29;
		unsigned long jreset :1;
	} bit;
} IoJpeg7cJpcmd;

/*	structure of jpstatus			(298C_0008h)	*/
typedef union _IoJpeg7cJpstatus
{
	unsigned long word;
	struct {
		unsigned long jpstatus :1;
		unsigned long :31;
	} bit;
} IoJpeg7cJpstatus;

/*	structure of jpqtable			(298C_000Ch)	*/
typedef union _IoJpeg7cJpqtable
{
	unsigned long word;
	struct {
		unsigned long qt0l :1;
		unsigned long qt0u :1;
		unsigned long qt1l :1;
		unsigned long qt1u :1;
		unsigned long qt2l :1;
		unsigned long qt2u :1;
		unsigned long :26;
	} bit;
} IoJpeg7cJpqtable;

/*	structure of jphtable			(298C_0010h)	*/
typedef union _IoJpeg7cJphtable
{
	unsigned long word;
	struct {
		unsigned long ht0dc :1;
		unsigned long ht0ac :1;
		unsigned long ht1dc :1;
		unsigned long ht1ac :1;
		unsigned long ht2dc :1;
		unsigned long ht2ac :1;
		unsigned long :26;
	} bit;
} IoJpeg7cJphtable;

/*	structure of jpdriset			(298C_0014h)	*/
typedef union _IoJpeg7cJpdriset
{
	unsigned long word;
	struct {
		unsigned long jpdriset :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJpdriset;

/*	structure of jpheight			(298C_0018h)	*/
typedef union _IoJpeg7cJpheight
{
	unsigned long word;
	struct {
		unsigned long jpheight :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJpheight;

/*	structure of jpwidth			(298C_001Ch)	*/
typedef union _IoJpeg7cJpwidth
{
	unsigned long word;
	struct {
		unsigned long jpwidth :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJpwidth;

/*	structure of jpbytcnt			(298C_0020h)	*/
typedef union _IoJpeg7cJpbytcnt
{
	unsigned long word;
	struct {
		unsigned long jpbytcnt :32;
	} bit;
} IoJpeg7cJpbytcnt;

/*	structure of jpformat			(298C_0024h)	*/
typedef union _IoJpeg7cJpformat
{
	unsigned long word;
	struct {
		unsigned long codecnt :1;
		unsigned long mkskip :1;
		unsigned long exifmod :1;
		unsigned long :29;
	} bit;
} IoJpeg7cJpformat;

/*	structure of jpintset			(298C_0028h)	*/
typedef union _IoJpeg7cJpintset
{
	unsigned long word;
	struct {
		unsigned long appmkset :1;
		unsigned long commkset :1;
		unsigned long umkset :1;
		unsigned long regrdset :1;
		unsigned long qtwset :1;
		unsigned long :3;
		unsigned long rstset :1;
		unsigned long sizset :1;
		unsigned long corset :1;
		unsigned long :20;
		unsigned long intset :1;
	} bit;
} IoJpeg7cJpintset;

/*	structure of jpintsta			(298C_002Ch)	*/
typedef union _IoJpeg7cJpintsta
{
	unsigned long word;
	struct {
		unsigned long appmkinfo :1;
		unsigned long commkinfo :1;
		unsigned long umksinfo :1;
		unsigned long regrdint :1;
		unsigned long qtwint :1;
		unsigned long :3;
		unsigned long rsterr :1;
		unsigned long sizerr :1;
		unsigned long errflg :1;
		unsigned long :19;
		unsigned long corend :1;
		unsigned long intflg :1;
	} bit;
} IoJpeg7cJpintsta;

/*	structure of jperrcod			(298C_0030h)	*/
typedef union _IoJpeg7cJperrcod
{
	unsigned long word;
	struct {
		unsigned long jperrcod :6;
		unsigned long :26;
	} bit;
} IoJpeg7cJperrcod;

/*	structure of jpcorsta			(298C_0034h)	*/
typedef union _IoJpeg7cJpcorsta
{
	unsigned long word;
	struct {
		unsigned long cordriinfo :1;
		unsigned long corsizinfo :1;
		unsigned long :30;
	} bit;
} IoJpeg7cJpcorsta;

/*	structure of jpsuspend			(298C_0038h)	*/
typedef union _IoJpeg7cJpsuspend
{
	unsigned long word;
	struct {
		unsigned long jpsuspend :1;
		unsigned long :31;
	} bit;
} IoJpeg7cJpsuspend;

/*	structure of jpdnlset			(298C_003Ch)	*/
typedef union _IoJpeg7cJpdnlset
{
	unsigned long word;
	struct {
		unsigned long jpdnlset :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJpdnlset;

/*	structure of Quantization table		(298C_0100h) (298C_0140h) (298C_0180h) (298C_01C0h)	*/
typedef union _IoJpeg7cJpqt
{
	unsigned long word[16];
	struct {
		unsigned long qt3 :8;
		unsigned long qt2 :8;
		unsigned long qt1 :8;
		unsigned long qt0 :8;
	} bit[16];
} IoJpeg7cJpqt;

/*	structure of Huffman DC Num			(298C_0200h) (298C_0300h)	*/	// Not Used
typedef union _IoJpeg7cJphtdn
{
	unsigned long word[4];
	struct {
		unsigned long htdn4 :8;
		unsigned long htdn3 :8;
		unsigned long htdn2 :8;
		unsigned long htdn1 :8;
	} bit[4];
} IoJpeg7cJphtdn;

/*	structure of Huffman DC Group No	(298C_0210h) (298C_0310h)	*/	// Not Used
typedef union _IoJpeg7cJphtds
{
	unsigned long word[3];
	struct {
		unsigned long htds3 :8;
		unsigned long htds2 :8;
		unsigned long htds1 :8;
		unsigned long htds0 :8;
	} bit[3];
} IoJpeg7cJphtds;

/*	structure of Huffman AC Num			(298C_0220h) (298C_0320h)	*/	// Not Used
typedef union _IoJpeg7cJphtan
{
	unsigned long word[4];
	struct {
		unsigned long htan4 :8;
		unsigned long htan3 :8;
		unsigned long htan2 :8;
		unsigned long htan1 :8;
	} bit[4];
} IoJpeg7cJphtan;

/*	structure of Huffman AC RS			(298C_0230h) (298C_0330h)	*/	// Not Used
typedef union _IoJpeg7cJphtars
{
	unsigned long word[40];
	struct {
		unsigned long htars3 :8;
		unsigned long htars2 :8;
		unsigned long htars1 :8;
		unsigned long htars0 :8;
	} bit[40];
} IoJpeg7cJphtars;

/*	structure of Huffman AC RS			(298C_02D0h) (298C_03D0h)	*/	// Not Used
typedef union _IoJpeg7cJphtars28
{
	unsigned long word;
	struct {
		unsigned long :16;
		unsigned long htars162 :8;
		unsigned long htars161 :8;
	} bit;
} IoJpeg7cJphtars28;

/*	structure of jictl			(298C_0400h)	*/
typedef union _IoJpeg7cJictl
{
	unsigned long word;
	struct {
		unsigned long :1;
		unsigned long b12m :1;
		unsigned long jirp :2;
		unsigned long jixp :2;
		unsigned long :8;
		unsigned long jitrg :2;
		unsigned long :16;
	} bit;
} IoJpeg7cJictl;

/*	structure of jcctl			(298C_0404h)	*/
typedef union _IoJpeg7cJcctl
{
	unsigned long word;
	struct {
		unsigned long jcps :1;
		unsigned long jcc :1;
		unsigned long jcrp :2;
		unsigned long :10;
		unsigned long jctrg :2;
		unsigned long :16;
	} bit;
} IoJpeg7cJcctl;

/*	structure of jmode			(298C_0408h)	*/
typedef union _IoJpeg7cJmode
{
	unsigned long word;
	struct {
		unsigned long jburstAlOn :1;
		unsigned long :9;
		unsigned long jjbendian :1;
		unsigned long jpbendian :1;
		unsigned long :4;
		unsigned long jmemform :2;
		unsigned long :2;
		unsigned long jpbdext :1;
		unsigned long :7;
		unsigned long jcscccen :1;
		unsigned long :3;
	} bit;
} IoJpeg7cJmode;

/*	structure of jimgygh		(298C_0410h)	*/
typedef union _IoJpeg7cJimgygh
{
	unsigned long word;
	struct {
		unsigned long jimgygh :20;
		unsigned long :12;
	} bit;
} IoJpeg7cJimgygh;

/*	structure of jimgcgh		(298C_0414h)	*/
typedef union _IoJpeg7cJimgcgh
{
	unsigned long word;
	struct {
		unsigned long jimgcgh :20;
		unsigned long :12;
	} bit;
} IoJpeg7cJimgcgh;

/*	structure of jimgsh			(298C_0418h)	*/
typedef union _IoJpeg7cJimgsh
{
	unsigned long word;
	struct {
		unsigned long jimgsh :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJimgsh;

/*	structure of jimgsv			(298C_041Ch)	*/
typedef union _IoJpeg7cJimgsv
{
	unsigned long word;
	struct {
		unsigned long jimgsv :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJimgsv;

/*	structure of jimgshdg		(298C_0420h)	*/
typedef union _IoJpeg7cJimgshdg
{
	unsigned long word;
	struct {
		unsigned long jimgshdg :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJimgshdg;

/*	structure of jhoffset		(298C_0424h)	*/
typedef union _IoJpeg7cJhoffset
{
	unsigned long word;
	struct {
		unsigned long jhoffset :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJhoffset;

/*	structure of jvoffset		(298C_0428h)	*/
typedef union _IoJpeg7cJvoffset
{
	unsigned long word;
	struct {
		unsigned long jvoffset :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJvoffset;

/*	structure of jimgay			(298C_0430h)	*/
typedef union _IoJpeg7cJimgay
{
	unsigned long word;
	struct {
		unsigned long jimgay :32;
	} bit;
} IoJpeg7cJimgay;

/*	structure of jimgacb		(298C_0434h)	*/
typedef union _IoJpeg7cJimgacb
{
	unsigned long word;
	struct {
		unsigned long jimgacb :32;
	} bit;
} IoJpeg7cJimgacb;

/*	structure of JC0DA			(298C_0440h)	*/
typedef union _IoJpeg7cJcoda
{
	unsigned long word;
	struct {
		unsigned long jcoda :32;
	} bit;
} IoJpeg7cJcoda;

/*	structure of jlineval		(298C_0450h)	*/
typedef union _IoJpeg7cJlineval
{
	unsigned long word;
	struct {
		unsigned long jlineval :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJlineval;

/*	structure of jsectval		(298C_0454h)	*/
typedef union _IoJpeg7cJsectval
{
	unsigned long word;
	struct {
		unsigned long jsectval :32;
	} bit;
} IoJpeg7cJsectval;

/*	structure of JC0DSV			(298C_0458h)	*/
typedef union _IoJpeg7cJcodsv
{
	unsigned long word;
	struct {
		unsigned long jcodsv :32;
	} bit;
} IoJpeg7cJcodsv;

/*	structure of jisvmn			(298C_0470h)	*/
typedef union _IoJpeg7cJisvmn
{
	unsigned long word;
	struct {
		unsigned long jisvmn :16;
		unsigned long :16;
	} bit;
} IoJpeg7cJisvmn;

/*	structure of jsctc			(298C_0474h)	*/
typedef union _IoJpeg7cJsctc
{
	unsigned long word;
	struct {
		unsigned long jsctc :32;
	} bit;
} IoJpeg7cJsctc;

/*	structure of jint			(298C_0480h)	*/
typedef union _IoJpeg7cJint
{
	unsigned long word;
	struct {
		unsigned long :12;
		unsigned long __jcpf :1;
		unsigned long :1;
		unsigned long __jcf :1;
		unsigned long __jif :1;
		unsigned long __jsectint :1;
		unsigned long __jlineint :1;
		unsigned long __jclrfmer :1;
		unsigned long :3;
		unsigned long __jjbint :1;
		unsigned long __jpbint :1;
		unsigned long jjirqst :3;
		unsigned long jjirq :1;
		unsigned long :1;
		unsigned long jerrint :1;
		unsigned long :1;
		unsigned long jallint :1;
	} bit;
} IoJpeg7cJint;

/*	structure of jinten			(298C_0484h)	*/
typedef union _IoJpeg7cJinten
{
	unsigned long word;
	struct {
		unsigned long :12;
		unsigned long jcpfen :1;
		unsigned long :1;
		unsigned long jcfen :1;
		unsigned long jifen :1;
		unsigned long jsecten :1;
		unsigned long jlineen :1;
		unsigned long jclrfmeren :1;
		unsigned long :3;
		unsigned long jjben :1;
		unsigned long jpben :1;
		unsigned long :8;
	} bit;
} IoJpeg7cJinten;

/*	structure of jstate			(298C_0488h)	*/
typedef union _IoJpeg7cJstate
{
	unsigned long word;
	struct {
		unsigned long :6;
		unsigned long jjbactp :1;
		unsigned long jpbactp :1;
		unsigned long :7;
		unsigned long jallactp :1;
		unsigned long :6;
		unsigned long jjbrstp :1;
		unsigned long jpbrstp :1;
		unsigned long :7;
		unsigned long jallrstp :1;
	} bit;
} IoJpeg7cJstate;

/*	structure of jpbsta			(298C_0490h)	*/
typedef union _IoJpeg7cJpbsta
{
	unsigned long word;
	struct {
		unsigned long jpaprot :3;
		unsigned long :1;
		unsigned long jpacache :4;
		unsigned long :12;
		unsigned long jpissueset :2;
		unsigned long :2;
		unsigned long jpres :2;
		unsigned long :6;
	} bit;
} IoJpeg7cJpbsta;

/*	structure of jjbsta			(298C_0494h)	*/
typedef union _IoJpeg7cJjbsta
{
	unsigned long word;
	struct {
		unsigned long japrot :3;
		unsigned long :1;
		unsigned long jjacache :4;
		unsigned long :12;
		unsigned long jjissueset :2;
		unsigned long :2;
		unsigned long jjres :2;
		unsigned long :6;
	} bit;
} IoJpeg7cJjbsta;

/*	structure of jbandcolor			(298C_04B0h)	*/
typedef union _IoJpeg7cJbandcolor
{
	unsigned long word;
	struct {
		unsigned long jbandy :8;
		unsigned long jbandcb :8;
		unsigned long jbandcr :8;
		unsigned long :8;
	} bit;
} IoJpeg7cJbandcolor;

/*	structure of jcsccc0-1			(298C_04C0h)	*/
/*	structure of jcsccc1-1			(298C_04C8h)	*/
/*	structure of JCSCCC2-1			(298C_04D0h)	*/
typedef union _IoJpeg7cJcsccc1
{
	unsigned long word;
	struct {
		unsigned long jcsccc0 :10;
		unsigned long :6;
		unsigned long jcsccc1 :10;
		unsigned long :6;
	} bit;
} IoJpeg7cJcsccc1;

/*	structure of jcsccc0-2			(298C_04C4h)	*/
/*	structure of jcsccc1-2			(298C_04CCh)	*/
/*	structure of JCSCCC2-2			(298C_04D4h)	*/
typedef union _IoJpeg7cJcsccc2
{
	unsigned long word;
	struct {
		unsigned long jcsccc2 :10;
		unsigned long :22;
	} bit;
} IoJpeg7cJcsccc2;

/*	structure of iipset				(298C_04E0h)	*/
typedef union _IoJpeg7cIipset
{
	unsigned long word;
	struct {
		unsigned long portMode :3;
		unsigned long ringOn :1;
		unsigned long blkSize :2;
		unsigned long :2;
		unsigned long ringSize :8;
		unsigned long :16;
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
	unsigned char dmy004000ff[0x0100 - 0x0040];
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
	unsigned char dmy021c021f[0x0220 - 0x021C];
	/* 298C_(0220 - 022Fh) */
	IoJpeg7cJphtan jphta0n;
	/* 298C_(0230 - 02CFh) */
	IoJpeg7cJphtars jphta0rs;
	/* 298C_(02D0 - 02D3h) */
	IoJpeg7cJphtars28 jphta0rs28;
	/* 298C_(02D4 - 02FFh) */
	unsigned char dmy02d402ff[0x0300 - 0x02D4];
	/* 298C_(0300 - 030Fh) */
	IoJpeg7cJphtdn jphtd1n;
	/* 298C_(0310 - 031Bh) */
	IoJpeg7cJphtds jphtd1s;
	/* 298C_(031C - 031Fh) */
	unsigned char dmy031c031f[0x0320 - 0x031C];
	/* 298C_(0320 - 032Fh) */
	IoJpeg7cJphtan jphta1n;
	/* 298C_(0330 - 03CFh) */
	IoJpeg7cJphtars jphta1rs;
	/* 298C_(03D0 - 03D3h) */
	IoJpeg7cJphtars28 jphta1rs28;
	/* 298C_(03D4 - 03FFh) */
	unsigned char dmy03d403ff[0x0400 - 0x03D4];
	/* 298C_(0400 - 0403h) */
	IoJpeg7cJictl jictl;
	/* 298C_(0404 - 0407h) */
	IoJpeg7cJcctl jcctl;
	/* 298C_(0408 - 040Bh) */
	IoJpeg7cJmode jmode;
	/* 298C_(040C - 040Fh) */
	unsigned char dmy040c040f[0x0410 - 0x040C];
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
	unsigned char dmy042c042f[0x0430 - 0x042C];
	/* 298C_(0430 - 0433h) */
	IoJpeg7cJimgay jimgay;
	/* 298C_(0434 - 0437h) */
	IoJpeg7cJimgacb jimgacb;
	/* 298C_(0438 - 043Fh) */
	unsigned char dmy0438043f[0x0440 - 0x0438];
	/* 298C_(0440 - 0443h) */
	IoJpeg7cJcoda jcoda;
	/* 298C_(0444 - 044Fh) */
	unsigned char dmy0444044f[0x0450 - 0x0444];
	/* 298C_(0450 - 0453h) */
	IoJpeg7cJlineval jlineval;
	/* 298C_(0454 - 0457h) */
	IoJpeg7cJsectval jsectval;
	/* 298C_(0458 - 045Bh) */
	IoJpeg7cJcodsv jcodsv;
	/* 298C_(045C - 046Fh) */
	unsigned char dmy045c046f[0x0470 - 0x045C];
	/* 298C_(0470 - 0473h) */
	IoJpeg7cJisvmn jisvmn;
	/* 298C_(0474 - 0477h) */
	IoJpeg7cJsctc jsctc;
	/* 298C_(0478 - 047Fh) */
	unsigned char dmy0478047f[0x0480 - 0x0478];
	/* 298C_(0480 - 0483h) */
	IoJpeg7cJint jint;
	/* 298C_(0484 - 0487h) */
	IoJpeg7cJinten jinten;
	/* 298C_(0488 - 048Bh) */
	IoJpeg7cJstate jstate;
	/* 298C_(048C - 048Fh) */
	unsigned char dmy048c048f[0x0490 - 0x048C];
	/* 298C_(0490 - 0493h) */
	IoJpeg7cJpbsta jpbsta;
	/* 298C_(0494 - 0497h) */
	IoJpeg7cJjbsta jjbsta;
	/* 298C_(0498 - 04AFh) */
	unsigned char dmy049804af[0x04B0 - 0x0498];
	/* 298C_(04B0 - 04B3h) */
	IoJpeg7cJbandcolor jbandcolor;
	/* 298C_(04B4 - 04BFh) */
	unsigned char dmy04b404bf[0x04C0 - 0x04B4];
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
	unsigned char dmy04d804df[0x04E0 - 0x04D8];
	/* 298C_(04E0 - 04E3h) */
	IoJpeg7cIipset iipset;
	/* 298C_04E4 - 298C_0FFFh) */
	unsigned char dmy298c04e4298c0fff[0x298C1000 - 0x298C04E4];
} IoFJpg7cWrap;

extern volatile IoFJpg7cWrap	ioJpg7;


KConstType	k_jdsjp7_get_type(void);
KJdsjp7*	k_jdsjp7_new(void);


#endif/*__K_JDSJP7_H__*/

