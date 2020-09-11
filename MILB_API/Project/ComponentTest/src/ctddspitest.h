/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :guguangjian
*@brief               :CtDdSpiTest类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_TEST_H__
#define __CT_DD_SPI_TEST_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_TEST					(ct_dd_spi_test_get_type())
#define CT_DD_SPI_TEST(obj)						(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiTest))
#define CT_IS_DD_SPI_TEST(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_TEST)) 

typedef struct 												_CtDdSpiTest CtDdSpiTest;
typedef struct 												_CtDdSpiTestPrivate CtDdSpiTestPrivate;

struct _CtDdSpiTest
{
	KObject parent;
	kuint32 gctDdSpiTransNum;
	E_DD_SPI_BIT_LEN gctDdSpiBitLen;
	kint32 gctDdSpiResult;
	kuchar gctDdSpiAsync;
};

KConstType 		ct_dd_spi_test_get_type(void);
CtDdSpiTest* 		ct_dd_spi_test_new(void);

void 					ct_dd_spi_test_cmd_wrap( kchar* cmd );
void 					ct_dd_spi_test_set_result(CtDdSpiTest *self,kint32 newResult);
kuchar 				ct_dd_spi_test_get_async(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_set_send_data_1(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_set_send_data_2(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_set_recv_data_1(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_set_recv_data_2(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_1(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_2(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_3(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_4(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_5(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_6(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_7(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_8(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_send_9(CtDdSpiTest *self);
void 					ct_dd_spi_test_pc_start_recv_1(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_2(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_3(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_4(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_5(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_6(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_7(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_8(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_9(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_10(CtDdSpiTest * self);
void 					ct_dd_spi_test_pc_start_recv_11(CtDdSpiTest * self);

#endif /* __CT_DD_SPI_TEST_H__ */
