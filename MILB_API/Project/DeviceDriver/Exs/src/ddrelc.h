/*
*@Copyright (C) 2010-2020 上海网用软件有限公司
*@date                :2020-09-04
*@author              :徐廷军
*@brief               :sns 索喜rtos
*@redd                :klib
*@function
*sns 索喜rtos，采用ETK-C语言编写
*设计的主要功能:
*1、
*2、
*@version
*1.0.0 2020年09月开始开发
*/

#ifndef __DD_RELC_H__
#define __DD_RELC_H__

#include <klib.h>
#include "driver_common.h"
#include "ddimtypedef.h"
#include "mptk_typedef.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DD_TYPE_RELC			(dd_relc_get_type())
#define DD_RELC(obj)			(K_TYPE_CHECK_INSTANCE_CAST(obj, DdRelc))
#define DD_IS_RELC(obj)		(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_RELC))
/**
@addtogroup dd_relc
@{
@} */

/*----------------------------------------------------------------------*/
/* Overview																	*/
/*----------------------------------------------------------------------*/
/** @weakgroup dd_relc
 @{
 RELC macro decodes the data encoded in encoder RELC.<br>
 There are two patterns how to run in RELC macro.<br>
 And each patterns have how to designate address.<br>

 Normal mode<br>
 Register mode 	: To run only once by designated an input and output address.<br>
 Descriptor mode : To run only once by a descriptor.<br><br>

 Continuous run mode<br>
 Register mode 	: To run continuously by auto-increment input and output address.<br>
 Descriptor mode : To run continuously by a descriptor.

 @} *//* --- end of relc_driver_overview */

/*----------------------------------------------------------------------*/
/* Sequence																	*/
/*----------------------------------------------------------------------*/
/** @weakgroup dd_relc
 @{
 - @ref Init_and_Start_run
 - @ref Proc_result_comp
 - @ref Proc_result_err
 - @ref Proc_result_reach_addr
 <hr>
 @section Init_and_Start_run Initialization and execution start
 @image html 01_RELC_init_start.png
 <br>
 <br>
 @section Proc_result_comp Result determination processing(processing is complete the whole pprocess)
 @image html 02_RELC_judge_result_Finish.png
 <br>
 <br>
 @section Proc_result_err Result determination processing(error is occured)
 @image html 03_RELC_judge_result_Error.png
 <br>
 <br>
 @section Proc_result_reach_addr Result determination processing(when it reaches the specified)
 @image html 04_RELC_judge_result_Reach_address.png

 @} *//* --- end of relc_driver_sequence */

/*----------------------------------------------------------------------	*/
/* Definition																		*/
/*----------------------------------------------------------------------	*/
/** @weakgroup dd_relc
@{*/
/* return value of RELC decoding */
/**< Normal end	*/
#define	DdRelc_D_DD_RELC_OK												(0)
/**< Input Parameter Error	*/
#define DdRelc_D_DD_RELC_PARAM_ERR								(1)
/**< Exclusive control NG */
#define DdRelc_D_DD_RELC_EXT_LOCK_NG							(2)
/**< Wait flag timeout	*/
#define DdRelc_D_DD_RELC_TIMEOUT									(3)
/**< Flag clear NG	*/
#define DdRelc_D_DD_RELC_FLG_CLR_NG								(4)

/* Descriptor mode */
/**< Normal mode(register)	*/
#define DdRelc_D_DD_RELC_RUN_MODE_NORMAL				(0)
/**< Descriptor mode	*/
#define DdRelc_D_DD_RELC_RUN_MODE_DESC					(1)

/* Continuous Run Mode */
/**< Normal mode(once)	*/
#define DdRelc_D_DD_RELC_CONT_MODE_NORMAL			(0)
/**< Continuous Mode	*/
#define DdRelc_D_DD_RELC_CONT_MODE_CONT				(1)

/* RELC designated address */
/**< Designated address disable	*/
#define DdRelc_D_DD_RELC_ADDR_DISABLE							(0)
/**< Designated address enable 	*/
#define DdRelc_D_DD_RELC_ADDR_ENABLE							(1)

