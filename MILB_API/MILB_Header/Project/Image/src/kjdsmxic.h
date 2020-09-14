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
	kulong word;
	struct
	{
		kulong tckenp1 :4;
		kulong :4;
		kulong tckenp2 :4;
		kulong :4;
		kulong tckenp3 :4;
		kulong :4;
		kulong tckenp4 :4;
		kulong :4;
	} bit;
} IoMxicTckenp;

/*	structure of tmie		*/
typedef union _IoMxicTmie
{
	kulong word;
	struct
	{
		kulong tce :1;
		kulong tme :1;
		kulong tdewe :1;
		kulong tdere :1;
		kulong tsawe :1;
		kulong :27;
	} bit;
} IoMxicTmie;

/*	structure of tmif		*/
typedef union _IoMxicTmif
{
	kulong word;
	struct
	{
		kulong __tcf :1;
		kulong __tmf :1;
		kulong __tdewf :1;
		kulong __tderf :1;
		kulong __tsawf :1;
		kulong :27;
	} bit;
} IoMxicTmif;

/*	structure of tdestw		*/
typedef union _IoMxicTdestw
{
	kulong word[2];
	struct
	{
		kulong tdemnw :7;
		kulong :25;
		kulong tdeadw :32;
	} bit;
} IoMxicTdestw;

/*	structure of tdestr		*/
typedef union _IoMxicTdestr
{
	kulong word[2];
	struct
	{
		kulong tdemnr :7;
		kulong :25;
		kulong tdeadr :32;
	} bit;
} IoMxicTdestr;

/*	structure of tcftrg		*/
typedef union _IoMxicTcftrg
{
	kulong word;
	struct
	{
		kulong tcftrg :1;
		kulong :31;
	} bit;
} IoMxicTcftrg;

/*	structure of tcfmd		*/
typedef union _IoMxicTcfmd
{
	kulong word[2];
	struct
	{
		kulong tcflg :1;
		kulong :7;
		kulong tenw1 :4;
		kulong tenw2 :4;
		kulong tenw3 :4;
		kulong tenw4 :4;
		kulong tenr1 :4;
		kulong tenr2 :4;
		kulong tenr3 :4;
		kulong tenr4 :4;
		kulong :24;
	} bit;
} IoMxicTcfmd;

/*	structure of tdeclr		*/
typedef union _IoMxicTdeclr
{
	kulong word;
	struct
	{
		kulong tdeclr :1;
		kulong :31;
	} bit;
} IoMxicTdeclr;

/*	structure of trvsw		*/
typedef union _IoMxicTrvsw
{
	kulong word;
	struct
	{
		kulong trvsw :1;
		kulong :31;
	} bit;
} IoMxicTrvsw;

/*	structure of taen		*/
typedef union _IoMxicTaen
{
	kulong word;
	struct
	{
		kulong taen :1;
		kulong :31;
	} bit;
} IoMxicTaen;

/*	structure of tacptcw		*/
typedef union _IoMxicTacptcw
{
	kulong word[4];
	struct
	{
		kulong tacptcw10 :5;
		kulong :3;
		kulong tacptcw11 :5;
		kulong :3;
		kulong tacptcw12 :5;
		kulong :3;
		kulong tacptcw13 :5;
		kulong :3;
		kulong tacptcw20 :5;
		kulong :3;
		kulong tacptcw21 :5;
		kulong :3;
		kulong tacptcw22 :5;
		kulong :3;
		kulong tacptcw23 :5;
		kulong :3;
		kulong tacptcw30 :5;
		kulong :3;
		kulong tacptcw31 :5;
		kulong :3;
		kulong tacptcw32 :5;
		kulong :3;
		kulong tacptcw33 :5;
		kulong :3;
		kulong tacptcw40 :5;
		kulong :3;
		kulong tacptcw41 :5;
		kulong :3;
		kulong tacptcw42 :5;
		kulong :3;
		kulong tacptcw43 :5;
		kulong :3;
	} bit;
} IoMxicTacptcw;

