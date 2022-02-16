#include "task2_firebase.h"


#include <FirebaseESP32.h>
#include <string>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

unsigned long sendDataPrevMillis = 0;
int firebaseNivel = 0;
int firebaseAlarme = 0;
int firebaseAlarmOnOff = 0;
int firebaseXmax = 0;
int firebaseXmin = 0;
bool flagDesce = false;
bool flagAlarme = false;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void initTask2(){



config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
}

void vTask2Firebase()
{

    if (Firebase.ready() && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0))
  {
    
    sendDataPrevMillis = millis();


//TRATAMENTO DO ALARME....

  Firebase.getString(fbdo, "/real/alarme");         //RECUPERA O SETPOINT DE ALARME
  firebaseAlarme = fbdo.stringData().toInt() ;
  Firebase.getInt(fbdo, "/real/alarmOnOff");
  firebaseAlarmOnOff = fbdo.intData();




  //TRATAMENTO DO NIVEL...
  Firebase.setInt(fbdo, "/real/nivel", firebaseNivel); //ENVIA O NIVEL 
  Firebase.getInt(fbdo, "/real/nivel");        // RECUPERA O NIVEL
  firebaseNivel = fbdo.intData();

  //TRATAMENTO DOS AJUSTES DE ESCALA DO SENSOR
  Firebase.getString(fbdo, "/real/xMax");
  firebaseXmax = fbdo.stringData().toInt();
  Firebase.getString(fbdo, "/real/xMin");
  firebaseXmin = fbdo.stringData().toInt();

    
  }

    
}