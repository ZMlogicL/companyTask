/*
 * imdisp8.h
 *
 *  Created on: 2020年9月8日
 *      Author: sns
 */
#ifndef __IM_DISP8_H__
#define __IM_DISP8_H__

#include <klib.h>
#include "driver_common.h"
#include "dd_top.h"
#include "imdisp0.h"

#define IM_TYPE_DISP8				(im_disp8_get_type())
#define IM_DISP8(obj) 				(K_TYPE_CHECK_INSTANCE_CAST(obj, ImDisp8))
#define IM_IS_DISP8(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_DISP8))

typedef struct   _ImDisp8 			ImDisp8;
typedef struct   _ImDisp8Private		ImDisp8Private;

struct _ImDisp8 {
	KObject parent;
};

KConstType 		im_disp8_get_type(void);
ImDisp8*	im_disp8_new(void);

// Data Synchronization Barrier.
#define Im_DISP_Dsb()	Dd_ARM_Dsb_Pou()
// Signed register access macros.
#define D_IM_DISP_VSYNC_TIME	(33) // Vertical synchronization period
#define im_disp_set_word_bit(org_data, bit_patten, set_data) (org_data = ((org_data) & (~(bit_patten))) | ((set_data) & (bit_patten)))
// Check point debug print.
#ifdef CO_DEBUG_ON_PC
#define Im_DISP_Check_Point		Ddim_Print
#else
#define Im_DISP_Check_Point(dmy)
#endif
/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
#define D_DD_TOP_PCKDISPSTP_BIT	(0x00002000)	/**< PCLK_DISP */
#define D_DD_TOP_HCKDISPSTP_BIT	(0x00004000)	/**< HCLK_DISP */
// Return error as parameter error
#define D_IM_DISP_MACRO_BUSY_NG						(D_IM_DISP | D_DDIM_MACRO_BUSY_NG)		/**< Processing result code.<br> Macro busy.			*/
#define D_IM_DISP_TIMEOUT							(D_IM_DISP | D_DDIM_TIMEOUT)			/**< Processing result code.<br> Time out error			*/
#define D_IM_DISP_STATUS_ABNORMAL					(D_IM_DISP | D_DDIM_STATUS_ABNORMAL)	/**< Processing result code.<br> Abnormal Status		*/
#define D_IM_DISP_ACCESS_ERR						(D_IM_DISP | D_DDIM_ACCESS_ERR)			/**< Processing result code.<br> TRG cannot be set up.	*/
#define	D_IM_DISP_MAIN_ADDR_BANK_SIZE				(4)		/**< Bank size of main image address.		*/
#define	D_IM_DISP_GRBLINK_SIZE						(5)		/**< Word size of GRBLINK.					*/
// General-purpose definition of register value (Effectiveness selection)
#define D_IM_DISP_ENABLE_OFF						(0)		/**< OFF	*/
#define D_IM_DISP_ENABLE_ON							(1)		/**< ON		*/
// General-purpose definition of register value (Polarity selection)
#define D_IM_DISP_POLARITY_POSITIVE					(0)		/**< Positive polarity.	*/
#define D_IM_DISP_POLARITY_NEGATIVE					(1)		/**< Negative polarity.	*/
// IFS Register - IFS (Display I/F selection)*/
#define D_IM_DISP_IFS_NONE							(0)		/**< IFS.IFS Register<br> Not select.	*/
#define D_IM_DISP_IFS_LCD							(1)		/**< IFS.IFS Register<br> D-LCD I/F.	*/
#define D_IM_DISP_IFS_HDMI							(2)		/**< IFS.IFS Register<br> HDMI.			*/
#define D_IM_DISP_IFS_MIPI							(3)		/**< IFS.IFS Register<br> MIPI-DSI.		*/
// General-purpose definition of register value (Soft reset)
#define D_IM_DISP_SR_CANCEL							(0)		/**< Soft reset cancel.	*/
#define D_IM_DISP_SR_RESET							(1)		/**< Soft reset.		*/
// General-purpose definition of register value (Table surface)
#define D_IM_DISP_TABLE_SURFACE_A					(0)		/**< Table A surface.	*/
#define D_IM_DISP_TABLE_SURFACE_B					(1)		/**< Table B surface.	*/
// General-purpose definition of register value (IP selection)
#define D_IM_DISP_IP_HDMI							(1)		/**< HDMI IP.		*/
#define D_IM_DISP_IP_MIPI							(2)		/**< MIPI-DSI IP.	*/
// General-purpose definition of register value (Video format selection)
#define D_IM_DISP_FORMAT_NORMAL						(0)		/**< Normal format.	*/
#define D_IM_DISP_FORMAT_VIDEO						(1)		/**< Video format.	*/
// LIDT0 Register - IFMT (Input format selection)
#define D_IM_DISP_LIDT_IFMT_YCC422_RP_8BIT			(0)		/**< LIDT.IFMT Register<br> YCbCr422 respect point 8bit format.			*/
#define D_IM_DISP_LIDT_IFMT_YCC422_RP_12BIT_PACK	(1)		/**< LIDT.IFMT Register<br> YCbCr422 respect point 12bit format.		*/
#define D_IM_DISP_LIDT_IFMT_YCC422_RP_16BIT			(2)		/**< LIDT.IFMT Register<br> YCbCr422 respect point 16bit format.		*/
#define D_IM_DISP_LIDT_IFMT_YCC422_RP_10BIT_PACK	(3)		/**< LIDT.IFMT Register<br> YCbCr422 respect point 10bit format.		*/
#define D_IM_DISP_LIDT_IFMT_YCC420_RP_8BIT			(4)		/**< LIDT.IFMT Register<br> YCbCr420 respect point 8bit format.			*/
#define D_IM_DISP_LIDT_IFMT_YCC420_RP_10BIT_PACK	(7)		/**< LIDT.IFMT Register<br> YCbCr420 respect point 10bit format.		*/
#define D_IM_DISP_LIDT_IFMT_GENERAL_8BIT			(8)		/**< LIDT.IFMT Register<br> General purpose 8bit input data.			*/
#define D_IM_DISP_LIDT_IFMT_GENERAL_16BIT			(10)	/**< LIDT.IFMT Register<br> General purpose 16bit input data.			*/
#define D_IM_DISP_LIDT_IFMT_GENERAL_10BIT			(11)	/**< LIDT.IFMT Register<br> General purpose 10bit input data.			*/
#define D_IM_DISP_LIDT_IFMT_GENERAL_10BITx2			(27)	/**< LIDT.IFMT Register<br> General purpose 10bit input data (10bitx2).	*/
// LIDT0 Register - NBT (Burst size selection)
// GRIDT Register - NBT (Burst size selection)
#define D_IM_DISP_NBT_128BYTE						(0)		/**< LIDT.NBT Register<br> 128 byte forwarding. */
#define D_IM_DISP_NBT_256BYTE						(1)		/**< LIDT.NBT Register<br> 256 byte forwarding. */
#define D_IM_DISP_NBT_512BYTE						(2)		/**< LIDT.NBT Register<br> 512 byte forwarding. */
// LIDT0 Register - IFEW (Input format effective bit width selection)
#define D_IM_DISP_IFEW_16BIT						(0)		/**< LIDT.IFEW Register<br> 16bit.	*/
#define D_IM_DISP_IFEW_14BIT						(1)		/**< LIDT.IFEW Register<br> 14bit.	*/
#define D_IM_DISP_IFEW_12BIT						(2)		/**< LIDT.IFEW Register<br> 12bit.	*/
#define D_IM_DISP_IFEW_10BIT						(3)		/**< LIDT.IFEW Register<br> 10bit.	*/
// LIDT1 Register - YSLVSL, CSLVSL (Master interface selection)
#define D_IM_DISP_SLVSL_MASTER_INTERFACE_0			(0)		/**< LIDT.YWHMD, LIDT.CSLVSL Register<br> Master interface 0.	*/
#define D_IM_DISP_SLVSL_MASTER_INTERFACE_1			(1)		/**< LIDT.YWHMD, LIDT.CSLVSL Register<br> Master interface 1.	*/
// LBLTMR Register - BTIMD (Warning display period mode)
#define D_IM_DISP_BTIMD_NORMAL						(0)		/**< LBLTMR.BTIMD Register<br> Normal mode (Always display).	*/
#define D_IM_DISP_BTIMD_BLINK						(1)		/**< LBLTMR.BTIMD Register<br> Blink mode.						*/
// LBOST Register - BOMD (Warning display operation mode)
#define D_IM_DISP_BOMD_MASTER						(0)		/**< LBOST.BOMD Register<br> Master.	*/
#define D_IM_DISP_BOMD_SLAVE						(1)		/**< LBOST.BOMD Register<br> Slave.		*/
// LGMMD Register - GMMD (Gamma correct mode)
#define D_IM_DISP_GMMD_EQUAL_INTERVAL_MODE			(0)		/**< LGMMD.GMMD Register<br> Equal interval mode.		*/
#define D_IM_DISP_GMMD_UNEQUAL_INTERVALS_MODE		(1)		/**< LGMMD.GMMD Register<br> Unequal intervals mode.	*/
// LREVDISP Register - HREV (Horizontal reversing display selection)
// LREVDISP Register - VREV	(Vertical reversing display selection)
#define D_IM_DISP_REV_NORMAL						(0)		/**< LREVDISP.HREV, LREVDISP.VREV Register<br> Normal display.		*/
#define D_IM_DISP_REV_REVERSE						(1)		/**< LREVDISP.HREV, LREVDISP.VREV Register<br> Reversing display.	*/
// TOCTL Register - CON (Connection destination selection)
#define D_IM_DISP_CON_EXTERNAL						(0)		/**< TOCTL.CON Register<br> Connects relay terminal of the chip.	*/
#define D_IM_DISP_CON_INTERNAL						(1)		/**< TOCTL.CON Register<br> Connects other internal blocks.			*/
// INTC Register - VFTMG (Vsync detection interruption flag generation timing)
#define D_IM_DISP_VFTMG_NONE						(0)		/**< INTC.VFTMG Register<br> Flag is not generated.												*/
#define D_IM_DISP_VFTMG_1ST							(1)		/**< INTC.VFTMG Register<br> Flag is generated detecting the Vsync of the 1st field.			*/
#define D_IM_DISP_VFTMG_2ND							(2)		/**< INTC.VFTMG Register<br> Flag is generated detecting the Vsync of the 2nd field.			*/
#define D_IM_DISP_VFTMG_1ST_2ND						(3)		/**< INTC.VFTMG Register<br> Flag is generated detecting the Vsync of the 1st and 2nd field.	*/
// POLSEL Register - CKEG (Output clock edge selection)
#define D_IM_DISP_CKEG_FALL							(0)		/**< POLSEL.CKEG Register<br> Clock standing fall for external output. */
#define D_IM_DISP_CKEG_RISE							(1)		/**< POLSEL.CKEG Register<br> Clock standing up for external output. */
// TSL Register - TSL (Transmission mode)
#define D_IM_DISP_TSL_PROGRESSIVE					(0)		/**< TSL.TSL: Progressive.	*/
#define D_IM_DISP_TSL_INTERLACE						(1)		/**< TSL.TSL: Interlace.	*/
// VCYC Register - VDSFT (Vsync output 0.5H shift selection)
#define D_IM_DISP_VDSFT_NORMAL						(0)		/**< VCYC.VDSFT Register<br> Normal output.		*/
#define D_IM_DISP_VDSFT_SHIFT						(1)		/**< VCYC.VDSFT Register<br> 0.5H shift output.	*/
// OVPW Register - OVPWU (Vsync pulse width unit selection)
#define D_IM_DISP_OVPWU_CLOCK_UNIT					(0)		/**< OVPW.OVPWU Register<br> Output clock unit.	*/
#define D_IM_DISP_OVPWU_LINE_UNIT					(1)		/**< OVPW.OVPWU Register<br> Line count unit.	*/
// VRFCTL Register - VENS (Vertical enable signal assert timing selection)
#define D_IM_DISP_VENS_H_ENABLE						(0)		/**< VRFCTL.VENS Register<br> Horizontal enable signal.	*/
#define D_IM_DISP_VENS_HSYNC						(1)		/**< VRFCTL.VENS Register<br> Hsync.					*/
// HRFCTL Register - HENS (Selection of operation of the horizontal enable signal for period of vertical blank)
#define D_IM_DISP_HENS_ASSERT_ON					(0)		/**< HRFCTL.HENS Register<br> Asserted for the period of a vertical blank.		*/
#define D_IM_DISP_HENS_ASSERT_OFF					(1)		/**< HRFCTL.HENS Register<br> Not asserted for the period of a vertical blank.	*/
// DOMD Register - MODE (Output mode)
#define D_IM_DISP_MODE_RGB888_24BIT					(0x00)	/**< DOMD.MODE Register<br> RGB888 24bit									*/
#define D_IM_DISP_MODE_RGB888_30BIT					(0x01)	/**< DOMD.MODE Register<br> RGB888 30bit(10bit x3)							*/
#define D_IM_DISP_MODE_RGB888_36BIT					(0x02)	/**< DOMD.MODE Register<br> RGB888 36bit(12bit x3)							*/
#define D_IM_DISP_MODE_RGB888_8BIT_1				(0x04)	/**< DOMD.MODE Register<br> RGB888 8bit 1 (R0->G1->B2->R3->G4->B5->...)		*/
#define D_IM_DISP_MODE_RGB888_8BIT_2				(0x05)	/**< DOMD.MODE Register<br> RGB888 8bit 2 (R0->G0->B0->R1->G1->B1->...)		*/
#define D_IM_DISP_MODE_RGB888_8BIT_3				(0x06)	/**< DOMD.MODE Register<br> RGB888 8bit 3 (RGB-dummy)						*/
#define D_IM_DISP_MODE_RGB888_16BIT_1				(0x08)	/**< DOMD.MODE Register<br> RGB888 16bit 1 (R0G0->B0R1->G1B1->R2G2->...)	*/
#define D_IM_DISP_MODE_RGB888_16BIT_2				(0x09)	/**< DOMD.MODE Register<br> RGB888 16bit 2 (RGB-dummy)						*/
#define D_IM_DISP_MODE_RGB565_8BIT					(0x0C)	/**< DOMD.MODE Register<br> RGB565 8bit										*/
#define D_IM_DISP_MODE_RGB565_16BIT					(0x0D)	/**< DOMD.MODE Register<br> RGB565 16bit									*/
#define D_IM_DISP_MODE_RGB666_18BIT					(0x0E)	/**< DOMD.MODE Register<br> RGB666 18bit									*/
#define D_IM_DISP_MODE_YCC422_8BIT					(0x40)	/**< DOMD.MODE Register<br> YCbCr422 8bit									*/
#define D_IM_DISP_MODE_YCC422_16BIT					(0x41)	/**< DOMD.MODE Register<br> YCbCr422 16bit									*/
#define D_IM_DISP_MODE_YCC444_24BIT					(0x42)	/**< DOMD.MODE Register<br> YCbCr444 24bit									*/
#define D_IM_DISP_MODE_YCC422_20BIT					(0x43)	/**< DOMD.MODE Register<br> YCbCr422 20bit(10bit x2)						*/
#define D_IM_DISP_MODE_YCC422_24BIT					(0x44)	/**< DOMD.MODE Register<br> YCbCr422 24bit(10bit x2)						*/
#define D_IM_DISP_MODE_DEEP_YCC444_30BIT			(0x50)	/**< DOMD.MODE Register<br> Deep Color YCbCr444 30bit(10bit x3)				*/
#define D_IM_DISP_MODE_DEEP_YCC444_36BIT			(0x51)	/**< DOMD.MODE Register<br> Deep Color YCbCr444 36bit(12bit x3)				*/
#define D_IM_DISP_MODE_DUAL_YCC444_12BIT			(0x60)	/**< DOMD.MODE Register<br> Dual Edge YCbCr444 12bit						*/
#define D_IM_DISP_MODE_YCC420_24BIT					(0x70)	/**< DOMD.MODE Register<br> YCbCr420 24bit									*/
#define D_IM_DISP_MODE_YCC420_30BIT					(0x71)	/**< DOMD.MODE Register<br> YCbCr420 30bit(10bit x3)						*/
#define D_IM_DISP_MODE_GENERAL_8BIT					(0xF0)	/**< DOMD.MODE Register<br> General purpose 8bit							*/
#define D_IM_DISP_MODE_GENERAL_16BIT				(0xF1)	/**< DOMD.MODE Register<br> General purpose 16bit							*/
#define D_IM_DISP_MODE_GENERAL_10BIT_1				(0xF2)	/**< DOMD.MODE Register<br> General purpose 10bit 1							*/
#define D_IM_DISP_MODE_GENERAL_10BIT_2				(0xFA)	/**< DOMD.MODE Register<br> General purpose 10bit 2 (10bit x2)				*/
// DOMD Register - OBPSL (Output bit position selection)
#define D_IM_DISP_OBPSL_LSB							(0)		/**< DOMD.OBPSL Register<br> Outputs by LSB stuff.	*/
#define D_IM_DISP_OBPSL_MSB							(1)		/**< DOMD.OBPSL Register<br> Outputs by MSB stuff.	*/
// DOMD Register - OBUSL (Output bit unit selection)
#define D_IM_DISP_OBUSL_8BIT						(0)		/**< DOMD.OBUSL Register<br> Outputs by 8bit unit.	*/
#define D_IM_DISP_OBUSL_12BIT						(2)		/**< DOMD.OBUSL Register<br> Outputs by 12bit unit.	*/
#define D_IM_DISP_OBUSL_16BIT						(3)		/**< DOMD.OBUSL Register<br> Outputs by 16bit unit.	*/
// BLDCTL Register - BLD1~4 (Blend order layer selection)
#define D_IM_DISP_BLD_GRID							(0)		/**< BLDCTL.BLD1~4 Register<br> Grid layer			*/
#define D_IM_DISP_BLD_FACE							(1)		/**< BLDCTL.BLD1~4 Register<br> Face frame layer	*/
#define D_IM_DISP_BLD_OSD0							(2)		/**< BLDCTL.BLD1~4 Register<br> OSD data 0 layer	*/
#define D_IM_DISP_BLD_OSD1							(3)		/**< BLDCTL.BLD1~4 Register<br> OSD data 1 layer	*/
// R2RCTL Register - R2REN (RGB->RGB matrix enable)
#define D_IM_DISP_R2REN_DISABLE						(0)		/**< R2RCTL.R2REN Register<br> RGB->RGB matrix disable	*/
#define D_IM_DISP_R2REN_ENABLE						(1)		/**< R2RCTL.R2REN Register<br> RGB->RGB matrix enable	*/
// YCTL Register - YLPF (Y data LPF)
#define D_IM_DISP_YLPF_DISABLE						(0)		/**< YCTL.YLPF Register<br> Y data LPF disable	*/
#define D_IM_DISP_YLPF_ENABLE						(1)		/**< YCTL.YLPF Register<br> Y data LPF enable	*/
// DOCTL0 Register - DTO1~6 (Data output order selection)
#define D_IM_DISP_DTO_R_Y0							(0)		/**< DOCTL0.DTO1~6 Register<br> R (or Y0)	*/
#define D_IM_DISP_DTO_G_CB							(1)		/**< DOCTL0.DTO1~6 Register<br> G (or CB)	*/
#define D_IM_DISP_DTO_B_CR							(2)		/**< DOCTL0.DTO1~6 Register<br> B (or CR)	*/
#define D_IM_DISP_DTO_0_Y1							(3)		/**< DOCTL0.DTO1~6 Register<br> 00h (or Y1)	*/
// DOCTL2 Register - CLVS (CbCr data output level selection)
#define D_IM_DISP_CLVS_NORMAL						(0)		/**< DOCTL2.CLVS Register<br> Normal output	*/
#define D_IM_DISP_CLVS_SIGNED						(1)		/**< DOCTL2.CLVS Register<br> Signed output	*/
// DOCTL2 Register - CTOH (Horizontal CbCr off selection)
#define D_IM_DISP_CTOH_LEFT							(0)		/**< DOCTL2.CTOH Register<br> Left CbCr data is selected.						*/
#define D_IM_DISP_CTOH_RIGHT						(1)		/**< DOCTL2.CTOH Register<br> Right CbCr data is selected.						*/
#define D_IM_DISP_CTOH_AVERAGE						(2)		/**< DOCTL2.CTOH Register<br> Average of right and left CbCr data is selected.	*/
#define D_IM_DISP_CTOH_FILTER						(3)		/**< DOCTL2.CTOH Register<br> 1:2:1 filter Calculation CbCr data is selected.	*/
// DOCTL2 Register - CTOV (Vertical CbCr off selection)
#define D_IM_DISP_CTOV_TOP							(0)		/**< DOCTL2.CTOV Register<br> Top CbCr data is selected.						*/
#define D_IM_DISP_CTOV_AVERAGE						(1)		/**< DOCTL2.CTOV Register<br> Average of top and bottom CbCr data is selected.	*/
// DOCTL2 Register - TRSOS (SAV/EAV code output selection)
#define D_IM_DISP_TRSOS_NONE						(0)		/**< DOCTL2.TRSOS Register<br> SAV/EAV code is not output.					*/
#define D_IM_DISP_TRSOS_15_8						(1)		/**< DOCTL2.TRSOS Register<br> SAV/EAV code is output to [15:8].			*/
#define D_IM_DISP_TRSOS_7_0							(2)		/**< DOCTL2.TRSOS Register<br> SAV/EAV code is output to [7:0].				*/
#define D_IM_DISP_TRSOS_BOTH						(3)		/**< DOCTL2.TRSOS Register<br> SAV/EAV code is output to [15:8] and [7:0].	*/
// GRIDT Register - IFMT (Input format selection)
#define D_IM_DISP_GRIDT_IFMT_RGBA8888				(0)		/**< GRIDT.IFMT Register<br> RGBA8888 format.				*/
#define D_IM_DISP_GRIDT_IFMT_YCC422					(1)		/**< GRIDT.IFMT Register<br> YCbCr422 format.				*/
#define D_IM_DISP_GRIDT_IFMT_RGBA4444				(2)		/**< GRIDT.IFMT Register<br> RGBA4444 format.				*/
#define D_IM_DISP_GRIDT_IFMT_RGB565					(3)		/**< GRIDT.IFMT Register<br> RGB565 format.					*/
#define D_IM_DISP_GRIDT_IFMT_RGBA5551				(4)		/**< GRIDT.IFMT Register<br> RGBA5551 format.				*/
#define D_IM_DISP_GRIDT_IFMT_YCC422_A4				(3)		/**< GRIDT.IFMT Register<br> YCbCr422 A4 surface format.	*/
#define D_IM_DISP_GRIDT_IFMT_YCC422_A8				(4)		/**< GRIDT.IFMT Register<br> YCbCr422 A8 surface format.	*/
// GRIDT Register - IFBTMU (Input format bottom-up selection)
#define D_IM_DISP_IFBTMU_UP_TO_BOTTOM				(0)		/**< GRIDT.IFBTMU Register<br> Format arranged from up to bottom.	*/
#define D_IM_DISP_IFBTMU_BOTTOM_TO_UP				(1)		/**< GRIDT.IFBTMU Register<br> Format arranged from bottom to up.	*/
// GRIPO Register - IPO1~4 (Input data arrangement order setting)
#define D_IM_DISP_IPO_RGBA8888_R					(0)		/**< GRIPO.IPO1~4 Register<br> R data in RGBA8888 format.				*/
#define D_IM_DISP_IPO_RGBA8888_G					(1)		/**< GRIPO.IPO1~4 Register<br> G data in RGBA8888 format.				*/
#define D_IM_DISP_IPO_RGBA8888_B					(2)		/**< GRIPO.IPO1~4 Register<br> B data in RGBA8888 format.				*/
#define D_IM_DISP_IPO_RGBA8888_A					(3)		/**< GRIPO.IPO1~4 Register<br> A data in RGBA8888 format.				*/
#define D_IM_DISP_IPO_YCC422_CB						(0)		/**< GRIPO.IPO1~4 Register<br> Cb data in YCbCr422 format.				*/
#define D_IM_DISP_IPO_YCC422_Y0						(1)		/**< GRIPO.IPO1~4 Register<br> Y0 data in YCbCr422 format.				*/
#define D_IM_DISP_IPO_YCC422_CR						(2)		/**< GRIPO.IPO1~4 Register<br> Cr data in YCbCr422 format.				*/
#define D_IM_DISP_IPO_YCC422_Y1						(3)		/**< GRIPO.IPO1~4 Register<br> Y1 data in YCbCr422 format.				*/
#define D_IM_DISP_IPO_RGBA4444_B0_A0				(0)		/**< GRIPO.IPO1~4 Register<br> {B0, A0} data in RGBA4444 format.		*/
#define D_IM_DISP_IPO_RGBA4444_R0_G0				(1)		/**< GRIPO.IPO1~4 Register<br> {R0, G0} data in RGBA4444 format.		*/
#define D_IM_DISP_IPO_RGBA4444_B1_A1				(2)		/**< GRIPO.IPO1~4 Register<br> {B1, A1} data in RGBA4444 format.		*/
#define D_IM_DISP_IPO_RGBA4444_R1_G1				(3)		/**< GRIPO.IPO1~4 Register<br> {R1, G1} data in RGBA4444 format.		*/
#define D_IM_DISP_IPO_RGB565_G0_B0					(0)		/**< GRIPO.IPO1~4 Register<br> {G0[2:0],B0} data in RGB565 format.		*/
#define D_IM_DISP_IPO_RGB565_R0_G0					(1)		/**< GRIPO.IPO1~4 Register<br> {R0,G0[5:3]} data in RGB565 format.		*/
#define D_IM_DISP_IPO_RGB565_G1_B1					(2)		/**< GRIPO.IPO1~4 Register<br> {G1[2:0],B1} data in RGB565 format.		*/
#define D_IM_DISP_IPO_RGB565_R1_G1					(3)		/**< GRIPO.IPO1~4 Register<br> {R1,G1[5:3]} data in RGB565 format.		*/
#define D_IM_DISP_IPO_RGBA5551_G0_B0_A0				(0)		/**< GRIPO.IPO1~4 Register<br> {G0[1:0],B0,A0} data in RGBA5551 format.	*/
#define D_IM_DISP_IPO_RGBA5551_R0_G0				(1)		/**< GRIPO.IPO1~4 Register<br> {R0,G0[4:2]} data in RGBA5551 format.	*/
#define D_IM_DISP_IPO_RGBA5551_G1_B1_A1				(2)		/**< GRIPO.IPO1~4 Register<br> {G1[1:0],B1,A1} data in RGBA5551 format.	*/
#define D_IM_DISP_IPO_RGBA5551_R1_G1				(3)		/**< GRIPO.IPO1~4 Register<br> {R1,G1[4:2]} data in RGBA5551 format.	*/
// GRBITRG Register - BITRG (Blink sync trigger)
#define D_IM_DISP_BITRG_NON							(0)		/**< GRBITRG.BITRG Register<br> Write:No operation, Read: -.						*/
#define D_IM_DISP_BITRG_WRITE_SYNC_WAIT				(1)		/**< GRBITRG.BITRG Register<br> Write:Blink sync reflect wait ON, Read: -.			*/
#define D_IM_DISP_BITRG_READ_STOP					(2)		/**< GRBITRG.BITRG Register<br> Write:No operation, Read:stop.						*/
#define D_IM_DISP_BITRG_READ_SYNC_WAIT				(3)		/**< GRBITRG.BITRG Register<br> Write:No operation, Read:Blink sync reflect wait.	*/
// MDSIC1 Register - MDSUDC (UpDateConfiguration input control)
#define D_IM_DISP_MDSUDC_NON						(0)		/**< MDSIC1.MDSUDC Register<br> Write:No operation, Read: -.							*/
#define D_IM_DISP_MDSUDC_WRITE_1SHOT				(1)		/**< MDSIC1.MDSUDC Register<br> Write:DPIUPDATECFG_I 1shot signal input, Read: -.		*/
#define D_IM_DISP_MDSUDC_READ_STOP					(2)		/**< MDSIC1.MDSUDC Register<br> Write:No operation, Read:stop.							*/
#define D_IM_DISP_MDSUDC_READ_UPDATE_WAIT			(3)		/**< MDSIC1.MDSUDC Register<br> Write:No operation, Read:DPI configuration update wait.	*/
// Clock On/Off
#define D_IM_DISP_CLKSTOP3_DISPAP_ON				(0x00008000)	/**< CLKSTOP3 - DISPAP[15:14] = 10	*/
#define D_IM_DISP_CLKSTOP3_DISPAP_OFF				(0x0000C000)	/**< CLKSTOP3 - DISPAP[15:14] = 11	*/
#define D_IM_DISP_CLKSTOP3_DISPAH_ON				(0x00020000)	/**< CLKSTOP3 - DISPAH[17:16] = 10	*/
#define D_IM_DISP_CLKSTOP3_DISPAH_OFF				(0x00030000)	/**< CLKSTOP3 - DISPAH[17:16] = 11	*/

