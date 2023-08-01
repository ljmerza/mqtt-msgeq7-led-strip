#include <Arduino.h>
#include <ArduinoJson.h>

#include "common.h"
#include "callback.h"
#include "wifi_common.h"

#include "effects.h"
#include "music_effects.h"
#include "holiday_effects.h"
#include "light_effects.h"

StaticJsonDocument<256> json_doc;


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.println("Message arrived on topic: " + String(topic));

    // Clear the previous JSON data
    json_doc.clear();

    // Parse the incoming JSON data
    DeserializationError error = deserializeJson(json_doc, payload, length);

    // Check for parsing errors
    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        return;
    }

    serializeJsonPretty(json_doc, Serial);
    process_json(json_doc);
    
    set_real_colors();

    // send state back to mqqt to keep things in sync with UI
    send_state();
}

void set_real_colors() {
    if (show_leds) {
        real_red = map(red, 0, 255, 0, brightness);
        real_green = map(green, 0, 255, 0, brightness);
        real_blue = map(blue, 0, 255, 0, brightness);

    } else {
        real_red = 0;
        real_green = 0;
        real_blue = 0;
    }
}

bool run_effect(){
    if (effect_string == "Rainbow") {
        rainbow();
    } else if (effect_string == "Rainbow With Glitter") {
        rainbow_with_glitter();
    } else if (effect_string == "Confetti") {
        confetti();
    } else if (effect_string == "Sinelon") {
        sinelon();
    } else if (effect_string == "BPM") {
        bpm();
    } else if (effect_string == "Juggle") {
        juggle();
    } else if (effect_string == "Candy Cane") {
        candy_cane();
    } else if (effect_string == "Party Colors") {
        party_colors();
    } else if (effect_string == "Rotate Party") {
        rotate_party_colors();
    } else if (effect_string == "Music Rainbow") {
        music_rainbow();
    } else if (effect_string == "Music RGB") {
        music_rgb();
    } else if (effect_string == "Music Rotate Party") {
        music_rotate_party_colors();
    } else if (effect_string == "Music Cycle") {
        music_party_color();
    } else if (effect_string == "Fire") {
        fire();
    } else if (effect_string == "Solid") {
        set_color(real_red, real_green, real_blue);
    } else if (effect_string == "Lightning") {
        lightning();
    } else if (effect_string == "Ripple") {
        ripple();
    } else if (effect_string == "Dots") {
        dots();
    } else if (effect_string == "Noise") {
        noise();
    } else if (effect_string == "Police All") {
        police_all();
    } else if (effect_string == "Police One") {
        police_one();
    } else if (effect_string == "Cyclon Rainbow") {
        cyclon_rainbow();
    } else if (effect_string == "St Patty") {
        st_patty();
    } else if (effect_string == "Christmas") {
        christmas();
    } else if (effect_string == "Halloween") {
        halloween();
    } else if (effect_string == "Pumpkin") {
        pumpkin();
    } else if (effect_string == "USA") {
        usa();
    } else if (effect_string == "Valentine") {
        valentine();
    } else if (effect_string == "Thanksgiving") {
        thanksgiving();
    } else if (effect_string == "Lamp Candle") {
        lamp_candle();
    } else if (effect_string == "Lamp Tungsten 40w") {
        lamp_tungsten_40w();
    } else if (effect_string == "Lamp Tungsten 100w") {
        lamp_tungsten_100w();
    } else if (effect_string == "Lamp High Pressure Sodium") {
        lamp_high_pressure_sodium();
    } else if (effect_string == "Solid Cloud") {
        cloud_colors_p();
    } else if (effect_string == "Solid Ocean") {
        ocean_colors_p();
    } else if (effect_string == "Solid Forest") {
        forest_colors_p();
    } else if (effect_string == "Solid Lava Colors") {
        lava_colors_p();
    } else if (effect_string == "Solid Rainbow Stripes") {
        rainbow_stripe_colors();
    } else if (effect_string == "Solid Party") {
        party_colors_p();
    } else if (effect_string == "Solid Heat") {
        heatColors_p();
    } else if (effect_string == "Twinkle") {
        twinkle();
    } else if (effect_string == "Music BPM") {
        music_bpm();
    } else if (effect_string == "Music Volume") {
        music_volume();
    } else if (effect_string == "Music Average") {
        music_average();
    } else if (effect_string == "Music Average") {
        music_average();
    }else if (effect_string == "Music Lines") {
        music_lines();
        return true;
    }

    return false;
}


void process_json(StaticJsonDocument<256>& json_doc) {
    // reset strip colors
    reset_strip();

    // are we on or off?
    if (json_doc.containsKey("state")) {
        if (strcmp(json_doc["state"], on_cmd) == 0) {
            show_leds = true;
        } else if (strcmp(json_doc["state"], off_cmd) == 0) {
            show_leds = false;
        }
    }

    Serial.println(show_leds);

    // set brightness
    if (json_doc.containsKey("brightness")) {
        brightness = json_doc["brightness"];
        FastLED.setBrightness(brightness);
    }

    // if we are cahnging color then do that
    if (json_doc.containsKey("color")) {
        JsonArray color = json_doc["color"];
        red = color[0];
        green = color[1];
        blue = color[2];
    }
    
    // if there's an effect given then do that
    if (json_doc.containsKey("effect")) {
        const char* effect = json_doc["effect"];
        effect_string = effect;
    }
    
    // if we were given a color_temp then do that
    // temp comes in as mireds, need to convert to kelvin then to RGB
    if (json_doc.containsKey("color_temp")) {
        color_temp = json_doc["color_temp"];
        unsigned int kelvin  = 1000000 / color_temp;
        temp2rgb(kelvin);
    }
}