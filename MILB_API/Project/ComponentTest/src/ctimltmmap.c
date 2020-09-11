/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :tangxin
*@brief               :CtImLtmMap类
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*@version
*1.0.0
*/

#include <stdlib.h>
#include <string.h>
#include "ct_im_ltm.h"
#include "im_ltm.h"
#include "driver_common.h"
#include "ddim_user_custom.h"
#if defined(CO_ACT_CLOCK) || defined(CO_ACT_ICLOCK) || defined(CO_ACT_HCLOCK) || defined(CO_ACT_PCLOCK)
#include "dd_top.h"
#endif
#include "jdsltm.h"

#include "ctimltmmap1.h"
#include "ctimltmmap2.h"
#include "ctimltmmap3.h"
#include "ctimltmmap.h"

G_DEFINE_TYPE(CtImLtmMap, ct_im_ltm_map, G_TYPE_OBJECT);

#define CT_IM_LTM_MAP_GET_PRIVATE(o)  (G_TYPE_INSTANCE_GET_PRIVATE ((o),CT_TYPE_IM_LTM_MAP, CtImLtmMapPrivate))

#ifdef CO_MSG_PRINT_ON
#define CtImLtmMap_D_IM_LTM_RESULT(statement)		result = statement
#else
#define CtImLtmMap_D_IM_LTM_RESULT
#endif

struct _CtImLtmMapPrivate
{
	CtImLtmMap1 *map1;
	CtImLtmMap2 *map2;
	CtImLtmMap3 *map3;
};

/*
 *DECLS
 * */
static void 	dispose_od(GObject *object);
static void 	finalize_od(GObject *object);
static gint32 	ctImLtmMapRun1( CtImLtmMap *self,const guint32 ctNo2nd );
static gint32 	ctImLtmMapRun2( CtImLtmMap *self,const guint32 ctNo2nd );
static gint32 	ctImLtmMapRun3( CtImLtmMap *self,const guint32 ctNo2nd );

static void ct_im_ltm_map_class_init(CtImLtmMapClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	object_class->dispose = dispose_od;
	object_class->finalize = finalize_od;
	g_type_class_add_private(klass, sizeof(CtImLtmMapPrivate));
}

static void ct_im_ltm_map_init(CtImLtmMap *self)
{
	CtImLtmMapPrivate *priv = CT_IM_LTM_MAP_GET_PRIVATE(self);
	priv->map1=ct_im_ltm_map1_new();
	priv->map2=ct_im_ltm_map2_new();
	priv->map3=ct_im_ltm_map3_new();
}

/*
 *IMPL
 * */
static void dispose_od(GObject *object)
{
	CtImLtmMap *self = (CtImLtmMap*)object;
	CtImLtmMapPrivate *priv = CT_IM_LTM_MAP_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map_parent_class)->dispose(object);
	if(priv->map1)
	{
		g_object_unref(priv->map1);
		priv->map1=NULL;
	}
	if(priv->map2)
	{
		g_object_unref(priv->map2);
		priv->map2=NULL;
	}
	if(priv->map3)
	{
		g_object_unref(priv->map3);
		priv->map3=NULL;
	}
}

static void finalize_od(GObject *object)
{
//	CtImLtmMap *self = (CtImLtmMap*)object;
//	CtImLtmMapPrivate *priv = CT_IM_LTM_MAP_GET_PRIVATE(self);
	G_OBJECT_CLASS(ct_im_ltm_map_parent_class)->finalize(object);
}

