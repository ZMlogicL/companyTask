/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro17Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro17print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro17Print, im_pro_1_7_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_7_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro17PrintPrivate, IM_TYPE_PRO_1_7_PRINT))


struct _ImPro17PrintPrivate
{


};


/**
 * IMPL
 */
static void im_pro_1_7_print_constructor(ImPro17Print *self)
{
	ImPro17PrintPrivate *priv = IM_PRO_1_7_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_7_print_destructor(ImPro17Print *self)
{
	ImPro17PrintPrivate *priv = IM_PRO_1_7_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


ImPro17Print* im_pro_1_7_print_new(void)
{
	ImPro17Print* self = k_object_new_with_private(IM_TYPE_PRO_1_7_PRINT, sizeof(ImPro17PrintPrivate));

	return self;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE


void im_pro_1_7_print_0(ImPro17Print *self,const char* string, kuchar ch, kuchar paenTrg)
{
    if(((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdspaen.bit.paen != paenTrg) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LVDS_Set_PAEN(%u) %s result:paen (%u) lvdstrg(%u) paenTrg(%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdspaen.bit.paen, 
        ((AbsImProPrint*)self)->ioPro->sen.lvds[ch].lvdstrg.bit.lvdstrg, paenTrg))
    };  
}    

void im_pro_1_7_print_1(ImPro17Print *self,const char* string, T_IM_PRO_SENTOP_CPHY_DELAYLINE_MONITOR* status)
{
    if(status->delaylineMoni[0].phyCodeCp0 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni1.bit.phy0CodeCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy0CodeCp0 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[0].phyCodeCp0, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni1.bit.phy0CodeCp0))
    };  
        
    if(status->delaylineMoni[0].phyCodeCp1 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni2.bit.phy0CodeCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy0CodeCp1 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[0].phyCodeCp1, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni2.bit.phy0CodeCp1))
    };  
        
    if(status->delaylineMoni[0].phyCodeCp2 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni3.bit.phy0CodeCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy0CodeCp2 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[0].phyCodeCp2, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy0dlmoni.phy0dlmoni3.bit.phy0CodeCp2))
    };  
        
    if(status->delaylineMoni[1].phyCodeCp0 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni1.bit.phy1CodeCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy1CodeCp0 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[1].phyCodeCp0, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni1.bit.phy1CodeCp0))
    };  
        
    if(status->delaylineMoni[1].phyCodeCp1 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni2.bit.phy1CodeCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy1CodeCp1 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[1].phyCodeCp1, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni2.bit.phy1CodeCp1))
    };  
        
    if(status->delaylineMoni[1].phyCodeCp2 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni3.bit.phy1CodeCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy1CodeCp2 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[1].phyCodeCp2, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy1dlmoni.phy1dlmoni3.bit.phy1CodeCp2))
    };  
        
    if(status->delaylineMoni[2].phyCodeCp0 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni1.bit.phy2CodeCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy2CodeCp0 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[2].phyCodeCp0, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni1.bit.phy2CodeCp0))
    };  
        
    if(status->delaylineMoni[2].phyCodeCp1 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni2.bit.phy2CodeCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy2CodeCp1 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[2].phyCodeCp1, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni2.bit.phy2CodeCp1))
    };  
        
    if(status->delaylineMoni[2].phyCodeCp2 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni3.bit.phy2CodeCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy2CodeCp2 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[2].phyCodeCp2, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy2dlmoni.phy2dlmoni3.bit.phy2CodeCp2))
    };  
        
    if(status->delaylineMoni[3].phyCodeCp0 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni1.bit.phy3CodeCp0) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy3CodeCp0 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[3].phyCodeCp0, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni1.bit.phy3CodeCp0))
    };  
        
    if(status->delaylineMoni[3].phyCodeCp1 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni2.bit.phy3CodeCp1) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy3CodeCp1 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[3].phyCodeCp1, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni2.bit.phy3CodeCp1))
    };  
        
    if(status->delaylineMoni[3].phyCodeCp2 != ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni3.bit.phy3CodeCp2) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_DelayLine_Monitor() %s result:phy3CodeCp2 (%u) reg_val (%u)\n", string, 
        status->delaylineMoni[3].phyCodeCp2, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phy3dlmoni.phy3dlmoni3.bit.phy3CodeCp2))
    };  
}

void im_pro_1_7_print_2(ImPro17Print *self,const char* string, T_IM_PRO_SENTOP_CPHY_COMMON_IF_MONITOR* status)
{
    if(status->phy0_cdrmon != ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni1.bit.phy0Cdrmon) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_Common_If_Monitor() %s result:phy0Cdrmon (%llu) reg_val (%llu)\n", 
        string, status->phy0_cdrmon, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni1.bit.phy0Cdrmon))
    };  
        
    if(status->phy1_cdrmon != ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni2.bit.phy1Cdrmon) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_Common_If_Monitor() %s result:phy1Cdrmon (%llu) reg_val (%llu)\n", 
        string, status->phy1_cdrmon, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni2.bit.phy1Cdrmon))
    };  
        
    if(status->phy2_cdrmon != ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni3.bit.phy2Cdrmon) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_Common_If_Monitor() %s result:phy2Cdrmon (%llu) reg_val (%llu)\n", 
        string, status->phy2_cdrmon, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni3.bit.phy2Cdrmon))
    };  
        
    if(status->phy3_cdrmon != ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni4.bit.phy3Cdrmon) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_SENTOP_CPHY_Get_Common_If_Monitor() %s result:phy3Cdrmon (%llu) reg_val (%llu)\n", 
        string, status->phy3_cdrmon, 
        ((AbsImProPrint*)self)->ioPro->sen.sentop.phycmoni.phycmoni4.bit.phy3Cdrmon))
    };  
}
#endif //CO_CT_IM_PRO_DISABLE

ImPro17Print* im_pro_1_7_print_get(void)
{
	static ImPro17Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_7_PRINT, sizeof(ImPro17PrintPrivate));
	}

	return self;
}
