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
    waiting, 
    initializing 
};

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

    private:
        void _setRed();
        void _setGreen();
        void _setYellow();
        
        int _red;
        int _green;
        int _blue;

};

#endif