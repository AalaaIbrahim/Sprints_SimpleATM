/*
 * pin.h
 *
 * Created: 02/05/2023 19:03:44
 *  Author: 20101
 */ 


#ifndef PIN_H_
#define PIN_H_

#include <string.h>
#include "../../Common/STD_Types.h"
#include "../../ECUAL/buzzer/buzzer.h"


typedef enum
{
	PIN_MATCHED,
	PIN_NOT_MATCHED,
	NULL_POINTER
}EN_PinState;


EN_PinState PIN_checkPinMatching(Schar8_t *pinFromAtm,Schar8_t *pinFromServer);

en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer);



#endif /* PIN_H_ */