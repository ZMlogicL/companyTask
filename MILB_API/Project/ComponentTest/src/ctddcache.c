/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-05
*@author              :jianghaodong
*@brief               :CtDdCache类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "dd_cache.h"

#include "ctddcache.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdCache, ct_dd_cache);
#define CT_DD_CACHE_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdCachePrivate,CT_TYPE_DD_CACHE))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Test Memory map.
// Please setting of mmu before test.
//
//   0x6500_0000 +-------------+-------------+
//               | INNER_NC    | OUTER_NC    |
//   0x6510_0000 +-------------+-------------+
//               | INNER_WB_WA | OUTER_NC    |
//   0x6520_0000 +-------------+-------------+
//               | INNER_NC    | OUTER_NC    |
//   0x6530_0000 +-------------+-------------+
//               | INNER_WB_WA | OUTER_NC    |
//   0x6540_0000 +-------------+-------------+
//
#define CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR		(0x65000000)	// NONCache Test Top Address
#define CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR		(0x65100000)	// L1Cache Test Top Address
#define CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR		(0x65200000)	// L2Cache Test Top Address
#define CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR		(0x65300000)	// L1L2Cache Test Top Address
#define CtDdCache_D_CT_DD_CACHE_SIZE						(0x00010000)	// Cache Test Size


struct _CtDdCachePrivate
{
};

/*
*DECLS
*/
static void cacheAreaWriteData(kuint32 startAddr, kuint32 writeData);
static void cacheAreaWrite(kuint32 writeData);
static void cacheAreaMemcmp(void);
static void cacheAreaInit(void);


/*
*IMPL
*/
static void ct_dd_cache_constructor(CtDdCache *self) 
{
}

static void ct_dd_cache_destructor(CtDdCache *self) 
{
}

/*----------------------------------------------------------------------*/
/* Local Method Definition												*/
/*----------------------------------------------------------------------*/
static void cacheAreaWriteData(kuint32 startAddr, kuint32 writeData)
{
	kuint32 writeAddress;

	writeAddress = startAddr;
	while(writeAddress < (startAddr + CtDdCache_D_CT_DD_CACHE_SIZE)) {
		memset((void*)writeAddress, writeData, 4);
		writeAddress += 4;
	}
}

static void cacheAreaWrite(kuint32 writeData)
{
	cacheAreaWriteData(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, writeData);
	cacheAreaWriteData(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR, writeData);
	cacheAreaWriteData(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR, writeData);
	cacheAreaWriteData(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR, writeData);
}

