/*
* atm.c
*
* Created: 02/05/2023 19:03:32
*  Author: 20101
*/

#include "atm.h"
#include <util/delay.h>

Uchar8_t buttonPressed;
en_buttonStatus myState;

Uchar8_t  ATMpin[5] = "";
Uchar8_t  CARDpin[8], CARDpan[20];
extern Uchar8_t keys_arr [10];
extern Uchar8_t global_u8OVFCounter;
Uchar8_t Entered_amount [8] = "0000.00";
extern Uchar8_t EnterCheck;
extern Uchar8_t ZeroCheck;

void Welcome(void)
{
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((Uchar8_t *)"Welcome To Atm");
	HTIM0_SyncDelay(1,Seconds);
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((Uchar8_t *)"Insert Your Card");
}


EN_PinState Get_pin(Uchar8_t *enteredpin)
{
	Uchar8_t colPos=0;
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString("Enter Your pin");
	Uchar8_t BTN,loc_counter=0;
	HLCD_gotoXY(1,colPos);
	while (loc_counter < 4 && EnterCheck == 0)
	{
		//myState = Button_enStatus();
		BTN = KEYPAD_GetButton();
		if(BTN == KEY_NOTHING)
		{
			if(ZeroCheck == 1)
			{
				ZeroCheck = 0;
				enteredpin[loc_counter] = '0';
				//HLCD_gotoXY(1,colPos++);
				HLCD_vidWriteChar('0');
				loc_counter++;
			}
			continue;
		}
		else if(BTN)
		{
			if(EnterCheck == 0 && ZeroCheck == 0)
			{
				enteredpin[loc_counter] = keys_arr[BTN-1];
				HLCD_vidWriteChar(enteredpin[loc_counter]);
				loc_counter++;
			}
			else if(EnterCheck == 1)
			{
				break;
			}
		}
		
	}
	EnterCheck = 0;
	if(loc_counter<4)
	{
		HLCD_ClrDisplay();
		HLCD_gotoXY(1,0);
		HLCD_WriteString("ERROR");
		_delay_ms(1000);
		return PIN_NOT_OK;
	}
	else
	{
		return PIN_OK;
	}
}


// EN_PinState Get_pin(Uchar8_t *enteredpin)
// {
// 	Uchar8_t colPos=0;
// 	HLCD_ClrDisplay();
// 	HLCD_gotoXY(0,0);
// 	HLCD_WriteString("Enter Your pin");
// 	Uchar8_t BTN,loc_counter=0;
// 	
// 	while (loc_counter < 4)
// 	{
// 		//myState = Button_enStatus();
// 		BTN = KEYPAD_GetButton();
// 		if(BTN == KEY_NOTHING)continue;
// 		else if(BTN)
// 		{
// 			HLCD_gotoXY(1,colPos++);
// 			enteredpin[loc_counter] = keys_arr[BTN-1];
// 			HLCD_vidWriteChar(enteredpin[loc_counter]);
// 			loc_counter++;
// 		}
// 		
// 		
// 	}
// 	if(loc_counter<4)
// 	{
// 		HLCD_ClrDisplay();
// 		HLCD_gotoXY(1,0);
// 		HLCD_WriteString("ERROR");
// 		return PIN_NOT_OK;
// 	}
// 	else {
// 		return PIN_OK;
// 	}
//

EN_PinState PIN_checkPinMatching(Uchar8_t *pinFromAtm,Uchar8_t *pinFromServer)
{
	EN_PinState ret = PIN_NOT_MATCHED;
	if(pinFromAtm == NULL || pinFromServer == NULL)
	{
		ret = NULL_POINTER;
	}
	else
	{
		if(!strcmp(pinFromAtm,pinFromServer))
		{
			ret = PIN_MATCHED;
			HLCD_ClrDisplay();
			HLCD_WriteString("PIN_MATCHED");
			_delay_ms(5000);
		}
		else
		{
			ret = PIN_NOT_MATCHED;
			HLCD_ClrDisplay();
			HLCD_WriteString("PIN_NOT_MATCHED");
			_delay_ms(5000);
		}
	}
	return ret;
}

