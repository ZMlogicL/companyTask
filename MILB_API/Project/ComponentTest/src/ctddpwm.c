/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief                	:CtDdPwm类
*@rely                		:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include "stdlib.h"
#include "string.h"
#include "peripheral.h"
#include "dd_pwm.h"
#include "dd_hdmac0.h"
#include "dd_top.h"
#include "dd_gic.h"
#include "ctddpwm.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPwm, ct_dd_pwm);
#define CT_DD_PWM_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPwmPrivate,CT_TYPE_DD_PWM))

/*
 * Definition
*/
#define	CtDdPwm_PWM_TEST

/*
 * Macro	只有自己用
 */
#define CtDdPwm_USER_LED13_On()		(*(volatile unsigned long*)0x1DFFB004 = 0x00400040)
#define CtDdPwm_USER_LED13_Off()		(*(volatile unsigned long*)0x1DFFB004 = 0x00400000)

struct _CtDdPwmPrivate
{
	T_DD_PWM_CTRL_CMN 						pwmCtrl;
	T_DD_PWM_CTRL_TIMER_E 				timerECtrl;
	T_DD_PWM_STEP 								pwmStp;
	T_DD_PWM_CTRL_TIMER_ABCD 		pwmCtrlAbcd;
};

static kuchar 	 S_G_DMA_CH;

/*----------------------------------------------------------------------
 * Enumeration
 *----------------------------------------------------------------------
 * Nothing Special
 *----------------------------------------------------------------------
 * Structure
 *----------------------------------------------------------------------
 * Nothing Special
 *----------------------------------------------------------------------
 * Global Data
 *----------------------------------------------------------------------
 * PWM stepping data
 */
static T_DD_PWM_TIMER_E_STEPS_DATA S_PWM_STEP_DATA[16] =
{
	/*
	 * cyc_num,	duty_num,				pulse_num(link)
	 */
	{	50625,		(50625 / 8 * 6),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 6),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 6),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 6),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 4),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 4),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 4),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 4),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 3),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 3),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 3),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 3),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 2),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 2),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 2),		{(kushort)(256 + (1 << 15))}	},
	{	50625,		(50625 / 8 * 2),		{(kushort)(256 + (0 << 15))}	}
};

static T_DD_PWM_TIMER_E_STEPS_DATA* S_PWM_STEP_DATA_P = S_PWM_STEP_DATA;

// PWM Under run data
static T_DD_PWM_TIMER_E_STEPS_DATA S_PWM_UNDER_RUN_DATA[4] =
{
	/*
	 * cyc_num,	duty_num,				pulse_num(link)
	 */
	{	52000,		(52000 / 8 * 2),		{(kushort)(512 + (1 << 15))}	},
	{	54000,		(54000 / 8 * 3),		{(kushort)(512 + (1 << 15))}	},
	{	56000,		(56000 / 8 * 4),		{(kushort)(512 + (1 << 15))}	},
	{	58000,		(58000 / 8 * 6),		{(kushort)(512 + (0 << 15))}	}
};

static T_DD_PWM_TIMER_E_STEPS_DATA* S_PWM_UNDER_RUN_DATA_P = S_PWM_UNDER_RUN_DATA;

/*
 * DECLS
 */
static void 		ctDdPwmCallback( kint32 ch, kint32 status );
static void 		ctDdPwnSetCtrl(T_DD_PWM_CTRL_CMN* ctrl,
			 	 	 	 	 	 	T_DD_PWM_CTRL_TIMER_ABCD* ctrlAbcd, kuchar ptnNo, kuchar ch);
#ifdef CtDdPwm_PWM_TEST
static void 		ctDdPwnSetCtrl2(CtDdPwm* self, kuchar ptnNo,kuchar cks,kulong cycNum);
#endif
static void 		ctDdPwmDmaStart(CtDdPwm* self, kuchar pwmCh, kuchar dmaCh );
static void 		ctDdPwmSetTimerECtrl( CtDdPwm* self,
									kuchar ptnNo, kuchar stepDataNum );
static void 		ctDdPwmSetGpio(void);

static void ct_dd_pwm_constructor(CtDdPwm *self) 
{
	CtDdPwmPrivate* priv = CT_DD_PWM_GET_PRIVATE(self);

	self->priv = priv;
	self->ret = D_DDIM_OK;
	self->tmout = D_DDIM_USER_SEM_WAIT_POL;
}

static void ct_dd_pwm_destructor(CtDdPwm *self) 
{
	self->priv = NULL;
}

