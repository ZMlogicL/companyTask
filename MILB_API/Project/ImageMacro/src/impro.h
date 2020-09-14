/*
 * impro.h
 *
 *  Created on: 2020年9月4日
 *      Author: sns
 */

#ifndef __IM_PRO_H__
#define __IM_PRO_H__

#include <klib.h>
#include "driver_common.h"

#define IM_TYPE_PRO		(im_pro_get_type())
#define IM_PRO(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImPro))
#define IM_IS_PRO(obj)	(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImPro))
#define	D_IM_B2B1_STATUS_NONE					(0x00000000UL)				/* All stopped		*/
#define	D_IM_B2B1_STATUS_ELF					((0x00000000UL)&(1<< 0))	/* ELF				*/
#define	D_IM_B2B1_STATUS_ELF_NSL				((0x00000000UL)&(1<< 1))	/* ELF NSL			*/
#define	D_IM_B2B1_STATUS_FSHD					((0x00000000UL)&(1<< 2))	/* FSHD				*/
#define	D_IM_B2B2_STATUS_NONE					(0x00000000UL)				/* All stopped		*/
#define	D_IM_B2B2_STATUS_ELF					((0x10000000UL)&(1<< 0))	/* ELF				*/
#define	D_IM_B2B2_STATUS_ELF_NSL				((0x10000000UL)&(1<< 1))	/* ELF NSL			*/
#define	D_IM_B2B2_STATUS_FSHD					((0x10000000UL)&(1<< 2))	/* FSHD				*/
#define	D_IM_B2B_STATUS_ELF_BOTH				( D_IM_B2B1_STATUS_ELF		| D_IM_B2B2_STATUS_ELF		)	/* Image Pipe1&2 ELF		*/
#define	D_IM_B2B_STATUS_ELF_NSL_BOTH			( D_IM_B2B1_STATUS_ELF_NSL	| D_IM_B2B2_STATUS_ELF_NSL	)	/* Image Pipe1&2 ELF NSL	*/
#define	D_IM_B2B_STATUS_FSHD_BOTH				( D_IM_B2B1_STATUS_FSHD		| D_IM_B2B2_STATUS_FSHD		)	/* Image Pipe1&2 FSHD		*/
#define im_pro_b2b_set_start_status(st, ch) 		(gIM_B2B_START_Status[((st) >> 28) & 0xf] |=  (((st) & 0x0fffffff) << (ch)))							/* B2B clock status ON	*/
#define im_pro_b2b_set_stop_status(st, ch)		(gIM_B2B_START_Status[((st) >> 28) & 0xf] &= ~(((st) & 0x0fffffff) << (ch)))							/* B2B clock status OFF	*/
#define im_pro_b2b_get_start_status(st, ch)		(((gIM_B2B_START_Status[((st) >> 28) & 0xf] & (((st) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE)		/* started check	*/
#define im_pro_b2b_get_stop_all()				(((gIM_B2B_START_Status[0] | gIM_B2B_START_Status[1] | gIM_B2B_START_Status[2]) != 0) ? FALSE : TRUE)	/* started check	*/

/*improbase.h文件有，给你注释了*/
//typedef struct _ImPro ImPro;
//typedef enum {
//	E_IM_PRO_UNIT_NUM_1 = 0,	/**< UNIT number 1 block	*/
//	E_IM_PRO_UNIT_NUM_2,		/**< UNIT number 2 block	*/
//	E_IM_PRO_BOTH_UNIT,			/**< UNIT 1 & 2 block	*/
//	E_IM_PRO_UNIT_NUM_MAX,		/**< MAX value	*/
//} E_IM_PRO_UNIT_NUM;

typedef enum {
	E_IM_PRO_ELF_NSLKEN_DIS = 0,		/**< Disable	*/
	E_IM_PRO_ELF_NSLKEN_EN				/**< Enable		*/
} E_IM_PRO_ELF_NSLKEN;

typedef enum {
	E_IM_PRO_ELF_NSLRES_0 = 0,		/**< High-precision data	*/
	E_IM_PRO_ELF_NSLRES_1,			/**<	|					*/
	E_IM_PRO_ELF_NSLRES_2,			/**<	|					*/
	E_IM_PRO_ELF_NSLRES_3			/**< Low-precision data		*/
} E_IM_PRO_ELF_NSLRES;

typedef enum {
	E_IM_PRO_ELF_NSLMD_REDUCTION = 0,	/**< reduction mode		*/
	E_IM_PRO_ELF_NSLMD_MAGNIFICATION	/**< magnification mode	*/
} E_IM_PRO_ELF_NSLMD;

