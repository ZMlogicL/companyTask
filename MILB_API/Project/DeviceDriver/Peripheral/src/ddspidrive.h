/*
* @Copyright(C) 2010-2020 上海网用软件有限公司
* @date        : 2020-09-04
* @author    : 肖泽友
* @brief        :SPI(Serial Peripheral Interface) driver
* @rely         :klib
* @function :sns 索喜rtos，采用ETK-C语言编写
* 设计的主要功能:
*          1、driver section
*
*@version   :1.0.0
*
*/

#ifndef __DD_SPI_DRIVE_H__
#define __DD_SPI_DRIVE_H__

#include <klib.h>
#include "ddspidrivebranch.h"

#define DD_TYPE_SPI_DRIVE                     (dd_spi_drive_get_type())
#define DD_SPI_DRIVE(obj)                       K_TYPE_CHECK_INSTANCE_CAST(obj, DdSpiDrive)
#define DD_IS_SPI_DRIVE(obj)                  K_TYPE_CHECK_INSTANCE_TYPE(obj, DD_TYPE_SPI_DRIVE)

typedef struct _DdSpiDrive                       DdSpiDrive;
typedef struct _DdSpiDrivePrivate           DdSpiDrivePrivate;

struct _DdSpiDrive
{
	KObject parent;
};

KConstType              dd_spi_drive_get_type(void);
DdSpiDrive*             dd_spi_drive_get(void);

/*
*Execute exclusive control for designated SPI channel.<br>
*When the designated channel is idle (un-lock) state, change the channel state to use(lock) and return "D_DDIM_OK",<br>
*if the channel state is in-use (lock), return "D_DD_SPI_SEM_NG".<br>
*When timeout occurs, return "D_DD_SPI_SEM_TIMEOUT".
*@param [in]	ch		Channel number(0 to 2)
*@param [in] timeOut	Time of timeout<br>
*					<ul><li>Positive Value(Time of timeout)
*					<li>@ref D_DDIM_USER_SEM_WAIT_POL
*					<li>@ref D_DDIM_USER_SEM_WAIT_FEVR</ul>
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SPI_SEM_TIMEOUT		: Semaphore acquisition Time Out
*@retval		D_DD_SPI_SEM_NG				: Semaphore acquisition NG
*/
kint32                        dd_spi_drive_open(DdSpiDrive* self, kuchar ch, kint32 timeOut);

/*
*Cancel exclusive control for designated SPI channel.<br>
*@param [in]	ch	Channel number(0 to 2)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SPI_SEM_NG				: Semaphore release NG
*/
kint32                        dd_spi_drive_close(DdSpiDrive* self, kuchar ch);

/*
*Set SPI operation condition and callback function for the specified channel.
*@param [in]	ch			Channel number(0 to 2)
*@param [in]	spiCtrl	SPI Control data. See @ref TDdSpiCtrl.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@retval		D_DD_SPI_STATUS_ABNORMAL	: Abnormal status
*@remarks
*	- SPI format is supported only Motorola SPI.
*	- Please refer to the @ref SPI_Channel_Specification for specification of each SPI channel.<br>
*/
kint32                        dd_spi_drive_ctrl(DdSpiDrive* self, kuchar ch, TDdSpiCtrl const* const spiCtrl);

/*
*Get SPI operation condition and callback function for the specified channel.
*@param [in]		ch			Channel number(0 to 2)
*@param [out]	spiCtrl	SPI Control data. See @ref TDdSpiCtrl.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                        dd_spi_drive_get_ctrl(DdSpiDrive* self, kuchar ch, TDdSpiCtrl* const spiCtrl);

/*
*Set sending data information.
*Please input transmitted data Buffer pointer and size information.
*@param [in]	ch			Channel number(0 to 2)
*@param [in]	sendAddr	Send data address
*@param [in]	num			Number of data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*	- The value must be guaranteed about the transmission data until the transmission processing is completed.<br>
*	- Set "USHORT" pointer to sendAddr when Data Length is "E_DD_SPI_BIT_LEN_9" or more.<br>
*	- Set "kuchar" pointer to sendAddr when Data Length is "E_DD_SPI_BIT_LEN_8" or less.<br>
*	- If after this API was called the Dd_SPI_Set_Recv_Data(), "num" will be overwritten.
*/
kint32                        dd_spi_drive_set_send_data(DdSpiDrive* self, kuchar ch,
		                               void const* const sendAddr, kuint32 num);

