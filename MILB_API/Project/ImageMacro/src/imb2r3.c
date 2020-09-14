/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
//#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
//#endif
#include "dd_arm.h"

#include "jdsb2r.h"
#include "imrdma.h"
#include"imb2r.h"
#include"imb2r1.h"
#include"imb2r2.h"
#include"imb2r3.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImB2r3, im_b2r3);
#define IM_B2R3_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImB2r3Private, IM_TYPE_B2R3))

struct _ImB2r3Private
{
	int a;
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
static const T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_ADDR	S_G_IM_B2R_DEKNEE_TBL_ADDR[3] = {
	{
		{
			0x29482000, 0x29482004, 0x29482008, 0x2948200C, 0x29482010, 0x29482014, 0x29482018, 0x2948201C,
			0x29482020, 0x29482024, 0x29482028, 0x2948202C, 0x29482030, 0x29482034, 0x29482038, 0x2948203C,
			0x29482040, 0x29482044, 0x29482048, 0x2948204C, 0x29482050, 0x29482054, 0x29482058, 0x2948205C,
			0x29482060, 0x29482064, 0x29482068, 0x2948206C, 0x29482070, 0x29482074, 0x29482078, 0x2948207C,
			0x29482080, 0x29482084, 0x29482088, 0x2948208C, 0x29482090, 0x29482094, 0x29482098, 0x2948209C,
			0x294820A0, 0x294820A4, 0x294820A8, 0x294820AC, 0x294820B0, 0x294820B4, 0x294820B8, 0x294820BC,
			0x294820C0, 0x294820C4, 0x294820C8, 0x294820CC, 0x294820D0, 0x294820D4, 0x294820D8, 0x294820DC,
			0x294820E0, 0x294820E4, 0x294820E8, 0x294820EC, 0x294820F0, 0x294820F4, 0x294820F8, 0x294820FC,
			0x29482100, 0x29482104, 0x29482108, 0x2948210C, 0x29482110, 0x29482114, 0x29482118, 0x2948211C,
			0x29482120, 0x29482124, 0x29482128, 0x2948212C, 0x29482130, 0x29482134, 0x29482138, 0x2948213C,
			0x29482140, 0x29482144, 0x29482148, 0x2948214C, 0x29482150, 0x29482154, 0x29482158, 0x2948215C,
			0x29482160, 0x29482164, 0x29482168, 0x2948216C, 0x29482170, 0x29482174, 0x29482178, 0x2948217C,
			0x29482180, 0x29482184, 0x29482188, 0x2948218C, 0x29482190, 0x29482194, 0x29482198, 0x2948219C,
			0x294821A0, 0x294821A4, 0x294821A8, 0x294821AC, 0x294821B0, 0x294821B4, 0x294821B8, 0x294821BC,
			0x294821C0, 0x294821C4, 0x294821C8, 0x294821CC, 0x294821D0, 0x294821D4, 0x294821D8, 0x294821DC,
			0x294821E0, 0x294821E4, 0x294821E8, 0x294821EC, 0x294821F0, 0x294821F4, 0x294821F8, 0x294821FC,
		},
	},
	{
		{
			0x29582000, 0x29582004, 0x29582008, 0x2958200C, 0x29582010, 0x29582014, 0x29582018, 0x2958201C,
			0x29582020, 0x29582024, 0x29582028, 0x2958202C, 0x29582030, 0x29582034, 0x29582038, 0x2958203C,
			0x29582040, 0x29582044, 0x29582048, 0x2958204C, 0x29582050, 0x29582054, 0x29582058, 0x2958205C,
			0x29582060, 0x29582064, 0x29582068, 0x2958206C, 0x29582070, 0x29582074, 0x29582078, 0x2958207C,
			0x29582080, 0x29582084, 0x29582088, 0x2958208C, 0x29582090, 0x29582094, 0x29582098, 0x2958209C,
			0x295820A0, 0x295820A4, 0x295820A8, 0x295820AC, 0x295820B0, 0x295820B4, 0x295820B8, 0x295820BC,
			0x295820C0, 0x295820C4, 0x295820C8, 0x295820CC, 0x295820D0, 0x295820D4, 0x295820D8, 0x295820DC,
			0x295820E0, 0x295820E4, 0x295820E8, 0x295820EC, 0x295820F0, 0x295820F4, 0x295820F8, 0x295820FC,
			0x29582100, 0x29582104, 0x29582108, 0x2958210C, 0x29582110, 0x29582114, 0x29582118, 0x2958211C,
			0x29582120, 0x29582124, 0x29582128, 0x2958212C, 0x29582130, 0x29582134, 0x29582138, 0x2958213C,
			0x29582140, 0x29582144, 0x29582148, 0x2958214C, 0x29582150, 0x29582154, 0x29582158, 0x2958215C,
			0x29582160, 0x29582164, 0x29582168, 0x2958216C, 0x29582170, 0x29582174, 0x29582178, 0x2958217C,
			0x29582180, 0x29582184, 0x29582188, 0x2958218C, 0x29582190, 0x29582194, 0x29582198, 0x2958219C,
			0x295821A0, 0x295821A4, 0x295821A8, 0x295821AC, 0x295821B0, 0x295821B4, 0x295821B8, 0x295821BC,
			0x295821C0, 0x295821C4, 0x295821C8, 0x295821CC, 0x295821D0, 0x295821D4, 0x295821D8, 0x295821DC,
			0x295821E0, 0x295821E4, 0x295821E8, 0x295821EC, 0x295821F0, 0x295821F4, 0x295821F8, 0x295821FC,
		},
	},
	{
		{
			0x29682000, 0x29682004, 0x29682008, 0x2968200C, 0x29682010, 0x29682014, 0x29682018, 0x2968201C,
			0x29682020, 0x29682024, 0x29682028, 0x2968202C, 0x29682030, 0x29682034, 0x29682038, 0x2968203C,
			0x29682040, 0x29682044, 0x29682048, 0x2968204C, 0x29682050, 0x29682054, 0x29682058, 0x2968205C,
			0x29682060, 0x29682064, 0x29682068, 0x2968206C, 0x29682070, 0x29682074, 0x29682078, 0x2968207C,
			0x29682080, 0x29682084, 0x29682088, 0x2968208C, 0x29682090, 0x29682094, 0x29682098, 0x2968209C,
			0x296820A0, 0x296820A4, 0x296820A8, 0x296820AC, 0x296820B0, 0x296820B4, 0x296820B8, 0x296820BC,
			0x296820C0, 0x296820C4, 0x296820C8, 0x296820CC, 0x296820D0, 0x296820D4, 0x296820D8, 0x296820DC,
			0x296820E0, 0x296820E4, 0x296820E8, 0x296820EC, 0x296820F0, 0x296820F4, 0x296820F8, 0x296820FC,
			0x29682100, 0x29682104, 0x29682108, 0x2968210C, 0x29682110, 0x29682114, 0x29682118, 0x2968211C,
			0x29682120, 0x29682124, 0x29682128, 0x2968212C, 0x29682130, 0x29682134, 0x29682138, 0x2968213C,
			0x29682140, 0x29682144, 0x29682148, 0x2968214C, 0x29682150, 0x29682154, 0x29682158, 0x2968215C,
			0x29682160, 0x29682164, 0x29682168, 0x2968216C, 0x29682170, 0x29682174, 0x29682178, 0x2968217C,
			0x29682180, 0x29682184, 0x29682188, 0x2968218C, 0x29682190, 0x29682194, 0x29682198, 0x2968219C,
			0x296821A0, 0x296821A4, 0x296821A8, 0x296821AC, 0x296821B0, 0x296821B4, 0x296821B8, 0x296821BC,
			0x296821C0, 0x296821C4, 0x296821C8, 0x296821CC, 0x296821D0, 0x296821D4, 0x296821D8, 0x296821DC,
			0x296821E0, 0x296821E4, 0x296821E8, 0x296821EC, 0x296821F0, 0x296821F4, 0x296821F8, 0x296821FC,
		},
	},
};
static const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR	S_G_IM_B2R_KNEE_TBL_R_ADDR[3] = {
	{
		{
			0x29482800, 0x29482804, 0x29482808, 0x2948280C, 0x29482810, 0x29482814, 0x29482818, 0x2948281C,
			0x29482820, 0x29482824, 0x29482828, 0x2948282C, 0x29482830, 0x29482834, 0x29482838, 0x2948283C,
			0x29482840, 0x29482844, 0x29482848, 0x2948284C, 0x29482850, 0x29482854, 0x29482858, 0x2948285C,
			0x29482860, 0x29482864, 0x29482868, 0x2948286C, 0x29482870, 0x29482874, 0x29482878, 0x2948287C,
			0x29482880, 0x29482884, 0x29482888, 0x2948288C, 0x29482890, 0x29482894, 0x29482898, 0x2948289C,
			0x294828A0, 0x294828A4, 0x294828A8, 0x294828AC, 0x294828B0, 0x294828B4, 0x294828B8, 0x294828BC,
			0x294828C0, 0x294828C4, 0x294828C8, 0x294828CC, 0x294828D0, 0x294828D4, 0x294828D8, 0x294828DC,
			0x294828E0, 0x294828E4, 0x294828E8, 0x294828EC, 0x294828F0, 0x294828F4, 0x294828F8, 0x294828FC,
			0x29482900,
		},
	},
	{
		{
			0x29582800, 0x29582804, 0x29582808, 0x2958280C, 0x29582810, 0x29582814, 0x29582818, 0x2958281C,
			0x29582820, 0x29582824, 0x29582828, 0x2958282C, 0x29582830, 0x29582834, 0x29582838, 0x2958283C,
			0x29582840, 0x29582844, 0x29582848, 0x2958284C, 0x29582850, 0x29582854, 0x29582858, 0x2958285C,
			0x29582860, 0x29582864, 0x29582868, 0x2958286C, 0x29582870, 0x29582874, 0x29582878, 0x2958287C,
			0x29582880, 0x29582884, 0x29582888, 0x2958288C, 0x29582890, 0x29582894, 0x29582898, 0x2958289C,
			0x295828A0, 0x295828A4, 0x295828A8, 0x295828AC, 0x295828B0, 0x295828B4, 0x295828B8, 0x295828BC,
			0x295828C0, 0x295828C4, 0x295828C8, 0x295828CC, 0x295828D0, 0x295828D4, 0x295828D8, 0x295828DC,
			0x295828E0, 0x295828E4, 0x295828E8, 0x295828EC, 0x295828F0, 0x295828F4, 0x295828F8, 0x295828FC,
			0x29582900,
		},
	},
	{
		{
			0x29682800, 0x29682804, 0x29682808, 0x2968280C, 0x29682810, 0x29682814, 0x29682818, 0x2968281C,
			0x29682820, 0x29682824, 0x29682828, 0x2968282C, 0x29682830, 0x29682834, 0x29682838, 0x2968283C,
			0x29682840, 0x29682844, 0x29682848, 0x2968284C, 0x29682850, 0x29682854, 0x29682858, 0x2968285C,
			0x29682860, 0x29682864, 0x29682868, 0x2968286C, 0x29682870, 0x29682874, 0x29682878, 0x2968287C,
			0x29682880, 0x29682884, 0x29682888, 0x2968288C, 0x29682890, 0x29682894, 0x29682898, 0x2968289C,
			0x296828A0, 0x296828A4, 0x296828A8, 0x296828AC, 0x296828B0, 0x296828B4, 0x296828B8, 0x296828BC,
			0x296828C0, 0x296828C4, 0x296828C8, 0x296828CC, 0x296828D0, 0x296828D4, 0x296828D8, 0x296828DC,
			0x296828E0, 0x296828E4, 0x296828E8, 0x296828EC, 0x296828F0, 0x296828F4, 0x296828F8, 0x296828FC,
			0x29682900,
		},
	},
};

static const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR	S_G_IM_B2R_KNEE_TBL_G_ADDR[3] = {
	{
		{
			0x29482A00, 0x29482A04, 0x29482A08, 0x29482A0C, 0x29482A10, 0x29482A14, 0x29482A18, 0x29482A1C,
			0x29482A20, 0x29482A24, 0x29482A28, 0x29482A2C, 0x29482A30, 0x29482A34, 0x29482A38, 0x29482A3C,
			0x29482A40, 0x29482A44, 0x29482A48, 0x29482A4C, 0x29482A50, 0x29482A54, 0x29482A58, 0x29482A5C,
			0x29482A60, 0x29482A64, 0x29482A68, 0x29482A6C, 0x29482A70, 0x29482A74, 0x29482A78, 0x29482A7C,
			0x29482A80, 0x29482A84, 0x29482A88, 0x29482A8C, 0x29482A90, 0x29482A94, 0x29482A98, 0x29482A9C,
			0x29482AA0, 0x29482AA4, 0x29482AA8, 0x29482AAC, 0x29482AB0, 0x29482AB4, 0x29482AB8, 0x29482ABC,
			0x29482AC0, 0x29482AC4, 0x29482AC8, 0x29482ACC, 0x29482AD0, 0x29482AD4, 0x29482AD8, 0x29482ADC,
			0x29482AE0, 0x29482AE4, 0x29482AE8, 0x29482AEC, 0x29482AF0, 0x29482AF4, 0x29482AF8, 0x29482AFC,
			0x29482B00,
		},
	},
	{
		{
			0x29582A00, 0x29582A04, 0x29582A08, 0x29582A0C, 0x29582A10, 0x29582A14, 0x29582A18, 0x29582A1C,
			0x29582A20, 0x29582A24, 0x29582A28, 0x29582A2C, 0x29582A30, 0x29582A34, 0x29582A38, 0x29582A3C,
			0x29582A40, 0x29582A44, 0x29582A48, 0x29582A4C, 0x29582A50, 0x29582A54, 0x29582A58, 0x29582A5C,
			0x29582A60, 0x29582A64, 0x29582A68, 0x29582A6C, 0x29582A70, 0x29582A74, 0x29582A78, 0x29582A7C,
			0x29582A80, 0x29582A84, 0x29582A88, 0x29582A8C, 0x29582A90, 0x29582A94, 0x29582A98, 0x29582A9C,
			0x29582AA0, 0x29582AA4, 0x29582AA8, 0x29582AAC, 0x29582AB0, 0x29582AB4, 0x29582AB8, 0x29582ABC,
			0x29582AC0, 0x29582AC4, 0x29582AC8, 0x29582ACC, 0x29582AD0, 0x29582AD4, 0x29582AD8, 0x29582ADC,
			0x29582AE0, 0x29582AE4, 0x29582AE8, 0x29582AEC, 0x29582AF0, 0x29582AF4, 0x29582AF8, 0x29582AFC,
			0x29582B00,
		},
	},
	{
		{
			0x29682A00, 0x29682A04, 0x29682A08, 0x29682A0C, 0x29682A10, 0x29682A14, 0x29682A18, 0x29682A1C,
			0x29682A20, 0x29682A24, 0x29682A28, 0x29682A2C, 0x29682A30, 0x29682A34, 0x29682A38, 0x29682A3C,
			0x29682A40, 0x29682A44, 0x29682A48, 0x29682A4C, 0x29682A50, 0x29682A54, 0x29682A58, 0x29682A5C,
			0x29682A60, 0x29682A64, 0x29682A68, 0x29682A6C, 0x29682A70, 0x29682A74, 0x29682A78, 0x29682A7C,
			0x29682A80, 0x29682A84, 0x29682A88, 0x29682A8C, 0x29682A90, 0x29682A94, 0x29682A98, 0x29682A9C,
			0x29682AA0, 0x29682AA4, 0x29682AA8, 0x29682AAC, 0x29682AB0, 0x29682AB4, 0x29682AB8, 0x29682ABC,
			0x29682AC0, 0x29682AC4, 0x29682AC8, 0x29682ACC, 0x29682AD0, 0x29682AD4, 0x29682AD8, 0x29682ADC,
			0x29682AE0, 0x29682AE4, 0x29682AE8, 0x29682AEC, 0x29682AF0, 0x29682AF4, 0x29682AF8, 0x29682AFC,
			0x29682B00,
		},
	},
};
static const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR	S_G_IM_B2R_KNEE_TBL_B_ADDR[3] = {
	{
		{
			0x29482C00, 0x29482C04, 0x29482C08, 0x29482C0C, 0x29482C10, 0x29482C14, 0x29482C18, 0x29482C1C,
			0x29482C20, 0x29482C24, 0x29482C28, 0x29482C2C, 0x29482C30, 0x29482C34, 0x29482C38, 0x29482C3C,
			0x29482C40, 0x29482C44, 0x29482C48, 0x29482C4C, 0x29482C50, 0x29482C54, 0x29482C58, 0x29482C5C,
			0x29482C60, 0x29482C64, 0x29482C68, 0x29482C6C, 0x29482C70, 0x29482C74, 0x29482C78, 0x29482C7C,
			0x29482C80, 0x29482C84, 0x29482C88, 0x29482C8C, 0x29482C90, 0x29482C94, 0x29482C98, 0x29482C9C,
			0x29482CA0, 0x29482CA4, 0x29482CA8, 0x29482CAC, 0x29482CB0, 0x29482CB4, 0x29482CB8, 0x29482CBC,
			0x29482CC0, 0x29482CC4, 0x29482CC8, 0x29482CCC, 0x29482CD0, 0x29482CD4, 0x29482CD8, 0x29482CDC,
			0x29482CE0, 0x29482CE4, 0x29482CE8, 0x29482CEC, 0x29482CF0, 0x29482CF4, 0x29482CF8, 0x29482CFC,
			0x29482D00,
		},
	},
	{
		{
			0x29582C00, 0x29582C04, 0x29582C08, 0x29582C0C, 0x29582C10, 0x29582C14, 0x29582C18, 0x29582C1C,
			0x29582C20, 0x29582C24, 0x29582C28, 0x29582C2C, 0x29582C30, 0x29582C34, 0x29582C38, 0x29582C3C,
			0x29582C40, 0x29582C44, 0x29582C48, 0x29582C4C, 0x29582C50, 0x29582C54, 0x29582C58, 0x29582C5C,
			0x29582C60, 0x29582C64, 0x29582C68, 0x29582C6C, 0x29582C70, 0x29582C74, 0x29582C78, 0x29582C7C,
			0x29582C80, 0x29582C84, 0x29582C88, 0x29582C8C, 0x29582C90, 0x29582C94, 0x29582C98, 0x29582C9C,
			0x29582CA0, 0x29582CA4, 0x29582CA8, 0x29582CAC, 0x29582CB0, 0x29582CB4, 0x29582CB8, 0x29582CBC,
			0x29582CC0, 0x29582CC4, 0x29582CC8, 0x29582CCC, 0x29582CD0, 0x29582CD4, 0x29582CD8, 0x29582CDC,
			0x29582CE0, 0x29582CE4, 0x29582CE8, 0x29582CEC, 0x29582CF0, 0x29582CF4, 0x29582CF8, 0x29582CFC,
			0x29582D00,
		},
	},
	{
		{
			0x29682C00, 0x29682C04, 0x29682C08, 0x29682C0C, 0x29682C10, 0x29682C14, 0x29682C18, 0x29682C1C,
			0x29682C20, 0x29682C24, 0x29682C28, 0x29682C2C, 0x29682C30, 0x29682C34, 0x29682C38, 0x29682C3C,
			0x29682C40, 0x29682C44, 0x29682C48, 0x29682C4C, 0x29682C50, 0x29682C54, 0x29682C58, 0x29682C5C,
			0x29682C60, 0x29682C64, 0x29682C68, 0x29682C6C, 0x29682C70, 0x29682C74, 0x29682C78, 0x29682C7C,
			0x29682C80, 0x29682C84, 0x29682C88, 0x29682C8C, 0x29682C90, 0x29682C94, 0x29682C98, 0x29682C9C,
			0x29682CA0, 0x29682CA4, 0x29682CA8, 0x29682CAC, 0x29682CB0, 0x29682CB4, 0x29682CB8, 0x29682CBC,
			0x29682CC0, 0x29682CC4, 0x29682CC8, 0x29682CCC, 0x29682CD0, 0x29682CD4, 0x29682CD8, 0x29682CDC,
			0x29682CE0, 0x29682CE4, 0x29682CE8, 0x29682CEC, 0x29682CF0, 0x29682CF4, 0x29682CF8, 0x29682CFC,
			0x29682D00,
		},
	},
};

static const T_IM_B2R_CTRL_RDMA_OFST_ADDR	S_G_IM_B2R_OFST_ADDR[3] = {
	{
		0x28412040, 0x28412044,
	},
	{
		0x28512040, 0x28512044,
	},
	{
		0x28612040, 0x28612044,
	},
};

static const T_IM_B2R_CTRL_RDMA_WB_SLOPE_ADDR	S_G_IM_B2R_WB_SLOPE_ADDR[3] = {
	{
		0x28412054, 0x28412058, 0x2841205C,
	},
	{
		0x28512054, 0x28512058, 0x2851205C,
	},
	{
		0x28612054, 0x28612058, 0x2861205C,
	},
};

static const T_IM_B2R_CTRL_RDMA_WB_CLIP_ADDR	S_G_IM_B2R_WB_CLIP_ADDR[3] = {
	{
		0x28412060, 0x28412064,
	},
	{
		0x28512060, 0x28512064,
	},
	{
		0x28612060, 0x28612064,
	},
};

static const T_IM_B2R_CTRL_RDMA_SENSITIVITY_ADDR	S_G_IM_B2R_SENSITIVITY_ADDR[3] = {
	{
		0x28412080, 0x28412084, 0x28412088, 0x2841208C, 0x28412090,
	},
	{
		0x28512080, 0x28512084, 0x28512088, 0x2851208C, 0x28512090,
	},
	{
		0x28612080, 0x28612084, 0x28612088, 0x2861208C, 0x28612090,
	},
};

static const T_IM_B2R_CTRL_RDMA_HPF_ADDR	S_G_IM_B2R_HPF_ADDR[3] = {
	{
		0x28412100, 0x28412110, 0x28412114, 0x28412118, 0x2841211C, 0x28412120, 0x28412124, 0x28412128,
		0x2841212C, 0x28412130, 0x28412134, 0x28412138, 0x2841213C, 0x28412140, 0x28412144, 0x28412148,
		0x28412150, 0x28412154, 0x28412158, 0x2841215C, 0x28412160, 0x28412168, 0x2841216C, 0x28412170,
		0x28412174, 0x28412178, 0x2841217C, 0x28412180, 0x28412184, 0x28412188, 0x2841218C, 0x28412190,
		0x28412194, 0x28412198, 0x2841219C, 0x284121A0, 0x284121A4, 0x284121A8, 0x284121AC, 0x284121B0,
	},
	{
		0x28512100, 0x28512110, 0x28512114, 0x28512118, 0x2851211C, 0x28512120, 0x28512124, 0x28512128,
		0x2851212C, 0x28512130, 0x28512134, 0x28512138, 0x2851213C, 0x28512140, 0x28512144, 0x28512148,
		0x28512150, 0x28512154, 0x28512158, 0x2851215C, 0x28512160, 0x28512168, 0x2851216C, 0x28512170,
		0x28512174, 0x28512178, 0x2851217C, 0x28512180, 0x28512184, 0x28512188, 0x2851218C, 0x28512190,
		0x28512194, 0x28512198, 0x2851219C, 0x285121A0, 0x285121A4, 0x285121A8, 0x285121AC, 0x285121B0,
	},
	{
		0x28612100, 0x28612110, 0x28612114, 0x28612118, 0x2861211C, 0x28612120, 0x28612124, 0x28612128,
		0x2861212C, 0x28612130, 0x28612134, 0x28612138, 0x2861213C, 0x28612140, 0x28612144, 0x28612148,
		0x28612150, 0x28612154, 0x28612158, 0x2861215C, 0x28612160, 0x28612168, 0x2861216C, 0x28612170,
		0x28612174, 0x28612178, 0x2861217C, 0x28612180, 0x28612184, 0x28612188, 0x2861218C, 0x28612190,
		0x28612194, 0x28612198, 0x2861219C, 0x286121A0, 0x286121A4, 0x286121A8, 0x286121AC, 0x286121B0,
	},
};
#endif	// CO_DDIM_UTILITY_USE

#ifndef CO_B2R_RDMA_ON
static volatile struct io_b2r_sram* S_G_IM_IO_B2R_TBL_PTR[D_IM_B2R_PIPE_MAX] = { &IO_B2R_TBL_P1, &IO_B2R_TBL_P2, &IO_B2R_TBL_P3 };
#endif	// CO_B2R_RDMA_ON

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_B2R_RDMA_ON
static VOID imB2rStartRdma( T_IM_RDMA_CTRL* ctrl );
static VOID imB2rSetRdmaValDekneeTable( UCHAR pipe_no, const USHORT* const src_tbl );
static VOID imB2rSetRdmaValKneeTable( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const UCHAR* const src_tbl );
static VOID imB2rSetRdmaValOffsetCtrl( UCHAR pipe_no, const T_IM_B2R_OFS* const ofs );
static VOID imB2rSetRdmaValWbSlopeCtrl( UCHAR pipe_no, UCHAR slope_gain_enable, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color );
static VOID imB2rSetRdmaValWbClipCtrl( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color );
static VOID imB2rSetRdmaValSensitivityCtrl( UCHAR pipe_no, const T_IM_B2R_CTRL_ADIP* const b2r_ctrl_adip );
#endif	// CO_B2R_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/

static void im_b2r3_constructor(ImB2r3 *self)
{
	//ImB2r3Private *priv = IM_B2R3_GET_PRIVATE(self);
}

static void im_b2r3_destructor(ImB2r3 *self)
{
	//ImB2r3Private *priv = IM_B2R3_GET_PRIVATE(self);
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_B2R_RDMA_ON
static VOID imB2rStartRdma( T_IM_RDMA_CTRL* ctrl )
{
	INT32 ercd;

	ercd = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_USER_SEM_WAIT_FEVR, ctrl, E_IM_RDMA_INT_MODE_OR );

	if( ercd != D_IM_RDMA_OK ){
		Ddim_Print(( "imB2rStartRdma error. %x\n", ercd ));
	}
}

VOID imB2rSetRdmaValDekneeTable( UCHAR pipe_no, const USHORT* const src_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_DEKNEE_TBL_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)src_tbl;
	imB2rStartRdma( &rdma_ctrl );
}