typedef struct {
	E_IM_PRO_ELF_NSLMD		l_noise_mode;			/**< Data mode of the long-wavelength noise data which is input from SDRAM.<br>
															target registor	:@@NSLMD */
	E_IM_PRO_ELF_NSLRES		l_noise_precision;		/**< Specify the accuracy of the long-wavelength noise data which is input from SDRAM.<br>
															target registor	:@@NSLRES */
	E_IM_PRO_ELF_NSLKEN		long_noise_comp;		/**< Compression enable of the long-wavelength noise data which is input from SDRAM.<br>
															target registor	:@@NSLKEN */
} T_IM_PRO_NSL_CTRL;

typedef struct {
	ULONG	FSHDCTBL;			/**< Frame Shading Concentric Circles Correction table register address */
} T_IM_PRO_RDMA_FSHD_CTBL_ADDR;

typedef enum {
	E_IM_PRO_FSHD_LUT_SEL_RAM0 = 0,		/**< RAM0(FSHDCTBL0)	*/
	E_IM_PRO_FSHD_LUT_SEL_RAM1			/**< RAM1(FSHDCTBL1)	*/
} E_IM_PRO_FSHD_LUT_SEL;

typedef struct {
	ULONG	FSHDCTL;			/**< 2841_(0A08 - 0A0Bh) */
	ULONG	FSHDHWPH;			/**< 2841_(0A1C - 0A1Fh) */
	ULONG	FSHDBC; 			/**< 2841_(0A20 - 0A23h) */
	ULONG	FSUL1;				/**< 2841_(0A24 - 0A27h) */
	ULONG	FSUL2;				/**< 2841_(0A28 - 0A2Bh) */
	ULONG	FSCTL;				/**< 2841_(0A30 - 0A33h) */
	ULONG	FSSUBPR;			/**< 2841_(0A34 - 0A37h) */
	ULONG	FSSUBSP;			/**< 2841_(0A38 - 0A3Bh) */
	ULONG	FSSUBDR;			/**< 2841_(0A3C - 0A3Fh) */
	ULONG	FSSUBST;			/**< 2841_(0A40 - 0A43h) */
	ULONG	FSA1;				/**< 2841_(0A44 - 0A47h) */
	ULONG	FSA2;				/**< 2841_(0A48 - 0A4Bh) */
	ULONG	CSCTL1; 			/**< 2841_(0A50 - 0A53h) */
	ULONG	CSCTL2; 			/**< 2841_(0A54 - 0A57h) */
	ULONG	CSTBLST;			/**< 2841_(0A58 - 0A5Bh) */
	ULONG	CSTBLS1;			/**< 2841_(0A5C - 0A5Fh) */
	ULONG	CSTBLS2;			/**< 2841_(0A60 - 0A63h) */
	ULONG	CSHDD;				/**< 2841_(0A64 - 0A67h) */
	ULONG	CSHDOA; 			/**< 2841_(0A68 - 0A6Bh) */
	ULONG	CSA1;				/**< 2841_(0A6C - 0A6Fh) */
	ULONG	CSA2;				/**< 2841_(0A70 - 0A73h) */
	ULONG	FSHDHCCTL;			/**< 2841_(0A80 - 0A83h) */
	ULONG	FSSLP1; 			/**< 2841_(0A84 - 0A87h) */
	ULONG	FSSLP2; 			/**< 2841_(0A88 - 0A8Bh) */
} T_IM_PRO_RDMA_FSHD_ADDR;

typedef struct {
	SHORT*	pshd_tbl;		/**< table address pointer for FSHDCTBL	*/
	USHORT	size;			/**< set table size for FSHDCTBL<br>
								value range		:[0 - 1024] number of array	*/
} T_IM_PRO_FSHD_TABLE;

typedef struct {
	USHORT							high_freq_area_adj_coeff;				/**< coefficient of Edge level adjustment parameter for high frequency area.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@EDGCATHA	*/
	UCHAR							test_para_1;							/**< Test parameter1. Please do not set a value other than 0xFF.	*/
	UCHAR							test_para_2;							/**< Test parameter2. Please do not set a value other than 0x09.	*/
} T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ;

typedef struct {
	ULONG	PZOFST;				/**< 2840_(9004 - 9007h) */
} T_IM_PRO_RDMA_PZSFT_ADDR;

