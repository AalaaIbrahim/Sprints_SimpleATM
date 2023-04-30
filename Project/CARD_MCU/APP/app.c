/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../Common/STD_Types.h"
#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"

//#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/husart/husart.h"
#include "../ECUAL/hspi/hspi_interface.h"

#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
Uchar8_t arrStr[20];
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: APP_terminalPinGet
 * DESCRIPTION		: Get pin from User within terminal and doing some validation
 * RETURN			: en_terminalPinGetStatus_t {PINGET_NOK or PINGET_OK}
 */
en_terminalPinGetStatus_t APP_terminalPinGet(Uchar8_t* arr)
{
	en_terminalPinGetStatus_t errorStatus = PINGET_OK;

	Uchar8_t counter = 0, flag = 0;
	HUSART_sendSTRING( (Uchar8_t*) "Enter your PIN: ");
	HUSART_receiveSTRING(arr, 6);
	while(arrStr[counter] != NULL)
	{
		if(arr[counter] >= '0' && arr[counter] <= '9')
		{
			counter++;
		}
		else
		{
			HUSART_sendSTRING( (Uchar8_t*) "Not numeric ");
			flag = 1;
			errorStatus = PINGET_NOK;
			break;
		}
	}
	if(counter <4 && flag == 0)
	{
		HUSART_sendSTRING( (Uchar8_t*) "below 4 dig ");
		errorStatus = PINGET_NOK;
	}
	else if(flag == 0)
	{
		HUSART_sendSTRING( (Uchar8_t*) "Succeed ");
	}
	return errorStatus;
}



void APP_Init(void)
{
	(void)HUSART_enInit();


}


void APP_Start(void)
{
	
}
