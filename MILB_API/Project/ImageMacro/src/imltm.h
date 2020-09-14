/*
 * imltm.h
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#ifndef __IM_LTM_H__
#define __IM_LTM_H__

#include <klib.h>
#include "driver_common.h"
#include "ddim_user_custom.h"
#include "jdsltm.h"
#include "ddim_typedef.h"

#define ImLtm_IM_TYPE_LTM		(im_ltm_get_type())
#define ImLtm_IM_LTM(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImLtm))
#define ImLtm_IM_IS_LTM(obj)	(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImLtm))
#define	ImLtm_D_IM_LTM_PARAM_ERROR			(D_IM_LTM | D_DDIM_INPUT_PARAM_ERROR)	/**< parameter error		*/
#define	ImLtm_D_IM_LTM_TIMEOUT					(D_IM_LTM | D_DDIM_TIMEOUT)				/**< timeout				*/
#define	ImLtm_D_IM_LTM_SYSTEM_ERROR		(D_IM_LTM | D_DDIM_SYSTEM_ERROR)		/**< System call error		*/
#define	ImLtm_D_IM_LTM_MACRO_BUSY			(D_IM_LTM | D_DDIM_MACRO_BUSY_NG)		/**< Macro busy error		*/
#define	ImLtm_D_IM_LTM_ENABLE_OFF				(0)						/**< Disable						*/
#define	ImLtm_D_IM_LTM_ENABLE_ON				(1)						/**< Enable							*/
#define	ImLtm_D_IM_LTM_WAIT_OFF					(0)						/**< Wait disable.					*/
#define	ImLtm_D_IM_LTM_WAIT_ON					(1)						/**< Wait enable.					*/
#define	ImLtm_D_IM_LTM_PIPE1							(0)						/**< Pipe1.							*/
#define	ImLtm_D_IM_LTM_PIPE2							(1)						/**< Pipe2.							*/
#define	ImLtm_D_IM_LTM_PIPE12						(2)						/**< Pipe1&2.						*/
#define	ImLtm_D_IM_LTM_PIPE_MAX					(3)						/**< Max value						*/
#define ImLtm_D_IM_LTM_PORT_1						(0)						/**< Port1							*/
#define ImLtm_D_IM_LTM_PORT_2						(1)						/**< Port2							*/
#define ImLtm_D_IM_LTM_PORT_3						(2)						/**< Port3							*/
#define ImLtm_D_IM_LTM_PORT_4						(3)						/**< Port4							*/
#define ImLtm_D_IM_LTM_PORT_MAX				(4)						/**< The maximum values of RGB/Y component to be processed */
#define	ImLtm_D_IM_LTM_PORT_R						(ImLtm_D_IM_LTM_PORT_1)		/**< R data(Planar)					*/
#define	ImLtm_D_IM_LTM_PORT_G						(ImLtm_D_IM_LTM_PORT_2)		/**< G data(Planar)					*/
#define	D_IM_LTM_PORT_B						(ImLtm_D_IM_LTM_PORT_3)		/**< B data(Planar)					*/
#define	D_IM_LTM_PORT_RGB				(ImLtm_D_IM_LTM_PORT_4)		/**< RGB data(Dot)					*/
#define D_IM_LTM_PORT_Y_YP_YN			(ImLtm_D_IM_LTM_PORT_4)		/**< Y data(Default)				*/
#define D_IM_LTM_PORT_Y_YP				(ImLtm_D_IM_LTM_PORT_1)		/**< Y data							*/
#define D_IM_LTM_PORT_Y_YN				(ImLtm_D_IM_LTM_PORT_2)		/**< Y data							*/
#define D_IM_LTM_RBK_READ_PORT_COUNT			(3)						/**< read port's count(RBK block)	*/
#define D_IM_LTM_RBK_WRITE_PORT_COUNT		(1)						/**< write port's count(RBK block)	*/
#define D_IM_LTM_MAP_READ_PORT_COUNT		(1)						/**< read port's count(MAP block)	*/
#define D_IM_LTM_MAP_WRITE_PORT_COUNT		(2)						/**< write port's count(MAP block)	*/
#define D_IM_LTM_LTM_READ_Y_PORT_COUNT		(2)						/**< read port's count(LTM block)	*/
#define D_IM_LTM_LTM_READ_RGB_PORT_COUNT	(3)						/**< read port's count(LTM block)	*/
#define D_IM_LTM_LTM_WRITE_PORT_COUNT			(3)						/**< write port's count(LTM block)	*/
#define	D_IM_LTM_BRST_512					(0)						/**< 512bytes burst					*/
#define	D_IM_LTM_BRST_256					(1)						/**< 256bytes burst					*/
#define	D_IM_LTM_PORT_DEFAULT			(0)						/**< Default port(Port4)		*/
#define	D_IM_LTM_PORT_SWITCH				(1)						/**< YP(Port1), YN(Port2)		*/
#define	D_IM_LTM_DTYP_PACK12				(2)						/**< 12bit PACK						*/
#define	D_IM_LTM_DTYP_UNPACK12			(3)						/**< 12bit UNPACK					*/
#define D_IM_LTM_TABLE_MAX_RCG			(32)					/**< RCG table array number	*/
#define D_IM_LTM_TABLE_MAX_YLOG		(512)					/**< YLOG table array number	*/
#define D_LTM_YLOG_TBL_00					(0)						/**< YLOG Table0 side0	*/
#define D_LTM_YLOG_TBL_01					(1)						/**< YLOG Table0 side1	*/
#define D_LTM_YLOG_TBL_10					(2)						/**< YLOG Table1 side0	*/
#define D_LTM_YLOG_TBL_11					(3)						/**< YLOG Table1 side1	*/
#define	D_IM_LTM_YLOG_TBL_SIDE_0			(0)						/**< Side 0 select(YLOG0/YLOG1 table)	*/
#define	D_IM_LTM_YLOG_TBL_SIDE_1			(1)						/**< Side 1 select(YLOG0/YLOG1 table)	*/
#define	D_IM_LTM_MASK_WRITE_ENABLE		(0)						/**< Writing with mask is enabled	*/
#define	D_IM_LTM_MASK_WRITE_DISABLE		(1)						/**< Writing with mask is disabled	*/
#define	D_IM_LTM_RBK1_INT_STATE_RBK_END			(0x00000001)			/**< RBK: Normal end				*/
#define	D_IM_LTM_RBK1_INT_STATE_FRAME_END	(0x00000002)			/**< Receiving the top of the frame	*/
#define	D_IM_LTM_RBK1_INT_STATE_LINE_END	(0x00000004)			/**< Line transferred				*/
#define	D_IM_LTM_RBK1_INT_STATE_WAIT_ERR	(0x00000008)			/**< Overrun error					*/
#define	D_IM_LTM_RBK1_INT_STATE_AXR_ERR		(0x00000010)			/**< AXI Read channel error			*/
#define	D_IM_LTM_RBK1_INT_STATE_AXW_ERR	(0x00000020)			/**< AXI Write channel error		*/
#define	D_IM_LTM_RBK2_INT_STATE_RBK_END		(0x00000100)			/**< RBK: Normal end				*/
#define	D_IM_LTM_RBK2_INT_STATE_FRAME_END	(0x00000200)			/**< Receiving the top of the frame	*/
#define	D_IM_LTM_RBK2_INT_STATE_LINE_END		(0x00000400)			/**< Line transferred				*/
#define	D_IM_LTM_RBK2_INT_STATE_WAIT_ERR		(0x00000800)			/**< Overrun error					*/
#define	D_IM_LTM_RBK2_INT_STATE_AXR_ERR			(0x00001000)			/**< AXI Read channel error			*/
#define	D_IM_LTM_RBK2_INT_STATE_AXW_ERR		(0x00002000)			/**< AXI Write channel error		*/
#define	D_IM_LTM_RBK1_INT_FLG_RBK_END				(0x00000001)			/**< RBK: Normal end				*/
#define	D_IM_LTM_RBK1_INT_FLG_FRAME_END		(0x00000002)			/**< Receiving the top of the frame	*/
#define	D_IM_LTM_RBK1_INT_FLG_LINE_END		(0x00000004)			/**< Line transferred				*/
#define	D_IM_LTM_RBK1_INT_FLG_WAIT_ERR		(0x00000008)			/**< Overrun error					*/
#define	D_IM_LTM_RBK1_INT_FLG_AXR_ERR			(0x00000010)			/**< AXI Read channel error			*/
#define	D_IM_LTM_RBK1_INT_FLG_AXW_ERR		(0x00000020)			/**< AXI Write channel error		*/
#define	D_IM_LTM_RBK1_INT_FLG_ALL				(0x0000003F)			/**< All flags(PIPE1)				*/
#define	D_IM_LTM_RBK2_INT_FLG_RBK_END		(0x00000100)			/**< RBK: Normal end				*/
#define	D_IM_LTM_RBK2_INT_FLG_FRAME_END	(0x00000200)			/**< Receiving the top of the frame	*/
#define	D_IM_LTM_RBK2_INT_FLG_LINE_END		(0x00000400)			/**< Line transferred				*/
#define	D_IM_LTM_RBK2_INT_FLG_WAIT_ERR		(0x00000800)			/**< Overrun error					*/
#define	D_IM_LTM_RBK2_INT_FLG_AXR_ERR			(0x00001000)			/**< AXI Read channel error			*/
#define	D_IM_LTM_RBK2_INT_FLG_AXW_ERR		(0x00002000)			/**< AXI Write channel error		*/
#define	D_IM_LTM_RBK2_INT_FLG_ALL			(0x00003F00)			/**< All flags(PIPE2)				*/
#define	D_IM_LTM_RBK_INT_FLG_ALL			(0x00003F3F)			/**< All flags						*/
#define	D_IM_LTM_RBK_TOP_PIXEL_R			(0)						/**< Bayer top pixel is R			*/
#define	D_IM_LTM_RBK_TOP_PIXEL_GR			(1)						/**< Bayer top pixel is Gr			*/
#define	D_IM_LTM_RBK_TOP_PIXEL_GB			(2)						/**< Bayer top pixel is Gb			*/
#define	D_IM_LTM_RBK_TOP_PIXEL_B			(3)						/**< Bayer top pixel is B			*/
#define	D_IM_LTM_RBK_SRO_DIRECT_1			(0)						/**< Input SRO1						*/
#define	D_IM_LTM_RBK_SRO_DIRECT_2			(1)						/**< Input SRO1&SRO2				*/
#define	D_IM_LTM_RBK_OUT_SDRAM				(0)						/**< Output to SDRAM				*/
#define	D_IM_LTM_RBK_OUT_MAP_DIRECT			(1)						/**< Output to MAP block(Direct)	*/
#define	D_IM_LTM_RBK_RDC_MODE_DIV_2			(0)						/**< Reduction 1/2	*/
#define	D_IM_LTM_RBK_RDC_MODE_DIV_4			(1)						/**< Reduction 1/4	*/
#define	D_IM_LTM_RBK_RDC_MODE_DIV_8			(2)						/**< Reduction 1/8	*/
#define	D_IM_LTM_MAP1_INT_STATE_MAP_END		(0x00000001)			/**< MAP: Normal end				*/
#define	D_IM_LTM_MAP1_INT_STATE_LINE_END		(0x00000002)			/**< Line transferred				*/
#define	D_IM_LTM_MAP1_INT_STATE_AXR_ERR			(0x00000004)			/**< AXI Read channel error			*/
#define	D_IM_LTM_MAP1_INT_STATE_AXW_ERR		(0x00000008)			/**< AXI Write channel error		*/
#define	D_IM_LTM_MAP1_INT_STATE_YLOG_ERR		(0x00000010)			/**< YLOG Table CPU access error	*/
#define	D_IM_LTM_MAP1_INT_STATE_HISTINI_END	(0x00000020)			/**< RAM initialize End				*/
#define	D_IM_LTM_MAP2_INT_STATE_MAP_END		(0x00000100)			/**< MAP: Normal end				*/
#define	D_IM_LTM_MAP2_INT_STATE_LINE_END		(0x00000200)			/**< Line transferred				*/
#define	D_IM_LTM_MAP2_INT_STATE_AXR_ERR			(0x00000400)			/**< AXI Read channel error			*/
#define	D_IM_LTM_MAP2_INT_STATE_AXW_ERR		(0x00000800)			/**< AXI Write channel error		*/
#define	D_IM_LTM_MAP2_INT_STATE_YLOG_ERR		(0x00001000)			/**< YLOG Table CPU access error	*/
#define	D_IM_LTM_MAP2_INT_STATE_HISTINI_END	(0x00002000)			/**< RAM initialize End				*/
#define	D_IM_LTM_MAP1_INT_FLG_MAP_END		(0x00000001)			/**< MAP: Normal end				*/
#define	D_IM_LTM_MAP1_INT_FLG_LINE_END		(0x00000002)			/**< Line transferred				*/
#define	D_IM_LTM_MAP1_INT_FLG_AXR_ERR			(0x00000004)			/**< AXI Read channel error			*/
#define	D_IM_LTM_MAP1_INT_FLG_AXW_ERR		(0x00000008)			/**< AXI Write channel error		*/
#define	D_IM_LTM_MAP1_INT_FLG_YLOG_ERR		(0x00000010)			/**< YLOG Table CPU access error	*/
#define	D_IM_LTM_MAP1_INT_FLG_HISTINI_END	(0x00000020)			/**< RAM initialize End				*/
#define	D_IM_LTM_MAP1_INT_FLG_ALL					(0x0000003F)			/**< All flags(PIPE1)				*/
#define	D_IM_LTM_MAP2_INT_FLG_MAP_END		(0x00000100)			/**< MAP: Normal end				*/
#define	D_IM_LTM_MAP2_INT_FLG_LINE_END		(0x00000200)			/**< Line transferred				*/
#define	D_IM_LTM_MAP2_INT_FLG_AXR_ERR			(0x00000400)			/**< AXI Read channel error			*/
#define	D_IM_LTM_MAP2_INT_FLG_AXW_ERR		(0x00000800)			/**< AXI Write channel error		*/
#define	D_IM_LTM_MAP2_INT_FLG_YLOG_ERR		(0x00001000)			/**< YLOG Table CPU access error	*/
#define	D_IM_LTM_MAP2_INT_FLG_HISTINI_END	(0x00002000)			/**< RAM initialize End				*/
#define	D_IM_LTM_MAP2_INT_FLG_ALL			(0x00003F00)			/**< All flags(PIPE2)				*/
#define	D_IM_LTM_MAP_INT_FLG_ALL			(0x00003F3F)			/**< All flags						*/
#define	D_IM_LTM_MAP_GENERATION_MODE_0		(0)						/**< Mode0	*/
#define	D_IM_LTM_MAP_GENERATION_MODE_1		(1)						/**< Mode1	*/
#define	D_IM_LTM_LTM1_INT_STATE_LTM_END		(0x00000001)			/**< LTM: Normal end						*/
#define	D_IM_LTM_LTM1_INT_STATE_EXIP_END	(0x00000002)			/**< Received transmission starting pulse	*/
#define	D_IM_LTM_LTM1_INT_STATE_LINE_END	(0x00000004)			/**< Line transferred						*/
#define	D_IM_LTM_LTM1_INT_STATE_AXR_ERR		(0x00000008)			/**< AXI Read channel error					*/
#define	D_IM_LTM_LTM1_INT_STATE_AXW_ERR	(0x00000010)			/**< AXI Write channel error				*/
#define	D_IM_LTM_LTM1_INT_STATE_YLOG_ERR	(0x00000020)			/**< YLOG Table CPU access error			*/
#define	D_IM_LTM_LTM2_INT_STATE_LTM_END		(0x00000100)			/**< LTM: Normal end						*/
#define	D_IM_LTM_LTM2_INT_STATE_EXIP_END	(0x00000200)			/**< Received transmission starting pulse	*/
#define	D_IM_LTM_LTM2_INT_STATE_LINE_END	(0x00000400)			/**< Line transferred						*/
#define	D_IM_LTM_LTM2_INT_STATE_AXR_ERR		(0x00000800)			/**< AXI Read channel error					*/
#define	D_IM_LTM_LTM2_INT_STATE_AXW_ERR	(0x00001000)			/**< AXI Write channel error				*/
#define	D_IM_LTM_LTM2_INT_STATE_YLOG_ERR	(0x00002000)			/**< YLOG Table CPU access error			*/
#define	D_IM_LTM_LTM1_INT_FLG_LTM_END			(0x00000001)			/**< LTM: Normal end						*/
#define	D_IM_LTM_LTM1_INT_FLG_EXIP_END		(0x00000002)			/**< Received transmission starting pulse	*/
#define	D_IM_LTM_LTM1_INT_FLG_LINE_END		(0x00000004)			/**< Line transferred						*/
#define	D_IM_LTM_LTM1_INT_FLG_AXR_ERR			(0x00000008)			/**< AXI Read channel error					*/
#define	D_IM_LTM_LTM1_INT_FLG_AXW_ERR		(0x00000010)			/**< AXI Write channel error				*/
#define	D_IM_LTM_LTM1_INT_FLG_YLOG_ERR		(0x00000020)			/**< YLOG Table CPU access error			*/
#define	D_IM_LTM_LTM1_INT_FLG_ALL				(0x0000003F)			/**< All flags(PIPE1)						*/
#define	D_IM_LTM_LTM2_INT_FLG_LTM_END		(0x00000100)			/**< LTM: Normal end						*/
#define	D_IM_LTM_LTM2_INT_FLG_EXIP_END		(0x00000200)			/**< Received transmission starting pulse	*/
#define	D_IM_LTM_LTM2_INT_FLG_LINE_END		(0x00000400)			/**< Line transferred						*/
#define	D_IM_LTM_LTM2_INT_FLG_AXR_ERR			(0x00000800)			/**< AXI Read channel error					*/
#define	D_IM_LTM_LTM2_INT_FLG_AXW_ERR		(0x00001000)			/**< AXI Write channel error				*/
#define	D_IM_LTM_LTM2_INT_FLG_YLOG_ERR		(0x00002000)			/**< YLOG Table CPU access error			*/
#define	D_IM_LTM_LTM2_INT_FLG_ALL			(0x00003F00)			/**< All flags(PIPE2)						*/
#define	D_IM_LTM_LTM_INT_FLG_ALL			(0x00003F3F)			/**< All flags								*/
#define	D_IM_LTM_LTM_OUT_SDRAM				(0)						/**< Output to SDRAM				*/
#define	D_IM_LTM_LTM_OUT_R2Y_DIRECT		(1)						/**< Output to R2Y macro(Direct)	*/