/** RDMA I/F CAG register address information
*/
typedef struct {
	ULONG	CAGMD;				/**< 2840_(9818 - 981Bh) */
	ULONG	RBR;				/**< 2840_(981C - 981Fh) */
	ULONG	ABOARV; 			/**< 2840_(9820 - 9823h) */
	ULONG	ABOARH; 			/**< 2840_(9824 - 9827h) */
	ULONG	ABOAGV; 			/**< 2840_(9828 - 982Bh) */
	ULONG	ABOAGH; 			/**< 2840_(982C - 982Fh) */
	ULONG	ABOABV; 			/**< 2840_(9830 - 9833h) */
	ULONG	ABOABH; 			/**< 2840_(9834 - 9837h) */
	ULONG	ABGAR;				/**< 2840_(9838 - 983Bh) */
	ULONG	ABGAG;				/**< 2840_(983C - 983Fh) */
	ULONG	ABGAB;				/**< 2840_(9840 - 9843h) */
	ULONG	ABLRV;				/**< 2840_(9844 - 9847h) */
	ULONG	ABLRH;				/**< 2840_(9848 - 984Bh) */
	ULONG	ABLGV;				/**< 2840_(984C - 984Fh) */
	ULONG	ABLGH;				/**< 2840_(9850 - 9853h) */
	ULONG	ABLBV;				/**< 2840_(9854 - 9857h) */
	ULONG	ABLBH;				/**< 2840_(9858 - 985Bh) */
	ULONG	ABOFSRV;			/**< 2840_(985C - 985Fh) */
	ULONG	ABOFSRH;			/**< 2840_(9860 - 9863h) */
	ULONG	ABOFSGV;			/**< 2840_(9864 - 9867h) */
	ULONG	ABOFSGH;			/**< 2840_(9868 - 986Bh) */
	ULONG	ABOFSBV;			/**< 2840_(986C - 986Fh) */
	ULONG	ABOFSBH;			/**< 2840_(9870 - 9873h) */
	ULONG	ABNLTHR1;			/**< 2840_(9874 - 9877h) */
	ULONG	ABNLTHG1;			/**< 2840_(9878 - 987Bh) */
	ULONG	ABNLTHB1;			/**< 2840_(987C - 987Fh) */
	ULONG	ABNLGAR1;			/**< 2840_(9880 - 9883h) */
	ULONG	ABNLGAG1;			/**< 2840_(9884 - 9887h) */
	ULONG	ABNLGAB1;			/**< 2840_(9888 - 988Bh) */
	ULONG	ABNLTHR2;			/**< 2840_(988C - 988Fh) */
	ULONG	ABNLTHG2;			/**< 2840_(9890 - 9893h) */
	ULONG	ABNLTHB2;			/**< 2840_(9894 - 9897h) */
	ULONG	ABNLGAR2;			/**< 2840_(9898 - 989Bh) */
	ULONG	ABNLGAG2;			/**< 2840_(989C - 989Fh) */
	ULONG	ABNLGAB2;			/**< 2840_(98A0 - 98A3h) */
	ULONG	ABNLTHR3;			/**< 2840_(98A4 - 98A7h) */
	ULONG	ABNLTHG3;			/**< 2840_(98A8 - 98ABh) */
	ULONG	ABNLTHB3;			/**< 2840_(98AC - 98AFh) */
	ULONG	ABNLGAR3;			/**< 2840_(98B0 - 98B3h) */
	ULONG	ABNLGAG3;			/**< 2840_(98B4 - 98B7h) */
	ULONG	ABNLGAB3;			/**< 2840_(98B8 - 98BBh) */
	ULONG	ABNLTHR4;			/**< 2840_(98BC - 98BFh) */
	ULONG	ABNLTHG4;			/**< 2840_(98C0 - 98C3h) */
	ULONG	ABNLTHB4;			/**< 2840_(98C4 - 98C7h) */
	ULONG	ABNLGAR4;			/**< 2840_(98C8 - 98CBh) */
	ULONG	ABNLGAG4;			/**< 2840_(98CC - 98CFh) */
	ULONG	ABNLGAB4;			/**< 2840_(98D0 - 98D3h) */
	ULONG	BFGLMT; 			/**< 2840_(98D4 - 98D7h) */
	ULONG	BFGTH;				/**< 2840_(98D8 - 98DBh) */
} T_IM_PRO_RDMA_CAG_ADDR;

