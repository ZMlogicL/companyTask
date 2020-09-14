/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author             chenling
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

#include "improcommon.h"
#include "dd_top.h"
#include "improcommonfig.h"
#include"improcommonlist.h"
K_TYPE_DEFINE_WITH_PRIVATE(ImProCommonFig, im_pro_common_fig);
#define IM_PRO_COMMON_FIG_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImProCommonFigPrivate, IM_TYPE_PRO_COMMON_FIG))



struct _ImProCommonFigPrivate
{
	int a;
};

// OBT
static	volatile	T_IM_PRO_OBT_BUF_INFO	gIM_PRO_OBT_Buffer_Info[D_IM_PRO_SENTOP_BLOB_NUM][D_IM_PRO_SEN_OBT_CH_NUM] = {
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
	{
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
		{	.addr_index.cur = 0,	.addr_index.max = D_IM_PRO_OB_BUFFER_MAX - 1,	},
	},
};

static	volatile	T_IM_PRO_STAT_AF_BUF_INFO	gIM_PRO_AF_Buffer_Info[D_IM_PRO_STAT_AF_CH_NUM][ E_IM_PRO_AF_WINDOW_MAX ];
static	volatile	T_IM_PRO_STAT_HIST_BUF_INFO	gIM_PRO_HIST_Buffer_Info[D_IM_PRO_STAT_HIST_CH_NUM];
static	volatile	ULONG	gIM_SEN_START_Status[3] = {0x00000000};


static void im_pro_common_fig_constructor(ImProCommonFig *self)
{
	ImProCommonFigPrivate *priv = IM_PRO_COMMON_FIG_GET_PRIVATE(self);
	priv-> a = 0;
}

static void im_pro_common_fig_destructor(ImProCommonFig *self)
{
	ImProCommonFigPrivate *priv = IM_PRO_COMMON_FIG_GET_PRIVATE(self);
	priv-> a = 0;
}

BOOL im_pro_common_fig_im_pro_comm_get_start_status( ImProCommonFig* self,UINT32 status, UINT32 ch )
{ImProCommonList* imProCommonList=im_pro_common_list_get();
	return im_pro_common_get_start_status( status, ch );
}

VOID im_pro_comm_update_obt_result( UINT32 blob_num, UINT32 ch )
{
	gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_addr = &gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur ];

	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );	// Dd_Top_Start_Clock
	gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur ].R	= IO_PRO.SEN.OBT[blob_num][ch].OBTCORE.OBTDATAR.bit.OBTDATAR;
	gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur ].Gr	= IO_PRO.SEN.OBT[blob_num][ch].OBTCORE.OBTDATAGR.bit.OBTDATAGR;
	gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur ].Gb	= IO_PRO.SEN.OBT[blob_num][ch].OBTCORE.OBTDATAGB.bit.OBTDATAGB;
	gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_table[ gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur ].B	= IO_PRO.SEN.OBT[blob_num][ch].OBTCORE.OBTDATAB.bit.OBTDATAB;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_SEN );	// Dd_Top_Stop_Clock

	gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur++;
	if (gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur > gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.max){
		// Index Reset
		gIM_PRO_OBT_Buffer_Info[blob_num][ch].addr_index.cur = 0;
	}
}

VOID im_pro_comm_get_obt_data( UINT32 blob_num, UINT32 ch, T_IM_PRO_RGB2* data )
{
#ifdef CO_PARAM_CHECK
	if( data == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_obt_data error. ch:%d data=NULL\n", ch));
		return;
	}
#endif
	im_pro_common_fig_im_pro_memcpy(NULL,data, (void *)gIM_PRO_OBT_Buffer_Info[blob_num][ch].data_addr, sizeof(T_IM_PRO_RGB2));
}

VOID im_pro_common_fig_im_pro_sen_set_start_status(ImProCommonFig* self,UINT32 status, UINT32 ch)
{
	(gIM_SEN_START_Status[((status) >> 28) & 0xf] |=  (((status) & 0x0fffffff) << (ch)));	/* SEN clock status ON	*/
}

VOID im_pro_common_fig_im_pro_sen_set_stop_status(ImProCommonFig* self,UINT32 status, UINT32 ch)
{
	(gIM_SEN_START_Status[((status) >> 28) & 0xf] &= ~(((status) & 0x0fffffff) << (ch)));	/* SEN clock status OFF	*/
}

