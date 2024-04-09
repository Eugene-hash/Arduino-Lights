extern uint8_t mode;
extern uint8_t color;
extern int16_t bright;
extern uint8_t state;
extern CRGB leds[];

void show_color() {
  CHSV chsv = CHSV(color, 255, 255);
  fill_solid(leds, COUNT_LEDS, chsv);
}

int wave1, wave2, wave3;
void sin_pal(CRGBPalette16 palette) {
  wave1 += beatsin8(10, -4, 4);
  wave2 += beatsin8(15, -2, 2);
  wave3 += beatsin8(12, -3, 3);

  for (uint8_t i = 0; i < COUNT_LEDS; i++) {
    uint8_t sin1 = sin8(5 * i + wave1);
    uint8_t sin2 = sin8(8 * i + wave2);
    uint8_t sin3 = sin8(7 * i + wave3);
    uint8_t temp = sin1 + sin2 + sin3;
    leds[i] = ColorFromPalette(palette, temp);
  }
}

void beat_rainbow() {
  uint8_t beatA = beatsin8(17, 0, 255);
  uint8_t beatB = beatsin8(13, 0, 255);
  uint8_t sum = (beatA + beatB) >> 1;
  fill_rainbow(leds, COUNT_LEDS, sum, 8);
}