/*	structure of tacptcr		*/
typedef union _IoMxicTacptcr
{
	kulong word[4];
	struct
	{
		kulong tacptcr10 :5;
		kulong :3;
		kulong tacptcr11 :5;
		kulong :3;
		kulong tacptcr12 :5;
		kulong :3;
		kulong tacptcr13 :5;
		kulong :3;
		kulong tacptcr20 :5;
		kulong :3;
		kulong tacptcr21 :5;
		kulong :3;
		kulong tacptcr22 :5;
		kulong :3;
		kulong tacptcr23 :5;
		kulong :3;
		kulong tacptcr30 :5;
		kulong :3;
		kulong tacptcr31 :5;
		kulong :3;
		kulong tacptcr32 :5;
		kulong :3;
		kulong tacptcr33 :5;
		kulong :3;
		kulong tacptcr40 :5;
		kulong :3;
		kulong tacptcr41 :5;
		kulong :3;
		kulong tacptcr42 :5;
		kulong :3;
		kulong tacptcr43 :5;
		kulong :3;
	} bit;
} IoMxicTacptcr;

/*	structure of tsmtrg		*/
typedef union _IoMxicTsmtrg
{
	kulong word;
	struct
	{
		kulong tsmtrg :1;
		kulong :31;
	} bit;
} IoMxicTsmtrg;

/*	structure of tregion	*/
typedef union _IoMxicTregion
{
	kulong word[2];
	struct
	{
		kulong tsize :32;
		kulong tstad :32;
	} bit;
} IoMxicTregion;

/*	structure of tsasetw	*/
typedef union _IoMxicTsasetw
{
	kulong word[10];
	struct
	{
		kulong tsatrgw :2;
		kulong :30;
		kulong :32;
		kulong tsamasw471Lo :32;
		kulong tsamasw471Hi :16;
		kulong :16;
		kulong tsamasw12764Lo :32;
		kulong tsamasw12764Hi :32;
		kulong tsasadw :32;
		kulong tsaeadw :32;
		kulong tsarw :1;
		kulong :7;
		kulong tsamnstw :7;
		kulong :17;
		kulong tsaadstw :32;
	} bit;
} IoMxicTsasetw;

/*	structure of tmtrg		*/
typedef union _IoMxicTmtrg
{
	kulong word;
	struct
	{
		kulong tmtrg :2;
		kulong :30;
	} bit;
} IoMxicTmtrg;

/*	structure of tmmd		*/
typedef union _IoMxicTmmd
{
	kulong word;
	struct
	{
		kulong tmon :2;
		kulong :2;
		kulong tmoff :2;
		kulong :2;
		kulong tmup :1;
		kulong :3;
		kulong tmupc :3;
		kulong :1;
		kulong tmclr :1;
		kulong tmclrc :1;
		kulong :2;
		kulong tmrsel :1;
		kulong :3;
		kulong thsen :1;
		kulong :7;
	} bit;
} IoMxicTmmd;

/*	structure of tmontrg	*/
typedef union _IoMxicTmontrg
{
	kulong word;
	struct
	{
		kulong tontrg :1;
		kulong :31;
	} bit;
} IoMxicTmontrg;

/*	structure of tmuptrg	*/
typedef union _IoMxicTmuptrg
{
	kulong word;
	struct
	{
		kulong tuptrg :1;
		kulong :31;
	} bit;
} IoMxicTmuptrg;

/*	structure of tmlimsel		*/
typedef union _IoMxicTmlimsel
{
	kulong word;
	struct
	{
		kulong tlimsel :9;
		kulong :3;
		kulong tmalms :1;
		kulong :19;
	} bit;
} IoMxicTmlimsel;

/*	structure of tmlimit		*/
typedef union _IoMxicTmlimit
{
	kulong word;
	struct
	{
		kulong tmlimt :32;
	} bit;
} IoMxicTmlimit;

/*	structure of tmsel			*/
typedef union _IoMxicTmsel
{
	kulong word[2];
	struct
	{
		kulong tmsel0 :9;
		kulong :3;
		kulong tmas0 :1;
		kulong :3;
		kulong tmsel1 :9;
		kulong :3;
		kulong tmas1 :1;
		kulong :3;
		kulong tmsel2 :9;
		kulong :3;
		kulong tmas2 :1;
		kulong :3;
		kulong tmsel3 :9;
		kulong :3;
		kulong tmas3 :1;
		kulong :3;
	} bit;
} IoMxicTmsel;

