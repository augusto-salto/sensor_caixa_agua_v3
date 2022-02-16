#include <task_update_firmware.h>

#include <update_firmware.h>


void task_update_firmware( void *pvParameters )
{
    (void) pvParameters;

    #if DEBUG_TASK_UPDATE_FIRMWARE == 1
    UBaseType_t uxHighWaterMark;
    #endif

        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
            Serial.print("\nTASK UPDATE FIRMWARE RUNING!");
            Serial.print("\nFIRMWARE CURRENT VERSION: ");
            Serial.print(FirmwareVer);
            Serial.print("\n");
        xSemaphoreGive(xSerial_semaphore);  




    
    while(1)
    {   

            if(FirmwareVersionCheck())
            {
                    vTaskDelete(handle_geral);
                    vTaskDelete(handle_sensor);
                #if USE_FIREBASE == 1
                    vTaskDelete(handle_firebase); 
                #endif

                #if USE_MQTT == 1
                    vTaskDelete(handle_mqtt);   
                #endif

            firmwareUpdate();

            }
            //xSemaphoreGive(xSerial_semaphore);  

        #if DEBUG_TASK_UPDATE_FIRMWARE == 1
            xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
            uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
            Serial.print("\nTASK UPDATE FIRMWARE RUNING DEBUG!");
            Serial.print("\nTASK UPDATE FIRMWARE SIZE: ");
            Serial.print(uxHighWaterMark);
            Serial.print("\n");
            xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
        #endif
    
   vTaskDelay(pdMS_TO_TICKS(30000));

    } // END WHILE(1)
} // END TASK