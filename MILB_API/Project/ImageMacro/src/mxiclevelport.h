/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxiclevelport.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_LEVEL_PORT_H__ 
#define __MXIC_LEVEL_PORT_H__ 

#include "mxicutlis.h"

#define MXIC_TYPE_LEVEL_PORT    (mxic_level_port_get_type())
#define MXIC_LEVEL_PORT(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicLevelPort))
#define MXIC_IS_LEVEL_PORT(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_LEVEL_PORT))


typedef struct{
	ImMxicUnit unit;
	ImMxicWrArbiter wrArbiter;
	ImMxicSpecArbiter arbiter;
}LevelPortArgs;

typedef struct _MxicLevelPort MxicLevelPort;
typedef struct _MxicLevelPortPrivate MxicLevelPortPrivate;

struct _MxicLevelPort {
    KObject parent;
};

KConstType  mxic_level_port_get_type(void);
// MxicLevelPort*     mxic_level_port_get(void);
MxicLevelPort*     mxic_level_port_new(void);

/**
This function set clock supply to a functional block. 
@param [in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param [in]		clock					Clock enable setting.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_set_clock_enable( MxicLevelPort *self, ImMxicUnit unit, const ImMxicClock* const clock );

/**
This function get clock supply to a functional block. 
@param [in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param [out]	clock					Clock enable setting.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_level_port_get_clock_enable( MxicLevelPort *self, ImMxicUnit unit, ImMxicClock* const clock );

/**
This function set the LevelPort(Port).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_level_port_set_levelport_port( MxicLevelPort *self, LevelPortArgs portArgs, 
											UCHAR master, ImMxicPort port );

/**
This function get the LevelPort(Port).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[out]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_level_port_get_levelport_port( MxicLevelPort *self, LevelPortArgs portArgs, 
											UCHAR master, ImMxicPort* const port );

/**
This function get the LevelPort(Level).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[out]		level					Target Level.<br>
										Please refer to @ref ImMxicLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_level_port_get_levelport_level( MxicLevelPort *self, LevelPortArgs levelArgs, 
												UCHAR master, ImMxicLevel* const level );

/**
This function set the LevelPort(Level).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		master					Master number.<br>
@param[in]		level					Target Level.<br>
										Please refer to @ref ImMxicLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_level_port_set_levelport_level( MxicLevelPort *self, LevelPortArgs levelArgs, 
												UCHAR master, ImMxicLevel level );

/**
This function set the LevelPort(All).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		allLevelport			All LevelPort information.<br>
										Please refer to @ref ImMxicAllLevelport.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_set_levelport_all( MxicLevelPort *self, ImMxicUnit unit, ImMxicAllLevelport* allLevelport );

/**
This function get the LevelPort(All).<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[out]		allLevelport			All LevelPort information.<br>
										Please refer to @ref ImMxicAllLevelport.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32 mxic_level_port_get_levelport_all( MxicLevelPort *self, ImMxicUnit unit, ImMxicAllLevelport* allLevelport );

#endif	// __MXIC_LEVEL_PORT_H__