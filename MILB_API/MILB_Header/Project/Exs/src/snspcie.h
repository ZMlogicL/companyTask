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
	kulong		word;
	struct {
		kulong	vid				:16;
		kulong	did				:16;
	} bit;
};

/* Status Command (Offset 0004h) */
union _IoStatusCommand {
	kulong		word;
	struct {
		kulong	ios				:1;
		kulong	ms				:1;
		kulong	bme				:1;
		kulong						:3;
		kulong	per				:1;
		kulong						:1;
		kulong	serre			:1;
		kulong						:1;
		kulong	id					:1;
		kulong						:8;
		kulong	is					:1;
		kulong	cl					:1;
		kulong						:3;
		kulong	mdpe			:1;
		kulong						:2;
		kulong	sta				:1;
		kulong	rta				:1;
		kulong	rma				:1;
		kulong	sse				:1;
		kulong	dpe				:1;
	} bit;
};

/* Class Code and Revision ID (Offset 0008h) */
union _IoClassCodeRevId {
	kulong		word;
	struct {
		kulong	rid 				:8;
		kulong	pi					:8;
		kulong	scc				:8;
		kulong	bcc				:8;
	} bit;
};

/* Header Type and Cache Line Size (Offset 000Ch) */
union _IoHdrTypeCacheLineSize {
	kulong		word;
	struct {
		kulong	cls 				:8;
		kulong						:8;
		kulong	ht 				:7;
		kulong	mfs				:1;
		kulong						:8;
	} bit;
};

/* Primary, Secondary, Subordinate Bus Numbers and Latency Timer (Offset 0018h) */
union _IoSecLatTimerSubBusSecBusPriBus {
	kulong		word;
	struct {
		kulong	pbn 				:8;
		kulong	subbn			:8;
		kulong	secbn			:8;
		kulong	slt					:8;
	} bit;
};

/* Secondary Status and IO Limit and IO Base (Offset 001Ch) <RC> */
union _IoSecStatIoLimitIoBase {
	kulong		word;
	struct {
		kulong	iobaIoa 	:1;
		kulong		 			:3;
		kulong	ioba			:4;
		kulong	iolIoa 		:1;
		kulong		 			:3;
		kulong	iol			:4;
		kulong					:8;
		kulong	mdpe		:1;
		kulong					:2;
		kulong	sta			:1;
		kulong	rta			:1;
		kulong	rma			:1;
		kulong	rse			:1;
		kulong	dpe			:1;
	} bit;
};

/* Memory Limit and Memory Base (Offset 0020h) <RC> */
union _IoMemLimitMemBase {
	kulong		word;
	struct {
		kulong						:4;
		kulong	mba				:12;
		kulong						:4;
		kulong	ml				:12;
	} bit;
};


/* Prefetchable Memory Limit and Prefetchable Memory Base Address (Offset 0024h) <RC> */
union _IoPrefMemLimitPrefMemBase {
	kulong		word;
	struct {
		kulong	pmd				:1;
		kulong						:3;
		kulong	pmba			:12;
		kulong	pmld			:1;
		kulong						:3;
		kulong	pml				:12;
	} bit;
};

/* Prefetchable Base Upper (Offset 0028h) <RC> */
union _IoPrefBaseUpper {
	kulong		word;
	struct {
		kulong	pbau32			:32;
	} bit;
};

/* Prefetchable Limit Upper (Offset 002Ch) <RC> */
union _IoPrefLimitUpper {
	kulong		word;
	struct {
		kulong	pmlu32			:32;
	} bit;
};

/* IO Limit Upper and IO Base Upper (Offset 0030h) <RC> */
union _IoIoLimitUpperIoBaseUpper {
	kulong		word;
	struct {
		kulong	iobau16			:16;
		kulong	iolu16				:16;
	} bit;
};

/* Capabilities Pointer (Offset 0034h) */
union _IoCapPtr {
	kulong		word;
	struct {
		kulong	ncp				:8;		/* New Capabilities Pointer */
		kulong						:24;
	} bit;
};

/* Expansion ROM Base Address (RC:Offset 0038h, EP: Offset 0030h) */
union _IoExpRomBar {
	kulong		word;
	struct {
		kulong	erome			:1;
		kulong						:10;
		kulong	ba				:21;
	} bit;
};

/* Bridge Control Interrupt Pin and Interrupt Line (Offset 003Ch) <RC> */
union _IoBridgeCtrlIntPinIntLine {
	kulong		word;
	struct {
		kulong	il	 				:8;
		kulong	ip					:8;
		kulong	per				:1;
		kulong	serre			:1;
		kulong	isae				:1;
		kulong	vgae				:1;
		kulong	vga16d		:1;
		kulong						:1;
		kulong	sbr				:1;
		kulong						:9;
	} bit;
};

/* Type1 Configuration Space Header */
struct _IoT1csh {
	IoDevIdVendId										devIdVendId;										/* +0000 - 0003h */
	IoStatusCommand									statusCommand;								/* +0004 - 0007h */
	IoClassCodeRevId									classCodeRevId;									/* +0008 - 000Bh */
	IoHdrTypeCacheLineSize						hdrTypeCacheLineSize;						/* +000C - 000Fh */
	kuchar														dmy00100017[0x0018-0x0010];			/* +0010 - 0017h */
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
	kulong		word;
	struct		{
		kulong	miosi			:1;
		kulong	mt				:2;
		kulong	pf					:1;
		kulong	ba				:28;
	} bit;
};

/* CardBus CIS Pointer (Offset 0028h) <EP> */
union _IoCardbusCisPtr {
	kulong		word;
	struct {
		kulong	ccp	 			:32;
	} bit;
};

/* Subsystem ID and Subsystem Vendor ID (Offset 002Ch) <EP> */
union _IoSubsysIdSubsysVId {
	kulong		word;
	struct {
		kulong	svid	 			:16;
		kulong	sid	 			:16;
	} bit;
};

/* Interrupt Pin and Interrupt Line (Offset 003Ch) <EP> */
union _IoIntPinIntLine {
	kulong		word;
	struct {
		kulong	il	 			:8;
		kulong	ip				:8;
		kulong					:16;
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
	kuchar										dmy0038003b[0x003C-0x0038];	/* +0038 - 003Bh */
	IoIntPinIntLine						intPinIntLine;					/* +003C - 003Fh */
};

/* Power Management Capabilities (Offset 0040h) */
union _IoPmcrPmc {
	kulong		word;
	struct {
		kulong	cid				: 8;
		kulong	ncp				: 8;
		kulong	ver				: 3;
		kulong						: 1;
		kulong						: 1;
		kulong	dsi				: 1;
		kulong	ac					: 3;
		kulong	d1s				: 1;
		kulong	d2s				: 1;
		kulong	pmes			: 5;
	} bit;
};

/* Power Management Control / Status (Offset 0044h) */
union _IoPmcrPmcs {
	kulong		word;
	struct {
		kulong	ps				:2;
		kulong					:1;
		kulong	nsr			:1;
		kulong					:4;
		kulong	pmeen		:1;
		kulong	dsel			:4;
		kulong	ds				:2;
		kulong	pmes		:1;
		kulong					:6;
		kulong	b2b3s		:1;
		kulong	bpcce		:1;
		kulong	data			:8;
	} bit;
};

/* Power Management Capabilities Register */
struct _IoPmcr {
	IoPmcrPmc			pmc;							/* +0040 - 0043h */
	IoPmcrPmcs		pmcs;							/* +0044 - 0047h */
	kuchar					dmy0048004f[0x0050-0x0048];	/* +0048 - 004Fh */
};

/* MSI Cap ID / Next Item / Message Control (Offset 050h) */
union _IoMsicrMcinc {
	kulong		word;
	struct		{
		kulong	cid				:8;
		kulong	np				:8;
		kulong	msie			:1;
		kulong	mmc			:3;
		kulong	mme			:3;
		kulong	ac64				:1;
		kulong	pvmc			:1;
		kulong						:7;
	} bit;
};

/* Message Address (Offset 054h) */
union _IoMsicrMla {
	kulong		word;
	struct	{
		kulong						:2;
		kulong	mla				:30;
	} bit;
};

/* Message Upper Address (Offset 058h) */
union _IoMsicrMua {
	kulong		word;
	struct		{
		kulong	mua				:32;
	} bit;
};

/* Message Data (Offset 05Ch) */
union	_IoMsicrMd	{
	kulong		word;
	struct		{
		kulong	md				:16;
		kulong						:16;
	} bit;
};

/* Mask Bits (Offset 060h) */
union _IoMsicrMmb {
	kulong		word;
	struct		{
		kulong	mmb			:32;
	} bit;
};

/* Pending Bits (Offset 064h) */
union _IoMsicrMpb {
	kulong		word;
	struct		{
		kulong	mpb				:32;
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
	kulong		word;
	struct {
		kulong	cid				:8;
		kulong	np				:8;

		kulong	cv					:4;
		kulong	dpt				:4;
		kulong	si					:1;
		kulong	imn				:5;
		kulong						:2;
	} bit;
};

/* Device Capability Register (Offset 0074h) */
union _IoPciecrDcr {
	kulong		word;
	struct {
		kulong	mpss			:3;
		kulong	pfs				:2;
		kulong	etfs				:1;
		kulong	el0al			:3; // EP only
		kulong	el1al			:3; // EP only
		kulong						:3;
		kulong	rber				:1;
		kulong						:2;
		kulong	csplv			:8; // EP only
		kulong	cspls			:2; // EP only
		kulong	flrc				:1; // EP only
		kulong						:3;
	} bit;
};

/* Device Control Register (Offset 0078h)  */
/* Device Status Register (Offset 007Ah)  */
union _IoPciecrDcsr {
	kulong		word;
	struct {
		kulong	cere			:1;
		kulong	nfere		:1;
		kulong	fere			:1;
		kulong	urre			:1;
		kulong	ero			:1;
		kulong	mps			:3;
		kulong	etfe			:1;
		kulong	pfe			:1;
		kulong	appme		:1;
		kulong	ens			:1;
		kulong	mrrs			:3;
		kulong	iflr			:1;

		kulong	ced			:1;
		kulong	nfed			:1;
		kulong	fed			:1;
		kulong	urd			:1;
		kulong	auxpd		:1;
		kulong	tp				:1;
		kulong					:10;
	} bit;
};

/* Link Capability Register (Offset 007Ch)  */
union _IoPciecrLcr {
	kulong		word;
	struct {
		kulong	mls				:4;
		kulong	mlw				:6;
		kulong	aspms			:2;
		kulong	l0el				:3;
		kulong	l1el				:3;
		kulong	cpm				:1;
		kulong	sderc			:1;
		kulong	dlllarc			:1;
		kulong	lbnc				:1;
		kulong	aspmoc		:1;
		kulong						:1;
		kulong	pn				:8;
	} bit;
};

/* Link Control Register (Offset 0080h) */
/* Link Status Register (Offset 0082h) */
union _IoPciecrLcsr {
	kulong		word;
	struct {
		kulong	aspmc		:2;
		kulong					:1;
		kulong	rcb			:1;
		kulong	ld				:1;
		kulong	rl				:1;
		kulong	ccc			:1;
		kulong	es				:1;
		kulong	ecpm		:1;
		kulong	hawd		:1;
		kulong	lbmie		:1;
		kulong	labie		:1;
		kulong					:2;
		kulong	drssc		:2;

