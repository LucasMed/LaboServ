/*
 * main.c
 *
 *  Created on: 3 de mar. de 2017
 *      Author: Lucas
 *
 *  Resumen: Prueba de Unit Test con Travis.
 */


#include "unity_fixture.h"

static void RunAllTest(void)
{
	RUN_TEST_GROUP(LedDriver);
}

int main(int argc, char *argv[])
{
	return UnityMain(argc, (const char*) argv, RunAllTest);
}
