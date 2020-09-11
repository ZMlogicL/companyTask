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
#include "ctclockfrequency.h"
#include "ctclockfrequencymid.h"

K_TYPE_DEFINE_WITH_PRIVATE(CtClockFrequency, ct_clock_frequency);
#define CT_CLOCK_FREQUENCY_GET_PRIVATE(o)(K_OBJECT_GET_PRIVATE ((o),CtClockFrequencyPrivate,CT_TYPE_CLOCK_FREQUENCY))

struct _CtClockFrequencyPrivate
{
    CtClockFrequencyMid* ctClockFrequencyMid;
};
/****************
* DECLS
*/
static void 			ct_clock_frequency_constructor(CtClockFrequency *self);
static void 			ct_clock_frequency_destructor(CtClockFrequency *self);
/****************
* IMPL
*/
static void ct_clock_frequency_constructor(CtClockFrequency *self) 
{
	CtClockFrequencyPrivate *priv = CT_CLOCK_FREQUENCY_GET_PRIVATE(self);
    priv->ctClockFrequencyMid = ct_clock_frequency_mid_new();
}

static void ct_clock_frequency_destructor(CtClockFrequency *self) 
{
	CtClockFrequencyPrivate *priv = CT_CLOCK_FREQUENCY_GET_PRIVATE(self);
    k_object_unref(priv->ctClockFrequencyMid);
}
/****************
 * PUBLIC
 */
