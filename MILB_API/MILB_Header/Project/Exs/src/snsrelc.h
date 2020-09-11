/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-05
*@author              :于孟孟
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#ifndef __SNS_RELC_H__
#define __SNS_RELC_H__


#include <klib.h>


#define SNS_TYPE_RELC                  (sns_relc_get_type())
#define SNS_RELC(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, SnsRelc))
#define SNS_IS_RELC(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SNS_TYPE_RELC))


typedef union _IoRelcReset  			IoRelcReset;
typedef union _IoRelcMode1 			IoRelcMode1;
typedef union _IoRelcMode2  		IoRelcMode2;
typedef union _IoRelcInten 			IoRelcInten;
typedef union _IoRelcIntst  			IoRelcIntst;
typedef union _IoRelcStatus  			IoRelcStatus;
typedef union _IoRelcBufSize  		IoRelcBufSize;
typedef union _IoRelcErrorNum  	IoRelcErrorNum;
typedef union _IoRelcReadByte  	IoRelcReadByte;
typedef union _IoRelcWriteByte  	IoRelcWriteByte;
typedef union _IoRelcBlock  			IoRelcBlock;
typedef struct _IoRelc  					IoRelc;
typedef struct _SnsRelc 					SnsRelc;
typedef struct _SnsRelcPrivate 		SnsRelcPrivate;

// structure of RELC RESET		(1B03_0000h)
union _IoRelcReset {
    unsigned long word;
    struct {
		unsigned long	srst	:1;
		unsigned long			:31;	// reserved
    }bit;
};

// structure of RELC MODE1		(1B03_0004h)
union _IoRelcMode1 {
    unsigned long word;
    struct {
		unsigned long	prun	:1;
		unsigned long	crmd	:1;
		unsigned long	dsmd	:1;
		unsigned long				:29;	// reserved
    }bit;
};

// structure of RELC MODE2		(1B03_0008h)
union _IoRelcMode2 {
    unsigned long word;
    struct {
		unsigned long	imax	:1;
		unsigned long	omax	:1;
		unsigned long	iaai		:1;
		unsigned long	oaai		:1;
		unsigned long				:28;	// reserved
    }bit;
};

// structure of RELC INTEN		(1B03_000Ch)
union _IoRelcInten {
    unsigned long word;
    struct {
		unsigned long	sint	:1;
		unsigned long	fint	:1;
		unsigned long	eint	:1;
		unsigned long	cint	:1;
		unsigned long			:28;	// reserved
    }bit;
};

// structure of RELC INTST		(1B03_0010h)
union _IoRelcIntst {
    unsigned long word;
    struct {
		unsigned long	__sins	:1;
		unsigned long	__fins	:1;
		unsigned long	__eins	:1;
		unsigned long	__cins	:1;
		unsigned long				:28;	// reserved
    }bit;
};

// structure of RELC STATUS		(1B03_0014h)
union _IoRelcStatus {
    unsigned long word;
    struct {
		unsigned long	runs	:1;
		unsigned long	slps	:1;
		unsigned long	fins	:1;
		unsigned long			:1;		// reserved
		unsigned long	sres	:3;
		unsigned long			:1;		// reserved
		unsigned long	eflg	:1;
		unsigned long			:23;	// reserved
    }bit;
};

// structure of RELC BUF SIZE	(1B03_0034h)
union _IoRelcBufSize {
    unsigned long word;
    struct {
		unsigned long	ibfs	:3;
		unsigned long			:5;		// reserved
		unsigned long	rbfs	:1;
		unsigned long			:23;	// reserved
    }bit;
};

// structure of RELC ERROR NUM	(1B03_0038h)
union _IoRelcErrorNum {
    unsigned long word;
    struct {
		unsigned long	enum1		:16;
		unsigned long					:16;		// reserved
    }bit;
};

// structure of RELC READ BYTE	(1B03_003Ch)
union _IoRelcReadByte {
    unsigned long word;
    struct {
		unsigned long	drnm	:16;
		unsigned long				:16;		// reserved
    }bit;
};

// structure of RELC WRITE BYTE	(1B03_0040h)
union _IoRelcWriteByte {
    unsigned long word;
    struct {
		unsigned long	dwnm	:16;
		unsigned long				:16;		// reserved
    }bit;
};

// structure of RELC BLOCK		(1B03_0044h)
union _IoRelcBlock {
    unsigned long word;
    struct {
		unsigned long	blkn	:16;
		unsigned long			:16;		// reserved
    }bit;
};


struct _IoRelc {
	IoRelcReset						relcReset;					// 1B03_0000h
	IoRelcMode1					relcMode1;					// 1B03_0004h
	IoRelcMode2					relcMode2;					// 1B03_0008h
	IoRelcInten						relcIntEn;				// 1B03_000Ch
	IoRelcIntst						relcIntSt;				// 1B03_0010h
	IoRelcStatus					relcStatus;				// 1B03_0014h
	unsigned long				relcInStartAddr;			// 1B03_0018h
	unsigned long				relcInEndAddr;			// 1B03_001Ch
	unsigned long				relcOutStartAddr;		// 1B03_0020h
	unsigned long				relcOutEndAddr;			// 1B03_0024h
	unsigned long				relcDescriptorAddr;		// 1B03_0028h
	unsigned long				relcSeqNum;				// 1B03_002Ch
	unsigned long				relcSeqCnt;				// 1B03_0030h
	IoRelcBufSize					relcBufSize;				// 1B03_0034h
	IoRelcErrorNum				relcErrorNum;				// 1B03_0038h
	IoRelcReadByte				relcReadByte;				// 1B03_003Ch
	IoRelcWriteByte				relcWriteByte;			// 1B03_0040h
	IoRelcBlock						relcBlock;					// 1B03_0044h
	unsigned long				relcInputByte;			// 1B03_0048h
	unsigned long				relcOutputByte;			// 1B03_004Ch
	unsigned char				dmy0000005000000fff[0x00001000-0x00000050];
	unsigned long				relcInputBufDataMirror;	// 1B03_1000h
	unsigned char				dmy00001004000017ff[0x00001800-0x00001004];
	unsigned long				relcInputBufData;		// 1B03_1800h
	unsigned char				dmy0000180400001fff[0x00002000-0x00001804];
	unsigned long				relcRefBufData;			// 1B03_2000h
	unsigned char				dmy0000200400003fff[0x00004000-0x00002004];
};

struct _SnsRelc
{
	KObject parent;
};


extern volatile IoRelc	ioRelc;					// addr 1B03_0000h-


KConstType sns_relc_get_type(void);
SnsRelc* 		sns_relc_new(void);
SnsRelc* 		sns_relc_get(void);

#endif /* __SNS_RELC_H__ */
