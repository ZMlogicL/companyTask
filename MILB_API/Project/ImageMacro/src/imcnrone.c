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
VOID im_cnrone_on_pclk( UCHAR ch )
{
#ifdef CO_ACT_CNR_PCLK
	INT32 intkey;

	intkey = Dd_ARM_DI();

	if (ch == D_IM_CNR_CH_0) {
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(),
				~D_DD_TOP_CNR1AP_BIT );
	}
	else if (ch == D_IM_CNR_CH_1) {
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AP_BIT );
	}
	else {
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), ~D_DD_TOP_CNR1AP_BIT );
		Dd_Top_Start_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), ~D_DD_TOP_CNR2AP_BIT );
	}

	Dd_ARM_EI( intkey );
#endif //CO_ACT_CNR_PCLK
}

// Stop CNR PCLK
VOID im_cnrone_off_pclk( UCHAR ch )
{
#ifdef CO_ACT_CNR_PCLK
	INT32 intkey;

	intkey = Dd_ARM_DI();

	if (ch == D_IM_CNR_CH_0) {
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AP_BIT );
	}
	else if (ch == D_IM_CNR_CH_1) {
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AP_BIT );
	}
	else {
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt1, &Dd_Top_Get_CLKSTOP11(), D_DD_TOP_CNR1AP_BIT );
		Dd_Top_Stop_Clock( (UCHAR*)&gIM_CNR_Pclk_Ctrl_Cnt2, &Dd_Top_Get_CLKSTOP13(), D_DD_TOP_CNR2AP_BIT );
	}

	Dd_ARM_EI( intkey );
#endif //CO_ACT_CNR_PCLK
}

/*
The semaphore of CNR is acquired for Off Line
*/
INT32 im_cnrone_ofl_open( UCHAR ch, const INT32 tmout )
{
	DDIM_USER_ID sid;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_open() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ) {
		Ddim_Assertion(("I:im_cnrone_ofl_open. input param error. tmout = %x\n", tmout));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == D_IM_CNR_CH_2) {
		for( UCHAR loop = D_IM_CNR_CH_0; loop <= D_IM_CNR_CH_1; loop++ ){
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
				return D_IM_CNR_SEM_TIMEOUT_ERR;
			}

			if( D_DDIM_USER_E_OK != ercd ) {
				// CNR processing error
				// CNR processing error
				Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Error\n"));
				return D_IM_CNR_SEM_NG;
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
			return D_IM_CNR_SEM_TIMEOUT_ERR;
		}

		if( D_DDIM_USER_E_OK != ercd ) {
			// CNR processing error
			// CNR processing error
			Ddim_Print(("I:im_cnrone_ofl_open() Error : Semaphore Get Error\n"));
			return D_IM_CNR_SEM_NG;
		}
	}

	return D_DDIM_OK;
}

/*
The semaphore of CNR is acquired for On The Fly
*/
INT32 im_cnrone_otf_open( UCHAR ch, const INT32 tmout )
{
	DDIM_USER_ID sid;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_open() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ) {
		Ddim_Assertion(("I:im_cnrone_otf_open. input param error. tmout = %x\n", tmout));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif	// CO_PARAM_CHECK

	if (ch == D_IM_CNR_CH_2) {
		for( UCHAR loop = D_IM_CNR_CH_0; loop <= D_IM_CNR_CH_1; loop++ ){
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
				return D_IM_CNR_SEM_TIMEOUT_ERR;
			}

			if( D_DDIM_USER_E_OK != ercd ) {
				// CNR processing error
				// CNR processing error
				Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Error\n"));
				return D_IM_CNR_SEM_NG;
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
			return D_IM_CNR_SEM_TIMEOUT_ERR;
		}

		if( D_DDIM_USER_E_OK != ercd ) {
			// CNR processing error
			// CNR processing error
			Ddim_Print(("I:im_cnrone_otf_open() Error : Semaphore Get Error\n"));
			return D_IM_CNR_SEM_NG;
		}
	}

	return D_DDIM_OK;
}