/* RELC addres increment */
/**< Address auto increment off	*/
#define DdRelc_D_DD_RELC_ADDR_INCRE_OFF					(0)
/**< Address auto increment on 	*/
#define DdRelc_D_DD_RELC_ADDR_INCRE_ON						(1)

/* interrupt flag */
/**< RELC interrupt end flag( processing is terminated )	*/
#define DdRelc_D_DD_RELC_INT_END_FLG								(0x00000001)
/**< RELC interrupt error flag( processing is abnormaly )	*/
#define DdRelc_D_DD_RELC_INT_ERR_FLG									(0x00000002)
/**< RELC interrupt sleep flag( processing is abnormaly )	*/
#define DdRelc_D_DD_RELC_INT_SLP_FLG									(0x00000004)

/* Interrupt type */
/**< Error interrupt	*/
#define DdRelc_D_DD_RELC_ERR													(1)
/**< Sleep interrupt	*/
#define DdRelc_D_DD_RELC_ERR													(2)
/**< Finish interrupt	*/
#define DdRelc_D_DD_RELC_FINISH											(3)
/**< Continuous run finish interrupt */
#define DdRelc_D_DD_RELC_CR_FINISH										(4)

/* error number */
/**< Input data error	*/
#define DdRelc_D_DD_RELC_ERR_INPUT_DATA_1						(0x0001)
/**< Input data error	*/
#define DdRelc_D_DD_RELC_ERR_INPUT_DATA_2						(0x0002)
/**< Input data error	*/
#define DdRelc_D_DD_RELC_ERR_INPUT_DATA_3						(0x0003)
/**< Input data error	*/
#define DdRelc_D_DD_RELC_ERR_INPUT_DATA_4						(0x0004)
/**< Bus error(input)	*/
#define DdRelc_D_DD_RELC_ERR_BUS_INPUT							(0x0010)
/**< Bus error(output) */
#define DdRelc_D_DD_RELC_ERR_BUS_OUTPUT						(0x0020)
/**< Address mismatch error(input)	*/
#define DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_INPUT	(0x1000)
/**< Address mismatch error(output)	*/
#define DdRelc_D_DD_RELC_ERR_ADDR_MISMATCH_OUTPUT	(0x2000)

/* type define */
/**< Type is defined to void	*/
#define void	void


/*---------------------------------------------------------------------	*/
/* dd_relc.c Definition													*/
/*---------------------------------------------------------------------	*/
/* Input buffer size */
/**< Input buffer size 64B */
#define DdRelc_D_DD_RELC_IN_BUF_64									(64)
/**< Input buffer size 128B */
#define DdRelc_D_DD_RELC_IN_BUF_128									(128)
/**< Input buffer size 256B */
#define DdRelc_D_DD_RELC_IN_BUF_256									(256)
/**< Input buffer size 512B */
#define DdRelc_D_DD_RELC_IN_BUF_512									(512)
/**< Input buffer size 1024B	*/
#define DdRelc_D_DD_RELC_IN_BUF_1024								(1024)
/**< Input buffer size 2048B	*/
#define DdRelc_D_DD_RELC_IN_BUF_2048								(2048)

/* Ref. buffer size */
/**< * Ref. buffer is mot exist */
#define DdRelc_D_DD_RELC_REF_NO_BUF									(0)
/**< * Ref. buffer size 8kbyte */
#define DdRelc_D_DD_RELC_REF_BUF_8K									(8196)


typedef struct _TDdRelcCtrlCmn						TDdRelcCtrlCmn;
typedef struct _TDdRelcCtrlReg						TDdRelcCtrlReg;
typedef struct _TDdRelcCtrlDesc						TDdRelcCtrlDesc;
typedef struct _TDdRelcDecInfo						TDdRelcDecInfo;
typedef union _UDdRelcSetMode2					UDdRelcSetMode2;

/** Type is defined to Callback function pointer for RELC */
typedef void (*RELK_CALLBACK)( kuint32 int_factor );

typedef struct _TDdRelcSetDesc						TDdRelcSetDesc;

#ifdef CO_DDIM_UTILITY_USE
typedef struct _TDdRelcSetModNormal			TDdRelcSetModNormal;
typedef struct _TDdRelcSetModDesc				TDdRelcSetModDesc;
#endif	/* CO_DDIM_UTILITY_USE */

