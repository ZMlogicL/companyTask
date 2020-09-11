/*
 * @Copyright (C) 2010-2019 上海网用软件有限公司
 * @date              :2020年9月5日
 * @author            :冯黎阳
 * @brief             :
 * @rely              :klib
 * @function
 * @version
 *
 */


#ifndef __DD_I2C_CTRL_H__
#define __DD_I2C_CTRL_H__

#include "klib.h"
#include "driver_common.h"


#define DD_TYPE_I2C_CTRL				(dd_i2c_ctrl_get_type())
#define DD_I2C_CTRL(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdI2cCtrl))
#define DD_IS_I2C_CTRL(obj)				(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_I2C_CTRL))


/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/** Recieve action from master side */
typedef enum {
	DdI2cCtrl_RECV_FROM_MASTER_NO_ACK = 0,	/**< Receive NO ACK from Master	*/
	DdI2cCtrl_RECV_FROM_MASTER_ACK,			/**< Receive ACK from Master	*/
	DdI2cCtrl_RECV_FROM_MASTER_DATA,			/**< Receive Data from Master	*/
	DdI2cCtrl_RECV_FROM_MASTER_ADDRESS,		/**< Receive Address from Master.*/
	DdI2cCtrl_RECV_FROM_MASTER_ERROR,		/**< Error occured.*/
} I2cRecvFromMaster;

/** Communication Mode */
typedef enum {
	DdI2cCtrl_RW_MODE_READ = 0,					/**< Read from slave only	*/
	DdI2cCtrl_RW_MODE_WRITE,						/**< Write to slave only	*/
} I2cRwMode;

/** Communication rate */
typedef enum {
	DdI2cCtrl_BPS_100 = 0,						/**< 100kbps	*/
	DdI2cCtrl_BPS_400							/**< 400kbps	*/
} DdI2cBps;

/** Address length */
typedef enum {
	DdI2cCtrl_ADDR_LEN_7 = 0,					/**< 7 bit address	*/
	DdI2cCtrl_ADDR_LEN_10						/**< 10 bit address	*/
} DdI2cAddrLen;

/** Timeout Divider */
typedef enum {
	DdI2cCtrl_TO_DIV_NO_CHECK = 0,				/**< Timer Disabled			*/
	DdI2cCtrl_TO_DIV_4,							/**< Divide by 4			*/
	DdI2cCtrl_TO_DIV_8,							/**< Divide by 8			*/
	DdI2cCtrl_TO_DIV_16,							/**< Divide by 16			*/
} DdI2cToDiv;

// Communication Side
typedef enum {
	DdI2cCtrl_SIDE_MASTER = 0,	// Master
	DdI2cCtrl_SIDE_SLAVE			// Slave
} DdI2cSide;

// I2C Address counter
typedef enum {
	DdI2cCtrl_ADDR_BYTE_1ST = 0,	// 7 bit address or first byte of 10 bit address
	DdI2cCtrl_ADDR_BYTE_2ND ,		// second byte of 10 bit address
	DdI2cCtrl_ADDR_BYTE_END		// End flag
} DdI2cAddrCnt;

typedef struct _DdI2cSlaveAction DdI2cSlaveAction;
typedef struct _DdI2cStartInfo DdI2cStartInfo;
typedef struct _DdI2cCtrlMaster DdI2cCtrlMaster;
typedef struct _DdI2cCtrlSlave DdI2cCtrlSlave;
typedef struct _DdI2cCtrlSmbus DdI2cCtrlSmbus;

/** Send Action from slave side */
struct _DdI2cSlaveAction {
	UCHAR actionMode;	/**< What do at slave.<br> */
						/**< @ref DdI2c_SEND_DATA_2_MASTER : Send data<br> */
						/**< @ref DdI2c_SEND_ACK_MASTER    : Send ACK <br> */
						/**< @ref DdI2c_SEND_NO_ACK_MASTER : Send NO ACK<br> */
	UCHAR sendData;	/**< Send data */
};

/**
Type is defined to Callback function pointer.<br>
@param [in] UCHAR						Channel number.
@param [in] I2cRecvFromMaster	Recieved action from master side.
@param [in] UCHAR						Received data from master side.
@retval DdI2cSlaveAction	Send action from slave side.
*/
typedef DdI2cSlaveAction (*DdI2cCtrlFunc)(UCHAR, I2cRecvFromMaster, UCHAR);

/** Start information */
struct _DdI2cStartInfo {
	I2cRwMode	rwMode;			/**< Read or Write */
	UINT32		rwDataLen;		/**< Read/Write data length */
	UCHAR* 		rwData;			/**< Read/Write data */
	UINT32		timeout;			/**< Communication timeout value (ms) */
};

