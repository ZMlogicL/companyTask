/*
 * improb2b.c
 *
 *  Created on: 2020年9月4日
 *      Author: sns
 */

#include "impro.h"
#include "jdspro.h"
//#include "im_pro.h"
#include "im_pro_common.h"
#include "dd_top.h"

typedef struct _ImProPrivate ImProPrivate;
 struct _ImProPrivate
{
	int a;
};

K_TYPE_DEFINE_DERIVED(ImPro, im_pro, sizeof(ImProPrivate),K_TYPE_OBJECT)
#define IM_PRO_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImProPrivate, IM_TYPE_PRO))

static	volatile	ULONG	gIM_B2B_START_Status[1] = {0x00000000};
//static volatile T_IM_PRO_B2BTOP_INFO	gIM_PRO_B2BTOP_Reg_Ptr_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
// 	// E_IM_PRO_UNIT_NUM_1
// 	{
// 		&IO_PRO.IMG_PIPE[0].B2B.B2BTOP
// 	},
// 	// E_IM_PRO_UNIT_NUM_2
// 	{
// 		&IO_PRO.IMG_PIPE[1].B2B.B2BTOP
// 	},
// 	// E_IM_PRO_BOTH_UNIT
// 	{
// 		&IO_PRO.IMG_PIPE[2].B2B.B2BTOP
// 	},
// };

//static const UINT32	gIM_PRO_ELF_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
//	D_IM_B2B1_STATUS_ELF,	D_IM_B2B2_STATUS_ELF,	D_IM_B2B_STATUS_ELF_BOTH,
//};

static const UINT32	gIM_PRO_ELF_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
	D_IM_B2B1_STATUS_ELF,	D_IM_B2B2_STATUS_ELF,	D_IM_B2B_STATUS_ELF_BOTH,
};

static const UINT32	gIM_PRO_ELF_NSL_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
	D_IM_B2B1_STATUS_ELF_NSL,	D_IM_B2B2_STATUS_ELF_NSL,	D_IM_B2B_STATUS_ELF_NSL_BOTH,
};

static const T_IM_PRO_FSHD_INFO	gIM_PRO_FSHD_Status_Tbl[E_IM_PRO_UNIT_NUM_MAX] = {
	{	&IO_PRO_TBL.B2B1_TBL.FSHDCTBL[0],	D_IM_B2B1_STATUS_FSHD,		{	D_IM_PRO_COMMON_STATUS_B2B1_M2P2,	D_IM_PRO_COMMON_STATUS_B2B1_M2P3,	D_IM_PRO_COMMON_STATUS_B2B1_PRCH2,	D_IM_PRO_COMMON_STATUS_B2B1_PRCH3,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE			}	},
	{	&IO_PRO_TBL.B2B2_TBL.FSHDCTBL[0],	D_IM_B2B2_STATUS_FSHD,		{	D_IM_PRO_COMMON_STATUS_B2B2_M2P2,	D_IM_PRO_COMMON_STATUS_B2B2_M2P3,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH2,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH3,
																			D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE,		D_IM_PRO_COMMON_STATUS_NONE			}	},
	{	&IO_PRO_TBL.B2B3_TBL.FSHDCTBL[0],	D_IM_B2B_STATUS_FSHD_BOTH,	{	D_IM_PRO_COMMON_STATUS_B2B1_M2P2,	D_IM_PRO_COMMON_STATUS_B2B1_M2P3,	D_IM_PRO_COMMON_STATUS_B2B1_PRCH2,	D_IM_PRO_COMMON_STATUS_B2B1_PRCH3,
																			D_IM_PRO_COMMON_STATUS_B2B2_M2P2,	D_IM_PRO_COMMON_STATUS_B2B2_M2P3,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH2,	D_IM_PRO_COMMON_STATUS_B2B2_PRCH3	}	},
};

