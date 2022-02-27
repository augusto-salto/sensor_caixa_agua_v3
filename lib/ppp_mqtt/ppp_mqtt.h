#ifndef PPP_MQTT_H
#define PPP_MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>
#include <definicoes.h>
#include <file_system_manager.h>

#define TOPICO_SUBSCRIBE_LED     "topico_button" 
#define TOPICO_SUBSCRIBE_STRING    "augusto.salto@hotmail.com[string]"
#define TOPICO_PUBLISH_BUTTOM   "topico_led"

#define SEND_TOPIC_SIZE 100
#define RECEIVE_TOPIC_SIZE 100
#define MQTT_ID_SIZE 150 

extern FileSystemManager fileSystemManager;

    void initMQTT(void);
    void mqtt_callback(char* topic, byte* payload, unsigned int length);
    void reconnectMQTT(void);
    void reconnectWiFi(void);
    void VerificaConexoesWiFIEMQTT(void);



class MqttClass 
{
    public:
        MqttClass();   

    // INICIA O MQTT (DEFINIR O ID ANTES!)
    void begin();

    // SET O ID DO ESP NO BROKER MQTT
    void setID();
    void setMqttServer();
    void setMqttPort();
    void setSubscribeTopics();

    // LISTA DE TOPICOS ESCRITOS!
    void subscribeTopic();

    // ENVIA UMA MENSAGEM A UM TOPICO
    void publishMsg(const char *topic, const char *msg);

    // LOOP DO MQTT
    void loop();

    // VERIFICA SE O MQTT ESTÁ RODANDO
    bool isConected();

private:
    char _mqtt_server[MQTT_SERVER_SIZE];
    int _mqtt_port;
    char _mqtt_id[MQTT_ID_SIZE];

    char _send_to_android_topic[SEND_TOPIC_SIZE];
    char _receive_from_android_topic[RECEIVE_TOPIC_SIZE];

};





#endif