static VOID imB2rSetRdmaValKneeTable( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const UCHAR* const src_tbl )
{
	T_IM_RDMA_CTRL rdma_ctrl = {
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	switch( tbl_type ){
		case E_B2R_RGBTBL_G:
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_KNEE_TBL_G_ADDR[pipe_no]);
			break;
		case E_B2R_RGBTBL_B:
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_KNEE_TBL_B_ADDR[pipe_no]);
			break;
		default:	// E_B2R_RGBTBL_R
			rdma_ctrl.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_KNEE_TBL_R_ADDR[pipe_no]);
			break;
	}
	rdma_ctrl.transfer_byte = ( sizeof( U_IM_B2R_CTRL_RDMA_KNEE_TBL_VAL ) + 3 ) & 0xFFF8;
	rdma_ctrl.reg_data_top_addr = (ULONG)src_tbl;
	imB2rStartRdma( &rdma_ctrl );
}

static VOID imB2rSetRdmaValOffsetCtrl( UCHAR pipe_no, const T_IM_B2R_OFS* const ofs )
{
	T_IM_B2R_CTRL_RDMA_OFST_VAL ofst_val;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_OFST_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	ImB2r1_IM_B2R_SET_REG_SIGNED( ofst_val.OFSTRB, union io_b2r_ofstrb, OFSTRR, ofs->R );
	ImB2r1_IM_B2R_SET_REG_SIGNED( ofst_val.OFSTRB, union io_b2r_ofstrb, OFSTBB, ofs->B );
	ImB2r1_IM_B2R_SET_REG_SIGNED( ofst_val.OFSTG,  union io_b2r_ofstg,  OFSTGR, ofs->Gr );
	ImB2r1_IM_B2R_SET_REG_SIGNED( ofst_val.OFSTG,  union io_b2r_ofstg,  OFSTGB, ofs->Gb );

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_OFST_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&ofst_val;
	imB2rStartRdma( &rdma_ctrl );
}

