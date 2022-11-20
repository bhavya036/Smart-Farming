#include "UbidotsESPMQTT.h"
#include <PubSubClient.h>
#include<DHT.h>
#define DHTPIN 14 ////NodeMCU GPIO14 Pin D5
const int sensor_pin = A0;
float sensorData = analogRead(A0);
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
/****************************************
* Define Constants
****************************************/
#define TOKEN "BBFF-juJ8AnLDWPD2d4OAz4FSybLcHFXUax" // Your Ubidots TOKEN
#define WIFINAME "Bhavya's Narzo 20" //Your wifi SSID
#define WIFIPASS "11111111" // Your Wifi Password
Ubidots client(TOKEN);
/****************************************
* Auxiliar Functions
****************************************/
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i=0;i<length;i++) {
  Serial.print((char)payload[i]);
}
Serial.println();
}
/****************************************
* Main Functions
****************************************/
void setup() {
dht.begin();
// put your setup code here, to run once:
client.setDebug(true); //Pass a true or false bool value to activate debug messages
Serial.begin(115200);
client.wifiConnection(WIFINAME, WIFIPASS);
client.begin(callback);
}
void loop() {
// put your main code here, to run repeatedly:
if(!client.connected()){
client.reconnect();
}
// Publish temperature,humidity & Soil Moisture
float Temperature = dht.readTemperature();
float Humidity = dht.readHumidity(); 
  /*Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");*/
  delay(1000);
client.add("temperature", Temperature);
client.ubidotsPublish("temperature");
client.add("humidity", Humidity); //Insert your variable Labels and the value to be sent
client.ubidotsPublish("humidity");
client.ubidotsPublish("temperature");
float moisture_percentage;
moisture_percentage = ( 100 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );
client.add("Soil Moisture", moisture_percentage);
client.loop();
delay(5000);
}