/*
 * IMPL
 *
 * Local Method Definition
 */
static void ctDdPwmCallback( kint32 ch, kint32 status )
{
	kint32 ret = D_DDIM_OK;
	if ((status == D_DD_PWM_INT_STATUS_FORCE_STOP) || (status == D_DD_PWM_INT_STATUS_AUTO_STOP)) {
		Dd_PWM_Stop(ch);
	}

	ret = Dd_HDMAC0_Stop(S_G_DMA_CH);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Error Dd_HDMAC0_Stop!! self->ret = 0x%x\n",ret));
	}
	ret = Dd_HDMAC0_Close(S_G_DMA_CH);
	if(ret != D_DDIM_OK){
		Ddim_Print(("Error Dd_HDMAC0_Close!! self->ret = 0x%x\n", ret));
	}

	Ddim_Print(("ctDdPwmCallback() - status=%d\n", status));
}

/*
 * Local Function
 *
 * @brief  Command main function for timer32 test.
 * @param  T_PWM_CTRL * ctrl	:The number of parameters
 *		   kuchar ptnNo			:The value of parameters
 *								:
 *								:
 *								:
 * @return void
 */
static void ctDdPwnSetCtrl(T_DD_PWM_CTRL_CMN* ctrl,
								   T_DD_PWM_CTRL_TIMER_ABCD* ctrlAbcd,
								   kuchar ptnNo, kuchar ch)
{
	kuchar 	clk;
	kushort 	cycNum;
	kint32 		result;
	kuchar 	chInBlk;

	result = Dd_PWM_Calculate( 60000, &clk, &cycNum);
	if ((result != D_DDIM_OK) && (result != D_DD_PWM_OVERFLOW_OK)){
		// Error
		return;
	}

	chInBlk = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & ch;

	switch (ptnNo) {
		//one-shot & restart enable & soft trigger
		case 0:
			// (1)one-shot
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_ONE;
			// (1)restart enable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_ON;
			ctrl->clk_sel = clk;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			//(1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (0)interrupt disable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_OFF;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			//(0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			//Timer E disable
			ctrl->tim_e_enable = 0;
			//channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			//(50625) wave cycle(usec)
			ctrlAbcd->cyc_time = 60000;
			ctrlAbcd->cyc_num = cycNum;
			// 50%
			ctrlAbcd->duty_num = cycNum >> 1;
			//callback function pointer
			ctrl->pCallBack = NULL;
			break;
		// PWM & restart disable & soft trigger
		case 1:
			// (0)PWM
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_PWM;
			// (0)restart disable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_OFF;
			ctrl->clk_sel = clk;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (1)interrupt enable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_ON;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			// Timer E disable
			ctrl->tim_e_enable = 0;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			// (50625) wave cycle(usec)
			ctrlAbcd->cyc_time = 60000;
			ctrlAbcd->cyc_num = cycNum;
			// 50%
			ctrlAbcd->duty_num = cycNum >> 1;
			// callback function pointer
			ctrl->pCallBack = NULL;
			break;
		// PWM & restart disable & cycle trigger
		case 2:
			// (0)PWM
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_PWM;
			// (0)restart disable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_OFF;
			ctrl->clk_sel = clk;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (0)interrupt disable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_OFF;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (5)Timer ch1
			ctrl->in_trigger = D_DD_PWM_GCN_TSEL_TIM1;
			// Timer E disable
			ctrl->tim_e_enable = 0;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			// (50625) wave cycle(usec)
			ctrlAbcd->cyc_time = 60000;
			ctrlAbcd->cyc_num = cycNum;
			// 50%
			ctrlAbcd->duty_num = cycNum >> 1;
			// callback function pointer
			ctrl->pCallBack = NULL;
			break;

		default:
			break;
	}
}

