/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-07
 *@author            :陈倩
 *@brief             :kjdspro
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

#ifndef __K_JDSPRO_H__
#define __K_JDSPRO_H__

#include <klib.h>
//#include "__jdspro_sen_top_apb.h"
//#include "__jdspro_sro_top_apb.h"
//#include "__jdspro_b2b_top_apb.h"
//#include "__jdspro_stat_top_apb.h"
//#include "__jdspro_pas_top_apb.h"
#include "__jdspro_m2p.h"
#include "__jdspro_p2m.h"
#include "__jdspro_prch.h"
#include "__jdspro_pwch.h"
#include "__jdspro_tbl.h"
#include "__jdspro_sen_top.h"
#include "__jdspro_sg.h"
#include "__jdspro_slvsec.h"
#include "__jdspro_lvds.h"
#include "__jdspro_mpid.h"
#include "__jdspro_mpic.h"
#include "__jdspro_moni.h"
#include "__jdspro_ldiv.h"
#include "__jdspro_lnr.h"
#include "__jdspro_obd_top.h"
#include "__jdspro_obt_top.h"
#include "__jdspro_sro_top.h"
#include "__jdspro_pg.h"
#include "__jdspro_ff.h"
#include "__jdspro_ffsh.h"
#include "__jdspro_ffc.h"
#include "__jdspro_pgain.h"
#include "__jdspro_sdc.h"
#include "__jdspro_pzsft.h"
#include "__jdspro_dpc.h"
#include "__jdspro_fshdl.h"
#include "__jdspro_afpb.h"
#include "__jdspro_cag.h"
#include "__jdspro_vrb.h"
#include "__jdspro_hrb.h"
// --- REMOVE_BUZ BEGIN
#ifdef CO_USE_BUZ
#include "__jdspro_buz.h"
#endif
#include "__jdspro_b2b_top.h"
#include "__jdspro_elf.h"
#include "__jdspro_fshd.h"
#include "__jdspro_stat_top.h"
#include "__jdspro_af_top.h"
#include "__jdspro_aeawb.h"
#include "__jdspro_flck.h"
#include "__jdspro_hist.h"
#include "__jdspro_pas_top.h"
#include "__jdspro_spt.h"
#include "__jdspro_sen_top_ahb.h"
#include "__jdspro_sro_top_ahb.h"
#include "__jdspro_b2b_top_ahb.h"
#include "__jdspro_stat_top_ahb.h"
#include "__jdspro_pas_top_ahb.h"

#define K_TYPE_JDSPRO				(k_jdspro_get_type())
#define K_JDSPRO(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KJdspro))
#define K_IS_JDSPRO(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSPRO))

typedef struct _KJdspro 				KJdspro;
typedef struct _KJdsproPrivate 	KJdsproPrivate;

struct _KJdspro
{
	KObject parent;
};

