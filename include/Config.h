#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

constexpr uint8_t IRREMOTE_PIN = 2;

constexpr uint8_t WS2812B_PIN = 6;
constexpr uint8_t COUNT_LED = 155;

constexpr uint8_t DEFAULT_POWER = true;

constexpr uint8_t DEFAULT_BRIGHT = 250;
constexpr uint8_t MAXIMUM_BRIGHT = 250;
constexpr uint8_t MINIMUM_BRIGHT = 40;
constexpr uint8_t DELTA_BRIGHT = 10;

constexpr uint8_t DEFAULT_EFFECT = 0;

constexpr uint8_t DEFAULT_SOLID = 0;
constexpr uint8_t DEFAULT_COLOR = 0;
constexpr uint8_t DELTA_COLOR = 5;

constexpr uint16_t HOLD_TIMEOUT = 500;
constexpr uint16_t HOLD_INTERVAL = 120;

#endif