/*
*Set receiving data information.
*@param [in]	ch	Channel number(0 to 2)
*@param [in]	recvAddr	Receive data address
*@param [in]	num			Number of data
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*	- Set "USHORT" pointer to recvAddr when Data Length is "E_DD_SPI_BIT_LEN_9" or more. <br>
*	- Set "kuchar" pointer to recvAddr when Data Length is "E_DD_SPI_BIT_LEN_8" or less.<br>
*	- If after this API was called the Dd_SPI_Set_Send_Data(), "num" will be overwritten.
*/
kint32                        dd_spi_drive_set_recv_data(DdSpiDrive* self, kuchar ch,
		                               void const* const recvAddr, kuint32 num);

/*
*Stop sending/receiving data(force stop).
*@param [in]	ch	Channel number(0 to 2)
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*			- If want to run again after running this API, please reconfigure Dd_SPI_Ctrl().
*			- Please call this API using the timer if want to stop the transfer.(in synchronous transfer)
 */
kint32                        dd_spi_drive_stop(DdSpiDrive* self, kuchar ch);

/*
*Set SPI Slave Select setting.
*@param [in]	ch			Channel number(0 to 2)
*@param [in]	ssInfo		SPI Slave Select setting information. See @ref DdSpiSsInfo.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*@remarks
*	- Please refer to the @ref SPI_Channel_Specification for CS specification of each SPI channel.<br>
*/
kint32                        dd_spi_drive_set_slave_select(DdSpiDrive* self, kuchar ch,
		                               DdSpiSsInfo const* const ssInfo);

/*
*Get SPI Slave Select setting.
*@param [in]		ch		Channel number(0 to 2)
*@param [out]	ssInfo	SPI Slave Select setting information. See @ref DdSpiSsInfo.
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                        dd_spi_drive_get_slave_select(DdSpiDrive* self, kuchar ch,
		                               DdSpiSsInfo* const ssInfo);

/*
*Set SPI Enable.
*@param [in]		ch		Channel number(0 to 2)
*@param [in]		enableSig	Enable signal selection. See @ref E_DD_SPI_ENABLE_SIG.<br>
*@param [in]		enable		Enable/Disable SPI port and TX/RX FIFOs.<br>
*@retval		D_DDIM_OK					: OK
*@retval		D_DD_SPI_INPUT_PARAM_ERROR	: Input parameter error
*/
kint32                        dd_spi_drive_set_spi_enable(DdSpiDrive* self, kuchar ch,
		                                DdSpiEnableSig enableSig, kboolean enable);

kint32                        dd_spi_drive_start_full_duplex(DdSpiDrive* self, kuchar ch);

kint32                        dd_spi_drive_start_recv(DdSpiDrive* self, kuchar ch);

kint32                        dd_spi_drive_start_send(DdSpiDrive* self, kuchar ch);

/*
 * 获取子类私有方法及属性
 */
void                          dd_spi_drive_get_branch_end_process(DdSpiDrive* self, kuchar ch);
void                          dd_spi_drive_get_branch_send_data(DdSpiDrive* self, kuchar ch);
void                          dd_spi_drive_get_branch_write_dummy_count(DdSpiDrive* self, kuchar ch);
kint32                        dd_spi_drive_get_branch_check_stopping_conditions(DdSpiDrive* self, kuchar ch);

TDdSpiInfo               dd_spi_drive_get_branch_spi_info(DdSpiDrive* self, kuchar ch);

void                          dd_spi_drive_set_branch_spi_info_add_recv_pos(DdSpiDrive* self,
		                                kuchar ch, kuint32 recvPos);
void                          dd_spi_drive_set_branch_spi_info_dma_wait(DdSpiDrive* self, kuchar ch, kuchar dmaWait);
void                          dd_spi_drive_set_branch_spi_info_force_stop_flg(DdSpiDrive* self,
		                                kuchar ch, kuchar forceStopFlg);
void                          dd_spi_drive_set_branch_spi_info_spi_mode(DdSpiDrive* self,
		                                kuchar ch, EDdSpiDir spiMode);
void                          dd_spi_drive_set_branch_spi_info_dummy_count(DdSpiDrive* self,
		                                kuchar ch, kuint32 dummyCount);

#endif /* __DD_SPI_DRIVE_H__ */
