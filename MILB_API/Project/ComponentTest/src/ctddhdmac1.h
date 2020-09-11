/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                 	:2020-09-04
*@author             	:杨升柄
*@brief                	:CtDdHdmac1类
*@rely                  	:klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC1_H__
#define __CT_DD_HDMAC1_H__

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_HDMAC1						(ct_dd_hdmac1_get_type())
#define CT_DD_HDMAC1(obj)							(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmac1))
#define CT_IS_DD_HDMAC1(obj)						(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC1))

/*
* Definition
* Size definition
*/
#define CtDdHdmac1_AUTO_TEST_SIZE			(0x96000)

//Address definition
#define CtDdHdmac1_SDRAM_BASE				(0x7A000000)

#define CtDdHdmac1_AUTO_TEST_ADR_SRC	(CtDdHdmac1_SDRAM_BASE)
#define CtDdHdmac1_AUTO_TEST_ADR_DST	(CtDdHdmac1_SDRAM_BASE + CtDdHdmac1_AUTO_TEST_SIZE)
// CPU1
#define CtDdHdmac1_CPU_TARGET				(2)

typedef struct 			_CtDdHdmac1 CtDdHdmac1;
typedef struct 			_CtDdHdmac1Private CtDdHdmac1Private;

struct _CtDdHdmac1
{
	KObject 									parent;

   /*
	* Definition
	* Enumeration
	* Global Data
	*/
	T_DD_HDMAC1_CTRL				gHdmac1Ctrl[8];
	T_DD_HDMAC1_CTRL_TRNS	gHdmac1CtrlTrns[8];
	T_DD_HDMAC1_TRNS_SIZE	gHdmac1TrnsSize[8];

	/*
	 * 函数拆分出来两边都有的变量
	 */
	kint32										ret;
	kint32										size;
	kuchar										ch;
	kulong										srcAddr;
	kulong										dstAddr;
	kchar*										endstr;
};

KConstType 			ct_dd_hdmac1_get_type(void);
CtDdHdmac1* 		ct_dd_hdmac1_new(void);

void 						ct_dd_hdmac1_from_main(CtDdHdmac1 *self, kint argc, kchar** argv);

#endif /* __CT_DD_HDMAC1_H__ */