/** Control layer selection. (Bit flag) */
typedef enum {
	// None
	E_IM_DISP_SEL_LAYER_NONE      = 0x0000,								/**< None							*/
	E_IM_DISP_SEL_LAYER_MAIN      = 0x0001,								/**< Main data input block.			*/
	E_IM_DISP_SEL_LAYER_DCORE     = 0x0002,								/**< Data output block.				*/
	E_IM_DISP_SEL_LAYER_OSD_0     = 0x0004,								/**< OSD-0 data input block.		*/
	E_IM_DISP_SEL_LAYER_OSD_1     = 0x0008,								/**< OSD-1 data input block.		*/
	// OSD
	E_IM_DISP_SEL_LAYER_OSD_ALL   = (E_IM_DISP_SEL_LAYER_OSD_0  |
									 E_IM_DISP_SEL_LAYER_OSD_1),		/**< ALL OSD data input blocks.		*/
	// ALL
	E_IM_DISP_SEL_LAYER_ALL       = (E_IM_DISP_SEL_LAYER_MAIN  |
									 E_IM_DISP_SEL_LAYER_DCORE |
									 E_IM_DISP_SEL_LAYER_OSD_0 |
									 E_IM_DISP_SEL_LAYER_OSD_1)			/**< ALL blocks.					*/
} E_IM_DISP_SEL_LAYER;

