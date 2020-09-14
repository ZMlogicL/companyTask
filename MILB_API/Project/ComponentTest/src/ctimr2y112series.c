/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y112series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y112series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y112series, ct_im_r2y_112series)
#define CT_IM_R2Y_112SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y112seriesPrivate, CT_TYPE_IM_R2Y_112SERIES))


struct _CtImR2y112seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_112series_constructor(CtImR2y112series *self)
{
	CtImR2y112seriesPrivate *priv = CT_IM_R2Y_112SERIES_GET_PRIVATE(self);
	self->imR2yUtility2 = im_r2y_utility2_new();
	self->imR2yUtility3 = im_r2y_utility3_new();
	self->imR2yUtility4 = im_r2y_utility4_new();
}

static void ct_im_r2y_112series_destructor(CtImR2y112series *self)
{
	CtImR2y112seriesPrivate *priv = CT_IM_R2Y_112SERIES_GET_PRIVATE(self);
			if(self->imR2yUtility2){
							k_object_unref(self->imR2yUtility2);
							self->imR2yUtility2=NULL;
				}

				if(self->imR2yUtility3){
					k_object_unref(self->imR2yUtility3);
					self->imR2yUtility3=NULL;
				}

				if(self->imR2yUtility4){
							k_object_unref(self->imR2yUtility4);
							self->imR2yUtility4=NULL;
				}
}


/*
 * PUBLIC
 */
#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_0: "
kint32 ct_im_r2y_112series_0(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgdtAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_egdt_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgdtAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_1: "
kint32 ct_im_r2y_112series_1(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgcmpAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_egcmp_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgcmpAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef CtImR2y112series_FUNC_NAME
#define CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_2: "
kint32 ct_im_r2y_112series_2(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCrvAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_crv_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCrvAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_3: "
kint32 ct_im_r2y_112series_3(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgcrvAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_egcrv_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgcrvAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_4: "
kint32 ct_im_r2y_112series_4(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaYbcrvAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_ybcrv_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaYbcrvAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_5: "
kint32 ct_im_r2y_112series_5(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaClpfAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_clpf_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaClpfAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_6: "
kint32 ct_im_r2y_112series_6(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCspAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_csp_cntl(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCspAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_7: "
kint32 ct_im_r2y_112series_7(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaToneTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility2_get_rdma_addr_tone_table(self->imR2yUtility2, pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaToneTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_8: "
kint32 ct_im_r2y_112series_8(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaGmdfTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility3_get_rdma_addr_gmdf_table(self->imR2yUtility3, pipeNo, 0, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmdfTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address RGB[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility3_get_rdma_addr_gmdf_table(self->imR2yUtility3, pipeNo, 1, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmdfTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address R[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility3_get_rdma_addr_gmdf_table(self->imR2yUtility3, pipeNo, 2, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmdfTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address G[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility3_get_rdma_addr_gmdf_table(self->imR2yUtility3, pipeNo, 3, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmdfTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address B[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility3_get_rdma_addr_gmdf_table(self->imR2yUtility3, pipeNo, 4, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmdfTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address Yb[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y112series_FUNC_NAME
#define 	CtImR2y112series_FUNC_NAME "ct_im_r2y_112series_9: "
kint32 ct_im_r2y_112series_9(CtImR2y112series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaGmflTblAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y112series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = im_r2y_utility4_get_rdma_addr_gmfl_table(self->imR2yUtility4, pipeNo, 0, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmflTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address RGB[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_gmfl_table(self->imR2yUtility4, pipeNo, 1, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmflTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address R[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_gmfl_table(self->imR2yUtility4, pipeNo, 2, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmflTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address G[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_gmfl_table(self->imR2yUtility4, pipeNo, 3, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmflTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address B[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
	ercd = im_r2y_utility4_get_rdma_addr_gmfl_table(self->imR2yUtility4, pipeNo, 4, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGmflTblAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y112series_FUNC_NAME "address Yb[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

CtImR2y112series *ct_im_r2y_112series_new(void)
{
	CtImR2y112series *self = k_object_new_with_private(CT_TYPE_IM_R2Y_112SERIES, sizeof(CtImR2y112seriesPrivate));

	return self;
}
