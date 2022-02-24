#include <file_system_manager.h>


FileSystemManager::FileSystemManager(){

           
}


bool FileSystemManager::isConfigured(){

    if (LITTLEFS.begin() == true) {
       
        if(LITTLEFS.exists("/config.json")){

            return true;

        } else{
            return false;
        }
        

    }else{
        
        return false;
    }
       

}

void FileSystemManager::format(){

  LITTLEFS.begin();
  LITTLEFS.format();
  
       

}


String FileSystemManager::getWifiSSID(){
    this->_getStringFromFS(_wifiSSID, JSON_ADDR_SSID_NAME);
    return this->_wifiSSID;
}

String FileSystemManager::getWifiPassword(){
    this->_getStringFromFS(_wifiPassword, JSON_ADDR_SSID_PASSWORD);
    return this->_wifiPassword;
}

String FileSystemManager::getEmail(){
    this->_getStringFromFS(_email, JSON_ADDR_EMAIL);
    return this->_email;
}

String FileSystemManager::getEmailPassword(){
    this->_getStringFromFS(_emailPassoword, JSON_ADDR_EMAIL_PASSWORD);
    return this->_emailPassoword;
}

String FileSystemManager::getNameSensor(){
    this->_getStringFromFS(_nameSensor, JSON_ADDR_NAME_SENSOR);
    return this->_nameSensor;
}

String FileSystemManager::getMqttPort(){
    this->_getStringFromFS(_mqttPort, JSON_ADDR_MQTT_PORT);
    return this->_mqttPort;
}

String FileSystemManager::getMqttServer(){
    this->_getStringFromFS(_mqttServer, JSON_ADDR_MQTT_SERVER);
    return this->_mqttServer;
}

bool FileSystemManager::setWifiSSID(char *SSIDname){

  strcpy(this->_wifiSSID, SSIDname);

  return  this->_setStringToFS();

}

bool FileSystemManager::setWifiPassword(char *SSIDpassword){

  strcpy(this->_wifiPassword, SSIDpassword);

  return  this->_setStringToFS();

}

bool FileSystemManager::setEmail(char *email){

  strcpy(this->_email, email);

 return   this->_setStringToFS();

}

bool FileSystemManager::setEmailPassword(char *emailPassoword){

  strcpy(this->_emailPassoword, emailPassoword);

  return  this->_setStringToFS();

}

bool FileSystemManager::setNameSensor(char *nameSensor){

  strcpy(this->_nameSensor, nameSensor);

  return this->_setStringToFS();

}

bool FileSystemManager::setMqttServer(char *mqttServer){

  strcpy(this->_mqttServer, mqttServer);

  return this->_setStringToFS();

}

bool FileSystemManager::setMqttPort(char *mqttPort){

  strcpy(this->_mqttPort, mqttPort);

  return this->_setStringToFS();

}



bool FileSystemManager::_setStringToFS(){

     DynamicJsonDocument json(1024);
    
    json[JSON_ADDR_EMAIL] = _email;
    json[JSON_ADDR_EMAIL_PASSWORD] = _emailPassoword;
    json[JSON_ADDR_SSID_NAME] = _wifiSSID;
    json[JSON_ADDR_SSID_PASSWORD] = _wifiPassword;
    json[JSON_ADDR_NAME_SENSOR] = _nameSensor;
    json[JSON_ADDR_MQTT_SERVER] = _mqttServer;
    json[JSON_ADDR_MQTT_PORT] = _mqttPort;
    

    

    File configFile = LITTLEFS.open("/config.json", "w");

    if (!configFile) {
      Serial.println("failed to open config file for writing");
      return false;

    }

    serializeJson(json, configFile);

    configFile.close();
    LITTLEFS.end();
    return true;
    
}


void FileSystemManager::_getStringFromFS(char *ptr,  const char* name){

   char returnBuff[100];
    char *ponteiro = ptr;
    if (LITTLEFS.begin()) {
    if (LITTLEFS.exists("/config.json")) {
      File configFile = LITTLEFS.open("/config.json", "r");
      if (configFile) 
        {
        
          size_t size = configFile.size();
        
          std::unique_ptr<char[]> buf(new char[size]);

          configFile.readBytes(buf.get(), size);

          DynamicJsonDocument json(1024);

          auto deserializeError = deserializeJson(json, buf.get());

          if ( ! deserializeError ) 
            {
              strcpy(returnBuff, json[name] | "N/A");
              strcpy(ponteiro, returnBuff); ////
            } else 
              {
                strcpy(ponteiro, "NULL"); ////this->_wifiSSID
              }

          configFile.close();
          LITTLEFS.end();
        }
    }else
      {
        Serial.println("NAO EXISTE O CONFIG FILE!");
        strcpy(ponteiro, "NULL");
      }

  } else 
  {
    Serial.println("failed to mount FS");
    strcpy(ponteiro, "NULL");  
  }



}