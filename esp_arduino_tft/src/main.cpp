#include <Arduino.h>
#include "GUI.h"
#include "image.h"
#include <lvgl.h>
//#include <../lv_examples/lv_examples.h>
//lv_log_register_print_cb()
static lv_disp_draw_buf_t draw_buf_dsc_1;
static lv_color_t draw_buf_1[128 * 50];
lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  int16_t x;
  int16_t y;
  TFT_SetRegion(area->x1,area->y1,area->x2,area->y2);
  for (y = area->y1; y <= area->y2; y++)
  {
    for (x = area->x1; x <= area->x2; x++)
    {
      TFT_WriteData_U16(color_p->full);     
      color_p++;
    }
    ESP.wdtFeed();
  }
  lv_disp_flush_ready(disp);
}
void lvgl_first_demo_start(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    //lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
    lv_label_set_text(label, "sb");                     /*Set the labels text*/


	lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label1, "hhhh!"); 
	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_align(btn, label1, LV_ALIGN_OUT_TOP_MID, 0, -10);
}
void setup()
{
  Serial.begin(9600);
  Serial.println("res+++dasda");
  TFT_Init();
  TFT_Clear(0x00);
  Gui_DrawPoint(10,10,0XFE);
  Gui_DrawPoint(10,11,0XFE);
  Gui_DrawPoint(10,12,0XFE);
  Gui_DrawPoint(10,13,0XFE);
  Gui_DrawPoint(11,10,0XFE);
  Gui_DrawPoint(11,11,0XFE);
  Gui_DrawPoint(11,12,0XFE);
  Gui_DrawPoint(11,13,0XFE);
  delay(100);
  //showimage(0, 0, 128, 71, gImage_pic);
  lv_init();
  lv_disp_draw_buf_init(&draw_buf_dsc_1, draw_buf_1, NULL, 128 * 50);
  
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/

  /*Set up the functions to access to your display*/

  /*Set the resolution of the display*/
  disp_drv.hor_res = 128;
  disp_drv.ver_res = 160;
  /*Used to copy the buffer's content to the display*/
  disp_drv.flush_cb = disp_flush;

  /*Set a display buffer*/
  disp_drv.draw_buf = &draw_buf_dsc_1;
  lv_disp_drv_register(&disp_drv);

  lvgl_first_demo_start();
}


void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("+++++++");
  lv_tick_inc(10);
  Serial.println("1111111111");
  lv_timer_handler(); /* let the GUI do its work */
  Serial.println("----------");
  //delay(5);
}