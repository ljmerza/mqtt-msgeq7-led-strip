#ifndef LIGHT_EFFECTS_GUARD 
#define LIGHT_EFFECTS_GUARD

void lamp_candle();
void lamp_tungsten_40w();
void lamp_tungsten_100w();
void lamp_high_pressure_sodium();

void fill_led_colors(CRGBPalette16 current_palette);

void cloud_colors_p();
void ocean_colors_p();
void forest_colors_p();
void lava_colors_p();
void rainbow_stripe_colors();
void party_colors_p();
void heatColors_p ();


CRGBPalette16 lamp_light(uint8_t red, uint8_t green, uint8_t blue);

#endif