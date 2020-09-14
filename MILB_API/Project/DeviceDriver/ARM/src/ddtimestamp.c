/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-08-04
*@author              :徐廷军
*@brief               :sns 索喜rtos
*@redd                :glib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年06月开始开发
*/


#include "ddarm.h"
#include "ddtimestamp.h"


G_DEFINE_TYPE(DdTimestamp, dd_timestamp, G_TYPE_OBJECT);
#define DD_TIMESTAMP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), DD_TYPE_TIMESTAMP, DdTimestampPrivate));
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
	gint a;
	DdTimestamp *ddtimestamp;
	DdimUserCustom_ER ercd;
	DdimUserCustom_ID sid;
};
/**
 *DECLS
 */
static void 		dispose_od(GObject *object);
static void 		finalize_od(GObject *object);
/**
 *IMPL
 */
static void 		dd_timestamp_class_init(DdTimestampClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class -> dispose = dispose_od;
	object_class -> finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(DdTimestampPrivate));
}

static void 		dd_timestamp_init(DdTimestamp *self)
{
	DdTimestampPrivate *priv = DD_TIMESTAMP_GET_PRIVATE(self);
	priv->a = 0;
	self->ddmiUserCustom = ddim_user_custom_new();
	priv->ddtimestamp = dd_timestamp_new();
	priv->ercd = dd_timestamp_new();
	priv->sid = dd_timestamp_new();
}
static void 		dispose_od(GObject *object)
{
	DdTimestampPrivate *priv = DD_TIMESTAMP_GET_PRIVATE(object);
	G_OBJECT_CLASS(dd_timestamp_parent_class) -> dispose(object);
}

