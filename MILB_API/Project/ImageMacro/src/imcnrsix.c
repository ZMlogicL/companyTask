/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/

#include "imcnr.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include "jdscnr.h"
// for memset
#include <string.h>
#include "imcnrone.h"
#include "imcnrtwo.h"
#include "imcnrsix.h"


G_DEFINE_TYPE(ImCnrsix, im_cnrsix, G_TYPE_OBJECT);
#define IM_CNRSIX_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRSIX, ImCnrsixPrivate));


struct _ImCnrsixPrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_cnrsix_class_init(ImCnrsixClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnrsixPrivate));
}

static void im_cnrsix_init(ImCnrsix *self)
{
	ImCnrsixPrivate *priv = IM_CNRSIX_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnrsixPrivate *self = IM_CNRSIX_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnrsixPrivate *self = IM_CNRSIX_GET_PRIVATE(object);
}


/*PUBLIC*/
/*
Set CbCr setting of source
*/
INT32 im_cnrsix_ofl_ctrl_sprs_cc(ImCnrsix *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrsix_ofl_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprsCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrsix_ofl_ctrl_sprs_cc() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.SPRS.bit.SPRS = sprsCtrl->enable;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprsCtrl->cbTable.bd1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprsCtrl->cbTable.bd2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprsCtrl->cbTable.bd3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprsCtrl->cbTable.bd4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBBD.SPRSCBBD2,
			union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprsCtrl->cbTable.bd5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprsCtrl->cbTable.of0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprsCtrl->cbTable.of1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprsCtrl->cbTable.of2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprsCtrl->cbTable.of3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprsCtrl->cbTable.of4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprsCtrl->cbTable.of5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprsCtrl->cbTable.gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprsCtrl->cbTable.gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprsCtrl->cbTable.gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprsCtrl->cbTable.gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprsCtrl->cbTable.gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprsCtrl->cbTable.gain5 );

	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprsCtrl->crTable.bd1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprsCtrl->crTable.bd2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprsCtrl->crTable.bd3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprsCtrl->crTable.bd4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRBD.SPRSCRBD2,
			union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprsCtrl->crTable.bd5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprsCtrl->crTable.of0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprsCtrl->crTable.of1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprsCtrl->crTable.of2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprsCtrl->crTable.of3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprsCtrl->crTable.of4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprsCtrl->crTable.of5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprsCtrl->crTable.gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprsCtrl->crTable.gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprsCtrl->crTable.gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprsCtrl->crTable.gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprsCtrl->crTable.gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprsCtrl->crTable.gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set CbCr setting of source
*/
INT32 im_cnrsix_otf_ctrl_sprs_cc(ImCnrsix *self, UCHAR ch, const ImCnrCtrlCcSrcDst* const sprsCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrsix_otf_ctrl_sprs_cc() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprsCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrsix_otf_ctrl_sprs_cc() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.SPRS.bit.SPRS = sprsCtrl->enable;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_1, sprsCtrl->cbTable.bd1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_2, sprsCtrl->cbTable.bd2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_3, sprsCtrl->cbTable.bd3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD1,
			union io_cnr_cspr_reg_sprscbbd_1, SPRSCBBD_4, sprsCtrl->cbTable.bd4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBBD.SPRSCBBD2,
			union io_cnr_cspr_reg_sprscbbd_2, SPRSCBBD_5, sprsCtrl->cbTable.bd5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_0, sprsCtrl->cbTable.of0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_1, sprsCtrl->cbTable.of1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_2, sprsCtrl->cbTable.of2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF1,
			union io_cnr_cspr_reg_sprscbof_1, SPRSCBOF_3, sprsCtrl->cbTable.of3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_4, sprsCtrl->cbTable.of4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBOF.SPRSCBOF2,
			union io_cnr_cspr_reg_sprscbof_2, SPRSCBOF_5, sprsCtrl->cbTable.of5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_0, sprsCtrl->cbTable.gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA1,
			union io_cnr_cspr_reg_sprscbga_1, SPRSCBGA_1, sprsCtrl->cbTable.gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_2, sprsCtrl->cbTable.gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA2,
			union io_cnr_cspr_reg_sprscbga_2, SPRSCBGA_3, sprsCtrl->cbTable.gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_4, sprsCtrl->cbTable.gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCBGA.SPRSCBGA3,
			union io_cnr_cspr_reg_sprscbga_3, SPRSCBGA_5, sprsCtrl->cbTable.gain5 );

	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_1, sprsCtrl->crTable.bd1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_2, sprsCtrl->crTable.bd2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_3, sprsCtrl->crTable.bd3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD1,
			union io_cnr_cspr_reg_sprscrbd_1, SPRSCRBD_4, sprsCtrl->crTable.bd4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRBD.SPRSCRBD2,
			union io_cnr_cspr_reg_sprscrbd_2, SPRSCRBD_5, sprsCtrl->crTable.bd5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_0, sprsCtrl->crTable.of0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_1, sprsCtrl->crTable.of1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_2, sprsCtrl->crTable.of2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF1,
			union io_cnr_cspr_reg_sprscrof_1, SPRSCROF_3, sprsCtrl->crTable.of3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_4, sprsCtrl->crTable.of4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCROF.SPRSCROF2,
			union io_cnr_cspr_reg_sprscrof_2, SPRSCROF_5, sprsCtrl->crTable.of5 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_0, sprsCtrl->crTable.gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA1,
			union io_cnr_cspr_reg_sprscrga_1, SPRSCRGA_1, sprsCtrl->crTable.gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_2, sprsCtrl->crTable.gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA2,
			union io_cnr_cspr_reg_sprscrga_2, SPRSCRGA_3, sprsCtrl->crTable.gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_4, sprsCtrl->crTable.gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OTF_CSPR_REG.SPRSCRGA.SPRSCRGA3,
			union io_cnr_cspr_reg_sprscrga_3, SPRSCRGA_5, sprsCtrl->crTable.gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
