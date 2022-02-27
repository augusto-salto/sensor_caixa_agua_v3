#include <ppp_mqtt.h>

#define ID_MQTT  "esp32_mqtt_augustoCesarClient2" 

const char* BROKER_MQTT = "broker.mqtt-dashboard.com"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
char button_status[10]     = {0};
bool flagButton = false;
char id_mqtt[15];

WiFiClient espClient; 
PubSubClient MQTT(espClient); 


MqttClass::MqttClass(){

    

}

void MqttClass::setMqttServer(char *server){
    strcpy(this->_mqtt_server, server);
}

void MqttClass::setMqttPort(char *port){
    strcpy(this->_mqtt_port, port);
}



void MqttClass::begin()
{

// SET SERVER
char mqtt_server[MQTT_SERVER_SIZE];
fileSystemManager.getMqttServer().toCharArray(mqtt_server, MQTT_SERVER_SIZE);
this->setMqttServer(mqtt_server);

//SET PORT 
    char mqtt_port[MQTT_PORT_SIZE];
    fileSystemManager.getMqttPort().toCharArray(mqtt_port, MQTT_PORT_SIZE);
    this->setMqttPort(mqtt_port);

// SET ID
    // O FORMATO DO ID SERA: EMAIL+NAMESENSOR
    
    char mqtt_id[150];
    char buff[100];

    fileSystemManager.getEmail().toCharArray(buff, 100);

    strcpy(mqtt_id, buff);

    Serial.print("\n1: ");
    Serial.print(mqtt_id);
    Serial.print("\n");

    strcat(mqtt_id, ":");

    fileSystemManager.getNameSensor().toCharArray(buff, 100);

    Serial.print("\n2: ");
    Serial.print(mqtt_id);
    Serial.print("\n");

    strcat(mqtt_id, buff);

    this->setID(mqtt_id);

    Serial.print("\nO ID DO MQTT OBJECT É: ");
    Serial.print(mqtt_id);
    Serial.print("\n");

initMQTT();

}

void MqttClass::setID(const char *id)
{
    
    strcpy(id_mqtt, id);
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
 
    //Serial.print("\nChegou a seguinte string via MQTT: ");
    //Serial.print(msg);
    //Serial.print("\nTOPICO DE CHEGADA: ");
    //Serial.print(topic);
    
    
    if (String(topic).equals("augusto.salto@hotmail.com[string]")){
        //Serial.print("\nBUFFER DE MENSAGEM TOPICO STRING: " + String(msg));
    }else if (msg.equals("1"))
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
  
    if (msg.equals("0"))
    {
        digitalWrite(LED_BUILTIN, LOW);    
    }
}

void initMQTT(void) 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}


void reconnectMQTT(void) 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(id_mqtt)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE_LED); 
            MQTT.subscribe(TOPICO_SUBSCRIBE_STRING); 
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
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
}




void MqttClass::loop(){

    MQTT.loop();
        
}

void MqttClass::publishMsg(const char *topic, const char *msg)
{
        MQTT.publish(topic, msg);
}


bool MqttClass::isConected()
{
    if (!MQTT.connected())
    {
        reconnectMQTT();
    }

        return MQTT.connected();
}

