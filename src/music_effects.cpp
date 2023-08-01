#include "config.h"
#include "common.h"
#include "music_effects.h"


uint8_t get_bass_reading() {
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_0, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq1);
    uint8_t freq = max(freq0, freq1);

    uint8_t reading = map(freq, 0, 255, 20, 255);
    return reading;
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

    uint8_t reading = map(freq, 0, 255, 20, 255);
    return reading;
}

uint8_t get_treble_reading() {
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_5, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_6, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq0);
    uint8_t freq = max(freq0, freq1);

    uint8_t reading = map(freq, 0, 255, 20, 255);
    return reading;
}

uint8_t get_breakpoint() {
    uint8_t bass = get_bass_reading();
    uint8_t mid = get_mid_reading();
    uint8_t treble = get_treble_reading();

    uint8_t sum = bass + mid + treble;
    uint8_t break_point = (sum / 3);

    if(bass > break_point) return 255;
    return 0;
}

uint8_t linear_scale(uint8_t input_value) {
    const uint8_t input_min = 50;
    const uint8_t input_max = 250;
    
    const uint8_t output_min = 0;
    const uint8_t output_max = 255;

    double scaled_value = ((input_value - input_min) / static_cast<double>(input_max - input_min)) * (output_max - output_min) + output_min;

    if (scaled_value < output_min) {
        scaled_value = output_min;
    }

    return static_cast<int>(scaled_value);
}

uint8_t exponential_scale(uint8_t input_value) {
    double scaling_factor = 2.0;

    double normalized_value = static_cast<double>(input_value) / 255.0;
    double scaled_value = pow(255.0, normalized_value * scaling_factor) - 1.0;
    return static_cast<int>(scaled_value);
}

void music_volume(){ 
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!newReading) return;

    uint8_t volume = MSGEQ7.getVolume();
    FastLED.setBrightness(volume);
}

void music_lines() {
    #define NUMBEROFLINES 14 // number of LED lines on strip at one time
    #define LINELENGTH 3 // length of each LED line
    #define EIGHTBIT 255
    #define NUM_CHANNELS 7
    #define HUESPEED 5 // how fast the hue increments for each LED movement
    #define LEDSPEED 0 // how fast the LED lines move in ms - effects MSGEQ7 reads

    int hues[NUMBEROFLINES] = {0,18,36,54,72,91,109,127,145,163,182,200,281,236};
    int positions[NUMBEROFLINES] = {0,7,14,21,28,35,42,49,56,63,70,77,84,90};
    int values[NUMBEROFLINES];

    for(int i=0; i < NUM_CHANNELS; i++){
        values[i] = MSGEQ7.get(i, 0);
    }

    // for each led line
    for (unsigned int k = 0; k < NUM_LEDS; k++) {

	    // for each led in the led line add color
	    for(int i = 0; i < LINELENGTH; i++){
	        if ( positions[k] + i < NUM_LEDS) {
	        	leds[positions[k] + i] = CHSV(hues[k], 255, values[k]);
	        }
	    }

	    // once all colors of that line are added show line
	    FastLED.show();

	    // turn off last LED, increment position
	    leds[positions[k]] = CRGB::Black;
	    positions[k]++;

	    // increment hue and check of hue max
	    hues[k] += HUESPEED;
	    if (hues[k] > EIGHTBIT) {
	    	hues[k] = 0;
	    }

	    // check for line position at end of strip
	    if (positions[k] > NUM_LEDS + LINELENGTH - 2) {
	        // if at end of strip reset position
	        positions[k] = 0;
	    }

	}

	// delay until next led change
	delay(LEDSPEED);
}

void music_average(){ 
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if(!newReading) return;

    uint8_t freq0 = MSGEQ7.get(MSGEQ7_0, 0);
    freq0 = mapNoise(freq0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);
    freq1 = mapNoise(freq1);
    uint8_t freq2 = MSGEQ7.get(MSGEQ7_2, 0);
    freq2 = mapNoise(freq2);
    uint8_t freq3 = MSGEQ7.get(MSGEQ7_3, 0);
    freq3 = mapNoise(freq3);
    uint8_t freq4 = MSGEQ7.get(MSGEQ7_4, 0);
    freq4 = mapNoise(freq4);
    uint8_t freq5 = MSGEQ7.get(MSGEQ7_5, 0);
    freq5 = mapNoise(freq5);
    uint8_t freq6 = MSGEQ7.get(MSGEQ7_6, 0);
    freq6 = mapNoise(freq6);

    uint8_t average = (freq0 + freq1 + freq2 + freq3 + freq4 + freq5 + freq6) / 7;
    FastLED.setBrightness(average);
}

void music_bpm(){
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = get_bass_reading();
        FastLED.setBrightness(freq);
        bpm();
    }
}

void music_rainbow() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = get_bass_reading();
        FastLED.setBrightness(freq);
        rainbow();
    }
}

void music_party_color() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = get_bass_reading();
        FastLED.setBrightness(freq);
        party_colors();
    }
}

void music_rgb() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);
        uint8_t freq3 = MSGEQ7.get(MSGEQ7_3, 0);
        uint8_t freq5 = MSGEQ7.get(MSGEQ7_5, 0);

        freq1 = mapNoise(freq1);
        freq3 = mapNoise(freq3);
        freq5 = mapNoise(freq5);

        fill_solid(leds, NUM_LEDS, CRGB(freq1, freq3, freq5));
        fadeToBlackBy(leds, NUM_LEDS, 10);
    }
}

void music_rotate_party_colors() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = get_bass_reading();
        rotate_party_colors();
        FastLED.setBrightness(freq);
    }
}
