#include <FSM.h>
#include <FSM_MACROS.h>;
FSM_SETUP(millis)

class RGB {
  public:
    byte values[3];
    RGB(byte Red, byte Green, byte Blue) {
      values[0] = Red;
      values[1] = Green;
      values[2] = Blue;
    }
};

class RGBLight {
    int Leds[3];


  public:
    RGBLight(int Red, int Green, int Blue) {
      Leds[0] = Red;
      Leds[1] = Green;
      Leds[2] = Blue;
    }

    void Write(RGB color) {
      for (int x = 0 ; x < 3 ; x++) {
        analogWrite(Leds[x], color.values[x]);
      }
    }

    void Configurar() {
      for (int x = 0 ; x < 3 ; x++) {
        pinMode(Leds[x], OUTPUT);
      }
    }

};



