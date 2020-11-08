#include <Arduino.h>
#include <RtcDS1307.h>
#include <task.h>
//#include <device.h>


static const char *task_str = "Task task is running\r\n"; //태스크로 넘겨줄 문자열   
void vTaskTask( void *pvParameters );
SemaphoreHandle_t xTaskSemaphore = NULL;

void task_init(void)
{
    xTaskSemaphore = xSemaphoreCreateBinary();    

    xTaskCreatePinnedToCore(  vTaskTask,           //태스크를 구현한 함수에 대한 포인터  
                "Task Task",               //태스크 이름  
                4096,                   //스택 깊이  
                (void*)task_str,   //태스크에 넘결 줄 매개변수에 대한 포인터  
                1,                      //태스크의 우선순위  
                    NULL,
                    1 );    

    
                    
}

//void printDateTime(const RtcDateTime& dt);
extern RtcDS1307 Rtc;


void vTaskTask( void *pvParameters )  
{  
 //   RtcDateTime dt(2020,9,2,16,15,00);

//    Rtc.SetDateTime(dt);
    
    for( ;; )  
    {  
        xSemaphoreTake( xTaskSemaphore, portMAX_DELAY );    

        RtcDateTime now = Rtc.GetDateTime();        
        //printDateTime(now);
        Serial.println();    
    }  
}  