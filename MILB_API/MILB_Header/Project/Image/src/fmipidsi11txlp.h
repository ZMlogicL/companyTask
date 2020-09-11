/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-10
*@author              :申雨
*@brief               :sns 索喜rtos
*@rely                :klib
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


#include <klib.h>


#define F_TYPE_MIPIDSI11TX_LP				(f_mipidsi11tx_lp_get_type())
#define F_MIPIDSI11TX_LP(obj)				(K_TYPE_CHECK_INSTANCE_CAST((obj), FMipidsi11txLp))
#define F_IS_MIPIDSI11TX_LP(obj)			(K_TYPE_CHECK_INSTANCE_TYPE((obj), F_TYPE_MIPIDSI11TX_LP))


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
typedef struct 				_FMipidsi11txLp FMipidsi11txLp;
typedef struct 				_FMipidsi11txLpPrivate	FMipidsi11txLpPrivate;

/*  structure of PWR_UP    (2800_C004h)    */
union _IoPwrUp{
    kulong       word;
    struct {
        kulong   shutdownz   :1;
        kulong               :31;
    }bit;
};

/*  structure of CLKMGR_CFG    (2800_C008h)    */
union _IoClkmgrCfg{
    kulong       word;
    struct {
        kulong   txEscClkDivision :8;
        kulong   toClkDivision     :8;
        kulong                       :16;
    }bit;
};

/*  structure of DPI_VCID    (2800_C00Ch)    */
union _IoDpiVcid{
    kulong       word;
    struct {
        kulong   dpiVcid    :2;
        kulong               :30;
    }bit;
};

/*  structure of DPI_COLOR_CODING    (2800_C010h)    */
union _IoDpiColorCoding{
    kulong       word;
    struct {
        kulong   dpiColorCoding    :4;
        kulong                       :4;
        kulong   loosely18En        :1;
        kulong                       :23;
    }bit;
};

/*  structure of DPI_CFG_POL (2800_C014h)    */
union _IoDpiCfgPol{
    kulong       word;
    struct {
        kulong   dataenActiveLow   :1;
        kulong   vsyncActiveLow    :1;
        kulong   hsyncActiveLow    :1;
        kulong   shutdActiveLow    :1;
        kulong   colormAcviteLow   :1;
        kulong                       :27;
    }bit;
};

/*  structure of DPI_LP_CMD_TIM (2800_C018h)    */
union _IoDpiLpCmdTim{
    kulong       word;
    struct {
        kulong   invactLpcmdTime   :8;
        kulong                       :8;
        kulong   outvactLpcmdTime  :8;
        kulong                       :8;
    }bit;
};

/*  structure of PCKHDL_CFG    (2800_C02Ch)    */
union _IoPckhdlCfg{
    kulong       word;
    struct {
        kulong   eotpTxEn  :1;
        kulong               :31;
    }bit;
};

/*  structure of MODE_CFG    (2800_C034h)    */
union _IoModeCfg{
    kulong       word;
    struct {
        kulong   cmdVideoMode  :1;
        kulong                   :31;
    }bit;
};

/*  structure of VID_MODE_CFG  (2800_C038h)    */
union _IoVidModeCfg{
    kulong       word;
    struct {
        kulong   vidModeType   :2;
        kulong                   :6;
        kulong   lpVsaEn       :1;
        kulong   lpVbpEn       :1;
        kulong   lpVfpEn       :1;
        kulong   lpVactEn      :1;
        kulong   lpHbpEn       :1;
        kulong   lpHfpEn       :1;
        kulong                   :1;
        kulong   lpCmdEn       :1;
        kulong   vpgEn          :1;
        kulong                   :3;
        kulong   vpgMode        :1;
        kulong                   :3;
        kulong   vpgOrientation :1;
        kulong                   :7;
    }bit;
};

/*  structure of VID_PKT_SIZE   (2800_C03Ch)    */
union _IoVidPktSize{
    kulong       word;
    struct {
        kulong   vidPktSize    :14;
        kulong                   :18;
    }bit;
};

/*  structure of VID_NUM_CHUNKS    (2800_C040h)    */
union _IoVidNumChunks{
    kulong       word;
    struct {
        kulong   vidNumChunks  :13;
        kulong                   :19;
    }bit;
};

