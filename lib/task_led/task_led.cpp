#include <task_led.h>

LedIndication ledIndicator;

void task_led( void *pvParameters )
{
    
    

    while(1)
    {   
        ledIndicator.applyLedState();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
        
        

}


void vTask_led_start(){

xTaskCreate( task_led /* Funcao a qual esta implementado o que a tarefa deve fazer */
                , "taskLedDebug" /* Nome (para fins de debug, se necessário) */
                , 2000 /* Tamanho da stack (em words) reservada para essa tarefa */
                , NULL /* Parametros passados (nesse caso, não há) */
                , 1 /* Prioridade */
                , NULL ); /* Handle da tarefa, opcional  */

    
}