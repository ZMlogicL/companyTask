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

#ifndef __IMPRO_PASSPT_H__
#define __IMPRO_PASSPT_H__

#include <klib.h>
#include "improbase.h"
#include "impropastop.h"

#define IMPRO_TYPE_PASSPT			(impro_passpt_get_type())
#define IMPRO_PASSPT(obj)			(K_TYPE_CHECK_INSTANCE_CAST (obj, ImproPasspt))
#define IMPRO_IS_PASSPT(obj)		(K_TYPE_CHECK_INSTANCE_TYPE (obj, IMPRO_TYPE_PASSPT))


/*宏定义区域*/
/**< Minimum setting of SPTBSV	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBSV_MIN					(2)
/**< Maximum setting of SPTBSV	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBSV_MAX					(255)
/**< Minimum setting of SPTBSH	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBSH_MIN					(2)
/**< Maximum setting of SPTBSH	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBSH_MAX					(255)
/**< Minimum setting of SPTBDE	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBDE_MIN					(0)
/**< Maximum setting of SPTBDE	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTBDE_MAX					(14)
/**< Minimum setting of SPTV	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTV_MIN						(0)
/**< Maximum setting of SPTV	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTV_MAX						(4095)
/**< Minimum setting of SPTH	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTH_MIN						(0)
/**< Maximum setting of SPTH	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTH_MAX						(8191)
/**< Minimum setting of SPTVBC	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTVBC_MIN					(1)
/**< Maximum setting of SPTVBC	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTVBC_MAX					(15)
/**< Minimum setting of SPTHBC	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTHBC_MIN					(1)
/**< Maximum setting of SPTHBC	*/
#define	ImproPasspt_D_IM_PRO_SPT_SPTHBC_MAX				(15)


/**其他结构体或类型定义区域*/
/** RDMA I/F SPT Shading Correction table register address information*/
typedef struct {
	/**< SPT Shading Correction table register address */
	ULONG	sptTbl;
} TimproRdmaSptShdTblAddr;



/** SPT Control information*/
typedef struct {
	/**< Select shading correction tabletarget registor	:@@sptTbl */
	EimproSptTblSel				tableSel;
	/**< Correction of horizontal pixels per frame interpolationvalue
	 * range:[2 - 255]target registor	:@@SPTBSH */
	USHORT										horizontalPixel;
	/**< Correction of vertical pixels per frame interpolation value range
	 *:[2 - 255]target registor	:@@SPTBSV */
	USHORT										verticalPixel;
	/**< Inverse coefficient correction interpolation frame (base unit)<br>
	value range		:[0 - 511] target registor	:@@SPTBDM */
	USHORT										InverseBase;
	/**< Inverse coefficient correction interpolation frame (Exponent part)<br>
	value range		:[0 - 14] target registor	:@@SPTBDE */
	USHORT										InverseExponent;
	/**< Compensation vertical direction start position<br>
	*value range:[0 - 4095](Multiples of 2)target registor	:@@SPTV */
	USHORT										posY;
	/**< Compensation horizontal direction start position
	value range		:[0 - 8191]target registor	:@@SPTH */
	USHORT										posX;
	/**< Vertical block size setting.value range		:[1 - 15]target registor	:@@SPTVBC */
	UCHAR											vBlockSize;
	/**< Horizontal block size setting.value range		:[1 - 15]target registor	:@@SPTHBC */
	UCHAR											hBlockSize;
	/**< upper limit clip value used in clip processing.<br>
	value range		:[0 - 32767]target registor	:@@SPTCLPH */
	USHORT										upperClipValue;
	/**< lower limit clip value used in clip processing.<br>
	value range		:[0 - 32767]target registor	:@@SPTCLPL */
	USHORT										lowerClipValue;
	/**< The value that does not the correction.<br>
	value range		:[0 - 32767]target registor	:@@SPTNOPV */
	USHORT										correctionThroughVal;
} TimproSptCtrl;

/** Shading Table address information*/
typedef struct {
	/**< table address pointer for SPTTBL0	*/
	SHORT*					pshdTbl;
	/**< set table size for SPTTBL0value range		:[0 - 256] number of array	*/
	USHORT					size;
} TimproSptTable;

/*类型定义区域*/
typedef struct _ImproPasspt                 						ImproPasspt;
typedef struct _ImproPassptPrivate             				ImproPassptPrivate;


/*
*对象结构体区域
*/
struct _ImproPasspt
{
	KObject    parent;
};


/*方法定义区域（公有放在new后面）*/
KConstType				impro_passpt_get_type(void);
ImproPasspt*			impro_passpt_new();
/**
SPT macro start
@retval		D_DDIM_OK				: Processing OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG	: PWCH not running NG
*/
extern	INT32			impro_passpt_start( VOID );
/**
SPT macro stop
@param[in]	force : force stop option
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: PWCH not stopped NG
*/
extern	INT32			impro_passpt_stop( UCHAR force );
/**
Setup of SPT control parameter.
@param[in]	sptCtrl : SPT Information @ref TimproSptCtrl
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
*/
extern	INT32			impro_passpt_ctrl( TimproSptCtrl* sptCtrl );
/**
A setup of enable access to the built-in RAM of SPT.
@param[in]	paenTrg : RAM access control<br>
				 value range :[0:Access inhibit  1:Permissions]<br>
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@retval		ImproBase_D_IM_PRO_MACRO_BUSY_NG		: Macro has not stopped.
*/
extern	INT32			impro_passpt_set_paen( UCHAR paenTrg );
/**
shading compensation table is registered.
@param[in]	tblSel : table select.
@param[in]	shdTbl		: Shading table info
@retval		D_DDIM_OK					: Setting OK
@retval		ImproBase_D_IM_PRO_INPUT_PARAM_ERROR	: Setting NG
@note		None
*/
extern	INT32			impro_passpt_set_table( EimproSptTblSel tblSel, TimproSptTable* shdTbl );
/**
Get the top address of the address array of FSHD Concentric Circles Correction table.
@param[in]		tblSel					: table select.
@param[out]		addr					: Top address of the address array of FSHD Concentric Circles Correction table.
@retval			D_DDIM_OK				: success.
@retval			D_IM_B2R_PARAM_ERROR	: parameter error.
*/
extern	INT32			impro_passpt_get_rdma_addr_spt_shd_tbl( EimproSptTblSel tblSel, const TimproRdmaSptShdTblAddr** addr );


#endif /* __IMPRO_PASSPT_H__ */

