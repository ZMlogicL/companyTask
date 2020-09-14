/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-04
 *@author : 王顺
 *@brief : DdPcieRcCommon
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */
/**
 * @file		dd_pcie_comm.h
 * @brief		PCIe driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
/**
 @weakgroup dd_pcie_comm
 @{

 Please refer to the PCIe_RootComplex and the PCIe_Endpoint.

 <hr>

 @section dd_pcie_comm_sequence Sequence Chart
 Please refer to the PCIe_RootComplex and the PCIe_Endpoint.

 @}
 */

/**
 @addtogroup dd_pcie_comm
 @{

 */

#ifndef _DD_PCIE_H_
#define _DD_PCIE_H_

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// Return value
#define	C_PCIE_INPUT_PARAM_ERROR	(D_DD_PCIE | D_DDIM_INPUT_PARAM_ERROR)
/**< Input Parameter Error */
#define	C_PCIE_ACCESS_ERR					(D_DD_PCIE | D_DDIM_ACCESS_ERR)
/**< Access error */
#define	C_PCIE_SEM_TIMEOUT				(D_DD_PCIE | D_DDIM_SEM_TIMEOUT)
/**< Semaphore acquisition Time Out */
#define	C_PCIE_SEM_NG							(D_DD_PCIE | D_DDIM_SEM_NG)
/**< Semaphore acquisition NG */
#define C_PCIE_TIMEOUT						(D_DD_PCIE | D_DDIM_TIMEOUT)
/**< Time Out */
#define	C_PCIE_COMM_ERROR				(D_DD_PCIE | D_DDIM_COMM_ERROR)
/**< Communication error (Not link up) */
#define C_PCIE_0_DBI_ADR						(0x19150000)
/**< PCIe0 DBI AXI Slave register top address	*/
#define C_PCIE_1_DBI_ADR						(0x19160000)
/**< PCIe1 DBI AXI Slave register top address	*/
#define C_PCIE_0_PIO_ADR						(0x19400000)
/**< PCIe0 PIO area	top address	*/
#define C_PCIE_1_PIO_ADR						(0x19800000)
/**< PCIe1 PIO area	top address */
#define C_PCIE_0_EXS_ADR						(0x1B111000)
/**< EXSTOP PCIE0 register top address	*/
#define C_PCIE_1_EXS_ADR						(0x1B112000)
/**< EXSTOP PCIE1 register top address	*/


typedef enum _DdPcieBifurcation DdPcieBifurcation;
typedef enum _DdPcieCh DdPcieCh;
typedef enum _DdPcieReType DdPcieReType;
typedef enum _DdPcieLinkSpeed DdPcieLinkSpeed;
typedef enum _DdPcieDmaTransMode DdPcieDmaTransMode;
typedef enum _DdPcieDmaCh DdPcieDmaCh;
typedef enum _DdPcieDmaDir DdPcieDmaDir;
typedef enum _DdPciePmst DdPciePmst;
typedef enum _DdPcieStLtssm DdPcieStLtssm;
typedef enum _DdPcieAspmControl DdPcieAspmControl;
typedef enum _DdPcieMps DdPcieMps;
typedef struct _DdPcieCtrlDma DdPcieCtrlDma;
typedef struct _DdPcieCtrlMem DdPcieCtrlMem;
typedef struct _DdPcieIntDmaCb DdPcieIntDmaCb;

/** Bifurcation mode */
enum _DdPcieBifurcation
{
	E_DD_PCIE_BIFURCATION_DISABLE = 0, /**< Bifurcation disable	*/
	E_DD_PCIE_BIFURCATION_ENABLE /**< Bifurcation enable	*/
};

/** PCIe channel */
enum _DdPcieCh
{
	E_DD_PCIE_CH0 = 0, /**< channel 0*/
	E_DD_PCIE_CH1 /**< channel 1*/
};

/** PCIe type */
enum _DdPcieReType
{
	E_DD_PCIE_RE_TYPE_EP = 0, /**< PCIe Endpoint*/
	E_DD_PCIE_RE_TYPE_RC, /**< PCIe Root Complex*/
	E_DD_PCIE_RE_TYPE_US, /**< PCIe type unsettled	*/
};

