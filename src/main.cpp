#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
//#include <devIO.h>
//#include <card.h>
//#include <device.h>
#include <task.h>
#include <lv_examples.h>

LV_FONT_DECLARE(Japan1);
#define LVGL_TICK_PERIOD 60

//Ticker tick; /* timer for interrupt handler */
TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

lv_obj_t * slider_label;
int screenWidth = 480;
int screenHeight = 320;
  
#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char * file, uint32_t line, const char * dsc)
{

  Serial.printf("%s@%d->%s\r\n", file, line, dsc);
  delay(100);
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint16_t c;

  tft.startWrite(); /* Start new TFT transaction */
  tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      c = color_p->full;
      tft.writeColor(c, 1);
      color_p++;
    }
  }
  tft.endWrite(); /* terminate TFT transaction */
  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch(&touchX, &touchY, 600);

    if(!touched)
    {
      return false;
    }

    if(touchX>screenWidth || touchY > screenHeight)
    {
      Serial.println("Y or y outside of expected parameters..");
      Serial.print("y:");
      Serial.print(touchX);
      Serial.print(" x:");
      Serial.print(touchY);
    }
    else
    {

      data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
  
      /*Save the state and save the pressed coordinate*/
      //if(data->state == LV_INDEV_STATE_PR) touchpad_get_xy(&last_x, &last_y);
     
      /*Set the coordinates (if released use the last pressed coordinates)*/
      data->point.x = touchX;
      data->point.y = touchY;
  
   //   Serial.print("Data x");
   //   Serial.println(touchX);
      
   //   Serial.print("Data y");
   //   Serial.println(touchY);

    }

    return false; /*Return `false` because we are not buffering and no more data to read*/
}


static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked\n");
    }
    else if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Toggled\n");
    }
}

void lv_ex_btn_t(void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    //lv_label_set_text(label, "Button");
    lv_label_set_text(label, "次のページへ");

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    //lv_label_set_text(label, "Toggled");
    lv_label_set_text(label, "テスト20");

    
    
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn3, event_handler);
    lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, 120);
    lv_btn_set_checkable(btn3, true);
    lv_btn_toggle(btn3);
    lv_btn_set_fit2(btn3, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn3, NULL);
    //lv_label_set_text(label, "Toggled");
    lv_label_set_text(label, "テスト30");
}


void lv_ex_btn_t02(void)
{
    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1, NULL);
    //lv_label_set_text(label, "Button");
    lv_label_set_text(label, "前のページへ");

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    //lv_label_set_text(label, "Toggled");
    lv_label_set_text(label, "テスト20");

    
    
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn3, event_handler);
    lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, 120);
    lv_btn_set_checkable(btn3, true);
    lv_btn_toggle(btn3);
    lv_btn_set_fit2(btn3, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn3, NULL);
    //lv_label_set_text(label, "Toggled");
    lv_label_set_text(label, "テスト30");
}


int test=0;

void setup() {


  ledcSetup(10, 5000/*freq*/, 10 /*resolution*/);
  ledcAttachPin(32, 10);
  analogReadResolution(10);
  ledcWrite(10,768);

  Serial.begin(115200); /* prepare for possible serial debug */

  lv_init();

  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif

  tft.begin(); /* TFT init */
  tft.setRotation(3);
  //tft.setRotation(1);

  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch(calData);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

  lv_ex_btn_t();

  #if 0
  io_init();
  
  
  card_init();
 // card_set_cb(card_handler);
  device_init();
  #endif

  task_init();
}



void loop() {

  lv_task_handler(); /* let the GUI do its work */
  delay(5);
}
