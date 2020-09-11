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


#ifndef __SNS_PCIE_H__
#define __SNS_PCIE_H__


#include <klib.h>


#define SNS_TYPE_PCIE                  (sns_pcie_get_type())
#define SNS_PCIE(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, SnsPcie))
#define SNS_IS_PCIE(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, SNS_TYPE_PCIE))


typedef union _IoDevIdVendId			IoDevIdVendId;
typedef union _IoStatusCommand 	IoStatusCommand;
typedef union _IoClassCodeRevId 		IoClassCodeRevId;
typedef union _IoHdrTypeCacheLineSize		IoHdrTypeCacheLineSize ;
typedef union _IoSecLatTimerSubBusSecBusPriBus 		IoSecLatTimerSubBusSecBusPriBus;
typedef union _IoSecStatIoLimitIoBase 		IoSecStatIoLimitIoBase;
typedef union _IoMemLimitMemBase 			IoMemLimitMemBase;
typedef union _IoPrefMemLimitPrefMemBase		IoPrefMemLimitPrefMemBase;
typedef union _IoPrefBaseUpper			IoPrefBaseUpper;
typedef union _IoPrefLimitUpper 			IoPrefLimitUpper;
typedef union _IoIoLimitUpperIoBaseUpper 		IoIoLimitUpperIoBaseUpper;
typedef union _IoCapPtr 						IoCapPtr;
typedef union _IoExpRomBar 				IoExpRomBar;
typedef union _IoBridgeCtrlIntPinIntLine 		IoBridgeCtrlIntPinIntLine;
typedef struct _IoT1csh 							IoT1csh;
typedef union _IoBar 								IoBar;
typedef union _IoCardbusCisPtr 			IoCardbusCisPtr;
typedef union _IoSubsysIdSubsysVId 	IoSubsysIdSubsysVId;
typedef union _IoIntPinIntLine 				IoIntPinIntLine;
typedef struct _IoT0csh 							IoT0csh;
typedef union _IoPmcrPmc 					IoPmcrPmc;
typedef union _IoPmcrPmcs 					IoPmcrPmcs;
typedef struct _IoPmcr 							IoPmcr;
typedef union _IoMsicrMcinc 					IoMsicrMcinc;
typedef union _IoMsicrMla 					IoMsicrMla;
typedef union _IoMsicrMua 					IoMsicrMua;
typedef union _IoMsicrMd  					IoMsicrMd;
typedef union _IoMsicrMmb 					IoMsicrMmb;
typedef union _IoMsicrMpb 					IoMsicrMpb;
typedef struct _IoMsicr 							IoMsicr;
typedef union _IoPciecrCr 						IoPciecrCr;
typedef union _IoPciecrDcr 					IoPciecrDcr;
typedef union _IoPciecrDcsr 					IoPciecrDcsr;
typedef union _IoPciecrLcr 					IoPciecrLcr;
typedef union _IoPciecrLcsr 					IoPciecrLcsr;
typedef union _IoPciecrScr 					IoPciecrScr;
typedef union _IoPciecrScsr 					IoPciecrScsr;
typedef union _IoPciecrRccr 					IoPciecrRccr;
typedef union _IoPciecrRsr 					IoPciecrRsr;
typedef union _IoPciecrDc2r 					IoPciecrDc2r;
typedef union _IoPciecrDc2sr 				IoPciecrDc2sr;
typedef union _IoPciecrLc2r 					IoPciecrLc2r;
typedef union _IoPciecrLc2sr 					IoPciecrLc2sr;
typedef struct _IoPciecr							IoPciecr;
typedef union _IoAercAerech 					IoAercAerech;
typedef union _IoAercUesr 						IoAercUesr;
typedef union _IoAercUemr  					IoAercUemr;
typedef union _IoAercUesvr  					IoAercUesvr;
typedef union _IoAercCesr 						IoAercCesr;
typedef union _IoAercCemr 					IoAercCemr;
typedef union _IoAercAeccr 					IoAercAeccr;
typedef union _IoAercHlr  						IoAercHlr;
typedef union _IoAercRecr  					IoAercRecr;
typedef union _IoAercResr 						IoAercResr;
typedef union _IoAercEsir 						IoAercEsir;
typedef union _IoTlpplr 							IoTlpplr;
typedef struct _IoAerc 							IoAerc;
typedef union _IoLtrcLtrech 					IoLtrcLtrech;
typedef union _IoLtrcMsnslr 					IoLtrcMsnslr;
typedef struct _IoLtrc 								IoLtrc;
typedef union _IoL1pmsecL1pmsech 	IoL1pmsecL1pmsech;
typedef union _IoL1pmsecL1pmscr 		IoL1pmsecL1pmscr;
typedef union _IoL1pmsecL1pmsc1r 		IoL1pmsecL1pmsc1r;
typedef union _IoL1pmsecL1pmsc2r  	IoL1pmsecL1pmsc2r;
typedef struct _IoL1pmsec  					IoL1pmsec;
typedef union _IoPplAlt  							IoPplAlt;
typedef union _IoPplVsd 						IoPplVsd;
typedef union _IoPplPf  							IoPplPf;
typedef union _IoPplAfac 						IoPplAfac;
typedef union _IoPplPlc 							IoPplPlc;
typedef union _IoPplLs 							IoPplLs;
typedef union _IoPplTcmfn 					IoPplTcmfn;
typedef union _IoPplStf1 						IoPplStf1;
typedef union _IoPplFm2						IoPplFm2;
typedef union _IoPplAmodnsrc 				IoPplAmodnsrc;
typedef union _IoPplPd0 						IoPplPd0;
typedef union _IoPplPd1  						IoPplPd1;
typedef union _IoPplTpfcs						IoPplTpfcs;
typedef union _IoPplTnfcs 						IoPplTnfcs;
typedef union _IoPplTcfcs 						IoPplTcfcs;
typedef union _IoPplQs 							IoPplQs;
typedef union _IoPplVta1 						IoPplVta1;
typedef union _IoPplVta2 						IoPplVta2;
typedef union _IoPplVprqc 					IoPplVprqc;
typedef union _IoPplVnrqc 					IoPplVnrqc;
typedef union _IoPplVcrqc 						IoPplVcrqc;
typedef union _IoPplGen2c 					IoPplGen2c;
typedef union _IoPplPhys						IoPplPhys;
typedef union _IoPplPhyc 						IoPplPhyc;
typedef union _IoPplMca 						IoPplMca;
typedef union _IoPplMcua 						IoPplMcua;
typedef union _IoPplMci0e						IoPplMci0e;
typedef union _IoPplMci0m  					IoPplMci0m;
typedef union _IoPplMci0s  					IoPplMci0s;
typedef union _IoPplMgi 						IoPplMgi;
typedef union _IoPplPilc 						IoPplPilc;
typedef union _IoPplMc1 						IoPplMc1;
typedef union _IoPplMlc 						IoPplMlc;
typedef union _IoPplPhyic 						IoPplPhyic;
typedef union _IoPplLfc 							IoPplLfc;
typedef union _IoPplAerdr 						IoPplAerdr;
typedef union _IoPplAmlt 						IoPplAmlt;
typedef union _IoPplAoc  						IoPplAoc;
typedef union _IoPplCc1 						IoPplCc1;
typedef union _IoPplCc2  						IoPplCc2;
typedef union _IoPplCc3 						IoPplCc3;
typedef union _IoPplAmmal  					IoPplAmmal;
typedef union _IoPplAmmah 					IoPplAmmah;
typedef union _IoPplIv  							IoPplIv;
typedef union _IoPplIrc1  						IoPplIrc1;
typedef union _IoPplIrc2o  						IoPplIrc2o;
typedef union _IoPplIrc2i   						IoPplIrc2i;
typedef union _IoPplIrc2  						IoPplIrc2;
typedef union _IoPplIlba 						IoPplIlba;
typedef union _IoPplIuba  						IoPplIuba;
typedef union _IoPplIla  							IoPplIla;
typedef union _IoPplIltao  						IoPplIltao;
typedef union _IoPplIltai  						IoPplIltai;
typedef union _IoPplIlta  						IoPplIlta;
typedef union _IoPplIuta  						IoPplIuta;
typedef union _IoPplDcdap  					IoPplDcdap;
typedef union _IoPplDc  							IoPplDc;
typedef union _IoPplDwee  					IoPplDwee;
typedef union _IoPplDwd  						IoPplDwd;
typedef union _IoPplDwcawl  				IoPplDwcawl;
typedef union _IoPplDwcawh 				IoPplDwcawh;
typedef union _IoPplDree  						IoPplDree;
typedef union _IoPplDrd  						IoPplDrd;
typedef union _IoPplDrcawl  					IoPplDrcawl;
typedef union _IoPplDrcawh  				IoPplDrcawh;
typedef union _IoPplDwis  						IoPplDwis;
typedef union _IoPplDwim  					IoPplDwim;
typedef union _IoPplDwic  						IoPplDwic;
typedef union _IoPplDwes  					IoPplDwes;
typedef union _IoPplDwdil 						IoPplDwdil;
typedef union _IoPplDwdih   					IoPplDwdih;
typedef union _IoPplDwail  					IoPplDwail;
typedef union _IoPplDwaih  					IoPplDwaih;
typedef union _IoPplDwc01id 				IoPplDwc01id;
typedef union _IoPplDwc23id  				IoPplDwc23id;
typedef union _IoPplDwc45id  				IoPplDwc45id;
typedef union _IoPplDwch67id  				IoPplDwch67id;
typedef union _IoPplDwllee  					IoPplDwllee;
typedef union _IoPplDris    						IoPplDris;
typedef union _IoPplDrim    					IoPplDrim;
typedef union _IoPplDric    					IoPplDric;
typedef union _IoPplDresl     					IoPplDresl;
typedef union _IoPplDresh    					IoPplDresh;
typedef union _IoPplDrllee    					IoPplDrllee;
typedef union _IoPplDrdil   					IoPplDrdil;
typedef union _IoPplDrdih  					IoPplDrdih;
typedef union _IoPplDrail    					IoPplDrail;
typedef union _IoPplDraih    					IoPplDraih;
typedef union _IoPplDrch01id    			IoPplDrch01id;
typedef union _IoPplDrch23id  				IoPplDrch23id;
typedef union _IoPplDrch45id   				IoPplDrch45id;
typedef union _IoPplDrch67id   				IoPplDrch67id;
typedef union _IoPplDvs    						IoPplDvs;
typedef union _IoPplDcc1   					IoPplDcc1;
typedef union _IoPplDts    						IoPplDts;
typedef union _IoPplDsl    						IoPplDsl;
typedef union _IoPplDsh     					IoPplDsh;
typedef union _IoPplDdl    						IoPplDdl;
typedef union _IoPplDdh   						IoPplDdh;
typedef union _IoPplDll    						IoPplDll;
typedef union _IoPplDlh    						IoPplDlh;
typedef union _IoPplPll    						IoPplPll;
typedef union _IoPplAcf    						IoPplAcf;
typedef union _IoPplL1s    						IoPplL1s;
typedef struct _IoPpl    							IoPpl;
typedef struct _IoPcieCoreRc   				IoPcieCoreRc;
typedef struct _IoPcieCoreEp   				IoPcieCoreEp;
typedef union _ioPcieCore    					IoPcieCore;
typedef union _IoPcieCoreControl			IoPcieCoreControl;
typedef union _IoPcieAxiClkStop   			IoPcieAxiClkStop;
typedef union _IoPcieClockControl   		IoPcieClockControl;
typedef union _IoPcieResetControl1    	IoPcieResetControl1;
typedef union _IoPcieResetControl2   	IoPcieResetControl2;
typedef union _IoPcieResetSelect1    		IoPcieResetSelect1;
typedef union _IoPcieResetSelect2    		IoPcieResetSelect2;
typedef union _IoPcieMsiRequest1    	IoPcieMsiRequest1;
typedef union _IoPcieMsiRequest2    	IoPcieMsiRequest2;
typedef union _IoPcieIntControl1    		IoPcieIntControl1;
typedef union _IoPcieIntControl2    		IoPcieIntControl2;
typedef union _IoPcieIntControl3    		IoPcieIntControl3;
typedef union _IoPcieEmControl    		IoPcieEmControl;
typedef union _IoPcieEmSelect   			IoPcieEmSelect;
typedef union _IoPcieEmMonitor    		IoPcieEmMonitor;
typedef union _IoPciePmUnlockReq    	IoPciePmUnlockReq;
typedef union _IoPcieLtrMsg    				IoPcieLtrMsg;
typedef union _IoPcieLtrMonitor1    		IoPcieLtrMonitor1;
typedef union _IoPcieLtrMonitor2    		IoPcieLtrMonitor2;
typedef union _IoPciePmControl1    		IoPciePmControl1;
typedef union _IoPciePmControl2    		IoPciePmControl2;
typedef union _IoPciePmSelect1    		IoPciePmSelect1;
typedef union _IoPciePmMonitor1    		IoPciePmMonitor1;
typedef union _IoPciePmMonitor2   		IoPciePmMonitor2;
typedef union _IoPcieConfigCom1    		IoPcieConfigCom1;
typedef union _IoPcieConfigCom2    		IoPcieConfigCom2;
typedef union _IoPcieConfigCom3 		IoPcieConfigCom3;
typedef union _IoPcieConfigCom4   		IoPcieConfigCom4;
typedef union _IoPcieConfigCom5    		IoPcieConfigCom5;
typedef union _IoPcieConfigCom6   		IoPcieConfigCom6;
typedef union _IoPcieCfgMonitor1   		IoPcieCfgMonitor1;
typedef union _IoPcieCfgMonitor2   		IoPcieCfgMonitor2;
typedef union _IoPcieCfgMonitor3   		IoPcieCfgMonitor3;
typedef union _IoPcieCfgMonitor4   		IoPcieCfgMonitor4;
typedef union _IoPcieCfgMonitor5   		IoPcieCfgMonitor5;
typedef union _IoPcieDebugMonitor1   IoPcieDebugMonitor1;
typedef union _IoPcieDebugMonitor2   IoPcieDebugMonitor2;
typedef union _IoPcieDebugMonitor3   IoPcieDebugMonitor3;
typedef struct _IoPcieDebugMonitor4   IoPcieDebugMonitor4;
typedef union _IoPcieMsgMonitor1   	IoPcieMsgMonitor1;
typedef struct _IoPcieMsgMonitor3   		IoPcieMsgMonitor3;
typedef union _IoPcieLinkMonitor   		IoPcieLinkMonitor;
typedef union _IoPcieToMonitor1   		IoPcieToMonitor1;
typedef union _IoPcieToMonitor2   		IoPcieToMonitor2;
typedef union _IoPcieToMonitor3 			IoPcieToMonitor3;
typedef union _IoPcieToMonitor4  		IoPcieToMonitor4;
typedef union _IoPcieTransmitMonitor IoPcieTransmitMonitor;
typedef union _IoPciePipeMonitor  		IoPciePipeMonitor;
typedef union _IoPciePhyMonitor  		IoPciePhyMonitor;
typedef struct _IoPcieMonitorBar0S  		IoPcieMonitorBar0S;
typedef struct _IoPcieMonitorBar0L  		IoPcieMonitorBar0L;
typedef union _IoPcieMonitorBar1S  	IoPcieMonitorBar1S;
typedef union _IoPcieMonitorBar1L  		IoPcieMonitorBar1L;
typedef struct _IoPcieMonitorBar2S  		IoPcieMonitorBar2S;
typedef struct _IoPcieMonitorBar2L  		IoPcieMonitorBar2L;
typedef union _IoPcieMonitorBar3S  	IoPcieMonitorBar3S;
typedef union _IoPcieMonitorBar3L  		IoPcieMonitorBar3L;
typedef struct _IoPcieMonitorBar4S  		IoPcieMonitorBar4S;
typedef struct _IoPcieMonitorBar4L   	IoPcieMonitorBar4L;
typedef union _IoPcieMonitorBar5S  	IoPcieMonitorBar5S;
typedef union _IoPcieMonitorBar5L  		IoPcieMonitorBar5L;
typedef union _IoPcieMonitorEromS  	IoPcieMonitorEromS;
typedef union _IoPcieMonitorEromL  	IoPcieMonitorEromL;
typedef struct _IoPcie  							IoPcie;
typedef struct _SnsPcie 							SnsPcie;
typedef struct _SnsPciePrivate 				SnsPciePrivate;