void ct_clock_frequency_get_run(CtClockFrequency *self)
{
	CtClockFrequencyPrivate *priv = CT_CLOCK_FREQUENCY_GET_PRIVATE(self);
	kulong val;
	kint i;

	DdTopone_SET_CLKSEL3_SENCLK(2);
	DdTopone_SET_CLKSEL5_SRO1CLK(3);
	DdTopone_SET_CLKSEL4_SRO1CLK_2(4);
	DdTopone_SET_CLKSEL5_LTMRBK1CLK(3);

	DdTopone_SET_CLKSEL7_SRO2CLK(3);
	DdTopone_SET_CLKSEL6_SRO2CLK_2(4);
	DdTopone_SET_CLKSEL7_LTMRBK2CLK(3);

	if (((CtDdParameter *)self)->argc == 6 || ((CtDdParameter *)self)->argc == 5 || ((CtDdParameter *)self)->argc == 4)
	{
		if (0 == strcmp(((CtDdParameter *)self)->argv[3], "EMMCCLK"))
		{
			Ddim_Print(("0:187.5MHz \n"));
			Ddim_Print(("1:166.666MHz \n"));
			Ddim_Print(("2:150MHz \n"));
			Ddim_Print(("3:100MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_EMMCCLK(val);
				Ddim_Print(("%02lu: %02d: dd_topone_get_emmcclk()=%ld\n", val, DdTopone_GET_CLKSEL1_EMMCCLK(), dd_topone_get_emmcclk()));
			}
			else
			{
				for (i = 0; i < 3; i++)
				{
					DdTopone_SET_CLKSEL1_EMMCCLK(i);
					Ddim_Print(("%02d: %02d: dd_topone_get_emmcclk()=%ld\n", i, DdTopone_GET_CLKSEL1_EMMCCLK(), dd_topone_get_emmcclk()));
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "NFCLK"))
		{
			Ddim_Print(("1:100MHz \n"));
			Ddim_Print(("2:80MHz \n"));
			Ddim_Print(("3:50MHz \n"));
			Ddim_Print(("4:20MHz \n"));
			Ddim_Print(("16:64MHz \n"));
			Ddim_Print(("24:32MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_NFCLK(val);
				if (dd_topone_get_nfclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_nfclk()=%ld\n", val, DdTopone_GET_CLKSEL1_NFCLK(), dd_topone_get_nfclk()));
				}
			}
			else
			{
				for (i = 0; i < 9; i++)
				{
					DdTopone_SET_CLKSEL1_NFCLK(i);
					if (dd_topone_get_nfclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_nfclk()=%ld\n", i, DdTopone_GET_CLKSEL1_NFCLK(), dd_topone_get_nfclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "UHS2CLK"))
		{
			Ddim_Print(("0:51.851MHz \n"));
			Ddim_Print(("1:46.666MHz \n"));
			Ddim_Print(("2:42.424MHz \n"));
			Ddim_Print(("3:38.888MHz \n"));
			Ddim_Print(("4:35.897MHz \n"));
			Ddim_Print(("5:33.333MHz \n"));
			Ddim_Print(("6:29.166MHz \n"));
			Ddim_Print(("7:25.925MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_UHS2CLK(val);
				if (dd_topone_get_uhs2clk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_uhs2clk()=%ld\n", val, DdTopone_GET_CLKSEL1_UHS2CLK(), dd_topone_get_uhs2clk()));
				}
			}
			else
			{
				for (i = 0; i < 8; i++)
				{
					DdTopone_SET_CLKSEL1_UHS2CLK(i);
					if (dd_topone_get_uhs2clk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_uhs2clk()=%ld\n", i, DdTopone_GET_CLKSEL1_UHS2CLK(), dd_topone_get_uhs2clk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "UHS1CLK2"))
		{
			Ddim_Print(("0:800MHz \n"));
			Ddim_Print(("1:533.333MHz \n"));
			Ddim_Print(("2:400MHz \n"));
			Ddim_Print(("3:200MHz \n"));
			Ddim_Print(("4:100MHz \n"));
			Ddim_Print(("8:700MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_UHS1CLK2(val);
				if (dd_topone_get_uhs1clk2())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_uhs1clk2()=%ld\n", val, DdTopone_GET_CLKSEL1_UHS1CLK2(), dd_topone_get_uhs1clk2()));
				}
			}
			else
			{
				for (i = 0; i < 9; i++)
				{
					DdTopone_SET_CLKSEL1_UHS1CLK2(i);
					if (dd_topone_get_uhs1clk2())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_uhs1clk2()=%ld\n", i, DdTopone_GET_CLKSEL1_UHS1CLK2(), dd_topone_get_uhs1clk2()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "UHS1CLK1"))
		{
			Ddim_Print(("0:800MHz \n"));
			Ddim_Print(("1:533.333MHz \n"));
			Ddim_Print(("2:400MHz \n"));
			Ddim_Print(("3:200MHz \n"));
			Ddim_Print(("4:100MHz \n"));
			Ddim_Print(("8:700MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_UHS1CLK1(val);
				if (dd_topone_get_uhs1clk1())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_uhs1clk1()=%ld\n", val, DdTopone_GET_CLKSEL1_UHS1CLK1(), dd_topone_get_uhs1clk1()));
				}
			}
			else
			{
				for (i = 0; i < 9; i++)
				{
					DdTopone_SET_CLKSEL1_UHS1CLK1(i);
					if (dd_topone_get_uhs1clk1())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_uhs1clk1()=%ld\n", i, DdTopone_GET_CLKSEL1_UHS1CLK1(), dd_topone_get_uhs1clk1()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "UHS1CLK0"))
		{
			Ddim_Print(("0:800MHz \n"));
			Ddim_Print(("1:533.333MHz \n"));
			Ddim_Print(("2:400MHz \n"));
			Ddim_Print(("3:200MHz \n"));
			Ddim_Print(("4:100MHz \n"));
			Ddim_Print(("8:700MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_UHS1CLK0(val);
				if (dd_topone_get_uhs1clk0())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_uhs1clk0()=%ld\n", val, DdTopone_GET_CLKSEL1_UHS1CLK0(), dd_topone_get_uhs1clk0()));
				}
			}
			else
			{
				for (i = 0; i < 9; i++)
				{
					DdTopone_SET_CLKSEL1_UHS1CLK0(i);
					if (dd_topone_get_uhs1clk0())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_uhs1clk0()=%ld\n",
								i, DdTopone_GET_CLKSEL1_UHS1CLK0(), dd_topone_get_uhs1clk0()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "RCLK"))
		{
			Ddim_Print(("0:54MHz \n"));
			Ddim_Print(("1:27MHz \n"));
			Ddim_Print(("2:18MHz \n"));
			Ddim_Print(("3:13.5MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL1_RCLK(val);
				if (dd_topone_get_rclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_rclk()=%ld\n",
							val, DdTopone_GET_CLKSEL1_RCLK(), dd_topone_get_rclk()));
				}
			}
			else
			{
				for (i = 0; i < 4; i++)
				{
					DdTopone_SET_CLKSEL1_RCLK(i);
					if (dd_topone_get_rclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_rclk()=%ld\n",
								i, DdTopone_GET_CLKSEL1_RCLK(), dd_topone_get_rclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "RAWCLK"))
		{
			Ddim_Print(("0:200MHz \n"));
			Ddim_Print(("1:160MHz \n"));
			Ddim_Print(("2:100MHz \n"));
			Ddim_Print(("3:50MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_RAWCLK(val);
				if (dd_topone_get_rawclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_rawclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_RAWCLK(), dd_topone_get_rawclk()));
				}
			}
			else
			{
				for (i = 0; i < 4; i++)
				{
					DdTopone_SET_CLKSEL2_RAWCLK(i);
					if (dd_topone_get_rawclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_rawclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_RAWCLK(), dd_topone_get_rawclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "HIFCLK"))
		{
			Ddim_Print(("0:594MHz \n"));
			Ddim_Print(("1:297MHz \n"));
			Ddim_Print(("2:148.5MHz \n"));
			Ddim_Print(("3:74.25MHz \n"));
			Ddim_Print(("4:27MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_HIFCLK(val);
				if (dd_topone_get_hifclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_hifclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_HIFCLK(), dd_topone_get_hifclk()));
				}
			}
			else
			{
				for (i = 0; i < 5; i++)
				{
					DdTopone_SET_CLKSEL2_HIFCLK(i);
					if (dd_topone_get_hifclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_hifclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_HIFCLK(), dd_topone_get_hifclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "MIFCLK"))
		{
			Ddim_Print(("0:169.714MHz \n"));
			Ddim_Print(("1:148.5MHz \n"));
			Ddim_Print(("2:108MHz \n"));
			Ddim_Print(("3:74.25MHz \n"));
			Ddim_Print(("4:66MHz \n"));
			Ddim_Print(("5:54MHz \n"));
			Ddim_Print(("6:49.5MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_MIFCLK(val);
				if (dd_topone_get_mifclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_mifclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_MIFCLK(), dd_topone_get_mifclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL2_MIFCLK(i);
					if (dd_topone_get_mifclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_mifclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_MIFCLK(), dd_topone_get_mifclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "IPUCLK"))
		{
			Ddim_Print(("0:400MHz \n"));
			Ddim_Print(("1:50MHz \n"));
			Ddim_Print(("2:100MHz \n"));
			Ddim_Print(("3:150MHz \n"));
			Ddim_Print(("4:200MHz \n"));
			Ddim_Print(("5:250MHz \n"));
			Ddim_Print(("6:300MHz \n"));
			Ddim_Print(("7:350MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_IPUCLK(val);
				if (DdTopone_GET_CLKSEL2_IPUCLK())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_ipuclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_IPUCLK(), dd_topone_get_ipuclk()));
				}
			}
			else
			{
				for (i = 0; i < 8; i++)
				{
					DdTopone_SET_CLKSEL2_IPUCLK(i);
					if (DdTopone_GET_CLKSEL2_IPUCLK())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_ipuclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_IPUCLK(), dd_topone_get_ipuclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "IPUTMECLK"))
		{
			Ddim_Print(("0:600MHz \n"));
			Ddim_Print(("1:75MHz \n"));
			Ddim_Print(("2:150MHz \n"));
			Ddim_Print(("3:225MHz \n"));
			Ddim_Print(("4:300MHz \n"));
			Ddim_Print(("5:375MHz \n"));
			Ddim_Print(("6:450MHz \n"));
			Ddim_Print(("7:525MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_IPUTMECLK(val);
				if (dd_topone_get_iputmeclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_iputmeclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_IPUTMECLK(), dd_topone_get_iputmeclk()));
				}
			}
			else
			{
				for (i = 0; i < 8; i++)
				{
					DdTopone_SET_CLKSEL2_IPUTMECLK(i);
					if (dd_topone_get_iputmeclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_iputmeclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_IPUTMECLK(), dd_topone_get_iputmeclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "GPUCLK"))
		{
			Ddim_Print(("0:466.666MHz \n"));
			Ddim_Print(("1:58.333MHz \n"));
			Ddim_Print(("2:116.666MHz \n"));
			Ddim_Print(("3:175MHz \n"));
			Ddim_Print(("4:233.333MHz \n"));
			Ddim_Print(("5:291.666MHz \n"));
			Ddim_Print(("6:350MHz \n"));
			Ddim_Print(("7:408.333MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_GPUCLK(val);
				if (dd_topone_get_gpuclk())
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_gpuclk()=%ld\n",
							val, DdTopone_GET_CLKSEL2_GPUCLK(), dd_topone_get_gpuclk()));
				}
			}
			else
			{
				for (i = 0; i < 8; i++)
				{
					DdTopone_SET_CLKSEL2_GPUCLK(i);
					if (dd_topone_get_gpuclk())
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_gpuclk()=%ld\n",
								i, DdTopone_GET_CLKSEL2_GPUCLK(), dd_topone_get_gpuclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "JPGCLK"))
		{
			Ddim_Print(("0:200MHz \n"));
			Ddim_Print(("1:25MHz \n"));
			Ddim_Print(("2:50MHz \n"));
			Ddim_Print(("3:75MHz \n"));
			Ddim_Print(("4:100MHz \n"));
			Ddim_Print(("5:125MHz \n"));
			Ddim_Print(("6:150MHz \n"));
			Ddim_Print(("7:175MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL2_JPGCLK(val);

				kulong clock = dd_topone_get_jpegclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_jpegclk=%ld\n",
							val, DdTopone_GET_CLKSEL2_JPGCLK(), dd_topone_get_jpegclk()));
				}
			}
			else
			{
				for (i = 0; i < 8; i++)
				{
					DdTopone_SET_CLKSEL2_JPGCLK(i);

					kulong clock = dd_topone_get_jpegclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_jpegclk=%ld\n",
								i, DdTopone_GET_CLKSEL2_JPGCLK(), dd_topone_get_jpegclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "ELACLK"))
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
				DdTopone_SET_CLKSEL2_ELACLK(val);

				kulong clock = dd_topone_get_elaclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_elaclk=%ld\n",
							val, DdTopone_GET_CLKSEL2_ELACLK(), dd_topone_get_elaclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL2_ELACLK(i);

					kulong clock = dd_topone_get_elaclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_elaclk=%ld\n", i,
								DdTopone_GET_CLKSEL2_ELACLK(), dd_topone_get_elaclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "PIPESEL"))
		{
			Ddim_Print(("2:Use PLL02 \n"));
			Ddim_Print(("3:Use PLL01 \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_PIPESEL(val);

				kulong clock = DdTopone_GET_CLKSEL3_PIPESEL();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: DdTopone_GET_CLKSEL3_PIPESEL=%d\n",
							val, DdTopone_GET_CLKSEL3_PIPESEL(), DdTopone_GET_CLKSEL3_PIPESEL()));
				}
			}
			else
			{
				for (i = 0; i < 2; i++)
				{
					DdTopone_SET_CLKSEL3_PIPESEL(i);

					kulong clock = DdTopone_GET_CLKSEL3_PIPESEL();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: DdTopone_GET_CLKSEL3_PIPESEL=%d\n",
								i, DdTopone_GET_CLKSEL3_PIPESEL(), DdTopone_GET_CLKSEL3_PIPESEL()));
					}
				}
			}
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES3_HARDWARE
		// --- REMOVE_ES_COMPILE_OPT END ---
		// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "HEVENCSEL"))
		{
			Ddim_Print(("0:500MHz \n"));
			Ddim_Print(("1:HEVENCCLK \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_HEVENCSEL(val);

				kulong clock = DdTopone_GET_CLKSEL3_HEVENCSEL();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: DdTopone_GET_CLKSEL3_HEVENCSEL=%d\n", val,
							DdTopone_GET_CLKSEL3_HEVENCSEL(), DdTopone_GET_CLKSEL3_HEVENCSEL()));
				}
			}
			else
			{
				for (i = 0; i < 2; i++)
				{
					DdTopone_SET_CLKSEL3_HEVENCSEL(i);

					//					kulong clock = DdTopone_GET_CLKSEL3_HEVENCSEL();
					//					if (clock){
					Ddim_Print(("%02d:\t%02d: DdTopone_GET_CLKSEL3_HEVENCSEL=%d\n",
							i, DdTopone_GET_CLKSEL3_HEVENCSEL(), DdTopone_GET_CLKSEL3_HEVENCSEL()));
					//					}
				}
			}
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
		// --- REMOVE_ES_COMPILE_OPT END ---
		else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "SENCLK"))
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
				DdTopone_SET_CLKSEL3_SENCLK(val);

				kulong clock = dd_topone_get_senclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_senclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_SENCLK(), dd_topone_get_senclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL3_SENCLK(i);

					kulong clock = dd_topone_get_senclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_senclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_SENCLK(), dd_topone_get_senclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "SENMSKCLK"))
		{
			Ddim_Print(("0:100MHz \n"));
			Ddim_Print(("1:80MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_SENMSKCLK(val);

				kulong clock = dd_topone_get_senmskclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_senmskclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_SENMSKCLK(), dd_topone_get_senmskclk()));
				}
			}
			else
			{
				for (i = 0; i < 2; i++)
				{
					DdTopone_SET_CLKSEL3_SENMSKCLK(i);

					kulong clock = dd_topone_get_senmskclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_senmskclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_SENMSKCLK(), dd_topone_get_senmskclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "IIPCLK"))
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
				DdTopone_SET_CLKSEL3_IIPCLK(val);

				kulong clock = dd_topone_get_iipclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_iipclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_IIPCLK(), dd_topone_get_iipclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL3_IIPCLK(i);

					kulong clock = dd_topone_get_iipclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_iipclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_IIPCLK(), dd_topone_get_iipclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "PASCLK"))
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
				DdTopone_SET_CLKSEL3_PASCLK(val);

				kulong clock = dd_topone_get_pasclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_pasclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_PASCLK(), dd_topone_get_pasclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL3_PASCLK(i);

					kulong clock = dd_topone_get_pasclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_pasclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_PASCLK(), dd_topone_get_pasclk()));
					}
				}
			}
		}else if ( 0 == strcmp(((CtDdParameter *)self)->argv[3], "IPPCLK"))
		{
			Ddim_Print(("0:800MHz \n"));
			Ddim_Print(("1:533.333MHz \n"));
			Ddim_Print(("2:400MHz \n"));
			Ddim_Print(("3:200MHz \n"));
			Ddim_Print(("4:700MHz \n"));
			Ddim_Print(("8:600MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_IPPCLK(val);

				kulong clock = dd_topone_get_ippclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_ippclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_IPPCLK(), dd_topone_get_ippclk()));
				}
			}
			else
			{
				for (i = 0; i < 9; i++)
				{
					DdTopone_SET_CLKSEL3_IPPCLK(i);

					kulong clock = dd_topone_get_ippclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_ippclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_IPPCLK(), dd_topone_get_ippclk()));
					}
				}
			}
		}
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#ifdef CO_ES1_HARDWARE
		// --- REMOVE_ES_COMPILE_OPT END ---
		// --- REMOVE_ES1_HARDWARE BEGIN ---
		else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "PXFCLK"))
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
				DdTopone_SET_CLKSEL3_PXFCLK(val);

				kulong clock = dd_topone_get_pxfclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_pxfclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_PXFCLK(), dd_topone_get_pxfclk()));
				}
			}
			else
			{
				for (i = 0; i < 7; i++)
				{
					DdTopone_SET_CLKSEL3_PXFCLK(i);

					kulong clock = dd_topone_get_pxfclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_pxfclk=%ld\n",
								i, DdTopone_GET_CLKSEL3_PXFCLK(), dd_topone_get_pxfclk()));
					}
				}
			}
		}
