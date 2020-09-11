/**
 * @file		__jdsiip4b_pixfmttbl.h
 * @brief		Definition JDSIIP4B Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

#include "../Project/Image/src/kjdsiip4b.h"
///*  structure of pixfmttbl0    (2888_0300h)    */
//IoIipIpxfmttbl0{
//    unsigned long       word;
//    struct {
//        unsigned long   p           :1;
//        unsigned long               :3;
//        unsigned long   ftype       :3;
//        unsigned long               :1;
//        unsigned long   pfmt        :4;
//        unsigned long   alpha       :1;
//        unsigned long               :3;
//        unsigned long   pdepth      :3;
//        unsigned long               :1;
//        unsigned long   adepth      :3;
//        unsigned long               :1;
//        unsigned long   chkyordr    :8;
//    }bit;
//};
//
///*  structure of pixfmttbl1    (2888_0304h)    */
//union IoIipIpxfmttbl1{
//    unsigned long       word;
//    struct {
//        unsigned long   sgyg    :1;
//        unsigned long   sgb     :1;
//        unsigned long   sgr     :1;
//        unsigned long   sga     :1;
//        unsigned long   asubspl :2;
//        unsigned long           :2;
//        unsigned long   mtifyg  :2;
//        unsigned long   mtifb   :2;
//        unsigned long   mtifr   :2;
//        unsigned long   mtifa   :2;
//        unsigned long   oarbhv  :1;
//        unsigned long           :15;
//    }bit;
//};
//
///*  structure of pixfmttbl2    (2888_0308h)    */
//union IoIipIpxfmttbl2{
//    unsigned long       word;
//    struct {
//        unsigned long   oarvalyg    :16;
//        unsigned long   oarvalb     :16;
//    }bit;
//};
//
///*  structure of pixfmttbl3    (2888_030Ch)    */
//union IoIipIpxfmttbl3{
//    unsigned long       word;
//    struct {
//        unsigned long   oarvalr :16;
//        unsigned long   oarvala :16;
//    }bit;
//};
//
///*  structure of pixfmttbl4    (2888_0310h)    */
//union IoIipIpxfmttbl4{
//    unsigned long       word;
//    struct {
//        long            ghszyg  :18;
//        unsigned long           :14;
//    }bit;
//};
//
///*  structure of pixfmttbl5    (2888_0314h)    */
//union IoIipIpxfmttbl5{
//    unsigned long       word;
//    struct {
//        long            ghszb   :18;
//        unsigned long           :14;
//    }bit;
//};
//
///*  structure of pixfmttbl6    (2888_0318h)    */
//union IoIipIpxfmttbl6{
//    unsigned long       word;
//    struct {
//        long            ghszr   :18;
//        unsigned long           :14;
//    }bit;
//};
//
///*  structure of pixfmttbl7    (2888_031Ch)    */
//union IoIipIpxfmttbl7{
//    unsigned long       word;
//    struct {
//        long            ghsza   :18;
//        unsigned long           :14;
//    }bit;
//};
//
///*  structure of pixfmttbl8    (2888_0320h)    */
//union IoIipIpxfmttbl8{
//    unsigned long       word;
//    struct {
//        unsigned long   pichsz  :15;
//        unsigned long           :1;
//        unsigned long   picvsz  :14;
//        unsigned long           :2;
//    }bit;
//};
//
///*  structure of pixfmttbl9    (2888_0324h)    */
//union IoIipIpxfmttbl9{
//    unsigned long       word;
//    struct {
//        unsigned long   adrsyg  :32;
//    }bit;
//};
//
///*  structure of pixfmttbl10   (2888_0328h)    */
//union IoIipIpxfmttbl10{
//    unsigned long       word;
//    struct {
//        unsigned long   adrsb   :32;
//    }bit;
//};
//
///*  structure of pixfmttbl11   (2888_032Ch)    */
//union IoIipIpxfmttbl11{
//    unsigned long       word;
//    struct {
//        unsigned long   adrsr   :32;
//    }bit;
//};
//
///*  structure of pixfmttbl12   (2888_0330h)    */
//union IoIipIpxfmttbl12{
//    unsigned long       word;
//    struct {
//        unsigned long   adrsa   :32;
//    }bit;
//};
//
///* Define i/o mapping */
//typedef struct IoIipPixfmttbl{
//    /* JDSIMG */
//    union  IoIipIpxfmttbl0   pixfmttbl0;    /* 2888_(0300 - 0303h) */
//    union  IoIipIpxfmttbl1   pixfmttbl1;    /* 2888_(0304 - 0307h) */
//    union  IoIipIpxfmttbl2   pixfmttbl2;    /* 2888_(0308 - 030Bh) */
//    union  IoIipIpxfmttbl3   pixfmttbl3;    /* 2888_(030C - 030Fh) */
//    union  IoIipIpxfmttbl4   pixfmttbl4;    /* 2888_(0310 - 0313h) */
//    union  IoIipIpxfmttbl5   pixfmttbl5;    /* 2888_(0314 - 0317h) */
//    union  IoIipIpxfmttbl6   pixfmttbl6;    /* 2888_(0318 - 031Bh) */
//    union  IoIipIpxfmttbl7   pixfmttbl7;    /* 2888_(031C - 031Fh) */
//    union  IoIipIpxfmttbl8   pixfmttbl8;    /* 2888_(0320 - 0323h) */
//    union  IoIipIpxfmttbl9   pixfmttbl9;    /* 2888_(0324 - 0327h) */
//    union  IoIipIpxfmttbl10  pixfmttbl10;   /* 2888_(0328 - 032Bh) */
//    union  IoIipIpxfmttbl11  pixfmttbl11;   /* 2888_(032C - 032Fh) */
//    union  IoIipIpxfmttbl12  pixfmttbl12;   /* 2888_(0330 - 0333h) */
//
//    unsigned char dmy_0334_033F[0x0340-0x0334]; /* 2888_(0334 - 033Fh) */
//
//}IoIipPixfmttbl;

