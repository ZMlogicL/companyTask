/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicfatory.c
 * @date 2020-09-04
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#include "mxicfactory.h"


K_TYPE_DEFINE_WITH_PRIVATE(MxicFactory, mxic_factory)
#define MXIC_FACTORY_GET_PRIVATE(o) (K_OBJECT_GET_PRIVATE((o), MxicFactoryPrivate, MXIC_TYPE_FACTORY))


struct _MxicFactoryPrivate
{
    int a;
};


/*----------------------------------------------------------------------*/
/* DECLS  															    */
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* IMPL  															    */
/*----------------------------------------------------------------------*/
static void mxic_factory_constructor(MxicFactory *self)
{
    //MxicFactoryPrivate *priv = MXIC_FACTORY_GET_PRIVATE(self);
}

static void mxic_factory_destructor(MxicFactory *self)
{
}


/*----------------------------------------------------------------------*/
/* PUBLIC  															    */
/*----------------------------------------------------------------------*/
ImMxic *mxic_factory_create_im_mxic(MxicFactory *self)
{
    if(!self->imMxic){
		self->imMxic = im_mxic_new();
	}
	return self->imMxic;
}
MxicUtlis *mxic_factory_create_mxic_utlis(MxicFactory *self)
{
    if(!self->mxicUtlis){
		self->mxicUtlis = mxic_utlis_new();
	}
	return self->mxicUtlis;
}
MxicMasterSlave *mxic_factory_create_mxic_master_slave(MxicFactory *self)
{
    if(!self->mxicMasterSlave){
		self->mxicMasterSlave = mxic_master_slave_new();
	}
	return self->mxicMasterSlave;
}
MxicMonitorAccess *mxic_factory_create_mxic_monitor_access(MxicFactory *self)
{
    if(!self->mxicMonitorAccess){
		self->mxicMonitorAccess = mxic_monitor_access_new();
	}
	return self->mxicMonitorAccess;
}
MxicLevelPort *mxic_factory_create_mxic_level_port(MxicFactory *self)
{
    if(!self->mxicLevelPort){
		self->mxicLevelPort = mxic_level_port_new();
	}
	return self->mxicLevelPort;
}
MxicSlot *mxic_factory_create_mxic_slot(MxicFactory *self)
{
    if(!self->mxicSlot){
		self->mxicSlot = mxic_slot_new();
	}
	return self->mxicSlot;
}
MxicAccCapa *mxic_factory_create_mxic_acc_capa(MxicFactory *self)
{
    if(!self->mxicAccCapa){
		self->mxicAccCapa = mxic_acc_capa_new();
	}
	return self->mxicAccCapa;
}
MxicMaster *mxic_factory_create_mxic_master(MxicFactory *self)
{
    if(!self->mxicMaster){
		self->mxicMaster = mxic_master_new();
	}
	return self->mxicMaster;
}

MxicFactory *mxic_factory_get(void)
{
    static MxicFactory* self = NULL;
	if(!self){
        self = k_object_new_with_private(MXIC_TYPE_FACTORY, sizeof(MxicFactoryPrivate));
        self->imMxic = NULL;
        self->mxicAccCapa = NULL;
        self->mxicLevelPort = NULL;
        self->mxicMaster = NULL;
        self->mxicMasterSlave = NULL;
        self->mxicMonitorAccess = NULL;
        self->mxicSlot = NULL;
        self->mxicUtlis = NULL;
    }
    return self;
}
