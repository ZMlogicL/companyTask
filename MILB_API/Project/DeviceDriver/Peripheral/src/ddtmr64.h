/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-02
* @author    : 肖泽友
* @brief        :peripheral 64 bit reload timer driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、
*
*@version   :1.0.0
*
*/

/*
@addtogroup dd_tmr64
@{
	@code
	kint32 Timer64_Sample_Code(void)
	{
		TDdTmr64Ctrl tmr64_ctrl;

		tmr64_ctrl.csr1.bit.trg  = 0;	// Start at Dd_TMR64_Start()
		tmr64_ctrl.csr1.bit.cnte = 0;	// Enalbe at Dd_TMR64_Start()
		tmr64_ctrl.csr1.bit.csl  = 2;	// 32div
		tmr64_ctrl.csr2.bit.cvt  = 0;	// Counter load trigger off
		tmr64_ctrl.csr2.bit.tsen = 0;	// Enable at Dd_TMR64_Start()

		ret = Dd_TMR64_Open(3000);
		if (ret != D_DDIM_OK) {
			// ERROR
			return;
		}
		ret = Dd_TMR64_Ctrl(&tmr64_ctrl);
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR64_Close();
			return;
		}
		ret = Dd_TMR64_Start(TRUE);		// Start count and enable time stamp
		if (ret != D_DDIM_OK) {
			// ERROR
			Dd_TMR64_Close();
			return;
		}

		// To get timer value at appropriate timing by following any API.
		//   Dd_TMR64_Get_Gyro_TimeStamp()
		//   Dd_TMR64_Get_FrameStart_TimeStamp()
		//   Dd_TMR64_Get_FrameEnd_TimeStamp()
		//   Dd_TMR64_Get_Counter()

		ret = Dd_TMR64_Stop();
		if (ret != D_DDIM_OK) {
			// ERROR
			return;
		}
		ret = Dd_TMR64_Close();
		if (ret != D_DDIM_OK) {
			// ERROR
			return;
		}
	}
	@endcode

*/

#ifndef __DD_TMR64_H__
#define __DD_TMR64_H__

#include <klib.h>
#include "driver_common.h"

#define DD_TYPE_TMR64                       (dd_tmr64_get_type())
#define DD_TMR64(obj)                         K_TYPE_CHECK_INSTANCE_CAST(obj, DdTmr64)
#define DD_IS_TMR64(obj)                    K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_TMR64)

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Return value of 64 bit reload timer processing result */
/*< Input Parameter Error */
#define DdTmr64_INPUT_PARAM_ERR		(D_DD_TMR64 | D_DDIM_INPUT_PARAM_ERROR)
/*< Semaphore acquisition Time Out */
#define DdTmr64_SEM_TIMEOUT			    (D_DD_TMR64 | D_DDIM_SEM_TIMEOUT)
/*< Semaphore acquisition NG */
#define DdTmr64_SEM_NG				            (D_DD_TMR64 | D_DDIM_SEM_NG)
/*< Abnormal Status */
#define DdTmr64_STATUS_ABNORMAL      (D_DD_TMR64 | D_DDIM_STATUS_ABNORMAL)
/*< DMA stop status error  */
#define DdTmr64_DMA_SS_ERROR			    (D_DD_TMR64 | D_DDIM_BUS_ERROR)

typedef struct _TDdTmr64Ctrl               TDdTmr64Ctrl;

typedef struct _DdTmr64                       DdTmr64;
typedef struct _DdTmr64Private           DdTmr64Private;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* CSR1 of free run timer */
typedef union
{
	/*< for kulong access */
	kulong		word;
	/*< for bit access*/
	struct {
		/*< Count start trriger (Read value is 0)*/
		kulong	 trg			:1;
		/*< Timer counter enable*/
		kulong	 cnte		:1;
		/*< Reserved*/
		kulong				:8;
		/*< Count clock select (0:1/2, 1:1/8, 2:1/32)*/
		kulong	 csl			:2;
		/*< Reserved	*/
		kulong				:4;
		/*< Reserved	*/
		kulong				:16;
    } bit;
}UDdTmr64Csr1;

/* CSR2 of free run timer */
typedef union
{
	/*< for kulong access */
	kulong		word;
	/*< for bit access*/
	struct {
		/*< Counter load trigger(Read value is 0)	*/
		kulong cvt			:1;
		/*< Reserved	*/
		kulong				:15;
		/*< Time stamp enable	*/
		kulong	 tsen		:1;
		/*< Reserved	*/
		kulong				:15;
    } bit;
}UDdTmr64Csr2;

