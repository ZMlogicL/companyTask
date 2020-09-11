/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :徐廷军
*@brief               :sns 索喜rtos
*@redd                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __DD_RELC_COMMON_H__
#define __DD_RELC_COMMON_H__


#include <klib.h>
#include "driver_common.h"
#include "ddimtypedef.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DD_TYPE_RELC_COMMON				(dd_relc_common_get_type())
#define DD_RELC_COMMON(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdRelcCommon))
#define DD_IS_RELC_COMMON(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_RELC_COMMON))


typedef struct _DdRelcCommon 					DdRelcCommon;
typedef struct _DdRelcCommonPrivate 	DdRelcCommonPrivate;


struct _DdRelcCommon
{
	KObject parent;
};


KConstType 		    			dd_relc_common_get_type(void);
DdRelcCommon*		        dd_relc_common_new(void);

/**
 *RELC decode status is get.
 *@retval	RELC decode status
 *@remarks This function get the following conditions.<br>
 *			000b(IDLE)<br>
 *			001b(RUN)<br>
 *			010b(SLEEP)<br>
 *			100b(FINISH)
 */
extern	kint32 dd_relc_get_status( DdRelc*self );

/**
 *RELC sleep reason is get.
 *@retval	RELC sleep reason
 *@remarks This function is get the following sleeping reason.<br>
 *			000b(User instructions)<br>
 *			001b(Reaches the input end address)<br>
 *			010b(Reaches the output end address)
 */
extern	kint32 dd_relc_get_sleep_reason( DdRelc*self );


/**
 *RELC error status is get.
 *@remarks This function is get the following error status.<br>
 *			0b(No error)<br>
 *			1b(Error is occured)
 */
extern	kint32 dd_relc_get_error_status( DdRelc*self );

/**
 *RELC error number is get.
 *@retval DdRelc_D_DD_RELC_OK						OK
 *@retval D_DD_RELC_ERR_INPUT_DATA_x			Input data error
 *@retval DdRelc_D_DD_RELC_ERR_BUS_INPUT				Bus error(input)
 *@retval DdRelc_D_DD_RELC_ERR_BUS_OUTPUT			Bus error(output)
 *@retval DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_INPUT	Address mismatch error(input)
 *@retval DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_OUTPUT	Address mismatch error(output)
 */
extern	kint32 dd_relc_get_error( DdRelc*self );

/**
RELC status is get.
@param[out] decInfo				RELC processing status
@remarks This function is get the following processing status.<br>
			Number of bytes read<br>
			Number of bytes written<br>
			Number of processing blocks<br>
			Decode the total number of bytes to read<br>
			Decode the total number of bytes to write<br>
			Sequential run counter
*/
extern	kint32 dd_relc_get_process_status(DdRelc*self, TDdRelcDecInfo* decInfo );

/**
The input and reference data buffer size for RELC is get.
@param[out] inBufSize				input buffer size
@param[out] refBufSize			reference buffer size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_get_buf_size(DdRelc*self, kushort* inBufSize, kushort* refBufSize );

/**
Set the data to the input data buffer(mirror erea).
@param[in]	inDataAddr			input data address
@param[in]	inDataSize			input data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_set_in_buf_data_mirror(DdRelc*self, kulong inDataAddr, kuint32 inDataSize );

/**
Get the data to the input data buffer(mirror erea).
@param[out]	inDataAddr			input data address
@param[out]	inDataSize			input data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_get_in_buf_data_mirror(DdRelc*self, kulong inDataAddr, kuint32 inDataSize );

/**
Set the data to the input data buffer.
@param[in] inDataAddr				input data address
@param[in] inDataSize				input data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_set_in_buf_data(DdRelc*self, kulong inDataAddr, kuint32 inDataSize );

/**
Get the data to the input data buffer.
@param[out]	inDataAddr			input data address
@param[out]	inDataSize			input data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_get_in_buf_data(DdRelc*self, kulong inDataAddr, kuint32 inDataSize );

/**
Set the data to the reference data buffer.
@param[in]	outDataAddr			output data address
@param[in]	outDataSize			output data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_set_ref_buf_data(DdRelc*self, kulong outDataAddr, kuint32 outDataSize );

/**
Get the data to the reference data buffer.
@param[out]	outDataAddr			output data address
@param[out]	outDataSize			output data size
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
*/
extern	kint32 dd_relc_get_ref_buf_data(DdRelc*self, kulong outDataAddr, kuint32 outDataSize );


#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/**
Set and Start RELC normal mode
@param[in] relcSetModNormal		RELC setting for normal mode
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be set below.<br>
			Input start address
			Input data size
			Output start address
			Output data size
			Sequential Run Number of Times	: 0 or 1(normal)/2~(continuous number of executions)
*/
extern kint32 dd_relc_utility_register(DdRelc*self, TDdRelcSetModNormal const* const relcSetModNormal );

/**
Set and Start RELC descriptor mode
@param[in] relcSetModDesc		RELC setting for descriptor mode
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be set below.<br>
			descriptor address
			Sequential Run Number of Times	: 0 or 1(normal)/2~(continuous number of executions)
*/
extern kint32 dd_relc_utility_descriptor(DdRelc*self, TDdRelcSetModDesc const* const relcSetModDesc );

#endif	/* CO_DDIM_UTILITY_USE */


#ifdef __cplusplus
}
#endif



#endif /* __DD_RELC_COMMON_H__ */
