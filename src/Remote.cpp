#define DECODE_NEC

#include <Arduino.h>
#include <IRremote.hpp>

#include "Config.h"
#include "Brightness.h"
#include "Controller.h"
#include "Keycodes.h"
#include "Remote.h"

uint32_t Remote::firstPress = 0;
uint32_t Remote::lastAction = 0;
uint8_t Remote::holdActive = false;

void Remote::begin() { IrReceiver.begin(IRREMOTE_PIN); }

bool Remote::isIdle() { return IrReceiver.isIdle(); }

void Remote::handle() {
    if (IrReceiver.decode()) {
        uint8_t command = IrReceiver.decodedIRData.command;
        uint8_t flags = IrReceiver.decodedIRData.flags;
        uint32_t now = millis();

        bool isRepeat = (flags & IRDATA_FLAGS_IS_REPEAT);
        bool isHoldable = command == IR_KEY_UP || command == IR_KEY_DOWN ||
                          command == IR_KEY_STAR || command == IR_KEY_HASH;

        if (!isRepeat) {
            firstPress = now;
            lastAction = now;
            holdActive = false;

            execute(command);
        } else {
            if (isHoldable) {
                if (!holdActive) {
                    if (now - firstPress >= HOLD_TIMEOUT) {
                        holdActive = true;
                        lastAction = now;
                        execute(command);
                    }
                } else {
                    if (now - lastAction >= HOLD_INTERVAL) {
                        lastAction = now;
                        execute(command);
                    }
                }
            }
        }

        IrReceiver.resume();
    }
}

void Remote::execute(uint8_t command) {
    switch (command) {
    case IR_KEY_ONE:
        Controller::setEffect(0);
        break;

    case IR_KEY_TWO:
        Controller::setEffect(1);
        break;

    case IR_KEY_THREE:
        Controller::setEffect(2);
        break;

    case IR_KEY_FOUR:
        Controller::setEffect(3);
        break;

    case IR_KEY_FIVE:
        Controller::setEffect(4);
        break;

    case IR_KEY_SIX:
        Controller::setEffect(5);
        break;

    case IR_KEY_SEVEN:
        Controller::setEffect(6);
        break;

    case IR_KEY_EIGHT:
        Controller::setEffect(7);
        break;

    case IR_KEY_NINE:
        Controller::setEffect(8);
        break;

    case IR_KEY_ZERO:
        Controller::toggleSolid();
        break;

    case IR_KEY_STAR:
        Controller::increaseColor();
        break;

    case IR_KEY_HASH:
        Controller::decreaseColor();
        break;

    case IR_KEY_UP:
        Brightness::increase();
        Controller::enablePower();
        break;

    case IR_KEY_DOWN:
        Brightness::decrease();
        Controller::enablePower();
        break;

    case IR_KEY_OK:
        Controller::togglePower();
        break;

    case IR_KEY_RIGHT:
        Controller::nextEffect();
        break;

    case IR_KEY_LEFT:
        Controller::prevEffect();
        break;
    }
}