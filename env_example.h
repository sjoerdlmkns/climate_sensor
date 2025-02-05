#include <DHT.h>

#ifndef ENV_H
#define ENV_H

// General
#define SENSOR_ID 1

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

#endif 
