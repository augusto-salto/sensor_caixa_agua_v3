#include <main.h>

WifiBleManager wifiblemanager;

String teste = "";

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(ONBOARD_BUTTON, INPUT_PULLUP);


  Serial.begin(115200);
  //bluetooth_init();
  ble_setup();
  

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
  
//bluetooth_loop();
ble_loop();

teste = String(wifiblemanager.getEmail());

Serial.print("\nWIFISSID: ");
Serial.print (teste);
Serial.print ("\n");
Serial.print("\ngetEmail: ");
Serial.print (wifiblemanager.getMqttPort());
Serial.print ("\n");

vTaskDelay(pdMS_TO_TICKS(1005));

 

}