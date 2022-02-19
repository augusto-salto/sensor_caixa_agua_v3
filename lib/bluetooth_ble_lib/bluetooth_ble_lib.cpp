#include <bluetooth_ble_lib.h>


BLECharacteristic *pCharacteristic;
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
      String varBuffer;
      String valueBuffer;
      String UUIDstring = pCharacteristic->getUUID().toString().c_str();
      UUIDstring.toUpperCase();

      
      
      //Serial.println(rxValue[0]);
 
      if (rxValue.length() > 0) {
        Serial.print("\n*** MENSAGEM RECEBIDA! *** ");
        Serial.print("\nCharacteristic UUID: ");
        Serial.print(pCharacteristic->getUUID().toString().c_str());
        Serial.print("\nMsg length: " + String(rxValue.length()));
        //Serial.print("\nReceived Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          //Serial.print(rxValue[i]);
          receivBuff += rxValue[i];
        }

        varBuffer = receivBuff.substring(0, receivBuff.indexOf(":"));
        valueBuffer = receivBuff.substring(receivBuff.indexOf(":")+1);
        received = receivBuff;
        receivBuff = "";

        if(UUIDstring.equals(String(CHARACTERISTIC_EMAIL)))
        {
          Serial.print("\nEmail: ");
          Serial.print(received);
          Serial.print("\n");
        }
          else if(UUIDstring.equals(String(CHARACTERISTIC_PASSWORD)))
          {
          Serial.print("\nPASSWORD: ");
          Serial.print(received);
          Serial.print("\n");
          }

          else if(UUIDstring.equals(String(CHARACTERISTIC_NAME)))
          {
          Serial.print("\nNAME: ");
          Serial.print(received);
          Serial.print("\n");
          }

          else if(UUIDstring.equals(String(CHARACTERISTIC_SSID)))
          {
          Serial.print("\nSSID: ");
          Serial.print(received);
          Serial.print("\n");
          }

          else if(UUIDstring.equals(String(CHARACTERISTIC_SSIDPASSWORD)))
          {
          Serial.print("\nSSID PASSWORD: ");
          Serial.print(received);
          Serial.print("\n");
          }

          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTSERVER)))
          {
          Serial.print("\nALTERNATIVE MQTT SERVER: ");
          Serial.print(received);
          Serial.print("\n");
          }

          else if(UUIDstring.equals(String(CHARACTERISTIC_ALTERNATIVEMQTTPORT)))
          {
          Serial.print("\nALTERNATIVE MQTT PORT: ");
          Serial.print(received);
          Serial.print("\n");
          }

          
        
        //Serial.print("\nVARIAVEL: " + varBuffer);
        //Serial.print("\nVALOR: " + valueBuffer);
        //Serial.print("\nString de teste: " + received);
        //Serial.print("\n");
      }
 
      // Processa o caracter recebido do aplicativo. Se for A acende o LED. B apaga o LED
      if (rxValue.find("A") != -1) { 
        Serial.println("Turning ON!");
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if (rxValue.find("B") != -1) {
        Serial.println("Turning OFF!");
        digitalWrite(LED_BUILTIN, LOW);
      }
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
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID), (uint32_t) 25, (uint8_t) 0);
  
 
  // Cria uma Característica BLE para envio dos dados
  pCharacteristic = pService->createCharacteristic(
                      DHTDATA_CHAR_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );
                       
  pCharacteristic->addDescriptor(new BLE2902());
 
  // cria uma característica BLE para recebimento dos dados
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  BLECharacteristic *pCharacteristicTx = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_TX,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  BLECharacteristic *pCharacteristicEmail = pService->createCharacteristic(
                                         CHARACTERISTIC_EMAIL,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );      

  BLECharacteristic *pCharacteristicPassword = pService->createCharacteristic(
                                         CHARACTERISTIC_PASSWORD,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );  

  BLECharacteristic *pCharacteristicName = pService->createCharacteristic(
                                         CHARACTERISTIC_NAME,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );     

  BLECharacteristic *pCharacteristicSSID = pService->createCharacteristic(
                                         CHARACTERISTIC_SSID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );                                                                        

  BLECharacteristic *pCharacteristicSSIDPassword = pService->createCharacteristic(
                                         CHARACTERISTIC_SSIDPASSWORD,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );  


  BLECharacteristic *pCharacteristicSSIDAlternativeMqttServer = pService->createCharacteristic(
                                         CHARACTERISTIC_ALTERNATIVEMQTTSERVER,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );     

  BLECharacteristic *pCharacteristicSSIDAlternativeMqtttPort = pService->createCharacteristic(
                                         CHARACTERISTIC_ALTERNATIVEMQTTPORT,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );                                          
                                       
 
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristicEmail->setCallbacks(new MyCallbacks());
  pCharacteristicPassword->setCallbacks(new MyCallbacks());
  pCharacteristicName->setCallbacks(new MyCallbacks());
  pCharacteristicSSID->setCallbacks(new MyCallbacks());
  pCharacteristicSSIDPassword->setCallbacks(new MyCallbacks());
  pCharacteristicSSIDAlternativeMqttServer->setCallbacks(new MyCallbacks());
  pCharacteristicSSIDAlternativeMqtttPort->setCallbacks(new MyCallbacks());

  // Inicia o serviço
  pService->start();
  
 
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  Serial.println("Esperando um cliente se conectar...");
  pCharacteristic->setValue("Hello World");
}

void ble_loop(){

    if (deviceConnected) {
 
     
    char humidityString[2];
    char temperatureString[2];

    dtostrf(humidity, 1, 2, humidityString);
    dtostrf(temperature, 1, 2, temperatureString);
 
    char dhtDataString[16];
    sprintf(dhtDataString, "%d,%d", temperature, humidity);
     
    pCharacteristic->setValue(dhtDataString);
     
    pCharacteristic->notify(); // Envia o valor para o aplicativo!
    //Serial.print("*** Dado enviado: ");
    //Serial.print(dhtDataString);
    //Serial.println(" ***");
  }
  vTaskDelay(pdMS_TO_TICKS(1000));
}


    