typedef struct _ImLtm ImLtm;
typedef struct {
	UCHAR					cache_type;						/**< cache type (4bits)		*/
	UCHAR					protect_type;					/**< protect type (3bits)	*/
} T_IM_LTM_CTRL_AXI_TYPE;

typedef struct {
	USHORT					img_top;						/**< Vertical start position	*/
	USHORT					img_left;						/**< Horizontal start position	*/
	USHORT					img_width;						/**< Horizontal size			*/
	USHORT					img_lines;						/**< Vertical size				*/
} T_IM_LTM_RECT;												/* Rectangle control data	*/

typedef struct {
	VOID*					addr_r;							/**< RSDRADR/LSDRADR2R : R address(32bits, multiple of 2)	*/
	VOID*					addr_g;							/**< RSDRADG/LSDRADR2G : G address(32bits, multiple of 2)	*/
	VOID*					addr_b;							/**< RSDRADB/LSDRADR2B : B address(32bits, multiple of 2)	*/
} T_IM_LTM_INADDR_INFO;

typedef struct {
	USHORT					yshadow;						/**< YSHADOW/LYSHADOW : Internal parameter 0(14bits)	*/
	USHORT					yhighlight;						/**< YHIGHLIGHT/LYHIGHLIGHT : Internal parameter 1(14bits)	*/
} T_IM_LTM_INTERNAL_PARAM;

