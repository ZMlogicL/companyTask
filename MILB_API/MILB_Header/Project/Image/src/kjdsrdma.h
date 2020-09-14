/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-05
 *@author            :郑蛘钊
 *@brief             :kjdsrdma
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_JDSRDMA_H__
#define __K_JDSRDMA_H__

#ifndef __JDSRDMA_REG_H__
#define __JDSRDMA_REG_H__


#include <klib.h>
#include "jdsrdmatopreg.h"
#include "jdsrdmacorereg.h"
#include "jdsproprch.h"


#define K_TYPE_JDSRDMA	        (k_jdsrdma_get_type())
#define K_JDSRDMA(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KJdsrdma))
#define K_IS_JDSRDMA(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_JDSRDMA))


typedef struct _KJdsrdma        KJdsrdma;
typedef struct _KJdsrdmaPrivate KJdsrdmaPrivate;

typedef struct _IoRdma          IoRdma;


struct _KJdsrdma
{
    KObject parent;
};

/* Define i/o mapping */
struct _IoRdma
{
    /* JDSIMG */
    IoRdmaTop rdmaTop; /* 2886_(9000 - 00FFh) */
    IoRdmaCore rdmaCore; /* 2886_(9100 - 01FFh) */
    IoPrch prch0; /* 2886_(9200 - 02FFh) */
    IoPrch prch1; /* 2886_(9300 - 03FFh) */

    kuchar dmy28869400288697ff[0x28869800 - 0x28869400]; /* 2886_9400 - 2886_97FFh */

    kuchar dmy2886980028869fff[0x2886A000 - 0x28869800]; /* 2886_9800 - 2886_9FFFh */
};


extern volatile IoRdma ioRdma;


KConstType  k_jdsrdma_get_type(void);
KJdsrdma*   k_jdsrdma_new(void);


#endif    // #define __JDSRDMA_REG_H__
#endif/*__K_JDSRDMA_H__*/
