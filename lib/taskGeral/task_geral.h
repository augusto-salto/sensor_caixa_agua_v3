#ifndef TASK_GERAL_H
#define TASK_GERAL_H

#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
//#include <Arduino.h>
#include <ppptech.h>

#if USE_FIREBASE == 1
#include <task_firebase.h>
#endif

#if USE_MQTT == 1
#include <task_mqtt.h>
#endif

#include <definicoes.h>

extern TaskHandle_t handle_firebase;
extern TaskHandle_t handle_sensor;
extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_wifi_ble_manager;
   


//extern PppTech pppTech; 
extern SemaphoreHandle_t xSerial_semaphore;



void task_geral( void *pvParameters );
void vTask_geral_start();



#endif