/*
 * atm.h
 *
 * Created: 02/05/2023 19:03:44
 *  Author: 20101
 */ 


#ifndef ATM_H_
#define ATM_H_

#include <string.h>
#include "../Common/STD_Types.h"
#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/lcd/lcd_interface.h"
#include "../ECUAL/hspi/hspi_interface.h"
#include "../ECUAL/h_ext_int/h_ext_int.h"
#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/icu/sw_icu.h"

#define		ATM_REQUEST_PIN		'P'
#define		ATM_REQUEST_PAN		'G'

typedef enum
{
	PIN_MATCHED,
	PIN_NOT_MATCHED,
	NULL_POINTER,
	PIN_OK,
	PIN_NOT_OK
}EN_PinState;

typedef enum
{
	ZERO = 0,
	ENTER,
	NOTHING

}en_buttonStatus;

void Welcome(void);
EN_PinState PIN_checkPinMatching(Uchar8_t *pinFromAtm,Uchar8_t *pinFromServer);
EN_PinState Get_pin(Uchar8_t *enteredpin);
en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer);
en_buttonStatus Button_enStatus(void);
EN_PinState ATM_ValidatePIN(void);
void get_amount_left (Uchar8_t * amount);


#endif /* ATM_H_ */