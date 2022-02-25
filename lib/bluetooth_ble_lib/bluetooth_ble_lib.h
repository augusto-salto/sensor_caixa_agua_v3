#ifndef BLUETOOTH_BLE_H
#define BLUETOOH_BLE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <iostream>
#include <string>
#include <Arduino.h>
#include <file_system_manager.h>


#define SERVICE_UUID                                    "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID

#define CHARACTERISTIC_UUID_RX                          "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX                          "6E400002-B5A3-F393-E0A9-E50E24DCCA9F"
#define DHTDATA_CHAR_UUID                               "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" 

#define CHARACTERISTIC_EMAIL                            "6E400002-B5A3-F393-E0A9-E50E24DCCA0E"
#define CHARACTERISTIC_PASSWORD                         "6E400002-B5A3-F393-E0A9-E50E24DCCA1E"
#define CHARACTERISTIC_NAME                             "6E400002-B5A3-F393-E0A9-E50E24DCCA2E"
#define CHARACTERISTIC_SSID                             "6E400002-B5A3-F393-E0A9-E50E24DCCA3E"
#define CHARACTERISTIC_SSIDPASSWORD                     "6E400002-B5A3-F393-E0A9-E50E24DCCA4E"
#define CHARACTERISTIC_ALTERNATIVEMQTTSERVER            "6E400002-B5A3-F393-E0A9-E50E24DCCA5E"
#define CHARACTERISTIC_ALTERNATIVEMQTTPORT              "6E400002-B5A3-F393-E0A9-E50E24DCCA6E"
#define CHARACTERISTIC_ESPRESTAR                        "6E400002-B5A3-F393-E0A9-E50E24DCCA7E"

void ble_loop();
void ble_setup();
void deleteBle();





#endif