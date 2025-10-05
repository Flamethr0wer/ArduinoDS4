#ifndef ARDUINOPS4_H
#define ARDUINOPS4_H

#include <Arduino.h>

enum dirEnum : uint8_t {
  DPAD_N = 1,
  DPAD_NE = 2,
  DPAD_E = 3,
  DPAD_SE = 4,
  DPAD_S = 5,
  DPAD_SW = 6,
  DPAD_W = 7,
  DPAD_NW = 8,
  DPAD_RELEASED = 9,
};

enum buttonEnum : uint8_t {
  TRIANGLE = 1,
  CIRCLE = 2,
  CROSS = 3,
  SQUARE = 4,
  SHARE = 5,
  OPTIONS = 6,
  PS = 7,
  L1 = 8,
  L2 = 9,
  L3 = 10,
  R1 = 11,
  R2 = 12,
  R3 = 13,
  TOUCHPAD = 14,
};

enum sideEnum : uint8_t {
  LEFT = 1,
  RIGHT = 2,
};

enum axisEnum : uint8_t {
  X = 1,
  Y = 2,
};

class ArduinoPS4 {
  public:
    void begin();
    void maintainConnection();
    void setDpad(dirEnum direction);
    void setButton(buttonEnum button, bool state);
    void setTrigger(sideEnum trigger, uint8_t value);
    void setJoystick(sideEnum joystick, axisEnum axis, uint8_t value);
  private:
    struct DS4Report {
      uint8_t reportID;
      uint8_t leftStickX;
      uint8_t leftStickY;
      uint8_t rightStickX;
      uint8_t rightStickY;
      uint8_t dpad : 4;
      uint16_t buttonWest : 1;
      uint16_t buttonSouth : 1;
      uint16_t buttonEast : 1;
      uint16_t buttonNorth : 1;
      uint16_t buttonL1 : 1;
      uint16_t buttonR1 : 1;
      uint16_t buttonL2 : 1;
      uint16_t buttonR2 : 1;
      uint16_t buttonSelect : 1;
      uint16_t buttonStart : 1;
      uint16_t buttonL3 : 1;
      uint16_t buttonR3 : 1;
      uint16_t buttonHome : 1;
      uint16_t buttonTouchpad : 1;
      uint8_t reportCounter : 6;
      uint8_t leftTrigger;
      uint8_t rightTrigger;
      uint16_t axisTiming;
      uint8_t battery;
      uint8_t reserved0;
      int16_t gyrox;
      int16_t gyroy;
      int16_t gyroz;
      int16_t accx;
      int16_t accy;
      int16_t accz;
      uint8_t misc[4];
      uint8_t powerLevel : 4;
      uint8_t charging : 1;
      uint8_t headphones : 1;
      uint8_t microphone : 1;
      uint8_t extension : 1;
      uint8_t extData0 : 1;
      uint8_t extData1 : 1;
      uint8_t notConnected : 1;
      uint8_t extData3 : 5;
      uint8_t misc2;
      uint8_t tpadIncrement;
      uint8_t touchpad_counter_p1 : 7;
      uint8_t touchpad_unpressed_p1 : 1;
      uint8_t touch1_pos1;
      uint8_t touch1_pos2;
      uint8_t touch1_pos3;
      uint8_t touchpad_counter_p2 : 7;
      uint8_t touchpad_unpressed_p2 : 1;
      uint8_t touch2_pos1;
      uint8_t touch2_pos2;
      uint8_t touch2_pos3;
      uint8_t mystery2[22];
    } __attribute__((packed));
    DS4Report report;
    volatile uint16_t timestamp = 0;
    volatile uint8_t reportCounter = 0;
    unsigned long lastReport = 0;
    unsigned long lastReconnect = 0;
    static void writeToEndpoint(const uint8_t* data, uint8_t len);
    static void txInterruptCallback();
    static void controllerOutHandler();
};

extern ArduinoPS4 arduinoPS4;

#endif
