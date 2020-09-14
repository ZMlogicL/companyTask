/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r5类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include "ctimb2r.h"

// #include "im_b2r.h"
#include "../../ImageMacro/src/imb2r.h"
#include "im_pro.h"
// #include "im_pro_common.h"
#include "../../ImageMacro/src/improcommon.h"

#include "driver_common.h"
// #include "ddim_user_custom.h"
#include "../../../../milb_api_usercustom/src/ddimusercustom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
// #include "dd_top.h"
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#endif

#include "jdsb2r.h"

#include <stdlib.h>
#include <string.h>

#include "ctimb2r.h"

#include "ctimb2r5.h"
#include "ctimb2r1.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtImB2r5, ct_im_b2r5);
#define CT_IM_B2R5_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtImB2r5Private,CT_TYPE_IM_B2R5))


/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_b2r_check_target_pipe_no_1(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE1+1))
#define ct_im_b2r_check_target_pipe_no_2(a)		(((a)+1) & (ImB2r_D_IM_B2R_PIPE2+1))


struct _CtImB2r5Private
{

};

/*
DECLS
*/

static void ct_im_b2r5_constructor(CtImB2r5 *self) 
{
//	CtImB2r5Private *priv = CT_IM_B2R5_GET_PRIVATE(self);
}

static void ct_im_b2r5_destructor(CtImB2r5 *self) 
{
//	CtImB2r5Private *priv = CT_IM_B2R5_GET_PRIVATE(self);
	self = NULL;
}

/*
IMPL//todo
*/

/*
PUBLIC//todo
*/

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_46: "
kint32 ct_im_b2r5_1_46( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_Deknee_Table( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_DEKNEE_TBL_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_47: "
kint32 ct_im_b2r5_1_47( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_Knee_Table( self->pipeNo, E_B2R_RGBTBL_R, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "R address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}

	ercd = Im_B2R_Get_RdmaAddr_Knee_Table( self->pipeNo, E_B2R_RGBTBL_G, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "G address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}

	ercd = Im_B2R_Get_RdmaAddr_Knee_Table( self->pipeNo, E_B2R_RGBTBL_B, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_KNEE_TBL_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "B address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_48: "
kint32 ct_im_b2r5_1_48( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_OFST_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_Offset_Cntl( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_OFST_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_49: "
kint32 ct_im_b2r5_1_49( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_WB_SLOPE_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_WB_Slope_Cntl( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_WB_SLOPE_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_50: "
kint32 ct_im_b2r5_1_50( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_WB_CLIP_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_WB_Clip_Cntl( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_WB_CLIP_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_51: "
kint32 ct_im_b2r5_1_51( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_SENSITIVITY_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_Sensitivity_Cntl( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_SENSITIVITY_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_52: "
kint32 ct_im_b2r5_1_52( CtImB2r5 *self )
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const T_IM_B2R_CTRL_RDMA_HPF_ADDR* addr;
	ULONG* pt_addr;

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));

#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Get_RdmaAddr_HPF_Cntl( self->pipeNo, &addr );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
	pt_addr = (ULONG*)addr;
	for( loopcnt = 0; loopcnt < sizeof(T_IM_B2R_CTRL_RDMA_HPF_ADDR) / sizeof(ULONG); loopcnt++ ) {
		Ddim_Print(( "address[%d] = 0x%lx\n", loopcnt, *pt_addr ));
		pt_addr++;
	}
#endif

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_53: "
kint32 ct_im_b2r5_1_53( CtImB2r5 *self )
{
	UCHAR ext_out_en[] = {
		[0] = ImB2r_D_IM_B2R_ENABLE_ON,
		[1] = ImB2r_D_IM_B2R_ENABLE_OFF,
	};
	UCHAR ext_out_alarm[] = {
		[0] = D_IM_B2R_EXT_OUT_ALARM_VALID_DATA,
		[1] = ImB2r_D_IM_B2R_EXT_OUT_ALARM_1LINE,
	};
	kuint32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(ext_out_en) / sizeof(ext_out_en[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = Im_B2R_Set_ExternalIfOutput( self->pipeNo, ext_out_en[loopcnt], ext_out_alarm[loopcnt] );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));
		Im_B2R_On_Pclk( ImB2r_D_IM_B2R_PIPE12 );
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.B2R_CMN.DINSEL.bit.EXTOEN   = %u\n", IO_B2R_P1.B2R_CMN.DINSEL.bit.EXTOEN   ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.B2R_CMN.DINSEL.bit.EXTOEN   = %u\n", IO_B2R_P2.B2R_CMN.DINSEL.bit.EXTOEN   ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P1.B2R_CMN.EXALMSL.bit.EXALMSL = %u\n", IO_B2R_P1.B2R_CMN.EXALMSL.bit.EXALMSL ));
		Ddim_Print(( D_IM_B2R_FUNC_NAME "IO_B2R_P2.B2R_CMN.EXALMSL.bit.EXALMSL = %u\n", IO_B2R_P2.B2R_CMN.EXALMSL.bit.EXALMSL ));
		Im_B2R_Off_Pclk( ImB2r_D_IM_B2R_PIPE12 );
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_B2R_FUNC_NAME
#define D_IM_B2R_FUNC_NAME "ct_im_b2r5_1_54: "
kint32 ct_im_b2r5_1_54( CtImB2r5 *self )
{
	UCHAR ext_out_en;
	UCHAR ext_out_alarm;
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif

	if( self->pipeNo == ImB2r_D_IM_B2R_PIPE12 ){
		return D_DDIM_OK;
	}

	Ddim_Print(( "%s\n", D_IM_B2R_FUNC_NAME ));


#ifdef CO_MSG_PRINT_ON
	ercd = Im_B2R_Set_ExternalIfOutput( self->pipeNo, ImB2r_D_IM_B2R_ENABLE_ON, D_IM_B2R_EXT_OUT_ALARM_3LINE );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	ercd = Im_B2R_Get_ExternalIfOutput( self->pipeNo, &ext_out_en, &ext_out_alarm );
	Ddim_Print(( D_IM_B2R_FUNC_NAME "0x%x\n", ercd ));

	Ddim_Print(( D_IM_B2R_FUNC_NAME "ext_out_en    = %u\n", ext_out_en ));
	Ddim_Print(( D_IM_B2R_FUNC_NAME "ext_out_alarm = %u\n", ext_out_alarm ));
#endif

	return D_DDIM_OK;
}



CtImB2r5* ct_im_b2r5_new(void) 
{
    CtImB2r5 *self = k_object_new_with_private(CT_TYPE_IM_B2R5, sizeof(CtImB2r5Private));
    return self;
}