/** RDMA I/F ELF register address information
*/
typedef struct {
	ULONG	ELFCTL; 			/**< 2841_(0420 - 0423h) */
	ULONG	ELFZP;				/**< 2841_(0424 - 0427h) */
	ULONG	ELFL1;				/**< 2841_(0428 - 042Bh) */
	ULONG	ELFL2;				/**< 2841_(042C - 042Fh) */
	ULONG	ANBOR1;				/**< 2841_(0430 - 0433h) */
	ULONG	ANBOR2;				/**< 2841_(0434 - 0437h) */
	ULONG	ANBKR1;				/**< 2841_(0438 - 043Bh) */
	ULONG	ANBKR2;				/**< 2841_(043C - 043Fh) */
	ULONG	ANBDR1;				/**< 2841_(0440 - 0443h) */
	ULONG	ANBDR2;				/**< 2841_(0444 - 0447h) */
	ULONG	ANBOG1;				/**< 2841_(0448 - 044Bh) */
	ULONG	ANBOG2;				/**< 2841_(044C - 044Fh) */
	ULONG	ANBKG1;				/**< 2841_(0450 - 0453h) */
	ULONG	ANBKG2;				/**< 2841_(0454 - 0457h) */
	ULONG	ANBDG1;				/**< 2841_(0458 - 045Bh) */
	ULONG	ANBDG2;				/**< 2841_(045C - 045Fh) */
	ULONG	ANBOB1;				/**< 2841_(0460 - 0463h) */
	ULONG	ANBOB2;				/**< 2841_(0464 - 0467h) */
	ULONG	ANBKB1;				/**< 2841_(0468 - 046Bh) */
	ULONG	ANBKB2;				/**< 2841_(046C - 046Fh) */
	ULONG	ANBDB1;				/**< 2841_(0470 - 0473h) */
	ULONG	ANBDB2;				/**< 2841_(0474 - 0477h) */
	ULONG	LGTW1;				/**< 2841_(0478 - 047Bh) */
	ULONG	LGTW2;				/**< 2841_(047C - 047Fh) */
	ULONG	LGT;				/**< 2841_(0480 - 0483h) */
	ULONG	LGTE;				/**< 2841_(0484 - 0487h) */
	ULONG	EDG2ANBA;			/**< 2841_(0488 - 048Bh) */
	ULONG	EDGSCLA;			/**< 2841_(048C - 048Fh) */
	ULONG	EDG2ANBB;			/**< 2841_(0490 - 0493h) */
	ULONG	EDGSCLB;			/**< 2841_(0494 - 0497h) */
	ULONG	EDG2ANBC;			/**< 2841_(0498 - 049Bh) */
	ULONG	EDGSCLC;			/**< 2841_(049C - 049Fh) */
	ULONG	EFTH1;				/**< 2841_(04A0 - 04A3h) */
	ULONG	EFTH2;				/**< 2841_(04A4 - 04A7h) */
	ULONG	LFTH;				/**< 2841_(04A8 - 04ABh) */
	ULONG	ELCOME; 			/**< 2841_(04AC - 04AFh) */
	ULONG	ELCOMEN;			/**< 2841_(04B0 - 04B3h) */
	ULONG	A1S5E1;				/**< 2841_(04B8 - 04BBh) */
	ULONG	A1S5E2;				/**< 2841_(04BC - 04BFh) */
	ULONG	A1S5L11; 			/**< 2841_(04C0 - 04C3h) */
	ULONG	A1S5L12; 			/**< 2841_(04C4 - 04C7h) */
	ULONG	A1S5L21; 			/**< 2841_(04C8 - 04CBh) */
	ULONG	A1S5L22; 			/**< 2841_(04CC - 04CFh) */
	ULONG	A1S5L31; 			/**< 2841_(04D0 - 04D3h) */
	ULONG	A1S5L32; 			/**< 2841_(04D4 - 04D7h) */
	ULONG	A1S5L41; 			/**< 2841_(04D8 - 04DBh) */
	ULONG	A1S5L42; 			/**< 2841_(04DC - 04DFh) */
	ULONG	NR1S5RGB1;			/**< 2841_(04E0 - 04E3h) */
	ULONG	NR1S5RGB2;			/**< 2841_(04E4 - 04E7h) */
	ULONG	NS1S5LM;			/**< 2841_(04E8 - 04EBh) */
	ULONG	A5S9E1;				/**< 2841_(04F0 - 04F3h) */
	ULONG	A5S9E2;				/**< 2841_(04F4 - 04F7h) */
	ULONG	A5S9L11;			/**< 2841_(04F8 - 04FBh) */
	ULONG	A5S9L12;			/**< 2841_(04FC - 04FFh) */
	ULONG	A5S9L21;			/**< 2841_(0500 - 0503h) */
	ULONG	A5S9L22;			/**< 2841_(0504 - 0507h) */
	ULONG	A5S9L31;			/**< 2841_(0508 - 050Bh) */
	ULONG	A5S9L32;			/**< 2841_(050C - 050Fh) */
	ULONG	A5S9L41;			/**< 2841_(0510 - 0513h) */
	ULONG	A5S9L42;			/**< 2841_(0514 - 0517h) */
	ULONG	NR5S9RGB1;			/**< 2841_(0518 - 051Bh) */
	ULONG	NR5S9RGB2;			/**< 2841_(051C - 051Fh) */
	ULONG	NS5S9LM;			/**< 2841_(0520 - 0523h) */
	ULONG	FS9W1;				/**< 2841_(0528 - 052Bh) */
	ULONG	FS9W2;				/**< 2841_(052C - 052Fh) */
	ULONG	FS9YC1;				/**< 2841_(0540 - 0543h) */
	ULONG	FS9YC2;				/**< 2841_(0544 - 0547h) */
	ULONG	FS9YC3;				/**< 2841_(0548 - 054Bh) */
	ULONG	FS9YC4;				/**< 2841_(054C - 054Fh) */
	ULONG	FS9YC5;				/**< 2841_(0550 - 0553h) */
	ULONG	FASTR;				/**< 2841_(0560 - 0563h) */
	ULONG	CRVAF;				/**< 2841_(0564 - 0567h) */
	ULONG	FCRVABTOF;			/**< 2841_(0568 - 056Bh) */
	ULONG	FCRVABTGA;			/**< 2841_(056C - 056Fh) */
	ULONG	FCRVABTBD;			/**< 2841_(0570 - 0573h) */
	ULONG	FCRVABTCP;			/**< 2841_(0574 - 0577h) */
	ULONG	FYABTGA;			/**< 2841_(0578 - 057Bh) */
	ULONG	FYABTBD;			/**< 2841_(057C - 057Fh) */
	ULONG	FYABTCLP;			/**< 2841_(0580 - 0583h) */
	ULONG	FAEHH;				/**< 2841_(0584 - 0587h) */
	ULONG	FBSTR;				/**< 2841_(0588 - 058Bh) */
	ULONG	CRVBF;				/**< 2841_(058C - 058Fh) */
	ULONG	FCRVBBTOF;			/**< 2841_(0590 - 0593h) */
	ULONG	FCRVBBTGA;			/**< 2841_(0594 - 0597h) */
	ULONG	FCRVBBTBD;			/**< 2841_(0598 - 059Bh) */
	ULONG	FCRVBBTCP;			/**< 2841_(059C - 059Fh) */
	ULONG	FYBBTGA;			/**< 2841_(05A0 - 05A3h) */
	ULONG	FYBBTBD;			/**< 2841_(05A4 - 05A7h) */
	ULONG	FYBBTCLP;			/**< 2841_(05A8 - 05ABh) */
	ULONG	FBEHH;				/**< 2841_(05AC - 05AFh) */
	ULONG	ELFMNNRRL;			/**< 2841_(05B0 - 05B3h) */
	ULONG	ELFMNNRGL;			/**< 2841_(05B4 - 05B7h) */
	ULONG	ELFMNNRBL;			/**< 2841_(05B8 - 05BBh) */
	ULONG	ELFAFNR;			/**< 2841_(05BC - 05BFh) */
	ULONG	ZELADCMD;			/**< 2841_(05C0 - 05C3h) */
	ULONG	ZANBOR1;			/**< 2841_(05C8 - 05CBh) */
	ULONG	ZANBOR2;			/**< 2841_(05CC - 05CFh) */
	ULONG	ZANBKR1;			/**< 2841_(05D0 - 05D3h) */
	ULONG	ZANBKR2;			/**< 2841_(05D4 - 05D7h) */
	ULONG	ZANBDR1;			/**< 2841_(05D8 - 05DBh) */
	ULONG	ZANBDR2;			/**< 2841_(05DC - 05DFh) */
	ULONG	ZANBOG1;			/**< 2841_(05E0 - 05E3h) */
	ULONG	ZANBOG2;			/**< 2841_(05E4 - 05E7h) */
	ULONG	ZANBKG1;			/**< 2841_(05E8 - 05EBh) */
	ULONG	ZANBKG2;			/**< 2841_(05EC - 05EFh) */
	ULONG	ZANBDG1;			/**< 2841_(05F0 - 05F3h) */
	ULONG	ZANBDG2;			/**< 2841_(05F4 - 05F7h) */
	ULONG	ZANBOB1;			/**< 2841_(05F8 - 05FBh) */
	ULONG	ZANBOB2;			/**< 2841_(05FC - 05FFh) */
	ULONG	ZANBKB1;			/**< 2841_(0600 - 0603h) */
	ULONG	ZANBKB2;			/**< 2841_(0604 - 0607h) */
	ULONG	ZANBDB1;			/**< 2841_(0608 - 060Bh) */
	ULONG	ZANBDB2;			/**< 2841_(060C - 060Fh) */
	ULONG	ZLGTW1;				/**< 2841_(0610 - 0613h) */
	ULONG	ZLGTW2;				/**< 2841_(0614 - 0617h) */
	ULONG	ZLGT;				/**< 2841_(0618 - 061Bh) */
	ULONG	ZLGTE;				/**< 2841_(061C - 061Fh) */
	ULONG	ZEDG2ANBA;			/**< 2841_(0620 - 0623h) */
	ULONG	ZEDGSCLA;			/**< 2841_(0624 - 0627h) */
	ULONG	ZEDG2ANBB;			/**< 2841_(0628 - 062Bh) */
	ULONG	ZEDGSCLB;			/**< 2841_(062C - 062Fh) */
	ULONG	ZALNGE1; 			/**< 2841_(0630 - 0633h) */
	ULONG	ZALNGE2; 			/**< 2841_(0634 - 0637h) */
	ULONG	ZALNG1;				/**< 2841_(0640 - 0643h) */
	ULONG	ZALNG2;				/**< 2841_(0644 - 0647h) */
	ULONG	ZALNG3;				/**< 2841_(0648 - 064Bh) */
	ULONG	ZALNG4;				/**< 2841_(064C - 064Fh) */
	ULONG	ZALNG5;				/**< 2841_(0650 - 0653h) */
	ULONG	ZALNG6;				/**< 2841_(0654 - 0657h) */
	ULONG	ZLFTH;				/**< 2841_(0660 - 0663h) */
	ULONG	ZLCOME; 			/**< 2841_(0664 - 0667h) */
	ULONG	ZLCOMEN;			/**< 2841_(0668 - 066Bh) */
	ULONG	ZNSLNGLM;			/**< 2841_(066C - 066Fh) */
	ULONG	EDGCATH;			/**< 2841_(0684 - 0687h) */
} T_IM_PRO_RDMA_ELF_ADDR;

