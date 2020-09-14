/*
 *
 *@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
 *@date : 2020-09-04
 *@author : 王顺
 *@brief : DdPcieRcCommon
 *@rely : klib.h
 *@function : 按ETK规范抄写索喜源代码
 *@version : 1.0.0 能正常上屏显示图像
 *
 */
/**
 * @file		dd_mcc.h
 * @brief		MCC (Multi-Core Condition) driver
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */

/**
@addtogroup dd_mcc
@{
	- @ref dd_mcc_sample_section1
*/

#ifndef _DD_MCC_H_
#define _DD_MCC_H_


#include "arm.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

#define DD_MCC_GET_CA70_WFI()		(1 & ioMcc.mcswfi.word)					/**< Get CA70 SWFI status */
#define DD_MCC_GET_CA71_WFI()		(1 & (ioMcc.mcswfi.word >> 1))		/**< Get CA71 SWFI status */
#define DD_MCC_GET_CA72_WFI()		(1 & (ioMcc.mcswfi.word >> 2))		/**< Get CA72 SWFI status */
#define DD_MCC_GET_CA73_WFI()		(1 & (ioMcc.mcswfi.word >> 3))		/**< Get CA73 SWFI status */
#define DD_MCC_GET_CA70_WFE()		(1 & (ioMcc.mcswfi.word >> 4))		/**< Get CA70 SWFE status */
#define DD_MCC_GET_CA71_WFE()		(1 & (ioMcc.mcswfi.word >> 5))		/**< Get CA71 SWFE status */
#define DD_MCC_GET_CA72_WFE()		(1 & (ioMcc.mcswfi.word >> 6))		/**< Get CA72 SWFE status */
#define DD_MCC_GET_CA73_WFE()		(1 & (ioMcc.mcswfi.word >> 7))		/**< Get CA73 SWFE status */

/*@}*/

/**
@weakgroup dd_mcc
@{
	@section dd_mcc_sample_section1		Sample of "WSFI status of CPU CORE is read" using Dd_MCC_Get_CA70_WFI function.
    @code
	if( 0 == Dd_MCC_Get_CA70_WFI() ) {
		// Processing which is not in a WFI state
		// TODO
	}
	else {
		// Processing of a WFI state
		// TODO
	}
    @endcode
@}*/

#ifdef __cplusplus
}
#endif

#endif	// _DD_MCC_H_
