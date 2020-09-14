/*
 * impro1.h
 *
 *  Created on: 2020年9月4日
 *      Author: sns
 */


#ifndef __IM_PRO1_H__
#define __IM_PRO1_H__

#include <klib.h>
#include "driver_common.h"
#include "impro.h"

#define IM_TYPE_PRO1			(im_pro1_get_type())
#define IM_PRO1(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, ImPro1))
#define IM_IS_PRO1(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, ImPro1))

typedef struct _ImPro1 ImPro1;


typedef enum {
	E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK_SRO = 0,	/**< FFC/CAG macro are used in SRO unit	*/
	E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK_B2B,		/**< FFC/CAG macro are used in B2B unit */
	E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK_MAX		/**< MAX value	*/
} E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK;

typedef enum {
	E_IM_PRO_B2BTOP_CLK_TYPE_B2BCLK = 0,		/**< B2BCLK		*/
} E_IM_PRO_B2BTOP_CLK_TYPE;

typedef enum {
	E_IM_PRO_ORG_R = 0,				/**< R pixel standard	*/
	E_IM_PRO_ORG_B,					/**< B pixel standard	*/
	E_IM_PRO_ORG_GR,				/**< Gr pixel standard	*/
	E_IM_PRO_ORG_GB					/**< Gb pixel standard	*/
} E_IM_PRO_ORG;

typedef enum {
	E_IM_PRO_B2BTOP_INPUT_MODE_DIRECT = 0,	/**< SRO direct connection mode	*/
	E_IM_PRO_B2BTOP_INPUT_MODE_REINPUT,		/**< Bayer data re-input mode	*/
	E_IM_PRO_B2BTOP_INPUT_MODE_MAX			/**< MAX value	*/
} E_IM_PRO_B2BTOP_INPUT_MODE;

typedef struct {
	E_IM_PRO_B2BTOP_INPUT_MODE			input_mode;					/**< Select the input mode of B2B unit. B2BTOPCTL1@@B2BISW */
	E_IM_PRO_B2BTOP_CAG_TARGET_BLOCK	cag_target_sel;				/**< Select in which unit FFC/CAG macro are used, SRO or B2B. B2BTOPCTL1@@CAGSL */
	E_IM_PRO_ORG						first_pixel[2];				/**< Select an Bayer first pixel for each PAT block input B2BTOPCTL2@@ORG0-@@ORG1 */
} T_IM_PRO_B2BTOP_CTRL;

typedef enum {
	E_IM_PRO_ELF_ELFAFS_MAIN_PATH = 0,	/**< Main line path output signal is selected.	*/
	E_IM_PRO_ELF_ELFAFS_NR_PATH			/**< Synthesis noise reduction signal is selected.	*/
} E_IM_PRO_ELF_ELFAFS;

typedef enum {
	E_IM_PRO_ELF_PDD_MODE_SURROUND_4PIX = 0,	/**< ELF processing is executed with reference to surrounding 4 pixels.	*/
	E_IM_PRO_ELF_PDD_MODE_SURROUND_8PIX			/**< ELF processing is executed with reference to surrounding 8 pixels.	*/
} E_IM_PRO_ELF_PDD_MODE;

typedef enum {
	E_IM_PRO_ELF_PDD_DIS = 0,		/**< Disable	*/
	E_IM_PRO_ELF_PDD_EN				/**< Enable		*/
} E_IM_PRO_ELF_PDD_ENABLE;

typedef struct {
	E_IM_PRO_ELF_PDD_ENABLE	pix_padding;		/**< input around padding<br>
													target registor	:@@ELFPDD */
	E_IM_PRO_ELF_PDD_MODE	padding_mode;		/**< Pixel padding mode.<br>
													target registor	:@@ELFRNG */
	E_IM_PRO_ELF_ELFAFS		nr_select;			/**< NR AF input selection path<br>
													target registor	:@@ELFAFS */
} T_IM_PRO_ELF_COMMON_CTRL;

