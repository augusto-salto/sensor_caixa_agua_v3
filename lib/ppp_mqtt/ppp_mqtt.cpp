#include <ppp_mqtt.h>

#define ID_MQTT  "esp32_mqtt_augustoCesarClient2" 

const char* mqtt_broker_server; //URL do broker MQTT que se deseja utilizar
int mqtt_broker_port; // Porta do Broker MQTT
char button_status[10]     = {0};
bool flagButton = false;
char id_mqtt[15];
char send_topic[100];
char receive_topic[100];

char receive_from_android_buffer[100];


WiFiClient espClient; 
PubSubClient MQTT(espClient); 


MqttClass::MqttClass(){

    

}

void MqttClass::setMqttServer(){

    char mqtt_server[MQTT_SERVER_SIZE];
    fileSystemManager.getMqttServer().toCharArray(mqtt_server, MQTT_SERVER_SIZE);
    strcpy(this->_mqtt_server, mqtt_server);
    mqtt_broker_server = this->_mqtt_server;
}

void MqttClass::setMqttPort(){
    char mqtt_port[MQTT_PORT_SIZE];
    String buff;

    fileSystemManager.getMqttPort().toCharArray(mqtt_port, MQTT_PORT_SIZE);
    
    buff = String(mqtt_port);
    this->_mqtt_port = buff.toInt();
    mqtt_broker_port = this->_mqtt_port;
    Serial.print("\nMQTT PORT: " + this->_mqtt_port );
    
}

void MqttClass::setSubscribeTopics()
{
// SEND TOPIC: EMAIL (NAME) + NOMESENSOR + [sensorToAndroid] 
    String stringBuff;
    char charBuff[100];
    int index;

    stringBuff = fileSystemManager.getEmail();
    index = stringBuff.indexOf("@");
    stringBuff = stringBuff.substring(0, index);
    strcpy(charBuff, stringBuff.c_str());
    strcat(charBuff, ":");

    stringBuff = fileSystemManager.getNameSensor();
    
    strcat(charBuff, stringBuff.c_str());
    strcat(charBuff, ":");

    strcat(charBuff, "[sensorToAndroid]");
    
    strcpy(this->_send_to_android_topic, charBuff);
    strcpy(send_topic, this->_send_to_android_topic);

    

// RECEIVE TOPIC: EMAIL(NAME)+NOMESENSOR+[androidToSensor]
    
     stringBuff = fileSystemManager.getEmail();
    index = stringBuff.indexOf("@");
    stringBuff = stringBuff.substring(0, index);
    strcpy(charBuff, stringBuff.c_str());
    strcat(charBuff, ":");
    stringBuff = fileSystemManager.getNameSensor();

    strcat(charBuff, stringBuff.c_str());
    strcat(charBuff, ":");
    strcat(charBuff, "[androidToSensor]");

    strcpy(this->_receive_from_android_topic, charBuff);
    strcpy(receive_topic, this->_receive_from_android_topic);

    

}


void MqttClass::begin()
{
    this->setID();
    this->setMqttServer();
    this->setMqttPort();
    this->setSubscribeTopics();


initMQTT();

}

void MqttClass::setID()
{
    char mqtt_id[150];
    char buff[100];

    fileSystemManager.getEmail().toCharArray(buff, 100);

    strcpy(mqtt_id, buff);
    strcat(mqtt_id, ":");

    fileSystemManager.getNameSensor().toCharArray(buff, 100);

    strcat(mqtt_id, buff);
    strcpy(this->_mqtt_id, mqtt_id);
   
}









void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
  
    /* obtem a string do payload recebido */
    for(unsigned int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
 
    Serial.print("\nChegou a seguinte string via MQTT: ");
    Serial.print(msg);
    //Serial.print("\nTOPICO DE CHEGADA: ");
    //Serial.print(topic);
    
    
    /*if (String(topic).equals(receive_topic)){
        //Serial.print("\nBUFFER DE MENSAGEM TOPICO STRING: " + String(msg));
    }*/

   /* if (msg.equals("n"))  // ANDROID REQUEST 
    {
        char receiveBuff[5] = "n";
        xQueueOverwrite(xQueue_android_request, (void *)&receiveBuff);  
        
    }
  
    if (msg.equals("s"))
    {
        char receiveBuff[5] = "s";
        xQueueOverwrite(xQueue_android_request, (void *)&receiveBuff);     
    }*/


    char receiveBuff[5] = "0";
    strcpy(receiveBuff, msg.c_str());
    xQueueOverwrite(xQueue_android_request, (void *)&receiveBuff); 
    
}

void initMQTT(void) 
{
    MQTT.setServer(mqtt_broker_server, mqtt_broker_port);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui fun????o de callback (fun????o chamada quando qualquer informa????o de um dos t??picos subescritos chega)
}


void reconnectMQTT(void) 
{
    while (!MQTT.connected()) 
    {
        Serial.print("Broker MQTT: ");
        Serial.println(mqtt_broker_server);

        if (MQTT.connect(id_mqtt)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            Serial.print("SEND TOPIC: ");
            Serial.print(send_topic);
            Serial.print("\n");
            Serial.print("RECEIVE TOPIC: ");
            Serial.print(receive_topic);
            Serial.print("\n");
            //MQTT.subscribe(send_topic); 
            MQTT.subscribe(receive_topic); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se n??o h?? conex??o com o Broker, a conex??o ?? refeita
}




void MqttClass::loop(){

    MQTT.loop();
        
}

void MqttClass::publishMsg(const char *msg)
{
        MQTT.publish(send_topic, msg);
}


bool MqttClass::isConected()
{
    if (!MQTT.connected())
    {
        reconnectMQTT();
    }

        return MQTT.connected();
}

