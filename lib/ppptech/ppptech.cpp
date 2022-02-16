#include <ppptech.h>




void PppTech::saveConfigCallback () {

  Serial.println("Chamou callback apos salvar! <<<<<<<<<<<<<<<<");
  shouldSaveConfig = true;

}

PppTech::PppTech(){

        
          
   
}

void PppTech::init(){


wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 1, 1), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0));

        readConfig(email, password);
        Serial.print("\nEMAIL RECUPERADO DO FILE SYSTEM: " + String(email));
        Serial.print("\nPASSWORD RECUPERADO DO FILE SYSTEM: " + String(password));  

        WiFiManagerParameter wifiManagerEmail("email", "E-MAIL", email, 100);
        WiFiManagerParameter wifiManagerPassword("password", "PASSWORD", email, 15);
  
        wifiManager.addParameter(&wifiManagerEmail);
        wifiManager.addParameter(&wifiManagerPassword);
  
        wifiManager.setSaveConfigCallback([this]() { this->saveConfigCallback(); });
        


// INICIALIZA O WIFI MANAGER
    if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  if(shouldSaveConfig){
      Serial.print("TO SALVANDO!!!");
      strcpy(email, wifiManagerEmail.getValue());
      strcpy(password, wifiManagerPassword.getValue());
      saveConfig(email, password);
  }

Serial.println("\nEmail no setup() : " + String(email));
  delay(500);
Serial.println("\npassword no setup() : " + String(password));
Serial.print("\nLOCAL IP:");
Serial.print(WiFi.localIP());

}



String PppTech::getEmail(){

        return this->email;

}

String PppTech::getPassword(){

        return this->password;

}


void PppTech::resetWifiManager(){

    wifiManager.erase();
    
}

void PppTech::formatFileSystem(){

    LITTLEFS.begin();
    LITTLEFS.format();

}











