/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#ifndef __F_MIPIDSI11TX_LP_H__
#define __F_MIPIDSI11TX_LP_H__


#include <stdio.h>
#include <glib-object.h>


typedef union 				_IoPwrUp IoPwrUp;
typedef union 				_IoClkmgrCfg IoClkmgrCfg;
typedef union 				_IoDpiVcid IoDpiVcid;
typedef union 				_IoDpiColorCoding IoDpiColorCoding;
typedef union 				_IoDpiCfgPol IoDpiCfgPol;
typedef union 				_IoDpiLpCmdTim IoDpiLpCmdTim;
typedef union 				_IoPckhdlCfg IoPckhdlCfg;
typedef union 				_IoModeCfg IoModeCfg;
typedef union 				_IoVidModeCfg IoVidModeCfg;
typedef union 				_IoVidPktSize IoVidPktSize;
typedef union 				_IoVidNumChunks IoVidNumChunks;
typedef union 				_IoVidNullSize IoVidNullSize;
typedef union 				_IoVidHsaTime IoVidHsaTime;
typedef union 				_IoVidHbpTime IoVidHbpTime;
typedef union 				_IoVidHlineTime IoVidHlineTime;
typedef union 				_IoVidVsaLines IoVidVsaLines;
typedef union 				_IoVidVbpLines IoVidVbpLines;
typedef union 				_IoVidVfpLines IoVidVfpLines;
typedef union 				_IoVidVactiveLines IoVidVactiveLines;
typedef union 				_IoCmdModeCfg IoCmdModeCfg;
typedef union 				_IoGenHdr IoGenHdr;
typedef union 				_IoGenPldData IoGenPldData;
typedef union 				_IoCmdPktStatus IoCmdPktStatus;
typedef union 				_IoToCntCfg IoToCntCfg;
typedef union 				_IoHsWrToCnt IoHsWrToCnt;
typedef union 				_IoLpWrToCnt IoLpWrToCnt;
typedef union 				_IoSdf3d IoSdf3d;
typedef union 				_IoLpclkCtrl IoLpclkCtrl;
typedef union 				_IoPhyTmrLpclkCfg IoPhyTmrLpclkCfg;
typedef union 				_IoPhyTmrCfg IoPhyTmrCfg;
typedef union 				_IoPhyRstz IoPhyRstz;
typedef union 				_IoPhyIfCfg IoPhyIfCfg;
typedef union 				_IoPhyUlpsCtrl IoPhyUlpsCtrl;
typedef union 				_IoPhyTxTriggers IoPhyTxTriggers;
typedef union 				_IoPhyStatus IoPhyStatus;
typedef union 				_IoIntSt1 IoIntSt1;
typedef union 				_IoIntMsk1 IoIntMsk1;
typedef union 				_IoVidShadowCtrl IoVidShadowCtrl;
typedef union 				_IoVidModeCfgAct IoVidModeCfgAct;
typedef union 				_IoPhySetup IoPhySetup;
typedef union 				_IoPhyTclkost IoPhyTclkost;
typedef struct 				_IoFMipidsi11txLp IoFMipidsi11txLp;

/*  structure of PWR_UP    (2800_C004h)    */
union _IoPwrUp{
    gulong       word;
    struct {
        gulong   shutdownz   :1;
        gulong               :31;
    }bit;
};

/*  structure of CLKMGR_CFG    (2800_C008h)    */
union _IoClkmgrCfg{
    gulong       word;
    struct {
        gulong   txEscClkDivision :8;
        gulong   toClkDivision     :8;
        gulong                       :16;
    }bit;
};

/*  structure of DPI_VCID    (2800_C00Ch)    */
union _IoDpiVcid{
    gulong       word;
    struct {
        gulong   dpiVcid    :2;
        gulong               :30;
    }bit;
};

