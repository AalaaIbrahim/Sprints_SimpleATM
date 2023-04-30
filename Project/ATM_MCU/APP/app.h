
#ifndef APP_H_
#define APP_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/


/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef enum
{
	ZERO = 0,
	ENTER

}en_buttonStatus;



/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: timer_ovfCount
 * DESCRIPTION		: Countiong OVF times
 * RETURN			: void
 */
void timer_ovfCount(void);
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: Button_enStatus
 * DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
 * RETURN			: en_buttonStatus {ZERO or ENTER}
 */
en_buttonStatus Button_enStatus(void);





void APP_Init(void);
void APP_Start(void);
 

#endif /* APP_H_ */