typedef struct {
	USHORT	elfl1;		/**< One global horizontal size<br>
							value range		:[0 - 4095] ELFL1<=ELFL2<=ELFL3<=ELFL4<br>
							target registor	:@@ELFL1	*/
	USHORT	elfl2;		/**< Two global horizontal size<br>
							value range		:[0 - 4095]<br>
							target registor	:@@ELFL2	*/
	USHORT	elfl3;		/**< Three global horizontal size<br>
							value range		:[0 - 4095]<br>
							target registor	:@@ELFL3	*/
	USHORT	elfl4;		/**< 4 global horizontal size<br>
							value range		:[0 - 4095]<br>
							target registor	:@@ELFL4	*/
} T_IM_PRO_ELF_COMMON2;

typedef enum {
	E_IM_PRO_ELF_NLA0EN_DIS = 0,	/**< Disable	*/
	E_IM_PRO_ELF_NLA0EN_EN 			/**< Enable		*/
} E_IM_PRO_ELF_NLA0EN;

typedef enum {
	E_IM_PRO_ELF_EFMD_DIS = 0,		/**< Disable	*/
	E_IM_PRO_ELF_EFMD_EN			/**< Enable		*/
} E_IM_PRO_ELF_EFMD;

typedef enum {
	E_IM_PRO_ELF_F9_MD_STRONG = 0,	/**< Filter is a strong	*/
	E_IM_PRO_ELF_F9_MD_WEAK			/**< Filter is weak		*/
} E_IM_PRO_ELF_F9_MD;

typedef enum {
	E_IM_PRO_ELF_F5_MD_STRONG = 0,	/**< Filter is a strong	*/
	E_IM_PRO_ELF_F5_MD_WEAK			/**< Filter is weak		*/
} E_IM_PRO_ELF_F5_MD;

typedef enum {
	E_IM_PRO_ELF_NFS9EN_DIS = 0,		/**< Disable	*/
	E_IM_PRO_ELF_NFS9EN_EN 			/**< Enable		*/
} E_IM_PRO_ELF_NFS9EN;

typedef enum {
	E_IM_PRO_ELF_LFMD_DIS = 0,		/**< Disable	*/
	E_IM_PRO_ELF_LFMD_EN      		/**< Enable		*/
} E_IM_PRO_ELF_LFMD;

typedef enum {
	E_IM_PRO_ELF_N5S9EN_DIS = 0,	/**< Disable	*/
	E_IM_PRO_ELF_N5S9EN_EN 			/**< Enable		*/
} E_IM_PRO_ELF_N5S9EN;

typedef enum {
	E_IM_PRO_ELF_N1S5EN_DIS = 0,	/**< Disable	*/
	E_IM_PRO_ELF_N1S5EN_EN			/**< Enable		*/
} E_IM_PRO_ELF_N1S5EN;

typedef struct {
	E_IM_PRO_ELF_N1S5EN		n1s5_enable			:1;		/**< Reference to the noise component Ns1s5<br>
															target registor	:@@N1S5EN */
	E_IM_PRO_ELF_N5S9EN		n5s9_enable			:1;		/**< Reference to the noise component Ns5s9<br>
															target registor	:@@N5S9EN */
	E_IM_PRO_ELF_NFS9EN		f9_enable			:1;		/**< Byr9 to blend in noise suppression<br>
															target registor	:@@NFS9EN */
	E_IM_PRO_ELF_NLA0EN		a0_enable			:1;		/**< Reference to the noise component Ns9s17<br>
															target registor	:@@NLA0EN */
	USHORT	dummy02								:4;		/**< Not used									*/

	E_IM_PRO_ELF_F5_MD		f5_filter_mode		:1;		/**< F5 Filter mode<br>
															target registor	:@@F5MD */
	E_IM_PRO_ELF_F9_MD		f9_filter_mode		:1;		/**< F9 Filter mode<br>
															target registor	:@@F9MD */
	USHORT	dummy03								:12;		/**< Not used									*/

	E_IM_PRO_ELF_EFMD		e_filter_mode		:1;		/**< E Filter mode<br>
															target registor	:@@EFMD */
	E_IM_PRO_ELF_LFMD		l_filter_mode		:1;		/**< L Filter mode<br>
															target registor	:@@LFMD */
	USHORT	dummy04								:5;		/**< Not used									*/
	USHORT	dummy07								:3;		/**< Not used									*/

} T_IM_PRO_ELF_COMMON1;

