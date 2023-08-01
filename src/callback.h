
#ifndef CALLBACK_GUARD 
#define CALLBACK_GUARD

#include "Common.h"
#include <Arduino.h>
#include <ArduinoJson.h>

void callback(char* topic, byte* payload, unsigned int length);
bool run_effect();
void process_json(StaticJsonDocument<256>& json_doc);
void set_real_colors();


#endif
