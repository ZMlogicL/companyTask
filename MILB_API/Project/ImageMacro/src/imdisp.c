/*
 * imdisp.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "jdsdisp3a.h"
#include "imdisp.h"
#include "imdisp1.h"
#include "imdisp8.h"
#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>


K_TYPE_DEFINE_WITH_PRIVATE(ImDisp, im_disp)
#define IM_DISP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDispPrivate,IM_TYPE_DISP))


struct _ImDispPrivate
{
	int a;
};

static void im_disp_constructor(ImDisp *self)
{
	//ImDispPrivate *priv = IM_DISP_GET_PRIVATE(self);
}

static void im_disp_destructor(ImDisp *self)
{
	//ImDispPrivate *priv = IM_DISP_GET_PRIVATE(self);
}


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
//---------------------- colabo  section -------------------------------
#endif // CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Global Data  														*/
/*----------------------------------------------------------------------*/
#ifdef CO_ACT_PCLOCK
#ifdef CO_DEBUG_DISP
// PCLK_Disp setting task counter (0~255)
volatile UCHAR gimDispApbClockCounter  = 0;
#else
// PCLK_Disp setting task counter (0~255)
static volatile UCHAR S_GIM_DISP_APB_CLOCK_COUNTER  = 0;
#endif // CO_DEBUG_DISP
#endif // CO_ACT_PCLOCK

#ifdef CO_ACT_HCLOCK
#ifdef CO_DEBUG_DISP
// HCLK_Disp setting task counter (0~255)
volatile UCHAR gimDispAhbClockCounter  = 0;
#else
// HCLK_Disp setting task counter (0~255)
static volatile UCHAR S_GIM_DISP_AHB_CLOCK_COUNTER  = 0;
#endif // CO_DEBUG_DISP
#endif // CO_ACT_HCLOCK

#ifdef SOURCE_CHECKER
#define __builtin_offsetof( type, member ) (1)	// Workaround of stddef.h by gcc-4.9.3
#endif

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//#define CO_DEBUG_DISP
//---------------------- driver  section -------------------------------
// Interrupt flag
#define D_IM_DISP_FLG_LEF				(0x00000001)	/**< Main inpuut error flag			*/
#define D_IM_DISP_FLG_GR0EF				(0x00000010)	/**< GR0 error flag					*/
#define D_IM_DISP_FLG_GR1EF				(0x00000020)	/**< GR1 error flag					*/
#define D_IM_DISP_FLG_GA0EF				(0x00000040)	/**< GR0 A component error flag		*/
#define D_IM_DISP_FLG_GA1EF				(0x00000080)	/**< GR1 A component error flag		*/
#define D_IM_DISP_FLG_LREE				(0x00000100)	/**< Main inpuut AXI error flag		*/
#define D_IM_DISP_FLG_GR0REF			(0x00001000)	/**< GR0 AXI error flag				*/
#define D_IM_DISP_FLG_GR1REF			(0x00002000)	/**< GR1 AXI error flag				*/
#define D_IM_DISP_FLG_GA0REF			(0x00004000)	/**< GR0 A component AXI error flag	*/
#define D_IM_DISP_FLG_GA1REF			(0x00008000)	/**< GR1 A component AXI error flag	*/
#define D_IM_DISP_FLG_VE 				(0x00010000)	/**< Main VSYNC flag				*/
#define D_IM_DISP_FLG_VE2 				(0x00020000)	/**< Main VSYNC flag for 2nd field	*/
#define im_disp_get_reg_signed_a( val, reg, type, member )		\
		{ \
			type work = { .word[0] = 0UL }; \
			work.bit.member = -1L; \
			if( ((work.bit.member) == 0xFFFFFFFFUL) || ((reg.bit.member) <= ((work.bit.member) /2)) ) { \
				(val) = reg.bit.member; \
			} \
			else { \
				(val) = -(work.bit.member - reg.bit.member +1); \
			} \
			im_disp_check_reg_type( (reg), work );	/* The structure type matching check. */ \
		}

