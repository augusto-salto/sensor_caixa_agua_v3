#include <conect_manager.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

FileSystemManager fileSystemManager;


bool ConnectManagerClass::checkDataCons(){

Serial.print("\nHEAP 1: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");

this->initialFSconfigure();

    if(fileSystemManager.isConfigured()){
        
        if(fileSystemManager.getEmail().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getEmailPassword().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getWifiSSID().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getWifiSSID().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getWifiPassword().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getMqttServer().equals("N/A"))
        {
            return false;
        }
        else if(fileSystemManager.getMqttPort().equals("N/A"))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else{
        return false;
    }


}

void ConnectManagerClass::initialFSconfigure(){
    if(!fileSystemManager.isConfigured()){
        fileSystemManager.initialState();
        Serial.print("FIZ A PRIMEIRA GRAVACAO NO FS");
    }
}



void ConnectManagerClass::disableBleAndConectWifi(){
    int i = 0;

Serial.print("\nHEAP 2: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");

Serial.print("BLE DELETE OBJECTS1");

BLEDevice::deinit(true);
vTaskDelay(pdMS_TO_TICKS(200));
Serial.print("BLE DELETE OBJECTS");

    if(btStop())
    {
        //WiFi.mode(WIFI_STA);
        WiFi.begin(fileSystemManager.getWifiSSID().c_str(), fileSystemManager.getWifiPassword().c_str());
        
        LITTLEFS.end();
        
        for(i = 0; i <= TENTATIVAS_CONNECT_WIFI; i++ ){
            if(WiFi.status() != WL_CONNECTED){
                vTaskDelay(pdMS_TO_TICKS(1000));
                Serial.print("\n");
                Serial.print("TENTATIVA " + String(i) + " DE CONEXAO AO WIFI");
                
            }else{
                break;
            }
        }

        if(i == 10){
            Serial.println("NAO FOI POSSIVEL CONECTAR AO WIFI! REINICIANDO...");
            vTaskDelay(pdMS_TO_TICKS(1000));
            ESP.restart(); //TODO verificar, ao inves de reiniciar acionar o led amarelo!
        }else if(WiFi.status() == WL_CONNECTED){
            Serial.print("\nWIFI CONECTADO!");
            Serial.print("\nIP LOCAL: ");
            Serial.print(WiFi.localIP());
            Serial.print("\n");
        }

        deleteBle();

Serial.print("\nHEAP 3: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");

    }
}

void ConnectManagerClass::bleSetupAndInit(){

    Serial.print("\nHEAP 4: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
    ble_setup();
    Serial.print("\nHEAP 5: ");
Serial.print(ESP.getFreeHeap());
Serial.print("\n");
}

void ConnectManagerClass::formatFileSystem(){
    fileSystemManager.format();
}