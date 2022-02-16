#include <task_mqtt.h>



void task_mqtt( void *pvParameters )
{
    (void) pvParameters;

    #if DEBUG_TASK_MQTT == 1
    UBaseType_t uxHighWaterMark;
    #endif

    MqttClass mqttObject;
    
    char chipIDstring[] = "0";
    

    sprintf(chipIDstring, "%lu", (long)ESP.getEfuseMac()); // CONVERTE O CHIPID PARA CHAR
    Serial.print("\nMEU CHIP ID: " + String(chipIDstring) + "\n");

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