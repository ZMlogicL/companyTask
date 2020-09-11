/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y110series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y110series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y110series, ct_im_r2y_110series)
#define CT_IM_R2Y_110SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y110seriesPrivate, CT_TYPE_IM_R2Y_110SERIES))


struct _CtImR2y110seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_110series_constructor(CtImR2y110series *self)
{
	//CtImR2y110seriesPrivate *priv = CT_IM_R2Y_110SERIES_GET_PRIVATE(self);
}

static void ct_im_r2y_110series_destructor(CtImR2y110series *self)
{
	//CtImR2y110seriesPrivate *priv = CT_IM_R2Y_110SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_0: "
kint32 ct_im_r2y_110series_0(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y1100
	{
		kushort srcTbl[D_IM_R2Y_TABLE_MAX_MAPSCL];
	};
	struct TCtImR2y1100 	tblBody;
	struct TCtImR2y1100		*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y1100
	{
		kushort srcTbl[D_IM_R2Y_TABLE_MAX_MAPSCL];
	}* tbl = (struct TCtImR2y1100*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y1100
	{
		kulong	word;
		struct
		{
			kulong	egmpscl0	:10;
			kulong				:6;
			kulong	egmpscl1	:10;
			kulong				:6;
		}bit;
	} wordConv =
		{
			.bit.egmpscl0 = 0,
			.bit.egmpscl1 = 0,
		};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
		// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_MAPSCL; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x3FF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_MAPSCL; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_MAPSCL; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x3FF - loopcnt2;
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = Im_R2Y_Set_MapScl_Table(pipeNo, tbl->srcTbl, 0, D_IM_R2Y_TABLE_MAX_MAPSCL);
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
		Im_R2Y_On_Hclk(pipeNo);
		Im_R2Y_Set_MapSclTblAccessEnable(pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_MAPSCL; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.egmpscl.hword[loopcnt2 / 17][loopcnt2 % 17];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 >= D_IM_R2Y_TABLE_MAX_MAPSCL) {
						break;
					}
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmpscl0;
					} else {
						regVal = wordConv.bit.egmpscl1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < D_IM_R2Y_TABLE_MAX_MAPSCL; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.egmpscl.hword[loopcnt2 / 17][loopcnt2 % 17];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 >= D_IM_R2Y_TABLE_MAX_MAPSCL) {
						break;
					}
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmpscl0;
					} else {
						regVal = wordConv.bit.egmpscl1;
					}
					//DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3, regVal,
					//tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		Im_R2Y_Set_MapSclTblAccessEnable(pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		Im_R2Y_Off_Hclk(pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_1: "
kint32 ct_im_r2y_110series_1(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEe0Addr	*addr;
	kulong	*ptAddr;
	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EE0_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEe0Addr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_2: "
kint32 ct_im_r2y_110series_2(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEe1Addr	*addr;
	kulong	*ptAddr;
	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EE1_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEe1Addr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_3: "
kint32 ct_im_r2y_110series_3(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaDekneeTblAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_Deknee_Table(pipeNo, E_R2Y_DKN_RGBTBL_R, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaDekneeTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address r[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = Im_R2Y_Get_RdmaAddr_Deknee_Table(pipeNo, E_R2Y_DKN_RGBTBL_G, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaDekneeTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address g[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = Im_R2Y_Get_RdmaAddr_Deknee_Table(pipeNo, E_R2Y_DKN_RGBTBL_B, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaDekneeTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address b[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_4: "
kint32 ct_im_r2y_110series_4(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaOfstAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_Offset_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaOfstAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_5: "
kint32 ct_im_r2y_110series_5(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaWbClipAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_WB_Clip_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaWbClipAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_6: "
kint32 ct_im_r2y_110series_6(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCc0Addr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_CC0_Matrix_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCc0Addr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_7: "
kint32 ct_im_r2y_110series_7(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCc0CoefAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_CC0_Matrix_Coefficient_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCc0CoefAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_8: "
kint32 ct_im_r2y_110series_8(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaMcycAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_Multi_Axis_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaMcycAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y110series_FUNC_NAME
#define 	CtImR2y110series_FUNC_NAME "ct_im_r2y_110series_9: "
kint32 ct_im_r2y_110series_9(CtImR2y110series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaBtcTcofAddr	 *addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y110series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_BeforeTone_Offset_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaBtcTcofAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y110series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

CtImR2y110series* ct_im_r2y_110series_new(void)
{
	CtImR2y110series* self = k_object_new_with_private(CT_TYPE_IM_R2Y_110SERIES, sizeof(CtImR2y110seriesPrivate));

	return self;
}