static void cacheAreaMemcmp(void)
{
	Ddim_Print(("NONCACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L1CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L2CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L1L2CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
}

static void cacheAreaInit(void)
{
	Ddim_Print(("Cache area initialize start\n"));
	memset((void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, 0x00, CtDdCache_D_CT_DD_CACHE_SIZE);
	memset((void*)CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR, 0x00, CtDdCache_D_CT_DD_CACHE_SIZE);
	memset((void*)CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR, 0x00, CtDdCache_D_CT_DD_CACHE_SIZE);
	memset((void*)CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR, 0x00, CtDdCache_D_CT_DD_CACHE_SIZE);
	Dd_CACHE_L1_Clean_Flush_Dcache_All();
	Dd_CACHE_L2_Clean_Flush_Dcache_All();
	Ddim_Print(("NONCACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L1CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L2CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("L1L2CACHE Result = %d\n", memcmp((void*)CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
			(void*)CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR, CtDdCache_D_CT_DD_CACHE_SIZE)));
	Ddim_Print(("Cache area initialize end\n"));
}

/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for CACHE test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 *			The meaning of parameters
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| P1              | P2   | P3   |Meaning                                                    |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1all_f         |      |      |L1 Cache Flush All Test.                                   |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1all_c         |      |      |L1 Cache Clean All Test.                                   |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1all_cf        |      |      |L1 Cache Clean & Flush All Test.                           |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2all_f         |      |      |L2 Cache Flush All Test.                                   |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2all_c         |      |      |L2 Cache Clean All Test.                                   |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2all_cf        |      |      |L2 Cache Clean & Flush All Test.                           |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2all_f       |      |      |L1L2 Cache Flush All Test.                                 |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2all_c       |      |      |L1L2 Cache Clean All Test.                                 |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2all_cf      |      |      |L1L2 Cache Clean & Flush All Test.                         |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1addr_f        |      |      |L1 Cache Flush Address/Size Test.                          |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1addr_c        |      |      |L1 Cache Clean Address/Size Test.                          |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1addr_cf       |      |      |L1 Cache Clean & Flush Address/Size Test.                  |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2addr_f        |      |      |L2 Cache Flush Address/Size Test.                          |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2addr_c        |      |      |L2 Cache Clean Address/Size Test.                          |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l2addr_cf       |      |      |L2 Cache Clean & Flush Address/Size Test.                  |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2addr_f      |      |      |L1L2 Cache Flush Address/Size Test.                        |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2addr_c      |      |      |L1L2 Cache Clean Address/Size Test.                        |
 *		+-----------------+------+------+-----------------------------------------------------------+
 *		| l1l2addr_cf     |      |      |L1L2 Cache Clean & Flush Address/Size Test.                |
 *		+-----------------+------+------+-----------------------------------------------------------+
 */
void ct_dd_cache_main_main(CtDdCache* self, kint argc, kchar** argv)
{
	if( argc < 2 ) {
		Ddim_Print(("please check 1st parameter!!\n"));
	}
	else if( 0 == strcmp( argv[1], "l1all_f" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x11111111);
		Dd_CACHE_L1_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1all_c" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x22222222);
		Dd_CACHE_L1_Clean_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1all_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x33333333);
		Dd_CACHE_L1_Clean_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2all_f" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x44444444);
		Dd_CACHE_L2_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2all_c" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Clean_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x55555555);
		Dd_CACHE_L2_Clean_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Clean_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2all_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Clean_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x66666666);
		Dd_CACHE_L2_Clean_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Clean_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2all_f" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_All / Dd_CACHE_L2_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x77777777);
		Dd_CACHE_L1_Flush_Dcache_All();
		Dd_CACHE_L2_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_All / Dd_CACHE_L2_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2all_c" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_All / Dd_CACHE_L2_Clean_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x88888888);
		Dd_CACHE_L1_Clean_Dcache_All();
		Dd_CACHE_L2_Clean_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_All / Dd_CACHE_L2_Clean_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2all_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_All / Dd_CACHE_L2_Clean_Flush_Dcache_All start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x99999999);
		Dd_CACHE_L1_Clean_Flush_Dcache_All();
		Dd_CACHE_L2_Clean_Flush_Dcache_All();
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_All / Dd_CACHE_L2_Clean_Flush_Dcache_All end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1addr_f" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xAAAAAAAA);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1addr_c" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xBBBBBBBB);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1addr_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xCCCCCCCC);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2addr_f" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xDDDDDDDD);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Flush_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2addr_c" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Clean_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xEEEEEEEE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Clean_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l2addr_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L2_Clean_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0xFFFFFFFF);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L2_Clean_Flush_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2addr_f" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_Addr / Dd_CACHE_L2_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x1F1F1F1F);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Flush_Dcache_Addr / Dd_CACHE_L2_Flush_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2addr_c" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_Addr / Dd_CACHE_L2_Clean_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x2F2F2F2F);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Dcache_Addr / Dd_CACHE_L2_Clean_Dcache_Addr end\n"));
	}
	else if( 0 == strcmp( argv[1], "l1l2addr_cf" ) ) {
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_Addr / Dd_CACHE_L2_Clean_Flush_Dcache_Addr start\n"));
		cacheAreaInit();
		cacheAreaWrite(0x3F3F3F3F);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_NONCACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L1_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		Dd_CACHE_L2_Clean_Flush_Dcache_Addr(CtDdCache_D_CT_DD_CACHE_L1L2CACHE_START_ADDR,
				CtDdCache_D_CT_DD_CACHE_SIZE);
		cacheAreaMemcmp();
		Ddim_Print(("Dd_CACHE_L1_Clean_Flush_Dcache_Addr / Dd_CACHE_L2_Clean_Flush_Dcache_Addr end\n"));
	}
	else
	{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdCache* ct_dd_cache_new(void) 
{
    CtDdCache *self = k_object_new_with_private(CT_TYPE_DD_CACHE, sizeof(CtDdCachePrivate));
    return self;
}
