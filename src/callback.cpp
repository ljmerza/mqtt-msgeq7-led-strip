#include <Arduino.h>
#include <ArduinoJson.h>

#include "common.h"
#include "callback.h"
#include "wifi_common.h"

#include "effects.h"
#include "music_effects.h"
#include "holiday_effects.h"
#include "light_effects.h"

const int BUFFER_SIZE = JSON_OBJECT_SIZE(10);

void callback(char* topic, byte* payload, unsigned int length) {
    
    Serial.println(' ');
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    char message[length + 1];
    for (int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
    }
    message[length] = '\0';
    Serial.println(message);

    if (!processJson(message)) {
        return;
    }

    setRealColors();

    // send state back to mqqt to keep things in sync with UI
    sendState();
}

void setRealColors() {
    if (showLeds) {
        realRed = map(red, 0, 255, 0, brightness);
        realGreen = map(green, 0, 255, 0, brightness);
        realBlue = map(blue, 0, 255, 0, brightness);

    } else {
        realRed = 0;
        realGreen = 0;
        realBlue = 0;
    }
}

void runEffect(){

    if (effectString == "Rainbow") {
        rainbow();
    } else if (effectString == "Rainbow With Glitter") {
        rainbowWithGlitter();
    } else if (effectString == "Confetti") {
        confetti();
    } else if (effectString == "Sinelon") {
        sinelon();
    } else if (effectString == "BPM") {
        bpm();
    } else if (effectString == "Juggle") {
        juggle();
    } else if (effectString == "Candy Cane") {
        candyCane();
    } else if (effectString == "Party Colors") {
        partyColors();
    } else if (effectString == "Rotate Party") {
        rotatePartyColors();
    } else if (effectString == "Music Rainbow") {
        musicRainbow();
    } else if (effectString == "Music RGB") {
        musicRGB();
    } else if (effectString == "Music Rotate Party") {
        musicRotatePartyColors();
    } else if (effectString == "Music Cycle") {
        musicPartyColor();
    } else if (effectString == "Fire") {
        fire();
    } else if (effectString == "Solid") {
        setColor(realRed, realGreen, realBlue);
    } else if (effectString == "Lightning") {
        lightning();
    } else if (effectString == "Ripple") {
        ripple();
    } else if (effectString == "Dots") {
        dots();
    } else if (effectString == "Noise") {
        noise();
    } else if (effectString == "Police All") {
        police_all();
    } else if (effectString == "Police One") {
        police_one();
    } else if (effectString == "Cyclon Rainbow") {
        cyclon_rainbow();
    } else if (effectString == "St Patty") {
        st_patty();
    } else if (effectString == "Christmas") {
        christmas();
    } else if (effectString == "Halloween") {
        halloween();
    } else if (effectString == "Pumpkin") {
        pumpkin();
    } else if (effectString == "USA") {
        usa();
    } else if (effectString == "Valentine") {
        valentine();
    } else if (effectString == "Thanksgiving") {
        thanksgiving();
    } else if (effectString == "Lamp Candle") {
        lamp_candle();
    } else if (effectString == "Lamp Tungsten 40w") {
        lamp_tungsten_40w();
    } else if (effectString == "Lamp Tungsten 100w") {
        lamp_tungsten_100w();
    } else if (effectString == "Lamp High Pressure Sodium") {
        lamp_high_pressure_sodium();
    } else if (effectString == "Solid Cloud") {
        cloudColors_p();
    } else if (effectString == "Solid Ocean") {
        oceanColors_p();
    } else if (effectString == "Solid Forest") {
        forestColors_p();
    } else if (effectString == "Solid Lava Colors") {
        lavaColors_p();
    } else if (effectString == "Solid Rainbow Stripes") {
        rainbowStripeColors_p();
    } else if (effectString == "Solid Party") {
        partyColors_p();
    } else if (effectString == "Solid Heat") {
        heatColors_p();
    } else if (effectString == "Twinkle") {
        twinkle();
    }
}

bool processJson(char* message) {
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(message);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return false;
    }

    // print the JSON to Serial
    root.prettyPrintTo(Serial);

    // reset strip colors
    reset_strip();

    // are we on or off?
    if (root.containsKey("state")) {
        if (strcmp(root["state"], on_cmd) == 0) {
            showLeds = true;
            
        } else if (strcmp(root["state"], off_cmd) == 0) {
            showLeds = false;
        }

        Serial.println(showLeds);
    }

    // set brightness
    if (root.containsKey("brightness")) {
        brightness = root["brightness"];
        FastLED.setBrightness(brightness);
    }

    // if we are cahnging color then do that
    if (root.containsKey("color")) {
        red = root["color"]["r"];
        green = root["color"]["g"];
        blue = root["color"]["b"];
    }
    
    // if there's an effect given then do that
    if (root.containsKey("effect")) {
        const char* effect = root["effect"];
        effectString = effect;
    }
    
    // if we were given a colortemp then do that
    // temp comes in as mireds, need to convert to kelvin then to RGB
    if (root.containsKey("color_temp")) {
        int color_temp = root["color_temp"];
        unsigned int kelvin  = 1000000 / color_temp;
        temp2rgb(kelvin);
    }

    return true;
}