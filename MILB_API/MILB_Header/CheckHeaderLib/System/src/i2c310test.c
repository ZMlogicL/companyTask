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
#include "i2c310test.h"


G_DEFINE_TYPE(I2c310Test, i2c310_test, G_TYPE_OBJECT);

#define I2C310_TEST_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),I2C310_TYPE_TEST, I2c310TestPrivate));


struct _I2c310TestPrivate
{
	 gint preserved;
};

/**
 * DECLS
 */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static void 	run_od(AbsHeaderTest *self);
/**
 * IMPL
 */
static void i2c310_test_class_init(I2c310TestClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(I2c310TestPrivate));

	AbsHeaderTestClass *absClass =  ABS_HEADER_TEST_CALSS(klass);
	absClass->run = run_od;
}

static void i2c310_test_init(I2c310Test *self)
{
	I2c310TestPrivate *priv = I2C310_TEST_GET_PRIVATE(self);

}

static void dispose_od(GObject *object)
{
	G_OBJECT_CLASS(i2c310_test_parent_class)->dispose(object);
}

static void finalize_od(GObject *object)
{
	I2c310Test *self = I2C310_TEST(object);
	I2c310TestPrivate *priv = I2C310_TEST_GET_PRIVATE(self);
	G_OBJECT_CLASS(i2c310_test_parent_class)->finalize(object);

}

static void run_od(AbsHeaderTest *self)
{

}
/**
 * PUBLIC
 */
/*************************************************************************/
void l2c310_test()
{
	RS_printf("IO_L2C310\n");
#if 0
	RS_printf("IO_L2C310.cache_id                             = %p\n", &IO_L2C310.cache_id );
	RS_printf("IO_L2C310.cache_type                           = %p\n", &IO_L2C310.cache_type );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_008_0FF );
	RS_printf("IO_L2C310.control                              = %p\n", &IO_L2C310.control );
	RS_printf("IO_L2C310.aux_control                          = %p\n", &IO_L2C310.aux_control );
	RS_printf("IO_L2C310.tag_ram_control                      = %p\n", &IO_L2C310.tag_ram_control );
	RS_printf("IO_L2C310.data_ram_control                     = %p\n", &IO_L2C310.data_ram_control );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_110_1FF );
	RS_printf("IO_L2C310.ev_counter_ctrl                      = %p\n", &IO_L2C310.ev_counter_ctrl );
	RS_printf("IO_L2C310.ev_counter1_cfg                      = %p\n", &IO_L2C310.ev_counter1_cfg );
	RS_printf("IO_L2C310.ev_counter0_cfg                      = %p\n", &IO_L2C310.ev_counter0_cfg );
	RS_printf("IO_L2C310.ev_counter1                          = %p\n", &IO_L2C310.ev_counter1 );
	RS_printf("IO_L2C310.ev_counter0                          = %p\n", &IO_L2C310.ev_counter0 );
	RS_printf("IO_L2C310.int_mask                             = %p\n", &IO_L2C310.int_mask );
	RS_printf("IO_L2C310.int_mask_status                      = %p\n", &IO_L2C310.int_mask_status );
	RS_printf("IO_L2C310.int_raw_status                       = %p\n", &IO_L2C310.int_raw_status );
	RS_printf("IO_L2C310.int_clear                            = %p\n", &IO_L2C310.int_clear );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_224_72F );
	RS_printf("IO_L2C310.cache_sync                           = %p\n", &IO_L2C310.cache_sync );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_734_76F );
	RS_printf("IO_L2C310.invalidate_line_by_pa                = %p\n", &IO_L2C310.invalidate_line_by_pa );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_774_77B );
	RS_printf("IO_L2C310.invalidate_by_way                    = %p\n", &IO_L2C310.invalidate_by_way );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_780_7AF );
	RS_printf("IO_L2C310.clean_line_by_pa                     = %p\n", &IO_L2C310.clean_line_by_pa );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_7B4_7B7 );
	RS_printf("IO_L2C310.clean_line_by_set_way                = %p\n", &IO_L2C310.clean_line_by_set_way );
	RS_printf("IO_L2C310.clean_by_way                         = %p\n", &IO_L2C310.clean_by_way );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_7C0_7EF );
	RS_printf("IO_L2C310.clean_and_invalidate_line_by_pa      = %p\n", &IO_L2C310.clean_and_invalidate_line_by_pa );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_7F4_7F7 );
	RS_printf("IO_L2C310.clean_and_invalidate_line_by_set_way = %p\n", &IO_L2C310.clean_and_invalidate_line_by_set_way );
	RS_printf("IO_L2C310.clean_and_invalidate_by_way          = %p\n", &IO_L2C310.clean_and_invalidate_by_way );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_800_8FF );
	for(int i=0; i<8; i++) {
		RS_printf("IO_L2C310.lockdown[%d].DATALOCK                 = %p\n", i, &IO_L2C310.lockdown[i].data.bit );
		RS_printf("IO_L2C310.lockdown[%d].INSTRLOCK                = %p\n", i, &IO_L2C310.lockdown[i].instruction.bit );
	}
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_940_94F );
	RS_printf("IO_L2C310.lockdown_by_line_enable              = %p\n", &IO_L2C310.lockdown_by_line_enable );
	RS_printf("IO_L2C310.unlock_all_lines                     = %p\n", &IO_L2C310.unlock_all_lines );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_958_BFF );
	RS_printf("IO_L2C310.address_filtering_start              = %p\n", &IO_L2C310.address_filtering_start );
	RS_printf("IO_L2C310.address_filtering_end                = %p\n", &IO_L2C310.address_filtering_end );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_C08_F3F );
	RS_printf("IO_L2C310.debug_control                        = %p\n", &IO_L2C310.debug_control );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_F44_F5F );
	RS_printf("IO_L2C310.prefetch_control                     = %p\n", &IO_L2C310.prefetch_control );
	RS_printf("Reserved                                       = %p\n", &IO_L2C310.dmy_F64_F7F );
	RS_printf("IO_L2C310.pwr_ctrl                             = %p\n", &IO_L2C310.pwr_ctrl );
	RS_printf(" \n");
#endif
}

I2c310Test *i2c310_test_new()
{
	I2c310Test *self = g_object_new(I2C310_TYPE_TEST, NULL);
	return self;
}