/* Define i/o mapping */
typedef struct _IoSroTopApb
{
	/* JDSIMG */
	IoSrotop srotop; /* 2840_(8000 - 80FFh) */
	IoPg pg; /* 2840_(8100 - 81FFh) */
	IoFfsh ffsh[2]; /* 2840_(8200 - 82FFh) */
	/* 2840_(8300 - 83FFh) */
	IoFf ff[2]; /* 2840_(8400 - 84FFh) */
	/* 2840_(8500 - 85FFh) */
	IoPgain pgain0; /* 2840_(8600 - 86FFh) */
	unsigned char dmy870087ff[0x8800 - 0x8700]; /* 2840_(8700 - 87FFh) */
	IoSdc sdc[2]; /* 2840_(8800 - 8BFFh) */
	/* 2840_(8C00 - 8FFFh) */
	IoPzsft pzsftb1; /* 2840_(9000 - 90FFh) */
	IoDpc dpc; /* 2840_(9100 - 91FFh) */
	IoPzsft pzsftb2; /* 2840_(9200 - 92FFh) */
	IoFshdl fshdl0; /* 2840_(9300 - 93FFh) */
	IoAfpb afpb[2]; /* 2840_(9400 - 94FFh) */
	/* 2840_(9500 - 95FFh) */
	IoPzsft pzsftc1; /* 2840_(9600 - 96FFh) */
	IoFfc ffc; /* 2840_(9700 - 97FFh) */
	IoCag cag; /* 2840_(9800 - 98FFh) */
	IoPzsft pzsftc2; /* 2840_(9900 - 99FFh) */
	IoFshdl fshdl1; /* 2840_(9A00 - 9AFFh) */
	IoVrb vrb; /* 2840_(9B00 - 9BFFh) */
	IoHrb hrb; /* 2840_(9C00 - 9DFFh) */
	IoP2m p2m[6]; /* 2840_(9E00 - 9EFFh) */
	/* 2840_(9F00 - 9FFFh) */
	/* 2840_(A000 - A0FFh) */
	/* 2840_(A100 - A1FFh) */
	/* 2840_(A200 - A2FFh) */
	/* 2840_(A300 - A3FFh) */
	IoPwch pwch[6]; /* 2840_(A400 - A4FFh) */
	/* 2840_(A500 - A5FFh) */
	/* 2840_(A600 - A6FFh) */
	/* 2840_(A700 - A7FFh) */
	/* 2840_(A800 - A8FFh) */
	/* 2840_(A900 - A9FFh) */
	IoM2p m2p[8]; /* 2840_(AA00 - AAFFh) */
	/* 2840_(AB00 - ABFFh) */
	/* 2840_(AC00 - ACFFh) */
	/* 2840_(AD00 - ADFFh) */
	/* 2840_(AE00 - AEFFh) */
	/* 2840_(AF00 - AFFFh) */
	/* 2840_(B000 - B0FFh) */
	/* 2840_(B100 - B1FFh) */
	IoPrch prch[10]; /* 2840_(B200 - B2FFh) */
	/* 2840_(B300 - B3FFh) */
	/* 2840_(B400 - B4FFh) */
	/* 2840_(B500 - B5FFh) */
	/* 2840_(B600 - B6FFh) */
	/* 2840_(B700 - B7FFh) */
	/* 2840_(B800 - B8FFh) */
	/* 2840_(B900 - B9FFh) */
	/* 2840_(BA00 - BAFFh) */
	/* 2840_(BB00 - BBFFh) */
	IoMoni moni0; /* 2840_(BC00 - BCFFh) */
// --- REMOVE_BUZ BEGIN
#ifdef CO_USE_BUZ
	unsigned char dmy2840bd002840c3ff[0x2840C400 - 0x2840BD00]; /* 2840_BD00 - 2840_C3FFh */
	IoBuz buz; /* 2840_(C400 - C4FFh) */
	IoMoni moni1; /* 2840_(C500 - C5FFh) */
	unsigned char dmy2840c6002840ffff[0x28410000 - 0x2840C600]; /* 2840_C600 - 2840_FFFFh */
#endif
// --- REMOVE_BUZ END
// --- REMOVE_BUZ BEGIN
#ifndef CO_USE_BUZ
// --- REMOVE_BUZ END
	unsigned char dmy2840bd002840ffff[0x28410000-0x2840BD00]; /* 2840_BD00 - 2840_FFFFh */
// --- REMOVE_BUZ BEGIN
#endif	// CO_USE_BUZ
// --- REMOVE_BUZ END
} IoSroTopApb;

