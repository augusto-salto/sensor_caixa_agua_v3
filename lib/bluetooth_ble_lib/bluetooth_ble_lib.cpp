#include <bluetooth_ble_lib.h>


BLECharacteristic *pCharacteristicEmail;
BLECharacteristic *pCharacteristicPassword;
BLECharacteristic *pCharacteristicName;
BLECharacteristic *pCharacteristicSSID;
BLECharacteristic *pCharacteristicSSIDPassword;
BLECharacteristic *pCharacteristicAlternativeMqttServer;
BLECharacteristic *pCharacteristicAlternativeMqtttPort;
BLECharacteristic *pCharacteristicESPrestart;
BLECharacteristic *pCharacteristicWifi;

BLEServer *pServer;
BLEService *pService;

extern FileSystemManager fileSystemManager;
extern SemaphoreHandle_t xFileSystem_semaphore;

//bool deviceConnected = false;
int humidity = 100;
int temperature = 222;
String receivBuff = "";
String received = "";



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.print("\nCLIENTE BLUETOOTH CONECTADO");
      //deviceConnected = true;
    };
 
    void onDisconnect(BLEServer* pServer) {
      //deviceConnected = false;
      Serial.print("\nCLIENTE BLUETOOTH DESCONECTADO! REINICIANDO O ESP! (BLUETOOTH_BLI_LIB)");
      vTaskDelay(pdMS_TO_TICKS(2000));
      ESP.restart();
    }

    
};


class MyCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic) 
    {
      std::string rxValue = pCharacteristic->getValue();
      String UUIDstring = pCharacteristic->getUUID().toString().c_str();
      UUIDstring.toUpperCase();

 
      if (rxValue.length() > 0) {
        
 
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
              pCharacteristicEmail->setValue("0e;true");
              pCharacteristicEmail->notify();
          }
          else
          {
              pCharacteristicEmail->setValue("0e;false");
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
                pCharacteristicPassword->setValue("1e;true");
                pCharacteristicPassword->notify();
            }
            else
            {
                pCharacteristicPassword->setValue("1e;false");
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
                pCharacteristicName->setValue("2e;true");
                pCharacteristicName->notify();
            }
            else
            {
                pCharacteristicName->setValue("2e;false");
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
                pCharacteristicSSID->setValue("3e;true");
                pCharacteristicSSID->notify();
            }
            else
            {
                pCharacteristicSSID->setValue("3e;false");
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
                pCharacteristicSSIDPassword->setValue("4e;true");
                pCharacteristicSSIDPassword->notify();
            }
            else
            {
                pCharacteristicSSIDPassword->setValue("4e;false");
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
                pCharacteristicAlternativeMqttServer->setValue("5e;true");
                pCharacteristicAlternativeMqttServer->notify();
            }
            else
            {
                pCharacteristicAlternativeMqttServer->setValue("5e;false");
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
                pCharacteristicAlternativeMqtttPort->setValue("6e;true");
                pCharacteristicAlternativeMqtttPort->notify();
            }
            else
            {
                pCharacteristicAlternativeMqtttPort->setValue("6e;false");
                pCharacteristicAlternativeMqtttPort->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);
          }

///// CHARACTERISTIC_ESP_RESTAR
          else if(UUIDstring.equals(String(CHARACTERISTIC_ESPRESTAR)))
          { 
            char sendBuffer[10];
            received.toCharArray(sendBuffer, 10);

            xSemaphoreTake(xFileSystem_semaphore, portMAX_DELAY ); 

            if(fileSystemManager.setConfigStatus(sendBuffer))
            {
                pCharacteristicESPrestart->setValue("7e;true");
                pCharacteristicESPrestart->notify();
            }
            else
            {
                pCharacteristicESPrestart->setValue("7e;false");
                pCharacteristicESPrestart->notify();
            }
            xSemaphoreGive(xFileSystem_semaphore);
                
          }    

          else if(UUIDstring.equals(String(CHARACTERISTIC_WIFI)))
          {
            char sendBuffer[10];
            received.toCharArray(sendBuffer, 10);
          Serial.print("\nWIFI SCAN REQUEST");
            char buffMsg[100] = "w";
            String buffString;
            int numNetWorks = 0;

            numNetWorks = WiFi.scanNetworks();
            if (numNetWorks == 0){
                buffString = "null";
            }else{
                for (int i = 0; i <= numNetWorks; i++)
                {
                    buffString = WiFi.SSID(i);
                    strcat(buffMsg, ";");
                    strcat(buffMsg, buffString.c_str());
                }
                pCharacteristicWifi->setValue(buffMsg);
                pCharacteristicWifi->notify();
                Serial.print("\nWIFI SCAN RESULTS: ");
                Serial.print(buffMsg);
                
                
            }
            
           
            
          }   
           
        
        
      }
 
      
    }
};

void ble_setup(){


  BLEDevice::init("PPPTECH_NIVEL_SENSOR"); // Give it a name
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), (uint32_t) 30, (uint8_t) 0);
  

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
  pCharacteristicWifi = pService->createCharacteristic(
                                         CHARACTERISTIC_WIFI,
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
  pCharacteristicWifi->setCallbacks(new MyCallbacks());
 

  pService->start();
  pServer->getAdvertising()->start();
  
  Serial.println("BLE HABILITADO!");
  
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
delete pCharacteristicWifi;
delete pServer;
delete pService;


}




    
