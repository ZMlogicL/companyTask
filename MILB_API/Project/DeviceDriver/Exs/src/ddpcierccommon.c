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


#include "ddpcierccommon.h"
#include"ddtoptwo.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdPcieRcCommon, dd_pcie_rc_common);

#define DD_PCIE_RC_COMMON_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), DdPcieRcCommonPrivate, DD_TYPE_PCIE_RC_COMMON))


struct _DdPcieRcCommonPrivate
{
	volatile DdPcieBifurcation	gddPcieRcBifurcation;
};


//volatile DdPcieBifurcation	gddPcieRcBifurcation = E_DD_PCIE_BIFURCATION_DISABLE;
volatile DdPcieRcIntTrsIcsMsiCb gddPcieRcIntTrsIcsMsiCb[C_PCIE_RC_MAX_CH] =
		{ { NULL, NULL, NULL }, { NULL, NULL, NULL } };
volatile DdPcieRcIntSysErrCb gddPcieRcIntSysErrCb[C_PCIE_RC_MAX_CH] =
		{ { NULL, NULL }, { NULL, NULL } };
volatile DdPcieRcIntEpCb gddPcieRcIntEpCb[C_PCIE_RC_MAX_CH] =
		{{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};
volatile DdPciRcIntOwnCb gddPcieRcIntOwnCb[C_PCIE_RC_MAX_CH] = {
		{ NULL, NULL, NULL, NULL }, { NULL, NULL, NULL, NULL } };
volatile vpCallbackPcieFunc gddPcieRcHpDetectCard[C_PCIE_RC_MAX_CH] = {NULL, NULL};
volatile kuint16 gddPcieRcConfigAdr[C_PCIE_RC_MAX_CH] = {(D_DD_PCIE_0_PIO_ADR >> 16), (D_DD_PCIE_1_PIO_ADR >> 16)};

/** PCIe IP mode */
volatile kuchar	gddPcieRcReType = E_DD_PCIE_RE_TYPE_US;	/**< Type Undettled */
volatile DdPcieIntDmaCb gddPcieRcIntDmaCb[C_PCIE_RC_MAX_CH] = {{NULL, NULL}, {NULL, NULL}};
volatile vpCallbackPcieFunc gddPcieRcIntMsiCb[C_PCIE_RC_MAX_CH] = {NULL, NULL};

/**
DECLS
*/

/**
IMPL
*/
static void dd_pcie_rc_common_constructor(DdPcieRcCommon *self)
{
	DdPcieRcCommonPrivate *priv = DD_PCIE_RC_COMMON_GET_PRIVATE(self);
	priv->gddPcieRcBifurcation = E_DD_PCIE_BIFURCATION_DISABLE;

}

static void dd_pcie_rc_common_destructor(DdPcieRcCommon *self)
{
//	DdPcieRcCommonPrivate *priv = DD_PCIE_RC_COMMON_GET_PRIVATE(self);
}
/**
PUBLIC
*/
/**
 * @brief	Initialize PCIe Root Complex.
 * @param	volatile IoPcie* ioPcie
 * @param	DdPcieBifurcation bifurcation
 */
void	dd_pcie_rc_common_init(DdPcieRcCommon *self, volatile IoPcie* ioPcie,
				volatile IoPcieCore* ioPcieCore, DdPcieBifurcation bifurcation)
{
	// 1 Assert all PHY / LINK resets
	ioPcie->resetControl1.word = 0x00000000;
	ioPcie->resetControl2.word = 0x00000000;
	ioPcie->resetSelect1.word = 0x31111000;
	ioPcie->resetSelect2.word = 0x00000111;

	// 2 Set P<n>_app_ltssm_enable='0' for reprogramming before linkup.
	ioPcie->coreControl.bit.appLtssmEnable = 0;

	// 3 Set device_type (RC)
	ioPcie->coreControl.bit.deviceType = 4;// Root Port of PCI Express Root Complex

	if (bifurcation == E_DD_PCIE_BIFURCATION_DISABLE) {
		// 4 pipe_port_sel=2'b01 ( Disable )
		ioPcie->phyConfigCom6.bit.pipePortSel = 1;
	} else {
		// 4 pipe_port_sel=2'b10 ( Enable )
		ioPcie->phyConfigCom6.bit.pipePortSel = 2;
	}

	// 5 Supply Reference (It has executed)
	// 6 Wait for 10usec (Reference Clocks is stable)
	DD_ARM_WAIT_NS(10000);

	// 7 De assert PERST#
	ioPcie->resetControl1.word = 0x00000030;

	// 8 Assert sysAuxPwrDet
	ioPcie->pmControl2.bit.sysAuxPwrDet = 1;

	// 9 Supply following clocks
	ioPcie->axiClkStop.word = 0x00000222;
	DdToptwo_SET_CLKSTOP2_PCISUPPCK(2);	// Sub clock of PCI is supplied.

	// 10 De assert PHY reset
	// 11 De assert LINK's PMC reset
	ioPcie->resetControl1.word = 0x00000033;

	// 12 PHY auto
	// 13 Wrapper auto
	// 14-17 PHY auto
	// 18 Wrapper auto

	// 19 Update registers through DBI AXI Slave interface
	ioPcieCore->rc.t1csh.statusCommand.bit.ios = 1;// Allow access response of IO space.
	ioPcieCore->rc.t1csh.statusCommand.bit.ms = 1;// Allow access response of Memory space.
	ioPcieCore->rc.t1csh.statusCommand.bit.bme = 1;// Device issues the Memory/IO Request. (including MSI)
	ioPcieCore->rc.pciecr.dcsr.bit.mrrs = 1;	// 256Byte max Read Request size
	ioPcieCore->rc.pciecr.dcsr.bit.mps = 2;	// 512Byte max Payload size
	ioPcieCore->rc.ppl.mc1.bit.drwe = 1;
	ioPcieCore->rc.pciecr.lcr.bit.lbnc = 1;	// PCIE_CAP_LINK_BW_NOT_CAP
	ioPcieCore->rc.ppl.mc1.bit.drwe = 0;

	// 20 Set P<n>_app_ltssm_enable='1'
	ioPcie->coreControl.bit.appLtssmEnable = 1;
}

/**
 * @brief	Check configration read and write parameter.
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_COMM_ERROR
 */
kint32 dd_pcie_rc_common_chk_config_rw_par(DdPcieRcCommon *self, DdPcieCh ch, kuint16 offset)
{
	if ((offset % 4) != 0) {	// Word boundary violation
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	if (dd_pcie_rc_get_link_status(NULL, ch) == FALSE) {	// Not link up
		return C_PCIE_COMM_ERROR;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Check EXSTOP PCIe register access parameter.
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_common_chk_exs_reg_par(DdPcieRcCommon *self, DdPcieCh ch, kuint16 offset)
{
	// Word boundary check.
	if ((offset % 4) != 0) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	// Check on reserved address.
	if ((offset >= 0x0060 && offset <= 0x00FF) || (offset >= 0x0118 && offset <= 0x01D7) || (offset == 0x0204)
			|| (offset == 0x0214) || (offset == 0x0234) || (offset >= 0x0288)) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Check DBI AXI slave register access parameter.
 * @param	DdPcieCh	ch
 * @param	kuint16			offset
 * @return	kint32	D_DDIM_OK/C_PCIE_INPUT_PARAM_ERROR/C_PCIE_ACCESS_ERR
 */
kint32 dd_pcie_rc_common_chk_dbi_reg_par(DdPcieRcCommon *self, DdPcieCh ch, kuint16 offset)
{
	// Word boundary check.
	if ((offset % 4) != 0) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	// Check on reserved address. Access Type = DBI(Normal Register Access).
	if ((offset >= 0x0010 && offset <= 0x0017) || (offset >= 0x0048 && offset <= 0x004F) ||
			(offset >= 0x0068 && offset <= 0x006F) || (offset >= 0x00A4 && offset <= 0x00AF)
			|| (offset >= 0x00B0 && offset <= 0x00FF) || (offset >= 0x0160 && offset <= 0x06FF)
			|| (offset >= 0x0754 && offset <= 0x080B) || (offset >= 0x0818 && offset <= 0x081F)
			|| (offset >= 0x0834 && offset <= 0x0887) || (offset >= 0x088C && offset <= 0x08B7)
			|| (offset >= 0x08C8 && offset <= 0x08CB) || (offset >= 0x08DC && offset <= 0x08DF)
			|| (offset >= 0x08EC && offset <= 0x08EF) || (offset >= 0x08F8 && offset <= 0x08FF)
			|| (offset >= 0x0920 && offset <= 0x096F) || (offset >= 0x0974 && offset <= 0x0977)
			|| (offset >= 0x0984 && offset <= 0x0987) || (offset >= 0x0990 && offset <= 0x099B)
			|| (offset >= 0x09A4 && offset <= 0x09A7) || (offset >= 0x09B0 && offset <= 0x09BB)
			|| (offset >= 0x09C0 && offset <= 0x09C3) || (offset >= 0x09F0 && offset <= 0x09FF)
			|| (offset >= 0x0A04 && offset <= 0x0A0F) || (offset >= 0x0A14 && offset <= 0x0A17)
			|| (offset >= 0x0A20 && offset <= 0x0A23) || (offset >= 0x0A2C && offset <= 0x0A33)
			|| (offset >= 0x0A38 && offset <= 0x0A3B) || (offset >= 0x0A5C && offset <= 0x0A6B)
			|| (offset >= 0x0A74 && offset <= 0x0A77) || (offset >= 0x0A94 && offset <= 0x0B2F)
			|| (offset >= 0x0B34 && offset <= 0x0B3F) || (offset >= 0x0B48 && offset <= 0x0FFF)) {
		return C_PCIE_INPUT_PARAM_ERROR;
	}

	if (ch == E_DD_PCIE_CH0) {
		if (DdExs_GET_RAM_PD_CTRL_PCIE0() != 0) {
			// PCIe power down
			return C_PCIE_ACCESS_ERR;
		}
	} else {
		if (DdExs_GET_RAM_PD_CTRL_PCIE1() != 0) {
			return C_PCIE_ACCESS_ERR;
		}
	}

	return D_DDIM_OK;
}

DdPcieBifurcation	dd_pcie_rc_common_get_gdd_pcie_rc_bifurcation(DdPcieRcCommon * self)
{
	DdPcieRcCommonPrivate *priv = DD_PCIE_RC_COMMON_GET_PRIVATE(self);
	return priv->gddPcieRcBifurcation;
}

void	dd_pcie_rc_common_set_gdd_pcie_rc_bifurcation(DdPcieRcCommon * self,
				DdPcieBifurcation	gddPcieRcBifurcation)
{
	DdPcieRcCommonPrivate *priv = DD_PCIE_RC_COMMON_GET_PRIVATE(self);
	priv->gddPcieRcBifurcation = gddPcieRcBifurcation;
}

DdPcieRcCommon* dd_pcie_rc_common_get(void)
{
	static DdPcieRcCommon* self = NULL;

	if (!self) {
		self = k_object_new_with_private(DD_TYPE_PCIE_RC_COMMON, sizeof(DdPcieRcCommonPrivate));
	}

	return self;
}
