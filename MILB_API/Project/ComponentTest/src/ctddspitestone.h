/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTestone类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_TESTONE_H__
#define __CT_DD_SPI_TESTONE_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_TESTONE				(ct_dd_spi_testone_get_type())
#define CT_DD_SPI_TESTONE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiTestone)) 
#define CT_IS_DD_SPI_TESTONE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_TESTONE))

typedef struct 													_CtDdSpiTestone CtDdSpiTestone;
typedef struct 													_CtDdSpiTestonePrivate CtDdSpiTestonePrivate;

struct _CtDdSpiTestone
{
	KObject parent;
	CtDdSpiTestonePrivate *priv;
};

KConstType 			ct_dd_spi_testone_get_type(void);
CtDdSpiTestone* 	ct_dd_spi_testone_new(void);

void 						ct_dd_spi_testone_set_test(CtDdSpiTestone *self,CtDdSpiTest *test);
void 						ct_dd_spi_testone_pc_start_full_1(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_2(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_3(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_4(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_5(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_6(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_7(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_8(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_9(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_10(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_start_full_11(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_stop_1(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_stop_2(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_setget_ss_1(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_setget_ss_2(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_setget_ss_3(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_setget_clkdiv_1(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_handler_1(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_handler_2(CtDdSpiTestone *self);
void 						ct_dd_spi_testone_pc_handler_3(CtDdSpiTestone *self);

#endif /* __CT_DD_SPI_TESTONE_H__ */
