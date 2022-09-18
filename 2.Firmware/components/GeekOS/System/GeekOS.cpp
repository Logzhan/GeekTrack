#include "GeekOS.h"
#include "stdio.h"
#include "Pages/AppFactory.h"
#include "System/PageManager/PageManager.h"
#include "Resource/ResourcePool.h"
#include "Pages/SystemInfos/SystemInfos.h"

static AppFactory factory;
static PageManager manager(&factory);

#define ACCOUNT_SEND_CMD(ACT, CMD)\
do{\
    DataProc::ACT##_Info_t info;\
    memset(&info, 0, sizeof(info));\
    info.cmd = DataProc::CMD;\
    DataProc::Center()->AccountMain.Notify(#ACT, &info, sizeof(info));\
}while(0)


/**
  * @brief  print the usage of memory infomation for lvgl.
  * @param  void
  * @date   2022-08-12
  * @retval void
  */
void GeekOSMemMonitor() {
    lv_mem_monitor_t monitor;
    lv_mem_monitor(&monitor);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
        (int)monitor.total_size - monitor.free_size,
        monitor.used_pct,
        monitor.frag_pct,
        (int)monitor.free_biggest_size);
}

/**
  * @brief  Initialize the GeekOS page and lvgl config mode.
  * @param  void
  * @date   2022-08-12
  * @retval void
  */
void GeekOS_Init() {

    /* Make sure the default group exists */
    if (!lv_group_get_default())
    {
        lv_group_t* group = lv_group_create();
        lv_group_set_default(group);
    }
    /* Initialize the data processing node */
    DataProc_Init();

    /* Set screen style */
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), 0);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    /* Set root default style */
    static lv_style_t rootStyle;
    lv_style_init(&rootStyle);
    lv_style_set_width(&rootStyle, LV_HOR_RES);
    lv_style_set_height(&rootStyle, LV_VER_RES);
    lv_style_set_bg_opa(&rootStyle, LV_OPA_COVER);
    lv_style_set_bg_color(&rootStyle, lv_color_black());
    manager.SetRootDefaultStyle(&rootStyle);

    /* Initialize resource pool */
    ResourcePool::Init();

    manager.Install("Launcher", "Pages/Launcher");
    manager.Install("Template", "Pages/_Template");
    manager.Install("Startup", "Pages/Startup");
    manager.Install("SystemInfos", "Pages/SystemInfos");

    /* Setting global lvgl load animation type */
    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);

    /* launch the Startup Page. */
    manager.Push("Pages/Startup");
    
    /* show the current lvgl memory usage */
    GeekOSMemMonitor();
}

void GeekOS_Uninit(){

}
