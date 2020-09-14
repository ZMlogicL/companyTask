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


G_DEFINE_TYPE(ImCnrone, im_cnrone, G_TYPE_OBJECT);
#define IM_CNRONE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), IM_TYPE_CNRONE, ImCnronePrivate));


struct _ImCnronePrivate{

};


/*DECLS*/
static void 					dispose_od(GObject *object);
static void 					finalize_od(GObject *object);


/*IMPL*/
static void im_cnrone_class_init(ImCnroneClass *klass)
{
	g_type_class_add_private(klass, sizeof(ImCnronePrivate));
}

static void im_cnrone_init(ImCnrone *self)
{
	ImCnronePrivate *priv = IM_CNRONE_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
	ImCnronePrivate *self = IM_CNRONE_GET_PRIVATE(object);
}

static void finalize_od(GObject *object)
{
	ImCnronePrivate *self = IM_CNRONE_GET_PRIVATE(object);
}


/*PUBLIC*/
// Start CNR PCLK
VOID im_cnrone_on_pclk(ImCnrone *self, UCHAR ch )
{
#ifdef CO_ACT_CNR_PCLK
	INT32 intkey;

	intkey = Dd_ARM_DI();

	if (ch == ImCnr_CH_0) {
		Dd_Top_Start_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(),
				~D_DD_TOP_CNR1AP_BIT );
	}
	else if (ch == ImCnr_CH_1) {
		Dd_Top_Start_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AP_BIT );
	}
	else {
		Dd_Top_Start_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1AP_BIT );
		Dd_Top_Start_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AP_BIT );
	}

	Dd_ARM_EI( intkey );
#endif //CO_ACT_CNR_PCLK
}

// Stop CNR PCLK
VOID im_cnrone_off_pclk(ImCnrone *self, UCHAR ch )
{
#ifdef CO_ACT_CNR_PCLK
	INT32 intkey;

	intkey = Dd_ARM_DI();

	if (ch == ImCnr_CH_0) {
		Dd_Top_Stop_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AP_BIT );
	}
	else if (ch == ImCnr_CH_1) {
		Dd_Top_Stop_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AP_BIT );
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AP_BIT );
		Dd_Top_Stop_Clock( (UCHAR*)&S_IM_CNR_PCLK_CTRL_CNT2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AP_BIT );
	}

	Dd_ARM_EI( intkey );
#endif //CO_ACT_CNR_PCLK
}

/*
The semaphore of CNR is acquired for Off Line
*/
INT32 im_cnrone_ofl_open(ImCnrone *self, UCHAR ch, const INT32 tmout )
{
	DDIM_USER_ID sid;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_open() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ) {
		Ddim_Assertion(("I:im_cnrone_ofl_open. input param error. tmout = %x\n", tmout));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == ImCnr_CH_2) {
		for( UCHAR loop = ImCnr_CH_0; loop <= ImCnr_CH_1; loop++ ){
			sid = SID_IM_CNR_OFL(loop);
			if( D_DDIM_USER_SEM_WAIT_POL == tmout ) {
				ercd = DDIM_User_Pol_Sem( sid );				// pol_sem()
			}
			else{
				ercd = DDIM_User_Twai_Sem( sid, (DDIM_USER_TMO)tmout );	// twai_sem()
			}

			if( D_DDIM_USER_E_TMOUT == ercd ) {
				// A semaphore acquisition processing time out
				Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Time Out\n"));
				return ImCnr_SEM_TIMEOUT_ERR;
			}

			if( D_DDIM_USER_E_OK != ercd ) {
				// CNR processing error
				// CNR processing error
				Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Error\n"));
				return ImCnr_SEM_NG;
			}
		}
	}
	else{
		sid = SID_IM_CNR_OFL(ch);
		if( D_DDIM_USER_SEM_WAIT_POL == tmout ) {
			ercd = DDIM_User_Pol_Sem( sid );				// pol_sem()
		}
		else{
			ercd = DDIM_User_Twai_Sem( sid, (DDIM_USER_TMO)tmout );	// twai_sem()
		}

		if( D_DDIM_USER_E_TMOUT == ercd ) {
			// A semaphore acquisition processing time out
			Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Time Out\n"));
			return ImCnr_SEM_TIMEOUT_ERR;
		}

		if( D_DDIM_USER_E_OK != ercd ) {
			// CNR processing error
			// CNR processing error
			Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Error\n"));
			return ImCnr_SEM_NG;
		}
	}

	return D_DDIM_OK;
}

