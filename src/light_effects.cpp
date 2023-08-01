#include "common.h"
#include "config.h"

void fill_led_colors(CRGBPalette16 current_palette){ 
    for(int i=0; i<NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(current_palette, 0, brightness, LINEARBLEND);
    } 
}

CRGBPalette16 lamp_light(uint8_t red, uint8_t green, uint8_t blue){
    CRGB rgb = CRGB(red, green, blue);

    CRGBPalette16 current_palette = CRGBPalette16(
        rgb, rgb, rgb, rgb,
        rgb, rgb, rgb, rgb,
        rgb, rgb, rgb, rgb,
        rgb, rgb, rgb, rgb
    );

    return current_palette;
}

void lamp_candle(){
    CRGBPalette16 current_palette = lamp_light(255, 147, 41);
    fill_led_colors(current_palette);
}

void lamp_tungsten_40w(){
    CRGBPalette16 current_palette = lamp_light(255, 197, 143);
    fill_led_colors(current_palette);
}

void lamp_tungsten_100w(){
    CRGBPalette16 current_palette = lamp_light(255, 214, 170);
    fill_led_colors(current_palette);
}

void lamp_high_pressure_sodium() {
    CRGBPalette16 current_palette = lamp_light(255, 183, 76);
    fill_led_colors(current_palette);
}

void cloud_colors_p() {
    CRGBPalette16 current_palette = CloudColors_p;
    fill_led_colors(current_palette);
}

void ocean_colors_p() {
    CRGBPalette16 current_palette = OceanColors_p;
    fill_led_colors(current_palette);
}

void forest_colors_p() {
    CRGBPalette16 current_palette = ForestColors_p;
    fill_led_colors(current_palette);
}

void lava_colors_p() {
    CRGBPalette16 current_palette = LavaColors_p;
    fill_led_colors(current_palette);
}

void rainbow_stripe_colors() {
    CRGBPalette16 current_palette = RainbowStripeColors_p;
    fill_led_colors(current_palette);
}

void party_colors_p() {
    CRGBPalette16 current_palette = PartyColors_p;
    fill_led_colors(current_palette);
}

void heatColors_p() {
    CRGBPalette16 current_palette = HeatColors_p;
    fill_led_colors(current_palette);
}