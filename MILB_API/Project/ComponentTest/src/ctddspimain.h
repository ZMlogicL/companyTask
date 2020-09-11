/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-03
*@author              :guguangjian
*@brief               :CtDdSpiMain类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_SPI_MAIN_H__
#define __CT_DD_SPI_MAIN_H__

#include <klib.h>

#define CT_TYPE_DD_SPI_MAIN					(ct_dd_spi_main_get_type())
#define CT_DD_SPI_MAIN(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdSpiMain)) 
#define CT_IS_DD_SPI_MAIN(obj)				(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_SPI_MAIN))

typedef struct 												_CtDdSpiMain CtDdSpiMain;
typedef struct 												_CtDdSpiMainPrivate CtDdSpiMainPrivate;

struct _CtDdSpiMain
{
	KObject parent;
};

KConstType 			ct_dd_spi_main_get_type(void);
CtDdSpiMain* 		ct_dd_spi_main_new(void);

void 						ct_dd_spi_main( CtDdSpiMain *self,kint argc, kchar** argv);
kuchar *					ct_dd_spi_return_sendbuf8(void);
void 						ct_dd_spi_set_sendbuf8(kuchar ch, kint index);
kushort*					ct_dd_spi_return_sendbuf16(void);
void 						ct_dd_spi_set_sendbuf16(kushort ch, kint index);
kuint32* 					ct_dd_spi_return_sendbuf32(void);
kuchar *					ct_dd_spi_return_recvbuf8(void);
kushort *					ct_dd_spi_return_recvbuf16(void);
kuint32 *					ct_dd_spi_return_recvbuf32(void);

#endif /* __CT_DD_SPI_MAIN_H__ */
