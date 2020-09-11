/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :陈倩
 *@brief             :audioif
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

#ifndef __AUDIO_IF_H__
#define __AUDIO_IF_H__


#include <klib.h>


#define AUDIO_TYPE_IF				(audio_if_get_type())
#define AUDIO_IF(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), AudioIf))
#define AUDIO_IS_IF(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), AUDIO_TYPE_IF))


typedef struct _AudioIf AudioIf;
typedef struct _AudioIfPrivate AudioIfPrivate;


struct _AudioIf
{
	KObject parent;
};

/*	structure of aures	*/
typedef union _IoAudioAures
{
	unsigned long word;
	struct
	{
		unsigned long auif0Rst :1;
		unsigned long auif1Rst :1;
		unsigned long auif2Rst :1;
		unsigned long auif3Rst :1;
		unsigned long auif4Rst :1;
		unsigned long auif5Rst :1;
		unsigned long :26;
	} bit;
} IoAudioAures;

/*	structure of auioe	*/
typedef union _IoAudioAuioe
{
	unsigned long word;
	struct
	{
		unsigned long auie0 :2;
		unsigned long auie1 :2;
		unsigned long auie2 :2;
		unsigned long auie3 :2;
		unsigned long auie4 :2;
		unsigned long auie5 :2;
		unsigned long :4;
		unsigned long auoe0 :2;
		unsigned long auoe1 :2;
		unsigned long auoe2 :2;
		unsigned long auoe3 :2;
		unsigned long auoe4 :2;
		unsigned long auoe5 :2;
		unsigned long :4;
	} bit;
} IoAudioAuioe;

/*	structure of aulbe	*/
typedef union _IoAudioAulbe
{
	unsigned long word;
	struct
	{
		unsigned long aulbe0 :2;
		unsigned long aulbe1 :2;
		unsigned long aulbe2 :2;
		unsigned long aulbe3 :2;
		unsigned long aulbe4 :2;
		unsigned long aulbe5 :2;
		unsigned long :20;
	} bit;
} IoAudioAulbe;

/*	structure of aucr	*/
typedef union _IoAudioAucr
{
	unsigned long word;
	struct
	{
		unsigned long auidsel :1;
		unsigned long auodsel :1;
		unsigned long :6;
		unsigned long inti :1;
		unsigned long into :1;
		unsigned long intie :1;
		unsigned long intoe :1;
		unsigned long auief :1;
		unsigned long auoef :1;
		unsigned long dmie :1;
		unsigned long dmoe :1;
		unsigned long auif :4;
		unsigned long :3;
		unsigned long auirf :1;
		unsigned long auof :7;
		unsigned long auorf :1;
	} bit;
} IoAudioAucr;

/*	structure of aumd	*/
typedef union _IoAudioAumd
{
	unsigned long word;
	struct
	{
		unsigned long :16;
		unsigned long ibyteSwp :1;
		unsigned long ihwSwp :1;
		unsigned long obyteSwp :1;
		unsigned long ohwSwp :1;
		unsigned long :4;
		unsigned long istg16 :1;
		unsigned long ostg16 :1;
		unsigned long :1;
		unsigned long stereo :1;
		unsigned long :3;
		unsigned long lbf :1;
	} bit;
} IoAudioAumd;

/*	structure of aust	*/
typedef union _IoAudioAust
{
	unsigned long word;
	struct
	{
		unsigned long :16;
		unsigned long irof :1;
		unsigned long oruf :1;
		unsigned long ofie :1;
		unsigned long ufie :1;
		unsigned long :4;
		unsigned long einti :1;
		unsigned long einto :1;
		unsigned long eintie :1;
		unsigned long eintoe :1;
		unsigned long edmie :1;
		unsigned long edmoe :1;
		unsigned long estg :2;
	} bit;
} IoAudioAust;

/*	structure of aucc	*/
typedef union _IoAudioAucc
{
	unsigned long word;
	struct
	{
		unsigned long :16;
		unsigned long divlr :2;
		unsigned long divck :3;
		unsigned long :3;
		unsigned long divmck :5;
		unsigned long :1;
		unsigned long dive :1;
		unsigned long auckoe :1;
	} bit;
} IoAudioAucc;