typedef struct _DdRelc 										DdRelc;
typedef struct _DdRelcPrivate 						DdRelcPrivate;


/*----------------------------------------------------------------------*/
/* Enumeration																	*/
/*----------------------------------------------------------------------*/
// Nothing Special
/*----------------------------------------------------------------------*/
/* Structure  																		*/
/*----------------------------------------------------------------------*/
/** RELC control common table */
struct _TDdRelcCtrlCmn
{
		/**< Descriptor Mode*/
		kuchar descMode;
		/**< Continuous Run Mode*/
		kuchar contRunMode;
		/**< Sequential Run Number of Times*/
		kulong seqNum;
		/**< RELC data write side HPROT (default:0x0B)*/
		kuchar writeHprot;
		/**< RELC data read side HPROT (default:0x0B)*/
		kuchar readHprot;
		/**< Callback function pointer*/
		VpCallback callback;
};

/** RELC control register table */
struct _TDdRelcCtrlReg
{
		/**< Input End Address Enable*/
		kuchar inEndAddrEn;
		/**< Output End Address Enable*/
		kuchar outEndAddrEn;
		/**< Input Address Auto Increment*/
		kuchar inAddrAutoInc;
		/**< Output Address Auto Increment*/
		kuchar outAddrAutoInc;
		/**< Input start address*/
		kulong inStartAddr;
		/**< Input end address*/
		kulong inEndAddr;
		/**< Output start address*/
		kulong outStartAddr;
		/**< Output end address*/
		kulong outEndAddr;
};

/** RELC control descriptor table */
struct _TDdRelcCtrlDesc
{
		/**< Descriptor address	*/
		kulong descriptorAddr;
};

/** RELC decode information */
struct _TDdRelcDecInfo
{
		/**< Number of bytes read	*/
		kushort readByte;
		/**< Number of bytes written	*/
		kushort writeByte;
		/**< Number of processing blocks */
		kushort procBlock;
		/**< Decode the total number of bytes to read	*/
		kulong decTotalReadBytes;
		/**< Decode the total number of bytes to write	*/
		kulong decTotalWriteBytes;
		/**< Sequential run counter	*/
		kulong seqCnt;
};

/** RELC control mode2 for descriptor */
union _UDdRelcSetMode2
{
		/**< for kulong access	*/
		kulong word;
		/**< bit field*/
		struct {
				/**< Input end address enable	*/
				kulong imax :1;
				/**< Output end address enable	*/
				kulong omax :1;
				/**< Input Address Auto Increment	*/
				kulong iaai :1;
				/**< Output Address Auto Increment	*/
				kulong oaai :1;
				/**< reserved	*/
				kulong :28;
		} bit;
};

/** RELC control struct for descriptor */
struct _TDdRelcSetDesc
{
		/**< Mode setting 2*/
		UDdRelcSetMode2 relcMode2;
		/**< Reserved 1				*/
		//	kushort	reserved1;
		/**< Input start address	*/
		kulong inStartAddr;
		/**< Input end address*/
		kulong inEndAddr;
		/**< Output start address	*/
		kulong outStartAddr;
		/**< Output end address*/
		kulong outEndAddr;
		/**< Reserved 2	*/
		kulong reserved2;
		/**< Reserved 3	*/
		kulong reserved3;
		/**< Reserved 4	*/
		kulong reserved4;
};

#ifdef CO_DDIM_UTILITY_USE
//---------------------- utility section -------------------------------
/** RELC control struct for normal mode*/
struct _TDdRelcSetModNormal
{
		/**< RELC data write side HPROT (default:0x0B)	*/
		kuchar writeHprot;
		/**< RELC data read side HPROT (default:0x0B)	*/
		kuchar readHprot;
		/**< Input start address	 */
		kulong inStartAddr;
		/**< Input data size*/
		//	kulong		inDataSize;
		/**< Output start address	*/
		kulong outStartAddr;
		/**< Output data size	*/
		//	kulong		outDataSize;
		/**< Sequential Run Number of Times*/
		kulong seqNum;
		/**< Callback function pointer*/
		VpCallback callback;
} ;

