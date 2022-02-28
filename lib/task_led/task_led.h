#ifndef TASK_LED_H
#define TASK_LED_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <Arduino.h>
#include <definicoes.h>
#include <led_indication.h>

void task_led( void *pvParameters );
void vTask_led_start();



#endif