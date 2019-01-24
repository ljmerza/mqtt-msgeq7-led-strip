
#include "config.h"
#include "common.h"
#include "callback.h"
#include "wifi_common.h"
#include "effects.h"
#include "music_effects.h"

void setup() {
    MSGEQ7.begin();
    Serial.begin(115200);

    setup_wifi();

    client.setServer(MQTT_SERVER, 1883);
    client.setCallback(callback);

    setupOTA();

    // Setting up heartbeat
    pinMode(LED_BUILTIN, OUTPUT);

    brightness = BRIGHTNESS;
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(brightness);

    // send state to mqqt to keep things in sync with UI
    sendState();
}

void loop() {

    if (!client.connected()) {
        delay(1);
        Serial.println("Attempting MQTT connection...");
        reconnect_mqtt();
        return;
    }

    if (WiFi.status() != WL_CONNECTED) {
        delay(1);
        Serial.println("Attempting WIFI connection...");
        setup_wifi();
        return;
    }

    // Process MQTT tasks
    client.loop();

    // Handle OTA
    ArduinoOTA.handle();

    if (showLeds) {
        FastLED.setBrightness(brightness);
        runEffect();
        FastLED.show();
    }

    // Insert a delay to keep the framerate modest
    delay(1000 / FRAMES_PER_SECOND);

    // Slowly cycle the "base color" through the rainbow
    EVERY_N_MILLISECONDS(10) {
        gHue++;
    }
}
