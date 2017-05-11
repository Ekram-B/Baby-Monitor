/* Author: Ekram Bhuiyan */

/* Includes */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/* Definitions */

#define ssid                 "****"
#define password             "****"
/* Required to add web application as a observer */
#define mqtt_server          "io.adafruit.com"
#define mqtt_server_port     1883
#define mqtt_user            "****"
#define mqtt_key             "*******************************"

/* Feed addresses for MQTT Feeds */
#define USERNAME             "******/"
#define PREAMBLE             "*****/"
#define T_GAUGE       "Baby Monitor Sensor"
#define T_GRAPH       "Baby Monitoring Graph"
#define T_CLIENTSTATUS       "clientStatus"
#define T_COMMAND            "command"

#define TRIG  16
#define ECHO  2

/* Global variables */
unsigned long entry;
byte clientStatus, prevClientStatus = 99;

float voltage;
char valueStr[5];
WiFiClient WiFiClient;
PubSubClient client(WiFiClient);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);                   
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(2000);                      
  Serial.print(".");
  }
  Serial.println("");
  digitalWrite(LED_BUILTIN, LOW );
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
}


void loop() {
  yield();
  if (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    /* Attempt to add the adadruit servers as an observer */
    if (client.connect("Baby monitor Gauge", mqtt_user, mqtt_key)) {
      Serial.println("connected to MQTT Broker");
      client.subscribe(USERNAME PREAMBLE T_COMMAND, 1);
      client.subscribe(USERNAME PREAMBLE "test", 1);
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  if (client.connected()) { 
    for (int j = 1; j <= 10; j++)
    {
        // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float acceleration = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(acceleration);
      Serial.println("Publish voltage");
      String hi = (String)acceleration;
      hi.toCharArray(valueStr, 4);
      client.publish(USERNAME PREAMBLE T_GAUGE, valueStr);
      client.publish(USERNAME PREAMBLE T_GRAPH, valueStr);
      delay(1000);
    }

  if (client.connected()&& prevClientStatus != clientStatus ) {
    Serial.println("Publish Status");
    String hi = (String)clientStatus;
    hi.toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE T_CLIENTSTATUS, valueStr);
    prevClientStatus = clientStatus;
  }
  client.loop();
}

void callback(char* topic, byte * data, unsigned int length) {
  //  handle message arrived {
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
  }
  Serial.println();
  if (data[1] == 'F')  {
    clientStatus = 0;
  } else {
    clientStatus = 1;
  }
}




