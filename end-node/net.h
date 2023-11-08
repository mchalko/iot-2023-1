/**
 * @file net.h
 * @author Miroslav Chalko
 * @brief network functions for publishing data 
*/

#include <stdint.h>

/**
 * @brief Initialize network
*/
void net_init(void);

/**
 * @brief Connect to network
 * @return 0 on success
*/
int net_connect(void);

/**
 * @brief Disconnect from network
*/
void net_disconnect(void);

/**
 * @brief Publish data to server
 * @param topic Topic to publish data to
 * @param data Data to publish
 * @return 0 on success
*/
int net_publish(const char *topic, const char *data);