/* LedDriver.c
 *
 *  Created on: 3 de mar. de 2017
 *      Author: Lucas
 */

/** \brief Main example source file
 **
 ** This is a mini example of the Led Driver.
 **
 **/

/** \addtogroup
 ** @{ */
/** \addtogroup
 ** @{ */
/** \addtogroup Main example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * LJM          Lucas Medina
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 2017-02-03   v 0.0.1   First version
 */

/*==================[inclusions]=============================================*/
#include <stdint-gcc.h>
#include "LedDriver.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
/* Variables propias del LedDriver */
static uint16_t * ledsAddress;
static uint16_t ledsImage;

/*==================[internal data definition]===============================*/
enum {
	ALL_LEDS_ON = ~0,
	ALL_LEDS_OFF = ~ALL_LEDS_ON
};
enum {
	FIRST_LED = 1,
	LAST_END = 16
};
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/* Funciones propias del LedDriver */
static uint16_t convertLedNumberToBit(uint8_t NLed);
static void updateHardware(void);
static uint8_t IsLedOutOfBounds(uint8_t NLed);
static void setLedImageBit(uint8_t NLed);
static void clearLedImageBit(uint8_t NLed);
/*==================[external functions definition]==========================*/

/* Almacena la direccion de memoria donde estan los Leds
 *
 * */
void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}
void LedDriver_Destroy(void)
{

}
/*	Pone en 0 todos los Leds
 *
 * */
void LedDriver_TurnOff_AllLeds()
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}
/*	Pone en uno todos los Leds
 *
 * */
void LedDriver_TurnON_AllLeds()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}
/*	Apaga de a un Led pasandole el numero de Led.
 *
 * */
void LedDriver_TurnOff_ALed(uint8_t NLed)
{
	if (IsLedOutOfBounds(NLed))
	{
		return;
	}
	clearLedImageBit(NLed);
	updateHardware();
	return;
}
/*	Prende de a un Led pasandole el numero de Led.
 *
 * */
void LedDriver_TurnON_ALed(uint8_t NLed)
{
	if (IsLedOutOfBounds(NLed))
	{
		return;
	}
	setLedImageBit(NLed);
	updateHardware();
	return;
}
/*	Verifica el estado del Led.
 *
 * */
void LedDriver_StateOfLed(uint16_t *address, uint8_t NLed)
{

}
/*	Funcion que se utiliza para convertir un numero entero a bit.
 *
 * */
static uint16_t convertLedNumberToBit(uint8_t NLed)
{
	return 1 << (NLed - 1);
}

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

static uint8_t IsLedOutOfBounds(uint8_t NLed)
{
	return (NLed < FIRST_LED) || (NLed > LAST_END);
}

static void setLedImageBit(uint8_t NLed)
{
	ledsImage |= convertLedNumberToBit(NLed);
}

static void clearLedImageBit(uint8_t NLed)
{
	ledsImage &= ~convertLedNumberToBit(NLed);
}

uint8_t LedDriver_IsOn(uint8_t NLed)
{
	if(IsLedOutOfBounds(NLed))
	{
		return 1;
	}
	return ledsImage & (convertLedNumberToBit(NLed));
}

uint8_t LedDriver_IsOff(uint8_t NLed)
{
	return LedDriver_IsOn(NLed);
}
