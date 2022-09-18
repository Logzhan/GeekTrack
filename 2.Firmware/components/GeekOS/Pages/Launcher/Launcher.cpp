#include "Launcher.h"
#ifndef  _WIN32
#include "System/HAL/HAL.h"
#endif // ! _WIN32

#include "stdio.h"
using namespace Page;

Launcher::Launcher()
    : timer(nullptr)
{
}

Launcher::~Launcher()
{

}

void Launcher::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Launcher::onViewLoad()
{
    Model.Init();
    View.Create(_root);
    AttachEvent(_root);
}

void Launcher::onViewDidLoad()
{
  
}

void Launcher::onViewWillAppear()
{
    Param_t param;
    
    param.color = lv_color_black();
    param.time = 1000;
    //PAGE_STASH_POP(param);
   
    timer = lv_timer_create(onTimerUpdate, param.time, this);
    stausBarTimer = lv_timer_create(onStatusBarUpdate, 200, this);

}

void Launcher::onViewDidAppear()
{
}

void Launcher::onViewWillDisappear()
{

}

void Launcher::onViewDidDisappear()
{
    lv_timer_del(timer);
    lv_timer_del(stausBarTimer);
}

void Launcher::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void Launcher::AttachEvent(lv_obj_t* obj)
{
    //lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Launcher::Update()
{
}

void Launcher::onTimerUpdate(lv_timer_t* timer)
{
    Launcher* instance = (Launcher*)timer->user_data;

    instance->Update();
}

void Launcher::onStatusBarUpdate(lv_timer_t* timer) {
#ifdef _WIN32
    static int bat = 0;
    bat = bat + 10;
    if (bat > 100) {
        bat = 0;
    }
#else
    Power_Info_t info;
    Power_GetInfo(&info);
    int bat = info.capacity;
#endif
    Launcher* instance = (Launcher*)timer->user_data;
    instance->View.UpdateBatteryInfo(instance->_root, bat);
    int16_t steps = instance->Model.GetUserStep();
    instance->View.UpdateStepInfo(instance->_root, steps);
}


void Launcher::onEvent(lv_event_t* event)
{
    Launcher* instance = (Launcher*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root)
    {
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE)
        {
            instance->_Manager->Pop();
        }
    }
    if(code == LV_EVENT_PRESSED){
        instance->_Manager->Push("Pages/SystemInfos");
    }
}
