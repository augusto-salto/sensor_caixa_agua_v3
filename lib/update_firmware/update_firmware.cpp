#include <update_firmware.h>
#include <cert.h>


String FirmwareVer = FIRMWARE_VERSION;
WiFiClientSecure * client = new WiFiClientSecure;

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
  String payload;
  int httpCode = 0;
  String fwurl = "";
  fwurl += URL_fw_Version;
  //fwurl += "?";
  //fwurl += String(rand());
  //Serial.println(fwurl);
  //WiFiClientSecure * client = new WiFiClientSecure;

  if (client) 
  {
   // client -> setCACert(rootCACertificate);
   client->setInsecure();
    

    

    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
    HTTPClient https;

    if (https.begin( * client, fwurl)) 
    { // HTTPS      
      Serial.print("\n>>>>>>>>> HEAP 1: ");
      Serial.print(xPortGetFreeHeapSize());
      Serial.print("\n");
            // start connection and send HTTP header
      vTaskDelay(200);
      
      httpCode = https.GET();
      vTaskDelay(200);
      
      if (httpCode == HTTP_CODE_OK) // if version received
      {
        payload = https.getString(); // save received version
      } else {
        Serial.print("error in downloading version file:");
        Serial.println(httpCode);
      }
      https.end();
    }
    client->stop();
    Serial.print("\n>>>>>>>>> HEAP 2: ");
    Serial.print(xPortGetFreeHeapSize());
    Serial.print("\n");
    //delete client;
  }
      
  if (httpCode == HTTP_CODE_OK) // if version received
  {
      Serial.print("\nVersao encontrada: " + payload);
      Serial.print("Versao rodando: " + FirmwareVer);
      payload.trim();
    if (payload.equals(FirmwareVer)) {
      Serial.print("\nDevice already on latest firmware version: ");
      Serial.print(FirmwareVer);
      Serial.print("\n");
      return 0;
    } 
    else 
    {
      //Serial.println(payload);
      Serial.println("\nNew firmware detected");
      return 1;
    }
  } 

  return 0;  
}