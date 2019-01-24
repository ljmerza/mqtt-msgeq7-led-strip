#include "config.h"
#include "common.h"
#include "music_effects.h"

uint8_t getBassReading() {
    // Get values for lowest frequencies
    uint8_t freq0 = MSGEQ7.get(MSGEQ7_0, 0);
    uint8_t freq1 = MSGEQ7.get(MSGEQ7_1, 0);
    freq0 = mapNoise(freq0);
    freq1 = mapNoise(freq0);

    // Use whichever frequency is being used more
    freq0 = max(freq0, freq1);

    // Map the values so there is always at least 20 brightness
    freq0 = map(freq0, 0, 255, 20, 255);

    return freq0;
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
