/*
 *@Copyright (C) 2010-2020 上海网用软件有限公司
 *@date              :2020-09-04
 *@author            :郑蛘钊
 *@brief             :kexiu
 *@rely              :klib
 *@function
 *设计的主要功能:
 *1、
 *2、
 *@version
 *1.0.0 2020年09月开始开发
 */

#ifndef __K_EXIU_H__
#define __K_EXIU_H__

#include <klib.h>

#define K_TYPE_EXIU	(k_exiu_get_type())
#define K_EXIU(obj)	(K_TYPE_CHECK_INSTANCE_CAST((obj), KExiu))
#define K_IS_EXIU(obj)	(K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_EXIU))

typedef struct _KExiu KExiu;
typedef struct _KExiuPrivate KExiuPrivate;

typedef struct _IoExiu IoExiu;

typedef union _IoExiuEimask IoExiuEimask;
typedef union _IoExiuEisrcsel IoExiuEisrcsel;
typedef union _IoExiuEireqsta IoExiuEireqsta;
typedef union _IoExiuEirawreqsta IoExiuEirawreqsta;
typedef union _IoExiuEireqclr IoExiuEireqclr;
typedef union _IoExiuEilvl IoExiuEilvl;
typedef union _IoExiuEiedg IoExiuEiedg;
typedef union _IoExiuEisir IoExiuEisir;

extern volatile IoExiu ioExiu;

struct _KExiu
{
    KObject parent;
};

/* structure of eimask          (1C26_F000h) */
union _IoExiuEimask
{
    unsigned long word;
    struct
    {
        unsigned long eimask0 :1;
        unsigned long eimask1 :1;
        unsigned long eimask2 :1;
        unsigned long eimask3 :1;
        unsigned long eimask4 :1;
        unsigned long eimask5 :1;
        unsigned long eimask6 :1;
        unsigned long eimask7 :1;
        unsigned long eimask8 :1;
        unsigned long eimask9 :1;
        unsigned long eimask10 :1;
        unsigned long eimask11 :1;
        unsigned long eimask12 :1;
        unsigned long eimask13 :1;
        unsigned long eimask14 :1;
        unsigned long eimask15 :1;
        unsigned long eimask16 :1;
        unsigned long eimask17 :1;
        unsigned long eimask18 :1;
        unsigned long eimask19 :1;
        unsigned long eimask20 :1;
        unsigned long eimask21 :1;
        unsigned long eimask22 :1;
        unsigned long eimask23 :1;
        unsigned long eimask24 :1;
        unsigned long eimask25 :1;
        unsigned long eimask26 :1;
        unsigned long eimask27 :1;
        unsigned long eimask28 :1;
        unsigned long eimask29 :1;
        unsigned long eimask30 :1;
        unsigned long eimask31 :1;
    } bit;
};

/* structure of eisrcsel        (1C26_F004h) */
union _IoExiuEisrcsel
{
    unsigned long word;
    struct
    {
        unsigned long eisrcsel0 :1;
        unsigned long eisrcsel1 :1;
        unsigned long eisrcsel2 :1;
        unsigned long eisrcsel3 :1;
        unsigned long eisrcsel4 :1;
        unsigned long eisrcsel5 :1;
        unsigned long eisrcsel6 :1;
        unsigned long eisrcsel7 :1;
        unsigned long eisrcsel8 :1;
        unsigned long eisrcsel9 :1;
        unsigned long eisrcsel10 :1;
        unsigned long eisrcsel11 :1;
        unsigned long eisrcsel12 :1;
        unsigned long eisrcsel13 :1;
        unsigned long eisrcsel14 :1;
        unsigned long eisrcsel15 :1;
        unsigned long eisrcsel16 :1;
        unsigned long eisrcsel17 :1;
        unsigned long eisrcsel18 :1;
        unsigned long eisrcsel19 :1;
        unsigned long eisrcsel20 :1;
        unsigned long eisrcsel21 :1;
        unsigned long eisrcsel22 :1;
        unsigned long eisrcsel23 :1;
        unsigned long eisrcsel24 :1;
        unsigned long eisrcsel25 :1;
        unsigned long eisrcsel26 :1;
        unsigned long eisrcsel27 :1;
        unsigned long eisrcsel28 :1;
        unsigned long eisrcsel29 :1;
        unsigned long eisrcsel30 :1;
        unsigned long eisrcsel31 :1;
    } bit;
};

