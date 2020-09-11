/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicacccapa.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_ACC_CAPA_H__ 
#define __MXIC_ACC_CAPA_H__ 

#include "mxicutlis.h"

#define MXIC_TYPE_ACC_CAPA    (mxic_acc_capa_get_type())
#define MXIC_ACC_CAPA(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicAccCapa))
#define MXIC_IS_ACC_CAPA(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_ACC_CAPA))


typedef struct _MxicAccCapa MxicAccCapa;
typedef struct _MxicAccCapaPrivate MxicAccCapaPrivate;

struct _MxicAccCapa {
    KObject parent;
};

KConstType  mxic_acc_capa_get_type(void);
MxicAccCapa*     mxic_acc_capa_new(void);

/**
This function set acceptance capability of the specified port.<br> 
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value. <br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPort for a set value. <br>
@param[in]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error
*/
INT32	mxic_acc_capa_set_acceptance_capability( MxicAccCapa *self, ImMxicUnit unit, ImMxicWrArbiter wrArbiter, 
		ImMxicSpecArbiter arbiter, ImMxicPort port, UCHAR capability );

/**
This function set acceptance capability of all ports.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		allCapability			Acceptance capability of all ports.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_acc_capa_set_acceptance_capability_all_port( MxicAccCapa *self, ImMxicUnit unit, 
			const MxicAllAcceptanceCapability* const allCapability );

/**
This function get acceptance capability of all ports.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		allCapability			Acceptance capability of all ports.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_acc_capa_get_acceptance_capability_all_port( MxicAccCapa *self, ImMxicUnit unit, 
			MxicAllAcceptanceCapability* const allCapability );

/**
This function set acceptance capability (gropu) of the specified port.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiterGr for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPortGr for a set value. <br>
@param[in]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_acc_capa_set_acceptance_capability_group( MxicAccCapa *self, ImMxicWrArbiter wrArbiter, 
			ImMxicSpecArbiterGr arbiter, ImMxicPortGr port, UCHAR capability );

/**
This function get acceptance capability (gropu) of the specified port.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiterGr for a set value. <br>
@param[in]		port					Target port.<br>
										Please refer to @ref ImMxicPortGr for a set value. <br>
@param[out]		capability				Acceptance capability. (1~8)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_acc_capa_get_acceptance_capability_group( MxicAccCapa *self, ImMxicWrArbiter wrArbiter, 
			ImMxicSpecArbiterGr arbiter, ImMxicPortGr port, UCHAR* capability );

#endif	// __MXIC_ACC_CAPA_H__