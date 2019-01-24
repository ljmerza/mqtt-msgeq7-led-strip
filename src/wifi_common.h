
#ifndef WIFI_COMMON_GUARD 
#define WIFI_COMMON_GUARD

#include "common.h"

void reconnect_mqtt();
void setupOTA();
void setup_wifi();
void sendState();

#endif