/*----------------------------------------------*/
/*	Core Register								*/
/*----------------------------------------------*/
/* Device ID and Vendor ID (Offset 0000h) */
union _IoDevIdVendId {
	unsigned long		word;
	struct {
		unsigned long	vid				:16;
		unsigned long	did				:16;
	} bit;
};

/* Status Command (Offset 0004h) */
union _IoStatusCommand {
	unsigned long		word;
	struct {
		unsigned long	ios				:1;
		unsigned long	ms				:1;
		unsigned long	bme				:1;
		unsigned long					:3;
		unsigned long	per				:1;
		unsigned long					:1;
		unsigned long	serre			:1;
		unsigned long					:1;
		unsigned long	id				:1;
		unsigned long					:8;
		unsigned long	is				:1;
		unsigned long	cl				:1;
		unsigned long					:3;
		unsigned long	mdpe			:1;
		unsigned long					:2;
		unsigned long	sta				:1;
		unsigned long	rta				:1;
		unsigned long	rma				:1;
		unsigned long	sse				:1;
		unsigned long	dpe				:1;
	} bit;
};

/* Class Code and Revision ID (Offset 0008h) */
union _IoClassCodeRevId {
	unsigned long		word;
	struct {
		unsigned long	rid 			:8;
		unsigned long	pi				:8;
		unsigned long	scc				:8;
		unsigned long	bcc				:8;
	} bit;
};

/* Header Type and Cache Line Size (Offset 000Ch) */
union _IoHdrTypeCacheLineSize {
	unsigned long		word;
	struct {
		unsigned long	cls 			:8;
		unsigned long					:8;
		unsigned long	ht 				:7;
		unsigned long	mfs				:1;
		unsigned long					:8;
	} bit;
};

/* Primary, Secondary, Subordinate Bus Numbers and Latency Timer (Offset 0018h) */
union _IoSecLatTimerSubBusSecBusPriBus {
	unsigned long		word;
	struct {
		unsigned long	pbn 				:8;
		unsigned long	subbn			:8;
		unsigned long	secbn			:8;
		unsigned long	slt					:8;
	} bit;
};

/* Secondary Status and IO Limit and IO Base (Offset 001Ch) <RC> */
union _IoSecStatIoLimitIoBase {
	unsigned long		word;
	struct {
		unsigned long	iobaIoa 		:1;
		unsigned long		 			:3;
		unsigned long	ioba			:4;
		unsigned long	iolIoa 		:1;
		unsigned long		 			:3;
		unsigned long	iol				:4;
		unsigned long					:8;
		unsigned long	mdpe			:1;
		unsigned long					:2;
		unsigned long	sta				:1;
		unsigned long	rta				:1;
		unsigned long	rma				:1;
		unsigned long	rse				:1;
		unsigned long	dpe				:1;
	} bit;
};

/* Memory Limit and Memory Base (Offset 0020h) <RC> */
union _IoMemLimitMemBase {
	unsigned long		word;
	struct {
		unsigned long						:4;
		unsigned long	mba				:12;
		unsigned long						:4;
		unsigned long	ml				:12;
	} bit;
};


/* Prefetchable Memory Limit and Prefetchable Memory Base Address (Offset 0024h) <RC> */
union _IoPrefMemLimitPrefMemBase {
	unsigned long		word;
	struct {
		unsigned long	pmd				:1;
		unsigned long						:3;
		unsigned long	pmba			:12;
		unsigned long	pmld			:1;
		unsigned long						:3;
		unsigned long	pml				:12;
	} bit;
};

/* Prefetchable Base Upper (Offset 0028h) <RC> */
union _IoPrefBaseUpper {
	unsigned long		word;
	struct {
		unsigned long	pbau32			:32;
	} bit;
};

/* Prefetchable Limit Upper (Offset 002Ch) <RC> */
union _IoPrefLimitUpper {
	unsigned long		word;
	struct {
		unsigned long	pmlu32			:32;
	} bit;
};

/* IO Limit Upper and IO Base Upper (Offset 0030h) <RC> */
union _IoIoLimitUpperIoBaseUpper {
	unsigned long		word;
	struct {
		unsigned long	iobau16			:16;
		unsigned long	iolu16				:16;
	} bit;
};

/* Capabilities Pointer (Offset 0034h) */
union _IoCapPtr {
	unsigned long		word;
	struct {
		unsigned long	ncp				:8;		/* New Capabilities Pointer */
		unsigned long						:24;
	} bit;
};

/* Expansion ROM Base Address (RC:Offset 0038h, EP: Offset 0030h) */
union _IoExpRomBar {
	unsigned long		word;
	struct {
		unsigned long	erome			:1;
		unsigned long						:10;
		unsigned long	ba				:21;
	} bit;
};

/* Bridge Control Interrupt Pin and Interrupt Line (Offset 003Ch) <RC> */
union _IoBridgeCtrlIntPinIntLine {
	unsigned long		word;
	struct {
		unsigned long	il	 				:8;
		unsigned long	ip					:8;
		unsigned long	per				:1;
		unsigned long	serre			:1;
		unsigned long	isae				:1;
		unsigned long	vgae				:1;
		unsigned long	vga16d		:1;
		unsigned long						:1;
		unsigned long	sbr				:1;
		unsigned long						:9;
	} bit;
};

/* Type1 Configuration Space Header */
struct _IoT1csh {
	IoDevIdVendId										devIdVendId;										/* +0000 - 0003h */
	IoStatusCommand									statusCommand;								/* +0004 - 0007h */
	IoClassCodeRevId									classCodeRevId;									/* +0008 - 000Bh */
	IoHdrTypeCacheLineSize						hdrTypeCacheLineSize;						/* +000C - 000Fh */
	unsigned char										dmy00100017[0x0018-0x0010];			/* +0010 - 0017h */
	IoSecLatTimerSubBusSecBusPriBus		secLatTimerSubBusSecBusPriBus;	/* +0018 - 001Bh */
	IoSecStatIoLimitIoBase							secStatIoLimitIoBase;					/* +001C - 001Fh */
	IoMemLimitMemBase							memLimitMemBase;						/* +0020 - 0023h */
	IoPrefMemLimitPrefMemBase				prefMemLimitPrefMemBase;		/* +0024 - 0027h */
	IoPrefBaseUpper									prefBaseUpper;								/* +0028 - 002Bh */
	IoPrefLimitUpper									prefLimitUpper;								/* +002C - 002Fh */
	IoIoLimitUpperIoBaseUpper					ioLimitUpperIoBaseUpper;			/* +0030 - 0033h */
	IoCapPtr													capPtr;												/* +0034 - 0037h */
	IoExpRomBar											expRomBar;									/* +0038 - 003Bh */
	IoBridgeCtrlIntPinIntLine						bridgeCtrlIntPinIntLine;					/* +003C - 003Fh */
};

/* Base Address Register 0 (Offset 010h) <EP> */
/* Base Address Register 1 (Offset 014h) <EP> */
/* Base Address Register 2 (Offset 018h) <EP> */
/* Base Address Register 3 (Offset 01Ch) <EP> */
/* Base Address Register 4 (Offset 020h) <EP> */
/* Base Address Register 5 (Offset 024h) <EP> */
union _IoBar {
	unsigned long		word;
	struct		{
		unsigned long	miosi			:1;
		unsigned long	mt				:2;
		unsigned long	pf					:1;
		unsigned long	ba				:28;
	} bit;
};

/* CardBus CIS Pointer (Offset 0028h) <EP> */
union _IoCardbusCisPtr {
	unsigned long		word;
	struct {
		unsigned long	ccp	 			:32;
	} bit;
};

/* Subsystem ID and Subsystem Vendor ID (Offset 002Ch) <EP> */
union _IoSubsysIdSubsysVId {
	unsigned long		word;
	struct {
		unsigned long	svid	 		:16;
		unsigned long	sid	 			:16;
	} bit;
};

/* Interrupt Pin and Interrupt Line (Offset 003Ch) <EP> */
union _IoIntPinIntLine {
	unsigned long		word;
	struct {
		unsigned long	il	 			:8;
		unsigned long	ip				:8;
		unsigned long					:16;
	} bit;
};

/* Type0 Configuration Space Header */
struct _IoT0csh {
	IoDevIdVendId						devIdVendId;							/* +0000 - 0003h */
	IoStatusCommand					statusCommand;					/* +0004 - 0007h */
	IoClassCodeRevId					classCodeRevId;						/* +0008 - 000Bh */
	IoHdrTypeCacheLineSize		hdrTypeCacheLineSize;			/* +000C - 000Fh */
	IoBar										bar[6];										/* +0010 - 0027h */
	IoCardbusCisPtr						cardbusCisPtr;				/* +0028 - 002Bh */
	IoSubsysIdSubsysVId				subsysIdSubsysVId;		/* +002C - 002Fh */
	IoExpRomBar							expRomBar;							/* +0030 - 0033h */
	IoCapPtr									capPtr;										/* +0034 - 0037h */
	unsigned char						dmy0038003b[0x003C-0x0038];	/* +0038 - 003Bh */
	IoIntPinIntLine						intPinIntLine;					/* +003C - 003Fh */
};

/* Power Management Capabilities (Offset 0040h) */
union _IoPmcrPmc {
	unsigned long		word;
	struct {
		unsigned long	cid				: 8;
		unsigned long	ncp				: 8;
		unsigned long	ver				: 3;
		unsigned long					: 1;
		unsigned long					: 1;
		unsigned long	dsi				: 1;
		unsigned long	ac				: 3;
		unsigned long	d1s				: 1;
		unsigned long	d2s				: 1;
		unsigned long	pmes			: 5;
	} bit;
};

/* Power Management Control / Status (Offset 0044h) */
union _IoPmcrPmcs {
	unsigned long		word;
	struct {
		unsigned long	ps				:2;
		unsigned long					:1;
		unsigned long	nsr				:1;
		unsigned long					:4;
		unsigned long	pmeen			:1;
		unsigned long	dsel			:4;
		unsigned long	ds				:2;
		unsigned long	pmes			:1;
		unsigned long					:6;
		unsigned long	b2b3s			:1;
		unsigned long	bpcce			:1;
		unsigned long	data			:8;
	} bit;
};

/* Power Management Capabilities Register */
struct _IoPmcr {
	IoPmcrPmc			pmc;							/* +0040 - 0043h */
	IoPmcrPmcs		pmcs;							/* +0044 - 0047h */
	unsigned char			dmy0048004f[0x0050-0x0048];	/* +0048 - 004Fh */
};

/* MSI Cap ID / Next Item / Message Control (Offset 050h) */
union _IoMsicrMcinc {
	unsigned long		word;
	struct		{
		unsigned long	cid				:8;
		unsigned long	np				:8;
		unsigned long	msie			:1;
		unsigned long	mmc			:3;
		unsigned long	mme			:3;
		unsigned long	ac64				:1;
		unsigned long	pvmc			:1;
		unsigned long						:7;
	} bit;
};

/* Message Address (Offset 054h) */
union _IoMsicrMla {
	unsigned long		word;
	struct	{
		unsigned long						:2;
		unsigned long	mla				:30;
	} bit;
};

/* Message Upper Address (Offset 058h) */
union _IoMsicrMua {
	unsigned long		word;
	struct		{
		unsigned long	mua				:32;
	} bit;
};

/* Message Data (Offset 05Ch) */
union	_IoMsicrMd	{
	unsigned long		word;
	struct		{
		unsigned long	md				:16;
		unsigned long						:16;
	} bit;
};

/* Mask Bits (Offset 060h) */
union _IoMsicrMmb {
	unsigned long		word;
	struct		{
		unsigned long	mmb				:32;
	} bit;
};

/* Pending Bits (Offset 064h) */
union _IoMsicrMpb {
	unsigned long		word;
	struct		{
		unsigned long	mpb				:32;
	} bit;
};

/* MSI Capability Register */
struct _IoMsicr {
	IoMsicrMcinc		msiCapIdNextCtrl;		/* +0050 - 0053h */
	IoMsicrMla			msiLowAdr;					/* +0054 - 0057h */
	IoMsicrMua			msiUppAdr;					/* +0058 - 005Bh */
	IoMsicrMd			msiData;						/* +005C - 005Fh */
	IoMsicrMmb		msiMaskBits;				/* +0060 - 0063h */
	IoMsicrMpb		msiPendingBits;			/* +0064 - 0067h */
};

/* Cap ID / Next Item (Offset 0070h) */
/* PCI Express Capability Register (Offset 0072h) */
union _IoPciecrCr {
	unsigned long		word;
	struct {
		unsigned long	cid				:8;
		unsigned long	np				:8;

		unsigned long	cv					:4;
		unsigned long	dpt				:4;
		unsigned long	si					:1;
		unsigned long	imn				:5;
		unsigned long						:2;
	} bit;
};

/* Device Capability Register (Offset 0074h) */
union _IoPciecrDcr {
	unsigned long		word;
	struct {
		unsigned long	mpss			:3;
		unsigned long	pfs				:2;
		unsigned long	etfs				:1;
		unsigned long	el0al			:3; // EP only
		unsigned long	el1al			:3; // EP only
		unsigned long					:3;
		unsigned long	rber			:1;
		unsigned long					:2;
		unsigned long	csplv			:8; // EP only
		unsigned long	cspls			:2; // EP only
		unsigned long	flrc			:1; // EP only
		unsigned long					:3;
	} bit;
};

/* Device Control Register (Offset 0078h)  */
/* Device Status Register (Offset 007Ah)  */
union _IoPciecrDcsr {
	unsigned long		word;
	struct {
		unsigned long	cere			:1;
		unsigned long	nfere			:1;
		unsigned long	fere			:1;
		unsigned long	urre			:1;
		unsigned long	ero				:1;
		unsigned long	mps				:3;
		unsigned long	etfe			:1;
		unsigned long	pfe				:1;
		unsigned long	appme			:1;
		unsigned long	ens				:1;
		unsigned long	mrrs			:3;
		unsigned long	iflr			:1;

		unsigned long	ced				:1;
		unsigned long	nfed			:1;
		unsigned long	fed				:1;
		unsigned long	urd				:1;
		unsigned long	auxpd			:1;
		unsigned long	tp				:1;
		unsigned long					:10;
	} bit;
};