#ifdef CtDdPwm_PWM_TEST
static void ctDdPwnSetCtrl2(CtDdPwm* self,
								   kuchar ptnNo,
								   kuchar cks,
								   kulong cycNum)
{
	CtDdPwmPrivate* priv = self->priv;
	T_DD_PWM_CTRL_CMN* ctrl = &priv->pwmCtrl;
	T_DD_PWM_CTRL_TIMER_ABCD* ctrlAbcd = &priv->pwmCtrlAbcd;
	kuchar ch = self->ch;
	kuchar chInBlk;

	chInBlk = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & ch;

	switch (ptnNo) {
		// one-shot & restart enable & soft trigger
		case 0:
			// (1)one-shot
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_ONE;
			// (1)restart enable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_ON;
			ctrl->clk_sel = cks;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (0)interrupt disable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_OFF;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			// Timer E disable
			ctrl->tim_e_enable = 0;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			// wave cycle(usec)
			ctrlAbcd->cyc_time = 0;
			ctrlAbcd->cyc_num = cycNum;
			// 50%
			ctrlAbcd->duty_num = cycNum >> 1;
			// callback function pointer
			ctrl->pCallBack = NULL;
			break;
		// PWM & restart disable & soft trigger
		case 1:
			// (0)PWM
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_PWM;
			// (0)restart disable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_OFF;
			ctrl->clk_sel = cks;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (1)interrupt enable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_ON;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			// Timer E disable
			ctrl->tim_e_enable = 0;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			// wave cycle(usec)
			ctrlAbcd->cyc_time = 0;
			ctrlAbcd->cyc_num = cycNum;
			// 50%
			ctrlAbcd->duty_num = cycNum >> 1;
			// callback function pointer
			ctrl->pCallBack = NULL;
			break;

		default:
			break;
	}
}
#endif

static void ctDdPwmDmaStart(CtDdPwm* self, kuchar pwmCh, kuchar dmaCh )
{
	kint32 ret;
	T_DD_HDMAC0_CTRL dmaCtrl;

	memset( &dmaCtrl, 0, sizeof(T_DD_HDMAC0_CTRL) );

	S_G_DMA_CH = dmaCh;
	// Channel open
	ret = Dd_HDMAC0_Open( dmaCh, D_DDIM_USER_SEM_WAIT_POL );
	if(ret != D_DDIM_OK){
		Ddim_Print(("Dd_HDMAC0_Open() error. self->ret=0x%x\n", ret));
		return;
	}

	dmaCtrl.config_a.word	 = 0;
	dmaCtrl.config_a.bit.is = D_DD_HDMAC0_IS_IDREQ_25 + (pwmCh >> 2);
	dmaCtrl.config_a.bit.bt = D_DD_HDMAC0_BT_NORMAL;
	// cycle, duty, pulse
	dmaCtrl.config_a.bit.bc = 3 - 1;
	// 16 - 8
	dmaCtrl.config_a.bit.tc = 8 - 1;

	dmaCtrl.config_b.word	 = 0;
	dmaCtrl.config_b.bit.ms = D_DD_HDMAC0_MS_BLK;
	dmaCtrl.config_b.bit.tw = D_DD_HDMAC0_TW_HWORD;
	dmaCtrl.config_b.bit.fs = D_DD_HDMAC0_FS_INCR;
	dmaCtrl.config_b.bit.fd = D_DD_HDMAC0_FD_FIX;
	dmaCtrl.config_b.bit.rc = D_DD_HDMAC0_RC_DISABLE;
	dmaCtrl.config_b.bit.rs = D_DD_HDMAC0_RS_ENABLE;
	dmaCtrl.config_b.bit.rd = D_DD_HDMAC0_RD_DISABLE;

	dmaCtrl.src_addr		 = (kulong)S_PWM_STEP_DATA_P;
	dmaCtrl.dst_addr		 = (kulong)(&(IO_PWMDMA[pwmCh >> 2].BFDTPT));
	dmaCtrl.int_handler	 = NULL;

	ret = Dd_HDMAC0_Ctrl_Common( dmaCh, &dmaCtrl );
	if(ret != D_DDIM_OK){
		Dd_HDMAC0_Close( dmaCh );
		Ddim_Print(("Dd_HDMAC0_Ctrl_Common() error. self->ret=0x%x\n", ret));
		return;
	}

	ret = Dd_HDMAC0_Start_Async( dmaCh );
	if(ret != D_DDIM_OK){
		Dd_HDMAC0_Close( dmaCh );
		Ddim_Print(("Dd_HDMAC0_Start_Async() error. self->ret=0x%x\n", ret));
		return;
	}
	return;
}

