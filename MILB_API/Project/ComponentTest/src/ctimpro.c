/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈元
*@brief : CtImPro
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/

#include "ctimprofile.h"
#include "ctimpro1.h"
//ctimpro11-17.h是ctimpro1.h的重构
#include "ctimpro11.h"
#include "ctimpro12.h"
#include "ctimpro13.h"
#include "ctimpro14.h"
#include "ctimpro15.h"
#include "ctimpro16.h"
#include "ctimpro17.h"
#include "ctimpro2.h"
//ctimpro21-27.h是ctimpro2.h的重构
#include "ctimpro21.h"
#include "ctimpro22.h"
#include "ctimpro23.h"
#include "ctimpro24.h"
#include "ctimpro25.h"
#include "ctimpro26.h"
#include "ctimpro27.h"
#include "ctimpro3.h"
//ctimpro31-33.h是ctimpro3的.h重构
#include "ctimpro31.h"
#include "ctimpro32.h"
#include "ctimpro33.h"
#include "ctimpro4.h"
//ctimpro4last.h和ctimpro4last.h是ctimpro4.h的重构
#include "ctimpro4continue.h"
#include "ctimpro4last.h"
#include "ctimpro5.h"
#include "ctimpro6.h"
#include "ctimpro7.h"
#include "ctimpro8.h"


#ifndef CO_CT_IM_PRO_DISABLE

