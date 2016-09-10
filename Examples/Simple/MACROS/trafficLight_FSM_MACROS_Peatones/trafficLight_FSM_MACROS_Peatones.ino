#include <FSM.h>
FSM_SETUP(millis)

class RGB {
  public:
    byte values[3];
    RGB(byte Rojo, byte Verde, byte Azul) {
      values[0] = Rojo;
      values[1] = Verde;
      values[2] = Azul;
    }
};

class RGBLight {
    int Leds[3];


  public:
    RGBLight(int Rojo, int Verde, int Azul) {
      Leds[0] = Rojo;
      Leds[1] = Verde;
      Leds[2] = Azul;
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

