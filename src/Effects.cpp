#include <Arduino.h>
#include <FastLED.h>

#include "Config.h"
#include "Effects.h"
#include "Palettes.h"

extern CRGB leds[];

CRGBPalette16 Effects::currentPalette;
const uint8_t *Effects::currentPalettePtr = nullptr;

uint8_t Effects::wave1 = 0;
uint8_t Effects::wave2 = 0;
uint8_t Effects::wave3 = 0;

const uint8_t Effects::count = 10;

const SimpleMode Effects::list[] = {
    &Effects::rainbow,
    &Effects::deepCosmos,
    &Effects::arcticIce,
    &Effects::cyberMagenta,
    &Effects::electricJungle,
    &Effects::midnightCrystal,
    &Effects::twilightMist,
    &Effects::retrowaveDream,
    &Effects::voodooMagic,
    &Effects::confetti
};

void Effects::plasma(const uint8_t *palette) {
    if (currentPalettePtr != palette) {
        currentPalette = palette;
        currentPalettePtr = palette;
    }

    wave1 += static_cast<int8_t>(beatsin8(10, 0, 8)) - 4;
    wave2 += static_cast<int8_t>(beatsin8(15, 0, 4)) - 2;
    wave3 += static_cast<int8_t>(beatsin8(12, 0, 6)) - 3;

    for (uint8_t i = 0; i < COUNT_LED; i++) {
        uint8_t sin1 = sin8(5 * i + wave1);
        uint8_t sin2 = sin8(8 * i + wave2);
        uint8_t sin3 = sin8(7 * i + wave3);
        uint8_t temp = sin1 + sin2 + sin3;

        leds[i] = ColorFromPalette(currentPalette, temp);
    }
}

void Effects::rainbow() {
    const uint8_t beatA = beatsin8(17, 0, 255);
    const uint8_t beatB = beatsin8(13, 0, 255);
    const uint8_t startHue = (beatA + beatB) >> 1;

    fill_rainbow(leds, COUNT_LED, startHue, 8);
}

void Effects::deepCosmos() { plasma(DeepCosmos_gp); }

void Effects::arcticIce() { plasma(ArcticIce_gp); }

void Effects::cyberMagenta() { plasma(CyberMagenta_gp); }

void Effects::electricJungle() { plasma(ElectricJungle_gp); }

void Effects::midnightCrystal() { plasma(MidnightCrystal_gp); }

void Effects::twilightMist() { plasma(TwilightMist_gp); }

void Effects::retrowaveDream() { plasma(RetrowaveDream_gp); }

void Effects::voodooMagic() { plasma(VoodooMagic_gp); }

void Effects::confetti() {
    const uint8_t hue = random8();
    const uint8_t pos = random8(COUNT_LED);

    fadeToBlackBy(leds, COUNT_LED, 10);
    leds[pos] += CHSV(hue, 200, 255);
}