static void 		finalize_od(GObject *object)
{
	DdTimestampPrivate *priv = DD_TIMESTAMP_GET_PRIVATE(object);
	DdTimestamp *self = dd_timestamp_new();
	if(self->ddmiUserCustom)
	{
		g_object_unref(self->ddmiUserCustom);
		self->ddmiUserCustom = NULL;
	}
	if(priv->ddtimestamp){
		g_object_unref(priv->ddtimestamp);
		priv->ddtimestamp;
	}
	if(priv->ercd){
		g_object_unref(priv->ercd);
		priv->ercd = NULL;
	}
	if(priv->sid){
		g_object_unref(priv->sid);
		priv->sid = NULL;
	}
	G_OBJECT_CLASS(dd_timestamp_parent_class) -> dispose(object);
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
 * @param	gint32 tmout
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_SEM_NG/
 * DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR/DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT
 */
gint32 dd_timestamp_open(DdTimestamp*self, gint32 tmout)
{
	DdimUserCustom_ER ercd;
	DdimUserCustom_ID sid;

#ifdef CO_PARAM_CHECK
	if (tmout < DdimUserCustom_SEM_WAIT_FEVR) {
		Ddim_Assertion(("dd_timestamp_open: input param error. tmout = %d\n", tmout));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	sid = SID_DD_TIMESTAMP;

	if (DdimUserCustom_SEM_WAIT_POL == tmout) {
		// pol_sem()
		//ercd = ddim_user_custom_pol_sem(ddim_user_custom_get(), sid);
		ercd = ddim_user_custom_pol_sem(self->ddmiUserCustom, sid);
	}
	else {
		// twai_sem()
		ercd = ddim_user_custom_twai_sem(self->ddmiUserCustom, sid, (DDIM_USER_TMO) tmout);
	}

	if (DdimUserCustom_E_OK != ercd) {
		if (DdimUserCustom_E_TMOUT == ercd) {
			return DdTimestamp_D_DD_TIMESTAMP_SEM_TIMEOUT;
		}
		return DdTimestamp_D_DD_TIMESTAMP_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Operation condition of Timestamp is set.
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
gint32 dd_timestamp_ctrl(DdTimestamp*self)
{
#ifdef CO_PARAM_CHECK
	if (self == NULL) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [*self] NULL\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
	if (self->frequency == 0) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [frequency] 0\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
	if (self->frequency > DdTimestamp_D_DD_TIMESTAMP_FREQUENCY_MAX) {
		Ddim_Assertion(("dd_timestamp_ctrl: input param error. [frequency] MAX Over\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	// Set value of CNTCR register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_HDbg(self->hdbg);
	// Set value of CNTCVL register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL((gulong )(self->counter & 0x00000000FFFFFFFF));
	// Set value of CNTCVU register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU((gulong )((self->counter & 0xFFFFFFFF00000000) >> 32));
	// Set value of CNTFID0 register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTFID0(self->frequency);

	return D_DDIM_OK;
}

/**
 * @brief	Start Global timer Counter function.
 */
void dd_timestamp_start(DdTimestamp*self)
{
	// Timestamp Counter Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(1);
	DD_ARM_DSB_POC();
}

/**
 * @brief	Stop Global timer function.
 */
void dd_timestamp_stop(DdTimestamp*self)
{
	// Timestamp Counter no Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(0);
	DD_ARM_DSB_POC();
}

/**
 * @brief	Exclusive control of Timestamp is released.
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_SEM_NG
 */
gint32 dd_timestamp_close(DdTimestamp*self)
{
	DdTimestampPrivate *priv = DD_TDDESTAMP_GET_PRIVATE(self);
	priv->sid = SID_DD_TIMESTAMP;

	// sig_sem()
	priv->ercd = ddim_user_custom_sig_sem(self->ddmiUserCustom, priv->sid);
	if ( DdimUserCustom_E_OK != priv->ercd) {
		return DdTimestamp_D_DD_TIMESTAMP_SEM_NG;
	}

	return D_DDIM_OK;
}

/**
 * @brief	Get value of TIMESTAMP CNTCVL and CNTCVU register.
 * @param	kulonglong* timestampCounter
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
gint32 dd_timestamp_get_counter(DdTimestamp*self, kulonglong* timestampCounter)
{
	gulong upCounter1 = 0;
	gulong upCounter2 = 0;
	gulong lowCounter = 0;

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
 * @param	DdTimestamp* self
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
gint32 dd_timestamp_get_control(DdTimestamp*self)
{
	DdTimestampPrivate *priv = DD_TDDESTAMP_GET_PRIVATE(self);
#ifdef CO_PARAM_CHECK
	if (self == NULL) {
		Ddim_Assertion(("dd_timestamp_get_control: input param error. [*self] NULL\n"));
		return DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR;
	}
#endif
	// Get value of CNTCR register
	self->hdbg = DdTimestamp_Dd_TIMESTAMP_Get_CNTCR_HDbg;
	// Get value of CNTCVL and CNTCVU register
	dd_timestamp_get_counter(priv->ddtimestamp, &(self->counter));
	// Get value of CNTFID0 register
	self->frequency = DdTimestamp_Dd_TIMESTAMP_Get_CNTFID0;

	return D_DDIM_OK;
}

/**
 * @brief	Set value of TIMESTAMP CNTCVL and CNTCVU register.
 * @param	kulonglong timestampCounter
 * @return	gint32 D_DDIM_OK
 */
gint32 dd_timestamp_set_counter(DdTimestamp*self, kulonglong timestampCounter)
{
	// Timestamp Counter no Increment
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCR_En(0);
	// Set value of CNTCVL register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVL((gulong )(timestampCounter & 0x00000000FFFFFFFF));
	// Set value of CNTCVU register
	DdTimestamp_Dd_TIMESTAMP_Set_CNTCVU((gulong )((timestampCounter & 0xFFFFFFFF00000000) >> 32));

	return D_DDIM_OK;
}

#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
/**
 * @brief	The operation condition of Timestamp is set. VALUE unit:[us]
 * @param	gulong usec, gulong frequency
 * @return	gint32 D_DDIM_OK/DdTimestamp_D_DD_TIMESTAMP_INPUT_PARAM_ERR
 */
gint32 dd_timestamp_set_timer(DdTimestamp*self, gulong usec, gulong frequency)
{
	DdTimestampPrivate *priv = DD_TDDESTAMP_GET_PRIVATE(self);
	//	kulonglong usec_count;
	gulong usecCountL;
	gulong usecCountU;
	gulong usec3124;
	gulong usec2312;
	gulong usec110;
	gulong usecCount3124;
	gulong usecCount2312;
	gulong usecCount110;
	gulong usecCountLWk;
	gulong usecCountUWk;

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
	dd_timestamp_init(priv->ddtimestamp);
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

DdTimestamp* 		dd_timestamp_new(void)
{
	DdTimestamp *self = g_object_new(DD_TYPE_TIMESTAMP, NULL);
	return self;
}

//DdTimestamp* dd_timestamp_get(void)
//{
//	DdTimestamp *self = NULL;
//	if(!self){
//		self = k_object_new(DD_TYPE_TDDESTAMP, NULL);
//	}
//	return self;
//}