typedef struct {
	UCHAR					use_tbl;						/**< MYLCTL.YLOGSL, LYLCTL.YLOGSL : YLOG table side select(1bit)
															<ul><li>@ref D_IM_LTM_YLOG_TBL_SIDE_0
																<li>@ref D_IM_LTM_YLOG_TBL_SIDE_1</ul>			*/
	USHORT					end_point0_tbl0;				/**< MYLOG0EP0, LYLOG0EP0 : YLOG0 table end point(side0)(14bits)	*/
	USHORT					end_point0_tbl1;				/**< MYLOG0EP1, LYLOG0EP1 : YLOG0 table end point(side1)(14bits)	*/
	USHORT					end_point1_tbl0;				/**< MYLOG1EP0, LYLOG1EP0 : YLOG1 table end point(side0)(14bits)	*/
	USHORT					end_point1_tbl1;				/**< MYLOG1EP1, LYLOG1EP1 : YLOG1 table end point(side1)(14bits)	*/
} T_IM_LTM_CTRL_YLOG;

typedef struct {
	T_IM_LTM_CTRL_AXI_TYPE	rch[D_IM_LTM_RBK_READ_PORT_COUNT];	/**< RAXICTLR1.ARCACHE_x, RAXICTLR1.ARPROT_x Read channel types.	*/
	T_IM_LTM_CTRL_AXI_TYPE	wch;								/**< RAXICTLW1.AWCACHE, RAXICTLW1.AWPROT Write channel types.		*/
} T_IM_LTM_RBK_CTRL_AXI;