typedef enum {
	E_IM_PRO_FSHD_CORRECTION_FORMAT_0 = 0,	/**< XXXX.XXXX_XXXX_XXXX	*/
	E_IM_PRO_FSHD_CORRECTION_FORMAT_1		/**< 1+XXXX.XXXX_XXXX_XXXX	*/
} E_IM_PRO_FSHD_CORRECTION_FORMAT;

typedef struct {
	E_IM_PRO_FSHD_LUT_SEL			select_ram;			/**< Selection correction LUT concentric<br>
															target registor	:@@CSSTBL */
	E_IM_PRO_FSHD_CORRECTION_FORMAT	select_format;		/**< Formatting correction factor concentric<br>
															target registor	:@@CSFMT */
	UCHAR							interpolated_val;	/**< Correction factor correction LUT value concentric<br>
															value range		:[0 - 7] <br>
															target registor	:@@CSHDLIR */
	UCHAR							interval_h;			/**< Concentric horizontal adjacent pixel spacing correction<br>
															value range		:[16 - 64] <br>
															target registor	:@@CSHDPARH */
	UCHAR							interval_v;			/**< Adjacent concentric vertical pixel spacing correction<br>
															value range		:[16 - 64] <br>
															target registor	:@@CSHDPARV */
	USHORT							start_address_r;	/**< Concentric correction RAM start address table (pixels R)<br>
															value range		:[pixels R Start Address 10bit] (Multiples of 2)<br>
															target registor	:@@CSTBLSRR */
	USHORT							start_address_gr;	/**< Concentric correction RAM start address table (pixels GR)<br>
															value range		:[pixels GR Start Address 10bit] (Multiples of 2)<br>
															target registor	:@@CSTBLSGR */
	USHORT							start_address_gb;	/**< Concentric correction RAM start address table (pixels GB)<br>
															value range		:[pixels GB Start Address 10bit] (Multiples of 2)<br>
															target registor	:@@CSTBLSGB */
	USHORT							start_address_b;	/**< Concentric correction RAM start address table (pixels B)<br>
															value range		:[pixels B Start Address 10bit] (Multiples of 2)<br>
															target registor	:@@CSTBLSBB */
	USHORT							offset;				/**< Concentric optical center offset correction<br>
															value range		:[0 - 16383] <br>
															target registor	:@@CSHDDO */
	USHORT							clip_value;			/**< Optical center of the concentric maximum clip value correction<br>
															value range		:[0 - 16383] <br>
															target registor	:@@CSHDDM */
	USHORT							pos_h;				/**< Horizontal position the optical center concentric correction<br>
															value range		:[0 - 16383] <br>
															target registor	:@@CSHDOAH */
	USHORT							pos_v;				/**< Vertical position of the optical center concentric correction<br>
															value range		:[0 - 16383] <br>
															target registor	:@@CSHDOAV */
	USHORT							magnification_r;	/**< Magnification correction factor concentric circles (pixels R)<br>
															value range		:[0 - 511] <br>
															target registor	:@@CSARR */
	USHORT							magnification_gr;	/**< Magnification correction factor concentric circles (pixels GR)<br>
															value range		:[0 - 511] <br>
															target registor	:@@CSAGR */
	USHORT							magnification_gb;	/**< Magnification correction factor concentric circles (pixels GB)<br>
															value range		:[0 - 511] <br>
															target registor	:@@CSAGB */
	USHORT							magnification_b	;	/**< Magnification correction factor concentric circles (pixels B)<br>
															value range		:[0 - 511] <br>
															target registor	:@@CSABB */
} T_IM_PRO_FSHD_CONCENTRIC_CTRL;

