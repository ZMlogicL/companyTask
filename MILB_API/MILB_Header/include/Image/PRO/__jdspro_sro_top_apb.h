/**
 * @file		__jdspro_sro_top_apb.h
 * @brief		Definition JDSPRO Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#ifndef _ioPro_sro_TOP_APB_H_
#define _ioPro_sro_TOP_APB_H_

//#include "__jdspro_sro_top.h"
//#include "__jdspro_pg.h"
//#include "__jdspro_ff.h"
//#include "__jdspro_ffsh.h"
//#include "__jdspro_ffc.h"
//#include "__jdspro_pgain.h"
//#include "__jdspro_sdc.h"
//#include "__jdspro_pzsft.h"
//#include "__jdspro_dpc.h"
//#include "__jdspro_fshdl.h"
//#include "__jdspro_afpb.h"
//#include "__jdspro_cag.h"
//#include "__jdspro_vrb.h"
//#include "__jdspro_hrb.h"
//#include "__jdspro_p2m.h"
//#include "__jdspro_pwch.h"
//#include "__jdspro_m2p.h"
//#include "__jdspro_prch.h"
//#include "__jdspro_moni.h"
//// --- REMOVE_BUZ BEGIN
//#ifdef CO_USE_BUZ
//#include "__jdspro_buz.h"
//#endif
#include "../Project/Image/src/kjdspro.h"
// --- REMOVE_BUZ END

///* Define i/o mapping */
//typedef struct _IoSroTopApb{
//    /* JDSIMG */
//    struct IoSrotop                srotop;     /* 2840_(8000 - 80FFh) */
//    struct IoPg                    pg;         /* 2840_(8100 - 81FFh) */
//    struct IoFfsh                  ffsh[2];    /* 2840_(8200 - 82FFh) */
//                                                /* 2840_(8300 - 83FFh) */
//    struct IoFf                    ff[2];      /* 2840_(8400 - 84FFh) */
//                                                /* 2840_(8500 - 85FFh) */
//    IoPgain                 pgain0;     /* 2840_(8600 - 86FFh) */
//
//    unsigned char dmy_8700_87FF[0x8800-0x8700]; /* 2840_(8700 - 87FFh) */
//
//    struct IoSdc                   sdc[2];     /* 2840_(8800 - 8BFFh) */
//                                                /* 2840_(8C00 - 8FFFh) */
//    struct IoPzsft                 pzsftb1;    /* 2840_(9000 - 90FFh) */
//    struct IoDpc                   dpc;        /* 2840_(9100 - 91FFh) */
//    struct IoPzsft                 pzsftb2;    /* 2840_(9200 - 92FFh) */
//    struct IoFshdl                 fshdl0;     /* 2840_(9300 - 93FFh) */
//    struct IoAfpb                  afpb[2];    /* 2840_(9400 - 94FFh) */
//                                                /* 2840_(9500 - 95FFh) */
//    struct IoPzsft                 pzsftc1;    /* 2840_(9600 - 96FFh) */
//    struct IoFfc                   ffc;        /* 2840_(9700 - 97FFh) */
//    struct IoCag                   cag;        /* 2840_(9800 - 98FFh) */
//    struct IoPzsft                 pzsftc2;    /* 2840_(9900 - 99FFh) */
//    struct IoFshdl                 fshdl1;     /* 2840_(9A00 - 9AFFh) */
//    struct IoVrb                   vrb;        /* 2840_(9B00 - 9BFFh) */
//    struct IoHrb                   hrb;        /* 2840_(9C00 - 9DFFh) */
//    IoP2m                   p2m[6];     /* 2840_(9E00 - 9EFFh) */
//                                                /* 2840_(9F00 - 9FFFh) */
//                                                /* 2840_(A000 - A0FFh) */
//                                                /* 2840_(A100 - A1FFh) */
//                                                /* 2840_(A200 - A2FFh) */
//                                                /* 2840_(A300 - A3FFh) */
//    IoPwch                  pwch[6];    /* 2840_(A400 - A4FFh) */
//                                                /* 2840_(A500 - A5FFh) */
//                                                /* 2840_(A600 - A6FFh) */
//                                                /* 2840_(A700 - A7FFh) */
//                                                /* 2840_(A800 - A8FFh) */
//                                                /* 2840_(A900 - A9FFh) */
//    IoM2p                   m2p[8];     /* 2840_(AA00 - AAFFh) */
//                                                /* 2840_(AB00 - ABFFh) */
//                                                /* 2840_(AC00 - ACFFh) */
//                                                /* 2840_(AD00 - ADFFh) */
//                                                /* 2840_(AE00 - AEFFh) */
//                                                /* 2840_(AF00 - AFFFh) */
//                                                /* 2840_(B000 - B0FFh) */
//                                                /* 2840_(B100 - B1FFh) */
//    IoPrch                  prch[10];   /* 2840_(B200 - B2FFh) */
//                                                /* 2840_(B300 - B3FFh) */
//                                                /* 2840_(B400 - B4FFh) */
//                                                /* 2840_(B500 - B5FFh) */
//                                                /* 2840_(B600 - B6FFh) */
//                                                /* 2840_(B700 - B7FFh) */
//                                                /* 2840_(B800 - B8FFh) */
//                                                /* 2840_(B900 - B9FFh) */
//                                                /* 2840_(BA00 - BAFFh) */
//                                                /* 2840_(BB00 - BBFFh) */
//    struct IoMoni                  moni0;      /* 2840_(BC00 - BCFFh) */
//
//// --- REMOVE_BUZ BEGIN
//#ifdef CO_USE_BUZ
//    unsigned char dmy_2840BD00_2840C3FF[0x2840C400-0x2840BD00]; /* 2840_BD00 - 2840_C3FFh */
//
//    struct IoBuz                   buz;       /* 2840_(C400 - C4FFh) */
//    struct IoMoni                  moni1;     /* 2840_(C500 - C5FFh) */
//
//    unsigned char dmy_2840C600_2840FFFF[0x28410000-0x2840C600]; /* 2840_C600 - 2840_FFFFh */
//
//#endif
//// --- REMOVE_BUZ END
//
//// --- REMOVE_BUZ BEGIN
//#ifndef CO_USE_BUZ
//// --- REMOVE_BUZ END
//    unsigned char dmy_2840BD00_2840FFFF[0x28410000-0x2840BD00]; /* 2840_BD00 - 2840_FFFFh */
//// --- REMOVE_BUZ BEGIN
//#endif	// CO_USE_BUZ
//// --- REMOVE_BUZ END
//}IoSroTopApb;

#endif	// _ioPro_sro_TOP_APB_H_