// OSD layer ID
static volatile const INT32 osd_layer_id[] = {
		E_IM_DISP_SEL_LAYER_OSD_0, E_IM_DISP_SEL_LAYER_OSD_1};

/** LCEPMD Register - CEPMD (Color difference data padding mode) */
typedef enum {
	E_IM_DISP_CEPMD_UPPER_SIDE			= 0,	/**< LCEPMD.CEPMD Register<br> Select the upper side of the color difference data							*/
	E_IM_DISP_CEPMD_AVERAGE				= 2,	/**< LCEPMD.CEPMD Register<br> Select the average value of the top and bottom of the color difference data	*/
	E_IM_DISP_CEPMD_3TO1_1TO3_RATE		= 3		/**< LCEPMD.CEPMD Register<br> Select a value calculated the top and bottom
																			   of the color difference data at a rate of 3:1 and 1:3						*/
} E_IM_DISP_CEPMD;

/** LYWCTL Register - YWSL (Warning type select) */
typedef enum {
	E_IM_DISP_YWSL_BRIGHTNESS_SPECIFIED_COLOR	= 0,	/**< LYWCTL.YWSL Register<br> Brightness warning - Specified color	*/
	E_IM_DISP_YWSL_BRIGHTNESS_ZEBRA				= 1,	/**< LYWCTL.YWSL Register<br> Brightness warning - Zebra			*/
	E_IM_DISP_YWSL_RGB_SPECIFIED_COLOR			= 2,	/**< LYWCTL.YWSL Register<br> RGB warning - Specified color			*/
	E_IM_DISP_YWSL_RGB_ZEBRA					= 3		/**< LYWCTL.YWSL Register<br> RGB warning - Zebra					*/
} E_IM_DISP_YWSL;

