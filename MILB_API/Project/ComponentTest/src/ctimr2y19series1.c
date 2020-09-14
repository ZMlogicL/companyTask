/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 梁正明
*@brief : CtImR2y19series1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "imr2yedge.h"
#include "ctimr2y19series1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y19series1, ct_im_r2y_19series1)
#define CT_IM_R2Y_19SERIES1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y19series1Private, CT_TYPE_IM_R2Y_19SERIES1))


struct _CtImR2y19series1Private
{

};


/*
 * IMPL
 */
static void ct_im_r2y_19series1_constructor(CtImR2y19series1 *self)
{
	CtImR2y19series1Private *priv = CT_IM_R2Y_19SERIES1_GET_PRIVATE(self);
	self->imR2yClk = im_r2y_clk_new();
	self->imR2yEdge = im_r2y_edge_new();
	self->imR2ySet = im_r2y_set_new();
}

static void ct_im_r2y_19series1_destructor(CtImR2y19series1 *self)
{
	CtImR2y19series1Private *priv = CT_IM_R2Y_19SERIES1_GET_PRIVATE(self);
	if(self->imR2ySet){
			k_object_unref(self->imR2ySet);
			self->imR2ySet=NULL;
		}

	if(self->imR2yEdge){
		k_object_unref(self->imR2yEdge);
		self->imR2yEdge=NULL;
	}

	if(self->imR2yClk){
			k_object_unref(self->imR2yClk);
			self->imR2yClk=NULL;
		}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y19series1_FUNC_NAME
#define 	CtImR2y19series1_FUNC_NAME "ct_im_r2y_19series1_5: "
kint32 ct_im_r2y_19series1_5(CtImR2y19series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y195
	{
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_HI];
	};
	struct TCtImR2y195 	tblBody;
	struct TCtImR2y195	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y195
	{
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_HI];
	}* tbl = (struct TCtImR2y195*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y195
	{
		kulong	word;
		struct
		{
			kulong	eghwton0 :9;
			kulong			 :7;
			kulong	eghwton1 :9;
			kulong			 :7;
		}bit;
	} wordConv =
		{
			.bit.eghwton0 = 0,
			.bit.eghwton1 = 0,
		};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_HI; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x1FF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_HI; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_HI; loopcnt2++) {
					if(loopcnt2 >= 128) {
						tbl->srcTbl[loopcnt2] = 0x1FF - (loopcnt2 - 128);
					} else {
						tbl->srcTbl[loopcnt2] = 0x1FF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_high_edge_step_table(self->imR2ySet, pipeNo, tbl->srcTbl, 0, ImR2y_TABLE_MAX_EDGE_TC_HI);
		DriverCommon_DDIM_PRINT((CtImR2y19series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_HI; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.eghwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eghwton0;
					} else {
						regVal = wordConv.bit.eghwton1;
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
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_HI; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.eghwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eghwton0;
					} else {
						regVal = wordConv.bit.eghwton1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3, regVal,
					//tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_high_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y19series1_FUNC_NAME
#define 	CtImR2y19series1_FUNC_NAME "ct_im_r2y_19series1_6: "
kint32 ct_im_r2y_19series1_6(CtImR2y19series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y196
	{
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM];
	};
	struct TCtImR2y196 	tblBody;
	struct TCtImR2y196	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y196
	{
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM];
	}* tbl = (struct TCtImR2y196*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y196
	{
		kulong	word;
		struct {
			kulong	egmwscl0	:8;
			kulong	egmwscl1	:8;
			kulong	egmwscl2	:8;
			kulong	egmwscl3	:8;
		}bit;
	} wordConv = {
		.bit.egmwscl0 = 0,
		.bit.egmwscl1 = 0,
		.bit.egmwscl2 = 0,
		.bit.egmwscl3 = 0,
	};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0xFF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM; loopcnt2++) {
					if(loopcnt2 >= 256) {
						tbl->srcTbl[loopcnt2] = 0xFF - (loopcnt2 - 256);
					} else {
						tbl->srcTbl[loopcnt2] = 0xFF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_medium_edge_scale_table(self->imR2ySet, pipeNo, tbl->srcTbl, 0, ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM);
		DriverCommon_DDIM_PRINT((CtImR2y19series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_medium_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.egmwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.egmwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.egmwscl2;
					} else {
						regVal = wordConv.bit.egmwscl3;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n",
					// loopcnt3, regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_MEDIUM; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.egmwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.egmwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.egmwscl2;
					} else {
						regVal = wordConv.bit.egmwscl3;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n",
					//loopcnt3, regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_medium_edge_scl_tbl_access_enable(pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y19series1_FUNC_NAME
#define 	CtImR2y19series1_FUNC_NAME "ct_im_r2y_19series1_7: "
kint32 ct_im_r2y_19series1_7(CtImR2y19series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y197 {
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_MEDIUM];
	};
	struct TCtImR2y197 	tblBody;
	struct TCtImR2y197	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y197 {
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_MEDIUM];
	}* tbl = (struct TCtImR2y197*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y197 {
		kulong	word;
		struct {
		kulong	egmwton0 :9;
		kulong			 :7;
		kulong	egmwton1 :9;
		kulong			 :7;
		}bit;
	} wordConv = {
		.bit.egmwton0 = 0,
		.bit.egmwton1 = 0,
	};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
		// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_MEDIUM; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x1FF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_MEDIUM; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_MEDIUM; loopcnt2++) {
					if(loopcnt2 >= 128) {
						tbl->srcTbl[loopcnt2] = 0x1FF - (loopcnt2 - 128);
					} else {
						tbl->srcTbl[loopcnt2] = 0x1FF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_medium_edge_step_table(self->imR2ySet, pipeNo, tbl->srcTbl,
				0, ImR2y_TABLE_MAX_EDGE_TC_MEDIUM);
		DriverCommon_DDIM_PRINT((CtImR2y19series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_MEDIUM; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.egmwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmwton0;
					} else {
						regVal = wordConv.bit.egmwton1;
					}
					//DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_MEDIUM; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.egmwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.egmwton0;
					} else {
						regVal = wordConv.bit.egmwton1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_medium_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y19series1_FUNC_NAME
#define 	CtImR2y19series1_FUNC_NAME "ct_im_r2y_19series1_8: "
kint32 ct_im_r2y_19series1_8(CtImR2y19series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y198 {
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_LO];
	};
	struct TCtImR2y198 	tblBody;
	struct TCtImR2y198	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y198 {
		kuchar srcTbl[ImR2y_TABLE_MAX_EDGE_SCALE_LO];
	}* tbl = (struct TCtImR2y198*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y198 {
		kulong	word;
		struct {
		kulong	eglwscl0	:8;
		kulong	eglwscl1	:8;
		kulong	eglwscl2	:8;
		kulong	eglwscl3	:8;
		}bit;
	} wordConv = {
		.bit.eglwscl0 = 0,
		.bit.eglwscl1 = 0,
		.bit.eglwscl2 = 0,
		.bit.eglwscl3 = 0,
	};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_LO; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0xFF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_LO; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_LO; loopcnt2++) {
					if(loopcnt2 >= 256) {
						tbl->srcTbl[loopcnt2] = 0xFF - (loopcnt2 - 256);
					} else {
						tbl->srcTbl[loopcnt2] = 0xFF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_low_edge_scale_table(self->imR2ySet, pipeNo, tbl->srcTbl,
				0, ImR2y_TABLE_MAX_EDGE_SCALE_LO);
		DriverCommon_DDIM_PRINT((CtImR2y19series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_LO; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.eglwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eglwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.eglwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.eglwscl2;
					} else {
						regVal = wordConv.bit.eglwscl3;
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
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_SCALE_LO; loopcnt2 += 4) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.eglwscl.byte[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 4); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eglwscl0;
					} else if(loopcnt3 == (loopcnt2 +1)) {
						regVal = wordConv.bit.eglwscl1;
					} else if(loopcnt3 == (loopcnt2 +2)) {
						regVal = wordConv.bit.eglwscl2;
					} else {
						regVal = wordConv.bit.eglwscl3;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_low_edge_scl_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

#undef 	CtImR2y19series1_FUNC_NAME
#define 	CtImR2y19series1_FUNC_NAME "ct_im_r2y_19series1_9: "
kint32 ct_im_r2y_19series1_9(CtImR2y19series1 *self, kuchar pipeNo)
{
#ifdef CO_DEBUG_ON_PC
	struct TCtImR2y199
	{
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_LO];
	};
	struct TCtImR2y199 	tblBody;
	struct TCtImR2y199	*tbl = &tblBody;
#else //!CO_DEBUG_ON_PC
	struct TCtImR2y199
	{
		kushort srcTbl[ImR2y_TABLE_MAX_EDGE_TC_LO];
	}* tbl = (struct TCtImR2y199*)D_IM_R2Y_IMG_MEM_IN_ADDR_TOP;
#endif //!CO_DEBUG_ON_PC
	kuint32 loopcnt;
	kuint32 loopcnt2;
	kuint32 loopcnt3;
	union UCtImR2y199
	{
		kulong	word;
		struct
		{
			kulong	eglwton0 :9;
			kulong			 :7;
			kulong	eglwton1 :9;
			kulong			 :7;
		}bit;
	} wordConv =
	{
		.bit.eglwton0 = 0,
		.bit.eglwton1 = 0,
	};
	kulong regVal;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	const char errmsg[] = "%u[%u] unmatch\n";

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y19series1_FUNC_NAME));
	for(loopcnt = 0; loopcnt < 3; loopcnt++) {
		DriverCommon_DDIM_PRINT(("** %u\n", loopcnt));
		switch(loopcnt) {
			// max
			default:
				//	case 0:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_LO; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0x1FF;
				}
				break;
			// min
			case 1:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_LO; loopcnt2++) {
					tbl->srcTbl[loopcnt2] = 0;
				}
				break;
			// indvisual
			case 2:
				for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_LO; loopcnt2++) {
					if(loopcnt2 >= 128)
					{
						tbl->srcTbl[loopcnt2] = 0x1FF - (loopcnt2 - 128);
					} else {
						tbl->srcTbl[loopcnt2] = 0x1FF - loopcnt2;
					}
				}
				break;
		}
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_low_edge_step_table(self->imR2ySet, pipeNo, tbl->srcTbl, 0, ImR2y_TABLE_MAX_EDGE_TC_LO);
		DriverCommon_DDIM_PRINT((CtImR2y19series1_FUNC_NAME "0x%x\n", ercd));
		im_r2y_clk_on_hclk(self->imR2yClk, pipeNo);
		im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_ON, ImR2y_WAIT_ON);
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_1(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_LO; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP1.eglwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eglwton0;
					} else {
						regVal = wordConv.bit.eglwton1;
					}
					//DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		if(CtImR2yTool_CHECK_TARGET_PIPE_NO_2(pipeNo)) {
			for(loopcnt2 = 0; loopcnt2 < ImR2y_TABLE_MAX_EDGE_TC_LO; loopcnt2 += 2) {
				// Force word read access
				wordConv.word = *(kulong*)&ioR2yTblP2.eglwton.hword[loopcnt2];
				for(loopcnt3 = loopcnt2; loopcnt3 < (loopcnt2 + 2); loopcnt3++) {
					if(loopcnt3 == loopcnt2) {
						regVal = wordConv.bit.eglwton0;
					} else {
						regVal = wordConv.bit.eglwton1;
					}
					//	DriverCommon_DDIM_PRINT(("[%u], 0x%lx, 0x%x, 0x%lx\n", loopcnt3,
					//regVal, tbl->srcTbl[loopcnt3], wordConv.word));
					if(regVal != tbl->srcTbl[loopcnt3]) {
						DriverCommon_DDIM_PRINT((errmsg, 0, loopcnt3));
					}
				}
			}
		}
		im_r2y_edge_set_low_edge_step_tbl_access_enable(self->imR2yEdge, pipeNo, ImR2y_ENABLE_OFF, ImR2y_WAIT_OFF);
		im_r2y_clk_off_hclk(self->imR2yClk, pipeNo);
#endif
	}

	return D_DDIM_OK;
}

CtImR2y19series1* ct_im_r2y_19series1_new(void)
{
	CtImR2y19series1* self = k_object_new_with_private(CT_TYPE_IM_R2Y_19SERIES1, sizeof(CtImR2y19series1Private));

	return self;
}
