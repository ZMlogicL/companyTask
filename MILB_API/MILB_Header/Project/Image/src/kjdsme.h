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
	kulong word;
	struct {
		kulong cmdr :1;
		kulong :31;
	} bit;
} IoMeSreset;

/*	structure of intmode		*/
typedef union _IoMeIntmode
{
	kulong word;
	struct {
		kulong ppavalid :1;
		kulong ppbvalid :1;
		kulong ppcvalid :1;
		kulong :1;
		kulong intmode :1;
		kulong :27;
	} bit;
} IoMeIntmode;

/*	structure of intstate		*/
typedef union _IoMeIntstate
{
	kulong word;
	struct {
		kulong ppaint :1;
		kulong ppbint :1;
		kulong ppcint :1;
		kulong :29;
	} bit;
} IoMeIntstate;

/*	structure of intcntr		*/
typedef union _IoMeIntcntr
{
	kulong word;
	struct {
		kulong interval :10;
		kulong :22;
	} bit;
} IoMeIntcntr;

/*	structure of cr				*/
typedef union _IoMeCr
{
	kulong word;
	struct {
		kulong cmdr :1;
		kulong :31;
	} bit;
} IoMeCr;

/*	structure of ptcc			*/
typedef union _IoMePtcc
{
	kulong word;
	struct {
		kulong cka :1;
		kulong :31;
	} bit;
} IoMePtcc;

/*	structure of pacc			*/
typedef union _IoMePacc
{
	kulong word;
	struct {
		kulong pabtCka :1;
		kulong ckm :1;
		kulong :30;
	} bit;
} IoMePacc;

/*	structure of irqsc			*/
typedef union _IoMeIrqsc
{
	kulong word;
	struct {
		kulong __irq0 :1;
		kulong __irq1 :1;
		kulong __irq2 :1;
		kulong __irq3 :1;
		kulong __irq4 :1;
		kulong __irq5 :1;
		kulong __irq6 :1;
		kulong __irq7 :1;
		kulong __irq8 :1;
		kulong :23;
	} bit;
} IoMeIrqsc;

/*	structure of irqe			*/
typedef union _IoMeIrqe
{
	kulong word;
	struct {
		kulong irqe0 :1;
		kulong irqe1 :1;
		kulong irqe2 :1;
		kulong irqe3 :1;
		kulong irqe4 :1;
		kulong irqe5 :1;
		kulong irqe6 :1;
		kulong irqe7 :1;
		kulong irqe8 :1;
		kulong :23;
	} bit;
} IoMeIrqe;

/*	structure of mirqs			*/
typedef union _IoMeMirqs
{
	kulong word;
	struct {
		kulong irqms0 :1;
		kulong irqms1 :1;
		kulong irqms2 :1;
		kulong irqms3 :1;
		kulong irqms4 :1;
		kulong irqms5 :1;
		kulong irqms6 :1;
		kulong irqms7 :1;
		kulong irqms8 :1;
		kulong :23;
	} bit;
} IoMeMirqs;

/*	structure of pabtParamMpr		*/
typedef union IoMePabtParamMpr
{
	kulong word;
	struct {
		kulong iniMpr :4;
		kulong apMpr :2;
		kulong :26;
	} bit;
} IoMePabtParamMpr;

/*	structure of pabtParamMvr		*/
typedef union _IoMePabtParamMvr
{
	kulong word;
	struct {
		kulong iniMvr :4;
		kulong apMvr :2;
		kulong :26;
	} bit;
} IoMePabtParamMvr;

/*	structure of pabtParamMvw		*/
typedef union _IoMePabtParamMvw
{
	kulong		word;
	struct {
		kulong	iniMvw			:4;
		kulong	apMvw			:2;
		kulong					:26;
	}bit;
}IoMePabtParamMvw;

/*	structure of pabtParamPpw		*/
typedef union _IoMePabtParamPpw
{
	kulong word;
	struct {
		kulong iniPpw :4;
		kulong apPpw :2;
		kulong :26;
	} bit;
} IoMePabtParamPpw;

/*	structure of pabtParamPpr		*/
typedef union _IoMePabtParamPpr
{
	kulong word;
	struct {
		kulong iniPpr :4;
		kulong apPpr :2;
		kulong :26;
	} bit;
} IoMePabtParamPpr;

