#ifndef WIFI_BLE_MANAGER_H
#define WIFI_BLE_MANAGER_H

#include <bluetooth_ble_lib.h> 
#include <LITTLEFS.h>
#include <ArduinoJson.h> 


class WifiBleManager 
{
    public:
    
        WifiBleManager();    

        bool isConfigured();

        String getWifiSSID();
        String getWifiPassword();
        String getEmail();
        String getEmailPassword();
        String getNameSensor();
        String getMqttServer();
        String getMqttPort();

        bool setWifiSSID(char *SSIDname);
        bool setWifiPassword(char *SSIDpassword);
        bool setEmail(char *email);
        bool setEmailPassword(char *emailPassoword);
        bool setNameSensor(char *nameSensor);
        bool setMqttServer(char *mqttServer);
        bool setMqttPort(char *mqttPort); 


    private:

        char _wifiSSID[50];
        char _wifiPassword[25];
        char _email[100];
        char _emailPassoword[25];
        char _nameSensor[25];
        char _mqttServer[100];
        char _mqttPort[20];

        void _getStringFromFS(char *ptr,  const char* name);



        
};





#endif