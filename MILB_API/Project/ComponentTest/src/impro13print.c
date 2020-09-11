/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro13Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro13print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro13Print, im_pro_1_3_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_3_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro13PrintPrivate, IM_TYPE_PRO_1_3_PRINT))


struct _ImPro13PrintPrivate
{


};


/**
 *IMPL
 */
static void im_pro_1_3_print_constructor(ImPro13Print *self)
{
	ImPro13PrintPrivate *priv = IM_PRO_1_3_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_3_print_destructor(ImPro13Print *self)
{
	ImPro13PrintPrivate *priv = IM_PRO_1_3_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *IMPL
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_3_print_0(ImPro13Print *self,const char* string, kuchar ch)
{
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivtrg.bit.ldivtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LDIV_Start(%u) %s result:trgr (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivtrg.bit.ldivtrg))}; 
}

void im_pro_1_3_print_1(ImPro13Print *self,const char* string, kuchar ch, kuchar force)
{
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivtrg.bit.ldivtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LDIV_Stop(%u, %u) %s result:trgr (%d)\n", 
        ch, force, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivtrg.bit.ldivtrg))}; 
}

void im_pro_1_3_print_2(ImPro13Print *self,const char* string, kuchar ch, TImProLdivCtrl* ldivCtrl)
{
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldstmd != ldivCtrl->mode) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldstmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldstmd, ldivCtrl->mode))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldipmd != ldivCtrl->ldipmd) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldipmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldipmd, ldivCtrl->ldipmd))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldvdmd != ldivCtrl->ldvdmd) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldvdmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldvdmd, ldivCtrl->ldvdmd))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldhdmd != ldivCtrl->hdInsertionEn) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldhdmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldhdmd, ldivCtrl->hdInsertionEn))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldmch != ldivCtrl->ldmch) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldmch (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldmch, ldivCtrl->ldmch))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.lddivmd != ldivCtrl->lddivmd) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:lddivmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.lddivmd, ldivCtrl->lddivmd))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldopmd != ldivCtrl->ldopmd) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_ctrl(%u) %s result:ldopmd (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivctl.bit.ldopmd, ldivCtrl->ldopmd))}; 
}                                                    

void im_pro_1_3_print_3(ImPro13Print *self,const char* string, kuchar ch, TImProLdivArea* ldivArea)
{
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivihw.bit.ldivihw != ldivArea->inWidth) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivihw (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivihw.bit.ldivihw, ldivArea->inWidth))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh_0 != ldivArea->outPosX[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivoh_0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh_0, ldivArea->outPosX[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh_1 != ldivArea->outPosX[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivoh_1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh1.bit.ldivoh_1, ldivArea->outPosX[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh_2 != ldivArea->outPosX[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivoh_2 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh_2, ldivArea->outPosX[2]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh_3 != ldivArea->outPosX[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivoh_3 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivoh.ldivoh2.bit.ldivoh_3, ldivArea->outPosX[3]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw_0 != ldivArea->outWidth[0]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivohw_0 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw_0, ldivArea->outWidth[0]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw_1 != ldivArea->outWidth[1]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivohw_1 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw1.bit.ldivohw_1, ldivArea->outWidth[1]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw_2 != ldivArea->outWidth[2]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivohw_2 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw_2, ldivArea->outWidth[2]))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw_3 != ldivArea->outWidth[3]) { 
        DriverCommon_DDIM_PRINT(("impro_sensldiv_set_area(%u) %s result:ldivohw_3 (%d) (%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivohw.ldivohw2.bit.ldivohw_3, ldivArea->outWidth[3]))}; 
}                                                    

void im_pro_1_3_print_4(ImPro13Print *self,const char* string, kuchar ch, kuchar paenTrg)
{
    if(((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivpaen.bit.ldpaen != paenTrg) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_LDIV_Set_PAEN(%u) %s result:ldpaen (%d) ldivtrg(%d) in(%d)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivpaen.bit.ldpaen, 
        ((AbsImProPrint*)self)->ioPro->sen.ldiv[ch].ldivtrg.bit.ldivtrg,paenTrg))}; 
}

void im_pro_1_3_print_5(ImPro13Print *self,const char* string, kuchar ch)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdtrg.bit.obdtrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Start(%u) blob_num:%u chNum:%u  %s result:obdtrg (%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdtrg.bit.obdtrg))}; 
}

void im_pro_1_3_print_6(ImPro13Print *self,const char* string, kuchar ch, kuchar force)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdtrg.bit.obdtrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Stop(%u, %u) blob_num:%u chNum:%u  %s result:obdtrg (%d)\n", 
        ch, force, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdtrg.bit.obdtrg))}; 
}

void im_pro_1_3_print_7(ImPro13Print *self,const char* string, kuchar ch, T_IM_PRO_OBD_CTRL* obCtrl)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdlthbit != obCtrl->obMinValue) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Ctrl(%u) blob_num:%u chNum:%u  %s result:obdlthbit(%d) (%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdlthbit,
        obCtrl->obMinValue))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdhthbit != obCtrl->obMaxValue) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Ctrl(%u) blob_num:%u chNum:%u  %s result:obdhthbit(%d) (%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdthbit.bit.obdhthbit, 
        obCtrl->obMaxValue))}; 
}

void im_pro_1_3_print_8(ImPro13Print *self,const char* string, kuchar ch, T_IM_PRO_AREA_INFO* obArea)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdh.bit.obdh != obArea->posX) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Set_Area(%u) blob_num:%u chNum:%u  %s result:obdh (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdh.bit.obdh, obArea->posX))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdv.bit.obdv != obArea->posY) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Set_Area(%u) blob_num:%u chNum:%u  %s result:obdv (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdv.bit.obdv, obArea->posY))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdhw.bit.obdhw != obArea->width) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Set_Area(%u) blob_num:%u chNum:%u  %s result:obdhw (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdhw.bit.obdhw, obArea->width))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdvw.bit.obdvw != obArea->lines) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Set_Area(%u) blob_num:%u chNum:%u  %s result:obdvw (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][chNum].obdcore.obdvw.bit.obdvw, obArea->lines))}; 
}

void im_pro_1_3_print_9(ImPro13Print *self,const char* string, kuchar ch, T_IM_PRO_RGB4* status)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(status->R != ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntr.bit.obdcntr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBCNT(%u) blob_num:%u chNum:%u %s result:R (%lu) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->R, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntr.bit.obdcntr))}; 
        
    if(status->Gr!= ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntgr.bit.obdcntgr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBCNT(%u) blob_num:%u chNum:%u %s result:Gr (%lu) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->Gr, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntgr.bit.obdcntgr))}; 
        
    if(status->Gb!= ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntgb.bit.obdcntgb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBCNT(%u) blob_num:%u chNum:%u %s result:Gb (%lu) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->Gb, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntgb.bit.obdcntgb))}; 
        
    if(status->B != ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntb.bit.obdcntb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBCNT(%u) blob_num:%u chNum:%u %s result:B (%lu) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->B, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obdcntb.bit.obdcntb))}; 
}
#endif

ImPro13Print* im_pro_1_3_print_new(void)
{
	ImPro13Print* self = k_object_new_with_private(IM_TYPE_PRO_1_3_PRINT, sizeof(ImPro13PrintPrivate));

	return self;
}

ImPro13Print* im_pro_1_3_print_get(void)
{
	static ImPro13Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_3_PRINT, sizeof(ImPro13PrintPrivate));
	}

	return self;
}
