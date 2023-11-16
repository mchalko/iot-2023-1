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

int main(void) {
    int16_t temp = 0;
    uint16_t pres = 0;
    uint8_t flag = 0;
    // initialize sensor
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    // initialize network
    net_init();
    
    for(;;){
        // read data from sensor
        if(flag){
            lpsxxx_read_temp(&lpsxxx, &temp);
            net_publish_data(temp, pres, 0);
        }else{
            lpsxxx_read_pres(&lpsxxx, &pres);
            net_publish_data(temp, pres, 0);
        }
        flag = !flag;
        
        ztimer_sleep(ZTIMER_MSEC, 2000);
    }

    return 0;
}