typedef struct {
	UCHAR					rch_axi_stat[D_IM_LTM_RBK_READ_PORT_COUNT];	/**< RAXIRERR.RRESP_x : Read channel status	*/
} T_IM_LTM_RBK_AXI_RCH_STAT;

typedef struct {
	UCHAR					wch_axi_stat;					/**< RAXIWERR.WRESP : Write channel status	*/
} T_IM_LTM_RBK_AXI_WCH_STAT;

typedef struct {
	UCHAR					rch_burst_length_r;				/**< RAXIBSIZ.BURSTRR : Transfer burst length of the read channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_g;				/**< RAXIBSIZ.BURSTRG : Transfer burst length of the read channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_b;				/**< RAXIBSIZ.BURSTRB : Transfer burst length of the read channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length;				/**< RAXIBSIZ.BURSTW  : Transfer burst length of the write channel.(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write;						/**< RAXIBSIZ.WSTBMSK : Writing with mask.(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
} T_IM_LTM_RBK_AXI_CTRL_PARAM;

typedef struct {
	USHORT					line_intr;						/**< RLINTLV.LINTLV : Monitor line count setting. (14bits)
															<p>We generate the interrupt request flag when the set value of this register.
															<p>This interrupt request, can be disabled by setting the "0000" h.	*/
	UCHAR					burst_length;					/**< RAXIBSIZ.BURSTW  : Transfer burst length of the write channel.(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write;						/**< RAXIBSIZ.WSTBMSK : Writing with mask.(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					out_select;						/**< RIOCTL.OUTSEL : Output destination select. (1bit)
															<ul><li>@ref D_IM_LTM_RBK_OUT_SDRAM
																<li>@ref D_IM_LTM_RBK_OUT_MAP_DIRECT</ul>	*/
	UCHAR					data_type;						/**< RIOCTL.W0DTYP : Output data type select(for SDRAM output). (2bits)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	UCHAR					reduction_enable;				/**< RDCMD.RDCEN : Pixel average reduction enable.(1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Pixel average reduction function isn't used
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Pixel average reduction function is used</ul>	*/
	UCHAR					reduction_mode;					/**< RDCMD.RDCMD : Pixel average reduction mode.(2bits)
															<ul><li>@ref D_IM_LTM_RBK_RDC_MODE_DIV_2
																<li>@ref D_IM_LTM_RBK_RDC_MODE_DIV_4
																<li>@ref D_IM_LTM_RBK_RDC_MODE_DIV_8</ul>	*/
	VOID					(*rbk_user_handler)(UINT32* int_status, UINT32 user_param);	/**< Interrupt Handler														*/
	UINT32					user_param;						/**< This set value will return to callback argument value when interrupt occurs.	*/
} T_IM_LTM_RBK_CTRL_COMMON;								/* LTM RBK control	*/

typedef struct {
	UCHAR					burst_length_r;					/**< RAXIBSIZ.BURSTRR : Transfer burst length of the read channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					burst_length_g;					/**< RAXIBSIZ.BURSTRG : Transfer burst length of the read channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					burst_length_b;					/**< RAXIBSIZ.BURSTRB : Transfer burst length of the read channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	USHORT					input_global;					/**< RSDRDEF : Input horizontal Gobal area bytes(16bits, multiple of 16)	*/
	T_IM_LTM_RECT			input_rect;						/**< input image size(and trimming)	*/
	UCHAR					shift_enable;					/**< RSFEN.RSFEN : Right 4bit shift enable.(1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Store data on lower 12bits.
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Right 4bit shift</ul>	*/
} T_IM_LTM_RBK_CTRL_SDRAM_INPUT;					/* LTM RBK SDRAM input mode control	*/

typedef struct {
	UCHAR					top_pixel0;						/**< RIOCTL.BAYER0 : Bayer data first pixel type.(2bits)
															<ul><li>@ref D_IM_LTM_RBK_TOP_PIXEL_R
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_GR
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_GB
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_B</ul>	*/
	UCHAR					top_pixel1;						/**< RIOCTL.BAYER1 : Bayer data first pixel type.(2bits)
															<ul><li>@ref D_IM_LTM_RBK_TOP_PIXEL_R
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_GR
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_GB
																<li>@ref D_IM_LTM_RBK_TOP_PIXEL_B</ul>	*/
	UCHAR					sro_mode;					/**< RIOCTL.SROMD : SRO direct input mode.(1bit)
															<ul><li>@ref D_IM_LTM_RBK_SRO_DIRECT_1
																<li>@ref D_IM_LTM_RBK_SRO_DIRECT_2</ul>	*/
	UCHAR					shift_enable0;					/**< RSFEN.RSFEN0 : Right 2bit shift enable.(1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Store data on lower 12bits.
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Right 2bit shift</ul>	*/
	UCHAR					shift_enable1;					/**< RSFEN.RSFEN1 : Right 2bit shift enable.(1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Store data on lower 12bits.
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Right 2bit shift</ul>	*/
	UCHAR					half_reduction_enable;			/**< HVEN.HVEN : 1/2 reduction enable.(1bit)
															<ul><li>@refImLtm_D_IM_LTM_ENABLE_OFF : 1/2 reduction function isn't used
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : 1/2 reduction function is used</ul>	*/
	T_IM_LTM_RECT			bayer_trim0;					/**< Trimming settings for SRO direct input0	*/
	T_IM_LTM_RECT			bayer_trim1;					/**< Trimming settings for SRO direct input1	*/
} T_IM_LTM_RBK_CTRL_SRO_DIRECT;						/* SRO direct connection mode control	*/

