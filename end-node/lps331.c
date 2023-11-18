/**
 * @file lps331.h
 * @author Miroslav Chalko
 * @brief LPS331AP pressure sensor driver
*/

#include "lps331.h"

#include "utils.h"

#include "periph/i2c.h"
#include "lpsxxx_internal.h"
#include "ztimer.h"
#define BOOT_TIMEOUT_MS 1000

int lps331_sample_data(lpsxxx_t *p){
    int ret = 0;
    
    i2c_acquire(p->params.i2c);
    // start sampling
    ret = i2c_write_reg(p->params.i2c, p->params.addr, LPSXXX_REG_CTRL_REG2, 1, 0);

    i2c_release(p->params.i2c);
    return ret;
}

int lps331_read_temp(lpsxxx_t* p, float *temp){
    int ret = 0;
    uint8_t tmp = 0;
    int16_t val = 0;
    
    i2c_acquire(p->params.i2c);
    ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_TEMP_OUT_L, &tmp, 0);
    if(ret < 0){
        goto out;
    }
    val |= tmp;

    ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_TEMP_OUT_H, &tmp, 0);
    if(ret < 0){
        goto out;
    }
    val |= ((uint16_t) tmp << 8);
    *temp = 42.5 + (val / 480.0);
    
out:
    i2c_release(p->params.i2c);
    return ret;
}

int lps331_read_pressure(lpsxxx_t* p, float *pres){
    uint8_t tmp;
    uint32_t val = 0;
    int ret;
    i2c_acquire(p->params.i2c);

    ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_PRESS_OUT_XL, &tmp, 0);
    if(ret < 0) {
        goto out;
    }
    val |= tmp;

    ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_PRESS_OUT_L, &tmp, 0);
    if(ret < 0) {
        goto out;
    }
    val |= ((uint32_t)tmp << 8);

    ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_PRESS_OUT_H, &tmp, 0);
    if(ret < 0) {
        goto out;
    }
    val |= ((uint32_t)tmp << 16);
    
    i2c_release(p->params.i2c);
    
    *pres = val / 4096.0;

out:
    return ret;
}


int lps331_reboot(lpsxxx_t* p){
    int ret;
    uint8_t val;

    i2c_acquire(p->params.i2c);
    // set reboot bits
    ret = i2c_write_reg(p->params.i2c, p->params.addr, LPSXXX_REG_CTRL_REG2, (1 << 7) | (1 << 2), 0);
    // wait for reboot to finish
    for(uint32_t i = 0;;i++){
        ztimer_sleep(ZTIMER_MSEC, 100);
        ret = i2c_read_reg(p->params.i2c, p->params.addr, LPSXXX_REG_CTRL_REG2, &val, 0);
        if(ret < 0){
            break;
        }
        if((val & (1 << 7)) == 0){
            break;
        }
        if(i == (BOOT_TIMEOUT_MS/100)){
            ret = -1;
            break;
        }
    }

    i2c_release(p->params.i2c);
    return ret;
}
