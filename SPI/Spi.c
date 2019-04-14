/*
 * Spi.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-062
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Spi.h"

/*******************************************************************/
/* SPI0_Master_Init                                                */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that init SPI0 as master                                     */
/*******************************************************************/
void SPI0_Master_Init(void)
{
    // Enable the SSI0 peripheral
              //
              SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
              //
              // Wait for the SSI0 module to be ready.
              //
              while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
              {
              }
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
                //
                // Wait for the SSI0 module to be ready.
                //
                while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
                {
                }

        // Enable SPI0 functionality on GPIO Port A pins 2 to 4.
          //
          GPIOPinConfigure(GPIO_PA2_SSI0CLK);
          GPIOPinConfigure(GPIO_PA3_SSI0FSS);
          GPIOPinConfigure(GPIO_PA4_SSI0RX);
          GPIOPinConfigure(GPIO_PA5_SSI0TX);

          GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4| GPIO_PIN_5);

          //
          // Configure the SSI.
          //
          //SSIClockSourceSet(SSI0_BASE ,SSI_CLOCK_SYSTEM );
          SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
          SSI_MODE_MASTER, 2000000, 8);
          //
          // Enable the SSI module.
          //
          SSIEnable(SSI0_BASE);
}

/*******************************************************************/
/* SPI0_Send                                                       */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that send data on SPI0                                       */
/*******************************************************************/
void SPI0_Send(uint8_t data_to_send)
{
    SSIDataPut(SSI0_BASE, data_to_send);
}

/*******************************************************************/
/* SPI3_Recieve                                                    */
/* Parameters : N/A                                                */
/* I/p : N/A                                                       */
/* O/p : N/A                                                       */
/* Return : void                                                   */
/* fn that Recieve data on SPI3                                    */
/*******************************************************************/
uint32_t SPI3_Recieve(void)
{
    static uint32_t received_data ;
    if(SSIDataGetNonBlocking(SSI2_BASE, &received_data) != 0 )
    {
        return received_data ;
    }
    else
        return 0 ;
}