typedef struct {
	SHORT							shading_blend_0;		/**< Frame shading blend ratio 0<br>
																value range		:[-512 - +511] <br>
																target registor	:@@FSHDBC0 */
	SHORT							shading_blend_1;		/**< Frame shading blend ratio 1<br>
																value range		:[-512 - +511] <br>
																target registor	:@@FSHDBC1 */
} T_IM_PRO_FSHD_BLEND_CTRL;

typedef enum {
	E_IM_PRO_FSHD_FRAME_ONLY = 0,					/**< Frame Only							*/
	E_IM_PRO_FSHD_CONCENTRIC_ONLY,					/**< Concentric Only					*/
	E_IM_PRO_FSHD_FRAME_CONCENTRIC_MULTIPLICATION,	/**< Frame Multiplication Concentric	*/
	E_IM_PRO_FSHD_FRAME_CONCENTRIC_ADDITION			/**< Frame Addition Concentric			*/
} E_IM_PRO_FSHD_SHADING_MODE;

typedef enum {
	E_IM_PRO_FSHD_FSMODE = 0,		/**< According to the setting of bit FSMODE	*/
	E_IM_PRO_FSHD_FRAME,			/**< Only use the correction factor frame	*/
} E_IM_PRO_FSHD_SHADING_MODE_AWB;

