#idndef ARDUINOPS4_H
#define ARDUINOPS4_H

#include <Arduino.h>

#define dpadUp 1
#define dpadRight 2
#define dpadDown 3
#define dpadLeft 4
#define triangle 5
#define circle 6
#define cross 7
#define square 8
#define SHARE 9
#define OPTIONS 10
#define PS 11
#define L1 12
#define L2 13
#define L3 14
#define R1 15
#define R2 16
#define R3 17
#define touchpad 18

#define left 0
#define right 1
#define X 0
#define Y 1

class ArduinoPS4 {
  public:
    void begin();
    void setButton(uint8_t button, bool state);
    void setTrigger(uint8_t trigger, uint8_t value);
    void setJoystick(bool joystick, bool axis, uint8_t value);
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
    volatile uint32_t timestamp = 0;
    unsigned long lastReport = 0;
    void writeToEndpoint(const uint8_t* data, uint8_t len);
    void txInterruptCallback()
    void controllerOutHandler()
}

#endif
