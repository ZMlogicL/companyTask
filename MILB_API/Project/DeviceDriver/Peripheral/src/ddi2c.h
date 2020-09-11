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


#ifndef _DD_I2C_H_
#define _DD_I2C_H_

#include "klib.h"
#include "driver_common.h"
#include "ddi2cctrl.h"


#define DD_TYPE_I2C				(dd_i2c_get_type())
#define DD_I2C(obj)				(K_TYPE_CHECK_INSTANCE_CAST(obj, DdI2c))
#define DD_IS_I2C(obj)			(K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_I2C))

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
// Return value of I2C processing result
#define	DdI2c_INPUT_PARAM_ERROR	(D_DD_I2C | D_DDIM_INPUT_PARAM_ERROR)	/**< Input parameter error	*/
#define	DdI2c_SEM_NG			(D_DD_I2C | D_DDIM_SEM_NG) 				/**< Semaphore acquisition NG	*/
#define	DdI2c_TIMEOUT			(D_DD_I2C | D_DDIM_TIMEOUT) 			/**< Timeout (need to dd_i2c_ctrl_close())	*/
#define	DdI2c_BUS_ERROR			(D_DD_I2C | D_DDIM_BUS_ERROR)			/**< Bus error */
#define DdI2c_STATUS_ABNORMAL	(D_DD_I2C | D_DDIM_STATUS_ABNORMAL)		/**< Abnormal Status */
#define	DdI2c_ARBITRATION_LOST	(D_DD_I2C | D_DDIM_ARBITRATION_LOST)	/**< Arbitration lost detect */
#define	DdI2c_COMM_ERROR		(D_DD_I2C | D_DDIM_COMM_ERROR)			/**< Communication error */
#define	DdI2c_PEC_ERROR			(D_DD_I2C | D_DDIM_PARITY_DATA)			/**< Packet Error */

#define DdI2c_SEND_DATA_2_MASTER	(1)			/**<Send data to master*/
#define DdI2c_SEND_ACK_MASTER		(2)			/**<Send ACK to master*/
#define DdI2c_SEND_NO_ACK_MASTER 	(3)			/**<Send NO ACK to master*/

#define DdI2c_SCLFRQ_MAX			(127)			// SCLFRQ Max value (4 - 127)

// Interrupt flag
#define	DdI2c_FLG_0				(0x00000001)	// I2C-0 interrupt flag
#define	DdI2c_FLG_1				(0x00000002)	// I2C-1 interrupt flag
#define	DdI2c_FLG_2				(0x00000004)	// I2C-2 interrupt flag

#define DdI2c_PCLK_25_0			(25000000)		// PCLK 25MHz
#define DdI2c_PCLK_50_0			(50000000)		// PCLK 50MHz

#define DdI2c_SCLFRQ_100K_50MHZ	(125)			// SCLFRQ value (100Kbps, PCLK=50MHz)
#define DdI2c_SCLFRQ_100K_25MHZ	(63)			// SCLFRQ value (100Kbps, PCLK=25MHz)
#define DdI2c_SCLFRQ_400K_50MHZ	(32)			// SCLFRQ value (400Kbps, PCLK=50MHz)
#define DdI2c_SCLFRQ_400K_25MHZ	(16)			// SCLFRQ value (400Kbps, PCLK=25MHz)

// I2C ch
typedef enum {
	DdI2c_CH_00 = 0,			// Channel 0
	DdI2c_CH_01 ,			// Channel 1
	DdI2c_CH_02 ,			// Channel 2
	DdI2c_CH_MAX				// End flag
} DdI2cChannel;

// I2C Communication state
typedef enum {
	DdI2c_STATE_IDLE = 0,			// IDLE
	DdI2c_STATE_SENDING_DATA ,		// Sending Data
	DdI2c_STATE_RECEIVING_DATA,		// Receiving data
	DdI2c_STATE_SENDING_ADDRESS,		// Sending Address used on 10 bit address
	DdI2c_STATE_END,					// Done normally
	DdI2c_STATE_ERROR				// Error occurred
} DdI2cState;

// I2C Communication Event
typedef enum {
	DdI2c_EVENT_START_READ = 0,		// Send START and read
	DdI2c_EVENT_START_WRITE ,		// Send START and write
	DdI2c_EVENT_SEND ,				// Send Address or Data
	DdI2c_EVENT_RECEIVE ,			// Receive Data
	DdI2c_EVENT_ERROR,				// Deal with error
	DdI2c_EVENT_STOP,				// Send STOP
	DdI2c_EVENT_SEND_PEC,			// Sending PEC byte
	DdI2c_EVENT_END_RW				// End read or write
} DdI2cEvent;

typedef union _DdI2cSlaveAddr DdI2cSlaveAddr;

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
union _DdI2cSlaveAddr {
	UCHAR		addrByte[DdI2cCtrl_ADDR_BYTE_END];	// Used to access whole byte
	struct {
		UCHAR	rw				:1;		// 1: Read from slave	0:Write	to slave
		UCHAR	addr			:7;		// 7 bit slave address
		UCHAR					:8;		// reserve
	} bit;	// Used to 7 bit data
};


typedef struct _DdI2c 			DdI2c;
typedef struct _DdI2cPrivate 	DdI2cPrivate;

