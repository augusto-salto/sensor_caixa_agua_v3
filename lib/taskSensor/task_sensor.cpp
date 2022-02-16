#include <task_sensor.h>



void task_sensor( void *pvParameters )
{
    (void) pvParameters;
    float nivel_send = 0.0;

    #if DEBUG_TASK_SENSOR == 1
    UBaseType_t uxHighWaterMark;
    #endif

    while(1)
    {   
        
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