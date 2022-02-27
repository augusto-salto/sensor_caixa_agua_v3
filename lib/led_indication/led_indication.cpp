#include <led_indication.h>



// xQueueReceive(xQueue_light_indication, (void *)&status_led, pdMS_TO_TICKS(100)); 

LedIndication::LedIndication(){

        pinMode(PIN_RED, OUTPUT);
        pinMode(PIN_GREEN, OUTPUT);
        pinMode(PIN_BLUE, OUTPUT);

}

void LedIndication::running(){
    this->_setGreen();
}

void LedIndication::not_configured(){
    this->_setYellow();
   
}

void LedIndication::wifi_not_conected(){
    this->_setGreen();
    vTaskDelay(pdMS_TO_TICKS(500));
    this->_turnOff();
}

void LedIndication::error(){
    this->_setRed();
}

void LedIndication::working(){
    this->_setYellow();
     vTaskDelay(pdMS_TO_TICKS(500));
    this->_turnOff();
}

void LedIndication::initializing(){
    this->_setBlue();
    
}

void LedIndication::turnOffLed(){
    this->_turnOff();
}


void LedIndication::_setGreen(){

    this->_red = 0;
    this->_green = 255;
    this->_blue = 0;
    
    analogWrite(PIN_RED, _red); 
    analogWrite(PIN_GREEN, _green);
    analogWrite(PIN_BLUE, _blue);
}

void LedIndication::_setRed(){

    this->_red = 255;
    this->_green = 0;
    this->_blue = 0;
    
    analogWrite(PIN_RED, _red); 
    analogWrite(PIN_GREEN, _green);
    analogWrite(PIN_BLUE, _blue);
}

void LedIndication::_setYellow(){

    this->_red = 255;
    this->_green = 255;
    this->_blue = 0;
    
    analogWrite(PIN_RED, _red); 
    analogWrite(PIN_GREEN, _green);
    analogWrite(PIN_BLUE, _blue);
}

void LedIndication::_setBlue(){

    this->_red = 0;
    this->_green = 0;
    this->_blue = 255;
    
    analogWrite(PIN_RED, _red); 
    analogWrite(PIN_GREEN, _green);
    analogWrite(PIN_BLUE, _blue);
}

void LedIndication::_turnOff(){

    this->_red = 0;
    this->_green = 0;
    this->_blue = 0;
    
    analogWrite(PIN_RED, _red); 
    analogWrite(PIN_GREEN, _green);
    analogWrite(PIN_BLUE, _blue);
}