static const volatile T_ct_im_pro_Func S_G_CT_IM_PRO_FUNC_TBL[D_FUNC_TABLE_CATE_NUM][D_FUNC_TABLE_FUNC_NUM] = {
    {	// sen
        ct_im_pro1_1, ct_im_pro1_2, ct_im_pro1_3, ct_im_pro1_4, ct_im_pro1_5, ct_im_pro1_6, ct_im_pro1_7,
        ct_im_pro1_8, ct_im_pro1_9, ct_im_pro1_1_0, ct_im_pro1_1_1, ct_im_pro1_1_2, ct_im_pro1_1_3, ct_im_pro1_1_4,
        ct_im_pro1_1_5, ct_im_pro1_1_6, ct_im_pro1_1_7, ct_im_pro1_1_8, ct_im_pro1_1_9, ct_im_pro1_2_0,
        ct_im_pro1_2_1, ct_im_pro1_2_2, ct_im_pro1_2_3, ct_im_pro1_2_4, ct_im_pro1_2_5, ct_im_pro1_2_6,
        ct_im_pro1_2_7, ct_im_pro1_2_8, ct_im_pro1_2_9, ct_im_pro1_3_0, ct_im_pro1_3_1, ct_im_pro1_3_2,
        ct_im_pro1_3_3, ct_im_pro1_3_4, ct_im_pro1_3_5, ct_im_pro1_3_6, ct_im_pro1_3_7, ct_im_pro1_3_8,
        ct_im_pro1_3_9, ct_im_pro1_4_0, ct_im_pro1_4_1, ct_im_pro1_4_2, ct_im_pro1_4_3, ct_im_pro1_4_4,
        ct_im_pro1_4_5, ct_im_pro1_4_6, ct_im_pro1_4_7, ct_im_pro1_4_8, ct_im_pro1_4_9, ct_im_pro1_5_0,
        ct_im_pro1_5_1, ct_im_pro1_5_2, ct_im_pro1_5_3, ct_im_pro1_5_4, ct_im_pro1_5_5, ct_im_pro1_5_6,
        ct_im_pro1_5_7, ct_im_pro1_5_8, ct_im_pro1_5_9, ct_im_pro1_6_0, ct_im_pro1_6_1, ct_im_pro1_6_2,
        ct_im_pro1_6_3, ct_im_pro1_6_4, ct_im_pro1_6_5, ct_im_pro1_6_6, ct_im_pro1_6_7, ct_im_pro1_6_8,
        ct_im_pro1_6_9, ct_im_pro1_7_0, ct_im_pro1_7_1, ct_im_pro1_7_2,
    },
    {   // sro
        ct_im_pro2_1, ct_im_pro2_2, ct_im_pro2_3, ct_im_pro2_4, ct_im_pro2_5, ct_im_pro2_6,  ct_im_pro2_7,
        ct_im_pro2_8, ct_im_pro2_9, ct_im_pro2_1_0, ct_im_pro2_1_1, ct_im_pro2_1_2, ct_im_pro2_1_3, ct_im_pro2_1_4,
        ct_im_pro2_1_5, ct_im_pro2_1_6, ct_im_pro2_1_7, ct_im_pro2_1_8, ct_im_pro2_1_9, ct_im_pro2_2_0,
        ct_im_pro2_2_1, ct_im_pro2_2_2, ct_im_pro2_2_3, ct_im_pro2_2_4, ct_im_pro2_2_5, ct_im_pro2_2_6,
        ct_im_pro2_2_7, ct_im_pro2_2_8, ct_im_pro2_2_9, ct_im_pro2_3_0,ct_im_pro2_3_1, ct_im_pro2_3_2,
        ct_im_pro2_3_3, ct_im_pro2_3_4, ct_im_pro2_3_5, ct_im_pro2_3_6, ct_im_pro2_3_7, ct_im_pro2_3_8,
        ct_im_pro2_3_9, ct_im_pro2_4_0, ct_im_pro2_4_1, ct_im_pro2_4_2, ct_im_pro2_4_3, ct_im_pro2_4_4,
        ct_im_pro2_4_5, ct_im_pro2_4_6, ct_im_pro2_4_7, ct_im_pro2_4_8, ct_im_pro2_4_9, ct_im_pro2_5_0,
        ct_im_pro2_5_1, ct_im_pro2_5_2, ct_im_pro2_5_3, ct_im_pro2_5_4, ct_im_pro2_5_5, ct_im_pro2_5_6,
        ct_im_pro2_5_7, ct_im_pro2_5_8, ct_im_pro2_5_9, ct_im_pro2_6_0, ct_im_pro2_6_1, ct_im_pro2_6_2,
        ct_im_pro2_6_3, ct_im_pro2_6_4, ct_im_pro2_6_5, ct_im_pro2_6_6, ct_im_pro2_6_7, ct_im_pro2_6_8,
        ct_im_pro2_6_9, ct_im_pro2_7_0, ct_im_pro2_7_1, ct_im_pro2_7_2, ct_im_pro2_7_3, ct_im_pro2_7_4, ct_im_pro2_7_5,
    },
    {   // b2b
        ct_im_pro3_1, ct_im_pro3_2, ct_im_pro3_3, ct_im_pro3_4, ct_im_pro3_5, ct_im_pro3_6, ct_im_pro3_7,
        ct_im_pro3_8, ct_im_pro3_9, ct_im_pro3_1_0, ct_im_pro3_1_1, ct_im_pro3_1_2, ct_im_pro3_1_3, ct_im_pro3_1_4,
        ct_im_pro3_1_5, ct_im_pro3_1_6, ct_im_pro3_1_7, ct_im_pro3_1_8, ct_im_pro3_1_9, ct_im_pro3_2_0,
        ct_im_pro3_2_1, ct_im_pro3_2_2, ct_im_pro3_2_3, ct_im_pro3_2_4, ct_im_pro3_2_5, ct_im_pro3_2_6,
        ct_im_pro3_2_7, ct_im_pro3_2_8, ct_im_pro3_2_9, ct_im_pro3_3_0, ct_im_pro3_3_1, ct_im_pro3_3_2,
        ct_im_pro3_3_3, ct_im_pro3_3_4, ct_im_pro3_3_5, ct_im_pro3_3_6, ct_im_pro3_3_7,ct_im_pro3_3_8,
    },
    {   // stat
        ct_im_pro4_1, ct_im_pro4_2, ct_im_pro4_3, ct_im_pro4_4, ct_im_pro4_5, ct_im_pro4_6, ct_im_pro4_7,
        ct_im_pro4_8, ct_im_pro4_9, ct_im_pro4_10, ct_im_pro4_11, ct_im_pro4_12, ct_im_pro4_13, ct_im_pro4_14,
        ct_im_pro4_15, ct_im_pro4_16, ct_im_pro4_17, ct_im_pro4_18, ct_im_pro4_19, ct_im_pro4_20, ct_im_pro4_21,
        ct_im_pro4_22, ct_im_pro4_23, ct_im_pro4_24, ct_im_pro4_25, ct_im_pro4_26, ct_im_pro4_27, ct_im_pro4_28,
        ct_im_pro4_continue_29, ct_im_pro4_continue_30, ct_im_pro4_continue_31, ct_im_pro4_continue_32,
        ct_im_pro4_continue_33, ct_im_pro4_continue_34, ct_im_pro4_continue_35, ct_im_pro4_continue_36,
        ct_im_pro4_continue_37, ct_im_pro4_continue_38, ct_im_pro4_continue_39, ct_im_pro4_continue_40,
        ct_im_pro4_continue_41, ct_im_pro4_continue_42, ct_im_pro4_continue_43, ct_im_pro4_continue_44,
        ct_im_pro4_continue_45, ct_im_pro4_continue_46, ct_im_pro4_continue_47, ct_im_pro4_continue_48,
        ct_im_pro4_continue_49, ct_im_pro4_continue_50, ct_im_pro4_continue_51, ct_im_pro4_continue_52,
        ct_im_pro4_continue_53, ct_im_pro4_continue_54, ct_im_pro4_continue_55, ct_im_pro4_continue_56,
        ct_im_pro4_continue_57, ct_im_pro4_last_58, ct_im_pro4_last_59, ct_im_pro4_last_60, ct_im_pro4_last_61,
        ct_im_pro4_last_62, ct_im_pro4_last_63, ct_im_pro4_last_64, ct_im_pro4_last_65, ct_im_pro4_last_66,
        ct_im_pro4_last_67, ct_im_pro4_last_68, ct_im_pro4_last_69, ct_im_pro4_last_70, ct_im_pro4_last_71,
        ct_im_pro4_last_72, ct_im_pro4_last_73, ct_im_pro4_last_74, ct_im_pro4_last_75, ct_im_pro4_last_76,
        ct_im_pro4_last_77, ct_im_pro4_last_78, ct_im_pro4_last_79, ct_im_pro4_last_80, ct_im_pro4_last_81,
        ct_im_pro4_last_82, ct_im_pro4_last_83,
    },
    {   // pas
        ct_im_pro5_1, ct_im_pro5_2, ct_im_pro5_3, ct_im_pro5_4, ct_im_pro5_5, ct_im_pro5_6,  ct_im_pro5_7,
        ct_im_pro5_8, ct_im_pro5_9, ct_im_pro5_10,
    },
    {   // Common
        ct_im_pro_6_0_1, ct_im_pro_6_0_2, ct_im_pro_6_0_3, ct_im_pro_6_0_4, ct_im_pro_6_0_5, ct_im_pro_6_0_6,
        ct_im_pro_6_0_7,
        ct_im_pro_6_0_8, ct_im_pro_6_0_9, ct_im_pro_6_1_0, ct_im_pro_6_11, ct_im_pro_6_12, ct_im_pro_6_13, ct_im_pro_6_14,
        ct_im_pro_6_15, ct_im_pro_6_16, ct_im_pro_6_17, ct_im_pro_6_18, ct_im_pro_6_19, ct_im_pro_6_20,
        ct_im_pro_6_21, ct_im_pro_6_22, ct_im_pro_6_23, ct_im_pro_6_24, ct_im_pro_6_25, ct_im_pro_6_26,
        ct_im_pro_6_27, ct_im_pro_6_28, ct_im_pro_6_29, ct_im_pro_6_30, ct_im_pro_6_31, ct_im_pro_6_32,
        ct_im_pro_6_33, ct_im_pro_6_34, ct_im_pro_6_35, ct_im_pro_6_36, ct_im_pro_6_37, ct_im_pro_6_38,
        ct_im_pro_6_39, ct_im_pro_6_40, ct_im_pro_6_41, ct_im_pro_6_42, ct_im_pro_6_43, ct_im_pro_6_44,
        ct_im_pro_6_45, ct_im_pro_6_46, ct_im_pro_6_47,
    },//TODO
    {   // Interrupt
        ct_im_pro_7_1, ct_im_pro_7_2, ct_im_pro_7_3, ct_im_pro_7_4, ct_im_pro_7_5, ct_im_pro_7_6, ct_im_pro_7_7,
        ct_im_pro_7_8, ct_im_pro_7_9, ct_im_pro_7_10, ct_im_pro_7_11, ct_im_pro_7_12, ct_im_pro_7_13, ct_im_pro_7_14,
        ct_im_pro_7_15, ct_im_pro_7_16, ct_im_pro_7_17, ct_im_pro_7_18, ct_im_pro_7_19, ct_im_pro_7_20,
        ct_im_pro_7_21, ct_im_pro_7_22, ct_im_pro_7_23, ct_im_pro_7_24, ct_im_pro_7_25, ct_im_pro_7_26,
        ct_im_pro_7_27, ct_im_pro_7_28, ct_im_pro_7_29, ct_im_pro_7_30, ct_im_pro_7_31, ct_im_pro_7_32,
        ct_im_pro_7_33, ct_im_pro_7_34, ct_im_pro_7_35, ct_im_pro_7_36, ct_im_pro_7_37, ct_im_pro_7_38,
        ct_im_pro_7_39, ct_im_pro_7_40, ct_im_pro_7_41, ct_im_pro_7_42, ct_im_pro_7_43, ct_im_pro_7_44,
        ct_im_pro_7_45, ct_im_pro_7_46, ct_im_pro_7_47, ct_im_pro_7_48, ct_im_pro_7_49, ct_im_pro_7_50,
        ct_im_pro_7_51, ct_im_pro_7_52, ct_im_pro_7_53, ct_im_pro_7_54, ct_im_pro_7_55, ct_im_pro_7_56,
        ct_im_pro_7_57, ct_im_pro_7_58, ct_im_pro_7_59, ct_im_pro_7_60, ct_im_pro_7_61, ct_im_pro_7_62,
        ct_im_pro_7_63, ct_im_pro_7_64, ct_im_pro_7_65, ct_im_pro_7_66, ct_im_pro_7_67, ct_im_pro_7_68,
        ct_im_pro_7_69, ct_im_pro_7_70, ct_im_pro_7_71, ct_im_pro_7_72, ct_im_pro_7_73, ct_im_pro_7_74,
        ct_im_pro_7_75, ct_im_pro_7_76, ct_im_pro_7_77, ct_im_pro_7_78, ct_im_pro_7_79, ct_im_pro_7_80,
        ct_im_pro_7_81, ct_im_pro_7_82, ct_im_pro_7_83, ct_im_pro_7_84, ct_im_pro_7_85, ct_im_pro_7_86,
        ct_im_pro_7_87, ct_im_pro_7_88, ct_im_pro_7_89, ct_im_pro_7_90, ct_im_pro_7_91,
    },//TODO
    {   // Board BringUp
        ct_im_pro_8_1, ct_im_pro_8_2, ct_im_pro_8_3, ct_im_pro_8_4, ct_im_pro_8_5, ct_im_pro_8_6, ct_im_pro_8_7,
        ct_im_pro_8_8, ct_im_pro_8_9, ct_im_pro_8_10,
    },//TODO
};

