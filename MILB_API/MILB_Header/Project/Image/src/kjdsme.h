/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date              :2020-09-07
*@author            :陈倩
*@brief             :kjdsme
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


#ifndef __K_JDSME_H__
#define __K_JDSME_H__


#include <klib.h>


#define K_TYPE_JDSME					(k_jdsme_get_type())
#define K_JDSME(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsme))
#define K_IS_JDSME(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSME))


typedef struct _KJdsme				KJdsme;
typedef struct _KJdsmePrivate	KJdsmePrivate;

struct  _KJdsme
{
	KObject parent;
};


/*	structure of sreset			*/
typedef union _IoMeSreset
{
	unsigned long word;
	struct {
		unsigned long cmdr :1;
		unsigned long :31;
	} bit;
} IoMeSreset;

/*	structure of intmode		*/
typedef union _IoMeIntmode
{
	unsigned long word;
	struct {
		unsigned long ppavalid :1;
		unsigned long ppbvalid :1;
		unsigned long ppcvalid :1;
		unsigned long :1;
		unsigned long intmode :1;
		unsigned long :27;
	} bit;
} IoMeIntmode;

/*	structure of intstate		*/
typedef union _IoMeIntstate
{
	unsigned long word;
	struct {
		unsigned long ppaint :1;
		unsigned long ppbint :1;
		unsigned long ppcint :1;
		unsigned long :29;
	} bit;
} IoMeIntstate;

/*	structure of intcntr		*/
typedef union _IoMeIntcntr
{
	unsigned long word;
	struct {
		unsigned long interval :10;
		unsigned long :22;
	} bit;
} IoMeIntcntr;

/*	structure of cr				*/
typedef union _IoMeCr
{
	unsigned long word;
	struct {
		unsigned long cmdr :1;
		unsigned long :31;
	} bit;
} IoMeCr;

/*	structure of ptcc			*/
typedef union _IoMePtcc
{
	unsigned long word;
	struct {
		unsigned long cka :1;
		unsigned long :31;
	} bit;
} IoMePtcc;

/*	structure of pacc			*/
typedef union _IoMePacc
{
	unsigned long word;
	struct {
		unsigned long pabtCka :1;
		unsigned long ckm :1;
		unsigned long :30;
	} bit;
} IoMePacc;

/*	structure of irqsc			*/
typedef union _IoMeIrqsc
{
	unsigned long word;
	struct {
		unsigned long __irq0 :1;
		unsigned long __irq1 :1;
		unsigned long __irq2 :1;
		unsigned long __irq3 :1;
		unsigned long __irq4 :1;
		unsigned long __irq5 :1;
		unsigned long __irq6 :1;
		unsigned long __irq7 :1;
		unsigned long __irq8 :1;
		unsigned long :23;
	} bit;
} IoMeIrqsc;

/*	structure of irqe			*/
typedef union _IoMeIrqe
{
	unsigned long word;
	struct {
		unsigned long irqe0 :1;
		unsigned long irqe1 :1;
		unsigned long irqe2 :1;
		unsigned long irqe3 :1;
		unsigned long irqe4 :1;
		unsigned long irqe5 :1;
		unsigned long irqe6 :1;
		unsigned long irqe7 :1;
		unsigned long irqe8 :1;
		unsigned long :23;
	} bit;
} IoMeIrqe;

/*	structure of mirqs			*/
typedef union _IoMeMirqs
{
	unsigned long word;
	struct {
		unsigned long irqms0 :1;
		unsigned long irqms1 :1;
		unsigned long irqms2 :1;
		unsigned long irqms3 :1;
		unsigned long irqms4 :1;
		unsigned long irqms5 :1;
		unsigned long irqms6 :1;
		unsigned long irqms7 :1;
		unsigned long irqms8 :1;
		unsigned long :23;
	} bit;
} IoMeMirqs;

/*	structure of pabtParamMpr		*/
typedef union IoMePabtParamMpr
{
	unsigned long word;
	struct {
		unsigned long iniMpr :4;
		unsigned long apMpr :2;
		unsigned long :26;
	} bit;
} IoMePabtParamMpr;

/*	structure of pabtParamMvr		*/
typedef union _IoMePabtParamMvr
{
	unsigned long word;
	struct {
		unsigned long iniMvr :4;
		unsigned long apMvr :2;
		unsigned long :26;
	} bit;
} IoMePabtParamMvr;

/*	structure of pabtParamMvw		*/
typedef union _IoMePabtParamMvw
{
	unsigned long		word;
	struct {
		unsigned long	iniMvw			:4;
		unsigned long	apMvw			:2;
		unsigned long					:26;
	}bit;
}IoMePabtParamMvw;