typedef struct {
	UCHAR					trimming_enable;				/**< RTEN.RTEN : Trimming enable (1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Do not do the trimming
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Trimming</ul>			*/
	T_IM_LTM_RECT			rgb_trim;						/**< Trimming settings for RGB	*/
} T_IM_LTM_RBK_RGB_TRIMMING;

typedef struct {
	VOID*					addr;							/**< RSDWAD : Output images top address																		*/
	USHORT					global_width;					/**< RSDWDEF : Output horizontal Gobal area bytes(16bits, multiple of 256 or 512(Depend on burst_length))	*/
} T_IM_LTM_RBK_OUTDATA_INFO;

typedef struct {
	T_IM_LTM_CTRL_AXI_TYPE	rch;								/**< MAXICTLR.ARCACHE, MAXICTLR.ARPROT Read channel types.			*/
	T_IM_LTM_CTRL_AXI_TYPE	wch[D_IM_LTM_MAP_WRITE_PORT_COUNT];	/**< MAXICTLW.AWCACHE_x, MAXICTLW.AWPROT_x Write channel types.		*/
} T_IM_LTM_MAP_CTRL_AXI;

typedef struct {
	UCHAR					rch_axi_stat;					/**< MAXIRERR.RRESP : Read channel status	*/
} T_IM_LTM_MAP_AXI_RCH_STAT;

typedef struct {
	UCHAR					wch_axi_stat[D_IM_LTM_MAP_WRITE_PORT_COUNT];	/**< MAXIWERR.WRESP_x : Write channel status	*/
} T_IM_LTM_MAP_AXI_WCH_STAT;

typedef struct {
	UCHAR					rch_burst_length;				/**< MAXIBSIZ.BURSTR : Transfer burst length of the read channel.(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_yp;			/**< MAXIBSIZ.BURSTWYP : Transfer burst length of the write channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_yn;			/**< MAXIBSIZ.BURSTWYN : Transfer burst length of the write channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write_yp;					/**< MAXIBSIZ.WSTBMSKYP : Writing with mask(YP).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_yn;					/**< MAXIBSIZ.WSTBMSKYN : Writing with mask(YN).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					write_select_yp;				/**< AXICHSEL.AXIWSEL1 : Select the master channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					write_select_yn;				/**< AXICHSEL.AXIWSEL2 : Select the master channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
} T_IM_LTM_MAP_AXI_CTRL_PARAM;

typedef struct {
	USHORT					line_intr;						/**< MLINTLV.LINTLV : Monitor line count setting. (10bits)
															<p>We generate the interrupt request flag when the set value of this register.
															<p>This interrupt request, can be disabled by setting the "000" h.	*/
	UCHAR					wch_burst_length_yp;			/**< MAXIBSIZ.BURSTWYP : Transfer burst length of the write channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_yn;			/**< MAXIBSIZ.BURSTWYN : Transfer burst length of the write channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write_yp;					/**< MAXIBSIZ.WSTBMSKYP : Writing with mask(YP).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_yn;					/**< MAXIBSIZ.WSTBMSKYN : Writing with mask(YN).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					write_select_yp;				/**< AXICHSEL.AXIWSEL1 : Select the master channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
	UCHAR					write_select_yn;				/**< AXICHSEL.AXIWSEL2 : Select the master channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
	UCHAR					data_type_yp;					/**< MIOCTL.W0DTYP : Output data type select(YP)(for SDRAM output). (2bits)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	UCHAR					data_type_yn;					/**< MIOCTL.W1DTYP : Output data type select(YN)(for SDRAM output). (2bits)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	VOID					(*map_user_handler)(UINT32* int_status, UINT32 user_param);	/**< Interrupt Handler														*/
	UINT32					user_param;						/**< This set value will return to callback argument value when interrupt occurs.	*/
} T_IM_LTM_MAP_CTRL_COMMON;								/* LTM MAP control	*/