/*  structure of VID_NULL_SIZE    (2800_C044h)    */
union _IoVidNullSize{
    kulong       word;
    struct {
        kulong   vidNullSize   :13;
        kulong                   :19;
    }bit;
};

/*  structure of VID_HSA_TIME   (2800_C048h)    */
union _IoVidHsaTime{
    kulong       word;
    struct {
        kulong   vidHsaTime    :12;
        kulong                   :20;
    }bit;
};

/*  structure of VID_HBP_TIME   (2800_C04Ch)    */
union _IoVidHbpTime{
    kulong       word;
    struct {
        kulong   vidHbpTime    :12;
        kulong                   :20;
    }bit;
};

/*  structure of VID_HLINE_TIME  (2800_C050h)    */
union _IoVidHlineTime{
    kulong       word;
    struct {
        kulong   vidHlineTime  :15;
        kulong                   :17;
    }bit;
};

/*  structure of VID_VSA_LINES  (2800_C054h)    */
union _IoVidVsaLines{
    kulong       word;
    struct {
        kulong   vsaLines   :10;
        kulong               :22;
    }bit;
};

/*  structure of VID_VBP_LINES  (2800_C058h)    */
union _IoVidVbpLines{
    kulong       word;
    struct {
        kulong   vbpLines   :10;
        kulong               :22;
    }bit;
};

/*  structure of VID_VFP_LINES  (2800_C05Ch)    */
union _IoVidVfpLines{
    kulong       word;
    struct {
        kulong   vfpLines   :10;
        kulong               :22;
    }bit;
};

/*  structure of VID_VACTIVE_LINES  (2800_C060h)    */
union _IoVidVactiveLines{
    kulong       word;
    struct {
        kulong   vActiveLines  :14;
        kulong                   :18;
    }bit;
};

/*  structure of CMD_MODE_CFG  (2800_C068h)    */
union _IoCmdModeCfg{
    kulong       word;
    struct {
        kulong                   :8;
        kulong   genSw0pTx    :1;
        kulong   genSw1pTx    :1;
        kulong   genSw2pTx    :1;
        kulong                   :3;
        kulong   genLwTx       :1;
        kulong                   :1;
        kulong   dcsSw0pTx    :1;
        kulong   dcsSw1pTx    :1;
        kulong                   :1;
        kulong   dcsLwTx       :1;
        kulong                   :12;
    }bit;
};

/*  structure of GEN_HDR  (2800_C06Ch)    */
union _IoGenHdr{
    kulong       word;
    struct {
        kulong   genDt          :6;
        kulong   genVc          :2;
        kulong   genWcLsbyte   :8;
        kulong   genWcMsbyte   :8;
        kulong                   :8;
    }bit;
};

/*  structure of GEN_PLD_DATA  (2800_C070h)    */
union _IoGenPldData{
    kulong       word;
    struct {
        kulong   genPldB1  :8;
        kulong   genPldB2  :8;
        kulong   genPldB3  :8;
        kulong   genPldB4  :8;
    }bit;
};

/*  structure of CMD_PKT_STATUS  (2800_C074h)    */
union _IoCmdPktStatus{
    kulong       word;
    struct {
        kulong   genCmdEmpty   :1;
        kulong   genCmdFull    :1;
        kulong   genPldWEmpty :1;
        kulong   genPldWFull  :1;
        kulong                   :28;
    }bit;
};

/*  structure of TO_CNT_CFG  (2800_C078h)    */
union _IoToCntCfg{
    kulong       word;
    struct {
        kulong               :16;
        kulong   hstxToCnt :16;
    }bit;
};

/*  structure of HS_WR_TO_CNT  (2800_C084h)    */
union _IoHsWrToCnt{
    kulong       word;
    struct {
        kulong   hsWrToCnt    :16;
        kulong                   :16;
    }bit;
};

/*  structure of LP_WR_TO_CNT  (2800_C088h)    */
union _IoLpWrToCnt{
    kulong       word;
    struct {
        kulong   lpWrToCnt    :16;
        kulong                   :16;
    }bit;
};

/*  structure of SDF_3D  (2800_C090h)    */
union _IoSdf3d{
    kulong       word;
    struct {
        kulong   mode3d         :2;
        kulong   format3d       :2;
        kulong   secondVsync    :1;
        kulong   rightFirst     :1;
        kulong                   :10;
        kulong   send3dCfg     :1;
        kulong                   :15;
    }bit;
};

