/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
//#include "../Common/STD_Types.h"
//#include "../Common/BIT_Math.h"
//#include "../Common/vect_table.h"

//#include "../ECUAL/htimer0/htimer0.h"
//#include "../ECUAL/HTimer/HTimer.h"
// #include "../ECUAL/button/button.h"
//#include "../ECUAL/keypad/keypad.h"
// #include "../ECUAL/lcd/lcd_interface.h"
// 
// #include "../ECUAL/hspi/hspi_interface.h"
// 
#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
Uchar8_t global_u8OVFCounter = 0;
// Uchar8_t buttonPressed;
// en_buttonStatus myState;
// 
// Uchar8_t  ATMpin[4] = {NULL};
extern VUchar8_t  ATMpin[5] ;
extern VUchar8_t ZeroFlag;
extern VUchar8_t setFlag;

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

// /*
//  * AUTHOR			: Bassel Yasser Mahmoud
//  * FUNCTION			: Button_enStatus
//  * DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
//  * RETURN			: en_buttonStatus {ZERO or ENTER}
//  */
// en_buttonStatus Button_enStatus(void)
// {
// 	en_buttonStatus local_buttonState;
// 	HButton_getPinVal(DIO_PIND_5, &buttonPressed);
// 
// 	if (!buttonPressed)
// 	{
// 		(void)HTimer_vidDelayMs(100);
// 		while (!buttonPressed)
// 		{
// 			HButton_getPinVal(DIO_PIND_5, &buttonPressed);
// 		}
// 	}
// 	(void)HTimer_enStop();
// 
// 	if (global_u8OVFCounter < 20 && global_u8OVFCounter > 0)
// 	{
// 		local_buttonState = ZERO;
// 		ZeroFlag = 1;
// 	}
// 	else if(global_u8OVFCounter >= 20)
// 	{
// 		local_buttonState = ENTER;
// 	}
// 
// 	return local_buttonState;
// }
// 
// 
// 
 
// 
// 
// /**
//  * \brief Function to implement logic after approved transaction
//  * 
//  * \param f32_a_NewBalance: balance after transaction which will be
//  *							displayed on LCD
//  * \return void
//  */
// void ATM_ApprovedCard(/* Get account data and transaction or just balance after transaction */float32_t f32_a_NewBalance)
// {
// 	HLCD_gotoXY(0, 4);
// 	HLCD_WriteString("Approved");
// 	HLCD_gotoXY(1, 2);
// 	HLCD_WriteString("Transaction");
// 	
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// 	
// 	/* Todo: remaining balance */
// 	HLCD_gotoXY(0, 4);
// 	HLCD_WriteString("Remaining");
// 	HLCD_gotoXY(1, 0);
// 	HLCD_WriteString("Balance  ");
// 	HLCD_DisplayFloat(f32_a_NewBalance);
// 	
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// 	
// 	HLCD_gotoXY(0, 1);
// 	HLCD_WriteString("Ejecting Card");
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// }
// 
// 
// /**
//  * \brief Function to get the card pin from the card MCU
//  * 
//  * \param pu8_a_CardPIN: reference to character array to
//  *						 store the PIN
//  * \return void
//  */
// void ATM_GetCardPIN(Uchar8_t *pu8_a_CardPIN)
// {
// 	/* Receive PIN from Card */
// 	HSPI_ReceiveData(pu8_a_CardPIN, PIN_LENGTH);
// }
// 
 void APP_Init(void)
 {
 
 	//(void)HButton_Init(DIO_PINB_2);
 	(void)KEYPAD_init();
 	//(void)HTimer_enInit();
 	//(void)HTimer_enCBF(timer_ovfCount);
 	(void)HLCD_vidInit();
 	//(void)HSPI_MasterInit();
 
 
 }
// 
// 
 void APP_Start(void)
 {
 	//myState = Button_enStatus();
 	//if(myState == ZERO)
 	//{
 		//global_u8OVFCounter = 0;
 //
 		///*TODO*/
 //
 	//}
 	//else if(myState == ENTER)
 	//{
 		//global_u8OVFCounter = 0;
 //
 		///*TODO*/
 //
 	//}
	 
	 Get_pin(ATMpin);
 	
 }