static VOID imB2rSetRdmaValWbSlopeCtrl( UCHAR pipe_no, UCHAR slope_gain_enable, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color )
{
	T_IM_B2R_CTRL_RDMA_WB_SLOPE_VAL slope_val;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_WB_SLOPE_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	slope_val.WBHCTL.bit.WBHCEN = slope_gain_enable;
	slope_val.WBSLP.bit.WBSLPRR = b2r_bay_color->R;
	slope_val.WBSLP.bit.WBSLPBB = b2r_bay_color->B;
	slope_val.WBSLP.bit.WBSLPGR = b2r_bay_color->Gr;
	slope_val.WBSLP.bit.WBSLPGB = b2r_bay_color->Gb;

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_WB_SLOPE_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&slope_val;
	imB2rStartRdma( &rdma_ctrl );
}

static VOID imB2rSetRdmaValWbClipCtrl( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color )
{
	T_IM_B2R_CTRL_RDMA_WB_CLIP_VAL clip_val;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_WB_CLIP_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	clip_val.WBLVRB.bit.WBLVRR = b2r_bay_color->R;
	clip_val.WBLVRB.bit.WBLVBB = b2r_bay_color->B;
	clip_val.WBLVGR.bit.WBLVGR = b2r_bay_color->Gr;
	clip_val.WBLVGR.bit.WBLVGB = b2r_bay_color->Gb;

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_WB_CLIP_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&clip_val;
	imB2rStartRdma( &rdma_ctrl );
}