// Write channel block(P2M/PWCH) force stop flag.
static volatile UCHAR S_GIM_DISP_WC_FORCE_STOP = D_IM_DISP_ENABLE_OFF;
// Spin Lock
static ULONG S_GIM_DISP_SPIN_LOCK __attribute__((section(".LOCK_SECTION"), aligned(64))) = 0;

/**
It is confirmed whether TRG can be set up.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	start_stop		Startup status.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_WRITE_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_READ_NO_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_READ_ACT</ul>
@retval	D_DDIM_OK				Normal end.
@retval	D_IM_DISP_ACCESS_ERR	TRG cannot be set up.
*/
static INT32 imDispIsTrgSet(ImDispEImDispSel block, ImDispEImDispTrg start_stop)
{
	INT32 ret = D_DDIM_OK;
	ULONG ifs = 0;

	if(start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) {
		ifs = IO_DISP.MAIN[block].DCORE.IFS.bit.IFS;
		switch (ifs) {
			case D_IM_DISP_IFS_LCD:		// LCD.
				if( Dd_Top_Get_CLKSTOP3_LCDCK() != 0 ) {
					Im_DISP_Check_Point(("CP:imDispIsTrgSet() : LCD clock stoped.\n"));
					ret = D_IM_DISP_ACCESS_ERR;
				}
				break;
			case D_IM_DISP_IFS_HDMI:	// HDMI.
				if( Dd_Top_Get_CLKSTOP3_HIFCK() != 0 ) {
					Im_DISP_Check_Point(("CP:imDispIsTrgSet() : HDMI clock stoped.\n"));
					ret = D_IM_DISP_ACCESS_ERR;
				}
				break;
			case D_IM_DISP_IFS_MIPI:	// MIPI.
				if( Dd_Top_Get_CLKSTOP3_MIFCK() != 0 ) {
					Im_DISP_Check_Point(("CP:imDispIsTrgSet() : MIPI clock stoped.\n"));
					ret = D_IM_DISP_ACCESS_ERR;
				}
				break;
			default:					// Not select.
				Im_DISP_Check_Point(("CP:imDispIsTrgSet() : Display I/F not select.\n"));
				ret = D_IM_DISP_ACCESS_ERR;
				break;
		}
	}
	else{
		// do nothing.
	}
	return ret;
}

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/* DISP PCLK change to ON
*/
VOID im_disp_pclk_on(ImDisp *self)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_On();
#endif	// CO_ACT_PCLOCK
}

/* DISP PCLK change to OFF
*/
VOID im_disp_pclk_off(ImDisp *self)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_Off();
#endif	// CO_ACT_PCLOCK
}

/* DISP HCLK change to ON
*/
 VOID im_disp_hclk_on(ImDisp *self)
{
#ifdef CO_ACT_HCLOCK
	Im_DISP_AHB_Clock_On();
#endif	// CO_ACT_HCLOCK
}

/* DISP HCLK change to OFF
*/
VOID im_disp_hclk_off(ImDisp *self)
{
#ifdef CO_ACT_HCLOCK
	Im_DISP_AHB_Clock_Off();
#endif	// CO_ACT_HCLOCK
}

