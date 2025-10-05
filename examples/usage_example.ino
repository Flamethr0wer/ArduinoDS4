#include <PS4Arduino.h>

void setup() {
  PS4controller.begin();
}

void loop() {
  PS4controller.setJoystick(LEFT, Y, 255);  // left joystick fully up
  PS4controller.setJoystick(LEFT, X, 200);  // and a bit to the right
  delay(1000);
  PS4controller.setButton(CROSS, 1);        // X pressed
  delay(100);
  PS4controller.setButton(CROSS, 0);        // X released
  PS4controller.setJoystick(LEFT, Y, 128);  // left          in     center
  PS4controller.setJoystick(LEFT, X, 128);  //      joystick    the
  delay(2000);
  PS4controller.setDpad(DPAD_N);            // D-pad up button pressed
  delay(500);
  PS4controller.setDpad(DPAD_SE);           // D-pad down and right buttons pressed
  delay(500);
  PS4controller.setDpad(DPAD_RELEASED);     // D-pad unpressed
  PS4controller.setTrigger(RIGHT, 255);     // R2 fully pressed
  delay(2000);
  PS4controller.setTrigger(RIGHT, 0);       // R2 fully released
  
  PS4controller.maintainConnection();       // Prevent disconnect
}
