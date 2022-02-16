#ifndef PPPTECH_H
#define PPPTECH_H
#pragma once
#include <WiFiManager.h>  
#include "FS.h"
#include <LITTLEFS.h>
#include <ArduinoJson.h>  
#include <Arduino.h>
#include <sistemaArquivosFS.h>  
#include <definicoes.h>

/*=============================================
*           Autor: Augusto Cesar de Lima
*                   25/01/2022
* =============================================*/

class PppTech 
{
    public:
    
        PppTech();    // CONSTRUTOR DA CLASSE, RECEBE UMA REFERENCIA A UM OBJETO WIFIMANAGER CRIADO;
        void saveConfigCallback ();
        String getEmail();
        String getPassword();
        void init();
        void resetWifiManager();
        void formatFileSystem();
        
        



        WiFiManager wifiManager;
        bool shouldSaveConfig = false;
        char email[100];
        char password[15];
};


















#endif