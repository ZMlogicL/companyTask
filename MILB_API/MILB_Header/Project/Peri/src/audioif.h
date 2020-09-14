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


typedef struct _AudioIf 				AudioIf;
typedef struct _AudioIfPrivate	AudioIfPrivate;


struct _AudioIf
{
	KObject parent;
};

/*	structure of aures	*/
typedef union _IoAudioAures
{
	kulong word;
	struct
	{
		kulong auif0Rst :1;
		kulong auif1Rst :1;
		kulong auif2Rst :1;
		kulong auif3Rst :1;
		kulong auif4Rst :1;
		kulong auif5Rst :1;
		kulong :26;
	} bit;
} IoAudioAures;

/*	structure of auioe	*/
typedef union _IoAudioAuioe
{
	kulong word;
	struct
	{
		kulong auie0 :2;
		kulong auie1 :2;
		kulong auie2 :2;
		kulong auie3 :2;
		kulong auie4 :2;
		kulong auie5 :2;
		kulong :4;
		kulong auoe0 :2;
		kulong auoe1 :2;
		kulong auoe2 :2;
		kulong auoe3 :2;
		kulong auoe4 :2;
		kulong auoe5 :2;
		kulong :4;
	} bit;
} IoAudioAuioe;

/*	structure of aulbe	*/
typedef union _IoAudioAulbe
{
	kulong word;
	struct
	{
		kulong aulbe0 :2;
		kulong aulbe1 :2;
		kulong aulbe2 :2;
		kulong aulbe3 :2;
		kulong aulbe4 :2;
		kulong aulbe5 :2;
		kulong :20;
	} bit;
} IoAudioAulbe;

/*	structure of aucr	*/
typedef union _IoAudioAucr
{
	kulong word;
	struct
	{
		kulong auidsel :1;
		kulong auodsel :1;
		kulong :6;
		kulong inti :1;
		kulong into :1;
		kulong intie :1;
		kulong intoe :1;
		kulong auief :1;
		kulong auoef :1;
		kulong dmie :1;
		kulong dmoe :1;
		kulong auif :4;
		kulong :3;
		kulong auirf :1;
		kulong auof :7;
		kulong auorf :1;
	} bit;
} IoAudioAucr;

/*	structure of aumd	*/
typedef union _IoAudioAumd
{
	kulong word;
	struct
	{
		kulong :16;
		kulong ibyteSwp :1;
		kulong ihwSwp :1;
		kulong obyteSwp :1;
		kulong ohwSwp :1;
		kulong :4;
		kulong istg16 :1;
		kulong ostg16 :1;
		kulong :1;
		kulong stereo :1;
		kulong :3;
		kulong lbf :1;
	} bit;
} IoAudioAumd;

/*	structure of aust	*/
typedef union _IoAudioAust
{
	kulong word;
	struct
	{
		kulong :16;
		kulong irof :1;
		kulong oruf :1;
		kulong ofie :1;
		kulong ufie :1;
		kulong :4;
		kulong einti :1;
		kulong einto :1;
		kulong eintie :1;
		kulong eintoe :1;
		kulong edmie :1;
		kulong edmoe :1;
		kulong estg :2;
	} bit;
} IoAudioAust;

/*	structure of aucc	*/
typedef union _IoAudioAucc
{
	kulong word;
	struct
	{
		kulong :16;
		kulong divlr :2;
		kulong divck :3;
		kulong :3;
		kulong divmck :5;
		kulong :1;
		kulong dive :1;
		kulong auckoe :1;
	} bit;
} IoAudioAucc;

/*	structure of audp	*/
typedef union _IoAudioAudp
{
	kulong word;
	struct
	{
		kulong mixplay :1;
		kulong :7;
		kulong aulrcp :1;
		kulong :7;
		kulong auidf :1;
		kulong auodf :1;
		kulong :6;
		kulong auods :2;
		kulong :2;
		kulong auids :2;
		kulong :2;
	} bit;
} IoAudioAudp;

/*	structure of auifst	*/
typedef union _IoAudioAuifst
{
	kulong word;
	struct
	{
		kulong auisl0 :1;
		kulong auisr0 :1;
		kulong auisl1 :1;
		kulong auisr1 :1;
		kulong auisl2 :1;
		kulong auisr2 :1;
		kulong auisl3 :1;
		kulong auisr3 :1;
		kulong auisl4 :1;
		kulong auisr4 :1;
		kulong auisl5 :1;
		kulong auisr5 :1;
		kulong auisl6 :1;
		kulong auisr6 :1;
		kulong auisl7 :1;
		kulong auisr7 :1;
		kulong auisl8 :1;
		kulong auisr8 :1;
		kulong auisl9 :1;
		kulong auisr9 :1;
		kulong auisl10 :1;
		kulong auisr10 :1;
		kulong auisl11 :1;
		kulong auisr11 :1;
		kulong auisl12 :1;
		kulong auisr12 :1;
		kulong auisl13 :1;
		kulong auisr13 :1;
		kulong auisl14 :1;
		kulong auisr14 :1;
		kulong auisl15 :1;
		kulong auisr15 :1;
	} bit;
} IoAudioAuifst;

