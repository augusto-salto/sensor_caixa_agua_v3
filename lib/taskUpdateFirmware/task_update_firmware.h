#ifndef TASK_UPDATE_FIRMWARE_H
#define TASK_UPDATE_FIRMWARE_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>
#include <definicoes.h>


#define TASK_UPDATE_FIRMWARE_SIZE 15100

extern String FirmwareVer;
extern SemaphoreHandle_t xSerial_semaphore;
void task_update_firmware( void *pvParameters );

extern TaskHandle_t handle_firebase;
extern TaskHandle_t handle_mqtt;
extern TaskHandle_t handle_sensor;
extern TaskHandle_t handle_geral;



#endif