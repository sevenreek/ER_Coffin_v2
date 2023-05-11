#include "GPIOController.h"

GPIOController::GPIOController()
{
	coffinTop.init();
	skeleton.init();
}
const uint8_t CoffinTop::PIN_MAGNET = 2;
void CoffinTop::init()
{
	pinMode(PIN_MAGNET, OUTPUT);
	digitalWrite(PIN_MAGNET, HIGH);
}
void CoffinTop::free()
{

}
void CoffinTop::open()
{
	digitalWrite(PIN_MAGNET, LOW);
	delay(100);
	digitalWrite(PIN_MAGNET, HIGH);
}


const uint8_t Skeleton::PIN_REEDS[SKELETON_REED_COUNT] = {3, 4, 5, 6}; // chest and skull are now permanently fixed inplace.
void Skeleton::init()
{
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		pinMode(PIN_REEDS[i], INPUT_PULLUP);
	}
	
}
void Skeleton::free()
{

}
uint8_t Skeleton::getCorrectCount()
{
	uint8_t count = 0;
  uint8_t newState = 0b0000;
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		uint8_t pinState = digitalRead(PIN_REEDS[i]);
    newState = newState | ((1 & pinState) << i); 
		if(pinState == LOW)
			count++;
	}
  if(newState != this->lastState) { 
    Serial.print(newState, BIN); 
    Serial.println();
  }
  this->lastState = newState;
	//Serial.println();
	return count;
}
