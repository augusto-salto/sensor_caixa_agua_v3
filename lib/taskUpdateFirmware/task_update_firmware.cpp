#include <task_update_firmware.h>

#include <update_firmware.h>

TaskHandle_t handle_updateFirmware;
light_indication up_firm_status;

void task_update_firmware( void *pvParameters )
{
    
    up_firm_status = light_indication::initializing;
    ledIndicator.setMqttStatus(up_firm_status);

    #if DEBUG_TASK_UPDATE_FIRMWARE == 1
    UBaseType_t uxHighWaterMark;
    #endif

  

    
    while(1)
    {   
        up_firm_status = light_indication::running;
        ledIndicator.setUpdateStatus(up_firm_status);

        xSemaphoreTake(xInitialize_semaphore, portMAX_DELAY);

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
        xSemaphoreGive(xInitialize_semaphore);   

        

        #if DEBUG_TASK_UPDATE_FIRMWARE == 1
            xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
            uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
            Serial.print("\nTASK UPDATE FIRMWARE RUNING DEBUG!");
            Serial.print("\nTASK UPDATE FIRMWARE SIZE: ");
            Serial.print(uxHighWaterMark);
            Serial.print("\n");
            xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
        #endif
    
   vTaskDelay(pdMS_TO_TICKS(180000));

    } // END WHILE(1)
} // END TASK


void vTask_update_firmware_start(){

    xTaskCreate( task_update_firmware 
                  , "taskUpdateFirmware" 
                  , TASK_UPDATE_FIRMWARE_SIZE 
                  , NULL 
                  , 10 
                  , &handle_updateFirmware ); 
                  
}
