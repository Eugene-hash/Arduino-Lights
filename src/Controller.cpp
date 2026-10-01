#include <Arduino.h>
#include <FastLED.h>

#include "Config.h"
#include "Controller.h"
#include "Effects.h"

extern CRGB leds[];

uint8_t Controller::power = DEFAULT_POWER;
uint8_t Controller::currentEffect = DEFAULT_EFFECT;
uint8_t Controller::isSolidColor = DEFAULT_SOLID;
uint8_t Controller::color = DEFAULT_COLOR;

void Controller::togglePower() {
    if (power) disablePower();
    else enablePower();
}

void Controller::enablePower() {
    power = true;
}

void Controller::disablePower() {
    FastLED.clear(true);
    power = false;
}

void Controller::setEffect(uint8_t effect) {
    if (isSolidColor) disableSolid();
    if (effect >= Effects::count) return;
    currentEffect = effect;
}

void Controller::nextEffect() {
    if (isSolidColor) return disableSolid();
    
    uint8_t next = currentEffect + 1;
    if (next == Effects::count) next = 0;
    setEffect(next);
}

void Controller::prevEffect() {
    if (isSolidColor) return disableSolid();

    int16_t prev = currentEffect - 1;
    if (prev < 0) prev = Effects::count - 1;
    setEffect(prev);
}

void Controller::toggleSolid() {
    if (isSolidColor) return disableSolid();
    else enableSolid();
}

void Controller::enableSolid() { isSolidColor = true; }

void Controller::disableSolid() { isSolidColor = false; }

void Controller::increaseColor() {
    if (!isSolidColor) return enableSolid();
    color += DELTA_COLOR;
}

void Controller::decreaseColor() {
    if (!isSolidColor) return enableSolid();
    color -= DELTA_COLOR;
}

void Controller::solidColor() {
    CHSV temp = CHSV(color, 255, 255);
    fill_solid(leds, COUNT_LED, temp);
}

void Controller::tick() {
    if (!power) return;

    if (isSolidColor) solidColor();
    else Effects::list[currentEffect]();

    FastLED.show();
}