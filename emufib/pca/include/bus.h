#ifndef BUS_H_TQ6MRMNQ
#define BUS_H_TQ6MRMNQ

/* Copyright (C) 
 * 2014 - Tomasz Wisniewski
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#include <config.h>
#include <common.h>
#include <stdint.h>


/**
 * @file bus.h 
 *
 * @brief Generic API for abstracting bus implementations
 *
 * You can use the struct bus_t structure definition to collect your bus implementation routines. It's useful when trying
 * to write drivers independent of the bus implementation. The device driver communicates with the bus using the function
 * pointers exposed by the bus_t structure - that way you can always change the bus implementation without having to modify the device driver
 *
 * As a reference have a look on how the pcd8544.h device driver is implemented. 
 */


/**
 * @brief function pointer type definition for bulk data transfers
 *
 * @param 
 * @param a_len
 * @param a_waitall
 *
 * @return 
 */
typedef uint8_t (*bus_bulkx_routine_t)(void *priv, void *a_data, uint8_t a_len, uint8_t a_waitall);


/**
 * @brief function pointer type definition for bulk data transfers
 *
 * @param 
 * @param a_len
 * @param a_waitall
 *
 * @return 
 */
typedef uint8_t (*bus_bulkx_simple_routine_t)(void *priv, void *a_data, uint8_t a_len);


/**
 * @brief function pointer type definition for byte data transfers
 *
 * @param 
 *
 * @return 
 */
typedef uint8_t (*bus_bytex_routine_t)(void *priv, uint8_t *a_data);


/**
 * @brief check for available bytes received
 *
 * @return number of bytes ready to be read
 */
typedef uint8_t (*bus_available_routine_t)(void *priv);


/**
 * @brief general bus interface for device drivers
 */
struct bus_t {
	// byte tx/rx routines
	bus_bytex_routine_t f_getc;
	bus_bytex_routine_t f_sendc;

	// bulk tx/rx routines
	bus_bulkx_routine_t f_recv;
	bus_bulkx_routine_t f_send;

	// general routines
	bus_available_routine_t f_avail;
	bus_bytex_routine_t f_peek;

	void *priv;
};


#endif /* end of include guard: BUS_H_TQ6MRMNQ */

