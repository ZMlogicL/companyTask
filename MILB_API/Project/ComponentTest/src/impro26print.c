/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-05
*@author : 陈阳
*@brief : Impro26Print
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "impro26print.h"



K_TYPE_DEFINE_DERIVED_WITH_PRIVATE(Impro26Print, impro_2_6_print, ABS_TYPE_IM_PRO_PRINT)
#define IMPRO_2_6_PRINT_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), Impro26PrintPrivate, IMPRO_TYPE_2_6_PRINT))


struct _Impro26PrintPrivate
{


};


/**
 * IMPL
 */
static void impro_2_6_print_constructor(Impro26Print *self)
{
	Impro26PrintPrivate *priv = IMPRO_2_6_PRINT_GET_PRIVATE(self);
//((AbsImProPrint*)self)->ioPro = ioPro;
    // ((AbsImProPrint*)self)->ioPro->  = kzalloc(sizeof(*struct IoPro), GFP_KERNEL);
}

static void impro_2_6_print_destructor(Impro26Print *self)
{
	Impro26PrintPrivate *priv = IMPRO_2_6_PRINT_GET_PRIVATE(self);
//    ((AbsImProPrint*)self)->ioPro = NULL;
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void im_pro_2_6_print_0(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_FFSH_CH ch, kint32 ercd, USHORT ffshCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshwric.bit.ffshwric != ffshCtrl) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Coeff_Read_Line_Wait(%u %u) %s result:ffshwric  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshwric.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshwric.bit.ffshwric,ffshCtrl))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FFSH_Set_Coeff_Read_Line_Wait(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_6_print_1(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_FFSH_CH ch, kint32 ercd, const T_IM_PRO_RDMA_FFSH_ADDR** ffshCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshbc.word != (*ffshCtrl)->ffshbc) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) %s result:ffshbc 0x%08lx  reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].
            ffshbc.word,(kulong)(*ffshCtrl)->ffshbc))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubpr.word != (*ffshCtrl)->ffshsubpr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) %s result:ffshsubpr  0x%08lx reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].
            ffshsubpr.word,(kulong)(*ffshCtrl)->ffshsubpr))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.word != (*ffshCtrl)->ffshsubsp) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) %s result:ffshsubsp  0x%08lx  reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubsp.word,
            (kulong)(*ffshCtrl)->ffshsubsp))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.word != (*ffshCtrl)->ffshsubdr) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) %s result:ffshsubdr  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubdr.word,
            (kulong)(*ffshCtrl)->ffshsubdr))
        };

        if((kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubst.word != (*ffshCtrl)->ffshsubst) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) %s result:ffshsubst  0x%08lx   reg_addr (0x%08lx)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ffsh[ch].ffshsubst.word,
            (kulong)(*ffshCtrl)->ffshsubst))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_Get_RdmaAddr_FFSH_Cntl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_6_print_2(Impro26Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Start(%u %u) result:  0x%08lx(%u)\n", 
            unitNo, ch, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fftrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fftrg.bit.fftrg));
}

void im_pro_2_6_print_3(Impro26Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Stop(%u %u %u) result:fftrg 0x%08lx(%u)\n", 
            unitNo, ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fftrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fftrg.bit.fftrg));
}

