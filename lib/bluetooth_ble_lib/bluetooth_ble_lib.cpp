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
      
      //Serial.println(rxValue[0]);
 
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("length: " + String(rxValue.length()));
        //Serial.print("\nReceived Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          //Serial.print(rxValue[i]);
          receivBuff += rxValue[i];
        }

        varBuffer = receivBuff.substring(0, receivBuff.indexOf(":"));
        valueBuffer = receivBuff.substring(receivBuff.indexOf(":")+1);
        received = receivBuff;
        receivBuff = "";

        Serial.println();
        Serial.println("*********");
        Serial.print("VARIAVEL: " + varBuffer);
        Serial.print("\nVALOR: " + valueBuffer);
        Serial.print("\nString de teste: " + received);
        Serial.print("\n");
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
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
 
  // Cria uma Característica BLE para envio dos dados
  pCharacteristic = pService->createCharacteristic(
                      DHTDATA_CHAR_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                       
  pCharacteristic->addDescriptor(new BLE2902());
 
  // cria uma característica BLE para recebimento dos dados
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
 
  pCharacteristic->setCallbacks(new MyCallbacks());
 
  // Inicia o serviço
  pService->start();
 
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  Serial.println("Esperando um cliente se conectar...");

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


    
