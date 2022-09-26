#include "HAL.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <sys/param.h>
#include "esp_netif.h"
#include "lwip/sockets.h"
#include <lwip/netdb.h>
#include "WIFINetwork.h"
#include "mpu9250.h"

#define UDP_PORT            9000
#define UDP_BUFF_LEN        128
#define TAG                 "HAL_Network"

struct sockaddr_in saddr = { 0 };
int  sock = -1; 
char buff[UDP_BUFF_LEN] = " ";
char ConfigString[64]   = {0};
char ssid[32] = {0};
char password[64] = {0};

void Network_Init()
{
    Config_GetString("WIFI_NAME", ssid, 32);
    Config_GetString("WIFI_PWD", password, 64);

    /* Connect WIFI first. */
    WIFI_Connect(ssid, password);
    /* Init socket to send data. */
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to create socket. Error %d", errno);
    }

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(UDP_PORT);
    saddr.sin_addr.s_addr = htonl(IPADDR_BROADCAST);
}

void Network_UdpSendData()
{
    int err = 0;
    Config_GetString("DEV_IDX", ConfigString, 64);
    while (1) 
    {
        float yaw = 0.0f, roll = 0.0f, pitch = 0.0f;
        float quat[4] = {0.0f};
        MPU9250_GetEulerAngles(&yaw, &roll, &pitch);
        MPU9250_GetQuaternion(quat);
		sprintf(buff, "%s %f %f %f %f\n",ConfigString, quat[0],quat[1],quat[2],quat[3]);
        err = sendto(sock, buff, 256, 0, (struct sockaddr *)&saddr, 
                sizeof(struct sockaddr_in));
        if (err < 0) {
            ESP_LOGE(TAG, "IPV4 sendto failed. errno: %d", errno);
        }   
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
    close(sock);
}