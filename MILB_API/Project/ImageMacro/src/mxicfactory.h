/***********************************************************************
 * @Copyright(C) 上海网用软件有限公司
 * @file mxicfactory.h
 * @date 2020-09-04
 * @author: 吴海辉
 * @brief: 
 * @version: 1.0.0
***********************************************************************/

#ifndef __MXIC_FACTORY_H__ 
#define __MXIC_FACTORY_H__ 

#include <klib.h>
#include "immxic.h"
#include "mxicutlis.h"
#include "mxicmasterslave.h"
#include "mxicmonitoraccess.h"
#include "mxiclevelport.h"
#include "mxicslot.h"
#include "mxicacccapa.h"
#include "mxicmaster.h"


#define MXIC_TYPE_FACTORY    (mxic_factory_get_type())
#define MXIC_FACTORY(obj)    (K_TYPE_CHECK_INSTANCE_CAST(obj, MxicFactory))
#define MXIC_IS_FACTORY(obj) (K_TYPE_CHECK_INSTANCE_TYPE(obj, MXIC_TYPE_FACTORY))


typedef struct _MxicFactory MxicFactory;
typedef struct _MxicFactoryPrivate MxicFactoryPrivate;

struct _MxicFactory {
    KObject parent;

    ImMxic* imMxic;
    MxicUtlis* mxicUtlis;
    MxicMasterSlave* mxicMasterSlave;
    MxicMonitorAccess* mxicMonitorAccess;
    MxicLevelPort* mxicLevelPort;
    MxicSlot* mxicSlot;
    MxicAccCapa* mxicAccCapa;
    MxicMaster* mxicMaster;
};

KConstType  mxic_factory_get_type(void);
MxicFactory*     mxic_factory_get(void);

ImMxic *mxic_factory_create_im_mxic(MxicFactory *self);
MxicUtlis *mxic_factory_create_mxic_utlis(MxicFactory *self);
MxicMasterSlave *mxic_factory_create_mxic_master_slave(MxicFactory *self);
MxicMonitorAccess *mxic_factory_create_mxic_monitor_access(MxicFactory *self);
MxicLevelPort *mxic_factory_create_mxic_level_port(MxicFactory *self);
MxicSlot *mxic_factory_create_mxic_slot(MxicFactory *self);
MxicAccCapa *mxic_factory_create_mxic_acc_capa(MxicFactory *self);
MxicMaster *mxic_factory_create_mxic_master(MxicFactory *self);


#endif	// __MXIC_FACTORY_H__