		kulong	cls			:4;
		kulong	nlw			:6;
		kulong					:1;
		kulong	lt				:1;
		kulong	scc			:1;
		kulong	dllla			:1;
		kulong	lbms		:1;
		kulong	labs			:1;
	} bit;
};

/* Slot Capabilities Register (Offset 0084h) <RC> */
union _IoPciecrScr {
	kulong		word;
	struct {
		kulong	abp				:1;
		kulong	pcp				:1;
		kulong	mrlsp			:1;
		kulong	aip				:1;
		kulong	pip				:1;
		kulong	hps				:1;
		kulong	hpc				:1;
		kulong	splv				:8;
		kulong	spls				:2;
		kulong	eip				:1;
		kulong	nccs				:1;
		kulong	psn				:13;
	} bit;
};

/* Slot Control Register (Offset 0088h) <RC> */
/* Slot Status Register (Offset 008Ah) <RC> */
union _IoPciecrScsr {
	kulong		word;
	struct {
		kulong	abpe			:1;
		kulong	pfde				:1;
		kulong	mrlsce			:1;
		kulong	pdce			:1;
		kulong	ccie				:1;
		kulong	hpie				:1;
		kulong	aic				:2;
		kulong	pic				:2;
		kulong	pcc				:1;
		kulong	eic				:1;
		kulong	dllsce			:1;
		kulong						:3;

		kulong	abp				:1;
		kulong	pfd				:1;
		kulong	mrlsc			:1;
		kulong	pdc				:1;
		kulong	cc					:1;
		kulong	mrlss			:1;
		kulong	pds				:1;
		kulong	eis				:1;
		kulong	dllsc				:1;
		kulong						:7;
	} bit;
};

/* Root Control Register (Offset 008Ch) <RC> */
/* Root Capability Register (Offset 008Eh) <RC> */
union _IoPciecrRccr {
	kulong		word;
	struct {
		kulong	secee			:1;
		kulong	senfee			:1;
		kulong	sefee			:1;
		kulong	pmeie			:1;
		kulong	crssve			:1;
		kulong						:11;