typedef struct {
	T_IM_PRO_ELF_COMMON1		cmn1;		/**< ELF Filter control common part 1	*/
	T_IM_PRO_ELF_COMMON2		cmn2;		/**< ELF Filter control common part 2	*/
} T_IM_PRO_ELF_CTRL;

struct _ImPro1 {
	KObject parent;
};

typedef struct {
	USHORT	g_width;		/**< global horizontal size<br>
								value range		:[10 - 2496] 2byte boundary<br>
								target registor	:@@ELFGHW	*/
	USHORT	g_lines;		/**< global vertical size<br>
								value range		:[10 - 8960] 2pixel boundary<br>
								target registor	:@@ELFGVW	*/
	USHORT	g_pos_x;		/**< global Compensation horizontal direction start position<br>
								value range		:[0 - 2496]<br>
								target registor	:@@ELFGH	*/
	USHORT	g_pos_y;		/**< global Compensation vertical direction start position<br>
								value range		:[0 - 8960] 2pixel boundary<br>
								target registor	:@@ELFGV	*/
	USHORT	width;			/**< horizontal size<br>
								value range		:[2 - 2488] 2byte boundary<br>
								target registor	:@@ELFHW	*/
	USHORT	lines;			/**< vertical size<br>
								value range		:[2 - 8952] 2pixel boundary<br>
								target registor	:@@ELFVW	*/
	USHORT	pos_x;			/**< Compensation horizontal direction start position<br>
								value range		:[4 - 2491]<br>
								target registor	:@@ELFH		*/
	USHORT	pos_y;			/**< Compensation vertical direction start position<br>
								value range		:[4 - 8954] 2pixel boundary<br>
								target registor	:@@ELFV		*/
} T_IM_PRO_ELF_AREA;

typedef struct {
	USHORT	offset[4];		/**< One common brightness threshold ELF<br>
								value range		:[0 - 4095]
								target registor	:@@ANBOR/@@ANBOG/@@ANBOB	*/
	USHORT	gain[4];		/**< noise table gain<br>
								value range		:[0 - 4095((12-bit fractional part))]
								target registor	:@@ANBKR/@@ANBKG/@@ANBKB	*/
	USHORT	boundary[4];	/**< noise boundary<br>
								value range		:[0 - 4095] 16byte boundary
								target registor	:@@ANBDR/@@ANBDG/@@ANBDB	*/
} T_IM_PRO_ELF_NOISE_FUNC;

typedef struct {
	USHORT	zero_point;		/**< Zero point level<br>
								value range		:[0 - 4095] <br>
								target registor	:@@ELFZP	*/
	USHORT	gain_r;			/**< R Gain for brightness<br>
								value range		:[0 - 1023(=3.99609375)] <br>
								target registor	:@@LGTWR	*/
	USHORT	gain_g;			/**< G Gain for brightness<br>
								value range :[0 - 1023(=3.99609375)] <br>
								target registor	:@@LGTWG	*/
	USHORT	gain_b;			/**< B Gain for brightness<br>
								value range		:[0 - 1023(=3.99609375)] <br>
								target registor	:@@LGTWB	*/
	UCHAR	factor_r;		/**< R factor for brightness<br>
								value range		:[0 - 31(=1.9375)] <br>
								target registor	:@@LGTR		*/
	UCHAR	factor_g;		/**< G factor for brightness<br>
								value range		:[0 - 31(=1.9375)] <br>
								target registor	:@@LGTG		*/
	UCHAR	factor_b;		/**< B factor for brightness<br>
								value range		:[0 - 31(=1.9375)] <br>
								target registor	:@@LGTB		*/
	UCHAR	color_para;		/**< Parameters for brightness color difference<br>
								value range		:[0 - 16(=1.0)] <br>
								target registor	:@@LGTC		*/
	UCHAR	contour_r;		/**< R factor for the degree of weight contour<br>
								value range		:[0 - 16(=1.0)] <br>
								target registor	:@@LGTER	*/
	UCHAR	contour_g;		/**< G factor for the degree of weight contour<br>
								value range		:[0 - 16(=1.0)] <br>
								target registor	:@@LGTEG	*/
	UCHAR	contour_b;		/**< B factor for the degree of weight contour<br>
								value range		:[0 - 16(=1.0)] <br>
								target registor	:@@LGTEB	*/
	USHORT	contour_a_1;	/**< A contour-based one time adjustment factor<br>
								value range		:[0 - 255(=3.984375)] <br>
								target registor	:@@EDG2ANBA	*/
	USHORT	contour_a_2;	/**< A contour-based two time adjustment factor<br>
								value range		:[0 - 1023] <br>
								target registor	:@@EDGSCLA	*/
	USHORT	contour_b_1;	/**< B contour-based one time adjustment factor<br>
								value range		:[0 - 1023(=15.984375)] <br>
								target registor	:@@EDG2ANBB	*/
	USHORT	contour_b_2;	/**< B contour-based two time adjustment factor<br>
								value range		:[0 - 1023] <br>
								target registor	:@@EDGSCLB	*/
	USHORT	contour_c_1;	/**< C contour-based one time adjustment factor<br>
								value range		:[0 - 1023(=15.984375)] <br>
								target registor	:@@EDG2ANBC	*/
	USHORT	contour_c_2;	/**< C contour-based two time adjustment factor<br>
								value range		:[0 - 1023] <br>
								target registor	:@@EDGSCLC	*/
} T_IM_PRO_ELF_LGT_EDG_FUNC;

