#include <main.h>



void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(ONBOARD_BUTTON, INPUT_PULLUP);


  Serial.begin(115200);
  bluetooth_init();
 
  #if USE_WIFI_MANAGER == 1
    pppTech.init();
  #endif


// CRIAÇÃO DA FILA
  xQueue_Nivel = xQueueCreate( 1, sizeof( float ) );

// CRIAÇÃO DO SEMAFORO
  xSerial_semaphore = xSemaphoreCreateMutex();


// CRIAÇÃO DAS TAREFAS
  #if USE_TASK_GERAL == 1
    vTask_Geral_start();
  #endif

    #if USE_FIREBASE == 1
      xTaskCreate( task_firebase 
                  , "taskFirebaseDebug" 
                  , TASK_FIREBASE_SIZE 
                  , NULL 
                  , 4 
                  , &handle_firebase ); 
    #endif

    #if USE_MQTT == 1
      xTaskCreate( task_mqtt 
                  , "taskMqttDebug" 
                  , TASK_MQTT_SIZE 
                  , NULL 
                  , TASK_MQTT_PRIORITY 
                  , &handle_mqtt ); 
    #endif

    #if USE_UPDATE_FIRMWARE == 1
      xTaskCreate( task_update_firmware 
                  , "taskUpdateFirmware" 
                  , TASK_UPDATE_FIRMWARE_SIZE 
                  , NULL 
                  , 2 
                  , &handle_updateFirmware ); 
    #endif

     vTask_sensor_init();

}



void loop() {
  
bluetooth_loop();
vTaskDelay(pdMS_TO_TICKS(5));

 

}