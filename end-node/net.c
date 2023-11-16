/**
 * @file net.c
 * @author Miroslav Chalko
 * @brief network functions for publishing data 
*/

#include "net.h"

#include "utils.h"
#include "config.h"

#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include "fmt.h"
#include "net/gcoap.h"
#include "net/sock/util.h"
#include "net/sock/dtls.h"
#include "net/sock/dtls/creds.h"
#include "net/utils.h"
#include "od.h"
#include "periph/pm.h"
#include "net/credman.h"
#include "net/dsm.h"

#define CREDENTIAL_TAG 1

static const char data_uri [] = DATA_URI;
static const char destination [] =  "[" HOST_ADDR "]:"STR(HOST_PORT);
static const uint8_t psk_id[] = PSK_IDENTITY;
static const uint8_t psk_key[] = PSK_KEY;
static const credman_credential_t credential = {
    .type = CREDMAN_TYPE_PSK,
    .tag = CREDENTIAL_TAG,
    .params = {
        .psk = {
            .key = { .s = psk_key, .len = sizeof(psk_key) - 1, },
            .id = { .s = psk_id, .len = sizeof(psk_id) - 1, },
        }
    },
};

static sock_udp_ep_t remote; // remote endpoint
static uint32_t fail_count; // counter of failed sends

int net_init(void){
    int ret;

    // initialize udp socket
    ret = sock_udp_name2ep(&remote, destination);
    if (ret < 0) {
        DPRINTLN("gcoap: sock init failed");
        goto out;
    }

    // initialize dtls - add credentials and assign socket
    ret = credman_add(&credential);
    if(ret < 0){
        DPRINTLN("gcoap: credman add failed");
        goto out;
    }

    sock_dtls_t * sock = gcoap_get_sock_dtls();
    ret = sock_dtls_add_credential(sock, CREDENTIAL_TAG);
    if (ret < 0) {
        DPRINTLN("gcoap: sock dtls add cred failed");
        goto out;
    }

    DPRINTLN("gcoap: client initialized, host: %s", destination);

out : 
    return ret;
}


int net_publish_json(const char* uri, const char *data){
    int ret;

    uint8_t buf[CONFIG_GCOAP_PDU_BUF_SIZE];
    coap_pkt_t pdu;
    uint8_t len;
    uint16_t datalen = strlen(data);

    ret = gcoap_req_init(&pdu, buf, CONFIG_GCOAP_PDU_BUF_SIZE, COAP_METHOD_POST, uri);
    if (ret < 0){
        DPRINTLN("gcoap: req init failed");
        goto out;
    }

    coap_hdr_set_type(pdu.hdr, COAP_TYPE_CON); // confirmable
    ret = coap_opt_add_format(&pdu, COAP_FORMAT_JSON); // json format
    if (ret < 0){
        DPRINTLN("gcoap: opt add opt - format failed");
        goto out;
    }

    ret = coap_opt_finish(&pdu, COAP_OPT_FINISH_PAYLOAD); // with payload
    if (ret < 0){
        DPRINTLN("gcoap: opt finish failed");
        goto out;
    }
    // add payload
    len = ret + datalen;
    memcpy(pdu.payload, data, datalen);

    // send request
    ret = gcoap_req_send(buf, len, &remote, NULL, NULL);
    if(ret < 0){
        DPRINTLN("gcoap: send fail, dtls not estabilisted");
    }else if (ret == 0){
        DPRINTLN("gcoap: send failed");
        fail_count++;
        if(fail_count > FAIL_REBOOT_TRESHOLD){
            DPRINTLN("gcoap: rebooting due to failed sends");
            pm_reboot();
        }
    }else{
        fail_count = 0;
        DPRINTLN("gcoap: sent %i bytes", ret);
    }

out:
    return ret;
}

int net_publish_data(int temp, int pres, int light){
    char result [128];
    sprintf(result, 
    "{"
    "\"" DATA_KEY_TEMP  "\":%i,"
    "\"" DATA_KEY_PRES  "\":%i,"
    "\"" DATA_KEY_LIGHT "\":%i"
    "}", temp, pres, light);

    return net_publish_json(data_uri, result);
}