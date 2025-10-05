# PS4Arduino
This library will allow you to turn your Arduino into a controller fully compatible with PS4!

## How to use
Really simple! This library includes 6 functions to cover all inputs:

- `PS4controller.begin()`: call this to initialize the library.

- `PS4controller.setButton(button, state)`: sets the state of a button. It takes two parameters: the button, which can be one of the following:
  - `TRIANGLE`
  - `CIRCLE`
  - `CROSS`
  - `SQUARE`
  - `SHARE`
  - `OPTIONS`
  - `PS`
  - `L1`
  - `L2`
  - `L3`
  - `R1`
  - `R2`
  - `R3`
  - `TOUCHPAD`
  
  and the state, which can be either `true`/`1` or `false`/`0`.

- `PS4Controller.setDpad(direction)`: sets the direction of the dpad. Takes 1 parameter, which can be:
  - `DPAD_N`
  - `DPAD_NE`
  - `DPAD_E`
  - `DPAD_SE`
  - `DPAD_S`
  - `DPAD_SW`
  - `DPAD_W`
  - `DPAD_NW`
  - `DPAD_RELEASED`

  (the letters stand for the cardinal directions, e.g. NE is the top and right buttons pressed simultaneously).

- `PS4Controller.setTrigger(trigger, value)`: this is the function to use if you want to press L2/R2 but not fully (useful for throttle/braking). Takes 2 parameters: the trigger (`LEFT`/`RIGHT`) and a value from 0 to 255 (0 is fully unpressed and 255 is fully pressed).

- `PS4Controller.setJoystick(joystick, axis, value)`: sets the value of a joystick axis. Takes three parameters: the joystick (`LEFT`/`RIGHT`), the axis (`X`/`Y`) and a value from 0 to 255. 128 is the middle.

- `PS4Controller.maintainConnection()`: You must call this frequently (e.g. once per loop) to prevent the board from being disconnected from your PS4.

And that's about it! You can take a look at this example for further reference.

## Currently supported boards:
- Arduino Leonardo
- Arduino Leonardo ETH
- Arduino Micro
- Arduino Esplora
