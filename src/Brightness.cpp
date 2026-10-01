#include <Arduino.h>
#include <FastLED.h>

#include "Config.h"
#include "Brightness.h"

const uint8_t CRT[] PROGMEM = {
    5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
    5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
    5,   5,   5,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,
    6,   6,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  10,  11,  11,  11,  11,
    11,  12,  12,  12,  12,  13,  13,  13,  13,  13,  14,  14,  14,  14,  15,  15,  15,  16,  16,
    16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,  20,  20,  21,  21,  22,  22,  22,
    23,  23,  24,  24,  24,  25,  25,  26,  26,  27,  27,  28,  28,  28,  29,  29,  30,  30,  31,
    31,  32,  33,  33,  34,  34,  35,  35,  36,  36,  37,  38,  38,  39,  39,  40,  41,  41,  42,
    43,  43,  44,  45,  45,  46,  47,  48,  48,  49,  50,  50,  51,  52,  53,  54,  54,  55,  56,
    57,  58,  58,  59,  60,  61,  62,  63,  64,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,
    74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  89,  90,  91,  92,  93,
    94,  96,  97,  98,  99,  100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117,
    119, 120, 121, 123, 124, 126, 127, 129, 130
};

int16_t Brightness::level = DEFAULT_BRIGHT;

void Brightness::apply() {
    const uint8_t *ptr = &CRT[level];
    uint8_t bright = pgm_read_byte(ptr);
    FastLED.setBrightness(bright);
}

void Brightness::setDefault() {
    level = DEFAULT_BRIGHT;
    apply();
}

void Brightness::increase() {
    level += DELTA_BRIGHT;
    if (level > MAXIMUM_BRIGHT) {
        level = MAXIMUM_BRIGHT;
    }
    apply();
}

void Brightness::decrease() {
    level -= DELTA_BRIGHT;
    if (level < MINIMUM_BRIGHT) {
        level = MINIMUM_BRIGHT;
    }
    apply();
}