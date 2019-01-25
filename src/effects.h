#ifndef EFFECTS_GUARD 
#define EFFECTS_GUARD

#include "common.h"

void partyColors();
void rainbow();

void addGlitter(fract8 chanceOfGlitter);
void rainbowWithGlitter();
void confetti();
void sinelon();
void bpm();


void juggle();
void rotatePartyColors();
void fire();
void setColor(int inR, int inG, int inB);
int temp2rgb(unsigned int kelvin);
void fadeall();

void lightning();
void ripple();
void dots();

extern uint8_t maxChanges;
extern CRGBPalette16 targetPalette;
extern CRGBPalette16 currentPalette;
void noise();


void twinkle();

int antipodal_index(int i);
void police_all();
void police_one();
void cyclon_rainbow();

void reset_strip();

#endif