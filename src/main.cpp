#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

// DHT Sensor
#define DHT_BUS 4
#define DHT_TYPE DHT11
DHT dht(DHT_BUS, DHT_TYPE);

// WIFI settings
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Wifi managers
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("Connected to Wi-Fi.");
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("Disconnected from Wi-Fi.");
  wifiReconnectTimer.once(2, connectToWifi);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  dht.begin();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);

  connectToWifi();
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println(temperature);
  Serial.println(humidity);

  delay(1000);
}