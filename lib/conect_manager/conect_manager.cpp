#include <conect_manager.h>

FileSystemManager fileSystemManager;


bool ConnectManagerClass::checkDataCons(){

    //checa se o file system foi configurado
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



void ConnectManagerClass::disableBleAndConectWifi(){
    int i = 0;
    
    if(btStop())
    {
        //WiFi.mode(WIFI_STA);
        WiFi.begin(fileSystemManager.getWifiSSID().c_str(), fileSystemManager.getWifiPassword().c_str());
        
        
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
        
    }
}

void ConnectManagerClass::bleSetupAndInit(){
    ble_setup();
}