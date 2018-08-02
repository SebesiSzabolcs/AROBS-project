/*
 * SPIModule.h
 *
 * Created: 7/30/2018 9:53:07 PM
 *  Author: bruno.sebesi
 */ 


#ifndef SPIMODULE_H_
#define SPIMODULE_H_
void SPIInit(void);
uint8_t SPISendByte(uint8_t SPISentMessage);
uint8_t SPIRecieveByte(void);
#endif /* SPIMODULE_H_ */