/* Control information */
struct _TDdTmr64Ctrl
{
	/*< Control status    TMCSR64_1 */
	UDdTmr64Csr1		csr1;
	/*< Control status    TMCSR64_2*/
	UDdTmr64Csr2		csr2;
};

struct _DdTmr64
{
	KObject parent;
};

KConstType          dd_tmr64_get_type(void);
DdTmr64*            dd_tmr64_get(void);

#ifdef __cplusplus
extern "C" {
#endif

/*
*The 64bit Timer is exclusively controlled.<br>
*If a pertinent 64bit Timer is unused, exclusive control OK is sent back as (Lock) while using it.<br>
*Exclusive control NG is sent back when using it (Lock inside of present).
*When timeout occurs, return "D_DD_TMR64_SEM_TIMEOUT".
*
*@param [in]		timeOut		Time of timeout<br>
*							<ul><li>Positive Value(Time of timeout)
*								<li>@ref D_DDIM_USER_SEM_WAIT_POL
*								<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*@retval D_DD_TMR64_SEM_NG			Lock Error
*@retval D_DD_TMR64_SEM_TIMEOUT		Semaphore acquisition Time Out
*@remarks This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
*		 This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
kint32	                   dd_tmr64_open(DdTmr64* self, kint32 timeOut);

/*
*64bit Timer is released.
*
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_SEM_NG			Lock Error
*@remarks This API uses DDIM_User_Sig_Sem().
*/
kint32	                   dd_tmr64_close(DdTmr64* self);

/*
*The operation condition of Timer is set.
*
*@param [in]    *tmr64Ctrl	Timer64 Control Information
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_ctrl(DdTmr64* self, TDdTmr64Ctrl const* const tmr64Ctrl);

/*
*Value of TDdTmr64Ctrl is gotten.
*
*@param [out]   *tmr64Ctrl	Timer64 Control Information
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_get_ctrl(DdTmr64* self, TDdTmr64Ctrl* const tmr64Ctrl);

/*
*64bit Timer is started.
*
*@param [in]    timeStampEnable	Time stamp enable
*@retval D_DDIM_OK					OK
*/
kint32	                   dd_tmr64_start(DdTmr64* self, kboolean timeStampEnable);

/*
*64bit Timer is stopped.
*
*@retval D_DDIM_OK					OK
*/
kint32	                   dd_tmr64_stop(DdTmr64* self);

/*
*64bit Timer Gyro Time Stamp value is gotten.
*
*@param [out]   timeStamp		Time stamp value of Gyro
*@retval D_DDIM_OK						OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_get_gyro_time_stamp(DdTmr64* self, kulong* const timeStamp);

/*
*64bit Timer Frame Start counter value is gotten.
*
*@param [in]    sensorNo		Sensor number
*@param [in]    lotationCount	Lotation count
*@param [out]   timeStamp		Time stamp value of Frame Start
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_get_frame_start_time_stamp(DdTmr64* self, kuint32 sensorNo,
		                            kuint32 lotationCount, kulonglong* const timeStamp);

/*
*64bit Timer Frame End counter value is gotten.
*
*@param [in]    sensorNo		Sensor number
*@param [in]    lotationCount	Lotation count
*@param [out]   timeStamp		Time stamp value of Frame End
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_get_frame_end_time_stamp(DdTmr64* self, kuint32 sensorNo,
		                            kuint32 lotationCount, kulonglong* const timeStamp);

/*
*64bit Timer counter value is gotten.
*
*@param [out]   counter	Current counter value
*@retval D_DDIM_OK					OK
*@retval D_DD_TMR64_INPUT_PARAM_ERR	Input Parameter Error
*/
kint32	                   dd_tmr64_get_counter(DdTmr64* self, kulonglong* const counter);

#ifdef CO_DDIM_UTILITY_USE
/*
*Enable/Disable 64bit Time Stamp.
*
*@param [in]    timeStampEnable	Time stamp enable
*@retval D_DDIM_OK					OK
*/
kint32	                   dd_tmr64_time_stamp_enable(DdTmr64* self, kboolean timeStampEnable);

#endif	// CO_DDIM_UTILITY_USE

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* __DD_TMR64_H__ */
