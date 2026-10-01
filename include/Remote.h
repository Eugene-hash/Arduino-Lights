#ifndef REMOTE_H
#define REMOTE_H

#include <Arduino.h>

class Remote {
  private:
    static uint32_t firstPress;
    static uint32_t lastAction;
    static uint8_t holdActive;

    static void execute(uint8_t command);

  public:
    Remote() = delete;

    static void begin();

    static bool isIdle();

    static void handle();
};

#endif