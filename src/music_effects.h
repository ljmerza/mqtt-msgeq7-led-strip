#ifndef MUSIC_EFFECTS_GUARD 
#define MUSIC_EFFECTS_GUARD

#include "effects.h"
#include "config.h"

uint8_t getBassReading();
uint8_t getMidsReading();
uint8_t getTrebleReading();

uint8_t _mapFrequencies(int freqArg0, int freqArg1);

void musicThreeFreq();

void musicRainbow();
void musicPartyColor();
void musicRGB();
void musicRotatePartyColors();

#endif