/**
Copy Gamma table to IO_DISP or IO_DISP to Gamma table.
@param[in]	table_top				gamma table top address.<br>
@param[in]	register_table_top		gamma table register top address.<br>
@param[in]	correct					Correct selection.<br>
									<ul><li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA
										<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN
										<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT
										<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_LUMINANCE
										<li>@ref ImDisp_E_IM_DISP_CORRECT_SELECT_CHROMA</ul>
@param[in]	access					Set or get.<br>
									<ul><li>@ref ImDisp_E_IM_DISP_ACCESS_GAMMA_SET
										<li>@ref ImDisp_E_IM_DISP_ACCESS_GAMMA_GET</ul>
*/
VOID im_disp_access_gamma_table(ImDisp *self, BYTE* table_top,
									 const BYTE* register_table_top,
									 const ImDispEImDispCorrectSelect correct,
									 const ImDispEImDispAccessGamma access)
{
	INT32 loop;
	INT32 array_num;
	BYTE** tbl_address;
	BYTE* tbl_register_address;

	// table index
	UINT32 anti_gamma_tbl_index[] = {
		offsetof(T_IM_DISP_ANTI_GAMMA_TBL, r_anti),
		offsetof(T_IM_DISP_ANTI_GAMMA_TBL, g_anti),
		offsetof(T_IM_DISP_ANTI_GAMMA_TBL, b_anti)
	};
	UINT32 gamma_tbl_in_index[] = {
		offsetof(T_IM_DISP_GAMMA_TBL_IN, r_data),
		offsetof(T_IM_DISP_GAMMA_TBL_IN, g_data),
		offsetof(T_IM_DISP_GAMMA_TBL_IN, b_data),
	};
	UINT32 gamma_tbl_out_index[] = {
		offsetof(T_IM_DISP_GAMMA_TBL_OUT, r_data),
		offsetof(T_IM_DISP_GAMMA_TBL_OUT, g_data),
		offsetof(T_IM_DISP_GAMMA_TBL_OUT, b_data),
	};
	
	// register table index
	UINT32 anti_gamma_tbl_register_index[] = {
		offsetof(struct io_jdslch_igtbl_rgb, IGTBLR),
		offsetof(struct io_jdslch_igtbl_rgb, IGTBLG),
		offsetof(struct io_jdslch_igtbl_rgb, IGTBLB)
	};
	UINT32 gamma_tbl_in_register_index[] = {
		offsetof(struct io_jdslch_gtbl_rgb, GTBLR),
		offsetof(struct io_jdslch_gtbl_rgb, GTBLG),
		offsetof(struct io_jdslch_gtbl_rgb, GTBLB),
	};
	UINT32 gamma_tbl_out_register_index[] = {
		offsetof(struct io_jdsdcore_gtbl_rgb, GTBLR),
		offsetof(struct io_jdsdcore_gtbl_rgb, GTBLG),
		offsetof(struct io_jdsdcore_gtbl_rgb, GTBLB),
	};

	// table size
	UINT32 anti_gamma_tbl_size[] = {
		sizeof(IO_DISP_TBL.MAIN[0].LCH.IGTBLA.IGTBLR),
		sizeof(IO_DISP_TBL.MAIN[0].LCH.IGTBLA.IGTBLG),
		sizeof(IO_DISP_TBL.MAIN[0].LCH.IGTBLA.IGTBLB)
	};
	UINT32 gamma_tbl_in_size[] = {
		sizeof(IO_DISP_TBL.MAIN[0].LCH.GTBLA.GTBLR),
		sizeof(IO_DISP_TBL.MAIN[0].LCH.GTBLA.GTBLG),
		sizeof(IO_DISP_TBL.MAIN[0].LCH.GTBLA.GTBLB)
	};
	UINT32 gamma_tbl_out_size[] = {
		sizeof(IO_DISP_TBL.MAIN[0].DCORE.GTBLA.GTBLR),
		sizeof(IO_DISP_TBL.MAIN[0].DCORE.GTBLA.GTBLG),
		sizeof(IO_DISP_TBL.MAIN[0].DCORE.GTBLA.GTBLB)
	};

	switch (correct) {
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ANTI_GAMMA:			// Anti Gamma.
			array_num = sizeof(anti_gamma_tbl_index) / sizeof(anti_gamma_tbl_index[0]);
			for(loop = 0; loop < array_num; loop++) {
				tbl_address = (BYTE**)(table_top + anti_gamma_tbl_index[loop]);
				tbl_register_address = (BYTE*)(register_table_top + anti_gamma_tbl_register_index[loop]);
				// check address
				if (((*tbl_address) != NULL) && ((tbl_register_address) != NULL)) {
					if (access == ImDisp_E_IM_DISP_ACCESS_GAMMA_SET){
						// Set table data
						memcpy((tbl_register_address), (*tbl_address), anti_gamma_tbl_size[loop]);
					}
					else {
						// Get table data
						memcpy((*tbl_address), (tbl_register_address), anti_gamma_tbl_size[loop]);
					}
				}
			}
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_IN:				// Gamma (Main data input block).
			array_num = sizeof(gamma_tbl_in_index) / sizeof(gamma_tbl_in_index[0]);
			for(loop = 0; loop < array_num; loop++) {
				tbl_address = (BYTE**)(table_top + gamma_tbl_in_index[loop]);
				tbl_register_address = (BYTE*)(register_table_top + gamma_tbl_in_register_index[loop]);
				// check address
				if (((*tbl_address) != NULL) && ((tbl_register_address) != NULL)) {
					if (access == ImDisp_E_IM_DISP_ACCESS_GAMMA_SET){
						// Set table data
						memcpy((tbl_register_address), (*tbl_address), gamma_tbl_in_size[loop]);
					}
					else {
						// Get table data
						memcpy((*tbl_address), (tbl_register_address), gamma_tbl_in_size[loop]);
					}
				}
			}
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_GAMMA_OUT:				// Gamma (Data output block).
			array_num = sizeof(gamma_tbl_out_index) / sizeof(gamma_tbl_out_index[0]);
			for(loop = 0; loop < array_num; loop++) {
				tbl_address = (BYTE**)(table_top + gamma_tbl_out_index[loop]);
				tbl_register_address = (BYTE*)(register_table_top + gamma_tbl_out_register_index[loop]);
				// check address
				if (((*tbl_address) != NULL) && ((tbl_register_address) != NULL)) {
					if (access == ImDisp_E_IM_DISP_ACCESS_GAMMA_SET){
						// Set table data
						memcpy((tbl_register_address), (*tbl_address), gamma_tbl_out_size[loop]);
					}
					else {
						// Get table data
						memcpy((*tbl_address), (tbl_register_address), gamma_tbl_out_size[loop]);
					}
				}
			}
			break;
		default:												// Luminance or Chroma.
			// check address
			tbl_address = (BYTE**)(table_top);
			tbl_register_address = (BYTE*)(register_table_top);
			if (((*tbl_address) != NULL) && ((tbl_register_address) != NULL)) {
				if (access == ImDisp_E_IM_DISP_ACCESS_GAMMA_SET) {
					// Set table data
					memcpy((tbl_register_address), (*tbl_address), sizeof(IO_DISP_TBL.MAIN[0].DCORE.YSTBLAYT));
				}
				else {
					// Get table data
					memcpy((*tbl_address), (tbl_register_address), sizeof(IO_DISP_TBL.MAIN[0].DCORE.YSTBLAYT));
				}
			}
			break;
	}
}

