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


// CRIAÇÃO DAS FILAS
  xQueue_Nivel = xQueueCreate( 1, sizeof( float ) );

// CRIAÇÃO DOS SEMAFOROS
  xSerial_semaphore = xSemaphoreCreateMutex();


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

}



void loop() {
  
bluetooth_loop();
vTaskDelay(pdMS_TO_TICKS(5));

 

}