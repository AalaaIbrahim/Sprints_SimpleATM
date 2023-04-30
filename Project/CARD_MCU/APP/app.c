/*************************************************************************************************************
* 													Includes
************************************************************************************************************/

#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"
#include "../Common/STD_Types.h"
//#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/husart/husart.h"
#include "../ECUAL/hspi/hspi_interface.h"

#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
Uchar8_t arrStr[20];
VUchar8_t pan_arr[20];
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

/*
 * AUTHOR			: Sharpel
 * FUNCTION			: APP_terminalPanGet
 * DESCRIPTION		: Get pan from User within terminal and doing some validation
 * RETURN			: en_terminalPanGetStatus_t {PANGET_NOK or PANGET_OK}
 */
en_terminalPanGetStatus_t APP_terminalPanGet(Uchar8_t* arr)
{
	Uchar8_t loc_counter=0;
	HUSART_sendSTRING((Uchar8_t*)"\r\nEnter Card Pan : ");
	HUSART_receiveSTRING(arr,20);
	while(arr[loc_counter] != NULL)
	{
		if(arr[loc_counter] >= '0' && arr[loc_counter] <= '9')
		{
			loc_counter++;
		}
		else
		{
			HUSART_sendSTRING((Uchar8_t*) "\r\nInvalid Pan Number - must contain Numbers only");
			return PANGET_NOK;
		}
	}
	if(loc_counter<16)
	{
	 HUSART_sendSTRING((Uchar8_t*) "\r\nInvalid Pan Number - must contain at least 16 numbers");
	 return PANGET_NOK;
	}
	else HUSART_sendSTRING((Uchar8_t*)"\r\nCORRECT PAN");
	return PANGET_OK;
}
void APP_Init(void)
{
	(void)HUSART_enInit();


}


void APP_Start(void)
{
	//APP_terminalPanGet(pan_arr);
	//HUSART_sendSTRING(pan_arr);
}