/**
Wait the channel stop.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer		layer selection.<br>
						(Two or more layer can be specified by the OR value.)<br>
						<ul><li>@ref E_IM_DISP_SEL_LAYER_MAIN
							<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
							<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
							<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	act			ImDisp_E_IM_DISP_TRG_READ_NO_ACT: Wait stop.ImDisp_E_IM_DISP_TRG_READ_ACT: Wait Start.
@retval	D_DDIM_OK				Normal end.
@retval	D_IM_DISP_TIMEOUT		The channel cannot stop within 33ms.
*/
 INT32 im_disp_wait_trg_stop_start(ImDisp *self, ImDispEImDispSel block, UINT32 layer, UINT32 act)
{
	INT32 ret = D_DDIM_OK;
	INT32 wait_counter = 0;
	INT32 loop;
	INT32 array_num;
	UINT32 stopped_channel_bit_map = layer;
	UINT32 trgger;

	UINT32 layer_id[] ={
		E_IM_DISP_SEL_LAYER_MAIN,
		E_IM_DISP_SEL_LAYER_DCORE,
		E_IM_DISP_SEL_LAYER_OSD_0,
		E_IM_DISP_SEL_LAYER_OSD_1
	};

	while(wait_counter < D_IM_DISP_VSYNC_TIME) {
		// Wait tgr stop
		im_disp_pclk_on(im_disp_new());
		array_num = sizeof(layer_id) / sizeof(layer_id[0]);
		for(loop = 0; loop < array_num; loop++) {
			switch( stopped_channel_bit_map & layer_id[loop]){
				// this channel had not stopped, yet.
				case E_IM_DISP_SEL_LAYER_MAIN:
					trgger = IO_DISP.MAIN[block].LCH.LTRG.word;
					break;
				case E_IM_DISP_SEL_LAYER_DCORE:
					trgger = IO_DISP.MAIN[block].DCORE.TRG.bit.TRG;
					break;
				case E_IM_DISP_SEL_LAYER_OSD_0:
					trgger = IO_DISP.MAIN[block].GRCH[0].GRTRG.word;
					break;
				case E_IM_DISP_SEL_LAYER_OSD_1:
					trgger = IO_DISP.MAIN[block].GRCH[1].GRTRG.word;
					break;
				default:
					// Check next trigger
					continue;
			}

			if(trgger == act) {
				stopped_channel_bit_map &= (~(layer_id[loop]));
			}
		}
		im_disp_pclk_off(im_disp_new());

		if(stopped_channel_bit_map == 0){
			// The channels want to stop were stopped
			break;
		}
		wait_counter++;
		DDIM_User_Dly_Tsk(1);
#ifdef CO_DEBUG_ON_PC
		stopped_channel_bit_map = 0;	// to avoid time out error.
#endif // CO_DEBUG_ON_PC
	}
	if(stopped_channel_bit_map){
		// Can not stop within 33 ms
		Im_DISP_Check_Point(("CP:im_disp_wait_trg_stop_start(im_disp_new()) 1\n"));
		ret = D_IM_DISP_TIMEOUT;
	}
	return ret;
}

