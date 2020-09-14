/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImMipi类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#include <stdlib.h>
#include <string.h>
#include "jdsdisp3a.h"
#include "ct_im_mipi.h"
#include "im_mipi.h"
#include "im_disp.h"
#include "ctimmipimain.h"

#include "ctimmipi.h"


G_DEFINE_TYPE(CtImMipi, ct_im_mipi, G_TYPE_OBJECT);
#define CT_IM_MIPI_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_MIPI, CtImMipiPrivate))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#ifdef CO_DEBUG_ON_PC
#define CtImMipi_D_MIPI_TEST_CMD_LEN		20
#endif	// CO_DEBUG_ON_PC

struct _CtImMipiPrivate
{

};

#ifdef CO_DEBUG_ON_PC
static gchar* S_GCMD_ARGV[25];
#endif	// CO_DEBUG_ON_PC
/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
#ifdef CO_DEBUG_ON_PC
static void 	ctImMipiSetCmd( gint cmdArgc, gchar* cmdArgv );
#endif	// CO_DEBUG_ON_PC

/*
*IMPL
*/
static void ct_im_mipi_class_init(CtImMipiClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImMipiPrivate));
}

static void ct_im_mipi_init(CtImMipi *self)
{
//	CtImMipiPrivate *priv = CT_IM_MIPI_GET_PRIVATE(self);
}

static void dispose_od(GObject *object)
{
//	CtImMipi *self = (CtImMipi*)object;
//	CtImMipiPrivate *priv = CT_IM_MIPI_GET_PRIVATE(self);
}

static void finalize_od(GObject *object)
{
//	CtImMipi *self = (CtImMipi*)object;
//	CtImMipiPrivate *priv = CT_IM_MIPI_GET_PRIVATE(self);
}

#ifdef CO_DEBUG_ON_PC
static void ctImMipiSetCmd( gint cmdArgc, gchar* cmdArgv )
{
	gint32 j;
	gint32 cmdPos = 0;

	for( j = 0; j < cmdArgc; j++ ) {
		S_GCMD_ARGV[ j ] = ( cmdArgv + ( cmdPos * CtImMipi_D_MIPI_TEST_CMD_LEN ) );
		cmdPos++;
	}
}
#endif	// CO_DEBUG_ON_PC
/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Local Method															*/
/*----------------------------------------------------------------------*/
void ct_im_mipi_pclk_on(void)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_On();
#endif	// CO_ACT_PCLOCK
}

/**
 * @brief	PCLK change to OFF.
 * @param	void.
 * @retval	void.
 */
void ct_im_mipi_pclk_off(void)
{
#ifdef CO_ACT_PCLOCK
	Im_DISP_APB_Clock_Off();
#endif	// CO_ACT_PCLOCK
}

void ct_im_mipi_cb(void)
{
	Ddim_Print((">> call ct_im_mipi_cb()\n"));
	return;
}