/** Control information for Master */
struct _DdI2cCtrlMaster {
	DdI2cBps		bps;					/**< Communication rate	*/
	DdI2cAddrLen	destSlaveAddrLen;	/**< Destination slave address length */
	USHORT			destSlaveAddr;		/**< Destination slave address */
};

/** Control information for Slave */
struct _DdI2cCtrlSlave {
	DdI2cAddrLen	ownSlaveAddrLen;	/**< Own Slave address length */
	USHORT			ownSlaveAddr;		/**< Own Slave address */
	UCHAR 			globalCallEn;		/**< Global Call Match Enable */
	DdI2cCtrlFunc	callback;			/**< Callback function pointer. See @ref DdI2cCtrlFunc.<br>
												 Please must set a callback in the case of Slave operation. */
};

/** Control information for SMBus (for Master and Slave) */
struct _DdI2cCtrlSmbus {
	UCHAR 			alertRespEn;		/**< Alert Response Match Enable (Slave only) */
	UINT32			pecNum;			/**< PEC(Packet Error Checking) number of bytes (0 is disable) */
	DdI2cToDiv		timeoutDiv;		/**< Timeout Divider */
	UCHAR			timeoutPresc;		/**< Timeout Prescaler (0 to 255) */
};

typedef struct _DdI2cCtrl 			DdI2cCtrl;
typedef struct _DdI2cCtrlPrivate 	DdI2cCtrlPrivate;


struct  _DdI2cCtrl {
	KObject parent;
};