typedef struct {
	USHORT	e_threshold_1;		/**< E threshold filter (L1 brightness)<br>
									value range		:[0 - 1023] <br>
									target registor	:@@EFL1TH	*/
	USHORT	e_threshold_2;		/**< E threshold filter (L2 brightness)<br>
									value range		:[0 - 1023] <br>
									target registor	:@@EFL2TH	*/
	USHORT	e_threshold_3;		/**< E threshold filter (L3 brightness)<br>
									value range		:[0 - 1023] <br>
									target registor	:@@EFL3TH	*/
	USHORT	e_threshold_4;		/**< E threshold filter (L4 brightness)<br>
									value range		:[0 - 1023] <br>
									target registor	:@@EFL4TH	*/
	SHORT	l_threshold;		/**< L threshold filter<br>
									value range		:[-1024 - +1023] <br>
									target registor	:@@LFTH		*/
	USHORT	l_contour_1;		/**< Applicable threshold contour L 1 degree<br>
									value range		:[0 - 4095] ELCOME1<=ELCOME2<br>
									target registor	:@@ELCOME1	*/
	USHORT	l_contour_2;		/**< Applicable threshold contour L 2 degree<br>
									value range		:[0 - 4095] <br>
									target registor	:@@ELCOME2	*/
	USHORT	l_cintensity_1;		/**< Applied intensity L (E1 degree contour)<br>
									value range		:[0 - 256(=1.0)] <br>
									target registor	:@@ELCOME1N	*/
	USHORT	l_cintensity_2;		/**< Applied intensity L (E2 degree contour)<br>
									value range		:[0 - 256(=1.0)] <br>
									target registor	:@@ELCOME2N	*/
} T_IM_PRO_ELF_L_E_FUNC;

