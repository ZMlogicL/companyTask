/*
*
*@Copyright(C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : ImPro5Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro5print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro5Print, im_pro_5_print,ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_5_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE((o), ImPro5PrintPrivate, IM_TYPE_PRO_5_PRINT))


struct _ImPro5PrintPrivate
{

};


/**
 *IMPL
 */
static void im_pro_5_print_constructor(ImPro5Print *self)
{
	ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_5_print_destructor(ImPro5Print *self)
{
	ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);
}


/**
 *PUBCLI
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_5_print_4(ImPro5Print *self, const char* string, kint32 ercd)
{
    ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);

    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Ctrl() result:org(%u)\n", 
        ((AbsImProPrint*)self)->ioPro->pas.pastop.pastopctl1.bit.org));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_PASTOP_Ctrl() error(not exist) ercd=0x%x\n", ercd));
    }
}

void im_pro_5_print_5(ImPro5Print *self, kint32 ercd)
{
    ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);

    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Start() result:spttrg(%u)\n", 
        ((AbsImProPrint*)self)->ioPro->pas.spt.spttrg.bit.spttrg));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Start() error(not exist) ercd=0x%x\n", ercd));
    }
}

void im_pro_5_print_6(ImPro5Print *self, kint32 ercd, kuchar force)
{
    ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);

    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Stop(%u) result:spttrg(%u)\n", force, 
        ((AbsImProPrint*)self)->ioPro->pas.spt.spttrg.bit.spttrg));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Stop(%u) error(not exist) ercd=0x%x\n", force, ercd));
    }
}

void im_pro_5_print_7(ImPro5Print *self, const char* string, kint32 ercd, TimproSptCtrl* ctrl)
{
    ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);

    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->pas.spt.spttbl.bit.spttbl != ctrl->tableSel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:spttbl(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.spttbl.bit.spttbl, ctrl->tableSel));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptbs.bit.sptbsh != ctrl->horizontalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptbsh(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptbs.bit.sptbsh, ctrl->horizontalPixel));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptbs.bit.sptbsv != ctrl->verticalPixel) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptbsv(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptbs.bit.sptbsv, ctrl->verticalPixel));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptbd.bit.sptbdm != ctrl->InverseBase) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptbdm(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptbd.bit.sptbdm, ctrl->InverseBase));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptbd.bit.sptbde != ctrl->InverseExponent) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptbde(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptbd.bit.sptbde, ctrl->InverseExponent));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptv.bit.sptv != ctrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptv(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptv.bit.sptv, ctrl->posY));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.spth.bit.spth != ctrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:spth(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.spth.bit.spth, ctrl->posX));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptvbc.bit.sptvbc != ctrl->vBlockSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptvbc(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptvbc.bit.sptvbc, ctrl->vBlockSize));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.spthbc.bit.spthbc != ctrl->hBlockSize) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:spthbc(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.spthbc.bit.spthbc, ctrl->hBlockSize));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptclp.bit.sptclph != ctrl->upperClipValue) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptclph(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptclp.bit.sptclph, ctrl->upperClipValue));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptclp.bit.sptclpl != ctrl->lowerClipValue) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptclpl(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptclp.bit.sptclpl, ctrl->lowerClipValue));
        }
        
        if(((AbsImProPrint*)self)->ioPro->pas.spt.sptnopv.bit.sptnopv != ctrl->correctionThroughVal){
            DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() result:sptnopv(%u)(%u)\n", 
            ((AbsImProPrint*)self)->ioPro->pas.spt.sptnopv.bit.sptnopv, ctrl->correctionThroughVal));
        }
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Ctrl() error(not exist) ercd=0x%x\n", ercd));
    }

}

void im_pro_5_print_8(ImPro5Print *self, kint32 ercd, kuchar paenTrg)
{
    ImPro5PrintPrivate *priv = IM_PRO_5_PRINT_GET_PRIVATE(self);

    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Set_PAEN(%u) result:paen(%u)\n", paenTrg, 
        ((AbsImProPrint*)self)->ioPro->pas.spt.sptpaen.bit.paen));
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Set_PAEN(%u) result:spttrg(%u)\n", paenTrg, 
        ((AbsImProPrint*)self)->ioPro->pas.spt.spttrg.bit.spttrg));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Set_PAEN() error(not exist) ercd=0x%x\n", ercd));
    }
}

void im_pro_5_print_9(ImPro5Print *self, const char* string, kint32 ercd, kint32 cmpErcd)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_SPT_Set_Table() API result(0x%x) memcmp result(0x%x)\n",ercd, cmpErcd));
}

void im_pro_5_10_Print(ImPro5Print *self, EImProSptTblSel tblSel, kint32 ercd, const TimproRdmaSptShdTblAddr** addr)
{
    if( ercd == DdimUserCustom_E_OK) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SPT_SHD_Tbl(%u) spttbl    reg_addr(0x%08lx)\n", 
                    tblSel,(kulong)(*addr)->spttbl));
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_SPT_SHD_Tbl(%u) error(not exist) ercd=0x%x\n", tblSel, ercd));
    }
}
#endif //CO_CT_IM_PRO_DISABLE

ImPro5Print* im_pro_5_print_new(void)
{
	ImPro5Print* self = k_object_new_with_private(IM_TYPE_PRO_5_PRINT, sizeof(ImPro5PrintPrivate));

	return self;
}

ImPro5Print* im_pro_5_print_get(void)
{
	static ImPro5Print* self = NULL;

	if(!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_5_PRINT, sizeof(ImPro5PrintPrivate));
	}

	return self;
}
