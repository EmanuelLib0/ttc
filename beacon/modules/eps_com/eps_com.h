/*
 * eps_com.h
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
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
 * \file eps_com.h
 * 
 * \brief Functions to receive data from EPS module
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 23/09/2016
 * 
 * \defgroup eps_com EPS Communication
 * \ingroup modules
 * \{
 */

#ifndef EPS_COM_H_
#define EPS_COM_H_

#include <stdint.h>
#include <stdbool.h>

#include "eps_com_config.h"

/**
 * \struct EPSData
 * 
 * \brief Struct to store the data from the EPS module.
 */
typedef struct
{
    uint8_t bat1_voltage[3];            /**< Battery 1 voltage. */
    uint8_t bat2_voltage[3];            /**< Battery 2 voltage. */
    uint8_t bat1_charge[2];             /**< Battery 1 charge. */
    uint8_t bat2_charge[2];             /**< Battery 2 charge. */
    uint8_t bat1_temperature[4];        /**< Battery 1 temperature. */
    uint8_t bat2_temperature[4];        /**< Battery 2 temperature. */
    uint8_t solar_panels_voltages[7];   /**< Solar panels voltages. */
    uint8_t solar_panels_currents[13];  /**< Solar panels currents. */
    uint8_t energy_level;               /**< Satellite energy level. */
} EPSData;

/**
 * \struct EPS_Com
 * 
 * \brief EPS communication variables struct.
 */
typedef struct
{
    uint8_t received_byte;                      /**< Byte buffer. */
    uint8_t byte_counter;                       /**< Received packet byte counter. */
    uint8_t buffer[EPS_COM_DATA_PKT_LEN + 1];   /**< Packet buffer. */
    uint8_t crc_fails;                          /**< Number of CRC failures (Packets with errors). */
    bool is_open;                               /**< Flag to store the EPS communication state (true = Open; false = Closed). */
    EPSData data;                               /**< EPS data. */
} EPS;

/**
 * \var eps_ptr
 * 
 * \brief 
 */
extern EPS *eps_ptr;

/**
 * \fn eps_com_init
 * 
 * \brief Initialization of the EPS communication module.
 * 
 * \param eps is a pointer to an EPS object.
 * 
 * \return Initialization status. It can be:
 *      - \b STATUS_SUCCESS
 *      - \b STATUS_FAIL
 *      .
 */
uint8_t eps_com_init(EPS *eps);

/**
 * \fn eps_com_receive_data
 * 
 * \brief Receives the data coming from the EPS module.
 * 
 * This is function only must be called from an interruption generated by
 * the EPS module.
 * 
 * \param eps is a pointer to an EPS object.
 * 
 * \return None
 */
static void eps_com_receive_data(EPS *eps);

/**
 * \fn eps_com_save_data_from_buffer
 * 
 * \brief Copy the bytes of the buffer to the eps_data struct.
 * 
 * \param buffer is the data buffer to copy the EPS data.
 * \param eps_data is the EPSData struct to store the EPS data.
 * 
 * \return None
 */
static void eps_com_save_data_from_buffer(uint8_t *buffer, EPSData *eps_data);

/**
 * \fn eps_com_clear_buffer
 * 
 * \brief Clears the data buffer.
 * 
 * \param buffer is a data buffer to store the incoming EPS data.
 * 
 * \return None
 */
static void eps_com_clear_buffer(uint8_t *buffer);

#endif // EPS_COM_H_

//! \} End of eps_com group