/*  structure of DPI_COLOR_CODING    (2800_C010h)    */
union _IoDpiColorCoding{
    gulong       word;
    struct {
        gulong   dpiColorCoding    :4;
        gulong                       :4;
        gulong   loosely18En        :1;
        gulong                       :23;
    }bit;
};

/*  structure of DPI_CFG_POL (2800_C014h)    */
union _IoDpiCfgPol{
    gulong       word;
    struct {
        gulong   dataenActiveLow   :1;
        gulong   vsyncActiveLow    :1;
        gulong   hsyncActiveLow    :1;
        gulong   shutdActiveLow    :1;
        gulong   colormAcviteLow   :1;
        gulong                       :27;
    }bit;
};

/*  structure of DPI_LP_CMD_TIM (2800_C018h)    */
union _IoDpiLpCmdTim{
    gulong       word;
    struct {
        gulong   invactLpcmdTime   :8;
        gulong                       :8;
        gulong   outvactLpcmdTime  :8;
        gulong                       :8;
    }bit;
};

/*  structure of PCKHDL_CFG    (2800_C02Ch)    */
union _IoPckhdlCfg{
    gulong       word;
    struct {
        gulong   eotpTxEn  :1;
        gulong               :31;
    }bit;
};

/*  structure of MODE_CFG    (2800_C034h)    */
union _IoModeCfg{
    gulong       word;
    struct {
        gulong   cmdVideoMode  :1;
        gulong                   :31;
    }bit;
};

/*  structure of VID_MODE_CFG  (2800_C038h)    */
union _IoVidModeCfg{
    gulong       word;
    struct {
        gulong   vidModeType   :2;
        gulong                   :6;
        gulong   lpVsaEn       :1;
        gulong   lpVbpEn       :1;
        gulong   lpVfpEn       :1;
        gulong   lpVactEn      :1;
        gulong   lpHbpEn       :1;
        gulong   lpHfpEn       :1;
        gulong                   :1;
        gulong   lpCmdEn       :1;
        gulong   vpgEn          :1;
        gulong                   :3;
        gulong   vpgMode        :1;
        gulong                   :3;
        gulong   vpgOrientation :1;
        gulong                   :7;
    }bit;
};

/*  structure of VID_PKT_SIZE   (2800_C03Ch)    */
union _IoVidPktSize{
    gulong       word;
    struct {
        gulong   vidPktSize    :14;
        gulong                   :18;
    }bit;
};

/*  structure of VID_NUM_CHUNKS    (2800_C040h)    */
union _IoVidNumChunks{
    gulong       word;
    struct {
        gulong   vidNumChunks  :13;
        gulong                   :19;
    }bit;
};

/*  structure of VID_NULL_SIZE    (2800_C044h)    */
union _IoVidNullSize{
    gulong       word;
    struct {
        gulong   vidNullSize   :13;
        gulong                   :19;
    }bit;
};

/*  structure of VID_HSA_TIME   (2800_C048h)    */
union _IoVidHsaTime{
    gulong       word;
    struct {
        gulong   vidHsaTime    :12;
        gulong                   :20;
    }bit;
};

/*  structure of VID_HBP_TIME   (2800_C04Ch)    */
union _IoVidHbpTime{
    gulong       word;
    struct {
        gulong   vidHbpTime    :12;
        gulong                   :20;
    }bit;
};

/*  structure of VID_HLINE_TIME  (2800_C050h)    */
union _IoVidHlineTime{
    gulong       word;
    struct {
        gulong   vidHlineTime  :15;
        gulong                   :17;
    }bit;
};

/*  structure of VID_VSA_LINES  (2800_C054h)    */
union _IoVidVsaLines{
    gulong       word;
    struct {
        gulong   vsaLines   :10;
        gulong               :22;
    }bit;
};

/*  structure of VID_VBP_LINES  (2800_C058h)    */
union _IoVidVbpLines{
    gulong       word;
    struct {
        gulong   vbpLines   :10;
        gulong               :22;
    }bit;
};

