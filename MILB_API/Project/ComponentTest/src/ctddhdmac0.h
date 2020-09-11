/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac0类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC0_H__
#define __CT_DD_HDMAC0_H__

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_HDMAC0							(ct_dd_hdmac0_get_type())
#define CT_DD_HDMAC0(obj)								(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmac0))
#define CT_IS_DD_HDMAC0(obj)							(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC0))

/*
* Definition
* Size definition
*/
#define CtDdHdmac0_AUTO_TEST_SIZE				(0x96000)

//Address definition
#define CtDdHdmac0_SDRAM_BASE					(0x7A000000)

#define CtDdHdmac0_AUTO_TEST_ADR_SRC		(CtDdHdmac0_SDRAM_BASE)
#define CtDdHdmac0_AUTO_TEST_ADR_DST		(CtDdHdmac0_SDRAM_BASE + CtDdHdmac0_AUTO_TEST_SIZE)
// CPU1
#define CtDdHdmac0_CPU_TARGET					(2)


typedef struct 			_CtDdHdmac0 CtDdHdmac0;
typedef struct 			_CtDdHdmac0Private CtDdHdmac0Private;

struct _CtDdHdmac0
{
	KObject parent;

	/*
	 * Definition
	 *
	 * Enumeration
	 *
	 * Global Data
	*/
	T_DD_HDMAC0_CTRL					gHdmac0Ctrl[8];
	T_DD_HDMAC0_CTRL_TRNS		gHdmac0CtrlTrns[8];
	T_DD_HDMAC0_TRNS_SIZE		gHdmac0TrnsSize[8];

	kint32											ret;
	kint32											size;
	kulong											srcAddr;
	kulong											dstAddr;
	kchar*											endstr;
	VP_CALLBACK								intHandler;
	kuchar											ch;
	kuchar											num;
	kint32											waitTime;
	kuchar											inputSel;

};

KConstType 			ct_dd_hdmac0_get_type(void);
CtDdHdmac0* 		ct_dd_hdmac0_new(void);

void 						ct_hdmac0_callback( void );
void 						ct_dd_hdmac0_from_main(CtDdHdmac0* self, kint argc, kchar** argv);


#endif /* __CT_DD_HDMAC0_H__ */
