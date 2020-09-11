/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : 陈阳
*@brief : CtImPro8
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimpro1.h"
#include "ctimpro8.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImPro8, ct_im_pro_8)
#define CT_IM_PRO_8_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImPro8Private, CT_TYPE_IM_PRO_8))


struct _CtImPro8Private
{
    TImProSentopCtrl sentopCtrl;
    TImProSentopBsCtrl bsCtrl;
    TImProSentopObtWeightCoeff obtWeightCoeff;
    TImProLdivCtrl ldivCtrl;
    TImProLdivArea ldivArea;
    TImProIntSentopCtrl intCtrl;
    TImProCallbackCfg callbackCfg;
    TImProSgCtrl sgCtrl;
};


/**
 * IMPL
 */
static void ct_im_pro_8_constructor(CtImPro8 *self)
{
	CtImPro8Private *priv = CT_IM_PRO_8_GET_PRIVATE(self);
    // priv->sentopCtrl = kzalloc(sizeof(*priv->sentopCtrl), GFP_KERNEL);
    priv->sentopCtrl.senConnectTypeSel[0] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_SLVS;
    priv->sentopCtrl.senConnectTypeSel[1] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS;
    priv->sentopCtrl.senConnectTypeSel[2] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS;
    priv->sentopCtrl.senConnectTypeSel[3] = ImproSentop_E_IM_PRO_SENTOP_CONN_TYPE_SEL_LVDS;
    priv->sentopCtrl.blobInputSel[0] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_0;
    priv->sentopCtrl.blobInputSel[1] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_1;
    priv->sentopCtrl.blobInputSel[2] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_2;
    priv->sentopCtrl.blobInputSel[3] = ImproSentop_E_IM_PRO_SENTOP_INPUT_TO_BLOB_FROM_LDIV0_3;
    priv->sentopCtrl.sdramOutputType[0] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_0_POST_BLOB;
    priv->sentopCtrl.sdramOutputType[1] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_1_POST_BLOB;
    priv->sentopCtrl.sdramOutputType[2] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_2_POST_BLOB;
    priv->sentopCtrl.sdramOutputType[3] = ImproSentop_E_IM_PRO_SENTOP_SDRAM_OUTPUT_TYPE_LDIV0_3_POST_BLOB;
    priv->sentopCtrl.outputSelSro2 = ImproSentop_E_IM_PRO_SENTOP_OUT_SEL_LDIV0;
    priv->sentopCtrl.sencoreHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_SENCORE_MAX_HSIZE_CTRL_1;
    priv->sentopCtrl.ldivHmaxSizeCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MAX_HSIZE_CTRL_1;
    priv->sentopCtrl.ldivMultiChInputCtrl = ImproSentop_E_IM_PRO_SENTOP_LDIV_MULTI_INPUT_CTRL_DISABLE;
    priv->sentopCtrl.firstPixel[0][0] = E_IM_PRO_ORG_R;
    priv->sentopCtrl.firstPixel[0][1] = E_IM_PRO_ORG_GB;
    priv->sentopCtrl.firstPixel[1][0] = E_IM_PRO_ORG_R;
    priv->sentopCtrl.firstPixel[1][1] = E_IM_PRO_ORG_GB;
    priv->sentopCtrl.firstPixel[2][0] = E_IM_PRO_ORG_R;
    priv->sentopCtrl.firstPixel[2][1] = E_IM_PRO_ORG_GB;
    priv->sentopCtrl.firstPixel[3][0] = E_IM_PRO_ORG_R;
    priv->sentopCtrl.firstPixel[3][1] = E_IM_PRO_ORG_GB;

    priv->bsCtrl.shiftValue[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_2BIT;
    priv->bsCtrl.shiftValue[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_2BIT;
    priv->bsCtrl.shiftValue[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT;
    priv->bsCtrl.shiftValue[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SHIFT_0BIT;
    priv->bsCtrl.satCompensation[0] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP;
    priv->bsCtrl.satCompensation[1] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_COMP;
    priv->bsCtrl.satCompensation[2] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP;
    priv->bsCtrl.satCompensation[3] = ImproSentop_E_IM_PRO_SENTOP_BS_SAT_NOCOMP;
    priv->bsCtrl.shiftDir[0] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L;
    priv->bsCtrl.shiftDir[1] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L;
    priv->bsCtrl.shiftDir[2] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L;
    priv->bsCtrl.shiftDir[3] = ImproSentop_E_IM_PRO_SENTOP_BS_BIT_SHIFT_DIR_L;

    priv->obtWeightCoeff.coeff[0][0] = 0;
    priv->obtWeightCoeff.coeff[0][1] = 0;
    priv->obtWeightCoeff.coeff[1][0] = 0;
    priv->obtWeightCoeff.coeff[1][1] = 0;
    priv->obtWeightCoeff.coeff[2][0] = 0;
    priv->obtWeightCoeff.coeff[2][1] = 0;
    priv->obtWeightCoeff.coeff[3][0] = 0;
    priv->obtWeightCoeff.coeff[3][1] = 0;

    priv->ldivCtrl.mode = ImproSensldiv_E_IM_PRO_LDIV_LDSTMD_LINE;
    priv->ldivCtrl.ldipmd = ImproSensldiv_E_IM_PRO_LDIV_LDIPMD_8POINT_INPUT;
    priv->ldivCtrl.ldvdmd = ImproSensldiv_E_IM_PRO_LDIV_LDVDMD_NO_SUBSAMPLING;
    priv->ldivCtrl.hdInsertionEn = ImproSensldiv_E_IM_PRO_LDIV_HD_INSERTION_ENABLE_DIS;
    priv->ldivCtrl.ldmch = ImproSensldiv_E_IM_PRO_LDIV_LDMCH_NO_COMBI;
    priv->ldivCtrl.lddivmd = ImproSensldiv_E_IM_PRO_LDIV_LDDIVMD_2RECT_OUTPUT;
    priv->ldivCtrl.ldopmd = ImproSensldiv_E_IM_PRO_LDIV_LDOPMD_2LINE_1OUT;

    priv->ldivArea.inWidth = 4200;
    priv->ldivArea.outPosX[0] = 48;
    priv->ldivArea.outPosX[1] = 48+2076;
    priv->ldivArea.outPosX[2] = 0;
    priv->ldivArea.outPosX[3] = 0;
    priv->ldivArea.outWidth[0] = 2076;
    priv->ldivArea.outWidth[1] = 2076;
    priv->ldivArea.outWidth[2] = 0;
    priv->ldivArea.outWidth[3] = 0;

    priv->intCtrl.intMode = E_IM_PRO_INT_INTMD_OR;
    priv->intCtrl.vdEnable.interruptBit = D_IM_PRO_INT_VDF00;
    priv->intCtrl.vdEnable.permissionFlg = 1;
    priv->intCtrl.hdEnable.interruptBit = 0;
    priv->intCtrl.hdEnable.permissionFlg = 0;

    priv->callbackCfg.inthandler = im_pro_8_1_slvs_sen_vd_cb;
    priv->callbackCfg.userParam = 0;

    priv->sgCtrl.vhdo	 = 1;
    priv->sgCtrl.vdot	 = 1;
    priv->sgCtrl.vdinv	 = 0;
    priv->sgCtrl.hdinv	 = 0;
    priv->sgCtrl.hdchg	 = 1;
    priv->sgCtrl.vddly	 = 0;
    priv->sgCtrl.vdocyc	 = 2275;
    priv->sgCtrl.vdow	 = 1;
    priv->sgCtrl.hdocyc	 = 264;
    priv->sgCtrl.hdow	 = 4;
    priv->sgCtrl.hdocyc2 = 264;
    priv->sgCtrl.hdow2	 = 4;
}

static void ct_im_pro_8_destructor(CtImPro8 *self)
{
	CtImPro8Private *priv = CT_IM_PRO_8_GET_PRIVATE(self);
}


/**
 * PUBLIC
 */
#ifndef CO_CT_IM_PRO_DISABLE
void ct_im_pro_8_1(CtImPro8 *self, const kuint32 idx )
{
    CtImPro8Private *priv = CT_IM_PRO_8_GET_PRIVATE(self);
    kint32 ercd;
    EImProPastopClkType clkType;
    kuchar onOff;
    kuchar waitSkip;

    TImProSentopObtCtrl obtCtrl = {
        .obtCommPerttern = ImproSentop_E_IM_PRO_SENTOP_OBT_COMM_PARTTERN_4SETS,
    };

    // Initialization of sen macro
    ercd = Im_PRO_SENTOP_SW_Reset();
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_SW_Reset() Error ercd=0x%x\n", ercd ));
        return;
    } else {
    }
    impro_sentop_init();

    clkType    = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_SENSORCLK;
    onOff      = D_IM_PRO_CLOCK_ON;
    waitSkip   = 0;
    ercd = impro_sentop_control_clock( clkType, onOff, waitSkip );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sentop_control_clock( %u, %u, %u ) Error ercd=0x%x\n", clkType, onOff, waitSkip, ercd ));
        return;
    } else {
    }

    clkType    = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK0;
    onOff      = D_IM_PRO_CLOCK_ON;
    waitSkip   = 0;
    ercd = impro_sentop_control_clock( clkType, onOff, waitSkip );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sentop_control_clock( %u, %u, %u ) Error ercd=0x%x\n", clkType, onOff, waitSkip, ercd ));
        return;
    } else {
    }

    clkType    = ImproSentop_E_IM_PRO_SENTOP_CLK_TYPE_APCLK2;
    onOff      = D_IM_PRO_CLOCK_ON;
    waitSkip   = 0;
    ercd = impro_sentop_control_clock( clkType, onOff, waitSkip );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sentop_control_clock( %u, %u, %u ) Error ercd=0x%x\n", clkType, onOff, waitSkip, ercd ));
        return;
    } else {
    }
    DriverCommon_DDIM_PRINT(( "impro_sentop_control_clock( %u, %u, %u ) result:CLKSTP1(%lu)\n", clkType, onOff, waitSkip, 
                ioPro.sen.sentop.CLKSTP.CLKSTP1.word ));

    ercd = impro_sentop_ctrl( &priv->sentopCtrl );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sentop_ctrl() invalid Error ercd=0x%x\n", ercd ));
        return;
    } else {
    }
    im_pro_1_0_print_4(NULL,"", &priv->sentopCtrl);

    ercd = Im_PRO_SENTOP_BS_Ctrl( &priv->bsCtrl );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_BS_Ctrl() Error ercd=0x%x\n", ercd ));
        return;
    } else {
    }
    im_pro_1_0_print_5(NULL, "", &priv->bsCtrl );

    ercd = Im_PRO_SENTOP_OBT_Ctrl( &obtCtrl );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_OBT_Ctrl() min_para Error ercd=0x%x\n", ercd ));
        return;
    } else {
    }
    im_pro_1_0_print_6(NULL, "", &obtCtrl );

    ercd = Im_PRO_SENTOP_OBT_Set_Weight_Coeff( &priv->obtWeightCoeff );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "Im_PRO_SENTOP_OBT_Set_Weight_Coeff() min_para Error ercd=0x%x\n", ercd ));
        return;
    } else {
    }
    im_pro_1_0_print_7(NULL, "", &priv->obtWeightCoeff );

	// VD interrupt configuration
	interrupt_clear1_sentop_interrupt_ctrl( &priv->intCtrl );
	interrupt_sen_set_vd_int_handler( &priv->callbackCfg );

	// SLVS-EC configuration
	im_pro_8_1_slvs_init_combo_phy(NULL);
	im_pro_8_1_slvs_init(NULL);

	// ldiv configuration
    ercd = impro_sensldiv_ctrl( ImproSensldiv_E_IM_PRO_LDIV_CH_0, &priv->ldivCtrl );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sensldiv_ctrl() max_para Error ercd=0x%x\n", ercd ));
    } else {
        im_pro_1_3_print_2(NULL, "", ImproSensldiv_E_IM_PRO_LDIV_CH_0, &priv->ldivCtrl );
    }

    ercd = impro_sensldiv_set_area( ImproSensldiv_E_IM_PRO_LDIV_CH_0, &priv->ldivArea );
    if( ercd != DdimUserCustom_E_OK ) {
        DriverCommon_DDIM_PRINT(( "impro_sensldiv_set_area() min_para Error ercd=0x%x\n", ercd ));
    } else {
        im_pro_1_3_print_3(NULL, "", ImproSensldiv_E_IM_PRO_LDIV_CH_0, &priv->ldivArea );
    }

	// P2M/PWCH configuration
    im_pro_8_1_slvs_raw_output(NULL);

	//sg configuration
	Im_PRO_SG_Ctrl( 0, &priv->sgCtrl );
}

