/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :陈倩
 *@brief             :kjdsmxic
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


#ifndef __K_JDSMXIC_H__
#define __K_JDSMXIC_H__


#include <klib.h>
//#include	"__jdsmxic_tbl.h"
#include "kjdsmxic1.h"


#define K_TYPE_JDSMXIC				(k_jdsmxic_get_type())
#define K_JDSMXIC(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsmxic))
#define K_IS_JDSMXIC(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSMXIC))


typedef struct _KJdsmxic 			KJdsmxic;
typedef struct _KJdsmxicPrivate KJdsmxicPrivate;


struct _KJdsmxic
{
	KObject parent;
};


/*	structure of tckenp		*/
typedef union _IoMxicTckenp
{
	unsigned long word;
	struct
	{
		unsigned long tckenp1 :4;
		unsigned long :4;
		unsigned long tckenp2 :4;
		unsigned long :4;
		unsigned long tckenp3 :4;
		unsigned long :4;
		unsigned long tckenp4 :4;
		unsigned long :4;
	} bit;
} IoMxicTckenp;

/*	structure of tmie		*/
typedef union _IoMxicTmie
{
	unsigned long word;
	struct
	{
		unsigned long tce :1;
		unsigned long tme :1;
		unsigned long tdewe :1;
		unsigned long tdere :1;
		unsigned long tsawe :1;
		unsigned long :27;
	} bit;
} IoMxicTmie;

/*	structure of tmif		*/
typedef union _IoMxicTmif
{
	unsigned long word;
	struct
	{
		unsigned long __tcf :1;
		unsigned long __tmf :1;
		unsigned long __tdewf :1;
		unsigned long __tderf :1;
		unsigned long __tsawf :1;
		unsigned long :27;
	} bit;
} IoMxicTmif;

/*	structure of tdestw		*/
typedef union _IoMxicTdestw
{
	unsigned long word[2];
	struct
	{
		unsigned long tdemnw :7;
		unsigned long :25;
		unsigned long tdeadw :32;
	} bit;
} IoMxicTdestw;

/*	structure of tdestr		*/
typedef union _IoMxicTdestr
{
	unsigned long word[2];
	struct
	{
		unsigned long tdemnr :7;
		unsigned long :25;
		unsigned long tdeadr :32;
	} bit;
} IoMxicTdestr;

/*	structure of tcftrg		*/
typedef union _IoMxicTcftrg
{
	unsigned long word;
	struct
	{
		unsigned long tcftrg :1;
		unsigned long :31;
	} bit;
} IoMxicTcftrg;

/*	structure of tcfmd		*/
typedef union _IoMxicTcfmd
{
	unsigned long word[2];
	struct
	{
		unsigned long tcflg :1;
		unsigned long :7;
		unsigned long tenw1 :4;
		unsigned long tenw2 :4;
		unsigned long tenw3 :4;
		unsigned long tenw4 :4;
		unsigned long tenr1 :4;
		unsigned long tenr2 :4;
		unsigned long tenr3 :4;
		unsigned long tenr4 :4;
		unsigned long :24;
	} bit;
} IoMxicTcfmd;

/*	structure of tdeclr		*/
typedef union _IoMxicTdeclr
{
	unsigned long word;
	struct
	{
		unsigned long tdeclr :1;
		unsigned long :31;
	} bit;
} IoMxicTdeclr;

/*	structure of trvsw		*/
typedef union _IoMxicTrvsw
{
	unsigned long word;
	struct
	{
		unsigned long trvsw :1;
		unsigned long :31;
	} bit;
} IoMxicTrvsw;

/*	structure of taen		*/
typedef union _IoMxicTaen
{
	unsigned long word;
	struct
	{
		unsigned long taen :1;
		unsigned long :31;
	} bit;
} IoMxicTaen;

/*	structure of tacptcw		*/
typedef union _IoMxicTacptcw
{
	unsigned long word[4];
	struct
	{
		unsigned long tacptcw10 :5;
		unsigned long :3;
		unsigned long tacptcw11 :5;
		unsigned long :3;
		unsigned long tacptcw12 :5;
		unsigned long :3;
		unsigned long tacptcw13 :5;
		unsigned long :3;
		unsigned long tacptcw20 :5;
		unsigned long :3;
		unsigned long tacptcw21 :5;
		unsigned long :3;
		unsigned long tacptcw22 :5;
		unsigned long :3;
		unsigned long tacptcw23 :5;
		unsigned long :3;
		unsigned long tacptcw30 :5;
		unsigned long :3;
		unsigned long tacptcw31 :5;
		unsigned long :3;
		unsigned long tacptcw32 :5;
		unsigned long :3;
		unsigned long tacptcw33 :5;
		unsigned long :3;
		unsigned long tacptcw40 :5;
		unsigned long :3;
		unsigned long tacptcw41 :5;
		unsigned long :3;
		unsigned long tacptcw42 :5;
		unsigned long :3;
		unsigned long tacptcw43 :5;
		unsigned long :3;
	} bit;
} IoMxicTacptcw;

