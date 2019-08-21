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
	Serial.println("Unlocking coffin...");
	digitalWrite(PIN_MAGNET, LOW);
	delay(100);
	digitalWrite(PIN_MAGNET, HIGH);
}

// A1, 12 ARMS
// A2 CHEST
// 7 A3 LEGS
const uint8_t Skeleton::PIN_REEDS[SKELETON_REED_COUNT] = {8,11,10,A0}; // chest and skull are now permanently fixed inplace.
const uint8_t Skeleton::PIN_LEDS[SKELETON_REED_COUNT] = { 7, A3, A1, A4 }; // chest and skull are now permanently fixed inplace.
const uint8_t Skeleton::PIN_CHEST_LED = A2;
void Skeleton::init()
{
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		pinMode(PIN_REEDS[i], INPUT_PULLUP);
		pinMode(PIN_LEDS[i], OUTPUT);
		digitalWrite(PIN_LEDS[i], LOW);
	}
	pinMode(PIN_CHEST_LED, OUTPUT);
	digitalWrite(PIN_CHEST_LED, LOW);
}
void Skeleton::killLEDs()
{
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		digitalWrite(PIN_LEDS[i], LOW);
	}
	digitalWrite(PIN_CHEST_LED, LOW);
}
void Skeleton::begin()
{
	digitalWrite(PIN_CHEST_LED, HIGH);
}
void Skeleton::free()
{

}
uint8_t Skeleton::getCorrectCount()
{
	uint8_t count = 0;
	for (int i = 0; i < SKELETON_REED_COUNT; i++)
	{
		Serial.print(digitalRead(PIN_REEDS[i]));
		if (digitalRead(PIN_REEDS[i]) == LOW)
		{
			count++;
			digitalWrite(PIN_LEDS[i], HIGH);
		}
		else
		{
			digitalWrite(PIN_LEDS[i], LOW);
		}
	}
	Serial.println();
	return count;
}
