/**
* @file utils.c
* @author Kuisma Hannuksela
* @brief various utilities
*/

#include "imath.h"

#include "utils.h"

uint32_t dynamic_sleep_time(int16_t* diff, uint32_t* prev_sleep, const uint16_t* tolerance) {
    static uint16_t exp;
    if (*diff == 0) {
        return min_sleep * powi(2, max_exp);
    }
    if (*diff < 0) *diff *= -1; // absolute value of diff
    exp = (*tolerance * *prev_sleep) / (*diff * min_sleep);
    if (exp > max_exp) exp = max_exp;
    return min_sleep * powi(2, exp);
}

uint32_t least_sleep_time(uint32_t* time1, uint32_t* time2, uint32_t* time3) {
    static uint32_t least_time;
    if (*time1 <= *time2) {
        if (*time1 <= *time3) {
            least_time = *time1;
        } else {
            least_time = *time3;
        }
    }
    else if (*time2 <= *time3) {
        least_time = *time2;
    } else {
        least_time = *time3;
    }
    *time1 -= least_time;
    *time2 -= least_time;
    *time3 -= least_time;
    return least_time;
}

