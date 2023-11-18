/**
 * @file lps331.h
 * @author Miroslav Chalko
 * @brief LPS331AP pressure sensor driver
*/

#ifndef __LPS331_H__
#define __LPS331_H__

#include <stdint.h>
#include "lpsxxx.h"

/**
 * @brief begin data sampling
 * @param p pointer to the sensor handle
*/
int lps331_sample_data(lpsxxx_t *p);

/**
 * @brief read data from the sensor
 * @param p pointer to the sensor handle
 * @param temp pointer to the variable where the temperature will be stored
 * @return 0 on success, -1 on error
*/
int lps331_read_temp(lpsxxx_t* p, float *temp);

/**
 * @brief read data from the sensor
 * @param p pointer to the sensor handle
 * @param press pointer to the variable where the pressure will be stored
 * @return 0 on success, -1 on error
*/
int lps331_read_pressure(lpsxxx_t* p, float *pres);

/**
 * @brief reboot the sensor
 * @param p pointer to the sensor handle
 * @return 0 on success, -1 on error
*/
int lps331_reboot(lpsxxx_t* p);


#endif // __LPS331_H__