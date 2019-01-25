#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "common.h"
#include "effects.h"
#include "music_effects.h"

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

WiFiClient wifiClient;
PubSubClient client(wifiClient);

bool showLeds = INITIAL_LED_STATE;
CRGB leds[NUM_LEDS];
int brightness = 0;

CMSGEQ7<MSGEQ7_SMOOTH, MSGEQ7_PIN_RESET, MSGEQ7_PIN_STROBE, MSGEQ7_PIN_ANALOG> MSGEQ7;

const char* on_cmd = "ON";
const char* off_cmd = "OFF";
String effectString = "Solid";

int red = 0;
int green = 0;
int blue = 0;

int realRed = 0;
int realGreen = 0;
int realBlue = 0;

void runLedLights(){
    if (showLeds) {
        FastLED.setBrightness(brightness);
        FastLED.show();
    }
}

String rgbString() {
    String rgb;
    rgb = String(red) + ',' + String(green) + ',' + String(blue);
    return rgb;
}