/* Link Capability Register (Offset 007Ch)  */
union _IoPciecrLcr {
	unsigned long		word;
	struct {
		unsigned long	mls				:4;
		unsigned long	mlw				:6;
		unsigned long	aspms			:2;
		unsigned long	l0el				:3;
		unsigned long	l1el				:3;
		unsigned long	cpm				:1;
		unsigned long	sderc			:1;
		unsigned long	dlllarc			:1;
		unsigned long	lbnc				:1;
		unsigned long	aspmoc		:1;
		unsigned long						:1;
		unsigned long	pn				:8;
	} bit;
};

/* Link Control Register (Offset 0080h) */
/* Link Status Register (Offset 0082h) */
union _IoPciecrLcsr {
	unsigned long		word;
	struct {
		unsigned long	aspmc			:2;
		unsigned long					:1;
		unsigned long	rcb				:1;
		unsigned long	ld				:1;
		unsigned long	rl				:1;
		unsigned long	ccc				:1;
		unsigned long	es				:1;
		unsigned long	ecpm			:1;
		unsigned long	hawd			:1;
		unsigned long	lbmie			:1;
		unsigned long	labie			:1;
		unsigned long						:2;
		unsigned long	drssc			:2;

		unsigned long	cls				:4;
		unsigned long	nlw				:6;
		unsigned long					:1;
		unsigned long	lt				:1;
		unsigned long	scc				:1;
		unsigned long	dllla			:1;
		unsigned long	lbms			:1;
		unsigned long	labs			:1;
	} bit;
};

/* Slot Capabilities Register (Offset 0084h) <RC> */
union _IoPciecrScr {
	unsigned long		word;
	struct {
		unsigned long	abp				:1;
		unsigned long	pcp				:1;
		unsigned long	mrlsp			:1;
		unsigned long	aip				:1;
		unsigned long	pip				:1;
		unsigned long	hps				:1;
		unsigned long	hpc				:1;
		unsigned long	splv				:8;
		unsigned long	spls				:2;
		unsigned long	eip				:1;
		unsigned long	nccs				:1;
		unsigned long	psn				:13;
	} bit;
};

/* Slot Control Register (Offset 0088h) <RC> */
/* Slot Status Register (Offset 008Ah) <RC> */
union _IoPciecrScsr {
	unsigned long		word;
	struct {
		unsigned long	abpe			:1;
		unsigned long	pfde			:1;
		unsigned long	mrlsce			:1;
		unsigned long	pdce			:1;
		unsigned long	ccie			:1;
		unsigned long	hpie			:1;
		unsigned long	aic				:2;
		unsigned long	pic				:2;
		unsigned long	pcc				:1;
		unsigned long	eic				:1;
		unsigned long	dllsce			:1;
		unsigned long					:3;

		unsigned long	abp				:1;
		unsigned long	pfd				:1;
		unsigned long	mrlsc			:1;
		unsigned long	pdc				:1;
		unsigned long	cc				:1;
		unsigned long	mrlss			:1;
		unsigned long	pds				:1;
		unsigned long	eis				:1;
		unsigned long	dllsc			:1;
		unsigned long					:7;
	} bit;
};

/* Root Control Register (Offset 008Ch) <RC> */
/* Root Capability Register (Offset 008Eh) <RC> */
union _IoPciecrRccr {
	unsigned long		word;
	struct {
		unsigned long	secee			:1;
		unsigned long	senfee			:1;
		unsigned long	sefee			:1;
		unsigned long	pmeie			:1;
		unsigned long	crssve			:1;
		unsigned long						:11;

		unsigned long	crssv			:1;
		unsigned long						:15;
	} bit;
};

/* Root Status Register (Offset 0090h) <RC> */
union _IoPciecrRsr {
	unsigned long		word;
	struct {
		unsigned long	pmerid			:16;
		unsigned long	pmes				:1;
		unsigned long	pmepend		:1;
		unsigned long							:14;
	} bit;
};

/* Device Capabilities 2 Register (Offset 0094h) */
union _IoPciecrDc2r {
	unsigned long		word;
	struct {
		unsigned long	ctrs					:4;
		unsigned long	ctds					:1;
		unsigned long	arifs					:1;
		unsigned long	aors					:1;
		unsigned long	_32aocs			:1;
		unsigned long	_64aocs			:1;
		unsigned long	_128cascs		:1;
		unsigned long	nroprprp			:1;
		unsigned long	ltrms				:1;
		unsigned long	tphcs				:2;
		unsigned long	lnscls				:2;
		unsigned long							:2;
		unsigned long	obffs				:2;
		unsigned long							:12;
	} bit;
};

/* Device Control2 Register (Offset 0098h) */
/* Device Status2 Register (Offset 009Ah) */
union _IoPciecrDc2sr {
	unsigned long		word;
	struct {
		unsigned long	ctv				:4;
		unsigned long	ctd				:1;
		unsigned long	arife				:1;
		unsigned long						:4;
		unsigned long	ltrme			:1;
		unsigned long						:5;

		unsigned long					:16;
	} bit;
};

/* Link Capability2 Register (Offset 009Ch) */
union _IoPciecrLc2r {
	unsigned long		word;
	struct {
		unsigned long						:1;
		unsigned long	slsv				:7;
		unsigned long	clsp				:1;
		unsigned long						:22;
		unsigned long	drss				:1;
	} bit;
};

/* Link Control2 Register (Offset 00A0h) */
/* Link Status2 Register (Offset 00A2h) */
union _IoPciecrLc2sr {
	unsigned long		word;
	struct {
		unsigned long	tls				:4;
		unsigned long	ec				:1;
		unsigned long	hasd			:1;
		unsigned long	sde				:1;
		unsigned long	tm				:3;
		unsigned long	emc				:1;
		unsigned long	csos			:1;
		unsigned long	cpde			:4;

		unsigned long	cdel			:1;
		unsigned long					:11;
		unsigned long	dcp				:3;
		unsigned long	drsmr			:1;
	} bit;
};

/* PCI Express Capability Register */
struct _IoPciecr {
	IoPciecrCr		cr;								/* +0070 - 0073h */
	IoPciecrDcr		dcr;							/* +0074 - 0077h */
	IoPciecrDcsr	dcsr;							/* +0078 - 007Bh */
	IoPciecrLcr		lcr;							/* +007C - 007Fh */
	IoPciecrLcsr	lcsr;							/* +0080 - 0083h */
	IoPciecrScr		scr;							/* +0084 - 0087h */	// RC only
	IoPciecrScsr	scsr;							/* +0088 - 008Bh */	// RC only
	IoPciecrRccr	rccr;							/* +008C - 008Fh */	// RC only
	IoPciecrRsr		rsr;							/* +0090 - 0093h */	// RC only
	IoPciecrDc2r	dc2r;							/* +0094 - 0097h */
	IoPciecrDc2sr	dc2sr;							/* +0098 - 009Bh */
	IoPciecrLc2r	lc2r;							/* +009C - 009Fh */
	IoPciecrLc2sr	lc2sr;							/* +00A0 - 00A3h */
	unsigned char			dmy00a400af[0x00B0-0x00A4];	/* +00A4 - 00AFh */
};

/* Advanced Error Reporting Enhanced Capability Header (Offset 0100h) */
union _IoAercAerech {
	unsigned long		word;
	struct {
		unsigned long	pcieecid		:16;
		unsigned long	capv				:4;
		unsigned long	nco				:12;
	} bit;
};

/* Uncorrectable Error Status Register (Offset 0104h) */
union _IoAercUesr {
	unsigned long		word;
	struct {
		unsigned long						:4;
		unsigned long	dlpes			:1;
		unsigned long	sdes				:1;
		unsigned long						:6;
		unsigned long	ptlps			:1;
		unsigned long	fcpes			:1;
		unsigned long	cts				:1;
		unsigned long	cas				:1;
		unsigned long	ucs				:1;
		unsigned long	ros				:1;
		unsigned long	mtlps			:1;
		unsigned long	ecrces			:1;
		unsigned long	ures				:1;
		unsigned long						:1;
		unsigned long	uies				:1;
		unsigned long						:2;
		unsigned long	tlppbes		:1;
		unsigned long						:6;
	} bit;
};

/* Uncorrectable Error Mask Register (Offset 0108h) */
union _IoAercUemr {
	unsigned long		word;
	struct {
		unsigned long						:4;
		unsigned long	dlpem			:1;
		unsigned long	sdem			:1;
		unsigned long						:6;
		unsigned long	ptlpm			:1;
		unsigned long	fcpem			:1;
		unsigned long	ctm				:1;
		unsigned long	cam				:1;
		unsigned long	ucm				:1;
		unsigned long	rom				:1;
		unsigned long	mtlpm			:1;
		unsigned long	ecrcem		:1;
		unsigned long	urem			:1;
		unsigned long						:1;
		unsigned long	uiem			:1;
		unsigned long						:1;
		unsigned long	aoebm			:1;
		unsigned long	tlppbem		:1;
		unsigned long						:6;
	} bit;
};

/* Uncorrectable Error Severity Register (Offset 010Ch) */
union _IoAercUesvr {
	unsigned long		word;
	struct {
		unsigned long						:4;
		unsigned long	dlpes			:1;
		unsigned long	sdes				:1;
		unsigned long						:6;
		unsigned long	ptlps			:1;
		unsigned long	fcpes			:1;
		unsigned long	ctes				:1;
		unsigned long	caes				:1;
		unsigned long	uces				:1;
		unsigned long	roes				:1;
		unsigned long	mtlps			:1;
		unsigned long	ecrces			:1;
		unsigned long	ures				:1;
		unsigned long						:1;
		unsigned long	uies				:1;
		unsigned long						:1;
		unsigned long	aoebs			:1;
		unsigned long	tlppbes		:1;
		unsigned long						:6;
	} bit;
};

/* Correctable Error Status Register (Offset 0110h) */
union _IoAercCesr {
	unsigned long		word;
	struct {
		unsigned long	res				:1;
		unsigned long						:5;
		unsigned long	btlps			:1;
		unsigned long	bdllps			:1;
		unsigned long	rnrs				:1;
		unsigned long						:3;
		unsigned long	rtts				:1;
		unsigned long	anfes			:1;
		unsigned long	cies				:1;
		unsigned long	hlos				:1;
		unsigned long						:16;
	} bit;
};

/* Correctable Error Mask Register (Offset 0114h) */
union _IoAercCemr {
	unsigned long		word;
	struct {
		unsigned long	rem				:1;
		unsigned long						:5;
		unsigned long	btlpm			:1;
		unsigned long	bdllpm		:1;
		unsigned long	rnrm			:1;
		unsigned long						:3;
		unsigned long	rttm				:1;
		unsigned long	anfem			:1;
		unsigned long	ciem			:1;
		unsigned long	hlom			:1;
		unsigned long						:16;
	} bit;
};

/* Advanced Error Capabilities and Control Register (Offset 0118h) */
union _IoAercAeccr {
	unsigned long		word;
	struct {
		unsigned long	fep				:5;
		unsigned long	ecrcgc			:1;
		unsigned long	ecrcge			:1;
		unsigned long	ecrccc			:1;
		unsigned long	ecrcce			:1;
		unsigned long	mhrc			:1;
		unsigned long	mhre			:1;
		unsigned long						:21;
	} bit;
};

/* Header Log Register (Offset 011Ch,0120h,0124h,0128h) */
union _IoAercHlr {
	unsigned long		word;
	struct {
		unsigned long	hlr				:32;
	} bit;
};

/* Root Error Command Register (Offset 012Ch) <RC> */
union _IoAercRecr {
	unsigned long		word;
	struct {
		unsigned long	cere				:1;
		unsigned long	nfere			:1;
		unsigned long	fere				:1;
		unsigned long						:29;
	} bit;
};

/* Root Error Status Register (Offset 0130h) <RC> */
union _IoAercResr {
	unsigned long		word;
	struct {
		unsigned long	ercorr			:1;
		unsigned long	mercorr		:1;
		unsigned long	erfnfr			:1;
		unsigned long	merfnfr		:1;
		unsigned long	fuf				:1;
		unsigned long	nfemr			:1;
		unsigned long	femr			:1;
		unsigned long						:20;
		unsigned long	aeimn			:5;
	} bit;
};

/* Error Source Identification Register (Offset 0134h) <RC> */
union _IoAercEsir {
	unsigned long		word;
	struct {
		unsigned long	ercorsi			:16;
		unsigned long	erfnfsi			:16;
	} bit;
};

/* TLP Prefix Log Register (Offset 0138h,013Ch,0140h,0144h) */
union _IoTlpplr {
	unsigned long		word;
	struct {
		unsigned long	tlpplr			:32;
	} bit;
};

/* Advanced Error Reporting Capability */
struct _IoAerc {
	IoAercAerech		aerech;							/* +0100 - 0103h */
	IoAercUesr			uesr;							/* +0104 - 0107h */
	IoAercUemr		uemr;							/* +0108 - 010Bh */
	IoAercUesvr		uesvr;							/* +010C - 010Fh */
	IoAercCesr			cesr;							/* +0110 - 0113h */
	IoAercCemr			cemr;							/* +0114 - 0117h */
	IoAercAeccr		aeccr;							/* +0118 - 011Bh */
	IoAercHlr				hlr[4];							/* +011C - 012Bh */
	IoAercRecr			recr;							/* +012C - 012Fh */	// RC Only
	IoAercResr			resr;							/* +0130 - 0133h */	// RC Only
	IoAercEsir			esir;							/* +0134 - 0137h */	// RC Only
	IoTlpplr				tlpplr[4];						/* +0138 - 0147h */
};

/* LTR Extended Capability Header (Offset 0148h) */
union _IoLtrcLtrech {
	unsigned long		word;
	struct {
		unsigned long	pcieecid		:16;
		unsigned long	capv			:4;
		unsigned long	nco				:12;
	} bit;
};

/* Max Snoop Latency Register    (Offset 014Ch) */
/* Max No-Snoop Latency Register (Offset 014Eh) */
union _IoLtrcMsnslr {
	unsigned long		word;
	struct {
		unsigned long	mslv			:10;
		unsigned long	msls			:3;
		unsigned long					:3;
		unsigned long	mnslv		:10;
		unsigned long	mnsls		:3;
		unsigned long					:3;
	} bit;
};

/* Latency Tolerance Reporting (LTR) Capability */
struct _IoLtrc {
	IoLtrcLtrech		ltrech;								/* +0148 - 014Bh */
	IoLtrcMsnslr		msnslr;							/* +014C - 014Fh */
};

/* L1 PM Substates Extended Capability Header (Offset 0150h) */
union _IoL1pmsecL1pmsech {
	unsigned long		word;
	struct {
		unsigned long	pcieecid		:16;
		unsigned long	cv					:4;
		unsigned long	nco				:12;
	} bit;
};

/* L1 PM Substates Capabilities Register (Offset 0154h) */
union _IoL1pmsecL1pmscr {
	unsigned long		word;
	struct {
		unsigned long	pcipml12s		:1;
		unsigned long	pcipml11s		:1;
		unsigned long	aspml12s			:1;
		unsigned long	aspml11s			:1;
		unsigned long	l1pmss				:1;
		unsigned long							:3;
		unsigned long	pcmrt				:8;
		unsigned long	ptpos				:2;
		unsigned long							:1;
		unsigned long	ptpov				:5;
		unsigned long							:8;
	} bit;
};

/* L1 PM Substates Control 1 Register (Offset 0158h) */
union _IoL1pmsecL1pmsc1r {
	unsigned long		word;
	struct {
		unsigned long	pcipml12e		:1;
		unsigned long	pcipml11e		:1;
		unsigned long	aspml12e		:1;
		unsigned long	aspml11e		:1;
		unsigned long							:4;
		unsigned long	cmrt					:8;
		unsigned long	ltrl12tv				:10;
		unsigned long							:3;
		unsigned long	ltrl12ts				:3;
	} bit;
};

