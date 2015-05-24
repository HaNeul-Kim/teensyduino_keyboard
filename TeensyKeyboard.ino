void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  Keyboard.begin();
}
const int FN1 = -1, FN2 = -2, FN3 = -3, MY_CAPS_LOCK = -11;
int capsState;// 0: not press, 1: caps lock press, 2: fn press
boolean fn1, fn2, fn3, caps;

int keymap[2][6][17] = {
  {
    {KEY_ESC, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINTSCREEN, KEY_SCROLL_LOCK, KEY_PAUSE},//  18
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP},// 19
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, KEY_DELETE, KEY_END, KEY_PAGE_DOWN},// 20
    {MY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_RETURN, 0, 0, 0, 0},//    21
    {KEY_LEFT_SHIFT, 0, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, 0, 0, KEY_UP, 0},//    22
    {FN1, KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, 0, KEY_SPACE, 0, 0, 0, KEY_RIGHT_GUI, FN2, FN3, 254, KEY_RIGHT_CTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT}//    23
  },
  {
    {KEY_ESC, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINTSCREEN, KEY_SCROLL_LOCK, KEY_PAUSE},//  18
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MEDIA_VOLUME_DEC, KEY_MEDIA_VOLUME_INC, KEY_MEDIA_MUTE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP},// 19
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_UP, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, 0, KEY_END, KEY_PAGE_DOWN},// 20
    {MY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_RETURN, 0, 0, 0, 0},//    21
    {KEY_LEFT_SHIFT, 0, KEY_Z, KEY_X, KEY_CAPS_LOCK, KEY_V, KEY_BACKSPACE, KEY_N, KEY_DELETE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT, 0, 0, 0, 0},//    22
    {FN1, KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, 0, KEY_LEFT_CTRL, 0, 0, 0, KEY_RIGHT_GUI, FN2, FN3, 254, KEY_RIGHT_CTRL, 0, 0, 0}//    23
  }
};

void loop() {
  for (int row = 18; row <= 23; row++) {
    for (int col = 1; col <= 17; col++) {
      int layer = 0;
      if (caps || fn1) {
        layer = 1;
      } else {
        layer = 0;
      }
      int pressKey = keymap[layer][row - 18][col - 1];
      digitalWrite(col, LOW);
      digitalRead(row);
      digitalRead(row);
      if (digitalRead(row)) {
        if (pressKey == FN1) {
          fn1 = false;
        } else if (pressKey == FN2) {
          fn2 = false;
        } else if (pressKey == FN3) {
          fn3 = false;
        } else if (pressKey == MY_CAPS_LOCK) {
          switch (capsState) {
            case 1:
              capsState = 0;
              caps = false;
              Keyboard.press(KEY_CAPS_LOCK);
              Keyboard.release(pressKey);
            case 2:
              capsState = 0;
              caps = false;
            default:
              break;
          }
        } else {
          Keyboard.release(pressKey);
        }
      } else {
//        Serial.print("press row = ");
//        Serial.print(row);
//        Serial.print(", col = ");
//        Serial.print(col);
//        Serial.print(", keymap[");
//        Serial.print(layer);
//        Serial.print("][");
//        Serial.print(row - 18);
//        Serial.print("][");
//        Serial.print(col - 1);
//        Serial.print("] = ");
//        Serial.println(pressKey);
        switch (pressKey) {
          case MY_CAPS_LOCK:
            if (capsState == 0) {
              capsState = 1;
            }
            caps = true;
            break;
          case FN1:
            fn1 = true;
            break;
          case FN2:
            fn2 = true;
            break;
          case FN3:
            fn3 = true;
            break;
          case KEY_MEDIA_VOLUME_DEC:
          case KEY_MEDIA_VOLUME_INC:
          case KEY_MEDIA_MUTE:
            Keyboard.set_media(pressKey);
            Keyboard.send_now();
            Keyboard.set_media(0);
            Keyboard.send_now();
            break;
          default:
            if (capsState == 1) {
              capsState = 2;
            }
            Keyboard.press(pressKey);
            delay(20);
            break;
        }
      }
      digitalWrite(col, HIGH);
    }
  }
}
