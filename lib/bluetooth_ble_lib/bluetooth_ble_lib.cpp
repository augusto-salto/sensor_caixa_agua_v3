#include <bluetooth_ble_lib.h>


BLECharacteristic *pCharacteristicEmail;
BLECharacteristic *pCharacteristicPassword;
BLECharacteristic *pCharacteristicName;
BLECharacteristic *pCharacteristicSSID;
BLECharacteristic *pCharacteristicSSIDPassword;
BLECharacteristic *pCharacteristicAlternativeMqttServer;
BLECharacteristic *pCharacteristicAlternativeMqtttPort;
BLECharacteristic *pCharacteristicESPrestart;

BLEServer *pServer;
BLEService *pService;

extern FileSystemManager fileSystemManager;
extern SemaphoreHandle_t xFileSystem_semaphore;

bool deviceConnected = false;
int humidity = 100;
int temperature = 222;
String receivBuff = "";
String received = "";



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
 
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }

    
};


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      //String varBuffer;
      //String valueBuffer;
      String UUIDstring = pCharacteristic->getUUID().toString().c_str();
      UUIDstring.toUpperCase();

 
      if (rxValue.length() > 0) {

        //Serial.print("\n*** MENSAGEM RECEBIDA! *** ");
        //Serial.print("\nCharacteristic UUID: ");
        //Serial.print(pCharacteristic->getUUID().toString().c_str());
        
 
        for (int i = 0; i < rxValue.length(); i++) {
          //Serial.print(rxValue[i]);
          receivBuff += rxValue[i];
        }

        received = receivBuff;
        receivBuff = "";


///// CHARACTERISTIC_EMAIL
        if(UUIDstring.equals(String(CHARACTERISTIC_EMAIL)))
        {
          char sendBuffer[EMAIL_SIZE];
          received.toCharArray(sendBuffer, EMAIL_SIZE);

          xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY );

          if(fileSystemManager.setEmail(sendBuffer))
          {
              pCharacteristicEmail->setValue("true");
              pCharacteristicEmail->notify();
          }
          else
          {
              pCharacteristicEmail->setValue("false");
              pCharacteristicEmail->notify();
          }

          xSemaphoreGive(xFileSystem_semaphore);

        }

///// CHARACTERISTIC_PASSWORD
          else if(UUIDstring.equals(String(CHARACTERISTIC_PASSWORD)))
          {
            char sendBuffer[EMAIL_PASSWORD_SIZE];
            received.toCharArray(sendBuffer, EMAIL_PASSWORD_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY );  

            if(fileSystemManager.setEmailPassword(sendBuffer))
            {
                pCharacteristicPassword->setValue("true");
                pCharacteristicPassword->notify();
            }
            else
            {
                pCharacteristicPassword->setValue("false");
                pCharacteristicPassword->notify();
            }

            xSemaphoreGive(xFileSystem_semaphore);

          }

///// CHARACTERISTIC_NAME
          else if(UUIDstring.equals(String(CHARACTERISTIC_NAME)))
          {
            char sendBuffer[NAME_SENSOR_SIZE];
            received.toCharArray(sendBuffer, NAME_SENSOR_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 

            if(fileSystemManager.setNameSensor(sendBuffer))
            {
                pCharacteristicName->setValue("true");
                pCharacteristicName->notify();
            }
            else
            {
                pCharacteristicName->setValue("false");
                pCharacteristicName->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore); 
          }

///// CHARACTERISTIC_SSID
          else if(UUIDstring.equals(String(CHARACTERISTIC_SSID)))
          {
            char sendBuffer[SSID_NAME_SIZE];
            received.toCharArray(sendBuffer, SSID_NAME_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 
            if(fileSystemManager.setWifiSSID(sendBuffer))
            {
                pCharacteristicSSID->setValue("true");
                pCharacteristicSSID->notify();
            }
            else
            {
                pCharacteristicSSID->setValue("false");
                pCharacteristicSSID->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);

          }

///// CHARACTERISTIC_SSIDPASSWORD
          else if(UUIDstring.equals(String(CHARACTERISTIC_SSIDPASSWORD)))
          {
            char sendBuffer[SSID_PASSWORD_SIZE];
            received.toCharArray(sendBuffer, SSID_PASSWORD_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 

            if(fileSystemManager.setWifiPassword(sendBuffer))
            {
                pCharacteristicSSIDPassword->setValue("true");
                pCharacteristicSSIDPassword->notify();
            }
            else
            {
                pCharacteristicSSIDPassword->setValue("false");
                pCharacteristicSSIDPassword->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);
          }

///// CHARACTERISTIC_ALTERNATIVEMQTTSERVER
          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTSERVER)))
          {

            char sendBuffer[MQTT_SERVER_SIZE];
            received.toCharArray(sendBuffer, MQTT_SERVER_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 

            if(fileSystemManager.setMqttServer(sendBuffer))
            {
                pCharacteristicAlternativeMqttServer->setValue("true");
                pCharacteristicAlternativeMqttServer->notify();
            }
            else
            {
                pCharacteristicAlternativeMqttServer->setValue("false");
                pCharacteristicAlternativeMqttServer->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);
          }

///// CHARACTERISTIC_ALTERNATIVEMQTTPORT
          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTPORT)))
          {
            char sendBuffer[MQTT_PORT_SIZE];
            received.toCharArray(sendBuffer, MQTT_PORT_SIZE);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 

            if(fileSystemManager.setMqttPort(sendBuffer))
            {
                pCharacteristicAlternativeMqtttPort->setValue("true");
                pCharacteristicAlternativeMqtttPort->notify();
            }
            else
            {
                pCharacteristicAlternativeMqtttPort->setValue("false");
                pCharacteristicAlternativeMqtttPort->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);
          }