BOOL im_pro_common_fig_im_pro_sen_get_start_status(ImProCommonFig* self,UINT32 status, UINT32 ch)
{
	return (((gIM_SEN_START_Status[((status) >> 28) & 0xf] & (((status) & 0x0fffffff) << (ch))) != 0) ? TRUE : FALSE);		/* started check	*/
}

BOOL im_pro_common_fig_im_pro_sen_get_stop_all(ImProCommonFig* self)
{
	return (((gIM_SEN_START_Status[0] | gIM_SEN_START_Status[1] | gIM_SEN_START_Status[2]) != 0) ? FALSE : TRUE);	/* started check	*/
}

VOID im_pro_comm_update_hist_result( E_IM_PRO_HIST_CH ch )
{
	gIM_PRO_HIST_Buffer_Info[ch].last_data_index	= gIM_PRO_HIST_Buffer_Info[ch].current_data_index;
	gIM_PRO_HIST_Buffer_Info[ch].current_data_index	= gIM_PRO_HIST_Buffer_Info[ch].data_index.cur;

	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]	= IO_PRO.STAT.HIST[ch].HISTRMODE.bit.HISTRMODE;
	gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]	= IO_PRO.STAT.HIST[ch].HISTGMODE.bit.HISTGMODE;
	gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]	= IO_PRO.STAT.HIST[ch].HISTBMODE.bit.HISTBMODE;
	gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]	= IO_PRO.STAT.HIST[ch].HISTYMODE.bit.HISTYMODE;
	gIM_PRO_HIST_Buffer_Info[ch].sum_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]					= IO_PRO.STAT.HIST[ch].HISTRSUM.bit.HISTRSUM;
	gIM_PRO_HIST_Buffer_Info[ch].sum_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]					= IO_PRO.STAT.HIST[ch].HISTGSUM.bit.HISTGSUM;
	gIM_PRO_HIST_Buffer_Info[ch].sum_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]					= IO_PRO.STAT.HIST[ch].HISTBSUM.bit.HISTBSUM;
	gIM_PRO_HIST_Buffer_Info[ch].sum_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ]					= IO_PRO.STAT.HIST[ch].HISTYSUM.bit.HISTYSUM;
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	im_pro_common_fig_im_pro_on_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)&gIM_PRO_HIST_Buffer_Info[ch].data_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], (void*)&IO_PRO_TBL.STAT_TBL.HISTDATA[ch].HISTRDATA.word[0], sizeof( gIM_PRO_HIST_Buffer_Info[ch].data_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ] ) );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)&gIM_PRO_HIST_Buffer_Info[ch].data_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], (void*)&IO_PRO_TBL.STAT_TBL.HISTDATA[ch].HISTGDATA.word[0], sizeof( gIM_PRO_HIST_Buffer_Info[ch].data_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ] ) );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)&gIM_PRO_HIST_Buffer_Info[ch].data_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], (void*)&IO_PRO_TBL.STAT_TBL.HISTDATA[ch].HISTBDATA.word[0], sizeof( gIM_PRO_HIST_Buffer_Info[ch].data_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ] ) );
	im_pro_common_fig_im_pro_memcpy( NULL,(void*)&gIM_PRO_HIST_Buffer_Info[ch].data_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], (void*)&IO_PRO_TBL.STAT_TBL.HISTDATA[ch].HISTYDATA.word[0], sizeof( gIM_PRO_HIST_Buffer_Info[ch].data_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ] ) );
	im_pro_off_hclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );

	gIM_PRO_HIST_Buffer_Info[ch].data_index.cur++;
	if (gIM_PRO_HIST_Buffer_Info[ch].data_index.cur > gIM_PRO_HIST_Buffer_Info[ch].data_index.max){
		// Index Reset
		gIM_PRO_HIST_Buffer_Info[ch].data_index.cur = 0;
	}
}

VOID im_pro_comm_get_hist_result( E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_DATA* hist_data )
{
#ifdef CO_PARAM_CHECK
	if( hist_data == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_hist_result error. ch:%d hist_data=NULL\n", ch));
		return;
	}
#endif
	hist_data->most_frequent_value[0]	= gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->most_frequent_value[1]	= gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->most_frequent_value[2]	= gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->most_frequent_value[3]	= gIM_PRO_HIST_Buffer_Info[ch].most_frequent_value_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->accumulation_value[0]	= gIM_PRO_HIST_Buffer_Info[ch].sum_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->accumulation_value[1]	= gIM_PRO_HIST_Buffer_Info[ch].sum_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->accumulation_value[2]	= gIM_PRO_HIST_Buffer_Info[ch].sum_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
	hist_data->accumulation_value[3]	= gIM_PRO_HIST_Buffer_Info[ch].sum_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ];
}

