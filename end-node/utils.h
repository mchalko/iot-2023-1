/**
 * @file utils.h
 * @author Mirolav Chalko
 * @brief Various utilities
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>

#ifdef USE_DPRINT
#include <stdio.h>
#define DPRINTLN(fmt, ...) printf( fmt "\n" ,##__VA_ARGS__)
#define DPRINT(fmt, ...) printf( fmt ,##__VA_ARGS__)
#else
#define DPRINTLN(...)
#define DPRINT(...)
#endif

#define _STR(x) #x

/**
 * @brief convert macro value to string
*/
#define STR(x) _STR(x)

/**
 * @brief get minimum value
*/
#define MIN(a,b) (((a)<(b))?(a):(b))

/**
 * @brief get maximum value
*/
#define MAX(a,b) (((b)<(a))?(a):(b))

/**
 * @brief get absolute value
*/
#define ABS(a) (((a)<0)?(-(a)):(a))

/**
 * @brief convert decimal part of float to integer
 * @param x float value
 * @param places number of decimal places, e.g. for 3 decimal places use 1000
*/
#define FLOAT_DECIMALS(x, places) ((uint32_t)((((float)(ABS(x))) - ((int)(ABS(x)))) * places))

#endif // __UTILS_H__