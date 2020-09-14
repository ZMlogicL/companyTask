/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-14
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
/**
 * @file		jdsprocag.h
 * @brief		Definition JDSPRO Macro I/O register
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */


#ifndef __JDSPRO_CAG_H__
#define __JDSPRO_CAG_H__


typedef union _IoCagtrg  			IoCagtrg;
typedef union _IoCagpaen  		IoCagpaen;
typedef union _IoCaggwp			IoCaggwp;
typedef union _IoCaggws			IoCaggws;
typedef union _IoCagwp				IoCagwp;
typedef union _IoCagws				IoCagws;
typedef union _IoCagmd				IoCagmd;
typedef union _IoRbr					IoRbr;
typedef union _IoAboarv				IoAboarv;
typedef union _IoAboarh			IoAboarh;
typedef union _IoAboagv			IoAboagv;
typedef union _IoAboagh			IoAboagh;
typedef union _IoAboabv			IoAboabv;
typedef union _IoAboabh			IoAboabh;
typedef union _IoAbgar				IoAbgar;
typedef union _IoAbgag				IoAbgag;
typedef union _IoAbgab				IoAbgab;
typedef union _IoAblrv				IoAblrv;
typedef union _IoAblrh				IoAblrh;
typedef union _IoAblgv				IoAblgv;
typedef union _IoAblgh				IoAblgh;
typedef union _IoAblbv				IoAblbv;
typedef union _IoAblbh				IoAblbh;
typedef union _IoAbofsrv			IoAbofsrv;
typedef union _IoAbofsrh			IoAbofsrh ;
typedef union _IoAbofsgv			IoAbofsgv;
typedef union _IoAbofsgh			IoAbofsgh;
typedef union _IoAbofsbv			IoAbofsbv;
typedef union _IoAbofsbh			IoAbofsbh;
typedef union _IoAbnlthr1			IoAbnlthr1;
typedef union _IoAbnlthg1			IoAbnlthg1;
typedef union _IoAbnlthb1			IoAbnlthb1;
typedef union _IoAbnlgar1			IoAbnlgar1;
typedef union _IoAbnlgag1			IoAbnlgag1;
typedef union _IoAbnlgab1			IoAbnlgab1;
typedef union _IoAbnlthr2			IoAbnlthr2;
typedef union _IoAbnlthg2 			IoAbnlthg2 ;
typedef union _IoAbnlthb2			IoAbnlthb2;
typedef union _IoAbnlgar2			IoAbnlgar2;
typedef union _IoAbnlgag2			IoAbnlgag2;
typedef union _IoAbnlgab2			IoAbnlgab2;
typedef union _IoAbnlthr3			IoAbnlthr3;
typedef union _IoAbnlthg3			IoAbnlthg3;
typedef union _IoAbnlthb3			IoAbnlthb3;
typedef union _IoAbnlgar3			IoAbnlgar3;
typedef union _IoAbnlgag3			IoAbnlgag3 ;
typedef union _IoAbnlgab3 		IoAbnlgab3 ;
typedef union _IoAbnlthr4			IoAbnlthr4;
typedef union _IoAbnlthg4			IoAbnlthg4;
typedef union _IoAbnlthb4			IoAbnlthb4;
typedef union _IoAbnlgar4			IoAbnlgar4;
typedef union _IoAbnlgag4			IoAbnlgag4;
typedef union _IoAbnlgab4			IoAbnlgab4;
typedef union _IoBfglmt				IoBfglmt;
typedef union _IoBfgth				IoBfgth;
typedef struct _IoCag					IoCag;


/*  structure of cagtrg (2840_9800h)    */
union _IoCagtrg{
    unsigned long       word;
    struct {
        unsigned long   cagtrg  :2;
        unsigned long          	 :30;
    }bit;
};

/*  structure of cagpaen    (2840_9804h)    */
union _IoCagpaen{
    unsigned long       word;
    struct {
        unsigned long   cpaen   	:1;
        unsigned long           		:31;
    }bit;
};

