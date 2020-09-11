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
*1.0.0 2020年06月开始开发
*/

#ifndef __DD_TIMESTAMP_H__
#define __DD_TIMESTAMP_H__


#include <klib.h>
#include "driver_common.h"
#include "arm.h"


#ifdef __cplusplus
extern "C" {
#endif

#define DD_TYPE_TDDESTAMP			(dd_timestamp_get_type())
#define DD_TDDESTAMP(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, DdTimestamp))
#define DD_IS_TDDESTAMP(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_TDDESTAMP))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return value of TIMESTAMP processing result
/**< Input Parameter Error */
#define	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR		(D_DD_TIMESTAMP | D_DDIM_INPUT_PARAM_ERROR)
/**< Semaphore acquisition Time Out */
#define DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT				(D_DD_TIMESTAMP | D_DDIM_SEM_TIMEOUT)
/**< Semaphore acquisition NG */
#define DdTimestamp_D_DD_TIMESTAMP_SEM_NG						(D_DD_TIMESTAMP | D_DDIM_SEM_NG)

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special
/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Counter Control Register (CNTCR)
/**< Get Enable (0:Disable 1:Enable) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_En							(ioTimestamp.cntcr.bit.en)
/**< Set Enable (0:Disable 1:Enable) */
#define DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(val)					{ioTimestamp.cntcr.bit.en = (val);}

/**< Get Halt on Debug (0:has no effect 1:halts the counter) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_HDbg					(ioTimestamp.cntcr.bit.hdbg)
/**< Set Halt on Debug (0:has no effect 1:halts the counter) */
#define DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_HDbg(val)				{ioTimestamp.cntcr.bit.hdbg = (val);}

// Counter Status Register (CNTSR)
/**< Get Enable (0:Not Debug Halted 1:Debug Halted) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTSR_Dbgh						(ioTimestamp.cntsr.bit.dbgh)

// Current Counter Value Lower register (CNTCVL)
/**< Get Counter Lower (0x00000000 to 0xFFFFFFFF) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL								(ioTimestamp.cntcvl)
/**< Set Counter Lower (0x00000000 to 0xFFFFFFFF) */
#define DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL(val)						{ioTimestamp.cntcvl = (val);}

// Current Counter Value Upper register (CNTCVU)
/**< Get Counter Upper (0x00000000 to 0xFFFFFFFF) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU								(ioTimestamp.cntcvu)
/**< Set Counter Upper (0x00000000 to 0xFFFFFFFF) */
#define DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU(val)						{ioTimestamp.cntcvu = (val);}

// Base Frequency ID register (CNTFID0)
/**< Get Frequency (0x00000000 to 0xEE6B2800(4GHz)) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0							(ioTimestamp.cntfid0)
/**< Set Frequency (0x00000000 to 0xEE6B2800(4GHz)) */
#define DdTimestamp_Dd_TIMESTAMP_Set_CNTFID0(val)						{ioTimestamp.cntfid0 = (val);}

// Peripheral ID4 Register (PERIPID4)
/**< Get Designer of the component (0b0100:JEDEC code) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR4_Des_2						(ioTimestamp.pidr4.bit.des2)
/**< Get Designer of the component (0b0000:4KB memory) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR4_Size							(ioTimestamp.pidr4.bit.size)

// Peripheral ID0 Register (PERIPID0)
/**< Get Part number of the component (0x01:Part number) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR0_Part_0					(ioTimestamp.pidr0.bit.part0)

// Peripheral ID1 Register (PERIPID1)
/**< Get Designer of the component (0b1011:JEDEC code) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR1_Des_0						(ioTimestamp.pidr1.bit.des0)
/**< Get Part number of the component (0b0001:Part number) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR1_Part_1					(ioTimestamp.pidr1.bit.part1)

// Peripheral ID2 Register (PERIPID2)
/**< Get Designer of the component (0b011:JEDEC code) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Des_1						(ioTimestamp.pidr2.bit.des1)
/**< Get Designer ID (0b1:JEDEC-assigned) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Jedec						(ioTimestamp.pidr2.bit.jedec)
/**< Get Device (0b0001:r0p1) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR2_Revision					(ioTimestamp.pidr2.bit.revision)

// Peripheral ID3 Register (PERIPID3)
/**< Get Errata (0b0000:No errata) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR3_Cmod						(ioTimestamp.pidr3.bit.cmod)
/**< Get Modify of component (0b0000:Not modified) */
#define DdTimestamp_Dd_TIMESTAMP_Get_PIDR3_Revand					(ioTimestamp.pidr3.bit.revand)

// Component ID0 Register (CIDR0)
/**< Get Identification code (0x0D) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CIDR0_Prmbl_0					(ioTimestamp.cidr0.bit.prmbl0)

// Component ID1 Register (CIDR1)
/**< Get Identification code (0b0000) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CIDR1_Prmbl_1					(ioTimestamp.cidr1.bit.prmbl1)
/**< Get Class of the component (0b1111:CoreSight SoC-400) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CIDR1_Class						(ioTimestamp.cidr1.bit.class)

// Component ID2 Register (CIDR2)
/**< Get Identification code (0x05) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CIDR2_Prmbl_2					(ioTimestamp.cidr2.bit.prmbl2)

// Component ID3 Register (CIDR3)
/**< Get Identification code (0xB1) */
#define DdTimestamp_Dd_TIMESTAMP_Get_CIDR3_Prmbl_3					(ioTimestamp.cidr3.bit.prmbl3)



typedef struct _DdTimestamp 				DdTimestamp;
typedef struct _DdTimestampPrivate 	DdTimestampPrivate;


/*----------------------------------------------------------------------*/
/* Enumeration																	*/
/*----------------------------------------------------------------------*/
// Nothing Special
/*----------------------------------------------------------------------*/
/* Structure  																		*/
/*----------------------------------------------------------------------*/
/** Control value */
struct _DdTimestamp
{
	KObject parent;
	/**< Halt on Debug of TIMESTAMP CNTCR register<br>
	 <ul>
	 <li>0:has no effect
	 <li>1:halts the counter
	 </ul> */
	kulong hdbg;
	/**< Counter of TIMESTAMP CNTCVL and CNTCVU register<br>
	 64bit counter value. */
	kulonglong counter;
	/**< Frequency of TIMESTAMP CNTFID0 register<br>
	 Value range:0x00000001 to 0xEE6B2800(4GHz) */
	kulong frequency;
};


/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
KConstType 		    		dd_timestamp_get_type(void);
DdTimestamp*		        dd_timestamp_new(void);

/**
 Initialize all Timestamp Register.
 */
extern void dd_timestamp_init (DdTimestamp*self);

/**
 Timestamp fuction is exclusively controlled.
 @param [in]		tmout: Time of timeout
 <ul>
 <li>Positive Value
 <li>@ref D_DDIM_USER_SEM_WAIT_POL
 <li>@ref D_DDIM_USER_SEM_WAIT_FEVR
 </ul>
 @retval	D_DDIM_OK: Normal end
 @retval	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR: Input Parameter Error
 @retval	DdTimestamp_D_DD_TIMESTAMP_SEM_NG: Lock Error (System Using designated channel number)
 @retval	DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT: Semaphore acquisition Time Out
 @remarks	If Timestamp is unused, exclusive control OK is sent back as (Lock) while using it.<br>
 Exclusive control NG is sent back when using it (Lock inside of present).<br>
 When timeout occurs, return "DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT".
 @remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
 */
extern kint32 dd_timestamp_open (DdTimestamp*self, kint32 tmout);

/**
 Setting of common control variable for Timestamp Counter.
 @param [in]	timestampCtrl: Tiemstamp Control value. See @ref DdTimestamp
 @retval	D_DDIM_OK: Normal end
 @retval	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR: Input Parameter Error
 */
extern kint32 dd_timestamp_ctrl (DdTimestamp*self, DdTimestamp* timestampCtrl);

/**
 Timestamp is started.
 */
extern void dd_timestamp_start (DdTimestamp*self);

/**
 Timestamp is stopped.
 */
extern void dd_timestamp_stop (DdTimestamp*self);

/**
 Timestamp is released.
 @retval	D_DDIM_OK: Normal end
 @retval	DdTimestamp_D_DD_TIMESTAMP_SEM_NG: UnLock Error
 @remarks	This API uses DDIM_User_Sig_Sem().
 */
extern kint32 dd_timestamp_close (DdTimestamp*self);

/**
 Get value of TIMESTAMP CNTCVL and CNTCVU register.
 @param [out]	timestampCounter		: Timestamp Counter
 @retval	D_DDIM_OK							: Normal end
 @retval	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR	: Input Parameter Error
 */
extern kint32 dd_timestamp_get_counter (DdTimestamp*self, kulonglong* timestampCounter);

/**
 Get value of Timestamp Control value.
 @param [out]	timestampCtrl			: Timestamp Control value. See @ref DdTimestamp
 @retval	D_DDIM_OK						: Noraml end
 @retval	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR	: Input Parameter Error
 */
extern kint32 dd_timestamp_get_control (DdTimestamp*self, DdTimestamp* timestampCtrl);

/**
 Set value of TIMESTAMP CNTCVL and CNTCVU register.
 @param [in]		timestampCounter		: Timestamp Counter
 @retval	D_DDIM_OK								: Normal end
 */
extern kint32 dd_timestamp_set_counter (DdTimestamp*self, kulonglong timestampCounter);

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/**
 @name Utility Functions
 @{*/
/**
 The operation condition of Timestamp is set according to designate time parameter.
 @param [in]	usec								: Designated time(micro second)
 @param [in]	frequency					: Frequency(0x00000001 to 0xEE6B2800(4GHz))
 @retval	D_DDIM_OK						: Noraml end
 @retval	DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR		: Input Parameter Error
 */
extern kint32 dd_timestamp_set_timer (DdTimestamp*self, kulong usec, kulong frequency);

/*@}*/
#endif	// CO_DDIM_UTILITY_USE

#ifdef __cplusplus
}
#endif