static gint32 ctImLtmMapRun1( CtImLtmMap *self,const guint32 ctNo2nd )
{
	CtImLtmMapPrivate *priv=CT_IM_LTM_MAP_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-1-1
		case 1:
			return ct_im_ltm_map2_1_1( priv->map2 );

		// Test-1-1-2
		case 2:
			return ct_im_ltm_map2_1_2( priv->map2 );

		// Test-1-1-3
		case 3:
			return ct_im_ltm_map2_1_3( priv->map2 );

		// Test-1-1-4
		case 4:
			return ct_im_ltm_map2_1_4( priv->map2 );

		// Test-1-1-5
		case 5:
			return ct_im_ltm_map2_1_5( priv->map2 );

		// Test-1-1-6
		case 6:
			return ct_im_ltm_map2_1_6( priv->map2 );

		// Test-1-1-7
		case 7:
			return ct_im_ltm_map1_1_7( priv->map1 );

		// Test-1-1-8
		case 8:
			return ct_im_ltm_map1_1_8( priv->map1 );

		// Test-1-1-9
		case 9:
			return ct_im_ltm_map3_1_9( priv->map3 );

		// Test-1-1-10
		case 10:
			return ct_im_ltm_map2_1_10( priv->map2 );

		// Test-1-1-11
		case 11:
			return ct_im_ltm_map2_1_11( priv->map2 );

		// Test-1-1-12
		case 12:
			return ct_im_ltm_map2_1_12( priv->map2 );

		// Test-1-1-13
		case 13:
			return ct_im_ltm_map2_1_13( priv->map2 );

		// Test-1-1-14
		case 14:
			return ct_im_ltm_map2_1_14( priv->map2 );

		// Test-1-1-15
		case 15:
			return ct_im_ltm_map2_1_15( priv->map2 );

		// Test-1-1-16
		case 16:
			return ct_im_ltm_map2_1_16( priv->map2 );

		// Test-1-1-17
		case 17:
			return ct_im_ltm_map2_1_17( priv->map2 );

		// Test-1-1-18
		case 18:
			return ct_im_ltm_map2_1_18( priv->map2 );

		// Test-1-1-19
		case 19:
			return ct_im_ltm_map2_1_19( priv->map2 );

		// Test-1-1-20
		case 20:
			return ct_im_ltm_map2_1_20( priv->map2 );

		// Test-1-1-21
		case 21:
			return ct_im_ltm_map1_1_21( priv->map1 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}

static gint32 ctImLtmMapRun2( CtImLtmMap *self, const guint32 ctNo2nd )
{
	CtImLtmMapPrivate *priv=CT_IM_LTM_MAP_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-2-1
		case 1:
			return ct_im_ltm_map1_2_1( priv->map1 );

		// Test-1-2-2
		case 2:
			return ct_im_ltm_map1_2_2( priv->map1 );

		// Test-1-2-3
		case 3:
			return ct_im_ltm_map1_2_3( priv->map1 );

		// Test-1-2-4
		case 4:
			return ct_im_ltm_map1_2_4( priv->map1 );

		// Test-1-2-5
		case 5:
			return ct_im_ltm_map1_2_5( priv->map1 );

		// Test-1-2-6
		case 6:
			return ct_im_ltm_map1_2_6( priv->map1 );

		// Test-1-2-7
		case 7:
			return ct_im_ltm_map1_2_7( priv->map1 );

		// Test-1-2-8
		case 8:
			return ct_im_ltm_map1_2_8( priv->map1 );

		// Test-1-2-9
		case 9:
			return ct_im_ltm_map1_2_9( priv->map1 );

		// Test-1-2-10
		case 10:
			return ct_im_ltm_map1_2_10( priv->map1 );

		// Test-1-2-11
		case 11:
			return ct_im_ltm_map1_2_11( priv->map1 );

		// Test-1-2-12
		case 12:
			return ct_im_ltm_map1_2_12( priv->map1 );

		// Test-1-2-13
		case 13:
			return ct_im_ltm_map1_2_13( priv->map1 );

		// Test-1-2-14
		case 14:
			return ct_im_ltm_map1_2_14( priv->map1 );

		// Test-1-2-15
		case 15:
			return ct_im_ltm_map1_2_15( priv->map1 );

		// Test-1-2-16
		case 16:
			return ct_im_ltm_map1_2_16( priv->map1 );

		// Test-1-2-17
		case 17:
			return ct_im_ltm_map1_2_17( priv->map1 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;
}

static gint32 ctImLtmMapRun3( CtImLtmMap *self, const guint32 ctNo2nd )
{
	CtImLtmMapPrivate *priv=CT_IM_LTM_MAP_GET_PRIVATE(self);

	switch( ctNo2nd ) {
		// Test-1-3-1
		case 1:
			return ct_im_ltm_map1_3_1( priv->map1 );

		// Test-1-3-2
		case 2:
			return ct_im_ltm_map3_3_2( priv->map3 );

		// Test-1-3-3
		case 3:
			return ct_im_ltm_map3_3_3( priv->map3 );

		// Test-1-3-4
		case 4:
			return ct_im_ltm_map3_3_4( priv->map3 );

		// Test-1-3-5
		case 5:
			return ct_im_ltm_map3_3_5( priv->map3 );

		// Test-1-3-6
		case 6:
			return ct_im_ltm_map3_3_6( priv->map3 );

		// Test-1-3-7
		case 7:
			return ct_im_ltm_map3_3_7( priv->map3 );

		// Test-1-3-8
		case 8:
			return ct_im_ltm_map3_3_8( priv->map3 );

		// Test-1-3-9
		case 9:
			return ct_im_ltm_map3_3_9( priv->map3 );

		// Test-1-3-10
		case 10:
			return ct_im_ltm_map3_3_10( priv->map3 );

		// Test-1-3-11
		case 11:
			return ct_im_ltm_map3_3_11( priv->map3 );

		// Test-1-3-12
		case 12:
			return ct_im_ltm_map3_3_12( priv->map3 );

		default:
			Ddim_Print(("Error: Unknown command.\n"));
			break;
	}

	return D_DDIM_INPUT_PARAM_ERROR;

}
/*
 *PUBLIC
 * */
#ifdef IM_LTM_STATUS_PRINT
extern void Im_LTM_MAP_Print_Status( void );
#endif

void ct_im_ltm_map_run(CtImLtmMap *self,const guint32 ctIdx1st, const guint32 ctIdx2nd, const guint32 ctIdx3rd)
{
	CtImLtmMapPrivate *priv=CT_IM_LTM_MAP_GET_PRIVATE(self);

#ifdef CO_MSG_PRINT_ON
	gint32 result = D_DDIM_INPUT_PARAM_ERROR;
#endif
	static gboolean S_IS_INIT = 0;
	guchar loopCnt;
	ct_im_ltm_map1_set_map3( priv->map1, priv->map3);
	ct_im_ltm_map2_set_map3(priv->map2,priv->map3);

	Ddim_Print(( "ct_im_ltm_map_run( %u, %u, %u ) Begin\n", ctIdx1st, ctIdx2nd, ctIdx3rd ));

	if( S_IS_INIT == 0 ) {
#ifdef CO_DEBUG_ON_PC
		memset( (gpointer)&IO_LTM_P1.MAP, '\0', sizeof(IO_LTM_P1.MAP) );
		memset( (gpointer)&IO_LTM_P2.MAP, '\0', sizeof(IO_LTM_P2.MAP) );
		IO_LTM_P1.MAP.MTRG.word = 2;
		IO_LTM_P2.MAP.MTRG.word = 2;
#endif // CO_DEBUG_ON_PC
		if( !((ctIdx1st == 1) && (ctIdx2nd == 1)) ) {
			Ddim_Print(( "Im_LTM_MAP_Init() Begin\n" ));
			Im_LTM_MAP_Init( D_IM_LTM_PIPE12 );
			Ddim_Print(( "Im_LTM_MAP_Init() End\n" ));
			S_IS_INIT = 1;
		}
	}

	if( ctIdx1st != 3 ){
		for( loopCnt = 0; loopCnt <= 1; loopCnt++ ){
			priv->map3->pipeNo = loopCnt;
			switch( ctIdx1st ) {
				case 1:
					CtImLtmMap_D_IM_LTM_RESULT( ctImLtmMapRun1( self,ctIdx2nd ) );
					break;

				case 2:
					CtImLtmMap_D_IM_LTM_RESULT( ctImLtmMapRun2( self, ctIdx2nd ) );
					break;

				default:
					Ddim_Print(( "Error: Unknown command.\n" ));
					break;
			}

#ifdef CO_MSG_PRINT_ON
			Ddim_Print(( "result = 0x%x\n", result ));
#endif
			Ddim_Print(( "ct_im_ltm_map_run( %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, loopCnt ));
		}
	}
	else{
		priv->map3->pipeNo = ctIdx3rd;
		CtImLtmMap_D_IM_LTM_RESULT( ctImLtmMapRun3( self,ctIdx2nd ) );

#ifdef CO_MSG_PRINT_ON
		Ddim_Print(( "result = 0x%x\n", result ));
#endif
		Ddim_Print(( "ct_im_ltm_map_run( %u, %u, %u) End\n", ctIdx1st, ctIdx2nd, ctIdx3rd ));
	}

	return;
}

// for Debug console interface
void ct_im_ltm_map_main(CtImLtmMap *self,gint32 argc, gchar** argv)
{
	if( argc < 3 ) {
		Ddim_Print(( "ct_im_ltm_map_main: parameter error.\n" ));
		return;
	}

	ct_im_ltm_map_run(self,(guint32)atoi((GConstType)argv[1]),
					   (guint32)atoi((GConstType)argv[2]),
					   (guint32)atoi((GConstType)argv[3]) );
}

/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：
 *        返回CtImLtmMap类的一个实例
 */
CtImLtmMap* ct_im_ltm_map_new()
{
	CtImLtmMap *self = g_object_new(CT_TYPE_IM_LTM_MAP,NULL);
	return self;
}