/*  structure of caggwp (2840_9808h)    */
union _IoCaggwp{
    unsigned long       word;
    struct {
        unsigned long   caggh   :13;
        unsigned long         		  :3;
        unsigned long   caggv   :14;
        unsigned long        		   :2;
    }bit;
};

/*  structure of caggws (2840_980Ch)    */
union _IoCaggws{
    unsigned long       word;
    struct {
        unsigned long   cagghw  :13;
        unsigned long           		:3;
        unsigned long   caggvw  :14;
        unsigned long          		:2;
    }bit;
};

/*  structure of cagwp  (2840_9810h)    */
union _IoCagwp{
    unsigned long       word;
    struct {
        unsigned long   cagh    :13;
        unsigned long           	:3;
        unsigned long   cagv    :14;
        unsigned long           	:2;
    }bit;
};

/*  structure of cagws  (2840_9814h)    */
union _IoCagws{
    unsigned long       word;
    struct {
        unsigned long   caghw   :13;
        unsigned long           		:3;
        unsigned long   cagvw   :14;
        unsigned long           		:2;
    }bit;
};

/*  structure of cagmd  (2840_9818h)    */
union _IoCagmd{
    unsigned long       word;
    struct {
        unsigned long   gcamd   	:1;
        unsigned long           		:3;
        unsigned long   cagpdd  	:1;
        unsigned long           		:3;
        unsigned long   camd    	:2;
        unsigned long           		:2;
        unsigned long   clpsel  	:1;
        unsigned long           		:19;
    }bit;
};

/*  structure of rbr    (2840_981Ch)    */
union _IoRbr{
    unsigned long       word;
    struct {
        unsigned long   rbrh    :12;
        unsigned long           	:4;
        unsigned long   rbrv    :12;
        unsigned long           	:4;
    }bit;
};

/*  structure of aboarv (2840_9820h)    */
union _IoAboarv{
    unsigned long       word;
    struct {
        long            aboarv  		:16;
        unsigned long           	:16;
    }bit;
};

/*  structure of aboarh (2840_9824h)    */
union _IoAboarh{
    unsigned long       word;
    struct {
        long            aboarh  		:16;
        unsigned long           	:16;
    }bit;
};

/*  structure of aboagv (2840_9828h)    */
union _IoAboagv{
    unsigned long       word;
    struct {
        long            aboagv  		:16;
        unsigned long           	:16;
    }bit;
};

/*  structure of aboagh (2840_982Ch)    */
union _IoAboagh{
    unsigned long       word;
    struct {
        long            aboagh  		:16;
        unsigned long          	:16;
    }bit;
};

/*  structure of aboabv (2840_9830h)    */
union _IoAboabv{
    unsigned long       word;
    struct {
        long            aboabv  		:16;
        unsigned long           	:16;
    }bit;
};

/*  structure of aboabh (2840_9834h)    */
union _IoAboabh{
    unsigned long       word;
    struct {
        long            aboabh  		:16;
        unsigned long           	:16;
    }bit;
};

/*  structure of abgar  (2840_9838h)    */
union _IoAbgar{
    unsigned long      word;
    struct {
        long            		abgar   		:13;
        unsigned long           			:19;
    }bit;
};

/*  structure of abgag  (2840_983Ch)    */
union _IoAbgag{
    unsigned long       word;
    struct {
        long            abgag   			:13;
        unsigned long           		:19;
    }bit;
};

/*  structure of abgab  (2840_9840h)    */
union _IoAbgab{
    unsigned long       word;
    struct {
        long            abgab   		:13;
        unsigned long           	:19;
    }bit;
};

/*  structure of ablrv  (2840_9844h)    */
union _IoAblrv{
    unsigned long       word;
    struct {
        long            ablrvu  	:12;
        unsigned long          :4;
        long            ablrvl  		:12;
        unsigned long          :4;
    }bit;
};

/*  structure of ablrh  (2840_9848h)    */
union _IoAblrh{
    unsigned long       word;
    struct {
        long            ablrhu  	:13;
        unsigned long          :3;
        long            ablrhl  	:13;
        unsigned long          :3;
    }bit;
};

