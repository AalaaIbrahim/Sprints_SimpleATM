
#ifndef APP_H_
#define APP_H_

#include "../Common/STD_Types.h"
/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/


/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/

typedef enum
{
	PINGET_NOK = 0,
	PINGET_OK

}en_terminalPinGetStatus_t;

typedef enum
{
	PANGET_NOK = 0,
	PANGET_OK

}en_terminalPanGetStatus_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: APP_terminalPinGet
 * DESCRIPTION		: Get pin from User within terminal and doing some validation
 * RETURN			: en_terminalPinGetStatus_t {PINGET_NOK or PINGET_OK}
 */
en_terminalPinGetStatus_t APP_terminalPinGet(Uchar8_t* arr);

/*
 * AUTHOR			: Sharpel
 * FUNCTION			: APP_terminalPanGet
 * DESCRIPTION		: Get pan from User within terminal and doing some validation
 * RETURN			: en_terminalPanGetStatus_t {PANGET_NOK or PANGET_OK}
 */
en_terminalPanGetStatus_t APP_terminalPanGet(Uchar8_t* arr);

void APP_Init(void);
void APP_Start(void);
 

#endif /* APP_H_ */