/*	structure of tacptcr		*/
typedef union _IoMxicTacptcr
{
	unsigned long word[4];
	struct
	{
		unsigned long tacptcr10 :5;
		unsigned long :3;
		unsigned long tacptcr11 :5;
		unsigned long :3;
		unsigned long tacptcr12 :5;
		unsigned long :3;
		unsigned long tacptcr13 :5;
		unsigned long :3;
		unsigned long tacptcr20 :5;
		unsigned long :3;
		unsigned long tacptcr21 :5;
		unsigned long :3;
		unsigned long tacptcr22 :5;
		unsigned long :3;
		unsigned long tacptcr23 :5;
		unsigned long :3;
		unsigned long tacptcr30 :5;
		unsigned long :3;
		unsigned long tacptcr31 :5;
		unsigned long :3;
		unsigned long tacptcr32 :5;
		unsigned long :3;
		unsigned long tacptcr33 :5;
		unsigned long :3;
		unsigned long tacptcr40 :5;
		unsigned long :3;
		unsigned long tacptcr41 :5;
		unsigned long :3;
		unsigned long tacptcr42 :5;
		unsigned long :3;
		unsigned long tacptcr43 :5;
		unsigned long :3;
	} bit;
} IoMxicTacptcr;

/*	structure of tsmtrg		*/
typedef union _IoMxicTsmtrg
{
	unsigned long word;
	struct
	{
		unsigned long tsmtrg :1;
		unsigned long :31;
	} bit;
} IoMxicTsmtrg;

/*	structure of tregion	*/
typedef union _IoMxicTregion
{
	unsigned long word[2];
	struct
	{
		unsigned long tsize :32;
		unsigned long tstad :32;
	} bit;
} IoMxicTregion;

/*	structure of tsasetw	*/
typedef union _IoMxicTsasetw
{
	unsigned long word[10];
	struct
	{
		unsigned long tsatrgw :2;
		unsigned long :30;
		unsigned long :32;
		unsigned long tsamasw471Lo :32;
		unsigned long tsamasw471Hi :16;
		unsigned long :16;
		unsigned long tsamasw12764Lo :32;
		unsigned long tsamasw12764Hi :32;
		unsigned long tsasadw :32;
		unsigned long tsaeadw :32;
		unsigned long tsarw :1;
		unsigned long :7;
		unsigned long tsamnstw :7;
		unsigned long :17;
		unsigned long tsaadstw :32;
	} bit;
} IoMxicTsasetw;

/*	structure of tmtrg		*/
typedef union _IoMxicTmtrg
{
	unsigned long word;
	struct
	{
		unsigned long tmtrg :2;
		unsigned long :30;
	} bit;
} IoMxicTmtrg;

/*	structure of tmmd		*/
typedef union _IoMxicTmmd
{
	unsigned long word;
	struct
	{
		unsigned long tmon :2;
		unsigned long :2;
		unsigned long tmoff :2;
		unsigned long :2;
		unsigned long tmup :1;
		unsigned long :3;
		unsigned long tmupc :3;
		unsigned long :1;
		unsigned long tmclr :1;
		unsigned long tmclrc :1;
		unsigned long :2;
		unsigned long tmrsel :1;
		unsigned long :3;
		unsigned long thsen :1;
		unsigned long :7;
	} bit;
} IoMxicTmmd;

/*	structure of tmontrg	*/
typedef union _IoMxicTmontrg
{
	unsigned long word;
	struct
	{
		unsigned long tontrg :1;
		unsigned long :31;
	} bit;
} IoMxicTmontrg;

/*	structure of tmuptrg	*/
typedef union _IoMxicTmuptrg
{
	unsigned long word;
	struct
	{
		unsigned long tuptrg :1;
		unsigned long :31;
	} bit;
} IoMxicTmuptrg;