/*
The semaphore of CNR is acquired for On The Fly
*/
INT32 im_cnrone_otf_open(ImCnrone *self, UCHAR ch, const INT32 tmout )
{
	DDIM_USER_ID sid;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_open() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ) {
		Ddim_Assertion(("I:im_cnrone_otf_open. input param error. tmout = %x\n", tmout));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == ImCnr_CH_2) {
		for( UCHAR loop = ImCnr_CH_0; loop <= ImCnr_CH_1; loop++ ){
			sid = SID_IM_CNR_OTF(loop);
			if( D_DDIM_USER_SEM_WAIT_POL == tmout ) {
				ercd = DDIM_User_Pol_Sem( sid );				// pol_sem()
			}
			else{
				ercd = DDIM_User_Twai_Sem( sid, (DDIM_USER_TMO)tmout );	// twai_sem()
			}

			if( D_DDIM_USER_E_TMOUT == ercd ) {
				// A semaphore acquisition processing time out
				Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Time Out\n"));
				return ImCnr_SEM_TIMEOUT_ERR;
			}

			if( D_DDIM_USER_E_OK != ercd ) {
				// CNR processing error
				// CNR processing error
				Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Error\n"));
				return ImCnr_SEM_NG;
			}
		}
	}
	else{
		sid = SID_IM_CNR_OTF(ch);
		if( D_DDIM_USER_SEM_WAIT_POL == tmout ) {
			ercd = DDIM_User_Pol_Sem( sid );				// pol_sem()
		}
		else{
			ercd = DDIM_User_Twai_Sem( sid, (DDIM_USER_TMO)tmout );	// twai_sem()
		}

		if( D_DDIM_USER_E_TMOUT == ercd ) {
			// A semaphore acquisition processing time out
			Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Time Out\n"));
			return ImCnr_SEM_TIMEOUT_ERR;
		}

		if( D_DDIM_USER_E_OK != ercd ) {
			// CNR processing error
			// CNR processing error
			Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Error\n"));
			return ImCnr_SEM_NG;
		}
	}

	return D_DDIM_OK;
}

