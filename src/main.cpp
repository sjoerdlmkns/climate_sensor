#include <DHT.h>

#define DHT_BUS 4
#define DHT_TYPE DHT11
DHT dht(DHT_BUS, DHT_TYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  dht.begin();
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println(temperature);
  Serial.println(humidity);

  delay(1000);
}