/*	structure of tmlimsel		*/
typedef union _IoMxicTmlimsel
{
	unsigned long word;
	struct
	{
		unsigned long tlimsel :9;
		unsigned long :3;
		unsigned long tmalms :1;
		unsigned long :19;
	} bit;
} IoMxicTmlimsel;

/*	structure of tmlimit		*/
typedef union _IoMxicTmlimit
{
	unsigned long word;
	struct
	{
		unsigned long tmlimt :32;
	} bit;
} IoMxicTmlimit;

/*	structure of tmsel			*/
typedef union _IoMxicTmsel
{
	unsigned long word[2];
	struct
	{
		unsigned long tmsel0 :9;
		unsigned long :3;
		unsigned long tmas0 :1;
		unsigned long :3;
		unsigned long tmsel1 :9;
		unsigned long :3;
		unsigned long tmas1 :1;
		unsigned long :3;
		unsigned long tmsel2 :9;
		unsigned long :3;
		unsigned long tmas2 :1;
		unsigned long :3;
		unsigned long tmsel3 :9;
		unsigned long :3;
		unsigned long tmas3 :1;
		unsigned long :3;
	} bit;
} IoMxicTmsel;

/*	structure of tmcnt		*/
typedef union _IoMxicTmcnt
{
	unsigned long word;
	struct
	{
		unsigned long tmcnt :32;
	} bit;
} IoMxicTmcnt;

/*	structure of thstw		*/
typedef union _IoMxicThstw
{
	unsigned long word[4];
	struct
	{
		unsigned long thstw0 :7;
		unsigned long :1;
		unsigned long thstw1 :7;
		unsigned long :1;
		unsigned long thstw2 :7;
		unsigned long :1;
		unsigned long thstw3 :7;
		unsigned long :1;
		unsigned long thstw4 :7;
		unsigned long :1;
		unsigned long thstw5 :7;
		unsigned long :1;
		unsigned long thstw6 :7;
		unsigned long :1;
		unsigned long thstw7 :7;
		unsigned long :1;
		unsigned long thstw8 :7;
		unsigned long :1;
		unsigned long thstw9 :7;
		unsigned long :1;
		unsigned long thstw10 :7;
		unsigned long :1;
		unsigned long thstw11 :7;
		unsigned long :1;
		unsigned long thstw12 :7;
		unsigned long :1;
		unsigned long thstw13 :7;
		unsigned long :1;
		unsigned long thstw14 :7;
		unsigned long :1;
		unsigned long thstw15 :7;
		unsigned long :1;
	} bit;
} IoMxicThstw;

/*	structure of thstr		*/
typedef union _IoMxicThstr
{
	unsigned long word[4];
	struct
	{
		unsigned long thstr0 :7;
		unsigned long :1;
		unsigned long thstr1 :7;
		unsigned long :1;
		unsigned long thstr2 :7;
		unsigned long :1;
		unsigned long thstr3 :7;
		unsigned long :1;
		unsigned long thstr4 :7;
		unsigned long :1;
		unsigned long thstr5 :7;
		unsigned long :1;
		unsigned long thstr6 :7;
		unsigned long :1;
		unsigned long thstr7 :7;
		unsigned long :1;
		unsigned long thstr8 :7;
		unsigned long :1;
		unsigned long thstr9 :7;
		unsigned long :1;
		unsigned long thstr10 :7;
		unsigned long :1;
		unsigned long thstr11 :7;
		unsigned long :1;
		unsigned long thstr12 :7;
		unsigned long :1;
		unsigned long thstr13 :7;
		unsigned long :1;
		unsigned long thstr14 :7;
		unsigned long :1;
		unsigned long thstr15 :7;
		unsigned long :1;
	} bit;
} IoMxicThstr;

/*	structure of TMARLP_W		*/
typedef union _IoMxicTmarlpW
{
	unsigned long word;
	struct
	{
		unsigned long masPortW :2;
		unsigned long :2;
		unsigned long masLevelW :2;
		unsigned long :26;
	} bit;
} IoMxicTmarlpW;

/*	structure of TMARLP_R		*/
typedef union _IoMxicTmarlpR
{
	unsigned long word;
	struct
	{
		unsigned long masPortR :2;
		unsigned long :2;
		unsigned long masLevelR :2;
		unsigned long :26;
	} bit;
} IoMxicTmarlpR;

/*	structure of trmcw		*/
typedef union _IoMxicTrmcw
{
	unsigned long word[2];
	struct
	{
		unsigned long trmw :2;
		unsigned long :14;
		unsigned long trmcvpw :12;
		unsigned long :4;
		unsigned long trmftw :5;
		unsigned long :3;
		unsigned long trpw :4;
		unsigned long :4;
		unsigned long tisulimw :6;
		unsigned long :10;
	} bit;
} IoMxicTrmcw;