/** Bank index. */
typedef enum {
	E_IM_DISP_BANK_00 = 0,	/**< Bank 0	*/
	E_IM_DISP_BANK_01,		/**< Bank 1 */
	E_IM_DISP_BANK_10,		/**< Bank 2 */
	E_IM_DISP_BANK_11,		/**< Bank 3 */
} E_IM_DISP_BANK;

/** LCC0/LCC1/LCC2. */
typedef union {
	LLONG		dword;	/**< All bits */
	struct {
		LLONG	CC0		:12;	/**< CC00/: Color space conversion matrix coefficient 0.<br>
									 Value range:-128~127(-2.0~1.984)						*/
		LLONG			:4;		/**< Reserve												*/
		LLONG	CC1		:12;	/**< CC1: Color space conversion matrix coefficient 1.<br>
									 Value range:-128~127(-2.0~1.984)						*/
		LLONG			:4;		/**< Reserve												*/
		LLONG	CC2		:12;	/**< CC2: Color space conversion matrix coefficient 2.<br>
									 Value range:-128~127(-2.0~1.984)						*/
		LLONG			:20;	/**< Reserve												*/
	}bit;	/**< Bit field */
}U_IM_DISP_LCC;

/** Channel input buffer size. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	width	:16;	/**< Horizontal size<br>
									 Value range:<br>
									 LISIZE.IHSIZE=128~65534 (2-byte unit)<br>
									 GRTISIZE.TIHSIZE=8~65534 (2-byte unit)<br>
									 GRISIZE.IHSIZE=8~65532 (4-byte unit)		*/
		ULONG	lines	:14;	/**< Vertical size<br>
									 Value range:<br>
									 LISIZE.IVSIZE=16~16382 (2-byte unit)<br>
									 GRTISIZE.TIVSIZE=8~16382 (2-byte unit)<br>
									 GRISIZE.IVSIZE=8~16382 (2-byte unit)		*/
		ULONG			:2;		/**< Reserve									*/
	}size;	/**< bit field */
} U_IM_DISP_SIZE;

