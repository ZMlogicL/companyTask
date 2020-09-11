/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#include <string.h>
#include "imbmh.h"
#include "driver_common.h"
// #if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
// #endif
#include "dd_arm.h"
#include "ddim_user_custom.h"

#include "jmlbmh.h"
#include "imbmh1.h"

K_TYPE_DEFINE_WITH_PRIVATE(ImBmh1, im_bmh1);
#define IM_BMH1_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), ImBmh1Private, IM_TYPE_BMH1))

struct _ImBmh1Private
{
	int a;
};

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/* Nothing Special */
// SLimbus channel_no

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
VOID imBmhMemcpyUlong( ULONG* const dst, ULONG* const src, UINT32 cp_size );
/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
static void im_bmh1_constructor(ImBmh1 *self)
{
	//ImBmh1Private *priv = IM_BMH1_GET_PRIVATE(self);
}

static void im_bmh1_destructor(ImBmh1 *self)
{
	//ImBmh1Private *priv = IM_BMH1_GET_PRIVATE(self);
}

VOID imBmhMemcpyUlong( ULONG* const dst, ULONG* const src, UINT32 cp_size )
{
	UINT32	i;
	ULONG	words;

	words = ( cp_size + sizeof(ULONG) - 1 ) / sizeof(ULONG);

	for ( i = 0; i < words; i++ ){
		dst[i] = src[i];
	}
}

/*----------------------------------------------------------------------*/
/* Global Function														*/
/*----------------------------------------------------------------------*/
/**
BMH Macro interrupt permission set
 */