/*
CNR(OFL) Control
*/
INT32 im_cnrone_ofl_ctrl( UCHAR ch, const ImCnrOflCtrl* const sprCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

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

	IO_CNR(ch)->OFL_REG_RW.RYDEF.bit.RYDEF	= sprCtrl->r_y_width;	// Y width for read			@RYDEF
	IO_CNR(ch)->OFL_REG_RW.RYTA.bit.RYTA	= sprCtrl->r_y_addr;	// Y address for read		@RYTA

	IO_CNR(ch)->OFL_REG_RW.RCDEF.bit.RCDEF	= sprCtrl->r_c_width;	// CbCr width for read		@RCDEF
	IO_CNR(ch)->OFL_REG_RW.RCBTA.bit.RCBTA	= sprCtrl->r_cb_addr;	// Cb address for read		@RCBTA
	IO_CNR(ch)->OFL_REG_RW.RCRTA.bit.RCRTA	= sprCtrl->r_cr_addr;	// Cr address for read		@RCRTA

	IO_CNR(ch)->OFL_REG_RW.WYDEF.bit.WYDEF	= sprCtrl->w_y_width;	// Y width for write		@WYDEF
	IO_CNR(ch)->OFL_REG_RW.WYTA.bit.WYTA	= sprCtrl->w_y_addr;	// Y address for write		@WYTA

	IO_CNR(ch)->OFL_REG_RW.WCDEF.bit.WCDEF	= sprCtrl->w_c_width;	// CbCr width for write		@WCDEF
	IO_CNR(ch)->OFL_REG_RW.WCBTA.bit.WCBTA	= sprCtrl->w_cb_addr;	// Cb address for write		@WCBTA
	IO_CNR(ch)->OFL_REG_RW.WCRTA.bit.WCRTA	= sprCtrl->w_cr_addr;	// Cr address for write		@WCRTA

	IO_CNR(ch)->OFL_REG_RW.TMPTA.bit.TMPTA	= sprCtrl->work_addr;	// Address fir work area	@TMPTA

	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVT	= sprCtrl->divide_top;		// Virtucal process devide	@VDIVT
	IO_CNR(ch)->OFL_REG_RW.VDIV.bit.VDIVB	= sprCtrl->divide_bot;		// Virtucal process devide	@VDIVB

	if( ch == D_IM_CNR_CH_2 ){
		gIM_CNR_OFL_CallBack_Func[D_IM_CNR_CH_0]	= sprCtrl->pCallBack;
		gIM_CNR_OFL_CallBack_Func[D_IM_CNR_CH_1]	= sprCtrl->pCallBack;
		gIM_CNR_OFL_UserParam[D_IM_CNR_CH_0]		= sprCtrl->user_param;
		gIM_CNR_OFL_UserParam[D_IM_CNR_CH_1]		= sprCtrl->user_param;
	}
	else{
		gIM_CNR_OFL_CallBack_Func[ch]	= sprCtrl->pCallBack;
		gIM_CNR_OFL_UserParam[ch]		= sprCtrl->user_param;
	}

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();
	return D_DDIM_OK;
}

