/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
//#include <util/delay.h>
#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/


extern Uchar8_t  ATMpin[5] ;
extern Uchar8_t  CARDpin[4] ;
Uchar8_t global_u8OVFCounter = 0;

extern VUchar8_t keys_arr [10];

EN_TriggerState TriggerState = N_TRIGGER; 

Uchar8_t welcomeFlag = 0;

/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/


void TriggerCallBack(void)
{
	TriggerState = TRIGGER;
}


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
void APP_Init(void)
{
	
	//(void)HButton_Init(DIO_PINB_2);
	(void)KEYPAD_init();
	(void)HTimer_enInit();
	(void)HTimer_enCBF(timer_ovfCount);
	(void)HLCD_vidInit();
	(void)HSPI_MasterInit();
	(void)H_EXTINT_create(EXTINT0, ANY_LOGICAL_CHANGE,TriggerCallBack);
	(void)SwICU_Init();
}


void APP_Start(void)
{
			
	switch(TriggerState)
	{
		case TRIGGER:
		{
			Get_pin(ATMpin);
			welcomeFlag = 0;
			//PIN_checkPinMatching(ATMpin, CARDpin);
			if(ATM_ValidatePIN() == PIN_MATCHED)
			{
				
			}
			else
			{
				/* Lock system if max tries exceeded */
				/* Break to restart the state to try again */
			}
			//_delay_ms(1000);
			//TriggerState = N_TRIGGER;
			break;
		}
		case N_TRIGGER:
		{
			if(welcomeFlag == 0)
			{
				Welcome();
				welcomeFlag = 1;
			}
			break;
		}	
	
	}
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
}




















/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: timer_ovfCount
 * DESCRIPTION		: Countiong OVF times
 * RETURN			: void
 */

//void timer_ovfCount(void)
//{
	//global_u8OVFCounter++;
//
//}


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


