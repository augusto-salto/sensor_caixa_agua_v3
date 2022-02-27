#ifndef MAIN_H
#define MAIN_H
#pragma once

#ifndef PPPTECH_H
#include <ppptech.h>
#endif

#ifndef TASK_FIREBASE_H
#include <task_firebase.h>
#endif

#ifndef TASK_SENSOR_H
#include <task_sensor.h>
#endif

#ifndef TASK_GERAL_H
#include <task_geral.h>
#endif

#ifndef TASK_MQTT_H
#include <task_mqtt.h>
#endif

#ifndef TASK_UPDATE_FIRMWARE_H
#include <task_update_firmware.h>
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

//#include <bluetooth_lib.h>
//#include <bluetooth_ble_lib.h>
//#include <file_system_manager.h>
//#include <conect_manager.h>
#include <task_wifi_ble_manager.h>
#include <led_indication.h>

#define ONBOARD_BUTTON 0
#define BUFF_SIZE 1000

#if USE_WIFI_MANAGER == 1
    PppTech pppTech; 
#endif

    QueueHandle_t xQueue_Nivel;
    QueueHandle_t xQueue_android_request;
    QueueHandle_t xQueue_light_indication;

    SemaphoreHandle_t xSerial_semaphore;
    SemaphoreHandle_t xFileSystem_semaphore;
    SemaphoreHandle_t xInitialize_semaphore;

extern TaskHandle_t handle_wifi_ble_manager;
extern TaskHandle_t handle_firebase;
extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_sensor;
extern TaskHandle_t handle_geral;
extern TaskHandle_t handle_updateFirmware;

    LedIndication ledindication = LedIndication(0, 2, 4);
    

    //extern void task_geral( void *pvParameters );
    //extern void task_firebase( void *pvParameters );
    //extern void task_sensor( void *pvParameters );



#endif