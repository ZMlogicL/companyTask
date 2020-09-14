/*
*@Copyright (c1) 2010-2020 上海网用软件有限公司
*@date:		 2020-8-5 (发布日期)
*@author:	 余林瑞
*@brief:
*@function:参照ETK代码规范，写一个模板类。
*设计的主要功能:
*1、命名规范
*2、类中各模块的布局规范
*3、常量枚举函数等声明及定义顺序
*@version: 1.0.0 实现一个模板类
*
*/


#ifndef  __DD_TOPFOUR_H__
#define __DD_TOPFOUR_H__


#include<glib-object.h>


G_BEGIN_DECLS


#ifdef __cplusplus
extern "c1" {
#endif


#define DD_TYPE_TOPFOUR										(dd_topfour_get_type ())
#define DD_TOPFOUR(obj)											(G_TYPE_CHECK_INSTANCE_CAST ((obj), DD_TYPE_TOPFOUR,DdTopfour))
#define DD_TOPFOUR_CLASS(klass)							(G_TYPE_CHECK_CLASS_CAST((klass), DD_TYPE_TOPFOUR, DdTopfourClass))
#define DD_IS_TOPFOUR(obj)										(G_TYPE_CHECK_INSTANCE_TYPE ((obj), DD_TYPE_TOPFOUR))
#define DD_IS_TOPFOUR_CLASS(klass)		    			(G_TYPE_CHECK_CLASS_TYPE ((klass), DD_TYPE_TOPFOUR))
#define DD_TOPFOUR_GET_CLASS(obj)						(G_TYPE_INSTANCE_GET_CLASS ((obj), DD_TYPE_TOPFOUR, DdTopfourClass))

// CLKSTOP-1
#define	DdTopfour_DSPCK_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_DSPAX_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_SENCK_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_SENAX_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_SENAH_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_SENAP_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_GPIOAP_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_AU0CK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_AU2CK_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_AU3CK_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_AU4CK_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_AU5CK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_NETAUCK_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-1 */
#define	DdTopfour_TEMPCK_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-1 */

// CLKSTOP-2
#define	DdTopfour_RCK_BIT					(1<<0)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_UHS1CK0_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_UHS1CK1_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_UHS1CK2_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_UHS2CK_BIT				(1<<8)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_NFCK_BIT					(1<<10)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_EMMCCK_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_NETSECCK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_NETRCK_BIT				(1<<16)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_EXSAX_BIT				(1<<18)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_SPICK_BIT				(1<<20)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_SLIMB00CK_BIT		(1<<22)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_SLIMB01CK_BIT		(1<<24)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_SLIMB10CK_BIT		(1<<26)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_SLIMB11CK_BIT		(1<<28)		/**< Bit Location of * on CLKSTOP-2 */
#define	DdTopfour_PCISUPPCK_BIT		(1<<30)		/**< Bit Location of * on CLKSTOP-2 */

// CLKSTOP-5
#define	DdTopfour_MICAX0_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX1_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX2_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX3_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX4_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX5_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAX6_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP0_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP1_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP2_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP3_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP4_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP5_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-5 */
#define	DdTopfour_MICAP6_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-5 */

// CLKSTOP-6
#define	DdTopfour_MICAH1_BIT			(1<<0)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_MICAH2_BIT			(1<<2)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_MICAH3_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_IMGAX_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_IMGAH0_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_IMGAH1_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_IMGAH3_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_IMGAP3_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_REGAP_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_XCHAX_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_XCHAP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_ELACK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_ELAAX_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-6 */
#define	DdTopfour_ELAAP_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-6 */

// CLKSTOP-7
#define	DdTopfour_IPUFDCK_BIT		(1<<0)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_IPUVISCK_BIT		(1<<2)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_IPUAX_BIT			(1<<4)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_IPUAH_BIT			(1<<6)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_RAWCK_BIT			(1<<8)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_RAWAX_BIT			(1<<10)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_RAWAP_BIT			(1<<12)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_SHDRCK_BIT			(1<<14)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_SHDRAX_BIT			(1<<16)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_SHDRAH_BIT			(1<<18)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_SHDRAP_BIT			(1<<20)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_M0CK_BIT			(1<<22)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_MECK_BIT			(1<<24)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_MEAX_BIT			(1<<26)		/**< Bit Location of * on CLKSTOP-7 */
#define	DdTopfour_MEAP_BIT			(1<<28)		/**< Bit Location of * on CLKSTOP-7 */


typedef struct 	_DdTopfour									DdTopfour;
typedef struct 	_DdTopfourClass 						DdTopfourClass;
typedef struct 	_DdTopfourPrivate 					DdTopfourPrivate;


struct _DdTopfour{
	GObject parent;
};

struct _DdTopfourClass 	{
	GObjectClass parentclass;
};


GType 									dd_topfour_get_type(void) G_GNUC_CONST;
DdTopfour* 						dd_topfour_new(void);

/**
Get the direction of a selectable GPIO port.<br>
It is get from the DDR(Data Direction Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] direction	Direction type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_DIR_IN
							  <li>1:@ref DdToptwo_GPIO_DIR_OUT
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topfour_get_gpio_direction(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* direction );

/**
Set the state of a selectable GPIO port.<br>
It is set to the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_toptwo_set_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR status );

/**
Set the functionality of a selectable GPIO port.<br>
It is set to the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [in]  function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_set_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR function );

/**
Get the functionality of a selectable GPIO port.<br>
It is get from the EPCR(External Port Control Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] function	Function type.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_FUNC_GPIO
							  <li>1:@ref DdToptwo_GPIO_FUNC_HWMODE
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Input parameter error.
*/
INT32 dd_topfour_get_gpio_function(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* function );

/**
Get the state of a selectable GPIO port.<br>
It is get from the PDR(Port Data Register) value.
@param [in]  port		Port name. See @ref DdTop_GPIO_PORT
@param [out] status		Port status.
						  <ul>
							  <li>0:@ref DdToptwo_GPIO_STATUS_LOW
							  <li>1:@ref DdToptwo_GPIO_STATUS_HIGH
						  </ul>
@retval D_DDIM_OK					Success.
@retval DdTopone_INPUT_PARAM_ERROR	Error occurred.
*/
INT32 dd_topfour_get_gpio_status(DdTopfour *self, DdTop_GPIO_PORT port, UCHAR* status );





#ifdef __cplusplus
}
#endif


G_END_DECLS


#endif/*__DD_TOPFOUR_H__*/
