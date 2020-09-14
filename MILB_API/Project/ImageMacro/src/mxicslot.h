/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicslot.h
 * @date 2020-09-02
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_SLOT_H__ 
#define __MXIC_SLOT_H__ 

#include "mxicutlis.h"


#define MXIC_TYPE_SLOT    (mxic_slot_get_type())
#define MXIC_SLOT(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicSlot))
#define MXIC_IS_SLOT(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_SLOT))


typedef struct{
	ImMxicUnit unit; 
	ImMxicWrArbiter wrArbiter; 
	ImMxicSpecArbiter arbiter;
}SlotArgs;


typedef struct _MxicSlot MxicSlot;
typedef struct _MxicSlotPrivate MxicSlotPrivate;

struct _MxicSlot {
    KObject parent;
};

KConstType  mxic_slot_get_type(void);
MxicSlot*     mxic_slot_get(void);
MxicSlot*     mxic_slot_new(void);


/**
This function set the slot priority level control.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		levelNumber			Target level.<br>
										Please refer to @ref MxicSlotLevelCtrl for a set value.<br>
@param[in]		priority				Priority level control settings.
										Please refer to @ref MxicSlotPriorityLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting ranges are from 1 to 64.
*/
kint32	mxic_slot_set_slot_priority( MxicSlot *self, SlotArgs priArgs, ImMxicPort port, 
			MxicSlotLevelCtrl levelNumber, const MxicSlotPriorityLevel* const priority );
/**
This function get the slot priority level control.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		levelNumber			Target level.<br>
										Please refer to @ref MxicSlotLevelCtrl for a set value.<br>
@param[in]		priority				Priority level control settings.
										Please refer to @ref MxicSlotPriorityLevel for a set value.<br>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32 	mxic_slot_get_slot_priority( MxicSlot *self, SlotArgs priArgs, ImMxicPort port, 
			MxicSlotLevelCtrl levelNumber, MxicSlotPriorityLevel* const priority );
/**
This function set the slot priority level control to all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		allPriority			Slot priority level control setting of all arbiter.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
@remarks		The setting  ranges are from 1 to 64.
*/
kint32	mxic_slot_set_slot_priority_all_arbiter( MxicSlot *self, ImMxicUnit unit, 
			const MxicAllSlotPriority* const allPriority );

/**
This function get the slot priority level control from all arbiter.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[out]		allPriority			Slot priority level control setting of all arbiter.
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_slot_get_slot_priority_all_arbiter( MxicSlot *self, ImMxicUnit unit, 
			MxicAllSlotPriority* const allPriority );

/**
This function set the slot mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		slot					Target slot number.<br>
										Please refer to @ref ImMxicSlot for a set value. <br>
@param[in]		maskEnable				Slot mask enable.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_slot_set_slot_mask( MxicSlot *self, SlotArgs maskArgs, ImMxicPort port, 
								ImMxicSlot slot, kuchar maskEnable );

/**
This function get the slot mask.<br>
@param[in]		unit					Target unit number.<br>
										Please refer to @ref ImMxicUnit for a set value.<br>
@param[in]		wrArbiter				Target write or read Arbiter.<br>
										Please refer to @ref ImMxicWrArbiter for a set value.<br>
@param[in]		arbiter					Target arbiter.<br>
										Please refer to @ref ImMxicSpecArbiter for a set value.<br>
@param[in]		port					Target Port.<br>
										Please refer to @ref ImMxicPort for a set value.<br>
@param[in]		slot					Target slot number.<br>
										Please refer to @ref ImMxicSlot for a set value. <br>
@param[out]		maskEnable				Slot mask enable.<br>
										<ul><li>@ref MxicUtlis_ON
											<li>@ref MxicUtlis_OFF</ul>
@retval			D_DDIM_OK					Success.
@retval			MxicUtlis_INPUT_PARAM_ERROR	Fail - Parameter error.
*/
kint32	mxic_slot_get_slot_mask( MxicSlot *self, SlotArgs maskArgs, ImMxicPort port, 
								ImMxicSlot slot, kuchar* const maskEnable );

#endif	// __MXIC_SLOT_H__