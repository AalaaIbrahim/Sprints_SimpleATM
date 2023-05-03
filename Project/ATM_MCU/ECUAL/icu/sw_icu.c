/*
 * sw_icu.c
 *
 * Created: 5/2/2023 2:02:01 PM
 *  Author: ME
 */ 

#include "../../Common/STD_Types.h"

#include "../../MCAL/timer1/tim1_interface.h"
#include "../../MCAL/extint/extinterrupt.h"


Uint16_t u16_g_TimerValue;
void SwICU_Init(void)
{
	/* Set extint to be triggered on rising edge at first (button is pulled down) */
	EXTINT_init(EXTINT2, RISING_EDGE);
	
	EXTINT_CallBack(EXTINT2, EXTI2_RisingEdgeNotification);
}

Uint16_t SwICU_GetTime(void)
{
	Uint16_t u16_l_msTime, u;
	float32_t f32_l_TickTime;
	
	f32_l_TickTime = TIM1_GetTickTime();
	u16_l_msTime = (Uint16_t)(f32_l_TickTime * TIM1_GetValue());

	return u16_l_msTime;
}
void EXTI2_RisingEdgeNotification(void)
{
	/* Start Timer */
	TIM1_Start(TIM1_CLK_DIV_BY_1024);

	/* Set the interrupt to be triggered on a rising edge */
	EXTINT_CallBack(EXTINT2, EXTI2_RisingEdgeNotification);
}

void EXTI2_FallingEdgeNotification(void)
{
	/* Get timer value */
	u16_g_TimerValue = SwICU_GetTime();

	/* Stop the timer */
	TIM1_Stop();

	/* Check Enter or Zero */
	
}



