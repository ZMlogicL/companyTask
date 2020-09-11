/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-01
*@author              :杨金波
*@brief               :sns 索喜rtos
*@rely                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/


#include<stdint.h>
#include<string.h>
#include<math.h>
#include <klib.h>
#include"improbase.h"


K_TYPE_DEFINE_WITH_PRIVATE(ImproBase, impro_base);
#define IMPRO_BASE_GET_PRIVATE(o)  (K_OBJECT_GET_PRIVATE((o), ImproBasePrivate, IMPRO_TYPE_BASE));


/*宏定义区域*/


/*内部结构体或类型定义，枚举定义区域(按顺序摆放)*/


/**私有结构体定义区域*/
struct _ImproBasePrivate
{
	   kint 		i;
};


/*文件全局变量(含常量及静态变量)定义区域*/


/*DECLS（私有函数声明区域）*/


/*对象初始化区域*/
static void impro_base_constructor(ImproBase *self)
{
	ImproBasePrivate *priv = IMPRO_BASE_GET_PRIVATE(self);
}


/*内存释放区域*/
static void impro_base_destructor(ImproBase *self)
{
	ImproBasePrivate *priv = IMPRO_BASE_GET_PRIVATE(self);
}



/*IMPL*/


/*回调方法区域*/

/*私有方法实现*/


/*PUBLIC*/


/*
 * 此函数用于创建对象
 * @para			--参数
 * @return：返回ImproBase类的一个实例
 *
 */
ImproBase* 	impro_base_new()
{
	ImproBase* self = k_object_new_with_private(IMPRO_TYPE_BASE,sizeof(ImproBasePrivate));
	ImproBasePrivate* priv = IMPRO_BASE_GET_PRIVATE(self);
	
	e_warning_o(self," impro_base_new \n");
	return self;
}