/*	structure of audp	*/
typedef union _IoAudioAudp
{
	unsigned long word;
	struct
	{
		unsigned long mixplay :1;
		unsigned long :7;
		unsigned long aulrcp :1;
		unsigned long :7;
		unsigned long auidf :1;
		unsigned long auodf :1;
		unsigned long :6;
		unsigned long auods :2;
		unsigned long :2;
		unsigned long auids :2;
		unsigned long :2;
	} bit;
} IoAudioAudp;

/*	structure of auifst	*/
typedef union _IoAudioAuifst
{
	unsigned long word;
	struct
	{
		unsigned long auisl0 :1;
		unsigned long auisr0 :1;
		unsigned long auisl1 :1;
		unsigned long auisr1 :1;
		unsigned long auisl2 :1;
		unsigned long auisr2 :1;
		unsigned long auisl3 :1;
		unsigned long auisr3 :1;
		unsigned long auisl4 :1;
		unsigned long auisr4 :1;
		unsigned long auisl5 :1;
		unsigned long auisr5 :1;
		unsigned long auisl6 :1;
		unsigned long auisr6 :1;
		unsigned long auisl7 :1;
		unsigned long auisr7 :1;
		unsigned long auisl8 :1;
		unsigned long auisr8 :1;
		unsigned long auisl9 :1;
		unsigned long auisr9 :1;
		unsigned long auisl10 :1;
		unsigned long auisr10 :1;
		unsigned long auisl11 :1;
		unsigned long auisr11 :1;
		unsigned long auisl12 :1;
		unsigned long auisr12 :1;
		unsigned long auisl13 :1;
		unsigned long auisr13 :1;
		unsigned long auisl14 :1;
		unsigned long auisr14 :1;
		unsigned long auisl15 :1;
		unsigned long auisr15 :1;
	} bit;
} IoAudioAuifst;

/*	structure of auofst	*/
typedef union _IoAudioAuofst
{
	unsigned long word;
	struct
	{
		unsigned long auosl0 :1;
		unsigned long auosr0 :1;
		unsigned long auosl1 :1;
		unsigned long auosr1 :1;
		unsigned long auosl2 :1;
		unsigned long auosr2 :1;
		unsigned long auosl3 :1;
		unsigned long auosr3 :1;
		unsigned long auosl4 :1;
		unsigned long auosr4 :1;
		unsigned long auosl5 :1;
		unsigned long auosr5 :1;
		unsigned long auosl6 :1;
		unsigned long auosr6 :1;
		unsigned long auosl7 :1;
		unsigned long auosr7 :1;
		unsigned long auosl8 :1;
		unsigned long auosr8 :1;
		unsigned long auosl9 :1;
		unsigned long auosr9 :1;
		unsigned long auosl10 :1;
		unsigned long auosr10 :1;
		unsigned long auosl11 :1;
		unsigned long auosr11 :1;
		unsigned long auosl12 :1;
		unsigned long auosr12 :1;
		unsigned long auosl13 :1;
		unsigned long auosr13 :1;
		unsigned long auosl14 :1;
		unsigned long auosr14 :1;
		unsigned long auosl15 :1;
		unsigned long auosr15 :1;
	} bit;
} IoAudioAuofst;

/*	structure of audma2ctl	*/
typedef union _IoAudioAudma2ctl
{
	unsigned long word;
	struct
	{
		unsigned long dmi2chen :1;
		unsigned long :7;
		unsigned long dmo2chen :1;
		unsigned long :23;
	} bit;
} IoAudioAudma2ctl;

/*	structure of audmisample	*/
typedef union _IoAudioAudmisample
{
	unsigned long word;
	struct
	{
		unsigned long dmispl :16;
		unsigned long :16;
	} bit;
} IoAudioAudmisample;

/*	structure of audmosample	*/
typedef union _IoAudioAudmosample
{
	unsigned long word;
	struct
	{
		unsigned long dmospl :16;
		unsigned long :16;
	} bit;
} IoAudioAudmosample;

