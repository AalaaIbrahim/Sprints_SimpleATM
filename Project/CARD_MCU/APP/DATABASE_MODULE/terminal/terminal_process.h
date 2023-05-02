/*
 * terminal_process.h
 *
 * Created: 02/05/2023 19:51:04
 *  Author: 20101
 */ 


#ifndef TERMINAL_PROCESS_H_
#define TERMINAL_PROCESS_H_

#include "../../../Common/STD_Types.h"
#include "../../../ECUAL/eeprom/HEEPROM_Interface.h"

typedef enum
{
	DATA_SAVED,
	DATA_NSAVED,
	DATA_READ,
	DATA_NREAD	
}EN_TerminalDataState;


EN_TerminalDataState SaveCardData(Sint16_t *CardPan,Schar8_t *CardPin);

EN_TerminalDataState ReadCardData(Sint16_t *CardPan,Schar8_t *CardPin);


#endif /* TERMINAL_PROCESS_H_ */