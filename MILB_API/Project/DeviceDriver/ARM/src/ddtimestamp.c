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


#include <MILB_API/Project/PalladiumTest/src/ddimusercustom.h>
#include "ddarm.h"
#include "ddtimestamp.h"


K_TYPE_DEFINE_WITH_PRIVATE(DdTimestamp, dd_timestamp);
#define DD_TDDESTAMP_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), DdTimestampPrivate, DD_TYPE_TDDESTAMP))
/*----------------------------------------------------------------------	*/
/* Definition																	*/
/*----------------------------------------------------------------------	*/
/**< Initialize TIMESTAMP Counter */
#define DdTimestamp_D_DD_TIMESTAMP_COUNTER_INIT		(0x00000000)
/**< Initialize TIMESTAMP Frequency */
#define DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_INIT	(0x00000000)
/**< Max TIMESTAMP Frequency */
#define DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_MAX	(0xEE6B2800)


struct _DdTimestampPrivate
{
	kint a;
};
/**
 *IMPL
 */
static void dd_timestamp_constructor(DdTimestamp *self)
{
//	DdTimestampPrivate *priv = DD_TDDESTAMP_GET_PRIVATE(self);
}

static void dd_timestamp_destructor(DdTimestamp *self)
{
//	DdTimestampPrivate *priv = DD_TDDESTAMP_GET_PRIVATE(self);
}
/**
 * PUBLIC
 */
/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Global Data															*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Local Function														*/
/*----------------------------------------------------------------------*/
// Nothing Special

/*----------------------------------------------------------------------*/
/* Grobal Function														*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/**
 * @brief  	Initialize all Timestamp Register.
 */
void dd_timestamp_init(DdTimestamp*self)
{
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(0);
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_HDbg(0);
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL(DdTimestamp_D_DD_TIMESTAMP_COUNTER_INIT);
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU(DdTimestamp_D_DD_TIMESTAMP_COUNTER_INIT);
	DdTimestamp_Dd_TIMESTAMP_Set_CNTFID0(DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_INIT);
}

/**
 * @brief	Timestamp fuction is exclusively controlled.
 * @param	kint32 tmout
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_SEM_NG/
 * DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR/DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT
 */