INT32 Im_BMH_Set_Interrupt( BYTE channel_no, USHORT interrupt_bit, UCHAR permission_flg )
{
	union io_bmh_bmhinte bmhinte;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Interrupt. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( permission_flg > E_IM_BMH_ONOFF_ENABLE ){
		Ddim_Assertion(("I:Im_BMH_Set_Interrupt error. 'permission_flg' value over!! (%d)\n", permission_flg));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhinte.word = 0;

	// SG VD Interrupt
	if(( interrupt_bit & D_IM_BMH_FLG_BMH_AXI_ERR ) != 0 ){
		bmhinte.bit.AXIE = permission_flg;
	}

	// SG HD Interrupt
	if(( interrupt_bit & D_IM_BMH_FLG_BMH_END) != 0 ){
		bmhinte.bit.BMHE = permission_flg;
	}

	IO_BMH[channel_no].BMHINTE.word = bmhinte.word;

	return D_DDIM_OK;
}


/*
BMH CUR set
*/
INT32 Im_BMH_Set_Cur( BYTE channel_no, const T_IM_BMH_CUR_BLOCK* const cur_write_data )
{
	ULONG loop1;
	ULONG loop2;
	ULONG loop_max;
	union io_bmh_bmhmd bmhmd;
	UCHAR write_flg = 0;
	typedef union {
		unsigned long word;
		struct {
			unsigned long	CUR_0	:8;
			unsigned long	CUR_1	:8;
			unsigned long	CUR_2	:8;
			unsigned long	CUR_3	:8;
		} bit;
	} u_bmh_cur;

	u_bmh_cur cur;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Cur. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( cur_write_data == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Cur. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhmd.word = IO_BMH[channel_no].BMHMD.word;
	loop_max = (( bmhmd.bit.LSELCNT % 8 ) == 0 ) ? 8 : ( bmhmd.bit.LSELCNT % 8 );		/* pgr0872 */

	for( loop1 = 0; loop1 < loop_max; loop1++ ){
		for( loop2 = 0; loop2 < 256; loop2 += 4 ){
			cur.word = 0;
			if( cur_write_data->cur_write_flg[loop1][loop2] == 1 ){
				write_flg = 1;
				cur.bit.CUR_0 = cur_write_data->cur_data[loop1][loop2];
			}
			if( cur_write_data->cur_write_flg[loop1][loop2 + 1] == 1 ){
				write_flg = 1;
				cur.bit.CUR_1 = cur_write_data->cur_data[loop1][loop2 + 1];
			}
			if( cur_write_data->cur_write_flg[loop1][loop2 + 2] == 1 ){
				write_flg = 1;
				cur.bit.CUR_2 = cur_write_data->cur_data[loop1][loop2 + 2];
			}
			if( cur_write_data->cur_write_flg[loop1][loop2 + 3] == 1 ){
				write_flg = 1;
				cur.bit.CUR_3 = cur_write_data->cur_data[loop1][loop2 + 3];
			}

			if( write_flg == 1 ){
				IO_BMH[channel_no].CUR.word[loop1][loop2 / 4] = cur.word;
				write_flg = 0;
			}
		}
	}

	for( loop2 = 0; loop2 < 256; loop2 += 4 ){
		cur.word = 0;
		if( cur_write_data->cur_write_flg[8][loop2] == 1 ){
			write_flg = 1;
			cur.bit.CUR_0 = cur_write_data->cur_data[8][loop2];
		}
		if( cur_write_data->cur_write_flg[8][loop2 + 1] == 1 ){
			write_flg = 1;
			cur.bit.CUR_1 = cur_write_data->cur_data[8][loop2 + 1];
		}
		if( cur_write_data->cur_write_flg[8][loop2 + 2] == 1 ){
			write_flg = 1;
			cur.bit.CUR_2 = cur_write_data->cur_data[8][loop2 + 2];
		}
		if( cur_write_data->cur_write_flg[8][loop2 + 3] == 1 ){
			write_flg = 1;
			cur.bit.CUR_3 = cur_write_data->cur_data[8][loop2 + 3];
		}

		if( write_flg == 1 ){
			IO_BMH[channel_no].CUR.word[8][loop2 / 4] = cur.word;
			write_flg = 0;
		}
	}

	return D_DDIM_OK;
}

/*
BMH REF set
*/
INT32 Im_BMH_Set_Ref( BYTE channel_no, const T_IM_BMH_REF_BLOCK* const ref_write_data )
{
	ULONG loop1;
	ULONG loop2;
	ULONG loop_max;
	union io_bmh_bmhmd bmhmd;
	UCHAR write_flg = 0;
	typedef union {
		unsigned long word;
		struct {
			unsigned long	REF_0	:8;
			unsigned long	REF_1	:8;
			unsigned long	REF_2	:8;
			unsigned long	REF_3	:8;
		} bit;
	} u_bmh_ref;

	u_bmh_ref ref;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Ref. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( ref_write_data == NULL ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Set_Ref. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhmd.word = IO_BMH[channel_no].BMHMD.word;
	loop_max = (( bmhmd.bit.LSELCNT % 8 ) == 0 ) ? 8 : ( bmhmd.bit.LSELCNT % 8 );		/* pgr0872 */

	for( loop1 = 0; loop1 < loop_max; loop1++ ){
		for( loop2 = 0; loop2 < 256; loop2 += 4 ){
			ref.word = 0;
			if( ref_write_data->ref_write_flg[loop1][loop2] == 1 ){
				write_flg = 1;
				ref.bit.REF_0 = ref_write_data->ref_data[loop1][loop2];
			}
			if( ref_write_data->ref_write_flg[loop1][loop2 + 1] == 1 ){
				write_flg = 1;
				ref.bit.REF_1 = ref_write_data->ref_data[loop1][loop2 + 1];
			}
			if( ref_write_data->ref_write_flg[loop1][loop2 + 2] == 1 ){
				write_flg = 1;
				ref.bit.REF_2 = ref_write_data->ref_data[loop1][loop2 + 2];
			}
			if( ref_write_data->ref_write_flg[loop1][loop2 + 3] == 1 ){
				write_flg = 1;
				ref.bit.REF_3 = ref_write_data->ref_data[loop1][loop2 + 3];
			}

			if( write_flg == 1 ){
				IO_BMH[channel_no].REF.word[loop1][loop2 / 4] = ref.word;
				write_flg = 0;
			}
		}
	}

	for( loop2 = 0; loop2 < 256; loop2 += 4 ){
		ref.word = 0;
		if( ref_write_data->ref_write_flg[8][loop2] == 1 ){
			write_flg = 1;
			ref.bit.REF_0 = ref_write_data->ref_data[8][loop2];
		}
		if( ref_write_data->ref_write_flg[8][loop2 + 1] == 1 ){
			write_flg = 1;
			ref.bit.REF_1 = ref_write_data->ref_data[8][loop2 + 1];
		}
		if( ref_write_data->ref_write_flg[8][loop2 + 2] == 1 ){
			write_flg = 1;
			ref.bit.REF_2 = ref_write_data->ref_data[8][loop2 + 2];
		}
		if( ref_write_data->ref_write_flg[8][loop2 + 3] == 1 ){
			write_flg = 1;
			ref.bit.REF_3 = ref_write_data->ref_data[8][loop2 + 3];
		}

		if( write_flg == 1 ){
			IO_BMH[channel_no].REF.word[8][loop2 / 4] = ref.word;
			write_flg = 0;
		}
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=000b)
*/
INT32 Im_BMH_Get_Sadr_000( BYTE channel_no, T_IM_BMH_SADR_000* const sadr_read_data )
{
	ULONG loop1;
	ULONG loop2;
	ULONG count = 0;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_000. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_000. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop1 = 0; loop1 < 2; loop1++ ){
		count = 0;
		for( loop2 = 0; loop2 < 57; loop2++ ){
			sadr_read_data->sadcmp[loop1][count] = sadr.bit000[loop1][loop2].SADcmp_0;
			sadr_read_data->pos[loop1][count]    = sadr.bit000[loop1][loop2].POS_0;
			count++;
			sadr_read_data->sadcmp[loop1][count] = sadr.bit000[loop1][loop2].SADcmp_1;
			sadr_read_data->pos[loop1][count]    = sadr.bit000[loop1][loop2].POS_1;
			count++;
			sadr_read_data->sadcmp[loop1][count] = sadr.bit000[loop1][loop2].SADcmp_2;
			sadr_read_data->pos[loop1][count]    = sadr.bit000[loop1][loop2].POS_2;
			count++;
			sadr_read_data->sadcmp[loop1][count] = sadr.bit000[loop1][loop2].SADcmp_3;
			sadr_read_data->pos[loop1][count]    = sadr.bit000[loop1][loop2].POS_3;
			count++;
		}
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=001b)
*/
INT32 Im_BMH_Get_Sadr_001( BYTE channel_no, T_IM_BMH_SADR_001* const sadr_read_data )
{
	ULONG loop;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_001. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_001. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop = 0; loop < 225; loop++ ){
			sadr_read_data->sadcmp[loop] = sadr.bit001[loop].SADcmp;
			sadr_read_data->pos[loop]    = sadr.bit001[loop].POS;
			sadr_read_data->sadmin[loop] = sadr.bit001[loop].SADmin;
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=010b)
*/
INT32 Im_BMH_Get_Sadr_010( BYTE channel_no, T_IM_BMH_SADR_010* const sadr_read_data )
{
	ULONG loop1;
	ULONG loop2;
	ULONG count = 0;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_010. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_010. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop1 = 0; loop1 < 2; loop1++ ){
		count = 0;
		for( loop2 = 0; loop2 < 113; loop2++ ){
			sadr_read_data->sadcmp[loop1][count]       = sadr.bit010[loop1][loop2].SADcmp_0;
			sadr_read_data->pos_integer[loop1][count]  = sadr.bit010[loop1][loop2].POS_Integer_0;
			sadr_read_data->pos_fraction[loop1][count] = sadr.bit010[loop1][loop2].POS_fraction_0;
			count++;
			sadr_read_data->sadcmp[loop1][count]       = sadr.bit010[loop1][loop2].SADcmp_1;
			sadr_read_data->pos_integer[loop1][count]  = sadr.bit010[loop1][loop2].POS_Integer_1;
			sadr_read_data->pos_fraction[loop1][count] = sadr.bit010[loop1][loop2].POS_fraction_1;
			count++;
		}
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=011b)
*/
INT32 Im_BMH_Get_Sadr_011( BYTE channel_no, T_IM_BMH_SADR_011* const sadr_read_data )
{
	ULONG loop;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_011. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_011. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop = 0; loop < 225; loop++ ){
			sadr_read_data->sadcmp[loop]       = sadr.bit011[loop].SADcmp;
			sadr_read_data->pos_integer[loop]  = sadr.bit011[loop].POS_Integer;
			sadr_read_data->pos_fraction[loop] = sadr.bit011[loop].POS_fraction;
			sadr_read_data->sadmin[loop]       = sadr.bit011[loop].SADmin;
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=100b)
*/
INT32 Im_BMH_Get_Sadr_100( BYTE channel_no, T_IM_BMH_SADR_100* const sadr_read_data )
{
	ULONG loop1;
	ULONG loop2;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_100. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_100. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop1 = 0; loop1 < 2; loop1++ ){
		for( loop2 = 0; loop2 < 112; loop2++ ){
			sadr_read_data->sadcmp[loop1][loop2]       = sadr.bit100[loop1][loop2].SADcmp;
			sadr_read_data->pos_integer[loop1][loop2]  = sadr.bit100[loop1][loop2].POS_Integer;
			sadr_read_data->pos_fraction[loop1][loop2] = sadr.bit100[loop1][loop2].POS_fraction;
			sadr_read_data->sadmin[loop1][loop2]       = sadr.bit100[loop1][loop2].SADmin;
		}
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=101b)
*/
INT32 Im_BMH_Get_Sadr_101( BYTE channel_no, T_IM_BMH_SADR_101* const sadr_read_data )
{
	ULONG loop1;
	ULONG loop2;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_101. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_101. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop1 = 0; loop1 < 2; loop1++ ){
		for( loop2 = 0; loop2 < 56; loop2++ ){
			sadr_read_data->sadcmp[loop1][loop2]       = sadr.bit101[loop1][loop2].SADcmp;
			sadr_read_data->pos_integer[loop1][loop2]  = sadr.bit101[loop1][loop2].POS_Integer;
			sadr_read_data->pos_fraction[loop1][loop2] = sadr.bit101[loop1][loop2].POS_fraction;
			sadr_read_data->sadmin[loop1][loop2]       = sadr.bit101[loop1][loop2].SADmin;

			sadr_read_data->weight[loop1][loop2]       = sadr.bit101[loop1][loop2].Weight;
			sadr_read_data->deviation[loop1][loop2]    = sadr.bit101[loop1][loop2].Deviation;
			sadr_read_data->cur_max[loop1][loop2]      = sadr.bit101[loop1][loop2].CUR_MAX;
			sadr_read_data->cur_min[loop1][loop2]      = sadr.bit101[loop1][loop2].CUR_MIN;
		}
	}

	return D_DDIM_OK;
}

/*
BMH SADR get (BMHMD.OUTMD=110b)
*/
INT32 Im_BMH_Get_Sadr_110( BYTE channel_no, T_IM_BMH_SADR_110* const sadr_read_data )
{
	ULONG loop1;
	ULONG loop2;
	union io_bmh_sadr sadr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_110. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sadr_read_data == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Sadr_110. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	imBmhMemcpyUlong( (ULONG*)&sadr.word, (ULONG*)&IO_BMH[channel_no].SADR.word, sizeof(sadr) );

	for( loop1 = 0; loop1 < 2; loop1++ ){
		for( loop2 = 0; loop2 < 28; loop2++ ){
			sadr_read_data->sadcmp[loop1][loop2]        = sadr.bit110[loop1][loop2].SADcmp;
			sadr_read_data->pos[loop1][loop2]           = sadr.bit110[loop1][loop2].POS;
			sadr_read_data->sadmin[loop1][loop2]        = sadr.bit110[loop1][loop2].SADmin;

			sadr_read_data->sadmin1before[loop1][loop2] = sadr.bit110[loop1][loop2].SADmin1before;
			sadr_read_data->sadmin1after[loop1][loop2]  = sadr.bit110[loop1][loop2].SADmin1after;
			sadr_read_data->sadmin2before[loop1][loop2] = sadr.bit110[loop1][loop2].SADmin2before;
			sadr_read_data->sadmin2after[loop1][loop2]  = sadr.bit110[loop1][loop2].SADmin2after;

			sadr_read_data->weight[loop1][loop2]        = sadr.bit110[loop1][loop2].Weight;
			sadr_read_data->deviation[loop1][loop2]     = sadr.bit110[loop1][loop2].Deviation;
			sadr_read_data->cur_max[loop1][loop2]       = sadr.bit110[loop1][loop2].CUR_MAX;
			sadr_read_data->cur_min[loop1][loop2]       = sadr.bit110[loop1][loop2].CUR_MIN;
		}
	}

	return D_DDIM_OK;
}

/*
Get BMH Dma mode control
*/
INT32 Im_BMH_Get_Ctrl_Dma( BYTE channel_no, T_IM_BMH_CTRL_DMA* const bmh_ctrl_dma )
{
	union io_bmh_bmhdma    bmhdma;
	union io_bmh_bmhghsize bmhghsize;
	union io_bmh_bmhhsize  bmhhsize;
	union io_bmh_bmhvsize  bmhvsize;
	union io_bmh_bmhcurad  bmhcurad;
	union io_bmh_bmhrefad  bmhrefad;
	union io_bmh_bmhsadad  bmhsadad;
	union io_bmh_bmhsadgh  bmhsadgh;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Ctrl_Dma. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( bmh_ctrl_dma == NULL ){
		// bmh_ctrl_dma setting error
		Ddim_Assertion(("I:Im_BMH_Get_Ctrl_Dma. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhdma.word    = IO_BMH[channel_no].BMHDMA.word;
	bmhghsize.word = IO_BMH[channel_no].BMHGHSIZE.word;
	bmhhsize.word  = IO_BMH[channel_no].BMHHSIZE.word;
	bmhvsize.word  = IO_BMH[channel_no].BMHVSIZE.word;
	bmhcurad.word  = IO_BMH[channel_no].BMHCURAD.word;
	bmhrefad.word  = IO_BMH[channel_no].BMHREFAD.word;
	bmhsadad.word  = IO_BMH[channel_no].BMHSADAD.word;
	bmhsadgh.word  = IO_BMH[channel_no].BMHSADGH.word;

	bmh_ctrl_dma->dmamd      = bmhdma.bit.DMAMD;				/* pgr0872 */
	bmh_ctrl_dma->ghsize_cur = bmhghsize.bit.GHSIZE_CUR;		/* pgr0872 */
	bmh_ctrl_dma->ghsize_ref = bmhghsize.bit.GHSIZE_REF;		/* pgr0872 */
	bmh_ctrl_dma->hsize_ref  = bmhhsize.bit.HSIZE_REF;			/* pgr0872 */
	bmh_ctrl_dma->vsize_ref  = bmhvsize.bit.VSIZE_REF;			/* pgr0872 */
	bmh_ctrl_dma->curstad    = bmhcurad.bit.CURSTAD;			/* pgr0872 */
	bmh_ctrl_dma->refstad    = bmhrefad.bit.REFSTAD;			/* pgr0872 */
	bmh_ctrl_dma->sadstad    = bmhsadad.bit.SADSTAD;			/* pgr0872 */
	bmh_ctrl_dma->sadghsize  = bmhsadgh.bit.SADGHSIZE;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
Get BMH BMHSAD_WR
*/
INT32 Im_BMH_Get_Bmhsad_wr( BYTE channel_no, T_IM_BMH_BMHSAD_WR* const sad_wr )
{
	union io_bmh_bmhsad_wr bmhsad_wr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhsad_wr. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sad_wr == NULL ){
		// sad_wr setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhsad_wr. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhsad_wr.word = IO_BMH[channel_no].BMHSAD_WR.word;

	sad_wr->sad_wr = bmhsad_wr.bit.SAD_WR;			/* pgr0872 */

	return D_DDIM_OK;
}


/*
Get BMH BMHHCNT
*/
INT32 Im_BMH_Get_Bmhhcnt( BYTE channel_no, T_IM_BMH_BMHHCNT* const cnt )
{
	union io_bmh_bmhhcnt bmhhcnt;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhhcnt. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( cnt == NULL ){
		// cnt setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhhcnt. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhhcnt.word = IO_BMH[channel_no].BMHHCNT.word;

	cnt->hcnt = bmhhcnt.bit.HCNT;			/* pgr0872 */
	cnt->rcnt = bmhhcnt.bit.RCNT;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
Get AXI bus I/F Status
*/
INT32 Im_BMH_Get_Bmhaxierr( BYTE channel_no, T_IM_BMH_AXI_STATUS* const sts )
{
	union io_bmh_bmhaxierr bmhaxierr;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhaxierr. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( sts == NULL ){
		// sts setting error
		Ddim_Assertion(("I:Im_BMH_Get_Bmhaxierr. Parameter is NULL.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	bmhaxierr.word = IO_BMH[channel_no].BMHAXIERR.word;

	sts->write_channel_response = bmhaxierr.bit.WRESP;			/* pgr0872 */
	sts->read_channel_response  = bmhaxierr.bit.RRESP;			/* pgr0872 */

	return D_DDIM_OK;
}

/*
The semaphore of BMH is acquired
*/
INT32 Im_BMH_Open( BYTE channel_no, const INT32 tmout )
{
	DDIM_USER_ID sid;
	DDIM_USER_ER ercd;

#ifdef CO_PARAM_CHECK
	if( channel_no >= ImBmh1_E_IM_BMH_CHANNEL_END ){
		// Parameter setting error
		Ddim_Assertion(("I:Im_BMH_Open. channel_no is abnormal.\n"));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
	if( tmout < D_DDIM_USER_SEM_WAIT_FEVR ){
		Ddim_Assertion(("I:Im_BMH_Open. input param error. tmout = %x\n", tmout ));
		return D_IM_BMH_INPUT_PARAMETER_ERROR;
	}
#endif	// CO_PARAM_CHECK

	sid = SID_IM_BMH( channel_no );
	if( tmout == D_DDIM_USER_SEM_WAIT_POL ){
		ercd = DDIM_User_Pol_Sem( sid );				// pol_sem()
	}
	else{
		ercd = DDIM_User_Twai_Sem( sid, (DDIM_USER_TMO)tmout );	// twai_sem()
	}

	if( ercd == D_DDIM_USER_E_TMOUT ){
		// A semaphore acquisition processing time out
		Ddim_Print(("I:Im_BMH_Open() Error : Semaphore Get Time Out\n"));
		return D_IM_BMH_SEM_TIMEOUT_ERR;
	}

	if( ercd != D_DDIM_USER_E_OK ){
		// BMH processing error
		Ddim_Print(("I:Im_BMH_Open() Error : Semaphore Get Error\n"));
		return D_IM_BMH_SEM_NG;
	}

	return D_DDIM_OK;
}

ImBmh1 *im_bmh1_get()
{
	static ImBmh1 *imBmh1 = NULL;
	if(!imBmh1)
	{
		imBmh1 = k_object_new_with_private(IM_TYPE_BMH1,sizeof(ImBmh1Private));
	}
	return imBmh1;
}
