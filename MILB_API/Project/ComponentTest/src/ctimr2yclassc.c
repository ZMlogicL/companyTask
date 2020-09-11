/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-02
*@author : THH
*@brief : CtImR2yClassc
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2yclassc.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2yClassc, ct_im_r2y_classc)
#define CT_IM_R2Y_CLASSC_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), CtImR2yClasscPrivate, CT_TYPE_IM_R2Y_CLASSC))


struct _CtImR2yClasscPrivate
{

};


static void ct_im_r2y_classc_constructor(CtImR2yClassc *self)
{
	CtImR2yClasscPrivate *priv = CT_IM_R2Y_CLASSC_GET_PRIVATE(self);

	self->ctImR2yClassa=ct_im_r2y_classa_new();
	self->ctImR2y=ct_im_r2y_new();
	self->imR2y3=ct_im_r2y3_new();
	self->imR2y2=ct_im_r2y2_new();
	self->imR2yProc=ct_im_r2y_proc_new();
	self->imR2yClk=im_r2y_clk_new();
	self->imR2y=im_r2y_new();
}

static void ct_im_r2y_classc_destructor(CtImR2yClassc *self)
{
	CtImR2yClasscPrivate *priv = CT_IM_R2Y_CLASSC_GET_PRIVATE(self);
	if(self->ctImR2yClassa){
					k_object_unref(self->ctImR2yClassa);
					self->ctImR2yClassa=NULL;
				}
	if(self->ctImR2y){
						k_object_unref(self->ctImR2y);
						self->ctImR2y=NULL;
					}
	if(self->imR2y3){
						k_object_unref(self->imR2y3);
						self->imR2y3=NULL;
					}
	if(self->imR2y2){
						k_object_unref(self->imR2y2);
						self->imR2y2=NULL;
					}
	if(self->imR2yProc){
						k_object_unref(self->imR2yProc);
						self->imR2yProc=NULL;
					}
	if(self->imR2yClk){
						k_object_unref(self->imR2yClk);
						self->imR2yClk=NULL;
					}
	if(self->imR2y){
						k_object_unref(self->imR2y);
						self->imR2y=NULL;
					}
}





#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_16: "
INT32 ct_im_r2y_classc_1_16( CtImR2yClassc *self,UCHAR pipeNo )
{
	TImR2yAxiYywStat r2yAxiWriteStat;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){//11111111111111111111111111111111111111111111111111111111111
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp0 = 3;
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp1 = 3;
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp2 = 3;

		ioR2yP1.yych.yywaaxsts.bit.yyabresp0 = 3;
		ioR2yP1.yych.yywaaxsts.bit.yyabresp1 = 3;

		ioR2yP1.yych.yyw1axsts.bit.yy1bresp0 = 3;
		ioR2yP1.yych.yyw1axsts.bit.yy1bresp1 = 3;
		ioR2yP1.yych.yyw1axsts.bit.yy1bresp2 = 3;

		ioR2yP1.yych.yyw2axsts.bit.yy2bresp = 3;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp0 = 3;
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp1 = 3;
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp2 = 3;

		ioR2yP2.yych.yywaaxsts.bit.yyabresp0 = 3;
		ioR2yP2.yych.yywaaxsts.bit.yyabresp1 = 3;

		ioR2yP2.yych.yyw1axsts.bit.yy1bresp0 = 3;
		ioR2yP2.yych.yyw1axsts.bit.yy1bresp1 = 3;
		ioR2yP2.yych.yyw1axsts.bit.yy1bresp2 = 3;

		ioR2yP2.yych.yyw2axsts.bit.yy2bresp = 3;
	}
#endif //CO_DEBUG_ON_PC

	memset( &r2yAxiWriteStat, '\0', sizeof(r2yAxiWriteStat) );
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_get_axi_write_stat(self->imR2y, pipeNo, &r2yAxiWriteStat );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
	im_r2y_get_axi_write_stat(self->imR2y, pipeNo, &r2yAxiWriteStat );
