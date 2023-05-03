/*
 * terminal_process.c
 *
 * Created: 02/05/2023 19:50:35
 *  Author: 20101
 */ 

#include "card_database.h"


Uchar8_t pin_arr[20];
Uchar8_t pan_arr[20];

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
	HUSART_receiveSTRING(arr, 5);
	while(arr[counter] != null)
	{
		if(arr[counter] >= '0' && arr[counter] <= '9')
		{
			counter++;
		}
		else
		{
			HUSART_sendSTRING( (Uchar8_t*) "\rNot numeric ");
			flag = 1;
			errorStatus = PINGET_NOK;
			break;
		}
	}
	if(counter < 4 && flag == 0)
	{
		HUSART_sendSTRING( (Uchar8_t*) "\rbelow 4 dig ");
		errorStatus = PINGET_NOK;
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
	HUSART_sendSTRING((Uchar8_t*)"\r\nEnter Card Pan : \r");
	HUSART_receiveSTRING(arr,20);
	while(arr[loc_counter] != null)
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
	return PANGET_OK;
}


EN_TerminalDataState SaveCardData(Uchar8_t *CardPan,Uchar8_t *CardPin)
{
	EN_TerminalDataState ret = DATA_NSAVED;
	
	if(CardPan == null || CardPin == null)
	{
		ret = DATA_NSAVED;
	}
	else
	{
		_delay_ms(200);
		eeprom_write_string(0x0000,CardPan);
		_delay_ms(200);
		eeprom_write_string(0x0020,CardPin);
		_delay_ms(200);
		eeprom_write_string(0x0050, (Uchar8_t*)"1");
		_delay_ms(200);
		ret = DATA_SAVED;
	}
	
	return ret;
}

EN_TerminalDataState ReadCardData(Uchar8_t *CardPan,Uchar8_t *CardPin)
{
		EN_TerminalDataState ret = DATA_NREAD;
		
		if(CardPan == null || CardPin == null)
		{
			ret = DATA_NREAD;
		}
		else
		{
			eeprom_read_string(0x0000,CardPan);
			eeprom_read_string(0x0020,CardPin);
			ret = DATA_READ;
		}
		return ret;
}

en_CardPinMatchError_t CARD_MatchPINs()
{
	Uchar8_t PIN_Confirm[10], u8_l_PINiterator;
	Uchar8_t u8_l_ValidatePIN, u8_l_ValidateConfirmPIN;
	
	/* Get PIN from user */
	HUSART_sendSTRING( (Uchar8_t*) "\rEnter your PIN : ");
	u8_l_ValidatePIN = APP_terminalPinGet(pin_arr);
	
	/* Get PIN again for Confirmation */
	HUSART_sendSTRING((Uchar8_t *)"\rConfirm Your PIN : ");
	u8_l_ValidateConfirmPIN = APP_terminalPinGet(PIN_Confirm);
	
	if((PINGET_OK == u8_l_ValidatePIN) && (PINGET_OK == u8_l_ValidateConfirmPIN))
	{
		/* Check if the user entered same PIN both times */
		for(u8_l_PINiterator=0; u8_l_PINiterator<PIN_LENGTH; u8_l_PINiterator++)
		{
			if(pin_arr[u8_l_PINiterator] != PIN_Confirm[u8_l_PINiterator])
			{
				HUSART_sendSTRING((Uchar8_t *)"\rPin Not Matched");
				return PIN_Match_NOK;
			}
		}
		
		HUSART_sendSTRING((Uchar8_t *)"\rPin Matched");
		return PIN_Match_OK;
	}
	
	return PIN_Match_NOK;
}



void CARD_SendTrigger(void)
{
	//ReadCardData();
}