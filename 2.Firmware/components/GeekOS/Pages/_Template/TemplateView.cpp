#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

using namespace Page;

void TemplateView::Create(lv_obj_t* root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
    
    // 设置对象背景颜色
    lv_obj_set_style_bg_color(root, lv_color_black(), 0);
    // 设置对象背景透明度
    lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);

    lv_obj_t* label = lv_label_create(root);
    lv_label_set_recolor(label, true);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    lv_label_set_text(label, "");
    ui.labelTitle = label;

    label = lv_label_create(root);
    lv_label_set_recolor(label, true);
    lv_label_set_text(label, "");
    lv_obj_center(label);
    ui.labelTick = label;

    /* Initialzie the style of line. */
    cube3D = new Cube3D(root);

    lv_group_t* group = lv_group_get_default();
    lv_group_set_wrap(group, true);
    lv_group_add_obj(group, root);

    cube3D->OffsetX = 120;
    cube3D->OffsetY = (135/2);
    cube3D->OffsetZ = 550;
}

void TemplateView::Update() {

    static int inc = -2;
    /* Rotate around x and y axes in 1 degree increments */
    cube3D->rotateX++;
    cube3D->rotateY++;
    /* Prevents overflow. */
    cube3D->rotateX = (cube3D->rotateX) % 360;
    cube3D->rotateX = (cube3D->rotateX) % 360;

    /* Zoom in and out on Z axis within limits */
    cube3D->OffsetZ += inc;
    /* Select Z axis auto zoom in. */
    if (cube3D->OffsetZ > 500) inc = -1;
    /* Select Z axis auto zoom out. */
    else if (cube3D->OffsetZ < 360) inc = 1;

    /* Render Cube3d with lvgl. */
    cube3D->Cube3DLVGLRender();

}

void TemplateView::Delete() {
    delete cube3D;
}
