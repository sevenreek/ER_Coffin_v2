
#include <SPI.h>
#include "BoardCoordinator.h"
WirelessController wireless(9, 10);
GPIOController gpio;
BoardCoordinator coordinator(&wireless, &gpio);

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  wireless.begin();
  Serial.println("Start");
}

// Add the main program code into the continuous loop() function
void loop()
{
	coordinator.onUpdate();
}
