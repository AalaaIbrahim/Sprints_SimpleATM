/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../Common/STD_Types.h"
#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"

#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/HTimer/HTimer.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/lcd/lcd_interface.h"

#include "../ECUAL/hspi/hspi_interface.h"

#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
Uchar8_t global_u8OVFCounter = 0;
Uchar8_t buttonPressed;
en_buttonStatus myState;

/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: timer_ovfCount
 * DESCRIPTION		: Countiong OVF times
 * RETURN			: void
 */

void timer_ovfCount(void)
{
	global_u8OVFCounter++;

}

/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: Button_enStatus
 * DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
 * RETURN			: en_buttonStatus {ZERO or ENTER}
 */
en_buttonStatus Button_enStatus(void)
{
	en_buttonStatus local_buttonState;
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




void APP_Init(void)
{

	(void)HButton_Init(DIO_PINB_2);
	(void)HTimer_enInit();
	(void)HTimer_enCBF(timer_ovfCount);


}


void APP_Start(void)
{
	myState = Button_enStatus();
	if(myState == ZERO)
	{
		global_u8OVFCounter = 0;

		/*TODO*/

	}
	else if(myState == ENTER)
	{
		global_u8OVFCounter = 0;

		/*TODO*/

	}
	


}
