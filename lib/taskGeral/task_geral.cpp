#include <task_geral.h>

TaskHandle_t handle_geral;


void task_geral( void *pvParameters )
{
    
    
    bool flagTaskStop = false;
    


    while(1)
    {   
        
        
        

        if(WiFi.status() != WL_CONNECTED){

            ledIndication.wifi_not_conected();
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
            ledIndication.running();
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
    ledIndication.running();
}
//#endif

/// TRATAMENTO DO BOTÃO ONBOARD!

        if(digitalRead(0) == LOW) {
           vTaskDelete(handle_firebase);
            vTaskDelete(handle_sensor);

            //pppTech.formatFileSystem();
            //pppTech.resetWifiManager();

            xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );   
            Serial.print("\nFILE SYSTEM FORMATADO E WIFIMANAGER RESETADO, REINICIANDO O ESP......");
            xSemaphoreGive(xSerial_semaphore);

            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            vTaskDelay( 1000 / portTICK_PERIOD_MS ); 

            ESP.restart();

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