/*  structure of ablgv  (2840_984Ch)    */
union _IoAblgv{
    unsigned long       word;
    struct {
        long            ablgvu  	:12;
        unsigned long          :4;
        long            ablgvl  	:12;
        unsigned long          :4;
    }bit;
};

/*  structure of ablgh  (2840_9850h)    */
union _IoAblgh{
    unsigned long       word;
    struct {
        long            ablghu  	:13;
        unsigned long          :3;
        long            ablghl  	:13;
        unsigned long          :3;
    }bit;
};

/*  structure of ablbv  (2840_9854h)    */
union _IoAblbv{
    unsigned long       word;
    struct {
        long            ablbvu  	:12;
        unsigned long          :4;
        long            ablbvl  	:12;
        unsigned long          :4;
    }bit;
};

/*  structure of ablbh  (2840_9858h)    */
union _IoAblbh{
    unsigned long       word;
    struct {
        long            ablbhu  	:13;
        unsigned long          :3;
        long            ablbhl  	:13;
        unsigned long          :3;
    }bit;
};

/*  structure of abofsrv    (2840_985Ch)    */
union _IoAbofsrv{
    unsigned long       word;
    struct {
        long            abofsrv 		:11;
        unsigned long           	:21;
    }bit;
};

/*  structure of abofsrh    (2840_9860h)    */
union _IoAbofsrh{
    unsigned long       word;
    struct {
        long            abofsrh 		:12;
        unsigned long           	:20;
    }bit;
};

/*  structure of abofsgv    (2840_9864h)    */
union _IoAbofsgv{
    unsigned long       word;
    struct {
        long            abofsgv 		:11;
        unsigned long           	:21;
    }bit;
};

/*  structure of abofsgh    (2840_9868h)    */
union _IoAbofsgh{
    unsigned long       word;
    struct {
        long            abofsgh 		:12;
        unsigned long           	:20;
    }bit;
};

/*  structure of abofsbv    (2840_986Ch)    */
union _IoAbofsbv{
    unsigned long       word;
    struct {
        long            abofsbv 		:11;
        unsigned long           	:21;
    }bit;
};

/*  structure of abofsbh    (2840_9870h)    */
union _IoAbofsbh{
    unsigned long       word;
    struct {
        long            abofsbh 		:12;
        unsigned long           	:20;
    }bit;
};