/**
 @weakgroup dd_timestamp
 @{
 @section Timestamp_start_base			Basic sequence of Timestamp
 @image html dd_timestamp_base.png
 <br>
 @section Timestamp_Sample_Basic			Sample of Timestamp (Basic sequence)
 The example of executing Timestamp counter start to end is as follows.<br>
 <b>Please call these APIs from either of one of multiple cores.<br>
 These are not under exclusive control between the cores.</b>
 @code
 kint32	ret;									// Return value
 DdTimestamp	timestampCtrl;

 timestampCtrl.hdbg = 0;						// has no effect
 timestampCtrl.counter = 0x0000000000000000;	// Counter
 timestampCtrl.frequency = 0xEE6B2800;			// 4GHz

 dd_timestamp_init();

 ret = dd_timestamp_open(D_DDIM_USER_SEM_WAIT_POL);
 if (ret != 0) {
 // ERROR
 return ;
 }

 ret = dd_timestamp_ctrl(&timestampCtrl);
 if (ret != 0) {
 // ERROR
 return ;
 }

 dd_timestamp_start();

 // Stop sequence
 dd_timestamp_stop(NULL);

 ret = dd_timestamp_close();
 if (ret != 0) {
 // ERROR
 }
 @endcode
 @}*/


#endif /* __DD_TIMESTAMP_H__ */