/** Link speed */
enum _DdPcieLinkSpeed
{
	E_DD_PCIE_LINK_SPEED_GEN1 = 1, /**< 2.5GT/s*/
	E_DD_PCIE_LINK_SPEED_GEN2 /**< 5.0GT/s	*/
};

/** DMA transfer mode */
enum _DdPcieDmaTransMode
{
	E_DD_PCIE_DMA_DEMAND_MODE = 0, /**< demand dma transfer (Non LL mode)*/
	E_DD_PCIE_DMA_LL_MODE /**< Linked List mode	*/
};

/** DMA channel */
enum _DdPcieDmaCh
{
	E_DD_PCIE_DMA_CH0 = 0, /**< dma channel 0*/
	E_DD_PCIE_DMA_CH1 /**< dma channel 1	*/
};

/** DMA direction */
enum _DdPcieDmaDir
{
	E_DD_PCIE_DMA_DIR_DTOS = 0, /**< destination to source (read)*/
	E_DD_PCIE_DMA_DIR_STOD /**< source to destination (write)	*/
};

/** Power Status */
enum _DdPciePmst
{
	E_DD_PCIE_PMST_D0 = 0, /**< D0 Status*/
	E_DD_PCIE_PMST_D1, /**< D1 Status*/
	E_DD_PCIE_PMST_D2, /**< D2 Status*/
	E_DD_PCIE_PMST_D3, /**< D3 Status*/
	E_DD_PCIE_PMST_UNINITIALIZED /**< Uninitialized	*/
};

/** LTSSM Status */
enum _DdPcieStLtssm
{
	E_DD_PCIE_S_DETECT_QUIET = 0, /**< DETECT_QUIET*/
	E_DD_PCIE_S_DETECT_ACT, /**< DETECT_ACT*/
	E_DD_PCIE_S_POLL_ACTIVE, /**< POLL_ACTIVE*/
	E_DD_PCIE_S_POLL_COMPLIANCE, /**< POLL_COMPLIANCE*/
	E_DD_PCIE_S_POLL_CONFIG, /**< POLL_CONFIG*/
	E_DD_PCIE_S_PRE_DETECT_QUIET, /**< PRE_DETECT_QUIET*/
	E_DD_PCIE_S_DETECT_WAIT, /**< DETECT_WAIT*/
	E_DD_PCIE_S_CFG_LINKWD_START, /**< CFG_LINKWD_START	*/
	E_DD_PCIE_S_CFG_LINKWD_ACEPT, /**< CFG_LINKWD_ACEPT	*/
	E_DD_PCIE_S_CFG_LANENUM_WAI, /**< CFG_LANENUM_WAI	*/
	E_DD_PCIE_S_CFG_LANENUM_ACEPT, /**< CFG_LANENUM_ACEPT*/
	E_DD_PCIE_S_CFG_COMPLETE, /**< CFG_COMPLETE	*/
	E_DD_PCIE_S_CFG_IDLE, /**< CFG_IDLE*/
	E_DD_PCIE_S_RCVRY_LOCK, /**< RCVRY_LOCK*/
	E_DD_PCIE_S_RCVRY_SPEED, /**< RCVRY_SPEED*/
	E_DD_PCIE_S_RCVRY_RCVRCFG, /**< RCVRY_RCVRCFG*/
	E_DD_PCIE_S_RCVRY_IDLE, /**< RCVRY_IDLE	*/
	E_DD_PCIE_S_L0, /**< L0*/
	E_DD_PCIE_S_L0S, /**< L0S*/
	E_DD_PCIE_S_L123_SEND_EIDLE, /**< L123_SEND_EIDLE	*/
	E_DD_PCIE_S_L1_IDLE, /**< L1_IDLE*/
	E_DD_PCIE_S_L2_IDLE, /**< L2_IDLE*/
	E_DD_PCIE_S_L2_WAKE, /**< L2_WAKE*/
	E_DD_PCIE_S_DISABLED_ENTRY, /**< DISABLED_ENTRY*/
	E_DD_PCIE_S_DISABLED_IDLE, /**< DISABLED_IDLE*/
	E_DD_PCIE_S_DISABLED, /**< DISABLED*/
	E_DD_PCIE_S_LPBK_ENTRY, /**< LPBK_ENTRY*/
	E_DD_PCIE_S_LPBK_ACTIVE, /**< LPBK_ACTIVE*/
	E_DD_PCIE_S_LPBK_EXIT, /**< LPBK_EXIT*/
	E_DD_PCIE_S_LPBK_EXIT_TIMEOUT, /**< LPBK_EXIT_TIMEOUT*/
	E_DD_PCIE_S_HOT_RESET_ENTRY, /**< HOT_RESET_ENTRY*/
	E_DD_PCIE_S_HOT_RESET, /**< HOT_RESET*/
	E_DD_PCIE_S_RCVRY_EQ0, /**< RCVRY_EQ0*/
	E_DD_PCIE_S_RCVRY_EQ1, /**< RCVRY_EQ1*/
	E_DD_PCIE_S_RCVRY_EQ2, /**< RCVRY_EQ2*/
	E_DD_PCIE_S_RCVRY_EQ3 /**< RCVRY_EQ3*/
};