/*	structure of pabtParamPsw		*/
typedef union _IoMePabtParamPsw
{
	kulong word;
	struct {
		kulong iniPsw :4;
		kulong apPsw :2;
		kulong :26;
	} bit;
} IoMePabtParamPsw;

/*	structure of srst				*/
typedef union _IoMeSrst
{
	kulong word;
	struct {
		kulong srst :1;
		kulong :31;
	} bit;
} IoMeSrst;

/*	structure of active				*/
typedef union _IoMeActive
{
	kulong word;
	struct {
		kulong clkact :1;
		kulong ckenMode0 :1;
		kulong ckenMode1 :1;
		kulong :29;
	} bit;
} IoMeActive;

/*	structure of state				*/
typedef union _IoMeState
{
	kulong word;
	struct {
		kulong :1;
		kulong me1State :3;
		kulong :28;
	} bit;
} IoMeState;

/*	structure of MBNUMH/V				*/
typedef union _IoMeMbnum
{
	kulong word[2];
	struct {
		kulong h :9;
		kulong :23;
		kulong v :8;
		kulong :24;
	} bit;
} IoMeMbnum;

/*	structure of inputmode			*/
typedef union _IoMeInputmode
{
	kulong word;
	struct {
		kulong inputmode :1;
		kulong :6;
		kulong refTxb :1;
		kulong :24;
	} bit;
} IoMeInputmode;

/*	structure of outlimit			*/
typedef union _IoMeOutlimit
{
	kulong word;
	struct {
		kulong limit :2;
		kulong :30;
	} bit;
} IoMeOutlimit;

/*	structure of QMBADRH/V			*/
typedef union _IoMeQmbadr
{
	kulong word[2];
	struct {
		kulong h :8;
		kulong :24;
		kulong v :7;
		kulong :25;
	} bit;
} IoMeQmbadr;

/*	structure of m1banknum			*/
typedef union _IoMeM1banknum
{
	kulong word;
	struct {
		kulong banknum :3;
		kulong :29;
	} bit;
} IoMeM1banknum;

/*	structure of M1ORGxMODE			*/
typedef union _IoMeM1orgmode
{
	kulong word;
	struct {
		kulong direction :1;
		kulong parity :1;
		kulong readmode :1;
		kulong sad0mode :3;
		kulong sad1mode :3;
		kulong vecmode :1;
		kulong vecsel :2;
		kulong :2;
		kulong pictype :2;
		kulong :16;
	} bit;
} IoMeM1orgmode;

/*	structure of m1start			*/
typedef union _IoMeM1start
{
	kulong word;
	struct {
		kulong :1;
		kulong m1picStr :1;
		kulong :30;
	} bit;
} IoMeM1start;

/*	structure of m1correct			*/
typedef union _IoMeM1corrct
{
	kulong word[5];
	struct {
		kulong fky :3;
		kulong bky :3;
		kulong :2;
		kulong fkx :2;
		kulong bkx :2;
		kulong mode :4;
		kulong :16;
		kulong fh :6;
		kulong :26;
		kulong fv :5;
		kulong :27;
		kulong bh :6;
		kulong :26;
		kulong bv :5;
		kulong :27;
	} bit;
} IoMeM1corrct;

/*	structure of M1MCWGHTP/B	*/
typedef union _IoMeM1mc
{
	kulong word[2];
	struct {
		kulong p :13;
		kulong :19;
		kulong b :13;
		kulong :19;
	} bit;
} IoMeM1mc;

/*	structure of m1splt					*/
typedef union _IoMeM1splt
{
	kulong word[3];
	struct {
		kulong mode :2;
		kulong :30;
		kulong th :8;
		kulong :24;
		kulong tv :8;
		kulong :24;
	} bit;
} IoMeM1splt;

/*	structure of m1skip		*/
typedef union _IoMeM1skip
{
	kulong word;
	struct {
		kulong skip :1;
		kulong :31;
	} bit;
} IoMeM1skip;

