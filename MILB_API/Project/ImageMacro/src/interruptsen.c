/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :王睿
*@brief               :sns 索喜rtos
*@rely               :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "interruptsen.h"
#include "interruptdefine.h"
#include "interruptfactor.h"
#include "interruptcallback.h"
#include "jdspro.h"
#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

K_TYPE_DEFINE_WITH_PRIVATE(InterruptSen, interrupt_sen);
#define INTERRUPT_SEN_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), InterruptSenPrivate, INTERRUPT_TYPE_SEN))

struct _InterruptSenPrivate
{
	int a;
};

static void interrupt_sen_constructor(InterruptSen *self)
{
	InterruptSenPrivate *priv = INTERRUPT_SEN_GET_PRIVATE(self);
	priv->a=0;
}

static void interrupt_sen_destructor(InterruptSen *self)
{
	InterruptSenPrivate *priv = INTERRUPT_SEN_GET_PRIVATE(self);
	priv->a=0;
}

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
static	volatile	TimproCallbackInfo	S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC														= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SG_VD_CALLBACK_FUNC															= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC													= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC													= {0};
static	volatile	TimproCallbackInfo	S_GIM_PRO_CMIPI_CALLBACK_FUNC[D_IM_PRO_SEN_CMIPI_CH_NUM][E_IM_PRO_CMIPI_INT_CATE_1+1]	= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_SLVS_CALLBACK_FUNC[D_IM_PRO_SEN_SLVS_CH_NUM][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2 + 1]			= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_LVDS_CALLBACK_FUNC[D_IM_PRO_SEN_LVDS_CH_NUM][E_IM_PRO_LVDS_OUTPUT_MODE_MAX]	= {{{0}}};
static	volatile	TimproCallbackInfo	S_GIM_PRO_DMIPI_CALLBACK_FUNC[D_IM_PRO_SEN_DMIPI_CH_NUM]								= {{0}};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_VD[8] = {
	{ D_IM_PRO_INT_VDF00,	D_IM_PRO_INT_VDE00,	D_IM_PRO_INT_VDF00 },
	{ D_IM_PRO_INT_VDF01,	D_IM_PRO_INT_VDE01,	D_IM_PRO_INT_VDF01 },
	{ D_IM_PRO_INT_VDF10,	D_IM_PRO_INT_VDE10,	D_IM_PRO_INT_VDF10 },
	{ D_IM_PRO_INT_VDF11,	D_IM_PRO_INT_VDE11,	D_IM_PRO_INT_VDF11 },
	{ D_IM_PRO_INT_VDF20,	D_IM_PRO_INT_VDE20,	D_IM_PRO_INT_VDF20 },
	{ D_IM_PRO_INT_VDF21,	D_IM_PRO_INT_VDE21,	D_IM_PRO_INT_VDF21 },
	{ D_IM_PRO_INT_VDF30,	D_IM_PRO_INT_VDE30,	D_IM_PRO_INT_VDF30 },
	{ D_IM_PRO_INT_VDF31,	D_IM_PRO_INT_VDE31,	D_IM_PRO_INT_VDF31 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SG_VD[4] = {
	{ D_IM_PRO_INT_SGVDF0,	D_IM_PRO_INT_SGVDE0,	D_IM_PRO_INT_SGVDF0 },
	{ D_IM_PRO_INT_SGVDF1,	D_IM_PRO_INT_SGVDE1,	D_IM_PRO_INT_SGVDF1 },
	{ D_IM_PRO_INT_SGVDF2,	D_IM_PRO_INT_SGVDE2,	D_IM_PRO_INT_SGVDF2 },
	{ D_IM_PRO_INT_SGVDF3,	D_IM_PRO_INT_SGVDE3,	D_IM_PRO_INT_SGVDF3 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_GYRO[8] = {
	{ D_IM_PRO_INT_GYRO_SOFF0,	D_IM_PRO_INT_GYRO_SOFE0,	D_IM_PRO_INT_GYRO_SOFF0 },
	{ D_IM_PRO_INT_GYRO_EOFF0,	D_IM_PRO_INT_GYRO_EOFE0,	D_IM_PRO_INT_GYRO_EOFF0 },
	{ D_IM_PRO_INT_GYRO_SOFF1,	D_IM_PRO_INT_GYRO_SOFE1,	D_IM_PRO_INT_GYRO_SOFF1 },
	{ D_IM_PRO_INT_GYRO_EOFF1,	D_IM_PRO_INT_GYRO_EOFE1,	D_IM_PRO_INT_GYRO_EOFF1 },
	{ D_IM_PRO_INT_GYRO_SOFF2,	D_IM_PRO_INT_GYRO_SOFE2,	D_IM_PRO_INT_GYRO_SOFF2 },
	{ D_IM_PRO_INT_GYRO_EOFF2,	D_IM_PRO_INT_GYRO_EOFE2,	D_IM_PRO_INT_GYRO_EOFF2 },
	{ D_IM_PRO_INT_GYRO_SOFF3,	D_IM_PRO_INT_GYRO_SOFE3,	D_IM_PRO_INT_GYRO_SOFF3 },
	{ D_IM_PRO_INT_GYRO_EOFF3,	D_IM_PRO_INT_GYRO_EOFE3,	D_IM_PRO_INT_GYRO_EOFF3 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SLVS_COMMON[24] = {
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE7_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE6_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE5_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE4_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE3_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE2_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE1_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IC_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IC_LANE0_BIT  },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE7_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE6_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE5_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE4_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE3_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE2_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE1_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_RDE_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_RDE_LANE0_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE7_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE7_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE6_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE6_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE5_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE5_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE4_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE4_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE3_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE3_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE2_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE2_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE1_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE1_BIT },
	{ D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTST_IPC_LANE0_BIT,	D_IM_PRO_SLVS_COMMON_PEINTEN_IPC_LANE0_BIT },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SLVS_INT[6] = {
	{ D_IM_PRO_SLVS_INTST_FSI_BIT,	D_IM_PRO_SLVS_INTEN_FSI_BIT,	D_IM_PRO_SLVS_INTST_FSI_BIT  },
	{ D_IM_PRO_SLVS_INTST_FSO_BIT,	D_IM_PRO_SLVS_INTEN_FSO_BIT,	D_IM_PRO_SLVS_INTST_FSO_BIT  },
	{ D_IM_PRO_SLVS_INTST_FEI_BIT,	D_IM_PRO_SLVS_INTEN_FEI_BIT,	D_IM_PRO_SLVS_INTST_FEI_BIT  },
	{ D_IM_PRO_SLVS_INTST_FEO_BIT,	D_IM_PRO_SLVS_INTEN_FEO_BIT,	D_IM_PRO_SLVS_INTST_FEO_BIT  },
	{ D_IM_PRO_SLVS_INTST_RDY_BIT,	D_IM_PRO_SLVS_INTEN_RDY_BIT,	D_IM_PRO_SLVS_INTST_RDY_BIT  },
	{ D_IM_PRO_SLVS_INTST_STBY_BIT,	D_IM_PRO_SLVS_INTEN_STBY_BIT,	D_IM_PRO_SLVS_INTST_STBY_BIT },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SLVS_LEINT[10] = {
	{ D_IM_PRO_SLVS_LEINTST_LBOVF_BIT,	D_IM_PRO_SLVS_LEINTEN_LBOVF_BIT,	D_IM_PRO_SLVS_LEINTST_LBOVF_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_LNE_BIT,	D_IM_PRO_SLVS_LEINTEN_LNE_BIT,		D_IM_PRO_SLVS_LEINTST_LNE_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_ECCE_BIT,	D_IM_PRO_SLVS_LEINTEN_ECCE_BIT,		D_IM_PRO_SLVS_LEINTST_ECCE_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_ECC2C_BIT,	D_IM_PRO_SLVS_LEINTEN_ECC2C_BIT,	D_IM_PRO_SLVS_LEINTST_ECC2C_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_ECC1C_BIT,	D_IM_PRO_SLVS_LEINTEN_ECC1C_BIT,	D_IM_PRO_SLVS_LEINTST_ECC1C_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_HCRCE_BIT,	D_IM_PRO_SLVS_LEINTEN_HCRCE_BIT,	D_IM_PRO_SLVS_LEINTST_HCRCE_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_HCRC2C_BIT,	D_IM_PRO_SLVS_LEINTEN_HCRC2C_BIT,	D_IM_PRO_SLVS_LEINTST_HCRC2C_BIT	},
	{ D_IM_PRO_SLVS_LEINTST_HCRC1C_BIT,	D_IM_PRO_SLVS_LEINTEN_HCRC1C_BIT,	D_IM_PRO_SLVS_LEINTST_HCRC1C_BIT	},
	{ D_IM_PRO_SLVS_LEINTST_PCRCE_BIT,	D_IM_PRO_SLVS_LEINTEN_PCRCE_BIT,	D_IM_PRO_SLVS_LEINTST_PCRCE_BIT		},
	{ D_IM_PRO_SLVS_LEINTST_LLE_BIT,	D_IM_PRO_SLVS_LEINTEN_LLE_BIT,		D_IM_PRO_SLVS_LEINTST_LLE_BIT		},
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SLVS_MEINT0[4] = {
	{ D_IM_PRO_SLVS_MEINTST0_DSD_BIT,	D_IM_PRO_SLVS_MEINTEN0_DSD_BIT,	D_IM_PRO_SLVS_MEINTST0_DSD_BIT },
	{ D_IM_PRO_SLVS_MEINTST0_DCL_BIT,	D_IM_PRO_SLVS_MEINTEN0_DCL_BIT,	D_IM_PRO_SLVS_MEINTST0_DCL_BIT },
	{ D_IM_PRO_SLVS_MEINTST0_SCL_BIT,	D_IM_PRO_SLVS_MEINTEN0_SCL_BIT,	D_IM_PRO_SLVS_MEINTST0_SCL_BIT },
	{ D_IM_PRO_SLVS_MEINTST0_ECL_BIT,	D_IM_PRO_SLVS_MEINTEN0_ECL_BIT,	D_IM_PRO_SLVS_MEINTST0_ECL_BIT },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_SLVS_MEINT1[16] = {
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE7_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE7_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE7_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE6_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE6_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE6_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE5_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE5_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE5_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE4_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE4_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE4_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE3_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE3_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE3_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE2_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE2_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE2_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE1_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE1_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE1_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FUNF_LANE0_BIT,	D_IM_PRO_SLVS_MEINTEN1_FUNF_LANE0_BIT,	D_IM_PRO_SLVS_MEINTST1_FUNF_LANE0_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE7_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE7_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE7_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE6_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE6_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE6_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE5_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE5_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE5_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE4_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE4_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE4_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE3_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE3_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE3_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE2_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE2_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE2_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE1_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE1_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE1_BIT },
	{ D_IM_PRO_SLVS_MEINTST1_FOVF_LANE0_BIT,	D_IM_PRO_SLVS_MEINTEN1_FOVF_LANE0_BIT,	D_IM_PRO_SLVS_MEINTST1_FOVF_LANE0_BIT },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_LVDS_NORMAL_INT[4] = {
	{ D_IM_PRO_LVDSINTFLG_SOFF0,	D_IM_PRO_LVDSINTENB_SOFE0,	D_IM_PRO_LVDSINTFLG_SOFF0 },
	{ D_IM_PRO_LVDSINTFLG_EOFF0,	D_IM_PRO_LVDSINTENB_EOFE0,	D_IM_PRO_LVDSINTFLG_EOFF0 },
	{ D_IM_PRO_LVDSINTFLG_SOLF0,	D_IM_PRO_LVDSINTENB_SOLE0,	D_IM_PRO_LVDSINTFLG_SOLF0 },
	{ D_IM_PRO_LVDSINTFLG_EOLF0,	D_IM_PRO_LVDSINTENB_EOLE0,	D_IM_PRO_LVDSINTFLG_EOLF0 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_LVDS_DOL1_INT[4] = {
	{ D_IM_PRO_LVDSINTFLG_SOFF1,	D_IM_PRO_LVDSINTENB_SOFE1,	D_IM_PRO_LVDSINTFLG_SOFF1 },
	{ D_IM_PRO_LVDSINTFLG_EOFF1,	D_IM_PRO_LVDSINTENB_EOFE1,	D_IM_PRO_LVDSINTFLG_EOFF1 },
	{ D_IM_PRO_LVDSINTFLG_SOLF1,	D_IM_PRO_LVDSINTENB_SOLE1,	D_IM_PRO_LVDSINTFLG_SOLF1 },
	{ D_IM_PRO_LVDSINTFLG_EOLF1,	D_IM_PRO_LVDSINTENB_EOLE1,	D_IM_PRO_LVDSINTFLG_EOLF1 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_LVDS_DOL2_INT[4] = {
	{ D_IM_PRO_LVDSINTFLG_SOFF2,	D_IM_PRO_LVDSINTENB_SOFE2,	D_IM_PRO_LVDSINTFLG_SOFF2 },
	{ D_IM_PRO_LVDSINTFLG_EOFF2,	D_IM_PRO_LVDSINTENB_EOFE2,	D_IM_PRO_LVDSINTFLG_EOFF2 },
	{ D_IM_PRO_LVDSINTFLG_SOLF2,	D_IM_PRO_LVDSINTENB_SOLE2,	D_IM_PRO_LVDSINTFLG_SOLF2 },
	{ D_IM_PRO_LVDSINTFLG_EOLF2,	D_IM_PRO_LVDSINTENB_EOLE2,	D_IM_PRO_LVDSINTFLG_EOLF2 },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_CMIPI_INT1[27] = {
	{ D_IM_PRO_MPICINTF1_CECF2,		D_IM_PRO_MPICINTE1_CEC2,		D_IM_PRO_MPICINTF1_CECF2	},
	{ D_IM_PRO_MPICINTF1_CECF1,		D_IM_PRO_MPICINTE1_CEC1,		D_IM_PRO_MPICINTF1_CECF1	},
	{ D_IM_PRO_MPICINTF1_CECF0,		D_IM_PRO_MPICINTE1_CEC0,		D_IM_PRO_MPICINTF1_CECF0	},
	{ D_IM_PRO_MPICINTF1_CEEF2,		D_IM_PRO_MPICINTE1_CEE2,		D_IM_PRO_MPICINTF1_CEEF2	},
	{ D_IM_PRO_MPICINTF1_CEEF1,		D_IM_PRO_MPICINTE1_CEE1,		D_IM_PRO_MPICINTF1_CEEF1	},
	{ D_IM_PRO_MPICINTF1_CEEF0,		D_IM_PRO_MPICINTE1_CEE0,		D_IM_PRO_MPICINTF1_CEEF0	},
	{ D_IM_PRO_MPICINTF1_CESSHF2,	D_IM_PRO_MPICINTE1_CESSH2,		D_IM_PRO_MPICINTF1_CESSHF2	},
	{ D_IM_PRO_MPICINTF1_CESSHF1,	D_IM_PRO_MPICINTE1_CESSH1,		D_IM_PRO_MPICINTF1_CESSHF1	},
	{ D_IM_PRO_MPICINTF1_CESSHF0,	D_IM_PRO_MPICINTE1_CESSH0,		D_IM_PRO_MPICINTF1_CESSHF0	},
	{ D_IM_PRO_MPICINTF1_CESHF2,	D_IM_PRO_MPICINTE1_CESH2,		D_IM_PRO_MPICINTF1_CESHF2	},
	{ D_IM_PRO_MPICINTF1_CESHF1,	D_IM_PRO_MPICINTE1_CESH1,		D_IM_PRO_MPICINTF1_CESHF1	},
	{ D_IM_PRO_MPICINTF1_CESHF0,	D_IM_PRO_MPICINTE1_CESH0,		D_IM_PRO_MPICINTF1_CESHF0	},
	{ D_IM_PRO_MPICINTF1_FEO1F,		D_IM_PRO_MPICINTE1_FEO1,		D_IM_PRO_MPICINTF1_FEO1F	},
	{ D_IM_PRO_MPICINTF1_FEO0F,		D_IM_PRO_MPICINTE1_FEO0,		D_IM_PRO_MPICINTF1_FEO0F	},
	{ D_IM_PRO_MPICINTF1_FEI1F,		D_IM_PRO_MPICINTE1_FEI1,		D_IM_PRO_MPICINTF1_FEI1F	},
	{ D_IM_PRO_MPICINTF1_FEI0F,		D_IM_PRO_MPICINTE1_FEI0,		D_IM_PRO_MPICINTF1_FEI0F	},
	{ D_IM_PRO_MPICINTF1_FSO1F,		D_IM_PRO_MPICINTE1_FSO1,		D_IM_PRO_MPICINTF1_FSO1F	},
	{ D_IM_PRO_MPICINTF1_FSO0F,		D_IM_PRO_MPICINTE1_FSO0,		D_IM_PRO_MPICINTF1_FSO0F	},
	{ D_IM_PRO_MPICINTF1_FSI1F,		D_IM_PRO_MPICINTE1_FSI1,		D_IM_PRO_MPICINTF1_FSI1F	},
	{ D_IM_PRO_MPICINTF1_FSI0F,		D_IM_PRO_MPICINTE1_FSI0,		D_IM_PRO_MPICINTF1_FSI0F	},
	{ D_IM_PRO_MPICINTF1_LZEF2,		D_IM_PRO_MPICINTE1_LZE2,		D_IM_PRO_MPICINTF1_LZEF2	},
	{ D_IM_PRO_MPICINTF1_LZEF1,		D_IM_PRO_MPICINTE1_LZE1,		D_IM_PRO_MPICINTF1_LZEF1	},
	{ D_IM_PRO_MPICINTF1_LZEF0,		D_IM_PRO_MPICINTE1_LZE0,		D_IM_PRO_MPICINTF1_LZEF0	},
	{ D_IM_PRO_MPICINTF1_EFSF,		D_IM_PRO_MPICINTE1_EFS,			D_IM_PRO_MPICINTF1_EFSF		},
	{ D_IM_PRO_MPICINTF1_CRCDTEF,	D_IM_PRO_MPICINTE1_CRCDTE,		D_IM_PRO_MPICINTF1_CRCDTEF	},
	{ D_IM_PRO_MPICINTF1_PHCRC2EF,	D_IM_PRO_MPICINTE1_PHCRC2E,		D_IM_PRO_MPICINTF1_PHCRC2EF	},
	{ D_IM_PRO_MPICINTF1_PHCRC1EF,	D_IM_PRO_MPICINTE1_PHCRC1E,		D_IM_PRO_MPICINTF1_PHCRC1EF	},
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_CMIPI_INT2[4] = {
	{ D_IM_PRO_MPICINTF2_CICHSF2,	D_IM_PRO_MPICINTE2_CICHSE2,		D_IM_PRO_MPICINTF2_CICHSF2 },
	{ D_IM_PRO_MPICINTF2_CICHSF1,	D_IM_PRO_MPICINTE2_CICHSE1,		D_IM_PRO_MPICINTF2_CICHSF1 },
	{ D_IM_PRO_MPICINTF2_CICHSF0,	D_IM_PRO_MPICINTE2_CICHSE0,		D_IM_PRO_MPICINTF2_CICHSF0 },
	{ D_IM_PRO_MPICINTF2_PHCRCAEF,	D_IM_PRO_MPICINTE2_PHCRCAEE,	D_IM_PRO_MPICINTF2_PHCRCAEF },
};

static const TimproIntflgTbl S_GIM_PRO_INTTBL_SEN_DMIPI_INT[32] = {
	{ D_IM_PRO_MPIINTF_DEC3,	D_IM_PRO_MPIINTE_DEC3,		D_IM_PRO_MPIINTF_DEC3	 },
	{ D_IM_PRO_MPIINTF_DEC2,	D_IM_PRO_MPIINTE_DEC2,		D_IM_PRO_MPIINTF_DEC2	 },
	{ D_IM_PRO_MPIINTF_DEC1,	D_IM_PRO_MPIINTE_DEC1,		D_IM_PRO_MPIINTF_DEC1	 },
	{ D_IM_PRO_MPIINTF_DEC0,	D_IM_PRO_MPIINTE_DEC0,		D_IM_PRO_MPIINTF_DEC0	 },
	{ D_IM_PRO_MPIINTF_DEE3,	D_IM_PRO_MPIINTE_DEE3,		D_IM_PRO_MPIINTF_DEE3	 },
	{ D_IM_PRO_MPIINTF_DEE2,	D_IM_PRO_MPIINTE_DEE2,		D_IM_PRO_MPIINTF_DEE2	 },
	{ D_IM_PRO_MPIINTF_DEE1,	D_IM_PRO_MPIINTE_DEE1,		D_IM_PRO_MPIINTF_DEE1	 },
	{ D_IM_PRO_MPIINTF_DEE0,	D_IM_PRO_MPIINTE_DEE0,		D_IM_PRO_MPIINTF_DEE0	 },
	{ D_IM_PRO_MPIINTF_DESSH3,	D_IM_PRO_MPIINTE_DESSH3,	D_IM_PRO_MPIINTF_DESSH3	 },
	{ D_IM_PRO_MPIINTF_DESSH2,	D_IM_PRO_MPIINTE_DESSH2,	D_IM_PRO_MPIINTF_DESSH2	 },
	{ D_IM_PRO_MPIINTF_DESSH1,	D_IM_PRO_MPIINTE_DESSH1,	D_IM_PRO_MPIINTF_DESSH1	 },
	{ D_IM_PRO_MPIINTF_DESSH0,	D_IM_PRO_MPIINTE_DESSH0,	D_IM_PRO_MPIINTF_DESSH0	 },
	{ D_IM_PRO_MPIINTF_DESH3,	D_IM_PRO_MPIINTE_DESHE3,	D_IM_PRO_MPIINTF_DESH3	 },
	{ D_IM_PRO_MPIINTF_DESH2,	D_IM_PRO_MPIINTE_DESHE2,	D_IM_PRO_MPIINTF_DESH2	 },
	{ D_IM_PRO_MPIINTF_DESH1,	D_IM_PRO_MPIINTE_DESHE1,	D_IM_PRO_MPIINTF_DESH1	 },
	{ D_IM_PRO_MPIINTF_DESH0,	D_IM_PRO_MPIINTE_DESHE0,	D_IM_PRO_MPIINTF_DESH0	 },
	{ D_IM_PRO_MPIINTF_FEO1,	D_IM_PRO_MPIINTE_FEO1,		D_IM_PRO_MPIINTF_FEO1	 },
	{ D_IM_PRO_MPIINTF_FEO0,	D_IM_PRO_MPIINTE_FEO0,		D_IM_PRO_MPIINTF_FEO0	 },
	{ D_IM_PRO_MPIINTF_FEI1,	D_IM_PRO_MPIINTE_FEI1,		D_IM_PRO_MPIINTF_FEI1	 },
	{ D_IM_PRO_MPIINTF_FEI0,	D_IM_PRO_MPIINTE_FEI0,		D_IM_PRO_MPIINTF_FEI0	 },
	{ D_IM_PRO_MPIINTF_FSO1,	D_IM_PRO_MPIINTE_FSO1,		D_IM_PRO_MPIINTF_FSO1	 },
	{ D_IM_PRO_MPIINTF_FSO0,	D_IM_PRO_MPIINTE_FSO0,		D_IM_PRO_MPIINTF_FSO0	 },
	{ D_IM_PRO_MPIINTF_FSI1,	D_IM_PRO_MPIINTE_FSI1,		D_IM_PRO_MPIINTF_FSI1	 },
	{ D_IM_PRO_MPIINTF_FSI0,	D_IM_PRO_MPIINTE_FSI0,		D_IM_PRO_MPIINTF_FSI0	 },
	{ D_IM_PRO_MPIINTF_LZE3,	D_IM_PRO_MPIINTE_LZE3,		D_IM_PRO_MPIINTF_LZE3	 },
	{ D_IM_PRO_MPIINTF_LZE2,	D_IM_PRO_MPIINTE_LZE2,		D_IM_PRO_MPIINTF_LZE2	 },
	{ D_IM_PRO_MPIINTF_LZE1,	D_IM_PRO_MPIINTE_LZE1,		D_IM_PRO_MPIINTF_LZE1	 },
	{ D_IM_PRO_MPIINTF_LZE0,	D_IM_PRO_MPIINTE_LZE0,		D_IM_PRO_MPIINTF_LZE0	 },
	{ D_IM_PRO_MPIINTF_EFS,		D_IM_PRO_MPIINTE_EFS,		D_IM_PRO_MPIINTF_EFS	 },
	{ D_IM_PRO_MPIINTF_CRCE,	D_IM_PRO_MPIINTE_CRCE,		D_IM_PRO_MPIINTF_CRCE	 },
	{ D_IM_PRO_MPIINTF_ECCW,	D_IM_PRO_MPIINTE_ECCW,		D_IM_PRO_MPIINTF_ECCW	 },
	{ D_IM_PRO_MPIINTF_ECCE,	D_IM_PRO_MPIINTE_ECCE,		D_IM_PRO_MPIINTF_ECCE	 },
};

/*----------------------------------------------------------------------*/
/* DECLS                           											   */
/*----------------------------------------------------------------------*/
static VOID imProSenVdIntHandlerPrint( UCHAR status );
static VOID imProCallbackSensorIfInt( UCHAR sencoreCh, TimproSencoreIntFactor* intFactor );
static VOID imProClearSensorIfIntFactorPrint( UCHAR sencoreCh, UCHAR status );
static VOID imProClearSensorIfIntFactor( UCHAR sencoreCh, TimproSencoreIntFactor* intFactor );

/*----------------------------------------------------------------------*/
/* IMPL														                   */
/*----------------------------------------------------------------------*/
static VOID imProSenVdIntHandlerPrint( UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "imProSenVdIntHandlerPrint() VHDINTFLG1(0x%08x) VHDINTENB1(0x%08x) (status:%u)\n", IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG1.word, IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB1.word, status ));
	Ddim_Print(( "imProSenVdIntHandlerPrint() SGVHDINTFLG(0x%08x) SGVHDINTENB(0x%08x) (status:%u)\n", IO_PRO.SEN.SENTOP.SGVHDINTFLG.word, IO_PRO.SEN.SENTOP.SGVHDINTENB.word, status ));
	Ddim_Print(( "imProSenVdIntHandlerPrint() GINTFLG(0x%08x) GINTENB(0x%08x) (status:%u)\n", IO_PRO.SEN.SENTOP.GINTFLG.word, IO_PRO.SEN.SENTOP.GINTENB.word, status ));
#endif
}

static VOID imProCallbackSensorIfInt( UCHAR sencoreCh, TimproSencoreIntFactor* intFactor )
{
	UINT32	loopcnt;
	UINT32	chLoopcnt;
	ULONG	callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= 0,
		.block_type	= 0,
		.channel	= 0,
	};
	DDIM_USER_FLGPTN	flgptn = 0;

	if( sencoreCh == 0 ) {
		/***************/
		/* SLVS Common */
		/***************/
		callbackResult = 0;
		for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_COMMON) / sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_COMMON[0])); loopcnt++ ) {
			if( (intFactor->slvsCommonIntf & S_GIM_PRO_INTTBL_SEN_SLVS_COMMON[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SEN_SLVS_COMMON[loopcnt].intFact;
			}
		}
		// Callback
		if (( S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
			cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
			cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
			cbId.channel		= sencoreCh,
			S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC.userParam );
		}

		// Each stream interrupt
		for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_SEN_SLVS_CH_NUM; chLoopcnt++ ) {
			/*************/
			/* SLVS INT  */
			/*************/
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_INT[0])); loopcnt++ ) {
				if( (intFactor->slvsIntf[chLoopcnt] & S_GIM_PRO_INTTBL_SEN_SLVS_INT[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_SLVS_INT[loopcnt].intFact;

					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_FSI_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_FSI_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_FSI_WAITEND_FLG;
					}
					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_FSO_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_FSO_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_FSO_WAITEND_FLG;
					}
					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_FEI_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_FEI_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_FEI_WAITEND_FLG;
					}
					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_FEO_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_FEO_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_FEO_WAITEND_FLG;
					}
					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_RDY_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_RDY_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_RDY_WAITEND_FLG;
					}
					if ((intFactor->slvsIntf[chLoopcnt] & D_IM_PRO_SLVS_INTST_STBY_BIT) != 0){
						flgptn |= (chLoopcnt == 0) ? D_IM_PRO_SLVS_STREAM_A_INTST_STBY_WAITEND_FLG : D_IM_PRO_SLVS_STREAM_B_INTST_STBY_WAITEND_FLG;
					}
				}
			}
			if( flgptn != 0 ) {
				DDIM_User_Set_Flg( FID_IM_SEN, flgptn );
			}

			// Callback
			if (( S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_INTN_O].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
				cbId.channel		= sencoreCh,
				S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_INTN_O].pCallback( &cbId, callbackResult, S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_INTN_O].userParam );
			}
			/***************/
			/* SLVS LEINT  */
			/***************/
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_LEINT) / sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_LEINT[0])); loopcnt++ ) {
				if( (intFactor->slvsLeintf[chLoopcnt] & S_GIM_PRO_INTTBL_SEN_SLVS_LEINT[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_SLVS_LEINT[loopcnt].intFact;
				}
			}
			// Callback
			if (( S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_LINK_ERR].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
				cbId.channel		= chLoopcnt,
				S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_LINK_ERR].pCallback( &cbId, callbackResult, S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_LINK_ERR].userParam);
			}
			/***************/
			/* SLVS MEINT0 */
			/***************/
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_MEINT0) / sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_MEINT0[0])); loopcnt++ ) {
				if( (intFactor->slvsMeintf0[chLoopcnt] & S_GIM_PRO_INTTBL_SEN_SLVS_MEINT0[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_SLVS_MEINT0[loopcnt].intFact;
				}
			}
			// Callback
			if (( S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
				cbId.channel		= chLoopcnt,
				S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1].pCallback( &cbId, callbackResult, S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR1].userParam );
			}
			/***************/
			/* SLVS MEINT1 */
			/***************/
			callbackResult = 0;
			for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_MEINT1) / sizeof(S_GIM_PRO_INTTBL_SEN_SLVS_MEINT1[0])); loopcnt++ ) {
				if( (intFactor->slvsMeintf1[chLoopcnt] & S_GIM_PRO_INTTBL_SEN_SLVS_MEINT1[loopcnt].flgBitmask) != 0 ) {
					callbackResult	|= S_GIM_PRO_INTTBL_SEN_SLVS_MEINT1[loopcnt].intFact;
				}
			}
			// Callback
			if (( S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2].pCallback != NULL ) && ( callbackResult != 0 )){
				cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
				cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
				cbId.channel		= chLoopcnt,
				S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2].pCallback( &cbId, callbackResult, S_GIM_PRO_SLVS_CALLBACK_FUNC[chLoopcnt][E_IM_PRO_SLVS_INT_TYPE_MAC_ERR2].userParam );
			}
		}
	}
	/********************/
	/* LVDS Normal INT  */
	/********************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_NORMAL_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_NORMAL_INT[0])); loopcnt++ ) {
		if( (intFactor->lvdsIntf0 & S_GIM_PRO_INTTBL_SEN_LVDS_NORMAL_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_LVDS_NORMAL_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][0].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][0].pCallback( &cbId, callbackResult, S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][0].userParam );
	}
	/********************/
	/* LVDS DOL1 INT    */
	/********************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_DOL1_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_DOL1_INT[0])); loopcnt++ ) {
		if( (intFactor->lvdsIntf1 & S_GIM_PRO_INTTBL_SEN_LVDS_DOL1_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_LVDS_DOL1_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][1].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][1].pCallback( &cbId, callbackResult, S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][1].userParam );
	}
	/********************/
	/* LVDS DOL2 INT    */
	/********************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_DOL2_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_LVDS_DOL2_INT[0])); loopcnt++ ) {
		if( (intFactor->lvdsIntf2 & S_GIM_PRO_INTTBL_SEN_LVDS_DOL2_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_LVDS_DOL2_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][2].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][2].pCallback( &cbId, callbackResult, S_GIM_PRO_LVDS_CALLBACK_FUNC[sencoreCh][2].userParam );
	}
	/***************/
	/* D-MIPI      */
	/***************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_DMIPI_INT) / sizeof(S_GIM_PRO_INTTBL_SEN_DMIPI_INT[0])); loopcnt++ ) {
		if( (intFactor->dmipiIntf & S_GIM_PRO_INTTBL_SEN_DMIPI_INT[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_DMIPI_INT[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_DMIPI_CALLBACK_FUNC[sencoreCh].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_DMIPI_CALLBACK_FUNC[sencoreCh].pCallback( &cbId, callbackResult, S_GIM_PRO_DMIPI_CALLBACK_FUNC[sencoreCh].userParam );
	}
	/********************/
	/* C-MIPI category0 */
	/********************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_CMIPI_INT1) / sizeof(S_GIM_PRO_INTTBL_SEN_CMIPI_INT1[0])); loopcnt++ ) {
		if( (intFactor->cmipiIntf1 & S_GIM_PRO_INTTBL_SEN_CMIPI_INT1[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_CMIPI_INT1[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_0].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_0].pCallback( &cbId, callbackResult, S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_0].userParam );
	}
	/********************/
	/* C-MIPI category1 */
	/********************/
	callbackResult = 0;
	for( loopcnt = 0; loopcnt < (sizeof(S_GIM_PRO_INTTBL_SEN_CMIPI_INT2) / sizeof(S_GIM_PRO_INTTBL_SEN_CMIPI_INT2[0])); loopcnt++ ) {
		if( (intFactor->cmipiIntf2 & S_GIM_PRO_INTTBL_SEN_CMIPI_INT2[loopcnt].flgBitmask) != 0 ) {
			callbackResult	|= S_GIM_PRO_INTTBL_SEN_CMIPI_INT2[loopcnt].intFact;
		}
	}
	// Callback
	if (( S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_1].pCallback != NULL ) && ( callbackResult != 0 )){
		cbId.unit_no		= E_IM_PRO_UNIT_NUM_1,
		cbId.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		cbId.channel		= sencoreCh,
		S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_1].pCallback( &cbId, callbackResult, S_GIM_PRO_CMIPI_CALLBACK_FUNC[sencoreCh][E_IM_PRO_CMIPI_INT_CATE_1].userParam );
	}
	/***************/
	/* MONI        */
	/***************/
	callbackResult = 0;
	interrupt_callback_monifunc(interrupt_callback_new(),loopcnt, intFactor, callbackResult, &cbId, sencoreCh);
}