/*	structure of pabtParamPpw		*/
typedef union _IoMePabtParamPpw
{
	unsigned long word;
	struct {
		unsigned long iniPpw :4;
		unsigned long apPpw :2;
		unsigned long :26;
	} bit;
} IoMePabtParamPpw;

/*	structure of pabtParamPpr		*/
typedef union _IoMePabtParamPpr
{
	unsigned long word;
	struct {
		unsigned long iniPpr :4;
		unsigned long apPpr :2;
		unsigned long :26;
	} bit;
} IoMePabtParamPpr;

/*	structure of pabtParamPsw		*/
typedef union _IoMePabtParamPsw
{
	unsigned long word;
	struct {
		unsigned long iniPsw :4;
		unsigned long apPsw :2;
		unsigned long :26;
	} bit;
} IoMePabtParamPsw;

/*	structure of srst				*/
typedef union _IoMeSrst
{
	unsigned long word;
	struct {
		unsigned long srst :1;
		unsigned long :31;
	} bit;
} IoMeSrst;

/*	structure of active				*/
typedef union _IoMeActive
{
	unsigned long word;
	struct {
		unsigned long clkact :1;
		unsigned long ckenMode0 :1;
		unsigned long ckenMode1 :1;
		unsigned long :29;
	} bit;
} IoMeActive;

/*	structure of state				*/
typedef union _IoMeState
{
	unsigned long word;
	struct {
		unsigned long :1;
		unsigned long me1State :3;
		unsigned long :28;
	} bit;
} IoMeState;

/*	structure of MBNUMH/V				*/
typedef union _IoMeMbnum
{
	unsigned long word[2];
	struct {
		unsigned long h :9;
		unsigned long :23;
		unsigned long v :8;
		unsigned long :24;
	} bit;
} IoMeMbnum;

/*	structure of inputmode			*/
typedef union _IoMeInputmode
{
	unsigned long word;
	struct {
		unsigned long inputmode :1;
		unsigned long :6;
		unsigned long refTxb :1;
		unsigned long :24;
	} bit;
} IoMeInputmode;

/*	structure of outlimit			*/
typedef union _IoMeOutlimit
{
	unsigned long word;
	struct {
		unsigned long limit :2;
		unsigned long :30;
	} bit;
} IoMeOutlimit;

/*	structure of QMBADRH/V			*/
typedef union _IoMeQmbadr
{
	unsigned long word[2];
	struct {
		unsigned long h :8;
		unsigned long :24;
		unsigned long v :7;
		unsigned long :25;
	} bit;
} IoMeQmbadr;

/*	structure of m1banknum			*/
typedef union _IoMeM1banknum
{
	unsigned long word;
	struct {
		unsigned long banknum :3;
		unsigned long :29;
	} bit;
} IoMeM1banknum;

/*	structure of M1ORGxMODE			*/
typedef union _IoMeM1orgmode
{
	unsigned long word;
	struct {
		unsigned long direction :1;
		unsigned long parity :1;
		unsigned long readmode :1;
		unsigned long sad0mode :3;
		unsigned long sad1mode :3;
		unsigned long vecmode :1;
		unsigned long vecsel :2;
		unsigned long :2;
		unsigned long pictype :2;
		unsigned long :16;
	} bit;
} IoMeM1orgmode;

/*	structure of m1start			*/
typedef union _IoMeM1start
{
	unsigned long word;
	struct {
		unsigned long :1;
		unsigned long m1picStr :1;
		unsigned long :30;
	} bit;
} IoMeM1start;

/*	structure of m1correct			*/
typedef union _IoMeM1corrct
{
	unsigned long word[5];
	struct {
		unsigned long fky :3;
		unsigned long bky :3;
		unsigned long :2;
		unsigned long fkx :2;
		unsigned long bkx :2;
		unsigned long mode :4;
		unsigned long :16;
		unsigned long fh :6;
		unsigned long :26;
		unsigned long fv :5;
		unsigned long :27;
		unsigned long bh :6;
		unsigned long :26;
		unsigned long bv :5;
		unsigned long :27;
	} bit;
} IoMeM1corrct;

/*	structure of M1MCWGHTP/B	*/
typedef union _IoMeM1mc
{
	unsigned long word[2];
	struct {
		unsigned long p :13;
		unsigned long :19;
		unsigned long b :13;
		unsigned long :19;
	} bit;
} IoMeM1mc;

/*	structure of m1splt					*/
typedef union _IoMeM1splt
{
	unsigned long word[3];
	struct {
		unsigned long mode :2;
		unsigned long :30;
		unsigned long th :8;
		unsigned long :24;
		unsigned long tv :8;
		unsigned long :24;
	} bit;
} IoMeM1splt;

/*	structure of m1skip		*/
typedef union _IoMeM1skip
{
	unsigned long word;
	struct {
		unsigned long skip :1;
		unsigned long :31;
	} bit;
} IoMeM1skip;