/* Define i/o mapping */
typedef struct _IoB2bTopApb
{
	/* JDSIMG */
	IoB2btop b2btop; /* 2841_(0000 - 00FFh) */
	IoPg pg; /* 2841_(0100 - 01FFh) */
	IoPgain pgain1; /* 2841_(0200 - 02FFh) */
	IoPzsft pzsfta1; /* 2841_(0300 - 03FFh) */
	IoElf elf; /* 2841_(0400 - 07FFh) */
	IoPzsft pzsfta2; /* 2841_(0800 - 08FFh) */
	IoPzsft pzsfta2a; /* 2841_(0900 - 09FFh) */
	IoFshd fshd; /* 2841_(0A00 - 0AFFh) */
	IoPgain pgain2; /* 2841_(0B00 - 0BFFh) */
	IoP2m p2m[2]; /* 2841_(0C00 - 0CFFh) */
	/* 2841_(0D00 - 0DFFh) */
	IoPwch pwch[2]; /* 2841_(0E00 - 0EFFh) */
	/* 2841_(0F00 - 0FFFh) */
	IoM2p m2p[4]; /* 2841_(1000 - 10FFh) */
	/* 2841_(1100 - 11FFh) */
	/* 2841_(1200 - 12FFh) */
	/* 2841_(1300 - 13FFh) */
	IoPrch prch[5]; /* 2841_(1400 - 14FFh) */
	/* 2841_(1500 - 15FFh) */
	/* 2841_(1600 - 16FFh) */
	/* 2841_(1700 - 17FFh) */
	/* 2841_(1800 - 18FFh) */
	unsigned char dmy19001fff[0x2000 - 0x1900]; /* 2841_(1900 - 1FFFh) */
} IoB2bTopApb;

typedef struct _IoProPipe
{
	/* 28x0_0000 - 28x0_7FFF */
	unsigned char dmy0x08000[0x8000];
	/* 28x0_(8000 - FFFFh) */
	IoSroTopApb sro;
	/* 28x1_(0000 - 1FFFh) */
	IoB2bTopApb b2b;
	/* 28x1_2000 - 28xF_FFFF */
	unsigned char dmy0xee000[0xEE000];
} IoProPipe;

/* Define i/o mapping */
typedef struct _IoSenTopApb
{
	/* JDSIMG */
	IoSentop sentop; /* 2800_(8000 - 83FFh) */
	IoSg sg[4]; /* 2800_(8400 - 84FFh) */
	/* 2800_(8500 - 85FFh) */
	/* 2800_(8600 - 86FFh) */
	/* 2800_(8700 - 87FFh) */
	IoLvds lvds[4]; /* 2800_(8800 - 89FFh) */
	/* 2800_(8A00 - 8BFFh) */
	/* 2800_(8C00 - 8DFFh) */
	/* 2800_(8E00 - 8FFFh) */
	IoSlvs slvsec; /* 2800_(9000 - 93FFh) */
	unsigned char dmy940097ff[0x9800 - 0x9400]; /* 2800_(9400 - 97FFh) */
	IoMpid mipid[4]; /* 2800_(9800 - 98FFh) */
	/* 2800_(9900 - 99FFh) */
	/* 2800_(9A00 - 9AFFh) */
	/* 2800_(9B00 - 9BFFh) */
	IoMpic mipic[4]; /* 2800_(9C00 - 9DFFh) */
	/* 2800_(9E00 - 9FFFh) */
	/* 2800_(A000 - A1FFh) */
	/* 2800_(A200 - A3FFh) */
	IoMoni moni[4]; /* 2800_(A400 - A4FFh) */
	/* 2800_(A500 - A5FFh) */
	/* 2800_(A600 - A6FFh) */
	/* 2800_(A700 - A7FFh) */
	IoLdiv ldiv[4]; /* 2800_(A800 - A8FFh) */
	IoLnr lnr[4]; /* 2800_(AC00 - ACFFh) */
	/* 2800_(AD00 - ADFFh) */
	/* 2800_(AE00 - AEFFh) */
	/* 2800_(AF00 - AFFFh) */
	IoObdTop obd[4][2]; /* 2800_(B000 - B0FFh) */
	/* 2800_(B100 - B1FFh) */
	/* 2800_(B200 - B2FFh) */
	/* 2800_(B300 - B3FFh) */
	/* 2800_(B400 - B4FFh) */
	/* 2800_(B500 - B5FFh) */
	/* 2800_(B600 - B6FFh) */
	/* 2800_(B700 - B7FFh) */
	IoObtTop obt[4][2]; /* 2800_(B800 - B8FFh) */
	/* 2800_(B900 - B9FFh) */
	/* 2800_(BA00 - BAFFh) */
	/* 2800_(BB00 - BBFFh) */
	/* 2800_(BC00 - BCFFh) */
	/* 2800_(BD00 - BDFFh) */
	/* 2800_(BE00 - BEFFh) */
	/* 2800_(BF00 - BFFFh) */
	IoP2m p2m[8]; /* 2800_(C000 - C0FFh) */
	/* 2800_(C100 - C1FFh) */
	/* 2800_(C200 - C2FFh) */
	/* 2800_(C300 - C3FFh) */
	/* 2800_(C400 - C4FFh) */
	/* 2800_(C500 - C5FFh) */
	/* 2800_(C600 - C6FFh) */
	/* 2800_(C700 - C7FFh) */
	IoPwch pwch[8]; /* 2800_(C800 - C8FFh) */
	/* 2800_(C900 - C9FFh) */
	/* 2800_(CA00 - CAFFh) */
	/* 2800_(CB00 - CBFFh) */
	/* 2800_(CC00 - CCFFh) */
	/* 2800_(CD00 - CDFFh) */
	/* 2800_(CE00 - CEFFh) */
	/* 2800_(CF00 - CFFFh) */
	unsigned char dmy2800d0002800ffff[0x28010000 - 0x2800D000]; /* 2800_D000 - 2800_FFFFh */
} IoSenTopApb;

