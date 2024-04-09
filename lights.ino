#include "FastLED.h"
#include "IRremote.h"

#define PIN_LEDS 6
#define COUNT_LEDS 96

#define PIN_RESEIVER_POWER 2
#define PIN_RESEIVER_INPUT 3

#define STATE_NOT_WORK 0
#define STATE_SHOW_COLOR 1
#define STATE_PLAY_MODE 2

#define DELAY 15
#define MAX_MODE 7
#define STRIDE_COLOR 8
#define STRIDE_BRIGHT 16
#define MAX_BRIGHT 255
#define MIN_BRIGHT 15

#define DEFAULT_BRIGHT 255
#define DEFAULT_COLOR 0
#define DEFAULT_MODE 0

#include "palettes.h"
#include "irreceive.h"
#include "modes.h"

CRGB leds[COUNT_LEDS];
uint32_t timer = millis();

uint8_t state = STATE_PLAY_MODE;
int16_t bright = DEFAULT_BRIGHT;
uint8_t color = DEFAULT_COLOR;
uint8_t mode = DEFAULT_MODE;

void setup() {
  FastLED.setBrightness(bright);
  FastLED.addLeds<NEOPIXEL, PIN_LEDS>(leds, COUNT_LEDS);

  pinMode(PIN_RESEIVER_POWER, OUTPUT);
  digitalWrite(PIN_RESEIVER_POWER, HIGH);
  IrReceiver.begin(PIN_RESEIVER_INPUT);
}

void loop() {
  if (IrReceiver.isIdle()) {
    if (millis() > timer) {
      timer = millis() + DELAY;

      switch (state) {
        case STATE_NOT_WORK:
          FastLED.clear(); break;

        case STATE_SHOW_COLOR:
          show_color(); break;

        case STATE_PLAY_MODE:
          if (mode != 0) {
            uint8_t palette = mode - 1;
            sin_pal(palettes[palette]);
          } else beat_rainbow();
      }

      FastLED.setBrightness(bright);
      FastLED.show();
    }
  }

  if (IrReceiver.decode()) {
    IRData IrData = IrReceiver.decodedIRData;
    irreceive(IrData.decodedRawData);
    IrReceiver.resume();
  }
}
