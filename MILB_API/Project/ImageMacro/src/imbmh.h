/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-02
*@author              :唐萍萍
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

#ifndef __IM_BMH_H__
#define __IM_BMH_H__

#include "driver_common.h"

#include "ddim_typedef.h"
#include <klib.h>

#define IM_TYPE_BMH		(im_bmh_get_type())
#define IM_BMH(obj)		(K_TYPE_CHECK_INSTANCE_CAST(obj, ImBmh))
#define IM_IS_BMH(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, IM_TYPE_BMH))

typedef struct 				_ImBmh ImBmh;
typedef struct 				_ImBmhPrivate ImBmhPrivate;

struct _ImBmh {
	KObject parent;
};

KConstType 		    im_bmh_get_type(void);
ImBmh*		        im_bmh_new(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
#define	D_IM_BMH_SEM_TIMEOUT_ERR		(D_IM_BMH | D_DDIM_SEM_TIMEOUT)			/**< Time Out                 (0xXX000011) */
#define	D_IM_BMH_NG						(D_IM_BMH | D_DDIM_SYSTEM_ERROR)		/**< Processing NG            (0xXX000099) */
#define D_IM_BMH_SEM_NG					(D_IM_BMH | D_DDIM_SEM_NG)				/**< Semaphore acquisition NG (0xXX000010) */
#define D_IM_BMH_INPUT_PARAMETER_ERROR	(D_IM_BMH | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error.         (0xXX000001) */
#define D_IM_BMH_BUSY_NG				(D_IM_BMH | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy               (0xXX000005) */
#define	D_IM_BMH_AXI_ERR				(D_IM_BMH | 0x100)						/**< AXI bus error.           (0xXX000100) */

#define D_IM_BMH_FLG_BMH_END		(0x00000001)	/**< bmh end flag		*/
#define D_IM_BMH_FLG_BMH_AXI_ERR	(0x00000010)	/**< bmh AXI error flag	*/



#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------
/** BMH enable / disable
*/
typedef enum {
	E_IM_BMH_ONOFF_DISABLE = 0,		/**< BMH disable	*/
	E_IM_BMH_ONOFF_ENABLE			/**< BMH enable	*/
} E_IM_BMH_ONOFF;


#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE


/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
//---------------------------- driver section ----------------------------

typedef VOID (*T_IM_BMH_CALLBACK)( ULONG interrupt_flag_mask );	/**< Callback function pointer	*/

/** BMH Control info for common
*/
typedef struct {
	UCHAR				lselcnt;	/**< Processing block vertical size setting [0000b ~ 1000b (4bit)]		@@LSELCNT	*/
	UCHAR				rbs;		/**< Reference block size setting [000b ~ 111b (3bit)]		@@RBS	*/
	UCHAR				pshift;		/**< Current block Pixel shift number setting [000b ~ 100b (3bit)]		@@PSHIFT	*/
	UCHAR				outmd;		/**< Setting the operation result output mode [000b ~ 110b (3bit)]		@@OUTMD	*/
	UCHAR				lutmd;		/**< LUT mode setting (0:LUT unused / 1:LUT used)		@@LUTMD	*/
	UCHAR				offmd;		/**< Position offset mode setting ((0:Minimum SAD position / 1:Position offset value))		@@OFFMD	*/
	UCHAR				mode;		/**< Setting process mode [0000b ~ 1000b (4bit)]		@@MODE	*/
	ULONG				poffset;	/**< Position offset value (aligned on 1byte)			@@POFFSET	*/
	ULONG				sadlv;		/**< SAD level comparison value (aligned on 2byte)		@@SADLV	*/
	T_IM_BMH_CALLBACK	pCallBack;	/**< callback function	*/
} T_IM_BMH_CTRL;

/** Im_BMH_Ctrl_Axi() parameter structure */
typedef struct {
	UINT32	read_cache_type;			/**< Read Cache type. */
	UINT32	read_protection_type;		/**< Read Protection type. */
	UINT32	write_cache_type;			/**< Write Cache type. */
	UINT32	write_protection_type;		/**< Write Protection type. */
} T_IM_BMH_AXI;

/** Im_BMH_Get_AXI_Status() parameter structure */
typedef struct {
	UCHAR	read_channel_response;	/**< RRESP register */
	UCHAR	write_channel_response;	/**< WRESP register */
} T_IM_BMH_AXI_STATUS;

/** Im_BMH_Set_Bmhre()/Im_BMH_Get_Bmhre() parameter structure */
typedef struct {
	UCHAR	bmhre;	/**< BMHRE register */
} T_IM_BMH_BMHRE;

/** Im_BMH_Get_Rsst() parameter structure */
typedef struct {
	UCHAR	rsst;	/**< BMHINTFS-RSST register */
} T_IM_BMH_RSST;

/** Im_BMH_Set_Bmhcont()/Im_BMH_Get_Bmhcont() parameter structure */
typedef struct {
	UCHAR	cont;	/**< BMHCONT-CONT register */
} T_IM_BMH_BMHCONT;

/** Im_BMH_Set_Bmhhcnt()/Im_BMH_Get_Bmhhcnt() parameter structure */
typedef struct {
	UCHAR	hcnt;	/**< BMHHCNT-HCNT register */
	UCHAR	rcnt;	/**< BMHHCNT-RCNT register */
} T_IM_BMH_BMHHCNT;

/** Im_BMH_Set_Bmhsad_wr()/Im_BMH_Get_Bmhsad_wr() parameter structure */
typedef struct {
	UCHAR	sad_wr;	/**< BMHSAD_WR-SAD_WR register */
} T_IM_BMH_BMHSAD_WR;

/** BMH Control info for DMA mode
*/
typedef struct {
	ULONG				dmamd;			/**< DMA mode setting (0:DMA mode Off / 1:DMA mode ON)	@@DMAMD	*/
	ULONG				ghsize_cur;		/**< Current image GHSIZE setting register (16bit) 8byte boundary		@@GHSIZE_CUR	*/
	ULONG				ghsize_ref;		/**< Reference image GHSIZE setting register (16bit) 8byte boundary	@@GHSIZE_REF	*/
	ULONG				hsize_ref;		/**< Reference image HSIZE setting register (16bit)		@@HSIZE_REF	*/
	ULONG				vsize_ref;		/**< Reference image VSIZE setting register (16bit)		@@VSIZE_REF	*/
	ULONG				curstad;		/**< Current image storage location start address setting register (32bit) <br>
											The start address, 8byte boundary		@@CURSTAD	*/
	ULONG				refstad;		/**< Reference image storage destination top address setting register (32bit) <br>
											The start address, 8byte boundary		@@REFSTAD	*/
	ULONG				sadstad;		/**< Calculation result storage destination top address setting register (32bit) <br>
											The start address, 8byte boundary		@@SADSTAD	*/
	ULONG				sadghsize;		/**< Calculation result storage destination GHSIZE setting register (16bit) 8byte boundary	@@BMHSADGH	*/
} T_IM_BMH_CTRL_DMA;

/** Im_BMH_Set_Cur() parameter structure */
typedef struct {
	UCHAR			cur_write_flg[9][256];	/**< CUR write flag (1:write other:do nothing)*/
	UCHAR			cur_data[9][256];		/**< CUR Write data */
} T_IM_BMH_CUR_BLOCK;

/** Im_BMH_Set_Ref() parameter structure */
typedef struct {
	UCHAR			ref_write_flg[9][256];	/**< REF write flag (1:write other:do nothing)*/
	UCHAR			ref_data[9][256];		/**< REF Write data */
} T_IM_BMH_REF_BLOCK;

/** Im_BMH_Set_Lut() parameter structure */
typedef struct {
	USHORT	lut[2048];				/**< LUT data */
} T_IM_BMH_LUT;

/** Im_BMH_Get_Sadr_000() parameter structure */
/** Array[225]-[227] is dummy.(Do not use) **/
typedef struct {
	UCHAR	sadcmp[2][228];			/**< SAD comparative result */
	UCHAR	pos[2][228];			/**< Position of minimum SAD  */
} T_IM_BMH_SADR_000;

/** Im_BMH_Get_Sadr_001() parameter structure */
typedef struct {
	UCHAR	sadcmp[225];			/**< SAD comparative result */
	UCHAR	pos[225];				/**< Position of minimum SAD */
	USHORT	sadmin[225];			/**< Value minimum SAD */
} T_IM_BMH_SADR_001;

/** Im_BMH_Get_Sadr_010() parameter structure */
/** Array[225] is dummy.(Do not use) **/
typedef struct {
	UCHAR	sadcmp[2][226];			/**< SAD comparative result */
	UCHAR	pos_integer[2][226];	/**< Position of minimum SAD(integer part) */
	UCHAR	pos_fraction[2][226];	/**< Position of minimum SAD(fractional part) */
} T_IM_BMH_SADR_010;

/** Im_BMH_Get_Sadr_011() parameter structure */
typedef struct {
	UCHAR	sadcmp[225];			/**< SAD comparative result */
	UCHAR	pos_integer[225];		/**< Position of minimum SAD(integer part) */
	UCHAR	pos_fraction[225];		/**< Position of minimum SAD(fractional part) */
	USHORT	sadmin[225];			/**< Value minimum SAD */
} T_IM_BMH_SADR_011;

/** Im_BMH_Get_Sadr_100() parameter structure */
typedef struct {
	UCHAR	sadcmp[2][112];			/**< SAD comparative result */
	UCHAR	pos_integer[2][112];	/**< Position of minimum SAD(integer part) */
	UCHAR	pos_fraction[2][112];	/**< Position of minimum SAD(fractional part) */
	USHORT	sadmin[2][112];			/**< Value minimum SAD */
} T_IM_BMH_SADR_100;

/** Im_BMH_Get_Sadr_101() parameter structure */
typedef struct {
	UCHAR	sadcmp[2][56];			/**< SAD comparative result */
	UCHAR	pos_integer[2][56];		/**< Position of minimum SAD(integer part) */
	UCHAR	pos_fraction[2][56];	/**< Position of minimum SAD(fractional part) */
	USHORT	sadmin[2][56];			/**< Value minimum SAD */
	UCHAR	weight[2][56];			/**< Weight of minimum SAD */
	UCHAR	deviation[2][56];		/**< standard deviation */
	UCHAR	cur_max[2][56];			/**< Max value of Current */
	UCHAR	cur_min[2][56];			/**< Minimum value of Current */
} T_IM_BMH_SADR_101;

/** Im_BMH_Get_Sadr_110() parameter structure */
typedef struct {
	UCHAR	sadcmp[2][28];			/**< SAD comparative result */
	UCHAR	pos[2][28];				/**< Position of minimum SAD */
	USHORT	sadmin[2][28];			/**< Value minimum SAD */
	USHORT	sadmin1before[2][28];	/**< Value minimum SAD(sadmin[x][y]-1) */
	USHORT	sadmin1after[2][28];	/**< Value minimum SAD(sadmin[x][y]+1) */
	USHORT	sadmin2before[2][28];	/**< Value minimum SAD(sadmin[x][y]-2) */
	USHORT	sadmin2after[2][28];	/**< Value minimum SAD(sadmin[x][y]+2) */
	UCHAR	weight[2][28];			/**< Weight of minimum SAD */
	UCHAR	deviation[2][28];		/**< standard deviation */
	UCHAR	cur_max[2][28];			/**< Max value of Current */
	UCHAR	cur_min[2][28];			/**< Minimum value of Current */
} T_IM_BMH_SADR_110;


#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif	// CO_DDIM_UTILITY_USE

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus
//---------------------------- driver section ----------------------------
extern	INT32 Im_BMH_Init( BYTE channel_no );
extern	INT32 Im_BMH_Start_Sync( BYTE channel_no, const INT32 wait_time );
extern	INT32 Im_BMH_Start_Async( BYTE channel_no );
extern	INT32 Im_BMH_Wait_End( BYTE channel_no, UINT32* const p_wait_factor, const INT32 wait_time );
extern	INT32 Im_BMH_Stop( BYTE channel_no );
extern	INT32 Im_BMH_Close( BYTE channel_no );
extern	INT32 Im_BMH_Get_Ctrl( BYTE channel_no, T_IM_BMH_CTRL* const bmh_ctrl );
extern	INT32 Im_BMH_Set_Bmhre( BYTE channel_no, const T_IM_BMH_BMHRE* const sram );
extern	INT32 Im_BMH_Get_Bmhre( BYTE channel_no, T_IM_BMH_BMHRE* const sram );
extern	INT32 Im_BMH_Get_Rsst( BYTE channel_no, T_IM_BMH_RSST* const rsst );
extern	INT32 Im_BMH_Set_Bmhcont( BYTE channel_no, const T_IM_BMH_BMHCONT* const cont );
extern	INT32 Im_BMH_Get_Bmhcont( BYTE channel_no, T_IM_BMH_BMHCONT* const cont );
extern	INT32 Im_BMH_Set_Bmhaxi( BYTE channel_no, const T_IM_BMH_AXI* const axi_ctrl );
extern	INT32 Im_BMH_Set_Bmhhcnt( BYTE channel_no, const T_IM_BMH_BMHHCNT* const cnt );
extern	INT32 Im_BMH_Set_Bmhsad_wr( BYTE channel_no, const T_IM_BMH_BMHSAD_WR* const sad_wr );
extern	INT32 Im_BMH_Set_Lut( BYTE channel_no, const T_IM_BMH_LUT* const lut_data );
extern	INT32 Im_BMH_Ctrl_Dma( BYTE channel_no, const T_IM_BMH_CTRL_DMA* const bmh_ctrl_dma );
extern	VOID Im_BMH_Int_Handler( BYTE channel_no );
extern	INT32 Im_BMH_Ctrl( BYTE channel_no, const T_IM_BMH_CTRL* const bmh_ctrl );

#ifdef CO_BMH_DEBUG
VOID Im_BMH_Print_ClockStatus( VOID )
#endif	// CO_BMH_DEBUG

#ifdef CO_DDIM_UTILITY_USE

#endif	// CO_DDIM_UTILITY_USE


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif /* __IM_BMH_H__ */
