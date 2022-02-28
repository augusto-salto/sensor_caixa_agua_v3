#include <led_indication.h>



// xQueueReceive(xQueue_light_indication, (void *)&status_led, pdMS_TO_TICKS(100)); 

LedIndication::LedIndication(){
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);
        pinMode(PIN_RED, OUTPUT);
        pinMode(PIN_GREEN, OUTPUT);
        pinMode(PIN_BLUE, OUTPUT);

}

void LedIndication::running(){
    this->_setGreen();
    digitalWrite(LED_BUILTIN, HIGH);
}

void LedIndication::not_configured(){
    this->_setYellow();
   
}

void LedIndication::wifi_not_conected(){
    this->_setGreen();
    vTaskDelay(pdMS_TO_TICKS(1500));
    this->_turnOff();
}

void LedIndication::error(){
    this->_setRed();
}

void LedIndication::working(){
    this->_setYellow();
    digitalWrite(LED_BUILTIN, HIGH);
     vTaskDelay(pdMS_TO_TICKS(800));
     digitalWrite(LED_BUILTIN, LOW);
    this->_turnOff();
}

void LedIndication::initializing(){
    this->_setBlue();

     digitalWrite(LED_BUILTIN, HIGH);
     vTaskDelay(pdMS_TO_TICKS(200));
     digitalWrite(LED_BUILTIN, LOW);
    this->_turnOff();
    
}

void LedIndication::turnOffLed(){
    this->_turnOff();
}


void LedIndication::applyLedState()

{

xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
    if((this->task_geral_status == light_indication::running) 
    && (this->task_mqtt_status == light_indication::running) 
    && (this->task_sensor_status == light_indication::running) 
    && (this->task_update_status ==light_indication::running)
    && (this->task_wifi_manager_status == light_indication::running) )
    {
        this->running();
        //Serial.print("\n\n 1 \n\n");
        
    } 
    else if((this->task_geral_status == light_indication::not_configured) 
    || (this->task_mqtt_status == light_indication::not_configured) 
    || (this->task_sensor_status == light_indication::not_configured) 
    || (this->task_update_status ==light_indication::not_configured)
    || (this->task_wifi_manager_status == light_indication::not_configured))
    {
        this->not_configured();
        //Serial.print("\n\n 2 \n\n");
    }
    else if((this->task_geral_status == light_indication::wifi_not_conected) 
    || (this->task_mqtt_status == light_indication::wifi_not_conected) 
    || (this->task_sensor_status == light_indication::wifi_not_conected) 
    || (this->task_update_status ==light_indication::wifi_not_conected)
    || (this->task_wifi_manager_status == light_indication::wifi_not_conected))
    {
        this->wifi_not_conected();
        //Serial.print("\n\n 3 \n\n");
    }
    else if((this->task_geral_status == light_indication::error) 
    || (this->task_mqtt_status == light_indication::error) 
    || (this->task_sensor_status == light_indication::error) 
    || (this->task_update_status ==light_indication::error)
    || (this->task_wifi_manager_status == light_indication::error))
    {
        this->error();
        //Serial.print("\n\n 4 \n\n");
    }
    else if((this->task_geral_status == light_indication::working) 
    || (this->task_mqtt_status == light_indication::working) 
    || (this->task_sensor_status == light_indication::working) 
    || (this->task_update_status ==light_indication::working)
    || (this->task_wifi_manager_status == light_indication::working))
    {
        this->working();
        //Serial.print("\n\n 5 \n\n");
    }
    else if((this->task_geral_status == light_indication::initializing) 
    || (this->task_mqtt_status == light_indication::initializing) 
    || (this->task_sensor_status == light_indication::initializing) 
    || (this->task_update_status ==light_indication::initializing)
    || (this->task_wifi_manager_status == light_indication::initializing))
    {
        this->initializing();
        //Serial.print("\n\n 6 \n\n");
    }else{
            //Serial.print("\n\n 7 \n\n");
    }
    
    
    //Serial.print("\n 1: " + String(this->task_geral_status));
    //Serial.print("\n 2: " + String(this->task_mqtt_status));
    //Serial.print("\n 3: " + String(this->task_sensor_status));
    //Serial.print("\n 4: " + String(this->task_update_status));
    //Serial.print("\n 5: " + String(this->task_wifi_manager_status));
    

xSemaphoreGive(xLed_semaphore);

}

void LedIndication::setWifiManagerStatus(light_indication light_indication)
{
    xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
        this->task_wifi_manager_status = light_indication;
    xSemaphoreGive(xLed_semaphore);
}

void LedIndication::setSensorStatus(light_indication light_indication)
{
    xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
        this->task_sensor_status = light_indication;
    xSemaphoreGive(xLed_semaphore);
}

void LedIndication::setGeralStatus(light_indication light_indication)
{
    xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
        this->task_geral_status = light_indication;
    xSemaphoreGive(xLed_semaphore);
}
void LedIndication::setMqttStatus(light_indication light_indication)
{
    xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
        this->task_mqtt_status = light_indication;
    xSemaphoreGive(xLed_semaphore);
}
void LedIndication::setUpdateStatus(light_indication light_indication)
{
    xSemaphoreTake(xLed_semaphore, pdMS_TO_TICKS(100));
        this->task_update_status = light_indication;
    xSemaphoreGive(xLed_semaphore);
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