#define IM_PRO_FUNC_NAME "ct_im_pro_%u_%u_%u: "
static char S_IM_PRO_FUNC_NAME_STRING[100];


void ct_im_pro_run(const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd, kuint32 allTestFlg)
{
	ImproSentop *improSentop = impro_sentop_new();//TODO
	ImproSrotop *improSrotop = impro_srotop_new();//TODO
	ImproPastop *improPastop = impro_pastop_new();//TODO
	static BOOL S_IS_INIT = 1;
	kint32 ercd;

	if ((ctIdx1st == 0) || (ctIdx2nd == 0)) {
		im_pro_management_info_print();//TODO
		//Ddim_Print(("Error: Unknown command.(%u-%u-%u)\n", ctIdx1st, ctIdx2nd, ctIdx3rd));
		return;
	}

	Ddim_Print(("ct_im_pro_run(%u, %u, %u) Begin\n", ctIdx1st, ctIdx2nd, ctIdx3rd));

	if (S_IS_INIT == 0) {
#ifdef CO_DEBUG_ON_PC
		memset((void*)&ioPro, '\0', sizeof(ioPro));
		memset((void*)&ioProTbl, '\0', sizeof(ioProTbl));

		// sen unit
		ioPro.sen.sg[0].sgtrg.bit.sgtrg = 2;
		ioPro.sen.sg[1].sgtrg.bit.sgtrg = 2;
		ioPro.sen.sg[2].sgtrg.bit.sgtrg = 2;
		ioPro.sen.sg[3].sgtrg.bit.sgtrg = 2;
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_A].trgr.bit.trg = 2;
		ioPro.sen.slvsec.stream[E_IM_PRO_SLVS_STREAM_TYPE_B].trgr.bit.trg = 2;
		ioPro.sen.ldiv[0].ldivtrg.bit.ldivtrg = 2;
		ioPro.sen.ldiv[1].ldivtrg.bit.ldivtrg = 2;
		ioPro.sen.ldiv[2].ldivtrg.bit.ldivtrg = 2;
		ioPro.sen.ldiv[3].ldivtrg.bit.ldivtrg = 2;
		ioPro.sen.obd[0][0].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[0][1].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[1][0].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[1][1].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[2][0].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[2][1].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[3][0].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obd[3][1].obdtrg.bit.obdtrg = 2;
		ioPro.sen.obt[0][0].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[0][1].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[1][0].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[1][1].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[2][0].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[2][1].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[3][0].obttrg.bit.obttrg = 2;
		ioPro.sen.obt[3][1].obttrg.bit.obttrg = 2;
		ioPro.sen.mipid[0].mpitrg.bit.mpitrg = 2;
		ioPro.sen.mipid[1].mpitrg.bit.mpitrg = 2;
		ioPro.sen.mipid[2].mpitrg.bit.mpitrg = 2;
		ioPro.sen.mipid[3].mpitrg.bit.mpitrg = 2;
		ioPro.sen.mipic[0].mpictrg.bit.mpictrg = 2;
		ioPro.sen.mipic[1].mpictrg.bit.mpictrg = 2;
		ioPro.sen.mipic[2].mpictrg.bit.mpictrg = 2;
		ioPro.sen.mipic[3].mpictrg.bit.mpictrg = 2;
		ioPro.sen.lvds[0].lvdstrg.bit.lvdstrg = 2;
		ioPro.sen.lvds[1].lvdstrg.bit.lvdstrg = 2;
		ioPro.sen.lvds[2].lvdstrg.bit.lvdstrg = 2;
		ioPro.sen.lvds[3].lvdstrg.bit.lvdstrg = 2;
		ioPro.sen.lnr[0].lnrtrg.bit.lnrtrg = 2;
		ioPro.sen.lnr[1].lnrtrg.bit.lnrtrg = 2;
		ioPro.sen.lnr[2].lnrtrg.bit.lnrtrg = 2;
		ioPro.sen.lnr[3].lnrtrg.bit.lnrtrg = 2;
		ioPro.sen.p2m[0].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[1].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[2].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[3].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[4].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[5].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[6].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.p2m[7].p2mtrg.bit.p2mtrg = 2;
		ioPro.sen.pwch[0].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[1].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[2].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[3].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[4].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[5].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[6].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.pwch[7].pwchtrg.bit.pwchtrg = 2;
		ioPro.sen.moni[0].monitrg.bit.monitrg = 2;
		ioPro.sen.moni[1].monitrg.bit.monitrg = 2;
		ioPro.sen.moni[2].monitrg.bit.monitrg = 2;
		ioPro.sen.moni[3].monitrg.bit.monitrg = 2;

		for(kint32 i = 0; i < E_IM_PRO_BOTH_UNIT; i++) {
			// sro unit
			ioPro.imgPipe[i].sro.pg.pgtrg.bit.pgtrg = 2;
			ioPro.imgPipe[i].sro.m2p[0].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[1].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.prch[0].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[1].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.p2m[0].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.p2m[1].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.p2m[2].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.p2m[3].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.p2m[4].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.p2m[5].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].sro.pwch[0].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.pwch[1].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.pwch[2].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.pwch[3].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.pwch[4].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.pwch[5].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].sro.m2p[0].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[1].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[2].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[3].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[6].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[7].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[8].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.m2p[9].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].sro.prch[0].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[1].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[2].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[3].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[4].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[5].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[6].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[7].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[8].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.prch[9].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].sro.pgain0.pgaintrg.bit.pgaintrg = 2;
			ioPro.imgPipe[i].sro.moni0.monitrg.bit.monitrg = 2;
			ioPro.imgPipe[i].sro.pzsftb1.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[i].sro.pzsftb2.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[i].sro.pzsftc1.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[i].sro.pzsftc2.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[i].sro.fshdl0.ffshtrg.bit.ffshtrg = 2;
			ioPro.imgPipe[i].sro.fshdl1.ffshtrg.bit.ffshtrg = 2;
			ioPro.imgPipe[i].sro.cag.cagtrg.bit.cagtrg = 2;
			ioPro.imgPipe[i].sro.dpc.dpctrg.bit.dpctrg = 2;
			ioPro.imgPipe[i].sro.ffc.fctrg.bit.fctrg = 2;
			ioPro.imgPipe[i].sro.hrb.hrbtrg.bit.hrbtrg = 2;
			ioPro.imgPipe[i].sro.ffsh[0].ffshtrg.bit.ffshtrg = 2;
			ioPro.imgPipe[i].sro.ffsh[1].ffshtrg.bit.ffshtrg = 2;
			ioPro.imgPipe[i].sro.ff[0].fftrg.bit.fftrg = 2;
			ioPro.imgPipe[i].sro.ff[1].fftrg.bit.fftrg = 2;
			ioPro.imgPipe[i].sro.sdc[0].sdctrg.bit.sdctrg = 2;
			ioPro.imgPipe[i].sro.sdc[1].sdctrg.bit.sdctrg = 2;
			ioPro.imgPipe[i].sro.afpb[0].afpbtrg.bit.afpbtrg = 2;
			ioPro.imgPipe[i].sro.afpb[1].afpbtrg.bit.afpbtrg = 2;

			// b2b unit
			ioPro.imgPipe[i].b2b.pg.pgtrg.bit.pgtrg = 2;
			ioPro.imgPipe[i].b2b.m2p[0].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].b2b.m2p[1].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].b2b.m2p[2].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].b2b.m2p[3].m2ptrg.bit.m2ptrg = 2;
			ioPro.imgPipe[i].b2b.prch[0].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].b2b.prch[1].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].b2b.prch[2].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].b2b.prch[3].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].b2b.prch[4].prchtrg.bit.prchtrg = 2;
			ioPro.imgPipe[i].b2b.pwch[0].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].b2b.pwch[1].pwchtrg.bit.pwchtrg = 2;
			ioPro.imgPipe[i].b2b.p2m[0].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].b2b.p2m[1].p2mtrg.bit.p2mtrg = 2;
			ioPro.imgPipe[i].b2b.pgain1.pgaintrg.bit.pgaintrg = 2;
			ioPro.imgPipe[i].b2b.pgain2.pgaintrg.bit.pgaintrg = 2;
			ioPro.imgPipe[1].b2b.pzsfta1.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[1].b2b.pzsfta2.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[1].b2b.pzsfta2a.pzsfttrg.bit.pzsfttrg = 2;
			ioPro.imgPipe[i].b2b.elf.elftrg.bit.elftrg = 2;
			ioPro.imgPipe[i].b2b.elf.nsltrg.bit.nsltrg = 2;
			ioPro.imgPipe[i].b2b.fshd.fshdtrg.bit.fshdtrg = 2;
		}

		// stat unit
		ioPro.stat.aeawb[0].aetrg.bit.aetrg = 2;
		ioPro.stat.aeawb[1].aetrg.bit.aetrg = 2;
		ioPro.stat.aeawb[2].aetrg.bit.aetrg = 2;
		ioPro.stat.aeawb[3].aetrg.bit.aetrg = 2;
		ioPro.stat.af[0].afgbal.aftrg.bit.aftrg = 2;
		ioPro.stat.af[1].afgbal.aftrg.bit.aftrg = 2;
		ioPro.stat.hist[0].histtrg.bit.histtrg = 2;
		ioPro.stat.hist[1].histtrg.bit.histtrg = 2;
		ioPro.stat.hist[2].histtrg.bit.histtrg = 2;
		ioPro.stat.hist[3].histtrg.bit.histtrg = 2;
		ioPro.stat.flck[0].fltrg.bit.fltrg = 2;
		ioPro.stat.flck[1].fltrg.bit.fltrg = 2;
		ioPro.stat.pwch[0].pwchtrg.bit.pwchtrg = 2;
		ioPro.stat.pwch[1].pwchtrg.bit.pwchtrg = 2;
		ioPro.stat.pwch[2].pwchtrg.bit.pwchtrg = 2;
		ioPro.stat.pwch[3].pwchtrg.bit.pwchtrg = 2;
		ioPro.stat.pwch[4].pwchtrg.bit.pwchtrg = 2;
		ioPro.stat.pwch[5].pwchtrg.bit.pwchtrg = 2;

		// pas unit
		ioPro.pas.spt.spttrg.bit.spttrg = 2;
		ioPro.pas.p2m0.p2mtrg.bit.p2mtrg = 2;
		ioPro.pas.pwch0.pwchtrg.bit.pwchtrg = 2;
		ioPro.pas.pg.pgtrg.bit.pgtrg = 2;
		ioPro.pas.m2p0.m2ptrg.bit.m2ptrg = 2;
		ioPro.pas.prch0.prchtrg.bit.prchtrg = 2;
		ioPro.pas.lnr.lnrtrg.bit.lnrtrg = 2;
		ioPro.pas.pgain.pgaintrg.bit.pgaintrg = 2;

