#include <sistemaArquivosFS.h>





void readConfig(char *retornoEmail, char *retornoPassword){


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
         

          strcpy(retornoEmail, json["email"] | "N/A");
          strcpy(retornoPassword, json["password"] | "N/A");

          Serial.print("\nE-MAIL: " + String(retornoEmail));
          Serial.print("\nPASSWORD: " + String(retornoPassword));


        } else {
          Serial.println("failed to load json config");
          
          
        }
        configFile.close();
      }
    }else{
      Serial.println("NAO EXISTE O CONFIG FILE!");
    }
  } else {
    Serial.println("failed to mount FS");
  }

}



void saveConfig(char *saveEmail, char *savePassword){

 

    DynamicJsonDocument json(1024);
    
    json["email"] = saveEmail;
    json["password"] = savePassword;

    File configFile = LITTLEFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    serializeJson(json, Serial);
    serializeJson(json, configFile);

    configFile.close();
    
  
}