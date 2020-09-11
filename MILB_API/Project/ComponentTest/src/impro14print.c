/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-04
*@author : 陈阳
*@brief : ImPro14Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro14print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(ImPro14Print, im_pro_1_4_print, ABS_TYPE_IM_PRO_PRINT)
#define IM_PRO_1_4_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), ImPro14PrintPrivate, IM_TYPE_PRO_1_4_PRINT))


struct _ImPro14PrintPrivate
{


};


/**
 *IMPL
 */
static void im_pro_1_4_print_constructor(ImPro14Print *self)
{
	ImPro14PrintPrivate *priv = IM_PRO_1_4_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void im_pro_1_4_print_destructor(ImPro14Print *self)
{
	ImPro14PrintPrivate *priv = IM_PRO_1_4_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 *PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_1_4_print_0(ImPro14Print *self,const char* string, kuchar ch, T_IM_PRO_RGB4* status)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obd_block_ch(ch, &blockNum, &chNum);
    if(status->R != ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatar.bit.obddatar) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBData(%u) blob_num:%u chNum:%u %s result:R (%lu) reg_val (%lu)\n", 
        ch, blockNum, chNum, string, status->R, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatar.bit.obddatar))}; 
        
    if(status->Gr!= ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatagr.bit.obddatagr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBData(%u) blob_num:%u chNum:%u %s result:Gr (%lu) reg_val (%lu)\n", 
        ch, blockNum, chNum, string, status->Gr, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatagr.bit.obddatagr))}; 
        
    if(status->Gb!= ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatagb.bit.obddatagb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBData(%u) blob_num:%u chNum:%u %s result:Gb (%lu) reg_val (%lu)\n", 
        ch, blockNum, chNum, string, status->Gb, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatagb.bit.obddatagb))}; 
        
    if(status->B != ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatab.bit.obddatab) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBD_Get_OBData(%u) blob_num:%u chNum:%u %s result:B (%lu) reg_val (%lu)\n", 
        ch, blockNum, chNum, string, status->B, 
        ((AbsImProPrint*)self)->ioPro->sen.obd[blockNum][ch].obdcore.obddatab.bit.obddatab))}; 
}      

void im_pro_1_4_print_1(ImPro14Print *self,const char* string, kuchar ch)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obttrg.bit.obttrg != D_IM_PRO_TRG_STATUS_RUNNING) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Start(%u) blob_num:%u chNum:%u  %s result:obttrg (%u)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obttrg.bit.obttrg))}; 
}

void im_pro_1_4_print_2(ImPro14Print *self,const char* string, kuchar ch, kuchar force)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obttrg.bit.obttrg != D_IM_PRO_TRG_STATUS_STOPPED) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Stop(%u, %u) blob_num:%u chNum:%u  %s result:obttrg (%u)\n", 
        ch, force, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obttrg.bit.obttrg))}; 
}

void im_pro_1_4_print_3(ImPro14Print *self,const char* string, kuchar ch, T_IM_PRO_OBT_CTRL* obCtrl)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obten != obCtrl->obtEnable) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obten (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obten, obCtrl->obtEnable))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtmd != obCtrl->mode) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obtmd (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtmd, obCtrl->mode))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtsl != obCtrl->sel) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obtsl (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtsl, obCtrl->sel))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtcen != obCtrl->intercomm_enable) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obtcen (%d) in(%d)\n", ch, blockNum, 
        chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.bit.obtcen, obCtrl->intercomm_enable))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obththbit != obCtrl->obMinValue) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obththbit(%d) in(%d)\n", ch, blockNum, 
        chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obththbit, obCtrl->obMinValue))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obtlthbit != obCtrl->obMaxValue) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Ctrl(%u) blob_num:%u chNum:%u  %s result:obtlthbit(%d) in(%d)\n", ch, blockNum, 
        chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.bit.obtlthbit, obCtrl->obMaxValue))}; 
}

void im_pro_1_4_print_4(ImPro14Print *self,const char* string, kuchar ch, T_IM_PRO_AREA_INFO* obArea)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obth.bit.obth != obArea->posX) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Area(%u) blob_num:%u chNum:%u  %s result:obth (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obth.bit.obth, obArea->posX))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtv.bit.obtv != obArea->posY) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Area(%u) blob_num:%u chNum:%u  %s result:obtv (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtv.bit.obtv, obArea->posY))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obthw.bit.obthw != obArea->width) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Area(%u) blob_num:%u chNum:%u  %s result:obthw (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obthw.bit.obthw, obArea->width))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtvw.bit.obtvw != obArea->lines) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Area(%u) blob_num:%u chNum:%u  %s result:obtvw (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtvw.bit.obtvw, obArea->lines))}; 
}

