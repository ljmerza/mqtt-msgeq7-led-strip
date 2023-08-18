
#define FASTLED_ALLOW_INTERRUPTS 0

#include "config.h"
#include "common.h"
#include "callback.h"
#include "wifi_common.h"
#include "effects.h"
#include "music_effects.h"

void setup() {
    MSGEQ7.begin();
    Serial.begin(115200);

    red = INITIAL_RED;
    green = INITIAL_GREEN;
    blue = INITIAL_BLUE;

    effect_string = INITIAL_EFFECT;
    brightness = INITIAL_BRIGHTNESS;

    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(brightness);

    // reset LEDs
    FastLED.clear();
    FastLED.show();

    setup_wifi();
    setup_ota();

    client.setServer(MQTT_SERVER, 1883);
    client.setCallback(callback);

}

void loop() {

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Attempting WIFI connection...");
        setup_wifi();
    }

    if (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        reconnect_mqtt();
        send_state();

    }

    // Process MQTT tasks
    client.loop();

    // Handle OTA
    ArduinoOTA.handle();

    if (show_leds) {
        run_effect();
        FastLED.show();
    } else {
        FastLED.clear();
        FastLED.show();
    }

    // Insert a delay to keep the framerate modest
    delay(1000 / FRAMES_PER_SECOND);

    // Slowly cycle the "base color" through the rainbow
    EVERY_N_MILLISECONDS(10) {
        nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges); // for NOISE animation
        gHue++;
    }
}