static void ctDdPwmSetTimerECtrl( CtDdPwm* self,
			kuchar ptnNo, kuchar stepDataNum )
{
	CtDdPwmPrivate* 					priv = self->priv;
	T_DD_PWM_CTRL_CMN* 		ctrl = &(priv->pwmCtrl);
	T_DD_PWM_CTRL_TIMER_E* 	timerECtrl = &(priv->timerECtrl);
	T_DD_PWM_STEP* 					pwmStp = &(priv->pwmStp);

	kuchar 									clk;
	kushort 									cycNum;
	kint32 										result;
	kint32 										ii;
	kuchar 									chInBlk;

	S_PWM_STEP_DATA_P = S_PWM_STEP_DATA;

	result = Dd_PWM_Calculate( 60000, &clk, &cycNum);
	if ((result != D_DDIM_OK) && (result != D_DD_PWM_OVERFLOW_OK)){
		// Error
		return;
	}

	chInBlk = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & self->ch;

	switch (ptnNo) {
		//PWM & restart disable & soft trigger
		case 1:
			// (0)PWM
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_PWM;
			// (0)restart disable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_OFF;
			ctrl->clk_sel = clk;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (0)interrupt disable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_OFF;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			// Timer E enable
			ctrl->tim_e_enable = 1;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			ctrl->pCallBack = (VP_CALLBACK_PWM)ctDdPwmCallback;
			timerECtrl->hold[0] = 0;
			timerECtrl->hold[1] = 0;
			timerECtrl->hold[2] = 0;
			timerECtrl->hold[3] = 0;
			timerECtrl->force_val[0] = 0;
			timerECtrl->force_val[1] = 0;
			timerECtrl->force_val[2] = 0;
			timerECtrl->force_val[3] = 0;
			timerECtrl->force[0] = 0;
			timerECtrl->force[1] = 0;
			timerECtrl->force[2] = 0;
			timerECtrl->force[3] = 0;
			// Inerrupt request timing for DMA
			timerECtrl->empty_dma_req	 = D_DD_PWM_PCHSET_RQTIM_4;
			// speed down setting under run error
			timerECtrl->undr_run_enable = D_DD_PWM_PCHSET_UDEN_OFF;
			// interrupt enable under run error
			timerECtrl->undr_run_int_err_enable = D_DD_PWM_PINTCT_UIE_ON;
			// interrupt enable for force stop
			timerECtrl->force_stop_int_enable = D_DD_PWM_PINTCT_FIE_ON;
			// interrupt enable for auto stop
			timerECtrl->auto_stop_int_enable = D_DD_PWM_PINTCT_AIE_ON;
			// interrupt enable for dma
			timerECtrl->dma_int_enable = D_DD_PWM_PINTCT_DRQE_OFF;
			timerECtrl->steps_data[0].cyc_num			 = cycNum;
			// 25%
			timerECtrl->steps_data[0].duty_num		 = cycNum >> 2;
			timerECtrl->steps_data[0].pulse_link.bit.pulse_num = 5;
			timerECtrl->steps_data[0].pulse_link.bit.link = 0;
			break;
		// DMA data transfer
		case 2:
			// (0)PWM
			ctrl->drv_mode = D_DD_PWM_PCNHL_MDSE_PWM;
			// (0)restart disable
			ctrl->restart_trig = D_DD_PWM_PCNHL_RTRG_OFF;
			ctrl->clk_sel = clk;
			// (0)output is "Low"
			ctrl->out_mask = D_DD_PWM_PCNHL_PGMS_L;
			// (1)rise edge
			ctrl->edge = D_DD_PWM_PCNHL_EGS_RISE;
			// (0)interrupt disable
			ctrl->int_enable = D_DD_PWM_PCNHL_IREN_OFF;
			// (1)agreement cycle
			ctrl->trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
			// (0)polarity usually
			ctrl->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			// (0-3)EN0-3 bit
			ctrl->in_trigger = chInBlk;
			// Timer E enable
			ctrl->tim_e_enable = 1;
			// channel assignment
			ctrl->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			ctrl->pCallBack = (VP_CALLBACK_PWM)ctDdPwmCallback;
			timerECtrl->hold[0] = 1;
			timerECtrl->hold[1] = 1;
			timerECtrl->hold[2] = 1;
			timerECtrl->hold[3] = 1;
			timerECtrl->force_val[0] = 0;
			timerECtrl->force_val[1] = 1;
			timerECtrl->force_val[2] = 1;
			timerECtrl->force_val[3] = 0;
			timerECtrl->force[0] = 1;
			timerECtrl->force[1] = 1;
			timerECtrl->force[2] = 1;
			timerECtrl->force[3] = 1;
			// Inerrupt request timing for DMA
			timerECtrl->empty_dma_req	 = D_DD_PWM_PCHSET_RQTIM_4;
			 // speed down setting under run error
			timerECtrl->undr_run_enable = D_DD_PWM_PCHSET_UDEN_OFF;
			// interrupt enable under run error
			timerECtrl->undr_run_int_err_enable = D_DD_PWM_PINTCT_UIE_ON;
			// interrupt enable for force stop
			timerECtrl->force_stop_int_enable = D_DD_PWM_PINTCT_FIE_ON;
			// interrupt enable for auto stop
			timerECtrl->auto_stop_int_enable = D_DD_PWM_PINTCT_AIE_ON;
			// interrupt enable for dma
			timerECtrl->dma_int_enable = D_DD_PWM_PINTCT_DRQE_ON;
			for( ii = 0; ii < D_DD_PWM_TIMER_E_STEPS; ii++ ) {
				timerECtrl->steps_data[ii].cyc_num = S_PWM_STEP_DATA_P->cyc_num;
				timerECtrl->steps_data[ii].duty_num = S_PWM_STEP_DATA_P->duty_num;
				timerECtrl->steps_data[ii].pulse_link.hword = S_PWM_STEP_DATA_P->pulse_link.hword;
				S_PWM_STEP_DATA_P++;
			}
			ctDdPwmDmaStart(self, self->ch, ((self->ch >> 2) + 1) );
			break;
		// Stepping motor utility
		case 3:
			// set timer_e ctrl data
			pwmStp->clk_sel = clk;
			pwmStp->polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
			pwmStp->ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
			pwmStp->hold[0] = 1;
			pwmStp->hold[1] = 1;
			pwmStp->hold[2] = 1;
			pwmStp->hold[3] = 1;
			pwmStp->force[0] = 0;
			pwmStp->force[1] = 1;
			pwmStp->force[2] = 1;
			pwmStp->force[3] = 0;
			pwmStp->step_data_num = stepDataNum;
			pwmStp->step_data = S_PWM_STEP_DATA_P;
			pwmStp->undr_run_data_num = 4;
			pwmStp->under_run_data = S_PWM_UNDER_RUN_DATA_P;
			pwmStp->pCallBack = (VP_CALLBACK_PWM)ctDdPwmCallback;
			break;

		default:
			break;
	}
}

