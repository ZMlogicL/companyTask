/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicmaster.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_MASTER_H__ 
#define __MXIC_MASTER_H__ 

#include "mxicutlis.h"


#define MXIC_TYPE_MASTER    (mxic_master_get_type())
#define MXIC_MASTER(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicMaster))
#define MXIC_IS_MASTER(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_MASTER))


typedef struct _MxicMaster MxicMaster;
typedef struct _MxicMasterPrivate MxicMasterPrivate;

struct _MxicMaster {
    KObject parent;
};

KConstType  mxic_master_get_type(void);
MxicMaster*     mxic_master_new(void);

/**
This function set the movement position after the master process.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		master					Master number.<br>
@param[in]		priority				Master priority level.<br>
										<ul><li>@ref MxicUtlis_MASTER_MOVE_LAST
											<li>@ref MxicUtlis_MASTER_MOVE_1
											<li>@ref MxicUtlis_MASTER_MOVE_2
											<li>@ref MxicUtlis_MASTER_MOVE_3
											<li>@ref MxicUtlis_MASTER_MOVE_4
											<li>@ref MxicUtlis_MASTER_MOVE_5
											<li>@ref MxicUtlis_MASTER_MOVE_6
											<li>@ref MxicUtlis_MASTER_MOVE_7
											<li>@ref MxicUtlis_MASTER_MOVE_8
											<li>@ref MxicUtlis_MASTER_MOVE_9
											<li>@ref MxicUtlis_MASTER_MOVE_10
											<li>@ref MxicUtlis_MASTER_MOVE_11
											<li>@ref MxicUtlis_MASTER_MOVE_12
											<li>@ref MxicUtlis_MASTER_MOVE_13
											<li>@ref MxicUtlis_MASTER_MOVE_14
											<li>@ref MxicUtlis_MASTER_MOVE_15</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_set_master_priority( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR priority );

/**
This function get the movement position after the master process.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[out]		priority				Master priority level.<br>
										<ul><li>@ref MxicUtlis_MASTER_MOVE_LAST
											<li>@ref MxicUtlis_MASTER_MOVE_1
											<li>@ref MxicUtlis_MASTER_MOVE_2
											<li>@ref MxicUtlis_MASTER_MOVE_3
											<li>@ref MxicUtlis_MASTER_MOVE_4
											<li>@ref MxicUtlis_MASTER_MOVE_5
											<li>@ref MxicUtlis_MASTER_MOVE_6
											<li>@ref MxicUtlis_MASTER_MOVE_7
											<li>@ref MxicUtlis_MASTER_MOVE_8
											<li>@ref MxicUtlis_MASTER_MOVE_9
											<li>@ref MxicUtlis_MASTER_MOVE_10
											<li>@ref MxicUtlis_MASTER_MOVE_11
											<li>@ref MxicUtlis_MASTER_MOVE_12
											<li>@ref MxicUtlis_MASTER_MOVE_13
											<li>@ref MxicUtlis_MASTER_MOVE_14
											<li>@ref MxicUtlis_MASTER_MOVE_15</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_priority( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR* const priority );

/**
This function set the master transfer mask and mask period.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		mask					Setting of mask.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting mask ranges are from 4 to 4096.
*/
INT32	mxic_master_set_master_mask( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
									const ImMxicMasterMask* const mask );

/**
This function get the master transfer mask and mask period.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[out]		mask					Setting of mask.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_mask( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
									ImMxicMasterMask* const mask );

/**
This function set factor of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[in]		enable					Setting of whether to make a master into a mask factor.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_set_master_mask_factor( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR enable );

/**
This function get factor of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[out]		enable					Setting of whether to make a master into a mask factor.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_mask_factor( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR* const enable );

/**
This function set target of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[in]		enable					Setting of whether to make a master into a mask target.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_set_master_mask_target( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR enable );

/**
This function get target of transfer demand mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		group					Mask group.<br>
										Please refer to @ref ImMxicMaskGroup for a set value.<br>
@param[out]		enable					Setting of whether to make a master into a mask target.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_mask_target( MxicMaster *self, ImMxicUnit unit, UCHAR master, 
											ImMxicMaskGroup group, UCHAR* const enable );

/**
This function set the mask factor master state.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		select					Master state select.(0:master address ch demand period ,1:master address ch demand to data transfer complete)<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_set_master_mask_select( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR select );

/**
This function get the mask factor master state.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[out]		select					Master state select.(0:master address ch demand period ,1:master address ch demand to data transfer complete)<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_mask_select( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR* const select );

/**
This function set the max number of master transaction.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[in]		transaction				Master transaction.(0~63)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_set_master_transaction( MxicMaster *self, ImMxicUnit unit, UCHAR master, UCHAR transaction );

/**
This function get the max number of master transaction.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value. <br>
@param[in]		master					Master number. See master parameter of function in mxic_master_set_master_priority.<br>
@param[out]		transaction				Master transaction.(0~63)<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
INT32	mxic_master_get_master_transaction( MxicMaster *self, ImMxicUnit unit, 
											UCHAR master, UCHAR* const transaction );

#endif	// __MXIC_MASTER_H__