/*	structure of M1SADSUM_U/l		*/
typedef union _IoMeM1sadsum
{
	kulong word[2];
	struct {
		kulong u :12;
		kulong :20;
		kulong l :12;
		kulong :20;
	} bit;
} IoMeM1sadsum;

/*	structure of m1adjust		*/
typedef union _IoMeM1adjust
{
	kulong word;
	struct {
		kulong cycle :15;
		kulong on :1;
		kulong :16;
	} bit;
} IoMeM1adjust;

/*	structure of m1pause		*/
typedef union _IoMeM1pause
{
	kulong word;
	struct {
		kulong line :7;
		kulong :8;
		kulong on :1;
		kulong :16;
	} bit;
} IoMeM1pause;

/*	structure of M1LIMITMVx		*/
typedef union _IoMeM1limitmv
{
	kulong word;
	struct {
		kulong p :4;
		kulong :4;
		kulong m :4;
		kulong :20;
	} bit;
} IoMeM1limitmv;

/*	structure of M1LIMITMHx		*/
typedef union _IoMeM1limitmh
{
	kulong word;
	struct {
		kulong p :5;
		kulong :3;
		kulong m :5;
		kulong :19;
	} bit;
} IoMeM1limitmh;

/*	structure of M1STORGxAVRSAD			*/
typedef union _IoMeM1storgavrsad
{
	kulong word[2];
	struct {
		kulong h :12;
		kulong :20;
		kulong l :16;
		kulong :16;
	} bit;
} IoMeM1storgavrsad;

/*	structure of M1STMINxAVRSAD			*/
typedef union _IoMeM1stminavrsad
{
	kulong word[2];
	struct {
		kulong h :12;
		kulong :20;
		kulong l :16;
		kulong :16;
	} bit;
} IoMeM1stminavrsad;

/*	structure of M1ST_ORGx_VxVx			*/
typedef union _IoMeM1storgv
{
	kulong word[4];
	struct {
		kulong vxvxH :12;
		kulong :20;
		kulong vxvxL :16;
		kulong :16;
		kulong vyvyH :12;
		kulong :20;
		kulong vyvyL :16;
		kulong :16;
	} bit;
} IoMeM1storgv;

/*	structure of pmbufCtl		*/
typedef union _IoMePmbufctl
{
	kulong word;
	struct {
		kulong cmdrst :1;
		kulong :7;
		kulong thru :1;
		kulong :23;
	} bit;
} IoMePmbufctl;

/*	structure of coremode		*/
typedef union _IoMeCoremode
{
	kulong word;
	struct {
		kulong lineintv :2;
		kulong :6;
		kulong initposy :2;
		kulong :22;
	} bit;
} IoMeCoremode;

/*	structure of cncl		*/
typedef union _IoMeCncl
{
	kulong word[3];
	struct {
		kulong mode :2;
		kulong :30;
		kulong thh :8;
		kulong :24;
		kulong thl :8;
		kulong :24;
	} bit;
} IoMeCncl;

/*	structure of voutFmt		*/
typedef union _IoMeVoutfmt
{
	kulong word;
	struct {
		kulong hsize :12;
		kulong :20;
	} bit;
} IoMeVoutfmt;

/*	structure of ORGAVRx		*/
typedef union _IoMeOrgavr
{
	kulong word;
	struct {
		kulong orgavr :8;
		kulong :24;
	} bit;
} IoMeOrgavr;

/*	structure of clkenb1		*/
typedef union _IoMeClkenb1
{
	kulong word;
	struct {
		kulong :4;
		kulong m6PfmEn :1;
		kulong :27;
	} bit;
} IoMeClkenb1;

/*	structure of clkenb4		*/
typedef union _IoMeClkenb4
{
	kulong		word;
	struct {
		kulong					:4;
		kulong	m6P4mEn		:1;
		kulong					:27;
	}bit;
}IoMeClkenb4;

/*	structure of clkact1		*/
typedef union _IoMeClkact1
{
	kulong word;
	struct {
		kulong :4;
		kulong m6PfmAct :1;
		kulong :27;
	} bit;
} IoMeClkact1;

/*	structure of clkact4		*/
typedef union _IoMeClkact4
{
	kulong word;
	struct {
		kulong :4;
		kulong m6P4mAct :1;
		kulong :27;
	} bit;
} IoMeClkact4;

