#include <task_wifi_ble_manager.h>

TaskHandle_t handle_wifi_ble_manager;

void task_wifi_ble_manager( void *pvParameters )
{
    //(void) pvParameters;

    ConnectManagerClass connectManager;
    bool checkDataIsCons = false;

    #if DEBUG_TASK_WIFI_BLE_MANAGER == 1
    UBaseType_t uxHighWaterMark;
    #endif
    
    #if FORMAT_FILE_SYSTEM == 1
    connectManager.formatFileSystem();    
    #endif
    connectManager.bleSetupAndInit();

    //xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY );  
    //xSemaphoreGive(xFileSystem_semaphore);
    
    while(!checkDataIsCons)
    {   

    vTaskDelay(pdMS_TO_TICKS(100));
#if FORMAT_FILE_SYSTEM == 0
 xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY );  

    if(!checkDataIsCons){
        if(connectManager.checkDataCons())
        {
          checkDataIsCons = true;
          connectManager.disableBleAndConectWifi();


        }
    }

xSemaphoreGive(xFileSystem_semaphore);
#endif
        #if DEBUG_TASK_WIFI_BLE_MANAGER == 1
            xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
            uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
            Serial.print("\nTASK UPDATE FIRMWARE RUNING DEBUG!");
            Serial.print("\nTASK UPDATE FIRMWARE SIZE: ");
            Serial.print(uxHighWaterMark);
            Serial.print("\n");
             vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA USO DE OUTRA TAREFA
            
        #endif
    
   vTaskDelay(pdMS_TO_TICKS(1000));

    } 
    

    
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

    //delete handle_wifi_ble_manager;
    //vPortFree(connectManager);
    vTaskDelete(NULL);
    

} // END TASK


void vTask_wifi_ble_manager_start(){

    xTaskCreate( task_wifi_ble_manager 
                  , "taskWifiBleManager" 
                  , TASK_WIFI_BLE_MANAGER_SIZE 
                  , NULL 
                  , 10 
                  , &handle_wifi_ble_manager ); 
                  
}