/*  structure of LPCLK_CTRL  (2800_C094h)    */
union _IoLpclkCtrl{
    kulong       word;
    struct {
        kulong   phyTxrequestclkhs  :1;
        kulong   autoClklaneCtrl   :1;
        kulong                       :30;
    }bit;
};

/*  structure of PHY_TMR_LPCLK_CFG  (2800_C098h)    */
union _IoPhyTmrLpclkCfg{
    kulong       word;
    struct {
        kulong   phyClkhs2lpTime   :10;
        kulong                       :6;
        kulong   phyClklp2hsTime   :10;
        kulong                       :6;
    }bit;
};

/*  structure of PHY_TMR_CFG  (2800_C09Ch)    */
union _IoPhyTmrCfg{
    kulong       word;
    struct {
        kulong                   :16;
        kulong   phyLp2hsTime  :8;
        kulong   phyHs2lpTime  :8;
    }bit;
};

/*  structure of PHY_RSTZ  (2800_C0A0h)    */
union _IoPhyRstz{
    kulong       word;
    struct {
        kulong   phyShutdownz   :1;
        kulong                   :31;
    }bit;
};

/*  structure of PHY_IF_CFG  (2800_C0A4h)    */
union _IoPhyIfCfg{
    kulong       word;
    struct {
        kulong   nLanes     :2;
        kulong               :30;
    }bit;
};

/*  structure of PHY_ULPS_CTRL  (2800_C0A8h)    */
union _IoPhyUlpsCtrl{
    kulong       word;
    struct {
        kulong   phyTxrequlpsclk    :1;
        kulong   phyTxexitulpsclk   :1;
        kulong   phyTxrequlpslan    :1;
        kulong   phyTxexitulpslan   :1;
        kulong                       :28;
    }bit;
};

/*  structure of PHY_TX_TRIGGERS  (2800_C0ACh)    */
union _IoPhyTxTriggers{
    kulong       word;
    struct {
        kulong   phyTxTriggers     :4;
        kulong                       :28;
    }bit;
};

/*  structure of PHY_STATUS  (2800_C0B0h)    */
union _IoPhyStatus{
    kulong       word;
    struct {
        kulong                           :1;
        kulong   phyDirection           :1;
        kulong   phyStopstateclklane    :1;
        kulong   phyUlpsactivenotclk    :1;
        kulong   phyStopstate0lane      :1;
        kulong   phyUlpsactivenot0lane  :1;
        kulong                           :1;
        kulong   phyStopstate1lane      :1;
        kulong   phyUlpsactivenot1lane  :1;
        kulong   phyStopstate2lane      :1;
        kulong   phyUlpsactivenot2lane  :1;
        kulong   phyStopstate3lane      :1;
        kulong   phyUlpsactivenot3lane  :1;
        kulong                           :19;
    }bit;
};

/*  structure of INT_ST1  (2800_C0C0h)    */
union _IoIntSt1{
    kulong       word;
    struct {
        kulong   toHsTx            :1;
        kulong                       :6;
        kulong   dpiPldWrErr      :1;
        kulong   genCmdWrErr      :1;
        kulong   genPldWrErr      :1;
        kulong   genPldSendErr    :1;
        kulong                       :21;
    }bit;
};

/*  structure of INT_MSK1  (2800_C0C8h)    */
union _IoIntMsk1{
    kulong       word;
    struct {
        kulong   toHsTx            :1;
        kulong                       :6;
        kulong   dpiPldWrErr      :1;
        kulong   genCmdWrErr      :1;
        kulong   genPldWrErr      :1;
        kulong   genPldSendErr    :1;
        kulong                       :21;
    }bit;
};

/*  structure of VID_SHADOW_CTRL  (2800_C100h)    */
union _IoVidShadowCtrl{
    kulong       word;
    struct {
        kulong   vidShadowEn       :1;
        kulong                       :7;
        kulong   vidShadowReq      :1;
        kulong                       :7;
        kulong   vidShadowPinReq  :1;
        kulong                       :15;
    }bit;
};

