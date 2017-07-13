/*
 * uart_radio_sim.c
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
 * 
 * This file is part of FloripaSat-Beacon.
 * 
 * FloripaSat-Beacon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-Beacon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-Beacon. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file uart_radio_sim.c
 * 
 * \brief UART Radio Simulation driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 11/06/2017
 * 
 * \addtogroup uart_radio_sim
 * \{
 */

#include <libs/driverlib/driverlib.h>

#include "uart_radio_sim.h"

uint8_t uart_radio_sim_init()
{
    // UART pins init.
    GPIO_setAsPeripheralModuleFunctionInputPin(UART_RADIO_SIM_UART_TX_PORT, RADIO_SIM_UART_TX_PIN);
    
    // Config UART (115200 bps, no parity, 1 stop bit, LSB first)
    USCI_A_UART_initParam uart_params = {0};
    uart_params.selectClockSource   = USCI_A_UART_CLOCKSOURCE_SMCLK;
    uart_params.clockPrescalar      = 52;		// Clock = 1 MHz, Baudrate = 1200 bps ([1] http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html)
    uart_params.firstModReg         = 1;		// Clock = 1 MHz, Baudrate = 1200 bps (See [1])
    uart_params.secondModReg        = 0;		// Clock = 1 MHz, Baudrate = 1200 bps (See [1])
    uart_params.parity              = USCI_A_UART_NO_PARITY;
    uart_params.msborLsbFirst       = USCI_A_UART_LSB_FIRST;
    uart_params.numberofStopBits    = USCI_A_UART_ONE_STOP_BIT;
    uart_params.uartMode            = USCI_A_UART_MODE;
    uart_params.overSampling        = USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;    // Clock = 1 MHz, Baudrate = 1200 bps (See [1])
    
    // UART initialization
    if (USCI_A_UART_init(UART_RADIO_SIM_UART_BASE_ADDRESS, &uart_params) == STATUS_SUCCESS)
    {
        // Enable UART module
        USCI_A_UART_enable(UART_RADIO_SIM_UART_BASE_ADDRESS);

        return STATUS_SUCCESS;
    }
    else
    {
        return STATUS_FAIL;
    }
}

void uart_radio_sim_send_data(uint8_t *data, uint16_t size)
{
    uint8_t i = 0;
    for(i=0;i<size;i++)
    {
        USCI_A_UART_transmitData(UART_RADIO_SIM_UART_BASE_ADDRESS, data[i]);
    }
}

//! \} End of uart_radio_sim group