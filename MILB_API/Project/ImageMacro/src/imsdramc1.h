/*
 * imsdramc1.h
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#ifndef __IM_SDRAMC1_H__
#define __IM_SDRAMC1_H__

#include <klib.h>
#include "driver_common.h"
#include "imsdramc.h"

#define IM_TYPE_SDRAMC1		(im_sdramc1_get_type())
#define IM_SDRAMC1(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImSdramc1))
#define IM_IS_SDRAMC1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImSdramc1))

typedef struct _ImSdramc1 ImSdramc1;
struct _ImSdramc1 {
	KObject parent;
};

KConstType 		    		im_sdramc1_get_type(void);
ImSdramc1*		            im_sdramc1_new(void);

extern INT32 im_sdramc_set_acceptancecapability( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const UCHAR rnum, const UCHAR wnum );
extern INT32 im_sdramc_get_acceptancecapability( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, UCHAR* const rnum, UCHAR* const wnum );
extern INT32 im_sdramc_set_burstlimit( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const E_IM_SDRAMC_BURST_LIMIT rsize, const E_IM_SDRAMC_BURST_LIMIT wsize );
extern INT32 im_sdramc_get_burstlimit( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_BURST_LIMIT* const rsize, E_IM_SDRAMC_BURST_LIMIT* const wsize );
extern INT32 im_sdramc_set_remapaddr( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, const LONG addr );
extern INT32 im_sdramc_get_remapaddr( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, LONG* const addr );
extern INT32 im_sdramc_set_ch_select( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port);
extern INT32 im_sdramc_get_ch_select( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_CH* chsel );
extern INT32 im_sdramc_set_cmd_arbitration_rate( E_IM_SDRAMC_CH ch, const T_IM_SDRAMC_CMD_ARB_RATE* const cmd_arb );
extern INT32 im_sdramc_get_cmd_arbitration_rate( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_CMD_ARB_RATE* const cmd_arb );
extern INT32 im_sdramc_set_cmd_arbitration_priority( E_IM_SDRAMC_CH ch, const T_IM_SDRAMC_CMD_ARB_PRI* const cmd_arb );
extern INT32 im_sdramc_get_cmd_arbitration_priority( E_IM_SDRAMC_CH ch, T_IM_SDRAMC_CMD_ARB_PRI* const cmd_arb );
extern INT32 im_sdramc_set_mode_register( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_RANK rank, const UCHAR ma, const UCHAR data );
extern INT32 im_sdeamc_get_mode_register( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_RANK rank, const UCHAR ma, UCHAR* const data );
extern INT32 im_sdramc_set_clock_enable_busIf( E_IM_SDRAMC_CH ch, E_IM_SDRAMC_PORT port, E_IM_SDRAMC_ACCESS access, E_IM_SDRAMC_EN enable );

#endif /* __IM_SDRAMC1_H__ */


