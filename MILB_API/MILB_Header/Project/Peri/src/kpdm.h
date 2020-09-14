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


typedef struct _KPdm 				KPdm;
typedef struct _KPdmPrivate 	KPdmPrivate;


struct _KPdm
{
	KObject parent;
};

/*	structure of PDM_CORE_CFG	*/
typedef union _IoPdmCorecfg
{
	kulong word;
	struct
	{
		kulong pdmcoreEn :1;
		kulong softMute :1;
		kulong sCycles :3;
		kulong hpcutoff :4;
		kulong adchpd :1;
		kulong sincRate :7;
		kulong mclkdiv :6;
		kulong pgaL :4;
		kulong pgaR :4;
		kulong lrswap :1;
	} bit;
} IoPdmCorecfg;

/*	structure of PDM_DMA_CFG	*/
typedef union _IoPdmDmacfg
{
	kulong word;
	struct
	{
		kulong dmaEn :1;
		kulong pcmWdlen :2;
		kulong pcmChset :2;
		kulong :1;
		kulong dmaBurstlen :2;
		kulong :2;
		kulong dmaFlush :1;
		kulong :1;
		kulong clrIrqDma0 :1;
		kulong clrIrqDma1 :1;
		kulong :1;
		kulong clrIrqFfovf :1;
		kulong :8;
		kulong sincShift :4;
		kulong dmickDly :2;
		kulong :2;
	} bit;
} IoPdmDmacfg;

/*	structure of PDM_DMA_LEN	*/
typedef union _IoPdmDmalen
{
	kulong word;
	struct
	{
		kulong :8;
		kulong dmaTsize :8;
		kulong dmaTtsize :15;
		kulong :1;
	} bit;
} IoPdmDmalen;

/*	structure of PDM_DMA_DST_ADDR	*/
typedef union _IoPdmDmadstaddr
{
	kulong word;
	struct
	{
		kulong :2;
		kulong dmaAddr :30;
	} bit;
} IoPdmDmadstaddr;

/*	structure of PDM_statUS	*/
typedef union _IoPdmStatus
{
	kulong word;
	struct
	{
		kulong ffovfIntReg :1;
		kulong :1;
		kulong dma0IntReg :1;
		kulong dma1IntReg :1;
		kulong :28;
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
	kuchar dmy1e0040181e0043ff[0x1E004400 - 0x1E004018];
} IoPdm;


/* addr 1E004000h-	*/
extern volatile IoPdm ioPdm[2];


KConstType k_pdm_get_type(void);
KPdm* k_pdm_new(void);


#endif/*__K_PDM_H__*/