VOID im_pro_comm_get_hist_ram( E_IM_PRO_HIST_CH ch, T_IM_PRO_HIST_RAM_DATA* hist_ram_data )
{
#ifdef CO_PARAM_CHECK
	if( hist_ram_data == NULL ) {
		Ddim_Assertion(("I:im_pro_comm_get_hist_ram error. ch:%d hist_ram_data=NULL\n", ch));
		return;
	}
#endif
	im_pro_common_fig_im_pro_memcpy( NULL,hist_ram_data->r, (void*)&gIM_PRO_HIST_Buffer_Info[ch].data_r[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], sizeof( hist_ram_data->r ) );
	im_pro_common_fig_im_pro_memcpy( NULL,hist_ram_data->g, (void*)&gIM_PRO_HIST_Buffer_Info[ch].data_g[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], sizeof( hist_ram_data->g ) );
	im_pro_common_fig_im_pro_memcpy( NULL,hist_ram_data->b, (void*)&gIM_PRO_HIST_Buffer_Info[ch].data_b[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], sizeof( hist_ram_data->b ) );
	im_pro_common_fig_im_pro_memcpy( NULL,hist_ram_data->y, (void*)&gIM_PRO_HIST_Buffer_Info[ch].data_y[ gIM_PRO_HIST_Buffer_Info[ch].current_data_index ][0], sizeof( hist_ram_data->y ) );
}

