#include "config.h"
#include "common.h"
#include "music_effects.h"

uint8_t getBassReading() {
    return _mapFrequencies(MSGEQ7_0, MSGEQ7_1);
}

uint8_t getMidsReading() {
    return _mapFrequencies(MSGEQ7_2, MSGEQ7_3);
}

uint8_t getTrebleReading() {
    return _mapFrequencies(MSGEQ7_5, MSGEQ7_6);
}

uint8_t _mapFrequencies(int freqArg0, int freqArg1){
    uint8_t freq0 = MSGEQ7.get(freqArg0, 0);
    uint8_t freq1 = MSGEQ7.get(freqArg1, 0);

    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq1);

    // Use whichever frequency is being used more
    freq0 = max(freq0, freq1);

    // Map the values so there is always at least 20 brightness
    freq0 = map(freq0, 0, 255, 20, 255);

    return freq0;
}

void musicThreeFreq(){
    // uint8_t bass = getBassReading();
    // uint8_t mids = getMidsReading();
    // uint8_t treble = getTrebleReading();

    // uint8_t freqGroup = 0;
    // for(uint8_t i=0; i<NUM_LEDS;) {

    //     uint8_t value = bass;
    //     if(freqGroup == 1){
    //         value = mids;
    //     } else if(freqGroup == 2){
    //         value = treble;
    //     }

    //     if(NUM_LEDS >= i){
    //         leds[i].setHSV(50, 50, value);
    //     }
    //     if(NUM_LEDS > i+1){
    //         leds[i+1] %= value;
    //     }
    //     if(NUM_LEDS > i+2){
    //         leds[i+2].fadeLightBy(value);
    //     }

    //     freqGroup++;
    //     if(freqGroup == 3){
    //         freqGroup = 0;
    //     }

    //     i = i+3;
    // }

    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = getBassReading();
        FastLED.setBrightness(freq);
        bpm();
    }
}

void musicRainbow() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = getBassReading();
        FastLED.setBrightness(freq);
        rainbow();
    }
}

void musicPartyColor() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = getBassReading();
        FastLED.setBrightness(freq);
        partyColors();
    }
}

void musicRGB() {
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

void musicRotatePartyColors() {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

    if (newReading) {
        uint8_t freq = getBassReading();
        rotatePartyColors();
        FastLED.setBrightness(freq);
    }
}