/* structure of eireqsta        (1C26_F008h) */
union _IoExiuEireqsta
{
    unsigned long word;
    struct
    {
        unsigned long eireqsta0 :1;
        unsigned long eireqsta1 :1;
        unsigned long eireqsta2 :1;
        unsigned long eireqsta3 :1;
        unsigned long eireqsta4 :1;
        unsigned long eireqsta5 :1;
        unsigned long eireqsta6 :1;
        unsigned long eireqsta7 :1;
        unsigned long eireqsta8 :1;
        unsigned long eireqsta9 :1;
        unsigned long eireqsta10 :1;
        unsigned long eireqsta11 :1;
        unsigned long eireqsta12 :1;
        unsigned long eireqsta13 :1;
        unsigned long eireqsta14 :1;
        unsigned long eireqsta15 :1;
        unsigned long eireqsta16 :1;
        unsigned long eireqsta17 :1;
        unsigned long eireqsta18 :1;
        unsigned long eireqsta19 :1;
        unsigned long eireqsta20 :1;
        unsigned long eireqsta21 :1;
        unsigned long eireqsta22 :1;
        unsigned long eireqsta23 :1;
        unsigned long eireqsta24 :1;
        unsigned long eireqsta25 :1;
        unsigned long eireqsta26 :1;
        unsigned long eireqsta27 :1;
        unsigned long eireqsta28 :1;
        unsigned long eireqsta29 :1;
        unsigned long eireqsta30 :1;
        unsigned long eireqsta31 :1;
    } bit;
};

/* structure of eirawreqsta     (1C26_F00Ch) */
union _IoExiuEirawreqsta
{
    unsigned long word;
    struct
    {
        unsigned long eirawreqsta0 :1;
        unsigned long eirawreqsta1 :1;
        unsigned long eirawreqsta2 :1;
        unsigned long eirawreqsta3 :1;
        unsigned long eirawreqsta4 :1;
        unsigned long eirawreqsta5 :1;
        unsigned long eirawreqsta6 :1;
        unsigned long eirawreqsta7 :1;
        unsigned long eirawreqsta8 :1;
        unsigned long eirawreqsta9 :1;
        unsigned long eirawreqsta10 :1;
        unsigned long eirawreqsta11 :1;
        unsigned long eirawreqsta12 :1;
        unsigned long eirawreqsta13 :1;
        unsigned long eirawreqsta14 :1;
        unsigned long eirawreqsta15 :1;
        unsigned long eirawreqsta16 :1;
        unsigned long eirawreqsta17 :1;
        unsigned long eirawreqsta18 :1;
        unsigned long eirawreqsta19 :1;
        unsigned long eirawreqsta20 :1;
        unsigned long eirawreqsta21 :1;
        unsigned long eirawreqsta22 :1;
        unsigned long eirawreqsta23 :1;
        unsigned long eirawreqsta24 :1;
        unsigned long eirawreqsta25 :1;
        unsigned long eirawreqsta26 :1;
        unsigned long eirawreqsta27 :1;
        unsigned long eirawreqsta28 :1;
        unsigned long eirawreqsta29 :1;
        unsigned long eirawreqsta30 :1;
        unsigned long eirawreqsta31 :1;
    } bit;
};

/* structure of eireqclr        (1C26_F010h) */
union _IoExiuEireqclr
{
    unsigned long word;
    struct
    {
        unsigned long eireqclr0 :1;
        unsigned long eireqclr1 :1;
        unsigned long eireqclr2 :1;
        unsigned long eireqclr3 :1;
        unsigned long eireqclr4 :1;
        unsigned long eireqclr5 :1;
        unsigned long eireqclr6 :1;
        unsigned long eireqclr7 :1;
        unsigned long eireqclr8 :1;
        unsigned long eireqclr9 :1;
        unsigned long eireqclr10 :1;
        unsigned long eireqclr11 :1;
        unsigned long eireqclr12 :1;
        unsigned long eireqclr13 :1;
        unsigned long eireqclr14 :1;
        unsigned long eireqclr15 :1;
        unsigned long eireqclr16 :1;
        unsigned long eireqclr17 :1;
        unsigned long eireqclr18 :1;
        unsigned long eireqclr19 :1;
        unsigned long eireqclr20 :1;
        unsigned long eireqclr21 :1;
        unsigned long eireqclr22 :1;
        unsigned long eireqclr23 :1;
        unsigned long eireqclr24 :1;
        unsigned long eireqclr25 :1;
        unsigned long eireqclr26 :1;
        unsigned long eireqclr27 :1;
        unsigned long eireqclr28 :1;
        unsigned long eireqclr29 :1;
        unsigned long eireqclr30 :1;
        unsigned long eireqclr31 :1;
    } bit;
};