/* AudioIF Control	(1E20_(0000 - 0FFh)*/
typedef struct _IoAudioifctrl
{
	/* 1E20_(0000 - 0003h)	*/
	IoAudioAures aures;
	/* 1E20_(0004 - 0007h)	*/
	unsigned char dmy1e2000041e200007[0x1E200008 - 0x1E200004];
	/* 1E20_(0008 - 000Bh)	*/
	unsigned char dmy1e2000081e20000b[0x1E20000C - 0x1E200008];
	/* 1E20_(000C - 000Fh)	*/
	IoAudioAuioe auioe;
	/* 1E20_(0010 - 0013h)	*/
	unsigned char dmy1e2000101e200013[0x1E200014 - 0x1E200010];
	/* 1E20_(0014 - 0017h)	*/
	IoAudioAulbe aulbe;
	/* 1E20_(0018 - 00FFh)	*/
	unsigned char dmy1e2000181e2000ff[0x1E200100 - 0x1E200018];
} IoAudioifctrl;

/* AudioIF ch0	(1E20_(0100 - 1FFh)*/
/* AudioIF ch1	(1E20_(0200 - 2FFh)*/
/* AudioIF ch2	(1E20_(0300 - 3FFh)*/
/* AudioIF ch3	(1E20_(0400 - 4FFh)*/
/* AudioIF ch4	(1E20_(0500 - 5FFh)*/
/* AudioIF ch5	(1E20_(0600 - 6FFh)*/
typedef struct _IoAudioif
{
	/* 1E20_(0100 - 0103h)	*/
	unsigned long auidlr;
	/* 1E20_(0104 - 0107h)	*/
	unsigned long auodlr;
	/* 1E20_(0108 - 010Bh)	*/
	IoAudioAucr aucr;
	/* 1E20_(010C - 010Fh)	*/
	IoAudioAumd aumd;
	/* 1E20_(0110 - 0113h)	*/
	IoAudioAust aust;
	/* 1E20_(0114 - 0117h)	*/
	IoAudioAucc aucc;
	/* 1E20_(0118 - 011Bh)	*/
	IoAudioAudp audp;
	/* 1E20_(011C - 011Fh)	*/
	IoAudioAuifst auifst;
	/* 1E20_(0120 - 0123h)	*/
	IoAudioAuofst auofst;
	/* 1E20_(0124 - 0127h)	*/
	unsigned char dmy1e2001241e200127[0x1E200128 - 0x1E200124];
	/* 1E20_(0128 - 012Bh)	*/
	unsigned long auidl;
	/* 1E20_(012C - 012Fh)	*/
	unsigned long auidr;
	/* 1E20_(0130 - 0133h)	*/
	unsigned long auodl;
	/* 1E20_(0134 - 0137h)	*/
	unsigned long auodr;
	/* 1E20_(0138 - 013Bh)	*/
	unsigned long auiddmapt;
	/* 1E20_(013C - 013Fh)	*/
	unsigned long auoddmapt;
	/* 1E20_(0140 - 0143h)	*/
	IoAudioAudma2ctl audma2ctl;
	/* 1E20_(0144 - 0147h)	*/
	IoAudioAudmisample audmisample;
	/* 1E20_(0148 - 014Bh)	*/
	IoAudioAudmosample audmosample;
	/* 1E20_(014C - 01FFh)	*/
	unsigned char dmy1e20014c1e2001ff[0x1E200200 - 0x1E20014C];
} IoAudioif;

/* Define I/O Mapping Audio */
typedef struct _IoAudio
{
	/* 1E20_(0000 - 00FFh)	*/
	IoAudioifctrl audioifCtrl;
	/* 1E20_(0100 - 06FFh)	*/
	IoAudioif audioif[6];
} IoAudio;


/* addr 1E200000h-	*/
extern volatile IoAudio ioAudio;


KConstType audio_if_get_type(void);
AudioIf* audio_if_new(void);


#endif/*__AUDIO_IF_H__*/

