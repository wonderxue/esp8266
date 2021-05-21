#include <Arduino.h>
#include "i2c.h"
#include "mpu.h"
#include "tft.h"
#include "lvgl.h"
void delay_us(int x)
{
  while (x--)
    ;
}
static void disp_init(void);

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
#if LV_USE_GPU
static void gpu_blend(lv_disp_drv_t *disp_drv, lv_color_t *dest, const lv_color_t *src, uint32_t length, lv_opa_t opa);
static void gpu_fill(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_coord_t dest_width,
                     const lv_area_t *fill_area, lv_color_t color);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
  /*-------------------------
     * Initialize your display
     * -----------------------*/
  disp_init();

  /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

  /* LVGL requires a buffer where it internally draws the widgets.
     * Later this buffer will passed your display drivers `flush_cb` to copy its content to your display.
     * The buffer has to be greater than 1 display row
     *
     * There are three buffering configurations:
     * 1. Create ONE buffer with some rows:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer with some rows:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Create TWO screen-sized buffer:
     *      Similar to 2) but the buffer have to be screen sized. When LVGL is ready it will give the
     *      whole frame to display. This way you only need to change the frame buffer's address instead of
     *      copying the pixels.
     * */

  /* Example for 1) */
  // static lv_disp_buf_t draw_buf_dsc_1;
  // static lv_color_t draw_buf_1[LV_HOR_RES_MAX * 10];                          /*A buffer for 10 rows*/
  // lv_disp_buf_init(&draw_buf_dsc_1, draw_buf_1, NULL, LV_HOR_RES_MAX * 10);   /*Initialize the display buffer*/

  // /* Example for 2) */
  static lv_disp_buf_t draw_buf_dsc_2;
  static lv_color_t draw_buf_2_1[LV_HOR_RES_MAX * 20];                                /*A buffer for 10 rows*/
  static lv_color_t draw_buf_2_2[LV_HOR_RES_MAX * 20];                                /*An other buffer for 10 rows*/
  lv_disp_buf_init(&draw_buf_dsc_2, draw_buf_2_1, draw_buf_2_2, LV_HOR_RES_MAX * 20); /*Initialize the display buffer*/

  /* Example for 3) */
  // static lv_disp_buf_t draw_buf_dsc_3;
  // static lv_color_t draw_buf_3_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*A screen sized buffer*/
  // static lv_color_t draw_buf_3_2[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*An other screen sized buffer*/
  // lv_disp_buf_init(&draw_buf_dsc_3, draw_buf_3_1, draw_buf_3_2, LV_HOR_RES_MAX * LV_VER_RES_MAX);   /*Initialize the display buffer*/

  /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

  lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/

  /*Set up the functions to access to your display*/

  /*Set the resolution of the display*/
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;

  /*Used to copy the buffer's content to the display*/
  disp_drv.flush_cb = disp_flush;

  /*Set a display buffer*/
  disp_drv.buffer = &draw_buf_dsc_2;

#if LV_USE_GPU
  /*Optionally add functions to access the GPU. (Only in buffered mode, LV_VDB_SIZE != 0)*/

  /*Blend two color array using opacity*/
  disp_drv.gpu_blend_cb = gpu_blend;

  /*Fill a memory array with a color*/
  disp_drv.gpu_fill_cb = gpu_fill;
#endif

  /*Finally register the driver*/
  lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your display and the required peripherals. */
static void disp_init(void)
{
  /*You code here*/
}

/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
  /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
  unsigned short x, y;
  TFT_SetRegion(area->x1, area->y1, area->x2, area->y2);
  ESP.wdtFeed();
  //Serial.println("-----------------");
  for (y = area->y1; y <= area->y2; y++)
    for (x = area->x1; x <= area->x2; x++)
    {
      TFT_WriteData_U16(color_p->full);
      color_p++;
    }
  //Gui_DrawArea(area->x1,area->y1,area->x2,area->y2,color_p);
  // for(y = area->y1; y <= area->y2; y++) {
  //     for(x = area->x1; x <= area->x2; x++) {
  //         /* Put a pixel to the display. For example: */
  //         /* put_px(x, y, *color_p)*/
  //         #if 1
  //         #error please add display function and change 1 to 0
  //         #endif
  //         color_p++;
  //     }
  // }
  /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}
void setup()
{
  // put your setup code here, to run once:
  //GY_Init();
  Serial.begin(115200);
  TFT_Init();
  lv_init();
  //Serial.println("------aaaa------");
  lv_port_disp_init();
  //Serial.println("------bbbb------");
  lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button to the current screen*/
  lv_obj_set_pos(btn, 10, 10);                       /*Set its position*/
  lv_obj_set_size(btn, 100, 50); /*Set its size*/    /*Assign a callback to the button*/
  lv_obj_t *label = lv_label_create(btn, NULL);      /*Add a label to the button*/
  lv_label_set_text(label, "Button");
  //Serial.println("------ccccc------");
}

void loop()
{
  // put your main code here, to run repeatedly:
  lv_tick_inc(4);
  //Serial.println("------aaaa------");
  lv_task_handler();
  //Serial.println("------hhh------");
}