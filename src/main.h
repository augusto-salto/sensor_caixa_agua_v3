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
#include <bluetooth_ble_lib.h>
#include <wifi_ble_manager.h>

#define ONBOARD_BUTTON 0
#define BUFF_SIZE 1000

#if USE_WIFI_MANAGER == 1
    PppTech pppTech; 
#endif

    QueueHandle_t xQueue_Nivel;
    SemaphoreHandle_t xSerial_semaphore;

    
    
    

    //extern void task_geral( void *pvParameters );
    //extern void task_firebase( void *pvParameters );
    //extern void task_sensor( void *pvParameters );



#endif