static VOID imProClearSensorIfIntFactorPrint( UCHAR sencoreCh, UCHAR status )
{
#ifdef CO_DEBUG_PRINT_IM_PRO
	if( sencoreCh == 0 ) {
		UCHAR slvs_ch;
		for( slvs_ch = 0; slvs_ch < D_IM_PRO_SEN_SLVS_CH_NUM; slvs_ch++ ) {
			Ddim_Print(( "imProClearSensorIfIntFactor(%u) SLVS  PEINTST (0x%08x) PEINTEN (0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.SLVSEC.COMMON.PEINTST.word, IO_PRO.SEN.SLVSEC.COMMON.PEINTEN.word, status ));
			Ddim_Print(( "imProClearSensorIfIntFactor(%u) SLVS  INTST   (0x%08x) INTEN   (0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].INTST.word, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].INTEN.word, status ));
			Ddim_Print(( "imProClearSensorIfIntFactor(%u) SLVS  LEINTST (0x%08x) LEINTEN (0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].LEINTST.word, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].LEINTEN.word, status ));
			Ddim_Print(( "imProClearSensorIfIntFactor(%u) SLVS  MEINTST0(0x%08x) MEINTEN0(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].MEINTST0.word, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].MEINTEN0.word, status ));
			Ddim_Print(( "imProClearSensorIfIntFactor(%u) SLVS  MEINTST1(0x%08x) MEINTEN1(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].MEINTST1.word, IO_PRO.SEN.SLVSEC.STREAM[slvs_ch].MEINTEN1.word, status ));
		}
	}

	Ddim_Print(( "imProClearSensorIfIntFactor(%u) LVDS  LVDSINTFLG0(0x%08x) LVDSINTENB0(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG0.word, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB0.word, status ));
	Ddim_Print(( "imProClearSensorIfIntFactor(%u) LVDS  LVDSINTFLG1(0x%08x) LVDSINTENB1(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG1.word, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB1.word, status ));
	Ddim_Print(( "imProClearSensorIfIntFactor(%u) LVDS  LVDSINTFLG2(0x%08x) LVDSINTENB2(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG2.word, IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB2.word, status ));

	Ddim_Print(( "imProClearSensorIfIntFactor(%u) CMIPI MPICINTF1(0x%08x) MPICINTE1(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF1.word, IO_PRO.SEN.MIPIC[sencoreCh].MPICINTE1.word, status ));
	Ddim_Print(( "imProClearSensorIfIntFactor(%u) CMIPI MPICINTF2(0x%08x) MPICINTE2(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF2.word, IO_PRO.SEN.MIPIC[sencoreCh].MPICINTE2.word, status ));

	Ddim_Print(( "imProClearSensorIfIntFactor(%u) DMIPI MPIINTF(0x%08x) MPIINTE(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.MIPID[sencoreCh].MPIINTF.word, IO_PRO.SEN.MIPID[sencoreCh].MPIINTE.word, status ));

	Ddim_Print(( "imProClearSensorIfIntFactor(%u) MONI  MONIINTFLG(0x%08x) MONIINTENB(0x%08x) (status:%u)\n", sencoreCh, IO_PRO.SEN.MONI[sencoreCh].MONIINTFLG.word, IO_PRO.SEN.MONI[sencoreCh].MONIINTENB.word, status ));
#endif
}

static VOID imProClearSensorIfIntFactor( UCHAR sencoreCh, TimproSencoreIntFactor* intFactor )      //等着
{
	UCHAR	chLoopcnt;

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	Im_Pro_Dsb();
	imProClearSensorIfIntFactorPrint( sencoreCh, 0 );

	// SLVS-EC
	if( sencoreCh == 0 ) {
		// Get & Clear interrupt flag
		intFactor->slvsCommonIntf	= IO_PRO.SEN.SLVSEC.COMMON.PEINTST.word & IO_PRO.SEN.SLVSEC.COMMON.PEINTEN.word;
		IO_PRO.SEN.SLVSEC.COMMON.PEINTST.word	= intFactor->slvsCommonIntf;
		for( chLoopcnt = 0; chLoopcnt < D_IM_PRO_SEN_SLVS_CH_NUM; chLoopcnt++ ) {
			intFactor->slvsIntf[chLoopcnt]		= IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].INTST.word & IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].INTEN.word;
			IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].INTST.word	= intFactor->slvsIntf[chLoopcnt];

			intFactor->slvsLeintf[chLoopcnt]		= IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].LEINTST.word & IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].LEINTEN.word;
			IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].LEINTST.word	= intFactor->slvsLeintf[chLoopcnt];

			intFactor->slvsMeintf0[chLoopcnt]	= IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTST0.word & IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTEN0.word;
			IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTST0.word = intFactor->slvsMeintf0[chLoopcnt];

			intFactor->slvsMeintf1[chLoopcnt]	= IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTST1.word & IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTEN1.word;
			IO_PRO.SEN.SLVSEC.STREAM[chLoopcnt].MEINTST1.word = intFactor->slvsMeintf1[chLoopcnt];
		}
	}

	// LVDS
	// Get interrupt flag
	intFactor->lvdsIntf0	= IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG0.word & IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB0.word;
	intFactor->lvdsIntf1	= IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG1.word & IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB1.word;
	intFactor->lvdsIntf2	= IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG2.word & IO_PRO.SEN.LVDS[sencoreCh].LVDSINTENB2.word;

	// Clear interrupt flag
	IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG0.word	= intFactor->lvdsIntf0;
	IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG1.word	= intFactor->lvdsIntf1;
	IO_PRO.SEN.LVDS[sencoreCh].LVDSINTFLG2.word	= intFactor->lvdsIntf2;

	//************* C-MIPI *************//
	// Get interrupt flag
	intFactor->cmipiIntf1	= IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF1.word & IO_PRO.SEN.MIPIC[sencoreCh].MPICINTE1.word;
	intFactor->cmipiIntf2	= IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF2.word & IO_PRO.SEN.MIPIC[sencoreCh].MPICINTE2.word;

	// Clear interrupt flag
	IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF1.word	= intFactor->cmipiIntf1;
	IO_PRO.SEN.MIPIC[sencoreCh].MPICINTF2.word	= intFactor->cmipiIntf2;

	//************* D-MIPI *************//
	intFactor->dmipiIntf	= IO_PRO.SEN.MIPID[sencoreCh].MPIINTF.word & IO_PRO.SEN.MIPID[sencoreCh].MPIINTE.word;

	// Clear interrupt flag
	IO_PRO.SEN.MIPID[sencoreCh].MPIINTF.word	= intFactor->dmipiIntf;

	//************* MONI *************//
	intFactor->moniIntf	= IO_PRO.SEN.MONI[sencoreCh].MONIINTFLG.word & IO_PRO.SEN.MONI[sencoreCh].MONIINTENB.word;
	if( intFactor->moniIntf != 0 ) {
		im_pro_comm_update_moni_result( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, sencoreCh );
	}

	// Clear interrupt flag
	IO_PRO.SEN.MONI[sencoreCh].MONIINTFLG.word	= intFactor->moniIntf;

	Im_Pro_Dsb();
	imProClearSensorIfIntFactorPrint( sencoreCh, 1 );
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
}

/*----------------------------------------------------------------------*/
/*PUBLIC   																       */
/*----------------------------------------------------------------------*/
/**
SEN block VD Int handler setting.
@param[in]	inthandler : Interrupt handler address pointer
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_vd_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SEN block VD Int handler.
*/
VOID interrupt_sen_vd_int_handler( VOID )
{
	UINT32			loopcnt;
	ULONG			vdIntf;
	ULONG			sgVdIntf;
	ULONG			gyroIntf;
	ULONG callbackResult = 0;
	T_CALLBACK_ID	cbId = {
		.unit_no	= E_IM_PRO_UNIT_NUM_1,
		.block_type	= E_IM_PRO_BLOCK_TYPE_SEN,
		.channel	= 0,
	};
	UINT32			corecnt;
	UCHAR			coresize;

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_vd_int_handler begin\n" ));
#endif

	im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	Im_Pro_Dsb();
	imProSenVdIntHandlerPrint( 0 );

	// Get interrupt flag
	vdIntf		= IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG1.word & IO_PRO.SEN.SENTOP.VHDINTENB.VHDINTENB1.word;
	sgVdIntf	= IO_PRO.SEN.SENTOP.SGVHDINTFLG.word & IO_PRO.SEN.SENTOP.SGVHDINTENB.word & D_IM_PRO_INT_SGVD_ALL;
	gyroIntf	= IO_PRO.SEN.SENTOP.GINTFLG.word & IO_PRO.SEN.SENTOP.GINTENB.word;

	// Clear interrupt flag
	IO_PRO.SEN.SENTOP.VHDINTFLG.VHDINTFLG1.word	= vdIntf;
	IO_PRO.SEN.SENTOP.SGVHDINTFLG.word			= sgVdIntf;
	IO_PRO.SEN.SENTOP.GINTFLG.word				= gyroIntf;

	Im_Pro_Dsb();
	imProSenVdIntHandlerPrint( 1 );

	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );
	/***********/
	/* VD Edge */
	/***********/
	coresize = ( sizeof(S_GIM_PRO_INTTBL_SEN_VD) / sizeof(S_GIM_PRO_INTTBL_SEN_VD[0]) / D_IM_PRO_SEN_SENCORE_NUM );
	for( corecnt = 0; corecnt < ( D_IM_PRO_SEN_SENCORE_NUM * coresize ); corecnt += coresize ){
		callbackResult = 0;
		for( loopcnt = corecnt; loopcnt < ( corecnt + coresize ); loopcnt++ ) {
			if( (vdIntf & S_GIM_PRO_INTTBL_SEN_VD[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SEN_VD[loopcnt].intFact;
			}
		}
		cbId.channel = corecnt / coresize;
		// Callback
		if (( S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
			S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SENTOP_VD_CALLBACK_FUNC.userParam );
		}
	}
	/**************/
	/* SG VD Edge */
	/**************/
	coresize = ( sizeof(S_GIM_PRO_INTTBL_SEN_SG_VD) / sizeof(S_GIM_PRO_INTTBL_SEN_SG_VD[0]) / D_IM_PRO_SEN_SENCORE_NUM );
	for( corecnt = 0; corecnt < ( D_IM_PRO_SEN_SENCORE_NUM * coresize ); corecnt += coresize ){
		callbackResult = 0;
		for( loopcnt = corecnt; loopcnt < ( corecnt + coresize ); loopcnt++ ) {
			if( (sgVdIntf & S_GIM_PRO_INTTBL_SEN_SG_VD[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SEN_SG_VD[loopcnt].intFact;
			}
		}
		cbId.channel = corecnt / coresize;
		// Callback
		if (( S_GIM_PRO_SG_VD_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
			S_GIM_PRO_SG_VD_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SG_VD_CALLBACK_FUNC.userParam );
		}
	}
	/**************/
	/* Gyro Edge  */
	/**************/
	coresize = ( sizeof(S_GIM_PRO_INTTBL_SEN_GYRO) / sizeof(S_GIM_PRO_INTTBL_SEN_GYRO[0]) / D_IM_PRO_SEN_SENCORE_NUM );
	for( corecnt = 0; corecnt < ( D_IM_PRO_SEN_SENCORE_NUM * coresize ); corecnt += coresize ){
		callbackResult = 0;
		for( loopcnt = corecnt; loopcnt < ( corecnt + coresize ); loopcnt++ ) {
			if( (gyroIntf & S_GIM_PRO_INTTBL_SEN_GYRO[loopcnt].flgBitmask) != 0 ) {
				callbackResult	|= S_GIM_PRO_INTTBL_SEN_GYRO[loopcnt].intFact;
			}
		}
		cbId.channel = corecnt / coresize;
		// Callback
		if (( S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC.pCallback != NULL ) && ( callbackResult != 0 )){
			S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC.pCallback( &cbId, callbackResult, S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC.userParam );
		}
	}
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_vd_int_handler end\n" ));
#endif
}

/**
SEN block SG VD Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_sg_vd_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SG_VD_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SG_VD_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SEN block Gyro Int handler setting.
@param[in]	callbackCfg : callback configuration
@retval		D_DDIM_OK					: Setting OK
@retval		D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
INT32 interrupt_sen_set_gyro_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SENTOP_GYRO_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
SLVS-EC Common Int handler setting.
@param[in]	inthandler : Interrupt handler address pointer
*/
INT32 interrupt_sen_slvs_set_common_int_handler( InterruptSen*self,T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC.pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SLVS_COMMON_CALLBACK_FUNC.userParam = callbackCfg->user_param;
	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of CMIPI is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : CMIPI Interrupt callback function address
*/
INT32 interrupt_sen_cmipi_set_int_handler( InterruptSen*self,
		E_IM_PRO_CMIPI_CH ch, E_IM_PRO_CMIPI_INT_CATE category, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_CMIPI_CALLBACK_FUNC[ch][category].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_CMIPI_CALLBACK_FUNC[ch][category].userParam = callbackCfg->user_param;

	return D_DDIM_OK;
}

/**
SLVS-EC Int handler setting.
@param[in]	streamType : stream type of SLVS
@param[in]	inthandler : Interrupt handler address pointer
*/
INT32 interrupt_sen_slvs_set_int_handler( InterruptSen*self,
		E_IM_PRO_SLVS_STREAM_TYPE streamType, E_IM_PRO_SLVS_INT_TYPE intType, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
#ifdef CO_PARAM_CHECK
	if (streamType > E_IM_PRO_SLVS_STREAM_TYPE_B){
		Ddim_Assertion(("I:interrupt_sen_slvs_set_int_handler error. 'streamType' value over!! (%d)\n", streamType));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	S_GIM_PRO_SLVS_CALLBACK_FUNC[streamType][intType].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_SLVS_CALLBACK_FUNC[streamType][intType].userParam = callbackCfg->user_param;

	return D_DDIM_OK;
}

/**
SEN block Sensor I/F 0 Int handler.
*/
VOID interrupt_sen_sensor_if_int_handler_0( VOID )
{
	TimproSencoreIntFactor	sencoreIntFactor = {0};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_0 begin\n" ));
#endif
	imProClearSensorIfIntFactor( 0, &sencoreIntFactor );
	imProCallbackSensorIfInt( 0, &sencoreIntFactor );

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_0 end\n" ));
#endif
}

/**
SEN block Sensor I/F 1 Int handler.
*/
VOID interrupt_sen_sensor_if_int_handler_1( VOID )
{
	TimproSencoreIntFactor	sencoreIntFactor = {0};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_1 begin\n" ));
#endif
	imProClearSensorIfIntFactor( 1, &sencoreIntFactor );
	imProCallbackSensorIfInt( 1, &sencoreIntFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_1 end\n" ));
#endif
}

/**
SEN block Sensor I/F 2 Int handler.
*/
VOID interrupt_sen_sensor_if_int_handler_2( VOID )
{
	TimproSencoreIntFactor	sencoreIntFactor = {0};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_2 begin\n" ));
#endif
	imProClearSensorIfIntFactor( 2, &sencoreIntFactor );
	imProCallbackSensorIfInt( 2, &sencoreIntFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_2 end\n" ));
#endif
}

/**
SEN block Sensor I/F 3 Int handler.
*/
VOID interrupt_sen_sensor_if_int_handler_3( VOID )
{
	TimproSencoreIntFactor	sencoreIntFactor = {0};

#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_3 begin\n" ));
#endif
	imProClearSensorIfIntFactor( 3, &sencoreIntFactor );
	imProCallbackSensorIfInt( 3, &sencoreIntFactor );
#ifdef CO_DEBUG_PRINT_IM_PRO
	Ddim_Print(( "interrupt_sen_sensor_if_int_handler_3 end\n" ));
#endif
}

/**
CallBackFunction which Call to the interruption timing of LVDS is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : LVDS Interrupt callback function address
*/
INT32 interrupt_sen_lvds_set_int_handler( InterruptSen*self,
		E_IM_PRO_LVDS_CH ch, E_IM_PRO_LVDS_OUTPUT_MODE outMode, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_LVDS_CALLBACK_FUNC[ch][outMode].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_LVDS_CALLBACK_FUNC[ch][outMode].userParam = callbackCfg->user_param;

	return D_DDIM_OK;
}

/**
CallBackFunction which Call to the interruption timing of DMIPI is registered
@param[in]	ch : Channel No.
@param[in]	inthandler : DMIPI Interrupt callback function address
*/
INT32 interrupt_sen_dmipi_set_int_handler( InterruptSen*self,E_IM_PRO_DMIPI_CH ch, T_IM_PRO_CALLBACK_CFG* callbackCfg )
{
	S_GIM_PRO_DMIPI_CALLBACK_FUNC[ch].pCallback = callbackCfg->inthandler;
	S_GIM_PRO_DMIPI_CALLBACK_FUNC[ch].userParam = callbackCfg->user_param;

	return D_DDIM_OK;
}

InterruptSen *interrupt_sen_new(void)
{
	InterruptSen* self = k_object_new_with_private(INTERRUPT_TYPE_SEN,sizeof(InterruptSenPrivate));
	return self;
}
