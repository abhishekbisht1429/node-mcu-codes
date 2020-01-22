#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Tony Stark";
const char* pass = "eighttoone";
const char* mqtt_server = "192.168.43.165";
int mqttPort = 1883;
const char* espTopic = "lock";
int ledPin = 13;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
void setup() {
    Serial.begin(115200);
    Serial.println("initiating");

    WiFi.begin("Tony Stark", "eighttoone");
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    pinMode(ledPin, OUTPUT);
    
    Serial.println("Setting up mqtt client");
    mqttClient.setServer(mqtt_server, mqttPort);
    mqttClient.setCallback(callback);
}

void callback(const char* topic, byte* payload, unsigned int length) {
    Serial.println("message arrived");
    Serial.print("Topic : ");
    Serial.println(topic);
    String topicStr = String(topic);
    if(topicStr.equals(String(espTopic))) {
        byte msg[length];
        for(int i=0;i<length;++i) {
            msg[i] = payload[i];
        }
        Serial.print("Message : ");
        Serial.println(msg[0]);
        if(msg[0]==48) {
            digitalWrite(ledPin, LOW);
        } else {
            digitalWrite(ledPin, HIGH);
        }
    }
}

void connectMqtt() {
    while(!mqttClient.connected()) {
        Serial.println("Connecting...");
        if(mqttClient.connect("ESP8266Client")) {
            Serial.println("Connected");
            mqttClient.subscribe(espTopic);
        } else {
            Serial.print("Failed, rc = ");
            Serial.println(mqttClient.state());
        }
    }
}

void loop() {
    if(!mqttClient.connected()) {
        connectMqtt();
    }
    mqttClient.loop();
}