/*	structure of trmcr		*/
typedef union _IoMxicTrmcr
{
	unsigned long word[2];
	struct
	{
		unsigned long trmr :2;
		unsigned long :14;
		unsigned long trmcvpr :12;
		unsigned long :4;
		unsigned long trmftr :5;
		unsigned long :3;
		unsigned long trpr :4;
		unsigned long :4;
		unsigned long tisulimr :6;
		unsigned long :10;
	} bit;
} IoMxicTrmcr;

/*	structure of TLVLW		*/
typedef union _IoMxicTlvlw
{
	unsigned long word[3];
	struct
	{
		unsigned long lmlw :4;
		unsigned long :4;
		unsigned long lpl0w :2;
		unsigned long :6;
		unsigned long lpccl0w :6;
		unsigned long :2;
		unsigned long lpcsl0w :6;
		unsigned long :2;
		unsigned long lpl1w :2;
		unsigned long :6;
		unsigned long lpccl1w :6;
		unsigned long :2;
		unsigned long lpcsl1w :6;
		unsigned long :10;
		unsigned long lpl2w :2;
		unsigned long :6;
		unsigned long lpccl2w :6;
		unsigned long :2;
		unsigned long lpcsl2w :6;
		unsigned long :10;
	} bit;
} IoMxicTlvlw;

/*	structure of TLVLR		*/
typedef union _IoMxicTlvlr
{
	unsigned long word[3];
	struct
	{
		unsigned long lmlr :4;
		unsigned long :4;
		unsigned long lpl0r :2;
		unsigned long :6;
		unsigned long lpccl0r :6;
		unsigned long :2;
		unsigned long lpcsl0r :6;
		unsigned long :2;
		unsigned long lpl1r :2;
		unsigned long :6;
		unsigned long lpccl1r :6;
		unsigned long :2;
		unsigned long lpcsl1r :6;
		unsigned long :10;
		unsigned long lpl2r :2;
		unsigned long :6;
		unsigned long lpccl2r :6;
		unsigned long :2;
		unsigned long lpcsl2r :6;
		unsigned long :10;
	} bit;
} IoMxicTlvlr;

/*	structure of tmstw		*/
typedef union _IoMxicTmstw
{
	unsigned long word;
	struct
	{
		unsigned long tmstw1 :4;
		unsigned long :4;
		unsigned long tmstw2 :4;
		unsigned long :4;
		unsigned long tmstw3 :4;
		unsigned long :4;
		unsigned long tmstw4 :4;
		unsigned long :4;
	} bit;
} IoMxicTmstw;

/*	structure of tmstr		*/
typedef union _IoMxicTmstr
{
	unsigned long word;
	struct
	{
		unsigned long tmstr1 :4;
		unsigned long :4;
		unsigned long tmstr2 :4;
		unsigned long :4;
		unsigned long tmstr3 :4;
		unsigned long :4;
		unsigned long tmstr4 :4;
		unsigned long :4;
	} bit;
} IoMxicTmstr;

/*	structure of TSLSW		*/
typedef union _IoMxicTslsw
{
	unsigned long word[4];
	struct
	{
		unsigned long slotsw0 :7;
		unsigned long :1;
		unsigned long slotsw1 :7;
		unsigned long :1;
		unsigned long slotsw2 :7;
		unsigned long :1;
		unsigned long slotsw3 :7;
		unsigned long :1;
		unsigned long slotsw4 :7;
		unsigned long :1;
		unsigned long slotsw5 :7;
		unsigned long :1;
		unsigned long slotsw6 :7;
		unsigned long :1;
		unsigned long slotsw7 :7;
		unsigned long :1;
		unsigned long slotsw8 :7;
		unsigned long :1;
		unsigned long slotsw9 :7;
		unsigned long :1;
		unsigned long slotsw10 :7;
		unsigned long :1;
		unsigned long slotsw11 :7;
		unsigned long :1;
		unsigned long slotsw12 :7;
		unsigned long :1;
		unsigned long slotsw13 :7;
		unsigned long :1;
		unsigned long slotsw14 :7;
		unsigned long :1;
		unsigned long slotsw15 :7;
		unsigned long :1;
	} bit;
} IoMxicTslsw;

