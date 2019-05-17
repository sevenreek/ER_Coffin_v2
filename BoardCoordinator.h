#pragma once

#include "WirelessController.h"
#include "GPIOController.h"
#include "Message.h"
enum CoffinStates {
	LOCKED,
	OPENED,
	DONE,
};
class BoardCoordinator {
private:
	CoffinStates state;
	WirelessController * wireless;
	GPIOController * gpio;
	unsigned int currentInterfaceIndex;
	unsigned long unlockTimer;
	unsigned long lastUpdate;
public:
	static const unsigned int PARTIAL_UNLOCK_TIME;
	BoardCoordinator(WirelessController * wireless, GPIOController * gpio);
	void onUpdate();
	void finishPuzzle();
};