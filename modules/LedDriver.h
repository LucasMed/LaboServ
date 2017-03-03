/*
 * LedDriver.h
 *
 *  Created on: 3 de mar. de 2017
 *      Author: Lucas
 */

#ifndef MODULES_LEDDRIVER_H_
#define MODULES_LEDDRIVER_H_

void LedDriver_Create(uint16_t *address);

void LedDriver_Destroy(void);

void LedDriver_TurnOff_AllLeds();

void LedDriver_TurnON_AllLeds();

void LedDriver_TurnOff_ALed(uint8_t NLed);

void LedDriver_TurnON_ALed(uint8_t NLed);

void LedDriver_StateOfLed(uint16_t *address, uint8_t NLed);

uint8_t LedDriver_IsOn(uint8_t NLed);

uint8_t LedDriver_IsOff(uint8_t NLed);

#endif /* MODULES_LEDDRIVER_H_ */