/*  structure of abnlthr1   (2840_9874h)    */
union _IoAbnlthr1{
    unsigned long       word;
    struct {
        unsigned long   abnlthr1    	:16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthg1   (2840_9878h)    */
union _IoAbnlthg1{
    unsigned long       word;
    struct {
        unsigned long   abnlthg1    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthb1   (2840_987Ch)    */
union _IoAbnlthb1{
    unsigned long       word;
    struct {
        unsigned long   abnlthb1    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlgar1   (2840_9880h)    */
union _IoAbnlgar1{
    unsigned long       word;
    struct {
        long            abnlgar1    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgag1   (2840_9884h)    */
union _IoAbnlgag1{
    unsigned long       word;
    struct {
        long            abnlgag1    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgab1   (2840_9888h)    */
union _IoAbnlgab1{
    unsigned long       word;
    struct {
        long            abnlgab1    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlthr2   (2840_988Ch)    */
union _IoAbnlthr2{
    unsigned long       word;
    struct {
        unsigned long   abnlthr2    	:16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthg2   (2840_9890h)    */
union _IoAbnlthg2{
    unsigned long       word;
    struct {
        unsigned long   abnlthg2    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthb2   (2840_9894h)    */
union _IoAbnlthb2{
    unsigned long       word;
    struct {
        unsigned long   abnlthb2    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlgar2   (2840_9898h)    */
union _IoAbnlgar2{
    unsigned long       word;
    struct {
        long            abnlgar2    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgag2   (2840_989Ch)    */
union _IoAbnlgag2{
    unsigned long       word;
    struct {
        long            abnlgag2    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgab2   (2840_98A0h)    */
union _IoAbnlgab2{
    unsigned long       word;
    struct {
        long            abnlgab2    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlthr3   (2840_98A4h)    */
union _IoAbnlthr3{
    unsigned long       word;
    struct {
        unsigned long   abnlthr3    	:16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthg3   (2840_98A8h)    */
union _IoAbnlthg3{
    unsigned long       word;
    struct {
        unsigned long   abnlthg3    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthb3   (2840_98ACh)    */
union _IoAbnlthb3{
    unsigned long       word;
    struct {
        unsigned long   abnlthb3    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlgar3   (2840_98B0h)    */
union _IoAbnlgar3{
    unsigned long       word;
    struct {
        long            abnlgar3    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgag3   (2840_98B4h)    */
union _IoAbnlgag3{
    unsigned long       word;
    struct {
        long            abnlgag3    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgab3   (2840_98B8h)    */
union _IoAbnlgab3{
    unsigned long       word;
    struct {
        long            abnlgab3    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlthr4   (2840_98BCh)    */
union _IoAbnlthr4{
    unsigned long       word;
    struct {
        unsigned long   abnlthr4    	:16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthg4   (2840_98C0h)    */
union _IoAbnlthg4{
    unsigned long       word;
    struct {
        unsigned long   abnlthg4    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlthb4   (2840_98C4h)    */
union _IoAbnlthb4{
    unsigned long       word;
    struct {
        unsigned long   abnlthb4    :16;
        unsigned long               		:16;
    }bit;
};

/*  structure of abnlgar4   (2840_98C8h)    */
union _IoAbnlgar4{
    unsigned long       word;
    struct {
        long            abnlgar4    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgag4   (2840_98CCh)    */
union _IoAbnlgag4{
    unsigned long       word;
    struct {
        long            abnlgag4    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of abnlgab4   (2840_98D0h)    */
union _IoAbnlgab4{
    unsigned long       word;
    struct {
        long            abnlgab4    		:15;
        unsigned long               	:17;
    }bit;
};

/*  structure of bfglmt (2840_98D4h)    */
union _IoBfglmt{
    unsigned long       word;
    struct {
        unsigned long   bfglmtl 	:14;
        unsigned long           		:2;
        unsigned long   bfglmth 	:14;
        unsigned long           		:2;
    }bit;
};

/*  structure of bfgth  (2840_98D8h)    */
union _IoBfgth{
    unsigned long       word;
    struct {
        unsigned long   bfgthk  		:8;
        unsigned long           			:8;
        unsigned long   bfgtha  		:14;
        unsigned long           			:2;
    }bit;
};

/* Define i/o mapping */
struct _IoCag{
    /* JDSIMG */
	IoCagtrg    		cagtrg;     	/* 2840_(9800 - 9803h) */
    IoCagpaen   	cagpaen;   	/* 2840_(9804 - 9807h) */
    IoCaggwp    	caggwp;    	/* 2840_(9808 - 980Bh) */
    IoCaggws    	caggws;    	/* 2840_(980C - 980Fh) */
    IoCagwp     		cagwp;     	/* 2840_(9810 - 9813h) */
    IoCagws     		cagws;      	/* 2840_(9814 - 9817h) */
    IoCagmd     	cagmd;      	/* 2840_(9818 - 981Bh) */
    IoRbr       		rbr;        		/* 2840_(981C - 981Fh) */
    IoAboarv    		aboarv;     	/* 2840_(9820 - 9823h) */
    IoAboarh    		aboarh;    	/* 2840_(9824 - 9827h) */
    IoAboagv    		aboagv;    	/* 2840_(9828 - 982Bh) */
    IoAboagh    	aboagh;  	  	/* 2840_(982C - 982Fh) */
    IoAboabv    	aboabv;     	/* 2840_(9830 - 9833h) */
    IoAboabh    	aboabh;     	/* 2840_(9834 - 9837h) */
    IoAbgar     		abgar;      	/* 2840_(9838 - 983Bh) */
    IoAbgag     		abgag;      	/* 2840_(983C - 983Fh) */
    IoAbgab     		abgab;      	/* 2840_(9840 - 9843h) */
    IoAblrv     		ablrv;      		/* 2840_(9844 - 9847h) */
    IoAblrh     		ablrh;      		/* 2840_(9848 - 984Bh) */
    IoAblgv     		ablgv;      	/* 2840_(984C - 984Fh) */
    IoAblgh     		ablgh;      	/* 2840_(9850 - 9853h) */
    IoAblbv     		ablbv;      	/* 2840_(9854 - 9857h) */
    IoAblbh     		ablbh;      	/* 2840_(9858 - 985Bh) */
    IoAbofsrv  		 abofsrv;    	/* 2840_(985C - 985Fh) */
    IoAbofsrh   		abofsrh;    	/* 2840_(9860 - 9863h) */
    IoAbofsgv   		abofsgv;    	/* 2840_(9864 - 9867h) */
    IoAbofsgh   	abofsgh;    	/* 2840_(9868 - 986Bh) */
    IoAbofsbv   		abofsbv;    	/* 2840_(986C - 986Fh) */
	IoAbofsbh 		abofsbh; 		/* 2840_(9870 - 9873h) */
	IoAbnlthr1 		abnlthr1; 	/* 2840_(9874 - 9877h) */
	IoAbnlthg1 		abnlthg1; 	/* 2840_(9878 - 987Bh) */
	IoAbnlthb1 		abnlthb1; 	/* 2840_(987C - 987Fh) */
	IoAbnlgar1 		abnlgar1; 	/* 2840_(9880 - 9883h) */
	IoAbnlgag1 	abnlgag1; 	/* 2840_(9884 - 9887h) */
	IoAbnlgab1 	abnlgab1;	/* 2840_(9888 - 988Bh) */
	IoAbnlthr2 		abnlthr2; 	/* 2840_(988C - 988Fh) */
	IoAbnlthg2 		abnlthg2; 	/* 2840_(9890 - 9893h) */
	IoAbnlthb2 		abnlthb2; 	/* 2840_(9894 - 9897h) */
	IoAbnlgar2 		abnlgar2; 	/* 2840_(9898 - 989Bh) */
	IoAbnlgag2 	abnlgag2; 	/* 2840_(989C - 989Fh) */
	IoAbnlgab2 	abnlgab2; 	/* 2840_(98A0 - 98A3h) */
	IoAbnlthr3 		abnlthr3; 	/* 2840_(98A4 - 98A7h) */
	IoAbnlthg3 		abnlthg3; 	/* 2840_(98A8 - 98ABh) */
	IoAbnlthb3 		abnlthb3; 	/* 2840_(98AC - 98AFh) */
	IoAbnlgar3 		abnlgar3; 	/* 2840_(98B0 - 98B3h) */
	IoAbnlgag3 	abnlgag3; 	/* 2840_(98B4 - 98B7h) */
	IoAbnlgab3 	abnlgab3; 	/* 2840_(98B8 - 98BBh) */
	IoAbnlthr4 		abnlthr4; 	/* 2840_(98BC - 98BFh) */
	IoAbnlthg4 		abnlthg4; 	/* 2840_(98C0 - 98C3h) */
	IoAbnlthb4 		abnlthb4; 	/* 2840_(98C4 - 98C7h) */
	IoAbnlgar4 		abnlgar4; 	/* 2840_(98C8 - 98CBh) */
	IoAbnlgag4 	abnlgag4; 	/* 2840_(98CC - 98CFh) */
	IoAbnlgab4 	abnlgab4; 	/* 2840_(98D0 - 98D3h) */
	IoBfglmt 			bfglmt; 		/* 2840_(98D4 - 98D7h) */
	IoBfgth 			bfgth; 			/* 2840_(98D8 - 98DBh) */
    unsigned char dmy98dc98ff[0x9900 - 0x98DC]; 	/* 2840_(98DC - 98FFh) */
};


#endif /* __JDSPRO_CAG_H__ */
