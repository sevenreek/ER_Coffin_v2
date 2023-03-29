// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Coffin.ino
    Created:	2019-05-02 10:57:38 AM
    Author:     DESKTOP-RP1NLIS\Dickbutt
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts

#include <SPI.h>
#include "BoardCoordinator.h"
WirelessController * wireless;
GPIOController *gpio;
BoardCoordinator * coordinator;
void setup()
{
	Serial.begin(9600);
	Serial.println("Starting");
	wireless = new WirelessController(14, 10);
	gpio = new GPIOController();
	coordinator = new BoardCoordinator(wireless, gpio);

}

// Add the main program code into the continuous loop() function
void loop()
{
	coordinator->onUpdate();

}
