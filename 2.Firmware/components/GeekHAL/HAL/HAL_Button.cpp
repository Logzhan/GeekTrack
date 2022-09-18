#include <stdio.h>
#include "HAL.h"
#include "ButtonEvent.h"
#include "driver/gpio.h"

/* Construct Button Object. */
ButtonEvent btPOWER;           // Power Button, No share Object.
Button_Info_t Button_Info;

/**
  * @brief  Button callback handle event.
  * @param  btn: Button object adress.
  * @param  event: Event type.
  * @retval None
  */
static void Button_EventHandler(ButtonEvent* btn, int event)
{
    if(event == ButtonEvent::EVENT_ButtonClick){
        if(btn == &btPOWER){
            Button_Info.btnPower = 1;
            printf("Button PWR short click.\n");
        }
    }
    if(event == ButtonEvent::EVENT_ButtonLongPressed){
        if(btn == &btPOWER){
            Button_Info.btnPowerLongPress = 1;
            printf("Button PWR long click.\n");
        }
    }
}


void Button_GPIO_Config(gpio_num_t gpio){
    gpio_pad_select_gpio(gpio);
    gpio_set_direction(gpio, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY);
}

/**
  * @brief  Button initialize
  * @param  None
  * @retval None
  */
void Button_Init()
{
    btPOWER.PinNum = CONFIG_BUTTON_KEY_PWR_PIN;
    /* Button GPIO configration. */
    Button_GPIO_Config((gpio_num_t)btPOWER.PinNum);
    /* Add button event. */
    btPOWER.EventAttach(Button_EventHandler);
}

void Button_Update(){
    btPOWER.EventMonitor((gpio_get_level((gpio_num_t)btPOWER.PinNum) == 0));
}

void Button_GetInfo(Button_Info_t* info){
    /* Set the button info. */
    info->btnPower= Button_Info.btnPower;
    /* Reset Button event. */
    Button_Info.btnPower = 0;
}