/*	structure of M1SADSUM_U/L		*/
typedef union _IoMeM1sadsum
{
	unsigned long word[2];
	struct {
		unsigned long u :12;
		unsigned long :20;
		unsigned long l :12;
		unsigned long :20;
	} bit;
} IoMeM1sadsum;

/*	structure of m1adjust		*/
typedef union _IoMeM1adjust
{
	unsigned long word;
	struct {
		unsigned long cycle :15;
		unsigned long on :1;
		unsigned long :16;
	} bit;
} IoMeM1adjust;

/*	structure of m1pause		*/
typedef union _IoMeM1pause
{
	unsigned long word;
	struct {
		unsigned long line :7;
		unsigned long :8;
		unsigned long on :1;
		unsigned long :16;
	} bit;
} IoMeM1pause;

/*	structure of M1LIMITMVx		*/
typedef union _IoMeM1limitmv
{
	unsigned long word;
	struct {
		unsigned long p :4;
		unsigned long :4;
		unsigned long m :4;
		unsigned long :20;
	} bit;
} IoMeM1limitmv;

/*	structure of M1LIMITMHx		*/
typedef union _IoMeM1limitmh
{
	unsigned long word;
	struct {
		unsigned long p :5;
		unsigned long :3;
		unsigned long m :5;
		unsigned long :19;
	} bit;
} IoMeM1limitmh;

