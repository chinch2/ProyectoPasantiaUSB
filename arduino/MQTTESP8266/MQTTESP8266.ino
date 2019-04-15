#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

String deviceserial = String(ESP.getChipId());// "ChipId"
String topic1 = "/devices/" + deviceserial;// "/devices/ChipId"
String topic2 = "/status/" + deviceserial;// "/status/ChipId"
String ACAP = "door2bot " + deviceserial;// "door2bot ChipId"
String versionn = "0.9";// "0.9"
String clientconnect = "/devices_" + deviceserial;

char deviceserialc[10];
char topic1c[20];
char topic2c[20];
char ACAPc[20];
char versionnc[5];
char clientconnectc[20];

int RelayPin = 2;    // RELAY connected to digital pin 2

//change with your MQTT server IP address
const char* mqtt_server = "10.20.184.10";//"144.202.36.117";

WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {

  char* payload_str;
  payload_str = (char*) malloc(length + 1);
  memcpy(payload_str, payload, length);
  payload_str[length] = '\0';
  //Serial.println(String(payload_str));
  if ( String(topic) == topic1 ) {
    if (String(payload_str) == "on" ) {
      digitalWrite(RelayPin, LOW);   // turn the RELAY on
      delay(1000);
      digitalWrite(RelayPin, HIGH);
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

void mqttreconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = clientconnect;
    // Attempt to connect
    clientconnect.toCharArray(clientconnectc, clientconnect.length() + 1);
    if (client.connect(clientconnectc)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      topic2.toCharArray(topic2c, topic2.length() + 1);
      client.publish(topic2c, "reconectado");
      // ... and resubscribe
      topic1.toCharArray(topic1c, topic1.length() + 1);
      client.subscribe(topic1c);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  deviceserial.toCharArray(deviceserialc, deviceserial.length() + 1);
  topic1.toCharArray(topic1c, topic1.length() + 1);
  topic2.toCharArray(topic2c, topic2.length() + 1);
  ACAP.toCharArray(ACAPc, ACAP.length() + 1);
  versionn.toCharArray(versionnc, versionn.length() + 1);
  clientconnect.toCharArray(clientconnectc, clientconnect.length() + 1);

  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();
  wifiManager.setTimeout(180);
  Serial.begin(9600);
  delay(10);

  if (!wifiManager.autoConnect(ACAPc)) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("connected...yeey :)");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  client.connect(clientconnectc);

  Serial.println("MQTT iniciado");

  client.subscribe(topic1c);
  client.publish(topic2c, "online");

  // initialize pin 2, where the relay is connected to.
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH);
}

int tellstate = 0;

void loop() {

  client.loop();
  yield();
  if (! client.connected()) {
    Serial.println("Not connected to MQTT....");
    mqttreconnect();
  }

  // Tell the current state every 60 seconds
  if ( (millis() - tellstate) > 60000 ) {
    //  if ( digitalRead(RelayPin) ) {
    client.publish(topic2c, "0.9");
    Serial.println("version publicada");
    //  } else {
    //    client.publish("house/2/attic/cv/thermostat/relay_state", "off");
    // }
    tellstate = millis();
  }
}
