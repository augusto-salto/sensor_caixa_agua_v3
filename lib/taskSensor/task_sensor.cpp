#include <task_sensor.h>

TaskHandle_t handle_sensor;
light_indication task_sensor_status;

void task_sensor( void *pvParameters )
{
    (void) pvParameters;

    task_sensor_status = light_indication::initializing;
    ledIndicator.setMqttStatus(task_sensor_status);

    float nivel_send = 0.0;

    #if DEBUG_TASK_SENSOR == 1
    UBaseType_t uxHighWaterMark;
    #endif

    while(1)
    {   
        
    task_sensor_status = light_indication::running;
    ledIndicator.setMqttStatus(task_sensor_status);

        if(nivel_send <= 500.0){
            nivel_send++;
            vTaskDelay( 500 / portTICK_PERIOD_MS );
        }else{
            nivel_send = 0.0;
            vTaskDelay( 500 / portTICK_PERIOD_MS );
        }

        xQueueOverwrite(xQueue_Nivel, (void *)&nivel_send);                                 // ESCREVE NA FILA A VARIAVEL NIVEL

    #if DEBUG_TASK_SENSOR == 1
        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nTASK2 NIVEL: " + String(nivel_send));
        Serial.print("\nTASK2 highWaterMark: ");
        Serial.print(uxHighWaterMark);
        Serial.print("\n");
        xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
    #endif

        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        
    }
}


void vTask_sensor_start(){


 xTaskCreate( task_sensor /* Funcao a qual esta implementado o que a tarefa deve fazer */
                  , "taskSensorDebug" /* Nome (para fins de debug, se necessário) */
                  , TASK_SENSOR_SIZE /* Tamanho da stack (em words) reservada para essa tarefa */
                  , NULL /* Parametros passados (nesse caso, não há) */
                  , 3 /* Prioridade */
                  , &handle_sensor ); /* Handle da tarefa, opcional */


}