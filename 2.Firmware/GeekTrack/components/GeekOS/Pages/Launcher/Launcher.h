#ifndef __LAUNCHER_PRESENTER_H
#define __LAUNCHER_PRESENTER_H

#include "LauncherView.h"
#include "LauncherModel.h"

namespace Page
{

class Launcher : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Launcher();
    virtual ~Launcher();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    static void onStatusBarUpdate(lv_timer_t* timer);
private:
    LauncherView View;
    LauncherModel Model;
    lv_timer_t* timer;
    lv_timer_t* stausBarTimer;
};

}

#endif