		kulong	crssv			:1;
		kulong						:15;
	} bit;
};

/* Root Status Register (Offset 0090h) <RC> */
union _IoPciecrRsr {
	kulong		word;
	struct {
		kulong	pmerid			:16;
		kulong	pmes				:1;
		kulong	pmepend		:1;
		kulong							:14;
	} bit;
};

/* Device Capabilities 2 Register (Offset 0094h) */
union _IoPciecrDc2r {
	kulong		word;
	struct {
		kulong	ctrs					:4;
		kulong	ctds					:1;
		kulong	arifs					:1;
		kulong	aors					:1;
		kulong	_32aocs			:1;
		kulong	_64aocs			:1;
		kulong	_128cascs		:1;
		kulong	nroprprp			:1;
		kulong	ltrms				:1;
		kulong	tphcs				:2;
		kulong	lnscls				:2;
		kulong							:2;
		kulong	obffs				:2;
		kulong							:12;
	} bit;
};

/* Device Control2 Register (Offset 0098h) */
/* Device Status2 Register (Offset 009Ah) */
union _IoPciecrDc2sr {
	kulong		word;
	struct {
		kulong	ctv				:4;
		kulong	ctd				:1;
		kulong	arife				:1;
		kulong						:4;
		kulong	ltrme			:1;
		kulong						:5;
		kulong						:16;
	} bit;
};

/* Link Capability2 Register (Offset 009Ch) */
union _IoPciecrLc2r {
	kulong		word;
	struct {
		kulong						:1;
		kulong	slsv				:7;
		kulong	clsp				:1;
		kulong						:22;
		kulong	drss				:1;
	} bit;
};

/* Link Control2 Register (Offset 00A0h) */
/* Link Status2 Register (Offset 00A2h) */
union _IoPciecrLc2sr {
	kulong		word;
	struct {
		kulong	tls					:4;
		kulong	ec					:1;
		kulong	hasd			:1;
		kulong	sde				:1;
		kulong	tm				:3;
		kulong	emc				:1;
		kulong	csos				:1;
		kulong	cpde			:4;
		kulong	cdel				:1;
		kulong						:11;
		kulong	dcp				:3;
		kulong	drsmr			:1;
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
	kuchar				dmy00a400af[0x00B0-0x00A4];	/* +00A4 - 00AFh */
};

/* Advanced Error Reporting Enhanced Capability Header (Offset 0100h) */
union _IoAercAerech {
	kulong		word;
	struct {
		kulong	pcieecid		:16;
		kulong	capv				:4;
		kulong	nco				:12;
	} bit;
};

/* Uncorrectable Error Status Register (Offset 0104h) */
union _IoAercUesr {
	kulong		word;
	struct {
		kulong						:4;
		kulong	dlpes			:1;
		kulong	sdes				:1;
		kulong						:6;
		kulong	ptlps			:1;
		kulong	fcpes			:1;
		kulong	cts				:1;
		kulong	cas				:1;
		kulong	ucs				:1;
		kulong	ros				:1;
		kulong	mtlps			:1;
		kulong	ecrces			:1;
		kulong	ures				:1;
		kulong						:1;
		kulong	uies				:1;
		kulong						:2;
		kulong	tlppbes		:1;
		kulong						:6;
	} bit;
};

/* Uncorrectable Error Mask Register (Offset 0108h) */
union _IoAercUemr {
	kulong		word;
	struct {
		kulong						:4;
		kulong	dlpem			:1;
		kulong	sdem			:1;
		kulong						:6;
		kulong	ptlpm			:1;
		kulong	fcpem			:1;
		kulong	ctm				:1;
		kulong	cam				:1;
		kulong	ucm				:1;
		kulong	rom				:1;
		kulong	mtlpm			:1;
		kulong	ecrcem		:1;
		kulong	urem			:1;
		kulong						:1;
		kulong	uiem			:1;
		kulong						:1;
		kulong	aoebm			:1;
		kulong	tlppbem		:1;
		kulong						:6;
	} bit;
};

/* Uncorrectable Error Severity Register (Offset 010Ch) */
union _IoAercUesvr {
	kulong		word;
	struct {
		kulong						:4;
		kulong	dlpes			:1;
		kulong	sdes				:1;
		kulong						:6;
		kulong	ptlps			:1;
		kulong	fcpes			:1;
		kulong	ctes				:1;
		kulong	caes				:1;
		kulong	uces				:1;
		kulong	roes				:1;
		kulong	mtlps			:1;
		kulong	ecrces			:1;
		kulong	ures				:1;
		kulong						:1;
		kulong	uies				:1;
		kulong						:1;
		kulong	aoebs			:1;
		kulong	tlppbes		:1;
		kulong						:6;
	} bit;
};

/* Correctable Error Status Register (Offset 0110h) */
union _IoAercCesr {
	kulong		word;
	struct {
		kulong	res				:1;
		kulong						:5;
		kulong	btlps			:1;
		kulong	bdllps			:1;
		kulong	rnrs				:1;
		kulong						:3;
		kulong	rtts				:1;
		kulong	anfes			:1;
		kulong	cies				:1;
		kulong	hlos				:1;
		kulong						:16;
	} bit;
};

/* Correctable Error Mask Register (Offset 0114h) */
union _IoAercCemr {
	kulong		word;
	struct {
		kulong	rem				:1;
		kulong						:5;
		kulong	btlpm			:1;
		kulong	bdllpm		:1;
		kulong	rnrm			:1;
		kulong						:3;
		kulong	rttm				:1;
		kulong	anfem			:1;
		kulong	ciem			:1;
		kulong	hlom			:1;
		kulong						:16;
	} bit;
};

/* Advanced Error Capabilities and Control Register (Offset 0118h) */
union _IoAercAeccr {
	kulong		word;
	struct {
		kulong	fep				:5;
		kulong	ecrcgc			:1;
		kulong	ecrcge			:1;
		kulong	ecrccc			:1;
		kulong	ecrcce			:1;
		kulong	mhrc			:1;
		kulong	mhre			:1;
		kulong						:21;
	} bit;
};

/* Header Log Register (Offset 011Ch,0120h,0124h,0128h) */
union _IoAercHlr {
	kulong		word;
	struct {
		kulong	hlr				:32;
	} bit;
};

/* Root Error Command Register (Offset 012Ch) <RC> */
union _IoAercRecr {
	kulong		word;
	struct {
		kulong	cere				:1;
		kulong	nfere			:1;
		kulong	fere				:1;
		kulong						:29;
	} bit;
};

/* Root Error Status Register (Offset 0130h) <RC> */
union _IoAercResr {
	kulong		word;
	struct {
		kulong	ercorr			:1;
		kulong	mercorr		:1;
		kulong	erfnfr			:1;
		kulong	merfnfr		:1;
		kulong	fuf				:1;
		kulong	nfemr			:1;
		kulong	femr			:1;
		kulong						:20;
		kulong	aeimn			:5;
	} bit;
};

/* Error Source Identification Register (Offset 0134h) <RC> */
union _IoAercEsir {
	kulong		word;
	struct {
		kulong	ercorsi			:16;
		kulong	erfnfsi			:16;
	} bit;
};

/* TLP Prefix Log Register (Offset 0138h,013Ch,0140h,0144h) */
union _IoTlpplr {
	kulong		word;
	struct {
		kulong	tlpplr			:32;
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
	kulong		word;
	struct {
		kulong	pcieecid		:16;
		kulong	capv			:4;
		kulong	nco				:12;
	} bit;
};

/* Max Snoop Latency Register    (Offset 014Ch) */
/* Max No-Snoop Latency Register (Offset 014Eh) */
union _IoLtrcMsnslr {
	kulong		word;
	struct {
		kulong	mslv			:10;
		kulong	msls			:3;
		kulong					:3;
		kulong	mnslv		:10;
		kulong	mnsls		:3;
		kulong					:3;
	} bit;
};

/* Latency Tolerance Reporting (LTR) Capability */
struct _IoLtrc {
	IoLtrcLtrech		ltrech;								/* +0148 - 014Bh */
	IoLtrcMsnslr		msnslr;							/* +014C - 014Fh */
};

/* L1 PM Substates Extended Capability Header (Offset 0150h) */
union _IoL1pmsecL1pmsech {
	kulong		word;
	struct {
		kulong	pcieecid		:16;
		kulong	cv					:4;
		kulong	nco				:12;
	} bit;
};

/* L1 PM Substates Capabilities Register (Offset 0154h) */
union _IoL1pmsecL1pmscr {
	kulong		word;
	struct {
		kulong	pcipml12s		:1;
		kulong	pcipml11s		:1;
		kulong	aspml12s			:1;
		kulong	aspml11s			:1;
		kulong	l1pmss				:1;
		kulong							:3;
		kulong	pcmrt				:8;
		kulong	ptpos				:2;
		kulong							:1;
		kulong	ptpov				:5;
		kulong							:8;
	} bit;
};

/* L1 PM Substates Control 1 Register (Offset 0158h) */
union _IoL1pmsecL1pmsc1r {
	kulong		word;
	struct {
		kulong	pcipml12e		:1;
		kulong	pcipml11e		:1;
		kulong	aspml12e		:1;
		kulong	aspml11e		:1;
		kulong							:4;
		kulong	cmrt					:8;
		kulong	ltrl12tv				:10;
		kulong							:3;
		kulong	ltrl12ts				:3;
	} bit;
};

/* L1 PM Substates Control 2 Register (Offset 015Ch) */
union _IoL1pmsecL1pmsc2r {
	kulong		word;
	struct {
		kulong	tpos			:2;
		kulong					:1;
		kulong	tpov			:5;
		kulong					:24;
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
	kulong		word;
	struct {
		kulong	rtl			:16;
		kulong	rtltl		:16;
	} bit;
};

/* VENDOR_SPEC_DLLP_OFF (Offset 0704h) */
union _IoPplVsd {
	kulong		word;
	struct {
		kulong	vsd			:32;
	} bit;
};

/* PORT_FORCE_OFF (Offset 0708h) */
union _IoPplPf {
	kulong		word;
	struct {
		kulong	ln			:8;
		kulong	fl			:4;
		kulong				:3;
		kulong	fe			:1;
		kulong	ls			:6;
		kulong				:2;
		kulong	csc		:8;
	} bit;
};

/* ACK_F_ASPM_CTRL_OFF (Offset 070Ch) */
union _IoPplAfac {
	kulong		word;
	struct {
		kulong	af				:8;
		kulong	anf			:8;
		kulong	ccnf			:8;
		kulong	l0sel			:3;
		kulong	l1el			:3;
		kulong	ea			:1;
		kulong					:1;
	} bit;
};

/* PORT_LINK_CTRL_OFF (Offset 0710h) */
union _IoPplPlc {
	kulong		word;
	struct {
		kulong	vsdr		:1;
		kulong	sd			:1;
		kulong	le			:1;
		kulong	ra			:1;
		kulong				:1;
		kulong	dle		:1;
		kulong				:1;
		kulong	flm		:1;
		kulong				:4;
		kulong				:4;
		kulong	lc			:6;
		kulong				:2;
		kulong				:1;
		kulong				:1;
		kulong				:1;
		kulong				:1;
		kulong				:4;
	} bit;
};

/* LANE_SKEW_OFF (Offset 0714h) */
union _IoPplLs {
	kulong		word;
	struct {
		kulong	ils				:24;
		kulong	fcd			:1;
		kulong	and			:1;
		kulong					:5;
		kulong	dltld			:1;
	} bit;
};

/* TIMER_CTRL_MAX_FUNC_NUM_OFF (Offset 0718h) */
union _IoPplTcmfn {
	kulong		word;
	struct {
		kulong	mfn			:8;
		kulong					:6;
		kulong	tmrt			:5;
		kulong	tman		:5;
		kulong					:5;
		kulong					:3;
	} bit;
};

/* SYMBOL_TIMER_FILTER_1_OFF (Offset 071Ch) */
union _IoPplStf1 {
	kulong		word;
	struct {
		kulong	siv			:11;
		kulong					:4;
		kulong	dfwt			:1;
		kulong	mr1			:16;
	} bit;
};

/* FILTER_MASK_2_OFF (Offset 0720h) */
union _IoPplFm2 {
	kulong		word;
	struct {
		kulong	mr2			:32;
	} bit;
};

/* AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF (Offset 0724h) */
union _IoPplAmodnsrc {
	kulong		word;
	struct {
		kulong	orsbe		:1;
		kulong					:31;
	} bit;
};

/* PL_DEBUG0_OFF (Offset 0728h) */
union _IoPplPd0 {
	kulong		word;
	struct {
		kulong	dr0			:32;
	} bit;
};

/* PL_DEBUG1_OFF (Offset 072Ch) */
union _IoPplPd1 {
	kulong		word;
	struct {
		kulong	dr1			:32;
	} bit;
};

/* TX_P_FC_CREDIT_STATUS_OFF (Offset 0730h) */
union _IoPplTpfcs {
	kulong		word;
	struct {
		kulong	tpdfc		:12;
		kulong	tphfc		:8;
		kulong					:12;
	} bit;
};

/* TX_NP_FC_CREDIT_STATUS_OFF (Offset 0734h) */
union _IoPplTnfcs {
	kulong		word;
	struct {
		kulong	tndfc		:12;
		kulong	tnhfc		:8;
		kulong					:12;
	} bit;
};

/* TX_CPL_FC_CREDIT_STATUS_OFF (Offset 0738h) */
union _IoPplTcfcs {
	kulong		word;
	struct {
		kulong	tcdfc		:12;
		kulong	tchfc		:8;
		kulong					:12;
	} bit;
};

/* QUEUE_STATUS_OFF (Offset 073Ch) */
union _IoPplQs {
	kulong		word;
	struct {
		kulong	rtfcnr		:1;
		kulong	trbn			:1;
		kulong	rqne			:1;
		kulong					:13;
		kulong	tmfc			:13;
		kulong					:2;
		kulong	tmfce		:1;
	} bit;
};

/* VC_TX_ARBI_1_OFF (Offset 0740h) */
union _IoPplVta1 {
	kulong		word;
	struct {
		kulong	wwv0		:8;
		kulong	wwv1		:8;
		kulong	wwv2		:8;
		kulong	wwv3		:8;
	} bit;
};

/* VC_TX_ARBI_2_OFF (Offset 0744h) */
union _IoPplVta2 {
	kulong		word;
	struct {
		kulong	wwv4		:8;
		kulong	wwv5		:8;
		kulong	wwv6		:8;
		kulong	wwv7		:8;
	} bit;
};

/* VC0_P_RX_Q_CTRL_OFF (Offset 0748h) */
union _IoPplVprqc {
	kulong		word;
	struct {
		kulong	vpdc		:12;
		kulong	vphc		:8;
		kulong					:1;
		kulong	vptqm		:3;
		kulong					:6;
		kulong	ttov			:1;
		kulong	vorq			:1;
	} bit;
};

/* VC0_NP_RX_Q_CTRL_OFF (Offset 074Ch) */
union _IoPplVnrqc {
	kulong		word;
	struct {
		kulong	vndc		:12;
		kulong	vnhc		:8;
		kulong					:1;
		kulong	vntqm		:3;
		kulong					:8;
	} bit;
};

/* VC0_CPL_RX_Q_CTRL_OFF (Offset 0750h) */
union _IoPplVcrqc {
	kulong		word;
	struct {
		kulong	vcdc			:12;
		kulong	vchc			:8;
		kulong					:1;
		kulong	vctqm		:3;
		kulong					:8;
	} bit;
};

/* GEN2_CTRL_OFF (Offset 080Ch) */
union _IoPplGen2c {
	kulong		word;
	struct {
		kulong	fts			:8;
		kulong	nol			:5;
		kulong	pdl			:3;
		kulong	alfce		:1;
		kulong	dsc			:1;
		kulong	cptc			:1;
		kulong	ctcr			:1;
		kulong	sd				:1;
		kulong	gei			:1;
		kulong					:10;
	} bit;
};

/* PHY_STATUS_OFF (Offset 0810h) */
union _IoPplPhys {
	kulong		word;
	struct {
		kulong	ps			:32;
	} bit;
};

/* PHY_CONTROL_OFF (Offset 0814h) */
union _IoPplPhyc {
	kulong		word;
	struct {
		kulong	pc			:32;
	} bit;
};

/* MSI_CTRL_ADDR_OFF (Offset 0820h) */
union _IoPplMca {
	kulong		word;
	struct {
		kulong	mca			:32;
	} bit;
};

/* MSI_CTRL_UPPER_ADDR_OFF (Offset 0824h) */
union _IoPplMcua {
	kulong		word;
	struct {
		kulong	mcua		:32;
	} bit;
};

/* MSI_CTRL_INT_0_EN_OFF (Offset 0828h) */
union _IoPplMci0e {
	kulong		word;
	struct {
		kulong	mci0e		:32;
	} bit;
};

/* MSI_CTRL_INT_0_MASK_OFF (Offset 082Ch) */
union _IoPplMci0m {
	kulong		word;
	struct {
		kulong	mci0m		:32;
	} bit;
};

/* MSI_CTRL_INT_0_STATUS_OFF (Offset 0830h) */
union _IoPplMci0s {
	kulong		word;
	struct {
		kulong	mci0s		:32;
	} bit;
};

/* MSI_GPIO_IO_OFF (Offset 0888h) */
union _IoPplMgi {
	kulong		word;
	struct {
		kulong	mgr			:32;
	} bit;
};

/* PIPE_LOOPBACK_CONTROL_OFF (Offset 08B8h) */
union _IoPplPilc {
	kulong		word;
	struct {
		kulong				:16;
		kulong				:6;
		kulong				:2;
		kulong				:3;
		kulong				:4;
		kulong	ple		:1;
	} bit;
};

/* MISC_CONTROL_1_OFF (Offset 08BCh) */
union _IoPplMc1 {
	kulong		word;
	struct {
		kulong	drwe		:1;
		kulong					:31;
	} bit;
};

/* MULTI_LANE_CONTROL_OFF (Offset 08C0h) */
union _IoPplMlc {
	kulong		word;
	struct {
		kulong	tlw			:6;
		kulong	dlwc		:1;
		kulong	us			:1;
		kulong				:24;
	} bit;
};

/* PHY_INTEROP_CTRL_OFF (Offset 08C4h) */
union _IoPplPhyic {
	kulong		word;
	struct {
		kulong	rc			:7;
		kulong				:1;
		kulong	l1em		:1;
		kulong	l1np		:1;
		kulong				:22;
	} bit;
};

/* LINK_FLUSH_CONTROL_OFF (Offset 08CCh) */
union _IoPplLfc {
	kulong		word;
	struct {
		kulong	afe			:1;
		kulong					:31;
	} bit;
};

/* AMBA_ERROR_RESPONSE_DEFAULT_OFF (Offset 08D0h) */
union _IoPplAerdr {
	kulong		word;
	struct {
		kulong	aerg		:1;
		kulong				:1;
		kulong	aerv		:1;
		kulong				:7;
		kulong	aerm	:6;
		kulong				:16;
	} bit;
};

/* AMBA_LINK_TIMEOUT_OFF (Offset 08D4h) */
union _IoPplAmlt {
	kulong		word;
	struct {
		kulong	ltpd		:8;
		kulong	lted		:1;
		kulong				:23;
	} bit;
};

/* AMBA_ORDERING_CTRL_OFF (Offset 08D8h) */
union _IoPplAoc {
	kulong		word;
	struct {
		kulong	amnpp		:1;
		kulong	ase				:1;
		kulong						:30;
	} bit;
};

/* COHERENCY_CONTROL_1_OFF (Offset 08E0h) */
union _IoPplCc1 {
	kulong		word;
	struct {
		kulong	cmv			:1;
		kulong					:1;
		kulong	cmbla		:30;
	} bit;
};

/* COHERENCY_CONTROL_2_OFF (Offset 08E4h) */
union _IoPplCc2 {
	kulong		word;
	struct {
		kulong	cmbha		:32;
	} bit;
};

/* COHERENCY_CONTROL_3_OFF (Offset 08E8h) */
union _IoPplCc3 {
	kulong		word;
	struct {
		kulong						:3;
		kulong	cmarm		:4;
		kulong						:4;
		kulong	cmawm		:4;
		kulong						:4;
		kulong	cmarv			:4;
		kulong						:4;
		kulong	cmawv			:4;
		kulong						:1;
	} bit;
};

/* AXI_MSTR_MSG_ADDR_LOW_OFF (Offset 08F0h) */
union _IoPplAmmal {
	kulong		word;
	struct {
		kulong					:12;
		kulong	camal		:20;
	} bit;
};

/* AXI_MSTR_MSG_ADDR_HIGH_OFF (Offset 08F4h) */
union _IoPplAmmah {
	kulong		word;
	struct {
		kulong	camah		:32;
	} bit;
};

/* IATU_VIEWPORT_OFF (Offset 0900h) */
union _IoPplIv {
	kulong		word;
	struct {
		kulong	ri			:1;
		kulong				:30;
		kulong	rd			:1;
	} bit;
};

/* IATU_REGION_CTRL_1_OFF_OUTBOUND_0 (Offset 0904h) */
/* IATU_REGION_CTRL_1_OFF_INBOUND_0  (Offset 0904h) */
union _IoPplIrc1 {
	kulong		word;
	struct {
		kulong	type		:5;
		kulong	tc			:3;
		kulong	td			:1;
		kulong	attr		:2;
		kulong				:5;
		kulong	at			:2;
		kulong				:2;
		kulong	c1fn		:3;
		kulong				:9;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF_OUTBOUND_0 (Offset 0908h) */
union _IoPplIrc2o {
	kulong		word;
	struct {
		kulong	mc			:8;
		kulong	tag			:8;
		kulong	tse			:1;
		kulong					:2;
		kulong	fb				:1;
		kulong	snp			:1;
		kulong					:1;
		kulong	ip				:1;
		kulong	hse			:1;
		kulong					:3;
		kulong	db			:1;
		kulong	csm			:1;
		kulong	im			:1;
		kulong					:1;
		kulong	re				:1;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF_INBOUND_0 (Offset 0908h) */
union _IoPplIrc2i {
	kulong		word;
	struct {
		kulong	mc			:8;
		kulong	bn			:3;
		kulong					:3;
		kulong	tcme		:1;
		kulong	tdme		:1;
		kulong	attrme		:1;
		kulong					:1;
		kulong	atme		:1;
		kulong	fnme		:1;
		kulong					:1;
		kulong	mcme		:1;
		kulong					:1;
		kulong	salte			:1;
		kulong	rc				:2;
		kulong					:1;
		kulong	ftmc			:1;
		kulong	csm			:1;
		kulong	im			:1;
		kulong	mm			:1;
		kulong	re				:1;
	} bit;
};

/* IATU_REGION_CTRL_2_OFF */
union _IoPplIrc2 {
	kulong		word;
	IoPplIrc2o	ob;
	IoPplIrc2i	ib;
};

/* IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0 (Offset 090Ch) */
/* IATU_LWR_BASE_ADDR_OFF_INBOUND_0  (Offset 090Ch) */
union _IoPplIlba {
	kulong		word;
	struct {
		kulong	lbh			:16;
		kulong	lbr			:16;
	} bit;
};

/* IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0 (Offset 0910h) */
/* IATU_UPPER_BASE_ADDR_OFF_INBOUND_0  (Offset 0910h) */
union _IoPplIuba {
	kulong		word;
	struct {
		kulong	ubr			:32;
	} bit;
};

/* IATU_LIMIT_ADDR_OFF_OUTBOUND_0 (Offset 0914h) */
/* IATU_LIMIT_ADDR_OFF_INBOUND_0  (Offset 0914h) */
union _IoPplIla {
	kulong		word;
	struct {
		kulong	lah			:16;
		kulong	lar			:16;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0 (Offset 0918h) */
union _IoPplIltao {
	kulong		word;
	struct {
		kulong	ltro		:32;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF_INBOUND_0 (Offset 0918h) */
union _IoPplIltai {
	kulong		word;
	struct {
		kulong	lth			:16;
		kulong	ltr				:16;
	} bit;
};

/* IATU_LWR_TARGET_ADDR_OFF */
union _IoPplIlta {
	kulong		word;
	IoPplIltao	ob;
	IoPplIltai		ib;
};

/* IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0 (Offset 091Ch) */
/* IATU_UPPER_TARGET_ADDR_OFF_INBOUND_0 (Offset 091Ch) */
union _IoPplIuta {
	kulong		word;
	struct {
		kulong	utr			:32;
	} bit;
};

/* DMA_CTRL_DATA_ARB_PRIOR_OFF (Offset 0970h) */
union _IoPplDcdap {
	kulong		word;
	struct {
		kulong	rw			:3;
		kulong	wctw		:3;
		kulong	rctw			:3;
		kulong	rtw			:3;
		kulong					:20;
	} bit;
};

/* DMA_CTRL_OFF (Offset 0978h) */
union _IoPplDc {
	kulong		word;
	struct {
		kulong	ndwc		:4;
		kulong					:12;
		kulong	ndrc			:4;
		kulong					:12;
	} bit;
};

/* DMA_WRITE_ENGINE_EN_OFF (Offset 097Ch) */
union _IoPplDwee {
	kulong		word;
	struct {
		kulong	dwe			:1;
		kulong					:31;
	} bit;
};

/* DMA_WRITE_DOORBELL_OFF (Offset 0980h) */
union _IoPplDwd {
	kulong		word;
	struct {
		kulong	wdn			:3;
		kulong					:28;
		kulong	ws			:1;
	} bit;
};

/* DMA_WRITE_CHANNEL_ARB_WEIGHT_LOW_OFF (Offset 0988h) */
union _IoPplDwcawl {
	kulong		word;
	struct {
		kulong	wc0w		:5;
		kulong	wc1w		:5;
		kulong	wc2w		:5;
		kulong	wc3w		:5;
		kulong					:12;
	} bit;
};

/* DMA_WRITE_CHANNEL_ARB_WEIGHT_HIGH_OFF (Offset 098Ch) */
union _IoPplDwcawh {
	kulong		word;
	struct {
		kulong	wc4w		:5;
		kulong	wc5w		:5;
		kulong	wc6w		:5;
		kulong	wc7w		:5;
		kulong					:12;
	} bit;
};

/* DMA_READ_ENGINE_EN_OFF (Offset 099Ch) */
union _IoPplDree {
	kulong		word;
	struct {
		kulong	dre			:1;
		kulong					:31;
	} bit;
};

/* DMA_READ_DOORBELL_OFF (Offset 09A0h) */
union _IoPplDrd {
	kulong		word;
	struct {
		kulong	rdn		:3;
		kulong				:28;
		kulong	rs			:1;
	} bit;
};

/* DMA_READ_CHANNEL_ARB_WEIGHT_LOW_OFF (Offset 09A8h) */
union _IoPplDrcawl {
	kulong		word;
	struct {
		kulong	rc0w		:5;
		kulong	rc1w		:5;
		kulong	rc2w		:5;
		kulong	rc3w		:5;
		kulong					:12;
	} bit;
};

/* DMA_READ_CHANNEL_ARB_WEIGHT_HIGH_OFF (Offset 09ACh) */
union _IoPplDrcawh {
	kulong		word;
	struct {
		kulong	rc4w		:5;
		kulong	rc5w		:5;
		kulong	rc6w		:5;
		kulong	rc7w		:5;
		kulong					:12;
	} bit;
};

/* DMA_WRITE_INT_STATUS_OFF (Offset 09BCh) */
union _IoPplDwis {
	kulong		word;
	struct {
		kulong	wdis			:8;
		kulong					:8;
		kulong	wais			:8;
		kulong					:8;
	} bit;
};

/* DMA_WRITE_INT_MASK_OFF (Offset 09C4h) */
union _IoPplDwim {
	kulong		word;
	struct {
		kulong	wdim		:2;
		kulong					:14;
		kulong	waim		:2;
		kulong					:14;
	} bit;
};

/* DMA_WRITE_INT_CLEAR_OFF (Offset 09C8h) */
union _IoPplDwic {
	kulong		word;
	struct {
		kulong	wdic		:8;
		kulong				:8;
		kulong	waic		:8;
		kulong				:8;
	} bit;
};

/* DMA_WRITE_ERR_STATUS_OFF (Offset 09CCh) */
union _IoPplDwes {
	kulong		word;
	struct {
		kulong	ared			:8;
		kulong					:8;
		kulong	lefed		:8;
		kulong					:8;
	} bit;
};

/* DMA_WRITE_DONE_IMWR_LOW_OFF (Offset 09D0h) */
union _IoPplDwdil {
	kulong		word;
	struct {
		kulong	dwdlr		:32;
	} bit;
};

/* DMA_WRITE_DONE_IMWR_HIGH_OFF (Offset 09D4h) */
union _IoPplDwdih {
	kulong		word;
	struct {
		kulong	dwdhr		:32;
	} bit;
};

/* DMA_WRITE_ABORT_IMWR_LOW_OFF (Offset 09D8h) */
union _IoPplDwail {
	kulong		word;
	struct {
		kulong	dwalr		:32;
	} bit;
};

/* DMA_WRITE_ABORT_IMWR_HIGH_OFF (Offset 09DCh) */
union _IoPplDwaih {
	kulong		word;
	struct {
		kulong	dwahr		:32;
	} bit;
};

/* DMA_WRITE_CH01_IMWR_DATA_OFF (Offset 09E0h) */
union _IoPplDwc01id {
	kulong		word;
	struct {
		kulong	wc0d			:16;
		kulong	wc1d			:16;
	} bit;
};

/* DMA_WRITE_CH23_IMWR_DATA_OFF (Offset 09E4h) */
union _IoPplDwc23id {
	kulong		word;
	struct {
		kulong	wc2d			:16;
		kulong	wc3d			:16;
	} bit;
};

/* DMA_WRITE_CH45_IMWR_DATA_OFF (Offset 09E8h) */
union _IoPplDwc45id {
	kulong		word;
	struct {
		kulong	wc4d			:16;
		kulong	wc5d			:16;
	} bit;
};

/* DMA_WRITE_CH67_IMWR_DATA_OFF (Offset 09ECh) */
union _IoPplDwch67id {
	kulong		word;
	struct {
		kulong	wc6d			:16;
		kulong	wc7d			:16;
	} bit;
};

/* DMA_WRITE_LINKED_LIST_ERR_EN_OFF (Offset 0A00h) */
union _IoPplDwllee {
	kulong		word;
	struct {
		kulong	wclllaie	:2;
		kulong					:14;
		kulong	wcllraie	:2;
		kulong					:14;
	} bit;
};

/* DMA_READ_INT_STATUS_OFF (Offset 0A10h) */
union _IoPplDris {
	kulong		word;
	struct {
		kulong	rdis		:8;
		kulong				:8;
		kulong	rais		:8;
		kulong				:8;
	} bit;
};

/* DMA_READ_INT_MASK_OFF (Offset 0A18h) */
union _IoPplDrim {
	kulong		word;
	struct {
		kulong	rdim	:2;
		kulong				:14;
		kulong	raim		:2;
		kulong				:14;
	} bit;
};

/* DMA_READ_INT_CLEAR_OFF (Offset 0A1Ch) */
union _IoPplDric {
	kulong		word;
	struct {
		kulong	rdic		:8;
		kulong				:8;
		kulong	raic		:8;
		kulong				:8;
	} bit;
};

/* DMA_READ_ERR_STATUS_LOW_OFF (Offset 0A24h) */
union _IoPplDresl {
	kulong		word;
	struct {
		kulong	awed		:8;
		kulong					:8;
		kulong	llefed		:8;
		kulong					:8;
	} bit;
};

/* DMA_READ_ERR_STATUS_HIGH_OFF (Offset 0A28h) */
union _IoPplDresh {
	kulong		word;
	struct {
		kulong	ur			:8;
		kulong	ca			:8;
		kulong	ct			:8;
		kulong	dp		:8;
	} bit;
};

/* DMA_READ_LINKED_LIST_ERR_EN_OFF (Offset 0A34h) */
union _IoPplDrllee {
	kulong		word;
	struct {
		kulong	rclllaie		:2;
		kulong					:14;
		kulong	rcllraie		:2;
		kulong					:14;
	} bit;
};

/* DMA_READ_DONE_IMWR_LOW_OFF (Offset 0A3Ch) */
union _IoPplDrdil {
	kulong		word;
	struct {
		kulong	drdlr		:32;
	} bit;
};

/* DMA_READ_DONE_IMWR_HIGH_OFF (Offset 0A40h) */
union _IoPplDrdih {
	kulong		word;
	struct {
		kulong	drdhr		:32;
	} bit;
};

/* DMA_READ_ABORT_IMWR_LOW_OFF (Offset 0A44h) */
union _IoPplDrail {
	kulong		word;
	struct {
		kulong	dralr		:32;
	} bit;
};

/* DMA_READ_ABORT_IMWR_HIGH_OFF (Offset 0A48h) */
union _IoPplDraih {
	kulong		word;
	struct {
		kulong	drahr		:32;
	} bit;
};

/* DMA_READ_CH01_IMWR_DATA_OFF (Offset 0A4Ch) */
union _IoPplDrch01id {
	kulong		word;
	struct {
		kulong	rc0d			:16;
		kulong	rc1d			:16;
	} bit;
};

/* DMA_READ_CH23_IMWR_DATA_OFF (Offset 0A50h) */
union _IoPplDrch23id {
	kulong		word;
	struct {
		kulong	rc2d			:16;
		kulong	rc3d			:16;
	} bit;
};

/* DMA_READ_CH45_IMWR_DATA_OFF (Offset 0A54h) */
union _IoPplDrch45id {
	kulong		word;
	struct {
		kulong	rc4d			:16;
		kulong	rc5d			:16;
	} bit;
};

/* DMA_READ_CH67_IMWR_DATA_OFF (Offset 0A58h) */
union _IoPplDrch67id {
	kulong		word;
	struct {
		kulong	rc6d			:16;
		kulong	rc7d			:16;
	} bit;
};

/* DMA_VIEWPORT_SEL_OFF (Offset 0A6Ch) */
union _IoPplDvs {
	kulong		word;
	struct {
		kulong	cn			:3;
		kulong					:28;
		kulong	cd			:1;
	} bit;
};

/* DMA_CH_CONTROL1_OFF_WRCH_0 (Offset 0A70h) */
/* DMA_CH_CONTROL1_OFF_RDCH_0 (Offset 0A70h) */
union _IoPplDcc1 {
	kulong		word;
	struct {
		kulong	cb			:1;
		kulong	tcb			:1;
		kulong	llp			:1;
		kulong	lie			:1;
		kulong	rie			:1;
		kulong	cs				:2;
		kulong					:1;
		kulong	ccs			:1;
		kulong	lle			:1;
		kulong					:2;
		kulong	dfn			:5;
		kulong					:7;
		kulong	ns				:1;
		kulong	dro			:1;
		kulong	dtd			:1;
		kulong	dtc			:3;
		kulong	dat			:2;
	} bit;
};

/* DMA_TRANSFER_SIZE_OFF_WRCH_0 (Offset 0A78h) */
/* DMA_TRANSFER_SIZE_OFF_RDCH_0 (Offset 0A78h) */
union _IoPplDts {
	kulong		word;
	struct {
		kulong	dts			:32;
	} bit;
};

/* DMA_SAR_LOW_OFF_WRCH_0 (Offset 0A7Ch) */
/* DMA_SAR_LOW_OFF_RDCH_0 (Offset 0A7Ch) */
union _IoPplDsl {
	kulong		word;
	struct {
		kulong	sarl		:32;
	} bit;
};

/* DMA_SAR_HIGH_OFF_WRCH_0 (Offset 0A80h) */
/* DMA_SAR_HIGH_OFF_RDCH_0 (Offset 0A80h) */
union _IoPplDsh {
	kulong		word;
	struct {
		kulong	sarh		:32;
	} bit;
};

/* DMA_DAR_LOW_OFF_WRCH_0 (Offset 0A84h) */
/* DMA_DAR_LOW_OFF_RDCH_0 (Offset 0A84h) */
union _IoPplDdl {
	kulong		word;
	struct {
		kulong	darl		:32;
	} bit;
};

/* DMA_DAR_HIGH_OFF_WRCH_0 (Offset 0A88h) */
/* DMA_DAR_HIGH_OFF_RDCH_0 (Offset 0A88h) */
union _IoPplDdh {
	kulong		word;
	struct {
		kulong	darh		:32;
	} bit;
};

/* DMA_LLP_LOW_OFF_WRCH_0 (Offset 0A8Ch) */
/* DMA_LLP_LOW_OFF_RDCH_0 (Offset 0A8Ch) */
union _IoPplDll {
	kulong		word;
	struct {
		kulong	ll			:32;
	} bit;
};

/* DMA_LLP_HIGH_OFF_WRCH_0 (Offset 0A90h) */
/* DMA_LLP_HIGH_OFF_RDCH_0 (Offset 0A90h) */
union _IoPplDlh {
	kulong		word;
	struct {
		kulong	lh			:32;
	} bit;
};

/* PL_LTR_LATENCY_OFF (Offset 0B30h) */
union _IoPplPll {
	kulong		word;
	struct {
		kulong	slv			:10;
		kulong	sls			:3;
		kulong					:2;
		kulong	slr			:1;
		kulong	nslv			:10;
		kulong	nsls			:3;
		kulong					:2;
		kulong	nslr			:1;
	} bit;
};

/* AUX_CLK_FREQ_OFF (Offset 0B40h) */
union _IoPplAcf {
	kulong		word;
	struct {
		kulong	acf			:10;
		kulong					:22;
	} bit;
};

/* L1_SUBSTATES_OFF (Offset 0B44h) */
union _IoPplL1s {
	kulong		word;
	struct {
		kulong	l1tpo		:2;
		kulong	l1tl12		:4;
		kulong	l1tpa		:2;
		kulong					:24;
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
	kuchar					dmy0754080b[0x080C-0x0754];	/* +0754 - 080Bh */
	IoPplGen2c			gen2c;							/* +080C - 080Fh */
	IoPplPhys			phys;							/* +0810 - 0813h */
	IoPplPhyc			phyc;							/* +0814 - 0817h */
	kuchar					dmy0818081f[0x0820-0x0818];	/* +0818 - 081Fh */
	IoPplMca				mca;							/* +0820 - 0823h */
	IoPplMcua			mcua;							/* +0824 - 0827h */
	IoPplMci0e			mci0e;							/* +0828 - 082Bh */
	IoPplMci0m		mci0m;							/* +082C - 082Fh */
	IoPplMci0s			mci0s;							/* +0830 - 0833h */
	kuchar					dmy08340887[0x0888-0x0834];	/* +0834 - 0887h */
	IoPplMgi				mgi;							/* +0888 - 088Bh */
	kuchar					dmy088c08b7[0x08B8-0x088C];	/* +088C - 08B7h */
	IoPplPilc				pilc;							/* +08B8 - 08BBh */
	IoPplMc1				mc1;							/* +08BC - 08BFh */
	IoPplMlc				mlc;							/* +08C0 - 08C3h */
	IoPplPhyic			phyic;							/* +08C4 - 08C7h */
	kuchar					dmy08c808cb[0x08CC-0x08C8];	/* +08C8 - 08CBh */
	IoPplLfc				lfc;							/* +08CC - 08CFh */
	IoPplAerdr			aerdr;							/* +08D0 - 08D3h */
	IoPplAmlt			amlt;							/* +08D4 - 08D7h */
	IoPplAoc				aoc;							/* +08D8 - 08DBh */
	kuchar					dmy08dc08df[0x08E0-0x08DC];	/* +08DC - 08DFh */
	IoPplCc1				cc1;							/* +08E0 - 08E3h */
	IoPplCc2				cc2;							/* +08E4 - 08E7h */
	IoPplCc3				cc3;							/* +08E8 - 08EBh */
	kuchar					dmy08ec08ef[0x08F0-0x08EC];	/* +08EC - 08EFh */
	IoPplAmmal		ammal;							/* +08F0 - 08F3h */
	IoPplAmmah		ammah;							/* +08F4 - 08F7h */
	kuchar					dmy08f808ff[0x0900-0x08F8];	/* +08F8 - 08FFh */
	IoPplIv					iv;								/* +0900 - 0903h */
	IoPplIrc1				irc1;							/* +0904 - 0907h */
	IoPplIrc2				irc2;							/* +0908 - 090Bh */
	IoPplIlba				ilba;							/* +090C - 090Fh */
	IoPplIuba			iuba;							/* +0910 - 0913h */
	IoPplIla				ila;							/* +0914 - 0917h */
	IoPplIlta				ilta;							/* +0918 - 091Bh */
	IoPplIuta				iuta;							/* +091C - 091Fh */
	kuchar					dmy0920096f[0x0970-0x0920];	/* +0920 - 096Fh */
	IoPplDcdap			dcdap;							/* +0970 - 0973h */
	kuchar					dmy09740977[0x0978-0x0974];	/* +0974 - 0977h */
	IoPplDc				dc;								/* +0978 - 097Bh */
	IoPplDwee			dwee;							/* +097C - 097Fh */
	IoPplDwd			dwd;							/* +0980 - 0983h */
	kuchar					dmy09840987[0x0988-0x0984];	/* +0984 - 0987h */
	IoPplDwcawl		dwcawl;							/* +0988 - 098Bh */
	IoPplDwcawh		dwcawh;							/* +098C - 098Fh */
	kuchar					dmy0990099b[0x099C-0x0990];	/* +0990 - 099Bh */
	IoPplDree			dree;							/* +099C - 099Fh */
	IoPplDrd				drd;							/* +09A0 - 09A3h */
	kuchar					dmy09a409a7[0x09A8-0x09A4];	/* +09A4 - 09A7h */
	IoPplDrcawl		drcawl;							/* +09A8 - 09ABh */
	IoPplDrcawh		drcawh;							/* +09AC - 09AFh */
	kuchar					dmy09b009bb[0x09BC-0x09B0];	/* +09B0 - 09BBh */
	IoPplDwis			dwis;							/* +09BC - 09BFh */
	kuchar					dmy09c009c3[0x09C4-0x09C0];	/* +09C0 - 09C3h */
	IoPplDwim			dwim;							/* +09C4 - 09C7h */
	IoPplDwic			dwic;							/* +09C8 - 09CBh */
	IoPplDwes			dwes;							/* +09CC - 09CFh */
	IoPplDwdil			dwdil;							/* +09D0 - 09D3h */
	IoPplDwdih			dwdih;							/* +09D4 - 09D7h */
	IoPplDwail			dwail;							/* +09D8 - 09DBh */
	IoPplDwaih			dwaih;							/* +09DC - 09DFh */
	IoPplDwc01id		dwc01id;						/* +09E0 - 09E3h */
	IoPplDwc23id		dwc23id;						/* +09E4 - 09E7h */
	IoPplDwc45id		dwc45id;						/* +09E8 - 09EBh */
	IoPplDwch67id	dwch67id;						/* +09EC - 09EFh */
	kuchar					dmy09f009ff[0x0A00-0x09F0];	/* +09F0 - 09FFh */
	IoPplDwllee		dwllee;							/* +0A00 - 0A03h */
	kuchar					dmy0a040a0f[0x0A10-0x0A04];	/* +0A04 - 0A0Fh */
	IoPplDris				dris;							/* +0A10 - 0A13h */
	kuchar					dmy0a140a17[0x0A18-0x0A14];	/* +0A14 - 0A17h */
	IoPplDrim			drim;							/* +0A18 - 0A1Bh */
	IoPplDric				dric;							/* +0A1C - 0A1Fh */
	kuchar					dmy0a200a23[0x0A24-0x0A20];	/* +0A20 - 0A23h */
	IoPplDresl			dresl;							/* +0A24 - 0A27h */
	IoPplDresh			dresh;							/* +0A28 - 0A2Bh */
	kuchar					dmy0a2c0a33[0x0A34-0x0A2C];	/* +0A2C - 0A33h */
	IoPplDrllee			drllee;							/* +0A34 - 0A37h */
	kuchar					dmy0a380a3b[0x0A3C-0x0A38];	/* +0A38 - 0A3Bh */
	IoPplDrdil			drdil;							/* +0A3C - 0A3Fh */
	IoPplDrdih			drdih;							/* +0A40 - 0A43h */
	IoPplDrail			drail;							/* +0A44 - 0A47h */
	IoPplDraih			draih;							/* +0A48 - 0A4Bh */
	IoPplDrch01id	drch01id;						/* +0A4C - 0A4Fh */
	IoPplDrch23id	drch23id;						/* +0A50 - 0A53h */
	IoPplDrch45id	drch45id;						/* +0A54 - 0A57h */
	IoPplDrch67id	drch67id;						/* +0A58 - 0A5Bh */
	kuchar					dmy0a5c0a6b[0x0A6C-0x0A5C];	/* +0A5C - 0A6Bh */
	IoPplDvs				dvs;							/* +0A6C - 0A6Fh */
	IoPplDcc1			dcc1;							/* +0A70 - 0A73h */
	kuchar					dmy0a740a77[0x0A78-0x0A74];	/* +0A74 - 0A77h */
	IoPplDts				dts;							/* +0A78 - 0A7Bh */
	IoPplDsl				dsl;							/* +0A7C - 0A7Fh */
	IoPplDsh				dsh;							/* +0A80 - 0A83h */
	IoPplDdl				ddl;							/* +0A84 - 0A87h */
	IoPplDdh				ddh;							/* +0A88 - 0A8Bh */
	IoPplDll				dll;							/* +0A8C - 0A8Fh */
	IoPplDlh				dlh;							/* +0A90 - 0A93h */
	kuchar					dmy0a940b2f[0x0B30-0x0A94];	/* +0A94 - 0B2Fh */
	IoPplPll				pll;							/* +0B30 - 0B33h */
	kuchar					dmy0b340b3f[0x0B40-0x0B34];	/* +0B34 - 0B3Fh */
	IoPplAcf				acf;							/* +0B40 - 0B43h */
	IoPplL1s				l1s;							/* +0B44 - 0B47h */
};

/* core register of Root Complex */
struct _IoPcieCoreRc {
	IoT1csh			t1csh;							/* +0000 - 003Fh */
	IoPmcr			pmcr;							/* +0040 - 004Fh */
	IoMsicr			msicr;							/* +0050 - 0067h */
	kuchar				dmy0068006f[0x0070-0x0068];	/* +0068 - 006Fh */
	IoPciecr			pciecr;							/* +0070 - 00AFh */
	kuchar				dmy00b000af[0x0100-0x00B0];	/* +00B0 - 00FFh */
	IoAerc				aerc;							/* +0100 - 0147h */
	IoLtrc				ltrc;							/* +0148 - 014Fh */
	IoL1pmsec		l1pmsec;						/* +0150 - 015Fh */
	kuchar				dmy016006ff[0x0700-0x0160];	/* +0160 - 06FFh */
	IoPpl				ppl;							/* +0700 - 0B47 */
};

/* core register of Endpoint */
struct _IoPcieCoreEp {
	IoT0csh			t0csh;							/* +0000 - 003Fh */
	IoPmcr			pmcr;							/* +0040 - 004Fh */
	IoMsicr			msicr;							/* +0050 - 0067h */
	kuchar				dmy0068006f[0x0070-0x0068];	/* +0068 - 006Fh */
	IoPciecr			pciecr;							/* +0070 - 00AFh */
	kuchar				dmy00b000af[0x0100-0x00B0];	/* +00B0 - 00FFh */
	IoAerc				aerc;							/* +0100 - 0147h */
	IoLtrc				ltrc;							/* +0148 - 014Fh */
	IoL1pmsec		l1pmsec;						/* +0150 - 015Fh */
	kuchar				dmy016006ff[0x0700-0x0160];	/* +0160 - 06FFh */
	IoPpl				ppl;							/* +0700 - 0B47h */
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
	kulong		word;
	struct {
		kulong	deviceType			:4;
		kulong	appLtssmEnable	:1;
		kulong								:3;
		kulong	appReqRetryEn	:1;
		kulong								:7;
		kulong	rxLaneFlipEn		:1;
		kulong								:3;
		kulong	txLaneFlipEn		:1;
		kulong								:11;
	} bit;
};

/* AXI_CLK_STOP (Offset 004h) */
union _IoPcieAxiClkStop {
	kulong		word;
	struct {
		kulong	mstrAclkStop		:1;
		kulong	mstrCsysreqReg	:1;
		kulong	mstrCsysackReg	:1;
		kulong	mstrCactiveReg	:1;
		kulong	slvAclkStop			:1;
		kulong	slvCsysreqReg		:1;
		kulong	slvCsysackReg		:1;
		kulong	slvCactiveReg		:1;
		kulong	dbiAclkStop			:1;
		kulong	dbiCsysreqReg	:1;
		kulong	dbiCsysackReg	:1;
		kulong	dbiCactiveReg		:1;
		kulong								:20;
	} bit;
};

/* CLOCK_CONTROL (Offset 006h) */
union _IoPcieClockControl {
	kulong		word;
	struct {
		kulong	appClkReqN	:1;
		kulong							:7;
		kulong	extPclkReq		:1;
		kulong							:3;
		kulong	clkSwitchEn		:1;
		kulong							:19;
	} bit;
};

/* RESET_CONTROL_1 (Offset 00Ch) */
union _IoPcieResetControl1 {
	kulong		word;
	struct {
		kulong	pwupRstNReg		:1;
		kulong	buttonRstNReg	:1;
		kulong								:2;
		kulong	perstNIReg			:1;
		kulong	perstNOReg		:1;
		kulong								:2;
		kulong	pipeRstNReg		:1;
		kulong								:3;
		kulong	coreRstNReg		:1;
		kulong								:3;
		kulong	nStiRstNReg		:1;
		kulong								:3;
		kulong	stiRstNReg			:1;
		kulong								:3;
		kulong	pwrRstNReg		:1;
		kulong								:3;
		kulong	phyRstNReg		:1;
		kulong	squRstNReg		:1;
		kulong								:2;
	} bit;
};

/* RESET_CONTROL_2 (Offset 010h) */
union _IoPcieResetControl2 {
	kulong		word;
	struct {
		kulong	mstrArstNReg		:1;
		kulong								:3;
		kulong	slvArstNReg			:1;
		kulong								:3;
		kulong	dbiArstNReg		:1;
		kulong								:7;
		kulong	appInitRst			:1;
		kulong								:15;
	} bit;
};

/* RESET_SELECT_1 (Offset 014h) */
union _IoPcieResetSelect1 {
	kulong		word;
	struct {
		kulong	pwupRstSel			:1;
		kulong	buttonRstSel		:1;
		kulong								:2;
		kulong	perstSel				:1;
		kulong								:3;
		kulong	pipeRstSel			:1;
		kulong								:3;
		kulong	coreRstSel			:1;
		kulong								:3;
		kulong	nStiRstSel			:1;
		kulong								:3;
		kulong	stiRstSel				:1;
		kulong								:3;
		kulong	pwrRstSel			:1;
		kulong								:3;
		kulong	phyRstSel			:1;
		kulong	squRstSel			:1;
		kulong								:2;
	} bit;
};

/* RESET_SELECT_2 (Offset 018h) */
union _IoPcieResetSelect2 {
	kulong		word;
	struct {
		kulong	mstrArstSel		:1;
		kulong							:3;
		kulong	slvArstSel			:1;
		kulong							:3;
		kulong	dbiArstSel		:1;
		kulong							:23;
	} bit;
};

/* MSI_REQUEST_1 (Offset 01Ch) */
union _IoPcieMsiRequest1 {
	kulong		word;
	struct {
		kulong	localInterrupt		:32;
	} bit;
};

/* MSI_REQUEST_2 (Offset 020h) */
union _IoPcieMsiRequest2 {
	kulong		word;
	struct {
		kulong	msiFuncNum		:3;
		kulong								:1;
		kulong	msiTc					:3;
		kulong								:25;
	} bit;
};

/* INTERRUPT_CONTROL_1 (Offset 024h) */
union _IoPcieIntControl1 {
	kulong		word;
	struct {
		kulong	sysInt					:1;
		kulong								:15;
		kulong	intSyncbyp			:1;
		kulong								:11;
		kulong	intaStatus			:1;
		kulong	intbStatus			:1;
		kulong	intcStatus			:1;
		kulong	intdStatus			:1;
	} bit;
};

/* INTERRUPT_CONTROL_2 (Offset 028h) */
union _IoPcieIntControl2 {
	kulong		word;
	struct {
		kulong	sendCorErrEn		:1;
		kulong	sendCorErrCen	:1;
		kulong	sendCorErrStt		:1;
		kulong	sendCorErrM		:1;
		kulong	sendNfErrEn		:1;
		kulong	sendNfErrCen		:1;
		kulong	sendNfErrStt		:1;
		kulong	sendNfErrM		:1;
		kulong	sendFErrEn			:1;
		kulong	sendFErrCen		:1;
		kulong	sendFErrStt			:1;
		kulong	sendFErrM			:1;
		kulong	sysErrRcEn			:1;
		kulong	sysErrRcCen		:1;
		kulong	sysErrRcStt			:1;
		kulong	sysErrRcM			:1;
		kulong	rdlhLinkUpEn		:1;
		kulong	rdlhLinkUpCen	:1;
		kulong	rdlhLinkUpStt		:1;
		kulong	rdlhLinkUpM		:1;
		kulong	wakeEn				:1;
		kulong	wakeClearEn		:1;
		kulong	wakeStatus			:1;
		kulong	wakeMask			:1;
		kulong	vendorMsgEn		:1;
		kulong	vendorMsgCen	:1;
		kulong	vendorMsgStt		:1;
		kulong	vendorMsgM		:1;
		kulong	smlhReqRstEn		:1;
		kulong	smlhReqRstCen	:1;
		kulong	smlhReqRstStt	:1;
		kulong	smlhReqRstM		:1;
	} bit;
};

/* INTERRUPT_CONTROL_3 (Offset 02Ch) */
union _IoPcieIntControl3 {
	kulong		word;
	struct {
		kulong	radmPmPmeEn		:1;
		kulong	radmPmPmeCen	:1;
		kulong	radmPmPmeStt		:1;
		kulong	radmPmPmeM		:1;
		kulong	radmMsgUlEn			:1;
		kulong	radmMsgUlCen		:1;
		kulong	radmMsgUlStt			:1;
		kulong	radmMsgUlM			:1;
		kulong	radmCorErrEn			:1;
		kulong	radmCorErrCen		:1;
		kulong	radmCorErrStt		:1;
		kulong	radmCorErrM			:1;
		kulong	radmNfErrEn			:1;
		kulong	radmNfErrCen		:1;
		kulong	radmNfErrStt			:1;
		kulong	radmNfErrM			:1;
		kulong	radmFErrEn				:1;
		kulong	radmFErrCen			:1;
		kulong	radmFErrStt			:1;
		kulong	radmFErrM				:1;
		kulong	radmMsgLtrEn		:1;
		kulong	radmMsgLtrCen		:1;
		kulong	radmMsgLtrStt		:1;
		kulong	radmMsgLtrM			:1;
		kulong	radmPm2ackEn		:1;
		kulong	radmPm2ackCen	:1;
		kulong	radmPm2ackStt		:1;
		kulong	radmPm2ackM		:1;
		kulong	radmPmToffEn		:1;
		kulong	radmPmToffCen		:1;
		kulong	radmPmToffStt		:1;
		kulong	radmPmToffM		:1;
	} bit;
};

/* ELECTROMECHANICAL_CONTROL (Offset 030h) */
union _IoPcieEmControl {
	kulong		word;
	struct {
		kulong	attenBPressed		:1;
		kulong									:3;
		kulong	preDetSttReg			:1;
		kulong									:3;
		kulong	mrlSensorStt			:1;
		kulong									:3;
		kulong	pwrFaultDet			:1;
		kulong									:3;
		kulong	mrlSensorChged		:1;
		kulong									:3;
		kulong	preDetChged			:1;
		kulong									:3;
		kulong	cmdCpledInt			:1;
		kulong									:3;
		kulong	emlIlEngaged			:1;
		kulong									:3;
	} bit;
};

/* ELECTROMECHANICAL_SELECT (Offset 034h) */
union _IoPcieEmSelect {
	kulong		word;
	struct {
		kulong								:4;
		kulong	preDetSttSel		:1;
		kulong								:27;
	} bit;
};

/* ELECRTOMECHANICAL_MONITOR (Offset 038h) */
union _IoPcieEmMonitor {
	kulong		word;
	struct {
		kulong	cfgEmlControl		:1;
		kulong								:31;
	} bit;
};

/* PM_UNLOCK_MESSAGE_REQUEST (Offset 03Ch) */
union _IoPciePmUnlockReq {
	kulong		word;
	struct {
		kulong	appUnlockMsg			:1;
		kulong										:3;
		kulong	pmXmtTurnoff			:1;
		kulong										:11;
		kulong	ltrMsgReq					:1;
		kulong										:11;
		kulong	ltrMsgFuncNum			:3;
		kulong										:1;
	} bit;
};

/* APP_LTR_MSG (Offset 040h) */
union _IoPcieLtrMsg {
	kulong		word;
	struct {
		kulong	ltrMsgLatency		:32;
	} bit;
};

/* LTR_MONITOR_1 (Offset 044h) */
union _IoPcieLtrMonitor1 {
	kulong		word;
	struct {
		kulong	appLtrMsgGr		:1;
		kulong								:30;
		kulong	appLtrMsgRst		:1;
	} bit;
};

/* LTR_MONITOR_2 (Offset 048h) */
union _IoPcieLtrMonitor2 {
	kulong		word;
	struct {
		kulong	appLtrLatency		:32;
	} bit;
};

/* PM_CONTROL_1 (Offset 04Ch) */
union _IoPciePmControl1 {
	kulong		word;
	struct {
		kulong	wakeReg			:1;
		kulong							:15;
		kulong	clkreqReg		:1;
		kulong							:15;
	} bit;
};

/* PM_CONTROL_2 (Offset 050h) */
union _IoPciePmControl2 {
	kulong		word;
	struct {
		kulong	outbandPwupCmd		:1;
		kulong										:3;
		kulong	appsPmXmtPme			:1;
		kulong										:3;
		kulong	sysAuxPwrDet				:1;
		kulong										:3;
		kulong	appReqEntrL1				:1;
		kulong										:3;
		kulong	ppRdyEntrL23				:1;
		kulong										:3;
		kulong	appReqExitL1				:1;
		kulong										:3;
		kulong	ppClkPmEn					:1;
		kulong										:3;
		kulong	appXferPending			:1;
		kulong										:3;
	} bit;
};

/* PM_SELECT_1 (Offset 054h) */
union _IoPciePmSelect1 {
	kulong		word;
	struct {
		kulong	wakeSel			:1;
		kulong							:15;
		kulong	clkreqSel			:1;
		kulong							:15;
	} bit;
};

/* PM_MONITOR_1 (Offset 058h) */
union _IoPciePmMonitor1 {
	kulong		word;
	struct {
		kulong	pmCurntState		:3;
		kulong								:1;
		kulong	pmDstate			:3;
		kulong								:1;
		kulong	pmStatus				:1;
		kulong								:3;
		kulong	pmPmeEn			:1;
		kulong								:3;
		kulong	smlhLtssmState	:6;
		kulong								:2;
		kulong	auxPmEn				:1;
		kulong								:7;
	} bit;
};

/* PM_MONITOR_2 (Offset 05Ch) */
union _IoPciePmMonitor2 {
	kulong		word;
	struct {
		kulong	pmLinkstInL0s	:1;
		kulong								:3;
		kulong	pmLinkstInL1		:1;
		kulong								:3;
		kulong	pmLinkstInL2		:1;
		kulong								:3;
		kulong	pmLinkstL2E		:1;
		kulong								:3;
		kulong	pmLinkstInL1s	:1;
		kulong								:3;
		kulong	cfgL1subEn			:1;
		kulong								:7;
		kulong	clkreqMonitor		:1;
		kulong								:3;
	} bit;
};

/* PHY_CONFIG_COMMON_1 (Offset 100h) */
union _IoPcieConfigCom1 {
	kulong		word;
	struct {
		kulong	pipeTx2rxLpbk			:1;
		kulong	phyRx2txLbEn				:1;
		kulong										:2;
		kulong	pgModeEn					:1;
		kulong	pmaPwForEn				:1;
		kulong	pcsPwForEn				:1;
		kulong										:1;
		kulong	phyMpllaForEn			:1;
		kulong	phyMpllaSscEn			:1;
		kulong	phyMpllbForEn			:1;
		kulong	phyMpllbSscEn			:1;
		kulong	phyExtCtrlSel				:1;
		kulong	phyRtuneReq				:1;
		kulong										:2;
		kulong	pcsPsoSCnt					:8;
		kulong	pcsStableCnt				:8;
	} bit;
};

/* PHY_CONFIG_COMMON_2 (Offset 104h) */
union _IoPcieConfigCom2 {
	kulong		word;
	struct {
		kulong	phyMpllMul		:7;
		kulong								:1;
		kulong	phyRefClkdiv2		:1;
		kulong								:11;
		kulong	rx0SrisModeEn	:1;
		kulong								:11;
	} bit;
};

/* PHY_CONFIG_COMMON_3 (Offset 108h) */
union _IoPcieConfigCom3 {
	kulong		word;
	struct {
		kulong	txDeemG1				:6;
		kulong									:2;
		kulong	txDeemG23p5db	:6;
		kulong									:2;
		kulong	txDeemG26db		:6;
		kulong									:10;
	} bit;
};

/* PHY_CONFIG_COMMON_4 (Offset 10Ch) */
union _IoPcieConfigCom4 {
	kulong		word;
	struct {
		kulong	txSwingFull				:7;
		kulong									:1;
		kulong	txSwingLow				:7;
		kulong									:1;
		kulong	commonClocks		:1;
		kulong									:15;
	} bit;
};

/* PHY_CONFIG_COMMON_5 (Offset 110h) */
union _IoPcieConfigCom5 {
	kulong		word;
	struct {
		kulong	phyTx0TermOfs		:5;
		kulong									:3;
		kulong	phyTx1TermOfs		:5;
		kulong									:3;
		kulong	phyRx0Eq				:3;
		kulong									:5;
		kulong	phyRx1Eq				:3;
		kulong									:5;
	} bit;
};

/* PHY_CONFIG_COMMON_6 (Offset 114h) */
union _IoPcieConfigCom6 {
	kulong		word;
	struct {
		kulong	pipePortSel			:2;
		kulong								:2;
		kulong	phyTxVboostLv	:3;
		kulong								:9;
		kulong	phyLosLevel		:5;
		kulong								:3;
		kulong	phyLosBias			:3;
		kulong								:5;
	} bit;
};

/* CFG_MONITOR_1 (Offset 1D8h) */
union _IoPcieCfgMonitor1 {
	kulong		word;
	struct {
		kulong	cfgBusMstrEn		:1;
		kulong								:3;
		kulong	cfgMemSpaceEn	:1;
		kulong								:3;
		kulong	cfgMaxRdSize		:3;
		kulong								:1;
		kulong	cfgMaxPlSize		:3;
		kulong								:1;
		kulong	cfgRcb					:1;
		kulong								:1;
		kulong	cfgPwrCtrlerc		:1;
		kulong								:1;
		kulong	cfgPmNoSrst		:1;
		kulong								:3;
		kulong	cfgPwrInd			:2;
		kulong								:2;
		kulong	cfgAttenInd			:2;
		kulong								:2;
	} bit;
};

/* CFG_MONITOR_2 (Offset 1DCh) */
union _IoPcieCfgMonitor2 {
	kulong		word;
	struct {
		kulong	cfgPhyControl		:32;
	} bit;
};

/* CFG_MONITOR_3 (Offset 1E0h) */
union _IoPcieCfgMonitor3 {
	kulong		word;
	struct {
		kulong	cfgPbusNum			:8;
		kulong	cfgPbusDevNum	:5;
		kulong									:3;
		kulong	cfg2ndbusNum		:8;
		kulong	cfgSubbusNum		:8;
	} bit;
};

/* CFG_MONITOR_4 (Offset 1E4h) */
union _IoPcieCfgMonitor4 {
	kulong		word;
	struct {
		kulong	cfgLtrMaxLat		:32;
	} bit;
};

/* CFG_MONITOR_5 (Offset 1E8h) */
union _IoPcieCfgMonitor5 {
	kulong		word;
	struct {
		kulong	cfgLtrMEn				:1;
		kulong									:3;
		kulong	cfgNoSnoopEn		:1;
		kulong									:3;
		kulong	cfgRelaxOrder			:1;
		kulong									:7;
		kulong	cfg2ndReset			:1;
		kulong									:15;
	} bit;
};

/* DEBUG_MONITOR_1 (Offset 1ECh) */
union _IoPcieDebugMonitor1 {
	kulong		word;
	struct {
		kulong										:4;
		kulong	rtlhRfcUpd					:1;
		kulong										:3;
		kulong	brdgSlvXferPe				:1;
		kulong										:3;
		kulong	brdgDbiXferPe			:1;
		kulong										:3;
		kulong	edmaXferPe				:1;
		kulong										:3;
		kulong	radmXferPe					:1;
		kulong										:3;
		kulong	radmQNotEmpty		:1;
		kulong										:3;
		kulong	radmQoverflow			:1;
		kulong										:3;
	} bit;
};

/* DEBUG_MONITOR_2 (Offset 1F0h) */
union _IoPcieDebugMonitor2 {
	kulong		word;
	struct {
		kulong	rtlhRfcData		:32;
	} bit;
};

/* DEBUG_MONITOR_3 (Offset 1F4h) */
union _IoPcieDebugMonitor3 {
	kulong		word;
	struct {
		kulong	cxplDInfoEi		:16;
		kulong							:16;
	} bit;
};

/* DEBUG_MONITOR_4 (Offset 1F8h) */
struct _IoPcieDebugMonitor4 {
	kulong		cxplDInfoL;				/* 1F8 - 1FBh */
	kulong		cxplDInfoU;				/* 1FC - 1FFh */
};

/* MSG_MONITOR_1 (Offset 200h) */
union _IoPcieMsgMonitor1 {
	kulong		word;
	struct {
		kulong									:16;
		kulong	radmMsgReqId		:16;
	} bit;
};

/* MSG_MONITOR_3 (Offset 208h) */
struct _IoPcieMsgMonitor3 {
	kulong		radmMsgPayloadL;			/* 208 - 20Bh */
	kulong		radmMsgPayloadU;			/* 20C - 20Fh */
};

/* LINK_MONITOR (Offset 210h) */
union _IoPcieLinkMonitor {
	kulong		word;
	struct {
		kulong	smlhLinkUp			:1;
		kulong								:3;
		kulong	smlhReq_rstNot	:1;
		kulong								:27;
	} bit;
};

/* TIMEOUT_MONITOR_1 (Offset 218h) */
union _IoPcieToMonitor1 {
	kulong		word;
	struct {
		kulong	radmToFuncNu		:3;
		kulong									:1;
		kulong	radmToCplTc			:3;
		kulong									:1;
		kulong	radmToCplTag		:8;
		kulong	radmRoCplAttr		:2;
		kulong									:2;
		kulong	radmToCplLen		:12;
	} bit;
};

/* TIMEOUT_MONITOR_2 (Offset 21Ch) */
union _IoPcieToMonitor2 {
	kulong		word;
	struct {
		kulong	radmCplTimeout	:1;
		kulong									:31;
	} bit;
};

/* TIMEOUT_MONITOR_3 (Offset 220h) */
union _IoPcieToMonitor3 {
	kulong		word;
	struct {
		kulong	trgtToCplFnum	:3;
		kulong								:1;
		kulong	trgtToCplTc			:3;
		kulong								:1;
		kulong	trgtToLkupId		:8;
		kulong	trgtToCplAttr		:2;
		kulong								:2;
		kulong	trgtToCplLen		:12;
	} bit;
};

/* TIMEOUT_MONITOR_4 (Offset 224h) */
union _IoPcieToMonitor4 {
	kulong		word;
	struct {
		kulong	trgtCplTimeout	:1;
		kulong								:3;
		kulong	trgtLkupEmpty	:1;
		kulong								:3;
		kulong	trgtLkupId			:8;
		kulong								:16;
	} bit;
};

/* TRANSMIT_MONITOR (Offset 228h) */
union _IoPcieTransmitMonitor {
	kulong		word;
	struct {
		kulong	pmXtlhBlkTlp		:1;
		kulong								:31;
	} bit;
};

/* PIPE_MONITOR (Offset 22Ch) */
union _IoPciePipeMonitor {
	kulong		word;
	struct {
		kulong	cfgHwAutoSpD	:1;
		kulong								:3;
		kulong	macPhyRate		:1;
		kulong								:27;
	} bit;
};

/* PHY_MONITOR (Offset 230h) */
union _IoPciePhyMonitor {
	kulong		word;
	struct {
		kulong								:1;
		kulong	phy0MpllaState	:1;
		kulong	phy0MpllbState	:1;
		kulong								:7;
		kulong	phyRtuneAck		:1;
		kulong								:5;
		kulong	pipeRxEbufLoc	:9;
		kulong								:7;
	} bit;
};

/* CONFIG_MONITOR_BAR0_START (Offset 238h) */
struct _IoPcieMonitorBar0S {
	kulong		cfgBar0StartL;			/* 238 - 23Bh */
	kulong		cfgBar0StartU;			/* 23C - 23Fh */
};

/* CONFIG_MONITOR_BAR0_LIMIT (Offset 240h) */
struct _IoPcieMonitorBar0L {
	kulong		cfgBar0LimitL;			/* 240 - 243h */
	kulong		cfgBar0LimitU;			/* 244 - 247h */
};

/* CONFIG_MONITOR_BAR1_START (Offset 248h) */
union _IoPcieMonitorBar1S {
	kulong		word;
	struct {
		kulong	cfgBar1Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR1_LIMIT (Offset 24Ch) */
union _IoPcieMonitorBar1L {
	kulong		word;
	struct {
		kulong	cfgBar1Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR2_START (Offset 250h) */
struct _IoPcieMonitorBar2S {
	kulong		cfgBar2StartL;			/* 250 - 253h */
	kulong		cfgBar2StartU;			/* 254 - 257h */
};

/* CONFIG_MONITOR_BAR2_LIMIT (Offset 258h) */
struct _IoPcieMonitorBar2L {
	kulong		cfgBar2LimitL;			/* 258 - 25Bh */
	kulong		cfgBar2LimitU;			/* 25C - 25Fh */
};

/* CONFIG_MONITOR_BAR3_START (Offset 260h) */
union _IoPcieMonitorBar3S {
	kulong		word;
	struct {
		kulong	cfgBar3Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR3_LIMIT (Offset 264h) */
union _IoPcieMonitorBar3L {
	kulong		word;
	struct {
		kulong	cfgBar3Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR4_START (Offset 268h) */
struct _IoPcieMonitorBar4S {
	kulong		cfgBar4StartL;			/* 258 - 25Bh */
	kulong		cfgBar4StartU;			/* 25C - 25Fh */
};

/* CONFIG_MONITOR_BAR4_LIMIT (Offset 270h) */
struct _IoPcieMonitorBar4L {
	kulong		cfgBar4LimitL;			/* 250 - 253h */
	kulong		cfgBar4LimitU;			/* 254 - 257h */
};

/* CONFIG_MONITOR_BAR5_START (Offset 278h) */
union _IoPcieMonitorBar5S {
	kulong		word;
	struct {
		kulong	cfgBar5Start		:32;
	} bit;
};

/* CONFIG_MONITOR_BAR5_LIMIT (Offset 27Ch) */
union _IoPcieMonitorBar5L {
	kulong		word;
	struct {
		kulong	cfgBar5Limit		:32;
	} bit;
};

/* CONFIG_MONITOR_EXP_ROM_START (Offset 280h) */
union _IoPcieMonitorEromS {
	kulong		word;
	struct {
		kulong	cfgEromStart		:32;
	} bit;
};

/* CONFIG_MONITOR_EEXP_ROM_LIMIT (Offset 284h) */
union _IoPcieMonitorEromL {
	kulong		word;
	struct {
		kulong	cfgEromLimit		:32;
	} bit;
};

/* MACRO REGISTER (Offset 000h - FFFh) */
struct _IoPcie {
	IoPcieCoreControl			coreControl;				/* +000 - 003h */
	IoPcieAxiClkStop			axiClkStop;				/* +004 - 007h */
	IoPcieClockControl			clockControl;				/* +008 - 00Bh */
	IoPcieResetControl1		resetControl1;			/* +00C - 00Fh */
	IoPcieResetControl2		resetControl2;			/* +010 - 013h */
	IoPcieResetSelect1			resetSelect1;				/* +014 - 017h */
	IoPcieResetSelect2			resetSelect2;				/* +018 - 01Bh */
	IoPcieMsiRequest1			msiRequest1;				/* +01C - 01Fh */
	IoPcieMsiRequest2			msiRequest2;				/* +020 - 023h */
	IoPcieIntControl1			intControl1;				/* +024 - 027h */
	IoPcieIntControl2			intControl2;				/* +028 - 02Bh */
	IoPcieIntControl3			intControl3;				/* +02C - 02Fh */
	IoPcieEmControl			emControl;					/* +030 - 033h */
	IoPcieEmSelect				emSelect;					/* +034 - 037h */
	IoPcieEmMonitor			emMonitor;					/* +038 - 03Bh */
	IoPciePmUnlockReq		pmUnlockReq;				/* +03C - 03Fh */
	IoPcieLtrMsg					ltrMsg;					/* +040 - 043h */
	IoPcieLtrMonitor1			ltrMonitor1;				/* +044 - 047h */
	IoPcieLtrMonitor2			ltrMonitor2;				/* +048 - 04Bh */
	IoPciePmControl1			pmControl1;				/* +04C - 04Fh */
	IoPciePmControl2			pmControl2;				/* +050 - 053h */
	IoPciePmSelect1			pmSelect1;				/* +054 - 057h */
	IoPciePmMonitor1			pmMonitor1;				/* +058 - 05Bh */
	IoPciePmMonitor2			pmMonitor2;				/* +05C - 05Fh */
	kuchar								dmy0600ff[0x100-0x060];	/* +060 - 0FFh */
	IoPcieConfigCom1			phyConfigCom1;			/* +100 - 103h */
	IoPcieConfigCom2			phyConfigCom2;			/* +104 - 107h */
	IoPcieConfigCom3			phyConfigCom3;			/* +108 - 10Bh */
	IoPcieConfigCom4			phyConfigCom4;			/* +10C - 10Fh */
	IoPcieConfigCom5			phyConfigCom5;			/* +110 - 113h */
	IoPcieConfigCom6			phyConfigCom6;			/* +114 - 117h */
	kuchar								dmy1181d7[0x1D8-0x118];	/* +118 - 1D7h */
	IoPcieCfgMonitor1			cfgMonitor1;				/* +1D8 - 1DBh */
	IoPcieCfgMonitor2			cfgMonitor2;				/* +1DC - 1DFh */
	IoPcieCfgMonitor3			cfgMonitor3;				/* +1E0 - 1E3h */
	IoPcieCfgMonitor4			cfgMonitor4;				/* +1E4 - 1E7h */
	IoPcieCfgMonitor5			cfgMonitor5;				/* +1E8 - 1EBh */
	IoPcieDebugMonitor1	debugMonitor1;			/* +1EC - 1EFh */
	IoPcieDebugMonitor2	debugMonitor2;			/* +1F0 - 1F3h */
	IoPcieDebugMonitor3	debugMonitor3;			/* +1F4 - 1F7h */
	IoPcieDebugMonitor4	debugMonitor4;			/* +1F8 - 1FFh */
	IoPcieMsgMonitor1		msgMonitor1;				/* +200 - 203h */
	kuchar								dmy204207[0x208-0x204];	/* +204 - 207h */
	IoPcieMsgMonitor3		msgMonitor3;				/* +208 - 20Fh */
	IoPcieLinkMonitor			linkMonitor;				/* +210 - 213h */
	kuchar								dmy214217[0x218-0x214];	/* +214 - 217h */
	IoPcieToMonitor1			toMonitor1;				/* +218 - 21Bh */
	IoPcieToMonitor2			toMonitor2;				/* +21C - 21Fh */
	IoPcieToMonitor3			toMonitor3;				/* +220 - 223h */
	IoPcieToMonitor4			toMonitor4;				/* +224 - 227h */
	IoPcieTransmitMonitor	transmitMonitor;			/* +228 - 22Bh */
	IoPciePipeMonitor			pipeMonitor;				/* +22C - 22Fh */
	IoPciePhyMonitor			phyMonitor;				/* +230 - 233h */
	kuchar								dmy234237[0x238-0x234];	/* +234 - 237h */
	IoPcieMonitorBar0S		monitorBar0S;				/* +238 - 23Fh */
    IoPcieMonitorBar0L		monitorBar0L;				/* +240 - 247h */
	IoPcieMonitorBar1S		monitorBar1S;				/* +248 - 24Bh */
	IoPcieMonitorBar1L		monitorBar1L;				/* +24C - 249h */
	IoPcieMonitorBar2S		monitorBar2S;				/* +250 - 257h */
	IoPcieMonitorBar2L		monitorBar2L;				/* +258 - 25Fh */
	IoPcieMonitorBar3S		monitorBar3S;				/* +260 - 263h */
	IoPcieMonitorBar3L		monitorBar3L;				/* +264 - 267h */
	IoPcieMonitorBar4S		monitorBar4S;				/* +268 - 26Fh */
	IoPcieMonitorBar4L		monitorBar4L;				/* +270 - 277h */
	IoPcieMonitorBar5S		monitorBar5S;				/* +278 - 27Bh */
	IoPcieMonitorBar5L		monitorBar5L;				/* +27C - 27Fh */
	IoPcieMonitorEromS		monitorEromS;				/* +280 - 283h */
	IoPcieMonitorEromL		monitorEromL;				/* +284 - 287h */
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