/*
CNR(OFL) Control
*/
INT32 im_cnrone_ofl_ctrl(ImCnrone *self, UCHAR ch, const ImCnrOflCtrl* const sprCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Read Setting
	//      |---RYDEF---|       |---RCDEF---|       |---RCDEF---|
	//  RYTA|-HSIZE-|   |  RCBTA|-HSIZE-|   |  RCRTA|-HSIZE-|   |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+
	//   |  |       | | |    |  |       | | |    |  |       | | |
	//   V  |       | d |    V  |       | d |    V  |       | d |
	//   S  |Y data | u |    S  |CB data| u |    S  |CR data| u |
	//   I  |valid  | m |    I  |valid  | m |    I  |valid  | m |
	//   Z  |area   | m |    Z  |area   | m |    Z  |area   | m |
	//   E  |       | y |    E  |       | y |    E  |       | y |
	//   |  |       | | |    |  |       | | |    |  |       | | |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+

	// Write Setting
	//      |---WYDEF---|       |---WCDEF---|       |---WCDEF---|
	//  WYTA|-HSIZE-|   |  WCBTA|-HSIZE-|   |  WCRTA|-HSIZE-|   |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+
	//   |  |       | | |    |  |       | | |    |  |       | | |
	//   V  |       | d |    V  |       | d |    V  |       | d |
	//   S  |Y data | u |    S  |CB data| u |    S  |CR data| u |
	//   I  |valid  | m |    I  |valid  | m |    I  |valid  | m |
	//   Z  |area   | m |    Z  |area   | m |    Z  |area   | m |
	//   E  |       | y |    E  |       | y |    E  |       | y |
	//   |  |       | | |    |  |       | | |    |  |       | | |
	// -----+-------+---+  -----+-------+---+  -----+-------+---+

	IO_CNR(ch)->OFL_REG_RW.SPRMOD.bit.YUV_MODE	= sprCtrl->mode;	// SPR YCC mode		@YUV_MODE

	IO_CNR(ch)->OFL_REG_RW.HSIZE.bit.HSIZE	= sprCtrl->width;		// SPR valid data width		@HSIZE
	IO_CNR(ch)->OFL_REG_RW.VSIZE.bit.VSIZE	= sprCtrl->lines;		// SPR valid data lines		@VSIZE

	IO_CNR(ch)->OFL_REG_RW.RYDEF.bit.RYDEF	= sprCtrl->rYWidth;	// Y width for read			@RYDEF
	IO_CNR(ch)->OFL_REG_RW.RYTA.bit.RYTA	= sprCtrl->rYAddr;	// Y address for read		@RYTA

	IO_CNR(ch)->OFL_REG_RW.RCDEF.bit.RCDEF	= sprCtrl->rCWidth;	// CbCr width for read		@RCDEF
	IO_CNR(ch)->OFL_REG_RW.RCBTA.bit.RCBTA	= sprCtrl->rCbAddr;	// Cb address for read		@RCBTA
	IO_CNR(ch)->OFL_REG_RW.RCRTA.bit.RCRTA	= sprCtrl->rCrAddr;	// Cr address for read		@RCRTA

	IO_CNR(ch)->OFL_REG_RW.WYDEF.bit.WYDEF	= sprCtrl->wYWidth;	// Y width for write		@WYDEF
	IO_CNR(ch)->OFL_REG_RW.WYTA.bit.WYTA	= sprCtrl->wYAddr;	// Y address for write		@WYTA

	IO_CNR(ch)->OFL_REG_RW.WCDEF.bit.WCDEF	= sprCtrl->wCWidth;	// CbCr width for write		@WCDEF
	IO_CNR(ch)->OFL_REG_RW.WCBTA.bit.WCBTA	= sprCtrl->wCbAddr;	// Cb address for write		@WCBTA
	IO_CNR(ch)->OFL_REG_RW.WCRTA.bit.WCRTA	= sprCtrl->wCrAddr;	// Cr address for write		@WCRTA

	IO_CNR(ch)->OFL_REG_RW.TMPTA.bit.TMPTA	= sprCtrl->workAddr;	// Address fir work area	@TMPTA

	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVT	= sprCtrl->divideTop;		// Virtucal process devide	@VDIVT
	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVB	= sprCtrl->divideBot;		// Virtucal process devide	@VDIVB

	if( ch == ImCnr_CH_2 ){
		S_IM_CNR_OFL_CALLBACK_FUNC[ImCnr_CH_0]	= sprCtrl->pCallBack;
		S_IM_CNR_OFL_CALLBACK_FUNC[ImCnr_CH_1]	= sprCtrl->pCallBack;
		S_IM_CNR_OFL_USERPARAM[ImCnr_CH_0]		= sprCtrl->userParam;
		S_IM_CNR_OFL_USERPARAM[ImCnr_CH_1]		= sprCtrl->userParam;
	}
	else{
		S_IM_CNR_OFL_CALLBACK_FUNC[ch]	= sprCtrl->pCallBack;
		S_IM_CNR_OFL_USERPARAM[ch]		= sprCtrl->userParam;
	}

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();
	return D_DDIM_OK;
}

