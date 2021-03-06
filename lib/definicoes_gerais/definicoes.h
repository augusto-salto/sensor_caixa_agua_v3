#ifndef DEFINICOES_H
#define DEFINICOES_H

#define FIRMWARE_VERSION "1.3"

#define DEBUG_TASK_MQTT 0               // DEBUG TASK MQTT
#define DEBUG_TASK_SENSOR 0             // DEBUG TASK SENSOR
#define DEBUG_TASK_UPDATE_FIRMWARE 0    // DEBUG TASK UPDATE FIRMWARE
#define DEBUG_TASK_WIFI_BLE_MANAGER 0   // DEBUG TASK WIFI AND BLE MANAGER


#define USE_FIREBASE 0                  // HABILITA O FIREBASE
#define USE_MQTT    1                   // HABILITA O PROTOCOLO MQTT
#define USE_UPDATE_FIRMWARE 1           // HABILITA A ATUALIZAÇÃO AUTOMATICA VIA GITHUB
#define USE_WIFI_MANAGER 0              // HABILITA O USO DO WIFIMANAGER
#define USE_TASK_GERAL 1                // HABILITA A TASK GERAL

#define FORMAT_FILE_SYSTEM 0
#define ENABLE_UPDATE 1

////////////////////////////// DEFINIÇÃO DOS PINOS DA PLACA //////////////////////////////

// LED RGB
#define PIN_RED 23      //GPIO 23
#define PIN_GREEN 22    //GPIO 22
#define PIN_BLUE 21     //GPIO 21

// BOTÃO DE RESET
#define ONBOARD_BUTTON 0

// SENSOR DE DISTANCIA
#define TRIGGER_PIN  12
#define ECHO_PIN 13

////////////////////////////// END DEFINIÇÃO DOS PINOS DA PLACA //////////////////////////////

#endif