/**
Control data of main data input block.<br>
It is possible to rewrite it while main data input block is operating.
*/
typedef struct {
	// Data input control register area.
	U_IM_DISP_LIDT					lidt;									/**< LIDT0~1: Input data forwarding setting register.<br>						*/
	U_IM_DISP_SIZE					lisize;									/**< LISIZE: Input data size setting register.<br>								*/
	T_IM_DISP_IMAGE_ADDR			laddr[D_IM_DISP_MAIN_ADDR_BANK_SIZE];	/**< LYSA0~3, LCSA0~3: Input address setting register.<br>						*/
	ULONG							y_hga;									/**< Horizontal global area of Y data.<br>
																				 Value range:2~65535<br>
																				 Bit depth=8bit -> 2-byte unit<br>
																				 Bit depth=12bit -> 3-byte unit<br>
																				 Bit depth=16bit -> 4-byte unit		 										*/
	ULONG							c_hga;									/**< Horizontal global area of CbCr data.<br>
																				 Value range:2~65535<br>
																				 Bit depth=8bit -> 2-byte unit<br>
																				 Bit depth=12bit -> 3-byte unit<br>
																				 Bit depth=16bit -> 4-byte unit		 										*/
	UINT32							libctl_iben;							/**< LIBCTL.IBEN: Input bank specification method selection (0 fixation).<br>	*/
	E_IM_DISP_BANK					libctl_ibset;							/**< LIBCTL.IBSET: Input bank specification.<br>
																				 <ul><li>@ref E_IM_DISP_BANK_00
																				     <li>@ref E_IM_DISP_BANK_01
																					 <li>@ref E_IM_DISP_BANK_10
																					 <li>@ref E_IM_DISP_BANK_11</ul>										*/
	// Data processing setting register area.
	E_IM_DISP_RSZSL					lrsz0;									/**< LRSZ0: Horizontal resize setting register - 0.<br>
																				 <ul><li>@ref E_IM_DISP_RSZSL_PADDING_THINNING
																					 <li>@ref E_IM_DISP_RSZSL_BILINEAR</ul>									*/
	U_IM_DISP_RSZ1					lrsz1;									/**< LRSZ1: Resize data 1 (Horizontal)											*/
	U_IM_DISP_RSZ2					lrsz2;									/**< LRSZ2: Resize data 2 (Vertical)											*/
	U_IM_DISP_RSZ3					lrsz3;									/**< LRSZ3: Resize data 3 (chrominance start position)							*/
	T_IM_DISP_YHLP					yhlp;									/**< YHLP data register.														*/
	T_IM_DISP_WARNING				warning;								/**< Warning processing setting register.										*/
	U_IM_DISP_LBLTMR				lbltmr;									/**< Luminance warning display period setting register.							*/
	T_IM_DISP_ZEBRA					zebra;									/**< LZBWID/LZBV/LZBPT: Zebra data register.									*/
	U_IM_DISP_YR_MATRIX_COEFFICIENT	ly2r[D_IM_DISP_MATRIX_SIZE];			/**< LY2R0/1/2: YCbCr->RGB matrix coefficient setting register.					*/
	E_IM_DISP_CORRECT_PROC			ltblaset_igen;							/**< LTBLASET.IGEN: Anti-gamma correction enable.<br>
																				 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
																					 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>							*/
	BYTE							ltblaset_igtsl;							/**< LTBLASET.IGTSL: Inverse gamma correction table surface.<br>
																				 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
																					 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>								*/
	E_IM_DISP_CORRECT_PROC			ltblaset_gmen;							/**< LTBLASET.GMEN: Gamma correction enable.<br>
																				 <ul><li>@ref E_IM_DISP_CORRECT_PROC_DISABLE
																					 <li>@ref E_IM_DISP_CORRECT_PROC_ENABLE</ul>							*/
	BYTE							ltblaset_gmtsl;							/**< LTBLASET.GMTSL: Gamma correction table surface.<br>
																				 <ul><li>@ref D_IM_DISP_TABLE_SURFACE_A
																					 <li>@ref D_IM_DISP_TABLE_SURFACE_B</ul>								*/
	U_IM_DISP_LCC					lcc[D_IM_DISP_MATRIX_SIZE];				/**< LCC0/1/2: Color space conversion matrix coefficient setting register.		*/
	U_IM_DISP_LGMMD					lgmmd;									/**< LGMMD: Gamma correct mode . */
	U_IM_DISP_LALP					lalp;									/**< LALP: Alpha value setting register. Value range:0x000~0xFF.				*/
	// Display area setting register area.
	U_IM_DISP_DSTA					ldsta;									/**< LDSTA: Display starting position setting register.							*/
	U_IM_DISP_LREVDISP				lrevdisp;								/**< LREVDISP: Reversing display selection register.							*/
} T_IM_DISP_CTRL_MAIN_LAYER;

/**	GRIDT register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	IFMT	:3;	/**< IFMT: Input format selection.<br>
								 <ul><li>@ref D_IM_DISP_GRIDT_IFMT_RGBA8888
								     <li>@ref D_IM_DISP_GRIDT_IFMT_YCC422
								     <li>@ref D_IM_DISP_GRIDT_IFMT_RGBA4444
								     <li>@ref D_IM_DISP_GRIDT_IFMT_RGB565
									 <li>@ref D_IM_DISP_GRIDT_IFMT_RGBA5551
									 <li>@ref D_IM_DISP_GRIDT_IFMT_YCC422_A4
									 <li>@ref D_IM_DISP_GRIDT_IFMT_YCC422_A8</ul>								*/
		ULONG			:1;	/**< Reserve																		*/
		ULONG	NBT		:2;	/**< NBT: Burst size selection.<br>
								 <ul><li>@ref D_IM_DISP_NBT_128BYTE
									 <li>@ref D_IM_DISP_NBT_256BYTE</ul>										*/
		ULONG			:10;/**< Reserve																		*/
		ULONG	CACHE	:4;	/**< CACHE: Cache type.<br>
								 d[0]:Bufferable bit. Value 0:Nonbufferable, 1:Bufferable.<br>
								 d[1]:Cacheable bit. Value 0:Noncacheable, 1:Cacheable.<br>
								 d[2]:Read allocate bit. Value 0:Read through, 1:Allocate on Reads.<br>
								 d[3]:Write allocate bit. Value 0:Write through, 1:Allocate on writes.<br>		*/
		ULONG	PROT	:3;	/**< PROT: Protect type.<br>
								 d[0]:Normal or privileged. Value 0:Normal access, 1:Privileged access.<br>
								 d[1]:Secure or non-secure. Value 0:Secure access, 1:Non-secure access.<br>
								 d[2]:Instruction or Data. Value 0:Data access, 1:Instrauction access.<br>		*/
		ULONG			:1;	/**< Reserve																		*/
		ULONG	SLVSL	:1;	/**< SLVSL: Master interface selection.<br> D_IM_DISP_SLVSL_MASTER_INTERFACE_0
								 <ul><li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_0
									 <li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_1</ul>							*/
		ULONG	ASLVSL	:1;	/**< ASLVSL: A component master interface selection.<br>
								 If format is YCbCr422 A4 surface or YCbCr422 A8 surface, this bit is enable.<br>
								 <ul><li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_0
									 <li>@ref D_IM_DISP_SLVSL_MASTER_INTERFACE_1</ul>							*/
		ULONG			:2;	/**< Reserve																		*/
		ULONG	IFBTMU	:1;	/**< IFBTMU: Input format bottom-up selection.<br>
								 <ul><li>@ref D_IM_DISP_IFBTMU_UP_TO_BOTTOM
									 <li>@ref D_IM_DISP_IFBTMU_BOTTOM_TO_UP</ul>								*/
		ULONG			:3;	/**< Reserve																		*/
	} bit;	/**< Bit field */
} U_IM_DISP_GRIDT;

/**	GRIPO register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	IPO1	:2;	/**< IPO1: Input data arrangement order 1 setting.<br>
								 <ul><li>@ref D_IM_DISP_IPO_RGBA8888_R
									 <li>@ref D_IM_DISP_IPO_RGBA8888_G
									 <li>@ref D_IM_DISP_IPO_RGBA8888_B
									 <li>@ref D_IM_DISP_IPO_RGBA8888_A
									 <li>@ref D_IM_DISP_IPO_YCC422_CB
									 <li>@ref D_IM_DISP_IPO_YCC422_Y0
									 <li>@ref D_IM_DISP_IPO_YCC422_CR
									 <li>@ref D_IM_DISP_IPO_YCC422_Y1
									 <li>@ref D_IM_DISP_IPO_RGBA4444_B0_A0
									 <li>@ref D_IM_DISP_IPO_RGBA4444_R0_G0
									 <li>@ref D_IM_DISP_IPO_RGBA4444_B1_A1
									 <li>@ref D_IM_DISP_IPO_RGBA4444_R1_G1
									 <li>@ref D_IM_DISP_IPO_RGB565_G0_B0
									 <li>@ref D_IM_DISP_IPO_RGB565_R0_G0
									 <li>@ref D_IM_DISP_IPO_RGB565_G1_B1
									 <li>@ref D_IM_DISP_IPO_RGB565_R1_G1
									 <li>@ref D_IM_DISP_IPO_RGBA5551_G0_B0_A0
									 <li>@ref D_IM_DISP_IPO_RGBA5551_R0_G0
									 <li>@ref D_IM_DISP_IPO_RGBA5551_G1_B1_A1
									 <li>@ref D_IM_DISP_IPO_RGBA5551_R1_G1</ul>		*/
		ULONG			:6;	/**< Reserve											*/
		ULONG	IPO2	:2;	/**< IPO2: Input data arrangement order 2 setting.<br>
								 The value that can be selected is the same as IPO1.*/
		ULONG			:6;	/**< Reserve											*/
		ULONG	IPO3	:2;	/**< IPO3: Input data arrangement order 3 setting.<br>
								 The value that can be selected is the same as IPO1.*/
		ULONG			:6;	/**< Reserve											*/
		ULONG	IPO4	:2;	/**< IPO4: Input data arrangement order 4 setting.<br>
								 The value that can be selected is the same as IPO1.*/
		ULONG			:6;	/**< Reserve											*/
	} bit;	/**< Bit field */
} U_IM_DISP_GRIPO;

/**	GRBLINK register structure. */
typedef union {
	ULONG		word[5];	/**< All bits */
	struct {
		USHORT	BTIMH_0	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_0	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_1	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_1	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_2	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_2	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_3	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_3	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_4	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_4	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_5	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_5	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_6	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_6	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_7	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_7	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_8	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_8	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIMH_9	:6;	/**< BTIMH: Setting at blink display period.<br>
								 Value range:0~63<br>
								 BTIMH = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
		USHORT	BTIML_9	:6;	/**< BTIML: Setting at blink non-display period.<br>
								 Value range:0~63<br>
								 BTIML = frame cout - 1.						*/
		USHORT			:2;	/**< Reserve										*/
	}bit;	/**< Bit field */
} U_IM_DISP_GRBLINK;

