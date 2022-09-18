#ifndef MESH_CUBE_H
#define MESH_CUBE_H

#include "Engine3DType.h"
#include "lvgl.h"


#define NODECOUNT      8
#define TRICOUNT       12
#define CUBE_LINECOUNT 12

#define NODE(a, b) (long)((nodes[a][b]))
#define EDGE(a, b) (long)((&faces[a][b]))

const long nodes[NODECOUNT][3] = {
    {(long) ( 50.0 * PRES),  (long) ( 50.0 * PRES),  (long) (-50.0 * PRES)},
    {(long) ( 50.0 * PRES),  (long) (-50.0 * PRES),  (long) (-50.0 * PRES)},
    {(long) (-50.0 * PRES),  (long) (-50.0 * PRES),  (long) (-50.0 * PRES)},
    {(long) (-50.0 * PRES),  (long) ( 50.0 * PRES),  (long) (-50.0 * PRES)},
    {(long) ( 50.0 * PRES),  (long) ( 50.0 * PRES),  (long) ( 50.0 * PRES)},
    {(long) (-50.0 * PRES),  (long) ( 50.0 * PRES),  (long) ( 50.0 * PRES)},                 
    {(long) (-50.0 * PRES),  (long) (-50.0 * PRES),  (long) ( 50.0 * PRES)},
    {(long) ( 50.0 * PRES),  (long) (-50.0 * PRES),  (long)  (50.0 * PRES)},
};

const unsigned char CubeLines[CUBE_LINECOUNT][2] = {
    {6, 7},
    {7, 4},
    {4, 5},
    {5, 6},
    {2, 1},
    {1, 0},
    {0, 3},
    {3, 2},
    {6, 2},
    {7, 1},
    {5, 3},
    {4, 0},
};

class Cube3D {
public:
    /* Scene 3d.   */
    Line3i   lines[CUBE_LINECOUNT];
    Line2i   Proj2DLine[CUBE_LINECOUNT];
    uint8_t  lineCount;
    uint16_t rotateX;
    uint16_t rotateY;
    int16_t  OffsetX;
    int16_t  OffsetY;
    int16_t  OffsetZ;

    /* lvgl render. */
    lv_obj_t* lineList[CUBE_LINECOUNT];
    lv_obj_t* root;
    lv_style_t style_line;

    /* Roate Matrix. */
    float    rm[3][3];

    Cube3D(lv_obj_t* root);
    void CreateRoateMatrix(void);
    void Line3DProj2D(Line3i vec, Line2i* vec2);
    void Cube3DProj2D(void);
    void Cube3DLVGLRender(void);
};


#endif // MESH_H