void im_pro_2_6_print_4(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_FF_CH ch, 
                        kint32 ercd, T_IM_PRO_FF_CTRL* ffCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffdefts.bit.ffdefts != ffCtrl->ffdefts) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Ctrl(%u %u) %s result:ffdefts  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffdefts.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffdefts.bit.ffdefts,ffCtrl->ffdefts))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffmnwgt.bit.ffmnwgt != ffCtrl->mnwgt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Ctrl(%u %u) %s result:ffmnwgt  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffmnwgt.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffmnwgt.bit.ffmnwgt,ffCtrl->mnwgt))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffsbwgt.bit.ffsbwgt != ffCtrl->sbwgt) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Ctrl(%u %u) %s result:ffsbwgt  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffsbwgt.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffsbwgt.bit.ffsbwgt,ffCtrl->sbwgt))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Ctrl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_6_print_5(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_FF_CH ch, kint32 ercd, T_IM_PRO_AREA_INFO* ffCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffh.bit.ffh != ffCtrl->posX) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_Area(%u %u) %s result:ffh  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffh.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffh.bit.ffh,ffCtrl->posX))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffv.bit.ffv != ffCtrl->posY) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_Area(%u %u) %s result:ffv  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffv.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffv.bit.ffv,ffCtrl->posY))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffhw.bit.ffhw != ffCtrl->width) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_Area(%u %u) %s result:ffhw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffhw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffhw.bit.ffhw,ffCtrl->width))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffvw.bit.ffvw != ffCtrl->lines) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_Area(%u %u) %s result:ffvw  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffvw.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].ffvw.bit.ffvw,ffCtrl->lines))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_Area(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_6_print_6(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_FF_CH ch, kint32 ercd, T_IM_PRO_FF_LPF_CTRL* ffCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb0.bit.fflpb0 != ffCtrl->b0) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_FIR_Filter(%u %u) %s result:fflpb0  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb0.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb0.bit.fflpb0,ffCtrl->b0))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb1.bit.fflpb1 != ffCtrl->b1) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_FIR_Filter(%u %u) %s result:fflpb1  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb1.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb1.bit.fflpb1,ffCtrl->b1))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb2.bit.fflpb2 != ffCtrl->b2) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_FIR_Filter(%u %u) %s result:fflpb2  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb2.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.ff[ch].fflpb2.bit.fflpb2,ffCtrl->b2))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_FF_Set_FIR_Filter(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}

void im_pro_2_6_print_7(Impro26Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Start(%u %u) result:sdctrg 0x%08lx(%u)\n", 
            unitNo, ch, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg));
}

void im_pro_2_6_print_8(Impro26Print *self, E_IM_PRO_UNIT_NUM unitNo, E_IM_PRO_SDC_CH ch, kuchar force)
{
    DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Stop(%u %u %u) result:sdctrg  0x%08lx(%u)\n", 
            unitNo, ch, force, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdctrg.bit.sdctrg));
}

void im_pro_2_6_print_9(Impro26Print *self, const char* string, E_IM_PRO_UNIT_NUM unitNo, 
                        E_IM_PRO_SDC_CH ch, kint32 ercd, T_IM_PRO_SDC_CTRL* sdcCtrl)
{
    if( ercd == DdimUserCustom_E_OK) {
        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmd != sdcCtrl->sdcMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl(%u %u) %s result:sdcmd  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmd,sdcCtrl->sdcMode))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpto != sdcCtrl->afpbOutputPtn) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl(%u %u) %s result:sdcpto  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpto,sdcCtrl->afpbOutputPtn))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmono != sdcCtrl->monochromeMode) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl(%u %u) %s result:sdcmono  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcmono,sdcCtrl->monochromeMode))
        };

        if(((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpdafen != sdcCtrl->afpbEnabled) {
            DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl(%u %u) %s result:sdcpdafen  0x%08lx(%d) in(%d)\n", 
            unitNo, ch, string, (kulong)&((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.word, 
            ((AbsImProPrint*)self)->ioPro->imgPipe[unitNo].sro.sdc[ch].sdcctl.bit.sdcpdafen,sdcCtrl->afpbEnabled))};
    } else {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SDC_Ctrl(%u %u) error ercd=0x%x\n", unitNo, ch, ercd));
    }
}
#endif

Impro26Print* impro_2_6_print_new(void)
{
	Impro26Print* self = k_object_new_with_private(IMPRO_TYPE_2_6_PRINT, sizeof(Impro26PrintPrivate));

	return self;
}

Impro26Print* impro_2_6_print_get(void)
{
	static Impro26Print* self = NULL;

	if (!self) {
		self = k_object_new_with_private(IMPRO_TYPE_2_6_PRINT, sizeof(Impro26PrintPrivate));
	}

	return self;
}