typedef enum {
	E_IM_PRO_FSHD_MONTAGE_MODE_OFF = 0,		/**< Montage image processing mode is OFF.	*/
	E_IM_PRO_FSHD_MONTAGE_MODE_ON,			/**< Montage image processing mode is ON.	*/
} E_IM_PRO_FSHD_MONTAGE_MODE;

typedef struct {
	E_IM_PRO_FSHD_SHADING_MODE		correction_mode;		/**< Correction mode<br>
																target registor	:@@FSMODE */
	E_IM_PRO_FSHD_SHADING_MODE_AWB	correction_mode_awb;	/**< Horizontal interpolation pixel unit<br>
																target registor	:@@FWMODE */
	E_IM_PRO_FSHD_MONTAGE_MODE		montage_mode;			/**< Montage mode<br>
																target registor	:@@FSHDPTMD */
	USHORT							clip_r;					/**< Clip surface shading correction value after (R)<br>
																value range		:[0 - 4095] <br>
																target registor	:@@FSULRR */
	USHORT							clip_gr;				/**< Clip surface shading correction value after (GR)<br>
																value range		:[0 - 4095] <br>
																target registor	:@@FSULGR */
	USHORT							clip_gb;				/**< Clip surface shading correction value after (GB)<br>
																value range		:[0 - 4095] <br>
																target registor	:@@FSULGB */
	USHORT							clip_b;					/**< Clip surface shading correction value after (B)<br>
																value range		:[0 - 4095] <br>
																target registor	:@@FSULBB */
} T_IM_PRO_FSHD_COMMON_CTRL;

typedef enum {
	E_IM_PRO_FSHD_SAT_CORRECTION_DIS = 0,	/**< Disable	*/
	E_IM_PRO_FSHD_SAT_CORRECTION_EN			/**< Enable		*/
} E_IM_PRO_FSHD_SAT_CORRECTION;

