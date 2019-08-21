#pragma once
#include "Arduino.h"
#include "WirelessController.h"


class GameObject {
public: 
	virtual void init() = 0;
	virtual void free() = 0;
};
class CoffinTop :  GameObject {
private:
	static const uint8_t PIN_MAGNET;
public:
	void init();
	void free();
	void open();
};
static const uint8_t SKELETON_REED_COUNT = 4; // chest and skull are now locked in place
class Skeleton :  GameObject {
private:
	static const uint8_t PIN_REEDS[SKELETON_REED_COUNT];
	static const uint8_t PIN_LEDS[SKELETON_REED_COUNT];
	static const uint8_t PIN_CHEST_LED;
public:
	void init();
	void free();
	void begin();
	void killLEDs();
	uint8_t getCorrectCount();
};
class GPIOController {
public:
	GPIOController();
	CoffinTop coffinTop;
	Skeleton skeleton;
};
