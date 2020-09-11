/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :陈倩
 *@brief             :kpdm
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


#ifndef __K_PDM_H__
#define __K_PDM_H__


#include <klib.h>


#define K_TYPE_PDM				(k_pdm_get_type())
#define K_PDM(obj)					(K_TYPE_CHECK_INSTANCE_CAST((obj), KPdm))
#define K_IS_PDM(obj)				(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_PDM))


typedef struct _KPdm KPdm;
typedef struct _KPdmPrivate KPdmPrivate;


struct _KPdm
{
	KObject parent;
};

/*	structure of PDM_CORE_CFG	*/
typedef union _IoPdmCorecfg
{
	unsigned long word;
	struct
	{
		unsigned long pdmcoreEn :1;
		unsigned long softMute :1;
		unsigned long sCycles :3;
		unsigned long hpcutoff :4;
		unsigned long adchpd :1;
		unsigned long sincRate :7;
		unsigned long mclkdiv :6;
		unsigned long pgaL :4;
		unsigned long pgaR :4;
		unsigned long lrswap :1;
	} bit;
} IoPdmCorecfg;

/*	structure of PDM_DMA_CFG	*/
typedef union _IoPdmDmacfg
{
	unsigned long word;
	struct
	{
		unsigned long dmaEn :1;
		unsigned long pcmWdlen :2;
		unsigned long pcmChset :2;
		unsigned long :1;
		unsigned long dmaBurstlen :2;
		unsigned long :2;
		unsigned long dmaFlush :1;
		unsigned long :1;
		unsigned long clrIrqDma0 :1;
		unsigned long clrIrqDma1 :1;
		unsigned long :1;
		unsigned long clrIrqFfovf :1;
		unsigned long :8;
		unsigned long sincShift :4;
		unsigned long dmickDly :2;
		unsigned long :2;
	} bit;
} IoPdmDmacfg;

/*	structure of PDM_DMA_LEN	*/
typedef union _IoPdmDmalen
{
	unsigned long word;
	struct
	{
		unsigned long :8;
		unsigned long dmaTsize :8;
		unsigned long dmaTtsize :15;
		unsigned long :1;
	} bit;
} IoPdmDmalen;

/*	structure of PDM_DMA_DST_ADDR	*/
typedef union _IoPdmDmadstaddr
{
	unsigned long word;
	struct
	{
		unsigned long :2;
		unsigned long dmaAddr :30;
	} bit;
} IoPdmDmadstaddr;

/*	structure of PDM_statUS	*/
typedef union _IoPdmStatus
{
	unsigned long word;
	struct
	{
		unsigned long ffovfIntReg :1;
		unsigned long :1;
		unsigned long dma0IntReg :1;
		unsigned long dma1IntReg :1;
		unsigned long :28;
	} bit;
} IoPdmStatus;

/* Define I/O Mapping PDM */
/* PDM ch0	(1E00_(4000 - 43FFh)*/
/* PDM ch1	(1E00_(4400 - 47FFh)*/
typedef struct _IoPdm
{
	/* 1E00_(4000 - 4003h)	*/
	IoPdmCorecfg coreCfg;
	/* 1E00_(4004 - 4007h)	*/
	IoPdmDmacfg dmaCfg;
	/* 1E00_(4008 - 400Bh)	*/
	IoPdmDmalen dmaLen;
	/* 1E00_(400C - 400Fh)	*/
	IoPdmDmadstaddr dma0DstAddr;
	/* 1E00_(4010 - 4013h)	*/
	IoPdmDmadstaddr dma1DstAddr;
	/* 1E00_(4014 - 4017h)	*/
	IoPdmStatus status;
	/* 1E00_(4018 - 43FFh)	*/
	unsigned char dmy1e0040181e0043ff[0x1E004400 - 0x1E004018];
} IoPdm;


/* addr 1E004000h-	*/
extern volatile IoPdm ioPdm[2];


KConstType k_pdm_get_type(void);
KPdm* k_pdm_new(void);


#endif/*__K_PDM_H__*/

