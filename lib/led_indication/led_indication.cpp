#include <led_indication.h>


// xQueueReceive(xQueue_light_indication, (void *)&status_led, pdMS_TO_TICKS(100)); 

LedIndication::LedIndication(){

        pinMode(PIN_RED, OUTPUT);
        pinMode(PIN_GREEN, OUTPUT);
        pinMode(PIN_BLUE, OUTPUT);

}

void LedIndication::running(){
    Serial.print("LED INICIADO!!!");
}

void LedIndication::_setGreen(){
    this->_red = 0;
    this->_green = 255;
    this->_blue = 127;
}

