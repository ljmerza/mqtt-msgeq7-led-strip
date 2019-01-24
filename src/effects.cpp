#include "common.h"



void partyColors() {
    static uint8_t startIndex = 0;

    startIndex = startIndex + 1;
    fill_palette(leds, NUM_LEDS, startIndex, 16, PartyColors_p, 255, LINEARBLEND);
}

void rainbow() {
    // FastLED's built-in rainbow generator
    fill_rainbow(leds, NUM_LEDS, gHue, 10);
}

void addGlitter(fract8 chanceOfGlitter) {
    if (random8() < chanceOfGlitter) {
        leds[random16(NUM_LEDS)] += CRGB::White;
    }
}

void rainbowWithGlitter() {
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addGlitter(80);
}

void confetti() {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CRGB(realRed + random8(64), realGreen, realBlue);
}

void sinelon() {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(13, 0, NUM_LEDS - 1);
    leds[pos] += CRGB(realRed, realGreen, realBlue);
}

void bpm() {
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);

    for (int i = 0; i < NUM_LEDS; i++) { // 9948
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, NUM_LEDS, 20);

    for (int i = 0; i < 8; i++) {
        leds[beatsin16(i + 7, 0, NUM_LEDS - 1  )] |= CRGB(realRed, realGreen, realBlue);
    }
}

void rotatePartyColors() {
    static uint8_t colorIndex = 0;
    static uint8_t delay = 0;

    fill_solid(&(leds[0]), NUM_LEDS, ColorFromPalette(PartyColors_p, colorIndex, 200));

    if (delay == 8) {
        colorIndex++;
        delay = 0;

    } else {
        delay++;
    }
}

void fire() {

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette(HeatColors_p, colorindex);
    int pixelnumber;

    pixelnumber = j;
    leds[pixelnumber] = color;
  }
}

void setColor(int inR, int inG, int inB) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].red = inR;
    leds[i].green = inG;
    leds[i].blue = inB;
  }
}

// LIGHTNING EFFECT
uint8_t frequency = 50; // controls the interval between strikes
uint8_t flashes = 8; //the upper limit of flashes per strike
unsigned int dimmer = 1;
uint8_t ledstart; // Starting location of a flash
uint8_t ledlen;
int lightningcounter = 0;

void lightning(){

    ledstart = random8(NUM_LEDS); // Determine starting location of flash
    ledlen = random8(NUM_LEDS - ledstart); // Determine length of flash (not to go beyond NUM_LEDS-1)

    for (int flashCounter = 0; flashCounter < random8(3, flashes); flashCounter++) {
        if (flashCounter == 0) dimmer = 5; // the brightness of the leader is scaled down by a factor of 5
        else dimmer = random8(1, 3); // return strokes are brighter than the leader

        fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 255 / dimmer));
        runLedLights();   

         // Show a section of LED's
        delay(random8(4, 10));                // each flash only lasts 4-10 milliseconds
        fill_solid(leds + ledstart, ledlen, CHSV(255, 0, 0)); // Clear the section of LED's

        runLedLights();
        if (flashCounter == 0) delay (130);   // longer delay until next flash after the leader
        delay(50 + random8(100));             // shorter delay between strokes
    }

    delay(random8(frequency) * 100);        // delay between strikes
    runLedLights();
}

void temp2rgb(unsigned int kelvin) {
    int tmp_internal = kelvin / 100.0;
    
    // red 
    if (tmp_internal <= 66) {
        Red = 255;
    } else {
        float tmp_red = 329.698727446 * pow(tmp_internal - 60, -0.1332047592);
        if (tmp_red < 0) {
            Red = 0;
        } else if (tmp_red > 255) {
            Red = 255;
        } else {
            Red = tmp_red;
        }
    }
    
    // green
    if (tmp_internal <=66){
        float tmp_green = 99.4708025861 * log(tmp_internal) - 161.1195681661;
        if (tmp_green < 0) {
            Green = 0;
        } else if (tmp_green > 255) {
            Green = 255;
        } else {
            Green = tmp_green;
        }
    } else {
        float tmp_green = 288.1221695283 * pow(tmp_internal - 60, -0.0755148492);
        if (tmp_green < 0) {
            Green = 0;
        } else if (tmp_green > 255) {
            Green = 255;
        } else {
            Green = tmp_green;
        }
    }
    
    // blue
    if (tmp_internal >=66) {
        Blue = 255;
    } else if (tmp_internal <= 19) {
        Blue = 0;
    } else {
        float tmp_blue = 138.5177312231 * log(tmp_internal - 10) - 305.0447927307;
        if (tmp_blue < 0) {
            Blue = 0;
        } else if (tmp_blue > 255) {
            Blue = 255;
        } else {
            Blue = tmp_blue;
        }
    }
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);  //for CYCLon
  }
}