typedef struct {
	UCHAR					burst_length;					/**< MAXIBSIZ.BURSTR : Transfer burst length of the read channel.(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	USHORT					input_global;					/**< MSDRDEF : Input horizontal Gobal area bytes(16bits, multiple of 16)	*/
	T_IM_LTM_RECT			input_rect;						/**< input image size(and trimming)	*/
	UCHAR					data_type;						/**< MIOCTL.R1DTYP : Input data type select. (2bits)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
} T_IM_LTM_MAP_CTRL_SDRAM_INPUT;					/* LTM MAP SDRAM input mode control	*/

typedef struct {
	VOID*					addr;							/**< MSDRAD : Intput images top address.*/
	UCHAR					top_bit_offset;					/**< MSDROFS : Setting top bit input data area (1bit)<br>
															<p>Set the first bit of the data area.
															   Set the position of the LSB bit in bit position.<br>
															   However, when you select 16-bit in input_dtype(MIOCTL.R1DTYP) is 0.
															   Only when you select a 12-bit pack, please select the setting of 0 or 1.
															<p>exp)<br>
															   I would like the following figure, data and each are stored in 12-bit pack.<br>
															   Assuming that the first pixel data3 at this time,
															   since the position of the LSB and bit 4 data3 address, I set 1.
															   @image html im_ltm_sdrofs_exp.png
															*/
} T_IM_LTM_MAP_INDATA_INFO;

typedef struct {
	VOID*					addr_yp;						/**< MSDWADW0 : Output images top address(YP)									*/
	USHORT					global_width_yp;				/**< MSDWDEFW0 : Output horizontal Gobal area bytes(YP)(16bits, multiple of 8)	*/
	VOID*					addr_yn;						/**< MSDWADW1 : Output images top address(YN)									*/
	USHORT					global_width_yn;				/**< MSDWDEFW1 : Output horizontal Gobal area bytes(YN)(16bits, multiple of 8)	*/
} T_IM_LTM_MAP_OUTDATA_INFO;

typedef struct {
	USHORT					gain_r;							/**< GAINR : WB operation R gain(gain_r / 256)(11bits)	*/
	USHORT					gain_g;							/**< GAING : WB operation G gain(gain_g / 256)(11bits)	*/
	USHORT					gain_b;							/**< GAINB : WB operation B gain(gain_b / 256)(11bits)	*/
	USHORT					clip_r;							/**< GAINCPR : WB operation R clip value(12bits)		*/
	USHORT					clip_g;							/**< GAINCPG : WB operation G clip value(12bits)		*/
	USHORT					clip_b;							/**< GAINCPB : WB operation B clip value(12bits)		*/
} T_IM_LTM_MAP_GAIN;

typedef struct {
	UCHAR					mode0;							/**< PEPS0M.PEPS0M / NEPS0M.NEPS0M : Generation mode(1bit)
															<ul><li>@ref D_IM_LTM_MAP_GENERATION_MODE_0
																<li>@ref D_IM_LTM_MAP_GENERATION_MODE_1</ul>				*/
	USHORT					coef0;							/**< PEPS0OF.PEPS0OF_3 : Generation coefficient(12bits)	*/
	UCHAR					mode1;							/**< PEPS1M.PEPS1M / NEPS1M.NEPS1M : Generation mode(1bit)
															<ul><li>@ref D_IM_LTM_MAP_GENERATION_MODE_0
																<li>@ref D_IM_LTM_MAP_GENERATION_MODE_1</ul>				*/
	USHORT					coef1;							/**< PEPS1OF.PEPS1OF_3 : Generation coefficient(12bits)	*/
	UCHAR					mode2;							/**< PEPS2M.PEPS2M / NEPS2M.NEPS2M : Generation mode(1bit)
															<ul><li>@ref D_IM_LTM_MAP_GENERATION_MODE_0
																<li>@ref D_IM_LTM_MAP_GENERATION_MODE_1</ul>				*/
	USHORT					coef2;							/**< PEPS2OF.PEPS2OF_3 : Generation coefficient(12bits)	*/
} T_IM_LTM_MAP_CTRL_GENERATION_MODE;

typedef struct {
	T_IM_LTM_CTRL_AXI_TYPE	rch_rgb[D_IM_LTM_LTM_READ_RGB_PORT_COUNT];	/**< LAXICTLR1.ARCACHE_x, LAXICTLR1.ARPROT_x Read channel types.	*/
	T_IM_LTM_CTRL_AXI_TYPE	rch_y[D_IM_LTM_LTM_READ_Y_PORT_COUNT];		/**< LAXICTLR2.ARCACHE_x, LAXICTLR2.ARPROT_x Read channel types.	*/
	T_IM_LTM_CTRL_AXI_TYPE	wch[D_IM_LTM_LTM_WRITE_PORT_COUNT];			/**< LAXICTLW.AWCACHE_x, LAXICTLW.AWPROT_x Write channel types.		*/
} T_IM_LTM_LTM_CTRL_AXI;

typedef struct {
	UCHAR					rch_rgb_axi_stat[D_IM_LTM_LTM_READ_RGB_PORT_COUNT];		/**< LAXIRERR.RRESP_R/G/B : Read channel status	*/
	UCHAR					rch_y_axi_stat[D_IM_LTM_LTM_READ_Y_PORT_COUNT];			/**< LAXIRERR.RRESP_YP/YN : Read channel status	*/
} T_IM_LTM_LTM_AXI_RCH_STAT;

typedef struct {
	UCHAR					wch_axi_stat[D_IM_LTM_LTM_WRITE_PORT_COUNT];	/**< LAXIWERR.WRESP_x : Write channel status	*/
} T_IM_LTM_LTM_AXI_WCH_STAT;

typedef struct {
	UCHAR					rch_burst_length_r;				/**< LAXIBSIZ.BURSTRR : Transfer burst length of the read channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_g;				/**< LAXIBSIZ.BURSTRG : Transfer burst length of the read channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_b;				/**< LAXIBSIZ.BURSTRB : Transfer burst length of the read channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_yp;			/**< LAXIBSIZ.BURSTRYP : Transfer burst length of the read channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_yn;			/**< LAXIBSIZ.BURSTRYN : Transfer burst length of the read channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_r;				/**< LAXIBSIZ.BURSTWR : Transfer burst length of the write channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_g;				/**< LAXIBSIZ.BURSTWG : Transfer burst length of the write channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_b;				/**< LAXIBSIZ.BURSTWB : Transfer burst length of the write channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write_r;					/**< LAXIBSIZ.WSTBMSKR : Writing with mask(R).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_g;					/**< LAXIBSIZ.WSTBMSKG : Writing with mask(G).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_b;					/**< LAXIBSIZ.WSTBMSKB : Writing with mask(B).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					read_select_yp;					/**< AXIRSEL.AXIRSEL1 : Select the master channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
	UCHAR					read_select_yn;					/**< AXIRSEL.AXIRSEL2 : Select the master channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
} T_IM_LTM_LTM_AXI_CTRL_PARAM;

typedef struct {
	USHORT					line_intr;						/**< LLINTLV.LINTLV : Monitor line count setting. (14bits)
															<p>We generate the interrupt request flag when the set value of this register.
															<p>This interrupt request, can be disabled by setting the "0000" h.	*/
	UCHAR					rch_burst_length_yp;			/**< LAXIBSIZ.BURSTRYP : Transfer burst length of the read channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_yn;			/**< LAXIBSIZ.BURSTRYN : Transfer burst length of the read channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_r;				/**< LAXIBSIZ.BURSTWR : Transfer burst length of the write channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_g;				/**< LAXIBSIZ.BURSTWG : Transfer burst length of the write channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					wch_burst_length_b;				/**< LAXIBSIZ.BURSTWB : Transfer burst length of the write channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					mask_write_r;					/**< LAXIBSIZ.WSTBMSKR : Writing with mask(R).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_g;					/**< LAXIBSIZ.WSTBMSKG : Writing with mask(G).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					mask_write_b;					/**< LAXIBSIZ.WSTBMSKB : Writing with mask(B).(1bit)
															<ul><li>@ref D_IM_LTM_MASK_WRITE_ENABLE
																<li>@ref D_IM_LTM_MASK_WRITE_DISABLE</ul>	*/
	UCHAR					read_select_yp;					/**< AXIRSEL.AXIRSEL1 : Select the master channel(YP).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
	UCHAR					read_select_yn;					/**< AXIRSEL.AXIRSEL2 : Select the master channel(YN).(1bit)
															<ul><li>@ref D_IM_LTM_PORT_DEFAULT
																<li>@ref D_IM_LTM_PORT_SWITCH</ul>	*/
	UCHAR					in_data_type_yp;				/**< LIOCTL.R3DTYP : Select the input data type(YP).(1bit)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	UCHAR					in_data_type_yn;				/**< LIOCTL.R4DTYP : Select the input data type(YN).(1bit)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	UCHAR					out_select;						/**< LIOCTL.OUTSEL : Output destination select.(1bit)
															<ul><li>@ref D_IM_LTM_LTM_OUT_SDRAM
																<li>@ref D_IM_LTM_LTM_OUT_R2Y_DIRECT</ul>	*/
	UCHAR					out_data_type;					/**< LIOCTL.W1DTYP : Select the output data type.(1bit)
															<ul><li>@ref D_IM_LTM_DTYP_PACK12
																<li>@ref D_IM_LTM_DTYP_UNPACK12</ul>	*/
	T_IM_LTM_RECT			input_rect;						/**< input image size(and trimming) for MAP images(YP/YN)	*/
	USHORT					global_width_yp;				/**< LSDWDEFR3 : Input horizontal Gobal area bytes(YP)(16bits, multiple of 16)	*/
	USHORT					global_width_yn;				/**< LSDWDEFR4 : Input horizontal Gobal area bytes(YN)(16bits, multiple of 16)	*/
	VOID					(*ltm_user_handler)(UINT32* int_status, UINT32 user_param);	/**< Interrupt Handler														*/
	UINT32					user_param;						/**< This set value will return to callback argument value when interrupt occurs.	*/
} T_IM_LTM_LTM_CTRL_COMMON;								/* LTM MAP control	*/

typedef struct {
	UCHAR					rch_burst_length_r;				/**< LAXIBSIZ.BURSTRR : Transfer burst length of the read channel(R).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_g;				/**< LAXIBSIZ.BURSTRG : Transfer burst length of the read channel(G).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	UCHAR					rch_burst_length_b;				/**< LAXIBSIZ.BURSTRB : Transfer burst length of the read channel(B).(1bit)
															<ul><li>@ref D_IM_LTM_BRST_512
																<li>@ref D_IM_LTM_BRST_256</ul>				*/
	USHORT					input_global_rgb;				/**< LSDRDEFR2 : Input rgb image's horizontal Gobal area bytes(16bits, multiple of 16)	*/
	T_IM_LTM_RECT			input_rect;						/**< input image size(and trimming) for RGB images	*/
} T_IM_LTM_LTM_CTRL_SDRAM_INPUT;					/* LTM MAP SDRAM input mode control	*/

typedef struct {
	VOID*					addr_yp;						/**< LSDRADR3 : Intput images top address(YP).*/
	VOID*					addr_yn;						/**< LSDRADR4 : Intput images top address(YN).*/
	UCHAR					top_bit_offset_yp;				/**< LSDROFS.SDROFSR3 : Setting top bit input data area(YP) (1bit)<br>
															<p>Set the first bit of the data area.
															   Set the position of the LSB bit in bit position.<br>
															   However, when you select 16-bit in input_dtype(LIOCTL.R3DTYP) is 0.
															   Only when you select a 12-bit pack, please select the setting of 0 or 1.
															<p>exp)<br>
															   I would like the following figure, data and each are stored in 12-bit pack.<br>
															   Assuming that the first pixel data3 at this time,
															   since the position of the LSB and bit 4 data3 address, I set 1.
															   @image html im_ltm_sdrofs_exp.png
															*/
	UCHAR					top_bit_offset_yn;				/**< LSDROFS.SDROFSR4 : Setting top bit input data area(YN) (1bit)<br>
															<p>Set the first bit of the data area.
															   Set the position of the LSB bit in bit position.<br>
															   However, when you select 16-bit in input_dtype(LIOCTL.R4DTYP) is 0.
															   Only when you select a 12-bit pack, please select the setting of 0 or 1.
															<p>exp)<br>
															   I would like the following figure, data and each are stored in 12-bit pack.<br>
															   Assuming that the first pixel data3 at this time,
															   since the position of the LSB and bit 4 data3 address, I set 1.
															   @image html im_ltm_sdrofs_exp.png
															*/
} T_IM_LTM_LTM_INDATA_INFO;

typedef struct {
	VOID*					addr[D_IM_LTM_LTM_WRITE_PORT_COUNT];			/**< LSDWADWR/LSDWADWG/LSDWADWB : Output images top address						*/
	USHORT					global_width[D_IM_LTM_LTM_WRITE_PORT_COUNT];	/**< LSDWDEFR/LSDWDEFG/LSDWDEFB : Output horizontal Gobal area bytes(16bits, multiple of 8)	*/
} T_IM_LTM_LTM_OUTDATA_INFO;

typedef struct {
	T_IM_LTM_RECT			input_rect;						/**< input image size for RGB images	*/
	UCHAR					bypass;							/**< LIOCTL.BYPASS : bypass mode.(1bit)
															<ul><li>@ref ImLtm_D_IM_LTM_ENABLE_OFF : Normal operation
																<li>@ref ImLtm_D_IM_LTM_ENABLE_ON : Bypass</ul>	*/
} T_IM_LTM_LTM_CTRL_B2R_DIRECT;						/* B2R direct connection mode control	*/

typedef struct {
	UINT32					hsta;							/**< LHSTA : Horizontal start position(25bits)	*/
	USHORT					hpit;							/**< LHPIT : Horizontal pitch size(15bits)		*/
	UINT32					vsta;							/**< LVSTA : Vertical start position(25bits)	*/
	USHORT					vpit;							/**< LVPIT : Vertical pitch size(15bits)		*/
} T_IM_LTM_LTM_MAP_RESIZE_PITCH;

typedef struct {
	USHORT					strength;						/**< NLVTHOF7, PLVTHOF7 : High frequency strength(13bits, 0~4096)	*/
} T_IM_LTM_LTM_CTRL_HF_STRENGTH;

typedef struct {
	UCHAR					ratio;							/**< BLDYRT : Blend ratio(4bits, 0~8)		*/
	USHORT					offset[8];						/**< BLDOF.BLDOF_x : Offset(13bits, 0~4096)	*/
	SHORT					gain[8];						/**< BLDGA.BLDGA_x : Gain(15bits)			*/
	USHORT					border[8];						/**< BLDBD.BLDBD_x : Border(12bits)			*/
	UCHAR					mode;							/**< LTMMD : Mode(1bit)						*/
} T_IM_LTM_LTM_CTRL_BLEND;

typedef struct {
	USHORT					offset[8];						/**< CGOF.CGOF_x : Offset(13bits, 0~4096)	*/
	SHORT					gain[8];						/**< CGGA.CGGA_x : Gain(13bits)				*/
	USHORT					border[7];						/**< CGBD.CGBD_x : Border(12bits)			*/
} T_IM_LTM_LTM_CTRL_CHROMA;

struct _ImLtm {
	KObject parent;
};

KConstType 		    im_ltm_get_type(void);
ImLtm*		            im_ltm_new(void);

extern INT32 Im_LTM_On_Pclk( UCHAR pipe_no );
extern INT32 Im_LTM_Off_Pclk( UCHAR pipe_no );
extern INT32 Im_LTM_Force_Off_Pclk( UCHAR pipe_no );
extern INT32 Im_LTM_On_Hclk( UCHAR pipe_no );
extern INT32 Im_LTM_Off_Hclk( UCHAR pipe_no );
extern INT32 Im_LTM_Force_Off_Hclk( UCHAR pipe_no );
extern INT32 Im_LTM_On_Aclk( UCHAR pipe_no );
extern INT32 Im_LTM_Off_Aclk( UCHAR pipe_no );
extern INT32 Im_LTM_Force_Off_Aclk( UCHAR pipe_no );
extern INT32 Im_LTM_On_Clk( UCHAR pipe_no );
extern INT32 Im_LTM_Off_Clk( UCHAR pipe_no );
extern INT32 Im_LTM_Force_Off_Clk( UCHAR pipe_no );
extern INT32 Im_LTM_On_RBKClk( UCHAR pipe_no );
extern INT32 Im_LTM_Off_RBKClk( UCHAR pipe_no );
extern INT32 Im_LTM_Force_Off_RBKClk( UCHAR pipe_no );
extern INT32 Im_LTM_Init_All_Block( UCHAR pipe_no );
extern INT32 Im_LTM_SW_Reset_All_Block( UCHAR pipe_no );
extern INT32 Im_LTM_Stop_All_Block( UCHAR pipe_no );
extern VOID Im_LTM_Int_Handler( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Init( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_SW_Reset( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_AXI* const ctrl_axi );
extern INT32 Im_LTM_MAP_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_RCH_STAT* const axi_read_stat );
extern INT32 Im_LTM_MAP_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_MAP_AXI_WCH_STAT* const axi_write_stat );
extern INT32 Im_LTM_MAP_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 Im_LTM_MAP_Set_AxiCtrlParam( UCHAR pipe_no, const T_IM_LTM_MAP_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 Im_LTM_MAP_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_COMMON* const map_ctrl );
extern INT32 Im_LTM_MAP_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_SDRAM_INPUT* const map_ctrl_sdram_input );
extern INT32 Im_LTM_MAP_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_INDATA_INFO* const in_data_info );
extern INT32 Im_LTM_MAP_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_MAP_OUTDATA_INFO* const out_data_info );
extern INT32 Im_LTM_MAP_Ctrl_ModeRBKDirect( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Set_FrameStop( UCHAR pipe_no, UCHAR onoff );
extern INT32 Im_LTM_MAP_Set_ParamHold( UCHAR pipe_no, const UCHAR hold_enable );
extern INT32 Im_LTM_MAP_Get_MapBusy( UCHAR pipe_no, BOOL* const busy_status );
extern INT32 Im_LTM_MAP_ContStart( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Start( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Stop( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );
extern VOID Im_LTM_MAP_Int_Handler( UCHAR pipe_no );
extern INT32 Im_LTM_MAP_Set_WB_Gain( UCHAR pipe_no, const T_IM_LTM_MAP_GAIN* const wb_gain );
extern INT32 Im_LTM_MAP_Ctrl_Generation_Mode( UCHAR pipe_no, const T_IM_LTM_MAP_CTRL_GENERATION_MODE* const mode );
extern INT32 Im_LTM_MAP_Get_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param );
extern INT32 Im_LTM_MAP_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl );
extern INT32 Im_LTM_MAP_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no );
extern INT32 Im_LTM_MAP_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl );
extern INT32 Im_LTM_LTM_Init( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_SW_Reset( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_Ctrl_Axi( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_AXI* const ctrl_axi );
extern INT32 Im_LTM_LTM_Get_AxiReadStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_RCH_STAT* const axi_read_stat );
extern INT32 Im_LTM_LTM_Get_AxiWriteStat( UCHAR pipe_no, T_IM_LTM_LTM_AXI_WCH_STAT* const axi_write_stat );
extern INT32 Im_LTM_LTM_Get_AxiCtrlParam( UCHAR pipe_no, T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 Im_LTM_LTM_Set_AxiCtrlParam( UCHAR pipe_no, const T_IM_LTM_LTM_AXI_CTRL_PARAM* const axi_ctrl_prm );
extern INT32 Im_LTM_LTM_Ctrl_Common( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_COMMON* const ltm_ctrl );
extern INT32 Im_LTM_LTM_Ctrl_ModeSDRAMInput( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_SDRAM_INPUT* const ltm_ctrl_sdram_input );
extern INT32 Im_LTM_LTM_Set_InAddr_Info_Rgb( UCHAR pipe_no, const T_IM_LTM_INADDR_INFO* const in_addr );
extern INT32 Im_LTM_LTM_Set_InData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_INDATA_INFO* const in_data_info );
extern INT32 Im_LTM_LTM_Set_OutData_Info( UCHAR pipe_no, const T_IM_LTM_LTM_OUTDATA_INFO* const out_data_info );
extern INT32 Im_LTM_LTM_Ctrl_ModeB2RDirect( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_B2R_DIRECT* const ltm_ctrl_b2r_direct );
extern INT32 Im_LTM_LTM_Set_MapImage_Resize_Pitch_Auto( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_Set_MapImage_Resize_Pitch( UCHAR pipe_no, const T_IM_LTM_LTM_MAP_RESIZE_PITCH* const resize_pitch );
extern INT32 Im_LTM_LTM_Set_FrameStop( UCHAR pipe_no, UCHAR onoff );
extern INT32 Im_LTM_LTM_Set_ParamHold( UCHAR pipe_no, const UCHAR hold_enable );
extern INT32 Im_LTM_LTM_Get_LtmBusy( UCHAR pipe_no, BOOL* const busy_status );
extern INT32 Im_LTM_LTM_ContStart( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_Start( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_Stop( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_WaitEnd( DDIM_USER_FLGPTN* const p_flgptn, DDIM_USER_FLGPTN waiptn, DDIM_USER_TMO tmout );
extern VOID 	Im_LTM_LTM_Int_Handler( UCHAR pipe_no );
extern INT32 Im_LTM_LTM_Set_High_Frequency_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_HF_STRENGTH* hf_ctrl );
extern INT32 Im_LTM_LTM_Set_Internal_Param( UCHAR pipe_no, T_IM_LTM_INTERNAL_PARAM* const param );
extern INT32 Im_LTM_LTM_Ctrl_Blend( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_BLEND* blend_ctrl );
extern INT32 Im_LTM_LTM_Set_RCG_Table( UCHAR pipe_no, const USHORT* const src_tbl );
extern INT32 Im_LTM_LTM_Ctrl_Chroma_Correction_Strength( UCHAR pipe_no, const T_IM_LTM_LTM_CTRL_CHROMA* chroma_ctrl );
extern INT32 Im_LTM_LTM_Ctrl_Ylog_Tbl( UCHAR pipe_no, const T_IM_LTM_CTRL_YLOG* const ylog_ctrl );
extern INT32 Im_LTM_LTM_Get_Active_Ylog_Tbl_No( UCHAR pipe_no, UCHAR* const tbl_no );
extern INT32 Im_LTM_LTM_Set_YLOG_Table( UCHAR pipe_no, UCHAR tbl_sel, const USHORT* const src_tbl );


#endif /* __IM_LTM_H__ */

























