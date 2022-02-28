#include <update_firmware.h>
#include <cert.h>

light_indication task_update_status;
String FirmwareVer = FIRMWARE_VERSION;
// WiFiClientSecure * client = new WiFiClientSecure;

void firmwareUpdate(void) {
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  //client.setInsecure();
  httpUpdate.setLedPin(LED_BUILTIN, LOW);
  t_httpUpdate_return ret = httpUpdate.update(client, URL_fw_Bin);

  switch (ret) {
  case HTTP_UPDATE_FAILED:
    Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
    break;

  case HTTP_UPDATE_NO_UPDATES:
    Serial.println("HTTP_UPDATE_NO_UPDATES");
    break;

  case HTTP_UPDATE_OK:
    Serial.println("HTTP_UPDATE_OK");
    break;
  }
}




int FirmwareVersionCheck(void) {
  WiFiClientSecure * client = new WiFiClientSecure;
  String payload;
  String currentVers;
  int httpCode = 0;
  String fwurl = "";
  fwurl += URL_fw_Version;
  

  if (client) 
  {
   // client -> setCACert(rootCACertificate);
  client->setInsecure();
  HTTPClient https;

  if (https.begin( * client, fwurl)) 
    { // HTTPS      
    
      vTaskDelay(200);
      httpCode = https.GET();
      vTaskDelay(200);
      
      if (httpCode == HTTP_CODE_OK) // if version received
      {
        payload = https.getString(); // save received version
        
        payload = payload.substring(payload.indexOf("FIRMWARE_VERSION") + 18, payload.indexOf("FIRMWARE_VERSION") + 21);
        //Serial.print(payload.substring(payload.indexOf("FIRMWARE_VERSION") + 18, payload.indexOf("FIRMWARE_VERSION") + 21));
        
      } else {
        Serial.print("error in downloading version file:");
        Serial.println(httpCode);
      }
      https.end();
    }
    client->stop();
    delete client;
    
    //delete client;
  }
      
  if (httpCode == HTTP_CODE_OK) // if version received
  {
      Serial.print("\nVersao encontrada: " + payload);
      Serial.print("\nVersao rodando: ");
      Serial.print(FIRMWARE_VERSION);
      payload.trim();
    if (payload.equals(FIRMWARE_VERSION)) {
      Serial.print("\nDispositivo ja esta atualizado");
      return 0;
    } 
    else 
    {
      //Serial.println(payload);
      Serial.println("\nNovo firmware encontrado!");
      
#if ENABLE_UPDATE == 1
     return 1;
#else
  return 0;
#endif

    }
  } 

  return 0;  
}