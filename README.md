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

This section is a step-by-step guide for people newer to the Arduino ecosystem. It will guide you through getting the required software to flash your  and control your PS4.

### Plan

1. Pre-requisites
2. Flash
3. Test
4. Iterate
5. Restore

### 1. Pre-requisites

You'll need to assemble the following:

1. Arduino IDE to edit the sketch - [official docs for download and install](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/)
2. PS4Arduino-AVR, follow [instructions](https://github.com/Flamethr0wer/PS4Arduino-AVR/blob/master/README.md) linked at top
3. Install PS4Arduino library in Arduino IDE. Follow the [official library install docs](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/) to install `PS4Arduino` by Flamethrower. Make sure it is at least v1.0.1
4. A physical Arduino board, see supported boards above

### 2. Flash

This step will update the board's identity and upload a sketch to your Arduino. The sketch will cause the controller to pause, move to the right, pause, move back to the left and repeat over and over.

There are three steps to this:

1. Change board to "____ as PS4 controller"
2. Enter sketch code
3. Upload to Arduino

#### 2.1. Change board to "____ as PS4 controller"

For a standard board, this should be simple the first time. Once connected, the board should appear in the Arduino IDE menu Tools > Ports.

In order for the PS4 to recognise the Arduino as a controller, part of its firmware needs to be updated to be non-standard. This is so it can report to the PS4 that it is a controller rather than an Arduino. This has the side effect of making it not show up in the Arduino IDE next time on your computer but more on that below.

1. Connect board, confirm it appears in Tools > Ports. It will shows as `COMn` on windows where n is a number eg `COM8`.
2. Override board type by selecting Tools > Board "{your board}" > "PS4Arduino AVR Boards" > "{your board} as PS4 contoller"

> [!NOTE]
> Once the board is changed it will not appear under the Tools > Ports menu. See [4. Iterate](#4-iterate) below for details.

#### 2.2. Enter sketch code

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

#### 2.3. Upload to Arduino

As the board is connected as a regular Arduino, this step is the same as other uploads: click the upload button.

For future uploads, it will be different since the board is telling your computer that it is a PS4 controller rather than Arduino. See [4. Iterate](#4-iterate) below.

### 3. Test

Now is the time to take your flashed Arduino and connect to your PS4. The best way to do this is as follows:

1. Turn on PS4 (normally with controller)
2. Get to a screen where you can test the code. In our example the home screen is ok
3. If turned on with controller, press and hold the ps button on controller for 10 seconds for it to turn off
4. Connect Arduino with usb cable
5. Observe your sketch running!

### 4. Iterate

As your board is now the "____ as PS4 controller" version, it will not show up on the Tools > Ports menu like it used to. This is a side effect of having it appear as a PS4 Controller.

Do not fear! It is still possible to upload the image, you just need to try this one easy trick:

1. Make the modification in your sketch.
2. Click the upload icon (or Sketch > Upload)
3. While it is compiling, press the reset button on your Arduino
    - On Windows with the Arduino IDE, this can be done after the "Compiling sketch..." notification changes to "Uploading..."
    - If you get an upload error try pressing the reset button earlier or later

### 5. Restore

**OPTIONAL**: If you wish to return your Arduino back to "normal" then you will need to reverse the change board steps above:

1. In the Arduino IDE, load a standard sketch eg Blink by File > Examples > 01 Basics > Blink
2. Set board type back to normal by selecting Tools > Board "{your board}" > "Arduino AVR Boards" > "{your board}"
3. Upload the standard AVR and sketch following steps above ie click upload then press reset on the Arduino board

## Troubleshooting

### error: 'PS4ARDUINO_RX_ENDPOINT' was not declared in this scope

This error occurs if you are trying to use the PS4Arduino library but have not use the PS4Arduino-ARV to change the board type. Instructions [here](https://github.com/Flamethr0wer/PS4Arduino-AVR/blob/master/README.md).

### Failed uploading: uploading error: exit status 1

This can occur after you have used the board "_____ as PS4 controller" (PS4Arduino-AVR) as it shows up to the computer as a game controller rather than an Arduino.

To fix this, start uploading your sketch and press the reset button on the Arduino board. More details above under [4. Iterate](#4-iterate) above.
