#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

class Controller {
private:
    static uint8_t power;
    static uint8_t currentEffect;
    static uint8_t isSolidColor;
    static uint8_t color;

    static void solidColor();

public:
    Controller() = delete;

    static void togglePower();
    static void enablePower();
    static void disablePower();

    static void setEffect(uint8_t effect);
    static void nextEffect();
    static void prevEffect();

    static void toggleSolid();
    static void enableSolid();
    static void disableSolid();
    static void increaseColor();
    static void decreaseColor();

    static void tick();
};

#endif