/*	structure of M1STORGxAVRSAD			*/
typedef union _IoMeM1storgavrsad
{
	unsigned long word[2];
	struct {
		unsigned long h :12;
		unsigned long :20;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMeM1storgavrsad;

/*	structure of M1STMINxAVRSAD			*/
typedef union _IoMeM1stminavrsad
{
	unsigned long word[2];
	struct {
		unsigned long h :12;
		unsigned long :20;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMeM1stminavrsad;

/*	structure of M1ST_ORGx_VxVx			*/
typedef union _IoMeM1storgv
{
	unsigned long word[4];
	struct {
		unsigned long vxvxH :12;
		unsigned long :20;
		unsigned long vxvxL :16;
		unsigned long :16;
		unsigned long vyvyH :12;
		unsigned long :20;
		unsigned long vyvyL :16;
		unsigned long :16;
	} bit;
} IoMeM1storgv;

/*	structure of pmbufCtl		*/
typedef union _IoMePmbufctl
{
	unsigned long word;
	struct {
		unsigned long cmdrst :1;
		unsigned long :7;
		unsigned long thru :1;
		unsigned long :23;
	} bit;
} IoMePmbufctl;

/*	structure of coremode		*/
typedef union _IoMeCoremode
{
	unsigned long word;
	struct {
		unsigned long lineintv :2;
		unsigned long :6;
		unsigned long initposy :2;
		unsigned long :22;
	} bit;
} IoMeCoremode;

/*	structure of cncl		*/
typedef union _IoMeCncl
{
	unsigned long word[3];
	struct {
		unsigned long mode :2;
		unsigned long :30;
		unsigned long thh :8;
		unsigned long :24;
		unsigned long thl :8;
		unsigned long :24;
	} bit;
} IoMeCncl;

/*	structure of voutFmt		*/
typedef union _IoMeVoutfmt
{
	unsigned long word;
	struct {
		unsigned long hsize :12;
		unsigned long :20;
	} bit;
} IoMeVoutfmt;

/*	structure of ORGAVRx		*/
typedef union _IoMeOrgavr
{
	unsigned long word;
	struct {
		unsigned long orgavr :8;
		unsigned long :24;
	} bit;
} IoMeOrgavr;

/*	structure of clkenb1		*/
typedef union _IoMeClkenb1
{
	unsigned long word;
	struct {
		unsigned long :4;
		unsigned long m6PfmEn :1;
		unsigned long :27;
	} bit;
} IoMeClkenb1;

/*	structure of clkenb4		*/
typedef union _IoMeClkenb4
{
	unsigned long		word;
	struct {
		unsigned long					:4;
		unsigned long	m6P4mEn		:1;
		unsigned long					:27;
	}bit;
}IoMeClkenb4;

/*	structure of clkact1		*/
typedef union _IoMeClkact1
{
	unsigned long word;
	struct {
		unsigned long :4;
		unsigned long m6PfmAct :1;
		unsigned long :27;
	} bit;
} IoMeClkact1;

/*	structure of clkact4		*/
typedef union _IoMeClkact4
{
	unsigned long word;
	struct {
		unsigned long :4;
		unsigned long m6P4mAct :1;
		unsigned long :27;
	} bit;
} IoMeClkact4;

/*	structure of pfSize		*/
typedef union _IoMePfsize
{
	unsigned long word[2];
	struct {
		unsigned long h :13;
		unsigned long :19;
		unsigned long v :12;
		unsigned long :20;
	} bit;
} IoMePfsize;

/*	structure of writeState		*/
typedef union _IoMeWritestate
{
	unsigned long word;
	struct {
		unsigned long ppA :1;
		unsigned long ppB :1;
		unsigned long ppC :1;
		unsigned long :29;
	} bit;
} IoMeWritestate;

/*	structure of abtType		*/
typedef union _IoMeAbttype
{
	unsigned long word;
	struct {
		unsigned long abtType :1;
		unsigned long :31;
	} bit;
} IoMeAbttype;

/*	structure of bankTblPvec		*/
typedef union _IoMeBanktblpvec
{
	unsigned long word;
	struct {
		unsigned long fwdPvec :8;
		unsigned long :24;
	} bit;
} IoMeBanktblpvec;

/*	structure of bankTbl8pelref	*/
typedef union _IoMeBanktbl8pelref
{
	unsigned long word;
	struct {
		unsigned long top :8;
		unsigned long :24;
	} bit;
} IoMeBanktbl8pelref;

/*	structure of bankTbl8pel	*/
typedef union _IoMeBanktbl8pel
{
	unsigned long word;
	struct {
		unsigned long fwd8pel :8;
		unsigned long :24;
	} bit;
} IoMeBanktbl8pel;

/*	structure of pf1On	*/
typedef union _IoMePf1on
{
	unsigned long word;
	struct {
		unsigned long pf1On :1;
		unsigned long pfbufEn :1;
		unsigned long :30;
	} bit;
} IoMePf1on;

/*	structure of pf1Inisize	*/
typedef union _IoMePf1inisize
{
	unsigned long word;
	struct {
		unsigned long sizeX :8;
		unsigned long sizeY :6;
		unsigned long :18;
	} bit;
} IoMePf1inisize;

/*	structure of pf1Tbsel		*/
typedef union _IoMePf1tbsel
{
	unsigned long word;
	struct {
		unsigned long tbsel :1;
		unsigned long :31;
	} bit;
} IoMePf1tbsel;

/*	structure of pf1Pmenum		*/
typedef union _IoMePf1pmenum
{
	unsigned long word;
	struct {
		unsigned long pmenum :2;
		unsigned long :30;
	} bit;
} IoMePf1pmenum;

/*	structure of pf1Start		*/
typedef union _IoMePfstart
{
	unsigned long word;
	struct {
		unsigned long str :1;
		unsigned long :31;
	} bit;
} IoMePfstart;

/*	structure of pf1Clear		*/
typedef union _IoMeClear
{
	unsigned long word;
	struct {
		unsigned long clr :1;
		unsigned long :31;
	} bit;
} IoMeClear;

/*	structure of PF1_PB0/2_STBKNO	*/
typedef union _IoMePf1pbstbkno
{
	unsigned long word;
	struct {
		unsigned long pf1Pb0Stbkno :14;
		unsigned long :1;
		unsigned long pf1Pb0Stbknoen :1;
		unsigned long :16;
	} bit;
} IoMePf1pbstbkno;

/*	structure of pf1Pfb0/2		*/
typedef union _IoMePf1pfb
{
	unsigned long word[2];
	struct {
		unsigned long posx :8;
		unsigned long posy :8;
		unsigned long :16;
		unsigned long sizey :4;
		unsigned long :28;
	} bit;
} IoMePf1pfb;

/*	structure of prevsz3dnrme	*/
typedef union _IoMePrevsz3dnrme
{
	unsigned long word[2];
	struct {
		unsigned long h :11;
		unsigned long :21;
		unsigned long v :10;
		unsigned long :22;
	} bit;
} IoMePrevsz3dnrme;

/*	structure of mrgn3dnrme	*/
typedef union _IoMeMtgn3dnrme
{
	unsigned long word[2];
	struct {
		unsigned long h :4;
		unsigned long :28;
		unsigned long v :4;
		unsigned long :28;
	} bit;
} IoMeMtgn3dnrme;

/*	structure of SHIFTX/Y_3DNRME	*/
typedef union _IoMeShift3dnrme
{
	unsigned long word[2];
	struct {
		long x :7;
		unsigned long :25;
		long y :7;
		unsigned long :25;
	} bit;
} IoMeShift3dnrme;

/*	structure of cmdRst		*/
typedef union _IoMeCmdrst
{
	unsigned long word;
	struct {
		unsigned long :15;
		unsigned long cmdRst :1;
		unsigned long :16;
	} bit;
} IoMeCmdrst;

/*	structure of M1_GBO_H/L		*/
typedef union _IoMeM1gbo
{
	unsigned long word[2];
	struct {
		unsigned long h :16;
		unsigned long :16;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMeM1gbo;

/*	structure of M1_GBS_H/L		*/
typedef union _IoMeM1gbs
{
	unsigned long word[2];
	struct {
		unsigned long h :6;
		unsigned long :26;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMeM1gbs;

/*	structure of m1Glss		*/
typedef union _IoMeM1glss
{
	unsigned long word;
	struct {
		unsigned long glss :11;
		unsigned long :21;
	} bit;
} IoMeM1glss;

/*	structure of PREV_GBO_H/L		*/
typedef union _IoMePrevgbo
{
	unsigned long word[2];
	struct {
		unsigned long h :16;
		unsigned long :16;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMePrevgbo;

/*	structure of PREV_GBS_H/L		*/
typedef union _IoMePrevgbs
{
	unsigned long word[2];
	struct {
		unsigned long h :6;
		unsigned long :26;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMePrevgbs;

/*	structure of prevGlss		*/
typedef union _IoMePrevglss
{
	unsigned long word;
	struct {
		unsigned long glss :11;
		unsigned long :21;
	} bit;
} IoMePrevglss;

/*	structure of PVEC_GBO_H/L		*/
typedef union _IoMePvecgbo
{
	unsigned long word[2];
	struct {
		unsigned long h :16;
		unsigned long :16;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMePvecgbo;

/*	structure of PVEC_GBS_H/L		*/
typedef union _IoMePvecgbs
{
	unsigned long word[2];
	struct {
		unsigned long h :14;
		unsigned long :18;
		unsigned long l :16;
		unsigned long :16;
	} bit;
} IoMePvecgbs;

/*	structure of WBUF0			*/
typedef union _IoMeWbuf
{
	unsigned long word[2];
	struct {
		unsigned long radd :7;
		unsigned long :25;
		unsigned long wadd :7;
		unsigned long :25;
	} bit;
} IoMeWbuf;

/*	structure of RBUF0/1			*/
typedef union _IoMeRbuf
{
	unsigned long word[2];
	struct {
		unsigned long radd :8;
		unsigned long :24;
		unsigned long wadd :8;
		unsigned long :24;
	} bit;
} IoMeRbuf;

/*	structure of axiCntlSet		*/
typedef union _IoMeAxicntlset
{
	unsigned long word;
	struct {
		unsigned long arcache :4;
		unsigned long arprot :3;
		unsigned long :1;
		unsigned long awcache :4;
		unsigned long awprot :3;
		unsigned long :1;
		unsigned long :16;
	} bit;
} IoMeAxicntlset;

/*	structure of axiErrClr		*/
typedef union _IoMeAxierrclr
{
	unsigned long word;
	struct {
		unsigned long curClr :1;
		unsigned long :3;
		unsigned long preClr :1;
		unsigned long :3;
		unsigned long vecClr :1;
		unsigned long :23;
	} bit;
} IoMeAxierrclr;

/*	structure of axiErrClr		*/
typedef union _IoMeAxierrstatus
{
	unsigned long word;
	struct {
		unsigned long respCir :2;
		unsigned long curSts :1;
		unsigned long :1;
		unsigned long respPre :2;
		unsigned long preSts :1;
		unsigned long :1;
		unsigned long respVec :2;
		unsigned long vecSts :1;
		unsigned long :21;
	} bit;
} IoMeAxierrstatus;

/*	structure of curRdmaQuStat		*/
typedef union _IoMeCurrdmaqustat
{
	unsigned long word;
	struct {
		unsigned long curPrqbacc :2;
		unsigned long :2;
		unsigned long curRrqbacc :2;
		unsigned long :2;
		unsigned long curCrqbacc :2;
		unsigned long :22;
	} bit;
} IoMeCurrdmaqustat;

/*	structure of preRdmaQuStat		*/
typedef union _IoMePrerdmaqustat
{
	unsigned long word;
	struct {
		unsigned long prePrqbacc :2;
		unsigned long :2;
		unsigned long preRrqbacc :2;
		unsigned long :2;
		unsigned long preCrqbacc :2;
		unsigned long :22;
	} bit;
} IoMePrerdmaqustat;

/*	structure of vecWdmaQuStat		*/
typedef union _IoMeVecwdmaqustat
{
	unsigned long word;
	struct {
		unsigned long pwqbacc :2;
		unsigned long :2;
		unsigned long rwqbacc :2;
		unsigned long :2;
		unsigned long cwqbacc :2;
		unsigned long :22;
	} bit;
} IoMeVecwdmaqustat;

typedef struct _IoMePme
{
	// PTCNT.
	/* (2000 - 2003h) */
	IoMeCr cr;
	/* (2004 - 2007h) */
	IoMePtcc ptcc;
	/* (2008 - 200Bh) */
	IoMePacc pacc;
	/* (200C - 203Fh) */
	unsigned char dmy200c203f[0x2040 - 0x200C];
	/* (2040 - 2043h) */
	IoMeIrqsc irqsc;
	/* (2044 - 2047h) */
	IoMeIrqe irqe;
	/* (2048 - 204Bh) */
	IoMeMirqs mirqs;
	/* (204C - 207Fh) */
	unsigned char dmy204c207f[0x2080 - 0x204C];
	/* (2080 - 2083h) */
	IoMePabtParamMpr pabtParamMpr;
	/* (2084 - 2087h) */
	IoMePabtParamMvr pabtParamMvr;
	/* (2088 - 208Bh) */
	IoMePabtParamMvw pabtParamMvw;
	/* (208C - 208Fh) */
	IoMePabtParamPpw pabtParamPpw;
	/* (2090 - 2093h) */
	IoMePabtParamPpr pabtParamPpr;
	/* (2094 - 2097h) */
	IoMePabtParamPsw pabtParamPsw;
	/* (2098 - 20FFh) */
	unsigned char dmy209820ff[0x2100 - 0x2098];
	/* (2100 - 27FFh) */
	unsigned char dmy210027ff[0x2800 - 0x2100];
	// pme.
	/* (2800 - 2803h) */
	IoMeSrst srst;
	/* (2804 - 2807h) */
	IoMeActive active;
	/* (2808 - 280Bh) */
	IoMeState state;
	/* (280C - 280Fh) */
	/* (2810 - 2813h) */
	IoMeMbnum mbnum;
	/* (2814 - 2817h) */
	IoMeInputmode inputmode;
	/* (2818 - 2837h) */
	unsigned char dmy28182837[0x2838 - 0x2818];
	/* (2838 - 283Bh) */
	IoMeOutlimit outlimit;
	/* (283C - 283Fh) */
	unsigned char dmy_283C_283F[0x2840 - 0x283C];
	/* (2840 - 2843h) */
	IoMeQmbadr qmbadr;
	/* (2844 - 2847h) */
	/* (2848 - 284Fh) */
	unsigned char dmy2848284f[0x2850 - 0x2848];
	/* (2850 - 2853h) */
	IoMeM1banknum m1banknum;
	/* (2854 - 2857h) */
	IoMeM1orgmode m1orgmode[4];
	/* (2858 - 285Bh) */
	/* (285C - 285Fh) */
	/* (2860 - 2863h) */
	/* (2864 - 28FFh) */
	unsigned char dmy286428ff[0x2900 - 0x2864];
	/* (2900 - 2903h) */
	IoMeM1start m1start;
	/* (2904 - 2907h) */
	IoMeM1corrct m1correct;
	/* (2908 - 290Bh) */
	/* (290C - 290Fh) */
	/* (2910 - 2913h) */
	/* (2914 - 2917h) */
	/* (2918 - 291Bh) */
	IoMeM1mc m1mc;
	/* (291C - 291Fh) */
	/* (2924 - 2927h) */
	IoMeM1splt m1splt; /* (2920 - 2923h) */
	/* (2928 - 292Bh) */
	/* (292C - 2937h) */
	unsigned char dmy292c2937[0x2938 - 0x292C];
	/* (2938 - 293Bh) */
	IoMeM1skip m1skip;
	/* (293C - 295Bh) */
	unsigned char dmy293c295b[0x295C - 0x293C];
	/* (295C - 295Fh) */
	IoMeM1sadsum m1sadsum;
	/* (2960 - 2963h) */
	/* (2964 - 2977h) */
	unsigned char dmy29642977[0x2978 - 0x2964];
	/* (2978 - 297Bh) */
	IoMeM1adjust m1adjust;
	/* (297C - 297Fh) */
	IoMeM1pause m1pause;
	/* (2980 - 2983h) */
	IoMeM1limitmv m1limitmv[4];
	/* (2984 - 2987h) */
	/* (2988 - 298Bh) */
	/* (298C - 298Fh) */
	/* (2990 - 2993h) */
	IoMeM1limitmh m1limitmh[4];
	/* (2994 - 2997h) */
	/* (2998 - 299Bh) */
	/* (299C - 299Fh) */
	/* (29A0 - 29BFh) */
	unsigned char dmy29a029bf[0x29C0 - 0x29A0];
	/* (29C0 - 29C3h) */
	/* (29C4 - 29C7h) */
	/* (29C8 - 29CBh) */
	/* (29CC - 29CFh) */
	/* (29D0 - 29D3h) */
	/* (29D4 - 29D7h) */
	/* (29D8 - 29DBh) */
	/* (29DC - 29DFh) */
	IoMeM1storgavrsad m1storgavrsad[4];
	/* (29E0 - 29E3h) */
	IoMeM1stminavrsad m1stminavrsad[4];
	/* (29E4 - 29E7h) */
	/* (29E8 - 29EBh) */
	/* (29EC - 29EFh) */
	/* (29F0 - 29F3h) */
	/* (29F4 - 29F7h) */
	/* (29F8 - 29FBh) */
	/* (29FC - 29FFh) */
	/* (2A00 - 2A03h) */
	IoMeM1storgv m1stOrgVxvx[4];
	/* (2A04 - 2A07h) */
	/* (2A08 - 2A0Bh) */
	/* (2A0C - 2A0Fh) */
	/* (2A10 - 2A13h) */
	/* (2A14 - 2A17h) */
	/* (2A18 - 2A1Bh) */
	/* (2A1C - 2A1Fh) */
	/* (2A20 - 2A23h) */
	/* (2A24 - 2A27h) */
	/* (2A28 - 2A2Bh) */
	/* (2A2C - 2A2Fh) */
	/* (2A30 - 2A33h) */
	/* (2A34 - 2A37h) */
	/* (2A38 - 2A3Bh) */
	/* (2A3C - 2A3Fh) */
	/* (2A40 - 2A43h) */
	IoMePmbufctl pmbufCtl;
	/* (2A44 - 2A4Fh) */
	unsigned char dmy2a442a4f[0x2A50 - 0x2A44];
	/* (2A50 - 2A53h) */
	IoMeCoremode coremode;
	/* (2A54 - 2A5Fh) */
	unsigned char dmy2a542a5f[0x2A60 - 0x2A54];
	/* (2A60 - 2A63h) */
	IoMeCncl cncl;
	/* (2A64 - 2A67h) */
	/* (2A68 - 2A6Bh) */
	/* (2A6C - 2A6Fh) */
	unsigned char dmy2a6c2a6f[0x2A70 - 0x2A6C];
	/* (2A70 - 2A73h) */
	IoMeVoutfmt voutFmt;
	/* (2A74 - 2A7Fh) */
	unsigned char dmy2a742a7f[0x2A80 - 0x2A74];
	/* (2A80 - 2A83h) */
	IoMeOrgavr orgavr[4];
	/* (2A84 - 2A87h) */
	/* (2A88 - 2A8Bh) */
	/* (2A8C - 2A8Fh) */
	/* (2A90 - 2AFFh) */
	unsigned char dmy2a902aff[0x2B00 - 0x2A90];
	/* (2B00 - 3FFFh) */
	unsigned char dmy2b003fff[0x4000 - 0x2B00];
} IoMePme;

/* Define i/o mapping */
typedef struct _IoJdsme
{
	// APBBRG.
	/* (0000 - 0003h) */
	IoMeSreset sreset;
	/* (0004 - 0007h) */
	IoMeIntmode intmode;
	/* (0008 - 000Bh) */
	IoMeIntstate intstate;
	/* (000C - 000Fh) */
	IoMeIntcntr intcntr;
	/* (0010 - 1FFFh) */
	unsigned char dmy00101fff[0x2000 - 0x0010];
	// PPA pme 0/1/2.
	/* (2000 - 3FFFh) */
	IoMePme pme[3];
	/* (2000 - 3FFFh) */
	/* (4000 - 5FFFh) */
	/* (6000 - 7FFFh) */
	// RMCIF.
	/* (8000 - 8003h) */
	IoMeClkenb1 clkenb1;
	/* (8004 - 8007h) */
	IoMeClkenb4 clkenb4;
	/* (8008 - 800Bh) */
	IoMeClkact1 clkact1;
	/* (800C - 800Fh) */
	IoMeClkact4 clkact4;
	/* (8010 - 801Fh) */
	unsigned char dmy8010801f[0x8020 - 0x8010];
	/* (8020 - 8023h) */
	IoMePfsize pfSize;
	/* (8024 - 8027h) */
	/* (8028 - 802Bh) */
	unsigned char dmy8028802b[0x802C - 0x8028];
	/* (802C - 802Fh) */
	IoMeWritestate writeState;
	/* (8030 - 8033h) */
	IoMeAbttype abtType;
	/* (8034 - 80FFh) */
	unsigned char dmy803480ff[0x8100 - 0x8034];
	/* (8100 - 8103h) */
	IoMeBanktblpvec bankTblPvec;
	/* (8104 - 81FFh) */
	unsigned char dmy810481ff[0x8200 - 0x8104];
	/* (8200 - 8203h) */
	IoMeBanktbl8pelref bankTbl8pelref;
	/* (8204 - 8207h) */
	IoMeBanktbl8pel bankTbl8pel;
	/* (8208 - 82FFh) */
	unsigned char dmy820882ff[0x8300 - 0x8208];
	/* (8300 - 8303h) */
	IoMePf1on pf1On;
	/* (8304 - 8307h) */
	IoMePf1inisize pf1Inisize;
	/* (8308 - 830Bh) */
	IoMePf1tbsel pf1Tbsel;
	/* (830C - 830Fh) */
	IoMePf1pmenum pf1Pmenum;
	/* (8310 - 8313h) */
	IoMePfstart pf1Start;
	/* (8314 - 8317h) */
	IoMeClear pf1Clear;
	/* (8318 - 831Bh) */
	unsigned char dmy8318831b[0x831C - 0x8318];
	/* (831C - 831Fh) */
	IoMePf1pbstbkno pf1Pb0Stbkno;
	/* (8320 - 8323h) */
	IoMePf1pbstbkno pf1Pb2Stbkno;
	/* (8324 - 8327h) */
	IoMePf1pfb pf1Pfb0;
	/* (8328 - 832Bh) */
	/* (832C - 832Fh) */
	IoMePf1pfb pf1Pfb2;
	/* (8330 - 8333h) */
	/* (8334 - 83FFh) */
	unsigned char dmy83348fff[0x8400 - 0x8334];
	/* (8400 - 8403h) */
	IoMePrevsz3dnrme prevsz3dnrme;
	/* (8404 - 8407h) */
	/* (8408 - 840Bh) */
	IoMeMtgn3dnrme mrgn3dnrme;
	/* (840C - 840Fh) */
	/* (8410 - 8413h) */
	IoMeShift3dnrme shift3dnrme;
	/* (8414 - 8417h) */
	/* (8418 - 84FFh) */
	unsigned char dmy841884ff[0x8500 - 0x8418];
	/* (8500 - 8503h) */
	IoMeCmdrst cmdRst;
	/* (8504 - 85FFh) */
	unsigned char dmy850485ff[0x8600 - 0x8504];
	/* (8600 - 8603h) */
	IoMeM1gbo m1Gbo;
	/* (8604 - 8607h) */
	/* (8608 - 860Bh) */
	IoMeM1gbs m1Gbs;
	/* (860C - 860Fh) */
	/* (8610 - 8613h) */
	IoMeM1glss m1Glss;
	/* (8614 - 86FFh) */
	unsigned char dmy861486ff[0x8700 - 0x8614];
	/* (8700 - 8703h) */
	IoMePrevgbo prevGbo;
	; /* (8704 - 8707h) */
	/* (8708 - 870Bh) */
	IoMePrevgbs prevGbs;
	/* (870C - 870Fh) */
	/* (8710 - 8713h) */
	IoMePrevglss prevGlss;
	/* (8714 - 87FFh) */
	unsigned char dmy871487ff[0x8800 - 0x8714];
	/* (8800 - 8803h) */
	IoMePvecgbo pvecGbo;
	/* (8804 - 8807h) */
	/* (8808 - 880Bh) */
	IoMePvecgbs pvecGbs;
	/* (880C - 880Fh) */
	/* (8810 - 89FFh) */
	unsigned char dmy881089ff[0x8A00 - 0x8810];
	/* (8A00 - 8A03h) */
	IoMeWbuf wbuf;
	/* (8A04 - 8A07h) */
	/* (8A08 - 8A0Bh) */
	IoMeRbuf rbuf[2];
	/* (8A0C - 8A0Fh) */
	/* (8A10 - 8A13h) */
	/* (8A14 - 8A17h) */
	/* (8A18 - 8BFFh) */
	unsigned char dmy8a188bff[0x8C00 - 0x8A18];
	/* (8C00 - 8C03h) */
	IoMeAxicntlset axiCntlSet;
	/* (8C04 - 8C0Fh) */
	unsigned char dmy8c048c0f[0x8C10 - 0x8C04];
	/* (8C10 - 8C13h) */
	IoMeAxierrclr axiErrClr;
	/* (8C14 - 8C17h) */
	IoMeAxierrstatus axiErrStatus;
	/* (8C18 - 8CFFh) */
	unsigned char dmy8c188cff[0x8D00 - 0x8C18];
	/* (8D00 - 8D03h) */
	IoMeCurrdmaqustat curRdmaQuStat;
	/* (8D04 - 8D07h) */
	IoMePrerdmaqustat preRdmaQuStat;
	/* (8D08 - 8D0Bh) */
	IoMeVecwdmaqustat vecWdmaQuStat;
	/* (8D0C - 8FFFh) */
	unsigned char dmy8d0c8fff[0x9000 - 0x8D0C];
	/* (9000 - 9FFFh) */
	unsigned char dmy90009fff[0xA000 - 0x9000];
	/* (A000 - FFFFh) */
	unsigned char dmya000ffff[0x10000 - 0xA000];
} IoJdsme;

extern volatile IoJdsme		ioMe;


KConstType	k_jdsme_get_type(void);
KJdsme*	k_jdsme_new(void);


#endif/*__K_JDSME_H__*/