/** GRY2R0/GRY2R1/GRY2R2. */
typedef union {
	LONG		word;	/**< All bits */
	struct {
		LONG	YR0		:8;	/**< YR00/YR10/YR20: YCbCr -> RGB matrix coefficient 0.<br>
								 Value range:-128~127(-2.0~1.984)						*/
		LONG	YR1		:8;	/**< YR01/YR11/YR21: YCbCr -> RGB matrix coefficient 0.<br>
								 Value range:-128~127(-2.0~1.984)						*/
		LONG	YR2		:8;	/**< YR02/YR12/YR22: YCbCr -> RGB matrix coefficient 0.<br>
								 Value range:-128~127(-2.0~1.984)						*/
		LONG			:8;	/**< Reserve												*/
	}bit;	/**< Bit field */
}U_IM_DISP_GRY2R;

/**
Control data of Grid.<br>
It is possible to rewrite it while data output block is operating.
*/
typedef struct {
	T_IM_DISP_GRID			grid;		/**< Grid display parameter.<br>					*/
	E_IM_DISP_GDISPEN		gdispen;	/**< GDISPEN: Grid display enable register.<br>
											 <ul><li>@ref E_IM_DISP_GDISPEN_NOT_DISPLAY
												 <li>@ref E_IM_DISP_GDISPEN_DISPLAY</ul>	*/
} T_IM_DISP_CTRL_GRID_LAYER;

/**
Control data of OSD data input block.<br>
It is possible to rewrite it while OSD data input block is operating.
*/
typedef struct {
	// Data input control register area.
	U_IM_DISP_GRIDT					gridt;										/**< GRIDT: Input data forwarding setting register.<br>								*/
	U_IM_DISP_SIZE					grtisize;									/**< GRTISIZE: Input area size setting register.<br>								*/
	U_IM_DISP_DSTA					grtdsta;									/**< GRTDSTA: Area display start position setting register.<br>						*/
	U_IM_DISP_GRIPO					gripo;										/**< GRIPO: Input data arrangement order setting register.<br>						*/
	E_IM_DISP_INPUT_DATA_AREA		grscctl_idset;								/**< GRSCCTL.IDSET: Input data arrangement order setting register.<br>
																					 <ul><li>@ref E_IM_DISP_INPUT_DATA_AREA_0
																						 <li>@ref E_IM_DISP_INPUT_DATA_AREA_1
																						 <li>@ref E_IM_DISP_INPUT_DATA_AREA_2
																						 <li>@ref E_IM_DISP_INPUT_DATA_AREA_3</ul>									*/
	// Display area setting register area.
	U_IM_DISP_SIZE					grisize[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];	/**< GRISIZE: Input data size setting register.<br>									*/
	ULONG							grsa0[D_IM_DISP_OSD_ADDR_0_BANK_SIZE];		/**< GRSA0: Processing start address setting 0 register.<br>
																					 Value range:0x00000000~0xFFFFFFFF (8-bytel unit)								*/
	ULONG							grsa[D_IM_DISP_OSD_ADDR_BANK_SIZE];			/**< GRSA: Processing start address setting register.<br>
																					 Value range:0x00000000~0xFFFFFFFF (8-bytel unit)								*/
	ULONG							grasa[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];	/**< GRASA: A deta Processing start address setting register.<br>
																					 Value range:0x00000000~0xFFFFFFFF (8-bytel unit)								*/
	ULONG							grhga[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];	/**< GRHGA: Horizontal global area.<br>
																					 Value range:8~65528 (8-bytel unit)												*/
	ULONG							grahga[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];	/**< GRAHGA: A deta horizontal global area.<br>
																					 Value range:8~65528 (8-bytel unit)												*/
	U_IM_DISP_DSTA					grdsta[D_IM_DISP_OSD_DISPLAY_AREA_COUNT];	/**< GRDSTA: Display starting position setting registers.<br>						*/
	ULONG							graren;										/**< GRAREN: Display enable setting register.<br>
																					 bit d[0]:AREN0 ~ d[9]:AREN9<br>
																					 Value 0:disable, 1:enable<br>													*/
	ULONG							grbsl;										/**< GRBSL: Blink method setting register.<br>
																					 bit d[0]:BSL0 ~ d[9]:BSL9<br>
																					 Value 0:not blink, 1:blink<br>													*/
	U_IM_DISP_GRBLINK				grblink;									/**< GRBLINK: Blink setting register.<br>											*/
	ULONG							grbinit;									/**< GRBINIT: Blink sync setting register.<br>
																					 bit d[0]:AREN0 ~ d[9]:AREN9<br>
																					 Value 0:not blink sync, 1:blink sync<br>										*/
	ULONG							grbitrg;									/**< GRBITRG: Blink sync trigger register.<br>
																					 <ul><li>@ref D_IM_DISP_BITRG_NON
																						 <li>@ref D_IM_DISP_BITRG_WRITE_SYNC_WAIT
																						 <li>@ref D_IM_DISP_BITRG_READ_STOP
																						 <li>@ref D_IM_DISP_BITRG_READ_SYNC_WAIT</ul>								*/
	// Data processing setting register area.
	E_IM_DISP_RSZSL					grrsz0;										/**< GRRSZ0: Horizontal resize setting register - 0.<br>
																					 <ul><li>@ref E_IM_DISP_RSZSL_PADDING_THINNING
																						 <li>@ref E_IM_DISP_RSZSL_BILINEAR</ul>										*/
	U_IM_DISP_RSZ1					grrsz1;										/**< GRRSZ1: Resize data 1 (Horizontal).<br>										*/
	U_IM_DISP_RSZ2					grrsz2;										/**< GRRSZ2: Resize data 2 (Vertical).<br>											*/
	U_IM_DISP_RSZ3					grrsz3;										/**< GRRSZ3: Resize data 3 (chrominance start position).<br>						*/
	U_IM_DISP_GRY2R					gry2r[D_IM_DISP_MATRIX_SIZE];				/**< GRY2R0/1/2: YCbCr->RGB matrix coefficient setting register.<br>				*/
	ULONG							gralp;										/**< GRALP: Alpha value setting register.<br>
																					 Value range:0~255																*/
} T_IM_DISP_CTRL_OSD_LAYER;

/**	TOCTL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	CON		:1;	/**< CON: Connection destination selection.
								 <ul><li>@ref D_IM_DISP_CON_EXTERNAL
									 <li>@ref D_IM_DISP_CON_INTERNAL</ul>		*/
		ULONG			:7;	/**< Reserve										*/
		ULONG	CKOEN	:1;	/**< CKOEN: Output clock oscillation permission (for external output)
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG	CKICEN	:1;	/**< CKICEN: Output clock oscillation permission (for internal connection)
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:6;	/**< Reserve										*/
		ULONG	WBEN	:1;	/**< WBEN: Write back permission
								 <ul><li>@ref D_IM_DISP_ENABLE_OFF
									 <li>@ref D_IM_DISP_ENABLE_ON</ul>			*/
		ULONG			:15;/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_TOCTL;

/**	POLSEL register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	VDPS	:1;	/**< VDPS: Vsync polarity selection.
								 <ul><li>@ref D_IM_DISP_POLARITY_POSITIVE
									 <li>@ref D_IM_DISP_POLARITY_NEGATIVE</ul>	*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	HDPS	:1;	/**< HDPS: Hsync polarity selection.
								 <ul><li>@ref D_IM_DISP_POLARITY_POSITIVE
									 <li>@ref D_IM_DISP_POLARITY_NEGATIVE</ul>	*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	VEPS	:1;	/**< VEPS: Vertical enable signal polarity selection.
								 <ul><li>@ref D_IM_DISP_POLARITY_POSITIVE
									 <li>@ref D_IM_DISP_POLARITY_NEGATIVE</ul>	*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	HEPS	:1;	/**< HEPS: Horizontal enable signal polarity selection.
								 <ul><li>@ref D_IM_DISP_POLARITY_POSITIVE
									 <li>@ref D_IM_DISP_POLARITY_NEGATIVE</ul>	*/
		ULONG			:3;	/**< Reserve										*/
		ULONG	CKEG	:1;	/**< CKEG: Output clock edge selection.
								 <ul><li>@ref D_IM_DISP_CKEG_FALL
									 <li>@ref D_IM_DISP_CKEG_RISE</ul>			*/
		ULONG			:15;/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_POLSEL;

/**	VCYC register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	VCYC1	:14;/**< VCYC1: Vertical cycle 1.(Setting at vertical cycle of the 1st field.)<br>
								 Value range:0~16383<br>
								 Progressive : VCYC1 >= VBLK.VBLK1 + OVSIZE.OVSIZE + 1.<br>
								 Interlace : VCYC1 >= VBLK.VBLK1 + OVSIZE.OVSIZE / 2 + 1.					*/
		ULONG			:2;	/**< Reserve																	*/
		ULONG	VCYC2	:14;/**< VCYC2: Vertical cycle 2.(Setting at vertical cycle of the 2nd field.)<br>
								 Value range:0~16383<br>
								 Progressive : VCYC2 >= VBLK.VBLK2 + OVSIZE.OVSIZE + 1.<br>
								 Interlace : VCYC2 >= VBLK.VBLK2 + OVSIZE.OVSIZE / 2 + 1.					*/
		ULONG			:1;	/**< Reserve																	*/
		ULONG	VDSFT	:1;	/**< VDSFT: Vsync output 0.5H shift selection.
								 <ul><li>@ref D_IM_DISP_VDSFT_NORMAL
									 <li>@ref D_IM_DISP_VDSFT_SHIFT</ul>									*/
	} bit;	/**< Bit field */
} U_IM_DISP_VCYC;

