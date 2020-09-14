/*
 *
*@Copyright(C) 2010-2015 上海网用软件有限公司
*@date:						2020-09-07
*@author:					xutingjun
*@brief:
*@function:
*设计的主要功能:
*@version:					1.0.0
*
*/


#ifndef __IM_FPT_H__
#define __IM_FPT_H__


#include <stdio.h>
#include <glib-object.h>
#include "imfptcommon.h"


G_BEGIN_DECLS


/*----------------------------------------------------------------------	*/
/* Function  																	*/
/*----------------------------------------------------------------------	*/
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


#ifdef CO_DDIM_UTILITY_USE
//---------------------------- utility section ---------------------------
// Nothing Special
//---------------------------- colabo section ----------------------------
// Nothing Special
#endif



#define IM_TYPE_FPT			(im_fpt_get_type ())
#define IM_FPT(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), IM_TYPE_FPT, ImFpt))
#define IM_FPT_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), IM_TYPE_FPT, ImFptClass))
#define IM_IS_FPT(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), IM_TYPE_FPT))
#define IM_IS_FPT_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), IM_TYPE_FPT))
#define IM_FPT_GET_CLASS(obj)		(G_TYPE_INSTANCE_GET_CLASS ((obj), IM_TYPE_FPT, ImFptClass))


typedef struct _ImFpt			ImFpt;
typedef struct _ImFptClass		ImFptClass;
typedef struct _ImFptPrivate 		ImFptPrivate;


struct _ImFpt
{
	GObject parent;
	IoFptFptaxictl0 fptaxictl0;
	DdimUserCustomTest *ddimUserCustomTest;
	IoFptFptctl2 fptctl2;
};

struct _ImFptClass
{
	GObjectClass parentClass;
};


GType						im_fpt_get_type(void)	G_GNUC_CONST;
ImFpt*					im_fpt_new(void);
void 						im_fpt_on_hclk(ImFpt*self, guchar ch);
void 						im_fpt_off_hclk(ImFpt*self, guchar ch);
void 						im_fpt_on_iclk(ImFpt*self, guchar ch);
void	 					im_fpt_off_iclk(ImFpt*self, guchar ch);
void 						im_fpt_on_pclk(ImFpt*self, guchar ch);
void 						im_fpt_off_pclk(ImFpt*self, guchar ch);
extern void 			im_fptasm_wait_cpucyc(gulong count);
/**
 Initialize driver.<br>

 @param[in]	ch :Channel number(0/1)
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 @retval		ImFptCommon_D_IM_FPT_RETVAL_ERR @ref ImFptCommon_D_IM_FPT_RETVAL_ERR(FPT is running.)
 @remarks	It should be called at first.
 @remarks	It should be called when FPT is not running.
 */
extern gint32 			im_fpt_im_fpt_init(ImFpt*self, guchar ch);

/**
 Open driver.<br>
 Exclusive access control API.<br>

 @param[in]	ch :Channel number(0/1)
 @param[in]	waitTime : Wait time [msec]. The valid range is -1, 0, ... .
 If this parameter is set to -1,
 API waits permanently unless system-call gets FPT semaphore.
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 @retval		ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR
 @remarks	This API uses DDIM_User_Pol_Sem() when waitTime is set to 0. <br>
 This API uses DDIM_User_Twai_Sem() when waitTime is set to the value except for 0.
 */
extern gint32 			im_fpt_open(ImFpt*self, guchar ch, gint32 waitTime);

/**
 Close driver.<br>
 Exclusive access control API.<br>

 @param[in]	ch :Channel number(0/1)
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_SYSTEM_CALL_ERR
 @retval		ImFptCommon_D_IM_FPT_RETVAL_ERR : @ref ImFptCommon_D_IM_FPT_RETVAL_ERR(FPT is running.)
 @remarks	It should be called when FPT is not running.
 @remarks	This API uses DDIM_User_Sig_Sem().
 */
extern gint32 im_fpt_close(ImFpt*self, guchar ch);

/**
 Configure the mode, "Calculate Feature Amount".<br>
 Please refer to @ref fpt_mode0.

 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptMode0.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern gint32 im_fpt_ctrl_mode0(ImFpt*self, guchar ch, const TfptMode0* const param);

/**
 Configure the mode, "Re-calculate Feature Amount".<br>
 Please refer to @ref fpt_mode1.

 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptMode1.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern gint32 im_fpt_ctrl_mode1(ImFpt*self, guchar ch, const TfptMode1* const param);

/**
 Configure the mode, "Feature point Tracking".<br>
 Please refer to @ref fpt_mode2.

 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptMode2.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern gint32 im_fpt_ctrl_mode2(ImFpt*self, guchar ch, const TfptMode2* const param);

/**
 Configure the mode, "Re-calculate Feature Amount and Feature point Tracking".<br>
 Please refer to @ref fpt_mode3.

 @param[in]	ch :Channel number(0/1)
 @param[in]	param : parameter. Please refer to @ref TfptMode3.<br>
 @retval		ImFptCommon_D_IM_FPT_RETVAL_OK : @ref ImFptCommon_D_IM_FPT_RETVAL_OK
 @retval		ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR	: @ref ImFptCommon_D_IM_FPT_RETVAL_INVALID_ARG_ERR
 */
