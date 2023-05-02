/*
 * atm.c
 *
 * Created: 02/05/2023 19:03:32
 *  Author: 20101
 */ 


#include "atm.h"
VUchar8_t  ATMpin[5] = "";
VUchar8_t ZeroFlag = 0;
VUchar8_t setFlag = 0;
extern VUchar8_t keys_arr [10];
VUchar8_t Entered_amount [] = "0000.00";

EN_PinState Get_pin(Uchar8_t *enteredpin)
{
	Uchar8_t colPos=0;
	HLCD_gotoXY(0,0);
	HLCD_WriteString("Enter Your pin");
	Uchar8_t BTN,loc_counter=0;
	while (loc_counter < 4 && !setFlag)
	{
		
		BTN = KEYPAD_GetButton();
		if(BTN == KEY_NOTHING)continue;
		else if(ZeroFlag == 1 )
		{
			HLCD_gotoXY(1,colPos++);
			HLCD_vidWriteChar('*');
			enteredpin[loc_counter] = 0;
			ZeroFlag = 0;
			loc_counter++;
			
		}
		else
		{
			HLCD_gotoXY(1,colPos++);
			HLCD_vidWriteChar('*');
			enteredpin[loc_counter] = keys_arr[BTN-1];
			loc_counter++;
		}
		
		
	}
	if(loc_counter<4)
	{
		return PIN_NOT_OK;
	}
	else {
		return PIN_OK;
	    }
}
EN_PinState PIN_checkPinMatching(Schar8_t *pinFromAtm,Schar8_t *pinFromServer)
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
		}
		else
		{
			ret = PIN_NOT_MATCHED;
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