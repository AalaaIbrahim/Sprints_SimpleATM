/*
 * terminal_process.c
 *
 * Created: 02/05/2023 19:50:35
 *  Author: 20101
 */ 

#include "terminal_process.h"

EN_TerminalDataState SaveCardData(Sint16_t *CardPan,Schar8_t *CardPin)
{
	EN_TerminalDataState ret = DATA_NSAVED;
	
	if(CardPan == NULL || CardPin == NULL)
	{
		ret = DATA_NSAVED;
	}
	else
	{
		eeprom_write_string(0x0000,CardPan);
		eeprom_write_string(0x0020,CardPin);
		ret = DATA_SAVED;
	}
	
	return ret;
}

EN_TerminalDataState ReadCardData(Sint16_t *CardPan,Schar8_t *CardPin)
{
		EN_TerminalDataState ret = DATA_NREAD;
		
		if(CardPan == NULL || CardPin == NULL)
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