/*	structure of tmcnt		*/
typedef union _IoMxicTmcnt
{
	kulong word;
	struct
	{
		kulong tmcnt :32;
	} bit;
} IoMxicTmcnt;

/*	structure of thstw		*/
typedef union _IoMxicThstw
{
	kulong word[4];
	struct
	{
		kulong thstw0 :7;
		kulong :1;
		kulong thstw1 :7;
		kulong :1;
		kulong thstw2 :7;
		kulong :1;
		kulong thstw3 :7;
		kulong :1;
		kulong thstw4 :7;
		kulong :1;
		kulong thstw5 :7;
		kulong :1;
		kulong thstw6 :7;
		kulong :1;
		kulong thstw7 :7;
		kulong :1;
		kulong thstw8 :7;
		kulong :1;
		kulong thstw9 :7;
		kulong :1;
		kulong thstw10 :7;
		kulong :1;
		kulong thstw11 :7;
		kulong :1;
		kulong thstw12 :7;
		kulong :1;
		kulong thstw13 :7;
		kulong :1;
		kulong thstw14 :7;
		kulong :1;
		kulong thstw15 :7;
		kulong :1;
	} bit;
} IoMxicThstw;

/*	structure of thstr		*/
typedef union _IoMxicThstr
{
	kulong word[4];
	struct
	{
		kulong thstr0 :7;
		kulong :1;
		kulong thstr1 :7;
		kulong :1;
		kulong thstr2 :7;
		kulong :1;
		kulong thstr3 :7;
		kulong :1;
		kulong thstr4 :7;
		kulong :1;
		kulong thstr5 :7;
		kulong :1;
		kulong thstr6 :7;
		kulong :1;
		kulong thstr7 :7;
		kulong :1;
		kulong thstr8 :7;
		kulong :1;
		kulong thstr9 :7;
		kulong :1;
		kulong thstr10 :7;
		kulong :1;
		kulong thstr11 :7;
		kulong :1;
		kulong thstr12 :7;
		kulong :1;
		kulong thstr13 :7;
		kulong :1;
		kulong thstr14 :7;
		kulong :1;
		kulong thstr15 :7;
		kulong :1;
	} bit;
} IoMxicThstr;

/*	structure of TMARLP_W		*/
typedef union _IoMxicTmarlpW
{
	kulong word;
	struct
	{
		kulong masPortW :2;
		kulong :2;
		kulong masLevelW :2;
		kulong :26;
	} bit;
} IoMxicTmarlpW;

/*	structure of TMARLP_R		*/
typedef union _IoMxicTmarlpR
{
	kulong word;
	struct
	{
		kulong masPortR :2;
		kulong :2;
		kulong masLevelR :2;
		kulong :26;
	} bit;
} IoMxicTmarlpR;

/*	structure of trmcw		*/
typedef union _IoMxicTrmcw
{
	kulong word[2];
	struct
	{
		kulong trmw :2;
		kulong :14;
		kulong trmcvpw :12;
		kulong :4;
		kulong trmftw :5;
		kulong :3;
		kulong trpw :4;
		kulong :4;
		kulong tisulimw :6;
		kulong :10;
	} bit;
} IoMxicTrmcw;

/*	structure of trmcr		*/
typedef union _IoMxicTrmcr
{
	kulong word[2];
	struct
	{
		kulong trmr :2;
		kulong :14;
		kulong trmcvpr :12;
		kulong :4;
		kulong trmftr :5;
		kulong :3;
		kulong trpr :4;
		kulong :4;
		kulong tisulimr :6;
		kulong :10;
	} bit;
} IoMxicTrmcr;