#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
		Dd_Top_Set_CLKSTOP1_SENAP(1);//TODO
		Dd_Top_Set_CLKSTOP1_SENAH(1);
		Dd_Top_Set_CLKSTOP1_SENAX(1);
		Dd_Top_Set_CLKSTOP1_SENCK(1);

		Dd_Top_Set_CLKSTOP10_SRO1AP(1);
		Dd_Top_Set_CLKSTOP10_SRO1AH(1);
		Dd_Top_Set_CLKSTOP10_SRO1AX(1);
		Dd_Top_Set_CLKSTOP10_SRO1CK(1);
		Dd_Top_Set_CLKSTOP10_SRO1CK_2(1);

		Dd_Top_Set_CLKSTOP10_B2B1AP(1);
		Dd_Top_Set_CLKSTOP10_B2B1AH(1);
		Dd_Top_Set_CLKSTOP10_B2B1AX(1);
		Dd_Top_Set_CLKSTOP10_B2B1CK(1);

		Dd_Top_Set_CLKSTOP14_STATAP(1);
		Dd_Top_Set_CLKSTOP14_STATAH(1);
		Dd_Top_Set_CLKSTOP14_STATAX(1);

		// need initialization of bus clock for pas
		Dd_Top_Set_CLKSTOP14_PASCK(1);