static void ctDdPwmSetGpio(void)
{
	*(volatile unsigned long*)0x1DFFB104 = 0x00000040;

	IO_CHIPTOP.EPCR.bit.PA5 = 1;
	IO_CHIPTOP.PERSEL3.bit.AU1WPPS = 0;

	IO_CHIPTOP.EPCR.bit.P80 = 1;
//	IO_CHIPTOP.PDR.bit.P80 =
	IO_CHIPTOP.DDR.bit.P80 = 1;
	IO_CHIPTOP.PUDCR.bit.P80 = 0;
	IO_CHIPTOP.PUDER.bit.P80 = 0;



#if 0
	// PORT6 P80-P83
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P80, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P81, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P82, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P83, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P80, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P81, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P82, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P83, 1);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P80, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P81, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P82, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P83, 0);

    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P60, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P61, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P62, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P63, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P64, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P65, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P66, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P67, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P60, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P61, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P62, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P63, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P64, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P65, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P66, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P67, 1);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P60, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P61, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P62, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P63, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P64, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P65, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P66, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P67, 0);

	// PORT7 P70-P73
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P70, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P71, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P72, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_P73, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P70, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P71, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P72, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_P73, 1);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P70, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P71, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P72, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_P73, 0);

	// PORTU PU4-PU7
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_PU4, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_PU5, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_PU6, 1);
    Dd_Top_Set_Gpio_Direction(E_DD_TOP_GPIO_PU7, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_PU4, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_PU5, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_PU6, 1);
    Dd_Top_Set_Gpio_Function(E_DD_TOP_GPIO_PU7, 1);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_PU4, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_PU5, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_PU6, 0);
    Dd_Top_Set_Gpio_Pull_Up_Down_Enable(E_DD_TOP_GPIO_PU7, 0);
#endif
}

/*
 * PUBLIC
 */
