#include "LauncherView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void LauncherView::Create(lv_obj_t* root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    CreateBackgroundImage(root);
    CreateStausBar(root);
    CreateStepObj(root);
    CreateTimeObj(root);
}

void LauncherView::CreateStausBar(lv_obj_t* root) {
    ui.batPrecent = lv_label_create(root);
    lv_label_set_recolor(ui.batPrecent, true);
    lv_label_set_text_fmt(ui.batPrecent, "#f1f1f1 %d%%", 90);
    lv_obj_set_pos(ui.batPrecent, 205, 5);
    //geek_page_anim_anim_in(bat_precent, 0);

    // 显示电池图标
    ui.sdCard = lv_label_create(root);
    lv_label_set_recolor(ui.sdCard, true);
    lv_label_set_text_fmt(ui.sdCard, "#f1f1f1 %s", LV_SYMBOL_SD_CARD);
    lv_obj_set_pos(ui.sdCard, 32, 5);
    //geek_page_anim_anim_in(sd_card, 0);

    // 显示SD卡图标
    ui.battery = lv_label_create(root);
    lv_label_set_recolor(ui.battery, true);
    lv_label_set_text_fmt(ui.battery, "#f1f1f1 %s", LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_pos(ui.battery, 182, 5);
    //geek_page_anim_anim_in(battery, 0);

    // 显示WIFI图标
    ui.wifi = lv_label_create(root);
    lv_label_set_recolor(ui.wifi, true);
    lv_label_set_text_fmt(ui.wifi, "#f1f1f1 %s", LV_SYMBOL_WIFI);
    lv_obj_set_pos(ui.wifi, 5, 5);
    //geek_page_anim_anim_in(wifi, 0);

    lv_group_t* group = lv_group_get_default();
    lv_group_set_wrap(group, true);
    lv_group_add_obj(group, root);

}

void LauncherView::CreateBackgroundImage(lv_obj_t* root) {
    //lv_obj_t* img = lv_img_create(root);
    //lv_img_set_src(img, ResourcePool::GetImage("bg_img_main"));
    //lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    //ui.bGImage = img;
}
extern "C" {
   LV_FONT_DECLARE(lv_font_montserrat_48);
}

void LauncherView::CreateTimeObj(lv_obj_t* root) {
     lv_obj_t* label = lv_label_create(root);
     lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
     lv_obj_set_style_text_color(label, lv_color_hex(0xf1f1f1), 0);
     lv_label_set_text_fmt(label, "%d:%d", 15, 34);
     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
     ui.labelTime = label;
}

void LauncherView::UpdateBatteryInfo(lv_obj_t* root, int capacity) {

    lv_label_set_text_fmt(ui.batPrecent, "#f1f1f1 %d%%", capacity);

    const char* battSymbol[] =
    {
        LV_SYMBOL_BATTERY_EMPTY,
        LV_SYMBOL_BATTERY_1,
        LV_SYMBOL_BATTERY_2,
        LV_SYMBOL_BATTERY_3,
        LV_SYMBOL_BATTERY_FULL
    };
    uint8_t bat_level = capacity / 20;
    if (bat_level > 4)bat_level = 4;

    lv_label_set_text_fmt(ui.battery, "#f1f1f1 %s", battSymbol[bat_level]);
}

void LauncherView::CreateStepObj(lv_obj_t* root) {

    ui.stepImage = lv_img_create(root);
    lv_img_set_src(ui.stepImage, ResourcePool::GetImage("run_ico_img"));
    lv_obj_set_pos(ui.stepImage, 155, 110);
    //geek_page_anim_anim_in(img2, 0);

    ui.stepCount = lv_label_create(root);
    lv_label_set_recolor(ui.stepCount, true);
    lv_label_set_text_fmt(ui.stepCount, "#f1f1f1 / %d", 12040);
    lv_obj_set_pos(ui.stepCount, 180, 115);
}

void LauncherView::UpdateStepInfo(lv_obj_t* root, int16_t step) {
    lv_label_set_text_fmt(ui.stepCount, "#f1f1f1 / %d", step);
}

void LauncherView::Delete() {

}
