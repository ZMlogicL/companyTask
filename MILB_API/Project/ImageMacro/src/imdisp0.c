/*
 * imdisp0.c
 *
 *  Created on: 2020年8月8日
 *      Author: sns
 */
#include "imdisp0.h"
#include "jdsdisp3a.h"

#include "dd_arm.h"
#include "ddim_user_custom.h"
#include <stddef.h>
#include <string.h>

K_TYPE_DEFINE_WITH_PRIVATE(ImDisp0, im_disp0)
#define IM_DISP0_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE ((o), ImDisp0Private,IM_TYPE_DISP0))

struct _ImDisp0Private{
	int a;
};

static void im_disp0_constructor(ImDisp0 *self){
//	ImDisp0Private *priv = IM_DISP0_GET_PRIVATE(self);
}

static void im_disp0_destructor(ImDisp0 *self){
}


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
//---------------------- driver  section -------------------------------
/**< Interrupt callback functions.	*/
static volatile VP_CALLBACK	S_GIM_DISP_INTERRUPT_CALLBACK[D_IM_DISP_BLOCK_NUM][ImDisp_E_IM_DISP_INT_CB_MAX] = {
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

void im_disp0_memcpy(ImDisp0 * self,ImDispEImDispSel block , T_IM_DISP_CTRL_OUTPUT const *const ctrl)
{
	memcpy((void*)S_GIM_DISP_INTERRUPT_CALLBACK[block], ctrl->int_callback, sizeof(ctrl->int_callback));

}

void im_disp0_memcpy1(ImDisp0 * self,ImDispEImDispSel block , T_IM_DISP_CTRL_OUTPUT *const ctrl)
{
	memcpy(ctrl->int_callback, (void*)S_GIM_DISP_INTERRUPT_CALLBACK[block], sizeof(ctrl->int_callback));

}

void im_disp0_gim_Disp_Interrupt_Callback1(ImDisp0 * self)
{
	INT32 loop;
		INT32 block_index;
		INT32 cbf_index;
		DDIM_USER_ER ercd;

		ImDispEImDispInterruptionSelect interrupt_bit_map[] ={
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2,		// Check 2nd field at first.
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE,

				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE,

				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE,
				ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE,
			};
			im_disp_pclk_on(im_disp_new());
		#ifdef CO_DEBUG_DISP
			Ddim_Print(("I:im_disp2_int_handler: start IO_DISP.MAIN[0].DCORE.INTF = %08X\n", (UINT32)IO_DISP.MAIN[0].DCORE.INTF.word));
			Ddim_Print(("I:im_disp2_int_handler: start IO_DISP.MAIN[1].DCORE.INTF = %08X\n", (UINT32)IO_DISP.MAIN[1].DCORE.INTF.word));
		#endif // CO_DEBUG_DISP

	for(block_index = D_IM_DISP_BLOCK_NUM - 1; block_index >= 0; block_index--) {

			for(loop = 0; loop < sizeof(interrupt_bit_map)/sizeof(interrupt_bit_map[0]); loop++) {
				if ((IO_DISP.MAIN[block_index].DCORE.INTF.word & interrupt_bit_map[loop]) != 0) {
	#ifdef CO_DEBUG_ON_PC
					UINT32 next_intf = IO_DISP.MAIN[block_index].DCORE.INTF.word & ~interrupt_bit_map[loop];
	#endif // CO_DEBUG_ON_PC
					//Vertical synchronization interrupt
					UINT32 disp_flg = im_disp_get_event_flag(im_disp_new(), interrupt_bit_map[loop]);
					// Set the flag for waiting vertical synchronization interrupt
					ercd = DDIM_User_Set_Flg(FID_IM_DISP, disp_flg);
	#ifdef CO_DEBUG_DISP
					Ddim_Print(("I:im_disp2_int_handler: DDIM_User_Set_Flg(%08X)\n", disp_flg));
	#endif // CO_DEBUG_DISP
					if (ercd != D_DDIM_USER_E_OK) {
						// DDIM_User_Set_Flg error
						Ddim_Print(("E:im_disp2_int_handler: DDIM_User_Set_Flg error. ercd = %d\n", ercd));
					}
	cbf_index = im_disp_get_cb_index(im_disp_new(), interrupt_bit_map[loop]);
	// check callback
					if (S_GIM_DISP_INTERRUPT_CALLBACK[block_index][cbf_index]!= NULL) {
						//Have call back function
						S_GIM_DISP_INTERRUPT_CALLBACK[block_index][cbf_index]();
					}
					IO_DISP.MAIN[block_index].DCORE.INTF.word = interrupt_bit_map[loop];
				#ifdef CO_DEBUG_ON_PC
								IO_DISP.MAIN[block_index].DCORE.INTF.word = next_intf;
				#endif // CO_DEBUG_ON_PC
							}
							if ((IO_DISP.MAIN[block_index].DCORE.INTF.word & ImDisp_E_IM_DISP_CORRECT_SELECT_ALL) == 0) {
								break;
							}
						}
					}
}


/* Set interruption's call-back function pointer.
*/
INT32 im_disp0_set_int_callback(ImDisp0 * self, ImDispEImDispSel block, UINT32 interruption_select, VP_CALLBACK vp_callback)
{
	INT32 index;
	INT32 cbf_index;
	INT32 array_num;
	INT32 ret = D_DDIM_OK;

	ImDispEImDispInterruptionSelect interrupt_index[] = {
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2,		/**< Vertical syschronization signal interruption for 2nd field permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE,		/**< Vertical syschronization signal interruption permission*/

		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE,	/**< GR1 A component AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE,	/**< GR0 A component AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE,	/**< GR1 AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE,	/**< GR0 AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE,		/**< Main AXI error interruption permission */

		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE,	/**< GR1 A component transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE,	/**< GR0 A component transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE,	/**< GR1 transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE,	/**< GR0 transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE,		/**< Main transmitte error interruption permission */
	};

#ifdef CO_PARAM_CHECK
	if ((interruption_select & ImDisp_E_IM_DISP_CORRECT_SELECT_ALL) == 0) {
		Ddim_Print(("E:im_disp0_set_int_callback: interruption_select parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Set Main
	array_num = sizeof(interrupt_index) / sizeof(interrupt_index[0]);
	for(index = array_num - 1; index >= 0; index--) {
		if((interruption_select & interrupt_index[index]) == interrupt_index[index]){
			// Set callback
			cbf_index = im_disp_get_cb_index(im_disp_new(), interrupt_index[index]);
			S_GIM_DISP_INTERRUPT_CALLBACK[block][cbf_index] = vp_callback;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

/* Get interruption's call-back function pointer.
*/
INT32 im_disp0_get_int_callback(ImDisp0 * self, ImDispEImDispSel block, ImDispEImDispInterruptionSelect interruption_select, VP_CALLBACK *vp_callback)
{
	INT32 index;
	INT32 cbf_index;
	INT32 ret = D_DDIM_OK;

	ImDispEImDispInterruptionSelect interrupt_select[] = {
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2,		/**< Vertical syschronization signal interruption for 2nd field permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE,		/**< Vertical syschronization signal interruption permission*/

		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE,	/**< GR1 A component AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE,	/**< GR0 A component AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE,	/**< GR1 AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE,	/**< GR0 AXI error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE,		/**< Main AXI error interruption permission */

		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE,	/**< GR1 A component transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE,	/**< GR0 A component transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE,	/**< GR1 transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE,	/**< GR0 transmitte error interruption permission */
		ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE,		/**< Main transmitte error interruption permission */
	};

#ifdef CO_PARAM_CHECK
	if (vp_callback == NULL) {
		Ddim_Print(("E:im_disp0_get_int_callback: NULL check error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
	if ((interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE2) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_VE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1REE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0REE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1REE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0REE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LREE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA1EE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GA0EE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR1EE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_GR0EE) &&
		(interruption_select != ImDisp_E_IM_DISP_INTERRUPTION_SELECT_LEE)) {
		Ddim_Print(("E:im_disp0_get_int_callback: interruption_select parameter error\n"));
		return D_IM_DISP_INPUT_PARAM_ERROR;
	}
#endif // CO_PARAM_CHECK

	im_disp_pclk_on(im_disp_new());
	// Get Main
	for(index = sizeof(interrupt_select)/sizeof(interrupt_select[0]) - 1;
		index >= 0;
		index--) {
		if(interruption_select == interrupt_select[index]) {
			cbf_index = im_disp_get_cb_index(im_disp_new(), interrupt_select[index]);
			*vp_callback = S_GIM_DISP_INTERRUPT_CALLBACK[block][cbf_index];
			break;
		}
	}
	im_disp_pclk_off(im_disp_new());

	return ret;
}

ImDisp0 *im_disp0_get()
{
	static ImDisp0 *imDisp0 = NULL;
	if(!imDisp0)
		imDisp0 = k_object_new_with_private(IM_TYPE_DISP0,sizeof(ImDisp0Private));
	return imDisp0;
}