/** RELC control struct for descriptor mode */
struct _TDdRelcSetModDesc
{
		/**< RELC data write side HPROT (default:0x0B)	*/
		kuchar writeHprot;
		/**< RELC data read side HPROT (default:0x0B) */
		kuchar readHprot;
		/**< descriptor address	*/
		kulong relcDescriptorAddr;
		/**< Sequential Run Number of Times */
		kulong seqNum;
		/**< Callback function pointer	*/
		VpCallback callback;
};
#endif	/* CO_DDIM_UTILITY_USE */

struct _DdRelc
{
	KObject parent;
};


KConstType 		    		dd_relc_get_type(void);
DdRelc*		        			dd_relc_new(void);

/*----------------------------------------------------------------------	*/
/* Global Data																*/
/*----------------------------------------------------------------------	*/
/* Nothing Special */

/*----------------------------------------------------------------------	*/
/* Macro                                                                			*/
/*----------------------------------------------------------------------	*/
/* Nothing Special */

/*----------------------------------------------------------------------	*/
/* Function																		*/
/*----------------------------------------------------------------------	*/

//---------------------------- driver section ----------------------------

/**
 *RELC initialize.
 *@param[in] writeHprot			RELC data write side HPROT (default:0x0B)
 *@param[in] readHprot			RELC data read side HPROT (default:0x0B)
 *@remarks This function performs interrupt permission and soft reset.
 */
extern	void dd_relc_init(DdRelc*self, kuchar writeHprot, kuchar readHprot );

/**
RELC is exclusively controlled.
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_EXT_LOCK_NG		Lock Error (System Using RELC)
@retval other	Fail.<br>
@remarks If RELC is unused, exclusive control OK is sent back as (Lock) while using it.<br>
         Exclusive control NG is sent back when using it (Lock inside of present).
*/
extern kint32 dd_relc_open (DdRelc*self);

/**
RELC is exclusively closed.
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_EXT_LOCK_NG		Lock Error (System Using RELC)
@remarks This API uses DDIM_User_Sig_Sem().
*/
extern	kint32 dd_relc_close(DdRelc*self);

/**
RELC decode is started.(Sync)
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_FLG_CLR_NG		Clear flag is NG
@retval DdRelc_D_DD_RELC_TIMEOUT			twai_flg is time out
@remarks This function will wait until the end of the decoding process.
@remarks This API uses DDIM_User_Clr_Flg().
@remarks This API uses DDIM_User_Twai_Flg().
*/
extern	kint32 dd_relc_start_sync( DdRelc*self );

/**
RELC decode is started.(Async)
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_FLG_CLR_NG		Clear flag is NG
@remarks The RELC is started by this function, and is waited by RELC_Wait_End().
@remarks This API uses DDIM_User_Clr_Flg().
*/
extern	kint32 dd_relc_start_async( DdRelc*self );

/**
Wait for the completion of the RELC decode.
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_TIMEOUT			twai_flg is time out
@remarks This function is used when RELC is started by RELC_Start_Async().
@remarks This API uses DDIM_User_Twai_Flg().
*/
extern	kint32 dd_relc_wait_end( DdRelc*self );

/**
RELC decode is stopped.(both Sync and Async)
*/
extern	void dd_relc_stop( DdRelc*self );

/**
The common control setting for RELC is set.
@param[in] relcCtrlCmn			RELC common control parameter
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be set below.<br>
			Descriptor mode 				: 0(normal/1(descriptor)<br>
			Continuous run mode 			: 0(normal)/1(continuous run)<br>
			Sequential run number of times	: When 0 or 1 is specified, a value is 1.<br>
			Callback function pointer 		: To define the function you want to call at interrupt time.
*/
extern	kint32 dd_relc_ctrl_common(DdRelc*self, TDdRelcCtrlCmn const* const relcCtrlCmn );

/**
The register control setting for RELC is set.
@param[in] relcCtrlReg			RELC register control parameter
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be set below.<br>
			Input end address enable 		: 0(disable)/1(enable)<br>
			Output end address enable 		: 0(disable)/1(enable)<br>
			Input address auto increment	: 0(disable)/1(enable)<br>
			Output address auto increment	: 0(disable)/1(enable)<br>
			Input start address<br>
			Input end address<br>
			Output start address<br>
			Output end address
*/
extern	kint32 dd_relc_ctrl_register(DdRelc*self, TDdRelcCtrlReg const* const relcCtrlReg );

