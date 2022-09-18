#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>
// ----------------------------------------------
// defines
// ----------------------------------------------
#define PRES             1
#define PSHIFT           14
#define PROUNDBIT        (1 << (PSHIFT-1))
#define DEG2RAD(x)       (x * 3.141592f / 180.0f)
// ----------------------------------------------
// typedef
// ----------------------------------------------

typedef struct {
    int x, y;
} Vector2i;

typedef struct {
  long x, y, z;
} Vector3;

typedef struct {
  int x, y, z;
} Vector3i;

typedef struct {
    Vector2i p0;
    Vector2i p1;
} Line2i;

typedef struct {
    Vector3i p0;
    Vector3i p1;
} Line3i;

// fixed point identity matrix
//typedef struct {
//  long m[4][4] = {
//      {PRES,    0,    0,    0},
//      {   0, PRES,    0,    0},
//      {   0,    0, PRES,    0},
//      {   0,    0,    0, PRES}
//  };
//} Matrix4;
//
//typedef struct {
//    float m[4][4] = {
//    {0.0f,    0.0f,    0.0f},
//    {0.0f,    0.0f,    0.0f},
//    {0.0f,    0.0f,    0.0f},
//    };
//} Matrix3f;

typedef struct {
    int w;                                 /* screen width.  */
    int h;                                 /* screen height, */
    int xOffset;
    int yOffset;
} ScreenInfo;

// ----------------------------------------------
// functions
// ----------------------------------------------
// fixed point multiplication
// static long pMultiply(long x, long y) {
//   return ( (x * y) + PROUNDBIT) >> PSHIFT;
// }


#endif // TYPE_H
