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
#include "dd_xdmasnap.h"

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
	T_DD_XDMASNAP_CTRL    dma_ctrl_trns;
	T_DD_XDMASNAP_COMMON  dma_common;
	kuchar                 protect_code_src = 0;
	kuchar                 protect_code_dst = 0;
	USHORT                xdmac_status = 0;
	USHORT                transfer_status = 0;
	USHORT                interrupt_status = 0;
	T_DD_XDMASNAP_TRNS_SIZE  dma_trns_size;
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
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_BYTE;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_BYTE;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("SNAP XDMAC Dd_XDMASNAP_Open done\n"));
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			Ddim_Print(("SNAP XDMAC Dd_XDMASNAP_Ctrl_Common done\n"));
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				
				Ddim_Print(("SNAP XDMAC Dd_XDMASNAP_Ctrl_Trns done\n"));
				
				ret = Dd_XDMASNAP_Start_Sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("Dd_XDMASNAP_Start_Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				else {
					Ddim_Print(("Dd_XDMASNAP_Start_Sync. Complete! : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			Ddim_Print(("SNAP XDMAC Dd_XDMASNAP_Start_Sync done\n"));
			
			ret = Dd_XDMASNAP_Close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			Ddim_Print(("SNAP XDMAC Dd_XDMASNAP_Close done\n"));
			
			break;
			
		// TEST ID 01-01-02
		case 2:
			memset((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, 0x00, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE);
			DDIM_User_L1l2cache_Clean_Flush_All();
			ch = 1;
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_HALFWORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_HALFWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
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
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_WORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_WORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = Dd_XDMASNAP_Wait_End(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
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
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = Dd_XDMASNAP_Wait_End(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
						
			Ddim_Print(("Result = %d\n", memcmp((void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, (void*)CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE)));
			break;
			
		// TEST ID 01-02-03
		case 5:
			ch = 0;
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = 1;
			dma_ctrl_trns.src_addr        = 0;
			dma_ctrl_trns.dst_addr        = 0;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_BYTE;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_BYTE;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
			dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_NONE;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_DISABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
				
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;

		// TEST ID 01-02-04
		case 6:
			ch = 0;
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_ROTATED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = 0xffffffff;
			dma_ctrl_trns.src_addr        = 0xffffffff;
			dma_ctrl_trns.dst_addr        = 0xffffffff;
			dma_ctrl_trns.int_handler     = NULL;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_ENABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_FIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_ENABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_FIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
			dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_DESTINATION;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_ENABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_ENABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_IDREQ_13;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_VALID;
			dma_ctrl_trns.config_2.bit.DCA = 0x0fffffff;
				
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Sync(ch, &status, wait_mode);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Close ERR : ret=0x%x\n", ret));
			}
			
			break;
			
		// TEST ID 01-02-05
		case 7:
			ch = 0;
			protect_code_src = 0x0;
			protect_code_dst = 0x0;
			
			ret = Dd_XDMASNAP_Set_Source_Protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMASNAP_Set_Source_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = Dd_XDMASNAP_Set_Destination_Protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMASNAP_Set_Destination_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-06
		case 8:
			ch = 0;
			protect_code_src = 0x3;
			protect_code_dst = 0x3;
			
			ret = Dd_XDMASNAP_Set_Source_Protect(ch,protect_code_src);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMASNAP_Set_Source_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			ret = Dd_XDMASNAP_Set_Destination_Protect(ch,protect_code_dst);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Dd_XDMASNAP_Set_Destination_Protect ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-07
		case 9:
			ch = 2;
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_CPU;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_WORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_WORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_ENABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Get_Status(ch,&xdmac_status,&transfer_status,&interrupt_status);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Dd_XDMASNAP_Get_Status ERR : ret=0x%x\n", ret));
				return ret;
			}
			Ddim_Print(("xdmac_status=%d\n", xdmac_status));
			Ddim_Print(("transfer_status=%d\n", transfer_status));
			Ddim_Print(("interrupt_status=%d\n", interrupt_status));
			
			break;
			
		// TEST ID 01-02-08
		case 10:
			ch = 3;
			
			arb_type                    = D_DD_XDMASNAP_XDACS_CP_FIXED;		// rotate
			wait_mode                   = D_DD_XDMASNAP_WAITMODE_EVENT;
			
			dma_common.common_config.bit.CP = arb_type;
			dma_common.common_config.bit.XE = D_DD_XDMASNAP_XDACS_XE_ENABLE;
			
			dma_ctrl_trns.trns_size       = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE;
			dma_ctrl_trns.src_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC;
			dma_ctrl_trns.dst_addr        = CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST;
			dma_ctrl_trns.int_handler     = ct_dd_xdmasnap_callback_cb;
			
			dma_ctrl_trns.config_1.bit.SBS = D_DD_XDMASNAP_XDSAC_SBS_DOUBLEWORD;
			dma_ctrl_trns.config_1.bit.DBS = D_DD_XDMASNAP_XDDAC_DBS_DOUBLEWORD;
			
			dma_ctrl_trns.config_1.bit.SRL = D_DD_XDMASNAP_XDSAC_SRL_DISABLE;
			dma_ctrl_trns.config_1.bit.SAF = D_DD_XDMASNAP_XDSAC_SAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.SBL = D_DD_XDMASNAP_XDSAC_SBL_LENGTH_16;
			dma_ctrl_trns.config_1.bit.DRL = D_DD_XDMASNAP_XDDAC_DRL_DISABLE;
			dma_ctrl_trns.config_1.bit.DAF = D_DD_XDMASNAP_XDDAC_DAF_NOTFIX;
			dma_ctrl_trns.config_1.bit.DBL = D_DD_XDMASNAP_XDDAC_DBL_LENGTH_16;
			
			if (wait_mode == D_DD_XDMASNAP_WAITMODE_EVENT) {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_ENABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_ENABLE;
			}
			else {
				dma_ctrl_trns.config_1.bit.TI = D_DD_XDMASNAP_XDDES_TI_DISABLE;
				dma_ctrl_trns.config_1.bit.EI = D_DD_XDMASNAP_XDDES_EI_DISABLE;
			}
			
			dma_ctrl_trns.config_1.bit.AT = D_DD_XDMASNAP_XDDES_AT_SOURCE;
			dma_ctrl_trns.config_1.bit.BR = D_DD_XDMASNAP_XDDES_BR_DISABLE;
			dma_ctrl_trns.config_1.bit.BT = D_DD_XDMASNAP_XDDES_BT_DISABLE;
			dma_ctrl_trns.config_1.bit.SA = D_DD_XDMASNAP_XDDES_SA_DISABLE;
			dma_ctrl_trns.config_1.bit.TF = D_DD_XDMASNAP_XDDES_TF_SOFT;
			dma_ctrl_trns.config_1.bit.SE = D_DD_XDMASNAP_XDDES_SE_ENABLE;
			dma_ctrl_trns.config_2.bit.DCN = D_DD_XDMASNAP_XDDCC_DCN_INVALID;
			dma_ctrl_trns.config_2.bit.DCA = 0;
			
			ret = Dd_XDMASNAP_Open(ch,D_DDIM_USER_SEM_WAIT_POL);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Open ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			ret = Dd_XDMASNAP_Ctrl_Common(&dma_common);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Common Setting ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			while (1) {
				ret = Dd_XDMASNAP_Ctrl_Trns(ch, &dma_ctrl_trns);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Ctrl Setting ERR : ret=0x%x\n", ret));
					break;
				}
				ret = Dd_XDMASNAP_Start_Async(ch);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Start ERR : ret=0x%x, status=0x%x\n", ret, status));
				}
				ret = Dd_XDMASNAP_Get_Status(ch,&xdmac_status,&transfer_status,&interrupt_status);
				if (ret != D_DDIM_OK) {
					Ddim_Print(("DMA Util Copy Sync. Dd_XDMASNAP_Get_Status ERR : ret=0x%x\n", ret));
					return ret;
				}
				ret = Dd_XDMASNAP_Wait_End(ch, &status, wait_mode);
				if (ret != 0) {
					Ddim_Print(("DMA Util Copy Sync. Wait_End ERR : ret=0x%x, status=0x%x\n", ret, status));
					break;
				}
				break;
			}
			
			ret = Dd_XDMASNAP_Close(ch);
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
			
			ret = Dd_XDMASNAP_Set_Trns_Size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Dd_XDMASNAP_Get_Status ERR : ret=0x%x\n", ret));
				return ret;
			}
			trns_size = Dd_XDMASNAP_Get_Trns_Size(ch);
			Ddim_Print(("Trns_Size==0x%x\n", (unsigned int)trns_size));
			
			break;
			
		// TEST ID 01-02-10
		case 12:
			ch = 0;
			
			dma_trns_size.trns_size = 0x12345678;
			dma_trns_size.src_addr = 0xFFFFFFFF;
			dma_trns_size.dst_addr = 0xFFFFFFFF;
			
			ret = Dd_XDMASNAP_Set_Trns_Size(ch,&dma_trns_size);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Dd_XDMASNAP_Get_Status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			src_addr = Dd_XDMASNAP_Get_Src_Addr(ch);
			dst_addr = Dd_XDMASNAP_Get_Dst_Addr(ch);
			Ddim_Print(("Src_Addr==0x%x\n", (unsigned int)src_addr));
			Ddim_Print(("Dst_Addr==0x%x\n", (unsigned int)dst_addr));
			
			break;
			
		// TEST ID 01-02-11
		case 13:
			Dd_XDMASNAP_Stop_All_Ch();
			
			break;
			
		// TEST ID 01-02-12
		case 14:
			ch = 0;
			
			ret = Dd_XDMASNAP_Clear_Status(ch);
			if (ret != D_DDIM_OK) {
				Ddim_Print(("DMA Util Copy Sync. Dd_XDMASNAP_Clear_Status ERR : ret=0x%x\n", ret));
				return ret;
			}
			
			break;
			
		// TEST ID 01-02-11
		case 15:
			Dd_XDMASNAP_Copy_SDRAM_Sync(0, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE, D_DD_XDMASNAP_WAITMODE_EVENT);
			break;
			
		case 16:
			Dd_XDMASNAP_Copy_SDRAM_Async(0, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_SRC, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_ADR_DST, CtDdXdmasnap1_D_XDMASNAP_AUTO_TEST_SIZE, NULL);
			ret = Dd_XDMASNAP_Wait_End(0, &status, D_DD_XDMASNAP_WAITMODE_EVENT);
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