typedef struct {
	USHORT	strength;								/**< F9 filter NR strength.<br>
														value range		:[0(=0.0) - 256(=1.0)]<br>
														target registor	:@@FASTR	*/
	CHAR	e_focus_coord[4];						/**< F9 filter coordinates (Cb,Cr) of the F9 filter elliptic focus 1 and 2.<br>
														value range		:[-128 - 127]<br>
														target registor	:@@CRVAFX1/@@CRVAFY1/@@CRVAFX2/@@CRVAFY2	*/
	USHORT	e_polygonal_line_offset1;				/**< F9 filter polygonal line offset 1of the F9 filter beta value color difference elliptic reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FCRVABTOF1	*/
	USHORT	e_polygonal_line_minus_inclination[2];	/**< F9 filter polygonal line minus inclination 0 and 1 of the F9 filter β value color difference elliptic reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FCRVABTGA0/@@FCRVABTGA1	*/
	UCHAR	e_polygonal_line_boundary1;				/**< F9 filter polygonal line boundary 1 of the F9 filter beta value color difference elliptic reference.<br>
														value range		:[0 - 127]<br>
														target registor	:@@FCRVABTBD1	*/
	USHORT	e_upper_clip;							/**< F9 filter upper clip value of the F9 filter beta value color difference elliptic reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FCRVABTCPH	*/
	USHORT	e_lower_clip;							/**< F9 filter lower clip value of the F9 filter beta value color difference elliptic reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FCRVABTCPL	*/
	UCHAR	l_polygonal_line_plus_inclination0;		/**< F9 filter polygonal line plus inclination0 of the F9 filter beta value luminance reference.<br>
														value range		:[0 - 255]<br>
														target registor	:@@FYABTGA0	*/
	UCHAR	l_polygonal_line_minus_inclination1;	/**< F9 filter polygonal line minus inclination1 of the F9 filter beta value luminance reference.<br>
														value range		:[0 - 255]<br>
														target registor	:@@FYABTGA1	*/
	USHORT	l_polygonal_line_boundary[2];			/**< F9 filter polygonal line boundary 0 and 1 of the F9 filter beta value luminance reference.<br>
														value range		:[0 - 4095]<br>
														target registor	:@@FYABTBD0/@@FYABTBD1	*/
	USHORT	l_upper_clip;							/**< F9 filter upper clip value of the F9 filter beta value color difference luminance reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FYABTCLPH	*/
	USHORT	l_lower_clip;							/**< F9 filter lower clip value of the F9 filter beta value color difference luminance reference.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FYABTCLPL	*/
	UCHAR	t_f_profile_transition;					/**< F9 filter working method (transition method) of the threshold of the profile tolerance F.<br>
														value range		:[0 - 15]<br>
														target registor	:@@FAECHH	*/
	USHORT	t_f_profile_threshold;					/**< F9 filter threshold of the profile tolerance F.<br>
														value range		:[0 - 511]<br>
														target registor	:@@FAETHH	*/
} T_IM_PRO_ELF_f9_FILTER;

typedef struct {
	USHORT gain[3];									/**< Gain coefficient of each pixel(R/G/B) for F9 NR.<br>
													    value range		:[0 - 1023]<br>
														target registor	:@@FS9WR/@@FS9WG/@@FS9WB	*/
} T_IM_PRO_ELF_f9_RGB_GAIN;

typedef struct {
	T_IM_PRO_ELF_f9_RGB_GAIN	rgb_gain;				/**< Gain coefficient of each pixel(R/G/B) for F9 NR.<br> */
	SHORT						yc_conv_matrix[9];		/**<  YC conversion matrix coefficient for F9 NR.<br>
															value range		:[-256 - 255]<br>
															target registor	:@@FS9YC	*/
	T_IM_PRO_ELF_f9_FILTER		f9a_group;				/**< F9 filter information of F9-A group.	*/
	T_IM_PRO_ELF_f9_FILTER		f9b_group;				/**< F9 filter information of F9-B group.	*/
} T_IM_PRO_ELF_f9_SAMPLING;

typedef struct {
	USHORT	s1s5_threshold[3];			/**< 1-5 degree threshold contour 1-3<br>
											value range		:[0 - 4095] A1S5E1<=A1S5E2<=A1S5E3<br>
											target registor	:@@A1S5E1/@@A1S5E2/@@A1S5E3	*/
	USHORT	s1s5_nr_l1_E13[3];			/**< 1-5 NR Intensity  (L1 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A1S5L1E1N/@@A1S5L1E2N/@@A1S5L1E3N	*/
	USHORT	s1s5_nr_l2_E13[3];			/**< 1-5 NR Intensity  (L2 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A1S5L2E1N/@@A1S5L2E2N/@@A1S5L2E3N	*/
	USHORT	s1s5_nr_l3_E13[3];			/**< 1-5 NR Intensity  (L3 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A1S5L3E1N/@@A1S5L3E2N/@@A1S5L3E3N	*/
	USHORT	s1s5_nr_l4_E13[3];			/**< 1-5 NR Intensity  (L4 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A1S5L4E1N/@@A1S5L4E2N/@@A1S5L4E3N	*/
	USHORT	s1s5_nr_adjustment[3];		/**< 1-5 NR (R/G/B) component intensity adjustment<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@NR1S5R/@@NR1S5G/@@NR1S5B	*/
	USHORT	s1s5_noise_limit_plus;		/**< 1-5 Noise limit (The positive side)<br>
											value range		:[0 - 4095] <br>
											target registor	:@@NS1S5LMP	*/
	USHORT	s1s5_noise_limit_minus;		/**< 1-5 Noise limit (The minus side)<br>
											value range		:[0 - 4095] <br>
											target registor	:@@NS1S5LMM	*/
} T_IM_PRO_ELF_1s5_SAMPLING;