/*  structure of VID_VFP_LINES  (2800_C05Ch)    */
union _IoVidVfpLines{
    gulong       word;
    struct {
        gulong   vfpLines   :10;
        gulong               :22;
    }bit;
};

/*  structure of VID_VACTIVE_LINES  (2800_C060h)    */
union _IoVidVactiveLines{
    gulong       word;
    struct {
        gulong   vActiveLines  :14;
        gulong                   :18;
    }bit;
};

/*  structure of CMD_MODE_CFG  (2800_C068h)    */
union _IoCmdModeCfg{
    gulong       word;
    struct {
        gulong                   :8;
        gulong   genSw0pTx    :1;
        gulong   genSw1pTx    :1;
        gulong   genSw2pTx    :1;
        gulong                   :3;
        gulong   genLwTx       :1;
        gulong                   :1;
        gulong   dcsSw0pTx    :1;
        gulong   dcsSw1pTx    :1;
        gulong                   :1;
        gulong   dcsLwTx       :1;
        gulong                   :12;
    }bit;
};

/*  structure of GEN_HDR  (2800_C06Ch)    */
union _IoGenHdr{
    gulong       word;
    struct {
        gulong   genDt          :6;
        gulong   genVc          :2;
        gulong   genWcLsbyte   :8;
        gulong   genWcMsbyte   :8;
        gulong                   :8;
    }bit;
};

/*  structure of GEN_PLD_DATA  (2800_C070h)    */
union _IoGenPldData{
    gulong       word;
    struct {
        gulong   genPldB1  :8;
        gulong   genPldB2  :8;
        gulong   genPldB3  :8;
        gulong   genPldB4  :8;
    }bit;
};

/*  structure of CMD_PKT_STATUS  (2800_C074h)    */
union _IoCmdPktStatus{
    gulong       word;
    struct {
        gulong   genCmdEmpty   :1;
        gulong   genCmdFull    :1;
        gulong   genPldWEmpty :1;
        gulong   genPldWFull  :1;
        gulong                   :28;
    }bit;
};

/*  structure of TO_CNT_CFG  (2800_C078h)    */
union _IoToCntCfg{
    gulong       word;
    struct {
        gulong               :16;
        gulong   hstxToCnt :16;
    }bit;
};

/*  structure of HS_WR_TO_CNT  (2800_C084h)    */
union _IoHsWrToCnt{
    gulong       word;
    struct {
        gulong   hsWrToCnt    :16;
        gulong                   :16;
    }bit;
};

/*  structure of LP_WR_TO_CNT  (2800_C088h)    */
union _IoLpWrToCnt{
    gulong       word;
    struct {
        gulong   lpWrToCnt    :16;
        gulong                   :16;
    }bit;
};

/*  structure of SDF_3D  (2800_C090h)    */
union _IoSdf3d{
    gulong       word;
    struct {
        gulong   mode3d         :2;
        gulong   format3d       :2;
        gulong   secondVsync    :1;
        gulong   rightFirst     :1;
        gulong                   :10;
        gulong   send3dCfg     :1;
        gulong                   :15;
    }bit;
};

/*  structure of LPCLK_CTRL  (2800_C094h)    */
union _IoLpclkCtrl{
    gulong       word;
    struct {
        gulong   phyTxrequestclkhs  :1;
        gulong   autoClklaneCtrl   :1;
        gulong                       :30;
    }bit;
};

/*  structure of PHY_TMR_LPCLK_CFG  (2800_C098h)    */
union _IoPhyTmrLpclkCfg{
    gulong       word;
    struct {
        gulong   phyClkhs2lpTime   :10;
        gulong                       :6;
        gulong   phyClklp2hsTime   :10;
        gulong                       :6;
    }bit;
};

/*  structure of PHY_TMR_CFG  (2800_C09Ch)    */
union _IoPhyTmrCfg{
    gulong       word;
    struct {
        gulong                   :16;
        gulong   phyLp2hsTime  :8;
        gulong   phyHs2lpTime  :8;
    }bit;
};

