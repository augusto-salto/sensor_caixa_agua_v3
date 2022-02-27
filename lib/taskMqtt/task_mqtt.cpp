#include <task_mqtt.h>

TaskHandle_t handle_mqtt;


void task_mqtt( void *pvParameters )
{
    char buff_android_request[5];
    float nivel = 0.0;

    #if DEBUG_TASK_MQTT == 1
    UBaseType_t uxHighWaterMark;
    #endif

    MqttClass mqttObject;

// INICIA O MQTT
xSemaphoreTake(xInitialize_semaphore, portMAX_DELAY);
    mqttObject.begin();
xSemaphoreGive(xInitialize_semaphore);
    
    while(1)
    {   
        mqttObject.isConected();
        mqttObject.loop();

        xQueueReceive(xQueue_android_request, (void *)&buff_android_request, pdMS_TO_TICKS(100));  

        if(String(buff_android_request).equals("n")){

            xQueueReceive(xQueue_Nivel, (void *)&nivel, portMAX_DELAY);
            char buffMsg[10];
            char floatToChar[5];

            strcpy(buffMsg, "n;");
            dtostrf(nivel, 5,2, floatToChar);
            strcat(buffMsg, floatToChar);

            mqttObject.publishMsg(buffMsg);

            // LIMPA O BUFFER REQUEST
            strcpy(buff_android_request, "0");
            xQueueOverwrite(xQueue_android_request, (void *)&buff_android_request);   
        }

       
    #if DEBUG_TASK_MQTT == 1
        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nTASK MQTT RUNING");
        Serial.print("\nTASK MQTT highWaterMark: ");
        Serial.print(uxHighWaterMark);
        Serial.print("\n");
        xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
    #endif

        //vTaskDelay( 1 / portTICK_PERIOD_MS );
        
    }
}

void vTask_mqtt_start(){

 xTaskCreate( task_mqtt 
                  , "taskMqttDebug" 
                  , TASK_MQTT_SIZE 
                  , NULL 
                  , TASK_MQTT_PRIORITY 
                  , &handle_mqtt ); 

}