typedef struct {
	USHORT	s5s9_threshold[3];			/**< 1-5 degree threshold contour 1-3<br>
											value range		:[0 - 4095] A5s9E1<=A5s9E2<=A5s9E3<br>
											target registor	:@@A5S9E1/@@A5S9E2/@@A5S9E3	*/
	USHORT	s5s9_nr_l1_E13[3];			/**< 1-5 NR Intensity  (L1 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A5S9L1E1N/@@A5S9L1E2N/@@A5S9L1E3N	*/
	USHORT	s5s9_nr_l2_E13[3];			/**< 1-5 NR Intensity  (L2 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A5S9L2E1N/@@A5S9L2E2N/@@A5S9L2E3N	*/
	USHORT	s5s9_nr_l3_E13[3];			/**< 1-5 NR Intensity  (L3 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A5S9L3E1N/@@A5S9L3E2N/@@A5S9L3E3N	*/
	USHORT	s5s9_nr_l4_E13[3];			/**< 1-5 NR Intensity  (L4 brightness, E1-3 degree contour)<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@A5S9L4E1N/@@A5S9L4E2N/@@A5S9L4E3N	*/
	USHORT	s5s9_nr_adjustment[3];		/**< 1-5 NR (R/G/B) component intensity adjustment<br>
											value range		:[0 - 256(=1.0)] <br>
											target registor	:@@NR5S9R/@@NR5S9G/@@NR5S9B	*/
	USHORT	s5s9_noise_limit_plus;		/**< 1-5 Noise limit (The positive side)<br>
											value range		:[0 - 4095] <br>
											target registor	:@@NS5S9LMP	*/
	USHORT	s5s9_noise_limit_minus;		/**< 1-5 Noise limit (The minus side)<br>
											value range		:[0 - 4095] <br>
											target registor	:@@NS5S9LMM	*/
} T_IM_PRO_ELF_5s9_SAMPLING;

typedef struct {
	USHORT	nr_strength_l1[3];			/**< (R/G/B) component strength NR main line path (L1 brightness)<br>
											value range		:[0 - 255(=1.0)] <br>
											target registor	:@@ELFMNNRRL1/@@ELFMNNRGL1/@@ELFMNNRBL1	*/
	USHORT	nr_strength_l2[3];			/**< (R/G/B) component strength NR main line path (L2 brightness)<br>
											value range		:[0 - 255(=1.0)] <br>
											target registor	:@@ELFMNNRRL2/@@ELFMNNRGL2/@@ELFMNNRBL2	*/
	USHORT	nr_strength_l3[3];			/**< (R/G/B) component strength NR main line path (L3 brightness)<br>
											value range		:[0 - 255(=1.0)] <br>
											target registor	:@@ELFMNNRRL3/@@ELFMNNRGL3/@@ELFMNNRBL3	*/
	USHORT	nr_strength_l4[3];			/**< (R/G/B) component strength NR main line path (L4 brightness)<br>
											value range		:[0 - 255(=1.0)] <br>
											target registor	:@@ELFMNNRRL4/@@ELFMNNRGL4/@@ELFMNNRBL4	*/
	USHORT	af_path_nr_strength;		/**< AF Path NR strength<br>
											value range		:[0 - 255(=1.0)] <br>
											target registor	:@@ELFAFNR	*/
} T_IM_PRO_ELF_Noise_Adj;

