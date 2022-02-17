#ifndef TASK_FIREBASE_H
#define TASK_FIREBASE_H
#pragma once




#define TASK_FIREBASE_SIZE 13000

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "Arduino.h"

#include <definicoes.h>
#ifndef FIREBASE_PPP_TECH_H
#include <firebase_ppp_tech.h>
#endif

extern QueueHandle_t xQueue_Nivel;
extern SemaphoreHandle_t xSerial_semaphore;


void task_firebase( void *pvParameters );
void vTask_firebase_start();





















#endif