static const T_IM_PRO_RDMA_ELF_ADDR gIM_PRO_ELF_Addr[E_IM_PRO_UNIT_NUM_MAX] = {
	{
		0x28410420,0x28410424,0x28410428,0x2841042C,
		0x28410430,0x28410434,0x28410438,0x2841043C,
		0x28410440,0x28410444,0x28410448,0x2841044C,
		0x28410450,0x28410454,0x28410458,0x2841045C,
		0x28410460,0x28410464,0x28410468,0x2841046C,
		0x28410470,0x28410474,0x28410478,0x2841047C,
		0x28410480,0x28410484,0x28410488,0x2841048C,
		0x28410490,0x28410494,0x28410498,0x2841049C,
		0x284104A0,0x284104A4,0x284104A8,0x284104AC,
		0x284104B0,0x284104B8,0x284104BC,0x284104C0,
		0x284104C4,0x284104C8,0x284104CC,0x284104D0,
		0x284104D4,0x284104D8,0x284104DC,0x284104E0,
		0x284104E4,0x284104E8,0x284104F0,0x284104F4,
		0x284104F8,0x284104FC,0x28410500,0x28410504,
		0x28410508,0x2841050C,0x28410510,0x28410514,
		0x28410518,0x2841051C,0x28410520,0x28410528,
		0x2841052C,0x28410540,0x28410544,0x28410548,
		0x2841054C,0x28410550,0x28410560,0x28410564,
		0x28410568,0x2841056C,0x28410570,0x28410574,
		0x28410578,0x2841057C,0x28410580,0x28410584,
		0x28410588,0x2841058C,0x28410590,0x28410594,
		0x28410598,0x2841059C,0x284105A0,0x284105A4,
		0x284105A8,0x284105AC,0x284105B0,0x284105B4,
		0x284105B8,0x284105BC,0x284105C0,0x284105C8,
		0x284105CC,0x284105D0,0x284105D4,0x284105D8,
		0x284105DC,0x284105E0,0x284105E4,0x284105E8,
		0x284105EC,0x284105F0,0x284105F4,0x284105F8,
		0x284105FC,0x28410600,0x28410604,0x28410608,
		0x2841060C,0x28410610,0x28410614,0x28410618,
		0x2841061C,0x28410620,0x28410624,0x28410628,
		0x2841062C,0x28410630,0x28410634,0x28410640,
		0x28410644,0x28410648,0x2841064C,0x28410650,
		0x28410654,0x28410660,0x28410664,0x28410668,
		0x2841066C,0x28410684,
	},
	{
		0x28510420,0x28510424,0x28510428,0x2851042C,
		0x28510430,0x28510434,0x28510438,0x2851043C,
		0x28510440,0x28510444,0x28510448,0x2851044C,
		0x28510450,0x28510454,0x28510458,0x2851045C,
		0x28510460,0x28510464,0x28510468,0x2851046C,
		0x28510470,0x28510474,0x28510478,0x2851047C,
		0x28510480,0x28510484,0x28510488,0x2851048C,
		0x28510490,0x28510494,0x28510498,0x2851049C,
		0x285104A0,0x285104A4,0x285104A8,0x285104AC,
		0x285104B0,0x285104B8,0x285104BC,0x285104C0,
		0x285104C4,0x285104C8,0x285104CC,0x285104D0,
		0x285104D4,0x285104D8,0x285104DC,0x285104E0,
		0x285104E4,0x285104E8,0x285104F0,0x285104F4,
		0x285104F8,0x285104FC,0x28510500,0x28510504,
		0x28510508,0x2851050C,0x28510510,0x28510514,
		0x28510518,0x2851051C,0x28510520,0x28510528,
		0x2851052C,0x28510540,0x28510544,0x28510548,
		0x2851054C,0x28510550,0x28510560,0x28510564,
		0x28510568,0x2851056C,0x28510570,0x28510574,
		0x28510578,0x2851057C,0x28510580,0x28510584,
		0x28510588,0x2851058C,0x28510590,0x28510594,
		0x28510598,0x2851059C,0x285105A0,0x285105A4,
		0x285105A8,0x285105AC,0x285105B0,0x285105B4,
		0x285105B8,0x285105BC,0x285105C0,0x285105C8,
		0x285105CC,0x285105D0,0x285105D4,0x285105D8,
		0x285105DC,0x285105E0,0x285105E4,0x285105E8,
		0x285105EC,0x285105F0,0x285105F4,0x285105F8,
		0x285105FC,0x28510600,0x28510604,0x28510608,
		0x2851060C,0x28510610,0x28510614,0x28510618,
		0x2851061C,0x28510620,0x28510624,0x28510628,
		0x2851062C,0x28510630,0x28510634,0x28510640,
		0x28510644,0x28510648,0x2851064C,0x28510650,
		0x28510654,0x28510660,0x28510664,0x28510668,
		0x2851066C,0x28510684,
	},
	{
		0x28610420,0x28610424,0x28610428,0x2861042C,
		0x28610430,0x28610434,0x28610438,0x2861043C,
		0x28610440,0x28610444,0x28610448,0x2861044C,
		0x28610450,0x28610454,0x28610458,0x2861045C,
		0x28610460,0x28610464,0x28610468,0x2861046C,
		0x28610470,0x28610474,0x28610478,0x2861047C,
		0x28610480,0x28610484,0x28610488,0x2861048C,
		0x28610490,0x28610494,0x28610498,0x2861049C,
		0x286104A0,0x286104A4,0x286104A8,0x286104AC,
		0x286104B0,0x286104B8,0x286104BC,0x286104C0,
		0x286104C4,0x286104C8,0x286104CC,0x286104D0,
		0x286104D4,0x286104D8,0x286104DC,0x286104E0,
		0x286104E4,0x286104E8,0x286104F0,0x286104F4,
		0x286104F8,0x286104FC,0x28610500,0x28610504,
		0x28610508,0x2861050C,0x28610510,0x28610514,
		0x28610518,0x2861051C,0x28610520,0x28610528,
		0x2861052C,0x28610540,0x28610544,0x28610548,
		0x2861054C,0x28610550,0x28610560,0x28610564,
		0x28610568,0x2861056C,0x28610570,0x28610574,
		0x28610578,0x2861057C,0x28610580,0x28610584,
		0x28610588,0x2861058C,0x28610590,0x28610594,
		0x28610598,0x2861059C,0x286105A0,0x286105A4,
		0x286105A8,0x286105AC,0x286105B0,0x286105B4,
		0x286105B8,0x286105BC,0x286105C0,0x286105C8,
		0x286105CC,0x286105D0,0x286105D4,0x286105D8,
		0x286105DC,0x286105E0,0x286105E4,0x286105E8,
		0x286105EC,0x286105F0,0x286105F4,0x286105F8,
		0x286105FC,0x28610600,0x28610604,0x28610608,
		0x2861060C,0x28610610,0x28610614,0x28610618,
		0x2861061C,0x28610620,0x28610624,0x28610628,
		0x2861062C,0x28610630,0x28610634,0x28610640,
		0x28610644,0x28610648,0x2861064C,0x28610650,
		0x28610654,0x28610660,0x28610664,0x28610668,
		0x2861066C,0x28610684,
	},
};

