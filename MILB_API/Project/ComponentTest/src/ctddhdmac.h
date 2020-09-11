/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-04
*@author              :杨升柄
*@brief               :CtDdHdmac类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __CT_DD_HDMAC_H__
#define __CT_DD_HDMAC_H__

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_HDMAC								(ct_dd_hdmac_get_type())
#define CT_DD_HDMAC(obj)								(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdHdmac))
#define CT_IS_DD_HDMAC(obj)							(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_HDMAC))

/*
* Definition
* Size definition
*/
#define CtDdHdmac_AUTO_TEST_SIZE				(0x96000)

//Address definition
#define CtDdHdmac_SDRAM_BASE						(0x7A000000)

#define CtDdHdmac_AUTO_TEST_ADR_SRC		(CtDdHdmac_SDRAM_BASE)
#define CtDdHdmac_AUTO_TEST_ADR_DST		(CtDdHdmac_SDRAM_BASE + CtDdHdmac_AUTO_TEST_SIZE)
// CPU1
#define CtDdHdmac_CPU_TARGET						(2)

typedef struct 			_CtDdHdmac CtDdHdmac;
typedef struct 			_CtDdHdmacPrivate CtDdHdmacPrivate;

struct _CtDdHdmac
{
	KObject 								parent;
	/*
	 * 原函数全局静态变量
	 */
	T_DD_HDMAC_CTRL			gHdmacCtrl[8];
	T_DD_HDMAC_CTRL_TRNS	gHdmacCtrlTrns[8];
	T_DD_HDMAC_TRNS_SIZE	gHdmacTrnsSize[8];
	/*
	 * 函数局部变量抽出来的属性
	 */
	kuchar									ch;
	kuchar									num;
	kchar*									endstr;
	VP_CALLBACK						intHandler;
	kulong									srcAddr;
	kulong									dstAddr;
	kint32									size;
	kint32									ret;
};

KConstType 	ct_dd_hdmac_get_type(void);
CtDdHdmac* 	ct_dd_hdmac_new(void);

void 				ct_dd_hdmac_from_main(CtDdHdmac *self, kint argc, kchar** argv);


#endif /* __CT_DD_HDMAC_H__ */
