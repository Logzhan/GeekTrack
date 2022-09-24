/* file library_wifi_network */

#ifndef _LIBRARY_WIFI_NETWORK_H_
#define _LIBRARY_WIFI_NETWORK_H_


#ifdef __cplusplus
extern "C" {
#endif

uint8_t Library_WIFI_Init(char* ssid, char* password);

uint8_t WIFI_Connect(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif