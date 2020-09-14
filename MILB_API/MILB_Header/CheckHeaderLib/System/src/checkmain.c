/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020年9月3日
*@author              :陈柱
*@brief               :
*@rely                :glib
*@function
*设计的主要功能:
*1、
*@version
*
*/
#include "defs.h"
#include "checkmain.h"


G_DEFINE_TYPE(CheckMain, check_main, G_TYPE_OBJECT);

#define CHECK_MAIN_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CHECK_TYPE_MAIN, CheckMainPrivate));


struct _CheckMainPrivate
{
	 gint preserved;
};

/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
/**
 * IMPL
 */
static void check_main_class_init(CheckMainClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CheckMainPrivate));

}

static void check_main_init(CheckMain *self)
{
	CheckMainPrivate *priv = CHECK_MAIN_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(check_main_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	CheckMain *self = CHECK_MAIN(object);
	CheckMainPrivate *priv = CHECK_MAIN_GET_PRIVATE(self);
	G_OBJECT_CLASS(check_main_parent_class)->finalize(object);

}
/**
 * PUBLIC
 */
/*************************************************************************/
void CheckHeaderMain( void )
{
	int index = 1;
	char io_buffer[16];

	RS_printf("Check Register Header\n");

	do {
		RS_printf("Select Index>");
		scanf("%s", io_buffer);

		index = atoi((const char *)io_buffer);

		RS_printf("Index is %d\n", index);

		switch (index)
		{
			case 0:
				b2r_test();
				break;
			case 1:
				iip_test();
				break;
			case 2:
				audio_test();
				break;
			case 3:
				hdmi_test();
				break;
			case 4:
				disp_test();
				break;
			case 5:
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_SEN);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO1);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO2);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_SRO3);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B1);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B2);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_B2B3);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_STAT);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_PAS);
				pro_test(CheckHeaderMain_E_PRO_BLOCK_TYPE_TABLE);
				break;
			case 6:
				xch_test();
				break;
			case 7:
				ela_test();
				break;
			case 8:
				jpeg_enc_test();
				break;
			case 9:
				jpeg_dec_test();
				break;
			case 10:
				exstop_test();
				break;
			case 11:
				cnr_test();
				break;
			case 12:
				peri_test();
				break;
			case 13:
				chiptop_test();
				break;
			case 14:
				img_test();
				break;
			case 15:
				sdramc_test();
				break;
			case 16:
				mxic_test();
				break;
			case 17:
				ptimer_test();
				break;
			case 18:
				wdog_test();
				break;
			case 19:
				xdmac_test();
				break;
			case 20:
				relc_test();
				break;
			case 21:
				exiu_test();
				break;
			case 22:
				gtimer_test();
				break;
			case 23:
				gic_test();
				break;
			case 24:
				exsgpv_test();
				break;
			case 25:
				ipcu_test();
				break;
			case 26:
				l2c310_test();
				break;
			case 27:
				mcc_test();
				break;
			case 28:
				mrbc_test();
				break;
			case 29:
				nic_test();
				break;
			case 30:
				scu_test();
				break;
			case 31:
				ddr_test();
				break;
			case 32:
				netsec_test();
				break;
			case 33:
				shdr_test();
				break;
			case 34:
				pdm_test();
				break;
			case 35:
				r2y_test();
				break;
			case 36:
				timestamp_test();
				break;
			case 37:
				img_raw();
				break;
			case 38:
				bmh_test();
				break;
			case 39:
				fpt_test();
				break;
			case 40:
				ltm_test();
				break;
			case 41:
				me_test();
				break;
			default:
				break;
		}
	} while ( index != 99 );
	RS_printf("\n");
	RS_printf("--- test end ---\n");

//	while (1);
}

CheckMain *check_main_new()
{
	CheckMain *self = g_object_new(CHECK_TYPE_MAIN, NULL);
	return self;
}
