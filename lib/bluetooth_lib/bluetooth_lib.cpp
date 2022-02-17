#include <bluetooth_lib.h>

uint8_t counter = 0;
BluetoothSerial SerialBT;

void bluetooth_init(){

     
SerialBT.begin("ESP SENSOR CAIXA");


}


void bluetooth_loop(){


 if (Serial.available()) {
    SerialBT.print("\n");
    SerialBT.print(Serial.read());
  }
  while (SerialBT.available()) {

    Serial.write(SerialBT.read());

  }


vTaskDelay(pdMS_TO_TICKS(200));

    SerialBT.print("\n");
    SerialBT.print(counter);
    counter = counter > 254 ? 0 : counter+1;
    
}