#endif
		// sen interrupt
		ct_im_pro_7_23(1);//TODO
		ct_im_pro_7_24(1);
		ct_im_pro_7_25(1);
		ct_im_pro_7_26(1);
		ct_im_pro_7_27(1);
		ct_im_pro_7_28(1);
		ct_im_pro_7_29(1);

		// sro interrupt
		ct_im_pro_7_53(1);
		ct_im_pro_7_54(1);
		ct_im_pro_7_55(1);
		ct_im_pro_7_56(1);
		ct_im_pro_7_57(1);
		ct_im_pro_7_58(1);

		// b2b interrupt
		ct_im_pro_7_66(1);
		ct_im_pro_7_67(1);
		ct_im_pro_7_68(1);
		ct_im_pro_7_69(1);
		ct_im_pro_7_70(1);
		ct_im_pro_7_71(1);

		// stat interrupt
		ct_im_pro_7_73(1);

		// pas interrupt
		ct_im_pro_7_85(1);
		ct_im_pro_7_86(1);
		ct_im_pro_7_87(1);
#endif // CO_DEBUG_ON_PC

		if (!((ctIdx1st == 1) && (ctIdx2nd == 1) && (ctIdx3rd == 1))) {
			Ddim_Print(("impro_sentop_sw_reset() Begin\n"));
			ercd = impro_sentop_sw_reset(improSentop);
			if (ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("impro_sentop_sw_reset() Error ercd=0x%x\n", ercd));
			} else {
			}
			Ddim_Print(("impro_sentop_sw_reset() End\n"));

			Ddim_Print(("impro_sentop_init() Begin\n"));
			impro_sentop_init(improSentop);
			Ddim_Print(("impro_sentop_init() End\n"));

			for (kint32 i = 0; i < E_IM_PRO_BOTH_UNIT; i++) {//TODO
				Ddim_Print(("impro_srotop_sw_reset(%u) Begin\n", i));
				ercd = impro_srotop_sw_reset(improSrotop, (E_IM_PRO_UNIT_NUM) i);//TODO
				if (ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("impro_srotop_sw_reset(%u) Error ercd=0x%x\n", i, ercd));
				} else {
				}
				Ddim_Print(("impro_srotop_sw_reset(%u) End\n", i));

				Ddim_Print(("impro_srotop_init(%u) Begin\n", i));
				impro_srotop_init(improSrotop, (E_IM_PRO_UNIT_NUM) i);//TODO
				Ddim_Print(("impro_srotop_init(%u) End\n", i));

				Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) Begin\n", i));
				ercd = Im_PRO_B2BTOP_SW_Reset((E_IM_PRO_UNIT_NUM) i);//TODO
				if (ercd != DdimUserCustom_E_OK) {
					Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) Error ercd=0x%x\n", i, ercd));
				} else {
				}
				Ddim_Print(("Im_PRO_B2BTOP_SW_Reset(%u) End\n", i));

				Ddim_Print(("Im_PRO_B2BTOP_Init(%u) Begin\n", i));
				Im_PRO_B2BTOP_Init((E_IM_PRO_UNIT_NUM) i);//TODO
				Ddim_Print(("Im_PRO_B2BTOP_Init(%u) End\n", i));
			}

			Ddim_Print(("Im_PRO_STATTOP_SW_Reset() Begin\n"));
			ercd = Im_PRO_STATTOP_SW_Reset();//TODO
			if (ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("Im_PRO_STATTOP_SW_Reset() Error ercd=0x%x\n", ercd));
			} else {
			}
			Ddim_Print(("Im_PRO_STATTOP_SW_Reset() End\n"));

			Ddim_Print(("Im_PRO_STATTOP_Init() Begin\n"));
			Im_PRO_STATTOP_Init();//TODO
			Ddim_Print(("Im_PRO_STATTOP_Init() End\n"));

			Ddim_Print(("impro_pastop_sw_reset() Begin\n"));
			ercd = impro_pastop_sw_reset(improPastop);
			if (ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("impro_pastop_sw_reset() Error ercd=0x%x\n", ercd));
			} else {
			}
			Ddim_Print(("impro_pastop_sw_reset() End\n"));

			Ddim_Print(("impro_pastop_init() Begin\n"));
			impro_pastop_init(improPastop);
			Ddim_Print(("impro_pastop_init() End\n"));

			S_IS_INIT = 1;
		}
	}

