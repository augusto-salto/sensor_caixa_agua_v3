#include <task_firebase.h>




void task_firebase( void *pvParameters )
{
    (void) pvParameters;
     float nivel_rcv = 0.0;
    UBaseType_t uxHighWaterMark;
    //FireBaseClass firebasePPP;

    while(1)
    {   
    
        xQueueReceive(xQueue_Nivel, (void *)&nivel_rcv, portMAX_DELAY);                     // PEGA NA FILA A VARIAVEL NIVEL



        xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );                                  // AGUARDA A LIBERAÇÃO DO SEMAFORO PARA USO DA PORTA SERIAL
        //Serial.print("FIREBASE NIVEL: ");
        //Serial.print(firebasePPP.getNivelToDebug());
        Serial.print("\n");
        Serial.print("\nTASK1 NIVEL: " + String(nivel_rcv));
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nTASK FIREBASE highWaterMark: ");
        Serial.print(uxHighWaterMark);
        Serial.print("\n");
        xSemaphoreGive(xSerial_semaphore);                                                  // LIBERA O SEMAFORO PARA OUTRA TASK


        vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
    }
}