void ct_dd_pwm_from_main(CtDdPwm* self, kint argc, kchar** argv)
{
	CtDdPwmPrivate* priv = self->priv;
	//rewrite cycle & duty
	kuchar wFact;

	// PWM Initialize
	if( strcmp(argv[1], "init") == 0 ){

		self->ret = Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH0_INT,1,D_DD_GIC_PRI30,0x1);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_GIC_Ctrl: CH0!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_GIC_Ctrl(E_DD_GIC_INTID_HDMAC0_CH2_INT,1,D_DD_GIC_PRI30,0x1);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_GIC_Ctrl: CH2!! self->ret = 0x%x\n", self->ret));
		}

		ctDdPwmSetGpio();

		Dd_PWM_Init();
	// PWM Open
	}else if( strcmp(argv[1], "open") == 0 ){
		self->ch = atoi(argv[2]);
		self->tmout = atoi(argv[3]);

		self->ret = Dd_PWM_Open(self->ch, self->tmout);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Open!! self->ret = 0x%x\n", self->ret));
		}
	// PWM Timer E Open
	}else if( strcmp(argv[1], "open_e") == 0 ){
		self->ch = atoi(argv[2]);
		self->tmout = atoi(argv[3]);

		self->ret = Dd_PWM_Open_Timer_E(self->ch, self->tmout);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Open_Timer_E!! self->ret = 0x%x\n", self->ret));
		}
	// PWM test Set
	}else if( strcmp(argv[1], "set_test") == 0 ){
		T_DD_PWM_CTRL_CMN pwmCtrl;
		T_DD_PWM_CTRL_TIMER_ABCD pwmCtrlAbcd;
		kuchar setPtn = 0;

		memset( &pwmCtrl, 0, sizeof(T_DD_PWM_CTRL_CMN) );
		memset( &pwmCtrlAbcd, 0, sizeof(T_DD_PWM_CTRL_TIMER_ABCD) );

		self->ch = atoi(argv[2]);
		// Setting patern no.
		setPtn = atoi(argv[3]);
		ctDdPwnSetCtrl(&pwmCtrl, &pwmCtrlAbcd, setPtn, self->ch);

		self->ret = Dd_PWM_Ctrl_Common(self->ch, &pwmCtrl);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Ctrl_Common!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_PWM_Ctrl_Timer_ABCD(self->ch, &pwmCtrlAbcd);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Ctrl_Timer_ABCD!! self->ret = 0x%x\n", self->ret));
		}
	}
#ifdef CtDdPwm_PWM_TEST
	// PWM test Set
	else if( strcmp(argv[1], "set_test2") == 0 ){
	//	ddpwm set_test2 self->ch ptn cks cycle_count
	//		self->ch							: 0-15
	//		ptn							: 0(one-shot & restart disable & soft trigger)
	//									: 1(PWM & restart enable & soft trigger)
	//		cks(Counter clocK Select)	: 0(RCLK)
	//									: 1(RCLK/18)
	//									: 2(RCLK/27)
	//									: 3(RCLK/64)
	//		cycle_count					: cycle_count = RCLK / division * cycle_time / 1000000
	//										ex. RCLK=13.5MHz, division=64, cycle_time = 60ms
	//											12656 = 13500000 / 64 * 60000 / 1000000
	//										ex. RCLK=13.5MHz, division=16, cycle_time = 60ms
	//											50625 = 13500000 / 16 * 60000 / 1000000
	//										ex. RCLK=18MHz, division=64, cycle_time = 60ms
	//											16875 = 18000000 / 64 * 60000 / 1000000
	//										ex. RCLK=27MHz, division=64, cycle_time = 60ms
	//											25313 = 27000000 / 64 * 60000 / 1000000
	//										ex. RCLK=54MHz, division=64, cycle_time = 60ms
	//											50625 = 54000000 / 64 * 60000 / 1000000
	//		note : duty=50% only
		kuchar setPtn = 0;
		kuchar cks;
		kulong cycleNum;

		memset( &(priv->pwmCtrl), 0, sizeof(T_DD_PWM_CTRL_CMN) );
		memset( &(priv->pwmCtrlAbcd), 0, sizeof(T_DD_PWM_CTRL_TIMER_ABCD) );

		self->ch = atoi(argv[2]);
		// Setting patern no.
		setPtn = atoi(argv[3]);
		cks = atoi(argv[4]);
		if(cks > 3){
			Ddim_Print(("input 4th parameter error (%d)\n", cks));
			return;
		}
		cycleNum = atol(argv[5]);
		if(cycleNum > 0xFFFF){
			Ddim_Print(("input 5th parameter error (Max value = 0xFFFF)\n"));
			return;
		}

		ctDdPwnSetCtrl2(self, setPtn, cks, cycleNum);

		Ddim_Print(("peri_clock             = %ld\n", Dd_Top_Get_RCLK()));
		Ddim_Print(("pwmCtrl.clk_sel       = %d\n", priv->pwmCtrl.clk_sel));
		Ddim_Print(("pwmCtrlAbcd.cyc_num  = %d\n", priv->pwmCtrlAbcd.cyc_num));
		Ddim_Print(("pwmCtrlAbcd.duty_num = %d\n", priv->pwmCtrlAbcd.duty_num));

		self->ret = Dd_PWM_Ctrl_Common(self->ch, &priv->pwmCtrl);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Ctrl_Common!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_PWM_Ctrl_Timer_ABCD(self->ch, &priv->pwmCtrlAbcd);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Ctrl_Timer_ABCD!! self->ret = 0x%x\n", self->ret));
		}
	}
