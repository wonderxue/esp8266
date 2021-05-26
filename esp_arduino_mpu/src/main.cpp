#include <Arduino.h>
#include "i2c.h"
#include "mpu.h"
#include "tft.h"
#include "lvgl.h"
#include "lvgl/porting/lv_port_disp.h"

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#ifdef __cplusplus
extern "C" {
#endif
void delayUs(int x)
{
  while (x--)
    ;
}
void ErrorReport(char *source,char *code)
{
  Serial.println("---Error---");
  Serial.println(source);
  Serial.println(code);
}
#ifdef __cplusplus
}
#endif
void setup()
{
  // put your setup code here, to run once:
  //GY_Init();
  Serial.begin(115200);
  tftInit();
  lv_init();
  lv_port_disp_init();
  lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button to the current screen*/
  lv_obj_set_pos(btn, 10, 10);                       /*Set its position*/
  lv_obj_set_size(btn, 100, 50); /*Set its size*/    /*Assign a callback to the button*/
  lv_obj_t *label = lv_label_create(btn, NULL);      /*Add a label to the button*/
  lv_label_set_text(label, "Button");
}

void loop()
{
  // put your main code here, to run repeatedly:
  lv_tick_inc(10);
  lv_task_handler();
}