kint32 dd_timestamp_open(DdTimestamp*self, kint32 tmout)
{
	DDIM_USER_ER ercd;
	DDIM_USER_ID sid;

#ifdef CO_PARAM_CHECK
	if (tmout < D_DDIM_USER_SEM_WAIT_FEVR) {
		Ddim_Assertion(("dd_timestamp_open: input param error. tmout = %d\n", tmout));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	sid = SID_DD_TIMESTAMP;

	if (D_DDIM_USER_SEM_WAIT_POL == tmout) {
		// pol_sem()
		ercd = DDIM_User_Pol_Sem(sid);
	}
	else {
		// twai_sem()
		ercd = DDIM_User_Twai_Sem(sid, (DDIM_USER_TMO) tmout);
	}

	if (D_DDIM_USER_E_OK != ercd) {
		if (D_DDIM_USER_E_TMOUT == ercd) {
			return DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT;
		}
		return DdTimestamp_D_DD_TIMESTAMP_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Operation condition of Timestamp is set.
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
kint32 dd_timestamp_ctrl(DdTimestamp*self, DdTimestamp* timestampCtrl)
{
#ifdef CO_PARAM_CHECK
	if (timestampCtrl == NULL) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [*timestampCtrl] NULL\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
	if (timestampCtrl->frequency == 0) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [frequency] 0\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
	if (timestampCtrl->frequency > DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_MAX) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [frequency] MAX Over\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	// Set value of CNTCR register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_HDbg(timestampCtrl->hdbg);
	// Set value of CNTCVL register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL((kulong )(timestampCtrl->counter & 0x00000000FFFFFFFF));
	// Set value of CNTCVU register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU((kulong )((timestampCtrl->counter & 0xFFFFFFFF00000000) >> 32));
	// Set value of CNTFID0 register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTFID0(timestampCtrl->frequency);

	return D_DDIM_OK;
}

/**
 * @brief	Start Global timer Counter function.
 */
void dd_timestamp_start(DdTimestamp*self)
{
	// Timestamp Counter Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(1);
	Dd_ARM_Dsb_Pou();
}

/**
 * @brief	Stop Global timer function.
 */
void dd_timestamp_stop(DdTimestamp*self)
{
	// Timestamp Counter no Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(0);
	Dd_ARM_Dsb_Pou();
}

/**
 * @brief	Exclusive control of Timestamp is released.
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_SEM_NG
 */
kint32 dd_timestamp_close(DdTimestamp*self)
{
	DDIM_USER_ER ercd;
	DDIM_USER_ID sid;

	sid = SID_DD_TIMESTAMP;

	// sig_sem()
	ercd = DDIM_User_Sig_Sem(sid);
	if ( D_DDIM_USER_E_OK != ercd) {
		return DdTimestamp_D_DD_TIMESTAMP_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get value of TIMESTAMP CNTCVL and CNTCVU register.
 * @param	kulonglong* timestampCounter
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
kint32 dd_timestamp_get_counter(DdTimestamp*self, kulonglong* timestampCounter)
{
	kulong upCounter1 = 0;
	kulong upCounter2 = 0;
	kulong lowCounter = 0;

#ifdef CO_PARAM_CHECK
	if (timestampCounter == NULL) {
		Ddim_Assertion(("dd_timestamp_get_counter: input param error. [*timestampCounter] NULL\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	// Get value of TIMESTAMP CNTCVU register
	upCounter1 = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
	// Get value of TIMESTAMP CNTCVL register
	lowCounter = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL;
	// Get value of TIMESTAMP CNTCVU register
	upCounter2 = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
	while (upCounter1 != upCounter2) {
		upCounter1 = upCounter2;
		// Get value of TIMESTAMP CNTCVL register
		lowCounter = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVL;
		// Get value of TIMESTAMP CNTCVU register
		upCounter2 = DdTimestamp_Dd_TIMESTAMP_Get_CNTCVU;
	}
	*timestampCounter = ((kulonglong) upCounter2 << 32) + lowCounter;

	return D_DDIM_OK;
}

/**
 * @brief	Get value of Timestamp Control value.
 * @param	DdTimestamp* timestampCtrl
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
kint32 dd_timestamp_get_control(DdTimestamp*self, DdTimestamp* timestampCtrl)
{
#ifdef CO_PARAM_CHECK
	if (timestampCtrl == NULL) {
		Ddim_Assertion(("dd_timestamp_get_control: input param error. [*timestampCtrl] NULL\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	// Get value of CNTCR register
	timestampCtrl->hdbg = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_HDbg;
	// Get value of CNTCVL and CNTCVU register
	dd_timestamp_get_counter(NULL, &(timestampCtrl->counter));
	// Get value of CNTFID0 register
	timestampCtrl->frequency = DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0;

	return D_DDIM_OK;
}

/**
 * @brief	Set value of TIMESTAMP CNTCVL and CNTCVU register.
 * @param	kulonglong timestampCounter
 * @return	kint32 D_DDIM_OK
 */
kint32 dd_timestamp_set_counter(DdTimestamp*self, kulonglong timestampCounter)
{
	// Timestamp Counter no Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(0);
	// Set value of CNTCVL register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL((kulong )(timestampCounter & 0x00000000FFFFFFFF));
	// Set value of CNTCVU register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU((kulong )((timestampCounter & 0xFFFFFFFF00000000) >> 32));

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/**
 * @brief	The operation condition of Timestamp is set. VALUE unit:[us]
 * @param	kulong usec, kulong frequency
 * @return	kint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
kint32 dd_timestamp_set_timer(DdTimestamp*self, kulong usec, kulong frequency)
{
	//	kulonglong usec_count;
	kulong usecCountL;
	kulong usecCountU;
	kulong usec3124;
	kulong usec2312;
	kulong usec110;
	kulong usecCount3124;
	kulong usecCount2312;
	kulong usecCount110;
	kulong usecCountLWk;
	kulong usecCountUWk;

#ifdef CO_PARAM_CHECK
	if (frequency == 0) {
		Ddim_Assertion(("dd_timestamp_set_timer: input param error. [frequency] 0\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
	if (frequency > DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_MAX) {
		Ddim_Assertion(("dd_timestamp_set_timer: input param error. [frequency] MAX Over\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	dd_timestamp_init(NULL);
	// Counter value
	//	usec_count = (usec * 1000000) / frequency;
	usec3124 = ((usec & 0xFF000000) >> 24);
	usec2312 = ((usec & 0x00FFF000) >> 12);
	usec110 = usec & 0x00000FFF;
	if (frequency > 0xFFFFFF) {
		usecCount3124 = ((usec3124 * 1000000) / (frequency / 0x1000000));
		usecCount2312 = ((usec2312 * 1000000) / (frequency / 0x1000000));
		usecCount110 = ((usec110 * 1000000) / (frequency / 0x1000000));
	}
	else {
		usecCount3124 = (usec3124 * 1000000) / frequency;
		usecCount2312 = (usec2312 * 1000000) / frequency;
		usecCount110 = (usec110 * 1000000) / frequency;
	}
	usecCountLWk = ((usecCount3124 & 0x0000000F) << 24) + ((usecCount2312 & 0x0000FFFF) << 12) + (usecCount110 & 0x0FFFFFFF);
	usecCountUWk = ((usecCount3124 & 0xFFFFFFF0) >> 4) + ((usecCount2312 & 0xFFFF0000) >> 16)
		+ ((usecCount110 & 0xF0000000) >> 28) + ((usecCountLWk & 0xF0000000) >> 28);
	usecCountL = ((usecCountUWk & 0x0000000F) << 28) + (usecCountLWk & 0x0FFFFFF);
	usecCountU = ((usecCountUWk & 0xFFFFFFF0) >> 4);

	DdTimestamp_Dd_TIMESTAMP_Set_CNTFID0(frequency);
	//	dd_timestamp_set_counter(NULL, usecCount);
	if (frequency > 0xFFFFFF) {
		DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL((usecCountL / 0x1000000) | ((usecCountU & 0x00FFFFFF) << 8));
		DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU(usecCountU / 0x1000000);
	}
	else {
		DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL(usecCountL);
		DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU(usecCountU);
	}
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(1);

	return D_DDIM_OK;
}
#endif	// CO_DDIM_UTILITY_USE

DdTimestamp* dd_timestamp_new(void)
{
	DdTimestamp *self = k_object_new_with_private(DD_TYPE_TDDESTAMP, sizeof(DdTimestampPrivate));
	return self;
}