/*	structure of TSLSR		*/
typedef union _IoMxicTslsr
{
	unsigned long word[4];
	struct
	{
		unsigned long slotsr0 :7;
		unsigned long :1;
		unsigned long slotsr1 :7;
		unsigned long :1;
		unsigned long slotsr2 :7;
		unsigned long :1;
		unsigned long slotsr3 :7;
		unsigned long :1;
		unsigned long slotsr4 :7;
		unsigned long :1;
		unsigned long slotsr5 :7;
		unsigned long :1;
		unsigned long slotsr6 :7;
		unsigned long :1;
		unsigned long slotsr7 :7;
		unsigned long :1;
		unsigned long slotsr8 :7;
		unsigned long :1;
		unsigned long slotsr9 :7;
		unsigned long :1;
		unsigned long slotsr10 :7;
		unsigned long :1;
		unsigned long slotsr11 :7;
		unsigned long :1;
		unsigned long slotsr12 :7;
		unsigned long :1;
		unsigned long slotsr13 :7;
		unsigned long :1;
		unsigned long slotsr14 :7;
		unsigned long :1;
		unsigned long slotsr15 :7;
		unsigned long :1;
	} bit;
} IoMxicTslsr;

/*	structure of tgcken		*/
typedef union _IoMxicTgcken
{
	unsigned long word;
	struct
	{
		unsigned long tgcksen :8;
		unsigned long :24;
	} bit;
} IoMxicTgcken;

/*	structure of tgcfmd		*/
typedef union _IoMxicTgcfmd
{
	unsigned long word;
	struct
	{
		unsigned long tegw0 :1;
		unsigned long tegw1 :1;
		unsigned long tegw2 :1;
		unsigned long tegw3 :1;
		unsigned long tegw4 :1;
		unsigned long tegw5 :1;
		unsigned long tegw6 :1;
		unsigned long tegw7 :1;
		unsigned long tegr0 :1;
		unsigned long tegr1 :1;
		unsigned long tegr2 :1;
		unsigned long tegr3 :1;
		unsigned long tegr4 :1;
		unsigned long tegr5 :1;
		unsigned long tegr6 :1;
		unsigned long tegr7 :1;
		unsigned long :16;
	} bit;
} IoMxicTgcfmd;

/*	structure of tgacptcw		*/
typedef union _IoMxicTgacptcw
{
	unsigned long word[4];
	struct
	{
		unsigned long tgacptcw00 :5;
		unsigned long :3;
		unsigned long tgacptcw01 :5;
		unsigned long :3;
		unsigned long tgacptcw10 :5;
		unsigned long :3;
		unsigned long tgacptcw11 :5;
		unsigned long :3;
		unsigned long tgacptcw20 :5;
		unsigned long :3;
		unsigned long tgacptcw21 :5;
		unsigned long :3;
		unsigned long tgacptcw30 :5;
		unsigned long :3;
		unsigned long tgacptcw31 :5;
		unsigned long :3;
		unsigned long tgacptcw40 :5;
		unsigned long :3;
		unsigned long tgacptcw41 :5;
		unsigned long :3;
		unsigned long tgacptcw50 :5;
		unsigned long :3;
		unsigned long tgacptcw51 :5;
		unsigned long :3;
		unsigned long tgacptcw60 :5;
		unsigned long :3;
		unsigned long tgacptcw61 :5;
		unsigned long :3;
		unsigned long tgacptcw70 :5;
		unsigned long :3;
		unsigned long tgacptcw71 :5;
		unsigned long :3;
	} bit;
} IoMxicTgacptcw;

/*	structure of tgacptcr		*/
typedef union _IoMxicTgacptcr
{
	unsigned long word[4];
	struct
	{
		unsigned long tgacptcr00 :5;
		unsigned long :3;
		unsigned long tgacptcr01 :5;
		unsigned long :3;
		unsigned long tgacptcr10 :5;
		unsigned long :3;
		unsigned long tgacptcr11 :5;
		unsigned long :3;
		unsigned long tgacptcr20 :5;
		unsigned long :3;
		unsigned long tgacptcr21 :5;
		unsigned long :3;
		unsigned long tgacptcr30 :5;
		unsigned long :3;
		unsigned long tgacptcr31 :5;
		unsigned long :3;
		unsigned long tgacptcr40 :5;
		unsigned long :3;
		unsigned long tgacptcr41 :5;
		unsigned long :3;
		unsigned long tgacptcr50 :5;
		unsigned long :3;
		unsigned long tgacptcr51 :5;
		unsigned long :3;
		unsigned long tgacptcr60 :5;
		unsigned long :3;
		unsigned long tgacptcr61 :5;
		unsigned long :3;
		unsigned long tgacptcr70 :5;
		unsigned long :3;
		unsigned long tgacptcr71 :5;
		unsigned long :3;
	} bit;
} IoMxicTgacptcr;

