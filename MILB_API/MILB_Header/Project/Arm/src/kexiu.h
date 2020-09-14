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


#define K_TYPE_EXIU 	         (k_exiu_get_type())
#define K_EXIU(obj)	             (K_TYPE_CHECK_INSTANCE_CAST((obj), KExiu))
#define K_IS_EXIU(obj)	         (K_TYPE_CHECK_INSTANCE_TYPE((obj), K_TYPE_EXIU))


typedef struct _KExiu            KExiu;
typedef struct _KExiuPrivate     KExiuPrivate;

typedef struct _IoExiu           IoExiu;

typedef union _IoExiuEimask      IoExiuEimask;
typedef union _IoExiuEisrcsel    IoExiuEisrcsel;
typedef union _IoExiuEireqsta    IoExiuEireqsta;
typedef union _IoExiuEirawreqsta IoExiuEirawreqsta;
typedef union _IoExiuEireqclr    IoExiuEireqclr;
typedef union _IoExiuEilvl       IoExiuEilvl;
typedef union _IoExiuEiedg       IoExiuEiedg;
typedef union _IoExiuEisir       IoExiuEisir;

extern volatile IoExiu ioExiu;


struct _KExiu
{
    KObject parent;
};


/* structure of eimask          (1C26_F000h) */
union _IoExiuEimask
{
    kulong word;
    struct
    {
        kulong eimask0 :1;
        kulong eimask1 :1;
        kulong eimask2 :1;
        kulong eimask3 :1;
        kulong eimask4 :1;
        kulong eimask5 :1;
        kulong eimask6 :1;
        kulong eimask7 :1;
        kulong eimask8 :1;
        kulong eimask9 :1;
        kulong eimask10 :1;
        kulong eimask11 :1;
        kulong eimask12 :1;
        kulong eimask13 :1;
        kulong eimask14 :1;
        kulong eimask15 :1;
        kulong eimask16 :1;
        kulong eimask17 :1;
        kulong eimask18 :1;
        kulong eimask19 :1;
        kulong eimask20 :1;
        kulong eimask21 :1;
        kulong eimask22 :1;
        kulong eimask23 :1;
        kulong eimask24 :1;
        kulong eimask25 :1;
        kulong eimask26 :1;
        kulong eimask27 :1;
        kulong eimask28 :1;
        kulong eimask29 :1;
        kulong eimask30 :1;
        kulong eimask31 :1;
    } bit;
};

/* structure of eisrcsel        (1C26_F004h) */
union _IoExiuEisrcsel
{
    kulong word;
    struct
    {
        kulong eisrcsel0 :1;
        kulong eisrcsel1 :1;
        kulong eisrcsel2 :1;
        kulong eisrcsel3 :1;
        kulong eisrcsel4 :1;
        kulong eisrcsel5 :1;
        kulong eisrcsel6 :1;
        kulong eisrcsel7 :1;
        kulong eisrcsel8 :1;
        kulong eisrcsel9 :1;
        kulong eisrcsel10 :1;
        kulong eisrcsel11 :1;
        kulong eisrcsel12 :1;
        kulong eisrcsel13 :1;
        kulong eisrcsel14 :1;
        kulong eisrcsel15 :1;
        kulong eisrcsel16 :1;
        kulong eisrcsel17 :1;
        kulong eisrcsel18 :1;
        kulong eisrcsel19 :1;
        kulong eisrcsel20 :1;
        kulong eisrcsel21 :1;
        kulong eisrcsel22 :1;
        kulong eisrcsel23 :1;
        kulong eisrcsel24 :1;
        kulong eisrcsel25 :1;
        kulong eisrcsel26 :1;
        kulong eisrcsel27 :1;
        kulong eisrcsel28 :1;
        kulong eisrcsel29 :1;
        kulong eisrcsel30 :1;
        kulong eisrcsel31 :1;
    } bit;
};

