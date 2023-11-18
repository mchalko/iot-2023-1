/**
 * @file sensors.c
 * @author Miroslav Chalko
 * @brief sensor manipulation functions
*/

#include "sensors.h"

#include "utils.h"
#include "config.h"

#include <math.h>

#include "lps331.h"
#include "isl29020.h"
#include "lpsxxx_params.h"
#include "isl29020_params.h"

#include "ztimer.h"


static lpsxxx_t lpsxxx;
static const lpsxxx_params_t params_lps331 =  { .i2c  = LPSXXX_PARAM_I2C,  .addr = LPSXXX_PARAM_ADDR, .rate = 0};
static isl29020_t isl29020;
static const isl29020_params_t params_isl29020 =  { .i2c   = ISL29020_PARAM_I2C,   
                                                    .addr  = ISL29020_PARAM_ADDR,  
                                                    .range = ISL29020_RANGE_64K, 
                                                    .mode  = ISL29020_MODE_AMBIENT 
                                                };


static float isl_measure(void* self){
    isl29020_sensor_t* s = (isl29020_sensor_t*)self;
    float prev_light = s->light;

    if(isl29020_enable(&isl29020) < 0){
        DPRINTLN("Error enabling ISL29020 sensor");
        s->light = NAN;
        return NAN;
    }
    // wait for measurement to finish
    ztimer_sleep(ZTIMER_MSEC, 450);

    int light = isl29020_read(&isl29020);
    if (light < 0){
        DPRINTLN("Error reading light");
        isl29020_disable(&isl29020);
        s->light = NAN;
        return NAN;
    }else{
        s->light = light;
    }

    isl29020_disable(&isl29020);
    return ABS(prev_light - s->light) * SENSITIVITY_LIGHT;
}

static float lps_measure(void* self){
    lps331_sensor_t* s = (lps331_sensor_t*)self;
    float prev_pressure = s->pressure;
    float prev_temperature = s->temperature;

    if(lpsxxx_enable(&lpsxxx) != LPSXXX_OK){
        DPRINTLN("Error enabling LPSXXX sensor");
        s->pressure = s->temperature = NAN;
        return NAN;
    }
    ztimer_sleep(ZTIMER_MSEC, 100);

    if(lps331_sample_data(&lpsxxx)){
        DPRINTLN("Error sampling data");
        s->pressure = s->temperature = NAN;
        return NAN;
    }
    ztimer_sleep(ZTIMER_MSEC, 1000);
    
    if(lps331_read_pressure(&lpsxxx, &s->pressure)){
        DPRINTLN("Error reading pressure");
        s->pressure = NAN;
    }

    if(lps331_read_temp(&lpsxxx, &s->temperature)){
        DPRINTLN("Error reading temperature");
        s->temperature = NAN;
    }
    
    lpsxxx_disable(&lpsxxx);
    return MAX(ABS(prev_pressure - s->pressure) * SENSITIVITY_PRES, 
               ABS(prev_temperature - s->temperature) * SENSITIVITY_TEMP);
}

static int isl_init(isl29020_sensor_t* s){
    s->light = NAN;
    s->base.measure = isl_measure;

    int ret = isl29020_init(&isl29020, &params_isl29020);
    if (ret < 0) {
        DPRINTLN("Error initializing ISL29020 sensor");
        return ret;
    }

    ret = isl29020_disable(&isl29020);
    if (ret < 0) {
        DPRINTLN("Error disabling ISL29020 sensor");
    }

    return ret;
}

static int lps_init(lps331_sensor_t* s){
    s->pressure = NAN;
    s->temperature = NAN;
    s->base.measure = lps_measure;

    lpsxxx.params = params_lps331;
    int ret = lps331_reboot(&lpsxxx);
    if(ret < 0){
        DPRINTLN("Error rebooting LPSXXX sensor");
        return ret;
    }

    ret = lpsxxx_init(&lpsxxx, &params_lps331);
    if(ret != LPSXXX_OK){
        DPRINTLN("Error initializing LPSXXX sensor");
        return ret;
    }

    ret = lpsxxx_disable(&lpsxxx);
    if (ret < 0) {
        DPRINTLN("Error disabling LPSXXX sensor");
    }

    return ret;
}


int sensors_init(sensors_handle_t *handle){
    int ret = 0;

    ret = isl_init(&handle->isl);
    if(ret < 0) return ret;

    ret = lps_init(&handle->lps);
    
    return ret;
}

int sensors_measure(sensors_handle_t *handle){
    static uint8_t flag; // signals first run
    sensor_t* sensors [] = {(sensor_t*)&handle->isl, (sensor_t*)&handle->lps};
    uint32_t now;
    float diff;
    int ret = 1; // default return value if no sensor was measured

    for(uint32_t i = 0; i < sizeof(sensors) / sizeof(*sensors); i++){
        sensor_t* s =  sensors[i];
        now = ztimer_now(ZTIMER_MSEC);
        if(now - s->last_wakeup > s->sleep_time){
            s->last_wakeup = ztimer_now(ZTIMER_MSEC);
            diff = s->measure((void*)s);
            
            if(!flag){
                flag = 1;
                s->sleep_time = MIN_SLEEP_TIME_MS;
            }else if(isnan(diff) || diff < 0.1){
                s->sleep_time = MAX_SLEEP_TIME_MS;
            }else {
                s->sleep_time = 1000 * (uint32_t)(40.0 / (diff * diff));
                s->sleep_time = MIN(s->sleep_time, MAX_SLEEP_TIME_MS);
                s->sleep_time = MAX(s->sleep_time, MIN_SLEEP_TIME_MS);
            }
            DPRINTLN("sleep time: %lu", s->sleep_time);
            
            if(isnan(diff)){
                ret = -1;  // signal error
            }else if (ret == 1){
                ret = 0; // mark that the sensor was measured
            }
        }
    }

    return ret;
}

uint32_t sensors_get_sleep_time(sensors_handle_t *handle){
    return MIN(handle->isl.base.sleep_time, handle->lps.base.sleep_time);
}