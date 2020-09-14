/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmac1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
// #include "ctddxdmac.h"
#include "driver_common.h"
// #include "dd_xdmac.h"
// #include "dd_top.h"
#include "../../DeviceDriver/Exs/src/ddxdmac.h"
#include "../../Project/DeviceDriver/LSITop/src/ddtop.h"

#include "ctddxdmac.h"

#include "ctddxdmac1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdXdmac1, ct_dd_xdmac1);
#define CT_DD_XDMAC1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdXdmac1Private,CT_TYPE_DD_XDMAC1))

struct _CtDdXdmac1Private
{
	CtDdXdmac* ctDdXdmac;
};

/*
DECLS
*/

static void ct_dd_xdmac1_constructor(CtDdXdmac1 *self) 
{
	CtDdXdmac1Private *priv = CT_DD_XDMAC1_GET_PRIVATE(self);
	priv->ctDdXdmac = NULL;
}

static void ct_dd_xdmac1_destructor(CtDdXdmac1 *self) 
{
	// CtDdXdmac1Private *priv = CT_DD_XDMAC1_GET_PRIVATE(self);
	self = NULL;
	
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

//  kint32 ct_xdmac_process(kuchar num)
 kint32 ct_dd_xdmac1_process(CtDdXdmac1 *self)
{
	kint32                 ret = 0;
	UINT32                wait_mode = 0;
	USHORT                status = 0;
	kuchar                 ch = 0;
	kuchar                 arb_type = 0;
	TDdXdmacCtrl       dma_ctrl_trns;
	TDdXdmacCommon     dma_common;
	kuchar                 protect_code_src = 0;
	kuchar                 protect_code_dst = 0;
	USHORT                xdmac_status = 0;
	USHORT                transfer_status = 0;
	USHORT                interrupt_status = 0;
	TDdXdmacTrnsSize  dma_trns_size;
	ULONG                 trns_size = 0;
	ULONG                 src_addr = 0;
	ULONG                 dst_addr = 0;
	
	CtDdXdmac1Private *priv = CT_DD_XDMAC1_GET_PRIVATE(self);

	switch (ct_dd_xdmac_get_num(priv->ctDdXdmac)) {
		// TEST ID 01-01-01
		case 1:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			
			arb_type                    = DdXdmacXDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_CPU;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_BYTE;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_BYTE;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_ENABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
				
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("XDMAC dd_xdmac_open done\n"));
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("XDMAC dd_xdmac_ctrl_common done\n"));
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				
				Ddim_Print(("XDMAC dd_xdmac_ctrl_trns done\n"));
				
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("dd_xdmac_start_sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				else {
					Ddim_Print(("dd_xdmac_start_sync. Complete! : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			Ddim_Print(("XDMAC dd_xdmac_start_sync done\n"));
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			Ddim_Print(("XDMAC dd_xdmac_close done\n"));
			
			break;
			
		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_EVENT;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_HALFWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_HALFWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-01-03
		case 3:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_CPU;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = ct_dd_xdmac_callback_cb;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_WORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_WORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_ENABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmac_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-01-04
		case 4:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 3;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_EVENT;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = ct_dd_xdmac_callback_cb;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
				
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmac_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
						
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-02-03
		case 5:
			ch = 0;
			
			arb_type                    = DdXdmacXDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_CPU;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = 1;
			dma_ctrl_trns.srcAddr        = 0;
			dma_ctrl_trns.dstAddr        = 0;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_BYTE;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_BYTE;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
			dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_NONE;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_DISABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
				
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;

		// TEST ID 01-02-04
		case 6:
			ch = 0;
			
			arb_type                    = DdXdmacXDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_CPU;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = 0xffffffff;
			dma_ctrl_trns.srcAddr        = 0xffffffff;
			dma_ctrl_trns.dstAddr        = 0xffffffff;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_ENABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_FIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_ENABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_FIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
			dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_DESTINATION;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_ENABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_ENABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_ENABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_IDREQ_13;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_VALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0x0fffffff;
				
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;
			
		// TEST ID 01-02-05
		case 7:
			ch = 0;
			protect_code_src = 0x0;
			protect_code_dst = 0x0;
			
			ret = Dd_XDMAC_Set_Source_Protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMAC_Set_Source_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = dd_xdmac_set_destination_protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmac_set_destination_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-06
		case 8:
			ch = 0;
			protect_code_src = 0x3;
			protect_code_dst = 0x3;
			
			ret = Dd_XDMAC_Set_Source_Protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMAC_Set_Source_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = dd_xdmac_set_destination_protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmac_set_destination_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-07
		case 9:
			ch = 2;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_CPU;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = ct_dd_xdmac_callback_cb;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_WORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_WORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_ENABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_get_status(ch,&xdmac_status,&transfer_status,&interrupt_status);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmac_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			Ddim_Print(("xdmac_status=%d\n", xdmac_status));
			Ddim_Print(("transfer_status=%d\n", transfer_status));
			Ddim_Print(("interrupt_status=%d\n", interrupt_status));
			
			break;
			
		// TEST ID 01-02-08
		case 10:
			ch = 3;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_EVENT;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = ct_dd_xdmac_callback_cb;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmac_get_status(ch,&xdmac_status,&transfer_status,&interrupt_status);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. dd_xdmac_get_status ERR : ret=0x%x\n", ret));
					return ret;
				}
				ret = dd_xdmac_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("xdmac_status=%d\n", xdmac_status));
			Ddim_Print(("transfer_status=%d\n", transfer_status));
			Ddim_Print(("interrupt_status=%d\n", interrupt_status));
			
			break;
			
		// TEST ID 01-02-09
		case 11:
			ch = 0;
			
			dma_trns_size.trnsSize = 0x12345678;
			dma_trns_size.srcAddr = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_trns_size.dstAddr = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			
			ret = dd_xdmac_set_trns_size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmac_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			trns_size = dd_xdmac_get_trns_size(ch);
			Ddim_Print(("Trns_Size==0x%x\n", (unsigned int)trns_size));
			
			break;
			
		// TEST ID 01-02-10
		case 12:
			ch = 0;
			
			dma_trns_size.trnsSize = 0x12345678;
			dma_trns_size.srcAddr = 0xFFFFFFFF;
			dma_trns_size.dstAddr = 0xFFFFFFFF;
			
			ret = dd_xdmac_set_trns_size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmac_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			src_addr = dd_xdmac_get_src_addr(ch);
			srcAddr = dd_xdmac_get_dst_addr(ch);
			Ddim_Print(("Src_Addr==0x%x\n", (unsigned int)src_addr));
			Ddim_Print(("Dst_Addr==0x%x\n", (unsigned int)dst_addr));
			
			break;
			
		// TEST ID 01-02-11
		case 13:
			dd_xdmac_stop_all_ch();
			
			break;
			
		// TEST ID 01-02-12
		case 14:
			ch = 0;
			
			ret = dd_xdmac_clear_status(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmac_clear_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-11
		case 15:
			dd_xdmac_copy_sdram_sync(0, CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE, DdXdmac_WAITMODE_EVENT);
			break;
			
		case 16:
			dd_xdmac_copy_sdram_async(0, CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE, NULL);
			ret = dd_xdmac_wait_end(0, &status, DdXdmac_WAITMODE_EVENT);
			if (ret != 0) {
				Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
				break;
			}
			break;
			
		case 17:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_EVENT;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_INTMEM;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_HALFWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_HALFWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_INTMEM, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			break;

		case 18:
			memset((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_DST, 0x00, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			
			arb_type                    = DdXdmacXDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmac_WAITMODE_EVENT;
			
			dma_common.commonConfig.bit.CP = arb_type;
			dma_common.commonConfig.bit.XE = DdXdmacXDACS_XE_ENABLE;
			
			dma_ctrl_trns.trnsSize       = CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE;
			dma_ctrl_trns.srcAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dstAddr        = CtDdXdmac1_D_XDMAC_AUTO_TEST_INTMEM;
			dma_ctrl_trns.intHandler     = NULL;
			
			dma_ctrl_trns.configOne.bit.SBS = DdXdmacXDSAC_SBS_HALFWORD;
			dma_ctrl_trns.configOne.bit.DBS = DdXdmacXDDAC_DBS_HALFWORD;
			
			dma_ctrl_trns.configOne.bit.SRL = DdXdmacXDSAC_SRL_DISABLE;
			dma_ctrl_trns.configOne.bit.SAF = DdXdmacXDSAC_SAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.SBL = DdXdmacXDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.configOne.bit.DRL = DdXdmacXDDAC_DRL_DISABLE;
			dma_ctrl_trns.configOne.bit.DAF = DdXdmacXDDAC_DAF_NOTFIX;
			dma_ctrl_trns.configOne.bit.DBL = DdXdmacXDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmac_WAITMODE_EVENT) {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_ENABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.configOne.bit.TI = DdXdmacXDDES_TI_DISABLE;
				dma_ctrl_trns.configOne.bit.EI = DdXdmacXDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.configOne.bit.AT = DdXdmacXDDES_AT_SOURCE;
			dma_ctrl_trns.configOne.bit.BR = DdXdmacXDDES_BR_DISABLE;
			dma_ctrl_trns.configOne.bit.BT = DdXdmacXDDES_BT_DISABLE;
			dma_ctrl_trns.configOne.bit.SA = DdXdmacXDDES_SA_DISABLE;
			dma_ctrl_trns.configOne.bit.TF = DdXdmacXDDES_TF_SOFT;
			dma_ctrl_trns.configOne.bit.SE = DdXdmacXDDES_SE_ENABLE;
			dma_ctrl_trns.configTwo.bit.DCN = DdXdmacXDDCC_DCN_INVALID;
			dma_ctrl_trns.configTwo.bit.DCA = 0;
			
			ret = dd_xdmac_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmac_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmac_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmac_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmac_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_ADR_SRC, (void*)CtDdXdmac1_D_XDMAC_AUTO_TEST_INTMEM, CtDdXdmac1_D_XDMAC_AUTO_TEST_SIZE)));
			break;
		default:
			ret = -1;
			break;
	}
	return ret;
}

void ct_dd_xdmac1_set_ctddxdmac(CtDdXdmac1 *self,CtDdXdmac *ctDdXdmac)
{
	CtDdXdmac1Private *priv = CT_DD_XDMAC1_GET_PRIVATE(self);
	priv->ctDdXdmac = ctDdXdmac;
}

CtDdXdmac1* ct_dd_xdmac1_new(void) 
{
    CtDdXdmac1 *self = k_object_new_with_private(CT_TYPE_DD_XDMAC1, sizeof(CtDdXdmac1Private));
    return self;
}