/* Define i/o mapping */
typedef struct _IoStatTopApb
{
	/* JDSIMG */
	IoStattop stattop; /* 2886_(0000 - 00FFh) */
	unsigned char dmy01001fff[0x2000 - 0x0100]; /* 2886_(0100 - 1FFFh) */
	IoAftop af[2]; /* 2886_(2000 - 3FFFh) */
	/* 2886_(4000 - 5FFFh) */
	IoAeawb aeawb[4]; /* 2886_(6000 - 60FFh) */
	/* 2886_(6100 - 61FFh) */
	/* 2886_(6200 - 62FFh) */
	/* 2886_(6300 - 63FFh) */
	IoFlck flck[2]; /* 2886_(6400 - 64FFh) */
	/* 2886_(6500 - 65FFh) */
	IoHist hist[4]; /* 2886_(6600 - 66FFh) */
	/* 2886_(6700 - 67FFh) */
	/* 2886_(6800 - 68FFh) */
	/* 2886_(6900 - 69FFh) */
	IoPwch pwch[6]; /* 2886_(6A00 - 6AFFh) */
	/* 2886_(6B00 - 6BFFh) */
	/* 2886_(6C00 - 6CFFh) */
	/* 2886_(6D00 - 6DFFh) */
	/* 2886_(6E00 - 6EFFh) */
	/* 2886_(6F00 - 6FFFh) */
	unsigned char dmy70007fff[0x8000 - 0x7000]; /* 2886_(7000 - 7FFFh) */
} IoStatTopApb;

/* Define i/o mapping */
typedef struct _IoPasTopApb
{
	/* JDSIMG */
	IoPastop pastop; /* 2886_(8000 - 80FFh) */
	 IoPg pg; /* 2886_(8100 - 81FFh) */
	IoLnr lnr; /* 2886_(8200 - 82FFh) */
	IoPgain pgain; /* 2886_(8300 - 83FFh) */
	IoSpt spt; /* 2886_(8400 - 84FFh) */
	IoP2m p2m0; /* 2886_(8500 - 85FFh) */
	IoPwch pwch0; /* 2886_(8600 - 86FFh) */
	IoM2p m2p0; /* 2886_(8700 - 87FFh) */
	IoPrch prch0; /* 2886_(8800 - 88FFh) */
	unsigned char dmy89008fff[0x9000 - 0x8900]; /* 2886_(8900 - 8FFFh) */
} IoPasTopApb;

