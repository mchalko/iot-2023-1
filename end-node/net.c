/**
 * @file net.c
 * @author Miroslav Chalko
 * @brief network functions for publishing data 
*/

#include "net.h"

#include <string.h>
#include "utils.h"
#include "config.h"

#include "timex.h"
#include "ztimer.h"
#include "thread.h"
#include "mutex.h"
#include "paho_mqtt.h"
#include "MQTTClient.h"

#define BUFFER_SIZE 1024

static MQTTClient client;
static Network network;
static uint8_t rx_buffer[BUFFER_SIZE];
static uint8_t tx_buffer[BUFFER_SIZE];

/**
 * @brief Convert QoS from uint8_t to enum
*/
static enum QoS get_qos(uint8_t q){
    switch (q){
        case 0 : return QOS0;
        case 1 : return QOS1;
        case 2 : return QOS2;
        default: return QOS0;
    }
}

void net_init(void){
    NetworkInit(&network);
    MQTTClientInit(&client, &network, COMMAND_TIMEOUT_MS, tx_buffer, BUFFER_SIZE, rx_buffer, BUFFER_SIZE);
    MQTTStartTask(&client);
    DPRINTLN("MQTT client initialized");
}

int net_connect(void){
    int ret = 0;

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = MQTT_VERSION_v311;
    data.clientID.cstring = MQTT_CLIENT_ID;
    data.username.cstring = MQTT_USER;
    data.password.cstring = MQTT_PWD;
    data.keepAliveInterval = DEFAULT_KEEPALIVE_SEC;
    data.cleansession = 1;
    data.willFlag = 0;

    ret = NetworkConnect(&network, MQTT_HOST, MQTT_PORT);
    if (ret < 0) {
        DPRINTLN("Unable to connect network %d", ret);
        return ret;
    }
    DPRINTLN("Network connected");

    ret = MQTTConnect(&client, &data);
    if (ret < 0) {
        DPRINTLN("Unable to connect client %d", ret);
        net_disconnect();
        return ret;
    } 
    DPRINTLN("MQTT client connected");

    return ret;
}

void net_disconnect(void){
    int ret = MQTTDisconnect(&client);
    if (ret < 0) {
        DPRINTLN("Unable to disconnect client");
    } 

    NetworkDisconnect(&network);
    DPRINTLN("Network disconnected");
}

int net_publish(const char *topic, const char *data){
    int ret;

    MQTTMessage message;
    message.qos = get_qos(MQTT_QOS);
    message.retained = MQTT_RETAIN_MSG;
    message.payload = (void *)data;
    message.payloadlen = strlen(data);

    if ((ret = MQTTPublish(&client, topic, &message)) < 0) {
        DPRINTLN("Unable to publish (%d)", ret);
    } else {
        DPRINTLN("Sending (%s) : %s", (char *)message.payload, topic);
    }

    return ret;
}