/*	structure of TLVLW		*/
typedef union _IoMxicTlvlw
{
	kulong word[3];
	struct
	{
		kulong lmlw :4;
		kulong :4;
		kulong lpl0w :2;
		kulong :6;
		kulong lpccl0w :6;
		kulong :2;
		kulong lpcsl0w :6;
		kulong :2;
		kulong lpl1w :2;
		kulong :6;
		kulong lpccl1w :6;
		kulong :2;
		kulong lpcsl1w :6;
		kulong :10;
		kulong lpl2w :2;
		kulong :6;
		kulong lpccl2w :6;
		kulong :2;
		kulong lpcsl2w :6;
		kulong :10;
	} bit;
} IoMxicTlvlw;

/*	structure of TLVLR		*/
typedef union _IoMxicTlvlr
{
	kulong word[3];
	struct
	{
		kulong lmlr :4;
		kulong :4;
		kulong lpl0r :2;
		kulong :6;
		kulong lpccl0r :6;
		kulong :2;
		kulong lpcsl0r :6;
		kulong :2;
		kulong lpl1r :2;
		kulong :6;
		kulong lpccl1r :6;
		kulong :2;
		kulong lpcsl1r :6;
		kulong :10;
		kulong lpl2r :2;
		kulong :6;
		kulong lpccl2r :6;
		kulong :2;
		kulong lpcsl2r :6;
		kulong :10;
	} bit;
} IoMxicTlvlr;

/*	structure of tmstw		*/
typedef union _IoMxicTmstw
{
	kulong word;
	struct
	{
		kulong tmstw1 :4;
		kulong :4;
		kulong tmstw2 :4;
		kulong :4;
		kulong tmstw3 :4;
		kulong :4;
		kulong tmstw4 :4;
		kulong :4;
	} bit;
} IoMxicTmstw;

/*	structure of tmstr		*/
typedef union _IoMxicTmstr
{
	kulong word;
	struct
	{
		kulong tmstr1 :4;
		kulong :4;
		kulong tmstr2 :4;
		kulong :4;
		kulong tmstr3 :4;
		kulong :4;
		kulong tmstr4 :4;
		kulong :4;
	} bit;
} IoMxicTmstr;

/*	structure of TSLSW		*/
typedef union _IoMxicTslsw
{
	kulong word[4];
	struct
	{
		kulong slotsw0 :7;
		kulong :1;
		kulong slotsw1 :7;
		kulong :1;
		kulong slotsw2 :7;
		kulong :1;
		kulong slotsw3 :7;
		kulong :1;
		kulong slotsw4 :7;
		kulong :1;
		kulong slotsw5 :7;
		kulong :1;
		kulong slotsw6 :7;
		kulong :1;
		kulong slotsw7 :7;
		kulong :1;
		kulong slotsw8 :7;
		kulong :1;
		kulong slotsw9 :7;
		kulong :1;
		kulong slotsw10 :7;
		kulong :1;
		kulong slotsw11 :7;
		kulong :1;
		kulong slotsw12 :7;
		kulong :1;
		kulong slotsw13 :7;
		kulong :1;
		kulong slotsw14 :7;
		kulong :1;
		kulong slotsw15 :7;
		kulong :1;
	} bit;
} IoMxicTslsw;

/*	structure of TSLSR		*/
typedef union _IoMxicTslsr
{
	kulong word[4];
	struct
	{
		kulong slotsr0 :7;
		kulong :1;
		kulong slotsr1 :7;
		kulong :1;
		kulong slotsr2 :7;
		kulong :1;
		kulong slotsr3 :7;
		kulong :1;
		kulong slotsr4 :7;
		kulong :1;
		kulong slotsr5 :7;
		kulong :1;
		kulong slotsr6 :7;
		kulong :1;
		kulong slotsr7 :7;
		kulong :1;
		kulong slotsr8 :7;
		kulong :1;
		kulong slotsr9 :7;
		kulong :1;
		kulong slotsr10 :7;
		kulong :1;
		kulong slotsr11 :7;
		kulong :1;
		kulong slotsr12 :7;
		kulong :1;
		kulong slotsr13 :7;
		kulong :1;
		kulong slotsr14 :7;
		kulong :1;
		kulong slotsr15 :7;
		kulong :1;
	} bit;
} IoMxicTslsr;

