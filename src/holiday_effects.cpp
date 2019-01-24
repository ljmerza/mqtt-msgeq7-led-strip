#include "common.h"

// ST PATTY
DEFINE_GRADIENT_PALETTE( bhw2_greenman_gp ) {
    0,   1, 22,  1,
  130,   1,168,  2,
  255,   1, 22,  1
};

void st_patty(){
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = bhw2_greenman_gp;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

// CHRISTMAS
DEFINE_GRADIENT_PALETTE( bhw2_xmas_gp ) {
    0,   0, 12,  0,
   40,   0, 55,  0,
   66,   1,117,  2,
   77,   1, 84,  1,
   81,   0, 55,  0,
  119,   0, 12,  0,
  153,  42,  0,  0,
  181, 121,  0,  0,
  204, 255, 12,  8,
  224, 121,  0,  0,
  244,  42,  0,  0,
  255,  42,  0,  0
};

void christmas() {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = bhw2_xmas_gp;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

void candyCane() {
    static uint8_t startIndex = 0;

    const CRGBPalette16 currentPalettestriped = CRGBPalette16(
        CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
        CRGB::Red, CRGB::Red, CRGB::White, CRGB::White, CRGB::White,
        CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White
    );

    startIndex = startIndex + 1;
    fill_palette(leds, NUM_LEDS, startIndex, 16, currentPalettestriped, 255, LINEARBLEND);
}

// HALLOWEEN
DEFINE_GRADIENT_PALETTE( Orange_to_Purple_gp ) {
    0, 208, 50,  1,
  127, 146, 27, 45,
  255,  97, 12,178
};

void halloween() {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = Orange_to_Purple_gp;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

// PUMPKIN
CRGBPalette16 HalloweenPalettestriped = CRGBPalette16(
    CRGB::DarkOrange, CRGB::DarkOrange, CRGB::DarkOrange, CRGB::DarkOrange, CRGB::DarkOrange, 
    CRGB::DarkOrange, CRGB::DarkOrange, CRGB::DarkOrange, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, 
     CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo
);

void pumpkin() {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* higher = faster motion */

    fill_palette(
        leds, 
        NUM_LEDS,
        startIndex, 16, /* higher = narrower stripes */
        HalloweenPalettestriped, 255, LINEARBLEND
    );
}

// USA
DEFINE_GRADIENT_PALETTE( bhw3_41_gp ) {
    0,   0,  0, 45,
   71,   7, 12,255,
   76,  75, 91,255,
   76, 255,255,255,
   81, 255,255,255,
  178, 255,255,255,
  179, 255, 55, 45,
  196, 255,  0,  0,
  255,  42,  0,  0
};

void usa() {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = bhw3_41_gp;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

DEFINE_GRADIENT_PALETTE( bhw2_redrosey_gp ) {
    0, 103,  1, 10,
   33, 109,  1, 12,
   76, 159,  5, 48,
  119, 175, 55,103,
  127, 175, 55,103,
  178, 159,  5, 48,
  221, 109,  1, 12,
  255, 103,  1, 10
};

void valentine() {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = bhw2_redrosey_gp;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    }
}

// THANKSGIVING
CRGBPalette16 ThxPalettestriped = CRGBPalette16(
    CRGB::OrangeRed, CRGB::OrangeRed, CRGB::OrangeRed, CRGB::OrangeRed, CRGB::OrangeRed, 
    CRGB::OrangeRed, CRGB::OrangeRed, CRGB::Olive, CRGB::Olive, CRGB::Olive, CRGB::Maroon, 
    CRGB::Maroon, CRGB::Maroon, CRGB::Maroon, CRGB::Maroon, CRGB::Maroon
);

void thanksgiving() {
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* higher = faster motion */

     fill_palette( 
        leds, NUM_LEDS,
        startIndex, 16, /* higher = narrower stripes */
        ThxPalettestriped, 255, LINEARBLEND
    );
}