/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :周洪
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、Exs driver
*2、将dd_exs.c里将前面的77个共有方法放在这里,并将
*@version
*1.0.0 2020年06月开始开发
*/

#include "exstop.h"
#include "driver_common.h"
#include "ddimusercustom.h"
#include "ddexs.h"

K_TYPE_DEFINE_WITH_PRIVATE(DdExs, dd_exs);
#define DD_EXS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), DdExsPrivate, DD_TYPE_EXS))

struct _DdExsPrivate
{
    int a;
};

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static kulong S_DD_EXS_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void dd_exs_constructor(DdExs *self)
{
	DdExsPrivate *priv = DD_EXS_GET_PRIVATE(self);
    priv->a = 0;
}

static void dd_exs_destructor(DdExs *self)
{

}

/*----------------------------------------------------------------------*/
/* PUBLIC(公有函数接口实现)									*/
/*----------------------------------------------------------------------*/
/**
Set status of transition requests to LowPower mode of XDMAC.<br>
@param[in]  *val Setting value
					<ul><li> 0:LowPower mode request.
						<li> 1:Normal mode request.</ul>
@retval	None.
*/
void dd_exs_set_xdmac_lowpower_ctl_csysreq(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);	//TODO:定义在dd_arm.h中原型DD_ARM_CRITICAL_SECTION_START(s)
	ioExstop.xdmacLpctrl.bit.csysReq = val;							//TODO:IO_EXSTOP不符合代码规范,应该用get 来读
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of nf_rst_n terminal.<br>
@param[in]  *val Setting value.
					<ul><li> 0:nf_rst_n terminal reset is released.
						<li> 1:nf_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_nf_rst_n_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.nfRstn = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of bch_rst_n terminal.<br>
@param[in]  *val Setting value
					<ul><li> 0:bch_rst_n terminal reset is released.
						<li> 1:bch_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_bch_rst_n_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.nfRstnBch = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of reg_rst_n terminal.<br>
@param[in]  *val Setting value
					<ul><li> 0:reg_rst_n terminal reset is released.
						<li> 1:reg_rst_n terminal reset is set.</ul>
@retval	None.
*/
void dd_exs_set_reg_rst_n_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.nfRstnReg = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of NETSEC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:NETSEC macro reset is released.
						<li> 1:NETSEC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_netsec_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.netsecRst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of eMMC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:eMMC macro reset is released.
						<li> 1:eMMC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_emmc_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.emcRst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of RELC macro.<br>
@param[in]  *val Setting value
					<ul><li> 0:RELC macro reset is released.
						<li> 1:RELC macro reset is set.</ul>
@retval	None.
*/
void dd_exs_set_relc_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset.bit.relcRst = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce SD3 (UHS2).<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
					<ul><li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_sd3_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxSd3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce SD4 (UHS1 Card).<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_sd4_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxSd4 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce PCIe0.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_pcie0_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxPcie0 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce PCIe1.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_pcie1_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxPcie1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce USB2 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb2vbus_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxUsb2Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce USB2 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb2id_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxUsb2Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce USB3 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb3vbus_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxUsb3Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set reset control of Card Debounce USB3 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:Card Debounce reset is released.
						<li> 1:Card Debounce reset is set.</ul>
