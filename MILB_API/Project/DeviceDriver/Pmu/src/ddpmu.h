/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */

#ifndef _DD_PMU_H_
#define _DD_PMU_H_


#include "klib.h"
#include "pmc.h"
#include "dd_arm.h"


#define DD_TYPE_PMU				(dd_pmu_get_type())
#define DD_PMU(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdPmu))
#define DD_IS_PMU(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_PMU))

#define	DdPmu_INPUT_PARAM_ERR	(D_DD_PMU | D_DDIM_INPUT_PARAM_ERROR)	/**< Input Parameter Error */

/** Power Domain ID */
typedef enum {
	DdPmu_PD_TYPE_HEVC_PROC0		= 0,						/**< HEVC processor0 */
	DdPmu_PD_TYPE_RESERVED,									/**< Reserved */
	DdPmu_PD_TYPE_HEVC_ENCODE,								/**< HEVC encoder */
	DdPmu_PD_TYPE_HEVC_DECODE,								/**< HEVC decoder */
	DdPmu_PD_TYPE_H264,										/**< H264 */
	DdPmu_PD_TYPE_IMAGE_PIPE0,								/**< Imaging pipe0 */
	DdPmu_PD_TYPE_IMAGE_PIPE1,								/**< Imaging pipe1 */
	DdPmu_PD_TYPE_MAX										/**< Maximum value. */
} DdPmuPdType;


typedef struct _DdPmu 			DdPmu;
typedef struct _DdPmuPrivate 	DdPmuPrivate;

struct  _DdPmu {
	KObject parent;
};


KConstType 	dd_pmu_get_type(void);
DdPmu* 		dd_pmu_get(void);

/**
Power Management Controller .<br>
Get status of PMU PD.
@param [in]		pdType				: PD type @ref DdPmuPdType
@param [out]	value				: Status value
@retval	D_DDIM_OK					: Normal end
@retval	DdPmu_INPUT_PARAM_ERR	: Input Parameter Error
*/
INT32 		dd_pmu_get_status(DdPmu *self, DdPmuPdType pdType, ULONG* value);

/**
Power Management Controller .<br>
Power Domain off.
@param [in]		pdType				: PD type @ref DdPmuPdType
@retval	D_DDIM_OK					: Normal end
@retval	DdPmu_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 		dd_pmu_pd_off(DdPmu *self, DdPmuPdType pdType);

/**
Power Management Controller .<br>
Power Domain on.
@param [in]		pdType				: PD type @ref DdPmuPdType
@retval	D_DDIM_OK					: Normal end
@retval	DdPmu_INPUT_PARAM_ERR	: Input Parameter Error
@remarks	This API uses DDIM_User_Dly_Tsk().
*/
INT32 		dd_pmu_pd_on(DdPmu *self, DdPmuPdType pdType);


#endif	// _DD_PMU_H_
