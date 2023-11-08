/*
 * Copyright (C) 2019 Javier FILEIV <javier.fileiv@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file        main.c
 * @brief       Example using MQTT Paho package from RIOT
 *
 * @author      Javier FILEIV <javier.fileiv@gmail.com>
 *
 * @}
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "mutex.h"
#include "paho_mqtt.h"
#include "shell.h"
#include "thread.h"
#include "timex.h"
#include "ztimer.h"
#include "MQTTClient.h"

#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

#define BUF_SIZE 1024
#define MQTT_VERSION_v311 4 /* MQTT v3.1.1 version is 4 */
#define COMMAND_TIMEOUT_MS 4000

#define DEFAULT_MQTT_CLIENT_ID "test"
#define DEFAULT_MQTT_USER ""
#define DEFAULT_MQTT_PWD ""
#define DEFAULT_HOST "2603:1020:2:3::11c"

/**
 * @brief Default MQTT port
 */
#define DEFAULT_MQTT_PORT 1883

/**
 * @brief Keepalive timeout in seconds
 */
#define DEFAULT_KEEPALIVE_SEC 120

#ifndef MAX_LEN_TOPIC
#define MAX_LEN_TOPIC 100
#endif

#ifndef MAX_TOPICS
#define MAX_TOPICS 4
#endif

#define IS_CLEAN_SESSION 1
#define IS_RETAINED_MSG 0

static MQTTClient client;
static Network network;
static int topic_cnt = 0;

static int _cmd_discon(int argc, char **argv) {
    (void)argc;
    (void)argv;
    topic_cnt = 0;
    int res = MQTTDisconnect(&client);
    if (res < 0) {
        printf("mqtt_example: Unable to disconnect\n");
    } else {
        printf("mqtt_example: Disconnect successful\n");
    }

    NetworkDisconnect(&network);
    return res;
}

static int _cmd_con(int argc, char **argv) {
    (void)argc;
    (void)argv;
    int ret = -1;

    int port = DEFAULT_MQTT_PORT;

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = MQTT_VERSION_v311;
    data.clientID.cstring = DEFAULT_MQTT_CLIENT_ID;
    data.username.cstring = DEFAULT_MQTT_USER;
    data.password.cstring = DEFAULT_MQTT_PWD;
    data.keepAliveInterval = DEFAULT_KEEPALIVE_SEC;
    data.cleansession = IS_CLEAN_SESSION;
    data.willFlag = 0;

    printf("Trying to connect to %s, port: %d\n", DEFAULT_HOST, port);
    ret = NetworkConnect(&network, DEFAULT_HOST, port);
    if (ret < 0) {
        printf("Unable to connect\n");
        return ret;
    }
    printf("netword connected");
    ret = MQTTConnect(&client, &data);
    if (ret < 0) {
        printf("Unable to connect client %d\n", ret);
        _cmd_discon(0, NULL);
        return ret;
    } else {
        printf("mqtt_example: Connection successfully\n");
    }

    return (ret > 0) ? 0 : 1;
}

static const char test_payload[] = "Hello from RIOT!";
static const char test_topic[] = "devices";

static int _cmd_pub(int argc, char **argv) {
    (void)argc;
    (void)argv;
    enum QoS qos = QOS0;

    MQTTMessage message;
    message.qos = qos;
    message.retained = IS_RETAINED_MSG;
    message.payload = (void *)test_payload;
    message.payloadlen = strlen(test_payload);

    int rc;
    if ((rc = MQTTPublish(&client, test_topic, &message)) < 0) {
        printf("Unable to publish (%d)\n", rc);
    } else {
        printf(
            "Message (%s) has been published to topic %s"
            "with QOS %d\n",
            (char *)message.payload, test_topic, (int)message.qos);
    }

    return rc;
}

static const shell_command_t shell_commands[] = {
    {"con", "connect to MQTT broker", _cmd_con}, {"pub", "publish something", _cmd_pub}, {NULL, NULL, NULL}};

static unsigned char buf[BUF_SIZE];
static unsigned char readbuf[BUF_SIZE];

int main(void) {
    if (IS_USED(MODULE_GNRC_ICMPV6_ECHO)) {
        msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    }

    NetworkInit(&network);

    MQTTClientInit(&client, &network, COMMAND_TIMEOUT_MS, buf, BUF_SIZE, readbuf, BUF_SIZE);
    printf("Running mqtt paho example. Type help for commands info\n");

    MQTTStartTask(&client);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