/* Define i/o mapping */
typedef struct _IoPro
{
	/* JDSIMG */
	// IMG_APB0
	/* 2800_(8000 - FFFFh) */
	IoSenTopApb sen;
	/* 2801_0000 - 280F_FFFF */
	unsigned char dmy28010000280fffff[0x28100000 - 0x28010000];
	/* 2810_0000 - 283F_FFFF */
	unsigned char dmy28100000283fffff[0x28400000 - 0x28100000];
	// IMG_APB1(PIPE[1] / PIPE[2] / PIPE[3])
	/* 2840_0000 - 286F_FFFF */
	IoProPipe imgPipe[3];
	/* 2870_0000 - 287F_FFFF */
	unsigned char dmy28700000287fffff[0x28800000 - 0x28700000];
	// IMG_APB3
	/* 2880_0000 - 2885_FFFF */
	unsigned char dmy288000002885ffff[0x28860000 - 0x28800000];
	/* 2886_(0000 - 7FFFh) */
	IoStatTopApb stat;
	/* 2886_(8000 - 8FFFh) */
	IoPasTopApb pas;
} IoPro;

/* Define i/o mapping */
typedef struct _IoProTbl
{
	/* JDSIMG */
	// IMG_APB0
	IoSenAhb senTbl; /* 2900_(0000 - 3FFFh) */
	unsigned char dmy29004000290fffff[0x29100000 - 0x29004000]; /* 2900_4000 - 290F_FFFF */
	unsigned char dmy29100000293fffff[0x29400000 - 0x29100000]; /* 2910_0000 - 293F_FFFF */
	// IMG_APB1(PIPE[1])
	unsigned char dmy294000002943ffff[0x29440000 - 0x29400000]; /* 2940_0000 - 2943_FFFF */
	IoSroAhb sro1Tbl; /* 2944_0000 - 2947_FFFFh */
	IoB2bAhb b2b1Tbl; /* 2948_0000 - 2948_1FFFh */
	unsigned char dmy29482000294fffff[0x29500000 - 0x29482000]; /* 2948_2000 - 294F_FFFF */
	// IMG_APB1(PIPE[2])
	unsigned char dmy295000002953ffff[0x29540000 - 0x29500000]; /* 2950_0000 - 2953_FFFF */
	IoSroAhb sro2Tbl; /* 2954_0000 - 2957_FFFFh */
	IoB2bAhb b2b2Tbl; /* 2958_0000 - 2958_1FFFh */
	unsigned char dmy29482000295fffff[0x29600000 - 0x29582000]; /* 2958_2000 - 295F_FFFF */
	// IMG_APB1(PIPE[3])
	unsigned char dmy296000002963ffff[0x29640000 - 0x29600000]; /* 2960_0000 - 2963_FFFF */
	IoSroAhb sro3Tbl; /* 2964_0000 - 2967_FFFFh */
	IoB2bAhb b2b3Tbl; /* 2968_0000 - 2968_1FFFh */
	unsigned char dmy29682000297fffff[0x29800000 - 0x29682000]; /* 2968_2000 - 297F_FFFF */
	// IMG_APB3
	unsigned char dmy298000002980ffff[0x29810000 - 0x29800000]; /* 2980_0000 - 2980_FFFF */
	IoStatAhb statTbl; /* 2981_0000 - 2981_3FFFh */
	IoPasAhb pasTbl; /* 2981_4000 - 2981_4FFFh */

} IoProTbl;


extern volatile IoPro ioPro;
extern volatile IoProTbl ioProTbl;


KConstType 	k_jdspro_get_type(void);
KJdspro* 			k_jdspro_new(void);


#endif/*__K_JDSPRO_H__*/