/*	structure of tgcken		*/
typedef union _IoMxicTgcken
{
	kulong word;
	struct
	{
		kulong tgcksen :8;
		kulong :24;
	} bit;
} IoMxicTgcken;

/*	structure of tgcfmd		*/
typedef union _IoMxicTgcfmd
{
	kulong word;
	struct
	{
		kulong tegw0 :1;
		kulong tegw1 :1;
		kulong tegw2 :1;
		kulong tegw3 :1;
		kulong tegw4 :1;
		kulong tegw5 :1;
		kulong tegw6 :1;
		kulong tegw7 :1;
		kulong tegr0 :1;
		kulong tegr1 :1;
		kulong tegr2 :1;
		kulong tegr3 :1;
		kulong tegr4 :1;
		kulong tegr5 :1;
		kulong tegr6 :1;
		kulong tegr7 :1;
		kulong :16;
	} bit;
} IoMxicTgcfmd;

/*	structure of tgacptcw		*/
typedef union _IoMxicTgacptcw
{
	kulong word[4];
	struct
	{
		kulong tgacptcw00 :5;
		kulong :3;
		kulong tgacptcw01 :5;
		kulong :3;
		kulong tgacptcw10 :5;
		kulong :3;
		kulong tgacptcw11 :5;
		kulong :3;
		kulong tgacptcw20 :5;
		kulong :3;
		kulong tgacptcw21 :5;
		kulong :3;
		kulong tgacptcw30 :5;
		kulong :3;
		kulong tgacptcw31 :5;
		kulong :3;
		kulong tgacptcw40 :5;
		kulong :3;
		kulong tgacptcw41 :5;
		kulong :3;
		kulong tgacptcw50 :5;
		kulong :3;
		kulong tgacptcw51 :5;
		kulong :3;
		kulong tgacptcw60 :5;
		kulong :3;
		kulong tgacptcw61 :5;
		kulong :3;
		kulong tgacptcw70 :5;
		kulong :3;
		kulong tgacptcw71 :5;
		kulong :3;
	} bit;
} IoMxicTgacptcw;

/*	structure of tgacptcr		*/
typedef union _IoMxicTgacptcr
{
	kulong word[4];
	struct
	{
		kulong tgacptcr00 :5;
		kulong :3;
		kulong tgacptcr01 :5;
		kulong :3;
		kulong tgacptcr10 :5;
		kulong :3;
		kulong tgacptcr11 :5;
		kulong :3;
		kulong tgacptcr20 :5;
		kulong :3;
		kulong tgacptcr21 :5;
		kulong :3;
		kulong tgacptcr30 :5;
		kulong :3;
		kulong tgacptcr31 :5;
		kulong :3;
		kulong tgacptcr40 :5;
		kulong :3;
		kulong tgacptcr41 :5;
		kulong :3;
		kulong tgacptcr50 :5;
		kulong :3;
		kulong tgacptcr51 :5;
		kulong :3;
		kulong tgacptcr60 :5;
		kulong :3;
		kulong tgacptcr61 :5;
		kulong :3;
		kulong tgacptcr70 :5;
		kulong :3;
		kulong tgacptcr71 :5;
		kulong :3;
	} bit;
} IoMxicTgacptcr;

/*	structure of tportmw	*/
typedef union _IoMxicTportmw
{
	kulong word[2];
	struct
	{
		kulong tportmw12764Lo :32;
		kulong tportmw12764Hi :32;
	} bit;
} IoMxicTportmw;

/*	structure of tportmr	*/
typedef union _IoMxicTportmr
{
	kulong word[2];
	struct
	{
		kulong tportmr12764Lo :32;
		kulong tportmr12764Hi :32;
	} bit;
} IoMxicTportmr;

/*	structure of tgslsw		*/
typedef union _IoMxicTgslsw
{
	kulong word[2];
	struct
	{
		kulong gslotsw0 :7;
		kulong :1;
		kulong gslotsw1 :7;
		kulong :1;
		kulong gslotsw2 :7;
		kulong :1;
		kulong gslotsw3 :7;
		kulong :1;
		kulong gslotsw4 :7;
		kulong :1;
		kulong gslotsw5 :7;
		kulong :1;
		kulong gslotsw6 :7;
		kulong :1;
		kulong gslotsw7 :7;
		kulong :1;
	} bit;
} IoMxicTgslsw;