@retval	None.
*/
void dd_exs_set_usb3id_cd_debounce_soft_reset(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.softreset2.bit.debrstxUsb3Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD3(UHS2) Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the SD3(UHS2) detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd3_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk02 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD3(UHS2) Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the SD3(UHS2) detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd3_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk03 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD4(UHS1 Card) Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the SD4(UHS1 Card) detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd4_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk04 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD4(UHS1 Card) Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the SD4(UHS1 Card) detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_sd4_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk05 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe0 Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe0 detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe0 detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie0_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk06 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe0 Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe0 detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe0 detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie0_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk07 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe1 Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe1 detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe1 detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie1_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk08 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe1 Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the PCIe1 detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the PCIe1 detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_pcie1_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk09 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 VBUS Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 VBUS detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 VBUS detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2vbus_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk10 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 VBUS Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 VBUS detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 VBUS detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2vbus_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk11 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 ID Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 ID detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 ID detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2id_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk12 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 ID Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB2 ID detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB2 ID detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb2id_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk13 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 VBUS Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 VBUS detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 VBUS detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3vbus_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk14 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 VBUS Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 VBUS detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 VBUS detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3vbus_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk14 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 ID Detect INT Mask(Rising Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 ID detection rising edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 ID detection rising edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3id_rim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk16 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 ID Detect INT Mask(Falling Edge).<br>
@param[in]  *val Setting value
					<ul><li> 0:The interrupt signal by the USB3 ID detection falling edge detection factor is output.
						<li> 1:The interrupt signal by the USB3 ID detection falling edge detection factor is mask.</ul>
@retval	None.
*/
void dd_exs_set_intmsk_usb3id_fim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.intMsk.bit.intMsk17 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}
/**
Set SD3(UHS2) Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the SD3(UHS2) signal is turned off.
						<li> 1:The debounce of the SD3(UHS2) signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_sd3_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenSd3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD4(UHS1 Card) Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the SD4(UHS1 Card) signal is turned off.
						<li> 1:The debounce of the SD4(UHS1 Card) signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_sd4_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenSd4 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe0 Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the PCIe0 signal is turned off.
						<li> 1:The debounce of the PCIe0 signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie0_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenPcie0 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe1 Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the PCIe1 signal is turned off.
						<li> 1:The debounce of the PCIe1 signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie1_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenPcie1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 VBUS Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB2 VBUS signal is turned off.
						<li> 1:The debounce of the USB2 VBUS signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2vbus_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenUsb2Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 ID Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB2 ID signal is turned off.
						<li> 1:The debounce of the USB2 ID signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2id_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenUsb2Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 VBUS Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB3 VBUS signal is turned off.
						<li> 1:The debounce of the USB3 VBUS signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3vbus_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenUsb3Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 ID Debounce ON/OFF.<br>
@param[in]  *val Setting value
					<ul><li> 0:The debounce of the USB3 ID signal is turned off.
						<li> 1:The debounce of the USB3 ID signal is turned on.</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3id_en(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.debenUsb3Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD-Card ch3 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_sd3detim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.sd3Detim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD-Card ch4 Debounce time..<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_sd4detim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.sd4Detim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe0 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie0detim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.pcie0Detim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIe1 Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_pcie1detim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.pcie1Detim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 VBUS Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2vbusdetim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.usb2VbusDetim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 ID Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb2iddetim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.usb2IdDetim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 VBUS Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3vbusdetim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.usb3VbusDetim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 ID Debounce time.<br>
@param[in]  *val Setting value
					<ul><li> 00:APBCLK 131072 cycles<br>
						<li> 01:APBCLK 65536 cycles (131072 cycles /2).
						<li> 10:APBCLK 262144 cycles (131072 cycles *2).
						<li> 11:APBCLK 524288 cycles (131072 cycles *4).</ul>
@retval	None.
*/
void dd_exs_set_deben_usb3iddetim(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.deben.bit.usb3IdDetim = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection SD3(UHS2).<br>
param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD3(UHS2) signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD3(UHS2) signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_sd3_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodSd3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection SD4(UHS1 Card).<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the SD4(UHS1 Card) signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the SD4(UHS1 Card) signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_sd4_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodSd4 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection PCIe0.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe0 signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe0 signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_pcie0_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodPcie0 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection PCIe1.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the PCIe1 signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the PCIe1 signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_pcie1_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodPcie1 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection USB2 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 VBUS signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 VBUS signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb2vbus_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodUsb2Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection USB2 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB2 ID signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB2 ID signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb2id_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodUsb2Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection USB3 VBUS.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 VBUS signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 VBUS signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb3vbus_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodUsb3Vbus = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the mode setting of the card detection USB3 ID.<br>
@param[in]  *val Setting value
					<ul><li> 0:After exiting reset at debounce circuit, generates an interrupt regardless of the state of the USB3 ID signal.
						<li> 1:After exiting reset at debounce circuit, generates an interrupt by the state of the USB3 ID signal.</ul>
@retval	None.
*/
void dd_exs_set_cdins_usb3id_mod(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.cdinsmdctl.bit.cdimodUsb3Id = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the RELC expanded data read side HPROT setting(Data/Opcode).<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_set_relc_hprot_read(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.rlcHptCtl.bit.reRHpt = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set the RELC expanded data write side HPROT setting(Data/Opcode).<br>
@param[in]  *val Setting value
@retval	None.
*/
void dd_exs_set_relc_hprot_write(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.rlcHptCtl.bit.reWHpt = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD2(UHS1 Wifi) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd2(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdSd2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD3(UHS2) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd3(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdSd3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set SD4(UHS1 Card) macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_sd4(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdSd4 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set Nand Flash macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_nf(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdNf = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set RELC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_relc(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdRelc = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set NETSEC macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_netsec(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdNetsec = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB2 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_usb2(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdUsb2 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set USB3 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_usb3(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdUsb3 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

/**
Set PCIE0 macro PD signal output of RAMCELL with PD.<br>
@param[in]  *val Setting value
					<ul><li> 0:Power-down mode is released.
						<li> 1:Enters Power-down mode.</ul>
@retval	None.
*/
void dd_exs_set_ram_pd_ctrl_pcie0(DdExs *self, kulong val)
{
	DD_ARM_CRITICAL_SECTION_START(S_DD_EXS_SPIN_LOCK);
	ioExstop.ramPd.bit.rampdPcie0 = val;
	DD_ARM_CRITICAL_SECTION_END(S_DD_EXS_SPIN_LOCK);
}

DdExs* dd_exs_get(void)
{
	static DdExs *ddExs = NULL;
	if(!ddExs)
	{
		ddExs = k_object_new_with_private(DD_TYPE_EXS,sizeof(DdExsPrivate));
	}
	return ddExs;
}
