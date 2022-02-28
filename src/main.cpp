#include <main.h>



void setup() 
{
  
  // CRIAÇÃO DAS FILAS
  xQueue_Nivel = xQueueCreate( 1, sizeof( float ) );
  xQueue_android_request = xQueueCreate( 1, sizeof( char[5] ) );
  xQueue_light_indication = xQueueCreate(1, sizeof (int));

// CRIAÇÃO DOS SEMAFOROS
  xSerial_semaphore = xSemaphoreCreateMutex();
  xFileSystem_semaphore = xSemaphoreCreateMutex();
  xInitialize_semaphore = xSemaphoreCreateMutex();
  xLed_semaphore = xSemaphoreCreateMutex();


  vTask_led_start();


 
  Serial.begin(115200);

  #if USE_WIFI_MANAGER == 1
    pppTech.init();
  #endif




  vTask_wifi_ble_manager_start();


/*

WiFi.begin("NINO", "ra201291");
while (WiFi.status() != WL_CONNECTED)
{
  Serial.println(".");
  vTaskDelay(pdMS_TO_TICKS(500));
}
vTask_update_firmware_start();
vTask_mqtt_start();
vTask_sensor_start();
vTask_geral_start();
*/




}



void loop() {

vTaskDelay(pdMS_TO_TICKS(10));

 
}