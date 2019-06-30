#ifndef CONFIG_GUARD 
#define CONFIG_GUARD

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <MSGEQ7.h>
#include <PubSubClient.h>

// MQTT Topics
#define LIGHT_STATE_TOPIC "led/kitchen"
#define LIGHT_SET_TOPIC "led/kitchen/set"

// Credentials
#define HOSTNAME "esp8266-light-strip"

#define MY_SSID ""
#define MY_PASSWORD ""

#define MQTT_SERVER ""
#define mqtt_username ""
#define mqtt_password ""

// OTA Settings
#define OTA_PORT 8266

// LED Config
#define DATA_PIN 5
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 150
#define FRAMES_PER_SECOND 60

#define INITIAL_LED_STATE false
#define INITIAL_BRIGHTNESS 100
#define INITIAL_RED 50
#define INITIAL_GREEN 50
#define INITIAL_BLUE 50

// Audio Processing Config
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH 200
#define MSGEQ7_PIN_ANALOG A0
#define MSGEQ7_PIN_RESET 14
#define MSGEQ7_PIN_STROBE 4

// FIRE
#define COOLING  55
#define SPARKING 120

#endif