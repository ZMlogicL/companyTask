/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-03
*@author              :杨升柄
*@brief               :CtDdIpcu类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0 2020年09月开始开发
*/
#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "dd_ipcu.h"
#include "ctddipcu.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtDdIpcu, ct_dd_ipcu);
#define CT_DD_IPCU_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdIpcuPrivate,CT_TYPE_DD_IPCU))

struct _CtDdIpcuPrivate
{
	CtDdIpcuFunc    func;
	kpointer              userData;
};

static void ct_dd_ipcu_constructor(CtDdIpcu *self) 
{
	CtDdIpcuPrivate *priv = CT_DD_IPCU_GET_PRIVATE(self);

	priv->userData = NULL;
	self->priv = priv;
}

static void ct_dd_ipcu_destructor(CtDdIpcu *self) 
{
	CtDdIpcuPrivate *priv = CT_DD_IPCU_GET_PRIVATE(self);

	priv->userData = NULL;
	self->priv = NULL;
}

void ct_dd_ipcu_test_all_2(CtDdIpcu* self)
{
	CtDdIpcuPrivate *priv = self->priv;
	kint32	seqNo = 0;

	if(priv->func)
	{
		/*
		 * [CT]01-02-001
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Src()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu get srcr 0 1", priv->userData);
		priv->func(self,"ddipcu get srcr 8 2", priv->userData);
		priv->func(self,"ddipcu get srcr 16 4", priv->userData);

		/*
		 * [CT]01-02-002
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Mode()\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu get mr 0", priv->userData);
		priv->func(self,"ddipcu get mr 8", priv->userData);
		priv->func(self,"ddipcu get mr 16", priv->userData);

		/*
		 * [CT]01-02-003
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set dsr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x4", priv->userData);
		priv->func(self,"ddipcu get dstsr 0 8", priv->userData);
		priv->func(self,"ddipcu get dstsr 8 6", priv->userData);
		priv->func(self,"ddipcu get dstsr 16 2", priv->userData);

		/*
		 * [CT]01-02-004
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);
		priv->func(self,"ddipcu get dstsr 0 9", priv->userData);
		priv->func(self,"ddipcu get dstsr 8 7", priv->userData);
		priv->func(self,"ddipcu get dstsr 16 3", priv->userData);

		/*
		 * [CT]01-02-005
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Send()\n", seqNo++));
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu get sndr 0", priv->userData);
		priv->func(self,"ddipcu get sndr 8", priv->userData);
		priv->func(self,"ddipcu get sndr 16", priv->userData);

		/*
		 * [CT]01-02-006
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set dcr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x40", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x4", priv->userData);
		priv->func(self,"ddipcu get dstsr 0 8", priv->userData);
		priv->func(self,"ddipcu get dstsr 8 6", priv->userData);
		priv->func(self,"ddipcu get dstsr 16 2", priv->userData);

		/*
		 * [CT]01-02-007
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set dcru 0 9", priv->userData);
		priv->func(self,"ddipcu set dcru 8 7", priv->userData);
		priv->func(self,"ddipcu set dcru 16 3", priv->userData);
		priv->func(self,"ddipcu get dstsr 0 9", priv->userData);
		priv->func(self,"ddipcu get dstsr 8 7", priv->userData);
		priv->func(self,"ddipcu get dstsr 16 3", priv->userData);

		/*
		 * [CT]01-02-008
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set asr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x40", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x4", priv->userData);
		priv->func(self,"ddipcu get astsr 0 8", priv->userData);
		priv->func(self,"ddipcu get astsr 8 6", priv->userData);
		priv->func(self,"ddipcu get astsr 16 2", priv->userData);

		/*
		 * [CT]01-02-009
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);
		priv->func(self,"ddipcu get astsr 0 9", priv->userData);
		priv->func(self,"ddipcu get astsr 8 7", priv->userData);
		priv->func(self,"ddipcu get astsr 16 3", priv->userData);

		/*
		 * [CT]01-02-010
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set acr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set acr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set acr 16 0x4", priv->userData);
		priv->func(self,"ddipcu get asrcr 0 8", priv->userData);
		priv->func(self,"ddipcu get asrcr 8 6", priv->userData);
		priv->func(self,"ddipcu get asrcr 16 2", priv->userData);

		/*
		 * [CT]01-02-011
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set acru 0 9", priv->userData);
		priv->func(self,"ddipcu set acru 8 7", priv->userData);
		priv->func(self,"ddipcu set acru 16 3", priv->userData);
		priv->func(self,"ddipcu get asrcr 0 9", priv->userData);
		priv->func(self,"ddipcu get asrcr 8 7", priv->userData);
		priv->func(self,"ddipcu get asrcr 16 3", priv->userData);

		/*
		 * [CT]01-02-012
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set msr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set msr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set msr 16 0x4", priv->userData);
		priv->func(self,"ddipcu get msr 0 8", priv->userData);
		priv->func(self,"ddipcu get msr 8 6", priv->userData);
		priv->func(self,"ddipcu get msr 16 2", priv->userData);

		/*
		 * [CT]01-02-013
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set msru 0 9", priv->userData);
		priv->func(self,"ddipcu set msru 8 7", priv->userData);
		priv->func(self,"ddipcu set msru 16 3", priv->userData);
		priv->func(self,"ddipcu get msr 0 9", priv->userData);
		priv->func(self,"ddipcu get msr 8 7", priv->userData);
		priv->func(self,"ddipcu get msr 16 3", priv->userData);

		/*
		 * [CT]01-02-014
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set mcr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set mcr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set mcr 16 0x4", priv->userData);
		priv->func(self,"ddipcu get msr 0 8", priv->userData);
		priv->func(self,"ddipcu get msr 8 6", priv->userData);
		priv->func(self,"ddipcu get msr 16 2", priv->userData);

		/*
		 * [CT]01-02-015
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set mcru 0 9", priv->userData);
		priv->func(self,"ddipcu set mcru 8 7", priv->userData);
		priv->func(self,"ddipcu set mcru 16 3", priv->userData);
		priv->func(self,"ddipcu get msr 0 9", priv->userData);
		priv->func(self,"ddipcu get msr 8 7", priv->userData);
		priv->func(self,"ddipcu get msr 16 3", priv->userData);

		/*
		 * [CT]01-02-016
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set dr 0 0 0x12345678", priv->userData);
		priv->func(self,"ddipcu set dr 0 8 0x12345678", priv->userData);
		priv->func(self,"ddipcu set dr 8 0 0x12345678", priv->userData);
		priv->func(self,"ddipcu set dr 8 8 0x12345678", priv->userData);
		priv->func(self,"ddipcu set dr 16 0 0x12345678", priv->userData);
		priv->func(self,"ddipcu set dr 16 8 0x12345678", priv->userData);
		priv->func(self,"ddipcu get dr 0 0", priv->userData);
		priv->func(self,"ddipcu get dr 0 8", priv->userData);
		priv->func(self,"ddipcu get dr 8 0", priv->userData);
		priv->func(self,"ddipcu get dr 8 8", priv->userData);
		priv->func(self,"ddipcu get dr 16 0", priv->userData);
		priv->func(self,"ddipcu get dr 16 8", priv->userData);

		/*
		 * [CT]01-02-017
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Src()\n", seqNo));
		priv->func(self,"ddipcu set srcr 24 0x1", priv->userData);

		/*
		 * [CT]01-02-018
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Mode()\n", seqNo++));
		priv->func(self,"ddipcu set mr 24 0x1", priv->userData);

		/*
		 * [CT]01-02-019
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Send()\n", seqNo++));
		priv->func(self,"ddipcu set sndr 24", priv->userData);

		/*
		 * [CT]01-02-020
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Send()\n", seqNo++));
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);

		/*
		 * [CT]01-02-021
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set dsr 24 0x100", priv->userData);

		/*
		 * [CT]01-02-022
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set dsr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-023
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-024
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set dsru 24 0", priv->userData);
		priv->func(self,"ddipcu set dsru 0 16", priv->userData);

		/*
		 * [CT]01-02-025
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);

		/*
		 * [CT]01-02-026
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);

		/*
		 * [CT]01-02-027
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set dcr 24 0x100", priv->userData);
		priv->func(self,"ddipcu set dcr 0 5", priv->userData);

		/*
		 * [CT]01-02-028
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-029
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-030
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set dcru 24 0", priv->userData);
		priv->func(self,"ddipcu set dcru 0 16", priv->userData);

		/*
		 * [CT]01-02-031
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set dcru 0 8", priv->userData);
		priv->func(self,"ddipcu set dcru 8 6", priv->userData);
		priv->func(self,"ddipcu set dcru 16 2", priv->userData);

		/*
		 * [CT]01-02-032
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Dst_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set dcru 0 9", priv->userData);
		priv->func(self,"ddipcu set dcru 8 7", priv->userData);
		priv->func(self,"ddipcu set dcru 16 3", priv->userData);

		/*
		 * [CT]01-02-033
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set msr 24 0x100", priv->userData);
		priv->func(self,"ddipcu set msr 0 16", priv->userData);

		/*
		 * [CT]01-02-034 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set msr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set msr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set msr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-035
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set msr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set msr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set msr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-036
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set msru 24 0", priv->userData);
		priv->func(self,"ddipcu set msru 0 16", priv->userData);

		/*
		 * [CT]01-02-037
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set msru 0 8", priv->userData);
		priv->func(self,"ddipcu set msru 8 7", priv->userData);
		priv->func(self,"ddipcu set msru 16 3", priv->userData);

		/*
		 * [CT]01-02-038
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set msr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set msr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set msr 16 0x4", priv->userData);

		/*
		 * [CT]01-02-039
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set mcr 24 0x100", priv->userData);
		priv->func(self,"ddipcu set mcr 0 0x300", priv->userData);

		/*
		 * [CT]01-02-040
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set mcr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set mcr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set mcr 16 0x40", priv->userData);

		/*
		 * [CT]01-02-041
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set mcr 24 0", priv->userData);
		priv->func(self,"ddipcu set mcr 0 16", priv->userData);

		/*
		 * [CT]01-02-042
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set mcru 0 9", priv->userData);
		priv->func(self,"ddipcu set mcru 8 7", priv->userData);
		priv->func(self,"ddipcu set mcru 16 3", priv->userData);

		/*
		 * [CT]01-02-043
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Msk_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x6", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x6", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x6", priv->userData);

		/*
		 * [CT]01-02-044
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-045
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-046
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 3", priv->userData);
		priv->func(self,"ddipcu set mr 8 3", priv->userData);
		priv->func(self,"ddipcu set mr 16 3", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-047
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-048
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set asru 24 0", priv->userData);
		priv->func(self,"ddipcu set asru 0 16", priv->userData);

		/*
		 * [CT]01-02-049
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);

		/*
		 * [CT]01-02-050
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);

		/*
		 * [CT]01-02-051
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 3", priv->userData);
		priv->func(self,"ddipcu set mr 8 3", priv->userData);
		priv->func(self,"ddipcu set mr 16 3", priv->userData);
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcru 0 9", priv->userData);
		priv->func(self,"ddipcu set dcru 8 7", priv->userData);
		priv->func(self,"ddipcu set dcru 16 3", priv->userData);
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);

		/*
		 * [CT]01-02-052
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcru 0 9", priv->userData);
		priv->func(self,"ddipcu set dcru 8 7", priv->userData);
		priv->func(self,"ddipcu set dcru 16 3", priv->userData);
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 0 9", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 8 7", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);
		priv->func(self,"ddipcu set asru 16 3", priv->userData);

		/*
		 * [CT]01-02-053
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set acr 24", priv->userData);

		/*
		 * [CT]01-02-054
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set acr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set acr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set acr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-055
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set acr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set acr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set acr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-056
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack()\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 5", priv->userData);
		priv->func(self,"ddipcu set mr 8 5", priv->userData);
		priv->func(self,"ddipcu set mr 16 5", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set dcr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set dcr 16 0x8", priv->userData);
		priv->func(self,"ddipcu set asr 0 0x200", priv->userData);
		priv->func(self,"ddipcu set asr 8 0x80", priv->userData);
		priv->func(self,"ddipcu set asr 16 0x8", priv->userData);

		/*
		 * [CT]01-02-057
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set acru 24 0", priv->userData);
		priv->func(self,"ddipcu set acru 0 16", priv->userData);

		/*
		 * [CT]01-02-058
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 0", priv->userData);
		priv->func(self,"ddipcu set srcr 8 0", priv->userData);
		priv->func(self,"ddipcu set srcr 16 0", priv->userData);
		priv->func(self,"ddipcu set acru 0 9", priv->userData);
		priv->func(self,"ddipcu set acru 8 7", priv->userData);
		priv->func(self,"ddipcu set acru 16 3", priv->userData);

		/*
		 * [CT]01-02-059
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set acru 0 9", priv->userData);
		priv->func(self,"ddipcu set acru 8 7", priv->userData);
		priv->func(self,"ddipcu set acru 16 3", priv->userData);

		/*
		 * [CT]01-02-060
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Clr_MB_Ack_Unit()\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 5", priv->userData);
		priv->func(self,"ddipcu set mr 8 5", priv->userData);
		priv->func(self,"ddipcu set mr 16 5", priv->userData);
		priv->func(self,"ddipcu set dsru 0 9", priv->userData);
		priv->func(self,"ddipcu set dsru 8 7", priv->userData);
		priv->func(self,"ddipcu set dsru 16 3", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu set dcr 0 9", priv->userData);
		priv->func(self,"ddipcu set dcr 8 7", priv->userData);
		priv->func(self,"ddipcu set dcr 16 3", priv->userData);
		priv->func(self,"ddipcu set asr 0 9", priv->userData);
		priv->func(self,"ddipcu set asr 8 7", priv->userData);
		priv->func(self,"ddipcu set asr 16 3", priv->userData);

		/*
		 * [CT]01-02-061
		 */
		Ddim_Print(("*** [CT] 01-02-%03d : Dd_IPCU_Set_MB_Data()\n", seqNo++));
		priv->func(self,"ddipcu set dr 24 0 1", priv->userData);
		priv->func(self,"ddipcu set dr 0 9 1", priv->userData);
	}
}

