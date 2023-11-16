/**
 * @file net.h
 * @author Miroslav Chalko
 * @brief network functions for publishing data 
*/

#include <stdint.h>

/**
 * @brief Initialize network
 * @return 0 on success
*/
int net_init(void);

/**
 * @brief Publish json data to server
 * @param data Data to publish
 * @return 0 on success
*/
int net_publish_json(const char* uri, const char *data);

/**
 * @brief Publish data to server
 * @param temp Temperature
 * @param pres Pressure
 * @param light Light
 * @return 0 on success
*/
int net_publish_data(int temp, int pres, int light);