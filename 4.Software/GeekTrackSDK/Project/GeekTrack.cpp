#include"stdafx.h"
#include"GeekTrackSDK.h"
#include<stdio.h>
#include<thread>
#include<winsock2.h>
#include<windows.h>

#pragma comment(lib,"ws2_32.lib")

/* max suppport diffrent device id. */
#define MAX_SUPPORT_DEV_NUM   9

struct GeekTrackNode_t {
	EulerAngles_t Pose;
	Quaternion_t  Quat;
	bool devOnline;
	GeekTrackNode_t() {
		memset(&Pose, 0, sizeof(EulerAngles_t));
		memset(&Quat, 0, sizeof(Quaternion_t));
		devOnline = false;
	}
};

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
		//printf("...\n");
		//从广播地址接收消息，注意用来绑定的地址和接收消息的地址是不一样的
		recvfrom(sock, buf, 256, 0, (struct sockaddr FAR*) &from, (int FAR*) & fromlength);
		Sleep(10);
		float q[4] = { 0.0f };
		int id = 0;
		//printf("%s\n", buf);
		int ret = sscanf_s(buf, "%d %f %f %f %f\n", &id, &q[0], &q[1], &q[2], &q[3]);
		if (ret > 0 && (id >= 0 && id < MAX_SUPPORT_DEV_NUM)) {

			float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;

			//pitch = asin((-2.0 * ((double)q[3]*q[1] - (double)q[0]*q[2])));                                           
			//yaw   = atan2((double)q[2]*q[1] + (double)q[0]*q[3], 0.5 - (double)q[2]*q[2] - (double)q[3]*q[3]); 
			//roll  = atan2((double)q[2]*q[3] + (double)q[0]*q[1], 0.5 - (double)q[2]*q[2] - (double)q[1]*q[1]); 


			float w, x, y, z;
			w = q[0]; x = q[1]; y = q[2]; z = q[3];
			double PI = 3.1415926;

			pitch = asin(-2.0f * (z * x - w * y)) * (180.0f / PI);
			yaw = atan2(y * x + w * z, 0.5f - y * y - z * z) * (180.0f / PI);
			roll = atan2(y * z + w * x, 0.5f - y * y - x * x) * (180.0f / PI);


			//yaw *= (180.0f / 3.141592f);
			//roll *= (180.0f / 3.141592f);
			//pitch *= (180.0f / 3.141592f);

			printf("yaw = %f, roll = %f, pitch = %f\n", yaw, roll, pitch);

			TrackNode[id].Quat.w = q[0];
			TrackNode[id].Quat.x = q[1];
			TrackNode[id].Quat.y = q[2];
			TrackNode[id].Quat.z = q[3];

			TrackNode[id].Pose.x = pitch;
			TrackNode[id].Pose.y = roll;
			TrackNode[id].Pose.z = yaw;
			TrackNode[id].devOnline = true;
		}
		ZeroMemory(buf, 256);
	}
}


void GeekTrack_Init() {

	static bool optval = false;
	//启动SOCKET库，版本为2.0
	if (optval == true) {
		return;
	}
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
	EulerAngles_t Pose = {0.0f, 0.0f, 0.0f};
	return Pose;
}

Quaternion_t GetQuaternion(int devId) {
	if (devId >= 0 && devId < MAX_SUPPORT_DEV_NUM) {
		return TrackNode[devId].Quat;
	}
	Quaternion_t Quat = { 0.0f, 0.0f, 0.0f, 0.0f };
	return Quat;
}

int main()
{
	GeekTrack_Init();
	int devId = 0;
	while (1) {
		Sleep(30);
		//printf("%d,%f,%f,%f\n", devId,TrackNode[devId].Pose.x, TrackNode[devId].Pose.y,
		//	TrackNode[devId].Pose.z);
	}
	system("pause");
	return 0;
}
