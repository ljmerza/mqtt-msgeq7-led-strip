
#ifndef WIFI_COMMON_GUARD 
#define WIFI_COMMON_GUARD

#include "common.h"

void reconnect_mqtt();
void setup_ota();
void setup_wifi();
void send_state();

#endif