static VOID imB2rSetRdmaValSensitivityCtrl( UCHAR pipe_no, const T_IM_B2R_CTRL_ADIP* const b2r_ctrl_adip )
{
	T_IM_B2R_CTRL_RDMA_SENSITIVITY_VAL adip_val;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_SENSITIVITY_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	adip_val.SHARP.bit.SHARPA      = b2r_ctrl_adip->sharp_level_a;
	adip_val.SHARP.bit.SHARPB      = b2r_ctrl_adip->sharp_level_b;
	adip_val.SHARP.bit.SHARPC      = b2r_ctrl_adip->sharp_level_c;
	adip_val.AIRESY.bit.AIRESYA    = b2r_ctrl_adip->adj_feel_a;
	adip_val.AIRESY.bit.AIRESYB    = b2r_ctrl_adip->adj_feel_b;
	adip_val.LF.bit.LFSTR          = b2r_ctrl_adip->lf_strength;
	adip_val.LF.bit.LFTH           = b2r_ctrl_adip->lf_threshold;
	adip_val.CMC.bit.CMCSCL        = b2r_ctrl_adip->cmc_level;
	adip_val.CMC.bit.CMCLMT        = b2r_ctrl_adip->cmc_limit;
	adip_val.DIRRLITH.bit.DIRRLITH = b2r_ctrl_adip->dir_reliab_threshold;

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_SENSITIVITY_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&adip_val;
	imB2rStartRdma( &rdma_ctrl );
}

