#ifndef PPP_MQTT_H
#define PPP_MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>
#include <definicoes.h>

#define TOPICO_SUBSCRIBE_LED     "topico_button" 
#define TOPICO_SUBSCRIBE_STRING    "augusto.salto@hotmail.com[string]"
#define TOPICO_PUBLISH_BUTTOM   "topico_led"
  


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
    void setID(const char *id);

    // LISTA DE TOPICOS ESCRITOS!
    void subscribeTopic();

    // ENVIA UMA MENSAGEM A UM TOPICO
    void publishMsg(const char *topic, const char *msg);

    // LOOP DO MQTT
    void loop();

    // VERIFICA SE O MQTT ESTÁ RODANDO
    bool isConected();

    
      

};





#endif