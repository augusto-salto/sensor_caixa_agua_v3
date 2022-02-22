#ifndef WIFI_BLE_MANAGER_H
#define WIFI_BLE_MANAGER_H

//#include <bluetooth_ble_lib.h> 
#include <LITTLEFS.h>
#include <ArduinoJson.h> 

#define JSON_ADDR_SSID_NAME         "wifiSSID"
#define JSON_ADDR_SSID_PASSWORD     "wifiPassword"
#define JSON_ADDR_EMAIL             "email"
#define JSON_ADDR_EMAIL_PASSWORD    "passwordEmail"
#define JSON_ADDR_NAME_SENSOR       "nameSensor"
#define JSON_ADDR_MQTT_SERVER       "mqttServer"
#define JSON_ADDR_MQTT_PORT         "mqttPort"

#define SSID_NAME_SIZE 50
#define SSID_PASSWORD_SIZE 25
#define EMAIL_SIZE 100
#define EMAIL_PASSWORD_SIZE 25
#define NAME_SENSOR_SIZE 25
#define MQTT_SERVER_SIZE 100
#define MQTT_PORT_SIZE 20


class FileSystemManager 
{
    public:
    
        FileSystemManager();    

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
        bool _setStringToFS();



        
};





#endif