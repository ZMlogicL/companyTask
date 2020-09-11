/*
*
*@Copyright (C) 2010-2020 贵阳高新网用软件有限公司
*@date : 2020-09-03
*@author : 杨文
*@brief : CtImHdmi
*@rely : klib.h
*@function : 按ETK规范抄写索喜源代码
*@version : 1.0.0 能正常上屏显示图像
*
*/


#ifndef __CT_IM_HDMI_H__
#define __CT_IM_HDMI_H__


#include <stdlib.h>
#include <string.h>
// #include "ct_im_hdmi.h"
#include "jdsdisp3a.h"
#include "im_hdmi.h"
#include "im_disp.h"
#include <klib.h>
#include "driver_common.h"
#include "ctimhdmi1.h"
#include "ctimhdmi2.h"


#define CT_TYPE_IM_HDMI                  (ct_im_hdmi_get_type())
#define CT_IM_HDMI(obj)                    (K_TYPE_CHECK_INSTANCE_CAST (obj, CtImHdmi)) 
#define CT_IS_IM_HDMI(obj)               (K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_IM_HDMI)) 


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_DEBUG_ON_PC
#define CtImHdmi_D_HDMI_TEST_CMD_LEN		20
#endif	// CO_DEBUG_ON_PC

#ifdef CO_DEBUG_ON_PC
static char* gCmdArgv[25];
#endif	// CO_DEBUG_ON_PC


typedef struct _CtImHdmi CtImHdmi;
typedef struct _CtImHdmiPrivate CtImHdmiPrivate;

struct _CtImHdmi 
{
	KObject parent;
};


KConstType ct_im_hdmi_get_type(void);
CtImHdmi* ct_im_hdmi_new(void);
CtImHdmi* ct_im_hdmi_get(void);


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
extern	VOID	ct_im_hdmi_main(int argc, char** argv);
extern	VOID	Ct_Im_Hdmi_PCSim_Test(VOID);


// extern const T_IM_HDMI_CSC_COEF S_GCT_IM_HDMI_CSC_MATRIX[D_IM_HDMI_CSC_CONF_COLUMN_NUM][D_IM_HDMI_CSC_CONF_ROW_NUM];
VOID ct_im_hdmi_main( INT32 argc, char** argv );
// VOID ct_im_hdmi_pclk_on(VOID);
// VOID ct_im_hdmi_pclk_off(VOID);


#endif /* __CT_IM_HDMI_H__ */
