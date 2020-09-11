/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :董如利
*@brief               :sns 索喜rtos
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
#include<ct_dd_top.h>
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"

#include "ctddtopfrist.h"


K_TYPE_DEFINE_WITH_PRIVATE(CtDdTopFrist, ct_dd_top_frist);
#define CT_DD_TOP_FRIST_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtDdTopFristPrivate,CT_TYPE_DD_TOP_FRIST))


struct _CtDdTopFristPrivate
{
	kint32 seqNo;
};
/****************
* DECLS
*/
static void 			ct_dd_top_frist_constructor(CtDdTopFrist *self);
static void 			ct_dd_top_frist_destructor(CtDdTopFrist *self);
/****************
* IMPL
*/
static void ct_dd_top_frist_constructor(CtDdTopFrist *self) 
{
	CtDdTopFristPrivate *priv = CT_DD_TOP_FRIST_GET_PRIVATE(self);
    priv->seqNo = 0;
}

static void ct_dd_top_frist_destructor(CtDdTopFrist *self) 
{
//	CtDdTopFristPrivate *priv = CT_DD_TOP_FRIST_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_dd_top_frist_set_seq_no(CtDdTopFrist *self,kint32 seqNo)
{
    CtDdTopFristPrivate *priv = CT_DD_TOP_FRIST_GET_PRIVATE(self);
    priv->seqNo = seqNo;
}

kint32 ct_dd_top_frist_get_seq_no(CtDdTopFrist *self)
{
    CtDdTopFristPrivate *priv = CT_DD_TOP_FRIST_GET_PRIVATE(self);
    return priv->seqNo;
}

void ct_dd_top_frist_pc_test_main(CtDdTopFrist *self)
{
    CtDdTopFristPrivate *priv = CT_DD_TOP_FRIST_GET_PRIVATE(self);

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_emmcclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock EMMCCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock EMMCCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock EMMCCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock EMMCCLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_nfclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFCLK 8");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_uhs2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS2CLK 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_uhs1clk2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK2 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_uhs1clk1()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK1 8");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_uhs1clk0()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock UHS1CLK0 8");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_rclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RCLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_rawclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RAWCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RAWCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RAWCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RAWCLK 2");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_hifclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HIFCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HIFCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HIFCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HIFCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HIFCLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_mifclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MIFCLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_ipuclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUCLK 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_iputmeclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPUTMECLK 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_gpuclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GPUCLK 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_jpegclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock JPGCLK 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_elaclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ELACLK 6");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-01-%03d : DdTopone_GET_CLKSEL3_HEVENCSEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCSEL");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCSEL 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCSEL 1");

// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
	Ddim_Print(("*** [CT] 01-01-%03d : DdTopone_GET_CLKSEL3_PIPESEL()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PIPESEL");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PIPESEL 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PIPESEL 1");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_senclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENCLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_senmskclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENMSKCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENMSKCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SENMSKCLK 1");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_iipclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IIPCLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_pasclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PASCLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_ippclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock IPPCLK 8");

// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_pxfclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PXFCLK 6");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_hevencclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HEVENCCLK 5");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_vdfclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock VDFCLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_sro1clk_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_r2y1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y1CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_ltm1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 16");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 24");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM1CLK 32");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_b2r1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 16");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R1CLK 24");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_cnr1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR1CLK 8");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_sro1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_b2b1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B1CLK 16");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_ltmrbk1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK1CLK 16");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_sro2clk_2()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO1CLK_2 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topone_get_r2y2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock R2Y2CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_ltm2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 16");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 24");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTM2CLK 32");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_b2r2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 16");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2R2CLK 24");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_cnr2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock CNR2CLK 8");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_sro2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SRO2CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_b2b2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock B2B2CLK 16");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_ltmrbk2clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock LTMRBK2CLK 16");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_apclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 9");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock APCLK 12");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_auclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock AUCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock AUCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock AUCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock AUCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock AUCLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_top_get_spiclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SPICLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SPICLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SPICLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SPICLK 2");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_dspclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock DSPCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock DSPCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock DSPCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock DSPCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock DSPCLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_aclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK 1");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_aclkEXS()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLKEXS");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLKEXS 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLKEXS 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLKEXS 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLKEXS 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_hclkBMH()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLKBMH");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLKBMH 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLKBMH 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_hclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLK 7");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock HCLK 15");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_pclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PCLK 15");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock PCLK 31");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_mclk400()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK400");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK400 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK400 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_mclk200()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK200");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK200 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MCLK200 7");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_aclk400()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK400");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK400 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK400 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_shdrclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 0");
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES1_HARDWARE BEGIN ---
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 6");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 7");
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---
// --- REMOVE_ES3_HARDWARE BEGIN ---
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 8");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 9");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 10");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 11");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 12");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 13");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 14");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock SHDRCLK 15");
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES3_HARDWARE
// --- REMOVE_ES_COMPILE_OPT END ---

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_ribclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock RIBCLK 4");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_nfbchclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFBCHCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFBCHCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock NFBCHCLK 1");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_meclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MECLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MECLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MECLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MECLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock MECLK 3");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_fpt1clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT1CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_fpt0clk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 2");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 3");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 4");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 5");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock FPT0CLK 6");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_topthree_get_gyroclk()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GYROCLK");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GYROCLK 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GYROCLK 1");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock GYROCLK 2");

	Ddim_Print(("*** [CT] 01-01-%03d : dd_toptwo_get_aclk300()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK300");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK300 0");
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop clock get_clock ACLK300 1");

	priv->seqNo = 0;
	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll00()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll00 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll00()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll00 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll01()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll01 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll01()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll01 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll02()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll02 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll02()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll02 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll03()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll03 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll03()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll03 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll04()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll04 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll04()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll04 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll05()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll05 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll05()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll05 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll05A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll05a start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll05A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll05a stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll06()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll06 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll06()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll06 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll07()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll07 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll07()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll07 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll08()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll08 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll08()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll08 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll10()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll10()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll10A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10a start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll10A()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10a stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_pll11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll11 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_pll11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll11 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll00()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll00 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll00()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll00 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll01()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll01 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll01()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll01 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll02()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll02 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll02()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll02 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll10()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll10()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll10 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll11 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll11()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll11 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_start_ddr_pll12()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll12 start");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll12()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll pll12 stop");

	Ddim_Print(("*** [CT] 01-02-%03d : dd_topthree_stop_ddr_pll12()\n", priv->seqNo++));
	ct_dd_top_wrap_pctest(((CtDdTopParent*)self)->ctDdTopWrap,"ddtop pll err");
}

CtDdTopFrist* ct_dd_top_frist_new(void) 
{
    CtDdTopFrist *self = k_object_new_with_private(CT_TYPE_DD_TOP_FRIST, sizeof(CtDdTopFristPrivate));
    return self;
}
