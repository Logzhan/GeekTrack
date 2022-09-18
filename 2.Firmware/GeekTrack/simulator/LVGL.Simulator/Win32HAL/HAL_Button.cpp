#include <stdio.h>
#include <conio.h>
#include "HAL\HAL.h"
#include "Event/ButtonEvent.h"

/* Construct Button Object. */
ButtonEvent btOK;              // 选择键
ButtonEvent btUP;              // 上键
ButtonEvent btDOWN;            // 下键
ButtonEvent btPOWER;           // 电源键，不共享对象
Button_Info_t Button_Info;

/**
  * @brief  按键事件回调处理
  * @param  btn:按键对象地址
  * @param  event:事件类型
  * @retval 无
  */
static void Button_EventHandler(ButtonEvent* btn, int event)
{
    if(event == ButtonEvent::EVENT_ButtonClick){
        if(btn == &btOK){
            Button_Info.btnOK = 1;
        }else if(btn == &btUP){
            Button_Info.btnUp = 1;
        }else if(btn == &btDOWN){
            Button_Info.btnDown = 1;
        }
    }
    if(event == ButtonEvent::EVENT_ButtonLongPressed){
        if(btn == &btOK){
            Button_Info.btnPower = 1;
        }
    }
}

/**
  * @brief  电源按键事件回调处理
  * @param  btn:按键对象地址
  * @param  event:事件类型
  * @retval 无
  */
static void ButtonPower_EventHandler(ButtonEvent* btn, int event){
    if(btn == &btPOWER){
        /*长按关机*/
        if(event == ButtonEvent::EVENT_ButtonLongPressed)
        {
            //Power_Shutdown();
        }
    }
}

/**
  * @brief  按键初始化
  * @param  无
  * @retval 无
  */
void Button_Init()
{
    /* Add button event. */
    btUP.EventAttach(Button_EventHandler);
    btOK.EventAttach(Button_EventHandler);
    btDOWN.EventAttach(Button_EventHandler);
    btPOWER.EventAttach(ButtonPower_EventHandler);
}

void Button_Update(){
    char ch = 0;
    if (_kbhit()) {
        ch = _getch();
    }
    btOK.EventMonitor((ch == 'q'));
    btUP.EventMonitor((ch == 'w'));
    btDOWN.EventMonitor((ch == 'e'));
}

void Button_GetInfo(Button_Info_t* info){
    /* Set the button info. */
    info->btnOK   = Button_Info.btnOK;
    info->btnUp   = Button_Info.btnUp;
    info->btnDown = Button_Info.btnDown;
    info->btnPower= Button_Info.btnPower;
    /* Reset Button event. */
    Button_Info.btnOK    = 0;
    Button_Info.btnUp    = 0;
    Button_Info.btnDown  = 0;
    Button_Info.btnPower = 0;
}