/**	OVPW register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	OVPW	:10;/**< VPW: Vsync pluse width.<br>
								 Value range:1~1023							*/
		ULONG			:6;	/**< Reserve									*/
		ULONG	OVPWU	:1;	/**< VPWU: Vsync pluse width unit selection.
								 <ul><li>@ref D_IM_DISP_OVPWU_CLOCK_UNIT
									 <li>@ref D_IM_DISP_OVPWU_LINE_UNIT</ul>	*/
		ULONG			:15;/**< Reserve									*/
	} bit;	/**< Bit field */
} U_IM_DISP_OVPW;

/**	VBLK register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	VBLK1	:8;	/**< VBLK1: Period of vertical blank.(1st field)<br>
								 Value range:1~255								*/
		ULONG	VBLK2	:8;	/**< VBLK2: Period of vertical blank.(2nd field)<br>
								 Value range:1~255								*/
		ULONG			:16;/**< Reserve										*/
	} bit;	/**< Bit field */
} U_IM_DISP_VBLK;

/**	DOMD register structure. */
typedef union {
	ULONG		word;	/**< All bits */
	struct {
		ULONG	MODE	:8;	/**< MODE: Output mode.
								 <ul><li>@ref D_IM_DISP_MODE_RGB888_24BIT
									 <li>@ref D_IM_DISP_MODE_RGB888_30BIT
									 <li>@ref D_IM_DISP_MODE_RGB888_36BIT
									 <li>@ref D_IM_DISP_MODE_RGB888_8BIT_1
									 <li>@ref D_IM_DISP_MODE_RGB888_8BIT_2
									 <li>@ref D_IM_DISP_MODE_RGB888_8BIT_3
									 <li>@ref D_IM_DISP_MODE_RGB888_16BIT_1
									 <li>@ref D_IM_DISP_MODE_RGB888_16BIT_2
									 <li>@ref D_IM_DISP_MODE_RGB565_8BIT
									 <li>@ref D_IM_DISP_MODE_RGB565_16BIT
									 <li>@ref D_IM_DISP_MODE_RGB666_18BIT
									 <li>@ref D_IM_DISP_MODE_YCC422_8BIT
									 <li>@ref D_IM_DISP_MODE_YCC422_16BIT
									 <li>@ref D_IM_DISP_MODE_YCC444_24BIT
									 <li>@ref D_IM_DISP_MODE_YCC422_20BIT
									 <li>@ref D_IM_DISP_MODE_YCC422_24BIT
									 <li>@ref D_IM_DISP_MODE_DEEP_YCC444_30BIT
									 <li>@ref D_IM_DISP_MODE_DEEP_YCC444_36BIT
									 <li>@ref D_IM_DISP_MODE_DUAL_YCC444_12BIT
									 <li>@ref D_IM_DISP_MODE_YCC420_24BIT
									 <li>@ref D_IM_DISP_MODE_YCC420_30BIT
									 <li>@ref D_IM_DISP_MODE_GENERAL_8BIT
									 <li>@ref D_IM_DISP_MODE_GENERAL_16BIT
									 <li>@ref D_IM_DISP_MODE_GENERAL_10BIT_1
									 <li>@ref D_IM_DISP_MODE_GENERAL_10BIT_2</ul>	*/
		ULONG			:8;	/**< Reserve											*/
		ULONG	OBPSL	:1;	/**< OBPSL: Output bit position selection.
								 <ul><li>@ref D_IM_DISP_OBPSL_LSB
									 <li>@ref D_IM_DISP_OBPSL_MSB</ul>				*/
		ULONG			:7;	/**< Reserve											*/
		ULONG	OBUSL	:2;	/**< OBUSL: Output bit unit selection.
								 <ul><li>@ref D_IM_DISP_OBUSL_8BIT
									 <li>@ref D_IM_DISP_OBUSL_12BIT
									 <li>@ref D_IM_DISP_OBUSL_16BIT</ul>			*/
		ULONG			:6;	/**< Reserve											*/
	} bit;	/**< Bit field */
} U_IM_DISP_DOMD;

/**
Control data of data output block.<br>
It is not possible to rewrite it while data output block is operating.
*/
typedef struct {
	// Whole control register area.
	E_IM_DISP_TGKMD			tgkmd;									/**< TRG.TGKMD: Trigger register - External start-up mode.<br>
																		 <ul><li>@ref E_IM_DISP_TGKMD_NORMAL
																			 <li>@ref E_IM_DISP_TGKMD_EXTERNAL</ul>								*/
	ULONG					tgkst;									/**< TGKST: Operation start register.<br>
																		 Value range:0~4095.													*/
	U_IM_DISP_TOCTL			toctl;									/**< TOCTL: Whole output control register.									*/
	// Timing control register area.
	E_IM_DISP_RPGTMG		rpgctl;									/**< RPGCTL: Register parameter taking control register.<br>
																		 <ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
																			 <li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>							*/
	U_IM_DISP_POLSEL		polsel;									/**< POLSEL: External output signal polarity selection register.<br>		*/
	ULONG					tsl;									/**< TSL: Forwarding method setting register.
																		 <ul><li>@ref D_IM_DISP_TSL_PROGRESSIVE
																			 <li>@ref D_IM_DISP_TSL_INTERLACE</ul>								*/
	U_IM_DISP_VCYC			vcyc;									/**< VCYC: Vertical cycle setting register.<br>								*/
	ULONG					hcyc;									/**< HCYC: Horizontal cycle setting register.<br>
																		 Value range:8~65535<br>
																		 HCYC >= HBLK.HBLK + (Output data horizontal cycle) + 8.				*/
	U_IM_DISP_OVPW			ovpw;									/**< OVPW: Vsync pulse width setting register.<br>							*/
	ULONG					hpw;									/**< HPW: Hsync pulse width setting register.<br>
																		 Value range:1~1023														*/
	U_IM_DISP_VBLK			vblk;									/**< VBLK: Period of vertical blank setting register.<br>					*/
	ULONG					hblk;									/**< HBLK: Period of horizontal blank setting register.<br>
																		 Value range:16~1023<br>
																		 16 <= HBLK <= HCYC.HCYC - (Output data horizontal cycle) - 8.			*/
	ULONG					vdly;									/**< VDLY: Vsync output delay setting register.<br>
																		 Value range:0~255<br>
																		 VDLY <= HCYC.HCYC / 2 - 1.												*/
	ULONG					hdly;									/**< HDLY: Hsync output delay setting register.<br>
																		 Value range:0~255<br>
																		 HDLY <= HCYC.HCYC / 2 - 1.												*/
	ULONG					ovsize;									/**< OVSIZE: Output data vertical size setting register.<br>
																		 Value range:0~16383													*/
	ULONG					ohsize;									/**< OHSIZE: Output data horizontal size setting register.<br>
																		 Value range:0~65535													*/
	ULONG					vrfctl;									/**< VRFCTL: Vertical enable signal operation setting register.<br>
																		 <ul><li>@ref D_IM_DISP_VENS_H_ENABLE
																			 <li>@ref D_IM_DISP_VENS_HSYNC</ul>									*/
	ULONG					hrfctl;									/**< HRFCTL: Horizontal enable signal operation setting register.<br>
																		 <ul><li>@ref D_IM_DISP_HENS_ASSERT_ON
																			 <li>@ref D_IM_DISP_HENS_ASSERT_OFF</ul>							*/
	// Output data control register area.
	U_IM_DISP_DOMD			domd;									/**< DOMD: Data output mode setting register.								*/
	E_IM_DISP_TABLE_ACCESS	tblaset_gmtaen;							/**< TBLASET.GMTAEN: Gamma correct table access enable.<br>
																		 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
																			 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>						*/
	E_IM_DISP_TABLE_ACCESS	tblaset_ysatta;							/**< TBLASET.YSATTA: Luminance and chroma correct table access enable.<br>
																		 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
																			 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>						*/
} T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT;

