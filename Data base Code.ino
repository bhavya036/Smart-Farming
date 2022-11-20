#include "UbidotsESPMQTT.h"
#include <PubSubClient.h>
#include<DHT.h>
#define DHTPIN 14 ////NodeMCU GPIO14 Pin D5
const int sensor_pin = A0;
float sensorData = analogRead(A0);
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#define TOKEN "BBFF-juJ8AnLDWPD2d4OAz4FSybLcHFXUax" // Ubidots Token
#define WIFINAME "Bhavya's Narzo 20" //Your wifi SSID
#define WIFIPASS "11111111" // Your Wifi Password
Ubidots client(TOKEN);
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i=0;i<length;i++) {
  Serial.print((char)payload[i]);
}
Serial.println();
}
void setup() {
dht.begin();
client.setDebug(true); 
Serial.begin(115200);
client.wifiConnection(WIFINAME, WIFIPASS);
client.begin(callback);
}
void loop() {

if(!client.connected()){
client.reconnect();
}
// temperature,humidity & Soil Moisture
float Temperature = dht.readTemperature();
float Humidity = dht.readHumidity(); 
  /*Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");*/
  delay(1000);
client.add("temperature", Temperature);
client.ubidotsPublish("temperature");
client.add("humidity", Humidity); 
client.ubidotsPublish("humidity");
client.ubidotsPublish("temperature");
float moisture_percentage;
moisture_percentage = ( 100 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );
client.add("Soil Moisture", moisture_percentage);
client.loop();
delay(5000);
}
