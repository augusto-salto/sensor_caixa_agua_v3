#ifndef TASK_SENSOR_H
#define TASK_SENSOR_H
#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>
#include <definicoes.h>

#define DEBUG_IS_ON 0
#define TASK_SENSOR_SIZE 1550

extern QueueHandle_t xQueue_Nivel;
extern SemaphoreHandle_t xSerial_semaphore;

void task_sensor( void *pvParameters );





#endif