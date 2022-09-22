#ifndef _GEEKTRACK_SDK_H_
#define _GEEKTRACK_SDK_H_

extern "C" {

typedef struct {
	float x, y, z;
}EulerAngles_t;


__declspec(dllexport) void GeekTrack_Init();

__declspec(dllexport) EulerAngles_t GetEulerAngles();
}

#endif