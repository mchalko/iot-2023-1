/**
 * @file utils.h
 * @author Mirolav Chalko
 * @brief Various utilities
 */

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
#define STR(x) _STR(x)

// set dynamic sleep limits
static const uint32_t min_sleep = 5000; // ms
static const uint16_t max_exp = 6; // 5 * 2^6 = 320 s max sleep time

/** Scales sleep time based on rate of change.
* min_sleep             for     diff * min_sleep / prev_sleep > tolerance
* min_sleep * 2         for     tolerance/2 < diff * min_sleep / prev_sleep <= tolerance
*                       ...
* min_sleep * 2^max_exp for     diff * min_sleep / prev_sleep <= tolerance/max_exp
*/
uint32_t dynamic_sleep_time(int16_t* diff, uint32_t* prev_sleep, const uint16_t* tolerance);

/**
* Finds the smallest of three sleep times and decrements each accordingly
*/
uint32_t least_sleep_time(uint32_t* time1, uint32_t* time2, uint32_t* time3);