struct  _DdI2c {
	KObject parent;
};

/*----------------------------------------------------------------------*/
/* Function																*/
/*----------------------------------------------------------------------*/
#ifdef __cplusplus
"C" {
#endif

KConstType 	dd_i2c_get_type(void);
DdI2c* 		dd_i2c_get(void);

UINT32 		dd_i2c_get_event_flg(DdI2c *self, UCHAR ch);

VOID 		dd_i2c_init_pec_info(DdI2c *self, UCHAR ch);

/**
Terminate the I2C.
@param[in] ch	I2C channel number (0 to 2)
*/
VOID 		dd_i2c_terminate(DdI2c *self, UCHAR ch);

/**
Get Test SDA.
@param[in] ch		I2C channel number (0 to 2)
@param[out] sda		Test SDA value (0:Low, 1:High)
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
*/
INT32 		dd_i2c_get_test_sda(DdI2c *self, UCHAR ch, UCHAR* sda);

/**
Get Error Cause.
@param[in] ch		I2C channel number (0 to 2)
@retval D_DDIM_OK					: OK
@retval	DdI2c_TIMEOUT			: Timeout (need to dd_i2c_ctrl_close())
@retval	DdI2c_BUS_ERROR			: Bus error
@retval	DdI2c_ARBITRATION_LOST	: Arbitration lost detect
@retval	DdI2c_COMM_ERROR			: Communication error
@retval	DdI2c_PEC_ERROR			: Packet Error
@remarks	This API uses DDIM_User_Set_Flg().
*/
UINT32 		dd_i2c_get_error_cause(DdI2c *self, UCHAR ch);

/**
Set Toggle SCL.
When SDA is low, setting 1 to this API toggles SCL for one cycle.<br>
Setting 1 to this API while SDA is high is ignored.<br>
@param[in] ch		I2C channel number (0 to 2)
@retval D_DDIM_OK					: OK
@retval DdI2c_INPUT_PARAM_ERROR	: Input Parameter Error
*/
INT32 		dd_i2c_set_toggle_scl(DdI2c *self, UCHAR ch);

/**
Intterupt handler.
The interruption flag is cleared, and the CallBack function is called when slave operatrion.<br>
(Only an interruption clear flag of CallBack when it is unregistered.)
@param [in] ch	I2C channel number (0 to 2)
*/
VOID 		dd_i2c_int_handler(DdI2c *self, UCHAR ch);

INT32 		dd_i2c_open(DdI2c *self, UCHAR ch, INT32 timeout);
INT32	 	dd_i2c_close(DdI2c *self, UCHAR ch);
INT32 		dd_i2c_start_master(DdI2c *self, UCHAR ch, const DdI2cStartInfo* const startInfo);
INT32 		dd_i2c_stop_master(DdI2c *self, UCHAR ch);
INT32 		dd_i2c_start_slave(DdI2c *self, UCHAR ch);
INT32 		dd_i2c_stop_slave(DdI2c *self, UCHAR ch);
INT32 		dd_i2c_ctrl_master(DdI2c *self, UCHAR ch, const DdI2cCtrlMaster* const ctrlMaster);
INT32 		dd_i2c_get_ctrl_master(DdI2c *self, UCHAR ch, DdI2cCtrlMaster* const ctrlMaster);
INT32 		dd_i2c_ctrl_slave(DdI2c *self, UCHAR ch, const DdI2cCtrlSlave* const ctrlSlave);
INT32 		dd_i2c_get_ctrl_slave(DdI2c *self, UCHAR ch, DdI2cCtrlSlave* const ctrlSlave);
INT32 		dd_i2c_ctrl_smbus(DdI2c *self, UCHAR ch, const DdI2cCtrlSmbus* const ctrlSmbus);
INT32 		dd_i2c_get_ctrl_smbus(DdI2c *self, UCHAR ch, DdI2cCtrlSmbus* const ctrlSmbus);
#ifdef CO_DDIM_UTILITY_USE
INT32 		dd_i2c_set_scl(DdI2c *self, UCHAR ch, UCHAR scl);
INT32 		dd_i2c_get_scl(DdI2c *self, UCHAR ch, UCHAR* scl);
#endif

DdI2cState dd_i2c_get_state(DdI2c *self, UCHAR ch);
void 		dd_i2c_set_state(DdI2c *self, UCHAR ch, DdI2cState state);
void 		dd_i2c_set_next_event(DdI2c *self, UCHAR ch, DdI2cEvent nextEvent);
UINT32 		dd_i2c_get_error(DdI2c *self, UCHAR ch);
void 		dd_i2c_set_error(DdI2c *self, UCHAR ch, UINT32 err);
void 		dd_i2c_set_data_count(DdI2c *self, UCHAR ch, UINT32 dataCount);
void 		dd_i2c_set_data(DdI2c *self, UCHAR ch, UCHAR* data);
void 		dd_i2c_set_data_num(DdI2c *self, UCHAR ch, UINT32 dataNum);
UINT32 		dd_i2c_get_pec_byte_num(DdI2c *self, UCHAR ch);
void 		dd_i2c_set_pec_byte_num(DdI2c *self, UCHAR ch, UINT32 pecByteNum);


#ifdef __cplusplus
}
#endif


#endif