typedef struct {
	USHORT	coeff1;						/**< profile tolerance adjustment coefficient1 of A0 function.<br>
											value range		:[0 - 1023] <br>
											target registor	:@@ZEDG2ANBA	*/
	USHORT	coeff2;						/**< profile tolerance adjustment coefficient2 of A0 function.<br>
											value range		:[0 - 1023] <br>
											target registor	:@@ZEDGSCLA	*/
} T_IM_PRO_ELF_a0_TOLERANCE_ADJ;

typedef enum {
	E_IM_PRO_ELF_A0_DPC_MODE_DISABLE = 0,		/**< No defect correction.	*/
	E_IM_PRO_ELF_A0_DPC_MODE_ENABLE_LOW,		/**< Tolerance to defects is supported and relatively low.<br>
														There is no problem with single defect.	*/
	E_IM_PRO_ELF_A0_DPC_MODE_ENABLE_HIGH = 3,	/**< Tolerance to defects is supported and relatively high.	*/
} E_IM_PRO_ELF_A0_DPC_MODE;

typedef struct {
	USHORT	offset[4];					/**< offset value of the noise characteristic enumeration function for the area 0-3 of A0 function.<br>
											value range		:[0 - 4095] <br>
											target registor	:@@ZANBOR/@@ZANBOG/@@ZANBOB	*/
	USHORT	gain[4];					/**< gain value of the noise characteristic enumeration function for the area 0-3 of A0 function.<br>
											value range		:[0 - 4095] <br>
											target registor	:@@ZANBKR/@@ZANBKG/@@ZANBKB	*/
	USHORT	area_boundary[4];			/**< area  boundary value of the noise characteristic enumeration function of A0 function in units of 16.<br>
											value range		:[0 - 4095] <br>
											target registor	:@@ZANBDR/@@ZANBDG/@@ZANBDB<br>
											Make sure to set this register to maintain the following relationship.<br>
											ZANBDB[0]<=ZANBDB[1]<=ZANBDB[2]<=ZANBDB[3]	*/
} T_IM_PRO_ELF_a0_NC;

typedef struct {
	E_IM_PRO_ELF_A0_DPC_MODE		dpc_mode;								/**< defective pixel correction mode in A0 function.<br>
																				target registor	:@@ZELADCMD	*/
	T_IM_PRO_ELF_a0_NC				nce[3];									/**< Noise Characteristic Enumeration parameters.	*/
	USHORT							lumi_rgb_gain[3];							/**< gain value for luminance for each pixel (R/G/B) of A0 function.<br>
																				value range		:[0 - 1023]<br>
																				target registor	:@@ZLGTWR/@@ZLGTWG/@@ZLGTWB	*/
	USHORT							lumi_rgb_coeff[3];						/**< coefficient for luminance for each pixel (R/G/B) of A0 function.<br>
																				value range		:[0 - 31(=1.0)]<br>
																				target registor	:@@ZLGTR/@@ZLGTG/@@ZLGTB	*/
	USHORT							lumi_c_coeff;							/**< difference parameter for luminance for each pixel (R/G/B) of A0 function.<br>
																				value range		:[0 - 31(=1.0)]<br>
																				target registor	:@@ZLGTC	*/
	UCHAR							t_weight[3];							/**< weight coefficient for profile tolerance for each pixel (R/G/B) of A0 function.<br>
																				value range		:[0 - 31(=1.0)]<br>
																				target registor	:@@ZLGTER/@@ZLGTEG/@@ZLGTEB	*/
	T_IM_PRO_ELF_a0_TOLERANCE_ADJ	t_adj_a;								/**< tolerance adjustment parameter of A-system.	*/
	T_IM_PRO_ELF_a0_TOLERANCE_ADJ	t_adj_b;								/**< tolerance adjustment parameter of B-system.	*/
	USHORT							t_long_wavelength_threshold[3];			/**< long wavelength profile tolerance threshold 1-3 of A0 function.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@ZALNGE1/@@ZALNGE2/@@ZALNGE3<br>
																				Make sure to set these bits to maintain the following relationship.<br>
																				ZALNGE1<=ZALNGE2<=ZALNGE3	*/
	USHORT							t_long_wavelength_nr_strength[4][3];	/**< long wavelength NR strength respectively in the luminance Lx and profile tolerance Ey (x=1,2,3,4; y=1,2,3) of A0 function.<br>
																				value range		:[0 - 511]<br>
																				target registor	:<br>
																									@@ZALNGL1E1N/@@ZALNGL1E2N/@@ZALNGL1E3N<br>
																									@@ZALNGL2E1N/@@ZALNGL2E2N/@@ZALNGL2E3N<br>
																									@@ZALNGL3E1N/@@ZALNGL3E2N/@@ZALNGL3E3N<br>
																									@@ZALNGL4E1N/@@ZALNGL4E2N/@@ZALNGL4E3N	*/
	USHORT							l_filter_extraction_threshold;			/**< L filter extraction threshold of A0 function.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@ZLFTH	*/
	USHORT							l_app_tolerance_threshold[2];			/**< L application profile tolerance threshold 1 and 2 of A0 function.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@ZLCOME1/@@ZLCOME2	*/
	USHORT							l_app_strength[2];						/**< L application strength 1 and 2 of A0 function.<br>
																				value range		:[0 - 4095(=1.0)]<br>
																				target registor	:@@ZLCOME1N/@@ZLCOME2N	*/
	USHORT							long_wavelength_noise_p_limiter;		/**< plus side clip value for the extraction noise data of A0 function.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@ZNSLNGLMP	*/
	USHORT							long_wavelength_noise_m_limiter;		/**< minus side clip value for the extraction noise data of A0 function.<br>
																				value range		:[0 - 4095]<br>
																				target registor	:@@ZNSLNGLMM	*/
} T_IM_PRO_ELF_a0_FILTER;