/*  structure of PHY_RSTZ  (2800_C0A0h)    */
union _IoPhyRstz{
    gulong       word;
    struct {
        gulong   phyShutdownz   :1;
        gulong                   :31;
    }bit;
};

/*  structure of PHY_IF_CFG  (2800_C0A4h)    */
union _IoPhyIfCfg{
    gulong       word;
    struct {
        gulong   nLanes     :2;
        gulong               :30;
    }bit;
};

/*  structure of PHY_ULPS_CTRL  (2800_C0A8h)    */
union _IoPhyUlpsCtrl{
    gulong       word;
    struct {
        gulong   phyTxrequlpsclk    :1;
        gulong   phyTxexitulpsclk   :1;
        gulong   phyTxrequlpslan    :1;
        gulong   phyTxexitulpslan   :1;
        gulong                       :28;
    }bit;
};

/*  structure of PHY_TX_TRIGGERS  (2800_C0ACh)    */
union _IoPhyTxTriggers{
    gulong       word;
    struct {
        gulong   phyTxTriggers     :4;
        gulong                       :28;
    }bit;
};

/*  structure of PHY_STATUS  (2800_C0B0h)    */
union _IoPhyStatus{
    gulong       word;
    struct {
        gulong                           :1;
        gulong   phyDirection           :1;
        gulong   phyStopstateclklane    :1;
        gulong   phyUlpsactivenotclk    :1;
        gulong   phyStopstate0lane      :1;
        gulong   phyUlpsactivenot0lane  :1;
        gulong                           :1;
        gulong   phyStopstate1lane      :1;
        gulong   phyUlpsactivenot1lane  :1;
        gulong   phyStopstate2lane      :1;
        gulong   phyUlpsactivenot2lane  :1;
        gulong   phyStopstate3lane      :1;
        gulong   phyUlpsactivenot3lane  :1;
        gulong                           :19;
    }bit;
};

/*  structure of INT_ST1  (2800_C0C0h)    */
union _IoIntSt1{
    gulong       word;
    struct {
        gulong   toHsTx            :1;
        gulong                       :6;
        gulong   dpiPldWrErr      :1;
        gulong   genCmdWrErr      :1;
        gulong   genPldWrErr      :1;
        gulong   genPldSendErr    :1;
        gulong                       :21;
    }bit;
};

/*  structure of INT_MSK1  (2800_C0C8h)    */
union _IoIntMsk1{
    gulong       word;
    struct {
        gulong   toHsTx            :1;
        gulong                       :6;
        gulong   dpiPldWrErr      :1;
        gulong   genCmdWrErr      :1;
        gulong   genPldWrErr      :1;
        gulong   genPldSendErr    :1;
        gulong                       :21;
    }bit;
};

/*  structure of VID_SHADOW_CTRL  (2800_C100h)    */
union _IoVidShadowCtrl{
    gulong       word;
    struct {
        gulong   vidShadowEn       :1;
        gulong                       :7;
        gulong   vidShadowReq      :1;
        gulong                       :7;
        gulong   vidShadowPinReq  :1;
        gulong                       :15;
    }bit;
};

/*  structure of VID_MODE_CFG_ACT  (2800_C038h)    */
union _IoVidModeCfgAct{
    gulong       word;
    struct {
        gulong   vidModeType   :2;
        gulong                   :6;
        gulong   lpVsaEn       :1;
        gulong   lpVbpEn       :1;
        gulong   lpVfpEn       :1;
        gulong   lpVactEn      :1;
        gulong   lpHbpEn       :1;
        gulong   lpHfpEn       :1;
        gulong                   :1;
        gulong   lpCmdEn       :1;
        gulong                   :16;
    }bit;
};

/*  structure of PHY_SETUP_CL (2800_C400h) / PHY_SETUP_DL (2800_C404h)    */
union _IoPhySetup{
    gulong       word;
    struct {
        gulong   sapTlpx    :8;
        gulong   sapHs0     :8;
        gulong   sapTrail   :8;
        gulong   sapPre     :8;
    }bit;
};