#endif	// CO_B2R_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
INT32 Im_B2R_Get_RdmaAddr_Deknee_Table( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_Deknee_Table error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_DEKNEE_TBL_ADDR[pipe_no]);

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_Knee_Table( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( tbl_type >=E_B2R_RGBTBL_MAX ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_Knee_Table error. tbl_type>=E_B2R_RGBTBL_MAX\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_Knee_Table error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	switch( tbl_type ){
		case E_B2R_RGBTBL_R:
			*addr = &(S_G_IM_B2R_KNEE_TBL_R_ADDR[pipe_no]);
			break;
		case E_B2R_RGBTBL_G:
			*addr = &(S_G_IM_B2R_KNEE_TBL_G_ADDR[pipe_no]);
			break;
		case E_B2R_RGBTBL_B:
			*addr = &(S_G_IM_B2R_KNEE_TBL_B_ADDR[pipe_no]);
			break;
		default:
			break;
	}

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_Offset_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_OFST_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_Offset_Cntl error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_OFST_ADDR[pipe_no]);

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_WB_Slope_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_WB_SLOPE_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_WB_Slope_Cntl error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_WB_SLOPE_ADDR[pipe_no]);

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_WB_Clip_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_WB_CLIP_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_WB_Clip_Cntl error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_WB_CLIP_ADDR[pipe_no]);

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_Sensitivity_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_SENSITIVITY_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_Sensitivity_Cntl error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_SENSITIVITY_ADDR[pipe_no]);

	return D_DDIM_OK;
}

