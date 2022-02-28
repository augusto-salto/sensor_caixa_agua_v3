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
#define JSON_ADDR_CONFIG_STATUS      "configStatus"

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

        void format();
        void initialState();
        
        bool isConfigured();

        String getWifiSSID();
        String getWifiPassword();
        String getEmail();
        String getEmailPassword();
        String getNameSensor();
        String getMqttServer();
        String getMqttPort();
        String getConfigOk();

        bool setWifiSSID(char *SSIDname);
        bool setWifiPassword(char *SSIDpassword);
        bool setEmail(char *email);
        bool setEmailPassword(char *emailPassoword);
        bool setNameSensor(char *nameSensor);
        bool setMqttServer(char *mqttServer);
        bool setMqttPort(char *mqttPort); 
        bool setConfigStatus(char *configStatus); 
        
        


    private:

        char _wifiSSID[SSID_NAME_SIZE] = "N/A";
        char _wifiPassword[SSID_PASSWORD_SIZE] = "N/A";
        char _email[EMAIL_SIZE] = "N/A";
        char _emailPassoword[EMAIL_PASSWORD_SIZE] = "N/A";
        char _nameSensor[NAME_SENSOR_SIZE] = "N/A";
        char _mqttServer[MQTT_SERVER_SIZE] = "N/A";
        char _mqttPort[MQTT_PORT_SIZE] = "N/A";
        char _configStatus[10] = "N/A";

        void _getStringFromFS(char *ptr,  const char* name);
        bool _setStringToFS();



        
};





#endif