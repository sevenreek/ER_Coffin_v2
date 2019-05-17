#pragma once
#include <SPI.h>
#include <RH_ASK.h>
#include "Message.h"
#include "Arduino.h"
class WirelessController {
private:
	RH_ASK * driver;
public:
	static const int REPEAT_COUNT;
	WirelessController(int speed, int rx, int tx, int ptt, bool ptt_inv);
	void sendMessage(Message * m, int repeatCount);
	bool hasMessage(Message *& m);
};