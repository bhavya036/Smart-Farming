//#include "UbidotsESPMQTT.h"
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define pump D0
//#define TOKEN ""
//#define WIFISSID "Bhavya's Narzo 20";
//#define PASSWORD "11111111";
const int sensor_pin = A0;
float sensorData = analogRead(A0);
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  //pinMode(LED, OUTPUT);
}

void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float moisture_percentage;
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  moisture_percentage = ( 100 - ( (analogRead(sensor_pin) / 1024.00) * 100.00 ) );
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(F("°F"));
  Serial.print("\n Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.print("%");
  delay(500);
 // digitalWrite(LED,HIGH);
 // delay (1000);
  if ( 80 > moisture_percentage > 20)
  {
    digitalWrite(pump,1);
    delay(5000);
  //  digitalWrite(pump,0);
 
  }
  else
  {
    digitalWrite(pump,0);
    
  }

}