CNR(OFL) Wait End
*/
INT32 im_cnrfive_ofl_wait_end(ImCnrsix *self, UCHAR ch, UINT32* const pWaitFactor, const INT32 waitTime )
{
	DDIM_USER_FLGPTN flgptn;
	DDIM_USER_FLGPTN waiptn;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfive_ofl_wait_end() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( pWaitFactor == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfive_ofl_wait_end() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	if (ch == ImCnr_CH_0) {
		waiptn = ImCnr_OFL_0_WAIT_FLGPTN;
	}
	else if (ch == ImCnr_CH_1) {
		waiptn = ImCnr_OFL_1_WAIT_FLGPTN;
	}
	else {
		waiptn = (ImCnr_OFL_0_WAIT_FLGPTN|ImCnr_OFL_1_WAIT_FLGPTN);
	}
	ercd = DDIM_User_Twai_Flg( FID_IM_CNR, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, waitTime );
	if( ercd == D_DDIM_USER_E_TMOUT ) {
		// A semaphore acquisition processing time out
		Ddim_Print(("im_cnrfive_ofl_wait_end() time out. ercd = %d\n", ercd));
		return ImCnr_SEM_TIMEOUT_ERR;
	}

	if( ercd != D_DDIM_USER_E_OK ) {
		// A semaphore acquisition processing error
		Ddim_Print(("im_cnrfive_ofl_wait_end() system error. ercd = %d\n", ercd));
		return ImCnr_SEM_NG;
	}

	DDIM_User_Clr_Flg( FID_IM_CNR, ~( flgptn & waiptn ) );

	*pWaitFactor = (UINT32)( flgptn & waiptn );

	if( (flgptn & ImCnr_AXI_ERR) != 0 ) {
		return ImCnr_AXI_ERR;
	}

	return D_DDIM_OK;
}

/*
CNR(OTF) Wait End
*/
INT32 im_cnrfive_otf_wait_end(ImCnrsix *self, UCHAR ch, UINT32* const pWaitFactor, const INT32 waitTime )
{
	DDIM_USER_FLGPTN flgptn;
	DDIM_USER_FLGPTN waiptn;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrfive_otf_wait_end() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( pWaitFactor == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrfive_otf_wait_end() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	if (ch == ImCnr_CH_0) {
		waiptn = ImCnr_OTF_0_WAIT_FLGPTN;
	}
	else if (ch == ImCnr_CH_1) {
		waiptn = ImCnr_OTF_1_WAIT_FLGPTN;
	}
	else {
		waiptn = (ImCnr_OTF_0_WAIT_FLGPTN|ImCnr_OTF_1_WAIT_FLGPTN);
	}
	ercd = DDIM_User_Twai_Flg( FID_IM_CNR, waiptn, D_DDIM_USER_TWF_ORW, &flgptn, waitTime );
	if( ercd == D_DDIM_USER_E_TMOUT ) {
		// A semaphore acquisition processing time out
		Ddim_Print(("im_cnrfive_otf_wait_end() time out. ercd = %d\n", ercd));
		return ImCnr_SEM_TIMEOUT_ERR;
	}

	if( ercd != D_DDIM_USER_E_OK ) {
		// A semaphore acquisition processing error
		Ddim_Print(("im_cnrfive_otf_wait_end() system error. ercd = %d\n", ercd));
		return ImCnr_SEM_NG;
	}

	DDIM_User_Clr_Flg( FID_IM_CNR, ~( flgptn & waiptn ) );

	*pWaitFactor = (UINT32)( flgptn & waiptn );

	if( (flgptn & ImCnr_AXI_ERR) != 0 ) {
		return ImCnr_AXI_ERR;
	}
	if( (flgptn & ImCnr_DRT_ERR) != 0 ) {
		return ImCnr_DRT_ERR;
	}

	return D_DDIM_OK;
}

ImCnrsix* im_cnrsix_new(void)
{
	ImCnrsix *self = g_object_new(IM_TYPE_CNRSIX, NULL);
	return self;
}
