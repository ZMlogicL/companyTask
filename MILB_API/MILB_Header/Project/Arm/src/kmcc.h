/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :Definition MCC (Multi-Core Controller) I/O register
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */


#ifndef __K_MCC_H__
#define __K_MCC_H__


#include <klib.h>


#define K_TYPE_MCC	        (k_mcc_get_type())
#define K_MCC(obj)	        (K_TYPE_CHECK_INSTANCE_CAST((obj), KMcc))
#define K_IS_MCC(obj)	    (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_MCC))

typedef struct _KMcc        KMcc;
typedef struct _KMccPrivate KMccPrivate;

typedef struct _IoMcc       IoMcc;

typedef union _IoMcswfi     IoMcswfi;


extern volatile IoMcc ioMcc;


struct _KMcc
{
    KObject parent;
};


/* structure of Standby WFI monitor register    (1C26_A010h) */
union _IoMcswfi
{
    kulong word;
    struct
    {
        kulong ca70Wfi :1;
        kulong ca71Wfi :1;
        kulong ca72Wfi :1;
        kulong ca73Wfi :1;
        kulong ca70Wfe :1;
        kulong ca71Wfe :1;
        kulong ca72Wfe :1;
        kulong ca73Wfe :1;
        kulong :24;
    } bit;
};


/*  MCC register                            */
struct _IoMcc
{
    kuchar dmyA000A00f[0xA010 - 0xA000]; // 1C26_(A000 - A00Fh) Reserved
    IoMcswfi mcswfi;                         // 1C26_(A010 - A013h) Standby WFI and WFE monitor Register
    kuchar dmyA014Afff[0xB000 - 0xA014]; // 1C26_(A014 - AFFFh) Reserved
};


KConstType  k_mcc_get_type(void);
KMcc*       k_mcc_new(void);


#endif/*__K_MCC_H__*/
