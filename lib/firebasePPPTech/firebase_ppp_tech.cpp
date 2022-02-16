#include <firebase_ppp_tech.h>

#include <FirebaseESP32.h>
#include <string>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config; 
    

FireBaseClass::FireBaseClass(){

    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
    Firebase.begin(&config, &auth);
   
}

int FireBaseClass::getAlarm(){

        if(Firebase.ready()){

            Firebase.getString(fbdo, "/real/alarme");         //RECUPERA O SETPOINT DE ALARME
            return fbdo.stringData().toInt() ;

        }else{
            return 0;
        }
}

bool FireBaseClass::getFlagAlarm(){
    
        if(Firebase.ready()){

            Firebase.getInt(fbdo, "/real/alarmOnOff");
            if (fbdo.intData() == 1){
                return true;
            }else{
                return false;
            }

        }else{
            return false;
        }
}

int FireBaseClass::getXmax(){

        if(Firebase.ready()){

            Firebase.getString(fbdo, "/real/xMax");
           return fbdo.stringData().toInt();

        }else{
            return 0;
        }
}

int FireBaseClass::getXmin(){

        if(Firebase.ready()){

            Firebase.getString(fbdo, "/real/xMin");
            return fbdo.stringData().toInt();

        }else{
            return 0;
        }
}


int FireBaseClass::getTotal(){

        if(Firebase.ready()){

            Firebase.getFloat(fbdo, "/real/volumeTotal");
           return fbdo.floatData();

        }else{
            return 0;
        }
}


void FireBaseClass::setDistanciaCm(int distancia){

        if(Firebase.ready()){

                Firebase.setInt(fbdo, "/real/realMedido", distancia); 

        }

}

void FireBaseClass::setNivel(int nivel){

        if(Firebase.ready()){

                Firebase.setInt(fbdo, "/real/nivel", nivel); 

        }

}

void FireBaseClass::setTotal(int total){

        if(Firebase.ready()){

                Firebase.setFloat(fbdo, "/real/volumeTotal", total);

        }

}

void FireBaseClass::setVazao(float vazao){

        if(Firebase.ready()){

               Firebase.setFloat(fbdo, "/real/vazaoInstantanea", vazao); 

        }

}



int FireBaseClass::getNivelToDebug(){

         if(Firebase.ready()){

            Firebase.getString(fbdo, "/real/nivel");
            return fbdo.stringData().toInt();

        }else{
            return 0;
        }
}


