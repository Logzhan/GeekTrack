#ifndef _GEEKTRACK_SDK_H_
#define _GEEKTRACK_SDK_H_

extern "C" {

typedef struct {
	float x, y, z;
}EulerAngles_t;

typedef struct {
	float w, x, y, z;
}Quaternion_t;

__declspec(dllexport) void GeekTrack_Init();

__declspec(dllexport) EulerAngles_t GetEulerAngles(int devId);

__declspec(dllexport) Quaternion_t GetQuaternion(int devId);
}

#endif