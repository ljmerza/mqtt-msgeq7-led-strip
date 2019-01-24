
#ifndef COMMON_GUARD
#define COMMON_GUARD

#include <Arduino.h>
#include <FastLED.h>
#include <MSGEQ7.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

extern PubSubClient client;

extern int red;
extern int green;
extern int blue;

extern int realRed;
extern int realGreen;
extern int realBlue;

extern bool showLeds;

extern int brightness;
extern uint8_t gHue; // rotating "base color" used by many of the patterns

extern const char* on_cmd;
extern const char* off_cmd;
extern String effectString; // which effect do we want

extern CMSGEQ7<MSGEQ7_SMOOTH, MSGEQ7_PIN_RESET, MSGEQ7_PIN_STROBE, MSGEQ7_PIN_ANALOG> MSGEQ7;
extern CRGB leds[NUM_LEDS];

String rgbString();
void runLedLights();



#endif