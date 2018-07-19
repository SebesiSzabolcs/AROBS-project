/*
 * UARTModule.h
 *
 * Created: 7/17/2018 9:59:56 PM
 *  Author: bruno.sebesi
 */ 


#ifndef UARTMODULE_H_
#define UARTMODULE_H_
void UARTInit(uint16_t ubrr);
void UARTSendChar(uint8_t uartMessage);
void UARTSendString(char* myString);
#endif /* UARTMODULE_H_ */