/*	structure of tportmw	*/
typedef union _IoMxicTportmw
{
	unsigned long word[2];
	struct
	{
		unsigned long tportmw12764Lo :32;
		unsigned long tportmw12764Hi :32;
	} bit;
} IoMxicTportmw;

/*	structure of tportmr	*/
typedef union _IoMxicTportmr
{
	unsigned long word[2];
	struct
	{
		unsigned long tportmr12764Lo :32;
		unsigned long tportmr12764Hi :32;
	} bit;
} IoMxicTportmr;

/*	structure of tgslsw		*/
typedef union _IoMxicTgslsw
{
	unsigned long word[2];
	struct
	{
		unsigned long gslotsw0 :7;
		unsigned long :1;
		unsigned long gslotsw1 :7;
		unsigned long :1;
		unsigned long gslotsw2 :7;
		unsigned long :1;
		unsigned long gslotsw3 :7;
		unsigned long :1;
		unsigned long gslotsw4 :7;
		unsigned long :1;
		unsigned long gslotsw5 :7;
		unsigned long :1;
		unsigned long gslotsw6 :7;
		unsigned long :1;
		unsigned long gslotsw7 :7;
		unsigned long :1;
	} bit;
} IoMxicTgslsw;

/*	structure of tgslsr		*/
typedef union _IoMxicTgslsr
{
	unsigned long word[2];
	struct
	{
		unsigned long gslotsr0 :7;
		unsigned long :1;
		unsigned long gslotsr1 :7;
		unsigned long :1;
		unsigned long gslotsr2 :7;
		unsigned long :1;
		unsigned long gslotsr3 :7;
		unsigned long :1;
		unsigned long gslotsr4 :7;
		unsigned long :1;
		unsigned long gslotsr5 :7;
		unsigned long :1;
		unsigned long gslotsr6 :7;
		unsigned long :1;
		unsigned long gslotsr7 :7;
		unsigned long :1;
	} bit;
} IoMxicTgslsr;