#ifdef __cplusplus
"C" {
#endif


KConstType 		dd_i2c_ctrl_get_type(void);
DdI2cCtrl* 		dd_i2c_ctrl_new(void);

VOID 			dd_i2c_ctrl_init_timeout_info(DdI2cCtrl *self, UCHAR ch);

UCHAR 			dd_i2c_ctrl_get_scl_frequency(DdI2cCtrl *self, DdI2cBps bps);

/**
Execute exclusive control for designated I2C channel.<br>
When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
if the channel state is in-use (lock), return "DdI2c_SEM_NG".<br>
When timeout occurs, return "DdI2c_TIMEOUT".
@param [in]	ch		Channel number(0 to 2)
@param [in] timeout	Time of timeout<br>
					<ul><li>Positive Value(Time of timeout)
						<li>@ref D_DDIM_USER_SEM_WAIT_POL
						<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
@retval	D_DDIM_OK					: OK
@retval	DdI2c_INPUT_PARAM_ERROR	: Input parameter error
@retval	DdI2c_TIMEOUT			: Semaphore acquisition Time Out
@retval	DdI2c_SEM_NG				: Semaphore acquisition NG
@remarks	This API uses DDIM_User_Pol_Sem() when wait_time is set to 0. <br>
			This API uses DDIM_User_Twai_Sem() when wait_time is set to the value except for 0.
*/
INT32 			dd_i2c_ctrl_open(DdI2cCtrl *self, UCHAR ch, INT32 timeout);

/**
Cancel exclusive control for designated I2C channel.
@param[in] ch		I2C channel number (0 to 2)
@retval	D_DDIM_OK					: OK
@retval	DdI2c_INPUT_PARAM_ERROR	: Input parameter error
@retval	DdI2c_SEM_NG				: Semaphore acquisition NG
@remarks	Please note that stop & exclusive control is compulsorily released when I2C is starting.
@remarks	This API uses DDIM_User_Sig_Sem().
*/
INT32	 		dd_i2c_ctrl_close(DdI2cCtrl *self, UCHAR ch);

/**
Send start condition.
@param[in] ch 			2C's ch number (0 to 2)
@param[in] startInfo	Start information
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
@retval DdI2c_ERROR				: System Error
@retval DdI2c_BUS_ERROR			: Bus Error
@retval DdI2c_ARBITRATION_LOST	: Arbitration lost detect
@retval DdI2c_COMM_ERROR			: Communication Error
@retval DdI2c_TIMEOUT			: Process Timeout
@retval DdI2c_STATUS_ABNORMAL	: Abnormal Status
@remarks This API uses DDIM_User_Clr_Flg().
@remarks This API uses DDIM_User_Twai_Flg().
*/
INT32 			dd_i2c_ctrl_start_master(DdI2cCtrl *self, UCHAR ch, const DdI2cStartInfo* const startInfo);

/**
Send stop condition.
@param[in] ch	I2C channel number (0 to 2)
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
@retval DdI2c_STATUS_ABNORMAL	: Abnormal Status
*/
INT32 			dd_i2c_ctrl_stop_master(DdI2cCtrl *self, UCHAR ch);

/**
Start the communication waiting from the master.
@param[in] ch 			2C's ch number (0 to 2)
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
@retval DdI2c_STATUS_ABNORMAL	: Abnormal Status
*/
INT32 			dd_i2c_ctrl_start_slave(DdI2cCtrl *self, UCHAR ch);

/**
Stop thje communication waiting from the master.
@param[in] ch	I2C channel number (0 to 2)
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
*/
INT32 			dd_i2c_ctrl_stop_slave(DdI2cCtrl *self, UCHAR ch);

/**
Set I2C master contorol information.
@param[in] ch				I2C channel number (0 to 2)
@param[in] *ctrlMaster		Master control info. @ref DdI2cCtrlMaster.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
@remarks Please call either the dd_i2c_ctrl_ctrl_master() or dd_i2c_ctrl_ctrl_slave().
*/
INT32 			dd_i2c_ctrl_ctrl_master(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlMaster* const ctrlMaster);

/**
Get I2C master contorol information.
@param[in]  ch				I2C channel number (0 to 2)
@param[out] *ctrlMaster	Master control info. @ref DdI2cCtrlMaster.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
*/
INT32 			dd_i2c_ctrl_get_ctrl_master(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlMaster* const ctrlMaster);

/**
Set I2C slave contorol information.
@param[in] ch				I2C channel number (0 to 2)
@param[in] *ctrlSlave		Slave control info. @ref DdI2cCtrlSlave.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
@remarks Please call either the dd_i2c_ctrl_ctrl_master() or dd_i2c_ctrl_ctrl_slave().
*/
INT32 			dd_i2c_ctrl_ctrl_slave(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlSlave* const ctrlSlave);

/**
Get I2C slave contorol information.
@param[in]  ch				I2C channel number (0 to 2)
@param[out] *ctrlSlave		Slave control info. @ref DdI2cCtrlSlave.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
*/
INT32 			dd_i2c_ctrl_get_ctrl_slave(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlSlave* const ctrlSlave);

/**
Set SMBus slave contorol information.
@param[in] ch				I2C channel number (0 to 2)
@param[in] *ctrlSmbus		SMBus Control info. @ref DdI2cCtrlSmbus.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
@retval DdI2c_STATUS_ABNORMAL		: Abnormal Status
@remarks Please call this API as necessary after the dd_i2c_ctrl_ctrl_master() or dd_i2c_ctrl_ctrl_slave().
@remarks If you want to enable the PEC, please set the transmit and receive data byte number(DdI2cStartInfo.rwDataLen) + 1.
*/
INT32 			dd_i2c_ctrl_ctrl_smbus(DdI2cCtrl *self, UCHAR ch, const DdI2cCtrlSmbus* const ctrlSmbus);

/**
Get SMBus slave contorol information.
@param[in]  ch				I2C channel number (0 to 2)
@param[out] *ctrlSmbus		SMBus Control info. @ref DdI2cCtrlSmbus.<br>
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
@retval DdI2c_STATUS_ABNORMAL		: Abnormal Status
*/
INT32 			dd_i2c_ctrl_get_ctrl_smbus(DdI2cCtrl *self, UCHAR ch, DdI2cCtrlSmbus* const ctrlSmbus);

#ifdef CO_DDIM_UTILITY_USE
/**
Set SCL frequency utility function.<br>
@param [in] ch	I2C channel number (0 to 2)
@param [in] scl	SCL frequency (range of 4..127)
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
@remarks Selecting a value of less than 4 will automatically default by adding an offset of 4.
*/
INT32 			dd_i2c_ctrl_set_scl(DdI2cCtrl *self, UCHAR ch, UCHAR scl);

/**
Get SCL frequency utility function.<br>
@param [in]  ch		I2C channel number (0 to 2)
@param [out] scl	SCL frequency
@retval D_DDIM_OK						: OK
@retval DdI2c_INPUT_PARAM_ERROR		: Input Parameter Error
*/
INT32 			dd_i2c_ctrl_get_scl(DdI2cCtrl *self, UCHAR ch, UCHAR* scl);

#endif

DdI2cSide 		dd_i2c_ctrl_get_side(DdI2cCtrl *self, UCHAR ch);
DdI2cAddrLen 	dd_i2c_ctrl_get_master_dest_slave_addr_len(DdI2cCtrl *self, UCHAR ch);
UCHAR 			dd_i2c_ctrl_get_slave_addr_byte(DdI2cCtrl *self, UCHAR ch, DdI2cAddrCnt cnt);
DdI2cCtrlFunc 	dd_i2c_ctrl_get_slave_callback(DdI2cCtrl *self, UCHAR ch);

#ifdef __cplusplus
}
#endif


#endif // __DD_I2C_CTRL_H__