// --- REMOVE_ES1_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif // CO_ES1_HARDWARE
#ifdef CO_ES3_HARDWARE
		// --- REMOVE_ES_COMPILE_OPT END ---
		// --- REMOVE_ES3_HARDWARE BEGIN ---
		else if (0 == strcmp(((CtDdParameter *)self)->argv[3], "HEVENCCLK"))
		{
			Ddim_Print(("0:466.666MHz \n"));
			Ddim_Print(("1:350MHz \n"));
			Ddim_Print(("2:280MHz \n"));
			Ddim_Print(("4:200MHz \n"));
			Ddim_Print(("5:100MHz \n"));
			if (((CtDdParameter *)self)->argc == 5)
			{
				val = atoi(((CtDdParameter *)self)->argv[4]);
				Ddim_Print(("value=%lu\n", val));
				DdTopone_SET_CLKSEL3_HEVENCCLK(val);

				kulong clock = dd_topone_get_hevencclk();
				if (clock)
				{
					Ddim_Print(("%02lu:\t%02d: dd_topone_get_hevencclk=%ld\n",
							val, DdTopone_GET_CLKSEL3_HEVENCCLK(), dd_topone_get_hevencclk()));
				}
			}
			else
			{
				for (i = 0; i < 6; i++)
				{
					DdTopone_SET_CLKSEL3_HEVENCCLK(i);

					kulong clock = dd_topone_get_hevencclk();
					if (clock)
					{
						Ddim_Print(("%02d:\t%02d: dd_topone_get_hevencclk=%ld\n", i,
								DdTopone_GET_CLKSEL3_HEVENCCLK(), dd_topone_get_hevencclk()));
					}
				}
			}
		}
// --- REMOVE_ES3_HARDWARE END ---
// --- REMOVE_ES_COMPILE_OPT BEGIN ---
#endif	// CO_ES3_HARDWARE
		// --- REMOVE_ES_COMPILE_OPT END ---
		else{
            ct_dd_parameter_set_parameter((CtDdParameter *)priv->ctClockFrequencyMid,
            		((CtDdParameter *)self)->argc,((CtDdParameter *)self)->argv);
            ct_clock_frequency_mid_get_run(priv->ctClockFrequencyMid);
		}
	}else {
		Ddim_Print(("please check parameter!!\n"));
	}

}

CtClockFrequency* ct_clock_frequency_new(void) 
{
    CtClockFrequency *self = k_object_new_with_private(CT_TYPE_CLOCK_FREQUENCY, sizeof(CtClockFrequencyPrivate));
    return self;
}
