#include <math.h>
#include "MeshCube.h"

Cube3D::Cube3D(lv_obj_t* root) {

    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 1);
    lv_style_set_line_color(&style_line, lv_color_hex(0xffffff));
    lv_style_set_line_rounded(&style_line, true);

    for (int i = 0; i < 12; i++) {
        lineList[i] = lv_line_create(root);
        lv_obj_add_style(lineList[i], &style_line, 0);
    }

    for (int i = 0; i < CUBE_LINECOUNT; i++) {
       lines[i].p0.x = NODE(CubeLines[i][0], 0);
       lines[i].p0.y = NODE(CubeLines[i][0], 1);
       lines[i].p0.z = NODE(CubeLines[i][0], 2);

       lines[i].p1.x = NODE(CubeLines[i][1], 0);
       lines[i].p1.y = NODE(CubeLines[i][1], 1);
       lines[i].p1.z = NODE(CubeLines[i][1], 2);
    }
    this->root = root;
}

void Cube3D::CreateRoateMatrix(void)
{
    /* Convert degrees to radians. */
    float rx = DEG2RAD(rotateX);
    float ry = DEG2RAD(rotateY);

    /* Zan is assumed to be zero */
    float s1 = sinf(ry);
    float s2 = sinf(rx);

    float c1 = cosf(ry);
    float c2 = cosf(rx);

    /* Fill rotate matrix member. */
    rm[0][0] =  c1;
    rm[0][1] =  0;
    rm[0][2] = -s1;

    rm[1][0] = (s1 * s2);
    rm[1][1] =  c2;
    rm[1][2] = (c1 * s2);

    rm[2][0] = (s1 * c2);
    rm[2][1] = -s2;
    rm[2][2] = (c1 * c2);
}

void Cube3D::Line3DProj2D(Line3i vec3, Line2i* vec2) {

    uint8_t Ok = 0;

    float xv1 = (vec3.p0.x * rm[0][0]) + (vec3.p0.y * rm[1][0]) + (vec3.p0.z * rm[2][0]);
    float yv1 = (vec3.p0.x * rm[0][1]) + (vec3.p0.y * rm[1][1]) + (vec3.p0.z * rm[2][1]);
    float zv1 = (vec3.p0.x * rm[0][2]) + (vec3.p0.y * rm[1][2]) + (vec3.p0.z * rm[2][2]);

    float zvt1 = zv1 - OffsetZ;

    int rx1 = 0, ry1 = 0;
    if (zvt1 < -5) {
        rx1 = (int)(256 * (xv1 / zvt1)) + OffsetX;
        ry1 = (int)(256 * (yv1 / zvt1)) + OffsetY;
        Ok = 1; // ok we are alright for point 1.
    }

    float xv2 = (vec3.p1.x * rm[0][0]) + (vec3.p1.y * rm[1][0]) + (vec3.p1.z * rm[2][0]);
    float yv2 = (vec3.p1.x * rm[0][1]) + (vec3.p1.y * rm[1][1]) + (vec3.p1.z * rm[2][1]);
    float zv2 = (vec3.p1.x * rm[0][2]) + (vec3.p1.y * rm[1][2]) + (vec3.p1.z * rm[2][2]);

    float zvt2 = zv2 - OffsetZ;

    int rx2 = 0, ry2 = 0;

    if (zvt2 < -5) {
        rx2 = (int)(256 * (xv2 / zvt2)) + OffsetX;
        ry2 = (int)(256 * (yv2 / zvt2)) + OffsetY;
    }
    else {
        Ok = 0;
    }

    if (Ok == 1) {
        vec2->p0.x = rx1;
        vec2->p0.y = ry1;
        vec2->p1.x = rx2;
        vec2->p1.y = ry2;
    }
}


void Cube3D::Cube3DProj2D() {
    CreateRoateMatrix();

    /* converts the 3d line segments to 2d. */
    for (int i = 0; i < CUBE_LINECOUNT; i++) {
        Line3DProj2D(lines[i], &(Proj2DLine[i]));
    }
}

void Cube3D::Cube3DLVGLRender(void) {
    Cube3DProj2D();
    static lv_point_t linePointsList[12][2] = { {0, 0} };
    for (int i = 0; i < CUBE_LINECOUNT; i++) {
        linePointsList[i][0].x = Proj2DLine[i].p0.x;
        linePointsList[i][0].y = Proj2DLine[i].p0.y;
        linePointsList[i][1].x = Proj2DLine[i].p1.x;
        linePointsList[i][1].y = Proj2DLine[i].p1.y;
        lv_line_set_points(lineList[i], linePointsList[i], 2);
    }
}