#endif

	Ddim_Print(( "yw0_axi_stat[0]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw0_axi_stat[1]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw0_axi_stat[2]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_2] ));
	Ddim_Print(( "yw0a_axi_stat[0] = %u\n", r2yAxiWriteStat.yyw0aAxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw0a_axi_stat[1] = %u\n", r2yAxiWriteStat.yyw0aAxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw1_axi_stat[0]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw1_axi_stat[1]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw1_axi_stat[2]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_2] ));
	Ddim_Print(( "yw2_axi_stat     = %u\n", r2yAxiWriteStat.yyw2AxiStat ));

#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp0 = 0;
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp1 = 0;
		ioR2yP1.yych.yyw0axsts.bit.yy0bresp2 = 0;

		ioR2yP1.yych.yywaaxsts.bit.yyabresp0 = 0;
		ioR2yP1.yych.yywaaxsts.bit.yyabresp1 = 0;

		ioR2yP1.yych.yyw1axsts.bit.yy1bresp0 = 0;
		ioR2yP1.yych.yyw1axsts.bit.yy1bresp1 = 0;
		ioR2yP1.yych.yyw1axsts.bit.yy1bresp2 = 0;

		ioR2yP1.yych.yyw2axsts.bit.yy2bresp = 0;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp0 = 0;
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp1 = 0;
		ioR2yP2.yych.yyw0axsts.bit.yy0bresp2 = 0;

		ioR2yP2.yych.yywaaxsts.bit.yyabresp0 = 0;
		ioR2yP2.yych.yywaaxsts.bit.yyabresp1 = 0;

		ioR2yP2.yych.yyw1axsts.bit.yy1bresp0 = 0;
		ioR2yP2.yych.yyw1axsts.bit.yy1bresp1 = 0;
		ioR2yP2.yych.yyw1axsts.bit.yy1bresp2 = 0;

		ioR2yP2.yych.yyw2axsts.bit.yy2bresp = 0;
	}
#endif //CO_DEBUG_ON_PC

	memset( &r2yAxiWriteStat, '\0', sizeof(r2yAxiWriteStat) );
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_get_axi_write_stat(self->imR2y, pipeNo, &r2yAxiWriteStat );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
	im_r2y_get_axi_write_stat(self->imR2y, pipeNo, &r2yAxiWriteStat );
#endif

	Ddim_Print(( "yw0_axi_stat[0]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw0_axi_stat[1]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw0_axi_stat[2]  = %u\n", r2yAxiWriteStat.yyw0AxiStat[D_IM_R2Y_PORT_2] ));
	Ddim_Print(( "yw0a_axi_stat[0] = %u\n", r2yAxiWriteStat.yyw0aAxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw0a_axi_stat[1] = %u\n", r2yAxiWriteStat.yyw0aAxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw1_axi_stat[0]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_0] ));
	Ddim_Print(( "yw1_axi_stat[1]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_1] ));
	Ddim_Print(( "yw1_axi_stat[2]  = %u\n", r2yAxiWriteStat.yyw1AxiStat[D_IM_R2Y_PORT_2] ));
	Ddim_Print(( "yw2_axi_stat     = %u\n", r2yAxiWriteStat.yyw2AxiStat ));

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_17: "
INT32 ct_im_r2y_classc_1_17( CtImR2yClassc *self,UCHAR pipeNo )
{
	TImR2yAxiYywMode	r2yAxiWriteMode;
	UINT32					loopcnt;
	UCHAR					loopcnt2, loopsta, loopend;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ioR2yP1.yych.yyw0axmd.bit.yyw0msl = 0x3F;
		ioR2yP1.yych.yyw0axmd.bit.yyw0bl = 2;
		ioR2yP1.yych.yyw0axmd.bit.yyw0doe = 7;

		ioR2yP1.yych.yywaaxmd.bit.yywamsl = 0xF;
		ioR2yP1.yych.yywaaxmd.bit.yywabl = 2;
		ioR2yP1.yych.yywaaxmd.bit.yywadoe = 3;

		ioR2yP1.yych.yyw1axmd.bit.yyw1msl = 0x3F;
		ioR2yP1.yych.yyw1axmd.bit.yyw1bl = 2;
		ioR2yP1.yych.yyw1axmd.bit.yyw1doe = 7;

		ioR2yP1.yych.yyw2axmd.bit.yyw2msl = 3;
		ioR2yP1.yych.yyw2axmd.bit.yyw2bl = 2;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyw0axmd.bit.yyw0msl = 0x3F;
		ioR2yP2.yych.yyw0axmd.bit.yyw0bl = 2;
		ioR2yP2.yych.yyw0axmd.bit.yyw0doe = 7;

		ioR2yP2.yych.yywaaxmd.bit.yywamsl = 0xF;
		ioR2yP2.yych.yywaaxmd.bit.yywabl = 2;
		ioR2yP2.yych.yywaaxmd.bit.yywadoe = 3;

		ioR2yP2.yych.yyw1axmd.bit.yyw1msl = 0x3F;
		ioR2yP2.yych.yyw1axmd.bit.yyw1bl = 2;
		ioR2yP2.yych.yyw1axmd.bit.yyw1doe = 7;

		ioR2yP2.yych.yyw2axmd.bit.yyw2msl = 3;
		ioR2yP2.yych.yyw2axmd.bit.yyw2bl = 2;
	}
#endif //CO_DEBUG_ON_PC

	ct_im_r2y_get_loop_val(self->ctImR2y, pipeNo, &loopsta, &loopend );

	for( loopcnt = 0; loopcnt < D_IM_R2Y_YYW_CH_MAX; loopcnt++ ) {
		Ddim_Print(( "yyw = %u\n", loopcnt ));

		for( loopcnt2 = loopsta; loopcnt2 <= loopend; loopcnt2++ ){
			memset( &r2yAxiWriteMode, '\0', sizeof(r2yAxiWriteMode) );
#ifdef CO_MSG_PRINT_ON
			ercd = im_r2y_get_axi_write_mode(self->imR2y, loopcnt2, loopcnt, &r2yAxiWriteMode );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
			im_r2y_get_axi_write_mode(self->imR2y, loopcnt2, loopcnt, &r2yAxiWriteMode );
#endif

			Ddim_Print(( "PIPE%d\n", loopcnt2+1 ));
			Ddim_Print(( "masterIfSelect = %x\n", r2yAxiWriteMode.masterIfSelect ));
			Ddim_Print(( "burstLength     = %u\n", r2yAxiWriteMode.burstLength ));
			Ddim_Print(( "outEnable[0]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_0] ));
			Ddim_Print(( "outEnable[1]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_1] ));
			Ddim_Print(( "outEnable[2]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_2] ));
		}
	}

#ifdef CO_DEBUG_ON_PC
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
		ioR2yP1.yych.yyw0axmd.bit.yyw0msl = 0;
		ioR2yP1.yych.yyw0axmd.bit.yyw0bl = 0;
		ioR2yP1.yych.yyw0axmd.bit.yyw0doe = 0;

		ioR2yP1.yych.yywaaxmd.bit.yywamsl = 0;
		ioR2yP1.yych.yywaaxmd.bit.yywabl = 0;
		ioR2yP1.yych.yywaaxmd.bit.yywadoe = 0;

		ioR2yP1.yych.yyw1axmd.bit.yyw1msl = 0;
		ioR2yP1.yych.yyw1axmd.bit.yyw1bl = 0;
		ioR2yP1.yych.yyw1axmd.bit.yyw1doe = 0;

		ioR2yP1.yych.yyw2axmd.bit.yyw2msl = 0;
		ioR2yP1.yych.yyw2axmd.bit.yyw2bl = 0;
	}
	if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
		ioR2yP2.yych.yyw0axmd.bit.yyw0msl = 0;
		ioR2yP2.yych.yyw0axmd.bit.yyw0bl = 0;
		ioR2yP2.yych.yyw0axmd.bit.yyw0doe = 0;

		ioR2yP2.yych.yywaaxmd.bit.yywamsl = 0;
		ioR2yP2.yych.yywaaxmd.bit.yywabl = 0;
		ioR2yP2.yych.yywaaxmd.bit.yywadoe = 0;

		ioR2yP2.yych.yyw1axmd.bit.yyw1msl = 0;
		ioR2yP2.yych.yyw1axmd.bit.yyw1bl = 0;
		ioR2yP2.yych.yyw1axmd.bit.yyw1doe = 0;

		ioR2yP2.yych.yyw2axmd.bit.yyw2msl = 0;
		ioR2yP2.yych.yyw2axmd.bit.yyw2bl = 0;
	}
#endif //CO_DEBUG_ON_PC

	for( loopcnt = 0; loopcnt < D_IM_R2Y_YYW_CH_MAX; loopcnt++ ) {
		Ddim_Print(( "yyw = %u\n", loopcnt ));

		for( loopcnt2 = loopsta; loopcnt2 <= loopend; loopcnt2++ ){
			memset( &r2yAxiWriteMode, '\0', sizeof(r2yAxiWriteMode) );
#ifdef CO_MSG_PRINT_ON
			ercd = im_r2y_get_axi_write_mode(self->imR2y, loopcnt2, loopcnt, &r2yAxiWriteMode );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
			im_r2y_get_axi_write_mode(self->imR2y, loopcnt2, loopcnt, &r2yAxiWriteMode );
#endif

			Ddim_Print(( "PIPE%d\n", loopcnt2+1 ));
			Ddim_Print(( "masterIfSelect = %x\n", r2yAxiWriteMode.masterIfSelect ));
			Ddim_Print(( "burstLength     = %u\n", r2yAxiWriteMode.burstLength ));
			Ddim_Print(( "outEnable[0]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_0] ));
			Ddim_Print(( "outEnable[1]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_1] ));
			Ddim_Print(( "outEnable[2]    = %u\n", r2yAxiWriteMode.outEnable[D_IM_R2Y_PORT_2] ));
		}
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_18: "
INT32 ct_im_r2y_classc_1_18( CtImR2yClassc *self,UCHAR pipeNo )
{
	UINT32					loopcnt;
	TImR2yAxiYywMode	r2yAxiWriteMode[2][4] = {
		[0] = { // max
			[0] = { // YYW0
				.masterIfSelect = 0x3F,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
				.outEnable[D_IM_R2Y_PORT_2] = 1,
			},
			[1] = { // YYW1
				.masterIfSelect = 0x3F,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
				.outEnable[D_IM_R2Y_PORT_2] = 1,
			},
			[2] = { // YYW2
				.masterIfSelect = 3,
				.burstLength = 2,
			},
			[3] = { // YYWA
				.masterIfSelect = 0xF,
				.burstLength = 2,
				.outEnable[D_IM_R2Y_PORT_0] = 1,
				.outEnable[D_IM_R2Y_PORT_1] = 1,
			},
		},
		[1] = { // min
			[0] = { // YYW0
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
				.outEnable[D_IM_R2Y_PORT_2] = 0,
			},
			[1] = { // YYW1
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
				.outEnable[D_IM_R2Y_PORT_2] = 0,
			},
			[2] = { // YYW2
				.masterIfSelect = 0,
				.burstLength = 0,
			},
			[3] = { // YYWA
				.masterIfSelect = 0,
				.burstLength = 0,
				.outEnable[D_IM_R2Y_PORT_0] = 0,
				.outEnable[D_IM_R2Y_PORT_1] = 0,
			},
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	Ddim_Print(( "yyw = 0\n" ));
	for( loopcnt = 0; loopcnt < (sizeof(r2yAxiWriteMode) / sizeof(r2yAxiWriteMode[0])); loopcnt++ ) {
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 0, &r2yAxiWriteMode[loopcnt][0] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 0, r2yAxiWriteMode[loopcnt][0] );
#endif
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "yyw0axmd.bit.yyw0msl = 0x%x\n", ioR2yP1.yych.yyw0axmd.bit.yyw0msl ));
		Ddim_Print(( "yyw0axmd.bit.yyw0bl  = 0x%x\n", ioR2yP1.yych.yyw0axmd.bit.yyw0bl ));
		Ddim_Print(( "yyw0axmd.bit.yyw0doe = 0x%x\n", ioR2yP1.yych.yyw0axmd.bit.yyw0doe ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "yyw0axmd.bit.yyw0msl = 0x%x\n", ioR2yP2.yych.yyw0axmd.bit.yyw0msl ));
		Ddim_Print(( "yyw0axmd.bit.yyw0bl  = 0x%x\n", ioR2yP2.yych.yyw0axmd.bit.yyw0bl ));
		Ddim_Print(( "yyw0axmd.bit.yyw0doe = 0x%x\n", ioR2yP2.yych.yyw0axmd.bit.yyw0doe ));
	}

	Ddim_Print(( "yyw = 1\n" ));
	for( loopcnt = 0; loopcnt < (sizeof(r2yAxiWriteMode) / sizeof(r2yAxiWriteMode[0])); loopcnt++ ) {
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 1, &r2yAxiWriteMode[loopcnt][1] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 1, r2yAxiWriteMode[loopcnt][1] );
#endif
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "yyw1axmd.bit.yyw1msl = 0x%x\n", ioR2yP1.yych.yyw1axmd.bit.yyw1msl ));
		Ddim_Print(( "yyw1axmd.bit.yyw1bl  = 0x%x\n", ioR2yP1.yych.yyw1axmd.bit.yyw1bl ));
		Ddim_Print(( "yyw1axmd.bit.yyw1doe = 0x%x\n", ioR2yP1.yych.yyw1axmd.bit.yyw1doe ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "yyw1axmd.bit.yyw1msl = 0x%x\n", ioR2yP2.yych.yyw1axmd.bit.yyw1msl ));
		Ddim_Print(( "yyw1axmd.bit.yyw1bl  = 0x%x\n", ioR2yP2.yych.yyw1axmd.bit.yyw1bl ));
		Ddim_Print(( "yyw1axmd.bit.yyw1doe = 0x%x\n", ioR2yP2.yych.yyw1axmd.bit.yyw1doe ));
	}

	Ddim_Print(( "yyw = 2\n" ));
	for( loopcnt = 0; loopcnt < (sizeof(r2yAxiWriteMode) / sizeof(r2yAxiWriteMode[0])); loopcnt++ ) {
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 2, &r2yAxiWriteMode[loopcnt][2] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 2, r2yAxiWriteMode[loopcnt][2] );
#endif
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "yyw2axmd.bit.yyw2msl = 0x%x\n", ioR2yP1.yych.yyw2axmd.bit.yyw2msl ));
		Ddim_Print(( "yyw2axmd.bit.yyw2bl  = 0x%x\n", ioR2yP1.yych.yyw2axmd.bit.yyw2bl ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "yyw2axmd.bit.yyw2msl = 0x%x\n", ioR2yP2.yych.yyw2axmd.bit.yyw2msl ));
		Ddim_Print(( "yyw2axmd.bit.yyw2bl  = 0x%x\n", ioR2yP2.yych.yyw2axmd.bit.yyw2bl ));
	}

	Ddim_Print(( "yyw = 0a\n" ));
	for( loopcnt = 0; loopcnt < (sizeof(r2yAxiWriteMode) / sizeof(r2yAxiWriteMode[0])); loopcnt++ ) {
#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 3, &r2yAxiWriteMode[loopcnt][3] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_set_axi_write_mode(self->imR2y, pipeNo, 3, r2yAxiWriteMode[loopcnt][3] );
#endif
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "yywaaxmd.yywamsl     = 0x%x\n", ioR2yP1.yych.yywaaxmd.bit.yywamsl ));
		Ddim_Print(( "yywaaxmd.yywabl      = 0x%x\n", ioR2yP1.yych.yywaaxmd.bit.yywabl ));
		Ddim_Print(( "yywaaxmd.yywadoe     = 0x%x\n", ioR2yP1.yych.yywaaxmd.bit.yywadoe ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "yywaaxmd.yywamsl     = 0x%x\n", ioR2yP2.yych.yywaaxmd.bit.yywamsl ));
		Ddim_Print(( "yywaaxmd.yywabl      = 0x%x\n", ioR2yP2.yych.yywaaxmd.bit.yywabl ));
		Ddim_Print(( "yywaaxmd.yywadoe     = 0x%x\n", ioR2yP2.yych.yywaaxmd.bit.yywadoe ));
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_19: "
INT32 ct_im_r2y_classc_1_19( CtImR2yClassc *self,UCHAR pipeNo )
{
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif
	UINT32 loopcnt;

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(gctImR2yCtrl) / sizeof(gctImR2yCtrl[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrl[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrl[loopcnt] );
#endif

		ct_im_r2y_classa_print_r2y_ctrl_reg(self->ctImR2yClassa);

#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_20: "
INT32 ct_im_r2y_classc_1_20( CtImR2yClassc *self,UCHAR pipeNo )
{
	UINT32 loopcnt;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));


	for( loopcnt = 0; loopcnt < (sizeof(gctImR2yCtrlSdramIn) / sizeof(gctImR2yCtrlSdramIn[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramIn[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gctImR2yCtrlSdramIn[loopcnt] );
#endif

		ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);
	}

#ifdef IM_R2Y_STATUS_PRINT
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_21: "
INT32 ct_im_r2y_classc_1_21( CtImR2yClassc *self,UCHAR pipeNo )
{
	UINT32 loopcnt;
	TImR2yCtrlDirect r2yCtrlDirect[] = {
		[0] = {	// max
			.frameStop = 1,
		},
		[1] = {	// min
			.frameStop = 0,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yCtrlDirect) / sizeof(r2yCtrlDirect[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		ercd = im_r2y3_ctrl_mode_direct(self->imR2y3, pipeNo, &r2yCtrlDirect[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		im_r2y3_ctrl_mode_direct(self->imR2y3, pipeNo, &r2yCtrlDirect[loopcnt] );
#endif

		ct_im_r2y_classa_print_r2y_ctrl_modedirect_reg(self->ctImR2yClassa);

#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_22: "
INT32 ct_im_r2y_classc_1_22( CtImR2yClassc *self,UCHAR pipeNo )
{
	UINT32 loopcnt;
	TImR2yInaddrInfo r2yInAddr[] = {
		[0] = { // max
			.rgb.addrR = (VOID*)0xFFFFFFFF,
			.rgb.addrG = (VOID*)0xFFFFFFFF,
			.rgb.addrB = (VOID*)0xFFFFFFFF,
		},
		[1] = { // max
			.rgb.addrR = (VOID*)0,
			.rgb.addrG = (VOID*)0,
			.rgb.addrB = (VOID*)0,
		},
		[2] = { // indvisual
			.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_R_ADDR_TOP,
			.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_G_ADDR_TOP,
			.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U16_B_ADDR_TOP,
		},
	};
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < (sizeof(r2yInAddr) / sizeof(r2yInAddr[0])); loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		ercd = im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr[loopcnt] );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr[loopcnt] );
#endif

		ct_im_r2y_classa_print_r2y_ctrl_modesdraminput_reg(self->ctImR2yClassa);

		// im_r2y_calc_yyr_address_sdram_input(), im_r2y_set_yyr_address_sdram_input(), im_r2y_set_in_addr_info(self->imR2y,)
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "YYRA_0 = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_0 ));
		Ddim_Print(( "YYRA_1 = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_1 ));
		Ddim_Print(( "YYRA_2 = %lx\n", ioR2yP1.yyr.YYRA.bit.YYRA_2 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "YYRA_0 = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_0 ));
		Ddim_Print(( "YYRA_1 = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_1 ));
		Ddim_Print(( "YYRA_2 = %lx\n", ioR2yP2.yyr.YYRA.bit.YYRA_2 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );

#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_23: "
INT32 ct_im_r2y_classc_1_23( CtImR2yClassc *self,UCHAR pipeNo )
{
	TImR2yOutbankInfo r2yAddr[D_IM_R2Y_YYW_CH_MAX];
	UINT32 loopcnt;
	UINT32 yywNo;
	UINT32 yywBankNo;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	Ddim_Print(( "%s\n", D_IM_R2Y_FUNC_NAME ));

	for( loopcnt = 0; loopcnt < 3; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));


		switch( loopcnt ) {
			case 0:	// max
				for( yywNo = D_IM_R2Y_YYW_CH_0; yywNo < D_IM_R2Y_YYW_CH_MAX; yywNo++ ) {
					r2yAddr[yywNo].bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
					r2yAddr[yywNo].useBankNum = D_IM_R2Y_YYW_BANK_3;
					for( yywBankNo = D_IM_R2Y_YYW_BANK_0; yywBankNo < D_IM_R2Y_YYW_BANK_MAX; yywBankNo++ ) {
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrY = (VOID*)0xFFFFFFFF;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCb = (VOID*)0xFFFFFFFF;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCr = (VOID*)0xFFFFFFFF;
					}
				}
				break;
			case 1:	// min
				for( yywNo = D_IM_R2Y_YYW_CH_0; yywNo < D_IM_R2Y_YYW_CH_MAX; yywNo++ ) {
					r2yAddr[yywNo].bankInitialPosition = D_IM_R2Y_YYW_BANK_0;
					r2yAddr[yywNo].useBankNum = D_IM_R2Y_YYW_BANK_0;
					for( yywBankNo = D_IM_R2Y_YYW_BANK_0; yywBankNo < D_IM_R2Y_YYW_BANK_MAX; yywBankNo++ ) {
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrY = (VOID*)0;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCb = (VOID*)0;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCr = (VOID*)0;
					}
				}
				break;
			default:
//			case 0:	// indivisual
				for( yywNo = D_IM_R2Y_YYW_CH_0; yywNo < D_IM_R2Y_YYW_CH_MAX; yywNo++ ) {
					r2yAddr[yywNo].bankInitialPosition = D_IM_R2Y_YYW_BANK_1;
					r2yAddr[yywNo].useBankNum = D_IM_R2Y_YYW_BANK_2;
					for( yywBankNo = D_IM_R2Y_YYW_BANK_0; yywBankNo < D_IM_R2Y_YYW_BANK_MAX; yywBankNo++ ) {
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrY = (VOID*)0x1FFFFFF0;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCb = (VOID*)0x2FFFFFF0;
						r2yAddr[yywNo].outputAddr[yywBankNo].ycc.addrCr = (VOID*)0x3FFFFFF0;
					}
				}
				break;
		}

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));

		for( yywNo = D_IM_R2Y_YYW_CH_0; yywNo < D_IM_R2Y_YYW_CH_MAX; yywNo++ ) {
			ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, yywNo, &r2yAddr[yywNo] );
			Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d\n", ercd ));
		}
#else
		im_r2y_ctrl(self->imR2y, pipeNo, &gctImR2yCtrlBase );
		im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
		for( yywNo = D_IM_R2Y_YYW_CH_0; yywNo < D_IM_R2Y_YYW_CH_MAX; yywNo++ ) {
			im_r2y_set_out_bank_info(self->imR2y, pipeNo, yywNo, &r2yAddr[yywNo] );
		}
#endif

		im_r2y_clk_on_pclk(self->imR2yClk, pipeNo );
		Ddim_Print(( "PIPE1\n" ));
		Ddim_Print(( "usebank0  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank0 ));
		Ddim_Print(( "yyw0a00 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a00 ));
		Ddim_Print(( "yyw0a10 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a10 ));
		Ddim_Print(( "yyw0a20 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a20 ));
		Ddim_Print(( "yyw0a01 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a01 ));
		Ddim_Print(( "yyw0a11 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a11 ));
		Ddim_Print(( "yyw0a21 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a21 ));
		Ddim_Print(( "yyw0a02 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a02 ));
		Ddim_Print(( "yyw0a12 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a12 ));
		Ddim_Print(( "yyw0a22 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a22 ));
		Ddim_Print(( "yyw0a03 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a03 ));
		Ddim_Print(( "yyw0a13 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a13 ));
		Ddim_Print(( "yyw0a23 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw0a.bit.yyw0a23 ));
		Ddim_Print(( "usebank1  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank1 ));
		Ddim_Print(( "yyw1a00 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a00 ));
		Ddim_Print(( "yyw1a10 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a10 ));
		Ddim_Print(( "yyw1a20 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a20 ));
		Ddim_Print(( "yyw1a01 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a01 ));
		Ddim_Print(( "yyw1a11 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a11 ));
		Ddim_Print(( "yyw1a21 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a21 ));
		Ddim_Print(( "yyw1a02 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a02 ));
		Ddim_Print(( "yyw1a12 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a12 ));
		Ddim_Print(( "yyw1a22 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a22 ));
		Ddim_Print(( "yyw1a03 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a03 ));
		Ddim_Print(( "yyw1a13 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a13 ));
		Ddim_Print(( "yyw1a23 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw1a.bit.yyw1a23 ));
		Ddim_Print(( "usebank2  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebank2 ));
		Ddim_Print(( "YYW2A_0_0 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a0 ));
		Ddim_Print(( "YYW2A_2_1 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a1 ));
		Ddim_Print(( "YYW2A_2_2 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a2 ));
		Ddim_Print(( "YYW2A_2_3 = 0x%x\n", (UINT32)ioR2yP1.yyw.yyw2a.bit.yyw2a3 ));
		Ddim_Print(( "usebanka  = %u\n",   (UINT32)ioR2yP1.yyw.yywctl.bit.usebanka ));
		Ddim_Print(( "yywaa00 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa00 ));
		Ddim_Print(( "yywaa10 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa10 ));
		Ddim_Print(( "yywaa01 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa01 ));
		Ddim_Print(( "yywaa11 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa11 ));
		Ddim_Print(( "yywaa02 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa02 ));
		Ddim_Print(( "yywaa12 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa12 ));
		Ddim_Print(( "yywaa03 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa03 ));
		Ddim_Print(( "yywaa13 = 0x%x\n", (UINT32)ioR2yP1.yyw.yywaa.bit.yywaa13 ));
		Ddim_Print(( "PIPE2\n" ));
		Ddim_Print(( "usebank0  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank0 ));
		Ddim_Print(( "yyw0a00 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a00 ));
		Ddim_Print(( "yyw0a10 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a10 ));
		Ddim_Print(( "yyw0a20 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a20 ));
		Ddim_Print(( "yyw0a01 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a01 ));
		Ddim_Print(( "yyw0a11 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a11 ));
		Ddim_Print(( "yyw0a21 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a21 ));
		Ddim_Print(( "yyw0a02 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a02 ));
		Ddim_Print(( "yyw0a12 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a12 ));
		Ddim_Print(( "yyw0a22 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a22 ));
		Ddim_Print(( "yyw0a03 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a03 ));
		Ddim_Print(( "yyw0a13 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a13 ));
		Ddim_Print(( "yyw0a23 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw0a.bit.yyw0a23 ));
		Ddim_Print(( "usebank1  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank1 ));
		Ddim_Print(( "yyw1a00 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a00 ));
		Ddim_Print(( "yyw1a10 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a10 ));
		Ddim_Print(( "yyw1a20 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a20 ));
		Ddim_Print(( "yyw1a01 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a01 ));
		Ddim_Print(( "yyw1a11 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a11 ));
		Ddim_Print(( "yyw1a21 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a21 ));
		Ddim_Print(( "yyw1a02 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a02 ));
		Ddim_Print(( "yyw1a12 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a12 ));
		Ddim_Print(( "yyw1a22 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a22 ));
		Ddim_Print(( "yyw1a03 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a03 ));
		Ddim_Print(( "yyw1a13 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a13 ));
		Ddim_Print(( "yyw1a23 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw1a.bit.yyw1a23 ));
		Ddim_Print(( "usebank2  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebank2 ));
		Ddim_Print(( "YYW2A_0_0 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a0 ));
		Ddim_Print(( "YYW2A_2_1 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a1 ));
		Ddim_Print(( "YYW2A_2_2 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a2 ));
		Ddim_Print(( "YYW2A_2_3 = 0x%x\n", (UINT32)ioR2yP2.yyw.yyw2a.bit.yyw2a3 ));
		Ddim_Print(( "usebanka  = %u\n",   (UINT32)ioR2yP2.yyw.yywctl.bit.usebanka ));
		Ddim_Print(( "yywaa00 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa00 ));
		Ddim_Print(( "yywaa10 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa10 ));
		Ddim_Print(( "yywaa01 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa01 ));
		Ddim_Print(( "yywaa11 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa11 ));
		Ddim_Print(( "yywaa02 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa02 ));
		Ddim_Print(( "yywaa12 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa12 ));
		Ddim_Print(( "yywaa03 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa03 ));
		Ddim_Print(( "yywaa13 = 0x%x\n", (UINT32)ioR2yP2.yyw.yywaa.bit.yywaa13 ));
		im_r2y_clk_off_pclk(self->imR2yClk, pipeNo );


#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

#undef D_IM_R2Y_FUNC_NAME
#define D_IM_R2Y_FUNC_NAME "ct_im_r2y_classc_1_24: "
INT32 ct_im_r2y_classc_1_24( CtImR2yClassc *self,UCHAR pipeNo )
{
	TImR2yCtrl r2yCtrl = gctImR2yCtrlBase;
	TImR2yResizeRect r2yResizeRectParam;
	TImR2yInaddrInfo r2yInAddr;
	TImR2yOutbankInfo r2yAddr0;
	UINT32 loopcnt;
	UCHAR bankIndex;
	DDIM_USER_FLGPTN flgptn = 0;
#ifdef CO_MSG_PRINT_ON
	INT32 ercd;
#endif

	r2yCtrl.outputMode0a = D_IM_R2Y_YYW0A_OUTPUT_MODE_DIV_4_Y;

	r2yResizeRectParam.inputSize.imgTop = 0;
	r2yResizeRectParam.inputSize.imgLeft = 0;
	r2yResizeRectParam.inputSize.imgWidth = D_IM_R2Y_SRC_IMG_PIXS_WIDTH;
	r2yResizeRectParam.inputSize.imgLines = D_IM_R2Y_SRC_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywWidth = D_IM_R2Y_DST_IMG_PIXS_WIDTH;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].yywLines = D_IM_R2Y_DST_IMG_PIXS_LINES;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0].outputGlobalW[D_IM_R2Y_PORT_CB] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_0A].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywWidth = 320;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].yywLines = 240;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_1].outputGlobalW[D_IM_R2Y_PORT_CB] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_C;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywWidth = 320;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].yywLines = 240;
	r2yResizeRectParam.outputSize[D_IM_R2Y_YYW_CH_2].outputGlobalW[D_IM_R2Y_PORT_Y] = D_IM_R2Y_DST_IMG_GLOBAL_WIDTH_YCC422_Y;

	r2yInAddr.rgb.addrR = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_R_ADDR_TOP;
	r2yInAddr.rgb.addrG = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_G_ADDR_TOP;
	r2yInAddr.rgb.addrB = (VOID*)D_IM_R2Y_IMG_MEM_IN_RGB_U8_B_ADDR_TOP;

	memset( &r2yAddr0, '\x0', sizeof(r2yAddr0) );
	r2yAddr0.bankInitialPosition = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.useBankNum = D_IM_R2Y_YYW_BANK_3;
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrY = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP + 0x0);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCb = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP + 0x0);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_0].ycc.addrCr = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP + 0x0);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrY = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP + 0x4);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCb = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP + 0x4);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_1].ycc.addrCr = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP + 0x4);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrY = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP + 0x8);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCb = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP + 0x8);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_2].ycc.addrCr = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP + 0x8);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrY = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_Y_ADDR_TOP + 0xC);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCb = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CB_ADDR_TOP + 0xC);
	r2yAddr0.outputAddr[D_IM_R2Y_YYW_BANK_3].ycc.addrCr = (VOID*)(D_IM_R2Y_IMG_MEM_OUT_YCC422_CR_ADDR_TOP + 0xC);

#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

	ercd = im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0 );
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
	im_r2y_ctrl(self->imR2y, pipeNo, &r2yCtrl );
	im_r2y_ctrl_mode_Sdram_input(self->imR2y, pipeNo, &gct_im_r2y_ctrl_sdram_in_base );
	im_r2y2_set_resize_rect(self->imR2y2, pipeNo, &r2yResizeRectParam );
	im_r2y_set_in_addr_info(self->imR2y, pipeNo, &r2yInAddr );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &r2yAddr0 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &r2yAddr0 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &r2yAddr0 );
	im_r2y_set_out_bank_info(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &r2yAddr0 );
#endif

	Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", 0 ));

#ifdef IM_R2Y_STATUS_PRINT
	Ddim_Print(( D_IM_R2Y_FUNC_NAME "Status\n" ));
	im_r2y_stat_print_status(self->imR2yStat);
#endif

	for( loopcnt = 0; loopcnt < D_IM_R2Y_YYW_BANK_MAX; loopcnt++ ) {
		Ddim_Print(( "** %u\n", loopcnt ));

#ifdef D_IM_R2Y_DEBUG_ON_PC
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[0] = 1;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[1] = 1;
		}
#endif
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "R2Y Start\n" ));


#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "loopcnt = %u\n", loopcnt ));
		ercd = Im_R2Y_Start( pipeNo );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
		Im_R2Y_Start( pipeNo );
#endif

#ifdef D_IM_R2Y_DEBUG_ON_PC
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[0] = 0;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			gIM_R2Y_macro_fake_finish[1] = 0;
		}
#endif

		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_1( pipeNo ) ){
			flgptn |= D_IM_R2Y1_INT_FLG_YYW0_END;
		}
		if( CtImR2yTool_CHECK_TARGET_PIPE_NO_2( pipeNo ) ){
			flgptn |= D_IM_R2Y2_INT_FLG_YYW0_END;
		}

#ifdef CO_MSG_PRINT_ON
		ercd = im_r2y_proc_wait_end(self->imR2yProc, NULL, flgptn, 60 );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));

		ercd = im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &bankIndex );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex ));

		ercd = im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &bankIndex );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex ));

		ercd = im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &bankIndex );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex ));

		ercd = im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &bankIndex );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "%d bank_idx=%u\n", ercd, bankIndex ));

		ercd = Im_R2Y_Stop( pipeNo );
		Ddim_Print(( D_IM_R2Y_FUNC_NAME "0x%x\n", ercd ));
#else
		im_r2y_proc_wait_end(self->imR2yProc, NULL, flgptn, 60 );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0, &bankIndex );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_1, &bankIndex );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_2, &bankIndex );
		im_r2y_get_out_bank_index(self->imR2y, pipeNo, D_IM_R2Y_YYW_CH_0A, &bankIndex );
		Im_R2Y_Stop( pipeNo );
#endif


#ifdef IM_R2Y_STATUS_PRINT
		im_r2y_stat_print_status(self->imR2yStat);
#endif
	}

	return D_DDIM_OK;
}

CtImR2yClassc* ct_im_r2y_classc_new(void)
{
	CtImR2yClassc* self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSC, sizeof(CtImR2yClasscPrivate));

	return self;
}

CtImR2yClassc* ct_im_r2y_classc_get(void)
{
	static CtImR2yClassc* self = NULL;

	if (!self) {
		self = k_object_new_with_private(CT_TYPE_IM_R2Y_CLASSC, sizeof(CtImR2yClasscPrivate));
	}

	return self;
}
