extern uint8_t mode;
extern uint8_t color;
extern int16_t bright;
extern uint8_t state;

void irreceive(uint32_t command) {
  switch (command) {
      // case 0xBA45FF00: break; // IR_KEY_ONE
      // case 0xB946FF00: break; // IR_KEY_TWO
      // case 0xB847FF00: break; // IR_KEY_THREE
      // case 0xBB44FF00: break; // IR_KEY_FOUR
      // case 0xBF40FF00: break; // IR_KEY_FIVE
      // case 0xBC43FF00: break; // IR_KEY_SIX
      // case 0xF807FF00: break; // IR_KEY_SEVEN
      // case 0xEA15FF00: break; // IR_KEY_EIGHT
      // case 0xF609FF00: break; // IR_KEY_NINE
      // case 0xE619FF00: break; // IR_KEY_ZERO


    case 0xE916FF00:  // IR_KEY_STAR
      if (state != STATE_SHOW_COLOR)
        state = STATE_SHOW_COLOR;
      else color += STRIDE_COLOR;
      break;

    case 0xF20DFF00:  // IR_KEY_GRILLE
      if (state != STATE_SHOW_COLOR)
        state = STATE_SHOW_COLOR;
      else color -= STRIDE_COLOR;
      break;

    case 0xE718FF00:  // IR_KEY_UP
      bright += STRIDE_BRIGHT;
      if (bright > MAX_BRIGHT)
        bright = MAX_BRIGHT;
      break;

    case 0xF708FF00:  // IR_KEY_LEFT
      if (state != STATE_PLAY_MODE)
        state = STATE_PLAY_MODE;
      else if (mode > 0) mode--;
      else mode = MAX_MODE;
      break;

    case 0xE31CFF00:  // IR_KEY_OK
      if (state != STATE_PLAY_MODE)
        state = STATE_PLAY_MODE;
      else state = STATE_NOT_WORK;
      break;

    case 0xA55AFF00:  // IR_KEY_RIGHT
      if (state != STATE_PLAY_MODE)
        state = STATE_PLAY_MODE;
      else if (mode == MAX_MODE)
        mode = 0; else mode++;
      break;

    case 0xAD52FF00:  // IR_KEY_DOWN
      bright -= STRIDE_BRIGHT;
      if (bright < MIN_BRIGHT)
        bright = MIN_BRIGHT;
      break;
  }
}
