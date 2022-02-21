#include <wifi_ble_manager.h>



WifiBleManager::WifiBleManager(){

        
           
}


bool WifiBleManager::isConfigured(){

/*DynamicJsonDocument json(1024);
    
    json["email"] = "saveEmail";
    json["passwordEmail"] = "savePassword";
    json["nameSensor"] = "saveEmail";
    ----------------json["wifiSSID"] = "savePassword";
    ----------------json["wifiPassword"] = "saveEmail";
    json["mqttServer"] = "savePassword";
    json["mqttPort"] = "savePassword";

    File configFile = LITTLEFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    serializeJson(json, Serial);
    serializeJson(json, configFile);

    configFile.close();*/
    

    if (LITTLEFS.begin() == true) {
       
        if(LITTLEFS.exists("/config.json")){

            return true;

        } else{
            return false;
        }
        

    }else{
        Serial.print("\n111111111111");
        return false;
    }
       

}


String WifiBleManager::getWifiSSID(){
    this->_getStringFromFS(_wifiSSID, "wifiSSID");
    return this->_wifiSSID;
}

String WifiBleManager::getWifiPassword(){
    this->_getStringFromFS(_wifiPassword, "wifiPassword");
    return this->_wifiPassword;
}

String WifiBleManager::getEmail(){
    this->_getStringFromFS(_email, "email");
    return this->_email;
}

String WifiBleManager::getEmailPassword(){
    this->_getStringFromFS(_emailPassoword, "passwordEmail");
    return this->_emailPassoword;
}

String WifiBleManager::getMqttPort(){
    this->_getStringFromFS(_mqttPort, "mqttPort");
    return this->_mqttPort;
}

String WifiBleManager::getNameSensor(){
    this->_getStringFromFS(_nameSensor, "nameSensor");
    return this->_nameSensor;
}

String WifiBleManager::getMqttServer(){
    this->_getStringFromFS(_mqttServer, "mqttServer");
    return this->_mqttServer;
}


void WifiBleManager::_getStringFromFS(char *ptr,  const char* name){
   char returnBuff[100];
    char *ponteiro = ptr;

    if (LITTLEFS.begin()) {
       
    if (LITTLEFS.exists("/config.json")) {
 
      File configFile = LITTLEFS.open("/config.json", "r");
      if (configFile) {
        
        size_t size = configFile.size();
        
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);


        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if ( ! deserializeError ) {
         

          strcpy(returnBuff, json[name] | "N/A");
          strcpy(ponteiro, returnBuff); ////
        


        } else {

          
          strcpy(ponteiro, "NULL"); ////this->_wifiSSID
    
          
        }
        configFile.close();
        
      }
    }else{
      Serial.println("NAO EXISTE O CONFIG FILE!");
      strcpy(ponteiro, "NULL");
      
    }
  } else {
    Serial.println("failed to mount FS");
    strcpy(ponteiro, "NULL");
    
  }



}