/*	structure of pfSize		*/
typedef union _IoMePfsize
{
	kulong word[2];
	struct {
		kulong h :13;
		kulong :19;
		kulong v :12;
		kulong :20;
	} bit;
} IoMePfsize;

/*	structure of writeState		*/
typedef union _IoMeWritestate
{
	kulong word;
	struct {
		kulong ppA :1;
		kulong ppB :1;
		kulong ppC :1;
		kulong :29;
	} bit;
} IoMeWritestate;

/*	structure of abtType		*/
typedef union _IoMeAbttype
{
	kulong word;
	struct {
		kulong abtType :1;
		kulong :31;
	} bit;
} IoMeAbttype;

/*	structure of bankTblPvec		*/
typedef union _IoMeBanktblpvec
{
	kulong word;
	struct {
		kulong fwdPvec :8;
		kulong :24;
	} bit;
} IoMeBanktblpvec;

/*	structure of bankTbl8pelref	*/
typedef union _IoMeBanktbl8pelref
{
	kulong word;
	struct {
		kulong top :8;
		kulong :24;
	} bit;
} IoMeBanktbl8pelref;

/*	structure of bankTbl8pel	*/
typedef union _IoMeBanktbl8pel
{
	kulong word;
	struct {
		kulong fwd8pel :8;
		kulong :24;
	} bit;
} IoMeBanktbl8pel;

/*	structure of pf1On	*/
typedef union _IoMePf1on
{
	kulong word;
	struct {
		kulong pf1On :1;
		kulong pfbufEn :1;
		kulong :30;
	} bit;
} IoMePf1on;

/*	structure of pf1Inisize	*/
typedef union _IoMePf1inisize
{
	kulong word;
	struct {
		kulong sizeX :8;
		kulong sizeY :6;
		kulong :18;
	} bit;
} IoMePf1inisize;

/*	structure of pf1Tbsel		*/
typedef union _IoMePf1tbsel
{
	kulong word;
	struct {
		kulong tbsel :1;
		kulong :31;
	} bit;
} IoMePf1tbsel;

/*	structure of pf1Pmenum		*/
typedef union _IoMePf1pmenum
{
	kulong word;
	struct {
		kulong pmenum :2;
		kulong :30;
	} bit;
} IoMePf1pmenum;

/*	structure of pf1Start		*/
typedef union _IoMePfstart
{
	kulong word;
	struct {
		kulong str :1;
		kulong :31;
	} bit;
} IoMePfstart;

/*	structure of pf1Clear		*/
typedef union _IoMeClear
{
	kulong word;
	struct {
		kulong clr :1;
		kulong :31;
	} bit;
} IoMeClear;

/*	structure of PF1_PB0/2_STBKNO	*/
typedef union _IoMePf1pbstbkno
{
	kulong word;
	struct {
		kulong pf1Pb0Stbkno :14;
		kulong :1;
		kulong pf1Pb0Stbknoen :1;
		kulong :16;
	} bit;
} IoMePf1pbstbkno;

/*	structure of pf1Pfb0/2		*/
typedef union _IoMePf1pfb
{
	kulong word[2];
	struct {
		kulong posx :8;
		kulong posy :8;
		kulong :16;
		kulong sizey :4;
		kulong :28;
	} bit;
} IoMePf1pfb;

/*	structure of prevsz3dnrme	*/
typedef union _IoMePrevsz3dnrme
{
	kulong word[2];
	struct {
		kulong h :11;
		kulong :21;
		kulong v :10;
		kulong :22;
	} bit;
} IoMePrevsz3dnrme;

/*	structure of mrgn3dnrme	*/
typedef union _IoMeMtgn3dnrme
{
	kulong word[2];
	struct {
		kulong h :4;
		kulong :28;
		kulong v :4;
		kulong :28;
	} bit;
} IoMeMtgn3dnrme;

/*	structure of SHIFTX/Y_3DNRME	*/
typedef union _IoMeShift3dnrme
{
	kulong word[2];
	struct {
		klong x :7;
		kulong :25;
		klong y :7;
		kulong :25;
	} bit;
} IoMeShift3dnrme;