typedef struct {
	E_IM_PRO_FSHD_CORRECTION_FORMAT	fsctl;					/**< Formatted frame correction factor<br>
																value range		:See @ref E_IM_PRO_FSHD_CORRECTION_FORMAT<br>
																target registor	:@@FSFMT */
	USHORT							frame_horizontal_size;	/**< Frame horizontal size correction factor<br>
																value range		:[4 - 314] 2pixel boundary<br>
																target registor	:@@FSSUBPRH */
	USHORT							frame_vertical_size;	/**< Frame vertical size correction factor<br>
																value range		:[4 - 1122] 2pixel boundary<br>
																target registor	:@@FSSUBPRV */
	USHORT							horizontal_pixel;		/**< Correction of horizontal pixels per frame interpolation<br>
																value range		:[16 - 724] 2pixel boundary<br>
																target registor	:@@FSSUBSPH */
	USHORT							vertical_pixel;			/**< Correction of vertical pixels per frame interpolation<br>
																value range		:[16 - 724] 2pixel boundary<br>
																target registor	:@@FSSUBSPV */
	USHORT							Inverse_base;			/**< Inverse coefficient correction interpolation frame (base unit)<br>
																value range		:[0 - 65535] <br>
																target registor	:@@FSSUBDRM */
	USHORT							Inverse_exponent;		/**< Inverse coefficient correction interpolation frame (Exponent part)<br>
																value range		:[0 - 11] <br>
																target registor	:@@FSSUBDRE */
	USHORT							montage_pos_h;			/**< horizontal montage position of the montage image in units of 2 pixels<br>
																value range		:[4 - 2496] 2pixel boundary<br>
																Set the value with reference to the left side of the setting processing window<br>
																and inside the setting value range of FSHDHW and satisfy the relationship shown below.<br>
																Moreover, make sure to set FSHDPTMD=1 to use this setting. <br>
																FSSUBSTH + FSHDHWPH = n * FSSUBSPH + 2<br>
																※n: integer<br>
																target registor	:@@FSHDHWPH */
	USHORT							start_pos_h;			/**< Horizontal start position correction factor frame<br>
																value range		:[0 - 722] 2pixel boundary<br>
																target registor	:@@FSSUBSTH */
	USHORT							start_pos_v;			/**< Vertical start position correction factor frame<br>
																value range		:[0 - 722] 2pixel boundary<br>
																target registor	:@@FSSUBSTV */
	USHORT							magnification_r;		/**< Magnification correction factor frame (pixel R)<br>
																value range		:[0 - 511] <br>
																target registor	:@@FSARR */
	USHORT							magnification_gr;		/**< Magnification correction factor frame (pixel GR)<br>
																value range		:[0 - 511] <br>
																target registor	:@@FSAGR */
	USHORT							magnification_gb;		/**< Magnification correction factor frame (pixel GB)<br>
																value range		:[0 - 511] <br>
																target registor	:@@FSAGB */
	USHORT							magnification_b;		/**< Magnification correction factor frame (pixel B)<br>
																value range		:[0 - 511] <br>
																target registor	:@@FSABB */
	E_IM_PRO_FSHD_SAT_CORRECTION	sat_correction_enabled;	/**< Saturation correction Enable/Disable<br>
																target registor	:@@FSHCEN */
	USHORT							sat_slope_gain[4];		/**< SLOPE gain for Saturation correction.<br>
																value range		:[0 - 4095(=255.9375)]<br>
																target registor	:[0]@@FSSLPRR, [1]@@FSSLPGR, [2]@@FSSLPGB, [3]@@FSSLPBB */
} T_IM_PRO_FSHD_FRAME_CTRL;

typedef struct {
	USHORT		pos_x;	/**< Start position x */
	USHORT		pos_y;	/**< Start position y */
	USHORT		width;	/**< Width of macro processing area */
	USHORT		lines;	/**< Line of macro processing area */
} T_IM_PRO_AREA_INFO;

struct _ImPro {
	KObject parent;
};

KConstType 		    im_pro_get_type(void);
ImPro*		            	im_pro_new(void);

extern	INT32 im_pro_elf_ctrl_nsl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_NSL_CTRL* nsl_ctrl );
extern	INT32 im_pro_elf_set_a0_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg );
extern	INT32 im_pro_elf_set_nsl_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg );
extern	INT32 im_pro_get_rdmaaddr_elf_cntl( E_IM_PRO_UNIT_NUM unit_no, const T_IM_PRO_RDMA_ELF_ADDR** addr );
extern	INT32 im_pro_elf_set_edge_adj( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ* edge_adj );
extern	INT32 im_pro_fshd_start( E_IM_PRO_UNIT_NUM unit_no );
extern	INT32 im_pro_fshd_stop( E_IM_PRO_UNIT_NUM unit_no, UCHAR force );
extern	INT32 im_pro_fshd_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_COMMON_CTRL* fshd_ctrl );
extern	INT32 im_pro_fshd_set_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg );
extern	INT32 im_pro_fshd_set_area( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_AREA_INFO* fshd_area );
extern	INT32 im_pro_fshd_set_blend( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_BLEND_CTRL* blend_ctrl );
extern	INT32 im_pro_fshd_set_frame( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_FRAME_CTRL* fshd_ctrl );
extern	INT32 im_pro_fshd_set_concentric( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_CONCENTRIC_CTRL* fshd_ctrl );
extern	E_IM_PRO_FSHD_LUT_SEL im_pro_fshd_get_ctbl_number( E_IM_PRO_UNIT_NUM unit_no );
extern	INT32 im_pro_fshd_set_table( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_FSHD_LUT_SEL tbl_sel, T_IM_PRO_FSHD_TABLE* shd_tbl );
extern	INT32 im_pro_fshd_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unit_no, USHORT req_interval_clk );
extern	INT32 im_pro_get_rdmaaddr_fshd_cntl( E_IM_PRO_UNIT_NUM unit_no, const T_IM_PRO_RDMA_FSHD_ADDR** addr );
extern	INT32 im_pro_get_rdmaaddr_fshd_ctbl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_FSHD_LUT_SEL tbl_sel, const T_IM_PRO_RDMA_FSHD_CTBL_ADDR** addr );


#endif /* __IM_PRO_H__ */