void im_pro_1_4_print_5(ImPro14Print *self,const char* string, kuchar ch, T_IM_PRO_RGB2* offset)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsr.bit.obtofsr != offset->R) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Offset(%u) blob_num:%u chNum:%u  %s result:obtofsr (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsr.bit.obtofsr, offset->R))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgr.bit.obtofsgr != offset->Gr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Offset(%u) blob_num:%u chNum:%u  %s result:obtofsgr(%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgr.bit.obtofsgr, offset->Gr))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgb.bit.obtofsgb != offset->Gb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Offset(%u) blob_num:%u chNum:%u  %s result:obtofsgb(%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgb.bit.obtofsgb, offset->Gb))}; 
        
    if(((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsb.bit.obtofsb != offset->B) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Set_Offset(%u) blob_num:%u chNum:%u  %s result:obtofsb (%d) in(%d)\n", 
        ch, blockNum, chNum, string, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsb.bit.obtofsb, offset->B))}; 
}

void im_pro_1_4_print_6(ImPro14Print *self,const char* string, kuchar ch, T_IM_PRO_RGB2* status)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if(status->R != ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatar.bit.obtdatar) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Get_OBTata(%u) blob_num:%u chNum:%u %s result:R (%u) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->R, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatar.bit.obtdatar))}; 
        
    if(status->Gr != ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatagr.bit.obtdatagr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Get_OBTata(%u) blob_num:%u chNum:%u %s result:Gr (%u) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->Gr, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatagr.bit.obtdatagr))}; 
        
    if(status->Gb != ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatagb.bit.obtdatagb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Get_OBTata(%u) blob_num:%u chNum:%u %s result:Gb (%u) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->Gb, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatagb.bit.obtdatagb))}; 
        
    if(status->B != ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatab.bit.obtdatab) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_OBT_Get_OBTata(%u) blob_num:%u chNum:%u %s result:B (%u) reg_val (%u)\n", 
        ch, blockNum, chNum, string, status->B, 
        ((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][ch].obtcore.obtdatab.bit.obtdatab))}; 
}

void im_pro_1_4_print_7(ImPro14Print *self,const char* string, kuchar ch, const T_IM_PRO_RDMA_OBT_ADDR** addr)
{
    kuchar blockNum = 0;
    kuchar chNum = 0;

    im_pro_comm_get_obt_block_ch(ch, &blockNum, &chNum);
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.word != (*addr)->obtctl) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtctl reg_addr \
        (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, 
        (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtctl.word, (kulong)(*addr)->obtctl))}; 
        
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.word != (*addr)->obtthbit) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtthbit \
        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtthbit.word,
        (kulong)(*addr)->obtthbit))}; 
        
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsr.word != (*addr)->obtofsr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtofsr  \
        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsr.word, 
        (kulong)(*addr)->obtofsr))}; 
        
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgr.word != (*addr)->obtofsgr) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtofsgr   \
        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgr.word, 
        (kulong)(*addr)->obtofsgr))}; 
        
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgb.word != (*addr)->obtofsgb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtofsgb \
        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsgb.word, 
        (kulong)(*addr)->obtofsgb))}; 
        
    if((kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsb.word != (*addr)->obtofsb) { 
        DriverCommon_DDIM_PRINT(("Im_PRO_Get_RdmaAddr_OBT_Cntl(%u) blob_num:%u chNum:%u %s obtofsb     \
        reg_addr (0x%08lx) rdma_addr (0x%08lx)\n", 
        ch, blockNum, chNum, string, (kulong)&((AbsImProPrint*)self)->ioPro->sen.obt[blockNum][chNum].obtcore.obtofsb.word, 
        (kulong)(*addr)->obtofsb))}; 
}

void im_pro_1_4_print_8(ImPro14Print *self,const char* string, kuchar ch)
{
    { DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_Init(%u) %s result:sr(%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpisr.bit.sr))}; 
}

void im_pro_1_4_print_9(ImPro14Print *self,const char* string, kuchar ch)
{
    { DriverCommon_DDIM_PRINT(("Im_PRO_DMIPI_SR(%u) %s result:sr(%u)\n", 
        ch, string, 
        ((AbsImProPrint*)self)->ioPro->sen.mipid[ch].mpisr.bit.sr))}; 
}
#endif

ImPro14Print* im_pro_1_4_print_new(void)
{
	ImPro14Print* self = k_object_new_with_private(IM_TYPE_PRO_1_4_PRINT, sizeof(ImPro14PrintPrivate));

	return self;
}

ImPro14Print* im_pro_1_4_print_get(void)
{
	static ImPro14Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IM_TYPE_PRO_1_4_PRINT, sizeof(ImPro14PrintPrivate));
	}

	return self;
}
