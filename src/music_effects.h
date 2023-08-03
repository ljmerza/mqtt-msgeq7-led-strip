#ifndef MUSIC_EFFECTS_GUARD 
#define MUSIC_EFFECTS_GUARD

#include "effects.h"
#include "config.h"

uint8_t get_bass_reading();
uint8_t get_mid_reading();
uint8_t get_treble_reading();
uint8_t linear_scale(uint8_t input_value);

void set_freq_to_brightness();

void music_lines();
void music_seven_channels();
void music_bpm();
void music_rainbow();
void music_party_colors();
void music_rgb();
void music_rotate_party_colors();

#endif