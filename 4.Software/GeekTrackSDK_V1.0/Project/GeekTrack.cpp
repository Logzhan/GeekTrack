#include"stdafx.h"
#include"GeekTrackSDK.h"
#include<stdio.h>
#include<thread>
#include<winsock2.h>
#include<windows.h>

#pragma comment(lib,"ws2_32.lib")

/* max suppport diffrent device id. */
#define MAX_SUPPORT_DEV_NUM   9

typedef  struct {
	EulerAngles_t Pose;
}GeekTrackNode_t;

GeekTrackNode_t TrackNode[MAX_SUPPORT_DEV_NUM];

SOCKET        sock;
sockaddr_in   from, a;
WSADATA       wsdata;
int           fromlength = 0;
std::thread*  t;

void GeekTrackUpdate() {
	char buf[256];
	int i = 0;
	while (1)
	{
		//从广播地址接收消息，注意用来绑定的地址和接收消息的地址是不一样的
		recvfrom(sock, buf, 256, 0, (struct sockaddr FAR*) &from, (int FAR*) & fromlength);
		Sleep(10);
		float yaw = 0.0f, roll = 0.0f, pitch = 0.0f;
		int id = 0;
		int ret = sscanf_s(buf, "%d %f %f %f\n", &id, &yaw, &roll, &pitch);
		if (ret > 0 && (id > 0 && id < MAX_SUPPORT_DEV_NUM)) {
			TrackNode[id].Pose.x = pitch;
			TrackNode[id].Pose.y = roll;
			TrackNode[id].Pose.z = yaw;
		}
		ZeroMemory(buf, 256);
	}
}


void GeekTrack_Init() {

	bool optval;
	//启动SOCKET库，版本为2.0
	WSAStartup(0x0202, &wsdata);
	optval = true;
	//然后赋值给两个地址，一个用来绑定套接字，一个用来从网络上的广播地址接收消息；
	a.sin_family = AF_INET;
	a.sin_addr.s_addr = 0;
	a.sin_port = htons(9000);

	//from.sin_family = AF_INET;
	//from.sin_addr.s_addr = INADDR_BROADCAST;
	//from.sin_port = htons(5050);

	fromlength = sizeof(SOCKADDR);
	//用UDP初始化套接字
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	// 设置该套接字为广播类型，
	//setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char FAR *)&optval, sizeof(optval));
	// 把该套接字绑定在一个具体的地址上
	bind(sock, (sockaddr*)&a, sizeof(sockaddr_in));

	t = new std::thread(GeekTrackUpdate);
	
}

EulerAngles_t GetEulerAngles(int devId) {
	if (devId >= 0 && devId < MAX_SUPPORT_DEV_NUM) {
		return TrackNode[devId].Pose;
	}
}

int main()
{
	GeekTrack_Init();
	int devId = 0;
	while (1) {
		Sleep(50);
		printf("%d,%f,%f,%f\n", devId,TrackNode[devId].Pose.x, TrackNode[devId].Pose.y,
			TrackNode[devId].Pose.z);
	}
	system("pause");
	return 0;
}
