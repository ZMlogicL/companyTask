/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                	:2020-09-03
*@author              	:杨升柄
*@brief               	:CtDdPwmMain类
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
#include "ctddpwmmain.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdPwmMain, ct_dd_pwm_main);
#define CT_DD_PWM_MAIN_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdPwmMainPrivate,CT_TYPE_DD_PWM_MAIN))

struct _CtDdPwmMainPrivate
{
	CtDdPwm* cdPwm;
};

static kulong S_GDD_PWM_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64)));

static void ct_dd_pwm_main_constructor(CtDdPwmMain *self) 
{
	CtDdPwmMainPrivate *priv = CT_DD_PWM_MAIN_GET_PRIVATE(self);

	priv->cdPwm = ct_dd_pwm_new();
	self->priv = priv;
}

static void ct_dd_pwm_main_destructor(CtDdPwmMain *self) 
{
	CtDdPwmMainPrivate *priv = CT_DD_PWM_MAIN_GET_PRIVATE(self);

	if(priv->cdPwm)
	{
		k_object_unref(priv->cdPwm);
	}
	priv->cdPwm = NULL;
	self->priv = NULL;
}

/*
 * PUBLIC
 * Global Function
 *
 * @brief  Command main function for PWM timer test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 *
 *			The meaning of parameters
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| P1		  | P2 | P3 	| P4	  | P5	|Meaning							 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| init		  |    |		|		  | 	|PWM timer initialize				 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| open		  | ch |tmout	|		  | 	|PWM timer open 					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| open_e	  | ch |tmout	|		  | 	|PWM timer E open 					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_test	  | ch |ptn		|		  | 	|PWM timer set						 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_test_e  | ch |ptn_e	|step_num | 	|PWM timer E set					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| start 	  | ch |		|		  | 	|PWM timer start					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| stop		  | ch |		|		  | 	|PWM timer stop 					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| stop_e	  | ch |		|		  | 	|PWM timer E stop 					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| close 	  | ch |		|		  | 	|PWM timer close					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| close_e 	  | ch |		|		  | 	|PWM timer E close					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| chg_wave	  | ch |chg ptn |cycle	  |duty |Change cycle & duty (norm/queue/rev)|
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| w_fact	  | ch |factor	|		  | 	|Set factor to rewrite cycle & duty  |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_tmr	  | ch |		|		  | 	|Get value of PWM timer register	 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_pls	  | ch |		|		  | 	|Get number of output pulse			 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_int	  | ch |		|		  | 	|Get interrupt flag and enable		 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_int	  | ch |PINTCT0	|PINTCT1  | 	|Set interrupt flag and enable		 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| cal_cyc	  | ch |usec	|		  | 	|Calculate cycle and clock from usec |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| cal_cycc	  | ch |usec	|clk	  | 	|Calculate cycle from usec and clock |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_trg	  | ch |trigger	|		  | 	|Set input trigger					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_pcn	  | ch |pcn		|		  | 	|Set control status					 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_one	  | ch |cycle	|duty	  | 	|Set PWM timer onshot				 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_chas	  | ch |		|		  | 	|Get channel assignment				 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_chas	  | ch |chas	|		  | 	|Set channel assignment				 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_intstat | ch |		|		  | 	|Get interrupt status of PWM		 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| get_cmn     | ch |		|		  | 	|Get control commmon data			 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| set_stp_mask| ch |mask	|		  | 	|Set mask state						 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			| err		  |    |		|		  | 	|Parameter error test				 |
 *			+-------------+----+--------+---------+-----+------------------------------------+
 *			ch			:	0-15
 *			ptn			:	0(one-shot & restart disable & soft trigger)
 *						:	1(PWM & restart enable & soft trigger)
 *						:	2(PWM & restart disable & cycle trigger)
 *			ptn_e		:	1(DMA disable)
 *						:	2(DMA enable)
 *						:	3(Stepping motor utility)
 *			step_num	:	step numbert (only ptn_e=3)
 *			chg ptn		:	n(PWM Change cycle and duty for Normal)
 *						:	q(PWM Change cycle and duty for Queue)
 *						:	r(PWM Change cycle and duty for Reverse)
 *			restart		:	0(start trigger is only once)
 *						:	n(start trigger is (n+1))
 *			factor		:	0(CPU access)
 *						:	1(interrupt of ch0)
 *						:	2(interrupt of ch1)
 *						:	3(interrupt of ch2)
 *			clk			:	0(not dividing frequency)
 *						:	1(4 dividing frequency)
 *						:	2(16 dividing frequency)
 *						:	3(64 dividing frequency)
 *			trigger		:	0-11
 *			chas		:	1(ABCD)
 *						:	2(CBAD)
 *			mask		:	0(L output)
 *						:	1(H output)
 *
 * @return void
 */

