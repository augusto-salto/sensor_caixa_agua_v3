#ifndef FIREBASE_PPP_TECH_H
#define FIREBASE_PPP_TECH_H

#include <definicoes.h>

#define API_KEY "AIzaSyB1ls5L7eCW6PcqbkcvSRi7JIt2YXU0X7Y"
#define DATABASE_URL "https://fluttermsg-43644-default-rtdb.firebaseio.com"
#define USER_EMAIL "augusto.salto@hotmail.com"
#define USER_PASSWORD "ra201291"




class FireBaseClass 
{
    public:
        FireBaseClass();    
        int getAlarm();
        bool getFlagAlarm();
        int getXmax();
        int getXmin();
        int getTotal();
        int getNivelToDebug();
        void setTotal(int total);
        void setDistanciaCm(int distancia);
        void setNivel(int nivel);
        void setVazao(float vazao);

      

};





#endif