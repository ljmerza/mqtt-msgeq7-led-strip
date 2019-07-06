
#ifndef CALLBACK_GUARD 
#define CALLBACK_GUARD

#include "Common.h"
#include <Arduino.h>

void callback(char* topic, byte* payload, unsigned int length);
void runEffect();
bool processJson(char* message);
void setRealColors();


#endif