extern gint32 im_fpt_ctrl_mode3(ImFpt*self, guchar ch, const TfptMode3* const param);


//---------------------------- utility section ---------------------------

//---------------------------- colabo section ----------------------------
// Nothing Special

/** @} */	// end of fpt_drv

/**
 @weakgroup fpt_usage Usage
 @{

 @section fpt_sample_seq Sequence Charts
 - @ref FPT_INIT
 - @ref FPT_EXE
 - @ref FPT_STOP

 <hr>
 @section FPT_INIT	1. Initialization
 @image html fpt_init.png
 <hr>

 @section FPT_EXE		2. Execution
 @image html fpt_mode.png
 @code

 #include "fpt.h"
 #define round_up( val, al )	((val+(al-1)) &(~(al-1)) )	// "al" is power of 2.

 void FPT_Sample( gint32 mode, const guchar* lut0, const guchar* lut1 )
	{
		TfptMode0 m0_param;
		TfptMode1 m1_param;
		TfptMode2 m2_param;
		TfptMode3 m3_param;
		TfptInterrupt int_param;
		guint32 status;
		gint offset;

		im_fpt_open( 0, 0 );

		switch( mode ) {
			case 0:
			m0_param.globalWidth = 1568;
			m0_param.width = 1568;
			m0_param.lines = 1050;
			m0_param.lutsel =( lut0 != NULL ) ? ImFptCommon_E_IM_FPT_LUTSEL_0 : ImFptCommon_E_IM_FPT_LUTSEL_OFF:
			m0_param.windowSize = D_IM_FPT_WINDOW_7x7;
			m0_param.downSampleX = ImFptCommon_D_IM_FPT_DS_MAX;
			m0_param.downSampleY = ImFptCommon_D_IM_FPT_DS_MAX;
			m0_param.imgAddr = 0x43000000;
			m0_param.featureAmountAddr = 0x43800000;
			offset =( m0_param.windowSize == ImFptCommon_D_IM_FPT_WINDOW_5x5 ) ? 12 : 14;
			m0_param.featureAmountLineByte = round_up((((1568/7) - offset) * 2), 8 );
			m0_param.histgramAddr = 0x44000000;

			im_fpt_ctrl_mode0( 0, &m0_param );
			break;
			case 1:
			m1_param.numFeaturePoint = 100;
			m1_param.output = ImFptCommon_D_IM_FPT_OUT_COORD_AND_FEATURE_AMOUNT;
			m1_param.globalWidth = 896;
			m1_param.width = 128;
			m1_param.lines = 128;
			m1_param.lutsel =( lut0 != NULL ) ? ImFptCommon_E_IM_FPT_LUTSEL_0 : ImFptCommon_E_IM_FPT_LUTSEL_OFF:
			m1_param.windowSize = D_IM_FPT_WINDOW_7x7;
			m1_param.downSampleX = 0x0400;
			m1_param.downSampleY = 0x0400;
			m1_param.imgAddr = 0x43000000;
			m1_param.inputCoordAddr = 0x43800000;
			m1_param.outputAddr = 0x44000000;

			im_fpt_ctrl_mode1( 0, &m1_param );
			break;
			case 2:
			m2_param.baseGlobalWidth = 896;
			m2_param.targetGlobalWidth = 896;
			m2_param.numFeaturePoint = 100;
			m2_param.usageTargetCoord = ImFptCommon_D_IM_FPT_READ_FROM_RAM;
			m2_param.downSampleX = 0x0400;
			m2_param.downSampleY = 0x0400;
			m2_param.lutcfg =((lut0 != NULL) &&((lut1 != NULL)) ) ? ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1 :
			( lut0 != NULL ) ? ImFptCommon_E_IM_FPT_LUTCFG_BASE_0 :
			( lut1 != NULL ) ? ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1 :
			ImFptCommon_E_IM_FPT_LUTCFG_OFF;
			m2_param.searchWindow.left = 0x700;	// 7.0
			m2_param.searchWindow.right = 0x700;// 7.0
			m2_param.searchWindow.top = 0x700;// 7.0
			m2_param.searchWindow.bottom = 0x700;// 7.0
			m2_param.trackingThreshold = 0x33;// 0.2
			m2_param.numIteration = 10;
			m2_param.baseImgAddr = 0x43000000;
			m2_param.targetImgAddr = 0x43800000;
			m2_param.baseCoordAddr = 0x44000000;
			m2_param.targetCoordAddr = 0x44800000;
			m2_param.trackingResultAddr = 0x45000000;

			im_fpt_ctrl_mode2( 0, &m2_param );
			break;
			case 3:
			m3_param.width = 128;
			m3_param.lines = 128;
			m3_param.windowSize = D_IM_FPT_WINDOW_7x7;
			m3_param.outputAddr = 0x46000000;
			m3_param.baseGlobalWidth = 896;
			m3_param.targetGlobalWidth = 896;
			m3_param.numFeaturePoint = 100;
			m3_param.usageTargetCoord = ImFptCommon_D_IM_FPT_READ_FROM_RAM;
			m3_param.downSampleX = 0x0400;
			m3_param.downSampleY = 0x0400;
			m3_param.lutcfg =((lut0 != NULL) &&((lut1 != NULL)) ) ? ImFptCommon_E_IM_FPT_LUTCFG_BASE_0__TARGET_1 :
			( lut0 != NULL ) ? ImFptCommon_E_IM_FPT_LUTCFG_BASE_0 :
			( lut1 != NULL ) ? ImFptCommon_E_IM_FPT_LUTCFG_TARGET_1 :
			ImFptCommon_E_IM_FPT_LUTCFG_OFF;
			m3_param.searchWindow.left = 0x700;// 7.0
			m3_param.searchWindow.right = 0x700;// 7.0
			m3_param.searchWindow.top = 0x700;// 7.0
			m3_param.searchWindow.bottom = 0x700;// 7.0
			m3_param.trackingThreshold = 0x33;// 0.2
			m3_param.numIteration = 10;
			m3_param.baseImgAddr = 0x43000000;
			m3_param.targetImgAddr = 0x43800000;
			m3_param.baseCoordAddr = 0x44000000;
			m3_param.targetCoordAddr = 0x44800000;
			m3_param.trackingResultAddr = 0x45000000;

			im_fpt_ctrl_mode3( 0, &m3_param );
			break;
			default:
			break;
		}

		if( lut0 != NULL ) {
			Im_FPT_Ctrl_LUTRAM( 0, 0, lut0 );
		}

		if( lut1 != NULL ) {
			Im_FPT_Ctrl_LUTRAM( 0, 1, lut1 );
		}

		int_param.flag =( ImFptCommon_D_IM_FPT_INTERRUPT_COMPLETE | ImFptCommon_D_IM_FPT_INTERRUPT_AXI_ERR | ImFptCommon_D_IM_FPT_INTERRUPT_PARAM_ERR );
		int_param.callback = NULL;	// If needs callback, please set the address of callback function.
		Im_FPT_Ctrl_Interrupt( 0, &int_param );

		Im_FPT_Start( 0 );

		Im_FPT_WaitEnd( 0, &status, 5000 );

		im_fpt_close( 0 );
	}
 @endcode

 <hr>

 @section FPT_STOP	3. Force Stop
 @image html fpt_stop.png

 <hr>
 */