/*	structure of tgslsr		*/
typedef union _IoMxicTgslsr
{
	kulong word[2];
	struct
	{
		kulong gslotsr0 :7;
		kulong :1;
		kulong gslotsr1 :7;
		kulong :1;
		kulong gslotsr2 :7;
		kulong :1;
		kulong gslotsr3 :7;
		kulong :1;
		kulong gslotsr4 :7;
		kulong :1;
		kulong gslotsr5 :7;
		kulong :1;
		kulong gslotsr6 :7;
		kulong :1;
		kulong gslotsr7 :7;
		kulong :1;
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
	kuchar dmy0010017[0x0018 - 0x0014];
	/* (0018 - 001Fh) */
	IoMxicTdestw tdestw;
	/* (0020 - 0027h) */
	kuchar dmy00200027[0x0028 - 0x0020];
	/* (0028 - 002Fh) */
	IoMxicTdestr tdestr;
	/* (0030 - 0033h) */
	kuchar dmy00300033[0x0034 - 0x0030];
	/* (0034 - 0037h) */
	IoMxicTcftrg tcftrg;
	/* (0038 - 003Fh) */
	IoMxicTcfmd tcfmd;
	/* (0040 - 0043h) */
	IoMxicTdeclr tdeclr;
	/* (0044 - 0047h) */
	IoMxicTrvsw trvsw;
	/* (0048 - 005Fh) */
	kuchar dmy0048005f[0x0060 - 0x0048];
	/* (0060 - 0063h) */
	IoMxicTaen taen;
	/* (0064 - 00FFh) */
	kuchar dmy006400ff[0x0100 - 0x0064];
	/* (0100 - 010Fh) */
	IoMxicTacptcw tacptcw;
	/* (0110 - 011Fh) */
	IoMxicTacptcr tacptcr;
	/* (0120 - 013Fh) */
	kuchar dmy0120013f[0x0140 - 0x0120];
	/* (0140 - 0143h) */
	IoMxicTsmtrg tsmtrg;
	/* (0144 - 015Fh) */
	kuchar dmy0144015f[0x0160 - 0x0144];
	/* (0160 - 017Fh) */
	IoMxicTregion tregion[4];
	/* (0180 - 03FFh) */
	kuchar dmy018003ff[0x0400 - 0x0180];
	/* (0400 - 049Fh) */
	IoMxicTsasetw tsasetw[4];
	/* (04A0 - 07FFh) */
	kuchar dmy04a007ff[0x0800 - 0x04A0];
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
	kuchar dmy083008ff[0x0900 - 0x0830];
	/* (0900 - 09FFh) */
	IoMxicThstw thstw[4][4];
	/* (0A00 - 0AFFh) */
	IoMxicThstr thstr[4][4];
	/* (0B00 - 0BFFh) */
	kuchar dmy0b000bff[0x0C00 - 0x0B00];
	/* (0C00 - 0FFFh) */
	kuchar dmy0c000fff[0x1000 - 0x0C00];
	/* master 28xx_(1000 - 1FFFh) */
	/* (1000 - 10FBh) */
	IoMxicTmarlpW tmarlpW1[63];
	/* (10FC - 10FFh) */
	kuchar dmy10fc10ff[0x1100 - 0x10FC];
	/* (1100 - 11FBh) */
	IoMxicTmarlpW tmarlpW2[63];
	/* (11FC - 11FFh) */
	kuchar dmy11fc11ff[0x1200 - 0x11FC];
	/* (1200 - 12FBh) */
	IoMxicTmarlpW tmarlpW3[63];
	/* (12FC - 12FFh) */
	kuchar dmy12fc12ff[0x1300 - 0x12FC];
	/* (1300 - 13FBh) */
	IoMxicTmarlpW tmarlpW4[63];
	/* (13FC - 13FFh) */
	kuchar dmy13fc13ff[0x1400 - 0x13FC];
	/* (1400 - 14FBh) */
	IoMxicTmarlpR tmarlpR1[63];
	/* (14FC - 14FFh) */
	kuchar dmy14fc14ff[0x1500 - 0x14FC];
	/* (1500 - 15FBh) */
	IoMxicTmarlpR tmarlpR2[63];
	/* (15FC - 15FFh) */
	kuchar dmy15fc15ff[0x1600 - 0x15FC];
	/* (1600 - 16FBh) */
	IoMxicTmarlpR tmarlpR3[63];
	/* (16FC - 16FFh) */
	kuchar dmy16fc16ff[0x1700 - 0x16FC];
	/* (1700 - 17FBh) */
	IoMxicTmarlpR tmarlpR4[63];
	/* (17FC - 1FFFh) */
	kuchar dmy17fc1fff[0x2000 - 0x17FC];
	/* TRMC 28xx_(2000 - 23FFh) */
	/* (2000 - 21F7h) */
	IoMxicTrmcw trmcw[63];
	/* (21F8 - 21FFh) */
	kuchar dmy21f821ff[0x2200 - 0x21F8];
	/* (2200 - 23F7h) */
	IoMxicTrmcr trmcr[63];
	/* (23F8 - 23FFh) */
	kuchar dmy23f823ff[0x2400 - 0x23F8];
	/* LEVEL 28xx_(2400 - 25FFh) */
	/* (2400 - 242Fh) */
	/* (2430 - 243Fh) */
	IoMxicTlvlw tlvlw1[4];
	/* (2440 - 246Fh) */
	kuchar dmy2430243f[0x2440 - 0x2430];
	/* (2470 - 247Fh) */
	IoMxicTlvlw tlvlw2[4];
	/* (2480 - 24AFh) */
	kuchar dmy2470247f[0x2480 - 0x2470];
	/* (24B0 - 24BFh) */
	IoMxicTlvlw tlvlw3[4];
	/* (24C0 - 24EFh) */
	kuchar dmy24b024bf[0x24C0 - 0x24B0];
	/* (24F0 - 24FFh) */
	IoMxicTlvlw tlvlw4[4];
	/* (2500 - 252Fh) */
	kuchar dmy24f024ff[0x2500 - 0x24F0];
	/* (2530 - 253Fh) */
	IoMxicTlvlr tlvlr1[4];
	/* (2540 - 256Fh) */
	kuchar dmy2530253f[0x2540 - 0x2530];
	/* (2570 - 257Fh) */
	IoMxicTlvlr tlvlr2[4];
	/* (2580 - 25AFh) */
	kuchar dmy2570257f[0x2580 - 0x2570];
	/* (25B0 - 25BFh) */
	IoMxicTlvlr tlvlr3[4];
	/* (25C0 - 25EFh) */
	kuchar dmy25b025bf[0x25C0 - 0x25B0];
	/* (25F0 - 25FFh) */
	IoMxicTlvlr tlvlr4[4];
	/* (2600 - 26FFh) */
	kuchar dmy25f025ff[0x2600 - 0x25F0];
	/* MASTER_statUS 28xx_(2700 - 277Fh) */
	kuchar dmy260026ff[0x2700 - 0x2600];
	/* (2700 - 273Fh) */
	/* (2740 - 277Fh) */
	IoMxicTmstw tmstw[16];
	/* (2780 - 27FFh) */
	IoMxicTmstr tmstr[16];
	/* SLOT_statUS 28xx_(2800 - 2FFFh) */
	kuchar dmy278027ff[0x2800 - 0x2780];
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
	kuchar dmy3008301f[0x3020 - 0x3008];
	/* (3020 - 302Fh) */
	IoMxicTgacptcw tgacptcw;
	/* (3030 - 303Fh) */
	IoMxicTgacptcr tgacptcr;
	/* (3040 - 3047h) */
	IoMxicTportmw tportmw;
	/* (3048 - 304Fh) */
	IoMxicTportmr tportmr;
	/* (3050 - 33FFh) */
	kuchar dmy305033ff[0x3400 - 0x3050];
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
	kuchar dmy39003fff[0x4000 - 0x3900];
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

