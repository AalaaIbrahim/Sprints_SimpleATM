/*
 * pin.c
 *
 * Created: 02/05/2023 19:03:32
 *  Author: 20101
 */ 

#include "pin.h"


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


en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer)
{
	en_BuzzerErrorState_t ret = BUZ_NOK;
	
	ret = BUZ_SetState(pst_a_buzzer,BUZ_ON);
	
	return ret;
}