// RIPPLE EFFECT
uint8_t colour; // Ripple colour is randomized.
int center = 0; // Center of the current ripple.
int step = -1; // -1 is the initializing step.
uint8_t myfade = 255; // Starting brightness.
#define maxsteps 16 // Case statement wouldn't allow a variable.
uint8_t bgcol = 0; // Background colour rotates.
int thisdelay = 20; // Standard delay value.

void ripple(){
     for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(bgcol++, 255, 15);  // Rotate background colour.

      switch (step) {
        case -1: // Initialize ripple variables.
          center = random(NUM_LEDS);
          colour = random8();
          step = 0;
          break;
        case 0:
          leds[center] = CHSV(colour, 255, 255); // Display the first pixel of the ripple.
          step ++;
          break;
        case maxsteps: // At the end of the ripples.
          step = -1;
          break;
        default: // Middle of the ripples.
          leds[(center + step + NUM_LEDS) % NUM_LEDS] += CHSV(colour, 255, myfade / step * 2); // Simple wrap from Marc Miller
          leds[(center - step + NUM_LEDS) % NUM_LEDS] += CHSV(colour, 255, myfade / step * 2);
          step ++; // Next step.
          break;
      }
}

// DOTS
uint8_t count = 0; // Count up to 255 and then reverts to 0
uint8_t fadeval = 224; // Trail behind the LED's. Lower => faster fade.
uint8_t dots_bpm = 30;

void dots(){
    uint8_t inner = beatsin8(dots_bpm, NUM_LEDS / 4, NUM_LEDS / 4 * 3);
    uint8_t outer = beatsin8(dots_bpm, 0, NUM_LEDS - 1);
    uint8_t middle = beatsin8(dots_bpm, NUM_LEDS / 3, NUM_LEDS / 3 * 2);

    leds[middle] = CRGB::Purple;
    leds[inner] = CRGB::Blue;
    leds[outer] = CRGB::Aqua;

    nscale8(leds, NUM_LEDS, fadeval);
}

//NOISE
static uint16_t dist; // A random number for our noise generator.
uint16_t scale = 30; // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint8_t maxChanges = 48; // Value for blending between palettes.
CRGBPalette16 targetPalette(OceanColors_p);
CRGBPalette16 currentPalette(CRGB::Black);

void noise() {
    for (int i = 0; i < NUM_LEDS; i++) { // Just onE loop to fill up the LED array as all of the pixels change.
        uint8_t index = inoise8(i * scale, dist + i * scale) % 255; // Get a value from the noise function. I'm using both x and y axis.
        leds[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND); // With that value, look up the 8 bit colour palette value and assign it to the current LED.
    }
    
    dist += beatsin8(10, 1, 4); // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
    runLedLights();
}

// TWINKLE
#define DENSITY 80
int twinklecounter = 0;

void twinkle() {
    const CRGB lightcolor(8, 7, 1);

    for ( int i = 0; i < NUM_LEDS; i++) {
        if ( !leds[i]) continue; // skip black pixels

        if ( leds[i].r & 1) { // is red odd?
            leds[i] -= lightcolor; // darken if red is odd
        } else {
            leds[i] += lightcolor; // brighten if red is even
        }
    }

    if ( random8() < DENSITY) {
        int j = random16(NUM_LEDS);
        if ( !leds[j] ) leds[j] = lightcolor;
    }
}

// POLICE
int police_index = 0;
int police_top_index = int(NUM_LEDS / 2);
int police_thissat = 255;
uint8_t thishuepolice = 0;

int antipodal_index(int i) {
    int iN = i + police_top_index;

    if (i >= police_top_index) {
        iN = ( i + police_top_index ) % NUM_LEDS;
    }

    return iN;
}

void police_all() {
    police_index++;

    if (police_index >= NUM_LEDS) {
      police_index = 0;
    }

    int idexR = police_index;
    int idexB = antipodal_index(idexR);
    int thathue = (thishuepolice + 160) % 255;
    leds[idexR] = CHSV(thishuepolice, police_thissat, 255);
    leds[idexB] = CHSV(thathue, police_thissat, 255);
}

void police_one() {
    police_index++;

    if (police_index >= NUM_LEDS) {
        police_index = 0;
    }

    int idexR = police_index;
    int idexB = antipodal_index(idexR);
    int thathue = (thishuepolice + 160) % 255;

    for (int i = 0; i < NUM_LEDS; i++ ) {
        if (i == idexR) {
            leds[i] = CHSV(thishuepolice, police_thissat, 255);

        } else if (i == idexB) {
            leds[i] = CHSV(thathue, police_thissat, 255);

        } else {
            leds[i] = CHSV(0, 0, 0);
        }
    }
}

void cyclon_rainbow() {
    static uint8_t hue = 0;

    // First slide the led in one direction
    for (int i = 0; i < NUM_LEDS; i++) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        runLedLights();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(10);
    }

    for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        runLedLights();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(10);
    }
}

void reset_strip() {
    FastLED.clear();
    FastLED.show();
}
