#ifndef COMMUNICATION_TRANSPORT_UART_H
#define COMMUNICATION_TRANSPORT_UART_H

/******************************************************************************
 * File        : communication_transport_uart.h
 * Description : UART Transport Layer
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "communication_transport.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Configuration
 ******************************************************************************/

#ifndef COMM_UART_BAUDRATE
#define COMM_UART_BAUDRATE      921600U
#endif

/******************************************************************************
 * Public API
 ******************************************************************************/

CommunicationStatus_t CommunicationTransportUART_Init(void);

CommunicationStatus_t CommunicationTransportUART_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