static const T_IM_PRO_RDMA_FSHD_ADDR gIM_PRO_FSHD_Addr[E_IM_PRO_UNIT_NUM_MAX] = {
	{
		0x28410A08,0x28410A1C,0x28410A20,0x28410A24,
		0x28410A28,0x28410A30,0x28410A34,0x28410A38,
		0x28410A3C,0x28410A40,0x28410A44,0x28410A48,
		0x28410A50,0x28410A54,0x28410A58,0x28410A5C,
		0x28410A60,0x28410A64,0x28410A68,0x28410A6C,
		0x28410A70,0x28410A80,0x28410A84,0x28410A88,
	},
	{
		0x28510A08,0x28510A1C,0x28510A20,0x28510A24,
		0x28510A28,0x28510A30,0x28510A34,0x28510A38,
		0x28510A3C,0x28510A40,0x28510A44,0x28510A48,
		0x28510A50,0x28510A54,0x28510A58,0x28510A5C,
		0x28510A60,0x28510A64,0x28510A68,0x28510A6C,
		0x28510A70,0x28510A80,0x28510A84,0x28510A88,
	},
	{
		0x28610A08,0x28610A1C,0x28610A20,0x28610A24,
		0x28610A28,0x28610A30,0x28610A34,0x28610A38,
		0x28610A3C,0x28610A40,0x28610A44,0x28610A48,
		0x28610A50,0x28610A54,0x28610A58,0x28610A5C,
		0x28610A60,0x28610A64,0x28610A68,0x28610A6C,
		0x28610A70,0x28610A80,0x28610A84,0x28610A88,
	},
};

