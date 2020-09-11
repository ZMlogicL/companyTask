/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
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
#include "../../DeviceDriver/LSITop/src/ddtop.h"
#include "../../DeviceDriver/LSITop/src/ddtopfour.h"
#include "../../DeviceDriver/LSITop/src/ddtopone.h"
#include "../../DeviceDriver/LSITop/src/ddtopthree.h"
#include "../../DeviceDriver/LSITop/src/ddtoptwo.h"
#include "ctclockfrequencyend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockFrequencyEnd, ct_clock_frequency_end);
#define CT_CLOCK_FREQUENCY_END_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockFrequencyEndPrivate,CT_TYPE_CLOCK_FREQUENCY_END))

struct _CtClockFrequencyEndPrivate
{
	kint a;
};
/****************
* DECLS
*/
static void 						ct_clock_frequency_end_constructor(CtClockFrequencyEnd *self);
static void 						ct_clock_frequency_end_destructor(CtClockFrequencyEnd *self);
/****************
* IMPL
*/
static void ct_clock_frequency_end_constructor(CtClockFrequencyEnd *self) 
{
	// CtClockFrequencyEndPrivate *priv = CT_CLOCK_FREQUENCY_END_GET_PRIVATE(self);
}

static void ct_clock_frequency_end_destructor(CtClockFrequencyEnd *self) 
{
	// CtClockFrequencyEndPrivate *priv = CT_CLOCK_FREQUENCY_END_GET_PRIVATE(self);
}
/****************
* PUBLIC
*/
void ct_clock_frequency_end_get_run(CtClockFrequencyEnd *self)
{
    kulong val;
	kint i;
    
    if (0 == strcmp(((CtDdParameter *)self)->argv[3], "AUCLK"))
    {
        Ddim_Print(("0:36.864MHz \n"));
        Ddim_Print(("1:22.5792MHz \n"));
        Ddim_Print(("2:24.576MHz \n"));
        Ddim_Print(("3:8.192MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL8_AUCLK(val);

            kulong clock = dd_top_get_auclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_auclk=%ld\n",
                		val, DdTopone_GET_CLKSEL8_AUCLK(), dd_top_get_auclk()));
            }
        }
        else
        {
            for (i = 0; i < 4; i++)
            {
                DdTopone_SET_CLKSEL8_AUCLK(i);

                kulong clock = dd_top_get_auclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_auclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL8_AUCLK(), dd_top_get_auclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SPICLK"))
    {
        Ddim_Print(("0:216MHz \n"));
        Ddim_Print(("1:108MHz \n"));
        Ddim_Print(("2:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL8_SPICLK(val);

            kulong clock = dd_top_get_spiclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_spiclk=%ld\n",
                		val, DdTopone_GET_CLKSEL8_SPICLK(), dd_top_get_spiclk()));
            }
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                DdTopone_SET_CLKSEL8_SPICLK(i);

                kulong clock = dd_top_get_spiclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_spiclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL8_SPICLK(), dd_top_get_spiclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "DSPCLK"))
    {
        Ddim_Print(("0:400MHz \n"));
        Ddim_Print(("1:266.666MHz \n"));
        Ddim_Print(("2:200MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL8_DSPCLK(val);

            kulong clock = dd_toptwo_get_dspclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_dspclk=%ld\n",
                		val, DdTopone_GET_CLKSEL8_DSPCLK(), dd_toptwo_get_dspclk()));
            }
        }
        else
        {
            for (i = 0; i < 4; i++)
            {
                DdTopone_SET_CLKSEL8_DSPCLK(i);

                kulong clock = dd_toptwo_get_dspclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_dspclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL8_DSPCLK(), dd_toptwo_get_dspclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "ACLK"))
    {
        Ddim_Print(("0:200MHz \n"));
        Ddim_Print(("1:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL9_ACLK(val);

            kulong clock = dd_toptwo_get_aclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_aclk=%ld\n",
                		val, DdTopone_GET_CLKSEL9_ACLK(), dd_toptwo_get_aclk()));
            }
        }
        else
        {
            for (i = 0; i < 8; i++)
            {
                DdTopone_SET_CLKSEL9_ACLK(i);

                kulong clock = dd_toptwo_get_aclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_aclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL9_ACLK(), dd_toptwo_get_aclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "ACLKEXS"))
    {
        Ddim_Print(("3:200MHz \n"));
        Ddim_Print(("4:160MHz \n"));
        Ddim_Print(("5:133.333MHz \n"));
        Ddim_Print(("7:50MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL9_ACLKEXS(val);

            kulong clock = dd_toptwo_get_aclkEXS();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_aclkEXS=%ld\n",
                		val, DdTopone_GET_CLKSEL9_ACLKEXS(), dd_toptwo_get_aclkEXS()));
            }
        }
        else
        {
            for (i = 3; i < 8; i++)
            {
                DdTopone_SET_CLKSEL9_ACLKEXS(i);

                kulong clock = dd_toptwo_get_aclkEXS();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_aclkEXS=%ld\n",
                    		i, DdTopone_GET_CLKSEL9_ACLKEXS(), dd_toptwo_get_aclkEXS()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "HCLKBMH"))
    {
        Ddim_Print(("3:200MHz \n"));
        Ddim_Print(("7:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL9_HCLKBMH(val);

            kulong clock = dd_toptwo_get_hclkBMH();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_hclkBMH=%ld\n",
                		val, DdTopone_GET_CLKSEL9_HCLKBMH(), dd_toptwo_get_hclkBMH()));
            }
        }
        else
        {
            for (i = 3; i < 8; i++)
            {
                DdTopone_SET_CLKSEL9_HCLKBMH(i);

                kulong clock = dd_toptwo_get_hclkBMH();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_hclkBMH=%ld\n",
                    		i, DdTopone_GET_CLKSEL9_HCLKBMH(), dd_toptwo_get_hclkBMH()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "HCLK"))
    {
        Ddim_Print(("7:100MHz \n"));
        Ddim_Print(("15:50MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL9_HCLK(val);

            kulong clock = dd_toptwo_get_hclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_hclk=%ld\n",
                		val, DdTopone_GET_CLKSEL9_HCLK(), dd_toptwo_get_hclk()));
            }
        }
        else
        {
            for (i = 7; i < 16; i++)
            {
                DdTopone_SET_CLKSEL9_HCLK(i);

                kulong clock = dd_toptwo_get_hclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_hclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL9_HCLK(), dd_toptwo_get_hclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "PCLK"))
    {
        Ddim_Print(("15:50MHz \n"));
        Ddim_Print(("31:25MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL9_PCLK(val);

            kulong clock = dd_toptwo_get_pclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_pclk=%ld\n",
                		val, DdTopone_GET_CLKSEL9_PCLK(), dd_toptwo_get_pclk()));
            }
        }
        else
        {
            for (i = 15; i < 32; i++)
            {
                DdTopone_SET_CLKSEL9_PCLK(i);

                kulong clock = dd_toptwo_get_pclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_pclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL9_PCLK(), dd_toptwo_get_pclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "MCLK400"))
    {
        Ddim_Print(("1:400MHz \n"));
        Ddim_Print(("3:200MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL10_MCLK400(val);

            kulong clock = dd_toptwo_get_mclk400();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_mclk400=%ld\n",
                		val, DdTopone_GET_CLKSEL10_MCLK400(), dd_toptwo_get_mclk400()));
            }
        }
        else
        {
            for (i = 1; i < 4; i++)
            {
                DdTopone_SET_CLKSEL10_MCLK400(i);

                kulong clock = dd_toptwo_get_mclk400();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_mclk400=%ld\n",
                    		i, DdTopone_GET_CLKSEL10_MCLK400(), dd_toptwo_get_mclk400()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "MCLK200"))
    {
        Ddim_Print(("3:200MHz \n"));
        Ddim_Print(("7:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL10_MCLK200(val);

            kulong clock = dd_toptwo_get_mclk200();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_mclk200=%ld\n",
                		val, DdTopone_GET_CLKSEL10_MCLK200(), dd_toptwo_get_mclk200()));
            }
        }
        else
        {
            for (i = 3; i < 8; i++)
            {
                DdTopone_SET_CLKSEL10_MCLK200(i);

                kulong clock = dd_toptwo_get_mclk200();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_mclk200=%ld\n",
                    		i, DdTopone_GET_CLKSEL10_MCLK200(), dd_toptwo_get_mclk200()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "ACLK400"))
    {
        Ddim_Print(("1:400MHz \n"));
        Ddim_Print(("3:200MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL10_ACLK400(val);

            kulong clock = dd_toptwo_get_aclk400();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_aclk400=%ld\n",
                		val, DdTopone_GET_CLKSEL10_ACLK400(), dd_toptwo_get_aclk400()));
            }
        }
        else
        {
            for (i = 1; i < 4; i++)
            {
                DdTopone_SET_CLKSEL10_ACLK400(i);

                kulong clock = dd_toptwo_get_aclk400();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_aclk400=%ld\n",
                    		i, DdTopone_GET_CLKSEL10_ACLK400(), dd_toptwo_get_aclk400()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SHDRCLK"))
    {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
        // --- REMOVE_ES_COMPILE_OPT END ---
        // --- REMOVE_ES1_HARDWARE BEGIN ---
        Ddim_Print(("0:400MHz \n"));
        Ddim_Print(("1:266.666MHz \n"));
        Ddim_Print(("2:200MHz \n"));
        Ddim_Print(("3:160MHz \n"));
        Ddim_Print(("4:133.333MHz \n"));
        Ddim_Print(("5:100MHz \n"));
        Ddim_Print(("6:80MHz \n"));
        Ddim_Print(("7:66.666MHz \n"));
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
        // --- REMOVE_ES_COMPILE_OPT END ---
        // --- REMOVE_ES3_HARDWARE BEGIN ---
        Ddim_Print(("0:432MHz \n"));
        Ddim_Print(("8:400MHz \n"));
        Ddim_Print(("9:266.666MHz \n"));
        Ddim_Print(("10:200MHz \n"));
        Ddim_Print(("11:160MHz \n"));
        Ddim_Print(("12:133.333MHz \n"));
        Ddim_Print(("13:100MHz \n"));
        Ddim_Print(("14:80MHz \n"));
        Ddim_Print(("15:66.666MHz \n"));
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif		// CO_ES3_HARDWARE
        // --- REMOVE_ES_COMPILE_OPT END ---
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_SHDRCLK(val);

            kulong clock = dd_toptwo_get_shdrclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_shdrclk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_SHDRCLK(), dd_toptwo_get_shdrclk()));
            }
        }
        else
        {
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
            // --- REMOVE_ES_COMPILE_OPT END ---
            // --- REMOVE_ES1_HARDWARE BEGIN ---
            for (i = 0; i < 8; i++)
            {
                DdTopone_SET_CLKSEL12_SHDRCLK(i);

                kulong clock = dd_toptwo_get_shdrclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_shdrclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_SHDRCLK(), dd_toptwo_get_shdrclk()));
                }
            }
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
            // --- REMOVE_ES_COMPILE_OPT END ---
            // --- REMOVE_ES3_HARDWARE BEGIN ---
            for (i = 0; i < 16; i++)
            {
                DdTopone_SET_CLKSEL12_SHDRCLK(i);

                kulong clock = dd_toptwo_get_shdrclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_shdrclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_SHDRCLK(), dd_toptwo_get_shdrclk()));
                }
            }
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif			// CO_ES3_HARDWARE
            // --- REMOVE_ES_COMPILE_OPT END ---
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "RIBCLK"))
    {
        Ddim_Print(("0:466.666MHz \n"));
        Ddim_Print(("1:350MHz \n"));
        Ddim_Print(("2:233.333MHz \n"));
        Ddim_Print(("3:116.666MHz \n"));
        Ddim_Print(("4:58.333MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_RIBCLK(val);

            kulong clock = dd_topthree_get_ribclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_ribclk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_RIBCLK(), dd_topthree_get_ribclk()));
            }
        }
        else
        {
            for (i = 0; i < 5; i++)
            {
                DdTopone_SET_CLKSEL12_RIBCLK(i);

                kulong clock = dd_topthree_get_ribclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_ribclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_RIBCLK(), dd_topthree_get_ribclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "NFBCHCLK"))
    {
        Ddim_Print(("0:200MHz \n"));
        Ddim_Print(("1:100MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_NFBCHCLK(val);

            kulong clock = dd_topthree_get_nfbchclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_nfbchclk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_NFBCHCLK(), dd_topthree_get_nfbchclk()));
            }
        }
        else
        {
            for (i = 0; i < 2; i++)
            {
                DdTopone_SET_CLKSEL12_NFBCHCLK(i);

                kulong clock = dd_topthree_get_nfbchclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_nfbchclkK=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_NFBCHCLK(), dd_topthree_get_nfbchclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "MECLK"))
    {
        Ddim_Print(("0:466.666MHz \n"));
        Ddim_Print(("1:233.333MHz \n"));
        Ddim_Print(("2:116.666MHz \n"));
        Ddim_Print(("3:58.333MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_MECLK(val);

            kulong clock = dd_topthree_get_meclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_meclk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_MECLK(), dd_topthree_get_meclk()));
            }
        }
        else
        {
            for (i = 0; i < 4; i++)
            {
                DdTopone_SET_CLKSEL12_MECLK(i);

                kulong clock = dd_topthree_get_meclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_meclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_MECLK(), dd_topthree_get_meclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "FPT1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_FPT1CLK(val);

            kulong clock = dd_topthree_get_fpt1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_fpt1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_FPT1CLK(), dd_topthree_get_fpt1clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL12_FPT1CLK(i);

                kulong clock = dd_topthree_get_fpt1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_fpt1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_FPT1CLK(), dd_topthree_get_fpt1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "FPT0CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_FPT0CLK(val);

            kulong clock = dd_topthree_get_fpt0clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_fpt0clk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_FPT0CLK(), dd_topthree_get_fpt0clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL12_FPT0CLK(i);

                kulong clock = dd_topthree_get_fpt0clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_fpt0clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_FPT0CLK(), dd_topthree_get_fpt0clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "GYROCLK"))
    {
        Ddim_Print(("0:100MHz \n"));
        Ddim_Print(("1:32MHz \n"));
        Ddim_Print(("2:2MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_GYROCLK(val);

            kulong clock = dd_topthree_get_gyroclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topthree_get_gyroclk=%ld\n",
                		val, DdTopone_GET_CLKSEL12_GYROCLK(), dd_topthree_get_gyroclk()));
            }
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                DdTopone_SET_CLKSEL12_GYROCLK(i);

                kulong clock = dd_topthree_get_gyroclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topthree_get_gyroclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_GYROCLK(), dd_topthree_get_gyroclk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "ACLK300"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL12_ACLK300(val);

            kulong clock = dd_toptwo_get_aclk300();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_toptwo_get_aclk300=%ld\n",
                		val, DdTopone_GET_CLKSEL12_ACLK300(), dd_toptwo_get_aclk300()));
            }
        }
        else
        {
            for (i = 0; i < 2; i++)
            {
                DdTopone_SET_CLKSEL12_ACLK300(i);

                kulong clock = dd_toptwo_get_aclk300();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_toptwo_get_aclk300=%ld\n",
                    		i, DdTopone_GET_CLKSEL12_ACLK300(), dd_toptwo_get_aclk300()));
                }
            }
        }
    }
    else
    {
        Ddim_Print(("please check 3rd parameter!!\n"));
    }
}

CtClockFrequencyEnd* ct_clock_frequency_end_new(void) 
{
    CtClockFrequencyEnd *self = k_object_new_with_private(CT_TYPE_CLOCK_FREQUENCY_END,
    		sizeof(CtClockFrequencyEndPrivate));
    return self;
}
