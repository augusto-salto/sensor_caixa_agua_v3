#include <main.h>

FileSystemManager fileSystemManager;
ConnectManagerClass connectManager;

String teste = "";
char email[EMAIL_SIZE] = "augusto.salto@hotmail.com";
bool flagTeste =  false;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(ONBOARD_BUTTON, INPUT_PULLUP);
  Serial.begin(115200);

  connectManager.bleSetupAndInit();

  while(!connectManager.checkDataCons()){
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  connectManager.disableBleAndConectWifi();
  
  //bluetooth_init();
  //ble_setup();
  
  

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
//ble_loop();
//vTaskDelay(pdMS_TO_TICKS(1000));

/*
if(fileSystemManager.isConfigured()){
  Serial.print("\n\n ********* INICIO *********");

Serial.print("\n GET E-MAIL: ");
Serial.print (fileSystemManager.getEmail());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET E-MAIL PASSWORD: ");
Serial.print (fileSystemManager.getEmailPassword());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET SSID: ");
Serial.print (fileSystemManager.getWifiSSID());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET SSID PASSWORD: ");
Serial.print (fileSystemManager.getWifiPassword());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET NAME SENSOR: ");
Serial.print (fileSystemManager.getNameSensor());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET MQTT SERVER: ");
Serial.print (fileSystemManager.getMqttServer());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n GET MQTT PORT: ");
Serial.print (fileSystemManager.getMqttPort());

vTaskDelay(pdMS_TO_TICKS(200));

Serial.print("\n ********* FIM *********");
}

Serial.print("\n ********* CHECANDO CONSISTENCIA DE DADOS *********");

if(!connectManager.checkDataCons())
{
  Serial.print("\nExistem dados inconsistentes!");
}else if(!flagTeste){
  Serial.print("\nDados checados com exito, desabilitando bluetooth e habilitando o wifi!");
  connectManager.disableBleAndConectWifi();
  flagTeste = true;
}
*/
//Serial.print("\nWIFI CONECTADO! TO NO LOOP!");
//Serial.print("\nIP LOCAL: ");
//Serial.print(WiFi.localIP());
//Serial.print("\n");




vTaskDelay(pdMS_TO_TICKS(5));

 

}