#include <Arduino.h>
#include <FastLED.h>

#include "Config.h"
#include "Brightness.h"
#include "Controller.h"
#include "Remote.h"

CRGB leds[COUNT_LED];

void setup() {
    FastLED.addLeds<NEOPIXEL, WS2812B_PIN>(leds, COUNT_LED).setCorrection(TypicalLEDStrip);

    Brightness::setDefault();

    Remote::begin();
}

void loop() {
    Remote::handle();

    EVERY_N_MILLIS(33) {
        if (!Remote::isIdle()) return;
        Controller::tick();
    }
}