/*  structure of VID_MODE_CFG_ACT  (2800_C038h)    */
union _IoVidModeCfgAct{
    kulong       word;
    struct {
        kulong   vidModeType   :2;
        kulong                   :6;
        kulong   lpVsaEn       :1;
        kulong   lpVbpEn       :1;
        kulong   lpVfpEn       :1;
        kulong   lpVactEn      :1;
        kulong   lpHbpEn       :1;
        kulong   lpHfpEn       :1;
        kulong                   :1;
        kulong   lpCmdEn       :1;
        kulong                   :16;
    }bit;
};

/*  structure of PHY_SETUP_CL (2800_C400h) / PHY_SETUP_DL (2800_C404h)    */
union _IoPhySetup{
    kulong       word;
    struct {
        kulong   sapTlpx    :8;
        kulong   sapHs0     :8;
        kulong   sapTrail   :8;
        kulong   sapPre     :8;
    }bit;
};

/*  structure of PHY_TCLKPOST  (2800_C408h)    */
union _IoPhyTclkost{
    kulong       word;
    struct {
        kulong   tclkPost   :6;
        kulong               :26;
    }bit;
};

/* Define i/o mapping */
struct _IoFMipidsi11txLp{
    /* F_MIPIDSI11TX_LP */
	/* 2800_(C000 - C003h) */
    kulong					version;
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
    kuchar dmyC01cC02b[0xC02C-0xC01C];
    /* 2800_(C02C - C02Fh) */
    IoPckhdlCfg				pckhdlCfg;
    /* 2800_(C030 - C033h) */
    kuchar dmyC030C033[0xC034-0xC030];
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
    kuchar dmyC064C067[0xC068-0xC064];
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
    kuchar dmyC07cC083[0xC084-0xC07C];
    /* 2800_(C084 - C087h) */
    IoHsWrToCnt			hsWrToCnt;
    /* 2800_(C088 - C08Bh) */
    IoLpWrToCnt			lpWrToCnt;
    /* 2800_(C08C - C08Fh) */
    kuchar dmyC08cC08f[0xC090-0xC08C];
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
    kuchar dmyC0b4C0bf[0xC0C0-0xC0B4];
    /* 2800_(C0C0 - 0C3Ch) */
    IoIntSt1				intSt1;
    /* 2800_(C0C4 - C0C7h) */
    kuchar dmyC0c4C0c7[0xC0C8-0xC0C4];
    /* 2800_(C0C8 - C0CBh) */
    IoIntMsk1				intMsk1;
    /* 2800_(C0CC - C0FFh) */
    kuchar dmyC0ccC0ff[0xC100-0xC0CC];
    /* 2800_(C100 - C103h) */
    IoVidShadowCtrl		vidShadowCtrl;
    /* 2800_(C104 - C10Bh) */
    kuchar dmyC104C10b[0xC10C-0xC104];
    /* 2800_(C10C - C10Fh) */
    IoDpiVcid				dpiVcidAct;
    /* 2800_(C110 - C113h) */
    IoDpiColorCoding		dpiColorCodingAct;
    /* 2800_(C114 - C117h) */
    kuchar dmyC114C117[0xC118-0xC114];
    /* 2800_(C118 - C11Bh) */
    IoDpiLpCmdTim			dpiLpCmdTimAct;
    /* 2800_(C11C - C137h) */
    kuchar dmyC11cC137[0xC138-0xC11C];
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
    kuchar dmyC164C18f[0xC190-0xC164];
    /* 2800_(C190 - C193h) */
    IoSdf3d					sdf3dAct;
    /* 2800_(C194 - C3FFh) */
    kuchar dmyC194C3ff[0xC400-0xC194];
    /* 2800_(C400 - C403h) */
    IoPhySetup				phySetupCl;
    /* 2800_(C404 - C407h) */
    IoPhySetup				phySetupDl;
    /* 2800_(C408 - C40Bh) */
    IoPhyTclkost			phyTclkpost;
    /* 2800_(C40C - CFFFCh) */
    kuchar dmyC40cCfff[0xD000-0xC40C];
};

struct  _FMipidsi11txLp
{
	KObject parent;
};


KConstType					f_mipidsi11tx_lp_get_type(void);
FMipidsi11txLp*			f_mipidsi11tx_lp_new(void);


#endif/*__F_MIPIDSI11TX_LP_H__*/
