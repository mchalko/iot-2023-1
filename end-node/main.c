/**
 * @file main.c
 * @author Miroslav Chalko
 * @brief end node main file
*/

#include <stdint.h>

#include "thread.h"
#include "net.h"
#include "ztimer.h"
#include "lpsxxx.h"
#include "lpsxxx_params.h"

static lpsxxx_t lpsxxx;

char data [150];
#define TOPIC_PRESSURE "pressure"
#define TOPIC_TEMPERATURE "temperature"


int main(void) {
    int16_t temp = 0;
    uint16_t pres = 0;
    uint8_t flag = 0;
    // initialize sensor
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    // initialize network
    net_init();
    // connect to host
    while(net_connect() < 0){}

    for(;;){
        // read data from sensor
        if(flag){
            lpsxxx_read_temp(&lpsxxx, &temp);
            sprintf(data, "%i.%u", temp / 100, temp % 100);
            net_publish(TOPIC_TEMPERATURE, data);
        }else{
            lpsxxx_read_pres(&lpsxxx, &pres);
            sprintf(data, "%d", pres);
            net_publish(TOPIC_PRESSURE, data);
        }
        flag = !flag;
        
        ztimer_sleep(ZTIMER_MSEC, 5000);
    }

    return 0;
}