KConstType 		    	im_pro1_get_type(void);
ImPro1*		            	im_pro1_new(void);

extern	VOID im_pro_b2btop_init( E_IM_PRO_UNIT_NUM unit_no );
extern	INT32 im_pro_b2btop_sw_reset( E_IM_PRO_UNIT_NUM unit_no );
extern	INT32 im_pro_b2btop_control_clock( E_IM_PRO_UNIT_NUM unit_no, E_IM_PRO_B2BTOP_CLK_TYPE clk_type, UCHAR on_off, UCHAR wait_skip );
extern	INT32 im_pro_b2btop_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_B2BTOP_CTRL* ctrl );
extern	INT32 im_pro_elf_start( E_IM_PRO_UNIT_NUM unit_no );
extern	VOID im_pro_elf_stop( E_IM_PRO_UNIT_NUM unit_no, UCHAR force );
extern	INT32 im_pro_elf_set_paen( E_IM_PRO_UNIT_NUM unit_no, UCHAR paen_trg );
extern	INT32 im_pro_elf_ctrl_common( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_COMMON_CTRL* elf_common_ctrl );
extern	INT32 im_pro_elf_ctrl( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_CTRL* elf_ctrl );
extern	INT32 im_pro_elf_set_area( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_AREA* elf_area );
extern	INT32 im_pro_elf_set_noisefunc( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_NOISE_FUNC* nfunc );
extern	INT32 im_pro_elf_set_lgt_edg_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_LGT_EDG_FUNC* lgt_filter );
extern	INT32 im_pro_elf_set_e_l_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_L_E_FUNC* e_l_filter );
extern	INT32 im_pro_elf_set_f9_filter( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_f9_SAMPLING* f9_filter );
extern 	INT32 im_pro_elf_set_f9_rgbgain( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_f9_RGB_GAIN* rgb_gain );
extern	INT32 im_pro_elf_set_1s5_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_1s5_SAMPLING* s1s5_sampling );
extern	INT32 im_pro_elf_set_5s9_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_5s9_SAMPLING* s5s9_sampling );
extern	INT32 im_pro_elf_set_noise_adj( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_Noise_Adj* noise_adj_filter );
extern	INT32 im_pro_elf_set_a0_sampling( E_IM_PRO_UNIT_NUM unit_no, T_IM_PRO_ELF_a0_FILTER* a0_filter );
extern	INT32 im_pro_elf_start_nsl( E_IM_PRO_UNIT_NUM unit_no );
extern	VOID im_pro_elf_stop_nsl( E_IM_PRO_UNIT_NUM unit_no, UCHAR force );

#endif /* __IM_PRO1_H__ */
