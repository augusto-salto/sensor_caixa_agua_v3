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

String WifiBleManager::getNameSensor(){
    this->_getStringFromFS(_nameSensor, "nameSensor");
    return this->_nameSensor;
}

String WifiBleManager::getMqttPort(){
    this->_getStringFromFS(_mqttPort, "mqttPort");
    return this->_mqttPort;
}

String WifiBleManager::getMqttServer(){
    this->_getStringFromFS(_mqttServer, "mqttServer");
    return this->_mqttServer;
}

bool WifiBleManager::setWifiSSID(char *SSIDname){

  strcpy(this->_wifiSSID, SSIDname);

  return  this->_setStringToFS(_wifiSSID, JSON_ADDR_SSID_NAME);

}

bool WifiBleManager::setWifiPassword(char *SSIDpassword){

  strcpy(this->_wifiPassword, SSIDpassword);

  return  this->_setStringToFS(_wifiPassword, JSON_ADDR_SSID_PASSWORD);

}

bool WifiBleManager::setEmail(char *email){

  strcpy(this->_email, email);

 return   this->_setStringToFS(_email, JSON_ADDR_EMAIL);

}

bool WifiBleManager::setEmailPassword(char *emailPassoword){

  strcpy(this->_emailPassoword, emailPassoword);

  return  this->_setStringToFS(_emailPassoword, JSON_ADDR_EMAIL_PASSWORD);

}

bool WifiBleManager::setNameSensor(char *nameSensor){

  strcpy(this->_nameSensor, nameSensor);

  return this->_setStringToFS(_nameSensor, JSON_ADDR_NAME_SENSOR);

}

bool WifiBleManager::setMqttServer(char *mqttServer){

  strcpy(this->_mqttServer, mqttServer);

  return this->_setStringToFS(_mqttServer, JSON_ADDR_MQTT_SERVER);

}

bool WifiBleManager::setMqttPort(char *mqttPort){

  strcpy(this->_mqttPort, mqttPort);

  return this->_setStringToFS(_mqttPort, JSON_ADDR_MQTT_PORT);

}



bool WifiBleManager::_setStringToFS(char *ptr, const char* name){

     DynamicJsonDocument json(1024);
    
    json[name] = ptr;
    

    File configFile = LITTLEFS.open("/config.json", "w");

    if (!configFile) {
      Serial.println("failed to open config file for writing");
      return false;

    }

    serializeJson(json, configFile);

    configFile.close();

    return true;
    
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