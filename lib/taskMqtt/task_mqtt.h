#ifndef TASK_MQTT_H
#define TASK_MQTT_H
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>

#include <ppp_mqtt.h>

#define TASK_MQTT_SIZE 15000
#define TASK_MQTT_PRIORITY 5



#include <definicoes.h>
extern SemaphoreHandle_t xSerial_semaphore;

void task_mqtt( void *pvParameters );
void vTask_mqtt_start();






#endif