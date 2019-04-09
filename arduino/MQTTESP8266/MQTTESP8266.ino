/*
    This code switches a relay connected to port 2 (GPIO2) on an ESP8266.

    It will connect to MQTT and listens on topic house/2/attic/cv/thermostat/relay
    for 'on' and 'off' commands. Every 60 seconds, it will publishes tHe current
    state on house/2/attic/cv/thermostat/relay_state

    Dimitar Manovski
    support@smart-republic.com



*/


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int RelayPin = 2;    // RELAY connected to digital pin 2

const char* ssid     = "PNP";
const char* password = "PNPSISTEMAS";

//change with your MQTT server IP address
const char* mqtt_server = "10.20.184.10";


WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(topic);
  Serial.print(" => ");

  char* payload_str;
  payload_str = (char*) malloc(length + 1);
  memcpy(payload_str, payload, length);
  payload_str[length] = '\0';
  Serial.println(String(payload_str));
  if ( String(topic) == "puerta/12345" ) {
    if (String(payload_str) == "on" ) {
      digitalWrite(RelayPin, HIGH);   // turn the RELAY on
      delay(1000);
      digitalWrite(RelayPin, LOW);
      //client.publish("house/2/attic/cv/thermostat/relay_state", "on");
    } /*else if ( String(payload_str) == "off" ) {
      digitalWrite(RelayPin, LOW);    // turn the RELAY off
      //client.publish("house/2/attic/cv/thermostat/relay_state", "off");
    } else {
      Serial.print("I do not know what to do with ");
      Serial.print(String(payload_str));
      Serial.print(" on topic ");
      Serial.println( String(topic));
    }*/
  }
}

void connect_to_MQTT() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  if (client.connect("puerta_12345")) {
    Serial.println("(re)-connected to MQTT");
    client.subscribe("puerta/12345");
  } else {
    Serial.println("Could not connect to MQTT");
  }
}

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connecting to our WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  /* Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  */
  connect_to_MQTT();

  // initialize pin 2, where the relay is connected to.
  pinMode(RelayPin, OUTPUT);
}

int tellstate = 0;

void loop() {
  client.loop();

  if (! client.connected()) {
    Serial.println("Not connected to MQTT....");
    connect_to_MQTT();
    delay(5000);
  }

  // Tell the current state every 60 seconds
  if ( (millis() - tellstate) > 60000 ) {
    //  if ( digitalRead(RelayPin) ) {
    client.publish("puerta/12345", "epale");
    //  } else {
    //    client.publish("house/2/attic/cv/thermostat/relay_state", "off");
    // }
    tellstate = millis();
  }
}
