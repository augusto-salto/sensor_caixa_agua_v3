#ifndef LED_INDICATION_H
#define LED_INDICATION_H

#include <definicoes.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <analogWrite.h>

enum light_indication {
    running,
    not_configured,
    wifi_not_conected,
    error,
    waiting, 
    working,
    initializing 
};



extern SemaphoreHandle_t xLed_semaphore;
extern QueueHandle_t xQueue_light_indication;

class LedIndication
{
    public:
        LedIndication();
        void running();
        void not_configured();
        void wifi_not_conected();
        void error();
        void working();
        void initializing();
        void turnOffLed();
        void applyLedState();

        void setWifiManagerStatus(light_indication light_indication);
        void setMqttStatus(light_indication light_indication);
        void setSensorStatus(light_indication light_indication);
        void setGeralStatus(light_indication light_indication);
        void setUpdateStatus(light_indication light_indication);


    private:
        void _setRed();
        void _setGreen();
        void _setYellow();
        void _setBlue();
        void _turnOff();
        
        int _red;
        int _green;
        int _blue;

        light_indication task_wifi_manager_status = light_indication::initializing;
        light_indication task_mqtt_status = light_indication::initializing;
        light_indication task_sensor_status = light_indication::running;
        light_indication task_geral_status = light_indication::initializing;
        light_indication task_update_status = light_indication::initializing;

};

#endif