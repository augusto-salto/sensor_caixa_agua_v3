#include <task_wifi_ble_manager.h>

TaskHandle_t handle_wifi_ble_manager;

void task_wifi_ble_manager( void *pvParameters )
{
    (void) pvParameters;
    ConnectManagerClass connectManager;

    #if DEBUG_TASK_WIFI_BLE_MANAGER == 1
    UBaseType_t uxHighWaterMark;
    #endif

        
    connectManager.bleSetupAndInit();


    
    while(!connectManager.checkDataCons())
    {   

    vTaskDelay(pdMS_TO_TICKS(100));

 
  

        #if DEBUG_TASK_WIFI_BLE_MANAGER == 1
            xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
            uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
            Serial.print("\nTASK UPDATE FIRMWARE RUNING DEBUG!");
            Serial.print("\nTASK UPDATE FIRMWARE SIZE: ");
            Serial.print(uxHighWaterMark);
            Serial.print("\n");
            xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
        #endif
    
   vTaskDelay(pdMS_TO_TICKS(10));

    } 
    
    connectManager.disableBleAndConectWifi();
    // CRIAÇÃO DAS TAREFAS
  #if USE_TASK_GERAL == 1
    vTask_geral_start();
  #endif

    #if USE_FIREBASE == 1
     vTask_firebase_start();
    #endif

    #if USE_MQTT == 1
     vTask_mqtt_start();
    #endif

    #if USE_UPDATE_FIRMWARE == 1
      vTask_update_firmware_start();
    #endif

     vTask_sensor_start();

     vTaskDelete(handle_wifi_ble_manager);
     vTaskSuspend(NULL);

} // END TASK


void vTask_wifi_ble_manager_start(){

    xTaskCreate( task_wifi_ble_manager 
                  , "taskWifiBleManager" 
                  , TASK_WIFI_BLE_MANAGER_SIZE 
                  , NULL 
                  , 10 
                  , &handle_wifi_ble_manager ); 
                  
}