INT32 Im_B2R_Get_RdmaAddr_HPF_Cntl( UCHAR pipe_no, const T_IM_B2R_CTRL_RDMA_HPF_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Get_RdmaAddr_HPF_Cntl error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	*addr = &(S_G_IM_B2R_HPF_ADDR[pipe_no]);

	return D_DDIM_OK;
}
#endif	// CO_DDIM_UTILITY_USE

/* Set Bayer Deknee table.
 */
INT32 Im_B2R_Set_Deknee_Table( UCHAR pipe_no, const USHORT* const src_tbl )
{
#ifndef CO_B2R_RDMA_ON
	UINT32 loop_cnt;
#endif	// CO_B2R_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(src_tbl == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_RGBDeknee_Table error. src_tbl = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_Deknee_Table error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = Im_B2R_Set_DekneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_ON, ImB2r_D_IM_B2R_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_B2R_RDMA_ON
		imB2rSetRdmaValDekneeTable( pipe_no, src_tbl );
#else	// CO_B2R_RDMA_ON
		Im_B2R_On_Hclk( pipe_no );

		for( loop_cnt = 0; loop_cnt < ImB2r_D_IM_B2R_TABLE_MAX_BAYER_DEKNEE; loop_cnt++ ) {
			S_G_IM_IO_B2R_TBL_PTR[pipe_no]->DKNTBL.hword[loop_cnt] = src_tbl[loop_cnt];
		}

		Im_B2R_Off_Hclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

		ercd = Im_B2R_Set_DekneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_OFF, ImB2r_D_IM_B2R_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}


/* Set RGB Knee table.
 */
INT32 Im_B2R_Set_Knee_Table( UCHAR pipe_no, E_B2R_RGBTBL tbl_type, const UCHAR* const src_tbl )
{
#ifndef CO_B2R_RDMA_ON
	UINT32 loop_cnt;
	volatile UCHAR* dst_tbl;
#endif	// CO_B2R_RDMA_ON
	INT32  ercd;

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(src_tbl == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_Knee_Table error. src_tbl = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_Knee_Table error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

	while( 1 ) {
		ercd = Im_B2R_Set_RGB_KneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_ON, ImB2r_D_IM_B2R_WAIT_ON );
		if( ercd != D_DDIM_OK ) {
			break;
		}

#ifdef CO_B2R_RDMA_ON
		imB2rSetRdmaValKneeTable( pipe_no, tbl_type, src_tbl );
#else
		Im_B2R_On_Hclk( pipe_no );

		switch( tbl_type ) {
			case E_B2R_RGBTBL_G:
				dst_tbl = S_G_IM_IO_B2R_TBL_PTR[pipe_no]->KNETBLG.byte;
				break;
			case E_B2R_RGBTBL_B:
				dst_tbl = S_G_IM_IO_B2R_TBL_PTR[pipe_no]->KNETBLB.byte;
				break;
			default:	// E_B2R_RGBTBL_R
				dst_tbl = S_G_IM_IO_B2R_TBL_PTR[pipe_no]->KNETBLR.byte;
				break;
		}
		for( loop_cnt = 0; loop_cnt < ImB2r_D_IM_B2R_TABLE_MAX_RGB_KNEE; loop_cnt++ ) {
			dst_tbl[loop_cnt] = src_tbl[loop_cnt];
		}

		Im_B2R_Off_Hclk( pipe_no );
#endif

		ercd = Im_B2R_Set_RGB_KneeAccessEnable( pipe_no, ImB2r_D_IM_B2R_ENABLE_OFF, ImB2r_D_IM_B2R_WAIT_OFF );
		if( ercd != D_DDIM_OK ) {
			break;
		}

		ercd = D_DDIM_OK;
		break;
	}

	return ercd;
}

/* Offset Control
 */
INT32 Im_B2R_Set_Offset( UCHAR pipe_no, const T_IM_B2R_OFS* const ofs )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if( ofs == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_Offset error. ofs = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_Offset error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

#ifdef CO_B2R_RDMA_ON
	imB2rSetRdmaValOffsetCtrl( pipe_no, ofs );
#else	// CO_B2R_RDMA_ON
	Im_B2R_On_Pclk( pipe_no );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.OFSTRB, union io_b2r_ofstrb, OFSTRR, ofs->R );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.OFSTRB, union io_b2r_ofstrb, OFSTBB, ofs->B );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.OFSTG,  union io_b2r_ofstg,  OFSTGR, ofs->Gr );
	ImB2r1_IM_B2R_SET_REG_SIGNED( im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.OFSTG,  union io_b2r_ofstg,  OFSTGB, ofs->Gb );
	Im_B2R_Off_Pclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

	return D_DDIM_OK;
}

/* WB Gain Saturation compensation control
 */