/** ASPM Control */
enum _DdPcieAspmControl
{
	E_DD_PCIE_ASPM_CONTROL_DISABLE = 0, /**< Disabled	*/
	E_DD_PCIE_ASPM_CONTROL_L0S, /**< L0s Entry Enabled	*/
	E_DD_PCIE_ASPM_CONTROL_L1, /**< L1 Entry Enabled*/
	E_DD_PCIE_ASPM_CONTROL_L0S_L1 /**< L0s and L1 Entry Enabled*/
};

/** Max payload size */
enum _DdPcieMps
{
	E_DD_PCIE_DMA_MPS_128 = 0, /**< 128 bytes	*/
	E_DD_PCIE_DMA_MPS_256, /**< 256 bytes	*/
	E_DD_PCIE_DMA_MPS_512 /**< 512 bytes	*/
};

typedef void (*VpCallbackPcieFunc)(UINT32 status);	/**< Type is defined to Callback function pointer for PCIE */

/** PCIe DMA control data */
struct _DdPcieCtrlDma
{
	DdPcieDmaTransMode mode; /**< DMA transfer mode		*/
	DdPcieCh ch; /**< PCIe channel(EP unused)	*/
	DdPcieDmaCh dmaCh; /**< DMA channel			*/
	UINT32 dmndSrcAddrL; /**< Demand dma transfer source lower address (Linked List DMA transfer unused)*/
	UINT32 dmndSrcAddrH; /**< Demand dma transfer source hight address (Linked List DMA transfer unused)*/
	UINT32 dmndDstAddrL; /**< Demand dma transfer destination lower address (Linked List DMA transfer unused)*/
	UINT32 dmndDstAddrH; /**< Demand dma transfer destination hight address (Linked List DMA transfer unused)	*/
	UINT32 dmndTransSize; /**< Demand dma transfer total size (Linked List DMA transfer unused)					*/
	UINT32 llAddr; /**< Link list dma transfer table address (Demand DMA transfer unused)					*/
	DdPcieDmaDir direction; /**< Transfer direction	*/
	vpCallbackPcieFunc intDmaCb; /**< Interrupt dma callback function	*/
};

/** PCIe memory control data */
struct _DdPcieCtrlMem
{
	DdPcieCh ch; /**< PCIe channel	*/
	UINT32 baseAdr; /**< base address	*/
	UINT32 limitAdr; /**< limit address	*/
	UINT32 lowTargetAdr; /**< Lower target address	*/
	UINT32 uppTargetAdr; /**< Upper target address	*/
};

/** PCIe interrupt DMA callback. */
struct _DdPcieIntDmaCb
{
	vpCallbackPcieFunc wrCb; /**< Write callback	*/
	vpCallbackPcieFunc rdCb; /**< Read callback	*/
};

#ifdef __cplusplus
}
#endif

#endif	// _DD_PCIE_H_
