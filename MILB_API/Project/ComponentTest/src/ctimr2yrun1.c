/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2yRun1
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2yclassb.h"
#include "ctimr2yclassc.h"
#include "ctimr2yclassd.h"
#include "ctimr2yclasse.h"
#include "ctimr2yclassf.h"
#include "ctimr2yclassg.h"
#include "ctimr2yclassh.h"
#include "ctimr2yclassi.h"
#include "ctimr2y17series.h"
#include "ctimr2y18series.h"
#include "ctimr2y18series1.h"
#include "ctimr2y19series.h"
#include "ctimr2y19series1.h"
#include "ctimr2y110series.h"
#include "ctimr2y111series.h"
#include "ctimr2y112series.h"
#include "ctimr2y113series.h"
#include "ctimr2yrun1.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yRun1, ct_im_r2y_run1)
#define CT_IM_R2Y_RUN1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yRun1Private, CT_TYPE_IM_R2Y_RUN1))


struct _CtImR2yRun1Private
{

};


/*
 * IMPL
 */
static void ct_im_r2y_run1_constructor(CtImR2yRun1 *self)
{
	//CtImR2yRun1Private *priv = CT_IM_R2Y_RUN1_GET_PRIVATE(self);
}

static void ct_im_r2y_run1_destructor(CtImR2yRun1 *self)
{
	//CtImR2yRun1Private *priv = CT_IM_R2Y_RUN1_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
kint32 ct_im_r2y_run_1(CtImR2yRun1 *self, kuchar pipeNo, const kuint32 ctNo3rd)
{
	switch(ctNo3rd) {
		// Test-1-1-1
		case 1:
			return ct_im_r2y_classb_1_1(pipeNo);

		// Test-1-1-2
		case 2:
			return ct_im_r2y_classb_1_2(pipeNo);

		// Test-1-1-3
		case 3:
			return ct_im_r2y_classb_1_3(pipeNo);

		// Test-1-1-4
		case 4:
			return ct_im_r2y_classb_1_4(pipeNo);

		// Test-1-1-5
		case 5:
			return ct_im_r2y_classb_1_5(pipeNo);

		// Test-1-1-6
		case 6:
			return ct_im_r2y_classb_1_6(pipeNo);

		// Test-1-1-7
		case 7:
			return ct_im_r2y_classb_1_7(pipeNo);

		// Test-1-1-8
		case 8:
			return ct_im_r2y_classb_1_8(pipeNo);

		// Test-1-1-9
		case 9:
			return ct_im_r2y_classb_1_9(pipeNo);

		// Test-1-1-10
		case 10:
			return ct_im_r2y_classb_1_10(pipeNo);

		// Test-1-1-11
		case 11:
			return ct_im_r2y_classb_1_11(pipeNo);

		// Test-1-1-12
		case 12:
			return ct_im_r2y_classb_1_12(pipeNo);

		// Test-1-1-13
		case 13:
			return ct_im_r2y_classb_1_13(pipeNo);

		// Test-1-1-14
		case 14:
			return ct_im_r2y_classb_1_14(pipeNo);

		// Test-1-1-15
		case 15:
			return ct_im_r2y_classd_1_15(pipeNo);

		// Test-1-1-16
		case 16:
			return ct_im_r2y_classc_1_16(pipeNo);

		// Test-1-1-17
		case 17:
			return ct_im_r2y_classc_1_17(pipeNo);

		// Test-1-1-18
		case 18:
			return ct_im_r2y_classc_1_18(pipeNo);

		// Test-1-1-19
		case 19:
			return ct_im_r2y_classc_1_19(pipeNo);

		// Test-1-1-20
		case 20:
			return ct_im_r2y_classc_1_20(pipeNo);

		// Test-1-1-21
		case 21:
			return ct_im_r2y_classc_1_21(pipeNo);

		// Test-1-1-22
		case 22:
			return ct_im_r2y_classc_1_22(pipeNo);

		// Test-1-1-23
		case 23:
			return ct_im_r2y_classc_1_23(pipeNo);

		// Test-1-1-24
		case 24:
			return ct_im_r2y_classc_1_24(pipeNo);

		// Test-1-1-25
		case 25:
			return ct_im_r2y_classd_1_25(pipeNo);

		// Test-1-1-26
		case 26:
			return ct_im_r2y_classd_1_26(pipeNo);

		// Test-1-1-27
		case 27:
			return ct_im_r2y_classd_1_27(pipeNo);

		// Test-1-1-28
		case 28:
			return ct_im_r2y_classd_1_28(pipeNo);

		// Test-1-1-29
		case 29:
			return ct_im_r2y_classd_1_29(pipeNo);

		// Test-1-1-30
		case 30:
			return ct_im_r2y_classd_1_30(pipeNo);

		// Test-1-1-31
		case 31:
			return ct_im_r2y_classd_1_31(pipeNo);

		// Test-1-1-32
		case 32:
			return ct_im_r2y_classd_1_32(pipeNo);

		// Test-1-1-33
		case 33:
			return ct_im_r2y_classd_1_33(pipeNo);

		// Test-1-1-34
		case 34:
			return ct_im_r2y_classd_1_34(pipeNo);

		// Test-1-1-35
		case 35:
			return ct_im_r2y_classd_1_35(pipeNo);

		// Test-1-1-36
		case 36:
			return ct_im_r2y_classd_1_36(pipeNo);

		// Test-1-1-37
		case 37:
			return ct_im_r2y_classe_1_37(pipeNo);

		// Test-1-1-38
		case 38:
			return ct_im_r2y_classe_1_38(pipeNo);

		// Test-1-1-39
		case 39:
			return ct_im_r2y_classe_1_39(pipeNo);

		// Test-1-1-40
		case 40:
			return ct_im_r2y_classe_1_40(pipeNo);

		// Test-1-1-41
		case 41:
			return ct_im_r2y_classe_1_41(pipeNo);

		// Test-1-1-42
		case 42:
			return ct_im_r2y_classe_1_42(pipeNo);

		// Test-1-1-43
		case 43:
			return ct_im_r2y_classe_1_43(pipeNo);

		// Test-1-1-44
		case 44:
			return ct_im_r2y_classe_1_44(pipeNo);

		// Test-1-1-45
		case 45:
			return ct_im_r2y_classe_1_45(pipeNo);

		// Test-1-1-46
		case 46:
			return ct_im_r2y_classf_1_46(pipeNo);

		// Test-1-1-47
		case 47:
			return ct_im_r2y_classf_1_47(pipeNo);

		// Test-1-1-48
		case 48:
			return ct_im_r2y_classf_1_48(pipeNo);

		// Test-1-1-49
		case 49:
			return ct_im_r2y_classf_1_49(pipeNo);

		// Test-1-1-50
		case 50:
			return ct_im_r2y_classf_1_50(pipeNo);

		// Test-1-1-51
		case 51:
			return ct_im_r2y_classf_1_51(pipeNo);

		// Test-1-1-52
		case 52:
			return ct_im_r2y_classf_1_52(pipeNo);

		// Test-1-1-53
		case 53:
			return ct_im_r2y_classf_1_53(pipeNo);

		// Test-1-1-54
		case 54:
			return ct_im_r2y_classg_1_54(pipeNo);

		// Test-1-1-55
		case 55:
			return ct_im_r2y_classh_1_55(pipeNo);

		// Test-1-1-56
		case 56:
			return ct_im_r2y_classh_1_56(pipeNo);

		// Test-1-1-57
		case 57:
			return ct_im_r2y_classh_1_57(pipeNo);

		// Test-1-1-58
		case 58:
			return ct_im_r2y_classh_1_58(pipeNo);

		// Test-1-1-59
		case 59:
			return ct_im_r2y_classh_1_59(pipeNo);

		// Test-1-1-60
		case 60:
			return ct_im_r2y_classh_1_60(pipeNo);

		// Test-1-1-61
		case 61:
			return ct_im_r2y_classh_1_61(pipeNo);

		// Test-1-1-62
		case 62:
			return ct_im_r2y_classh_1_62(pipeNo);

		// Test-1-1-63
		case 63:
			return ct_im_r2y_classh_1_63(pipeNo);

		// Test-1-1-64
		case 64:
			return ct_im_r2y_classh_1_64(pipeNo);

		// Test-1-1-65
		case 65:
			return ct_im_r2y_classh_1_65(pipeNo);

		// Test-1-1-66
		case 66:
			return ct_im_r2y_classh_1_66(pipeNo);

		// Test-1-1-67
		case 67:
			return ct_im_r2y_classh_1_67(pipeNo);

		// Test-1-1-68
		case 68:
			return ct_im_r2y_classh_1_68(pipeNo);

		// Test-1-1-69
		case 69:
			return ct_im_r2y_classh_1_69(pipeNo);

		// Test-1-1-70
		case 70:
			return ct_im_r2y_classi_1_70(pipeNo);

		// Test-1-1-71
		case 71:
			return ct_im_r2y_classi_1_71(pipeNo);

		// Test-1-1-72
		case 72:
			return ct_im_r2y_classi_1_72(pipeNo);

		// Test-1-1-73
		case 73:
			return ct_im_r2y_classi_1_73(pipeNo);

		// Test-1-1-74
		case 74:
			return ct_im_r2y_17series_4(NULL, pipeNo);

		// Test-1-1-75
		case 75:
			return ct_im_r2y_17series_5(NULL, pipeNo);

		// Test-1-1-76
		case 76:
			return ct_im_r2y_17series_6(NULL, pipeNo);

		// Test-1-1-77
		case 77:
			return ct_im_r2y_17series_7(NULL, pipeNo);

		// Test-1-1-78
		case 78:
			return ct_im_r2y_17series_8(NULL, pipeNo);

		// Test-1-1-79
		case 79:
			return ct_im_r2y_17series_9(NULL, pipeNo);

		// Test-1-1-80
		case 80:
			return ct_im_r2y_18series_0(NULL, pipeNo);

		// Test-1-1-81
		case 81:
			return ct_im_r2y_18series_1(NULL, pipeNo);

		// Test-1-1-82
		case 82:
			return ct_im_r2y_18series_2(NULL, pipeNo);

		// Test-1-1-83
		case 83:
			return ct_im_r2y_18series_3(NULL, pipeNo);

		// Test-1-1-84
		case 84:
			return ct_im_r2y_18series_4(NULL, pipeNo);

		// Test-1-1-85
		case 85:
			return ct_im_r2y_18series_5(NULL, pipeNo);

		// Test-1-1-86
		case 86:
			return ct_im_r2y_18series1_6(NULL, pipeNo);

		// Test-1-1-87
		case 87:
			return ct_im_r2y_18series1_7(NULL, pipeNo);

		// Test-1-1-88
		case 88:
			return ct_im_r2y_18series1_8(NULL, pipeNo);

		// Test-1-1-89
		case 89:
			return ct_im_r2y_18series1_9(NULL, pipeNo);

		// Test-1-1-90
		case 90:
			return ct_im_r2y_19series_0(NULL, pipeNo);

		// Test-1-1-91
		case 91:
			return ct_im_r2y_19series_1(NULL, pipeNo);

		// Test-1-1-92
		case 92:
			return ct_im_r2y_19series_2(NULL, pipeNo);

		// Test-1-1-93
		case 93:
			return ct_im_r2y_19series_3(NULL, pipeNo);

		// Test-1-1-94
		case 94:
			return ct_im_r2y_19series_4(NULL, pipeNo);

		// Test-1-1-95
		case 95:
			return ct_im_r2y_19series1_5(NULL, pipeNo);

		// Test-1-1-96
		case 96:
			return ct_im_r2y_19series1_6(NULL, pipeNo);

		// Test-1-1-97
		case 97:
			return ct_im_r2y_19series1_7(NULL, pipeNo);

		// Test-1-1-98
		case 98:
			return ct_im_r2y_19series1_8(NULL, pipeNo);

		// Test-1-1-99
		case 99:
			return ct_im_r2y_19series1_9(NULL, pipeNo);

		// Test-1-1-100
		case 100:
			return ct_im_r2y_110series_0(NULL, pipeNo);

		// Test-1-1-101
		case 101:
			return ct_im_r2y_110series_1(NULL, pipeNo);

		// Test-1-1-102
		case 102:
			return ct_im_r2y_110series_2(NULL, pipeNo);

		// Test-1-1-103
		case 103:
			return ct_im_r2y_110series_3(NULL, pipeNo);

		// Test-1-1-104
		case 104:
			return ct_im_r2y_110series_4(NULL, pipeNo);

		// Test-1-1-105
		case 105:
			return ct_im_r2y_110series_5(NULL, pipeNo);

		// Test-1-1-106
		case 106:
			return ct_im_r2y_110series_6(NULL, pipeNo);

		// Test-1-1-107
		case 107:
			return ct_im_r2y_110series_7(NULL, pipeNo);

		// Test-1-1-108
		case 108:
			return ct_im_r2y_110series_8(NULL, pipeNo);

		// Test-1-1-109
		case 109:
			return ct_im_r2y_110series_9(NULL, pipeNo);

		// Test-1-1-110
		case 110:
			return ct_im_r2y_111series_0(NULL, pipeNo);

		// Test-1-1-111
		case 111:
			return ct_im_r2y_111series_1(NULL, pipeNo);

		// Test-1-1-112
		case 112:
			return ct_im_r2y_111series_2(NULL, pipeNo);

		// Test-1-1-113
		case 113:
			return ct_im_r2y_111series_3(NULL, pipeNo);

		// Test-1-1-114
		case 114:
			return ct_im_r2y_111series_4(NULL, pipeNo);

		// Test-1-1-115
		case 115:
			return ct_im_r2y_111series_5(NULL, pipeNo);

		// Test-1-1-116
		case 116:
			return ct_im_r2y_111series_6(NULL, pipeNo);

		// Test-1-1-117
		case 117:
			return ct_im_r2y_111series_7(NULL, pipeNo);

		// Test-1-1-118
		case 118:
			return ct_im_r2y_111series_8(NULL, pipeNo);

		// Test-1-1-119
		case 119:
			return ct_im_r2y_111series_9(NULL, pipeNo);

		// Test-1-1-120
		case 120:
			return ct_im_r2y_112series_0(NULL, pipeNo);

		// Test-1-1-121
		case 121:
			return ct_im_r2y_112series_1(NULL, pipeNo);

		// Test-1-1-122
		case 122:
			return ct_im_r2y_112series_2(NULL, pipeNo);

		// Test-1-1-123
		case 123:
			return ct_im_r2y_112series_3(NULL, pipeNo);

		// Test-1-1-124
		case 124:
			return ct_im_r2y_112series_4(NULL, pipeNo);

		// Test-1-1-125
		case 125:
			return ct_im_r2y_112series_5(NULL, pipeNo);

		// Test-1-1-126
		case 126:
			return ct_im_r2y_112series_6(NULL, pipeNo);

		// Test-1-1-127
		case 127:
			return ct_im_r2y_112series_7(NULL, pipeNo);

		// Test-1-1-128
		case 128:
			return ct_im_r2y_112series_8(NULL, pipeNo);

		// Test-1-1-129
		case 129:
			return ct_im_r2y_112series_9(NULL, pipeNo);

		// Test-1-1-130
		case 130:
			return ct_im_r2y_113series_0(NULL, pipeNo);

		// Test-1-1-131
		case 131:
			return ct_im_r2y_113series_1(NULL, pipeNo);

		// Test-1-1-132
		case 132:
			return ct_im_r2y_113series_2(NULL, pipeNo);

		// Test-1-1-133
		case 133:
			return ct_im_r2y_113series_3(NULL, pipeNo);

		// Test-1-1-134
		case 134:
			return ct_im_r2y_113series_4(NULL, pipeNo);

		// Test-1-1-135
		case 135:
			return ct_im_r2y_113series_5(NULL, pipeNo);

		// Test-1-1-136
		case 136:
			return ct_im_r2y_113series_6(NULL, pipeNo);

		// Test-1-1-137
		case 137:
			return ct_im_r2y_113series_7(NULL, pipeNo);

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

CtImR2yRun1* ct_im_r2y_run1_new(void)
{
	CtImR2yRun1* self = k_object_new_with_private(CT_TYPE_IM_R2Y_RUN1, sizeof(CtImR2yRun1Private));

	return self;
}
