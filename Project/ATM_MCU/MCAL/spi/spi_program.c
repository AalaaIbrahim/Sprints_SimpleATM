/*
 * spi_program.c
 *
 * Created: 4/27/2023 3:54:39 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "../../Common/vect_table.h"

#include "../dio/dio_interface.h"

#include "spi_register.h"
#include "spi_private.h"
#include "spi_config.h"
#include "spi_interface.h"

/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
Uchar8_t u8_g_SlaveState = SPI_SLAVE_IDLE;

void (*SPI_CallbackFn)(void) = NULL;

/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
/**
 * \brief Initialize the MCU as the Master
 *		  in SPI communication
 *
 * \return void
 */
void SPI_MasterInit(void)
{
	/* Set MCU as Master */
	SET_BIT(SPCR, SPCR_MSTR);
		
	/* Configure Prescaler bits in SPCR and SPI2X bit in SPSR */
	SPCSR &= SPI_CLK_MASK;
	SPCSR |= SPI_CLK_SELECT;
			
	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}

/**
 * \brief Initialize the MCU as a slave
 *		  in SPI communication				
 * 
 * \return void
 */
void SPI_SlaveInit(void)
{
	/* Set MCU as Slave */
	CLEAR_BIT(SPCR, SPCR_MSTR);
	
	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}

/**
 * \brief Sets the value of the SPI data register
 * 
 * \param u8_a_data: Desired value
 * 
 * \return void
 */
void SPI_SetValue(Uchar8_t u8_a_data)
{
	SPDR = u8_a_data;
}

/**
 * \brief Exchange a letter with selected slave
 * 
 * \param u8_a_character Character to send
 * \param pu8_a_receivedChar Pointer to character to store received value
 * 
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_TranscieveChar(Uchar8_t u8_a_character, Uchar8_t* pu8_a_receivedChar)
{
	Uint32_t u32_l_timeCount = 0;
	
	if(pu8_a_receivedChar != NULL)
	{
		SPDR = u8_a_character;
		
		/* Wait until Interrupt flag is raised */
		while((GET_BIT(SPSR, SPSR_SPIF) == 0) && (u32_l_timeCount < SPI_TIMEOUT))
		{
			u32_l_timeCount ++;
		}
		
		if(SPI_TIMEOUT == u32_l_timeCount) {DIO_s8SETPinVal(DIO_PIND_4, HIGH);return SPI_NOK;}
		
		/* Store the received value */
		*pu8_a_receivedChar = SPDR;
		//DIO_s8SETPortVal(DIO_PORTA, *pu8_a_receivedChar);
	}
	else
	{
		return SPI_NOK;
	}
	
	return SPI_OK;
}

/**
 * \brief Set a notification function for the SPI Interrupt 
 * 
 * \param pv_a_CallbackFn reference to the function to callback
 *						  when the SPI Interrupt is triggered
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_SetCallback(void (*pv_a_CallbackFn)(void))
{
	if(pv_a_CallbackFn != NULL)
	{
		SPI_CallbackFn = pv_a_CallbackFn;
	}
	else
	{
		return SPI_NOK;
	}
	
	return SPI_OK;
}

/*************************************************************************************************************
 * 													  ISRs
 ************************************************************************************************************/
ISR(SPI_STC_INT)
{
	switch(u8_g_SlaveState)
	{
		case SPI_SLAVE_SEND_ARRAY:
		{
			break;
		}
	}
	if(SPI_CallbackFn != NULL)
	{
		SPI_CallbackFn();
	}	
}