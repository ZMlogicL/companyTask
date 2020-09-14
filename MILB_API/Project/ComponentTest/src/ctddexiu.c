/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtDdExiu类
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
#include "driver_common.h"
#include "ddexiu.h"

#include "ctddexiu.h"


G_DEFINE_TYPE(CtDdExiu, ct_dd_exiu, G_TYPE_OBJECT);
#define CT_DD_EXIU_GET_PRIVATE(o)(G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_DD_EXIU, CtDdExiuPrivate))

struct _CtDdExiuPrivate
{
	DdExiu *ddExiu;
};


/*
*DECLS
*/
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/*
*IMPL
*/

static void ct_dd_exiu_class_init(CtDdExiuClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtDdExiuPrivate));
}

static void ct_dd_exiu_init(CtDdExiu *self)
{
	CtDdExiuPrivate *priv = CT_DD_EXIU_GET_PRIVATE(self);
	priv->ddExiu=dd_exiu_new();
}

static void dispose_od(GObject *object)
{
	CtDdExiu *self = (CtDdExiu*)object;
	CtDdExiuPrivate *priv = CT_DD_EXIU_GET_PRIVATE(self);
	if(priv->ddExiu){
		g_object_unref(priv->ddExiu);
		priv->ddExiu=NULL;
	}
	G_OBJECT_CLASS(ct_dd_exiu_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
//	CtDdExiu *self = (CtDdExiu*)object;
//	CtDdExiuPrivate *priv = CT_DD_EXIU_GET_PRIVATE(self);
}


/*
*PUBLIC
*/
/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
/**
 * @brief  Command main function for EXIU test.
 * @param  int argc	:The number of parameters
 *		   char** argv	:The value of parameters
 * @return void
 *
 *		The meaning of parameters
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| P1          | P2            | P3  | P4  |Meaning                                              |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| display     | -             | -   | -   |Display all registers in external interrupt Unit.    |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eimask_rele   | num | -   |It set Interrupt Mask Release.                       |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eimask_mask   | num | -   |It set Interrupt Mask.                               |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eimask_val    | val | -   |It set Interrupt is Mask or Release.                 |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eisrcsel_ext  | num | -   |It set Interrupt External Source.                    |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eisrcsel_soft | num | -   |It set Interrupt Software Source.                    |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eireqclr_ch   | num | -   |It set Interrupt Cleared Channel.                    |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eireqclr_val  | val | -   |It set Interrupt Cleared Value.                      |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eilvl_lo      | num | -   |It set Interrupt Low level or Falling edge.          |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eilvl_hi      | num | -   |It set Interrupt High level or Rising edge.          |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eiedg_lvl     | num | -   |It set Interrupt Level Detection.                    |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eiedg_edg     | num | -   |It set Interrupt Edge Detection.                     |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| set         | eisir_gen     | num | -   |It set Software Interrupt Generate.                  |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 *		| err         | -             | -   | -   |Parameter Error Test.                                |
 *		+-------------+---------------+-----+-----+-----------------------------------------------------+
 */
void ct_dd_exiu_main_main(CtDdExiu *self, gint argc, gchar** argv)
{
	gint32  ercd;
	guint32 ch;
	guint32 dat;

	if( 0 == strcmp( argv[1], "display" ) ) {
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eimask(priv->ddExiu, ch, &dat);
			Ddim_Print(("Interrupt Mask(EIMASK) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eisrcsel(priv->ddExiu, ch, &dat);
			Ddim_Print(("Interrupt Source(EISRCSEL) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eireqsta(priv->ddExiu, ch, &dat);
			Ddim_Print(("Internal Interrupt Request(EIREQSTA) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eirawreqsta(priv->ddExiu, ch, &dat);
			Ddim_Print(("Raw Interrupt Request(EIRAWREQSTA) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eilvl(priv->ddExiu, ch, &dat);
			Ddim_Print(("External Interrupt Level(EILVL) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eiedg(priv->ddExiu, ch, &dat);
			Ddim_Print(("Interrupt Detection Method(EIEDG) of Channel[%d] = %d\n", ch, dat));
		}
		for( ch=D_DD_EXIU_CH_MIN; ch < D_DD_EXIU_CH_MAX+1; ch++ ) {
			dd_exiu_get_eisir(priv->ddExiu, ch, &dat);
			Ddim_Print(("Software Interrupt(EISIR) of Channel[%d] = %d\n", ch, dat));
		}
	}
	else if( 0 == strcmp( argv[1], "set" ) ) {
		if( 0 == strcmp( argv[2], "eimask_rele" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eimask_release(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Mask Release.\n"));
		}
		else if( 0 == strcmp( argv[2], "eimask_mask" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eimask_mask(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Mask.\n"));
		}
		else if( 0 == strcmp( argv[2], "eimask_val" ) ) {
			gulong val;
			val = (gulong)atof(argv[3]);
			dd_exiu_set_eimask_val(priv->ddExiu, val);
			Ddim_Print(("It set Interrupt is Mask or Release. \n"));
		}
		else if( 0 == strcmp( argv[2], "eisrcsel_ext" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eisrcsel_ext(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt External Source.\n"));
		}
		else if( 0 == strcmp( argv[2], "eisrcsel_soft" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eisrcsel_soft(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Software Source.\n"));
		}
		else if( 0 == strcmp( argv[2], "eireqclr_ch" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eireqclr_ch(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Cleared Channel.\n"));
		}
		else if( 0 == strcmp( argv[2], "eireqclr_val" ) ) {
			gulong val;
			val = (gulong)atof(argv[3]);
			dd_exiu_set_eireqclr_val(priv->ddExiu, val);
			Ddim_Print(("It set Interrupt Cleared Value.\n"));
		}
		else if( 0 == strcmp( argv[2], "eilvl_lo" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eilvl_lo(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Low level or Falling edge.\n"));
		}
		else if( 0 == strcmp( argv[2], "eilvl_hi" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eilvl_hi(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt High level or Rising edge.\n"));
		}
		else if( 0 == strcmp( argv[2], "eiedg_lvl" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eiedg_level(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Level Detection.\n"));
		}
		else if( 0 == strcmp( argv[2], "eiedg_edg" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eiedg_edge(priv->ddExiu, num);
			Ddim_Print(("It set Interrupt Edge Detection.\n"));
		}
		else if( 0 == strcmp( argv[2], "eisir_gen" ) ) {
			int num;
			num = atoi(argv[3]);
			dd_exiu_set_eisir_generate(priv->ddExiu, num);
			Ddim_Print(("It set Software Interrupt Generate.\n"));
		}
		else{
			Ddim_Print(("please check 2nd parameter!!\n"));
		}
	}
	else if( 0 == strcmp( argv[1], "err" ) ) {
		ercd = dd_exiu_get_eimask(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Interrupt Mask(EIMASK) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eimask(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Interrupt Mask(EIMASK) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eimask(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Interrupt Mask(EIMASK) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eisrcsel(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Interrupt Source(EISRCSEL) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eisrcsel(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Interrupt Source(EISRCSEL) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eisrcsel(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Interrupt Source(EISRCSEL) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eireqsta(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Internal Interrupt Request(EIREQSTA) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eireqsta(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Internal Interrupt Request(EIREQSTA) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eireqsta(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Internal Interrupt Request(EIREQSTA) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eirawreqsta(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Raw Interrupt Request(EIRAWREQSTA) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eirawreqsta(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Raw Interrupt Request(EIRAWREQSTA) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eirawreqsta(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Raw Interrupt Request(EIRAWREQSTA) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eilvl(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("External Interrupt Level(EILVL) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eilvl(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("External Interrupt Level(EILVL) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eilvl(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("External Interrupt Level(EILVL) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eiedg(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Interrupt Detection Method(EIEDG) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eiedg(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Interrupt Detection Method(EIEDG) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eiedg(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Interrupt Detection Method(EIEDG) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_get_eisir(priv->ddExiu, D_DD_EXIU_CH_MIN - 1, &dat);
		Ddim_Print(("Software Interrupt(EISIR) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eisir(priv->ddExiu, D_DD_EXIU_CH_MAX + 1, &dat);
		Ddim_Print(("Software Interrupt(EISIR) ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_get_eisir(priv->ddExiu, D_DD_EXIU_CH_MAX, NULL);
		Ddim_Print(("Software Interrupt(EISIR) ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eimask_release(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Mask Release ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eimask_release(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Mask Release ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eimask_mask(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Mask ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eimask_mask(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Mask ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eimask_val(priv->ddExiu, D_DD_EXIU_VAL_MIN - 1);
		Ddim_Print(("Set Interrupt is Mask or Release ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eimask_val(priv->ddExiu, D_DD_EXIU_VAL_MAX + 1);
		Ddim_Print(("Set Interrupt is Mask or Release ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eisrcsel_ext(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt External Source ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eisrcsel_ext(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt External Source ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eisrcsel_soft(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Software Source ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eisrcsel_soft(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Software Source ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eireqclr_ch(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Cleared Channel ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eireqclr_ch(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Cleared Channel ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eireqclr_val(priv->ddExiu, D_DD_EXIU_VAL_MIN - 1);
		Ddim_Print(("Set Interrupt is Cleared Value ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eireqclr_val(priv->ddExiu, D_DD_EXIU_VAL_MAX + 1);
		Ddim_Print(("Set Interrupt is Cleared Value ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eilvl_lo(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Low level or Falling edge ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eilvl_lo(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Low level or Falling edge ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eilvl_hi(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt High level or Rising edge ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eilvl_hi(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt High level or Rising edge ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eiedg_level(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Level Detection ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eiedg_level(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Level Detection edge ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eiedg_edge(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Level Edge Detection ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eiedg_edge(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Level Edge Detection ercd = 0x%08x\n", ercd));

		ercd = dd_exiu_set_eisir_generate(priv->ddExiu, D_DD_EXIU_CH_MIN - 1);
		Ddim_Print(("Set Interrupt Software Interrupt Generate ercd = 0x%08x\n", ercd));
		ercd = dd_exiu_set_eisir_generate(priv->ddExiu, D_DD_EXIU_CH_MAX + 1);
		Ddim_Print(("Set Interrupt Software Interrupt Generate ercd = 0x%08x\n", ercd));
	}
	else{
		Ddim_Print(("please check 1st parameter!!\n"));
	}
}

CtDdExiu *ct_dd_exiu_new(void) 
{
    CtDdExiu *self = g_object_new(CT_TYPE_DD_EXIU, NULL);
    return self;
}