/* structure of eilvl           (1C26_F014h) */
union _IoExiuEilvl
{
    unsigned long word;
    struct
    {
        unsigned long eilvl0 :1;
        unsigned long eilvl1 :1;
        unsigned long eilvl2 :1;
        unsigned long eilvl3 :1;
        unsigned long eilvl4 :1;
        unsigned long eilvl5 :1;
        unsigned long eilvl6 :1;
        unsigned long eilvl7 :1;
        unsigned long eilvl8 :1;
        unsigned long eilvl9 :1;
        unsigned long eilvl10 :1;
        unsigned long eilvl11 :1;
        unsigned long eilvl12 :1;
        unsigned long eilvl13 :1;
        unsigned long eilvl14 :1;
        unsigned long eilvl15 :1;
        unsigned long eilvl16 :1;
        unsigned long eilvl17 :1;
        unsigned long eilvl18 :1;
        unsigned long eilvl19 :1;
        unsigned long eilvl20 :1;
        unsigned long eilvl21 :1;
        unsigned long eilvl22 :1;
        unsigned long eilvl23 :1;
        unsigned long eilvl24 :1;
        unsigned long eilvl25 :1;
        unsigned long eilvl26 :1;
        unsigned long eilvl27 :1;
        unsigned long eilvl28 :1;
        unsigned long eilvl29 :1;
        unsigned long eilvl30 :1;
        unsigned long eilvl31 :1;
    } bit;
};

/* structure of eiedg           (1C26_F018h) */
union _IoExiuEiedg
{
    unsigned long word;
    struct
    {
        unsigned long eiedg0 :1;
        unsigned long eiedg1 :1;
        unsigned long eiedg2 :1;
        unsigned long eiedg3 :1;
        unsigned long eiedg4 :1;
        unsigned long eiedg5 :1;
        unsigned long eiedg6 :1;
        unsigned long eiedg7 :1;
        unsigned long eiedg8 :1;
        unsigned long eiedg9 :1;
        unsigned long eiedg10 :1;
        unsigned long eiedg11 :1;
        unsigned long eiedg12 :1;
        unsigned long eiedg13 :1;
        unsigned long eiedg14 :1;
        unsigned long eiedg15 :1;
        unsigned long eiedg16 :1;
        unsigned long eiedg17 :1;
        unsigned long eiedg18 :1;
        unsigned long eiedg19 :1;
        unsigned long eiedg20 :1;
        unsigned long eiedg21 :1;
        unsigned long eiedg22 :1;
        unsigned long eiedg23 :1;
        unsigned long eiedg24 :1;
        unsigned long eiedg25 :1;
        unsigned long eiedg26 :1;
        unsigned long eiedg27 :1;
        unsigned long eiedg28 :1;
        unsigned long eiedg29 :1;
        unsigned long eiedg30 :1;
        unsigned long eiedg31 :1;
    } bit;
};

/* structure of eisir           (1C26_F01Ch) */
union _IoExiuEisir
{
    unsigned long word;
    struct
    {
        unsigned long eisir0 :1;
        unsigned long eisir1 :1;
        unsigned long eisir2 :1;
        unsigned long eisir3 :1;
        unsigned long eisir4 :1;
        unsigned long eisir5 :1;
        unsigned long eisir6 :1;
        unsigned long eisir7 :1;
        unsigned long eisir8 :1;
        unsigned long eisir9 :1;
        unsigned long eisir10 :1;
        unsigned long eisir11 :1;
        unsigned long eisir12 :1;
        unsigned long eisir13 :1;
        unsigned long eisir14 :1;
        unsigned long eisir15 :1;
        unsigned long eisir16 :1;
        unsigned long eisir17 :1;
        unsigned long eisir18 :1;
        unsigned long eisir19 :1;
        unsigned long eisir20 :1;
        unsigned long eisir21 :1;
        unsigned long eisir22 :1;
        unsigned long eisir23 :1;
        unsigned long eisir24 :1;
        unsigned long eisir25 :1;
        unsigned long eisir26 :1;
        unsigned long eisir27 :1;
        unsigned long eisir28 :1;
        unsigned long eisir29 :1;
        unsigned long eisir30 :1;
        unsigned long eisir31 :1;
    } bit;
};

/*  EXIU register                           */
struct _IoExiu
{
    IoExiuEimask eimask; /* 1C26_(F000 - F003h) Interrupt Masking Register */
    IoExiuEisrcsel eisrcsel; /* 1C26_(F004 - F007h) Interrupt Source Select Register */
    IoExiuEireqsta eireqsta; /* 1C26_(F008 - F00Bh) Internal Interrupt Request Status Register */
    IoExiuEirawreqsta eirawreqsta; /* 1C26_(F00C - F00Fh) Raw Interrupt Request Status Register */
    IoExiuEireqclr eireqclr; /* 1C26_(F010 - F013h) Interrupt Clear Register */
    IoExiuEilvl eilvl; /* 1C26_(F014 - F017h) External Interrupt Level Setting Register */
    IoExiuEiedg eiedg; /* 1C26_(F018 - F01Bh) Interrupt Detection Method Setting Register */
    IoExiuEisir eisir; /* 1C26_(F01C - F01Fh) Software Interrupt Register */
};

KConstType k_exiu_get_type(void);
KExiu* k_exiu_new(void);

#endif/*__K_EXIU_H__*/