static const T_IM_PRO_RDMA_FSHD_CTBL_ADDR gIM_PRO_FSHD_Ctbl_Addr[E_IM_PRO_UNIT_NUM_MAX][D_IM_PRO_B2B_FSHD_CTBL_CNT] = {
	{
		{ 0x29480000 },
		{ 0x29480800 },
	},
	{
		{ 0x29580000 },
		{ 0x29580800 },
	},
	{
		{ 0x29680000 },
		{ 0x29680800 },
	},
};

static void im_pro_constructor(ImPro *self)
{
	//ImProPrivate *priv = IM_PRO_GET_PRIVATE(self);
}

static void im_pro_destructor(ImPro *self)
{
	//ImProPrivate *priv = IM_PRO_GET_PRIVATE(self);
}

VOID im_pro_comm_get_fshd_reg_info( E_IM_PRO_UNIT_NUM unit_no, const T_IM_PRO_FSHD_INFO** fshdl_info )
{
	*fshdl_info = &gIM_PRO_FSHD_Status_Tbl[unit_no];
}

INT32 im_pro_elf_ctrl_nsl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_NSL_CTRL* nsl_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (nsl_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_elf_ctrl_nsl error. nsl_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if (( nsl_ctrl->long_noise_comp == E_IM_PRO_ELF_NSLKEN_EN ) && ( nsl_ctrl->l_noise_precision > E_IM_PRO_ELF_NSLRES_1 )){
		Ddim_Assertion(("I:im_pro_elf_ctrl_nsl parameter combination error.  When NSLKNE=1, setting NSLRES to 2 or 3 is prohibited. NSLKNE(%u) NSLRES(%u)\n", nsl_ctrl->long_noise_comp, nsl_ctrl->l_noise_precision));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.NSLMD				= nsl_ctrl->l_noise_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.NSLRES				= nsl_ctrl->l_noise_precision;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFCTL.bit.NSLKNE				= nsl_ctrl->long_noise_comp;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_a0_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen_trg == 0 ) && ( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_elf_set_a0_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFPAEN.bit.EPAENA0 = paen_trg;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_nsl_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen_trg == 0 ) && ( IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_elf_set_nsl_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFPAEN.bit.EPAENNSL = paen_trg;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_get_rdmaaddr_elf_cntl( E_IM_PRO_UNIT_NUM unit_no, const T_IM_PRO_RDMA_ELF_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:im_pro_get_rdmaaddr_elf_cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &(gIM_PRO_ELF_Addr[unit_no]);

	return D_DDIM_OK;
}

INT32 im_pro_elf_set_edge_adj( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_HIGH_FREQ_AREA_EDGE_ADJ* edge_adj )
{
#ifdef CO_PARAM_CHECK
	if( edge_adj == NULL ) {
		Ddim_Assertion(("I:im_pro_elf_set_edge_adj. error. edge_adj=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGCATH.bit.EDGCATHA	= edge_adj->high_freq_area_adj_coeff;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGCATH.bit.ELFTEST1	= edge_adj->test_para_1;
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.EDGCATH.bit.ELFTEST2	= edge_adj->test_para_2;

	return D_DDIM_OK;
}

INT32 im_pro_fshd_start( E_IM_PRO_UNIT_NUM unit_no )
{
	for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_FSHD_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
		if(gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
			if (im_pro_comm_get_start_status(gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt], 0) == FALSE){
				Ddim_Print(("I:im_pro_fshd_start. macro not running error. Pre-Started Macro status:(%u) \n", gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt]));
				return D_IM_PRO_MACRO_BUSY_NG;
			}
		}
	}

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDTRG.bit.FSHDTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_start_status(gIM_PRO_FSHD_Status_Tbl[unit_no].status, 0);

	return D_DDIM_OK;
}

INT32 im_pro_fshd_stop( E_IM_PRO_UNIT_NUM unit_no, UCHAR force )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDTRG.bit.FSHDTRG = D_IM_PRO_TRG_FRAME_STOP;		// stop
	}
	else {
		for( UCHAR loopcnt = 0; loopcnt < D_IM_PRO_FSHD_PRE_STARTED_STATUS_MAX; loopcnt++ ) {
			if(gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt] != D_IM_PRO_COMMON_STATUS_NONE) {
				if (im_pro_comm_get_start_status(gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt], 0) == TRUE){
					Ddim_Print(("I:im_pro_fshd_stop. macro not stop error. Pre-Stopped Macro status:(%u) \n", gIM_PRO_FSHD_Status_Tbl[unit_no].pre_started_status[loopcnt]));
					return D_IM_PRO_MACRO_BUSY_NG;
				}
			}
		}
		IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDTRG.bit.FSHDTRG = D_IM_PRO_TRG_FORCE_STOP;		// force stop
	}
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_stop_status(gIM_PRO_FSHD_Status_Tbl[unit_no].status, 0);

	return D_DDIM_OK;
}

