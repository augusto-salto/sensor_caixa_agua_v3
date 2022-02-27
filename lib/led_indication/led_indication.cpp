#include <led_indication.h>


// xQueueReceive(xQueue_light_indication, (void *)&status_led, pdMS_TO_TICKS(100)); 

LedIndication::LedIndication(int pinRed, int pinYellow, int pinBlue){

    this->_pinRed = pinRed;
    this->_pinYellow = pinYellow;
    this-> _pinBlue = pinBlue;

    Serial.print("LED INICIADO!!!");
    
}