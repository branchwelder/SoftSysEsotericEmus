#ifndef __COMMON_H__
#define __COMMON_H__

/* Copyright (C) 
 * 2013 - Tomasz Wisniewski
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


/**
 * @file common.h 
 *
 * @brief common macros and definitions
 *
 * This file provides some general purpose data types definitions, macros and routines
 *
 */

#include <stdint.h>

// ================================================================================


/**
 * @brief volatile int8_t
 */
typedef volatile int8_t vint8_t;

/**
 * @brief volatile uint8_t
 */
typedef volatile uint8_t vuint8_t;

/**
 * @brief volatile int16_t
 */
typedef volatile int16_t vint16_t;

/**
 * @brief volatile uint16_t
 */
typedef volatile uint16_t vuint16_t;

/**
 * @brief volatile int32_t
 */
typedef volatile int32_t vint32_t;

/**
 * @brief volatile uint32_t
 */
typedef volatile uint32_t vuint32_t;

/**
 * @brief volatile int64_t
 */
typedef volatile int64_t vint64_t;

/**
 * @brief volatile uint64_t
 */
typedef volatile uint64_t vuint64_t;


/**
 * @brief return value type
 */
typedef enum _e_return {
	RET_OK = 0x00,
	RET_ERROR = 0x80,
	RET_ERROR_PARAMETER,
	RET_ERROR_RESOURCES
} e_return;

// ================================================================================


/**
 * @brief define NULL just for convenience
 */
#ifndef NULL
#define NULL (void *)0x00
#endif


/**
 * @brief unused attribute - to make the compiler happy when needed
 */
#define UNUSED __attribute__((unused))


/**
 * @brief macro to determine if the returned value is an error
 */
#define IS_ERROR(__x) \
	( (__x) >= RET_ERROR)


/**
 * @brief macro to determine if the returned value is a warning
 */
#define IS_WARNING(__x) \
	( ((__x) > RET_OK) && ((__x) < RET_ERROR) )


/**
 * @brief macro to determine if the returned value is a warning or a success
 */
#define IS_WARNING_OK(__x) \
	( ((__x) >= RET_OK) && ((__x) < RET_ERROR))


// ================================================================================


/**
 * @brief return maximum value out of two given
 *
 * @param __x first value
 * @param __y second value
 *
 * @return __x or __y depending on which is bigger
 */
#define MAX(__x, __y) \
	( (__x) > (__y) ? (__x) : (__y))


/**
 * @brief return minimum value out of two given
 *
 * @param __x first value
 * @param __y second value
 *
 * @return __x or __y depending on which is smaller
 */
#define MIN(__x, __y) \
	( (__x) < (__y) ? (__x) : (__y))


/**
 * @brief exchange value between variables
 *
 * This implementation doesn't use a temporary variable
 *
 * @param __x first value
 * @param __y second value
 *
 */
#define EXCHANGE(__x, __y) \
	__x ^= __y; __y ^= __x; __x ^= __y


/**
 * @brief converts binary value to BCD representation
 *
 * @param __val value to be converted
 *
 * @return BCD converted value
 */
#define BCD2BIN(__val) \
	((__val & 0x0f) + (__val >> 4) * 10)


/**
 * @brief converts BCD value to binary representation
 *
 * @param __val value to be converted
 *
 * @return binary converted value
 */
#define BIN2BCD(__val) \
	(((__val / 10) << 4) + __val % 10)


/**
 * @brief get pointer to DDR register from PORT register
 *
 * @param __val pointer to PORT register 
 *
 * @return pointer to DDR register
 */
#define GET_DDRX_FROM_PORTX(__portx) \
	(__portx - 1)	


/**
 * @brief get pointer to PIN register from PORT register
 *
 * @param __val pointer to PORT register 
 *
 * @return pointer to PIN register
 */
#define GET_PINX_FROM_PORTX(__portx) \
	(__portx - 2)	


// ================================================================================


/**
 * @brief provide a brief calculation of the memory usage and report how much is left
 *
 * @return number of bytes available
 */
uint16_t common_memory_left();


/**
 * @brief calculate the absolute value of the number
 *
 * @param a_value positive/negative signed value
 *
 * @return absolute unsigned value
 */
uint32_t common_abs(int32_t a_value);


#define common_zero_mem(__ptr, __len) while (__len--) (*(char *)(__ptr)) = 0x00


/**
 * @brief performs ordered dithering using bayer 8x8 matrix of 6 bit depth color (0-63) to 1 bit.
 *
 * @param c color (must be scaled to range 0-63)
 * @param x x coordinate
 * @param y y coordinate
 *
 * @return true if point should be drawned, flase if otherwise
 */
uint8_t common_ditherPoint(uint8_t c, uint8_t x, uint8_t y);


/**
 * @brief exchange byte order in a 32 bit word
 *
 * @param a_value
 *
 * @return 
 */
uint32_t common_swap(uint32_t a_value);

#endif /* __COMMON_H__ */