void ct_im_mipi_pcsim_test(CtImMipi* self)
{
#ifdef CO_DEBUG_ON_PC
	gint cmdCnt = 0;

	// MIPI Test command data
	gchar mipi_test_argv1[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "init", "0" };
	gchar mipi_test_argv2[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "pc", "1" };
//	gchar mipi_test_argv3[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "ulps", "enter", "0", "0" };
	gchar mipi_test_argv4_1[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "ulps", "enter", "1" };
	gchar mipi_test_argv4_2[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "ulps", "enter", "2" };
//	gchar mipi_test_argv5[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "ulps", "exit", "0", "0" };
	gchar mipi_test_argv6[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "ulps", "exit", "1" };
	gchar mipi_test_argv7[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "lane", "set", "0", "0" };
	gchar mipi_test_argv8[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "lane", "set", "1" };
	gchar mipi_test_argv9[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "lane", "get", "0", "0" };
	gchar mipi_test_argv10[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "lane", "get", "1" };
	gchar mipi_test_argv11[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "set", "0", "0" };
	gchar mipi_test_argv12[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "set", "1" };
	gchar mipi_test_argv13[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "get", "0", "0" };
	gchar mipi_test_argv14[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "get", "1" };
//	gchar mipi_test_argv15[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "update", "0" };
//	gchar mipi_test_argv16_1[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "update", "1" };
//	gchar mipi_test_argv16_2[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "dpi", "update", "2" };
	gchar mipi_test_argv17[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "tc", "set", "0", "0" };
	gchar mipi_test_argv18[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "tc", "set", "1" };
	gchar mipi_test_argv19[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "tc", "get", "0", "0" };
	gchar mipi_test_argv20[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "tc", "get", "1" };
//	gchar mipi_test_argv21[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "pt", "0", "1" };
	gchar mipi_test_argv22_1[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "pt", "0", "0" };
	gchar mipi_test_argv22_2[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "pt", "1" };
	gchar mipi_test_argv23[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "timer", "set", "0" };
	gchar mipi_test_argv24[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "mask", "set", "0" };
	gchar mipi_test_argv25[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "mask", "get", "0", "0" };
	gchar mipi_test_argv26[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "mask", "get", "1" };
	gchar mipi_test_argv27[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "cb", "set", "0", "0" };
	gchar mipi_test_argv28[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "cb", "set", "5", "0" };
	gchar mipi_test_argv29[][CtImMipi_D_MIPI_TEST_CMD_LEN] = { "immipi", "gint", "0" };

	Ddim_Print(("\n======== MIPI ========\n"));
	Ddim_Print((">> Test 1-1-1\n"));
	cmdCnt = (sizeof(mipi_test_argv1) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv1);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-2\n"));
	cmdCnt = (sizeof(mipi_test_argv2) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv2);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-3\n"));

	// Set

//	cmdCnt = (sizeof(mipi_test_argv3) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv3);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-4\n"));
	cmdCnt = (sizeof(mipi_test_argv4_1) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv4_1);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	cmdCnt = (sizeof(mipi_test_argv4_2) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv4_2);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-5\n"));
//	cmdCnt = (sizeof(mipi_test_argv5) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv5);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-6\n"));
	cmdCnt = (sizeof(mipi_test_argv6) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv6);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-7\n"));
	cmdCnt = (sizeof(mipi_test_argv7) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv7);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-8\n"));
	cmdCnt = (sizeof(mipi_test_argv8) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv8);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-9\n"));
	cmdCnt = (sizeof(mipi_test_argv9) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv9);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-10\n"));
	cmdCnt = (sizeof(mipi_test_argv10) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv10);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-11\n"));
	cmdCnt = (sizeof(mipi_test_argv11) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv11);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-12\n"));
	cmdCnt = (sizeof(mipi_test_argv12) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv12);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-13\n"));
	cmdCnt = (sizeof(mipi_test_argv13) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv13);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-14\n"));
	cmdCnt = (sizeof(mipi_test_argv14) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv14);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-15\n"));
//	cmdCnt = (sizeof(mipi_test_argv15) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv15);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-16\n"));
//	cmdCnt = (sizeof(mipi_test_argv16_1) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv16_1);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

//	cmdCnt = (sizeof(mipi_test_argv16_2) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv16_2);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-17\n"));
	cmdCnt = (sizeof(mipi_test_argv17) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv17);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-18\n"));
	cmdCnt = (sizeof(mipi_test_argv18) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv18);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-19\n"));
	cmdCnt = (sizeof(mipi_test_argv19) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv19);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-20\n"));
	cmdCnt = (sizeof(mipi_test_argv20) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv20);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-21\n"));
//	cmdCnt = (sizeof(mipi_test_argv21) / CtImMipi_D_MIPI_TEST_CMD_LEN);
//	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv21);
//	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-22\n"));
	cmdCnt = (sizeof(mipi_test_argv22_1) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv22_1);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);
	cmdCnt = (sizeof(mipi_test_argv22_2) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv22_2);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-23\n"));
	cmdCnt = (sizeof(mipi_test_argv23) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv23);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-24\n"));
	cmdCnt = (sizeof(mipi_test_argv24) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv24);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-25\n"));
	cmdCnt = (sizeof(mipi_test_argv25) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv25);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-26\n"));
	cmdCnt = (sizeof(mipi_test_argv26) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv26);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-27\n"));
	cmdCnt = (sizeof(mipi_test_argv27) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv27);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-28\n"));
	cmdCnt = (sizeof(mipi_test_argv28) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv28);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);

	Ddim_Print(("\n>> Test 1-1-29\n"));
	cmdCnt = (sizeof(mipi_test_argv29) / CtImMipi_D_MIPI_TEST_CMD_LEN);
	ctImMipiSetCmd(cmdCnt, (gchar*)mipi_test_argv29);
	Ct_Im_Mipi_Main(cmdCnt, S_GCMD_ARGV);
#endif	// CO_DEBUG_ON_PC
}

CtImMipi *ct_im_mipi_new(void) 
{
    CtImMipi *self = g_object_new(CT_TYPE_IM_MIPI, NULL);
    return self;
}