/* L1 PM Substates Control 2 Register (Offset 015Ch) */
union _IoL1pmsecL1pmsc2r {
	unsigned long		word;
	struct {
		unsigned long	tpos			:2;
		unsigned long					:1;
		unsigned long	tpov			:5;
		unsigned long					:24;
	} bit;
};

/* L1 PM Substates Extended Capability */
struct _IoL1pmsec {
	IoL1pmsecL1pmsech	l1pmsech;					/* +0150 - 0153h */
	IoL1pmsecL1pmscr	l1pmscr;					/* +0154 - 0157h */
	IoL1pmsecL1pmsc1r	l1pmsc1r;					/* +0158 - 015Bh */
	IoL1pmsecL1pmsc2r	l1pmsc2r;					/* +015C - 015Fh */
};

/* ACK_LATENCY_TIMER_OFF (Offset 0700h) */
union _IoPplAlt {
	unsigned long		word;
	struct {
		unsigned long	rtl			:16;
		unsigned long	rtltl		:16;
	} bit;
};

/* VENDOR_SPEC_DLLP_OFF (Offset 0704h) */
union _IoPplVsd {
	unsigned long		word;
	struct {
		unsigned long	vsd			:32;
	} bit;
};

/* PORT_FORCE_OFF (Offset 0708h) */
union _IoPplPf {
	unsigned long		word;
	struct {
		unsigned long	ln			:8;
		unsigned long	fl			:4;
		unsigned long				:3;
		unsigned long	fe			:1;
		unsigned long	ls			:6;
		unsigned long				:2;
		unsigned long	csc			:8;
	} bit;
};

/* ACK_F_ASPM_CTRL_OFF (Offset 070Ch) */
union _IoPplAfac {
	unsigned long		word;
	struct {
		unsigned long	af				:8;
		unsigned long	anf			:8;
		unsigned long	ccnf			:8;
		unsigned long	l0sel			:3;
		unsigned long	l1el			:3;
		unsigned long	ea			:1;
		unsigned long					:1;
	} bit;
};

/* PORT_LINK_CTRL_OFF (Offset 0710h) */
union _IoPplPlc {
	unsigned long		word;
	struct {
		unsigned long	vsdr		:1;
		unsigned long	sd			:1;
		unsigned long	le			:1;
		unsigned long	ra			:1;
		unsigned long				:1;
		unsigned long	dle		:1;
		unsigned long				:1;
		unsigned long	flm		:1;
		unsigned long				:4;
		unsigned long				:4;
		unsigned long	lc			:6;
		unsigned long				:2;
		unsigned long				:1;
		unsigned long				:1;
		unsigned long				:1;
		unsigned long				:1;
		unsigned long				:4;
	} bit;
};

/* LANE_SKEW_OFF (Offset 0714h) */
union _IoPplLs {
	unsigned long		word;
	struct {
		unsigned long	ils				:24;
		unsigned long	fcd			:1;
		unsigned long	and			:1;
		unsigned long					:5;
		unsigned long	dltld			:1;
	} bit;
};

/* TIMER_CTRL_MAX_FUNC_NUM_OFF (Offset 0718h) */
union _IoPplTcmfn {
	unsigned long		word;
	struct {
		unsigned long	mfn			:8;
		unsigned long					:6;
		unsigned long	tmrt			:5;
		unsigned long	tman		:5;
		unsigned long					:5;
		unsigned long					:3;
	} bit;
};

/* SYMBOL_TIMER_FILTER_1_OFF (Offset 071Ch) */
union _IoPplStf1 {
	unsigned long		word;
	struct {
		unsigned long	siv			:11;
		unsigned long					:4;
		unsigned long	dfwt			:1;
		unsigned long	mr1			:16;
	} bit;
};

/* FILTER_MASK_2_OFF (Offset 0720h) */
union _IoPplFm2 {
	unsigned long		word;
	struct {
		unsigned long	mr2			:32;
	} bit;
};

/* AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF (Offset 0724h) */
union _IoPplAmodnsrc {
	unsigned long		word;
	struct {
		unsigned long	orsbe		:1;
		unsigned long					:31;
	} bit;
};

/* PL_DEBUG0_OFF (Offset 0728h) */
union _IoPplPd0 {
	unsigned long		word;
	struct {
		unsigned long	dr0			:32;
	} bit;
};

/* PL_DEBUG1_OFF (Offset 072Ch) */
union _IoPplPd1 {
	unsigned long		word;
	struct {
		unsigned long	dr1			:32;
	} bit;
};

/* TX_P_FC_CREDIT_STATUS_OFF (Offset 0730h) */
union _IoPplTpfcs {
	unsigned long		word;
	struct {
		unsigned long	tpdfc		:12;
		unsigned long	tphfc		:8;
		unsigned long					:12;
	} bit;
};

/* TX_NP_FC_CREDIT_STATUS_OFF (Offset 0734h) */
union _IoPplTnfcs {
	unsigned long		word;
	struct {
		unsigned long	tndfc		:12;
		unsigned long	tnhfc		:8;
		unsigned long					:12;
	} bit;
};

/* TX_CPL_FC_CREDIT_STATUS_OFF (Offset 0738h) */
union _IoPplTcfcs {
	unsigned long		word;
	struct {
		unsigned long	tcdfc		:12;
		unsigned long	tchfc		:8;
		unsigned long					:12;
	} bit;
};

/* QUEUE_STATUS_OFF (Offset 073Ch) */
union _IoPplQs {
	unsigned long		word;
	struct {
		unsigned long	rtfcnr		:1;
		unsigned long	trbn			:1;
		unsigned long	rqne			:1;
		unsigned long					:13;
		unsigned long	tmfc			:13;
		unsigned long					:2;
		unsigned long	tmfce		:1;
	} bit;
};

/* VC_TX_ARBI_1_OFF (Offset 0740h) */
union _IoPplVta1 {
	unsigned long		word;
	struct {
		unsigned long	wwv0		:8;
		unsigned long	wwv1		:8;
		unsigned long	wwv2		:8;
		unsigned long	wwv3		:8;
	} bit;
};

/* VC_TX_ARBI_2_OFF (Offset 0744h) */
union _IoPplVta2 {
	unsigned long		word;
	struct {
		unsigned long	wwv4		:8;
		unsigned long	wwv5		:8;
		unsigned long	wwv6		:8;
		unsigned long	wwv7		:8;
	} bit;
};

/* VC0_P_RX_Q_CTRL_OFF (Offset 0748h) */
union _IoPplVprqc {
	unsigned long		word;
	struct {
		unsigned long	vpdc		:12;
		unsigned long	vphc		:8;
		unsigned long					:1;
		unsigned long	vptqm		:3;
		unsigned long					:6;
		unsigned long	ttov			:1;
		unsigned long	vorq			:1;
	} bit;
};

/* VC0_NP_RX_Q_CTRL_OFF (Offset 074Ch) */
union _IoPplVnrqc {
	unsigned long		word;
	struct {
		unsigned long	vndc		:12;
		unsigned long	vnhc		:8;
		unsigned long					:1;
		unsigned long	vntqm		:3;
		unsigned long					:8;
	} bit;
};

/* VC0_CPL_RX_Q_CTRL_OFF (Offset 0750h) */
union _IoPplVcrqc {
	unsigned long		word;
	struct {
		unsigned long	vcdc			:12;
		unsigned long	vchc			:8;
		unsigned long					:1;
		unsigned long	vctqm		:3;
		unsigned long					:8;
	} bit;
};

/* GEN2_CTRL_OFF (Offset 080Ch) */
union _IoPplGen2c {
	unsigned long		word;
	struct {
		unsigned long	fts			:8;
		unsigned long	nol			:5;
		unsigned long	pdl			:3;
		unsigned long	alfce		:1;
		unsigned long	dsc			:1;
		unsigned long	cptc			:1;
		unsigned long	ctcr			:1;
		unsigned long	sd				:1;
		unsigned long	gei			:1;
		unsigned long					:10;
	} bit;
};

/* PHY_STATUS_OFF (Offset 0810h) */
union _IoPplPhys {
	unsigned long		word;
	struct {
		unsigned long	ps			:32;
	} bit;
};

/* PHY_CONTROL_OFF (Offset 0814h) */
union _IoPplPhyc {
	unsigned long		word;
	struct {
		unsigned long	pc			:32;
	} bit;
};

/* MSI_CTRL_ADDR_OFF (Offset 0820h) */
union _IoPplMca {
	unsigned long		word;
	struct {
		unsigned long	mca			:32;
	} bit;
};

/* MSI_CTRL_UPPER_ADDR_OFF (Offset 0824h) */
union _IoPplMcua {
	unsigned long		word;
	struct {
		unsigned long	mcua		:32;
	} bit;
};

/* MSI_CTRL_INT_0_EN_OFF (Offset 0828h) */
union _IoPplMci0e {
	unsigned long		word;
	struct {
		unsigned long	mci0e		:32;
	} bit;
};

/* MSI_CTRL_INT_0_MASK_OFF (Offset 082Ch) */
union _IoPplMci0m {
	unsigned long		word;
	struct {
		unsigned long	mci0m		:32;
	} bit;
};

/* MSI_CTRL_INT_0_STATUS_OFF (Offset 0830h) */
union _IoPplMci0s {
	unsigned long		word;
	struct {
		unsigned long	mci0s		:32;
	} bit;
};

/* MSI_GPIO_IO_OFF (Offset 0888h) */
union _IoPplMgi {
	unsigned long		word;
	struct {
		unsigned long	mgr			:32;
	} bit;
};

/* PIPE_LOOPBACK_CONTROL_OFF (Offset 08B8h) */
union _IoPplPilc {
	unsigned long		word;
	struct {
		unsigned long				:16;
		unsigned long				:6;
		unsigned long				:2;
		unsigned long				:3;
		unsigned long				:4;
		unsigned long	ple			:1;
	} bit;
};

/* MISC_CONTROL_1_OFF (Offset 08BCh) */
union _IoPplMc1 {
	unsigned long		word;
	struct {
		unsigned long	drwe		:1;
		unsigned long				:31;
	} bit;
};

/* MULTI_LANE_CONTROL_OFF (Offset 08C0h) */
union _IoPplMlc {
	unsigned long		word;
	struct {
		unsigned long	tlw			:6;
		unsigned long	dlwc		:1;
		unsigned long	us			:1;
		unsigned long				:24;
	} bit;
};

/* PHY_INTEROP_CTRL_OFF (Offset 08C4h) */
union _IoPplPhyic {
	unsigned long		word;
	struct {
		unsigned long	rc			:7;
		unsigned long				:1;
		unsigned long	l1em		:1;
		unsigned long	l1np		:1;
		unsigned long				:22;
	} bit;
};

/* LINK_FLUSH_CONTROL_OFF (Offset 08CCh) */
union _IoPplLfc {
	unsigned long		word;
	struct {
		unsigned long	afe			:1;
		unsigned long					:31;
	} bit;
};

/* AMBA_ERROR_RESPONSE_DEFAULT_OFF (Offset 08D0h) */
union _IoPplAerdr {
	unsigned long		word;
	struct {
		unsigned long	aerg		:1;
		unsigned long				:1;
		unsigned long	aerv		:1;
		unsigned long				:7;
		unsigned long	aerm		:6;
		unsigned long				:16;
	} bit;
};

/* AMBA_LINK_TIMEOUT_OFF (Offset 08D4h) */
union _IoPplAmlt {
	unsigned long		word;
	struct {
		unsigned long	ltpd		:8;
		unsigned long	lted		:1;
		unsigned long				:23;
	} bit;
};

/* AMBA_ORDERING_CTRL_OFF (Offset 08D8h) */
union _IoPplAoc {
	unsigned long		word;
	struct {
		unsigned long	amnpp		:1;
		unsigned long	ase				:1;
		unsigned long						:30;
	} bit;
};

/* COHERENCY_CONTROL_1_OFF (Offset 08E0h) */
union _IoPplCc1 {
	unsigned long		word;
	struct {
		unsigned long	cmv			:1;
		unsigned long					:1;
		unsigned long	cmbla		:30;
	} bit;
};

/* COHERENCY_CONTROL_2_OFF (Offset 08E4h) */
union _IoPplCc2 {
	unsigned long		word;
	struct {
		unsigned long	cmbha		:32;
	} bit;
};

/* COHERENCY_CONTROL_3_OFF (Offset 08E8h) */
union _IoPplCc3 {
	unsigned long		word;
	struct {
		unsigned long						:3;
		unsigned long	cmarm		:4;
		unsigned long						:4;
		unsigned long	cmawm		:4;
		unsigned long						:4;
		unsigned long	cmarv			:4;
		unsigned long						:4;
		unsigned long	cmawv			:4;
		unsigned long						:1;
	} bit;
};

/* AXI_MSTR_MSG_ADDR_LOW_OFF (Offset 08F0h) */
union _IoPplAmmal {
	unsigned long		word;
	struct {
		unsigned long					:12;
		unsigned long	camal		:20;
	} bit;
};

/* AXI_MSTR_MSG_ADDR_HIGH_OFF (Offset 08F4h) */
union _IoPplAmmah {
	unsigned long		word;
	struct {
		unsigned long	camah		:32;
	} bit;
};

/* IATU_VIEWPORT_OFF (Offset 0900h) */
union _IoPplIv {
	unsigned long		word;
	struct {
		unsigned long	ri			:1;
		unsigned long				:30;
		unsigned long	rd			:1;
	} bit;
};

