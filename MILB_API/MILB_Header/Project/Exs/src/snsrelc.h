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
    kulong word;
    struct {
		kulong	srst	:1;
		kulong			:31;	// reserved
    }bit;
};

// structure of RELC MODE1		(1B03_0004h)
union _IoRelcMode1 {
    kulong word;
    struct {
		kulong	prun	:1;
		kulong	crmd	:1;
		kulong	dsmd	:1;
		kulong				:29;	// reserved
    }bit;
};

// structure of RELC MODE2		(1B03_0008h)
union _IoRelcMode2 {
    kulong word;
    struct {
		kulong	imax	:1;
		kulong	omax	:1;
		kulong	iaai		:1;
		kulong	oaai		:1;
		kulong				:28;	// reserved
    }bit;
};

// structure of RELC INTEN		(1B03_000Ch)
union _IoRelcInten {
    kulong word;
    struct {
		kulong	sint	:1;
		kulong	fint	:1;
		kulong	eint	:1;
		kulong	cint	:1;
		kulong			:28;	// reserved
    }bit;
};

// structure of RELC INTST		(1B03_0010h)
union _IoRelcIntst {
    kulong word;
    struct {
		kulong	__sins	:1;
		kulong	__fins	:1;
		kulong	__eins	:1;
		kulong	__cins	:1;
		kulong				:28;	// reserved
    }bit;
};

// structure of RELC STATUS		(1B03_0014h)
union _IoRelcStatus {
    kulong word;
    struct {
		kulong	runs	:1;
		kulong	slps	:1;
		kulong	fins	:1;
		kulong			:1;		// reserved
		kulong	sres	:3;
		kulong			:1;		// reserved
		kulong	eflg	:1;
		kulong			:23;	// reserved
    }bit;
};

// structure of RELC BUF SIZE	(1B03_0034h)
union _IoRelcBufSize {
    kulong word;
    struct {
		kulong	ibfs	:3;
		kulong			:5;		// reserved
		kulong	rbfs	:1;
		kulong			:23;	// reserved
    }bit;
};

// structure of RELC ERROR NUM	(1B03_0038h)
union _IoRelcErrorNum {
    kulong word;
    struct {
		kulong	enum1		:16;
		kulong					:16;		// reserved
    }bit;
};

// structure of RELC READ BYTE	(1B03_003Ch)
union _IoRelcReadByte {
    kulong word;
    struct {
		kulong	drnm	:16;
		kulong				:16;		// reserved
    }bit;
};

// structure of RELC WRITE BYTE	(1B03_0040h)
union _IoRelcWriteByte {
    kulong word;
    struct {
		kulong	dwnm	:16;
		kulong				:16;		// reserved
    }bit;
};

// structure of RELC BLOCK		(1B03_0044h)
union _IoRelcBlock {
    kulong word;
    struct {
		kulong	blkn	:16;
		kulong			:16;		// reserved
    }bit;
};


struct _IoRelc {
	IoRelcReset						relcReset;					// 1B03_0000h
	IoRelcMode1					relcMode1;					// 1B03_0004h
	IoRelcMode2					relcMode2;					// 1B03_0008h
	IoRelcInten						relcIntEn;				// 1B03_000Ch
	IoRelcIntst						relcIntSt;				// 1B03_0010h
	IoRelcStatus					relcStatus;				// 1B03_0014h
	kulong								relcInStartAddr;			// 1B03_0018h
	kulong								relcInEndAddr;			// 1B03_001Ch
	kulong								relcOutStartAddr;		// 1B03_0020h
	kulong								relcOutEndAddr;			// 1B03_0024h
	kulong								relcDescriptorAddr;		// 1B03_0028h
	kulong								relcSeqNum;				// 1B03_002Ch
	kulong								relcSeqCnt;				// 1B03_0030h
	IoRelcBufSize					relcBufSize;				// 1B03_0034h
	IoRelcErrorNum				relcErrorNum;				// 1B03_0038h
	IoRelcReadByte				relcReadByte;				// 1B03_003Ch
	IoRelcWriteByte				relcWriteByte;			// 1B03_0040h
	IoRelcBlock						relcBlock;					// 1B03_0044h
	kulong								relcInputByte;			// 1B03_0048h
	kulong								relcOutputByte;			// 1B03_004Ch
	kuchar								dmy0000005000000fff[0x00001000-0x00000050];
	kulong								relcInputBufDataMirror;	// 1B03_1000h
	kuchar								dmy00001004000017ff[0x00001800-0x00001004];
	kulong								relcInputBufData;		// 1B03_1800h
	kuchar								dmy0000180400001fff[0x00002000-0x00001804];
	kulong								relcRefBufData;			// 1B03_2000h
	kuchar								dmy0000200400003fff[0x00004000-0x00002004];
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
