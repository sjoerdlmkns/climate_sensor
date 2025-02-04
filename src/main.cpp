#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

// DHT Sensor
#define DHT_BUS 4
#define DHT_TYPE DHT11
DHT dht(DHT_BUS, DHT_TYPE);

// WIFI settings
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// MQTT Broker settings
#define MQTT_HOST IPAddress(0, 0, 0, 0)
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

// MQTT Topics
#define TOPIC "/sensor"

// Wifi managers
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

// Tickers
Ticker wifiReconnectTimer;
Ticker mqttReconnectTimer;

AsyncMqttClient mqttClient;

void connectToMqtt()
{
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("Disconnected from Wi-Fi.");
  wifiReconnectTimer.once(2, connectToWifi);
}



void onMqttConnect(bool sessionPresent)
{
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttPublish(uint16_t packetId)
{
Serial.print("Publish acknowledged.");
Serial.print("PacketId: ");
Serial.println(packetId);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");

  dht.begin();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCredentials(MQTT_USERNAME, MQTT_PASSWORD);

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