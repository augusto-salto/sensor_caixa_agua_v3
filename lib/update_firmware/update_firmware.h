#ifndef UPDATE_FIRMWARE_H
#define UPDATE_FIRMWARE_H

#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>

#include <definicoes.h>

#include <Arduino.h>


//#define URL_fw_Version "https://raw.githubusercontent.com/programmer131/ESP8266_ESP32_SelfUpdate/master/esp32_ota/bin_version.txt"
//#define URL_fw_Bin     "https://raw.githubusercontent.com/programmer131/ESP8266_ESP32_SelfUpdate/master/esp32_ota/fw.bin"
//  #define URL_fw_Version "https://raw.githubusercontent.com/augusto-salto/updateSensorNivel/main/bin_version.txt"

 // --> funcional --> #define URL_fw_Version "https://raw.githubusercontent.com/augusto-salto/sensor_caixa_agua_v3/main/lib/versao/bin_version.txt"
#define URL_fw_Version "https://raw.githubusercontent.com/augusto-salto/sensor_caixa_agua_v3/main/lib/definicoes_gerais/definicoes.h"
// 
//#define URL_fw_Bin "https://raw.githubusercontent.com/augusto-salto/updateSensorNivel/main/fw.bin"



#define URL_fw_Bin "https://raw.githubusercontent.com/augusto-salto/sensor_caixa_agua_v3/main/.pio/build/nodemcu-32s/firmware.bin"

extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_firebase;



void firmwareUpdate();
int FirmwareVersionCheck();


#endif