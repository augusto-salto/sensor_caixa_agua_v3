#include <task_mqtt.h>

TaskHandle_t handle_mqtt;

void task_mqtt( void *pvParameters )
{
    (void) pvParameters;

    #if DEBUG_TASK_MQTT == 1
    UBaseType_t uxHighWaterMark;
    #endif

    MqttClass mqttObject;
    
    char chipIDstring[] = "0";
    sprintf(chipIDstring, "%lu", (long)ESP.getEfuseMac()); // CONVERTE O CHIPID PARA CHAR
    mqttObject.setID(chipIDstring);
    mqttObject.begin();
    
    while(1)
    {   
        mqttObject.isConected();
        mqttObject.loop();


       
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