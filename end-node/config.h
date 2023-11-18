/**
 * @file config.h
 * @author Miroslav Chalko
 * @brief generic config file
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define HOST_ADDR "2603:c026:c103:7f77:d52:bbe3:21fd:cb2c" // server address
#define HOST_PORT 5684 // server port
#define DATA_URI "/data" // data URI

#define FAIL_REBOOT_TRESHOLD 5 // reboot after x failed sends

#define DATA_KEY_TEMP "temperature" // temperature key
#define DATA_KEY_PRES "pressure" // pressure key
#define DATA_KEY_LIGHT "light" // light key

#define PSK_IDENTITY "client"
#define PSK_KEY "123"

#define MIN_SLEEP_TIME_MS 2500 // minimum sleep time in seconds
#define MAX_SLEEP_TIME_MS 60000 // maximum sleep time in seconds

#define SENSITIVITY_LIGHT 0.1 // light sensor sensitivity
#define SENSITIVITY_TEMP 1 // temperature sensor sensitivity
#define SENSITIVITY_PRES 1.5 // pressure sensor sensitivity

#define CONNECTION_RETRY_TIME_MS 5000 // connection retry time in milliseconds

#endif // __CONFIG_H__