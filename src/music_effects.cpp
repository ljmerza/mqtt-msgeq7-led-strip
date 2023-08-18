#include <iostream>
#include <algorithm>

#include "config.h"
#include "common.h"
#include "music_effects.h"

#define MSGEQ7_NUM_BANDS 7

uint8_t get_bass_reading() {
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_0, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq1);
    uint8_t freq = max(freq0, freq1);

    return freq;
}

uint8_t get_mid_reading() {
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_2, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_3, 0);
    uint8_t freq2 = MSGEQ7.get(MSGEQ7_4, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq1);
    freq2 = mapNoise(freq2);

    uint8_t freq = max(freq0, freq1);
    freq = max(freq, freq2);

    return freq;
}

uint8_t get_treble_reading() {
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_5, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_6, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq0);
    uint8_t freq = max(freq0, freq1);

    return freq;
}

uint8_t linear_scale(uint8_t input_value) {
    const uint8_t input_min = 75;
    const uint8_t input_max = 230;
    
    const uint8_t output_min = 0;
    const uint8_t output_max = 255;

    double scaled_value = ((input_value - input_min) / static_cast<double>(input_max - input_min)) * (output_max - output_min) + output_min;

    if (scaled_value < output_min) {
        scaled_value = output_min;
    }
    if (scaled_value > output_max) {
        scaled_value = output_max;
    }

    return static_cast<int>(scaled_value);
}

void set_freq_to_brightness() {
    uint8_t freq = get_bass_reading();
    freq = linear_scale(freq);
    FastLED.setBrightness(freq);
}

#define NUMBEROFLINES 1 // number of LED lines on strip at one time
#define LINELENGTH 4 // length of each LED line
#define EIGHTBIT 255
#define HUESPEED 5 // how fast the hue increments for each LED movement
#define LEDSPEED 1 // how fast the LED lines move in ms - affects MSGEQ7 reads
int hues[NUMBEROFLINES] = {0}; // the hue of each line at any given point in time
int positions[NUMBEROFLINES] = {0}; // positions of lines at any given point in time

void music_lines() {
    MSGEQ7.read(100);
    uint8_t freq = get_bass_reading();
    freq = linear_scale(freq);
    Serial.println(freq);

    // Loop through each line
    for(unsigned int k = 0; k < NUMBEROFLINES; k++) {

	    // For each LED in the led line, add color with the given brightness (freq)
        for (int i = 0; i < LINELENGTH; i++) {
            int led_index = positions[k] + i;
            if (led_index < NUM_LEDS) {
                // Set the color of the LED using CHSV(hue, saturation, brightness)
                leds[led_index] = CHSV(hues[k], 255, freq);
            }
        }

	    // Turn off the previous LED in the line, and increment the position for the next iteration
        // this moves the line forward
        if (positions[k] > 0) {
            leds[positions[k]] = CRGB::Black;
        }
        positions[k]++;

	    // increment hue and check of hue max
	    hues[k] += HUESPEED;
	    if (hues[k] > EIGHTBIT) {
	    	hues[k] = 0;
	    }

	    // Check if the line's position has reached the end of the strip
	    if (positions[k] > NUM_LEDS) {
	        positions[k] = 0;
	    }
	}

    // delay until next led change
	delay(LEDSPEED);
}


int max_brightness = 0;  // Variable to keep track of the maximum brightness
int frame_count = 0;  // Counter to keep track of the number of frames
float scale_factor = 1.02; // Initialize scale_factor
float bias = 1; // Initialize bias
CHSV hsvLeds[NUM_LEDS];  // add a parallel CHSV array

// Function to map the noise value to a brightness value
#define READING_FUNCTIONS 2
uint8_t (*get_reading_functions[READING_FUNCTIONS])() = {get_bass_reading, get_mid_reading};

void music_seven_channels() {
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    int MSGEQ7_values[MSGEQ7_NUM_BANDS];

    for (int i = 0; i < 7; ++i) {
        MSGEQ7_values[i] = get_reading_functions[i % READING_FUNCTIONS]();
    }

    fill_rainbow(hsvLeds, NUM_LEDS, gHue, 10);  // fill LEDs with moving rainbow

    for (int i = 0; i < NUM_LEDS; i++) {
        int band = i % MSGEQ7_NUM_BANDS;
        
        int brightness = pow(MSGEQ7_values[band], scale_factor * bias);
        brightness = constrain(brightness, 0, 255);

        hsvLeds[i].value = brightness; // adjust the brightness
        leds[i] = hsvLeds[i]; // convert CHSV to CRGB
        max_brightness = max(max_brightness, brightness);
    }

    frame_count++;
    // Every 60 frames, adjust the scale_factor and bias to keep the brightness thresholds from moving too quickly.
    if (frame_count >= 60) {
        // Serial.print(max_brightness);
        // Serial.print(" ");
        // Serial.print(scale_factor);
        // Serial.print(" ");
        // Serial.println(bias);

        if (max_brightness < 100) {
            scale_factor *= 1.15;
            bias += 0.5;
        } else if (max_brightness > 250) {
            scale_factor *= 0.85;
            bias -= 0.05;
        }

        scale_factor = constrain(scale_factor, 1.02, 1.5);
        bias = constrain(bias, 1.0, 1.5);

        max_brightness = 0;
        frame_count = 0;
    }
}

void music_bpm(){
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    set_freq_to_brightness();
    bpm();
}

void music_rainbow() {
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    set_freq_to_brightness();
    rainbow();
}

void music_party_colors() {
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    set_freq_to_brightness();
    party_colors();
}

void music_rotate_party_colors() {
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    set_freq_to_brightness();
    rotate_party_colors();
}

void music_rgb() {
    bool new_reading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!new_reading) return;

    uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);
    uint8_t freq3 = MSGEQ7.get(MSGEQ7_3, 0);
    uint8_t freq5 = MSGEQ7.get(MSGEQ7_5, 0);

    freq1 = mapNoise(freq1);
    freq3 = mapNoise(freq3);
    freq5 = mapNoise(freq5);

    fill_solid(leds, NUM_LEDS, CRGB(freq1, freq3, freq5));
    fadeToBlackBy(leds, NUM_LEDS, 10);
}