/* Define i/o mapping */
typedef struct _IoJdsmxic
{
	/* ALL 28xx_(0000 - 07FFh) */
	/* (0000 - 0003h) */
	IoMxicTmirst tmirst;
	/* (0004 - 0007h) */
	IoMxicTcken tcken;
	/* (0008 - 000Bh) */
	IoMxicTckenp tckenp;
	/* (000C - 000Fh) */
	IoMxicTmie tmie;
	/* (0010 - 0013h) */
	IoMxicTmif tmif;
	/* (0014 - 0017h) */
	unsigned char dmy0010017[0x0018 - 0x0014];
	/* (0018 - 001Fh) */
	IoMxicTdestw tdestw;
	/* (0020 - 0027h) */
	unsigned char dmy00200027[0x0028 - 0x0020];
	/* (0028 - 002Fh) */
	IoMxicTdestr tdestr;
	/* (0030 - 0033h) */
	unsigned char dmy00300033[0x0034 - 0x0030];
	/* (0034 - 0037h) */
	IoMxicTcftrg tcftrg;
	/* (0038 - 003Fh) */
	IoMxicTcfmd tcfmd;
	/* (0040 - 0043h) */
	IoMxicTdeclr tdeclr;
	/* (0044 - 0047h) */
	IoMxicTrvsw trvsw;
	/* (0048 - 005Fh) */
	unsigned char dmy0048005f[0x0060 - 0x0048];
	/* (0060 - 0063h) */
	IoMxicTaen taen;
	/* (0064 - 00FFh) */
	unsigned char dmy006400ff[0x0100 - 0x0064];
	/* (0100 - 010Fh) */
	IoMxicTacptcw tacptcw;
	/* (0110 - 011Fh) */
	IoMxicTacptcr tacptcr;
	/* (0120 - 013Fh) */
	unsigned char dmy0120013f[0x0140 - 0x0120];
	/* (0140 - 0143h) */
	IoMxicTsmtrg tsmtrg;
	/* (0144 - 015Fh) */
	unsigned char dmy0144015f[0x0160 - 0x0144];
	/* (0160 - 017Fh) */
	IoMxicTregion tregion[4];
	/* (0180 - 03FFh) */
	unsigned char dmy018003ff[0x0400 - 0x0180];
	/* (0400 - 049Fh) */
	IoMxicTsasetw tsasetw[4];
	/* (04A0 - 07FFh) */
	unsigned char dmy04a007ff[0x0800 - 0x04A0];
	/* MONITOR 28xx_(0800 - 0BFFh) */
	/* (0800 - 0803h) */
	IoMxicTmtrg tmtrg;
	/* (0804 - 0807h) */
	IoMxicTmmd tmmd;
	/* (0808 - 080Bh) */
	IoMxicTmontrg tmontrg;
	/* (080C - 080Fh) */
	IoMxicTmuptrg tmuptrg;
	/* (0810 - 0813h) */
	IoMxicTmlimsel tmlimsel;
	/* (0814 - 0817h) */
	IoMxicTmlimit tmlimit;
	/* (0818 - 081Fh) */
	IoMxicTmsel tmsel;
	/* (0820 - 082Fh) */
	IoMxicTmcnt tmcnt[4];
	/* (0830 - 08FFh) */
	unsigned char dmy083008ff[0x0900 - 0x0830];
	/* (0900 - 09FFh) */
	IoMxicThstw thstw[4][4];
	/* (0A00 - 0AFFh) */
	IoMxicThstr thstr[4][4];
	/* (0B00 - 0BFFh) */
	unsigned char dmy0b000bff[0x0C00 - 0x0B00];
	/* (0C00 - 0FFFh) */
	unsigned char dmy0c000fff[0x1000 - 0x0C00];
	/* master 28xx_(1000 - 1FFFh) */
	/* (1000 - 10FBh) */
	IoMxicTmarlpW tmarlpW1[63];
	/* (10FC - 10FFh) */
	unsigned char dmy10fc10ff[0x1100 - 0x10FC];
	/* (1100 - 11FBh) */
	IoMxicTmarlpW tmarlpW2[63];
	/* (11FC - 11FFh) */
	unsigned char dmy11fc11ff[0x1200 - 0x11FC];
	/* (1200 - 12FBh) */
	IoMxicTmarlpW tmarlpW3[63];
	/* (12FC - 12FFh) */
	unsigned char dmy12fc12ff[0x1300 - 0x12FC];
	/* (1300 - 13FBh) */
	IoMxicTmarlpW tmarlpW4[63];
	/* (13FC - 13FFh) */
	unsigned char dmy13fc13ff[0x1400 - 0x13FC];
	/* (1400 - 14FBh) */
	IoMxicTmarlpR tmarlpR1[63];
	/* (14FC - 14FFh) */
	unsigned char dmy14fc14ff[0x1500 - 0x14FC];
	/* (1500 - 15FBh) */
	IoMxicTmarlpR tmarlpR2[63];
	/* (15FC - 15FFh) */
	unsigned char dmy15fc15ff[0x1600 - 0x15FC];
	/* (1600 - 16FBh) */
	IoMxicTmarlpR tmarlpR3[63];
	/* (16FC - 16FFh) */
	unsigned char dmy16fc16ff[0x1700 - 0x16FC];
	/* (1700 - 17FBh) */
	IoMxicTmarlpR tmarlpR4[63];
	/* (17FC - 1FFFh) */
	unsigned char dmy17fc1fff[0x2000 - 0x17FC];
	/* TRMC 28xx_(2000 - 23FFh) */
	/* (2000 - 21F7h) */
	IoMxicTrmcw trmcw[63];
	/* (21F8 - 21FFh) */
	unsigned char dmy21f821ff[0x2200 - 0x21F8];
	/* (2200 - 23F7h) */
	IoMxicTrmcr trmcr[63];
	/* (23F8 - 23FFh) */
	unsigned char dmy23f823ff[0x2400 - 0x23F8];
	/* LEVEL 28xx_(2400 - 25FFh) */
	/* (2400 - 242Fh) */
	/* (2430 - 243Fh) */
	IoMxicTlvlw tlvlw1[4];
	/* (2440 - 246Fh) */
	unsigned char dmy2430243f[0x2440 - 0x2430];
	/* (2470 - 247Fh) */
	IoMxicTlvlw tlvlw2[4];
	/* (2480 - 24AFh) */
	unsigned char dmy2470247f[0x2480 - 0x2470];
	/* (24B0 - 24BFh) */
	IoMxicTlvlw tlvlw3[4];
	/* (24C0 - 24EFh) */
	unsigned char dmy24b024bf[0x24C0 - 0x24B0];
	/* (24F0 - 24FFh) */
	IoMxicTlvlw tlvlw4[4];
	/* (2500 - 252Fh) */
	unsigned char dmy24f024ff[0x2500 - 0x24F0];
	/* (2530 - 253Fh) */
	IoMxicTlvlr tlvlr1[4];
	/* (2540 - 256Fh) */
	unsigned char dmy2530253f[0x2540 - 0x2530];
	/* (2570 - 257Fh) */
	IoMxicTlvlr tlvlr2[4];
	/* (2580 - 25AFh) */
	unsigned char dmy2570257f[0x2580 - 0x2570];
	/* (25B0 - 25BFh) */
	IoMxicTlvlr tlvlr3[4];
	/* (25C0 - 25EFh) */
	unsigned char dmy25b025bf[0x25C0 - 0x25B0];
	/* (25F0 - 25FFh) */
	IoMxicTlvlr tlvlr4[4];
	/* (2600 - 26FFh) */
	unsigned char dmy25f025ff[0x2600 - 0x25F0];
	/* MASTER_statUS 28xx_(2700 - 277Fh) */
	unsigned char dmy260026ff[0x2700 - 0x2600];
	/* (2700 - 273Fh) */
	/* (2740 - 277Fh) */
	IoMxicTmstw tmstw[16];
	/* (2780 - 27FFh) */
	IoMxicTmstr tmstr[16];
	/* SLOT_statUS 28xx_(2800 - 2FFFh) */
	unsigned char dmy278027ff[0x2800 - 0x2780];
	/* (2800 - 28FFh) */
	IoMxicTslsw tslsw1[4][4];
	/* (2900 - 29FFh) */
	IoMxicTslsw tslsw2[4][4];
	/* (2A00 - 2AFFh) */
	IoMxicTslsw tslsw3[4][4];
	/* (2B00 - 2BFFh) */
	IoMxicTslsw tslsw4[4][4];
	/* (2C00 - 2CFFh) */
	IoMxicTslsr tslsr1[4][4];
	/* (2D00 - 2DFFh) */
	IoMxicTslsr tslsr2[4][4];
	/* (2E00 - 2EFFh) */
	IoMxicTslsr tslsr3[4][4];
	/* (2F00 - 2FFFh) */
	IoMxicTslsr tslsr4[4][4];
	/* GROUP_ARB 28xx_(3000 - 3FFFh) */
	/* (3000 - 3003h) */
	IoMxicTgcken tgcken;
	/* (3004 - 3007h) */
	IoMxicTgcfmd tgcfmd;
	/* (3008 - 301Fh) */
	unsigned char dmy3008301f[0x3020 - 0x3008];
	/* (3020 - 302Fh) */
	IoMxicTgacptcw tgacptcw;
	/* (3030 - 303Fh) */
	IoMxicTgacptcr tgacptcr;
	/* (3040 - 3047h) */
	IoMxicTportmw tportmw;
	/* (3048 - 304Fh) */
	IoMxicTportmr tportmr;
	/* (3050 - 33FFh) */
	unsigned char dmy305033ff[0x3400 - 0x3050];
	/* (3400 - 35FFh) */
	IoMxicTrmcw trmcwGr[64];
	/* (3600 - 37FFh) */
	IoMxicTrmcr trmcrGr[64];
	/* (3800 - 383Fh) */
	IoMxicTmstw tmstwGr[16];
	/* (3840 - 387Fh) */
	IoMxicTmstr tmstrGr[16];
	/* (3880 - 38BFh) */
	IoMxicTgslsw tgslsw[8];
	/* (38C0 - 38FFh) */
	IoMxicTgslsr tgslsr[8];
	/* (3900 - 3FFFh) */
	unsigned char dmy39003fff[0x4000 - 0x3900];
} IoJdsmxic;


extern volatile IoJdsmxicTbl IoMxic1Tbl;
extern volatile IoJdsmxicTbl IoMxic2Tbl;
extern volatile IoJdsmxicTbl IoMxic3Tbl;
extern volatile IoJdsmxic ioMxic0;
extern volatile IoJdsmxic ioMxic1;
extern volatile IoJdsmxic ioMxic2;
extern volatile IoJdsmxic ioMxic3;
extern volatile IoJdsmxic ioMxic4;
extern volatile IoJdsmxic ioMxic5;
extern volatile IoJdsmxic ioMxic6;


KConstType 			k_jdsmxic_get_type(void);
KJdsmxic* 				k_jdsmxic_new(void);


#endif/*__K_JDSMXIC_H__*/