/*	structure of cmdRst		*/
typedef union _IoMeCmdrst
{
	kulong word;
	struct {
		kulong :15;
		kulong cmdRst :1;
		kulong :16;
	} bit;
} IoMeCmdrst;

/*	structure of M1_GBO_H/l		*/
typedef union _IoMeM1gbo
{
	kulong word[2];
	struct {
		kulong h :16;
		kulong :16;
		kulong l :16;
		kulong :16;
	} bit;
} IoMeM1gbo;

/*	structure of M1_GBS_H/l		*/
typedef union _IoMeM1gbs
{
	kulong word[2];
	struct {
		kulong h :6;
		kulong :26;
		kulong l :16;
		kulong :16;
	} bit;
} IoMeM1gbs;

/*	structure of m1Glss		*/
typedef union _IoMeM1glss
{
	kulong word;
	struct {
		kulong glss :11;
		kulong :21;
	} bit;
} IoMeM1glss;

/*	structure of PREV_GBO_H/l		*/
typedef union _IoMePrevgbo
{
	kulong word[2];
	struct {
		kulong h :16;
		kulong :16;
		kulong l :16;
		kulong :16;
	} bit;
} IoMePrevgbo;

/*	structure of PREV_GBS_H/l		*/
typedef union _IoMePrevgbs
{
	kulong word[2];
	struct {
		kulong h :6;
		kulong :26;
		kulong l :16;
		kulong :16;
	} bit;
} IoMePrevgbs;

/*	structure of prevGlss		*/
typedef union _IoMePrevglss
{
	kulong word;
	struct {
		kulong glss :11;
		kulong :21;
	} bit;
} IoMePrevglss;

/*	structure of PVEC_GBO_H/l		*/
typedef union _IoMePvecgbo
{
	kulong word[2];
	struct {
		kulong h :16;
		kulong :16;
		kulong l :16;
		kulong :16;
	} bit;
} IoMePvecgbo;

/*	structure of PVEC_GBS_H/l		*/
typedef union _IoMePvecgbs
{
	kulong word[2];
	struct {
		kulong h :14;
		kulong :18;
		kulong l :16;
		kulong :16;
	} bit;
} IoMePvecgbs;

/*	structure of WBUF0			*/
typedef union _IoMeWbuf
{
	kulong word[2];
	struct {
		kulong radd :7;
		kulong :25;
		kulong wadd :7;
		kulong :25;
	} bit;
} IoMeWbuf;

/*	structure of RBUF0/1			*/
typedef union _IoMeRbuf
{
	kulong word[2];
	struct {
		kulong radd :8;
		kulong :24;
		kulong wadd :8;
		kulong :24;
	} bit;
} IoMeRbuf;

/*	structure of axiCntlSet		*/
typedef union _IoMeAxicntlset
{
	kulong word;
	struct {
		kulong arcache :4;
		kulong arprot :3;
		kulong :1;
		kulong awcache :4;
		kulong awprot :3;
		kulong :1;
		kulong :16;
	} bit;
} IoMeAxicntlset;

/*	structure of axiErrClr		*/
typedef union _IoMeAxierrclr
{
	kulong word;
	struct {
		kulong curClr :1;
		kulong :3;
		kulong preClr :1;
		kulong :3;
		kulong vecClr :1;
		kulong :23;
	} bit;
} IoMeAxierrclr;

/*	structure of axiErrClr		*/
typedef union _IoMeAxierrstatus
{
	kulong word;
	struct {
		kulong respCir :2;
		kulong curSts :1;
		kulong :1;
		kulong respPre :2;
		kulong preSts :1;
		kulong :1;
		kulong respVec :2;
		kulong vecSts :1;
		kulong :21;
	} bit;
} IoMeAxierrstatus;

/*	structure of curRdmaQuStat		*/
typedef union _IoMeCurrdmaqustat
{
	kulong word;
	struct {
		kulong curPrqbacc :2;
		kulong :2;
		kulong curRrqbacc :2;
		kulong :2;
		kulong curCrqbacc :2;
		kulong :22;
	} bit;
} IoMeCurrdmaqustat;

