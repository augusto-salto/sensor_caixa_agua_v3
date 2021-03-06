#ifndef TASK_UPDATE_FIRMWARE_H
#define TASK_UPDATE_FIRMWARE_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>
#include <definicoes.h>
#include <led_indication.h>


#define TASK_UPDATE_FIRMWARE_SIZE 7000

extern String FirmwareVer;
extern SemaphoreHandle_t xSerial_semaphore;
extern SemaphoreHandle_t xInitialize_semaphore;

extern TaskHandle_t handle_firebase;
extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_sensor;
extern TaskHandle_t handle_geral;

extern LedIndication ledIndicator;

void task_update_firmware( void *pvParameters );
void vTask_update_firmware_start();

#endif