/**
The descriptor control setting for RELC is set.
@param[in] relcCtrlDesc			RELC descriptor control parameter
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be set below.<br>
			descriptor address
*/
extern	kint32 dd_relc_ctrl_descriptor(DdRelc*self, TDdRelcCtrlDesc const* const relcCtrlDesc );

/**
The input start address for RELC is set.
@param[in] inStartAddr			Input start address
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks If you set during the operation of the SLEEP, without having to reset <br>
		 the Resume is not guaranteed.
*/
extern	kint32 dd_relc_set_in_start_addr(DdRelc*self, kulong inStartAddr );

/**
The input end address for RELC is set.
@param[in] inEndAddr				Input end address
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks To enable this designation should be set relc_mode2[0](IMAX) to 1.
*/
extern	kint32 dd_relc_set_in_end_addr(DdRelc*self, kulong inEndAddr);

/**
The output start address for RELC is set.
@param[in] outStartAddr			Output start address
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks If you set during the operation of the SLEEP, without having to reset <br>
		 the Resume is not guaranteed.
*/
extern	kint32 dd_relc_set_out_start_addr(DdRelc*self, kulong outStartAddr);

/**
The output end address for RELC is set.
@param[in] outEndAddr				Output end address
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks To enable this designation should be set relc_mode2[1](OMAX) to 1.
*/
extern	kint32 dd_relc_set_out_end_addr(DdRelc*self, kulong outEndAddr);

/**
The common control setting for RELC is get.
@param[out] relcCtrlCmn			RELC common control parameter
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be get below.<br>
			Descriptor mode 				: 0(normal/1(descriptor)<br>
			Continuous run mode 			: 0(normal)/1(continuous run)<br>
			Sequential run number of Times	: When 0 or 1 is specified, a value is 1.<br>
			Callback function pointer 		: To define the function you want to call at interrupt time.
*/
extern	kint32 dd_relc_get_ctrl_common(DdRelc*self, TDdRelcCtrlCmn* const relcCtrlCmn);

/**
The register control setting for RELC is get.
@param[out] relcCtrlReg			RELC register control parameter
@retval DdRelc_D_DD_RELC_OK				OK
@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
@remarks This function can be get below.<br>
			Input end address enable 		: 0(disable)/1(enable)<br>
			Output end address enable 		: 0(disable)/1(enable)<br>
			Input address auto increment	: 0(disable)/1(enable)<br>
			Output address auto increment	: 0(disable)/1(enable)<br>
			Input start address<br>
			Input end address<br>
			Output start address<br>
			Output end address
*/
extern	kint32 dd_relc_get_ctrl_register(DdRelc*self, TDdRelcCtrlReg* const relcCtrlReg );

/**
 *The descriptor control setting for RELC is get.
 *@param[out] relcCtrlDesc			RELC descriptor control parameter
 *@retval DdRelc_D_DD_RELC_OK				OK
 *@retval DdRelc_D_DD_RELC_PARAM_ERR			Parameter error
 *@remarks This function can be get below.<br> descriptor address
 */
extern	kint32 dd_relc_get_ctrl_descriptor(DdRelc*self, TDdRelcCtrlDesc* const relcCtrlDesc );

/**
 *It is Interrupt Handler of RELC.<br>
 *The interruption flag is cleared, and the CallBack function is called.<br>
 *@remarks This handler operates in the following cases.<br>
 *			RELC decode error is occured.<br>
 *			RELC decode is stopped.<br>
 *			Normal mode of RELC decode is finished.<br>
 *			Continuous run mode of RELC decode is finished.
 *@remarks	This API uses DDIM_User_Set_Flg().
 */
extern	void dd_relc_int_handler( DdRelc*self );


#ifdef __cplusplus
}
#endif

/*@} --- end of relc_driver_api */

/*----------------------------------------------------------------------*/
/* Message																*/
/*----------------------------------------------------------------------*/
/** @weakgroup dd_relc
@{*/

// Nothing Special

/*@} --- end of relc_driver_message */


#endif /* __DD_RELC_H__ */