/*  structure of PHY_TCLKPOST  (2800_C408h)    */
union _IoPhyTclkost{
    gulong       word;
    struct {
        gulong   tclkPost   :6;
        gulong               :26;
    }bit;
};

/* Define i/o mapping */
struct _IoFMipidsi11txLp{
    /* F_MIPIDSI11TX_LP */
	/* 2800_(C000 - C003h) */
    gulong					version;
    /* 2800_(C004 - C007h) */
    IoPwrUp					pwrUp;
    /* 2800_(C008 - C00Bh) */
    IoClkmgrCfg				clkmgrCfg;
    /* 2800_(C00C - C00Fh) */
    IoDpiVcid				dpiVcid;
    /* 2800_(C010 - C013h) */
    IoDpiColorCoding		dpiColorCoding;
    /* 2800_(C014 - C017h) */
    IoDpiCfgPol			dpiCfgPol;
    /* 2800_(C018 - C01Bh) */
    IoDpiLpCmdTim			dpiLpCmdTim;
    /* 2800_(C01C - C02Bh) */
    guchar dmyC01cC02b[0xC02C-0xC01C];
    /* 2800_(C02C - C02Fh) */
    IoPckhdlCfg				pckhdlCfg;
    /* 2800_(C030 - C033h) */
    guchar dmyC030C033[0xC034-0xC030];
    /* 2800_(C034 - C037h) */
    IoModeCfg				modeCfg;
    /* 2800_(C038 - C03Bh) */
    IoVidModeCfg			vidModeCfg;
    /* 2800_(C03C - C03Fh) */
    IoVidPktSize			vidPktSize;
    /* 2800_(C040 - C043h) */
    IoVidNumChunks			vidNumChunks;
    /* 2800_(C044 - C047h) */
    IoVidNullSize			vidNullSize;
    /* 2800_(C048 - C04Bh) */
    IoVidHsaTime			vidHsaTime;
    /* 2800_(C04C - C04Fh) */
    IoVidHbpTime			vidHbpTime;
    /* 2800_(C050 - C053h) */
    IoVidHlineTime			vidHlineTime;
    /* 2800_(C054 - C057h) */
    IoVidVsaLines			vidVsaLines;
    /* 2800_(C058 - C05Bh) */
    IoVidVbpLines			vidVbpLines;
    /* 2800_(C05C - C05Fh) */
    IoVidVfpLines			vidVfpLines;
    /* 2800_(C060 - C063h) */
    IoVidVactiveLines		vidVactiveLines;
    /* 2800_(C064 - C067h) */
    guchar dmyC064C067[0xC068-0xC064];
    /* 2800_(C068 - C06Bh) */
    IoCmdModeCfg			cmdModeCfg;
    /* 2800_(C06C - C06Fh) */
    IoGenHdr				genHdr;
    /* 2800_(C070 - C073h) */
    IoGenPldData			genPldData;
    /* 2800_(C074 - C077h) */
    IoCmdPktStatus			cmdPktStatus;
    /* 2800_(C078 - C07Bh) */
    IoToCntCfg				toCntCfg;
    /* 2800_(C07C - C083h) */
    guchar dmyC07cC083[0xC084-0xC07C];
    /* 2800_(C084 - C087h) */
    IoHsWrToCnt			hsWrToCnt;
    /* 2800_(C088 - C08Bh) */
    IoLpWrToCnt			lpWrToCnt;
    /* 2800_(C08C - C08Fh) */
    guchar dmyC08cC08f[0xC090-0xC08C];
    /* 2800_(C090 - C093h) */
    IoSdf3d					sdf3d;
    /* 2800_(C094 - C097h) */
    IoLpclkCtrl				lpclkCtrl;
    /* 2800_(C098 - C09Bh) */
    IoPhyTmrLpclkCfg		phyTmrLpclkCfg;
    /* 2800_(C09C - C09Fh) */
    IoPhyTmrCfg			phyTmrCfg;
    /* 2800_(C0A0 - C0A3h) */
    IoPhyRstz				phyRstz;
    /* 2800_(C0A4 - C0A7h) */
    IoPhyIfCfg				phyIfCfg;
    /* 2800_(C0A8 - C0ABh) */
    IoPhyUlpsCtrl			phyUlpsCtrl;
    /* 2800_(C0AC - C0AFh) */
    IoPhyTxTriggers		phyTxTriggers;
    /* 2800_(C0B0 - C0B3h) */
    IoPhyStatus				phyStatus;
    /* 2800_(C0B4 - C0BFh) */
    guchar dmyC0b4C0bf[0xC0C0-0xC0B4];
    /* 2800_(C0C0 - 0C3Ch) */
    IoIntSt1				intSt1;
    /* 2800_(C0C4 - C0C7h) */
    guchar dmyC0c4C0c7[0xC0C8-0xC0C4];
    /* 2800_(C0C8 - C0CBh) */
    IoIntMsk1				intMsk1;
    /* 2800_(C0CC - C0FFh) */
    guchar dmyC0ccC0ff[0xC100-0xC0CC];
    /* 2800_(C100 - C103h) */
    IoVidShadowCtrl		vidShadowCtrl;
    /* 2800_(C104 - C10Bh) */
    guchar dmyC104C10b[0xC10C-0xC104];
    /* 2800_(C10C - C10Fh) */
    IoDpiVcid				dpiVcidAct;
    /* 2800_(C110 - C113h) */
    IoDpiColorCoding		dpiColorCodingAct;
    /* 2800_(C114 - C117h) */
    guchar dmyC114C117[0xC118-0xC114];
    /* 2800_(C118 - C11Bh) */
    IoDpiLpCmdTim			dpiLpCmdTimAct;
    /* 2800_(C11C - C137h) */
    guchar dmyC11cC137[0xC138-0xC11C];
    /* 2800_(C138 - C13Bh) */
    IoVidModeCfgAct		vidModeCfgAct;
    /* 2800_(C13C - C13Fh) */
    IoVidPktSize			vidPktSizeAct;
    /* 2800_(C140 - C143h) */
    IoVidNumChunks			vidNumChunksAct;
    /* 2800_(C144 - C147h) */
    IoVidNullSize			vidNullSizeAct;
    /* 2800_(C148 - C14Bh) */
    IoVidHsaTime			vidHsaTimeAct;
    /* 2800_(C14C - C14Fh) */
    IoVidHbpTime			vidHbpTimeAct;
    /* 2800_(C150 - C153h) */
    IoVidHlineTime			vidHlineTimeAct;
    /* 2800_(C154 - C157h) */
    IoVidVsaLines			vidVsaLinesAct;
    /* 2800_(C158 - C15Bh) */
    IoVidVbpLines			vidVbpLinesAct;
    /* 2800_(C15C - C15Fh) */
    IoVidVfpLines			vidVfpLinesAct;
    /* 2800_(C160 - C163h) */
    IoVidVactiveLines		vidVactiveLinesAct;
    /* 2800_(C164 - C18Fh) */
    guchar dmyC164C18f[0xC190-0xC164];
    /* 2800_(C190 - C193h) */
    IoSdf3d					sdf3dAct;
    /* 2800_(C194 - C3FFh) */
    guchar dmyC194C3ff[0xC400-0xC194];
    /* 2800_(C400 - C403h) */
    IoPhySetup				phySetupCl;
    /* 2800_(C404 - C407h) */
    IoPhySetup				phySetupDl;
    /* 2800_(C408 - C40Bh) */
    IoPhyTclkost			phyTclkpost;
    /* 2800_(C40C - CFFFCh) */
    guchar dmyC40cCfff[0xD000-0xC40C];
};


#endif/*__F_MIPIDSI11TX_LP_H__*/
