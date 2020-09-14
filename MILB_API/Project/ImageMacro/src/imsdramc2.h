/*
 * imsdramc2.h
 *
 *  Created on: 2020年9月3日
 *      Author: sns
 */

#ifndef __IM_SDRAMC2_H__
#define __IM_SDRAMC2_H__

#include <klib.h>

#define IM_TYPE_SDRAMC2			(im_sdramc2_get_type())
#define IM_SDRAMC2(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImSdramc2))
#define IM_IS_SDRAMC2(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImSdramc2))

typedef struct _ImSdramc2 ImSdramc2;
struct _ImSdramc2 {
	KObject parent;
};

KConstType 		    		im_sdramc2_get_type(void);
ImSdramc2*		            im_sdramc2_new(void);

#endif /* __IM_SDRAMC2_H__ */


