/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :liudong
*@brief               :CtImB2r1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_B2R1_H_
#define __CT_IM_B2R1_H_

#include <klib.h>

#define CT_TYPE_IM_B2R1					(ct_im_b2r1_get_type())
#define CT_IM_B2R1(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtImB2r1)) 
#define CT_IS_IM_B2R1(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_B2R1)) 

typedef struct 			_CtImB2r1 CtImB2r1;
typedef struct 			_CtImB2r1Private CtImB2r1Private;

struct _CtImB2r1
{
	KObject parent;
	UCHAR pipeNo;

};

//私有变公有变量
extern T_IM_B2R_CTRL gctImB2rCtrlBase;
extern T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInBase;
extern T_IM_B2R_CTRL gctImB2rCtrlRaw;
extern T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw16bit;
extern T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw12bit;
extern T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw10bit;
extern T_IM_B2R_CTRL_SDRAM_INPUT gctImB2rCtrlSdramInRaw8bit;
extern T_IM_B2R_RECT gctImB2rRectParamOutRgbP12;
extern T_IM_B2R_RECT gctImB2rRectParamOutRgbU8;
extern T_IM_B2R_INADDR_INFO gctImB2rInAddrRaw;
extern T_IM_B2R_OUTBANK_INFO gctImB2rOutAddrRgb;

extern const UCHAR gctImB2rKneeTbl[D_IM_B2R_TABLE_MAX_RGB_KNEE];

//本身就是全局变量
extern T_IM_B2R_CTRL_B2B_DIRECT gctImB2rCtrlB2bDirect;



KConstType 		ct_im_b2r1_get_type(void);
CtImB2r1* 		ct_im_b2r1_new(void);

//私有变公有
void 			ct_im_b2r1_handler_cb( kuint32* result, kuint32 user_param );
void 			ct_im_b2r1_set_b2b( E_IM_PRO_UNIT_NUM unit_no );
void 			ct_im_b2r1_start_b2b( E_IM_PRO_UNIT_NUM unit_no );
void 			ct_im_b2r1_waitend_stop_b2b( E_IM_PRO_UNIT_NUM unit_no );
void 			ct_im_b2r1_set_wb_gain( CtImB2r1* self );
void 			ct_im_b2r1_print_b2r_common_reg( void );
void 			ct_im_b2r1_print_b2r_ybr_reg( void );
void 			ct_im_b2r1_print_b2r_ybw_reg( void );
void 			ct_im_b2r1_print_b2r_ctrl_reg( void );
void 			ct_im_b2r1_print_b2r_ctrl_modesdraminput_reg( void );
void 			ct_im_b2r1_print_b2r_ctrl_modeb2bdirect_reg( void );
void 			ct_im_b2r1_print_rect_reg( void );
void 			ct_im_b2r1_print_trimming_reg( void );
void 			ct_im_b2r1_print_other_reg( void );
void 			ct_im_b2r1_print_fb2r_ctrl_reg( void );
void 			ct_im_b2r1_print_axi_reg( void );

void 			ct_im_b2r1_printreg( void );

#endif /* __CT_IM_B2R1_H_ */