VOID im_pro_comm_update_af_result( E_IM_PRO_AF_CH ch )
{
	UCHAR	i;

	im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
	for (i = E_IM_PRO_AF_WINDOW_MAX; i > 0; i --){
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].last_data_index		= gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index	= gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].data_index.cur;

		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataS_Tbl    [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAS.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataGE_Tbl   [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAGE.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataL_Tbl    [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAL.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataH0_Tbl   [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAH0.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataH1_Tbl   [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAH1.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataH2_Tbl   [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAH2.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataV_Tbl    [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAV.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMAX_Tbl  [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMAX.bit.AFDATAMAX;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMIN_Tbl  [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMIN.bit.AFDATAMIN;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMAXE_Tbl [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMAX.bit.AFDATAMAXE;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMINE_Tbl [gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMIN.bit.AFDATAMINE;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMAXH0_Tbl[gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMH0.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMAXH1_Tbl[gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMH1.word;
		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].DataMAXH2_Tbl[gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].current_data_index]	= IO_PRO.STAT.AF[ch].AFWIN[ i - 1 ].AFDATAMH2.word;

		gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].data_index.cur++;
		if (gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].data_index.cur > gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].data_index.max){
			// Index Reset
			gIM_PRO_AF_Buffer_Info[ch][ i - 1 ].data_index.cur = 0;
		}
	}
	im_pro_off_pclk( E_IM_PRO_UNIT_NUM_1, E_IM_PRO_CLK_BLOCK_TYPE_STAT );
}

ULONG im_pro_comm_get_af_data( E_IM_PRO_AF_CH ch, E_IM_PRO_AF_WINDOW_NO win_no, E_IM_PRO_AF_RESULT_TYPE type, E_IM_PRO_AF_RESULT_DATA_TYPE data_type )
{
	UCHAR index = 0;
	ULONG rer_data = 0;
	if( data_type == E_IM_PRO_AF_RESULT_DATA_TYPE_CURRENT ) {
		index = gIM_PRO_AF_Buffer_Info[ch][win_no].current_data_index;
	}
	else {
		index = gIM_PRO_AF_Buffer_Info[ch][win_no].last_data_index;
	}

	switch( type) {
		case E_IM_PRO_AF_RESULT_TYPE_EVAL_CALC:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataS_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVAL_BRIGHT:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataGE_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVAL_DARK:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataL_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL0:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataH0_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL1:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataH1_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL2:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataH2_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_VERTICAL:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataV_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MAX:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMAX_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVALUATED_VALUE_MIN:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMIN_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MAX:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMAXE_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_EVALUATION_VALUE_MIN:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMINE_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_0_EACH_LINE_MAX:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMAXH0_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_1_EACH_LINE_MAX:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMAXH1_Tbl[index];
			break;
		case E_IM_PRO_AF_RESULT_TYPE_HORIZONTAL_2_EACH_LINE_MAX:
			rer_data = gIM_PRO_AF_Buffer_Info[ch][win_no].DataMAXH2_Tbl[index];
			break;
		default:
			break;
	}

	return rer_data;
}

VOID im_pro_common_fig_im_pro_memcpy(ImProCommonFig* self,VOID *dst, VOID *src, UINT32 cp_size)
{
	UINT32	i;
	UCHAR*	dst_addr;
	UCHAR*	src_addr;
	dst_addr = dst;
	src_addr = src;
	for (i = 0; i < cp_size; i ++){
		*dst_addr ++ = *src_addr ++;
	}
}

VOID im_pro_comm_get_clk_loop_cnt( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type, E_IM_PRO_UNIT_NUM* loop_start, E_IM_PRO_UNIT_NUM* loop_end )
{
	switch( unit_no ) {
		case E_IM_PRO_UNIT_NUM_1:
			*loop_start	= unit_no;
			*loop_end	= E_IM_PRO_UNIT_NUM_2;
			break;

		case E_IM_PRO_UNIT_NUM_2:
			*loop_start	= unit_no;
			*loop_end	= E_IM_PRO_BOTH_UNIT;
			break;

		//case E_IM_PRO_BOTH_UNIT:
		default:
			if( (block_type == E_IM_PRO_CLK_BLOCK_TYPE_SEN)		||
				(block_type == E_IM_PRO_CLK_BLOCK_TYPE_STAT)	||
				(block_type == E_IM_PRO_CLK_BLOCK_TYPE_PAS) ) {
				*loop_start	= E_IM_PRO_UNIT_NUM_1;
				*loop_end	= E_IM_PRO_UNIT_NUM_2;
			}
			else {
				*loop_start	= E_IM_PRO_UNIT_NUM_1;
				*loop_end	= E_IM_PRO_BOTH_UNIT;
			}
			break;
	}
}

VOID im_pro_common_fig_im_pro_on_drive_clk(E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_CLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Drive_Clk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_common_fig_im_pro_on_drive_clk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Start_Clock(	(UCHAR*)gIM_Drive_Clk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Drive_Clk_Info[loop_start][block_type].reg_addr,
							~gIM_Drive_Clk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_common_fig_im_pro_on_pclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_PCLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );

	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Pclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_common_fig_im_pro_on_pclk error. loop_start:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Start_Clock(	(UCHAR*)gIM_Pclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Pclk_Info[loop_start][block_type].reg_addr,
							~gIM_Pclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_common_fig_im_pro_on_hclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
	if( ( block_type == E_IM_PRO_CLK_BLOCK_TYPE_STAT ) ||
		( block_type == E_IM_PRO_CLK_BLOCK_TYPE_PAS ) ) {
		DDIM_User_AhbReg_SpinLock();	// JPEG issue work around.
	}
#ifdef CO_ACT_PRO_HCLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Hclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_common_fig_im_pro_on_hclk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Start_Clock(	(UCHAR*)gIM_Hclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Hclk_Info[loop_start][block_type].reg_addr,
							~gIM_Hclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_common_fig_im_pro_on_xclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_ICLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Xclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_common_fig_im_pro_on_xclk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Start_Clock(	(UCHAR*)gIM_Xclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Xclk_Info[loop_start][block_type].reg_addr,
							~gIM_Xclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_off_drive_clk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_CLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Drive_Clk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_off_drive_clk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Stop_Clock(	(UCHAR*)gIM_Drive_Clk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Drive_Clk_Info[loop_start][block_type].reg_addr,
							gIM_Drive_Clk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_off_pclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_PCLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Pclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_off_pclk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Stop_Clock(	(UCHAR*)gIM_Pclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Pclk_Info[loop_start][block_type].reg_addr,
							gIM_Pclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

VOID im_pro_off_hclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_HCLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Hclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_off_hclk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Stop_Clock(	(UCHAR*)gIM_Hclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Hclk_Info[loop_start][block_type].reg_addr,
							gIM_Hclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
	if( ( block_type == E_IM_PRO_CLK_BLOCK_TYPE_STAT ) ||
		( block_type == E_IM_PRO_CLK_BLOCK_TYPE_PAS ) ) {
		DDIM_User_AhbReg_SpinUnLock();	// JPEG issue work around.
	}
}

VOID im_pro_off_xclk( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type )
{
#ifdef CO_ACT_PRO_ICLOCK
	E_IM_PRO_UNIT_NUM loop_start = E_IM_PRO_UNIT_NUM_1;
	E_IM_PRO_UNIT_NUM loop_end = E_IM_PRO_UNIT_NUM_2;

	im_pro_comm_get_clk_loop_cnt( unit_no, block_type, &loop_start, &loop_end );
	for( ; loop_start < loop_end; loop_start++ ) {
		if( gIM_Xclk_Info[loop_start][block_type].reg_addr == 0 ) {
			Ddim_Assertion(("I:im_pro_off_xclk error. unit_no:%u block_type=%u\n", loop_start, block_type));
			return;
		}
		im_pro_spin_lock_start( loop_start, block_type, gIM_PRO_Spin_Lock );
		Dd_Top_Stop_Clock(	(UCHAR*)gIM_Xclk_Info[loop_start][block_type].reg_ctrl_cnt,
							gIM_Xclk_Info[loop_start][block_type].reg_addr,
							gIM_Xclk_Info[loop_start][block_type].reg_bit );
		im_pro_spin_lock_end( loop_start, block_type, gIM_PRO_Spin_Lock );
	}
#endif
}

UINT32 im_pro_get_sen_clk_hz( VOID )
{
	UINT32 macro_clk_sel = 0;
	UINT32 macro_clk_hz = 0;
	macro_clk_sel = Dd_Top_Get_CLKSEL3_SENCLK();
	if( macro_clk_sel == SENCLK_300MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_300MHZ;
	}
	else if( macro_clk_sel == SENCLK_200MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_200MHZ;
	}
	else if( macro_clk_sel == SENCLK_150MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_150MHZ;
	}
	else if( macro_clk_sel == SENCLK_100MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_100MHZ;
	}
	else if( macro_clk_sel == SENCLK_75MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_75MHZ;
	}
	else if( macro_clk_sel == SENCLK_60MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_60MHZ;
	}
	else if( macro_clk_sel == SENCLK_50MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_50MHZ;
	}
	return macro_clk_hz;
}

VOID im_pro_get_current_clk_hz( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_CLK_BLOCK_TYPE block_type, UINT32* cpu_clk_hz, UINT32* macro_clk_hz )
{
	switch( block_type ) {
		case E_IM_PRO_CLK_BLOCK_TYPE_SEN:
			*macro_clk_hz = im_pro_get_sen_clk_hz();
			break;
		case E_IM_PRO_CLK_BLOCK_TYPE_SRO:
			*macro_clk_hz = im_pro_get_sro_clk_hz( unit_no );
			break;
		case E_IM_PRO_CLK_BLOCK_TYPE_SRO2:
			*macro_clk_hz = im_pro_get_sro2_clk_hz( unit_no );
			break;
		case E_IM_PRO_CLK_BLOCK_TYPE_B2B:
			*macro_clk_hz = im_pro_get_b2b_clk_hz( unit_no );
			break;
		case E_IM_PRO_CLK_BLOCK_TYPE_STAT:
			// it calculated by most low clock working conditions
			// because STAT block works on any connection blocks clock.
			*macro_clk_hz = D_IM_PRO_CLK_50MHZ;
			break;
		case E_IM_PRO_CLK_BLOCK_TYPE_PAS:
			*macro_clk_hz = im_pro_get_pas_clk_hz();
			break;
		default:
			*macro_clk_hz = 0;
			break;
	}
	*cpu_clk_hz	= D_IM_PRO_CA7_CLK_HZ;
}

UINT32 im_pro_get_pas_clk_hz( VOID )
{
	UINT32 macro_clk_sel = 0;
	UINT32 macro_clk_hz = 0;
	macro_clk_sel = Dd_Top_Get_CLKSEL3_PASCLK();
	if( macro_clk_sel == PASCLK_300MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_300MHZ;
	}
	else if( macro_clk_sel == PASCLK_200MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_200MHZ;
	}
	else if( macro_clk_sel == PASCLK_150MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_150MHZ;
	}
	else if( macro_clk_sel == PASCLK_100MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_100MHZ;
	}
	else if( macro_clk_sel == PASCLK_75MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_75MHZ;
	}
	else if( macro_clk_sel == PASCLK_60MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_60MHZ;
	}
	else if( macro_clk_sel == PASCLK_50MHz ) {
		macro_clk_hz = D_IM_PRO_CLK_50MHZ;
	}
	else {
	}
	return macro_clk_hz;
}

ImProCommonFig *im_pro_common_fig_new(void)
{
	ImProCommonFig* self = k_object_new_with_private(IM_TYPE_PRO_COMMON_FIG,sizeof(ImProCommonFigPrivate));
	return self;
}