///// CHARACTERISTIC_ESP_RESTAR
          else if(UUIDstring.equals(String(CHARACTERISTIC_ESPRESTAR)))
          {
                
                pCharacteristicESPrestart->setValue("true");
                pCharacteristicESPrestart->notify();
                vTaskDelay(pdMS_TO_TICKS(2000));
                ESP.restart();
          }       
           
        
        
      }
 
      // Processa o caracter recebido do aplicativo. Se for A acende o LED. B apaga o LED
    /*  if (rxValue.find("A") != -1) { 
        Serial.println("Turning ON!");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if (rxValue.find("B") != -1) {
        Serial.println("Turning OFF!");
        digitalWrite(LED_BUILTIN, LOW);
      }*/
    }
};

void ble_setup(){
Serial.print("\nBLE SETUP -> 1: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
// Create the BLE Device
    //BLEDevice::setMTU(128);
  BLEDevice::init("PPPTECH_NIVEL_SENSOR"); // Give it a name
  // Configura o dispositivo como Servidor BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

 
  // Cria o servico UART
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), (uint32_t) 30, (uint8_t) 0);
  
 Serial.print("\nBLE SETUP -> 2: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
 
 
  // cria uma característica BLE para recebimento dos dados
 


  pCharacteristicEmail = pService->createCharacteristic(
                                         CHARACTERISTIC_EMAIL,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );      

  

  pCharacteristicPassword = pService->createCharacteristic(
                                         CHARACTERISTIC_PASSWORD,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );  

  pCharacteristicName = pService->createCharacteristic(
                                         CHARACTERISTIC_NAME,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );     

  pCharacteristicSSID = pService->createCharacteristic(
                                         CHARACTERISTIC_SSID,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );                                                                        

  pCharacteristicSSIDPassword = pService->createCharacteristic(
                                         CHARACTERISTIC_SSIDPASSWORD,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );  


  pCharacteristicAlternativeMqttServer = pService->createCharacteristic(
                                         CHARACTERISTIC_ALTERNATIVEMQTTSERVER,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );     

  pCharacteristicAlternativeMqtttPort = pService->createCharacteristic(
                                         CHARACTERISTIC_ALTERNATIVEMQTTPORT,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );    

  pCharacteristicESPrestart = pService->createCharacteristic(
                                         CHARACTERISTIC_ESPRESTAR,
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );                                                                              
                                       
 
  
  pCharacteristicEmail->setCallbacks(new MyCallbacks());
  pCharacteristicPassword->setCallbacks(new MyCallbacks());
  pCharacteristicName->setCallbacks(new MyCallbacks());
  pCharacteristicSSID->setCallbacks(new MyCallbacks());
  pCharacteristicSSIDPassword->setCallbacks(new MyCallbacks());
  pCharacteristicAlternativeMqttServer->setCallbacks(new MyCallbacks());
  pCharacteristicAlternativeMqtttPort->setCallbacks(new MyCallbacks());
  pCharacteristicESPrestart->setCallbacks(new MyCallbacks());
  Serial.print("\nBLE SETUP -> 3: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
  pService->start();
  
 Serial.print("\nBLE SETUP -> 4: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  Serial.print("\nBLE SETUP -> 5: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
  Serial.println("BLE HABILITADO!");
  //pCharacteristicEmail->setValue("augusto.salto@hotmail.com");
}





void deleteBle()
{
delete pServer;
delete pCharacteristicEmail;
delete pCharacteristicPassword;
delete pCharacteristicName;
delete pCharacteristicSSID;
delete pCharacteristicSSIDPassword;
delete pCharacteristicAlternativeMqttServer;
delete pCharacteristicAlternativeMqtttPort;
delete pCharacteristicESPrestart;
delete pServer;
delete pService;


}




    
