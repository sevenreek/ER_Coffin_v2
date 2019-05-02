#include "GPIOController.h"

GPIOController::GPIOController()
{
	coffinTop.init();
	skeleton.init();
}
const uint8_t CoffinTop::PIN_MAGNET = 9;
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


const uint8_t Skeleton::PIN_REEDS[SKELETON_REED_COUNT] = {8,10,11,12,13};
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
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		if (digitalRead(PIN_REEDS[i]) == LOW)
			count++;
	}
	return count;
}
