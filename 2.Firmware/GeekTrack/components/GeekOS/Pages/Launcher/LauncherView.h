#ifndef __LAUNCHER_VIEW_H
#define __LAUNCHER_VIEW_H

#include "Pages/Page.h"

namespace Page
{

class LauncherView
{
public:
    void Create(lv_obj_t* root);
    void CreateTimeObj(lv_obj_t* root);
    void CreateBackgroundImage(lv_obj_t* root);
    void CreateStausBar(lv_obj_t* root);
    void UpdateBatteryInfo(lv_obj_t* root, int capacity);
    void UpdateStepInfo(lv_obj_t* root, int16_t step);
    void CreateStepObj(lv_obj_t* root);

    void Delete(void);
public:
    struct
    {
        lv_obj_t* labelTime;
        lv_obj_t* bGImage;
        lv_obj_t* batPrecent;
        lv_obj_t* sdCard;
        lv_obj_t* battery;
        lv_obj_t* wifi;
        lv_obj_t* stepImage;
        lv_obj_t* stepCount;
    } ui;

private:

};

}

#endif // !__VIEW_H