#endif
	// PWM timer E test set
	else if( strcmp(argv[1], "set_test_e") == 0 ){
		kuchar setPtn;
		kuchar dmaCh;
		kuchar stepNum = 0;

		memset( &priv->pwmCtrl, 0, sizeof(T_DD_PWM_CTRL_CMN) );
		memset( &priv->timerECtrl, 0, sizeof(T_DD_PWM_CTRL_TIMER_E) );
		memset( &priv->pwmStp, 0, sizeof(T_DD_PWM_STEP) );

		self->ch = atoi(argv[2]);
		dmaCh = atoi(argv[3]);
		// Setting patern no.
		setPtn = atoi(argv[4]);
		if( setPtn == 3 ){
			stepNum = atoi(argv[5]);
		}

		ctDdPwmSetTimerECtrl(self, setPtn, stepNum );

		if( setPtn == 3 ){
			self->ret = Dd_PWM_Write_Step(self->ch, dmaCh, &priv->pwmStp);
			if(self->ret != 0){
				Ddim_Print(("Error Dd_PWM_Write_Step!! self->ret = 0x%x\n", self->ret));
			}
		}else
		{
			self->ret = Dd_PWM_Ctrl_Common(self->ch, &priv->pwmCtrl);
			if(self->ret != D_DDIM_OK){
				Ddim_Print(("Error Dd_PWM_Ctrl_Common!! self->ret = 0x%x\n", self->ret));
			}
			self->ret = Dd_PWM_Ctrl_Timer_E(self->ch, &priv->timerECtrl);
			if(self->ret != D_DDIM_OK){
				Ddim_Print(("Error Dd_PWM_Ctrl_Timer_E!! self->ret = 0x%x\n", self->ret));
			}
		}
	// PWM Start
	}else if( strcmp(argv[1], "start") == 0 ){

		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Start(self->ch);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Start!! self->ret = 0x%x\n", self->ret));
			return;
		}

		CtDdPwm_USER_LED13_On();
		Ddim_Print(("PWM Start !!\n"));
	// PWM E Start
	}else if( strcmp(argv[1], "start_e") == 0 ){

		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Start(self->ch);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Start!! self->ret = 0x%x\n", self->ret));
			return;
		}

		self->ret = Dd_HDMAC0_Open(0, D_DDIM_USER_SEM_WAIT_FEVR);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_HDMAC0_Open!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_HDMAC0_Start_Async(S_G_DMA_CH);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_HDMAC0_Start!! self->ret = 0x%x\n", self->ret));
		}
		Ddim_Print(("PWM E Start !!\n"));
	// PWM Stop
	}else if( strcmp(argv[1], "stop") == 0 ){
		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Stop(self->ch);
		CtDdPwm_USER_LED13_Off();
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Stop!! self->ret = 0x%x\n", self->ret));
		}
	// PWM E Stop
	}else if( strcmp(argv[1], "stop_e") == 0 ){
		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Stop(self->ch);
		CtDdPwm_USER_LED13_Off();
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Stop!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_HDMAC0_Stop(S_G_DMA_CH);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_HDMAC0_Stop!! self->ret = 0x%x\n", self->ret));
		}
		self->ret = Dd_HDMAC0_Close(S_G_DMA_CH);
		if(self->ret != D_DDIM_OK){
			Ddim_Print(("Error Dd_HDMAC0_Close!! self->ret = 0x%x\n", self->ret));
		}
	// PWM Close
	}else if( strcmp(argv[1], "close") == 0 ){
		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Close(self->ch);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Close!! self->ret = 0x%x\n", self->ret));
		}
	}else if( strcmp(argv[1], "close_e") == 0 ){			/* PWM E Close */
		self->ch = atoi(argv[2]);
		self->ret = Dd_PWM_Close_Timer_E(self->ch);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Close_Timer_E!! self->ret = 0x%x\n", self->ret));
		}
	}else if( strcmp(argv[1], "chg_wave") == 0 ){		/* PWM Change cycle and duty */
		kushort cycle = 1;
		kuchar duty;
		kuchar clk = 1;

		self->ch = atoi(argv[2]);
		duty = atoi(argv[5]);

		// cycle time(usec) check
		if (atoi(argv[4])){
			// cycle time(usec) convert
			self->ret = Dd_PWM_Calculate( atoi(argv[4]), &clk, &cycle);
			if (self->ret != D_DDIM_OK){
				Ddim_Print(("Error Dd_PWM_Calculate!! self->ret = 0x%x\n", self->ret));
				return;
			}
		}
		// PWM Change cycle and duty for Normal
		if( strcmp(argv[3], "n") == 0 ){
			self->ret = Dd_PWM_Write_Cycle_Duty(self->ch, cycle, duty, clk);
			if(self->ret != 0){
				Ddim_Print(("Error Dd_PWM_Write_Cycle_Duty!! self->ret = 0x%x\n", self->ret));
			}
		}
		// PWM Change cycle and duty for Queue
		else if( strcmp(argv[3], "q") == 0 ){
			self->ret = Dd_PWM_Write_Cycle_Duty_Queue(self->ch, cycle, duty, clk);
			if(self->ret != 0){
				Ddim_Print(("Error Dd_PWM_Write_Cycle_Duty_Queue!! self->ret = 0x%x\n", self->ret));
			}
		}
		// PWM Change cycle and duty for Reverse
		else if( strcmp(argv[3], "r") == 0 ){
			self->ret = Dd_PWM_Write_Cycle_Duty_Reverse(self->ch, cycle, duty, clk);
			if(self->ret != 0){
				Ddim_Print(("Error Dd_PWM_Write_Cycle_Duty_Reverse!! self->ret = 0x%x\n", self->ret));
			}
		}else
		{
			Ddim_Print( ("please check 3rd parameter!!\n" ) );
		}
	// PWM Set factor to rewrite cycle & duty
	}else if( strcmp(argv[1], "wFact") == 0 ){
		self->ch = atoi(argv[2]);
		wFact = atoi(argv[3]);

		self->ret = Dd_PWM_Write_Cycle_Duty_Switch(self->ch, wFact);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Write_Cycle_Duty_Switch!! self->ret = 0x%x\n", self->ret));
		}
	// Set PWM timer onshot
	}else if( strcmp(argv[1], "set_one") == 0 ){
		kushort cycTime, dutyTime;
		T_DD_PWM_CTRL_CMN ctrl;
		T_DD_PWM_CTRL_TIMER_ABCD ctrlAbcd;

		memset( &ctrl, 0, sizeof(T_DD_PWM_CTRL_CMN) );
		memset( &ctrlAbcd, 0, sizeof(T_DD_PWM_CTRL_TIMER_ABCD) );

		self->ch = atoi(argv[2]);
		cycTime = atoi(argv[3]);
		dutyTime = atoi(argv[4]);
		// (1)restart enable
		ctrl.restart_trig = D_DD_PWM_PCNHL_RTRG_ON;
		// (0)output is "Low"
		ctrl.out_mask = D_DD_PWM_PCNHL_PGMS_L;
		// (1)rise edge
		ctrl.edge = D_DD_PWM_PCNHL_EGS_RISE;
		// (1)agreement cycle
		ctrl.trigger = D_DD_PWM_PCNHL_IRS_CYCLE;
		// (0)polarity usually
		ctrl.polarity = D_DD_PWM_PCNHL_OSEL_NORMAL;
		// trigger input factor
		ctrl.in_trigger = (D_DD_PWM_CH_NUM_IN_BLOCK - 1) & self->ch;
		// Timer E disable
		ctrl.tim_e_enable = 0;
		// channel assignment
		ctrl.ch_assign = D_DD_PWM_GCN_CHAS_ABCD;
		// callback function pointer
		ctrl.pCallBack = (VP_CALLBACK_PWM)ctDdPwmCallback;
		// wave cycle(usec)
		ctrlAbcd.cyc_time = cycTime;
		// number of cycle
		ctrlAbcd.cyc_num = 0;
		// number of duty
		ctrlAbcd.duty_num = 0;

		self->ret = Dd_PWM_Write_Oneshot(self->ch, dutyTime, &ctrl, &ctrlAbcd);
		if(self->ret != 0){
			Ddim_Print(("Error Dd_PWM_Write_Oneshot!! self->ret = 0x%x\n", self->ret));
		}else
		{
			Ddim_Print(("PWM timer onshot set OK.\n"));
		}
	}
}

CtDdPwm* ct_dd_pwm_new(void) 
{
    CtDdPwm *self = k_object_new_with_private(CT_TYPE_DD_PWM, sizeof(CtDdPwmPrivate));
    return self;
}
