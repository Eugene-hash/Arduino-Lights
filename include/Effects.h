#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>
#include <FastLED.h>

typedef void (*SimpleMode)();

class Effects {
  private:
    static CRGBPalette16 currentPalette;
    static const uint8_t *currentPalettePtr;
    static uint8_t wave1, wave2, wave3;

    static void plasma(const uint8_t *palette);

  public:
    static const SimpleMode list[];
    static const uint8_t count;

    Effects() = delete;

    static void rainbow();
    static void deepCosmos();
    static void arcticIce();
    static void cyberMagenta();
    static void electricJungle();
    static void midnightCrystal();
    static void twilightMist();
    static void retrowaveDream();
    static void voodooMagic();
    static void confetti();
};

#endif