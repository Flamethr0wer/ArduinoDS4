#include "PS4Arduino.h"

#if defined(USBCON) && !defined(PS4ARDUINO_USB)
	#warning "You need to select [____ as PS4 controller] in the boards tab to be able to communicate with your PlayStation!"
#endif

PS4Arduino PS4controller;

void PS4Arduino::writeToEndpoint(const uint8_t* data, uint8_t len) {
  	for (uint8_t i = 0; i < len; i++) {
    	UEDATX = data[i];
  	}
}

void PS4Arduino::txInterruptCallback() {
  	PS4controller.reportCounter = (PS4controller.reportCounter + 1) & 0x3F;
	PS4controller.report.reportCounter = PS4controller.reportCounter;
  	PS4controller.timestamp++;
  	PS4controller.report.axisTiming = PS4controller.timestamp;
  	PS4controller.writeToEndpoint((const uint8_t*)&PS4controller.report, sizeof(PS4controller.report));
  	UEINTX &= ~(1 << FIFOCON);
}

void PS4Arduino::controllerOutHandler() {
	uint8_t buf[64];
    int n = USB_Recv(PS4ARDUINO_RX_ENDPOINT, buf, USB_Available(PS4ARDUINO_RX_ENDPOINT));
}

void PS4Arduino::begin(){
	memset(&report, 0, sizeof(report));
	report.reportID = 0x01;
	report.leftStickX = 0x80;
	report.leftStickY = 0x80;
	report.rightStickX = 0x80;
	report.rightStickY = 0x80;
	report.dpad = 0x08;
	report.buttonNorth = 0x00;
	report.buttonSouth = 0x00;
	report.buttonEast = 0x00;
	report.buttonWest = 0x00;
	report.buttonL1 = 0x00;
	report.buttonL2 = 0x00;
	report.buttonL3 = 0x00;
	report.buttonR1 = 0x00;
	report.buttonR2 = 0x00;
	report.buttonR3 = 0x00;
	report.buttonHome = 0x00;
	report.buttonTouchpad = 0x00;
	report.reportCounter = reportCounter;
	report.leftTrigger = 0x00;
	report.rightTrigger = 0x00;
	report.axisTiming = timestamp;
	report.battery = 0x11;
	report.gyrox = 0x0000;
	report.gyroy = 0x0000;
	report.gyroz = 0x0000;
	report.accx = 0x0000;
	report.accy = 0x0000;
	report.accz = 0x2000;

	PS4ArduinoUSB::setSendCallback(txInterruptCallback);
  	PS4ArduinoUSB::setRecvCallback(controllerOutHandler);

	noInterrupts();
  	UENUM = PS4ARDUINO_TX_ENDPOINT;
  	if (UEINTX & (1 << RWAL)) {
    	writeToEndpoint((const uint8_t*)&report, sizeof(report));
    	UEINTX &= ~(1 << FIFOCON);
  	}
  	interrupts();

	delay(1000);
	report.buttonHome = 0x01;

	noInterrupts();
  	UENUM = PS4ARDUINO_TX_ENDPOINT;
  	if (UEINTX & (1 << RWAL)) {
    	writeToEndpoint((const uint8_t*)&report, sizeof(report));
    	UEINTX &= ~(1 << FIFOCON);
  	}
  	interrupts();
	
	delay(100);
	report.buttonHome = 0x00;
}

void PS4Arduino::maintainConnection() {
  	if (millis() - lastReconnect >= 480000) {
    	UDCON |= (1 << DETACH);
  		delay(100);
  		UDCON &= ~(1 << DETACH);
		lastReconnect = millis();
		delay(1000);
		PS4ArduinoUSB::setSendCallback(txInterruptCallback);
		PS4ArduinoUSB::setRecvCallback(controllerOutHandler);
		
		report.buttonHome = 0x01;
		
		noInterrupts();
  		UENUM = PS4ARDUINO_TX_ENDPOINT;
  		if (UEINTX & (1 << RWAL)) {
    		writeToEndpoint((const uint8_t*)&report, sizeof(report));
    		UEINTX &= ~(1 << FIFOCON);
  		}
  		interrupts();
		
		delay(100);
		report.buttonHome=0x00;
  	}
}

void PS4Arduino::setDpad(dirEnum direction) {
	if(direction == 1) {report.dpad = 0;}
	else if(direction == 2) {report.dpad = 1;}
	else if(direction == 3) {report.dpad = 2;}
	else if(direction == 4) {report.dpad = 3;}
	else if(direction == 5) {report.dpad = 4;}
	else if(direction == 6) {report.dpad = 5;}
	else if(direction == 7) {report.dpad = 6;}
	else if(direction == 8) {report.dpad = 7;}
	else if(direction == 9) {report.dpad = 8;}
}

void PS4Arduino::setButton(buttonEnum button, bool state) {
	if(button == 1) {report.buttonNorth = state;}
	else if(button == 2) {report.buttonEast = state;}
	else if(button == 3) {report.buttonSouth = state;}
	else if(button == 4) {report.buttonWest = state;}
	else if(button == 5) {report.buttonSelect = state;}
	else if(button == 6) {report.buttonStart = state;}
	else if(button == 7) {report.buttonHome = state;}
	else if(button == 8) {report.buttonL1 = state;}
	else if(button == 9) {report.buttonL2 = state;}
	else if(button == 10) {report.buttonL3 = state;}
	else if(button == 11) {report.buttonR1 = state;}
	else if(button == 12) {report.buttonR2 = state;}
	else if(button == 13) {report.buttonR3 = state;}
	else if(button == 14) {report.buttonTouchpad = state; }
}

void PS4Arduino::setTrigger(sideEnum trigger, uint8_t value) {
	if(trigger == 1) {report.leftTrigger = value;}
	else if(trigger == 2) {report.rightTrigger = value;}
}

void PS4Arduino::setJoystick(sideEnum joystick, axisEnum axis, uint8_t value) {
	if(joystick == 1 && axis == 1) {report.leftStickX = value;}
	else if(joystick == 1 && axis == 2) {report.leftStickY = value;}
	else if(joystick == 2 && axis == 1) {report.rightStickX = value;}
	else if(joystick == 2 && axis == 2) {report.rightStickY = value;}
}