/* structure of eireqsta        (1C26_F008h) */
union _IoExiuEireqsta
{
    kulong word;
    struct
    {
        kulong eireqsta0 :1;
        kulong eireqsta1 :1;
        kulong eireqsta2 :1;
        kulong eireqsta3 :1;
        kulong eireqsta4 :1;
        kulong eireqsta5 :1;
        kulong eireqsta6 :1;
        kulong eireqsta7 :1;
        kulong eireqsta8 :1;
        kulong eireqsta9 :1;
        kulong eireqsta10 :1;
        kulong eireqsta11 :1;
        kulong eireqsta12 :1;
        kulong eireqsta13 :1;
        kulong eireqsta14 :1;
        kulong eireqsta15 :1;
        kulong eireqsta16 :1;
        kulong eireqsta17 :1;
        kulong eireqsta18 :1;
        kulong eireqsta19 :1;
        kulong eireqsta20 :1;
        kulong eireqsta21 :1;
        kulong eireqsta22 :1;
        kulong eireqsta23 :1;
        kulong eireqsta24 :1;
        kulong eireqsta25 :1;
        kulong eireqsta26 :1;
        kulong eireqsta27 :1;
        kulong eireqsta28 :1;
        kulong eireqsta29 :1;
        kulong eireqsta30 :1;
        kulong eireqsta31 :1;
    } bit;
};

/* structure of eirawreqsta     (1C26_F00Ch) */
union _IoExiuEirawreqsta
{
    kulong word;
    struct
    {
        kulong eirawreqsta0 :1;
        kulong eirawreqsta1 :1;
        kulong eirawreqsta2 :1;
        kulong eirawreqsta3 :1;
        kulong eirawreqsta4 :1;
        kulong eirawreqsta5 :1;
        kulong eirawreqsta6 :1;
        kulong eirawreqsta7 :1;
        kulong eirawreqsta8 :1;
        kulong eirawreqsta9 :1;
        kulong eirawreqsta10 :1;
        kulong eirawreqsta11 :1;
        kulong eirawreqsta12 :1;
        kulong eirawreqsta13 :1;
        kulong eirawreqsta14 :1;
        kulong eirawreqsta15 :1;
        kulong eirawreqsta16 :1;
        kulong eirawreqsta17 :1;
        kulong eirawreqsta18 :1;
        kulong eirawreqsta19 :1;
        kulong eirawreqsta20 :1;
        kulong eirawreqsta21 :1;
        kulong eirawreqsta22 :1;
        kulong eirawreqsta23 :1;
        kulong eirawreqsta24 :1;
        kulong eirawreqsta25 :1;
        kulong eirawreqsta26 :1;
        kulong eirawreqsta27 :1;
        kulong eirawreqsta28 :1;
        kulong eirawreqsta29 :1;
        kulong eirawreqsta30 :1;
        kulong eirawreqsta31 :1;
    } bit;
};

/* structure of eireqclr        (1C26_F010h) */
union _IoExiuEireqclr
{
    kulong word;
    struct
    {
        kulong eireqclr0 :1;
        kulong eireqclr1 :1;
        kulong eireqclr2 :1;
        kulong eireqclr3 :1;
        kulong eireqclr4 :1;
        kulong eireqclr5 :1;
        kulong eireqclr6 :1;
        kulong eireqclr7 :1;
        kulong eireqclr8 :1;
        kulong eireqclr9 :1;
        kulong eireqclr10 :1;
        kulong eireqclr11 :1;
        kulong eireqclr12 :1;
        kulong eireqclr13 :1;
        kulong eireqclr14 :1;
        kulong eireqclr15 :1;
        kulong eireqclr16 :1;
        kulong eireqclr17 :1;
        kulong eireqclr18 :1;
        kulong eireqclr19 :1;
        kulong eireqclr20 :1;
        kulong eireqclr21 :1;
        kulong eireqclr22 :1;
        kulong eireqclr23 :1;
        kulong eireqclr24 :1;
        kulong eireqclr25 :1;
        kulong eireqclr26 :1;
        kulong eireqclr27 :1;
        kulong eireqclr28 :1;
        kulong eireqclr29 :1;
        kulong eireqclr30 :1;
        kulong eireqclr31 :1;
    } bit;
};

