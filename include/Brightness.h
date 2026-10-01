#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <Arduino.h>

class Brightness {
  private:
    static int16_t level;
    
    static void apply();

  public:
    Brightness() = delete;

    static void setDefault();

    static void increase();

    static void decrease();
};

#endif