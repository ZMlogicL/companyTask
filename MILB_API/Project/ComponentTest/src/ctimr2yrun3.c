/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2yRun3
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y3series.h"
#include "ctimr2y31series.h"
#include "ctimr2y32series.h"
#include "ctimr2y33series.h"
#include "ctimr2y33series1.h"
#include "ctimr2y34series.h"
#include "ctimr2y35series.h"
#include "ctimr2y36series.h"
#include "ctimr2y36series1.h"
#include "ctimr2y37series.h"
#include "ctimr2yrun1.h"
#include "ctimr2y2series.h"
#include "ctimr2yrun3.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yRun3, ct_im_r2y_run3)
#define CT_IM_R2Y_RUN3_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yRun3Private, CT_TYPE_IM_R2Y_RUN3))


struct _CtImR2yRun3Private
{

};


/*
 * IMPL
 */
static void ct_im_r2y_run3_constructor(CtImR2yRun3 *self)
{
	//CtImR2yRun3Private *priv = CT_IM_R2Y_RUN3_GET_PRIVATE(self);
}

static void ct_im_r2y_run3_destructor(CtImR2yRun3 *self)
{
	//CtImR2yRun3Private *priv = CT_IM_R2Y_RUN3_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
kint32 ct_im_r2y_run3_3(CtImR2yRun3 *self, kuchar pipeNo, const kuint32 ctNo3rd)
{
	switch(ctNo3rd) {
		// Test-1-2-1
		case 1:
			return ct_im_r2y_3series_1(NULL, pipeNo);

		case 2:
			return ct_im_r2y_3series_2(NULL, pipeNo);

		case 3:
			return ct_im_r2y_3series_3(NULL, pipeNo);

		case 4:
			return ct_im_r2y_3series_4(NULL, pipeNo);

		case 5:
			return ct_im_r2y_3series_5(NULL, pipeNo);

		case 6:
			return ct_im_r2y_3series_6(NULL, pipeNo);

		case 12:
			return ct_im_r2y_31series_2(NULL, pipeNo);

		case 13:
			return ct_im_r2y_31series_3(NULL, pipeNo);

		case 14:
			return ct_im_r2y_31series_4(NULL, pipeNo);

		case 15:
			return ct_im_r2y_31series_5(NULL, pipeNo);

		case 16:
			return ct_im_r2y_31series_6(NULL, pipeNo);

		case 17:
			return ct_im_r2y_31series_7(NULL, pipeNo);

		case 18:
			return ct_im_r2y_31series_8(NULL, pipeNo);

		case 19:
			return ct_im_r2y_31series_9(NULL, pipeNo);

		case 20:
			return ct_im_r2y_32series_0(NULL, pipeNo);

		case 21:
			return ct_im_r2y_32series_1(NULL, pipeNo);

		case 22:
			return ct_im_r2y_32series_2(NULL, pipeNo);

		case 23:
			return ct_im_r2y_32series_3(NULL, pipeNo);

		case 24:
			return ct_im_r2y_32series_4(NULL, pipeNo);

		case 25:
			return ct_im_r2y_32series_5(NULL, pipeNo);

		case 26:
			return ct_im_r2y_32series_6(NULL, pipeNo);

		case 27:
			return ct_im_r2y_32series_7(NULL, pipeNo);

		case 28:
			return ct_im_r2y_32series_8(NULL, pipeNo);

		case 29:
			return ct_im_r2y_32series_9(NULL, pipeNo);

		case 30:
			return ct_im_r2y_33series_0(NULL, pipeNo);

		case 31:
			return ct_im_r2y_33series_1(NULL, pipeNo);

		case 32:
			return ct_im_r2y_33series_2(NULL, pipeNo);

		case 33:
			return ct_im_r2y_33series_3(NULL, pipeNo);

		case 34:
			return ct_im_r2y_33series_4(NULL, pipeNo);

		case 35:
			return ct_im_r2y_33series1_5(NULL, pipeNo);

		case 36:
			return ct_im_r2y_33series1_6(NULL, pipeNo);

		case 37:
			return ct_im_r2y_33series1_7(NULL, pipeNo);

		case 38:
			return ct_im_r2y_33series1_8(NULL, pipeNo);

		case 39:
			return ct_im_r2y_33series1_9(NULL, pipeNo);

		case 40:
			return ct_im_r2y_34series_0(NULL, pipeNo);

		case 41:
			return ct_im_r2y_34series_1(NULL, pipeNo);

		case 42:
			return ct_im_r2y_34series_2(NULL, pipeNo);

		case 43:
			return ct_im_r2y_34series_3(NULL, pipeNo);

		case 44:
			return ct_im_r2y_34series_4(NULL, pipeNo);

		case 45:
			return ct_im_r2y_34series_5(NULL, pipeNo);

		case 46:
			return ct_im_r2y_34series_6(NULL, pipeNo);

		case 47:
			return ct_im_r2y_34series_7(NULL, pipeNo);

		case 48:
			return ct_im_r2y_34series_8(NULL, pipeNo);

		case 49:
			return ct_im_r2y_34series_9(NULL, pipeNo);

		case 50:
			return ct_im_r2y_35series_0(NULL, pipeNo);

		case 51:
			return ct_im_r2y_35series_1(NULL, pipeNo);

		case 52:
			return ct_im_r2y_35series_2(NULL, pipeNo);

		case 53:
			return ct_im_r2y_35series_3(NULL, pipeNo);

		case 54:
			return ct_im_r2y_35series_4(NULL, pipeNo);

		case 55:
			return ct_im_r2y_35series_5(NULL, pipeNo);

		case 56:
			return ct_im_r2y_35series_6(NULL, pipeNo);

		case 57:
			return ct_im_r2y_35series_7(NULL, pipeNo);

		case 58:
			return ct_im_r2y_35series_8(NULL, pipeNo);

		case 59:
			return ct_im_r2y_35series_9(NULL, pipeNo);

		case 60:
			return ct_im_r2y_36series_0(NULL, pipeNo);

		case 61:
			return ct_im_r2y_36series_1(NULL, pipeNo);

		case 62:
			return ct_im_r2y_36series_2(NULL, pipeNo);

		case 63:
			return ct_im_r2y_36series_3(NULL, pipeNo);

		case 64:
			return ct_im_r2y_36series_4(NULL, pipeNo);

		case 65:
			return ct_im_r2y_36series_5(NULL, pipeNo);

		case 66:
			return ct_im_r2y_36series1_6(NULL, pipeNo);

		case 67:
			return ct_im_r2y_36series1_7(NULL, pipeNo);

		case 68:
			return ct_im_r2y_36series1_8(NULL, pipeNo);

		case 69:
			return ct_im_r2y_36series1_9(NULL, pipeNo);

		case 70:
			return ct_im_r2y_37series_0(NULL, pipeNo);

		case 71:
			return ct_im_r2y_37series_1(NULL, pipeNo);

		case 72:
			return ct_im_r2y_37series_2(NULL, pipeNo);

		case 73:
			return ct_im_r2y_37series_3(NULL, pipeNo);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

VOID ct_im_r2y_run3_run(CtImR2yRun3 *self, const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd)
{
#ifdef CO_MSG_PRINT_ON
	kint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static BOOL isInit = 0;
	kuchar loopCnt;

	Ddim_Print(("ct_im_r2y_run3_run(NULL, %u, %u, %u) Begin\n", ctIdx1st, ctIdx2nd, ctIdx3rd));
	gctImR2yInAddrRgb8bit.rgb.addrR  = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_R_ADDR_TOP;
	gctImR2yInAddrRgb8bit.rgb.addrG  = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_G_ADDR_TOP;
	gctImR2yInAddrRgb8bit.rgb.addrB  = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_B_ADDR_TOP;
	gctImR2yInAddrRgb12bit.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_P12_R_ADDR_TOP;
	gctImR2yInAddrRgb12bit.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_P12_G_ADDR_TOP;
	gctImR2yInAddrRgb12bit.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_P12_B_ADDR_TOP;
	gctImR2yInAddrRgb16bit.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP;
	gctImR2yInAddrRgb16bit.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_G_ADDR_TOP;
	gctImR2yInAddrRgb16bit.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_B_ADDR_TOP;
	gctImR2yOutAddrYcc422.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP;
	gctImR2yOutAddrYcc422.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP;
	gctImR2yOutAddrYcc422.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP;
	gct_im_r2y_out_addr_ycc444.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC444_Y_ADDR_TOP;
	gct_im_r2y_out_addr_ycc444.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC444_CB_ADDR_TOP;
	gct_im_r2y_out_addr_ycc444.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC444_CR_ADDR_TOP;
	gctImR2yOutAddrYcc420.outputAddr[ImR2y_YYW_BANK_0].ycc.addrY
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC420_Y_ADDR_TOP;
	gctImR2yOutAddrYcc420.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCb
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC420_CB_ADDR_TOP;
	gctImR2yOutAddrYcc420.outputAddr[ImR2y_YYW_BANK_0].ycc.addrCr
			= (VOID*)D_IM_R2Y_IMG_MEM_OUT_YCC420_CR_P_ADDR_TOP;

	if(isInit == 0) {
#ifdef CO_DEBUG_ON_PC
		memset((VOID*)&IO_R2Y_P1, '\0', sizeof(IO_R2Y_P1));
		memset((VOID*)&IO_R2Y_TBL_P1, '\0', sizeof(IO_R2Y_TBL_P1));
		memset((VOID*)&IO_R2Y_P2, '\0', sizeof(IO_R2Y_P2));
		memset((VOID*)&IO_R2Y_TBL_P2, '\0', sizeof(IO_R2Y_TBL_P2));
#endif // CO_DEBUG_ON_PC
		if(!((ctIdx1st == 1) && (ctIdx2nd == 1))) {
			Ddim_Print(("Im_R2Y_Init() Begin\n"));
			Im_R2Y_Init(D_IM_R2Y_PIPE12);
			Ddim_Print(("Im_R2Y_Init() End\n"));
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#ifdef CO_DEBUG_ON_PC
			IO_CHIPTOP.CLKSTOP11.bit.R2Y1CK = 0;
			IO_CHIPTOP.CLKSTOP11.bit.R2Y1AP = 0;
			IO_CHIPTOP.CLKSTOP11.bit.R2Y1AH = 0;
			IO_CHIPTOP.CLKSTOP11.bit.R2Y1AX = 0;
			IO_CHIPTOP.CLKSTOP13.bit.R2Y2CK = 0;
			IO_CHIPTOP.CLKSTOP13.bit.R2Y2AP = 0;
			IO_CHIPTOP.CLKSTOP13.bit.R2Y2AH = 0;
			IO_CHIPTOP.CLKSTOP13.bit.R2Y2AX = 0;
#endif // CO_DEBUG_ON_PC
#endif
			isInit = 1;
		}
	}

	if(ctIdx1st != 3) {
#ifdef CO_DEBUG_ON_PC
		for(loopCnt = D_IM_R2Y_PIPE1; loopCnt <= D_IM_R2Y_PIPE2; loopCnt++) {
#else // CO_DEBUG_ON_PC
		for(loopCnt = D_IM_R2Y_PIPE1; loopCnt <= D_IM_R2Y_PIPE12; loopCnt++) {
#endif // CO_DEBUG_ON_PC
			switch(ctIdx1st) {
				case 1:
					D_IM_R2Y_RESULT(ct_im_r2y_run_1(NULL, loopCnt, ctIdx2nd));
					break;
				case 2:
					D_IM_R2Y_RESULT(ct_im_r2y_2series_run_2(NULL, loopCnt, ctIdx2nd));
					break;
				default:
					Ddim_Print(("Error: Unknown command.\n"));
					break;
			}
		}
#ifdef CO_MSG_PRINT_ON
		Ddim_Print(("result = 0x%x\n", result));
#endif
		Ddim_Print(("ct_im_r2y_run3_run(NULL, %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, loopCnt));
	} else {
		D_IM_R2Y_RESULT(ct_im_r2y_run3_3(NULL, ctIdx3rd, ctIdx2nd));
#ifdef CO_MSG_PRINT_ON
		Ddim_Print(("result = 0x%x\n", result));
#endif
		Ddim_Print(("ct_im_r2y_run3_run(NULL, %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, ctIdx3rd));
	}

	return;
}

// for Debug console interface
VOID ct_im_r2y_run3_main(CtImR2yRun3 *self, kint32 argc, CHAR** argv)
{
	if(argc < 3) {
		Ddim_Print(("Ct_Im_R2Y_Main: parameter error.\n"));
		return;
	}
	ct_im_r2y_run3_run(NULL, (kuint32)atoi((const char*)argv[1]),
			(kuint32)atoi((const char*)argv[2]),
			(kuint32)atoi((const char*)argv[3]));
}

CtImR2yRun3* ct_im_r2y_run3_new(void)
{
	CtImR2yRun3* self = k_object_new_with_private(CT_TYPE_IM_R2Y_RUN3, sizeof(CtImR2yRun3Private));

	return self;
}
