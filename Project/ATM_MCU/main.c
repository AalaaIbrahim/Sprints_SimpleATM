/*
 * ATM_MCU.c
 *
 * Created: 4/29/2023 5:30:30 AM
 * Author : ME
 */ 
#include "APP/app.h"

void main(void)
{
	APP_Init();

    while (1) 
    {
		APP_Start();
    }
}

