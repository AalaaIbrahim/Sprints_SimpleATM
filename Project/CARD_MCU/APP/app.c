/*************************************************************************************************************
* 													Includes
************************************************************************************************************/

#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"
#include "../Common/STD_Types.h"
//#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/husart/husart.h"
#include "../ECUAL/hspi/hspi_interface.h"
#include "../ECUAL/eeprom/HEEPROM_Interface.h"

#include "../card_database/card_database.h"
#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
extern Uchar8_t pin_arr[20];
extern Uchar8_t pan_arr[20];

Uchar8_t u8_g_EepromFlag, u8_g_CardState, u8_g_PanValid;
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

void APP_Init(void)
{
	(void)HUSART_enInit();
}


void APP_Start(void)
{
	// 	APP_terminalPanGet(pan_arr);
	// 	HUSART_sendSTRING(pan_arr);
	
	switch(u8_g_CardState)
	{
		case CardGetMode:
		{
			u8_g_EepromFlag = eeprom_read_byte(0x0050);
			if(u8_g_EepromFlag != 0xFF) u8_g_CardState = CardProgMode_GetPan;
			else u8_g_CardState = CardUserMode;
			break;
		}
		case CardProgMode_GetPan:
		{
			u8_g_PanValid = APP_terminalPanGet(pan_arr);
			HUSART_sendSTRING(pan_arr);
			
			if(PANGET_OK == u8_g_PanValid) u8_g_CardState = CardProgMode_GetPin;
			
			break;
		}
		case CardProgMode_GetPin:
		{
			if(CARD_MatchPINs() == PIN_Match_OK) u8_g_CardState = CardUserMode;
			else u8_g_CardState = CardProgMode_GetPin;
			break;
		}
		case CardUserMode:
		{
			/* Get PIN from EEPROM to prepare data in SPI buffer (?)*/
			
			/* Trigger ATM */
			HSPI_SlaveRequest(pin_arr, PIN_LENGTH);
			break;
		}
	}
	
}
