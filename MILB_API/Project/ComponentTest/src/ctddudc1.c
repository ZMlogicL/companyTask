/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :李清
*@brief               :CtDdUdc1类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年06月开始开发
*/
#include "ddimusercustom.h"
#include "peripheral.h"
#include "ddudc.h"
#include "ddtop.h"
#include "stdlib.h"
#include "string.h"
#include "ddgic.h"
#include "ctddudc.h"
#include "ctddudc1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdUdc1, ct_dd_udc1);
#define CT_DD_UDC1_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdUdc1Private,CT_TYPE_DD_UDC1))

struct _CtDdUdc1Private {
	kint i;
};

static void ct_dd_udc1_constructor(CtDdUdc1 *self) 
{
// CtDdUdc1Private *priv = CT_DD_UDC1_GET_PRIVATE(self);
}

static void ct_dd_udc1_destructor(CtDdUdc1 *self)
{
// CtDdUdc1Private *priv = CT_DD_UDC1_GET_PRIVATE(self);
}
/*
 *PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for UDC test.
 * @param  kint32 argc	:The number of parameters
 *		   CGAR** argv	:The value of parameters
 */
void ct_dd_udc1_main(CtDdUdc1 *self, kint argc, KType* argv)
{
	kuchar				ch;
	kboolean			isTimerMode   	= FALSE;
	kboolean			isUpDownMode  	= FALSE;
	CtDdUdc *			cdUdc 			= ct_dd_udc_new();
	DdUdc *				ddUdc 			= dd_udc_get();
	DdimUserCustom *	ddimUserCus 	= ddim_user_custom_new();
	
	memset(&self->udcCrl, 0, sizeof(DdUdcCtrlCmn));

	if (strcmp((KConstType)argv[1], "init") == 0) {
		// UDC initialize test 
		// [command] udc init
		dd_udc_init(ddUdc);

		// General-purpose port setting for UDC test.
		for (cdUdc->i = 0; cdUdc->i < 6; cdUdc->i++, cdUdc->ch = cdUdc->i) { // AIN
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_EPCR, 0);
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_DDR, 0);
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_PDR, 0);

			// BIN
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_EPCR, 0);
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_DDR, 0);
			ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_PDR, 0);

			// ZIN
			if ((cdUdc->i == DdUdc_CH0) || (cdUdc->i == DdUdc_CH1)) {
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_ZIN, CtDdUdc_PORT_KIND_EPCR, 0);
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_ZIN, CtDdUdc_PORT_KIND_DDR, 0);
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_ZIN, CtDdUdc_PORT_KIND_PDR, 0);
			}
		}

		ct_dd_udc_print_clk_info(cdUdc);
		ct_dd_udc_print_trg_info(cdUdc);
		ct_dd_udc_print_reg_info(cdUdc);

		// GIC set (ch0-5)
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH0_INT, 1, C_PRI30, 2);
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH1_INT, 1, C_PRI30, 2);
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH2_INT, 1, C_PRI30, 2);
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH3_INT, 1, C_PRI30, 2);
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH4_INT, 1, C_PRI30, 2);
		dd_gic_ctrl(DdGic_INTID_UPDOWN_COUNTER_CH5_INT, 1, C_PRI30, 2);

		Ddim_Print(("dd_udc_init OK.\n"));
	} else if(strcmp((KConstType)argv[1], "open") == 0) {
		// UDC open
		// [command] udc open P1
		//           P1: Channel number(0~3)
		if(argc >= 3) {
			self->ercd = dd_udc_open(ddUdc, (atoi((KConstType)argv[2])),DdimUserCustom_SEM_WAIT_POL);
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_open NG. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("dd_udc_open OK.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "close") == 0) {
		// UDC close
		// [command] udc close P1
		//           P1: Channel number(0~3)
		if(argc >= 3) {
			self->ercd = dd_udc_close(ddUdc, atoi((KConstType)argv[2]));
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_close NG. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("dd_udc_close OK.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "start") == 0) {
		// UDC start
		// [command] udc start P1 P2 P3 P4 P5 P6 P7 P8 P9 P11 (P12)
		//           P1 : Mode("timer", "up_down" "phase2" "phase4")					@CCR.CMS
		//           P2 : Channel number(0~3)
		//           P3 : UDCR															@UDCR
		//           P4 : RCR															@RCR
		//           P5 : Compare clear enable(0:Disable, 1:Enable)						@CCR.UCRE
		//           P6 : Reload enable(0:Disable, 1:Enable)							@CCR.RLDE
		//           P7 : Function of terminal ZIN.(0:Clear, 1:Gate)					@CCR.CGSC
		//           P8 : Detect edge of terminal ZIN.(0:Not, 1:Fall/Low, 2:Rise/High)	@CCR.CGE
		//           P9 : Compare interrupt enable(0:Disable, 1:Enable)					@CSR.CITE
		//           P10: Under/Over-flow interrupt enable(0:Disable, 1:Enable)			@CSR.UDIE
		//           P11: Count direction interrupt enable(0:Disable, 1:Enable)			@CSR.CFIE
		// (Timer)   P12: Built-in prescaler.(0:2 Clock cycle, 1:8 Clock cycle)			@CCR.CLKS
		// (Up/Down) P12: Count clock edge(0:Not, 1:Fall, 2:Rise, 3:Both)				@CCR.CES
		// (Phase)   P12: Not used.
		if(argc >= 13) {
			// Set common parameter
			ch                  	= atoi((KConstType)argv[3]);
			self->udcCrl.udcr       = atoi((KConstType)argv[4]);
			self->udcCrl.rcr        = atoi((KConstType)argv[5]);
			self->udcCrl.compClear  = atoi((KConstType)argv[6]);
			self->udcCrl.reload     = atoi((KConstType)argv[7]);
			self->udcCrl.zinMode    = atoi((KConstType)argv[8]);
			self->udcCrl.zinEdge    = atoi((KConstType)argv[9]);
			self->udcCrl.cmpInt     = atoi((KConstType)argv[10]);
			self->udcCrl.underOver  = atoi((KConstType)argv[11]);
			self->udcCrl.cntDirInt 	= atoi((KConstType)argv[12]);
			self->udcCrl.pCallBack  = ctDdUdcCallback_cd;

			cdUdc->ch = ch;
			if (strcmp((KConstType)argv[2], "timer") == 0) {
				// Timer mode
				Ddim_Print(("Timer mode.\n"));
				if(argc < 14) {
					Ddim_Print(("Command parameter error.\n"));
					return;
				}
				self->udcCrl.countMode 	= DdUdc_CMS_TIMER;
				isTimerMode      		= TRUE;
			} else if (strcmp((KConstType)argv[2], "up_down") == 0) {
				// Up/Down count mode
				Ddim_Print(("Up/Down count mode.\n"));
				if(argc < 14) {
					Ddim_Print(("Command parameter error.\n"));
					return;
				}
				self->udcCrl.countMode = DdUdc_CMS_UP_DOWN;
				isUpDownMode    = TRUE;
			} else if (strcmp((KConstType)argv[2], "phase2") == 0) { // Phase lag count mode 2
				Ddim_Print(("Phase lag count mode 2 mode.\n"));
				self->udcCrl.countMode = DdUdc_CMS_PHASE_LAG_2;

				// Preparation for test of phase lag count mode. (Initial state is Low.)
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_PDR, 0);
				// AIN -> Low
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_PDR, 0);	
				// BIN -> Low
			} else if (strcmp((KConstType)argv[2], "phase4") == 0) { // Phase lag count mode 4
				Ddim_Print(("Phase lag count mode 4 mode.\n"));
				self->udcCrl.countMode = DdUdc_CMS_PHASE_LAG_4;

				// Preparation for test of phase lag count mode. (Initial state is Low.)
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_PDR, 0);	
				// AIN -> Low
				ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_PDR, 0);	
				// BIN -> Low
			} else { // Command error
				Ddim_Print(("Command parameter error.\n"));
				return;
			}

			cdUdc->ch = ch;
			// Display settings berore dd_udc_ctrl_common
			Ddim_Print(("Setting before write\n"));
			ct_dd_udc_print_crl_common(cdUdc, &self->udcCrl);

			// Set execution parameter
			self->ercd = dd_udc_ctrl_common(ddUdc, ch, &self->udcCrl);
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_ctrl_common error. ercd=%d\n", self->ercd));
				return;
			} else {
				Ddim_Print(("dd_udc_ctrl_common OK.\n"));
			}

			// Display settings after dd_udc_ctrl_common
			Ddim_Print(("Setting after write\n"));
			self->ercd = dd_udc_get_ctrl_common(ddUdc, ch, &self->udcCrl);
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_get_ctrl_common NG. ercd=%d\n", self->ercd));
				return;
			}
			ct_dd_udc_print_crl_common(cdUdc, &self->udcCrl);

			if (isTimerMode == TRUE) {
				self->ercd = dd_udc_ctrl_timer(ddUdc, ch, atoi((KConstType)argv[13]));
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_ctrl_timer error. ercd=%d\n", self->ercd));
					return;
				} else {
					Ddim_Print(("dd_udc_ctrl_timer OK. prescaler=%d\n", atoi((KConstType)argv[13])));
				}
			} else if(isUpDownMode == TRUE) {
				self->ercd = dd_udc_ctrl_up_down(ddUdc, ch, atoi((KConstType)argv[13]));
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_ctrl_up_down error. ercd=%d\n", self->ercd));
					return;
				} else {
					Ddim_Print(("dd_udc_ctrl_up_down OK. edge=%d\n", atoi((KConstType)argv[13])));
				}
			} else { 
				// DO NOTHING
			}

			// UDC start
			self->ercd = dd_udc_start(ddUdc, ch);
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_start(%d) NG. ercd=%d\n", ch, self->ercd));
			} else {
				ct_dd_udc_print_trg_info(cdUdc);
				Ddim_Print(("dd_udc_start(%d) OK.\n", ch));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "stop") == 0) {
		// UDC stop
		// [command] udc stop P1
		//           P1 : Channel number(0~3)
		if(argc >= 3) {
			ch = atoi((KConstType)argv[2]);
			self->ercd = dd_udc_stop(ddUdc, ch);
			if(self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_stop(%d) NG. ercd=%d\n", ch, self->ercd));
			} else {
				ct_dd_udc_print_trg_info(cdUdc);
				Ddim_Print(("dd_udc_stop(%d) OK.\n", ch));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "get_crl") == 0) {
		// Get control data
		// [command] udc get_crl P1 P2
		//           P1 : Kind of control data("common", "timer" "up_down")
		//           P2 : Channel number(0~3)
		if(argc >= 4) {
			ch = atoi((KConstType)argv[3]);
			cdUdc->ch = ch;
			if (strcmp((KConstType)argv[2], "common") == 0) { // Get common control data
				self->ercd = dd_udc_get_ctrl_common(ddUdc, ch, &self->udcCrl);
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_get_ctrl_common NG. ercd=%d\n", self->ercd));
					return;
				}
				Ddim_Print(("---- dd_udc_get_ctrl_common(Ch%d) ----\n", ch));
				ct_dd_udc_print_crl_common(cdUdc, &self->udcCrl);
				Ddim_Print(("dd_udc_get_ctrl_common OK.\n"));
			} else if (strcmp((KConstType)argv[2], "timer") == 0) { // Get timer control data
				self->ercd = dd_udc_get_ctrl_timer(ddUdc, ch, &self->prescaler);
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_get_ctrl_timer NG. ercd=%d\n", self->ercd));
					return;
				}
				Ddim_Print(("---- dd_udc_get_ctrl_timer(Ch%d) ----\n", ch));
				Ddim_Print(("CCR.CLKS = 0x%x\n", self->prescaler));
				Ddim_Print(("dd_udc_get_ctrl_timer OK.\n"));
			} else if (strcmp((KConstType)argv[2], "up_down") == 0) { // Get up/donw control data
				self->ercd = dd_udc_get_ctrl_up_down(ddUdc, ch, &self->edge);
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_get_ctrl_up_down NG. ercd=%d\n", self->ercd));
					return;
				}
				Ddim_Print(("---- dd_udc_get_ctrl_up_down(Ch%d) ----\n", ch));
				Ddim_Print(("CCR.CES  = 0x%x\n", self->edge));
				Ddim_Print(("dd_udc_get_ctrl_up_down OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "cb") == 0) {
		if (strcmp((KConstType)argv[2], "set") == 0) {
			// Set callback function pointer
			// [command] udc cb set P1 P2
			//           P1 : Channel number(0~3)
			//           P2 : Function selection
			if(argc >= 5) {
				ch = atoi((KConstType)argv[3]);

				// Select callback function
				switch (atoi((KConstType)argv[4])) {
					case 0:
						// Main function
						self->callback = ctDdUdcCallback_cd;
						break;

					default:
						// Sub function
						self->callback = ctDdUdcCallbackSub_cd;
						break;
				}
				dd_udc_set_callback(ddUdc, ch, self->callback);
				Ddim_Print(("---- dd_udc_set_callback(Ch%d) ----\n", ch));
				Ddim_Print(("callback = %p\n", self->callback));
				Ddim_Print(("dd_udc_set_callback OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "rcr") == 0) {
		if (strcmp((KConstType)argv[2], "set") == 0) {
			// Set RCR register value
			// [command] udc rcr set P1 P2
			//           P1 : Channel number(0~3)
			//           P2 : RCR
			if(argc >= 5) {
				ch = atoi((KConstType)argv[3]);

				self->ercd = dd_udc_set_rcr_counter(ddUdc, ch, atoi((KConstType)argv[4]));
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_set_rcr_counter NG. ercd=%d\n", self->ercd));
				} else {
					Ddim_Print(("dd_udc_set_rcr_counter OK.\n"));
				}
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "udcr") == 0) {
		if (strcmp((KConstType)argv[2], "get") == 0) {
			// Get UDCR register value
			// [command] udc udcr get P1
			//           P1 : Channel number(0~3)
			if(argc >= 4) {
				ch = atoi((KConstType)argv[3]);
				Ddim_Print(("---- dd_udc_get_udcr_counter(Ch%d) ----\n", ch));
				Ddim_Print(("UDCR = 0x%x\n", dd_udc_get_udcr_counter(ddUdc, ch)));
				Ddim_Print(("dd_udc_get_udcr_counter OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if (strcmp((KConstType)argv[2], "set") == 0) {
			// Set UDCR register value
			// [command] udc udcr set P1 P2
			//           P1 : Channel number(0~3)
			//           P2 : UDCR
			if(argc >= 5) {
				ch = atoi((KConstType)argv[3]);

				self->ercd = dd_udc_set_udcr_counter(ddUdc, ch, atoi((KConstType)argv[4]));
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_set_udcr_counter NG. ercd=%d\n", self->ercd));
				} else {
					Ddim_Print(("dd_udc_set_udcr_counter OK.\n"));
				}
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if (strcmp((KConstType)argv[2], "clear") == 0) {
			// Clear UDCR register value
			// [command] udc udcr clear P1
			//           P1 : Channel number(0~3)
			if(argc >= 4) {
				ch = atoi((KConstType)argv[3]);

				Ddim_Print(("---- dd_udc_force_clear_udcr(Ch%d) ----\n", ch));
				Ddim_Print(("Before UDCR = 0x%x\n", dd_udc_get_udcr_counter(ddUdc, ch)));
				self->ercd = dd_udc_force_clear_udcr(ddUdc, ch);
				Ddim_Print(("After UDCR = 0x%x\n", dd_udc_get_udcr_counter(ddUdc, ch)));
				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_force_clear_udcr NG. ercd=%d\n", self->ercd));
				} else {
					Ddim_Print(("dd_udc_force_clear_udcr OK.\n"));
				}
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "mode") == 0) {
		if (strcmp((KConstType)argv[2], "set") == 0) {
			// Set count mode
			// [command] udc mode set P1 P2
			//           P1 : Channel number(0~3)
			//           P2 : Count mode(0~3)
			if(argc >= 5) {
				ch = atoi((KConstType)argv[3]);
				Ddim_Print(("Before set: IO_PERI.UDC[%d].CCR.bit.__CMS=%d\n", 
					ch, ioPeri.udc[ch].ccr.bit.__cms));
				self->ercd = dd_udc_set_count_mode(ddUdc, ch, atoi((KConstType)argv[4]));
				Ddim_Print(("After set : IO_PERI.UDC[%d].CCR.bit.__CMS=%d\n", 
					ch, ioPeri.udc[ch].ccr.bit.__cms));

				if(self->ercd != D_DDIM_OK) {
					Ddim_Print(("dd_udc_set_count_mode NG.\n"));
				} else {
					Ddim_Print(("dd_udc_set_count_mode OK.\n"));
				}
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "port") == 0) { // Virtual input control(AIN, BIN, ZIN)
		self->tmrAinCh = CtDdUdc1_TMR_AIN_CH; // Timer channel number
		self->tmrBinCh = CtDdUdc1_TMR_BIN_CH; // Timer channel number
		cdUdc->tmrChA = self->tmrAinCh;
		cdUdc->tmrChB = self->tmrBinCh;
		
		if (strcmp((KConstType)argv[2], "ph_lag") == 0) { // Virtual input for phase lag count mode.
			if (strcmp((KConstType)argv[3], "start") == 0) {
				/*
				  Start virtual AIN/BIN input for phase lag count mode.
							+----+    +----+    +----+   
							|    |    |    |    |    |   
					AIN ----+    +----+    +----+    +---
							  +----+    +----+    +----+ 
							  |    |    |    |    |    | 
					BIN ------+    +----+    +----+    +-

				  [command] udc port ph_lag start P1 P2 P3 P4
							P1 : Channel number of UDC(0~3)
							P2 : AIN interval(msec)
							P3 : BIN interval(msec)
							P4 : Gap of start timing.(msec)
				*/
				if (argc >= 8) {
					ch = atoi((KConstType)argv[4]); // UDC channel number
					cdUdc->ch = ch;

					// Start virtual AIN input.
					self->ercd = ct_dd_udc_start_virtual_ain(cdUdc, ch, // UDC channel number												
						(atoi((KConstType)argv[5]) * 1000)	// Interval(usec)
					);
					if (self->ercd != D_DDIM_OK) {
						Ddim_Print(("ct_dd_udc_start_virtual_ain NG. ercd=%d\n", self->ercd));
						return;
					}
					ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_AIN, CtDdUdc_PORT_KIND_PDR, 1);
					// AIN -> High
					Ddim_Print((
						"[AIN] (Ch=%d) (TIM=0) (UDCR=%d) (PDR=1)\n",
						ct_dd_udc_get_ain_ch(cdUdc),
						dd_udc_get_udcr_counter(ddUdc, ct_dd_udc_get_ain_ch(cdUdc))));

					// Wait gap time
					ddim_user_custom_dly_tsk(ddimUserCus, (kuint32)atoi((KConstType)argv[7]));

					// Start virtual BIN input.
					self->ercd = ct_dd_udc_start_virtual_bin(cdUdc, 
						ch,										// UDC channel number
						(atoi((KConstType)argv[6]) * 1000)	// Interval(usec)
					);
					if (self->ercd != D_DDIM_OK) {
						Ddim_Print(("ct_dd_udc_start_virtual_bin NG. ercd=%d\n", self->ercd));
						return;
					}
					ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_BIN, CtDdUdc_PORT_KIND_PDR, 1);
					// BIN -> High
					Ddim_Print((
						"[BIN] (Ch=%d) (TIM=0) (UDCR=%d) (PDR=1)\n",
						ct_dd_udc_get_bin_ch(cdUdc),
						dd_udc_get_udcr_counter(ddUdc, ct_dd_udc_get_bin_ch(cdUdc))));
				} else {
					Ddim_Print(("Command parameter error.\n"));
				}
			} else if (strcmp((KConstType)argv[3], "stop") == 0) {
				// Stop virtual AIN/BIN input for phase lag count mode.
				// [command] udc port ph_lag stop
				// Stop AIN/BIN
				ct_dd_udc_stop_virtual_ain(cdUdc);
				ct_dd_udc_stop_virtual_bin(cdUdc);
				Ddim_Print(("Stop virtual AIN/BIN OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if (strcmp((KConstType)argv[2], "ain") == 0) { // Virtual input AIN
			if (strcmp((KConstType)argv[3], "start") == 0) { 
				/*
				  Start virtual AIN input
							+----+    +----+    +----+   
							|    |    |    |    |    |   
					AIN ----+    +----+    +----+    +---

				  [command] udc port ain start P1 P2
							P1 : Channel number of UDC(0~3)
							P2 : AIN interval(msec)
				*/
				if (argc >= 6) {
					self->ercd = ct_dd_udc_start_virtual_ain(cdUdc, 
						atoi((KConstType)argv[4]),			// UDC channel number								
						(atoi((KConstType)argv[5]) * 1000)	// Interval(usec)
					);
					if (self->ercd != D_DDIM_OK) {
						Ddim_Print(("ct_dd_udc_start_virtual_ain NG. ercd=%d\n", self->ercd));
						return;
					} else {
						Ddim_Print(("Start virtual AIN OK.\n"));
					}
				} else {
					Ddim_Print(("Command parameter error.\n"));
				}
			} else if (strcmp((KConstType)argv[3], "stop") == 0) {
				// Stop virtual AIN input.
				// [command] udc port ain stop
				ct_dd_udc_stop_virtual_ain(cdUdc);
				Ddim_Print(("Stop virtual AIN OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if (strcmp((KConstType)argv[2], "bin") == 0) { // Virtual input BIN
			if (strcmp((KConstType)argv[3], "start") == 0) {
				/*
				  Start virtual BIN input
							+----+    +----+    +----+   
							|    |    |    |    |    |   
					BIN ----+    +----+    +----+    +---

				  [command] udc port bin start P1 P2
							P1 : Channel number of UDC(0~3)
							P2 : BIN interval(msec)
				*/
				if (argc >= 6) {
					self->ercd = ct_dd_udc_start_virtual_bin(cdUdc, 
						atoi((KConstType)argv[4]),			// UDC channel number
						(atoi((KConstType)argv[5]) * 1000)	// Interval(usec)
					);
					if (self->ercd != D_DDIM_OK) {
						Ddim_Print(("ct_dd_udc_start_virtual_bin NG. ercd=%d\n", self->ercd));
						return;
					} else {
						Ddim_Print(("Start virtual BIN OK.\n"));
					}
				} else {
					Ddim_Print(("Command parameter error.\n"));
				}
			} else if (strcmp((KConstType)argv[3], "stop") == 0) {
				// Stop virtual BIN input.
				// [command] udc port bin stop
				ct_dd_udc_stop_virtual_bin(cdUdc);
				Ddim_Print(("Stop virtual BIN OK.\n"));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if (strcmp((KConstType)argv[2], "zin") == 0) {
			// Change ZIN level
			// [command] udc port zin P1 P2
			//           P1 : Channel number(0~1)
			//           P2 : Level(h: high, l:low)
			if (argc >= 5) {
				ch = atoi((KConstType)argv[3]); // UDC channel number
				cdUdc->ch = ch;

				// Check UDCTRG setting
				if ((DdTopothree_GET_PERSEL2_UDCTRG() == 0) || 
					((DdTopothree_GET_PERSEL2_UDCTRG() == 1) && (ch != 0) && (ch != 1))) {
					Ddim_Print(("UDCTRG setting error. ZIN can't use.\n"));
					return;
				}

				if (strcmp((KConstType)argv[4], "h") == 0) { // ZIN -> High
					ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_ZIN, CtDdUdc_PORT_KIND_PDR, 1);
					Ddim_Print(("ZIN -> High.\n"));
				} else if (strcmp((KConstType)argv[4], "l") == 0) { // ZIN -> Low
					ct_dd_udc_set_port(cdUdc, CtDdUdc_TRG_KIND_ZIN, CtDdUdc_PORT_KIND_PDR, 0);
					Ddim_Print(("ZIN -> Low.\n"));
				} else {
					Ddim_Print(("Command parameter error.\n"));
				}
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "observe") == 0) { // Setting of UDCR observer
		if (strcmp((KConstType)argv[2], "start") == 0) {
			if(argc >= 5) {
				Ddim_Print(("[observe start]\n"));
				// Start cycle handler for observe UDCR register.
				// [command] udc observe start P1 P2
				//           P1 : Channel number(0~3)
				//           P2 : Cycle time(msec)
				cdUdc->gctDdUdcObsCh = atoi((KConstType)argv[3]); // UDC channel number

				// Start timer
				cdUdc->tmrCh = CtDdUdc1_TMR_OBS_CH;
				self->ercd = ct_dd_udc_start_timer32(cdUdc, 
					(atoi((KConstType)argv[4]) * 1000), 
					ctDdUdcObserveUdcr_cd);
				if (self->ercd != D_DDIM_OK) { // Timer execution error.
					Ddim_Print(("ct_dd_udc_start_timer32 NG. ercd=%d\n", self->ercd));
					return;
				}
				Ddim_Print(("Start Ch%d UDCR observer.\n", cdUdc->gctDdUdcObsCh));
			} else {
				Ddim_Print(("Command parameter error.\n"));
				return;
			}
		} else if (strcmp((KConstType)argv[2], "stop") == 0) {
			// Stop cycle handler.
			// [command] udc observe stop
			cdUdc->tmrCh = CtDdUdc1_TMR_OBS_CH;
			ct_dd_udc_stop_timer32(cdUdc);
			Ddim_Print(("Stop UDCR observer.\n"));
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "udctrg") == 0) {
		if (strcmp((KConstType)argv[2], "set") == 0) {
			// Set PERSEL2.UDCTRG
			// [command] udc udctrg set P1
			//           P1 : UpDownCounter Trigger select
			//                0: All channels can use phase lag, can't use zin. 
			//                1: ch0~1 can use phase lag and zin.
			//                   ch2~3 can't use phase lag, zin and up count.
			kuint32 udctrg;
			udctrg = atoi((KConstType)argv[3]);

			switch (udctrg) {
				case 0: // FALL THROUGH 
				case 1:
					DdTopothree_SET_PERSEL2_UDCTRG(udctrg);
					break;

				default:
					Ddim_Print(("Command parameter error. UDCTRG must be 0~1\n"));
					return;
			}
		} else if (strcmp((KConstType)argv[2], "get") == 0) {
			// Get PERSEL2.UDCTRG
			Ddim_Print(("IO_CHIPTOP.PERSEL2.bit.UDCTRG=%d\n", 
				(kuint32)DdTopothree_GET_PERSEL2_UDCTRG()));
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "utility") == 0) {
		if (strcmp((KConstType)argv[2], "start") == 0) {
			// Start utility function.
			// [command] udc utility start P1 P2
			//           P1 : Channel number(0~3)
			//           P2 : Count time(usec)

			//utility function
			Ddim_Print(("Start utility function.\n"));

			// Set UDC ch and count time
			ch = atoi((KConstType)argv[3]);
			self->usec = atol((KConstType)argv[4]);

			// Get peripheral clock
			self->periClock = DdTopone_Get_CLKSEL1_RCLK();
			Ddim_Print(("Top:CLKSEL-A.RCLK = 0x%x\n",self->periClock));

			// Channel error check
			if (ch >= 6) {
				Ddim_Print(("Command parameter error.\n"));
				return;
			}

			// Set utility function parameter
			self->ercd = dd_udc_utility_write_timer_mode(ddUdc, ch, self->usec, ctDdUdcUtilityCallback_cd);
			if (self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_utility_write_timer_mode NG. ercd=%d\n",self->ercd));
				return;
			}

			// Check dividing rate
			self->ercd = dd_udc_get_ctrl_timer(ddUdc, ch, &self->prescaler);
			if (self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_get_ctrl_timer NG. ercd=%d\n",self->ercd));
				return;
			} else {
				Ddim_Print(("CLKS = %d\n",self->prescaler));
			}

			self->ercd = ddim_user_custom_get_tim(ddimUserCus, &cdUdc->gctDdUdcTimUtilSta);
			if (self->ercd != DdimUserCustom_E_OK) {
				Ddim_Print(("UDC utility function: get_tim NG. ercd=%d\n", self->ercd));
				return;
			}

			// Check utility function parameter
			self->ercd = dd_udc_get_ctrl_common(ddUdc, ch,&self->udcCrl);
			if (self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_get_ctrl_common NG. ercd=%d\n",self->ercd));
				return;
			}
			cdUdc->ch = ch;
			ct_dd_udc_print_crl_common(cdUdc, &self->udcCrl);

			// Start utility function
			self->ercd = dd_udc_start(ddUdc, ch);
			if (self->ercd != D_DDIM_OK) {
				Ddim_Print(("dd_udc_start NG. ercd=%d\n",self->ercd));
				return;
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}
	} else if(strcmp((KConstType)argv[1], "err") == 0) {
		// Error processing test
		// [command] udc err
		if(strcmp((KConstType)argv[2], "ctrl_common") == 0) { // [dd_udc_ctrl_common]
			if(strcmp((KConstType)argv[3], "p1") == 0) {     //   - Channel number is illegal.
				self->ercd = dd_udc_ctrl_common(ddUdc, 6, &self->udcCrl);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_common(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { //   - udcCrl parameter is NULL.
				self->ercd = dd_udc_ctrl_common(ddUdc, 0, NULL);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_common(): udcCrl parameter is NULL. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "get_ctrl_common") == 0) { // [dd_udc_get_ctrl_common]
			if(strcmp((KConstType)argv[3], "p1") == 0) {     			//   - Channel number is illegal.
				self->ercd = dd_udc_get_ctrl_common(ddUdc, 6, &self->udcCrl);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_common(): Channel number is illegal.ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { 			//   - udcCrl parameter is NULL.
				self->ercd = dd_udc_get_ctrl_common(ddUdc, 0, NULL);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_common(): udcCrl parameter is NULL. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "ctrl_timer") == 0) { 		// [dd_udc_ctrl_timer]
			if(strcmp((KConstType)argv[3], "p1") == 0) {     			//   - Channel number is illegal.
				self->ercd = dd_udc_ctrl_timer(ddUdc, 6, DdUdc_CLKS_2_CLOCK);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_timer(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { 			//   - Prescaler is illegal.
				self->ercd = dd_udc_ctrl_timer(ddUdc, DdUdc_CH0, 2);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_timer(): Prescaler is illegal. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "get_ctrl_timer") == 0) { 	// [dd_udc_get_ctrl_timer]
			if(strcmp((KConstType)argv[3], "p1") == 0) {      			//   - Channel number is illegal.
				self->ercd = dd_udc_get_ctrl_timer(ddUdc, 6, &self->prescaler);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_timer(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { 			//   - prescaler parameter is NULL.
				self->ercd = dd_udc_get_ctrl_timer(ddUdc, 0, NULL);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_timer(): prescaler parameter is NULL.ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "ctrl_up_down") == 0) { 	// [dd_udc_ctrl_up_down]
			if(strcmp((KConstType)argv[3], "p1") == 0) {     			//   - Channel number is illegal.
				self->ercd = dd_udc_ctrl_up_down(ddUdc, 6, DdUdc_CES_RISE);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_up_down(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { 			//   - Edge is illegal.
				self->ercd = dd_udc_ctrl_up_down(ddUdc, DdUdc_CH0, 4);
				Ddim_Print((
					"[Error Test] dd_udc_ctrl_up_down(): Edge is illegal. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "get_ctrl_up_down") == 0) { // [dd_udc_get_ctrl_up_down]
			if(strcmp((KConstType)argv[3], "p1") == 0) {				//   - Channel number is illegal.
				self->ercd = dd_udc_get_ctrl_up_down(ddUdc, 6, &self->edge);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_up_down(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) {
				//   - edge parameter is NULL.
				self->ercd = dd_udc_get_ctrl_up_down(ddUdc, 0, NULL);
				Ddim_Print((
					"[Error Test] dd_udc_get_ctrl_up_down(): edge parameter is NULL. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "start") == 0) {
			// [dd_udc_start]
			//   - Channel number is illegal.
			self->ercd = dd_udc_start(ddUdc, 6);
			Ddim_Print(("[Error Test] dd_udc_start(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "stop") == 0) {
			// [dd_udc_stop]
			//   - Channel number is illegal.
			self->ercd = dd_udc_stop(ddUdc, 6);
			Ddim_Print(("[Error Test] dd_udc_stop(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "callback") == 0) {
			// [dd_udc_set_callback]
			//   - Channel number is illegal.
			dd_udc_set_callback(ddUdc, 6, ctDdUdcCallback_cd);
		} else if(strcmp((KConstType)argv[2], "set_rcr_counter") == 0) {
			// [dd_udc_set_rcr_counter]
			//   - Channel number is illegal.
			self->ercd = dd_udc_set_rcr_counter(ddUdc, 6, 10000);
			Ddim_Print((
				"[Error Test] dd_udc_set_rcr_counter(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "get_udcr_counter") == 0) {
			// [dd_udc_get_udcr_counter]
			//   - Channel number is illegal.
			self->ercd = dd_udc_get_udcr_counter(ddUdc, 6);
			Ddim_Print((
				"[Error Test] dd_udc_get_udcr_counter(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "set_udcr_counter") == 0) {
			// [dd_udc_set_udcr_counter]
			//   - Channel number is illegal.
			self->ercd = dd_udc_set_udcr_counter(ddUdc, 6, 10000);
			Ddim_Print((
				"[Error Test] dd_udc_set_udcr_counter(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "force_clear_udcr") == 0) {
			// [dd_udc_force_clear_udcr]
			//   - Channel number is illegal.
			self->ercd = dd_udc_force_clear_udcr(ddUdc, 6);
			Ddim_Print((
				"[Error Test] dd_udc_force_clear_udcr(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "get_up_down_flg") == 0) {
			// [dd_udc_get_up_down_flg]
			//   - Channel number is illegal.
			self->ercd = dd_udc_get_up_down_flg(ddUdc, 6);
			Ddim_Print((
				"[Error Test] dd_udc_get_up_down_flg(): Channel number is illegal. ercd=%d\n", self->ercd));
		} else if(strcmp((KConstType)argv[2], "set_count_mode") == 0) {
			// [dd_udc_set_count_mode]
			if(strcmp((KConstType)argv[3], "p1") == 0) {     //   - Channel number is illegal.
				self->ercd = dd_udc_set_count_mode(ddUdc, 6, DdUdc_CMS_TIMER);
				Ddim_Print((
					"[Error Test] dd_udc_set_count_mode(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p2") == 0) { //   - Count mode is illegal.
				self->ercd = dd_udc_set_count_mode(ddUdc, DdUdc_CH0, 4);
				Ddim_Print((
					"[Error Test] dd_udc_set_count_mode(): Count mode is illegal. ercd=%d\n", self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else if(strcmp((KConstType)argv[2], "write_timer_mode") == 0) { // [dd_udc_utility_write_timer_mode]
			if(strcmp((KConstType)argv[3], "p1") == 0) {      			//   - Channel number is illegal.
				self->ercd = dd_udc_utility_write_timer_mode(ddUdc, 6, 100, ctDdUdcUtilityCallback_cd);
				Ddim_Print((
					"[Error Test] dd_udc_utility_write_timer_mode(): Channel number is illegal. ercd=%d\n", self->ercd));
			} else if(strcmp((KConstType)argv[3], "p3") == 0) { 			//   - timer_callback parameter is NULL.
				self->ercd = dd_udc_utility_write_timer_mode(ddUdc, DdUdc_CH0, 100, NULL);
				Ddim_Print((
					"[Error Test] dd_udc_utility_write_timer_mode(): timer_callback parameter is NULL. ercd=%d\n",
					self->ercd));
			} else {
				Ddim_Print(("Command parameter error.\n"));
			}
		} else {
			Ddim_Print(("Command parameter error.\n"));
		}

	} else {
		Ddim_Print(("Command parameter error.\n"));
	}
	k_object_unref(cdUdc);
	cdUdc = NULL;
	k_object_unref(ddUdc);
	ddUdc = NULL;
	k_object_unref(ddimUserCus);
	ddimUserCus = NULL; 
}

kuchar ct_dd_udc1_get_obs_ch(CtDdUdc1 *self)
{
	return self->gctDdUdcObsCh;
}

kulonglong ct_dd_udc1_get_tim_util_sta(CtDdUdc1 *self)
{
	return self->gctDdUdcTimUtilSta;
}

CtDdUdc1 *ct_dd_udc1_new(void)
{
	CtDdUdc1 *self = k_object_new_with_private(CT_TYPE_DD_UDC1, sizeof(CtDdUdc1Private));
	return self;
}