void ct_im_pro_8_2(CtImPro8 *self, const kuint32 idx )
{
    E_IM_PRO_P2M_CH		p2mOddCh	 = E_IM_PRO_P2M_CH0;
	E_IM_PRO_P2M_CH		p2mEvenCh	 = E_IM_PRO_P2M_CH1;
	E_IM_PRO_PWCH		pwchOddCh	 = E_IM_PRO_PWCH_0;
	E_IM_PRO_PWCH		pwchEvenCh = E_IM_PRO_PWCH_1;

	// sg
	Im_PRO_SG_Start( 0 );

	// P2M/PWCH
	Im_PRO_PWch_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh );
	Im_PRO_P2M_Set_PAEN( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh, 1 );
	Im_PRO_P2M_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh );
	Im_PRO_PWch_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh );
	Im_PRO_P2M_Set_PAEN( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh, 1 );
	Im_PRO_P2M_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh );

	p2mOddCh	 = E_IM_PRO_P2M_CH2;
	p2mEvenCh	 = E_IM_PRO_P2M_CH3;
	pwchOddCh	 = E_IM_PRO_PWCH_2;
	pwchEvenCh	    = E_IM_PRO_PWCH_3;

	Im_PRO_PWch_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchOddCh );
	Im_PRO_P2M_Set_PAEN( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh, 1 );
	Im_PRO_P2M_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mOddCh );
	Im_PRO_PWch_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, pwchEvenCh );
	Im_PRO_P2M_Set_PAEN( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh, 1 );
	Im_PRO_P2M_Start( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_BLOCK_TYPE_SEN, p2mEvenCh );

	// ldiv
	Im_PRO_LDIV_Set_PAEN( ImproSensldiv_E_IM_PRO_LDIV_CH_0, 1 );
	Im_PRO_LDIV_Start( ImproSensldiv_E_IM_PRO_LDIV_CH_0 );

	// SLVS-EC
	Im_PRO_SLVS_Start( E_IM_PRO_SLVS_STREAM_TYPE_A );
}

void ct_im_pro_8_3(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_4(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_5(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_6(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_7(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_8(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_9(CtImPro8 *self, const kuint32 idx )
{
}

void ct_im_pro_8_10(CtImPro8 *self, const kuint32 idx )
{
}
#endif

CtImPro8* ct_im_pro_8_new(void)
{
	CtImPro8* self = k_object_new_with_private(CT_TYPE_IM_PRO_8, sizeof(CtImPro8Private));

	return self;
}

CtImPro8* ct_im_pro_8_get(void)
{
	static CtImPro8* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_PRO_8, sizeof(CtImPro8Private));
	}

	return self;
}
