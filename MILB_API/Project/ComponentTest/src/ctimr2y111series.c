/*
*
*@Copyright (C) 2010-2019 贵阳高新网用软件有限公司
*@date : 2020-09-07
*@author : 梁正明
*@brief : CtImR2y111series
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#include "ctimr2ytool.h"
#include "ctimr2y111series.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtImR2y111series, ct_im_r2y_111series)
#define CT_IM_R2Y_111SERIES_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o), \
		CtImR2y111seriesPrivate, CT_TYPE_IM_R2Y_111SERIES))


struct _CtImR2y111seriesPrivate
{

};


/*
 * IMPL
 */
static void ct_im_r2y_111series_constructor(CtImR2y111series *self)
{
	//CtImR2y111seriesPrivate *priv = CT_IM_R2Y_111SERIES_GET_PRIVATE(self);
}

static void ct_im_r2y_111series_destructor(CtImR2y111series *self)
{
	//CtImR2y111seriesPrivate *priv = CT_IM_R2Y_111SERIES_GET_PRIVATE(self);
}


/*
 * PUBLIC
 */
#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_0: "
kint32 ct_im_r2y_111series_0(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaToneAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_Tone_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaToneAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_1: "
kint32 ct_im_r2y_111series_1(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaGammaAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_Gamma_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaGammaAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_2: "
kint32 ct_im_r2y_111series_2(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCc1Addr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_CC1_Matrix_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCc1Addr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_3: "
kint32 ct_im_r2y_111series_3(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaCc1CoefAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_CC1_Matrix_Coefficient_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaCc1CoefAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_4: "
kint32 ct_im_r2y_111series_4(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaYccAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_YCC_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaYccAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_5: "
kint32 ct_im_r2y_111series_5(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaYnrAddr	*addr;
	kulong	*ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_YNR_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaYnrAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_6: "
kint32 ct_im_r2y_111series_6(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEenrAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EENR_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEenrAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_7: "
kint32 ct_im_r2y_111series_7(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEghwAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EGHW_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEghwAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef 	CtImR2y111series_FUNC_NAME
#define 	CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_8: "
kint32 ct_im_r2y_111series_8(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEgmwAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EGMW_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEgmwAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

#undef CtImR2y111series_FUNC_NAME
#define CtImR2y111series_FUNC_NAME "ct_im_r2y_111series_9: "
kint32 ct_im_r2y_111series_9(CtImR2y111series *self, kuchar pipeNo)
{
#ifdef CO_MSG_PRINT_ON
	kint32 ercd;
#endif
	kuint32 loopcnt;
	const TImR2yCtrlRdmaEglwAddr *addr;
	kulong *ptAddr;

	DriverCommon_DDIM_PRINT(("%s\n", CtImR2y111series_FUNC_NAME));
#ifdef CO_MSG_PRINT_ON
	ercd = Im_R2Y_Get_RdmaAddr_EGLW_Cntl(pipeNo, &addr);
	DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "0x%x\n", ercd));
	ptAddr = (kulong*)addr;
	for(loopcnt = 0; loopcnt < sizeof(TImR2yCtrlRdmaEglwAddr) / sizeof(kulong); loopcnt++) {
		DriverCommon_DDIM_PRINT((CtImR2y111series_FUNC_NAME "address[%d] = 0x%lx\n", loopcnt, *ptAddr));
		ptAddr++;
	}
#endif

	return D_DDIM_OK;
}

CtImR2y111series *ct_im_r2y_111series_new(void)
{
	CtImR2y111series *self = k_object_new_with_private(CT_TYPE_IM_R2Y_111SERIES, sizeof(CtImR2y111seriesPrivate));

	return self;
}
