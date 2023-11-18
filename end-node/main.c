/**
 * @file main.c
 * @author Miroslav Chalko
 * @brief end node main file
*/

#include <stdint.h>
#include <stdio.h>

#include "thread.h"
#include "net.h"
#include "utils.h"
#include "sensors.h"
#include "ztimer.h"

static sensors_handle_t sensor_handle;

int main(void) {
    int ret;
    
    ret = sensors_init(&sensor_handle);
    if (ret < 0) {
        DPRINTLN("Error initializing sensors");
        goto error;
    }

    ret = net_init();
    if (ret < 0) {
        DPRINTLN("Error initializing network");
        goto error;
    }

    for(;;){
        ret = sensors_measure(&sensor_handle);
        if (ret == 0) {
            net_publish_data(sensor_handle.lps.temperature,
                             sensor_handle.lps.pressure,
                             sensor_handle.isl.light);
        }

        ztimer_sleep(ZTIMER_MSEC, sensors_get_sleep_time(&sensor_handle));
    }

error:
    for(;;);

    return 0;
}
