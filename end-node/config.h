/**
 * @file config.h
 * @author Miroslav Chalko
 * @brief generic config file
*/

#define HOST_ADDR "2603:c026:c103:7f77:d52:bbe3:21fd:cb2c" // server address
#define HOST_PORT 5684 // server port
#define DATA_URI "/data" // data URI

#define FAIL_REBOOT_TRESHOLD 5 // reboot after x failed sends

#define DATA_KEY_TEMP "temperature" // temperature key
#define DATA_KEY_PRES "pressure" // pressure key
#define DATA_KEY_LIGHT "light" // light key

#define PSK_IDENTITY "client"
#define PSK_KEY "123"

#define KEEPALIVE_INTERVAL_SEC 120 // keepalive