/**
Start/stop Main layer.
@param[in]	block			Common block selection.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_HDMI
								<li>@ref ImDisp_E_IM_DISP_LCD_MIPI</ul>
@param[in]	layer			layer selection.<br>
							(Two or more layer can be specified by the OR value.)<br>
							<ul><li>@ref E_IM_DISP_SEL_LAYER_MAIN
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_0
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_1
								<li>@ref E_IM_DISP_SEL_LAYER_OSD_ALL</ul>
@param[in]	write_channel	Write channel block selection.<br>
							Value:<br>
							0 : not select<br>
							1 : Write channel 0 (Luminance data)<br>
							2 : Write channel 1 (Chrominance data)<br>
							3 : Write channel 0 & 1<br>
@param[in]	start_stop		Startup status.<br>
							<ul><li>@ref ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_WRITE_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_READ_NO_ACT
								<li>@ref ImDisp_E_IM_DISP_TRG_READ_ACT</ul>
@retval	D_DDIM_OK						Normal end.
@retval	D_IM_DISP_INPUT_PARAM_ERROR		Input parameter error.
@retval	D_IM_DISP_TIMEOUT				The channel cannot stop within 33ms.
@retval	D_IM_DISP_ACCESS_ERR			TRG cannot be set up.
*/
INT32 im_disp_set_trg(ImDisp *self, ImDispEImDispSel block, UINT32 layer, BYTE write_channel, ImDispEImDispTrg start_stop)
{
	// Wait
	INT32 ret = D_DDIM_OK;
	UINT32 act = ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT;
	E_IM_DISP_P2M_PWCH_TRG wc_trg = E_IM_DISP_P2M_PWCH_TRG_READ_NO_ACT;
	INT32 loop;
	INT32 wc_num[2] = { 1, 2};	// Write channel 0, Write channel 1.

	switch(start_stop) {
		case  ImDisp_E_IM_DISP_TRG_WRITE_ACT:		// Start
			// To set start must be at stopping state
			act = ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
			break;
		case ImDisp_E_IM_DISP_TRG_READ_NO_ACT:		// Stop
		case ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT:
			act = ImDisp_E_IM_DISP_TRG_READ_ACT;
			break;
		default:
			// do nothing
			Im_DISP_Check_Point(("CP:im_disp_set_trg(im_disp_new()) 1\n"));
			ret = D_IM_DISP_INPUT_PARAM_ERROR;
			break;
	}
	if(ret == D_DDIM_OK) {
		// Main data input block
		if ((layer & E_IM_DISP_SEL_LAYER_MAIN) == E_IM_DISP_SEL_LAYER_MAIN) {
			// wait
			if (im_disp_wait_trg_stop_start(im_disp_new(), block, E_IM_DISP_SEL_LAYER_MAIN, act) == D_DDIM_OK) {
				// check trigger status
				if ((start_stop == ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT) ||
					(start_stop == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
					(IO_DISP.MAIN[block].LCH.LTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)){

					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GIM_DISP_SPIN_LOCK);

					ret = imDispIsTrgSet(block, start_stop);
					if(ret == D_DDIM_OK) {
						// Set trigger
						IO_DISP.MAIN[block].LCH.LTRG.word = start_stop;
#ifdef CO_DEBUG_ON_PC
						IO_DISP.MAIN[block].LCH.LTRG.word = (start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) ? ImDisp_E_IM_DISP_TRG_READ_ACT : ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
#endif // CO_DEBUG_ON_PC
					}

					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GIM_DISP_SPIN_LOCK);
				}
			}
		}
	}
	if(ret == D_DDIM_OK) {
		// OSD_0 data input block
		if ((layer & E_IM_DISP_SEL_LAYER_OSD_0) == E_IM_DISP_SEL_LAYER_OSD_0) {
			// wait
			if (im_disp_wait_trg_stop_start(im_disp_new(), block, E_IM_DISP_SEL_LAYER_OSD_0, act) == D_DDIM_OK) {
				// check trigger status
				if ((start_stop == ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT) ||
					(start_stop == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
					(IO_DISP.MAIN[block].GRCH[0].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)){

					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GIM_DISP_SPIN_LOCK);

					ret = imDispIsTrgSet(block, start_stop);
					if(ret == D_DDIM_OK) {
						// Set trigger
						IO_DISP.MAIN[block].GRCH[0].GRTRG.word = start_stop;
#ifdef CO_DEBUG_ON_PC
						IO_DISP.MAIN[block].GRCH[0].GRTRG.word = (start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) ? ImDisp_E_IM_DISP_TRG_READ_ACT : ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
#endif // CO_DEBUG_ON_PC
					}
					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GIM_DISP_SPIN_LOCK);
				}
			}
		}
	}
	if(ret == D_DDIM_OK) {
		// OSD_1 data input block
		if ((layer & E_IM_DISP_SEL_LAYER_OSD_1) == E_IM_DISP_SEL_LAYER_OSD_1) {
			// wait
			if (im_disp_wait_trg_stop_start(im_disp_new(), block, E_IM_DISP_SEL_LAYER_OSD_1, act) == D_DDIM_OK) {
				// check trigger status
				if ((start_stop == ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT) ||
					(start_stop == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
					(IO_DISP.MAIN[block].GRCH[1].GRTRG.word == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)){

					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GIM_DISP_SPIN_LOCK);

					ret = imDispIsTrgSet(block, start_stop);
					if(ret == D_DDIM_OK) {
						// Set trigger
						IO_DISP.MAIN[block].GRCH[1].GRTRG.word = start_stop;
#ifdef CO_DEBUG_ON_PC
						IO_DISP.MAIN[block].GRCH[1].GRTRG.word = (start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) ? ImDisp_E_IM_DISP_TRG_READ_ACT : ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
#endif // CO_DEBUG_ON_PC
					}

					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GIM_DISP_SPIN_LOCK);
				}
			}
		}
	}
	if(ret == D_DDIM_OK) {
		// Write channel block(PWCH macro, P2M macro).
		for (loop = 0; loop < 2; loop++) {
			// check write channel number.
			if ((write_channel & wc_num[loop]) == wc_num[loop]) {
				// set write channel trigger.
				if (start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) {
					// After forcibly stopped, if it is not already stopped.
					if ((S_GIM_DISP_WC_FORCE_STOP == D_IM_DISP_ENABLE_ON) &&
						((IO_DISP.PWCH[loop].PWCHTRG.bit.PWCHTRG == E_IM_DISP_P2M_PWCH_TRG_READ_ACT) ||
						 (IO_DISP.P2M[loop].P2MTRG.bit.P2MTRG == E_IM_DISP_P2M_PWCH_TRG_READ_ACT)))
					{
						// not set trigger.
						break;
					}

					// start.
					wc_trg = E_IM_DISP_P2M_PWCH_TRG_WRITE_START;

					// force stop flag OFF.
					S_GIM_DISP_WC_FORCE_STOP = D_IM_DISP_ENABLE_OFF;
				}
				else if (start_stop == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) {
					// stop.
					wc_trg = E_IM_DISP_P2M_PWCH_TRG_WRITE_STOP;

					// force stop flag OFF.
					S_GIM_DISP_WC_FORCE_STOP = D_IM_DISP_ENABLE_OFF;
				}
				else {
					// force stop.
					wc_trg = E_IM_DISP_P2M_PWCH_TRG_READ_NO_ACT;

					// force stop flag ON.
					S_GIM_DISP_WC_FORCE_STOP = D_IM_DISP_ENABLE_ON;
				}

				// Set PWCH TRG.
				IO_DISP.PWCH[loop].PWCHTRG.bit.PWCHTRG	= wc_trg;
				// Set P2M TRG.
				IO_DISP.P2M[loop].P2MTRG.bit.P2MTRG		= wc_trg;
			}
		}
	}

	if(ret == D_DDIM_OK) {
		// Output data input block
		if ((layer & E_IM_DISP_SEL_LAYER_DCORE) == E_IM_DISP_SEL_LAYER_DCORE) {
			// wait
			if (im_disp_wait_trg_stop_start(im_disp_new(), block, E_IM_DISP_SEL_LAYER_DCORE, act) == D_DDIM_OK) {
				// check trigger status
				if ((start_stop == ImDisp_E_IM_DISP_TRG_WRITE_NO_ACT) ||
					(start_stop == ImDisp_E_IM_DISP_TRG_READ_NO_ACT) ||
					(IO_DISP.MAIN[block].DCORE.TRG.bit.TRG == ImDisp_E_IM_DISP_TRG_READ_NO_ACT)){
					// DCORE and other layer access
					if (layer != E_IM_DISP_SEL_LAYER_DCORE) {
						// wait
						DDIM_User_Dly_Tsk(20);
					}

					// SpinLock.
					Dd_ARM_Critical_Section_Start(S_GIM_DISP_SPIN_LOCK);

					ret = imDispIsTrgSet(block, start_stop);
					if(ret == D_DDIM_OK) {
						// Set trigger
						IO_DISP.MAIN[block].DCORE.TRG.bit.TRG = start_stop;
#ifdef CO_DEBUG_ON_PC
						IO_DISP.MAIN[block].DCORE.TRG.bit.TRG = (start_stop == ImDisp_E_IM_DISP_TRG_WRITE_ACT) ? ImDisp_E_IM_DISP_TRG_READ_ACT : ImDisp_E_IM_DISP_TRG_READ_NO_ACT;
#endif // CO_DEBUG_ON_PC
					}

					// SpinUnLock.
					Dd_ARM_Critical_Section_End(S_GIM_DISP_SPIN_LOCK);
				}
			}
		}
	}
	return ret;
}

