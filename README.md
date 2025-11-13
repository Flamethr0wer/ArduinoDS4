# PS4Arduino
This library will allow you to turn your Arduino into a controller fully compatible with PS4!

**IMPORTANT: You must install the PS4Arduino-AVR core for the library to work. Instructions [here](https://github.com/Flamethr0wer/PS4Arduino-AVR/blob/master/README.md). \
Once installed, you need to select "____ as PS4 controller" as the board.**

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

- `PS4controller.setDpad(direction)`: sets the direction of the dpad. Takes 1 parameter, which can be:
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

- `PS4controller.setTrigger(trigger, value)`: this is the function to use if you want to press L2/R2 but not fully (useful for throttle/braking). Takes 2 parameters: the trigger (`LEFT`/`RIGHT`) and a value from 0 to 255 (0 is fully unpressed and 255 is fully pressed).

- `PS4controller.setJoystick(joystick, axis, value)`: sets the value of a joystick axis. Takes three parameters: the joystick (`LEFT`/`RIGHT`), the axis (`X`/`Y`) and a value from 0 to 255. 128 is the middle.

- `PS4controller.maintainConnection()`: You must call this frequently (e.g. once per loop) to prevent the board from being disconnected from your PS4.

And that's about it! You can take a look at [this example](https://github.com/Flamethr0wer/PS4Arduino/blob/main/examples/usage_example.ino) for further reference.

## Currently supported boards:
- Arduino Leonardo
- Arduino Leonardo ETH
- Arduino Micro
- Arduino Esplora

## Step-by-step

This section is for people newer to the Arduino ecosystem based on a contributer's learnings.

### Plan

1. get pre-requisites
2. flash demo program
3. test it
4. iterate
5. restore

### 1 pre-reqs

You'll need to get the following:

1. Arduino IDE - [official docs for download and install](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/)
2. PS4Arduino-AVR, follow [instructions](https://github.com/Flamethr0wer/PS4Arduino-AVR/blob/master/README.md) also linked at top
3. Install PS4Arduino library in Arduino IDE. Follow the [official docs](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/) to install `PS4Arduino`

### 2 flash demo program

This will pause, move to the right, pause, move back to the left and then repeat over and over.

There are three steps to this:

1. change board to "____ as PS4 controller"
2. enter the sketch code
3. upload to arduino

#### 1 change board to ___ as PS4 controller

For a standard board, this should be simple the first time. Once connected, the board should appear in the Arduino IDE menu Tools > Ports.

In order for the PS4 to recognise the Arduino as a controller, part of its firmware needs to be updated to be non-standard. This is so it can report to the PS4 that it is a controller rather than an Arduino. This has the side effect of making it not show up in the Arduino IDE next time but more on that below.

1. Connect board, confirm it appears in Tools > Ports. It will shows as COMn on windows where n is a number eg COM8.
2. Override board type by selecting Tools > Board "{your board}" > "PS4Arduino AVR Boards" > "{your board} as PS4 contoller"

#### 2 enter sketch code

The sketch code is below, copy and paste this into the Arduino IDE:

```
#include "PS4Arduino.h"

void setup() {
  PS4controller.begin();
}

void loop() {

  delay(2000);
  PS4controller.setDpad(DPAD_E);         // D-pad right
  delay(50);
  PS4controller.setDpad(DPAD_RELEASED);  // D-pad unpressed

  delay(2000);                           // wait 2 seconds
  PS4controller.setDpad(DPAD_W);         // D-pad left
  delay(50);
  PS4controller.setDpad(DPAD_RELEASED);  // D-pad unpressed

  PS4controller.maintainConnection();    // keep connected
}
```

#### upload to Arduino

As the board is connected as regular Arduino, this step is the same as other uploads: click the upload button.

For future uploads, it will be different since the board is telling your computer that it is a PS4 controller rather than Arduino.

### test it

Now is the time to take your hot flashed board and connect to your PS4. The best way to do this is as follows:

1. turn on PS4 (normally with controller)
2. get to a screen where you can test the code. In our example the home screen is ok
3. if turned on with controller, press and hold the ps button on controller for 10 seconds for it to turn off
4. connect arduino with usb cable
5. observe your programme running!

### iterate

TODO: note how have to click upload then press reset button

### restore

If you wish to return your Arduino back to "normal" then you will need to reverse the change board steps above.

1. Load Blink by File > Examples > 01 Basics > Blink
2. Set board type back to normal by selecting Tools > Board "{your board}" > "Arduino AVR Boards" > "{your board}"
3. Upload following steps above ie click upload then press reset on the arduino board
