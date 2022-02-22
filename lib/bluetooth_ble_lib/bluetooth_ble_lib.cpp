#include <bluetooth_ble_lib.h>


BLECharacteristic *pCharacteristicEmail;
BLECharacteristic *pCharacteristicPassword;
BLECharacteristic *pCharacteristicName;
BLECharacteristic *pCharacteristicSSID;
BLECharacteristic *pCharacteristicSSIDPassword;
BLECharacteristic *pCharacteristicAlternativeMqttServer;
BLECharacteristic *pCharacteristicAlternativeMqtttPort;

extern FileSystemManager fileSystemManager;

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
          

        }

///// CHARACTERISTIC_PASSWORD
          else if(UUIDstring.equals(String(CHARACTERISTIC_PASSWORD)))
          {
            char sendBuffer[EMAIL_PASSWORD_SIZE];
            received.toCharArray(sendBuffer, EMAIL_PASSWORD_SIZE);
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
          }

///// CHARACTERISTIC_NAME
          else if(UUIDstring.equals(String(CHARACTERISTIC_NAME)))
          {
            char sendBuffer[NAME_SENSOR_SIZE];
            received.toCharArray(sendBuffer, NAME_SENSOR_SIZE);
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
          }

///// CHARACTERISTIC_SSID
          else if(UUIDstring.equals(String(CHARACTERISTIC_SSID)))
          {
            char sendBuffer[SSID_NAME_SIZE];
            received.toCharArray(sendBuffer, SSID_NAME_SIZE);
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
          }

///// CHARACTERISTIC_SSIDPASSWORD
          else if(UUIDstring.equals(String(CHARACTERISTIC_SSIDPASSWORD)))
          {
            char sendBuffer[SSID_PASSWORD_SIZE];
            received.toCharArray(sendBuffer, SSID_PASSWORD_SIZE);
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
          }

///// CHARACTERISTIC_ALTERNATIVEMQTTSERVER
          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTSERVER)))
          {
            char sendBuffer[MQTT_SERVER_SIZE];
            received.toCharArray(sendBuffer, MQTT_SERVER_SIZE);
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
          }

///// CHARACTERISTIC_ALTERNATIVEMQTTPORT
          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTPORT)))
          {
            char sendBuffer[MQTT_PORT_SIZE];
            received.toCharArray(sendBuffer, MQTT_PORT_SIZE);
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

// Create the BLE Device
    //BLEDevice::setMTU(128);
  BLEDevice::init("PPPTECH_NIVEL_SENSOR"); // Give it a name
  // Configura o dispositivo como Servidor BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

 
  // Cria o servico UART
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), (uint32_t) 30, (uint8_t) 0);
  
 
 
 
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
                                       
 
  
  pCharacteristicEmail->setCallbacks(new MyCallbacks());
  pCharacteristicPassword->setCallbacks(new MyCallbacks());
  pCharacteristicName->setCallbacks(new MyCallbacks());
  pCharacteristicSSID->setCallbacks(new MyCallbacks());
  pCharacteristicSSIDPassword->setCallbacks(new MyCallbacks());
  pCharacteristicAlternativeMqttServer->setCallbacks(new MyCallbacks());
  pCharacteristicAlternativeMqtttPort->setCallbacks(new MyCallbacks());

  //pCharacteristicEmail->addDescriptor(new BLE2902());
  //pCharacteristicPassword->addDescriptor(new BLE2902());
  //pCharacteristicName->addDescriptor(new BLE2902());
  //pCharacteristicSSID->addDescriptor(new BLE2902());
  //pCharacteristicSSIDPassword->addDescriptor(new BLE2902());
  //pCharacteristicAlternativeMqttServer->addDescriptor(new BLE2902());
  //pCharacteristicAlternativeMqtttPort->addDescriptor(new BLE2902());
  

  // Inicia o serviço
  pService->start();
  
 
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  Serial.println("Esperando um cliente se conectar...");
  //pCharacteristicEmail->setValue("augusto.salto@hotmail.com");
}

void ble_loop(){


    if(humidity < 199 ){
      humidity++;
    }else{
      humidity = 1;
    }

    if (deviceConnected) {
 
     
    char humidityString[2];
    char temperatureString[2];

    dtostrf(humidity, 1, 2, humidityString);
    dtostrf(temperature, 1, 2, temperatureString);
 
    char dhtDataString[16];
    sprintf(dhtDataString, "%d,%d", temperature, humidity);
     
    //pCharacteristicEmail->setValue(dhtDataString);
    //pCharacteristicEmail->notify(); 

    // Envia o valor para o aplicativo!
    //Serial.print("*** Dado enviado: ");
    //Serial.print(dhtDataString);
    //Serial.println(" ***");
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}




    