/*	structure of auofst	*/
typedef union _IoAudioAuofst
{
	kulong word;
	struct
	{
		kulong auosl0 :1;
		kulong auosr0 :1;
		kulong auosl1 :1;
		kulong auosr1 :1;
		kulong auosl2 :1;
		kulong auosr2 :1;
		kulong auosl3 :1;
		kulong auosr3 :1;
		kulong auosl4 :1;
		kulong auosr4 :1;
		kulong auosl5 :1;
		kulong auosr5 :1;
		kulong auosl6 :1;
		kulong auosr6 :1;
		kulong auosl7 :1;
		kulong auosr7 :1;
		kulong auosl8 :1;
		kulong auosr8 :1;
		kulong auosl9 :1;
		kulong auosr9 :1;
		kulong auosl10 :1;
		kulong auosr10 :1;
		kulong auosl11 :1;
		kulong auosr11 :1;
		kulong auosl12 :1;
		kulong auosr12 :1;
		kulong auosl13 :1;
		kulong auosr13 :1;
		kulong auosl14 :1;
		kulong auosr14 :1;
		kulong auosl15 :1;
		kulong auosr15 :1;
	} bit;
} IoAudioAuofst;

/*	structure of audma2ctl	*/
typedef union _IoAudioAudma2ctl
{
	kulong word;
	struct
	{
		kulong dmi2chen :1;
		kulong :7;
		kulong dmo2chen :1;
		kulong :23;
	} bit;
} IoAudioAudma2ctl;

/*	structure of audmisample	*/
typedef union _IoAudioAudmisample
{
	kulong word;
	struct
	{
		kulong dmispl :16;
		kulong :16;
	} bit;
} IoAudioAudmisample;

/*	structure of audmosample	*/
typedef union _IoAudioAudmosample
{
	kulong word;
	struct
	{
		kulong dmospl :16;
		kulong :16;
	} bit;
} IoAudioAudmosample;

/* AudioIF Control	(1E20_(0000 - 0FFh)*/
typedef struct _IoAudioifctrl
{
	/* 1E20_(0000 - 0003h)	*/
	IoAudioAures aures;
	/* 1E20_(0004 - 0007h)	*/
	kuchar dmy1e2000041e200007[0x1E200008 - 0x1E200004];
	/* 1E20_(0008 - 000Bh)	*/
	kuchar dmy1e2000081e20000b[0x1E20000C - 0x1E200008];
	/* 1E20_(000C - 000Fh)	*/
	IoAudioAuioe auioe;
	/* 1E20_(0010 - 0013h)	*/
	kuchar dmy1e2000101e200013[0x1E200014 - 0x1E200010];
	/* 1E20_(0014 - 0017h)	*/
	IoAudioAulbe aulbe;
	/* 1E20_(0018 - 00FFh)	*/
	kuchar dmy1e2000181e2000ff[0x1E200100 - 0x1E200018];
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
	kulong auidlr;
	/* 1E20_(0104 - 0107h)	*/
	kulong auodlr;
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
	kuchar dmy1e2001241e200127[0x1E200128 - 0x1E200124];
	/* 1E20_(0128 - 012Bh)	*/
	kulong auidl;
	/* 1E20_(012C - 012Fh)	*/
	kulong auidr;
	/* 1E20_(0130 - 0133h)	*/
	kulong auodl;
	/* 1E20_(0134 - 0137h)	*/
	kulong auodr;
	/* 1E20_(0138 - 013Bh)	*/
	kulong auiddmapt;
	/* 1E20_(013C - 013Fh)	*/
	kulong auoddmapt;
	/* 1E20_(0140 - 0143h)	*/
	IoAudioAudma2ctl audma2ctl;
	/* 1E20_(0144 - 0147h)	*/
	IoAudioAudmisample audmisample;
	/* 1E20_(0148 - 014Bh)	*/
	IoAudioAudmosample audmosample;
	/* 1E20_(014C - 01FFh)	*/
	kuchar dmy1e20014c1e2001ff[0x1E200200 - 0x1E20014C];
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

