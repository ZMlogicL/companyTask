/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-02
*@author              :liudong
*@brief               :CtDdXdmasnap1类
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
#include "ctddxdmasnap.h"
#include "driver_common.h"
// #include "dd_xdmasnap.h"
#include "../../DeviceDriver/ARM/src/ddxdmasnap.h"

#include "ctddxdmasnap.h"
#include "ctddxdmasnap1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdXdmasnap1, ct_dd_xdmasnap1);
#define CT_DD_XDMASNAP1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdXdmasnap1Private,CT_TYPE_DD_XDMASNAP1))

struct _CtDdXdmasnap1Private
{
	CtDdXdmasnap* ctDdXdmasnap;
};

/*
DECLS
*/

static void ct_dd_xdmasnap1_constructor(CtDdXdmasnap1 *self) 
{
	CtDdXdmasnap1Private *priv = CT_DD_XDMASNAP1_GET_PRIVATE(self);
	priv->ctDdXdmasnap = NULL;
}

static void ct_dd_xdmasnap1_destructor(CtDdXdmasnap1 *self) 
{
//	CtDdXdmasnap1Private *priv = CT_DD_XDMASNAP1_GET_PRIVATE(self);
	self = 	NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

//  kint32 ct_xdmasnap_process(kuchar num)
 kint32 ct_dd_xdmasnap1_process(CtDdXdmasnap1 *self)
{
	kint32                 ret = 0;
	UINT32                wait_mode = 0;
	USHORT                status = 0;
	kuchar                 ch = 0;
	kuchar                 arb_type = 0;
	TDdXdmasnapCtrl    dma_ctrl_trns;
	TDdXdmasnapCommon  dma_common;
	kuchar                 protect_code_src = 0;
	kuchar                 protect_code_dst = 0;
	USHORT                xdmac_status = 0;
	USHORT                transfer_status = 0;
	USHORT                interrupt_status = 0;
	DdXdmasnapTrnsSize  dma_trns_size;
	ULONG                 trns_size = 0;
	ULONG                 src_addr = 0;
	ULONG                 dst_addr = 0;
	
	CtDdXdmasnap1Private *priv = CT_DD_XDMASNAP1_GET_PRIVATE(self);

	switch (ct_dd_xdmasnap_get_num(priv->ctDdXdmasnap)) {
		// TEST ID 01-01-01
		case 1:
			memset((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, 0x00, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 0;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_BYTE;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_BYTE;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("SNAP XDMAC dd_xdmasnap_open done\n"));
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("SNAP XDMAC dd_xdmasnap_ctrl_common done\n"));
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				
				Ddim_Print(("SNAP XDMAC dd_xdmasnap_ctrl_trns done\n"));
				
				ret = dd_xdmasnap_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("dd_xdmasnap_start_sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				else {
					Ddim_Print(("dd_xdmasnap_start_sync. Complete! : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			Ddim_Print(("SNAP XDMAC dd_xdmasnap_start_sync done\n"));
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			Ddim_Print(("SNAP XDMAC dd_xdmasnap_close done\n"));
			
			break;
			
		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, 0x00, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-01-03
		case 3:
			memset((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, 0x00, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 2;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmasnap_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-01-04
		case 4:
			memset((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, 0x00, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 3;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmasnap_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
						
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-02-03
		case 5:
			ch = 0;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = 1;
			dma_ctrl_trns.src_addr        = 0;
			dma_ctrl_trns.dst_addr        = 0;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_BYTE;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_BYTE;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
			dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_NONE;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_DISABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;

		// TEST ID 01-02-04
		case 6:
			ch = 0;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = 0xffffffff;
			dma_ctrl_trns.src_addr        = 0xffffffff;
			dma_ctrl_trns.dst_addr        = 0xffffffff;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_ENABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_FIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_ENABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_FIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
			dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_DESTINATION;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_ENABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_ENABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_IDREQ_13;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_VALID;
			dma_ctrl_trns.config_2.bit.DCA = 0x0fffffff;
				
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;
			
		// TEST ID 01-02-05
		case 7:
			ch = 0;
			protect_code_src = 0x0;
			protect_code_dst = 0x0;
			
			ret = dd_xdmasnap_set_source_protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmasnap_set_source_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = dd_xdmasnap_set_destination_protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmasnap_set_destination_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-06
		case 8:
			ch = 0;
			protect_code_src = 0x3;
			protect_code_dst = 0x3;
			
			ret = dd_xdmasnap_set_source_protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmasnap_set_source_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = dd_xdmasnap_set_destination_protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util dd_xdmasnap_set_destination_protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-07
		case 9:
			ch = 2;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_WORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_WORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_get_status(ch,&xdmac_status,&transfer_status,&interrupt_status);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmasnap_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			Ddim_Print(("xdmac_status=%d\n", xdmac_status));
			Ddim_Print(("transfer_status=%d\n", transfer_status));
			Ddim_Print(("interrupt_status=%d\n", interrupt_status));
			
			break;
			
		// TEST ID 01-02-08
		case 10:
			ch = 3;
			
			arb_type                    = DdXdmasnap_D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = DdXdmasnap_D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = DdXdmasnap_D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = DdXdmasnap_D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = DdXdmasnap_D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = DdXdmasnap_D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = DdXdmasnap_D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = DdXdmasnap_D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = DdXdmasnap_D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = DdXdmasnap_D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = DdXdmasnap_D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = DdXdmasnap_D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = DdXdmasnap_D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = dd_xdmasnap_open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = dd_xdmasnap_ctrl_common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = dd_xdmasnap_ctrl_trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = dd_xdmasnap_start_async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = dd_xdmasnap_get_status(ch,&xdmac_status,&transfer_status,&interrupt_status);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. dd_xdmasnap_get_status ERR : ret=0x%x\n", ret));
					return ret;
				}
				ret = dd_xdmasnap_wait_end(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = dd_xdmasnap_close(ch);
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
			
			dma_trns_size.trns_size = 0x12345678;
			dma_trns_size.src_addr = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_trns_size.dst_addr = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			
			ret = dd_xdmasnap_set_trns_size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmasnap_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			trns_size = dd_xdmasnap_get_trns_size(ch);
			Ddim_Print(("Trns_Size==0x%x\n", (unsigned int)trns_size));
			
			break;
			
		// TEST ID 01-02-10
		case 12:
			ch = 0;
			
			dma_trns_size.trns_size = 0x12345678;
			dma_trns_size.src_addr = 0xFFFFFFFF;
			dma_trns_size.dst_addr = 0xFFFFFFFF;
			
			ret = dd_xdmasnap_set_trns_size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmasnap_get_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			src_addr = dd_xdmasnap_get_src_addr(ch);
			dst_addr = dd_xdmasnap_get_dst_addr(ch);
			Ddim_Print(("Src_Addr==0x%x\n", (unsigned int)src_addr));
			Ddim_Print(("Dst_Addr==0x%x\n", (unsigned int)dst_addr));
			
			break;
			
		// TEST ID 01-02-11
		case 13:
			dd_xdmasnap_stop_All_Ch();
			
			break;
			
		// TEST ID 01-02-12
		case 14:
			ch = 0;
			
			ret = dd_xdmasnap_clear_status(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. dd_xdmasnap_clear_status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-11
		case 15:
			dd_xdmasnap_copy_sdram_sync(0, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
			break;
			
		case 16:
			dd_xdmasnap_copy_sdram_async(0, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE, NULL);
			ret = dd_xdmasnap_wait_end(0, &status, DdXdmasnap_D_DD_XDMASNAP_WAITMODE_EVENT);
			if (ret != 0) {
				Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
				break;
			}
			break;
			
		default:
			ret = -1;
			break;
	}
	return ret;
}

void ct_dd_xdmasnap1_set_ctddxdmasnap(CtDdXdmasnap1 *self,CtDdXdmasnap *ctDdXdmasnap)
{
	CtDdXdmasnap1Private *priv = CT_DD_XDMASNAP1_GET_PRIVATE(self);
	priv->ctDdXdmasnap = ctDdXdmasnap;
}

CtDdXdmasnap1* ct_dd_xdmasnap1_new(void) 
{
    CtDdXdmasnap1 *self = k_object_new_with_private(CT_TYPE_DD_XDMASNAP1, sizeof(CtDdXdmasnap1Private));
    return self;
}