void ct_dd_ipcu_test_all_3(CtDdIpcu* self)
{
	CtDdIpcuPrivate *priv = self->priv;
	kint32	seqNo = 0;

	if(priv->func)
	{
		/*
		 * [CT]01-03-001,002
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_Int_Stat()\n", seqNo++));
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack(),Dd_IPCU_Get_MB_Req(),Dd_IPCU_Get_MB_Adr()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set mr 0 2", priv->userData);
		priv->func(self,"ddipcu set dsr 0 0x100", priv->userData);
		priv->func(self,"ddipcu set sndr 0", priv->userData);
		priv->func(self,"ddipcu get isr 0 8 0", priv->userData);
		priv->func(self,"ddipcu get mbar 0 8", priv->userData);

		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set mr 8 2", priv->userData);
		priv->func(self,"ddipcu set dsr 8 0x40", priv->userData);
		priv->func(self,"ddipcu set sndr 8", priv->userData);
		priv->func(self,"ddipcu get isr 1 6 8", priv->userData);
		priv->func(self,"ddipcu get mbar 1 6", priv->userData);

		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu set mr 16 2", priv->userData);
		priv->func(self,"ddipcu set dsr 16 0x4", priv->userData);
		priv->func(self,"ddipcu set sndr 16", priv->userData);
		priv->func(self,"ddipcu get isr 2 2 16", priv->userData);
		priv->func(self,"ddipcu get mbar 2 2", priv->userData);

		seqNo = 11;

		/*
		 * [CT]01-03-012
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_Int_Stat()\n", seqNo++));
		priv->func(self,"ddipcu set srcr 0 1", priv->userData);
		priv->func(self,"ddipcu set srcr 8 2", priv->userData);
		priv->func(self,"ddipcu set srcr 16 4", priv->userData);
		priv->func(self,"ddipcu get mbsr 0 0", priv->userData);
		priv->func(self,"ddipcu get mbsr 1 8", priv->userData);
		priv->func(self,"ddipcu get mbsr 2 16", priv->userData);

		/*
		 * [CT]01-03-013
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_Int_Stat(), Dd_IPCU_Get_Int_Stat_MB()\n", seqNo++));
		priv->func(self,"ddipcu get isr 3 0 1", priv->userData);
		priv->func(self,"ddipcu get isr 0 16 1", priv->userData);

		/*
		 * [CT]01-03-014
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack(), Dd_IPCU_Get_MB_Req(), Dd_IPCU_Get_MB_Adr()\n", seqNo++));
		priv->func(self,"ddipcu get mbar 3 0", priv->userData);
		priv->func(self,"ddipcu get mbar 0 16 1", priv->userData);

		/*
		 * [CT]01-03-015
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Src(), Dd_IPCU_Get_MB_Src_Unit()\n", seqNo++));
		priv->func(self,"ddipcu get srcr 0 24 0", priv->userData);

		/*
		 * [CT]01-03-016
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Mode()\n", seqNo++));
		priv->func(self,"ddipcu get mr 24", priv->userData);

		/*
		 * [CT]01-03-017
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Send()\n", seqNo++));
		priv->func(self,"ddipcu get sndr 24", priv->userData);

		/*
		 * [CT]01-03-018
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Dst_Stat(), Dd_IPCU_Get_MB_Dst_Stat_Unit()\n", seqNo++));
		priv->func(self,"ddipcu dstsr 24 2", priv->userData);
		priv->func(self,"ddipcu dstsr 1 16", priv->userData);

		/*
		 * [CT]01-03-019
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Msk_Stat(), Dd_IPCU_Get_MB_Msk_Stat_Unit())\n", seqNo++));
		priv->func(self,"ddipcu msr 24 2", priv->userData);
		priv->func(self,"ddipcu msr 1 16", priv->userData);

		/*
		 * [CT]01-03-020
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack_Stat(), Dd_IPCU_Get_MB_Ack_Stat_Unit())\n", seqNo++));
		priv->func(self,"ddipcu msr 24 2", priv->userData);
		priv->func(self,"ddipcu msr 1 16", priv->userData);

		/*
		 * [CT]01-03-021
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack_Stat(), Dd_IPCU_Get_MB_Ack_Stat_Unit())\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 4", priv->userData);
		priv->func(self,"ddipcu set mr 8 4", priv->userData);
		priv->func(self,"ddipcu set mr 16 4", priv->userData);
		priv->func(self,"ddipcu get astsr 0 1", priv->userData);
		priv->func(self,"ddipcu get astsr 8 1", priv->userData);
		priv->func(self,"ddipcu get astsr 16 1", priv->userData);

		/*
		 * [CT]01-03-022
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack_Src(), Dd_IPCU_Get_MB_Ack_Src_Unit())\n", seqNo++));
		priv->func(self,"ddipcu asrcr 24 2", priv->userData);
		priv->func(self,"ddipcu asrcr 1 16", priv->userData);

		/*
		 * [CT]01-03-023
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Ack_Src(), Dd_IPCU_Get_MB_Ack_Src_Unit())\n", seqNo++));
		priv->func(self,"ddipcu set mr 0 0", priv->userData);
		priv->func(self,"ddipcu set mr 8 0", priv->userData);
		priv->func(self,"ddipcu set mr 16 0", priv->userData);
		priv->func(self,"ddipcu get asrcr 0 1", priv->userData);
		priv->func(self,"ddipcu get asrcr 8 1", priv->userData);
		priv->func(self,"ddipcu get asrcr 16 1", priv->userData);

		/*
		 * [CT]01-03-024
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Data())\n", seqNo++));
		priv->func(self,"ddipcu get dr 24 0", priv->userData);
		priv->func(self,"ddipcu get dr 0 9",priv->userData);

		/*
		 * [CT]01-03-025
		 */
		Ddim_Print(("*** [CT] 01-03-%03d : Dd_IPCU_Get_MB_Stat(), Dd_IPCU_Get_MB_Stat_MB())\n", seqNo++));
		priv->func(self,"ddipcu get mbsr 3 0",priv->userData);
		priv->func(self,"ddipcu get mbsr 0 8",priv->userData);
	}
}

void  ct_dd_ipcu_set_func(CtDdIpcu *self, CtDdIpcuFunc func, kpointer userData)
{
	CtDdIpcuPrivate *priv = self->priv;

	priv->func = func;
	priv->userData = userData;
}

CtDdIpcu* ct_dd_ipcu_new(void) 
{
    CtDdIpcu *self = k_object_new_with_private(CT_TYPE_DD_IPCU, sizeof(CtDdIpcuPrivate));
    return self;
}
