/*
 * TestLedDriver.c
 *
 *  Created on: 3 de mar. de 2017
 *      Author: Lucas
 */


#include "unity_fixture.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver);
//Define file scope data accessible to test group members prior to TEST_SETUP.
static uint16_t virtualLeds;

TEST_SETUP(LedDriver)
{
	//initialization steps are executed before each TEST
	LedDriver_Create(&virtualLeds);
}
TEST_TEAR_DOWN(LedDriver)
{
	//clean up steps are executed after each TEST
}
//Each group has a TEST_GROUP_RUNNER
TEST_GROUP_RUNNER(LedDriver)
{
	//Each TEST has a corresponding RUN_TEST_CASE
	RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
	RUN_TEST_CASE(LedDriver, TurnOffAllLeds);
	RUN_TEST_CASE(LedDriver, TurnOnAllLeds);
	RUN_TEST_CASE(LedDriver, TurnOnALedOne);
	RUN_TEST_CASE(LedDriver, TurnOffALedOne);
	RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
	RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
	RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
	RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
	RUN_TEST_CASE(LedDriver, OutOfBoundsTurnOnDoesNoHarm);
	RUN_TEST_CASE(LedDriver, OutOfBoundsTurnOffDoesNoHarm);
	RUN_TEST_CASE(LedDriver, IsOn);
	RUN_TEST_CASE(LedDriver, OutOfBourdersLedsAreAlwaysOff);
	RUN_TEST_CASE(LedDriver, IsOff);
	RUN_TEST_CASE(LedDriver, TurnOffMultipleLeds);
	RUN_TEST_CASE(LedDriver, AllOff);
}
/*
	* A TEST contains:
	* TEST specific initializations
	* operations on the code under test
	* TEST specific condition checks
	*/
/*
 * TEST(nombre_del_grupo, nombre_del_test)
 */

/* Testear que todos los Leds esten en 0
 * cuando se Inicializa.
 * */
TEST(LedDriver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);

	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnALedOne)
{
	LedDriver_TurnON_ALed(1);

	TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffALedOne)
{
	LedDriver_TurnON_ALed(1);
	LedDriver_TurnOff_ALed(1);

	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{

	LedDriver_TurnON_ALed(9);
	LedDriver_TurnON_ALed(8);

	TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffMultipleLeds)
{
	LedDriver_TurnON_AllLeds();

	LedDriver_TurnOff_ALed(9);
	LedDriver_TurnOff_ALed(8);

	TEST_ASSERT_EQUAL_HEX16((~0x180) & 0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAllLeds)
{
	LedDriver_TurnOff_AllLeds();

	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds)
{
	LedDriver_TurnON_AllLeds();

	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnON_AllLeds();
	LedDriver_TurnOff_ALed(8);

	TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnON_ALed(8);

	TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_TurnON_ALed(1);
	LedDriver_TurnON_ALed(16);

	TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
	LedDriver_TurnON_ALed(-1);
	LedDriver_TurnON_ALed(0);
	LedDriver_TurnON_ALed(17);
	LedDriver_TurnON_ALed(255);

	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnON_AllLeds();

	LedDriver_TurnOff_ALed(-1);
	LedDriver_TurnOff_ALed(0);
	LedDriver_TurnOff_ALed(17);
	LedDriver_TurnOff_ALed(255);

	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, IsOn)
{
	TEST_ASSERT_FALSE(LedDriver_IsOn(11));
	LedDriver_TurnON_ALed(11);
	TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, IsOff)
{
	TEST_ASSERT_TRUE(LedDriver_IsOff(12));
	LedDriver_TurnON_ALed(12);
	TEST_ASSERT_FALSE(LedDriver_IsOff(12))
}

TEST(LedDriver, OutOfBourdersLedsAreAlwaysOff)
{
	TEST_ASSERT_TRUE(LedDriver_IsOff(0));
	TEST_ASSERT_TRUE(LedDriver_IsOff(17));
	TEST_ASSERT_FALSE(LedDriver_IsOn(0));
	TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

TEST(LedDriver, AllOff)
{
	LedDriver_TurnON_AllLeds();
	LedDriver_TurnOff_AllLeds();
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
