#ifndef CONECT_MANAGER_H
#define CONECT_MANAGER_H

#include <bluetooth_ble_lib.h>
#include <file_system_manager.h>
#include <WiFi.h>

#define TENTATIVAS_CONNECT_WIFI 20


class ConnectManagerClass 
{
    public:
        
        void bleSetupAndInit();
        bool checkDataCons();
        void disableBleAndConectWifi();
        void formatFileSystem();
        void initialFSconfigure();
        

    private:



        
};










#endif