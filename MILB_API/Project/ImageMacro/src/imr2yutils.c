/*
 * imr2yutils.c
 *
 *  Created on: 2020年9月2日
*@author              :gonghaotian
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/

#include "imr2yutils.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImR2yUtils, im_r2y_utils);
#define IM_R2Y_UTILS_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImR2yUtilsPrivate, IM_TYPE_R2Y_UTILS))



struct _ImR2yUtilsPrivate
{
	int a;
};

/*
 * DECLS
 */


/*
 * IMPL
 */
static void im_r2y_utils_constructor(ImR2yUtils *self)
{
//	ImR2yUtilsPrivate *priv = IM_R2Y_UTILS_GET_PRIVATE(self);
}

static void im_r2y_utils_destructor(ImR2yUtils *self)
{
//	ImR2yUtilsPrivate *priv = IM_R2Y_UTILS_GET_PRIVATE(self);
}

static void ioR2yRegPtrInit(ImR2yUtils *self){
	self->gIM_Io_R2y_Reg_Ptr[0] = &IO_R2Y_P1;
	self->gIM_Io_R2y_Reg_Ptr[1] = &IO_R2Y_P2;
	self->gIM_Io_R2y_Reg_Ptr[2] = &IO_R2Y_P3;

}

static void ioR2yTblPtrInit(ImR2yUtils *self){
	self->gIM_Io_R2y_Tbl_Ptr[0] = &IO_R2Y_TBL_P1;
	self->gIM_Io_R2y_Tbl_Ptr[1] = &IO_R2Y_TBL_P2;
	self->gIM_Io_R2y_Tbl_Ptr[2] = &IO_R2Y_TBL_P3;

}
/*
 * PUBLIC
 */
volatile T_IM_R2Y_STATE_MNG* im_r2y_utils_get_state_mng(ImR2yUtils* self)
{
	return self->gIM_R2Y_State;
}

volatile struct io_r2y** im_r2y_utils_get_io_reg(ImR2yUtils* self)
{
	return self->gIM_Io_R2y_Reg_Ptr;
}

volatile T_IM_R2Y_YYRA_OFS_INFO* im_r2y_utils_get_yyra_ofs_info(ImR2yUtils* self)
{
	return &self->gIM_R2Y_yyra_ofs_info;
}

volatile struct io_r2y_sram** im_r2y_utils_get_io_tbl(ImR2yUtils* self)
{
	return self->gIM_Io_R2y_Tbl_Ptr;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
// Nothing Special
//---------------------- colabo  section -------------------------------
#ifdef CO_R2Y_RDMA_ON
//TODO 私转公
VOID im_r2y_utils_start_rdma(ImR2yUtils *self, T_IM_RDMA_CTRL* ctrl )
{
	INT32 ercd;

	ercd = Im_RDMA_Ctrl_Quick_Start_Sync( D_DDIM_USER_SEM_WAIT_FEVR, ctrl, E_IM_RDMA_INT_MODE_OR );

	if( ercd != D_IM_RDMA_OK ){
		Ddim_Print(( "im_r2y_utils_start_rdma error. %x\n", ercd ));
	}
}
#endif	// CO_R2Y_RDMA_ON
#endif	// CO_DDIM_UTILITY_USE

VOID im_r2y_utils_get_loop_val(ImR2yUtils *self, UCHAR pipe_no, UCHAR* loop_sta, UCHAR* loop_end )
{
	switch( pipe_no ){
		case D_IM_R2Y_PIPE1:
			*loop_sta = 0;
			*loop_end = 0;
			break;
		case D_IM_R2Y_PIPE2:
			*loop_sta = 1;
			*loop_end = 1;
			break;
//		case D_IM_R2Y_PIPE12:
		default:
			*loop_sta = 0;
			*loop_end = 1;
			break;
	}
}

ImR2yUtils *im_r2y_utils_get(void)
{
	static ImR2yUtils* self = NULL ;
	if(!self){
		self = 	k_object_new_with_private(IM_TYPE_R2Y_UTILS,sizeof(ImR2yUtilsPrivate));
		ioR2yRegPtrInit(self);
		ioR2yTblPtrInit(self);
	}
	return self;
}