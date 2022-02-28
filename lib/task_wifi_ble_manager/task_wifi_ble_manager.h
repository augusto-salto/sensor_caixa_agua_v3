#ifndef TASK_WIFI_BLE_MANAGER_H
#define TASK_WIFI_BLE_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>
#include <definicoes.h>

#include <task_firebase.h>
#include <task_geral.h>
#include <task_mqtt.h>
#include <task_geral.h>
#include <task_sensor.h>
#include <task_update_firmware.h>

#include <led_indication.h>
#include <task_led.h>
#include <conect_manager.h>

#define TASK_WIFI_BLE_MANAGER_SIZE 18000

extern SemaphoreHandle_t xSerial_semaphore;
extern SemaphoreHandle_t xFileSystem_semaphore;

extern TaskHandle_t handle_firebase;
extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_sensor;
extern TaskHandle_t handle_geral;
extern TaskHandle_t handle_updateFirmware;

extern LedIndication ledIndicator;

void task_wifi_ble_manager( void *pvParameters );
void vTask_wifi_ble_manager_start();




#endif