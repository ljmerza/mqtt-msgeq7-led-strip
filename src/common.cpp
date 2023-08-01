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

bool show_leds = INITIAL_LED_STATE;
CRGB leds[NUM_LEDS];
int brightness = 0;

CMSGEQ7<MSGEQ7_SMOOTH, MSGEQ7_PIN_RESET, MSGEQ7_PIN_STROBE, MSGEQ7_PIN_ANALOG> MSGEQ7;

const char* on_cmd = "on";
const char* off_cmd = "off";
String effect_string = "Solid";

int red = 0;
int green = 0;
int blue = 0;

int color_temp = 0;

int real_red = 0;
int real_green = 0;
int real_blue = 0;

void run_led_lights(){
    if (show_leds) {
        FastLED.setBrightness(brightness);
        FastLED.show();
    }
}

String rgb_string() {
    String rgb;
    rgb = String(red) + ',' + String(green) + ',' + String(blue);
    return rgb;
}