#include "ArduinoDS4.h"

#if defined(USBCON)
	#ifndef ARDUINODS4_USB
		#warning "You need to select [____ as DS4] in the boards tab to be able to communicate with your PlayStation!"
	#endif
#else
	#ifndef USB_XINPUT
		#error "Warning: this board does not support HID. It will not work with ArduinoDS4."
	#endif
#endif

