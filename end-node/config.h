/**
 * @file config.h
 * @brief generic config file
*/

#define MQTT_VERSION_v311 4 // MQTT version 3.1.1
#define COMMAND_TIMEOUT_MS 4000 // network command timeout

#define MQTT_CLIENT_ID "end-node" // MQTT client ID
#define MQTT_USER "" // MQTT user
#define MQTT_PWD "" // MQTT password
#define MQTT_HOST "2603:c026:c103:7f77:d52:bbe3:21fd:cb2c" // MQTT server host
#define MQTT_PORT 1883 // MQTT server port
#define MQTT_QOS 1 // MQTT QoS

#define DEFAULT_KEEPALIVE_SEC 120 // MQTT keepalive
#define MQTT_RETAIN_MSG 1 // mqtt retain message on server