/**
Get the event flag of vertical synchronization interrupt.
@param[in]	interrupt_type	interrupt type
@return The event flag.
*/
UINT32 im_disp_get_event_flag(ImDisp *self, ImDispEImDispInterruptionSelect interrupt_type)
{
	UINT32 disp_flg;

	// Set GR/Main flag
	switch(interrupt_type) {
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE:
			disp_flg = D_IM_DISP_FLG_VE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2:
			disp_flg = D_IM_DISP_FLG_VE2;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE:
			disp_flg = D_IM_DISP_FLG_GA0EF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE:
			disp_flg = D_IM_DISP_FLG_GA1EF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE:
			disp_flg = D_IM_DISP_FLG_GR0EF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE:
			disp_flg = D_IM_DISP_FLG_GR1EF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE:
			disp_flg = D_IM_DISP_FLG_LEF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE:
			disp_flg = D_IM_DISP_FLG_GA0REF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE:
			disp_flg = D_IM_DISP_FLG_GA1REF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE:
			disp_flg = D_IM_DISP_FLG_GR0REF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE:
			disp_flg = D_IM_DISP_FLG_GR1REF;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE:
			disp_flg = D_IM_DISP_FLG_LREE;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_VE:
			disp_flg =  D_IM_DISP_FLG_VE |
						D_IM_DISP_FLG_VE2;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_GRREE:
			disp_flg =  D_IM_DISP_FLG_GR0REF |
						D_IM_DISP_FLG_GR1REF |
						D_IM_DISP_FLG_GA0REF |
						D_IM_DISP_FLG_GA1REF;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_GREE:
			disp_flg =  D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_REE:
			disp_flg =  D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF |
						D_IM_DISP_FLG_LREE;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_EE:
			disp_flg =  D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF |
						D_IM_DISP_FLG_LEF;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_GR_ERROR:
			disp_flg =  D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF |
						D_IM_DISP_FLG_GR0REF |
						D_IM_DISP_FLG_GR1REF |
						D_IM_DISP_FLG_GA0REF |
						D_IM_DISP_FLG_GA1REF;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_MIAN_ERROR:
			disp_flg =  D_IM_DISP_FLG_LREE |
						D_IM_DISP_FLG_LEF;
			break;
		case ImDisp_E_IM_DISP_CORRECT_SELECT_ALL_ERROR:
			disp_flg =  D_IM_DISP_FLG_LEF |
						D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF |
						D_IM_DISP_FLG_LREE |
						D_IM_DISP_FLG_GR0REF |
						D_IM_DISP_FLG_GR1REF |
						D_IM_DISP_FLG_GA0REF |
						D_IM_DISP_FLG_GA1REF;
			break;
		default: // ImDisp_E_IM_DISP_CORRECT_SELECT_ALL
			disp_flg =  D_IM_DISP_FLG_LEF |
						D_IM_DISP_FLG_GR0EF |
						D_IM_DISP_FLG_GR1EF |
						D_IM_DISP_FLG_GA0EF |
						D_IM_DISP_FLG_GA1EF |
						D_IM_DISP_FLG_LREE |
						D_IM_DISP_FLG_GR0REF |
						D_IM_DISP_FLG_GR1REF |
						D_IM_DISP_FLG_GA0REF |
						D_IM_DISP_FLG_GA1REF |
						D_IM_DISP_FLG_VE |
						D_IM_DISP_FLG_VE2;
			break;
	}

	return disp_flg;
}

/**
Get call back function pointer array's index
@param[in]	interrupt_type	interrupt's type
@return call back function pointer array's index.
*/
INT32 im_disp_get_cb_index(ImDisp *self, ImDispEImDispInterruptionSelect interrupt_type)
{
	INT32 cb_index;
	switch(interrupt_type) {
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_VE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2:
			cb_index = ImDisp_E_IM_DISP_INT_CB_VE2;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GR0EE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GR1EE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GA0EE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GA1EE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_LEE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GR0REE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GR1REE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GA0REE;
			break;
		case ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE:
			cb_index = ImDisp_E_IM_DISP_INT_CB_GA1REE;
			break;
		default: // ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE,
			cb_index = ImDisp_E_IM_DISP_INT_CB_LREE;
			break;
	}
	return cb_index;
}

ImDisp *im_disp_new(void)
{
	ImDisp* self = k_object_new_with_private(IM_TYPE_DISP,sizeof(ImDispPrivate));
	return self;
}