INT32 Im_B2R_Set_WB_Slope_Gain( UCHAR pipe_no, UCHAR slope_gain_enable, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(b2r_bay_color == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_WB_Slope_Gain error. bay_color = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_WB_Slope_Gain error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

#ifdef CO_B2R_RDMA_ON
	imB2rSetRdmaValWbSlopeCtrl( pipe_no, slope_gain_enable, b2r_bay_color );
#else	// CO_B2R_RDMA_ON
	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBHCTL.bit.WBHCEN = slope_gain_enable;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBSLP.bit.WBSLPRR = b2r_bay_color->R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBSLP.bit.WBSLPBB = b2r_bay_color->B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBSLP.bit.WBSLPGR = b2r_bay_color->Gr;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBSLP.bit.WBSLPGB = b2r_bay_color->Gb;
	Im_B2R_Off_Pclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

	return D_DDIM_OK;
}

/* WB Clip Level control
 */
INT32 Im_B2R_Set_WB_Clip_Level( UCHAR pipe_no, const T_IM_B2R_BAYER_COLOR* const b2r_bay_color )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(b2r_bay_color == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Set_WB_Clip_Level error. b2r_bay_color = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Set_WB_Clip_Level error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

#ifdef CO_B2R_RDMA_ON
	imB2rSetRdmaValWbClipCtrl( pipe_no, b2r_bay_color );
#else	// CO_B2R_RDMA_ON
	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBLVRB.bit.WBLVRR = b2r_bay_color->R;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBLVRB.bit.WBLVBB = b2r_bay_color->B;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBLVGR.bit.WBLVGR = b2r_bay_color->Gr;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.OFG.WBLVGR.bit.WBLVGB = b2r_bay_color->Gb;
	Im_B2R_Off_Pclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

	return D_DDIM_OK;
}

/* Sensitivity(ADIP) Control
 */
INT32 Im_B2R_Ctrl_Sensitivity( UCHAR pipe_no, const T_IM_B2R_CTRL_ADIP* const b2r_ctrl_adip )
{
	ImB2r2*	imB2r2=im_b2r2_get();

#ifdef CO_PARAM_CHECK
	// check on input pointer
	if(b2r_ctrl_adip == NULL) {
		// Parameter setting error
		Ddim_Assertion(("Im_B2R_Ctrl_Sensitivity error. b2r_ctrl_adip = NULL\n"));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
	if( pipe_no > ImB2r_D_IM_B2R_PIPE12 ){
		Ddim_Assertion(( "Im_B2R_Ctrl_Sensitivity error. pipe_no>ImB2r_D_IM_B2R_PIPE12\n" ));
		return ImB2r_D_IM_B2R_PARAM_ERROR;
	}
#endif

#ifdef CO_B2R_RDMA_ON
	imB2rSetRdmaValSensitivityCtrl( pipe_no, b2r_ctrl_adip );
#else	// CO_B2R_RDMA_ON
	// It sets it to the register at once.
	Im_B2R_On_Pclk( pipe_no );
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.SHARP.bit.SHARPA      = b2r_ctrl_adip->sharp_level_a;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.SHARP.bit.SHARPB      = b2r_ctrl_adip->sharp_level_b;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.SHARP.bit.SHARPC      = b2r_ctrl_adip->sharp_level_c;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.AIRESY.bit.AIRESYA    = b2r_ctrl_adip->adj_feel_a;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.AIRESY.bit.AIRESYB    = b2r_ctrl_adip->adj_feel_b;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.LF.bit.LFSTR          = b2r_ctrl_adip->lf_strength;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.LF.bit.LFTH           = b2r_ctrl_adip->lf_threshold;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.CMC.bit.CMCSCL        = b2r_ctrl_adip->cmc_level;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.CMC.bit.CMCLMT        = b2r_ctrl_adip->cmc_limit;
	im_b2r2_get_g_im_io_b2r_reg_ptr(imB2r2,pipe_no)->F_B2R.CIA.DIRRLITH.bit.DIRRLITH = b2r_ctrl_adip->dir_reliab_threshold;
	Im_B2R_Off_Pclk( pipe_no );
#endif	// CO_B2R_RDMA_ON

	return D_DDIM_OK;
}

//为了平衡代码量，把调用他的公有函数放到别的文件，这个私有函数需要转为公有
#ifdef CO_DDIM_UTILITY_USE
#ifdef CO_B2R_RDMA_ON
VOID im_b2r_set_rdma_val_hpf_ctrl( UCHAR pipe_no, const T_IM_B2R_CTRL_HPF* const b2r_ctrl_hpf )
{
	T_IM_B2R_CTRL_RDMA_HPF_VAL hpf_val;
	T_IM_RDMA_CTRL rdma_ctrl = {
		.reg_addr_tbl_addr = (ULONG)&(S_G_IM_B2R_HPF_ADDR[pipe_no]),
		.req_threshold = E_IM_RDMA_PRCH_CNT_NOLIMIT,
		.pCallBack = NULL,
	};

	hpf_val.HFACTL.bit.HFEEN  = b2r_ctrl_hpf->hpf_enable;
	hpf_val.HFACTL.bit.HFAFEN = b2r_ctrl_hpf->flat_ctrl_enable;
	hpf_val.HFACTL.bit.HFAYEN = b2r_ctrl_hpf->y_ctrl_enable;
	hpf_val.HFK.bit.HFK0      = b2r_ctrl_hpf->hpf_k[0];
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK1, b2r_ctrl_hpf->hpf_k[1] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK2, b2r_ctrl_hpf->hpf_k[2] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK3, b2r_ctrl_hpf->hpf_k[3] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK4, b2r_ctrl_hpf->hpf_k[4] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK5, b2r_ctrl_hpf->hpf_k[5] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK6, b2r_ctrl_hpf->hpf_k[6] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK7, b2r_ctrl_hpf->hpf_k[7] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK8, b2r_ctrl_hpf->hpf_k[8] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFK, union io_b2r_hfk, HFK9, b2r_ctrl_hpf->hpf_k[9] );
	hpf_val.HFEFCLP.bit.HFEFCLPP = b2r_ctrl_hpf->hpf_level_clip_p;
	hpf_val.HFEFCLP.bit.HFEFCLPM = b2r_ctrl_hpf->hpf_level_clip_m;
	hpf_val.HFAFST.bit.HFAFSL    = b2r_ctrl_hpf->flat_scale;
	hpf_val.HFAFST.bit.HFAFTH    = b2r_ctrl_hpf->flat_threshold;
	hpf_val.HFAFGU.bit.HFAFGU    = b2r_ctrl_hpf->flat_gain_limit;
	hpf_val.HFAFCLP.bit.HFAFCLPP = b2r_ctrl_hpf->flat_level_clip_p;
	hpf_val.HFAFCLP.bit.HFAFCLPM = b2r_ctrl_hpf->flat_level_clip_m;
	hpf_val.HFAYC.bit.HFAYC00    = b2r_ctrl_hpf->y_convert_coef[0];
	hpf_val.HFAYC.bit.HFAYC01    = b2r_ctrl_hpf->y_convert_coef[1];
	hpf_val.HFAYC.bit.HFAYC02    = b2r_ctrl_hpf->y_convert_coef[2];
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC10, b2r_ctrl_hpf->y_convert_coef[3] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC11, b2r_ctrl_hpf->y_convert_coef[4] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC12, b2r_ctrl_hpf->y_convert_coef[5] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC20, b2r_ctrl_hpf->y_convert_coef[6] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC21, b2r_ctrl_hpf->y_convert_coef[7] );
	ImB2r1_IM_B2R_SET_REG_SIGNED_A( hpf_val.HFAYC, union io_b2r_hfayc, HFAYC22, b2r_ctrl_hpf->y_convert_coef[8] );
	hpf_val.HFAYOF.bit.HFAYOF_0 = b2r_ctrl_hpf->y_ctrl_offset[0];
	hpf_val.HFAYOF.bit.HFAYOF_1 = b2r_ctrl_hpf->y_ctrl_offset[1];
	hpf_val.HFAYOF.bit.HFAYOF_2 = b2r_ctrl_hpf->y_ctrl_offset[2];
	hpf_val.HFAYOF.bit.HFAYOF_3 = b2r_ctrl_hpf->y_ctrl_offset[3];
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFAYGA, union io_b2r_hfayga, HFAYGA_0, b2r_ctrl_hpf->y_ctrl_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFAYGA, union io_b2r_hfayga, HFAYGA_1, b2r_ctrl_hpf->y_ctrl_gain[1] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFAYGA, union io_b2r_hfayga, HFAYGA_2, b2r_ctrl_hpf->y_ctrl_gain[2] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFAYGA, union io_b2r_hfayga, HFAYGA_3, b2r_ctrl_hpf->y_ctrl_gain[3] );
	hpf_val.HFAYBD.bit.HFAYBD_0     = b2r_ctrl_hpf->y_ctrl_border[0];
	hpf_val.HFAYBD.bit.HFAYBD_1     = b2r_ctrl_hpf->y_ctrl_border[1];
	hpf_val.HFAYBD.bit.HFAYBD_2     = b2r_ctrl_hpf->y_ctrl_border[2];
	hpf_val.HFAYBD.bit.HFAYBD_3     = b2r_ctrl_hpf->y_ctrl_border[3];
	hpf_val.HFAYDIV.bit.HFAYDIV1    = b2r_ctrl_hpf->y_ctrl_gain_posi_dec1;
	hpf_val.HFAYDIV.bit.HFAYDIV2    = b2r_ctrl_hpf->y_ctrl_gain_posi_dec2;
	hpf_val.HFAYCLP.bit.HFAYCLPP    = b2r_ctrl_hpf->y_ctrl_level_clip_p;
	hpf_val.HFAYCLP.bit.HFAYCLPM    = b2r_ctrl_hpf->y_ctrl_level_clip_m;
	hpf_val.HFACOR.bit.HFACORP      = b2r_ctrl_hpf->y_ctrl_cor_p;
	hpf_val.HFACOR.bit.HFACORM      = b2r_ctrl_hpf->y_ctrl_cor_m;
	hpf_val.HFACLP.bit.HFACLPR      = b2r_ctrl_hpf->hpf_add_level_clip_r;
	hpf_val.HFACLP.bit.HFACLPG      = b2r_ctrl_hpf->hpf_add_level_clip_g;
	hpf_val.HFACLP.bit.HFACLPB      = b2r_ctrl_hpf->hpf_add_level_clip_b;
	hpf_val.HFACRVCTL.bit.HFACAE    = b2r_ctrl_hpf->area_a_enable;
	hpf_val.HFACRVCTL.bit.HFACBE    = b2r_ctrl_hpf->area_b_enable;
	hpf_val.HFACRVCTL.bit.HFACRVMRG = b2r_ctrl_hpf->area_marge_method;
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFX1, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus1_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFY1, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus1_y );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFX2, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus2_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVAFX, union io_b2r_hfacvafx, HFACRVAFY2, b2r_ctrl_hpf->area_a_ctrl.ellipse_area_focus2_y );
	hpf_val.HFACRVASCLOF.bit.HFACRVASCLOF1 = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_offset;
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACRVASCLGA, union io_b2r_hfacrvasclga, HFACRVASCLGA_0, b2r_ctrl_hpf->area_a_ctrl.c_area_scale_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACRVASCLGA, union io_b2r_hfacrvasclga, HFACRVASCLGA_1, b2r_ctrl_hpf->area_a_ctrl.c_area_scale_gain[1] );
	hpf_val.HFACRVASCLBD.bit.HFACRVASCLBD1 = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_border;
	hpf_val.HFACRVASCLCP.bit.HFACRVASCLCPL = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_clip_l;
	hpf_val.HFACRVASCLCP.bit.HFACRVASCLCPH = b2r_ctrl_hpf->area_a_ctrl.c_area_scale_clip_h;
	hpf_val.HFAYASCLGA.bit.HFAYASCLGA_0    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_gain[0];
	hpf_val.HFAYASCLGA.bit.HFAYASCLGA_1    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_gain[1];
	hpf_val.HFAYASCLBD.bit.HFAYASCLBD_0    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_border[0];
	hpf_val.HFAYASCLBD.bit.HFAYASCLBD_1    = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_border[1];
	hpf_val.HFAYASCLCLP.bit.HFAYASCLCLPL   = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_clip_l;
	hpf_val.HFAYASCLCLP.bit.HFAYASCLCLPH   = b2r_ctrl_hpf->area_a_ctrl.y_area_scale_clip_h;
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFX1, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus1_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFY1, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus1_y );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFX2, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus2_x );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACVBFX, union io_b2r_hfacvbfx, HFACRVBFY2, b2r_ctrl_hpf->area_b_ctrl.ellipse_area_focus2_y );
	hpf_val.HFACRVBSCLOF.bit.HFACRVBSCLOF1 = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_offset;
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACRVBSCLGA, union io_b2r_hfacrvbsclga, HFACRVBSCLGA_0, b2r_ctrl_hpf->area_b_ctrl.c_area_scale_gain[0] );
	ImB2r1_IM_B2R_SET_REG_SIGNED( hpf_val.HFACRVBSCLGA, union io_b2r_hfacrvbsclga, HFACRVBSCLGA_1, b2r_ctrl_hpf->area_b_ctrl.c_area_scale_gain[1] );
	hpf_val.HFACRVBSCLBD.bit.HFACRVBSCLBD1 = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_border;
	hpf_val.HFACRVBSCLCP.bit.HFACRVBSCLCPL = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_clip_l;
	hpf_val.HFACRVBSCLCP.bit.HFACRVBSCLCPH = b2r_ctrl_hpf->area_b_ctrl.c_area_scale_clip_h;
	hpf_val.HFAYBSCLGA.bit.HFAYBSCLGA_0    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_gain[0];
	hpf_val.HFAYBSCLGA.bit.HFAYBSCLGA_1    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_gain[1];
	hpf_val.HFAYBSCLBD.bit.HFAYBSCLBD_0    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_border[0];
	hpf_val.HFAYBSCLBD.bit.HFAYBSCLBD_1    = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_border[1];
	hpf_val.HFAYBSCLCLP.bit.HFAYBSCLCLPL   = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_clip_l;
	hpf_val.HFAYBSCLCLP.bit.HFAYBSCLCLPH   = b2r_ctrl_hpf->area_b_ctrl.y_area_scale_clip_h;

	rdma_ctrl.transfer_byte = sizeof( T_IM_B2R_CTRL_RDMA_HPF_VAL );
	rdma_ctrl.reg_data_top_addr = (ULONG)&hpf_val;
	imB2rStartRdma( &rdma_ctrl );
}
#endif	// CO_B2R_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

ImB2r3 *im_b2r3_get()
{
	static ImB2r3 *imB2r3 = NULL;
	if(!imB2r3)
		imB2r3 = k_object_new_with_private(IM_TYPE_B2R3,sizeof(ImB2r3Private));
	return imB2r3;
}