/*
CNR(OTF) Control
*/
INT32 im_cnrone_otf_ctrl( UCHAR ch, const ImCnrOtfCtrl* const sprCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif
	if (sprCtrl->width < 96 || sprCtrl->width > 2360) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input width error : %d\n", sprCtrl->width));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (sprCtrl->lines < 72 || sprCtrl->lines > 4096) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input lines error : %d\n", sprCtrl->lines));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if ( (sprCtrl->w_offset_x != 0)&&(sprCtrl->w_offset_x < 96 || sprCtrl->w_offset_x > 2360)) {
		Ddim_Assertion(("im_cnrone_otf_ctrl() error. input w_offset_x error : %lu\n", sprCtrl->w_offset_x));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if (sprCtrl->video_format == 1){
		if (sprCtrl->w_c_width % 128){
			Ddim_Assertion(("im_cnrone_otf_ctrl() error. input w_c_width error : %lu\n", sprCtrl->w_c_width));
			return D_IM_CNR_INPUT_PARAM_ERROR;
		}
		if( sprCtrl->mode != ImCnr_OTF_YCC_MODE_YCC420_SIMPLE ){
			Ddim_Assertion(("im_cnrone_otf_ctrl() error. mode error : %d\n", sprCtrl->mode));
			return D_IM_CNR_INPUT_PARAM_ERROR;
		}
	}

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

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
	IO_CNR(ch)->OTF_REG_RW.SPRMOD.bit.CNRVFM		= sprCtrl->video_format;	// SPR video format			@CNRVFM

	IO_CNR(ch)->OTF_REG_RW.HSIZE.bit.HSIZE			= sprCtrl->width;			// SPR valid data width		@HSIZE
	IO_CNR(ch)->OTF_REG_RW.VSIZE.bit.VSIZE			= sprCtrl->lines;			// SPR valid data lines		@VSIZE

	IO_CNR(ch)->OTF_REG_RW.WCDEF.bit.WCDEF			= sprCtrl->w_c_width;		// CbCr width for write		@WCDEF

	IO_CNR(ch)->OTF_REG_RW.CNRWOFSX.bit.CNRWOFSX	= sprCtrl->w_offset_x;		// write offset X direction	@CNRWOFSX

	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVL			= sprCtrl->divide_left;	// Virtucal process devide	@HDIVL
	IO_CNR(ch)->OTF_REG_RW.HDIV.bit.HDIVR			= sprCtrl->divide_right;	// Virtucal process devide	@VDIVR

	IO_CNR(ch)->OTF_REG_RW.SPRTRG.bit.CNRCSE		= sprCtrl->continuous;		// Continuous processing	@CNRCSE

	if( ch == D_IM_CNR_CH_2 ){
		gIM_CNR_OTF_CallBack_Func[D_IM_CNR_CH_0]	= sprCtrl->pCallBack;
		gIM_CNR_OTF_CallBack_Func[D_IM_CNR_CH_1]	= sprCtrl->pCallBack;
		gIM_CNR_OTF_UserParam[D_IM_CNR_CH_0]		= sprCtrl->user_param;
		gIM_CNR_OTF_UserParam[D_IM_CNR_CH_1]		= sprCtrl->user_param;
	}
	else{
		gIM_CNR_OTF_CallBack_Func[ch]				= sprCtrl->pCallBack;
		gIM_CNR_OTF_UserParam[ch]					= sprCtrl->user_param;
	}

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OTF) Set output address information
*/
INT32 im_cnrone_otf_set_outaddr_info( UCHAR ch, const ImCnrOtfOutaddrInfo* const addrInfo )
{
	INT32 out_addr_cnt;

#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_set_outaddr_info() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( addrInfo == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_set_outaddr_info() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( (addrInfo->use_bank_num == 0)||(addrInfo->use_bank_num > D_IM_CNR_ADDR_BANK_MAX) ){
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_set_outaddr_info() use_bank_num parameter is error : %d\n",
				addrInfo->use_bank_num));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

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

	if( ch == D_IM_CNR_CH_2 ){
		// set output address information	@WCTA
		gIM_CNR_Latest_Mng[D_IM_CNR_CH_0].bank_area			= 0;	// reset
		gIM_CNR_Latest_Mng[D_IM_CNR_CH_1].bank_area			= 0;	// reset
		gIM_CNR_Latest_Mng[D_IM_CNR_CH_0].addr				= 0;	// reset
		gIM_CNR_Latest_Mng[D_IM_CNR_CH_1].addr				= 0;	// reset
		gIM_CNR_Output_Mng[D_IM_CNR_CH_0].bank_area			= 0;	// reset
		gIM_CNR_Output_Mng[D_IM_CNR_CH_1].bank_area			= 0;	// reset
		gIM_CNR_Output_Mng[D_IM_CNR_CH_0].use_bank_num		= addrInfo->use_bank_num;
		gIM_CNR_Output_Mng[D_IM_CNR_CH_1].use_bank_num		= addrInfo->use_bank_num;
		for( out_addr_cnt = 0; out_addr_cnt < addrInfo->use_bank_num; out_addr_cnt++ ){
			gIM_CNR_Output_Mng[D_IM_CNR_CH_0].output_addr[out_addr_cnt]	= addrInfo->w_c_addr[out_addr_cnt];
			gIM_CNR_Output_Mng[D_IM_CNR_CH_1].output_addr[out_addr_cnt]	= addrInfo->w_c_addr[out_addr_cnt];
		}
		IO_CNR(D_IM_CNR_CH_0)->OTF_REG_RW.WCTA.bit.WCTA		= addrInfo->w_c_addr[0];
		IO_CNR(D_IM_CNR_CH_1)->OTF_REG_RW.WCTA.bit.WCTA		= addrInfo->w_c_addr[0];
	}
	else{
		// set output address information	@WCTA
		gIM_CNR_Latest_Mng[ch].bank_area		= 0;	// reset
		gIM_CNR_Latest_Mng[ch].addr				= 0;	// reset
		gIM_CNR_Output_Mng[ch].bank_area		= 0;	// reset
		gIM_CNR_Output_Mng[ch].use_bank_num		= addrInfo->use_bank_num;
		for( out_addr_cnt = 0; out_addr_cnt < addrInfo->use_bank_num; out_addr_cnt++ ){
			gIM_CNR_Output_Mng[ch].output_addr[out_addr_cnt]	= addrInfo->w_c_addr[out_addr_cnt];
		}
		IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= addrInfo->w_c_addr[0];
	}

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OTF) increment output address index
*/
INT32 im_cnrone_otf_increment_outaddr_index( UCHAR ch )
{
#ifdef CO_PARAM_CHECK
	if (ch > D_IM_CNR_CH_1) {
		Ddim_Assertion(("im_cnrone_otf_increment_outaddr_index() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	// Update output address
	++gIM_CNR_Output_Mng[ch].bank_area;
	gIM_CNR_Output_Mng[ch].bank_area		= ADDR_BNK_LIMIT( gIM_CNR_Output_Mng[ch].bank_area,
			gIM_CNR_Output_Mng[ch].use_bank_num );
	IO_CNR(ch)->OTF_REG_RW.WCTA.bit.WCTA	= gIM_CNR_Output_Mng[ch].output_addr[gIM_CNR_Output_Mng[ch].bank_area];

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
CNR(OFL) Control set AXI bus I/F Control
*/
INT32 im_cnrone_ofl_ctrl_Axi( UCHAR ch, const ImCnrOflAxi* const axiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_Axi() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axiCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_Axi() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWPROT		= axiCtrl->write_protection_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARPROT		= axiCtrl->read_protection_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.AWCACHE	= axiCtrl->write_cache_type;
	IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.ARCACHE	= axiCtrl->read_cache_type;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}


/*
CNR(OTF) Control set AXI bus I/F Control
*/
INT32 im_cnrone_otf_ctrl_axi( UCHAR ch, const ImCnrOtfAxi* const axiCtrl )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl_axi() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( axiCtrl == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl_axi() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWPROT		= axiCtrl->write_protection_type;
	IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.AWCACHE	= axiCtrl->write_cache_type;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}


/*
Get AXI bus I/F Status
*/
INT32 im_cnrone_ofl_get_axi_status( UCHAR ch, ImCnrOflAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnrone_ofl_get_axi_status() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnrone_ofl_get_axi_status() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	sts->read_channel_response = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.RRESP;
	sts->write_channel_response = IO_CNR(ch)->OFL_REG_RW.SPRAXISET.bit.WRESP;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 im_cnrone_otf_get_axi_status( UCHAR ch, ImCnrOtfAxiStatus* const sts )
{
#ifdef CO_PARAM_CHECK
	if (ch >= (D_IM_CNR_CH_NUM_MAX-1)) {
		Ddim_Assertion(("im_cnrone_otf_get_axi_status() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sts == NULL ) {
		// sts setting error
		Ddim_Assertion(("I:im_cnrone_otf_get_axi_status() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	sts->write_channel_response = IO_CNR(ch)->OTF_REG_RW.SPRAXISET.bit.WRESP;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnrone_ofl_ctrl_c( UCHAR ch, const ImCnrCtrlC* const sprCtrlC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_c() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_CSPR_REG.CSPREN.bit.CSPREN = sprCtrlC->enable;
	IO_CNR(ch)->OFL_CSPR_REG.CGDKEN.bit.CGDKEN = sprCtrlC->gradation_keep_en;

	IO_CNR(ch)->OFL_CSPR_REG.MCEN.bit.MCEN = sprCtrlC->mid_freq_nr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_0 = sprCtrlC->mid_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_1 = sprCtrlC->mid_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_2 = sprCtrlC->mid_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHH.bit.MCYTHH_3 = sprCtrlC->mid_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_0 = sprCtrlC->mid_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_1 = sprCtrlC->mid_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_2 = sprCtrlC->mid_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCYTHV.bit.MCYTHV_3 = sprCtrlC->mid_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_0 = sprCtrlC->mid_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_1 = sprCtrlC->mid_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_2 = sprCtrlC->mid_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHH.bit.MCCTHH_3 = sprCtrlC->mid_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_0 = sprCtrlC->mid_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_1 = sprCtrlC->mid_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_2 = sprCtrlC->mid_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.MCCTHV.bit.MCCTHV_3 = sprCtrlC->mid_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = sprCtrlC->mid_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OFL_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = sprCtrlC->mid_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OFL_CSPR_REG.MCYDYM.bit.MCYDYM = sprCtrlC->mid_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OFL_CSPR_REG.MCYSCL.bit.MCYSCL = sprCtrlC->mid_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.MCSSCL.bit.MCSSCL = sprCtrlC->mid_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.MCCSCL.bit.MCCSCL = sprCtrlC->mid_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OFL_CSPR_REG.LCEN.bit.LCEN = sprCtrlC->low_freq_nr.enable;

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_0 = sprCtrlC->low_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_1 = sprCtrlC->low_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_2 = sprCtrlC->low_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHH.bit.LCYTHH_3 = sprCtrlC->low_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_0 = sprCtrlC->low_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_1 = sprCtrlC->low_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_2 = sprCtrlC->low_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCYTHV.bit.LCYTHV_3 = sprCtrlC->low_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_0 = sprCtrlC->low_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_1 = sprCtrlC->low_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_2 = sprCtrlC->low_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHH.bit.LCCTHH_3 = sprCtrlC->low_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_0 = sprCtrlC->low_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_1 = sprCtrlC->low_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_2 = sprCtrlC->low_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OFL_CSPR_REG.LCCTHV.bit.LCCTHV_3 = sprCtrlC->low_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = sprCtrlC->low_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OFL_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = sprCtrlC->low_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OFL_CSPR_REG.LCYDYM.bit.LCYDYM = sprCtrlC->low_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OFL_CSPR_REG.LCYSCL.bit.LCYSCL = sprCtrlC->low_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.LCSSCL.bit.LCSSCL = sprCtrlC->low_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OFL_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->low_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTEN = sprCtrlC->whitening_enable;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTVAL = sprCtrlC->whitening_value;
	IO_CNR(ch)->OFL_CSPR_REG.WHTMD.bit.WHTBASE = sprCtrlC->whitening_base;

	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.BLENDMD = sprCtrlC->c_blend_md;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSPRALPBD = sprCtrlC->c_alpha_blend;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGEN = sprCtrlC->c_range;
	IO_CNR(ch)->OFL_CSPR_REG.BLEND.bit.CSRGMD = sprCtrlC->c_range_mode;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for CbCr
*/
INT32 im_cnrone_otf_ctrl_c( UCHAR ch, const ImCnrCtrlC* const sprCtrlC )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_otf_ctrl_c() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCtrlC == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_otf_ctrl_c() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OTF_CSPR_REG.CSPREN.bit.CSPREN = sprCtrlC->enable;
	IO_CNR(ch)->OTF_CSPR_REG.CGDKEN.bit.CGDKEN = sprCtrlC->gradation_keep_en;

	IO_CNR(ch)->OTF_CSPR_REG.MCEN.bit.MCEN = sprCtrlC->mid_freq_nr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_0 = sprCtrlC->mid_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_1 = sprCtrlC->mid_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_2 = sprCtrlC->mid_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHH.bit.MCYTHH_3 = sprCtrlC->mid_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_0 = sprCtrlC->mid_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_1 = sprCtrlC->mid_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_2 = sprCtrlC->mid_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCYTHV.bit.MCYTHV_3 = sprCtrlC->mid_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_0 = sprCtrlC->mid_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_1 = sprCtrlC->mid_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_2 = sprCtrlC->mid_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHH.bit.MCCTHH_3 = sprCtrlC->mid_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_0 = sprCtrlC->mid_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_1 = sprCtrlC->mid_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_2 = sprCtrlC->mid_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.MCCTHV.bit.MCCTHV_3 = sprCtrlC->mid_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYCR = sprCtrlC->mid_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OTF_CSPR_REG.MCYDYMDT.bit.MCYDYMYG = sprCtrlC->mid_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OTF_CSPR_REG.MCYDYM.bit.MCYDYM = sprCtrlC->mid_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OTF_CSPR_REG.MCYSCL.bit.MCYSCL = sprCtrlC->mid_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.MCSSCL.bit.MCSSCL = sprCtrlC->mid_freq_nr.c_y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.MCCSCL.bit.MCCSCL = sprCtrlC->mid_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OTF_CSPR_REG.LCEN.bit.LCEN = sprCtrlC->low_freq_nr.enable;

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_0 = sprCtrlC->low_freq_nr.h_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_1 = sprCtrlC->low_freq_nr.h_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_2 = sprCtrlC->low_freq_nr.h_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHH.bit.LCYTHH_3 = sprCtrlC->low_freq_nr.h_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_0 = sprCtrlC->low_freq_nr.v_y_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_1 = sprCtrlC->low_freq_nr.v_y_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_2 = sprCtrlC->low_freq_nr.v_y_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCYTHV.bit.LCYTHV_3 = sprCtrlC->low_freq_nr.v_y_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_0 = sprCtrlC->low_freq_nr.h_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_1 = sprCtrlC->low_freq_nr.h_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_2 = sprCtrlC->low_freq_nr.h_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHH.bit.LCCTHH_3 = sprCtrlC->low_freq_nr.h_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_0 = sprCtrlC->low_freq_nr.v_c_threshold[0];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_1 = sprCtrlC->low_freq_nr.v_c_threshold[1];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_2 = sprCtrlC->low_freq_nr.v_c_threshold[2];
	IO_CNR(ch)->OTF_CSPR_REG.LCCTHV.bit.LCCTHV_3 = sprCtrlC->low_freq_nr.v_c_threshold[3];

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYCR = sprCtrlC->low_freq_nr.y_threshold_cor;
	IO_CNR(ch)->OTF_CSPR_REG.LCYDYMDT.bit.LCYDYMYG = sprCtrlC->low_freq_nr.y_threshold_gain;

	IO_CNR(ch)->OTF_CSPR_REG.LCYDYM.bit.LCYDYM = sprCtrlC->low_freq_nr.y_threshold_dym_en;

	IO_CNR(ch)->OTF_CSPR_REG.LCYSCL.bit.LCYSCL = sprCtrlC->low_freq_nr.y_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->low_freq_nr.c_threshold_scl_en;
	IO_CNR(ch)->OTF_CSPR_REG.LCCSCL.bit.LCCSCL = sprCtrlC->low_freq_nr.c_threshold_scl_en;

	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTEN = sprCtrlC->whitening_enable;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTVAL = sprCtrlC->whitening_value;
	IO_CNR(ch)->OTF_CSPR_REG.WHTMD.bit.WHTBASE = sprCtrlC->whitening_base;

	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.BLENDMD = sprCtrlC->c_blend_md;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSPRALPBD = sprCtrlC->c_alpha_blend;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGEN = sprCtrlC->c_range;
	IO_CNR(ch)->OTF_CSPR_REG.BLEND.bit.CSRGMD = sprCtrlC->c_range_mode;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR setting for Y for Off Line
*/
INT32 im_cnrone_ofl_ctrl_y( UCHAR ch, const ImCnrOflCtrlY* const sprCtrlY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_ctrl_y() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCtrlY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_ctrl_y() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

	IO_CNR(ch)->OFL_REG_YSPR.YSPREN.bit.YSPREN = sprCtrlY->enable;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRMD = sprCtrlY->threshold_type;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRMODE.bit.YSPRFE = sprCtrlY->level;

	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYV = sprCtrlY->v_y_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEY.bit.YSPRFXEYH = sprCtrlY->h_y_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECV = sprCtrlY->v_c_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRFXEC.bit.YSPRFXECH = sprCtrlY->h_c_threshold;
	IO_CNR(ch)->OFL_REG_YSPR.YSPRALPBD.bit.YSPRALPBD = sprCtrlY->alpha_blend_ratio;

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR table for Y
*/
INT32 im_cnrone_ofl_set_yspr_table( UCHAR ch, const ImCnrTable* const sprYspr )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_set_yspr_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprYspr == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_set_yspr_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

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
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_0, sprYspr->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_1, sprYspr->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_2, sprYspr->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA1,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_1, YSPRDYEYGA_3, sprYspr->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_4, sprYspr->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_REG_YSPR.YSPRDYEYGA.YSPRDYEYGA2,
			union io_cnr_ofl_reg_yspr_ysprdyeyga_2, YSPRDYEYGA_5, sprYspr->gain5 );

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

/*
Set SPR Y table for Middle frequency CbCr
*/
INT32 im_cnrone_ofl_set_cspr_mid_y_table( UCHAR ch, const ImCnrTable* const sprCsprMidY )
{
#ifdef CO_PARAM_CHECK
	if (ch >= D_IM_CNR_CH_NUM_MAX) {
		Ddim_Assertion(("im_cnrone_ofl_set_cspr_mid_y_table() error. input channel error : %d\n", ch));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
	if( sprCsprMidY == NULL ) {
		// Parameter setting error
		Ddim_Assertion(("I:im_cnrone_ofl_set_cspr_mid_y_table() Parameter is NULL.\n"));
		return D_IM_CNR_INPUT_PARAM_ERROR;
	}
#endif

	im_cnrone_on_pclk(ch);
	Im_CNR_Dsb();

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
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_0, sprCsprMidY->gain0 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_1, sprCsprMidY->gain1 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_2, sprCsprMidY->gain2 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA1,
			union io_cnr_cspr_reg_mcysclga_1, MCYSCLGA_3, sprCsprMidY->gain3 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_4, sprCsprMidY->gain4 );
	im_cnr_set_reg_signed( IO_CNR(ch)->OFL_CSPR_REG.MCYSCLGA.MCYSCLGA2,
			union io_cnr_cspr_reg_mcysclga_2, MCYSCLGA_5, sprCsprMidY->gain5 );

	im_cnrone_off_pclk(ch);
	Im_CNR_Dsb();

	return D_DDIM_OK;
}

ImCnrone* im_cnrone_new(void)
{
	ImCnrone *self = g_object_new(IM_TYPE_CNRONE, NULL);
	return self;
}