/** @} */	// end of fpt_usage
/**
 @weakgroup fpt_overview Overview
 @{

 FPT has the following 3 function:

 - @ref fpt_mode0
 - @ref fpt_mode1
 - @ref fpt_mode2
 - @ref fpt_mode3

 For more information, please refer to FPT HW specification.

 <hr>

 @section fpt_mode0	Mode0(Calculate Feature Amount)
 Following figure shows input/output data in mode0.<br>
 In the figure, TfptMode0::xxx is the parameter of im_fpt_ctrl_mode0().<br>
 FPT outputs "Feature Amount" and "Histgram" using "Input image".<br>
 @image html fpt_func_mode0.png
 The data format of 1 component is the followings:<br>
 - [IN]Input image: U8(unsigned, 8 bits)
 <br>
 - [OUT]Feature Amount: S16(signed, 16 bits)
 <br>
 - [OUT]Histgram: U16(unsigned, 16 bits)
 <br>

 <hr>

 @section fpt_mode1	Mode1(Re-calculate Feature Amount)
 Following figure shows input/output data in mode1.<br>
 In the figure, TfptMode1::xxx is the parameter of im_fpt_ctrl_mode1().<br>
 FPT reads "Input image" and "Input coord data".<br>
 And output data depends on TfptMode1::output setting.<br>
 When TfptMode1::output is set to @ref ImFptCommon_D_IM_FPT_OUT_COORD_ONLY(0), it contains feature point coord data only.<br>
 When TfptMode1::output is set to @ref ImFptCommon_D_IM_FPT_OUT_COORD_AND_FEATURE_AMOUNT(1), it contains feature point coord also feature amount data.<br>
 @image html fpt_func_mode1.png
 The data format of 1 component is the followings:<br>
 - [IN]Input image: U8(unsigned, 8 bits)
 <br>
 - [IN]Input coord data: U15+U15, please refer to following table.
 <table>
 <tr>
 <th>bit31</th>
 <th>bit[30:16]</th>
 <th>bit15</th>
 <th>bit[14:0]</th>
 </tr>
 <tr>
 <td>unused [0]</td>
 <td>vertical coord, U15</td>
 <td>unused [0]</td>
 <td>horizontal coord, U15</td>
 </tr>
 </table>
 <br>
 - [OUT]Only Feature point coord data: U15+U15, please refer to following table.
 <table>
 <tr>
 <th>bit31</th>
 <th>bit[30:16]</th>
 <th>bit15</th>
 <th>bit[14:0]</th>
 </tr>
 <tr>
 <td>unused [0]</td>
 <td>vertical coord, U15</td>
 <td>unused [0]</td>
 <td>horizontal coord, U15</td>
 </tr>
 </table>
 <br>
 - [OUT]Feature Amount + Feature point coord data: S16+U15+U15, please refer to following table.
 <table>
 <tr>
 <th>bit[63:48]</th>
 <th>bit[47:32]</th>
 <th>bit31</th>
 <th>bit[30:16]</th>
 <th>bit15</th>
 <th>bit[14:0]</th>
 </tr>
 <tr>
 <td>unused [0]</td>
 <td>feature amount, S16</td>
 <td>unused [0]</td>
 <td>vertical coord, U15</td>
 <td>unused [0]</td>
 <td>horizontal coord, U15</td>
 </tr>
 </table>
 <br>
 Please note that horizontal/vertical coord data U15 is integer only.<br>

 <hr>

 @section fpt_mode2	Mode2(Feature point Tracking)
 Following figure shows input/output data in mode2.<br>
 In the figure, TfptMode2::xxx is the parameter of im_fpt_ctrl_mode2().<br>
 In this mode, FPT tracks feature point using base and target image.<br>
 When TfptMode2::usageTargetCoord is set to @ref ImFptCommon_D_IM_FPT_READ_FROM_RAM(0), FPT reads target's feature point coord data.<br>
 Output contains tracking result.<br>
 @image html fpt_func_mode2.png
 The data format of 1 component is the followings:<br>
 - [IN]Target/Base image: U8(unsigned, 8 bits)
 <br>
 - [IN]Target/Base coord data: U15+U15, please refer to following table.
 <table>
 <tr>
 <th>bit31</th>
 <th>bit[30:16]</th>
 <th>bit15</th>
 <th>bit[14:0]</th>
 </tr>
 <tr>
 <td>unused [0]</td>
 <td>vertical coord, U15</td>
 <td>unused [0]</td>
 <td>horizontal coord, U15</td>
 </tr>
 </table>
 Please note that horizontal/vertical coord data U15 is integer only.<br>
 <br>
 - [OUT]Tracking result: S13+U2+S13, please refer to following table.
 <table>
 <tr>
 <th>bit[31:29]</th>
 <th>bit[28:16]</th>
 <th>bit15</th>
 <th>bit[14:13]</th>
 <th>bit[12:0]</th>
 </tr>
 <tr>
 <td>unused [0]</td>
 <td>vertical vector, S13[*1]</td>
 <td>unused [0]</td>
 <td>tracking status, U2[*2]</td>
 <td>horizontal vector, S13 [*1]</td>
 </tr>
 </table>
 [*1]: signed 13bits. 5.8 fixed point value. MSB(bit12) means sign bit. <br>
 [*2]: unsigned 2 bits.
 <ul>
 <li>0: Tracking success.<br>
 <li>1: Outside the range of tracking.<br>
 <li>2: Exceed the maximum number of iteration.<br>
 <li>3: Outside the range of tracking & Exceed the maximum number of iteration<br>
 </ul>
 <br>

 @section fpt_mode3	Mode3(Re-calculate Feature Amount & Feature point Tracking)
 In this mode, Automatically and continuously and run the Mode1 and Mode2.<br>
 <br>

 <hr>
 */
/** @} */	// end of fpt_overview


#ifdef __cplusplus
}
#endif	// __cplusplus


G_END_DECLS


#endif /* __IM_FPT_H__ */