/*	structure of preRdmaQuStat		*/
typedef union _IoMePrerdmaqustat
{
	kulong word;
	struct {
		kulong prePrqbacc :2;
		kulong :2;
		kulong preRrqbacc :2;
		kulong :2;
		kulong preCrqbacc :2;
		kulong :22;
	} bit;
} IoMePrerdmaqustat;

/*	structure of vecWdmaQuStat		*/
typedef union _IoMeVecwdmaqustat
{
	kulong word;
	struct {
		kulong pwqbacc :2;
		kulong :2;
		kulong rwqbacc :2;
		kulong :2;
		kulong cwqbacc :2;
		kulong :22;
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
	kuchar dmy200c203f[0x2040 - 0x200C];
	/* (2040 - 2043h) */
	IoMeIrqsc irqsc;
	/* (2044 - 2047h) */
	IoMeIrqe irqe;
	/* (2048 - 204Bh) */
	IoMeMirqs mirqs;
	/* (204C - 207Fh) */
	kuchar dmy204c207f[0x2080 - 0x204C];
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
	kuchar dmy209820ff[0x2100 - 0x2098];
	/* (2100 - 27FFh) */
	kuchar dmy210027ff[0x2800 - 0x2100];
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
	kuchar dmy28182837[0x2838 - 0x2818];
	/* (2838 - 283Bh) */
	IoMeOutlimit outlimit;
	/* (283C - 283Fh) */
	kuchar dmy_283C_283F[0x2840 - 0x283C];
	/* (2840 - 2843h) */
	IoMeQmbadr qmbadr;
	/* (2844 - 2847h) */
	/* (2848 - 284Fh) */
	kuchar dmy2848284f[0x2850 - 0x2848];
	/* (2850 - 2853h) */
	IoMeM1banknum m1banknum;
	/* (2854 - 2857h) */
	IoMeM1orgmode m1orgmode[4];
	/* (2858 - 285Bh) */
	/* (285C - 285Fh) */
	/* (2860 - 2863h) */
	/* (2864 - 28FFh) */
	kuchar dmy286428ff[0x2900 - 0x2864];
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
	kuchar dmy292c2937[0x2938 - 0x292C];
	/* (2938 - 293Bh) */
	IoMeM1skip m1skip;
	/* (293C - 295Bh) */
	kuchar dmy293c295b[0x295C - 0x293C];
	/* (295C - 295Fh) */
	IoMeM1sadsum m1sadsum;
	/* (2960 - 2963h) */
	/* (2964 - 2977h) */
	kuchar dmy29642977[0x2978 - 0x2964];
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
	kuchar dmy29a029bf[0x29C0 - 0x29A0];
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
	kuchar dmy2a442a4f[0x2A50 - 0x2A44];
	/* (2A50 - 2A53h) */
	IoMeCoremode coremode;
	/* (2A54 - 2A5Fh) */
	kuchar dmy2a542a5f[0x2A60 - 0x2A54];
	/* (2A60 - 2A63h) */
	IoMeCncl cncl;
	/* (2A64 - 2A67h) */
	/* (2A68 - 2A6Bh) */
	/* (2A6C - 2A6Fh) */
	kuchar dmy2a6c2a6f[0x2A70 - 0x2A6C];
	/* (2A70 - 2A73h) */
	IoMeVoutfmt voutFmt;
	/* (2A74 - 2A7Fh) */
	kuchar dmy2a742a7f[0x2A80 - 0x2A74];
	/* (2A80 - 2A83h) */
	IoMeOrgavr orgavr[4];
	/* (2A84 - 2A87h) */
	/* (2A88 - 2A8Bh) */
	/* (2A8C - 2A8Fh) */
	/* (2A90 - 2AFFh) */
	kuchar dmy2a902aff[0x2B00 - 0x2A90];
	/* (2B00 - 3FFFh) */
	kuchar dmy2b003fff[0x4000 - 0x2B00];
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
	kuchar dmy00101fff[0x2000 - 0x0010];
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
	kuchar dmy8010801f[0x8020 - 0x8010];
	/* (8020 - 8023h) */
	IoMePfsize pfSize;
	/* (8024 - 8027h) */
	/* (8028 - 802Bh) */
	kuchar dmy8028802b[0x802C - 0x8028];
	/* (802C - 802Fh) */
	IoMeWritestate writeState;
	/* (8030 - 8033h) */
	IoMeAbttype abtType;
	/* (8034 - 80FFh) */
	kuchar dmy803480ff[0x8100 - 0x8034];
	/* (8100 - 8103h) */
	IoMeBanktblpvec bankTblPvec;
	/* (8104 - 81FFh) */
	kuchar dmy810481ff[0x8200 - 0x8104];
	/* (8200 - 8203h) */
	IoMeBanktbl8pelref bankTbl8pelref;
	/* (8204 - 8207h) */
	IoMeBanktbl8pel bankTbl8pel;
	/* (8208 - 82FFh) */
	kuchar dmy820882ff[0x8300 - 0x8208];
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
	kuchar dmy8318831b[0x831C - 0x8318];
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
	kuchar dmy83348fff[0x8400 - 0x8334];
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
	kuchar dmy841884ff[0x8500 - 0x8418];
	/* (8500 - 8503h) */
	IoMeCmdrst cmdRst;
	/* (8504 - 85FFh) */
	kuchar dmy850485ff[0x8600 - 0x8504];
	/* (8600 - 8603h) */
	IoMeM1gbo m1Gbo;
	/* (8604 - 8607h) */
	/* (8608 - 860Bh) */
	IoMeM1gbs m1Gbs;
	/* (860C - 860Fh) */
	/* (8610 - 8613h) */
	IoMeM1glss m1Glss;
	/* (8614 - 86FFh) */
	kuchar dmy861486ff[0x8700 - 0x8614];
	/* (8700 - 8703h) */
	IoMePrevgbo prevGbo;
	; /* (8704 - 8707h) */
	/* (8708 - 870Bh) */
	IoMePrevgbs prevGbs;
	/* (870C - 870Fh) */
	/* (8710 - 8713h) */
	IoMePrevglss prevGlss;
	/* (8714 - 87FFh) */
	kuchar dmy871487ff[0x8800 - 0x8714];
	/* (8800 - 8803h) */
	IoMePvecgbo pvecGbo;
	/* (8804 - 8807h) */
	/* (8808 - 880Bh) */
	IoMePvecgbs pvecGbs;
	/* (880C - 880Fh) */
	/* (8810 - 89FFh) */
	kuchar dmy881089ff[0x8A00 - 0x8810];
	/* (8A00 - 8A03h) */
	IoMeWbuf wbuf;
	/* (8A04 - 8A07h) */
	/* (8A08 - 8A0Bh) */
	IoMeRbuf rbuf[2];
	/* (8A0C - 8A0Fh) */
	/* (8A10 - 8A13h) */
	/* (8A14 - 8A17h) */
	/* (8A18 - 8BFFh) */
	kuchar dmy8a188bff[0x8C00 - 0x8A18];
	/* (8C00 - 8C03h) */
	IoMeAxicntlset axiCntlSet;
	/* (8C04 - 8C0Fh) */
	kuchar dmy8c048c0f[0x8C10 - 0x8C04];
	/* (8C10 - 8C13h) */
	IoMeAxierrclr axiErrClr;
	/* (8C14 - 8C17h) */
	IoMeAxierrstatus axiErrStatus;
	/* (8C18 - 8CFFh) */
	kuchar dmy8c188cff[0x8D00 - 0x8C18];
	/* (8D00 - 8D03h) */
	IoMeCurrdmaqustat curRdmaQuStat;
	/* (8D04 - 8D07h) */
	IoMePrerdmaqustat preRdmaQuStat;
	/* (8D08 - 8D0Bh) */
	IoMeVecwdmaqustat vecWdmaQuStat;
	/* (8D0C - 8FFFh) */
	kuchar dmy8d0c8fff[0x9000 - 0x8D0C];
	/* (9000 - 9FFFh) */
	kuchar dmy90009fff[0xA000 - 0x9000];
	/* (A000 - FFFFh) */
	kuchar dmya000ffff[0x10000 - 0xA000];
} IoJdsme;


extern volatile IoJdsme		ioMe;


KConstType	k_jdsme_get_type(void);
KJdsme*	k_jdsme_new(void);


#endif/*__K_JDSME_H__*/