INT32 im_pro_fshd_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_COMMON_CTRL* fshd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (fshd_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_fshd_ctrl error. fshd_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSULRR_MIN, D_IM_PRO_FSHD_FSULRR_MAX, fshd_ctrl->clip_r, "im_pro_fshd_ctrl : clip_r" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSULGR_MIN, D_IM_PRO_FSHD_FSULGR_MAX, fshd_ctrl->clip_gr, "im_pro_fshd_ctrl : clip_gr" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSULGB_MIN, D_IM_PRO_FSHD_FSULGB_MAX, fshd_ctrl->clip_gb, "im_pro_fshd_ctrl : clip_gb" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSULBB_MIN, D_IM_PRO_FSHD_FSULBB_MAX, fshd_ctrl->clip_b, "im_pro_fshd_ctrl : clip_b" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDCTL.bit.FSMODE		= fshd_ctrl->correction_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDCTL.bit.FWMODE		= fshd_ctrl->correction_mode_awb;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDCTL.bit.FSHDPTMD		= fshd_ctrl->montage_mode;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSUL1.bit.FSULRR			= fshd_ctrl->clip_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSUL1.bit.FSULGR			= fshd_ctrl->clip_gr;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSUL2.bit.FSULGB			= fshd_ctrl->clip_gb;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSUL2.bit.FSULBB			= fshd_ctrl->clip_b;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg )
{
#ifdef CO_PARAM_CHECK
	if( ( paen_trg == 0 ) && ( IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDTRG.bit.FSHDTRG != D_IM_PRO_TRG_STATUS_STOPPED ) ) {
		Ddim_Assertion(("I:im_pro_fshd_set_paen. macro has not stopped error.\n"));
		return D_IM_PRO_MACRO_BUSY_NG;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDPAEN.bit.FSPAEN = paen_trg;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_area( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_AREA_INFO* fshd_area )
{
#ifdef CO_PARAM_CHECK
	if (fshd_area == NULL){
		Ddim_Assertion(("I:im_pro_fshd_set_area error. fshd_area=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSHDH_MIN, D_IM_PRO_FSHD_FSHDH_MAX, fshd_area->pos_x, "im_pro_fshd_set_area : pos_x" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSHDV_MIN, D_IM_PRO_FSHD_FSHDV_MAX, fshd_area->pos_y, "im_pro_fshd_set_area : pos_y" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSHDHW_MIN, D_IM_PRO_FSHD_FSHDHW_MAX, fshd_area->width, "im_pro_fshd_set_area : width" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSHDVW_MIN, D_IM_PRO_FSHD_FSHDVW_MAX, fshd_area->lines, "im_pro_fshd_set_area : lines" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDH.bit.FSHDH	= fshd_area->pos_x;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDV.bit.FSHDV	= fshd_area->pos_y;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDHW.bit.FSHDHW	= fshd_area->width;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDVW.bit.FSHDVW	= fshd_area->lines;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_blend( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_BLEND_CTRL* blend_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (blend_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_fshd_set_blend error. blend_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDBC, union io_fshdbc, FSHDBC0, blend_ctrl->shading_blend_0 );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDBC, union io_fshdbc, FSHDBC1, blend_ctrl->shading_blend_1 );
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_frame( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_FRAME_CTRL* fshd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (fshd_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_fshd_set_frame error. fshd_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( im_pro_check_val_range( D_IM_PRO_FSHD_FSHDHWPH_MIN, D_IM_PRO_FSHD_FSHDHWPH_MAX, fshd_ctrl->montage_pos_h, "im_pro_fshd_set_frame : montage_pos_h" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( (IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDCTL.bit.FSHDPTMD == 1) && (( fshd_ctrl->start_pos_h + fshd_ctrl->montage_pos_h - 2 ) % fshd_ctrl->horizontal_pixel != 0) ) {
		Ddim_Assertion(("I:im_pro_fshd_set_frame parameter error. Please satisfy following relationship. start_pos_h + montage_pos_h == n * horizontal_pixel + 2\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBPRH_MIN, D_IM_PRO_FSHD_FSSUBPRH_MAX, fshd_ctrl->frame_horizontal_size, "im_pro_fshd_set_frame : frame_horizontal_size" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBPRV_MIN, D_IM_PRO_FSHD_FSSUBPRV_MAX, fshd_ctrl->frame_vertical_size, "im_pro_fshd_set_frame : frame_vertical_size" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBSPH_MIN, D_IM_PRO_FSHD_FSSUBSPH_MAX, fshd_ctrl->horizontal_pixel, "im_pro_fshd_set_frame : horizontal_pixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBSPV_MIN, D_IM_PRO_FSHD_FSSUBSPV_MAX, fshd_ctrl->vertical_pixel, "im_pro_fshd_set_frame : vertical_pixel" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBSTH_MIN, D_IM_PRO_FSHD_FSSUBSTH_MAX, fshd_ctrl->start_pos_h, "im_pro_fshd_set_frame : start_pos_h" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSSUBSTV_MIN, D_IM_PRO_FSHD_FSSUBSTV_MAX, fshd_ctrl->start_pos_v, "im_pro_fshd_set_frame : start_pos_v" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSARR_MIN, D_IM_PRO_FSHD_FSARR_MAX, fshd_ctrl->magnification_r, "im_pro_fshd_set_frame : magnification_r" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSAGR_MIN, D_IM_PRO_FSHD_FSAGR_MAX, fshd_ctrl->magnification_gr, "im_pro_fshd_set_frame : magnification_gr" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSAGB_MIN, D_IM_PRO_FSHD_FSAGB_MAX, fshd_ctrl->magnification_gb, "im_pro_fshd_set_frame : magnification_gb" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_FSABB_MIN, D_IM_PRO_FSHD_FSABB_MAX, fshd_ctrl->magnification_b, "im_pro_fshd_set_frame : magnification_b" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSCTL.bit.FSFMT		= fshd_ctrl->fsctl;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBPR.bit.FSSUBPRH	= fshd_ctrl->frame_horizontal_size;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBPR.bit.FSSUBPRV	= fshd_ctrl->frame_vertical_size;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBSP.bit.FSSUBSPH	= fshd_ctrl->horizontal_pixel;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBSP.bit.FSSUBSPV	= fshd_ctrl->vertical_pixel;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBDR.bit.FSSUBDRM	= fshd_ctrl->Inverse_base;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBDR.bit.FSSUBDRE	= fshd_ctrl->Inverse_exponent;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDHWPH.bit.FSHDHWPH	= fshd_ctrl->montage_pos_h;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBST.bit.FSSUBSTH	= fshd_ctrl->start_pos_h;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBST.bit.FSSUBSTV	= fshd_ctrl->start_pos_v;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSA1.bit.FSARR		= fshd_ctrl->magnification_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSA1.bit.FSAGR		= fshd_ctrl->magnification_gr;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSA2.bit.FSAGB		= fshd_ctrl->magnification_gb;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSA2.bit.FSABB		= fshd_ctrl->magnification_b;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDHCCTL.bit.FSHCEN	= fshd_ctrl->sat_correction_enabled;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSLP1.bit.FSSLPRR	= fshd_ctrl->sat_slope_gain[0];
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSLP1.bit.FSSLPGR	= fshd_ctrl->sat_slope_gain[1];
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSLP2.bit.FSSLPGB	= fshd_ctrl->sat_slope_gain[2];
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSLP2.bit.FSSLPBB	= fshd_ctrl->sat_slope_gain[3];
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_concentric( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_FSHD_CONCENTRIC_CTRL* fshd_ctrl )
{
#ifdef CO_PARAM_CHECK
	if (fshd_ctrl == NULL){
		Ddim_Assertion(("I:im_pro_fshd_set_concentric error. fshd_ctrl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSHDPARV_MIN, D_IM_PRO_FSHD_CSHDPARV_MAX, fshd_ctrl->interval_v, "im_pro_fshd_set_concentric : interval_v" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSHDPARV_MIN, D_IM_PRO_FSHD_CSHDPARV_MAX, fshd_ctrl->interval_v, "im_pro_fshd_set_concentric : interval_v" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSARR_MIN, D_IM_PRO_FSHD_CSARR_MAX, fshd_ctrl->magnification_r, "im_pro_fshd_set_frame : magnification_r" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSAGR_MIN, D_IM_PRO_FSHD_CSAGR_MAX, fshd_ctrl->magnification_gr, "im_pro_fshd_set_frame : magnification_gr" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSAGB_MIN, D_IM_PRO_FSHD_CSAGB_MAX, fshd_ctrl->magnification_gb, "im_pro_fshd_set_frame : magnification_gb" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( im_pro_check_val_range( D_IM_PRO_FSHD_CSABB_MIN, D_IM_PRO_FSHD_CSABB_MAX, fshd_ctrl->magnification_b, "im_pro_fshd_set_frame : magnification_b" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSCTL1.bit.CSSTBL			= fshd_ctrl->select_ram;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSCTL2.bit.CSFMT			= fshd_ctrl->select_format;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSCTL2.bit.CSHDLIR		= fshd_ctrl->interpolated_val;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSCTL2.bit.CSHDPARH		= fshd_ctrl->interval_h;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSCTL2.bit.CSHDPARV		= fshd_ctrl->interval_v;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSTBLS1.bit.CSTBLSRR		= fshd_ctrl->start_address_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSTBLS1.bit.CSTBLSGR		= fshd_ctrl->start_address_gr;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSTBLS2.bit.CSTBLSGB		= fshd_ctrl->start_address_gb;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSTBLS2.bit.CSTBLSBB		= fshd_ctrl->start_address_b;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSHDD.bit.CSHDDO			= fshd_ctrl->offset;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSHDD.bit.CSHDDM			= fshd_ctrl->clip_value;
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSHDOA, union io_cshdoa, CSHDOAH, fshd_ctrl->pos_h );
	im_pro_set_reg_signed( IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSHDOA, union io_cshdoa, CSHDOAV, fshd_ctrl->pos_v );
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSA1.bit.CSARR			= fshd_ctrl->magnification_r;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSA1.bit.CSAGR			= fshd_ctrl->magnification_gr;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSA2.bit.CSAGB			= fshd_ctrl->magnification_gb;
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSA2.bit.CSABB			= fshd_ctrl->magnification_b;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

E_IM_PRO_FSHD_LUT_SEL im_pro_fshd_get_ctbl_number( E_IM_PRO_UNIT_NUM unit_no )
{
	E_IM_PRO_FSHD_LUT_SEL ctbl_num;

	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	ctbl_num = IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.CSTBLST.bit.CSTBST;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return ctbl_num;
}

INT32 im_pro_fshd_set_table( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_FSHD_LUT_SEL tbl_sel, T_IM_PRO_FSHD_TABLE* shd_tbl )
{
#ifdef CO_PARAM_CHECK
	if (shd_tbl == NULL){
		Ddim_Assertion(("I:im_pro_fshd_set_table error. shd_tbl=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	if( ( shd_tbl->pshd_tbl == NULL ) || ( shd_tbl->size == 0 ) ) {
		Ddim_Assertion(("I:im_pro_fshd_set_table error. shd_tbl->pshd_tbl=%lx shd_tbl->size=%u\n", (ULONG)shd_tbl->pshd_tbl, shd_tbl->size));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	im_pro_on_hclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	im_pro_memcpy( (VOID*)&gIM_PRO_FSHD_Status_Tbl[unit_no].tbl_reg_ptr[tbl_sel].hword[0], shd_tbl->pshd_tbl, shd_tbl->size );
	im_pro_off_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_fshd_set_coeff_read_line_wait( E_IM_PRO_UNIT_NUM unit_no, USHORT req_interval_clk )
{
#ifdef CO_PARAM_CHECK
	if( im_pro_check_val_range( D_IM_PRO_FSHD_FSWRIC_MIN, D_IM_PRO_FSHD_FSWRIC_MAX, req_interval_clk, "im_pro_fshd_set_coeff_read_line_wait : req_interval_clk" ) == FALSE ) {
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
	else if( req_interval_clk >= ((IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSHDHW.bit.FSHDHW - (4*IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSSUBPR.bit.FSSUBPRH))-10)/3 ) {
		Ddim_Assertion(("I:Im_PRO_FSHDL_Set_Coeff_Read_Line_Wait. parameter error. Please satisfy following relationship. (req_interval_clk  < ((FSHDHW-(4*FSSUBPRH)) -10)/3) (%u)\n", req_interval_clk));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.FSHD.FSWRIC.bit.FSWRIC			= req_interval_clk;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	return D_DDIM_OK;
}

INT32 im_pro_get_rdmaaddr_fshd_cntl( E_IM_PRO_UNIT_NUM unit_no, const T_IM_PRO_RDMA_FSHD_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:im_pro_get_rdmaaddr_fshd_cntl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &gIM_PRO_FSHD_Addr[unit_no];

	return D_DDIM_OK;
}

INT32 im_pro_get_rdmaaddr_fshd_ctbl( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_FSHD_LUT_SEL tbl_sel, const T_IM_PRO_RDMA_FSHD_CTBL_ADDR** addr )
{
#ifdef CO_PARAM_CHECK
	if( addr == NULL ) {
		Ddim_Assertion(("I:im_pro_get_rdmaaddr_fshd_ctbl. error. addr=NULL\n"));
		return D_IM_PRO_INPUT_PARAM_ERROR;
	}
#endif

	*addr = &gIM_PRO_FSHD_Ctbl_Addr[unit_no][tbl_sel];

	return D_DDIM_OK;
}

VOID im_pro_elf_stop_nsl( E_IM_PRO_UNIT_NUM unit_no, UCHAR force )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NSLTRG.bit.NSLTRG = D_IM_PRO_TRG_FRAME_STOP;		// stop
	}
	else {
		IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NSLTRG.bit.NSLTRG = D_IM_PRO_TRG_FORCE_STOP;		// force stop
	}
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_stop_status(gIM_PRO_ELF_NSL_Status_Tbl[unit_no], 0);
}

INT32 im_pro_elf_start_nsl( E_IM_PRO_UNIT_NUM unit_no )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.NSLTRG.bit.NSLTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_start_status(gIM_PRO_ELF_NSL_Status_Tbl[unit_no], 0);

	return D_DDIM_OK;
}

VOID im_pro_elf_stop( E_IM_PRO_UNIT_NUM unit_no, UCHAR force )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	if(force == 0) {
		IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG = D_IM_PRO_TRG_FRAME_STOP;		// stop
	}
	else {
		IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG = D_IM_PRO_TRG_FORCE_STOP;		// force stop
	}
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_stop_status(gIM_PRO_ELF_Status_Tbl[unit_no], 0);
}

INT32 im_pro_elf_start( E_IM_PRO_UNIT_NUM unit_no )
{
	im_pro_on_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Start_Clock
	IO_PRO.IMG_PIPE[unit_no].B2B.ELF.ELFTRG.bit.ELFTRG = D_IM_PRO_TRG_START;
	im_pro_off_pclk( unit_no, E_IM_PRO_CLK_BLOCK_TYPE_B2B );	// Dd_Top_Stop_Clock

	im_pro_b2b_set_start_status(gIM_PRO_ELF_Status_Tbl[unit_no], 0);

	return D_DDIM_OK;
}

ImPro *im_pro_new(void)
{
	ImPro* self = k_object_new(IM_TYPE_PRO);
	return self;
}
