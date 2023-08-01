# MQTT RGB Light Strips

A WiFi Connected RGB LED Strip using MQTT.

## Hardware

- MSGEQ7 Audio Spectrum Analyzer
- ESP8266 (can change the config to use any ESP32 but make sure tha change ESP8266WiFi to WiFi library)
- WS2811 LED strips (can change the config to use any LED strip)

Check out the `schematic/` folder for more information.

## Software

This repository uses [PlatformIO](https://platformio.org/) for building the embedded software.
To get started copy the `src/config.example.h` file to `src/config.h`.
Afterwards update the MQTT topics, WiFi information and LED strip information to match your setup.

## Home Assistant

Copy the yaml in the `/homeassistant/mqtt.yaml` file.
