/*
*@Copyright (C) 2010-2019 上海网用软件有限公司
*@date                :2020-09-10
*@author              :jianghaodong
*@brief               :CtImRbkRun1类
*@rely                :klib
*@function
*
*设计的主要功能:
*1、
*@version
*
*/

#ifndef __CT_IM_RBK_RUN1_H_
#define __CT_IM_RBK_RUN1_H_

#include "im_ltm.h"

#include "./../../../fj/glib/src/gobject.h"


G_BEGIN_DECLS

#define CT_TYPE_IM_RBK_RUN1						(ct_im_rbk_run1_get_type())
#define CT_IM_RBK_RUN1(obj)						(G_TYPE_CHECK_INSTANCE_CAST (obj, CtImRbkRun1))
#define CT_IM_RBK_RUN1_CLASS(klass)			(G_TYPE_CHECK_CLASS_CAST ((klass), CT_TYPE_IM_RBK_RUN1, CtImRbkRun1Class))
#define CT_IS_IM_RBK_RUN1(obj)					(G_TYPE_CHECK_INSTANCE_TYPE ((obj), CT_TYPE_IM_RBK_RUN1)) 
#define CT_IS_IM_RBK_RUN1_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), CT_TYPE_IM_RBK_RUN1))
#define CT_IM_RBK_RUN1_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), CT_TYPE_IM_RBK_RUN1, CtImRbkRun1Class))

/*----------------------------------------------------------------------*/
/* Macro																*/
/*----------------------------------------------------------------------*/
#define ct_im_ltm_rbk_check_target_pipe_no_1(a)		(((a)+1) & (D_IM_LTM_PIPE1+1))
#define ct_im_ltm_rbk_check_target_pipe_no_2(a)		(((a)+1) & (D_IM_LTM_PIPE2+1))


typedef struct 			_CtImRbkRun1 CtImRbkRun1;
typedef struct 			_CtImRbkRun1Class CtImRbkRun1Class;
typedef struct 			_CtImRbkRun1Private CtImRbkRun1Private;

struct _CtImRbkRun1
{
	GObject parent;
	guchar pipeNo;
};

struct _CtImRbkRun1Class
{
	GObjectClass parentclass;
};


GType 						ct_im_rbk_run1_get_type(void);
CtImRbkRun1 *		ct_im_rbk_run1_new(void);

gint32 						ct_im_rbk_run1_rbk_1_1(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_2(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_3(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_4(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_5(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_6(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_7(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_8(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_9(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_10(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_11(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_12(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_13(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_14(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_15(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_16(CtImRbkRun1* self);
gint32 						ct_im_rbk_run1_rbk_1_17(CtImRbkRun1* self);

T_IM_LTM_RBK_CTRL_COMMON *
								ct_im_rbk_run1_get_gct_im_ltm_rbk_ctrl_common_base(CtImRbkRun1* self);
void 						ct_im_rbk_run1_set_pipe_no(CtImRbkRun1* self, guchar pipeNo);
guchar 					ct_im_rbk_run1_get_pipe_no(CtImRbkRun1* self);


G_END_DECLS

#endif /* __CT_IM_RBK_RUN1_H_ */
