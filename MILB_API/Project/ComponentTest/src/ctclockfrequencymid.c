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
#include "ctclockfrequencymid.h"
#include "ctclockfrequencyend.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockFrequencyMid, ct_clock_frequency_mid);
#define CT_CLOCK_FREQUENCY_MID_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockFrequencyMidPrivate,CT_TYPE_CLOCK_FREQUENCY_MID))

struct _CtClockFrequencyMidPrivate
{
    CtClockFrequencyEnd*  ctClockFrequencyEnd;
};
/****************
* DECLS
*/
static void 						ct_clock_frequency_mid_constructor(CtClockFrequencyMid *self);
static void 						ct_clock_frequency_mid_destructor(CtClockFrequencyMid *self);
/****************
* IMPL
*/
static void ct_clock_frequency_mid_constructor(CtClockFrequencyMid *self) 
{
	CtClockFrequencyMidPrivate *priv = CT_CLOCK_FREQUENCY_MID_GET_PRIVATE(self);
    priv->ctClockFrequencyEnd = ct_clock_frequency_end_new();
}

static void ct_clock_frequency_mid_destructor(CtClockFrequencyMid *self) 
{
	CtClockFrequencyMidPrivate *priv = CT_CLOCK_FREQUENCY_MID_GET_PRIVATE(self);
    k_object_unref(priv->ctClockFrequencyEnd);
}
/****************
* PUBLIC
*/
void ct_clock_frequency_mid_get_run(CtClockFrequencyMid *self)
{
    CtClockFrequencyMidPrivate *priv = CT_CLOCK_FREQUENCY_MID_GET_PRIVATE(self);
    kulong val;
	kint i;

	if (0 == strcmp(((CtDdParameter *)self)->argv[3], "VDFCLK"))
		{
			Ddim_Print(("0:700MHz \n"));
			Ddim_Print(("1:280MHz \n"));
			Ddim_Print(("2:155.555MHz \n"));
			Ddim_Print(("4:533.333MHz \n"));
			Ddim_Print(("5:400MHz \n"));
			Ddim_Print(("6:100MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_VDFCLK(val);

				kulong clock = dd_topone_get_vdfclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_vdfclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_VDFCLK(), dd_topone_get_vdfclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL3_VDFCLK(i);

					kulong clock = dd_topone_get_vdfclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_vdfclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_VDFCLK(), dd_topone_get_vdfclk()));
					}
				}
			}
		}
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SRO1CLK_2"))
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
            DdTopone_SET_CLKSEL4_SRO1CLK_2(val);

            kulong clock = dd_topone_get_sro1clk_2();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_sro1clk_2=%ld\n",
                		val, DdTopone_GET_CLKSEL4_SRO1CLK_2(), dd_topone_get_sro1clk_2()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL4_SRO1CLK_2(i);

                kulong clock = dd_topone_get_sro1clk_2();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_sro1clk_2=%ld\n",
                    		i, DdTopone_GET_CLKSEL4_SRO1CLK_2(), dd_topone_get_sro1clk_2()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "R2Y1CLK"))
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
            DdTopone_SET_CLKSEL4_R2Y1CLK(val);

            kulong clock = dd_topone_get_r2y1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_r2y1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL4_R2Y1CLK(), dd_topone_get_r2y1clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL4_R2Y1CLK(i);

                kulong clock = dd_topone_get_r2y1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_r2y1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL4_R2Y1CLK(), dd_topone_get_r2y1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "LTM1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO1CLK\n"));
        Ddim_Print(("16:SRO1CLK_2\n"));
        Ddim_Print(("24:B2B1CLK\n"));
        Ddim_Print(("32:B2R1CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL4_LTM1CLK(val);

            kulong clock = dd_topone_get_ltm1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_ltm1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL4_LTM1CLK(), dd_topone_get_ltm1clk()));
            }
        }
        else
        {
            for (i = 0; i < 33; i++)
            {
                DdTopone_SET_CLKSEL4_LTM1CLK(i);

                kulong clock = dd_topone_get_ltm1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_ltm1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL4_LTM1CLK(), dd_topone_get_ltm1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "B2R1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO1CLK\n"));
        Ddim_Print(("16:SRO1CLK_2\n"));
        Ddim_Print(("24:B2B1CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL4_B2R1CLK(val);

            kulong clock = dd_topone_get_b2r1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_b2r1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL4_B2R1CLK(), dd_topone_get_b2r1clk()));
            }
        }
        else
        {
            for (i = 0; i < 25; i++)
            {
                DdTopone_SET_CLKSEL4_B2R1CLK(i);

                kulong clock = dd_topone_get_b2r1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_b2r1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL4_B2R1CLK(), dd_topone_get_b2r1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "CNR1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:R2Y1CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL4_CNR1CLK(val);

            kulong clock = dd_topone_get_cnr1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_cnr1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL4_CNR1CLK(), dd_topone_get_cnr1clk()));
            }
        }
        else
        {
            for (i = 0; i < 9; i++)
            {
                DdTopone_SET_CLKSEL4_CNR1CLK(i);

                kulong clock = dd_topone_get_cnr1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_cnr1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL4_CNR1CLK(), dd_topone_get_cnr1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SRO1CLK"))
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
            DdTopone_SET_CLKSEL5_SRO1CLK(val);

            kulong clock = dd_topone_get_sro1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_sro1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL5_SRO1CLK(), dd_topone_get_sro1clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL5_SRO1CLK(i);

                kulong clock = dd_topone_get_sro1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_sro1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL5_SRO1CLK(), dd_topone_get_sro1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "B2B1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO1CLK\n"));
        Ddim_Print(("16:SRO1CLK_2\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL5_B2B1CLK(val);

            kulong clock = dd_topone_get_b2b1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_b2b1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL5_B2B1CLK(), dd_topone_get_b2b1clk()));
            }
        }
        else
        {
            for (i = 0; i < 17; i++)
            {
                DdTopone_SET_CLKSEL5_B2B1CLK(i);

                kulong clock = dd_topone_get_b2b1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_b2b1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL5_B2B1CLK(), dd_topone_get_b2b1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "LTMRBK1CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO1CLK\n"));
        Ddim_Print(("16:SRO1CLK_2\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL5_LTMRBK1CLK(val);

            kulong clock = dd_topone_get_ltmrbk1clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_ltmrbk1clk=%ld\n",
                		val, DdTopone_GET_CLKSEL5_LTMRBK1CLK(), dd_topone_get_ltmrbk1clk()));
            }
        }
        else
        {
            for (i = 0; i < 17; i++)
            {
                DdTopone_SET_CLKSEL5_LTMRBK1CLK(i);

                kulong clock = dd_topone_get_ltmrbk1clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_ltmrbk1clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL5_LTMRBK1CLK(), dd_topone_get_ltmrbk1clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SRO2CLK_2"))
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
            DdTopone_SET_CLKSEL6_SRO2CLK_2(val);

            kulong clock = dd_top_get_sro2clk_2();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_sro2clk_2=%ld\n",
                		val, DdTopone_GET_CLKSEL6_SRO2CLK_2(), dd_top_get_sro2clk_2()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL6_SRO2CLK_2(i);

                kulong clock = dd_top_get_sro2clk_2();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_sro2clk_2=%ld\n",
                    		i, DdTopone_GET_CLKSEL6_SRO2CLK_2(), dd_top_get_sro2clk_2()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "R2Y2CLK"))
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
            DdTopone_SET_CLKSEL6_R2Y2CLK(val);

            kulong clock = dd_topone_get_r2y2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_topone_get_r2y2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL6_R2Y2CLK(), dd_topone_get_r2y2clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL6_R2Y2CLK(i);

                kulong clock = dd_topone_get_r2y2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_topone_get_r2y2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL6_R2Y2CLK(), dd_topone_get_r2y2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "LTM2CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO2CLK\n"));
        Ddim_Print(("16:SRO2CLK_2\n"));
        Ddim_Print(("24:B2B2CLK\n"));
        Ddim_Print(("32:B2R2CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL6_LTM2CLK(val);

            kulong clock = dd_top_get_ltm2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_ltm2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL6_LTM2CLK(), dd_top_get_ltm2clk()));
            }
        }
        else
        {
            for (i = 0; i < 33; i++)
            {
                DdTopone_SET_CLKSEL6_LTM2CLK(i);

                kulong clock = dd_top_get_ltm2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_ltm2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL6_LTM2CLK(), dd_top_get_ltm2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "B2R2CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO2CLK\n"));
        Ddim_Print(("16:SRO2CLK_2\n"));
        Ddim_Print(("24:B2B2CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL6_B2R2CLK(val);

            kulong clock = dd_top_get_b2r2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_b2r2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL6_B2R2CLK(), dd_top_get_b2r2clk()));
            }
        }
        else
        {
            for (i = 0; i < 25; i++)
            {
                DdTopone_SET_CLKSEL6_B2R2CLK(i);

                kulong clock = dd_top_get_b2r2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_b2r2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL6_B2R2CLK(), dd_top_get_b2r2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "CNR2CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:R2Y2CLK\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL6_CNR2CLK(val);

            kulong clock = dd_top_get_cnr2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_cnr2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL6_CNR2CLK(), dd_top_get_cnr2clk()));
            }
        }
        else
        {
            for (i = 0; i < 9; i++)
            {
                DdTopone_SET_CLKSEL6_CNR2CLK(i);

                kulong clock = dd_top_get_cnr2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_cnr2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL6_CNR2CLK(), dd_top_get_cnr2clk()));
                }
            }
        }
    }
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
    // --- REMOVE_ES_COMPILE_OPT END ---
    // --- REMOVE_ES3_HARDWARE BEGIN ---
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "MIPISEL"))
    {
        Ddim_Print(("0:PLL08 \n"));
        Ddim_Print(("1:PLL08/4 \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL7_MIPISEL(val);

            Ddim_Print(("%02lu:\t DdTopone_GET_CLKSEL7_MIPISEL=%d\n", val, DdTopone_GET_CLKSEL7_MIPISEL()));
        }
        else
        {
            for (i = 0; i < 2; i++)
            {
                DdTopone_SET_CLKSEL7_MIPISEL(i);

                Ddim_Print(("%02d:\t DdTopone_GET_CLKSEL7_MIPISEL=%d\n", i, DdTopone_GET_CLKSEL7_MIPISEL()));
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "PDM0SEL"))
    {
        Ddim_Print(("0:PDMCLK \n"));
        Ddim_Print(("1:AUCLK \n"));
        Ddim_Print(("2:AUCLK/2 \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL7_PDM0SEL(val);

            Ddim_Print(("%02lu:\t DdTopone_GET_CLKSEL7_PDM0SEL=%d\n", val, DdTopone_GET_CLKSEL7_PDM0SEL()));
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                DdTopone_SET_CLKSEL7_PDM0SEL(i);

                Ddim_Print(("%02d:\t DdTopone_GET_CLKSEL7_PDM0SEL=%d\n", i, DdTopone_GET_CLKSEL7_PDM0SEL()));
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "PDM1SEL"))
    {
        Ddim_Print(("0:PDMCLK \n"));
        Ddim_Print(("1:AUCLK \n"));
        Ddim_Print(("2:AUCLK/2 \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL7_PDM1SEL(val);

            Ddim_Print(("%02lu:\t DdTopone_GET_CLKSEL7_PDM1SEL=%d\n", val, DdTopone_GET_CLKSEL7_PDM1SEL()));
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                DdTopone_SET_CLKSEL7_PDM1SEL(i);

                Ddim_Print(("%02d:\t DdTopone_GET_CLKSEL7_PDM1SEL=%d\n", i, DdTopone_GET_CLKSEL7_PDM1SEL()));
            }
        }
    }
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
    // --- REMOVE_ES_COMPILE_OPT END ---
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SRO2CLK"))
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
            DdTopone_SET_CLKSEL7_SRO2CLK(val);

            kulong clock = dd_top_get_sro2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_sro2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL7_SRO2CLK(), dd_top_get_sro2clk()));
            }
        }
        else
        {
            for (i = 0; i < 7; i++)
            {
                DdTopone_SET_CLKSEL7_SRO2CLK(i);

                kulong clock = dd_top_get_sro2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_sro2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL7_SRO2CLK(), dd_top_get_sro2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "B2B2CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO2CLK\n"));
        Ddim_Print(("16:SRO2CLK_2\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL7_B2B2CLK(val);

            kulong clock = dd_top_get_b2b2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_b2b2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL7_B2B2CLK(), dd_top_get_b2b2clk()));
            }
        }
        else
        {
            for (i = 0; i < 17; i++)
            {
                DdTopone_SET_CLKSEL7_B2B2CLK(i);

                kulong clock = dd_top_get_b2b2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_b2b2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL7_B2B2CLK(), dd_top_get_b2b2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "LTMRBK2CLK"))
    {
        Ddim_Print(("0:300MHz \n"));
        Ddim_Print(("1:200MHz \n"));
        Ddim_Print(("2:150MHz \n"));
        Ddim_Print(("3:100MHz \n"));
        Ddim_Print(("4:75MHz \n"));
        Ddim_Print(("5:60MHz \n"));
        Ddim_Print(("6:50MHz \n"));
        Ddim_Print(("8:SRO2CLK\n"));
        Ddim_Print(("16:SRO2CLK_2\n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL7_LTMRBK2CLK(val);

            kulong clock = dd_top_get_ltmrbk2clk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_ltmrbk2clk=%ld\n",
                		val, DdTopone_GET_CLKSEL7_LTMRBK2CLK(), dd_top_get_ltmrbk2clk()));
            }
        }
        else
        {
            for (i = 0; i < 17; i++)
            {
                DdTopone_SET_CLKSEL7_LTMRBK2CLK(i);

                kulong clock = dd_top_get_ltmrbk2clk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_ltmrbk2clk=%ld\n",
                    		i, DdTopone_GET_CLKSEL7_LTMRBK2CLK(), dd_top_get_ltmrbk2clk()));
                }
            }
        }
    }
    else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "APCLK"))
    {
        Ddim_Print(("0:74.25MHz \n"));
        Ddim_Print(("1:54MHz \n"));
        Ddim_Print(("2:37.125MHz \n"));
        Ddim_Print(("3:27MHz \n"));
        Ddim_Print(("4:72MHz \n"));
        Ddim_Print(("5:48MHz \n"));
        Ddim_Print(("8:64MHz \n"));
        Ddim_Print(("9:45.714MHz \n"));
        Ddim_Print(("12:60MHz \n"));
        if (((CtDdParameter *)self)->argc == 5)
        {
            val = atoi(((CtDdParameter *)self)->argv[4]);
            Ddim_Print(("value=%lu\n", val));
            DdTopone_SET_CLKSEL8_APCLK(val);

            kulong clock = dd_top_get_apclk();
            if (clock)
            {
                Ddim_Print(("%02lu:\t%02d: dd_top_get_apclk=%ld\n",
                		val, DdTopone_GET_CLKSEL8_APCLK(), dd_top_get_apclk()));
            }
        }
        else
        {
            for (i = 0; i < 13; i++)
            {
                DdTopone_SET_CLKSEL8_APCLK(i);

                kulong clock = dd_top_get_apclk();
                if (clock)
                {
                    Ddim_Print(("%02d:\t%02d: dd_top_get_apclk=%ld\n",
                    		i, DdTopone_GET_CLKSEL8_APCLK(), dd_top_get_apclk()));
                }
            }
        }
    }
    else
    {
        ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockFrequencyEnd,
        		((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
        ct_clock_frequency_end_get_run(priv->ctClockFrequencyEnd);
    }
}

CtClockFrequencyMid* ct_clock_frequency_mid_new(void) 
{
    CtClockFrequencyMid *self = k_object_new_with_private(CT_TYPE_CLOCK_FREQUENCY_MID,
    		sizeof(CtClockFrequencyMidPrivate));
    return self;
}
