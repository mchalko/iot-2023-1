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
#include "ztimer.h"
#include "lpsxxx.h"
#include "lpsxxx_params.h"
#include "isl29020.h"
#include "isl29020_params.h"

static lpsxxx_t lpsxxx;
static isl29020_t isl29020;

int main(void) {
    int16_t temp = 0;
    int16_t last_temp = 0;
    int16_t temp_diff;
    const uint16_t temp_tolerance = 10; // 0.1 C

    uint16_t pres = 0;
    uint16_t last_pres = 0;
    int16_t pres_diff;
    const uint16_t pres_tolerance = 10; // hPa

    int16_t lux = 0;
    int16_t last_lux = 0;
    int16_t lux_diff;
    const uint16_t lux_tolerance = 10; // lux

    uint32_t temp_sleep = min_sleep;
    uint32_t temp_sleep_left = 0;
    uint32_t pres_sleep = min_sleep;
    uint32_t pres_sleep_left = 0;
    uint32_t lux_sleep = min_sleep;
    uint32_t lux_sleep_left = 0;

    // initialize sensors
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    isl29020_init(&isl29020, &isl29020_params[0]);
    // initialize network
    net_init();

    uint32_t last_wakeup = ztimer_now(ZTIMER_MSEC);

    for(;;){
        // read data from sensors
        if (temp_sleep_left < min_sleep) {
            lpsxxx_read_temp(&lpsxxx, &temp);
            temp_diff = temp - last_temp;
            last_temp = temp;
            temp /= 100;
            printf("Temp: %d\n", temp);
            // dynamic scaling of sleep time
            temp_sleep = dynamic_sleep_time(&temp_diff, &temp_sleep, &temp_tolerance);
            temp_sleep_left = temp_sleep;
        }
        if (pres_sleep_left < min_sleep) {
            lpsxxx_read_pres(&lpsxxx, &pres);
            pres_diff = pres - last_pres;
            last_pres = pres;
            printf("Pres: %d\n", pres);
            pres_sleep = dynamic_sleep_time(&pres_diff, &pres_sleep, &pres_tolerance);
            pres_sleep_left = pres_sleep;
        }
        if (lux_sleep_left < min_sleep) {
            lux = isl29020_read(&isl29020);
            lux_diff = lux - last_lux;
            last_lux = lux;
            printf("Lux: %d\n", lux);
            lux_sleep = dynamic_sleep_time(&lux_diff, &lux_sleep, &lux_tolerance);
            lux_sleep_left = lux_sleep;
        }

        net_publish_data(temp, pres, lux);
        ztimer_periodic_wakeup(ZTIMER_MSEC, &last_wakeup,
                               least_sleep_time(&temp_sleep_left, &pres_sleep_left, &lux_sleep_left));
    }


    return 0;
}
