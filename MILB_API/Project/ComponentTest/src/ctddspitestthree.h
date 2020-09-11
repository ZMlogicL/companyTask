/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTestthree类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_TESTTHREE_H__
#define __CT_DD_SPI_TESTTHREE_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_TESTTHREE					(ct_dd_spi_testthree_get_type())
#define CT_DD_SPI_TESTTHREE(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiTestthree)) 
#define CT_IS_DD_SPI_TESTTHREE(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_TESTTHREE))

typedef struct 													_CtDdSpiTestthree CtDdSpiTestthree;
typedef struct 													_CtDdSpiTestthreePrivate CtDdSpiTestthreePrivate;

struct _CtDdSpiTestthree
{
	KObject parent;
	CtDdSpiTestthreePrivate *priv;
};

KConstType 				ct_dd_spi_testthree_get_type(void);
CtDdSpiTestthree* 		ct_dd_spi_testthree_new(void);

void 							ct_dd_spi_testthree_set_test(CtDdSpiTestthree *self,CtDdSpiTest *test);
void 							ct_dd_spi_testthree_pc_start_recv_dma_1(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_2(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_3(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_4(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_5(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_6(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_7(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_recv_dma_8(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_1(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_2(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_3(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_4(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_5(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_6(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_7(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_start_full_dma_8(CtDdSpiTestthree *self);
void 							ct_dd_spi_testthree_pc_set_enable_1(CtDdSpiTestthree *self);

#endif /* __CT_DD_SPI_TESTTHREE_H__ */
