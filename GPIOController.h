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
static const uint8_t SKELETON_REED_COUNT = 5;
class Skeleton :  GameObject {
private:
	static const uint8_t PIN_REEDS[SKELETON_REED_COUNT];
public:
	void init();
	void free();
	uint8_t getCorrectCount();
};
class GPIOController {
public:
	GPIOController();
	CoffinTop coffinTop;
	Skeleton skeleton;
};