/*
CNR(OTF) Control
*/
INT32 im_cnrone_otf_ctrl(ImCnrone *self, UCHAR ch, const ImCnrOtfCtrl* const sprCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif
	if (sprCtrl->width < 96 || sprCtrl->width > 2360) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input width error : %d\n", sprCtrl->width));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if (sprCtrl->lines < 72 || sprCtrl->lines > 4096) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input lines error : %d\n", sprCtrl->lines));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if ( (sprCtrl->wOffsetX != 0)&&(sprCtrl->wOffsetX < 96 || sprCtrl->wOffsetX > 2360)) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input wOffsetX error : %lu\n", sprCtrl->wOffsetX));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if (sprCtrl->videoFormat == 1){
		if (sprCtrl->wCWidth % 128){
			Ddim_Assertion(("im_cnrone_otf_ctrl() error. input wCWidth error : %lu\n", sprCtrl->wCWidth));
			return ImCnr_INPUT_PARAM_ERROR;
		}
		if( sprCtrl->mode != ImCnr_OTF_YCC_MODE_YCC420_SIMPLE ){
			Ddim_Assertion(("im_cnrone_otf_ctrl() error. mode error : %d\n", sprCtrl->mode));
			return ImCnr_INPUT_PARAM_ERROR;
		}
	}

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Write Setting
	//      |---WCDEF---|
	//  WCTA|-HSIZE-|   |
	// -----+-------+---+
	//   |  |       | | |
	//   V  |       | d |
	//   S  |C data | u |
	//   I  |valid  | m |
	//   Z  |area   | m |
	//   E  |       | y |
	//   |  |       | | |
	// -----+-------+---+

	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.YUV_MODE		= sprCtrl->mode;			// SPR YCC mode				@YUV_MODE
	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.EXMODE		= sprCtrl->extra_mode;		// SPR extra mode			@EXMODE
	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.CNRVFM		= sprCtrl->videoFormat;	// SPR video format			@CNRVFM

	IO_CNR(ch)->OTF_REG_RW.HSIZE.bit.HSIZE			= sprCtrl->width;			// SPR valid data width		@HSIZE
	IO_CNR(ch)->OTF_REG_RW.VSIZE.bit.VSIZE			= sprCtrl->lines;			// SPR valid data lines		@VSIZE

	IO_CNR(ch)->OTF_REG_RW.WCDEF.bit.WCDEF			= sprCtrl->wCWidth;		// CbCr width for write		@WCDEF

	IO_CNR(ch)->OTF_REG_RW.CNRWOFSX.bit.CNRWOFSX	= sprCtrl->wOffsetX;		// write offset X direction	@CNRWOFSX

	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVL			= sprCtrl->divideLeft;	// Virtucal process devide	@HDIVL
	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVR			= sprCtrl->divideRight;	// Virtucal process devide	@VDIVR

	IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.CNRCSE		= sprCtrl->continuous;		// Continuous processing	@CNRCSE

	if( ch == ImCnr_CH_2 ){
		S_IM_CNR_OTF_CALLBACK_FUNC[ImCnr_CH_0]	= sprCtrl->pCallBack;
		S_IM_CNR_OTF_CALLBACK_FUNC[ImCnr_CH_1]	= sprCtrl->pCallBack;
		S_IM_CNR_OTF_USERPARAM[ImCnr_CH_0]		= sprCtrl->userParam;
		S_IM_CNR_OTF_USERPARAM[ImCnr_CH_1]		= sprCtrl->userParam;
	}
	else{
		S_IM_CNR_OTF_CALLBACK_FUNC[ch]				= sprCtrl->pCallBack;
		S_IM_CNR_OTF_USERPARAM[ch]					= sprCtrl->userParam;
	}

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
CNR(OTF) Set output address information
*/
INT32 im_cnrone_otf_set_outaddr_info(ImCnrone *self, UCHAR ch, const ImCnrOtfOutaddrInfo* const addrInfo )
{
	INT32 outAddrCnt;

#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_set_outaddr_info() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( addrInfo == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_set_outaddr_info() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( (addrInfo->useBankNum == 0)||(addrInfo->useBankNum > ImCnr_ADDR_BANK_MAX) ){
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_set_outaddr_info() useBankNum parameter is error : %d\n",
				addrInfo->useBankNum));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Write Setting
	//      |---WCDEF---|
	//  WCTA|-HSIZE-|   |
	// -----+-------+---+
	//   |  |       | | |
	//   V  |       | d |
	//   S  |C data | u |
	//   I  |valid  | m |
	//   Z  |area   | m |
	//   E  |       | y |
	//   |  |       | | |
	// -----+-------+---+

	if( ch == ImCnr_CH_2 ){
		// set output address information	@WCTA
		S_IM_CNR_LATEST_MNG[ImCnr_CH_0].bankArea			= 0;	// reset
		S_IM_CNR_LATEST_MNG[ImCnr_CH_1].bankArea			= 0;	// reset
		S_IM_CNR_LATEST_MNG[ImCnr_CH_0].addr				= 0;	// reset
		S_IM_CNR_LATEST_MNG[ImCnr_CH_1].addr				= 0;	// reset
		S_IM_CNR_OUTPUT_MNG[ImCnr_CH_0].bankArea			= 0;	// reset
		S_IM_CNR_OUTPUT_MNG[ImCnr_CH_1].bankArea			= 0;	// reset
		S_IM_CNR_OUTPUT_MNG[ImCnr_CH_0].useBankNum		= addrInfo->useBankNum;
		S_IM_CNR_OUTPUT_MNG[ImCnr_CH_1].useBankNum		= addrInfo->useBankNum;
		for( outAddrCnt = 0; outAddrCnt < addrInfo->useBankNum; outAddrCnt++ ){
			S_IM_CNR_OUTPUT_MNG[ImCnr_CH_0].outputAddr[outAddrCnt]	= addrInfo->wCAddr[outAddrCnt];
			S_IM_CNR_OUTPUT_MNG[ImCnr_CH_1].outputAddr[outAddrCnt]	= addrInfo->wCAddr[outAddrCnt];
		}
		IO_CNR(ImCnr_CH_0)->OTF_REG_RW.WCTA.bit.WCTA		= addrInfo->wCAddr[0];
		IO_CNR(ImCnr_CH_1)->OTF_REG_RW.WCTA.bit.WCTA		= addrInfo->wCAddr[0];
	}
	else{
		// set output address information	@WCTA
		S_IM_CNR_LATEST_MNG[ch].bankArea		= 0;	// reset
		S_IM_CNR_LATEST_MNG[ch].addr				= 0;	// reset
		S_IM_CNR_OUTPUT_MNG[ch].bankArea		= 0;	// reset
		S_IM_CNR_OUTPUT_MNG[ch].useBankNum		= addrInfo->useBankNum;
		for( outAddrCnt = 0; outAddrCnt < addrInfo->useBankNum; outAddrCnt++ ){
			S_IM_CNR_OUTPUT_MNG[ch].outputAddr[outAddrCnt]	= addrInfo->wCAddr[outAddrCnt];
		}
		IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= addrInfo->wCAddr[0];
	}

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
CNR(OTF) increment output address index
*/
INT32 im_cnrone_otf_increment_outaddr_index(ImCnrone *self, UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch > ImCnr_CH_1) {
		Ddim_Assertion(("im_cnrone_otf_increment_outaddr_index() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	// Update output address
	++S_IM_CNR_OUTPUT_MNG[ch].bankArea;
	S_IM_CNR_OUTPUT_MNG[ch].bankArea		= ImCnr_ADDR_BNK_LIMIT( S_IM_CNR_OUTPUT_MNG[ch].bankArea,
			S_IM_CNR_OUTPUT_MNG[ch].useBankNum );
	IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= S_IM_CNR_OUTPUT_MNG[ch].outputAddr[S_IM_CNR_OUTPUT_MNG[ch].bankArea];

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
CNR(OFL) Control set AXI bus I/F Control
*/
INT32 im_cnrone_ofl_ctrl_Axi(ImCnrone *self, UCHAR ch, const ImCnrOflAxi* const axiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_Axi() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( axiCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_Axi() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWPROT		= axiCtrl->writeProtectionType;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARPROT		= axiCtrl->readProtectionType;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWCACHE	= axiCtrl->writeCacheType;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARCACHE	= axiCtrl->readCacheType;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}


/*
CNR(OTF) Control set AXI bus I/F Control
*/
INT32 im_cnrone_otf_ctrl_axi(ImCnrone *self, UCHAR ch, const ImCnrOtfAxi* const axiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl_axi() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( axiCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl_axi() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWPROT		= axiCtrl->writeProtectionType;
	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWCACHE	= axiCtrl->writeCacheType;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}


/*
Get AXI bus I/F Status
*/
INT32 im_cnrone_ofl_get_axi_status(ImCnrone *self, UCHAR ch, ImCnrOflAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (ImCnr_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnrone_ofl_get_axi_status() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnrone_ofl_get_axi_status() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	sts->readChannelResponse = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP;
	sts->writeChannelResponse = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnrone_otf_get_axi_status(ImCnrone *self, UCHAR ch, ImCnrOtfAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (ImCnr_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnrone_otf_get_axi_status() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnrone_otf_get_axi_status() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	sts->writeChannelResponse = IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnrone_ofl_ctrl_c(ImCnrone *self, UCHAR ch, const ImCnrCtrlC* const sprCtrlC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_c() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.CSPREN.bit.CSPREN = sprCtrlC->enable;
	IO_CNR(ch)->OFL_CSPR_REG.CGDKEN.bit.CGDKEN = sprCtrlC->gradationKeepEn;

	IO_CNR(ch)->OFL_CSPR_REG.MCEN.bit.MCEN = sprCtrlC->midFreqNr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_0 = sprCtrlC->midFreqNr.hYThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_1 = sprCtrlC->midFreqNr.hYThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_2 = sprCtrlC->midFreqNr.hYThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_3 = sprCtrlC->midFreqNr.hYThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_0 = sprCtrlC->midFreqNr.vYThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_1 = sprCtrlC->midFreqNr.vYThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_2 = sprCtrlC->midFreqNr.vYThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_3 = sprCtrlC->midFreqNr.vYThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_0 = sprCtrlC->midFreqNr.hCThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_1 = sprCtrlC->midFreqNr.hCThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_2 = sprCtrlC->midFreqNr.hCThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_3 = sprCtrlC->midFreqNr.hCThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_0 = sprCtrlC->midFreqNr.vCThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_1 = sprCtrlC->midFreqNr.vCThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_2 = sprCtrlC->midFreqNr.vCThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_3 = sprCtrlC->midFreqNr.vCThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = sprCtrlC->midFreqNr.yThresholdCor;
	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = sprCtrlC->midFreqNr.yThresholdGain;

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYM.bit.MCYDYM = sprCtrlC->midFreqNr.yThresholdDymEn;

	IO_CNR(ch)->OFL_CSPR_REG.MCYSCL.bit.MCYSCL = sprCtrlC->midFreqNr.yThresholdSclEn;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCL.bit.MCSSCL = sprCtrlC->midFreqNr.cYThresholdSclEn;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCL.bit.MCCSCL = sprCtrlC->midFreqNr.cThresholdSclEn;

	IO_CNR(ch)->OFL_CSPR_REG.LCEN.bit.LCEN = sprCtrlC->lowFreqNr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_0 = sprCtrlC->lowFreqNr.hYThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_1 = sprCtrlC->lowFreqNr.hYThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_2 = sprCtrlC->lowFreqNr.hYThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_3 = sprCtrlC->lowFreqNr.hYThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_0 = sprCtrlC->lowFreqNr.vYThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_1 = sprCtrlC->lowFreqNr.vYThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_2 = sprCtrlC->lowFreqNr.vYThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_3 = sprCtrlC->lowFreqNr.vYThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_0 = sprCtrlC->lowFreqNr.hCThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_1 = sprCtrlC->lowFreqNr.hCThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_2 = sprCtrlC->lowFreqNr.hCThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_3 = sprCtrlC->lowFreqNr.hCThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_0 = sprCtrlC->lowFreqNr.vCThreshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_1 = sprCtrlC->lowFreqNr.vCThreshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_2 = sprCtrlC->lowFreqNr.vCThreshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_3 = sprCtrlC->lowFreqNr.vCThreshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = sprCtrlC->lowFreqNr.yThresholdCor;
	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = sprCtrlC->lowFreqNr.yThresholdGain;

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYM.bit.LCYDYM = sprCtrlC->lowFreqNr.yThresholdDymEn;

	IO_CNR(ch)->OFL_CSPR_REG.LCYSCL.bit.LCYSCL = sprCtrlC->lowFreqNr.yThresholdSclEn;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCL.bit.LCSSCL = sprCtrlC->lowFreqNr.cYThresholdSclEn;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->lowFreqNr.cThresholdSclEn;

	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTEN = sprCtrlC->whiteningEnable;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTVAL = sprCtrlC->whiteningValue;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTBASE = sprCtrlC->whiteningBase;

	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.BLENDMD = sprCtrlC->cBlendMd;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSPRALPBD = sprCtrlC->cAlphaBlend;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGEN = sprCtrlC->cRange;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGMD = sprCtrlC->cRangeMode;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnrone_otf_ctrl_c(ImCnrone *self, UCHAR ch, const ImCnrCtrlC* const sprCtrlC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl_c() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl_c() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OTF_CSPR_REG.CSPREN.bit.CSPREN = sprCtrlC->enable;
	IO_CNR(ch)->OTF_CSPR_REG.CGDKEN.bit.CGDKEN = sprCtrlC->gradationKeepEn;

	IO_CNR(ch)->OTF_CSPR_REG.MCEN.bit.MCEN = sprCtrlC->midFreqNr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_0 = sprCtrlC->midFreqNr.hYThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_1 = sprCtrlC->midFreqNr.hYThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_2 = sprCtrlC->midFreqNr.hYThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_3 = sprCtrlC->midFreqNr.hYThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_0 = sprCtrlC->midFreqNr.vYThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_1 = sprCtrlC->midFreqNr.vYThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_2 = sprCtrlC->midFreqNr.vYThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_3 = sprCtrlC->midFreqNr.vYThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_0 = sprCtrlC->midFreqNr.hCThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_1 = sprCtrlC->midFreqNr.hCThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_2 = sprCtrlC->midFreqNr.hCThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_3 = sprCtrlC->midFreqNr.hCThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_0 = sprCtrlC->midFreqNr.vCThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_1 = sprCtrlC->midFreqNr.vCThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_2 = sprCtrlC->midFreqNr.vCThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_3 = sprCtrlC->midFreqNr.vCThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = sprCtrlC->midFreqNr.yThresholdCor;
	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = sprCtrlC->midFreqNr.yThresholdGain;

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYM.bit.MCYDYM = sprCtrlC->midFreqNr.yThresholdDymEn;

	IO_CNR(ch)->OTF_CSPR_REG.MCYSCL.bit.MCYSCL = sprCtrlC->midFreqNr.yThresholdSclEn;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCL.bit.MCSSCL = sprCtrlC->midFreqNr.cYThresholdSclEn;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCL.bit.MCCSCL = sprCtrlC->midFreqNr.cThresholdSclEn;

	IO_CNR(ch)->OTF_CSPR_REG.LCEN.bit.LCEN = sprCtrlC->lowFreqNr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_0 = sprCtrlC->lowFreqNr.hYThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_1 = sprCtrlC->lowFreqNr.hYThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_2 = sprCtrlC->lowFreqNr.hYThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_3 = sprCtrlC->lowFreqNr.hYThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_0 = sprCtrlC->lowFreqNr.vYThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_1 = sprCtrlC->lowFreqNr.vYThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_2 = sprCtrlC->lowFreqNr.vYThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_3 = sprCtrlC->lowFreqNr.vYThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_0 = sprCtrlC->lowFreqNr.hCThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_1 = sprCtrlC->lowFreqNr.hCThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_2 = sprCtrlC->lowFreqNr.hCThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_3 = sprCtrlC->lowFreqNr.hCThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_0 = sprCtrlC->lowFreqNr.vCThreshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_1 = sprCtrlC->lowFreqNr.vCThreshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_2 = sprCtrlC->lowFreqNr.vCThreshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_3 = sprCtrlC->lowFreqNr.vCThreshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = sprCtrlC->lowFreqNr.yThresholdCor;
	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = sprCtrlC->lowFreqNr.yThresholdGain;

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYM.bit.LCYDYM = sprCtrlC->lowFreqNr.yThresholdDymEn;

	IO_CNR(ch)->OTF_CSPR_REG.LCYSCL.bit.LCYSCL = sprCtrlC->lowFreqNr.yThresholdSclEn;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->lowFreqNr.cThresholdSclEn;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->lowFreqNr.cThresholdSclEn;

	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTEN = sprCtrlC->whiteningEnable;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTVAL = sprCtrlC->whiteningValue;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTBASE = sprCtrlC->whiteningBase;

	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.BLENDMD = sprCtrlC->cBlendMd;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSPRALPBD = sprCtrlC->cAlphaBlend;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGEN = sprCtrlC->cRange;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGMD = sprCtrlC->cRangeMode;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR setting for Y for Off Line
*/
INT32 im_cnrone_ofl_ctrl_y(ImCnrone *self, UCHAR ch, const ImCnrOflCtrlY* const sprCtrlY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCtrlY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_y() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_REG_YSPR.YSPREN.bit.YSPREN = sprCtrlY->enable;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRMD = sprCtrlY->thresholdType;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRFE = sprCtrlY->level;

	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYV = sprCtrlY->vYThreshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYH = sprCtrlY->hYThreshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECV = sprCtrlY->vCThreshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECH = sprCtrlY->hCThreshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRALPBD.bit.YSPRALPBD = sprCtrlY->alphaBlendRatio;

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR table for Y
*/
INT32 im_cnrone_ofl_set_yspr_table(ImCnrone *self, UCHAR ch, const ImCnrTable* const sprYspr )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_set_yspr_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprYspr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_set_yspr_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_1	= sprYspr->bd1;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_2	= sprYspr->bd2;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_3	= sprYspr->bd3;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD1.bit.YSPRDYEYBD_4	= sprYspr->bd4;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYBD.YSPRDYEYBD2.bit.YSPRDYEYBD_5	= sprYspr->bd5;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_0	= sprYspr->of0;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_1	= sprYspr->of1;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_2	= sprYspr->of2;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF1.bit.YSPRDYEYOF_3	= sprYspr->of3;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_4	= sprYspr->of4;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYOF.YSPRDYEYOF2.bit.YSPRDYEYOF_5	= sprYspr->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, sprYspr->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_1, sprYspr->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_2, sprYspr->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, sprYspr->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, sprYspr->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, sprYspr->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnrone_ofl_set_cspr_mid_y_table(ImCnrone *self, UCHAR ch, const ImCnrTable* const sprCsprMidY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= ImCnr_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return ImCnr_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return ImCnr_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	ImCnr_DSB();

	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_1	= sprCsprMidY->bd1;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_2	= sprCsprMidY->bd2;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_3	= sprCsprMidY->bd3;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD1.bit.MCYSCLBD_4	= sprCsprMidY->bd4;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLBD.MCYSCLBD2.bit.MCYSCLBD_5	= sprCsprMidY->bd5;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_0	= sprCsprMidY->of0;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_1	= sprCsprMidY->of1;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_2	= sprCsprMidY->of2;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF1.bit.MCYSCLOF_3	= sprCsprMidY->of3;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_4	= sprCsprMidY->of4;
	IO_CNR(ch)->OFL_CSPR_REG.MCYSCLOF.MCYSCLOF2.bit.MCYSCLOF_5	= sprCsprMidY->of5;

	// write signed data
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, sprCsprMidY->gain0 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, sprCsprMidY->gain1 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, sprCsprMidY->gain2 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, sprCsprMidY->gain3 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, sprCsprMidY->gain4 );
	ImCnr_SET_REG_SIGNED( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, sprCsprMidY->gain5 );

	im_cnrone_off_pclk(ch);
	ImCnr_DSB();

	return D_DDIM_OK;
}

ImCnrone* im_cnrone_new(void)
{
	ImCnrone *self = g_object_new(IM_TYPE_CNRONE, NULL);
	return self;
}