#ifdef CO_PRO_DEBUG_PRINT_FUNC
	Im_PRO_Print_ClockStatus();//TODO
#endif

	if (allTestFlg == 1) {
		for (kuint32 i = 0; i < D_FUNC_TABLE_CATE_NUM; i++) {//TODO
			for (kuint32 j = 0; j < D_FUNC_TABLE_FUNC_NUM; j++) {
				if ((S_G_CT_IM_PRO_FUNC_TBL[i][j] != NULL)) {
					sprintf(S_IM_PRO_FUNC_NAME_STRING, IM_PRO_FUNC_NAME, i + 1, j + 1, ctIdx3rd);
					Ddim_Print(("%sstart\n", S_IM_PRO_FUNC_NAME_STRING));
					S_G_CT_IM_PRO_FUNC_TBL[i][j](ctIdx3rd);
					Ddim_Print(("%send\n", S_IM_PRO_FUNC_NAME_STRING));
				} else {
					Ddim_Print(("Error: Unknown command.(%u-%u-%u)\n", i+1, j+1, ctIdx3rd));
				}
			}
		}
	} else {
		if ((S_G_CT_IM_PRO_FUNC_TBL[ctIdx1st - 1][ctIdx2nd - 1] != NULL)) {
			sprintf(S_IM_PRO_FUNC_NAME_STRING, IM_PRO_FUNC_NAME, ctIdx1st, ctIdx2nd, ctIdx3rd);
			Ddim_Print(("%sstart\n", S_IM_PRO_FUNC_NAME_STRING));
			S_G_CT_IM_PRO_FUNC_TBL[ctIdx1st - 1][ctIdx2nd - 1](ctIdx3rd);
			Ddim_Print(("%send\n", S_IM_PRO_FUNC_NAME_STRING));
		} else {
			Ddim_Print(("Error: Unknown command.(%u-%u-%u)\n", ctIdx1st, ctIdx2nd, ctIdx3rd));
		}
	}
}

/**
 * @brief:  Command main function for PRO test.
 * @param  int argc :The number of parameters
 *         char** argv  :The value of parameters
 * @return void
 */
void ct_im_pro_main(int argc, char** argv)
{
	if (argc < 4) {
		Ddim_Print(("ct_im_pro_main: parameter error.\n"));
		return;
	}

	ct_im_pro_run((kuint32) atoi((const char*) argv[1]), (kuint32) atoi((const char*) argv[2]),
			(kuint32) atoi((const char*) argv[3]), (kuint32) atoi((const char*) argv[4]));
}

#else   // CO_CT_IM_PRO_DISABLE

void ct_im_pro_run(const kuint32 ctIdx1st, const kuint32 ctIdx2nd, const kuint32 ctIdx3rd, kuint32 allTestFlg)
{
}

void ct_im_pro_main(int argc, char** argv)
{
}
#endif  // CO_CT_IM_PRO_DISABLE


