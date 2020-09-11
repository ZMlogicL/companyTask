该文件未到1000行，未进行拆分。
公有方法改动：


(形参 ImImg*self  ;   im_img_new())

1、Im_IMG_Init       改成了      im_img_init

2、Im_IMG_Get_IMGPIPEPSW    改成了     im_img_get_imgpipepsw

3、Im_IMG_Set_IMGPIPEPSW   改成了    im_img_set_imgpipepsw

4、Im_IMG_Get_MXICMON    改成了    im_img_get_mxicmon

5、Im_IMG_Set_MXICMON    改成了     im_img_set_mxicmon

6、Im_IMG_Get_SRAMPD   改成了    im_img_get_srampd

7、Im_IMG_Set_SRAMPD   改成了   im_img_set_srampd


im_img.h中的枚举，结构体，宏定义等    改到了im_img.h中

/** IMGPIPEPSW type */
typedef enum {
	E_IM_IMG_IMGPIPEPSW_R2YSEL = 0,		/**< IMGPIPEPSW.R2YSEL : R2Y input select */
	E_IM_IMG_IMGPIPEPSW_B2RCNC			/**< IMGPIPEPSW.B2RCNC : B2R connection select */
} E_IM_IMG_IMGPIPEPSW_TYP;
改成了
/** IMGPIPEPSW type */
typedef enum {
	ImImg_IMGPIPEPSW_R2YSEL = 0,		/**< IMGPIPEPSW.R2YSEL : R2Y input select */
	ImImg_IMGPIPEPSW_B2RCNC			/**< IMGPIPEPSW.B2RCNC : B2R connection select */
} ImImgImgpipepswTyp;


/** IMGPIPEPSW select */
typedef enum {
	E_IM_IMG_IMGPIPEPSW_B2R = 0,		/**< [R2Y input]B2R  / [B2R connection]NONE */
	E_IM_IMG_IMGPIPEPSW_LTM,			/**< [R2Y input]LTM  / [B2R connection]LTM  */
	E_IM_IMG_IMGPIPEPSW_NONE			/**< [R2Y input]NONE / [B2R connection]NONE */
} E_IM_IMG_IMGPIPEPSW_SEL;
改成了
/** IMGPIPEPSW select */
typedef enum {
	ImImg_IMGPIPEPSW_B2R = 0,		/**< [R2Y input]B2R  / [B2R connection]NONE */
	ImImg_IMGPIPEPSW_LTM,			/**< [R2Y input]LTM  / [B2R connection]LTM  */
	ImImg_IMGPIPEPSW_NONE			/**< [R2Y input]NONE / [B2R connection]NONE */
} ImImgImgpipeswSel;


/** MXICMON type */
typedef enum {
	E_IM_IMG_MXICMON_VDEN = 0,			/**< MXICMON.VDEN   : MXIC VD enable */
	E_IM_IMG_MXICMON_HDEN,				/**< MXICMON.HDEN   : MXIC HD enable */
	E_IM_IMG_MXICMON_SENEN,				/**< MXICMON.SENEN  : MXIC SEN  ERROR enable */
	E_IM_IMG_MXICMON_SRO1EN,			/**< MXICMON.SRO1EN : MXIC SRO1 ERROR enable */
	E_IM_IMG_MXICMON_SRO2EN,			/**< MXICMON.SRO2EN : MXIC SRO2 ERROR enable */
	E_IM_IMG_MXICMON_B2B1EN,			/**< MXICMON.B2B1EN : MXIC B2B1 ERROR enable */
	E_IM_IMG_MXICMON_B2B2EN,			/**< MXICMON.B2B2EN : MXIC B2B2 ERROR enable */
	E_IM_IMG_MXICMON_YO1EN,				/**< MXICMON.YO1EN  : MXIC R2Y1 ERROR enable */
	E_IM_IMG_MXICMON_YO2EN,				/**< MXICMON.YO2EN  : MXIC R2Y2 ERROR enable */
	E_IM_IMG_MXICMON_STATEN,			/**< MXICMON.STATEN : MXIC STAT ERROR enable */
	E_IM_IMG_MXICMON_PASEN,				/**< MXICMON.PASEN  : MXIC PAS  ERROR enable */
	E_IM_IMG_MXICMON_DEN				/**< MXICMON.DEN    : MXIC DISP ERROR enable */
} E_IM_IMG_MXICMON_TYP;
改成了
/** MXICMON type */
typedef enum {
	ImImg_MXICMON_VDEN = 0,			/**< MXICMON.VDEN   : MXIC VD enable */
	ImImg_MXICMON_HDEN,				/**< MXICMON.HDEN   : MXIC HD enable */
	ImImg_MXICMON_SENEN,				/**< MXICMON.SENEN  : MXIC SEN  ERROR enable */
	ImImg_MXICMON_SRO1EN,			/**< MXICMON.SRO1EN : MXIC SRO1 ERROR enable */
	ImImg_MXICMON_SRO2EN,			/**< MXICMON.SRO2EN : MXIC SRO2 ERROR enable */
	ImImg_MXICMON_B2B1EN,			/**< MXICMON.B2B1EN : MXIC B2B1 ERROR enable */
	ImImg_MXICMON_B2B2EN,			/**< MXICMON.B2B2EN : MXIC B2B2 ERROR enable */
	ImImg_MXICMON_YO1EN,				/**< MXICMON.YO1EN  : MXIC R2Y1 ERROR enable */
	ImImg_MXICMON_YO2EN,				/**< MXICMON.YO2EN  : MXIC R2Y2 ERROR enable */
	ImImg_MXICMON_STATEN,			/**< MXICMON.STATEN : MXIC STAT ERROR enable */
	ImImg_MXICMON_PASEN,				/**< MXICMON.PASEN  : MXIC PAS  ERROR enable */
	ImImg_MXICMON_DEN				/**< MXICMON.DEN    : MXIC DISP ERROR enable */
} ImImgMxicmonTyp;


/** MXICMON status */
typedef enum {
	E_IM_IMG_MXICMON_DISABLE = 0,		/**< Disable */
	E_IM_IMG_MXICMON_ENABLE				/**< Enable  */
} E_IM_IMG_MXICMON_STS;
改成了
/** MXICMON status */
typedef enum {
	ImImg_MXICMON_DISABLE = 0,		/**< Disable */
	ImImg_MXICMON_ENABLE				/**< Enable  */
} ImImgMxicmonSts;


/** SRAMPD type */
typedef enum {
	ImImg_SRAMPD_Y01 = 0,			/**< Data placement conversion PBUF for Y0-1 */
	ImImg_SRAMPD_Y23,				/**< Data placement conversion PBUF for Y2-3 */
	ImImg_SRAMPD_C					/**< Data placement conversion PBUF for C    */
} ImImgSrampdTyp;
改成了
/** SRAMPD type */
typedef enum {
	ImImg_SRAMPD_Y01 = 0,			/**< Data placement conversion PBUF for Y0-1 */
	ImImg_SRAMPD_Y23,				/**< Data placement conversion PBUF for Y2-3 */
	ImImg_SRAMPD_C					/**< Data placement conversion PBUF for C    */
} ImImgSrampdTyp;