void ct_dd_pwm_main_test(CtDdPwmMain* self, kint argc, kchar** argv)
{
	CtDdPwmMainPrivate* priv = self->priv;
	kint32 								tmout = D_DDIM_USER_SEM_WAIT_POL;

	//main函数拆分出去的部分
	ct_dd_pwm_from_main(priv->cdPwm, argc, argv);

	/*
	 * Calculate cycle from usec and clock
	 */
	if( strcmp(argv[1], "cal_cycc") == 0 ){
		kulong 	usec;
		kuchar 	clk;
		kushort 	cycle;

		usec = atoi(argv[2]);
		clk = atoi(argv[3]);

		priv->cdPwm->ret = Dd_PWM_Calculate_Cycle(usec, clk, &cycle);
		if ((priv->cdPwm->ret != D_DDIM_OK) && (priv->cdPwm->ret != D_DD_PWM_OVERFLOW_OK)){
			Ddim_Print(("Error Dd_PWM_Calculate_Cycle!! ret = 0x%x\n", priv->cdPwm->ret))
		}else
		{
			Ddim_Print(("PWM Calculate Cycle:\n"));
			Ddim_Print(("    usec        = %lu\n", usec));
			Ddim_Print(("    clock index = %d\n", clk));
			Ddim_Print(("    cycle       = %d\n", cycle));
		}
	/*
	 * Set input trigger
	*/
	}else if( strcmp(argv[1], "set_trg") == 0 ){
		kuchar gcnTsel;

		priv->cdPwm->ch = atoi(argv[2]);
		gcnTsel = atoi(argv[3]);

		priv->cdPwm->ret = Dd_PWM_Write_Input_Trg(priv->cdPwm->ch, gcnTsel);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Write_Input_Trg!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Input Trigger Set OK.\n"));
		}
	/*
	 *  Set control status
	 */
	}else if( strcmp(argv[1], "set_pcn") == 0 ){
		kushort pcn;

		priv->cdPwm->ch = atoi(argv[2]);
		pcn = atoi(argv[3]);

		priv->cdPwm->ret = Dd_PWM_Write_Pcn(priv->cdPwm->ch, pcn);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Write_Pcn!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM control status set OK.\n"));
		}
	/*
	 * Get value of PWM timer register
	 */
	}else if( strcmp(argv[1], "get_tmr") == 0 ){
		kushort timerVal, timerEVal;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Timer(priv->cdPwm->ch, &timerVal, &timerEVal);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Get_Timer!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Timer Value:\n"));
			Ddim_Print(("    ABCD = 0x%x\n", timerVal));
			Ddim_Print(("    E    = 0x%x\n", timerEVal));
		}
	/*
	 * Get number of output pulse
	 */
	}else if( strcmp(argv[1], "get_pls") == 0 ){
		kulong pulseNum;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Pulse_Num(priv->cdPwm->ch, &pulseNum);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Get_Pulse_Num!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Output Pulse Number = %lu\n", pulseNum));
		}
	/*
	 * Get interrupt flag and enable for timer E
	 */
	}else if( strcmp(argv[1], "get_int") == 0 ){
		kushort intFlgCtrl0, intFlgCtrl1;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Interrupt_Flag(priv->cdPwm->ch, &intFlgCtrl0, &intFlgCtrl1);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Get_Interrupt_Flag!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Interrupt Flag:\n"));
			Ddim_Print(("    PINTCT0 = 0x%x\n", intFlgCtrl0));
			Ddim_Print(("    PINTCT1 = 0x%x\n", intFlgCtrl1));
		}
	}else if( strcmp(argv[1], "set_int") == 0 ){
		kushort intFlgCtrl0, intFlgCtrl1;

		priv->cdPwm->ch = atoi(argv[2]);
		intFlgCtrl0 = strtol(argv[3], NULL, 16);
		intFlgCtrl1 = strtol(argv[4], NULL, 16);
		// pgr0539
		priv->cdPwm->ret = Dd_PWM_Set_Interrupt_Flag(priv->cdPwm->ch, intFlgCtrl0, intFlgCtrl1);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Set_Interrupt_Flag!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Interrupt Flag Set OK.\n"));
		}
	/*
	 *  Calculate cycle and clock from usec
	 */
	}else if( strcmp(argv[1], "cal_cyc") == 0 ){
		kulong usec;
		kuchar clk;
		kushort cycle;

		usec = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Calculate(usec, &clk, &cycle);
		if ((priv->cdPwm->ret != D_DDIM_OK) && (priv->cdPwm->ret != D_DD_PWM_OVERFLOW_OK)){
			Ddim_Print(("Error Dd_PWM_Calculate!! ret = 0x%x\n", priv->cdPwm->ret))
		}else
		{
			Ddim_Print(("PWM Calculate:\n"));
			Ddim_Print(("    usec        = %lu\n", usec));
			Ddim_Print(("    clock index = %d\n", clk));
			Ddim_Print(("    cycle       = %d\n", cycle));
		}
	/*
	 * Get channel assignment
	 */
	}else if( strcmp(argv[1], "get_chas") == 0 ){
		kuchar chAssign;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Channel_Assign(priv->cdPwm->ch, &chAssign);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Get_Channel_Assign!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Channel Assignment:\n"));
			Ddim_Print(("    CH[%d] = %d\n", priv->cdPwm->ch, chAssign));
		}
	/*
	 * Set channel assignment
	 */
	}else if( strcmp(argv[1], "set_chas") == 0 ){
		kuchar chAssign;

		priv->cdPwm->ch = atoi(argv[2]);
		chAssign = atoi(argv[3]);

		priv->cdPwm->ret = Dd_PWM_Set_Channel_Assign(priv->cdPwm->ch, chAssign);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Set_Channel_Assign!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Channel Assignment Set OK.\n"));
		}
	/*
	 *  Get interrupt status of PWM
	 */
	}else if( strcmp(argv[1], "get_intstat") == 0 ){
		priv->cdPwm->ch = atoi(argv[2]);

		Dd_ARM_Critical_Section_Start( S_GDD_PWM_SPIN_LOCK );
		priv->cdPwm->ret = Dd_PWM_Get_Int_Stat( priv->cdPwm->ch );
		Dd_ARM_Critical_Section_End( S_GDD_PWM_SPIN_LOCK );

		Ddim_Print(("PWM interrupt status [ch%d=%d]\n", priv->cdPwm->ch, priv->cdPwm->ret));
	/*
	 * Get conrtol common data
	 */
	}else if( strcmp(argv[1], "get_cmn") == 0 ){
		T_DD_PWM_CTRL_CMN ctrlCmn;

		memset( &ctrlCmn, 0, sizeof(T_DD_PWM_CTRL_CMN) );

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Ctrl_Common(priv->cdPwm->ch, &ctrlCmn);
		if (priv->cdPwm->ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Get Ctrl !!\n"));
		}

		Ddim_Print(("---PWM[%d] Get Ctrl Data---\n", priv->cdPwm->ch));
		Ddim_Print(("drv_mode     =%d\n", ctrlCmn.drv_mode));
		Ddim_Print(("clk_sel      =%d\n", ctrlCmn.clk_sel));
		Ddim_Print(("restart_trig =%d\n", ctrlCmn.restart_trig));
		Ddim_Print(("output mask  =%d\n", ctrlCmn.out_mask));
		Ddim_Print(("edge         =%d\n", ctrlCmn.edge));
		Ddim_Print(("int_enable   =%d\n", ctrlCmn.int_enable));
		Ddim_Print(("trigger      =%d\n", ctrlCmn.trigger));
		Ddim_Print(("polarity     =%d\n", ctrlCmn.polarity));
		Ddim_Print(("in_trigger   =%d\n", ctrlCmn.in_trigger));
		Ddim_Print(("tim_e_enable =%d\n", ctrlCmn.tim_e_enable));
		Ddim_Print(("chAssign    =%d\n", ctrlCmn.ch_assign));
		Ddim_Print(("pCallBack    =%10p\n", ctrlCmn.pCallBack));
	/*
	 * Set mask state
	 */
	}else if( strcmp(argv[1], "set_stp_mask") == 0 ){
		kuchar mask;

		priv->cdPwm->ch = atoi(argv[2]);
		mask = atoi(argv[3]);

		priv->cdPwm->ret = Dd_PWM_Set_Stopped_OutPut_Mask(priv->cdPwm->ch, mask);
		if(priv->cdPwm->ret != 0){
			Ddim_Print(("Error Dd_PWM_Set_Mask!! ret = 0x%x\n", priv->cdPwm->ret));
		}else
		{
			Ddim_Print(("PWM Stop Mask Set OK.\n"));
		}
	/*
	 * Get mask state
	 */
	}else if( strcmp(argv[1], "get_stp_mask") == 0 ){
		kuchar mask;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Stopped_OutPut_Mask(priv->cdPwm->ch, &mask);
		if (priv->cdPwm->ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Get Mask !!\n"));
		}

		Ddim_Print(("---PWM[%d] Get Mask---\n", priv->cdPwm->ch));
		Ddim_Print(("mask     =%d\n", mask));
	/*
	 * Get PWM stop status
	 */
	}else if( strcmp(argv[1], "get_stp_out") == 0 ){
		kuchar ch_status;

		priv->cdPwm->ch = atoi(argv[2]);

		priv->cdPwm->ret = Dd_PWM_Get_Stopped_OutPut_Status(priv->cdPwm->ch, &ch_status);
		if (priv->cdPwm->ret != D_DDIM_OK){
			Ddim_Print(("Error PWM Get stp_out !!\n"));
		}

		Ddim_Print(("---PWM[%d] Get Stop Output---\n", priv->cdPwm->ch));
		Ddim_Print(("status     =%d\n", ch_status));
	}else if (strcmp(argv[1], "err") == 0){
		T_DD_PWM_CTRL_CMN 					pwmCtrl;
		T_DD_PWM_CTRL_TIMER_ABCD 	pwmCtrlAbcd;
		T_DD_PWM_CTRL_TIMER_E 			pwmCtrlE;
		kushort 											timerVal, timerEVal;
		kulong 											pulseNum;
		kushort 											intFlgCtrl0 = 0, intFlgCtrl1 = 0;
		kuchar 											chAssign = 0;
		kuchar 											clk;
		kushort 											cycle;
		T_DD_PWM_STEP 							pwmStp;

		memset( &pwmCtrl, 0, sizeof(T_DD_PWM_CTRL_CMN) );
		memset( &pwmCtrlAbcd, 0, sizeof(T_DD_PWM_CTRL_TIMER_ABCD) );
		memset( &pwmCtrlE, 0, sizeof(T_DD_PWM_CTRL_TIMER_E) );
		memset( &pwmStp, 0, sizeof(T_DD_PWM_STEP) );

		switch ( atoi(argv[2]) ) {
			case 0 :
				priv->cdPwm->ret = Dd_PWM_Open( D_DD_PWM_CH_NUM_MAX, tmout );
				Ddim_Print(("Dd_PWM_Open(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 1 :
				priv->cdPwm->ret = Dd_PWM_Open( 0, -2 );
				Ddim_Print(("Dd_PWM_Open(): tmout value error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 2 :
				priv->cdPwm->ret = Dd_PWM_Close( D_DD_PWM_CH_NUM_MAX );
				Ddim_Print(("Dd_PWM_Close(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 3 :
				priv->cdPwm->ret = Dd_PWM_Open_Timer_E( 1, tmout );
				Ddim_Print(("Dd_PWM_Open_Timer_E(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 4 :
				priv->cdPwm->ret = Dd_PWM_Open_Timer_E( 0, -2 );
				Ddim_Print(("Dd_PWM_Open_Timer_E(): tmout value error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 5 :
				priv->cdPwm->ret = Dd_PWM_Close_Timer_E( 5 );
				Ddim_Print(("Dd_PWM_Close_Timer_E(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 6 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Common( D_DD_PWM_CH_NUM_MAX, &pwmCtrl );
				Ddim_Print(("Dd_PWM_Ctrl_Common(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 7 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Common( 0, NULL );
				Ddim_Print(("Dd_PWM_Ctrl_Common(): pwmCtrl is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 8 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Timer_ABCD( D_DD_PWM_CH_NUM_MAX, &pwmCtrlAbcd );
				Ddim_Print(("Dd_PWM_Ctrl_Timer_ABCD(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 9 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Timer_ABCD( 0, NULL );
				Ddim_Print(("Dd_PWM_Ctrl_Timer_ABCD(): pwmCtrlAbcd is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 10 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Timer_E( D_DD_PWM_CH_NUM_MAX, &pwmCtrlE );
				Ddim_Print(("Dd_PWM_Ctrl_Timer_E(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 11 :
				priv->cdPwm->ret = Dd_PWM_Ctrl_Timer_E( 0, NULL );
				Ddim_Print(("Dd_PWM_Ctrl_Timer_E(): pwmCtrlE is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 12 :
				priv->cdPwm->ret = Dd_PWM_Start( D_DD_PWM_CH_NUM_MAX );
				Ddim_Print(("Dd_PWM_Start(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 13 :
				priv->cdPwm->ret = Dd_PWM_Stop( D_DD_PWM_CH_NUM_MAX );
				Ddim_Print(("Dd_PWM_Stop(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 14 :
				priv->cdPwm->ret = Dd_PWM_Get_Timer(D_DD_PWM_CH_NUM_MAX, &timerVal, &timerEVal);
				Ddim_Print(("Dd_PWM_Get_Timer(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 15 :
				priv->cdPwm->ret = Dd_PWM_Get_Timer(0, NULL, &timerEVal);
				Ddim_Print(("Dd_PWM_Get_Timer(): timerVal is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 16 :
				priv->cdPwm->ret = Dd_PWM_Get_Timer(0, &timerVal, NULL);
				Ddim_Print(("Dd_PWM_Get_Timer(): timerEVal is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 17 :
				priv->cdPwm->ret = Dd_PWM_Get_Pulse_Num(D_DD_PWM_CH_NUM_MAX, &pulseNum);
				Ddim_Print(("Dd_PWM_Get_Pulse_Num(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 18 :
				priv->cdPwm->ret = Dd_PWM_Get_Pulse_Num(0, NULL);
				Ddim_Print(("Dd_PWM_Get_Pulse_Num(): pulseNum is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 19 :
				priv->cdPwm->ret = Dd_PWM_Get_Interrupt_Flag(D_DD_PWM_CH_NUM_MAX, &intFlgCtrl0, &intFlgCtrl1);
				Ddim_Print(("Dd_PWM_Get_Interrupt_Flag(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 20 :
				priv->cdPwm->ret = Dd_PWM_Get_Interrupt_Flag(0, NULL, &intFlgCtrl1);
				Ddim_Print(("Dd_PWM_Get_Interrupt_Flag(): intFlgCtrl0 is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 21 :
				priv->cdPwm->ret = Dd_PWM_Get_Interrupt_Flag(0, &intFlgCtrl0, NULL);
				Ddim_Print(("Dd_PWM_Get_Interrupt_Flag(): intFlgCtrl1 is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 22 :
				priv->cdPwm->ret = Dd_PWM_Set_Interrupt_Flag(D_DD_PWM_CH_NUM_MAX, intFlgCtrl0, intFlgCtrl1);
				Ddim_Print(("Dd_PWM_Set_Interrupt_Flag(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 23 :
				priv->cdPwm->ret = Dd_PWM_Get_Channel_Assign(D_DD_PWM_CH_NUM_MAX, &chAssign);
				Ddim_Print(("Dd_PWM_Get_Channel_Assign(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 24 :
				priv->cdPwm->ret = Dd_PWM_Get_Channel_Assign(0, NULL);
				Ddim_Print(("Dd_PWM_Get_Channel_Assign(): chAssign is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 25 :
				priv->cdPwm->ret = Dd_PWM_Set_Channel_Assign(D_DD_PWM_CH_NUM_MAX, chAssign);
				Ddim_Print(("Dd_PWM_Set_Channel_Assign(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 26 :
				priv->cdPwm->ret = Dd_PWM_Set_Channel_Assign(0, (D_DD_PWM_GCN_CHAS_CBAD + 1));
				Ddim_Print(("Dd_PWM_Set_Channel_Assign(): chAssign error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 27 :
				priv->cdPwm->ret = Dd_PWM_Get_Int_Stat(D_DD_PWM_CH_NUM_MAX);
				Ddim_Print(("Dd_PWM_Get_Int_Stat(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 28 :
				Dd_PWM_Int_Handler(D_DD_PWM_CH_NUM_MAX);
				Ddim_Print(("Dd_PWM_Int_Handler(): CH number error.\n"));
				break;
			case 29 :
				Dd_PWM_Int_Handler_STP(D_DD_PWM_CH_NUM_MAX);
				Ddim_Print(("Dd_PWM_Int_Handler_STP(): CH number error.\n"));
				break;
			case 30 :
				priv->cdPwm->ret = Dd_PWM_Calculate(0, &clk, &cycle);
				Ddim_Print(("Dd_PWM_Calculate(): usec error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 31 :
				priv->cdPwm->ret = Dd_PWM_Calculate(60000, NULL, &cycle);
				Ddim_Print(("Dd_PWM_Calculate(): clk is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 32 :
				priv->cdPwm->ret = Dd_PWM_Calculate(60000, &clk, NULL);
				Ddim_Print(("Dd_PWM_Calculate(): cycle is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 33 :
				priv->cdPwm->ret = Dd_PWM_Calculate_Cycle(0, 3, &cycle);
				Ddim_Print(("Dd_PWM_Calculate_Cycle(): usec error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 34 :
				priv->cdPwm->ret = Dd_PWM_Calculate_Cycle(60000, D_DD_PWM_PCNHL_CKS_DIV_64+1, &cycle);
				Ddim_Print(("Dd_PWM_Calculate_Cycle(): clk error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 35 :
				priv->cdPwm->ret = Dd_PWM_Calculate_Cycle(60000, 3, NULL);
				Ddim_Print(("Dd_PWM_Calculate_Cycle(): cycle is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 36 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty(D_DD_PWM_CH_NUM_MAX, 50000, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 37 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty(0, 0, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty(): cycle error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 38 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty(0, 50000, 0, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty(): duty error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 39 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty(0, 50000, 50, D_DD_PWM_PCNHL_CKS_DIV_64+1);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty(): clk_sel error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 40 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Reverse(D_DD_PWM_CH_NUM_MAX, 50000, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Reverse(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 41 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Reverse(0, 0, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Reverse(): cycle error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 42 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Reverse(0, 50000, 0, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Reverse(): duty error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 43 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Reverse(0, 50000, 50, D_DD_PWM_PCNHL_CKS_DIV_64+1);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Reverse(): clk_sel error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 44 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Queue(D_DD_PWM_CH_NUM_MAX, 50000, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Queue(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 45 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Queue(0, 0, 50, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Queue(): cycle error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 46 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Queue(0, 50000, 0, 3);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Queue(): duty error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 47 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Queue(0, 50000, 50, D_DD_PWM_PCNHL_CKS_DIV_64+1);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Queue(): clk_sel error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 48 :
				priv->cdPwm->ret = Dd_PWM_Write_Input_Trg(D_DD_PWM_CH_NUM_MAX, 0);
				Ddim_Print(("Dd_PWM_Write_Input_Trg(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 49 :
				priv->cdPwm->ret = Dd_PWM_Write_Cycle_Duty_Switch(D_DD_PWM_CH_NUM_MAX, 0);
				Ddim_Print(("Dd_PWM_Write_Cycle_Duty_Switch(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 50 :
				priv->cdPwm->ret = Dd_PWM_Write_Pcn(D_DD_PWM_CH_NUM_MAX, 0);
				Ddim_Print(("Dd_PWM_Write_Pcn(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 51 :
				priv->cdPwm->ret = Dd_PWM_Write_Oneshot(D_DD_PWM_CH_NUM_MAX, 30000, &pwmCtrl, &pwmCtrlAbcd);
				Ddim_Print(("Dd_PWM_Write_Oneshot(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 52 :
				priv->cdPwm->ret = Dd_PWM_Write_Oneshot(0, 30000, NULL, &pwmCtrlAbcd);
				Ddim_Print(("Dd_PWM_Write_Oneshot(): pwmCtrl is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 53 :
				priv->cdPwm->ret = Dd_PWM_Write_Oneshot(0, 30000, &pwmCtrl, NULL);
				Ddim_Print(("Dd_PWM_Write_Oneshot(): pwmCtrlAbcd is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 54 :
				priv->cdPwm->ret = Dd_PWM_Write_Step(9, 0, &pwmStp);
				Ddim_Print(("Dd_PWM_Write_Step(): CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 55 :
				priv->cdPwm->ret = Dd_PWM_Write_Step(0, D_DD_HDMAC0_CH_NUM_MAX, &pwmStp);
				Ddim_Print(("Dd_PWM_Write_Step(): DMA CH number error. ret=%X\n", priv->cdPwm->ret ));
				break;
			case 56 :
				priv->cdPwm->ret = Dd_PWM_Write_Step(0, 0, NULL);
				Ddim_Print(("Dd_PWM_Write_Step(): pwmStp is NULL. ret=%X\n", priv->cdPwm->ret ));
				break;
			default :
				Ddim_Print(("please check 2nd parameter!!\n"));
				break;
		}
	}else
	{
		Ddim_Print( ("please check 1st parameter!!\n" ) );
	}
}

CtDdPwmMain* ct_dd_pwm_main_new(void) 
{
    CtDdPwmMain *self = k_object_new_with_private(CT_TYPE_DD_PWM_MAIN, sizeof(CtDdPwmMainPrivate));
    return self;
}
