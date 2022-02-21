#include <main.h>

WifiBleManager wifiblemanager;

String teste = "";
char email[EMAIL_SIZE] = "augusto.salto@hotmail.com";

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
vTaskDelay(pdMS_TO_TICKS(3000));

teste = String(wifiblemanager.getEmail());
vTaskDelay(pdMS_TO_TICKS(500));
wifiblemanager.setEmail(email);
vTaskDelay(pdMS_TO_TICKS(500));

Serial.print("\nTESTE E-MAIL: ");
Serial.print (teste);
Serial.print ("\n");
Serial.print("\nNOVO E-MAIL: ");
Serial.print (wifiblemanager.getEmail());
Serial.print ("\n");


vTaskDelay(pdMS_TO_TICKS(1005));

 

}