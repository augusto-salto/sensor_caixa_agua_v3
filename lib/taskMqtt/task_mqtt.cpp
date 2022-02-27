#include <task_mqtt.h>

TaskHandle_t handle_mqtt;


void task_mqtt( void *pvParameters )
{
    char buff_android_request[5] = "0";
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
            char buffMsg[15] = "n;";
            char floatToChar[5];
            String buffString;

            
            dtostrf(nivel, 5,1, floatToChar);
            buffString = floatToChar;
            buffString.trim();
            strcat(buffMsg, buffString.c_str());
            
            mqttObject.publishMsg(buffMsg);
            Serial.print("\nMENSAGEM ENVIADA AO ANDROID: ");
            Serial.print(buffMsg);
            Serial.print("\n");
            
            // LIMPA O BUFFER REQUEST
            strcpy(buff_android_request, "0");
            
            xQueueOverwrite(xQueue_android_request, (void *)&buff_android_request);   
            
            
        } else if(String(buff_android_request).equals("s")){
            
            char buffMsg[15] = "s;";
            String buffString;

            buffString = WiFi.RSSI();

            strcat(buffMsg, buffString.c_str());
            mqttObject.publishMsg(buffMsg);
            Serial.print("\nMENSAGEM ENVIADA AO ANDROID: ");
            Serial.print(buffMsg);
            Serial.print("\n");
            
            // LIMPA O BUFFER REQUEST
            strcpy(buff_android_request, "0");
            
            xQueueOverwrite(xQueue_android_request, (void *)&buff_android_request);   
            
        } else if(String(buff_android_request).equals("v")){
            
            char buffMsg[15] = "v;";
            String buffString;

            buffString = FIRMWARE_VERSION;

            strcat(buffMsg, buffString.c_str());
            mqttObject.publishMsg(buffMsg);
            Serial.print("\nMENSAGEM ENVIADA AO ANDROID: ");
            Serial.print(buffMsg);
            Serial.print("\n");
            
            // LIMPA O BUFFER REQUEST
            strcpy(buff_android_request, "0");
            
            xQueueOverwrite(xQueue_android_request, (void *)&buff_android_request);   
            
        } else if(String(buff_android_request).equals("f")){
            
            char buffMsg[15] = "f;";
            String buffString;

            buffString = "factory";

            strcat(buffMsg, buffString.c_str());
            mqttObject.publishMsg(buffMsg);
            Serial.print("\nMENSAGEM ENVIADA AO ANDROID: ");
            Serial.print(buffMsg);
            Serial.print("\n");
            
            fileSystemManager.format();
            vTaskDelay(pdMS_TO_TICKS(1500));
            ESP.restart();


            
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

