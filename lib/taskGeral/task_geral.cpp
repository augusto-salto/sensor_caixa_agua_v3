#include <task_geral.h>

TaskHandle_t handle_geral;
light_indication task_geral_status;



void task_geral( void *pvParameters )
{
    
    task_geral_status = light_indication::initializing;
    ledIndicator.setGeralStatus(task_geral_status);

    bool flagTaskStop = false;
     pinMode(ONBOARD_BUTTON, INPUT_PULLUP);


    while(1)
    {   
        
        
        

        if(WiFi.status() != WL_CONNECTED){

            task_geral_status = light_indication::wifi_not_conected;
            ledIndicator.setGeralStatus(task_geral_status);

            if(!flagTaskStop){
                
                #if USE_FIREBASE == 1
                vTaskDelete(handle_firebase); 
                xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );  
                Serial.print("\nSEM WIFI! TASK FIREBASE DELETADA!");
                xSemaphoreGive(xSerial_semaphore);
                flagTaskStop = true;
                #endif 

                 #if USE_MQTT == 1
                vTaskDelete(handle_mqtt); 
                 xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );  
                Serial.print("\nSEM WIFI! TASK MQTT!");
                xSemaphoreGive(xSerial_semaphore);
                flagTaskStop = true;
                #endif 

               
            }

        }else if(WiFi.status() == WL_CONNECTED && flagTaskStop)
        {
            task_geral_status = light_indication::running;
            ledIndicator.setGeralStatus(task_geral_status);

            #if USE_FIREBASE == 1
                xTaskCreate( task_firebase 
                   , "taskFirebaseDebug" 
                    , TASK_FIREBASE_SIZE 
                    , NULL 
                    , 4 
                    , &handle_firebase ); 
            
                xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );   
                Serial.print("\nTASK FIREBASE CRIADA!");
                xSemaphoreGive(xSerial_semaphore);
                flagTaskStop = false; 
            #endif

            #if USE_MQTT == 1
                xTaskCreate( task_mqtt 
                   , "taskFirebaseDebug" 
                    , TASK_MQTT_SIZE 
                    , NULL 
                    , TASK_MQTT_PRIORITY 
                    , &handle_mqtt); 

                xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );   
                Serial.print("\nTASK 1 criada!");
                xSemaphoreGive(xSerial_semaphore);
                flagTaskStop = false; 
            #endif
                
}

if(WiFi.status() == WL_CONNECTED){
    task_geral_status = light_indication::running;
    ledIndicator.setGeralStatus(task_geral_status);
}
//#endif

/// TRATAMENTO DO BOTÃO ONBOARD!

        if(digitalRead(ONBOARD_BUTTON) == LOW) {
            task_geral_status = light_indication::working;
            ledIndicator.setGeralStatus(task_geral_status);

            Serial.print("ESTAGIO 1 DO BOTAO, CUIDADO VAI FORMATA");
            vTaskDelay(pdMS_TO_TICKS(6000));

            if(digitalRead(ONBOARD_BUTTON) == LOW)
            {

                #if USE_FIREBASE == 1
                    vTaskDelete(handle_firebase);
                #endif

                #if USE_MQTT == 1
                    vTaskDelete(handle_mqtt);
                #endif

                #if  USE_UPDATE_FIRMWARE == 1
                    vTaskDelete(handle_updateFirmware);
                #endif
                    vTaskDelete(handle_sensor);

                    FileSystemManager fileSystemManagerTaskGeral;
                    fileSystemManagerTaskGeral.format();

                    xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );   
                    Serial.print("\nFILE SYSTEM FORMATADO E WIFIMANAGER RESETADO, REINICIANDO O ESP......");
                    xSemaphoreGive(xSerial_semaphore);

                    vTaskDelay(pdMS_TO_TICKS(3000));

                    ESP.restart();

            } else
                {
                    task_geral_status = light_indication::running;
                    ledIndicator.setGeralStatus(task_geral_status);
                }   

        }

    vTaskDelay( 50 / portTICK_PERIOD_MS ); 

    }

}


void vTask_geral_start(){

xTaskCreate( task_geral /* Funcao a qual esta implementado o que a tarefa deve fazer */
                , "taskGeralDebug" /* Nome (para fins de debug, se necessário) */
                , 2000 /* Tamanho da stack (em words) reservada para essa tarefa */
                , NULL /* Parametros passados (nesse caso, não há) */
                , 4 /* Prioridade */
                , &handle_geral ); /* Handle da tarefa, opcional  */

    
}