/* structure of eilvl           (1C26_F014h) */
union _IoExiuEilvl
{
    kulong word;
    struct
    {
        kulong eilvl0 :1;
        kulong eilvl1 :1;
        kulong eilvl2 :1;
        kulong eilvl3 :1;
        kulong eilvl4 :1;
        kulong eilvl5 :1;
        kulong eilvl6 :1;
        kulong eilvl7 :1;
        kulong eilvl8 :1;
        kulong eilvl9 :1;
        kulong eilvl10 :1;
        kulong eilvl11 :1;
        kulong eilvl12 :1;
        kulong eilvl13 :1;
        kulong eilvl14 :1;
        kulong eilvl15 :1;
        kulong eilvl16 :1;
        kulong eilvl17 :1;
        kulong eilvl18 :1;
        kulong eilvl19 :1;
        kulong eilvl20 :1;
        kulong eilvl21 :1;
        kulong eilvl22 :1;
        kulong eilvl23 :1;
        kulong eilvl24 :1;
        kulong eilvl25 :1;
        kulong eilvl26 :1;
        kulong eilvl27 :1;
        kulong eilvl28 :1;
        kulong eilvl29 :1;
        kulong eilvl30 :1;
        kulong eilvl31 :1;
    } bit;
};

/* structure of eiedg           (1C26_F018h) */
union _IoExiuEiedg
{
    kulong word;
    struct
    {
        kulong eiedg0 :1;
        kulong eiedg1 :1;
        kulong eiedg2 :1;
        kulong eiedg3 :1;
        kulong eiedg4 :1;
        kulong eiedg5 :1;
        kulong eiedg6 :1;
        kulong eiedg7 :1;
        kulong eiedg8 :1;
        kulong eiedg9 :1;
        kulong eiedg10 :1;
        kulong eiedg11 :1;
        kulong eiedg12 :1;
        kulong eiedg13 :1;
        kulong eiedg14 :1;
        kulong eiedg15 :1;
        kulong eiedg16 :1;
        kulong eiedg17 :1;
        kulong eiedg18 :1;
        kulong eiedg19 :1;
        kulong eiedg20 :1;
        kulong eiedg21 :1;
        kulong eiedg22 :1;
        kulong eiedg23 :1;
        kulong eiedg24 :1;
        kulong eiedg25 :1;
        kulong eiedg26 :1;
        kulong eiedg27 :1;
        kulong eiedg28 :1;
        kulong eiedg29 :1;
        kulong eiedg30 :1;
        kulong eiedg31 :1;
    } bit;
};

/* structure of eisir           (1C26_F01Ch) */
union _IoExiuEisir
{
    kulong word;
    struct
    {
        kulong eisir0 :1;
        kulong eisir1 :1;
        kulong eisir2 :1;
        kulong eisir3 :1;
        kulong eisir4 :1;
        kulong eisir5 :1;
        kulong eisir6 :1;
        kulong eisir7 :1;
        kulong eisir8 :1;
        kulong eisir9 :1;
        kulong eisir10 :1;
        kulong eisir11 :1;
        kulong eisir12 :1;
        kulong eisir13 :1;
        kulong eisir14 :1;
        kulong eisir15 :1;
        kulong eisir16 :1;
        kulong eisir17 :1;
        kulong eisir18 :1;
        kulong eisir19 :1;
        kulong eisir20 :1;
        kulong eisir21 :1;
        kulong eisir22 :1;
        kulong eisir23 :1;
        kulong eisir24 :1;
        kulong eisir25 :1;
        kulong eisir26 :1;
        kulong eisir27 :1;
        kulong eisir28 :1;
        kulong eisir29 :1;
        kulong eisir30 :1;
        kulong eisir31 :1;
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


KConstType   k_exiu_get_type(void);
KExiu*       k_exiu_new(void);


#endif/*__K_EXIU_H__*/