/* IATU_REGION_CTRL_1_OFF_OUTBOUND_0 (Offset 0904h) */
/* IATU_REGION_CTRL_1_OFF_INBOUND_0  (Offset 0904h) */
union _IoPplIrc1 {
	unsigned long		word;
	struct {
		unsigned long	type		:5;
		unsigned long	tc			:3;
		unsigned long	td			:1;
		unsigned long	attr		:2;
		unsigned long				:5;
		unsigned long	at			:2;
		unsigned long				:2;
		unsigned long	c1fn		:3;
		unsigned long				:9;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF_OUTBOUND_0 (Offset 0908h) */
union _IoPplIrc2o {
	unsigned long		word;
	struct {
		unsigned long	mc			:8;
		unsigned long	tag			:8;
		unsigned long	tse			:1;
		unsigned long					:2;
		unsigned long	fb				:1;
		unsigned long	snp			:1;
		unsigned long					:1;
		unsigned long	ip				:1;
		unsigned long	hse			:1;
		unsigned long					:3;
		unsigned long	db			:1;
		unsigned long	csm			:1;
		unsigned long	im			:1;
		unsigned long					:1;
		unsigned long	re			:1;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF_INBOUND_0 (Offset 0908h) */
union _IoPplIrc2i {
	unsigned long		word;
	struct {
		unsigned long	mc			:8;
		unsigned long	bn			:3;
		unsigned long					:3;
		unsigned long	tcme		:1;
		unsigned long	tdme		:1;
		unsigned long	attrme		:1;
		unsigned long					:1;
		unsigned long	atme		:1;
		unsigned long	fnme		:1;
		unsigned long					:1;
		unsigned long	mcme		:1;
		unsigned long					:1;
		unsigned long	salte			:1;
		unsigned long	rc				:2;
		unsigned long					:1;
		unsigned long	ftmc			:1;
		unsigned long	csm			:1;
		unsigned long	im			:1;
		unsigned long	mm			:1;
		unsigned long	re				:1;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF */
union _IoPplIrc2 {
	unsigned long		word;
	IoPplIrc2o	ob;
	IoPplIrc2i	ib;
};

/* IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0 (Offset 090Ch) */
/* IATU_LWR_BASE_ADDR_OFF_INBOUND_0  (Offset 090Ch) */
union _IoPplIlba {
	unsigned long		word;
	struct {
		unsigned long	lbh			:16;
		unsigned long	lbr			:16;
	} bit;
};

/* IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0 (Offset 0910h) */
/* IATU_UPPER_BASE_ADDR_OFF_INBOUND_0  (Offset 0910h) */
union _IoPplIuba {
	unsigned long		word;
	struct {
		unsigned long	ubr			:32;
	} bit;
};

/* IATU_LIMIT_ADDR_OFF_OUTBOUND_0 (Offset 0914h) */
/* IATU_LIMIT_ADDR_OFF_INBOUND_0  (Offset 0914h) */
union _IoPplIla {
	unsigned long		word;
	struct {
		unsigned long	lah			:16;
		unsigned long	lar			:16;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0 (Offset 0918h) */
union _IoPplIltao {
	unsigned long		word;
	struct {
		unsigned long	ltro		:32;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF_INBOUND_0 (Offset 0918h) */
union _IoPplIltai {
	unsigned long		word;
	struct {
		unsigned long	lth			:16;
		unsigned long	ltr				:16;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF */
union _IoPplIlta {
	unsigned long		word;
	IoPplIltao	ob;
	IoPplIltai		ib;
};

/* IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0 (Offset 091Ch) */
/* IATU_UPPER_TARGET_ADDR_OFF_INBOUND_0 (Offset 091Ch) */
union _IoPplIuta {
	unsigned long		word;
	struct {
		unsigned long	utr			:32;
	} bit;
};

/* DMA_CTRL_DATA_ARB_PRIOR_OFF (Offset 0970h) */
union _IoPplDcdap {
	unsigned long		word;
	struct {
		unsigned long	rw			:3;
		unsigned long	wctw		:3;
		unsigned long	rctw			:3;
		unsigned long	rtw			:3;
		unsigned long					:20;
	} bit;
};

/* DMA_CTRL_OFF (Offset 0978h) */
union _IoPplDc {
	unsigned long		word;
	struct {
		unsigned long	ndwc		:4;
		unsigned long					:12;
		unsigned long	ndrc			:4;
		unsigned long					:12;
	} bit;
};

/* DMA_WRITE_ENGINE_EN_OFF (Offset 097Ch) */
union _IoPplDwee {
	unsigned long		word;
	struct {
		unsigned long	dwe			:1;
		unsigned long					:31;
	} bit;
};

/* DMA_WRITE_DOORBELL_OFF (Offset 0980h) */
union _IoPplDwd {
	unsigned long		word;
	struct {
		unsigned long	wdn			:3;
		unsigned long					:28;
		unsigned long	ws			:1;
	} bit;
};

/* DMA_WRITE_CHANNEL_ARB_WEIGHT_LOW_OFF (Offset 0988h) */
union _IoPplDwcawl {
	unsigned long		word;
	struct {
		unsigned long	wc0w		:5;
		unsigned long	wc1w		:5;
		unsigned long	wc2w		:5;
		unsigned long	wc3w		:5;
		unsigned long					:12;
	} bit;
};

/* DMA_WRITE_CHANNEL_ARB_WEIGHT_HIGH_OFF (Offset 098Ch) */
union _IoPplDwcawh {
	unsigned long		word;
	struct {
		unsigned long	wc4w		:5;
		unsigned long	wc5w		:5;
		unsigned long	wc6w		:5;
		unsigned long	wc7w		:5;
		unsigned long					:12;
	} bit;
};

/* DMA_READ_ENGINE_EN_OFF (Offset 099Ch) */
union _IoPplDree {
	unsigned long		word;
	struct {
		unsigned long	dre			:1;
		unsigned long				:31;
	} bit;
};

/* DMA_READ_DOORBELL_OFF (Offset 09A0h) */
union _IoPplDrd {
	unsigned long		word;
	struct {
		unsigned long	rdn			:3;
		unsigned long				:28;
		unsigned long	rs			:1;
	} bit;
};

/* DMA_READ_CHANNEL_ARB_WEIGHT_LOW_OFF (Offset 09A8h) */
union _IoPplDrcawl {
	unsigned long		word;
	struct {
		unsigned long	rc0w		:5;
		unsigned long	rc1w		:5;
		unsigned long	rc2w		:5;
		unsigned long	rc3w		:5;
		unsigned long					:12;
	} bit;
};

/* DMA_READ_CHANNEL_ARB_WEIGHT_HIGH_OFF (Offset 09ACh) */
union _IoPplDrcawh {
	unsigned long		word;
	struct {
		unsigned long	rc4w		:5;
		unsigned long	rc5w		:5;
		unsigned long	rc6w		:5;
		unsigned long	rc7w		:5;
		unsigned long					:12;
	} bit;
};

/* DMA_WRITE_INT_STATUS_OFF (Offset 09BCh) */
union _IoPplDwis {
	unsigned long		word;
	struct {
		unsigned long	wdis			:8;
		unsigned long					:8;
		unsigned long	wais			:8;
		unsigned long					:8;
	} bit;
};

/* DMA_WRITE_INT_MASK_OFF (Offset 09C4h) */
union _IoPplDwim {
	unsigned long		word;
	struct {
		unsigned long	wdim		:2;
		unsigned long					:14;
		unsigned long	waim		:2;
		unsigned long					:14;
	} bit;
};

/* DMA_WRITE_INT_CLEAR_OFF (Offset 09C8h) */
union _IoPplDwic {
	unsigned long		word;
	struct {
		unsigned long	wdic		:8;
		unsigned long				:8;
		unsigned long	waic		:8;
		unsigned long				:8;
	} bit;
};

/* DMA_WRITE_ERR_STATUS_OFF (Offset 09CCh) */
union _IoPplDwes {
	unsigned long		word;
	struct {
		unsigned long	ared			:8;
		unsigned long					:8;
		unsigned long	lefed		:8;
		unsigned long					:8;
	} bit;
};

/* DMA_WRITE_DONE_IMWR_LOW_OFF (Offset 09D0h) */
union _IoPplDwdil {
	unsigned long		word;
	struct {
		unsigned long	dwdlr		:32;
	} bit;
};

/* DMA_WRITE_DONE_IMWR_HIGH_OFF (Offset 09D4h) */
union _IoPplDwdih {
	unsigned long		word;
	struct {
		unsigned long	dwdhr		:32;
	} bit;
};

/* DMA_WRITE_ABORT_IMWR_LOW_OFF (Offset 09D8h) */
union _IoPplDwail {
	unsigned long		word;
	struct {
		unsigned long	dwalr		:32;
	} bit;
};

/* DMA_WRITE_ABORT_IMWR_HIGH_OFF (Offset 09DCh) */
union _IoPplDwaih {
	unsigned long		word;
	struct {
		unsigned long	dwahr		:32;
	} bit;
};

/* DMA_WRITE_CH01_IMWR_DATA_OFF (Offset 09E0h) */
union _IoPplDwc01id {
	unsigned long		word;
	struct {
		unsigned long	wc0d			:16;
		unsigned long	wc1d			:16;
	} bit;
};

/* DMA_WRITE_CH23_IMWR_DATA_OFF (Offset 09E4h) */
union _IoPplDwc23id {
	unsigned long		word;
	struct {
		unsigned long	wc2d			:16;
		unsigned long	wc3d			:16;
	} bit;
};

/* DMA_WRITE_CH45_IMWR_DATA_OFF (Offset 09E8h) */
union _IoPplDwc45id {
	unsigned long		word;
	struct {
		unsigned long	wc4d			:16;
		unsigned long	wc5d			:16;
	} bit;
};

/* DMA_WRITE_CH67_IMWR_DATA_OFF (Offset 09ECh) */
union _IoPplDwch67id {
	unsigned long		word;
	struct {
		unsigned long	wc6d			:16;
		unsigned long	wc7d			:16;
	} bit;
};

/* DMA_WRITE_LINKED_LIST_ERR_EN_OFF (Offset 0A00h) */
union _IoPplDwllee {
	unsigned long		word;
	struct {
		unsigned long	wclllaie	:2;
		unsigned long				:14;
		unsigned long	wcllraie	:2;
		unsigned long				:14;
	} bit;
};

/* DMA_READ_INT_STATUS_OFF (Offset 0A10h) */
union _IoPplDris {
	unsigned long		word;
	struct {
		unsigned long	rdis		:8;
		unsigned long				:8;
		unsigned long	rais		:8;
		unsigned long				:8;
	} bit;
};

/* DMA_READ_INT_MASK_OFF (Offset 0A18h) */
union _IoPplDrim {
	unsigned long		word;
	struct {
		unsigned long	rdim		:2;
		unsigned long				:14;
		unsigned long	raim		:2;
		unsigned long				:14;
	} bit;
};

/* DMA_READ_INT_CLEAR_OFF (Offset 0A1Ch) */
union _IoPplDric {
	unsigned long		word;
	struct {
		unsigned long	rdic		:8;
		unsigned long				:8;
		unsigned long	raic		:8;
		unsigned long				:8;
	} bit;
};

/* DMA_READ_ERR_STATUS_LOW_OFF (Offset 0A24h) */
union _IoPplDresl {
	unsigned long		word;
	struct {
		unsigned long	awed		:8;
		unsigned long					:8;
		unsigned long	llefed		:8;
		unsigned long					:8;
	} bit;
};

/* DMA_READ_ERR_STATUS_HIGH_OFF (Offset 0A28h) */
union _IoPplDresh {
	unsigned long		word;
	struct {
		unsigned long	ur			:8;
		unsigned long	ca			:8;
		unsigned long	ct			:8;
		unsigned long	dp			:8;
	} bit;
};

/* DMA_READ_LINKED_LIST_ERR_EN_OFF (Offset 0A34h) */
union _IoPplDrllee {
	unsigned long		word;
	struct {
		unsigned long	rclllaie		:2;
		unsigned long					:14;
		unsigned long	rcllraie		:2;
		unsigned long					:14;
	} bit;
};

/* DMA_READ_DONE_IMWR_LOW_OFF (Offset 0A3Ch) */
union _IoPplDrdil {
	unsigned long		word;
	struct {
		unsigned long	drdlr		:32;
	} bit;
};

/* DMA_READ_DONE_IMWR_HIGH_OFF (Offset 0A40h) */
union _IoPplDrdih {
	unsigned long		word;
	struct {
		unsigned long	drdhr		:32;
	} bit;
};

/* DMA_READ_ABORT_IMWR_LOW_OFF (Offset 0A44h) */
union _IoPplDrail {
	unsigned long		word;
	struct {
		unsigned long	dralr		:32;
	} bit;
};

/* DMA_READ_ABORT_IMWR_HIGH_OFF (Offset 0A48h) */
union _IoPplDraih {
	unsigned long		word;
	struct {
		unsigned long	drahr		:32;
	} bit;
};

/* DMA_READ_CH01_IMWR_DATA_OFF (Offset 0A4Ch) */
union _IoPplDrch01id {
	unsigned long		word;
	struct {
		unsigned long	rc0d			:16;
		unsigned long	rc1d			:16;
	} bit;
};

/* DMA_READ_CH23_IMWR_DATA_OFF (Offset 0A50h) */
union _IoPplDrch23id {
	unsigned long		word;
	struct {
		unsigned long	rc2d			:16;
		unsigned long	rc3d			:16;
	} bit;
};

/* DMA_READ_CH45_IMWR_DATA_OFF (Offset 0A54h) */
union _IoPplDrch45id {
	unsigned long		word;
	struct {
		unsigned long	rc4d			:16;
		unsigned long	rc5d			:16;
	} bit;
};

/* DMA_READ_CH67_IMWR_DATA_OFF (Offset 0A58h) */
union _IoPplDrch67id {
	unsigned long		word;
	struct {
		unsigned long	rc6d			:16;
		unsigned long	rc7d			:16;
	} bit;
};

/* DMA_VIEWPORT_SEL_OFF (Offset 0A6Ch) */
union _IoPplDvs {
	unsigned long		word;
	struct {
		unsigned long	cn			:3;
		unsigned long				:28;
		unsigned long	cd			:1;
	} bit;
};

/* DMA_CH_CONTROL1_OFF_WRCH_0 (Offset 0A70h) */
/* DMA_CH_CONTROL1_OFF_RDCH_0 (Offset 0A70h) */
union _IoPplDcc1 {
	unsigned long		word;
	struct {
		unsigned long	cb			:1;
		unsigned long	tcb			:1;
		unsigned long	llp			:1;
		unsigned long	lie			:1;
		unsigned long	rie			:1;
		unsigned long	cs				:2;
		unsigned long					:1;
		unsigned long	ccs			:1;
		unsigned long	lle			:1;
		unsigned long					:2;
		unsigned long	dfn			:5;
		unsigned long					:7;
		unsigned long	ns				:1;
		unsigned long	dro			:1;
		unsigned long	dtd			:1;
		unsigned long	dtc			:3;
		unsigned long	dat			:2;
	} bit;
};

/* DMA_TRANSFER_SIZE_OFF_WRCH_0 (Offset 0A78h) */
/* DMA_TRANSFER_SIZE_OFF_RDCH_0 (Offset 0A78h) */
union _IoPplDts {
	unsigned long		word;
	struct {
		unsigned long	dts			:32;
	} bit;
};

/* DMA_SAR_LOW_OFF_WRCH_0 (Offset 0A7Ch) */
/* DMA_SAR_LOW_OFF_RDCH_0 (Offset 0A7Ch) */
union _IoPplDsl {
	unsigned long		word;
	struct {
		unsigned long	sarl		:32;
	} bit;
};

/* DMA_SAR_HIGH_OFF_WRCH_0 (Offset 0A80h) */
/* DMA_SAR_HIGH_OFF_RDCH_0 (Offset 0A80h) */
union _IoPplDsh {
	unsigned long		word;
	struct {
		unsigned long	sarh		:32;
	} bit;
};

/* DMA_DAR_LOW_OFF_WRCH_0 (Offset 0A84h) */
/* DMA_DAR_LOW_OFF_RDCH_0 (Offset 0A84h) */
union _IoPplDdl {
	unsigned long		word;
	struct {
		unsigned long	darl		:32;
	} bit;
};

/* DMA_DAR_HIGH_OFF_WRCH_0 (Offset 0A88h) */
/* DMA_DAR_HIGH_OFF_RDCH_0 (Offset 0A88h) */
union _IoPplDdh {
	unsigned long		word;
	struct {
		unsigned long	darh		:32;
	} bit;
};

/* DMA_LLP_LOW_OFF_WRCH_0 (Offset 0A8Ch) */
/* DMA_LLP_LOW_OFF_RDCH_0 (Offset 0A8Ch) */
union _IoPplDll {
	unsigned long		word;
	struct {
		unsigned long	ll			:32;
	} bit;
};

/* DMA_LLP_HIGH_OFF_WRCH_0 (Offset 0A90h) */
/* DMA_LLP_HIGH_OFF_RDCH_0 (Offset 0A90h) */
union _IoPplDlh {
	unsigned long		word;
	struct {
		unsigned long	lh			:32;
	} bit;
};

/* PL_LTR_LATENCY_OFF (Offset 0B30h) */
union _IoPplPll {
	unsigned long		word;
	struct {
		unsigned long	slv			:10;
		unsigned long	sls			:3;
		unsigned long					:2;
		unsigned long	slr			:1;
		unsigned long	nslv			:10;
		unsigned long	nsls			:3;
		unsigned long					:2;
		unsigned long	nslr			:1;
	} bit;
};

/* AUX_CLK_FREQ_OFF (Offset 0B40h) */
union _IoPplAcf {
	unsigned long		word;
	struct {
		unsigned long	acf			:10;
		unsigned long					:22;
	} bit;
};

/* L1_SUBSTATES_OFF (Offset 0B44h) */
union _IoPplL1s {
	unsigned long		word;
	struct {
		unsigned long	l1tpo		:2;
		unsigned long	l1tl12		:4;
		unsigned long	l1tpa		:2;
		unsigned long					:24;
	} bit;
};

/* PF0_PORT_LOGIC */
struct _IoPpl {
	IoPplAlt				alt;							/* +0700 - 0703h */
	IoPplVsd				vsd;							/* +0704 - 0707h */
	IoPplPf				pf;								/* +0708 - 070Bh */
	IoPplAfac			afac;							/* +070C - 070Fh */
	IoPplPlc				plc;							/* +0710 - 0713h */
	IoPplLs				ls;								/* +0714 - 0717h */
	IoPplTcmfn			tcmfn;							/* +0718 - 071Bh */
	IoPplStf1				stf1;							/* +071C - 071Fh */
	IoPplFm2			fm2;							/* +0720 - 0723h */
	IoPplAmodnsrc	amodnsrc;						/* +0724 - 0727h */
	IoPplPd0				pd0;							/* +0728 - 072Bh */
	IoPplPd1				pd1;							/* +072C - 072Fh */
	IoPplTpfcs			tpfcs;							/* +0730 - 0733h */
	IoPplTnfcs			tnfcs;							/* +0734 - 0737h */
	IoPplTcfcs			tcfcs;							/* +0738 - 073Bh */
	IoPplQs				qs;								/* +073C - 073Fh */
	IoPplVta1			vta1;							/* +0740 - 0743h */
	IoPplVta2			vta2;							/* +0744 - 0747h */
	IoPplVprqc			vprqc;							/* +0748 - 074Bh */
	IoPplVnrqc			vnrqc;							/* +074C - 074Fh */
	IoPplVcrqc			vcrqc;							/* +0750 - 0753h */
	unsigned char			dmy0754080b[0x080C-0x0754];	/* +0754 - 080Bh */
	IoPplGen2c			gen2c;							/* +080C - 080Fh */
	IoPplPhys			phys;							/* +0810 - 0813h */
	IoPplPhyc			phyc;							/* +0814 - 0817h */
	unsigned char			dmy0818081f[0x0820-0x0818];	/* +0818 - 081Fh */
	IoPplMca				mca;							/* +0820 - 0823h */
	IoPplMcua			mcua;							/* +0824 - 0827h */
	IoPplMci0e			mci0e;							/* +0828 - 082Bh */
	IoPplMci0m		mci0m;							/* +082C - 082Fh */
	IoPplMci0s			mci0s;							/* +0830 - 0833h */
	unsigned char			dmy08340887[0x0888-0x0834];	/* +0834 - 0887h */
	IoPplMgi				mgi;							/* +0888 - 088Bh */
	unsigned char			dmy088c08b7[0x08B8-0x088C];	/* +088C - 08B7h */
	IoPplPilc				pilc;							/* +08B8 - 08BBh */
	IoPplMc1				mc1;							/* +08BC - 08BFh */
	IoPplMlc				mlc;							/* +08C0 - 08C3h */
	IoPplPhyic			phyic;							/* +08C4 - 08C7h */
	unsigned char			dmy08c808cb[0x08CC-0x08C8];	/* +08C8 - 08CBh */
	IoPplLfc				lfc;							/* +08CC - 08CFh */
	IoPplAerdr			aerdr;							/* +08D0 - 08D3h */
	IoPplAmlt			amlt;							/* +08D4 - 08D7h */
	IoPplAoc				aoc;							/* +08D8 - 08DBh */
	unsigned char			dmy08dc08df[0x08E0-0x08DC];	/* +08DC - 08DFh */
	IoPplCc1				cc1;							/* +08E0 - 08E3h */
	IoPplCc2				cc2;							/* +08E4 - 08E7h */
	IoPplCc3				cc3;							/* +08E8 - 08EBh */
	unsigned char			dmy08ec08ef[0x08F0-0x08EC];	/* +08EC - 08EFh */
	IoPplAmmal		ammal;							/* +08F0 - 08F3h */
	IoPplAmmah		ammah;							/* +08F4 - 08F7h */
	unsigned char			dmy08f808ff[0x0900-0x08F8];	/* +08F8 - 08FFh */
	IoPplIv					iv;								/* +0900 - 0903h */
	IoPplIrc1				irc1;							/* +0904 - 0907h */
	IoPplIrc2				irc2;							/* +0908 - 090Bh */
	IoPplIlba				ilba;							/* +090C - 090Fh */
	IoPplIuba			iuba;							/* +0910 - 0913h */
	IoPplIla				ila;							/* +0914 - 0917h */
	IoPplIlta				ilta;							/* +0918 - 091Bh */
	IoPplIuta				iuta;							/* +091C - 091Fh */
	unsigned char			dmy0920096f[0x0970-0x0920];	/* +0920 - 096Fh */
	IoPplDcdap			dcdap;							/* +0970 - 0973h */
	unsigned char			dmy09740977[0x0978-0x0974];	/* +0974 - 0977h */
	IoPplDc				dc;								/* +0978 - 097Bh */
	IoPplDwee			dwee;							/* +097C - 097Fh */
	IoPplDwd			dwd;							/* +0980 - 0983h */
	unsigned char			dmy09840987[0x0988-0x0984];	/* +0984 - 0987h */
	IoPplDwcawl		dwcawl;							/* +0988 - 098Bh */
	IoPplDwcawh		dwcawh;							/* +098C - 098Fh */
	unsigned char			dmy0990099b[0x099C-0x0990];	/* +0990 - 099Bh */
	IoPplDree			dree;							/* +099C - 099Fh */
	IoPplDrd				drd;							/* +09A0 - 09A3h */
	unsigned char			dmy09a409a7[0x09A8-0x09A4];	/* +09A4 - 09A7h */
	IoPplDrcawl		drcawl;							/* +09A8 - 09ABh */
	IoPplDrcawh		drcawh;							/* +09AC - 09AFh */
	unsigned char			dmy09b009bb[0x09BC-0x09B0];	/* +09B0 - 09BBh */
	IoPplDwis		dwis;							/* +09BC - 09BFh */
	unsigned char			dmy09c009c3[0x09C4-0x09C0];	/* +09C0 - 09C3h */
	IoPplDwim		dwim;							/* +09C4 - 09C7h */
	IoPplDwic		dwic;							/* +09C8 - 09CBh */
	IoPplDwes		dwes;							/* +09CC - 09CFh */
	IoPplDwdil		dwdil;							/* +09D0 - 09D3h */
	IoPplDwdih		dwdih;							/* +09D4 - 09D7h */
	IoPplDwail		dwail;							/* +09D8 - 09DBh */
	IoPplDwaih		dwaih;							/* +09DC - 09DFh */
	IoPplDwc01id	dwc01id;						/* +09E0 - 09E3h */
	IoPplDwc23id	dwc23id;						/* +09E4 - 09E7h */
	IoPplDwc45id	dwc45id;						/* +09E8 - 09EBh */
	IoPplDwch67id	dwch67id;						/* +09EC - 09EFh */
	unsigned char			dmy09f009ff[0x0A00-0x09F0];	/* +09F0 - 09FFh */
	IoPplDwllee		dwllee;							/* +0A00 - 0A03h */
	unsigned char			dmy0a040a0f[0x0A10-0x0A04];	/* +0A04 - 0A0Fh */
	IoPplDris		dris;							/* +0A10 - 0A13h */
	unsigned char			dmy0a140a17[0x0A18-0x0A14];	/* +0A14 - 0A17h */
	IoPplDrim		drim;							/* +0A18 - 0A1Bh */
	IoPplDric		dric;							/* +0A1C - 0A1Fh */
	unsigned char			dmy0a200a23[0x0A24-0x0A20];	/* +0A20 - 0A23h */
	IoPplDresl		dresl;							/* +0A24 - 0A27h */
	IoPplDresh		dresh;							/* +0A28 - 0A2Bh */
	unsigned char			dmy0a2c0a33[0x0A34-0x0A2C];	/* +0A2C - 0A33h */
	IoPplDrllee		drllee;							/* +0A34 - 0A37h */
	unsigned char			dmy0a380a3b[0x0A3C-0x0A38];	/* +0A38 - 0A3Bh */
	IoPplDrdil		drdil;							/* +0A3C - 0A3Fh */
	IoPplDrdih		drdih;							/* +0A40 - 0A43h */
	IoPplDrail		drail;							/* +0A44 - 0A47h */
	IoPplDraih		draih;							/* +0A48 - 0A4Bh */
	IoPplDrch01id	drch01id;						/* +0A4C - 0A4Fh */
	IoPplDrch23id	drch23id;						/* +0A50 - 0A53h */
	IoPplDrch45id	drch45id;						/* +0A54 - 0A57h */
	IoPplDrch67id	drch67id;						/* +0A58 - 0A5Bh */
	unsigned char			dmy0a5c0a6b[0x0A6C-0x0A5C];	/* +0A5C - 0A6Bh */
	IoPplDvs		dvs;							/* +0A6C - 0A6Fh */
	IoPplDcc1		dcc1;							/* +0A70 - 0A73h */
	unsigned char			dmy0a740a77[0x0A78-0x0A74];	/* +0A74 - 0A77h */
	IoPplDts		dts;							/* +0A78 - 0A7Bh */
	IoPplDsl		dsl;							/* +0A7C - 0A7Fh */
	IoPplDsh		dsh;							/* +0A80 - 0A83h */
	IoPplDdl		ddl;							/* +0A84 - 0A87h */
	IoPplDdh		ddh;							/* +0A88 - 0A8Bh */
	IoPplDll		dll;							/* +0A8C - 0A8Fh */
	IoPplDlh		dlh;							/* +0A90 - 0A93h */
	unsigned char			dmy0a940b2f[0x0B30-0x0A94];	/* +0A94 - 0B2Fh */
	IoPplPll		pll;							/* +0B30 - 0B33h */
	unsigned char			dmy0b340b3f[0x0B40-0x0B34];	/* +0B34 - 0B3Fh */
	IoPplAcf		acf;							/* +0B40 - 0B43h */
	IoPplL1s		l1s;							/* +0B44 - 0B47h */
};

/* core register of Root Complex */
struct _IoPcieCoreRc {
	IoT1csh			t1csh;							/* +0000 - 003Fh */
	IoPmcr			pmcr;							/* +0040 - 004Fh */
	IoMsicr			msicr;							/* +0050 - 0067h */
	unsigned char			dmy0068006f[0x0070-0x0068];	/* +0068 - 006Fh */
	IoPciecr		pciecr;							/* +0070 - 00AFh */
	unsigned char			dmy00b000af[0x0100-0x00B0];	/* +00B0 - 00FFh */
	IoAerc			aerc;							/* +0100 - 0147h */
	IoLtrc			ltrc;							/* +0148 - 014Fh */
	IoL1pmsec		l1pmsec;						/* +0150 - 015Fh */
	unsigned char			dmy016006ff[0x0700-0x0160];	/* +0160 - 06FFh */
	IoPpl			ppl;							/* +0700 - 0B47 */
};

/* core register of Endpoint */
struct _IoPcieCoreEp {
	IoT0csh			t0csh;							/* +0000 - 003Fh */
	IoPmcr			pmcr;							/* +0040 - 004Fh */
	IoMsicr			msicr;							/* +0050 - 0067h */
	unsigned char			dmy0068006f[0x0070-0x0068];	/* +0068 - 006Fh */
	IoPciecr		pciecr;							/* +0070 - 00AFh */
	unsigned char			dmy00b000af[0x0100-0x00B0];	/* +00B0 - 00FFh */
	IoAerc			aerc;							/* +0100 - 0147h */
	IoLtrc			ltrc;							/* +0148 - 014Fh */
	IoL1pmsec		l1pmsec;						/* +0150 - 015Fh */
	unsigned char			dmy016006ff[0x0700-0x0160];	/* +0160 - 06FFh */
	IoPpl			ppl;							/* +0700 - 0B47h */
};

/* CORE Register mapping */
union _ioPcieCore	{
	IoPcieCoreRc	rc;		/* Root Complex */
	IoPcieCoreEp	ep;		/* Endpoint     */
};

/*----------------------------------------------*/
/*	Macro Register								*/
/*----------------------------------------------*/
/* CORE_CONTROL (Offset 000h) */
union _IoPcieCoreControl {
	unsigned long		word;
	struct {
		unsigned long	deviceType			:4;
		unsigned long	appLtssmEnable	:1;
		unsigned long								:3;
		unsigned long	appReqRetryEn	:1;
		unsigned long								:7;
		unsigned long	rxLaneFlipEn		:1;
		unsigned long								:3;
		unsigned long	txLaneFlipEn		:1;
		unsigned long								:11;
	} bit;
};

/* AXI_CLK_STOP (Offset 004h) */
union _IoPcieAxiClkStop {
	unsigned long		word;
	struct {
		unsigned long	mstrAclkStop		:1;
		unsigned long	mstrCsysreqReg	:1;
		unsigned long	mstrCsysackReg	:1;
		unsigned long	mstrCactiveReg	:1;
		unsigned long	slvAclkStop			:1;
		unsigned long	slvCsysreqReg		:1;
		unsigned long	slvCsysackReg		:1;
		unsigned long	slvCactiveReg		:1;
		unsigned long	dbiAclkStop			:1;
		unsigned long	dbiCsysreqReg		:1;
		unsigned long	dbiCsysackReg		:1;
		unsigned long	dbiCactiveReg		:1;
		unsigned long						:20;
	} bit;
};

/* CLOCK_CONTROL (Offset 006h) */
union _IoPcieClockControl {
	unsigned long		word;
	struct {
		unsigned long	appClkReqN	:1;
		unsigned long							:7;
		unsigned long	extPclkReq		:1;
		unsigned long							:3;
		unsigned long	clkSwitchEn		:1;
		unsigned long							:19;
	} bit;
};

/* RESET_CONTROL_1 (Offset 00Ch) */
union _IoPcieResetControl1 {
	unsigned long		word;
	struct {
		unsigned long	pwupRstNReg		:1;
		unsigned long	buttonRstNReg	:1;
		unsigned long								:2;
		unsigned long	perstNIReg			:1;
		unsigned long	perstNOReg		:1;
		unsigned long								:2;
		unsigned long	pipeRstNReg		:1;
		unsigned long								:3;
		unsigned long	coreRstNReg		:1;
		unsigned long								:3;
		unsigned long	nStiRstNReg		:1;
		unsigned long								:3;
		unsigned long	stiRstNReg			:1;
		unsigned long								:3;
		unsigned long	pwrRstNReg		:1;
		unsigned long								:3;
		unsigned long	phyRstNReg		:1;
		unsigned long	squRstNReg		:1;
		unsigned long								:2;
	} bit;
};

/* RESET_CONTROL_2 (Offset 010h) */
union _IoPcieResetControl2 {
	unsigned long		word;
	struct {
		unsigned long	mstrArstNReg		:1;
		unsigned long								:3;
		unsigned long	slvArstNReg			:1;
		unsigned long								:3;
		unsigned long	dbiArstNReg		:1;
		unsigned long								:7;
		unsigned long	appInitRst			:1;
		unsigned long								:15;
	} bit;
};

/* RESET_SELECT_1 (Offset 014h) */
union _IoPcieResetSelect1 {
	unsigned long		word;
	struct {
		unsigned long	pwupRstSel			:1;
		unsigned long	buttonRstSel		:1;
		unsigned long								:2;
		unsigned long	perstSel				:1;
		unsigned long								:3;
		unsigned long	pipeRstSel			:1;
		unsigned long								:3;
		unsigned long	coreRstSel			:1;
		unsigned long								:3;
		unsigned long	nStiRstSel			:1;
		unsigned long								:3;
		unsigned long	stiRstSel				:1;
		unsigned long								:3;
		unsigned long	pwrRstSel			:1;
		unsigned long								:3;
		unsigned long	phyRstSel			:1;
		unsigned long	squRstSel			:1;
		unsigned long								:2;
	} bit;
};

/* RESET_SELECT_2 (Offset 018h) */
union _IoPcieResetSelect2 {
	unsigned long		word;
	struct {
		unsigned long	mstrArstSel		:1;
		unsigned long						:3;
		unsigned long	slvArstSel		:1;
		unsigned long						:3;
		unsigned long	dbiArstSel		:1;
		unsigned long						:23;
	} bit;
};

/* MSI_REQUEST_1 (Offset 01Ch) */
union _IoPcieMsiRequest1 {
	unsigned long		word;
	struct {
		unsigned long	localInterrupt		:32;
	} bit;
};

/* MSI_REQUEST_2 (Offset 020h) */
union _IoPcieMsiRequest2 {
	unsigned long		word;
	struct {
		unsigned long	msiFuncNum		:3;
		unsigned long								:1;
		unsigned long	msiTc					:3;
		unsigned long								:25;
	} bit;
};

/* INTERRUPT_CONTROL_1 (Offset 024h) */
union _IoPcieIntControl1 {
	unsigned long		word;
	struct {
		unsigned long	sysInt					:1;
		unsigned long								:15;
		unsigned long	intSyncbyp			:1;
		unsigned long								:11;
		unsigned long	intaStatus			:1;
		unsigned long	intbStatus			:1;
		unsigned long	intcStatus			:1;
		unsigned long	intdStatus			:1;
	} bit;
};

/* INTERRUPT_CONTROL_2 (Offset 028h) */
union _IoPcieIntControl2 {
	unsigned long		word;
	struct {
		unsigned long	sendCorErrEn		:1;
		unsigned long	sendCorErrCen	:1;
		unsigned long	sendCorErrStt		:1;
		unsigned long	sendCorErrM		:1;
		unsigned long	sendNfErrEn		:1;
		unsigned long	sendNfErrCen		:1;
		unsigned long	sendNfErrStt		:1;
		unsigned long	sendNfErrM		:1;
		unsigned long	sendFErrEn			:1;
		unsigned long	sendFErrCen		:1;
		unsigned long	sendFErrStt			:1;
		unsigned long	sendFErrM			:1;
		unsigned long	sysErrRcEn			:1;
		unsigned long	sysErrRcCen		:1;
		unsigned long	sysErrRcStt		:1;
		unsigned long	sysErrRcM		:1;
		unsigned long	rdlhLinkUpEn		:1;
		unsigned long	rdlhLinkUpCen	:1;
		unsigned long	rdlhLinkUpStt		:1;
		unsigned long	rdlhLinkUpM		:1;
		unsigned long	wakeEn				:1;
		unsigned long	wakeClearEn		:1;
		unsigned long	wakeStatus			:1;
		unsigned long	wakeMask			:1;
		unsigned long	vendorMsgEn		:1;
		unsigned long	vendorMsgCen		:1;
		unsigned long	vendorMsgStt		:1;
		unsigned long	vendorMsgM		:1;
		unsigned long	smlhReqRstEn		:1;
		unsigned long	smlhReqRstCen	:1;
		unsigned long	smlhReqRstStt	:1;
		unsigned long	smlhReqRstM		:1;
	} bit;
};

/* INTERRUPT_CONTROL_3 (Offset 02Ch) */
union _IoPcieIntControl3 {
	unsigned long		word;
	struct {
		unsigned long	radmPmPmeEn		:1;
		unsigned long	radmPmPmeCen		:1;
		unsigned long	radmPmPmeStt		:1;
		unsigned long	radmPmPmeM		:1;
		unsigned long	radmMsgUlEn		:1;
		unsigned long	radmMsgUlCen		:1;
		unsigned long	radmMsgUlStt		:1;
		unsigned long	radmMsgUlM		:1;
		unsigned long	radmCorErrEn		:1;
		unsigned long	radmCorErrCen	:1;
		unsigned long	radmCorErrStt	:1;
		unsigned long	radmCorErrM		:1;
		unsigned long	radmNfErrEn		:1;
		unsigned long	radmNfErrCen		:1;
		unsigned long	radmNfErrStt		:1;
		unsigned long	radmNfErrM		:1;
		unsigned long	radmFErrEn		:1;
		unsigned long	radmFErrCen		:1;
		unsigned long	radmFErrStt		:1;
		unsigned long	radmFErrM		:1;
		unsigned long	radmMsgLtrEn		:1;
		unsigned long	radmMsgLtrCen	:1;
		unsigned long	radmMsgLtrStt	:1;
		unsigned long	radmMsgLtrM		:1;
		unsigned long	radmPm2ackEn		:1;
		unsigned long	radmPm2ackCen		:1;
		unsigned long	radmPm2ackStt		:1;
		unsigned long	radmPm2ackM		:1;
		unsigned long	radmPmToffEn		:1;
		unsigned long	radmPmToffCen	:1;
		unsigned long	radmPmToffStt	:1;
		unsigned long	radmPmToffM		:1;
	} bit;
};

/* ELECTROMECHANICAL_CONTROL (Offset 030h) */
union _IoPcieEmControl {
	unsigned long		word;
	struct {
		unsigned long	attenBPressed		:1;
		unsigned long									:3;
		unsigned long	preDetSttReg			:1;
		unsigned long									:3;
		unsigned long	mrlSensorStt			:1;
		unsigned long									:3;
		unsigned long	pwrFaultDet			:1;
		unsigned long									:3;
		unsigned long	mrlSensorChged		:1;
		unsigned long									:3;
		unsigned long	preDetChged			:1;
		unsigned long									:3;
		unsigned long	cmdCpledInt			:1;
		unsigned long									:3;
		unsigned long	emlIlEngaged			:1;
		unsigned long									:3;
	} bit;
};

/* ELECTROMECHANICAL_SELECT (Offset 034h) */
union _IoPcieEmSelect {
	unsigned long		word;
	struct {
		unsigned long								:4;
		unsigned long	preDetSttSel		:1;
		unsigned long								:27;
	} bit;
};

/* ELECRTOMECHANICAL_MONITOR (Offset 038h) */
union _IoPcieEmMonitor {
	unsigned long		word;
	struct {
		unsigned long	cfgEmlControl		:1;
		unsigned long								:31;
	} bit;
};

/* PM_UNLOCK_MESSAGE_REQUEST (Offset 03Ch) */
union _IoPciePmUnlockReq {
	unsigned long		word;
	struct {
		unsigned long	appUnlockMsg			:1;
		unsigned long										:3;
		unsigned long	pmXmtTurnoff			:1;
		unsigned long										:11;
		unsigned long	ltrMsgReq					:1;
		unsigned long										:11;
		unsigned long	ltrMsgFuncNum			:3;
		unsigned long										:1;
	} bit;
};

/* APP_LTR_MSG (Offset 040h) */
union _IoPcieLtrMsg {
	unsigned long		word;
	struct {
		unsigned long	ltrMsgLatency		:32;
	} bit;
};

/* LTR_MONITOR_1 (Offset 044h) */
union _IoPcieLtrMonitor1 {
	unsigned long		word;
	struct {
		unsigned long	appLtrMsgGr		:1;
		unsigned long										:30;
		unsigned long	appLtrMsgRst		:1;
	} bit;
};

/* LTR_MONITOR_2 (Offset 048h) */
union _IoPcieLtrMonitor2 {
	unsigned long		word;
	struct {
		unsigned long	appLtrLatency		:32;
	} bit;
};

/* PM_CONTROL_1 (Offset 04Ch) */
union _IoPciePmControl1 {
	unsigned long		word;
	struct {
		unsigned long	wakeReg			:1;
		unsigned long						:15;
		unsigned long	clkreqReg			:1;
		unsigned long						:15;
	} bit;
};

/* PM_CONTROL_2 (Offset 050h) */
union _IoPciePmControl2 {
	unsigned long		word;
	struct {
		unsigned long	outbandPwupCmd		:1;
		unsigned long										:3;
		unsigned long	appsPmXmtPme			:1;
		unsigned long										:3;
		unsigned long	sysAuxPwrDet				:1;
		unsigned long										:3;
		unsigned long	appReqEntrL1				:1;
		unsigned long										:3;
		unsigned long	ppRdyEntrL23				:1;
		unsigned long										:3;
		unsigned long	appReqExitL1				:1;
		unsigned long										:3;
		unsigned long	ppClkPmEn					:1;
		unsigned long										:3;
		unsigned long	appXferPending			:1;
		unsigned long										:3;
	} bit;
};

/* PM_SELECT_1 (Offset 054h) */
union _IoPciePmSelect1 {
	unsigned long		word;
	struct {
		unsigned long	wakeSel			:1;
		unsigned long							:15;
		unsigned long	clkreqSel			:1;
		unsigned long							:15;
	} bit;
};

/* PM_MONITOR_1 (Offset 058h) */
union _IoPciePmMonitor1 {
	unsigned long		word;
	struct {
		unsigned long	pmCurntState		:3;
		unsigned long								:1;
		unsigned long	pmDstate			:3;
		unsigned long								:1;
		unsigned long	pmStatus				:1;
		unsigned long								:3;
		unsigned long	pmPmeEn			:1;
		unsigned long								:3;
		unsigned long	smlhLtssmState	:6;
		unsigned long								:2;
		unsigned long	auxPmEn				:1;
		unsigned long								:7;
	} bit;
};

/* PM_MONITOR_2 (Offset 05Ch) */
union _IoPciePmMonitor2 {
	unsigned long		word;
	struct {
		unsigned long	pmLinkstInL0s	:1;
		unsigned long								:3;
		unsigned long	pmLinkstInL1		:1;
		unsigned long								:3;
		unsigned long	pmLinkstInL2		:1;
		unsigned long								:3;
		unsigned long	pmLinkstL2E		:1;
		unsigned long								:3;
		unsigned long	pmLinkstInL1s	:1;
		unsigned long								:3;
		unsigned long	cfgL1subEn			:1;
		unsigned long								:7;
		unsigned long	clkreqMonitor		:1;
		unsigned long								:3;
	} bit;
};

/* PHY_CONFIG_COMMON_1 (Offset 100h) */
union _IoPcieConfigCom1 {
	unsigned long		word;
	struct {
		unsigned long	pipeTx2rxLpbk			:1;
		unsigned long	phyRx2txLbEn				:1;
		unsigned long										:2;
		unsigned long	pgModeEn					:1;
		unsigned long	pmaPwForEn				:1;
		unsigned long	pcsPwForEn				:1;
		unsigned long										:1;
		unsigned long	phyMpllaForEn			:1;
		unsigned long	phyMpllaSscEn			:1;
		unsigned long	phyMpllbForEn			:1;
		unsigned long	phyMpllbSscEn			:1;
		unsigned long	phyExtCtrlSel				:1;
		unsigned long	phyRtuneReq				:1;
		unsigned long										:2;
		unsigned long	pcsPsoSCnt					:8;
		unsigned long	pcsStableCnt				:8;
	} bit;
};

/* PHY_CONFIG_COMMON_2 (Offset 104h) */
union _IoPcieConfigCom2 {
	unsigned long		word;
	struct {
		unsigned long	phyMpllMul		:7;
		unsigned long								:1;
		unsigned long	phyRefClkdiv2		:1;
		unsigned long								:11;
		unsigned long	rx0SrisModeEn	:1;
		unsigned long								:11;
	} bit;
};

/* PHY_CONFIG_COMMON_3 (Offset 108h) */
union _IoPcieConfigCom3 {
	unsigned long		word;
	struct {
		unsigned long	txDeemG1				:6;
		unsigned long									:2;
		unsigned long	txDeemG23p5db	:6;
		unsigned long									:2;
		unsigned long	txDeemG26db		:6;
		unsigned long									:10;
	} bit;
};

/* PHY_CONFIG_COMMON_4 (Offset 10Ch) */
union _IoPcieConfigCom4 {
	unsigned long		word;
	struct {
		unsigned long	txSwingFull				:7;
		unsigned long									:1;
		unsigned long	txSwingLow				:7;
		unsigned long									:1;
		unsigned long	commonClocks		:1;
		unsigned long									:15;
	} bit;
};

/* PHY_CONFIG_COMMON_5 (Offset 110h) */
union _IoPcieConfigCom5 {
	unsigned long		word;
	struct {
		unsigned long	phyTx0TermOfs		:5;
		unsigned long									:3;
		unsigned long	phyTx1TermOfs		:5;
		unsigned long									:3;
		unsigned long	phyRx0Eq				:3;
		unsigned long									:5;
		unsigned long	phyRx1Eq				:3;
		unsigned long									:5;
	} bit;
};

/* PHY_CONFIG_COMMON_6 (Offset 114h) */
union _IoPcieConfigCom6 {
	unsigned long		word;
	struct {
		unsigned long	pipePortSel			:2;
		unsigned long								:2;
		unsigned long	phyTxVboostLv	:3;
		unsigned long								:9;
		unsigned long	phyLosLevel		:5;
		unsigned long								:3;
		unsigned long	phyLosBias			:3;
		unsigned long								:5;
	} bit;
};

/* CFG_MONITOR_1 (Offset 1D8h) */
union _IoPcieCfgMonitor1 {
	unsigned long		word;
	struct {
		unsigned long	cfgBusMstrEn		:1;
		unsigned long								:3;
		unsigned long	cfgMemSpaceEn	:1;
		unsigned long								:3;
		unsigned long	cfgMaxRdSize		:3;
		unsigned long								:1;
		unsigned long	cfgMaxPlSize		:3;
		unsigned long								:1;
		unsigned long	cfgRcb					:1;
		unsigned long								:1;
		unsigned long	cfgPwrCtrlerc		:1;
		unsigned long								:1;
		unsigned long	cfgPmNoSrst		:1;
		unsigned long								:3;
		unsigned long	cfgPwrInd			:2;
		unsigned long								:2;
		unsigned long	cfgAttenInd			:2;
		unsigned long								:2;
	} bit;
};

/* CFG_MONITOR_2 (Offset 1DCh) */
union _IoPcieCfgMonitor2 {
	unsigned long		word;
	struct {
		unsigned long	cfgPhyControl		:32;
	} bit;
};

/* CFG_MONITOR_3 (Offset 1E0h) */
union _IoPcieCfgMonitor3 {
	unsigned long		word;
	struct {
		unsigned long	cfgPbusNum			:8;
		unsigned long	cfgPbusDevNum	:5;
		unsigned long									:3;
		unsigned long	cfg2ndbusNum		:8;
		unsigned long	cfgSubbusNum		:8;
	} bit;
};

/* CFG_MONITOR_4 (Offset 1E4h) */
union _IoPcieCfgMonitor4 {
	unsigned long		word;
	struct {
		unsigned long	cfgLtrMaxLat		:32;
	} bit;
};

/* CFG_MONITOR_5 (Offset 1E8h) */
union _IoPcieCfgMonitor5 {
	unsigned long		word;
	struct {
		unsigned long	cfgLtrMEn				:1;
		unsigned long									:3;
		unsigned long	cfgNoSnoopEn		:1;
		unsigned long									:3;
		unsigned long	cfgRelaxOrder			:1;
		unsigned long									:7;
		unsigned long	cfg2ndReset			:1;
		unsigned long									:15;
	} bit;
};

/* DEBUG_MONITOR_1 (Offset 1ECh) */
union _IoPcieDebugMonitor1 {
	unsigned long		word;
	struct {
		unsigned long										:4;
		unsigned long	rtlhRfcUpd					:1;
		unsigned long										:3;
		unsigned long	brdgSlvXferPe				:1;
		unsigned long										:3;
		unsigned long	brdgDbiXferPe			:1;
		unsigned long										:3;
		unsigned long	edmaXferPe				:1;
		unsigned long										:3;
		unsigned long	radmXferPe					:1;
		unsigned long										:3;
		unsigned long	radmQNotEmpty		:1;
		unsigned long										:3;
		unsigned long	radmQoverflow			:1;
		unsigned long										:3;
	} bit;
};

/* DEBUG_MONITOR_2 (Offset 1F0h) */
union _IoPcieDebugMonitor2 {
	unsigned long		word;
	struct {
		unsigned long	rtlhRfcData		:32;
	} bit;
};

/* DEBUG_MONITOR_3 (Offset 1F4h) */
union _IoPcieDebugMonitor3 {
	unsigned long		word;
	struct {
		unsigned long	cxplDInfoEi		:16;
		unsigned long							:16;
	} bit;
};

/* DEBUG_MONITOR_4 (Offset 1F8h) */
struct _IoPcieDebugMonitor4 {
	unsigned long		cxplDInfoL;				/* 1F8 - 1FBh */
	unsigned long		cxplDInfoU;				/* 1FC - 1FFh */
};

/* MSG_MONITOR_1 (Offset 200h) */
union _IoPcieMsgMonitor1 {
	unsigned long		word;
	struct {
		unsigned long									:16;
		unsigned long	radmMsgReqId		:16;
	} bit;
};

/* MSG_MONITOR_3 (Offset 208h) */
struct _IoPcieMsgMonitor3 {
	unsigned long		radmMsgPayloadL;			/* 208 - 20Bh */
	unsigned long		radmMsgPayloadU;			/* 20C - 20Fh */
};

/* LINK_MONITOR (Offset 210h) */
union _IoPcieLinkMonitor {
	unsigned long		word;
	struct {
		unsigned long	smlhLinkUp			:1;
		unsigned long								:3;
		unsigned long	smlhReq_rstNot	:1;
		unsigned long								:27;
	} bit;
};

/* TIMEOUT_MONITOR_1 (Offset 218h) */
union _IoPcieToMonitor1 {
	unsigned long		word;
	struct {
		unsigned long	radmToFuncNu		:3;
		unsigned long									:1;
		unsigned long	radmToCplTc			:3;
		unsigned long									:1;
		unsigned long	radmToCplTag		:8;
		unsigned long	radmRoCplAttr		:2;
		unsigned long									:2;
		unsigned long	radmToCplLen		:12;
	} bit;
};

/* TIMEOUT_MONITOR_2 (Offset 21Ch) */
union _IoPcieToMonitor2 {
	unsigned long		word;
	struct {
		unsigned long	radmCplTimeout	:1;
		unsigned long									:31;
	} bit;
};

/* TIMEOUT_MONITOR_3 (Offset 220h) */
union _IoPcieToMonitor3 {
	unsigned long		word;
	struct {
		unsigned long	trgtToCplFnum	:3;
		unsigned long								:1;
		unsigned long	trgtToCplTc			:3;
		unsigned long								:1;
		unsigned long	trgtToLkupId		:8;
		unsigned long	trgtToCplAttr		:2;
		unsigned long								:2;
		unsigned long	trgtToCplLen		:12;
	} bit;
};

/* TIMEOUT_MONITOR_4 (Offset 224h) */
union _IoPcieToMonitor4 {
	unsigned long		word;
	struct {
		unsigned long	trgtCplTimeout	:1;
		unsigned long						:3;
		unsigned long	trgtLkupEmpty		:1;
		unsigned long						:3;
		unsigned long	trgtLkupId		:8;
		unsigned long						:16;
	} bit;
};

/* TRANSMIT_MONITOR (Offset 228h) */
union _IoPcieTransmitMonitor {
	unsigned long		word;
	struct {
		unsigned long	pmXtlhBlkTlp		:1;
		unsigned long						:31;
	} bit;
};

/* PIPE_MONITOR (Offset 22Ch) */
union _IoPciePipeMonitor {
	unsigned long		word;
	struct {
		unsigned long	cfgHwAutoSpD	:1;
		unsigned long						:3;
		unsigned long	macPhyRate		:1;
		unsigned long						:27;
	} bit;
};

/* PHY_MONITOR (Offset 230h) */
union _IoPciePhyMonitor {
	unsigned long		word;
	struct {
		unsigned long								:1;
		unsigned long	phy0MpllaState	:1;
		unsigned long	phy0MpllbState	:1;
		unsigned long								:7;
		unsigned long	phyRtuneAck		:1;
		unsigned long								:5;
		unsigned long	pipeRxEbufLoc	:9;
		unsigned long								:7;
	} bit;
};

/* CONFIG_MONITOR_BAR0_START (Offset 238h) */
struct _IoPcieMonitorBar0S {
	unsigned long		cfgBar0StartL;			/* 238 - 23Bh */
	unsigned long		cfgBar0StartU;			/* 23C - 23Fh */
};

/* CONFIG_MONITOR_BAR0_LIMIT (Offset 240h) */
struct _IoPcieMonitorBar0L {
	unsigned long		cfgBar0LimitL;			/* 240 - 243h */
	unsigned long		cfgBar0LimitU;			/* 244 - 247h */
};

/* CONFIG_MONITOR_BAR1_START (Offset 248h) */
union _IoPcieMonitorBar1S {
	unsigned long		word;
	struct {
		unsigned long	cfgBar1Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR1_LIMIT (Offset 24Ch) */
union _IoPcieMonitorBar1L {
	unsigned long		word;
	struct {
		unsigned long	cfgBar1Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR2_START (Offset 250h) */
struct _IoPcieMonitorBar2S {
	unsigned long		cfgBar2StartL;			/* 250 - 253h */
	unsigned long		cfgBar2StartU;			/* 254 - 257h */
};

/* CONFIG_MONITOR_BAR2_LIMIT (Offset 258h) */
struct _IoPcieMonitorBar2L {
	unsigned long		cfgBar2LimitL;			/* 258 - 25Bh */
	unsigned long		cfgBar2LimitU;			/* 25C - 25Fh */
};

/* CONFIG_MONITOR_BAR3_START (Offset 260h) */
union _IoPcieMonitorBar3S {
	unsigned long		word;
	struct {
		unsigned long	cfgBar3Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR3_LIMIT (Offset 264h) */
union _IoPcieMonitorBar3L {
	unsigned long		word;
	struct {
		unsigned long	cfgBar3Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR4_START (Offset 268h) */
struct _IoPcieMonitorBar4S {
	unsigned long		cfgBar4StartL;			/* 258 - 25Bh */
	unsigned long		cfgBar4StartU;			/* 25C - 25Fh */
};

/* CONFIG_MONITOR_BAR4_LIMIT (Offset 270h) */
struct _IoPcieMonitorBar4L {
	unsigned long		cfgBar4LimitL;			/* 250 - 253h */
	unsigned long		cfgBar4LimitU;			/* 254 - 257h */
};

/* CONFIG_MONITOR_BAR5_START (Offset 278h) */
union _IoPcieMonitorBar5S {
	unsigned long		word;
	struct {
		unsigned long	cfgBar5Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR5_LIMIT (Offset 27Ch) */
union _IoPcieMonitorBar5L {
	unsigned long		word;
	struct {
		unsigned long	cfgBar5Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_EXP_ROM_START (Offset 280h) */
union _IoPcieMonitorEromS {
	unsigned long		word;
	struct {
		unsigned long	cfgEromStart		:32;
	} bit;
};

/* CONFIG_MONITOR_EEXP_ROM_LIMIT (Offset 284h) */
union _IoPcieMonitorEromL {
	unsigned long		word;
	struct {
		unsigned long	cfgEromLimit		:32;
	} bit;
};

/* MACRO REGISTER (Offset 000h - FFFh) */
struct _IoPcie {
	IoPcieCoreControl		coreControl;				/* +000 - 003h */
	IoPcieAxiClkStop		axiClkStop;				/* +004 - 007h */
	IoPcieClockControl		clockControl;				/* +008 - 00Bh */
	IoPcieResetControl1	resetControl1;			/* +00C - 00Fh */
	IoPcieResetControl2	resetControl2;			/* +010 - 013h */
	IoPcieResetSelect1		resetSelect1;				/* +014 - 017h */
	IoPcieResetSelect2		resetSelect2;				/* +018 - 01Bh */
	IoPcieMsiRequest1		msiRequest1;				/* +01C - 01Fh */
	IoPcieMsiRequest2		msiRequest2;				/* +020 - 023h */
	IoPcieIntControl1		intControl1;				/* +024 - 027h */
	IoPcieIntControl2		intControl2;				/* +028 - 02Bh */
	IoPcieIntControl3		intControl3;				/* +02C - 02Fh */
	IoPcieEmControl		emControl;					/* +030 - 033h */
	IoPcieEmSelect			emSelect;					/* +034 - 037h */
	IoPcieEmMonitor		emMonitor;					/* +038 - 03Bh */
	IoPciePmUnlockReq	pmUnlockReq;				/* +03C - 03Fh */
	IoPcieLtrMsg				ltrMsg;					/* +040 - 043h */
	IoPcieLtrMonitor1		ltrMonitor1;				/* +044 - 047h */
	IoPcieLtrMonitor2		ltrMonitor2;				/* +048 - 04Bh */
	IoPciePmControl1		pmControl1;				/* +04C - 04Fh */
	IoPciePmControl2		pmControl2;				/* +050 - 053h */
	IoPciePmSelect1		pmSelect1;				/* +054 - 057h */
	IoPciePmMonitor1		pmMonitor1;				/* +058 - 05Bh */
	IoPciePmMonitor2		pmMonitor2;				/* +05C - 05Fh */
	unsigned char			dmy0600ff[0x100-0x060];	/* +060 - 0FFh */
	IoPcieConfigCom1		phyConfigCom1;			/* +100 - 103h */
	IoPcieConfigCom2		phyConfigCom2;			/* +104 - 107h */
	IoPcieConfigCom3		phyConfigCom3;			/* +108 - 10Bh */
	IoPcieConfigCom4		phyConfigCom4;			/* +10C - 10Fh */
	IoPcieConfigCom5		phyConfigCom5;			/* +110 - 113h */
	IoPcieConfigCom6		phyConfigCom6;			/* +114 - 117h */
	unsigned char			dmy1181d7[0x1D8-0x118];	/* +118 - 1D7h */
	IoPcieCfgMonitor1		cfgMonitor1;				/* +1D8 - 1DBh */
	IoPcieCfgMonitor2		cfgMonitor2;				/* +1DC - 1DFh */
	IoPcieCfgMonitor3		cfgMonitor3;				/* +1E0 - 1E3h */
	IoPcieCfgMonitor4		cfgMonitor4;				/* +1E4 - 1E7h */
	IoPcieCfgMonitor5		cfgMonitor5;				/* +1E8 - 1EBh */
	IoPcieDebugMonitor1	debugMonitor1;			/* +1EC - 1EFh */
	IoPcieDebugMonitor2	debugMonitor2;			/* +1F0 - 1F3h */
	IoPcieDebugMonitor3	debugMonitor3;			/* +1F4 - 1F7h */
	IoPcieDebugMonitor4	debugMonitor4;			/* +1F8 - 1FFh */
	IoPcieMsgMonitor1		msgMonitor1;				/* +200 - 203h */
	unsigned char				dmy204207[0x208-0x204];	/* +204 - 207h */
	IoPcieMsgMonitor3		msgMonitor3;				/* +208 - 20Fh */
	IoPcieLinkMonitor			linkMonitor;				/* +210 - 213h */
	unsigned char				dmy214217[0x218-0x214];	/* +214 - 217h */
	IoPcieToMonitor1			toMonitor1;				/* +218 - 21Bh */
	IoPcieToMonitor2		toMonitor2;				/* +21C - 21Fh */
	IoPcieToMonitor3		toMonitor3;				/* +220 - 223h */
	IoPcieToMonitor4		toMonitor4;				/* +224 - 227h */
	IoPcieTransmitMonitor	transmitMonitor;			/* +228 - 22Bh */
	IoPciePipeMonitor		pipeMonitor;				/* +22C - 22Fh */
	IoPciePhyMonitor		phyMonitor;				/* +230 - 233h */
	unsigned char					dmy234237[0x238-0x234];	/* +234 - 237h */
	IoPcieMonitorBar0S	monitorBar0S;				/* +238 - 23Fh */
    IoPcieMonitorBar0L	monitorBar0L;				/* +240 - 247h */
	IoPcieMonitorBar1S	monitorBar1S;				/* +248 - 24Bh */
	IoPcieMonitorBar1L	monitorBar1L;				/* +24C - 249h */
	IoPcieMonitorBar2S	monitorBar2S;				/* +250 - 257h */
	IoPcieMonitorBar2L	monitorBar2L;				/* +258 - 25Fh */
	IoPcieMonitorBar3S	monitorBar3S;				/* +260 - 263h */
	IoPcieMonitorBar3L	monitorBar3L;				/* +264 - 267h */
	IoPcieMonitorBar4S	monitorBar4S;				/* +268 - 26Fh */
	IoPcieMonitorBar4L	monitorBar4L;				/* +270 - 277h */
	IoPcieMonitorBar5S	monitorBar5S;				/* +278 - 27Bh */
	IoPcieMonitorBar5L	monitorBar5L;				/* +27C - 27Fh */
	IoPcieMonitorEromS	monitorEromS;				/* +280 - 283h */
	IoPcieMonitorEromL	monitorEromL;				/* +284 - 287h */
};

struct _SnsPcie
{
	KObject parent;
};



extern volatile IoPcieCore	ioPcie0Core;				/* 1915_(0000 - FFFFh) */
extern volatile IoPcieCore	ioPcie1Core;				/* 1916_(0000 - FFFFh) */
extern volatile IoPcie			ioPcie0;					/* 1B11_1(000 - FFFh) */
extern volatile IoPcie			ioPcie1;					/* 1B11_2(000 - FFFh) */


KConstType sns_pcie_get_type(void);
SnsPcie* 		sns_pcie_new(void);
SnsPcie* 		sns_pcie_get(void);


#endif /* __SNS_PCIE_H__ */