void get_amount_left (Uchar8_t * amount)
{
	
	HLCD_gotoXY(0,0);
	HLCD_WriteString("ENTER amount");
	HLCD_gotoXY(1,0);
	HLCD_WriteString(amount);
	Uchar8_t BTN ,loc_counter=0,i=0;
	while(loc_counter<6)
	{
		BTN = KEYPAD_GetButton();
		if(!BTN)continue;
		else
		{
			for(i=0;i<6;i++)
			{
				if(i==3)
				{
					amount[i]=amount[i+2];
					HLCD_gotoXY(1,i);
					HLCD_vidWriteChar(amount[i]);
					i=5;
				};
				amount[i]=amount[i+1];
				HLCD_gotoXY(1,i);
				HLCD_vidWriteChar(amount[i]);
			}
			amount[6] = keys_arr[BTN-1];
			HLCD_gotoXY(1,6);
			HLCD_vidWriteChar(amount[6]);
			
		}
		loc_counter++;
		
	}
	
	
}
void get_amount (Uchar8_t * amount)
{
	
	HLCD_gotoXY(0,0);
	HLCD_WriteString("ENTER amount");
	HLCD_gotoXY(1,0);
	HLCD_WriteString(amount);
	Uchar8_t BTN ,loc_counter =0;
	while(loc_counter<7)
	{
		BTN = KEYPAD_GetButton();
		if(!BTN)continue;
		else
		{
			if(amount[loc_counter]=='.')loc_counter+=1;
			amount[loc_counter]=keys_arr[BTN-1];
			HLCD_gotoXY(1,loc_counter);
			HLCD_vidWriteChar(amount[loc_counter]);
			loc_counter ++ ;
			
		}
	}
}



en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer)
{
	en_BuzzerErrorState_t ret = BUZ_NOK;
	
	ret = BUZ_SetState(pst_a_buzzer,BUZ_ON);
	
	return ret;
}


Uchar8_t u8_g_ReceivePIN = 0;
EN_PinState u8_g_MatchPIN;
Uchar8_t arr_g_CardPIN[5];
Uchar8_t arr_g_CardPAN[20];

void Card_Trigger(void)
{
	u8_g_ReceivePIN = 1;
}

EN_PinState ATM_ValidatePIN(void)
{
	EN_PinState u8_l_MatchPIN;
	
	/* Request PIN From Card */
	HSPI_SendChar(ATM_REQUEST_PIN);
	_delay_ms(5);
	HSPI_ReceiveData(CARDpin, 5);
	//HLCD_ClrDisplay();
	//HLCD_WriteString("Received ");
	//HLCD_WriteString(CARDpin);
	//_delay_ms(3000);
	
	/* Request PIN From Card */
	HSPI_SendChar(ATM_REQUEST_PAN);
	_delay_ms(5);
	HSPI_ReceiveData(CARDpan, 20);
	//HLCD_ClrDisplay();
	//HLCD_WriteString("Received ");
	//HLCD_gotoXY(1,0);
	//HLCD_WriteString(CARDpan);
	//_delay_ms(10000);
	
	u8_l_MatchPIN = PIN_checkPinMatching(CARDpin, ATMpin);
	
	return u8_l_MatchPIN;
}


/*
* AUTHOR			: Bassel Yasser Mahmoud
* FUNCTION			: Button_enStatus
* DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
* RETURN			: en_buttonStatus {ZERO or ENTER}
*/
en_buttonStatus Button_enStatus(void)
{
	en_buttonStatus local_buttonState = NOTHING;
	HButton_getPinVal(DIO_PIND_5, &buttonPressed);

	if (!buttonPressed)
	{
		(void)HTimer_vidDelayMs(100);
		while (!buttonPressed)
		{
			HButton_getPinVal(DIO_PIND_5, &buttonPressed);
		}
	}
	
	(void)HTimer_enStop();

	if (global_u8OVFCounter < 20 && global_u8OVFCounter > 0)
	{
		local_buttonState = ZERO;
	}
	else if(global_u8OVFCounter >= 20)
	{
		local_buttonState = ENTER;
	}
	
	return local_buttonState;
}