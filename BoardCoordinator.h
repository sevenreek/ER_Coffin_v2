#pragma once

#include "WirelessController.h"
#include "GPIOController.h"
#include "Message.h"
class BoardCoordinator {
private:
	bool opened;
	WirelessController * wireless;
	GPIOController * gpio;
	unsigned int currentInterfaceIndex;
public:
	BoardCoordinator(WirelessController * wireless, GPIOController * gpio);
	void onUpdate();
};