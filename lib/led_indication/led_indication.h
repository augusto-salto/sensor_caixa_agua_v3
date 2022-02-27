#ifndef LED_INDICATION_H
#define LED_INDICATION_H

#include <definicoes.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

enum light_indication {
    running,
    not_configured,
    wifi_not_conected,
    error,
    waiting 
};

extern QueueHandle_t xQueue_light_indication;

class LedIndication
{
    public:
        LedIndication(int pinRed, int pinYellow, int pinBlue);
        void running();
        void not_configured();
        void wifi_not_conected();
        void error();
        void working();

    private:
        void _red();
        void _green();
        void _yellow();
        
        int _pinRed;
        int _pinYellow;
        int _pinBlue;

};

#endif