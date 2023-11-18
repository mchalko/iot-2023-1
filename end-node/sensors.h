/**
 * @file sensors.h
 * @author Miroslav Chalko
 * @brief definition of the sensor manipulation functions
*/

#ifndef __SENSORS_H__
#define __SENSORS_H__

#include <stdint.h>

typedef struct{
    uint32_t sleep_time; // sleep time in milliseconds
    uint32_t last_wakeup; // last wakeup time in milliseconds
    float (*measure)(void*); // function pointer to the measure function, returns the difference between the last and the current value
}sensor_t;

typedef struct{
    sensor_t base;
    float light;
}isl29020_sensor_t;

typedef struct{
    sensor_t base;
    float temperature;
    float pressure;
}lps331_sensor_t;

typedef struct{
    isl29020_sensor_t isl;
    lps331_sensor_t lps;
} sensors_handle_t;

/**
 * @brief initialize all the sensors
 * @param handle pointer to the sensor handle
 * @return 0 on success, -1 on error
*/
int sensors_init(sensors_handle_t *handle);

/**
 * @brief measure all the sensors
 * @param handle pointer to the sensor handle
 * @return 0 on success, -1 on error, 1 if the sensor is not ready yet
*/
int sensors_measure(sensors_handle_t *handle);

/**
 * @brief get sleep time in milliseconds
 * @param handle pointer to the sensor handle
 * @return sleep time in milliseconds
 * @note the sleep time is calculated from the last measured values
 */
uint32_t sensors_get_sleep_time(sensors_handle_t *handle);


#endif // __SENSORS_H__