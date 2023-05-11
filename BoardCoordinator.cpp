#include "BoardCoordinator.h"
const unsigned int BoardCoordinator::PARTIAL_UNLOCK_TIME = 25000; // ms
BoardCoordinator::BoardCoordinator(WirelessController * wireless, GPIOController * gpio)
{
	state = LOCKED;
	this->wireless = wireless;
	this->gpio = gpio;
	unlockTimer = 0;
}
void BoardCoordinator::finishPuzzle()
{
	Serial.println("Finished skeleton");
	Message* m = new Message(SNDR_COFFIN, MTYPE_STATE, CMD_COFFIN_COMPLETED, 0);
	wireless->sendMessage(m, 1);
	delete m;
	state = DONE;
}
void BoardCoordinator::onUpdate()
{
	Message * msg = 0;
	if (wireless->hasMessage(msg) && msg->sender == SNDR_MEGA && msg->command==CMD_COFFIN_UNLOCKED)
	{
		Serial.println("Unlocking");
		gpio->coffinTop.open();
		state = OPENED;
		delete msg;
	}
	
	if (state == OPENED)
	{
		lastUpdate = millis();
		if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT)
		{
			finishPuzzle();
		}
		else if (gpio->skeleton.getCorrectCount() == SKELETON_REED_COUNT-1 && lastUpdate != millis())
		{
			unlockTimer = unlockTimer + (millis() - lastUpdate);
	
			if (unlockTimer >= PARTIAL_UNLOCK_TIME) {
				finishPuzzle();
			}
		}
		delay(1);
	}
}