/**
Control data of P2M macro in write channel block.
*/
typedef struct {
	ULONG				p2mpaen;		/**< P2MPAEN: P2M-chip RAM access enable register.<br>
											 <ul><li>@ref D_IM_DISP_ENABLE_OFF
												 <li>@ref D_IM_DISP_ENABLE_ON</ul>								*/
	E_IM_DISP_PLPF		p2mctl_plpf;	/**< P2MCTL.PLPF: LPF recording mode.<br>
											 <ul><li>@ref E_IM_DISP_PLPF_INVALID
												 <li>@ref E_IM_DISP_PLPF_SHORT
												 <li>@ref E_IM_DISP_PLPF_MIDDLE
												 <li>@ref E_IM_DISP_PLPF_LONG</ul>								*/
	E_IM_DISP_P2MTYP	p2mctl_p2mtyp;	/**< P2MCTL.P2MTYP: P2M recording mode.<br>
											 <ul><li>@ref E_IM_DISP_P2MTYP_8
												 <li>@ref E_IM_DISP_P2MTYP_10_PACK
												 <li>@ref E_IM_DISP_P2MTYP_12_PACK
												 <li>@ref E_IM_DISP_P2MTYP_16</ul>								*/
	USHORT				p2mofs;			/**< P2MOFS: P2M input offset register.<br>
											 Value range:0~32767.												*/
	BYTE				pbsft;			/**< PBSFT: P2M right bit shift amount register.<br>
											 Value range:0~8.													*/
	USHORT				pclph;			/**< PCLPH: P2M on the clip amount register.<br>
											 Value range:0~65535.												*/
	USHORT				ptrmv;			/**< PTRMV: P2M trimming vertical start position register.<br>
											 Value range:0~8191.												*/
	USHORT				ptrmh;			/**< PTRMH: P2M trimming horizontal start position register.<br>
											 Value range:0~12287.												*/
	USHORT				ptrmvw;			/**< PTRMVW: P2M trimming vertical processing line number register.<br>
											 Value range:0~65535.												*/
	ULONG				ptrmhw;			/**< PTRMHW: P2M trimming horizontal processing line number register.<br>
											 Value range:0~16777215.											*/
	BYTE				ptrmxvcyc;		/**< PTRMXVCYC: P2M trimming vertical thinning cycle register.<br>
											 Value 0:cycle 64 Lines, 1:cycle 1 line~63:cycle 63 lines.			*/
	BYTE				ptrmxhcyc;		/**< PTRMXHCYC: P2M trimming horizontal thinning cycle register.<br>
											 Value 0:cycle 64 pixels, 1:cycle 1 pixel~63:cycle 63 pixels.		*/
	UINT64				ptrmxven;		/**< PTRMXVEN: P2M trimming vertical uptake line register.<br>
											 bit d[0]:64 lines ~ d[63]:1 line.<br>
											 MSB is the beginning of one period,<br>
											 LSB will correspond to the end of one period<br>					*/
	UINT64				ptrmxhen;		/**< PTRMXHEN: P2M trimming horizontal capture pixel register.<br>
											 bit d[0]:64 pixel ~ d[63]:1 pixel.<br>
											 MSB is the beginning of one period,<br>
											 LSB will correspond to the end of one period<br>					*/
	BYTE				p2mmir;			/**< P2MMIR: P2M left and right inverted enable register.<br>
											 <ul><li>@ref D_IM_DISP_ENABLE_OFF
												 <li>@ref D_IM_DISP_ENABLE_ON</ul>								*/
	E_IM_DISP_P2M2PMD	p2m2pmd;		/**< P2M2PMD: P2M 1 pixel / 2 pixel input mode selection register.<br>
											 <ul><li>@ref E_IM_DISP_P2M2PMD_1
												 <li>@ref E_IM_DISP_P2M2PMD_2</ul>								*/
} T_IM_DISP_CTRL_P2M;

/**
Control data of main data input block.<br>
It is not possible to rewrite it while main data input block is operating.
*/
typedef struct {
	// Whole control register area.
	E_IM_DISP_RPGTMG		lrpgctl;			/**< LRPGCTL: Register parameter taking control register.<br>
													 <ul><li>@ref E_IM_DISP_RPGTMG_VSYNC_FRAME_TOP
														 <li>@ref E_IM_DISP_RPGTMG_VSYNC_VSYNC</ul>						*/
	// Data processing setting register area.
	E_IM_DISP_TABLE_ACCESS	ltblaset_igtaen;	/**< LTBLASET.IGTAEN: Anti-gamma correct table access enable.<br>
													 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
														 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>					*/
	E_IM_DISP_TABLE_ACCESS	ltblaset_gtaen;		/**< LTBLASET.GTAEN: Gamma correct table access enable.<br>
													 <ul><li>@ref E_IM_DISP_TABLE_ACCESS_DISABLE
														 <li>@ref E_IM_DISP_TABLE_ACCESS_ENABLE</ul>					*/
} T_IM_DISP_CTRL_MAIN_LAYER_TRG_LIMIT;

/** Gamma correction table data (data output block). */
typedef struct {
	//Note !!! Don't change the following data's order
	USHORT*			r_data;		/**< Pointer of R data gamma table.<br>
									 Please specify the address of the array of USHORT[33].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			g_data;		/**< Pointer of G data gamma table.<br>
									 Please specify the address of the array of USHORT[33].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			b_data;		/**< Pointer of B data gamma table.<br>
									 Please specify the address of the array of USHORT[33].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
} T_IM_DISP_GAMMA_TBL_OUT;

/** data output block table setting data. */
typedef struct {
	T_IM_DISP_GAMMA_TBL_OUT	gamma_a;		/**< Gamma correction table A										*/
	T_IM_DISP_GAMMA_TBL_OUT	gamma_b;		/**< Gamma correction table B										*/
	USHORT*					luminance_a;	/**< Pointer of Luminance correction table A.<br>
												 Please specify the address of the array of USHORT[33].<br>
												 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*					chroma_a;		/**< Pointer of Chroma correction gain table A.<br>
												 Please specify the address of the array of USHORT[33].<br>
												 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*					luminance_b;	/**< Pointer of Luminance correction table B.<br>
												 Please specify the address of the array of USHORT[33].<br>
												 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*					chroma_b;		/**< Pointer of Chroma correction gain table B.<br>
												 Please specify the address of the array of USHORT[33].<br>
												 If NULL is specified, this setting is skipped.<br>				*/
} T_IM_DISP_CTRL_OUTPUT_TBL;

/** Gamma correction table data (main data input block). */
typedef struct {
	//Note !!! Don't change the following data's order
	USHORT*			r_data;		/**< Pointer of R data gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			g_data;		/**< Pointer of G data gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			b_data;		/**< Pointer of B data gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
} T_IM_DISP_GAMMA_TBL_IN;

/** Anti-gamma correction table data. */
typedef struct {
	//Note !!! Don't change the following data's order
	USHORT*			r_anti;		/**< Pointer of R data anti gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			g_anti;		/**< Pointer of G data anti gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
	USHORT*			b_anti;		/**< Pointer of B data anti gamma table.<br>
									 Please specify the address of the array of USHORT[32].<br>
									 If NULL is specified, this setting is skipped.<br>				*/
} T_IM_DISP_ANTI_GAMMA_TBL;

/** main data input block table setting data. */
typedef struct {
	T_IM_DISP_ANTI_GAMMA_TBL	anti_a;		/**< Anti gamma correction table A	*/
	T_IM_DISP_ANTI_GAMMA_TBL	anti_b;		/**< Anti gamma correction table B	*/
	T_IM_DISP_GAMMA_TBL_IN		gamma_a;	/**< Gamma correction table A		*/
	T_IM_DISP_GAMMA_TBL_IN		gamma_b;	/**< Gamma correction table B		*/
} T_IM_DISP_CTRL_MAIN_TBL;

INT32 im_disp_param_check_lidt(E_IM_DISP_SEL block, U_IM_DISP_LIDT lidt);
INT32 im_disp_param_check_lisize(U_IM_DISP_SIZE lisize);
INT32 im_disp_param_check_ldsta(U_IM_DISP_DSTA ldsta);
INT32 im_disp_param_check_lfd(ULONG y_hga, ULONG c_hga);
INT32 im_disp_param_check_resize(E_IM_DISP_RSZSL rsz0, U_IM_DISP_RSZ1 rsz1, U_IM_DISP_RSZ2 rsz2, U_IM_DISP_RSZ3 rsz3);
INT32 im_disp_param_check_warning(T_IM_DISP_WARNING const *const warning);
INT32 im_disp_param_check_blend(U_IM_DISP_BLDCTL bldctl);
INT32 im_disp_param_check_grid(T_IM_DISP_GRID const *const grid);
INT32 im_disp_param_check_face_frame(T_IM_DISP_FACE_FRAME_PARAM const *const face);
INT32 im_disp_param_check_top_face(BYTE msff);
INT32 im_disp_param_check_gridt(U_IM_DISP_GRIDT gridt);
INT32 im_disp_param_check_grtisize(U_IM_DISP_SIZE grtisize);
INT32 im_disp_param_check_grtdsta(U_IM_DISP_DSTA grtdsta);
INT32 im_disp_param_check_gripo(U_IM_DISP_GRIPO ipo);
INT32 im_disp_param_check_grisize(const U_IM_DISP_SIZE grisize[], UINT32 input_size_count);
INT32 im_disp_param_check_grsa(ULONG address);
INT32 im_disp_param_check_grhga(ULONG grhga);
INT32 im_disp_param_check_grdsta(U_IM_DISP_DSTA grdsta);
INT32 im_disp_param_check_ctrl_main_layer(E_IM_DISP_SEL block, T_IM_DISP_CTRL_MAIN_LAYER const *const ctrl);
INT32 im_disp_param_check_ctrl_output(E_IM_DISP_SEL block, T_IM_DISP_CTRL_OUTPUT_TRG_LIMIT const *const ctrl_trg_limit, T_IM_DISP_CTRL_OUTPUT const *const ctrl);

#endif /* __IM_DISP8_H__ */


