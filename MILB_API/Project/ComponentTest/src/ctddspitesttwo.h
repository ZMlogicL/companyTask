/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTesttwo类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_TESTTWO_H__
#define __CT_DD_SPI_TESTTWO_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_TESTTWO				(ct_dd_spi_testtwo_get_type())
#define CT_DD_SPI_TESTTWO(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiTesttwo)) 
#define CT_IS_DD_SPI_TESTTWO(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_TESTTWO))

typedef struct 													_CtDdSpiTesttwo CtDdSpiTesttwo;
typedef struct 													_CtDdSpiTesttwoPrivate CtDdSpiTesttwoPrivate;

struct _CtDdSpiTesttwo
{
	KObject parent;
	CtDdSpiTesttwoPrivate *priv;
};

KConstType 				ct_dd_spi_testtwo_get_type(void);
CtDdSpiTesttwo* 		ct_dd_spi_testtwo_new(void);

void 							ct_dd_spi_testtwo_set_test(CtDdSpiTesttwo *self,CtDdSpiTest *test);
void 							ct_dd_spi_testtwo_pc_handler_8(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_9(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_10(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_11(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_calc_1(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_calc_2(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_calc_3(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_calc_4(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_1(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_2(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_3(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_4(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_5(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_6(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_7(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_start_send_dma_8(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_7(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_6(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_5(CtDdSpiTesttwo *self);
void 							ct_dd_spi_testtwo_pc_handler_4(CtDdSpiTesttwo *self);

#endif /* __CT_DD_SPI_TESTTWO_H__ */
