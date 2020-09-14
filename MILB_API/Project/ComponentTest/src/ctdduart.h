/**
 * @file		ct_dd_uart.h
 * @brief		This is ct header for ct_dd_uart.c.
 * @note		None
 * @attention	None
 * 
 * <B><I>Copyright 2015 Socionext Inc.</I></B>
 */
#ifndef _CT_DD_UART_H_
#define _CT_DD_UART_H_

#include "driver_common.h"
#include <klib.h>

#define CT_TYPE_DD_UART					(ct_dd_uart_get_type())
#define CT_DD_UART(obj)					(K_TYPE_CHECK_INSTANCE_CAST (obj, CtDdUart)) 
#define CT_IS_DD_UART(obj)					(K_TYPE_CHECK_INSTANCE_TYPE (obj, CT_TYPE_DD_UART)) 


/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
#define CtDdUart_D_UART_SRC_ADDR			(0x5A000000)	// UART TRANSFER SOURCE BUFFER ADDRESS
#define CtDdUart_D_UART_SRC_SIZE			(0x1000)		// UART TRANSFER SOURCE BUFFER SIZE(sizeof(CHAR[4096]))
#define CtDdUart_D_UART_SLAVE_ADDR_0		(0x01)			// UART slave address
#define CtDdUart_D_UART_SLAVE_ADDR_1		(0x02)			// UART slave address
#define CtDdUart_D_UART_SLAVE_ADDR_2		(0x04)			// UART slave address
#define CtDdUart_D_UART_SLAVE_ADDR_3		(0x08)			// UART slave address
//#define D_UART_SLAVE_ADDR_4	(0x10)			// UART slave address
#define CtDdUart_D_UART_SLAVE_ADDR_5		(0x20)			// UART slave address

typedef struct 			_CtDdUart CtDdUart;
typedef struct 			_CtDdUartPrivate CtDdUartPrivate;

struct _CtDdUart
{
	KObject parent;

};

extern kuchar gUartRBuff[256];
extern kuchar gUARTCh;

KConstType 			ct_dd_uart_get_type(void);
CtDdUart* 			ct_dd_uart_new(void);

/*----------------------------------------------------------------------*/
/* Definition															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Enumeration															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Structure															*/
/*----------------------------------------------------------------------*/
/* Nothing Special */

/*----------------------------------------------------------------------*/
/* Function Prototype Definition										*/
/*----------------------------------------------------------------------*/


//
void  				ct_dd_uart_send_callback_cb();
void  				ct_dd_uart_receive_callback_cb( void const *const r_result );
void  				ct_dd_uart_receive_callback_echo_cb( void const *const r_result );
void  				ct_dd_uart_receive_callback_dma_cb( void const *const r_result );
void 				ct_dd_uart_send_dma_callback_cb(kint32 status);
void 				ct_dd_uart_recv_dma_callback_cb(kint32 status);

void				ct_dd_uart_main(CtDdUart* self,int argc, char** argv);
void				ct_dd_uart_pcsim_test( CtDdUart* self );


#endif	// _CT_DD_UART_H_
